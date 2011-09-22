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
#ifndef _FMTFLCNT_HXX
#define _FMTFLCNT_HXX


#include <bf_svtools/poolitem.hxx>
namespace binfilter {

class SwFrmFmt;
class SwTxtFlyCnt;
// ATT_FLYCNT *******************************************************

class SwFmtFlyCnt : public SfxPoolItem
{
    friend class SwTxtFlyCnt;
    SwTxtFlyCnt* pTxtAttr;      // mein TextAttribut
    SwFrmFmt* pFmt;             // mein Fly/DrawFrame-Format
    // geschuetzter CopyCtor
    SwFmtFlyCnt& operator=(const SwFmtFlyCnt& rFlyCnt);

public:
    SwFmtFlyCnt( SwFrmFmt *pFrmFmt );
    // "pure virtual Methoden" vom SfxPoolItem
    virtual int             operator==( const SfxPoolItem& ) const { DBG_BF_ASSERT(0, "STRIP"); return 0; }
    virtual SfxPoolItem*    Clone( SfxItemPool* pPool = 0 ) const;
    virtual SfxPoolItem*    Create(SvStream &, USHORT nVer) const;
    virtual SvStream&       Store(SvStream &rStream, USHORT) const { return rStream; }

    inline SwFrmFmt *GetFrmFmt() const { return pFmt; }
    // fuer Undo: loesche "logisch" das FlyFrmFormat, wird sich im
    //          Undo-Object gemerkt.
    inline void SetFlyFmt( SwFrmFmt* pNew = 0 )   { pFmt = pNew; }

    const SwTxtFlyCnt *GetTxtFlyCnt() const { return pTxtAttr; }
          SwTxtFlyCnt *GetTxtFlyCnt()       { return pTxtAttr; }
};

} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
