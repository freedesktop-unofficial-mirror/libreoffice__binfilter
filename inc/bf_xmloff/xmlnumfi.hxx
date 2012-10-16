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

#ifndef _XMLOFF_XMLNUMFI_HXX
#define _XMLOFF_XMLNUMFI_HXX

#include <bf_svtools/bf_solar.h>

#include <com/sun/star/util/XNumberFormatsSupplier.hpp>

#include <com/sun/star/xml/sax/XAttributeList.hpp>
#include <bf_xmloff/xmlstyle.hxx>
#include <rtl/ustrbuf.hxx>
#include <i18npool/lang.h>
#ifndef __SGI_STL_VECTOR
#include <vector>
#endif
#include <unotools/localedatawrapper.hxx>
class Color;
class Color;
namespace binfilter {
class SvNumberFormatter;
class SvtSysLocale;

#define XML_NUMBERSTYLES "NumberStyles"

enum SvXMLStylesTokens
{
    XML_TOK_STYLES_NUMBER_STYLE,
    XML_TOK_STYLES_CURRENCY_STYLE,
    XML_TOK_STYLES_PERCENTAGE_STYLE,
    XML_TOK_STYLES_DATE_STYLE,
    XML_TOK_STYLES_TIME_STYLE,
    XML_TOK_STYLES_BOOLEAN_STYLE,
    XML_TOK_STYLES_TEXT_STYLE
};

enum SvXMLDateElementAttributes
{
    XML_DEA_NONE,
    XML_DEA_ANY,
    XML_DEA_SHORT,
    XML_DEA_LONG,
    XML_DEA_TEXTSHORT,
    XML_DEA_TEXTLONG
};

class SvXMLNumImpData;
class SvXMLImport;
class SvXMLStyleContext;
class SvXMLStylesContext;
struct SvXMLNumberInfo;

//  use SvXMLNumFmtHelper in the context for <office:styles> to create
//  child contexts for data styles

class SvXMLNumFmtHelper
{
    SvXMLNumImpData* pData;

    // #110680#
    ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory > mxServiceFactory;

public:
    // #110680#
    //SvXMLNumFmtHelper( const ::com::sun::star::uno::Reference<
    //      ::com::sun::star::util::XNumberFormatsSupplier >& rSupp );
    //SvXMLNumFmtHelper( SvNumberFormatter* pNumberFormatter );
    SvXMLNumFmtHelper(
        const ::com::sun::star::uno::Reference< ::com::sun::star::util::XNumberFormatsSupplier >& rSupp,
        const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& xServiceFactory );

    SvXMLNumFmtHelper(
        SvNumberFormatter* pNumberFormatter,
        const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& xServiceFactory );

    ~SvXMLNumFmtHelper();

    SvXMLStyleContext*  CreateChildContext( SvXMLImport& rImport,
                USHORT nPrefix, const ::rtl::OUString& rLocalName,
                const ::com::sun::star::uno::Reference<
                      ::com::sun::star::xml::sax::XAttributeList>& xAttrList,
                    SvXMLStylesContext& rStyles);

    SvXMLNumImpData* getData() { return pData; }

    const SvXMLTokenMap&    GetStylesElemTokenMap();

//  sal_uInt32  GetKeyForName( const ::rtl::OUString& rName );
};

//  SvXMLNumFmtDefaults is used in import and export

class SvXMLNumFmtDefaults
{
public:
    // return value is NfIndexTableOffset
    static sal_uInt16 GetDefaultDateFormat( SvXMLDateElementAttributes eDOW,
                SvXMLDateElementAttributes eDay, SvXMLDateElementAttributes eMonth,
                SvXMLDateElementAttributes eYear, SvXMLDateElementAttributes eHours,
                SvXMLDateElementAttributes eMins, SvXMLDateElementAttributes eSecs,
                sal_Bool bSystem );
};

struct MyCondition
{
    ::rtl::OUString sCondition;
    ::rtl::OUString sMapName;
};

class SvXMLNumFormatContext : public SvXMLStyleContext
{
    SvXMLNumImpData*    pData;
    SvXMLStylesContext*             pStyles;
    std::vector <MyCondition>   aMyConditions;
    sal_uInt16          nType;
    sal_Int32           nKey;
//  ::rtl::OUString     sFormatName;
    ::rtl::OUString     sFormatTitle;
//  ::rtl::OUString     sMapName;
    ::rtl::OUString     sCalendar;
    ::rtl::OUString     sFormatString;
    LanguageType        nFormatLang;
    ::com::sun::star::lang::Locale  aLocale;
    sal_Bool            bAutoOrder;
    sal_Bool            bFromSystem;
    sal_Bool            bTruncate;
    sal_Bool            bAutoDec;       // set in AddNumber
    sal_Bool            bAutoInt;       // set in AddNumber
    sal_Bool            bHasExtraText;
    ::rtl::OUStringBuffer   aFormatCode;
    ::rtl::OUStringBuffer   aConditions;
    sal_Bool            bHasLongDoW;
    sal_Bool            bHasEra;
    sal_Bool            bHasDateTime;
    sal_Bool            bRemoveAfterUse;

