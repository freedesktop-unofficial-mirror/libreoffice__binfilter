/*************************************************************************
 *
 *  $RCSfile: sw_ftnfrm.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 17:36:14 $
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
#ifndef _FTNIDX_HXX
#include <ftnidx.hxx>
#endif
#ifndef _PAGEFRM_HXX
#include <pagefrm.hxx>
#endif
#ifndef _COLFRM_HXX
#include <colfrm.hxx>
#endif
#ifndef _ROOTFRM_HXX
#include <rootfrm.hxx>
#endif
// auto strip #ifndef _CNTFRM_HXX
// auto strip #include <cntfrm.hxx>
// auto strip #endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>
#endif
#ifndef _FRMTOOL_HXX
#include <frmtool.hxx>
#endif
// auto strip #ifndef _ERRHDL_HXX
// auto strip #include <errhdl.hxx>
// auto strip #endif
#ifndef _SWTABLE_HXX
#include <swtable.hxx>
#endif
#ifndef _FTNFRM_HXX
#include <ftnfrm.hxx>
#endif
#ifndef _TXTFRM_HXX
#include <txtfrm.hxx>
#endif
#ifndef _TABFRM_HXX
#include <tabfrm.hxx>
#endif
#ifndef _PAGEDESC_HXX
#include <pagedesc.hxx>
#endif
#ifndef _FTNINFO_HXX
#include <ftninfo.hxx>
#endif
// auto strip #ifndef _NDINDEX_HXX
// auto strip #include <ndindex.hxx>
// auto strip #endif
#ifndef _SECTFRM_HXX
#include <sectfrm.hxx>
#endif
#ifndef _PAM_HXX
#include <pam.hxx>
#endif
namespace binfilter {

/*************************************************************************
|*
|*  lcl_FindFtnPos()        Sucht die Position des Attributes im FtnArray am
|*      Dokument, dort stehen die Fussnoten gluecklicherweise nach ihrem
|*      Index sortiert.
|*
|*  Ersterstellung      MA 29. Jun. 93
|*  Letzte Aenderung    MA 13. Dec. 93
|*
|*************************************************************************/

/*N*/ #define ENDNOTE 0x80000000

/*N*/ ULONG MA_FASTCALL lcl_FindFtnPos( const SwDoc *pDoc, const SwTxtFtn *pAttr )
/*N*/ {
/*N*/   const SwFtnIdxs &rFtnIdxs = pDoc->GetFtnIdxs();
/*N*/
/*N*/ #ifdef MA_DEBUG
/*N*/   //Wenn das Array nicht stimmt haben wir ein Problem, denn viele
/*N*/   //Ftn-Functions bauen auf dem Array auf.
/*N*/   for ( USHORT k = 0; k+1 < rFtnIdxs.Count(); ++k )
/*N*/   {
/*N*/       SwIndex aIdx1(&pDoc->GetNodes());
/*N*/       SwIndex aIdx2(&pDoc->GetNodes());
/*N*/       rFtnIdxs[k]->pFtn->  GetTxtNode().GetIndex(aIdx1);
/*N*/       rFtnIdxs[k+1]->pFtn->GetTxtNode().GetIndex(aIdx2);
/*N*/       if ( aIdx1.GetIndex() > aIdx2.GetIndex() )
/*N*/       {
/*N*/           ASSERT( !rFtnIdxs.Count(), "FtnIdxs not up to date" );
/*N*/       }
/*N*/       else if ( aIdx1.GetIndex() == aIdx2.GetIndex() )
/*N*/       {
/*N*/           SwTxtFtn *p1 = rFtnIdxs[k];
/*N*/           SwTxtFtn *p2 = rFtnIdxs[k+1];
/*N*/           ASSERT( *p1->GetStart() < *p2->GetStart(),
/*N*/                   "FtnIdxs not up to date" );
/*N*/       }
/*N*/   }
/*N*/ #endif
/*N*/
/*N*/   USHORT nRet;
/*N*/   SwTxtFtnPtr pBla = (SwTxtFtn*)pAttr;
/*N*/   if ( rFtnIdxs.Seek_Entry( pBla, &nRet ) )
/*N*/   {
/*N*/       if( pAttr->GetFtn().IsEndNote() )
/*?*/           return ULONG(nRet) + ENDNOTE;
/*N*/       return nRet;
/*N*/   }
/*?*/   ASSERT( !pDoc, "FtnPos not found." );
/*?*/   return 0;
/*N*/ }

//STRIP001 BOOL SwFtnFrm::operator<( const SwTxtFtn* pTxtFtn ) const
//STRIP001 {
//STRIP001  const SwDoc* pDoc = GetFmt()->GetDoc();
//STRIP001  ASSERT( pDoc, "SwFtnFrm: Missing doc!" );
//STRIP001  return lcl_FindFtnPos( pDoc, GetAttr() ) <
//STRIP001         lcl_FindFtnPos( pDoc, pTxtFtn );
//STRIP001 }

/*************************************************************************
|*
|*  BOOL lcl_NextFtnBoss( SwFtnBossFrm* pBoss, SwPageFrm* pPage)
|*  setzt pBoss auf den naechsten SwFtnBossFrm, das kann entweder eine Spalte
|*  oder eine Seite (ohne Spalten) sein. Wenn die Seite dabei gewechselt wird
|*  enthaelt pPage die neue Seite und die Funktion liefert TRUE.
|*
|*  Ersterstellung      AMA 06. Nov. 98
|*  Letzte Aenderung    AMA 06. Nov. 98
|*
|*************************************************************************/

/*N*/ BOOL lcl_NextFtnBoss( SwFtnBossFrm* &rpBoss, SwPageFrm* &rpPage,
/*N*/   BOOL bDontLeave )
/*N*/ {
/*N*/   if( rpBoss->IsColumnFrm() )
/*N*/   {
/*?*/       if( rpBoss->GetNext() )
/*?*/       {
/*?*/           rpBoss = (SwFtnBossFrm*)rpBoss->GetNext(); //naechste Spalte
/*?*/           return FALSE;
/*?*/       }
/*?*/       if( rpBoss->IsInSct() )
/*?*/       {
/*?*/           SwSectionFrm* pSct = rpBoss->FindSctFrm()->GetFollow();
/*?*/           if( pSct )
/*?*/           {
/*?*/               ASSERT( pSct->Lower() && pSct->Lower()->IsColumnFrm(),
/*?*/                       "Where's the column?" );
/*?*/               rpBoss = (SwColumnFrm*)pSct->Lower();
/*?*/               SwPageFrm* pOld = rpPage;
/*?*/               rpPage = pSct->FindPageFrm();
/*?*/               return pOld != rpPage;
/*?*/           }
/*?*/           else if( bDontLeave )
/*?*/           {
/*?*/               rpPage = NULL;
/*?*/               rpBoss = NULL;
/*?*/               return FALSE;
/*?*/           }
/*?*/       }
/*N*/   }
/*N*/   rpPage = (SwPageFrm*)rpPage->GetNext(); // naechste Seite
/*N*/   rpBoss = rpPage;
/*N*/   if( rpPage )
/*N*/   {
/*N*/       SwLayoutFrm* pBody = rpPage->FindBodyCont();
/*N*/       if( pBody && pBody->Lower() && pBody->Lower()->IsColumnFrm() )
/*?*/           rpBoss = (SwFtnBossFrm*)pBody->Lower(); // erste Spalte
/*N*/   }
/*N*/   return TRUE;
/*N*/ }

/*************************************************************************
|*
|*  USHORT lcl_ColumnNum( SwFrm* pBoss )
|*  liefert die Spaltennummer, wenn pBoss eine Spalte ist,
|*  sonst eine Null (bei Seiten).
|*
|*  Ersterstellung      AMA 06. Nov. 98
|*  Letzte Aenderung    AMA 06. Nov. 98
|*
|*************************************************************************/

/*N*/ USHORT lcl_ColumnNum( const SwFrm* pBoss )
/*N*/ {
/*N*/   USHORT nRet = 0;
/*N*/   if( !pBoss->IsColumnFrm() )
/*N*/       return 0;
/*?*/   const SwFrm* pCol;
/*?*/   if( pBoss->IsInSct() )
/*?*/   {
/*?*/       pCol = pBoss->GetUpper()->FindColFrm();
/*?*/       if( pBoss->GetNext() || pBoss->GetPrev() )
/*?*/       {
/*?*/           while( pBoss )
/*?*/           {
/*?*/               ++nRet;                     // Section columns
/*?*/               pBoss = pBoss->GetPrev();
/*?*/           }
/*?*/       }
/*?*/   }
/*?*/   else
/*?*/       pCol = pBoss;
/*?*/   while( pCol )
/*?*/   {
/*?*/       nRet += 256;                    // Page columns
/*?*/       pCol = pCol->GetPrev();
/*?*/   }
/*?*/   return nRet;
/*N*/ }

/*************************************************************************
|*
|*  SwFtnContFrm::SwFtnContFrm()
|*
|*  Ersterstellung      MA 24. Feb. 93
|*  Letzte Aenderung    MA 02. Mar. 93
|*
|*************************************************************************/


/*N*/ SwFtnContFrm::SwFtnContFrm( SwFrmFmt *pFmt ):
/*N*/   SwLayoutFrm( pFmt )
/*N*/ {
/*N*/     nType = FRMC_FTNCONT;
/*N*/ }


// lcl_Undersize(..) klappert einen SwFrm und dessen Inneres ab
// und liefert die Summe aller TxtFrm-Vergroesserungswuensche

/*N*/ long lcl_Undersize( const SwFrm* pFrm )
/*N*/ {
/*N*/   long nRet = 0;
/*N*/     SWRECTFN( pFrm )
/*N*/   if( pFrm->IsTxtFrm() )
/*N*/   {
/*N*/       if( ((SwTxtFrm*)pFrm)->IsUndersized() )
/*N*/         {
/*?*/           // Dieser TxtFrm waere gern ein bisschen groesser
/*?*/             nRet = ((SwTxtFrm*)pFrm)->GetParHeight() -
/*?*/                     (pFrm->Prt().*fnRect->fnGetHeight)();
/*?*/             if( nRet < 0 )
/*?*/               nRet = 0;
/*N*/         }
/*N*/   }
/*N*/   else if( pFrm->IsLayoutFrm() )
/*N*/   {
/*N*/       const SwFrm* pNxt = ((SwLayoutFrm*)pFrm)->Lower();
/*N*/       while( pNxt )
/*N*/       {
/*N*/           nRet += lcl_Undersize( pNxt );
/*N*/           pNxt = pNxt->GetNext();
/*N*/       }
/*N*/   }
/*N*/   return nRet;
/*N*/ }

/*************************************************************************
|*
|*  SwFtnContFrm::Format()
|*
|*  Beschreibung:       "Formatiert" den Frame;
|*                      Die Fixsize wird hier nicht eingestellt.
|*  Ersterstellung      MA 01. Mar. 93
|*  Letzte Aenderung    MA 17. Nov. 98
|*
|*************************************************************************/


