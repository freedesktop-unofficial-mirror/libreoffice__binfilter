/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: xmloff_XMLSectionExport.cxx,v $
 * $Revision: 1.6 $
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

#ifndef _XMLOFF_XMLSECTIONEXPORT_HXX_
#include "XMLSectionExport.hxx"
#endif

#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif



#include <vector>







#ifndef _COM_SUN_STAR_BEANS_PROPERTYVALUES_HPP_
#include <com/sun/star/beans/PropertyValues.hpp>
#endif



#ifndef _COM_SUN_STAR_TEXT_XTEXTSECTION_HPP_
#include <com/sun/star/text/XTextSection.hpp>
#endif

#ifndef _COM_SUN_STAR_TEXT_SECTIONFILELINK_HPP_
#include <com/sun/star/text/SectionFileLink.hpp>
#endif



#ifndef _COM_SUN_STAR_TEXT_XDOCUMENTINDEX_HPP_
#include <com/sun/star/text/XDocumentIndex.hpp>
#endif


#ifndef _COM_SUN_STAR_TEXT_BIBLIOGRAPHYDATAFIELD_HPP_
#include <com/sun/star/text/BibliographyDataField.hpp>
#endif

#ifndef _COM_SUN_STAR_TEXT_XTEXTFIELDSSUPPLIER_HPP_
#include <com/sun/star/text/XTextFieldsSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_TEXT_XCHAPTERNUMBERINGSUPPLIER_HPP_
#include <com/sun/star/text/XChapterNumberingSupplier.hpp>
#endif

#ifndef _XMLOFF_XMLKYWD_HXX
#include "xmlkywd.hxx"
#endif




#ifndef _XMLOFF_XMLUCONV_HXX
#include "xmluconv.hxx"
#endif


#ifndef _XMLOFF_XMLEXP_HXX
#include "xmlexp.hxx"
#endif


#ifndef _XMLOFF_TXTFLDE_HXX
#include "txtflde.hxx"
#endif

