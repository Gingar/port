/*******************************************************************************

  Copyright 2010 LIFIA - Facultad de Informatica - Univ. Nacional de La Plata

********************************************************************************

  This file is part of Ginga implementation.

    This program is free software: you can redistribute it and/or modify it 
  under the terms of the GNU General Public License as published by the Free 
  Software Foundation, either version 2 of the License.

    Ginga is distributed in the hope that it will be useful, but WITHOUT ANY 
  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
  A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with
  this program. If not, see <http://www.gnu.org/licenses/>.

********************************************************************************

  Este archivo es parte de la implementación de Ginga.

    Este programa es Software Libre: Ud. puede redistribuirlo y/o modificarlo 
  bajo los términos de la Licencia Pública General GNU como es publicada por la
  Free Software Foundation, según la versión 2 de la licencia.

    Ginga se distribuye esperando que resulte de utilidad, pero SIN NINGUNA 
  GARANTÍA; ni siquiera la garantía implícita de COMERCIALIZACIÓN o ADECUACIÓN 
  PARA ALGÚN PROPÓSITO PARTICULAR. Para más detalles, revise la Licencia Pública 
  General GNU.

    Ud. debería haber recibido una copia de la Licencia Pública General GNU 
  junto a este programa. Si no, puede verla en <http://www.gnu.org/licenses/>.

*******************************************************************************/
#include <sstream>
#include <iostream>

using namespace std;

#include "../include/services/RemoteEventService.h"

using namespace ::br::pucrio::telemidia::ginga::core::multidevice;

int main(int argc, char *argv[]) {
	bool result = false;

	RemoteEventService* res = new RemoteEventService();

	cout << "[INICIO DO TESTE]\n";

	cout << "\n[p0]\n";
	res->addDeviceClass(2);

	cout << "\n[p1]\n";
	res->addDevice(2,1,"192.168.1.102");

	//cout << "\n[p2]\n";
	//res->addDocument(2,"doc.ncl","<ncl></ncl>");
	//sleep(3);
	cout << "\n[p3]\n";
	res->startDocument(2,"tests/proview-device/proview-device.ncl");
	cout << "\n[p3.1]\n";
	sleep(10);
	cout << "\n[p4]\n";
	res->stopDocument(2,"doc.ncl");


	//teste 2//
/*
	TCPClientConnection* tcp;
	tcp = new TCPClientConnection("localhost","22222");

	cout << "\n[p1]\n";
	result = tcp->post("0 ADD document.ncl 5\n<ncl>\n");
	cout << result << "\n";

	sleep(3);

	cout << "[p2]\n";
	result = tcp->post("0 START document.ncl 0\n");
	cout << result << "\n";

	sleep(3);
	cout << "[p3]\n";
	result = tcp->post("0 ASDADD teste.oi 0\n");
	cout << result << "\n";
	cout << "[FIM DO TESTE]\n";
	return 0;
*/
}
