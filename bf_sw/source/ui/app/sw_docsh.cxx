/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */


#ifdef _MSC_VER
#pragma hdrstop
#endif

#include <hintids.hxx>

#include <rtl/logfile.hxx>
#include <tools/urlobj.hxx>
#include <bf_svtools/whiter.hxx>
#include <bf_svtools/stritem.hxx>
#include <bf_svx/adjitem.hxx>

#include <bf_sfx2/app.hxx>

#include <bf_sfx2/docfile.hxx>
#include <bf_sfx2/docfilt.hxx>
#include <bf_sfx2/printer.hxx>
#include <bf_svx/linkmgr.hxx>
#include <comphelper/classids.hxx>

#include <fmtpdsc.hxx>
#include <fmtfsize.hxx>

#include <osl/diagnose.h>

#include <swwait.hxx>

#include <horiornt.hxx>

#include <wdocsh.hxx>
#include <crsrsh.hxx>
#include <swmodule.hxx>
#include <globdoc.hxx>
#include <usrpref.hxx>
#include <shellio.hxx>      // I/O
#include <sw3io.hxx>        // I/O, Hausformat
#include <docstyle.hxx>
#include <doc.hxx>
#include <pagedesc.hxx>
#include <swbaslnk.hxx>
#include <ndindex.hxx>
#include <ndole.hxx>

#include <swerror.h>        // Fehlermeldungen
#include <helpid.h>
#include <cmdid.h>          //
#include <globals.hrc>
#include <app.hrc>

#include <bf_svtools/moduleoptions.hxx>

using namespace ::com::sun::star::uno;
using ::rtl::OUString;

