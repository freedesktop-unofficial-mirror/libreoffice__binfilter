/*************************************************************************
 *
 *  $RCSfile: sch_schgroup.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 12:48:11 $
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

#pragma hdrstop

// auto strip #ifndef _SVDOPATH_HXX //autogen
// auto strip #include <bf_svx/svdopath.hxx>
// auto strip #endif
// auto strip #ifndef _SVDHDL_HXX //autogen
// auto strip #include <bf_svx/svdhdl.hxx>
// auto strip #endif
// auto strip #ifndef _SVDPAGE_HXX //autogen
// auto strip #include <bf_svx/svdpage.hxx>
// auto strip #endif

#include "glob.hxx"
// auto strip #include "schdll.hxx"
// auto strip #include "objid.hxx"
// auto strip #include "chtmodel.hxx"
#include "schgroup.hxx"
#include <math.h>
namespace binfilter {

/*N*/ TYPEINIT1(SchObjGroup, SdrObjGroup);


/*************************************************************************
|*
|* Konstruktor
|*
\************************************************************************/

/*N*/ SchObjGroup::SchObjGroup(ChartModel *pChmodel) :
/*N*/   SdrObjGroup(),
/*N*/   bAskForLogicRect(TRUE),
/*N*/     mbUseChartInventor( true )
/*N*/ {
/*N*/   // FG: Damit soll es Objekten im chart ermoeglicht werden sich wie ein
/*N*/   //     Objekt im Draw zu verhalten falls gewünscht. Nicht alles was
/*N*/   //     prinzipiell geht soll man auch koennen.
/*N*/   aInfo.bResizeFreeAllowed    = TRUE;
/*N*/   aInfo.bResizePropAllowed    = TRUE;
/*N*/   aInfo.bRotateFreeAllowed    = TRUE;
/*N*/   aInfo.bRotate90Allowed      = TRUE;
/*N*/   aInfo.bMirrorFreeAllowed    = FALSE;
/*N*/   aInfo.bMirror45Allowed      = FALSE;
/*N*/   aInfo.bMirror90Allowed      = FALSE;
/*N*/   aInfo.bShearAllowed         = TRUE;
/*N*/
/*N*/   eChartGroupType = NOTHING;
/*N*/   pChartmodel = pChmodel;
/*N*/   SetModel( pChartmodel );
/*N*/ }

/*************************************************************************
|*
|* Destruktor
|*
\************************************************************************/

/*N*/ SchObjGroup::~SchObjGroup()
/*N*/ {
/*N*/ }

/*************************************************************************
|*
|* Identifier zurueckgeben
|*
\************************************************************************/

/*N*/ UINT32 SchObjGroup::GetObjInventor() const
/*N*/ {
/*N*/     if( mbUseChartInventor )
/*N*/         return SchInventor;
/*N*/     else
/*?*/         return SdrInventor;
/*N*/ }

/*************************************************************************
|*
|* Identifier zurueckgeben
|*
\************************************************************************/

/*N*/ UINT16 SchObjGroup::GetObjIdentifier() const
/*N*/ {
/*N*/   return SCH_OBJGROUP_ID;
/*N*/ }

/*************************************************************************
|*
|* Handle-Anzahl bestimmen
|*
\************************************************************************/

//STRIP001 USHORT SchObjGroup::GetHdlCount() const
//STRIP001 {
//STRIP001  USHORT nCount = 0;
//STRIP001  BOOL bLine = FALSE;
//STRIP001
//STRIP001  SdrObjListIter aIterator(*GetSubList(), IM_DEEPNOGROUPS);
//STRIP001
//STRIP001  while (aIterator.IsMore())
//STRIP001  {
//STRIP001      SdrObject* pObj = aIterator.Next();
//STRIP001      SchObjectId* pId = GetObjectId(*pObj);
//STRIP001
//STRIP001      if (pId)
//STRIP001          if (!bLine)
//STRIP001          {
//STRIP001              if (pId && pId->GetObjId() == CHOBJID_LINE)
//STRIP001              {
//STRIP001                  bLine = TRUE;
//STRIP001                  nCount = 2;
//STRIP001              }
//STRIP001              else if (pObj->GetObjIdentifier() != OBJ_TEXT) nCount++;
//STRIP001          }
//STRIP001          else if (pId && pId->GetObjId() == CHOBJID_LINE) nCount += 2;
//STRIP001  }
//STRIP001
//STRIP001  return nCount;
//STRIP001 }

