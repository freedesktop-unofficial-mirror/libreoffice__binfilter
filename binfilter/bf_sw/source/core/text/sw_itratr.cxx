/*************************************************************************
 *
 *  $RCSfile: sw_itratr.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 15:35:51 $
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
#ifndef _SVX_CHARSCALEITEM_HXX
#include <bf_svx/charscaleitem.hxx>
#endif
#ifndef _TXTATR_HXX
#include <txtatr.hxx>
#endif
#ifndef _SFX_PRINTER_HXX //autogen
#include <bf_sfx2/printer.hxx>
#endif
#ifndef _SVX_LRSPITEM_HXX //autogen
#include <bf_svx/lrspitem.hxx>
#endif
#ifndef _WINDOW_HXX //autogen
#include <vcl/window.hxx>
#endif
#ifndef _SV_SVAPP_HXX
#include <vcl/svapp.hxx>
#endif
#ifndef _FMTANCHR_HXX //autogen
#include <fmtanchr.hxx>
#endif
#ifndef _FMTFSIZE_HXX //autogen
#include <fmtfsize.hxx>
#endif
#ifndef _FMTORNT_HXX //autogen
#include <fmtornt.hxx>
#endif
#ifndef _FMTFLCNT_HXX //autogen
#include <fmtflcnt.hxx>
#endif
#ifndef _FMTCNTNT_HXX //autogen
#include <fmtcntnt.hxx>
#endif
#ifndef _FMTFTN_HXX //autogen
#include <fmtftn.hxx>
#endif
#ifndef _FMTHBSH_HXX //autogen
#include <fmthbsh.hxx>
#endif
#ifndef _FRMATR_HXX
#include <frmatr.hxx>
#endif
#ifndef _FRMFMT_HXX //autogen
#include <frmfmt.hxx>
#endif
#ifndef _FMTFLD_HXX
#include <fmtfld.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _VIEWSH_HXX
#include <viewsh.hxx>   // ViewShell
#endif
#ifndef _ROOTFRM_HXX
#include <rootfrm.hxx>
#endif
#ifndef _DOCARY_HXX
#include <docary.hxx>
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>
#endif
#ifndef _DCONTACT_HXX
#include <dcontact.hxx>
#endif
#ifndef _FLDBAS_HXX
#include <fldbas.hxx>      // SwField
#endif
#ifndef _PAM_HXX
#include <pam.hxx>         // SwPosition        (lcl_MinMaxNode)
#endif
#ifndef _TXATBASE_HXX
#include <txatbase.hxx>
#endif
#ifndef _ITRATR_HXX
#include <itratr.hxx>
#endif
#ifndef _SWFONT_HXX
#include <swfont.hxx>
#endif
#ifndef _HTMLTBL_HXX
#include <htmltbl.hxx>
#endif
#ifndef _SWTABLE_HXX
#include <swtable.hxx>
#endif
#ifndef _REDLNITR_HXX
#include <redlnitr.hxx>
#endif
#ifndef _FMTSRND_HXX
#include <fmtsrnd.hxx>
#endif
#ifndef _ITRTXT_HXX
#include <itrtxt.hxx>
#endif
#ifndef _BREAKIT_HXX
#include <breakit.hxx>
#endif
#ifndef _COM_SUN_STAR_I18N_WORDTYPE_HPP_
#include <com/sun/star/i18n/WordType.hpp>
#endif
#ifndef _COM_SUN_STAR_I18N_SCRIPTTYPE_HDL_
#include <com/sun/star/i18n/ScriptType.hdl>
#endif

using namespace ::com::sun::star::i18n;
using namespace ::com::sun::star;

extern BYTE WhichFont( xub_StrLen nIdx, const String* pTxt,
                       const SwScriptInfo* pSI );

/*************************************************************************
 *                      SwAttrIter::Chg()
 *************************************************************************/

/*N*/ void SwAttrIter::Chg( SwTxtAttr *pHt )
/*N*/ {
/*N*/     ASSERT( pHt && pFnt, "No attribute of font available for change");
/*N*/     if( pRedln && pRedln->IsOn() )
            {DBG_ASSERT(0, "STRIP");} //STRIP001 /*?*/         pRedln->ChangeTxtAttr( pFnt, *pHt, sal_True );
/*N*/   else
/*N*/         aAttrHandler.PushAndChg( *pHt, *pFnt );
/*N*/   nChgCnt++;
/*N*/ }

/*************************************************************************
 *                      SwAttrIter::Rst()
 *************************************************************************/

/*N*/ void SwAttrIter::Rst( SwTxtAttr *pHt )
/*N*/ {
/*N*/     ASSERT( pHt && pFnt, "No attribute of font available for reset");
/*N*/     // get top from stack after removing pHt
/*N*/     if( pRedln && pRedln->IsOn() )
            {DBG_ASSERT(0, "STRIP");} //STRIP001 /*?*/         pRedln->ChangeTxtAttr( pFnt, *pHt, sal_False );
/*N*/   else
/*N*/         aAttrHandler.PopAndChg( *pHt, *pFnt );
/*N*/   nChgCnt--;
/*N*/ }

/*************************************************************************
 *              virtual SwAttrIter::~SwAttrIter()
 *************************************************************************/

/*N*/ SwAttrIter::~SwAttrIter()
/*N*/ {
/*N*/   delete pRedln;
/*N*/   delete pFnt;
/*N*/ }

/*************************************************************************
 *                      SwAttrIter::GetAttr()
 *
 * Liefert fuer eine Position das Attribut, wenn das Attribut genau auf
 * der Position nPos liegt und kein EndIndex besitzt.
 * GetAttr() wird fuer Attribute benoetigt, die die Formatierung beeinflussen
 * sollen, ohne dabei den Inhalt des Strings zu veraendern. Solche "entarteten"
 * Attribute sind z.B. Felder (die expandierten Text bereit halten) und
 * zeilengebundene Frames. Um Mehrdeutigkeiten zwischen verschiedenen
 * solcher Attribute zu vermeiden, werden beim Anlegen eines Attributs
 * an der Startposition ein Sonderzeichen in den String einfuegt.
 * Der Formatierer stoesst auf das Sonderzeichen und holt sich per
 * GetAttr() das entartete Attribut.
 *************************************************************************/

/*N*/ SwTxtAttr *SwAttrIter::GetAttr( const xub_StrLen nPos ) const
/*N*/ {
/*N*/   if( pHints )
/*N*/   {
/*N*/       for( MSHORT i = 0; i < pHints->Count(); ++i )
/*N*/       {
/*N*/           SwTxtAttr *pPos = pHints->GetHt(i);
/*N*/           xub_StrLen nStart = *pPos->GetStart();
/*N*/           if( nPos < nStart )
/*N*/               return 0;
/*N*/           if( nPos == nStart && !pPos->GetEnd() )
/*N*/               return pPos;
/*N*/       }
/*N*/   }
/*N*/   return 0;
/*N*/ }

/*************************************************************************
 *                        SwAttrIter::SeekAndChg()
 *************************************************************************/

