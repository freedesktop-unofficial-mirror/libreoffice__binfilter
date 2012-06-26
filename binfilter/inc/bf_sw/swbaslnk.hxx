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
#ifndef _SWBASLNK_HXX
#define _SWBASLNK_HXX

#include <bf_svtools/bf_solar.h>


#include <bf_so3/lnkbase.hxx>
namespace binfilter {

class SwNode;
class SwCntntNode;
class SwNodeIndex;

class SwBaseLink : public ::binfilter::SvBaseLink
{
    SwCntntNode* pCntntNode;
    BOOL bSwapIn : 1;
    BOOL bNoDataFlag : 1;
    BOOL bIgnoreDataChanged : 1;

public:
    TYPEINFO();

    SwBaseLink( USHORT nMode, USHORT nFormat, SwCntntNode* pNode = 0 )
        : ::binfilter::SvBaseLink( nMode, nFormat ), pCntntNode( pNode ),
        bSwapIn( FALSE ), bNoDataFlag( FALSE ), bIgnoreDataChanged( FALSE )
    {}
    virtual ~SwBaseLink();

    virtual void DataChanged( const String& rMimeType,
                                const ::com::sun::star::uno::Any & rValue );



    SwCntntNode *GetCntntNode() { return pCntntNode; }

    // nur fuer Grafiken
    bool SwapIn( BOOL bWaitForData = FALSE, BOOL bNativFormat = FALSE );

    bool IsShowQuickDrawBmp() const;                // nur fuer Grafiken

    bool Connect() { return 0 != SvBaseLink::GetRealObject(); }

    // nur fuer Grafik-Links ( zum Umschalten zwischen DDE / Grf-Link)
    void SetObjType( USHORT nType ) { SvBaseLink::SetObjType( nType ); }

    BOOL IsRecursion( const SwBaseLink* pChkLnk ) const;
    virtual BOOL IsInRange( ULONG nSttNd, ULONG nEndNd, xub_StrLen nStt = 0,
                            xub_StrLen nEnd = STRING_NOTFOUND ) const;

    void SetNoDataFlag()    { bNoDataFlag = TRUE; }
    BOOL ChkNoDataFlag()    { return bNoDataFlag ? !(bNoDataFlag = FALSE) : FALSE; }
    BOOL IsNoDataFlag() const           { return bNoDataFlag; }
};


} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
