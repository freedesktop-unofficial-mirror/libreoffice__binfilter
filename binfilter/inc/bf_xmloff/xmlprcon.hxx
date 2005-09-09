/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xmlprcon.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 17:42:38 $
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

#ifndef _XMLOFF_XMLPROPERTYSETCONTEXT_HXX
#define _XMLOFF_XMLPROPERTYSETCONTEXT_HXX

#ifndef _XMLOFF_XMLICTXT_HXX
#include <bf_xmloff/xmlictxt.hxx>
#endif

#ifndef _XMLOFF_XMLIMPPR_HXX
#include <bf_xmloff/xmlimppr.hxx>
#endif
#ifndef _XMLOFF_PROPERTYSETMAPPER_HXX
#include <bf_xmloff/xmlprmap.hxx>
#endif
#ifndef _UNIVERSALL_REFERENCE_HXX
#include <bf_xmloff/uniref.hxx>
#endif

namespace rtl { class OUString; }
namespace binfilter {

class SvXMLImportPropertyMapper;

class SvXMLPropertySetContext : public SvXMLImportContext
{
protected:
    sal_Int32 nStartIdx;
    sal_Int32 nEndIdx;
    ::std::vector< XMLPropertyState > &rProperties;
    UniReference < SvXMLImportPropertyMapper >   xMapper;

public:

    SvXMLPropertySetContext(
            SvXMLImport& rImport, USHORT nPrfx,
            const ::rtl::OUString& rLName,
            const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& xAttrList,
            ::std::vector< XMLPropertyState > &rProps,
            const UniReference < SvXMLImportPropertyMapper > &rMap,
              sal_Int32 nStartIdx = -1, sal_Int32 nEndIdx = -1 );

    virtual ~SvXMLPropertySetContext();

    virtual SvXMLImportContext *CreateChildContext( USHORT nPrefix,
                                     const ::rtl::OUString& rLocalName,
                                     const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& xAttrList );

    // This method is called from this instance implementation of
    // CreateChildContext if the element matches an entry in the
    // SvXMLImportItemMapper with the mid flag MID_FLAG_ELEMENT_ITEM_IMPORT
    virtual SvXMLImportContext *CreateChildContext( USHORT nPrefix,
                                   const ::rtl::OUString& rLocalName,
                                   const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& xAttrList,
                                   ::std::vector< XMLPropertyState > &rProperties,
                                   const XMLPropertyState& rProp );

};

}//end of namespace binfilter
#endif  //  _XMLOFF_XMLPROPERTYSETCONTEXT_HXX

