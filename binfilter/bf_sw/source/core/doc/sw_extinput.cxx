/*************************************************************************
 *
 *  $RCSfile: sw_extinput.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 17:10:20 $
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

// auto strip #ifndef _HINTIDS_HXX
// auto strip #include <hintids.hxx>
// auto strip #endif

// auto strip #ifndef _SV_KEYCODES_HXX
// auto strip #include <vcl/keycodes.hxx>
// auto strip #endif
// auto strip #ifndef _VCL_CMDEVT_HXX
// auto strip #include <vcl/cmdevt.hxx>
// auto strip #endif

#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif
#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _EXTINPUT_HXX
#include <extinput.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
// auto strip #ifndef _INDEX_HXX
// auto strip #include <index.hxx>
// auto strip #endif
// auto strip #ifndef _NDTXT_HXX
// auto strip #include <ndtxt.hxx>
// auto strip #endif
// auto strip #ifndef _TXTFRM_HXX
// auto strip #include <txtfrm.hxx>
// auto strip #endif
// auto strip #ifndef _HINTS_HXX
// auto strip #include <hints.hxx>
// auto strip #endif
// auto strip #ifndef _SWUNDO_HXX
// auto strip #include <swundo.hxx>
// auto strip #endif
namespace binfilter {


//STRIP001 SwExtTextInput::SwExtTextInput( const SwPaM& rPam, Ring* pRing )
//STRIP001  : SwPaM( *rPam.GetPoint(), (SwPaM*)pRing )
//STRIP001 {
//STRIP001  bIsOverwriteCursor = FALSE;
//STRIP001  bInsText = TRUE;
//STRIP001 }

//STRIP001 SwExtTextInput::~SwExtTextInput()
//STRIP001 {
//STRIP001  SwTxtNode* pTNd = GetPoint()->nNode.GetNode().GetTxtNode();
//STRIP001  if( pTNd )
//STRIP001  {
//STRIP001      SwIndex& rIdx = GetPoint()->nContent;
//STRIP001      xub_StrLen nSttCnt = rIdx.GetIndex(),
//STRIP001                 nEndCnt = GetMark()->nContent.GetIndex();
//STRIP001      if( nEndCnt != nSttCnt )
//STRIP001      {
//STRIP001          if( nEndCnt < nSttCnt )
//STRIP001          {
//STRIP001              xub_StrLen n = nEndCnt; nEndCnt = nSttCnt; nSttCnt = n;
//STRIP001          }
//STRIP001
//STRIP001          // damit Undo / Redlining usw. richtig funktioniert,
//STRIP001          // muss ueber die Doc-Schnittstellen gegangen werden !!!
//STRIP001          SwDoc* pDoc = GetDoc();
//STRIP001          rIdx = nSttCnt;
//STRIP001          String sTxt( pTNd->GetTxt().Copy( nSttCnt, nEndCnt - nSttCnt ));
//STRIP001          if( bIsOverwriteCursor && sOverwriteText.Len() )
//STRIP001          {
//STRIP001              xub_StrLen nLen = sTxt.Len();
//STRIP001              if( nLen > sOverwriteText.Len() )
//STRIP001              {
//STRIP001                  rIdx += sOverwriteText.Len();
//STRIP001                  pTNd->Erase( rIdx, nLen - sOverwriteText.Len() );
//STRIP001                  rIdx = nSttCnt;
//STRIP001                  pTNd->Replace( rIdx, sOverwriteText.Len(),
//STRIP001                                          sOverwriteText );
//STRIP001                  if( bInsText )
//STRIP001                  {
//STRIP001                      rIdx = nSttCnt;
//STRIP001                      pDoc->StartUndo( UNDO_OVERWRITE );
//STRIP001                      pDoc->Overwrite( *this, sTxt.Copy( 0,
//STRIP001                                                  sOverwriteText.Len() ));
//STRIP001                      pDoc->Insert( *this, sTxt.Copy( sOverwriteText.Len() ));
//STRIP001                      pDoc->EndUndo( UNDO_OVERWRITE );
//STRIP001                  }
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  pTNd->Replace( rIdx, nLen, sOverwriteText.Copy( 0, nLen ));
//STRIP001                  if( bInsText )
//STRIP001                  {
//STRIP001                      rIdx = nSttCnt;
//STRIP001                      pDoc->Overwrite( *this, sTxt );
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              pTNd->Erase( rIdx, nEndCnt - nSttCnt );
//STRIP001
//STRIP001              if( bInsText )
//STRIP001                  pDoc->Insert( *this, sTxt );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void SwExtTextInput::SetInputData( const CommandExtTextInputData& rData )
//STRIP001 {
//STRIP001  SwTxtNode* pTNd = GetPoint()->nNode.GetNode().GetTxtNode();
//STRIP001  if( pTNd )
//STRIP001  {
//STRIP001      xub_StrLen nSttCnt = GetPoint()->nContent.GetIndex(),
//STRIP001                  nEndCnt = GetMark()->nContent.GetIndex();
//STRIP001      if( nEndCnt < nSttCnt )
//STRIP001      {
//STRIP001          xub_StrLen n = nEndCnt; nEndCnt = nSttCnt; nSttCnt = n;
//STRIP001      }
//STRIP001
//STRIP001      SwIndex aIdx( pTNd, nSttCnt );
//STRIP001      const String& rNewStr = rData.GetText();
//STRIP001
//STRIP001      if( bIsOverwriteCursor && sOverwriteText.Len() )
//STRIP001      {
//STRIP001          xub_StrLen nReplace = nEndCnt - nSttCnt;
//STRIP001          if( rNewStr.Len() < nReplace )
//STRIP001          {
//STRIP001              // then we must insert from the saved original text
//STRIP001              // some characters
//STRIP001              nReplace -= rNewStr.Len();
//STRIP001              aIdx += rNewStr.Len();
//STRIP001              pTNd->Replace( aIdx, nReplace,
//STRIP001                          sOverwriteText.Copy( rNewStr.Len(), nReplace ));
//STRIP001              aIdx = nSttCnt;
//STRIP001              nReplace = rNewStr.Len();
//STRIP001          }
//STRIP001          else if( sOverwriteText.Len() < nReplace )
//STRIP001          {
//STRIP001              nReplace -= sOverwriteText.Len();
//STRIP001              aIdx += sOverwriteText.Len();
//STRIP001              pTNd->Erase( aIdx, nReplace );
//STRIP001              aIdx = nSttCnt;
//STRIP001              nReplace = sOverwriteText.Len();
//STRIP001          }
//STRIP001          else if( (nReplace = sOverwriteText.Len()) > rNewStr.Len() )
//STRIP001              nReplace = rNewStr.Len();
//STRIP001
//STRIP001          pTNd->Replace( aIdx, nReplace, rNewStr );
//STRIP001          if( !HasMark() )
//STRIP001              SetMark();
//STRIP001          GetMark()->nContent = aIdx;
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          if( nSttCnt < nEndCnt )
//STRIP001              pTNd->Erase( aIdx, nEndCnt - nSttCnt );
//STRIP001
//STRIP001          pTNd->Insert( rNewStr, aIdx, INS_EMPTYEXPAND );
//STRIP001          if( !HasMark() )
//STRIP001              SetMark();
//STRIP001      }
//STRIP001
//STRIP001      GetPoint()->nContent = nSttCnt;
//STRIP001
//STRIP001      if( aAttrs.Count() )
//STRIP001          aAttrs.Remove( 0, aAttrs.Count() );
//STRIP001      if( rData.GetTextAttr() )
//STRIP001          aAttrs.Insert( rData.GetTextAttr(), rData.GetText().Len(), 0 );
//STRIP001  }
//STRIP001 }

//STRIP001 void SwExtTextInput::SetFontForPos( USHORT nPos, Font& rFont )
//STRIP001 {
//STRIP001 }

//STRIP001 void SwExtTextInput::InvalidateRange()       // das Layout anstossen
//STRIP001 {
//STRIP001  ULONG nEndNd = GetMark()->nNode.GetIndex(),
//STRIP001          nSttNd = GetPoint()->nNode.GetIndex();
//STRIP001  xub_StrLen nEndCnt = GetMark()->nContent.GetIndex(),
//STRIP001              nSttCnt = GetPoint()->nContent.GetIndex();
//STRIP001
//STRIP001  if( nSttNd > nEndNd || ( nSttNd == nEndNd && nSttCnt > nEndCnt ))
//STRIP001  {
//STRIP001      ULONG nTmp = nSttNd; nSttNd = nEndNd; nEndNd = nTmp;
//STRIP001      nTmp = nSttCnt; nSttCnt = nEndCnt; nEndCnt = (xub_StrLen)nTmp;
//STRIP001  }
//STRIP001
//STRIP001  SwUpdateAttr aHt( 0, 0, RES_FMT_CHG );
//STRIP001  SwNodes& rNds = GetDoc()->GetNodes();
//STRIP001  SwNode* pNd;
//STRIP001  for( ULONG n = nSttNd; n <= nEndNd; ++n )
//STRIP001      if( ND_TEXTNODE == ( pNd = rNds[ n ] )->GetNodeType() )
//STRIP001      {
//STRIP001          aHt.nStart = n == nSttNd ? nSttCnt : 0;
//STRIP001          aHt.nEnd = n == nEndNd ? nEndCnt : ((SwTxtNode*)pNd)->GetTxt().Len();
//STRIP001          ((SwTxtNode*)pNd)->Modify( &aHt, &aHt );
//STRIP001      }
//STRIP001 }

//STRIP001 void SwExtTextInput::SetOverwriteCursor( BOOL bFlag )
//STRIP001 {
//STRIP001  bIsOverwriteCursor = bFlag;
//STRIP001
//STRIP001  SwTxtNode* pTNd;
//STRIP001  if( bIsOverwriteCursor &&
//STRIP001      0 != (pTNd = GetPoint()->nNode.GetNode().GetTxtNode()) )
//STRIP001  {
//STRIP001      xub_StrLen nSttCnt = GetPoint()->nContent.GetIndex(),
//STRIP001                  nEndCnt = GetMark()->nContent.GetIndex();
//STRIP001      sOverwriteText = pTNd->GetTxt().Copy( nEndCnt < nSttCnt ? nEndCnt
//STRIP001                                                              : nSttCnt );
//STRIP001      if( sOverwriteText.Len() )
//STRIP001      {
//STRIP001          xub_StrLen nInWrdAttrPos = sOverwriteText.Search( CH_TXTATR_INWORD ),
//STRIP001                  nWrdAttrPos = sOverwriteText.Search( CH_TXTATR_BREAKWORD );
//STRIP001          if( nWrdAttrPos < nInWrdAttrPos )
//STRIP001              nInWrdAttrPos = nWrdAttrPos;
//STRIP001          if( STRING_NOTFOUND != nInWrdAttrPos )
//STRIP001              sOverwriteText.Erase( nInWrdAttrPos );
//STRIP001      }
//STRIP001  }
//STRIP001 }

// die Doc Schnittstellen:

//STRIP001 SwExtTextInput* SwDoc::CreateExtTextInput( const SwPaM& rPam )
//STRIP001 {
//STRIP001  SwExtTextInput* pNew = new SwExtTextInput( rPam, pExtInputRing );
//STRIP001  if( !pExtInputRing )
//STRIP001      pExtInputRing = pNew;
//STRIP001  pNew->SetMark();
//STRIP001  return pNew;
//STRIP001 }

//STRIP001 void SwDoc::DeleteExtTextInput( SwExtTextInput* pDel )
//STRIP001 {
//STRIP001  if( pDel == pExtInputRing )
//STRIP001  {
//STRIP001      if( pDel->GetNext() != pExtInputRing )
//STRIP001          pExtInputRing = (SwPaM*)pDel->GetNext();
//STRIP001      else
//STRIP001          pExtInputRing = 0;
//STRIP001  }
//STRIP001  delete pDel;
//STRIP001 }

/*N*/ SwExtTextInput* SwDoc::GetExtTextInput( const SwNode& rNd,
/*N*/                                       xub_StrLen nCntntPos ) const
/*N*/ {
/*N*/   SwExtTextInput* pRet = 0;
/*N*/   if( pExtInputRing )
/*N*/   {
/*?*/       ULONG nNdIdx = rNd.GetIndex();
/*?*/       SwExtTextInput* pTmp = (SwExtTextInput*)pExtInputRing;
/*?*/       do {
/*?*/           ULONG nPt = pTmp->GetPoint()->nNode.GetIndex(),
/*?*/                 nMk = pTmp->GetMark()->nNode.GetIndex();
/*?*/           xub_StrLen nPtCnt = pTmp->GetPoint()->nContent.GetIndex(),
/*?*/                      nMkCnt = pTmp->GetMark()->nContent.GetIndex();
/*?*/
/*?*/           if( nPt < nMk || ( nPt == nMk && nPtCnt < nMkCnt ))
/*?*/           {
/*?*/               ULONG nTmp = nMk; nMk = nPt; nPt = nTmp;
/*?*/               nTmp = nMkCnt; nMkCnt = nPtCnt; nPtCnt = (xub_StrLen)nTmp;
/*?*/           }
/*?*/
/*?*/           if( nMk <= nNdIdx && nNdIdx <= nPt &&
/*?*/               ( STRING_NOTFOUND == nCntntPos ||
/*?*/                   ( nMkCnt <= nCntntPos && nCntntPos <= nPtCnt )))
/*?*/           {
/*?*/               pRet = pTmp;
/*?*/               break;
/*?*/           }
/*?*/       } while( pExtInputRing != (pTmp = (SwExtTextInput*)pExtInputRing ) );
/*N*/   }
/*N*/   return pRet;
/*N*/ }

//STRIP001 SwExtTextInput* SwDoc::GetExtTextInput() const
//STRIP001 {
//STRIP001  ASSERT( !pExtInputRing || pExtInputRing == pExtInputRing->GetNext(),
//STRIP001          "more then one InputEngine available" );
//STRIP001  return (SwExtTextInput*)pExtInputRing;
//STRIP001 }


}
