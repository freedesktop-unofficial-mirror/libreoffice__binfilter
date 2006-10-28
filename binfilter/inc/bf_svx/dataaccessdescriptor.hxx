/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: dataaccessdescriptor.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 03:25:56 $
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

#ifndef _SVX_DATACCESSDESCRIPTOR_HXX_
#define _SVX_DATACCESSDESCRIPTOR_HXX_

#ifndef _COM_SUN_STAR_BEANS_PROPERTYVALUE_HPP_
#include <com/sun/star/beans/PropertyValue.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
#include <com/sun/star/beans/XPropertySet.hpp>
#endif
#include <tools/debug.hxx>
namespace binfilter {
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
    public:
        ODataAccessDescriptor(){DBG_BF_ASSERT(0, "STRIP"); }//STRIP001 ;
        ODataAccessDescriptor( const ODataAccessDescriptor& _rSource ){DBG_BF_ASSERT(0, "STRIP");} //STRIP001 ;
        ODataAccessDescriptor( const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >& _rValues ){DBG_BF_ASSERT(0, "STRIP");} //STRIP001 ;
        ODataAccessDescriptor( const ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue >& _rValues ){DBG_BF_ASSERT(0, "STRIP"); }//STRIP001 ;

        // allows to construct a descriptor from an Any containing either an XPropertySet or a property value sequence
        ODataAccessDescriptor( const ::com::sun::star::uno::Any& _rValues ){DBG_BF_ASSERT(0, "STRIP"); }//STRIP001 ;


        ~ODataAccessDescriptor(){DBG_BF_ASSERT(0, "STRIP");} //STRIP001
        ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue >
            createPropertyValueSequence(){DBG_BF_ASSERT(0, "STRIP");return ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue >();} //STRIP001 ;
        ::com::sun::star::uno::Any& operator [] ( DataAccessDescriptorProperty _eWhich ){DBG_BF_ASSERT(0, "STRIP"); static ::com::sun::star::uno::Any aDummy; return aDummy;}//STRIP001 ;
    };

//........................................................................
}   // namespace svx
//........................................................................

}//end of namespace binfilter
#endif // _SVX_DATACCESSDESCRIPTOR_HXX_

