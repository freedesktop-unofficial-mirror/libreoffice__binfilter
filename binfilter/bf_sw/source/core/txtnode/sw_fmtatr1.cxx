/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_fmtatr1.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 12:42:16 $
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




}
