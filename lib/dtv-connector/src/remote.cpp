#include "remote.h"
#include <util/mcr.h>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/sync/named_semaphore.hpp>
#include <stdio.h>

namespace connector {

Remote::Remote( int memSize )
{
	_memSize = memSize;
	_shm = NULL;
	_mmap = NULL;
	_nMutex = NULL;
	_nSem = NULL;
	_exit = true;
}

Remote::~Remote()
{
	assert(!_shm);
}

bool Remote::start() {
	bool result;

	printf( "[Remote] Start: memory size=%d\n", _memSize );
	clean();
	
	try {
		//	Create process mutex and semaphore
		_nMutex = new ipc::named_mutex( ipc::create_only, GINGA_SHARED_MUTEX );
		_nSem = new ipc::named_semaphore( ipc::create_only, GINGA_SHARED_SEM, 0, ipc::permissions() );

		//	Create shared memory
		_shm = new ipc::shared_memory_object( ipc::create_only, GINGA_SHARED_MEMORY, ipc::read_write );
		_shm->truncate( _memSize );

		//	Map the whole shared memory in this process
		_mmap = new ipc::mapped_region( *_shm, ipc::read_write );

		//	Start render thread
		_exit=false;
		_thread = boost::thread( boost::bind( &Remote::renderThread, this ) );
		result = true;
	} catch( ... ) {
		printf( "[Remote] Warning, error creating shared memory\n" );
		stop();
		result=false;
	}
	
	return result;
}

void Remote::stop() {
	printf( "[Remote] Stop\n" );

	if (!_exit) {
		_exit=true;
		_nSem->post();
		_thread.join();
	}
	
	DEL(_mmap);
	DEL(_shm);
	DEL(_nMutex);
	DEL(_nSem);
}

char *Remote::addr() const {
	return static_cast<char*>( _mmap->get_address() );
}

int Remote::size() const {
	return _mmap->get_size();	
}

void Remote::clean() {
	ipc::shared_memory_object::remove( GINGA_SHARED_MEMORY );
	ipc::named_mutex::remove( GINGA_SHARED_MUTEX );
	ipc::named_semaphore::remove( GINGA_SHARED_SEM );
}

void Remote::lockMemory() {
	_nMutex->lock();
}

void Remote::unlockMemory() {
	_nMutex->unlock();
}

void Remote::renderThread() {
	printf( "[Remote] Render thread begin\n" );	
	bool exit=false;
	while (!exit) {
		_nSem->wait();
		if (_exit) {
			exit=true;
		}
		else {
			render();
		}
	}

	printf( "[Remote] Render thread end\n" );		
}

}

