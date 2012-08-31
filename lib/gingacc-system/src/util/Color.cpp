/******************************************************************************
Este arquivo eh parte da implementacao do ambiente declarativo do middleware
Ginga (Ginga-NCL).

Direitos Autorais Reservados (c) 1989-2007 PUC-Rio/Laboratorio TeleMidia

Este programa eh software livre; voce pode redistribui-lo e/ou modificah-lo sob
os termos da Licen� Publica Geral GNU versao 2 conforme publicada pela Free
Software Foundation.

Este programa eh distribu�o na expectativa de que seja util, porem, SEM
NENHUMA GARANTIA; nem mesmo a garantia implicita de COMERCIABILIDADE OU
ADEQUACAO A UMA FINALIDADE ESPECIFICA. Consulte a Licenca Publica Geral do
GNU versao 2 para mais detalhes.

Voce deve ter recebido uma copia da Licenca Publica Geral do GNU versao 2 junto
com este programa; se nao, escreva para a Free Software Foundation, Inc., no
endereco 59 Temple Street, Suite 330, Boston, MA 02111-1307 USA.

Para maiores informacoes:
ncl @ telemidia.puc-rio.br
http://www.ncl.org.br
http://www.ginga.org.br
http://www.telemidia.puc-rio.br
******************************************************************************
This file is part of the declarative environment of middleware Ginga (Ginga-NCL)

Copyright: 1989-2007 PUC-RIO/LABORATORIO TELEMIDIA, All Rights Reserved.
  Copyright 2010 LIFIA - Facultad de Informatica - Univ. Nacional de La Plata


This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License version 2 as published by
the Free Software Foundation.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.  See the GNU General Public License version 2 for more
details.

You should have received a copy of the GNU General Public License version 2
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA

For further information contact:
ncl @ telemidia.puc-rio.br
http://www.ncl.org.br
http://www.ginga.org.br
http://www.telemidia.puc-rio.br
*******************************************************************************/

#include "../../include/util/Color.h"
#include "generated/config.h"

namespace util {

	void Color::setColorToI(string color) {
		if (color=="") {
			color = "#000000";
		}

		if (color.substr(0,1)=="#" && color.length() > 6) {
			r = (int)(stof(color.substr(1, 2)));
			g = (int)(stof(color.substr(3, 2)));
			b = (int)(stof(color.substr(5, 2)));
			return;
		}
		
		// backward compatibility with magenta == transparent
		if (color=="magenta" || color == "transparent" ) {
			setColor(BG_R, BG_G, BG_B);
			this->alpha = BG_A;

		}else if (color=="black") {
			setColor(0x10, 0x10, 0x10);
			
		}else if (color=="white") {
			setColor(0xFF, 0xFF, 0xFF);
			
		} else if (color=="blue") {
			setColor(0x00, 0x00, 0xFF);

		} else if (color=="cyan") {
			setColor(0x00, 0xFF, 0xFF);

		} else if (color=="darkGray") {
			setColor(0xA9, 0xA9, 0xA9);

		} else if (color=="gray") {
			setColor(0x80, 0x80, 0x80);

		} else if (color=="green") {
			setColor(0x00, 0x80, 0x00);

		} else if (color=="lightGray") {
			setColor(0xD3, 0xD3, 0xD3);

		} else if (color=="orange") {
			setColor(0xFF, 0xA5, 0x00);

		} else if (color=="pink") {
			setColor(0xFF, 0xC0, 0xCB);

		} else if (color=="red") {
			setColor(0xFF, 0x00, 0x00);

		} else if (color=="yellow") {
			setColor(0xFF, 0xFF, 0x00);

		} else if (color=="silver") {
			setColor(0xC0, 0xC0, 0xC0);

		} else if (color=="maroon") {
			setColor(0x80, 0x00, 0x00);

		} else if (color=="fuchsia") {
			setColor(0xFF, 0x00, 0xFF);

		} else if (color=="purple") {
			setColor(0x80, 0x00, 0x80);

		} else if (color=="lime") {
			setColor(0x00, 0xFF, 0x00);

		} else if (color=="olive") {
			setColor(0x80, 0x80, 0x00);

		} else if (color=="navy") {
			setColor(0x00, 0x00, 0x80);

		} else if (color=="aqua") {
			setColor(0x00, 0xFF, 0xFF);

		} else if (color=="teal") {
			setColor(0x00, 0x80, 0x80);
		}
		else {
			setColor(0x00, 0x00, 0x00);
		}
	}

	Color::Color() {
		this->alpha = 255;
	}

	Color::Color(int r, int g, int b, int alpha) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->alpha = alpha;
	}

	Color::Color(string color, int alpha) {
		this->alpha = alpha;
		setColorToI(color);
	}

	void Color::setColor(string color) {
		setColorToI(color);
	}

	void Color::setColor(int red, int green, int blue) {
		this->r = red;
		this->g = green;
		this->b = blue;
	}

	int Color::getR() {
		return r;
	}

	int Color::getG() {
		return g;
	}

	int Color::getB() {
		return b;
	}

	int Color::getAlpha() {
		return alpha;
	}
}
