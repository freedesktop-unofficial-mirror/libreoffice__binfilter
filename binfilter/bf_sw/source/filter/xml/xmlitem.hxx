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

#ifndef _XMLITEM_HXX
#define _XMLITEM_HXX

#include <com/sun/star/xml/sax/XAttributeList.hpp>

#include <bf_svtools/bf_solar.h>
#include <limits.h>

#include <bf_xmloff/xmlictxt.hxx>

namespace rtl { class OUString; }
namespace binfilter {

class SfxItemSet;

class SvXMLUnitConverter;
class SvXMLImportItemMapper;

struct SvXMLItemMapEntry;

class SvXMLItemSetContext : public SvXMLImportContext
{
protected:
    SfxItemSet                  &rItemSet;
    const SvXMLImportItemMapper &rIMapper;
    const SvXMLUnitConverter    &rUnitConv;

public:

    SvXMLItemSetContext( SvXMLImport& rImport, USHORT nPrfx,
                         const ::rtl::OUString& rLName,
                         const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& xAttrList,
                         SfxItemSet&  rItemSet,
                         const SvXMLImportItemMapper& rIMappper,
                         const SvXMLUnitConverter& rUnitConv );

    virtual ~SvXMLItemSetContext();

    virtual SvXMLImportContext *CreateChildContext( USHORT nPrefix,
                                     const ::rtl::OUString& rLocalName,
                                     const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& xAttrList );

    // This method is called from this instance implementation of
    // CreateChildContext if the element matches an entry in the
    // SvXMLImportItemMapper with the mid flag MID_FLAG_ELEMENT_ITEM_IMPORT
    virtual SvXMLImportContext *CreateChildContext( USHORT nPrefix,
                                   const ::rtl::OUString& rLocalName,
                                   const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& xAttrList,
                                    SfxItemSet&  rItemSet,
                                   const SvXMLItemMapEntry& rEntry,
                                   const SvXMLUnitConverter& rUnitConv );


};


} //namespace binfilter
#endif  //  _XMLITEM_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
