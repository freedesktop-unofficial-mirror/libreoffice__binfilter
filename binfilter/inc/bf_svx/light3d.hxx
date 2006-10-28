/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: light3d.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 03:42:19 $
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

#ifndef _E3D_LIGHT3D_HXX
#define _E3D_LIGHT3D_HXX

#ifndef _E3D_PNTOBJ3D_HXX
#include <bf_svx/pntobj3d.hxx>
#endif
namespace binfilter {

/************************************************************************/

class E3dLight;

#ifndef _E3D_LIGHT3D_LIST
DECLARE_LIST(E3dLightList, E3dLight*)//STRIP008 DECLARE_LIST(E3dLightList, E3dLight*);
#endif

/*************************************************************************
|*
|* Basisklasse fuer alle Lichtquellen, gleichzeitig als ambiente
|* (ungerichtete) Lichtquelle zu verwenden. D.h., die Position dient
|* nur der Verwaltung, hat aber keinen Einfluss auf die Beleuchtung.
|*
\************************************************************************/

class E3dLight : public E3dPointObj
{
 private:
    Color       aColor;
    double      fIntensity;
    double      fRed, fGreen, fBlue;

    FASTBOOL    bOn             : 1;
    FASTBOOL    bVisible        : 1;

 protected:
    FASTBOOL ImpCalcLighting(Color& rNewColor, const Color& rPntColor,
                             double fR, double fG, double fB) const;
    // Lichtquellen koennen Unterobjekte nur selbst anlegen
    virtual void Insert3DObj(E3dObject* p3DObj);

    virtual void CreateLightObj();

 public:
    TYPEINFO();
    E3dLight(const Vector3D& rPos, const Color& rColor,
             double fLightIntensity = 1.0);
    E3dLight();

    virtual UINT16 GetObjIdentifier() const;

    virtual FASTBOOL CalcLighting(Color& rNewColor,
                                  const Vector3D& rPnt,
                                  const Vector3D& rPntNormal,
                                  const Color& rPntColor);

    virtual void SetPosition(const Vector3D& rNewPos);

    double GetIntensity() const { return fIntensity; }
    virtual void SetIntensity(double fNew);

    const Color& GetColor() const { return aColor; }
    virtual void SetColor(const Color& rNewColor);

    FASTBOOL IsOn() const { return bOn; }

    FASTBOOL IsLightObjVisible() const { return bVisible; }

    double GetRed() const   { return fRed; }
    double GetGreen() const { return fGreen; }
    double GetBlue() const  { return fBlue; }

    virtual void WriteData(SvStream& rOut) const;
    virtual void ReadData(const SdrObjIOHeader& rHead, SvStream& rIn);


//-/    virtual void           SetAttributes(const SfxItemSet& rAttr, FASTBOOL bReplaceAll);
//-/    virtual void           NbcSetAttributes(const SfxItemSet& rAttr, FASTBOOL bReplaceAll);
//-/    virtual void           TakeAttributes(SfxItemSet& rAttr, FASTBOOL bMerge, FASTBOOL bOnlyHardAttr) const;
//-/    virtual void Collect3DAttributes(SfxItemSet& rAttr) const;
//-/    virtual void Distribute3DAttributes(const SfxItemSet& rAttr);

    virtual void           SetStyleSheet(SfxStyleSheet* pNewStyleSheet, FASTBOOL bDontRemoveHardAttr);
    virtual SfxStyleSheet* GetStyleSheet() const;
};

}//end of namespace binfilter
#endif          // _E3D_LIGHT3D_HXX
