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

#ifndef _CSTITEM_HXX
#define _CSTITEM_HXX

#include <bf_svtools/bf_solar.h>

#include <tools/rtti.hxx>

#include <bf_svtools/poolitem.hxx>

class SvStream;

namespace binfilter {

enum CrawlStatus
{
    CSTAT_NEVER_UPD         = 0,        /* noch nie ueberprueft                         */
    CSTAT_IN_UPD            = 1,        /* Ueberpruefung laeuft                         */
    CSTAT_UPD_NEWER         = 2,        /* wurde ueberprueft und ist neuer              */
    CSTAT_UPD_NOT_NEWER     = 3,        /* wurde ueberprueft und ist nicht neuer        */
    CSTAT_UPD_CANCEL        = 4,        /* Ueberpruefung vom Benutzer abgebrochen       */
    CSTAT_ERR_GENERAL       = 5,        /* allgemeiner Fehler                           */
    CSTAT_ERR_NOTEXISTS     = 6,        /* Server existiert nicht                       */
    CSTAT_ERR_NOTREACHED    = 7,        /* Server nicht ereicht                         */
    CSTAT_UPD_IMMEDIATELY   = 8,        /* es wird gleich ueberprueftt                  */
    CSTAT_ERR_OFFLINE       = 9         /* Ueberpruefung nicht m?glich, da Offline      */
};

DBG_NAMEEX(SfxCrawlStatusItem)

// class SfxDateTimeRangeItem -------------------------------------------------

class SfxCrawlStatusItem : public SfxPoolItem
{
private:
            CrawlStatus     eStatus;
public:
            TYPEINFO();

            SfxCrawlStatusItem( const SfxCrawlStatusItem& rCpy );
            SfxCrawlStatusItem( USHORT nWhich, CrawlStatus eStat );
            ~SfxCrawlStatusItem() { DBG_DTOR(SfxCrawlStatusItem, 0); }

    virtual int             operator==( const SfxPoolItem& )            const;
    using SfxPoolItem::Compare;
    virtual int             Compare( const SfxPoolItem &rWith )         const;
    virtual SfxPoolItem*    Create( SvStream&, USHORT nItemVersion )    const;
    virtual SvStream& Store( SvStream& rStream, USHORT ) const { return rStream; }
    virtual SfxPoolItem*    Clone( SfxItemPool* pPool = 0 )             const;

    virtual SfxItemPresentation GetPresentation( SfxItemPresentation ePres,
                                    SfxMapUnit eCoreMetric,
                                    SfxMapUnit ePresMetric,
                                    XubString &rText,
                                    const ::IntlWrapper * pIntlWrapper = 0 )
        const;

    CrawlStatus             GetStatus() const { return eStatus; }
    void                    SetStatus(CrawlStatus eNew) { eStatus = eNew; }

    virtual bool PutValue  ( const ::com::sun::star::uno::Any& rVal,
                             BYTE nMemberId = 0 );
    virtual bool QueryValue( ::com::sun::star::uno::Any& rVal,
                             BYTE nMemberId = 0 ) const;
};

}

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
