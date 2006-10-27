/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: unostyls.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 18:39:39 $
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

#ifndef _COM_SUN_STAR_CONTAINER_XINDEXACCESS_HPP_
#include <com/sun/star/container/XIndexAccess.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XNAMEACCESS_HPP_
#include <com/sun/star/container/XNameAccess.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_XSERVICEINFO_HPP_
#include <com/sun/star/lang/XServiceInfo.hpp>
#endif

#include <cppuhelper/implbase3.hxx>

#include <unomodel.hxx>
namespace binfilter {

class SvUnoWeakContainer;

class SdUnoStyleFamilies : public ::cppu::WeakImplHelper3<
                                        ::com::sun::star::lang::XServiceInfo,
                                        ::com::sun::star::container::XIndexAccess,
                                        ::com::sun::star::container::XNameAccess >
{
protected:
    ::com::sun::star::uno::Reference< ::com::sun::star::frame::XModel > mxModel;
    SdXImpressDocument* mpModel;

    sal_Bool mbImpress;

    ::com::sun::star::uno::WeakReference< ::com::sun::star::container::XNameAccess > mxGraphicStyles;
    SvUnoWeakContainer* mpStyleFamilies;

    sal_uInt16 getLayoutCount() throw();
    ::rtl::OUString getLayoutNameByIndex( sal_uInt16 nIndex ) throw();
    sal_uInt16 getLayoutIndexByName( const ::rtl::OUString& rName ) throw();

    void createGraphicStyleFamily( ::com::sun::star::uno::Any& rAny ) throw( ::com::sun::star::container::NoSuchElementException ) ;
    void createStyleFamilyByIndex( sal_uInt16 nLayout, ::com::sun::star::uno::Any& rAny ) throw();

public:
    SdUnoStyleFamilies( SdXImpressDocument* pModel ) throw();
    virtual ~SdUnoStyleFamilies() throw();

    sal_Bool isValid() const throw() { return mxModel.is(); }

    // XServiceInfo
    virtual ::rtl::OUString SAL_CALL getImplementationName() throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ServiceName ) throw(::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames() throw(::com::sun::star::uno::RuntimeException);

    // XNameAccess
    virtual ::com::sun::star::uno::Any SAL_CALL getByName( const ::rtl::OUString& aName ) throw(::com::sun::star::container::NoSuchElementException, ::com::sun::star::lang::WrappedTargetException, ::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getElementNames() throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL hasByName( const ::rtl::OUString& aName ) throw(::com::sun::star::uno::RuntimeException);

    // XElementAccess
    virtual ::com::sun::star::uno::Type SAL_CALL getElementType() throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL hasElements() throw(::com::sun::star::uno::RuntimeException);

    // XIndexAccess
    virtual sal_Int32 SAL_CALL getCount() throw(::com::sun::star::uno::RuntimeException) ;
    virtual ::com::sun::star::uno::Any SAL_CALL getByIndex( sal_Int32 Index ) throw(::com::sun::star::lang::IndexOutOfBoundsException, ::com::sun::star::lang::WrappedTargetException, ::com::sun::star::uno::RuntimeException);
};

} //namespace binfilter
