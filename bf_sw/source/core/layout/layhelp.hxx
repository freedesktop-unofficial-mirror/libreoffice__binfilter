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
#ifndef _LAYHELP_HXX
#define _LAYHELP_HXX

#include <bf_svtools/bf_solar.h>

#ifndef _SVSTDARR_HXX
#define _SVSTDARR_USHORTS
#define _SVSTDARR_ULONGS
#define _SVSTDARR_BYTES
#define _SVSTDARR_XUB_STRLEN
#include <bf_svtools/svstdarr.hxx>
#endif
#include <swrect.hxx>
class SvStream;
namespace binfilter {

class SwDoc;
class SwFrm;
class SwLayoutFrm;
class SwPageFrm;
class SwFlyFrm;
class SwSectionFrm;
class SwSectionNode;
class SwLayoutCache;


/*************************************************************************
 *                      class SwLayCacheImpl
 * contains the page break information and the text frame positions
 * of the document (after loading)
 * and is used inside the constructor of the layout rootframe to
 * insert content and text frames at the right pages.
 * For every page of the main text (body content, no footnotes, text frames etc.)
 * we have the nodeindex of the first content at the page,
 * the type of content ( table or paragraph )
 * and if it's not the first part of the table/paragraph,
 * the row/character-offset inside the table/paragraph.
 * The text frame positions are stored in the SwPageFlyCache array.
 *************************************************************************/

class SwFlyCache;
typedef SwFlyCache* SwFlyCachePtr;
SV_DECL_PTRARR_DEL( SwPageFlyCache, SwFlyCachePtr, 0, 4 )

class SwLayCacheImpl : public SvULongs
{
    SvXub_StrLens aOffset;
    SvUShorts aType;
    SwPageFlyCache aFlyCache;
    sal_Bool bUseFlyCache;

public:
    SwLayCacheImpl() : SvULongs( 20, 10 ), aOffset( 20, 10 ), aType( 20, 10 ) {}

    ULONG GetBreakIndex( USHORT nIdx ) const { return GetObject( nIdx ); }
    xub_StrLen GetBreakOfst( USHORT nIdx ) const { return aOffset[ nIdx ]; }
    USHORT GetBreakType( USHORT nIdx ) const { return aType[ nIdx ]; }

    USHORT GetFlyCount() const { return aFlyCache.Count(); }
    SwFlyCache *GetFlyCache( USHORT nIdx ) const { return aFlyCache[ nIdx ]; }

    sal_Bool IsUseFlyCache() const { return bUseFlyCache; }
};

/*************************************************************************
 *                      class SwActualSection
 * helps to create the sectionframes during the _InsertCnt-function
 * by controlling nested sections.
 *************************************************************************/

class SwActualSection
{
    SwActualSection *pUpper;
    SwSectionFrm    *pSectFrm;
    SwSectionNode   *pSectNode;
public:
    SwActualSection( SwActualSection *pUpper,
                     SwSectionFrm    *pSect,
                     SwSectionNode   *pNd );

    SwSectionFrm    *GetSectionFrm()                    { return pSectFrm; }
    void             SetSectionFrm( SwSectionFrm *p )   { pSectFrm = p; }
    SwSectionNode   *GetSectionNode()                   { return pSectNode;}
    SwActualSection *GetUpper()                         { return pUpper; }
};

/*************************************************************************
 *                      class SwLayHelper
 * helps during the _InsertCnt-function to create new pages.
 * If there's a layoutcache available, this information is used.
 *************************************************************************/

class SwLayHelper
{
    SwFrm* &rpFrm;
    SwFrm* &rpPrv;
    SwPageFrm* &rpPage;
    SwLayoutFrm* &rpLay;
    SwActualSection* &rpActualSection;
    BOOL &rbBreakAfter;
    SwDoc* pDoc;
    SwLayCacheImpl* pImpl;
    ULONG nMaxParaPerPage;
    ULONG nParagraphCnt;
    ULONG nStartOfContent;
    USHORT nIndex;                      // the index in the page break array
    USHORT nFlyIdx;                     // the index in the fly cache array
    BOOL bFirst : 1;
    void _CheckFlyCache( SwPageFrm* pPage );
public:
    SwLayHelper( SwDoc *pD, SwFrm* &rpF, SwFrm* &rpP, SwPageFrm* &rpPg,
            SwLayoutFrm* &rpL, SwActualSection* &rpA, BOOL &rBrk,
            ULONG nNodeIndex, BOOL bCache );
    ~SwLayHelper();
    ULONG CalcPageCount();
    BOOL CheckInsert( ULONG nNodeIndex );

    BOOL BreakPage( xub_StrLen& rOffs, ULONG nNodeIndex );
    BOOL CheckInsertPage();

    // Look for fresh text frames at this (new) page and set them to the right
    // position, if they are in the fly cache.
    void CheckFlyCache( SwPageFrm* pPage )
    { if( pImpl && nFlyIdx < pImpl->GetFlyCount() ) _CheckFlyCache( pPage ); }
};

#define SW_LAYCACHE_IO_REC_PAGES    'p'
#define SW_LAYCACHE_IO_REC_PARA     'P'
#define SW_LAYCACHE_IO_REC_TABLE    'T'
#define SW_LAYCACHE_IO_REC_FLY      'F'

#define SW_LAYCACHE_IO_VERSION_MAJOR    1
#define SW_LAYCACHE_IO_VERSION_MINOR    1

// Stored information about text frames:
class SwFlyCache : public SwRect // position and size
{
public:
    ULONG nOrdNum;      // Id to recognize text frames
    USHORT nPageNum;    // page number
    SwFlyCache( USHORT nP, ULONG nO, long nX1, long nY1, long nW, long nH ) :
        SwRect( nX1, nY1, nW, nH ), nOrdNum( nO ), nPageNum( nP ){}
};

} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
