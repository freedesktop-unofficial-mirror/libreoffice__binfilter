/*************************************************************************
 *
 *  $RCSfile: viewimp.hxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 15:23:32 $
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
#ifndef _VIEWIMP_HXX
#define _VIEWIMP_HXX


#ifndef _TIMER_HXX //autogen
#include <vcl/timer.hxx>
#endif
#ifndef _SV_COLOR_HXX //autogen
#include <vcl/color.hxx>
#endif
// OD 25.06.2003 #108784#
#ifndef _SVDTYPES_HXX
#include <bf_svx/svdtypes.hxx>
#endif

#include "swtypes.hxx"
#include "swrect.hxx"
#include <tools/debug.hxx> //for strip
class ViewShell;
class SwFlyFrm;
class SwViewOption;
class SwRegionRects;
class SwScrollAreas;
class SwScrollColumn;
class SwFrm;
class SwLayAction;
class SwLayIdle;
class SwDrawView;
class SdrPageView;
class SwPageFrm;
class SwRegionRects;
class ExtOutputDevice;
class SdrPaintInfoRec;
struct SdrPaintProcRec;
#ifdef ACCESSIBLE_LAYOUT
class SwAccessibleMap;
class SdrObject;
class Fraction;
#endif
// OD 12.12.2002 #103492#
class SwPagePreviewLayout;
// OD 15.01.2003 #103492#
#ifndef _PREVWPAGE_HXX
#include <prevwpage.hxx>
#endif
// OD 15.01.2003 #103492#
#include <vector>

class SwViewImp
{
    friend class ViewShell;

    friend class SwLayAction;   //Lay- und IdleAction tragen sich ein und aus.
    friend class SwLayIdle;

    // OD 12.12.2002 #103492# - for paint of page preview
    friend class SwPagePreviewLayout;

    ViewShell *pSh;             //Falls jemand einen Imp durchreicht und doch
                                //mal eine ViewShell braucht hier die
                                //Rueckwaertsverkettung.

    SwDrawView  *pDrawView;     //Unsere DrawView
    SdrPageView *pSdrPageView;  //Genau eine Seite fuer unsere DrawView

    SwPageFrm     *pFirstVisPage;//Zeigt immer auf die erste sichtbare Seite.
    SwRegionRects *pRegion;      //Sammler fuer Paintrects aus der LayAction.
    SwScrollAreas *pScrollRects; //Sammler fuer Scrollrects aus der LayAction.
    SwScrollAreas *pScrolledArea;//Sammler der gescrollten Rechtecke.

    SwLayAction   *pLayAct;      //Ist gesetzt wenn ein Action-Objekt existiert
                                 //Wird vom SwLayAction-CTor ein- und vom DTor
                                 //ausgetragen.
    SwLayIdle     *pIdleAct;     //Analog zur SwLayAction fuer SwLayIdle.

#ifdef ACCESSIBLE_LAYOUT
//STRIP001  SwAccessibleMap *pAccMap;       // Accessible Wrappers
#endif


    AutoTimer     aScrollTimer;  //Fuer das Aufraeumen nach dem Scrollen.

    BOOL bFirstPageInvalid  :1; //Pointer auf erste Seite ungueltig?
    BOOL bNextScroll        :1; //Scroll in der folgenden EndAction erlaubt?
    BOOL bScroll            :1; //Scroll in der aktuellen EndAction erlaubt?
    BOOL bScrolled          :1; //Wurde gescrolled? Dann im Idle aufraeumen.

    BOOL bResetXorVisibility:1; //StartAction/EndAction
    BOOL bShowHdlPaint      :1; //LockPaint/UnlockPaint
    BOOL bResetHdlHiddenPaint:1;//  -- "" --
    BOOL bPaintInScroll     :1; //Paint (Update() im ScrollHdl der ViewShell

    BOOL bSmoothUpdate      :1; //Meber fuer SmoothScroll
    BOOL bStopSmooth        :1;
    BOOL bStopPrt           :1; // Stop Printing

    USHORT nRestoreActions  ; //Die Anzahl der zu restaurierenden Actions (UNO)
    SwRect aSmoothRect;

    // OD 12.12.2002 #103492#
//STRIP001     SwPagePreviewLayout* mpPgPrevwLayout;

    /**
        Signal whether to stop printing.

        @param _useless just to fit macro
    */
    DECL_LINK(SetStopPrt, void * _useless = NULL);

    /**
       Returns if printer shall be stopped.

       @retval TRUE The printer shall be stopped.
       @retval FALSE else
    */
    BOOL IsStopPrt() { return bStopPrt; }

    /**
       Resets signal for stopping printing.

    */
    void ResetStopPrt() { bStopPrt = FALSE; }

    void SetFirstVisPage();     //Neue Ermittlung der ersten sichtbaren Seite

    void ResetNextScroll()    { bNextScroll = FALSE; }
    void SetNextScroll()      { bNextScroll = TRUE; }
    void SetScroll()          { bScroll = TRUE; }
    void ResetScrolled()      { bScrolled = FALSE; }
    void SetScrolled()        { bScrolled = TRUE; }

    SwScrollAreas *GetScrollRects() { return pScrollRects; }
