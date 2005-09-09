/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: orntenum.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 16:17:12 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/

#ifndef _ORNTENUM_HXX
#define _ORNTENUM_HXX
namespace binfilter {

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

} //namespace binfilter
#endif
