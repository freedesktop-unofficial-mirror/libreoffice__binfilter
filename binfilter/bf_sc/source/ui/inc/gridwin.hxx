/*************************************************************************
 *
 *  $RCSfile: gridwin.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:29:50 $
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

#ifndef SC_GRIDWIN_HXX
#define SC_GRIDWIN_HXX

#ifndef _STRING_HXX //autogen
#include <tools/string.hxx>
#endif

#ifndef _TRANSFER_HXX
#include <svtools/transfer.hxx>
#endif

// nur auf dem MAC Auto-Filter per Popup
#ifdef MAC
#define AUTOFILTER_POPUP
#else
#undef AUTOFILTER_POPUP
#endif

#ifndef SC_VIEWUTIL_HXX
#include "viewutil.hxx"
#endif

#ifndef SC_VIEWDATA_HXX
#include "viewdata.hxx"
#endif

#ifndef SC_CBUTTON_HXX
#include "cbutton.hxx"
#endif
class FloatingWindow;
namespace binfilter {

// ---------------------------------------------------------------------------

struct RowInfo;
class ScViewSelectionEngine;
class ScPivot;
class ScDPObject;
class ScOutputData;
class ScFilterListBox;
class AutoFilterPopup;
class SdrObject;
class SdrEditView;
class ScNoteMarker;
class SdrHdlList;
class ScTransferObj;

        //  Maus-Status (nMouseStatus)

#define SC_GM_NONE          0
#define SC_GM_TABDOWN       1
#define SC_GM_DBLDOWN       2
#define SC_GM_FILTER        3
#define SC_GM_IGNORE        4
#define SC_GM_WATERUNDO     5
#define SC_GM_URLDOWN       6

        //  Page-Drag-Modus

#define SC_PD_NONE          0
#define SC_PD_RANGE_L       1
#define SC_PD_RANGE_R       2
#define SC_PD_RANGE_T       4
#define SC_PD_RANGE_B       8
#define SC_PD_RANGE_TL      (SC_PD_RANGE_T|SC_PD_RANGE_L)
#define SC_PD_RANGE_TR      (SC_PD_RANGE_T|SC_PD_RANGE_R)
#define SC_PD_RANGE_BL      (SC_PD_RANGE_B|SC_PD_RANGE_L)
#define SC_PD_RANGE_BR      (SC_PD_RANGE_B|SC_PD_RANGE_R)
#define SC_PD_BREAK_H       16
#define SC_PD_BREAK_V       32


//STRIP001 class ScHideTextCursor
//STRIP001 {
//STRIP001 private:
//STRIP001  ScViewData* pViewData;
//STRIP001  ScSplitPos  eWhich;
//STRIP001
//STRIP001 public:
//STRIP001          ScHideTextCursor( ScViewData* pData, ScSplitPos eW );
//STRIP001          ~ScHideTextCursor();
//STRIP001 };


class ScGridWindow : public Window, public DropTargetHelper, public DragSourceHelper
{
    //  ScFilterListBox wird immer fuer Auswahlliste benutzt
    friend class ScFilterListBox;
#ifdef AUTOFILTER_POPUP
    friend class AutoFilterPopup;
#endif

private:
    ScViewData*             pViewData;
    ScSplitPos              eWhich;
    ScHSplitPos             eHWhich;
    ScVSplitPos             eVWhich;

    ScNoteMarker*           pNoteMarker;

    ScFilterListBox*        pFilterBox;
    USHORT                  nFilterBoxCol;
    USHORT                  nFilterBoxRow;
    FloatingWindow*         pFilterFloat;

    USHORT                  nCursorHideCount;

    BOOL                    bMarking;

    USHORT                  nButtonDown;
    BOOL                    bEEMouse;               // Edit-Engine hat Maus
    BYTE                    nMouseStatus;

    BOOL                    bPivotMouse;            // Pivot-D&D (alte Pivottabellen)
    ScPivot*                pDragPivot;
    BOOL                    bPivotColField;
    USHORT                  nPivotCol;
    USHORT                  nPivotField;

    BOOL                    bDPMouse;               // DataPilot-D&D (neue Pivottabellen)
    long                    nDPField;
    ScDPObject*             pDragDPObj; //! name?

    BOOL                    bRFMouse;               // RangeFinder-Drag
    BOOL                    bRFSize;
    USHORT                  nRFIndex;
    short                   nRFAddX;
    short                   nRFAddY;

    USHORT                  nPagebreakMouse;        // Pagebreak-Modus Drag
    USHORT                  nPagebreakBreak;
    USHORT                  nPagebreakPrev;
    ScRange                 aPagebreakSource;
    ScRange                 aPagebreakDrag;
    BOOL                    bPagebreakDrawn;

    BYTE                    nPageScript;

    long                    nLastClickX;
    long                    nLastClickY;

    BOOL                    bDragRect;
    USHORT                  nDragStartX;
    USHORT                  nDragStartY;
    USHORT                  nDragEndX;
    USHORT                  nDragEndY;

    USHORT                  nCurrentPointer;

    BOOL                    bIsInScroll;
    BOOL                    bIsInPaint;

    ScDDComboBoxButton      aComboButton;

    Point                   aCurMousePos;

    USHORT                  nPaintCount;
    Rectangle               aRepaintPixel;
    BOOL                    bNeedsRepaint;

    BOOL                    bAutoMarkVisible;
    ScAddress               aAutoMarkPos;

    Rectangle               aInvertRect;

//STRIP001  DECL_LINK( PopupModeEndHdl, FloatingWindow* );

//STRIP001  BOOL            TestMouse( const MouseEvent& rMEvt, BOOL bAction );

//STRIP001  void            DoPushButton( USHORT nCol, USHORT nRow, const MouseEvent& rMEvt );
//STRIP001  void            PivotMouseMove( const MouseEvent& rMEvt );
//STRIP001  void            PivotMouseButtonUp( const MouseEvent& rMEvt );
//STRIP001  BOOL            PivotTestMouse( const MouseEvent& rMEvt, BOOL bMove );
//STRIP001  void            DoPivotDrop( BOOL bDelete, BOOL bToCols, short nDestPos );

//STRIP001  void            DPMouseMove( const MouseEvent& rMEvt );
//STRIP001  void            DPMouseButtonUp( const MouseEvent& rMEvt );
//STRIP001  void            DPTestMouse( const MouseEvent& rMEvt, BOOL bMove );

//STRIP001  void            RFMouseMove( const MouseEvent& rMEvt, BOOL bUp );

//STRIP001  void            PagebreakMove( const MouseEvent& rMEvt, BOOL bUp );

//STRIP001  void            UpdateDragRect( BOOL bShowRange, const Rectangle& rPosRect );

//STRIP001  BOOL            IsAutoFilterActive( USHORT nCol, USHORT nRow, USHORT nTab );
//STRIP001  void            ExecFilter( ULONG nSel, USHORT nCol, USHORT nRow,
//STRIP001                              const String& aValue );
//STRIP001  void            FilterSelect( ULONG nSel );

//STRIP001  void            ExecDataSelect( USHORT nCol, USHORT nRow, const String& rStr );

//STRIP001  BOOL            HasScenarioButton( const Point& rPosPixel, ScRange& rScenRange );

//STRIP001  BOOL            DropScroll( const Point& rMousePos );

//STRIP001  sal_Int8        AcceptPrivateDrop( const AcceptDropEvent& rEvt );
//STRIP001  sal_Int8        ExecutePrivateDrop( const ExecuteDropEvent& rEvt );
//STRIP001  sal_Int8        DropTransferObj( ScTransferObj* pTransObj, USHORT nDestPosX, USHORT nDestPosY,
//STRIP001                                  const Point& rLogicPos, sal_Int8 nDndAction );

//STRIP001  BOOL            DrawMouseButtonDown(const MouseEvent& rMEvt);
//STRIP001  BOOL            DrawMouseButtonUp(const MouseEvent& rMEvt);
//STRIP001  BOOL            DrawMouseMove(const MouseEvent& rMEvt);
//STRIP001  BOOL            DrawKeyInput(const KeyEvent& rKEvt);
//STRIP001  BOOL            DrawCommand(const CommandEvent& rCEvt);
//STRIP001  BOOL            DrawHasMarkedObj();
    void            DrawEndAction();
//STRIP001  void            DrawMarkDropObj( SdrObject* pObj );
    SdrObject*      GetEditObject();
//STRIP001  BOOL            IsMyModel(SdrEditView* pSdrView);
    void            DrawStartTimer();

    void            DrawRedraw( ScOutputData& rOutputData, const Rectangle& rDrawingRect,
                                        ScUpdateMode eMode, ULONG nLayer );
    void            DrawSdrGrid( const Rectangle& rDrawingRect );
//STRIP001  BOOL            DrawBeforeScroll();
//STRIP001  void            DrawAfterScroll(BOOL bVal);
//STRIP001  void            OutlinerViewPaint( const Rectangle& rRect );
    void            DrawMarks();
    BOOL            NeedDrawMarks();
//STRIP001  void            DrawComboButton( const Point&   rCellPos,
//STRIP001                                   long           nCellSizeX,
//STRIP001                                   long           nCellSizeY,
//STRIP001                                      BOOL           bArrowState,
//STRIP001                                   BOOL           bBtnIn  = FALSE );

//STRIP001  void            DrawPagePreview( USHORT nX1, USHORT nY1, USHORT nX2, USHORT nY2 );

//STRIP001  BOOL            GetEditUrl( const Point& rPos,
//STRIP001                              String* pName=0, String* pUrl=0, String* pTarget=0 );
//STRIP001  BOOL            GetEditUrlOrError( BOOL bSpellErr, const Point& rPos,
//STRIP001                              String* pName=0, String* pUrl=0, String* pTarget=0 );

//STRIP001  BOOL            HitRangeFinder( const Point& rMouse, BOOL& rCorner, USHORT* pIndex = NULL,
//STRIP001                                      short* pAddX = NULL, short* pAddY = NULL );

//STRIP001  USHORT          HitPageBreak( const Point& rMouse, ScRange* pSource = NULL,
//STRIP001                                  USHORT* pBreak = NULL, USHORT* pPrev = NULL );

#ifdef AUTOFILTER_POPUP
//STRIP001  void            DoAutoFilterPopup( USHORT nCol, USHORT nRow, BOOL bDataSelect );
#endif

//STRIP001  void            PasteSelection( const Point& rPosPixel );

protected:
//STRIP001  virtual void    Resize( const Size& rSize );
//STRIP001  virtual void    Paint( const Rectangle& rRect );
//STRIP001  virtual void    KeyInput(const KeyEvent& rKEvt);
//STRIP001  virtual void    GetFocus();
//STRIP001  virtual void    LoseFocus();

//STRIP001  virtual void    RequestHelp( const HelpEvent& rEvt );
//STRIP001  virtual void    Command( const CommandEvent& rCEvt );

//STRIP001  virtual sal_Int8 AcceptDrop( const AcceptDropEvent& rEvt );
//STRIP001  virtual sal_Int8 ExecuteDrop( const ExecuteDropEvent& rEvt );
//STRIP001  virtual void    StartDrag( sal_Int8 nAction, const Point& rPosPixel );

public:
    ScGridWindow( Window* pParent, ScViewData* pData, ScSplitPos eWhichPos );
    ~ScGridWindow();

//STRIP001  virtual void    DataChanged( const DataChangedEvent& rDCEvt );

//STRIP001  virtual void    MouseButtonDown( const MouseEvent& rMEvt );
//STRIP001  virtual void    MouseButtonUp( const MouseEvent& rMEvt );
//STRIP001  virtual void    MouseMove( const MouseEvent& rMEvt );
//STRIP001  virtual void    Tracking( const TrackingEvent& rTEvt );

//STRIP001  virtual ::com::sun::star::uno::Reference< ::com::sun::star::accessibility::XAccessible > CreateAccessible();

//STRIP001  void            FakeButtonUp();

//STRIP001  Point           GetMousePosPixel() const;
//STRIP001  void            UpdateStatusPosSize();

    void            ClickExtern();

//STRIP001  void            SetPointer( const Pointer& rPointer );

//STRIP001  void            MoveMouseStatus( ScGridWindow &rDestWin );

//STRIP001  void            ScrollPixel( long nDifX, long nDifY );
//STRIP001  void            UpdateEditViewPos();

    void            UpdateFormulas();

//STRIP001  void            DoAutoFilterMenue( USHORT nCol, USHORT nRow, BOOL bDataSelect );
//STRIP001  void            DoScenarioMenue( const ScRange& rScenRange );

    void            DrawButtons( USHORT nX1, USHORT nY1, USHORT nX2, USHORT nY2,
                                    RowInfo* pRowInfo, USHORT nArrCount );

    void            Draw( USHORT nX1, USHORT nY1, USHORT nX2, USHORT nY2,
                        ScUpdateMode eMode = SC_UPDATE_ALL );

//STRIP001  void            InvertSimple( USHORT nX1, USHORT nY1, USHORT nX2, USHORT nY2,
//STRIP001                                  BOOL bTestMerge = FALSE, BOOL bRepeat = FALSE );

//STRIP001  void            DrawDragRect( USHORT nX1, USHORT nY1, USHORT nX2, USHORT nY2,
//STRIP001                                  BOOL bMarkDrop = TRUE );

//STRIP001  void            DrawRefMark( USHORT nRefStartX, USHORT nRefStartY,
//STRIP001                                  USHORT nRefEndX, USHORT nRefEndY,
//STRIP001                                  const Color& rColor, BOOL bHandle );

//STRIP001  void            CreateAnchorHandle(SdrHdlList& rHdl, const ScAddress& rAddress);

    void            HideCursor();
    void            ShowCursor();
    void            DrawCursor();
    void            DrawAutoFillMark();
     void           UpdateAutoFillMark(BOOL bMarked, const ScRange& rMarkRange);

//STRIP001  BOOL            ShowNoteMarker( short nPosX, short nPosY, BOOL bKeyboard );
    void            HideNoteMarker();

    MapMode         GetDrawMapMode( BOOL bForce = FALSE );

    void            ContinueDrag();

    void            StopMarking();
//STRIP001  void            UpdateInputContext();

    void            CheckInverted()     { if (nPaintCount) bNeedsRepaint = TRUE; }

//STRIP001  void            DoInvertRect( const Rectangle& rPixel );

    void            CheckNeedsRepaint();
};



} //namespace binfilter
#endif

