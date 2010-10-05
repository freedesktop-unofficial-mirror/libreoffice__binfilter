/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2000, 2010 Oracle and/or its affiliates.
 *
 * OpenOffice.org - a multi-platform office productivity suite
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

#ifndef _XMLOFF_XMLINDEXBIBLIOGRAPHYENTRYCONTEXT_HXX_
#define _XMLOFF_XMLINDEXBIBLIOGRAPHYENTRYCONTEXT_HXX_

#include "XMLIndexSimpleEntryContext.hxx"

#include <com/sun/star/uno/Reference.h>

#include <com/sun/star/uno/Sequence.h>

#include <com/sun/star/beans/PropertyValue.hpp>


namespace com { namespace sun { namespace star {
    namespace xml { namespace sax { class XAttributeList; } }
} } }
namespace rtl { class OUString; }
namespace binfilter {
class XMLIndexTemplateContext;
struct SvXMLEnumMapEntry;

extern const SvXMLEnumMapEntry aBibliographyDataFieldMap[];

/**
 * Import bibliography index entry templates
 */
class XMLIndexBibliographyEntryContext : public XMLIndexSimpleEntryContext
{
    // bibliography info
    sal_Int16 nBibliographyInfo;
    sal_Bool bBibliographyInfoOK;

public:

    TYPEINFO();

    XMLIndexBibliographyEntryContext(
        SvXMLImport& rImport,
        XMLIndexTemplateContext& rTemplate,
        sal_uInt16 nPrfx,
        const ::rtl::OUString& rLocalName );

    ~XMLIndexBibliographyEntryContext();

protected:

    /** process parameters */
    virtual void StartElement(
        const ::com::sun::star::uno::Reference<
            ::com::sun::star::xml::sax::XAttributeList> & xAttrList);

    /** call FillPropertyValues and insert into template */
    virtual void EndElement();

    /** fill property values for this template entry */
    virtual void FillPropertyValues(
        ::com::sun::star::uno::Sequence<
            ::com::sun::star::beans::PropertyValue> & rValues);

};

}//end of namespace binfilter
#endif
