/*************************************************************************
 *
 *  $RCSfile: pview.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:41:21 $
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
#ifndef _SWPVIEW_HXX
#define _SWPVIEW_HXX

#ifndef _SFXVIEWFRM_HXX //autogen
#include <bf_sfx2/viewfrm.hxx>
#endif
#ifndef _VIEWFAC_HXX //autogen
#include <bf_sfx2/viewfac.hxx>
#endif
#ifndef _LINK_HXX //autogen
#include <tools/link.hxx>
#endif
#ifndef _WINDOW_HXX //autogen
#include <vcl/window.hxx>
#endif
#ifndef _SFXVIEWSH_HXX //autogen
#include <bf_sfx2/viewsh.hxx>
#endif
#include "shellid.hxx"
#ifndef _SVX_ZOOMITEM_HXX
#include <bf_svx/zoomitem.hxx>
#endif
class ImageButton;
class Button;
class SvtAccessibilityOptions;
namespace binfilter {

class SwViewOption;
class SwDocShell;
class SwScrollbar;
class ViewShell;
class SwPagePreView;
class SwRect;
class DataChangedEvent;
class CommandEvent;

// OD 12.12.2002 #103492#
class SwPagePreviewLayout;

// OD 24.03.2003 #108282# - delete member <mnVirtPage> and its accessor.
class SwPagePreViewWin : public Window
{
    ViewShell*          mpViewShell;
    USHORT              mnSttPage;
    BYTE                mnRow, mnCol;
    Size                maPxWinSize;
    Fraction            maScale;
    SwPagePreView&      mrView;
    // OD 02.12.2002 #103492#
    bool                mbCalcScaleForPreviewLayout;
    Rectangle           maPaintedPreviewDocRect;
    // OD 12.12.2002 #103492#
    SwPagePreviewLayout* mpPgPrevwLayout;

//STRIP001  void SetPagePreview( BYTE nRow, BYTE nCol );

public:
    SwPagePreViewWin( Window* pParent, SwPagePreView& rView );
    ~SwPagePreViewWin();

    //Ruft ViewShell::Paint
//STRIP001  virtual void Paint( const Rectangle& rRect );
//STRIP001  virtual void KeyInput( const KeyEvent & );
//STRIP001  virtual void Command( const CommandEvent& rCEvt );
//STRIP001  virtual void MouseButtonDown(const MouseEvent& rMEvt);
//STRIP001  virtual void DataChanged( const DataChangedEvent& );

//STRIP001     void SetViewShell( ViewShell* pShell );

    ViewShell* GetViewShell() const { return mpViewShell; }

//STRIP001     BYTE    GetRow() const      { return mnRow; }
//STRIP001     void    SetRow( BYTE n )    { if( n ) mnRow = n; }
//STRIP001
//STRIP001     BYTE    GetCol() const      { return mnCol; }
//STRIP001     void    SetCol( BYTE n )    { if( n ) mnCol = n; }
//STRIP001
//STRIP001     USHORT  GetSttPage() const      { return mnSttPage; }
//STRIP001     void    SetSttPage( USHORT n )  { mnSttPage = n; }

    /** get selected page number of document preview

        OD 13.12.2002 #103492#

        @author OD

        @return selected page number
    */
//STRIP001     sal_uInt16 SelectedPage() const;

    /** set selected page number in document preview

        OD 13.12.2002 #103492#

        @author OD

        @param _nSelectedPageNum
        input parameter - physical page number of page that will be the selected one.
    */
//STRIP001     void SetSelectedPage( sal_uInt16 _nSelectedPageNum );

    //JP 19.08.98: bei Einspaltigkeit gibt es keine 0. Seite!
//STRIP001     USHORT  GetDefSttPage() const   { return 1 == mnCol ? 1 : 0; }

//STRIP001  void CalcWish( BYTE nNewRow, BYTE nNewCol );

//STRIP001     const Size& GetWinSize() const  { return maPxWinSize; }
//STRIP001  void SetWinSize( const Size& rNewSize );

    // OD 18.12.2002 #103492# - add <MV_SELPAGE>, <MV_SCROLL>
//STRIP001     enum MoveMode{ MV_CALC, MV_PAGE_UP, MV_PAGE_DOWN, MV_DOC_STT, MV_DOC_END,
//STRIP001                    MV_SELPAGE, MV_SCROLL, MV_NEWWINSIZE };
//STRIP001  int MovePage( int eMoveMode );

    // erzeuge den String fuer die StatusLeiste
