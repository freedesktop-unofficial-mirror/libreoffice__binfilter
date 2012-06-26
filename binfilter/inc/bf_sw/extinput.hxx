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
#ifndef _EXTINPUT_HXX
#define _EXTINPUT_HXX

#include <bf_svtools/bf_solar.h>

#ifndef _SVSTDARR_HXX
#define _SVSTDARR_USHORTS
#include <bf_svtools/svstdarr.hxx>
#endif
#include <pam.hxx>
class CommandExtTextInputData;
class Font;

namespace binfilter {


class SwExtTextInput : public SwPaM
{
    SvUShorts aAttrs;
    String sOverwriteText;
    BOOL bInsText : 1;
    BOOL bIsOverwriteCursor : 1;
public:
            SwExtTextInput(){};

    const SvUShorts& GetAttrs() const   { return aAttrs; }
    BOOL IsInsText() const              { return bInsText; }
    void SetInsText( BOOL bFlag )       { bInsText = bFlag; }
    BOOL IsOverwriteCursor() const      { return bIsOverwriteCursor; }
};

} //namespace binfilter
#endif  //_EXTINPUT_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
