/*************************************************************************
 *
 *  $RCSfile: sw_ftnidx.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 17:10:45 $
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

#ifndef _TXTFTN_HXX
#include <txtftn.hxx>
#endif
#ifndef _FMTFTN_HXX
#include <fmtftn.hxx>
#endif
#ifndef _FTNINFO_HXX
#include <ftninfo.hxx>
#endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif
// auto strip #ifndef _ERRHDL_HXX
// auto strip #include <errhdl.hxx>
// auto strip #endif

#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _FTNIDX_HXX
#include <ftnidx.hxx>
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>
#endif
// auto strip #ifndef _FMTCOL_HXX
// auto strip #include <fmtcol.hxx>
// auto strip #endif
#ifndef _NDINDEX_HXX
#include <ndindex.hxx>
#endif
#ifndef _SECTION_HXX
#include <section.hxx>
#endif
#ifndef _FMTFTNTX_HXX
#include <fmtftntx.hxx>
#endif
// auto strip #ifndef _ROOTFRM_HXX
// auto strip #include <rootfrm.hxx>
// auto strip #endif
namespace binfilter {


/*?*/ _SV_IMPL_SORTAR_ALG( _SwFtnIdxs, SwTxtFtnPtr )
/*?*/ BOOL _SwFtnIdxs::Seek_Entry( const SwTxtFtnPtr rSrch, USHORT* pFndPos ) const
/*?*/ {
/*?*/   ULONG nIdx = _SwTxtFtn_GetIndex( rSrch );
/*?*/   xub_StrLen nCntIdx = *rSrch->GetStart();
/*?*/
/*?*/   register USHORT nO = Count(), nM, nU = 0;
/*?*/   if( nO > 0 )
/*?*/   {
/*?*/       nO--;
/*?*/       while( nU <= nO )
/*?*/       {
/*?*/           nM = nU + ( nO - nU ) / 2;
/*?*/           ULONG nFndIdx = _SwTxtFtn_GetIndex( (*this)[ nM ] );
/*?*/           if( nFndIdx == nIdx && *(*this)[ nM ]->GetStart() == nCntIdx )
/*?*/           {
/*?*/               if( pFndPos )
/*?*/                   *pFndPos = nM;
/*?*/               return TRUE;
/*?*/           }
/*?*/           else if( nFndIdx < nIdx ||
/*?*/               (nFndIdx == nIdx && *(*this)[ nM ]->GetStart() < nCntIdx ))
/*?*/               nU = nM + 1;
/*?*/           else if( nM == 0 )
/*?*/           {
/*?*/               if( pFndPos )
/*?*/                   *pFndPos = nU;
/*?*/               return FALSE;
/*?*/           }
/*?*/           else
/*?*/               nO = nM - 1;
/*?*/       }
/*?*/   }
/*?*/   if( pFndPos )
/*?*/       *pFndPos = nU;
/*?*/   return FALSE;
/*?*/ }


