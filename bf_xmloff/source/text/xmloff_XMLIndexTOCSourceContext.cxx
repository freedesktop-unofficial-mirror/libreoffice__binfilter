/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */


#include "XMLIndexTOCSourceContext.hxx"


#include <com/sun/star/container/XIndexReplace.hpp>

#include "XMLIndexTemplateContext.hxx"




#include "xmlimp.hxx"


#include "xmlnmspe.hxx"



#include "xmluconv.hxx"


namespace binfilter {



using namespace ::binfilter::xmloff::token;

using ::rtl::OUString;
using ::com::sun::star::beans::XPropertySet;
using ::com::sun::star::uno::Reference;
using ::com::sun::star::uno::Any;
using ::com::sun::star::xml::sax::XAttributeList;

const sal_Char sAPI_CreateFromChapter[] = "CreateFromChapter";
const sal_Char sAPI_CreateFromOutline[] = "CreateFromOutline";
const sal_Char sAPI_CreateFromMarks[] = "CreateFromMarks";
const sal_Char sAPI_Level[] = "Level";
const sal_Char sAPI_CreateFromLevelParagraphStyles[] = "CreateFromLevelParagraphStyles";


TYPEINIT1( XMLIndexTOCSourceContext, XMLIndexSourceBaseContext );

XMLIndexTOCSourceContext::XMLIndexTOCSourceContext(
    SvXMLImport& rInImport,
    sal_uInt16 nPrfx,
    const OUString& rLocalName,
    Reference<XPropertySet> & rPropSet) :
        XMLIndexSourceBaseContext(rInImport, nPrfx, rLocalName,
                                  rPropSet, sal_True),
        sCreateFromMarks(RTL_CONSTASCII_USTRINGPARAM(sAPI_CreateFromMarks)),
        sLevel(RTL_CONSTASCII_USTRINGPARAM(sAPI_Level)),
       sCreateFromOutline(RTL_CONSTASCII_USTRINGPARAM(sAPI_CreateFromOutline)),
        sCreateFromLevelParagraphStyles(RTL_CONSTASCII_USTRINGPARAM(
            sAPI_CreateFromLevelParagraphStyles)),
        // use all chapters by default
        nOutlineLevel(rInImport.GetTextImport()->GetChapterNumbering()->
                                                                  getCount()),
        bUseOutline(sal_True),
        bUseMarks(sal_True),
        bUseParagraphStyles(sal_False)
{
}

XMLIndexTOCSourceContext::~XMLIndexTOCSourceContext()
{
}

void XMLIndexTOCSourceContext::ProcessAttribute(
    enum IndexSourceParamEnum eParam,
    const OUString& rValue)
{
    switch (eParam)
    {
        case XML_TOK_INDEXSOURCE_OUTLINE_LEVEL:
            if ( IsXMLToken( rValue, XML_NONE ) )
            {
                // #104651# use OUTLINE_LEVEL and USE_OUTLINE_LEVEL instead of
                // OUTLINE_LEVEL with values none|1..10. For backwards
                // compatibility, 'none' must still be read.
                bUseOutline = sal_False;
            }
            else
            {
                sal_Int32 nTmp;
                if (SvXMLUnitConverter::convertNumber(
                    nTmp, rValue, 1, GetImport().GetTextImport()->
                    GetChapterNumbering()->getCount()))
                {
                    bUseOutline = sal_True;
                    nOutlineLevel = nTmp;
                }
            }
            break;

        case XML_TOK_INDEXSOURCE_USE_OUTLINE_LEVEL:
        {
            sal_Bool bTmp;
            if (SvXMLUnitConverter::convertBool(bTmp, rValue))
            {
                bUseOutline = bTmp;
            }
            break;
        }


        case XML_TOK_INDEXSOURCE_USE_INDEX_MARKS:
        {
            sal_Bool bTmp;
            if (SvXMLUnitConverter::convertBool(bTmp, rValue))
            {
                bUseMarks = bTmp;
            }
            break;
        }

        case XML_TOK_INDEXSOURCE_USE_INDEX_SOURCE_STYLES:
        {
            sal_Bool bTmp;
            if (SvXMLUnitConverter::convertBool(bTmp, rValue))
            {
                bUseParagraphStyles = bTmp;
            }
            break;
        }

        default:
            // default: ask superclass
            XMLIndexSourceBaseContext::ProcessAttribute(eParam, rValue);
            break;
    }
}

void XMLIndexTOCSourceContext::EndElement()
{
    Any aAny;

    aAny.setValue(&bUseMarks, ::getBooleanCppuType());
    rIndexPropertySet->setPropertyValue(sCreateFromMarks, aAny);

    aAny.setValue(&bUseOutline, ::getBooleanCppuType());
    rIndexPropertySet->setPropertyValue(sCreateFromOutline, aAny);

    aAny.setValue(&bUseParagraphStyles, ::getBooleanCppuType());
    rIndexPropertySet->setPropertyValue(sCreateFromLevelParagraphStyles, aAny);

    aAny <<= (sal_Int16)nOutlineLevel;
    rIndexPropertySet->setPropertyValue(sLevel, aAny);

    // process common attributes
    XMLIndexSourceBaseContext::EndElement();
}


SvXMLImportContext* XMLIndexTOCSourceContext::CreateChildContext(
    sal_uInt16 nInPrefix,
    const OUString& rLocalName,
    const Reference<XAttributeList> & xAttrList )
{
    if ( (XML_NAMESPACE_TEXT == nInPrefix) &&
         IsXMLToken(rLocalName, XML_TABLE_OF_CONTENT_ENTRY_TEMPLATE) )
    {
        return new XMLIndexTemplateContext(GetImport(), rIndexPropertySet,
                                           nInPrefix, rLocalName,
                                           aLevelNameTOCMap,
                                           XML_OUTLINE_LEVEL,
                                           aLevelStylePropNameTOCMap,
                                           aAllowedTokenTypesTOC);
    }
    else
    {
        return XMLIndexSourceBaseContext::CreateChildContext(nInPrefix,
                                                             rLocalName,
                                                             xAttrList);
    }
}
}//end of namespace binfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
