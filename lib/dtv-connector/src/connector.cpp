/*******************************************************************************

  Copyright (C) 2010, 2011 LIFIA - Facultad de Informatica - Univ. Nacional de La Plata

********************************************************************************

  This file is part of DTV-connector implementation.

    DTV-connector is free software: you can redistribute it and/or modify it
  under the terms of the GNU Lesser General Public License as published by the Free
  Software Foundation, either version 2 of the License.

    DTV-connector is distributed in the hope that it will be useful, but WITHOUT ANY
  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
  A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License along with
  this program. If not, see <http://www.gnu.org/licenses/>.

********************************************************************************

  Este archivo es parte de la implementación de DTV-connector.

    DTV-connector es Software Libre: Ud. puede redistribuirlo y/o modificarlo
  bajo los términos de la Licencia Pública General Reducida GNU como es publicada por la
  Free Software Foundation, según la versión 2 de la licencia.

    DTV-connector se distribuye esperando que resulte de utilidad, pero SIN NINGUNA
  GARANTÍA; ni siquiera la garantía implícita de COMERCIALIZACIÓN o ADECUACIÓN
  PARA ALGÚN PROPÓSITO PARTICULAR. Para más detalles, revise la Licencia Pública
  General Reducida GNU.

    Ud. debería haber recibido una copia de la Licencia Pública General Reducida GNU
  junto a este programa. Si no, puede verla en <http://www.gnu.org/licenses/>.

*******************************************************************************/
#include "connector.h"
#include "generated/config.h"
#include "handler/messagehandler.h"
#include "handler/keepalivehandler.h"
#include <boost/foreach.hpp>

#define CONNECTOR_TCP_PORT 55555

