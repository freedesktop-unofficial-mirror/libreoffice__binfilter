/*************************************************************************
 *
 *  $RCSfile: sw_cellfml.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:40:56 $
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

#include <float.h>
#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif

#ifndef _FMTFLD_HXX //autogen
#include <fmtfld.hxx>
#endif
#ifndef _TXTFLD_HXX //autogen
#include <txtfld.hxx>
#endif
#ifndef _FRMFMT_HXX //autogen
#include <frmfmt.hxx>
#endif
#ifndef _LAYFRM_HXX
#include <layfrm.hxx>
#endif
#ifndef _CNTFRM_HXX
#include <cntfrm.hxx>
#endif
#ifndef _TABFRM_HXX
#include <tabfrm.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _DOCARY_HXX
#include <docary.hxx>
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>
#endif
#ifndef _SWTABLE_HXX
#include <swtable.hxx>
#endif
#ifndef _TBLSEL_HXX
#include <tblsel.hxx>
#endif
#ifndef _CELLFML_HXX
#include <cellfml.hxx>
#endif
#ifndef _CALC_HXX
#include <calc.hxx>
#endif
#ifndef _EXPFLD_HXX
#include <expfld.hxx>
#endif
#ifndef _USRFLD_HXX
#include <usrfld.hxx>
#endif
#ifndef _FLDDAT_HXX
#include <flddat.hxx>
#endif
#ifndef _CELLATR_HXX
#include <cellatr.hxx>
#endif
#ifndef _NDINDEX_HXX
#include <ndindex.hxx>
#endif
#ifndef _HINTS_HXX
#include <hints.hxx>
#endif
namespace binfilter {

const sal_Unicode cRelTrenner = ',';
const sal_Unicode cRelKennung = '';        // CTRL-R

const USHORT cMAXSTACKSIZE = 50;

/*N*/ const SwFrm* lcl_GetBoxFrm( const SwTableBox& rBox );
//STRIP001 long lcl_GetLongBoxNum( String& rStr );
//STRIP001 const SwTableBox* lcl_RelToBox( const SwTable&, const SwTableBox*, const String& );
//STRIP001 String lcl_BoxNmToRel( const SwTable&, const SwTableNode&,
//STRIP001                      const String& , const String& , BOOL );


/*************************************************************************
|*
|*  double SwTableBox::GetValue() const
|*      gebe den Wert dieser Box zurueck. Der Wert ergibt sich aus dem 1.
|*      TextNode. Beginnt dieser mit einer Zahl/Formel, so berechne diese;
|*      oder mit einem Feld, dann hole den Wert.
|*      Alle anderen Bedingungen returnen einen Fehler (oder 0 ?)
|*
|*  Ersterstellung      JP 30. Jun. 93
|*  Letzte Aenderung    JP 30. Jun. 93
|*
|*************************************************************************/

/*N*/ double SwTableBox::GetValue( SwTblCalcPara& rCalcPara ) const
/*N*/ {
/*N*/   double nRet = 0;
/*N*/
/*N*/   if( rCalcPara.rCalc.IsCalcError() )
/*?*/       return nRet;            // schon ein Fehler in der Berechnung
/*N*/
/*N*/   rCalcPara.rCalc.SetCalcError( CALC_SYNTAX );    // default immer Fehler
/*N*/
/*N*/   // keine Content Box ?
/*N*/   if( !pSttNd  )
/*?*/       return nRet;
/*N*/
/*N*/   if( rCalcPara.IncStackCnt() )
/*?*/       return nRet;
/*N*/
/*N*/   rCalcPara.SetLastTblBox( this );
/*N*/
/*N*/   // wird eine Rekursion erzeugt ?
/*N*/   SwTableBox* pBox = (SwTableBox*)this;
/*N*/   if( rCalcPara.pBoxStk->Seek_Entry( pBox ))
/*?*/       return nRet;            // steht schon auf dem Stack: FEHLER
/*N*/
/*N*/   // bei dieser Box nochmal aufsetzen
/*N*/   rCalcPara.SetLastTblBox( this );
/*N*/
/*N*/   rCalcPara.pBoxStk->Insert( pBox );      // eintragen
/*N*/   do {        // Middle-Check-Loop, damit aus dieser gesprungen werden kann
/*N*/               // hier aufgespannt, damit am Ende der Box-Pointer aus dem
/*N*/               // Stack ausgetragen wird
/*N*/       SwDoc* pDoc = GetFrmFmt()->GetDoc();
/*N*/
/*N*/       const SfxPoolItem* pItem;
/*N*/       if( SFX_ITEM_SET == GetFrmFmt()->GetItemState(
/*N*/                               RES_BOXATR_FORMULA, FALSE, &pItem ) )
/*N*/       {
/*?*/           rCalcPara.rCalc.SetCalcError( CALC_NOERR ); // wieder zuruecksetzen
/*?*/           if( !((SwTblBoxFormula*)pItem)->IsValid() )
/*?*/           {
/*?*/               // dann berechnen
/*?*/               DBG_BF_ASSERT(0, "STRIP"); //STRIP001 const SwTable* pTmp = rCalcPara.pTbl;
//STRIP001 /*?*/                rCalcPara.pTbl = &pBox->GetSttNd()->FindTableNode()->GetTable();
//STRIP001 /*?*/                ((SwTblBoxFormula*)pItem)->Calc( rCalcPara, nRet );
//STRIP001 /*?*/
//STRIP001 /*?*/                if( !rCalcPara.IsStackOverFlow() )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    SwFrmFmt* pFmt = pBox->ClaimFrmFmt();
//STRIP001 /*?*/                    SfxItemSet aTmp( pDoc->GetAttrPool(),
//STRIP001 /*?*/                                        RES_BOXATR_BEGIN,RES_BOXATR_END-1 );
//STRIP001 /*?*/                    aTmp.Put( SwTblBoxValue( nRet ) );
//STRIP001 /*?*/                    if( SFX_ITEM_SET != pFmt->GetItemState( RES_BOXATR_FORMAT ))
//STRIP001 /*?*/                        aTmp.Put( SwTblBoxNumFormat( 0 ));
//STRIP001 /*?*/                    pFmt->SetAttr( aTmp );
//STRIP001 /*?*/                }
//STRIP001 /*?*/                rCalcPara.pTbl = pTmp;
/*?*/           }
/*?*/           else
/*?*/               nRet = GetFrmFmt()->GetTblBoxValue().GetValue();
/*?*/           break;
/*N*/       }
/*N*/       else if( SFX_ITEM_SET == pBox->GetFrmFmt()->GetItemState(
/*N*/                               RES_BOXATR_VALUE, FALSE, &pItem ) )
/*N*/       {
/*?*/           rCalcPara.rCalc.SetCalcError( CALC_NOERR ); // wieder zuruecksetzen
/*?*/           nRet = ((SwTblBoxValue*)pItem)->GetValue();
/*?*/           break;
/*N*/       }
/*N*/
/*N*/       SwTxtNode* pTxtNd = pDoc->GetNodes()[ pSttNd->GetIndex() + 1 ]->GetTxtNode();
/*N*/       if( !pTxtNd )
/*?*/           break;
/*N*/
/*N*/       xub_StrLen nSttPos = 0;
/*N*/       const String& rTxt = pTxtNd->GetTxt();
/*N*/       while( nSttPos < rTxt.Len() &&
/*N*/               ( ' ' ==  rTxt.GetChar( nSttPos ) || '\t' ==  rTxt.GetChar( nSttPos ) ) )
/*?*/           ++nSttPos;
/*N*/
/*N*/       // beginnt an erster Position ein "RechenFeld", dann erfrage den Wert
/*N*/       // von diesem
/*N*/       sal_Unicode cChr;
/*N*/       if( nSttPos < rTxt.Len() &&
/*N*/           ( CH_TXTATR_BREAKWORD == ( cChr = rTxt.GetChar(nSttPos)) ||
/*N*/             CH_TXTATR_INWORD == cChr ))
/*N*/       {
/*N*/           SwIndex aIdx( pTxtNd, nSttPos );
/*N*/           SwTxtFld* pTxtFld = pTxtNd->GetTxtFld( aIdx );
/*N*/           if( !pTxtFld )
/*?*/               break;
/*N*/
/*N*/           rCalcPara.rCalc.SetCalcError( CALC_NOERR ); // wieder zuruecksetzen
/*N*/
/*N*/           const SwField* pFld = pTxtFld->GetFld().GetFld();
/*N*/           switch( pFld->GetTyp()->Which()  )
/*N*/           {
/*N*/           case RES_SETEXPFLD:
/*?*/               nRet = ((SwSetExpField*)pFld)->GetValue();
/*?*/               break;
/*?*/           case RES_USERFLD:
/*?*/               nRet = ((SwUserFieldType*)pFld)->GetValue();
/*?*/               break;
/*N*/           case RES_TABLEFLD:
/*N*/               {
/*N*/                   SwTblField* pTblFld = (SwTblField*)pFld;
/*N*/                   if( !pTblFld->IsValid() )       // ist der Wert gueltig ??
/*N*/                   {
/*N*/                       // die richtige Tabelle mitgeben!
/*N*/                       const SwTable* pTmp = rCalcPara.pTbl;
/*N*/                       rCalcPara.pTbl = &pTxtNd->FindTableNode()->GetTable();
/*N*/                       pTblFld->CalcField( rCalcPara );
/*N*/                       rCalcPara.pTbl = pTmp;
/*N*/                   }
/*N*/                   nRet = pTblFld->GetValue();
/*N*/               }
/*N*/               break;
/*N*/
/*N*/           case RES_DATETIMEFLD:
/*?*/               nRet = ((SwDateTimeField*)pFld)->GetValue();
/*?*/               break;
/*?*/
/*?*/           case RES_JUMPEDITFLD:
/*?*/               //JP 14.09.98: Bug 56112 - der Platzhalter kann nie einen
/*?*/               //              gueltigen Inhalt haben!
/*?*/               nRet = 0;
/*?*/               break;
/*?*/
/*?*/           default:
/*?*/               nRet = rCalcPara.rCalc.Calculate( pFld->Expand() ).GetDouble();
/*N*/           }
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           // Ergebnis ist 0 und kein Fehler!
/*N*/           rCalcPara.rCalc.SetCalcError( CALC_NOERR ); // wieder zuruecksetzen
/*N*/
/*N*/           double aNum;
/*N*/           String sTxt( rTxt.Copy( nSttPos ) );
/*N*/           ULONG nFmtIndex = GetFrmFmt()->GetTblBoxNumFmt().GetValue();
/*N*/
/*N*/           SvNumberFormatter* pNumFmtr = pDoc->GetNumberFormatter();
/*N*/
/*N*/           if( NUMBERFORMAT_TEXT == nFmtIndex )
/*N*/               nFmtIndex = 0;
/*N*/           // JP 22.04.98: Bug 49659 - Sonderbehandlung fuer Prozent
/*?*/           else if( sTxt.Len() &&
/*?*/                   NUMBERFORMAT_PERCENT == pNumFmtr->GetType( nFmtIndex ))
/*?*/           {
/*?*/               ULONG nTmpFmt = 0;
/*?*/               if( pNumFmtr->IsNumberFormat( sTxt, nTmpFmt, aNum ) &&
/*?*/                   NUMBERFORMAT_NUMBER == pNumFmtr->GetType( nTmpFmt ))
/*?*/                   sTxt += '%';
/*?*/           }
/*N*/
/*N*/           if( pNumFmtr->IsNumberFormat( sTxt, nFmtIndex, aNum ))
/*N*/               nRet = aNum;
/*N*/       }
/*N*/
/*N*/ // ?? sonst ist das ein Fehler
/*N*/   } while( FALSE );
/*N*/
/*N*/   if( !rCalcPara.IsStackOverFlow() )
/*N*/   {
/*N*/       rCalcPara.pBoxStk->Remove( pBox );      // raus aus dem Stack
/*N*/       rCalcPara.DecStackCnt();
/*N*/   }
/*N*/
/*N*/   //JP 12.01.99: mit Fehlererkennung, Bug 60794
/*N*/   if( DBL_MAX == nRet )
/*?*/       rCalcPara.rCalc.SetCalcError( CALC_SYNTAX );    // Fehler setzen
/*N*/
/*N*/   return nRet;
/*N*/ }

