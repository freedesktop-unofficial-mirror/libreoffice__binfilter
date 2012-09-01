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
#ifndef _SWTBLFMT_HXX
#define _SWTBLFMT_HXX

#include <frmfmt.hxx>
namespace binfilter {

class SwDoc;

class SwTableFmt : public SwFrmFmt
{
    friend class SwDoc;

protected:
    SwTableFmt( SwAttrPool& rPool, const sal_Char* pFmtNm,
                    SwFrmFmt *pDrvdFrm )
        : SwFrmFmt( rPool, pFmtNm, pDrvdFrm, RES_FRMFMT, aTableSetRange )
    {}
    SwTableFmt( SwAttrPool& rPool, const String &rFmtNm,
                    SwFrmFmt *pDrvdFrm )
        : SwFrmFmt( rPool, rFmtNm, pDrvdFrm, RES_FRMFMT, aTableSetRange )
    {}


public:
    TYPEINFO();     //Bereits in Basisklasse Client drin.

    DECL_FIXEDMEMPOOL_NEWDEL(SwTableFmt)
};

class SwTableLineFmt : public SwFrmFmt
{
    friend class SwDoc;

protected:
    SwTableLineFmt( SwAttrPool& rPool, const sal_Char* pFmtNm,
                    SwFrmFmt *pDrvdFrm )
        : SwFrmFmt( rPool, pFmtNm, pDrvdFrm, RES_FRMFMT, aTableLineSetRange )
    {}
    SwTableLineFmt( SwAttrPool& rPool, const String &rFmtNm,
                    SwFrmFmt *pDrvdFrm )
        : SwFrmFmt( rPool, rFmtNm, pDrvdFrm, RES_FRMFMT, aTableLineSetRange )
    {}

public:
    TYPEINFO();     //Bereits in Basisklasse Client drin.

    DECL_FIXEDMEMPOOL_NEWDEL(SwTableLineFmt)
};

class SwTableBoxFmt : public SwFrmFmt
{
    friend class SwDoc;

protected:
    SwTableBoxFmt( SwAttrPool& rPool, const sal_Char* pFmtNm,
                    SwFrmFmt *pDrvdFrm )
        : SwFrmFmt( rPool, pFmtNm, pDrvdFrm, RES_FRMFMT, aTableBoxSetRange )
    {}
    SwTableBoxFmt( SwAttrPool& rPool, const String &rFmtNm,
                    SwFrmFmt *pDrvdFrm )
        : SwFrmFmt( rPool, rFmtNm, pDrvdFrm, RES_FRMFMT, aTableBoxSetRange )
    {}

public:
    TYPEINFO();     //Bereits in Basisklasse Client drin.

    // zum Erkennen von Veraenderungen (haupts. TableBoxAttribute)
    virtual void Modify( SfxPoolItem* pOldValue, SfxPoolItem* pNewValue );

    DECL_FIXEDMEMPOOL_NEWDEL(SwTableBoxFmt)
};


} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
