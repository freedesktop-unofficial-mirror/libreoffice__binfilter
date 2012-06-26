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


#ifndef SD_DLGCTRLS_HXX
#define SD_DLGCTRLS_HXX

#include <vcl/lstbox.hxx>
#include <vcl/window.hxx>

#include "schresid.hxx"
namespace binfilter {

/*************************************************************************
|*
|* FadeEffectLB
|*
\************************************************************************/
class FadeEffectLB : public ListBox
{

public:
         FadeEffectLB( Window* pParent, SchResId Id ) : ListBox( pParent, Id ) {}
         FadeEffectLB( Window* pParent, WinBits aWB ) : ListBox( pParent, aWB ) {}

    virtual void Fill();
};

} //namespace binfilter
#endif // SD_DLGCTRLS_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
