/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sfx2_shell.cxx,v $
 *
 *  $Revision: 1.10 $
 *
 *  last change: $Author: rt $ $Date: 2007-04-25 14:35:28 $
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

#ifndef _PSEUDO_HXX //autogen
#include <so3/pseudo.hxx>
#endif
#ifndef _SFXITEMPOOL_HXX //autogen
#include <svtools/itempool.hxx>
#endif
#ifndef _UNDO_HXX //autogen
#include <svtools/undo.hxx>
#endif
#ifndef _SVTOOLS_ITEMDEL_HXX
#include <svtools/itemdel.hxx>
#endif

#ifndef   SVTOOLS_ASYNCLINK_HXX
#include <svtools/asynclink.hxx>
#endif
#ifndef _SBXCLASS_HXX //autogen
#include "bf_basic/sbx.hxx"
#endif

#include <svtools/undoopt.hxx>

#pragma hdrstop

#include "viewfrm.hxx"
#include "objface.hxx"
#include "viewsh.hxx"
#include "dispatch.hxx"
#include "request.hxx"

#ifndef _COM_SUN_STAR_LANG_XTYPEPROVIDER_HPP_
#include <com/sun/star/lang/XTypeProvider.hpp>
#endif

#include "macrconf.hxx"
namespace binfilter {

//====================================================================

/*N*/ DBG_NAME(SfxShell)

//====================================================================

/*N*/ TYPEINIT0(SfxShell);

//====================================================================
/*N*/ typedef SfxSlot* SfxSlotPtr;
/*N*/ SV_DECL_PTRARR_DEL( SfxVerbSlotArr_Impl, SfxSlotPtr, 4, 4)//STRIP008 ;
/*N*/ SV_IMPL_PTRARR( SfxVerbSlotArr_Impl, SfxSlotPtr);

/*N*/ struct SfxVerbList
/*N*/ {
/*N*/   SfxVerbSlotArr_Impl       aSlotArr;
/*N*/   SvVerbList                aVerbList;
/*N*/ };

/*N*/ struct SfxShell_Impl: public SfxBroadcaster
/*N*/ {
/*N*/   String                      aObjectName;// Name des Sbx-Objects
/*N*/   SfxItemArray_Impl           aItems;     // Datenaustausch auf Item-Basis
/*N*/     SfxViewShell*               pViewSh;    // SfxViewShell falls Shell ViewFrame/ViewShell/SubShell ist
/*N*/   SfxViewFrame*               pFrame;     // Frame, falls <UI-aktiv>
/*N*/   SfxVerbList*                pVerbs;
/*N*/   SfxRepeatTarget*            pRepeatTarget;
/*N*/ //    SbxObjectRef                xParent;
/*N*/   BOOL                        bInAppBASIC;
/*N*/   BOOL                        bActive;
/*N*/   ULONG                       nDisableFlags;
/*N*/   ULONG                       nHelpId;
/*N*/     svtools::AsynchronLink*     pExecuter;
/*N*/     svtools::AsynchronLink*     pUpdater;
/*N*/   SfxShell_Impl()  : pExecuter( 0 ), pUpdater( 0 ) {}
/*N*/   ~SfxShell_Impl() { delete pExecuter; delete pUpdater;}
/*N*/ };

//====================================================================
#ifdef DBG_UTIL

/*?*/ String SfxShellIdent_Impl( const SfxShell *pSh )

/*  [Beschreibung]

    Interne Hilfesfunktion. Liefert einen die SfxShell 'pSh' beschreibenden
    String zur"uck. Z.B.: SfxApplication[StarWriter]
*/

/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return String();//STRIP001
/*?*/ }

#endif
//====================================================================

/*?*/ void __EXPORT SfxShell::EmptyExecStub(SfxShell *, SfxRequest &)
/*?*/ {
/*?*/ }

/*N*/ void __EXPORT SfxShell::EmptyStateStub(SfxShell *, SfxItemSet &)
/*N*/ {
/*N*/ }

/*N*/ SfxShell::SfxShell()

/*  [Beschreibung]

    Der Konstruktor der Klasse SfxShell initialisierung nur einfache
    Typen, das dazugeh"orige SbxObject wird erst on-demand erzeugt.
    Daher ist das Anlegen einer SfxShell Instanz sehr billig.
*/

/*N*/ :   pPool(0),
/*N*/   pUndoMgr(0),
/*N*/   pImp(0)
/*N*/ {
/*N*/   DBG_CTOR(SfxShell, 0);
/*N*/   pImp = new SfxShell_Impl;
/*N*/   pImp->pViewSh = 0;
/*N*/   pImp->pFrame = 0;
/*N*/   pImp->pVerbs = 0;
/*N*/   pImp->pRepeatTarget = 0;
/*N*/   pImp->bInAppBASIC = FALSE;
/*N*/   pImp->nHelpId = 0L;
/*N*/   pImp->bActive = FALSE;
/*N*/   pImp->nDisableFlags = 0;
/*N*/ }

//-------------------------------------------------------------------------

/*N*/ SfxShell::SfxShell( SfxViewShell *pViewSh )

/*  [Beschreibung]

    Der Konstruktor der Klasse SfxShell initialisierung nur einfache
    Typen, das dazugeh"orige SbxObject wird erst on-demand erzeugt.
    Daher ist das Anlegen einer SfxShell Instanz sehr billig.
*/

/*N*/ :   pPool(0),
/*N*/   pUndoMgr(0),
/*N*/   pImp(0)
/*N*/ {
/*N*/   DBG_CTOR(SfxShell, 0);
/*N*/   pImp = new SfxShell_Impl;
/*N*/   pImp->pViewSh = pViewSh;
/*N*/   pImp->pFrame = 0;
/*N*/   pImp->pVerbs = 0;
/*N*/   pImp->pRepeatTarget = 0;
/*N*/   pImp->bInAppBASIC = FALSE;
/*N*/   pImp->nHelpId = 0L;
/*N*/   pImp->bActive = FALSE;
/*N*/ }

//--------------------------------------------------------------------

/*N*/ SfxShell::~SfxShell()

/*  [Beschreibung]

    Die Verbindungs zu einem ggf. zugeh"origen SbxObject wird gel"ost.
    Das SbxObject existiert ggf. weiter, kann aber keine Funktionen
    mehr ausf"uhren und keine Properties mehr bereitstellen.
*/

