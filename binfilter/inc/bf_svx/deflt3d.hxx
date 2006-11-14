/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: deflt3d.hxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: ihi $ $Date: 2006-11-14 12:20:56 $
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

#ifndef _E3D_DEFLT3D_HXX
#define _E3D_DEFLT3D_HXX




#ifndef _B3D_BASE3D_HXX
#include <bf_goodies/base3d.hxx>
#endif
class SfxItemSet;
namespace binfilter {


/*************************************************************************
|*
|* Klasse zum verwalten der 3D-Default Attribute
|*
\************************************************************************/

class E3dDefaultAttributes
{
private:
    // Compound-Objekt
//-/    B3dMaterial         aDefaultFrontMaterial;
    Color               aDefaultAmbientColor;

//  B3dMaterial         aDefaultBackMaterial;
//-/    Base3DTextureKind   eDefaultTextureKind;
//-/    Base3DTextureMode   eDefaultTextureMode;
//-/    BOOL                bDefaultDoubleSided                     ;
    BOOL                bDefaultCreateNormals                   ;
    BOOL                bDefaultCreateTexture                   ;
//-/    BOOL                bDefaultUseStdNormals                   ;
//-/    BOOL                bDefaultUseStdNormalsUseSphere          ;
//-/    BOOL                bDefaultInvertNormals                   ;
//-/    BOOL                bDefaultUseStdTextureX                  ;
//-/    BOOL                bDefaultUseStdTextureXUseSphere         ;
//-/    BOOL                bDefaultUseStdTextureY                  ;
//-/    BOOL                bDefaultUseStdTextureYUseSphere         ;
//-/    BOOL                bDefaultShadow3D                        ;
//-/    BOOL                bDefaultFilterTexture                   ;
    BOOL                bDefaultUseDifferentBackMaterial        ;

    // Cube-Objekt
    Vector3D            aDefaultCubePos;
    Vector3D            aDefaultCubeSize;
    UINT16              nDefaultCubeSideFlags;
    BOOL                bDefaultCubePosIsCenter                 ;

    // Sphere-Objekt
//-/    long                nDefaultHSegments;
//-/    long                nDefaultVSegments;
    Vector3D            aDefaultSphereCenter;
    Vector3D            aDefaultSphereSize;

    // Lathe-Objekt
    long                nDefaultLatheEndAngle;
    double              fDefaultLatheScale;
//-/    double              fDefaultBackScale;
//-/    double              fDefaultPercentDiag;
    BOOL                bDefaultLatheSmoothed                   ;
    BOOL                bDefaultLatheSmoothFrontBack            ;
    BOOL                bDefaultLatheCharacterMode              ;
    BOOL                bDefaultLatheCloseFront;
    BOOL                bDefaultLatheCloseBack;

    // Extrude-Objekt
    double              fDefaultExtrudeScale;
//-/    double              fDefaultExtrudeDepth;
    BOOL                bDefaultExtrudeSmoothed                 ;
    BOOL                bDefaultExtrudeSmoothFrontBack          ;
    BOOL                bDefaultExtrudeCharacterMode            ;
    BOOL                bDefaultExtrudeCloseFront;
    BOOL                bDefaultExtrudeCloseBack;

    // Scene-Objekt
//-/    B3dLightGroup       aDefaultLightGroup;
//-/    Vector3D            aDefaultShadowPlaneDirection;
//-/    Base3DShadeModel    eDefaultShadeModel;
    BOOL                bDefaultDither                          ;
//-/    BOOL                bDefaultForceDraftShadeModel            ;

public:
    // Konstruktor
    E3dDefaultAttributes();

    // Defaults zuruecksetzen
    void Reset();

