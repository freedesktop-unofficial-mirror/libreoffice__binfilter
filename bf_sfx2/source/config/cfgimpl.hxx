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

#include <bf_tools/string.hxx>
#include <bf_svtools/svarray.hxx>

#include "cfgitem.hxx"
class SotStorage;
class SvStream;
namespace binfilter {

typedef SfxConfigItem* SfxConfigItemPtr;
SV_DECL_PTRARR( SfxConfigItems_Impl, SfxConfigItemPtr, 2, 2)

struct SfxConfigItem_Impl
{
    SotStorageRef   xStorage;
    String          aName;              // old 5.0 format data
    String          aStreamName;
    SfxConfigItem*  pCItem;
    SfxConfigItems_Impl aItems;
    USHORT          nType;
    BOOL            bDefault;

                    SfxConfigItem_Impl( SfxConfigItem* pConf = NULL )
                        : pCItem( pConf )
                        , nType( pConf ? pConf->GetType() : 0 )
                        , bDefault( TRUE )
                    {}
};

typedef SfxConfigItem_Impl* SfxConfigItemPtr_Impl;
SV_DECL_PTRARR( SfxConfigItemArr_Impl, SfxConfigItemPtr_Impl, 2, 2)

class SfxObjectShell;
class SfxIFConfig_Impl;
class SfxConfigManagerImExport_Impl
{
    SfxConfigItemArr_Impl*  pItemArr;
    SfxObjectShell*         pObjShell;
    SfxIFConfig_Impl*       pIFaceConfig;

    BOOL            ImportItem( SfxConfigItem_Impl* pItem, SvStream* pStream, SotStorage* pStor );

public:
                    SfxConfigManagerImExport_Impl( SfxObjectShell* pDoc, SfxConfigItemArr_Impl* pArr )
                        : pItemArr( pArr )
                        , pObjShell( pDoc )
                        , pIFaceConfig( NULL )
                    {}

    USHORT          Import( SotStorage* pIn, SotStorage* pStor );

    static String   GetStreamName( USHORT nType );
    static USHORT   GetType( const String& rStreamName );
    static BOOL     HasConfiguration( SotStorage& rStorage );
};

}//end of namespace binfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
