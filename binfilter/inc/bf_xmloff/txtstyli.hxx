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
#ifndef _XMLOFF_TXTSTYLI_HXX_
#define _XMLOFF_TXTSTYLI_HXX_

#include <bf_xmloff/prstylei.hxx>
namespace binfilter {

class SvXMLTokenMap;
class XMLEventsImportContext;

class XMLTextStyleContext : public XMLPropStyleContext
{
    ::rtl::OUString             sListStyleName;
    ::rtl::OUString             sCategoryVal;
    ::rtl::OUString             sDropCapTextStyleName;
    ::rtl::OUString             sMasterPageName;
    const ::rtl::OUString       sIsAutoUpdate;
    const ::rtl::OUString       sCategory;
    const ::rtl::OUString       sNumberingStyleName;
public:
    const ::rtl::OUString       sDropCapCharStyleName;
private:
    const ::rtl::OUString       sPageDescName;

    sal_Bool    bAutoUpdate : 1;
    sal_Bool    bHasMasterPageName : 1;

    sal_Bool bHasCombinedCharactersLetter : 1;

    XMLEventsImportContext* pEventContext;

protected:

    virtual void SetAttribute( sal_uInt16 nPrefixKey,
                               const ::rtl::OUString& rLocalName,
                               const ::rtl::OUString& rValue );

public:

    TYPEINFO();

    XMLTextStyleContext( SvXMLImport& rImport, sal_uInt16 nPrfx,
            const ::rtl::OUString& rLName,
            const ::com::sun::star::uno::Reference<
                ::com::sun::star::xml::sax::XAttributeList > & xAttrList,
            SvXMLStylesContext& rStyles, sal_uInt16 nFamily,
            sal_Bool bDefaultStyle = sal_False );
    virtual ~XMLTextStyleContext();

    virtual SvXMLImportContext *CreateChildContext(
            sal_uInt16 nPrefix,
            const ::rtl::OUString& rLocalName,
            const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList > & xAttrList );

    sal_Bool IsAutoUpdate() const { return bAutoUpdate; }

    const ::rtl::OUString& GetListStyle() const { return sListStyleName; }
    const ::rtl::OUString& GetMasterPageName() const { return sMasterPageName; }
    sal_Bool HasMasterPageName() const { return bHasMasterPageName; }
    const ::rtl::OUString& GetDropCapStyleName() const { return sDropCapTextStyleName; }

    virtual void CreateAndInsert( sal_Bool bOverwrite );
    virtual void Finish( sal_Bool bOverwrite );
    virtual void SetDefaults();

    // overload FillPropertySet, so we can get at the combined characters
    virtual void FillPropertySet(
            const ::com::sun::star::uno::Reference<
                ::com::sun::star::beans::XPropertySet > & rPropSet );

    inline sal_Bool HasCombinedCharactersLetter()
        { return bHasCombinedCharactersLetter; }

    const ::std::vector< XMLPropertyState > & _GetProperties() { return GetProperties(); }
};

}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
