/*************************************************************************
 *
 *  $RCSfile: sw_swserv.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 17:12:56 $
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

// auto strip #ifndef _SVSTOR_HXX //autogen
// auto strip #include <so3/svstor.hxx>
// auto strip #endif
#ifndef _SVXLINKMGR_HXX
#include <bf_svx/linkmgr.hxx>
#endif
#ifndef _COM_SUN_STAR_UNO_SEQUENCE_H_
#include <com/sun/star/uno/Sequence.h>
#endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif
#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif

#ifndef _DOC_HXX
#include <doc.hxx>
#endif
// auto strip #ifndef _SWTYPES_HXX
// auto strip #include <swtypes.hxx>
// auto strip #endif
#ifndef _SWSERV_HXX
#include <swserv.hxx>
#endif
#ifndef _SWBASLNK_HXX
#include <swbaslnk.hxx>
#endif
#ifndef _MVSAVE_HXX
#include <mvsave.hxx>
#endif
#ifndef _BOOKMRK_HXX
#include <bookmrk.hxx>
#endif
#ifndef _PAM_HXX
#include <pam.hxx>
#endif
// auto strip #ifndef _NODE_HXX
// auto strip #include <node.hxx>
// auto strip #endif
// auto strip #ifndef _SHELLIO_HXX
// auto strip #include <shellio.hxx>
// auto strip #endif

#ifndef _SWERROR_H
#include <swerror.h>
#endif
namespace binfilter {

/*N*/ SV_IMPL_REF( SwServerObject )

/*N*/ SwServerObject::~SwServerObject()
/*N*/ {
/*N*/ }


//STRIP001 BOOL SwServerObject::GetData( ::com::sun::star::uno::Any & rData,
//STRIP001                                  const String & rMimeType, BOOL )
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001  WriterRef xWrt;
//STRIP001  switch( SotExchange::GetFormatIdFromMimeType( rMimeType ) )
//STRIP001  {
//STRIP001  case FORMAT_STRING:
//STRIP001      ::GetASCWriter( aEmptyStr, xWrt );
//STRIP001      break;
//STRIP001
//STRIP001  case FORMAT_RTF:
//STRIP001      ::GetRTFWriter( aEmptyStr, xWrt );
//STRIP001      break;
//STRIP001  }
//STRIP001
//STRIP001  if( xWrt.Is() )
//STRIP001  {
//STRIP001      SwPaM* pPam = 0;
//STRIP001      switch( eType )
//STRIP001      {
//STRIP001      case BOOKMARK_SERVER:
//STRIP001          if( CNTNT_TYPE.pBkmk->GetOtherPos() )
//STRIP001          {
//STRIP001              // Bereich aufspannen
//STRIP001              pPam = new SwPaM( CNTNT_TYPE.pBkmk->GetPos(),
//STRIP001                              *CNTNT_TYPE.pBkmk->GetOtherPos() );
//STRIP001          }
//STRIP001          break;
//STRIP001
//STRIP001      case TABLE_SERVER:
//STRIP001          pPam = new SwPaM( *CNTNT_TYPE.pTblNd,
//STRIP001                          *CNTNT_TYPE.pTblNd->EndOfSectionNode() );
//STRIP001          break;
//STRIP001
//STRIP001      case SECTION_SERVER:
//STRIP001          pPam = new SwPaM( SwPosition( *CNTNT_TYPE.pSectNd ) );
//STRIP001          pPam->Move( fnMoveForward );
//STRIP001          pPam->SetMark();
//STRIP001          pPam->GetPoint()->nNode = *CNTNT_TYPE.pSectNd->EndOfSectionNode();
//STRIP001          pPam->Move( fnMoveBackward );
//STRIP001          break;
//STRIP001      }
//STRIP001
//STRIP001      if( pPam )
//STRIP001      {
//STRIP001          // Stream anlegen
//STRIP001          SvMemoryStream aMemStm( 65535, 65535 );
//STRIP001          SwWriter aWrt( aMemStm, *pPam, FALSE );
//STRIP001          if( !IsError( aWrt.Write( xWrt )) )
//STRIP001          {
//STRIP001              aMemStm << '\0';        // append a zero char
//STRIP001              rData <<= ::com::sun::star::uno::Sequence< sal_Int8 >(
//STRIP001                                      (sal_Int8*)aMemStm.GetData(),
//STRIP001                                      aMemStm.Seek( STREAM_SEEK_TO_END ) );
//STRIP001              bRet = TRUE;
//STRIP001          }
//STRIP001
//STRIP001          delete pPam;
//STRIP001      }
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }


