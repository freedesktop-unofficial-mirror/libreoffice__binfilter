/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sfx2_objxtor.cxx,v $
 *
 *  $Revision: 1.12 $
 *
 *  last change: $Author: kz $ $Date: 2006-11-08 11:51:14 $
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

#include "arrdecl.hxx"

#ifndef _COM_SUN_STAR_UTIL_XCLOSEABLE_HPP_
#include <com/sun/star/util/XCloseable.hpp>
#endif

#ifndef _VOS_MUTEX_HXX_
#include <vos/mutex.hxx>
#endif

#ifndef _SV_RESARY_HXX
#include <tools/resary.hxx>
#endif
#ifndef _MSGBOX_HXX //autogen
#include <vcl/msgbox.hxx>
#endif
#ifndef _WRKWIN_HXX //autogen
#include <vcl/wrkwin.hxx>
#endif
#ifndef _SV_SVAPP_HXX
#include <vcl/svapp.hxx>
#endif
#ifndef _SFXENUMITEM_HXX //autogen
#include <svtools/eitem.hxx>
#endif
#ifndef _RTTI_HXX //autogen
#include <tools/rtti.hxx>
#endif
#ifndef _SFXLSTNER_HXX //autogen
#include <svtools/lstner.hxx>
#endif

#ifndef _SFX_HELP_HXX
#include <sfxhelp.hxx>
#endif
#ifndef _SB_SBSTAR_HXX //autogen
#include <basic/sbstar.hxx>
#endif
#ifndef _SFXSTRITEM_HXX
#include <svtools/stritem.hxx>
#endif
#pragma hdrstop

#ifndef _SBXCLASS_HXX //autogen
#include <basic/sbx.hxx>
#endif

#include "objsh.hxx"

#ifndef _BASIC_SBUNO_HXX
#include <basic/sbuno.hxx>
#endif

#ifndef _SFXECODE_HXX
#include <svtools/sfxecode.hxx>
#endif
#ifndef _EHDL_HXX
#include <svtools/ehdl.hxx>
#endif
#ifndef INCLUDED_SVTOOLS_PRINTWARNINGOPTIONS_HXX
#include <svtools/printwarningoptions.hxx>
#endif

#include <svtools/urihelper.hxx>
#include <svtools/pathoptions.hxx>
#include <unotools/localfilehelper.hxx>
#include <unotools/ucbhelper.hxx>
#include <svtools/asynclink.hxx>

#include "docfac.hxx"
#include "docfile.hxx"
#include "event.hxx"
#include "cfgmgr.hxx"
#include "dispatch.hxx"
#include "viewsh.hxx"
#include "interno.hxx"
#include "sfxresid.hxx"
#include "objshimp.hxx"
#include "appbas.hxx"
#include "sfxtypes.hxx"
#include "evntconf.hxx"
#include "request.hxx"
#include "doc.hrc"
#include "sfxlocal.hrc"
#include "docinf.hxx"
#include "objuno.hxx"
#include "appdata.hxx"
#include "appuno.hxx"
#include "sfxsids.hrc"
#include "basmgr.hxx"
#include "dlgcont.hxx"

#ifndef _BASMGR_HXX
#include <basic/basmgr.hxx>
#endif

#include "scriptcont.hxx"
#include "imgmgr.hxx"

#ifndef _SVTOOLS_IMGDEF_HXX
#include <svtools/imgdef.hxx>
#endif

#include "tbxconf.hxx"
#include "accmgr.hxx"
#include "helpid.hrc"

using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::script;

#ifndef _UNO_MAPPING_HXX_
#include <uno/mapping.hxx>
#endif