//STRIP001  void FlushScrolledArea();
//STRIP001  BOOL _FlushScrolledArea( SwRect& rRect );
//STRIP001  BOOL FlushScrolledArea( SwRect& rRect )
//STRIP001  { if( !pScrolledArea ) return FALSE; return _FlushScrolledArea( rRect ); }
//STRIP001  void _ScrolledRect( const SwRect& rRect, long nOffs );
//STRIP001  void ScrolledRect( const SwRect& rRect, long nOffs )
//STRIP001  { if( pScrolledArea ) _ScrolledRect( rRect, nOffs ); }

    void StartAction();         //Henkel Anzeigen und verstecken.
    void EndAction();           //gerufen von ViewShell::ImplXXXAction
//STRIP001  void LockPaint();           //dito, gerufen von ViewShell::ImplLockPaint
//STRIP001  void UnlockPaint();

//STRIP001  void PaintFlyChilds( SwFlyFrm *pFly, ExtOutputDevice& rOut,
//STRIP001                       const SdrPaintInfoRec& rInfoRec );
#ifdef ACCESSIBLE_LAYOUT
//STRIP001  SwAccessibleMap *CreateAccessibleMap();
#endif

public:
    SwViewImp( ViewShell * );
    ~SwViewImp();
    void Init( const SwViewOption * );          //nur fuer ViewShell::Init()

    const ViewShell *GetShell() const { return pSh; }
          ViewShell *GetShell()       { return pSh; }

//STRIP001  Color GetRetoucheColor() const;

    //Verwaltung zur ersten sichtbaren Seite
    inline const SwPageFrm *GetFirstVisPage() const;
    inline       SwPageFrm *GetFirstVisPage();
    void SetFirstVisPageInvalid() { bFirstPageInvalid = TRUE; }

    //SS'en fuer Paint- und Scrollrects.
    BOOL AddPaintRect( const SwRect &rRect );
    void AddScrollRect( const SwFrm *pFrm, const SwRect &rRect, long nOffs );
//STRIP001  void MoveScrollArea();
    SwRegionRects *GetRegion()      { return pRegion; }
    void DelRegions();                      //Loescht Scroll- und PaintRects

    //Handler fuer das Refresh von gescrollten Bereichen (Korrektur des
    //Alignments). Ruft das Refresh mit der ScrolledArea.
    //RefreshScrolledArea kann z.B. beim Setzen des Crsr genutzt werden, es
    //wird nur der Anteil des Rect refreshed, der mit der ScrolledArea
    //ueberlappt. Das 'reingereichte Rechteck wird veraendert!
    void RestartScrollTimer()            { aScrollTimer.Start(); }
    DECL_LINK( RefreshScrolledHdl, Timer * );