//STRIP001 BOOL SwServerObject::SetData( const String & rMimeType,
//STRIP001                  const ::com::sun::star::uno::Any& rData )
//STRIP001 {
//STRIP001  // set new data into the "server" -> at first nothing to do
//STRIP001  return FALSE;
//STRIP001 }


//STRIP001 void SwServerObject::SendDataChanged( const SwPosition& rPos )
//STRIP001 {
//STRIP001  // ist an unseren Aenderungen jemand interessiert ?
//STRIP001  if( HasDataLinks() )
//STRIP001  {
//STRIP001      int bCall = FALSE;
//STRIP001      const SwStartNode* pNd = 0;
//STRIP001      switch( eType )
//STRIP001      {
//STRIP001      case BOOKMARK_SERVER:
//STRIP001          if( CNTNT_TYPE.pBkmk->GetOtherPos() )
//STRIP001          {
//STRIP001              SwBookmark& rBkmk = *CNTNT_TYPE.pBkmk;
//STRIP001              bCall = rBkmk.GetPos() < *rBkmk.GetOtherPos()
//STRIP001                  ? ( rBkmk.GetPos() <= rPos && rPos < *rBkmk.GetOtherPos() )
//STRIP001                  : ( *rBkmk.GetOtherPos() <= rPos && rPos < rBkmk.GetPos() );
//STRIP001          }
//STRIP001          break;
//STRIP001
//STRIP001      case TABLE_SERVER:      pNd = CNTNT_TYPE.pTblNd;    break;
//STRIP001      case SECTION_SERVER:    pNd = CNTNT_TYPE.pSectNd;   break;
//STRIP001      }
//STRIP001      if( pNd )
//STRIP001      {
//STRIP001          register ULONG nNd = rPos.nNode.GetIndex();
//STRIP001          bCall = pNd->GetIndex() < nNd && nNd < pNd->EndOfSectionIndex();
//STRIP001      }
//STRIP001
//STRIP001      if( bCall )
//STRIP001      {
//STRIP001          // Recursionen erkennen und flaggen
//STRIP001          IsLinkInServer( 0 );
//STRIP001          SvLinkSource::NotifyDataChanged();
//STRIP001      }
//STRIP001  }
//STRIP001  // sonst melden wir uns ab !!
//STRIP001 // ????? JP 27.06.95: geht das so ????
//STRIP001 //   else
//STRIP001 //       Closed();
//STRIP001 }


