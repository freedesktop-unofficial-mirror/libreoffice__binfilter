/*************************************************************************
 *
 *  $RCSfile: sw_visiturl.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-04 14:44:43 $
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


#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif
// auto strip #ifndef _ERRHDL_HXX
// auto strip #include <errhdl.hxx>
// auto strip #endif

#ifndef _SFXDOCFILE_HXX //autogen
#include <bf_sfx2/docfile.hxx>
#endif
#ifndef _INETHIST_HXX //autogen
#include <svtools/inethist.hxx>
#endif
// auto strip #ifndef _URLOBJ_HXX //autogen
// auto strip #include <tools/urlobj.hxx>
// auto strip #endif

#ifndef _FMTINFMT_HXX //autogen
#include <fmtinfmt.hxx>
#endif
#ifndef _TXTINET_HXX //autogen
#include <txtinet.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _VISITURL_HXX
#include <visiturl.hxx>
#endif
#ifndef _HINTS_HXX
#include <hints.hxx>
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>
#endif
#ifndef _VISCRS_HXX
#include <viscrs.hxx>
#endif
#ifndef _EDITSH_HXX
#include <editsh.hxx>
#endif
#ifndef _DOCSH_HXX
#include <docsh.hxx>
#endif
namespace binfilter {


/*N*/ SwURLStateChanged::SwURLStateChanged( const SwDoc* pD )
/*N*/   : pDoc( pD )
/*N*/ {
/*N*/   StartListening( *INetURLHistory::GetOrCreate() );
/*N*/ }

/*N*/ SwURLStateChanged::~SwURLStateChanged()
/*N*/ {
/*N*/   EndListening( *INetURLHistory::GetOrCreate() );
/*N*/ }

/*N*/ void SwURLStateChanged::Notify( SfxBroadcaster& rBC, const SfxHint& rHint )
/*N*/ {
/*N*/   if( rHint.ISA( INetURLHistoryHint ) && pDoc->GetRootFrm() )
/*N*/   {
/*N*/       // diese URL wurde veraendert:
/*N*/       const INetURLObject* pIURL = ((INetURLHistoryHint&)rHint).GetObject();
/*N*/       String sURL( pIURL->GetMainURL( INetURLObject::NO_DECODE ) ), sBkmk;
/*N*/
/*N*/       SwEditShell* pESh = pDoc->GetEditShell();
/*N*/
/*N*/       if( pDoc->GetDocShell() && pDoc->GetDocShell()->GetMedium() &&
/*N*/           // falls das unser Doc ist, kann es auch lokale Spruenge geben!
/*N*/           sURL == pDoc->GetDocShell()->GetMedium()->GetName() )
/*?*/           (sBkmk = pIURL->GetMark()).Insert( INET_MARK_TOKEN, 0 );
/*N*/
/*N*/       BOOL bAction = FALSE, bUnLockView = FALSE;
/*N*/       const SwFmtINetFmt* pItem;
/*N*/       const SwTxtINetFmt* pTxtAttr;
/*N*/       const SwTxtNode* pTxtNd;
/*N*/       USHORT n, nMaxItems = pDoc->GetAttrPool().GetItemCount( RES_TXTATR_INETFMT );
/*N*/       for( n = 0; n < nMaxItems; ++n )
/*N*/           if( 0 != (pItem = (SwFmtINetFmt*)pDoc->GetAttrPool().GetItem(
/*N*/               RES_TXTATR_INETFMT, n ) ) &&
/*N*/               ( pItem->GetValue() == sURL ||
/*N*/                   ( sBkmk.Len() && pItem->GetValue() == sBkmk )) &&
/*N*/               0 != ( pTxtAttr = pItem->GetTxtINetFmt()) &&
/*N*/               0 != ( pTxtNd = pTxtAttr->GetpTxtNode() ) )
/*N*/           {
/*?*/               if( !bAction && pESh )
/*?*/               {
/*?*/                   pESh->StartAllAction();
/*?*/                   bAction = TRUE;
/*?*/                   bUnLockView = !pESh->IsViewLocked();
/*?*/                   pESh->LockView( TRUE );
/*?*/               }
/*?*/               ((SwTxtINetFmt*)pTxtAttr)->SetValidVis( FALSE );
/*?*/               const SwTxtAttr* pAttr = pTxtAttr;
/*?*/               SwUpdateAttr aUpdateAttr( *pAttr->GetStart(),
/*?*/                                         *pAttr->GetEnd(),
/*?*/                                         RES_FMT_CHG );
/*?*/               ((SwTxtNode*)pTxtNd)->SwCntntNode::Modify( &aUpdateAttr,
/*?*/                                                           &aUpdateAttr );
/*?*/           }
/*N*/
/*N*/       if( bAction )
/*?*/           pESh->EndAllAction();
/*N*/       if( bUnLockView )
/*?*/           pESh->LockView( FALSE );
/*N*/   }
/*N*/ }

    // erfrage ob die URL besucht war. Uebers Doc, falls nur ein Bookmark
    // angegeben ist. Dann muss der Doc. Name davor gesetzt werden!
/*N*/ BOOL SwDoc::IsVisitedURL( const String& rURL ) const
/*N*/ {
/*N*/ #if OSL_DEBUG_LEVEL > 1
/*N*/   static long nTmp = 0;
/*N*/   ++nTmp;
/*N*/ #endif
/*N*/
/*N*/   BOOL bRet = FALSE;
/*N*/   if( rURL.Len() )
/*N*/   {
/*N*/       INetURLHistory *pHist = INetURLHistory::GetOrCreate();
/*N*/       if( '#' == rURL.GetChar( 0 ) && pDocShell && pDocShell->GetMedium() )
/*N*/       {
/*N*/           INetURLObject aIObj( pDocShell->GetMedium()->GetURLObject() );
/*N*/           aIObj.SetMark( rURL.Copy( 1 ) );
/*N*/           bRet = pHist->QueryUrl( aIObj );
/*N*/       }
/*N*/       else
/*N*/           bRet = pHist->QueryUrl( rURL );
/*N*/
/*N*/       // dann  wollen wird auch ueber Statusaenderungen in der History
/*N*/       // informiert werden!
/*N*/       if( !pURLStateChgd )
/*N*/       {
/*N*/           SwDoc* pD = (SwDoc*)this;
/*N*/           pD->pURLStateChgd = new SwURLStateChanged( this );
/*N*/       }
/*N*/   }
/*N*/   return bRet;
/*N*/ }



}
