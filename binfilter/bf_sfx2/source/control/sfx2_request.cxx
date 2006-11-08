/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sfx2_request.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: kz $ $Date: 2006-11-08 12:26:01 $
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

#ifndef _SFXITEMITER_HXX //autogen
#include <svtools/itemiter.hxx>
#endif

#ifndef _ARGS_HXX //autogen
#include <svtools/itempool.hxx>
#endif

#ifndef _SVTOOLS_ITEMDEL_HXX
#include <svtools/itemdel.hxx>
#endif

#pragma hdrstop

#include "request.hxx"
#include "dispatch.hxx"
#include "viewfrm.hxx"
#include "objface.hxx"


#include "appuno.hxx"

namespace binfilter {

//===================================================================

/*N*/ using namespace ::com::sun::star;

/*N*/ struct SfxRequest_Impl: public SfxListener

/*  [Beschreibung]

    Implementations-Struktur der Klasse <SfxRequest>.
*/

/*N*/ {
/*N*/   SfxRequest*         pAnti;       // Owner wegen sterbendem Pool
/*N*/   String              aTarget;     // ggf. von App gesetztes Zielobjekt
/*N*/   SfxItemPool*        pPool;       // ItemSet mit diesem Pool bauen
/*N*/   SfxPoolItem*        pRetVal;     // R"uckgabewert geh"ort sich selbst
/*N*/     SfxShell*           pShell;      // ausgef"uhrt an dieser Shell
/*N*/   const SfxSlot*      pSlot;       // ausgef"uhrter Slot
/*N*/   USHORT              nModifier;   // welche Modifier waren gedrueckt?
/*N*/   BOOL                bDone;       // "uberhaupt ausgef"uhrt
/*N*/   BOOL                bIgnored;    // vom User abgebrochen
/*N*/   BOOL                bCancelled;  // nicht mehr zustellen
/*N*/   BOOL                bUseTarget;  // aTarget wurde von Applikation gesetzt
/*N*/   USHORT              nCallMode;   // Synch/Asynch/API/Record
/*N*/     BOOL                bAllowRecording;
/*N*/   SfxAllItemSet*      pInternalArgs;
/*N*/     SfxViewFrame*       pViewFrame;
/*N*/
/*N*/     ::com::sun::star::uno::Reference< ::com::sun::star::frame::XDispatchRecorder > xRecorder;
/*N*/
/*N*/                       SfxRequest_Impl( SfxRequest *pOwner )
/*N*/                       : pAnti( pOwner), bCancelled(FALSE),
/*N*/                         nCallMode( SFX_CALLMODE_SYNCHRON ), nModifier(0),
/*N*/                           pPool(0), pInternalArgs( 0 ), bAllowRecording( FALSE ), pViewFrame(0)
/*N*/                       {}
/*N*/   ~SfxRequest_Impl() { delete pInternalArgs; }
/*N*/
/*N*/
/*N*/   void                SetPool( SfxItemPool *pNewPool );
/*N*/   virtual void        Notify( SfxBroadcaster &rBC, const SfxHint &rHint );
/*N*/     void                Record( const uno::Sequence < beans::PropertyValue >& rArgs );
/*N*/ };


//====================================================================

/*?*/ void SfxRequest_Impl::Notify( SfxBroadcaster &rBC, const SfxHint &rHint )
/*?*/ {
/*?*/   SfxSimpleHint *pSimpleHint = PTR_CAST(SfxSimpleHint, &rHint);
/*?*/   if ( pSimpleHint && pSimpleHint->GetId() == SFX_HINT_DYING )
/*?*/       pAnti->Cancel();
/*?*/ }

//====================================================================

/*N*/ void SfxRequest_Impl::SetPool( SfxItemPool *pNewPool )
/*N*/ {
/*N*/   if ( pNewPool != pPool )
/*N*/   {
/*N*/       if ( pPool )
/*?*/           EndListening( pPool->BC() );
/*N*/       pPool = pNewPool;
/*N*/       if ( pNewPool )
/*N*/           StartListening( pNewPool->BC() );
/*N*/   }
/*N*/ }

//====================================================================


/*N*/ SfxRequest::~SfxRequest()
/*N*/ {
/*N*/   DBG_MEMTEST();
/*N*/
/*N*/   // nicht mit Done() marktierte Requests mit 'rem' rausschreiben
/*N*/   if ( pImp->xRecorder.is() && !pImp->bDone && !pImp->bIgnored )
/*?*/         pImp->Record( uno::Sequence < beans::PropertyValue >() );
/*N*/
/*N*/   // Objekt abr"aumen
/*N*/   delete pArgs;
/*N*/   if ( pImp->pRetVal )
/*N*/       DeleteItemOnIdle(pImp->pRetVal);
/*N*/   delete pImp;
/*N*/ }
//--------------------------------------------------------------------


/*N*/ SfxRequest::SfxRequest
/*N*/ (
/*N*/   const SfxRequest& rOrig
/*N*/ )
/*N*/ : nSlot(rOrig.nSlot),
/*N*/   pArgs(rOrig.pArgs? new SfxAllItemSet(*rOrig.pArgs): 0),
/*N*/   pImp( new SfxRequest_Impl(this) )
/*N*/ {
/*N*/   DBG_MEMTEST();
/*N*/
/*N*/     pImp->bAllowRecording = rOrig.pImp->bAllowRecording;
/*N*/     pImp->bDone = FALSE;
/*N*/   pImp->bIgnored = FALSE;
/*N*/   pImp->pRetVal = 0;
/*N*/   pImp->pShell = 0;
/*N*/   pImp->pSlot = 0;
/*N*/   pImp->nCallMode = rOrig.pImp->nCallMode;
/*N*/   pImp->bUseTarget = rOrig.pImp->bUseTarget;
/*N*/   pImp->aTarget = rOrig.pImp->aTarget;
/*N*/   pImp->nModifier = rOrig.pImp->nModifier;
/*N*/
/*N*/   if ( pArgs )
/*N*/       pImp->SetPool( pArgs->GetPool() );
/*N*/   else
/*N*/       pImp->SetPool( rOrig.pImp->pPool );
/*N*/ }
//--------------------------------------------------------------------


/*?*/ SfxRequest::SfxRequest
/*?*/ (
/*?*/     SfxViewFrame*   pViewFrame,
/*?*/     USHORT          nSlotId
/*?*/
/*?*/ )

/*  [Beschreibung]

    Mit diesem Konstruktor k"onnen Events, die nicht "uber den SfxDispatcher
    gelaufen sind (z.B aus KeyInput() oder Mouse-Events) nachtr"aglich
    recorded werden. Dazu wird eine SfxRequest-Instanz mit diesem Konstruktor
    erzeugt und dann genauso verfahren, wie mit einem SfxRequest, der in
    eine <Slot-Execute-Methode> als Parameter gegeben wird.
*/

/*?*/ : nSlot(nSlotId),
/*?*/   pArgs(0),
/*?*/   pImp( new SfxRequest_Impl(this) )
/*?*/ {
/*?*/   DBG_MEMTEST();
/*?*/
/*?*/   pImp->bDone = FALSE;
/*?*/   pImp->bIgnored = FALSE;
/*?*/     pImp->SetPool( &pViewFrame->GetPool() );
/*?*/   pImp->pRetVal = 0;
/*?*/   pImp->pShell = 0;
/*?*/     pImp->pSlot = 0;
/*?*/   pImp->nCallMode = SFX_CALLMODE_SYNCHRON;
/*?*/   pImp->bUseTarget = FALSE;
/*?*/     pImp->pViewFrame = pViewFrame;
/*?*/     if( pImp->pViewFrame->GetDispatcher()->GetShellAndSlot_Impl( nSlotId, &pImp->pShell, &pImp->pSlot, TRUE, TRUE ) )
/*?*/     {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*?*/     }
/*?*/ #ifdef DBG_UTIL
/*?*/     else
/*?*/     {
/*?*/         ByteString aStr( "Recording unsupported slot: ");
/*?*/         aStr += ByteString::CreateFromInt32( pImp->pPool->GetSlotId(nSlotId) );
/*?*/         DBG_ERROR( aStr.GetBuffer() );
/*?*/     }
/*?*/ #endif
/*?*/ }

//--------------------------------------------------------------------


/*N*/ SfxRequest::SfxRequest
/*N*/ (
/*N*/   USHORT          nSlotId,    // auszuf"uhrende <Slot-Id>
/*N*/   SfxCallMode     nMode,      // Synch/API/...
/*N*/   SfxItemPool&    rPool       // ggf. f"ur das SfxItemSet f"ur Parameter
/*N*/ )

// creates a SfxRequest without arguments

/*N*/ : nSlot(nSlotId),
/*N*/   pArgs(0),
/*N*/   pImp( new SfxRequest_Impl(this) )
/*N*/ {
/*N*/   DBG_MEMTEST();
/*N*/
/*N*/   pImp->bDone = FALSE;
/*N*/   pImp->bIgnored = FALSE;
/*N*/   pImp->SetPool( &rPool );
/*N*/   pImp->pRetVal = 0;
/*N*/   pImp->pShell = 0;
/*N*/   pImp->pSlot = 0;
/*N*/   pImp->nCallMode = nMode;
/*N*/   pImp->bUseTarget = FALSE;
/*N*/ }

//-----------------------------------------------------------------------

/*N*/ SfxRequest::SfxRequest
/*N*/ (
/*N*/   USHORT                  nSlotId,
/*N*/   USHORT                  nMode,
/*N*/   const SfxAllItemSet&    rSfxArgs
/*N*/ )

// creates a SfxRequest with arguments

/*N*/ : nSlot(nSlotId),
/*N*/   pArgs(new SfxAllItemSet(rSfxArgs)),
/*N*/   pImp( new SfxRequest_Impl(this) )
/*N*/ {
/*N*/   DBG_MEMTEST();
/*N*/
/*N*/   pImp->bDone = FALSE;
/*N*/   pImp->bIgnored = FALSE;
/*N*/   pImp->SetPool( rSfxArgs.GetPool() );
/*N*/   pImp->pRetVal = 0;
/*N*/   pImp->pShell = 0;
/*N*/   pImp->pSlot = 0;
/*N*/   pImp->nCallMode = nMode;
/*N*/   pImp->bUseTarget = FALSE;
/*N*/ }
//--------------------------------------------------------------------

/*N*/ USHORT SfxRequest::GetCallMode() const
/*N*/ {
/*N*/   return pImp->nCallMode;
/*N*/ }

//--------------------------------------------------------------------

/*?*/ BOOL SfxRequest::IsSynchronCall() const
/*?*/ {
/*?*/   return SFX_CALLMODE_SYNCHRON == ( SFX_CALLMODE_SYNCHRON & pImp->nCallMode );
/*?*/ }

//--------------------------------------------------------------------

/*N*/ void SfxRequest::SetSynchronCall( BOOL bSynchron )
/*N*/ {
/*N*/   if ( bSynchron )
/*?*/       pImp->nCallMode |= SFX_CALLMODE_SYNCHRON;
/*N*/   else
/*N*/       pImp->nCallMode &= ~(USHORT) SFX_CALLMODE_SYNCHRON;
/*N*/ }

/*?*/ void SfxRequest::SetInternalArgs_Impl( const SfxAllItemSet& rArgs )
/*?*/ {
/*?*/   delete pImp->pInternalArgs;
/*?*/   pImp->pInternalArgs = new SfxAllItemSet( rArgs );
/*?*/ }

/*N*/ const SfxItemSet* SfxRequest::GetInternalArgs_Impl() const
/*N*/ {
/*N*/   return pImp->pInternalArgs;
/*N*/ }

//--------------------------------------------------------------------


/*?*/ void SfxRequest_Impl::Record
/*?*/ (
/*?*/     const uno::Sequence < beans::PropertyValue >& rArgs    // aktuelle Parameter
/*?*/ )

/*  [Beschreibung]

    Interne Hilfsmethode zum erzeugen einer <SfxMacroStatement>-Instanz,
    welche den bereits ausgef"uhrten SfxRequest wiederholbar beschreibt.

    Die erzeugte Instanz, auf die ein Pointer zur"uckgeliefert wird
    geht in das Eigentum des Aufrufers "uber.
*/

/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*?*/ }

