/*************************************************************************
 *
 *  $RCSfile: svx_linkmgr.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:40:43 $
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

#pragma hdrstop

#ifndef _COM_SUN_STAR_UNO_SEQUENCE_H_
#include <com/sun/star/uno/Sequence.h>
#endif
#include <sot/formats.hxx>
#ifndef _SOT_EXCHANGE_HXX //autogen
#include <sot/exchange.hxx>
#endif
#ifndef _SV_GRAPH_HXX
#include <vcl/graph.hxx>
#endif
#ifndef _LNKBASE_HXX //autogen
#include <so3/lnkbase.hxx>
#endif
#ifndef _URLOBJ_HXX //autogen
#include <tools/urlobj.hxx>
#endif
#ifndef _IPOBJ_HXX //autogen
#include <so3/ipobj.hxx>
#endif
#ifndef _SFXSTRITEM_HXX //autogen
#include <svtools/stritem.hxx>
#endif
#ifndef _SFXENUMITEM_HXX //autogen
#include <svtools/eitem.hxx>
#endif
#ifndef _SFXINTITEM_HXX //autogen
#include <svtools/intitem.hxx>
#endif
#ifndef _SFXRECTITEM_HXX //autogen
#include <svtools/rectitem.hxx>
#endif
#ifndef _SFXAPP_HXX
#include <bf_sfx2/app.hxx>
#endif
#ifndef _SFXREQUEST_HXX
#include <bf_sfx2/request.hxx>
#endif
#ifndef _SFX_OBJSH_HXX //autogen
#include <bf_sfx2/objsh.hxx>
#endif
#ifndef _SFX_INTERNO_HXX //autogen
#include <bf_sfx2/interno.hxx>
#endif
#ifndef _SFXDISPATCH_HXX //autogen
#include <bf_sfx2/dispatch.hxx>
#endif
#ifndef _UNOTOOLS_CHARCLASS_HXX
#include <unotools/charclass.hxx>
#endif
#ifndef _UNOTOOLS_LOCALFILEHELPER_HXX
#include <unotools/localfilehelper.hxx>
#endif
#ifndef _SFXITEMSET_HXX
#include <svtools/itemset.hxx>
#endif
#ifndef SVTOOLS_URIHELPER_HXX
#include <svtools/urihelper.hxx>
#endif
#include <com/sun/star/datatransfer/DataFlavor.hpp>

#include "linkmgr.hxx"
#include "fileobj.hxx"
#include "dialmgr.hxx"
#include "dialogs.hrc"
#include "unolingu.hxx"
namespace binfilter {

//STRIP001 class SvxInternalLink : public ::so3::SvLinkSource
//STRIP001 {
//STRIP001 public:
//STRIP001  SvxInternalLink() {}
//STRIP001
//STRIP001  virtual BOOL Connect( ::so3::SvBaseLink* );
//STRIP001 };


/*N*/ SvxLinkManager::SvxLinkManager( SvPersist * pPersist )
/*N*/ {
/*N*/   SvLinkManager::SetPersist( pPersist );
/*N*/ }

/*N*/ ::so3::SvLinkSourceRef SvxLinkManager::CreateObj( ::so3::SvBaseLink * pLink )
/*N*/ {
/*N*/   switch( pLink->GetObjType() )
/*N*/   {
/*N*/   case OBJECT_CLIENT_FILE:
/*N*/   case OBJECT_CLIENT_GRF:
/*N*/       return new SvFileObject;
/*N*/
/*N*/   case OBJECT_INTERN:
/*?*/       {DBG_BF_ASSERT(0, "STRIP");} //STRIP001 return new SvxInternalLink();
/*N*/   }
/*?*/   return SvLinkManager::CreateObj( pLink );
/*N*/ }


/*N*/ BOOL SvxLinkManager::InsertFileLink( ::so3::SvBaseLink& rLink,
/*N*/                                   USHORT nFileType,
/*N*/                                   const String& rFileNm,
/*N*/                                   const String* pFilterNm,
/*N*/                                   const String* pRange )
/*N*/ {
/*N*/   if( !( OBJECT_CLIENT_SO & rLink.GetObjType() ))
/*N*/       return FALSE;
/*N*/
/*N*/   String sCmd( rFileNm );
/*N*/   sCmd += ::so3::cTokenSeperator;
/*N*/   if( pRange )
/*N*/       sCmd += *pRange;
/*N*/   if( pFilterNm )
/*N*/       ( sCmd += ::so3::cTokenSeperator ) += *pFilterNm;
/*N*/
/*N*/   return SvLinkManager::InsertLink( &rLink, nFileType,
/*N*/                                   ::so3::LINKUPDATE_ONCALL, &sCmd );
/*N*/ }

