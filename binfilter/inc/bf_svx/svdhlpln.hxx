/*************************************************************************
 *
 *  $RCSfile: svdhlpln.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:42 $
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

#ifndef _SVDHLPLN_HXX
#define _SVDHLPLN_HXX

#ifndef _GEN_HXX //autogen
#include <tools/gen.hxx>
#endif

#ifndef _POINTR_HXX //autogen
#include <vcl/pointr.hxx>
#endif

#ifndef _CONTNR_HXX //autogen
#include <tools/contnr.hxx>
#endif

class OutputDevice;
////////////////////////////////////////////////////////////////////////////////////////////////////

enum SdrHelpLineKind {SDRHELPLINE_POINT,SDRHELPLINE_VERTICAL,SDRHELPLINE_HORIZONTAL};
#define SDRHELPLINE_MIN SDRHELPLINE_POINT
#define SDRHELPLINE_MAX SDRHELPLINE_HORIZONTAL

#define SDRHELPLINE_POINT_PIXELSIZE 15 /* Tatsaechliche Groesse= PIXELSIZE*2+1 */

class SdrHelpLine {
    Point            aPos; // je nach Wert von eKind ist X oder Y evtl. belanglos
    SdrHelpLineKind  eKind;
public:
    SdrHelpLine(SdrHelpLineKind eNewKind=SDRHELPLINE_POINT): eKind(eNewKind) {}
    SdrHelpLine(SdrHelpLineKind eNewKind, const Point& rNewPos): aPos(rNewPos), eKind(eNewKind) {}
    FASTBOOL operator==(const SdrHelpLine& rCmp) const { return aPos==rCmp.aPos && eKind==rCmp.eKind; }
    FASTBOOL operator!=(const SdrHelpLine& rCmp) const { return !operator==(rCmp); }

    void            SetKind(SdrHelpLineKind eNewKind) { eKind=eNewKind; }
    SdrHelpLineKind GetKind() const                   { return eKind; }
    void            SetPos(const Point& rPnt)         { aPos=rPnt; }
    const Point&    GetPos() const                    { return aPos; }

//STRIP001  Pointer         GetPointer() const;
//STRIP001  void            Draw(OutputDevice& rOut, const Point& rOfs) const;
    FASTBOOL        IsHit(const Point& rPnt, USHORT nTolLog, const OutputDevice& rOut) const;
    // OutputDevice wird benoetigt, da Fangpunkte eine feste Pixelgroesse haben
//STRIP001  Rectangle       GetBoundRect(const OutputDevice& rOut) const;

    /* returns true if this and the given help line would be rendered at the same pixel position
        of the given OutputDevice. This can be used to avoid drawing multiple help lines with xor
        on same position which could render them invisible */
//STRIP001  bool            IsVisibleEqual( const SdrHelpLine& rHelpLine, const OutputDevice& rOut ) const;

    friend SvStream& operator<<(SvStream& rOut, const SdrHelpLine& rHL);
    friend SvStream& operator>>(SvStream& rIn, SdrHelpLine& rHL);
};

#define SDRHELPLINE_NOTFOUND 0xFFFF

class SdrHelpLineList {
    Container aList;
protected:
    SdrHelpLine* GetObject(USHORT i) const { return (SdrHelpLine*)(aList.GetObject(i)); }
public:
    SdrHelpLineList(): aList(1024,4,4) {}
    SdrHelpLineList(const SdrHelpLineList& rSrcList): aList(1024,4,4)      { *this=rSrcList; }
    ~SdrHelpLineList()                                                     { Clear(); }
    void               Clear();
    void               operator=(const SdrHelpLineList& rSrcList);
//STRIP001  FASTBOOL operator==(const SdrHelpLineList& rCmp) const;
//STRIP001  FASTBOOL operator!=(const SdrHelpLineList& rCmp) const                 { return !operator==(rCmp); }
    USHORT             GetCount() const                                    { return USHORT(aList.Count()); }
    void               Insert(const SdrHelpLine& rHL, USHORT nPos=0xFFFF)  { aList.Insert(new SdrHelpLine(rHL),nPos); }
    void               Delete(USHORT nPos)                                 { delete aList.Remove(nPos); }
    void               Move(USHORT nPos, USHORT nNewPos)                   { aList.Insert(aList.Remove(nPos),nNewPos); }
    SdrHelpLine&       operator[](USHORT nPos)                             { return *GetObject(nPos); }
    const SdrHelpLine& operator[](USHORT nPos) const                       { return *GetObject(nPos); }
//STRIP001  void               DrawAll(OutputDevice& rOut, const Point& rOfs) const;
    USHORT             HitTest(const Point& rPnt, USHORT nTolLog, const OutputDevice& rOut) const;
    friend SvStream& operator<<(SvStream& rOut, const SdrHelpLineList& rHLL);
    friend SvStream& operator>>(SvStream& rIn, SdrHelpLineList& rHLL);
};

////////////////////////////////////////////////////////////////////////////////////////////////////

#endif //_SVDHLPLN_HXX