namespace binfilter {

using namespace ::com::sun::star;
using namespace ::com::sun::star::text;
using namespace ::com::sun::star::uno;
using namespace ::std;
using namespace ::binfilter::xmloff::token;

using ::rtl::OUString;
using ::rtl::OUStringBuffer;
using ::com::sun::star::beans::XPropertySet;
using ::com::sun::star::beans::PropertyValue;
using ::com::sun::star::beans::PropertyValues;
using ::com::sun::star::beans::PropertyState;
using ::com::sun::star::container::XIndexReplace;
using ::com::sun::star::container::XNameAccess;
using ::com::sun::star::container::XNamed;
using ::com::sun::star::lang::XServiceInfo;
using ::com::sun::star::lang::Locale;
using ::com::sun::star::uno::XInterface;


XMLSectionExport::XMLSectionExport(
    SvXMLExport& rExp,
    XMLTextParagraphExport& rParaExp) :
        rExport(rExp),
        rParaExport(rParaExp),
        sCondition(RTL_CONSTASCII_USTRINGPARAM("Condition")),
        sCreateFromChapter(RTL_CONSTASCII_USTRINGPARAM("CreateFromChapter")),
        sCreateFromLabels(RTL_CONSTASCII_USTRINGPARAM("CreateFromLabels")),
        sCreateFromMarks(RTL_CONSTASCII_USTRINGPARAM("CreateFromMarks")),
        sCreateFromOutline(RTL_CONSTASCII_USTRINGPARAM("CreateFromOutline")),
        sDdeCommandElement(RTL_CONSTASCII_USTRINGPARAM("DDECommandElement")),
        sDdeCommandFile(RTL_CONSTASCII_USTRINGPARAM("DDECommandFile")),
        sDdeCommandType(RTL_CONSTASCII_USTRINGPARAM("DDECommandType")),
        sFileLink(RTL_CONSTASCII_USTRINGPARAM("FileLink")),
        sIsCaseSensitive(RTL_CONSTASCII_USTRINGPARAM("IsCaseSensitive")),
        sIsProtected(RTL_CONSTASCII_USTRINGPARAM("IsProtected")),
        sIsVisible(RTL_CONSTASCII_USTRINGPARAM("IsVisible")),
        sLabelCategory(RTL_CONSTASCII_USTRINGPARAM("LabelCategory")),
        sLabelDisplayType(RTL_CONSTASCII_USTRINGPARAM("LabelDisplayType")),
        sLevel(RTL_CONSTASCII_USTRINGPARAM("Level")),
        sLevelFormat(RTL_CONSTASCII_USTRINGPARAM("LevelFormat")),
        sLevelParagraphStyles(
            RTL_CONSTASCII_USTRINGPARAM("LevelParagraphStyles")),
        sLinkRegion(RTL_CONSTASCII_USTRINGPARAM("LinkRegion")),
        sMainEntryCharacterStyleName(
            RTL_CONSTASCII_USTRINGPARAM("MainEntryCharacterStyleName")),
        sParaStyleHeading(RTL_CONSTASCII_USTRINGPARAM("ParaStyleHeading")),
        sParaStyleLevel(RTL_CONSTASCII_USTRINGPARAM("ParaStyleLevel")),
        sTitle(RTL_CONSTASCII_USTRINGPARAM("Title")),
        sName(RTL_CONSTASCII_USTRINGPARAM("Name")),
        sUseAlphabeticalSeparators(
            RTL_CONSTASCII_USTRINGPARAM("UseAlphabeticalSeparators")),
        sUseCombinedEntries(RTL_CONSTASCII_USTRINGPARAM("UseCombinedEntries")),
        sUseDash(RTL_CONSTASCII_USTRINGPARAM("UseDash")),
        sUseKeyAsEntry(RTL_CONSTASCII_USTRINGPARAM("UseKeyAsEntry")),
        sUsePP(RTL_CONSTASCII_USTRINGPARAM("UsePP")),
        sUseUpperCase(RTL_CONSTASCII_USTRINGPARAM("UseUpperCase")),
        sCreateFromOtherEmbeddedObjects(RTL_CONSTASCII_USTRINGPARAM("CreateFromOtherEmbeddedObjects")),
        sCreateFromStarCalc(RTL_CONSTASCII_USTRINGPARAM("CreateFromStarCalc")),
        sCreateFromStarChart(RTL_CONSTASCII_USTRINGPARAM("CreateFromStarChart")),
        sCreateFromStarDraw(RTL_CONSTASCII_USTRINGPARAM("CreateFromStarDraw")),
        sCreateFromStarImage(RTL_CONSTASCII_USTRINGPARAM("CreateFromStarImage")),
        sCreateFromStarMath(RTL_CONSTASCII_USTRINGPARAM("CreateFromStarMath")),
        sCreateFromEmbeddedObjects(RTL_CONSTASCII_USTRINGPARAM("CreateFromEmbeddedObjects")),
        sCreateFromGraphicObjects(RTL_CONSTASCII_USTRINGPARAM("CreateFromGraphicObjects")),
        sCreateFromTables(RTL_CONSTASCII_USTRINGPARAM("CreateFromTables")),
        sCreateFromTextFrames(RTL_CONSTASCII_USTRINGPARAM("CreateFromTextFrames")),
        sUseLevelFromSource(RTL_CONSTASCII_USTRINGPARAM("UseLevelFromSource")),
        sIsCommaSeparated(RTL_CONSTASCII_USTRINGPARAM("IsCommaSeparated")),
        sIsAutomaticUpdate(RTL_CONSTASCII_USTRINGPARAM("IsAutomaticUpdate")),
        sIsRelativeTabstops(RTL_CONSTASCII_USTRINGPARAM("IsRelativeTabstops")),
        sCreateFromLevelParagraphStyles(
            RTL_CONSTASCII_USTRINGPARAM("CreateFromLevelParagraphStyles")),
        sDocumentIndex(RTL_CONSTASCII_USTRINGPARAM("DocumentIndex")),
        sContentSection(RTL_CONSTASCII_USTRINGPARAM("ContentSection")),
        sHeaderSection(RTL_CONSTASCII_USTRINGPARAM("HeaderSection")),
        sTextSection(RTL_CONSTASCII_USTRINGPARAM("TextSection")),
        sIsGlobalDocumentSection(RTL_CONSTASCII_USTRINGPARAM("IsGlobalDocumentSection")),
        sProtectionKey(RTL_CONSTASCII_USTRINGPARAM("ProtectionKey")),
        sSortAlgorithm(RTL_CONSTASCII_USTRINGPARAM("SortAlgorithm")),
        sLocale(RTL_CONSTASCII_USTRINGPARAM("Locale")),
        sUserIndexName(RTL_CONSTASCII_USTRINGPARAM("UserIndexName")),
        sIsCurrentlyVisible(RTL_CONSTASCII_USTRINGPARAM("IsCurrentlyVisible")),
        sHeadingStyleName(RTL_CONSTASCII_USTRINGPARAM("HeadingStyleName")),
        sEmpty(),
        bHeadingDummiesExported( sal_False )
{
}

void XMLSectionExport::ExportSectionStart(
    const Reference<XTextSection> & rSection,
    sal_Bool bAutoStyles)
{
    Reference<XPropertySet> xPropertySet(rSection, UNO_QUERY);

    // always export section (auto) style
    if (bAutoStyles)
    {
        // get PropertySet and add section style
        GetParaExport().Add( XML_STYLE_FAMILY_TEXT_SECTION, xPropertySet );
    }
    else
    {
        // always export section style
        GetExport().AddAttribute(XML_NAMESPACE_TEXT, XML_STYLE_NAME,
                                 GetParaExport().Find(
                                     XML_STYLE_FAMILY_TEXT_SECTION,
                                     xPropertySet, sEmpty ));

        // export index or regular section
        Reference<XDocumentIndex> xIndex;
        if (GetIndex(rSection, xIndex))
        {
            if (xIndex.is())
            {
                // we are an index
                ExportIndexStart(xIndex);
            }
            else
            {
                // we are an index header
                ExportIndexHeaderStart(rSection);
            }
        }
        else
        {
            // we are not an index
            ExportRegularSectionStart(rSection);
        }
    }
}

sal_Bool XMLSectionExport::GetIndex(
    const Reference<XTextSection> & rSection,
    Reference<XDocumentIndex> & rIndex) const
{
    // first, reset result
    sal_Bool bRet = sal_False;
    rIndex = NULL;

    // get section Properties
    Reference<XPropertySet> xSectionPropSet(rSection, UNO_QUERY);

    // then check if this section happens to be inside an index
    if (xSectionPropSet->getPropertySetInfo()->
                                    hasPropertyByName(sDocumentIndex))
    {
        Any aAny = xSectionPropSet->getPropertyValue(sDocumentIndex);
        Reference<XDocumentIndex> xDocumentIndex;
        aAny >>= xDocumentIndex;

        // OK, are we inside of an index
        if (xDocumentIndex.is())
        {
            // is the enclosing index identical with "our" section?
            Reference<XPropertySet> xIndexPropSet(xDocumentIndex, UNO_QUERY);
            aAny = xIndexPropSet->getPropertyValue(sContentSection);
            Reference<XTextSection> xEnclosingSection;
            aAny >>= xEnclosingSection;

            // if the enclosing section is "our" section, then we are an index!
            if (rSection == xEnclosingSection)
            {
                rIndex = xDocumentIndex;
                bRet = sal_True;
            }
            // else: index header or regular section

            // is the enclosing index identical with the header section?
            aAny = xIndexPropSet->getPropertyValue(sHeaderSection);
            // now mis-named: contains header section
            aAny >>= xEnclosingSection;

            // if the enclosing section is "our" section, then we are an index!
            if (rSection == xEnclosingSection)
            {
                bRet = sal_True;
            }
            // else: regular section
        }
        // else: we aren't even inside of an index
    }
    // else: we don't even know what an index is.

    return bRet;
}


void XMLSectionExport::ExportSectionEnd(
    const Reference<XTextSection> & rSection,
    sal_Bool bAutoStyles)
{
    // no end section for styles
    if (!bAutoStyles)
    {
        enum XMLTokenEnum eElement = XML_TOKEN_INVALID;

        // export index or regular section end
        Reference<XDocumentIndex> xIndex;
        if (GetIndex(rSection, xIndex))
        {
            if (xIndex.is())
            {
                // index end: close index body element
                GetExport().EndElement( XML_NAMESPACE_TEXT, XML_INDEX_BODY,
                                        sal_True );
                GetExport().IgnorableWhitespace();

                switch (MapSectionType(xIndex->getServiceName()))
                {
                    case TEXT_SECTION_TYPE_TOC:
                        eElement = XML_TABLE_OF_CONTENT;
                        break;

                    case TEXT_SECTION_TYPE_ILLUSTRATION:
                        eElement = XML_ILLUSTRATION_INDEX;
                        break;

                    case TEXT_SECTION_TYPE_ALPHABETICAL:
                        eElement = XML_ALPHABETICAL_INDEX;
                        break;

                    case TEXT_SECTION_TYPE_TABLE:
                        eElement = XML_TABLE_INDEX;
                        break;

                    case TEXT_SECTION_TYPE_OBJECT:
                        eElement = XML_OBJECT_INDEX;
                        break;

                    case TEXT_SECTION_TYPE_USER:
                        eElement = XML_USER_INDEX;
                        break;

                    case TEXT_SECTION_TYPE_BIBLIOGRAPHY:
                        eElement = XML_BIBLIOGRAPHY;
                        break;

                    default:
                        DBG_ERROR("unknown index type");
                        // default: skip index!
                        break;
                }
            }
            else
            {
                eElement = XML_INDEX_TITLE;
            }
        }
        else
        {
            eElement = XML_SECTION;
        }

        if (XML_TOKEN_INVALID != eElement)
        {
            // any old attributes?
            GetExport().CheckAttrList();

            // element surrounded by whitespace
            GetExport().EndElement( XML_NAMESPACE_TEXT, eElement, sal_True);
            GetExport().IgnorableWhitespace();
        }
        else
        {
            DBG_ERROR("Need element name!");
        }
    }
    // else: autostyles -> ignore
}

void XMLSectionExport::ExportIndexStart(
    const Reference<XDocumentIndex> & rIndex)
{
    // get PropertySet
    Reference<XPropertySet> xPropertySet(rIndex, UNO_QUERY);

    switch (MapSectionType(rIndex->getServiceName()))
    {
        case TEXT_SECTION_TYPE_TOC:
            ExportTableOfContentStart(xPropertySet);
            break;

        case TEXT_SECTION_TYPE_ILLUSTRATION:
            ExportIllustrationIndexStart(xPropertySet);
            break;

        case TEXT_SECTION_TYPE_ALPHABETICAL:
            ExportAlphabeticalIndexStart(xPropertySet);
            break;

        case TEXT_SECTION_TYPE_TABLE:
            ExportTableIndexStart(xPropertySet);
            break;

        case TEXT_SECTION_TYPE_OBJECT:
            ExportObjectIndexStart(xPropertySet);
            break;

        case TEXT_SECTION_TYPE_USER:
            ExportUserIndexStart(xPropertySet);
            break;

        case TEXT_SECTION_TYPE_BIBLIOGRAPHY:
            ExportBibliographyStart(xPropertySet);
            break;

        default:
            // skip index
            DBG_ERROR("unknown index type");
            break;
    }
}

void XMLSectionExport::ExportIndexHeaderStart(
    const Reference<XTextSection> & rSection)
{
    // export name, dammit!
    Reference<XNamed> xName(rSection, UNO_QUERY);
    GetExport().AddAttribute(XML_NAMESPACE_TEXT, XML_NAME, xName->getName());

    // format already handled -> export only start element
    GetExport().StartElement( XML_NAMESPACE_TEXT, XML_INDEX_TITLE, sal_True );
    GetExport().IgnorableWhitespace();
}


SvXMLEnumStringMapEntry __READONLY_DATA aIndexTypeMap[] =
{
    ENUM_STRING_MAP_ENTRY( "com.sun.star.text.ContentIndex", TEXT_SECTION_TYPE_TOC ),
    ENUM_STRING_MAP_ENTRY( "com.sun.star.text.DocumentIndex", TEXT_SECTION_TYPE_ALPHABETICAL ),
    ENUM_STRING_MAP_ENTRY( "com.sun.star.text.TableIndex", TEXT_SECTION_TYPE_TABLE ),
    ENUM_STRING_MAP_ENTRY( "com.sun.star.text.ObjectIndex", TEXT_SECTION_TYPE_OBJECT ),
    ENUM_STRING_MAP_ENTRY( "com.sun.star.text.Bibliography", TEXT_SECTION_TYPE_BIBLIOGRAPHY ),
    ENUM_STRING_MAP_ENTRY( "com.sun.star.text.UserIndex", TEXT_SECTION_TYPE_USER ),
    ENUM_STRING_MAP_ENTRY( "com.sun.star.text.IllustrationsIndex", TEXT_SECTION_TYPE_ILLUSTRATION ),
    ENUM_STRING_MAP_END()
};

enum SectionTypeEnum XMLSectionExport::MapSectionType(
    const OUString& rServiceName)
{
    enum SectionTypeEnum eType = TEXT_SECTION_TYPE_UNKNOWN;

    sal_uInt16 nTmp;
    if (SvXMLUnitConverter::convertEnum(nTmp, rServiceName, aIndexTypeMap))
    {
        eType = (enum SectionTypeEnum)nTmp;
    }

    // TODO: index header section types, etc.

    return eType;
}

void XMLSectionExport::ExportRegularSectionStart(
    const Reference<XTextSection> & rSection)
{
    // style name already handled in ExportSectionStart(...)

    Reference<XNamed> xName(rSection, UNO_QUERY);
    GetExport().AddAttribute(XML_NAMESPACE_TEXT, XML_NAME, xName->getName());

    // get XPropertySet for other values
    Reference<XPropertySet> xPropSet(rSection, UNO_QUERY);
    Any aAny;

    // condition and display
    aAny = xPropSet->getPropertyValue(sCondition);
    OUString sCond;
    aAny >>= sCond;
    enum XMLTokenEnum eDisplay = XML_TOKEN_INVALID;
    if (sCond.getLength() > 0)
    {
        GetExport().AddAttribute(XML_NAMESPACE_TEXT, XML_CONDITION, sCond);
        eDisplay = XML_CONDITION;

        // #97450# store hidden-status (of conditional sections only)
        aAny = xPropSet->getPropertyValue(sIsCurrentlyVisible);
        if (! *(sal_Bool*)aAny.getValue())
        {
            GetExport().AddAttribute(XML_NAMESPACE_TEXT, XML_IS_HIDDEN,
                                     XML_TRUE);
        }
    }
    else
    {
        eDisplay = XML_NONE;
    }
    aAny = xPropSet->getPropertyValue(sIsVisible);
    if (! *(sal_Bool*)aAny.getValue())
    {
        GetExport().AddAttribute(XML_NAMESPACE_TEXT, XML_DISPLAY, eDisplay);
    }

    // protect + protection key
    aAny = xPropSet->getPropertyValue(sIsProtected);
    if (*(sal_Bool*)aAny.getValue())
    {
        GetExport().AddAttribute(XML_NAMESPACE_TEXT, XML_PROTECTED, XML_TRUE);
    }
    Sequence<sal_Int8> aPassword;
    xPropSet->getPropertyValue(sProtectionKey) >>= aPassword;
    if (aPassword.getLength() > 0)
    {
        OUStringBuffer aBuffer;
        SvXMLUnitConverter::encodeBase64(aBuffer, aPassword);
        GetExport().AddAttribute(XML_NAMESPACE_TEXT, XML_PROTECTION_KEY,
                                 aBuffer.makeStringAndClear());
    }

    // export element
    GetExport().IgnorableWhitespace();
    GetExport().StartElement( XML_NAMESPACE_TEXT, XML_SECTION, sal_True );

    // data source
    // unfortunately, we have to test all relevant strings for non-zero length
    aAny = xPropSet->getPropertyValue(sFileLink);
    SectionFileLink aFileLink;
    aAny >>= aFileLink;

    aAny = xPropSet->getPropertyValue(sLinkRegion);
    OUString sRegionName;
    aAny >>= sRegionName;

    if ( (aFileLink.FileURL.getLength() > 0) ||
         (aFileLink.FilterName.getLength() > 0) ||
         (sRegionName.getLength() > 0) )
    {
        if (aFileLink.FileURL.getLength() > 0)
        {
            GetExport().AddAttribute(XML_NAMESPACE_XLINK, XML_HREF,
                                     GetExport().GetRelativeReference( aFileLink.FileURL) );
        }

        if (aFileLink.FilterName.getLength() > 0)
        {
            GetExport().AddAttribute(XML_NAMESPACE_TEXT, XML_FILTER_NAME,
                                     aFileLink.FilterName);
        }

        if (sRegionName.getLength() > 0)
        {
            GetExport().AddAttribute(XML_NAMESPACE_TEXT, XML_SECTION_NAME,
                                     sRegionName);
        }

        SvXMLElementExport aElem(GetExport(),
                                 XML_NAMESPACE_TEXT, XML_SECTION_SOURCE,
                                 sal_True, sal_True);
    }
    else
    {
        // check for DDE first
        if (xPropSet->getPropertySetInfo()->hasPropertyByName(sDdeCommandFile))
        {
            // data source DDE
            // unfortunately, we have to test all relevant strings for
            // non-zero length
            aAny = xPropSet->getPropertyValue(sDdeCommandFile);
            OUString sApplication;
            aAny >>= sApplication;
            aAny = xPropSet->getPropertyValue(sDdeCommandType);
            OUString sTopic;
            aAny >>= sTopic;
            aAny = xPropSet->getPropertyValue(sDdeCommandElement);
            OUString sItem;
            aAny >>= sItem;

            if ( (sApplication.getLength() > 0) ||
                 (sTopic.getLength() > 0) ||
                 (sItem.getLength() > 0 )   )
            {
                GetExport().AddAttribute(XML_NAMESPACE_OFFICE,
                                         XML_DDE_APPLICATION, sApplication);
                GetExport().AddAttribute(XML_NAMESPACE_OFFICE, XML_DDE_TOPIC,
                                         sTopic);
                GetExport().AddAttribute(XML_NAMESPACE_OFFICE, XML_DDE_ITEM,
                                         sItem);

                aAny = xPropSet->getPropertyValue(sIsAutomaticUpdate);
                if (*(sal_Bool*)aAny.getValue())
                {
                    GetExport().AddAttribute(XML_NAMESPACE_OFFICE,
                                             XML_AUTOMATIC_UPDATE, XML_TRUE);
                }

                SvXMLElementExport aElem(GetExport(),
                                         XML_NAMESPACE_OFFICE,
                                         XML_DDE_SOURCE, sal_True, sal_True);
            }
            // else: no DDE data source
        }
        // else: no DDE on this system
    }
}

void XMLSectionExport::ExportTableOfContentStart(
    const Reference<XPropertySet> & rPropertySet)
{
    // export TOC element start
    ExportBaseIndexStart(XML_TABLE_OF_CONTENT, rPropertySet);

    // scope for table-of-content-source element
    {

        Any aAny;

        // TOC specific index source attributes:

        // outline-level: 1..10
        sal_Int16 nLevel;
        if( rPropertySet->getPropertyValue(sLevel) >>= nLevel )
        {
            OUStringBuffer sBuffer;
            SvXMLUnitConverter::convertNumber(sBuffer, (sal_Int32)nLevel);
            GetExport().AddAttribute(XML_NAMESPACE_TEXT,
                                     XML_OUTLINE_LEVEL,
                                     sBuffer.makeStringAndClear());
        }

        // use outline level
        ExportBoolean(rPropertySet, sCreateFromOutline,
                          XML_USE_OUTLINE_LEVEL, sal_True);

        // use index marks
        ExportBoolean(rPropertySet, sCreateFromMarks,
                      XML_USE_INDEX_MARKS, sal_True);

        // use level styles
        ExportBoolean(rPropertySet, sCreateFromLevelParagraphStyles,
                      XML_USE_INDEX_SOURCE_STYLES, sal_False);

        ExportBaseIndexSource(TEXT_SECTION_TYPE_TOC, rPropertySet);
    }

    ExportBaseIndexBody(TEXT_SECTION_TYPE_TOC, rPropertySet);
}

void XMLSectionExport::ExportObjectIndexStart(
    const Reference<XPropertySet> & rPropertySet)
{
    // export index start
    ExportBaseIndexStart(XML_OBJECT_INDEX, rPropertySet);

    // scope for index source element
    {
        ExportBoolean(rPropertySet, sCreateFromOtherEmbeddedObjects,
                      XML_USE_OTHER_OBJECTS, sal_False);
        ExportBoolean(rPropertySet, sCreateFromStarCalc,
                      XML_USE_SPREADSHEET_OBJECTS, sal_False);
        ExportBoolean(rPropertySet, sCreateFromStarChart,
                      XML_USE_CHART_OBJECTS, sal_False);
        ExportBoolean(rPropertySet, sCreateFromStarDraw,
                      XML_USE_DRAW_OBJECTS, sal_False);
        ExportBoolean(rPropertySet, sCreateFromStarMath,
                      XML_USE_MATH_OBJECTS, sal_False);

        ExportBaseIndexSource(TEXT_SECTION_TYPE_OBJECT, rPropertySet);
    }

    ExportBaseIndexBody(TEXT_SECTION_TYPE_OBJECT, rPropertySet);
}

void XMLSectionExport::ExportIllustrationIndexStart(
    const Reference<XPropertySet> & rPropertySet)
{
    // export index start
    ExportBaseIndexStart(XML_ILLUSTRATION_INDEX, rPropertySet);

    // scope for index source element
    {
        // export common attributes for illustration and table indices
        ExportTableAndIllustrationIndexSourceAttributes(rPropertySet);

        ExportBaseIndexSource(TEXT_SECTION_TYPE_ILLUSTRATION, rPropertySet);
    }

    ExportBaseIndexBody(TEXT_SECTION_TYPE_ILLUSTRATION, rPropertySet);
}

void XMLSectionExport::ExportTableIndexStart(
    const Reference<XPropertySet> & rPropertySet)
{
    // export index start
    ExportBaseIndexStart(XML_TABLE_INDEX, rPropertySet);

    // scope for index source element
    {
        // export common attributes for illustration and table indices
        ExportTableAndIllustrationIndexSourceAttributes(rPropertySet);

        ExportBaseIndexSource(TEXT_SECTION_TYPE_TABLE, rPropertySet);
    }

    ExportBaseIndexBody(TEXT_SECTION_TYPE_TABLE, rPropertySet);
}

void XMLSectionExport::ExportAlphabeticalIndexStart(
    const Reference<XPropertySet> & rPropertySet)
{
    // export TOC element start
    ExportBaseIndexStart(XML_ALPHABETICAL_INDEX, rPropertySet);

    // scope for table-of-content-source element
    {

        // style name (if present)
        Any aAny;
        aAny = rPropertySet->getPropertyValue(sMainEntryCharacterStyleName);
        OUString sStyleName;
        aAny >>= sStyleName;
        if (sStyleName.getLength())
        {
            GetExport().AddAttribute(XML_NAMESPACE_TEXT,
                                     XML_MAIN_ENTRY_STYLE_NAME,
                                     sStyleName);
        }

        // other (boolean) attributes
        ExportBoolean(rPropertySet, sIsCaseSensitive, XML_IGNORE_CASE,
                      sal_False, sal_True);
        ExportBoolean(rPropertySet, sUseAlphabeticalSeparators,
                      XML_ALPHABETICAL_SEPARATORS, sal_False);
        ExportBoolean(rPropertySet, sUseCombinedEntries, XML_COMBINE_ENTRIES,
                      sal_True);
        ExportBoolean(rPropertySet, sUseDash, XML_COMBINE_ENTRIES_WITH_DASH,
                      sal_False);
        ExportBoolean(rPropertySet, sUseKeyAsEntry, XML_USE_KEYS_AS_ENTRIES,
                      sal_False);
        ExportBoolean(rPropertySet, sUsePP, XML_COMBINE_ENTRIES_WITH_PP,
                      sal_True);
        ExportBoolean(rPropertySet, sUseUpperCase, XML_CAPITALIZE_ENTRIES,
                      sal_False);
        ExportBoolean(rPropertySet, sIsCommaSeparated, XML_COMMA_SEPARATED,
                      sal_False);

        // sort algorithm
        aAny = rPropertySet->getPropertyValue(sSortAlgorithm);
        OUString sAlgorithm;
        aAny >>= sAlgorithm;
        if (sAlgorithm.getLength() > 0)
        {
            GetExport().AddAttribute( XML_NAMESPACE_TEXT, XML_SORT_ALGORITHM,
                                      sAlgorithm );
        }

        // locale
        aAny = rPropertySet->getPropertyValue(sLocale);
        Locale aLocale;
        aAny >>= aLocale;
        GetExport().AddAttribute(XML_NAMESPACE_FO, XML_LANGUAGE,
                                 aLocale.Language);
        GetExport().AddAttribute(XML_NAMESPACE_FO, XML_COUNTRY,
                                 aLocale.Country);

        ExportBaseIndexSource(TEXT_SECTION_TYPE_ALPHABETICAL, rPropertySet);
    }

    ExportBaseIndexBody(TEXT_SECTION_TYPE_ALPHABETICAL, rPropertySet);
}

void XMLSectionExport::ExportUserIndexStart(
    const Reference<XPropertySet> & rPropertySet)
{
    // export TOC element start
    ExportBaseIndexStart(XML_USER_INDEX, rPropertySet);

    // scope for table-of-content-source element
    {
        // bool attributes
        ExportBoolean(rPropertySet, sCreateFromEmbeddedObjects,
                      XML_USE_OBJECTS, sal_False);
        ExportBoolean(rPropertySet, sCreateFromGraphicObjects,
                      XML_USE_GRAPHICS, sal_False);
        ExportBoolean(rPropertySet, sCreateFromMarks,
                      XML_USE_INDEX_MARKS, sal_False);
        ExportBoolean(rPropertySet, sCreateFromTables,
                      XML_USE_TABLES, sal_False);
        ExportBoolean(rPropertySet, sCreateFromTextFrames,
                      XML_USE_FLOATING_FRAMES, sal_False);
        ExportBoolean(rPropertySet, sUseLevelFromSource,
                      XML_COPY_OUTLINE_LEVELS, sal_False);
        ExportBoolean(rPropertySet, sCreateFromLevelParagraphStyles,
                      XML_USE_INDEX_SOURCE_STYLES, sal_False);

        Any aAny = rPropertySet->getPropertyValue( sUserIndexName );
        OUString sIndexName;
        aAny >>= sIndexName;
        GetExport().AddAttribute(XML_NAMESPACE_TEXT, XML_INDEX_NAME,
                                 sIndexName);

        ExportBaseIndexSource(TEXT_SECTION_TYPE_USER, rPropertySet);
    }

    ExportBaseIndexBody(TEXT_SECTION_TYPE_USER, rPropertySet);
}

void XMLSectionExport::ExportBibliographyStart(
    const Reference<XPropertySet> & rPropertySet)
{
    // export TOC element start
    ExportBaseIndexStart(XML_BIBLIOGRAPHY, rPropertySet);

    // scope for table-of-content-source element
    {
        // No attributes. Fine.

        ExportBaseIndexSource(TEXT_SECTION_TYPE_BIBLIOGRAPHY, rPropertySet);
    }

    ExportBaseIndexBody(TEXT_SECTION_TYPE_BIBLIOGRAPHY, rPropertySet);
}


void XMLSectionExport::ExportBaseIndexStart(
    XMLTokenEnum eElement,
    const Reference<XPropertySet> & rPropertySet)
{
    // protect + protection key
    Any aAny = rPropertySet->getPropertyValue(sIsProtected);
    if (*(sal_Bool*)aAny.getValue())
    {
        GetExport().AddAttribute(XML_NAMESPACE_TEXT, XML_PROTECTED, XML_TRUE);
    }

    // index name
    OUString sIndexName;
    rPropertySet->getPropertyValue(sName) >>= sIndexName;
    if ( sIndexName.getLength() > 0 )
    {
        GetExport().AddAttribute(XML_NAMESPACE_TEXT, XML_NAME, sIndexName);
    }

    // index  Element start
    GetExport().IgnorableWhitespace();
    GetExport().StartElement( XML_NAMESPACE_TEXT, eElement, sal_False );
}

static const sal_Char* aTypeSourceElementNameMap[] =
{
    sXML_table_of_content_source,       // TOC
    sXML_table_index_source,            // table index
    sXML_illustration_index_source,     // illustration index
    sXML_object_index_source,           // object index
    sXML_user_index_source,             // user index
    sXML_alphabetical_index_source,     // alphabetical index
    sXML_bibliography_source            // bibliography
};

void XMLSectionExport::ExportBaseIndexSource(
    SectionTypeEnum eType,
    const Reference<XPropertySet> & rPropertySet)
{
    // check type
    DBG_ASSERT(eType >= TEXT_SECTION_TYPE_TOC, "illegal index type");
    DBG_ASSERT(eType <= TEXT_SECTION_TYPE_BIBLIOGRAPHY, "illegal index type");

    Any aAny;

    // common attributes; not supported by bibliography
    if (eType != TEXT_SECTION_TYPE_BIBLIOGRAPHY)
    {
        // document or chapter index?
        aAny = rPropertySet->getPropertyValue(sCreateFromChapter);
        if (*(sal_Bool*)aAny.getValue())
        {
            GetExport().AddAttribute(XML_NAMESPACE_TEXT,
                                     XML_INDEX_SCOPE, XML_CHAPTER);
        }

        // tab-stops relative to margin?
        aAny = rPropertySet->getPropertyValue(sIsRelativeTabstops);
        if (! *(sal_Bool*)aAny.getValue())
        {
            GetExport().AddAttribute(XML_NAMESPACE_TEXT,
                                     XML_RELATIVE_TAB_STOP_POSITION,
                                     XML_FALSE);
        }
    }

    // the index source element (all indices)
    SvXMLElementExport aElem(GetExport(),
                             XML_NAMESPACE_TEXT,
                             aTypeSourceElementNameMap[
                                 eType - TEXT_SECTION_TYPE_TOC],
                             sal_True, sal_True);

    // scope for title template (all indices)
    {
        // header style name
        aAny = rPropertySet->getPropertyValue(sParaStyleHeading);
        OUString sStyleName;
        aAny >>= sStyleName;
        GetExport().AddAttribute(XML_NAMESPACE_TEXT,
                                 XML_STYLE_NAME,
                                 sStyleName);

        // title template
        SvXMLElementExport aHeaderTemplate(GetExport(),
                                           XML_NAMESPACE_TEXT,
                                           XML_INDEX_TITLE_TEMPLATE,
                                           sal_True, sal_False);

        // title as element content
        aAny = rPropertySet->getPropertyValue(sTitle);
        OUString sTitleString;
        aAny >>= sTitleString;
        GetExport().Characters(sTitleString);
    }

    // export level templates (all indices)
    aAny = rPropertySet->getPropertyValue(sLevelFormat);
    Reference<XIndexReplace> xLevelTemplates;
    aAny >>= xLevelTemplates;

    // iterate over level formats;
    // skip element 0 (empty template for title)
    sal_Int32 nLevelCount = xLevelTemplates->getCount();
    for(sal_Int32 i = 1; i<nLevelCount; i++)
    {
        // get sequence
        Sequence<PropertyValues> aTemplateSequence;
        aAny = xLevelTemplates->getByIndex(i);
        aAny >>= aTemplateSequence;

        // export the sequence (abort export if an error occured; #91214#)
        sal_Bool bResult =
            ExportIndexTemplate(eType, i, rPropertySet, aTemplateSequence);
        if ( !bResult )
            break;
    }

    // only TOC and user index:
    // styles from which to build the index (LevelParagraphStyles)
    if ( (TEXT_SECTION_TYPE_TOC == eType) ||
         (TEXT_SECTION_TYPE_USER == eType)   )
    {
        aAny = rPropertySet->getPropertyValue(sLevelParagraphStyles);
        Reference<XIndexReplace> xLevelParagraphStyles;
        aAny >>= xLevelParagraphStyles;
        ExportLevelParagraphStyles(xLevelParagraphStyles);
    }
}


void XMLSectionExport::ExportBaseIndexBody(
    SectionTypeEnum eType,
    const Reference<XPropertySet> & rSection)
{
    // type not used; checked anyway.
    DBG_ASSERT(eType >= TEXT_SECTION_TYPE_TOC, "illegal index type");
    DBG_ASSERT(eType <= TEXT_SECTION_TYPE_BIBLIOGRAPHY, "illegal index type");

    // export start only

    // any old attributes?
    GetExport().CheckAttrList();

    // start surrounded by whitespace
    GetExport().IgnorableWhitespace();
    GetExport().StartElement( XML_NAMESPACE_TEXT, XML_INDEX_BODY, sal_True );
}

void XMLSectionExport::ExportTableAndIllustrationIndexSourceAttributes(
    const Reference<XPropertySet> & rPropertySet)
{
    // use caption
    Any aAny = rPropertySet->getPropertyValue(sCreateFromLabels);
    if (! *(sal_Bool*)aAny.getValue())
    {
        GetExport().AddAttribute(XML_NAMESPACE_TEXT,
                                 XML_USE_CAPTION, XML_FALSE);
    }

    // sequence name
    aAny = rPropertySet->getPropertyValue(sLabelCategory);
    OUString sSequenceName;
    aAny >>= sSequenceName;
    GetExport().AddAttribute(XML_NAMESPACE_TEXT,
                             XML_CAPTION_SEQUENCE_NAME,
                             sSequenceName);

    // caption format
    aAny = rPropertySet->getPropertyValue(sLabelDisplayType);
    sal_Int16 nType;
    aAny >>= nType;
    GetExport().AddAttribute(XML_NAMESPACE_TEXT,
                             XML_CAPTION_SEQUENCE_FORMAT,
                             XMLTextFieldExport::MapReferenceType(nType));
}


// map index of LevelFormats to attribute value;
// level 0 is always the header
static const sal_Char* aLevelNameTOCMap[] =
    { NULL, sXML_1, sXML_2, sXML_3, sXML_4, sXML_5, sXML_6, sXML_7,
          sXML_8, sXML_9, sXML_10, NULL };
static const sal_Char* aLevelNameTableMap[] =
    { NULL, "", NULL };
static const sal_Char* aLevelNameAlphaMap[] =
    { NULL, sXML_separator, sXML_1, sXML_2, sXML_3, NULL };
static const sal_Char* aLevelNameBibliographyMap[] =
    { NULL, sXML_article, sXML_book, sXML_booklet, sXML_conference,
          sXML_custom1, sXML_custom2, sXML_custom3, sXML_custom4,
          sXML_custom5, sXML_email, sXML_inbook, sXML_incollection,
          sXML_inproceedings, sXML_journal,
          sXML_manual, sXML_mastersthesis, sXML_misc, sXML_phdthesis,
          sXML_proceedings, sXML_techreport, sXML_unpublished, sXML_www,
          NULL };

static const sal_Char** aTypeLevelNameMap[] =
{
    aLevelNameTOCMap,           // TOC
    aLevelNameTableMap,         // table index
    aLevelNameTableMap,         // illustration index
    aLevelNameTableMap,         // object index
    aLevelNameTOCMap,           // user index
    aLevelNameAlphaMap,         // alphabetical index
    aLevelNameBibliographyMap   // bibliography
};

static const sal_Char* aLevelStylePropNameTOCMap[] =
    { NULL, "ParaStyleLevel1", "ParaStyleLevel2", "ParaStyleLevel3",
          "ParaStyleLevel4", "ParaStyleLevel5", "ParaStyleLevel6",
          "ParaStyleLevel7", "ParaStyleLevel8", "ParaStyleLevel9",
          "ParaStyleLevel10", NULL };
static const sal_Char* aLevelStylePropNameTableMap[] =
    { NULL, "ParaStyleLevel1", NULL };
static const sal_Char* aLevelStylePropNameAlphaMap[] =
    { NULL, "ParaStyleSeparator", "ParaStyleLevel1", "ParaStyleLevel2",
          "ParaStyleLevel3", NULL };
static const sal_Char* aLevelStylePropNameBibliographyMap[] =
          // TODO: replace with real property names, when available
    { NULL, "ParaStyleLevel1", "ParaStyleLevel1", "ParaStyleLevel1",
          "ParaStyleLevel1", "ParaStyleLevel1", "ParaStyleLevel1",
          "ParaStyleLevel1", "ParaStyleLevel1", "ParaStyleLevel1",
          "ParaStyleLevel1", "ParaStyleLevel1", "ParaStyleLevel1",
          "ParaStyleLevel1", "ParaStyleLevel1", "ParaStyleLevel1",
          "ParaStyleLevel1", "ParaStyleLevel1", "ParaStyleLevel1",
          "ParaStyleLevel1", "ParaStyleLevel1", "ParaStyleLevel1",
          "ParaStyleLevel1",
          NULL };

static const sal_Char** aTypeLevelStylePropNameMap[] =
{
    aLevelStylePropNameTOCMap,          // TOC
    aLevelStylePropNameTableMap,        // table index
    aLevelStylePropNameTableMap,        // illustration index
    aLevelStylePropNameTableMap,        // object index
    aLevelStylePropNameTOCMap,          // user index
    aLevelStylePropNameAlphaMap,        // alphabetical index
    aLevelStylePropNameBibliographyMap  // bibliography
};

static const sal_Char* aTypeLevelAttrMap[] =
{
    sXML_outline_level,     // TOC
    NULL,                   // table index
    NULL,                   // illustration index
    NULL,                   // object index
    sXML_outline_level,     // user index
    sXML_outline_level,     // alphabetical index
    sXML_bibliography_type  // bibliography
};

static const sal_Char* aTypeElementNameMap[] =
{
    sXML_table_of_content_entry_template,   // TOC
    sXML_table_index_entry_template,        // table index
    sXML_illustration_index_entry_template, // illustration index
    sXML_object_index_entry_template,       // object index
    sXML_user_index_entry_template,         // user index
    sXML_alphabetical_index_entry_template, // alphabetical index
    sXML_bibliography_entry_template        // bibliography
};


sal_Bool XMLSectionExport::ExportIndexTemplate(
    SectionTypeEnum eType,
    sal_Int32 nOutlineLevel,
    const Reference<XPropertySet> & rPropertySet,
    Sequence<Sequence<PropertyValue> > & rValues)
{
    DBG_ASSERT(eType >= TEXT_SECTION_TYPE_TOC, "illegal index type");
    DBG_ASSERT(eType <= TEXT_SECTION_TYPE_BIBLIOGRAPHY, "illegal index type");
    DBG_ASSERT(nOutlineLevel >= 0, "illegal outline level");

    if ( (eType >= TEXT_SECTION_TYPE_TOC) &&
         (eType <= TEXT_SECTION_TYPE_BIBLIOGRAPHY) &&
         (nOutlineLevel >= 0) )
    {
        // get level name and level attribute name from aLevelNameMap;
        const sal_Char* pLevelAttrName =
            aTypeLevelAttrMap[eType-TEXT_SECTION_TYPE_TOC];
        const sal_Char* pLevelName =
            aTypeLevelNameMap[eType-TEXT_SECTION_TYPE_TOC][nOutlineLevel];

        // #92124#: some old documents may be broken, then they have
        // too many template levels; we need to recognize this and
        // export only as many as is legal for the respective index
        // type. To do this, we simply return an error flag, which
        // will then abort further template level exports.
        DBG_ASSERT(NULL != pLevelName, "can't find level name");
        if ( NULL == pLevelName )
        {
            // output level not found? Then end of templates! #91214#
            return sal_False;
        }

        // output level name
        if ((NULL != pLevelName) && (NULL != pLevelAttrName))
        {
            GetExport().AddAttributeASCII(XML_NAMESPACE_TEXT,
                                          pLevelAttrName,
                                          pLevelName);
        }

        // paragraph level style name
        const sal_Char* pPropName =
            aTypeLevelStylePropNameMap[eType-TEXT_SECTION_TYPE_TOC][nOutlineLevel];
        DBG_ASSERT(NULL != pPropName, "can't find property name");
        if (NULL != pPropName)
        {
            Any aAny = rPropertySet->getPropertyValue(
                OUString::createFromAscii(pPropName));
            OUString sParaStyleName;
            aAny >>= sParaStyleName;
            GetExport().AddAttribute(XML_NAMESPACE_TEXT,
                                     XML_STYLE_NAME,
                                     sParaStyleName);
        }

        // template element
        const sal_Char* pElementName =
            aTypeElementNameMap[eType - TEXT_SECTION_TYPE_TOC];
        SvXMLElementExport aLevelTemplate(GetExport(),
                                          XML_NAMESPACE_TEXT,
                                          pElementName,
                                          sal_True, sal_True);

        // export sequence
        sal_Int32 nTemplateCount = rValues.getLength();
        for(sal_Int32 nTemplateNo = 0;
            nTemplateNo < nTemplateCount;
            nTemplateNo++)
        {
            ExportIndexTemplateElement(
                rValues[nTemplateNo]);
        }
    }

    return sal_True;
}


enum TemplateTypeEnum
{
    TOK_TTYPE_ENTRY_NUMBER,
    TOK_TTYPE_ENTRY_TEXT,
    TOK_TTYPE_TAB_STOP,
    TOK_TTYPE_TEXT,
    TOK_TTYPE_PAGE_NUMBER,
    TOK_TTYPE_CHAPTER_INFO,
    TOK_TTYPE_HYPERLINK_START,
    TOK_TTYPE_HYPERLINK_END,
    TOK_TTYPE_BIBLIOGRAPHY,
    TOK_TTYPE_INVALID
};

enum TemplateParamEnum
{
    TOK_TPARAM_TOKEN_TYPE,
    TOK_TPARAM_CHAR_STYLE,
    TOK_TPARAM_TAB_RIGHT_ALIGNED,
    TOK_TPARAM_TAB_POSITION,
    TOK_TPARAM_TAB_FILL_CHAR,
    TOK_TPARAM_TEXT,
    TOK_TPARAM_CHAPTER_FORMAT,
    TOK_TPARAM_BIBLIOGRAPHY_DATA
};

SvXMLEnumStringMapEntry __READONLY_DATA aTemplateTypeMap[] =
{
    ENUM_STRING_MAP_ENTRY( "TokenEntryNumber",  TOK_TTYPE_ENTRY_NUMBER ),
    ENUM_STRING_MAP_ENTRY( "TokenEntryText",    TOK_TTYPE_ENTRY_TEXT ),
    ENUM_STRING_MAP_ENTRY( "TokenTabStop",      TOK_TTYPE_TAB_STOP ),
    ENUM_STRING_MAP_ENTRY( "TokenText",         TOK_TTYPE_TEXT ),
    ENUM_STRING_MAP_ENTRY( "TokenPageNumber",   TOK_TTYPE_PAGE_NUMBER ),
    ENUM_STRING_MAP_ENTRY( "TokenChapterInfo",  TOK_TTYPE_CHAPTER_INFO ),
    ENUM_STRING_MAP_ENTRY( "TokenHyperlinkStart", TOK_TTYPE_HYPERLINK_START ),
    ENUM_STRING_MAP_ENTRY( "TokenHyperlinkEnd", TOK_TTYPE_HYPERLINK_END ),
    ENUM_STRING_MAP_ENTRY( "TokenBibliographyDataField", TOK_TTYPE_BIBLIOGRAPHY ),
    ENUM_STRING_MAP_END()
};

SvXMLEnumStringMapEntry __READONLY_DATA aTemplateParamMap[] =
{
    ENUM_STRING_MAP_ENTRY( "TokenType",             TOK_TPARAM_TOKEN_TYPE ),
    ENUM_STRING_MAP_ENTRY( "CharacterStyleName",    TOK_TPARAM_CHAR_STYLE ),
    ENUM_STRING_MAP_ENTRY( "TabStopRightAligned",   TOK_TPARAM_TAB_RIGHT_ALIGNED ),
    ENUM_STRING_MAP_ENTRY( "TabStopPosition",       TOK_TPARAM_TAB_POSITION ),
    ENUM_STRING_MAP_ENTRY( "TabStopFillCharacter",  TOK_TPARAM_TAB_FILL_CHAR ),
    ENUM_STRING_MAP_ENTRY( "Text",                  TOK_TPARAM_TEXT ),
    ENUM_STRING_MAP_ENTRY( "ChapterFormat",         TOK_TPARAM_CHAPTER_FORMAT ),
    ENUM_STRING_MAP_ENTRY( "BibliographyDataField", TOK_TPARAM_BIBLIOGRAPHY_DATA ),
    ENUM_STRING_MAP_END()
};

SvXMLEnumMapEntry __READONLY_DATA aBibliographyDataFieldMap[] =
{
    { XML_ADDRESS,              BibliographyDataField::ADDRESS },
    { XML_ANNOTE,               BibliographyDataField::ANNOTE },
    { XML_AUTHOR,               BibliographyDataField::AUTHOR },
    { XML_BIBLIOGRAPHY_TYPE,    BibliographyDataField::BIBILIOGRAPHIC_TYPE },
    { XML_BOOKTITLE,            BibliographyDataField::BOOKTITLE },
    { XML_CHAPTER,              BibliographyDataField::CHAPTER },
    { XML_CUSTOM1,              BibliographyDataField::CUSTOM1 },
    { XML_CUSTOM2,              BibliographyDataField::CUSTOM2 },
    { XML_CUSTOM3,              BibliographyDataField::CUSTOM3 },
    { XML_CUSTOM4,              BibliographyDataField::CUSTOM4 },
    { XML_CUSTOM5,              BibliographyDataField::CUSTOM5 },
    { XML_EDITION,              BibliographyDataField::EDITION },
    { XML_EDITOR,               BibliographyDataField::EDITOR },
    { XML_HOWPUBLISHED,         BibliographyDataField::HOWPUBLISHED },
    { XML_IDENTIFIER,           BibliographyDataField::IDENTIFIER },
    { XML_INSTITUTION,          BibliographyDataField::INSTITUTION },
    { XML_ISBN,                 BibliographyDataField::ISBN },
    { XML_JOURNAL,              BibliographyDataField::JOURNAL },
    { XML_MONTH,                BibliographyDataField::MONTH },
    { XML_NOTE,                 BibliographyDataField::NOTE },
    { XML_NUMBER,               BibliographyDataField::NUMBER },
    { XML_ORGANIZATIONS,        BibliographyDataField::ORGANIZATIONS },
    { XML_PAGES,                BibliographyDataField::PAGES },
    { XML_PUBLISHER,            BibliographyDataField::PUBLISHER },
    { XML_REPORT_TYPE,          BibliographyDataField::REPORT_TYPE },
    { XML_SCHOOL,               BibliographyDataField::SCHOOL },
    { XML_SERIES,               BibliographyDataField::SERIES },
    { XML_TITLE,                BibliographyDataField::TITLE },
    { XML_URL,                  BibliographyDataField::URL },
    { XML_VOLUME,               BibliographyDataField::VOLUME },
    { XML_YEAR,                 BibliographyDataField::YEAR },
    { XML_TOKEN_INVALID, 0 }
};

void XMLSectionExport::ExportIndexTemplateElement(
    Sequence<PropertyValue> & rValues)
{
    // variables for template values

    // char style
    OUString sCharStyle;
    sal_Bool bCharStyleOK = sal_False;

    // text
    OUString sText;
    sal_Bool bTextOK = sal_False;

    // tab position
    sal_Bool bRightAligned = sal_False;
    sal_Bool bRightAlignedOK = sal_False;

    // tab position
    sal_Int32 nTabPosition = 0;
    sal_Bool bTabPositionOK = sal_False;

    // fill character
    OUString sFillChar;
    sal_Bool bFillCharOK = sal_False;

    // chapter format
    sal_Int16 nChapterFormat = 0;
    sal_Bool bChapterFormatOK = sal_False;

    // Bibliography Data
    sal_Int16 nBibliographyData = 0;
    sal_Bool bBibliographyDataOK = sal_False;


    // token type
    enum TemplateTypeEnum nTokenType = TOK_TTYPE_INVALID;

    sal_Int32 nCount = rValues.getLength();
    for(sal_Int32 i = 0; i<nCount; i++)
    {
        sal_uInt16 nToken;
        if ( SvXMLUnitConverter::convertEnum( nToken, rValues[i].Name,
                                              aTemplateParamMap ) )
        {
            // Only use direct and default values.
            // Wrong. no property states, so ignore.
            // if ( (beans::PropertyState_DIRECT_VALUE == rValues[i].State) ||
            //      (beans::PropertyState_DEFAULT_VALUE == rValues[i].State)  )

            switch (nToken)
            {
                case TOK_TPARAM_TOKEN_TYPE:
                {
                    sal_uInt16 nTmp;
                    OUString sVal;
                    rValues[i].Value >>= sVal;
                    if (SvXMLUnitConverter::convertEnum( nTmp, sVal,
                                                         aTemplateTypeMap))
                    {
                        nTokenType = (enum TemplateTypeEnum)nTmp;
                    }
                    break;
                }

                case TOK_TPARAM_CHAR_STYLE:
                    // only valid, if not empty
                    rValues[i].Value >>= sCharStyle;
                    bCharStyleOK = sCharStyle.getLength() > 0;
                    break;

                case TOK_TPARAM_TEXT:
                    rValues[i].Value >>= sText;
                    bTextOK = sal_True;
                    break;

                case TOK_TPARAM_TAB_RIGHT_ALIGNED:
                    bRightAligned =
                        *(sal_Bool *)rValues[i].Value.getValue();
                    bRightAlignedOK = sal_True;
                    break;

                case TOK_TPARAM_TAB_POSITION:
                    rValues[i].Value >>= nTabPosition;
                    bTabPositionOK = sal_True;
                    break;

                case TOK_TPARAM_TAB_FILL_CHAR:
                    rValues[i].Value >>= sFillChar;
                    bFillCharOK = sal_True;
                    break;

                case TOK_TPARAM_CHAPTER_FORMAT:
                    rValues[i].Value >>= nChapterFormat;
                    bChapterFormatOK = sal_True;
                    break;
                case TOK_TPARAM_BIBLIOGRAPHY_DATA:
                    rValues[i].Value >>= nBibliographyData;
                    bBibliographyDataOK = sal_True;
                    break;
            }
        }
    }

    // convert type to token (and check validity) ...
    sal_Char* pElement = NULL;
    switch(nTokenType)
    {
        case TOK_TTYPE_ENTRY_TEXT:
            pElement = sXML_index_entry_text;
            break;
        case TOK_TTYPE_TAB_STOP:
            // test validity
            pElement = ( bRightAligned || bTabPositionOK || bFillCharOK )
                ? sXML_index_entry_tab_stop : NULL;
            break;
        case TOK_TTYPE_TEXT:
            // test validity
            pElement = bTextOK ? sXML_index_entry_span : NULL;
            break;
        case TOK_TTYPE_PAGE_NUMBER:
            pElement = sXML_index_entry_page_number;
            break;
        case TOK_TTYPE_CHAPTER_INFO:    // keyword index
            pElement = sXML_index_entry_chapter;
            break;
        case TOK_TTYPE_ENTRY_NUMBER:    // table of content
            pElement = sXML_index_entry_chapter_number;
            break;
        case TOK_TTYPE_HYPERLINK_START:
            pElement = sXML_index_entry_link_start;
            break;
        case TOK_TTYPE_HYPERLINK_END:
            pElement = sXML_index_entry_link_end;
            break;
        case TOK_TTYPE_BIBLIOGRAPHY:
            pElement = bBibliographyDataOK
                ? sXML_index_entry_bibliography : NULL;
            break;
        default:
            ; // unknown/unimplemented template
            break;
    }

    // ... and write Element
    if (pElement != NULL)
    {
        // character style (for most templates)
        if (bCharStyleOK)
        {
            switch (nTokenType)
            {
                case TOK_TTYPE_ENTRY_TEXT:
                case TOK_TTYPE_TEXT:
                case TOK_TTYPE_PAGE_NUMBER:
                case TOK_TTYPE_ENTRY_NUMBER:
                case TOK_TTYPE_HYPERLINK_START:
                case TOK_TTYPE_HYPERLINK_END:
                case TOK_TTYPE_BIBLIOGRAPHY:
                case TOK_TTYPE_CHAPTER_INFO:
                case TOK_TTYPE_TAB_STOP:
                    GetExport().AddAttribute(XML_NAMESPACE_TEXT,
                                             XML_STYLE_NAME, sCharStyle);
                    break;
                default:
                    ; // nothing: no character style
                    break;
            }
        }

        // tab properties
        if (TOK_TTYPE_TAB_STOP == nTokenType)
        {
            // tab type
            GetExport().AddAttribute(XML_NAMESPACE_STYLE, XML_TYPE,
                                     bRightAligned ? XML_RIGHT : XML_LEFT);

            if (bTabPositionOK && (! bRightAligned))
            {
                // position for left tabs (convert to measure)
                OUStringBuffer sBuf;
                GetExport().GetMM100UnitConverter().convertMeasure(sBuf,
                                                                 nTabPosition);
                GetExport().AddAttribute(XML_NAMESPACE_STYLE,
                                         XML_POSITION,
                                         sBuf.makeStringAndClear());
            }

            // fill char ("leader char")
            if (bFillCharOK && (sFillChar.getLength() > 0))
            {
                GetExport().AddAttribute(XML_NAMESPACE_STYLE,
                                         XML_LEADER_CHAR, sFillChar);
            }
        }

        // bibliography data
        if (TOK_TTYPE_BIBLIOGRAPHY == nTokenType)
        {
            DBG_ASSERT(bBibliographyDataOK, "need bibl data");
            OUStringBuffer sBuf;
            if (SvXMLUnitConverter::convertEnum( sBuf, nBibliographyData,
                                                 aBibliographyDataFieldMap ) )
            {
                GetExport().AddAttribute(XML_NAMESPACE_TEXT,
                                         XML_BIBLIOGRAPHY_DATA_FIELD,
                                         sBuf.makeStringAndClear());
            }
        }

        // chapter info
        if (TOK_TTYPE_CHAPTER_INFO == nTokenType)
        {
            DBG_ASSERT(bChapterFormatOK, "need chapter info");
            GetExport().AddAttribute(
                XML_NAMESPACE_TEXT, XML_DISPLAY,
                XMLTextFieldExport::MapChapterDisplayFormat(nChapterFormat));
        }

        // export template
        SvXMLElementExport aTemplateElement(GetExport(), XML_NAMESPACE_TEXT,
                                            pElement, sal_True, sal_False);

        // entry text or span element: write text
        if (TOK_TTYPE_TEXT == nTokenType)
        {
            GetExport().Characters(sText);
        }
    }
}

void XMLSectionExport::ExportLevelParagraphStyles(
    Reference<XIndexReplace> & xLevelParagraphStyles)
{
    // iterate over levels
    sal_Int32 nPLevelCount = xLevelParagraphStyles->getCount();
    for(sal_Int32 nLevel = 0; nLevel < nPLevelCount; nLevel++)
    {
        Any aAny = xLevelParagraphStyles->getByIndex(nLevel);
        Sequence<OUString> aStyleNames;
        aAny >>= aStyleNames;

        // export only if at least one style is contained
        sal_Int32 nNamesCount = aStyleNames.getLength();
        if (nNamesCount > 0)
        {
            // level attribute; we count 1..10; API 0..9
            OUStringBuffer sBuf;
            sal_Int32 nLevelPlusOne = nLevel + 1;
            SvXMLUnitConverter::convertNumber(sBuf, nLevelPlusOne);
            GetExport().AddAttribute(XML_NAMESPACE_TEXT,
                                     XML_OUTLINE_LEVEL,
                                     sBuf.makeStringAndClear());

            // source styles element
            SvXMLElementExport aParaStyles(GetExport(),
                                           XML_NAMESPACE_TEXT,
                                           XML_INDEX_SOURCE_STYLES,
                                           sal_True, sal_True);

            // iterate over styles in this level
            for(sal_Int32 nName = 0; nName < nNamesCount; nName++)
            {
                // stylename attribute
                GetExport().AddAttribute(XML_NAMESPACE_TEXT,
                                         XML_STYLE_NAME,
                                         aStyleNames[nName]);

                // element
                SvXMLElementExport aParaStyle(GetExport(),
                                              XML_NAMESPACE_TEXT,
                                              XML_INDEX_SOURCE_STYLE,
                                              sal_True, sal_False);
            }
        }
    }
}

void XMLSectionExport::ExportBoolean(
    const Reference<XPropertySet> & rPropSet,
    const OUString& sPropertyName,
    enum XMLTokenEnum eAttributeName,
    sal_Bool bDefault,
    sal_Bool bInvert)
{
    DBG_ASSERT(eAttributeName != XML_TOKEN_INVALID, "Need attribute name");

    Any aAny = rPropSet->getPropertyValue(sPropertyName);
    sal_Bool bTmp = *(sal_Bool*)aAny.getValue();

    // value = value ^ bInvert
    // omit if value == default
    // negate forces sal_Bool to 0/1, making them comparable
    if ((!(bTmp ^ bInvert)) != (!bDefault))
    {
        // export non-default value (since default is omitted)
        GetExport().AddAttribute(XML_NAMESPACE_TEXT,
                                 eAttributeName,
                                 bDefault ? XML_FALSE : XML_TRUE);
    }
}

const sal_Char sAPI_FieldMaster_Bibliography[] =
                                "com.sun.star.text.FieldMaster.Bibliography";
const sal_Char sAPI_SortKey[] = "SortKey";
const sal_Char sAPI_IsSortAscending[] = "IsSortAscending";

void XMLSectionExport::ExportBibliographyConfiguration(SvXMLExport& rExport)
{
    // first: get field master (via text field supplier)
    Reference<XTextFieldsSupplier> xTextFieldsSupp( rExport.GetModel(),
                                                    UNO_QUERY );
    if ( xTextFieldsSupp.is() )
    {
        const OUString sFieldMaster_Bibliography(
            RTL_CONSTASCII_USTRINGPARAM(sAPI_FieldMaster_Bibliography));

        // get bibliography field master
        Reference<XNameAccess> xMasters =
            xTextFieldsSupp->getTextFieldMasters();
        if ( xMasters->hasByName(sFieldMaster_Bibliography) )
        {
            Any aAny =
                xMasters->getByName(sFieldMaster_Bibliography);
            Reference<XPropertySet> xPropSet;
            aAny >>= xPropSet;

            DBG_ASSERT( xPropSet.is(), "field master must have XPropSet" );

            const OUString sBracketBefore(
                RTL_CONSTASCII_USTRINGPARAM("BracketBefore"));
            const OUString sBracketAfter(
                RTL_CONSTASCII_USTRINGPARAM("BracketAfter"));
            const OUString sIsNumberEntries(
                RTL_CONSTASCII_USTRINGPARAM("IsNumberEntries"));
            const OUString sIsSortByPosition(
                RTL_CONSTASCII_USTRINGPARAM("IsSortByPosition"));
            const OUString sSortKeys(
                RTL_CONSTASCII_USTRINGPARAM("SortKeys"));
            const OUString sSortAlgorithm(
                RTL_CONSTASCII_USTRINGPARAM("SortAlgorithm"));
            const OUString sLocale(
                RTL_CONSTASCII_USTRINGPARAM("Locale"));

            OUString sTmp;

            aAny = xPropSet->getPropertyValue(sBracketBefore);
            aAny >>= sTmp;
            rExport.AddAttribute(XML_NAMESPACE_TEXT, XML_PREFIX, sTmp);

            aAny = xPropSet->getPropertyValue(sBracketAfter);
            aAny >>= sTmp;
            rExport.AddAttribute(XML_NAMESPACE_TEXT, XML_SUFFIX, sTmp);

            aAny = xPropSet->getPropertyValue(sIsNumberEntries);
            if (*(sal_Bool*)aAny.getValue())
            {
                rExport.AddAttribute(XML_NAMESPACE_TEXT,
                                     XML_NUMBERED_ENTRIES, XML_TRUE);
            }

            aAny = xPropSet->getPropertyValue(sIsSortByPosition);
            if (! *(sal_Bool*)aAny.getValue())
            {
                rExport.AddAttribute(XML_NAMESPACE_TEXT,
                                     XML_SORT_BY_POSITION, XML_FALSE);
            }

            // sort algorithm
            aAny = xPropSet->getPropertyValue(sSortAlgorithm);
            OUString sAlgorithm;
            aAny >>= sAlgorithm;
            if( sAlgorithm.getLength() > 0 )
            {
                rExport.AddAttribute( XML_NAMESPACE_TEXT,
                                      XML_SORT_ALGORITHM, sAlgorithm );
            }

            // locale
            aAny = xPropSet->getPropertyValue(sLocale);
            Locale aLocale;
            aAny >>= aLocale;
            rExport.AddAttribute(XML_NAMESPACE_FO, XML_LANGUAGE,
                                     aLocale.Language);
            rExport.AddAttribute(XML_NAMESPACE_FO, XML_COUNTRY,
                                     aLocale.Country);

            // configuration element
            SvXMLElementExport aElement(rExport, XML_NAMESPACE_TEXT,
                                        XML_BIBLIOGRAPHY_CONFIGURATION,
                                        sal_True, sal_True);

            // sort keys
            aAny = xPropSet->getPropertyValue(sSortKeys);
            Sequence<Sequence<PropertyValue> > aKeys;
            aAny >>= aKeys;
            sal_Int32 nKeysCount = aKeys.getLength();
            for(sal_Int32 nKeys = 0; nKeys < nKeysCount; nKeys++)
            {
                Sequence<PropertyValue> & rKey = aKeys[nKeys];

                sal_Int32 nKeyCount = rKey.getLength();
                for(sal_Int32 nKey = 0; nKey < nKeyCount; nKey++)
                {
                    PropertyValue& rValue = rKey[nKey];

                    if (rValue.Name.equalsAsciiL(sAPI_SortKey,
                                                 sizeof(sAPI_SortKey)-1))
                    {
                        sal_Int16 nKey;
                        rValue.Value >>= nKey;
                        OUStringBuffer sBuf;
                        if (SvXMLUnitConverter::convertEnum( sBuf, nKey,
                                                 aBibliographyDataFieldMap ) )
                        {
                            rExport.AddAttribute(XML_NAMESPACE_TEXT, XML_KEY,
                                                 sBuf.makeStringAndClear());
                        }
                    }
                    else if (rValue.Name.equalsAsciiL(sAPI_IsSortAscending,
                                            sizeof(sAPI_IsSortAscending)-1))
                    {
                        sal_Bool bTmp = *(sal_Bool*)rValue.Value.getValue();
                        rExport.AddAttribute(XML_NAMESPACE_TEXT,
                                             XML_SORT_ASCENDING,
                                             bTmp ? XML_TRUE : XML_FALSE);
                    }
                }

                SvXMLElementExport aKeyElem(rExport,
                                            XML_NAMESPACE_TEXT, XML_SORT_KEY,
                                            sal_True, sal_True);
            }
        }
    }
}


sal_Bool XMLSectionExport::IsMuteSection(
    const Reference<XTextSection> & rSection) const
{
    sal_Bool bRet = sal_False;

    // a section is mute if
    // 1) it exists
    // 2) the SaveLinkedSections flag (at the export) is false
    // 3) the IsGlobalDocumentSection property is true
    // 4) it is not an Index

    if ( (!rExport.IsSaveLinkedSections()) && rSection.is() )
    {
        // walk the section chain and set bRet if any is linked
        for(Reference<XTextSection> aSection(rSection);
            aSection.is();
            aSection = aSection->getParentSection())
        {
            // check if it is a global document section (linked or index)
            Reference<XPropertySet> xPropSet(aSection, UNO_QUERY);
            if (xPropSet.is())
            {
                Any aAny = xPropSet->getPropertyValue(sIsGlobalDocumentSection);

                if ( *(sal_Bool*)aAny.getValue() )
                {
                    Reference<XDocumentIndex> xIndex;
                    if (! GetIndex(rSection, xIndex))
                    {
                        bRet = sal_True;

                        // early out if result is known
                        break;
                    }
                }
            }
            // section has no properties: ignore
        }
    }
    // else: no section, or always save sections: default (false)

    return bRet;
}

sal_Bool XMLSectionExport::IsMuteSection(
    const Reference<XTextContent> & rSection,
    sal_Bool bDefault) const
{
    // default: like default argument
    sal_Bool bRet = bDefault;

    Reference<XPropertySet> xPropSet(rSection->getAnchor(), UNO_QUERY);
    if (xPropSet.is())
    {
        if (xPropSet->getPropertySetInfo()->hasPropertyByName(sTextSection))
        {
            Any aAny = xPropSet->getPropertyValue(sTextSection);
            Reference<XTextSection> xSection;
            aAny >>= xSection;

            bRet = IsMuteSection(xSection);
        }
        // else: return default
    }
    // else: return default

    return bRet;
}

sal_Bool XMLSectionExport::IsInSection(
    const Reference<XTextSection> & rEnclosingSection,
    const Reference<XTextContent> & rContent,
    sal_Bool bDefault)
{
    // default: like default argument
    sal_Bool bRet = bDefault;
    DBG_ASSERT(rEnclosingSection.is(), "enclosing section expected");

    Reference<XPropertySet> xPropSet(rContent, UNO_QUERY);
    if (xPropSet.is())
    {
        if (xPropSet->getPropertySetInfo()->hasPropertyByName(sTextSection))
        {
            Any aAny = xPropSet->getPropertyValue(sTextSection);
            Reference<XTextSection> xSection;
            aAny >>= xSection;

            // now walk chain of text sections (if we have one)
            if (xSection.is())
            {
                do
                {
                    bRet = (rEnclosingSection == xSection);
                    xSection = xSection->getParentSection();
                }
                while (!bRet && xSection.is());
            }
            else
                bRet = sal_False;   // no section -> can't be inside
        }
        // else: no TextSection property -> return default
    }
    // else: no XPropertySet -> return default

    return bRet;
}


void XMLSectionExport::ExportMasterDocHeadingDummies()
{
    if( bHeadingDummiesExported )
        return;

    Reference< XChapterNumberingSupplier > xCNSupplier( rExport.GetModel(),
                                                        UNO_QUERY );

    Reference< XIndexReplace > xChapterNumbering;
    if( xCNSupplier.is() )
        xChapterNumbering = xCNSupplier->getChapterNumberingRules();

    if( !xChapterNumbering.is() )
        return;

    sal_Int32 nCount = xChapterNumbering->getCount();
    for( sal_Int32 nLevel = 0; nLevel < nCount; nLevel++ )
    {
        OUString sStyle;
        Sequence<PropertyValue> aProperties;
        xChapterNumbering->getByIndex( nLevel ) >>= aProperties;
        for( sal_Int32 i = 0; i < aProperties.getLength(); i++ )
        {
            if( aProperties[i].Name == sHeadingStyleName )
            {
                aProperties[i].Value >>= sStyle;
                break;
            }
        }
        if( sStyle.getLength() > 0 )
        {
            GetExport().AddAttribute( XML_NAMESPACE_TEXT, XML_STYLE_NAME,
                                      sStyle );

            OUStringBuffer sTmp;
            sTmp.append( nLevel+1L );
            GetExport().AddAttribute( XML_NAMESPACE_TEXT, XML_LEVEL,
                                        sTmp.makeStringAndClear() );
            SvXMLElementExport aElem( GetExport(), XML_NAMESPACE_TEXT, XML_H,
                                        sal_True, sal_False );
        }
    }

    bHeadingDummiesExported  = sal_True;
}
}//end of namespace binfilter
