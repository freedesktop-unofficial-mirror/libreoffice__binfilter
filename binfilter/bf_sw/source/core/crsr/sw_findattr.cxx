/*************************************************************************
 *
 *  $RCSfile: sw_findattr.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:40:48 $
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

#ifndef _COM_SUN_STAR_LANG_LOCALE_HPP_
#include <com/sun/star/lang/Locale.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_SEARCHOPTIONS_HPP_
#include <com/sun/star/util/SearchOptions.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_SEARCHFLAGS_HPP_
#include <com/sun/star/util/SearchFlags.hpp>
#endif

#ifndef _ISOLANG_HXX
#include <tools/isolang.hxx>
#endif

#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif

#ifndef _SV_SVAPP_HXX //autogen wg. Application
#include <vcl/svapp.hxx>
#endif
#ifndef _SFXITEMITER_HXX //autogen
#include <svtools/itemiter.hxx>
#endif
#ifndef _SFX_WHITER_HXX //autogen
#include <svtools/whiter.hxx>
#endif

#ifndef _SVX_BRKITEM_HXX //autogen
#include <bf_svx/brkitem.hxx>
#endif
#ifndef _SVX_COLRITEM_HXX //autogen
#include <bf_svx/colritem.hxx>
#endif
#ifndef _SVX_FONTITEM_HXX //autogen
#include <bf_svx/fontitem.hxx>
#endif
#ifndef _FMTPDSC_HXX //autogen
#include <fmtpdsc.hxx>
#endif
#ifndef _TXATBASE_HXX //autogen
#include <txatbase.hxx>
#endif
#ifndef _FCHRFMT_HXX //autogen
#include <fchrfmt.hxx>
#endif
#ifndef _CHARFMT_HXX //autogen
#include <charfmt.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _SWCRSR_HXX
#include <swcrsr.hxx>
#endif
#ifndef _EDITSH_HXX
#include <editsh.hxx>
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>
#endif
#ifndef _PAMTYP_HXX
#include <pamtyp.hxx>
#endif
#ifndef _SWUNDO_HXX
#include <swundo.hxx>
#endif
#ifndef _CRSSKIP_HXX
#include <crsskip.hxx>
#endif
#ifndef _UNDOBJ_HXX
#include <undobj.hxx>
#endif
namespace binfilter {

using namespace ::com::sun::star;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::util;

//STRIP001 SV_DECL_PTRARR_SORT( SwpFmts, SwFmt*, 0, 4 )
//STRIP001 SV_IMPL_PTRARR_SORT( SwpFmts, SwFmt* )

    // Sonderbehandlung fuer SvxFontItem, nur den Namen vergleichen:
//STRIP001 int CmpAttr( const SfxPoolItem& rItem1, const SfxPoolItem& rItem2 )
//STRIP001 {
//STRIP001  switch( rItem1.Which() )
//STRIP001  {
//STRIP001  case RES_CHRATR_FONT:
//STRIP001      return ((SvxFontItem&)rItem1).GetFamilyName() ==
//STRIP001              ((SvxFontItem&)rItem2).GetFamilyName();
//STRIP001
//STRIP001  case RES_CHRATR_COLOR:
//STRIP001      return ((SvxColorItem&)rItem1).GetValue().IsRGBEqual(
//STRIP001                              ((SvxColorItem&)rItem2).GetValue() );
//STRIP001  case RES_PAGEDESC:
//STRIP001      return ((SwFmtPageDesc&)rItem1).GetNumOffset() ==
//STRIP001                      ((SwFmtPageDesc&)rItem2).GetNumOffset() &&
//STRIP001              ((SwFmtPageDesc&)rItem1).GetPageDesc() ==
//STRIP001                      ((SwFmtPageDesc&)rItem2).GetPageDesc();
//STRIP001  }
//STRIP001  return rItem1 == rItem2;
//STRIP001 }


/*N*/ const SwTxtAttr* GetFrwrdTxtHint( const SwpHints& rHtsArr, USHORT& rPos,
/*N*/                                   xub_StrLen nCntntPos )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  while( rPos < rHtsArr.Count() )
//STRIP001  {
//STRIP001      const SwTxtAttr *pTxtHt = rHtsArr.GetStart( rPos++ );
//STRIP001      // der Start vom Attribut muss innerhalb des Bereiches liegen !!
//STRIP001      if( *pTxtHt->GetStart() >= nCntntPos )
//STRIP001          return pTxtHt;      // gueltiges TextAttribut
//STRIP001  }
/*N*/   return 0;                   // kein gueltiges TextAttribut
/*N*/ }


/*N*/ const SwTxtAttr* GetBkwrdTxtHint( const SwpHints& rHtsArr, USHORT& rPos,
/*N*/                                 xub_StrLen nCntntPos )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  while( rPos > 0 )
//STRIP001  {
//STRIP001      //Hack mit cast fuer das Update
//STRIP001      const SwTxtAttr *pTxtHt = rHtsArr.GetStart( --rPos );
//STRIP001      // der Start vom Attribut muss innerhalb des Bereiches liegen !!
//STRIP001      if( *pTxtHt->GetStart() < nCntntPos )
//STRIP001          return pTxtHt;      // gueltiges TextAttribut
//STRIP001  }
/*N*/   return 0;                   // kein gueltiges TextAttribut
/*N*/ }


//STRIP001 void lcl_SetAttrPam( SwPaM & rPam, xub_StrLen nStart, const xub_StrLen* pEnde,
//STRIP001                      const BOOL bSaveMark )
//STRIP001 {
//STRIP001  xub_StrLen nCntntPos;
//STRIP001  if( bSaveMark )
//STRIP001      nCntntPos = rPam.GetMark()->nContent.GetIndex();
//STRIP001  else
//STRIP001      nCntntPos = rPam.GetPoint()->nContent.GetIndex();
//STRIP001  FASTBOOL bTstEnde = rPam.GetPoint()->nNode == rPam.GetMark()->nNode;
//STRIP001
//STRIP001  SwCntntNode* pCNd = rPam.GetCntntNode();
//STRIP001  rPam.GetPoint()->nContent.Assign( pCNd, nStart );
//STRIP001  rPam.SetMark();     // Point == GetMark
//STRIP001
//STRIP001  // Point zeigt auf das Ende vom SuchBereich oder Ende vom Attribut
//STRIP001  if( pEnde )
//STRIP001  {
//STRIP001      if( bTstEnde && *pEnde > nCntntPos )
//STRIP001          rPam.GetPoint()->nContent = nCntntPos;
//STRIP001      else
//STRIP001          rPam.GetPoint()->nContent = *pEnde;
//STRIP001  }
//STRIP001 }

//------------------ Suche nach einem Text Attribut -----------------------

// diese Funktion sucht in einem TextNode nach dem vorgegebenen Attribut.
// Wird es gefunden, dann hat der SwPaM den Bereich der das Attribut
// umspannt, unter Beachtung des Suchbereiches


//STRIP001 FASTBOOL lcl_Search( const SwTxtNode& rTxtNd, SwPaM& rPam,
//STRIP001                  const SfxPoolItem& rCmpItem,
//STRIP001                  SwMoveFn fnMove, BOOL bValue )
//STRIP001 {
//STRIP001  if ( !rTxtNd.HasHints() )
//STRIP001      return FALSE;
//STRIP001  const SwTxtAttr *pTxtHt = 0;
//STRIP001  FASTBOOL bForward = fnMove == fnMoveForward;
//STRIP001  USHORT nPos = bForward ? 0 : rTxtNd.GetSwpHints().Count();
//STRIP001  xub_StrLen nCntntPos = rPam.GetPoint()->nContent.GetIndex();
//STRIP001
//STRIP001  while( 0 != ( pTxtHt=(*fnMove->fnGetHint)(rTxtNd.GetSwpHints(),nPos,nCntntPos)))
//STRIP001      if( pTxtHt->Which() == rCmpItem.Which() &&
//STRIP001          ( !bValue || CmpAttr( pTxtHt->GetAttr(), rCmpItem )))
//STRIP001      {
//STRIP001          lcl_SetAttrPam( rPam, *pTxtHt->GetStart(), pTxtHt->GetEnd(), bForward );
//STRIP001          return TRUE;
//STRIP001      }
//STRIP001  return FALSE;
//STRIP001 }


//------------------ Suche nach mehren Text Attributen -------------------

//STRIP001 struct _SwSrchChrAttr
//STRIP001 {
//STRIP001  USHORT nWhich;
//STRIP001  xub_StrLen nStt, nEnd;
//STRIP001
//STRIP001  _SwSrchChrAttr( const SfxPoolItem& rItem,
//STRIP001                  xub_StrLen nStart, xub_StrLen nAnyEnd )
//STRIP001      : nWhich( rItem.Which() ), nStt( nStart ), nEnd( nAnyEnd )
//STRIP001  {}
//STRIP001 };

