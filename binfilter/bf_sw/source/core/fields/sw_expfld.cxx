/*************************************************************************
 *
 *  $RCSfile: sw_expfld.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 15:18:39 $
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

#ifndef _UNOTOOLS_COLLATORWRAPPER_HXX
#include <unotools/collatorwrapper.hxx>
#endif
#ifndef _UNOTOOLS_CHARCLASS_HXX
#include <unotools/charclass.hxx>
#endif
#ifndef _UNO_LINGU_HXX
#include <bf_svx/unolingu.hxx>
#endif
#ifndef _SVX_PAGEITEM_HXX
#include <bf_svx/pageitem.hxx>
#endif
#ifndef _SVX_LANGITEM_HXX
#include <bf_svx/langitem.hxx>
#endif
#ifndef _SVX_FONTITEM_HXX
#include <bf_svx/fontitem.hxx>
#endif
#ifndef _COM_SUN_STAR_TEXT_SETVARIABLETYPE_HPP_
#include <com/sun/star/text/SetVariableType.hpp>
#endif

#ifndef _UNOFIELD_HXX
#include <unofield.hxx>
#endif
#ifndef _FMTFLD_HXX
#include <fmtfld.hxx>
#endif
#ifndef _TXTFLD_HXX
#include <txtfld.hxx>
#endif
#ifndef _FMTANCHR_HXX
#include <fmtanchr.hxx>
#endif
#ifndef _TXTFTN_HXX
#include <txtftn.hxx>
#endif
#ifndef _FRMFMT_HXX
#include <frmfmt.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _LAYFRM_HXX
#include <layfrm.hxx>
#endif
#ifndef _PAGEFRM_HXX
#include <pagefrm.hxx>
#endif
#ifndef _CNTFRM_HXX
#include <cntfrm.hxx>
#endif
#ifndef _ROOTFRM_HXX
#include <rootfrm.hxx>
#endif
#ifndef _TABFRM_HXX
#include <tabfrm.hxx>
#endif
#ifndef _FLYFRM_HXX
#include <flyfrm.hxx>
#endif
#ifndef _FTNFRM_HXX
#include <ftnfrm.hxx>
#endif
#ifndef _EXPFLD_HXX
#include <expfld.hxx>
#endif
#ifndef _USRFLD_HXX
#include <usrfld.hxx>
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>
#endif
#ifndef _CALC_HXX
#include <calc.hxx>
#endif
#ifndef _PAM_HXX
#include <pam.hxx>
#endif
#ifndef _DOCFLD_HXX
#include <docfld.hxx>
#endif
#ifndef _SWCACHE_HXX
#include <swcache.hxx>
#endif
#ifndef _SWTABLE_HXX
#include <swtable.hxx>
#endif
#ifndef _BREAKIT_HXX
#include <breakit.hxx>
#endif
#ifndef _SWSTYLENAMEMAPPER_HXX
#include <SwStyleNameMapper.hxx>
#endif
#ifndef _UNOFLDMID_H
#include <unofldmid.h>
#endif

using namespace ::com::sun::star;
using namespace ::com::sun::star::text;
using namespace ::rtl;

//STRIP001 SV_IMPL_PTRARR( _SwSeqFldList, _SeqFldLstElem* )

//-----------------------------------------------------------------------------
/*N*/ sal_Int16 lcl_SubTypeToAPI(USHORT nSubType)
/*N*/ {
/*N*/       sal_Int16 nRet;
/*N*/       switch(nSubType)
/*N*/       {
/*N*/           case GSE_EXPR   :   nRet = SetVariableType::VAR /*0*/; break;
/*N*/           case GSE_SEQ    :   nRet = SetVariableType::SEQUENCE /*1*/; break;
/*N*/           case GSE_FORMULA:   nRet = SetVariableType::FORMULA /*2*/; break;
/*N*/           case GSE_STRING :   nRet = SetVariableType::STRING /*3*/; break;
/*N*/       }
/*N*/       return nRet;
/*N*/ }
//-----------------------------------------------------------------------------
/*N*/ sal_Int32 lcl_APIToSubType(const uno::Any& rAny)
/*N*/ {
/*N*/       sal_Int16 nVal;
/*N*/       rAny >>= nVal;
/*N*/       sal_Int32 nSet = 0;
/*N*/       switch(nVal)
/*N*/       {
/*N*/           case SetVariableType::VAR:      nSet = GSE_EXPR;  break;
/*N*/           case SetVariableType::SEQUENCE: nSet = GSE_SEQ;  break;
/*?*/           case SetVariableType::FORMULA:  nSet = GSE_FORMULA; break;
/*N*/           case SetVariableType::STRING:   nSet = GSE_STRING;  break;
/*N*/           default:
/*?*/               DBG_ERROR("wrong value")
/*?*/               nSet = -1;
/*N*/       }
/*N*/       return nSet;
/*N*/ }
//-----------------------------------------------------------------------------

/*N*/ void ReplacePoint( String& rTmpName, BOOL bWithCommandType )
/*N*/ {
/*N*/     // replace first and last (if bWithCommandType: last two) dot Ersten und letzten Punkt ersetzen, da in Tabellennamen Punkte erlaubt sind
/*N*/     // since table names may contain dots
/*N*/
/*N*/   xub_StrLen nLen = rTmpName.Len();
/*N*/   sal_Unicode *pStr = rTmpName.GetBufferAccess(), *pBackStr = pStr + nLen;
/*N*/
/*N*/     long nBackCount = bWithCommandType ? 2 : 1;
/*N*/     for( xub_StrLen i = nLen; i; --i, pBackStr-- )
/*N*/       if( '.' == *pBackStr )
/*N*/       {
/*?*/           *pBackStr = DB_DELIM;
/*?*/             if(!--nBackCount)
/*?*/                 break;
/*N*/       }
/*N*/   for( i = 0; i < nLen; ++i, ++pStr )
/*N*/       if( '.' == *pStr )
/*N*/       {
/*?*/           *pStr = DB_DELIM;
/*?*/           break;
/*N*/       }
/*N*/ }

/*N*/ SwTxtNode* GetFirstTxtNode( const SwDoc& rDoc, SwPosition& rPos,
/*N*/                           const SwCntntFrm *pCFrm, Point &rPt )
/*N*/ {
/*N*/   SwTxtNode* pTxtNode;
/*N*/   if ( !pCFrm )
/*N*/   {
/*?*/       rPos.nNode = *rDoc.GetNodes().GetEndOfContent().StartOfSectionNode();
/*?*/       SwCntntNode* pCNd;
/*?*/       while( 0 != (pCNd = rDoc.GetNodes().GoNext( &rPos.nNode ) ) &&
/*?*/               0 == ( pTxtNode = pCNd->GetTxtNode() ) )
/*?*/                       ;
/*?*/       ASSERT( pTxtNode, "wo ist der 1.TextNode" );
/*?*/       rPos.nContent.Assign( pTxtNode, 0 );
/*N*/   }
/*N*/   else if ( !pCFrm->IsValid() )
/*N*/   {
/*N*/       pTxtNode = (SwTxtNode*)pCFrm->GetNode();
/*N*/       rPos.nNode = *pTxtNode;
/*N*/       rPos.nContent.Assign( pTxtNode, 0 );
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       pCFrm->GetCrsrOfst( &rPos, rPt );
/*N*/       pTxtNode = rPos.nNode.GetNode().GetTxtNode();
/*N*/   }
/*N*/   return pTxtNode;
/*N*/ }

