/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: errhdl.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 15:57:33 $
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
#ifndef _ERRHDL_HXX
#define _ERRHDL_HXX

#ifndef PRODUCT

#ifndef _SOLAR_H
#include <tools/solar.h>
#endif
#ifndef _SAL_TYPES_H_
#include <sal/types.h>
#endif

namespace binfilter {
// -----------------------------------------------------------------------
// Ausgabe einer Fehlermeldung inkl. Dateiname und Zeilennummer
// wo der Fehler auftrat.
// Die Funktion darf nicht direkt benutzt werden!
// -----------------------------------------------------------------------
extern void AssertFail( const sal_Char*, const sal_Char*, USHORT );
extern void AssertFail( USHORT, const sal_Char*, USHORT );

extern BOOL bAssert;                // TRUE, wenn eine ASSERT-Box hochkam
#ifdef WIN
//MSC (7.0) machts nur mit static, ZTC in inlines nur ohne...
#define ASSERT( cond, message ) \
    if( !(cond) ) { \
        static const char __FAR_DATA _pErrorText[] = #message; \
        static const char __FAR_DATA _pFileName[]  = __FILE__; \
        ::binfilter::AssertFail( _pErrorText, _pFileName, __LINE__ ); \
    }
#else
#define ASSERT( cond, message ) \
    if( !(cond) ) { \
        const char   *_pErrorText = #message; \
        const char   *_pFileName  = __FILE__; \
       ::binfilter::AssertFail( _pErrorText, _pFileName, __LINE__ ); \
    }
#endif

// -----------------------------------------------------------------------
// Prueft ob die angegebene Bedingung wahr ist, wenn nicht wird eine
// Fehlermeldung die ueber die ID Identifiziert wird, ausgegeben.
// -----------------------------------------------------------------------
#ifdef WIN
//MSC (7.0) machts nur mit static, ZTC in inlines nur ohne...
#define ASSERT_ID( cond, id )   \
    if( !(cond) ) { \
        static const char __FAR_DATA _pFileName[]  = __FILE__;  \
        ::binfilter::AssertFail( (USHORT)id, _pFileName, __LINE__ );    \
    }
#else
#define ASSERT_ID( cond, id ) \
    if( !(cond) ) { \
        const char   *_pFileName  = __FILE__; \
       ::binfilter::AssertFail( (USHORT)id, _pFileName, __LINE__ ); \
    }
#endif
} //namespace binfilter

// -----------------------------------------------------------------------
// Beim Bilden der Produktversion werden alle Debug-Utilities automatisch
// ignoriert
// -----------------------------------------------------------------------
#else // PRODUCT

namespace binfilter {
#define ASSERT( cond, message )     ;
#define ASSERT_ID( cond, id )       ;
} //namespace binfilter

#endif // PRODUCT

#endif
