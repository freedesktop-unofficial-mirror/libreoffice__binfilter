/*************************************************************************
 *
 *  $RCSfile: dataaccessdescriptor.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:47 $
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
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc..
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/

#ifndef _SVX_DATACCESSDESCRIPTOR_HXX_
#define _SVX_DATACCESSDESCRIPTOR_HXX_

#ifndef _COM_SUN_STAR_BEANS_PROPERTYVALUE_HPP_
#include <com/sun/star/beans/PropertyValue.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
#include <com/sun/star/beans/XPropertySet.hpp>
#endif
#include <tools/debug.hxx>
//........................................................................
namespace svx
{
//........................................................................

    class ODADescriptorImpl;

    //====================================================================
    //= DataAccessDescriptorProperty
    //====================================================================
    enum DataAccessDescriptorProperty
    {
        daDataSource,           /// data source name            (string)
        daConnection,           /// connection                  (XConnection)

        daCommand,              /// command                     (string)
        daCommandType,          /// command type                (long)
        daEscapeProcessing,     /// escape processing           (boolean)
        daFilter,               /// additional filter           (string)
        daCursor,               /// the cursor                  (XResultSet)

        daColumnName,           /// column name                 (string)
        daColumnObject,         /// column object               (XPropertySet)

        daSelection,            /// selection                   (sequence< any >)
        daBookmarkSelection     /// selection are bookmarks?    (boolean)
    };

    //====================================================================
    //= ODataAccessDescriptor
    //====================================================================
    /** class encapsulating the <type scope="com::sun::star::sdb">DataAccessDescriptor</type> service.
    */
    class ODataAccessDescriptor
    {
//STRIP001  protected:
//STRIP001      ODADescriptorImpl*      m_pImpl;
//STRIP001
    public:
        ODataAccessDescriptor(){DBG_ASSERT(0, "STRIP"); }//STRIP001 ;
        ODataAccessDescriptor( const ODataAccessDescriptor& _rSource ){DBG_ASSERT(0, "STRIP");} //STRIP001 ;
        ODataAccessDescriptor( const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >& _rValues ){DBG_ASSERT(0, "STRIP");} //STRIP001 ;
        ODataAccessDescriptor( const ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue >& _rValues ){DBG_ASSERT(0, "STRIP"); }//STRIP001 ;

        // allows to construct a descriptor from an Any containing either an XPropertySet or a property value sequence
        ODataAccessDescriptor( const ::com::sun::star::uno::Any& _rValues ){DBG_ASSERT(0, "STRIP"); }//STRIP001 ;

//STRIP001      const ODataAccessDescriptor& operator=(const ODataAccessDescriptor& _rSource);

        ~ODataAccessDescriptor(){DBG_ASSERT(0, "STRIP");} //STRIP001
//STRIP001
//STRIP001      /** returns the descriptor as property set
//STRIP001          <p>If you call this method more than once, without writing any values between both calls, the same object
//STRIP001          is returned. If you wrote values, a new object is returned.</p>
//STRIP001      */
//STRIP001      ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >
//STRIP001                  createPropertySet();
//STRIP001      /** returns the descriptor as property value sequence
//STRIP001          <p>If you call this method more than once, without writing any values between both calls, the same object
//STRIP001          is returned. If you wrote values, a new object is returned.</p>
//STRIP001      */
        ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue >
            createPropertyValueSequence(){DBG_ASSERT(0, "STRIP");return ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue >();} //STRIP001 ;
//STRIP001
//STRIP001      /** returns the descriptor as Any sequence
//STRIP001          <p>If you call this method more than once, without writing any values between both calls, the same object
//STRIP001          is returned. If you wrote values, a new object is returned.</p>
//STRIP001      */
//STRIP001      ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Any >
//STRIP001                  createAnySequence();
//STRIP001
//STRIP001      /** initialized the descriptor from the property set given
//STRIP001          <p>If <arg>_bClear</arg> is <TRUE/>, the descriptor will clear all it's current settings before
//STRIP001          initializing with the new ones.</p>
//STRIP001      */
//STRIP001      void        initializeFrom(
//STRIP001                      const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >& _rxValues,
//STRIP001                      sal_Bool _bClear = sal_True);
//STRIP001
//STRIP001      /** initialized the descriptor from the property values given
//STRIP001          <p>If <arg>_bClear</arg> is <TRUE/>, the descriptor will clear all it's current settings before
//STRIP001          initializing with the new ones.</p>
//STRIP001      */
//STRIP001      void        initializeFrom(
//STRIP001                      const ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue >& _rValues,
//STRIP001                      sal_Bool _bClear = sal_True);
//STRIP001
//STRIP001      /// checks whether or not a given property is present in the descriptor
//STRIP001      sal_Bool    has(DataAccessDescriptorProperty _eWhich) const;
//STRIP001
//STRIP001      /** erases the given property from the descriptor
//STRIP001      */
//STRIP001      void        erase(DataAccessDescriptorProperty _eWhich);
//STRIP001
//STRIP001      /** empties the descriptor
//STRIP001      */
//STRIP001      void        clear();
//STRIP001
//STRIP001      /// return the value of a given property
//STRIP001      const   ::com::sun::star::uno::Any& operator [] ( DataAccessDescriptorProperty _eWhich ) const;
//STRIP001
//STRIP001      /** return the (modifiable) value of a given property
//STRIP001          <p>This operator is not allowed to be called if the descriptor is readonly.</p>
//STRIP001      */
        ::com::sun::star::uno::Any& operator [] ( DataAccessDescriptorProperty _eWhich ){DBG_ASSERT(0, "STRIP"); static ::com::sun::star::uno::Any aDummy; return aDummy;}//STRIP001 ;
    };

//........................................................................
}   // namespace svx
//........................................................................

#endif // _SVX_DATACCESSDESCRIPTOR_HXX_