/*************************************************************************
|*
|* Handle erzeugen
|*
\************************************************************************/

//STRIP001 SdrHdl* SchObjGroup::GetHdl(USHORT nHdlNum) const
//STRIP001 {
//STRIP001  USHORT nCount = 0;
//STRIP001  BOOL bLine = FALSE;
//STRIP001
//STRIP001  SdrObject* pObj = NULL;
//STRIP001  SdrObjListIter aIterator(*GetSubList(), IM_DEEPNOGROUPS);
//STRIP001
//STRIP001  while (nCount <= nHdlNum && aIterator.IsMore())
//STRIP001  {
//STRIP001      pObj = aIterator.Next();
//STRIP001      SchObjectId* pId = GetObjectId(*pObj);
//STRIP001
//STRIP001      if (pId)
//STRIP001          if (!bLine)
//STRIP001          {
//STRIP001              if (pId && pId->GetObjId() == CHOBJID_LINE)
//STRIP001              {
//STRIP001                  bLine = TRUE;
//STRIP001                  nCount = 2;
//STRIP001              }
//STRIP001              else if (pObj->GetObjIdentifier() != OBJ_TEXT) nCount++;
//STRIP001          }
//STRIP001          else if (pId && pId->GetObjId() == CHOBJID_LINE) nCount += 2;
//STRIP001  }
//STRIP001
//STRIP001  Point aPos;
//STRIP001
//STRIP001  if (pObj)
//STRIP001  {
//STRIP001      if (bLine)
//STRIP001      {
//STRIP001          const XPolygon& rXPoly = ((SdrPathObj*)pObj)->GetPathPoly()[0];
//STRIP001          aPos = rXPoly[nHdlNum % 2];
//STRIP001      }
//STRIP001      else if (pObj->ISA(SdrPathObj))
//STRIP001      {
//STRIP001          const XPolygon& rXPoly = ((SdrPathObj*)pObj)->GetPathPoly()[0];
//STRIP001          aPos = rXPoly[1];
//STRIP001      }
//STRIP001      else
//STRIP001          aPos = pObj->GetBoundRect().Center();
//STRIP001  }
//STRIP001
//STRIP001  return new SdrHdl(aPos, HDL_MOVE);
//STRIP001 }

/*************************************************************************
|*
|* Handle-Liste fuellen
|*
\************************************************************************/