/*  */

// Struktur, die zum TabelleRechnen benoetigt wird

/*N*/ SwTblCalcPara::SwTblCalcPara( SwCalc& rCalculator, const SwTable& rTable )
/*N*/   : rCalc( rCalculator ), pTbl( &rTable ), nStackCnt( 0 ),
/*N*/   nMaxSize( cMAXSTACKSIZE ), pLastTblBox( 0 )
/*N*/ {
/*N*/   pBoxStk = new SwTableSortBoxes;
/*N*/ }

/*N*/ SwTblCalcPara::~SwTblCalcPara()
/*N*/ {
/*N*/   delete pBoxStk;
/*N*/ }

//STRIP001 BOOL SwTblCalcPara::CalcWithStackOverflow()
//STRIP001 {
//STRIP001  // falls ein StackUeberlauf erkannt wurde, sollte mit
//STRIP001  // der letzten Box noch mal aufgesetzt werden. Irgend
//STRIP001  // ein Weg sollte dann
//STRIP001  USHORT nSaveMaxSize = nMaxSize;
//STRIP001
//STRIP001  nMaxSize = cMAXSTACKSIZE - 5;
//STRIP001  USHORT nCnt = 0;
//STRIP001  SwTableBoxes aStackOverFlows;
//STRIP001  do {
//STRIP001      SwTableBox* pBox = (SwTableBox*)pLastTblBox;
//STRIP001      nStackCnt = 0;
//STRIP001      rCalc.SetCalcError( CALC_NOERR );
//STRIP001      aStackOverFlows.C40_INSERT( SwTableBox, pBox, nCnt++ );
//STRIP001
//STRIP001      pBoxStk->Remove( pBox );
//STRIP001      pBox->GetValue( *this );
//STRIP001  } while( IsStackOverFlow() );
//STRIP001
//STRIP001  nMaxSize = cMAXSTACKSIZE - 3;       // es muss mind. 1 Stufe tiefer gehen!
//STRIP001
//STRIP001  // falls Rekursionen erkannt wurden
//STRIP001  nStackCnt = 0;
//STRIP001  rCalc.SetCalcError( CALC_NOERR );
//STRIP001  pBoxStk->Remove( USHORT(0), pBoxStk->Count() );
//STRIP001
//STRIP001  while( !rCalc.IsCalcError() && nCnt )
//STRIP001  {
//STRIP001      aStackOverFlows[ --nCnt ]->GetValue( *this );
//STRIP001      if( IsStackOverFlow() && !CalcWithStackOverflow() )
//STRIP001          break;
//STRIP001  }
//STRIP001
//STRIP001  nMaxSize = nSaveMaxSize;
//STRIP001  aStackOverFlows.Remove( 0, aStackOverFlows.Count() );
//STRIP001  return !rCalc.IsCalcError();
//STRIP001 }

/*  */

/*N*/ SwTableFormula::SwTableFormula( const String& rFormel )
/*N*/   : sFormel( rFormel )
/*N*/ {
/*N*/   eNmType = EXTRNL_NAME;
/*N*/   bValidValue = FALSE;
/*N*/ }

