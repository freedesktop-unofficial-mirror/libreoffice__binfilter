/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: b3dlight.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: ihi $ $Date: 2006-11-14 12:17:46 $
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

#ifndef _B3D_B3DLIGHT_HXX
#define _B3D_B3DLIGHT_HXX

#ifndef _SVX_VECTOR3D_HXX
#include "vector3d.hxx"
#endif

#ifndef _SVX_MATRIL3D_HXX
#include "matril3d.hxx"
#endif

#ifndef _STREAM_HXX
#include <tools/stream.hxx>
#endif

namespace binfilter {

/*************************************************************************
|*
|* Unterstuetzte Lichtquellen
|*
\************************************************************************/

#define BASE3D_MAX_NUMBER_LIGHTS        (8)

enum Base3DLightNumber
{
    Base3DLight0 = 0,
    Base3DLight1,
    Base3DLight2,
    Base3DLight3,
    Base3DLight4,
    Base3DLight5,
    Base3DLight6,
    Base3DLight7,
    Base3DLightNone
};

/*************************************************************************
|*
|* Basisklasse fuer Lichtquellen
|*
\************************************************************************/

class B3dLight
{
private:
    Color                   aAmbient;
    Color                   aDiffuse;
    Color                   aSpecular;
    Vector3D                aPosition;
    Vector3D                aPositionEye;
    Vector3D                aSpotDirection;
    Vector3D                aSpotDirectionEye;
    UINT16                  nSpotExponent;
    double                  fSpotCutoff;
    double                  fCosSpotCutoff;
    double                  fConstantAttenuation;
    double                  fLinearAttenuation;
    double                  fQuadraticAttenuation;

    unsigned                bIsFirstLight           : 1;
    unsigned                bIsEnabled              : 1;
    unsigned                bIsDirectionalSource    : 1;
    unsigned                bIsSpot                 : 1;
    unsigned                bIsAmbient              : 1;
    unsigned                bIsDiffuse              : 1;
    unsigned                bIsSpecular             : 1;
    unsigned                bLinearOrQuadratic      : 1;

public:
    B3dLight();

    // Zugriffsfunktionen
    void SetIntensity(const Color rNew,
        Base3DMaterialValue=Base3DMaterialAmbient);
    const Color GetIntensity(Base3DMaterialValue=Base3DMaterialAmbient);
    void SetPositionEye(const Vector3D& rNew)
        { aPositionEye=rNew; }
    const Vector3D& GetPositionEye()
        { return aPositionEye; }
    void SetPosition(const Vector3D& rNew)
        { aPosition=rNew; }
    const Vector3D& GetPosition()
        { return aPosition; }
    void SetSpotDirection(const Vector3D& rNew);
    const Vector3D& GetSpotDirection()
        { return aSpotDirection; }
    void SetSpotDirectionEye(const Vector3D& rNew);
    const Vector3D& GetSpotDirectionEye()
        { return aSpotDirectionEye; }
    void SetSpotExponent(UINT16 nNew)
        { nSpotExponent=nNew; }
    UINT16 GetSpotExponent()
        { return nSpotExponent; }
    void SetSpotCutoff(double fNew) ;
    double GetSpotCutoff()
        { return fSpotCutoff; }
    double GetCosSpotCutoff()
        { return fCosSpotCutoff; }
    void SetConstantAttenuation(double fNew)
        { fConstantAttenuation=fNew; }
    double GetConstantAttenuation()
        { return fConstantAttenuation; }
    void SetLinearAttenuation(double fNew);
    double GetLinearAttenuation()
        { return fLinearAttenuation; }
    void SetQuadraticAttenuation(double fNew);
    double GetQuadraticAttenuation()
        { return fQuadraticAttenuation; }

    void Enable(BOOL bNew=TRUE)
        { bIsEnabled=bNew; }
    BOOL IsEnabled()
        { return bIsEnabled; }
    void SetFirst(BOOL bNew=TRUE)
        { bIsFirstLight=bNew; }
    BOOL IsFirst()
        { return bIsFirstLight; }
    void SetDirectionalSource(BOOL bNew=TRUE)
        { bIsDirectionalSource=bNew; }
    BOOL IsDirectionalSource()
        { return bIsDirectionalSource; }
    BOOL IsSpot()
        { return bIsSpot; }
    BOOL IsAmbient()
        { return bIsAmbient; }
    BOOL IsDiffuse()
        { return bIsDiffuse; }
    BOOL IsSpecular()
        { return bIsSpecular; }
    BOOL IsLinearOrQuadratic()
        { return bLinearOrQuadratic; }

