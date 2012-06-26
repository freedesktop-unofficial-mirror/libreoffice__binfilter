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
#ifndef _TXTATR_HXX
#define _TXTATR_HXX

#include <bf_svtools/bf_solar.h>

#include <txatbase.hxx>     // SwTxtAttr/SwTxtAttrEnd
#include <calbck.hxx>
namespace binfilter {

class SwTxtNode;    // fuer SwTxtFld
class SvxFont;
class SwCharSetCol;
class SwCharFmt;
class SvxTwoLinesItem;

// ATT_CHARFMT *********************************************

class SwTxtCharFmt : public SwTxtAttrEnd
{
    SwTxtNode* pMyTxtNd;
    BOOL bPrevNoHyph    : 1;
    BOOL bPrevBlink     : 1;
    BOOL bPrevURL       : 1;
    BOOL bColor         : 1;

public:
    SwTxtCharFmt( const SwFmtCharFmt& rAttr, xub_StrLen nStart, xub_StrLen nEnd );
    ~SwTxtCharFmt( );

    // werden vom SwFmtCharFmt hierher weitergeleitet
    virtual void Modify( SfxPoolItem*, SfxPoolItem* );    // SwClient
    virtual BOOL GetInfo( SfxPoolItem& rInfo ) const;

    // erfrage und setze den TxtNode Pointer
    inline const SwTxtNode& GetTxtNode() const;
    void ChgTxtNode( const SwTxtNode* pNew ) { pMyTxtNd = (SwTxtNode*)pNew; }

};

// ATT_HARDBLANK ******************************

// ATT_XNLCONTAINERITEM ******************************

// ******************************

class SwTxtRuby : public SwTxtAttrEnd, public SwClient
{

public:
    SwTxtRuby( const SwFmtRuby& rAttr, xub_StrLen nStartIn, xub_StrLen nEndIn ):
                         SwTxtAttrEnd( (SfxPoolItem &)rAttr, nStartIn, nEndIn )
    { DBG_BF_ASSERT(0, "STRIP"); };

};

// ******************************

// --------------- Inline Implementierungen ------------------------

inline const SwTxtNode& SwTxtCharFmt::GetTxtNode() const
{
    OSL_ENSURE( pMyTxtNd, "SwTxtCharFmt:: wo ist mein TextNode?" );
    return *pMyTxtNd;
}

} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
