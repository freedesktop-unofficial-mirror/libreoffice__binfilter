/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_view3d.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 20:51:53 $
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

#define ITEMID_COLOR 0











#ifndef _XOUTX_HXX
#include "xoutx.hxx"
#endif

#ifndef _SVX_SVXIDS_HRC
#include <svxids.hrc>
#endif


#ifndef _XTABLE_HXX
#include "xtable.hxx"
#endif


#ifndef _SVX_DIALOGS_HRC
#include "dialogs.hrc"
#endif










#ifndef _E3D_POLYSC3D_HXX
#include "polysc3d.hxx"
#endif


#ifndef _E3D_VIEW3D_HXX
#include "view3d.hxx"
#endif







namespace binfilter {

#define ITEMVALUE(ItemSet,Id,Cast)  ((const Cast&)(ItemSet).Get(Id)).GetValue()

/*N*/ TYPEINIT1(E3dView, SdrView);

long Scalar (Point aPoint1,
             Point aPoint2);

Point ScaleVector (Point  aPoint,
                   double nScale);

double NormVector (Point aPoint);

BOOL LineCutting (Point aP1,
                  Point aP2,
                  Point aP3,
                  Point aP4);

long Point2Line (Point aP1,
                 Point aP2,
                 Point aP3);

long DistPoint2Line (Point u,
                     Point v1,
                     Point v);

/*************************************************************************
|*
|* Konstruktor 1
|*
\************************************************************************/

/*N*/ E3dView::E3dView(SdrModel* pModel, OutputDevice* pOut) :
/*N*/     SdrView(pModel, pOut)
/*N*/ {
/*N*/   InitView ();
/*N*/ }

/*************************************************************************
|*
|* Konstruktor 2
|*
\************************************************************************/

/*?*/ E3dView::E3dView(SdrModel* pModel, ExtOutputDevice* pExtOut) :
/*?*/     SdrView(pModel, pExtOut)
/*?*/ {
/*?*/   InitView ();
/*?*/ }

/*************************************************************************
|*
|* Konstruktor 3
|*
\************************************************************************/

/*?*/ E3dView::E3dView(SdrModel* pModel) :
/*?*/     SdrView(pModel)
/*?*/ {
/*?*/   InitView ();
/*?*/ }

/*************************************************************************
|*
|* DrawMarkedObj ueberladen, da eventuell nur einzelne 3D-Objekte
|* gezeichnet werden sollen
|*
\************************************************************************/


/*************************************************************************
|*
|* Model holen ueberladen, da bei einzelnen 3D Objekten noch eine Szene
|* untergeschoben werden muss
|*
\************************************************************************/


/*************************************************************************
|*
|* Bei Paste muss - falls in eine Scene eingefuegt wird - die
|* Objekte der Szene eingefuegt werden, die Szene selbst aber nicht
|*
\************************************************************************/


// #83403# Service routine used from local Clone() and from SdrCreateView::EndCreateObj(...)

/*************************************************************************
|*
|* 3D-Konvertierung moeglich?
|*
\************************************************************************/

/*N*/ BOOL E3dView::IsConvertTo3DObjPossible() const
/*N*/ {
/*N*/   BOOL bAny3D(FALSE);
/*N*/   BOOL bGroupSelected(FALSE);
/*N*/   BOOL bRetval(TRUE);
/*N*/
/*N*/   for(sal_uInt32 a=0;!bAny3D && a<aMark.GetMarkCount();a++)
/*N*/   {
/*?*/       SdrObject *pObj = aMark.GetMark(a)->GetObj();
/*?*/       if(pObj)
/*?*/       {
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 ImpIsConvertTo3DPossible(pObj, bAny3D, bGroupSelected);
/*?*/       }
/*N*/   }
/*N*/
/*N*/   bRetval = !bAny3D
/*N*/       && (
/*N*/          IsConvertToPolyObjPossible(FALSE)
/*N*/       || IsConvertToPathObjPossible(FALSE)
/*N*/       || IsImportMtfPossible());
/*N*/   return bRetval;
/*N*/ }


/*************************************************************************
|*
|* 3D-Konvertierung zu Extrude ausfuehren
|*
\************************************************************************/






/*************************************************************************
|*
|* 3D-Konvertierung zu Extrude steuern
|*
\************************************************************************/


/*************************************************************************
|*
|* Alle enthaltenen Extrude-Objekte Tiefenarrangieren
|*
\************************************************************************/




/*************************************************************************
|*
|* Drag beginnen, vorher ggf. Drag-Methode fuer 3D-Objekte erzeugen
|*
\************************************************************************/


/*************************************************************************
|*
|* Pruefen, obj 3D-Szene markiert ist
|*
\************************************************************************/


/*************************************************************************
|*
|* Pruefen, obj 3D-Szene markiert ist
|*
\************************************************************************/


/*************************************************************************
|*
|* aktuelles 3D-Zeichenobjekt setzen, dafuer Szene erzeugen
|*
\************************************************************************/


/*************************************************************************
|*
|* neu erzeugte Szene initialisieren
|*
\************************************************************************/


/*************************************************************************
|*
|* startsequenz fuer die erstellung eines 3D-Rotationskoerpers
|*
\************************************************************************/


/*************************************************************************
|*
|* was passiert bei einer Mausbewegung, wenn das Objekt erstellt wird ?
|*
\************************************************************************/


/*************************************************************************
|*
|* Schluss. Objekt und evtl. Unterobjekte ueber ImpCreate3DLathe erstellen
|*          [FG] Mit dem Parameterwert TRUE (SDefault: FALSE) wird einfach ein
|*               Rotationskoerper erzeugt, ohne den Benutzer die Lage der
|*               Achse fetlegen zu lassen. Es reicht dieser Aufruf, falls
|*               ein Objekt selektiert ist. (keine Initialisierung noetig)
|*
\************************************************************************/


/*************************************************************************
|*
|* stelle das Mirrorobjekt dar
|*
\************************************************************************/

/*N*/ void E3dView::ShowMirrored ()
/*N*/ {
/*N*/   if (b3dCreationActive)
/*N*/   {
/*?*/       OutputDevice  *pOut = GetWin(0);
/*?*/       RasterOp      eRop0 = pOut->GetRasterOp();
/*?*/
/*?*/       Color aOldLineColor( pXOut->GetLineColor() );
/*?*/       Color aOldFillColor( pXOut->GetFillColor() );
/*?*/       Color aNewLineColor( COL_BLACK );
/*?*/       Color aNewFillColor( COL_TRANSPARENT );
/*?*/
/*?*/
/*?*/       // invertiere die Darstellung
/*?*/       pOut->SetRasterOp(ROP_INVERT);
/*?*/       pXOut->SetOutDev(pOut);
/*?*/       pXOut->OverrideLineColor( aNewLineColor );
/*?*/       pXOut->OverrideFillColor( aNewFillColor );
/*?*/
/*?*/       for (long nMark = 0;
/*?*/                 nMark < nPolyCnt;
/*?*/                 nMark ++)
/*?*/       {
/*?*/           const XPolyPolygon &rXPP    = pMirroredPolygon [nMark];
/*?*/           USHORT             nPolyAnz = rXPP.Count();
/*?*/
/*?*/             for (USHORT nPolyNum = 0;
/*?*/                        nPolyNum < nPolyAnz;
/*?*/                        nPolyNum ++)
/*?*/           {
/*?*/               const XPolygon &rXP = rXPP [nPolyNum];
/*?*/
/*?*/               pXOut->DrawXPolyLine(rXP);
/*?*/           }
/*?*/       }
/*?*/
/*?*/       pXOut->OverrideLineColor( aOldLineColor );
/*?*/       pXOut->OverrideFillColor( aOldFillColor );
/*?*/       pOut->SetRasterOp(eRop0);
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* Destruktor
|*
\************************************************************************/

/*N*/ E3dView::~E3dView ()
/*N*/ {
/*N*/   /*#90353#*/delete [] pMirrorPolygon;
/*N*/   /*#90353#*/delete [] pMirroredPolygon;
/*N*/   /*#90353#*/delete [] pMarkedObjs;
/*N*/ }

/*************************************************************************
|*
|* Bestimme Anzahl der Polygone und kopiere in die Spiegelpolygone
|*
\************************************************************************/


/*************************************************************************
|*
|* spiegele die originalpolygone und stelle sie als hilfsfigur dar
|*
\************************************************************************/


/*************************************************************************
|*
|* beende das erzeugen und loesche die polygone
|*
\************************************************************************/

/*N*/ void E3dView::ResetCreationActive ()
/*N*/ {
/*N*/   /*#90353#*/delete [] pMirrorPolygon;
/*N*/   /*#90353#*/delete [] pMirroredPolygon;
/*N*/   /*#90353#*/delete [] pMarkedObjs;
/*N*/
/*N*/   pMarkedObjs       = 0;
/*N*/   pMirrorPolygon    =
/*N*/   pMirroredPolygon  = 0;
/*N*/   b3dCreationActive = FALSE;
/*N*/   nPolyCnt          = 0;
/*N*/ }

/*************************************************************************
|*
|* Skalarprodukt zweier Punktvektoren
|*
\************************************************************************/


/*************************************************************************
|*
|* Skalarprodukt zweier Punktvektoren
|*
\************************************************************************/


/*************************************************************************
|*
|* Skalarprodukt zweier Punktvektoren
|*
\************************************************************************/


/*************************************************************************
|*
|* Pruefe, ob sich zwei Geradensegemente schneiden
|* Dazu wird ueber einfache Determinanten bestimmt, wie die Endpunkte
|* zu der jeweils anderen Gerade liegen.
|*
\************************************************************************/


/*************************************************************************
|*
|* Bestimme, ob sich ein Punkt aP1 rechts oder links eines Geradensegments,
|* definiert durch aP2 und aP3, befindet.
|* >0 : rechts, <0 : links, =0 : auf dem Geradensegment
|* Die Vektoren (Punkte) liegen in der homogenen Form vor, wobei die
|* Skalierung =1 gesetzt ist (schneller und einfacher).
|*
\************************************************************************/


/*************************************************************************
|*
|* Bestimme den Abstand eines Punktes u zu einem Geradensegment,
|* definiert durch v1 und v.
|*
\************************************************************************/


/*************************************************************************
|*
|* Klasse initialisieren
|*
\************************************************************************/

/*N*/ void E3dView::InitView ()
/*N*/ {
/*N*/   eDragConstraint          = E3DDRAG_CONSTR_XYZ;
/*N*/   eDragDetail              = E3DDETAIL_ONEBOX;
/*N*/   b3dCreationActive        = FALSE;
/*N*/   pMirrorPolygon           = 0;
/*N*/   pMirroredPolygon         = 0;
/*N*/   nPolyCnt                 = 0;
/*N*/   pMyPV                    = 0;
/*N*/   pMarkedObjs              = 0;
/*N*/   fDefaultScaleX           =
/*N*/   fDefaultScaleY           =
/*N*/   fDefaultScaleZ           = 1.0;
/*N*/   fDefaultRotateX          =
/*N*/   fDefaultRotateY          =
/*N*/   fDefaultRotateZ          = 0.0;
/*N*/   fDefaultExtrusionDeepth  = 1000; // old: 2000;
/*N*/   fDefaultLightIntensity   = 0.8; // old: 0.6;
/*N*/   fDefaultAmbientIntensity = 0.4;
/*N*/     nHDefaultSegments        = 12;
/*N*/     nVDefaultSegments        = 12;
/*N*/     aDefaultLightColor       = RGB_Color(COL_WHITE);
/*N*/     aDefaultAmbientColor     = RGB_Color(COL_BLACK);
/*N*/   aDefaultLightPos         = Vector3D (1, 1, 1); // old: Vector3D (0, 0, 1);
/*N*/   aDefaultLightPos.Normalize();
/*N*/     bDoubleSided             = FALSE;
/*N*/ }

/*************************************************************************
|*
|* Zeige eine Hilfsfigur
|*
\************************************************************************/


/*************************************************************************
|*
|* Verdecke eine Hilfsfigur
|*
\************************************************************************/


/*************************************************************************
|*
|* Zeige eine Hilfsfigur
|*
\************************************************************************/


/*************************************************************************
|*
|* Koennen die selektierten Objekte aufgebrochen werden?
|*
\************************************************************************/


/*************************************************************************
|*
|* Selektierte Lathe-Objekte aufbrechen
|*
\************************************************************************/



/*************************************************************************
|*
|* Szenen mischen
|*
\************************************************************************/
// Wird bisher noch nirgenswo (weder im Draw oder Chart) aufgerufen


/*************************************************************************
|*
|* Possibilities, hauptsaechlich gruppieren/ungruppieren
|*
\************************************************************************/
/*N*/ void E3dView::CheckPossibilities()
/*N*/ {
/*N*/   // call parent
/*N*/   SdrView::CheckPossibilities();
/*N*/
/*N*/   // Weitere Flags bewerten
/*N*/   if(bGroupPossible || bUnGroupPossible || bGrpEnterPossible)
/*N*/   {
/*?*/       INT32 nMarkCnt = aMark.GetMarkCount();
/*?*/       BOOL bCoumpound = FALSE;
/*?*/       BOOL b3DObject = FALSE;
/*?*/       for(INT32 nObjs = 0L; (nObjs < nMarkCnt) && !bCoumpound; nObjs++)
/*?*/       {
/*?*/           SdrObject *pObj = aMark.GetMark(nObjs)->GetObj();
/*?*/           if(pObj && pObj->ISA(E3dCompoundObject))
/*?*/               bCoumpound = TRUE;
/*?*/           if(pObj && pObj->ISA(E3dObject))
/*?*/               b3DObject = TRUE;
/*?*/       }
/*?*/
/*?*/       // Bisher: Es sind ZWEI oder mehr beliebiger Objekte selektiert.
/*?*/       // Nachsehen, ob CompoundObjects beteiligt sind. Falls ja,
/*?*/       // das Gruppieren verbieten.
/*?*/       if(bGroupPossible && bCoumpound)
/*?*/           bGroupPossible = FALSE;
/*?*/
/*?*/       if(bUnGroupPossible && b3DObject)
/*?*/           bUnGroupPossible = FALSE;
/*?*/
/*?*/       if(bGrpEnterPossible && bCoumpound)
/*?*/           bGrpEnterPossible = FALSE;
/*N*/   }

//  bGroupPossible
//  bCombinePossible
//  bUnGroupPossible
//  bGrpEnterPossible
/*N*/ }



}