//STRIP001  void GetStatusStr( String& rStr, USHORT nPageCount ) const;

//STRIP001  void RepaintCoreRect( const SwRect& rRect );

    /** method to adjust preview to a new zoom factor

        OD 02.12.2002 #103492#
        paint of preview is prepared for a new zoom factor

        @author OD
    */
//STRIP001     void AdjustPreviewToNewZoom( const sal_uInt16 nZoomFactor );
//STRIP001
//STRIP001     const Rectangle&           GetPaintedPreviewDocRect() const
//STRIP001                                     { return maPaintedPreviewDocRect;}
//STRIP001     void                       Scroll(long nXMove, long nYMove);
//STRIP001
#ifdef ACCESSIBLE_LAYOUT
//STRIP001     virtual ::com::sun::star::uno::Reference<
//STRIP001         ::com::sun::star::accessibility::XAccessible>
//STRIP001                     CreateAccessible();
#endif
};


/*--------------------------------------------------------------------
    Beschreibung:   Sicht auf ein Dokument
 --------------------------------------------------------------------*/

class SwPagePreView: public SfxViewShell
{
    // ViewWindow und Henkel zur Core
    // aktuelle Dispatcher-Shell
     SwPagePreViewWin        aViewWin;
    //viewdata of the previous SwView and the new crsrposition
    String                  sSwViewData,
    //and the new cursor position if the user double click in the PagePreView
                            sNewCrsrPos;
    // to support keyboard the number of the page to go to can be set too
    USHORT                  nNewPage;
   // Sichtbarer Bereich
    String                  sPageStr;
    Size                    aDocSz;
     Rectangle               aVisArea;

    // MDI Bedienelemente
    SwScrollbar             *pHScrollbar;
    SwScrollbar             *pVScrollbar;
     ImageButton             *pPageUpBtn,
                            *pPageDownBtn;
     // Dummy-Window zum FÅllen der rechten unteren Ecke, wenn beide Scrollbars
    // aktiv sind
     Window                 *pScrollFill;

    USHORT                  mnPageCount;
    BOOL                    bNormalPrint;

    // OD 09.01.2003 #106334#
    // new members to reset design mode at draw view for form shell on switching
    // back from writer page preview to normal view.
     sal_Bool                mbResetFormDesignMode:1;
    sal_Bool                mbFormDesignModeToReset:1;

//STRIP001  void            Init(const SwViewOption* = 0);
//STRIP001  Point           AlignToPixel(const Point& rPt) const;

//STRIP001  int             _CreateScrollbar( int bHori );
//STRIP001  DECL_LINK( ScrollHdl, SwScrollbar * );
//STRIP001  DECL_LINK( EndScrollHdl, SwScrollbar * );
//STRIP001  DECL_LINK( BtnPage, Button * );
//STRIP001  int             ChgPage( int eMvMode, int bUpdateScrollbar = TRUE );


//STRIP001  virtual USHORT          Print( SfxProgress &rProgress,
//STRIP001                                 PrintDialog *pPrintDialog = 0 );
//STRIP001  virtual SfxPrinter*     GetPrinter( BOOL bCreate = FALSE );
//STRIP001  virtual USHORT          SetPrinter( SfxPrinter *pNewPrinter, USHORT nDiffFlags = SFX_PRINTER_ALL );
//STRIP001  virtual SfxTabPage*     CreatePrintOptionsPage( Window *pParent,
//STRIP001                                              const SfxItemSet &rOptions );
//STRIP001  virtual PrintDialog*    CreatePrintDialog( Window *pParent );

//STRIP001  void CalcAndSetBorderPixel( SvBorder &rToFill, FASTBOOL bInner );

    /** help method to execute SfxRequest FN_PAGE_UP and FN_PAGE_DOWN

        OD 04.03.2003 #107369#

        @param _bPgUp
        input parameter - boolean that indicates, if FN_PAGE_UP or FN_PAGE_DOWN
        has to be executed.

        @param _pReq
        optional input parameter - pointer to the <SfxRequest> instance, if existing.

        @author OD
    */
//STRIP001     void _ExecPgUpAndPgDown( const bool  _bPgUp,
//STRIP001                              SfxRequest* _pReq = 0 );

protected:
//STRIP001  virtual void    InnerResizePixel( const Point &rOfs, const Size &rSize );
//STRIP001  virtual void    OuterResizePixel( const Point &rOfs, const Size &rSize );
//STRIP001  virtual Size    GetOptimalSizePixel() const;

