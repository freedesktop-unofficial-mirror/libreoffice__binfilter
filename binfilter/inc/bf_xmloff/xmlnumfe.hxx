/*************************************************************************
 *
 *  $RCSfile: xmlnumfe.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: aw $ $Date: 2003-12-05 09:18:07 $
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

#ifndef _XMLOFF_XMLNUMFE_HXX
#define _XMLOFF_XMLNUMFE_HXX

#ifndef _COM_SUN_STAR_UTIL_XNUMBERFORMATSSUPPLIER_HPP_
#include <com/sun/star/util/XNumberFormatsSupplier.hpp>
#endif

#ifndef _COM_SUN_STAR_UNO_SEQUENCE_H_
#include <com/sun/star/uno/Sequence.h>
#endif

#ifndef _RTL_USTRBUF_HXX_
#include <rtl/ustrbuf.hxx>
#endif
class Color;
class CharClass;
class LocaleDataWrapper;
class SvNumberFormatter;
class SvNumberformat;

namespace binfilter {

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

