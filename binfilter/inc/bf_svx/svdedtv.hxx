/*************************************************************************
 *
 *  $RCSfile: svdedtv.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:28:47 $
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

#ifndef _SVDEDTV_HXX
#define _SVDEDTV_HXX

// HACK to avoid too deep includes and to have some
// levels free in svdmark itself (MS compiler include depth limit)
#ifndef _SVDHDL_HXX
#include <bf_svx/svdhdl.hxx>
#endif

#include <bf_svx/svdmrkv.hxx>

#ifndef _XPOLY_HXX
#include <bf_svx/xpoly.hxx>
#endif

#ifndef _SVDMODEL_HXX
#include <bf_svx/svdmodel.hxx>
#endif
class SfxUndoAction;
class SfxStyleSheet;
namespace binfilter {

//************************************************************
//   Vorausdeklarationen
//************************************************************

class SdrUndoAction;
class SdrUndoGroup;
class SdrLayer;
class SvdProgressInfo;

//************************************************************
//   Defines
//************************************************************

enum SdrHorAlign  {
    SDRHALIGN_NONE,
    SDRHALIGN_LEFT,
    SDRHALIGN_RIGHT,
    SDRHALIGN_CENTER
};

enum SdrVertAlign {
    SDRVALIGN_NONE,
    SDRVALIGN_TOP,
    SDRVALIGN_BOTTOM,
    SDRVALIGN_CENTER
};

enum SdrMergeMode {
    SDR_MERGE_MERGE,
    SDR_MERGE_SUBSTRACT,
    SDR_MERGE_INTERSECT
};

// Optionen fuer InsertObject()
#define SDRINSERT_DONTMARK    0x0001 /* Obj wird nicht markiert (aktuelle Markierung bleibt bestehen) */
#define SDRINSERT_ADDMARK     0x0002 /* Das Obj wird zu einer ggf. bereits bestehenden Selektion hinzumarkiert */
#define SDRINSERT_SETDEFATTR  0x0004 /* Die aktuellen Attribute (+StyleSheet) werden dem Obj zugewiesen */
#define SDRINSERT_SETDEFLAYER 0x0008 /* Der aktuelle Layer wird dem Obj zugewiesen */
#define SDRINSERT_NOBROADCAST 0x0010 /* Einfuegen mit NbcInsertObject() fuer SolidDragging */

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  @@@@@ @@@@@  @@ @@@@@@  @@ @@ @@ @@@@@ @@   @@
//  @@    @@  @@ @@   @@    @@ @@ @@ @@    @@   @@
//  @@    @@  @@ @@   @@    @@ @@ @@ @@    @@ @ @@
//  @@@@  @@  @@ @@   @@    @@@@@ @@ @@@@  @@@@@@@
//  @@    @@  @@ @@   @@     @@@  @@ @@    @@@@@@@
//  @@    @@  @@ @@   @@     @@@  @@ @@    @@@ @@@
//  @@@@@ @@@@@  @@   @@      @   @@ @@@@@ @@   @@
//
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

class SdrEditView: public SdrMarkView
{
    friend class                SdrPageView;

protected:

