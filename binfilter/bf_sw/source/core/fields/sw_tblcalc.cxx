/*************************************************************************
 *
 *  $RCSfile: sw_tblcalc.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 15:18:34 $
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

#ifndef _CNTFRM_HXX
#include <cntfrm.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _PAM_HXX
#include <pam.hxx>      // fuer GetBodyTxtNode
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>
#endif
#ifndef _FMTFLD_HXX //autogen
#include <fmtfld.hxx>
#endif
#ifndef _TXTFLD_HXX //autogen
#include <txtfld.hxx>
#endif
#ifndef _EXPFLD_HXX
#include <expfld.hxx>
#endif
#ifndef _HINTS_HXX
#include <hints.hxx>    // fuer Modify()
#endif
#ifndef _DOCFLD_HXX
#include <docfld.hxx>   // fuer _SetGetExpFld
#endif
#ifndef _UNOFLDMID_H
#include <unofldmid.h>
#endif

using namespace ::com::sun::star;
using namespace ::rtl;


/*N*/ SwTblFieldType::SwTblFieldType(SwDoc* pDocPtr)
/*N*/   : SwValueFieldType( pDocPtr, RES_TABLEFLD )
/*N*/ {}


/*N*/ SwFieldType* SwTblFieldType::Copy() const
/*N*/ {
DBG_ASSERT(0, "STRIP"); return NULL;//STRIP001 //STRIP001   return new SwTblFieldType(GetDoc());
/*N*/ }



/*N*/ void SwTblField::CalcField( SwTblCalcPara& rCalcPara )
/*N*/ {
/*N*/   if( rCalcPara.rCalc.IsCalcError() )     // ist schon Fehler gesetzt ?
/*?*/       return;
/*N*/
/*N*/   // erzeuge aus den BoxNamen die Pointer
/*N*/   BoxNmToPtr( rCalcPara.pTbl );
/*N*/   String sFml( MakeFormel( rCalcPara ));
/*N*/   SetValue( rCalcPara.rCalc.Calculate( sFml ).GetDouble() );
/*N*/   ChgValid( !rCalcPara.IsStackOverFlow() );       // ist der Wert wieder gueltig?
/*N*/ }



/*N*/ SwTblField::SwTblField( SwTblFieldType* pType, const String& rFormel,
/*N*/                       USHORT nType, ULONG nFmt )
/*N*/   : SwValueField( pType, nFmt ), SwTableFormula( rFormel ),
/*N*/   nSubType(nType), sExpand( '0' )
/*N*/ {
/*N*/ }


/*N*/ SwField* SwTblField::Copy() const
/*N*/ {
/*N*/   SwTblField* pTmp = new SwTblField( (SwTblFieldType*)GetTyp(),
/*N*/                                       SwTableFormula::GetFormula(), nSubType, GetFormat() );
/*N*/   pTmp->sExpand     = sExpand;
/*N*/   pTmp->SwValueField::SetValue(GetValue());
/*N*/   pTmp->SwTableFormula::operator=( *this );
/*N*/     pTmp->SetAutomaticLanguage(IsAutomaticLanguage());
/*N*/   return pTmp;
/*N*/ }


/*N*/ String SwTblField::GetCntnt(BOOL bName) const
/*N*/ {
/*N*/   if( bName )
/*N*/   {
/*?*/       String aStr(GetTyp()->GetName());
/*?*/       aStr += ' ';
/*?*/
/*?*/       USHORT nOldSubType = nSubType;
/*?*/       SwTblField* pThis = (SwTblField*)this;
/*?*/       pThis->nSubType |= SUB_CMD;
/*?*/       aStr += Expand();
/*?*/       pThis->nSubType = nOldSubType;
/*?*/
/*?*/       return aStr;
/*N*/   }
/*N*/   return Expand();
/*N*/ }

// suche den TextNode, in dem das Feld steht
/*N*/ const SwNode* SwTblField::GetNodeOfFormula() const
/*N*/ {
/*N*/   if( !GetTyp()->GetDepends() )
/*N*/       return 0;
/*N*/
/*N*/   SwClientIter aIter( *GetTyp() );
/*N*/   SwClient * pLast = aIter.GoStart();
/*N*/   if( pLast )     // konnte zum Anfang gesprungen werden ??
/*N*/       do {
/*N*/           const SwFmtFld* pFmtFld = (SwFmtFld*)pLast;
/*N*/           if( this == pFmtFld->GetFld() )
/*N*/               return (SwTxtNode*)&pFmtFld->GetTxtFld()->GetTxtNode();
/*N*/
/*N*/       } while( 0 != ( pLast = aIter++ ));
/*N*/   return 0;
/*N*/ }


