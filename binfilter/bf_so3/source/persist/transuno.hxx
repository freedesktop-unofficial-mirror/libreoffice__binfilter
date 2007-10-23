/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: transuno.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: vg $ $Date: 2007-10-23 13:54:10 $
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

#ifndef _TRANSUNO_HXX
#define _TRANSUNO_HXX "$Revision: 1.2 $"

#ifndef _RTL_USTRING_
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
#ifndef _COM_SUN_STAR_BEANS_PROPERTY_HPP_
#include <com/sun/star/beans/Property.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_PROPERTYVALUE_HPP_
#include <com/sun/star/beans/PropertyValue.hpp>
#endif
#ifndef _COM_SUN_STAR_UCB_PROPERTYVALUEINFO_HPP_
#include <com/sun/star/ucb/PropertyValueInfo.hpp>
#endif
#ifndef _COM_SUN_STAR_UCB_XCONTENT_HPP_
#include <com/sun/star/ucb/XContent.hpp>
#endif
#ifndef _COM_SUN_STAR_UCB_XCOMMANDPROCESSOR_HPP_
#include <com/sun/star/ucb/XCommandProcessor.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_XROW_HPP_
#include <com/sun/star/sdbc/XRow.hpp>
#endif

using com::sun::star::beans::PropertyValue;
using com::sun::star::beans::Property;
using com::sun::star::ucb::XContent;
using com::sun::star::ucb::XCommandProcessor;

/*========================================================================
 *
 * SvBindingTransport_Impl interface.
 *
 *======================================================================*/
class SvBindingTransport_Impl
{
public:
    /** getProcessServiceFactory.
     */
    static com::sun::star::uno::Reference<com::sun::star::uno::XInterface>
    getProcessServiceFactory (void);

    /** createContent.
     */
    static com::sun::star::uno::Reference<XContent>
    createContent (
        const rtl::OUString &rUrl);

    /** getProperties.
     */
    static com::sun::star::uno::Any
    getProperties (
        const com::sun::star::uno::Reference<XCommandProcessor> &rxProc,
        const com::sun::star::uno::Sequence<Property>           &rxProp);

    /** setProperties.
     */
    static void setProperties (
        const com::sun::star::uno::Reference<XCommandProcessor> &rxProc,
        const com::sun::star::uno::Sequence<PropertyValue>           &rxProp);
};

/*========================================================================
 *
 * The End.
 *
 *======================================================================*/

#endif /* !_TRANSUNO_HXX */

