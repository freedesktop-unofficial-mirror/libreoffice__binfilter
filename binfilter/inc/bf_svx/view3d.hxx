/*************************************************************************
 *
 *  $RCSfile: view3d.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:29:27 $
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

#ifndef _E3D_VIEW3D_HXX
#define _E3D_VIEW3D_HXX

#include <bf_svx/svdview.hxx>

#ifndef _SVX_DEF3D_HXX
#include <bf_svx/def3d.hxx>
#endif

#ifndef _E3D_DEFLT3D_HXX
#include <bf_svx/deflt3d.hxx>
#endif

#ifndef _SVX_VECTOR3D_HXX
#include <goodies/vector3d.hxx>
#endif
namespace binfilter {

//************************************************************
//   Vorausdeklarationen
//************************************************************

class E3dObject;
class E3dScene;
class SceneList;

/*************************************************************************
|*
|* Ableitung von SdrView zur Bearbeitung von 3D-Objekten
|*
\************************************************************************/

class E3dView : public SdrView
{
protected:
    SdrObject**                 pMarkedObjs;
    XPolyPolygon*               pMirrorPolygon;
    XPolyPolygon*               pMirroredPolygon;
    SdrPageView*                pMyPV;

    E3dDefaultAttributes        a3DDefaultAttr;
    MouseEvent                  aMouseEvent;                    // Die Parameter der letzten Events (Mouse, Keyboard)
    Vector3D                    aDefaultTranslation;            // wird das Objekt erstmalig verschoben ?
    Vector3D                    aDefaultLightPos;               // wo ist das gerichtete Licht ?
//-/    Vector3D                    aDefaultCamPos;                 // nur die Z-Achse (aus dem Bildschirm heraus)
    Color                       aDefaultLightColor;             // dito mit den Farben
    Color                       aDefaultAmbientColor;

    double                      fDefaultScaleX;                 // Verzerrungen
    double                      fDefaultScaleY;
    double                      fDefaultScaleZ;
    double                      fDefaultRotateX;                // und Drehungen
    double                      fDefaultRotateY;
    double                      fDefaultRotateZ;
    double                      fDefaultExtrusionDeepth;        // Extrusionstiefe
//-/    double                      fDefaultCamFocal;               // Brennweite der Kamera
    double                      fDefaultLightIntensity;         // Intensitaeten der beiden (notwendigen) Licht-
    double                      fDefaultAmbientIntensity;       // quellen
    long                        nHDefaultSegments;              // wieviele HSegmente braucht mein Lathe-Ojekt
    long                        nVDefaultSegments;              // wieviele VSegmente braucht mein Lathe-Ojekt
    long                        nPolyCnt;

    E3dDragConstraint           eDragConstraint;
    E3dDragDetail               eDragDetail;

    BOOL                        b3dCreationActive;
    BOOL                        bDoubleSided;

    void InitView();

//STRIP001  void ImpCreate3DObject(E3dScene* pScene, SdrObject* pObj, BOOL bExtrude, double fDepth, Matrix4D& rLatheMat);
//STRIP001  void ImpCreateSingle3DObjectFlat(E3dScene* pScene, SdrObject* pObj, BOOL bExtrude, double fDepth, Matrix4D& rLatheMat);
//STRIP001  void ImpChangeSomeAttributesFor3DConversion(SdrObject* pObj);
//STRIP001  void ImpChangeSomeAttributesFor3DConversion2(SdrObject* pObj);

//STRIP001  void InitScene(E3dScene* pScene, double fW, double fH, double fCamZ);
//STRIP001  void ImpIsConvertTo3DPossible(SdrObject* pObj, BOOL& rAny3D, BOOL& rGroupSelected) const;
//STRIP001  void BreakSingle3DObj(E3dObject* pObj);

public:
    TYPEINFO();

    E3dView(SdrModel* pModel, OutputDevice* pOut);
    E3dView(SdrModel* pModel, ExtOutputDevice* pExtOut);
    E3dView(SdrModel* pModel);
    virtual ~E3dView();

    // Alle markierten Objekte auf dem angegebenen OutputDevice ausgeben.
//STRIP001  virtual void DrawMarkedObj(OutputDevice& rOut, const Point& rOfs) const;

    // Zugriff auf die Default-Attribute
    E3dDefaultAttributes& Get3DDefaultAttributes() { return a3DDefaultAttr; }
//STRIP001  virtual BOOL BegDragObj(const Point& rPnt, OutputDevice* pOut = NULL, SdrHdl* pHdl = NULL, short nMinMov = -3, SdrDragMethod* pForcedMeth = NULL);
    virtual void CheckPossibilities();

    // Event setzen/rausruecken
    void SetMouseEvent(const MouseEvent& rNew) { aMouseEvent = rNew; }
    const MouseEvent& GetMouseEvent() { return aMouseEvent; }

    // Model holen ueberladen, da bei einzelnen 3D Objekten noch eine Szene
    // untergeschoben werden muss
//STRIP001  virtual SdrModel* GetMarkedObjModel() const;

    // Bei Paste muss - falls in eine Scene eingefuegt wird - die
    // Objekte der Szene eingefuegt werden, die Szene selbst aber nicht
//STRIP001  virtual BOOL Paste(const SdrModel& rMod, const Point& rPos, SdrObjList* pLst=NULL, UINT32 nOptions=0);

    // #83403# Service routine used from local Clone() and from SdrCreateView::EndCreateObj(...)
//STRIP001  BOOL ImpCloneAll3DObjectsToDestScene(E3dScene* pSrcScene, E3dScene* pDstScene, Point aOffset);

//STRIP001  BOOL HasMarkedScene();
//STRIP001  E3dScene* GetMarkedScene();

