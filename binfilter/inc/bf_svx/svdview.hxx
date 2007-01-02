/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svdview.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: hr $ $Date: 2007-01-02 18:36:20 $
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

#ifndef _SVDVIEW_HXX
#define _SVDVIEW_HXX

// HACK to avoid too deep includes and to have some
// levels free in svdmark itself (MS compiler include depth limit)
#ifndef _SVDHDL_HXX
#include <bf_svx/svdhdl.hxx>
#endif

#ifndef INCLUDED_SVTOOLS_ACCESSIBILITYOPTIONS_HXX
#include <svtools/accessibilityoptions.hxx>
#endif

#include <bf_svx/svdcrtv.hxx>
namespace binfilter {

////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Klassenhierarchie der View:
//         SfxListener
//         SdrPaintView    PntV   Action            ModChg   Attr   Notify
//         SdrSnapView     SnpV   Action
//
//         SdrMarkView     MrkV   Action   MrkChg   ModChg          Notify
//
//         SdrEditView     EdtV            MrkChg   ModChg   Attr
//         SdrPolyEditView PoEV
//         SdrGlueEditView GlEV
//         SdrObjEditView  EdxV   Action            ModChg   Attr   Notify
//
//         SdrExchangeView XcgV
//         SdrDragView     DrgV   Action
//
//         SdrCreateView   CrtV   Action
//         SdrView         View
//
////////////////////////////////////////////////////////////////////////////////////////////////////

//************************************************************
//   Vorausdeklarationen
//************************************************************

class SvxURLField;

//************************************************************
//   Defines
//************************************************************

enum SdrViewContext {SDRCONTEXT_STANDARD,
                     SDRCONTEXT_POINTEDIT,
                     SDRCONTEXT_GLUEPOINTEDIT,
                     SDRCONTEXT_TEXTEDIT,
                     SDRCONTEXT_GRAPHIC};

enum SdrEventKind  {SDREVENT_NONE,
                    SDREVENT_TEXTEDIT,
                    SDREVENT_MOVACTION,
                    SDREVENT_ENDACTION,
                    SDREVENT_BCKACTION,
                    SDREVENT_BRKACTION,
                    SDREVENT_ENDCREATE,
                    SDREVENT_ENDDRAG,
                    SDREVENT_MARKOBJ,
                    SDREVENT_MARKPOINT,
                    SDREVENT_MARKGLUEPOINT,
                    SDREVENT_BEGMARK,
                    SDREVENT_BEGINSOBJPOINT,
                    SDREVENT_ENDINSOBJPOINT,
                    SDREVENT_BEGINSGLUEPOINT,
                    SDREVENT_BEGDRAGHELPLINE,
                    SDREVENT_BEGDRAGOBJ,
                    SDREVENT_BEGCREATEOBJ,
                    SDREVENT_BEGMACROOBJ,
                    SDREVENT_BEGTEXTEDIT,
                    SDREVENT_ENDMARK,
                    SDREVENT_BRKMARK,
                    SDREVENT_EXECUTEURL};

#define SDRMOUSEBUTTONDOWN 1
#define SDRMOUSEMOVE       2
#define SDRMOUSEBUTTONUP   3

//************************************************************
//   Hilfsklasse SdrViewEvent
//************************************************************

struct SdrViewEvent
{
    SdrHdl*                     pHdl;
    SdrObject*                  pObj;
    SdrObject*                  pRootObj;        // Dieses Markieren bei BegTextEdit
    SdrPageView*                pPV;
    const SvxURLField*          pURLField;

    Point                       aLogicPos;
    SdrHitKind                  eHit;
    SdrEventKind                eEvent;
    SdrHdlKind                  eHdlKind;
    SdrCreateCmd                eEndCreateCmd;   // auch fuer EndInsPoint

    UINT16                      nMouseClicks;
    UINT16                      nMouseMode;
    UINT16                      nMouseCode;
    UINT16                      nHlplIdx;
    UINT16                      nGlueId;

    unsigned                    bMouseDown : 1;
    unsigned                    bMouseUp : 1;
    unsigned                    bDoubleHdlSize : 1;  // Doppelte Handlegroesse wg. TextEdit
    unsigned                    bIsAction : 1;       // Action ist aktiv
    unsigned                    bIsTextEdit : 1;     // TextEdit laeuft zur Zeit
    unsigned                    bTextEditHit : 1;    // offene OutlinerView getroffen
    unsigned                    bAddMark : 1;
    unsigned                    bUnmark : 1;
    unsigned                    bPrevNextMark : 1;
    unsigned                    bMarkPrev : 1;
    unsigned                    bInsPointNewObj : 1;
    unsigned                    bDragWithCopy : 1;
    unsigned                    bCaptureMouse : 1;
    unsigned                    bReleaseMouse : 1;

public:
    SdrViewEvent();
    ~SdrViewEvent();

