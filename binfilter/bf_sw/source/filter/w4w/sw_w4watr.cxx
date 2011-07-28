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
/*
 * Dieses File enthaelt alle Ausgabe-Funktionen des W4W-Writers;
 * fuer alle Nodes, Attribute, Formate und Chars.
 */
#ifdef _MSC_VER
#pragma hdrstop
#endif

#include <hintids.hxx>

#include <bf_svtools/whiter.hxx>
#include <bf_svx/hyznitem.hxx>
#include <bf_svx/langitem.hxx>
#include <bf_svx/orphitem.hxx>
#include <bf_svx/tstpitem.hxx>
#include <bf_svx/spltitem.hxx>
#include <bf_svx/widwitem.hxx>
#include <bf_svx/adjitem.hxx>
#include <bf_svx/cmapitem.hxx>
#include <bf_svx/lspcitem.hxx>
#include <bf_svx/kernitem.hxx>
#include <bf_svx/wghtitem.hxx>
#include <bf_svx/udlnitem.hxx>
#include <bf_svx/escpitem.hxx>
#include <bf_svx/crsditem.hxx>
#include <bf_svx/colritem.hxx>
#include <bf_svx/brkitem.hxx>
#include <bf_svx/postitem.hxx>
#include <bf_svx/shdditem.hxx>
#include <bf_svx/ulspitem.hxx>
#include <bf_svx/lrspitem.hxx>
#include <bf_svx/fontitem.hxx>
#include <bf_svx/fhgtitem.hxx>


#include <fmtftn.hxx>
#include <txtftn.hxx>
#include <fmtpdsc.hxx>
#include <fmthdft.hxx>
#include <fmtcntnt.hxx>
#include <fmtfsize.hxx>
#include <fmtfld.hxx>
#include <frmatr.hxx>
#include <charatr.hxx>
#include <ftninfo.hxx>
#include <ndtxt.hxx>
#include <doc.hxx>
#include <pam.hxx>
#include <paratr.hxx>
#include <fldbas.hxx>          // fuer SwField ...
#include <ndgrf.hxx>
#include <grfatr.hxx>
#include <fmtcol.hxx>
#include <bookmrk.hxx>      // fuer SwBookmark ...
#include <pagedesc.hxx>     // fuer SwPageDesc...
#include <pageiter.hxx>
#include <wrtw4w.hxx>
namespace binfilter {


/*
 * um nicht immer wieder nach einem Update festzustellen, das irgendwelche
 * Hint-Ids dazugekommen sind, wird hier definiert, die Groesse der Tabelle
 * definiert und mit der akt. verglichen. Bei unterschieden wird der
 * Compiler schon meckern.
 *
 * diese Section und die dazugeherigen Tabellen muessen in folgenden Files
 * gepflegt werden: rtf\rtfatr.cxx, sw6\sw6atr.cxx, w4w\w4watr.cxx
 */

#if !defined(MSC) && !defined(UNX) && !defined(PPC) && !defined(CSET) && !defined(__MINGW32__) && !defined(OS2)

#define ATTRFNTAB_SIZE 130
#if ATTRFNTAB_SIZE != POOLATTR_END - POOLATTR_BEGIN
#error "Attribut-Tabelle ist ungueltigt. Wurden neue Hint-ID's zugefuegt ??"
#endif

#ifdef FORMAT_TABELLE
// da sie nicht benutzt wird!
#define FORMATTAB_SIZE 7
#if FORMATTAB_SIZE != RES_FMT_END - RES_FMT_BEGIN
#error "Format-Tabelle ist ungueltigt. Wurden neue Hint-ID's zugefuegt ??"
#endif
#endif

#define NODETAB_SIZE 3
#if NODETAB_SIZE != RES_NODE_END - RES_NODE_BEGIN
#error "Node-Tabelle ist ungueltigt. Wurden neue Hint-ID's zugefuegt ??"
#endif

#endif



//-----------------------------------------------------------------------

// einige Forward Deklarationen

#define OUTRECORD(rStrm,pStr)   rStrm << sW4W_RECBEGIN << pStr << cW4W_RED

inline int HI_BYTE( USHORT n )  { return (int)( ( n >> 8 ) & 0xff );  }
inline int LO_BYTE( USHORT n )  { return (int)( n & 0xff ); }


/* Ausgabe der Nodes */

/*
 *  Ausgabe der Texte-Attribute:
 *      Die Text-Attribute sind in einem VarArray nach ihren Start-Positionen
 *      sortiert. Fuer den W4W-Writer ist aber auch das Ende von Bedeutung.
 *      Darum die Idee, sobald im SwpHints-Array ein Attribut mit der Start-
 *      Position gefunden wurde, in einem Sortierten-Array die Endposition
 *      zu speichern. Sobald der Writer die Position erreicht hat, wird die
 *      schliessende Klammer ausgegeben und die Position aus dem Sort.Array
 *      geloescht.
 */

struct W4WSttEndPos
{
    USHORT nFontSize, nFontId;
    const SwTxtAttr* pTxtAttr;
    W4WSttEndPos( const SwTxtAttr* pTxtAt, USHORT nFSize, USHORT nFId );
    W4WSttEndPos( const W4WSttEndPos & rSEPos );
    BOOL operator<( const W4WSttEndPos & rSEPos );
};

W4WSttEndPos::W4WSttEndPos( const SwTxtAttr* pTxtAt, USHORT nFSize, USHORT nFId )
    : nFontSize(nFSize)
    , nFontId( nFId )
    , pTxtAttr(pTxtAt)
{}

W4WSttEndPos::W4WSttEndPos( const W4WSttEndPos & rSEPos )
    : nFontSize( rSEPos.nFontSize )
    , nFontId( rSEPos.nFontId )
    , pTxtAttr( rSEPos.pTxtAttr)
{}

BOOL W4WSttEndPos::operator<( const W4WSttEndPos & rSEPos )
{
    USHORT nEnd1, nEnd2;
    if( ( nEnd1 = *pTxtAttr->GetEnd() ) < ( nEnd2 = *rSEPos.pTxtAttr->GetEnd() ) )
        return TRUE;
    if( nEnd1 == nEnd2 )
        return *pTxtAttr->GetStart() > *rSEPos.pTxtAttr->GetStart();
    return FALSE;
}

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
