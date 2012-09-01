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
#ifndef _FCHRFMT_HXX
#define _FCHRFMT_HXX

#include <bf_svtools/bf_solar.h>


#include <format.hxx>
class IntlWrapper;
namespace binfilter {

class SwCharFmt;
class SwTxtCharFmt;


// ATT_CHARFMT *********************************************


class SwFmtCharFmt: public SfxPoolItem, public SwClient
{
    friend class SwTxtCharFmt;
    SwTxtCharFmt* pTxtAttr;     // mein TextAttribut
public:
    SwFmtCharFmt( SwCharFmt *pFmt );
    SwFmtCharFmt( const SwFmtCharFmt& rAttr );
    ~SwFmtCharFmt();        // fuer SEXPORT
    TYPEINFO();

    // "pure virtual Methoden" vom SfxPoolItem
    virtual int             operator==( const SfxPoolItem& ) const;
    virtual SfxPoolItem*    Clone( SfxItemPool* pPool = 0 ) const;
    virtual SfxPoolItem*    Create(SvStream &, USHORT nVer) const;
    virtual SvStream&       Store(SvStream &rStream, USHORT) const { return rStream; }

    virtual SfxItemPresentation GetPresentation(
                SfxItemPresentation     /* ePres */,
                SfxMapUnit              /* eCoreMetric */,
                SfxMapUnit              /* ePresMetric */,
                String&                 /* rText */,
                const ::IntlWrapper*    /* pIntl */ = NULL
            ) const
            {   return SFX_ITEM_PRESENTATION_NONE; }

    virtual bool             QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;

    // an das SwTxtCharFmt weiterleiten (vom SwClient)
    virtual BOOL    GetInfo( SfxPoolItem& rInfo ) const;

    void SetCharFmt( SwFmt* pFmt ) { pFmt->Add(this); }
    SwCharFmt* GetCharFmt() const { return (SwCharFmt*)GetRegisteredIn(); }
};
} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
