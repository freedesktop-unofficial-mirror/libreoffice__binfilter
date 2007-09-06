/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_wrtswtbl.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 13:02:01 $
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

#ifdef PCH
#endif

#ifdef _MSC_VER
#pragma hdrstop
#endif

#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif


#ifndef _WRTSWTBL_HXX
#include <wrtswtbl.hxx>
#endif
#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif
#ifndef _SWTABLE_HXX
#include <swtable.hxx>
#endif
#ifndef _FRMFMT_HXX
#include <frmfmt.hxx>
#endif
#ifndef _FMTFSIZE_HXX
#include <fmtfsize.hxx>
#endif

#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif

namespace binfilter {



//-----------------------------------------------------------------------


//-----------------------------------------------------------------------




//-----------------------------------------------------------------------

/*N*/ SwWriteTableCol::SwWriteTableCol( USHORT nPosition )
/*N*/   : nPos(nPosition),
/*N*/   bLeftBorder(TRUE), bRightBorder(TRUE),
/*N*/   nWidthOpt( 0 ), bRelWidthOpt( FALSE ),
/*N*/   bOutWidth( TRUE )
/*N*/ {
/*N*/ }

//-----------------------------------------------------------------------

/*N*/ long SwWriteTable::GetBoxWidth( const SwTableBox *pBox )
/*N*/ {
/*N*/   const SwFrmFmt *pFmt = pBox->GetFrmFmt();
/*N*/   const SwFmtFrmSize& aFrmSize=
/*N*/       (const SwFmtFrmSize&)pFmt->GetAttr( RES_FRM_SIZE );
/*N*/
/*N*/   return aFrmSize.GetSize().Width();
/*N*/ }


























}