//STRIP001 class SwAttrCheckArr
//STRIP001 {
//STRIP001  _SwSrchChrAttr *pFndArr, *pStackArr;
//STRIP001  xub_StrLen nNdStt, nNdEnd;
//STRIP001  USHORT nArrStart, nArrLen;
//STRIP001  USHORT nFound, nStackCnt;
//STRIP001  SfxItemSet aCmpSet;
//STRIP001  BOOL bNoColls;
//STRIP001  BOOL bForward;
//STRIP001
//STRIP001 public:
//STRIP001  SwAttrCheckArr( const SfxItemSet& rSet, int bForward, int bNoCollections );
//STRIP001  ~SwAttrCheckArr();
//STRIP001
//STRIP001  void SetNewSet( const SwTxtNode& rTxtNd, const SwPaM& rPam );
//STRIP001
//STRIP001  // wieviele Attribute ueberhaupt ??
//STRIP001  USHORT Count() const    { return aCmpSet.Count(); }
//STRIP001  int Found() const       { return nFound == aCmpSet.Count(); }
//STRIP001  int CheckStack();
//STRIP001
//STRIP001  xub_StrLen Start() const;
//STRIP001  xub_StrLen End() const;
//STRIP001
//STRIP001  xub_StrLen GetNdStt() const { return nNdStt; }
//STRIP001  xub_StrLen GetNdEnd() const { return nNdEnd; }
//STRIP001
//STRIP001  int SetAttrFwd( const SwTxtAttr& rAttr );
//STRIP001  int SetAttrBwd( const SwTxtAttr& rAttr );
//STRIP001 };



//STRIP001 SwAttrCheckArr::SwAttrCheckArr( const SfxItemSet& rSet, int bFwd,
//STRIP001                              int bNoCollections )
//STRIP001  : aCmpSet( *rSet.GetPool(), RES_CHRATR_BEGIN, RES_TXTATR_END-1 )
//STRIP001 {
//STRIP001  aCmpSet.Put( rSet, FALSE );
//STRIP001  bNoColls = bNoCollections;
//STRIP001
//STRIP001  bForward = bFwd;
//STRIP001
//STRIP001  // Bestimmen den Bereich des Fnd/Stack-Arrays (Min/Max)
//STRIP001  SfxItemIter aIter( aCmpSet );
//STRIP001  nArrStart = aCmpSet.GetWhichByPos( aIter.GetFirstPos() );
//STRIP001  nArrLen = aCmpSet.GetWhichByPos( aIter.GetLastPos() ) - nArrStart+1;
//STRIP001
//STRIP001  pFndArr = (_SwSrchChrAttr*)new char[ nArrLen * sizeof(_SwSrchChrAttr) ];
//STRIP001  pStackArr = (_SwSrchChrAttr*)new char[ nArrLen * sizeof(_SwSrchChrAttr) ];
//STRIP001 }


//STRIP001 SwAttrCheckArr::~SwAttrCheckArr()
//STRIP001 {
//STRIP001     delete[] (void*) pFndArr;
//STRIP001     delete[] (void*) pStackArr;
//STRIP001 }



//STRIP001 #pragma optimize( "e", off )

//STRIP001 void SwAttrCheckArr::SetNewSet( const SwTxtNode& rTxtNd, const SwPaM& rPam )
//STRIP001 {
//STRIP001  memset( pFndArr, 0, nArrLen * sizeof(_SwSrchChrAttr) );
//STRIP001  memset( pStackArr, 0, nArrLen * sizeof(_SwSrchChrAttr) );
//STRIP001  nFound = 0;
//STRIP001  nStackCnt = 0;
//STRIP001
//STRIP001  if( bForward )
//STRIP001  {
//STRIP001      nNdStt = rPam.GetPoint()->nContent.GetIndex();
//STRIP001      nNdEnd = rPam.GetPoint()->nNode == rPam.GetMark()->nNode
//STRIP001              ? rPam.GetMark()->nContent.GetIndex()
//STRIP001              : rTxtNd.GetTxt().Len();
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      nNdEnd = rPam.GetPoint()->nContent.GetIndex();
//STRIP001      nNdStt = rPam.GetPoint()->nNode == rPam.GetMark()->nNode
//STRIP001              ? rPam.GetMark()->nContent.GetIndex()
//STRIP001              : 0;
//STRIP001  }
//STRIP001
//STRIP001  if( bNoColls && !rTxtNd.GetpSwAttrSet() )
//STRIP001      return ;
//STRIP001
//STRIP001  const SfxItemSet& rSet = rTxtNd.GetSwAttrSet();
//STRIP001 //   if( !rSet.Count() )
//STRIP001 //       return;
//STRIP001
//STRIP001  SfxItemIter aIter( aCmpSet );
//STRIP001  const SfxPoolItem* pItem = aIter.GetCurItem();
//STRIP001  const SfxPoolItem* pFndItem;
//STRIP001  USHORT nWhich;
//STRIP001
//STRIP001  while( TRUE )
//STRIP001  {
//STRIP001      // nur testen, ob vorhanden ist ?
//STRIP001      if( IsInvalidItem( pItem ) )
//STRIP001      {
//STRIP001          nWhich = aCmpSet.GetWhichByPos( aIter.GetCurPos() );
//STRIP001          if( RES_TXTATR_END <= nWhich )
//STRIP001              break;              // Ende der TextAttribute
//STRIP001
//STRIP001          if( SFX_ITEM_SET == rSet.GetItemState( nWhich, !bNoColls, &pFndItem )
//STRIP001              && !CmpAttr( *pFndItem, rSet.GetPool()->GetDefaultItem( nWhich ) ))
//STRIP001          {
//STRIP001              pFndArr[ nWhich - nArrStart ] =
//STRIP001                  _SwSrchChrAttr( *pFndItem, nNdStt, nNdEnd );
//STRIP001              nFound++;
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          if( RES_TXTATR_END <= (nWhich = pItem->Which() ))
//STRIP001              break;              // Ende der TextAttribute
//STRIP001
//STRIP001 //JP 27.02.95: wenn nach defaults gesucht wird, dann muss man bis zum Pool
//STRIP001 //               runter
//STRIP001 //           if( SFX_ITEM_SET == rSet.GetItemState( nWhich, !bNoColls, &pFndItem )
//STRIP001 //                && *pFndItem == *pItem )
//STRIP001          if( CmpAttr( rSet.Get( nWhich, !bNoColls ), *pItem ) )
//STRIP001          {
//STRIP001              pFndArr[ nWhich - nArrStart ] =
//STRIP001                  _SwSrchChrAttr( *pItem, nNdStt, nNdEnd );
//STRIP001              nFound++;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      if( aIter.IsAtEnd() )
//STRIP001          break;
//STRIP001      pItem = aIter.NextItem();
//STRIP001  }
//STRIP001 }
//STRIP001 #pragma optimize( "", on )


