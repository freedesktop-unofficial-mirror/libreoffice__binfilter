/*************************************************************************
 *
 *  $RCSfile: svdglev.hxx,v $
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

#ifndef _SVDGLEV_HXX
#define _SVDGLEV_HXX

// HACK to avoid too deep includes and to have some
// levels free in svdmark itself (MS compiler include depth limit)
#ifndef _SVDHDL_HXX
#include <bf_svx/svdhdl.hxx>
#endif

#include <bf_svx/svdpoev.hxx>

//************************************************************
//   Vorausdeklarationen
//************************************************************

class SdrGluePoint;

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
//
//   @@@@  @@    @@  @@ @@@@@   @@@@@ @@@@@  @@ @@@@@@  @@ @@ @@ @@@@@ @@   @@
//  @@  @@ @@    @@  @@ @@      @@    @@  @@ @@   @@    @@ @@ @@ @@    @@   @@
//  @@     @@    @@  @@ @@      @@    @@  @@ @@   @@    @@ @@ @@ @@    @@ @ @@
//  @@ @@@ @@    @@  @@ @@@@    @@@@  @@  @@ @@   @@    @@@@@ @@ @@@@  @@@@@@@
//  @@  @@ @@    @@  @@ @@      @@    @@  @@ @@   @@     @@@  @@ @@    @@@@@@@
//  @@  @@ @@    @@  @@ @@      @@    @@  @@ @@   @@     @@@  @@ @@    @@@ @@@
//   @@@@@ @@@@@  @@@@  @@@@@   @@@@@ @@@@@  @@   @@      @   @@ @@@@@ @@   @@
//
//  Editieren von Klebepunkten an den Objekten (Klebepunkte fuer Verbinder)
//
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

class SdrGlueEditView: public SdrPolyEditView
{
    void ImpClearVars();

    // Markierte Klebepunkte kopieren und anstelle der alten markieren
//STRIP001  void ImpCopyMarkedGluePoints();
    typedef void (*PGlueDoFunc)(SdrGluePoint&, const SdrObject* pObj, const void*, const void*, const void*, const void*, const void*);
    typedef void (*PGlueTrFunc)(Point&, const void*, const void*, const void*, const void*, const void*);
//STRIP001  void ImpDoMarkedGluePoints(PGlueDoFunc pDoFunc, BOOL bConst, const void* p1=NULL, const void* p2=NULL, const void* p3=NULL, const void* p4=NULL, const void* p5=NULL);
//STRIP001  void ImpTransformMarkedGluePoints(PGlueTrFunc pTrFunc, const void* p1=NULL, const void* p2=NULL, const void* p3=NULL, const void* p4=NULL, const void* p5=NULL);

public:
    SdrGlueEditView(SdrModel* pModel1, OutputDevice* pOut=NULL);
    SdrGlueEditView(SdrModel* pModel1, ExtOutputDevice* pXOut);
    virtual ~SdrGlueEditView();

    // Durch den Parameter nThisEsc uebergibt man die Richtung, die man
    // checken bzw. setzen/loeschen will.
    // Moegliche Werte fuer nThisEsc sind z.Zt.
    // SDRESC_LEFT, SDRESC_RIGHT, SDRESC_TOP und SDRESC_BOTTOM
//STRIP001  TRISTATE IsMarkedGluePointsEscDir(USHORT nThisEsc) const;
//STRIP001  void SetMarkedGluePointsEscDir(USHORT nThisEsc, BOOL bOn);
    BOOL IsSetMarkedGluePointsEscDirPossible() const { return !IsReadOnly() && HasMarkedGluePoints(); }

    // Checken/setzen, ob die Klebepunktpositionen relativ zur
    // Objektgroesse sind (Percent=TRUE) oder nicht (Percent=FALSE)
//STRIP001  TRISTATE IsMarkedGluePointsPercent() const;
//STRIP001  void SetMarkedGluePointsPercent(BOOL bOn);
    BOOL IsSetMarkedGluePointsPercentPossible() const { return !IsReadOnly() && HasMarkedGluePoints(); }

    // bVert=FALSE: Horizontales Alignment checken/setzen
    //      SDRHORZALIGN_CENTER
    //      SDRHORZALIGN_LEFT
    //      SDRHORZALIGN_RIGHT
    //      SDRHORZALIGN_DONTCARE (nur bei Get())
    // bVert=TRUE: Vertikales Alignment checken/setzen
    //      SDRVERTALIGN_CENTER
    //      SDRVERTALIGN_TOP
    //      SDRVERTALIGN_BOTTOM
    //      SDRVERTALIGN_DONTCARE (nur bei Get())
//STRIP001  USHORT GetMarkedGluePointsAlign(BOOL bVert) const;
//STRIP001  void SetMarkedGluePointsAlign(BOOL bVert, USHORT nAlign);
//STRIP001  BOOL IsSetMarkedGluePointsAlignPossible() const { return !IsReadOnly() && HasMarkedGluePoints(); }

    // Alle merkierten Klebepunkte entfernen
//STRIP001  void DeleteMarkedGluePoints();
//STRIP001  BOOL IsDeleteMarkedGluePointsPossible() const;

//STRIP001  void MoveMarkedGluePoints  (const Size& rSiz, BOOL bCopy=FALSE);
//STRIP001  void ResizeMarkedGluePoints(const Point& rRef, const Fraction& xFact, const Fraction& yFact, BOOL bCopy=FALSE);
//STRIP001  void RotateMarkedGluePoints(const Point& rRef, long nWink, BOOL bCopy=FALSE);
    void MirrorMarkedGluePoints(const Point& rRef1, const Point& rRef2, BOOL bCopy=FALSE);
    void MirrorMarkedGluePointsHorizontal(BOOL bCopy=FALSE);
    void MirrorMarkedGluePointsVertical(BOOL bCopy=FALSE);
    void ShearMarkedGluePoints(const Point& rRef, long nWink, BOOL bVShear=FALSE, BOOL bCopy=FALSE);
    void CrookMarkedGluePoints(const Point& rRef, const Point& rRad, SdrCrookMode eMode, BOOL bVertical=FALSE, BOOL bNoContortion=FALSE, BOOL bCopy=FALSE);
    void DistortMarkedGluePoints(const Rectangle& rRef, const XPolygon& rDistortedRect, BOOL bNoContortion=FALSE, BOOL bCopy=FALSE);

    void AlignMarkedGluePoints(SdrHorAlign eHor, SdrVertAlign eVert);
};

#endif //_SVDGLEV_HXX