/*N*/ sal_Bool SwAttrIter::SeekAndChg( const xub_StrLen nNewPos, OutputDevice *pOut )
/*N*/ {
/*N*/   sal_Bool bChg = nStartIndex && nNewPos == nPos ? pFnt->IsFntChg() : Seek( nNewPos );
/*N*/   if ( pLastOut != pOut )
/*N*/   {
/*N*/       pLastOut = pOut;
/*N*/       pFnt->SetFntChg( sal_True );
/*N*/       bChg = sal_True;
/*N*/   }
/*N*/   if( bChg )
/*N*/   {
/*N*/       // wenn der Aenderungszaehler auf Null ist, kennen wir die MagicNo
/*N*/       // des gewuenschten Fonts ...
/*N*/       if ( !nChgCnt && !nPropFont )
/*N*/           pFnt->SetMagic( aMagicNo[ pFnt->GetActual() ],
/*N*/               aFntIdx[ pFnt->GetActual() ], pFnt->GetActual() );
/*N*/       pFnt->ChgPhysFnt( pShell, pOut );
/*N*/   }
/*N*/   return bChg;
/*N*/ }

//STRIP001 sal_Bool SwAttrIter::IsSymbol( const xub_StrLen nNewPos )
//STRIP001 {
//STRIP001  Seek( nNewPos );
//STRIP001  if ( !nChgCnt && !nPropFont )
//STRIP001      pFnt->SetMagic( aMagicNo[ pFnt->GetActual() ],
//STRIP001          aFntIdx[ pFnt->GetActual() ], pFnt->GetActual() );
//STRIP001  return pFnt->IsSymbol( pShell );
//STRIP001 }

/*************************************************************************
 *                        SwAttrIter::SeekStartAndChg()
 *************************************************************************/

/*N*/ sal_Bool SwAttrIter::SeekStartAndChg( OutputDevice *pOut, const sal_Bool bParaFont )
/*N*/ {
/*N*/     if ( pRedln && pRedln->ExtOn() )
            {DBG_ASSERT(0, "STRIP");} //STRIP001 /*?*/         pRedln->LeaveExtend( *pFnt, 0 );
/*N*/
/*N*/     // reset font to its original state
/*N*/     aAttrHandler.Reset();
/*N*/     aAttrHandler.ResetFont( *pFnt );
/*N*/
/*N*/     nStartIndex = nEndIndex = nPos = nChgCnt = 0;
/*N*/   if( nPropFont )
/*?*/       pFnt->SetProportion( nPropFont );
/*N*/     if( pRedln )
/*N*/   {
            DBG_ASSERT(0, "STRIP"); //STRIP001 /*?*/        pRedln->Clear( pFnt );
//STRIP001 /*?*/        if( !bParaFont )
//STRIP001 /*?*/            nChgCnt += pRedln->Seek( *pFnt, 0, STRING_LEN );
//STRIP001 /*?*/        else
//STRIP001 /*?*/            pRedln->Reset();
/*N*/   }
/*N*/
/*N*/   if ( pHints && !bParaFont )
/*N*/   {
/*N*/       SwTxtAttr *pTxtAttr;
/*N*/       // Solange wir noch nicht am Ende des StartArrays angekommen sind &&
/*N*/       // das TextAttribut an Position 0 beginnt ...
/*?*/       while ( ( nStartIndex < pHints->GetStartCount() ) &&
/*?*/               !(*(pTxtAttr=pHints->GetStart(nStartIndex))->GetStart()) )
/*?*/       {
/*?*/           // oeffne die TextAttribute
/*?*/           Chg( pTxtAttr );
/*?*/           nStartIndex++;
/*?*/       }
/*N*/   }
/*N*/
/*N*/   register sal_Bool bChg = pFnt->IsFntChg();
/*N*/   if ( pLastOut != pOut )
/*N*/   {
/*N*/       pLastOut = pOut;
/*N*/       pFnt->SetFntChg( sal_True );
/*N*/       bChg = sal_True;
/*N*/   }
/*N*/   if( bChg )
/*N*/   {
/*N*/       // wenn der Aenderungszaehler auf Null ist, kennen wir die MagicNo
/*N*/       // des gewuenschten Fonts ...
/*N*/       if ( !nChgCnt && !nPropFont )
/*N*/           pFnt->SetMagic( aMagicNo[ pFnt->GetActual() ],
/*N*/               aFntIdx[ pFnt->GetActual() ], pFnt->GetActual() );
/*N*/       pFnt->ChgPhysFnt( pShell, pOut );
/*N*/   }
/*N*/   return bChg;
/*N*/ }

/*************************************************************************
 *                       SwAttrIter::SeekFwd()
 *************************************************************************/

// AMA: Neuer AttrIter Nov 94

/*N*/ void SwAttrIter::SeekFwd( const xub_StrLen nNewPos )
/*N*/ {
/*N*/   SwTxtAttr *pTxtAttr;
/*N*/
/*N*/   if ( nStartIndex ) // wenn ueberhaupt schon Attribute geoeffnet wurden...
/*N*/   {
/*N*/       // Schliesse Attr, die z. Z. geoeffnet sind, vor nNewPos+1 aber enden.
/*N*/
/*N*/       // Solange wir noch nicht am Ende des EndArrays angekommen sind &&
/*N*/       // das TextAttribut vor oder an der neuen Position endet ...
/*N*/       while ( ( nEndIndex < pHints->GetEndCount() ) &&
/*N*/               (*(pTxtAttr=pHints->GetEnd(nEndIndex))->GetAnyEnd()<=nNewPos))
/*N*/       {
/*N*/           // schliesse die TextAttribute, deren StartPos vor
/*N*/           // oder an der alten nPos lag, die z.Z. geoeffnet sind.
/*N*/           if (*pTxtAttr->GetStart() <= nPos)  Rst( pTxtAttr );
/*N*/           nEndIndex++;
/*N*/       }
/*N*/   }
/*N*/   else // ueberlies die nicht geoeffneten Enden
/*N*/   {
/*N*/       while ( ( nEndIndex < pHints->GetEndCount() ) &&
/*N*/               (*(pTxtAttr=pHints->GetEnd(nEndIndex))->GetAnyEnd()<=nNewPos))
/*N*/       {
/*N*/           nEndIndex++;
/*N*/       }
/*N*/   }
/*N*/   // Solange wir noch nicht am Ende des StartArrays angekommen sind &&
/*N*/   // das TextAttribut vor oder an der neuen Position beginnt ...
/*N*/   while ( ( nStartIndex < pHints->GetStartCount() ) &&
/*N*/          (*(pTxtAttr=pHints->GetStart(nStartIndex))->GetStart()<=nNewPos))
/*N*/   {
/*N*/       // oeffne die TextAttribute, deren Ende hinter der neuen Position liegt
/*N*/       if ( *pTxtAttr->GetAnyEnd() > nNewPos )  Chg( pTxtAttr );
/*N*/       nStartIndex++;
/*N*/   }
/*N*/
/*N*/ }

/*************************************************************************
 *                       SwAttrIter::Seek()
 *************************************************************************/