//STRIP001 void SchObjGroup::AddToHdlList(SdrHdlList& rHdlList) const
//STRIP001 {
//STRIP001  BOOL bLine = FALSE;
//STRIP001
//STRIP001  SdrObjListIter aIterator(*GetSubList(), IM_DEEPWITHGROUPS);
//STRIP001
//STRIP001  while (aIterator.IsMore())
//STRIP001  {
//STRIP001      SdrObject* pObj = aIterator.Next();
//STRIP001      SchObjectId* pId = GetObjectId(*pObj);
//STRIP001      if (pId && (pId->GetObjId() == CHOBJID_LINE))
//STRIP001      {
//STRIP001          bLine = TRUE;
//STRIP001          break;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  aIterator.Reset();
//STRIP001
//STRIP001  while (aIterator.IsMore())
//STRIP001  {
//STRIP001      SdrObject* pObj = aIterator.Next();
//STRIP001      SchObjectId* pId = GetObjectId(*pObj);
//STRIP001      Point aPos;
//STRIP001
//STRIP001      if (pId)
//STRIP001          if (!bLine)
//STRIP001          {
//STRIP001              if (pObj->GetObjIdentifier() != OBJ_TEXT)
//STRIP001              {
//STRIP001                  if (pObj->ISA(SdrPathObj))
//STRIP001                  {
//STRIP001                         const XPolyPolygon& rPolyPoly = static_cast< const SdrPathObj & >( *pObj ).GetPathPoly();
//STRIP001                         if( rPolyPoly.Count() > 0 )
//STRIP001                             aPos = (rPolyPoly[ 0 ])[ 1 ];
//STRIP001                  }
//STRIP001                  else aPos = pObj->GetBoundRect().Center();
//STRIP001
//STRIP001                  SdrHdl* pHdl = new SdrHdl(aPos, HDL_MOVE);
//STRIP001                  rHdlList.AddHdl(pHdl);
//STRIP001              }
//STRIP001          }
//STRIP001          else if (pId)
//STRIP001               {
//STRIP001                   switch (pId->GetObjId())
//STRIP001                   {
//STRIP001                       case CHOBJID_LINE :
//STRIP001                       case CHOBJID_DIAGRAM_AVERAGEVALUE :
//STRIP001                       {
//STRIP001                              DBG_ASSERT( pObj->ISA( SdrPathObj ), "chart line is no path object" );
//STRIP001                              const XPolyPolygon& rPolyPoly = static_cast< const SdrPathObj & >( *pObj ).GetPathPoly();
//STRIP001                              DBG_ASSERT( rPolyPoly.Count() > 0, "Empty poly-polygon found" );
//STRIP001                           for (USHORT i = 0; i < 2; i++)
//STRIP001                           {
//STRIP001                               aPos = (rPolyPoly[ 0 ])[ i ];
//STRIP001                               SdrHdl* pHdl = new SdrHdl(aPos, HDL_MOVE);
//STRIP001                               rHdlList.AddHdl(pHdl);
//STRIP001                           }
//STRIP001                       }
//STRIP001
//STRIP001                       case CHOBJID_DIAGRAM_NET :
//STRIP001                       {
//STRIP001                           aPos = pObj->GetBoundRect().Center();
//STRIP001
//STRIP001                           SdrHdl* pHdl = new SdrHdl(aPos, HDL_MOVE);
//STRIP001                           rHdlList.AddHdl(pHdl);
//STRIP001                       }
//STRIP001
//STRIP001                       default :
//STRIP001                           ;
//STRIP001                   }
//STRIP001               }
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|* Identifier zurueckgeben
|*
\************************************************************************/

//STRIP001 FASTBOOL SchObjGroup::HasSpecialDrag() const
//STRIP001 {
//STRIP001  return TRUE;
//STRIP001 }


/*************************************************************************
|*
|* Faehigkeiten der Chart-Gruppe feststellen
|*
\************************************************************************/

//STRIP001 void SchObjGroup::TakeObjInfo(SdrObjTransformInfoRec& rInfo) const
//STRIP001 {
//STRIP001  // FG: Damit soll es Objekten im chart ermoeglicht werden sich wie ein
//STRIP001  //     Objekt im Draw zu verhalten falls gewünscht.
//STRIP001  rInfo.bResizeFreeAllowed    = aInfo.bResizeFreeAllowed;
//STRIP001  rInfo.bResizePropAllowed    = aInfo.bResizePropAllowed;
//STRIP001  rInfo.bRotateFreeAllowed    = aInfo.bRotateFreeAllowed;
//STRIP001  rInfo.bRotate90Allowed      = aInfo.bRotate90Allowed;
//STRIP001  rInfo.bMirrorFreeAllowed    = aInfo.bMirrorFreeAllowed;
//STRIP001  rInfo.bMirror45Allowed      = aInfo.bMirror45Allowed;
//STRIP001  rInfo.bMirror90Allowed      = aInfo.bMirror90Allowed;
//STRIP001  rInfo.bShearAllowed         = aInfo.bShearAllowed;
//STRIP001 }

/*************************************************************************
|*
|* Faehigkeiten der Chart-Gruppe zuweisen
|*
\************************************************************************/

/*N*/ void  SchObjGroup::SetObjInfo(SdrObjTransformInfoRec aMyInfo)
/*N*/ {
/*N*/   // FG: Damit soll es Objekten im chart ermoeglicht werden sich wie ein
/*N*/   //     Objekt im Draw zu verhalten falls gewünscht.
/*N*/   aInfo.bResizeFreeAllowed    = aMyInfo.bResizeFreeAllowed;
/*N*/   aInfo.bResizePropAllowed    = aMyInfo.bResizePropAllowed;
/*N*/   aInfo.bRotateFreeAllowed    = aMyInfo.bRotateFreeAllowed;
/*N*/   aInfo.bRotate90Allowed      = aMyInfo.bRotate90Allowed;
/*N*/   aInfo.bMirrorFreeAllowed    = aMyInfo.bMirrorFreeAllowed;
/*N*/   aInfo.bMirror45Allowed      = aMyInfo.bMirror45Allowed;
/*N*/   aInfo.bMirror90Allowed      = aMyInfo.bMirror90Allowed;
/*N*/   aInfo.bShearAllowed         = aMyInfo.bShearAllowed;
/*N*/ }