namespace binfilter {
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::script;
using namespace ::com::sun::star::container;

/*N*/ class SwTmpPersist : public SvPersist
/*N*/{
/*N*/   SwDocShell* pDShell;
/*N*/   virtual void FillClass( SvGlobalName * pClassName,
/*N*/                           ULONG * pClipFormat,
/*N*/                           String * pAppName,
/*N*/                           String * pLongUserName,
/*N*/                           String * pUserName,
/*N*/                           long nFileFormat=SOFFICE_FILEFORMAT_CURRENT ) const;
/*N*/   virtual BOOL Save() {return false;}
/*N*/ public:
/*N*/   SwTmpPersist( SwDocShell& rDSh ) : pDShell( &rDSh ) {}
/*N*/};


/*--------------------------------------------------------------------
    Beschreibung:   Aller Filter registrieren
 --------------------------------------------------------------------*/

SFX_IMPL_OBJECTFACTORY_DLL(SwDocShell, SFXOBJECTSHELL_STD_NORMAL|SFXOBJECTSHELL_HASMENU,  \
//swriter3  0xDC5C7E40L, 0xB35C, 0x101B, 0x99, 0x61, 0x04, 0x02, 0x1C, 0x00, 0x70,0x02)
//swriter4  0x8b04e9b0,  0x420e, 0x11d0, 0xa4, 0x5e, 0x0,  0xa0, 0x24, 0x9d, 0x57,0xb1, Sw)
//swriter5  0xc20cf9d1, 0x85ae, 0x11d1, 0xaa, 0xb4, 0x0, 0x60, 0x97, 0xda, 0x56, 0x1a
  SvGlobalName(BF_SO3_SW_CLASSID), Sw)      /*swriter5,*/

/*{
    ::RegisterFilterInSfxFactory( (SfxObjectFactory&)Factory(), RC_DOC_ICON );
}
  */


/*N*/ TYPEINIT2(SwDocShell, SfxObjectShell, SfxListener);

/*--------------------------------------------------------------------
    Beschreibung: Laden vorbereiten
 --------------------------------------------------------------------*/


/*N*/ Reader* SwDocShell::StartConvertFrom(SfxMedium& rMedium, SwReader** ppRdr,
/*N*/                                   SwCrsrShell *pCrsrShell,
/*N*/                                   SwPaM* pPaM )
/*N*/ {
/*N*/   BOOL bAPICall = FALSE;
    const SfxPoolItem* pApiItem;
    const SfxItemSet* pMedSet;
    if( 0 != ( pMedSet = rMedium.GetItemSet() ) && SFX_ITEM_SET ==
            pMedSet->GetItemState( FN_API_CALL, TRUE, &pApiItem ) )
            bAPICall = ((const SfxBoolItem*)pApiItem)->GetValue();

    const SfxFilter* pFlt = rMedium.GetFilter();
    if( !pFlt )
    {
        if(!bAPICall)
        {
        }
        return 0;
    }
    String aLclFileName( rMedium.GetName() );
    SwRead pRead = SwIoSystem::GetReader( pFlt->GetUserData() );
    if( !pRead )
        return 0;

    if( rMedium.IsStorage()
        ? SW_STORAGE_READER & pRead->GetReaderType()
        : SW_STREAM_READER & pRead->GetReaderType() )
    {
        *ppRdr = pPaM ? new SwReader( rMedium, aLclFileName, *pPaM ) :
            pCrsrShell ?
                new SwReader( rMedium, aLclFileName, *pCrsrShell->GetCrsr() )
                    : new SwReader( rMedium, aLclFileName, pDoc );
    }
    else
        return 0;

    // PassWord Checken
    String aPasswd;
    if ((*ppRdr)->NeedsPasswd( *pRead ))
    {
        {
            const SfxItemSet* pSet = rMedium.GetItemSet();
            const SfxPoolItem *pPassItem;
            if(pSet && SFX_ITEM_SET == pSet->GetItemState(SID_PASSWORD, TRUE, &pPassItem))
                aPasswd = ((const SfxStringItem *)pPassItem)->GetValue();
        }

        if (!(*ppRdr)->CheckPasswd( aPasswd, *pRead ))
        {
                delete *ppRdr;
            return 0;
        }
    }
    if(rMedium.IsStorage())
    {
        SvStorageRef aStor( rMedium.GetStorage() );
        const SfxItemSet* pSet = rMedium.GetItemSet();
        const SfxPoolItem *pItem;
        if(pSet && SFX_ITEM_SET == pSet->GetItemState(SID_PASSWORD, TRUE, &pItem))
        {
            DBG_ASSERT(pItem->IsA( TYPE(SfxStringItem) ), "Fehler Parametertype");
            rtl::OString aLclPasswd(rtl::OUStringToOString(((const SfxStringItem *)pItem)->GetValue(),
                osl_getThreadTextEncoding()));
            aStor->SetKey( aLclPasswd );
        }
        // Fuer's Dokument-Einfuegen noch die FF-Version, wenn's der
        // eigene Filter ist.
        DBG_ASSERT(pRead != ReadSw3 || /*pRead != ReadXML ||*/ pFlt->GetVersion(),
                "Am Filter ist keine FF-Version gesetzt" );
        if( (pRead == ReadSw3 /*|| pRead == ReadXML*/) && pFlt->GetVersion() )
            aStor->SetVersion( (long)pFlt->GetVersion() );
    }
    // beim Sw3-Reader noch den pIo-Pointer setzen
    if( pRead == ReadSw3 )
        ((Sw3Reader*)pRead)->SetSw3Io( pIo );

    if( pFlt->GetDefaultTemplate().Len() )
        pRead->SetTemplateName( pFlt->GetDefaultTemplate() );

    if( pRead == ReadAscii && 0 != rMedium.GetInStream() &&
        pFlt->GetUserData().EqualsAscii( FILTER_TEXT_DLG ) )
    {
        SwAsciiOptions aOpt;
        const SfxItemSet* pSet;
        const SfxPoolItem* pItem;
        if( 0 != ( pSet = rMedium.GetItemSet() ) && SFX_ITEM_SET ==
            pSet->GetItemState( SID_FILE_FILTEROPTIONS, TRUE, &pItem ) )
            aOpt.ReadUserData( ((const SfxStringItem*)pItem)->GetValue() );

        if( pRead )
            pRead->GetReaderOpt().SetASCIIOpts( aOpt );
    }

    return pRead;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: Laden
 --------------------------------------------------------------------*/

 BOOL SwDocShell::ConvertFrom( SfxMedium& rMedium )
 {
    RTL_LOGFILE_CONTEXT_AUTHOR( aLog, "SW", "JP93722",  "SwDocShell::ConvertFrom" );

    SwReader* pRdr;
    SwRead pRead = StartConvertFrom(rMedium, &pRdr);
    if (!pRead)
        return FALSE;

        // SfxProgress unterdruecken, wenn man Embedded ist
    SW_MOD()->SetEmbeddedLoadSave(
                            SFX_CREATE_MODE_EMBEDDED == GetCreateMode() );

    pRdr->GetDoc()->SetHTMLMode( ISA(SwWebDocShell) );

     /* #106748# Restore the pool default if reading a saved document. */
     pDoc->RemoveAllFmtLanguageDependencies();

    ULONG nErr = pRdr->Read( *pRead );

    // Evtl. ein altes Doc weg
    if( pDoc )
        RemoveLink();
    pDoc = pRdr->GetDoc();

    // die DocInfo vom Doc am DocShell-Medium setzen
    if( GetMedium()->GetFilter() &&
        GetMedium()->GetFilter()->UsesStorage() )
    {
        SvStorageRef aRef = GetMedium()->GetStorage();
        if( aRef.Is() )
            pDoc->GetInfo()->Save(aRef);
    }

    AddLink();

    OSL_ENSURE( !pBasePool, "wer hat seinen Pool nicht zerstoert?" );
    pBasePool = new SwDocStyleSheetPool( *pDoc,
                        SFX_CREATE_MODE_ORGANIZER == GetCreateMode() );
    UpdateFontList();
    InitDraw();

    delete pRdr;

    SW_MOD()->SetEmbeddedLoadSave( FALSE );

    SetError( nErr );
    BOOL bOk = !IsError( nErr );

    // StartFinishedLoading rufen. Nicht bei asynchronen Filtern!
    // Diese muessen das selbst rufen!
    if( bOk && !pDoc->IsInLoadAsynchron() )
        StartLoadFinishedTimer();

    return bOk;
 }

/*--------------------------------------------------------------------
    Beschreibung:   Haende weg
 --------------------------------------------------------------------*/


/*N*/ void SwDocShell::HandsOff()
/*N*/ {
/*N*/   pIo->HandsOff();
/*N*/   SfxInPlaceObject::HandsOff();
/*N*/ }


/*--------------------------------------------------------------------
    Beschreibung: Draw()-Overload fuer OLE2 (Sfx)
 --------------------------------------------------------------------*/

/*N*/ void SwDocShell::SetVisArea( const Rectangle &rRect )
/*N*/ {
/*N*/   Rectangle aRect( rRect );
         SfxInPlaceObject::SetVisArea( aRect );
/*N*/ }


/*N*/ Rectangle SwDocShell::GetVisArea( USHORT nAspect ) const
/*N*/ {
/*N*/   if ( nAspect == ASPECT_THUMBNAIL )
/*N*/   {
/*?*/       //PreView: VisArea auf die erste Seite einstellen.
/*?*/
/*?*/       //PageDesc besorgen, vom ersten Absatz oder den default.
/*?*/       SwNodeIndex aIdx( pDoc->GetNodes().GetEndOfExtras(), 1 );
/*?*/       SwCntntNode* pNd = pDoc->GetNodes().GoNext( &aIdx );
/*?*/       const SwFmtPageDesc &rDesc = pNd->GetSwAttrSet().GetPageDesc();
/*?*/       const SwPageDesc* pDesc = rDesc.GetPageDesc();
/*?*/       if( !pDesc )
/*?*/           pDesc = &pDoc->GetPageDesc( 0 );
/*?*/
/*?*/       //Das Format wird evtl. von der virtuellen Seitennummer bestimmt.
/*?*/       const USHORT nPgNum = rDesc.GetNumOffset();
/*?*/       const BOOL bOdd = nPgNum % 2 ? TRUE : FALSE;
/*?*/       const SwFrmFmt *pFmt = bOdd ? pDesc->GetRightFmt() : pDesc->GetLeftFmt();
/*?*/       if ( !pFmt ) //#40568#
/*?*/           pFmt = bOdd ? pDesc->GetLeftFmt() : pDesc->GetRightFmt();
/*?*/
/*?*/       if ( pFmt->GetFrmSize().GetWidth() == LONG_MAX )
/*?*/           //Jetzt wird es aber Zeit fuer die Initialisierung
/*?*/           pDoc->GetPrt( TRUE );
/*?*/
/*?*/       const SwFmtFrmSize& rFrmSz = pFmt->GetFrmSize();
/*?*/       const Size aSz( rFrmSz.GetWidth(), rFrmSz.GetHeight() );
/*?*/       const Point aPt( DOCUMENTBORDER, DOCUMENTBORDER );
/*?*/       const Rectangle aRect( aPt, aSz );
/*?*/       return aRect;
/*N*/   }
/*N*/   return SvEmbeddedObject::GetVisArea( nAspect );
/*N*/ }

/*N*/ Printer *SwDocShell::GetDocumentPrinter()
/*N*/ {
/*N*/   return pDoc->GetPrt();
/*N*/ }

/*N*/ OutputDevice* SwDocShell::GetDocumentRefDev()
/*N*/ {
/*N*/     return pDoc->_GetRefDev();
/*N*/ }

/*N*/ void SwDocShell::OnDocumentPrinterChanged( Printer * pNewPrinter )
/*N*/ {
/*N*/   if ( pNewPrinter )
/*N*/       GetDoc()->SetJobsetup( pNewPrinter->GetJobSetup() );
/*N*/   else
/*N*/       GetDoc()->SetPrt( 0 );
/*N*/ }

/*N*/ ULONG SwDocShell::GetMiscStatus() const
/*N*/ {
/*N*/   return SfxInPlaceObject::GetMiscStatus() |
/*N*/          SVOBJ_MISCSTATUS_RESIZEONPRINTERCHANGE;
/*N*/ }

/*N*/ IMPL_LINK( SwDocShell, Ole2ModifiedHdl, void *, p )
/*N*/ {
/*N*/   // vom Doc wird der Status mitgegeben (siehe doc.cxx)
/*N*/   //  Bit 0:  -> alter Zustand
/*N*/   //  Bit 1:  -> neuer Zustand
/*N*/   long nStatus = (long)p;
/*N*/   if( IsEnableSetModified() )
/*N*/       SetModified( (nStatus & 2) ? TRUE : FALSE );
/*N*/   return 0;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung:   Pool returnen Hier weil virtuelll
 --------------------------------------------------------------------*/


/*N*/ SfxStyleSheetBasePool*    SwDocShell::GetStyleSheetPool()
/*N*/ {
/*N*/   return pBasePool;
/*N*/ }


/*N*/ void SwDocShell::StartLoadFinishedTimer()
/*N*/ {
/*N*/   BOOL bSttTimer = FALSE;
    // ohne WrtShell haben wir eine WebDocShell und muessen uns die
    // Optionen vom Modul holen
/*N*/   if( SW_MOD()->GetUsrPref(TRUE)->IsGraphic() )
/*N*/   {
/*N*/       const SvxLinkManager& rLnkMgr = pDoc->GetLinkManager();
/*N*/       const ::binfilter::SvBaseLinks& rLnks = rLnkMgr.GetLinks();
/*N*/       for( USHORT n = 0; n < rLnks.Count(); ++n )
/*N*/       {
/*N*/           ::binfilter::SvBaseLink* pLnk = &(*rLnks[ n ]);
/*N*/           if( pLnk && OBJECT_CLIENT_GRF == pLnk->GetObjType() &&
/*N*/               pLnk->ISA( SwBaseLink ) )
/*N*/           {
/*N*/               ::binfilter::SvLinkSource* pLnkObj = pLnk->GetObj();
/*N*/               if( !pLnkObj )
/*N*/               {
/*N*/                   String sFileNm;
/*N*/                   if( rLnkMgr.GetDisplayNames( pLnk, 0, &sFileNm, 0, 0 ))
/*N*/                   {
/*N*/                       INetURLObject aURL( sFileNm );
/*N*/                       switch( aURL.GetProtocol() )
/*N*/                       {
/*N*/                       case INET_PROT_NOT_VALID:
/*N*/                       case INET_PROT_FILE:
/*N*/                       case INET_PROT_MAILTO:
/*N*/                       case INET_PROT_NEWS:
/*N*/                       case INET_PROT_CID:
/*N*/                           break;
/*N*/
/*N*/                       default:
/*?*/                           ((SwBaseLink*)pLnk)->SwapIn();
/*?*/                           ((SwBaseLink*)pLnk)->GetCntntNode()->SetAutoFmtLvl(1);
/*?*/                           bSttTimer = TRUE;
/*N*/                           break;
/*N*/                       }
/*N*/                   }
/*N*/               }
/*N*/               else
/*N*/               {
/*N*/                   BOOL bSendState = FALSE;
/*N*/                   if( pLnkObj->IsPending() )
/*N*/                       bSttTimer = TRUE;       // Pending?
/*N*/                   else if( !pLnkObj->IsDataComplete() )
/*N*/                   {
/*N*/                       // falls aber nicht angetickert werden muss (liegt
/*N*/                       // im QuickdrawCache)
/*N*/                       if( !((SwBaseLink*)pLnk)->IsShowQuickDrawBmp() )
/*N*/                       {
/*N*/                           ((SwBaseLink*)pLnk)->SwapIn();
/*N*/                           ((SwBaseLink*)pLnk)->GetCntntNode()->SetAutoFmtLvl(1);
/*N*/                           bSttTimer = TRUE;
/*N*/                       }
/*N*/                       else
/*N*/                           // dann muss aber auf jedenfall der Status
/*N*/                           // an die Handler verschickt werden!
/*N*/                           bSendState = TRUE;
/*N*/                   }
/*N*/                   else if( ((SwBaseLink*)pLnk)->IsShowQuickDrawBmp() )
/*N*/                       // Wenn die Grafik aus dem QuickDrawCache kommt,
/*N*/                       // wird sie nie angefordert!
/*N*/                       // Dann muss aber auf jedenfall der Status
/*N*/                       // an die Handler verschickt werden!
/*N*/                       bSendState = TRUE;
/*N*/
/*N*/                   if( bSendState )
/*N*/                   {
/*?*/                       ::com::sun::star::uno::Any aValue;
/*?*/                       aValue <<= ::rtl::OUString::valueOf(
/*?*/                                           (sal_Int32)STATE_LOAD_OK );
/*?*/                       String sMimeType( SotExchange::GetFormatMimeType(
/*?*/                           SvxLinkManager::RegisterStatusInfoId() ));
/*?*/                       pLnkObj->DataChanged( sMimeType, aValue );
/*N*/                   }
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if( bSttTimer )
/*N*/   {
/*N*/       aFinishedTimer.SetTimeoutHdl( STATIC_LINK( this, SwDocShell, IsLoadFinished ));
/*N*/       aFinishedTimer.SetTimeout( 1000 );
/*N*/       aFinishedTimer.Start();
/*N*/       GetDoc()->StopIdleTimer();
/*N*/   }
/*N*/   FinishedLoading( SFX_LOADED_MAINDOCUMENT |
/*N*/                   ( bSttTimer ? 0 : SFX_LOADED_IMAGES ));
/*N*/ }


/*N*/ IMPL_STATIC_LINK( SwDocShell, IsLoadFinished, void*, EMPTYARG )
/*N*/ {
/*N*/   BOOL bSttTimer = FALSE;
/*N*/
/*N*/   if( !pThis->IsAbortingImport() )
/*N*/   {
/*N*/       const SvxLinkManager& rLnkMgr = pThis->pDoc->GetLinkManager();
/*N*/       const ::binfilter::SvBaseLinks& rLnks = rLnkMgr.GetLinks();
/*N*/       for( USHORT n = rLnks.Count(); n; )
/*N*/       {
/*N*/           ::binfilter::SvBaseLink* pLnk = &(*rLnks[ --n ]);
/*N*/           if( pLnk && OBJECT_CLIENT_GRF == pLnk->GetObjType() &&
/*N*/               pLnk->ISA( SwBaseLink ) )
/*N*/           {
/*N*/               ::binfilter::SvLinkSource* pLnkObj = pLnk->GetObj();
/*N*/               if( pLnkObj && pLnkObj->IsPending() &&
/*N*/                   !((SwBaseLink*)pLnk)->IsShowQuickDrawBmp() )
/*N*/               {
/*?*/                   bSttTimer = TRUE;
/*?*/                   break;
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }

/*N*/   if( bSttTimer )
/*?*/       pThis->aFinishedTimer.Start();
/*N*/   else
/*N*/   {
/*N*/       BOOL bIsModifiedEnabled = pThis->IsEnableSetModified();
/*N*/       pThis->EnableSetModified( FALSE );
/*N*/       pThis->FinishedLoading( SFX_LOADED_MAINDOCUMENT | SFX_LOADED_IMAGES );
/*N*/       pThis->EnableSetModified( bIsModifiedEnabled );
/*N*/
/*N*/       pThis->GetDoc()->StartIdleTimer();
/*N*/   }
/*N*/   return 0;
/*N*/ }


// eine Uebertragung wird abgebrochen (wird aus dem SFX gerufen)
/*N*/ void SwDocShell::CancelTransfers()
/*N*/ {
/*N*/   // alle Links vom LinkManager Canceln
/*N*/   aFinishedTimer.Stop();
/*N*/   pDoc->GetLinkManager().CancelTransfers();
/*N*/   SfxObjectShell::CancelTransfers();
/*N*/ }

/*N*/ Sequence< OUString >  SwDocShell::GetEventNames()
/*N*/ {
/*N*/   Sequence< OUString > aRet = SfxObjectShell::GetEventNames();
/*N*/   sal_Int32 nLen = aRet.getLength();
/*N*/   aRet.realloc(nLen + 2);
/*N*/   OUString* pNames = aRet.getArray();
/*N*/   pNames[nLen++] = OUString( RTL_CONSTASCII_USTRINGPARAM( "OnMailMerge" ));
/*N*/   pNames[nLen] = OUString( RTL_CONSTASCII_USTRINGPARAM( "OnPageCountChange" ));
/*N*/   return aRet;
/*N*/ }
/*N*/ void SwTmpPersist::FillClass( SvGlobalName * pClassName,
/*N*/                           ULONG * pClipFormat,
/*N*/                           String * pAppName,
/*N*/                           String * pLongUserName,
/*N*/                           String * pUserName,
/*N*/                           long nFileFormat ) const
/*N*/ {
/*N*/   pDShell->SwDocShell::FillClass( pClassName, pClipFormat, pAppName,
/*N*/                                   pLongUserName, pUserName, nFileFormat );
/*N*/ }

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
