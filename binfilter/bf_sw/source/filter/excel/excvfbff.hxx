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
#ifndef _EXCVFBFF_HXX
#define _EXCVFBFF_HXX

#include <bf_svtools/bf_solar.h>
class String;
namespace binfilter {



class ValueFormBuffer;

#if defined(MAC)
typedef void                ( ValueFormBuffer::*Fkt_rString )( String & );
typedef sal_uInt32          ( ValueFormBuffer::*Fkt_USHORT )( USHORT );
#endif

class ValueFormBuffer
    {
    private:
#if !defined(MAC)
// MSC will es auf jeden Fall hier
        typedef void        ( ValueFormBuffer::*Fkt_rString )( String & );
        typedef sal_uInt32  ( ValueFormBuffer::*Fkt_USHORT )( USHORT );
#endif

        sal_uInt32          *pHandles;      // Array mit Handles...
        USHORT              nMax;           // Groesse des Arrays
        USHORT              nCount;         // Index des naechsten freien Eintrags
        sal_uInt32          nDefaultHandle;

        // nur fuer Excel5
        static const USHORT nAnzBuiltin;    // bekannte Formate
        static const USHORT nNewFormats;    // selbstdefinierte
        static const sal_Char   *pBuiltinFormats[]; // vordefinierte Formate

        Fkt_rString         _NewValueFormat;
        Fkt_USHORT          _GetValueFormat;
        // ----------------------------------------------------------
        void                Init( void );
                            // fuer 1. Nutzung
        void                __NewValueFormat( String &rFormString );
        sal_uInt32          __GetValueFormat( USHORT nExcIndex );
                            // fuer n-te Nutzung
        void                _NewValueFormatX( String &rFormString );
        void                _NewValueFormat5( String &rFormString );
        sal_uInt32          _GetValueFormatX5( USHORT nExcIndex );
    public:
        ValueFormBuffer( const USHORT nSize = 2048 );
        ~ValueFormBuffer();

        inline void         NewValueFormat( String &rFormString );
        inline ULONG        GetValueFormat( USHORT nExcIndex );
#ifdef USED
        void                Reset( void );
#endif
    };

inline void ValueFormBuffer::NewValueFormat( String &rFormString )
    {
    ( this->*_NewValueFormat )( rFormString );
    }

inline ULONG ValueFormBuffer::GetValueFormat( USHORT nExcIndex )
    {
    return ( this->*_GetValueFormat )( nExcIndex );
    }


} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
