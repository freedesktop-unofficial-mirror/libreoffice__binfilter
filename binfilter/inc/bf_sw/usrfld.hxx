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
#ifndef _USRFLD_HXX
#define _USRFLD_HXX

#include <bf_svtools/bf_solar.h>

#include "fldbas.hxx"
namespace binfilter {

class SfxPoolItem;
class SwCalc;
class SwDoc;

/*--------------------------------------------------------------------
    Beschreibung: Benutzerfelder
 --------------------------------------------------------------------*/

class SwUserFieldType : public SwValueFieldType
{
    BOOL    bValidValue : 1;
    BOOL    bDeleted : 1;
    double  nValue;
    String  aName;
    String  aContent;
    USHORT  nType;

public:
    SwUserFieldType( SwDoc* pDocPtr, const String& );

    virtual const String&   GetName() const;
    virtual SwFieldType*    Copy() const;

    String                  Expand(sal_uInt32 nFmt, USHORT nSubType, USHORT nLng);

    String                  GetContent( sal_uInt32 nFmt = 0 );
           void             SetContent( const String& rStr, sal_uInt32 nFmt = 0 );

    inline BOOL             IsValid() const;
    inline void             ChgValid( BOOL bNew );


           double           GetValue(SwCalc& rCalc);    // Member nValue neu berrechnen
    inline double           GetValue() const;
    inline void             SetValue(const double nVal);

    inline USHORT           GetType() const;
    inline void             SetType(USHORT);

    BOOL                    IsDeleted() const       { return bDeleted; }
    void                    SetDeleted( BOOL b )    { bDeleted = b; }

    virtual BOOL        QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMId ) const;
    virtual BOOL        PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMId );
};

inline BOOL SwUserFieldType::IsValid() const
    { return bValidValue; }

inline void SwUserFieldType::ChgValid( BOOL bNew )
    { bValidValue = bNew; }

inline double SwUserFieldType::GetValue() const
    { return nValue; }

inline void SwUserFieldType::SetValue(const double nVal)
    { nValue = nVal; }

inline USHORT SwUserFieldType::GetType() const
    { return nType; }

inline void SwUserFieldType::SetType(USHORT nSub)
{
    nType = nSub;
    EnableFormat(!(nSub & GSE_STRING));
}

/*--------------------------------------------------------------------
    Beschreibung: Benutzerfelder
 --------------------------------------------------------------------*/

class SwUserField : public SwValueField
{
    USHORT  nSubType;

public:
    SwUserField(SwUserFieldType*, USHORT nSub = 0, sal_uInt32 nFmt = 0);

    virtual USHORT          GetSubType() const;
    virtual void            SetSubType(USHORT nSub);

    virtual double          GetValue() const;
    virtual void            SetValue( const double& rVal );

    virtual String          Expand() const;
    virtual SwField*        Copy() const;
    virtual String          GetCntnt(BOOL bName = FALSE) const;

    // Name kann nicht geaendert werden
    virtual const String&   GetPar1() const;

    // Inhalt
    virtual String          GetPar2() const;
    virtual void            SetPar2(const String& rStr);
    virtual BOOL        QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMId ) const;
    virtual BOOL        PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMId );
};

} //namespace binfilter
#endif // _USRFLD_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
