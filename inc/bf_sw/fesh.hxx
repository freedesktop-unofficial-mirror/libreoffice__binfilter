/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */
#ifndef _FESH_HXX
#define _FESH_HXX

#include <bf_svtools/bf_solar.h>

#include <editsh.hxx>
#include <orntenum.hxx>
#include <flyenum.hxx>

// OD 25.06.2003 #108784#
#include <bf_svx/svdtypes.hxx>

#include <vector>
class Color;
namespace binfilter {

class SvEmbeddedObject;
class SvEmbeddedObjectRef;
class SvInPlaceObject;
class SwFlyFrm;

class SwTabCols;
class SvxBrushItem;
class SwTableAutoFmt;
class SwFrm;
class SwTabFrm;
class SwFmtFrmSize;
class SvxBorderLine;
class SvStorageStream;
class SdrObject;

class Outliner;
class SotDataObject;
class SwFrmFmt;
struct SwSortOptions;
class SdrMarkList;

enum FrmType
{
    //Veroderung.
    FRMTYPE_NONE    = 0,
    FRMTYPE_PAGE    = 1,
    FRMTYPE_HEADER  = 2,
    FRMTYPE_FOOTER  = 4,
    FRMTYPE_BODY    = 8,
    FRMTYPE_COLUMN  = 16,
    FRMTYPE_TABLE   = 32,
    FRMTYPE_FLY_FREE    = 64,
    FRMTYPE_FLY_ATCNT   = 128,
    FRMTYPE_FLY_INCNT   = 256,
    FRMTYPE_FOOTNOTE    = 512,
    FRMTYPE_FTNPAGE     = 1024,
    FRMTYPE_FLY_ANY     = 2048,
    FRMTYPE_DRAWOBJ     = 4096,
    FRMTYPE_COLSECT     = 8192,
    FRMTYPE_COLSECTOUTTAB = 16384
};

#define FRMTYPE_ANYCOLSECT ( FRMTYPE_COLSECT | FRMTYPE_COLSECTOUTTAB )

enum GotoObjType
{
    DRAW_CONTROL = 1,
    DRAW_SIMPLE = 2,
    DRAW_ANY = 3,
    FLY_FRM = 4,
    FLY_GRF = 8,
    FLY_OLE = 16,
    FLY_ANY = 28,
    GOTO_ANY = 31
};

enum FlyProtectType
{
     FLYPROTECT_CONTENT     = 1,        // kann verodert werden!
     FLYPROTECT_SIZE        = 2,
     FLYPROTECT_POS         = 4,
     FLYPROTECT_PARENT      = 8,        // nur Parents untersuchen
     FLYPROTECT_FIXED       = 16        // nur nicht aufhebbarer Schutz
                                        // z.B. durch OLE-Server, gilt auch
                                        // fuer Dialog
};

enum ObjCntType     //Fuer das Ermitteln des Cntnts per Positon (D&D)
{
    OBJCNT_NONE,
    OBJCNT_FLY,
    OBJCNT_GRF,
    OBJCNT_OLE,
    OBJCNT_SIMPLE,
    OBJCNT_CONTROL,
    OBJCNT_URLBUTTON,

    OBJCNT_GROUPOBJ,
    OBJCNT_DONTCARE     // nicht bestimmbar - unterschiedliche Objecte selektiert
};

enum CurRectType
{
    RECT_PAGE,                  //Rect der aktuellen Seite.
    RECT_PAGE_CALC,             //... Seite wird ggf. Formatiert
    RECT_PAGE_PRT,              //Rect der aktuellen PrtArea der Seite
    RECT_FRM,                   //Rect des aktuellen Rahmen
    RECT_FLY_EMBEDDED,          //Rect des aktuellen FlyFrm
    RECT_FLY_PRT_EMBEDDED,      //Rect der PrtArea des FlyFrm
    RECT_SECTION,               //Rect des aktuellen Bereichs
    RECT_OUTTABSECTION,         //Rect des aktuellen Bereichs,
                                // aber ausserhalb der Tabelle
    RECT_SECTION_PRT,           //Rect der aktuellen PrtArea des Bereichs
    RECT_OUTTABSECTION_PRT,     //Rect der aktuellen PrtArea des Bereichs,
                                // aber ausserhalb der Tabelle
    RECT_HEADERFOOTER,          //Rect des aktuellen Headers/Footer
    RECT_HEADERFOOTER_PRT       //Rect der PrtArea des aktuellen Headers/Footers
};

struct SwGetCurColNumPara
{
    const SwFrmFmt* pFrmFmt;
    const SwRect* pPrtRect, *pFrmRect;
    SwGetCurColNumPara() : pFrmFmt( 0 ), pPrtRect( 0 ), pFrmRect( 0 ) {}
};

#define SW_PASTESDR_INSERT      1
#define SW_PASTESDR_REPLACE     2
#define SW_PASTESDR_SETATTR     3

#define SW_ADD_SELECT   1
#define SW_ENTER_GROUP  2
#define SW_LEAVE_FRAME  4

#define SW_MOVE_UP      0
#define SW_MOVE_DOWN    1
#define SW_MOVE_LEFT    2
#define SW_MOVE_RIGHT   3

#define SW_TABCOL_NONE  0
#define SW_TABCOL_HORI  1
#define SW_TABCOL_VERT  2

class SwFEShell : public SwEditShell
{
    BOOL bCheckForOLEInCaption;

public:
    TYPEINFO();
    SwFEShell( SwDoc& rDoc, Window *pWin );
    virtual ~SwFEShell();

    // #107513#
    // Test if there is a draw object at that position and if it should be selected.
    // The 'should' is aimed at Writer text fly frames which may be in front of
    // the draw object.
    sal_Bool ShouldObjectBeSelected(const Point& rPt);

    //Liefert neben der Grafik in rName bei gelinkten Grafiken den Namen mit
    //Pfad und sonst den Grafiknamen. rbLink ist TRU bei gelinkten Grafiken.

    //Der Client fuer das OleObject muss bezueglich der Scalierung auf dem
    //neuesten Stand gehalten werden. Impl in der WrtShell.
    //Wird ein Pointer auf eine Size uebergeben, so ist diese die aktuelle
    //Core-Groesse des Objectes. Anderfalls wird die Groesse per GetCurFlyRect()
    //besorgt.
    virtual void CalcAndSetScale( SvEmbeddedObjectRef xIPObj,
                                  const SwRect *pFlyPrtRect = 0,
                                  const SwRect *pFlyFrmRect = 0 ) = 0;

    //Objekte mit ActivateWhenVisible werden beim Paint Connected.
    //gerufen von notxtfrm::Paint, impl in wrtsh
    virtual void ConnectObj( SvInPlaceObjectRef xIPObj, const SwRect &rPrt,
                             const SwRect &rFrm ) = 0;
};

} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
