/*************************************************************************
 *
 *  $RCSfile: xmlimppr.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: aw $ $Date: 2003-12-05 09:18:06 $
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
#ifndef _XMLOFF_XMLIMPPR_HXX
#define _XMLOFF_XMLIMPPR_HXX

#ifndef _SOLAR_H
#include <tools/solar.h>
#endif

#ifndef _COM_SUN_STAR_XML_SAX_XATTRIBUTELIST_HPP_
#include <com/sun/star/xml/sax/XAttributeList.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
#include <com/sun/star/beans/XPropertySet.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_XMULTIPROPERTYSET_HPP_
#include <com/sun/star/beans/XMultiPropertySet.hpp>
#endif

#ifndef __SGI_STL_VECTOR
#include <vector>
#endif

#ifndef _UNIVERSALL_REFERENCE_HXX
#include <bf_xmloff/uniref.hxx>
#endif
namespace rtl { class OUString; }
namespace binfilter {

struct XMLPropertyState;
class XMLPropertySetMapper;


class SvXMLUnitConverter;
class SvXMLNamespaceMap;
class SvXMLImport;

/** This struct is used as an optional parameter to the static
 * _FillPropertySet() methods.
 *
 * It should not be used in any other context.
 */
struct _ContextID_Index_Pair
{
    sal_Int16 nContextID;
    sal_Int32 nIndex;
};

class SvXMLImportPropertyMapper : public UniRefBase
{
    UniReference< SvXMLImportPropertyMapper> mxNextMapper;

    SvXMLImport& rImport;   // access to error handling

protected:

    UniReference< XMLPropertySetMapper > maPropMapper;

public:

    SvXMLImportPropertyMapper(
            const UniReference< XMLPropertySetMapper >& rMapper,
            SvXMLImport& rImport);
    virtual ~SvXMLImportPropertyMapper();

    // Add a ImportPropertyMapper at the end of the import mapper chain.
    // The added mapper MUST not be used outside the Mapper chain any longer,
    // because its PropertyMapper will be replaced.
    void ChainImportMapper(
        const UniReference< SvXMLImportPropertyMapper>& rMapper );

    /** fills the given itemset with the attributes in the given list */
    void importXML(
            ::std::vector< XMLPropertyState >& rProperties,
            ::com::sun::star::uno::Reference<
                    ::com::sun::star::xml::sax::XAttributeList > xAttrList,
            const SvXMLUnitConverter& rUnitConverter,
            const SvXMLNamespaceMap& rNamespaceMap ) const;

    /** like above, except that the mart is only serached within the range
      *  [nStartIdx, nEndIdx[
      */
    void importXML(
            ::std::vector< XMLPropertyState >& rProperties,
            ::com::sun::star::uno::Reference<
                    ::com::sun::star::xml::sax::XAttributeList > xAttrList,
            const SvXMLUnitConverter& rUnitConverter,
            const SvXMLNamespaceMap& rNamespaceMap,
            sal_Int32 nStartIdx, sal_Int32 nEndIdx ) const;

    /** this method is called for every item that has the MID_FLAG_SPECIAL_ITEM_IMPORT flag set */
    virtual sal_Bool handleSpecialItem(
            XMLPropertyState& rProperty,
            ::std::vector< XMLPropertyState >& rProperties,
            const ::rtl::OUString& rValue,
            const SvXMLUnitConverter& rUnitConverter,
            const SvXMLNamespaceMap& rNamespaceMap ) const;

    /** This method is called when all attributes have benn processed. It may be used to remove items that are incomplete */
    virtual void finished(
            ::std::vector< XMLPropertyState >& rProperties,
            sal_Int32 nStartIndex, sal_Int32 nEndIndex ) const;

    sal_Bool FillPropertySet(
            const ::std::vector< XMLPropertyState >& aProperties,
            const ::com::sun::star::uno::Reference<
                    ::com::sun::star::beans::XPropertySet > rPropSet ) const;

    inline const UniReference< XMLPropertySetMapper >&
        getPropertySetMapper() const;

    /** implementation helper for FillPropertySet: fill an XPropertySet.
     * Exceptions will be asserted. */
    static sal_Bool _FillPropertySet(
        const ::std::vector<XMLPropertyState> & rProperties,
        const ::com::sun::star::uno::Reference<
            ::com::sun::star::beans::XPropertySet> & rPropSet,
        const ::com::sun::star::uno::Reference<
            ::com::sun::star::beans::XPropertySetInfo> & rPropSetInfo,
        const UniReference<XMLPropertySetMapper> & rPropMapper,
        SvXMLImport& rImport,

        // parameter for use by txtstyli.cxx; allows efficient
        // catching the combined characters property
        struct _ContextID_Index_Pair* pSpecialContextIds = NULL );

    /** implementation helper for FillPropertySet: fill an XMultiPropertySet.
     * If unsuccessul, set return value. */
    static sal_Bool _FillMultiPropertySet(
        const ::std::vector<XMLPropertyState> & rProperties,
        const ::com::sun::star::uno::Reference<
            ::com::sun::star::beans::XMultiPropertySet> & rMultiPropSet,
        const ::com::sun::star::uno::Reference<
            ::com::sun::star::beans::XPropertySetInfo> & rPropSetInfo,
        const UniReference<XMLPropertySetMapper> & rPropMapper,

        // parameters for use by txtstyli.cxx; allows efficient
        // catching the combined characters property
        struct _ContextID_Index_Pair* pSpecialContextIds = NULL );

};

inline const UniReference< XMLPropertySetMapper >&
    SvXMLImportPropertyMapper::getPropertySetMapper() const
{
    return maPropMapper;
}

}//end of namespace binfilter
#endif  //  _XMLOFF_XMLIMPPR_HXX