/*N*/ void SwTableFormula::_MakeFormel( const SwTable& rTbl, String& rNewStr,
/*N*/                   String& rFirstBox, String* pLastBox, void* pPara ) const
/*N*/ {
/*N*/   SwTblCalcPara* pCalcPara = (SwTblCalcPara*)pPara;
/*N*/   if( pCalcPara->rCalc.IsCalcError() )        // ist schon Fehler gesetzt ?
/*?*/       return;
/*N*/
/*N*/   SwTableBox* pSttBox, *pEndBox = 0;
/*N*/
/*N*/   rFirstBox.Erase(0,1);       // Kennung fuer Box loeschen
/*N*/   // ein Bereich in dieser Klammer ?
/*N*/   if( pLastBox )
/*N*/   {
/*N*/   //TODOUNICODE: does it work?
/*N*/ //        pEndBox = (SwTableBox*)(long)(*pLastBox);
/*N*/       pEndBox = (SwTableBox*)pLastBox->ToInt32();
/*N*/
/*N*/       // ist das ueberhaupt ein gueltiger Pointer ??
/*N*/       if( !rTbl.GetTabSortBoxes().Seek_Entry( pEndBox ))
/*?*/           pEndBox = 0;
/*N*/       rFirstBox.Erase( 0, pLastBox->Len()+1 );
/*N*/   }
/*N*/   //TODOUNICODE: does it work?
/*N*/ //    pSttBox = (SwTableBox*)(long)rFirstBox;
/*N*/   pSttBox = (SwTableBox*)rFirstBox.ToInt32();
/*N*/   // ist das ueberhaupt ein gueltiger Pointer ??
/*N*/   if( !rTbl.GetTabSortBoxes().Seek_Entry( pSttBox ))
/*?*/       pSttBox = 0;
/*N*/
/*N*/   rNewStr += ' ';
/*N*/   if( pEndBox && pSttBox )    // Bereich ?
/*N*/   {
/*N*/       // hole ueber das Layout alle "selectierten" Boxen und berechne
/*N*/       // deren Werte
/*N*/       SwSelBoxes aBoxes;
/*N*/       GetBoxes( *pSttBox, *pEndBox, aBoxes );
/*N*/
/*N*/       rNewStr += '(';
/*N*/       for( USHORT n = 0; n < aBoxes.Count() &&
/*N*/                          !pCalcPara->rCalc.IsCalcError(); ++n )
/*N*/       {
/*N*/           if( n )
/*N*/               rNewStr += cListDelim;
/*N*/           rNewStr += pCalcPara->rCalc.GetStrResult(
/*N*/                       aBoxes[n]->GetValue( *pCalcPara ), FALSE );
/*N*/       }
/*N*/       rNewStr += ')';
/*N*/   }
/*N*/   else if( pSttBox && !pLastBox )         // nur die StartBox ?
/*N*/                           //JP 12.01.99: und keine EndBox in der Formel!
/*N*/       // Berechne den Wert der Box
/*N*/       rNewStr += pCalcPara->rCalc.GetStrResult(
/*N*/                           pSttBox->GetValue( *pCalcPara ), FALSE );
/*N*/   else
/*?*/       pCalcPara->rCalc.SetCalcError( CALC_SYNTAX );   // Fehler setzen
/*N*/   rNewStr += ' ';
/*N*/ }

//STRIP001 void SwTableFormula::RelNmsToBoxNms( const SwTable& rTbl, String& rNewStr,
//STRIP001          String& rFirstBox, String* pLastBox, void* pPara ) const
//STRIP001 {
//STRIP001  // relativen Namen zu Box-Namen (externe Darstellung)
//STRIP001  SwNode* pNd = (SwNode*)pPara;
//STRIP001  ASSERT( pNd, "Feld steht in keinem TextNode" );
//STRIP001  const SwTableBox *pRelBox, *pBox = (SwTableBox *)rTbl.GetTblBox(
//STRIP001                  pNd->FindTableBoxStartNode()->GetIndex() );
//STRIP001
//STRIP001  rNewStr += rFirstBox.Copy(0,1);     // Kennung fuer Box erhalten
//STRIP001  rFirstBox.Erase(0,1);
//STRIP001  if( pLastBox )
//STRIP001  {
//STRIP001      if( 0 != ( pRelBox = lcl_RelToBox( rTbl, pBox, *pLastBox )) )
//STRIP001          rNewStr += pRelBox->GetName();
//STRIP001      else
//STRIP001          rNewStr.AppendAscii("A1");
//STRIP001      rNewStr += ':';
//STRIP001      rFirstBox.Erase( 0, pLastBox->Len()+1 );
//STRIP001  }
//STRIP001
//STRIP001  if( 0 != ( pRelBox = lcl_RelToBox( rTbl, pBox, rFirstBox )) )
//STRIP001      rNewStr += pRelBox->GetName();
//STRIP001  else
//STRIP001      rNewStr.AppendAscii("A1");
//STRIP001
//STRIP001  // Kennung fuer Box erhalten
//STRIP001  rNewStr += rFirstBox.GetChar( rFirstBox.Len() - 1 );
//STRIP001 }

//STRIP001 void SwTableFormula::RelBoxNmsToPtr( const SwTable& rTbl, String& rNewStr,
//STRIP001          String& rFirstBox, String* pLastBox, void* pPara ) const
//STRIP001 {
//STRIP001  // relativen Namen zu Box-Pointern (interne Darstellung)
//STRIP001  SwNode* pNd = (SwNode*)pPara;
//STRIP001  ASSERT( pNd, "Feld steht in keinem Node" );
//STRIP001  const SwTableBox *pRelBox, *pBox = (SwTableBox*)rTbl.GetTblBox(
//STRIP001                  pNd->FindTableBoxStartNode()->GetIndex() );
//STRIP001
//STRIP001  rNewStr += rFirstBox.Copy(0,1);     // Kennung fuer Box erhalten
//STRIP001  rFirstBox.Erase(0,1);
//STRIP001  if( pLastBox )
//STRIP001  {
//STRIP001      if( 0 != ( pRelBox = lcl_RelToBox( rTbl, pBox, *pLastBox )) )
//STRIP001          rNewStr += String::CreateFromInt32( (long)pRelBox );
//STRIP001      else
//STRIP001          rNewStr += '0';
//STRIP001      rNewStr += ':';
//STRIP001      rFirstBox.Erase( 0, pLastBox->Len()+1 );
//STRIP001  }
//STRIP001
//STRIP001  if( 0 != ( pRelBox = lcl_RelToBox( rTbl, pBox, rFirstBox )) )
//STRIP001      rNewStr += String::CreateFromInt32( (long)pRelBox );
//STRIP001  else
//STRIP001      rNewStr += '0';
//STRIP001
//STRIP001  // Kennung fuer Box erhalten
//STRIP001  rNewStr += rFirstBox.GetChar( rFirstBox.Len() - 1 );
//STRIP001 }


//STRIP001 void SwTableFormula::BoxNmsToRelNm( const SwTable& rTbl, String& rNewStr,
//STRIP001                  String& rFirstBox, String* pLastBox, void* pPara ) const
//STRIP001 {
//STRIP001  // Box-Namen (externe Darstellung) zu relativen Namen
//STRIP001  SwNode* pNd = (SwNode*)pPara;
//STRIP001  ASSERT( pNd, "Feld steht in keinem Node" );
//STRIP001  const SwTableNode* pTblNd = pNd->FindTableNode();
//STRIP001
//STRIP001  String sRefBoxNm;
//STRIP001  if( &pTblNd->GetTable() == &rTbl )
//STRIP001  {
//STRIP001      const SwTableBox *pBox = rTbl.GetTblBox(
//STRIP001              pNd->FindTableBoxStartNode()->GetIndex() );
//STRIP001      ASSERT( pBox, "Feld steht in keiner Tabelle" );
//STRIP001      sRefBoxNm = pBox->GetName();
//STRIP001  }
//STRIP001
//STRIP001  rNewStr += rFirstBox.Copy(0,1);     // Kennung fuer Box erhalten
//STRIP001  rFirstBox.Erase(0,1);
//STRIP001  if( pLastBox )
//STRIP001  {
//STRIP001      rNewStr += lcl_BoxNmToRel( rTbl, *pTblNd, sRefBoxNm, *pLastBox,
//STRIP001                              eNmType == EXTRNL_NAME );
//STRIP001      rNewStr += ':';
//STRIP001      rFirstBox.Erase( 0, pLastBox->Len()+1 );
//STRIP001  }
//STRIP001
//STRIP001  rNewStr += lcl_BoxNmToRel( rTbl, *pTblNd, sRefBoxNm, rFirstBox,
//STRIP001                          eNmType == EXTRNL_NAME );
//STRIP001
//STRIP001  // Kennung fuer Box erhalten
//STRIP001  rNewStr += rFirstBox.GetChar( rFirstBox.Len() - 1 );
//STRIP001 }