    // Die Transformationsnachfragen, etc. etwas cachen
    unsigned                    bPossibilitiesDirty : 1;
    unsigned                    bReadOnly : 1;
    unsigned                    bGroupPossible : 1;
    unsigned                    bUnGroupPossible : 1;
    unsigned                    bGrpEnterPossible : 1;
    unsigned                    bDeletePossible : 1;
    unsigned                    bToTopPossible : 1;
    unsigned                    bToBtmPossible : 1;
    unsigned                    bReverseOrderPossible : 1;
    unsigned                    bImportMtfPossible : 1;
    unsigned                    bCombinePossible : 1;
    unsigned                    bDismantlePossible : 1;
    unsigned                    bCombineNoPolyPolyPossible : 1;
    unsigned                    bDismantleMakeLinesPossible : 1;
    unsigned                    bOrthoDesiredOnMarked : 1;
    unsigned                    bMoreThanOneNotMovable : 1;   // Es ist mehr als ein Objekt nicht verschiebbar
    unsigned                    bOneOrMoreMovable : 1;        // Wenigstens 1 Obj verschiebbar
    unsigned                    bMoreThanOneNoMovRot : 1;     // Es ist mehr als ein Objekt nicht verschieb- und drehbar (Crook)
    unsigned                    bContortionPossible : 1;      // Alles Polygone (ggf. gruppiert)
    unsigned                    bAllPolys : 1;                // Alles Polygone (nicht gruppiert)
    unsigned                    bOneOrMorePolys : 1;          // Mindestens 1 Polygon (nicht gruppiert)
    unsigned                    bMoveAllowed : 1;
    unsigned                    bResizeFreeAllowed : 1;
    unsigned                    bResizePropAllowed : 1;
    unsigned                    bRotateFreeAllowed : 1;
    unsigned                    bRotate90Allowed : 1;
    unsigned                    bMirrorFreeAllowed : 1;
    unsigned                    bMirror45Allowed : 1;
    unsigned                    bMirror90Allowed : 1;
    unsigned                    bShearAllowed : 1;
    unsigned                    bEdgeRadiusAllowed : 1;
    unsigned                    bTransparenceAllowed : 1;
    unsigned                    bGradientAllowed : 1;
    unsigned                    bCanConvToPath : 1;
    unsigned                    bCanConvToPoly : 1;
    unsigned                    bCanConvToContour : 1;
    unsigned                    bCanConvToPathLineToArea : 1;
    unsigned                    bCanConvToPolyLineToArea : 1;
    unsigned                    bMoveProtect : 1;
    unsigned                    bResizeProtect : 1;
    unsigned                    bCombineError : 1;
    // Z-Order von virtuellen Objekten zusammenhalten (Writer)
    unsigned                    bBundleVirtObj : 1;

private:
    void ImpClearVars();
    void ImpResetPossibilityFlags();

protected:
//STRIP001  void ImpBroadcastEdgesOfMarkedNodes();

    // Konvertierung der markierten Objekte in Poly bzw. Bezier.
//STRIP001  void ImpConvertTo(BOOL bPath, BOOL bLineToArea);

    // Konvertiert ein Obj, wirft bei Erfolg das alte as seiner Liste und
    // fuegt das neue an dessen Position ein. Inkl Undo. Es wird weder ein
    // MarkEntry noch ein ModelChgBroadcast generiert.
//STRIP001  SdrObject* ImpConvertOneObj(SdrObject* pObj, BOOL bPath, BOOL bLineToArea);

    // Setzen der beiden Flags bToTopPossible und bToBtmPossible.
    // bToTopPossibleDirty und bToBtmPossibleDirty werden dabei gleichzeitig
    // zurueckgesetzt.
    void ImpCheckToTopBtmPossible();

    // fuer den Writer werden virtuelle Objekte buendig zusammengehalten (Z-Order)
//STRIP001  void ImpBundleVirtObjOfMarkList();

    // fuer CombineMarkedObjects und DismantleMarkedObjects
//STRIP001  void ImpCopyAttributes(const SdrObject* pSource, SdrObject* pDest) const;

    // fuer CombineMarkedObjects
//STRIP001  BOOL ImpCanConvertForCombine1(const SdrObject* pObj) const;
//STRIP001  BOOL ImpCanConvertForCombine(const SdrObject* pObj) const;
//STRIP001  XPolyPolygon ImpGetXPolyPoly1(const SdrObject* pObj, BOOL bCombine) const;
//STRIP001  XPolyPolygon ImpGetXPolyPoly(const SdrObject* pObj, BOOL bCombine) const;
//STRIP001  void ImpCombineToSinglePoly(XPolyPolygon& rXPP, long nJoinTol) const;

    // fuer DismantleMarkedObjects
//STRIP001  BOOL ImpCanDismantle(const XPolyPolygon& rXPP, BOOL bMakeLines) const;
//STRIP001  BOOL ImpCanDismantle(const SdrObject* pObj, BOOL bMakeLines) const;
//STRIP001  void ImpDismantleOneObject(const SdrObject* pObj, SdrObjList& rOL, ULONG& rPos, SdrPageView* pPV, BOOL bMakeLines);
//STRIP001  void ImpCrookObj(SdrObject* pO, const Point& rRef, const Point& rRad, SdrCrookMode eMode,
//STRIP001      BOOL bVertical, BOOL bNoContortion, BOOL bRotate, const Rectangle& rMarkRect);
//STRIP001  void ImpDistortObj(SdrObject* pO, const Rectangle& rRef, const XPolygon& rDistortedRect, BOOL bNoContortion);
//STRIP001  BOOL ImpDelLayerCheck(SdrObjList* pOL, SdrLayerID nDelID) const;
//STRIP001  void ImpDelLayerDelObjs(SdrObjList* pOL, SdrLayerID nDelID);

