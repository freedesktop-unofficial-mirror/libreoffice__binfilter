/*************************************************************************
 *
 *  $RCSfile: ruler.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:37 $
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
#ifndef _SVX_RULER_HXX
#define _SVX_RULER_HXX

#ifndef _SV_MENU_HXX //autogen
#include <vcl/menu.hxx>
#endif

#ifndef _RULER_HXX //autogen
#include <svtools/ruler.hxx>
#endif

#ifndef _SFXLSTNER_HXX //autogen
#include <svtools/lstner.hxx>
#endif

class SvxProtectItem;
class SvxRulerItem;
class SfxBindings;
class SvxLongLRSpaceItem;
class SvxLongULSpaceItem;
class SvxTabStopItem;
class SvxLRSpaceItem;
class SvxPagePosSizeItem;
class SvxColumnItem;
class SfxRectangleItem;
class SvxObjectItem;
class SfxBoolItem;
struct SvxRuler_Impl;

class SvxRuler: public Ruler, public SfxListener
{
friend class SvxRulerItem;
    SvxRulerItem **pCtrlItem;
    SvxLongLRSpaceItem *pLRSpaceItem;  //Linker und Rechter Rand
    SfxRectangleItem *pMinMaxItem; //Maxima fuers Draggen
    SvxLongULSpaceItem *pULSpaceItem;  //Oberer und Unterer Rand
    SvxTabStopItem *pTabStopItem;  //Tabstops
    SvxLRSpaceItem *pParaItem;     //Absaetze
    SvxLRSpaceItem *pParaBorderItem; //Border distance
    SvxPagePosSizeItem *pPagePosItem; //Seitenabstaende zum Lineal
    SvxColumnItem *pColumnItem;    //Spalten
    SvxObjectItem *pObjectItem;    //Objekt
    Window *pEditWin;
    SvxRuler_Impl *pRuler_Imp;
    BOOL bAppSetNullOffset :1;
    BOOL bHorz :1;
    long lLogicNullOffset;      // in logischen Koordinaten
    long lAppNullOffset;        // in logischen Koordinaten
    long lMinFrame;             // minimale Framebreite in Pixel
    long lInitialDragPos;
    USHORT nFlags;
    enum {
        NONE = 0x0000,
        DRAG_OBJECT =  0x0001,
        // letzte Spalte verkleinern, Shift
        DRAG_OBJECT_SIZE_LINEAR = 0x0002,
        DRAG_OBJECT_SIZE_PROPORTIONAL = 0x0004, // proportional, Ctrl
        // nur aktuelle Zeile (Tabelle; Shift-Ctrl)
        DRAG_OBJECT_ACTLINE_ONLY = 0x0008,
        // aktuell gleiche Tastenbelegung
        DRAG_OBJECT_LEFT_INDENT_ONLY = DRAG_OBJECT_SIZE_PROPORTIONAL
        }
    nDragType;
    USHORT nDefTabType;
    USHORT nTabCount;
    USHORT nTabBufSize;
    long lDefTabDist;
    long lTabPos;
    RulerTab *pTabs;            // Tabpositionen in Pixel
    RulerIndent *pIndents;      // Absatzraender in Pixel
    RulerBorder *pBorders;
    USHORT nBorderCount;
    RulerBorder *pObjectBorders;
    SfxBindings *pBindings;
    long nDragOffset;
    long nMaxLeft;
    long nMaxRight;
    BOOL bValid;
    BOOL bListening;
    BOOL bActive;
#if _SOLAR__PRIVATE
    void StartListening_Impl();
//STRIP001  long GetCorrectedDragPos( BOOL bLeft = TRUE, BOOL bRight = TRUE );
//STRIP001  void DrawLine_Impl(long &lTabPos, int, BOOL Hori=TRUE);
//STRIP001  USHORT GetObjectBordersOff(USHORT nIdx) const;

    // Seitenr"ander oder umgebender Rahmen
    void UpdateFrame(const SvxLongLRSpaceItem *);
    void UpdateFrame(const SvxLongULSpaceItem *);
    void UpdateFrameMinMax(const SfxRectangleItem *);
    // Absatzeinzuege
    void UpdatePara(const SvxLRSpaceItem *);
    // Border distance
    void UpdateParaBorder(const SvxLRSpaceItem *);
    // Tabs
    void Update(const SvxTabStopItem *);
    // Seitenposition und -breite
    void Update(const SvxPagePosSizeItem *);
    // Spalten
    void Update(const SvxColumnItem *);
    // Object Selektion
//STRIP001  void Update(const SvxObjectItem *);
    // Protect
    void Update( const SvxProtectItem* );
    // left-to-right text
    void UpdateTextRTL( const SfxBoolItem* );
    // Absatzeinzuege
    void UpdatePara();
    void UpdateTabs();
    void UpdatePage();
    void UpdateFrame();
    void UpdateColumns();
//STRIP001  void UpdateObject();

//STRIP001  long PixelHAdjust(long lPos, long lPos2) const;
//STRIP001  long PixelVAdjust(long lPos, long lPos2) const;
//STRIP001  long PixelAdjust(long lPos, long lPos2) const;

    long ConvertHPosPixel(long lPos) const;
    long ConvertVPosPixel(long lPos) const;
    long ConvertHSizePixel(long lSize) const;
    long ConvertVSizePixel(long lSize) const;

    long ConvertPosPixel(long lPos) const;
    long ConvertSizePixel(long lSize) const;

//STRIP001  long ConvertHPosLogic(long lPos) const;
//STRIP001  long ConvertVPosLogic(long lPos) const;
//STRIP001  long ConvertHSizeLogic(long lSize) const;
//STRIP001  long ConvertVSizeLogic(long lSize) const;

//STRIP001  long ConvertPosLogic(long lPos) const;
//STRIP001  long ConvertSizeLogic(long lSize) const;

//STRIP001  long GetFirstLineIndent() const;
//  long GetLogicFirstLineIndent() const;
//STRIP001  long GetLeftIndent() const;
//  long GetLogicLeftIndent() const;
//STRIP001  long GetRightIndent() const;
//STRIP001  long GetLogicRightIndent() const;
//STRIP001  long GetPageWidth() const;

    inline long GetLeftFrameMargin() const;
    long GetRightFrameMargin() const;

//STRIP001  void CalcMinMax();

//STRIP001  void EvalModifier();
//STRIP001  void DragMargin1();
//STRIP001  void DragMargin2();
//STRIP001  void DragIndents();
//STRIP001  void DragTabs();
//STRIP001  void DragBorders();
//STRIP001  void DragObjectBorder();

//STRIP001  void ApplyMargins();
//STRIP001  void ApplyIndents();
//STRIP001  void ApplyTabs();
//STRIP001  void ApplyBorders();
//STRIP001  void ApplyObject();

//STRIP001  long GetFrameLeft() const;
//STRIP001  void SetFrameLeft(long);

//STRIP001  long GetLeftMin() const;
//STRIP001  long GetRightMax() const;

//STRIP001  DECL_LINK( TabMenuSelect, Menu * );
//STRIP001  DECL_LINK( MenuSelect, Menu * );
//STRIP001  void PrepareProportional_Impl(RulerType);

//STRIP001  USHORT GetNextVisible(USHORT nColumn);
//STRIP001  USHORT GetPrevVisible(USHORT nColumn);
#endif

    void Update();

enum UpdateType {
    MOVE_ALL,
    MOVE_LEFT,
    MOVE_RIGHT
    };
//STRIP001  void UpdateParaContents_Impl(long lDiff, UpdateType = MOVE_ALL);
protected:
//STRIP001  virtual void    Command( const CommandEvent& rCEvt );
//STRIP001  virtual void    Click();
//STRIP001  virtual long    StartDrag();
//STRIP001  virtual void    Drag();
//STRIP001  virtual void    EndDrag();
//STRIP001  virtual void    ExtraDown();
    virtual void    MouseMove( const MouseEvent& rMEvt );

    virtual void SFX_NOTIFY( SfxBroadcaster& rBC, const TypeId& rBCType,
                         const SfxHint& rHint, const TypeId& rHintType );

    // Berechnung der Grenzwerte fuer Objectgrenzen
    // Werte sind bezogen auf die Seite
//STRIP001  virtual BOOL    CalcLimits(long &nMax1, long &nMax2, BOOL bFirst) const;
    BOOL IsActLastColumn(
        BOOL bForceDontConsiderHidden = FALSE, USHORT nAct=USHRT_MAX) const ;
//STRIP001  BOOL IsActFirstColumn(
//STRIP001      BOOL bForceDontConsiderHidden = FALSE, USHORT nAct=USHRT_MAX) const;
//STRIP001  USHORT GetActLeftColumn(
//STRIP001      BOOL bForceDontConsiderHidden = FALSE, USHORT nAct=USHRT_MAX ) const;
//STRIP001  USHORT GetActRightColumn (
//STRIP001      BOOL bForceDontConsiderHidden = FALSE, USHORT nAct=USHRT_MAX ) const;
//STRIP001  long CalcPropMaxRight(USHORT nCol=USHRT_MAX) const;

public:
#define     SVXRULER_SUPPORT_TABS                       0x0001
#define     SVXRULER_SUPPORT_PARAGRAPH_MARGINS          0x0002
#define     SVXRULER_SUPPORT_BORDERS                    0x0004
#define     SVXRULER_SUPPORT_OBJECT                     0x0008
#define     SVXRULER_SUPPORT_SET_NULLOFFSET             0x0010
#define     SVXRULER_SUPPORT_NEGATIVE_MARGINS           0x0020
#define     SVXRULER_SUPPORT_PARAGRAPH_MARGINS_VERTICAL 0x0040

    SvxRuler(Window* pParent,
             Window *pEditWin,
             USHORT nRulerFlags,
             SfxBindings &rBindings,
             WinBits nWinStyle = WB_STDRULER);
    ~SvxRuler();

//STRIP001  void SetMinFrameSize(long lSize);
//STRIP001  long GetMinFrameSize() const ;

//STRIP001  USHORT GetRulerFlags() const { return nFlags; }

    void SetDefTabDist(long);
//STRIP001  long GetDefTabDist() const;

    // Setzen / Erfragen NullOffset in logischen Einheiten
//STRIP001  void SetNullOffsetLogic(long lOff = 0);
//STRIP001  long GetNullOffsetLogic() const { return lAppNullOffset; }

    void SetActive(BOOL bOn = TRUE);
//STRIP001  BOOL IsActive() const { return bActive; }

    void ForceUpdate() { Update(); }
};

#endif

