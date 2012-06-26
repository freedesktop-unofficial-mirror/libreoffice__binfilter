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

#ifndef SC_DPTABRES_HXX
#define SC_DPTABRES_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_svtools/svarray.hxx>

#include <bf_tools/string.hxx>

#include <com/sun/star/sheet/MemberResult.hpp>
#include <com/sun/star/sheet/DataResult.hpp>
#include <com/sun/star/uno/Sequence.hxx>

#include "global.hxx"       // enum ScSubTotalFunc
namespace binfilter {


class ScAddress;
class ScDocument;
class ScDPSource;
class ScDPDimension;
class ScDPLevel;
class ScDPMember;
class ScDPAggData;

struct ScDPValueData;

//
//  aggregated data
//! separate header file?
//





// --------------------------------------------------------------------
//
//  results for a hierarchy dimension
//

#define SC_DP_RES_GROW  16

class ScDPResultDimension;
class ScDPDataDimension;
class ScDPDataMember;
struct ScDPItemData;


#define SC_DPMEASURE_ALL    -1
#define SC_DPMEASURE_ANY    -2

class ScDPResultData
{
public:
    ScDPResultData( ScDPSource* /*pSrc*/ ) {DBG_BF_ASSERT(0, "STRIP");}
    ~ScDPResultData(){DBG_BF_ASSERT(0, "STRIP");}
};


class ScDPResultMember
{

public:
                        ScDPResultMember( ScDPResultData*, ScDPDimension*,
                                            ScDPLevel*, ScDPMember*,
                                            BOOL ) {DBG_BF_ASSERT(0, "STRIP");}
                        ~ScDPResultMember(){DBG_BF_ASSERT(0, "STRIP");}



//  BOOL                SubTotalEnabled() const;






                        //! this will be removed!
};









                        //! this will be removed!

//! replace PtrArr with 32-bit array ????




//  result dimension contains only members



                        //  allocates new members



                        //  modifies existing members, allocates data dimensions



                        //  for ScDPDataDimension::InitFrom






} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
