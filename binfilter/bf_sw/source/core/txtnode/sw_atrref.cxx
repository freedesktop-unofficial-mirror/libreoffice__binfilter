/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_atrref.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 12:41:47 $
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


#ifdef _MSC_VER
#pragma hdrstop
#endif

#ifndef _TXTRFMRK_HXX //autogen
#include <txtrfmrk.hxx>
#endif
#ifndef _FMTRFMRK_HXX //autogen
#include <fmtrfmrk.hxx>
#endif
namespace binfilter {


/****************************************************************************
 *
 *  class SwFmtRefMark
 *
 ****************************************************************************/

/*N*/ SwFmtRefMark::~SwFmtRefMark( )
/*N*/ {
/*N*/ }

/*N*/ SwFmtRefMark::SwFmtRefMark( const XubString& rName )
/*N*/   : SfxPoolItem( RES_TXTATR_REFMARK ),
/*N*/   aRefName( rName ),
/*N*/   pTxtAttr( 0 )
/*N*/ {
/*N*/ }

/*N*/ SwFmtRefMark::SwFmtRefMark( const SwFmtRefMark& rAttr )
/*N*/   : SfxPoolItem( RES_TXTATR_REFMARK ),
/*N*/   aRefName( rAttr.aRefName ),
/*N*/   pTxtAttr( 0 )
/*N*/ {
/*N*/ }

int SwFmtRefMark::operator==( const SfxPoolItem& rAttr ) const
{
    {DBG_BF_ASSERT(0, "STRIP");} return 0;//STRIP001    ASSERT( SfxPoolItem::operator==( rAttr ), "keine gleichen Attribute" );
}

/*N*/ SfxPoolItem* SwFmtRefMark::Clone( SfxItemPool* ) const
/*N*/ {
/*N*/   return new SwFmtRefMark( *this );
/*N*/ }

/*************************************************************************
 *                      class SwTxtRefMark
 *************************************************************************/

// Attribut fuer Inhalts-/Positions-Referenzen im Text

/*N*/ SwTxtRefMark::SwTxtRefMark( const SwFmtRefMark& rAttr,
/*N*/                   xub_StrLen nStart, xub_StrLen* pEnde )
/*N*/   : SwTxtAttrEnd( rAttr, nStart, nStart ),
/*N*/   pEnd( 0 ),
/*N*/   pMyTxtNd( 0 )
/*N*/ {
/*N*/   ((SwFmtRefMark&)rAttr).pTxtAttr = this;
/*N*/   if( pEnde )
/*N*/   {
/*N*/       nEnd = *pEnde;
/*N*/       pEnd = &nEnd;
/*N*/   }
/*N*/   SetDontMergeAttr( TRUE );
/*N*/   SetDontMoveAttr( TRUE );
/*N*/   SetOverlapAllowedAttr( TRUE );
/*N*/ }

/*N*/ xub_StrLen* SwTxtRefMark::GetEnd()
/*N*/ {
/*N*/   return pEnd;
/*N*/ }

}