    // nEventKind ist SDRMOUSEBUTTONDOWN, SDRMOUSEMOVE oder SDRMOUSEBUTTONUP
    void SetMouseEvent(const MouseEvent& rMEvt, USHORT nEventKind);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  @@ @@ @@ @@@@@ @@   @@
//  @@ @@ @@ @@    @@   @@
//  @@ @@ @@ @@    @@ @ @@
//  @@@@@ @@ @@@@  @@@@@@@
//   @@@  @@ @@    @@@@@@@
//   @@@  @@ @@    @@@ @@@
//    @   @@ @@@@@ @@   @@
//
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

class SdrView: public SdrCreateView
{
    friend class                SdrPageView;

    unsigned                    bNoExtendedMouseDispatcher : 1;
    unsigned                    bNoExtendedKeyDispatcher : 1;
    unsigned                    bNoExtendedCommandDispatcher : 1;
    unsigned                    bTextEditOnObjectsWithoutTextIfTextTool : 1;

protected:
    // Abgeleitete Klassen ueberladen lediglich die Methoden ReadData() und
    // WriteData(). Diese werden von den Streamoperatoren der View gerufen.
    // Wichtig ist, dass die ueberladen Methoden der abgeleiteten Klasse
    // als erstes die Methode der Basisklasse rufen, da sonst der CharSet
    // am Stream nicht korrekt gesetzt wird, ...
    virtual void WriteRecords(SvStream& rOut) const;
    virtual BOOL ReadRecord(const SdrIOHeader& rViewHead, const SdrNamedSubRecord& rSubHead, SvStream& rIn);

    SvtAccessibilityOptions maAccessibilityOptions;

    virtual void SFX_NOTIFY(SfxBroadcaster& rBC, const TypeId& rBCType, const SfxHint& rHint, const TypeId& rHintType);

public:
    TYPEINFO();
    SdrView(SdrModel* pModel1, OutputDevice* pOut);
    SdrView(SdrModel* pModel1, ExtOutputDevice* pOut);
    SdrView(SdrModel* pModel1);
    virtual ~SdrView();

    // Default sind alle Dispatcher aktiviert. Will die App z.B. fuer
    // Sonderbehandlungen im MouseDispatcher eingreifen, so muss sie
    // den erweiterten MouseDispather mit unten stehender Methode deaktivieren
    // und selbst nachimplementieren. Beispiel fuer MouseButtonDown:
    //      SdrViewEvent aVEvt;
    //      SdrHitKind eHit=pSdrView->PickAnything(rMEvt,SDRMOUSEBUTTONDOWN,aVEvt);
    //      ... hier Applikationsspezifischer Eingriff ...
    //      pSdrView->DoMouseEvent(aVEvt);
    //      SetPointer(GetPreferedPointer(...))
    //      CaptureMouse(...)
    void EnableExtendedMouseEventDispatcher(BOOL bOn) { bNoExtendedMouseDispatcher = !bOn; }
    BOOL IsExtendedMouseEventDispatcherEnabled() const { return bNoExtendedMouseDispatcher; }

    void EnableExtendedKeyInputDispatcher(BOOL bOn) { bNoExtendedKeyDispatcher=!bOn; }
    BOOL IsExtendedKeyInputDispatcherEnabled() const { return bNoExtendedKeyDispatcher; }

    void EnableExtendedCommandEventDispatcher(BOOL bOn) { bNoExtendedCommandDispatcher=!bOn; }
    BOOL IsExtendedCommandEventDispatcherEnabled() const { return bNoExtendedCommandDispatcher; }

    void EnableTextEditOnObjectsWithoutTextIfTextTool(BOOL bOn) { bTextEditOnObjectsWithoutTextIfTextTool=bOn; }
    BOOL IsEnableTextEditOnObjectsWithoutTextIfTextToolEnabled() const { return bTextEditOnObjectsWithoutTextIfTextTool; }


    // unvollstaendige Implementation:
    // Das OutputDevice ist notwendig, damit ich die HandleSize ermitteln kann.
    // Bei NULL wird das 1. angemeldete Win verwendet.
    Pointer GetPreferedPointer(const Point& rMousePos, const OutputDevice* pOut, USHORT nModifier=0, BOOL bLeftDown=FALSE) const;
    SdrHitKind PickAnything(const Point& rLogicPos, SdrViewEvent& rVEvt) const;
    SdrViewContext GetContext() const;

