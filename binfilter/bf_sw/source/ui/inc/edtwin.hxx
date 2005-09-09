/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: edtwin.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 05:30:44 $
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
#ifndef _EDTWIN_HXX
#define _EDTWIN_HXX

#ifndef _LINK_HXX
#include <tools/link.hxx>
#endif
#ifndef _TIMER_HXX
#include <vcl/timer.hxx>
#endif
#ifndef _WINDOW_HXX
#include <vcl/window.hxx>
#endif
#ifndef _TRANSFER_HXX
#include <svtools/transfer.hxx>
#endif

#ifndef _SWEVENT_HXX
#include <swevent.hxx>
#endif

#define _SVSTDARR_STRINGSISORTDTOR
#include <svtools/svstdarr.hxx>
namespace binfilter {

class   SwWrtShell;
class   SwView;
class   SwRect;
class   SwDrawBase;
class   ViewShell;
//STRIP001 class    SwAnchorMarker;
class   SdrViewUserMarker;
class   SdrObject;
class   SwShadowCursor;
class   DataChangedEvent;
class   OfaAutoCorrCfg;
class   SvxAutoCorrect;
struct  SwApplyTemplate;
struct  QuickHelpData;

/*--------------------------------------------------------------------
    Beschreibung:   Eingabe-Fenster
 --------------------------------------------------------------------*/

class SwEditWin: public Window,
                public DropTargetHelper, public DragSourceHelper
{
friend void     ScrollMDI(ViewShell* pVwSh, const SwRect&,
                          USHORT nRangeX, USHORT nRangeY);
friend BOOL     IsScrollMDI(ViewShell* pVwSh, const SwRect&);

friend void     SizeNotify(ViewShell* pVwSh, const Size &);

friend void     PageNumNotify(  ViewShell* pVwSh,
                                USHORT nPhyNum,
                                USHORT nVirtNum,
                                const String& rPg );

    static  QuickHelpData* pQuickHlpData;

    static  BOOL    bReplaceQuote;
    static  long    nDDStartPosX, nDDStartPosY;

    static  Color   aTextColor;     //Textfarbe, fuer die Giesskanne
    static  BOOL    bTransparentBackColor; // Hintergrund transparent
    static  Color   aTextBackColor; //Texthintergrundfarbe, fuer die Giesskanne

    /*
     * Timer und Handler fuer das Weiterscrollen, wenn der
     * Mauspointer innerhalb eines Drag-Vorgangs ausserhalb des
     * EditWin stehen bleibt.  In regelmaessigen Intervallen wird
     * die Selektion in Richtung der Mausposition vergroessert.
     */
    AutoTimer       aTimer;
    // Timer fuer verschachtelte KeyInputs (z.B. fuer Tabellen)
    Timer           aKeyInputTimer;
    // timer for ANY-KeyInut question without a following KeyInputEvent
    Timer           aKeyInputFlushTimer;

    String          aInBuffer;
    Point           aStartPos;
    Point           aMovePos;
    Point           aRszMvHdlPt;
    Timer           aTemplateTimer;

    // Type/Objecte ueber dem der MousePointer steht
    SwCallMouseEvent aSaveCallEvent;

    SwApplyTemplate     *pApplyTempl;
//STRIP001  SwAnchorMarker      *pAnchorMarker; // zum Verschieben eines Ankers

    SdrViewUserMarker   *pUserMarker;
    SdrObject           *pUserMarkerObj;
//STRIP001  SwShadowCursor      *pShadCrsr;

    SwView         &rView;

    int             aActHitType;    // aktueller Mauspointer

    ULONG           nDropFormat;    //Format aus dem letzten QueryDrop
    USHORT          nDropAction;    //Action aus dem letzten QueryDrop
    USHORT          nDropDestination;   //Ziel aus dem letzten QueryDrop

    UINT16          eDrawMode;
    UINT16          eBezierMode;
    UINT16          nInsFrmColCount; //Spaltenzahl fuer interaktiven Rahmen
    BOOL            bLinkRemoved    : 1,
                    bMBPressed      : 1,
                    bInsDraw        : 1,
                    bInsFrm         : 1,
                    bIsInMove       : 1,
                    bIsInDrag       : 1, //StartExecuteDrag nich doppelt ausfuehren
                    bOldIdle        : 1, //Zum abschalten des Idle'ns
                    bOldIdleSet     : 1, //waehrend QeueryDrop
                    bTblInsDelMode  : 1, //
                    bTblIsInsMode   : 1, //
                    bTblIsColMode   : 1, //
                    bChainMode      : 1, //Rahmen verbinden
                    bWasShdwCrsr    : 1, //ShadowCrsr war im MouseButtonDown an
                    bLockInput      : 1; //Lock waehrend die Rechenleiste aktiv ist

//STRIP001  void            LeaveArea(const Point &);
//STRIP001  void            JustifyAreaTimer();
//STRIP001  inline void     EnterArea();

//STRIP001  void            RstMBDownFlags();

//STRIP001  void            ChangeFly( BYTE nDir, BOOL bWeb = FALSE );
//STRIP001     void            ChangeDrawing( BYTE nDir );

//STRIP001  BOOL            EnterDrawMode(const MouseEvent& rMEvt, const Point& aDocPos);
//STRIP001     BOOL            RulerColumnDrag( SwView& , const MouseEvent& rMEvt, BOOL bVerticalMode);

    //Hilfsfunktionen fuer D&D
//STRIP001  void            DropCleanup();
//STRIP001  void            CleanupDropUserMarker();
//STRIP001  USHORT          GetDropDestination( const Point& rPixPnt,
//STRIP001                                      SdrObject ** ppObj = 0 );

    /*
     * Handler fuer das Weiterscrollen, wenn der Mauspointer innerhalb eines
     * Drag-Vorgangs ausserhalb des EditWin stehen bleibt. In regelmaessigen
     * Intervallen wird die Selektion in Richtung der Mausposition
     * vergroessert.
     */
    DECL_LINK( TimerHandler, Timer * );
//STRIP001  void            StartDDTimer();
//STRIP001  void            StopDDTimer(SwWrtShell *, const Point &);
//STRIP001  DECL_LINK( DDHandler, Timer * );

    // timer for ANY-KeyInut question without a following KeyInputEvent
    DECL_LINK( KeyInputFlushHandler, Timer * );

    // Timer fuer verschachtelte KeyInputs (z.B. fuer Tabellen)
    DECL_LINK( KeyInputTimerHandler, Timer * );

    // Timer fuer das ApplyTemplates per Maus (verkapptes Drag&Drop)
    DECL_LINK( TemplateTimerHdl, Timer* );

protected:

//STRIP001  virtual void    DataChanged( const DataChangedEvent& );
//STRIP001  virtual void    Paint( const Rectangle& rRect );
//STRIP001  virtual void    KeyInput(const KeyEvent &rKEvt);

//STRIP001  virtual void    GetFocus();
//STRIP001  virtual void    LoseFocus();


//STRIP001  virtual void    MouseMove(const MouseEvent& rMEvt);
//STRIP001  virtual void    MouseButtonDown(const MouseEvent& rMEvt);
//STRIP001  virtual void    MouseButtonUp(const MouseEvent& rMEvt);
//STRIP001  virtual void    RequestHelp(const HelpEvent& rEvt);

//STRIP001  virtual void    Command( const CommandEvent& rCEvt );

                                // Drag & Drop Interface
//STRIP001  virtual sal_Int8    AcceptDrop( const AcceptDropEvent& rEvt );
//STRIP001  virtual sal_Int8    ExecuteDrop( const ExecuteDropEvent& rEvt );
//STRIP001  virtual void        StartDrag( sal_Int8 nAction, const Point& rPosPixel );

    void    ShowAutoTextCorrectQuickHelp( const String& rWord, OfaAutoCorrCfg* pACfg, SvxAutoCorrect* pACorr );
public:

    void            UpdatePointer(const Point &, USHORT nButtons = 0);

//STRIP001  BOOL            IsDrawSelMode();
    BOOL            IsDrawAction()                  { return (bInsDraw); }
    void            SetDrawAction(BOOL bFlag)       { bInsDraw = bFlag; }
    inline UINT16   GetDrawMode(BOOL bBuf = FALSE) const { return eDrawMode; }
    inline void     SetDrawMode(UINT16 eDrwMode)    { eDrawMode = eDrwMode; }
//STRIP001  void            StdDrawMode(USHORT nSlotId);
    BOOL            IsFrmAction()                   { return (bInsFrm); }
    inline UINT16   GetBezierMode()                 { return eBezierMode; }
    void            SetBezierMode(UINT16 eBezMode)  { eBezierMode = eBezMode; }
//STRIP001  void            EnterDrawTextMode(const Point& aDocPos); // DrawTextEditMode einschalten
//STRIP001  void            InsFrm(USHORT nCols);
//STRIP001  void            StopInsFrm();
    UINT16          GetFrmColCount() const {return nInsFrmColCount;} //Spaltenzahl fuer interaktiven Rahmen


//STRIP001  void            SetChainMode( BOOL bOn );
    BOOL            IsChainMode() const             { return bChainMode; }

//STRIP001  void            FlushInBuffer( SwWrtShell *pSh );

    static  void    SetReplaceQuote(BOOL bOn = TRUE) { bReplaceQuote = bOn; }
    static  BOOL    IsReplaceQuote() { return bReplaceQuote; }

//STRIP001  void             SetApplyTemplate(const SwApplyTemplate &);
    SwApplyTemplate* GetApplyTemplate() const { return pApplyTempl; }

//STRIP001  void            StartExecuteDrag();
//STRIP001  void            DragFinished();
    USHORT          GetDropAction() const { return nDropAction; }
    ULONG           GetDropFormat() const { return nDropFormat; }

    Color           GetTextColor() { return aTextColor; }
    void            SetTextColor(const Color& rCol ) { aTextColor = rCol; }

    Color           GetTextBackColor()
                                            { return aTextBackColor; }
    void            SetTextBackColor(const Color& rCol )
                                            { aTextBackColor = rCol; }
    void            SetTextBackColorTransparent(BOOL bSet)
                                    { bTransparentBackColor = bSet; }
    BOOL            IsTextBackColorTransparent()
                                    { return bTransparentBackColor; }
    void            LockKeyInput(BOOL bSet){bLockInput = bSet;}

    const SwView &GetView() const { return rView; }
          SwView &GetView()       { return rView; }

#ifdef ACCESSIBLE_LAYOUT
//STRIP001     virtual ::com::sun::star::uno::Reference< ::com::sun::star::accessibility::XAccessible > CreateAccessible();
#endif

    // Tipfenster loeschen
//STRIP001  static void ClearTip();

    static inline long GetDDStartPosX() { return nDDStartPosX; }
    static inline long GetDDStartPosY() { return nDDStartPosY; }

    static void _InitStaticData();
    static void _FinitStaticData();

    //#i3370# remove quick help to prevent saving of autocorrection suggestions
    void StopQuickHelp();

    SwEditWin(Window *pParent, SwView &);
    virtual ~SwEditWin();
};


} //namespace binfilter
#endif

