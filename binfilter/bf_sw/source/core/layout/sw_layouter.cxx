/*************************************************************************
 *
 *  $RCSfile: sw_layouter.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 17:37:08 $
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

#include "layouter.hxx"

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#include "doc.hxx"
// auto strip #include "sectfrm.hxx"
// auto strip #include "ftnboss.hxx"
// auto strip #include "cntfrm.hxx"
#include "pagefrm.hxx"
// auto strip #include "ftnfrm.hxx"
namespace binfilter {

/*N*/ #define LOOP_DETECT 250

/*N*/ class SwLooping
/*N*/ {
/*N*/   USHORT nMinPage;
/*N*/   USHORT nMaxPage;
/*N*/   USHORT nCount;
/*N*/ public:
/*N*/   SwLooping( SwPageFrm* pPage );
/*N*/   void Control( SwPageFrm* pPage );
/*N*/   static void Drastic( SwFrm* pFrm );
/*N*/ };

//STRIP001 class SwEndnoter
//STRIP001 {
//STRIP001  SwLayouter* pMaster;
//STRIP001  SwSectionFrm* pSect;
//STRIP001  SvPtrarr* pEndArr;
//STRIP001 public:
//STRIP001  SwEndnoter( SwLayouter* pLay )
//STRIP001      : pMaster( pLay ), pSect( NULL ), pEndArr( NULL ) {}
//STRIP001  ~SwEndnoter() { delete pEndArr; }
//STRIP001  void CollectEndnotes( SwSectionFrm* pSct );
//STRIP001  void CollectEndnote( SwFtnFrm* pFtn );
//STRIP001  void Collect( SwFtnFrm* pFtn );
//STRIP001  const SwSectionFrm* GetSect() { return pSect; }
//STRIP001  void InsertEndnotes();
//STRIP001  BOOL HasEndnotes() const { return pEndArr && pEndArr->Count(); }
//STRIP001 };

//STRIP001 void SwEndnoter::CollectEndnotes( SwSectionFrm* pSct )
//STRIP001 {
//STRIP001  ASSERT( pSct, "CollectEndnotes: Which section?" );
//STRIP001  if( !pSect )
//STRIP001      pSect = pSct;
//STRIP001  else if( pSct != pSect )
//STRIP001      return;
//STRIP001  pSect->CollectEndnotes( pMaster );
//STRIP001 }

//STRIP001 void SwEndnoter::CollectEndnote( SwFtnFrm* pFtn )
//STRIP001 {
//STRIP001  if( pEndArr && USHRT_MAX != pEndArr->GetPos( (VoidPtr)pFtn ) )
//STRIP001      return;
//STRIP001
//STRIP001  if( pFtn->GetUpper() )
//STRIP001  {
//STRIP001      // pFtn is the master, he incorporates its follows
//STRIP001      SwFtnFrm *pNxt = pFtn->GetFollow();
//STRIP001      while ( pNxt )
//STRIP001      {
//STRIP001          SwFrm *pCnt = pNxt->ContainsAny();
//STRIP001          if ( pCnt )
//STRIP001          {
//STRIP001              do
//STRIP001              {   SwFrm *pNxtCnt = pCnt->GetNext();
//STRIP001                  pCnt->Cut();
//STRIP001                  pCnt->Paste( pFtn );
//STRIP001                  pCnt = pNxtCnt;
//STRIP001              } while ( pCnt );
//STRIP001          }
//STRIP001          else
//STRIP001          {   ASSERT( pNxt->Lower() && pNxt->Lower()->IsSctFrm(),
//STRIP001                      "Endnote without content?" );
//STRIP001              pNxt->Cut();
//STRIP001              delete pNxt;
//STRIP001          }
//STRIP001          pNxt = pFtn->GetFollow();
//STRIP001      }
//STRIP001      if( pFtn->GetMaster() )
//STRIP001          return;
//STRIP001      pFtn->Cut();
//STRIP001  }
//STRIP001  else if( pEndArr )
//STRIP001  {
//STRIP001      for ( USHORT i = 0; i < pEndArr->Count(); ++i )
//STRIP001      {
//STRIP001          SwFtnFrm *pEndFtn = (SwFtnFrm*)((*pEndArr)[i]);
//STRIP001          if( pEndFtn->GetAttr() == pFtn->GetAttr() )
//STRIP001          {
//STRIP001              delete pFtn;
//STRIP001              return;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  if( !pEndArr )
//STRIP001      pEndArr = new SvPtrarr( 5, 5 );  // deleted from the SwLayouter
//STRIP001  pEndArr->Insert( (VoidPtr)pFtn, pEndArr->Count() );
//STRIP001 }