/*N*/ String SwTblField::Expand() const
/*N*/ {
/*N*/   String aStr;
/*N*/   if (nSubType & SUB_CMD)
/*N*/   {
/*N*/       if( EXTRNL_NAME != GetNameType() )
/*N*/       {
/*?*/           const SwNode* pNd = GetNodeOfFormula();
/*?*/           const SwTableNode* pTblNd = pNd ? pNd->FindTableNode() : 0;
/*?*/           if( pTblNd )
/*?*/               ((SwTblField*)this)->PtrToBoxNm( &pTblNd->GetTable() );
/*N*/       }
/*N*/       if( EXTRNL_NAME == GetNameType() )
/*N*/           aStr = SwTableFormula::GetFormula();
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       aStr = sExpand;
/*N*/       if(nSubType & GSE_STRING)
/*N*/       {
/*?*/           // es ist ein String
/*?*/           aStr = sExpand;
/*?*/           aStr.Erase( 0,1 );
/*?*/           aStr.Erase( aStr.Len()-1, 1 );
/*N*/       }
/*N*/   }
/*N*/   return aStr;
/*N*/ }

/*N*/ USHORT SwTblField::GetSubType() const
/*N*/ {
/*N*/   return nSubType;
/*N*/ }

//STRIP001 void SwTblField::SetSubType(USHORT nType)
//STRIP001 {
//STRIP001  nSubType = nType;
//STRIP001 }


/*N*/ void SwTblField::SetValue( const double& rVal )
/*N*/ {
/*N*/   SwValueField::SetValue(rVal);
/*N*/   sExpand = ((SwValueFieldType*)GetTyp())->ExpandValue(rVal, GetFormat(), GetLanguage());
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: Parameter setzen
 --------------------------------------------------------------------*/


/*N*/ String SwTblField::GetPar2() const
/*N*/ {
/*N*/   return SwTableFormula::GetFormula();
/*N*/ }


//STRIP001 void SwTblField::SetPar2(const String& rStr)
//STRIP001 {
//STRIP001  SetFormula( rStr );
//STRIP001 }


/*-----------------04.03.98 10:33-------------------

--------------------------------------------------*/
/*N*/ BOOL SwTblField::QueryValue( uno::Any& rAny, BYTE nMId ) const
/*N*/ {
/*N*/     nMId &= ~CONVERT_TWIPS;
/*N*/   BOOL bRet = TRUE;
/*N*/   switch ( nMId )
/*N*/   {
/*N*/   case FIELD_PROP_PAR2:
/*N*/       {
/*N*/           USHORT nOldSubType = nSubType;
/*N*/           SwTblField* pThis = (SwTblField*)this;
/*N*/           pThis->nSubType |= SUB_CMD;
/*N*/           rAny <<= rtl::OUString( Expand() );
/*N*/           pThis->nSubType = nOldSubType;
/*N*/       }
/*N*/       break;
/*N*/   case FIELD_PROP_BOOL1:
/*N*/       {
/*N*/           BOOL bFormula = 0 != (SUB_CMD & nSubType);
/*N*/           rAny.setValue(&bFormula, ::getBooleanCppuType());
/*N*/       }
/*N*/       break;
/*N*/   case FIELD_PROP_PAR1:
/*?*/       rAny <<= rtl::OUString(GetExpStr());
/*?*/       break;
/*N*/   case FIELD_PROP_FORMAT:
/*N*/         rAny <<= (sal_Int32)GetFormat();
/*N*/       break;
/*N*/   default:
/*?*/         bRet = sal_False;
/*N*/   }
/*N*/     return bRet;
/*N*/ }
/*-----------------04.03.98 10:33-------------------

--------------------------------------------------*/
//STRIP001 BOOL SwTblField::PutValue( const uno::Any& rAny, BYTE nMId )
//STRIP001 {
//STRIP001     nMId &= ~CONVERT_TWIPS;
//STRIP001  BOOL bRet = TRUE;
//STRIP001  String sTmp;
//STRIP001  switch ( nMId )
//STRIP001  {
//STRIP001  case FIELD_PROP_PAR2:
//STRIP001      SetFormula( ::GetString( rAny, sTmp ));
//STRIP001      break;
//STRIP001  case FIELD_PROP_BOOL1:
//STRIP001         if(*(sal_Bool*)rAny.getValue())
//STRIP001             nSubType = GSE_FORMULA|SUB_CMD;
//STRIP001         else
//STRIP001             nSubType = GSE_FORMULA;
//STRIP001      break;
//STRIP001  case FIELD_PROP_PAR1:
//STRIP001         ChgExpStr( ::GetString( rAny, sTmp ));
//STRIP001      break;
//STRIP001     case FIELD_PROP_FORMAT:
//STRIP001         {
//STRIP001             sal_Int32 nTmp;
//STRIP001             rAny >>= nTmp;
//STRIP001             SetFormat(nTmp);
//STRIP001         }
//STRIP001         break;
//STRIP001  default:
//STRIP001         bRet = sal_False;
//STRIP001  }
//STRIP001     return bRet;
//STRIP001 }