//STRIP001  void _RefreshScrolledArea( const SwRect &rRect );
//STRIP001  void RefreshScrolledArea( SwRect &rRect );

    //Wird vom Layout ggf. waehrend einer Action gerufen, wenn der
    //Verdacht besteht, dass es etwas drunter und drueber geht.
    void ResetScroll()        { bScroll = FALSE; }

    BOOL IsNextScroll() const { return bNextScroll; }
    BOOL IsScroll()     const { return bScroll; }
    BOOL IsScrolled()   const { return bScrolled; }

    BOOL IsPaintInScroll() const { return bPaintInScroll; }

    // neues Interface fuer StarView Drawing
    inline const BOOL HasDrawView() const { return 0 != pDrawView; }
          SwDrawView* GetDrawView()       { return pDrawView; }
    const SwDrawView* GetDrawView() const { return pDrawView; }
          SdrPageView*GetPageView()       { return pSdrPageView; }
    const SdrPageView*GetPageView() const { return pSdrPageView; }
    void MakeDrawView();

    // OD 29.08.2002 #102450#
    // add 3rd parameter <const Color* pPageBackgrdColor> for setting this
    // color as the background color at the outliner of the draw view
    // for painting layers <hell> and <heaven>
    // OD 09.12.2002 #103045# - add 4th parameter for the horizontal text
    // direction of the page in order to set the default horizontal text
    // direction at the outliner of the draw view for painting layers <hell>
    // and <heaven>.
    // OD 25.06.2003 #108784# - correct type of 1st parameter
//STRIP001     void   PaintLayer  ( const SdrLayerID _nLayerID,
//STRIP001                          const SwRect& _rRect,
//STRIP001                          const Color* _pPageBackgrdColor = 0,
//STRIP001                          const bool _bIsPageRightToLeft = false ) const;

    //wird als Link an die DrawEngine uebergeben, entscheidet was wie
    //gepaintet wird oder nicht.
//STRIP001     DECL_LINK( PaintDispatcher, SdrPaintProcRec * );

    // Interface Drawing
//STRIP001  BOOL IsDragPossible( const Point &rPoint );
    void NotifySizeChg( const Size &rNewSz );

    //SS Fuer die Lay- bzw. IdleAction und verwandtes
    BOOL  IsAction() const                   { return pLayAct  != 0; }
    BOOL  IsIdleAction() const               { return pIdleAct != 0; }
          SwLayAction &GetLayAction()        { return *pLayAct; }
    const SwLayAction &GetLayAction() const  { return *pLayAct; }
          SwLayIdle   &GetIdleAction()       { return *pIdleAct;}
    const SwLayIdle   &GetIdleAction() const { return *pIdleAct;}

    //Wenn eine Aktion laueft wird diese gebeten zu pruefen ob es
    //an der zeit ist den WaitCrsr einzuschalten.
    void CheckWaitCrsr();
    BOOL IsCalcLayoutProgress() const;  //Fragt die LayAction wenn vorhanden.
    //TRUE wenn eine LayAction laeuft, dort wird dann auch das Flag fuer
    //ExpressionFields gesetzt.
    BOOL IsUpdateExpFlds();

    void    SetRestoreActions(USHORT nSet){nRestoreActions = nSet;}
    USHORT  GetRestoreActions() const{return nRestoreActions;}

    // OD 12.12.2002 #103492#
//STRIP001     void InitPagePreviewLayout();

    // OD 12.12.2002 #103492#
//STRIP001     inline SwPagePreviewLayout* PagePreviewLayout()
//STRIP001     {
//STRIP001         return mpPgPrevwLayout;
//STRIP001     }

#ifdef ACCESSIBLE_LAYOUT
    // Is this view accessible?
//STRIP001  sal_Bool IsAccessible() const { return pAccMap != 0; }

//STRIP001  inline SwAccessibleMap& GetAccessibleMap();

    // Update (this) accessible view
//STRIP001  void UpdateAccessible();

    // Remove a frame from the accessible view
    void DisposeAccessible( const SwFrm *pFrm, const SdrObject *pObj,
                            sal_Bool bRecursive );
//STRIP001  inline void DisposeAccessibleFrm( const SwFrm *pFrm,
//STRIP001                             sal_Bool bRecursive=sal_False );
    inline void DisposeAccessibleObj( const SdrObject *pObj );

    // Move a frame's position in the accessible view
    void MoveAccessible( const SwFrm *pFrm, const SdrObject *pObj,
                         const SwRect& rOldFrm );
//STRIP001  inline void MoveAccessibleFrm( const SwFrm *pFrm, const SwRect& rOldFrm );

    // Add a frame in the accessible view
