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
#ifndef _PORRST_HXX
#define _PORRST_HXX

#include <bf_svtools/svarray.hxx>

#include "porlay.hxx"
#include "porexp.hxx"
namespace binfilter {

#ifdef VERTICAL_LAYOUT
#define LINE_BREAK_WIDTH        150
#define SPECIAL_FONT_HEIGHT     200
#endif

class SwTxtFormatInfo;

/*************************************************************************
 *                      class SwBreakPortion
 *************************************************************************/

class SwBreakPortion : public SwLinePortion
{
#ifdef VERTICAL_LAYOUT
#else
    void CalcViewWidth( const SwTxtSizeInfo &rInf );
#endif

protected:
#ifndef VERTICAL_LAYOUT
    KSHORT  nViewWidth;
#endif
    KSHORT  nRestWidth;
public:
            SwBreakPortion( const SwLinePortion &rPortion );
    // liefert 0 zurueck, wenn keine Nutzdaten enthalten sind.
    virtual SwLinePortion *Compress();
    virtual void Paint( const SwTxtPaintInfo& ) const { DBG_BF_ASSERT(0, "STRIP"); }
    virtual sal_Bool Format( SwTxtFormatInfo &rInf );
    USHORT GetRestWidth() const { return nRestWidth; }

    // Accessibility: pass information about this portion to the PortionHandler

    OUTPUT_OPERATOR
};

/*************************************************************************
 *                      class SwKernPortion
 *************************************************************************/

class SwKernPortion : public SwLinePortion
{
    short nKern;
    sal_Bool bBackground;

#ifdef VERTICAL_LAYOUT
    sal_Bool bGridKern;
#endif

public:

#ifdef VERTICAL_LAYOUT
    // This constructor automatically appends the portion to rPortion
    // bBG indicates, that the background of the kerning portion has to
    // be painted, e.g., if the portion if positioned between to fields.
    // bGridKern indicates, that the kerning portion is used to provide
    // additional space in grid mode.
    SwKernPortion( SwLinePortion &rPortion, short nKrn,
                   sal_Bool bBG = sal_False, sal_Bool bGridKern = sal_False );

    // This constructor only sets the height and ascent to the values
    // of rPortion. It is only used for kerning portions for grid mode
#else
    SwKernPortion( SwLinePortion &rPortion, short nKrn,
                   sal_Bool bBG = sal_False );
#endif

    virtual void FormatEOL( SwTxtFormatInfo &rInf );
    virtual void Paint( const SwTxtPaintInfo & ) const { DBG_BF_ASSERT(0, "STRIP"); }

    OUTPUT_OPERATOR
};

/*************************************************************************
 *                      class SwArrowPortion
 *************************************************************************/

class SwArrowPortion : public SwLinePortion
{
    Point aPos;
    sal_Bool bLeft;
public:
            SwArrowPortion( const SwLinePortion &rPortion );
    virtual void Paint( const SwTxtPaintInfo & ) const { DBG_BF_ASSERT(0, "STRIP"); }
    virtual SwLinePortion *Compress();
    inline sal_Bool IsLeft() const { return bLeft; }
    inline const Point& GetPos() const { return aPos; }
    OUTPUT_OPERATOR
};

/*************************************************************************
 *                      class SwHangingPortion
 * The characters which are forbidden at the start of a line like the dot and
 * other punctuation marks are allowed to display in the margin of the page
 * by a user option.
 * The SwHangingPortion is the corresponding textportion to do that.
 *************************************************************************/

class SwHangingPortion : public SwTxtPortion
{
    KSHORT nInnerWidth;
public:
    inline SwHangingPortion( SwPosSize aSize ) : nInnerWidth( aSize.Width() )
        { SetWhichPor( POR_HNG );  SetLen( 1 ); Height( aSize.Height() ); }

    inline KSHORT GetInnerWidth() const { return nInnerWidth; }
};


/*************************************************************************
 *                  inline - Implementations
 *************************************************************************/

CLASSIO( SwBreakPortion )
CLASSIO( SwEndPortion )
CLASSIO( SwKernPortion )
CLASSIO( SwArrowPortion )

} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
