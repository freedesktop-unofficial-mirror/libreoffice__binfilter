/*************************************************************************
 *
 *  $RCSfile: svdtypes.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:43 $
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

#ifndef _SVDTYPES_HXX
#define _SVDTYPES_HXX

#ifndef _SOLAR_H
#include <tools/solar.h>
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
//  @@@@  @@@@@  @@@@@    @@@@  @@@@@  @@@@@@ @@@@@  @@@@  @@@@@@
// @@  @@ @@  @@ @@  @@  @@  @@ @@  @@     @@ @@    @@  @@   @@
// @@     @@  @@ @@  @@  @@  @@ @@  @@     @@ @@    @@       @@
//  @@@@  @@  @@ @@@@@   @@  @@ @@@@@      @@ @@@@  @@       @@
//     @@ @@  @@ @@  @@  @@  @@ @@  @@     @@ @@    @@       @@
// @@  @@ @@  @@ @@  @@  @@  @@ @@  @@ @@  @@ @@    @@  @@   @@
//  @@@@  @@@@@  @@  @@   @@@@  @@@@@   @@@@  @@@@@  @@@@    @@
////////////////////////////////////////////////////////////////////////////////////////////////////

const UINT32 SdrInventor=UINT32('S')*0x00000001+
                         UINT32('V')*0x00000100+
                         UINT32('D')*0x00010000+
                         UINT32('r')*0x01000000;

// Kommandos fuer EndCreate()
enum SdrCreateCmd {SDRCREATE_NEXTPOINT,     // Naechster Polygonpunkt, Kreissegment: Naechste Koordinate
                   SDRCREATE_NEXTOBJECT,    // Naechstes Polygon im PolyPolygon
                   SDRCREATE_FORCEEND};     // Ende erzwungen

enum SdrDragMode
{
    SDRDRAG_MOVE,       // Verschieben
    SDRDRAG_RESIZE,     // Groesse aendern
    SDRDRAG_ROTATE,     // Drehen
    SDRDRAG_MIRROR,     // Spiegeln
    SDRDRAG_SHEAR,      // Schraegstellen
    SDRDRAG_CROOK,      // Kreisfoermig verbiegen
    SDRDRAG_DISTORT,    // Freies verzerren (Rect in beliebiges Viereck transformieren)

    // new modes for interactive transparence and gradient tools
    SDRDRAG_TRANSPARENCE,
    SDRDRAG_GRADIENT
};

// fuer SdrObject::ConvertToPoly()
enum SdrConvertType {SDRCONVERT_POLY,   // reines Polygon erzeugen
                     SDRCONVERT_BEZIER, // alles Beziersegmente
                     SDRCONVERT_MIXED}; // Gemischtes Objekt (optimal)

// fuer SdrObject::TakeContour()
enum SdrContourType {SDRCONTOUR_NORMAL,   // fuer Dragging
                     SDRCONTOUR_ALIGNED,  // fuer Fontwork
                     SDRCONTOUR_DETAILED, // fuer ?
                     SDRCONTOUR_OUTER,    // fuer Writer Kontourfluss
                     SDRCONTOUR_INNER,    // fuer KontourFrames
                     SDRCONTOUR_INNERUNROTATED}; // fuer KontourFrames

////////////////////////////////////////////////////////////////////////////////////////////////////
//  @@     @@@@  @@  @@ @@@@@ @@@@@
//  @@    @@  @@ @@  @@ @@    @@  @@
//  @@    @@  @@ @@  @@ @@    @@  @@
//  @@    @@@@@@  @@@@  @@@@  @@@@@
//  @@    @@  @@   @@   @@    @@  @@
//  @@    @@  @@   @@   @@    @@  @@
//  @@@@@ @@  @@   @@   @@@@@ @@  @@
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
// Bei der Identifikation eines Layer kann es vorkommen, das dieser nicht
// vorhanden ist. SdrLayerAdmin::GetLayerID(const String&) liefert
// dann diesen Wert:
#define SDRLAYER_NOTFOUND 0xFF
// Man kann diesen Wert jodoch ohne Bedenken den Methoden des SdrLayerSet
// zuwerfen, bekommt dann jedoch immer FALSE, bzw. tut die Methode nix.
////////////////////////////////////////////////////////////////////////////////////////////////////
// Typdeklaration fuer Layer-IDs
typedef BYTE SdrLayerID;
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
// @@@@@   @@@@   @@@@  @@@@@         @@@@  @@@@@  @@@@@@ @@    @@  @@@@  @@@@@@
// @@  @@ @@  @@ @@  @@ @@           @@  @@ @@  @@     @@ @@    @@ @@  @@   @@
// @@  @@ @@  @@ @@     @@      @@   @@  @@ @@  @@     @@ @@    @@ @@       @@
// @@@@@  @@@@@@ @@ @@@ @@@@   @@@@  @@  @@ @@@@@      @@ @@    @@  @@@@    @@
// @@     @@  @@ @@  @@ @@      @@   @@  @@ @@  @@     @@ @@    @@     @@   @@
// @@     @@  @@ @@  @@ @@           @@  @@ @@  @@ @@  @@ @@    @@ @@  @@   @@
// @@     @@  @@  @@@@@ @@@@@         @@@@  @@@@@   @@@@  @@@@@ @@  @@@@    @@
////////////////////////////////////////////////////////////////////////////////////////////////////
enum SdrObjListKind {SDROBJLIST_UNKNOWN    =0x00,    // Unbekannt
                     // reine Objektlisten:
                     SDROBJLIST_GROUPOBJ   =0x01,    // Objektliste eines Gruppenobjekts
                     SDROBJLIST_VIRTOBJECTS=0x02,    // Liste ist die Liste der virtuellen Objekte
                     SDROBJLIST_SYMBOLTABLE=0x03,    // Liste ist die Symboltabelle
                     // Hier haben zur Not noch 12 weitere Listentypen Platz
                     // Pages:
                     SDROBJLIST_DRAWPAGE   =0x10,    // Liste ist eine Zeichenseite
                     SDROBJLIST_MASTERPAGE =0x11,    // Liste ist eine Masterpage
                     // Hier haben zur Not noch 8 weitere Pagetypen Platz
                     // Spezialwerte fuer SdrObjSurrogate:
                     SDROBJLIST_SAMELIST   =0x1E,    // Fuer SdrObjSurrogate
                     SDROBJLIST_SAMEPAGE   =0x1F,    // Fuer SdrObjSurrogate
                     SDROBJLIST_RESERVEDBEG=0xE0,    // Die oberen 3 Bits sind ebenfalls
                     SDROBJLIST_RESERVEDEND=0xFF};   // fuer die Surrogate reserviert

inline FASTBOOL SdrIsPageKind(SdrObjListKind eK) { return eK>=SDROBJLIST_DRAWPAGE && eK<=0x1A; }
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
//  @@@@@  @@@@@ @@@@@  @@@@@  @@@@  @@@@@@
//  @@  @@ @@    @@  @@ @@    @@  @@   @@
//  @@  @@ @@    @@  @@ @@    @@  @@   @@
//  @@@@@  @@@@  @@@@@  @@@@  @@@@@@   @@
//  @@  @@ @@    @@     @@    @@  @@   @@
//  @@  @@ @@    @@     @@    @@  @@   @@
//  @@  @@ @@@@@ @@     @@@@@ @@  @@   @@
////////////////////////////////////////////////////////////////////////////////////////////////////

enum SdrRepeatFunc {SDRREPFUNC_OBJ_NONE,
                    // Mit Parameter
                    SDRREPFUNC_OBJ_MOVE,         // Distanz
                    SDRREPFUNC_OBJ_RESIZE,       // Faktor, Referenz(%) bezogen auf MarkRect
                    SDRREPFUNC_OBJ_SETSNAPRECT,  // Rectangle
                    SDRREPFUNC_OBJ_SETLOGICRECT, // Rectangle
                    SDRREPFUNC_OBJ_ROTATE,       // Drehwinkel, Referenz(%) bezogen auf MarkRect
                    SDRREPFUNC_OBJ_SHEAR,        // Winkel,Faktor, Referenz(%) bezogen auf MarkRect
                    SDRREPFUNC_OBJ_CROOKROTATE,
                    SDRREPFUNC_OBJ_CROOKSLANT,
                    SDRREPFUNC_OBJ_CROOKSTRETCH,
                    SDRREPFUNC_OBJ_ALIGN,        // Hor/Vert/bBound
                    SDRREPFUNC_OBJ_SETATTRIBUTES,// ItemSet
                    SDRREPFUNC_OBJ_SETSTYLESHEET,// StyleSheet*
                    // Ohne Parameter
                    SDRREPFUNC_OBJ_DELETE,
                    SDRREPFUNC_OBJ_COMBINE_POLYPOLY,
                    SDRREPFUNC_OBJ_COMBINE_ONEPOLY,
                    SDRREPFUNC_OBJ_DISMANTLE_POLYS,
                    SDRREPFUNC_OBJ_DISMANTLE_LINES,
                    SDRREPFUNC_OBJ_CONVERTTOPOLY,
                    SDRREPFUNC_OBJ_CONVERTTOPATH,
                    SDRREPFUNC_OBJ_GROUP,
                    SDRREPFUNC_OBJ_UNGROUP,
                    SDRREPFUNC_OBJ_PUTTOTOP,
                    SDRREPFUNC_OBJ_PUTTOBTM,
                    SDRREPFUNC_OBJ_MOVTOTOP,
                    SDRREPFUNC_OBJ_MOVTOBTM,
                    SDRREPFUNC_OBJ_REVORDER,
                    SDRREPFUNC_OBJ_IMPORTMTF,
                    SDRREPFUNC_PAGE_DELETE,
                    SDRREPFUNC_LAST};

////////////////////////////////////////////////////////////////////////////////////////////////////

#endif //_SVDTYPES_HXX