//--------------------------------------------------------------------

/*?*/ void SfxRequest::Record_Impl
/*?*/ (
/*?*/     SfxShell& rSh,    // die <SfxShell>, die den Request ausgef"uhrt hat
/*?*/   const SfxSlot&  rSlot,  // der <SfxSlot>, der den Request ausgef"uhrt hat
/*?*/     ::com::sun::star::uno::Reference< ::com::sun::star::frame::XDispatchRecorder > xRecorder,  // der Recorder, mit dem aufgezeichnet wird
/*?*/     SfxViewFrame* pViewFrame
/*?*/ )

/*  [Beschreibung]

    Diese interne Methode markiert den SfxRequest als in dem angegebenen
    SfxMakro aufzuzeichnen.

    Pointer auf die Parameter werden in Done() wieder verwendet, m"usseb
    dann also noch leben.
*/

/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*?*/ }

//--------------------------------------------------------------------

/*?*/ void SfxRequest::SetArgs( const SfxAllItemSet& rArgs )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*?*/ }

//--------------------------------------------------------------------

/*N*/ void SfxRequest::AppendItem(const SfxPoolItem &rItem)
/*N*/ {
/*N*/   if(!pArgs)
/*?*/       pArgs = new SfxAllItemSet(*pImp->pPool);
/*N*/   pArgs->Put(rItem, rItem.Which());
/*N*/ }

