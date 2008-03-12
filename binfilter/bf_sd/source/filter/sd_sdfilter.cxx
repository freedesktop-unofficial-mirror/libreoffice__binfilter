/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sd_sdfilter.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 07:30:29 $
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

#ifndef _COM_SUN_STAR_TASK_XSTATUSINDICATORFACTORY_HPP_
#include <com/sun/star/task/XStatusIndicatorFactory.hpp>
#endif

#include <tools/debug.hxx>
#include <osl/file.hxx>
#include <vos/module.hxx>
#include <bf_svtools/pathoptions.hxx>
#include <bf_sfx2/docfile.hxx>
#include <bf_sfx2/progress.hxx>

#include "bf_sd/docshell.hxx"

#include "sdresid.hxx"
#include "pres.hxx"
#include "drawdoc.hxx"
#include "sdfilter.hxx"
#include "glob.hrc"

namespace binfilter {

// --------------
// - Namespaces -
// --------------

using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::task;
using namespace ::com::sun::star::frame;

// ------------
// - SdFilter -
// ------------

SdFilter::SdFilter( SfxMedium& rMedium, SdDrawDocShell& rDocShell, sal_Bool bShowProgress ) :
    mrMedium( rMedium ),
    mrDocShell( rDocShell ),
    mrDocument( *rDocShell.GetDoc() ),
    mxModel( rDocShell.GetModel() ),
    mpProgress( NULL ),
    mbIsDraw( rDocShell.GetDocumentType() == DOCUMENT_TYPE_DRAW ),
    mbShowProgress( bShowProgress )
{
}

// -----------------------------------------------------------------------------

SdFilter::~SdFilter()
{
    delete mpProgress;
}

// -----------------------------------------------------------------------------

::rtl::OUString SdFilter::ImplGetFullLibraryName( const ::rtl::OUString& rLibraryName ) const
{
    String aTemp( ::rtl::OUString::createFromAscii( SVLIBRARY( "?" ) ) );
    xub_StrLen nIndex = aTemp.Search( (sal_Unicode)'?' );
    aTemp.Replace( nIndex, 1, rLibraryName );
    ::rtl::OUString aLibraryName( aTemp );
    return aLibraryName;
}

// -----------------------------------------------------------------------------

::vos::OModule* SdFilter::OpenLibrary( const ::rtl::OUString& rLibraryName ) const
{
    ::rtl::OUString aDest;
    ::rtl::OUString aNormalizedPath;
    ::vos::OModule* pRet;

    if ( ::osl::FileBase::getFileURLFromSystemPath( SvtPathOptions().GetFilterPath(), aDest ) != ::osl::FileBase::E_None )
        aDest = SvtPathOptions().GetFilterPath();
    aDest += ::rtl::OUString( sal_Unicode( '/' ) );
    aDest += ::rtl::OUString( ImplGetFullLibraryName( rLibraryName ) );
    ::osl::FileBase::getSystemPathFromFileURL( aDest, aNormalizedPath );

    if( !( pRet = new ::vos::OModule( aNormalizedPath ) )->isLoaded() )
        delete pRet, pRet = NULL;

    return pRet;
}

// -----------------------------------------------------------------------------

void SdFilter::CreateStatusIndicator()
{
    try
    {
        if (mxModel.is())
        {
            Reference< XController > xController( mxModel->getCurrentController());
            if( xController.is())
            {
                Reference< XFrame > xFrame( xController->getFrame());
                if( xFrame.is())
                {
                    Reference< XStatusIndicatorFactory > xFactory( xFrame, UNO_QUERY );
                    if( xFactory.is())
                    {
                        mxStatusIndicator = xFactory->createStatusIndicator();
                    }
                }
            }
        }
    }
    catch( Exception& )
    {
    }
}

// -----------------------------------------------------------------------------

void SdFilter::CreateProgress()
{
    mpProgress = new SfxProgress( &mrDocShell, String( SdResId( STR_LOAD_DOC ) ), 100 );
    mpProgress->SetState( 0, 100 );
}

// -----------------------------------------------------------------------------

sal_Bool SdFilter::Import()
{
    DBG_ERROR( "Not implemented" );
    return sal_False;
}

// -----------------------------------------------------------------------------

sal_Bool SdFilter::Export()
{
    DBG_ERROR( "Not implemented" );
    return sal_False;
}
}
