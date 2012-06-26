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
#ifndef _FMTHDFT_HXX
#define _FMTHDFT_HXX

#include <bf_svtools/bf_solar.h>

#include <format.hxx>
class IntlWrapper;
namespace binfilter {

class SwFrmFmt;



//Kopfzeile, fuer Seitenformate
//Client von FrmFmt das den Header beschreibt.

class SwFmtHeader: public SfxPoolItem, public SwClient
{
    BOOL bActive;       //Nur zur Steuerung (Erzeugung des Inhaltes)

public:
    SwFmtHeader( BOOL bOn = FALSE );
    SwFmtHeader( SwFrmFmt *pHeaderFmt );
    SwFmtHeader( const SwFmtHeader &rCpy );
    ~SwFmtHeader();
    SwFmtHeader& operator=( const SwFmtHeader &rCpy );

    TYPEINFO();

    // "pure virtual Methoden" vom SfxPoolItem
    virtual int             operator==( const SfxPoolItem& ) const;
    virtual SfxPoolItem*    Clone( SfxItemPool* pPool = 0 ) const;
    virtual SfxPoolItem*    Create(SvStream &, USHORT nVer) const;
    virtual SvStream&       Store(SvStream &rStream, USHORT) const { return rStream; }

    const SwFrmFmt *GetHeaderFmt() const { return (SwFrmFmt*)pRegisteredIn; }
          SwFrmFmt *GetHeaderFmt()       { return (SwFrmFmt*)pRegisteredIn; }

    BOOL IsActive() const { return bActive; }
    void SetActive( BOOL bNew = TRUE ) { bActive = bNew; }
};

//Fusszeile, fuer Seitenformate
//Client von FrmFmt das den Footer beschreibt.

class SwFmtFooter: public SfxPoolItem, public SwClient
{
    BOOL bActive;       //Nur zur Steuerung (Erzeugung des Inhaltes)

public:
    SwFmtFooter( BOOL bOn = FALSE );
    SwFmtFooter( SwFrmFmt *pFooterFmt );
    SwFmtFooter( const SwFmtFooter &rCpy );
    ~SwFmtFooter();
    SwFmtFooter& operator=( const SwFmtFooter &rCpy );

    TYPEINFO();

    // "pure virtual Methoden" vom SfxPoolItem
    virtual int             operator==( const SfxPoolItem& ) const;
    virtual SfxPoolItem*    Clone( SfxItemPool* pPool = 0 ) const;
    virtual SfxPoolItem*    Create(SvStream &, USHORT nVer) const;
    virtual SvStream&       Store(SvStream &rStream, USHORT) const { return rStream; }

    const SwFrmFmt *GetFooterFmt() const { return (SwFrmFmt*)pRegisteredIn; }
          SwFrmFmt *GetFooterFmt()       { return (SwFrmFmt*)pRegisteredIn; }

    BOOL IsActive() const { return bActive; }
    void SetActive( BOOL bNew = TRUE ) { bActive = bNew; }
};

inline const SwFmtHeader &SwAttrSet::GetHeader(BOOL bInP) const
    { return (const SwFmtHeader&)Get( RES_HEADER,bInP); }
inline const SwFmtFooter &SwAttrSet::GetFooter(BOOL bInP) const
    { return (const SwFmtFooter&)Get( RES_FOOTER,bInP); }

inline const SwFmtHeader &SwFmt::GetHeader(BOOL bInP) const
    { return aSet.GetHeader(bInP); }
inline const SwFmtFooter &SwFmt::GetFooter(BOOL bInP) const
    { return aSet.GetFooter(bInP); }

} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
