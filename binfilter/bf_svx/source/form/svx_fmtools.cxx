/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_fmtools.cxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: obo $ $Date: 2007-07-17 11:38:16 $
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

#include "fmtools.hxx"

#include <com/sun/star/uno/Reference.hxx>
#include <com/sun/star/container/XIndexAccess.hpp>

namespace binfilter {

using namespace ::com::sun::star;

/*N*/ sal_Int32 getElementPos(const uno::Reference< container::XIndexAccess>& xCont, const uno::Reference< uno::XInterface >& xElement)
/*N*/ {
/*N*/   sal_Int32 nIndex = -1;
/*N*/   if (!xCont.is())
/*N*/       return nIndex;
/*N*/
/*N*/   uno::Reference< uno::XInterface > xNormalized( xElement, uno::UNO_QUERY );
/*N*/   DBG_ASSERT( xNormalized.is(), "getElementPos: invalid element!" );
/*N*/   if ( xNormalized.is() )
/*N*/   {
/*N*/       // Feststellen an welcher Position sich das Kind befindet
/*N*/       nIndex = xCont->getCount();
/*N*/       while (nIndex--)
/*N*/       {
/*N*/           try
/*N*/           {
/*N*/               uno::Reference< uno::XInterface > xCurrent;
/*N*/               xCont->getByIndex( nIndex ) >>= xCurrent;
/*N*/               DBG_ASSERT( xCurrent.get() == uno::Reference< uno::XInterface >( xCurrent, uno::UNO_QUERY ).get(),
/*N*/                   "getElementPos: container element not normalized!" );
/*N*/               if ( xNormalized.get() == xCurrent.get() )
/*N*/                   break;
/*N*/           }
/*N*/           catch(uno::Exception&)
/*N*/           {
/*N*/               DBG_ERROR( "getElementPos: caught an exception!" );
/*N*/           }
/*N*/
/*N*/       }
/*N*/   }
/*N*/   return nIndex;
/*N*/ }

}
