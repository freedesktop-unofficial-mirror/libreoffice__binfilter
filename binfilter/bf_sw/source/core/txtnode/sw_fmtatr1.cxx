/*************************************************************************
 *
 *  $RCSfile: sw_fmtatr1.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 15:38:54 $
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

#include <hintids.hxx>
#ifndef _ERRHDL_HXX //autogen
#include <errhdl.hxx>
#endif
#ifndef _FMTHBSH_HXX //autogen
#include <fmthbsh.hxx>
#endif


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


