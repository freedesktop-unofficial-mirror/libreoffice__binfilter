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

#include "XMLSectionFootnoteConfigImport.hxx"

#include "rtl/ustring.hxx"

#include <com/sun/star/uno/Reference.h>

#include "xmlimp.hxx"
#include "xmluconv.hxx"
#include "xmlnmspe.hxx"
#include "nmspmap.hxx"
#include "xmlnumi.hxx"
#include "txtprmap.hxx"

#include <tools/debug.hxx>
#include <vector>

namespace binfilter {


using namespace ::binfilter::xmloff::token;
using namespace ::com::sun::star::style;

using ::rtl::OUString;
using ::std::vector;
using ::com::sun::star::uno::Any;
using ::com::sun::star::uno::Reference;
using ::com::sun::star::xml::sax::XAttributeList;


TYPEINIT1(XMLSectionFootnoteConfigImport, SvXMLImportContext);


XMLSectionFootnoteConfigImport::XMLSectionFootnoteConfigImport(
    SvXMLImport& rInImport,
    sal_uInt16 nInPrefix,
    const OUString& rLocalName,
    vector<XMLPropertyState> & rProps,
    const UniReference<XMLPropertySetMapper> & rMapperRef,
    sal_Int32 nIndex) :
        SvXMLImportContext(rInImport, nInPrefix, rLocalName),
        rProperties(rProps),
        rMapper(rMapperRef),
        nPropIndex(nIndex)
{
}

XMLSectionFootnoteConfigImport::~XMLSectionFootnoteConfigImport()
{
}

void XMLSectionFootnoteConfigImport::StartElement(
    const Reference<XAttributeList> & xAttrList)
{
    sal_Bool bEnd = sal_True;   // we're inside the element, so this is true
    sal_Bool bNumOwn = sal_False;
    sal_Bool bNumRestart = sal_False;
    sal_Int16 nNumRestartAt = 0;
    OUString sNumPrefix;
    OUString sNumSuffix;
    OUString sNumFormat;
    OUString sNumLetterSync;

    // iterate over xattribute list and fill values
    sal_Int16 nLength = xAttrList->getLength();
    for(sal_Int16 nAttr = 0; nAttr < nLength; nAttr++)
    {
        OUString sLocalName;
        sal_uInt16 nLclPrefix = GetImport().GetNamespaceMap().
            GetKeyByAttrName( xAttrList->getNameByIndex(nAttr),
                              &sLocalName );
        OUString sAttrValue = xAttrList->getValueByIndex(nAttr);

        if (XML_NAMESPACE_TEXT == nLclPrefix)
        {
            if (IsXMLToken(sLocalName, XML_START_VALUE))
            {
                sal_Int32 nTmp;
                if (SvXMLUnitConverter::convertNumber(nTmp, sAttrValue))
                {
                    nNumRestartAt = nTmp - 1;
                    bNumRestart = sal_True;
                }
            }
        }
        else if (XML_NAMESPACE_STYLE == nLclPrefix)
        {
            if (IsXMLToken(sLocalName, XML_NUM_PREFIX))
            {
                sNumPrefix = sAttrValue;
                bNumOwn = sal_True;
            }
            else if (IsXMLToken(sLocalName, XML_NUM_SUFFIX))
            {
                sNumSuffix = sAttrValue;
                bNumOwn = sal_True;
            }
            else if (IsXMLToken(sLocalName, XML_NUM_FORMAT))
            {
                sNumFormat = sAttrValue;
                bNumOwn = sal_True;
            }
            else if (IsXMLToken(sLocalName, XML_NUM_LETTER_SYNC))
            {
                sNumLetterSync = sAttrValue;
                bNumOwn = sal_True;
            }
        }
    }

    // OK, now we have all values and can fill the XMLPropertyState vector
    Any aAny;
    sal_Bool bEndnote = IsXMLToken(GetLocalName(), XML_ENDNOTES_CONFIGURATION);

    aAny.setValue( &bNumOwn, ::getBooleanCppuType() );
    sal_Int32 nIndex = rMapper->FindEntryIndex( bEndnote ?
        CTF_SECTION_ENDNOTE_NUM_OWN : CTF_SECTION_FOOTNOTE_NUM_OWN );
    XMLPropertyState aNumOwn( nIndex, aAny );
    rProperties.push_back( aNumOwn );

    aAny.setValue( &bNumRestart, ::getBooleanCppuType() );
    nIndex = rMapper->FindEntryIndex( bEndnote ?
        CTF_SECTION_ENDNOTE_NUM_RESTART : CTF_SECTION_FOOTNOTE_NUM_RESTART );
    XMLPropertyState aNumRestart( nIndex, aAny );
    rProperties.push_back( aNumRestart );

    aAny <<= nNumRestartAt;
    nIndex = rMapper->FindEntryIndex( bEndnote ?
        CTF_SECTION_ENDNOTE_NUM_RESTART_AT :
        CTF_SECTION_FOOTNOTE_NUM_RESTART_AT );
    XMLPropertyState aNumRestartAtState( nIndex, aAny );
    rProperties.push_back( aNumRestartAtState );

    sal_Int16 nNumType = NumberingType::ARABIC;
    GetImport().GetMM100UnitConverter().convertNumFormat( nNumType,
                                                    sNumFormat,
                                                    sNumLetterSync );
    aAny <<= nNumType;
    nIndex = rMapper->FindEntryIndex( bEndnote ?
        CTF_SECTION_ENDNOTE_NUM_TYPE : CTF_SECTION_FOOTNOTE_NUM_TYPE );
    XMLPropertyState aNumFormatState( nIndex, aAny );
    rProperties.push_back( aNumFormatState );

    aAny <<= sNumPrefix;
    nIndex = rMapper->FindEntryIndex( bEndnote ?
        CTF_SECTION_ENDNOTE_NUM_PREFIX : CTF_SECTION_FOOTNOTE_NUM_PREFIX );
    XMLPropertyState aPrefixState( nIndex, aAny );
    rProperties.push_back( aPrefixState );

    aAny <<= sNumSuffix;
    nIndex = rMapper->FindEntryIndex( bEndnote ?
        CTF_SECTION_ENDNOTE_NUM_SUFFIX : CTF_SECTION_FOOTNOTE_NUM_SUFFIX );
    XMLPropertyState aSuffixState( nIndex, aAny );
    rProperties.push_back( aSuffixState );

    aAny.setValue( &bEnd, ::getBooleanCppuType() );
    nIndex = rMapper->FindEntryIndex( bEndnote ?
        CTF_SECTION_ENDNOTE_END : CTF_SECTION_FOOTNOTE_END );
    DBG_ASSERT( nIndex == nPropIndex, "Wrong property mapper index received.");
    XMLPropertyState aEndState( nIndex, aAny );
    rProperties.push_back( aEndState );
}
}//end of namespace binfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
