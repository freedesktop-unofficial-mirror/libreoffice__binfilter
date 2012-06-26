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
#ifndef _FILEOBJ_HXX
#define _FILEOBJ_HXX

#include <bf_so3/linksrc.hxx>
#include <bf_sfx2/docfile.hxx>
class Graphic;
namespace binfilter {

struct Impl_DownLoadData;


class SvFileObject : public ::binfilter::SvLinkSource
{
    String sFileNm;
    String sFilter;
    String sReferer;
    SfxMediumRef xMed;
    Impl_DownLoadData* pDownLoadData;

    BYTE nType;

    BOOL bLoadAgain : 1;
    BOOL bSynchron : 1;
    BOOL bLoadError : 1;
    BOOL bWaitForData : 1;
    BOOL bInNewData : 1;
    BOOL bDataReady : 1;
    BOOL bMedUseCache : 1;
    BOOL bNativFormat : 1;
    BOOL bClearMedium : 1;
    BOOL bStateChangeCalled : 1;
    BOOL bInCallDownLoad : 1;

    BOOL GetGraphic_Impl( Graphic&, SvStream* pStream = 0 );
    BOOL LoadFile_Impl();
    void SendStateChg_Impl( USHORT nState );

    DECL_STATIC_LINK( SvFileObject, DelMedium_Impl, SfxMediumRef* );
    DECL_STATIC_LINK( SvFileObject, LoadGrfReady_Impl, void* );
    DECL_STATIC_LINK( SvFileObject, LoadGrfNewData_Impl, void* );
protected:
    virtual ~SvFileObject();

public:
    SvFileObject();

    virtual BOOL GetData( ::com::sun::star::uno::Any & rData /*out param*/,
                            const String & rMimeType,
                            BOOL bSynchron = FALSE );

    virtual BOOL Connect( ::binfilter::SvBaseLink* );

    // erfrage ob das man direkt auf die Daten zugreifen kann oder ob das
    // erst angestossen werden muss

    void CancelTransfers();
};


}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