    // Entfernt alle Obj der MarkList aus ihren ObjLists inkl Undo.
    // Die Eintraege in rMark bleiben erhalten. rMark ist nicht const,
    // da ein ForceSort() gerufen wird.
//STRIP001  void DeleteMarked(SdrMarkList& rMark);

    // Die Transformationsnachfragen etwas cachen
    //void ImpCheckMarkTransform() const; veraltet
    // Checken, was man so mit den markierten Objekten alles machen kann
    virtual void CheckPossibilities();
    void ForcePossibilities() const { if (bPossibilitiesDirty || bSomeObjChgdFlag) ((SdrEditView*)this)->CheckPossibilities(); }

public:
    SdrEditView(SdrModel* pModel1, OutputDevice* pOut=NULL);
    SdrEditView(SdrModel* pModel1, ExtOutputDevice* pXOut);
    virtual ~SdrEditView();

    // Jeder Aufruf einer undofaehigen Methode an der View generiert eine
    // UndoAction. Moechte man mehrere
    // Methodenaufrufe zu einer UndoAction zusammenfassen, so kann man diese
    // mit BegUndo() / EndUndo() klammern (beliebig tief). Als Kommentar der
    // UndoAction wird der des ersten BegUndo(String) aller Klammerungen
    // verwendet. NotifyNewUndoAction() wird in diesem Fall erst beim letzten
    // EndUndo() gerufen. NotifyNewUndoAction() wird nicht gerufen bei einer
    // leeren Klammerung.
#ifndef WIN
//STRIP001  void BegUndo()                       { pMod->BegUndo();         } // Undo-Klammerung auf
//STRIP001  void BegUndo(const String& rComment) { pMod->BegUndo(rComment); } // Undo-Klammerung auf
//STRIP001  void BegUndo(const String& rComment, const String& rObjDescr, SdrRepeatFunc eFunc=SDRREPFUNC_OBJ_NONE) { pMod->BegUndo(rComment,rObjDescr,eFunc); } // Undo-Klammerung auf
//STRIP001  void BegUndo(SdrUndoGroup* pUndoGrp) { pMod->BegUndo(pUndoGrp); } // Undo-Klammerung auf
//STRIP001  void EndUndo();                                                   // Undo-Klammerung zu (inkl BroadcastEdges)
//STRIP001  void AddUndo(SdrUndoAction* pUndo)   { pMod->AddUndo(pUndo);    } // Action hinzufuegen
    // nur nach dem 1. BegUndo oder vor dem letzten EndUndo:
//STRIP001  void SetUndoComment(const String& rComment) { pMod->SetUndoComment(rComment); }
//STRIP001  void SetUndoComment(const String& rComment, const String& rObjDescr) { pMod->SetUndoComment(rComment,rObjDescr); }
#else  // ifndef WIN
//STRIP001  void BegUndo();
//STRIP001  void BegUndo(const String& rComment);
//STRIP001  void BegUndo(const String& rComment, const String& rObjDescr, SdrRepeatFunc eFunc=SDRREPFUNC_OBJ_NONE);
//STRIP001  void BegUndo(SdrUndoGroup* pUndoGrp);
//STRIP001  void EndUndo();                                                   // Undo-Klammerung zu (inkl BroadcastEdges)
//STRIP001  void AddUndo(SdrUndoAction* pUndo);
    // nur nach dem 1. BegUndo oder vor dem letzten EndUndo:
//STRIP001  void SetUndoComment(const String& rComment);
//STRIP001  void SetUndoComment(const String& rComment, const String& rObjDescr);
#endif

    // Layerverwaltung. Mit Undo.
//STRIP001  SdrLayer* InsertNewLayer(const String& rName, USHORT nPos=0xFFFF);
    // Loeschen eines Layer inkl. aller darauf befindlichen Objekte
    void      DeleteLayer(const String& rName);
    // Verschieben eines Layer (Layerreihenfolge aendern)
//STRIP001  void      MoveLayer(const String& rName, USHORT nNewPos);