/*N*/ void SwTableFormula::PtrToBoxNms( const SwTable& rTbl, String& rNewStr,
/*N*/                       String& rFirstBox, String* pLastBox, void* ) const
/*N*/ {
/*N*/   // ein Bereich in dieser Klammer ?
/*N*/   SwTableBox* pBox;
/*N*/
/*N*/   rNewStr += rFirstBox.Copy(0,1);     // Kennung fuer Box erhalten
/*N*/   rFirstBox.Erase(0,1);
/*N*/   if( pLastBox )
/*N*/   {
/*N*/ //        pBox = (SwTableBox*)(long)(*pLastBox);
/*N*/       pBox = (SwTableBox*)pLastBox->ToInt32();
/*N*/
/*N*/       // ist das ueberhaupt ein gueltiger Pointer ??
/*N*/       if( rTbl.GetTabSortBoxes().Seek_Entry( pBox ))
/*N*/           rNewStr += pBox->GetName();
/*N*/       else
/*N*/           rNewStr += '?';
/*N*/       rNewStr += ':';
/*N*/       rFirstBox.Erase( 0, pLastBox->Len()+1 );
/*N*/   }
/*N*/
/*N*/ //    pBox = (SwTableBox*)(long)rFirstBox;
/*N*/   pBox = (SwTableBox*)rFirstBox.ToInt32();
/*N*/   // ist das ueberhaupt ein gueltiger Pointer ??
/*N*/   if( rTbl.GetTabSortBoxes().Seek_Entry( pBox ))
/*N*/       rNewStr += pBox->GetName();
/*N*/   else
/*N*/       rNewStr += '?';
/*N*/
/*N*/   // Kennung fuer Box erhalten
/*N*/   rNewStr += rFirstBox.GetChar( rFirstBox.Len() - 1 );
/*N*/ }

/*N*/ void SwTableFormula::BoxNmsToPtr( const SwTable& rTbl, String& rNewStr,
/*N*/                       String& rFirstBox, String* pLastBox, void* ) const
/*N*/ {
/*N*/   // ein Bereich in dieser Klammer ?
/*N*/   const SwTableBox* pBox;
/*N*/
/*N*/   rNewStr += rFirstBox.Copy(0,1);     // Kennung fuer Box erhalten
/*N*/   rFirstBox.Erase(0,1);
/*N*/   if( pLastBox )
/*N*/   {
/*N*/       pBox = rTbl.GetTblBox( *pLastBox );
/*N*/       rNewStr += String::CreateFromInt32( (long)pBox );
/*N*/       rNewStr += ':';
/*N*/       rFirstBox.Erase( 0, pLastBox->Len()+1 );
/*N*/   }
/*N*/
/*N*/   pBox = rTbl.GetTblBox( rFirstBox );
/*N*/   rNewStr += String::CreateFromInt32( (long)pBox );
/*N*/
/*N*/   // Kennung fuer Box erhalten
/*N*/   rNewStr += rFirstBox.GetChar( rFirstBox.Len() - 1 );
/*N*/ }

    // erzeuge die externe (fuer UI) Formel
/*N*/ void SwTableFormula::PtrToBoxNm( const SwTable* pTbl )
/*N*/ {
/*N*/   const SwNode* pNd = 0;
/*N*/   FnScanFormel fnFormel = 0;
/*N*/   switch( eNmType)
/*N*/   {
/*N*/   case INTRNL_NAME:
/*N*/       if( pTbl )
/*N*/           fnFormel = &SwTableFormula::PtrToBoxNms;
/*N*/       break;
/*N*/   case REL_NAME:
/*?*/       if( pTbl )
/*?*/       {
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 fnFormel = &SwTableFormula::RelNmsToBoxNms;
//STRIP001 /*?*/            pNd = GetNodeOfFormula();
/*?*/       }
/*?*/       break;
/*N*/   case EXTRNL_NAME:
/*N*/       return;
/*N*/   }
/*?*/   sFormel = ScanString( fnFormel, *pTbl, (void*)pNd );
/*?*/   eNmType = EXTRNL_NAME;
/*N*/ }

    // erzeuge die interne (in CORE) Formel
/*N*/ void SwTableFormula::BoxNmToPtr( const SwTable* pTbl )
/*N*/ {
/*N*/   const SwNode* pNd = 0;
/*N*/   FnScanFormel fnFormel = 0;
/*N*/   switch( eNmType)
/*N*/   {
/*N*/   case EXTRNL_NAME:
/*?*/       if( pTbl )
/*?*/           fnFormel = &SwTableFormula::BoxNmsToPtr;
/*?*/       break;
/*?*/   case REL_NAME:
/*?*/       if( pTbl )
/*?*/       {
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 fnFormel = &SwTableFormula::RelBoxNmsToPtr;
//STRIP001 /*?*/            pNd = GetNodeOfFormula();
/*?*/       }
/*?*/       break;
/*?*/   case INTRNL_NAME:
/*?*/       return;
/*N*/   }
/*N*/   sFormel = ScanString( fnFormel, *pTbl, (void*)pNd );
/*N*/   eNmType = INTRNL_NAME;
/*N*/ }

    // erzeuge die relative (fuers Kopieren) Formel
//STRIP001 void SwTableFormula::ToRelBoxNm( const SwTable* pTbl )
//STRIP001 {
//STRIP001  const SwNode* pNd = 0;
//STRIP001  FnScanFormel fnFormel = 0;
//STRIP001  switch( eNmType)
//STRIP001  {
//STRIP001  case INTRNL_NAME:
//STRIP001  case EXTRNL_NAME:
//STRIP001      if( pTbl )
//STRIP001      {
//STRIP001          fnFormel = &SwTableFormula::BoxNmsToRelNm;
//STRIP001          pNd = GetNodeOfFormula();
//STRIP001      }
//STRIP001      break;
//STRIP001  case REL_NAME:
//STRIP001      return;
//STRIP001  }
//STRIP001  sFormel = ScanString( fnFormel, *pTbl, (void*)pNd );
//STRIP001  eNmType = REL_NAME;
//STRIP001 }


