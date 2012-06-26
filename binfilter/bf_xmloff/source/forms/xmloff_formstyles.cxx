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

#include "formstyles.hxx"
namespace binfilter {

//.........................................................................
namespace xmloff
{
//.........................................................................

    using namespace token;
    using namespace ::com::sun::star::uno;
    using namespace ::com::sun::star::xml;

    //=====================================================================
    //= OControlStyleContext
    //=====================================================================
    //---------------------------------------------------------------------
    OControlStyleContext::OControlStyleContext( SvXMLImport& _rImport, const sal_uInt16 _Prefix, const ::rtl::OUString& _rLocalName,
        const Reference< sax::XAttributeList >& _rxAttrList, SvXMLStylesContext& _rParentStyles,
        const sal_uInt16 _nFamily, const sal_Bool _bDefaultStyle )
        :XMLPropStyleContext( _rImport, _Prefix, _rLocalName, _rxAttrList, _rParentStyles, _nFamily, _bDefaultStyle )
    {
    }

    //---------------------------------------------------------------------
    void OControlStyleContext::SetAttribute( sal_uInt16 _nPrefixKey, const ::rtl::OUString& _rLocalName, const ::rtl::OUString& _rValue )
    {
        if ( _rLocalName == GetXMLToken( XML_DATA_STYLE_NAME ) )
            m_sNumberStyleName = _rValue;
        else
            XMLPropStyleContext::SetAttribute( _nPrefixKey, _rLocalName, _rValue );
    }

//.........................................................................
}   // namespace xmloff
//.........................................................................


}//end of namespace binfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