/*N*/ void SwFtnContFrm::Format( const SwBorderAttrs * )
/*N*/ {
/*N*/   //GesamtBorder ermitteln, es gibt nur einen Abstand nach oben.
/*N*/   const SwPageFrm* pPage = FindPageFrm();
/*N*/   const SwPageFtnInfo &rInf = pPage->GetPageDesc()->GetFtnInfo();
/*N*/   const SwTwips nBorder = rInf.GetTopDist() + rInf.GetBottomDist() +
/*N*/                           rInf.GetLineWidth();
/*N*/     SWRECTFN( this )
/*N*/   if ( !bValidPrtArea )
/*N*/   {
/*N*/       bValidPrtArea = TRUE;
/*N*/         (Prt().*fnRect->fnSetTop)( nBorder );
/*N*/         (Prt().*fnRect->fnSetWidth)( (Frm().*fnRect->fnGetWidth)() );
/*N*/         (Prt().*fnRect->fnSetHeight)((Frm().*fnRect->fnGetHeight)() - nBorder );
/*N*/         if( (Prt().*fnRect->fnGetHeight)() < 0 && !pPage->IsFtnPage() )
/*N*/           bValidSize = FALSE;
/*N*/   }
/*N*/
/*N*/   if ( !bValidSize )
/*N*/   {
/*N*/       if ( pPage->IsFtnPage() && !GetFmt()->GetDoc()->IsBrowseMode() )
/*?*/                 Grow( LONG_MAX PHEIGHT, FALSE );
/*N*/       else
/*N*/       {
/*N*/           //Die Groesse in der VarSize wird durch den Inhalt plus den
/*N*/           //Raendern bestimmt.
/*N*/           SwTwips nRemaining = 0;
/*N*/           SwFrm *pFrm = pLower;
/*N*/           while ( pFrm )
/*N*/           {   // lcl_Undersize(..) beruecksichtigt (rekursiv) TxtFrms, die gerne
/*N*/               // groesser waeren. Diese entstehen insbesondere in spaltigen Rahmen,
/*N*/               // wenn diese noch nicht ihre maximale Groesse haben.
/*N*/                 nRemaining += (pFrm->Frm().*fnRect->fnGetHeight)()
/*N*/                               + lcl_Undersize( pFrm );
/*N*/               pFrm = pFrm->GetNext();
/*N*/           }
/*N*/           //Jetzt noch den Rand addieren
/*N*/           nRemaining += nBorder;
/*N*/
/*N*/           SwTwips nDiff;
/*N*/           if( IsInSct() )
/*N*/           {
/*?*/                 nDiff = -(Frm().*fnRect->fnBottomDist)(
/*?*/                                         (GetUpper()->*fnRect->fnGetPrtBottom)() );
/*?*/                 if( nDiff > 0 )
/*?*/               {
/*?*/                     if( nDiff > (Frm().*fnRect->fnGetHeight)() )
/*?*/                         nDiff = (Frm().*fnRect->fnGetHeight)();
/*?*/                     (Frm().*fnRect->fnAddBottom)( -nDiff );
/*?*/                     (Prt().*fnRect->fnAddHeight)( -nDiff );
/*?*/               }
/*N*/           }
/*N*/             nDiff = (Frm().*fnRect->fnGetHeight)() - nRemaining;
/*N*/           if ( nDiff > 0 )
/*?*/                 Shrink( nDiff PHEIGHT );
/*N*/           else if ( nDiff < 0 )
/*N*/           {
/*N*/                 Grow( -nDiff PHEIGHT );
/*N*/               //Es kann passieren, dass weniger Platz zur Verfuegung steht,
/*N*/               //als der bereits der Border benoetigt - die Groesse der
/*N*/               //PrtArea wird dann negativ.
/*N*/                 SwTwips nPrtHeight = (Prt().*fnRect->fnGetHeight)();
/*N*/                 if( nPrtHeight < 0 )
/*N*/               {
/*?*/                     const SwTwips nDiff = Max( (Prt().*fnRect->fnGetTop)(),
/*?*/                                                 -nPrtHeight );
/*?*/                     (Prt().*fnRect->fnSubTop)( nDiff );
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/       bValidSize = TRUE;
/*N*/   }
/*N*/ }
/*************************************************************************
|*
|*  SwFtnContFrm::GrowFrm(), ShrinkFrm()
|*
|*  Ersterstellung      MA 24. Feb. 93
|*  Letzte Aenderung    AMA 05. Nov. 98
|*
|*************************************************************************/

/*N*/ SwTwips SwFtnContFrm::GrowFrm( SwTwips nDist, BOOL bTst, BOOL bInfo )
/*N*/ {
/*N*/   //Keine Pruefung ob FixSize oder nicht, die FtnContainer sind immer bis
/*N*/   //zur Maximalhoehe variabel.
/*N*/   //Wenn die Maximalhoehe LONG_MAX ist, so nehmen wir uns soviel Platz wie eben
/*N*/   //moeglich.
/*N*/   //Wenn die Seite eine spezielle Fussnotenseite ist, so nehmen wir uns auch
/*N*/   //soviel Platz wie eben moeglich.
/*N*/ #ifndef PRODUCT
/*N*/   if ( !GetUpper() || !GetUpper()->IsFtnBossFrm() )
/*?*/   {   ASSERT( !this, "Keine FtnBoss." );
/*?*/       return 0;
/*N*/   }
/*N*/ #endif
/*N*/
/*N*/     SWRECTFN( this )
/*N*/     if( (Frm().*fnRect->fnGetHeight)() > 0 &&
/*N*/          nDist > ( LONG_MAX - (Frm().*fnRect->fnGetHeight)() ) )
/*N*/         nDist = LONG_MAX - (Frm().*fnRect->fnGetHeight)();
/*N*/
/*N*/   SwFtnBossFrm *pBoss = (SwFtnBossFrm*)GetUpper();
/*N*/   if( IsInSct() )
/*N*/   {
/*?*/       SwSectionFrm* pSect = FindSctFrm();
/*?*/       ASSERT( pSect, "GrowFrm: Missing SectFrm" );
/*?*/       // In a section, which has to maximize, a footnotecontainer is allowed
/*?*/       // to grow, when the section can't grow anymore.
/*?*/       if( !bTst && !pSect->IsColLocked() &&
/*?*/           pSect->ToMaximize( FALSE ) && pSect->Growable() )
/*?*/       {
/*?*/           pSect->InvalidateSize();
/*?*/           return 0;
/*?*/       }
/*N*/   }
/*N*/   SwPageFrm *pPage = pBoss->FindPageFrm();
/*N*/   if ( !pPage->IsFtnPage() || GetFmt()->GetDoc()->IsBrowseMode() )
/*N*/   {
/*N*/       if ( pBoss->GetMaxFtnHeight() != LONG_MAX )
/*N*/       {
/*N*/             nDist = Min( nDist, pBoss->GetMaxFtnHeight()
/*N*/                          - (Frm().*fnRect->fnGetHeight)() );
/*N*/           if ( nDist <= 0 )
/*?*/               return 0L;
/*N*/       }
/*N*/       //Der FtnBoss will bezueglich des MaxWerts auch noch mitreden.
/*N*/       if( !IsInSct() )
/*N*/       {
/*N*/           const SwTwips nMax = pBoss->GetVarSpace();
/*N*/           if ( nDist > nMax )
/*N*/               nDist = nMax;
/*N*/           if ( nDist <= 0 )
/*?*/               return 0L;
/*N*/       }
/*N*/   }
/*N*/     else if( nDist > (GetPrev()->Frm().*fnRect->fnGetHeight)() )
/*N*/       //aber mehr als der Body kann koennen und wollen wir nun auch wieder
/*N*/       //nicht herausruecken.
/*?*/         nDist = (GetPrev()->Frm().*fnRect->fnGetHeight)();
/*N*/
/*N*/     long nAvail = 0;
/*N*/   if ( GetFmt()->GetDoc()->IsBrowseMode() )
/*N*/   {
/*?*/         nAvail = GetUpper()->Prt().Height();
/*?*/       const SwFrm *pAvail = GetUpper()->Lower();
/*?*/       do
/*?*/         {   nAvail -= pAvail->Frm().Height();
/*?*/           pAvail = pAvail->GetNext();
/*?*/       } while ( pAvail );
/*?*/       if ( nAvail > nDist )
/*?*/           nAvail = nDist;
/*N*/   }
/*N*/
/*N*/     if ( !bTst )
/*N*/     {
/*N*/         (Frm().*fnRect->fnSetHeight)( (Frm().*fnRect->fnGetHeight)() + nDist );
/*N*/         if( IsVertical() && !IsReverse() )
/*?*/             Frm().Pos().X() -= nDist;
/*N*/     }
/*N*/   long nGrow = nDist - nAvail,
/*N*/        nReal = 0;
/*N*/   if ( nGrow > 0 )
/*N*/   {
/*N*/       BYTE nAdjust = pBoss->NeighbourhoodAdjustment( this );
/*N*/       if( NA_ONLY_ADJUST == nAdjust )
/*N*/           nReal = AdjustNeighbourhood( nGrow, bTst );
/*N*/       else
/*N*/       {
/*?*/           if( NA_GROW_ADJUST == nAdjust )
/*?*/           {
/*?*/               SwFrm* pFtn = Lower();
/*?*/               if( pFtn )
/*?*/               {
/*?*/                   while( pFtn->GetNext() )
/*?*/                       pFtn = pFtn->GetNext();
/*?*/                   if( ((SwFtnFrm*)pFtn)->GetAttr()->GetFtn().IsEndNote() )
/*?*/                   {
/*?*/                       nReal = AdjustNeighbourhood( nGrow, bTst );
/*?*/                       nAdjust = NA_GROW_SHRINK; // no more AdjustNeighbourhood
/*?*/                   }
/*?*/               }
/*?*/           }
/*?*/             nReal += pBoss->Grow( nGrow - nReal, bTst );
/*?*/           if( ( NA_GROW_ADJUST == nAdjust || NA_ADJUST_GROW == nAdjust )
/*?*/                 && nReal < nGrow )
/*?*/               nReal += AdjustNeighbourhood( nGrow - nReal, bTst );
/*N*/       }
/*N*/   }
/*N*/
/*N*/   nReal += nAvail;
/*N*/
/*N*/   if ( !bTst )
/*N*/   {
/*N*/       if ( nReal != nDist )
/*N*/         {
/*?*/             nDist -= nReal;
/*?*/           //Den masslosen Wunsch koennen wir leider nur in Grenzen erfuellen.
/*?*/             Frm().SSize().Height() -= nDist;
/*?*/             if( IsVertical() && !IsReverse() )
/*?*/                 Frm().Pos().X() += nDist;
/*N*/         }
/*N*/
/*N*/       //Nachfolger braucht nicht invalidiert werden, denn wir wachsen
/*N*/       //immer nach oben.
/*N*/       if( nReal )
/*N*/       {
/*N*/           _InvalidateSize();
/*N*/           _InvalidatePos();
/*N*/           InvalidatePage( pPage );
/*N*/       }
/*N*/   }
/*N*/   return nReal;
/*N*/ }


/*N*/ SwTwips SwFtnContFrm::ShrinkFrm( SwTwips nDiff, BOOL bTst, BOOL bInfo )
/*N*/ {
/*N*/   SwPageFrm *pPage = FindPageFrm();
/*N*/   if ( pPage && (!pPage->IsFtnPage() || GetFmt()->GetDoc()->IsBrowseMode()) )
/*N*/   {
/*N*/         SwTwips nRet = SwLayoutFrm::ShrinkFrm( nDiff, bTst, bInfo );
/*N*/         if( IsInSct() && !bTst )
/*N*/             FindSctFrm()->InvalidateNextPos();
/*N*/       if ( !bTst && nRet )
/*N*/       {
/*N*/           _InvalidatePos();
/*N*/           InvalidatePage( pPage );
/*N*/       }
/*N*/       return nRet;
/*N*/   }
/*?*/   return 0;
/*N*/ }


/*************************************************************************
|*
|*  SwFtnFrm::SwFtnFrm()
|*
|*  Ersterstellung      MA 24. Feb. 93
|*  Letzte Aenderung    MA 11. Oct. 93
|*
|*************************************************************************/


/*N*/ SwFtnFrm::SwFtnFrm( SwFrmFmt *pFmt, SwCntntFrm *pCnt, SwTxtFtn *pAt ):
/*N*/   SwLayoutFrm( pFmt ),
/*N*/   pFollow( 0 ),
/*N*/   pMaster( 0 ),
/*N*/   pRef( pCnt ),
/*N*/   pAttr( pAt ),
/*N*/   bBackMoveLocked( FALSE )
/*N*/ {
/*N*/     nType = FRMC_FTN;
/*N*/ }

/*************************************************************************
|*
|*  SwFtnFrm::InvalidateNxtFtnCnts()
|*
|*  Ersterstellung      MA 29. Jun. 93
|*  Letzte Aenderung    MA 29. Jun. 93
|*
|*************************************************************************/


/*N*/ void SwFtnFrm::InvalidateNxtFtnCnts( SwPageFrm *pPage )
/*N*/ {
/*N*/   if ( GetNext() )
/*N*/   {
/*N*/       SwFrm *pCnt = ((SwLayoutFrm*)GetNext())->ContainsAny();
/*N*/       if( pCnt )
/*N*/       {
/*?*/           pCnt->InvalidatePage( pPage );
/*?*/           pCnt->_InvalidatePrt();
/*?*/           do
/*?*/           {   pCnt->_InvalidatePos();
/*?*/               if( pCnt->IsSctFrm() )
/*?*/               {
/*?*/                   SwFrm* pTmp = ((SwSectionFrm*)pCnt)->ContainsAny();
/*?*/                   if( pTmp )
/*?*/                       pTmp->_InvalidatePos();
/*?*/               }
/*?*/               pCnt->GetUpper()->_InvalidateSize();
/*?*/               pCnt = pCnt->FindNext();
/*?*/           } while ( pCnt && GetUpper()->IsAnLower( pCnt ) );
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ #ifndef PRODUCT
/*N*/
/*N*/ SwTwips SwFtnFrm::GrowFrm( SwTwips nDist, BOOL bTst, BOOL bInfo )
/*N*/ {
/*N*/ #if OSL_DEBUG_LEVEL > 1
/*N*/   static USHORT nNum = USHRT_MAX;
/*N*/   SwTxtFtn* pTxtFtn = GetAttr();
/*N*/   if ( pTxtFtn->GetFtn().GetNumber() == nNum )
/*N*/   {
/*?*/       int bla = 5;
/*N*/   }
/*N*/ #endif
/*N*/     return SwLayoutFrm::GrowFrm( nDist, bTst, bInfo );
/*N*/ }


/*N*/ SwTwips SwFtnFrm::ShrinkFrm( SwTwips nDist, BOOL bTst, BOOL bInfo )
/*N*/ {
/*N*/ #if OSL_DEBUG_LEVEL > 1
/*N*/   static USHORT nNum = USHRT_MAX;
/*N*/   if( nNum != USHRT_MAX )
/*N*/   {
/*?*/       SwTxtFtn* pTxtFtn = GetAttr();
/*?*/       if( &pTxtFtn->GetAttr() && pTxtFtn->GetFtn().GetNumber() == nNum )
/*?*/       {
/*?*/           int bla = 5;
/*?*/       }
/*N*/   }
/*N*/ #endif
/*N*/     return SwLayoutFrm::ShrinkFrm( nDist, bTst, bInfo );
/*N*/ }
/*N*/ #endif

/*************************************************************************
|*
|*  SwFtnFrm::Cut()
|*
|*  Ersterstellung      MA 23. Feb. 94
|*  Letzte Aenderung    MA 24. Jul. 95
|*
|*************************************************************************/


/*N*/ void SwFtnFrm::Cut()
/*N*/ {
/*N*/   if ( GetNext() )
/*?*/       GetNext()->InvalidatePos();
/*N*/   else if ( GetPrev() )
/*?*/       GetPrev()->SetRetouche();
/*N*/
/*N*/   //Erst removen, dann Upper Shrinken.
/*N*/   SwLayoutFrm *pUp = GetUpper();
/*N*/
/*N*/   //Verkettung korrigieren.
/*N*/   SwFtnFrm *pFtn = (SwFtnFrm*)this;
/*N*/   if ( pFtn->GetFollow() )
/*?*/       pFtn->GetFollow()->SetMaster( pFtn->GetMaster() );
/*N*/   if ( pFtn->GetMaster() )
/*?*/       pFtn->GetMaster()->SetFollow( pFtn->GetFollow() );
/*N*/   pFtn->SetFollow( 0 );
/*N*/   pFtn->SetMaster( 0 );
/*N*/
/*N*/   // Alle Verbindungen kappen.
/*N*/   Remove();
/*N*/
/*N*/   if ( pUp )
/*N*/   {
/*N*/       //Die letzte Fussnote nimmt ihren Container mit.
/*N*/       if ( !pUp->Lower() )
/*N*/       {
/*N*/           SwPageFrm *pPage = pUp->FindPageFrm();
/*N*/           if ( pPage )
/*N*/           {
/*N*/               SwLayoutFrm *pBody = pPage->FindBodyCont();
/*N*/               if ( !pBody->ContainsCntnt() )
/*?*/                   pPage->FindRootFrm()->SetSuperfluous();
/*N*/           }
/*N*/           SwSectionFrm* pSect = pUp->FindSctFrm();
/*N*/           pUp->Cut();
/*N*/           delete pUp;
/*N*/           // Wenn der letzte Fussnotencontainer aus einem spaltigen Bereich verschwindet,
/*N*/           // so kann dieser, falls er keinen Follow besitzt, zusammenschrumpfen.
/*N*/           if( pSect && !pSect->ToMaximize( FALSE ) && !pSect->IsColLocked() )
/*?*/               pSect->_InvalidateSize();
/*N*/       }
/*N*/       else
/*?*/       {   if ( Frm().Height() )
/*?*/                 pUp->Shrink( Frm().Height() PHEIGHT );
/*?*/           pUp->SetCompletePaint();
/*?*/           pUp->InvalidatePage();
/*N*/       }
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|*  SwFtnFrm::Paste()
|*
|*  Ersterstellung      MA 23. Feb. 94
|*  Letzte Aenderung    MA 23. Feb. 94
|*
|*************************************************************************/


/*N*/ void SwFtnFrm::Paste(  SwFrm* pParent, SwFrm* pSibling )
/*N*/ {
/*N*/   ASSERT( pParent, "Kein Parent fuer Paste." );
/*N*/   ASSERT( pParent->IsLayoutFrm(), "Parent ist CntntFrm." );
/*N*/   ASSERT( pParent != this, "Bin selbst der Parent." );
/*N*/   ASSERT( pSibling != this, "Bin mein eigener Nachbar." );
/*N*/   ASSERT( !GetPrev() && !GetNext() && !GetUpper(),
/*N*/           "Bin noch irgendwo angemeldet." );
/*N*/
/*N*/   //In den Baum einhaengen.
/*N*/   InsertBefore( (SwLayoutFrm*)pParent, pSibling );
/*N*/
/*N*/     SWRECTFN( this )
/*N*/     if( (Frm().*fnRect->fnGetWidth)()!=(pParent->Prt().*fnRect->fnGetWidth)() )
/*?*/       _InvalidateSize();
/*N*/   _InvalidatePos();
/*N*/   SwPageFrm *pPage = FindPageFrm();
/*N*/   InvalidatePage( pPage );
/*N*/   if ( GetNext() )
/*?*/       GetNext()->_InvalidatePos();
/*N*/     if( (Frm().*fnRect->fnGetHeight)() )
/*?*/         pParent->Grow( (Frm().*fnRect->fnGetHeight)() );
/*N*/
/*N*/   //Wenn mein Vorgaenger mein Master ist und/oder wenn mein Nachfolger mein
/*N*/   //Follow ist so kann ich deren Inhalt uebernehmen und sie vernichten.
/*N*/   if ( GetPrev() && GetPrev() == GetMaster() )
/*?*/   {   ASSERT( SwFlowFrm::CastFlowFrm( GetPrev()->GetLower() ),
/*?*/               "Fussnote ohne Inhalt?" );
/*?*/       (SwFlowFrm::CastFlowFrm( GetPrev()->GetLower()))->
/*?*/           MoveSubTree( this, GetLower() );
/*?*/       SwFrm *pDel = GetPrev();
/*?*/       pDel->Cut();
/*?*/       delete pDel;
/*N*/   }
/*N*/   if ( GetNext() && GetNext() == GetFollow() )
/*?*/   {   ASSERT( SwFlowFrm::CastFlowFrm( GetNext()->GetLower() ),
/*?*/               "Fussnote ohne Inhalt?" );
/*?*/       (SwFlowFrm::CastFlowFrm( GetNext()->GetLower()))->MoveSubTree( this );
/*?*/       SwFrm *pDel = GetNext();
/*?*/       pDel->Cut();
/*?*/       delete pDel;
/*N*/   }
/*N*/ #ifndef PRODUCT
/*N*/   SwDoc *pDoc = GetFmt()->GetDoc();
/*N*/   if ( GetPrev() )
/*N*/   {
/*N*/       ASSERT( lcl_FindFtnPos( pDoc, ((SwFtnFrm*)GetPrev())->GetAttr() ) <=
/*?*/               lcl_FindFtnPos( pDoc, GetAttr() ), "Prev ist not FtnPrev" );
/*N*/   }
/*N*/   if ( GetNext() )
/*N*/   {
/*?*/       ASSERT( lcl_FindFtnPos( pDoc, GetAttr() ) <=
/*?*/               lcl_FindFtnPos( pDoc, ((SwFtnFrm*)GetNext())->GetAttr() ),
/*?*/               "Next is not FtnNext" );
/*N*/   }
/*N*/ #endif
/*N*/   InvalidateNxtFtnCnts( pPage );
/*N*/ }

/*************************************************************************
|*
|*  SwFrm::GetNextFtnLeaf()
|*
|*  Beschreibung        Liefert das naechste LayoutBlatt in den das
|*      Frame gemoved werden kann.
|*      Neue Seiten werden nur dann erzeugt, wenn der Parameter TRUE ist.
|*  Ersterstellung      MA 16. Nov. 92
|*  Letzte Aenderung    AMA 09. Nov. 98
|*
|*************************************************************************/


//STRIP001 SwLayoutFrm *SwFrm::GetNextFtnLeaf( MakePageType eMakePage )
//STRIP001 {
//STRIP001  SwFtnBossFrm *pOldBoss = FindFtnBossFrm();
//STRIP001  SwPageFrm* pOldPage = pOldBoss->FindPageFrm();
//STRIP001  SwPageFrm* pPage;
//STRIP001  SwFtnBossFrm *pBoss = pOldBoss->IsColumnFrm() ?
//STRIP001      (SwFtnBossFrm*)pOldBoss->GetNext() : 0; // naechste Spalte, wenn vorhanden
//STRIP001  if( pBoss )
//STRIP001      pPage = NULL;
//STRIP001  else
//STRIP001  {
//STRIP001      if( pOldBoss->GetUpper()->IsSctFrm() )
//STRIP001      {   // Das kann nur in einem spaltigen Bereich sein
//STRIP001          SwLayoutFrm* pNxt = pOldBoss->GetNextSctLeaf( eMakePage );
//STRIP001          if( pNxt )
//STRIP001          {
//STRIP001              ASSERT( pNxt->IsColBodyFrm(), "GetNextFtnLeaf: Funny Leaf" );
//STRIP001              pBoss = (SwFtnBossFrm*)pNxt->GetUpper();
//STRIP001              pPage = pBoss->FindPageFrm();
//STRIP001          }
//STRIP001          else
//STRIP001              return 0;
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          // naechste Seite
//STRIP001          pPage = (SwPageFrm*)pOldPage->GetNext();
//STRIP001          // Leerseiten ueberspringen
//STRIP001          if( pPage && pPage->IsEmptyPage() )
//STRIP001              pPage = (SwPageFrm*)pPage->GetNext();
//STRIP001          pBoss = pPage;
//STRIP001      }
//STRIP001  }
//STRIP001  // Was haben wir jetzt?
//STRIP001  // pBoss != NULL, pPage==NULL => pBoss ist die auf der gleichen Seite folgende Spalte
//STRIP001  // pBoss != NULL, pPage!=NULL => pBoss und pPage sind die folgende Seite (Empty uebersprungen)
//STRIP001  // pBoss == NULL => pPage == NULL, es gibt keine folgende Seite
//STRIP001
//STRIP001  //Wenn die Fussnote bereits einen Follow hat brauchen wir nicht zu suchen.
//STRIP001  //Wenn allerdings zwischen Ftn und Follow unerwuenschte Leerseiten/spalten
//STRIP001  //herumlungern, so legen wir auf der naechstbesten Seite/Spalte einen weiteren
//STRIP001  //Follow an, der Rest wird sich schon finden.
//STRIP001  SwFtnFrm *pFtn = FindFtnFrm();
//STRIP001  if ( pFtn && pFtn->GetFollow() )
//STRIP001  {
//STRIP001      SwFtnBossFrm* pTmpBoss = pFtn->GetFollow()->FindFtnBossFrm();
//STRIP001      // Folgende Faelle werden hier erkannt und akzeptiert
//STRIP001      // 1. Die FtnBosse sind benachbarte Seiten oder benachbarte Spalten
//STRIP001      // 2. Der neue ist die erste Spalte der benachbarten Seite
//STRIP001      // 3. Der neue ist die erste Spalte in einem Bereich in der naechsten Spalte/Seite
//STRIP001      while( pTmpBoss != pBoss && pTmpBoss && !pTmpBoss->GetPrev() )
//STRIP001          pTmpBoss = pTmpBoss->GetUpper()->FindFtnBossFrm();
//STRIP001      if( pTmpBoss == pBoss )
//STRIP001          return pFtn->GetFollow();
//STRIP001  }
//STRIP001
//STRIP001  // Wenn wir keinen pBoss gefunden haben oder es sich um eine "falsche" Seite handelt,
//STRIP001  // muss eine neue Seite her
//STRIP001  if ( !pBoss || ( pPage && pPage->IsEndNotePage() && !pOldPage->IsEndNotePage() ) )
//STRIP001  {
//STRIP001      if ( eMakePage == MAKEPAGE_APPEND || eMakePage == MAKEPAGE_INSERT )
//STRIP001      {
//STRIP001          pBoss = InsertPage( pOldPage, pOldPage->IsFtnPage() );
//STRIP001          ((SwPageFrm*)pBoss)->SetEndNotePage( pOldPage->IsEndNotePage() );
//STRIP001      }
//STRIP001      else
//STRIP001          return 0;
//STRIP001  }
//STRIP001  if( pBoss->IsPageFrm() )
//STRIP001  {   // Wenn wir auf einer spaltigen Seite gelandet sind,
//STRIP001      // gehen wir in die erste Spalte
//STRIP001      SwLayoutFrm* pLay = pBoss->FindBodyCont();
//STRIP001      if( pLay && pLay->Lower() && pLay->Lower()->IsColumnFrm() )
//STRIP001          pBoss = (SwFtnBossFrm*)pLay->Lower();
//STRIP001  }
//STRIP001  //Seite/Spalte gefunden, da schummeln wir uns doch gleich mal 'rein
//STRIP001  SwFtnContFrm *pCont = pBoss->FindFtnCont();
//STRIP001  if ( !pCont && pBoss->GetMaxFtnHeight() &&
//STRIP001       ( eMakePage == MAKEPAGE_APPEND || eMakePage == MAKEPAGE_INSERT ) )
//STRIP001      pCont = pBoss->MakeFtnCont();
//STRIP001  return pCont;
//STRIP001 }

/*************************************************************************
|*
|*  SwFrm::GetPrevFtnLeaf()
|*
|*  Beschreibung        Liefert das vorhergehende LayoutBlatt in das der
|*      Frame gemoved werden kann.
|*  Ersterstellung      MA 16. Nov. 92
|*  Letzte Aenderung    AMA 06. Nov. 98
|*
|*************************************************************************/


//STRIP001 SwLayoutFrm *SwFrm::GetPrevFtnLeaf( MakePageType eMakeFtn )
//STRIP001 {
//STRIP001  //Der Vorgaenger fuer eine Fussnote ist falls moeglich der Master
//STRIP001  //in der Fussnoteneigenen Verkettung.
//STRIP001  SwLayoutFrm *pRet = 0;
//STRIP001  SwFtnFrm *pFtn = FindFtnFrm();
//STRIP001  pRet = pFtn->GetMaster();
//STRIP001
//STRIP001  SwFtnBossFrm* pOldBoss = FindFtnBossFrm();
//STRIP001  SwPageFrm *pOldPage = pOldBoss->FindPageFrm();
//STRIP001
//STRIP001  if ( !pOldBoss->GetPrev() && !pOldPage->GetPrev() )
//STRIP001      return pRet; // es gibt weder eine Spalte noch eine Seite vor uns
//STRIP001
//STRIP001  if ( !pRet )
//STRIP001  {
//STRIP001      BOOL bEndn = pFtn->GetAttr()->GetFtn().IsEndNote();
//STRIP001      SwFrm* pTmpRef = NULL;
//STRIP001      if( bEndn && pFtn->IsInSct() )
//STRIP001      {
//STRIP001          SwSectionFrm* pSect = pFtn->FindSctFrm();
//STRIP001          if( pSect->IsEndnAtEnd() )
//STRIP001              pTmpRef = pSect->FindLastCntnt( FINDMODE_LASTCNT );
//STRIP001      }
//STRIP001      if( !pTmpRef )
//STRIP001          pTmpRef = pFtn->GetRef();
//STRIP001      SwFtnBossFrm* pStop = pTmpRef->FindFtnBossFrm( !bEndn );
//STRIP001
//STRIP001      const USHORT nNum = pStop->GetPhyPageNum();
//STRIP001
//STRIP001      //Wenn die Fussnoten am Dokumentende angezeigt werden, so verlassen wir
//STRIP001      //die Entsprechenden Seiten nicht.
//STRIP001      //Selbiges gilt analog fuer die Endnotenseiten.
//STRIP001      const FASTBOOL bEndNote = pOldPage->IsEndNotePage();
//STRIP001      const FASTBOOL bFtnEndDoc = pOldPage->IsFtnPage();
//STRIP001      SwFtnBossFrm* pNxtBoss = pOldBoss;
//STRIP001      SwSectionFrm *pSect = pNxtBoss->GetUpper()->IsSctFrm() ?
//STRIP001                            (SwSectionFrm*)pNxtBoss->GetUpper() : 0;
//STRIP001
//STRIP001      do
//STRIP001      {
//STRIP001          if( pNxtBoss->IsColumnFrm() && pNxtBoss->GetPrev() )
//STRIP001              pNxtBoss = (SwFtnBossFrm*)pNxtBoss->GetPrev();  // eine Spalte zurueck
//STRIP001          else                                // oder eine Seite zurueck
//STRIP001          {
//STRIP001              SwLayoutFrm* pBody;
//STRIP001              if( pSect )
//STRIP001              {
//STRIP001                  if( pSect->IsFtnLock() )
//STRIP001                  {
//STRIP001                      if( pNxtBoss == pOldBoss )
//STRIP001                          return 0;
//STRIP001                      pStop = pNxtBoss;
//STRIP001                  }
//STRIP001                  else
//STRIP001                  {
//STRIP001                      pSect = pSect->FindMaster();
//STRIP001                      if( !pSect || !pSect->Lower() )
//STRIP001                          return 0;
//STRIP001                      ASSERT( pSect->Lower()->IsColumnFrm(),
//STRIP001                              "GetPrevFtnLeaf: Where's the column?" );
//STRIP001                      pNxtBoss = (SwFtnBossFrm*)pSect->Lower();
//STRIP001                      pBody = pSect;
//STRIP001                  }
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  SwPageFrm* pPage = (SwPageFrm*)pNxtBoss->FindPageFrm()->GetPrev();
//STRIP001                  if( !pPage || pPage->GetPhyPageNum() < nNum ||
//STRIP001                      bEndNote != pPage->IsEndNotePage() || bFtnEndDoc != pPage->IsFtnPage() )
//STRIP001                      return NULL; // Keine in Frage kommende Seite mehr gefunden
//STRIP001                  pNxtBoss = pPage;
//STRIP001                  pBody = pPage->FindBodyCont();
//STRIP001              }
//STRIP001              // Die vorherige Seite haben wir nun, ggf. sollten wir in die letzte Spalte
//STRIP001              // der Seite wechseln
//STRIP001              if( pBody )
//STRIP001              {
//STRIP001                  if ( pBody->Lower() && pBody->Lower()->IsColumnFrm() )
//STRIP001                  {
//STRIP001                      pNxtBoss = (SwFtnBossFrm*)pBody->Lower();
//STRIP001                      while( pNxtBoss->GetNext() ) // letzte Spalte suchen
//STRIP001                          pNxtBoss = (SwFtnBossFrm*)pNxtBoss->GetNext();
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001          SwFtnContFrm *pCont = pNxtBoss->FindFtnCont();
//STRIP001          if ( pCont )
//STRIP001          {
//STRIP001              pRet = pCont;
//STRIP001              break;
//STRIP001          }
//STRIP001          if ( pStop == pNxtBoss )
//STRIP001          {   //Die Seite/Spalte auf der sich auch die Referenz tummelt, ist erreicht.
//STRIP001              //Wir koennen jetzt probehalber mal einen Container erzeugen und
//STRIP001              //uns hineinpasten.
//STRIP001              if ( eMakeFtn == MAKEPAGE_FTN && pNxtBoss->GetMaxFtnHeight() )
//STRIP001                  pRet = pNxtBoss->MakeFtnCont();
//STRIP001              break;
//STRIP001          }
//STRIP001      } while( !pRet );
//STRIP001  }
//STRIP001  if ( pRet )
//STRIP001  {
//STRIP001      const SwFtnBossFrm* pNewBoss = pRet->FindFtnBossFrm();
//STRIP001      BOOL bJump = FALSE;
//STRIP001      if( pOldBoss->IsColumnFrm() && pOldBoss->GetPrev() ) // es gibt eine vorherige Spalte
//STRIP001          bJump = pOldBoss->GetPrev() != (SwFrm*)pNewBoss;         // sind wir darin gelandet?
//STRIP001      else if( pNewBoss->IsColumnFrm() && pNewBoss->GetNext() )
//STRIP001          bJump = TRUE; // es gibt hinter dem neuen Boss noch eine Spalte, die aber nicht
//STRIP001                        // der alte Boss sein kann, das haben wir ja bereits geprueft.
//STRIP001      else // hier landen wir nur, wenn neuer und alter Boss entweder Seiten oder letzte (neu)
//STRIP001      {   // bzw. erste (alt) Spalten einer Seite sind. In diesem Fall muss noch geprueft
//STRIP001          // werden, ob Seiten ueberspringen wurden.
//STRIP001          USHORT nDiff = pOldPage->GetPhyPageNum() - pRet->FindPageFrm()->GetPhyPageNum();
//STRIP001          if ( nDiff > 2 ||
//STRIP001               (nDiff > 1 && !((SwPageFrm*)pOldPage->GetPrev())->IsEmptyPage()) )
//STRIP001              bJump = TRUE;
//STRIP001      }
//STRIP001      if( bJump )
//STRIP001          SwFlowFrm::SetMoveBwdJump( TRUE );
//STRIP001  }
//STRIP001  return pRet;
//STRIP001 }

/*************************************************************************
|*
|*  SwFrm::IsFtnAllowed()
|*
|*  Ersterstellung      MA 22. Mar. 94
|*  Letzte Aenderung    MA 01. Dec. 94
|*
|*************************************************************************/


/*N*/ BOOL SwFrm::IsFtnAllowed() const
/*N*/ {
/*N*/   if ( !IsInDocBody() )
/*N*/       return FALSE;
/*N*/
/*N*/   if ( IsInTab() )
/*N*/   {
/*N*/       //Keine Ftns in wiederholten Headlines.
/*N*/       const SwTabFrm *pTab = ((SwFrm*)this)->ImplFindTabFrm();
/*N*/       if ( pTab->GetTable()->IsHeadlineRepeat() && pTab->IsFollow() )
/*N*/           return !((SwLayoutFrm*)pTab->Lower())->IsAnLower( this );
/*N*/   }
/*N*/   return TRUE;
/*N*/ }

/*************************************************************************
|*
|*  SwRootFrm::UpdateFtnNums()
|*
|*  Ersterstellung      MA 02. Mar. 93
|*  Letzte Aenderung    MA 09. Dec. 97
|*
|*************************************************************************/


//STRIP001 void SwRootFrm::UpdateFtnNums()
//STRIP001 {
//STRIP001  //Seitenweise Numerierung nur wenn es am Dokument so eingestellt ist.
//STRIP001  if ( GetFmt()->GetDoc()->GetFtnInfo().eNum == FTNNUM_PAGE )
//STRIP001  {
//STRIP001      SwPageFrm *pPage = (SwPageFrm*)Lower();
//STRIP001      while ( pPage && !pPage->IsFtnPage() )
//STRIP001      {
//STRIP001          pPage->UpdateFtnNum();
//STRIP001          pPage = (SwPageFrm*)pPage->GetNext();
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|*  RemoveFtns()        Entfernen aller Fussnoten (nicht etwa die Referenzen)
|*                      und Entfernen aller Fussnotenseiten.
|*
|*  Ersterstellung      MA 05. Dec. 97
|*  Letzte Aenderung    AMA 06. Nov. 98
|*
|*************************************************************************/

/*N*/ void lcl_RemoveFtns( SwFtnBossFrm* pBoss, BOOL bPageOnly, BOOL bEndNotes )
/*N*/ {
/*N*/   do
/*N*/   {
/*N*/       SwFtnContFrm *pCont = pBoss->FindFtnCont();
/*N*/       if ( pCont )
/*N*/       {
/*?*/           SwFtnFrm *pFtn = (SwFtnFrm*)pCont->Lower();
/*?*/           ASSERT( pFtn, "FtnCont ohne Ftn." );
/*?*/           if ( bPageOnly )
/*?*/               while ( pFtn->GetMaster() )
/*?*/                   pFtn = pFtn->GetMaster();
/*?*/           do
/*?*/           {
/*?*/               SwFtnFrm *pNxt = (SwFtnFrm*)pFtn->GetNext();
/*?*/               if ( !pFtn->GetAttr()->GetFtn().IsEndNote() ||
/*?*/                       bEndNotes )
/*?*/               {
/*?*/                   pFtn->GetRef()->Prepare( PREP_FTN, (void*)pFtn->GetAttr() );
/*?*/                   if ( bPageOnly && !pNxt )
/*?*/                       pNxt = pFtn->GetFollow();
/*?*/                   pFtn->Cut();
/*?*/                   delete pFtn;
/*?*/               }
/*?*/               pFtn = pNxt;
/*?*/
/*?*/           } while ( pFtn );
/*N*/       }
/*N*/         if( !pBoss->IsInSct() )
/*N*/       {
/*N*/           // A sectionframe with the Ftn/EndnAtEnd-flags may contain
/*N*/           // foot/endnotes. If the last lower frame of the bodyframe is
/*N*/           // a multicolumned sectionframe, it may contain footnotes, too.
/*N*/           SwLayoutFrm* pBody = pBoss->FindBodyCont();
/*N*/           if( pBody && pBody->Lower() )
/*N*/           {
/*N*/               SwFrm* pLow = pBody->Lower();
/*N*/               while( pLow->GetNext() )
/*N*/               {
/*N*/                   if( pLow->IsSctFrm() && ( !pLow->GetNext() ||
/*N*/                       ((SwSectionFrm*)pLow)->IsAnyNoteAtEnd() ) &&
/*N*/                       ((SwSectionFrm*)pLow)->Lower() &&
/*N*/                       ((SwSectionFrm*)pLow)->Lower()->IsColumnFrm() )
/*?*/                       lcl_RemoveFtns( (SwColumnFrm*)((SwSectionFrm*)pLow)->Lower(),
/*?*/                           bPageOnly, bEndNotes );
/*N*/                   pLow = pLow->GetNext();
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/       // noch 'ne Spalte?
/*N*/       pBoss = pBoss->IsColumnFrm() ? (SwColumnFrm*)pBoss->GetNext() : NULL;
/*N*/   } while( pBoss );
/*N*/ }

/*N*/ void SwRootFrm::RemoveFtns( SwPageFrm *pPage, BOOL bPageOnly, BOOL bEndNotes )
/*N*/ {
/*N*/   if ( !pPage )
/*?*/       pPage = (SwPageFrm*)Lower();
/*N*/
/*N*/   do
/*N*/   {   // Bei spaltigen Seiten muessen wir in allen Spalten aufraeumen
/*N*/       SwFtnBossFrm* pBoss;
/*N*/       SwLayoutFrm* pBody = pPage->FindBodyCont();
/*N*/       if( pBody && pBody->Lower() && pBody->Lower()->IsColumnFrm() )
/*N*/           pBoss = (SwFtnBossFrm*)pBody->Lower(); // die erste Spalte
/*N*/       else
/*N*/           pBoss = pPage; // keine Spalten
/*N*/       lcl_RemoveFtns( pBoss, bPageOnly, bEndNotes );
/*N*/       if ( !bPageOnly )
/*N*/       {
/*?*/           if ( pPage->IsFtnPage() &&
/*?*/                (!pPage->IsEndNotePage() || bEndNotes) )
/*?*/           {
/*?*/               SwFrm *pDel = pPage;
/*?*/               pPage = (SwPageFrm*)pPage->GetNext();
/*?*/               pDel->Cut();
/*?*/               delete pDel;
/*?*/           }
/*?*/           else
/*?*/               pPage = (SwPageFrm*)pPage->GetNext();
/*N*/       }
/*N*/       else
/*N*/           break;
/*N*/
/*?*/   } while ( pPage );
/*N*/ }

/*************************************************************************
|*
|*  SetFtnPageDescs()   Seitenvorlagen der Fussnotenseiten aendern
|*
|*  Ersterstellung      MA 11. Dec. 97
|*  Letzte Aenderung    MA 11. Dec. 97
|*
|*************************************************************************/

//STRIP001 void SwRootFrm::CheckFtnPageDescs( BOOL bEndNote )
//STRIP001 {
//STRIP001  SwPageFrm *pPage = (SwPageFrm*)Lower();
//STRIP001  while ( pPage && !pPage->IsFtnPage() )
//STRIP001      pPage = (SwPageFrm*)pPage->GetNext();
//STRIP001  while ( pPage && pPage->IsEndNotePage() != bEndNote )
//STRIP001      pPage = (SwPageFrm*)pPage->GetNext();
//STRIP001  if ( pPage )
//STRIP001      SwFrm::CheckPageDescs( pPage, FALSE );
//STRIP001 }


/*************************************************************************
|*
|*  SwFtnBossFrm::MakeFtnCont()
|*
|*  Ersterstellung      MA 25. Feb. 93
|*  Letzte Aenderung    AMA 29. Oct. 98
|*
|*************************************************************************/


/*N*/ SwFtnContFrm *SwFtnBossFrm::MakeFtnCont()
/*N*/ {
/*N*/   //Einfuegen eines Fussnotencontainers. Der Fussnotencontainer sitzt
/*N*/   //immer direkt hinter dem Bodytext.
/*N*/   //Sein FrmFmt ist immer das DefaultFrmFmt.
/*N*/
/*N*/ #ifndef PRODUCT
/*N*/   if ( FindFtnCont() )
/*?*/   {   ASSERT( !this, "Fussnotencontainer bereits vorhanden." );
/*?*/       return 0;
/*N*/   }
/*N*/ #endif
/*N*/
/*N*/   SwFtnContFrm *pNew = new SwFtnContFrm( GetFmt()->GetDoc()->GetDfltFrmFmt());
/*N*/   SwLayoutFrm *pLay = FindBodyCont();
/*N*/   pNew->Paste( this, pLay->GetNext() );
/*N*/   return pNew;
/*N*/ }

/*************************************************************************
|*
|*  SwFtnBossFrm::FindFtnCont()
|*
|*  Ersterstellung      MA 25. Feb. 93
|*  Letzte Aenderung    AMA 29. Oct. 98
|*
|*************************************************************************/


/*N*/ SwFtnContFrm *SwFtnBossFrm::FindFtnCont()
/*N*/ {
/*N*/   SwFrm *pFrm = Lower();
/*N*/   while( pFrm && !pFrm->IsFtnContFrm() )
/*N*/       pFrm = pFrm->GetNext();
/*N*/
/*N*/ #ifndef PRODUCT
/*N*/   if ( pFrm )
/*N*/   {
/*N*/       SwFrm *pFtn = pFrm->GetLower();
/*N*/       ASSERT( pFtn, "Cont ohne Fussnote." );
/*N*/       while ( pFtn )
/*N*/       {
/*N*/           ASSERT( pFtn->IsFtnFrm(), "Nachbar von Fussnote keine Fussnote." );
/*N*/           pFtn = pFtn->GetNext();
/*N*/       }
/*N*/   }
/*N*/ #endif
/*N*/
/*N*/   return (SwFtnContFrm*)pFrm;
/*N*/ }

/*************************************************************************
|*
|*  SwFtnBossFrm::FindNearestFtnCont()  Sucht den naechst greifbaren Fussnotencontainer.
|*
|*  Ersterstellung      MA 02. Aug. 93
|*  Letzte Aenderung    AMA 29. Oct. 98
|*
|*************************************************************************/

/*N*/ SwFtnContFrm *SwFtnBossFrm::FindNearestFtnCont( BOOL bDontLeave )
/*N*/ {
/*N*/   SwFtnContFrm *pCont = 0;
/*N*/   if ( GetFmt()->GetDoc()->GetFtnIdxs().Count() )
/*N*/   {
/*N*/       pCont = FindFtnCont();
/*N*/       if ( !pCont )
/*N*/       {
/*N*/           SwPageFrm *pPage = FindPageFrm();
/*N*/           SwFtnBossFrm* pBoss = this;
/*N*/           BOOL bEndNote = pPage->IsEndNotePage();
/*N*/           do
/*N*/           {
/*N*/               BOOL bChgPage = lcl_NextFtnBoss( pBoss, pPage, bDontLeave );
/*N*/               // Haben wir noch einen Boss gefunden? Bei einem Seitenwechsel muss
/*N*/               // zudem noch das EndNotenFlag uebereinstimmen
/*N*/               if( pBoss && ( !bChgPage || pPage->IsEndNotePage() == bEndNote ) )
/*N*/                   pCont = pBoss->FindFtnCont();
/*N*/           } while ( !pCont && pPage );
/*N*/       }
/*N*/   }
/*N*/   return pCont;
/*N*/ }


/*************************************************************************
|*
|*  SwFtnBossFrm::FindFirstFtn()
|*
|*  Beschreibung        Erste Fussnote des Fussnotenbosses suchen.
|*  Ersterstellung      MA 26. Feb. 93
|*  Letzte Aenderung    AMA 29. Oct. 99
|*
|*************************************************************************/


/*N*/ SwFtnFrm *SwFtnBossFrm::FindFirstFtn()
/*N*/ {
/*N*/   //Erstmal den naechsten FussnotenContainer suchen.
/*N*/   SwFtnContFrm *pCont = FindNearestFtnCont();
/*N*/   if ( !pCont )
/*N*/       return 0;
/*N*/
/*N*/   //Ab der ersten Fussnote im Container die erste suchen, die
/*N*/   //von der aktuellen Spalte (bzw. einspaltigen Seite) referenziert wird.
/*N*/
/*N*/   SwFtnFrm *pRet = (SwFtnFrm*)pCont->Lower();
/*N*/   const USHORT nRefNum = FindPageFrm()->GetPhyPageNum();
/*N*/   const USHORT nRefCol = lcl_ColumnNum( this );
/*N*/   USHORT nPgNum, nColNum; //Seitennummer, Spaltennummer
/*N*/   SwFtnBossFrm* pBoss;
/*N*/   SwPageFrm* pPage;
/*N*/   if( pRet )
/*N*/   {
/*N*/       pBoss = pRet->GetRef()->FindFtnBossFrm();
/*N*/       ASSERT( pBoss, "FindFirstFtn: No boss found" );
/*N*/       if( !pBoss )
/*?*/           return FALSE; // ´There must be a bug, but no GPF
/*N*/       pPage = pBoss->FindPageFrm();
/*N*/       nPgNum = pPage->GetPhyPageNum();
/*N*/       if ( nPgNum == nRefNum )
/*N*/       {
/*N*/           nColNum = lcl_ColumnNum( pBoss );
/*N*/           if( nColNum == nRefCol )
/*N*/               return pRet; //hat ihn.
/*?*/           else if( nColNum > nRefCol )
/*?*/               return NULL; //mind. eine Spalte zu weit.
/*?*/       }
/*?*/       else if ( nPgNum > nRefNum )
/*?*/           return NULL;    //mind. eine Seite zu weit.
/*?*/   }
/*?*/   else
/*?*/       return NULL;
/*?*/   // Ende, wenn Ref auf einer spaeteren Seite oder auf der gleichen Seite in einer
/*?*/   // spaeteren Spalte liegt
/*?*/
/*?*/   do
/*?*/   {
/*?*/       while ( pRet->GetFollow() )
/*?*/           pRet = pRet->GetFollow();
/*?*/
/*?*/       SwFtnFrm *pNxt = (SwFtnFrm*)pRet->GetNext();
/*?*/       if ( !pNxt )
/*?*/       {
/*?*/           pBoss = pRet->FindFtnBossFrm();
/*?*/           pPage = pBoss->FindPageFrm();
/*?*/           lcl_NextFtnBoss( pBoss, pPage, FALSE ); // naechster FtnBoss
/*?*/           pCont = pBoss ? pBoss->FindNearestFtnCont() : 0;
/*?*/           if ( pCont )
/*?*/               pNxt = (SwFtnFrm*)pCont->Lower();
/*?*/       }
/*?*/       if ( pNxt )
/*?*/       {
/*?*/           pRet = pNxt;
/*?*/           pBoss = pRet->GetRef()->FindFtnBossFrm();
/*?*/           pPage = pBoss->FindPageFrm();
/*?*/           nPgNum = pPage->GetPhyPageNum();
/*?*/           if ( nPgNum == nRefNum )
/*?*/           {
/*?*/               nColNum = lcl_ColumnNum( pBoss );
/*?*/               if( nColNum == nRefCol )
/*?*/                   break; //hat ihn.
/*?*/               else if( nColNum > nRefCol )
/*?*/                   pRet = 0; //mind. eine Spalte zu weit.
/*?*/           }
/*?*/           else if ( nPgNum > nRefNum )
/*?*/               pRet = 0;   //mind. eine Seite zu weit.
/*?*/       }
/*?*/       else
/*?*/           pRet = 0;   //Gibt eben keinen.
/*?*/   } while( pRet );
/*?*/   return pRet;
/*N*/ }

/*************************************************************************
|*
|*  SwFtnBossFrm::FindFirstFtn()
|*
|*  Beschreibunt        Erste Fussnote zum Cnt suchen.
|*  Ersterstellung      MA 04. Mar. 93
|*  Letzte Aenderung    AMA 28. Oct. 98
|*
|*************************************************************************/


/*N*/ const SwFtnFrm *SwFtnBossFrm::FindFirstFtn( SwCntntFrm *pCnt ) const
/*N*/ {
/*N*/   const SwFtnFrm *pRet = ((SwFtnBossFrm*)this)->FindFirstFtn();
/*N*/   if ( pRet )
/*N*/   {
/*N*/       const USHORT nColNum = lcl_ColumnNum( this ); //Spaltennummer
/*N*/       const USHORT nPageNum = GetPhyPageNum();
/*N*/       while ( pRet && (pRet->GetRef() != pCnt) )
/*N*/       {
/*?*/           while ( pRet->GetFollow() )
/*?*/               pRet = pRet->GetFollow();
/*?*/
/*?*/           if ( pRet->GetNext() )
/*?*/               pRet = (const SwFtnFrm*)pRet->GetNext();
/*?*/           else
/*?*/           {   SwFtnBossFrm *pBoss = (SwFtnBossFrm*)pRet->FindFtnBossFrm();
/*?*/               SwPageFrm *pPage = pBoss->FindPageFrm();
/*?*/               lcl_NextFtnBoss( pBoss, pPage, FALSE ); // naechster FtnBoss
/*?*/               SwFtnContFrm *pCont = pBoss ? pBoss->FindNearestFtnCont() : 0;
/*?*/               pRet = pCont ? (SwFtnFrm*)pCont->Lower() : 0;
/*?*/           }
/*?*/           if ( pRet )
/*?*/           {
/*?*/               const SwFtnBossFrm* pBoss = pRet->GetRef()->FindFtnBossFrm();
/*?*/               if( pBoss->GetPhyPageNum() != nPageNum ||
/*?*/                   nColNum != lcl_ColumnNum( pBoss ) )
/*?*/               pRet = 0;
/*?*/           }
/*N*/       }
/*N*/   }
/*N*/   return pRet;
/*N*/ }

/*************************************************************************
|*
|*  SwFtnBossFrm::ResetFtn()
|*
|*  Ersterstellung      MA 11. May. 95
|*  Letzte Aenderung    AMA 29. Oct. 98
|*
|*************************************************************************/


/*N*/ void SwFtnBossFrm::ResetFtn( const SwFtnFrm *pCheck )
/*N*/ {
/*N*/   //Vernichten der Inkarnationen von Fussnoten zum Attribut, wenn sie nicht
/*N*/   //zu pAssumed gehoeren.
/*N*/   ASSERT( !pCheck->GetMaster(), "Master not an Master." );
/*N*/
/*N*/   SwNodeIndex aIdx( *pCheck->GetAttr()->GetStartNode(), 1 );
/*N*/   SwCntntNode *pNd = aIdx.GetNode().GetCntntNode();
/*N*/   if ( !pNd )
/*?*/       pNd = pCheck->GetFmt()->GetDoc()->
/*?*/             GetNodes().GoNextSection( &aIdx, TRUE, FALSE );
/*N*/   SwClientIter aIter( *pNd );
/*N*/   SwClient* pLast = aIter.GoStart();
/*N*/   while( pLast )
/*N*/   {
/*N*/       if ( pLast->ISA(SwFrm) )
/*N*/       {
/*N*/           SwFrm *pFrm = (SwFrm*)pLast;
/*N*/           SwFrm *pTmp = pFrm->GetUpper();
/*N*/           while ( pTmp && !pTmp->IsFtnFrm() )
/*?*/               pTmp = pTmp->GetUpper();
/*N*/
/*N*/           SwFtnFrm *pFtn = (SwFtnFrm*)pTmp;
/*N*/           while ( pFtn && pFtn->GetMaster() )
/*?*/               pFtn = pFtn->GetMaster();
/*N*/           if ( pFtn != pCheck )
/*N*/           {
/*?*/               while ( pFtn )
/*?*/               {
/*?*/                   SwFtnFrm *pNxt = pFtn->GetFollow();
/*?*/                   pFtn->Cut();
/*?*/                   delete pFtn;
/*?*/                   pFtn = pNxt;
/*?*/               }
/*N*/           }
/*N*/       }
/*N*/       pLast = ++aIter;
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|*  SwFtnBossFrm::InsertFtn()
|*
|*  Ersterstellung      MA 26. Feb. 93
|*  Letzte Aenderung    AMA 29. Oct. 98
|*
|*************************************************************************/


/*N*/ void SwFtnBossFrm::InsertFtn( SwFtnFrm* pNew )
/*N*/ {
/*N*/ #if (OSL_DEBUG_LEVEL > 1) && !defined(PRODUCT)
/*N*/   static USHORT nStop = 0;
/*N*/   if ( nStop == pNew->GetFrmId() )
/*N*/   {
/*?*/       int bla = 5;
/*N*/   }
/*N*/ #endif
/*N*/   //Die Fussnote haben wir, sie muss jetzt nur noch irgendwo
/*N*/   //hin und zwar vor die Fussnote, deren Attribut vor das
/*N*/   //der neuen zeigt (Position wird ueber das Doc ermittelt)
/*N*/   //Gibt es in diesem Fussnotenboss noch keine Fussnoten, so muss eben ein
/*N*/   //Container erzeugt werden.
/*N*/   //Gibt es bereits einen Container aber noch keine Fussnote zu diesem
/*N*/   //Fussnotenboss, so muss die Fussnote hinter die letzte Fussnote der dichtesten
/*N*/   //Vorseite/spalte.
/*N*/
/*N*/   ResetFtn( pNew );
/*N*/   SwFtnFrm *pSibling = FindFirstFtn();
/*N*/   BOOL bDontLeave = FALSE;
/*N*/
/*N*/   // Ok, a sibling has been found, but is the sibling in an acceptable
/*N*/   // environment?
/*N*/   if( IsInSct() )
/*N*/   {
/*?*/       SwSectionFrm* pMySect = ImplFindSctFrm();
/*?*/       BOOL bEndnt = pNew->GetAttr()->GetFtn().IsEndNote();
/*?*/       if( bEndnt )
/*?*/       {
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 const SwSectionFmt* pEndFmt = pMySect->GetEndSectFmt();
//STRIP001 /*?*/            bDontLeave = 0 != pEndFmt;
//STRIP001 /*?*/            if( pSibling )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                if( pEndFmt )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    if( !pSibling->IsInSct() ||
//STRIP001 /*?*/                        !pSibling->ImplFindSctFrm()->IsDescendantFrom( pEndFmt ) )
//STRIP001 /*?*/                        pSibling = NULL;
//STRIP001 /*?*/                }
//STRIP001 /*?*/                else if( pSibling->IsInSct() )
//STRIP001 /*?*/                    pSibling = NULL;
//STRIP001 /*?*/            }
/*?*/       }
/*?*/       else
/*?*/       {
/*?*/           bDontLeave = pMySect->IsFtnAtEnd();
/*?*/           if( pSibling )
/*?*/           {
/*?*/               if( pMySect->IsFtnAtEnd() )
/*?*/               {
/*?*/                   if( !pSibling->IsInSct() ||
/*?*/                       !pMySect->IsAnFollow( pSibling->ImplFindSctFrm() ) )
/*?*/                       pSibling = NULL;
/*?*/               }
/*?*/               else if( pSibling->IsInSct() )
/*?*/                   pSibling = NULL;
/*?*/           }
/*?*/       }
/*N*/   }
/*N*/
/*N*/   if( pSibling && pSibling->FindPageFrm()->IsEndNotePage() !=
/*N*/       FindPageFrm()->IsEndNotePage() )
/*?*/       pSibling = NULL;
/*N*/
/*N*/   //Damit die Position herausgefunden werden kann.
/*N*/   SwDoc *pDoc = GetFmt()->GetDoc();
/*N*/   const ULONG nStPos = ::binfilter::lcl_FindFtnPos( pDoc, pNew->GetAttr() );
/*N*/
/*N*/   ULONG nCmpPos, nLastPos;
/*N*/   SwFtnContFrm *pParent = 0;
/*N*/   if( pSibling )
/*N*/   {
/*?*/       nCmpPos = ::binfilter::lcl_FindFtnPos( pDoc, pSibling->GetAttr() );
/*?*/       if( nCmpPos > nStPos )
/*?*/           pSibling = NULL;
/*N*/   }
/*N*/
/*N*/   if ( !pSibling )
/*N*/   {   pParent = FindFtnCont();
/*N*/       if ( !pParent )
/*N*/       {
/*N*/           //Es gibt noch keinen FussnotenContainer, also machen wir einen.
/*N*/           //HAAAAAAAALT! So einfach ist das leider mal wieder nicht: Es kann
/*N*/           //sein, dass irgendeine naechste Fussnote existiert die vor der
/*N*/           //einzufuegenden zu stehen hat, weil z.B. eine Fussnote ueber zig
/*N*/           //Seiten aufgespalten ist usw.
/*N*/           pParent = FindNearestFtnCont( bDontLeave );
/*N*/           if ( pParent )
/*N*/           {
/*?*/               SwFtnFrm *pFtn = (SwFtnFrm*)pParent->Lower();
/*?*/               if ( pFtn )
/*?*/               {
/*?*/
/*?*/                   nCmpPos = ::binfilter::lcl_FindFtnPos( pDoc, pFtn->GetAttr() );
/*?*/                   if ( nCmpPos > nStPos )
/*?*/                       pParent = 0;
/*?*/               }
/*?*/               else
/*?*/                   pParent = 0;
/*N*/           }
/*N*/       }
/*N*/       if ( !pParent )
/*N*/           //Jetzt kann aber ein Fussnotencontainer gebaut werden.
/*N*/           pParent = MakeFtnCont();
/*N*/       else
/*N*/       {
/*?*/           //Ausgehend von der ersten Fussnote unterhalb des Parents wird die
/*?*/           //erste Fussnote gesucht deren Index hinter dem Index der
/*?*/           //einzufuegenden liegt; vor dieser kann der neue dann gepastet
/*?*/           //werden.
/*?*/           pSibling = (SwFtnFrm*)pParent->Lower();
/*?*/           if ( !pSibling )
/*?*/           {   ASSERT( !this, "Keinen Platz fuer Fussnote gefunden.");
/*?*/               return;
/*?*/           }
/*?*/           nCmpPos  = ::binfilter::lcl_FindFtnPos( pDoc, pSibling->GetAttr() );
/*?*/
/*?*/           SwFtnBossFrm *pNxtB = this; //Immer den letzten merken, damit wir nicht
/*?*/           SwFtnFrm  *pLastSib = 0;    //ueber das Ziel hinausschiessen.
/*?*/
/*?*/           while ( pSibling && nCmpPos <= nStPos )
/*?*/           {
/*?*/               pLastSib = pSibling; // der kommt schon mal in Frage
/*?*/               nLastPos = nCmpPos;
/*?*/
/*?*/               while ( pSibling->GetFollow() )
/*?*/                   pSibling = pSibling->GetFollow();
/*?*/
/*?*/               if ( pSibling->GetNext() )
/*?*/               {
/*?*/                   pSibling = (SwFtnFrm*)pSibling->GetNext();
/*?*/                   ASSERT( !pSibling->GetMaster() || ( ENDNOTE > nStPos &&
/*?*/                           pSibling->GetAttr()->GetFtn().IsEndNote() ),
/*?*/                           "InsertFtn: Master expected I" );
/*?*/               }
/*?*/               else
/*?*/               {
/*?*/                   pNxtB = pSibling->FindFtnBossFrm();
/*?*/                   SwPageFrm *pSibPage = pNxtB->FindPageFrm();
/*?*/                   BOOL bEndNote = pSibPage->IsEndNotePage();
/*?*/                   BOOL bChgPage = lcl_NextFtnBoss( pNxtB, pSibPage, bDontLeave );
/*?*/                   // Bei Seitenwechsel muss das EndNoteFlag ueberprueft werden.
/*?*/                   SwFtnContFrm *pCont = pNxtB && ( !bChgPage ||
/*?*/                       pSibPage->IsEndNotePage() == bEndNote )
/*?*/                       ? pNxtB->FindNearestFtnCont( bDontLeave ) : 0;
/*?*/                   if( pCont )
/*?*/                       pSibling = (SwFtnFrm*)pCont->Lower();
/*?*/                   else // kein weiterer FtnContainer, dann werden  wir uns wohl hinter
/*?*/                       break; // pSibling haengen
/*?*/               }
/*?*/               if ( pSibling )
/*?*/               {
/*?*/                   nCmpPos = ::binfilter::lcl_FindFtnPos( pDoc, pSibling->GetAttr() );
/*?*/                   ASSERT( nCmpPos > nLastPos, "InsertFtn: Order of FtnFrm's buggy" );
/*?*/               }
/*?*/           }
/*?*/           // pLastSib ist jetzt die letzte Fussnote vor uns,
/*?*/           // pSibling leer oder die erste nach uns.
/*?*/           if ( pSibling && pLastSib && (pSibling != pLastSib) )
/*?*/           {   //Sind wir vielleicht bereits ueber das Ziel hinausgeschossen?
/*?*/               if ( nCmpPos > nStPos )
/*?*/                   pSibling = pLastSib;
/*?*/           }
/*?*/           else if ( !pSibling )
/*?*/           {   //Eine Chance haben wir noch: wir nehmen einfach die letzte
/*?*/               //Fussnote im Parent. Ein Sonderfall, der z.B. beim
/*?*/               //zurueckfliessen von Absaetzen mit mehreren Fussnoten
/*?*/               //vorkommt.
/*?*/               //Damit wir nicht die Reihenfolge verwuerfeln muessen wir den
/*?*/               //Parent der letzten Fussnote, die wir an der Hand hatten benutzen.
/*?*/               pSibling = pLastSib;
/*?*/               while( pSibling->GetFollow() )
/*?*/                   pSibling = pSibling->GetFollow();
/*?*/               ASSERT( !pSibling->GetNext(), "InsertFtn: Who's that guy?" );
/*?*/           }
/*N*/       }
/*N*/   }
/*N*/   else
/*N*/   {   //Die erste Fussnote der Spalte/Seite haben wir an der Hand, jetzt ausgehend
/*?*/       //von dieser die erste zur selben Spalte/Seite suchen deren Index hinter
/*?*/       //den uebergebenen zeigt, die letzte, die wir an der Hand hatten, ist
/*?*/       //dann der Vorgaenger.
/*?*/       SwFtnBossFrm* pBoss = pNew->GetRef()->FindFtnBossFrm(
/*?*/           !pNew->GetAttr()->GetFtn().IsEndNote() );
/*?*/       USHORT nRefNum = pBoss->GetPhyPageNum();    // Die Seiten- und
/*?*/       USHORT nRefCol = lcl_ColumnNum( pBoss );    // Spaltennummer der neuen Fussnote
/*?*/       BOOL bEnd = FALSE;
/*?*/       SwFtnFrm *pLastSib = 0;
/*?*/       while ( pSibling && !bEnd && (nCmpPos <= nStPos) )
/*?*/       {
/*?*/           pLastSib = pSibling;
/*?*/           nLastPos = nCmpPos;
/*?*/
/*?*/           while ( pSibling->GetFollow() )
/*?*/               pSibling = pSibling->GetFollow();
/*?*/
/*?*/           SwFtnFrm *pFoll = (SwFtnFrm*)pSibling->GetNext();
/*?*/           if ( pFoll )
/*?*/           {
/*?*/               pBoss = pSibling->GetRef()->FindFtnBossFrm( !pSibling->
/*?*/                                           GetAttr()->GetFtn().IsEndNote() );
/*?*/               USHORT nTmpRef;
/*?*/               if( nStPos >= ENDNOTE ||
/*?*/                   (nTmpRef = pBoss->GetPhyPageNum()) < nRefNum ||
/*?*/                   ( nTmpRef == nRefNum && lcl_ColumnNum( pBoss ) <= nRefCol ))
/*?*/                   pSibling = pFoll;
/*?*/               else
/*?*/                   bEnd = TRUE;
/*?*/           }
/*?*/           else
/*?*/           {
/*?*/               SwFtnBossFrm* pNxtB = pSibling->FindFtnBossFrm();
/*?*/               SwPageFrm *pSibPage = pNxtB->FindPageFrm();
/*?*/               BOOL bEndNote = pSibPage->IsEndNotePage();
/*?*/               BOOL bChgPage = lcl_NextFtnBoss( pNxtB, pSibPage, bDontLeave );
/*?*/               // Bei Seitenwechsel muss das EndNoteFlag ueberprueft werden.
/*?*/               SwFtnContFrm *pCont = pNxtB && ( !bChgPage ||
/*?*/                   pSibPage->IsEndNotePage() == bEndNote )
/*?*/                   ? pNxtB->FindNearestFtnCont( bDontLeave ) : 0;
/*?*/               if ( pCont )
/*?*/                   pSibling = (SwFtnFrm*)pCont->Lower();
/*?*/               else
/*?*/                   bEnd = TRUE;
/*?*/           }
/*?*/           if ( !bEnd && pSibling )
/*?*/               nCmpPos = ::binfilter::lcl_FindFtnPos( pDoc, pSibling->GetAttr() );
/*?*/           if ( pSibling && pLastSib && (pSibling != pLastSib) )
/*?*/           {   //Sind wir vielleicht bereits ueber das Ziel hinausgeschossen?
/*?*/               if ( (nLastPos < nCmpPos) && (nCmpPos > nStPos) )
/*?*/               {
/*?*/                   pSibling = pLastSib;
/*?*/                   bEnd = TRUE;
/*?*/               }
/*?*/           }
/*?*/       }
/*N*/   }
/*N*/   if ( pSibling )
/*N*/   {
/*?*/       nCmpPos = ::binfilter::lcl_FindFtnPos( pDoc, pSibling->GetAttr() );
/*?*/       if ( nCmpPos < nStPos )
/*?*/       {
/*?*/           while ( pSibling->GetFollow() )
/*?*/               pSibling = pSibling->GetFollow();
/*?*/           pParent = (SwFtnContFrm*)pSibling->GetUpper();
/*?*/           pSibling = (SwFtnFrm*)pSibling->GetNext();
/*?*/       }
/*?*/       else
/*?*/       {
/*?*/           if( pSibling->GetMaster() )
/*?*/           {
/*?*/               if( ENDNOTE > nCmpPos || nStPos >= ENDNOTE )
/*?*/               {
/*?*/                   ASSERT( FALSE, "InsertFtn: Master expected II" );
/*?*/                   do
/*?*/                       pSibling = pSibling->GetMaster();
/*?*/                   while ( pSibling->GetMaster() );
/*?*/               }
/*?*/           }
/*?*/           pParent = (SwFtnContFrm*)pSibling->GetUpper();
/*?*/       }
/*N*/   }
/*N*/   ASSERT( pParent, "paste in space?" );
/*N*/   pNew->Paste( pParent, pSibling );
/*N*/ }

/*************************************************************************
|*
|*  SwFtnBossFrm::AppendFtn()
|*
|*  Ersterstellung      MA 25. Feb. 93
|*  Letzte Aenderung    AMA 29. Oct. 98
|*
|*************************************************************************/


/*N*/ void SwFtnBossFrm::AppendFtn( SwCntntFrm *pRef, SwTxtFtn *pAttr )
/*N*/ {
/*N*/   //Wenn es die Fussnote schon gibt tun wir nix.
/*N*/   if ( FindFtn( pRef, pAttr ) )
/*?*/       return;
/*N*/
/*N*/   //Wenn Fussnoten am Dokumentende eingestellt sind, so brauchen wir 'eh erst
/*N*/   //ab der entsprechenden Seite zu suchen.
/*N*/   //Wenn es noch keine gibt, muss eben eine erzeugt werden.
/*N*/   //Wenn es sich um eine Endnote handelt, muss eine Endnotenseite gesucht
/*N*/   //bzw. erzeugt werden.
/*N*/   SwDoc *pDoc = GetFmt()->GetDoc();
/*N*/   SwFtnBossFrm *pBoss = this;
/*N*/   SwPageFrm *pPage = FindPageFrm();
/*N*/   SwPageFrm *pMyPage = pPage;
/*N*/   BOOL bChgPage = FALSE;
/*N*/   BOOL bEnd = FALSE;
/*N*/   if ( pAttr->GetFtn().IsEndNote() )
/*N*/   {
/*?*/       bEnd = TRUE;
/*?*/       if( GetUpper()->IsSctFrm() &&
/*?*/           ((SwSectionFrm*)GetUpper())->IsEndnAtEnd() )
/*?*/       {
/*?*/           SwFrm* pLast =
/*?*/               ((SwSectionFrm*)GetUpper())->FindLastCntnt( FINDMODE_ENDNOTE );
/*?*/           if( pLast )
/*?*/           {
/*?*/               pBoss = pLast->FindFtnBossFrm();
/*?*/               pPage = pBoss->FindPageFrm();
/*?*/           }
/*?*/       }
/*?*/       else
/*?*/       {
/*?*/           while ( pPage->GetNext() && !pPage->IsEndNotePage() )
/*?*/           {
/*?*/               pPage = (SwPageFrm*)pPage->GetNext();
/*?*/               bChgPage = TRUE;
/*?*/           }
/*?*/           if ( !pPage->IsEndNotePage() )
/*?*/           {
/*?*/               SwPageDesc *pDesc = pDoc->GetEndNoteInfo().GetPageDesc( *pDoc );
/*?*/               pPage = ::binfilter::InsertNewPage( *pDesc, pPage->GetUpper(),
/*?*/                       !pPage->OnRightPage(), FALSE, TRUE, 0 );
/*?*/               pPage->SetEndNotePage( TRUE );
/*?*/               bChgPage = TRUE;
/*?*/           }
/*?*/           else
/*?*/           {
/*?*/               //Wir koennen wenigstens schon mal ungefaehr die richtige Seite
/*?*/               //suchen. Damit stellen wir sicher das wir auch bei hunderten
/*?*/               //Fussnoten noch in endlicher Zeit fertig werden.
/*?*/               SwPageFrm *pNxt = (SwPageFrm*)pPage->GetNext();
/*?*/               const ULONG nStPos = ::binfilter::lcl_FindFtnPos( pDoc, pAttr );
/*?*/               while ( pNxt && pNxt->IsEndNotePage() )
/*?*/               {
/*?*/                   SwFtnContFrm *pCont = pNxt->FindFtnCont();
/*?*/                   if ( pCont && pCont->Lower() )
/*?*/                   {
/*?*/                       ASSERT( pCont->Lower()->IsFtnFrm(), "Keine Ftn im Container" );
/*?*/                       if ( nStPos > ::binfilter::lcl_FindFtnPos( pDoc,
/*?*/                                       ((SwFtnFrm*)pCont->Lower())->GetAttr()))
/*?*/                       {
/*?*/                           pPage = pNxt;
/*?*/                           pNxt = (SwPageFrm*)pPage->GetNext();
/*?*/                           continue;
/*?*/                       }
/*?*/                   }
/*?*/                   break;
/*?*/               }
/*?*/           }
/*?*/       }
/*N*/   }
/*N*/   else if( FTNPOS_CHAPTER == pDoc->GetFtnInfo().ePos && ( !GetUpper()->
/*N*/            IsSctFrm() || !((SwSectionFrm*)GetUpper())->IsFtnAtEnd() ) )
/*N*/   {
/*?*/       while ( pPage->GetNext() && !pPage->IsFtnPage() &&
/*?*/               !((SwPageFrm*)pPage->GetNext())->IsEndNotePage() )
/*?*/       {
/*?*/           pPage = (SwPageFrm*)pPage->GetNext();
/*?*/           bChgPage = TRUE;
/*?*/       }
/*?*/
/*?*/       if ( !pPage->IsFtnPage() )
/*?*/       {
/*?*/           SwPageDesc *pDesc = pDoc->GetFtnInfo().GetPageDesc( *pDoc );
/*?*/           pPage = ::binfilter::InsertNewPage( *pDesc, pPage->GetUpper(),
/*?*/               !pPage->OnRightPage(), FALSE, TRUE, pPage->GetNext() );
/*?*/           bChgPage = TRUE;
/*?*/       }
/*?*/       else
/*?*/       {
/*?*/           //Wir koennen wenigstens schon mal ungefaehr die richtige Seite
/*?*/           //suchen. Damit stellen wir sicher das wir auch bei hunderten
/*?*/           //Fussnoten noch in endlicher Zeit fertig werden.
/*?*/           SwPageFrm *pNxt = (SwPageFrm*)pPage->GetNext();
/*?*/           const ULONG nStPos = ::binfilter::lcl_FindFtnPos( pDoc, pAttr );
/*?*/           while ( pNxt && pNxt->IsFtnPage() && !pNxt->IsEndNotePage() )
/*?*/           {
/*?*/               SwFtnContFrm *pCont = pNxt->FindFtnCont();
/*?*/               if ( pCont && pCont->Lower() )
/*?*/               {
/*?*/                   ASSERT( pCont->Lower()->IsFtnFrm(), "Keine Ftn im Container" );
/*?*/                   if ( nStPos > ::binfilter::lcl_FindFtnPos( pDoc,
/*?*/                                       ((SwFtnFrm*)pCont->Lower())->GetAttr()))
/*?*/                   {
/*?*/                       pPage = pNxt;
/*?*/                       pNxt = (SwPageFrm*)pPage->GetNext();
/*?*/                       continue;
/*?*/                   }
/*?*/               }
/*?*/               break;
/*?*/           }
/*?*/       }
/*N*/   }
/*N*/
/*N*/   //Erstmal eine Fussnote und die benoetigten CntntFrms anlegen.
/*N*/   if ( !pAttr->GetStartNode() )
/*?*/   {   ASSERT( !this, "Kein Fussnoteninhalt." );
/*?*/       return;
/*N*/   }
/*N*/
/*N*/   // Wenn es auf der Seite/Spalte bereits einen FtnCont gibt,
/*N*/   // kann in einen spaltigen Bereich keiner erzeugt werden.
/*N*/   if( pBoss->IsInSct() && pBoss->IsColumnFrm() && !pPage->IsFtnPage() )
/*N*/   {
/*?*/       SwSectionFrm* pSct = pBoss->FindSctFrm();
/*?*/       if( bEnd ? !pSct->IsEndnAtEnd() : !pSct->IsFtnAtEnd() )
/*?*/       {
/*?*/           SwFtnContFrm* pFtnCont = pSct->FindFtnBossFrm(!bEnd)->FindFtnCont();
/*?*/           if( pFtnCont )
/*?*/           {
/*?*/               DBG_BF_ASSERT(0, "STRIP"); //STRIP001 SwFtnFrm* pTmp = (SwFtnFrm*)pFtnCont->Lower();
//STRIP001 /*?*/                if( bEnd )
//STRIP001 /*?*/                    while( pTmp && !pTmp->GetAttr()->GetFtn().IsEndNote() )
//STRIP001 /*?*/                        pTmp = (SwFtnFrm*)pTmp->GetNext();
//STRIP001 /*?*/                if( pTmp && *pTmp < pAttr )
//STRIP001 /*?*/                    return;
/*?*/           }
/*?*/       }
/*N*/   }
/*N*/
/*N*/   SwFtnFrm *pNew = new SwFtnFrm( pDoc->GetDfltFrmFmt(), pRef, pAttr );
/*N*/   {
/*N*/       SwNodeIndex aIdx( *pAttr->GetStartNode(), 1 );
/*N*/       ::binfilter::_InsertCnt( pNew, pDoc, aIdx.GetIndex() );
/*N*/   }
/*N*/   // Wenn die Seite gewechselt (oder gar neu angelegt) wurde,
/*N*/   // muessen wir uns dort in die erste Spalte setzen
/*N*/   if( bChgPage )
/*N*/   {
/*?*/       SwLayoutFrm* pBody = pPage->FindBodyCont();
/*?*/       ASSERT( pBody, "AppendFtn: NoPageBody?" );
/*?*/       if( pBody->Lower() && pBody->Lower()->IsColumnFrm() )
/*?*/           pBoss = (SwFtnBossFrm*)pBody->Lower();
/*?*/       else
/*?*/           pBoss = pPage; // bei nichtspaltigen Seiten auf die Seite selbst
/*N*/   }
/*N*/   pBoss->InsertFtn( pNew );
/*N*/   if ( pNew->GetUpper() )         //Eingesetzt oder nicht?
/*N*/   {
/*N*/       ::binfilter::RegistFlys( pNew->FindPageFrm(), pNew );
/*N*/       SwSectionFrm* pSect = FindSctFrm();
/*N*/       // Der Inhalt des FtnContainers in einem (spaltigen) Bereich
/*N*/       // braucht nur kalkuliert zu werden,
/*N*/       // wenn der Bereich bereits bis zur Unterkante seines Uppers geht.
/*N*/       if( pSect && !pSect->IsJoinLocked() && ( bEnd ? !pSect->IsEndnAtEnd() :
/*N*/           !pSect->IsFtnAtEnd() ) && pSect->Growable() )
/*?*/           pSect->InvalidateSize();
/*N*/       else
/*N*/       {
/*N*/           SwCntntFrm *pCnt = pNew->ContainsCntnt();
/*N*/           while ( pCnt && pCnt->FindFtnFrm()->GetAttr() == pAttr )
/*N*/           {
/*N*/               pCnt->Calc();
/*N*/               pCnt = (SwCntntFrm*)pCnt->FindNextCnt();
/*N*/           }
/*N*/       }
/*N*/       pMyPage->UpdateFtnNum();
/*N*/   }
/*N*/   else
/*?*/       delete pNew;
/*N*/ }
/*************************************************************************
|*
|*  SwFtnBossFrm::FindFtn()
|*
|*  Ersterstellung      MA 25. Feb. 93
|*  Letzte Aenderung    AMA 29. Oct. 98
|*
|*************************************************************************/


/*N*/ SwFtnFrm *SwFtnBossFrm::FindFtn( const SwCntntFrm *pRef, const SwTxtFtn *pAttr )
/*N*/ {
/*N*/   //Der einfachste und sicherste Weg geht ueber das Attribut.
/*N*/   ASSERT( pAttr->GetStartNode(), "FtnAtr ohne StartNode." );
/*N*/   SwNodeIndex aIdx( *pAttr->GetStartNode(), 1 );
/*N*/   SwCntntNode *pNd = aIdx.GetNode().GetCntntNode();
/*N*/   if ( !pNd )
/*N*/       pNd = pRef->GetAttrSet()->GetDoc()->
/*?*/             GetNodes().GoNextSection( &aIdx, TRUE, FALSE );
/*N*/   if ( !pNd )
/*?*/       return 0;
/*N*/   SwClientIter aIter( *pNd );
/*N*/   SwClient *pClient;
/*N*/   if ( 0 != (pClient = aIter.GoStart()) )
/*N*/       do
/*N*/       {
/*N*/           if ( pClient->IsA( TYPE(SwFrm) ) )
/*N*/           {
/*N*/               SwFrm *pFrm = ((SwFrm*)pClient)->GetUpper();
/*N*/               SwFtnFrm *pFtn = pFrm->FindFtnFrm();
/*N*/               if ( pFtn && pFtn->GetRef() == pRef )
/*N*/               {
/*N*/                   // The following condition becomes true, if the whole
/*N*/                   // footnotecontent is a section. While no frames exist,
/*N*/                   // the HiddenFlag of the section is set, this causes
/*N*/                   // the GoNextSection-function leaves the footnote.
/*N*/                   if( pFtn->GetAttr() != pAttr )
/*?*/                       return 0;
/*N*/                   while ( pFtn && pFtn->GetMaster() )
/*?*/                       pFtn = pFtn->GetMaster();
/*N*/                   return pFtn;
/*N*/               }
/*N*/           }
/*?*/       } while ( 0 != (pClient = aIter++) );
/*N*/
/*N*/   return 0;
/*N*/ }
/*************************************************************************
|*
|*  SwFtnBossFrm::RemoveFtn()
|*
|*  Ersterstellung      MA 25. Feb. 93
|*  Letzte Aenderung    AMA 29. Oct. 98
|*
|*************************************************************************/


/*N*/ void SwFtnBossFrm::RemoveFtn( const SwCntntFrm *pRef, const SwTxtFtn *pAttr,
/*N*/                             BOOL bPrep )
/*N*/ {
/*N*/   SwFtnFrm *pFtn = FindFtn( pRef, pAttr );
/*N*/   if( pFtn )
/*N*/   {
/*N*/       do
/*N*/       {
/*N*/           SwFtnFrm *pFoll = pFtn->GetFollow();
/*N*/           pFtn->Cut();
/*N*/           delete pFtn;
/*N*/           pFtn = pFoll;
/*N*/       } while ( pFtn );
/*N*/       if( bPrep && pRef->IsFollow() )
/*N*/       {
/*?*/           ASSERT( pRef->IsTxtFrm(), "NoTxtFrm has Footnote?" );
/*?*/           SwTxtFrm* pMaster = (SwTxtFrm*)pRef->FindMaster();
/*?*/           if( !pMaster->IsLocked() )
/*?*/               pMaster->Prepare( PREP_FTN_GONE );
/*N*/       }
/*N*/   }
/*N*/   FindPageFrm()->UpdateFtnNum();
/*N*/ }

/*************************************************************************
|*
|*  SwFtnBossFrm::ChangeFtnRef()
|*
|*  Ersterstellung      MA 25. Feb. 93
|*  Letzte Aenderung    AMA 29. Oct. 98
|*
|*************************************************************************/


//STRIP001 void SwFtnBossFrm::ChangeFtnRef( const SwCntntFrm *pOld, const SwTxtFtn *pAttr,
//STRIP001                               SwCntntFrm *pNew )
//STRIP001 {
//STRIP001  SwFtnFrm *pFtn = FindFtn( pOld, pAttr );
//STRIP001  while ( pFtn )
//STRIP001  {
//STRIP001      pFtn->SetRef( pNew );
//STRIP001      pFtn = pFtn->GetFollow();
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|*  SwFtnBossFrm::CollectFtns()
|*
|*  Ersterstellung      MA 24. Jul. 95
|*  Letzte Aenderung    AMA 29. Oct. 98
|*
|*************************************************************************/


/// OD 03.04.2003 #108446# - add parameter <_bCollectOnlyPreviousFtns> in
/// order to control, if only footnotes, which are positioned before the
/// footnote boss frame <this> have to be collected.
//STRIP001 void SwFtnBossFrm::CollectFtns( const SwCntntFrm* _pRef,
//STRIP001                                 SwFtnBossFrm*     _pOld,
//STRIP001                                 SvPtrarr&         _rFtnArr,
//STRIP001                                 const sal_Bool    _bCollectOnlyPreviousFtns )
//STRIP001 {
//STRIP001     SwFtnFrm *pFtn = _pOld->FindFirstFtn();
//STRIP001  while( !pFtn )
//STRIP001  {
//STRIP001         if( _pOld->IsColumnFrm() )
//STRIP001      {   // Spalten abklappern
//STRIP001             while ( !pFtn && _pOld->GetPrev() )
//STRIP001          {
//STRIP001              //Wenn wir keine Fussnote gefunden haben, ist noch nicht alles zu
//STRIP001              //spaet. Die Schleife wird beim Aufnehmen von Follow-Zeilen durch
//STRIP001              //Tabellen benoetigt. Fuer alle anderen Faelle ist sie in der Lage
//STRIP001              //'krumme' Verhaeltnisse zu korrigieren.
//STRIP001                 _pOld = (SwFtnBossFrm*)_pOld->GetPrev();
//STRIP001                 pFtn = _pOld->FindFirstFtn();
//STRIP001          }
//STRIP001      }
//STRIP001      if( !pFtn )
//STRIP001      {
//STRIP001          //  vorherige Seite
//STRIP001          SwPageFrm* pPg;
//STRIP001             for ( SwFrm* pTmp = _pOld;
//STRIP001                   0 != ( pPg = (SwPageFrm*)pTmp->FindPageFrm()->GetPrev())
//STRIP001                     && pPg->IsEmptyPage() ;
//STRIP001                 )
//STRIP001             {
//STRIP001              pTmp = pPg;
//STRIP001             }
//STRIP001          if( !pPg )
//STRIP001              return;
//STRIP001
//STRIP001          SwLayoutFrm* pBody = pPg->FindBodyCont();
//STRIP001          if( pBody->Lower() && pBody->Lower()->IsColumnFrm() )
//STRIP001          {   // mehrspaltige Seite => letzte Spalte suchen
//STRIP001                 _pOld = (SwFtnBossFrm*)pBody->Lower();
//STRIP001                 while ( _pOld->GetNext() )
//STRIP001                     _pOld = (SwFtnBossFrm*)_pOld->GetNext();
//STRIP001          }
//STRIP001          else
//STRIP001                 _pOld = pPg; // einspaltige Seite
//STRIP001             pFtn = _pOld->FindFirstFtn();
//STRIP001      }
//STRIP001  }
//STRIP001     // OD 03.04.2003 #108446# - consider new parameter <_bCollectOnlyPreviousFtns>
//STRIP001     SwFtnBossFrm* pRefBossFrm = NULL;
//STRIP001     if ( _bCollectOnlyPreviousFtns )
//STRIP001     {
//STRIP001         pRefBossFrm = this;
//STRIP001     }
//STRIP001     _CollectFtns( _pRef, pFtn, _rFtnArr, _bCollectOnlyPreviousFtns, pRefBossFrm );
//STRIP001 }


/*************************************************************************
|*
|*  SwFtnBossFrm::_CollectFtns()
|*
|*  Ersterstellung      MA 24. Jul. 95
|*  Letzte Aenderung    AMA 29. Oct. 98
|*
|*************************************************************************/
//STRIP001 inline void FtnInArr( SvPtrarr& rFtnArr, SwFtnFrm* pFtn )
//STRIP001 {
//STRIP001  if ( USHRT_MAX == rFtnArr.GetPos( (VoidPtr)pFtn ) )
//STRIP001      rFtnArr.Insert( (VoidPtr)pFtn, rFtnArr.Count() );
//STRIP001 }

/// OD 03.04.2003 #108446# - add parameters <_bCollectOnlyPreviousFtns> and
/// <_pRefFtnBossFrm> in order to control, if only footnotes, which are positioned
/// before the given reference footnote boss frame have to be collected.
/// Note: if parameter <_bCollectOnlyPreviousFtns> is true, then parameter
/// <_pRefFtnBossFrm> have to be referenced to an object.
/// Adjust parameter names.
//STRIP001 void SwFtnBossFrm::_CollectFtns( const SwCntntFrm*   _pRef,
//STRIP001                                  SwFtnFrm*           _pFtn,
//STRIP001                                  SvPtrarr&           _rFtnArr,
//STRIP001                                  sal_Bool            _bCollectOnlyPreviousFtns,
//STRIP001                                  const SwFtnBossFrm* _pRefFtnBossFrm)
//STRIP001 {
//STRIP001     // OD 03.04.2003 #108446# - assert, that no reference footnote boss frame
//STRIP001     // is set, in spite of the order, that only previous footnotes has to be
//STRIP001     // collected.
//STRIP001     ASSERT( !_bCollectOnlyPreviousFtns || _pRefFtnBossFrm,
//STRIP001             "<SwFtnBossFrm::_CollectFtns(..)> - No reference footnote boss frame for collecting only previous footnotes set.\nCrash will be caused!" );
//STRIP001
//STRIP001     //Alle Fussnoten die von pRef referenziert werden nacheinander
//STRIP001  //einsammeln (Attribut fuer Attribut), zusammengefuegen
//STRIP001  //(der Inhalt zu einem Attribut kann ueber mehrere Seiten verteilt sein)
//STRIP001  //und ausschneiden.
//STRIP001
//STRIP001  SvPtrarr aNotFtnArr( 20, 20 );  //Zur Robustheit werden hier die nicht
//STRIP001                                  //dazugehoerigen Fussnoten eingetragen.
//STRIP001                                  //Wenn eine Fussnote zweimal angefasst wird
//STRIP001                                  //ists vorbei! So kommt die Funktion auch
//STRIP001                                  //noch mit einem kaputten Layout
//STRIP001                                  //einigermassen (ohne Schleife und Absturz)
//STRIP001                                  //"klar".
//STRIP001
//STRIP001  //Hier sollte keiner mit einer Follow-Ftn ankommen, es sei denn er hat
//STRIP001  //ernste Absichten (:-)); spricht er kommt mit einer Ftn an die vor der
//STRIP001  //ersten der Referenz liegt.
//STRIP001     ASSERT( !_pFtn->GetMaster() || _pFtn->GetRef() != _pRef, "FollowFtn moven?" );
//STRIP001     while ( _pFtn->GetMaster() )
//STRIP001         _pFtn = _pFtn->GetMaster();
//STRIP001
//STRIP001  BOOL bFound = FALSE;
//STRIP001
//STRIP001     while ( _pFtn )
//STRIP001  {
//STRIP001      //Erstmal die naechste Fussnote der Spalte/Seite suchen, damit wir nicht
//STRIP001      //nach dem Cut jeder Fussnote von vorn anfangen muessen.
//STRIP001         SwFtnFrm *pNxtFtn = _pFtn;
//STRIP001      while ( pNxtFtn->GetFollow() )
//STRIP001          pNxtFtn = pNxtFtn->GetFollow();
//STRIP001      pNxtFtn = (SwFtnFrm*)pNxtFtn->GetNext();
//STRIP001
//STRIP001      if ( !pNxtFtn )
//STRIP001      {
//STRIP001             SwFtnBossFrm* pBoss = _pFtn->FindFtnBossFrm();
//STRIP001          SwPageFrm* pPage = pBoss->FindPageFrm();
//STRIP001          do
//STRIP001          {
//STRIP001              lcl_NextFtnBoss( pBoss, pPage, FALSE );
//STRIP001              if( pBoss )
//STRIP001              {
//STRIP001                  SwLayoutFrm* pCont = pBoss->FindFtnCont();
//STRIP001                  if( pCont )
//STRIP001                  {
//STRIP001                      pNxtFtn = (SwFtnFrm*)pCont->Lower();
//STRIP001                      if( pNxtFtn )
//STRIP001                      {
//STRIP001                          while( pNxtFtn->GetMaster() )
//STRIP001                              pNxtFtn = pNxtFtn->GetMaster();
//STRIP001                             if( pNxtFtn == _pFtn )
//STRIP001                              pNxtFtn = NULL;
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001          } while( !pNxtFtn && pBoss );
//STRIP001      }
//STRIP001      else if( !pNxtFtn->GetAttr()->GetFtn().IsEndNote() )
//STRIP001      {   ASSERT( !pNxtFtn->GetMaster(), "_CollectFtn: Master exspected" );
//STRIP001          while ( pNxtFtn->GetMaster() )
//STRIP001              pNxtFtn = pNxtFtn->GetMaster();
//STRIP001      }
//STRIP001         if ( pNxtFtn == _pFtn )
//STRIP001      {
//STRIP001          ASSERT( FALSE, "_CollectFtn: Devil's circle" );
//STRIP001          pNxtFtn = 0;
//STRIP001      }
//STRIP001
//STRIP001         // OD 03.04.2003 #108446# - determine, if found footnote has to be collected.
//STRIP001         sal_Bool bCollectFoundFtn = sal_False;
//STRIP001         if ( _pFtn->GetRef() == _pRef && !_pFtn->GetAttr()->GetFtn().IsEndNote() )
//STRIP001      {
//STRIP001             if ( _bCollectOnlyPreviousFtns )
//STRIP001             {
//STRIP001                 SwFtnBossFrm* pBossOfFoundFtn = _pFtn->FindFtnBossFrm( sal_True );
//STRIP001                 ASSERT( pBossOfFoundFtn,
//STRIP001                         "<SwFtnBossFrm::_CollectFtns(..)> - footnote boss frame of found footnote frame missing.\nWrong layout!" );
//STRIP001                 if ( !pBossOfFoundFtn ||    // don't crash, if no footnote boss is found.
//STRIP001                      pBossOfFoundFtn->IsBefore( _pRefFtnBossFrm )
//STRIP001                    )
//STRIP001                 {
//STRIP001                     bCollectFoundFtn = sal_True;
//STRIP001                 }
//STRIP001             }
//STRIP001             else
//STRIP001             {
//STRIP001                 bCollectFoundFtn = sal_True;
//STRIP001             }
//STRIP001         }
//STRIP001
//STRIP001         if ( bCollectFoundFtn )
//STRIP001         {
//STRIP001             ASSERT( !_pFtn->GetMaster(), "FollowFtn moven?" );
//STRIP001             SwFtnFrm *pNxt = _pFtn->GetFollow();
//STRIP001          while ( pNxt )
//STRIP001          {
//STRIP001              SwFrm *pCnt = pNxt->ContainsAny();
//STRIP001              if ( pCnt )
//STRIP001              {   //Unterwegs wird der Follow zerstoert weil er leer wird!
//STRIP001                  do
//STRIP001                  {   SwFrm *pNxtCnt = pCnt->GetNext();
//STRIP001                      pCnt->Cut();
//STRIP001                         pCnt->Paste( _pFtn );
//STRIP001                      pCnt = pNxtCnt;
//STRIP001                  } while ( pCnt );
//STRIP001              }
//STRIP001              else
//STRIP001              {   ASSERT( !pNxt, "Fussnote ohne Inhalt?" );
//STRIP001                  pNxt->Cut();
//STRIP001                  delete pNxt;
//STRIP001              }
//STRIP001                 pNxt = _pFtn->GetFollow();
//STRIP001          }
//STRIP001             _pFtn->Cut();
//STRIP001             FtnInArr( _rFtnArr, _pFtn );
//STRIP001          bFound = TRUE;
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001             FtnInArr( aNotFtnArr, _pFtn );
//STRIP001          if( bFound )
//STRIP001              break;
//STRIP001      }
//STRIP001      if ( pNxtFtn &&
//STRIP001              USHRT_MAX == _rFtnArr.GetPos( (VoidPtr)pNxtFtn ) &&
//STRIP001           USHRT_MAX == aNotFtnArr.GetPos( (VoidPtr)pNxtFtn ) )
//STRIP001             _pFtn = pNxtFtn;
//STRIP001      else
//STRIP001          break;
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|*  SwFtnBossFrm::_MoveFtns()
|*
|*  Ersterstellung      MA 26. Feb. 93
|*  Letzte Aenderung    AMA 29. Oct. 98
|*
|*************************************************************************/


//STRIP001 void SwFtnBossFrm::_MoveFtns( SvPtrarr &rFtnArr, BOOL bCalc )
//STRIP001 {
//STRIP001  //Alle Fussnoten die von pRef referenziert werden muessen von der
//STRIP001  //aktuellen Position, die sich durch die alte Spalte/Seite ergab, auf eine
//STRIP001  //neue Position, bestimmt durch die neue Spalte/Seite, gemoved werden.
//STRIP001  const USHORT nMyNum = FindPageFrm()->GetPhyPageNum();
//STRIP001  const USHORT nMyCol = lcl_ColumnNum( this );
//STRIP001     SWRECTFN( this )
//STRIP001
//STRIP001  for ( USHORT i = 0; i < rFtnArr.Count(); ++i )
//STRIP001  {
//STRIP001      SwFtnFrm *pFtn = (SwFtnFrm*)rFtnArr[i];
//STRIP001
//STRIP001      SwFtnBossFrm* pRefBoss = pFtn->GetRef()->FindFtnBossFrm( TRUE );
//STRIP001      if( pRefBoss != this )
//STRIP001      {
//STRIP001          const USHORT nRefNum = pRefBoss->FindPageFrm()->GetPhyPageNum();
//STRIP001          const USHORT nRefCol = lcl_ColumnNum( this );
//STRIP001          if( nRefNum < nMyNum || ( nRefNum == nMyNum && nRefCol <= nMyCol ) )
//STRIP001              pRefBoss = this;
//STRIP001      }
//STRIP001      pRefBoss->InsertFtn( pFtn );
//STRIP001
//STRIP001      if ( pFtn->GetUpper() ) //Robust, z.B. bei doppelten
//STRIP001      {
//STRIP001          // Damit FtnFrms, die nicht auf die Seite passen, nicht fuer zuviel
//STRIP001          // Unruhe sorgen (Loop 66312), wird ihr Inhalt zunaechst zusammengestaucht.
//STRIP001          // Damit wird der FtnCont erst gegrowt, wenn der Inhalt formatiert wird
//STRIP001          // und feststellt, dass er auf die Seite passt.
//STRIP001          SwFrm *pCnt = pFtn->ContainsAny();
//STRIP001          while( pCnt )
//STRIP001          {
//STRIP001              if( pCnt->IsLayoutFrm() )
//STRIP001              {
//STRIP001                  SwFrm* pTmp = ((SwLayoutFrm*)pCnt)->ContainsAny();
//STRIP001                  while( pTmp && ((SwLayoutFrm*)pCnt)->IsAnLower( pTmp ) )
//STRIP001                  {
//STRIP001                      pTmp->Prepare( PREP_MOVEFTN );
//STRIP001                         (pTmp->Frm().*fnRect->fnSetHeight)(0);
//STRIP001                         (pTmp->Prt().*fnRect->fnSetHeight)(0);
//STRIP001                      pTmp = pTmp->FindNext();
//STRIP001                  }
//STRIP001              }
//STRIP001              else
//STRIP001                  pCnt->Prepare( PREP_MOVEFTN );
//STRIP001                 (pCnt->Frm().*fnRect->fnSetHeight)(0);
//STRIP001                 (pCnt->Prt().*fnRect->fnSetHeight)(0);
//STRIP001              pCnt = pCnt->GetNext();
//STRIP001          }
//STRIP001             (pFtn->Frm().*fnRect->fnSetHeight)(0);
//STRIP001             (pFtn->Prt().*fnRect->fnSetHeight)(0);
//STRIP001          pFtn->Calc();
//STRIP001          pFtn->GetUpper()->Calc();
//STRIP001
//STRIP001          if( bCalc )
//STRIP001          {
//STRIP001              SwTxtFtn *pAttr = pFtn->GetAttr();
//STRIP001              pCnt = pFtn->ContainsAny();
//STRIP001                 BOOL bUnlock = !pFtn->IsBackMoveLocked();
//STRIP001              pFtn->LockBackMove();
//STRIP001
//STRIP001              while ( pCnt && pCnt->FindFtnFrm()->GetAttr() == pAttr )
//STRIP001              {
//STRIP001                  pCnt->_InvalidatePos();
//STRIP001                  pCnt->Calc();
//STRIP001                  if( pCnt->IsSctFrm() )
//STRIP001                  {   // Wenn es sich um einen nichtleeren Bereich handelt,
//STRIP001                      // iterieren wir auch ueber seinen Inhalt
//STRIP001                      SwFrm* pTmp = ((SwSectionFrm*)pCnt)->ContainsAny();
//STRIP001                      if( pTmp )
//STRIP001                          pCnt = pTmp;
//STRIP001                      else
//STRIP001                          pCnt = pCnt->FindNext();
//STRIP001                  }
//STRIP001                  else
//STRIP001                      pCnt = pCnt->FindNext();
//STRIP001              }
//STRIP001                 if( bUnlock )
//STRIP001                 {
//STRIP001                     pFtn->UnlockBackMove();
//STRIP001                     if( !pFtn->ContainsAny() && !pFtn->IsColLocked() )
//STRIP001                     {
//STRIP001                         pFtn->Cut();
//STRIP001                         delete pFtn;
//STRIP001                     }
//STRIP001                 }
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {   ASSERT( !pFtn->GetMaster() && !pFtn->GetFollow(),
//STRIP001                  "DelFtn und Master/Follow?" );
//STRIP001          delete pFtn;
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|*  SwFtnBossFrm::MoveFtns()
|*
|*  Ersterstellung      BP 05. Aug. 93
|*  Letzte Aenderung    AMA 29. Oct. 98
|*
|*************************************************************************/


//STRIP001 void SwFtnBossFrm::MoveFtns( const SwCntntFrm *pSrc, SwCntntFrm *pDest,
//STRIP001                           SwTxtFtn *pAttr )
//STRIP001 {
//STRIP001  if( ( GetFmt()->GetDoc()->GetFtnInfo().ePos == FTNPOS_CHAPTER &&
//STRIP001      (!GetUpper()->IsSctFrm() || !((SwSectionFrm*)GetUpper())->IsFtnAtEnd()))
//STRIP001      || pAttr->GetFtn().IsEndNote() )
//STRIP001      return;
//STRIP001
//STRIP001  ASSERT( this == pSrc->FindFtnBossFrm( TRUE ),
//STRIP001          "SwPageFrm::MoveFtns: source frame isn't on that FtnBoss" );
//STRIP001
//STRIP001  SwFtnFrm *pFtn = FindFirstFtn();
//STRIP001  if( pFtn )
//STRIP001  {
//STRIP001      ChangeFtnRef( pSrc, pAttr, pDest );
//STRIP001      SwFtnBossFrm *pDestBoss = pDest->FindFtnBossFrm( TRUE );
//STRIP001      ASSERT( pDestBoss, "+SwPageFrm::MoveFtns: no destination boss" );
//STRIP001      if( pDestBoss )     // robust
//STRIP001      {
//STRIP001          SvPtrarr aFtnArr( 5, 5 );
//STRIP001          pDestBoss->_CollectFtns( pDest, pFtn, aFtnArr );
//STRIP001          if ( aFtnArr.Count() )
//STRIP001          {
//STRIP001              pDestBoss->_MoveFtns( aFtnArr, TRUE );
//STRIP001              SwPageFrm* pSrcPage = FindPageFrm();
//STRIP001              SwPageFrm* pDestPage = pDestBoss->FindPageFrm();
//STRIP001              // Nur beim Seitenwechsel FtnNum Updaten
//STRIP001              if( pSrcPage != pDestPage )
//STRIP001              {
//STRIP001                  if( pSrcPage->GetPhyPageNum() > pDestPage->GetPhyPageNum() )
//STRIP001                      pSrcPage->UpdateFtnNum();
//STRIP001                  pDestPage->UpdateFtnNum();
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|*  SwFtnBossFrm::RearrangeFtns()
|*
|*  Ersterstellung      MA 20. Jan. 94
|*  Letzte Aenderung    AMA 29. Oct. 98
|*
|*************************************************************************/


/*N*/ void SwFtnBossFrm::RearrangeFtns( const SwTwips nDeadLine, const BOOL bLock,
/*N*/                                 const SwTxtFtn *pAttr )
/*N*/ {
/*N*/   //Alle Fussnoten der Spalte/Seite dergestalt anformatieren,
/*N*/   //dass sie ggf. die Spalte/Seite wechseln.
/*N*/
/*N*/   SwSaveFtnHeight aSave( this, nDeadLine );
/*N*/   SwFtnFrm *pFtn = FindFirstFtn();
/*N*/   if( pFtn && pFtn->GetPrev() && bLock )
/*N*/   {
/*?*/       SwFtnFrm* pFirst = (SwFtnFrm*)pFtn->GetUpper()->Lower();
/*?*/       SwFrm* pCntnt = pFirst->ContainsAny();
/*?*/       if( pCntnt )
/*?*/       {
/*?*/             BOOL bUnlock = !pFirst->IsBackMoveLocked();
/*?*/           pFirst->LockBackMove();
/*?*/           pFirst->Calc();
/*?*/           pCntnt->Calc();
/*?*/             if( bUnlock )
/*?*/                 pFirst->UnlockBackMove();
/*?*/       }
/*?*/       pFtn = FindFirstFtn();
/*N*/   }
/*N*/   SwDoc *pDoc = GetFmt()->GetDoc();
/*N*/   const ULONG nFtnPos = pAttr ? ::binfilter::lcl_FindFtnPos( pDoc, pAttr ) : 0;
/*N*/   SwFrm *pCnt = pFtn ? pFtn->ContainsAny() : 0;
/*N*/   if ( pCnt )
/*N*/   {
/*N*/       BOOL bMore = TRUE;
/*N*/       BOOL bStart = pAttr == 0; // wenn kein Attribut uebergeben wird, alle bearbeiten
/*N*/       do
/*N*/       {
/*N*/           if( !bStart )
/*N*/               bStart = ::binfilter::lcl_FindFtnPos( pDoc, pCnt->FindFtnFrm()->GetAttr() )
/*N*/                        == nFtnPos;
/*N*/           if( bStart )
/*N*/             {
/*N*/                 pCnt->_InvalidatePos();
/*N*/               pCnt->_InvalidateSize();
/*N*/               pCnt->Prepare( PREP_ADJUST_FRM );
/*N*/                 SwFtnFrm* pFtnFrm = pCnt->FindFtnFrm();
/*N*/                 // OD 30.10.2002 #97265# - invalidate position of footnote
/*N*/                 // frame, if it's below its footnote container, in order to
/*N*/                 // assure its correct position, probably calculating its previous
/*N*/                 // footnote frames.
/*N*/                 {
/*N*/                     SWRECTFN( this );
/*N*/                     SwFrm* aFtnContFrm = pFtnFrm->GetUpper();
/*N*/                     if ( (pFtnFrm->Frm().*fnRect->fnTopDist)((aFtnContFrm->*fnRect->fnGetPrtBottom)()) > 0 )
/*N*/                     {
/*N*/                         pFtnFrm->_InvalidatePos();
/*N*/                     }
/*N*/                 }
/*N*/                 if ( bLock )
/*N*/               {
/*N*/                     BOOL bUnlock = !pFtnFrm->IsBackMoveLocked();
/*N*/                     pFtnFrm->LockBackMove();
/*N*/                     pFtnFrm->Calc();
/*N*/                   pCnt->Calc();
/*N*/                     if( bUnlock )
/*N*/                     {
/*N*/                         pFtnFrm->UnlockBackMove();
/*N*/                         if( !pFtnFrm->Lower() &&
/*N*/                             !pFtnFrm->IsColLocked() )
/*N*/                         {
/*N*/                             pFtnFrm->Cut();
/*N*/                             delete pFtnFrm;
/*N*/                         }
/*N*/                     }
/*N*/               }
/*N*/               else
/*N*/               {
/*N*/                     pFtnFrm->Calc();
/*N*/                   pCnt->Calc();
/*N*/               }
/*N*/           }
/*N*/           SwSectionFrm *pDel = NULL;
/*N*/           if( pCnt->IsSctFrm() )
/*N*/           {
/*N*/               SwFrm* pTmp = ((SwSectionFrm*)pCnt)->ContainsAny();
/*N*/               if( pTmp )
/*N*/               {
/*N*/                   pCnt = pTmp;
/*N*/                   continue;
/*N*/               }
/*N*/               pDel = (SwSectionFrm*)pCnt;
/*N*/           }
/*N*/           if ( pCnt->GetNext() )
/*N*/               pCnt = pCnt->GetNext();
/*N*/           else
/*N*/           {
/*N*/               pCnt = pCnt->FindNext();
/*N*/               if ( pCnt )
/*N*/               {
/*N*/                   SwFtnFrm* pFtn = pCnt->FindFtnFrm();
/*N*/                   if( pFtn->GetRef()->FindFtnBossFrm(
/*N*/                       pFtn->GetAttr()->GetFtn().IsEndNote() ) != this )
/*N*/                       bMore = FALSE;
/*N*/               }
/*N*/               else
/*N*/                   bMore = FALSE;
/*N*/           }
/*N*/           if( pDel )
/*N*/           {
/*N*/               pDel->Cut();
/*N*/               delete pDel;
/*N*/           }
/*N*/           if ( bMore )
/*N*/           {
/*N*/               //Nicht weiter als bis zur angegebenen Fussnote, falls eine
/*N*/               //angegeben wurde.
/*N*/               if ( pAttr &&
/*N*/                    (::binfilter::lcl_FindFtnPos( pDoc,
/*N*/                                   pCnt->FindFtnFrm()->GetAttr()) > nFtnPos ) )
/*N*/                   bMore = FALSE;
/*N*/           }
/*N*/       } while ( bMore );
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|*  SwPageFrm::UpdateFtnNum()
|*
|*  Ersterstellung      MA 02. Mar. 93
|*  Letzte Aenderung    AMA 29. Oct. 98
|*
|*************************************************************************/

/*N*/ void SwPageFrm::UpdateFtnNum()
/*N*/ {
/*N*/   //Seitenweise Numerierung nur wenn es am Dokument so eingestellt ist.
/*N*/   if ( GetFmt()->GetDoc()->GetFtnInfo().eNum != FTNNUM_PAGE )
/*N*/       return;
/*?*/
/*?*/   SwLayoutFrm* pBody = FindBodyCont();
/*?*/   if( !pBody || !pBody->Lower() )
/*?*/       return;
/*?*/
/*?*/   SwCntntFrm* pCntnt = pBody->ContainsCntnt();
/*?*/   USHORT nNum = 0;
/*?*/
/*?*/   while( pCntnt && pCntnt->FindPageFrm() == this )
/*?*/   {
/*?*/       if( ((SwTxtFrm*)pCntnt)->HasFtn() )
/*?*/       {
/*?*/           SwFtnBossFrm* pBoss = pCntnt->FindFtnBossFrm( TRUE );
/*?*/           if( pBoss->GetUpper()->IsSctFrm() &&
/*?*/               ((SwSectionFrm*)pBoss->GetUpper())->IsOwnFtnNum() )
/*?*/               pCntnt = ((SwSectionFrm*)pBoss->GetUpper())->FindLastCntnt();
/*?*/           else
/*?*/           {
/*?*/               SwFtnFrm* pFtn = (SwFtnFrm*)pBoss->FindFirstFtn( pCntnt );
/*?*/               while( pFtn )
/*?*/               {
/*?*/                   SwTxtFtn* pTxtFtn = pFtn->GetAttr();
/*?*/                   if( !pTxtFtn->GetFtn().IsEndNote() &&
/*?*/                       !pTxtFtn->GetFtn().GetNumStr().Len() &&
/*?*/                       !pFtn->GetMaster() &&
/*?*/                       (pTxtFtn->GetFtn().GetNumber() != ++nNum) )
/*?*/                       pTxtFtn->SetNumber( nNum );
/*?*/                   if ( pFtn->GetNext() )
/*?*/                       pFtn = (SwFtnFrm*)pFtn->GetNext();
/*?*/                   else
/*?*/                   {
/*?*/                       SwFtnBossFrm* pBoss = pFtn->FindFtnBossFrm( TRUE );
/*?*/                       SwPageFrm* pPage = pBoss->FindPageFrm();
/*?*/                       pFtn = NULL;
/*?*/                       lcl_NextFtnBoss( pBoss, pPage, FALSE );
/*?*/                       if( pBoss )
/*?*/                       {
/*?*/                           SwFtnContFrm *pCont = pBoss->FindNearestFtnCont();
/*?*/                           if ( pCont )
/*?*/                               pFtn = (SwFtnFrm*)pCont->Lower();
/*?*/                       }
/*?*/                   }
/*?*/                   if( pFtn && pFtn->GetRef() != pCntnt )
/*?*/                       pFtn = NULL;
/*?*/               }
/*?*/           }
/*?*/       }
/*?*/       pCntnt = pCntnt->FindNextCnt();
/*?*/   }
/*N*/ }

/*************************************************************************
|*
|*  SwFtnBossFrm::SetFtnDeadLine()
|*
|*  Ersterstellung      MA 02. Aug. 93
|*  Letzte Aenderung    MA 16. Nov. 98
|*
|*************************************************************************/

/*N*/ void SwFtnBossFrm::SetFtnDeadLine( const SwTwips nDeadLine )
/*N*/ {
/*N*/   SwFrm *pBody = FindBodyCont();
/*N*/   pBody->Calc();
/*N*/
/*N*/   SwFrm *pCont = FindFtnCont();
/*N*/   const SwTwips nMax = nMaxFtnHeight;//Aktuelle MaxHeight nicht ueberschreiten.
/*N*/     SWRECTFN( this )
/*N*/   if ( pCont )
/*N*/   {
/*N*/       pCont->Calc();
/*N*/         nMaxFtnHeight = -(pCont->Frm().*fnRect->fnBottomDist)( nDeadLine );
/*N*/   }
/*N*/   else
/*N*/         nMaxFtnHeight = -(pBody->Frm().*fnRect->fnBottomDist)( nDeadLine );
/*N*/
/*N*/   if ( GetFmt()->GetDoc()->IsBrowseMode() )
/*?*/         nMaxFtnHeight += pBody->Grow( LONG_MAX PHEIGHT, TRUE );
/*N*/   if ( IsInSct() )
/*?*/         nMaxFtnHeight += FindSctFrm()->Grow( LONG_MAX PHEIGHT, TRUE );
/*N*/
/*N*/   if ( nMaxFtnHeight < 0 )
/*N*/       nMaxFtnHeight = 0;
/*N*/   if ( nMax != LONG_MAX && nMaxFtnHeight > nMax )
/*N*/       nMaxFtnHeight = nMax;
/*N*/ }

/*************************************************************************
|*
|*  SwFtnBossFrm::GetVarSpace()
|*
|*  Ersterstellung      MA 03. Apr. 95
|*  Letzte Aenderung    MA 16. Nov. 98
|*
|*************************************************************************/
/*N*/ SwTwips SwFtnBossFrm::GetVarSpace() const
/*N*/ {
/*N*/   //Fuer Seiten soll ein Wert von 20% der Seitenhoehe nicht unterschritten
/*N*/   //werden (->AMA: was macht MS da?)
/*N*/   //->AMA: Was ist da fuer Bereiche sinnvoll (und kompatibel zu MS ;-)?
/*N*/   //AMA: MS kennt scheinbar kein Begrenzung, die Fussnoten nehmen durchaus
/*N*/   // die ganze Seite/Spalte ein.
/*N*/
/*N*/   const SwPageFrm* pPg = FindPageFrm();
/*N*/   ASSERT( pPg, "Footnote lost page" );
/*N*/
/*N*/   const SwFrm *pBody = FindBodyCont();
/*N*/   SwTwips nRet;
/*N*/   if( pBody )
/*N*/   {
/*N*/         SWRECTFN( this )
/*N*/       if( IsInSct() )
/*N*/       {
/*?*/           nRet = 0;
/*?*/             SwTwips nTmp = (*fnRect->fnYDiff)( (pBody->*fnRect->fnGetPrtTop)(),
/*?*/                                                (Frm().*fnRect->fnGetTop)() );
/*?*/           const SwSectionFrm* pSect = FindSctFrm();
/*?*/           //  Endnotes in a ftncontainer causes a deadline:
/*?*/           // the bottom of the last contentfrm
/*?*/           if( pSect->IsEndnAtEnd() ) // endnotes allowed?
/*?*/           {
/*?*/               ASSERT( !Lower() || !Lower()->GetNext() || Lower()->GetNext()->
/*?*/                       IsFtnContFrm(), "FtnContainer exspected" );
/*?*/               const SwFtnContFrm* pCont = Lower() ?
/*?*/                   (SwFtnContFrm*)Lower()->GetNext() : 0;
/*?*/               if( pCont )
/*?*/               {
/*?*/                   SwFtnFrm* pFtn = (SwFtnFrm*)pCont->Lower();
/*?*/                   while( pFtn)
/*?*/                   {
/*?*/                       if( pFtn->GetAttr()->GetFtn().IsEndNote() )
/*?*/                       { // endnote found
/*?*/                           SwFrm* pFrm = ((SwLayoutFrm*)Lower())->Lower();
/*?*/                           if( pFrm )
/*?*/                           {
/*?*/                               while( pFrm->GetNext() )
/*?*/                                   pFrm = pFrm->GetNext(); // last cntntfrm
/*?*/                                 nTmp += (*fnRect->fnYDiff)(
/*?*/                                          (Frm().*fnRect->fnGetTop)(),
/*?*/                                          (pFrm->Frm().*fnRect->fnGetBottom)() );
/*?*/                           }
/*?*/                           break;
/*?*/                       }
/*?*/                       pFtn = (SwFtnFrm*)pFtn->GetNext();
/*?*/                   }
/*?*/               }
/*?*/           }
/*?*/           if( nTmp < nRet )
/*?*/               nRet = nTmp;
/*?*/       }
/*N*/       else
/*N*/             nRet = - (pPg->Prt().*fnRect->fnGetHeight)()/5;
/*N*/         nRet += (pBody->Frm().*fnRect->fnGetHeight)();
/*N*/       if( nRet < 0 )
/*?*/           nRet = 0;
/*N*/   }
/*N*/   else
/*?*/       nRet = 0;
/*N*/   if ( IsPageFrm() && GetFmt()->GetDoc()->IsBrowseMode() )
/*?*/       nRet += BROWSE_HEIGHT - Frm().Height();
/*N*/   return nRet;
/*N*/ }

/*************************************************************************
|*
|*  SwFtnBossFrm::NeighbourhoodAdjustment(SwFrm*)
|*
|*  gibt Auskunft, ob die Groessenveraenderung von pFrm von AdjustNeighbourhood(...)
|*  oder von Grow/Shrink(..) verarbeitet werden sollte.
|*  Bei einem PageFrm oder in Spalten direkt unterhalb der Seite muss AdjustNei..
|*  gerufen werden, in Rahmenspalten Grow/Shrink.
|*  Spannend sind die spaltigen Bereiche: Wenn es in der Spalte einen Fussnotencontainer
|*  gibt und die Fussnoten nicht vom Bereich eingesammelt werden, ist ein Adjust..,
|*  ansonsten ein Grow/Shrink notwendig.
|*
|*  Ersterstellung      AMA 09. Dec 98
|*  Letzte Aenderung    AMA 09. Dec 98
|*
|*************************************************************************/

/*N*/ BYTE SwFtnBossFrm::_NeighbourhoodAdjustment( const SwFrm* pFrm ) const
/*N*/ {
/*N*/   BYTE nRet = NA_ONLY_ADJUST;
/*N*/   if( GetUpper() && !GetUpper()->IsPageBodyFrm() )
/*N*/   {
/*N*/       // Spaltige Rahmen erfordern Grow/Shrink
/*N*/       if( GetUpper()->IsFlyFrm() )
/*N*/           nRet = NA_GROW_SHRINK;
/*N*/       else
/*N*/       {
/*?*/           ASSERT( GetUpper()->IsSctFrm(), "NeighbourhoodAdjustment: Unexspected Upper" );
/*?*/           if( !GetNext() && !GetPrev() )
/*?*/               nRet = NA_GROW_ADJUST; // section with a single column (FtnAtEnd)
/*?*/           else
/*?*/           {
/*?*/               const SwFrm* pTmp = Lower();
/*?*/               ASSERT( pTmp, "NeighbourhoodAdjustment: Missing Lower()" );
/*?*/               if( !pTmp->GetNext() )
/*?*/                   nRet = NA_GROW_SHRINK;
/*?*/               else if( !GetUpper()->IsColLocked() )
/*?*/                   nRet = NA_ADJUST_GROW;
/*?*/               ASSERT( !pTmp->GetNext() || pTmp->GetNext()->IsFtnContFrm(),
/*?*/                       "NeighbourhoodAdjustment: Who's that guy?" );
/*?*/           }
/*N*/       }
/*N*/   }
/*N*/   return nRet;
/*N*/ }

/*************************************************************************
|*
|*  SwPageFrm::SetColMaxFtnHeight()
|*
|*  Ersterstellung      AMA 29. Oct 98
|*  Letzte Aenderung    AMA 29. Oct 98
|*
|*************************************************************************/
//STRIP001 void SwPageFrm::SetColMaxFtnHeight()
//STRIP001 {
//STRIP001  SwLayoutFrm *pBody = FindBodyCont();
//STRIP001  if( pBody && pBody->Lower() && pBody->Lower()->IsColumnFrm() )
//STRIP001  {
//STRIP001      SwColumnFrm* pCol = (SwColumnFrm*)pBody->Lower();
//STRIP001      do
//STRIP001      {
//STRIP001          pCol->SetMaxFtnHeight( GetMaxFtnHeight() );
//STRIP001          pCol = (SwColumnFrm*)pCol->GetNext();
//STRIP001      } while ( pCol );
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|*  SwLayoutFrm::MoveLowerFtns
|*
|*  Ersterstellung      MA 01. Sep. 94
|*  Letzte Aenderung    MA 05. Sep. 95
|*
|*************************************************************************/


/*N*/ BOOL SwLayoutFrm::MoveLowerFtns( SwCntntFrm *pStart, SwFtnBossFrm *pOldBoss,
/*N*/                                SwFtnBossFrm *pNewBoss, const BOOL bFtnNums )
/*N*/ {
/*N*/   SwDoc *pDoc = GetFmt()->GetDoc();
/*N*/   if ( !pDoc->GetFtnIdxs().Count() )
/*N*/       return FALSE;
/*?*/   if( pDoc->GetFtnInfo().ePos == FTNPOS_CHAPTER &&
/*?*/       ( !IsInSct() || !FindSctFrm()->IsFtnAtEnd() ) )
/*?*/       return TRUE;
/*?*/
/*?*/   if ( !pNewBoss )
/*?*/       pNewBoss = FindFtnBossFrm( TRUE );
/*?*/   if ( pNewBoss == pOldBoss )
/*?*/       return FALSE;
/*?*/
/*?*/   DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001 BOOL bMoved = FALSE;
//STRIP001 /*?*/    if( !pStart )
//STRIP001 /*?*/        pStart = ContainsCntnt();
//STRIP001 /*?*/
//STRIP001 /*?*/    SvPtrarr aFtnArr( 5, 5 );
//STRIP001 /*?*/
//STRIP001 /*?*/    while ( IsAnLower( pStart ) )
//STRIP001 /*?*/    {
//STRIP001 /*?*/        if ( ((SwTxtFrm*)pStart)->HasFtn() )
//STRIP001 /*?*/         {
//STRIP001 /*?*/             // OD 03.04.2003 #108446# - To avoid unnecessary moves of footnotes
//STRIP001 /*?*/             // use new parameter <_bCollectOnlyPreviousFtn> (4th parameter of
//STRIP001 /*?*/             // method <SwFtnBossFrm::CollectFtn(..)>) to control, that only
//STRIP001 /*?*/             // footnotes have to be collected, that are positioned before the
//STRIP001 /*?*/             // new dedicated footnote boss frame.
//STRIP001 /*?*/             pNewBoss->CollectFtns( pStart, pOldBoss, aFtnArr, sal_True );
//STRIP001 /*?*/         }
//STRIP001 /*?*/        pStart = pStart->GetNextCntntFrm();
//STRIP001 /*?*/    }
//STRIP001 /*?*/
//STRIP001 /*?*/    ASSERT( pOldBoss->IsInSct() == pNewBoss->IsInSct(),
//STRIP001 /*?*/            "MoveLowerFtns: Section confusion" );
//STRIP001 /*?*/    SvPtrarr *pFtnArr;
//STRIP001 /*?*/    SwLayoutFrm *pNewChief, *pOldChief;
//STRIP001 /*?*/    if( pStart && pOldBoss->IsInSct() && ( pOldChief = pOldBoss->FindSctFrm() )
//STRIP001 /*?*/        != ( pNewChief = pNewBoss->FindSctFrm() ) )
//STRIP001 /*?*/    {
//STRIP001 /*?*/        pFtnArr = new SvPtrarr( 5, 5 );
//STRIP001 /*?*/        pOldChief = pOldBoss->FindFtnBossFrm( TRUE );
//STRIP001 /*?*/        pNewChief = pNewBoss->FindFtnBossFrm( TRUE );
//STRIP001 /*?*/        while( pOldChief->IsAnLower( pStart ) )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            if ( ((SwTxtFrm*)pStart)->HasFtn() )
//STRIP001 /*?*/                ((SwFtnBossFrm*)pNewChief)->CollectFtns( pStart,
//STRIP001 /*?*/                                        (SwFtnBossFrm*)pOldBoss, *pFtnArr );
//STRIP001 /*?*/            pStart = pStart->GetNextCntntFrm();
//STRIP001 /*?*/        }
//STRIP001 /*?*/        if( !pFtnArr->Count() )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            delete pFtnArr;
//STRIP001 /*?*/            pFtnArr = NULL;
//STRIP001 /*?*/        }
//STRIP001 /*?*/    }
//STRIP001 /*?*/    else
//STRIP001 /*?*/        pFtnArr = NULL;
//STRIP001 /*?*/
//STRIP001 /*?*/    if ( aFtnArr.Count() || pFtnArr )
//STRIP001 /*?*/    {
//STRIP001 /*?*/        if( aFtnArr.Count() )
//STRIP001 /*?*/            pNewBoss->_MoveFtns( aFtnArr, TRUE );
//STRIP001 /*?*/        if( pFtnArr )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            ((SwFtnBossFrm*)pNewChief)->_MoveFtns( *pFtnArr, TRUE );
//STRIP001 /*?*/            delete pFtnArr;
//STRIP001 /*?*/        }
//STRIP001 /*?*/        bMoved = TRUE;
//STRIP001 /*?*/
//STRIP001 /*?*/        // Nur bei einem Seitenwechsel muss die FtnNum neu berechnet werden
//STRIP001 /*?*/        if ( bFtnNums )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            SwPageFrm* pOldPage = pOldBoss->FindPageFrm();
//STRIP001 /*?*/            SwPageFrm* pNewPage =pNewBoss->FindPageFrm();
//STRIP001 /*?*/            if( pOldPage != pNewPage )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                pOldPage->UpdateFtnNum();
//STRIP001 /*?*/                pNewPage->UpdateFtnNum();
//STRIP001 /*?*/            }
//STRIP001 /*?*/        }
//STRIP001 /*?*/    }
//STRIP001 /*?*/    return bMoved;
/*N*/ }

/*************************************************************************
|*
|*  SwLayoutFrm::MoveFtnCntFwd()
|*
|*  Ersterstellung      MA 24. Nov. 94
|*  Letzte Aenderung    MA 15. Jun. 95
|*
|*************************************************************************/


//STRIP001 BOOL SwCntntFrm::MoveFtnCntFwd( BOOL bMakePage, SwFtnBossFrm *pOldBoss )
//STRIP001 {
//STRIP001  ASSERT( IsInFtn(), "Keine Ftn." );
//STRIP001  SwLayoutFrm *pFtn = FindFtnFrm();
//STRIP001
//STRIP001  // The first paragraph in the first footnote in the first column in the
//STRIP001  // sectionfrm at the top of the page has not to move forward, if the
//STRIP001  // columnbody is empty.
//STRIP001  if( pOldBoss->IsInSct() && !pOldBoss->GetIndPrev() && !GetIndPrev() &&
//STRIP001      !pFtn->GetPrev() )
//STRIP001  {
//STRIP001      SwLayoutFrm* pBody = pOldBoss->FindBodyCont();
//STRIP001      if( !pBody || !pBody->Lower() )
//STRIP001          return TRUE;
//STRIP001  }
//STRIP001
//STRIP001  //fix(9538): Wenn die Ftn noch Nachbarn hinter sich hat, so muessen
//STRIP001  //diese ersteinmal verschwinden.
//STRIP001  SwLayoutFrm *pNxt = (SwLayoutFrm*)pFtn->GetNext();
//STRIP001  SwLayoutFrm *pLst = 0;
//STRIP001  while ( pNxt )
//STRIP001  {
//STRIP001      while ( pNxt->GetNext() )
//STRIP001          pNxt = (SwLayoutFrm*)pNxt->GetNext();
//STRIP001      if ( pNxt == pLst )
//STRIP001          pNxt = 0;
//STRIP001      else
//STRIP001      {   pLst = pNxt;
//STRIP001          SwCntntFrm *pCnt = pNxt->ContainsCntnt();
//STRIP001          if( pCnt )
//STRIP001              pCnt->MoveFtnCntFwd( TRUE, pOldBoss );
//STRIP001          pNxt = (SwLayoutFrm*)pFtn->GetNext();
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  BOOL bSamePage = TRUE;
//STRIP001  SwLayoutFrm *pNewUpper =
//STRIP001              GetLeaf( bMakePage ? MAKEPAGE_INSERT : MAKEPAGE_NONE, TRUE );
//STRIP001
//STRIP001  if ( pNewUpper )
//STRIP001  {
//STRIP001      BOOL bSameBoss = TRUE;
//STRIP001      SwFtnBossFrm * const pNewBoss = pNewUpper->FindFtnBossFrm();
//STRIP001      //Wechseln wir die Spalte/Seite?
//STRIP001      if ( FALSE == ( bSameBoss = pNewBoss == pOldBoss ) )
//STRIP001         {
//STRIP001             bSamePage = pOldBoss->FindPageFrm() == pNewBoss->FindPageFrm(); // Seitenwechsel?
//STRIP001          pNewUpper->Calc();
//STRIP001      }
//STRIP001
//STRIP001      //Das Layoutblatt, dass wir fuer Fussnoten bekommen ist entweder
//STRIP001      //ein Fussnotencontainer oder eine Fussnote
//STRIP001      //Wenn es eine Fussnote ist, und sie die gleiche Fussnotenreferez
//STRIP001      //wie der alte Upper hat, so moven wir uns direkt hinein.
//STRIP001      //Ist die Referenz einen andere oder ist es ein Container, so wird
//STRIP001      //eine neue Fussnote erzeugt und in den Container gestellt.
//STRIP001      // Wenn wir in einem Bereich innerhalb der Fussnote sind, muss
//STRIP001      // SectionFrame noch angelegt werden.
//STRIP001      SwFtnFrm* pTmpFtn = pNewUpper->IsFtnFrm() ? ((SwFtnFrm*)pNewUpper) : 0;
//STRIP001      if( !pTmpFtn )
//STRIP001      {
//STRIP001          ASSERT( pNewUpper->IsFtnContFrm(), "Neuer Upper kein FtnCont.");
//STRIP001          SwFtnContFrm *pCont = (SwFtnContFrm*)pNewUpper;
//STRIP001
//STRIP001          //Fussnote erzeugen.
//STRIP001          SwFtnFrm *pOld = FindFtnFrm();
//STRIP001          pTmpFtn = new SwFtnFrm( pOld->GetFmt()->GetDoc()->GetDfltFrmFmt(),
//STRIP001                                  pOld->GetRef(), pOld->GetAttr() );
//STRIP001          //Verkettung der Fussnoten.
//STRIP001          if ( pOld->GetFollow() )
//STRIP001          {
//STRIP001              pTmpFtn->SetFollow( pOld->GetFollow() );
//STRIP001              pOld->GetFollow()->SetMaster( pTmpFtn );
//STRIP001          }
//STRIP001          pOld->SetFollow( pTmpFtn );
//STRIP001          pTmpFtn->SetMaster( pOld );
//STRIP001          SwFrm* pNx = pCont->Lower();
//STRIP001          if( pNx && pTmpFtn->GetAttr()->GetFtn().IsEndNote() )
//STRIP001              while(pNx && !((SwFtnFrm*)pNx)->GetAttr()->GetFtn().IsEndNote())
//STRIP001                  pNx = pNx->GetNext();
//STRIP001          pTmpFtn->Paste( pCont, pNx );
//STRIP001          pTmpFtn->Calc();
//STRIP001      }
//STRIP001      ASSERT( pTmpFtn->GetAttr() == FindFtnFrm()->GetAttr(), "Wrong Footnote!" );
//STRIP001      // Bereiche in Fussnoten beduerfen besonderer Behandlung
//STRIP001      SwLayoutFrm *pNewUp = pTmpFtn;
//STRIP001      if( IsInSct() )
//STRIP001      {
//STRIP001          SwSectionFrm* pSect = FindSctFrm();
//STRIP001          // Bereich in Fussnote (oder nur Fussnote in Bereich)?
//STRIP001          if( pSect->IsInFtn() )
//STRIP001          {
//STRIP001              if( pTmpFtn->Lower() && pTmpFtn->Lower()->IsSctFrm() &&
//STRIP001                  pSect->GetFollow() == (SwSectionFrm*)pTmpFtn->Lower() )
//STRIP001                  pNewUp = (SwSectionFrm*)pTmpFtn->Lower();
//STRIP001              else
//STRIP001              {
//STRIP001                     pNewUp = new SwSectionFrm( *pSect, FALSE );
//STRIP001                  pNewUp->InsertBefore( pTmpFtn, pTmpFtn->Lower() );
//STRIP001                     static_cast<SwSectionFrm*>(pNewUp)->Init();
//STRIP001                  pNewUp->Frm().Pos() = pTmpFtn->Frm().Pos();
//STRIP001                  pNewUp->Frm().Pos().Y() += 1; //wg. Benachrichtigungen.
//STRIP001
//STRIP001                  // Wenn unser Bereichsframe einen Nachfolger hat, so muss dieser
//STRIP001                  // umgehaengt werden hinter den neuen Follow der Bereichsframes.
//STRIP001                  SwFrm* pTmp = pSect->GetNext();
//STRIP001                  if( pTmp )
//STRIP001                  {
//STRIP001                      SwFlowFrm* pNxt;
//STRIP001                      if( pTmp->IsCntntFrm() )
//STRIP001                          pNxt = (SwCntntFrm*)pTmp;
//STRIP001                      else if( pTmp->IsSctFrm() )
//STRIP001                          pNxt = (SwSectionFrm*)pTmp;
//STRIP001                      else
//STRIP001                      {
//STRIP001                          ASSERT( pTmp->IsTabFrm(), "GetNextSctLeaf: Wrong Type" );
//STRIP001                          pNxt = (SwTabFrm*)pTmp;
//STRIP001                      }
//STRIP001                      pNxt->MoveSubTree( pTmpFtn, pNewUp->GetNext() );
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      MoveSubTree( pNewUp, pNewUp->Lower() );
//STRIP001
//STRIP001      if( !bSameBoss )
//STRIP001          Prepare( PREP_BOSS_CHGD );
//STRIP001  }
//STRIP001  return bSamePage;
//STRIP001 }

/*************************************************************************
|*
|*  class SwSaveFtnHeight
|*
|*  Ersterstellung      MA 19. Jan. 94
|*  Letzte Aenderung    MA 19. Jan. 94
|*
|*************************************************************************/


/*N*/ SwSaveFtnHeight::SwSaveFtnHeight( SwFtnBossFrm *pBs, const SwTwips nDeadLine ) :
/*N*/   pBoss( pBs ),
/*N*/   nOldHeight( pBs->GetMaxFtnHeight() )
/*N*/ {
/*N*/   pBoss->SetFtnDeadLine( nDeadLine );
/*N*/   nNewHeight = pBoss->GetMaxFtnHeight();
/*N*/ }



/*N*/ SwSaveFtnHeight::~SwSaveFtnHeight()
/*N*/ {
/*N*/   //Wenn zwischendurch jemand an der DeadLine gedreht hat, so lassen wir
/*N*/   //ihm seinen Spass!
/*N*/   if ( nNewHeight == pBoss->GetMaxFtnHeight() )
/*N*/       pBoss->nMaxFtnHeight = nOldHeight;
/*N*/ }


/*N*/ #ifndef PRODUCT
//JP 15.10.2001: in a non pro version test if the attribute has the same
//              meaning which his reference is

// Normally, the pRef member and the GetRefFromAttr() result has to be
// identically. Sometimes footnote will be moved from a master to its follow,
// but the GetRef() is called first, so we have to ignore a master/follow
// mismatch.

/*N*/ const SwCntntFrm* SwFtnFrm::GetRef() const
/*N*/ {
/*N*/     const SwCntntFrm* pRefAttr = GetRefFromAttr();
/*N*/     ASSERT( pRef == pRefAttr || pRef->IsAnFollow( pRefAttr )
/*N*/             || pRefAttr->IsAnFollow( pRef ),
/*N*/             "access to deleted Frame? pRef != pAttr->GetRef()" );
/*N*/   return pRef;
/*N*/ }

/*N*/ SwCntntFrm* SwFtnFrm::GetRef()
/*N*/ {
/*N*/     const SwCntntFrm* pRefAttr = GetRefFromAttr();
/*N*/     ASSERT( pRef == pRefAttr || pRef->IsAnFollow( pRefAttr )
/*N*/             || pRefAttr->IsAnFollow( pRef ),
/*N*/             "access to deleted Frame? pRef != pAttr->GetRef()" );
/*N*/   return pRef;
/*N*/ }

/*N*/ #endif

/*N*/ const SwCntntFrm* SwFtnFrm::GetRefFromAttr()  const
/*N*/ {
/*N*/   SwFtnFrm* pThis = (SwFtnFrm*)this;
/*N*/   return pThis->GetRefFromAttr();
/*N*/ }

/*N*/ SwCntntFrm* SwFtnFrm::GetRefFromAttr()
/*N*/ {
/*N*/   ASSERT( pAttr, "invalid Attribute" );
/*N*/   SwTxtNode& rTNd = (SwTxtNode&)pAttr->GetTxtNode();
/*N*/   SwPosition aPos( rTNd, SwIndex( &rTNd, *pAttr->GetStart() ));
/*N*/   SwCntntFrm* pCFrm = rTNd.GetFrm( 0, &aPos, FALSE );
/*N*/   return pCFrm;
/*N*/ }

}