//STRIP001 int SwAttrCheckArr::SetAttrFwd( const SwTxtAttr& rAttr )
//STRIP001 {
//STRIP001  _SwSrchChrAttr aTmp( rAttr.GetAttr(), *rAttr.GetStart(), *rAttr.GetAnyEnd() );
//STRIP001  // alle die nicht im Bereich sind -> ignorieren
//STRIP001  if( aTmp.nEnd <= nNdStt || aTmp.nStt >= nNdEnd )
//STRIP001      return Found();
//STRIP001
//STRIP001  const SfxPoolItem* pItem;
//STRIP001
//STRIP001 // --------------------------------------------------------------
//STRIP001 // Hier wird jetzt ausdruecklich auch in Zeichenvorlagen gesucht
//STRIP001 // --------------------------------------------------------------
//STRIP001  USHORT nWhch = rAttr.Which();
//STRIP001  SfxWhichIter* pIter = NULL;
//STRIP001  const SfxPoolItem* pTmpItem;
//STRIP001  const SwAttrSet* pSet;
//STRIP001  if( RES_TXTATR_CHARFMT == nWhch )
//STRIP001  {
//STRIP001      if( bNoColls )
//STRIP001          return Found();
//STRIP001      SwCharFmt* pFmt = rAttr.GetCharFmt().GetCharFmt();
//STRIP001      if( pFmt )
//STRIP001      {
//STRIP001          pSet = &pFmt->GetAttrSet();
//STRIP001          pIter = new SfxWhichIter( *pSet );
//STRIP001          nWhch = pIter->FirstWhich();
//STRIP001          while( nWhch &&
//STRIP001              SFX_ITEM_SET != pSet->GetItemState( nWhch, TRUE, &pTmpItem ) )
//STRIP001              nWhch = pIter->NextWhich();
//STRIP001          if( !nWhch )
//STRIP001              pTmpItem = NULL;
//STRIP001      }
//STRIP001      else
//STRIP001          pTmpItem = NULL;
//STRIP001  }
//STRIP001  else
//STRIP001      pTmpItem = &rAttr.GetAttr();
//STRIP001  while( pTmpItem )
//STRIP001  {
//STRIP001      SfxItemState eState = aCmpSet.GetItemState( nWhch, FALSE, &pItem );
//STRIP001      if( SFX_ITEM_DONTCARE == eState || SFX_ITEM_SET == eState )
//STRIP001      {
//STRIP001          register USHORT n;
//STRIP001          _SwSrchChrAttr* pCmp;
//STRIP001
//STRIP001          // loesche erstmal alle, die bis zu der Start Position schon wieder
//STRIP001          // ungueltig sind:
//STRIP001
//STRIP001          _SwSrchChrAttr* pArrPtr;
//STRIP001          if( nFound )
//STRIP001              for( pArrPtr = pFndArr, n = 0; n < nArrLen;
//STRIP001                  ++n, ++pArrPtr )
//STRIP001                  if( pArrPtr->nWhich && pArrPtr->nEnd <= aTmp.nStt )
//STRIP001                  {
//STRIP001                      pArrPtr->nWhich = 0;        // geloescht
//STRIP001                      nFound--;
//STRIP001                  }
//STRIP001
//STRIP001          // loesche erstmal alle, die bis zu der Start Position schon wieder
//STRIP001          // ungueltig sind. Und verschiebe alle die "offen" sind, heisst ueber
//STRIP001          // die Start Position ragen, vom Stack in den FndSet
//STRIP001
//STRIP001          if( nStackCnt )
//STRIP001              for( pArrPtr = pStackArr, n=0; n < nArrLen; ++n, ++pArrPtr )
//STRIP001              {
//STRIP001                  if( !pArrPtr->nWhich )
//STRIP001                      continue;
//STRIP001
//STRIP001                  if( pArrPtr->nEnd <= aTmp.nStt )
//STRIP001                  {
//STRIP001                      pArrPtr->nWhich = 0;        // geloescht
//STRIP001                      if( !--nStackCnt )
//STRIP001                          break;
//STRIP001                  }
//STRIP001                  else if( pArrPtr->nStt <= aTmp.nStt )
//STRIP001                  {
//STRIP001                      if( ( pCmp = &pFndArr[ n ])->nWhich )
//STRIP001                      {
//STRIP001                          if( pCmp->nEnd < pArrPtr->nEnd )        // erweitern
//STRIP001                              pCmp->nEnd = pArrPtr->nEnd;
//STRIP001                      }
//STRIP001                      else
//STRIP001                      {
//STRIP001                          *pCmp = *pArrPtr;
//STRIP001                          nFound++;
//STRIP001                      }
//STRIP001                      pArrPtr->nWhich = 0;
//STRIP001                      if( !--nStackCnt )
//STRIP001                          break;
//STRIP001                  }
//STRIP001              }
//STRIP001
//STRIP001          BOOL bContinue = FALSE;
//STRIP001
//STRIP001          if( SFX_ITEM_DONTCARE == eState  )
//STRIP001          {
//STRIP001              // wird Attribut gueltig ?
//STRIP001              if( !CmpAttr( aCmpSet.GetPool()->GetDefaultItem( nWhch ),
//STRIP001                  *pTmpItem ))
//STRIP001              {
//STRIP001                  // suche das Attribut und erweiter es gegebenenfalls
//STRIP001                  if( !( pCmp = &pFndArr[ nWhch - nArrStart ])->nWhich )
//STRIP001                  {
//STRIP001                      *pCmp = aTmp;               // nicht gefunden, eintragen
//STRIP001                      nFound++;
//STRIP001                  }
//STRIP001                  else if( pCmp->nEnd < aTmp.nEnd )       // erweitern ?
//STRIP001                      pCmp->nEnd = aTmp.nEnd;
//STRIP001
//STRIP001                  bContinue = TRUE;
//STRIP001              }
//STRIP001          }
//STRIP001          // wird Attribut gueltig ?
//STRIP001          else if(  CmpAttr( *pItem, *pTmpItem ) )
//STRIP001          {
//STRIP001              pFndArr[ nWhch - nArrStart ] = aTmp;
//STRIP001              ++nFound;
//STRIP001              bContinue = TRUE;
//STRIP001          }
//STRIP001
//STRIP001          // tja, dann muss es auf den Stack
//STRIP001          if( !bContinue && ( pCmp = &pFndArr[ nWhch - nArrStart ])->nWhich )
//STRIP001          {
//STRIP001              // vorhanden, auf den Stack. Aber nur wenn es noch grosser ist
//STRIP001              if( pCmp->nEnd > aTmp.nEnd )
//STRIP001              {
//STRIP001                  ASSERT( !pStackArr[ nWhch - nArrStart ].nWhich,
//STRIP001                                  "Stack-Platz ist noch belegt" );
//STRIP001
//STRIP001      // ---------
//STRIP001      // JP 22.08.96: nur Ende manipulieren reicht nicht. Bug 30547
//STRIP001      //          pCmp->nStt = aTmp.nEnd;
//STRIP001                  if( aTmp.nStt <= pCmp->nStt )
//STRIP001                      pCmp->nStt = aTmp.nEnd;
//STRIP001                  else
//STRIP001                      pCmp->nEnd = aTmp.nStt;
//STRIP001      // ---------
//STRIP001
//STRIP001                  pStackArr[ nWhch - nArrStart ] = *pCmp;
//STRIP001                  nStackCnt++;
//STRIP001              }
//STRIP001              pCmp->nWhich = 0;
//STRIP001              nFound--;
//STRIP001          }
//STRIP001      }
//STRIP001      if( pIter )
//STRIP001      {
//STRIP001          nWhch = pIter->NextWhich();
//STRIP001          while( nWhch &&
//STRIP001              SFX_ITEM_SET != pSet->GetItemState( nWhch, TRUE, &pTmpItem ) )
//STRIP001              nWhch = pIter->NextWhich();
//STRIP001          if( !nWhch )
//STRIP001              break;
//STRIP001      }
//STRIP001      else
//STRIP001          break;
//STRIP001  }
//STRIP001 // --------------------------------------------------------------
//STRIP001 #ifdef USED
//STRIP001  {
//STRIP001      SfxItemState eState = aCmpSet.GetItemState( rAttr.Which(), FALSE, &pItem );
//STRIP001      if( SFX_ITEM_DONTCARE != eState && SFX_ITEM_SET != eState )
//STRIP001          return Found();
//STRIP001
//STRIP001      register USHORT n, nWhich = rAttr.Which();
//STRIP001      _SwSrchChrAttr* pCmp;
//STRIP001
//STRIP001      // loesche erstmal alle, die bis zu der Start Position schon wieder
//STRIP001      // ungueltig sind:
//STRIP001
//STRIP001      _SwSrchChrAttr* pArrPtr;
//STRIP001      if( nFound )
//STRIP001          for( pArrPtr = pFndArr, n = 0; n < nArrLen;
//STRIP001              ++n, ++pArrPtr )
//STRIP001              if( pArrPtr->nWhich && pArrPtr->nEnd <= aTmp.nStt )
//STRIP001              {
//STRIP001                  pArrPtr->nWhich = 0;        // geloescht
//STRIP001                  nFound--;
//STRIP001              }
//STRIP001
//STRIP001      // loesche erstmal alle, die bis zu der Start Position schon wieder
//STRIP001      // ungueltig sind. Und verschiebe alle die "offen" sind, heisst ueber
//STRIP001      // die Start Position ragen, vom Stack in den FndSet
//STRIP001
//STRIP001      if( nStackCnt )
//STRIP001          for( pArrPtr = pStackArr, n=0; n < nArrLen; ++n, ++pArrPtr )
//STRIP001          {
//STRIP001              if( !pArrPtr->nWhich )
//STRIP001                  continue;
//STRIP001
//STRIP001              if( pArrPtr->nEnd <= aTmp.nStt )
//STRIP001              {
//STRIP001                  pArrPtr->nWhich = 0;        // geloescht
//STRIP001                  if( !--nStackCnt )
//STRIP001                      break;
//STRIP001              }
//STRIP001              else if( pArrPtr->nStt <= aTmp.nStt )
//STRIP001              {
//STRIP001                  if( ( pCmp = &pFndArr[ n ])->nWhich )
//STRIP001                  {
//STRIP001                      if( pCmp->nEnd < pArrPtr->nEnd )        // erweitern
//STRIP001                          pCmp->nEnd = pArrPtr->nEnd;
//STRIP001                  }
//STRIP001                  else
//STRIP001                  {
//STRIP001                      *pCmp = *pArrPtr;
//STRIP001                      nFound++;
//STRIP001                  }
//STRIP001                  pArrPtr->nWhich = 0;
//STRIP001                  if( !--nStackCnt )
//STRIP001                      break;
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001
//STRIP001      if( SFX_ITEM_DONTCARE == eState  )
//STRIP001      {
//STRIP001          // wird Attribut gueltig ?
//STRIP001          if( !CmpAttr( aCmpSet.GetPool()->GetDefaultItem( nWhich ),
//STRIP001              rAttr.GetAttr() ))
//STRIP001          {
//STRIP001              // suche das Attribut und erweiter es gegebenenfalls
//STRIP001              if( !( pCmp = &pFndArr[ nWhich - nArrStart ])->nWhich )
//STRIP001              {
//STRIP001                  *pCmp = aTmp;               // nicht gefunden, eintragen
//STRIP001                  nFound++;
//STRIP001              }
//STRIP001              else if( pCmp->nEnd < aTmp.nEnd )       // erweitern ?
//STRIP001                  pCmp->nEnd = aTmp.nEnd;
//STRIP001
//STRIP001              return Found();
//STRIP001          }
//STRIP001      }
//STRIP001      // wird Attribut gueltig ?
//STRIP001      else if(  CmpAttr( *pItem, rAttr.GetAttr() ) )
//STRIP001      {
//STRIP001          pFndArr[ nWhich - nArrStart ] = aTmp;
//STRIP001          return ++nFound == aCmpSet.Count();
//STRIP001      }
//STRIP001
//STRIP001      // tja, dann muss es auf den Stack
//STRIP001      if( ( pCmp = &pFndArr[ nWhich - nArrStart ])->nWhich )
//STRIP001      {
//STRIP001          // vorhanden, auf den Stack. Aber nur wenn es noch grosser ist
//STRIP001          if( pCmp->nEnd > aTmp.nEnd )
//STRIP001          {
//STRIP001              ASSERT( !pStackArr[ nWhich - nArrStart ].nWhich,
//STRIP001                              "Stack-Platz ist noch belegt" );
//STRIP001
//STRIP001  // ---------
//STRIP001  // JP 22.08.96: nur Ende manipulieren reicht nicht. Bug 30547
//STRIP001  //          pCmp->nStt = aTmp.nEnd;
//STRIP001              if( aTmp.nStt <= pCmp->nStt )
//STRIP001                  pCmp->nStt = aTmp.nEnd;
//STRIP001              else
//STRIP001                  pCmp->nEnd = aTmp.nStt;
//STRIP001  // ---------
//STRIP001
//STRIP001              pStackArr[ nWhich - nArrStart ] = *pCmp;
//STRIP001              nStackCnt++;
//STRIP001          }
//STRIP001          pCmp->nWhich = 0;
//STRIP001          nFound--;
//STRIP001      }
//STRIP001  }
//STRIP001 #endif
//STRIP001  return Found();
//STRIP001 }