    //  contained date elements, used to recognize default date formats
    SvXMLDateElementAttributes  eDateDOW;
    SvXMLDateElementAttributes  eDateDay;
    SvXMLDateElementAttributes  eDateMonth;
    SvXMLDateElementAttributes  eDateYear;
    SvXMLDateElementAttributes  eDateHours;
    SvXMLDateElementAttributes  eDateMins;
    SvXMLDateElementAttributes  eDateSecs;
    sal_Bool                    bDateNoDefault;

    sal_Int32   PrivateGetKey();

public:
                SvXMLNumFormatContext( SvXMLImport& rImport, USHORT nPrfx,
                                    const ::rtl::OUString& rLName,
                                    SvXMLNumImpData* pNewData, sal_uInt16 nNewType,
                                    const ::com::sun::star::uno::Reference<
                                        ::com::sun::star::xml::sax::XAttributeList>& xAttrList,
                                    SvXMLStylesContext& rStyles );
                SvXMLNumFormatContext( SvXMLImport& rImport, USHORT nPrfx,
                                    const ::rtl::OUString& rLName,
                                    const ::com::sun::star::uno::Reference<
                                        ::com::sun::star::xml::sax::XAttributeList>& xAttrList,
                                    const sal_Int32 nKey,
                                    SvXMLStylesContext& rStyles );
    virtual     ~SvXMLNumFormatContext();

    virtual SvXMLImportContext *CreateChildContext( USHORT nPrefix,
                                    const ::rtl::OUString& rLocalName,
                                    const ::com::sun::star::uno::Reference<
                                          ::com::sun::star::xml::sax::XAttributeList>& xAttrList );
    virtual void CreateAndInsert(sal_Bool bOverwrite);
    virtual void Finish(sal_Bool bOverwrite);

    SvXMLNumImpData* GetData() const                { return pData; }
    sal_Int32 GetKey();
    void GetFormat( ::rtl::OUString& rFormatString, ::com::sun::star::lang::Locale& rLocale);
    sal_uInt16 GetType() const                      { return nType; }   // SvXMLStylesTokens

    sal_Bool IsFromSystem() const                   { return bFromSystem; }
    sal_Bool HasLongDoW() const                     { return bHasLongDoW; }
    void SetHasLongDoW(sal_Bool bSet)               { bHasLongDoW = bSet; }
    sal_Bool HasEra() const                         { return bHasEra; }
    void SetHasEra(sal_Bool bSet)                   { bHasEra = bSet; }

    void UpdateCalendar( const ::rtl::OUString& rNewCalendar );

    const LocaleDataWrapper& GetLocaleData() const;

    void AddToCode( const ::rtl::OUString& rString );
    void AddNumber( const SvXMLNumberInfo& rInfo );
    void AddCurrency( const ::rtl::OUString& rContent, LanguageType nLang );

    void AddNfKeyword( sal_uInt16 nIndex );
    sal_Bool ReplaceNfKeyword( sal_uInt16 nOld, sal_uInt16 nNew );
    void AddCondition( const sal_Int32 nIndex );
    void AddCondition( const sal_Int32 nIndex, const ::rtl::OUString& rFormat, const LocaleDataWrapper& rData );
    void AddCondition( const ::rtl::OUString& rCondition, const ::rtl::OUString& rApplyName );
    void AddColor( const Color& rColor );

    /// determine whether number format uses the system language
    sal_Bool IsSystemLanguage();
};

}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