    void         SetZoom(SvxZoomType eSet, USHORT nFactor);

public:
    SFX_DECL_VIEWFACTORY(SwPagePreView);
    SFX_DECL_INTERFACE(SW_PAGEPREVIEW);
    TYPEINFO();

//STRIP001  inline Window*          GetFrameWindow() const { return &(GetViewFrame())->GetWindow(); }
     inline ViewShell*       GetViewShell() const { return aViewWin.GetViewShell(); }
//STRIP001  inline const Rectangle& GetVisArea() const { return aVisArea; }
//STRIP001  inline void             GrabFocusViewWin() { aViewWin.GrabFocus(); }
//STRIP001  inline void             RepaintCoreRect( const SwRect& rRect )
//STRIP001                              { aViewWin.RepaintCoreRect( rRect ); }

//STRIP001  void            DocSzChgd(const Size& rNewSize);
//STRIP001  const Size&     GetDocSz() const { return aDocSz; }

//STRIP001  virtual void    SetVisArea( const Rectangle&, BOOL bUpdateScrollbar = TRUE);

//STRIP001  inline void     AdjustEditWin();

//STRIP001     void            ScrollViewSzChg();
//STRIP001     void            ScrollDocSzChg();
//STRIP001     void            ShowHScrollbar(sal_Bool bShow);
//STRIP001     sal_Bool        IsHScrollbarVisible()const;

//STRIP001     void            ShowVScrollbar(sal_Bool bShow);
//STRIP001     sal_Bool        IsVScrollbarVisible()const;

//STRIP001     USHORT          GetPageCount() const        { return mnPageCount; }

//STRIP001  BOOL            HandleWheelCommands( const CommandEvent& );
//STRIP001
//STRIP001  const String&   GetPrevSwViewData() const       { return sSwViewData; }
//STRIP001  void            SetNewCrsrPos( const String& rStr ) { sNewCrsrPos = rStr; }
//STRIP001  const String&   GetNewCrsrPos() const           { return sNewCrsrPos; }
//STRIP001
//STRIP001     USHORT          GetNewPage() const {return nNewPage;}
//STRIP001     void            SetNewPage(USHORT nSet)  {nNewPage = nSet;}

        // Handler
    void            Execute(SfxRequest&){DBG_BF_ASSERT(0, "STRIP");} ;//STRIP001    void            Execute(SfxRequest&);
    void            GetState(SfxItemSet&){DBG_BF_ASSERT(0, "STRIP");} ;//STRIP001   void            GetState(SfxItemSet&);
    void            StateUndo(SfxItemSet&){DBG_BF_ASSERT(0, "STRIP");} ;//STRIP001  void            StateUndo(SfxItemSet&);

    SwDocShell*     GetDocShell();

    //apply Accessiblity options
//STRIP001     void ApplyAccessiblityOptions(SvtAccessibilityOptions& rAccessibilityOptions);

    // OD 09.01.2003 #106334# - inline method to request values of new members
    // <mbResetFormDesignMode> and <mbFormDesignModeToReset>
//STRIP001     inline sal_Bool ResetFormDesignMode() const
//STRIP001     {
//STRIP001         return mbResetFormDesignMode;
//STRIP001     }

//STRIP001     inline sal_Bool FormDesignModeToReset() const
//STRIP001     {
//STRIP001         return mbFormDesignModeToReset;
//STRIP001     }

    /** adjust position of vertical scrollbar

        OD 19.02.2003 #107369
        Currently used, if the complete preview layout rows fit into to the given
        window, if a new page is selected and this page is visible.

        @author OD

        @param _nNewThumbPos
        input parameter - new position, which will be assigned to the vertical
        scrollbar.
    */
    void SetVScrollbarThumbPos( const sal_uInt16 _nNewThumbPos );

    SwPagePreView( SfxViewFrame* pFrame, SfxViewShell* );
     ~SwPagePreView();
};

// ----------------- inline Methoden ----------------------


//STRIP001 inline void SwPagePreView::AdjustEditWin()
//STRIP001 {
//STRIP001  OuterResizePixel( Point(), GetFrameWindow()->GetOutputSizePixel() );
//STRIP001 }

} //namespace binfilter
#endif