    // Die Methoden beruecksichtigen den jeweiligen Kontex:
    // - Einfaches Zeichnen
    // - Punktbearbeitungs-Mode
    // - Klebepunkt-Editmode
    // - TextEdit
    // - ... to be continued
    BOOL HasMarked() const { return HasMarkedObj(); }
    void UnmarkAll();


    virtual void DeleteMarked();

    // Markieren von Objekten, Polygonpunkten oder Klebepunkten (je nach View-
    // Kontext) durch Aufziehen eines Selektionsrahmens.
    //   bAddMark=TRUE: zur bestehenden Selektion hinzumarkieren (->Shift)
    //   bUnmark=TRUE: Bereits selektierte Objekte/Punkte/Klebepunkte die innerhalb
    //                 des aufgezogenen Rahmens liegen werden deselektiert.

    // Folgende Actions sind moeglich:
    //   - ObjectCreating
    //   - ObjectMarking
    //   - Object-specific dragging
    //   - General dragging
    // und mehr...
    String GetStatusText();

    // Strings werden beim rausstreamen in den am Stream eingestellten
    // StreamCharSet konvertiert.
    // Abgeleitete Klassen mit eigenen persistenten Membern ueberladen
    // die virtuellen Methoden ReadData() und WriteData().
    friend SvStream& operator<<(SvStream& rOut, const SdrView& rView);

    // Wenn das Model im Stream in einem fremden CharSet vorliegt
    // wird beim einstreamen implizit auf den SystemCharSet konvertiert.
    // Abgeleitete Klassen mit eigenen persistenten Membern ueberladen
    // die virtuellen Methoden ReadData() und WriteData().
    friend SvStream& operator>>(SvStream& rIn, SdrView& rView);


    virtual void onAccessibilityOptionsChanged();
};

}//end of namespace binfilter
#endif //_SVDVIEW_HXX

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Die App macht sich zunaechst ein SdrModel.
// Anschliessend oeffnet sie ein Win und erzeugt dann eine SdrView.
// An der SdrView meldet sie dann mit der Methode ShowPage() eine Seite an.
// Eine SdrView kann in beliebig vielen Fenstern gleichzeitig angezeigt werden.
// Intern:
// Eine SdrView kann beliebig viele Seiten gleichzeitig anzeigen. Seiten
// werden an- und abgemeldet mit ShowPage()/HidePage(). Fuer jede angemeldete
// Seite wird eine SdrPageView-Instanz im Container aPages angelegt. Bei
// gleichzeitiger Anzeige mehrerer Seiten ist darauf zu achten, dass der Offset-
// Parameter von ShowPage() der Seitengroesse angepasst ist, da sich sonst die
// Seiten ueberlappen koennten.
//
// Elementare Methoden:
// ~~~~~~~~~~~~~~~~~~~~
//   Einfache Events:
//   ~~~~~~~~~~~~~~~~
//     BOOL KeyInput(const KeyEvent& rKEvt, Window* pWin);
//     BOOL MouseButtonDown(const MouseEvent& rMEvt, Window* pWin);
//     BOOL MouseButtonUp(const MouseEvent& rMEvt, Window* pWin);
//     BOOL MouseMove(const MouseEvent& rMEvt, Window* pWin);
//     BOOL Command(const CommandEvent& rCEvt, Window* pWin);
//
//   Exchange (Clipboard derzeit noch ohne SdrPrivateData):
//   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//     BOOL Cut(ULONG nFormat=SDR_ANYFORMAT);
//     BOOL Yank(ULONG nFormat=SDR_ANYFORMAT);
//     BOOL Paste(Window* pWin=NULL, ULONG nFormat=SDR_ANYFORMAT);
//
//   SfxItems:
//   ~~~~~~~~~
//     BOOL GetAttributes(SfxItemSet& rTargetSet, BOOL bOnlyHardAttr=FALSE) const;
//     BOOL SetAttributes(const SfxItemSet& rSet, BOOL bReplaceAll);
//     SfxStyleSheet* GetStyleSheet() const;
//     BOOL SetStyleSheet(SfxStyleSheet* pStyleSheet, BOOL bDontRemoveHardAttr);
//
//   Sonstiges:
//   ~~~~~~~~~~
//     Pointer GetPreferedPointer(const Point& rMousePos, const OutputDevice* pOut, USHORT nTol=0) const;
//     String  GetStatusText();
//
///////////////////////////////////////////////////////////////////////////////////////////////// */