//STRIP001 void SwEndnoter::Collect( SwFtnFrm* pFtn )
//STRIP001 {
//STRIP001 }

//STRIP001 void SwEndnoter::InsertEndnotes()
//STRIP001 {
//STRIP001  if( !pSect )
//STRIP001      return;
//STRIP001  if( !pEndArr || !pEndArr->Count() )
//STRIP001  {
//STRIP001      pSect = NULL;
//STRIP001      return;
//STRIP001  }
//STRIP001  ASSERT( pSect->Lower() && pSect->Lower()->IsFtnBossFrm(),
//STRIP001          "InsertEndnotes: Where's my column?" );
//STRIP001  SwFrm* pRef = pSect->FindLastCntnt( FINDMODE_MYLAST );
//STRIP001  SwFtnBossFrm *pBoss = pRef ? pRef->FindFtnBossFrm()
//STRIP001                             : (SwFtnBossFrm*)pSect->Lower();
//STRIP001  pBoss->_MoveFtns( *pEndArr );
//STRIP001  delete pEndArr;
//STRIP001  pEndArr = NULL;
//STRIP001  pSect = NULL;
//STRIP001 }

/*N*/ SwLooping::SwLooping( SwPageFrm* pPage )
/*N*/ {
/*N*/   ASSERT( pPage, "Where's my page?" );
/*N*/   nMinPage = pPage->GetPhyPageNum();
/*N*/   nMaxPage = nMinPage;
/*N*/   nCount = 0;
/*N*/ }

/*N*/ void SwLooping::Drastic( SwFrm* pFrm )
/*N*/ {
/*N*/   while( pFrm )
/*N*/   {
/*N*/       if( pFrm->IsLayoutFrm() )
/*N*/           Drastic( ((SwLayoutFrm*)pFrm)->Lower() );
/*N*/       pFrm->bValidPos = TRUE;
/*N*/       pFrm->bValidSize = TRUE;
/*N*/       pFrm->bValidPrtArea = TRUE;
/*N*/       pFrm = pFrm->GetNext();
/*N*/   }
/*N*/ }

