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

#ifndef SC_MSGPOOL_HXX
#define SC_MSGPOOL_HXX

#include "scitems.hxx"

#include <bf_svtools/itempool.hxx>
#include <bf_svtools/stritem.hxx>
#include <bf_svtools/eitem.hxx>
#include <bf_sfx2/srchitem.hxx>

#include "uiitems.hxx"
namespace binfilter {


//------------------------------------------------------------------------

class ScDocumentPool;

//------------------------------------------------------------------------

class ScMessagePool: public SfxItemPool
{
    SfxStringItem       aGlobalStringItem;
    SvxSearchItem       aGlobalSearchItem;
    ScSortItem          aGlobalSortItem;
    ScQueryItem         aGlobalQueryItem;
    ScSubTotalItem      aGlobalSubTotalItem;
    ScConsolidateItem   aGlobalConsolidateItem;
    ScPivotItem         aGlobalPivotItem;
    ScSolveItem         aGlobalSolveItem;
    ScUserListItem      aGlobalUserListItem;

    SfxBoolItem         aPrintWarnItem;

    SfxPoolItem**   ppPoolDefaults;
    ScDocumentPool* pDocPool;

public:
    ScMessagePool();
    ~ScMessagePool();

    virtual SfxMapUnit              GetMetric( USHORT nWhich ) const;
};



} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
