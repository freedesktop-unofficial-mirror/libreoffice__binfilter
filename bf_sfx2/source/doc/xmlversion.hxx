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
#ifndef _SFX_XMLVERSION_HXX
#define _SFX_XMLVERSION_HXX

#include <bf_so3/svstor.hxx>

#include <bf_xmloff/xmlexp.hxx>

#include <bf_xmloff/xmlimp.hxx>



class DateTime;
namespace binfilter {

class SfxVersionTableDtor;

// ------------------------------------------------------------------------
class SfxXMLVersListImport_Impl : public SvXMLImport
{
private:
    SfxVersionTableDtor *mpVersions;

protected:

    // This method is called after the namespace map has been updated, but
    // before a context for the current element has been pushed.
    virtual SvXMLImportContext *CreateContext( sal_uInt16 nPrefix,
                    const ::rtl::OUString& rLocalName,
                    const ::com::sun::star::uno::Reference<
                    ::com::sun::star::xml::sax::XAttributeList > & xAttrList );

public:

    // #110680#
    SfxXMLVersListImport_Impl(
        const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory > xServiceFactory,
        SfxVersionTableDtor *pVersions );
    ~SfxXMLVersListImport_Impl() throw();

    SfxVersionTableDtor*     GetList() { return mpVersions; }
};

// ------------------------------------------------------------------------
class SfxXMLVersListContext_Impl : public SvXMLImportContext
{
private:
    SfxXMLVersListImport_Impl & rLocalRef;

public:

    SfxXMLVersListContext_Impl( SfxXMLVersListImport_Impl& rImport,
                           sal_uInt16 nPrefix,
                           const ::rtl::OUString& rLocalName,
                           const ::com::sun::star::uno::Reference<
                           ::com::sun::star::xml::sax::XAttributeList > & xAttrList );

    ~SfxXMLVersListContext_Impl();

    virtual SvXMLImportContext *CreateChildContext( sal_uInt16 nPrefix,
                           const ::rtl::OUString& rLocalName,
                           const ::com::sun::star::uno::Reference<
                           ::com::sun::star::xml::sax::XAttributeList > & xAttrList );

};

// ------------------------------------------------------------------------
class SfxXMLVersionContext_Impl : public SvXMLImportContext
{
private:
    SfxXMLVersListImport_Impl&  rLocalRef;

    static sal_Bool         ParseISODateTimeString(
                                const ::rtl::OUString& rString,
                                DateTime& rDateTime );

public:

    SfxXMLVersionContext_Impl( SfxXMLVersListImport_Impl& rImport,
                          sal_uInt16 nPrefix,
                          const ::rtl::OUString& rLocalName,
                          const ::com::sun::star::uno::Reference<
                          ::com::sun::star::xml::sax::XAttributeList > & xAttrList );

    ~SfxXMLVersionContext_Impl();
};


// ------------------------------------------------------------------------
class SfxXMLVersList_Impl
{
public:
    static sal_Bool ReadInfo( SvStorageRef xRoot, SfxVersionTableDtor *pList );
};



}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