/*N*/ String SwTableFormula::ScanString( FnScanFormel fnFormel, const SwTable& rTbl,
/*N*/                                   void* pPara ) const
/*N*/ {
/*N*/   String aStr;
/*N*/   USHORT nFml = 0, nStt = 0, nEnd = 0, nTrenner;
/*N*/
/*N*/   do {
/*N*/       // falls der Formel ein Name vorangestellt ist, diese Tabelle
/*N*/       // benutzen !!
/*N*/       const SwTable* pTbl = &rTbl;
/*N*/
/*N*/       nStt = sFormel.Search( '<', nFml );
/*N*/       if( STRING_NOTFOUND != nStt )
/*N*/       {
/*N*/           while( STRING_NOTFOUND != nStt &&
/*N*/               ( ' ' == sFormel.GetChar( nStt + 1 ) ||
/*N*/                 '=' == sFormel.GetChar( nStt + 1 ) ) )
/*?*/               nStt = sFormel.Search( '<', nStt + 1 );
/*N*/
/*N*/           if( STRING_NOTFOUND != nStt )
/*N*/               nEnd = sFormel.Search( '>', nStt+1 );
/*N*/       }
/*N*/       if( STRING_NOTFOUND == nStt || STRING_NOTFOUND == nEnd )
/*N*/       {
/*N*/           // den Rest setzen und beenden
/*N*/           aStr.Insert( sFormel, nFml, sFormel.Len() - nFml );
/*N*/           break;
/*N*/       }
/*N*/       aStr.Insert( sFormel, nFml, nStt - nFml );  // Anfang schreiben
/*N*/
/*N*/       if( fnFormel != NULL )
/*N*/       {
/*N*/           // ist ein TabellenName vorangestellt ??
/*N*/           // JP 16.02.99: SplitMergeBoxNm behandeln den Namen selbst
/*N*/           // JP 22.02.99: der CAST muss fuer den Linux-Compiler sein
/*N*/           // JP 28.06.99: rel. BoxName have no preceding tablename!
/*N*/           if( fnFormel != (FnScanFormel)&SwTableFormula::_SplitMergeBoxNm &&
/*N*/               1 < sFormel.Len() && cRelKennung != sFormel.GetChar( 1 ) &&
/*N*/               STRING_NOTFOUND != ( nTrenner = sFormel.Search( '.', nStt ))
/*N*/               && nTrenner < nEnd )
/*N*/           {
/*?*/               String sTblNm( sFormel.Copy( nStt, nEnd - nStt ));
/*?*/
/*?*/               // falls im Namen schon die Punkte enthalten sind,
/*?*/               // treten diese immer paarig auf!!! (A1.1.1 !!)
/*?*/               if( (sTblNm.GetTokenCount( '.' ) - 1 ) & 1 )
/*?*/               {
/*?*/                   sTblNm.Erase( nTrenner - nStt );
/*?*/
/*?*/                   // beim Bauen der Formel ist der TabellenName unerwuenscht
/*?*/                   //JP 22.02.99: der CAST muss fuer den Linux-Compiler sein
/*?*/                   if( fnFormel != (FnScanFormel)&SwTableFormula::_MakeFormel )
/*?*/                       aStr += sTblNm;
/*?*/                   nStt = nTrenner;
/*?*/
/*?*/                   sTblNm.Erase( 0, 1 );   // Trenner loeschen
/*?*/                   if( sTblNm != rTbl.GetFrmFmt()->GetName() )
/*?*/                   {
/*?*/                       // dann suchen wir uns mal unsere Tabelle:
/*?*/                       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 const SwTable* pFnd = FindTable(
//STRIP001 /*?*/                                                *rTbl.GetFrmFmt()->GetDoc(),
//STRIP001 /*?*/                                                sTblNm );
//STRIP001 /*?*/                        if( pFnd )
//STRIP001 /*?*/                            pTbl = pFnd;
//STRIP001 /*?*/                        // ??
//STRIP001 /*?*/                        ASSERT( pFnd, "Tabelle nicht gefunden, was nun?" );
/*?*/                   }
/*?*/               }
/*N*/           }
/*N*/
/*N*/           String sBox( sFormel.Copy( nStt, nEnd - nStt + 1 ));
/*N*/           // ein Bereich in dieser Klammer ?
/*N*/           if( STRING_NOTFOUND != ( nTrenner = sFormel.Search( ':', nStt ))
/*N*/               && nTrenner < nEnd )
/*N*/           {
/*N*/               // ohne die Anfangsklammer
/*N*/               String aFirstBox( sFormel.Copy( nStt+1, nTrenner - nStt - 1 ));
/*N*/               (this->*fnFormel)( *pTbl, aStr, sBox, &aFirstBox, pPara );
/*N*/           }
/*N*/           else
/*N*/               (this->*fnFormel)( *pTbl, aStr, sBox, 0, pPara );
/*N*/       }
/*N*/
/*N*/       nFml = nEnd+1;
/*N*/   } while( TRUE );
/*N*/   return aStr;
/*N*/ }

//STRIP001 const SwTable* SwTableFormula::FindTable( SwDoc& rDoc, const String& rNm ) const
//STRIP001 {
//STRIP001  const SwFrmFmts& rTblFmts = *rDoc.GetTblFrmFmts();
//STRIP001  const SwTable* pTmpTbl, *pRet = 0;
//STRIP001  for( USHORT nFmtCnt = rTblFmts.Count(); nFmtCnt; )
//STRIP001  {
//STRIP001      SwFrmFmt* pFmt = rTblFmts[ --nFmtCnt ];
//STRIP001      // falls wir von Sw3Writer gerufen werden, dann ist dem
//STRIP001      // FormatNamen eine Nummer anhaengig
//STRIP001      SwTableBox* pFBox;
//STRIP001      if( COMPARE_EQUAL == rNm.CompareTo( pFmt->GetName(),
//STRIP001                                      pFmt->GetName().Search( 0x0a ) ) &&
//STRIP001          0 != ( pTmpTbl = SwTable::FindTable( pFmt ) ) &&
//STRIP001          0 != (pFBox = pTmpTbl->GetTabSortBoxes()[0] ) &&
//STRIP001          pFBox->GetSttNd() &&
//STRIP001          pFBox->GetSttNd()->GetNodes().IsDocNodes() )
//STRIP001      {
//STRIP001          // eine Tabelle im normalen NodesArr
//STRIP001          pRet = pTmpTbl;
//STRIP001          break;
//STRIP001      }
//STRIP001  }
//STRIP001  return pRet;
//STRIP001 }

/*  */

/*N*/ const SwFrm* lcl_GetBoxFrm( const SwTableBox& rBox )
/*N*/ {
/*

    // oder besser ueber die Box den Frame suchen

    SwClientIter aIter( *pBox->GetFrmFmt() );
    ULONG nMinPos = ULONG_MAX;
    const SwFrm* pFnd = 0;
    for( SwFrm* pF = (SwFrm*)aIter.First( TYPE( SwCellFrm )); pF;
            pF = (SwFrm*)aIter.Next() )
    {
        if( pF->Frm().Y() <
    }
*/
/*N*/
/*N*/   SwNodeIndex aIdx( *rBox.GetSttNd() );
/*N*/   SwCntntNode* pCNd = aIdx.GetNodes().GoNext( &aIdx );
/*N*/   ASSERT( pCNd, "Box hat keinen TextNode" );
/*N*/   Point aPt;      // den im Layout 1. Frame returnen - Tab.Kopfzeile !!
/*N*/   return pCNd->GetFrm( &aPt, NULL, FALSE );
/*N*/ }

//STRIP001 long lcl_GetLongBoxNum( String& rStr )
//STRIP001 {
//STRIP001  USHORT nPos;
//STRIP001  long nRet;
//STRIP001  if( STRING_NOTFOUND == ( nPos = rStr.Search( cRelTrenner ) ))
//STRIP001  {
//STRIP001      nRet = rStr.ToInt32();
//STRIP001      rStr.Erase();
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      nRet = rStr.Copy( 0, nPos ).ToInt32();
//STRIP001      rStr.Erase( 0, nPos+1 );
//STRIP001  }
//STRIP001  return nRet;
//STRIP001 }

//STRIP001 const SwTableBox* lcl_RelToBox( const SwTable& rTbl,
//STRIP001                                  const SwTableBox* pRefBox,
//STRIP001                                  const String& rGetName )
//STRIP001 {
//STRIP001  // hole die Line
//STRIP001  const SwTableBox* pBox = 0;
//STRIP001  String sGetName( rGetName );
//STRIP001
//STRIP001  // ist es denn wirklich eine relative Angabe??
//STRIP001  if( cRelKennung == sGetName.GetChar(0) )            // ja, ...
//STRIP001  {
//STRIP001      if( !pRefBox )
//STRIP001          return 0;
//STRIP001
//STRIP001      sGetName.Erase( 0, 1 );
//STRIP001
//STRIP001      const SwTableLines* pLines = (SwTableLines*)&rTbl.GetTabLines();
//STRIP001      const SwTableBoxes* pBoxes;
//STRIP001      const SwTableLine* pLine;
//STRIP001
//STRIP001      // bestimme erst mal die Start-Werte der Box:
//STRIP001      pBox = (SwTableBox*)pRefBox;
//STRIP001      pLine = pBox->GetUpper();
//STRIP001      while( pLine->GetUpper() )
//STRIP001      {
//STRIP001          pBox = pLine->GetUpper();
//STRIP001          pLine = pBox->GetUpper();
//STRIP001      }
//STRIP001      USHORT nSttBox = pLine->GetTabBoxes().GetPos( pBox );
//STRIP001      USHORT nSttLine = rTbl.GetTabLines().GetPos( pLine );
//STRIP001
//STRIP001      long nBoxOffset = lcl_GetLongBoxNum( sGetName ) + nSttBox;
//STRIP001      long nLineOffset = lcl_GetLongBoxNum( sGetName ) + nSttLine;
//STRIP001
//STRIP001      if( nBoxOffset < 0 || nBoxOffset >= USHRT_MAX ||
//STRIP001          nLineOffset < 0 || nLineOffset >= USHRT_MAX )
//STRIP001          return 0;
//STRIP001
//STRIP001      if( nLineOffset >= long(pLines->Count()) )
//STRIP001          return 0;
//STRIP001
//STRIP001      pLine = (*pLines)[ USHORT(nLineOffset) ];
//STRIP001
//STRIP001      // dann suche die Box
//STRIP001      pBoxes = &pLine->GetTabBoxes();
//STRIP001      if( nBoxOffset >= long(pBoxes->Count()) )
//STRIP001          return 0;
//STRIP001      pBox = (*pBoxes)[ USHORT(nBoxOffset) ];
//STRIP001
//STRIP001      while( sGetName.Len() )
//STRIP001      {
//STRIP001          nSttBox = SwTable::_GetBoxNum( sGetName );
//STRIP001          pLines = &pBox->GetTabLines();
//STRIP001          if( nSttBox )
//STRIP001              --nSttBox;
//STRIP001
//STRIP001          nSttLine = SwTable::_GetBoxNum( sGetName );
//STRIP001
//STRIP001          // bestimme die Line
//STRIP001          if( !nSttLine || nSttLine > pLines->Count() )
//STRIP001              break;
//STRIP001          pLine = (*pLines)[ nSttLine-1 ];
//STRIP001
//STRIP001          // bestimme die Box
//STRIP001          pBoxes = &pLine->GetTabBoxes();
//STRIP001          if( nSttBox >= pBoxes->Count() )
//STRIP001              break;
//STRIP001          pBox = (*pBoxes)[ nSttBox ];
//STRIP001      }
//STRIP001
//STRIP001      if( pBox )
//STRIP001      {
//STRIP001          if( !pBox->GetSttNd() )
//STRIP001              // "herunterfallen lassen" bis zur ersten Box
//STRIP001              while( pBox->GetTabLines().Count() )
//STRIP001                  pBox = pBox->GetTabLines()[0]->GetTabBoxes()[0];
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      // sonst ist es eine absolute externe Darstellung:
//STRIP001      pBox = rTbl.GetTblBox( sGetName );
//STRIP001  }
//STRIP001  return pBox;
//STRIP001 }

//STRIP001 String lcl_BoxNmToRel( const SwTable& rTbl, const SwTableNode& rTblNd,
//STRIP001                          const String& rRefBoxNm, const String& rGetStr,
//STRIP001                          BOOL bExtrnlNm )
//STRIP001 {
//STRIP001  String sCpy( rRefBoxNm );
//STRIP001  String sTmp( rGetStr );
//STRIP001  if( !bExtrnlNm )
//STRIP001  {
//STRIP001      // in die Externe Darstellung umwandeln.
//STRIP001 //       SwTableBox* pBox = (SwTableBox*)(long)sTmp;
//STRIP001      SwTableBox* pBox = (SwTableBox*)sTmp.ToInt32();
//STRIP001      if( !rTbl.GetTabSortBoxes().Seek_Entry( pBox ))
//STRIP001          return '?';
//STRIP001      sTmp = pBox->GetName();
//STRIP001  }
//STRIP001
//STRIP001  // sollte die es eine Tabellen uebergreifende Formel sein, dann behalte
//STRIP001  // die externe Darstellung bei:
//STRIP001  if( &rTbl == &rTblNd.GetTable() )
//STRIP001  {
//STRIP001      long nBox = SwTable::_GetBoxNum( sTmp, TRUE );
//STRIP001      nBox -= SwTable::_GetBoxNum( sCpy, TRUE );
//STRIP001      long nLine = SwTable::_GetBoxNum( sTmp );
//STRIP001      nLine -= SwTable::_GetBoxNum( sCpy );
//STRIP001
//STRIP001      sCpy = sTmp;        //JP 01.11.95: den Rest aus dem BoxNamen anhaengen
//STRIP001
//STRIP001      sTmp = cRelKennung;
//STRIP001      sTmp += String::CreateFromInt32( nBox );
//STRIP001      sTmp += cRelTrenner;
//STRIP001      sTmp += String::CreateFromInt32( nLine );
//STRIP001
//STRIP001      if( sCpy.Len() )
//STRIP001      {
//STRIP001          sTmp += cRelTrenner;
//STRIP001          sTmp += sCpy;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if( sTmp.Len() && '>' == sTmp.GetChar( sTmp.Len() - 1 ))
//STRIP001      sTmp.Erase( sTmp.Len()-1 );
//STRIP001
//STRIP001  return sTmp;
//STRIP001 }

//STRIP001 USHORT SwTableFormula::GetBoxesOfFormula( const SwTable& rTbl,
//STRIP001                                      SwSelBoxes& rBoxes )
//STRIP001 {
//STRIP001  if( rBoxes.Count() )
//STRIP001      rBoxes.Remove( USHORT(0), rBoxes.Count() );
//STRIP001
//STRIP001  BoxNmToPtr( &rTbl );
//STRIP001  ScanString( &SwTableFormula::_GetFmlBoxes, rTbl, &rBoxes );
//STRIP001  return rBoxes.Count();
//STRIP001 }

//STRIP001 void SwTableFormula::_GetFmlBoxes( const SwTable& rTbl, String& rNewStr,
//STRIP001                  String& rFirstBox, String* pLastBox, void* pPara ) const
//STRIP001 {
//STRIP001  SwSelBoxes* pBoxes = (SwSelBoxes*)pPara;
//STRIP001  SwTableBox* pSttBox, *pEndBox = 0;
//STRIP001
//STRIP001  rFirstBox.Erase(0,1);       // Kennung fuer Box loeschen
//STRIP001  // ein Bereich in dieser Klammer ?
//STRIP001  if( pLastBox )
//STRIP001  {
//STRIP001 //       pEndBox = (SwTableBox*)(long)(*pLastBox);
//STRIP001      pEndBox = (SwTableBox*)pLastBox->ToInt32();
//STRIP001
//STRIP001      // ist das ueberhaupt ein gueltiger Pointer ??
//STRIP001      if( !rTbl.GetTabSortBoxes().Seek_Entry( pEndBox ))
//STRIP001          pEndBox = 0;
//STRIP001      rFirstBox.Erase( 0, pLastBox->Len()+1 );
//STRIP001  }
//STRIP001
//STRIP001 //   pSttBox = (SwTableBox*)(long)rFirstBox;
//STRIP001  pSttBox = (SwTableBox*)rFirstBox.ToInt32();
//STRIP001  // ist das ueberhaupt ein gueltiger Pointer ??
//STRIP001  if( !rTbl.GetTabSortBoxes().Seek_Entry( pSttBox ))
//STRIP001      pSttBox = 0;
//STRIP001
//STRIP001  if( pEndBox && pSttBox )    // Bereich ?
//STRIP001  {
//STRIP001      // ueber das Layout alle "selectierten" Boxen und berechne
//STRIP001      // deren Werte
//STRIP001      SwSelBoxes aBoxes;
//STRIP001      GetBoxes( *pSttBox, *pEndBox, aBoxes );
//STRIP001      pBoxes->Insert( &aBoxes );
//STRIP001  }
//STRIP001  else if( pSttBox )          // nur die StartBox ?
//STRIP001      pBoxes->Insert( pSttBox );
//STRIP001 }

/*N*/ void SwTableFormula::GetBoxes( const SwTableBox& rSttBox,
/*N*/                               const SwTableBox& rEndBox,
/*N*/                               SwSelBoxes& rBoxes ) const
/*N*/ {
/*N*/   // hole ueber das Layout alle "selektierten" Boxen
/*N*/   const SwLayoutFrm *pStt, *pEnd;
/*N*/   const SwFrm* pFrm = lcl_GetBoxFrm( rSttBox );
/*N*/   pStt = pFrm ? pFrm->GetUpper() : 0;
/*N*/   pEnd = ( 0 != (pFrm = lcl_GetBoxFrm( rEndBox ))) ? pFrm->GetUpper() : 0;
/*N*/   if( !pStt || !pEnd )
/*?*/       return ;                        // no valid selection
/*N*/
/*N*/   GetTblSel( pStt, pEnd, rBoxes );
/*N*/
/*N*/   const SwTable* pTbl = pStt->FindTabFrm()->GetTable();
/*N*/
/*N*/   // filter die Kopfzeilen-Boxen heraus:
/*N*/   if( pTbl->IsHeadlineRepeat() )
/*N*/       do {    // middle-check loop
/*N*/           const SwTableLine* pHeadLine = pTbl->GetTabLines()[0];
/*N*/           const SwTableLine* pLine = rSttBox.GetUpper();
/*N*/           while( pLine->GetUpper() )
/*?*/               pLine = pLine->GetUpper()->GetUpper();
/*N*/
/*N*/           if( pLine == pHeadLine )
/*?*/               break;      // Headline mit im Bereich !
/*N*/           // vielleicht ist ja Start und Ende vertauscht
/*N*/           pLine = rEndBox.GetUpper();
/*N*/           while ( pLine->GetUpper() )
/*?*/               pLine = pLine->GetUpper()->GetUpper();
/*N*/           if( pLine == pHeadLine )
/*?*/               break;      // Headline mit im Bereich !
/*N*/
/*N*/           const SwTabFrm *pTable = pStt->FindTabFrm();
/*N*/           const SwTabFrm *pEndTable = pEnd->FindTabFrm();
/*N*/           if( pTable == pEndTable )       // keine gespl. Tabelle
/*N*/               break;
/*N*/
/*N*/           // dann mal die Tabellenkoepfe raus:
/*?*/           for( USHORT n = 0; n < rBoxes.Count(); ++n )
/*?*/           {
/*?*/               while( (pLine = rBoxes[n]->GetUpper())->GetUpper() )
/*?*/                   pLine = pLine->GetUpper()->GetUpper();
/*?*/
/*?*/               if( pLine == pHeadLine )
/*?*/                   rBoxes.Remove( n--, 1 );
/*?*/           }
/*?*/       } while( FALSE );
/*N*/ }

    // sind alle Boxen gueltig, auf die sich die Formel bezieht?
//STRIP001 void SwTableFormula::_HasValidBoxes( const SwTable& rTbl, String& rNewStr,
//STRIP001                  String& rFirstBox, String* pLastBox, void* pPara ) const
//STRIP001 {
//STRIP001  BOOL* pBValid = (BOOL*)pPara;
//STRIP001  if( *pBValid )      // einmal falsch, immer falsch
//STRIP001  {
//STRIP001      SwTableBox* pSttBox, *pEndBox = 0;
//STRIP001      rFirstBox.Erase(0,1);       // Kennung fuer Box loeschen
//STRIP001
//STRIP001      // ein Bereich in dieser Klammer ?
//STRIP001      if( pLastBox )
//STRIP001          rFirstBox.Erase( 0, pLastBox->Len()+1 );
//STRIP001
//STRIP001      switch( eNmType)
//STRIP001      {
//STRIP001      case INTRNL_NAME:
//STRIP001          if( pLastBox )
//STRIP001          {
//STRIP001 //               pEndBox = (SwTableBox*)(long)(*pLastBox);
//STRIP001              pEndBox = (SwTableBox*)pLastBox->ToInt32();
//STRIP001          }
//STRIP001 //           pSttBox = (SwTableBox*)(long)rFirstBox;
//STRIP001          pSttBox = (SwTableBox*)rFirstBox.ToInt32();
//STRIP001          break;
//STRIP001
//STRIP001      case REL_NAME:
//STRIP001          {
//STRIP001              const SwNode* pNd = GetNodeOfFormula();
//STRIP001              const SwTableBox* pBox = !pNd ? 0
//STRIP001                                             : (SwTableBox *)rTbl.GetTblBox(
//STRIP001                                  pNd->FindTableBoxStartNode()->GetIndex() );
//STRIP001              if( pLastBox )
//STRIP001                  pEndBox = (SwTableBox*)lcl_RelToBox( rTbl, pBox, *pLastBox );
//STRIP001              pSttBox = (SwTableBox*)lcl_RelToBox( rTbl, pBox, rFirstBox );
//STRIP001          }
//STRIP001          break;
//STRIP001
//STRIP001      case EXTRNL_NAME:
//STRIP001          if( pLastBox )
//STRIP001              pEndBox = (SwTableBox*)rTbl.GetTblBox( *pLastBox );
//STRIP001          pSttBox = (SwTableBox*)rTbl.GetTblBox( rFirstBox );
//STRIP001          break;
//STRIP001      }
//STRIP001
//STRIP001      // sind das gueltige Pointer ?
//STRIP001      if( ( pLastBox &&
//STRIP001            ( !pEndBox || !rTbl.GetTabSortBoxes().Seek_Entry( pEndBox ) ) ) ||
//STRIP001          ( !pSttBox || !rTbl.GetTabSortBoxes().Seek_Entry( pSttBox ) ) )
//STRIP001              *pBValid = FALSE;
//STRIP001  }
//STRIP001 }

//STRIP001 BOOL SwTableFormula::HasValidBoxes() const
//STRIP001 {
//STRIP001  BOOL bRet = TRUE;
//STRIP001  const SwNode* pNd = GetNodeOfFormula();
//STRIP001  if( pNd && 0 != ( pNd = pNd->FindTableNode() ) )
//STRIP001      ScanString( &SwTableFormula::_HasValidBoxes,
//STRIP001                      ((SwTableNode*)pNd)->GetTable(), &bRet );
//STRIP001  return bRet;
//STRIP001 }


//STRIP001 USHORT SwTableFormula::GetLnPosInTbl( const SwTable& rTbl, const SwTableBox* pBox )
//STRIP001 {
//STRIP001  USHORT nRet = USHRT_MAX;
//STRIP001  if( pBox )
//STRIP001  {
//STRIP001      const SwTableLine* pLn = pBox->GetUpper();
//STRIP001      while( pLn->GetUpper() )
//STRIP001          pLn = pLn->GetUpper()->GetUpper();
//STRIP001      nRet = rTbl.GetTabLines().GetPos( pLn );
//STRIP001  }
//STRIP001  return nRet;
//STRIP001 }

//STRIP001 void SwTableFormula::_SplitMergeBoxNm( const SwTable& rTbl, String& rNewStr,
//STRIP001                  String& rFirstBox, String* pLastBox, void* pPara ) const
//STRIP001 {
//STRIP001  SwTableFmlUpdate& rTblUpd = *(SwTableFmlUpdate*)pPara;
//STRIP001
//STRIP001  rNewStr += rFirstBox.Copy(0,1);     // Kennung fuer Box erhalten
//STRIP001  rFirstBox.Erase(0,1);
//STRIP001
//STRIP001  String sTblNm;
//STRIP001  const SwTable* pTbl = &rTbl;
//STRIP001
//STRIP001  String* pTblNmBox = pLastBox ? pLastBox : &rFirstBox;
//STRIP001
//STRIP001  USHORT nLastBoxLen = pTblNmBox->Len();
//STRIP001  USHORT nTrenner = pTblNmBox->Search( '.' );
//STRIP001  if( STRING_NOTFOUND != nTrenner &&
//STRIP001      // falls im Namen schon die Punkte enthalten sind,
//STRIP001      // treten diese immer paarig auf!!! (A1.1.1 !!)
//STRIP001      (pTblNmBox->GetTokenCount( '.' ) - 1 ) & 1 )
//STRIP001  {
//STRIP001      sTblNm = pTblNmBox->Copy( 0, nTrenner );
//STRIP001      pTblNmBox->Erase( 0, nTrenner + 1);// den Punkt entfernen
//STRIP001      const SwTable* pFnd = FindTable( *rTbl.GetFrmFmt()->GetDoc(), sTblNm );
//STRIP001      if( pFnd )
//STRIP001          pTbl = pFnd;
//STRIP001
//STRIP001      if( TBL_MERGETBL == rTblUpd.eFlags )
//STRIP001      {
//STRIP001          if( pFnd )
//STRIP001          {
//STRIP001              if( pFnd == rTblUpd.DATA.pDelTbl )
//STRIP001              {
//STRIP001                  if( rTblUpd.pTbl != &rTbl )         // es ist nicht die akt.
//STRIP001                      (rNewStr += rTblUpd.pTbl->GetFrmFmt()->GetName() )
//STRIP001                          += '.'; // den neuen Tabellen Namen setzen
//STRIP001                  rTblUpd.bModified = TRUE;
//STRIP001              }
//STRIP001              else if( pFnd != rTblUpd.pTbl ||
//STRIP001                  ( rTblUpd.pTbl != &rTbl && &rTbl != rTblUpd.DATA.pDelTbl))
//STRIP001                  (rNewStr += sTblNm ) += '.';    // den Tabellen Namen behalten
//STRIP001              else
//STRIP001                  rTblUpd.bModified = TRUE;
//STRIP001          }
//STRIP001          else
//STRIP001              (rNewStr += sTblNm ) += '.';    // den Tabellen Namen behalten
//STRIP001
//STRIP001      }
//STRIP001  }
//STRIP001  if( pTblNmBox == pLastBox )
//STRIP001      rFirstBox.Erase( 0, nLastBoxLen + 1 );
//STRIP001
//STRIP001  SwTableBox* pSttBox, *pEndBox = 0;
//STRIP001  switch( eNmType )
//STRIP001  {
//STRIP001  case INTRNL_NAME:
//STRIP001      if( pLastBox )
//STRIP001      {
//STRIP001 //           pEndBox = (SwTableBox*)(long)(*pLastBox);
//STRIP001          pEndBox = (SwTableBox*)pLastBox->ToInt32();
//STRIP001      }
//STRIP001 //       pSttBox = (SwTableBox*)(long)rFirstBox;
//STRIP001      pSttBox = (SwTableBox*)rFirstBox.ToInt32();
//STRIP001      break;
//STRIP001
//STRIP001  case REL_NAME:
//STRIP001      {
//STRIP001          const SwNode* pNd = GetNodeOfFormula();
//STRIP001          const SwTableBox* pBox = pNd ? pTbl->GetTblBox(
//STRIP001                          pNd->FindTableBoxStartNode()->GetIndex() ) : 0;
//STRIP001          if( pLastBox )
//STRIP001              pEndBox = (SwTableBox*)lcl_RelToBox( *pTbl, pBox, *pLastBox );
//STRIP001          pSttBox = (SwTableBox*)lcl_RelToBox( *pTbl, pBox, rFirstBox );
//STRIP001      }
//STRIP001      break;
//STRIP001
//STRIP001  case EXTRNL_NAME:
//STRIP001      if( pLastBox )
//STRIP001          pEndBox = (SwTableBox*)pTbl->GetTblBox( *pLastBox );
//STRIP001      pSttBox = (SwTableBox*)pTbl->GetTblBox( rFirstBox );
//STRIP001      break;
//STRIP001  }
//STRIP001
//STRIP001  if( pLastBox && !pTbl->GetTabSortBoxes().Seek_Entry( pEndBox ))
//STRIP001      pEndBox = 0;
//STRIP001  if( !pTbl->GetTabSortBoxes().Seek_Entry( pSttBox ))
//STRIP001      pSttBox = 0;
//STRIP001
//STRIP001  if( TBL_SPLITTBL == rTblUpd.eFlags )
//STRIP001  {
//STRIP001      // wo liegen die Boxen, in der "alten" oder in der neuen Tabelle?
//STRIP001      BOOL bInNewTbl = FALSE;
//STRIP001      if( pLastBox )
//STRIP001      {
//STRIP001          // das ist die "erste" Box in der Selektion. Die bestimmt ob die
//STRIP001          // Formel in der alten oder neuen Tabelle steht.
//STRIP001          USHORT nEndLnPos = SwTableFormula::GetLnPosInTbl( *pTbl, pEndBox ),
//STRIP001                  nSttLnPos = SwTableFormula::GetLnPosInTbl( *pTbl, pSttBox );
//STRIP001
//STRIP001          if( USHRT_MAX != nSttLnPos && USHRT_MAX != nEndLnPos &&
//STRIP001              rTblUpd.nSplitLine <= nSttLnPos ==
//STRIP001              rTblUpd.nSplitLine <= nEndLnPos )
//STRIP001          {
//STRIP001              // bleiben in der gleichen Tabelle
//STRIP001              bInNewTbl = rTblUpd.nSplitLine <= nEndLnPos &&
//STRIP001                                  pTbl == rTblUpd.pTbl;
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              // das ist aufjedenfall eine ungueltige Formel, also fuers
//STRIP001              // Undo auf Modified setzen
//STRIP001              rTblUpd.bModified = TRUE;
//STRIP001              if( pEndBox )
//STRIP001                  bInNewTbl = USHRT_MAX != nEndLnPos &&
//STRIP001                                  rTblUpd.nSplitLine <= nEndLnPos &&
//STRIP001                                  pTbl == rTblUpd.pTbl;
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          USHORT nSttLnPos = SwTableFormula::GetLnPosInTbl( *pTbl, pSttBox );
//STRIP001          // dann landet das Teil in der neuen Tabelle?
//STRIP001          bInNewTbl = USHRT_MAX != nSttLnPos &&
//STRIP001                          rTblUpd.nSplitLine <= nSttLnPos &&
//STRIP001                          pTbl == rTblUpd.pTbl;
//STRIP001      }
//STRIP001
//STRIP001      // wenn die Formel selbst in der neuen Tabellen landet
//STRIP001      if( rTblUpd.bBehindSplitLine )
//STRIP001      {
//STRIP001          if( !bInNewTbl )
//STRIP001          {
//STRIP001              rTblUpd.bModified = TRUE;
//STRIP001              ( rNewStr += rTblUpd.pTbl->GetFrmFmt()->GetName() ) += '.';
//STRIP001          }
//STRIP001          else if( sTblNm.Len() )
//STRIP001              ( rNewStr += sTblNm ) += '.';
//STRIP001      }
//STRIP001      else if( bInNewTbl )
//STRIP001      {
//STRIP001          rTblUpd.bModified = TRUE;
//STRIP001          ( rNewStr += *rTblUpd.DATA.pNewTblNm ) += '.';
//STRIP001      }
//STRIP001      else if( sTblNm.Len() )
//STRIP001          ( rNewStr += sTblNm ) += '.';
//STRIP001  }
//STRIP001
//STRIP001  if( pLastBox )
//STRIP001      ( rNewStr += String::CreateFromInt32((long)pEndBox )) += ':';
//STRIP001  ( rNewStr += String::CreateFromInt32((long)pSttBox ))
//STRIP001            += rFirstBox.GetChar( rFirstBox.Len() - 1 );
//STRIP001 }

    // erzeuge die externe Formel, beachte aber das die Formel
    // in einer gesplitteten/gemergten Tabelle landet
//STRIP001 void SwTableFormula::ToSplitMergeBoxNm( SwTableFmlUpdate& rTblUpd )
//STRIP001 {
//STRIP001  const SwTable* pTbl;
//STRIP001  const SwNode* pNd = GetNodeOfFormula();
//STRIP001  if( pNd && 0 != ( pNd = pNd->FindTableNode() ))
//STRIP001      pTbl = &((SwTableNode*)pNd)->GetTable();
//STRIP001  else
//STRIP001      pTbl = rTblUpd.pTbl;
//STRIP001
//STRIP001  sFormel = ScanString( &SwTableFormula::_SplitMergeBoxNm, *pTbl, (void*)&rTblUpd );
//STRIP001  eNmType = INTRNL_NAME;
//STRIP001 }


}