/*************************************************************************
|*
|* Wirkliches Resize einer Chart-Gruppe (ohne Broadcast)
|* Bei manchen Chart-Gruppen ist eine Neuberechnung bei einem Resize
|* besser als ein hartes Resize.
|*
\************************************************************************/

//STRIP001 void SchObjGroup::NbcResize(const Point& rRef, const Fraction& xFact, const Fraction& yFact)
//STRIP001 {
//STRIP001 }

/*************************************************************************
|*
|* Um das Verhalten bei einem Resize in Abhaehngigkeit des selektierten
|* Objektes zu ernoeglichen. Bei Diagramme werden nicht die Teilobjekte
|* Resized sondern das Chart in den neuen Grenzen aufgebaut.
|*
\************************************************************************/

//STRIP001 void SchObjGroup::Resize(const Point& rRef, const Fraction& xFact, const Fraction& yFact)
//STRIP001 {
//STRIP001  if (eChartGroupType == DIAGRAM)
//STRIP001  {
//STRIP001      DBG_ASSERT(pChartmodel, "Bei der Diagrammgruppe muss das Model gesetzt sein!");
//STRIP001      if (pChartmodel != NULL)
//STRIP001      {
//STRIP001          // FG: Der folgende Teil ist noetig da das BoundRect die Größe des Charts ohne
//STRIP001          //     die Beschriftung darstellt und genau dieses wird Resized.
//STRIP001          //     Die Handles der 2d-Charts sitzen an den Achsen, die Textgroesse
//STRIP001          //     der Beschriftung soll ja nicht veraendert werden.
//STRIP001          //     CreateChart und BuildChart achten aber auf das ChartRect, das eigentlich
//STRIP001          //     nichts mit dem BoundRect der Subliste oder aehnlichem zu tun hat.
//STRIP001          //     Man verkleinert also das "falsche" BoundRect und zaehlt am Schluss den Platz
//STRIP001          //     fuer die Beschriftung hinzu.
//STRIP001          //     Ein besserer Weg waere es hier zwischen dem Platz fuer die Beschriftung und
//STRIP001          //     dem der eigentlichen Diagrammflaeche zu unterscheiden.
//STRIP001          //
//STRIP001          Rectangle aRectChart = pChartmodel->GetChartRect();
//STRIP001          Rectangle aRect = GetBoundRect();
//STRIP001          Point aPointBottomLeftRectChart = aRectChart.BottomLeft();
//STRIP001          Point aPointBottomLeftBoundRect = aRect.BottomLeft();
//STRIP001          Point aPointTopRightRectChart = aRectChart.TopRight();
//STRIP001          Point aPointTopRightBoundRect = aRect.TopRight();
//STRIP001          Point aDifferenceLeftBottom = aPointBottomLeftRectChart - aPointBottomLeftBoundRect;
//STRIP001          Point aDifferenceTopRight = aPointTopRightRectChart - aPointTopRightBoundRect;
//STRIP001          aRect.nRight = rRef.nA + (long) ((aRect.nRight - rRef.nA) * xFact.GetNumerator()
//STRIP001                                                          / xFact.GetDenominator());
//STRIP001          aRect.nLeft = rRef.nA + (long) ((aRect.nLeft - rRef.nA) * xFact.GetNumerator()
//STRIP001                                                        / xFact.GetDenominator());
//STRIP001          aRect.nTop = rRef.nB + (long) ((aRect.nTop - rRef.nB) * yFact.GetNumerator()
//STRIP001                                                    / yFact.GetDenominator());
//STRIP001          aRect.nBottom = rRef.nB + (long) ((aRect.nBottom - rRef.nB) * yFact.GetNumerator()
//STRIP001                                                           / yFact.GetDenominator());
//STRIP001          // FG: 11.3.97 Dies hier soll ein BuildChart mit geaenderten Koordinaten fuer diese
//STRIP001          //     eine Gruppe erzwingen.
//STRIP001 //           pSub->Clear();
//STRIP001             // The above does not result in a BuildChart and besides it is bad style
//STRIP001             // to flush an object on resize.  And by the way it results in a GPF (#97355#)
//STRIP001          bAskForLogicRect = FALSE;
//STRIP001          aRect.Left() += aDifferenceLeftBottom.X();
//STRIP001          aRect.Bottom() += aDifferenceLeftBottom.Y();
//STRIP001          aRect.Right() += aDifferenceTopRight.X();
//STRIP001          aRect.Top() += aDifferenceTopRight.Y();
//STRIP001          pChartmodel->SetDiagramRectangle(aRect);
//STRIP001          SetChanged();
//STRIP001      }
//STRIP001      if (pUserCall!=NULL) pUserCall->Changed(*this,SDRUSERCALL_RESIZE,GetLogicRect());
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      SdrObjGroup::Resize(rRef, xFact, yFact);
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|* Um mitzubekommen welche Objekte bewegt werden. Leider wird das
|* nicht nur vom Benutzer verursacht.
|*
\************************************************************************/

