/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: acmplwrd.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 15:46:29 $
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
#ifndef _ACMPLWRD_HXX
#define _ACMPLWRD_HXX


#define _SVSTDARR_STRINGSISORTDTOR
#include <svtools/svstdarr.hxx>
namespace binfilter {

class SwDoc;
class SwAutoCompleteWord_Impl;
class SwAutoCompleteClient;

class SwAutoCompleteWord
{
    friend class SwAutoCompleteClient;

    SvStringsISortDtor aWordLst; // contains extended strings carrying source information
    SvPtrarr aLRULst;

    SwAutoCompleteWord_Impl* pImpl;
    USHORT nMaxCount, nMinWrdLen;
    BOOL bLockWordLst;

    void DocumentDying(const SwDoc& rDoc);
public:
    SwAutoCompleteWord( USHORT nWords = 500, USHORT nMWrdLen = 10 );
    ~SwAutoCompleteWord();

    BOOL InsertWord( const String& rWord, SwDoc& rDoc );
//STRIP001  BOOL RemoveWord( const String& rWord );
//STRIP001  BOOL SearchWord( const String& rWord, USHORT* pFndPos = 0 ) const;

//STRIP001  BOOL GetRange( const String& rWord, USHORT& rStt, USHORT& rEnd ) const;

//STRIP001  BOOL SetToTop( const String& rWord );

    USHORT Count() const { return aWordLst.Count(); }

    const String& operator[]( USHORT n ) const { return *aWordLst[ n ]; }

    BOOL IsLockWordLstLocked() const        { return bLockWordLst; }
    void SetLockWordLstLocked( BOOL bFlag ) { bLockWordLst = bFlag; }

    USHORT GetMaxCount() const              { return nMaxCount; }
//STRIP001  void SetMaxCount( USHORT n );

    USHORT GetMinWordLen() const                { return nMinWrdLen; }
//STRIP001  void SetMinWordLen( USHORT n );

    const SvStringsISortDtor& GetWordList() const { return aWordLst; }
//STRIP001  void CheckChangedList( const SvStringsISortDtor& rNewLst );
};


} //namespace binfilter
#endif