/*N*/ sal_Bool SwAttrIter::Seek( const xub_StrLen nNewPos )
/*N*/ {
/*N*/     if ( pRedln && pRedln->ExtOn() )
            {DBG_ASSERT(0, "STRIP");} //STRIP001 /*?*/         pRedln->LeaveExtend( *pFnt, nNewPos );
/*N*/
/*N*/   if( pHints )
/*N*/   {
/*N*/       if( !nNewPos || nNewPos < nPos )
/*N*/       {
/*N*/             if( pRedln )
                    {DBG_ASSERT(0, "STRIP");} //STRIP001 /*?*/              pRedln->Clear( NULL );
/*N*/
/*N*/             // reset font to its original state
/*N*/             aAttrHandler.Reset();
/*N*/             aAttrHandler.ResetFont( *pFnt );
/*N*/
/*N*/             if( nPropFont )
/*?*/               pFnt->SetProportion( nPropFont );
/*N*/           nStartIndex = nEndIndex = nPos = 0;
/*N*/           nChgCnt = 0;
/*N*/
/*N*/             // Achtung!
/*N*/             // resetting the font here makes it necessary to apply any
/*N*/             // changes for extended input directly to the font
/*N*/             if ( pRedln && pRedln->ExtOn() )
/*N*/             {
                    DBG_ASSERT(0, "STRIP"); //STRIP001 /*?*/                 pRedln->UpdateExtFont( *pFnt );
//STRIP001 /*?*/                 ++nChgCnt;
/*N*/             }
/*N*/       }
/*N*/       SeekFwd( nNewPos );
/*N*/   }
/*N*/
/*N*/     pFnt->SetActual( WhichFont( nNewPos, 0, pScriptInfo ) );
/*N*/
/*N*/     if( pRedln )
            {DBG_ASSERT(0, "STRIP");} //STRIP001 /*?*/      nChgCnt += pRedln->Seek( *pFnt, nNewPos, nPos );
/*N*/   nPos = nNewPos;
/*N*/
/*N*/   if( nPropFont )
/*?*/       pFnt->SetProportion( nPropFont );
/*N*/
/*N*/   return pFnt->IsFntChg();
/*N*/ }

/*************************************************************************
 *                      SwAttrIter::GetNextAttr()
 *************************************************************************/

/*N*/ xub_StrLen SwAttrIter::GetNextAttr( ) const
/*N*/ {
/*N*/   xub_StrLen nNext = STRING_LEN;
/*N*/   if( pHints )
/*N*/   {
/*N*/       if (pHints->GetStartCount() > nStartIndex) // Gibt es noch Starts?
/*N*/          nNext = (*pHints->GetStart(nStartIndex)->GetStart());
/*N*/       if (pHints->GetEndCount() > nEndIndex) // Gibt es noch Enden?
/*N*/       {
/*N*/           xub_StrLen nNextEnd = (*pHints->GetEnd(nEndIndex)->GetAnyEnd());
/*N*/           if ( nNextEnd<nNext ) nNext = nNextEnd; // Wer ist naeher?
/*N*/       }
/*N*/   }
/*N*/     if( pRedln )
            {DBG_ASSERT(0, "STRIP");} //STRIP001 /*?*/      return pRedln->GetNextRedln( nNext );
/*N*/   return nNext;
/*N*/ }

#if OSL_DEBUG_LEVEL > 1
/*************************************************************************
 *                      SwAttrIter::Dump()
 *************************************************************************/

//STRIP001 void SwAttrIter::Dump( SvStream &rOS ) const
//STRIP001 {
//STRIP001 // Noch nicht an den neuen Attributiterator angepasst ...
//STRIP001 }

#endif

class SwMinMaxArgs
{
public:
    OutputDevice *pOut;
    ULONG &rMin;
    ULONG &rMax;
    ULONG &rAbsMin;
    long nRowWidth;
    long nWordWidth;
    long nWordAdd;
    xub_StrLen nNoLineBreak;
    SwMinMaxArgs( OutputDevice *pOutI, ULONG& rMinI, ULONG &rMaxI, ULONG &rAbsI )
        : pOut( pOutI ), rMin( rMinI ), rMax( rMaxI ), rAbsMin( rAbsI )
        { nRowWidth = nWordWidth = nWordAdd = 0; nNoLineBreak = STRING_LEN; }
    void Minimum( long nNew ) { if( (long)rMin < nNew ) rMin = nNew; }
    void NewWord() { nWordAdd = nWordWidth = 0; }
};

//STRIP001 sal_Bool lcl_MinMaxString( SwMinMaxArgs& rArg, SwFont* pFnt, const XubString &rTxt,
//STRIP001  xub_StrLen nIdx, xub_StrLen nEnd )
//STRIP001 {
//STRIP001  sal_Bool bRet = sal_False;
//STRIP001  while( nIdx < nEnd )
//STRIP001  {
//STRIP001      xub_StrLen nStop = nIdx;
//STRIP001         sal_Bool bClear;
//STRIP001         LanguageType eLang = pFnt->GetLanguage();
//STRIP001         if( pBreakIt->xBreak.is() )
//STRIP001         {
//STRIP001             bClear = CH_BLANK == rTxt.GetChar( nStop );
//STRIP001             Boundary aBndry( pBreakIt->xBreak->getWordBoundary( rTxt, nIdx,
//STRIP001                              pBreakIt->GetLocale( eLang ),
//STRIP001                              WordType::DICTIONARY_WORD, TRUE ) );
//STRIP001             nStop = (xub_StrLen)aBndry.endPos;
//STRIP001             if( nIdx <= aBndry.startPos && nIdx && nIdx-1 != rArg.nNoLineBreak )
//STRIP001                 rArg.NewWord();
//STRIP001             if( nStop == nIdx )
//STRIP001                 ++nStop;
//STRIP001             if( nStop > nEnd )
//STRIP001                 nStop = nEnd;
//STRIP001         }
//STRIP001         else
//STRIP001         {
//STRIP001             while( nStop < nEnd && CH_BLANK != rTxt.GetChar( nStop ) )
//STRIP001                 ++nStop;
//STRIP001             bClear = nStop == nIdx;
//STRIP001             if ( bClear )
//STRIP001             {
//STRIP001                 rArg.NewWord();
//STRIP001                 while( nStop < nEnd && CH_BLANK == rTxt.GetChar( nStop ) )
//STRIP001                     ++nStop;
//STRIP001             }
//STRIP001         }
//STRIP001
//STRIP001         SwDrawTextInfo aDrawInf( 0, *rArg.pOut, 0, rTxt, nIdx, nStop - nIdx );
//STRIP001         long nAktWidth = pFnt->_GetTxtSize( aDrawInf ).Width();
//STRIP001      rArg.nRowWidth += nAktWidth;
//STRIP001      if( bClear )
//STRIP001          rArg.NewWord();
//STRIP001      else
//STRIP001      {
//STRIP001          rArg.nWordWidth += nAktWidth;
//STRIP001          if( (long)rArg.rAbsMin < rArg.nWordWidth )
//STRIP001              rArg.rAbsMin = rArg.nWordWidth;
//STRIP001          rArg.Minimum( rArg.nWordWidth + rArg.nWordAdd );
//STRIP001          bRet = sal_True;
//STRIP001      }
//STRIP001      nIdx = nStop;
//STRIP001     }
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 sal_Bool SwTxtNode::IsSymbol( const xub_StrLen nBegin ) const
//STRIP001 {
//STRIP001  SwScriptInfo aScriptInfo;
//STRIP001     SwAttrIter aIter( *(SwTxtNode*)this, aScriptInfo );
//STRIP001     aIter.Seek( nBegin );
//STRIP001  return aIter.GetFnt()->IsSymbol( GetDoc()->GetRootFrm() ?
//STRIP001              GetDoc()->GetRootFrm()->GetCurrShell() : 0 );
//STRIP001 }

