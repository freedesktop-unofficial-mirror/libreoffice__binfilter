/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2000, 2010 Oracle and/or its affiliates.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/
#ifndef _WRTW4W_HXX
#define _WRTW4W_HXX

#include <bf_svtools/bf_solar.h>

#include <swtypes.hxx>
#include <shellio.hxx>
#include <horiornt.hxx>
class SvMemoryStream;
namespace binfilter {

// einige Forward Deklarationen

class SvxBoxItem;
class SvxFontItem;
class SwAttrSet;
class SwDoc;
class SwFlyFrmFmt;
class SwFmt;
class SwFrmFmt;
class SwGrfNode;
class SwPageDesc;
class SwTable;
class SwTableLine;
class SwTableNode;
class SwTxtFmtColl;
struct SwPosition;

#define cW4W_BEGICF     '\x1b'
#define cW4W_LED        '\x1d'
#define cW4W_TXTERM     '\x1f'
#define cW4W_RED        '\x1e'

#ifdef JP_STR_OPTIMIERUNG
    JP 23.09.94: leider kann der MAC-Compiler keine String-Concatinierung

#define sW4W_BEGICF     "\x1b"
#define sW4W_LED        "\x1d"
#define sW4W_TXTERM     "\x1f"
#define sW4W_RED        "\x1e"

// lasse den Compiler die Strings zusammenbauen!
#define CNCT_STR2(a,b)                          ( a b )
#define CNCT_STR3(a,b,c)                        ( a b c )
#define CNCT_STR4(a,b,c,d)                      ( a b c d )
#define CNCT_STR5(a,b,c,d,e)                    ( a b c d e )
#define CNCT_STR6(a,b,c,d,e,f)                  ( a b c d e f )
#define CNCT_STR7(a,b,c,d,e,f,g)                ( a b c d e f g )
#define CNCT_STR12(a,b,c,d,e,f,g,h,i,j,k,l)     ( a b c d e f g h i j k l )

#define CNCT_STR1_RECSTT(a)         ( sW4W_BEGICF sW4W_LED a )
#define CNCT_STR2_RECSTT(a,b)       ( sW4W_BEGICF sW4W_LED a b )
#define CNCT_STR3_RECSTT(a,b,c)     ( sW4W_BEGICF sW4W_LED a b c )
#define CNCT_STR4_RECSTT(a,b,c,d)   ( sW4W_BEGICF sW4W_LED a b c d )

#endif

extern const sal_Char sW4W_RECBEGIN[3]; // W4W_BEGICF W4W_LED
extern const sal_Char sW4W_TERMEND[3];  // W4W_TXTREM W4W_RED


SvStream& W4WOutHex( SvStream& rStrm, USHORT nHex );
SvStream& W4WOutHex4( SvStream& rStrm, USHORT nHex );
SvStream& W4WOutLong( SvStream& rStrm, long nVal );
SvStream& W4WOutULong( SvStream& rStrm, ULONG nVal );


} //namespace binfilter
#endif  //  _WRTW4W_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