//STRIP001 void SwServerObject::SendDataChanged( const SwPaM& rRange )
//STRIP001 {
//STRIP001  // ist an unseren Aenderungen jemand interessiert ?
//STRIP001  if( HasDataLinks() )
//STRIP001  {
//STRIP001      int bCall = FALSE;
//STRIP001      const SwStartNode* pNd = 0;
//STRIP001      const SwPosition* pStt = rRange.Start(), *pEnd = rRange.End();
//STRIP001      switch( eType )
//STRIP001      {
//STRIP001      case BOOKMARK_SERVER:
//STRIP001          if( CNTNT_TYPE.pBkmk->GetOtherPos() )
//STRIP001          {
//STRIP001              SwBookmark& rBkmk = *CNTNT_TYPE.pBkmk;
//STRIP001              const SwPosition* pBkStt = &rBkmk.GetPos(),
//STRIP001                              * pBkEnd = rBkmk.GetOtherPos();
//STRIP001              if( *pBkStt > *pBkEnd )
//STRIP001              {
//STRIP001                  const SwPosition* pTmp = pBkStt;
//STRIP001                  pBkStt = pBkEnd;
//STRIP001                  pBkEnd = pTmp;
//STRIP001              }
//STRIP001              bCall = *pStt <= *pBkEnd && *pEnd > *pBkStt;
//STRIP001          }
//STRIP001          break;
//STRIP001
//STRIP001      case TABLE_SERVER:      pNd = CNTNT_TYPE.pTblNd;    break;
//STRIP001      case SECTION_SERVER:    pNd = CNTNT_TYPE.pSectNd;   break;
//STRIP001      }
//STRIP001      if( pNd )
//STRIP001      {
//STRIP001          // liegt der Start-Bereich im Node Bereich ?
//STRIP001          bCall = pStt->nNode.GetIndex() <  pNd->EndOfSectionIndex() &&
//STRIP001                  pEnd->nNode.GetIndex() >= pNd->GetIndex();
//STRIP001      }
//STRIP001
//STRIP001      if( bCall )
//STRIP001      {
//STRIP001          // Recursionen erkennen und flaggen
//STRIP001          IsLinkInServer( 0 );
//STRIP001          SvLinkSource::NotifyDataChanged();
//STRIP001      }
//STRIP001  }
//STRIP001  // sonst melden wir uns ab !!
//STRIP001 // ????? JP 27.06.95: geht das so ????
//STRIP001 //   else
//STRIP001 //       Closed();
//STRIP001 }


/*N*/ BOOL SwServerObject::IsLinkInServer( const SwBaseLink* pChkLnk ) const
/*N*/ {
/*N*/   ULONG nSttNd = 0, nEndNd = 0;
/*N*/   xub_StrLen nStt, nEnd;
/*N*/   const SwNode* pNd = 0;
/*N*/   const SwNodes* pNds = 0;
/*N*/
/*N*/   switch( eType )
/*N*/   {
/*?*/   case BOOKMARK_SERVER:
/*?*/       if( CNTNT_TYPE.pBkmk->GetOtherPos() )
/*?*/       {
/*?*/           SwBookmark& rBkmk = *CNTNT_TYPE.pBkmk;
/*?*/           const SwPosition* pStt = &rBkmk.GetPos(),
/*?*/                           * pEnd = rBkmk.GetOtherPos();
/*?*/           if( *pStt > *pEnd )
/*?*/           {
/*?*/               const SwPosition* pTmp = pStt;
/*?*/               pStt = pEnd;
/*?*/               pEnd = pTmp;
/*?*/           }
/*?*/
/*?*/           nSttNd = pStt->nNode.GetIndex();
/*?*/           nStt = pStt->nContent.GetIndex();
/*?*/           nEndNd = pEnd->nNode.GetIndex();
/*?*/           nEnd = pEnd->nContent.GetIndex();
/*?*/           pNds = &pStt->nNode.GetNodes();
/*?*/       }
/*?*/       break;
/*?*/
/*?*/   case TABLE_SERVER:      pNd = CNTNT_TYPE.pTblNd;    break;
/*?*/   case SECTION_SERVER:    pNd = CNTNT_TYPE.pSectNd;   break;
/*?*/
/*N*/   case SECTION_SERVER+1:
/*N*/       return TRUE;
/*N*/   }
/*N*/
/*N*/   if( pNd )
/*N*/   {
/*N*/       nSttNd = pNd->GetIndex();
/*N*/       nEndNd = pNd->EndOfSectionIndex();
/*N*/       nStt = 0, nEnd = USHRT_MAX;
/*N*/       pNds = &pNd->GetNodes();
/*N*/   }
/*N*/
/*N*/   if( nSttNd && nEndNd )
/*N*/   {
/*N*/       // LinkManager besorgen:
/*N*/       const ::so3::SvBaseLinks& rLnks = pNds->GetDoc()->GetLinkManager().GetLinks();
/*N*/
/*N*/ // um Rekursionen zu Verhindern: ServerType umsetzen!
/*N*/ SwServerObject::ServerModes eSave = eType;
/*N*/ if( !pChkLnk )
/*N*/ // sowas sollte man nicht tun, wer weiss schon, wie gross ein enum ist
/*N*/ // ICC nimmt keinen int
/*N*/ // #41723#
/*N*/ //    *((int*)&eType) = SECTION_SERVER+1;
/*N*/   ((SwServerObject*)this)->eType = NONE_SERVER;
/*N*/       for( USHORT n = rLnks.Count(); n; )
/*N*/       {
/*N*/           const ::so3::SvBaseLink* pLnk = &(*rLnks[ --n ]);
/*N*/           if( pLnk && OBJECT_CLIENT_GRF != pLnk->GetObjType() &&
/*N*/               pLnk->ISA( SwBaseLink ) &&
/*N*/               !((SwBaseLink*)pLnk)->IsNoDataFlag() &&
/*N*/               ((SwBaseLink*)pLnk)->IsInRange( nSttNd, nEndNd, nStt, nEnd ))
/*N*/           {
/*N*/               if( pChkLnk )
/*N*/               {
/*N*/                   if( pLnk == pChkLnk ||
/*N*/                       ((SwBaseLink*)pLnk)->IsRecursion( pChkLnk ) )
/*N*/                       return TRUE;
/*N*/               }
/*N*/               else if( ((SwBaseLink*)pLnk)->IsRecursion( (SwBaseLink*)pLnk ) )
/*N*/                   ((SwBaseLink*)pLnk)->SetNoDataFlag();
/*N*/           }
/*N*/       }
/*N*/ if( !pChkLnk )
/*N*/   //  *((int*)&eType) = eSave;
/*?*/   ((SwServerObject*)this)->eType = eSave;
/*N*/   }
/*N*/
/*N*/   return FALSE;
/*N*/ }