class SwMinMaxNodeArgs
{
public:
    ULONG nMaxWidth;    // Summe aller Rahmenbreite
    long nMinWidth;     // Breitester Rahmen
    long nLeftRest;     // noch nicht von Rahmen ueberdeckter Platz im l. Rand
    long nRightRest;    // noch nicht von Rahmen ueberdeckter Platz im r. Rand
    long nLeftDiff;     // Min/Max-Differenz des Rahmens im linken Rand
    long nRightDiff;    // Min/Max-Differenz des Rahmens im rechten Rand
    ULONG nIndx;        // Indexnummer des Nodes
    void Minimum( long nNew ) { if( nNew > nMinWidth ) nMinWidth = nNew; }
};

//STRIP001 sal_Bool lcl_MinMaxNode( const SwFrmFmtPtr& rpNd, void* pArgs )
//STRIP001 {
//STRIP001  const SwFmtAnchor& rFmtA = ((SwFrmFmt*)rpNd)->GetAnchor();
//STRIP001
//STRIP001  bool bCalculate = false;
//STRIP001  if (
//STRIP001      (FLY_AT_CNTNT == rFmtA.GetAnchorId()) ||
//STRIP001      (FLY_AUTO_CNTNT == rFmtA.GetAnchorId())
//STRIP001     )
//STRIP001  {
//STRIP001      bCalculate = true;
//STRIP001  }
//STRIP001
//STRIP001  if (bCalculate)
//STRIP001  {
//STRIP001      const SwMinMaxNodeArgs *pIn = (const SwMinMaxNodeArgs*)pArgs;
//STRIP001      const SwPosition *pPos = rFmtA.GetCntntAnchor();
//STRIP001      ASSERT(pPos && pIn, "Unexpected NULL arguments");
//STRIP001      if (!pPos || !pIn || pIn->nIndx != pPos->nNode.GetIndex())
//STRIP001          bCalculate = false;
//STRIP001  }
//STRIP001
//STRIP001  if (bCalculate)
//STRIP001  {
//STRIP001      long nMin, nMax;
//STRIP001      SwHTMLTableLayout *pLayout = 0;
//STRIP001      MSHORT nWhich = ((SwFrmFmt*)rpNd)->Which();
//STRIP001      if( RES_DRAWFRMFMT != nWhich )
//STRIP001      {
//STRIP001          // Enthaelt der Rahmen zu Beginn oder am Ende eine Tabelle?
//STRIP001          SwDoc *pDoc = ((SwFrmFmt*)rpNd)->GetDoc();
//STRIP001
//STRIP001          const SwFmtCntnt& rFlyCntnt = ((SwFrmFmt*)rpNd)->GetCntnt();
//STRIP001          ULONG nStt = rFlyCntnt.GetCntntIdx()->GetIndex();
//STRIP001          SwTableNode* pTblNd = pDoc->GetNodes()[nStt+1]->GetTableNode();
//STRIP001          if( !pTblNd )
//STRIP001          {
//STRIP001              SwNode *pNd = pDoc->GetNodes()[nStt];
//STRIP001              pNd = pDoc->GetNodes()[pNd->EndOfSectionIndex()-1];
//STRIP001              if( pNd->IsEndNode() )
//STRIP001                  pTblNd = pNd->StartOfSectionNode()->GetTableNode();
//STRIP001          }
//STRIP001
//STRIP001          if( pTblNd )
//STRIP001              pLayout = pTblNd->GetTable().GetHTMLTableLayout();
//STRIP001      }
//STRIP001
//STRIP001      const SwFmtHoriOrient& rOrient = ((SwFrmFmt*)rpNd)->GetHoriOrient();
//STRIP001      SwHoriOrient eHoriOri = rOrient.GetHoriOrient();
//STRIP001
//STRIP001      long nDiff;
//STRIP001      if( pLayout )
//STRIP001      {
//STRIP001          nMin = pLayout->GetMin();
//STRIP001          nMax = pLayout->GetMax();
//STRIP001          nDiff = nMax - nMin;
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          if( RES_DRAWFRMFMT == nWhich )
//STRIP001          {
//STRIP001              const SdrObject* pSObj = rpNd->FindSdrObject();
//STRIP001              if( pSObj )
//STRIP001                  nMin = pSObj->GetBoundRect().GetWidth();
//STRIP001              else
//STRIP001              nMin = 0;
//STRIP001
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              const SwFmtFrmSize &rSz = ( (SwFrmFmt*)rpNd )->GetFrmSize();
//STRIP001              nMin = rSz.GetWidth();
//STRIP001          }
//STRIP001          nMax = nMin;
//STRIP001          nDiff = 0;
//STRIP001      }
//STRIP001
//STRIP001      const SvxLRSpaceItem &rLR = ( (SwFrmFmt*)rpNd )->GetLRSpace();
//STRIP001      nMin += rLR.GetLeft();
//STRIP001      nMin += rLR.GetRight();
//STRIP001      nMax += rLR.GetLeft();
//STRIP001      nMax += rLR.GetRight();
//STRIP001
//STRIP001      if( SURROUND_THROUGHT == ((SwFrmFmt*)rpNd)->GetSurround().GetSurround() )
//STRIP001      {
//STRIP001          ( (SwMinMaxNodeArgs*)pArgs )->Minimum( nMin );
//STRIP001          return sal_True;
//STRIP001      }
//STRIP001
//STRIP001      // Rahmen, die recht bzw. links ausgerichtet sind, gehen nur
//STRIP001      // teilweise in die Max-Berechnung ein, da der Rand schon berueck-
//STRIP001      // sichtigt wird. Nur wenn die Rahmen in den Textkoerper ragen,
//STRIP001      // wird dieser Teil hinzuaddiert.
//STRIP001      switch( eHoriOri )
//STRIP001      {
//STRIP001          case HORI_RIGHT:
//STRIP001          {
//STRIP001              if( nDiff )
//STRIP001              {
//STRIP001                  ((SwMinMaxNodeArgs*)pArgs)->nRightRest -=
//STRIP001                      ((SwMinMaxNodeArgs*)pArgs)->nRightDiff;
//STRIP001                  ((SwMinMaxNodeArgs*)pArgs)->nRightDiff = nDiff;
//STRIP001              }
//STRIP001              if( FRAME!=rOrient.GetRelationOrient() )
//STRIP001              {
//STRIP001                  if( ((SwMinMaxNodeArgs*)pArgs)->nRightRest > 0 )
//STRIP001                      ((SwMinMaxNodeArgs*)pArgs)->nRightRest = 0;
//STRIP001              }
//STRIP001              ((SwMinMaxNodeArgs*)pArgs)->nRightRest -= nMin;
//STRIP001              break;
//STRIP001          }
//STRIP001          case HORI_LEFT:
//STRIP001          {
//STRIP001              if( nDiff )
//STRIP001              {
//STRIP001                  ((SwMinMaxNodeArgs*)pArgs)->nLeftRest -=
//STRIP001                      ((SwMinMaxNodeArgs*)pArgs)->nLeftDiff;
//STRIP001                  ((SwMinMaxNodeArgs*)pArgs)->nLeftDiff = nDiff;
//STRIP001              }
//STRIP001              if( FRAME!=rOrient.GetRelationOrient() &&
//STRIP001                  ((SwMinMaxNodeArgs*)pArgs)->nLeftRest < 0 )
//STRIP001                  ((SwMinMaxNodeArgs*)pArgs)->nLeftRest = 0;
//STRIP001              ((SwMinMaxNodeArgs*)pArgs)->nLeftRest -= nMin;
//STRIP001              break;
//STRIP001          }
//STRIP001          default:
//STRIP001          {
//STRIP001              ( (SwMinMaxNodeArgs*)pArgs )->nMaxWidth += nMax;
//STRIP001              ( (SwMinMaxNodeArgs*)pArgs )->Minimum( nMin );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return sal_True;
//STRIP001 }