//STRIP001 int SwAttrCheckArr::SetAttrBwd( const SwTxtAttr& rAttr )
//STRIP001 {
//STRIP001  _SwSrchChrAttr aTmp( rAttr.GetAttr(), *rAttr.GetStart(), *rAttr.GetAnyEnd() );
//STRIP001  // alle die nicht im Bereich sind -> ignorieren
//STRIP001  if( aTmp.nEnd < nNdStt || aTmp.nStt >= nNdEnd )
//STRIP001      return Found();
//STRIP001
//STRIP001  const SfxPoolItem* pItem;
//STRIP001 // --------------------------------------------------------------
//STRIP001 // Hier wird jetzt ausdruecklich auch in Zeichenvorlagen gesucht
//STRIP001 // --------------------------------------------------------------
//STRIP001  USHORT nWhch = rAttr.Which();
//STRIP001  SfxWhichIter* pIter = NULL;
//STRIP001  const SfxPoolItem* pTmpItem;
//STRIP001  const SwAttrSet* pSet;
//STRIP001  if( RES_TXTATR_CHARFMT == nWhch )
//STRIP001  {
//STRIP001      if( bNoColls )
//STRIP001          return Found();
//STRIP001      SwCharFmt* pFmt = rAttr.GetCharFmt().GetCharFmt();
//STRIP001      if( pFmt )
//STRIP001      {
//STRIP001          pSet = &pFmt->GetAttrSet();
//STRIP001          pIter = new SfxWhichIter( *pSet );
//STRIP001          nWhch = pIter->FirstWhich();
//STRIP001          while( nWhch &&
//STRIP001              SFX_ITEM_SET != pSet->GetItemState( nWhch, TRUE, &pTmpItem ) )
//STRIP001              nWhch = pIter->NextWhich();
//STRIP001          if( !nWhch )
//STRIP001              pTmpItem = NULL;
//STRIP001      }
//STRIP001      else
//STRIP001          pTmpItem = NULL;
//STRIP001  }
//STRIP001  else
//STRIP001      pTmpItem = &rAttr.GetAttr();
//STRIP001  while( pTmpItem )
//STRIP001  {
//STRIP001      SfxItemState eState = aCmpSet.GetItemState( nWhch, FALSE, &pItem );
//STRIP001      if( SFX_ITEM_DONTCARE == eState || SFX_ITEM_SET == eState )
//STRIP001      {
//STRIP001          register USHORT n;
//STRIP001          _SwSrchChrAttr* pCmp;
//STRIP001
//STRIP001          // loesche erstmal alle, die bis zu der Start Position schon wieder
//STRIP001          // ungueltig sind:
//STRIP001
//STRIP001          _SwSrchChrAttr* pArrPtr;
//STRIP001          if( nFound )
//STRIP001              for( pArrPtr = pFndArr, n = 0; n < nArrLen; ++n, ++pArrPtr )
//STRIP001                  if( pArrPtr->nWhich && pArrPtr->nStt >= aTmp.nEnd )
//STRIP001                  {
//STRIP001                      pArrPtr->nWhich = 0;        // geloescht
//STRIP001                      nFound--;
//STRIP001                  }
//STRIP001
//STRIP001          // loesche erstmal alle, die bis zu der Start Position schon wieder
//STRIP001          // ungueltig sind. Und verschiebe alle die "offen" sind, heisst ueber
//STRIP001          // die Start Position ragen, vom Stack in den FndSet
//STRIP001
//STRIP001          if( nStackCnt )
//STRIP001              for( pArrPtr = pStackArr, n = 0; n < nArrLen; ++n, ++pArrPtr )
//STRIP001              {
//STRIP001                  if( !pArrPtr->nWhich )
//STRIP001                      continue;
//STRIP001
//STRIP001                  if( pArrPtr->nStt >= aTmp.nEnd )
//STRIP001                  {
//STRIP001                      pArrPtr->nWhich = 0;        // geloescht
//STRIP001                      if( !--nStackCnt )
//STRIP001                          break;
//STRIP001                  }
//STRIP001                  else if( pArrPtr->nEnd >= aTmp.nEnd )
//STRIP001                  {
//STRIP001                      if( ( pCmp = &pFndArr[ n ])->nWhich )
//STRIP001                      {
//STRIP001                          if( pCmp->nStt > pArrPtr->nStt )        // erweitern
//STRIP001                              pCmp->nStt = pArrPtr->nStt;
//STRIP001                      }
//STRIP001                      else
//STRIP001                      {
//STRIP001                          *pCmp = *pArrPtr;
//STRIP001                          nFound++;
//STRIP001                  }
//STRIP001                  pArrPtr->nWhich = 0;
//STRIP001                  if( !--nStackCnt )
//STRIP001                      break;
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          BOOL bContinue = FALSE;
//STRIP001          if( SFX_ITEM_DONTCARE == eState  )
//STRIP001          {
//STRIP001              // wird Attribut gueltig ?
//STRIP001              if( !CmpAttr( aCmpSet.GetPool()->GetDefaultItem( nWhch ),
//STRIP001                  *pTmpItem ) )
//STRIP001              {
//STRIP001                  // suche das Attribut und erweiter es gegebenenfalls
//STRIP001                  if( !( pCmp = &pFndArr[ nWhch - nArrStart ])->nWhich )
//STRIP001                  {
//STRIP001                      *pCmp = aTmp;               // nicht gefunden, eintragen
//STRIP001                      nFound++;
//STRIP001                  }
//STRIP001                  else if( pCmp->nStt > aTmp.nStt )       // erweitern ?
//STRIP001                      pCmp->nStt = aTmp.nStt;
//STRIP001
//STRIP001                  bContinue = TRUE;
//STRIP001              }
//STRIP001          }
//STRIP001          // wird Attribut gueltig ?
//STRIP001          else if( CmpAttr( *pItem, *pTmpItem ))
//STRIP001          {
//STRIP001              pFndArr[ nWhch - nArrStart ] = aTmp;
//STRIP001              ++nFound;
//STRIP001              bContinue = TRUE;
//STRIP001          }
//STRIP001
//STRIP001          // tja, dann muss es auf den Stack
//STRIP001          if( !bContinue && ( pCmp = &pFndArr[ nWhch - nArrStart ])->nWhich )
//STRIP001          {
//STRIP001              // vorhanden, auf den Stack. Aber nur wenn es noch grosser ist
//STRIP001              if( pCmp->nStt < aTmp.nStt )
//STRIP001              {
//STRIP001                  ASSERT( !pStackArr[ nWhch - nArrStart ].nWhich,
//STRIP001                          "Stack-Platz ist noch belegt" );
//STRIP001
//STRIP001 // ---------
//STRIP001 // JP 22.08.96: nur Ende manipulieren reicht nicht. Bug 30547
//STRIP001 //           pCmp->nEnd = aTmp.nStt;
//STRIP001                  if( aTmp.nEnd <= pCmp->nEnd )
//STRIP001                      pCmp->nEnd = aTmp.nStt;
//STRIP001                  else
//STRIP001                      pCmp->nStt = aTmp.nEnd;
//STRIP001 // ---------
//STRIP001
//STRIP001                  pStackArr[ nWhch - nArrStart ] = *pCmp;
//STRIP001                  nStackCnt++;
//STRIP001              }
//STRIP001              pCmp->nWhich = 0;
//STRIP001              nFound--;
//STRIP001          }
//STRIP001      }
//STRIP001      if( pIter )
//STRIP001      {
//STRIP001          nWhch = pIter->NextWhich();
//STRIP001          while( nWhch &&
//STRIP001              SFX_ITEM_SET != pSet->GetItemState( nWhch, TRUE, &pTmpItem ) )
//STRIP001              nWhch = pIter->NextWhich();
//STRIP001          if( !nWhch )
//STRIP001              break;
//STRIP001      }
//STRIP001      else
//STRIP001          break;
//STRIP001  }
//STRIP001  return Found();
//STRIP001 }


