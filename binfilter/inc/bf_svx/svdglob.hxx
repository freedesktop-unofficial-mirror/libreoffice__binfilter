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

#ifndef _SVDGLOB_HXX
#define _SVDGLOB_HXX


#include <tools/resid.hxx>

#include <bf_tools/string.hxx>
class Link;
class ResMgr;
namespace binfilter {
//************************************************************
//   Vorausdeklarationen
//************************************************************


class SdrEngineDefaults;
class ImpSdrStrCache;

//************************************************************
//   Defines
//************************************************************

// Den zur App passenden Resourcemanager holen
ResMgr* ImpGetResMgr();

class SdrResId: ResId {
public:
    SdrResId(USHORT nId): ResId(nId,*ImpGetResMgr()) {}
};

////////////////////////////////////////////////////////////////////////////////////////////////////

}//end of namespace binfilter
#endif //_SVDGLOB_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
