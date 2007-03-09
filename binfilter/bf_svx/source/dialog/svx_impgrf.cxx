/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_impgrf.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: obo $ $Date: 2007-03-09 15:38:30 $
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

// include ------------------------------------------------------------------

#include <limits.h>             // USHRT_MAX

#ifndef _SFXDOCFILE_HXX
#include <bf_sfx2/docfile.hxx>
#endif

using namespace ::ucb;
using namespace ::com::sun::star::uno;

#include "dialogs.hrc"
#include "impgrf.hrc"

#define _SVX_IMPGRF_CXX
#include "impgrf.hxx"

#include "dialmgr.hxx"
#include "helpid.hrc"
namespace binfilter {

// defines ---------------------------------------------------------------

#define IMPGRF_INIKEY_ASLINK        "ImportGraphicAsLink"
#define IMPGRF_INIKEY_PREVIEW       "ImportGraphicPreview"
#define IMPGRF_CONFIGNAME           String(DEFINE_CONST_UNICODE("ImportGraphicDialog"))

// -----------------------------------------------------------------------

/*N*/ GraphicFilter* DialogsResMgr::GetGrfFilter_Impl()
/*N*/ {
/*N*/   if( !pGrapicFilter )
/*N*/   {
/*N*/ #ifndef SVX_LIGHT
/*N*/       pGrapicFilter = new GraphicFilter;
/*N*/ #else
/*N*/       pGrapicFilter = new GraphicFilter(sal_False);
/*N*/ #endif
/*N*/       ::binfilter::FillFilter( *pGrapicFilter );
/*N*/   }
/*N*/   return pGrapicFilter;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ GraphicFilter* GetGrfFilter()
/*N*/ {
/*N*/   return (*(DialogsResMgr**)GetAppData(BF_SHL_SVX))->GetGrfFilter_Impl();
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ USHORT FillFilter( GraphicFilter& rFilter )
/*N*/ {
/*N*/   ResMgr* pMgr = DIALOG_MGR();
/*N*/     return rFilter.GetImportFormatCount();
/*N*/ }

// -----------------------------------------------------------------------

}
