/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: transuno.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 08:21:11 $
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

#ifndef _RTL_WSTRING
#include <rtl/ustring.h>
#endif

#ifndef _COM_SUN_STAR_UNO_REFERENCE_H_
#include <com/sun/star/uno/Reference.h>
#endif
#ifndef _COM_SUN_STAR_UNO_SEQUENCE_HXX_
#include <com/sun/star/uno/Sequence.hxx>
#endif
#ifndef _COM_SUN_STAR_UNO_XINTERFACE_HPP_
#include <com/sun/star/uno/XInterface.hpp>
#endif

#ifndef _COM_SUN_STAR_BEANS_PROPERTYVALUE_HPP_
#include <com/sun/star/beans/PropertyValue.hpp>
#endif

#ifndef _COM_SUN_STAR_LANG_XMULTISERVICEFACTORY_HPP_
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#endif

#ifndef _COM_SUN_STAR_UCB_XCONTENT_HPP_
#include <com/sun/star/ucb/XContent.hpp>
#endif
#ifndef _COM_SUN_STAR_UCB_XCONTENTIDENTIFIER_HPP_
#include <com/sun/star/ucb/XContentIdentifier.hpp>
#endif
#ifndef _COM_SUN_STAR_UCB_XCONTENTIDENTIFIERFACTORY_HPP_
#include <com/sun/star/ucb/XContentIdentifierFactory.hpp>
#endif
#ifndef _COM_SUN_STAR_UCB_XCONTENTPROVIDER_HPP_
#include <com/sun/star/ucb/XContentProvider.hpp>
#endif
#ifndef _COM_SUN_STAR_UCB_XCONTENTPROVIDERMANAGER_HPP_
#include <com/sun/star/ucb/XContentProviderManager.hpp>
#endif

#include <unotools/processfactory.hxx>

#ifndef _TRANSUNO_HXX
#include <transuno.hxx>
#endif

/*========================================================================
 *
 * SvBindingTransport_Impl internals.
 *
 *======================================================================*/
using namespace com::sun::star::ucb;
using namespace com::sun::star::uno;
using namespace com::sun::star::sdbc;

namespace binfilter {

typedef com::sun::star::lang::XMultiServiceFactory factory_type;
typedef com::sun::star::uno::XInterface            interface_type;


/*
 * S2U.
 */
inline rtl::OUString S2U (const sal_Char *ascii)
{
    return rtl::OUString::createFromAscii (ascii);
}

/*========================================================================
 *
 * SvBindingTransport_Impl implementation.
 *
 *======================================================================*/
/*
 * getProcessServiceFactory.
 */
com::sun::star::uno::Reference<com::sun::star::uno::XInterface>
SvBindingTransport_Impl::getProcessServiceFactory (void)
{
    return com::sun::star::uno::Reference<com::sun::star::uno::XInterface>(
        utl::getProcessServiceFactory(), com::sun::star::uno::UNO_QUERY_THROW);
}

/*
 * createContent.
 */
com::sun::star::uno::Reference<XContent>
SvBindingTransport_Impl::createContent (const rtl::OUString &rUrl)
{
    com::sun::star::uno::Reference<factory_type>
        xFactory (getProcessServiceFactory(), com::sun::star::uno::UNO_QUERY);
    if (!xFactory.is())
        return com::sun::star::uno::Reference<XContent>();

    com::sun::star::uno::Reference<interface_type>
        xBroker (xFactory->createInstance (
            S2U ("com.sun.star.ucb.UniversalContentBroker")));
    if (!xBroker.is())
        return com::sun::star::uno::Reference<XContent>();

    com::sun::star::uno::Reference<XContentProvider>
        xProvider (xBroker, com::sun::star::uno::UNO_QUERY);
    if (!xProvider.is())
        return com::sun::star::uno::Reference<XContent>();

    com::sun::star::uno::Reference<XContentIdentifierFactory>
        xIdentProv (xProvider, com::sun::star::uno::UNO_QUERY);
    if (!xIdentProv.is())
        return com::sun::star::uno::Reference<XContent>();

    com::sun::star::uno::Reference<XContentIdentifier>
        xIdent (xIdentProv->createContentIdentifier (rUrl));
    if (!xIdent.is())
        return com::sun::star::uno::Reference<XContent>();

    return xProvider->queryContent (xIdent);
}

/*
 * getProperties.
 */
Any SvBindingTransport_Impl::getProperties ( const Reference<XCommandProcessor> &rxProcessor, const Sequence<Property> &rProperties)
{
    Any aResult;
    if (rxProcessor.is() && rProperties.getLength())
    {
        try
        {
            com::sun::star::uno::Reference<XCommandEnvironment> xEnvironment;
            Command aCommand;
            aCommand.Name     = ::rtl::OUString::createFromAscii("getPropertyValues");
            aCommand.Handle   = -1; /* unknown */
            aCommand.Argument <<= rProperties;
            aResult = rxProcessor->execute( aCommand, 0, xEnvironment );
        }
        catch (com::sun::star::uno::Exception &)
        {
        }
    }

    return aResult;
}

/*
 * setProperties.
 */
void SvBindingTransport_Impl::setProperties ( const Reference<XCommandProcessor> &rxProcessor, const Sequence<PropertyValue> &rProperties)
{
    if (rxProcessor.is() && rProperties.getLength())
    {
        try
        {
            Reference<XCommandEnvironment> xEnvironment;
            Command aCommand;
            aCommand.Name     = ::rtl::OUString::createFromAscii("setPropertyValues");
            aCommand.Handle   = -1; /* unknown */
            aCommand.Argument <<= rProperties;
            rxProcessor->execute( aCommand, 0, xEnvironment );
        }
        catch (com::sun::star::uno::Exception &)
        {
        }
    }
}

}
