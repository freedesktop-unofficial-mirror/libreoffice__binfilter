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

#ifndef _BLINK_HXX
#define _BLINK_HXX

class SwLinePortion;
class SwTxtFrm;

#include <bf_svtools/svarray.hxx>
#include <tools/gen.hxx>
namespace binfilter {

class SwBlinkPortion
{
    Point               aPos;
    const SwLinePortion *pPor;
    USHORT              nDir;
public:
    SwBlinkPortion( const SwLinePortion* pPortion, USHORT nDirection )
            { pPor = pPortion; nDir = nDirection; }
    SwBlinkPortion( const SwBlinkPortion* pBlink, const SwLinePortion* pPort )
    {   pPor = pPort; aPos = pBlink->aPos; nDir = pBlink->nDir; }
    void SetPos( const Point& aNew ){ aPos = aNew; }
    const Point& GetPos() const{ return aPos; }
    const SwLinePortion *GetPortion() const{ return pPor; }
    USHORT GetDirection() const { return nDir; }
    BOOL operator<( const SwBlinkPortion& rBlinkPortion ) const
    { return (long)pPor < (long)rBlinkPortion.pPor; }
    BOOL operator==( const SwBlinkPortion& rBlinkPortion ) const
    { return (long)pPor == (long)rBlinkPortion.pPor; }
};

typedef SwBlinkPortion* SwBlinkPortionPtr;
SV_DECL_PTRARR_SORT_DEL(SwBlinkList, SwBlinkPortionPtr, 0, 10)

} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