#define FLYINCNT_MIN_WIDTH 284

// changing this method very likely requires changing of
// "GetScalingOfSelectedText"
//STRIP001 void SwTxtNode::GetMinMaxSize( ULONG nIndex, ULONG& rMin, ULONG &rMax,
//STRIP001                             ULONG& rAbsMin, OutputDevice* pOut ) const
//STRIP001 {
//STRIP001  if( !pOut )
//STRIP001  {
//STRIP001      ViewShell* pSh;
//STRIP001      GetDoc()->GetEditShell( &pSh );
//STRIP001      if( pSh )
//STRIP001          pOut = pSh->GetWin();
//STRIP001      if( !pOut )
//STRIP001          pOut = GetpApp()->GetDefaultDevice();
//STRIP001  }
//STRIP001
//STRIP001  MapMode aOldMap( pOut->GetMapMode() );
//STRIP001  pOut->SetMapMode( MapMode( MAP_TWIP ) );
//STRIP001
//STRIP001  rMin = 0;
//STRIP001  rMax = 0;
//STRIP001  rAbsMin = 0;
//STRIP001
//STRIP001  const SvxLRSpaceItem &rSpace = GetSwAttrSet().GetLRSpace();
//STRIP001  long nLROffset = rSpace.GetTxtLeft() + GetLeftMarginWithNum( sal_True );
//STRIP001  short nFLOffs;
//STRIP001  // Bei Numerierung ist ein neg. Erstzeileneinzug vermutlich
//STRIP001  // bereits gefuellt...
//STRIP001  if( !GetFirstLineOfsWithNum( nFLOffs ) || nFLOffs > nLROffset )
//STRIP001      nLROffset = nFLOffs;
//STRIP001
//STRIP001  SwMinMaxNodeArgs aNodeArgs;
//STRIP001  aNodeArgs.nMinWidth = 0;
//STRIP001  aNodeArgs.nMaxWidth = 0;
//STRIP001  aNodeArgs.nLeftRest = nLROffset;
//STRIP001  aNodeArgs.nRightRest = rSpace.GetRight();
//STRIP001  aNodeArgs.nLeftDiff = 0;
//STRIP001  aNodeArgs.nRightDiff = 0;
//STRIP001  if( nIndex )
//STRIP001  {
//STRIP001      SwSpzFrmFmts* pTmp = (SwSpzFrmFmts*)GetDoc()->GetSpzFrmFmts();
//STRIP001      if( pTmp )
//STRIP001      {
//STRIP001          aNodeArgs.nIndx = nIndex;
//STRIP001          pTmp->ForEach( &lcl_MinMaxNode, &aNodeArgs );
//STRIP001      }
//STRIP001  }
//STRIP001  if( aNodeArgs.nLeftRest < 0 )
//STRIP001      aNodeArgs.Minimum( nLROffset - aNodeArgs.nLeftRest );
//STRIP001  aNodeArgs.nLeftRest -= aNodeArgs.nLeftDiff;
//STRIP001  if( aNodeArgs.nLeftRest < 0 )
//STRIP001      aNodeArgs.nMaxWidth -= aNodeArgs.nLeftRest;
//STRIP001
//STRIP001  if( aNodeArgs.nRightRest < 0 )
//STRIP001      aNodeArgs.Minimum( rSpace.GetRight() - aNodeArgs.nRightRest );
//STRIP001  aNodeArgs.nRightRest -= aNodeArgs.nRightDiff;
//STRIP001  if( aNodeArgs.nRightRest < 0 )
//STRIP001      aNodeArgs.nMaxWidth -= aNodeArgs.nRightRest;
//STRIP001
//STRIP001  SwScriptInfo aScriptInfo;
//STRIP001     SwAttrIter aIter( *(SwTxtNode*)this, aScriptInfo );
//STRIP001  xub_StrLen nIdx = 0;
//STRIP001  aIter.SeekAndChg( nIdx, pOut );
//STRIP001  xub_StrLen nLen = aText.Len();
//STRIP001  long nAktWidth = 0;
//STRIP001  MSHORT nAdd = 0;
//STRIP001  SwMinMaxArgs aArg( pOut, rMin, rMax, rAbsMin );
//STRIP001  while( nIdx < nLen )
//STRIP001  {
//STRIP001      xub_StrLen nNextChg = aIter.GetNextAttr();
//STRIP001      xub_StrLen nStop = aScriptInfo.NextScriptChg( nIdx );
//STRIP001      if( nNextChg > nStop )
//STRIP001          nNextChg = nStop;
//STRIP001      SwTxtAttr *pHint = NULL;
//STRIP001      xub_Unicode cChar = CH_BLANK;
//STRIP001      nStop = nIdx;
//STRIP001      while( nStop < nLen && nStop < nNextChg &&
//STRIP001             CH_TAB != ( cChar = aText.GetChar( nStop ) ) &&
//STRIP001                CH_BREAK != cChar && CHAR_HARDBLANK != cChar &&
//STRIP001                CHAR_HARDHYPHEN != cChar && CHAR_SOFTHYPHEN != cChar &&
//STRIP001                !pHint )
//STRIP001      {
//STRIP001          if( ( CH_TXTATR_BREAKWORD != cChar && CH_TXTATR_INWORD != cChar )
//STRIP001              || ( 0 == ( pHint = aIter.GetAttr( nStop ) ) ) )
//STRIP001              ++nStop;
//STRIP001      }
//STRIP001      if( lcl_MinMaxString( aArg, aIter.GetFnt(), aText, nIdx, nStop ) )
//STRIP001          nAdd = 20;
//STRIP001      nIdx = nStop;
//STRIP001      aIter.SeekAndChg( nIdx, pOut );
//STRIP001      switch( cChar )
//STRIP001      {
//STRIP001          case CH_BREAK  :
//STRIP001          {
//STRIP001              if( (long)rMax < aArg.nRowWidth )
//STRIP001                  rMax = aArg.nRowWidth;
//STRIP001              aArg.nRowWidth = 0;
//STRIP001              aArg.NewWord();
//STRIP001              aIter.SeekAndChg( ++nIdx, pOut );
//STRIP001          }
//STRIP001          break;
//STRIP001          case CH_TAB    :
//STRIP001          {
//STRIP001              aArg.NewWord();
//STRIP001              aIter.SeekAndChg( ++nIdx, pOut );
//STRIP001          }
//STRIP001          break;
//STRIP001             case CHAR_SOFTHYPHEN:
//STRIP001                 ++nIdx;
//STRIP001             break;
//STRIP001             case CHAR_HARDBLANK:
//STRIP001             case CHAR_HARDHYPHEN:
//STRIP001             {
//STRIP001                 XubString sTmp( cChar );
//STRIP001                 SwDrawTextInfo aDrawInf(
//STRIP001                         GetDoc()->GetRootFrm() ?
//STRIP001                         GetDoc()->GetRootFrm()->GetCurrShell() : 0,
//STRIP001                         *pOut, 0, sTmp, 0, 1, 0, sal_False );
//STRIP001                 nAktWidth = aIter.GetFnt()->_GetTxtSize( aDrawInf ).Width();
//STRIP001                 aArg.nWordWidth += nAktWidth;
//STRIP001                 aArg.nRowWidth += nAktWidth;
//STRIP001                 if( (long)rAbsMin < aArg.nWordWidth )
//STRIP001                     rAbsMin = aArg.nWordWidth;
//STRIP001                 aArg.Minimum( aArg.nWordWidth + aArg.nWordAdd );
//STRIP001                 aArg.nNoLineBreak = nIdx++;
//STRIP001             }
//STRIP001             break;
//STRIP001          case CH_TXTATR_BREAKWORD:
//STRIP001          case CH_TXTATR_INWORD:
//STRIP001          {
//STRIP001              if( !pHint )
//STRIP001                  break;
//STRIP001              long nOldWidth = aArg.nWordWidth;
//STRIP001              long nOldAdd = aArg.nWordAdd;
//STRIP001              aArg.NewWord();
//STRIP001
//STRIP001              switch( pHint->Which() )
//STRIP001              {
//STRIP001                  case RES_TXTATR_FLYCNT :
//STRIP001                  {
//STRIP001                      SwFrmFmt *pFrmFmt = pHint->GetFlyCnt().GetFrmFmt();
//STRIP001                      const SvxLRSpaceItem &rLR = pFrmFmt->GetLRSpace();
//STRIP001                      if( RES_DRAWFRMFMT == pFrmFmt->Which() )
//STRIP001                      {
//STRIP001                          const SdrObject* pSObj = pFrmFmt->FindSdrObject();
//STRIP001                          if( pSObj )
//STRIP001                              nAktWidth = pSObj->GetBoundRect().GetWidth();
//STRIP001                          else
//STRIP001                              nAktWidth = 0;
//STRIP001                      }
//STRIP001                      else
//STRIP001                      {
//STRIP001                          const SwFmtFrmSize& rTmpSize = pFrmFmt->GetFrmSize();
//STRIP001                          if( RES_FLYFRMFMT == pFrmFmt->Which()
//STRIP001                              && rTmpSize.GetWidthPercent() )
//STRIP001                          {
/*-----------------24.01.97 14:09----------------------------------------------
 * Hier ein HACK fuer folgende Situation: In dem Absatz befindet sich
 * ein Textrahmen mit relativer Groesse. Dann nehmen wir mal als minimale
 * Breite 0,5 cm und als maximale KSHRT_MAX.
 * Sauberer und vielleicht spaeter notwendig waere es, ueber den Inhalt
 * des Textrahmens zu iterieren und GetMinMaxSize rekursiv zu rufen.
 * --------------------------------------------------------------------------*/
