/*************************************************************************
 *
 *  $RCSfile: sw_cellatr.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 16:55:31 $
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
// auto strip #ifndef _HINTIDS_HXX
// auto strip #include <hintids.hxx>            // fuer RES_..
// auto strip #endif

#ifndef _CELLATR_HXX
#include <cellatr.hxx>
#endif
// auto strip #ifndef _CALC_HXX
// auto strip #include <calc.hxx>
// auto strip #endif
// auto strip #ifndef _FORMAT_HXX
// auto strip #include <format.hxx>
// auto strip #endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

// auto strip #ifndef _DOC_HXX
// auto strip #include <doc.hxx>
// auto strip #endif
#ifndef _SWTABLE_HXX
#include <swtable.hxx>
#endif

#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif

// auto strip #ifndef _NODE_HXX
// auto strip #include <node.hxx>
// auto strip #endif
// auto strip #ifndef _HINTS_HXX
// auto strip #include <hints.hxx>
// auto strip #endif
// auto strip #ifndef _ROLBCK_HXX
// auto strip #include <rolbck.hxx>
// auto strip #endif
namespace binfilter {



//TYPEINIT1( SwFmt, SwClient ); //rtti fuer SwFmt

/*************************************************************************
|*
*************************************************************************/


/*N*/ SwTblBoxNumFormat::SwTblBoxNumFormat( UINT32 nFormat, BOOL bFlag )
/*N*/   : SfxUInt32Item( RES_BOXATR_FORMAT, nFormat ), bAuto( bFlag )
/*N*/ {
/*N*/ }


/*N*/ int SwTblBoxNumFormat::operator==( const SfxPoolItem& rAttr ) const
/*N*/ {
/*N*/   ASSERT( SfxPoolItem::operator==( rAttr ), "keine gleichen Attribute" );
/*N*/   return GetValue() == ((SwTblBoxNumFormat&)rAttr).GetValue() &&
/*N*/           bAuto == ((SwTblBoxNumFormat&)rAttr).bAuto;
/*N*/ }


/*N*/ SfxPoolItem* SwTblBoxNumFormat::Clone( SfxItemPool* ) const
/*N*/ {
/*N*/   return new SwTblBoxNumFormat( GetValue(), bAuto );
/*N*/ }


/*************************************************************************
|*
*************************************************************************/



/*N*/ SwTblBoxFormula::SwTblBoxFormula( const String& rFormula )
/*N*/   : SfxPoolItem( RES_BOXATR_FORMULA ),
/*N*/   SwTableFormula( rFormula ),
/*N*/   pDefinedIn( 0 )
/*N*/ {
/*N*/ }


/*N*/ int SwTblBoxFormula::operator==( const SfxPoolItem& rAttr ) const
/*N*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001 ASSERT( SfxPoolItem::operator==( rAttr ), "keine gleichen Attribute" );
//STRIP001 /*?*/    return GetFormula() == ((SwTblBoxFormula&)rAttr).GetFormula() &&
//STRIP001 /*?*/            pDefinedIn == ((SwTblBoxFormula&)rAttr).pDefinedIn;
/*N*/ }


/*N*/ SfxPoolItem* SwTblBoxFormula::Clone( SfxItemPool* ) const
/*N*/ {
/*?*/  DBG_BF_ASSERT(0, "STRIP"); return NULL;//STRIP001 // auf externe Darstellung umschalten!!
//STRIP001  SwTblBoxFormula* pNew = new SwTblBoxFormula( GetFormula() );
//STRIP001  pNew->SwTableFormula::operator=( *this );
//STRIP001  return pNew;
/*N*/ }



    // suche den Node, in dem die Formel steht:
    //  TextFeld    -> TextNode,
    //  BoxAttribut -> BoxStartNode
    // !!! MUSS VON JEDER ABLEITUNG UEBERLADEN WERDEN !!!
/*N*/ const SwNode* SwTblBoxFormula::GetNodeOfFormula() const
/*N*/ {
/*?*/ DBG_BF_ASSERT(0, "STRIP"); return NULL;//STRIP001     const SwNode* pRet = 0;
//STRIP001  if( pDefinedIn )
//STRIP001  {
//STRIP001      SwClient* pBox = SwClientIter( *pDefinedIn ).First( TYPE( SwTableBox ));
//STRIP001      if( pBox )
//STRIP001          pRet = ((SwTableBox*)pBox)->GetSttNd();
//STRIP001  }
//STRIP001  return pRet;
/*N*/ }


SwTableBox* SwTblBoxFormula::GetTableBox()
{
    SwTableBox* pBox = 0;
    if( pDefinedIn )
        pBox = (SwTableBox*)SwClientIter( *pDefinedIn ).
                            First( TYPE( SwTableBox ));
    return pBox;
}


