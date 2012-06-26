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
#ifndef _FMTURL_HXX
#define _FMTURL_HXX

#include <bf_svtools/bf_solar.h>


#include <format.hxx>
class IntlWrapper;

namespace binfilter {
class ImageMap;


// URL, ServerMap und ClientMap

class SwFmtURL: public SfxPoolItem
{
    String    sTargetFrameName; // in diesen Frame soll die URL
    String    sURL;             //Einfache URL
    String    sName;            // Name des Anchors
    ImageMap *pMap;             //ClientSide Images

    BOOL      bIsServerMap;     //mit der URL eine ServerSideImageMap

    SwFmtURL& operator=( const SwFmtURL& );

public:
    SwFmtURL();
    SwFmtURL( const SwFmtURL& );
    ~SwFmtURL();

    // "pure virtual Methoden" vom SfxPoolItem
    virtual int             operator==( const SfxPoolItem& ) const;
    virtual SfxPoolItem*    Clone( SfxItemPool* pPool = 0 ) const;
    virtual SfxPoolItem*    Create(SvStream &, USHORT nVer) const;
    virtual SvStream&       Store(SvStream &rStream, USHORT) const { return rStream; }
    virtual USHORT          GetVersion( USHORT nFFVer ) const;
    virtual bool            QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;
    virtual bool            PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 );

    void SetTargetFrameName( const String& rStr ) { sTargetFrameName = rStr; }
    void SetURL( const String &rURL, BOOL bServerMap );
    void SetMap( const ImageMap *pM );  //Pointer wird kopiert!

    const String   &GetTargetFrameName()const { return sTargetFrameName; }
    const String   &GetURL()            const { return sURL; }
          BOOL      IsServerMap()       const { return bIsServerMap; }
    const ImageMap *GetMap()            const { return pMap; }
          ImageMap *GetMap()                  { return pMap; }

    const String& GetName() const           { return sName; }
    void SetName( const String& rNm )       { sName = rNm; }
};


inline const SwFmtURL &SwAttrSet::GetURL(BOOL bInP) const
    { return (const SwFmtURL&)Get( RES_URL,bInP); }

inline const SwFmtURL &SwFmt::GetURL(BOOL bInP) const
    { return aSet.GetURL(bInP); }

} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
