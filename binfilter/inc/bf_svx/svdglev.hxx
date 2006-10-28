/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svdglev.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 04:04:56 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
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
namespace binfilter {

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
    typedef void (*PGlueDoFunc)(SdrGluePoint&, const SdrObject* pObj, const void*, const void*, const void*, const void*, const void*);
    typedef void (*PGlueTrFunc)(Point&, const void*, const void*, const void*, const void*, const void*);

public:
    SdrGlueEditView(SdrModel* pModel1, OutputDevice* pOut=NULL);
    SdrGlueEditView(SdrModel* pModel1, ExtOutputDevice* pXOut);
    virtual ~SdrGlueEditView();

    // Durch den Parameter nThisEsc uebergibt man die Richtung, die man
    // checken bzw. setzen/loeschen will.
    // Moegliche Werte fuer nThisEsc sind z.Zt.
    // SDRESC_LEFT, SDRESC_RIGHT, SDRESC_TOP und SDRESC_BOTTOM
    BOOL IsSetMarkedGluePointsEscDirPossible() const { return !IsReadOnly() && HasMarkedGluePoints(); }

    // Checken/setzen, ob die Klebepunktpositionen relativ zur
    // Objektgroesse sind (Percent=TRUE) oder nicht (Percent=FALSE)
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

    // Alle merkierten Klebepunkte entfernen

    void MirrorMarkedGluePoints(const Point& rRef1, const Point& rRef2, BOOL bCopy=FALSE);
    void MirrorMarkedGluePointsHorizontal(BOOL bCopy=FALSE);
    void MirrorMarkedGluePointsVertical(BOOL bCopy=FALSE);
    void ShearMarkedGluePoints(const Point& rRef, long nWink, BOOL bVShear=FALSE, BOOL bCopy=FALSE);
    void CrookMarkedGluePoints(const Point& rRef, const Point& rRad, SdrCrookMode eMode, BOOL bVertical=FALSE, BOOL bNoContortion=FALSE, BOOL bCopy=FALSE);
    void DistortMarkedGluePoints(const Rectangle& rRef, const XPolygon& rDistortedRect, BOOL bNoContortion=FALSE, BOOL bCopy=FALSE);

    void AlignMarkedGluePoints(SdrHorAlign eHor, SdrVertAlign eVert);
};

}//end of namespace binfilter
#endif //_SVDGLEV_HXX

