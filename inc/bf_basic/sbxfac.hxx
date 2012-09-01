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


#ifndef __SBX_SBX_FACTORY_HXX
#define __SBX_SBX_FACTORY_HXX

#include <bf_svtools/bf_solar.h>

#include "sbxdef.hxx"

namespace binfilter {

class SbxBase;
class SbxObject;
class String;
class UniString;

class SbxFactory
{
    BOOL bHandleLast;   // TRUE: Factory soll zuletzt gefragt werden, da teuer
public:
    SbxFactory( BOOL bLast=FALSE )  { bHandleLast = bLast; }
    virtual ~SbxFactory() {}
    BOOL IsHandleLast( void )       { return bHandleLast; }
    virtual SbxBase* Create( UINT16 nSbxId, UINT32 = SBXCR_SBX );
    virtual SbxObject* CreateObject( const String& );
};

}

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
