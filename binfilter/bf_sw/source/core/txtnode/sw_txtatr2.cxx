/*************************************************************************
 *
 *  $RCSfile: sw_txtatr2.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 18:02:40 $
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

#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif
// auto strip #ifndef _SFX_OBJSH_HXX //autogen
// auto strip #include <bf_sfx2/objsh.hxx>
// auto strip #endif
// auto strip #ifndef _SVX_XMLCNITM_HXX
// auto strip #include <bf_svx/xmlcnitm.hxx>
// auto strip #endif
// auto strip #ifndef _SVX_TWOLINESITEM_HXX
// auto strip #include <bf_svx/twolinesitem.hxx>
// auto strip #endif
#ifndef _TXTINET_HXX //autogen
#include <txtinet.hxx>
#endif
#ifndef _TXTATR_HXX //autogen
#include <txtatr.hxx>
#endif
#ifndef _FCHRFMT_HXX //autogen
#include <fchrfmt.hxx>
#endif
#ifndef _FMTINFMT_HXX //autogen
#include <fmtinfmt.hxx>
#endif
#ifndef _CHARFMT_HXX //autogen
#include <charfmt.hxx>
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>        // SwCharFmt, SwTxtNode
#endif
#ifndef _HINTS_HXX
#include <hints.hxx>        // SwCharFmt, SwUpdateAttr
#endif
#ifndef _POOLFMT_HXX
#include <poolfmt.hxx>      // RES_POOLCHR_INET_...
#endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _DOC_HXX
#include <doc.hxx>          // SwDoc
#endif
// auto strip #ifndef _FMTRUBY_HXX
// auto strip #include <fmtruby.hxx>
// auto strip #endif
// auto strip #ifndef _FMTHBSH_HXX //autogen
// auto strip #include <fmthbsh.hxx>
// auto strip #endif
namespace binfilter {

//STRIP001 TYPEINIT1(SwTxtINetFmt,SwClient);
//STRIP001 TYPEINIT1(SwTxtRuby,SwClient);

/*************************************************************************
 *                      class SwTxtHardBlank
 *************************************************************************/

//STRIP001 SwTxtHardBlank::SwTxtHardBlank( const SwFmtHardBlank& rAttr, xub_StrLen nStart )
//STRIP001  : SwTxtAttr( rAttr, nStart ),
//STRIP001  cChar( rAttr.GetChar() )
//STRIP001 {
//STRIP001  ASSERT( ' ' != cChar && '-' != cChar,
//STRIP001          "Invalid character for the HardBlank attribute - "
//STRIP001          "must be a normal unicode character" );
//STRIP001 }


/*************************************************************************
 *                      class SwTxtCharFmt
 *************************************************************************/

/*N*/ SwTxtCharFmt::SwTxtCharFmt( const SwFmtCharFmt& rAttr,
/*N*/                   xub_StrLen nStart, xub_StrLen nEnd )
/*N*/   : SwTxtAttrEnd( rAttr, nStart, nEnd ),
/*N*/   pMyTxtNd( 0 )
/*N*/ {
/*N*/   ((SwFmtCharFmt&)rAttr).pTxtAttr = this;
/*N*/   SetCharFmtAttr( TRUE );
/*N*/ }

/*N*/ SwTxtCharFmt::~SwTxtCharFmt( )
/*N*/ {
/*N*/ }

/*N*/ void SwTxtCharFmt::Modify( SfxPoolItem* pOld, SfxPoolItem* pNew )
/*N*/ {
/*N*/   USHORT nWhich = pOld ? pOld->Which() : pNew ? pNew->Which() : 0;
/*N*/ #ifndef PRODUCT
/*N*/   if ( (nWhich<RES_CHRATR_BEGIN || nWhich>RES_CHRATR_END)
/*N*/           && (nWhich!=RES_OBJECTDYING)
/*N*/           && (nWhich!=RES_ATTRSET_CHG)
/*N*/           && (nWhich!=RES_FMT_CHG) )
/*N*/       ASSERT(!this, "SwTxtCharFmt::Modify(): unbekanntes Modify!");
/*N*/ #endif
/*N*/
/*N*/   if( pMyTxtNd )
/*N*/   {
/*N*/       SwUpdateAttr aUpdateAttr( *GetStart(), *GetEnd(), nWhich );
/*N*/       pMyTxtNd->SwCntntNode::Modify( &aUpdateAttr, &aUpdateAttr );
/*N*/   }
/*N*/ }

    // erfrage vom Modify Informationen
