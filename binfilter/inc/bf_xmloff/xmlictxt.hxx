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

#ifndef _XMLOFF_XMLICTXT_HXX
#define _XMLOFF_XMLICTXT_HXX

#include <com/sun/star/xml/sax/XAttributeList.hpp>

#include <bf_svtools/bf_solar.h>
#include <tools/ref.hxx>
#include <tools/rtti.hxx>
namespace binfilter {

class SvXMLNamespaceMap;
class SvXMLImport;

class SvXMLImportContext : public SvRefBase
{
    friend class SvXMLImport;

    SvXMLImport& rImport;

    USHORT      nPrefix;
    ::rtl::OUString aLocalName;

    SvXMLNamespaceMap   *pRewindMap;

    SvXMLNamespaceMap  *GetRewindMap() const { return pRewindMap; }
    void SetRewindMap( SvXMLNamespaceMap *p ) { pRewindMap = p; }

protected:

    SvXMLImport& GetImport() { return rImport; }
    const SvXMLImport& GetImport() const { return rImport; }

public:
    TYPEINFO();

    USHORT GetPrefix() const { return nPrefix; }
    const ::rtl::OUString& GetLocalName() const { return aLocalName; }

    // A contexts constructor does anything that is required if an element
    // starts. Namespace processing has been done already.
    // Note that virtual methods cannot be used inside constructors. Use
    // StartElement instead if this is required.
    SvXMLImportContext( SvXMLImport& rImport, USHORT nPrfx,
                        const ::rtl::OUString& rLName );

    // A contexts destructor does anything that is required if an element
    // ends. By default, nothing is done.
    // Note that virtual methods cannot be used inside destructors. Use
    // EndElement instead if this is required.
    virtual ~SvXMLImportContext();

    // Create a childs element context. By default, the import's
    // CreateContext method is called to create a new default context.
    virtual SvXMLImportContext *CreateChildContext( USHORT nPrefix,
                                   const ::rtl::OUString& rLocalName,
                                   const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& xAttrList );

    // StartElement is called after a context has been constructed and
    // before a elements context is parsed. It may be used for actions that
    // require virtual methods. The default is to do nothing.
    virtual void StartElement( const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& xAttrList );

    // EndElement is called before a context will be destructed, but
    // after a elements context has been parsed. It may be used for actions
    // that require virtual methods. The default is to do nothing.
    virtual void EndElement();

    // This method is called for all characters that are contained in the
    // current element. The default is to ignore them.
    virtual void Characters( const ::rtl::OUString& rChars );
};

SV_DECL_REF( SvXMLImportContext )
SV_IMPL_REF( SvXMLImportContext )

}//end of namespace binfilter
#endif  //  _XMLOFF_XMLICTXT_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
