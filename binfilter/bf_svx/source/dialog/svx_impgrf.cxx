/*************************************************************************
 *
 *  $RCSfile: svx_impgrf.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 15:24:59 $
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

// include ------------------------------------------------------------------

#include <limits.h>             // USHRT_MAX

// auto strip #ifndef _URLOBJ_HXX
// auto strip #include <tools/urlobj.hxx>
// auto strip #endif
// auto strip #ifndef _BIGINT_HXX
// auto strip #include <tools/bigint.hxx>
// auto strip #endif
// auto strip #ifndef _SFXENUMITEM_HXX
// auto strip #include <svtools/eitem.hxx>
// auto strip #endif
// auto strip #ifndef _SFXSTRITEM_HXX
// auto strip #include <svtools/stritem.hxx>
// auto strip #endif
#ifndef _SFXDOCFILE_HXX
#include <bf_sfx2/docfile.hxx>
#endif
// auto strip #ifndef _SFXDISPATCH_HXX
// auto strip #include <bf_sfx2/dispatch.hxx>
// auto strip #endif
// auto strip #ifndef _SV_MSGBOX_HXX //autogen
// auto strip #include <vcl/msgbox.hxx>
// auto strip #endif
// auto strip #ifndef _SV_WAITOBJ_HXX //autogen
// auto strip #include <vcl/waitobj.hxx>
// auto strip #endif
// auto strip #ifndef INCLUDED_SVTOOLS_PATHOPTIONS_HXX
// auto strip #include <svtools/pathoptions.hxx>
// auto strip #endif
// auto strip #ifndef INCLUDED_SVTOOLS_VIEWOPTIONS_HXX
// auto strip #include <svtools/viewoptions.hxx>
// auto strip #endif
// auto strip #ifndef _UNOTOOLS_LOCALFILEHELPER_HXX
// auto strip #include <unotools/localfilehelper.hxx>
// auto strip #endif
#pragma hdrstop

// auto strip #include <ucbhelper/content.hxx>
// auto strip #include <osl/file.hxx>

// auto strip #ifndef _COM_SUN_STAR_UCB_COMMANDABORTEDEXCEPTION_HPP_
// auto strip #include <com/sun/star/ucb/CommandAbortedException.hpp>
// auto strip #endif

using namespace ::ucb;
using namespace ::com::sun::star::uno;

#include "dialogs.hrc"
#include "impgrf.hrc"

#define _SVX_IMPGRF_CXX
#include "impgrf.hxx"

#include "dialmgr.hxx"
// auto strip #include "svxerr.hxx"
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
/*N*/   const Link aLink;
/*N*/   pGrapicFilter->SetStartFilterHdl( aLink );
/*N*/   pGrapicFilter->SetEndFilterHdl( aLink );
/*N*/   pGrapicFilter->SetUpdatePercentHdl( aLink );
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

#pragma optimize( "", off )

//STRIP001 int LoadGraphic( const String &rPath, const String &rFilterName,
//STRIP001               Graphic& rGraphic, GraphicFilter* pFilter,
//STRIP001               USHORT* pDeterminedFormat )
//STRIP001 {
//STRIP001  if ( !pFilter )
//STRIP001      pFilter = ::GetGrfFilter();
//STRIP001
//STRIP001  const int nFilter = rFilterName.Len() && pFilter->GetImportFormatCount()
//STRIP001                  ? pFilter->GetImportFormatNumber( rFilterName )
//STRIP001                  : GRFILTER_FORMAT_DONTKNOW;
//STRIP001
//STRIP001  SfxMedium* pMed = 0;
//STRIP001
//STRIP001  // dann teste mal auf File-Protokoll:
//STRIP001  SvStream* pStream = NULL;
//STRIP001  INetURLObject aURL( rPath );
//STRIP001
//STRIP001  if ( aURL.HasError() || INET_PROT_NOT_VALID == aURL.GetProtocol() )
//STRIP001  {
//STRIP001      aURL.SetSmartProtocol( INET_PROT_FILE );
//STRIP001      aURL.SetSmartURL( rPath );
//STRIP001  }
//STRIP001  else if ( INET_PROT_FILE != aURL.GetProtocol() )
//STRIP001  {
//STRIP001      // z.Z. nur auf die aktuelle DocShell
//STRIP001      pMed = new SfxMedium( rPath, STREAM_READ, TRUE );
//STRIP001      pMed->SetTransferPriority( SFX_TFPRIO_SYNCHRON );
//STRIP001      pMed->DownLoad();
//STRIP001      pStream = pMed->GetInStream();
//STRIP001  }
//STRIP001  int nRes = GRFILTER_OK;
//STRIP001
//STRIP001  if ( !pStream )
//STRIP001      nRes = pFilter->ImportGraphic( rGraphic, aURL, nFilter, pDeterminedFormat );
//STRIP001  else
//STRIP001      nRes = pFilter->ImportGraphic( rGraphic, rPath, *pStream,
//STRIP001                                     nFilter, pDeterminedFormat );
//STRIP001
//STRIP001 #ifndef PRODUCT
//STRIP001  if( nRes )
//STRIP001  {
//STRIP001      if( pMed )
//STRIP001      {
//STRIP001          DBG_WARNING3( "GrafikFehler [%d] - [%s] URL[%s]",
//STRIP001                          nRes,
//STRIP001                          pMed->GetPhysicalName().GetBuffer(),
//STRIP001                          rPath.GetBuffer() );
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          DBG_WARNING2( "GrafikFehler [%d] - [%s]", nRes, rPath.GetBuffer() );
//STRIP001      }
//STRIP001  }
//STRIP001 #endif
//STRIP001
//STRIP001  if ( pMed )
//STRIP001      delete pMed;
//STRIP001  return nRes;
//STRIP001 }

#pragma optimize( "", on )

}
