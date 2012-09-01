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
#ifndef _PAM_HXX
#define _PAM_HXX

#include <bf_svtools/bf_solar.h>

#include <stddef.h>         // fuer MemPool
#include <tools/gen.hxx>
#include <tools/mempool.hxx>

#include <cshtyp.hxx>       // fuer die Funktions-Definitionen
#include <ring.hxx>         // Superklasse
#include <index.hxx>        // fuer SwIndex
#include <ndindex.hxx>      // fuer SwNodeIndex
namespace com { namespace sun { namespace star { namespace util {
    struct SearchOptions;
} } } }
namespace binfilter {
class SfxPoolItem;
class SfxItemSet;


class SwFmt;

class SwDoc;
class SwNode;
class SwCntntNode;
class SwNodes;
class SwPaM;


namespace utl {
    class TextSearch;
}

struct SwPosition
{
    SwNodeIndex nNode;
    SwIndex nContent;

    SwPosition( );
    SwPosition( const SwNode& rNode );
    SwPosition( const SwNodeIndex &rNode );
    SwPosition( const SwNodeIndex &rNode, const SwIndex &rCntnt );
    SwPosition( const SwPosition & );

    SwPosition &operator=(const SwPosition &);

    bool operator < (const SwPosition &) const;
    bool operator > (const SwPosition &) const;
    bool operator <=(const SwPosition &) const;
    bool operator >=(const SwPosition &) const;
    bool operator ==(const SwPosition &) const;
    bool operator !=(const SwPosition &) const;
};


// SwPointAndMark / SwPaM
struct SwMoveFnCollection;
typedef SwMoveFnCollection* SwMoveFn;
extern SwMoveFn fnMoveForward, fnMoveBackward;

typedef bool (*SwGoInDoc)( SwPaM& rPam, SwMoveFn fnMove );
extern SwGoInDoc fnGoDoc, fnGoNode, fnGoCntnt, fnGoCntntCells;

class SwPaM : public Ring
{
    SwPosition aBound1;
    SwPosition aBound2;
    SwPosition *pPoint;
    SwPosition *pMark;


public:
    SwPaM(){};
    SwPaM( const SwPosition& rPos, SwPaM* pRing = 0 );
    SwPaM( const SwPosition& rMk, const SwPosition& rPt, SwPaM* pRing = 0 );
    SwPaM( SwPaM & );
    SwPaM( const SwNode& rMk, const SwNode& rPt,
           long nMkOffset = 0, long nPtOffset = 0, SwPaM* pRing = 0 );
    SwPaM(  const SwNode& rMk, xub_StrLen nMkCntnt,
            const SwNode& rPt, xub_StrLen nPtCntnt, SwPaM* pRing = 0 );
    SwPaM( const SwNode& rNd, xub_StrLen nCntnt = 0, SwPaM* pRing = 0 );
    SwPaM( const SwNodeIndex& rNd, xub_StrLen nCntnt = 0, SwPaM* pRing = 0 );
    virtual ~SwPaM();

    // Bewegen des Cursors
    bool Move( SwMoveFn fnMove = fnMoveForward,
                    SwGoInDoc fnGo = fnGoCntnt );

    // Suchen

    virtual void SetMark();
    void DeleteMark() { pMark = pPoint; }
#ifndef DBG_UTIL
    void Exchange()
    {
        if(pPoint != pMark)
        {
            SwPosition *pTmp = pPoint;
            pPoint = pMark;
            pMark = pTmp;
        }
    }
#else
    void Exchange();
#endif
    /*
     * Undokumented Feature: Liefert zurueck, ob das Pam ueber
     * eine Selektion verfuegt oder nicht. Definition einer
     * Selektion: Point und Mark zeigen auf unterschiedliche
     * Puffer.
     */
    bool HasMark() const { return pPoint == pMark? FALSE : TRUE; }

    const SwPosition *GetPoint() const { return pPoint; }
          SwPosition *GetPoint()       { return pPoint; }
    const SwPosition *GetMark()  const { return pMark; }
          SwPosition *GetMark()        { return pMark; }

    const SwPosition *Start() const
                    { return (*pPoint) <= (*pMark)? pPoint: pMark; }
          SwPosition *Start()
                    { return (*pPoint) <= (*pMark)? pPoint: pMark; }
    const SwPosition *End()   const
                    { return (*pPoint) > (*pMark)? pPoint: pMark; }
          SwPosition *End()
                    { return (*pPoint) > (*pMark)? pPoint: pMark; }

    SwPaM& operator=( SwPaM & );

    // erfrage vom SwPaM den aktuellen Node/ContentNode am SPoint / Mark
    SwNode* GetNode( BOOL bPoint = TRUE ) const
    {
        return &( bPoint ? pPoint->nNode : pMark->nNode ).GetNode();
    }
    SwCntntNode* GetCntntNode( BOOL bPoint = TRUE ) const
    {
        return ( bPoint ? pPoint->nNode : pMark->nNode ).GetNode().GetCntntNode();
    }

    /**
       Normalizes PaM, i.e. sort point and mark.

       @param bPointFirst TRUE: If the point is behind the mark then swap.
                          FALSE: If the mark is behind the point then swap.
    */
    SwPaM & Normalize(BOOL bPointFirst = TRUE);

    // erfrage vom SwPaM das Dokument, in dem er angemeldet ist
    SwDoc* GetDoc() const { return pPoint->nNode.GetNode().GetDoc(); }
    SwPosition& GetBound( BOOL bOne = TRUE )
    {   return bOne ? aBound1 : aBound2; }
    const SwPosition& GetBound( BOOL bOne = TRUE ) const
    {   return bOne ? aBound1 : aBound2; }

    // erfrage die Seitennummer auf der der Cursor steht
    USHORT GetPageNum( BOOL bAtPoint = TRUE, const Point* pLayPos = 0 );

    DECL_FIXEDMEMPOOL_NEWDEL(SwPaM)
};


bool CheckNodesRange( const SwNodeIndex&, const SwNodeIndex&, bool );
bool GoInCntnt( SwPaM & rPam, SwMoveFn fnMove );


} //namespace binfilter
#endif  // _PAM_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