/*N*/ void SwFtnIdxs::UpdateFtn( const SwNodeIndex& rStt )
/*N*/ {
/*N*/   if( !Count() )
/*N*/       return;
/*N*/
/*N*/   // besorge erstmal das Nodes-Array ueber den StartIndex der ersten Fussnote
/*N*/   SwDoc* pDoc = rStt.GetNode().GetDoc();
/*N*/   if( pDoc->IsInReading() )
/*N*/       return ;
/*N*/   SwTxtFtn* pTxtFtn;
/*N*/
/*N*/   const SwEndNoteInfo& rEndInfo = pDoc->GetEndNoteInfo();
/*N*/   const SwFtnInfo& rFtnInfo = pDoc->GetFtnInfo();
/*N*/
/*N*/   //Fuer normale Fussnoten werden Chapter- und Dokumentweise Nummerierung
/*N*/   //getrennt behandelt. Fuer Endnoten gibt es nur die Dokumentweise
/*N*/   //Nummerierung.
/*N*/   if( FTNNUM_CHAPTER == rFtnInfo.eNum )
/*N*/   {
/*?*/       const SwOutlineNodes& rOutlNds = pDoc->GetNodes().GetOutLineNds();
/*?*/       const SwNode* pCapStt = &pDoc->GetNodes().GetEndOfExtras();
/*?*/       ULONG nCapEnd = pDoc->GetNodes().GetEndOfContent().GetIndex();
/*?*/       if( rOutlNds.Count() )
/*?*/       {
/*?*/           // suche den Start des Kapitels, in den rStt steht.
                USHORT n=0;
/*?*/           for( n = 0; n < rOutlNds.Count(); ++n )
/*?*/               if( rOutlNds[ n ]->GetIndex() > rStt.GetIndex() )
/*?*/                   break;      // gefunden
/*?*/               else if( !rOutlNds[ n ]->GetTxtNode()->GetTxtColl()->GetOutlineLevel() )
/*?*/                   pCapStt = rOutlNds[ n ];    // Start eines neuen Kapitels
/*?*/           // dann suche jetzt noch das Ende vom Bereich
/*?*/           for( ; n < rOutlNds.Count(); ++n )
/*?*/               if( !rOutlNds[ n ]->GetTxtNode()->GetTxtColl()->GetOutlineLevel() )
/*?*/               {
/*?*/                   nCapEnd = rOutlNds[ n ]->GetIndex();    // Ende des gefundenen Kapitels
/*?*/                   break;
/*?*/               }
/*?*/       }
/*?*/
/*?*/       USHORT nPos, nFtnNo = 1;
/*?*/       if( SeekEntry( *pCapStt, &nPos ) && nPos )
/*?*/       {
/*?*/           // gehe nach vorne bis der Index nicht mehr gleich ist
/*?*/           const SwNode* pCmpNd = &rStt.GetNode();
/*?*/           while( nPos && pCmpNd == &((*this)[ --nPos ]->GetTxtNode()) )
/*?*/               ;
/*?*/           ++nPos;
/*?*/       }
/*?*/
/*?*/       if( nPos == Count() )       // nichts gefunden
/*?*/           return;
/*?*/
/*?*/       if( !rOutlNds.Count() )
/*?*/           nFtnNo = nPos+1;
/*?*/
/*?*/       for( ; nPos < Count(); ++nPos )
/*?*/       {
/*?*/           pTxtFtn = (*this)[ nPos ];
/*?*/           if( pTxtFtn->GetTxtNode().GetIndex() >= nCapEnd )
/*?*/               break;
/*?*/
/*?*/           const SwFmtFtn &rFtn = pTxtFtn->GetFtn();
/*?*/           if( !rFtn.GetNumStr().Len() && !rFtn.IsEndNote() &&
/*?*/               !SwUpdFtnEndNtAtEnd::FindSectNdWithEndAttr( *pTxtFtn ))
/*?*/               pTxtFtn->SetNumber( rFtnInfo.nFtnOffset + nFtnNo++,
/*?*/                                   &rFtn.GetNumStr() );
/*?*/       }
/*N*/   }
/*N*/
/*N*/   SwUpdFtnEndNtAtEnd aNumArr;
/*N*/
/*N*/   // BOOL, damit hier auch bei Chapter-Einstellung die Endnoten
/*N*/   // durchlaufen.
/*N*/   const FASTBOOL bEndNoteOnly = FTNNUM_DOC != rFtnInfo.eNum;
/*N*/
/*N*/   USHORT nPos, nFtnNo = 1, nEndNo = 1;
/*N*/   ULONG nUpdNdIdx = rStt.GetIndex();
/*N*/   for( nPos = 0; nPos < Count(); ++nPos )
/*N*/   {
/*N*/       pTxtFtn = (*this)[ nPos ];
/*N*/       if( nUpdNdIdx <= pTxtFtn->GetTxtNode().GetIndex() )
/*N*/           break;
/*N*/
/*?*/       const SwFmtFtn &rFtn = pTxtFtn->GetFtn();
/*?*/       if( !rFtn.GetNumStr().Len() )
/*?*/       {
/*?*/           if( !aNumArr.ChkNumber( *pTxtFtn ) )
/*?*/           {
/*?*/               if( pTxtFtn->GetFtn().IsEndNote() )
/*?*/                   nEndNo++;
/*?*/               else
/*?*/                   nFtnNo++;
/*?*/           }
/*?*/       }
/*N*/   }
/*N*/
/*N*/   // ab nPos bei allen FootNotes die Array-Nummer setzen
/*N*/   for( ; nPos < Count(); ++nPos )
/*N*/   {
/*N*/       pTxtFtn = (*this)[ nPos ];
/*N*/       const SwFmtFtn &rFtn = pTxtFtn->GetFtn();
/*N*/       if( !rFtn.GetNumStr().Len() )
/*N*/       {
/*N*/           USHORT nSectNo = aNumArr.ChkNumber( *pTxtFtn );
/*N*/           if( !nSectNo && ( rFtn.IsEndNote() || !bEndNoteOnly ))
/*N*/               nSectNo = rFtn.IsEndNote()
/*N*/                           ? rEndInfo.nFtnOffset + nEndNo++
/*N*/                           : rFtnInfo.nFtnOffset + nFtnNo++;
/*N*/
/*N*/           if( nSectNo )
/*N*/           {
/*N*/               if( rFtn.IsEndNote() )
/*?*/                   pTxtFtn->SetNumber( nSectNo, &rFtn.GetNumStr() );
/*N*/               else
/*N*/                   pTxtFtn->SetNumber( nSectNo, &rFtn.GetNumStr() );
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   // Pageweise wird vom MA erfuellt !!
/*N*/ }


/*N*/ void SwFtnIdxs::UpdateAllFtn()
/*N*/ {
/*N*/   if( !Count() )
/*N*/       return;
/*N*/
/*N*/   // besorge erstmal das Nodes-Array ueber den StartIndex der
/*N*/   // ersten Fussnote
/*N*/   SwDoc* pDoc = (SwDoc*) (*this)[ 0 ]->GetTxtNode().GetDoc();
/*N*/   SwTxtFtn* pTxtFtn;
/*N*/   const SwEndNoteInfo& rEndInfo = pDoc->GetEndNoteInfo();
/*N*/   const SwFtnInfo& rFtnInfo = pDoc->GetFtnInfo();
/*N*/
/*N*/   SwUpdFtnEndNtAtEnd aNumArr;
/*N*/
/*N*/   //Fuer normale Fussnoten werden Chapter- und Dokumentweise Nummerierung
/*N*/   //getrennt behandelt. Fuer Endnoten gibt es nur die Dokumentweise
/*N*/   //Nummerierung.
/*N*/   if( FTNNUM_CHAPTER == rFtnInfo.eNum )
/*N*/   {
/*?*/       const SwOutlineNodes& rOutlNds = pDoc->GetNodes().GetOutLineNds();
/*?*/       USHORT nNo = 1,         // Nummer fuer die Fussnoten
/*?*/              nFtnIdx = 0;     // Index in das FtnIdx-Array
/*?*/       for( USHORT n = 0; n < rOutlNds.Count(); ++n )
/*?*/       {
/*?*/           if( !rOutlNds[ n ]->GetTxtNode()->GetTxtColl()->GetOutlineLevel() )
/*?*/           {
/*?*/               ULONG nCapStt = rOutlNds[ n ]->GetIndex();  // Start eines neuen Kapitels
/*?*/               for( ; nFtnIdx < Count(); ++nFtnIdx )
/*?*/               {
/*?*/                   pTxtFtn = (*this)[ nFtnIdx ];
/*?*/                   if( pTxtFtn->GetTxtNode().GetIndex() >= nCapStt )
/*?*/                       break;
/*?*/
/*?*/                   // Endnoten nur Dokumentweise
/*?*/                   const SwFmtFtn &rFtn = pTxtFtn->GetFtn();
/*?*/                   if( !rFtn.IsEndNote() && !rFtn.GetNumStr().Len() &&
/*?*/                       !SwUpdFtnEndNtAtEnd::FindSectNdWithEndAttr( *pTxtFtn ))
/*?*/                       pTxtFtn->SetNumber( rFtnInfo.nFtnOffset + nNo++,
/*?*/                                           &rFtn.GetNumStr() );
/*?*/               }
/*?*/               if( nFtnIdx >= Count() )
/*?*/                   break;          // ok alles geupdatet
/*?*/               nNo = 1;
/*?*/           }
/*?*/       }
/*?*/
/*?*/       for( nNo = 1; nFtnIdx < Count(); ++nFtnIdx )
/*?*/       {
/*?*/           //Endnoten nur Dokumentweise
/*?*/           pTxtFtn = (*this)[ nFtnIdx ];
/*?*/           const SwFmtFtn &rFtn = pTxtFtn->GetFtn();
/*?*/           if( !rFtn.IsEndNote() && !rFtn.GetNumStr().Len() &&
/*?*/               !SwUpdFtnEndNtAtEnd::FindSectNdWithEndAttr( *pTxtFtn ))
/*?*/               pTxtFtn->SetNumber( rFtnInfo.nFtnOffset + nNo++,
/*?*/                                   &rFtn.GetNumStr() );
/*?*/       }
/*?*/
/*N*/   }

    // BOOL, damit hier auch bei Chapter-Einstellung die Endnoten
    // durchlaufen.
/*N*/   const FASTBOOL bEndNoteOnly = FTNNUM_DOC != rFtnInfo.eNum;
/*N*/   USHORT nFtnNo = 0, nEndNo = 0;
/*N*/   for( USHORT nPos = 0; nPos < Count(); ++nPos )
/*N*/   {
/*N*/       pTxtFtn = (*this)[ nPos ];
/*N*/       const SwFmtFtn &rFtn = pTxtFtn->GetFtn();
/*N*/       if( !rFtn.GetNumStr().Len() )
/*N*/       {
/*?*/           USHORT nSectNo = aNumArr.ChkNumber( *pTxtFtn );
/*?*/           if( !nSectNo && ( rFtn.IsEndNote() || !bEndNoteOnly ))
/*?*/               nSectNo = rFtn.IsEndNote()
/*?*/                               ? rEndInfo.nFtnOffset + (++nEndNo)
/*?*/                               : rFtnInfo.nFtnOffset + (++nFtnNo);
/*?*/
/*?*/           if( nSectNo )
/*?*/           {
/*?*/               if( rFtn.IsEndNote() )
/*?*/                   pTxtFtn->SetNumber( nSectNo, &rFtn.GetNumStr() );
/*?*/               else
/*?*/                   pTxtFtn->SetNumber( nSectNo, &rFtn.GetNumStr() );
/*?*/           }
/*?*/       }
/*N*/   }
/*N*/
/*N*/   if( pDoc->GetRootFrm() && FTNNUM_PAGE == rFtnInfo.eNum )
/*?*/       {DBG_BF_ASSERT(0, "STRIP"); }//STRIP001 pDoc->GetRootFrm()->UpdateFtnNums();
/*N*/ }

//STRIP001 void SwFtnIdxs::UpdateFtnInSections()
//STRIP001 {
//STRIP001  if( !Count() )
//STRIP001      return;
//STRIP001
//STRIP001  // besorge erstmal das Nodes-Array ueber den StartIndex der
//STRIP001  // ersten Fussnote
//STRIP001  SwDoc* pDoc = (SwDoc*) (*this)[ 0 ]->GetTxtNode().GetDoc();
//STRIP001  SwTxtFtn* pTxtFtn;
//STRIP001  SwUpdFtnEndNtAtEnd aNumArr;
//STRIP001  for( USHORT nPos = 0; nPos < Count(); ++nPos )
//STRIP001  {
//STRIP001      pTxtFtn = (*this)[ nPos ];
//STRIP001      const SwFmtFtn &rFtn = pTxtFtn->GetFtn();
//STRIP001      if( !rFtn.GetNumStr().Len() )
//STRIP001      {
//STRIP001          USHORT nSectNo = aNumArr.ChkNumber( *pTxtFtn );
//STRIP001          if( nSectNo )
//STRIP001          {
//STRIP001              if( rFtn.IsEndNote() )
//STRIP001                  pTxtFtn->SetNumber( nSectNo, &rFtn.GetNumStr() );
//STRIP001              else
//STRIP001                  pTxtFtn->SetNumber( nSectNo, &rFtn.GetNumStr() );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*N*/ SwTxtFtn* SwFtnIdxs::SeekEntry( const SwNodeIndex& rPos, USHORT* pFndPos ) const
/*N*/ {
/*N*/   ULONG nIdx = rPos.GetIndex();
/*N*/
/*N*/   register USHORT nO = Count(), nM, nU = 0;
/*N*/   if( nO > 0 )
/*N*/   {
/*N*/       nO--;
/*N*/       while( nU <= nO )
/*N*/       {
/*N*/           nM = nU + ( nO - nU ) / 2;
/*N*/           ULONG nNdIdx = _SwTxtFtn_GetIndex( (*this)[ nM ] );
/*N*/           if( nNdIdx == nIdx )
/*N*/           {
/*N*/               if( pFndPos )
/*N*/                   *pFndPos = nM;
/*N*/               return (*this)[ nM ];
/*N*/           }
/*N*/           else if( nNdIdx < nIdx )
/*N*/               nU = nM + 1;
/*N*/           else if( nM == 0 )
/*N*/           {
/*N*/               if( pFndPos )
/*N*/                   *pFndPos = nU;
/*N*/               return 0;
/*N*/           }
/*N*/           else
/*N*/               nO = nM - 1;
/*N*/       }
/*N*/   }
/*?*/   if( pFndPos )
/*?*/       *pFndPos = nU;
/*?*/   return 0;
/*N*/ }

/*  */

/*N*/ const SwSectionNode* SwUpdFtnEndNtAtEnd::FindSectNdWithEndAttr(
/*N*/               const SwTxtFtn& rTxtFtn )
/*N*/ {
/*N*/   USHORT nWh = rTxtFtn.GetFtn().IsEndNote() ? RES_END_AT_TXTEND
/*N*/                                             : RES_FTN_AT_TXTEND;
/*N*/   USHORT nVal;
/*N*/   const SwSectionNode* pNd = rTxtFtn.GetTxtNode().FindSectionNode();
/*N*/   while( pNd && FTNEND_ATTXTEND_OWNNUMSEQ != ( nVal =
/*N*/           ((const SwFmtFtnAtTxtEnd&)pNd->GetSection().GetFmt()->
/*N*/           GetAttr( nWh, TRUE )).GetValue() ) &&
/*N*/           FTNEND_ATTXTEND_OWNNUMANDFMT != nVal )
/*?*/       pNd = pNd->FindStartNode()->FindSectionNode();
/*N*/
/*N*/   return pNd;
/*N*/ }

/*N*/ USHORT SwUpdFtnEndNtAtEnd::GetNumber( const SwTxtFtn& rTxtFtn,
/*N*/                                   const SwSectionNode& rNd )
/*N*/ {
DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001  USHORT nRet = 0, nWh;
//STRIP001  SvPtrarr* pArr;
//STRIP001  SvUShorts* pNum;
//STRIP001  if( rTxtFtn.GetFtn().IsEndNote() )
//STRIP001  {
//STRIP001      pArr = &aEndSects;
//STRIP001      pNum = &aEndNums;
//STRIP001      nWh = RES_END_AT_TXTEND;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      pArr = &aFtnSects;
//STRIP001      pNum = &aFtnNums;
//STRIP001      nWh = RES_FTN_AT_TXTEND;
//STRIP001  }
//STRIP001  void* pNd = (void*)&rNd;
//STRIP001
//STRIP001  for( USHORT n = pArr->Count(); n; )
//STRIP001      if( pArr->GetObject( --n ) == pNd )
//STRIP001      {
//STRIP001          nRet = ++pNum->GetObject( n );
//STRIP001          break;
//STRIP001      }
//STRIP001
//STRIP001  if( !nRet )
//STRIP001  {
//STRIP001      pArr->Insert( pNd, pArr->Count() );
//STRIP001      nRet = ((SwFmtFtnEndAtTxtEnd&)rNd.GetSection().GetFmt()->
//STRIP001                              GetAttr( nWh )).GetOffset();
//STRIP001      ++nRet;
//STRIP001      pNum->Insert( nRet, pNum->Count() );
//STRIP001  }
//STRIP001  return nRet;
/*N*/ }

/*N*/ USHORT SwUpdFtnEndNtAtEnd::ChkNumber( const SwTxtFtn& rTxtFtn )
/*N*/ {
/*N*/   const SwSectionNode* pSectNd = FindSectNdWithEndAttr( rTxtFtn );
/*N*/   return pSectNd ? GetNumber( rTxtFtn, *pSectNd ) : 0;
/*N*/ }




}