    // Getter/Setter fuer Default-Werte aller 3D-Objekte
    // Compound-Objekt
//-/    const B3dMaterial& GetDefaultFrontMaterial() { return aDefaultFrontMaterial; }
//-/    void SetDefaultFrontMaterial(const B3dMaterial& rNew) { aDefaultFrontMaterial = rNew; }
    const Color& GetDefaultAmbientColor() { return aDefaultAmbientColor; }
    void SetDefaultAmbientColor(const Color& rNew) { aDefaultAmbientColor = rNew; }

//  const B3dMaterial& GetDefaultBackMaterial() { return aDefaultBackMaterial; }
//  void SetDefaultBackMaterial(const B3dMaterial& rNew) { aDefaultBackMaterial = rNew; }
//-/    const Base3DTextureKind GetDefaultTextureKind() { return eDefaultTextureKind; }
//-/    void SetDefaultTextureKind(const Base3DTextureKind eNew) { eDefaultTextureKind = eNew; }
//-/    const Base3DTextureMode GetDefaultTextureMode() { return eDefaultTextureMode; }
//-/    void SetDefaultTextureMode(const Base3DTextureMode eNew) { eDefaultTextureMode = eNew; }
//-/    const BOOL GetDefaultDoubleSided() { return bDefaultDoubleSided; }
//-/    void SetDefaultDoubleSided(const BOOL bNew) { bDefaultDoubleSided = bNew; }
    const BOOL GetDefaultCreateNormals() { return bDefaultCreateNormals; }
    void SetDefaultCreateNormals(const BOOL bNew) { bDefaultCreateNormals = bNew; }
    const BOOL GetDefaultCreateTexture() { return bDefaultCreateTexture; }
    void SetDefaultCreateTexture(const BOOL bNew) { bDefaultCreateTexture = bNew; }
//-/    const BOOL GetDefaultUseStdNormals() { return bDefaultUseStdNormals; }
//-/    void SetDefaultUseStdNormals(const BOOL bNew) { bDefaultUseStdNormals = bNew; }
//-/    const BOOL GetDefaultUseStdNormalsUseSphere() { return bDefaultUseStdNormalsUseSphere; }
//-/    void SetDefaultUseStdNormalsUseSphere(const BOOL bNew) { bDefaultUseStdNormalsUseSphere = bNew; }
//-/    const BOOL GetDefaultInvertNormals() { return bDefaultInvertNormals; }
//-/    void SetDefaultInvertNormals(const BOOL bNew) { bDefaultInvertNormals = bNew; }
//-/    const BOOL GetDefaultUseStdTextureX() { return bDefaultUseStdTextureX; }
//-/    void SetDefaultUseStdTextureX(const BOOL bNew) { bDefaultUseStdTextureX = bNew; }
//-/    const BOOL GetDefaultUseStdTextureXUseSphere() { return bDefaultUseStdTextureXUseSphere; }
//-/    void SetDefaultUseStdTextureXUseSphere(const BOOL bNew) { bDefaultUseStdTextureXUseSphere = bNew; }
//-/    const BOOL GetDefaultUseStdTextureY() { return bDefaultUseStdTextureY; }
//-/    void SetDefaultUseStdTextureY(const BOOL bNew) { bDefaultUseStdTextureY = bNew; }
//-/    const BOOL GetDefaultUseStdTextureYUseSphere() { return bDefaultUseStdTextureYUseSphere; }
//-/    void SetDefaultUseStdTextureYUseSphere(const BOOL bNew) { bDefaultUseStdTextureYUseSphere = bNew; }
//-/    const BOOL GetDefaultShadow3D() { return bDefaultShadow3D; }
//-/    void SetDefaultShadow3D(const BOOL bNew) { bDefaultShadow3D = bNew; }
//-/    const BOOL GetDefaultFilterTexture() { return bDefaultFilterTexture; }
//-/    void SetDefaultFilterTexture(const BOOL bNew) { bDefaultFilterTexture = bNew; }
    const BOOL GetDefaultUseDifferentBackMaterial() { return bDefaultUseDifferentBackMaterial; }
    void SetDefaultUseDifferentBackMaterial(const BOOL bNew) { bDefaultUseDifferentBackMaterial = bNew; }

    // Cube-Objekt
    const Vector3D& GetDefaultCubePos() { return aDefaultCubePos; }
    void SetDefaultCubePos(const Vector3D& rNew) { aDefaultCubePos = rNew; }
    const Vector3D& GetDefaultCubeSize() { return aDefaultCubeSize; }
    void SetDefaultCubeSize(const Vector3D& rNew) { aDefaultCubeSize = rNew; }
    const UINT16 GetDefaultCubeSideFlags() { return nDefaultCubeSideFlags; }
    void SetDefaultCubeSideFlags(const UINT16 nNew) { nDefaultCubeSideFlags = nNew; }
    const BOOL GetDefaultCubePosIsCenter() { return bDefaultCubePosIsCenter; }
    void SetDefaultCubePosIsCenter(const BOOL bNew) { bDefaultCubePosIsCenter = bNew; }

    // Sphere-Objekt
//-/    const long GetDefaultHSegments() { return nDefaultHSegments; }
//-/    void SetDefaultHSegments(const long nNew) { nDefaultHSegments = nNew; }
//-/    const long GetDefaultVSegments() { return nDefaultVSegments; }
//-/    void SetDefaultVSegments(const long nNew) { nDefaultVSegments = nNew; }
    const Vector3D& GetDefaultSphereCenter() { return aDefaultSphereCenter; }
    void SetDefaultSphereCenter(const Vector3D& rNew) { aDefaultSphereCenter = rNew; }
    const Vector3D& GetDefaultSphereSize() { return aDefaultSphereSize; }
    void SetDefaultSphereSize(const Vector3D& rNew) { aDefaultSphereSize = rNew; }