namespace connector {

Connector::Connector( const std::string &file, bool isServer/*=false*/ )
	: _endPointName(file),	  
	  _port(CONNECTOR_TCP_PORT),
	  _socket(new Socket(_io)),
	  _dataIn( 1024 ),
	  _keepAliveTimer(_io),
	  _acceptTimer(_io)
{
	_isServer            = isServer;
	_keepAliveHandler    = NULL;
	_isConnected         = false;

	//	Connect timeout
	_connectTimeout      = CONNECTOR_CONNECT_TIMEOUT;
	_retryConnectTimeout = CONNECTOR_CONNECT_TIMEOUT_RETRY;
	_maxConnectRetry     = CONNECTOR_CONNECT_TIMEOUT_MAX_RETRY;

	//	Keep alive
	_keepAliveInterval   = CONNECTOR_KEEP_ALIVE_INTERVAL;
	_maxKeepAliveRetry   = CONNECTOR_KEEP_ALIVE_MAX_RETRY;
	_keepAlive           = 0;
	
	printf( "[Connector (%p)] Constructor: file=%s, mode=%d\n", this, file.c_str(), isServer );
	_thread = boost::thread( boost::bind( &Connector::connectorThread, this ) );
}

Connector::~Connector()
{
	printf( "[Connector (%p)] Destructor begin\n", this );	
	_io.stop();
	_thread.join();

	BOOST_FOREACH( const HandlerElement &elem, _handlers ) {
		delete elem.second;
	}

	//	Remove endpoint in case we are the server
	if (_isServer) {
		std::remove(_endPointName.c_str());
	}

	printf( "[Connector (%p)] Destructor end\n", this );
}

void Connector::handle_accept(AcceptorPtr /*acceptor*/,
	const boost::system::error_code& error)
{
	if (!error) {
		_acceptTimer.cancel();
		connected();
		tryRead();
	}
	else {
		_io.stop();
	}
}

void Connector::onAcceptExpired( const boost::system::error_code& error ) {
	if (!error) {
		printf( "[Connector (%p)] Warning, accept timer expired: timer=%d\n", this, _connectTimeout );
		connectTimeout();
	}
}

void Connector::setRetryConnectTimeout( int timeout ) {
	_retryConnectTimeout = timeout;
}

void Connector::setMaxConnectRetry( int maxRetry ) {
	_maxConnectRetry = maxRetry;
}

void Connector::setConnectTimeout( int timeout ) {
	_connectTimeout = timeout;
}

Connector::Endpoint Connector::getEndpoint() {
#if CONNECTOR_USE_TCP_SOCKETS
	return boost::asio::ip::tcp::endpoint(boost::asio::ip::address_v4::loopback(), _port);
#else
	return boost::asio::local::stream_protocol::endpoint(_endPointName);
#endif
}

void Connector::handle_connect(const boost::system::error_code& error) {
	if (error) {
		_maxConnectRetry--;
		if (_maxConnectRetry < 0) {
			printf( "[Connector (%p)] Error: couldn't connect. Timeout expired!\n", this );
			connectTimeout();
		}
		else {
			printf( "[Connector (%p)] Error: couldn't connect. Retrying in %dms\n", this, _retryConnectTimeout );
			boost::this_thread::sleep( boost::posix_time::milliseconds( _retryConnectTimeout ) );
			_socket->async_connect(getEndpoint(),  
				boost::bind(&Connector::handle_connect, this,
					boost::asio::placeholders::error));
		}
	}
	else {
		connected();
		tryRead();
	}
}

void Connector::tryRead( void ) {
	_socket->async_read_some(
		boost::asio::buffer(_dataIn.buffer(), _dataIn.capacity()),
		boost::bind(
			&Connector::handle_read,
			this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred
		)
	);	
}

void Connector::handle_read( const boost::system::error_code& error, size_t transferred ) {
    if (error) {
		//	Error receiving data
	    printf( "[Connector (%p)] Warning: Thread received error from socket: msg=%s\n",
			this, error.message().c_str() );
		_io.stop();
    }
	else {
		//printf( "[Connector (%p)] Bytes transferred: %d\n", this, transferred );

		_dataIn.resize(transferred);
		assembleMessage(_dataIn);  // Assemble the received message

		tryRead();
	}
}

void Connector::send( const util::Buffer *msg ) {
	try {
		boost::asio::write(
			*_socket,
			boost::asio::buffer(msg->buffer(),msg->length()),
			boost::asio::transfer_all()
		);
	} catch( ... ) {
		printf( "[Connector (%p)] Warning, error sending data\n", this );
	}
}

void Connector::assembleMessage( const util::Buffer &b ) {
	int offset  = 0;
	int msgSize, need;
	int rcvLen=b.length();

	while (offset < rcvLen) {
		int sLen=_msg.length();
		
		//	How many bytes need for complete message?
		if (sLen > MESSAGE_HEADER) {
			//	Stored bytes already have header
			msgSize = MSG_SIZE(_msg.buffer());
			need    = msgSize - sLen;
		}
		else if (MESSAGE_HEADER-sLen <= (rcvLen-offset)) {
			//	Stored bytes don't have the header, but with bytes received complete header!
			_msg.append( b.buffer()+offset, MESSAGE_HEADER-sLen );
			offset += MESSAGE_HEADER-sLen;
			sLen    = MESSAGE_HEADER;
			msgSize = MSG_SIZE(_msg.buffer());
			need    = msgSize-MESSAGE_HEADER;
		}
		else {
			//	Can't complete the header
			_msg.append( b.buffer()+offset, rcvLen-offset );
			offset = rcvLen;
			continue;
		}

		assert( need >= 0 );

		//	Copy bytes
		int rest = (rcvLen-offset);
		int copy = (rest > need) ? need : rest;

		// printf( "[Connector (%p)] rcvLen=%d, sLen=%d, msgSize=%d, need=%d, rest=%d, copy=%d\n",
		// 	this, rcvLen, sLen, msgSize, need, rest, copy );
		
		_msg.append( b.buffer()+offset, copy );
		offset += copy;

		// printf( "[Connector (%p)] msgLen=%d\n", this, _msg.length() );

		//	Is message complete?
		if (msgSize == _msg.length()) {
			messageReceived(&_msg);
			_msg.resize(0);
		}
	}
}

void Connector::messageReceived( util::Buffer *m ) {
    util::BYTE type = MSG_TYPE(m->buffer());

	//  printf( "[Connector (%p)] Received a message: type=%d\n", this, type );
    
    Handlers::iterator cb = _handlers.find( (messages::type)type );
    if (cb != _handlers.end()) {
		//printf( "[Connector (%p)] Dispatching to handler\n", this );
		(*cb).second->process( m );
	} else {
	    printf( "[Connector (%p)] Warning: Received unhandled message type: type=%02x\n", this, type );
    }
}

void Connector::addHandler( messages::type type, MessageHandler *handler ) {
	_io.post( boost::bind( &Connector::addHandlerImpl, this, type, handler) );
}

void Connector::addHandler( MessageHandler *handler ) {
	if (handler) {
		_io.post( boost::bind( &Connector::addHandlerImpl, this, handler->type(), handler) );
	}
}

void Connector::addHandlerImpl( messages::type type, MessageHandler *handler ) {
	Handlers::iterator it=_handlers.find(type);
	if (it != _handlers.end()) {
		delete (*it).second;
		if (!handler) {
			_handlers.erase(it);
		}
	}

	if (handler) {
		_handlers[type] = handler;
	}
}

void Connector::connectorThread( void ) {
	printf( "[Connector (%p)] Connector thread started: mode=%d\n",
		this, _isServer );

	if (_isServer) {
		AcceptorPtr acceptor(new Acceptor(_io, getEndpoint()));
		acceptor->async_accept(*_socket,
		    boost::bind(&Connector::handle_accept, this, acceptor, 
				    boost::asio::placeholders::error));

		    //	Launch timer ....
		    launchTimer( _acceptTimer, _connectTimeout, &Connector::onAcceptExpired );
	} else {
		_socket->async_connect(getEndpoint(),
			boost::bind(&Connector::handle_connect, this,
				boost::asio::placeholders::error));
	}

	try {
		_io.run();
	}
	catch (std::exception& e) {
		printf( "[Connector (%p)] Exception: %s\n", this, e.what() );
	}

	disconnected();
	printf( "[Connector (%p)] Info: Connector Thread Stopped\n", this );
}

void Connector::onConnect( const Callback &callback ) {
	_onConnect = callback;
}

void Connector::connected( void ) {
	//	--Connector thread
	if (!_isConnected) {
		if (!_onConnect.empty()) {
			printf( "[Connector (%p)] Connected\n", this );
			_onConnect();
		}
		_isConnected = true;

		//	Add Keep Alive handler
		_keepAliveHandler = new KeepAliveHandler();
		_keepAliveHandler->onKeepAliveEvent( boost::bind(&Connector::onKeepAliveEvent, this, _1) );
		addHandler( _keepAliveHandler );

		if (_isServer) {
			printf( "[Connector (%p)] Launching keep alive timer: interval=%d, retry=%d\n",
				this, _keepAliveInterval, _maxKeepAliveRetry );
			
			//	Launch keep alive timer ....
			_keepAlive=0;
			launchTimer( _keepAliveTimer, _keepAliveInterval, &Connector::onKeepAliveIntervalExpired );
		}
	}
}

void Connector::launchTimer( boost::asio::deadline_timer &timer, int ms, TimerCallback fnc ) {
	timer.expires_from_now( boost::posix_time::milliseconds(ms) );
	timer.async_wait( boost::bind( fnc, this, boost::asio::placeholders::error ) );
}

void Connector::onKeepAliveEvent( connector::KeepAliveData * /*ka*/ ) {
	//	--Connector thread
	if (_isServer) {
		_keepAlive=0;
	}
	else {
		//printf( "[Connector (%p)] Received keep alive\n", this );	

		//	Return data;
		_keepAliveHandler->send(this);
	}
}

void Connector::onKeepAliveIntervalExpired( const boost::system::error_code& error ) {
	//	--Connector thread
	if (!error) {
		//printf( "[Connector (%p)] Sending keep alive\n", this );

		//	Check keep alive data
		if (_keepAlive >= _maxKeepAliveRetry) {
			timeout();
		}
		else {
			_keepAlive++;
			_keepAliveHandler->send(this);
		}

		//	Re-launch timer
		launchTimer( _keepAliveTimer, _keepAliveInterval, &Connector::onKeepAliveIntervalExpired );
	}
}

void Connector::onDisconnect( const Callback &callback ) {
	_onDisconnect = callback;
}

void Connector::disconnected( void ) {
	//	--Connector thread
	if (_isConnected) {
		printf( "[Connector (%p)] Disconnected\n", this );

		//	Send exit to all handlers
		BOOST_FOREACH( const HandlerElement &elem, _handlers ) {
			elem.second->notifyDisconnect();
		}

		//	Send global exit
		if (!_onDisconnect.empty()) {
			_onDisconnect();
		}
		
		_isConnected = false;
	}	
}

void Connector::connectTimeout() {
	//	--Connector thread
	if (!_onConnectTimeout.empty()) {
		printf( "[Connector (%p)] Connect timeout expired\n", this );	
		_onConnectTimeout();
		_io.stop();
	}	
}

void Connector::onConnectTimeout( const Callback &callback ) {
	_onConnectTimeout = callback;
}

void Connector::timeout() {
	//	--Connector thread
	if (!_onTimeout.empty()) {
		printf( "[Connector (%p)] Keep alive Timeout!!!\n", this );
		_onTimeout();
		_io.stop();		
	}
}

void Connector::onTimeout( const Callback &callback ) {
	_onTimeout = callback;
}

//	Keep alive timeout
void Connector::setKeepAliveInterval( int timeout ) {
	_keepAliveInterval = timeout;
}

void Connector::setMaxKeeyAliveRetry( int timeout ) {
	_maxKeepAliveRetry = timeout;
}

}
