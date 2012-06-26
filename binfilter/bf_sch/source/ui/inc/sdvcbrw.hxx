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

#ifndef _SDVCBRW_HXX
#define _SDVCBRW_HXX
/*
#include <bf_svx/vcbrw.hxx>
*/
#include <bf_svtools/brdcst.hxx>

#include <bf_svtools/lstner.hxx>
namespace binfilter {

class SdrView;

/*************************************************************************
|*
|* Klasse fuer Browser
|*
\************************************************************************/
class SdVCBrowser : public VCBrowser //, public SfxListener, public SfxBroadcaster
{
protected:
    SdrView*    pView;
    BOOL        bUpdate;

    BOOL    Close();

    virtual void SFX_NOTIFY( SfxBroadcaster& rBC, const TypeId& rBCType,
                         const SfxHint& rHint, const TypeId& rHintType );
    void         Modify();


public:
    SdVCBrowser( Window* pParent );

    void Update( SdrView* pView );
};




} //namespace binfilter
#endif      // _SDVCBRW_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
