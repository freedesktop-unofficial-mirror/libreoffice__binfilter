/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: txtexppr.hxx,v $
 * $Revision: 1.3 $
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/
#ifndef _XMLOFF_TXTEXPPR_HXX
#define _XMLOFF_TXTEXPPR_HXX


#ifndef _XMLOFF_XMLEXPPR_HXX
#include "xmlexppr.hxx"
#endif
#ifndef _XMLOFF_TXTDROPE_HXX
#include "txtdrope.hxx"
#endif
#ifndef _XMLOFF_XMLTABE_HXX
#include "xmltabe.hxx"
#endif
#ifndef _XMLOFF_XMLTEXTCOLUMNSEXPORT_HXX
#include "XMLTextColumnsExport.hxx"
#endif
#ifndef _XMLOFF_XMLBACKGROUNDIMAGEEXPORT_HXX
#include "XMLBackgroundImageExport.hxx"
#endif
namespace binfilter {

class SvXMLExport;
class XMLTextExportPropertySetMapper: public SvXMLExportPropertyMapper
{
    SvXMLExport& rExport;

    ::rtl::OUString sDropCharStyle;
    sal_Bool bDropWholeWord;

    void ContextFontFilter(
                XMLPropertyState *pFontNameState,
                XMLPropertyState *pFontFamilyNameState,
                XMLPropertyState *pFontStyleNameState,
                XMLPropertyState *pFontFamilyState,
                XMLPropertyState *pFontPitchState,
                XMLPropertyState *pFontCharsetState ) const;
    void ContextFontHeightFilter(
                XMLPropertyState* pCharHeightState,
                XMLPropertyState* pCharPropHeightState,
                XMLPropertyState* pCharDiffHeightState ) const;

protected:
//  SvXMLUnitConverter& mrUnitConverter;
//  const Reference< xml::sax::XDocumentHandler > & mrHandler;
    XMLTextDropCapExport maDropCapExport;
    SvxXMLTabStopExport maTabStopExport;
    XMLTextColumnsExport maTextColumnsExport;
    XMLBackgroundImageExport maBackgroundImageExport;

    /** Application-specific filter. By default do nothing. */
    virtual void ContextFilter(
            ::std::vector< XMLPropertyState >& rProperties,
            ::com::sun::star::uno::Reference<
                        ::com::sun::star::beans::XPropertySet > rPropSet ) const;
    const SvXMLExport& GetExport() const { return rExport; }

public:

    XMLTextExportPropertySetMapper(
            const UniReference< XMLPropertySetMapper >& rMapper,
            SvXMLExport& rExt );
    virtual ~XMLTextExportPropertySetMapper();

    virtual void handleElementItem(
        SvXMLExport& rExport,
        const XMLPropertyState& rProperty,
        sal_uInt16 nFlags,
        const ::std::vector< XMLPropertyState > *pProperties = 0,
        sal_uInt32 nIdx = 0 ) const;

    virtual void handleSpecialItem(
        SvXMLAttributeList& rAttrList,
        const XMLPropertyState& rProperty,
        const SvXMLUnitConverter& rUnitConverter,
        const SvXMLNamespaceMap& rNamespaceMap,
        const ::std::vector< XMLPropertyState > *pProperties = 0,
        sal_uInt32 nIdx = 0 ) const;
};


}//end of namespace binfilter
#endif