//STRIP001 BOOL SvxLinkManager::InsertFileLink( ::so3::SvBaseLink& rLink )
//STRIP001 {
//STRIP001  if( OBJECT_CLIENT_FILE == ( OBJECT_CLIENT_FILE & rLink.GetObjType() ))
//STRIP001      return SvLinkManager::InsertLink( &rLink, rLink.GetObjType(),
//STRIP001                                          ::so3::LINKUPDATE_ONCALL );
//STRIP001  return FALSE;
//STRIP001 }

        // erfrage die Strings fuer den Dialog
/*N*/ BOOL SvxLinkManager::GetDisplayNames( const ::so3::SvBaseLink* pBaseLink,
/*N*/                                       String* pType,
/*N*/                                       String* pFile,
/*N*/                                       String* pLink,
/*N*/                                       String* pFilter ) const
/*N*/ {
/*N*/   BOOL bRet = FALSE;
/*N*/   const String sLNm( pBaseLink->GetLinkSourceName() );
/*N*/   if( sLNm.Len() )
/*N*/       switch( pBaseLink->GetObjType() )
/*N*/       {
/*N*/       case OBJECT_CLIENT_FILE:
/*N*/       case OBJECT_CLIENT_GRF:
/*N*/           {
/*N*/               USHORT nPos = 0;
/*N*/               String sFile( sLNm.GetToken( 0, ::so3::cTokenSeperator, nPos ) );
/*N*/               String sRange( sLNm.GetToken( 0, ::so3::cTokenSeperator, nPos ) );
/*N*/
/*N*/               if( pFile )
/*N*/                   *pFile = sFile;
/*N*/               if( pLink )
/*N*/                   *pLink = sRange;
/*N*/               if( pFilter )
/*N*/                   *pFilter = sLNm.Copy( nPos );
/*N*/
/*N*/               if( pType )
/*?*/                   *pType = String( ResId(
/*?*/                               OBJECT_CLIENT_FILE == pBaseLink->GetObjType()
/*?*/                                       ? RID_SVXSTR_FILELINK
/*?*/                                       : RID_SVXSTR_GRAFIKLINK
/*?*/                                       , DIALOG_MGR() ));
/*N*/
/*N*/               bRet = TRUE;
/*N*/           }
/*N*/           break;
/*N*/       default:
/*N*/           bRet = SvLinkManager::GetDisplayNames( pBaseLink, pType, pFile,
/*N*/                                                   pLink, pFilter );
/*N*/           break;
/*N*/       }
/*N*/   return bRet;
/*N*/ }

// eine Uebertragung wird abgebrochen, also alle DownloadMedien canceln
// (ist zur Zeit nur fuer die FileLinks interressant!)
/*N*/ void SvxLinkManager::CancelTransfers()
/*N*/ {
/*N*/   SvFileObject* pFileObj;
/*N*/   ::so3::SvBaseLink* pLnk;
/*N*/
/*N*/   const ::so3::SvBaseLinks& rLnks = GetLinks();
/*N*/   for( USHORT n = rLnks.Count(); n; )
/*N*/       if( 0 != ( pLnk = &(*rLnks[ --n ])) &&
/*N*/           OBJECT_CLIENT_FILE == (OBJECT_CLIENT_FILE & pLnk->GetObjType()) &&
/*N*/           0 != ( pFileObj = (SvFileObject*)pLnk->GetObj() ) )
/*N*/ //            0 != ( pFileObj = (SvFileObject*)SvFileObject::ClassFactory()->
/*N*/ //                                    CastAndAddRef( pLnk->GetObj() )) )
/*N*/           pFileObj->CancelTransfers();
/*N*/ }

//STRIP001 void SvxLinkManager::SetTransferPriority( ::so3::SvBaseLink& rLink, USHORT nPrio )
//STRIP001 {
//STRIP001  SvFileObject* pFileObj =
//STRIP001 //       (SvFileObject*)SvFileObject::ClassFactory()->
//STRIP001 //                                   CastAndAddRef( rLink.GetObj() );
//STRIP001          OBJECT_CLIENT_FILE == (OBJECT_CLIENT_FILE & rLink.GetObjType()) ?
//STRIP001              (SvFileObject*)rLink.GetObj() : 0;
//STRIP001
//STRIP001  if( pFileObj )
//STRIP001      pFileObj->SetTransferPriority( nPrio );
//STRIP001 }


    // um Status Informationen aus dem FileObject an den BaseLink zu
    // senden, gibt es eine eigene ClipBoardId. Das SvData-Object hat
    // dann die entsprechenden Informationen als String.
    // Wird zur Zeit fuer FileObject in Verbindung mit JavaScript benoetigt
    // - das braucht Informationen ueber Load/Abort/Error
