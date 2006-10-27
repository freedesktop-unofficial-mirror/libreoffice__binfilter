/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_cellatr.cxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 22:14:25 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/


#pragma hdrstop

#include <float.h>

#ifndef _CELLATR_HXX
#include <cellatr.hxx>
#endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
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
