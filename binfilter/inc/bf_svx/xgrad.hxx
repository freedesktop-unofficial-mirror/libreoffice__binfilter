/*************************************************************************
 *
 *  $RCSfile: xgrad.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:29:39 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/

#ifndef _SVX__XGRADIENT_HXX
#define _SVX__XGRADIENT_HXX

#include <bf_svx/xenum.hxx>

#ifndef _COLOR_HXX //autogen
#include <vcl/color.hxx>
#endif
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