    // Markierte Objekte die ausserhalb ihrer Page liegen
    // werden ggf. einer anderen Page zugewiesen
    // z.Zt. noch ohne Undo!!!
//STRIP001  void ForceMarkedObjToAnotherPage();
//STRIP001  void ForceMarkedToAnotherPage()   { ForceMarkedObjToAnotherPage(); }

    BOOL IsReadOnly() const { ForcePossibilities(); return bReadOnly; }

    // Loeschen aller markierten Objekte
//STRIP001  void DeleteMarkedObj();
    BOOL IsDeleteMarkedObjPossible() const { ForcePossibilities(); return bDeletePossible; }

    // Logisch- umschliessendes Rect aller markierten Objekte setzen.
    // Das das wirklich geschieht ist nicht garantiert, denn eine
    // waagerechte Linie hat z.B. immer eine Hoehe von 0.
//STRIP001  void SetMarkedObjRect(const Rectangle& rRect, BOOL bCopy=FALSE);
//STRIP001  void MoveMarkedObj(const Size& rSiz, BOOL bCopy=FALSE);
//STRIP001  void ResizeMarkedObj(const Point& rRef, const Fraction& xFact, const Fraction& yFact, BOOL bCopy=FALSE);
//STRIP001  long GetMarkedObjRotate() const;
//STRIP001  void RotateMarkedObj(const Point& rRef, long nWink, BOOL bCopy=FALSE);
//STRIP001  void MirrorMarkedObj(const Point& rRef1, const Point& rRef2, BOOL bCopy=FALSE);
//STRIP001  void MirrorMarkedObjHorizontal(BOOL bCopy=FALSE);
//STRIP001  void MirrorMarkedObjVertical(BOOL bCopy=FALSE);
//STRIP001  long GetMarkedObjShear() const;
//STRIP001  void ShearMarkedObj(const Point& rRef, long nWink, BOOL bVShear=FALSE, BOOL bCopy=FALSE);
//STRIP001  void CrookMarkedObj(const Point& rRef, const Point& rRad, SdrCrookMode eMode, BOOL bVertical=FALSE, BOOL bNoContortion=FALSE, BOOL bCopy=FALSE);
//STRIP001  void DistortMarkedObj(const Rectangle& rRef, const XPolygon& rDistortedRect, BOOL bNoContortion=FALSE, BOOL bCopy=FALSE);

    // Markierte Objekte kopieren und anstelle der alten markieren
//STRIP001  void CopyMarkedObj();
//STRIP001  void SetAllMarkedRect(const Rectangle& rRect, BOOL bCopy=FALSE) { SetMarkedObjRect(rRect,bCopy); }
//STRIP001  void MoveAllMarked(const Size& rSiz, BOOL bCopy=FALSE) { MoveMarkedObj   (rSiz,bCopy); }
//STRIP001  void ResizeAllMarked(const Point& rRef, const Fraction& xFact, const Fraction& yFact, BOOL bCopy=FALSE) { ResizeMarkedObj (rRef,xFact,yFact,bCopy); }
//STRIP001  long GetAllMarkedRotate() const { return GetMarkedObjRotate(); }
//STRIP001  void RotateAllMarked(const Point& rRef, long nWink, BOOL bCopy=FALSE) { RotateMarkedObj(rRef,nWink,bCopy); }
//STRIP001  void MirrorAllMarked(const Point& rRef1, const Point& rRef2, BOOL bCopy=FALSE) { MirrorMarkedObj(rRef1,rRef2,bCopy); }
//STRIP001  void MirrorAllMarkedHorizontal(BOOL bCopy=FALSE) { MirrorMarkedObjHorizontal(bCopy); }
//STRIP001  void MirrorAllMarkedVertical(BOOL bCopy=FALSE) { MirrorMarkedObjVertical(bCopy); }
//STRIP001  long GetAllMarkedShear() const { return GetMarkedObjShear(); }
//STRIP001  void ShearAllMarked(const Point& rRef, long nWink, BOOL bVShear=FALSE, BOOL bCopy=FALSE) { ShearMarkedObj(rRef,nWink,bVShear,bCopy); }
//STRIP001  void CrookAllMarked(const Point& rRef, const Point& rRad, SdrCrookMode eMode, BOOL bVertical=FALSE, BOOL bNoContortion=FALSE, BOOL bCopy=FALSE) { CrookMarkedObj(rRef,rRad,eMode,bVertical,bNoContortion,bCopy); }
//STRIP001  void DistortAllMarked(const Rectangle& rRef, const XPolygon& rDistortedRect, BOOL bNoContortion=FALSE, BOOL bCopy=FALSE) { DistortMarkedObj(rRef,rDistortedRect,bNoContortion,bCopy); }
//STRIP001  void CopyMarked() { CopyMarkedObj(); }
    BOOL IsMoveAllowed() const { ForcePossibilities(); return bMoveAllowed && !bMoveProtect; }
//STRIP001  BOOL IsResizeAllowed(BOOL bProp=FALSE) const;
//STRIP001  BOOL IsRotateAllowed(BOOL b90Deg=FALSE) const;
    BOOL IsMirrorAllowed(BOOL b45Deg=FALSE, BOOL b90Deg=FALSE) const;
    BOOL IsTransparenceAllowed() const;
    BOOL IsGradientAllowed() const;
//STRIP001  BOOL IsShearAllowed() const;
//STRIP001  BOOL IsEdgeRadiusAllowed() const;
    BOOL IsCrookAllowed(BOOL bNoContortion=FALSE) const;
//STRIP001  BOOL IsDistortAllowed(BOOL bNoContortion=FALSE) const;

