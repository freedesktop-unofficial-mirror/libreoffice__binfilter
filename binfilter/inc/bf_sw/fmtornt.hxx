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
#ifndef _FMTORNT_HXX
#define _FMTORNT_HXX

#include <bf_svtools/bf_solar.h>

#include <swtypes.hxx>
#include <format.hxx>
#include <horiornt.hxx>
#include <orntenum.hxx>
class IntlWrapper;
namespace binfilter {



#define IVER_VERTORIENT_REL ((USHORT)0x0001)

class SwFmtVertOrient: public SfxPoolItem
{
    SwTwips          nYPos; //Enthaelt _immer_ die aktuelle RelPos.
    SwVertOrient     eOrient;
    SwRelationOrient eRelation;
public:
    TYPEINFO();
    SwFmtVertOrient( SwTwips nY = 0, SwVertOrient eVert = VERT_NONE,
                     SwRelationOrient eRel = PRTAREA );
    inline SwFmtVertOrient &operator=( const SwFmtVertOrient &rCpy );

    // "pure virtual Methoden" vom SfxPoolItem
    virtual int             operator==( const SfxPoolItem& ) const;
    virtual SfxPoolItem*    Clone( SfxItemPool* pPool = 0 ) const;
    virtual SfxPoolItem*    Create(SvStream &, USHORT nVer) const;
    virtual SvStream&       Store(SvStream &rStream, USHORT) const { return rStream; }
    virtual USHORT          GetVersion( USHORT nFFVer ) const;
    virtual bool            QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;
    virtual bool            PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 );

    SwVertOrient GetVertOrient() const { return eOrient; }
    SwRelationOrient GetRelationOrient() const { return eRelation; }
    void   SetVertOrient( SwVertOrient eNew ) { eOrient = eNew; }
    void   SetRelationOrient( SwRelationOrient eNew ) { eRelation = eNew; }

    SwTwips GetPos() const { return nYPos; }
    void    SetPos( SwTwips nNew ) { nYPos = nNew; }

    SwTwips GetPosConvertedFromSw31( const SvxULSpaceItem *pULSpace ) const;
};

//SwFmtHoriOrient, wie und woran orientiert --
//  sich der FlyFrm in der Hoizontalen ----------

#define IVER_HORIORIENT_TOGGLE ((USHORT)0x0001)
#define IVER_HORIORIENT_REL ((USHORT)0x0002)

class SwFmtHoriOrient: public SfxPoolItem
{
    SwTwips          nXPos; //Enthaelt _immer_ die aktuelle RelPos.
    SwHoriOrient     eOrient;
    SwRelationOrient eRelation;
    BOOL             bPosToggle : 1; // auf geraden Seiten Position spiegeln
public:
    TYPEINFO();
    SwFmtHoriOrient( SwTwips nX = 0, SwHoriOrient eHori = HORI_NONE,
        SwRelationOrient eRel = PRTAREA, BOOL bPos = FALSE );
    inline SwFmtHoriOrient &operator=( const SwFmtHoriOrient &rCpy );

    // "pure virtual Methoden" vom SfxPoolItem
    virtual int             operator==( const SfxPoolItem& ) const;
    virtual SfxPoolItem*    Clone( SfxItemPool* pPool = 0 ) const;
    virtual SfxPoolItem*    Create(SvStream &, USHORT nVer) const;
    virtual SvStream&       Store(SvStream &rStream, USHORT) const { return rStream; }
    virtual USHORT          GetVersion( USHORT nFFVer ) const;
    virtual bool            QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;
    virtual bool            PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 );

    SwHoriOrient GetHoriOrient() const { return eOrient; }
    SwRelationOrient GetRelationOrient() const { return eRelation; }
    void SetHoriOrient( SwHoriOrient eNew ) { eOrient = eNew; }
    void SetRelationOrient( SwRelationOrient eNew ) { eRelation = eNew; }

    SwTwips GetPos() const { return nXPos; }
    void    SetPos( SwTwips nNew ) { nXPos = nNew; }

    SwTwips GetPosConvertedFromSw31( const SvxLRSpaceItem *pLRSpace ) const;

    BOOL IsPosToggle() const { return bPosToggle; }
    void SetPosToggle( BOOL bNew ) { bPosToggle = bNew; }
};

inline SwFmtVertOrient &SwFmtVertOrient::operator=( const SwFmtVertOrient &rCpy )
{
    nYPos = rCpy.GetPos();
    eOrient = rCpy.GetVertOrient();
    eRelation = rCpy.GetRelationOrient();
    return *this;
}
inline SwFmtHoriOrient &SwFmtHoriOrient::operator=( const SwFmtHoriOrient &rCpy )
{
    nXPos = rCpy.GetPos();
    eOrient = rCpy.GetHoriOrient();
    eRelation = rCpy.GetRelationOrient();
    bPosToggle = rCpy.IsPosToggle();
    return *this;
}

inline const SwFmtVertOrient &SwAttrSet::GetVertOrient(BOOL bInP) const
    { return (const SwFmtVertOrient&)Get( RES_VERT_ORIENT,bInP); }
inline const SwFmtHoriOrient &SwAttrSet::GetHoriOrient(BOOL bInP) const
    { return (const SwFmtHoriOrient&)Get( RES_HORI_ORIENT,bInP); }

inline const SwFmtVertOrient &SwFmt::GetVertOrient(BOOL bInP) const
    { return aSet.GetVertOrient(bInP); }
inline const SwFmtHoriOrient &SwFmt::GetHoriOrient(BOOL bInP) const
    { return aSet.GetHoriOrient(bInP); }

} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
