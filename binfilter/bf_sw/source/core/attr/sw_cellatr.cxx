/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: sw_cellatr.cxx,v $
 * $Revision: 1.12 $
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/


#ifdef _MSC_VER
#pragma hdrstop
#endif

#include <float.h>

#ifndef _CELLATR_HXX
#include <cellatr.hxx>
#endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _SWTABLE_HXX
#include <swtable.hxx>
#endif

#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif

#ifndef _NODE_HXX
#include <node.hxx>
#endif
#ifndef _HINTS_HXX
#include <hints.hxx>
#endif
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
/*?*/   ASSERT( SfxPoolItem::operator==( rAttr ), "keine gleichen Attribute" );
 /*?*/  return GetFormula() == ((SwTblBoxFormula&)rAttr).GetFormula() &&
 /*?*/          pDefinedIn == ((SwTblBoxFormula&)rAttr).pDefinedIn;
/*N*/ }


/*N*/ SfxPoolItem* SwTblBoxFormula::Clone( SfxItemPool* ) const
/*N*/ {
/*?*/  // auf externe Darstellung umschalten!!
    SwTblBoxFormula* pNew = new SwTblBoxFormula( GetFormula() );
    pNew->SwTableFormula::operator=( *this );
    return pNew;
/*N*/ }



    // suche den Node, in dem die Formel steht:
    //  TextFeld    -> TextNode,
    //  BoxAttribut -> BoxStartNode
    // !!! MUSS VON JEDER ABLEITUNG UEBERLADEN WERDEN !!!
/*N*/ const SwNode* SwTblBoxFormula::GetNodeOfFormula() const
/*N*/ {
/*?*/       const SwNode* pRet = 0;
            if( pDefinedIn )
            {
                SwClient* pBox = SwClientIter( *pDefinedIn ).First( TYPE( SwTableBox ));
                if( pBox )
                    pRet = ((SwTableBox*)pBox)->GetSttNd();
            }
            return pRet;
/*N*/ }


SwTableBox* SwTblBoxFormula::GetTableBox()
{
    SwTableBox* pBox = 0;
    if( pDefinedIn )
        pBox = (SwTableBox*)SwClientIter( *pDefinedIn ).
                            First( TYPE( SwTableBox ));
    return pBox;
}


void SwTblBoxFormula::ChangeState( const SfxPoolItem* pItem )
{
    if( !pDefinedIn )
        return ;

    SwTableFmlUpdate* pUpdtFld;
    if( !pItem || RES_TABLEFML_UPDATE != pItem->Which() )
    {
        // setze bei allen das Value-Flag zurueck
        ChgValid( FALSE );
        return ;
    }

    pUpdtFld = (SwTableFmlUpdate*)pItem;

    // bestimme die Tabelle, in der das Attribut steht
    const SwTableNode* pTblNd;
    const SwNode* pNd = GetNodeOfFormula();
    if( pNd && &pNd->GetNodes() == &pNd->GetDoc()->GetNodes() &&
        0 != ( pTblNd = pNd->FindTableNode() ))
    {
        switch( pUpdtFld->eFlags )
        {
        case TBL_CALC:
            // setze das Value-Flag zurueck
            // JP 17.06.96: interne Darstellung auf alle Formeln
            //              (Referenzen auf andere Tabellen!!!)
//          if( VF_CMD & pFld->GetFormat() )
//              pFld->PtrToBoxNm( pUpdtFld->pTbl );
//          else
                ChgValid( FALSE );
            break;
        case TBL_BOXNAME:
            // ist es die gesuchte Tabelle ??
            if( &pTblNd->GetTable() == pUpdtFld->pTbl )
                // zur externen Darstellung
                PtrToBoxNm( pUpdtFld->pTbl );
            break;
        case TBL_BOXPTR:
            // zur internen Darstellung
            // JP 17.06.96: interne Darstellung auf alle Formeln
            //              (Referenzen auf andere Tabellen!!!)
            BoxNmToPtr( &pTblNd->GetTable() );
            break;
        case TBL_RELBOXNAME:
            // ist es die gesuchte Tabelle ??
            if( &pTblNd->GetTable() == pUpdtFld->pTbl )
                // zur relativen Darstellung
                ToRelBoxNm( pUpdtFld->pTbl );
            break;

        case TBL_SPLITTBL:
            if( &pTblNd->GetTable() == pUpdtFld->pTbl )
            {
                USHORT nLnPos = SwTableFormula::GetLnPosInTbl(
                                        pTblNd->GetTable(), GetTableBox() );
                pUpdtFld->bBehindSplitLine = USHRT_MAX != nLnPos &&
                                            pUpdtFld->nSplitLine <= nLnPos;
            }
            else
                pUpdtFld->bBehindSplitLine = FALSE;
            // kein break
        case TBL_MERGETBL:
            if( pUpdtFld->pHistory )
            {
                // fuer die History brauche ich aber die unveraenderte Formel
                SwTblBoxFormula aCopy( *this );
                pUpdtFld->bModified = FALSE;
                ToSplitMergeBoxNm( *pUpdtFld );

                if( pUpdtFld->bModified )
                {
                    // und dann in der externen Darstellung
                    aCopy.PtrToBoxNm( &pTblNd->GetTable() );
                }
            }
            else
                ToSplitMergeBoxNm( *pUpdtFld );
            break;
        }
    }
}

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
