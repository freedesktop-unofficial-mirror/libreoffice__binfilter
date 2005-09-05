/*************************************************************************
 *
 *  $RCSfile: xmlprmap.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-05 08:46:09 $
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

#ifndef _XMLOFF_PROPERTYSETMAPPER_HXX
#define _XMLOFF_PROPERTYSETMAPPER_HXX

#ifndef _COM_SUN_STAR_UNO_SEQUENCE_HXX_
#include <com/sun/star/uno/Sequence.hxx>
#endif

#ifndef _COM_SUN_STAR_UNO_ANY_HXX_
#include <com/sun/star/uno/Any.hxx>
#endif

#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
#include <com/sun/star/beans/XPropertySet.hpp>
#endif

#ifndef __SGI_STL_VECTOR
#include <vector>
#endif

#ifndef _UNIVERSALL_REFERENCE_HXX
#include <bf_xmloff/uniref.hxx>
#endif

#ifndef _XMLOFF_PROPMAPPINGTYPES_HXX
#include <bf_xmloff/maptype.hxx>
#endif

#ifndef _XMLOFF_XMLTYPES_HXX
#include <bf_xmloff/xmltypes.hxx>
#endif

#ifndef _XMLOFF_PROPERTYHANDLERFACTORY_HXX
#include <bf_xmloff/prhdlfac.hxx>
#endif
namespace binfilter {

class SvXMLUnitConverter;
class XMLPropertyHandler;

///////////////////////////////////////////////////////////////////////////
//
/** Helper-class for XML-im/export:
    - Holds a pointer to a given array of XMLPropertyMapEntry
    - Provides several methods to access data from this array
    - Holds a Sequence of XML-names (for properties)
    - The filter takes all properties of the XPropertySet which are also
      in the XMLPropertyMapEntry and which are have not a default value
      and put them into a vector of XMLPropertyStae
    - this class knows how to compare, im/export properties

    Attention: At all methods, which get an index as parameter, there is no
               range validation to save runtime !!
*/
struct XMLPropertySetMapperEntry_Impl
{
    ::rtl::OUString sXMLAttributeName;
    ::rtl::OUString sAPIPropertyName;
    sal_uInt16 nXMLNameSpace;
    sal_Int32  nType;
    sal_Int16  nContextId;
    const XMLPropertyHandler *pHdl;

    XMLPropertySetMapperEntry_Impl(
        const XMLPropertyMapEntry& rMapEntry,
        const UniReference< XMLPropertyHandlerFactory >& rFactory );

    XMLPropertySetMapperEntry_Impl(
        const XMLPropertySetMapperEntry_Impl& rEntry );
};

class XMLPropertySetMapper : public UniRefBase
{
    ::std::vector< XMLPropertySetMapperEntry_Impl > aMapEntries;
    ::std::vector< UniReference < XMLPropertyHandlerFactory > > aHdlFactories;

public:
    /** The last element of the XMLPropertyMapEntry-array must contain NULL-values */
    XMLPropertySetMapper(
            const XMLPropertyMapEntry* pEntries,
            const UniReference< XMLPropertyHandlerFactory >& rFactory );
    virtual ~XMLPropertySetMapper();

    void AddMapperEntry( const UniReference < XMLPropertySetMapper >& rMapper );

    /** Return number of entries in input-array */
    const sal_Int32 GetEntryCount() const { return aMapEntries.size(); }

    /** Returns the flags of an entry */
    const sal_uInt32 GetEntryFlags( sal_Int32 nIndex ) const
    {
        return aMapEntries[nIndex].nType & ~MID_FLAG_MASK;
    }

    /** Returns the type of an entry */
    const sal_uInt32 GetEntryType( sal_Int32 nIndex,
                                   sal_Bool bWithFlags = sal_True ) const
    {
        sal_uInt32 nType = aMapEntries[nIndex].nType;
        if( !bWithFlags )
            nType = nType & MID_FLAG_MASK;
        return nType;
    }

    /** Returns the namespace-key of an entry */
    const sal_uInt16 GetEntryNameSpace( sal_Int32 nIndex ) const
    {
        return aMapEntries[nIndex].nXMLNameSpace;
    }

    /** Returns the 'local' XML-name of the entry */
    const ::rtl::OUString& GetEntryXMLName( sal_Int32 nIndex ) const
    {
        return aMapEntries[nIndex].sXMLAttributeName;
    }

    /** Returns the entry API name */
    const ::rtl::OUString& GetEntryAPIName( sal_Int32 nIndex ) const
    {
        return aMapEntries[nIndex].sAPIPropertyName;
    }

    /** returns the entry context id */
    const sal_Int16 GetEntryContextId( sal_Int32 nIndex ) const
    {
        return nIndex == -1 ? 0 : aMapEntries[nIndex].nContextId;
    }

    /** Returns the index of an entry with the given XML-name and namespace
        If there is no matching entry the method returns -1 */
    const sal_Int32 GetEntryIndex( sal_uInt16 nNamespace,
                                   const ::rtl::OUString& rStrName,
                                   sal_Int32 nStartAt = -1 ) const;

    /** Retrieves a PropertyHandler for that property wich placed at nIndex in the XMLPropertyMapEntry-array */
    const XMLPropertyHandler* GetPropertyHandler( sal_Int32 nIndex ) const
    {
        return aMapEntries[nIndex].pHdl;
    }

    /** import/export
        This methods calls the respective im/export-method of the respective PropertyHandler. */
    virtual sal_Bool exportXML( ::rtl::OUString& rStrExpValue,
                                const XMLPropertyState& rProperty,
                                const SvXMLUnitConverter& rUnitConverter ) const;
    virtual sal_Bool importXML( const ::rtl::OUString& rStrImpValue,
                                XMLPropertyState& rProperty,
                                const SvXMLUnitConverter& rUnitConverter ) const;

    /** searches for an entry that matches the given api name, namespace and local name or -1 if nothing found */
    sal_Int32 FindEntryIndex( const sal_Char* sApiName,
                              sal_uInt16 nNameSpace,
                              const ::rtl::OUString& sXMLName ) const;

    /** searches for an entry that matches the given ContextId or gives -1 if nothing found */
    sal_Int32 FindEntryIndex( const sal_Int16 nContextId ) const;
};

}//end of namespace binfilter
#endif // _XMLOFF_PROPERTYSETMAPPER_HXX