/*N*/ {
/*N*/   DBG_DTOR(SfxShell, 0);
/*N*/   delete pImp->pVerbs;
/*N*/   delete pImp;
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void SfxShell::SetName( const String &rName )

/*  [Beschreibung]

    Setzt den Namen des Shell-Objekts. Mit diesem Namen kann die
    SfxShell-Instanz vom BASIC aus angesprochen werden.
*/

/*N*/ {
/*N*/   pImp->aObjectName = rName;
/*N*/ }

//--------------------------------------------------------------------

/*N*/ const String& SfxShell::GetName() const

/*  [Beschreibung]

    Liefert den Namen des Shell-Objekts. Mit diesem Namen kann die
    SfxShell-Instanz vom BASIC aus angesprochen werden.
*/

/*N*/ {
/*N*/   return pImp->aObjectName;
/*N*/ }

//--------------------------------------------------------------------

/*?*/ SvGlobalName SfxShell::GetGlobalName() const

/*  [Beschreibung]

    Liefert den Global Unique Identifier des Shell-Objekts. Mit diesem
    Namen kann die SfxShell-Instanz z.B. via OLE Automation angesprochen
    werden, bzw. in der Registration-Database gefunden werden.
*/

/*?*/ {
/*?*/   return SvGlobalName();
/*?*/ }

//--------------------------------------------------------------------

/*N*/ SfxDispatcher* SfxShell::GetDispatcher() const

/*  [Beschreibung]

    Diese Methode liefert einen Pointer auf den <SfxDispatcher>, in
    dem die SfxShell gerade <UI-aktiv> ist bzw. einen 0-Pointer, wenn
    sie gerade nicht UI-aktiv ist.

    Der zur"uckgegebene Pointer ist nur im unmittelbaren Kontext des
    Methodenaufrufs g"ultig.
*/

/*N*/ {
/*N*/   return pImp->pFrame ? pImp->pFrame->GetDispatcher() : 0;
/*N*/ }

//--------------------------------------------------------------------

/*N*/ SfxViewShell* SfxShell::GetViewShell() const

/*  [Beschreibung]

    Liefert bei SubShells die SfxViewShell, in der sie liegen. Sonst und
    falls nicht vom App-Entwickler angegeben liefert diese Methode 0.
*/

/*N*/ {
/*N*/   return pImp->pViewSh;
/*N*/ }

//--------------------------------------------------------------------

/*N*/ SfxViewFrame* SfxShell::GetFrame() const

/*  [Beschreibung]

    Diese Methode liefert einen Pointer auf den <SfxViewFrame>, dem diese
    SfxShell-Instanz zugeordnet ist oder in dem sie zur Zeit <UI-aktiv> ist.
    Ein 0-Pointer wird geliefert, wenn diese SfxShell-OInstanz gerade nicht
    UI-aktiv ist und auch keinem SfxViewFrame fest zugeordnet ist.

    Der zur"uckgegebene Pointer ist nur im unmittelbaren Kontext des
    Methodenaufrufs g"ultig.


    [Anmerkung]

    Nur Instanzen von Subklasse von SfxApplication und SfxObjectShell sollten
    hier einen 0-Pointer liefern. Ansonsten liegt ein Fehler im Anwendungs-
    programm vor (falscher Ctor von SfxShell gerufen).


    [Querverweise]

    <SfxViewShell::GetViewFrame()const>
*/

/*N*/ {
/*N*/   if ( pImp->pFrame )
/*N*/       return pImp->pFrame;
/*N*/   if ( pImp->pViewSh )
/*N*/       return pImp->pViewSh->GetViewFrame();
/*N*/   return 0;
/*N*/ }

//--------------------------------------------------------------------

/*N*/ const SfxPoolItem* SfxShell::GetItem
/*N*/ (
/*N*/   USHORT  nSlotId         // Slot-Id des zu erfragenden <SfxPoolItem>s
/*N*/ )   const

/*  [Beschreibung]

    Mit dieser Methode kann auf beliebige Objekte von Subklassen von
    <SfxPoolItem> zugegriffen werden. Diese Austauschtechnik wird ben"otigt,
    wenn z.B. spezielle <SfxToolBoxControl> Subklassen Zugriff auf
    bestimmte Daten z.B. der <SfxObjectShell> ben"otigen.

    Die zur"uckgelieferte Instanz geh"ort der jeweilige SfxShell und
    darf nur im unmittelbaren Kontext des Methodenaufrufs verwendet werden.


    [Querverweise]

    <SfxShell::PutItem(const SfxPoolItem&)>
    <SfxShell::RemoveItem(USHORT)>
*/

/*N*/ {
/*N*/   for ( USHORT nPos = 0; nPos < pImp->aItems.Count(); ++nPos )
/*N*/       if ( pImp->aItems.GetObject(nPos)->Which() == nSlotId )
/*N*/           return pImp->aItems.GetObject(nPos);
/*N*/   return 0;
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void SfxShell::RemoveItem
/*N*/ (
/*N*/   USHORT  nSlotId         // Slot-Id des zu l"oschenden <SfxPoolItem>s
/*N*/ )

/*  [Beschreibung]

    Mit dieser Methode k"onnen die allgemein zur Verf"ugung gestellten
    Instanzen von Subklassen von <SfxPoolItem> aus der SfxShell entfernt
    werden.

    Die gespeicherte Instanz wird gel"oscht.


    [Querverweise]

    <SfxShell::PutItem(const SfxPoolItem&)>
    <SfxShell::GetItem(USHORT)>
*/

/*N*/ {
/*N*/   for ( USHORT nPos = 0; nPos < pImp->aItems.Count(); ++nPos )
/*?*/       if ( pImp->aItems.GetObject(nPos)->Which() == nSlotId )
/*?*/       {
/*?*/           // Item entfernen und l"oschen
/*?*/           SfxPoolItem *pItem = pImp->aItems.GetObject(nPos);
/*?*/           delete pItem;
/*?*/           pImp->aItems.Remove(nPos);
/*?*/
/*?*/           // falls aktiv Bindings benachrichtigen
/*?*/           SfxDispatcher *pDispat = GetDispatcher();
/*?*/           if ( pDispat )
/*?*/           {
/*?*/               SfxVoidItem aVoid( nSlotId );
/*?*/               pDispat->GetBindings()->Broadcast( SfxPoolItemHint( &aVoid ) );
/*?*/           }
/*N*/       }
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void SfxShell::PutItem
/*N*/ (
/*N*/   const SfxPoolItem&  rItem   /*  Instanz, von der eine Kopie erstellt wird,
                                    die in der SfxShell in einer Liste
                                    gespeichert wird. */
/*N*/ )

/*  [Beschreibung]

    Mit dieser Methode k"onnen beliebige Objekte von Subklassen von
    <SfxPoolItem> zur Verf"ugung gestellt werden. Diese Austauschtechnik
    wird ben"otigt, wenn z.B. spezielle <SfxToolBoxControl> Subklassen
    Zugriff auf bestimmte Daten z.B. der <SfxObjectShell> ben"otigen.

    Falls ein SfxPoolItem mit derselben Slot-Id exisitert, wird dieses
    automatisch gel"oscht.


    [Querverweise]

    <SfxShell::RemoveItem(USHORT)>
    <SfxShell::GetItem(USHORT)>
*/

/*N*/ {
/*N*/   DBG_ASSERT( !rItem.ISA(SfxSetItem), "SetItems aren't allowed here" );
/*N*/   DBG_ASSERT( SfxItemPool::IsSlot( rItem.Which() ),
/*N*/               "items with Which-Ids aren't allowed here" );
/*N*/
/*N*/   // MSC auf WNT/W95 machte hier Mist, Vorsicht bei Umstellungen
/*N*/   const SfxPoolItem *pItem = rItem.Clone();
/*N*/   SfxPoolItemHint aItemHint( (SfxPoolItem*) pItem );
/*N*/   const USHORT nWhich = rItem.Which();
/*N*/   SfxPoolItem **ppLoopItem = (SfxPoolItem**) pImp->aItems.GetData();
/*N*/   USHORT nPos;
/*N*/   for ( nPos = 0; nPos < pImp->aItems.Count(); ++nPos, ++ppLoopItem )
/*N*/   {
/*N*/       if ( (*ppLoopItem)->Which() == nWhich )
/*N*/       {
/*N*/           // Item austauschen
/*N*/           delete *ppLoopItem;
/*N*/           pImp->aItems.Remove(nPos);
/*N*/           pImp->aItems.Insert( (SfxPoolItemPtr) pItem, nPos );
/*N*/
/*N*/           // falls aktiv Bindings benachrichtigen
/*N*/           SfxDispatcher *pDispat = GetDispatcher();
/*N*/           if ( pDispat )
/*N*/               pDispat->GetBindings()->Broadcast( aItemHint );
/*N*/           return;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   Broadcast( aItemHint );
/*N*/   pImp->aItems.Insert((SfxPoolItemPtr)pItem, nPos );
/*N*/ }

//--------------------------------------------------------------------

/*N*/ SfxInterface* SfxShell::GetInterface() const

/*  [Beschreibung]

    Mit dieser virtuellen Methode, die durch das Makro <SFX_DECL_INTERFACE>
    von jeder Subclass mit eigenen Slots automatisch "uberladen wird, kann
    auf die zu der Subklasse geh"orende <SfxInterface>-Instanz zugegriffen
    werden.

    Die Klasse SfxShell selbst hat noch kein eigenes SfxInterface
    (keine Slots), daher wird ein 0-Pointer zur"uckgeliefert.
*/

/*N*/ {
/*N*/   return 0;
/*N*/ }

//--------------------------------------------------------------------

/*N*/ SfxBroadcaster* SfxShell::GetBroadcaster()

/*  [Beschreibung]

    Liefert einen SfxBroadcaster f"ur diese SfxShell-Instanz bis die
    Klasse SfxShell von SfxBroadcaster abgeleitet ist.
*/

/*N*/ {
/*N*/   return pImp;
/*N*/ }

//--------------------------------------------------------------------

/*N*/ SfxUndoManager* SfxShell::GetUndoManager()

/*  [Beschreibung]

    Jede Subclass von SfxShell kann "uber einen <SfxUndoManager> verf"ugen.
    Dieser kann in den abgeleiteten Klasse mit <SfxShell:SetUndoManager()>
    gesetzt werden.

    Die Klasse SfxShell selbst hat noch keinen SfxUndoManager, es wird
    daher ein 0-Pointer zur"uckgeliefert.
*/

/*N*/ {
/*N*/   return pUndoMgr;
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void SfxShell::SetUndoManager( SfxUndoManager *pNewUndoMgr )

/*  [Beschreibung]

    Setzt einen <SfxUndoManager> f"ur diese <SfxShell> Instanz. F"ur das
    Undo wird immer nur der Undo-Manager an der jeweils oben auf dem
    Stack des <SfxDispatcher> liegenden SfxShell verwendet.

    Am "ubergebenen <SfxUndoManager> wird automatisch die aktuelle
    Max-Undo-Action-Count Einstellung aus den Optionen gesetzt.

    'pNewUndoMgr' mu\s bis zum Dtor dieser SfxShell-Instanz oder bis
    zum n"achsten 'SetUndoManager()' existieren.
*/

/*N*/ {
/*N*/   pUndoMgr = pNewUndoMgr;
/*N*/   if ( pUndoMgr )
/*N*/         pUndoMgr->SetMaxUndoActionCount( (USHORT) SvtUndoOptions().GetUndoCount() );
/*N*/ }

//--------------------------------------------------------------------

/*N*/ SfxRepeatTarget* SfxShell::GetRepeatTarget() const

/*  [Beschreibung]

    Liefert einen Pointer auf die <SfxRepeatTarget>-Instanz, die
    als RepeatTarget bei SID_REPEAT verwendet wird, wenn der
    von dieser SfxShell gelieferte <SfxUndoManager> angesprochen wird.
    Der R"uckgabewert kann 0 sein.


    [Anmerkung]

    Eine Ableitung von <SfxShell> oder einer ihrer Subklassen von
    <SfxRepeatTarget> ist nicht zu empfehlen, da Compiler-Fehler
    provoziert werden (wegen Call-to-Pointer-to-Member-Function to
    subclass).
*/

/*N*/ {
/*N*/   return pImp->pRepeatTarget;
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void SfxShell::SetRepeatTarget( SfxRepeatTarget *pTarget )

/*  [Beschreibung]

    Setzt den die <SfxRepeatTarget>-Instanz, die bei SID_REPEAT als
    RepeatTarget verwendet wird, wenn der von dieser SfxShell gelieferte
    <SfxUndoManager> angesprochen wird. Durch 'pTarget==0' wird SID_REPEAT
    f"ur diese SfxShell disabled. Die Instanz '*pTarget' mu\s so lange
    leben, wie sie angemeldet ist.


    [Anmerkung]

    Eine Ableitung von <SfxShell> oder einer ihrer Subklassen von
    <SfxRepeatTarget> ist nicht zu empfehlen, da Compiler-Fehler
    provoziert werden (wegen Call-to-Pointer-to-Member-Function to
    subclass).
*/

/*N*/ {
/*N*/   pImp->pRepeatTarget = pTarget;
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void SfxShell::Invalidate
/*N*/ (
/*N*/   USHORT          nId     /* Zu invalidierende Slot-Id oder Which-Id.
                               Falls diese 0 ist (default), werden
                               alle z.Zt. von dieser Shell bedienten
                               Slot-Ids invalidiert. */
/*N*/ )

/*  [Beschreibung]

    Mit dieser Methode k"onnen Slots der Subclasses "uber die Slot-Id
    oder alternativ "uber die Which-Id invalidiert werden. Slot-Ids,
    die von der Subclass ererbt sind, werden ebenfalls invalidert.

    [Querverweise]
    <SfxBindings::Invalidate(USHORT)>
    <SfxBindings::InvalidateAll(BOOL)>
*/

/*N*/ {
/*N*/     if ( !GetViewShell() )
/*N*/     {
/*N*/ #if SUPD>603
/*?*/         DBG_ERROR( "wrong Invalidate method called!" );
/*N*/ #endif
/*N*/         return;
/*N*/     }
/*N*/
/*N*/     Invalidate_Impl( GetViewShell()->GetViewFrame()->GetBindings(), nId );
/*N*/ }

/*N*/ void SfxShell::Invalidate_Impl( SfxBindings& rBindings, USHORT nId )
/*N*/ {
/*N*/   if ( nId == 0 )
/*N*/     {
/*N*/         rBindings.InvalidateShell( *this, FALSE );
/*N*/     }
/*N*/   else
/*N*/   {
/*N*/       const SfxInterface *pIF = GetInterface();
/*N*/       do
/*N*/       {
/*N*/           const SfxSlot *pSlot = pIF->GetSlot(nId);
/*N*/           if ( pSlot )
/*N*/           {
/*N*/               // bei Enum-Slots ist der Master-Slot zu invalidieren
/*N*/               if ( SFX_KIND_ENUM == pSlot->GetKind() )
/*?*/                   pSlot = pSlot->GetLinkedSlot();
/*N*/
/*N*/               // den Slot selbst und ggf. auch alle Slave-Slots invalidieren
/*N*/               rBindings.Invalidate( pSlot->GetSlotId() );
/*N*/               for ( const SfxSlot *pSlave = pSlot->GetLinkedSlot();
/*N*/                     pSlave && pIF->ContainsSlot_Impl( pSlave ) &&
/*N*/                       pSlave->GetLinkedSlot() == pSlot;
/*N*/                     ++pSlave )
/*?*/                   rBindings.Invalidate( pSlave->GetSlotId() );
/*N*/
/*N*/               return;
/*N*/           }
/*N*/
/*N*/           pIF = pIF->GetGenoType();
/*N*/       }
/*N*/
/*N*/       while ( pIF );
/*N*/
/*N*/       DBG_WARNING( "W3: invalidating slot-id unknown in shell" );
/*N*/   }
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void SfxShell::DoActivate( SfxViewFrame *pFrame, BOOL bMDI )

/*  [Beschreibung]

    Diese Methode steuert die Aktivierung der SfxShell-Instanz. Zun"achst
    wird durch Aufruf der virtuellen Methode <SfxShell::Activate(BOOL)>
    der Subclass die M"oglichkeit gegeben, auf das Event zu reagieren.

    Bei bMDI == TRUE wird das zugeh"orige SbxObject 'scharfgeschaltet',
    so da\s Methoden des Objekts unqualifiziert (ohne den Namen des Objekts)
    vom BASIC gefunden werden.
*/

/*N*/ {
/*N*/ #ifndef PRODUCT
/*N*/   const SfxInterface *p_IF = GetInterface();
/*N*/   if ( !p_IF )
/*?*/       return;
/*N*/ #endif
#ifdef DBG_UTIL_VB
        String aMsg("SfxShell::DoActivate() ");
        aMsg += (long)this;
        aMsg += "  ";
        aMsg += GetInterface()->GetName();
        aMsg += " bMDI ";
        if ( bMDI ) aMsg += "MDI";
        DbgTrace( aMsg.GetBuffer() );
#endif

/*N*/   if ( bMDI )
/*N*/   {
/*N*/       // Frame merken, in dem aktiviert wird
/*N*/       pImp->pFrame = pFrame;
/*N*/       pImp->bActive = TRUE;
/*N*/   }
/*N*/
/*N*/   // Subklasse benachrichtigen
/*N*/   Activate(bMDI);
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void SfxShell::DoDeactivate( SfxViewFrame *pFrame, BOOL bMDI )

/*  [Beschreibung]

    Diese Methode steuert die Deaktivierung der SfxShell-Instanz. Bei
    bMDI == TRUE wird zun"achst das SbxObject in einen Status versetzt,
    so da\s Methoden vom BASIC aus nur noch qualifiziert gerufen werden
    k"onnen.

    Dann erh"alt in jedem Fall die Subclass durch Aufruf der virtuellen
    Methode <SfxShell::Deactivate(BOOL)> die M"oglichkeit auf das Event
    zu reagieren.
*/

/*N*/ {
/*N*/ #ifndef PRODUCT
/*N*/   const SfxInterface *p_IF = GetInterface();
/*N*/   if ( !p_IF )
/*N*/       return;
/*N*/ #endif
/*N*/ #ifdef DBG_UTIL_VB
/*N*/       String aMsg("SfxShell::DoDeactivate()");
/*N*/       aMsg += (long)this;
/*N*/       aMsg += "  ";
/*N*/       aMsg += GetInterface()->GetName();
/*N*/       aMsg += " bMDI ";
/*N*/       if ( bMDI ) aMsg += "MDI";
/*N*/       DbgTrace( aMsg.GetBuffer() );
/*N*/ #endif

    // nur wenn er vom Frame kommt (nicht z.B. pop der BASIC-IDE vom AppDisp)
/*N*/   if ( bMDI && pImp->pFrame == pFrame )
/*N*/   {
/*N*/       // austragen
/*N*/       pImp->pFrame = 0;
/*N*/       pImp->bActive = FALSE;
/*N*/   }
/*N*/
/*N*/   // Subklasse benachrichtigen
/*N*/   Deactivate(bMDI);
/*N*/ }

//--------------------------------------------------------------------

/*N*/ BOOL SfxShell::IsActive() const
/*N*/ {
/*N*/   return pImp->bActive;
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void SfxShell::Activate
/*N*/ (
/*N*/   BOOL    bMDI        /*  TRUE
                            der <SfxDispatcher>, auf dem die SfxShell sich
                            befindet, ist aktiv geworden oder die SfxShell
                            Instanz wurde auf einen aktiven SfxDispatcher
                            gepusht. (vergl. SystemWindow::IsMDIActivate())

                            FALSE
                            das zum <SfxViewFrame>, auf dessen SfxDispatcher
                            sich die SfxShell Instanz befindet, wurde
                            aktiviert.
                            (z.B. durch einen geschlossenen Dialog) */
/*N*/ )

/*  [Beschreibung]

    Virtuelle Methode, die beim Aktivieren der SfxShell Instanz gerufen
    wird, um den Subclasses die Gelegenheit zu geben, auf das Aktivieren
    zu reagieren.

    Die Basisimplementation ist leer und braucht nicht gerufen zu werden.


    [Querverweise]
    StarView SystemWindow::Activate(BOOL)
*/

/*N*/ {
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void SfxShell::Deactivate
/*N*/ (
/*N*/   BOOL    bMDI        /*  TRUE
                            der <SfxDispatcher>, auf dem die SfxShell sich
                            befindet, ist inaktiv geworden oder die SfxShell
                            Instanz wurde auf einen aktiven SfxDispatcher
                            gepoppt. (vergl. SystemWindow::IsMDIActivate())

                            FALSE
                            das zum <SfxViewFrame>, auf dessen SfxDispatcher
                            sich die SfxShell Instanz befindet, wurde
                            deaktiviert. (z.B. durch einen Dialog) */

/*N*/ )

/*  [Beschreibung]

    Virtuelle Methode, die beim Deaktivieren der SfxShell Instanz gerufen
    wird, um den Subclasses die Gelegenheit zu geben, auf das Deaktivieren
    zu reagieren.

    Die Basisimplementation ist leer und braucht nicht gerufen zu werden.


    [Querverweise]
    StarView SystemWindow::Dectivate(BOOL)
*/

/*N*/ {
/*N*/ }

/*N*/ void SfxShell::ParentActivate
/*N*/ (
/*N*/ )

/*  [Beschreibung]

    Ein Parent des <SfxDispatcher>, auf dem die SfxShell sich befindet,
    ist aktiv geworden, oder die SfxShell Instanz wurde auf einen
    <SfxDispatcher> gepusht, dessen parent aktiv ist.

    Die Basisimplementation ist leer und braucht nicht gerufen zu werden.

    [Querverweise]
    SfxShell::Activate()
*/
/*N*/ {
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void SfxShell::ParentDeactivate
/*N*/ (
/*N*/ )

/*  [Beschreibung]

    Der aktive Parent des <SfxDispatcher>, auf dem die SfxShell sich befindet,
    ist deaktiviert worden.

    Die Basisimplementation ist leer und braucht nicht gerufen zu werden.

    [Querverweise]
    SfxShell::Deactivate()
*/
/*N*/ {
/*N*/ }

//--------------------------------------------------------------------
#if 0
// falls noch mal "pure virtual function called" auf dem MAC:
//  Bitte MAC nicht mehr unterstuetzen
// der MPW-Linker will die immer haben, obwohl pure virtual

#ifdef MAC
extern "C"
{
    void debugstr( char *pMsg );
}
#endif

SfxItemPool& SfxShell::GetPool()
{
    debugstr( "pure virtual function called: SfxShell::GetPool()" );
    SfxItemPool aPool(0,0);
    return aPool;
}

#endif

//--------------------------------------------------------------------

/*N*/ void SfxShell::FillStatusBar( StatusBar& )

/*  [Beschreibung]

    Mit dieser Factory-Methode kann der Applikationsprogrammierer einer
    SfxShell-Subklasse eine eigene Statusbar zuweisen. Der SFx bevorzugt
    jeweils die Statusbar einer weiter oben auf den <SfxDispatcher>-Stack
    liegenden SfxShell.

    Die Basisimplementation ist leer und braucht nicht gerufen zu werden.

*/

/*N*/ {
/*N*/ }

//--------------------------------------------------------------------

/*N*/ ResMgr* SfxShell::GetResMgr() const

/*  [Beschreibung]

    Diese Methode liefert den ResMgr der <Resource-DLL>, die von der
    SfxShell-Instanz verwendet wird. Ist dies ein 0-Pointer, so
    ist der aktuelle Resource-Manager zu verwenden.
*/

/*N*/ {
/*N*/   return GetInterface()->GetResMgr();
/*N*/ }

//--------------------------------------------------------------------

/*N*/ FASTBOOL SfxShell::CanExecuteSlot_Impl( const SfxSlot &rSlot )

/*  [Beschreibung]

    Diese Methode stellt durch Aufruf der Statusfunktion fest,
    ob 'rSlot' aktuell ausgef"uhrt werden kann.
*/
/*N*/ {
/*N*/   // Slot-Status holen
/*N*/   SfxItemPool &rPool = GetPool();
/*N*/   const USHORT nId = rSlot.GetWhich( rPool );
/*N*/   SfxItemSet aSet(rPool, nId, nId);
/*N*/   SfxStateFunc pFunc = rSlot.GetStateFnc();
/*N*/   CallState( pFunc, aSet );
/*N*/   return aSet.GetItemState(nId) != SFX_ITEM_DISABLED;
/*N*/ }

//--------------------------------------------------------------------
#if 0
ULONG SfxShell::ExecuteSlot
(
    USHORT              nSlot,      // In: auszuf"uhrender Slot
    USHORT              nMemberId,  // In: MemberId f"ur strukturierte Items
    SbxVariable&        rRet,       // Out: Returnwert
    SbxBase*            pArgs       // In: 0, einzelner Parameter/Parameterliste
)

/*  [Beschreibung]

    Methode zum Ausf"uhren eines <SfxSlot>s von einem SfxShellObject
    (BASIC oder andere API).

    Aufrufe von APIs werden nicht recorded (ist ja auch kein <SfxDispatcher>).


    [R"uckgabewert]

    ULONG                       ErrorCode
*/

{
    // Slot suchen
    const SfxSlot *pSlot = GetInterface()->GetSlot(nSlot);
    if ( !pSlot )
        return SbxERR_PROC_UNDEFINED;

    // ggf. disabled
    if ( !pSlot->IsMode(SFX_SLOT_FASTCALL) && !CanExecuteSlot_Impl(*pSlot) )
        return SbERR_METHOD_FAILED;

    // "ofters ben"otigte Werte
    SfxItemPool &rPool = GetPool();
    SfxMapUnit eUserMetric = SFX_APP()->GetOptions().GetUserMetric();

    // Returnwert zum sp"ateren Aufbereiten als SbxVariable merken
    BOOL bDone = FALSE; // Return nur auswerten, wenn nicht abgebrochen wurde
    const SfxPoolItem *pRetItem = 0;
    SbxObject *pOwnObject = GetSbxObject(); // Hack fuer #22783

    // aktuelle Parameter oder Property (impliziter Parameter)?
    if ( pArgs || pSlot->IsMode(SFX_SLOT_PROPSET) )
    {
        // aktuelle Parameter in diesem ItemSet sammeln
        SfxAllItemSet aSet( rPool );

        // mehrere Parameter?
        if ( pSlot->IsMode(SFX_SLOT_METHOD) )
        {
            // das kann nur ein Methoden-Slot sein
            DBG_ASSERT( !pArgs || pArgs->ISA(SbxArray), "not an SbxArray as arguments" );

            // "uber die formalen Parameter iterieren
            USHORT nFormalArgs = pSlot->GetFormalArgumentCount();
            USHORT nActualArgs = pArgs ? ((SbxArray*)pArgs)->Count() - 1 : 0;
            USHORT nBasicArg = 0;
            for ( USHORT nArg = 0;
                  nArg < nFormalArgs && nBasicArg < nActualArgs;
                  ++nArg )
            {
                // formale Paramterbeschreibung besorgen
                const SfxFormalArgument &rArg = pSlot->GetFormalArgument(nArg);

                // Item per Factory erzeugen
                SfxPoolItem *pItem = rArg.CreateItem();
                DBG_ASSERT( pItem, "item without factory" );
                pItem->SetWhich( rPool.GetWhich(rArg.nSlotId) );

                // Konvertieren / ggf. strukturierte Items zusammensetzen
                ULONG eErr = 0;
                USHORT nSubCount = rArg.pType->nAttribs;
                if ( !nSubCount )
                {
                    // einfaches Item
                    SbxVariable *pSubArg = ((SbxArray*)pArgs)->Get(++nBasicArg);
                    eErr = rPool.SetVariable( *pItem, *pSubArg, eUserMetric );
                }
                else
                {
                    // strukturiertes Item
                    for ( USHORT n = 1; n <= nSubCount && !eErr; ++n )
                    {
                        SbxVariable *pSubArg = ((SbxArray*)pArgs)->Get(++nBasicArg);
                        pSubArg->SetUserData(
                                    long(rArg.pType->aAttrib[n-1].nAID) << 20 );
                        eErr = rPool.SetVariable( *pItem, *pSubArg, eUserMetric );
                    }
                }

                // falls Item erzeugt werden konnte, an Request anh"angen
                if ( 0 == eErr )
                    aSet.Put( *pItem,pItem->Which() );
                delete pItem; //! Optimieren (Put mit direkter Uebernahme)
                if ( 0 != eErr )
                    return eErr;
            }

            // nicht alle Parameter abger"aumt (zuviele)?
            if ( nBasicArg < nActualArgs )
                return SbxERR_WRONG_ARGS;
        }
        else
        {
            // Instanz von SfxPoolItem-Subklasse besorgen/erzeugen
            SfxPoolItem *pItem = 0;

            // Teil eines strukturiertes Items?
            if ( nMemberId )
            {
                //  => Status-Item besorgen
                const SfxPoolItem *pState = GetSlotState(nSlot);
                if ( pState && !pState->ISA(SfxVoidItem) )
                    pItem = pState->Clone();
            }

            // kein StatusItem oder einfaches/komplexes Item
            if ( !pItem )
            {
                // per Factory erzeugen
                pItem = pSlot->GetType()->CreateItem();
                DBG_ASSERT( pItem, "item without factory" );
                pItem->SetWhich( rPool.GetWhich(nSlot) );
            }

            // Daten aus Variable in das Item "ubertragen
            ULONG eErr = rPool.SetVariable( *pItem, rRet, eUserMetric );
            if ( 0 == eErr )
                aSet.Put( *pItem,pItem->Which() );
            delete pItem; //! Optimieren (Put mit direkter Uebernahme)
            if ( 0 != eErr )
                return eErr;
        }

        // via Request mit 'normaler' Execute-Methode ausf"uhren
        SfxRequest aReq( nSlot, SFX_CALLMODE_API, aSet );
        aSet.ClearItem(); // pPool k"onnte in _Execute sterben
        SfxExecFunc pFunc = pSlot->GetExecFnc();
        CallExec( pFunc, aReq );
        bDone = aReq.IsDone();
        pRetItem = aReq.GetReturnValue();
    }
    else
    {
        // ohne Parameter direkt ausf"uhren
        SfxRequest aReq( nSlot, SFX_CALLMODE_API, GetPool() );
//      SfxRequest aReq( nSlot, GetPool(), TRUE );
        SfxExecFunc pFunc = pSlot->GetExecFnc();
        CallExec( pFunc, aReq );
        bDone = aReq.IsDone();
        pRetItem = aReq.GetReturnValue();
    }

    // in IDL ein Return-Wert angegeben?
    if ( pSlot->IsMode(SFX_SLOT_METHOD) && rRet.GetType() != SbxVOID )
    {
        // ist aber kein Returnwert gesetzt worden?
        if ( !pRetItem || pRetItem->ISA(SfxVoidItem) )
        {
            // Ignore ohne Parameter ist erlaubt und auch normal
            if ( !bDone )
                return 0;

            // sonst mu\s einer gesetzt worden sein
            DBG_ERROR( "IDL hat Return-Wert, Execute-Methode setzt aber keinen!" );
            return SbxERR_CONVERSION;
        }

        // Returnwert in SbxVariable packen
        HACK( #22783 - lebt *this noch? )
        if ( ((SfxShellObject*)pOwnObject)->GetShell() )
            GetPool().FillVariable( *pRetItem, rRet, eUserMetric );
        else
            pRetItem->FillVariable( rRet, eUserMetric, eUserMetric );
    }

    return 0;
}
#endif

/*?*/ long ShellCall_Impl( void* pObj, void* pArg )
/*?*/ {
DBG_BF_ASSERT(0, "STRIP"); //STRIP001   ((SfxShell* )pObj)->ExecuteSlot( *(SfxRequest*)pArg, (SfxInterface*)0L );
/*?*/   return 0;
/*N*/ }

/*  [Beschreibung]
    Asynchrones ExecuteSlot fuer das RELOAD
 */

//--------------------------------------------------------------------
/*?*/ const SfxPoolItem* SfxShell::ExecuteSlot( SfxRequest& rReq, BOOL bAsync )
/*?*/ {DBG_BF_ASSERT(0, "STRIP");return 0; //STRIP001
/*?*/ }

/*N*/ const SfxPoolItem* SfxShell::ExecuteSlot
/*N*/ (
/*N*/   SfxRequest &rReq,           // der weiterzuleitende <SfxRequest>
/*N*/   const SfxInterface* pIF     // default = 0 bedeutet virtuell besorgen
/*N*/ )

/*  [Beschreibung]

    Diese Methode erm"oglicht das Weiterleiten eines <SfxRequest> an
    die angegebene Basis-<SfxShell>.


    [Beispiel]

    In einer von SfxViewShell abgeleiteten Klasse soll SID_PRINTDOCDIRECT
    abgefangen werden. Unter bestimmten Umst"anden soll vor dem Drucken
    eine Abfrage erscheinen, und der Request soll ggf. abgebrochen werden.

    Dazu ist in der IDL dieser Subklasse der o.g. Slot einzutragen. Die
    Execute-Methode enth"alt dann skizziert:

    void SubViewShell::Exec( SfxRequest &rReq )
    {
        if ( rReq.GetSlot() == SID_PRINTDOCDIRECT )
        {
            'dialog'
            if ( 'condition' )
                ExecuteSlot( rReq, SfxViewShell::GetInterface() );
        }
    }

    Es braucht i.d.R. kein rReq.Done() gerufen zu werden, da das bereits
    die Implementierung der SfxViewShell erledigt bzw. abgebrochen wurde.


    [Querverweise]

    <SfxShell::GetSlotState(USHORT,const SfxInterface*,SfxItemSet*)>
*/

/*N*/ {
/*N*/   if ( !pIF )
/*N*/       pIF = GetInterface();
/*N*/
/*N*/     USHORT nSlot = rReq.GetSlot();
/*N*/     const SfxSlot* pSlot = NULL;
/*N*/     if ( nSlot >= SID_VERB_START && nSlot <= SID_VERB_END )
/*?*/         pSlot = GetVerbSlot_Impl(nSlot);
/*N*/     if ( !pSlot )
/*N*/         pSlot = pIF->GetSlot(nSlot);
/*N*/     if ( !pSlot && SfxMacroConfig::IsMacroSlot( nSlot ) )
/*N*/   {
/*?*/       SfxMacroInfo* pInfo = SFX_APP()->GetMacroConfig()->GetMacroInfo(nSlot);
/*?*/       if ( pInfo )
/*?*/           pSlot = pInfo->GetSlot();
/*N*/   }
/*N*/
/*N*/   DBG_ASSERT( pSlot, "slot not supported" );
/*N*/
/*N*/   SfxExecFunc pFunc = pSlot->GetExecFnc();
/*N*/     if ( pFunc )
/*N*/         CallExec( pFunc, rReq );
/*N*/
/*N*/   return rReq.GetReturnValue();
/*N*/ }

//--------------------------------------------------------------------

/*N*/ const SfxPoolItem* SfxShell::GetSlotState
/*N*/ (
/*N*/   USHORT              nSlotId,    // Slot-Id des zu befragenden Slots
/*N*/   const SfxInterface* pIF,        // default = 0 bedeutet virtuell besorgen
/*N*/   SfxItemSet*         pStateSet   // SfxItemSet der Slot-State-Methode
/*N*/ )

/*  [Beschreibung]

    Diese Methode liefert den Status des Slots mit der angegebenen Slot-Id
    "uber das angegebene Interface.

    Ist der Slot disabled oder in dieser SfxShell (und deren Parent-Shells)
    nicht bekannt, wird ein 0-Pointer zur"uckgeliefert.

    Hat der Slot keinen Status, wird ein SfxVoidItem zur"uckgeliefert.

    Der Status wird bei pStateSet != 0 gleich in diesem Set gesetzt, so
    da\s <SfxShell>-Subklassen Slots-"uberladen und auch bei der
    Status-Methode die Basis-Implementierung rufen k"onnen.


    [Beispiel]

    In einer von SfxViewShell abgeleiteten Klasse soll SID_PRINTDOCDIRECT
    abgefangen werden. Unter bestimmten Umst"anden soll vor dem Drucken
    eine Abfrage erscheinen, und der Request soll ggf. abgebrochen werden.

    Dazu ist in der IDL dieser Subklasse der o.g. Slot einzutragen. Die
    Status-Methode enth"alt dann skizziert:

    void SubViewShell::PrintState( SfxItemSet &rState )
    {
        if ( rState.GetItemState( SID_PRINTDOCDIRECT ) != SFX_ITEM_UNKNOWN )
            GetSlotState( SID_PRINTDOCDIRECT, SfxViewShell::GetInterface(),
                    &rState );
        ...
    }


    [Querverweise]

    <SfxShell::ExecuteSlot(SfxRequest&)>
*/

/*N*/ {
/*N*/   // Slot am angegebenen Interface besorgen
/*N*/   if ( !pIF )
/*N*/       pIF = GetInterface();
/*N*/   SfxItemState eState;
/*N*/   SfxItemPool &rPool = GetPool();
/*N*/
/*N*/     const SfxSlot* pSlot = NULL;
/*N*/     if ( nSlotId >= SID_VERB_START && nSlotId <= SID_VERB_END )
/*?*/         pSlot = GetVerbSlot_Impl(nSlotId);
/*N*/     if ( !pSlot )
/*N*/         pSlot = pIF->GetSlot(nSlotId);
/*N*/     if ( !pSlot && SfxMacroConfig::IsMacroSlot( nSlotId ) )
/*N*/   {
/*N*/       SfxMacroInfo* pInfo = SFX_APP()->GetMacroConfig()->GetMacroInfo(nSlotId);
/*N*/       if ( pInfo )
/*N*/           pSlot = pInfo->GetSlot();
/*N*/   }
/*N*/
/*N*/   if ( pSlot )
/*N*/       // ggf. auf Which-Id mappen
/*N*/       nSlotId = pSlot->GetWhich( rPool );
/*N*/
/*N*/   // Item und Item-Status besorgen
/*N*/   const SfxPoolItem *pItem;
/*N*/   SfxItemSet aSet( rPool, nSlotId, nSlotId ); // pItem stirbt sonst zu fr"uh
/*N*/   if ( pSlot )
/*N*/   {
/*N*/       // Status-Methode rufen
/*N*/       SfxStateFunc pFunc = pSlot->GetStateFnc();
/*N*/         if ( pFunc )
/*N*/             CallState( pFunc, aSet );
/*N*/       eState = aSet.GetItemState( nSlotId, TRUE, &pItem );
/*N*/
/*N*/       // ggf. Default-Item besorgen
/*N*/       if ( eState == SFX_ITEM_DEFAULT )
/*N*/       {
/*N*/           if ( SfxItemPool::IsWhich(nSlotId) )
/*?*/               pItem = &rPool.GetDefaultItem(nSlotId);
/*N*/           else
/*N*/               eState = SFX_ITEM_DONTCARE;
/*N*/       }
/*N*/   }
/*N*/   else
/*N*/       eState = SFX_ITEM_UNKNOWN;
/*N*/
/*N*/   // Item und Item-Status auswerten und ggf. in pStateSet mitpflegen
/*N*/   SfxPoolItem *pRetItem = 0;
/*N*/   if ( eState <= SFX_ITEM_DISABLED )
/*N*/   {
/*N*/       if ( pStateSet )
/*N*/           pStateSet->DisableItem(nSlotId);
/*N*/       return 0;
/*N*/   }
/*N*/   else if ( eState == SFX_ITEM_DONTCARE )
/*N*/   {
/*N*/       if ( pStateSet )
/*N*/           pStateSet->ClearItem(nSlotId);
/*N*/       pRetItem = new SfxVoidItem(0);
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       if ( pStateSet && pStateSet->Put( *pItem ) )
/*N*/           return &pStateSet->Get( pItem->Which() );
/*N*/       pRetItem = pItem->Clone();
/*N*/   }
/*N*/   DeleteItemOnIdle(pRetItem);
/*N*/
/*N*/   return pRetItem;
/*N*/ }

//--------------------------------------------------------------------



/*N*/ void SfxShell::SetVerbs(const SvVerbList* pVerbs)
/*N*/ {
/*N*/   SfxViewShell *pViewSh = PTR_CAST ( SfxViewShell, this);
/*N*/
/*N*/   DBG_ASSERT(pViewSh, "SetVerbs nur an der ViewShell aufrufen!");
/*N*/
/*N*/   if (pImp->pVerbs)
/*N*/   {
/*?*/       // Zun"achst alle Statecaches dirty machen, damit keiner mehr versucht,
/*?*/       // die Slots zu benutzen
/*?*/
/*?*/       SfxBindings *pBindings =
/*?*/           pViewSh->GetViewFrame()->GetDispatcher()->GetBindings();
/*?*/       USHORT nCount = pImp->pVerbs->aSlotArr.Count();
/*?*/       for (USHORT n=0; n<nCount ; n++)
/*?*/       {
/*?*/           USHORT nId = SID_VERB_START + n;
/*?*/           pBindings->Invalidate(nId, FALSE, TRUE);
/*?*/       }
/*?*/
/*?*/       DELETEZ (pImp->pVerbs);
/*N*/   }
/*N*/
/*N*/   if (pVerbs)
/*?*/       pImp->pVerbs = new SfxVerbList();
/*N*/
/*N*/   if (pVerbs)
/*N*/   {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/   }
/*N*/
/*N*/   if (pViewSh)
/*N*/   {
/*N*/       // Der Status von SID_OBJECT wird im Controller direkt an der Shell
/*N*/       // abgeholt, es reicht also, ein neues StatusUpdate anzuregen
/*N*/       SfxBindings *pBindings = pViewSh->GetViewFrame()->GetDispatcher()->
/*N*/               GetBindings();
/*N*/       pBindings->Invalidate( SID_OBJECT, TRUE, TRUE );
/*N*/   }
/*N*/ }

//--------------------------------------------------------------------

/*?*/ const SvVerbList* SfxShell::GetVerbs() const
/*?*/ {
/*?*/ DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001    return pImp->pVerbs ? &pImp->pVerbs->aVerbList : 0;
/*?*/ }

//--------------------------------------------------------------------

/*N*/ void SfxShell::VerbExec(SfxRequest& rReq)
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/ }

//--------------------------------------------------------------------

/*?*/ void SfxShell::VerbState(SfxItemSet &rSet)
/*?*/ {
/*?*/ }

//--------------------------------------------------------------------

/*?*/ const SfxSlot* SfxShell::GetVerbSlot_Impl(USHORT nId) const
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*?*/       return 0;
/*?*/ }

//--------------------------------------------------------------------

/*N*/ void SfxShell::SetHelpId(ULONG nId)
/*N*/ {
/*N*/   pImp->nHelpId = nId;
/*N*/ }

//--------------------------------------------------------------------

/*N*/ ULONG SfxShell::GetHelpId() const
/*N*/ {
/*N*/   return pImp->nHelpId;
/*N*/ }

//--------------------------------------------------------------------

/*?*/ SfxObjectShell* SfxShell::GetObjectShell()
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*?*/       return NULL;
/*?*/ }

//--------------------------------------------------------------------

/*N*/ SfxSlotPool& SfxShell::GetSlotPool_Impl() const
/*N*/ {
/*N*/   return SFX_APP()->GetSlotPool( GetFrame() );
/*N*/ }

/*N*/ sal_Bool SfxShell::HasUIFeature( sal_uInt32 )
/*N*/ {
/*N*/   return sal_False;
/*N*/ }

/*N*/ long DispatcherUpdate_Impl( void* pObj, void* pArg )
/*N*/ {
/*N*/   ((SfxDispatcher*) pArg)->Update_Impl( TRUE );
/*N*/     ((SfxDispatcher*) pArg)->GetBindings()->InvalidateAll(FALSE);
/*N*/   return 0;
/*N*/ }

/*N*/ void SfxShell::UIFeatureChanged()
/*N*/ {
/*N*/   SfxViewFrame *pFrame = GetFrame();
/*N*/   if ( pFrame && pFrame->IsVisible() )
/*N*/   {
/*N*/       // Auch dann Update erzwingen, wenn Dispatcher schon geupdated ist,
/*N*/       // sonst bleibt evtl. irgendwas in den gebunkerten Tools stecken.
/*N*/       // Asynchron aufrufen, um Rekursionen zu vermeiden
/*N*/       if ( !pImp->pUpdater )
/*N*/             pImp->pUpdater = new svtools::AsynchronLink( Link( this, DispatcherUpdate_Impl ) );
/*N*/
/*N*/       // Mehrfachaufrufe gestattet
/*N*/       pImp->pUpdater->Call( pFrame->GetDispatcher(), TRUE );
/*N*/   }
/*N*/ }

/*N*/ void SfxShell::SetDisableFlags( ULONG nFlags )
/*N*/ {
/*N*/   pImp->nDisableFlags = nFlags;
/*N*/ }

/*N*/ ULONG SfxShell::GetDisableFlags() const
/*N*/ {
/*N*/   return pImp->nDisableFlags;
/*N*/ }

/*N*/ SfxItemSet*   SfxShell::CreateItemSet( USHORT nId )
/*N*/ {
/*N*/   return NULL;
/*N*/ }

/*N*/ void SfxShell::ApplyItemSet( USHORT nId, const SfxItemSet& rSet )
/*N*/ {
/*N*/ }

/*N*/ void SfxShell::SetViewShell_Impl( SfxViewShell* pView )
/*N*/ {
/*N*/     pImp->pViewSh = pView;
/*N*/ }



}