/*N*/ ULONG SvxLinkManager::RegisterStatusInfoId()
/*N*/ {
/*N*/   static ULONG nFormat = 0;
/*N*/
/*N*/   if( !nFormat )
/*N*/   {
/*N*/ // wie sieht die neue Schnittstelle aus?
/*N*/ //        nFormat = Exchange::RegisterFormatName( "StatusInfo vom SvxInternalLink" );
/*N*/       nFormat = SotExchange::RegisterFormatName(
/*N*/                   String::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM(
/*N*/                               "StatusInfo vom SvxInternalLink" )));
/*N*/   }
/*N*/   return nFormat;
/*N*/ }

// ----------------------------------------------------------------------

/*N*/ BOOL SvxLinkManager::GetGraphicFromAny( const String& rMimeType,
/*N*/                               const ::com::sun::star::uno::Any & rValue,
/*N*/                               Graphic& rGrf )
/*N*/ {
/*?*/   BOOL bRet = FALSE;
/*?*/   ::com::sun::star::uno::Sequence< sal_Int8 > aSeq;
/*?*/   if( rValue.hasValue() && ( rValue >>= aSeq ) )
/*?*/   {
/*?*/       SvMemoryStream aMemStm( (void*)aSeq.getConstArray(), aSeq.getLength(),
/*?*/                               STREAM_READ );
/*?*/       aMemStm.Seek( 0 );
/*?*/
/*?*/       switch( SotExchange::GetFormatIdFromMimeType( rMimeType ) )
/*?*/       {
/*?*/       case SOT_FORMATSTR_ID_SVXB:
/*?*/           {
/*?*/               aMemStm >> rGrf;
/*?*/               bRet = TRUE;
/*?*/           }
/*?*/           break;
/*?*/       case FORMAT_GDIMETAFILE:
/*?*/           {
/*?*/               GDIMetaFile aMtf;
/*?*/               aMtf.Read( aMemStm );
/*?*/               rGrf = aMtf;
/*?*/               bRet = TRUE;
/*?*/           }
/*?*/           break;
/*?*/       case FORMAT_BITMAP:
/*?*/           {
/*?*/               Bitmap aBmp;
/*?*/               aMemStm >> aBmp;
/*?*/               rGrf = aBmp;
/*?*/               bRet = TRUE;
/*?*/           }
/*?*/           break;
/*?*/       }
/*?*/   }
/*?*/   return bRet;
/*N*/ }


// ----------------------------------------------------------------------
//STRIP001 String lcl_DDE_RelToAbs( const String& rTopic )
//STRIP001 {
//STRIP001  String sRet;
//STRIP001  INetURLObject aURL( rTopic );
//STRIP001  if( INET_PROT_NOT_VALID == aURL.GetProtocol() )
//STRIP001      utl::LocalFileHelper::ConvertSystemPathToURL( rTopic,
//STRIP001                                      INetURLObject::GetBaseURL(), sRet );
//STRIP001  if( !sRet.Len() )
//STRIP001      sRet = URIHelper::SmartRelToAbs( rTopic );
//STRIP001  return sRet;
//STRIP001 }

