/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: view3d.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 04:23:14 $
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



public:
    TYPEINFO();

    E3dView(SdrModel* pModel, OutputDevice* pOut);
    E3dView(SdrModel* pModel, ExtOutputDevice* pExtOut);
    E3dView(SdrModel* pModel);
    virtual ~E3dView();

    // Alle markierten Objekte auf dem angegebenen OutputDevice ausgeben.

    // Zugriff auf die Default-Attribute
    E3dDefaultAttributes& Get3DDefaultAttributes() { return a3DDefaultAttr; }
    virtual void CheckPossibilities();

    // Event setzen/rausruecken
    void SetMouseEvent(const MouseEvent& rNew) { aMouseEvent = rNew; }
    const MouseEvent& GetMouseEvent() { return aMouseEvent; }

    // Model holen ueberladen, da bei einzelnen 3D Objekten noch eine Szene
    // untergeschoben werden muss

    // Bei Paste muss - falls in eine Scene eingefuegt wird - die
    // Objekte der Szene eingefuegt werden, die Szene selbst aber nicht

    // #83403# Service routine used from local Clone() and from SdrCreateView::EndCreateObj(...)


    BOOL IsConvertTo3DObjPossible() const;

    // Nachtraeglichhe Korrekturmoeglichkeit um alle Extrudes in einer
    // bestimmten Tiefensortierung anzulegen
    void DoDepthArrange(E3dScene* pScene, double fDepth);
    void Set3DDragConstraint(E3dDragConstraint eConstr) { eDragConstraint = eConstr; }
    E3dDragConstraint Get3DDragConstraint() { return eDragConstraint; }
    void Set3DDragDetail(E3dDragDetail eDetail) { eDragDetail = eDetail; }
    E3dDragDetail Get3DDragDetail() { return eDragDetail; }
    BOOL IsCreationActive() const { return b3dCreationActive; }
    void ResetCreationActive();
    void ShowMirrored();

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



    BOOL DoubleSided () const
    {
        return bDoubleSided;
    }

    BOOL &DoubleSided ()
    {
        return bDoubleSided;
    }

};

}//end of namespace binfilter
#endif          // _E3D_VIEW3D_HXX