//STRIP001                              nAktWidth = FLYINCNT_MIN_WIDTH; // 0,5 cm
//STRIP001                              if( (long)rMax < KSHRT_MAX )
//STRIP001                                  rMax = KSHRT_MAX;
//STRIP001                          }
//STRIP001                          else
//STRIP001                              nAktWidth = pFrmFmt->GetFrmSize().GetWidth();
//STRIP001                      }
//STRIP001                      nAktWidth += rLR.GetLeft();
//STRIP001                      nAktWidth += rLR.GetRight();
//STRIP001                      aArg.nWordAdd = nOldWidth + nOldAdd;
//STRIP001                      aArg.nWordWidth = nAktWidth;
//STRIP001                      aArg.nRowWidth += nAktWidth;
//STRIP001                      if( (long)rAbsMin < aArg.nWordWidth )
//STRIP001                          rAbsMin = aArg.nWordWidth;
//STRIP001                      aArg.Minimum( aArg.nWordWidth + aArg.nWordAdd );
//STRIP001                      break;
//STRIP001                  }
//STRIP001                  case RES_TXTATR_FTN :
//STRIP001                  {
//STRIP001                      const XubString aTxt = pHint->GetFtn().GetNumStr();
//STRIP001                      if( lcl_MinMaxString( aArg, aIter.GetFnt(), aTxt, 0,
//STRIP001                          aTxt.Len() ) )
//STRIP001                          nAdd = 20;
//STRIP001                      break;
//STRIP001                  }
//STRIP001                  case RES_TXTATR_FIELD :
//STRIP001                  {
//STRIP001                      SwField *pFld = (SwField*)pHint->GetFld().GetFld();
//STRIP001                      const String aTxt = pFld->GetCntnt( FALSE );
//STRIP001                      if( lcl_MinMaxString( aArg, aIter.GetFnt(), aTxt, 0,
//STRIP001                          aTxt.Len() ) )
//STRIP001                          nAdd = 20;
//STRIP001                      break;
//STRIP001                  }
//STRIP001                  default: aArg.nWordWidth = nOldWidth;
//STRIP001                           aArg.nWordAdd = nOldAdd;
//STRIP001
//STRIP001              }
//STRIP001              aIter.SeekAndChg( ++nIdx, pOut );
//STRIP001          }
//STRIP001          break;
//STRIP001      }
//STRIP001  }
//STRIP001  if( (long)rMax < aArg.nRowWidth )
//STRIP001      rMax = aArg.nRowWidth;
//STRIP001
//STRIP001  nLROffset += rSpace.GetRight();
//STRIP001
//STRIP001  rAbsMin += nLROffset;
//STRIP001  rAbsMin += nAdd;
//STRIP001  rMin += nLROffset;
//STRIP001  rMin += nAdd;
//STRIP001  if( (long)rMin < aNodeArgs.nMinWidth )
//STRIP001      rMin = aNodeArgs.nMinWidth;
//STRIP001  if( (long)rAbsMin < aNodeArgs.nMinWidth )
//STRIP001      rAbsMin = aNodeArgs.nMinWidth;
//STRIP001  rMax += aNodeArgs.nMaxWidth;
//STRIP001  rMax += nLROffset;
//STRIP001  rMax += nAdd;
//STRIP001  if( rMax < rMin ) // z.B. Rahmen mit Durchlauf gehen zunaechst nur
//STRIP001      rMax = rMin;  // in das Minimum ein
//STRIP001  pOut->SetMapMode( aOldMap );
//STRIP001 }

/*************************************************************************
 *                      SwTxtNode::GetScalingOfSelectedText()
 *
 * Calculates the width of the text part specified by nStt and nEnd,
 * the height of the line containing nStt is devided by this width,
 * indicating the scaling factor, if the text part is rotated.
 * Having CH_BREAKs in the text part, this method returns the scaling
 * factor for the longest of the text parts separated by the CH_BREAKs.
 *
 * changing this method very likely requires changing of "GetMinMaxSize"
 *************************************************************************/

