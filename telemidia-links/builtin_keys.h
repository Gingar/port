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
/* builtin_keys.h
 * (c) 2002 Martin 'PerM' Pergel
 * This file is a part of the Links program, released under GPL.
 */

/* Funkce */
#define CparseInt 0
#define CparseFloat 1
#define Cescape 2
#define Cunescape 3
#define Cabs 4
#define Cacos 5
#define Casin 6
#define Catan 7
#define Catan2 8
#define Cceil 9
#define Ccos 10
#define Clog 11
#define Cexp 12
#define Cmax 13
#define Cmin 14
#define Cpow 15
#define Crandom 16
#define Cround 17
#define Csin 18
#define Csqrt 19
#define Ctan 20
#define CArray 21
#define CBoolean 22
#define CDate 23
#define CNumber 24
#define CString 25
#define Calert 26
#define Cclear 27
#define Cdclose 28
#define Cdopen 29
#define Cwrite 30
#define Cwriteln 31
#define Cconfirm 32
#define Cwclose 33
#define Cwopen 34
#define Cprompt 35
#define CsetTimeout 36
#define CclearTimeout 37
#define Cback 38
#define Cforward 39
#define Cgo 40 /* Hrajte GO! */
#define CImage 41
#define Ceval 42
#define Cshift 43
#define Cunshift 44
#define Cslice 45
#define Csplice 46
#define CgetElementById 47


#define Cjoin 200
#define Creverse 201
#define Csort 202
#define CIntMETFUN 203
/*#define Ccrclick 204*/
#define Cfocus 205
#define Cblur 206
#define Cselect 207
#define Cclick 208
#define CtoString 209
#define Cfloor 210
#define Cmd5 211
#define Cparse 212
#define CsetDate 213
#define CgetDate 214
#define CsetHours 215
#define CgetHours 216
#define CsetMinutes 217
#define CgetMinutes 218
#define CsetMonth 219
#define CgetMonth 220
#define CsetSeconds 221
#define CgetSeconds 222
#define CsetTime 223
#define CgetTime 224
#define CsetYear 225
#define CgetYear 226
#define CtoGMTString 227
#define CtoLocaleString 228
#define CUTC 229
#define CjavaEnabled 230
#define Clocationreplace 231
#define Csubmitform 232
#define Cresetform 233
#define CisNaN 234

/* Promenne */
#define Cmatika 0
#define Clength 1
#define Cbarvicka 2
/*#define CalinkColor 2*/
#define Canchors 3
/*#define CbgColor 4*/
#define Ccookie 5
/*#define CfgColor 6*/
#define Cforms 7
#define ClastModified 8
/*#define ClinkColor 9*/
#define Clinks 10
#define Clocation 11
#define Creferer 12
#define Ctitle 13
/*#define CvlinkColor 14*/
#define CappCodeName 15
#define CappName 16
#define CappVersion 17
#define CuserAgent 18
#define CdefaultStatus 19
#define Cframes 20
#define Cwlength 21
#define Cname 22
#define Cstatus 25
#define Chash 28
#define Chost 29
#define Chostname 30
#define Chref 31
#define Cpathname 32
#define Cport 33
#define Cprotocol 34
#define Csearch 35
#define Clinkptr 36
#define Ctarget 37
#define Cformptr 38
#define Caction 39
#define Celements 40
#define Cencoding 41
#define Cmethod 42
#define Cftarget 43
#define Ctextptr 44
#define Cpasswdptr 45
#define Ctextarptr 46
#define Cchkboxptr 47
#define Cradioptr 48
#define Cselectptr 49
#define Csubmitptr 50
#define Cresetptr 51
#define Chiddenptr 52
#define Canchorptr 53
#define Cchecked 54
#define CdefaultChecked 55
#define Cfename 56
#define Cvalue 57
#define Cradiolength 58
#define CdefaultValue 59
#define Cselectlength 60
#define Cselectname 61
#define Cselectoptions 62
#define CselectmrchadefaultSelected 63
#define Cselectindex 64
#define CselectselectedIndex 65
#define Cselectmrchatext 66
#define Cselectmrchavalue 67
#define Cselectmrchaselected 68
#define Chistorylength 69
#define Cimages 70
#define Cimageptr 71
#define Csrc 72
#define Cborder 73
#define Ccomplete 74
#define Cheight 75
#define Chspace 76
#define Clowsrc 77
#define Cimagename 78
#define Cvspace 79
#define Cwidth 80
#define Cframeptr 81
#define Csubframes 82
#define Cframeparent 83
#define Cimagealt 84
#define Cbuttonptr 85
#define Cselectmrcha 86
#define Ctop 87
#define Cparent 88
#define Cself 89
#define Call 90
#define Conkeydown 91
#define Conkeypress 92
#define Conkeyup 93

/* Vsechno se udela tak, ze se jen vrati cislicko, ktere se nekde najde */

/* Objektiky */

#define C_OBJ_Objekt 0
#define C_OBJ_document 1
#define C_OBJ_Math 2
#define C_OBJ_window 3
#define C_OBJ_location 4
#define C_OBJ_navigator 5
#define C_OBJ_links 6
#define C_OBJ_forms 7
#define C_OBJ_anchors 8
#define C_OBJ_link 9
#define C_OBJ_form 10
#define C_OBJ_elements 11
#define C_OBJ_radioa 12
#define C_OBJ_text 13
#define C_OBJ_passwd 14
#define C_OBJ_textarea 15
#define C_OBJ_submit 16
#define C_OBJ_reset 17
#define C_OBJ_hidden 18
#define C_OBJ_checkbox 19
#define C_OBJ_radio 20
#define C_OBJ_select 21
#define C_OBJ_images 22
#define C_OBJ_image 23
#define C_OBJ_frame 24
#define C_OBJ_frames 25
#define C_OBJ_button 26

/* Pozor! U toString se zatim neseru s nejakejma midckama !!! */

