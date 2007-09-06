/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_layouter.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 12:20:48 $
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


#ifdef _MSC_VER
#pragma hdrstop
#endif

#include "layouter.hxx"

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#include "doc.hxx"
#include "pagefrm.hxx"
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
/*N*/   delete pLooping;
/*N*/ }





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



/*N*/ BOOL SwLayouter::StartLoopControl( SwDoc* pDoc, SwPageFrm *pPage )
/*N*/ {
/*N*/   ASSERT( pDoc, "No doc, no fun" );
/*N*/   if( !pDoc->GetLayouter() )
/*N*/       pDoc->SetLayouter( new SwLayouter() );
/*N*/   return !pDoc->GetLayouter()->pLooping &&
/*N*/           pDoc->GetLayouter()->StartLooping( pPage );
/*N*/ }


}
