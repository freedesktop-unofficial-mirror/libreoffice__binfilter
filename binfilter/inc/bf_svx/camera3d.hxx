/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: camera3d.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: hr $ $Date: 2007-01-02 18:31:20 $
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

#ifndef _CAMERA3D_HXX
#define _CAMERA3D_HXX

#ifndef _VIEWPT3D_HXX
#include <bf_svx/viewpt3d.hxx>
#endif
namespace binfilter {

/*************************************************************************
|*
|* Kamera-Ableitung
|*
\************************************************************************/

class Camera3D : public Viewport3D
{
 protected:
    Vector3D    aResetPos;
    Vector3D    aResetLookAt;
    double      fResetFocalLength;
    double      fResetBankAngle;

    Vector3D    aPosition;
    Vector3D    aLookAt;
    double      fFocalLength;
    double      fBankAngle;

    FASTBOOL    bAutoAdjustProjection;

 public:
    Camera3D(const Vector3D& rPos, const Vector3D& rLookAt,
             double fFocalLen = 35.0, double fBankAng = 0);
    Camera3D();

    // Anfangswerte wieder herstellen
    void Reset();

    void SetDefaults(const Vector3D& rPos, const Vector3D& rLookAt,
                     double fFocalLen = 35.0, double fBankAng = 0);

    void SetViewWindow(double fX, double fY, double fW, double fH);

    void SetPosition(const Vector3D& rNewPos);
    const Vector3D& GetPosition() const { return aPosition; }
    void SetLookAt(const Vector3D& rNewLookAt);
    const Vector3D& GetLookAt() const { return aLookAt; }
    void SetPosAndLookAt(const Vector3D& rNewPos, const Vector3D& rNewLookAt);

    // Brennweite in mm
    void    SetFocalLength(double fLen);
    double  GetFocalLength() const { return fFocalLength; }

    // Neigung links/rechts
    void    SetBankAngle(double fAngle);
    double  GetBankAngle() const { return fBankAngle; }

    // Um den Blickpunkt drehen, Position wird dabei veraendert
    void RotateAroundLookAt(double fHAngle, double fVAngle);

    void SetAutoAdjustProjection(FASTBOOL bAdjust = TRUE)
        { bAutoAdjustProjection = bAdjust; }
    FASTBOOL IsAutoAdjustProjection() const { return bAutoAdjustProjection; }

    // Die Umstellung von Filerevision 12 auf 13 erfolgte zur 355
    // 5.2.1997 Franz Gotsis, ReadData31 kann also auch die
    // zur 4.0 gehoerigen Filrevisionen bis zu 12 lesen.
    virtual void WriteData31(SvStream& rOut) const;
    virtual void ReadData31(SvStream& rIn);

    virtual void WriteData(SvStream& rOut) const;
    virtual void ReadData(const SdrObjIOHeader& rHead, SvStream& rIn);
};

SvStream& operator<<(SvStream& rOStream, const Viewport3D&);
SvStream& operator>>(SvStream& rIStream, Viewport3D&);

}//end of namespace binfilter
#endif      // _CAMERA3D_HXX
