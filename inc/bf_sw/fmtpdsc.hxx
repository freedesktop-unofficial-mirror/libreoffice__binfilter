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
#ifndef _FMTPDSC_HXX
#define _FMTPDSC_HXX

#include <bf_svtools/bf_solar.h>


#include <format.hxx>
class IntlWrapper;
namespace binfilter {

class SwPageDesc;
class SwHistory;
class SwPaM;


//Pagedescriptor
//Client vom SwPageDesc der durch das Attribut "beschrieben" wird.

#define IVER_FMTPAGEDESC_NOAUTO ((USHORT)0x0001)
#define IVER_FMTPAGEDESC_LONGPAGE   ((USHORT)0x0002)

class SwFmtPageDesc : public SfxPoolItem, public SwClient
{
    // diese "Doc"-Funktion ist friend, um nach dem kopieren das
    // Auto-Flag setzen zu koennen !!
    friend BOOL InsAttr( SwDoc*, const SwPaM &, const SfxItemSet&, USHORT,
                        SwHistory* );
    SwModify* pDefinedIn;       // Verweis auf das Objekt, in dem das
                                // Attribut gesetzt wurde (CntntNode/Format)
    USHORT nNumOffset;          // Seitennummer Offset
    USHORT nDescNameIdx;        // SW3-Reader: Stringpool-Index des Vorlagennamens

public:
    SwFmtPageDesc( const SwPageDesc *pDesc = 0 );
    SwFmtPageDesc( const SwFmtPageDesc &rCpy );
    SwFmtPageDesc &operator=( const SwFmtPageDesc &rCpy );
    ~SwFmtPageDesc();

    TYPEINFO();

    // "pure virtual Methoden" vom SfxPoolItem
    virtual int             operator==( const SfxPoolItem& ) const;
    virtual SfxPoolItem*    Clone( SfxItemPool* pPool = 0 ) const;
    virtual SfxPoolItem*    Create(SvStream &, USHORT nVer) const;
    virtual SvStream&       Store(SvStream &rStream, USHORT) const { return rStream; }
    virtual USHORT          GetVersion( USHORT nFFVer ) const;
    virtual bool            QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;
    virtual bool            PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 );

    virtual void Modify( SfxPoolItem *pOld, SfxPoolItem *pNew );

          SwPageDesc *GetPageDesc() { return (SwPageDesc*)GetRegisteredIn(); }
    const SwPageDesc *GetPageDesc() const { return (SwPageDesc*)GetRegisteredIn(); }

    USHORT  GetNumOffset() const        { return nNumOffset; }
    void    SetNumOffset( USHORT nNum ) { nNumOffset = nNum; }

    // erfrage/setze, wo drin das Attribut verankert ist
    inline const SwModify* GetDefinedIn() const { return pDefinedIn; }
    void ChgDefinedIn( const SwModify* pNew ) { pDefinedIn = (SwModify*)pNew; }

    // fuer den SW3-Reader:
    USHORT GetDescNameIdx() const { return nDescNameIdx; }
    void SetDescNameIdx( USHORT n ) { nDescNameIdx = n;  }
};


inline const SwFmtPageDesc &SwAttrSet::GetPageDesc(BOOL bInP) const
    { return (const SwFmtPageDesc&)Get( RES_PAGEDESC,bInP); }

inline const SwFmtPageDesc &SwFmt::GetPageDesc(BOOL bInP) const
    { return aSet.GetPageDesc(bInP); }

} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
