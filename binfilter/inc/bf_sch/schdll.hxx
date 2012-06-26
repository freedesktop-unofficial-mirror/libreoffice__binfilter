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

#ifndef _SCH_DLL_HXX
#define _SCH_DLL_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_sfx2/sfxdefs.hxx>

// header for class SfxModule
#include <bf_sfx2/module.hxx>
// header for class SvInPlaceObject
#include <bf_so3/ipobj.hxx>

#include <bf_sch/chattr.hxx>    // to do: remove this line and replace most of the schdll.hxx includes to chattr.hxx
class OutputDevice;
class Window;
class SvStream;

namespace binfilter {
class SvFactory;
class SvInPlaceObjectRef;
class SfxItemSet;

#define extern_c extern "C"

/*-------------------------------------------------------------------------

  The class SchDLL initializes the data, interfaces, controls, etc.
  that are needed by the shared library.

  It also maintains the ressource manager.

  to use the shared chart library SchDLL must be instanciated.

-------------------------------------------------------------------------*/

class SchDragServer;
class SchMemChart;
class SfxMedium;
class SfxFilter;
class XOutdevItemPool;
class ChartModel;

class SchDLL
{
public:

    SchDLL();
    ~SchDLL();

    static void     Init();
    static void     Exit();
    static void     LibInit();
    static void     LibExit();

    static void     Update( SvInPlaceObjectRef aIPObj, SchMemChart* pData, OutputDevice* pOut=NULL);

    static SchMemChart*  GetChartData( SvInPlaceObjectRef aIPObj );

    static SchMemChart* NewMemChart( short nCols, short nRows );
};

/*-------------------------------------------------------------------------

  The following functions are called from the static interface (above)
  after the shared library has been loaded

-------------------------------------------------------------------------*/

extern_c void __LOADONCALLAPI SchUpdate( SvInPlaceObjectRef aIPObj, SchMemChart* pData, OutputDevice* pOut = NULL );
extern_c SchMemChart* __LOADONCALLAPI SchGetChartData( SvInPlaceObjectRef aIPObj );
extern_c SchMemChart* __LOADONCALLAPI SchNewMemChartXY( short nCols, short nRows );
extern_c void __LOADONCALLAPI SetTransparentBackground( SvInPlaceObjectRef aIPObj, BOOL bTransp = TRUE );

} //namespace binfilter
#endif          // _SCH_DLL_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
