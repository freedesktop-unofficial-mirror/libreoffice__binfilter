/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_forbiddencharacterstable.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: vg $ $Date: 2006-04-06 16:14:06 $
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

#include <forbiddencharacterstable.hxx>

#include <unotools/localedatawrapper.hxx>
#include <unolingu.hxx>

// auto strip #ifndef _COM_SUN_STAR_LANG_XSINGLESERVICEFACTORY_HPP_
// auto strip #include <com/sun/star/lang/XMultiServiceFactory.hpp>
// auto strip #endif
/*STRIP001*/#include <tools/debug.hxx>
namespace binfilter {
/*N*/ SvxForbiddenCharactersTable::SvxForbiddenCharactersTable( ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory > xMSF, USHORT nISize, USHORT nGrow )
/*N*/  : SvxForbiddenCharactersTableImpl( nISize, nGrow )
/*N*/ {
/*N*/   mxMSF = xMSF;
/*N*/ }


/*N*/ SvxForbiddenCharactersTable::~SvxForbiddenCharactersTable()
/*N*/ {
/*N*/   for ( ULONG n = Count(); n; )
/*N*/       delete GetObject( --n );
/*N*/ }



const ::com::sun::star::i18n::ForbiddenCharacters* SvxForbiddenCharactersTable::GetForbiddenCharacters( USHORT nLanguage, BOOL bGetDefault ) const
{
    ForbiddenCharactersInfo* pInf = Get( nLanguage );
    if ( !pInf && bGetDefault && mxMSF.is() )
    {
        const SvxForbiddenCharactersTableImpl *pConstImpl =
            dynamic_cast<const SvxForbiddenCharactersTableImpl*>(this);
        SvxForbiddenCharactersTableImpl* pImpl =
            const_cast<SvxForbiddenCharactersTableImpl*>(pConstImpl);
        pInf = new ForbiddenCharactersInfo;
        pImpl->Insert( nLanguage, pInf );
        pInf->bTemporary = TRUE;
        LocaleDataWrapper aWrapper( mxMSF, SvxCreateLocale( nLanguage ) );
        pInf->aForbiddenChars = aWrapper.getForbiddenCharacters();
    }
    return pInf ? &pInf->aForbiddenChars : NULL;
}



/*N*/ void SvxForbiddenCharactersTable::SetForbiddenCharacters( USHORT nLanguage, const ::com::sun::star::i18n::ForbiddenCharacters& rForbiddenChars )
/*N*/ {
/*N*/   ForbiddenCharactersInfo* pInf = Get( nLanguage );
/*N*/   if ( !pInf )
/*N*/   {
/*N*/       pInf = new ForbiddenCharactersInfo;
/*N*/       Insert( nLanguage, pInf );
/*N*/   }
/*N*/   pInf->bTemporary = FALSE;
/*N*/   pInf->aForbiddenChars = rForbiddenChars;
/*N*/ }

/*N*/ void SvxForbiddenCharactersTable::ClearForbiddenCharacters( USHORT nLanguage )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  ForbiddenCharactersInfo* pInf = Get( nLanguage );
//STRIP001  if ( pInf )
//STRIP001  {
//STRIP001      Remove( nLanguage );
//STRIP001      delete pInf;
//STRIP001  }
/*N*/ }
}
