/*************************************************************************
 *
 *  $RCSfile: sw_gctable.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 17:10:58 $
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

// auto strip #ifndef _SVX_BOXITEM_HXX //autogen
// auto strip #include <bf_svx/boxitem.hxx>
// auto strip #endif

#ifndef _TBLRWCL_HXX
#include <tblrwcl.hxx>
#endif
#ifndef _SWTBLFMT_HXX
#include <swtblfmt.hxx>
#endif
namespace binfilter {


//STRIP001 inline const SvxBorderLine* GetLineTB( const SvxBoxItem* pBox, BOOL bTop )
//STRIP001 {
//STRIP001  return bTop ? pBox->GetTop() : pBox->GetBottom();
//STRIP001 }


//STRIP001 BOOL _SwGCBorder_BoxBrd::CheckLeftBorderOfFormat( const SwFrmFmt& rFmt )
//STRIP001 {
//STRIP001  const SvxBorderLine* pBrd;
//STRIP001  const SfxPoolItem* pItem;
//STRIP001  if( SFX_ITEM_SET == rFmt.GetItemState( RES_BOX, TRUE, &pItem ) &&
//STRIP001      0 != ( pBrd = ((SvxBoxItem*)pItem)->GetLeft() ) )
//STRIP001  {
//STRIP001      if( *pBrdLn == *pBrd )
//STRIP001          bAnyBorderFnd = TRUE;
//STRIP001      return TRUE;
//STRIP001  }
//STRIP001  return FALSE;
//STRIP001 }



//STRIP001 BOOL lcl_GCBorder_ChkBoxBrd_L( const SwTableLine*& rpLine, void* pPara )
//STRIP001 {
//STRIP001  const SwTableBox* pBox = rpLine->GetTabBoxes()[ 0 ];
//STRIP001  return lcl_GCBorder_ChkBoxBrd_B( pBox, pPara );
//STRIP001 }

//STRIP001 BOOL lcl_GCBorder_ChkBoxBrd_B( const SwTableBox*& rpBox, void* pPara )
//STRIP001 {
//STRIP001  BOOL bRet = TRUE;
//STRIP001  if( rpBox->GetTabLines().Count() )
//STRIP001  {
//STRIP001      for( USHORT n = 0, nLines = rpBox->GetTabLines().Count();
//STRIP001              n < nLines && bRet; ++n )
//STRIP001      {
//STRIP001          const SwTableLine* pLine = rpBox->GetTabLines()[ n ];
//STRIP001          bRet = lcl_GCBorder_ChkBoxBrd_L( pLine, pPara );
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      _SwGCBorder_BoxBrd* pBPara = (_SwGCBorder_BoxBrd*)pPara;
//STRIP001      bRet = pBPara->CheckLeftBorderOfFormat( *rpBox->GetFrmFmt() );
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 BOOL lcl_GCBorder_GetLastBox_L( const SwTableLine*& rpLine, void* pPara )
//STRIP001 {
//STRIP001  const SwTableBoxes& rBoxes = rpLine->GetTabBoxes();
//STRIP001  const SwTableBox* pBox = rBoxes[ rBoxes.Count()-1 ];
//STRIP001  ::lcl_GCBorder_GetLastBox_B( pBox, pPara );
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 BOOL lcl_GCBorder_GetLastBox_B( const SwTableBox*& rpBox, void* pPara )
//STRIP001 {
//STRIP001  SwTableLines& rLines = (SwTableLines&)rpBox->GetTabLines();
//STRIP001  if( rLines.Count() )
//STRIP001      rLines.ForEach( &lcl_GCBorder_GetLastBox_L, pPara );
//STRIP001  else
//STRIP001      ((SwTableBoxes*)pPara)->Insert( rpBox, ((SwTableBoxes*)pPara)->Count() );
//STRIP001  return TRUE;
//STRIP001 }

// suche das "Ende" der vorgegebene BorderLine. Returnt wird die "Layout"Pos!
//STRIP001 USHORT lcl_FindEndPosOfBorder( const SwCollectTblLineBoxes& rCollTLB,
//STRIP001                      const SvxBorderLine& rBrdLn, USHORT& rStt, BOOL bTop )
//STRIP001 {
//STRIP001  USHORT nPos, nLastPos = 0;
//STRIP001  for( USHORT nEnd = rCollTLB.Count(); rStt < nEnd; ++rStt )
//STRIP001  {
//STRIP001      const SfxPoolItem* pItem;
//STRIP001      const SvxBorderLine* pBrd;
//STRIP001      const SwTableBox& rBox = rCollTLB.GetBox( rStt, &nPos );
//STRIP001
//STRIP001      if( SFX_ITEM_SET != rBox.GetFrmFmt()->GetItemState(RES_BOX,TRUE, &pItem )
//STRIP001          || 0 == ( pBrd = GetLineTB( (SvxBoxItem*)pItem, bTop ))
//STRIP001          || !( *pBrd == rBrdLn ))
//STRIP001          break;
//STRIP001      nLastPos = nPos;
//STRIP001  }
//STRIP001  return nLastPos;
//STRIP001 }

//STRIP001 inline const SvxBorderLine* lcl_GCBorder_GetBorder( const SwTableBox& rBox,
//STRIP001                                              BOOL bTop,
//STRIP001                                              const SfxPoolItem** ppItem )
//STRIP001 {
//STRIP001  return SFX_ITEM_SET == rBox.GetFrmFmt()->GetItemState( RES_BOX, TRUE, ppItem )
//STRIP001          ? GetLineTB( (SvxBoxItem*)*ppItem, bTop )
//STRIP001          : 0;
//STRIP001 }

//STRIP001 void lcl_GCBorder_DelBorder( const SwCollectTblLineBoxes& rCollTLB,
//STRIP001                              USHORT& rStt, BOOL bTop,
//STRIP001                              const SvxBorderLine& rLine,
//STRIP001                              const SfxPoolItem* pItem,
//STRIP001                              USHORT nEndPos,
//STRIP001                              SwShareBoxFmts* pShareFmts )
//STRIP001 {
//STRIP001  SwTableBox* pBox = (SwTableBox*)&rCollTLB.GetBox( rStt );
//STRIP001  USHORT nNextPos;
//STRIP001  const SvxBorderLine* pLn = &rLine;
//STRIP001
//STRIP001  do {
//STRIP001      if( pLn && *pLn == rLine )
//STRIP001      {
//STRIP001          SvxBoxItem aBox( *(SvxBoxItem*)pItem );
//STRIP001          if( bTop )
//STRIP001              aBox.SetLine( 0, BOX_LINE_TOP );
//STRIP001          else
//STRIP001              aBox.SetLine( 0, BOX_LINE_BOTTOM );
//STRIP001
//STRIP001          if( pShareFmts )
//STRIP001              pShareFmts->SetAttr( *pBox, aBox );
//STRIP001          else
//STRIP001              pBox->ClaimFrmFmt()->SetAttr( aBox );
//STRIP001      }
//STRIP001
//STRIP001      if( ++rStt >= rCollTLB.Count() )
//STRIP001          break;
//STRIP001
//STRIP001      pBox = (SwTableBox*)&rCollTLB.GetBox( rStt, &nNextPos );
//STRIP001      if( nNextPos > nEndPos )
//STRIP001          break;
//STRIP001
//STRIP001      pLn = lcl_GCBorder_GetBorder( *pBox, bTop, &pItem );
//STRIP001
//STRIP001  } while( TRUE );
//STRIP001 }


//STRIP001 BOOL lcl_GC_Line_Border( const SwTableLine*& rpLine, void* pPara )
//STRIP001 {
//STRIP001  _SwGCLineBorder* pGCPara = (_SwGCLineBorder*)pPara;
//STRIP001
//STRIP001  // zuerst die rechte Kante mit der linken Kante der naechsten Box
//STRIP001  // innerhalb dieser Line
//STRIP001  {
//STRIP001      _SwGCBorder_BoxBrd aBPara;
//STRIP001      const SvxBorderLine* pBrd;
//STRIP001      const SfxPoolItem* pItem;
//STRIP001      const SwTableBoxes& rBoxes = rpLine->GetTabBoxes();
//STRIP001      for( USHORT n = 0, nBoxes = rBoxes.Count() - 1; n < nBoxes; ++n )
//STRIP001      {
//STRIP001          SwTableBoxes aBoxes;
//STRIP001          {
//STRIP001              const SwTableBox* pBox = rBoxes[ n ];
//STRIP001              if( pBox->GetSttNd() )
//STRIP001                  aBoxes.Insert( pBox, 0 );
//STRIP001              else
//STRIP001                  lcl_GCBorder_GetLastBox_B( pBox, &aBoxes );
//STRIP001          }
//STRIP001
//STRIP001          SwTableBox* pBox;
//STRIP001          for( USHORT i = aBoxes.Count(); i; )
//STRIP001              if( SFX_ITEM_SET == (pBox = aBoxes[ --i ])->GetFrmFmt()->
//STRIP001                  GetItemState( RES_BOX, TRUE, &pItem ) &&
//STRIP001                  0 != ( pBrd = ((SvxBoxItem*)pItem)->GetRight() ) )
//STRIP001              {
//STRIP001                  aBPara.SetBorder( *pBrd );
//STRIP001                  const SwTableBox* pNextBox = rBoxes[n+1];
//STRIP001                  if( lcl_GCBorder_ChkBoxBrd_B( pNextBox, &aBPara ) &&
//STRIP001                      aBPara.IsAnyBorderFound() )
//STRIP001                  {
//STRIP001                      SvxBoxItem aBox( *(SvxBoxItem*)pItem );
//STRIP001                      aBox.SetLine( 0, BOX_LINE_RIGHT );
//STRIP001                      if( pGCPara->pShareFmts )
//STRIP001                          pGCPara->pShareFmts->SetAttr( *pBox, aBox );
//STRIP001                      else
//STRIP001                          pBox->ClaimFrmFmt()->SetAttr( aBox );
//STRIP001                  }
//STRIP001              }
//STRIP001
//STRIP001          aBoxes.Remove( 0, aBoxes.Count() );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // und jetzt die eigene untere Kante mit der nachfolgenden oberen Kante
//STRIP001  if( !pGCPara->IsLastLine() )
//STRIP001  {
//STRIP001      SwCollectTblLineBoxes aBottom( FALSE );
//STRIP001      SwCollectTblLineBoxes aTop( TRUE );
//STRIP001
//STRIP001      ::lcl_Line_CollectBox( rpLine, &aBottom );
//STRIP001
//STRIP001      const SwTableLine* pNextLine = (*pGCPara->pLines)[ pGCPara->nLinePos+1 ];
//STRIP001      ::lcl_Line_CollectBox( pNextLine, &aTop );
//STRIP001
//STRIP001      // dann entferne mal alle "doppelten" gleichen Lines
//STRIP001      USHORT nBtmPos, nTopPos,
//STRIP001              nSttBtm = 0, nSttTop = 0,
//STRIP001              nEndBtm = aBottom.Count(), nEndTop = aTop.Count();
//STRIP001
//STRIP001      const SwTableBox *pBtmBox = &aBottom.GetBox( nSttBtm++, &nBtmPos ),
//STRIP001                       *pTopBox = &aTop.GetBox( nSttTop++, &nTopPos );
//STRIP001      const SfxPoolItem *pBtmItem, *pTopItem;
//STRIP001      const SvxBorderLine *pBtmLine, *pTopLine;
//STRIP001      BOOL bGetTopItem = TRUE, bGetBtmItem = TRUE;
//STRIP001
//STRIP001      do {
//STRIP001          if( bGetBtmItem )
//STRIP001              pBtmLine = lcl_GCBorder_GetBorder( *pBtmBox, FALSE, &pBtmItem );
//STRIP001          if( bGetTopItem )
//STRIP001              pTopLine = lcl_GCBorder_GetBorder( *pTopBox, TRUE, &pTopItem );
//STRIP001
//STRIP001          if( pTopLine && pBtmLine && *pTopLine == *pBtmLine )
//STRIP001          {
//STRIP001              // dann kann einer entfernt werden, aber welche?
//STRIP001              USHORT nSavSttBtm = nSttBtm, nSavSttTop = nSttTop;
//STRIP001              USHORT nBtmEndPos = ::lcl_FindEndPosOfBorder( aBottom,
//STRIP001                                              *pTopLine, nSttBtm, FALSE );
//STRIP001              if( !nBtmEndPos ) nBtmEndPos = nBtmPos;
//STRIP001              USHORT nTopEndPos = ::lcl_FindEndPosOfBorder( aTop,
//STRIP001                                              *pTopLine, nSttTop, TRUE );
//STRIP001              if( !nTopEndPos ) nTopEndPos = nTopPos;
//STRIP001
//STRIP001
//STRIP001              if( nTopEndPos <= nBtmEndPos )
//STRIP001              {
//STRIP001                  // dann die TopBorder bis zur BottomEndPos loeschen
//STRIP001                  nSttTop = nSavSttTop;
//STRIP001                  if( nTopPos <= nBtmEndPos )
//STRIP001                      lcl_GCBorder_DelBorder( aTop, --nSttTop, TRUE,
//STRIP001                                          *pBtmLine, pTopItem, nBtmEndPos,
//STRIP001                                          pGCPara->pShareFmts );
//STRIP001                  else
//STRIP001                      nSttBtm = nSavSttBtm;
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  // sonst die BottomBorder bis zur TopEndPos loeschen
//STRIP001                  nSttBtm = nSavSttBtm;
//STRIP001                  if( nBtmPos <= nTopEndPos )
//STRIP001                      lcl_GCBorder_DelBorder( aBottom, --nSttBtm, FALSE,
//STRIP001                                          *pTopLine, pBtmItem, nTopEndPos,
//STRIP001                                          pGCPara->pShareFmts );
//STRIP001                  else
//STRIP001                      nSttTop = nSavSttTop;
//STRIP001              }
//STRIP001              nTopPos = nBtmPos;
//STRIP001          }
//STRIP001
//STRIP001          if( nTopPos == nBtmPos )
//STRIP001          {
//STRIP001              if( nSttBtm >= nEndBtm || nSttTop >= nEndTop )
//STRIP001                  break;
//STRIP001
//STRIP001              pBtmBox = &aBottom.GetBox( nSttBtm++, &nBtmPos );
//STRIP001              pTopBox = &aTop.GetBox( nSttTop++, &nTopPos );
//STRIP001              bGetTopItem = bGetBtmItem = TRUE;
//STRIP001          }
//STRIP001          else if( nTopPos < nBtmPos )
//STRIP001          {
//STRIP001              if( nSttTop >= nEndTop )
//STRIP001                  break;
//STRIP001              pTopBox = &aTop.GetBox( nSttTop++, &nTopPos );
//STRIP001              bGetTopItem = TRUE;
//STRIP001              bGetBtmItem = FALSE;
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              if( nSttBtm >= nEndBtm )
//STRIP001                  break;
//STRIP001              pBtmBox = &aBottom.GetBox( nSttBtm++, &nBtmPos );
//STRIP001              bGetTopItem = FALSE;
//STRIP001              bGetBtmItem = TRUE;
//STRIP001          }
//STRIP001
//STRIP001      } while( TRUE );
//STRIP001  }
//STRIP001
//STRIP001  ((SwTableLine*)rpLine)->GetTabBoxes().ForEach( &lcl_GC_Box_Border, pPara );
//STRIP001
//STRIP001  ++pGCPara->nLinePos;
//STRIP001
//STRIP001  return TRUE;
//STRIP001 }


//STRIP001 BOOL lcl_GC_Box_Border( const SwTableBox*& rpBox, void* pPara )
//STRIP001 {
//STRIP001  if( rpBox->GetTabLines().Count() )
//STRIP001  {
//STRIP001      _SwGCLineBorder aPara( *rpBox );
//STRIP001      aPara.pShareFmts = ((_SwGCLineBorder*)pPara)->pShareFmts;
//STRIP001      ((SwTableBox*)rpBox)->GetTabLines().ForEach( &lcl_GC_Line_Border, &aPara );
//STRIP001  }
//STRIP001  return TRUE;
//STRIP001 }


//STRIP001 void SwTable::GCBorderLines()
//STRIP001 {
//STRIP001  // alle doppleten Borderlines benachbarter Tabellen-Content-Boxen
//STRIP001  // entfernen. Und zwar wird versucht, die Struktur unserer default
//STRIP001  // Border wiederherzustellen, die wie folgt aussieht:
//STRIP001  //
//STRIP001  //   +-- +--+
//STRIP001  //   |   |  |
//STRIP001  //   +-- +--+
//STRIP001  //
//STRIP001  //   |   |  |
//STRIP001  //   +-- +--+
//STRIP001
//STRIP001  SwShareBoxFmts aShareFmts;
//STRIP001  _SwGCLineBorder aPara( *this );
//STRIP001  aPara.pShareFmts = &aShareFmts;
//STRIP001  GetTabLines().ForEach( &lcl_GC_Line_Border, &aPara );
//STRIP001 }


/*  */

