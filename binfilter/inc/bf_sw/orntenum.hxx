/*************************************************************************
 *
 *  $RCSfile: orntenum.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:53 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/

#ifndef _ORNTENUM_HXX
#define _ORNTENUM_HXX

//SwFmtVertOrient, wie und woran orientiert --
//  sich der FlyFrm in der Vertikalen -----------

enum SwRelationOrient
{
    FRAME,          // Absatz inkl. Raender
    PRTAREA,        // Absatz ohne Raender
    REL_CHAR,       // an einem Zeichen
    REL_PG_LEFT,    // im linken Seitenrand
    REL_PG_RIGHT,   // im rechten Seitenrand
    REL_FRM_LEFT,   // im linken Absatzrand
    REL_FRM_RIGHT,  // im rechten Absatzrand
    REL_PG_FRAME,   // Seite inkl. Raender, bei seitengeb. identisch mit FRAME
    REL_PG_PRTAREA, // Seite ohne Raender, bei seitengeb. identisch mit PRTAREA
    // Wenn neue enums benoetigt werden, muessen die Ausweich-Arrays mitgepflegt
    // werden, LAST_ENUM_DUMMY muss immer das letzte enum bleiben
    LAST_ENUM_DUMMY
};

enum SwVertOrient
{
    VERT_NONE,  //Der Wert in nYPos gibt die RelPos direkt an.
    VERT_TOP,   //Der Rest ist fuer automatische Ausrichtung.
    VERT_CENTER,
    VERT_BOTTOM,
    VERT_CHAR_TOP,      //Ausrichtung _nur_ fuer Zeichengebundene Rahmen
    VERT_CHAR_CENTER,   //wie der Name jew. sagt wird der RefPoint des Rahmens
    VERT_CHAR_BOTTOM,   //entsprechend auf die Oberkante, Mitte oder Unterkante
    VERT_LINE_TOP,      //der Zeile gesetzt. Der Rahmen richtet sich  dann
    VERT_LINE_CENTER,   //entsprechend aus.
    VERT_LINE_BOTTOM
};

#endif
