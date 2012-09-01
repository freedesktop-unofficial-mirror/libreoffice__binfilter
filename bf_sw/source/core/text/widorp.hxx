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
#ifndef _WIDORP_HXX
#define _WIDORP_HXX

class SwTxtFrm;

#include "swtypes.hxx"
#include "itrtxt.hxx"
namespace binfilter {

class SwTxtFrmBreak
{
private:
          SwTwips  nRstHeight;
#ifdef VERTICAL_LAYOUT
    SwTwips  nOrigin;
#else
    const SwTwips  nOrigin;
#endif
protected:
    SwTxtFrm *pFrm;
    sal_Bool     bBreak;
    sal_Bool     bKeep;
public:
    SwTxtFrmBreak( SwTxtFrm *pFrm, const SwTwips nRst = 0  );
    sal_Bool IsBreakNow( SwTxtMargin &rLine );

    sal_Bool IsBroken() const   { return bBreak; }
    sal_Bool IsKeepAlways() const { return bKeep; }
          void Keep()               { bKeep = sal_True; }
          void Break()              { bKeep = sal_False; bBreak = sal_True; }

    inline sal_Bool GetKeep() const { return bKeep; }
    inline void SetKeep( const sal_Bool bNew ) { bKeep = bNew; }

    sal_Bool IsInside( SwTxtMargin &rLine ) const;

    // Um Sonderfaelle mit Ftn behandeln zu koennen.
    // Mit SetRstHeight wird dem SwTxtFrmBreak die Resthoehe eingestellt,
    // Um TruncLines() rufen zu koennen, ohne dass IsBreakNow() einen
    // anderen Wert zurueckliefert.
    // Es wird dabei davon ausgegangen, dass rLine auf der letzten Zeile
    // steht, die nicht mehr passt.

#ifdef VERTICAL_LAYOUT
    void SetRstHeight( const SwTxtMargin &rLine )
    {
        if ( !pFrm->IsVertical() )
            nRstHeight = rLine.Y() - nOrigin;
    }
#else
    void SetRstHeight( const SwTxtMargin &rLine ) { nRstHeight = rLine.Y() - nOrigin; }
#endif

    SwTwips GetRstHeight() const { return nRstHeight; }
};

class WidowsAndOrphans : public SwTxtFrmBreak
{
private:
    MSHORT   nWidLines, nOrphLines;

public:
    WidowsAndOrphans( SwTxtFrm *pFrm, const SwTwips nRst = 0,
        sal_Bool bCheckKeep = sal_True );
    sal_Bool FindWidows( SwTxtFrm *pFrm, SwTxtMargin &rLine );
    MSHORT GetWidowsLines() const
    { return nWidLines; }
    MSHORT GetOrphansLines() const
    { return nOrphLines; }
    void ClrOrphLines(){ nOrphLines = 0; }

    sal_Bool FindBreak( SwTxtFrm *pFrm, SwTxtMargin &rLine, sal_Bool bHasToFit );
    sal_Bool WouldFit( SwTxtMargin &rLine, SwTwips &rMaxHeight );
    sal_Bool IsBreakNow( SwTxtMargin &rLine )
    {   return ( rLine.GetLineNr() > nOrphLines ) &&
                 SwTxtFrmBreak::IsBreakNow( rLine ); }
};


} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