//--------------------------------------------------------------------

/*?*/ void SfxRequest::RemoveItem( USHORT nID )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*?*/ }

//--------------------------------------------------------------------

/*N*/ const SfxPoolItem* SfxRequest::GetArg
/*N*/ (
/*N*/   USHORT          nSlotId,    // Slot-Id oder Which-Id des Parameters
/*N*/   FASTBOOL        bDeep,      // FALSE: nicht in Parent-ItemSets suchen
/*N*/   TypeId          aType       // != 0:  RTTI Pruefung mit Assertion
/*N*/ )     const
/*N*/ {
/*N*/   return GetItem( pArgs, nSlotId, bDeep, aType );
/*N*/ }


//--------------------------------------------------------------------
/*N*/ const SfxPoolItem* SfxRequest::GetItem
/*N*/ (
/*N*/   const SfxItemSet* pArgs,
/*N*/   USHORT          nSlotId,    // Slot-Id oder Which-Id des Parameters
/*N*/   FASTBOOL        bDeep,      // FALSE: nicht in Parent-ItemSets suchen
/*N*/   TypeId          aType       // != 0:  RTTI Pruefung mit Assertion
/*N*/ )

/*  [Beschreibung]

    Mit dieser Methode wird der Zugriff auf einzelne Parameter im
    SfxRequest wesentlich vereinfacht. Insbesondere wird die Typpr"ufung
    (per Assertion) durchgef"uhrt, wodurch die Applikations-Sourcen
    wesentlich "ubersichtlicher werden. In der PRODUCT-Version wird
    eine 0 zur"uckgegeben, wenn das gefundene Item nicht von der
    angegebenen Klasse ist.


    [Beispiel]

    void MyShell::Execute( SfxRequest &rReq )
    {
        switch ( rReq.GetSlot() )
        {
            case SID_MY:
            {
                ...
                // ein Beispiel ohne Verwendung des Makros
                const SfxInt32Item *pPosItem = (const SfxUInt32Item*)
                    rReq.GetArg( SID_POS, FALSE, TYPE(SfxInt32Item) );
                USHORT nPos = pPosItem ? pPosItem->GetValue() : 0;

                // ein Beispiel mit Verwendung des Makros
                SFX_REQUEST_ARG(rReq, pSizeItem, SfxInt32Item, SID_SIZE, FALSE);
                USHORT nSize = pSizeItem ? pPosItem->GetValue() : 0;

                ...
            }

            ...
        }
    }
*/