//STRIP001 USHORT SwTxtNode::GetScalingOfSelectedText(  xub_StrLen nStt, xub_StrLen nEnd )
//STRIP001  const
//STRIP001 {
//STRIP001     ViewShell* pSh = NULL;
//STRIP001     OutputDevice* pOut = NULL;
//STRIP001  GetDoc()->GetEditShell( &pSh );
//STRIP001
//STRIP001     if ( pSh )
//STRIP001         pOut = &pSh->GetRefDev();
//STRIP001     else
//STRIP001     {
//STRIP001         //Zugriff ueber StarONE, es muss keine Shell existieren oder aktiv sein.
//STRIP001         if ( GetDoc()->IsBrowseMode() ) //?!?!?!?
//STRIP001             pOut = GetpApp()->GetDefaultDevice();
//STRIP001         else
//STRIP001             pOut = &GetDoc()->GetRefDev();
//STRIP001     }
//STRIP001
//STRIP001     ASSERT( pOut, "GetScalingOfSelectedText without outdev" )
//STRIP001
//STRIP001     MapMode aOldMap( pOut->GetMapMode() );
//STRIP001  pOut->SetMapMode( MapMode( MAP_TWIP ) );
//STRIP001
//STRIP001     if ( nStt == nEnd )
//STRIP001     {
//STRIP001         if ( !pBreakIt->xBreak.is() )
//STRIP001             return 100;
//STRIP001
//STRIP001         SwScriptInfo aScriptInfo;
//STRIP001         SwAttrIter aIter( *(SwTxtNode*)this, aScriptInfo );
//STRIP001         aIter.SeekAndChg( nStt, pOut );
//STRIP001
//STRIP001         Boundary aBound =
//STRIP001             pBreakIt->xBreak->getWordBoundary( GetTxt(), nStt,
//STRIP001             pBreakIt->GetLocale( aIter.GetFnt()->GetLanguage() ),
//STRIP001             WordType::DICTIONARY_WORD, sal_True );
//STRIP001
//STRIP001         if ( nStt == aBound.startPos )
//STRIP001             // cursor is at left or right border of word
//STRIP001             return 100;
//STRIP001
//STRIP001         nStt = (xub_StrLen)aBound.startPos;
//STRIP001         nEnd = (xub_StrLen)aBound.endPos;
//STRIP001
//STRIP001         if ( nStt == nEnd )
//STRIP001             return 100;
//STRIP001     }
//STRIP001
//STRIP001     SwScriptInfo aScriptInfo;
//STRIP001  SwAttrIter aIter( *(SwTxtNode*)this, aScriptInfo );
//STRIP001
//STRIP001     // We do not want scaling attributes to be considered during this
//STRIP001     // calculation. For this, we push a temporary scaling attribute with
//STRIP001     // scaling value 100 and priority flag on top of the scaling stack
//STRIP001     SwAttrHandler& rAH = aIter.GetAttrHandler();
//STRIP001     SvxCharScaleWidthItem aItem;
//STRIP001     SwTxtAttrEnd aAttr( aItem, nStt, nEnd );
//STRIP001     aAttr.SetPriorityAttr( sal_True );
//STRIP001     rAH.PushAndChg( aAttr, *(aIter.GetFnt()) );
//STRIP001
//STRIP001     xub_StrLen nIdx = nStt;
//STRIP001
//STRIP001  ULONG nWidth = 0;
//STRIP001  ULONG nProWidth = 0;
//STRIP001
//STRIP001  while( nIdx < nEnd )
//STRIP001  {
//STRIP001      aIter.SeekAndChg( nIdx, pOut );
//STRIP001
//STRIP001      // scan for end of portion
//STRIP001      xub_StrLen nNextChg = aIter.GetNextAttr();
//STRIP001      xub_StrLen nStop = aScriptInfo.NextScriptChg( nIdx );
//STRIP001      if( nNextChg > nStop )
//STRIP001          nNextChg = nStop;
//STRIP001
//STRIP001      nStop = nIdx;
//STRIP001      xub_Unicode cChar = CH_BLANK;
//STRIP001         SwTxtAttr* pHint = NULL;
//STRIP001
//STRIP001      // stop at special characters in [ nIdx, nNextChg ]
//STRIP001      while( nStop < nEnd && nStop < nNextChg )
//STRIP001      {
//STRIP001          cChar = aText.GetChar( nStop );
//STRIP001          if( CH_TAB == cChar || CH_BREAK == cChar ||
//STRIP001                 CHAR_HARDBLANK == cChar || CHAR_HARDHYPHEN == cChar ||
//STRIP001                 CHAR_SOFTHYPHEN == cChar ||
//STRIP001                ( CH_TXTATR_BREAKWORD == cChar ||  CH_TXTATR_INWORD == cChar ) &&
//STRIP001                ( 0 == ( pHint = aIter.GetAttr( nStop ) ) ) )
//STRIP001              break;
//STRIP001          else
//STRIP001              ++nStop;
//STRIP001      }
//STRIP001
//STRIP001      // calculate text widths up to cChar
//STRIP001         if ( nStop > nIdx )
//STRIP001         {
//STRIP001             SwDrawTextInfo aDrawInf( pSh, *pOut, 0, GetTxt(), nIdx, nStop - nIdx );
//STRIP001             nProWidth += aIter.GetFnt()->_GetTxtSize( aDrawInf ).Width();
//STRIP001         }
//STRIP001
//STRIP001      nIdx = nStop;
//STRIP001      aIter.SeekAndChg( nIdx, pOut );
//STRIP001
//STRIP001      if ( cChar == CH_BREAK )
//STRIP001      {
//STRIP001          nWidth = Max( nWidth, nProWidth );
//STRIP001          nProWidth = 0;
//STRIP001          nIdx++;
//STRIP001      }
//STRIP001      else if ( cChar == CH_TAB )
//STRIP001      {
//STRIP001          // tab receives width of one space
//STRIP001             XubString sTmp( CH_BLANK );
//STRIP001             SwDrawTextInfo aDrawInf( pSh, *pOut, 0, sTmp, 0, 1 );
//STRIP001             nProWidth += aIter.GetFnt()->_GetTxtSize( aDrawInf ).Width();
//STRIP001          nIdx++;
//STRIP001      }
//STRIP001         else if ( cChar == CHAR_SOFTHYPHEN )
//STRIP001             ++nIdx;
//STRIP001         else if ( cChar == CHAR_HARDBLANK || cChar == CHAR_HARDHYPHEN )
//STRIP001         {
//STRIP001             XubString sTmp( cChar );
//STRIP001             SwDrawTextInfo aDrawInf( pSh, *pOut, 0, sTmp, 0, 1 );
//STRIP001             nProWidth += aIter.GetFnt()->_GetTxtSize( aDrawInf ).Width();
//STRIP001          nIdx++;
//STRIP001         }
//STRIP001      else if ( pHint && ( cChar == CH_TXTATR_BREAKWORD || CH_TXTATR_INWORD ) )
//STRIP001      {
//STRIP001          switch( pHint->Which() )
//STRIP001          {
//STRIP001              case RES_TXTATR_FTN :
//STRIP001              {
//STRIP001                  const XubString aTxt = pHint->GetFtn().GetNumStr();
//STRIP001                     SwDrawTextInfo aDrawInf( pSh, *pOut, 0, aTxt, 0, aTxt.Len() );
//STRIP001
//STRIP001                     nProWidth += aIter.GetFnt()->_GetTxtSize( aDrawInf ).Width();
//STRIP001                  break;
//STRIP001              }
//STRIP001              case RES_TXTATR_FIELD :
//STRIP001              {
//STRIP001                  SwField *pFld = (SwField*)pHint->GetFld().GetFld();
//STRIP001                  const String aTxt = pFld->GetCntnt( FALSE );
//STRIP001                     SwDrawTextInfo aDrawInf( pSh, *pOut, 0, aTxt, 0, aTxt.Len() );
//STRIP001
//STRIP001                     nProWidth += aIter.GetFnt()->_GetTxtSize( aDrawInf ).Width();
//STRIP001                  break;
//STRIP001              }
//STRIP001              default:
//STRIP001              {
//STRIP001              // any suggestions for a default action?
//STRIP001              }
//STRIP001          } // end of switch
//STRIP001          nIdx++;
//STRIP001      } // end of while
//STRIP001  }
//STRIP001
//STRIP001  nWidth = Max( nWidth, nProWidth );
//STRIP001
//STRIP001  // search for a text frame this node belongs to
//STRIP001  SwClientIter aClientIter( *(SwTxtNode*)this );
//STRIP001  SwClient* pLast = aClientIter.GoStart();
//STRIP001     SwTxtFrm* pFrm = 0;
//STRIP001
//STRIP001  while( pLast )
//STRIP001  {
//STRIP001      if ( pLast->ISA( SwTxtFrm ) )
//STRIP001      {
//STRIP001          SwTxtFrm* pTmpFrm = ( SwTxtFrm* )pLast;
//STRIP001          if ( pTmpFrm->GetOfst() <= nStt &&
//STRIP001              ( !pTmpFrm->GetFollow() ||
//STRIP001                 pTmpFrm->GetFollow()->GetOfst() > nStt ) )
//STRIP001          {
//STRIP001              pFrm = pTmpFrm;
//STRIP001              break;
//STRIP001          }
//STRIP001      }
//STRIP001      pLast = ++aClientIter;
//STRIP001  }
//STRIP001
//STRIP001  // search for the line containing nStt
//STRIP001     if ( pFrm && pFrm->HasPara() )
//STRIP001  {
//STRIP001      SwTxtInfo aInf( pFrm );
//STRIP001         SwTxtIter aLine( pFrm, &aInf );
//STRIP001      aLine.CharToLine( nStt );
//STRIP001         pOut->SetMapMode( aOldMap );
//STRIP001         return (USHORT)( nWidth ?
//STRIP001          ( ( 100 * aLine.GetCurr()->Height() ) / nWidth ) : 0 );
//STRIP001  }
//STRIP001  // no frame or no paragraph, we take the height of the character
//STRIP001  // at nStt as line height
//STRIP001
//STRIP001     aIter.SeekAndChg( nStt, pOut );
//STRIP001     pOut->SetMapMode( aOldMap );
//STRIP001
//STRIP001     SwDrawTextInfo aDrawInf( pSh, *pOut, 0, GetTxt(), nStt, 1 );
//STRIP001     return (USHORT)
//STRIP001            ( nWidth ? ((100 * aIter.GetFnt()->_GetTxtSize( aDrawInf ).Height()) / nWidth ) : 0 );
//STRIP001 }

