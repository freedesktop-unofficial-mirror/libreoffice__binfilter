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

#ifndef SCH_MAPPROV_HXX
#define SCH_MAPPROV_HXX

// header for SfxItemPropertyMap
#include <bf_svtools/itemprop.hxx>

namespace binfilter {

// ----------------------------------------------
//                   Map-Id's
// ----------------------------------------------

#define CHMAP_NONE                   0
#define CHMAP_CHART                  1
#define CHMAP_AREA                   2
#define CHMAP_LINE                   3
#define CHMAP_DOC                    4
#define CHMAP_AXIS                   5
#define CHMAP_LEGEND                 6
#define CHMAP_TITLE                  7
#define CHMAP_DATAROW                8
#define CHMAP_DATAPOINT              9
#define CHMAP_END                   10      // last one used + 1

class ChartModel;

// ----------------------------------------------
//      Map-Provider ( to sort the maps )
// ----------------------------------------------

class SchUnoPropertyMapProvider
{
private:
    SfxItemPropertyMap* pMapArr[ CHMAP_END ];
    void Sort( short nId );

public:
    SchUnoPropertyMapProvider();
    ~SchUnoPropertyMapProvider();

    SfxItemPropertyMap* GetMap( short PropertyId, ChartModel* );
    SfxItemPropertyMap* CopyMap( const SfxItemPropertyMap* pMap1 );
};

} //namespace binfilter
#endif  // SCH_MAPPROV_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