    // Lathe-Objekt
    const long GetDefaultLatheEndAngle() { return nDefaultLatheEndAngle; }
    void SetDefaultLatheEndAngle(const long nNew) { nDefaultLatheEndAngle = nNew; }
    const double GetDefaultLatheScale() { return fDefaultLatheScale; }
    void SetDefaultLatheScale(const double fNew) { fDefaultLatheScale = fNew; }
//-/    const double GetDefaultBackScale() { return fDefaultBackScale; }
//-/    void SetDefaultBackScale(const double fNew) { fDefaultBackScale = fNew; }
//-/    const double GetDefaultPercentDiag() { return fDefaultPercentDiag; }
//-/    void SetDefaultPercentDiag(const double fNew) { fDefaultPercentDiag = fNew; }
    const BOOL GetDefaultLatheSmoothed() { return bDefaultLatheSmoothed; }
    void SetDefaultLatheSmoothed(const BOOL bNew) { bDefaultLatheSmoothed = bNew; }
    const BOOL GetDefaultLatheSmoothFrontBack() { return bDefaultLatheSmoothFrontBack; }
    void SetDefaultLatheSmoothFrontBack(const BOOL bNew) { bDefaultLatheSmoothFrontBack = bNew; }
    const BOOL GetDefaultLatheCharacterMode() { return bDefaultLatheCharacterMode; }
    void SetDefaultLatheCharacterMode(const BOOL bNew) { bDefaultLatheCharacterMode = bNew; }
    const BOOL GetDefaultLatheCloseFront() { return bDefaultLatheCloseFront; }
    void SetDefaultLatheCloseFront(const BOOL bNew) { bDefaultLatheCloseFront = bNew; }
    const BOOL GetDefaultLatheCloseBack() { return bDefaultLatheCloseBack; }
    void SetDefaultLatheCloseBack(const BOOL bNew) { bDefaultLatheCloseBack = bNew; }

    // Extrude-Objekt
    const double GetDefaultExtrudeScale() { return fDefaultExtrudeScale; }
    void SetDefaultExtrudeScale(const double fNew) { fDefaultExtrudeScale = fNew; }
//-/    const double GetDefaultExtrudeDepth() { return fDefaultExtrudeDepth; }
//-/    void SetDefaultExtrudeDepth(const double fNew) { fDefaultExtrudeDepth = fNew; }
    const BOOL GetDefaultExtrudeSmoothed() { return bDefaultExtrudeSmoothed; }
    void SetDefaultExtrudeSmoothed(const BOOL bNew) { bDefaultExtrudeSmoothed = bNew; }
    const BOOL GetDefaultExtrudeSmoothFrontBack() { return bDefaultExtrudeSmoothFrontBack; }
    void SetDefaultExtrudeSmoothFrontBack(const BOOL bNew) { bDefaultExtrudeSmoothFrontBack = bNew; }
    const BOOL GetDefaultExtrudeCharacterMode() { return bDefaultExtrudeCharacterMode; }
    void SetDefaultExtrudeCharacterMode(const BOOL bNew) { bDefaultExtrudeCharacterMode = bNew; }
    const BOOL GetDefaultExtrudeCloseFront() { return bDefaultExtrudeCloseFront; }
    void SetDefaultExtrudeCloseFront(const BOOL bNew) { bDefaultExtrudeCloseFront = bNew; }
    const BOOL GetDefaultExtrudeCloseBack() { return bDefaultExtrudeCloseBack; }
    void SetDefaultExtrudeCloseBack(const BOOL bNew) { bDefaultExtrudeCloseBack = bNew; }

    // Scene-Objekt
//-/    const B3dLightGroup& GetDefaultLightGroup() { return aDefaultLightGroup; }
//-/    void SetDefaultLightGroup(const B3dLightGroup& rNew) { aDefaultLightGroup = rNew; }
//-/    const Vector3D& GetDefaultShadowPlaneDirection() { return aDefaultShadowPlaneDirection; }
//-/    void SetDefaultShadowPlaneDirection(const Vector3D& rNew) { aDefaultShadowPlaneDirection = rNew; }
//-/    const Base3DShadeModel GetDefaultShadeModel() { return eDefaultShadeModel; }
//-/    void SetDefaultShadeModel(const Base3DShadeModel eNew) { eDefaultShadeModel = eNew; }
    const BOOL GetDefaultDither() { return bDefaultDither; }
    void SetDefaultDither(const BOOL bNew) { bDefaultDither = bNew; }
//-/    const BOOL GetDefaultForceDraftShadeModel() { return bDefaultForceDraftShadeModel; }
//-/    void SetDefaultForceDraftShadeModel(const BOOL bNew) { bDefaultForceDraftShadeModel = bNew; }

    // Default-Attribute setzen/lesen
//-/    void SetDefaultValues(const SfxItemSet& rAttr);
//-/    void TakeDefaultValues(SfxItemSet& rAttr);
//-/
//-/protected:
};

}//end of namespace binfilter
#endif          // _E3D_DEFLT3D_HXX