    BOOL IsConvertTo3DObjPossible() const;
//STRIP001  void ConvertMarkedObjTo3D(BOOL bExtrude=TRUE, Vector3D aPnt1 = Vector3D(), Vector3D aPnt2 = Vector3D(0.0, 1.0, 0.0));

    // Nachtraeglichhe Korrekturmoeglichkeit um alle Extrudes in einer
    // bestimmten Tiefensortierung anzulegen
    void DoDepthArrange(E3dScene* pScene, double fDepth);
//STRIP001  void ConvertMarkedToPolyObj(BOOL bLineToArea);
    void Set3DDragConstraint(E3dDragConstraint eConstr) { eDragConstraint = eConstr; }
    E3dDragConstraint Get3DDragConstraint() { return eDragConstraint; }
    void Set3DDragDetail(E3dDragDetail eDetail) { eDragDetail = eDetail; }
    E3dDragDetail Get3DDragDetail() { return eDragDetail; }
//STRIP001  void SetCurrent3DObj(E3dObject* p3DObj);
//STRIP001  void Start3DCreation();
    BOOL IsCreationActive() const { return b3dCreationActive; }
//STRIP001  virtual void MovAction(const Point& rPnt);
//STRIP001  void End3DCreation(BOOL bUseDefaultValuesForMirrorAxes=FALSE);
    void ResetCreationActive();
    void ShowMirrored();
//STRIP001  void CreateMirrorPolygons();
//STRIP001  void ShowMirrorPolygons(Point aMirrorPoint1, Point aMirrorPoint2);

    const Vector3D &DefaultTranslation () const
    {
        return aDefaultTranslation;
    }

    Vector3D &DefaultTranslation ()
    {
        return aDefaultTranslation;
    }

    const Vector3D &DefaultLightPos () const
    {
        return aDefaultLightPos;
    }

    Vector3D &DefaultLightPos ()
    {
        return aDefaultLightPos;
    }

//STRIP001  double GetDefaultCamPosZ();
//-/    const Vector3D &DefaultCamPos () const
//-/    {
//-/        return aDefaultCamPos;
//-/    }

//-/    Vector3D &DefaultCamPos ()
//-/    {
//-/        return aDefaultCamPos;
//-/    }

    double &DefaultScaleX ()
    {
        return fDefaultScaleX;
    }

    double DefaultScaleX () const
    {
        return fDefaultScaleX;
    }

    double &DefaultScaleY ()
    {
        return fDefaultScaleY;
    }

    double DefaultScaleY () const
    {
        return fDefaultScaleY;
    }

    double &DefaultScaleZ ()
    {
        return fDefaultScaleZ;
    }

    double DefaultScaleZ () const
    {
        return fDefaultScaleZ;
    }

    double &DefaultRotateX ()
    {
        return fDefaultRotateX;
    }

    double DefaultRotateX () const
    {
        return fDefaultRotateX;
    }

    double &DefaultRotateY ()
    {
        return fDefaultRotateY;
    }

    double DefaultRotateY () const
    {
        return fDefaultRotateY;
    }

    double &DefaultRotateZ ()
    {
        return fDefaultRotateZ;
    }

    double DefaultRotateZ () const
    {
        return fDefaultRotateZ;
    }

    double &DefaultExtrusionDeepth ()
    {
        return fDefaultExtrusionDeepth;
    }

    double DefaultExtrusionDeepth () const
    {
        return fDefaultExtrusionDeepth;
    }

//STRIP001  double GetDefaultCamFocal();
//-/    double &DefaultCamFocal ()
//-/    {
//-/        return fDefaultCamFocal;
//-/    }

//-/    double DefaultCamFocal () const
//-/    {
//-/        return fDefaultCamFocal;
//-/    }

    double &DefaultLightIntensity ()
    {
        return fDefaultLightIntensity;
    }

    double DefaultLightIntensity () const
    {
        return fDefaultLightIntensity;
    }

    double &DefaultAmbientIntensity ()
    {
        return fDefaultAmbientIntensity;
    }

    double DefaultAmbientIntensity () const
    {
        return fDefaultAmbientIntensity;
    }

    const Color &DefaultLightColor () const
    {
        return aDefaultLightColor;
    }

    Color DefaultLightColor ()
    {
        return aDefaultLightColor;
    }

    const Color &DefaultAmbientColor () const
    {
        return aDefaultAmbientColor;
    }

    Color DefaultAmbientColor ()
    {
        return aDefaultAmbientColor;
    }

    long GetHDefaultSegments() const { return nHDefaultSegments; }
    void SetHDefaultSegments(long nSegs) { nHDefaultSegments = nSegs; }

    long GetVDefaultSegments() const { return nVDefaultSegments; }
    void SetVDefaultSegments(long nSegs) { nVDefaultSegments = nSegs; }

//STRIP001  virtual void ShowDragObj(OutputDevice* pOut);
//STRIP001  virtual void HideDragObj(OutputDevice* pOut);
//STRIP001  virtual void DrawDragObj(OutputDevice* pOut, BOOL bFull) const;

//STRIP001  BOOL IsBreak3DObjPossible() const;
//STRIP001  void Break3DObj();

    BOOL DoubleSided () const
    {
        return bDoubleSided;
    }

    BOOL &DoubleSided ()
    {
        return bDoubleSided;
    }

//STRIP001  void MergeScenes();
//STRIP001  SfxItemSet Get3DAttributes(E3dScene* pInScene = NULL, BOOL bOnly3DAttr=FALSE) const;
//STRIP001  void Set3DAttributes(const SfxItemSet& rAttr, E3dScene* pInScene = NULL, BOOL bOnly3DAttr=FALSE);
};

}//end of namespace binfilter
#endif          // _E3D_VIEW3D_HXX
