/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2000, 2010 Oracle and/or its affiliates.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/
#ifndef SVTOOLS_DOCUMENTINFOPREVIEW_HXX
#define SVTOOLS_DOCUMENTINFOPREVIEW_HXX

#include <bf_svtools/bf_solar.h>

#include "bf_svtools/svtdllapi.h"

#include <vcl/window.hxx>
#include <com/sun/star/document/XStandaloneDocumentInfo.hpp>
#include <com/sun/star/lang/Locale.hpp>

namespace binfilter {

class SvtExtendedMultiLineEdit_Impl;
class SvtDocInfoTable_Impl;

class  ODocumentInfoPreview : public Window
{
    SvtExtendedMultiLineEdit_Impl*  m_pEditWin;
    SvtDocInfoTable_Impl*           m_pInfoTable;
    com::sun::star::lang::Locale    m_aLocale;

public:
    ODocumentInfoPreview( Window* pParent ,WinBits _nBits);
    virtual ~ODocumentInfoPreview();

    virtual void Resize();
    void    Clear();
    void    fill(const ::com::sun::star::uno::Reference< ::com::sun::star::document::XStandaloneDocumentInfo>& _xDocInfo
                ,const String& rURL);
    void    InsertEntry( const String& rTitle, const String& rValue );
    void SetAutoScroll(BOOL _bAutoScroll);
};

}

#endif // SVTOOLS_DOCUMENTINFOPREVIEW_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */