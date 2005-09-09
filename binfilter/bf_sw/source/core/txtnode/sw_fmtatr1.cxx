/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_fmtatr1.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 02:39:08 $
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

#include <hintids.hxx>
#ifndef _ERRHDL_HXX //autogen
#include <errhdl.hxx>
#endif
#ifndef _FMTHBSH_HXX //autogen
#include <fmthbsh.hxx>
#endif
namespace binfilter {


/*************************************************************************
|*
|*    class SwFmtHardBlank
|*
|*    Beschreibung      Dokument 1.20
|*    Ersterstellung    JP 23.11.90
|*    Letzte Aenderung  JP 20.02.91
|*
*************************************************************************/

/*N*/ SwFmtHardBlank::SwFmtHardBlank( sal_Unicode cCh, BOOL bCheck )
/*N*/   : SfxPoolItem( RES_TXTATR_HARDBLANK ),
/*N*/   cChar( cCh )
/*N*/ {
/*N*/   ASSERT( !bCheck || (' ' != cCh && '-' != cCh),
/*N*/           "Invalid character for the HardBlank attribute - "
/*N*/           "must be a normal unicode character" );
/*N*/ }

//STRIP001 int SwFmtHardBlank::operator==( const SfxPoolItem& rAttr ) const
//STRIP001 {
//STRIP001  ASSERT( SfxPoolItem::operator==( rAttr ), "keine gleichen Attribute" );
//STRIP001  return cChar == ((SwFmtHardBlank&)rAttr).GetChar();
//STRIP001 }

//STRIP001 SfxPoolItem* SwFmtHardBlank::Clone( SfxItemPool* ) const
//STRIP001 {
//STRIP001  return new SwFmtHardBlank( *this );
//STRIP001 }

/*************************************************************************
|*
|*    class SwFmtSoftHyph
|*
|*    Beschreibung      Dokument 1.20
|*    Ersterstellung    JP 23.11.90
|*    Letzte Aenderung  JP 20.02.91
|*
*************************************************************************/

/*N*/ SwFmtSoftHyph::SwFmtSoftHyph()
/*N*/   : SfxPoolItem( RES_TXTATR_SOFTHYPH )
/*N*/ {
/*N*/ }

//STRIP001 int SwFmtSoftHyph::operator==( const SfxPoolItem& rAttr ) const
//STRIP001 {
//STRIP001  ASSERT( SfxPoolItem::operator==( rAttr ), "keine gleichen Attribute" );
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 SfxPoolItem* SwFmtSoftHyph::Clone( SfxItemPool* ) const
//STRIP001 {
//STRIP001  return new SwFmtSoftHyph( *this );
//STRIP001 }


}
