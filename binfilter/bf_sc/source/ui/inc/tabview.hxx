/*************************************************************************
 *
 *  $RCSfile: tabview.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:39:45 $
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

#ifndef SC_TABVIEW_HXX
#define SC_TABVIEW_HXX

#ifndef _SV_SCRBAR_HXX //autogen
#include <vcl/scrbar.hxx>
#endif

#ifndef _SVX_ZOOMITEM_HXX //autogen
#include <bf_svx/zoomitem.hxx>
#endif

#ifndef _IPCLIENT_HXX //autogen
#include <so3/ipclient.hxx>
#endif

#ifndef SO2_DECL_SVINPLACECLIENT_DEFINED
#define SO2_DECL_SVINPLACECLIENT_DEFINED
SO2_DECL_REF(SvInPlaceClient)
#endif

#include "viewutil.hxx"
#include "select.hxx"
class SvBorder;
class Splitter;
namespace binfilter {

class ScEditEngineDefaulter;
class ScGridWindow;
class ScOutlineWindow;
class ScRowBar;
class ScColBar;
class ScTabControl;
class ScTabViewShell;
class SfxPrinter;
class ScDrawView;
class FuPoor;
class ScTabSplitter;
class SdrView;
class SdrObject;
class ScHintWindow;
class ScPageBreakData;
class ScHighlightRanges;
class SchMemChart;
struct ChartSelectionInfo;
class SdrHdlList;

#define SPLIT_HANDLE_SIZE   3
#define SC_FORCEMODE_NONE   0xff

// ---------------------------------------------------------------------------
//      Hilfs - Fenster

class ScCornerButton : public Window
{
private:
    ScViewData*     pViewData;
    BOOL            bAdd;

protected:
//STRIP001  virtual void    Paint( const Rectangle& rRect );
    virtual void    Resize();
//STRIP001  virtual void    MouseButtonDown( const MouseEvent& rMEvt );
public:
                    ScCornerButton( Window* pParent, ScViewData* pData, BOOL bAdditional );
                    ~ScCornerButton();

    virtual void    StateChanged( StateChangedType nType );
//STRIP001  virtual void    DataChanged( const DataChangedEvent& rDCEvt );
};


// ---------------------------------------------------------------------------

class ScTabView
{
private:
    Window*             pFrameWin;              // als erstes !!!
    ScViewData          aViewData;              // muss ganz vorne stehen !

    ScViewSelectionEngine*  pSelEngine;
    ScViewFunctionSet       aFunctionSet;

    ScHeaderSelectionEngine* pHdrSelEng;
    ScHeaderFunctionSet      aHdrFunc;

    SvInPlaceClientRef  aIPClient;

    ScDrawView*         pDrawView;

    Size                aFrameSize;             // wie bei DoResize uebergeben
    Point               aBorderPos;

    BOOL                bDrawSelMode;           // nur Zeichenobjekte selektieren ?

    FuPoor*             pDrawActual;
    FuPoor*             pDrawOld;

    ScGridWindow*       pGridWin[4];
    ScColBar*           pColBar[2];
    ScRowBar*           pRowBar[2];
    ScOutlineWindow*    pColOutline[2];
    ScOutlineWindow*    pRowOutline[2];
    ScTabSplitter*      pHSplitter;
    ScTabSplitter*      pVSplitter;
    ScTabControl*       pTabControl;
    ScrollBar           aVScrollTop;
    ScrollBar           aVScrollBottom;         // anfangs sichtbar
    ScrollBar           aHScrollLeft;           // anfangs sichtbar
    ScrollBar           aHScrollRight;
    ScCornerButton      aCornerButton;
    ScCornerButton      aTopButton;
    ScrollBarBox        aScrollBarBox;

    ScHintWindow*       pInputHintWindow;       // Eingabemeldung bei Gueltigkeit

    ScPageBreakData*    pPageBreakData;         // fuer Seitenumbruch-Modus
    ScHighlightRanges*  pHighlightRanges;

    Timer               aScrollTimer;
    ScGridWindow*       pTimerWindow;
    MouseEvent          aTimerMEvt;

    ULONG               nTipVisible;

    BOOL                bDragging;              // fuer Scrollbars
    long                nPrevDragPos;

    BOOL                bIsBlockMode;           // Block markieren
    BOOL                bBlockNeg;              // wird Markierung aufgehoben?
    BOOL                bBlockCols;             // werden ganze Spalten markiert?
    BOOL                bBlockRows;             // werden ganze Zeilen markiert?
    USHORT              nBlockStartX;
    USHORT              nBlockEndX;
    USHORT              nBlockStartY;
    USHORT              nBlockEndY;
    USHORT              nBlockStartZ;
    USHORT              nBlockEndZ;

    SvxZoomType         eZoomType;
    BOOL                bMinimized;
    BOOL                bInUpdateHeader;
    BOOL                bInActivatePart;
    BOOL                bInZoomUpdate;
    BOOL                bMoveIsShift;
    BOOL                bNewStartIfMarking;


    void            Init();

//STRIP001  void            DoAddWin( ScGridWindow* pWin );

    void            InitScrollBar( ScrollBar& rScrollBar, long nMaxVal );
    DECL_LINK(      ScrollHdl, ScrollBar* );
    DECL_LINK(      EndScrollHdl, ScrollBar* );

    DECL_LINK(      SplitHdl, Splitter* );
//STRIP001  void            DoHSplit(long nSplitPos);
//STRIP001  void            DoVSplit(long nSplitPos);

    DECL_LINK(      TimerHdl, Timer* );

    void            UpdateHeaderWidth( const ScVSplitPos* pWhich = NULL,
                                        const USHORT* pPosY = NULL );
    void            UpdateVarZoom();

protected:
//STRIP001  void            HideTip();
//STRIP001  void            ShowRefTip();

    void            ZoomChanged();
    void            UpdateShow();
    void            GetBorderSize( SvBorder& rBorder, const Size& rSize );

//STRIP001  void            ResetDrawDragMode();
//STRIP001  BOOL            IsDrawTextEdit() const;
    void            DrawEnableAnim(BOOL bSet);
//STRIP001  void            DrawShowMarkHdl(BOOL bShow);

    void            MakeDrawView( BYTE nForceDesignMode = SC_FORCEMODE_NONE );

    void            HideNoteMarker();

//STRIP001  void            UpdateIMap( SdrObject* pObj );

public:
                    ScTabView( Window* pParent, ScDocShell& rDocSh, ScTabViewShell* pViewShell );
                     ScTabView( Window* pParent, const ScTabView& rScTabView, ScTabViewShell* pViewShell );
                    ~ScTabView();

//STRIP001  void            MakeDrawLayer();

    void            HideListBox();

//STRIP001  BOOL            HasHintWindow() const   { return pInputHintWindow != NULL; }
//STRIP001  void            RemoveHintWindow();
    void            TestHintWindow();


    DECL_LINK(      TabBarResize, void* );
//STRIP001  void            SetTabBarWidth( long nNewWidth );
    long            GetTabBarWidth();

    void            DoResize( const Point& rOffset, const Size& rSize, BOOL bInner = FALSE );
    void            RepeatResize( BOOL bUpdateFix = TRUE );
    void            UpdateFixPos();
//STRIP001  Point           GetGridOffset() const;

    BOOL            IsDrawSelMode() const       { return bDrawSelMode; }
    void            SetDrawSelMode(BOOL bNew)   { bDrawSelMode = bNew; }

    void            SetDrawFuncPtr(FuPoor* pFuncPtr)    { pDrawActual = pFuncPtr; }
    void            SetDrawFuncOldPtr(FuPoor* pFuncPtr) { pDrawOld = pFuncPtr; }
    FuPoor*         GetDrawFuncPtr()                    { return pDrawActual; }
    FuPoor*         GetDrawFuncOldPtr()                 { return pDrawOld; }

//STRIP001  void            DrawDeselectAll();
//STRIP001  void            DrawMarkListHasChanged();
//STRIP001  void            UpdateAnchorHandles();
//STRIP001  String          GetSelectedChartName() const;

    ScPageBreakData* GetPageBreakData()     { return pPageBreakData; }
    ScHighlightRanges* GetHighlightRanges() { return pHighlightRanges; }

//STRIP001  void            UpdatePageBreakData( BOOL bForcePaint = FALSE );

//STRIP001  void            DrawMarkRect( const Rectangle& rRect );

    ScViewData*         GetViewData()       { return &aViewData; }
    const ScViewData*   GetViewData() const { return &aViewData; }

    ScViewFunctionSet*      GetFunctionSet()    { return &aFunctionSet; }
    ScViewSelectionEngine*  GetSelEngine()      { return pSelEngine; }

//STRIP001  BOOL            SelMouseButtonDown( const MouseEvent& rMEvt );

    ScDrawView*     GetScDrawView()         { return pDrawView; }
    SdrView*        GetSdrView();           // gegen CLOKs

    BOOL            IsMinimized() const     { return bMinimized; }

//STRIP001  void            TabChanged();
    void            SetZoom( const Fraction& rNewX, const Fraction& rNewY );
//STRIP001  void            SetPagebreakMode( BOOL bSet );

    void            UpdateLayerLocks();

//STRIP001  void            UpdateDrawTextOutliner();
//STRIP001  void            DigitLanguageChanged();

    void            UpdateInputLine();

//STRIP001  void            InitRefMode( USHORT nCurX, USHORT nCurY, USHORT nCurZ, ScRefType eType,
//STRIP001                                  BOOL bPaint = TRUE );
//STRIP001  void            DoneRefMode( BOOL bContinue = FALSE );
//STRIP001  void            UpdateRef( USHORT nCurX, USHORT nCurY, USHORT nCurZ );
//STRIP001  void            StopRefMode();

//STRIP001  void            EndSelection();
    void            StopMarking();
//STRIP001  void            FakeButtonUp( ScSplitPos eWhich );

    Window*         GetActiveWin();
    Window*         GetWindowByPos( ScSplitPos ePos );

//STRIP001  ScSplitPos      FindWindow( Window* pWindow ) const;

//STRIP001  void            SetActivePointer( const Pointer& rPointer );
//STRIP001  void            SetActivePointer( const ResId& rId );

//STRIP001  void            ActiveGrabFocus();
//STRIP001  void            ActiveCaptureMouse();
//STRIP001  void            ActiveReleaseMouse();
//STRIP001  Point           ActivePixelToLogic( const Point& rDevicePoint );

//STRIP001  void            ClickCursor( USHORT nPosX, USHORT nPosY, BOOL bControl );

    void            SetCursor( USHORT nPosX, USHORT nPosY, BOOL bNew = FALSE );

//STRIP001  void            CellContentChanged();
//STRIP001  void            SelectionChanged();
//STRIP001  void            CursorPosChanged();
//STRIP001  void            UpdateInputContext();

    void            CheckSelectionTransfer();

//STRIP001  void            InvertHorizontal( ScVSplitPos eWhich, long nDragPos );
//STRIP001  void            InvertVertical( ScHSplitPos eWhich, long nDragPos );

//STRIP001  Point           GetInsertPos();

    void            UpdateAutoFillMark();

//STRIP001  void            HideCursor();               // nur aktiver Teil
//STRIP001  void            ShowCursor();
//STRIP001  void            HideAllCursors();
//STRIP001  void            ShowAllCursors();

    void            AlignToCursor( short nCurX, short nCurY, ScFollowMode eMode,
                                    const ScSplitPos* pWhich = NULL );

    SvxZoomType     GetZoomType() const             { return eZoomType; }
    void            SetZoomType( SvxZoomType eNew ) { eZoomType = eNew; }
    USHORT          CalcZoom( SvxZoomType eType, USHORT nOldZoom ){DBG_BF_ASSERT(0, "STRIP"); return 0; } //STRIP001 USHORT         CalcZoom( SvxZoomType eType, USHORT nOldZoom );

//  void            CalcZoom( SvxZoomType eType, USHORT& rZoom, USHORT& rCol, USHORT& rRow );

//STRIP001  void            StartDataSelect();

                    //  MoveCursorAbs       - absolut
                    //  MoveCursorRel       - einzelne Zellen
                    //  MoveCursorPage      - Bildschirmseite
                    //  MoveCursorArea      - Datenblock
                    //  MoveCursorEnd       - links oben / benutzter Bereich

//STRIP001  void            MoveCursorAbs( short nCurX, short nCurY, ScFollowMode eMode,
//STRIP001                                  BOOL bShift, BOOL bControl,
//STRIP001                                  BOOL bKeepOld = FALSE, BOOL bKeepSel = FALSE );
//STRIP001  void            MoveCursorRel( short nMovX, short nMovY, ScFollowMode eMode,
//STRIP001                                  BOOL bShift, BOOL bKeepSel = FALSE );
//STRIP001  void            MoveCursorPage( short nMovX, short nMovY, ScFollowMode eMode,
//STRIP001                                  BOOL bShift, BOOL bKeepSel = FALSE );
//STRIP001  void            MoveCursorArea( short nMovX, short nMovY, ScFollowMode eMode,
//STRIP001                                  BOOL bShift, BOOL bKeepSel = FALSE );
//STRIP001  void            MoveCursorEnd( short nMovX, short nMovY, ScFollowMode eMode,
//STRIP001                                  BOOL bShift, BOOL bKeepSel = FALSE );
//STRIP001  void            MoveCursorScreen( short nMovX, short nMovY, ScFollowMode eMode, BOOL bShift );

//STRIP001  void            MoveCursorEnter( BOOL bShift );     // Shift fuer Richtung (kein Markieren)

//STRIP001     BOOL            MoveCursorKeyInput( const KeyEvent& rKeyEvent );

//STRIP001  void            FindNextUnprot( BOOL bShift, BOOL bInSelection = TRUE );

    void            SetNewStartIfMarking();

    void            SetTabNo( USHORT nTab, BOOL bNew = FALSE );
//STRIP001  void            SelectNextTab( short nDir );

//STRIP001  void            ActivateView( BOOL bActivate, BOOL bFirst );
//STRIP001  void            ActivatePart( ScSplitPos eWhich );
    BOOL            IsInActivatePart() const    { return bInActivatePart; }

//STRIP001  void            SetTimer( ScGridWindow* pWin, const MouseEvent& rMEvt );
//STRIP001  void            ResetTimer();

    void            ScrollX( long nDeltaX, ScHSplitPos eWhich, BOOL bUpdBars = TRUE );
    void            ScrollY( long nDeltaY, ScVSplitPos eWhich, BOOL bUpdBars = TRUE );
//STRIP001  void            ScrollLines( long nDeltaX, long nDeltaY );              // aktives

//STRIP001  BOOL            ScrollCommand( const CommandEvent& rCEvt, ScSplitPos ePos );

    void            ScrollToObject( SdrObject* pDrawObj );
//STRIP001  void            MakeVisible( const Rectangle& rHMMRect );

                                    // Zeichnen

//STRIP001  void            InvertBlockMark(USHORT nBlockStartX, USHORT nBlockStartY,
//STRIP001                              USHORT nBlockEndX, USHORT nBlockEndY);

//STRIP001  void            DrawDragRect( USHORT nStartX, USHORT nStartY, USHORT nEndX, USHORT nEndY,
//STRIP001                                  ScSplitPos ePos );

//STRIP001  void            PaintCell( USHORT nCol, USHORT nRow, USHORT nTab );
    void            PaintArea( USHORT nStartCol, USHORT nStartRow, USHORT nEndCol, USHORT nEndRow,
                                        ScUpdateMode eMode = SC_UPDATE_ALL );

    void            PaintGrid();

    void            PaintTopCol( USHORT nCol );
    void            PaintTopArea( USHORT nStartCol, USHORT nEndCol );
    void            PaintTop();

//STRIP001  void            PaintLeftRow( USHORT nRow );
    void            PaintLeftArea( USHORT nStartRow, USHORT nEndRow );
    void            PaintLeft();

    BOOL            PaintExtras();

//STRIP001  void            RecalcPPT();

//STRIP001  void            CreateAnchorHandles(SdrHdlList& rHdl, const ScAddress& rAddress);

    void            UpdateFormulas();
    void            InterpretVisible();
//STRIP001  void            CheckNeedsRepaint();

//STRIP001  void            PaintRangeFinder( long nNumber = -1 );
//STRIP001  void            AddHighlightRange( const ScRange& rRange, const Color& rColor );
//STRIP001  void            ClearHighlightRanges();

//STRIP001  long            DoChartSelection( ChartSelectionInfo &rInfo, const SchMemChart& rMemChart );

    long            GetGridWidth( ScHSplitPos eWhich );
    long            GetGridHeight( ScVSplitPos eWhich );

    void            UpdateScrollBars();
    void            SetNewVisArea();

//STRIP001  void            InvalidateAttribs();

//STRIP001  void            MakeEditView( ScEditEngineDefaulter* pEngine, USHORT nCol, USHORT nRow );
    void            KillEditView( BOOL bNoPaint );
//STRIP001  void            UpdateEditView();


                                    //  Bloecke

//STRIP001  void            SelectAll( BOOL bContinue = FALSE );
//STRIP001  void            SelectAllTables();

//STRIP001  void            MarkCursor( USHORT nCurX, USHORT nCurY, USHORT nCurZ,
//STRIP001                                  BOOL bCols = FALSE, BOOL bRows = FALSE );
//STRIP001  void            InitBlockMode( USHORT nCurX, USHORT nCurY, USHORT nCurZ,
//STRIP001                                  BOOL bTestNeg = FALSE,
//STRIP001                                  BOOL bCols = FALSE, BOOL bRows = FALSE );
    void            InitOwnBlockMode();
    void            DoneBlockMode( BOOL bContinue = FALSE );

    BOOL            IsBlockMode() const     { return bIsBlockMode; }

//STRIP001  void            MarkColumns();
//STRIP001  void            MarkRows();
//STRIP001  void            MarkDataArea( BOOL bIncludeCursor = TRUE );
    void            MarkMatrixFormula();
    void            Unmark();

    void            MarkRange( const ScRange& rRange, BOOL bSetCursor = TRUE, BOOL bContinue = FALSE );

//STRIP001  BOOL            IsMarking( USHORT nCol, USHORT nRow, USHORT nTab ) const;

//STRIP001  void            PaintMarks( USHORT nStartCol, USHORT nStartRow, USHORT nEndCol, USHORT nEndRow );
//STRIP001  void            PaintBlock( BOOL bReset = FALSE );

//STRIP001  void            LockModifiers( USHORT nModifiers );
    USHORT          GetLockedModifiers() const;
    void            ViewOptionsHasChanged( BOOL bHScrollChanged,
                                            BOOL bGraphicsChanged = FALSE);

//STRIP001  Point           GetMousePosPixel();

//STRIP001  void            SnapSplitPos( Point& rScreenPosPixel );
    void            FreezeSplitters( BOOL bFreeze );
    void            RemoveSplit();
//STRIP001  void            SplitAtCursor();
    void            SplitAtPixel( const Point& rPixel, BOOL bHor, BOOL bVer );
    void            InvalidateSplit();

    void            ErrorMessage( USHORT nGlobStrId );
//STRIP001  Window*         GetParentOrChild( USHORT nChildId );

//STRIP001  void            EnableRefInput(BOOL bFlag=TRUE);

    Window*         GetFrameWin() const { return pFrameWin; }
};



} //namespace binfilter
#endif