//STRIP001 xub_StrLen SwAttrCheckArr::Start() const
//STRIP001 {
//STRIP001  xub_StrLen nStart = nNdStt;
//STRIP001  _SwSrchChrAttr* pArrPtr = pFndArr;
//STRIP001  for( USHORT n = 0; n < nArrLen; ++n, ++pArrPtr )
//STRIP001      if( pArrPtr->nWhich && pArrPtr->nStt > nStart )
//STRIP001          nStart = pArrPtr->nStt;
//STRIP001
//STRIP001  return nStart;
//STRIP001 }


//STRIP001 xub_StrLen SwAttrCheckArr::End() const
//STRIP001 {
//STRIP001  _SwSrchChrAttr* pArrPtr = pFndArr;
//STRIP001  xub_StrLen nEnd = nNdEnd;
//STRIP001  for( USHORT n = 0; n < nArrLen; ++n, ++pArrPtr )
//STRIP001      if( pArrPtr->nWhich && pArrPtr->nEnd < nEnd )
//STRIP001          nEnd = pArrPtr->nEnd;
//STRIP001
//STRIP001  return nEnd;
//STRIP001 }


//STRIP001 int SwAttrCheckArr::CheckStack()
//STRIP001 {
//STRIP001  if( !nStackCnt )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  USHORT n;
//STRIP001  xub_StrLen nSttPos = Start(), nEndPos = End();
//STRIP001  _SwSrchChrAttr* pArrPtr;
//STRIP001  for( pArrPtr = pStackArr, n = 0; n < nArrLen; ++n, ++pArrPtr )
//STRIP001  {
//STRIP001      if( !pArrPtr->nWhich )
//STRIP001          continue;
//STRIP001
//STRIP001      if( bForward ? pArrPtr->nEnd <= nSttPos : pArrPtr->nStt >= nEndPos )
//STRIP001      {
//STRIP001          pArrPtr->nWhich = 0;        // geloescht
//STRIP001          if( !--nStackCnt )
//STRIP001              return nFound == aCmpSet.Count();
//STRIP001      }
//STRIP001      else if( bForward ? pArrPtr->nStt < nEndPos : pArrPtr->nEnd > nSttPos )
//STRIP001      {
//STRIP001          // alle die "offen" sind, heisst ueber die Start Position ragen,
//STRIP001          // im FndSet setzen
//STRIP001          ASSERT( !pFndArr[ n ].nWhich, "Array-Platz ist noch belegt" );
//STRIP001          pFndArr[ n ] = *pArrPtr;
//STRIP001          pArrPtr->nWhich = 0;
//STRIP001          nFound++;
//STRIP001          if( !--nStackCnt )
//STRIP001              return nFound == aCmpSet.Count();
//STRIP001      }
//STRIP001  }
//STRIP001  return nFound == aCmpSet.Count();
//STRIP001 }



//STRIP001 int lcl_SearchForward( const SwTxtNode& rTxtNd, SwAttrCheckArr& rCmpArr,
//STRIP001                          SwPaM& rPam )
//STRIP001 {
//STRIP001  xub_StrLen nEndPos, nSttPos;
//STRIP001  rCmpArr.SetNewSet( rTxtNd, rPam );
//STRIP001  if( !rTxtNd.HasHints() )
//STRIP001  {
//STRIP001      if( !rCmpArr.Found() )
//STRIP001          return FALSE;
//STRIP001      nEndPos = rCmpArr.GetNdEnd();
//STRIP001      lcl_SetAttrPam( rPam, rCmpArr.GetNdStt(), &nEndPos, TRUE );
//STRIP001      return TRUE;
//STRIP001  }
//STRIP001
//STRIP001  // dann gehe mal durch das nach "Start" sortierte Array
//STRIP001  const SwpHints& rHtArr = rTxtNd.GetSwpHints();
//STRIP001  const SwTxtAttr* pAttr;
//STRIP001  USHORT nPos = 0;
//STRIP001
//STRIP001  // sollte jetzt schon alles vorhanden sein, dann teste, mit welchem
//STRIP001  // das wieder beendet wird.
//STRIP001  if( rCmpArr.Found() )
//STRIP001  {
//STRIP001      for( ; nPos < rHtArr.Count(); ++nPos )
//STRIP001          if( !rCmpArr.SetAttrFwd( *( pAttr = rHtArr.GetStart( nPos )) ) )
//STRIP001          {
//STRIP001              if( rCmpArr.GetNdStt() < *pAttr->GetStart() )
//STRIP001              {
//STRIP001                  // dann haben wir unser Ende:
//STRIP001                  lcl_SetAttrPam( rPam, rCmpArr.GetNdStt(),
//STRIP001                              pAttr->GetStart(), TRUE );
//STRIP001                  return TRUE;
//STRIP001              }
//STRIP001              // ansonsten muessen wir weiter suchen
//STRIP001              break;
//STRIP001          }
//STRIP001
//STRIP001      if( nPos == rHtArr.Count() && rCmpArr.Found() )
//STRIP001      {
//STRIP001          // dann haben wir unseren Bereich
//STRIP001          nEndPos = rCmpArr.GetNdEnd();
//STRIP001          lcl_SetAttrPam( rPam, rCmpArr.GetNdStt(), &nEndPos, TRUE );
//STRIP001          return TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  for( ; nPos < rHtArr.Count(); ++nPos )
//STRIP001      if( rCmpArr.SetAttrFwd( *( pAttr = rHtArr.GetStart( nPos )) ) )
//STRIP001      {
//STRIP001          // sollten noch mehr auf der gleichen Position anfangen ??
//STRIP001          // auch die noch mit testen !!
//STRIP001          nSttPos = *pAttr->GetStart();
//STRIP001          while( ++nPos < rHtArr.Count() && nSttPos ==
//STRIP001                  *( pAttr = rHtArr.GetStart( nPos ))->GetStart() &&
//STRIP001                  rCmpArr.SetAttrFwd( *pAttr ) )
//STRIP001              ;
//STRIP001          if( !rCmpArr.Found() )
//STRIP001              continue;
//STRIP001
//STRIP001          // dann haben wir den Bereich zusammen
//STRIP001          if( (nSttPos = rCmpArr.Start()) > (nEndPos = rCmpArr.End()) )
//STRIP001              return FALSE;
//STRIP001          lcl_SetAttrPam( rPam, nSttPos, &nEndPos, TRUE );
//STRIP001          return TRUE;
//STRIP001      }
//STRIP001
//STRIP001  if( !rCmpArr.CheckStack() ||
//STRIP001      (nSttPos = rCmpArr.Start()) > (nEndPos = rCmpArr.End()) )
//STRIP001      return FALSE;
//STRIP001  lcl_SetAttrPam( rPam, nSttPos, &nEndPos, TRUE );
//STRIP001  return TRUE;
//STRIP001 }


