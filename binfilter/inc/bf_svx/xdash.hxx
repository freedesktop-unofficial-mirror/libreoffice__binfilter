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

#ifndef _SVX_XDASH_HXX
#define _SVX_XDASH_HXX

//-------------
// class XDash
//-------------

#include <bf_svx/xenum.hxx>
namespace binfilter {

class XDash
{
protected:
    XDashStyle  eDash;
    USHORT      nDots;
    ULONG       nDotLen;
    USHORT      nDashes;
    ULONG       nDashLen;
    ULONG       nDistance;

public:
          XDash(XDashStyle eDash = XDASH_RECT,
                USHORT nDots = 1, ULONG nDotLen = 20,
                USHORT nDashes = 1, ULONG nDashLen = 20, ULONG nDistance = 20);

    int operator==(const XDash& rDash) const;

    void SetDashStyle(XDashStyle eNewStyle) { eDash = eNewStyle; }
    void SetDots(USHORT nNewDots)           { nDots = nNewDots; }
    void SetDotLen(ULONG nNewDotLen)        { nDotLen = nNewDotLen; }
    void SetDashes(USHORT nNewDashes)       { nDashes = nNewDashes; }
    void SetDashLen(ULONG nNewDashLen)      { nDashLen = nNewDashLen; }
    void SetDistance(ULONG nNewDistance)    { nDistance = nNewDistance; }

    XDashStyle  GetDashStyle() const        { return eDash; }
    USHORT      GetDots() const             { return nDots; }
    ULONG       GetDotLen() const           { return nDotLen; }
    USHORT      GetDashes() const           { return nDashes; }
    ULONG       GetDashLen() const          { return nDashLen; }
    ULONG       GetDistance() const         { return nDistance; }

};

}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
