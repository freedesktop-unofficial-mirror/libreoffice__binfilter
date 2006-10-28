/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: unofill.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 04:22:13 $
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

#ifndef _SVX_UNOFILL_HXX_
#define _SVX_UNOFILL_HXX_

#ifndef _COM_SUN_STAR_UNO_XINTERFACE_HPP_
#include <com/sun/star/uno/XInterface.hpp>
#endif
namespace binfilter {

class SdrModel;

::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > SAL_CALL SvxUnoGradientTable_createInstance( SdrModel* pModel );
::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > SAL_CALL SvxUnoHatchTable_createInstance( SdrModel* pModel );
::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > SAL_CALL SvxUnoBitmapTable_createInstance( SdrModel* pModel );
::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > SAL_CALL SvxUnoTransGradientTable_createInstance( SdrModel* pModel );
::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > SAL_CALL SvxUnoMarkerTable_createInstance( SdrModel* pModel );
::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > SAL_CALL SvxUnoDashTable_createInstance( SdrModel* pModel );

}//end of namespace binfilter
#endif // _SVX_UNOFILL_HXX_
