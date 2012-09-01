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


#include <com/sun/star/xml/sax/XParser.hpp>


#include <unotools/streamwrap.hxx>





#include <bf_xmloff/xmlimp.hxx>

#include <bf_xmloff/xmlnmspe.hxx>
#include <bf_xmloff/xmlstyle.hxx>

#include "editsource.hxx"

#include "unotext.hxx"
#include <legacysmgr/legacy_binfilters_smgr.hxx>
namespace binfilter {
using namespace ::com::sun::star;
using namespace ::com::sun::star::document;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::xml::sax;
using namespace ::com::sun::star::text;
using namespace cppu;
using namespace xmloff::token;

using rtl::OUString;


///////////////////////////////////////////////////////////////////////

/*N*/ class SvxXMLTextImportContext : public SvXMLImportContext
/*N*/ {
/*N*/ public:
/*N*/   SvxXMLTextImportContext( SvXMLImport& rImport, USHORT nPrfx, const OUString& rLName, const Reference< XAttributeList >& xAttrList, const Reference< XText >& xText );
/*N*/   virtual ~SvxXMLTextImportContext();
/*N*/
/*N*/   virtual SvXMLImportContext *CreateChildContext( USHORT nPrefix, const OUString& rLocalName, const Reference< XAttributeList >& xAttrList );
/*N*/
/*N*/ //    SvxXMLXTableImport& getImport() const { return *(SvxXMLXTableImport*)&GetImport(); }
/*N*/
/*N*/ private:
/*N*/   const Reference< XText > mxText;
/*N*/ };
/*N*/
/*N*/ ///////////////////////////////////////////////////////////////////////
/*N*/
/*N*/ SvxXMLTextImportContext::SvxXMLTextImportContext( SvXMLImport& rInImport, USHORT nPrfx, const OUString& rLName, const Reference< XAttributeList >& /*xAttrList*/, const Reference< XText >& xText )
/*N*/ : SvXMLImportContext( rInImport, nPrfx, rLName ), mxText( xText )
/*N*/ {
/*N*/ }
/*N*/
/*N*/ SvxXMLTextImportContext::~SvxXMLTextImportContext()
/*N*/ {
/*N*/ }
/*N*/
/*N*/ SvXMLImportContext *SvxXMLTextImportContext::CreateChildContext( USHORT nInPrefix, const OUString& rLocalName, const Reference< XAttributeList >& xAttrList )
/*N*/ {
/*N*/   SvXMLImportContext* pContext = NULL;
/*N*/   if(XML_NAMESPACE_OFFICE == nInPrefix && IsXMLToken( rLocalName, XML_BODY ) )
/*N*/   {
/*N*/       pContext = new SvxXMLTextImportContext( GetImport(), nInPrefix, rLocalName, xAttrList, mxText );
/*N*/   }
/*N*/   else if( XML_NAMESPACE_OFFICE == nInPrefix && IsXMLToken( rLocalName, XML_AUTOMATIC_STYLES ) )
/*N*/   {
/*N*/       pContext = new SvXMLStylesContext( GetImport(), nInPrefix, rLocalName, xAttrList );
/*N*/       GetImport().GetTextImport()->SetAutoStyles( (SvXMLStylesContext*)pContext );
/*N*/
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       pContext = GetImport().GetTextImport()->CreateTextChildContext( GetImport(), nInPrefix, rLocalName, xAttrList );
/*N*/   }
/*N*/
/*N*/   if( NULL == pContext )
/*N*/       pContext = new SvXMLImportContext( GetImport(), nInPrefix, rLocalName );
/*N*/
/*N*/   return pContext;
/*N*/ }
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