//STRIP001 void SwTblBoxFormula::ChangeState( const SfxPoolItem* pItem )
//STRIP001 {
//STRIP001  if( !pDefinedIn )
//STRIP001      return ;
//STRIP001
//STRIP001  SwTableFmlUpdate* pUpdtFld;
//STRIP001  if( !pItem || RES_TABLEFML_UPDATE != pItem->Which() )
//STRIP001  {
//STRIP001      // setze bei allen das Value-Flag zurueck
//STRIP001      ChgValid( FALSE );
//STRIP001      return ;
//STRIP001  }
//STRIP001
//STRIP001  pUpdtFld = (SwTableFmlUpdate*)pItem;
//STRIP001
//STRIP001  // bestimme die Tabelle, in der das Attribut steht
//STRIP001  const SwTableNode* pTblNd;
//STRIP001  const SwNode* pNd = GetNodeOfFormula();
//STRIP001  if( pNd && &pNd->GetNodes() == &pNd->GetDoc()->GetNodes() &&
//STRIP001      0 != ( pTblNd = pNd->FindTableNode() ))
//STRIP001  {
//STRIP001      switch( pUpdtFld->eFlags )
//STRIP001      {
//STRIP001      case TBL_CALC:
//STRIP001          // setze das Value-Flag zurueck
//STRIP001          // JP 17.06.96: interne Darstellung auf alle Formeln
//STRIP001          //              (Referenzen auf andere Tabellen!!!)
//STRIP001 //           if( VF_CMD & pFld->GetFormat() )
//STRIP001 //               pFld->PtrToBoxNm( pUpdtFld->pTbl );
//STRIP001 //           else
//STRIP001              ChgValid( FALSE );
//STRIP001          break;
//STRIP001      case TBL_BOXNAME:
//STRIP001          // ist es die gesuchte Tabelle ??
//STRIP001          if( &pTblNd->GetTable() == pUpdtFld->pTbl )
//STRIP001              // zur externen Darstellung
//STRIP001              PtrToBoxNm( pUpdtFld->pTbl );
//STRIP001          break;
//STRIP001      case TBL_BOXPTR:
//STRIP001          // zur internen Darstellung
//STRIP001          // JP 17.06.96: interne Darstellung auf alle Formeln
//STRIP001          //              (Referenzen auf andere Tabellen!!!)
//STRIP001          BoxNmToPtr( &pTblNd->GetTable() );
//STRIP001          break;
//STRIP001      case TBL_RELBOXNAME:
//STRIP001          // ist es die gesuchte Tabelle ??
//STRIP001          if( &pTblNd->GetTable() == pUpdtFld->pTbl )
//STRIP001              // zur relativen Darstellung
//STRIP001              ToRelBoxNm( pUpdtFld->pTbl );
//STRIP001          break;
//STRIP001
//STRIP001      case TBL_SPLITTBL:
//STRIP001          if( &pTblNd->GetTable() == pUpdtFld->pTbl )
//STRIP001          {
//STRIP001              USHORT nLnPos = SwTableFormula::GetLnPosInTbl(
//STRIP001                                      pTblNd->GetTable(), GetTableBox() );
//STRIP001              pUpdtFld->bBehindSplitLine = USHRT_MAX != nLnPos &&
//STRIP001                                          pUpdtFld->nSplitLine <= nLnPos;
//STRIP001          }
//STRIP001          else
//STRIP001              pUpdtFld->bBehindSplitLine = FALSE;
//STRIP001          // kein break
//STRIP001      case TBL_MERGETBL:
//STRIP001          if( pUpdtFld->pHistory )
//STRIP001          {
//STRIP001              // fuer die History brauche ich aber die unveraenderte Formel
//STRIP001              SwTblBoxFormula aCopy( *this );
//STRIP001              pUpdtFld->bModified = FALSE;
//STRIP001              ToSplitMergeBoxNm( *pUpdtFld );
//STRIP001
//STRIP001              if( pUpdtFld->bModified )
//STRIP001              {
//STRIP001                  // und dann in der externen Darstellung
//STRIP001                  aCopy.PtrToBoxNm( &pTblNd->GetTable() );
//STRIP001                  pUpdtFld->pHistory->Add( &aCopy, &aCopy,
//STRIP001                              pNd->FindTableBoxStartNode()->GetIndex() );
//STRIP001              }
//STRIP001          }
//STRIP001          else
//STRIP001              ToSplitMergeBoxNm( *pUpdtFld );
//STRIP001          break;
//STRIP001      }
//STRIP001  }
//STRIP001 }


//STRIP001 void SwTblBoxFormula::Calc( SwTblCalcPara& rCalcPara, double& rValue )
//STRIP001 {
//STRIP001  if( !rCalcPara.rCalc.IsCalcError() )        // ist schon Fehler gesetzt ?
//STRIP001  {
//STRIP001      // erzeuge aus den BoxNamen die Pointer
//STRIP001      BoxNmToPtr( rCalcPara.pTbl );
//STRIP001      String sFml( MakeFormel( rCalcPara ));
//STRIP001      if( !rCalcPara.rCalc.IsCalcError() )
//STRIP001          rValue = rCalcPara.rCalc.Calculate( sFml ).GetDouble();
//STRIP001      else
//STRIP001          rValue = DBL_MAX;
//STRIP001      ChgValid( !rCalcPara.IsStackOverFlow() );       // der Wert ist wieder gueltig
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
*************************************************************************/


/*N*/ SwTblBoxValue::SwTblBoxValue()
/*N*/   : SfxPoolItem( RES_BOXATR_VALUE ), nValue( 0 )
/*N*/ {
/*N*/ }


/*N*/ SwTblBoxValue::SwTblBoxValue( const double nVal )
/*N*/   : SfxPoolItem( RES_BOXATR_VALUE ), nValue( nVal )
/*N*/ {
/*N*/ }


/*N*/ int SwTblBoxValue::operator==( const SfxPoolItem& rAttr ) const
/*N*/ {
/*N*/   ASSERT( SfxPoolItem::operator==( rAttr ), "keine gleichen Attribute" );
/*N*/   return nValue == ((SwTblBoxValue&)rAttr).nValue;
/*N*/ }


/*N*/ SfxPoolItem* SwTblBoxValue::Clone( SfxItemPool* ) const
/*N*/ {
/*N*/   return new SwTblBoxValue( nValue );
/*N*/ }




}
