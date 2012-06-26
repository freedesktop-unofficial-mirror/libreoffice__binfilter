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

#ifndef _SBXCONV_HXX
#define _SBXCONV_HXX

#include "sbxdec.hxx"

namespace binfilter {

class SbxINT64Converter
{
public:
    static BigInt SbxINT64_2_BigInt( const SbxINT64 &r );
    static BOOL BigInt_2_SbxINT64( const BigInt& b, SbxINT64 *p );
    static BigInt SbxUINT64_2_BigInt( const SbxUINT64 &r );
    static BOOL BigInt_2_SbxUINT64( const BigInt& b, SbxUINT64 *p );
};

// SBXSCAN.CXX
extern void ImpCvtNum( double nNum, short nPrec, String& rRes, BOOL bCoreString=FALSE );
extern SbxError ImpScan
    ( const String& rSrc, double& nVal, SbxDataType& rType, USHORT* pLen,
      BOOL bAllowIntntl=FALSE, BOOL bOnlyIntntl=FALSE );

// SBXINT.CXX

double      ImpRound( double );
INT16       ImpGetInteger( const SbxValues* );
void        ImpPutInteger( SbxValues*, INT16 );
sal_Int64   ImpGetInt64( const SbxValues* );
void        ImpPutInt64( SbxValues*, sal_Int64 );
sal_uInt64  ImpGetUInt64( const SbxValues* );
void        ImpPutUInt64( SbxValues*, sal_uInt64 );

sal_Int64   ImpDoubleToSalInt64( double d );
sal_uInt64  ImpDoubleToSalUInt64( double d );
double      ImpSalUInt64ToDouble( sal_uInt64 n );

// SBXLNG.CXX

INT32   ImpGetLong( const SbxValues* );
void    ImpPutLong( SbxValues*, INT32 );

// SBXSNG.CXX

float   ImpGetSingle( const SbxValues* );
void    ImpPutSingle( SbxValues*, float );

// SBXDBL.CXX

double  ImpGetDouble( const SbxValues* );
void    ImpPutDouble( SbxValues*, double, BOOL bCoreString=FALSE );

#if FALSE
// SBX64.CXX

SbxINT64  ImpGetINT64( const SbxValues* );
void      ImpPutINT64( SbxValues*, const SbxINT64& );
SbxUINT64 ImpGetUINT64( const SbxValues* );
void      ImpPutUINT64( SbxValues*, const SbxUINT64& );
#endif

// SBXCURR.CXX

SbxUINT64 ImpDoubleToUINT64( double );
double    ImpUINT64ToDouble( const SbxUINT64& );
SbxINT64  ImpDoubleToINT64( double );
double    ImpINT64ToDouble( const SbxINT64& );

#if TRUE
INT32     ImpGetCurrLong( const SbxValues* );
void      ImpPutCurrLong( SbxValues*, INT32 );
INT32     ImpDoubleToCurrLong( double );
double    ImpCurrLongToDouble( INT32 );
#endif

SbxINT64  ImpGetCurrency( const SbxValues* );
void      ImpPutCurrency( SbxValues*, const SbxINT64& );
inline
SbxINT64  ImpDoubleToCurrency( double d )
          { return ImpDoubleToINT64( d * CURRENCY_FACTOR ); }
inline
double    ImpCurrencyToDouble( const SbxINT64 &r )
          { return ImpINT64ToDouble( r ) / CURRENCY_FACTOR; }


// SBXDEC.CXX

SbxDecimal* ImpCreateDecimal( SbxValues* p );
SbxDecimal* ImpGetDecimal( const SbxValues* p );
void ImpPutDecimal( SbxValues* p, SbxDecimal* pDec );

// SBXDATE.CXX

double  ImpGetDate( const SbxValues* );
void    ImpPutDate( SbxValues*, double );

// SBXSTR.CXX

String  ImpGetString( const SbxValues* );
String  ImpGetCoreString( const SbxValues* );
void    ImpPutString( SbxValues*, const String* );

// SBXCHAR.CXX

sal_Unicode ImpGetChar( const SbxValues* );
void    ImpPutChar( SbxValues*, sal_Unicode );

// SBXBYTE.CXX
BYTE    ImpGetByte( const SbxValues* );
void    ImpPutByte( SbxValues*, BYTE );

// SBXUINT.CXX

UINT16  ImpGetUShort( const SbxValues* );
void    ImpPutUShort( SbxValues*, UINT16 );

// SBXULNG.CXX

UINT32  ImpGetULong( const SbxValues* );
void    ImpPutULong( SbxValues*, UINT32 );

// SBXBOOL.CXX

enum SbxBOOL ImpGetBool( const SbxValues* );
void    ImpPutBool( SbxValues*, INT16 );

}

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
