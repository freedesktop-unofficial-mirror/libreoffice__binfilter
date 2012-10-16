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

#ifndef _SVX__XGRADIENT_HXX
#define _SVX__XGRADIENT_HXX

#include <bf_svx/xenum.hxx>

#include <tools/color.hxx>
namespace binfilter {

//-----------------
// class XGradient
//-----------------

class XGradient
{
protected:
    XGradientStyle  eStyle;
    Color           aStartColor;
    Color           aEndColor;
    long            nAngle;
    USHORT          nBorder;
    USHORT          nOfsX;
    USHORT          nOfsY;
    USHORT          nIntensStart;
    USHORT          nIntensEnd;
    USHORT          nStepCount;

public:
    XGradient() {}
    XGradient( const Color& rStart, const Color& rEnd,
               XGradientStyle eStyle = XGRAD_LINEAR, long nAngle = 0,
               USHORT nXOfs = 50, USHORT nYOfs = 50, USHORT nBorder = 0,
               USHORT nStartIntens = 100, USHORT nEndIntens = 100,
               USHORT nSteps = 0 );

    int operator==(const XGradient& rGradient) const;

    void SetGradientStyle(XGradientStyle eNewStyle) { eStyle = eNewStyle; }
    void SetStartColor(const Color& rColor)         { aStartColor = rColor; }
    void SetEndColor(const Color& rColor)           { aEndColor = rColor; }
    void SetAngle(long nNewAngle)                   { nAngle = nNewAngle; }
    void SetBorder(USHORT nNewBorder)               { nBorder = nNewBorder; }
    void SetXOffset(USHORT nNewOffset)              { nOfsX = nNewOffset; }
    void SetYOffset(USHORT nNewOffset)              { nOfsY = nNewOffset; }
    void SetStartIntens(USHORT nNewIntens)          { nIntensStart = nNewIntens; }
    void SetEndIntens(USHORT nNewIntens)            { nIntensEnd = nNewIntens; }
    void SetSteps(USHORT nSteps)                    { nStepCount = nSteps; }

    XGradientStyle GetGradientStyle() const         { return eStyle; }
    Color          GetStartColor() const            { return aStartColor; }
    Color          GetEndColor() const              { return aEndColor; }
    long           GetAngle() const                 { return nAngle; }
    USHORT         GetBorder() const                { return nBorder; }
    USHORT         GetXOffset() const               { return nOfsX; }
    USHORT         GetYOffset() const               { return nOfsY; }
    USHORT         GetStartIntens() const           { return nIntensStart; }
    USHORT         GetEndIntens() const             { return nIntensEnd; }
    USHORT         GetSteps() const                 { return nStepCount; }
};

}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