/*N*/ const SwTxtNode* GetBodyTxtNode( const SwDoc& rDoc, SwPosition& rPos,
/*N*/                               const SwFrm& rFrm )
/*N*/ {
/*N*/   const SwLayoutFrm* pLayout = (SwLayoutFrm*)rFrm.GetUpper();
/*N*/   const SwTxtNode* pTxtNode = 0;
/*N*/
/*N*/   while( pLayout )
/*N*/   {
/*N*/       if( pLayout->IsFlyFrm() )
/*N*/       {
/*N*/           // hole das FlyFormat
/*N*/           SwFrmFmt* pFlyFmt = ((SwFlyFrm*)pLayout)->GetFmt();
/*N*/           ASSERT( pFlyFmt, "kein FlyFormat gefunden, wo steht das Feld" );
/*N*/
/*N*/           const SwFmtAnchor &rAnchor = pFlyFmt->GetAnchor();
/*N*/
/*N*/           if( FLY_AT_FLY == rAnchor.GetAnchorId() )
/*N*/           {
/*N*/               // und der Fly muss irgendwo angehaengt sein, also
/*N*/               // den befragen
/*?*/               pLayout = (SwLayoutFrm*)((SwFlyFrm*)pLayout)->GetAnchor();
/*?*/               continue;
/*N*/           }
/*N*/           else if( FLY_AT_CNTNT == rAnchor.GetAnchorId() ||
/*N*/                    FLY_AUTO_CNTNT == rAnchor.GetAnchorId() ||
/*N*/                    FLY_IN_CNTNT == rAnchor.GetAnchorId() )
/*N*/           {
/*N*/               ASSERT( rAnchor.GetCntntAnchor(), "keine gueltige Position" );
/*N*/               rPos = *rAnchor.GetCntntAnchor();
/*N*/               pTxtNode = rPos.nNode.GetNode().GetTxtNode();
/*N*/               if( FLY_AT_CNTNT == rAnchor.GetAnchorId() )
/*?*/               {DBG_ASSERT(0, "STRIP");} //STRIP001    ((SwTxtNode*)pTxtNode)->MakeStartIndex( &rPos.nContent );
/*N*/ // oder doch besser das Ende vom (Anker-)TextNode nehmen ??
/*N*/ //                    ((SwTxtNode*)pTxtNode)->MakeEndIndex( &rPos.nContent );
/*N*/
/*N*/               // noch nicht abbrechen, kann ja auch noch im
/*N*/               // Header/Footer/Footnote/Fly stehen !!
/*N*/               pLayout = ((SwFlyFrm*)pLayout)->GetAnchor()
/*N*/                           ? ((SwFlyFrm*)pLayout)->GetAnchor()->GetUpper() : 0;
/*N*/               continue;
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               pLayout->FindPageFrm()->GetCntntPosition(
/*N*/                                               pLayout->Frm().Pos(), rPos );
/*N*/               pTxtNode = rPos.nNode.GetNode().GetTxtNode();
/*N*/           }
/*N*/       }
/*N*/       else if( pLayout->IsFtnFrm() )
/*N*/       {
/*?*/           // hole den Node vom Anker
/*?*/           const SwTxtFtn* pFtn = ((SwFtnFrm*)pLayout)->GetAttr();
/*?*/           pTxtNode = &pFtn->GetTxtNode();
/*?*/           rPos.nNode = *pTxtNode;
/*?*/           rPos.nContent = *pFtn->GetStart();
/*N*/       }
/*N*/       else if( pLayout->IsHeaderFrm() || pLayout->IsFooterFrm() )
/*N*/       {
/*N*/           const SwCntntFrm* pCntFrm;
/*N*/           const SwPageFrm* pPgFrm = pLayout->FindPageFrm();
/*N*/           if( pLayout->IsHeaderFrm() )
/*N*/           {
/*N*/               const SwTabFrm *pTab;
/*N*/               if( 0 != ( pCntFrm = pPgFrm->FindFirstBodyCntnt()) &&
/*N*/                   0 != (pTab = pCntFrm->FindTabFrm()) && pTab->IsFollow() &&
/*N*/                   pTab->GetTable()->IsHeadlineRepeat() &&
/*N*/                   ((SwLayoutFrm*)pTab->Lower())->IsAnLower( pCntFrm ))
/*N*/               {
/*N*/                   // take the next line
/*N*/                   const SwLayoutFrm* pRow = (SwLayoutFrm*)pTab->Lower();
/*N*/                   pRow = (SwLayoutFrm*)pRow->GetNext();
/*N*/                   pCntFrm = pRow->ContainsCntnt();
/*N*/               }
/*N*/           }
/*N*/           else
/*?*/               pCntFrm = pPgFrm->FindLastBodyCntnt();
/*N*/
/*N*/           if( pCntFrm )
/*N*/           {
/*N*/               pTxtNode = pCntFrm->GetNode()->GetTxtNode();
/*N*/               rPos.nNode = *pTxtNode;
/*N*/               ((SwTxtNode*)pTxtNode)->MakeEndIndex( &rPos.nContent );
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               Point aPt( pLayout->Frm().Pos() );
/*N*/               aPt.Y()++;      // aus dem Header raus
/*N*/               pCntFrm = pPgFrm->GetCntntPos( aPt, FALSE, TRUE, FALSE );
/*N*/               pTxtNode = GetFirstTxtNode( rDoc, rPos, pCntFrm, aPt );
/*N*/           }
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           pLayout = pLayout->GetUpper();
/*N*/           continue;
/*N*/       }
/*N*/       break;      // gefunden und beende die Schleife
/*N*/   }
/*N*/   return pTxtNode;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: SwSetExpFieldType by JP
 --------------------------------------------------------------------*/

/*N*/ SwGetExpFieldType::SwGetExpFieldType(SwDoc* pDoc)
/*N*/   : SwValueFieldType( pDoc, RES_GETEXPFLD )
/*N*/ {
/*N*/ }

/*N*/ SwFieldType* SwGetExpFieldType::Copy() const
/*N*/ {
DBG_ASSERT(0, "STRIP"); return NULL;//STRIP001 //STRIP001   return new SwGetExpFieldType(GetDoc());
/*N*/ }

/*N*/ void SwGetExpFieldType::Modify( SfxPoolItem*, SfxPoolItem* pNew )
/*N*/ {
/*N*/   if( pNew && RES_DOCPOS_UPDATE == pNew->Which() )
/*N*/       SwModify::Modify( 0, pNew );
/*N*/   // sonst nichts weiter expandieren
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: SwGetExpField by JP
 --------------------------------------------------------------------*/

/*N*/ SwGetExpField::SwGetExpField(SwGetExpFieldType* pTyp, const String& rFormel,
/*N*/                           USHORT nSub, ULONG nFmt)
/*N*/   : SwFormulaField( pTyp, nFmt, 0.0 ),
/*N*/   nSubType(nSub),
/*N*/   bIsInBodyTxt( TRUE )
/*N*/ {
/*N*/   SetFormula( rFormel );
/*N*/ }

/*N*/ String SwGetExpField::Expand() const
/*N*/ {
/*N*/   if(nSubType & SUB_CMD)
/*N*/       return GetFormula();
/*N*/   else
/*N*/       return sExpand;
/*N*/ }

/*N*/ String SwGetExpField::GetCntnt(BOOL bName) const
/*N*/ {
/*N*/   if ( bName )
/*N*/   {
/*?*/       String aStr( SwFieldType::GetTypeStr( GSE_FORMULA & nSubType
/*?*/                                               ? TYP_FORMELFLD
/*?*/                                               : TYP_GETFLD ) );
/*?*/       aStr += ' ';
/*?*/       aStr += GetFormula();
/*?*/       return aStr;
/*N*/   }
/*N*/   return Expand();
/*N*/ }

/*N*/ SwField* SwGetExpField::Copy() const
/*N*/ {
/*N*/   SwGetExpField *pTmp = new SwGetExpField((SwGetExpFieldType*)GetTyp(),
/*N*/                                           GetFormula(), nSubType, GetFormat());
/*N*/   pTmp->SetLanguage(GetLanguage());
/*N*/   pTmp->SwValueField::SetValue(GetValue());
/*N*/   pTmp->sExpand       = sExpand;
/*N*/   pTmp->bIsInBodyTxt  = bIsInBodyTxt;
/*N*/     pTmp->SetAutomaticLanguage(IsAutomaticLanguage());
/*N*/
/*N*/   return pTmp;
/*N*/ }

//STRIP001 void SwGetExpField::ChangeExpansion( const SwFrm& rFrm, const SwTxtFld& rFld )
//STRIP001 {
//STRIP001  if( bIsInBodyTxt )      // nur Felder in Footer, Header, FootNote, Flys
//STRIP001      return;
//STRIP001
//STRIP001  ASSERT( !rFrm.IsInDocBody(), "Flag ist nicht richtig, Frame steht im DocBody" );
//STRIP001
//STRIP001  // bestimme mal das Dokument (oder geht es noch einfacher?)
//STRIP001  const SwTxtNode* pTxtNode = &rFld.GetTxtNode();
//STRIP001  SwDoc& rDoc = *(SwDoc*)pTxtNode->GetDoc();
//STRIP001
//STRIP001  // einen Index fuers bestimmen vom TextNode anlegen
//STRIP001  SwPosition aPos( SwNodeIndex( rDoc.GetNodes() ) );
//STRIP001  pTxtNode = GetBodyTxtNode( rDoc, aPos, rFrm );
//STRIP001
//STRIP001  // Wenn kein Layout vorhanden, kommt es in Kopf und Fusszeilen dazu
//STRIP001  // das ChnageExpansion uebers Layout-Formatieren aufgerufen wird
//STRIP001  // aber kein TxtNode vorhanden ist
//STRIP001  //
//STRIP001  if(!pTxtNode)
//STRIP001      return;
//STRIP001
//STRIP001  _SetGetExpFld aEndFld( aPos.nNode, &rFld, &aPos.nContent );
//STRIP001  if(GetSubType() & GSE_STRING)
//STRIP001  {
//STRIP001      SwHash** ppHashTbl;
//STRIP001      USHORT nSize;
//STRIP001      rDoc.FldsToExpand( ppHashTbl, nSize, aEndFld );
//STRIP001      LookString( ppHashTbl, nSize, GetFormula(), sExpand );
//STRIP001      ::DeleteHashTable( ppHashTbl, nSize );      // HashTabelle loeschen
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      // fuelle den Calculator mit den Werten
//STRIP001      SwCalc aCalc( rDoc );
//STRIP001      rDoc.FldsToCalc( aCalc, aEndFld );
//STRIP001
//STRIP001      // Wert berechnen
//STRIP001      SetValue(aCalc.Calculate(GetFormula()).GetDouble());
//STRIP001
//STRIP001      // Auswertung nach Format
//STRIP001      sExpand = ((SwValueFieldType*)GetTyp())->ExpandValue(
//STRIP001                              GetValue(), GetFormat(), GetLanguage());
//STRIP001  }
//STRIP001 }

//STRIP001 String SwGetExpField::GetPar2() const
//STRIP001 {
//STRIP001  return GetFormula();
//STRIP001 }

//STRIP001 void SwGetExpField::SetPar2(const String& rStr)
//STRIP001 {
//STRIP001  SetFormula(rStr);
//STRIP001 }

/*N*/ USHORT SwGetExpField::GetSubType() const
/*N*/ {
/*N*/   return nSubType;
/*N*/ }

/*N*/ void SwGetExpField::SetSubType(USHORT nType)
/*N*/ {
/*N*/   nSubType = nType;
/*N*/ }

/*N*/ void SwGetExpField::SetLanguage(USHORT nLng)
/*N*/ {
/*N*/   if (nSubType & SUB_CMD)
/*N*/       SwField::SetLanguage(nLng);
/*N*/   else
/*N*/       SwValueField::SetLanguage(nLng);
/*N*/ }

/*-----------------07.03.98 16:08-------------------

--------------------------------------------------*/
/*N*/ BOOL SwGetExpField::QueryValue( uno::Any& rAny, BYTE nMId ) const
/*N*/ {
/*N*/     nMId &= ~CONVERT_TWIPS;
/*N*/   switch( nMId )
/*N*/   {
/*N*/   case FIELD_PROP_DOUBLE:
/*N*/       rAny <<= GetValue();
/*N*/       break;
/*N*/   case FIELD_PROP_FORMAT:
/*N*/       rAny <<= (sal_Int32)GetFormat();
/*N*/       break;
/*N*/   case FIELD_PROP_USHORT1:
/*?*/        rAny <<= (sal_Int16)nSubType;
/*?*/       break;
/*N*/   case FIELD_PROP_PAR1:
/*N*/       rAny <<= OUString( GetFormula() );
/*N*/       break;
/*N*/   case FIELD_PROP_SUBTYPE:
/*N*/       {
/*N*/           sal_Int16 nRet = lcl_SubTypeToAPI(GetSubType() & 0xff);
/*N*/           rAny <<= nRet;
/*N*/       }
/*N*/       break;
/*N*/   case FIELD_PROP_BOOL2:
/*N*/       {
/*N*/           BOOL bTmp = 0 != (nSubType & SUB_CMD);
/*N*/           rAny.setValue(&bTmp, ::getBooleanCppuType());
/*N*/       }
/*N*/       break;
/*N*/   case FIELD_PROP_PAR4:
/*?*/       rAny <<= rtl::OUString(GetExpStr());
/*?*/       break;
/*?*/   default:
/*?*/         return SwField::QueryValue(rAny, nMId);
/*N*/   }
/*N*/   return TRUE;
/*N*/ }
/*-----------------07.03.98 16:08-------------------

--------------------------------------------------*/
//STRIP001 BOOL SwGetExpField::PutValue( const uno::Any& rAny, BYTE nMId )
//STRIP001 {
//STRIP001     nMId &= ~CONVERT_TWIPS;
//STRIP001  sal_Int32 nTmp;
//STRIP001  String sTmp;
//STRIP001  switch( nMId )
//STRIP001  {
//STRIP001  case FIELD_PROP_DOUBLE:
//STRIP001      SwValueField::SetValue(*(double*) rAny.getValue());
//STRIP001      break;
//STRIP001  case FIELD_PROP_FORMAT:
//STRIP001      rAny >>= nTmp;
//STRIP001      SetFormat(nTmp);
//STRIP001      break;
//STRIP001  case FIELD_PROP_USHORT1:
//STRIP001       rAny >>= nTmp;
//STRIP001       nSubType = nTmp;
//STRIP001      break;
//STRIP001  case FIELD_PROP_PAR1:
//STRIP001      SetFormula( ::GetString( rAny, sTmp ));
//STRIP001      break;
//STRIP001  case FIELD_PROP_SUBTYPE:
//STRIP001      nTmp = lcl_APIToSubType(rAny);
//STRIP001      if( nTmp >=0 )
//STRIP001          SetSubType( (GetSubType() & 0xff00) | nTmp);
//STRIP001      break;
//STRIP001  case FIELD_PROP_BOOL2:
//STRIP001      if(*(sal_Bool*) rAny.getValue())
//STRIP001          nSubType |= SUB_CMD;
//STRIP001      else
//STRIP001          nSubType &= (~SUB_CMD);
//STRIP001      break;
//STRIP001  case FIELD_PROP_PAR4:
//STRIP001      ChgExpStr(::GetString( rAny, sTmp ));
//STRIP001      break;
//STRIP001  default:
//STRIP001         return SwField::PutValue(rAny, nMId);
//STRIP001  }
//STRIP001  return TRUE;
//STRIP001 }

/*-----------------JP: 17.06.93 -------------------
 Set-Expression-Type
 --------------------------------------------------*/

/*N*/ SwSetExpFieldType::SwSetExpFieldType( SwDoc* pDoc, const String& rName, USHORT nTyp )
/*N*/   : SwValueFieldType( pDoc, RES_SETEXPFLD ),
/*N*/   sName( rName ),
/*N*/   nType(nTyp),
/*N*/   cDelim( '.' ), nLevel( UCHAR_MAX ),
/*N*/   bDeleted( FALSE ),
/*N*/   pOutlChgNd( 0 )
/*N*/ {
/*N*/   if( ( GSE_SEQ | GSE_STRING ) & nType )
/*N*/       EnableFormat(FALSE);    // Numberformatter nicht einsetzen
/*N*/ }

/*N*/ SwFieldType* SwSetExpFieldType::Copy() const
/*N*/ {
/*N*/   SwSetExpFieldType* pNew = new SwSetExpFieldType(GetDoc(), sName, nType);
/*N*/   pNew->bDeleted = bDeleted;
/*N*/   pNew->cDelim = cDelim;
/*N*/   pNew->nLevel = nLevel;
/*N*/
/*N*/   return pNew;
/*N*/ }

/*N*/ const String& SwSetExpFieldType::GetName() const
/*N*/ {
/*N*/   return sName;
/*N*/ }

//STRIP001 void SwSetExpFieldType::Modify( SfxPoolItem*, SfxPoolItem* )
//STRIP001 {
//STRIP001  return;     // nicht weiter expandieren
//STRIP001 }

//STRIP001 void SwSetExpFieldType::SetSeqFormat(ULONG nFmt)
//STRIP001 {
//STRIP001  SwClientIter aIter(*this);
//STRIP001  for( SwFmtFld* pFld = (SwFmtFld*)aIter.First( TYPE(SwFmtFld) );
//STRIP001          pFld; pFld = (SwFmtFld*)aIter.Next() )
//STRIP001      pFld->GetFld()->ChangeFormat( nFmt );
//STRIP001 }

//STRIP001 ULONG SwSetExpFieldType::GetSeqFormat()
//STRIP001 {
//STRIP001  if( !GetDepends() )
//STRIP001      return SVX_NUM_ARABIC;
//STRIP001
//STRIP001  SwField *pFld = ((SwFmtFld*)GetDepends())->GetFld();
//STRIP001  return pFld->GetFormat();
//STRIP001 }

/*N*/ USHORT SwSetExpFieldType::SetSeqRefNo( SwSetExpField& rFld )
/*N*/ {
/*N*/   if( !GetDepends() || !(GSE_SEQ & nType) )
/*?*/       return USHRT_MAX;
/*N*/
/*N*/ extern void InsertSort( SvUShorts& rArr, USHORT nIdx, USHORT* pInsPos = 0 );
/*N*/   SvUShorts aArr( 64 );
/*N*/
/*N*/   USHORT n;
/*N*/
/*N*/   // dann testmal, ob die Nummer schon vergeben ist oder ob eine neue
/*N*/   // bestimmt werden muss.
/*N*/   SwClientIter aIter( *this );
/*N*/   const SwTxtNode* pNd;
/*N*/   for( SwFmtFld* pF = (SwFmtFld*)aIter.First( TYPE( SwFmtFld )); pF;
/*N*/           pF = (SwFmtFld*)aIter.Next() )
/*N*/       if( pF->GetFld() != &rFld && pF->GetTxtFld() &&
/*N*/           0 != ( pNd = pF->GetTxtFld()->GetpTxtNode() ) &&
/*N*/           pNd->GetNodes().IsDocNodes() )
/*N*/           InsertSort( aArr, ((SwSetExpField*)pF->GetFld())->GetSeqNumber() );
/*N*/
/*N*/
/*N*/   // teste erstmal ob die Nummer schon vorhanden ist:
/*N*/   USHORT nNum = rFld.GetSeqNumber();
/*N*/   if( USHRT_MAX != nNum )
/*N*/   {
/*N*/       for( n = 0; n < aArr.Count(); ++n )
/*N*/           if( aArr[ n ] > nNum )
/*?*/               return nNum;            // nicht vorhanden -> also benutzen
/*N*/           else if( aArr[ n ] == nNum )
/*N*/               break;                  // schon vorhanden -> neue erzeugen
/*N*/
/*N*/       if( n == aArr.Count() )
/*N*/           return nNum;            // nicht vorhanden -> also benutzen
/*N*/   }
/*N*/
/*N*/   // alle Nummern entsprechend geflag, also bestimme die richtige Nummer
/*N*/   for( n = 0; n < aArr.Count(); ++n )
/*N*/       if( n != aArr[ n ] )
/*?*/           break;
/*N*/
/*N*/   rFld.SetSeqNumber( n );
/*N*/   return n;
/*N*/ }

//STRIP001 USHORT SwSetExpFieldType::GetSeqFldList( SwSeqFldList& rList )
//STRIP001 {
//STRIP001  if( rList.Count() )
//STRIP001      rList.Remove( 0, rList.Count() );
//STRIP001
//STRIP001  SwClientIter aIter( *this );
//STRIP001  const SwTxtNode* pNd;
//STRIP001  for( SwFmtFld* pF = (SwFmtFld*)aIter.First( TYPE( SwFmtFld )); pF;
//STRIP001          pF = (SwFmtFld*)aIter.Next() )
//STRIP001      if( pF->GetTxtFld() &&
//STRIP001          0 != ( pNd = pF->GetTxtFld()->GetpTxtNode() ) &&
//STRIP001          pNd->GetNodes().IsDocNodes() )
//STRIP001      {
//STRIP001          _SeqFldLstElem* pNew = new _SeqFldLstElem( pNd->GetExpandTxt( 0,
//STRIP001                              (*pF->GetTxtFld()->GetStart()) + 1, FALSE ),
//STRIP001                          ((SwSetExpField*)pF->GetFld())->GetSeqNumber() );
//STRIP001          rList.InsertSort( pNew );
//STRIP001      }
//STRIP001
//STRIP001  return rList.Count();
//STRIP001 }


//STRIP001 void SwSetExpFieldType::SetChapter( SwSetExpField& rFld, const SwNode& rNd )
//STRIP001 {
//STRIP001  const SwTxtNode* pTxtNd = rNd.FindOutlineNodeOfLevel( nLevel );
//STRIP001  if( pTxtNd )
//STRIP001  {
//STRIP001      ASSERT( pTxtNd && pTxtNd->GetOutlineNum(),
//STRIP001              "kein Outline TextNode" );
//STRIP001
//STRIP001      SwNodeNum aNum( *pTxtNd->GetOutlineNum() );
//STRIP001      if( nLevel < aNum.GetLevel() )
//STRIP001          aNum.SetLevel( nLevel );
//STRIP001
//STRIP001      // nur die Nummer besorgen, ohne Pre-/Post-fixstrings
//STRIP001      String sNumber( GetDoc()->GetOutlineNumRule()->MakeNumString(
//STRIP001                                              aNum, FALSE ));
//STRIP001      if( sNumber.Len() )
//STRIP001          rFld.ChgExpStr(  ( sNumber += cDelim ) += rFld.GetExpStr() );
//STRIP001  }
//STRIP001 }

/* -----------------24.03.99 09:44-------------------
 *
 * --------------------------------------------------*/
/*N*/ BOOL SwSetExpFieldType::QueryValue( uno::Any& rAny, BYTE nMId ) const
/*N*/ {
/*N*/     nMId &= ~CONVERT_TWIPS;
/*N*/   switch( nMId )
/*N*/   {
/*N*/   case FIELD_PROP_SUBTYPE:
/*N*/       {
/*N*/           sal_Int16 nRet = lcl_SubTypeToAPI(GetType());
/*N*/           rAny <<= nRet;
/*N*/       }
/*N*/       break;
/*N*/   case FIELD_PROP_PAR2:
/*?*/       rAny <<= OUString(GetDelimiter());
/*?*/       break;
/*N*/   case FIELD_PROP_SHORT1:
/*N*/       {
/*N*/           sal_Int8 nRet = nLevel < MAXLEVEL? nLevel : -1;
/*N*/           rAny <<= nRet;
/*N*/       }
/*N*/       break;
/*N*/   default:
/*?*/       DBG_ERROR("illegal property");
/*N*/   }
/*N*/   return TRUE;
/*N*/ }

/*N*/ BOOL SwSetExpFieldType::PutValue( const uno::Any& rAny, BYTE nMId )
/*N*/ {
/*N*/     nMId &= ~CONVERT_TWIPS;
/*N*/   switch( nMId )
/*N*/   {
/*N*/   case FIELD_PROP_SUBTYPE:
/*N*/       {
/*N*/           sal_Int32 nSet = lcl_APIToSubType(rAny);
/*N*/           if(nSet >=0)
/*N*/               SetType(nSet);
/*N*/       }
/*N*/       break;
/*N*/   case FIELD_PROP_PAR2:
/*N*/       {
/*?*/           String sTmp;
/*?*/           if( ::GetString( rAny, sTmp ).Len() )
/*?*/               SetDelimiter( sTmp.GetChar( 0 ));
/*?*/           else
/*?*/               SetDelimiter(' ');
/*?*/       }
/*?*/       break;
/*N*/   case FIELD_PROP_SHORT1:
/*N*/       {
/*N*/           sal_Int8 nLvl;
/*N*/           rAny >>= nLvl;
/*N*/           if(nLvl < 0 || nLvl >= MAXLEVEL)
/*N*/               SetOutlineLvl(UCHAR_MAX);
/*N*/           else
/*?*/               SetOutlineLvl(nLvl);
/*N*/       }
/*N*/       break;
/*N*/   default:
/*?*/       DBG_ERROR("illegal property");
/*N*/   }
/*N*/   return TRUE;
/*N*/ }

//STRIP001 BOOL SwSeqFldList::InsertSort( _SeqFldLstElem* pNew )
//STRIP001 {
//STRIP001  sal_Unicode* p = pNew->sDlgEntry.GetBufferAccess();
//STRIP001  while( *p )
//STRIP001  {
//STRIP001      if( *p < 0x20 )
//STRIP001          *p = 0x20;
//STRIP001      ++p;
//STRIP001  }
//STRIP001
//STRIP001  USHORT nPos;
//STRIP001  BOOL bRet = SeekEntry( *pNew, &nPos );
//STRIP001  if( !bRet )
//STRIP001      C40_INSERT( _SeqFldLstElem, pNew, nPos );
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 BOOL SwSeqFldList::SeekEntry( const _SeqFldLstElem& rNew, USHORT* pP )
//STRIP001 {
//STRIP001  register USHORT nO = Count(), nM, nU = 0;
//STRIP001  if( nO > 0 )
//STRIP001  {
//STRIP001      CollatorWrapper & rCaseColl = ::GetAppCaseCollator(),
//STRIP001                      & rColl = ::GetAppCollator();
//STRIP001      const CharClass& rCC = GetAppCharClass();
//STRIP001
//STRIP001      //#59900# Die Sortierung soll die Nummer korrekt einordnen
//STRIP001      //also "10" nach "9" und nicht "10" nach "1"
//STRIP001      const String& rTmp2 = rNew.sDlgEntry;
//STRIP001      xub_StrLen nFndPos2 = 0;
//STRIP001      String sNum2( rTmp2.GetToken( 0, ' ', nFndPos2 ));
//STRIP001      BOOL bIsNum2IsNumeric = rCC.isAsciiNumeric( sNum2 );
//STRIP001      sal_Int32 nNum2 = bIsNum2IsNumeric ? sNum2.ToInt32() : 0;
//STRIP001
//STRIP001      nO--;
//STRIP001      while( nU <= nO )
//STRIP001      {
//STRIP001          nM = nU + ( nO - nU ) / 2;
//STRIP001
//STRIP001          //#59900# Die Sortierung soll die Nummer korrekt einordnen
//STRIP001          //also "10" nach "9" und nicht "10" nach "1"
//STRIP001          const String& rTmp1 = (*((_SeqFldLstElem**)pData + nM))->sDlgEntry;
//STRIP001          xub_StrLen nFndPos1 = 0;
//STRIP001          String sNum1( rTmp1.GetToken( 0, ' ', nFndPos1 ));
//STRIP001          sal_Int32 nCmp;
//STRIP001
//STRIP001          if( bIsNum2IsNumeric && rCC.isNumeric( sNum1 ) )
//STRIP001          {
//STRIP001              sal_Int32 nNum1 = sNum1.ToInt32();
//STRIP001              nCmp = nNum2 - nNum1;
//STRIP001              if( 0 == nCmp )
//STRIP001                  nCmp = rCaseColl.compareString( rTmp2.Copy( nFndPos2 ),
//STRIP001                                                    rTmp1.Copy( nFndPos1 ));
//STRIP001          }
//STRIP001          else
//STRIP001              nCmp = rColl.compareString( rTmp2, rTmp1 );
//STRIP001
//STRIP001          if( 0 == nCmp )
//STRIP001          {
//STRIP001              if( pP ) *pP = nM;
//STRIP001              return TRUE;
//STRIP001          }
//STRIP001          else if( 0 < nCmp )
//STRIP001              nU = nM + 1;
//STRIP001          else if( nM == 0 )
//STRIP001              break;
//STRIP001          else
//STRIP001              nO = nM - 1;
//STRIP001      }
//STRIP001  }
//STRIP001  if( pP ) *pP = nU;
//STRIP001  return FALSE;
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung: SwSetExpField by JP
 --------------------------------------------------------------------*/

/*N*/ SwSetExpField::SwSetExpField(SwSetExpFieldType* pTyp, const String& rFormel,
/*N*/                                       ULONG nFmt)
/*N*/   : SwFormulaField( pTyp, nFmt, 0.0 ), nSeqNo( USHRT_MAX ),
/*N*/   nSubType(0)
/*N*/ {
/*N*/   SetFormula(rFormel);
/*N*/   // SubType ignorieren !!!
/*N*/   bInput = FALSE;
/*N*/   if( IsSequenceFld() )
/*N*/   {
/*N*/       SwValueField::SetValue(1.0);
/*N*/       if( !rFormel.Len() )
/*N*/       {
/*N*/           String sFormel(rFormel);
/*N*/           sFormel += pTyp->GetName();
/*N*/           sFormel += '+';
/*N*/           sFormel += '1';
/*N*/           SetFormula(sFormel);
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ String SwSetExpField::Expand() const
/*N*/ {
/*N*/   String aStr;
/*N*/   if (nSubType & SUB_CMD)
/*N*/   {   // Der CommandString ist gefragt
/*?*/       aStr = GetTyp()->GetName();
/*?*/       aStr.AppendAscii( RTL_CONSTASCII_STRINGPARAM( " = " ));
/*?*/       aStr += GetFormula();
/*N*/   }
/*N*/   else if(!(nSubType & SUB_INVISIBLE))
/*N*/   {   // Der Wert ist sichtbar
/*N*/       aStr = sExpand;
/*N*/   }
/*N*/   return aStr;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: liefert den Namen oder den Inhalt
 --------------------------------------------------------------------*/

/*N*/ String SwSetExpField::GetCntnt(BOOL bName) const
/*N*/ {
/*N*/   if( bName )
/*N*/   {
/*?*/       USHORT nStrType;
/*?*/
/*?*/       if( IsSequenceFld() )
/*?*/           nStrType = TYP_SEQFLD;
/*?*/       else if( bInput )
/*?*/           nStrType = TYP_SETINPFLD;
/*?*/       else
/*?*/           nStrType = TYP_SETFLD;
/*?*/
/*?*/       String aStr( SwFieldType::GetTypeStr( nStrType ) );
/*?*/       aStr += ' ';
/*?*/       aStr += GetTyp()->GetName();
/*?*/
/*?*/       if( TYP_SEQFLD != nStrType )
/*?*/       {
/*?*/           // Sequence nicht die Formel ausgeben
/*?*/           aStr.AppendAscii( RTL_CONSTASCII_STRINGPARAM( " = " ));
/*?*/           aStr += GetFormula();
/*?*/       }
/*?*/       return aStr;
/*N*/   }
/*N*/   return Expand();
/*N*/ }

/*N*/ SwField* SwSetExpField::Copy() const
/*N*/ {
/*N*/   SwSetExpField *pTmp = new SwSetExpField((SwSetExpFieldType*)GetTyp(),
/*N*/                                           GetFormula(), GetFormat());
/*N*/   pTmp->SwValueField::SetValue(GetValue());
/*N*/   pTmp->sExpand       = sExpand;
/*N*/     pTmp->SetAutomaticLanguage(IsAutomaticLanguage());
/*N*/   pTmp->SetLanguage(GetLanguage());
/*N*/   pTmp->aPText        = aPText;
/*N*/   pTmp->bInput        = bInput;
/*N*/   pTmp->nSeqNo        = nSeqNo;
/*N*/   pTmp->SetSubType(GetSubType());
/*N*/
/*N*/   return pTmp;
/*N*/ }

/*N*/ void SwSetExpField::SetSubType(USHORT nSub)
/*N*/ {
/*N*/   ((SwSetExpFieldType*)GetTyp())->SetType(nSub & 0xff);
/*N*/   nSubType = nSub & 0xff00;
/*N*/
/*N*/   DBG_ASSERT( (nSub & 0xff) != 3, "SubType ist illegal!" );
/*N*/ }

/*N*/ USHORT SwSetExpField::GetSubType() const
/*N*/ {
/*N*/   return ((SwSetExpFieldType*)GetTyp())->GetType() | nSubType;
/*N*/ }

/*N*/ void SwSetExpField::SetValue( const double& rAny )
/*N*/ {
/*N*/   SwValueField::SetValue(rAny);
/*N*/
/*N*/   if( IsSequenceFld() )
/*N*/       sExpand = FormatNumber( (USHORT)GetValue(), GetFormat() );
/*N*/   else
/*N*/       sExpand = ((SwValueFieldType*)GetTyp())->ExpandValue( rAny,
/*N*/                                               GetFormat(), GetLanguage());
/*N*/ }

/*N*/ void SwGetExpField::SetValue( const double& rAny )
/*N*/ {
/*N*/   SwValueField::SetValue(rAny);
/*N*/   sExpand = ((SwValueFieldType*)GetTyp())->ExpandValue( rAny, GetFormat(),
/*N*/                                                           GetLanguage());
/*N*/ }
/* -----------------14.07.99 12:21-------------------
    Description: Find the index of the reference text
    following the current field
 --------------------------------------------------*/
/*N*/ xub_StrLen SwGetExpField::GetReferenceTextPos( const SwFmtFld& rFmt, SwDoc& rDoc)
/*N*/ {
/*N*/   //
/*N*/   const SwTxtFld* pTxtFld = rFmt.GetTxtFld();
/*N*/   const SwTxtNode& rTxtNode = pTxtFld->GetTxtNode();
/*N*/   //
/*N*/   xub_StrLen nRet = *pTxtFld->GetStart() + 1;
/*N*/   String sNodeText = rTxtNode.GetTxt();
/*N*/   sNodeText.Erase(0, nRet);
/*N*/   if(sNodeText.Len())
/*N*/   {
/*N*/       //now check if sNodeText starts with a non-alphanumeric character plus a blank
/*N*/       USHORT nSrcpt = pBreakIt->GetRealScriptOfText( sNodeText, 0 );
/*N*/
/*N*/       static USHORT nIds[] =
/*N*/       {
/*N*/           RES_CHRATR_LANGUAGE, RES_CHRATR_LANGUAGE,
/*N*/           RES_CHRATR_FONT, RES_CHRATR_FONT,
/*N*/           RES_CHRATR_CJK_LANGUAGE, RES_CHRATR_CJK_LANGUAGE,
/*N*/           RES_CHRATR_CJK_FONT, RES_CHRATR_CJK_FONT,
/*N*/           RES_CHRATR_CTL_LANGUAGE, RES_CHRATR_CTL_LANGUAGE,
/*N*/           RES_CHRATR_CTL_FONT, RES_CHRATR_CTL_FONT,
/*N*/           0, 0
/*N*/       };
/*N*/       SwAttrSet aSet(rDoc.GetAttrPool(), nIds);
/*N*/       rTxtNode.GetAttr(aSet, nRet, nRet+1);
/*N*/
/*N*/       if( RTL_TEXTENCODING_SYMBOL != ((SvxFontItem&)aSet.Get(
/*N*/               GetWhichOfScript( RES_CHRATR_FONT, nSrcpt )) ).GetCharSet() )
/*N*/       {
/*N*/           LanguageType eLang = ((SvxLanguageItem&)aSet.Get(
/*N*/               GetWhichOfScript( RES_CHRATR_LANGUAGE, nSrcpt )) ).GetLanguage();
/*N*/           CharClass aCC( SvxCreateLocale( eLang ));
/*N*/           sal_Unicode c0 = sNodeText.GetChar(0);
/*N*/           BOOL bIsAlphaNum = aCC.isAlphaNumeric( sNodeText, 0 );
/*N*/           if( !bIsAlphaNum ||
/*N*/               (c0 == ' ' || c0 == '\t'))
/*N*/           {
/*N*/               nRet++;
/*N*/               if( sNodeText.Len() > 1 &&
/*N*/                   (sNodeText.GetChar(1) == ' ' ||
/*N*/                    sNodeText.GetChar(1) == '\t'))
/*N*/                   nRet++;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   return nRet;
/*N*/ }


/*--------------------------------------------------------------------
    Beschreibung: Parameter setzen
 --------------------------------------------------------------------*/

/*N*/ const String& SwSetExpField::GetPar1() const
/*N*/ {
/*N*/   return ((SwSetExpFieldType*)GetTyp())->GetName();
/*N*/ }

//STRIP001 String SwSetExpField::GetPar2() const
//STRIP001 {
//STRIP001  USHORT nType = ((SwSetExpFieldType*)GetTyp())->GetType();
//STRIP001
//STRIP001  if (nType & GSE_STRING)
//STRIP001      return GetFormula();
//STRIP001  return GetExpandedFormula();
//STRIP001 }

//STRIP001 void SwSetExpField::SetPar2(const String& rStr)
//STRIP001 {
//STRIP001  USHORT nType = ((SwSetExpFieldType*)GetTyp())->GetType();
//STRIP001
//STRIP001  if( !(nType & GSE_SEQ) || rStr.Len() )
//STRIP001  {
//STRIP001      if (nType & GSE_STRING)
//STRIP001          SetFormula(rStr);
//STRIP001      else
//STRIP001          SetExpandedFormula(rStr);
//STRIP001  }
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung: Eingabefeld Type
 ---------------------------------------------------------------------*/

/*N*/ SwInputFieldType::SwInputFieldType( SwDoc* pD )
/*N*/   : SwFieldType( RES_INPUTFLD ), pDoc( pD )
/*N*/ {
/*N*/ }

/*N*/ SwFieldType* SwInputFieldType::Copy() const
/*N*/ {
DBG_ASSERT(0, "STRIP"); return NULL;//STRIP001 //STRIP001   SwInputFieldType* pType = new SwInputFieldType( pDoc );
//STRIP001  return pType;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: Eingabefeld
 --------------------------------------------------------------------*/

/*N*/ SwInputField::SwInputField(SwInputFieldType* pType, const String& rContent,
/*N*/                          const String& rPrompt, USHORT nSub, ULONG nFmt) :
/*N*/   SwField(pType, nFmt), nSubType(nSub), aContent(rContent), aPText(rPrompt)
/*N*/ {
/*N*/ }

/*N*/ String SwInputField::GetCntnt(BOOL bName) const
/*N*/ {
/*N*/   if ( bName )
/*N*/   {
/*?*/       String aStr(SwField::GetCntnt(bName));
/*?*/       if ((nSubType & 0x00ff) == INP_USR)
/*?*/       {
/*?*/           aStr += GetTyp()->GetName();
/*?*/           aStr += ' ';
/*?*/           aStr += aContent;
/*?*/       }
/*?*/       return aStr;
/*N*/   }
/*N*/   return Expand();
/*N*/ }

/*N*/ SwField* SwInputField::Copy() const
/*N*/ {
/*N*/   SwInputField* pFld = new SwInputField((SwInputFieldType*)GetTyp(), aContent,
/*N*/                                         aPText, GetSubType(), GetFormat());
/*N*/     pFld->SetAutomaticLanguage(IsAutomaticLanguage());
/*N*/   return pFld;
/*N*/ }

/*N*/ String SwInputField::Expand() const
/*N*/ {
/*N*/   String sRet;
/*N*/   if((nSubType & 0x00ff) == INP_TXT)
/*N*/       sRet = aContent;
/*N*/
/*N*/   else if( (nSubType & 0x00ff) == INP_USR )
/*N*/   {
/*?*/       SwUserFieldType* pUserTyp = (SwUserFieldType*)
/*?*/                           ((SwInputFieldType*)GetTyp())->GetDoc()->
/*?*/                           GetFldType( RES_USERFLD, aContent );
/*?*/       if( pUserTyp )
/*?*/           sRet = pUserTyp->GetContent();
/*N*/   }
/*N*/   return sRet;
/*N*/ }

/*-----------------06.03.98 11:12-------------------

--------------------------------------------------*/
/*N*/ BOOL SwInputField::QueryValue( uno::Any& rAny, BYTE nMId ) const
/*N*/ {
/*N*/     nMId &= ~CONVERT_TWIPS;
/*N*/   switch( nMId )
/*N*/   {
/*N*/   case FIELD_PROP_PAR1:
/*?*/        rAny <<= OUString( aContent );
/*?*/       break;
/*N*/   case FIELD_PROP_PAR2:
/*N*/       rAny <<= OUString( aPText );
/*N*/       break;
/*N*/   default:
/*?*/       DBG_ERROR("illegal property");
/*N*/   }
/*N*/   return TRUE;
/*N*/ }
/*-----------------06.03.98 11:12-------------------

--------------------------------------------------*/
//STRIP001 BOOL SwInputField::PutValue( const uno::Any& rAny, BYTE nMId )
//STRIP001 {
//STRIP001     nMId &= ~CONVERT_TWIPS;
//STRIP001  switch( nMId )
//STRIP001  {
//STRIP001  case FIELD_PROP_PAR1:
//STRIP001       ::GetString( rAny, aContent );
//STRIP001      break;
//STRIP001  case FIELD_PROP_PAR2:
//STRIP001      ::GetString( rAny, aPText );
//STRIP001      break;
//STRIP001  default:
//STRIP001      DBG_ERROR("illegal property");
//STRIP001  }
//STRIP001  return TRUE;
//STRIP001 }
/*--------------------------------------------------------------------
    Beschreibung: Bedingung setzen
 --------------------------------------------------------------------*/

//STRIP001 void SwInputField::SetPar1(const String& rStr)
//STRIP001 {
//STRIP001  aContent = rStr;
//STRIP001 }

/*N*/ const String& SwInputField::GetPar1() const
/*N*/ {
/*N*/   return aContent;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: True/False Text
 --------------------------------------------------------------------*/

//STRIP001 void SwInputField::SetPar2(const String& rStr)
//STRIP001 {
//STRIP001  aPText = rStr;
//STRIP001 }

/*N*/ String SwInputField::GetPar2() const
/*N*/ {
/*N*/   return aPText;
/*N*/ }

/*N*/ USHORT SwInputField::GetSubType() const
/*N*/ {
/*N*/   return nSubType;
/*N*/ }

//STRIP001 void SwInputField::SetSubType(USHORT nSub)
//STRIP001 {
//STRIP001  nSubType = nSub;
//STRIP001 }
/*-----------------05.03.98 17:22-------------------

--------------------------------------------------*/
/*N*/ BOOL SwSetExpField::QueryValue( uno::Any& rAny, BYTE nMId ) const
/*N*/ {
/*N*/     nMId &= ~CONVERT_TWIPS;
/*N*/   switch( nMId )
/*N*/   {
/*N*/   case FIELD_PROP_BOOL2:
/*N*/       {
/*N*/           sal_Bool bVal = 0 == (nSubType & SUB_INVISIBLE);
/*N*/           rAny.setValue(&bVal, ::getBooleanCppuType());
/*N*/       }
/*N*/       break;
/*N*/   case FIELD_PROP_FORMAT:
/*N*/       rAny <<= (sal_Int32)GetFormat();
/*N*/       break;
/*N*/   case FIELD_PROP_USHORT2:
/*N*/       rAny <<= (sal_Int16)GetFormat();
/*N*/       break;
/*N*/   case FIELD_PROP_USHORT1:
/*N*/       rAny <<= (sal_Int16)nSeqNo;
/*N*/       break;
/*N*/   case FIELD_PROP_PAR1:
/*N*/       rAny <<= OUString ( SwStyleNameMapper::GetProgName(GetPar1(), GET_POOLID_TXTCOLL ) );
/*N*/       break;
/*N*/   case FIELD_PROP_PAR2:
/*N*/       {
/*N*/           //I18N - if the formula contains only "TypeName+1"
/*N*/           //and it's one of the initially created sequence fields
/*N*/           //then the localized names has to be replaced by a programmatic name
/*N*/           OUString sFormula = SwXFieldMaster::LocalizeFormula(*this, GetFormula(), TRUE);
/*N*/           rAny <<= OUString( sFormula );
/*N*/       }
/*N*/       break;
/*N*/   case FIELD_PROP_DOUBLE:
/*N*/       rAny <<= (double)GetValue();
/*N*/       break;
/*N*/   case FIELD_PROP_SUBTYPE:
/*N*/       {
/*N*/           sal_Int16 nRet = 0;
/*N*/               nRet = lcl_SubTypeToAPI(GetSubType() & 0xff);
/*N*/           rAny <<= nRet;
/*N*/       }
/*N*/       break;
/*N*/   case FIELD_PROP_PAR3:
/*?*/       rAny <<= OUString( aPText );
/*?*/       break;
/*?*/   case FIELD_PROP_BOOL3:
/*?*/       {
/*?*/           BOOL bTmp = 0 != (nSubType & SUB_CMD);
/*?*/           rAny.setValue(&bTmp, ::getBooleanCppuType());
/*?*/       }
/*?*/       break;
/*N*/   case FIELD_PROP_BOOL1:
/*N*/       {
/*N*/           BOOL bTmp = GetInputFlag();
/*N*/           rAny.setValue(&bTmp, ::getBooleanCppuType());
/*N*/       }
/*N*/       break;
/*N*/   case FIELD_PROP_PAR4:
/*?*/       rAny <<= rtl::OUString(GetExpStr());
/*?*/       break;
/*?*/   default:
/*?*/         return SwField::QueryValue(rAny, nMId);
/*N*/   }
/*N*/   return TRUE;
/*N*/ }
/*-----------------05.03.98 17:22-------------------

--------------------------------------------------*/
/*N*/ BOOL SwSetExpField::PutValue( const uno::Any& rAny, BYTE nMId )
/*N*/ {
/*N*/     nMId &= ~CONVERT_TWIPS;
/*N*/   sal_Int32 nTmp32;
/*N*/   sal_Int16 nTmp16;
/*N*/   String sTmp;
/*N*/   switch( nMId )
/*N*/   {
/*N*/   case FIELD_PROP_BOOL2:
/*?*/       if(*(sal_Bool*)rAny.getValue())
/*?*/           nSubType &= ~SUB_INVISIBLE;
/*?*/       else
/*?*/           nSubType |= SUB_INVISIBLE;
/*?*/       break;
/*N*/   case FIELD_PROP_FORMAT:
/*N*/       rAny >>= nTmp32;
/*N*/       SetFormat(nTmp32);
/*N*/       break;
/*N*/   case FIELD_PROP_USHORT2:
/*?*/       {
/*?*/           rAny >>= nTmp16;
/*?*/           if(nTmp16 <= SVX_NUMBER_NONE )
/*?*/               SetFormat(nTmp16);
/*?*/           else
/*?*/               //exception(wrong_value)
/*?*/               ;
/*?*/       }
/*?*/       break;
/*?*/   case FIELD_PROP_USHORT1:
/*?*/       rAny >>= nTmp16;
/*?*/       nSeqNo = nTmp16;
/*?*/       break;
/*?*/   case FIELD_PROP_PAR1:
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001 SetPar1( SwStyleNameMapper::GetUIName(
//STRIP001 /*?*/                            ::GetString( rAny, sTmp ), GET_POOLID_TXTCOLL ) );
/*?*/       break;
/*N*/   case FIELD_PROP_PAR2:
/*N*/       {
/*N*/           OUString uTmp;
/*N*/           rAny >>= uTmp;
/*N*/           //I18N - if the formula contains only "TypeName+1"
/*N*/           //and it's one of the initially created sequence fields
/*N*/           //then the localized names has to be replaced by a programmatic name
/*N*/           OUString sFormula = SwXFieldMaster::LocalizeFormula(*this, uTmp, FALSE);
/*N*/           SetFormula( sFormula );
/*N*/       }
/*N*/       break;
/*N*/   case FIELD_PROP_DOUBLE:
/*N*/       {
/*N*/           double fVal;
/*N*/           rAny >>= fVal;
/*N*/           SetValue(fVal);
/*N*/       }
/*N*/       break;
/*N*/   case FIELD_PROP_SUBTYPE:
/*N*/       nTmp32 = lcl_APIToSubType(rAny);
/*N*/       if(nTmp32 >= 0)
/*N*/           SetSubType((GetSubType() & 0xff00) | nTmp32);
/*N*/       break;
/*N*/   case FIELD_PROP_PAR3:
/*?*/       ::GetString( rAny, aPText );
/*?*/       break;
/*N*/   case FIELD_PROP_BOOL3:
/*N*/       if(*(sal_Bool*) rAny.getValue())
/*?*/           nSubType |= SUB_CMD;
/*N*/       else
/*N*/           nSubType &= (~SUB_CMD);
/*N*/       break;
/*N*/   case FIELD_PROP_BOOL1:
/*?*/       SetInputFlag(*(sal_Bool*) rAny.getValue());
/*?*/       break;
/*N*/   case FIELD_PROP_PAR4:
/*N*/       ChgExpStr( ::GetString( rAny, sTmp ));
/*N*/       break;
/*N*/   default:
/*?*/         return SwField::PutValue(rAny, nMId);
/*N*/   }
/*N*/   return TRUE;
/*N*/ }



