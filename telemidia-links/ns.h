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
/* ns.h
 * Javascript namespace
 * (c) 2002 Martin 'PerM' Pergel
 * This file is a part of the Links program, released under GPL
 */

abuf* getarg(abuf**);
void add_to_parlist(lns*,lns*);
void zrusargy(abuf*,js_context*);
void delete_from_parlist(lns*,lns*);
lns* llookup(char*,js_id_name **,plns*,js_context*);
lns* cllookup(char*,js_id_name **,plns*,js_context*);
lns* loklookup(long,plns*,js_context*);
char *key_2_name(long, js_context *);
char* find_var_name(long,js_id_name*);
