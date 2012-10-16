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

#ifndef _XMLOFF_XMLNUMFE_HXX
#define _XMLOFF_XMLNUMFE_HXX

#include <com/sun/star/util/XNumberFormatsSupplier.hpp>

#include <com/sun/star/uno/Sequence.h>

#include <rtl/ustrbuf.hxx>
class Color;
class CharClass;
class LocaleDataWrapper;

namespace binfilter {
class SvNumberFormatter;
class SvNumberformat;

#define XML_WRITTENNUMBERSTYLES "WrittenNumberStyles"

class SvXMLExport;
class SvXMLNamespaceMap;
class SvXMLAttributeList;
class SvXMLNumUsedList_Impl;
class SvXMLEmbeddedTextEntryArr;

class SvXMLNumFmtExport
{
private:
    SvXMLExport&                rExport;
    ::rtl::OUString             sPrefix;
    SvNumberFormatter*          pFormatter;
    ::rtl::OUStringBuffer       sTextContent;
    SvXMLNumUsedList_Impl*      pUsedList;
    CharClass*                  pCharClass;
    LocaleDataWrapper*          pLocaleData;

    void    AddCalendarAttr_Impl( const ::rtl::OUString& rCalendar );
    void    AddStyleAttr_Impl( sal_Bool bLong );
    void    AddTextualAttr_Impl( sal_Bool bText );
    void    AddLanguageAttr_Impl( sal_Int32 nLang );

    void    AddToTextElement_Impl( const ::rtl::OUString& rString );
    void    FinishTextElement_Impl();

    void    WriteColorElement_Impl( const Color& rColor );
    void    WriteNumberElement_Impl( sal_Int32 nDecimals, sal_Int32 nInteger,
                                        const ::rtl::OUString& rDashStr, sal_Bool bVarDecimals,
                                        sal_Bool bGrouping, sal_Int32 nTrailingThousands,
                                        const SvXMLEmbeddedTextEntryArr& rEmbeddedEntries );
    void    WriteScientificElement_Impl( sal_Int32 nDecimals, sal_Int32 nInteger,
                                        sal_Bool bGrouping, sal_Int32 nExp );
    void    WriteFractionElement_Impl( sal_Int32 nInteger, sal_Bool bGrouping,
                                        sal_Int32 nNumerator, sal_Int32 nDenominator );
    void    WriteCurrencyElement_Impl( const ::rtl::OUString& rString,
                                        const ::rtl::OUString& rExt );
    void    WriteBooleanElement_Impl();
    void    WriteTextContentElement_Impl();
    void    WriteDayElement_Impl( const ::rtl::OUString& rCalendar, sal_Bool bLong );
    void    WriteMonthElement_Impl( const ::rtl::OUString& rCalendar, sal_Bool bLong, sal_Bool bText );
    void    WriteYearElement_Impl( const ::rtl::OUString& rCalendar, sal_Bool bLong );
    void    WriteEraElement_Impl( const ::rtl::OUString& rCalendar, sal_Bool bLong );
    void    WriteDayOfWeekElement_Impl( const ::rtl::OUString& rCalendar, sal_Bool bLong );
    void    WriteWeekElement_Impl( const ::rtl::OUString& rCalendar );
    void    WriteQuarterElement_Impl( const ::rtl::OUString& rCalendar, sal_Bool bLong );
    void    WriteHoursElement_Impl( sal_Bool bLong );
    void    WriteMinutesElement_Impl( sal_Bool bLong );
    void    WriteSecondsElement_Impl( sal_Bool bLong, sal_uInt16 nDecimals );
    void    WriteAMPMElement_Impl();
    void    WriteMapElement_Impl( sal_Int32 nOp, double fLimit,
                                    sal_Int32 nKey, sal_Int32 nPart );

    sal_Bool WriteTextWithCurrency_Impl( const ::rtl::OUString& rString,
                            const ::com::sun::star::lang::Locale& rLocale );
    void    ExportPart_Impl( const SvNumberformat& rFormat, sal_uInt32 nKey,
                                sal_uInt16 nPart, sal_Bool bDefPart );

    void    ExportFormat_Impl( const SvNumberformat& rFormat, sal_uInt32 nKey );

public:
    SvXMLNumFmtExport( SvXMLExport& rExport,
                       const ::com::sun::star::uno::Reference<
                        ::com::sun::star::util::XNumberFormatsSupplier >& rSupp );
    SvXMLNumFmtExport( SvXMLExport& rExport,
                       const ::com::sun::star::uno::Reference<
                        ::com::sun::star::util::XNumberFormatsSupplier >& rSupp,
                       const ::rtl::OUString& rPrefix );

    virtual ~SvXMLNumFmtExport();

    // core API
    void Export( sal_Bool bIsAutoStyle);

    // mark number format as used
    void SetUsed( sal_uInt32 nKey );

    // get the style name that was generated for a key
    ::rtl::OUString GetStyleName( sal_uInt32 nKey );

    void GetWasUsed( ::com::sun::star::uno::Sequence<sal_Int32>& rWasUsed);
    void SetWasUsed(const ::com::sun::star::uno::Sequence<sal_Int32>& rWasUsed);

    // two methods to allow the field import/export to treat system languages
    // properly:

    /// obtain number format with system languange for a given key
    sal_uInt32 ForceSystemLanguage( sal_uInt32 nKey );

    /// determine whether number format uses system language
    bool IsSystemLanguage( sal_uInt32 nKey );
};

}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
