/*************************************************************************
 *
 *  $RCSfile: svdcrtv.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:41 $
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

#ifndef _SVDCRTV_HXX
#define _SVDCRTV_HXX

// HACK to avoid too deep includes and to have some
// levels free in svdmark itself (MS compiler include depth limit)
#ifndef _SVDHDL_HXX
#include <bf_svx/svdhdl.hxx>
#endif

#include <bf_svx/svddrgv.hxx>

//************************************************************
//   Vorausdeklarationen
//************************************************************

class XLineAttrSetItem;
class XFillAttrSetItem;
class SdrEdgeObj;
class SdrObjConnection;
class ImpSdrConnectMarker;

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
//
//   @@@@  @@@@@  @@@@@  @@@@  @@@@@@ @@@@@  @@ @@ @@ @@@@@ @@   @@
//  @@  @@ @@  @@ @@    @@  @@   @@   @@     @@ @@ @@ @@    @@   @@
//  @@     @@  @@ @@    @@  @@   @@   @@     @@ @@ @@ @@    @@ @ @@
//  @@     @@@@@  @@@@  @@@@@@   @@   @@@@   @@@@@ @@ @@@@  @@@@@@@
//  @@     @@  @@ @@    @@  @@   @@   @@      @@@  @@ @@    @@@@@@@
//  @@  @@ @@  @@ @@    @@  @@   @@   @@      @@@  @@ @@    @@@ @@@
//   @@@@  @@  @@ @@@@@ @@  @@   @@   @@@@@    @   @@ @@@@@ @@   @@
//
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

class SdrCreateView: public SdrDragView
{
    friend class                SdrPageView;
    friend class                ImpSdrCreateLibObjMove;
    friend class                ImpSdrCreateLibObjResize;

protected:
    SdrObject*                  pAktCreate;   // Aktuell in Erzeugung befindliches Objekt
    SdrPageView*                pCreatePV;    // Hier wurde die Erzeugung gestartet
    SdrObject*                  pCurrentLibObj;
    SdrDragMethod*              pLibObjDragMeth;
    ImpSdrConnectMarker*        pConnectMarker;

    Pointer                     aAktCreatePointer;

    INT32                       nAutoCloseDistPix;
    INT32                       nFreeHandMinDistPix;
    UINT32                      nAktInvent;     // Aktuell eingestelltes
    UINT16                      nAktIdent;      // Obj fuer Neuerzeugung

    unsigned                    bAutoTextEdit : 1; // Textedit nach dem erzeugen eines Textrahmens starten
    unsigned                    b1stPointAsCenter : 1;
    unsigned                    bUseIncompatiblePathCreateInterface : 1;
    unsigned                    bAutoClosePolys : 1;
    unsigned                    bCurrentLibObjMoveNoResize : 1;
    unsigned                    bCurrentLibObjSetDefAttr : 1;
    unsigned                    bCurrentLibObjSetDefLayer : 1;

private:
    void ImpClearVars();
    void ImpMakeCreateAttr();
//STRIP001  void ImpDelCreateAttr();

protected:
//STRIP001  BOOL ImpBegCreateObj(UINT32 nInvent, UINT16 nIdent, const Point& rPnt, OutputDevice* pOut,
//STRIP001      short nMinMov, SdrPageView* pPV, const Rectangle& rLogRect);

//STRIP001  void ShowCreateObj(OutputDevice* pOut, BOOL bFull);
//STRIP001  void HideCreateObj(OutputDevice* pOut, BOOL bFull);
//STRIP001  void DrawCreateObj(OutputDevice* pOut, BOOL bFull) const;
//STRIP001  void DrawCreateObjDiff(XPolyPolygon& rXPP0, XPolyPolygon& rXPP1);
    virtual void WriteRecords(SvStream& rOut) const;
    virtual BOOL ReadRecord(const SdrIOHeader& rViewHead, const SdrNamedSubRecord& rSubHead, SvStream& rIn);
    BOOL CheckEdgeMode();

public:
    SdrCreateView(SdrModel* pModel1, OutputDevice* pOut=NULL);
    SdrCreateView(SdrModel* pModel1, ExtOutputDevice* pXOut);
    virtual ~SdrCreateView();

    virtual void ToggleShownXor(OutputDevice* pOut, const Region* pRegion) const;
    virtual BOOL IsAction() const;
//STRIP001  virtual void MovAction(const Point& rPnt);
//STRIP001  virtual void EndAction();
//STRIP001  virtual void BckAction();
    virtual void BrkAction();
//STRIP001  virtual void TakeActionRect(Rectangle& rRect) const;

//STRIP001  BOOL MouseMove(const MouseEvent& rMEvt, Window* pWin);

    void SetActiveLayer(const String& rName) { aAktLayer=rName; }
    const String& GetActiveLayer() const { return aAktLayer; }
    void SetMeasureLayer(const String& rName) { aMeasureLayer=rName; }
    const String& GetMeasureLayer() const { return aMeasureLayer; }

    // Ist der MeasureLayer nicht gesetzt (Leerstring), so
    // wird der ActiveLayer auch fuer Bemassung verwendet.
    void SetEditMode(SdrViewEditMode eMode) { SdrDragView::SetEditMode(eMode); CheckEdgeMode(); }
    void SetEditMode(BOOL bOn=TRUE) { SdrDragView::SetEditMode(bOn); CheckEdgeMode(); }
    void SetCreateMode(BOOL bOn=TRUE) { SdrDragView::SetCreateMode(bOn); CheckEdgeMode(); }
    void SetGluePointEditMode(BOOL bOn=TRUE) { SdrDragView::SetGluePointEditMode(bOn); CheckEdgeMode(); }

    // Feststellen, ob Textwerkzeug aktiviert
    BOOL IsTextTool() const;

    // Feststellen, ob Objektverbinderwerkzeug aktiviert
    BOOL IsEdgeTool() const;

    // Feststellen, ob Bemassungswerkzeug aktiviert
//STRIP001  BOOL IsMeasureTool() const;

    void SetCurrentObj(UINT16 nIdent, UINT32 nInvent=SdrInventor);
    void TakeCurrentObj(UINT16& nIdent, UINT32& nInvent) const  { nInvent=nAktInvent; nIdent=nAktIdent; }
    UINT32 GetCurrentObjInventor() const { return nAktInvent; }
    UINT16 GetCurrentObjIdentifier() const { return nAktIdent; }

    // Hier kann man ein vorgefertigtes Objekt als Create-Default setzen.
    // Die Methoden arbeiten in Wechselwirkung mit Set/TakeCurrentObj().
    // TakeCurrentObj liefert anschliessend OBJ_NONE solange bis wieder mit
    // obiger Methode ein Objekt fuer normales Create gesetzt wird. Das zuvor
    // gesetzte vorgefertigte Objekt wird dann per delete abgeraeumt.
    // Das uebergebene Obj beim Aufruf dieser Methode der View uebereignet!
    // Bei jedem BegCreate wird eine Kopie angefertigt, welche dann eingefuegt
    // wird. Wenn bMoveNoResize=FALSE, wird das Objekt dann via Resize
    // "aufgezogen". Andernfalls wird es nur gemoved.
    // Als Mauszeiger wird POINTER_CROSS verwendet.
//STRIP001  void SetCurrentLibObj(SdrObject* pObj, BOOL bMoveNoResize=FALSE, BOOL bSetDefAttr=TRUE, BOOL bSetDefLayer=TRUE);
    const SdrObject* GetCurrentLibObj() const { return pCurrentLibObj; }

    // Starten des normalen Create
//STRIP001  BOOL BegCreateObj(const Point& rPnt, OutputDevice* pOut=NULL, short nMinMov=-3, SdrPageView* pPV=NULL);
//STRIP001  void MovCreateObj(const Point& rPnt);
//STRIP001  BOOL EndCreateObj(SdrCreateCmd eCmd);
//STRIP001  void BckCreateObj();  // z.B. wieder 1 Polygonpunkt zurueck.
    void BrkCreateObj();
    BOOL IsCreateObj() const { return pAktCreate!=NULL; }
    SdrObject* GetCreateObj() const { return pAktCreate; }

    // BegCreateCaptionObj() erzeugt ein SdrCaptionObj (Legendenobjekt).
    // rObjSiz ist die anfaengliche Groesse des Legenden-Textrahmens.
    // gedraggd wird lediglich die Laenge des Zipfel.
//STRIP001  BOOL BegCreateCaptionObj(const Point& rPnt, const Size& rObjSiz, OutputDevice* pOut=NULL, short nMinMov=-3, SdrPageView* pPV=NULL);

    // Einfuegen eines vorgefertigten Objekts. pObj wird dabei uebereignet.
    // Die Einstellung des CurrentObj bleibt hierbei unbeeinflusst!
    // Diese Funktion eignet sich dafuer, um via eigenem "Drag&Drop" von
    // einer Symbolbibliothek ein Symbol per Maus zu greifen und dieses auf
    // das Dokument zu ziehen.
//STRIP001  BOOL BegCreateLibObj(const Point& rPnt, SdrObject* pObj, BOOL bMoveNoResize=TRUE, BOOL bSetDefAttr=FALSE,
//STRIP001      BOOL bSetDefLayer=FALSE, OutputDevice* pOut=NULL, short nMinMov=-3, SdrPageView* pPV=NULL);

    // Wenn TextEditAfterCreate auf TRUE steht (das ist der Default),
    // dann wird nach dem erzeugen eines Textrahmenobjekts (OBJ_TEXT,
    // OBJ_TEXTEXT, OBJ_OUTLINERTEXT, OBJ_TITLETEXT, OBJ_CAPTION)
    // automatisch ein TextEdit (SdrObjEditView::BegTextEdit) gestartet.
    BOOL IsTextEditAfterCreate() const { return bAutoTextEdit; }
    void SetTextEditAfterCreate(BOOL bOn) { bAutoTextEdit = bOn; }

    // Erzeugen eines Kreises/Rechtecks/Textrahmens wobei der 1. Punkt
    // nicht die linke obere Ecke, sondern das Zentrum des Objekts vorgibt.
    // Persistentes Flag. Default=FALSE.
    BOOL IsCreate1stPointAsCenter() const { return b1stPointAsCenter; }
    void SetCreate1stPointAsCenter(BOOL bOn) { b1stPointAsCenter = bOn; SnapMove(); }

    // Fuer Polylines (OBJ_PLIN) und Freihandlinien (OBJ_FREELINE). Ist dieses
    // Flag TRUE, werden diese beiden Objekttypen implizit geschlossen und in
    // Polygon (OBJ_POLY) bzw. Freihandflaeche (OBJ_FREEFILL) gewandelt falls
    // zum Ende des Create die Distanz zwischen Startpunkt und Endpunkt des
    // Objekts <=n Pixel ist, wobei SetAutoCloseDistPix vorgegeben wird.
    // Default=TRUE.
    BOOL IsAutoClosePolys() const { return bAutoClosePolys; }
    void SetAutoClosePolys(BOOL bOn) { bAutoClosePolys=bOn; }

    // Default=5 Pixel.
    USHORT GetAutoCloseDistPix() const { return USHORT(nAutoCloseDistPix); }
    void SetAutoCloseDistPix(USHORT nVal) { nAutoCloseDistPix=nVal; }

    // Vorgabe des minimalen Pixelabstands zwischen 2 Bezierpunkten bei der
    // Erzeugung einer Freihandlinie.
    // Default=10 Pixel.
    USHORT GetFreeHandMinDistPix() const { return USHORT(nFreeHandMinDistPix); }
    void SetFreeHandMinDistPix(USHORT nVal) { nFreeHandMinDistPix=nVal; }

    // Wer das (zur restlichen Create-Funktionalitaet von SvDraw) inkompatible
    // Create-Interface am PathObj beibehalten moechte muss das nachfolgende
    // Flag setzen. Dieses wirkt sich aus bei den Objekttypen:
    //     OBJ_POLY, OBJ_PLIN, OBJ_PATHLINE, OBJ_PATHFILL
    // Dieses Flag hat nur voruebergehenden Character. Die betroffenen
    // Applikationen sollten alsbald umgestellt werden.
    // Default=FALSE;
    BOOL IsUseIncompatiblePathCreateInterface() const { return bUseIncompatiblePathCreateInterface; }
    void SetUseIncompatiblePathCreateInterface(BOOL bOn) { bUseIncompatiblePathCreateInterface = bOn; }
//STRIP001  void SetConnectMarker(const SdrObjConnection& rCon, const SdrPageView& rPV);
//STRIP001  void HideConnectMarker();

    // Attribute des ggf. gerade in der Erzeugung befindlichen Objekts
    /* new interface src537 */
//STRIP001  BOOL GetAttributes(SfxItemSet& rTargetSet, BOOL bOnlyHardAttr=FALSE) const;

//STRIP001  BOOL SetAttributes(const SfxItemSet& rSet, BOOL bReplaceAll);
//STRIP001  SfxStyleSheet* GetStyleSheet(BOOL& rOk) const;
    BOOL SetStyleSheet(SfxStyleSheet* pStyleSheet, BOOL bDontRemoveHardAttr);
};

#endif //_SVDCRTV_HXX