struct _GCLinePara
{
    SwTableLines* pLns;
    SwShareBoxFmts* pShareFmts;

    _GCLinePara( SwTableLines& rLns, _GCLinePara* pPara = 0 )
        : pLns( &rLns ), pShareFmts( pPara ? pPara->pShareFmts : 0 )
    {}
};

/*N*/ BOOL lcl_MergeGCBox( const SwTableBox*& rpTblBox, void* pPara )
/*N*/ {
/*N*/   SwTableBox*& rpBox = (SwTableBox*&)rpTblBox;
/*N*/   USHORT n, nLen = rpBox->GetTabLines().Count();
/*N*/   if( nLen )
/*N*/   {
/*N*/       // ACHTUNG: die Anzahl der Lines kann sich aendern!
/*N*/       _GCLinePara aPara( rpBox->GetTabLines(), (_GCLinePara*)pPara );
/*N*/       for( n = 0; n < rpBox->GetTabLines().Count() &&
/*N*/           lcl_MergeGCLine( *(rpBox->GetTabLines().GetData() + n), &aPara );
/*N*/           ++n )
/*N*/           ;
/*N*/
/*N*/       if( 1 == rpBox->GetTabLines().Count() )
/*N*/       {
/*N*/           // Box mit einer Line, dann verschiebe alle Boxen der Line
/*N*/           // hinter diese Box in der Parent-Line und loesche diese Box
/*?*/           SwTableLine* pInsLine = rpBox->GetUpper();
/*?*/           SwTableLine* pCpyLine = rpBox->GetTabLines()[0];
/*?*/           USHORT nInsPos = pInsLine->GetTabBoxes().C40_GETPOS( SwTableBox, rpBox );
/*?*/           for( n = 0; n < pCpyLine->GetTabBoxes().Count(); ++n )
/*?*/               pCpyLine->GetTabBoxes()[n]->SetUpper( pInsLine );
/*?*/
/*?*/           pInsLine->GetTabBoxes().Insert( &pCpyLine->GetTabBoxes(), nInsPos+1 );
/*?*/           pCpyLine->GetTabBoxes().Remove( 0, n );
/*?*/           // loesche alte die Box mit der Line
/*?*/           pInsLine->GetTabBoxes().DeleteAndDestroy( nInsPos );
/*?*/
/*?*/           return FALSE;       // neu aufsetzen
/*N*/       }
/*N*/   }
/*N*/   return TRUE;
/*N*/ }