/*N*/ BOOL SwTxtCharFmt::GetInfo( SfxPoolItem& rInfo ) const
/*N*/ {
/*N*/   if( RES_AUTOFMT_DOCNODE != rInfo.Which() || !pMyTxtNd ||
/*N*/       &pMyTxtNd->GetNodes() != ((SwAutoFmtGetDocNode&)rInfo).pNodes )
/*N*/       return TRUE;
/*N*/
/*N*/   ((SwAutoFmtGetDocNode&)rInfo).pCntntNode = pMyTxtNd;
/*N*/   return FALSE;
/*N*/ }

/*************************************************************************
 *                      class SwTxtINetFmt
 *************************************************************************/

/*N*/ SwTxtINetFmt::SwTxtINetFmt( const SwFmtINetFmt& rAttr,
/*N*/                           xub_StrLen nStart, xub_StrLen nEnd )
/*N*/   : SwTxtAttrEnd( rAttr, nStart, nEnd ),
/*N*/   SwClient( 0 ),
/*N*/     pMyTxtNd( 0 )
/*N*/ {
/*N*/   bValidVis = FALSE;
/*N*/   ((SwFmtINetFmt&)rAttr).pTxtAttr  = this;
/*N*/   SetCharFmtAttr( TRUE );
/*N*/ }

/*N*/ SwTxtINetFmt::~SwTxtINetFmt( )
/*N*/ {
/*N*/ }