//STRIP001 BOOL SvxInternalLink::Connect( ::so3::SvBaseLink* pLink )
//STRIP001 {
//STRIP001  SfxObjectShell* pFndShell = 0;
//STRIP001  String sTopic, sItem, sReferer;
//STRIP001  if( pLink->GetLinkManager() &&
//STRIP001      pLink->GetLinkManager()->GetDisplayNames( pLink, 0, &sTopic, &sItem )
//STRIP001      && sTopic.Len() )
//STRIP001  {
//STRIP001      // erstmal nur ueber die DocumentShells laufen und die mit dem
//STRIP001      // Namen heraussuchen:
//STRIP001
//STRIP001      CharClass aCC( SvxCreateLocale( LANGUAGE_SYSTEM ));
//STRIP001      String sNm( sTopic ), sNmURL( lcl_DDE_RelToAbs( sTopic ) ),
//STRIP001             sTmp;
//STRIP001      aCC.toLower( sNm );
//STRIP001      aCC.toLower( sNmURL );
//STRIP001
//STRIP001      TypeId aType( TYPE(SfxObjectShell) );
//STRIP001
//STRIP001      BOOL bFirst = TRUE;
//STRIP001      SfxObjectShell* pShell = 0;
//STRIP001      SvInPlaceObjectRef aRef( pLink->GetLinkManager()->GetPersist());
//STRIP001      if( aRef.Is() )
//STRIP001      {
//STRIP001          // sch... SFX: das gerade gelesen Doc hat noch keinen Namen und
//STRIP001          // steht noch nicht in der Doc. Liste
//STRIP001          pShell = ((SfxInPlaceObject*)&aRef)->GetObjectShell();
//STRIP001
//STRIP001          if( pShell && pShell->GetMedium() )
//STRIP001          {
//STRIP001              sReferer = pShell->GetMedium()->GetName();
//STRIP001              if( !pShell->HasName()  )
//STRIP001                  sTmp = sReferer;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      if ( !pShell )
//STRIP001      {
//STRIP001          bFirst = FALSE;
//STRIP001          pShell = SfxObjectShell::GetFirst( &aType );
//STRIP001      }
//STRIP001
//STRIP001      while( pShell )
//STRIP001      {
//STRIP001          if( !sTmp.Len() )
//STRIP001              sTmp = pShell->GetTitle( SFX_TITLE_FULLNAME );
//STRIP001
//STRIP001          aCC.toLower( sTmp );
//STRIP001          if( sTmp == sNm || sTmp == sNmURL )     // die wollen wir haben
//STRIP001          {
//STRIP001              pFndShell = pShell;
//STRIP001              break;
//STRIP001          }
//STRIP001
//STRIP001          if( bFirst )
//STRIP001          {
//STRIP001              bFirst = FALSE;
//STRIP001              pShell = SfxObjectShell::GetFirst( &aType );
//STRIP001          }
//STRIP001          else
//STRIP001              pShell = SfxObjectShell::GetNext( *pShell, &aType );
//STRIP001
//STRIP001          sTmp.Erase();
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // empty topics are not allowed - which document is it
//STRIP001  if( !sTopic.Len() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  if( !pFndShell )
//STRIP001  {
//STRIP001      // dann versuche die Datei zu laden:
//STRIP001      INetURLObject aURL( sTopic );
//STRIP001      INetProtocol eOld = aURL.GetProtocol();
//STRIP001      aURL.SetURL( sTopic = lcl_DDE_RelToAbs( sTopic ) );
//STRIP001      if( INET_PROT_NOT_VALID != eOld ||
//STRIP001          INET_PROT_HTTP != aURL.GetProtocol() )
//STRIP001      {
//STRIP001          SfxStringItem aName( SID_FILE_NAME, sTopic );
//STRIP001             SfxBoolItem aMinimized(SID_MINIMIZEWINS, TRUE);
//STRIP001             SfxStringItem aTarget( SID_TARGETNAME, String::CreateFromAscii("_blank") );
//STRIP001          SfxStringItem aReferer( SID_REFERER, sReferer );
//STRIP001
//STRIP001             // #i14200# (DDE-link crashes wordprocessor)
//STRIP001             SfxAllItemSet aArgs( SFX_APP()->GetPool() );
//STRIP001             aArgs.Put(aReferer);
//STRIP001             aArgs.Put(aTarget);
//STRIP001             aArgs.Put(aMinimized);
//STRIP001             aArgs.Put(aName);
//STRIP001             SfxRequest aRequest( SID_OPENDOC, SFX_CALLMODE_SYNCHRON, aArgs );
//STRIP001             SFX_APP()->ExecuteSlot( aRequest );
//STRIP001             const SfxPoolItem*  pRet = aRequest.GetReturnValue();
//STRIP001
//STRIP001          if( pRet && pRet->ISA( SfxViewFrameItem ) &&
//STRIP001              ((SfxViewFrameItem*)pRet)->GetFrame() )
//STRIP001                 pFndShell = ((SfxViewFrameItem*)pRet)->GetFrame()->GetObjectShell();
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  BOOL bRet = FALSE;
//STRIP001  if( pFndShell )
//STRIP001  {
//STRIP001      ::so3::SvLinkSource* pNewSrc = pFndShell->DdeCreateLinkSource( sItem );
//STRIP001      if( pNewSrc )
//STRIP001      {
//STRIP001          bRet = TRUE;
//STRIP001
//STRIP001          ::com::sun::star::datatransfer::DataFlavor aFl;
//STRIP001          SotExchange::GetFormatDataFlavor( pLink->GetContentType(), aFl );
//STRIP001
//STRIP001          pLink->SetObj( pNewSrc );
//STRIP001          pNewSrc->AddDataAdvise( pLink, aFl.MimeType,
//STRIP001                              ::so3::LINKUPDATE_ONCALL == pLink->GetUpdateMode()
//STRIP001                                  ? ADVISEMODE_ONLYONCE
//STRIP001                                  : 0 );
//STRIP001      }
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }


}
