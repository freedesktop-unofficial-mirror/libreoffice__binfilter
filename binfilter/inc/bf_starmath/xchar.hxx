/*************************************************************************
 *
 *  $RCSfile: xchar.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:33 $
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

#ifndef XCHAR_HXX
#define XCHAR_HXX


#ifndef _SV_GEN_HXX //autogen
#include <tools/gen.hxx>
#endif
#ifndef _SV_OUTDEV_HXX //autogen
#include <vcl/outdev.hxx>
#endif
#ifndef _SV_POLY_HXX //autogen
#include <vcl/poly.hxx>
#endif
#ifndef _XPOLY_HXX //autogen
#include <bf_svx/xpoly.hxx>
#endif


#include "rect.hxx"


//STRIP001 PolyPolygon  SmGetPolyPolygon(const XPolyPolygon &rPoly, OutputDevice *pDev);
//STRIP001 void          SmDrawPolyPolygon(OutputDevice &rDev, const PolyPolygon &rPPoly);


////////////////////////////////////////
// SmPolygon
//

class SmPolygonLoader;

class SmPolygon
{
    friend class SmPolygonLoader;

    XPolyPolygon    aPoly;
    Rectangle       aBoundRect; // das umgebende Rechteck (ohne Rand!)
                                // wie von OutputDevice::GetBoundRect
    Size            aFontSize;  // vom Originalzeichen (Width != 0 aus FontMetric)
    Point           aPos;
    Size            aOrigSize;  // Originalgröße (des BoundRect)
    Point           aOrigPos;   // Offset des BoundRect im Originalzeichen

    double          fScaleX,    // Skalierungsfaktoren der aktuellen (gewollten)
                    fScaleY,    // Größe gegenüber der Originalgröße

                    fDelayedFactorX,    // dienen zum sammeln der Änderungen
                    fDelayedFactorY;    // bis tatsächlich skaliert wird

    sal_Unicode     cChar;
    BOOL            bDelayedScale,
                    bDelayedBoundRect;

    void            Scale();

public:
    SmPolygon();
    SmPolygon(sal_Unicode cChar);
    // default copy-constructor verwenden

    const Size &    GetOrigFontSize() const { return aFontSize; };
    const Size &    GetOrigSize() const { return aOrigSize; }
    const Point &   GetOrigPos() const { return aOrigPos; }

    void            ScaleBy(double fFactorX, double fFactorY);
    double          GetScaleX() const { return fScaleX * fDelayedFactorX; }
    double          GetScaleY() const { return fScaleY * fDelayedFactorY; }

    void            AdaptToX(const OutputDevice &rDev, ULONG nWidth);
    void            AdaptToY(const OutputDevice &rDev, ULONG nHeight);

    void            Move  (const Point &rPoint);
    void            MoveTo(const Point &rPoint) { Move(rPoint - aPos); }

    const sal_Unicode       GetChar() const { return cChar; }
//STRIP001  const XPolyPolygon &    GetXPolyPolygon() const;
    const Rectangle &       GetBoundRect(const OutputDevice &rDev) const;

//STRIP001  void            Draw(OutputDevice &rDev, const Point &rPoint) const;

    // default assignment-operator verwenden

    friend SvStream & operator >> (SvStream &rIStream, SmPolygon &rPoly);
    friend SvStream & operator << (SvStream &rOStream, const SmPolygon &rPoly);
};



#endif