//STRIP001 int lcl_SearchBackward( const SwTxtNode& rTxtNd, SwAttrCheckArr& rCmpArr,
//STRIP001                          SwPaM& rPam )
//STRIP001 {
//STRIP001  xub_StrLen nEndPos, nSttPos;
//STRIP001  rCmpArr.SetNewSet( rTxtNd, rPam );
//STRIP001  if( !rTxtNd.HasHints() )
//STRIP001  {
//STRIP001      if( !rCmpArr.Found() )
//STRIP001          return FALSE;
//STRIP001      nEndPos = rCmpArr.GetNdEnd();
//STRIP001      lcl_SetAttrPam( rPam, rCmpArr.GetNdStt(), &nEndPos, FALSE );
//STRIP001      return TRUE;
//STRIP001  }
//STRIP001
//STRIP001  // dann gehe mal durch das nach "Start" sortierte Array
//STRIP001  const SwpHints& rHtArr = rTxtNd.GetSwpHints();
//STRIP001  const SwTxtAttr* pAttr;
//STRIP001  USHORT nPos = rHtArr.Count();
//STRIP001
//STRIP001  // sollte jetzt schon alles vorhanden sein, dann teste, mit welchem
//STRIP001  // das wieder beendet wird.
//STRIP001  if( rCmpArr.Found() )
//STRIP001  {
//STRIP001      while( nPos )
//STRIP001          if( !rCmpArr.SetAttrBwd( *( pAttr = rHtArr.GetEnd( --nPos )) ) )
//STRIP001          {
//STRIP001              nSttPos = *pAttr->GetAnyEnd();
//STRIP001              if( nSttPos < rCmpArr.GetNdEnd() )
//STRIP001              {
//STRIP001                  // dann haben wir unser Ende:
//STRIP001                  nEndPos = rCmpArr.GetNdEnd();
//STRIP001                  lcl_SetAttrPam( rPam, nSttPos, &nEndPos, FALSE );
//STRIP001                  return TRUE;
//STRIP001              }
//STRIP001
//STRIP001              // ansonsten muessen wir weiter suchen
//STRIP001              break;
//STRIP001          }
//STRIP001
//STRIP001      if( !nPos && rCmpArr.Found() )
//STRIP001      {
//STRIP001          // dann haben wir unseren Bereich
//STRIP001          nEndPos = rCmpArr.GetNdEnd();
//STRIP001          lcl_SetAttrPam( rPam, rCmpArr.GetNdStt(), &nEndPos, FALSE );
//STRIP001          return TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  while( nPos )
//STRIP001      if( rCmpArr.SetAttrBwd( *( pAttr = rHtArr.GetEnd( --nPos )) ) )
//STRIP001      {
//STRIP001          // sollten noch mehr auf der gleichen Position anfangen ??
//STRIP001          // auch die noch mit testen !!
//STRIP001          if( nPos )
//STRIP001          {
//STRIP001              nEndPos = *pAttr->GetAnyEnd();
//STRIP001              while( --nPos && nEndPos ==
//STRIP001                      *( pAttr = rHtArr.GetEnd( nPos ))->GetAnyEnd() &&
//STRIP001                      rCmpArr.SetAttrBwd( *pAttr ) )
//STRIP001                  ;
//STRIP001          }
//STRIP001          if( !rCmpArr.Found() )
//STRIP001              continue;
//STRIP001
//STRIP001
//STRIP001          // dann haben wir den Bereich zusammen
//STRIP001          if( (nSttPos = rCmpArr.Start()) > (nEndPos = rCmpArr.End()) )
//STRIP001              return FALSE;
//STRIP001          lcl_SetAttrPam( rPam, nSttPos, &nEndPos, FALSE );
//STRIP001          return TRUE;
//STRIP001      }
//STRIP001
//STRIP001  if( !rCmpArr.CheckStack() ||
//STRIP001      (nSttPos = rCmpArr.Start()) > (nEndPos = rCmpArr.End()) )
//STRIP001      return FALSE;
//STRIP001  lcl_SetAttrPam( rPam, nSttPos, &nEndPos, FALSE );
//STRIP001  return TRUE;
//STRIP001 }


//STRIP001 int lcl_Search( const SwCntntNode& rCNd, SwPaM& rPam,
//STRIP001          const SfxItemSet& rCmpSet, BOOL bNoColls  )
//STRIP001 {
//STRIP001  // nur die harte Attributierung suchen ?
//STRIP001  if( bNoColls && !rCNd.GetpSwAttrSet() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  const SfxItemSet& rNdSet = rCNd.GetSwAttrSet();
//STRIP001  SfxItemIter aIter( rCmpSet );
//STRIP001  const SfxPoolItem* pItem = aIter.GetCurItem();
//STRIP001  const SfxPoolItem* pNdItem;
//STRIP001  USHORT nWhich;
//STRIP001
//STRIP001  while( TRUE )
//STRIP001  {
//STRIP001      // nur testen, ob vorhanden ist ?
//STRIP001      if( IsInvalidItem( pItem ))
//STRIP001      {
//STRIP001          nWhich = rCmpSet.GetWhichByPos( aIter.GetCurPos() );
//STRIP001          if( SFX_ITEM_SET != rNdSet.GetItemState( nWhich, !bNoColls, &pNdItem )
//STRIP001              || CmpAttr( *pNdItem, rNdSet.GetPool()->GetDefaultItem( nWhich ) ))
//STRIP001              return FALSE;
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          nWhich = pItem->Which();
//STRIP001 //JP 27.02.95: wenn nach defaults gesucht wird, dann muss man bis zum Pool
//STRIP001 //               runter
//STRIP001 //           if( SFX_ITEM_SET != rNdSet.GetItemState( nWhich, !bNoColls, &pNdItem )
//STRIP001 //               || *pNdItem != *pItem )
//STRIP001          if( !CmpAttr( rNdSet.Get( nWhich, !bNoColls ), *pItem ))
//STRIP001              return FALSE;
//STRIP001      }
//STRIP001
//STRIP001      if( aIter.IsAtEnd() )
//STRIP001          break;
//STRIP001      pItem = aIter.NextItem();
//STRIP001  }
//STRIP001  return TRUE;            // wurde gefunden
//STRIP001 }


//STRIP001 FASTBOOL SwPaM::Find( const SfxPoolItem& rAttr, FASTBOOL bValue, SwMoveFn fnMove,
//STRIP001                  const SwPaM *pRegion, FASTBOOL bInReadOnly )
//STRIP001 {
//STRIP001  // stelle fest welches Attribut gesucht wird:
//STRIP001  USHORT nWhich = rAttr.Which();
//STRIP001  int bCharAttr = RES_CHRATR_BEGIN <= nWhich && nWhich < RES_TXTATR_END;
//STRIP001
//STRIP001  SwPaM* pPam = MakeRegion( fnMove, pRegion );
//STRIP001
//STRIP001  FASTBOOL bFound = FALSE;
//STRIP001  FASTBOOL bFirst = TRUE;
//STRIP001  FASTBOOL bSrchForward = fnMove == fnMoveForward;
//STRIP001  SwCntntNode * pNode;
//STRIP001  const SfxPoolItem* pItem;
//STRIP001  SwpFmts aFmtArr;
//STRIP001
//STRIP001  // Wenn am Anfang/Ende, aus dem Node moven
//STRIP001  if( bSrchForward
//STRIP001      ? pPam->GetPoint()->nContent.GetIndex() == pPam->GetCntntNode()->Len()
//STRIP001      : !pPam->GetPoint()->nContent.GetIndex() )
//STRIP001  {
//STRIP001      if( !(*fnMove->fnNds)( &pPam->GetPoint()->nNode, FALSE ))
//STRIP001      {
//STRIP001          delete pPam;
//STRIP001          return FALSE;
//STRIP001      }
//STRIP001      SwCntntNode *pNd = pPam->GetCntntNode();
//STRIP001      xub_StrLen nTmpPos = bSrchForward ? 0 : pNd->Len();
//STRIP001      pPam->GetPoint()->nContent.Assign( pNd, nTmpPos );
//STRIP001  }
//STRIP001
//STRIP001  while( 0 != ( pNode = ::GetNode( *pPam, bFirst, fnMove, bInReadOnly ) ) )
//STRIP001  {
//STRIP001      if( bCharAttr )
//STRIP001      {
//STRIP001          if( !pNode->IsTxtNode() )       // CharAttr sind nur in TextNodes
//STRIP001              continue;
//STRIP001
//STRIP001          if( ((SwTxtNode*)pNode)->HasHints() &&
//STRIP001              lcl_Search( *(SwTxtNode*)pNode, *pPam, rAttr, fnMove,  bValue ))
//STRIP001          {
//STRIP001              // setze auf die Werte vom Attribut
//STRIP001              SetMark();
//STRIP001              *GetPoint() = *pPam->GetPoint();
//STRIP001              *GetMark() = *pPam->GetMark();
//STRIP001              bFound = TRUE;
//STRIP001              break;
//STRIP001          }
//STRIP001          else if( RES_TXTATR_BEGIN < nWhich )   // TextAttribut
//STRIP001              continue;               // --> also weiter
//STRIP001      }
//STRIP001
//STRIP001      // keine harte Attributierung, dann pruefe, ob die Vorlage schon
//STRIP001      // mal nach dem Attribut befragt wurde
//STRIP001      if( !pNode->GetpSwAttrSet() )
//STRIP001      {
//STRIP001          const SwFmt* pTmpFmt = pNode->GetFmtColl();
//STRIP001          if( aFmtArr.Count() && aFmtArr.Seek_Entry( pTmpFmt ))
//STRIP001              continue;   // die Collection wurde schon mal befragt
//STRIP001          aFmtArr.Insert( pTmpFmt );
//STRIP001      }
//STRIP001
//STRIP001      if( SFX_ITEM_SET == pNode->GetSwAttrSet().GetItemState( nWhich,
//STRIP001          TRUE, &pItem ) && ( !bValue || *pItem == rAttr ) )
//STRIP001      {
//STRIP001          // FORWARD:  Point an das Ende, GetMark zum Anfanf vom Node
//STRIP001          // BACKWARD: Point zum Anfang,  GetMark an das Ende vom Node
//STRIP001          // und immer nach der Logik: inkl. Start, exkl. End !!!
//STRIP001          *GetPoint() = *pPam->GetPoint();
//STRIP001          SetMark();
//STRIP001          pNode->MakeEndIndex( &GetPoint()->nContent );
//STRIP001          Move( fnMoveForward, fnGoCntnt );
//STRIP001          bFound = TRUE;
//STRIP001          break;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // beim rueckwaerts Suchen noch Point und Mark vertauschen
//STRIP001  if( bFound && !bSrchForward )
//STRIP001      Exchange();
//STRIP001
//STRIP001  delete pPam;
//STRIP001  return bFound;
//STRIP001 }