    // Vereinigen mehrerer Objekte zu einem PolyPolygon:
    // - Rechtecke/Kreise/Text... werden implizit gewandelt.
    // - Polylines werden automatisch geschlossen.
    // - Die Attribute und der Layer werden vom Ersten der markierten Objekte
    //   uebernommen (also vom untersten der Z-Order).
    // - Gruppenobjekte werden miteinbezogen, wenn alle! Memberobjekte der
    //   Gruppe wandelbar sind. Beinhaltet eine Gruppe also beispielsweise
    //   eine Bitmap oder ein OLE-Objekt, wird die gesamte Gruppe nicht
    //   beruecksichtigt.
    // bNoPolyPoly=TRUE: Alles wird zu einem einzigen Polygon zusammengefasst
    BOOL CombineMarkedObjects(BOOL bNoPolyPoly = FALSE);

    // for combining multiple polygons, with direct support of the modes
    // SID_POLY_MERGE, SID_POLY_SUBSTRACT, SID_POLY_INTERSECT
//STRIP001  void MergeMarkedObjects(SdrMergeMode eMode);

    // for distribution dialog function
//STRIP001  void DistributeMarkedObjects();

    // Markierte Polypolygonobjekte in Polygone zerlegen
    // Gruppenobjekte werden durchsucht und zerlegt, wenn es sich bei allen
    // Memberobjekten um PathObjs handelt.
    // bMakeLines=TRUE: alle Polygone werden in einzelne Linien bzw.
    //                  Beziersegmente zerlegt
    void DismantleMarkedObjects(BOOL bMakeLines=FALSE);
//STRIP001  BOOL IsCombinePossible(BOOL bNoPolyPoly=FALSE) const;
//STRIP001  BOOL IsDismantlePossible(BOOL bMakeLines=FALSE) const;

    // Ein neues bereits fertig konstruiertes Obj einfuegen. Das Obj gehoert
    // anschliessend dem Model. Nach dem Einfuegen wird das neue Objekt
    // markiert (wenn dies nicht via nOptions unterbunden wird).
    // U.U. wird das Obj jedoch nicht eingefuegt, sondern deleted, naemlich
    // wenn der Ziel-Layer gesperrt oder nicht sichtbar ist. In diesem Fall
    // returniert die Methode mit FALSE.
    // Die Methode generiert u.a. auch eine Undo-Action.
//STRIP001  BOOL InsertObject(SdrObject* pObj, SdrPageView& rPV, ULONG nOptions=0);

    // Ein Zeichenobjekt durch ein neues ersetzen. *pNewObj gehoert
    // anschliessend mir, *pOldObj wandert ins Undo.
    // Sollte in jedem Fall mit einer Undo-Klammerung versehen werden, z.B.:
    // String aStr(pView->GetMarkDescription());
    // aStr+=" ersetzen";
    // BegUndo(aStr);
    // ReplaceObject(...);
    // ...
    // EndUndo();
//STRIP001  void ReplaceObject(SdrObject* pOldObj, SdrPageView& rPV, SdrObject* pNewObj, BOOL bMark=TRUE);

//STRIP001  void SetNotPersistAttrToMarked(const SfxItemSet& rAttr, BOOL bReplaceAll);
//STRIP001  void MergeNotPersistAttrFromMarked(SfxItemSet& rAttr, BOOL bOnlyHardAttr) const;
//STRIP001  void MergeAttrFromMarked(SfxItemSet& rAttr, BOOL bOnlyHardAttr) const;
//STRIP001  SfxItemSet GetAttrFromMarked(BOOL bOnlyHardAttr) const;
//STRIP001  void SetAttrToMarked(const SfxItemSet& rAttr, BOOL bReplaceAll);