/*N*/ {
/*N*/   if ( pArgs )
/*N*/   {
/*N*/       // ggf. in Which-Id umrechnen
/*N*/       USHORT nWhich = pArgs->GetPool()->GetWhich(nSlotId);
/*N*/
/*N*/       // ist das Item gesetzt oder bei bDeep==TRUE verf"ugbar?
/*N*/       const SfxPoolItem *pItem = 0;
/*N*/       if ( ( bDeep ? SFX_ITEM_AVAILABLE : SFX_ITEM_SET )
/*N*/            <= pArgs->GetItemState( nWhich, bDeep, &pItem ) )
/*N*/       {
/*N*/           // stimmt der Typ "uberein?
/*N*/           if ( !pItem || pItem->IsA(aType) )
/*N*/               return pItem;
/*N*/
/*N*/           // Item da aber falsch => Programmierfehler
/*N*/           DBG_ERROR(  "invalid argument type" );
/*N*/       }
/*N*/   }
/*N*/
/*N*/   // keine Parameter, nicht gefunden oder falschen Typ gefunden
/*N*/   return 0;
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void SfxRequest::SetReturnValue(const SfxPoolItem &rItem)
/*N*/ {
/*N*/   DBG_ASSERT(!pImp->pRetVal, "Returnwert mehrfach setzen?");
/*N*/   if(pImp->pRetVal)
/*?*/       delete pImp->pRetVal;
/*N*/   pImp->pRetVal = rItem.Clone();
/*N*/ }

//--------------------------------------------------------------------

/*N*/ const SfxPoolItem* SfxRequest::GetReturnValue() const
/*N*/ {
/*N*/   return pImp->pRetVal;
/*N*/ }

//--------------------------------------------------------------------

/*?*/ void SfxRequest::Done
/*?*/ (
    const SfxItemSet&   rSet,   /*  von der Applikation mitgeteilte Parameter,
                                    die z.B. in einem Dialog vom Benuter
                                    erfragt wurden, ggf. 0 falls keine
                                    Parameter gesetzt wurden */

    FASTBOOL            bKeep   /*  TRUE (default)
                                    'rSet' wird gepeichert und ist "uber
                                    GetArgs() abfragbar

                                    FALSE
                                    'rSet' wird nicht kopiert (schneller) */
/*?*/ )

/*  [Beschreibung]

    Diese Methode mu\s in der <Execute-Methode> des <SfxSlot>s gerufen
    werden, der den SfxRequest ausgef"uhrt hat, wenn die Ausf"uhrung
    tats"achlich stattgefunden hat. Wird 'Done()' nicht gerufen, gilt
    der SfxRequest als abgebrochen.

    Etwaige Returnwerte werden nur durchgereicht, wenn 'Done()' gerufen
    wurde. Ebenso werden beim Aufzeichnen von Makros nur echte
    Statements erzeugt, wenn 'Done()' gerufen wurde; f"ur SfxRequests,
    die nicht derart gekennzeichnet wurden, wird anstelle dessen eine
    auf die abgebrochene Funktion hinweisende Bemerkung ('rem') eingf"ugt.


    [Anmerkung]

    'Done()' wird z.B. nicht gerufen, wenn ein durch die Funktion gestarteter
    Dialog vom Benutzer abgebrochen wurde oder das Ausf"uhren aufgrund
    eines falschen Kontextes (ohne Verwendung separater <SfxShell>s)
    nicht durchgef"uhrt werden konnte. 'Done()' mu\s sehr wohl gerufen
    werden, wenn das Ausf"uhren der Funktion zu einem regul"aren Fehler
    f"uhrte (z.B. Datei konnte nicht ge"offnet werden).
*/

/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*?*/ }