/*N*/ void SwLooping::Control( SwPageFrm* pPage )
/*N*/ {
/*N*/   if( !pPage )
/*N*/       return;
/*N*/   USHORT nNew = pPage->GetPhyPageNum();
/*N*/   if( nNew > nMaxPage )
/*N*/       nMaxPage = nNew;
/*N*/   if( nNew < nMinPage )
/*N*/   {
/*N*/       nMinPage = nNew;
/*N*/       nMaxPage = nNew;
/*N*/       nCount = 0;
/*N*/   }
/*N*/   else if( nNew > nMinPage + 2 )
/*N*/   {
/*N*/       nMinPage = nNew - 2;
/*N*/       nMaxPage = nNew;
/*N*/       nCount = 0;
/*N*/   }
/*N*/   else if( ++nCount > LOOP_DETECT )
/*N*/   {
/*N*/ #ifndef PRODUCT
/*N*/ #if OSL_DEBUG_LEVEL > 1
/*N*/       static BOOL bNoLouie = FALSE;
/*N*/       if( bNoLouie )
/*N*/           return;
/*N*/ #endif
/*N*/ #endif
/*N*/       ASSERT( FALSE, "Looping Louie" );
/*N*/       nCount = 0;
/*N*/       Drastic( pPage->Lower() );
/*N*/       if( nNew > nMinPage && pPage->GetPrev() )
/*N*/           Drastic( ((SwPageFrm*)pPage->GetPrev())->Lower() );
/*N*/       if( nNew < nMaxPage && pPage->GetNext() )
/*N*/           Drastic( ((SwPageFrm*)pPage->GetNext())->Lower() );
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|*  SwLayouter::SwLayouter()
|*
|*  Ersterstellung      AMA 02. Nov. 99
|*  Letzte Aenderung    AMA 02. Nov. 99
|*
|*************************************************************************/

/*N*/ SwLayouter::SwLayouter() : pLooping( NULL ) //STRIP001 pEndnoter( NULL ), pLooping( NULL )
/*N*/ {
/*N*/ }

/*N*/ SwLayouter::~SwLayouter()
/*N*/ {
//STRIP001 /*N*/    delete pEndnoter;
/*N*/   delete pLooping;
/*N*/ }

//STRIP001 void SwLayouter::_CollectEndnotes( SwSectionFrm* pSect )
//STRIP001 {
//STRIP001  if( !pEndnoter )
//STRIP001      pEndnoter = new SwEndnoter( this );
//STRIP001  pEndnoter->CollectEndnotes( pSect );
//STRIP001 }

//STRIP001 BOOL SwLayouter::HasEndnotes() const
//STRIP001 {
//STRIP001  return pEndnoter->HasEndnotes();
//STRIP001 }

//STRIP001 void SwLayouter::CollectEndnote( SwFtnFrm* pFtn )
//STRIP001 {
//STRIP001  pEndnoter->CollectEndnote( pFtn );
//STRIP001 }

//STRIP001 void SwLayouter::InsertEndnotes( SwSectionFrm* pSect )
//STRIP001 {
//STRIP001  if( !pEndnoter || pEndnoter->GetSect() != pSect )
//STRIP001      return;
//STRIP001  pEndnoter->InsertEndnotes();
//STRIP001 }

/*N*/ void SwLayouter::LoopControl( SwPageFrm* pPage, BYTE nLoop )
/*N*/ {
/*N*/   ASSERT( pLooping, "Looping: Lost control" );
/*N*/   pLooping->Control( pPage );
/*N*/ }

/*N*/ BOOL SwLayouter::StartLooping( SwPageFrm* pPage )
/*N*/ {
/*N*/   if( pLooping )
/*?*/       return FALSE;
/*N*/   pLooping = new SwLooping( pPage );
/*N*/   return TRUE;
/*N*/ }

/*N*/ void SwLayouter::EndLoopControl()
/*N*/ {
/*N*/   delete pLooping;
/*N*/   pLooping = NULL;
/*N*/ }

//STRIP001 void SwLayouter::CollectEndnotes( SwDoc* pDoc, SwSectionFrm* pSect )
//STRIP001 {
//STRIP001  ASSERT( pDoc, "No doc, no fun" );
//STRIP001  if( !pDoc->GetLayouter() )
//STRIP001      pDoc->SetLayouter( new SwLayouter() );
//STRIP001  pDoc->GetLayouter()->_CollectEndnotes( pSect );
//STRIP001 }

//STRIP001 BOOL SwLayouter::Collecting( SwDoc* pDoc, SwSectionFrm* pSect, SwFtnFrm* pFtn )
//STRIP001 {
//STRIP001  if( !pDoc->GetLayouter() )
//STRIP001      return FALSE;
//STRIP001  SwLayouter *pLayouter = pDoc->GetLayouter();
//STRIP001  if( pLayouter->pEndnoter && pLayouter->pEndnoter->GetSect() && pSect &&
//STRIP001      ( pLayouter->pEndnoter->GetSect()->IsAnFollow( pSect ) ||
//STRIP001        pSect->IsAnFollow( pLayouter->pEndnoter->GetSect() ) ) )
//STRIP001  {
//STRIP001      if( pFtn )
//STRIP001          pLayouter->CollectEndnote( pFtn );
//STRIP001      return TRUE;
//STRIP001  }
//STRIP001  return FALSE;
//STRIP001 }

/*N*/ BOOL SwLayouter::StartLoopControl( SwDoc* pDoc, SwPageFrm *pPage )
/*N*/ {
/*N*/   ASSERT( pDoc, "No doc, no fun" );
/*N*/   if( !pDoc->GetLayouter() )
/*N*/       pDoc->SetLayouter( new SwLayouter() );
/*N*/   return !pDoc->GetLayouter()->pLooping &&
/*N*/           pDoc->GetLayouter()->StartLooping( pPage );
/*N*/ }


}