/*N*/ SwCharFmt* SwTxtINetFmt::GetCharFmt()
/*N*/ {
/*N*/   const SwFmtINetFmt& rFmt = SwTxtAttrEnd::GetINetFmt();
/*N*/   SwCharFmt* pRet = NULL;
/*N*/
/*N*/   if( rFmt.GetValue().Len() )
/*N*/   {
/*N*/       const SwDoc* pDoc = GetTxtNode().GetDoc();
/*N*/       if( !IsValidVis() )
/*N*/       {
/*N*/           SetVisited( pDoc->IsVisitedURL( rFmt.GetValue() ) );
/*N*/           SetValidVis( TRUE );
/*N*/       }
/*N*/       USHORT nId;
/*N*/       const String& rStr = IsVisited() ? rFmt.GetVisitedFmt()
/*N*/                                          : rFmt.GetINetFmt();
/*N*/       if( rStr.Len() )
/*N*/           nId = IsVisited() ? rFmt.GetVisitedFmtId() : rFmt.GetINetFmtId();
/*N*/       else
/*N*/           nId = IsVisited() ? RES_POOLCHR_INET_VISIT : RES_POOLCHR_INET_NORMAL;
/*N*/
/*N*/       // JP 10.02.2000, Bug 72806: dont modify the doc for getting the
/*N*/       //      correct charstyle.
/*N*/       BOOL bResetMod = !pDoc->IsModified();
/*N*/       Link aOle2Lnk;
/*N*/       if( bResetMod )
/*N*/       {
/*N*/           aOle2Lnk = pDoc->GetOle2Link();
/*N*/           ((SwDoc*)pDoc)->SetOle2Link( Link() );
/*N*/       }
/*N*/
/*N*/       pRet = IsPoolUserFmt( nId )
/*N*/               ? ((SwDoc*)pDoc)->FindCharFmtByName( rStr )
/*N*/               : ((SwDoc*)pDoc)->GetCharFmtFromPool( nId );
/*N*/
/*N*/       if( bResetMod )
/*N*/       {
/*N*/           ((SwDoc*)pDoc)->ResetModified();
/*N*/           ((SwDoc*)pDoc)->SetOle2Link( aOle2Lnk );
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if( pRet )
/*N*/       pRet->Add( this );
/*N*/   else if( GetRegisteredIn() )
/*N*/       pRegisteredIn->Remove( this );
/*N*/
/*N*/   return pRet;
/*N*/ }

/*N*/ void SwTxtINetFmt::Modify( SfxPoolItem* pOld, SfxPoolItem* pNew )
/*N*/ {
/*N*/   USHORT nWhich = pOld ? pOld->Which() : pNew ? pNew->Which() : 0;
/*N*/ #ifndef PRODUCT
/*N*/   if ( (nWhich<RES_CHRATR_BEGIN || nWhich>RES_CHRATR_END)
/*N*/           && (nWhich!=RES_OBJECTDYING)
/*N*/           && (nWhich!=RES_ATTRSET_CHG)
/*N*/           && (nWhich!=RES_FMT_CHG) )
/*N*/       ASSERT(!this, "SwTxtCharFmt::Modify(): unbekanntes Modify!");
/*N*/ #endif
/*N*/
/*N*/   if( pMyTxtNd )
/*N*/   {
/*N*/       SwUpdateAttr aUpdateAttr( *GetStart(), *GetEnd(), nWhich );
/*N*/       pMyTxtNd->SwCntntNode::Modify( &aUpdateAttr, &aUpdateAttr );
/*N*/   }
/*N*/ }

    // erfrage vom Modify Informationen
/*N*/ BOOL SwTxtINetFmt::GetInfo( SfxPoolItem& rInfo ) const
/*N*/ {
/*N*/   if( RES_AUTOFMT_DOCNODE != rInfo.Which() || !pMyTxtNd ||
/*N*/       &pMyTxtNd->GetNodes() != ((SwAutoFmtGetDocNode&)rInfo).pNodes )
/*N*/       return TRUE;
/*N*/
/*N*/   ((SwAutoFmtGetDocNode&)rInfo).pCntntNode = pMyTxtNd;
/*N*/   return FALSE;
/*N*/ }

//STRIP001 BOOL SwTxtINetFmt::IsProtect( ) const
//STRIP001 {
//STRIP001  return pMyTxtNd && pMyTxtNd->IsProtect();
//STRIP001 }

// ATT_XNLCONTAINERITEM ******************************

//STRIP001 SwTxtXMLAttrContainer::SwTxtXMLAttrContainer(
//STRIP001                          const SvXMLAttrContainerItem& rAttr,
//STRIP001                          xub_StrLen nStart, xub_StrLen nEnd )
//STRIP001  : SwTxtAttrEnd( rAttr, nStart, nEnd )
//STRIP001 {}



// ******************************

//STRIP001 SwTxtRuby::SwTxtRuby( const SwFmtRuby& rAttr,
//STRIP001                      xub_StrLen nStart, xub_StrLen nEnd )
//STRIP001  : SwTxtAttrEnd( rAttr, nStart, nEnd ),
//STRIP001  SwClient( 0 ),
//STRIP001  pMyTxtNd( 0 )
//STRIP001 {
//STRIP001  ((SwFmtRuby&)rAttr).pTxtAttr  = this;
//STRIP001  SetDontExpand( TRUE );              // never expand this attribut
//STRIP001  SetLockExpandFlag( TRUE );
//STRIP001  SetDontMergeAttr( TRUE );
//STRIP001  SetDontExpandStartAttr( TRUE );
//STRIP001 }

//STRIP001 SwTxtRuby::~SwTxtRuby()
//STRIP001 {
//STRIP001 }

//STRIP001 void SwTxtRuby::Modify( SfxPoolItem *pOld, SfxPoolItem *pNew )
//STRIP001 {
//STRIP001  USHORT nWhich = pOld ? pOld->Which() : pNew ? pNew->Which() : 0;
//STRIP001 #ifndef PRODUCT
//STRIP001  if ( (nWhich<RES_CHRATR_BEGIN || nWhich>RES_CHRATR_END)
//STRIP001          && (nWhich!=RES_OBJECTDYING)
//STRIP001          && (nWhich!=RES_ATTRSET_CHG)
//STRIP001          && (nWhich!=RES_FMT_CHG) )
//STRIP001      ASSERT(!this, "SwTxtCharFmt::Modify(): unbekanntes Modify!");
//STRIP001 #endif
//STRIP001
//STRIP001  if( pMyTxtNd )
//STRIP001  {
//STRIP001      SwUpdateAttr aUpdateAttr( *GetStart(), *GetEnd(), nWhich );
//STRIP001      pMyTxtNd->SwCntntNode::Modify( &aUpdateAttr, &aUpdateAttr );
//STRIP001  }
//STRIP001 }

//STRIP001 BOOL SwTxtRuby::GetInfo( SfxPoolItem& rInfo ) const
//STRIP001 {
//STRIP001  if( RES_AUTOFMT_DOCNODE != rInfo.Which() || !pMyTxtNd ||
//STRIP001      &pMyTxtNd->GetNodes() != ((SwAutoFmtGetDocNode&)rInfo).pNodes )
//STRIP001      return TRUE;
//STRIP001
//STRIP001  ((SwAutoFmtGetDocNode&)rInfo).pCntntNode = pMyTxtNd;
//STRIP001  return FALSE;
//STRIP001 }

//STRIP001 SwCharFmt* SwTxtRuby::GetCharFmt()
//STRIP001 {
//STRIP001  const SwFmtRuby& rFmt = SwTxtAttrEnd::GetRuby();
//STRIP001  SwCharFmt* pRet = 0;
//STRIP001
//STRIP001  if( rFmt.GetText().Len() )
//STRIP001  {
//STRIP001      const SwDoc* pDoc = GetTxtNode().GetDoc();
//STRIP001      const String& rStr = rFmt.GetCharFmtName();
//STRIP001      USHORT nId = rStr.Len() ? rFmt.GetCharFmtId() : RES_POOLCHR_RUBYTEXT;
//STRIP001
//STRIP001      // JP 10.02.2000, Bug 72806: dont modify the doc for getting the
//STRIP001      //              correct charstyle.
//STRIP001      BOOL bResetMod = !pDoc->IsModified();
//STRIP001      Link aOle2Lnk;
//STRIP001      if( bResetMod )
//STRIP001      {
//STRIP001          aOle2Lnk = pDoc->GetOle2Link();
//STRIP001          ((SwDoc*)pDoc)->SetOle2Link( Link() );
//STRIP001      }
//STRIP001
//STRIP001      pRet = IsPoolUserFmt( nId )
//STRIP001              ? ((SwDoc*)pDoc)->FindCharFmtByName( rStr )
//STRIP001              : ((SwDoc*)pDoc)->GetCharFmtFromPool( nId );
//STRIP001
//STRIP001      if( bResetMod )
//STRIP001      {
//STRIP001          ((SwDoc*)pDoc)->ResetModified();
//STRIP001          ((SwDoc*)pDoc)->SetOle2Link( aOle2Lnk );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if( pRet )
//STRIP001      pRet->Add( this );
//STRIP001  else if( GetRegisteredIn() )
//STRIP001      pRegisteredIn->Remove( this );
//STRIP001
//STRIP001  return pRet;
//STRIP001 }

// ******************************

//STRIP001 SwTxt2Lines::SwTxt2Lines( const SvxTwoLinesItem& rAttr,
//STRIP001                      xub_StrLen nStart, xub_StrLen nEnd )
//STRIP001  : SwTxtAttrEnd( rAttr, nStart, nEnd )
//STRIP001 {
//STRIP001 }

}