    void Init();

    // Laden/Speichern in StarView
    virtual void WriteData(SvStream& rOut) const;
    virtual void ReadData(SvStream& rIn);

protected:
};

/*************************************************************************
|*
|* Gruppe von Lichtquellen
|*
\************************************************************************/

class B3dLightGroup
{
private:
    // Lichtquellen
    B3dLight                aLight[BASE3D_MAX_NUMBER_LIGHTS];

    // lokale Parameter des LightModels
    Color                   aGlobalAmbientLight;

    // Hauptschalter fuer die Beleuchtung
    unsigned                bLightingEnabled            : 1;
    unsigned                bLocalViewer                : 1;
    unsigned                bModelTwoSide               : 1;

public:
    // Konstruktor
    B3dLightGroup();

    // lokale Parameter des LightModels
    virtual void SetGlobalAmbientLight(const Color rNew);
    const Color GetGlobalAmbientLight();
    virtual void SetLocalViewer(BOOL bNew=TRUE);
    BOOL GetLocalViewer();
    virtual void SetModelTwoSide(BOOL bNew=FALSE);
    BOOL GetModelTwoSide();

    // Hauptschalter fuer die Beleuchtung
    virtual void EnableLighting(BOOL bNew=TRUE);
    BOOL IsLightingEnabled();

    // Lichtquellen Interface
    void SetIntensity(const Color rNew,
        Base3DMaterialValue=Base3DMaterialAmbient,
        Base3DLightNumber=Base3DLight0);
    const Color GetIntensity(Base3DMaterialValue=Base3DMaterialAmbient,
        Base3DLightNumber=Base3DLight0);
    void SetPosition(const Vector3D& rNew,
        Base3DLightNumber=Base3DLight0);
    void SetDirection(const Vector3D& rNew,
        Base3DLightNumber=Base3DLight0);
    const Vector3D& GetPosition(Base3DLightNumber=Base3DLight0);
    const Vector3D& GetDirection(Base3DLightNumber=Base3DLight0);
    void SetSpotDirection(const Vector3D& rNew,
        Base3DLightNumber=Base3DLight0);
    const Vector3D& GetSpotDirection(Base3DLightNumber=Base3DLight0);
    void SetSpotExponent(UINT16 nNew,
        Base3DLightNumber=Base3DLight0);
    UINT16 GetSpotExponent(Base3DLightNumber=Base3DLight0);
    void SetSpotCutoff(double fNew,
        Base3DLightNumber=Base3DLight0);
    double GetSpotCutoff(Base3DLightNumber=Base3DLight0);
    void SetConstantAttenuation(double fNew,
        Base3DLightNumber=Base3DLight0);
    double GetConstantAttenuation(Base3DLightNumber=Base3DLight0);
    void SetLinearAttenuation(double fNew,
        Base3DLightNumber=Base3DLight0);
    double GetLinearAttenuation(Base3DLightNumber=Base3DLight0);
    void SetQuadraticAttenuation(double fNew,
        Base3DLightNumber=Base3DLight0);
    double GetQuadraticAttenuation(Base3DLightNumber=Base3DLight0);
    void Enable(BOOL bNew=TRUE,
        Base3DLightNumber=Base3DLight0);
    BOOL IsEnabled(Base3DLightNumber=Base3DLight0);
    BOOL IsDirectionalSource(Base3DLightNumber=Base3DLight0);

    // Direkter Zugriff auf B3dLight
    B3dLight& GetLightObject(Base3DLightNumber=Base3DLight0);

    // Laden/Speichern in StarView
    virtual void WriteData(SvStream& rOut) const;
    virtual void ReadData(SvStream& rIn);

protected:
};

}//end of namespace binfilter

#endif          // _B3D_B3DLIGHT_HXX