/*N*/ BOOL lcl_MergeGCLine( const SwTableLine*& rpLine, void* pPara )
/*N*/ {
/*N*/   SwTableLine* pLn = (SwTableLine*)rpLine;
/*N*/   USHORT nLen = pLn->GetTabBoxes().Count();
/*N*/   if( nLen )
/*N*/   {
/*N*/       _GCLinePara* pGCPara = (_GCLinePara*)pPara;
/*N*/       while( 1 == nLen )
/*N*/       {
/*N*/           // es gibt eine Box mit Lines
/*N*/           SwTableBox* pBox = pLn->GetTabBoxes()[0];
/*N*/           if( !pBox->GetTabLines().Count() )
/*N*/               break;
/*N*/
/*N*/           SwTableLine* pLine = pBox->GetTabLines()[0];
/*N*/
/*N*/           // pLine wird zu der aktuellen, also der rpLine,
/*N*/           // die restlichen werden ins LinesArray hinter der akt.
/*N*/           // verschoben.
/*N*/           // Das LinesArray ist im pPara!
/*N*/           nLen = pBox->GetTabLines().Count();
/*N*/
/*N*/           SwTableLines& rLns = *pGCPara->pLns;
/*N*/           const SwTableLine* pTmp = pLn;
/*N*/           USHORT nInsPos = rLns.GetPos( pTmp );
/*N*/           ASSERT( USHRT_MAX != nInsPos, "Line nicht gefunden!" );
/*N*/
/*N*/           SwTableBox* pUpper = pLn->GetUpper();
/*N*/
/*N*/           rLns.Remove( nInsPos, 1 );      // die Line dem aus Array loeschen
/*N*/           rLns.Insert( &pBox->GetTabLines(), nInsPos );
/*N*/
/*N*/           // JP 31.03.99: Bug 60000 - die Attribute der zu loeschenden
/*N*/           // Line an die "eingefuegten" uebertragen
/*N*/           const SfxPoolItem* pItem;
/*N*/           if( SFX_ITEM_SET == pLn->GetFrmFmt()->GetItemState(
/*N*/                                   RES_BACKGROUND, TRUE, &pItem ))
/*N*/           {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/                SwTableLines& rBoxLns = pBox->GetTabLines();
//STRIP001 /*?*/                for( USHORT nLns = 0; nLns < nLen; ++nLns )
//STRIP001 /*?*/                    if( SFX_ITEM_SET != rBoxLns[ nLns ]->GetFrmFmt()->
//STRIP001 /*?*/                            GetItemState( RES_BACKGROUND, TRUE ))
//STRIP001 /*?*/                        pGCPara->pShareFmts->SetAttr( *rBoxLns[ nLns ], *pItem );
/*N*/           }
/*N*/
/*N*/           pBox->GetTabLines().Remove( 0, nLen );  // Lines aus Array loeschen
/*N*/
/*N*/           delete pLn;
/*N*/
/*N*/           // Abhaengigkeit neu setzen
/*N*/           while( nLen-- )
/*N*/               rLns[ nInsPos++ ]->SetUpper( pUpper );
/*N*/
/*N*/           pLn = pLine;                        // und neu setzen
/*N*/           nLen = pLn->GetTabBoxes().Count();
/*N*/       }
/*N*/
/*N*/       // ACHTUNG: die Anzahl der Boxen kann sich aendern!
/*N*/       for( nLen = 0; nLen < pLn->GetTabBoxes().Count(); ++nLen )
/*N*/           if( !lcl_MergeGCBox( *(pLn->GetTabBoxes().GetData() + nLen ), pPara ))
/*N*/               --nLen;
/*N*/   }
/*N*/   return TRUE;
/*N*/ }

        // Struktur ein wenig aufraeumen
/*N*/ void SwTable::GCLines()
/*N*/ {
/*N*/   // ACHTUNG: die Anzahl der Lines kann sich aendern!
/*N*/   _GCLinePara aPara( GetTabLines() );
/*N*/   SwShareBoxFmts aShareFmts;
/*N*/   aPara.pShareFmts = &aShareFmts;
/*N*/   for( USHORT n = 0; n < GetTabLines().Count() &&
/*N*/           lcl_MergeGCLine( *(GetTabLines().GetData() + n ), &aPara ); ++n )
/*N*/       ;
/*N*/ }


}