/*N*/ void SchObjGroup::Move(const Size& rSiz)
/*N*/ {
/*N*/
/*N*/   if (eChartGroupType == DIAGRAM)
/*N*/   {
/*?*/       DBG_ASSERT( pChartmodel, "No Model" );
/*?*/       if (pChartmodel != NULL)
/*?*/       {
/*?*/           Rectangle aRectChart = pChartmodel->GetChartRect();
/*?*/           Rectangle aRect = GetBoundRect();
/*?*/           Point aPointBottomLeftRectChart = aRectChart.BottomLeft();
/*?*/           Point aPointBottomLeftBoundRect = aRect.BottomLeft();
/*?*/           Point aPointTopRightRectChart = aRectChart.TopRight();
/*?*/           Point aPointTopRightBoundRect = aRect.TopRight();
/*?*/           Point aDifferenceLeftBottom = aPointBottomLeftRectChart - aPointBottomLeftBoundRect;
/*?*/           Point aDifferenceTopRight = aPointTopRightRectChart - aPointTopRightBoundRect;
/*?*/           aRect.Left() += rSiz.Width();
/*?*/           aRect.Right() += rSiz.Width();
/*?*/           aRect.Top() += rSiz.Height();
/*?*/           aRect.Bottom() += rSiz.Height();
/*?*/           bAskForLogicRect = FALSE;
/*?*/           aRect.Left() += aDifferenceLeftBottom.X();
/*?*/           aRect.Bottom() += aDifferenceLeftBottom.Y();
/*?*/           aRect.Right() += aDifferenceTopRight.X();
/*?*/           aRect.Top() += aDifferenceTopRight.Y();
/*?*/           pChartmodel->SetDiagramRectangle(aRect);
/*?*/       }
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       SdrObjGroup::Move(rSiz);
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* Um mitzubekommen welche Objekte bewegt werden. Leider wird das
|* nicht nur vom Benutzer verursacht.
|*
\************************************************************************/

//STRIP001 void SchObjGroup::SetGroupMoved(BOOL value)
//STRIP001 {
//STRIP001  switch (eChartGroupType)
//STRIP001  {
//STRIP001      case (DIAGRAM):
//STRIP001          if (pChartmodel != NULL)
//STRIP001          {
//STRIP001              pChartmodel->SetDiagramHasBeenMovedOrResized(value);
//STRIP001          }
//STRIP001          break;
//STRIP001      case (LEGEND):
//STRIP001          if (pChartmodel != NULL)
//STRIP001          {
//STRIP001              pChartmodel->SetLegendHasBeenMoved( value );
//STRIP001                 pChartmodel->SetLegendPos( GetLogicRect().TopLeft());
//STRIP001          }
//STRIP001          break;
//STRIP001
//STRIP001  }
//STRIP001 }

/*N*/ void SchObjGroup::SetUseChartInventor( bool bUseChartInventor )
/*N*/ {
/*N*/     mbUseChartInventor = bUseChartInventor;
/*N*/ }

}
