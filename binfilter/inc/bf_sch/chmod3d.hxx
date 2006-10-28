/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: chmod3d.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 02:46:42 $
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


#ifndef SCH_CHARTMODEL_3D_OBJECTS
#define SCH_CHARTMODEL_3D_OBJECTS


//Ableitungen der 3D-Objekte, um #52277# zu beheben.
//Ueberladen der NbcSetAttributes um Attr abzufangen und in das ChartModel zu leiten

#ifndef _E3D_EXTRUD3D_HXX //autogen
#include <bf_svx/extrud3d.hxx>
#endif
#ifndef _E3D_POLYGON3D_HXX //autogen
#include <bf_svx/polygn3d.hxx>
#endif
#ifndef _E3D_DEFLT3D_HXX //autogen
#include <bf_svx/deflt3d.hxx>
#endif
#ifndef _SVDORECT_HXX //autogen
#include <bf_svx/svdorect.hxx>
#endif
#ifndef _E3D_LATHE3D_HXX //autogen
#include <bf_svx/lathe3d.hxx>
#endif
#define CHART_SHAPE3D_IGNORE  -2 //intern! (GetChartShapeStyle()!)
#define CHART_SHAPE3D_ANY     -1 //undefinierter Typ (GetChartShapeStyle()!)
#define CHART_SHAPE3D_SQUARE   0
#define CHART_SHAPE3D_CYLINDER 1
#define CHART_SHAPE3D_CONE     2
#define CHART_SHAPE3D_PYRAMID  3 //reserved
#define CHART_SHAPE3D_HANOI    4
namespace binfilter {


class SchE3dLatheObj : public E3dLatheObj
{
public:
    SchE3dLatheObj(E3dDefaultAttributes& rDefault, const PolyPolygon& rPP)
        :E3dLatheObj(rDefault,rPP){};
    SchE3dLatheObj(E3dDefaultAttributes& rDefault, const XPolyPolygon& rXPP)
        :E3dLatheObj(rDefault,rXPP){};
    SchE3dLatheObj(E3dDefaultAttributes& rDefault, const XPolygon& rXPoly)
        :E3dLatheObj(rDefault,rXPoly){};
    SchE3dLatheObj(E3dDefaultAttributes& rDefault, const PolyPolygon3D rPoly3D)
        :E3dLatheObj(rDefault,rPoly3D){};
    SchE3dLatheObj()
        :E3dLatheObj(){};

//-/    virtual void NbcSetAttributes(const SfxItemSet& rAttr, FASTBOOL bReplaceAll);
    virtual void SetItem(const SfxPoolItem& rItem);
    virtual void SetItemSet(const SfxItemSet& rSet);
};


class SchE3dExtrudeObj : public E3dExtrudeObj
{
public:

    SchE3dExtrudeObj(E3dDefaultAttributes& rDefault, const PolyPolygon& rPP, double fDepth)
        :E3dExtrudeObj(rDefault,rPP,fDepth){};
    SchE3dExtrudeObj(E3dDefaultAttributes& rDefault, const XPolyPolygon& rXPP, double fDepth)
        :E3dExtrudeObj(rDefault,rXPP,fDepth){};
    SchE3dExtrudeObj()
        :E3dExtrudeObj(){};

//-/    virtual void NbcSetAttributes(const SfxItemSet& rAttr, FASTBOOL bReplaceAll);
    virtual void SetItem(const SfxPoolItem& rItem);
    virtual void SetItemSet(const SfxItemSet& rSet);
};

class SchE3dPolygonObj : public E3dPolygonObj
{
public:
    SchE3dPolygonObj(E3dDefaultAttributes& rDefault, const PolyPolygon3D& rPoly3D,
        BOOL bLinOnly=FALSE)
        :E3dPolygonObj(rDefault,rPoly3D,bLinOnly){};

    SchE3dPolygonObj(E3dDefaultAttributes& rDefault, const PolyPolygon3D& rPoly3D,
        const PolyPolygon3D& rVector3D, BOOL bLinOnly=FALSE)
        :E3dPolygonObj(rDefault,rPoly3D,rVector3D,bLinOnly){};

    SchE3dPolygonObj(E3dDefaultAttributes& rDefault, const PolyPolygon3D& rPoly3D,
        const PolyPolygon3D& rVector3D, const PolyPolygon3D& rNormal3D, BOOL bLinOnly=FALSE)
        :E3dPolygonObj(rDefault,rPoly3D,rVector3D,rNormal3D,bLinOnly){};

    SchE3dPolygonObj(E3dDefaultAttributes& rDefault, const Vector3D& rP1,
        const Vector3D& rP2, BOOL bLinOnly=TRUE)
        : E3dPolygonObj(rDefault,rP1,rP2,bLinOnly){};

    SchE3dPolygonObj() : E3dPolygonObj(){};

//-/    virtual void NbcSetAttributes(const SfxItemSet& rAttr, FASTBOOL bReplaceAll);
    virtual void SetItem(const SfxPoolItem& rItem);
    virtual void SetItemSet(const SfxItemSet& rSet);
};


class SchE3dObject : public E3dObject
{

 public:
     SchE3dObject()
         :E3dObject(){};

//-/     virtual void NbcSetAttributes(const SfxItemSet& rAttr, FASTBOOL bReplaceAll);
    virtual void SetItemSet(const SfxItemSet& rSet);
};
class SchRectObj : public SdrRectObj
{
public:
    SchRectObj(SdrObjKind eNewTextKind, const Rectangle& rRect)
        :SdrRectObj(eNewTextKind,rRect){};
    SchRectObj(const Rectangle& rRect): SdrRectObj(rRect){};

    virtual void NbcSetOutlinerParaObject(OutlinerParaObject* pTextObject);
//-/    virtual void NbcSetAttributes(const SfxItemSet& rAttr, FASTBOOL bReplaceAll);
    virtual void SetItemSet(const SfxItemSet& rSet);
};

} //namespace binfilter
#endif




