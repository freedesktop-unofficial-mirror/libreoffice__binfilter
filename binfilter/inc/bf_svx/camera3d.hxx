/*************************************************************************
 *
 *  $RCSfile: camera3d.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:36 $
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

#ifndef _CAMERA3D_HXX
#define _CAMERA3D_HXX

#ifndef _VIEWPT3D_HXX
#include <bf_svx/viewpt3d.hxx>
#endif

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
    void    SetFocalLengthWithCorrect(double fLen);
    double  GetFocalLength() const { return fFocalLength; }

    // Neigung links/rechts
    void    SetBankAngle(double fAngle);
    double  GetBankAngle() const { return fBankAngle; }

    // Um die Kameraposition drehen, LookAt wird dabei veraendert
    void Rotate(double fHAngle, double fVAngle);

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

#endif      // _CAMERA3D_HXX
