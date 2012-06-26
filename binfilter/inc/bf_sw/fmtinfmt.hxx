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
#ifndef _FMTINFMT_HXX
#define _FMTINFMT_HXX

#include <bf_svtools/bf_solar.h>


#include <bf_svtools/poolitem.hxx>

class IntlWrapper;

namespace binfilter {

class SvxMacro;
class SvxMacroTableDtor;
class SwTxtINetFmt;
// ATT_INETFMT *********************************************

class SwFmtINetFmt: public SfxPoolItem
{
    friend class SwTxtINetFmt;

    String aURL;                    // die URL
    String aTargetFrame;            // in diesen Frame soll die URL
    String aINetFmt;
    String aVisitedFmt;
    String aName;                   // Name des Links
    SvxMacroTableDtor* pMacroTbl;
    SwTxtINetFmt* pTxtAttr;         // mein TextAttribut
    USHORT nINetId;
    USHORT nVisitedId;
public:
    SwFmtINetFmt( const String& rURL, const String& rTarget );
    SwFmtINetFmt( const SwFmtINetFmt& rAttr );
    SwFmtINetFmt();                     // for TypeInfo
    virtual ~SwFmtINetFmt();

    TYPEINFO();

    // "pure virtual Methoden" vom SfxPoolItem
    virtual int             operator==( const SfxPoolItem& ) const;
    virtual SfxPoolItem*    Clone( SfxItemPool* pPool = 0 ) const;
    virtual SfxPoolItem*    Create(SvStream &, USHORT nVer) const;
    virtual SvStream&       Store(SvStream &rStream, USHORT) const { return rStream; }

    virtual bool            QueryValue( ::com::sun::star::uno::Any& rVal,
                                        BYTE nMemberId = 0 ) const;
    virtual bool            PutValue( const ::com::sun::star::uno::Any& rVal,
                                        BYTE nMemberId = 0 );

    virtual USHORT          GetVersion( USHORT nFFVer ) const;

    const SwTxtINetFmt* GetTxtINetFmt() const   { return pTxtAttr; }
    SwTxtINetFmt* GetTxtINetFmt()               { return pTxtAttr; }

    const String& GetValue() const          { return aURL; }
    void SetValue( const String& rS )       { aURL = rS; }

    const String& GetName() const           { return aName; }
    void SetName( const String& rNm )       { aName = rNm; }

    const String& GetTargetFrame() const    { return aTargetFrame; }
    void SetTargetFrame( const String& rNm ){ aTargetFrame = rNm; }

    const String& GetINetFmt() const        { return aINetFmt; }
    void SetINetFmt( const String& rNm )    { aINetFmt = rNm; }

    const String& GetVisitedFmt() const     { return aVisitedFmt; }
    void SetVisitedFmt( const String& rNm ) { aVisitedFmt = rNm; }

    USHORT GetINetFmtId() const             { return nINetId; }
    void SetINetFmtId( USHORT nNew )        { nINetId = nNew; }

    USHORT GetVisitedFmtId() const          { return nVisitedId; }
    void SetVisitedFmtId( USHORT nNew )     { nVisitedId = nNew; }

    // setze eine neue oder loesche die akt. MakroTabelle
    const SvxMacroTableDtor* GetMacroTbl() const    { return pMacroTbl; }

    // setze / erfrage ein Makro
/*N #i27164#*/  void SetMacro( USHORT nEvent, const SvxMacro& rMacro );
    const SvxMacro* GetMacro( USHORT nEvent ) const;
};


} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
