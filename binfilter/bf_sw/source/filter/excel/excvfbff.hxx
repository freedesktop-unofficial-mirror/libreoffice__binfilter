/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: excvfbff.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: kz $ $Date: 2006-11-08 15:42:11 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/
#ifndef _EXCVFBFF_HXX
#define _EXCVFBFF_HXX

#ifndef _SOLAR_H
#include <tools/solar.h>
#endif
class String;
namespace binfilter {



class ValueFormBuffer;

#if defined(BLC) || defined(MAC)
// BLC will es auf jeden Fall hier
typedef void                ( ValueFormBuffer::*Fkt_rString )( String & );
typedef ULONG               ( ValueFormBuffer::*Fkt_USHORT )( USHORT );
#endif

class ValueFormBuffer
    {
    private:
#if !defined(BLC) && !defined(MAC)
// MSC will es auf jeden Fall hier
        typedef void        ( ValueFormBuffer::*Fkt_rString )( String & );
        typedef ULONG       ( ValueFormBuffer::*Fkt_USHORT )( USHORT );
#endif

        ULONG               *pHandles;      // Array mit Handles...
        USHORT              nMax;           // Groesse des Arrays
        USHORT              nCount;         // Index des naechsten freien Eintrags
        ULONG               nDefaultHandle;

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
        ULONG               __GetValueFormat( USHORT nExcIndex );
                            // fuer n-te Nutzung
        void                _NewValueFormatX( String &rFormString );
        void                _NewValueFormat5( String &rFormString );
        ULONG               _GetValueFormatX5( USHORT nExcIndex );
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

