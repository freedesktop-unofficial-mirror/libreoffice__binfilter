/*************************************************************************
 *
 *  $RCSfile: svdpoev.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:28:58 $
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

#ifndef _SVDPOEV_HXX
#define _SVDPOEV_HXX

// HACK to avoid too deep includes and to have some
// levels free in svdmark itself (MS compiler include depth limit)
#ifndef _SVDHDL_HXX
#include <bf_svx/svdhdl.hxx>
#endif

#include <bf_svx/svdedtv.hxx>
namespace binfilter {

//************************************************************
//   Defines
//************************************************************

enum SdrPathSmoothKind  {SDRPATHSMOOTH_DONTCARE,   // nur fuer Statusabfrage
                         SDRPATHSMOOTH_ANGULAR,    // Eckig
                         SDRPATHSMOOTH_ASYMMETRIC, // unsymmetrisch, normales Smooth
                         SDRPATHSMOOTH_SYMMETRIC}; // symmetrisch

enum SdrPathSegmentKind {SDRPATHSEGMENT_DONTCARE,  // nur fuer Statusabfrage
                         SDRPATHSEGMENT_LINE,      // gerader Streckenabschnitt
                         SDRPATHSEGMENT_CURVE,     // Kurvenabschnitt (Bezier)
                         SDRPATHSEGMENT_TOGGLE};   // nur fuer Set: Toggle

enum SdrObjClosedKind   {SDROBJCLOSED_DONTCARE,    // nur fuer Statusabfrage
                         SDROBJCLOSED_OPEN,        // Objekte geoeffnet (Linie, Polyline, ...)
                         SDROBJCLOSED_CLOSED,      // Objekte geschlossen (Polygon, ...)
                         SDROBJCLOSED_TOGGLE};     // nur fuer Set: Toggle (not implemented yet)

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
//
// @@@@@   @@@@  @@  @@  @@  @@@@@ @@@@@  @@ @@@@@@  @@ @@ @@ @@@@@ @@   @@
// @@  @@ @@  @@ @@  @@  @@  @@    @@  @@ @@   @@    @@ @@ @@ @@    @@   @@
// @@  @@ @@  @@ @@  @@  @@  @@    @@  @@ @@   @@    @@ @@ @@ @@    @@ @ @@
// @@@@@  @@  @@ @@   @@@@   @@@@  @@  @@ @@   @@    @@@@@ @@ @@@@  @@@@@@@
// @@     @@  @@ @@    @@    @@    @@  @@ @@   @@     @@@  @@ @@    @@@@@@@
// @@     @@  @@ @@    @@    @@    @@  @@ @@   @@     @@@  @@ @@    @@@ @@@
// @@      @@@@  @@@@@ @@    @@@@@ @@@@@  @@   @@      @   @@ @@@@@ @@   @@
//
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

class SdrPolyEditView: public SdrEditView
{
    friend class                SdrEditView;

protected:
    BOOL                        bSetMarkedPointsSmoothPossible : 1;
    BOOL                        bSetMarkedSegmentsKindPossible : 1;

    SdrPathSmoothKind           eMarkedPointsSmooth;
    SdrPathSegmentKind          eMarkedSegmentsKind;

private:
    void ImpClearVars();
    void ImpResetPolyPossibilityFlags();
    void ImpCheckPolyPossibilities();

    // Markierte Punkte kopieren und anstelle der alten markieren
    // ist noch nicht implementiert!
//STRIP001  void ImpCopyMarkedPoints();
    typedef void (*PPolyTrFunc)(Point&, Point*, Point*, const void*, const void*, const void*, const void*, const void*);
//STRIP001  void ImpTransformMarkedPoints(PPolyTrFunc pTrFunc, const void* p1=NULL, const void* p2=NULL, const void* p3=NULL, const void* p4=NULL, const void* p5=NULL);

public:
    SdrPolyEditView(SdrModel* pModel1, OutputDevice* pOut=NULL);
    SdrPolyEditView(SdrModel* pModel1, ExtOutputDevice* pXOut);
    virtual ~SdrPolyEditView();

    BOOL IsSetMarkedPointsSmoothPossible() const { ForcePossibilities(); return bSetMarkedPointsSmoothPossible; }
    SdrPathSmoothKind GetMarkedPointsSmooth() const { ForcePossibilities(); return eMarkedPointsSmooth; }
//STRIP001  void SetMarkedPointsSmooth(SdrPathSmoothKind eKind);

    // Ein PolySegment kann eine Strecke oder eine Bezierkurve sein.
    BOOL IsSetMarkedSegmentsKindPossible() const { ForcePossibilities(); return bSetMarkedSegmentsKindPossible; }
    SdrPathSegmentKind GetMarkedSegmentsKind() const { ForcePossibilities(); return eMarkedSegmentsKind; }
//STRIP001  void SetMarkedSegmentsKind(SdrPathSegmentKind eKind);

    // Moeglicherweise ist das Obj hinterher geloescht:
//STRIP001  void DeleteMarkedPoints();
    BOOL IsDeleteMarkedPointsPossible() const { return HasMarkedPoints(); }

//STRIP001  void MoveMarkedPoints(const Size& rSiz, BOOL bCopy=FALSE);
//STRIP001  void ResizeMarkedPoints(const Point& rRef, const Fraction& xFact, const Fraction& yFact, BOOL bCopy=FALSE);
//STRIP001  void RotateMarkedPoints(const Point& rRef, long nWink, BOOL bCopy=FALSE);

    // Hierbei entstehen eventuell beliebig viele neue Objekte:
//STRIP001  void RipUpAtMarkedPoints();
//STRIP001  BOOL IsRipUpAtMarkedPointsPossible() const;

    // Alle markierten Polylines werden zu Polygonen, alle offenen
    // Bezierkurven zu geschlossenen.
//STRIP001  void ShutMarkedObjects();
//STRIP001  void CloseMarkedObjects(BOOL bToggle=FALSE, BOOL bOpen=FALSE, long nOpenDistance=0);
//STRIP001  void OpenMarkedObjects(long nOpenDistance=0) { CloseMarkedObjects(FALSE,TRUE,nOpenDistance); }
//STRIP001  BOOL IsOpenCloseMarkedObjectsPossible() const;
//STRIP001  SdrObjClosedKind GetMarkedObjectsClosedState() const;
};

}//end of namespace binfilter
#endif //_SVDPOEV_HXX