//--------------------------------------------------------------------


/*N*/ void SfxRequest::Done( BOOL bRelease )
/*N*/ //    [<SfxRequest::Done(SfxItemSet&)>]
/*N*/ {
/*N*/   Done_Impl( pArgs );
/*N*/   if( bRelease )
/*?*/       DELETEZ( pArgs );
/*N*/ }

//--------------------------------------------------------------------

/*N*/ BOOL SfxRequest::IsCancelled() const
/*N*/ {
/*N*/   return pImp->bCancelled;
/*N*/ }

//--------------------------------------------------------------------

/*?*/ void SfxRequest::Cancel()

/*  [Beschreibung]

    Markiert diesen Request als nicht mehr auszufuehren. Wird z.B. gerufen,
    wenn das Ziel (genauer dessen Pool) stirbt.
*/

/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*?*/ }

//--------------------------------------------------------------------


/*N*/ void SfxRequest::Ignore()

/*  [Beschreibung]

    Wird diese Methode anstelle von <SfxRequest::Done()> gerufen, dann
    wird dieser Request nicht recorded.


    [Bespiel]

    Das Selektieren von Tools im StarDraw soll nicht aufgezeichnet werden,
    dieselben Slots sollen aber zum erzeugen der von den Tools zu
    erzeugenden Objekte verwendet werde. Also kann nicht NoRecord
    angegeben werden, dennoch soll u.U. nicht aufgezeichnet werden.
*/