    // Geometrische Attribute (Position, Groesse, Drehwinkel)
    // Bei der Position wird ein evtl. gesetzter PageOrigin beruecksichtigt.
//STRIP001  SfxItemSet GetGeoAttrFromMarked() const;
//STRIP001  void SetGeoAttrToMarked(const SfxItemSet& rAttr);

    // Returnt NULL wenn:
    // - Nix markiert,
    // - kein StyleSheet an den markierten Objekten gesetzt
    // - Bei Mehrfachselektion die markierten Objekte auf unterschiedliche
    //   StyleSheets verweisen.
//STRIP001  SfxStyleSheet* GetStyleSheetFromMarked() const;

    // z.Zt. noch ohne Undo :(
//STRIP001  void SetStyleSheetToMarked(SfxStyleSheet* pStyleSheet, BOOL bDontRemoveHardAttr);

    /* new interface src537 */
//STRIP001  BOOL GetAttributes(SfxItemSet& rTargetSet, BOOL bOnlyHardAttr) const;

//STRIP001  BOOL SetAttributes(const SfxItemSet& rSet, BOOL bReplaceAll);
//STRIP001  SfxStyleSheet* GetStyleSheet(BOOL& rOk) const;
    BOOL SetStyleSheet(SfxStyleSheet* pStyleSheet, BOOL bDontRemoveHardAttr);

    // Alle markierten Objekte zu einer Gruppe zusammenfassen.
    // Anschliessend wird die neue Gruppe markiert. Bei einer
    // seitenuebergreifenden Markierung wird eine Gruppe je Seite erzeugt.
    // Alle erzeugten Gruppen sind anschliessend markiert.
    // Ueber pUserGrp kann ein eigenes Gruppenobjekt vorgegeben werden. Dieses
    // wird  jedoch nicht direkt verwendet, sondern via Clone kopiert.
    // Wird NULL uebergeben, macht sich die Methode SdrObjGroup-Instanzen.
    void GroupMarked(const SdrObject* pUserGrp=NULL);

    // Alle markierten Objektgruppen werden aufgeloesst (1 Level).
    // Anschliessend sind statt der Gruppenobjekte alle ehemaligen
    // Memberobjekte der aufgeloesten Gruppen markiert. Waren zum auch Objekte
    // markiert, die keine Gruppenobjekte sind, so bleiben diese weiterhin
    // zusaetzlich markiert.
    void UnGroupMarked();

    BOOL IsGroupPossible() const { ForcePossibilities(); return bGroupPossible; }
    BOOL IsUnGroupPossible() const { ForcePossibilities(); return bUnGroupPossible; }
    BOOL IsGroupEnterPossible() const { ForcePossibilities(); return bGrpEnterPossible; }

    // Markierte Objekte in Polygone/Bezierkurven verwandeln. Die BOOL-
    // Funktionen returnen TRUE, wenn wenigstens eins der markierten
    // Objekte gewandelt werden kann. Memberobjekte von Gruppenobjekten
    // werden ebenfalls gewandelt. Naehere Beschreibung siehe SdrObj.HXX.
    BOOL IsConvertToPathObjPossible(BOOL bLineToArea) const { ForcePossibilities(); return bLineToArea ? bCanConvToPathLineToArea : bCanConvToPath; }
    BOOL IsConvertToPolyObjPossible(BOOL bLineToArea) const { ForcePossibilities(); return bLineToArea ? bCanConvToPolyLineToArea : bCanConvToPoly; }
    BOOL IsConvertToContourPossible() const { ForcePossibilities(); return bCanConvToContour; }
//STRIP001  void ConvertMarkedToPathObj(BOOL bLineToArea);
//STRIP001  void ConvertMarkedToPolyObj(BOOL bLineToArea);

