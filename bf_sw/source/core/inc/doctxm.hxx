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
#ifndef _DOCTXM_HXX
#define _DOCTXM_HXX


#include <bf_svtools/svarray.hxx>
#include <tools/gen.hxx>

#include <tox.hxx>
#include <section.hxx>
class  SvUShorts;
class  SvStringsDtor;
class  SvPtrarr;
namespace binfilter {

class  SwTOXInternational;

class  SwTxtNode;
class  SwTxtFmtColl;
struct SwPosition;
struct SwTOXSortTabBase;

typedef SwTOXSortTabBase* SwTOXSortTabBasePtr;

SV_DECL_PTRARR(SwTOXSortTabBases, SwTOXSortTabBasePtr, 0, 5 )

/*--------------------------------------------------------------------
     Beschreibung: Ring der speziellen Verzeichnisse
 --------------------------------------------------------------------*/

class SwTOXBaseSection : public SwTOXBase, public SwSection
{
    SwTOXSortTabBases aSortArr;

    void    UpdateAll();

    // Sortiert einfuegen ins Array fuer die Generierung

    // Alpha-Trennzeichen bei der Generierung einfuegen

    // Textrumpf generieren
    // add parameter <_TOXSectNdIdx> and <_pDefaultPageDesc>

    // Seitennummerplatzhalter gegen aktuelle Nummern austauschen

    // Bereich fuer Stichwort einfuegen suchen

    // returne die TextCollection ueber den Namen / aus Format-Pool

public:
    SwTOXBaseSection( const SwTOXBase& rBase );
    virtual ~SwTOXBaseSection();

    void UpdatePageNum();               // Seitennummern einfuegen
    TYPEINFO();                         // fuers rtti

};

struct SwDefTOXBase_Impl
{
    SwTOXBase* pContBase;
    SwTOXBase* pIdxBase;
    SwTOXBase* pUserBase;
    SwTOXBase* pTblBase;
    SwTOXBase* pObjBase;
    SwTOXBase* pIllBase;
    SwTOXBase* pAuthBase;

    SwDefTOXBase_Impl() :
    pContBase(0),
    pIdxBase(0),
    pUserBase(0),
    pTblBase(0),
    pObjBase(0),
    pIllBase(0),
    pAuthBase(0)
    {}
    ~SwDefTOXBase_Impl()
    {
        delete pContBase;
        delete pIdxBase;
        delete pUserBase;
        delete pTblBase;
        delete pObjBase;
        delete pIllBase;
        delete pAuthBase;
    }

};

} //namespace binfilter
#endif  // _DOCTXM_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