//STRIP001 typedef int (*FnSearchAttr)( const SwTxtNode&, SwAttrCheckArr&, SwPaM& );
//STRIP001
//STRIP001 FASTBOOL SwPaM::Find( const SfxItemSet& rSet, FASTBOOL bNoColls, SwMoveFn fnMove,
//STRIP001                  const SwPaM *pRegion, FASTBOOL bInReadOnly )
//STRIP001 {
//STRIP001  SwPaM* pPam = MakeRegion( fnMove, pRegion );
//STRIP001
//STRIP001  FASTBOOL bFound = FALSE;
//STRIP001  FASTBOOL bFirst = TRUE;
//STRIP001  FASTBOOL bSrchForward = fnMove == fnMoveForward;
//STRIP001  SwCntntNode * pNode;
//STRIP001  SwpFmts aFmtArr;
//STRIP001
//STRIP001  // teste doch mal welche Text/Char-Attribute gesucht werden
//STRIP001  SwAttrCheckArr aCmpArr( rSet, bSrchForward, bNoColls );
//STRIP001  SfxItemSet aOtherSet( GetDoc()->GetAttrPool(),
//STRIP001                          RES_PARATR_BEGIN, RES_GRFATR_END-1 );
//STRIP001  aOtherSet.Put( rSet, FALSE );   // alle Invalid-Items erhalten!
//STRIP001
//STRIP001  FnSearchAttr fnSearch = bSrchForward
//STRIP001                              ? (&::lcl_SearchForward)
//STRIP001                              : (&::lcl_SearchBackward);
//STRIP001
//STRIP001  // Wenn am Anfang/Ende, aus dem Node moven
//STRIP001  // Wenn am Anfang/Ende, aus dem Node moven
//STRIP001  if( bSrchForward
//STRIP001      ? pPam->GetPoint()->nContent.GetIndex() == pPam->GetCntntNode()->Len()
//STRIP001      : !pPam->GetPoint()->nContent.GetIndex() )
//STRIP001  {
//STRIP001      if( !(*fnMove->fnNds)( &pPam->GetPoint()->nNode, FALSE ))
//STRIP001      {
//STRIP001          delete pPam;
//STRIP001          return FALSE;
//STRIP001      }
//STRIP001      SwCntntNode *pNd = pPam->GetCntntNode();
//STRIP001      xub_StrLen nTmpPos = bSrchForward ? 0 : pNd->Len();
//STRIP001      pPam->GetPoint()->nContent.Assign( pNd, nTmpPos );
//STRIP001  }
//STRIP001
//STRIP001
//STRIP001  while( 0 != ( pNode = ::GetNode( *pPam, bFirst, fnMove, bInReadOnly ) ) )
//STRIP001  {
//STRIP001      if( aCmpArr.Count() )
//STRIP001      {
//STRIP001          if( !pNode->IsTxtNode() )       // CharAttr sind nur in TextNodes
//STRIP001              continue;
//STRIP001
//STRIP001          if( (!aOtherSet.Count() ||
//STRIP001              lcl_Search( *pNode, *pPam, aOtherSet, bNoColls )) &&
//STRIP001              (*fnSearch)( *(SwTxtNode*)pNode, aCmpArr, *pPam ))
//STRIP001          {
//STRIP001              // setze auf die Werte vom Attribut
//STRIP001              SetMark();
//STRIP001              *GetPoint() = *pPam->GetPoint();
//STRIP001              *GetMark() = *pPam->GetMark();
//STRIP001              bFound = TRUE;
//STRIP001              break;
//STRIP001          }
//STRIP001          continue;       // TextAttribute
//STRIP001      }
//STRIP001
//STRIP001      if( !aOtherSet.Count() )
//STRIP001          continue;
//STRIP001
//STRIP001      // keine harte Attributierung, dann pruefe, ob die Vorlage schon
//STRIP001      // mal nach dem Attribut befragt wurde
//STRIP001      if( !pNode->GetpSwAttrSet() )
//STRIP001      {
//STRIP001          const SwFmt* pTmpFmt = pNode->GetFmtColl();
//STRIP001          if( aFmtArr.Count() && aFmtArr.Seek_Entry( pTmpFmt ))
//STRIP001              continue;   // die Collection wurde schon mal befragt
//STRIP001          aFmtArr.Insert( pTmpFmt );
//STRIP001      }
//STRIP001
//STRIP001      if( lcl_Search( *pNode, *pPam, aOtherSet, bNoColls ))
//STRIP001      {
//STRIP001          // FORWARD:  Point an das Ende, GetMark zum Anfanf vom Node
//STRIP001          // BACKWARD: Point zum Anfang,  GetMark an das Ende vom Node
//STRIP001          // und immer nach der Logik: inkl. Start, exkl. End !!!
//STRIP001          *GetPoint() = *pPam->GetPoint();
//STRIP001          SetMark();
//STRIP001          pNode->MakeEndIndex( &GetPoint()->nContent );
//STRIP001          Move( fnMoveForward, fnGoCntnt );
//STRIP001          bFound = TRUE;
//STRIP001          break;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // beim rueckwaerts Suchen noch Point und Mark vertauschen
//STRIP001  if( bFound && !bSrchForward )
//STRIP001      Exchange();
//STRIP001
//STRIP001  delete pPam;
//STRIP001  return bFound;
//STRIP001 }

//------------------ Methoden vom SwCursor ---------------------------

// Parameter fuer das Suchen vom Attributen
struct SwFindParaAttr : public SwFindParas
{
    BOOL bValue;
    const SfxItemSet *pSet, *pReplSet;
    const SearchOptions *pSearchOpt;
    SwCursor& rCursor;
    ::utl::TextSearch* pSTxt;

    SwFindParaAttr( const SfxItemSet& rSet, BOOL bNoCollection,
                    const SearchOptions* pOpt, const SfxItemSet* pRSet,
                    SwCursor& rCrsr )
        : pSet( &rSet ), pReplSet( pRSet ), rCursor( rCrsr ),
            bValue( bNoCollection ), pSearchOpt( pOpt ), pSTxt( 0 )
        {}
    ~SwFindParaAttr()   { delete pSTxt; }

    virtual int Find( SwPaM* , SwMoveFn , const SwPaM*, FASTBOOL bInReadOnly );
     virtual int IsReplaceMode() const;
};