//STRIP001  inline void AddAccessibleFrm( const SwFrm *pFrm );

     inline void AddAccessibleObj( const SdrObject *pObj );

    // Invalidate accessible frame's frame's content
    void InvalidateAccessibleFrmContent( const SwFrm *pFrm );

    // Invalidate accessible frame's cursor position
//STRIP001  void InvalidateAccessibleCursorPosition( const SwFrm *pFrm );

    // Invalidate editable state for all accessible frames
//STRIP001  void InvalidateAccessibleEditableState( sal_Bool bAllShells=sal_True,
//STRIP001                                          const SwFrm *pFrm=0 );

    // Invalidate opaque state for all accessible frames
//STRIP001  void InvalidateAccessibleOpaqueState();

    // Invalidate frame's relation set (for chained frames)
//STRIP001  void InvalidateAccessibleRelationSet( const SwFlyFrm *pMaster,
//STRIP001                                           const SwFlyFrm *pFollow );

    // update data for accessible preview
    // OD 15.01.2003 #103492# - change method signature due to new page preview
    // functionality
//STRIP001     void UpdateAccessiblePreview( const std::vector<PrevwPage*>& _rPrevwPages,
//STRIP001                                   const Fraction&  _rScale,
//STRIP001                                   const SwPageFrm* _pSelectedPageFrm,
//STRIP001                                   const Size&      _rPrevwWinSize );

//STRIP001     void InvalidateAccessiblePreViewSelection( sal_uInt16 nSelPage );

    // Fire all accessible events that have been collected so far
//STRIP001  void FireAccessibleEvents();
#endif
};

//Kann auf dem Stack angelegt werden, wenn etwas ausgegeben oder
//gescrolled wird. Handles und sontiges vom Drawing werden im CTor
//gehidet und im DTor wieder sichtbar gemacht.
//AW 06-Sep99: Hiding of handles is no longer necessary, removed
//STRIP001 class SwSaveHdl
//STRIP001 {
//STRIP001  SwViewImp *pImp;
//STRIP001  BOOL       bXorVis;
//STRIP001 public:
//STRIP001  SwSaveHdl( SwViewImp *pImp );
//STRIP001  ~SwSaveHdl();
//STRIP001 };


inline SwPageFrm *SwViewImp::GetFirstVisPage()
{
    if ( bFirstPageInvalid )
        SetFirstVisPage();
    return pFirstVisPage;
}

inline const SwPageFrm *SwViewImp::GetFirstVisPage() const
{
    if ( bFirstPageInvalid )
        ((SwViewImp*)this)->SetFirstVisPage();
    return pFirstVisPage;
}

#ifdef ACCESSIBLE_LAYOUT
//STRIP001 inline SwAccessibleMap& SwViewImp::GetAccessibleMap()
//STRIP001 {
//STRIP001  if( !pAccMap )
//STRIP001      CreateAccessibleMap();
//STRIP001
//STRIP001  return *pAccMap;
//STRIP001 }

//STRIP001 inline void SwViewImp::DisposeAccessibleFrm( const SwFrm *pFrm,
//STRIP001                             sal_Bool bRecursive )
//STRIP001 {
//STRIP001  DisposeAccessible( pFrm, 0, bRecursive );
//STRIP001 }

inline void SwViewImp::DisposeAccessibleObj( const SdrObject *pObj )
{
    DisposeAccessible( 0, pObj, sal_False );
}

//STRIP001 inline void SwViewImp::MoveAccessibleFrm( const SwFrm *pFrm,
//STRIP001                                        const SwRect& rOldFrm )
//STRIP001 {
//STRIP001  MoveAccessible( pFrm, 0, rOldFrm );
//STRIP001 }

//STRIP001 inline void SwViewImp::AddAccessibleFrm( const SwFrm *pFrm )
//STRIP001 {
//STRIP001  SwRect aEmptyRect;
//STRIP001  MoveAccessible( pFrm, 0, aEmptyRect );
//STRIP001 }

inline void SwViewImp::AddAccessibleObj( const SdrObject *pObj )
{
    SwRect aEmptyRect;
    MoveAccessible( 0, pObj, aEmptyRect );
}

#endif

#endif //_VIEWIMP_HXX