/*N*/ {
/*N*/   // als tats"achlich ausgef"uhrt markieren
/*N*/   pImp->bIgnored = TRUE;
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void SfxRequest::Done_Impl
/*N*/ (
    const SfxItemSet*   pSet    /*  von der Applikation mitgeteilte Parameter,
                                    die z.B. in einem Dialog vom Benuter
                                    erfragt wurden, ggf. 0 falls keine
                                    Parameter gesetzt wurden */
/*N*/ )

/*  [Beschreibung]

    Interne Methode zum als 'done' markieren des SfxRequest und zum Auswerten
    der Parameter in 'pSet' falls aufgezeichnet wird.
*/

/*N*/ {
/*N*/   // als tats"achlich ausgef"uhrt markieren
/*N*/   pImp->bDone = TRUE;
/*N*/
/*N*/   // nicht Recorden
/*N*/   if ( !pImp->xRecorder.is() )
/*N*/       return;
/*N*/
/*N*/   // wurde ein anderer Slot ausgef"uhrt als angefordert (Delegation)
/*N*/   if ( nSlot != pImp->pSlot->GetSlotId() )
/*N*/   {
/*N*/       // Slot neu suchen
/*N*/       pImp->pSlot = pImp->pShell->GetInterface()->GetSlot(nSlot);
/*N*/       DBG_ASSERT( pImp->pSlot, "delegated SlotId not found" );
/*N*/       if ( !pImp->pSlot ) // Hosentr"ger und G"urtel
/*N*/           return;
/*N*/   }

    // record-f"ahig?
    // neues Recorden verwendet UnoName!
/*?*/     if ( !pImp->pSlot->pUnoName )
/*?*/     {
/*?*/         ByteString aStr( "Recording not exported slot: ");
/*?*/         aStr += ByteString::CreateFromInt32( pImp->pSlot->GetSlotId() );
/*?*/         DBG_ERROR( aStr.GetBuffer() );
/*?*/     }
/*?*/
/*?*/     if ( !pImp->pSlot->pUnoName ) // Hosentr"ger und G"urtel
/*?*/         return;
/*?*/
/*?*/   // "ofters ben"otigte Werte
/*?*/   SfxItemPool &rPool = pImp->pShell->GetPool();
/*?*/
/*?*/   // Property-Slot?
/*?*/   if ( !pImp->pSlot->IsMode(SFX_SLOT_METHOD) )
/*?*/   {
/*?*/       // des Property als SfxPoolItem besorgen
/*?*/       const SfxPoolItem *pItem;
/*?*/       USHORT nWhich = rPool.GetWhich(pImp->pSlot->GetSlotId());
/*?*/         SfxItemState eState = pSet ? pSet->GetItemState( nWhich, FALSE, &pItem ) : SFX_ITEM_UNKNOWN;
/*?*/ #ifdef DBG_UTIL
/*?*/         if ( SFX_ITEM_SET != eState )
/*?*/         {
/*?*/             ByteString aStr( "Recording property not available: ");
/*?*/             aStr += ByteString::CreateFromInt32( pImp->pSlot->GetSlotId() );
/*?*/             DBG_ERROR( aStr.GetBuffer() );
/*?*/         }
/*?*/ #endif
/*?*/         uno::Sequence < beans::PropertyValue > aSeq;
/*?*/       if ( eState == SFX_ITEM_SET )
/*?*/             TransformItems( pImp->pSlot->GetSlotId(), *pSet, aSeq, pImp->pSlot );
/*?*/         pImp->Record( aSeq );
/*?*/   }
/*?*/
/*?*/   // alles in ein einziges Statement aufzeichnen?
/*?*/   else if ( pImp->pSlot->IsMode(SFX_SLOT_RECORDPERSET) )
/*?*/   {
/*?*/         uno::Sequence < beans::PropertyValue > aSeq;
/*?*/         if ( pSet )
/*?*/             TransformItems( pImp->pSlot->GetSlotId(), *pSet, aSeq, pImp->pSlot );
/*?*/         pImp->Record( aSeq );
/*?*/   }
/*?*/
/*?*/   // jedes Item als einzelnes Statement recorden
/*?*/   else if ( pImp->pSlot->IsMode(SFX_SLOT_RECORDPERITEM) )
/*?*/   {
/*?*/       if ( pSet )
/*?*/       {
/*?*/           // "uber die Items iterieren
/*?*/           SfxItemIter aIter(*pSet);
/*?*/             for ( const SfxPoolItem* pItem = aIter.FirstItem(); pItem; pItem = aIter.NextItem() )
/*?*/           {
/*?*/               // die Slot-Id f"ur das einzelne Item ermitteln
/*?*/               USHORT nWhich = rPool.GetWhich( pItem->Which() );
/*?*/               USHORT nSlotId = rPool.GetSlotId( pItem->Which() );
/*?*/               if ( nSlotId == nSlot )
/*?*/               {
/*?*/                   // mit Hosentr"ager und G"urtel reparieren des falschen Flags
/*?*/                   DBG_ERROR( "recursion RecordPerItem - use RecordPerSet!" );
/*?*/                   SfxSlot *pSlot = (SfxSlot*) pImp->pSlot;
/*?*/                   pSlot->nFlags &= ~((ULONG)SFX_SLOT_RECORDPERITEM);
/*?*/                   pSlot->nFlags &=  SFX_SLOT_RECORDPERSET;
/*?*/               }
/*?*/
/*?*/               // einen Sub-Request recorden
/*?*/                 SfxRequest aReq( pImp->pViewFrame, nSlotId );
/*?*/                 if ( aReq.pImp->pSlot )
/*?*/                     aReq.AppendItem( *pItem );
/*?*/                 aReq.Done();
/*?*/           }
/*?*/       }
/*?*/       else
/*?*/       {
/*?*/           HACK(hierueber nochmal nachdenken)
/*?*/             pImp->Record( uno::Sequence < beans::PropertyValue >() );
/*?*/       }
/*?*/   }
/*N*/ }

//--------------------------------------------------------------------

/*N*/ BOOL SfxRequest::IsDone() const

/*  [Beschreibung]

    Mit dieser Methode kann abgefragt werden, ob der SfxRequest tats"achlich
    ausgef"uhrt wurde oder nicht. Wurde ein SfxRequest nicht ausgef"uhrt,
    liegt dies z.B. daran, da\s der Benutzer abgebrochen hat oder
    der Kontext f"ur diesen Request falsch war, dieses aber nicht "uber
    eine separate <SfxShell> realisiert wurde.

    SfxRequest-Instanzen, die hier FALSE liefern, werden nicht recorded.


    [Querverweise]

    <SfxRequest::Done(const SfxItemSet&)>
    <SfxRequest::Done()>
*/

/*N*/ {
/*N*/   return pImp->bDone;
/*N*/ }

//--------------------------------------------------------------------

/*?*/ SfxMacro* SfxRequest::GetRecordingMacro()

/*  [Beschreibung]

    Mit dieser Methode kann abgefragt werden, ob und in welchem <SfxMacro>
    die SfxRequests gerade aufgezeichnet werden.
*/

/*?*/ {
/*?*/     return NULL;
/*?*/ }

//--------------------------------------------------------------------


/*  [Beschreibung]

    Hier wird versucht einen Recorder fuer dispatch() Aufrufe vom Frame zu bekommen.
    Dieser ist dort per Property an einem Supplier verfuegbar - aber nur dann, wenn
    recording angeschaltet wurde.
    (Siehe auch SfxViewFrame::MiscExec_Impl() und SID_RECORDING)
*/




//--------------------------------------------------------------------

/*N*/ BOOL SfxRequest::IsAPI() const

/*  [Beschreibung]

    Liefert TRUE, wenn dieser SfxRequest von einer API (z.B. BASIC)
    erzeugt wurde, sonst FALSE.
*/

/*N*/ {
/*N*/   return SFX_CALLMODE_API == ( SFX_CALLMODE_API & pImp->nCallMode );
/*N*/ }

//--------------------------------------------------------------------



/*  [Beschreibung]

    Liefert TRUE, wenn dieser SfxRequest recorded werden soll, d.h.
    1. zu Zeit ein Makro aufgezeichnet wird
    2. dieser Request "uberhaupt aufgezeichnet wird
    3. der Request nicht von reiner API (z.B. BASIC) ausgeht,
    sonst FALSE.
*/


//--------------------------------------------------------------------
/*N*/ void SfxRequest::SetModifier( USHORT nModi )
/*N*/ {
/*N*/   pImp->nModifier = nModi;
/*N*/ }

//--------------------------------------------------------------------
/*N*/ USHORT SfxRequest::GetModifier() const
/*N*/ {
/*N*/   return pImp->nModifier;
/*N*/ }

//--------------------------------------------------------------------

/*?*/ void SfxRequest::SetTarget( const String &rTarget )

/*  [Beschreibung]

    Mit dieser Methode kann das zu recordende Zielobjekt umgesetzt werden.


    [Beispiel]

    Die BASIC-Methode 'Open' wird zwar von der Shell 'Application' ausgef"uhrt,
    aber am Objekt 'Documents' (global) recorded:

        rReq.SetTarget( "Documents" );

    Dies f"uhrt dann zu:

        Documents.Open( ... )
*/

/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/ }

/*N*/ void SfxRequest::AllowRecording( BOOL bSet )
/*N*/ {
/*N*/     pImp->bAllowRecording = bSet;
/*N*/ }

/*N*/ BOOL SfxRequest::AllowsRecording() const
/*N*/ {
/*N*/     BOOL bAllow = pImp->bAllowRecording;
/*N*/     if( !bAllow )
/*N*/         bAllow = ( SFX_CALLMODE_API != ( SFX_CALLMODE_API & pImp->nCallMode ) ) &&
/*N*/                  ( SFX_CALLMODE_RECORD == ( SFX_CALLMODE_RECORD & pImp->nCallMode ) );
/*N*/     return bAllow;
/*N*/ }
}