/*N*/ SwFontIter::SwFontIter( const SwTxtNode& rNode, SwAttrHandler& rAH,
/*N*/                         xub_StrLen nStt, xub_StrLen nEnd )
/*N*/     : aFnt( *rAH.GetFont() ), rAttrHandler( rAH ), pHints( rNode.GetpSwpHints() ),
/*N*/       nStartIndex( 0 ), nEndIndex( 0 ), nCurrPos( nStt ), nEndPos( nEnd )
/*N*/ {
/*N*/     ASSERT( pHints,
/*N*/             "I think SwFontIter is too expensive if we do not have hints" )
/*N*/ }

/*N*/ SwFontIter::~SwFontIter()
/*N*/ {
/*N*/     rAttrHandler.Reset();
/*N*/ }

/*N*/ xub_StrLen SwFontIter::NextFontChg() const
/*N*/ {
/*N*/    xub_StrLen nNextPos = STRING_LEN;
/*N*/
/*N*/     if (pHints->GetStartCount() > nStartIndex) // Gibt es noch Starts?
/*N*/        nNextPos = (*pHints->GetStart(nStartIndex)->GetStart());
/*N*/     if (pHints->GetEndCount() > nEndIndex) // Gibt es noch Enden?
/*N*/     {
/*N*/         xub_StrLen nNextEnd = (*pHints->GetEnd(nEndIndex)->GetAnyEnd());
/*N*/         if ( nNextEnd < nNextPos ) nNextPos = nNextEnd; // Wer ist naeher?
/*N*/     }
/*N*/
/*N*/     return Min( nEndPos, nNextPos );
/*N*/ }

/*N*/ const SwFont& SwFontIter::GetCurrFont( xub_StrLen nNewPos )
/*N*/ {
/*N*/     ASSERT( nNewPos >= nCurrPos, "Do not use me (SwFontIter) like this" )
/*N*/
/*N*/     // change font for position nPos:
/*N*/     const SwTxtAttr *pTxtAttr;
/*N*/
/*N*/     if ( nStartIndex )
/*N*/   {
/*N*/       while ( ( nEndIndex < pHints->GetEndCount() ) &&
/*N*/                 (*(pTxtAttr = pHints->GetEnd(nEndIndex))->GetAnyEnd() <= nNewPos))
/*N*/       {
/*N*/             // close attributes in front of old position
/*N*/             if ( *pTxtAttr->GetStart() <= nCurrPos )
/*N*/                 rAttrHandler.PopAndChg( *pTxtAttr, aFnt );
/*N*/
/*N*/             nEndIndex++;
/*N*/       }
/*N*/   }
/*N*/     else // skip non open attributes
/*N*/   {
/*N*/       while ( ( nEndIndex < pHints->GetEndCount() ) &&
/*N*/                 (*(pTxtAttr = pHints->GetEnd(nEndIndex))->GetAnyEnd() <= nNewPos))
/*N*/       {
/*N*/           nEndIndex++;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   while ( ( nStartIndex < pHints->GetStartCount() ) &&
/*N*/            (*(pTxtAttr = pHints->GetStart(nStartIndex))->GetStart() <= nNewPos))
/*N*/   {
/*N*/         // open attributes behind new position
/*N*/         if ( *pTxtAttr->GetAnyEnd() > nNewPos )
/*N*/             rAttrHandler.PushAndChg( *pTxtAttr, aFnt );
/*N*/
/*N*/         nStartIndex++;
/*N*/   }
/*N*/
/*N*/     nCurrPos = nNewPos;
/*N*/
/*N*/     return aFnt;
/*N*/ }
