/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */


#ifdef _MSC_VER
#pragma hdrstop
#endif

#include <float.h>

#include <cellatr.hxx>

#include <horiornt.hxx>

#include <doc.hxx>
#include <swtable.hxx>

#include <osl/diagnose.h>

#include <node.hxx>
#include <hints.hxx>
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
/*N*/   OSL_ENSURE( SfxPoolItem::operator==( rAttr ), "keine gleichen Attribute" );
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
/*?*/   OSL_ENSURE( SfxPoolItem::operator==( rAttr ), "keine gleichen Attribute" );
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
/*N*/   OSL_ENSURE( SfxPoolItem::operator==( rAttr ), "keine gleichen Attribute" );
/*N*/   return nValue == ((SwTblBoxValue&)rAttr).nValue;
/*N*/ }


/*N*/ SfxPoolItem* SwTblBoxValue::Clone( SfxItemPool* ) const
/*N*/ {
/*N*/   return new SwTblBoxValue( nValue );
/*N*/ }




}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
