/*************************************************************************
 *
 *  $RCSfile: sch_SchAddInCollection.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:32:19 $
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

#include "SchAddInCollection.hxx"

#ifndef _COM_SUN_STAR_UNO_REFERENCE_H_
#include <com/sun/star/uno/Reference.h>
#endif
#ifndef _COM_SUN_STAR_LANG_XMULTISERVICEFACTORY_HPP_
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_XSINGLESERVICEFACTORY_HPP_
#include <com/sun/star/lang/XSingleServiceFactory.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XCONTENTENUMERATIONACCESS_HPP_
#include <com/sun/star/container/XContentEnumerationAccess.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_XSERVICENAME_HPP_
#include <com/sun/star/lang/XServiceName.hpp>
#endif
#ifndef _COMPHELPER_PROCESSFACTORY_HXX_
#include <comphelper/processfactory.hxx>
#endif
#include<tools/debug.hxx> //STRIP001
#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif
namespace binfilter {
using namespace ::com::sun::star;

/*N*/ SchAddInCollection::SchAddInCollection() :
/*N*/         mbInitialized( sal_False )
/*N*/ {
/*N*/ }

/*N*/ SchAddInCollection::~SchAddInCollection()
/*N*/ {}

/*N*/ void SchAddInCollection::Initialize()
/*N*/ {
/*N*/     // collect all service names of available AddIns
/*N*/
/*N*/     try
/*N*/     {
/*N*/         uno::Reference< lang::XMultiServiceFactory > xFactory = ::legacy_binfilters::getLegacyProcessServiceFactory();
/*N*/         uno::Reference< container::XContentEnumerationAccess > xEnumAcc( xFactory, uno::UNO_QUERY );
/*N*/         if( xEnumAcc.is())
/*N*/         {
/*N*/             uno::Reference< container::XEnumeration > xEnum =
/*N*/                 xEnumAcc->createContentEnumeration( ::rtl::OUString::createFromAscii( "com.sun.star.chart.Diagram" ));
/*N*/             if( xEnum.is())
/*N*/             {
/*N*/                 // clear possibly existing list
/*N*/                 if( mbInitialized )
/*N*/                     maServiceNames.realloc( 0 );
/*N*/
/*N*/                 while( xEnum->hasMoreElements())
/*N*/                 {
/*N*/                     // create Instance to collect the service name of the addin
/*N*/                     uno::Any aFactoryAny = xEnum->nextElement();
/*N*/                     uno::Reference< uno::XInterface > xFactoryIntf;
/*N*/                     aFactoryAny >>= xFactoryIntf;
/*N*/                     if( xFactoryIntf.is())
/*N*/                     {
/*N*/                         uno::Reference< lang::XSingleServiceFactory > xAddInFactory( xFactoryIntf, uno::UNO_QUERY );
/*N*/                         if( xAddInFactory.is())
/*N*/                         {
/*N*/                             uno::Reference< lang::XServiceName > xServicName(
/*N*/                                 xAddInFactory->createInstance(), uno::UNO_QUERY );
/*N*/                             if( xServicName.is())
/*N*/                             {
/*N*/                                 sal_Int32 nIndex = maServiceNames.getLength();
/*N*/                                 maServiceNames.realloc( nIndex + 1 );
/*N*/                                 maServiceNames[ nIndex ] = xServicName->getServiceName();
/*N*/                             }
/*N*/                         }
/*N*/                     }
/*N*/                 }
/*N*/             }
/*N*/         }
/*N*/         mbInitialized = sal_True;
/*N*/     }
/*N*/     catch( const uno::Exception& aEx )
/*N*/     {
/*N*/         OSL_ENSURE( false,
/*N*/                     ::rtl::OUStringToOString(
/*N*/                         ::rtl::OUString(
/*N*/                             RTL_CONSTASCII_USTRINGPARAM(
/*N*/                                 "Couldn't initialize add-in collection: " )) +
/*N*/                         aEx.Message,
/*N*/                         RTL_TEXTENCODING_ASCII_US ).getStr() );
/*N*/     }
/*N*/ }

/*N*/ uno::Reference< util::XRefreshable > SchAddInCollection::GetAddInByName( const ::rtl::OUString& rName )
/*N*/ {
/*N*/     if( ! mbInitialized )
/*?*/         {DBG_ASSERT(0, "STRIP");} //STRIP001 Initialize();
/*N*/
/*N*/     const sal_Int32 nSize = maServiceNames.getLength();
/*N*/     for( sal_Int32 i = 0; i < nSize; i++ )
/*N*/     {
/*N*/         if( rName.equalsIgnoreAsciiCase( maServiceNames[ i ] ))
/*N*/         {
/*N*/             uno::Reference< lang::XMultiServiceFactory > xFactory = ::legacy_binfilters::getLegacyProcessServiceFactory();
/*N*/             return uno::Reference< util::XRefreshable >( xFactory->createInstance( rName ), uno::UNO_QUERY );
/*N*/         }
/*N*/     }
/*N*/
/*N*/     return uno::Reference< util::XRefreshable >();
/*N*/ }

/*N*/ uno::Sequence< ::rtl::OUString > SchAddInCollection::GetAddInNames()
/*N*/ {
/*N*/     if( ! mbInitialized )
/*N*/         Initialize();
/*N*/
/*N*/     return maServiceNames;
/*N*/ }
}