/*N*/int SwFindParaAttr::Find( SwPaM* pCrsr, SwMoveFn fnMove, const SwPaM* pRegion,
/*N*/                           FASTBOOL bInReadOnly )
/*N*/{
DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001      // String ersetzen ?? (nur wenn Text angegeben oder nicht attributiert
//STRIP001  //                      gesucht wird)
//STRIP001  BOOL bReplaceTxt = pSearchOpt && ( pSearchOpt->replaceString.getLength() ||
//STRIP001                                  !pSet->Count() );
//STRIP001  BOOL bReplaceAttr = pReplSet && pReplSet->Count();
//STRIP001  if( bInReadOnly && (bReplaceAttr || bReplaceTxt ))
//STRIP001      bInReadOnly = FALSE;
//STRIP001
//STRIP001  // wir suchen nach Attributen, soll zusaetzlich Text gesucht werden ?
//STRIP001  {
//STRIP001      SwPaM aRegion( *pRegion->GetMark(), *pRegion->GetPoint() );
//STRIP001      SwPaM* pTextRegion = &aRegion;
//STRIP001      SwPaM aSrchPam( *pCrsr->GetPoint() );
//STRIP001
//STRIP001      while( TRUE )
//STRIP001      {
//STRIP001          if( pSet->Count() )         // gibts ueberhaupt Attributierung?
//STRIP001          {
//STRIP001              // zuerst die Attributierung
//STRIP001              if( !aSrchPam.Find( *pSet, bValue, fnMove, &aRegion, bInReadOnly ) )
//STRIP001 //JP 17.11.95: was ist mit Attributen in leeren Absaetzen !!
//STRIP001 //                   || *pCrsr->GetMark() == *pCrsr->GetPoint() )    // kein Bereich ??
//STRIP001                  return FIND_NOT_FOUND;
//STRIP001
//STRIP001              if( !pSearchOpt )
//STRIP001                  break;      // ok, nur Attribute, also gefunden
//STRIP001
//STRIP001              pTextRegion = &aSrchPam;
//STRIP001          }
//STRIP001          else if( !pSearchOpt )
//STRIP001              return FIND_NOT_FOUND;
//STRIP001
//STRIP001          // dann darin den Text
//STRIP001          if( !pSTxt )
//STRIP001          {
//STRIP001              SearchOptions aTmp( *pSearchOpt );
//STRIP001
//STRIP001              // search in selection
//STRIP001              aTmp.searchFlag |= (SearchFlags::REG_NOT_BEGINOFLINE |
//STRIP001                                  SearchFlags::REG_NOT_ENDOFLINE);
//STRIP001
//STRIP001              String aLang, aCntry;
//STRIP001              ConvertLanguageToIsoNames( LANGUAGE_SYSTEM, aLang, aCntry );
//STRIP001              aTmp.Locale = Locale( aLang, aCntry, ::rtl::OUString() );
//STRIP001
//STRIP001              pSTxt = new utl::TextSearch( aTmp );
//STRIP001          }
//STRIP001          // Bug 24665: suche im richtigen Bereich weiter (pTextRegion!)
//STRIP001          if( aSrchPam.Find( *pSearchOpt, *pSTxt, fnMove, pTextRegion, bInReadOnly ) &&
//STRIP001              *aSrchPam.GetMark() != *aSrchPam.GetPoint() )   // gefunden ?
//STRIP001              break;                                      // also raus
//STRIP001          else if( !pSet->Count() )
//STRIP001              return FIND_NOT_FOUND;      // nur Text und nicht gefunden
//STRIP001
//STRIP001          // und wieder neu aufsetzen, aber eine Position weiter
//STRIP001          //JP 04.11.97: Bug 44897 - aber den Mark wieder aufheben, damit
//STRIP001          //              weiterbewegt werden kann!
//STRIP001          {
//STRIP001              BOOL bCheckRegion = TRUE;
//STRIP001              SwPosition* pPos = aSrchPam.GetPoint();
//STRIP001              if( !(*fnMove->fnNd)( &pPos->nNode.GetNode(),
//STRIP001                                      &pPos->nContent, CRSR_SKIP_CHARS ))
//STRIP001              {
//STRIP001                  if( (*fnMove->fnNds)( &pPos->nNode, FALSE ))
//STRIP001                  {
//STRIP001                      SwCntntNode *pNd = pPos->nNode.GetNode().GetCntntNode();
//STRIP001                      xub_StrLen nCPos;
//STRIP001                      if( fnMove == fnMoveForward )
//STRIP001                          nCPos = 0;
//STRIP001                      else
//STRIP001                          nCPos = pNd->Len();
//STRIP001                      pPos->nContent.Assign( pNd, nCPos );
//STRIP001                  }
//STRIP001                  else
//STRIP001                      bCheckRegion = FALSE;
//STRIP001              }
//STRIP001              if( !bCheckRegion || *aRegion.GetPoint() <= *pPos )
//STRIP001                  return FIND_NOT_FOUND;      // nicht gefunden
//STRIP001          }
//STRIP001          *aRegion.GetMark() = *aSrchPam.GetPoint();
//STRIP001      }
//STRIP001
//STRIP001      *pCrsr->GetPoint() = *aSrchPam.GetPoint();
//STRIP001      pCrsr->SetMark();
//STRIP001      *pCrsr->GetMark() = *aSrchPam.GetMark();
//STRIP001  }
//STRIP001
//STRIP001  if( bReplaceTxt )
//STRIP001  {
//STRIP001      int bRegExp = SearchAlgorithms_REGEXP == pSearchOpt->algorithmType;
//STRIP001      SwIndex& rSttCntIdx = pCrsr->Start()->nContent;
//STRIP001      xub_StrLen nSttCnt = rSttCntIdx.GetIndex();
//STRIP001
//STRIP001      // damit die Region auch verschoben wird, in den Shell-Cursr-Ring
//STRIP001      // mit aufnehmen !!
//STRIP001      Ring *pPrev;
//STRIP001      if( bRegExp )
//STRIP001      {
//STRIP001          pPrev = pRegion->GetPrev();
//STRIP001          ((Ring*)pRegion)->MoveRingTo( &rCursor );
//STRIP001      }
//STRIP001
//STRIP001      rCursor.GetDoc()->Replace( *pCrsr, pSearchOpt->replaceString, bRegExp );
//STRIP001      rCursor.SaveTblBoxCntnt( pCrsr->GetPoint() );
//STRIP001
//STRIP001      if( bRegExp )
//STRIP001      {
//STRIP001          // und die Region wieder herausnehmen:
//STRIP001          Ring *p, *pNext = (Ring*)pRegion;
//STRIP001          do {
//STRIP001              p = pNext;
//STRIP001              pNext = p->GetNext();
//STRIP001              p->MoveTo( (Ring*)pRegion );
//STRIP001          } while( p != pPrev );
//STRIP001      }
//STRIP001      rSttCntIdx = nSttCnt;
//STRIP001  }
//STRIP001
//STRIP001  if( bReplaceAttr )
//STRIP001  {
//STRIP001      // --- Ist die Selection noch da ??????
//STRIP001
//STRIP001      // und noch die Attribute setzen
//STRIP001 #ifdef OLD
//STRIP001      pCrsr->GetDoc()->Insert( *pCrsr, *pReplSet );
//STRIP001 #else
//STRIP001      //JP 13.07.95: alle gesuchten Attribute werden, wenn nicht im
//STRIP001      //              ReplaceSet angegeben, auf Default zurueck gesetzt
//STRIP001
//STRIP001      if( !pSet->Count() )
//STRIP001          pCrsr->GetDoc()->Insert( *pCrsr, *pReplSet );
//STRIP001      else
//STRIP001      {
//STRIP001          SfxItemPool* pPool = pReplSet->GetPool();
//STRIP001          SfxItemSet aSet( *pPool, pReplSet->GetRanges() );
//STRIP001
//STRIP001          SfxItemIter aIter( *pSet );
//STRIP001          const SfxPoolItem* pItem = aIter.GetCurItem();
//STRIP001          while( TRUE )
//STRIP001          {
//STRIP001              // alle die nicht gesetzt sind mit Pool-Defaults aufuellen
//STRIP001              if( !IsInvalidItem( pItem ) && SFX_ITEM_SET !=
//STRIP001                  pReplSet->GetItemState( pItem->Which(), FALSE ))
//STRIP001                  aSet.Put( pPool->GetDefaultItem( pItem->Which() ));
//STRIP001
//STRIP001              if( aIter.IsAtEnd() )
//STRIP001                  break;
//STRIP001              pItem = aIter.NextItem();
//STRIP001          }
//STRIP001          aSet.Put( *pReplSet );
//STRIP001          pCrsr->GetDoc()->Insert( *pCrsr, aSet );
//STRIP001      }
//STRIP001 #endif
//STRIP001      return FIND_NO_RING;
//STRIP001  }
//STRIP001
//STRIP001  else
//STRIP001      return FIND_FOUND;
/*N*/ }


/*N*/int SwFindParaAttr::IsReplaceMode() const
/*N*/{
DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001  return ( pSearchOpt && pSearchOpt->replaceString.getLength() ) ||
//STRIP001         ( pReplSet && pReplSet->Count() );
/*N*/ }

// Suchen nach Attributen


/*M*/ ULONG SwCursor::Find( const SfxItemSet& rSet, FASTBOOL bNoCollections,
/*M*/                   SwDocPositions nStart, SwDocPositions nEnde, BOOL& bCancel,
/*M*/                   FindRanges eFndRngs,
/*M*/                   const SearchOptions* pSearchOpt, const SfxItemSet* pReplSet )
/*M*/ {
/*M*/   // OLE-Benachrichtigung abschalten !!
/*M*/   SwDoc* pDoc = GetDoc();
/*M*/   Link aLnk( pDoc->GetOle2Link() );
/*M*/   pDoc->SetOle2Link( Link() );
/*M*/
/*M*/   BOOL bReplace = ( pSearchOpt && ( pSearchOpt->replaceString.getLength() ||
/*M*/                                   !rSet.Count() ) ) ||
/*M*/                   (pReplSet && pReplSet->Count());
/*M*/   BOOL bSttUndo = pDoc->DoesUndo() && bReplace;
/*M*/   if( bSttUndo )
/*M*/       pDoc->StartUndo( UNDO_REPLACE );
/*M*/
/*M*/   SwFindParaAttr aSwFindParaAttr( rSet, bNoCollections, pSearchOpt,
/*M*/                                   pReplSet, *this );
/*M*/
/*M*/     ULONG nRet = FindAll(aSwFindParaAttr, nStart, nEnde, eFndRngs, bCancel );
/*M*/   pDoc->SetOle2Link( aLnk );
/*M*/   if( nRet && bReplace )
/*M*/       pDoc->SetModified();
/*M*/
/*M*/   if( bSttUndo )
/*M*/       pDoc->EndUndo( UNDO_REPLACE );
/*M*/
/*M*/   return nRet;
/*M*/ }



}