    // Alle markierten Objekte untereinander ausrichten. Normalerweise werden
    // das SnapRect der Obj verwendet. Ist bBoundRects=TRUE, werden stattdessen
    // die BoundRects ausgerichtet.
//STRIP001  void AlignMarkedObjects(SdrHorAlign eHor, SdrVertAlign eVert, BOOL bBoundRects=FALSE);
//STRIP001  BOOL IsAlignPossible() const;

    // Markierte Objekte etwas nach "oben" holen
//STRIP001  void MovMarkedToTop();

    // Markierte Objekte etwas nach "unten" holen
//STRIP001  void MovMarkedToBtm();

    // Markierte Objekte ganz nach "oben" stellen
//STRIP001  void PutMarkedToTop();

    // Markierte Objekte ganz nach "unten" stellen
//STRIP001  void PutMarkedToBtm();

    // Markierte direkt vor das uebergebene Objekt stellen
    // NULL -> wie PutMarkedToTop();
//STRIP001  void PutMarkedInFrontOfObj(const SdrObject* pRefObj);

    // Markierte direkt hinter das uebergebene Objekt stellen
    // NULL -> wie PutMarkedToBtm();
//STRIP001  void PutMarkedBehindObj(const SdrObject* pRefObj);

    // Z-Order der markierten Objekte vertauschen
//STRIP001  void ReverseOrderOfMarked();

    // Feststellen, ob nach vorn/hinten stellen moeglich ist
    // GetMaxToTop/BtmObj() wird von diesen Methoden nur begrenzt
    // beruecksichtigt, d.h. es kann vorkommen dass IsToTopPossible()
    // TRUE liefert, MovMarkedToTop() jedoch nichts aendert (z.B. bei
    // Mehrfachselektion), weil eine von der abgeleiteten View ueber
    // GetMaxToTopObj() auferlegte Restriktion dies verhindert.
    BOOL IsToTopPossible() const { ForcePossibilities(); return bToTopPossible; }
    BOOL IsToBtmPossible() const { ForcePossibilities(); return bToBtmPossible; }
    BOOL IsReverseOrderPossible() const { ForcePossibilities(); return bReverseOrderPossible; }

    // Ueber diese Methoden stellt die View fest, wie weit ein Objekt
    // nach vorn bzw. nach hinten gestellt werden darf (Z-Order). Das
    // zurueckgegebene Objekt wird dann nicht "ueberholt". Bei Rueckgabe
    // von NULL (Defaultverhalten) bestehen keine Restriktionen.
//STRIP001  virtual SdrObject* GetMaxToTopObj(SdrObject* pObj) const;
//STRIP001  virtual SdrObject* GetMaxToBtmObj(SdrObject* pObj) const;

    // Folgende Methode wird gerufen, wenn z.B. durch ToTop, ToBtm, ... die
    // Reihenfolgen der Objekte geaendert wurde. Der Aufruf erfolgt dann nach
    // jedem SdrObjList::SetObjectOrdNum(nOldPos,nNewPos);
//STRIP001  virtual void ObjOrderChanged(SdrObject* pObj, ULONG nOldPos, ULONG nNewPos);

    // Falls ein oder mehrere Objekte des Types SdrGrafObj oder SdrOle2Obj
    // markiert sind und diese in der Lage sind ein StarView-Metafile zu
    // liefern, konvertiert diese Methode das Metafile in Drawingobjekte.
    // Die SdrGrafObjs/SdrOle2Objs werden dann durch die neue Objekte ersetzt.
//STRIP001  void DoImportMarkedMtf(SvdProgressInfo *pProgrInfo=NULL);
    BOOL IsImportMtfPossible() const { ForcePossibilities(); return bImportMtfPossible; }

    // Wird der Modus VirtualObjectBundling eingeschaltet, werden beim
    // ToTop/ToBtm virtuelle Objekte die dasselbe Objekt referenzieren
    // in ihrer Z-Order buendig zusammengehalten (Writer).
    // Defaulteinstellung ist FALSE=ausgeschaltet.
    void SetVirtualObjectBundling(BOOL bOn) { bBundleVirtObj=bOn; }
    BOOL IsVirtualObjectBundling() const { return bBundleVirtObj; }

    // von der SdrMarkView ueberladen fuer den internen gebrauch
    virtual void MarkListHasChanged();
    virtual void ModelHasChanged();
};

}//end of namespace binfilter
#endif //_SVDEDTV_HXX

