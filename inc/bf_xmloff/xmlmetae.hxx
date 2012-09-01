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

#ifndef _XMLOFF_XMLMETAE_HXX
#define _XMLOFF_XMLMETAE_HXX

#include <com/sun/star/document/XDocumentInfo.hpp>
#include <com/sun/star/xml/sax/XDocumentHandler.hpp>
#include <com/sun/star/xml/sax/XAttributeList.hpp>
#include <com/sun/star/beans/XPropertySet.hpp>
#include <com/sun/star/util/DateTime.hpp>
#include <com/sun/star/lang/Locale.hpp>
#include <bf_xmloff/xmltoken.hxx>
class Time;

namespace com { namespace sun { namespace star { namespace frame {
    class XModel;
} } } }
namespace binfilter {

class SvXMLNamespaceMap;
class SvXMLAttributeList;
class SvXMLExport;

class SfxXMLMetaExport
{
private:
    SvXMLExport&                                        rExport;
    ::com::sun::star::uno::Reference<
        ::com::sun::star::document::XDocumentInfo>      xDocInfo;
    ::com::sun::star::uno::Reference<
        ::com::sun::star::beans::XPropertySet>          xInfoProp;
    ::com::sun::star::lang::Locale                      aLocale;

    void    SimpleStringElement( const ::rtl::OUString& rPropertyName,
                                 sal_uInt16 nNamespace,
                             enum ::binfilter::xmloff::token::XMLTokenEnum eElementName );
    void    SimpleDateTimeElement( const ::rtl::OUString& rPropertyName,
                                   sal_uInt16 nNamespace,
                             enum ::binfilter::xmloff::token::XMLTokenEnum eElementName );

public:
    SfxXMLMetaExport( SvXMLExport& rExport,
                      const ::com::sun::star::uno::Reference<
                        ::com::sun::star::frame::XModel>& rDocModel );

    virtual ~SfxXMLMetaExport();

    // core API
    void Export();

    static ::rtl::OUString GetISODateTimeString(
                        const ::com::sun::star::util::DateTime& rDateTime );
    static ::rtl::OUString GetISODurationString( const Time& rTime );
};

}//end of namespace binfilter
#endif // _XMLOFF_XMLMETAE_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