//====================================================================
#include "so3/staticbaseurl.hxx"
namespace binfilter {

/*N*/ DBG_NAME(SfxObjectShell)

#define DocumentInfo
#include "sfxslots.hxx"

extern ::svtools::AsynchronLink* pPendingCloser;
static SfxObjectShell* pWorkingDoc = NULL;

//=========================================================================

/*N*/ TYPEINIT1(SfxObjectShell, SfxShell);

//--------------------------------------------------------------------

/*N*/ SfxObjectShell_Impl::~SfxObjectShell_Impl()
/*N*/ {
/*N*/   if ( pPendingCloser == pCloser )
/*N*/       pPendingCloser = 0;
/*N*/   delete pCloser;
/*N*/ }

// initializes a document from a file-description

/*N*/ SfxObjectShell::SfxObjectShell
/*N*/ (
/*N*/   SfxObjectCreateMode eMode   /*  Zweck, zu dem die SfxObjectShell
                                    erzeugt wird:

                                    SFX_CREATE_MODE_EMBEDDED (default)
                                        als SO-Server aus einem anderen
                                        Dokument heraus

                                    SFX_CREATE_MODE_STANDARD,
                                        als normales, selbst"aendig ge"offnetes
                                        Dokument

                                    SFX_CREATE_MODE_PREVIEW
                                        um ein Preview durchzuf"uhren,
                                        ggf. werden weniger Daten ben"otigt

                                    SFX_CREATE_MODE_ORGANIZER
                                        um im Organizer dargestellt zu
                                        werden, hier werden keine Inhalte
                                        ben"otigt */
/*N*/ )

/*  [Beschreibung]

    Konstruktor der Klasse SfxObjectShell.
*/

/*N*/ : pImp( new SfxObjectShell_Impl ),
/*N*/   _pFactory( 0 ),
/*N*/   eCreateMode(eMode),
/*N*/   pStyleSheetPool(0),
/*N*/   pMedium(0)
/*N*/ {
/*N*/   DBG_CTOR(SfxObjectShell, 0);
/*N*/
/*N*/   bHasName = sal_False;
/*N*/   SfxShell::SetName( GetTitle() );
/*N*/   nViewNo = 0;

    // Aggregation InPlaceObject+Automation
//(mba)    AddInterface( SvDispatch::ClassFactory() );

/*N*/   SfxObjectShell *pThis = this;
/*N*/   SfxObjectShellArr_Impl &rArr = SFX_APP()->GetObjectShells_Impl();
/*N*/   rArr.C40_INSERT( SfxObjectShell, pThis, rArr.Count() );
/*N*/   pImp->bInList = sal_True;
/*N*/   pImp->nLoadedFlags = SFX_LOADED_ALL;
/*N*/ }

//--------------------------------------------------------------------

// virtual dtor of typical base-class SfxObjectShell

/*N*/ SfxObjectShell::~SfxObjectShell()
/*N*/ {
/*N*/   DBG_DTOR(SfxObjectShell, 0);
/*N*/
/*N*/   if ( IsEnableSetModified() )
/*N*/       EnableSetModified( sal_False );
/*N*/
/*N*/   // Niemals GetInPlaceObject() aufrufen, der Zugriff auf den
/*N*/   // Ableitungszweig SfxInternObject ist wegen eines Compiler Bugs nicht
/*N*/   // erlaubt
/*N*/   SfxObjectShell::Close();
/*N*/     pImp->xModel = NULL;
/*N*/
/*N*/     String aPhysName;
/*N*/     if ( pMedium )
/*N*/         aPhysName = pMedium->GetPhysicalName();
/*N*/
/*N*/   DELETEX(pImp->pEventConfig);
/*N*/     DELETEX(pImp->pImageManager);
/*N*/     DELETEX(pImp->pTbxConfig);
/*N*/     DELETEX(pImp->pAccMgr);
/*N*/   DELETEX(pImp->pCfgMgr);
/*N*/     DELETEX(pImp->pReloadTimer );
/*N*/
/*N*/   SfxApplication *pSfxApp = SFX_APP();
/*N*/   if ( USHRT_MAX != pImp->nVisualDocumentNumber )
/*N*/       pSfxApp->ReleaseIndex(pImp->nVisualDocumentNumber);
/*N*/
/*N*/   // Basic-Manager zerst"oren
/*N*/   if ( pImp->pBasicMgr )
/*N*/       BasicManager::LegacyDeleteBasicManager( pImp->pBasicMgr );
/*N*/   if( pImp->pBasicLibContainer )
/*N*/       pImp->pBasicLibContainer->release();
/*N*/   if( pImp->pDialogLibContainer )
/*N*/       pImp->pDialogLibContainer->release();
/*N*/
/*N*/   if ( pSfxApp->GetDdeService() )
/*N*/       pSfxApp->RemoveDdeTopic( this );
/*N*/
/*N*/   delete pImp->pDocInfo;
/*N*/   if ( pImp->xModel.is() )
/*N*/       pImp->xModel = ::com::sun::star::uno::Reference< ::com::sun::star::frame::XModel > ();
/*N*/
/*N*/     if ( pMedium && pMedium->IsTemporary() )
/*N*/         HandsOff();
/*N*/
/*N*/     DELETEX( pMedium );
/*N*/
/*N*/     if ( pImp->aTempName.Len() )
/*N*/     {
/*?*/         if ( aPhysName == pImp->aTempName && !IsHandsOff() )
/*?*/             HandsOff();
/*?*/         String aTmp;
/*?*/         ::utl::LocalFileHelper::ConvertPhysicalNameToURL( pImp->aTempName, aTmp );
/*?*/         ::utl::UCBContentHelper::Kill( aTmp );
/*N*/     }
/*N*/
/*N*/     delete pImp;
/*N*/ }

//--------------------------------------------------------------------

/*?*/ SfxObjectFactory& SfxObjectShell::GetFactory() const
/*?*/ {
/*?*/   return *_pFactory;
/*?*/ }
//--------------------------------------------------------------------

/*N*/ void SfxObjectShell::ViewAssigned()

/*  [Beschreibung]

    Diese Methode wird gerufen, wenn eine ::com::sun::star::sdbcx::View zugewiesen wird.
*/

/*N*/ {
/*N*/   // Spaetestens jetzt die Factory initialisieren (wegen HelpFileName)
/*N*/   GetFactory().DoInitFactory();
/*N*/ }

//--------------------------------------------------------------------
// closes the Object and all its views

/*N*/ sal_Bool SfxObjectShell::Close()
/*N*/ {
/*N*/   {DBG_CHKTHIS(SfxObjectShell, 0);}
/*N*/   if ( !pImp->bClosing )
/*N*/   {
/*N*/       // falls noch ein Progress l"auft, nicht schlie\sen
/*N*/       if ( !pImp->bDisposing && GetProgress() )
/*N*/           return sal_False;
/*N*/
/*N*/       pImp->bClosing = sal_True;
/*N*/       Reference< util::XCloseable > xCloseable( GetBaseModel(), UNO_QUERY );
/*N*/
/*N*/       if ( xCloseable.is() )
/*N*/       {
/*N*/           try
/*N*/           {
/*N*/               xCloseable->close( sal_True );
/*N*/           }
/*N*/           catch( Exception& )
/*N*/           {
/*N*/               pImp->bClosing = sal_False;
/*N*/           }
/*N*/       }
/*N*/
/*N*/       if ( pImp->bClosing )
/*N*/       {
/*N*/           // aus Document-Liste austragen
/*N*/           SfxApplication *pSfxApp = SFX_APP();
/*N*/           SfxObjectShellArr_Impl &rDocs = pSfxApp->GetObjectShells_Impl();
/*N*/           const SfxObjectShell *pThis = this;
/*N*/           sal_uInt16 nPos = rDocs.GetPos(pThis);
/*N*/           if ( nPos < rDocs.Count() )
/*N*/               rDocs.Remove( nPos );
/*N*/           pImp->bInList = sal_False;
/*N*/
/*N*/           // Broadcasten (w"ahrend dessen festhalten)
/*N*/           SfxObjectShellRef aRef(this);
/*
            // Ist leider zu sp"at, da kaum noch Macros laufen, wenn keine View
            // mehr da ist!
            if ( _pFactory && _pFactory->GetFlags() & SFXOBJECTSHELL_HASOPENDOC )
                // Event nur bei echten Dokumenten
                pSfxApp->NotifyEvent( SfxEventHint(SFX_EVENT_CLOSEDOC, this) );
*/
/*N*/           // Broadcast moved to SfxBaseModel!
/*N*/           //Broadcast( SfxSimpleHint(SFX_HINT_DEINITIALIZING) );
/*N*/           //pImp->bClosing = sal_False;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return sal_True;
/*N*/ }

//--------------------------------------------------------------------

// returns a pointer the first SfxDocument of specified type

/*N*/ SfxObjectShell* SfxObjectShell::GetFirst
/*N*/ (
/*N*/   const TypeId* pType ,
/*N*/   sal_Bool            bOnlyVisible
/*N*/ )
/*N*/ {
/*N*/   SfxObjectShellArr_Impl &rDocs = SFX_APP()->GetObjectShells_Impl();
/*N*/
/*N*/   // seach for a SfxDocument of the specified type
/*N*/   for ( sal_uInt16 nPos = 0; nPos < rDocs.Count(); ++nPos )
/*N*/   {
/*N*/       SfxObjectShell* pSh = rDocs.GetObject( nPos );
/*N*/       if ( bOnlyVisible && pSh->IsPreview() && pSh->IsReadOnly() )
/*N*/           continue;
/*N*/
/*N*/       if ( ( !pType || pSh->IsA(*pType) ) &&
/*N*/            ( !bOnlyVisible || SfxViewFrame::GetFirst( pSh, 0, sal_True )))
/*N*/           return pSh;
/*N*/   }
/*N*/
/*N*/   return 0;
/*N*/ }
//--------------------------------------------------------------------

// returns a pointer to the next SfxDocument of specified type behind *pDoc

/*N*/ SfxObjectShell* SfxObjectShell::GetNext
/*N*/ (
/*N*/   const SfxObjectShell&   rPrev,
/*N*/   const TypeId*           pType,
/*N*/   sal_Bool                    bOnlyVisible
/*N*/ )
/*N*/ {
/*N*/   SfxObjectShellArr_Impl &rDocs = SFX_APP()->GetObjectShells_Impl();
/*N*/
/*N*/   // refind the specified predecessor
/*N*/   sal_uInt16 nPos;
/*N*/   for ( nPos = 0; nPos < rDocs.Count(); ++nPos )
/*N*/       if ( rDocs.GetObject(nPos) == &rPrev )
/*N*/           break;
/*N*/
/*N*/   // search for the next SfxDocument of the specified type
/*N*/   for ( ++nPos; nPos < rDocs.Count(); ++nPos )
/*N*/   {
/*N*/       SfxObjectShell* pSh = rDocs.GetObject( nPos );
/*N*/       if ( bOnlyVisible && pSh->IsPreview() && pSh->IsReadOnly() )
/*N*/           continue;
/*N*/
/*N*/       if ( ( !pType || pSh->IsA(*pType) ) &&
/*N*/            ( !bOnlyVisible || SfxViewFrame::GetFirst( pSh, 0, sal_True )))
/*N*/           return pSh;
/*N*/   }
/*N*/   return 0;
/*N*/ }

//--------------------------------------------------------------------

/*N*/ SfxObjectShell* SfxObjectShell::Current()
/*N*/ {
/*N*/   SfxViewFrame *pFrame = SFX_APP()->GetViewFrame();
/*N*/   return pFrame ? pFrame->GetObjectShell() : 0;
/*N*/ }

//-------------------------------------------------------------------------

/*?*/ sal_Bool SfxObjectShell::IsInPrepareClose() const

/*  [Beschreibung]

    Diese Methode liefert sal_True, falls gerade ein PrepareClose laeuft.
*/

/*?*/ {
/*?*/   return pImp->bInPrepareClose;
/*?*/ }

//------------------------------------------------------------------------

/*N*/ struct BoolEnv_Impl
/*N*/ {
/*N*/   SfxObjectShell_Impl* pImp;
/*N*/   BoolEnv_Impl( SfxObjectShell_Impl* pImpP) : pImp( pImpP )
/*N*/   { pImpP->bInPrepareClose = sal_True; }
/*N*/   ~BoolEnv_Impl() { pImp->bInPrepareClose = sal_False; }
/*N*/ };


/*N*/ sal_uInt16 SfxObjectShell::PrepareClose
/*N*/ (
/*N*/   sal_Bool    bUI,        // sal_True: Dialoge etc. erlaubt, sal_False: silent-mode
/*N*/   sal_Bool    bForBrowsing
/*N*/ )
/*N*/ {
/*N*/   if( pImp->bInPrepareClose || pImp->bPreparedForClose )
/*N*/       return sal_True;
/*N*/   BoolEnv_Impl aBoolEnv( pImp );
/*N*/
/*N*/   // DocModalDialog?
/*N*/   if ( IsInModalMode() )
/*N*/       return sal_False;
/*N*/
/*N*/   SfxViewFrame* pFirst = SfxViewFrame::GetFirst( this );
/*N*/   if( pFirst && !pFirst->GetFrame()->PrepareClose_Impl( bUI, bForBrowsing ) )
/*N*/       return sal_False;
/*N*/
/*N*/   // prepare views for closing
/*N*/   for ( SfxViewFrame* pFrm = SfxViewFrame::GetFirst(
/*N*/       this, TYPE(SfxViewFrame));
/*N*/         pFrm; pFrm = SfxViewFrame::GetNext( *pFrm, this ) )
/*N*/   {
/*N*/       DBG_ASSERT(pFrm->GetViewShell(),"KeineShell");
/*N*/       if ( pFrm->GetViewShell() )
/*N*/       {
/*N*/           sal_uInt16 nRet = pFrm->GetViewShell()->PrepareClose( bUI, bForBrowsing );
/*N*/           if ( nRet != sal_True )
/*N*/               return nRet;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if( GetInPlaceObject() && GetInPlaceObject()->GetClient())
/*N*/   {
/*?*/       pImp->bPreparedForClose = sal_True;
/*?*/       return sal_True;
/*N*/   }
/*N*/
/*N*/   // ggf. nachfragen, ob gespeichert werden soll
/*N*/       // nur fuer in sichtbaren Fenstern dargestellte Dokumente fragen
/*N*/   SfxViewFrame *pFrame = SfxObjectShell::Current() == this
/*N*/       ? SfxViewFrame::Current() : SfxViewFrame::GetFirst( this );
/*N*/   while ( pFrame && (pFrame->GetFrameType() & SFXFRAME_SERVER ) )
/*?*/       pFrame = SfxViewFrame::GetNext( *pFrame, this );
/*N*/
/*N*/   SfxApplication *pSfxApp = SFX_APP();
/*N*/   pSfxApp->NotifyEvent( SfxEventHint(SFX_EVENT_PREPARECLOSEDOC, this) );
/*N*/   sal_Bool bClose = sal_False;
/*N*/   if ( bUI && IsModified() )
/*N*/   {
/*?*/       if ( pFrame )
/*?*/       {
/*?*/           // minimierte restoren
/*?*/             DBG_BF_ASSERT(0, "STRIP"); //STRIP001 SfxFrame* pTop = pFrame->GetTopFrame();
/*?*/       }
/*N*/   }
/*N*/
/*N*/   // ggf. hinweisen, da\s unter Fremdformat gespeichert
/*N*/   if( pMedium )
/*N*/   {
/*N*/       SFX_ITEMSET_ARG( pMedium->GetItemSet(), pIgnoreInformationLost,
/*N*/                        SfxBoolItem, SID_DOC_IGNOREINFORMATIONLOST, sal_False);
/*N*/       if( pIgnoreInformationLost && pIgnoreInformationLost->GetValue() )
/*N*/           bUI = sal_False;
/*N*/   }
/*N*/   if ( bUI && !bClose && IsInformationLost() )
/*N*/   {
/*N*/       // minimierte restoren
/*?*/         DBG_BF_ASSERT(0, "STRIP"); //STRIP001 SfxFrame* pTop = pFrame->GetTopFrame();
/*N*/   }
/*N*/
/*N*/   pImp->bPreparedForClose = sal_True;
/*N*/   return sal_True;
/*N*/ }

//--------------------------------------------------------------------

/*N*/ BasicManager* SfxObjectShell::GetBasicManager() const
/*N*/ {
/*N*/     return HasBasic() ? pImp->pBasicMgr : SFX_APP()->GetBasicManager();
/*N*/ }

/*N*/ sal_Bool SfxObjectShell::HasBasic() const
/*N*/ {
/*N*/     if ( !pImp->bBasicInitialized )
/*N*/     {
/*N*/         String aName( GetMedium()->GetName() );
/*N*/         ((SfxObjectShell*)this)->InitBasicManager_Impl( GetStorage(), aName.Len() ? &aName : NULL );
/*N*/     }
/*N*/   return pImp->pBasicMgr != NULL;
/*N*/ }

//--------------------------------------------------------------------


//--------------------------------------------------------------------

Reference< XLibraryContainer > SfxObjectShell::GetBasicContainer()
{
    if( !pImp->pBasicLibContainer )
        GetBasicManager();
    Reference< XLibraryContainer > xRet
        = static_cast< XLibraryContainer* >( pImp->pBasicLibContainer );
    return xRet;
}

//--------------------------------------------------------------------

/*N*/ StarBASIC* SfxObjectShell::GetBasic() const
/*N*/ {
/*N*/   return GetBasicManager()->GetLib(0);
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void SfxObjectShell::InitBasicManager_Impl
/*N*/ (
/*N*/   SvStorage*  pStor       /* Storage, aus dem das Dokument geladen wird
                               (aus <SvPersist::Load()>) bzw. 0, falls es
                               sich um ein neues Dokument handelt
                               (aus <SvPersist::InitNew()>). */
/*N*/     , const String* pName
)
/*  [Beschreibung]

    Erzeugt einen Dokument-BasicManager und l"adt diesen ggf. (pStor != 0)
    aus dem Storage.


    [Anmerkung]

    Diese Methode mu"s aus den "Uberladungen von <SvPersist::Load()> (mit
    dem pStor aus dem Parameter von Load()) sowie aus der "Uberladung
    von <SvPersist::InitNew()> (mit pStor = 0) gerufen werden.
*/

/*N*/ {
/*N*/   StarBASIC *pAppBasic = SFX_APP()->GetBasic();
/*N*/     DBG_ASSERT( !pImp->bBasicInitialized && !pImp->pBasicMgr, "Lokaler BasicManager bereits vorhanden");
/*N*/
/*N*/     pImp->bBasicInitialized = TRUE;
/*N*/   BasicManager* pBasicManager;
/*N*/   if ( pStor )
/*N*/   {
/*N*/       String aOldURL = so3::StaticBaseUrl::GetBaseURL();
/*N*/       String aNewURL;
/*N*/       if( HasName() )
/*N*/           aNewURL = GetMedium()->GetName();
/*N*/       else
/*N*/       {
/*N*/           aNewURL = GetDocInfo().GetTemplateFileName();
/*N*/           // Bei Templates keine ::com::sun::star::util::URL...
/*N*/             aNewURL = so3::StaticBaseUrl::SmartRelToAbs( aNewURL );
/*N*/       }
/*N*/       so3::StaticBaseUrl::SetBaseURL( aNewURL );
/*N*/
/*N*/       // load BASIC-manager
/*N*/       SfxErrorContext aErrContext( ERRCTX_SFX_LOADBASIC, GetTitle() );
/*N*/ #if SUPD<613//MUSTINI
/*N*/       SfxIniManager *pIniMgr = SFX_APP()->GetIniManager();
/*N*/       String aAppBasicDir( pIniMgr->Get(SFX_KEY_BASIC_PATH) );
/*N*/ #else
/*N*/       String aAppBasicDir = SvtPathOptions().GetBasicPath();
/*N*/ #endif
/*N*/         pImp->pBasicMgr = pBasicManager = new BasicManager(
                *pStor,
                so3::StaticBaseUrl::GetBaseURL(INetURLObject::NO_DECODE),
                pAppBasic, &aAppBasicDir );
/*N*/       if ( pImp->pBasicMgr->HasErrors() )
/*N*/       {
/*?*/           // handle errors
/*?*/           BasicError *pErr = pImp->pBasicMgr->GetFirstError();
/*?*/           while ( pErr )
/*?*/           {
/*?*/               // show message to user
/*?*/               if ( ERRCODE_BUTTON_CANCEL ==
/*?*/                    ErrorHandler::HandleError( pErr->GetErrorId() ) )
/*?*/               {
/*?*/                   // user wants to break loading of BASIC-manager
/*?*/                   BasicManager::LegacyDeleteBasicManager( pImp->pBasicMgr );
/*?*/                   pStor = 0;
/*?*/                   break;
/*?*/               }
/*?*/               pErr = pImp->pBasicMgr->GetNextError();
/*?*/           }
/*N*/       }
/*N*/
/*N*/       so3::StaticBaseUrl::SetBaseURL( aOldURL );
/*N*/   }
/*N*/
/*N*/   // not loaded?
/*N*/   if ( !pStor )
/*N*/   {
/*?*/       // create new BASIC-manager
/*?*/       StarBASIC *pBas = new StarBASIC(pAppBasic);
/*?*/       pBas->SetFlag( SBX_EXTSEARCH );
/*?*/       pImp->pBasicMgr = pBasicManager = new BasicManager( pBas );
/*N*/   }
/*N*/
/*N*/   // Basic container
/*N*/   SfxScriptLibraryContainer* pBasicCont = new SfxScriptLibraryContainer
/*N*/       ( DEFINE_CONST_UNICODE( "StarBasic" ), pBasicManager, pStor );
/*N*/   pBasicCont->acquire();  // Hold via UNO
/*N*/     Reference< XLibraryContainer > xBasicCont = static_cast< XLibraryContainer* >( pBasicCont );
/*N*/   pImp->pBasicLibContainer = pBasicCont;
/*N*/
/*N*/   // Dialog container
/*N*/   SfxDialogLibraryContainer* pDialogCont = new SfxDialogLibraryContainer( pStor );
/*N*/   pDialogCont->acquire(); // Hold via UNO
/*N*/     Reference< XLibraryContainer > xDialogCont = static_cast< XLibraryContainer* >( pDialogCont );
/*N*/   pImp->pDialogLibContainer = pDialogCont;
/*N*/
/*N*/   LibraryContainerInfo* pInfo = new LibraryContainerInfo
/*N*/         ( xBasicCont, xDialogCont, static_cast< OldBasicPassword* >( pBasicCont ) );
/*N*/   pBasicManager->SetLibraryContainerInfo( pInfo );
/*N*/     pBasicCont->setBasicManager( pBasicManager );
/*N*/
/*N*/   // damit auch Dialoge etc. 'qualifiziert' angesprochen werden k"onnen
/*N*/   StarBASIC *pBas = pImp->pBasicMgr->GetLib(0);
/*N*/   // Initialize Uno
/*N*/   //pBas->setRoot( GetModel() );
/*N*/   sal_Bool bWasModified = pBas->IsModified();
/*N*/   pBas->SetParent( pAppBasic );
/*N*/
/*N*/   // Properties im Doc-BASIC
/*N*/   // ThisComponent
/*N*/     ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface >  xInterface ( GetModel(), ::com::sun::star::uno::UNO_QUERY );
/*N*/     ::com::sun::star::uno::Any aComponent;
/*N*/     aComponent <<= xInterface;
/*N*/     SbxObjectRef xUnoObj = GetSbUnoObject( DEFINE_CONST_UNICODE("ThisComponent"), aComponent );
/*N*/     xUnoObj->SetFlag( SBX_DONTSTORE );
/*N*/     pBas->Insert( xUnoObj );
/*N*/
/*N*/   // Standard lib name
/*N*/   ::rtl::OUString aStdLibName( RTL_CONSTASCII_USTRINGPARAM( "Standard" ) );
/*N*/
/*N*/   // Basic container
/*N*/   if ( xBasicCont.is() && !xBasicCont->hasByName( aStdLibName ) )
/*N*/       xBasicCont->createLibrary( aStdLibName );   // create Standard library
/*N*/   Any aBasicCont;
/*N*/   aBasicCont <<= xBasicCont;
/*N*/   xUnoObj = GetSbUnoObject( DEFINE_CONST_UNICODE("BasicLibraries"), aBasicCont );
/*N*/   pBas->Insert( xUnoObj );
/*N*/
/*N*/   // Dialog container
/*N*/   if ( xDialogCont.is() && !xDialogCont->hasByName( aStdLibName ) )
/*N*/       xDialogCont->createLibrary( aStdLibName );  // create Standard library
/*N*/   Any aDialogCont;
/*N*/   aDialogCont <<= xDialogCont;
/*N*/   xUnoObj = GetSbUnoObject( DEFINE_CONST_UNICODE("DialogLibraries"), aDialogCont );
/*N*/   pBas->Insert( xUnoObj );
/*N*/
/*N*/
/*N*/   // Modify-Flag wird bei MakeVariable gesetzt
/*N*/   pBas->SetModified( bWasModified );
/*N*/ }

//--------------------------------------------------------------------
#if 0 //(mba)
#endif

//--------------------------------------------------------------------

/*?*/ sal_uInt16 SfxObjectShell::Count()
/*?*/ {
/*?*/   return SFX_APP()->GetObjectShells_Impl().Count();
/*?*/ }

//--------------------------------------------------------------------

/*?*/ sal_Bool SfxObjectShell::DoClose()
/*?*/ {
/*?*/   return Close();
/*?*/ }

//--------------------------------------------------------------------

/*?*/ void SfxObjectShell::SetLastMark_Impl( const String &rMark )
/*?*/ {
/*?*/   pImp->aMark = rMark;
/*?*/ }

//--------------------------------------------------------------------

/*?*/ const String& SfxObjectShell::GetLastMark_Impl() const
/*?*/ {
/*?*/   return pImp->aMark;
/*?*/ }

//--------------------------------------------------------------------

/*?*/ SfxObjectShell* SfxObjectShell::GetObjectShell()
/*?*/ {
/*?*/   return this;
/*?*/ }

//--------------------------------------------------------------------

/*N*/ SEQUENCE< OUSTRING > SfxObjectShell::GetEventNames()
/*N*/ {
/*N*/   return GetEventNames_Impl();
/*N*/ }
/*N*/
/*N*/ SEQUENCE< OUSTRING > SfxObjectShell::GetEventNames_Impl()
/*N*/ {
/*N*/     ::vos::OGuard aGuard( Application::GetSolarMutex() );
/*N*/
/*N*/   ResStringArray aEventNames( SfxResId( EVENT_NAMES_ARY ) );
/*N*/   USHORT nCount = aEventNames.Count();
/*N*/
/*N*/   SEQUENCE < OUSTRING > aSequence( nCount );
/*N*/
/*N*/   OUSTRING* pNames = aSequence.getArray();
/*N*/
/*N*/   for ( USHORT i=0; i<nCount; i++ )
/*N*/   {
/*N*/       pNames[i] = aEventNames.GetString( i );
/*N*/   }
/*N*/
/*N*/   return aSequence;
/*N*/ }

//--------------------------------------------------------------------
/* ASDBG
void SfxObjectShell::SetModel( SfxModel* pModel )
{
    if ( pImp->xModel.is() )
        DBG_WARNING( "Model already set!" );
    pImp->xModel = pModel;
}

//--------------------------------------------------------------------

XModel* SfxObjectShell::GetModel()
{
    return pImp->xModel;
}
*/
//--------------------------------------------------------------------

/*N*/ void SfxObjectShell::SetModel( SfxBaseModel* pModel )
/*N*/ {
/*N*/   if ( pImp->xModel.is() )
/*N*/       DBG_WARNING( "Model already set!" );
/*N*/
/*N*/   pImp->xModel = pModel;
/*N*/ }

//--------------------------------------------------------------------

/*N*/ ::com::sun::star::uno::Reference< ::com::sun::star::frame::XModel > SfxObjectShell::GetModel()
/*N*/ {
/*N*/   return pImp->xModel;
/*N*/ }

/*N*/ void SfxObjectShell::SetBaseModel( SfxBaseModel* pModel )
/*N*/ {
/*N*/   if ( pImp->xModel.is() && pModel )
/*N*/       DBG_WARNING( "Model already set!" );
/*N*/
/*N*/   pImp->xModel = pModel;
/*N*/ }

//--------------------------------------------------------------------

/*N*/ ::com::sun::star::uno::Reference< ::com::sun::star::frame::XModel > SfxObjectShell::GetBaseModel()
/*N*/ {
/*N*/   return pImp->xModel;
/*N*/ }
/* -----------------------------10.09.2001 15:56------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ void SfxObjectShell::SetAutoStyleFilterIndex(sal_uInt16 nSet)
/*N*/ {
/*N*/     pImp->nStyleFilter = nSet;
/*N*/ }

/*N*/ void SfxObjectShell::SetWorkingDocument( SfxObjectShell* pDoc )
/*N*/ {
/*N*/   pWorkingDoc = pDoc;
/*N*/   StarBASIC* pBas = SFX_APP()->GetBasic_Impl();
/*N*/     if ( pDoc && pBas )
/*N*/     {
/*N*/         SFX_APP()->Get_Impl()->pThisDocument = pDoc;
/*N*/         ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface >  xInterface ( pDoc->GetModel() , ::com::sun::star::uno::UNO_QUERY );
/*N*/         ::com::sun::star::uno::Any aComponent;
/*N*/         aComponent <<= xInterface;
/*N*/         SbxVariable *pCompVar = pBas->Find( DEFINE_CONST_UNICODE("ThisComponent"), SbxCLASS_PROPERTY );
/*N*/         if ( pCompVar )
/*N*/         {
/*?*/             pCompVar->PutObject( GetSbUnoObject( DEFINE_CONST_UNICODE("ThisComponent"), aComponent ) );
/*N*/         }
/*N*/         else
/*N*/         {
/*N*/             SbxObjectRef xUnoObj = GetSbUnoObject( DEFINE_CONST_UNICODE("ThisComponent"), aComponent );
/*N*/             xUnoObj->SetFlag( SBX_DONTSTORE );
/*N*/             pBas->Insert( xUnoObj );
/*N*/         }
/*N*/     }
/*N*/ }

}