/*  */


/*N*/ SwDataChanged::SwDataChanged( const SwPaM& rPam, USHORT nTyp )
/*N*/   : pPam( &rPam ), nType( nTyp ), pDoc( rPam.GetDoc() ), pPos( 0 )
/*N*/ {
/*N*/   nNode = rPam.GetPoint()->nNode.GetIndex();
/*N*/   nCntnt = rPam.GetPoint()->nContent.GetIndex();
/*N*/ }


/*N*/ SwDataChanged::SwDataChanged( SwDoc* pDoc, const SwPosition& rPos, USHORT nTyp )
/*N*/   : pPam( 0 ), nType( nTyp ), pDoc( pDoc ), pPos( &rPos )
/*N*/ {
/*N*/   nNode = rPos.nNode.GetIndex();
/*N*/   nCntnt = rPos.nContent.GetIndex();
/*N*/ }
/*N*/

/*N*/ SwDataChanged::~SwDataChanged()
/*N*/ {
/*N*/   // JP 09.04.96: nur wenn das Layout vorhanden ist ( also waehrend der
/*N*/   //              Eingabe)
/*N*/   if( pDoc->GetRootFrm() )
/*N*/   {
/*N*/       const ::so3::SvLinkSources& rServers = pDoc->GetLinkManager().GetServers();
/*N*/
/*N*/       for( USHORT nCnt = rServers.Count(); nCnt; )
/*N*/       {
/*N*/           ::so3::SvLinkSourceRef refObj( rServers[ --nCnt ] );
/*N*/           // noch jemand am Object interessiert ?
/*?*/           if( refObj->HasDataLinks() && refObj->ISA( SwServerObject ))
/*?*/           {
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001   SwServerObject& rObj = *(SwServerObject*)&refObj;
//STRIP001 /*?*/                if( pPos )
//STRIP001 /*?*/                    rObj.SendDataChanged( *pPos );
//STRIP001 /*?*/                else
//STRIP001 /*?*/                    rObj.SendDataChanged( *pPam );
/*?*/           }
/*?*/
/*?*/           // sollte jetzt gar keine Verbindung mehr bestehen
/*?*/           if( !refObj->HasDataLinks() )
/*?*/           {
/*?*/               // dann raus aus der Liste (Object bleibt aber bestehen!)
/*?*/               // falls es noch da ist !!
/*?*/               if( nCnt < rServers.Count() && &refObj == rServers[ nCnt ] )
/*?*/                   pDoc->GetLinkManager().RemoveServer( nCnt, 1 );
/*?*/           }
/*?*/       }
/*N*/   }
/*N*/ }




}
