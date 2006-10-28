/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: charttyp.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 02:46:08 $
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
#ifndef _SFXITEMSET_HXX //autogen
#include <svtools/itemset.hxx>
#endif

#ifndef _SVX_CHRTITEM_HXX //autogen
#include <bf_svx/chrtitem.hxx>
#endif
#ifndef _SVX_TAB_LINE_HXX //autogen
#include <bf_svx/tabline.hxx>
#endif
#include "chtmodel.hxx"
namespace binfilter {

#define SPLINE_NONE  0
#define SPLINE_CUBIC 1
#define SPLINE_B     2

class ChartType
{

    BOOL bHasLines;
    BOOL bIsDonut;
    BOOL bIsPercent;
    BOOL bIs3D;
    BOOL bIsDeep3D;
    BOOL bIsVertical;
    BOOL bIsStacked;

    BOOL bHasVolume;
    BOOL bHasUpDown;
    //Dies ist (noch) ein Booltyp, 0=keins, 1= default.später kann einmal mit Typ=2,3,...
    //ein bestimmtes Symbol an einer Datenreihe gesetzt werden
    INT32 nSymbolType;
    INT32 nShapeType;

    long nSplineType;
    long nSpecialType; //nur fuer Kompatiblität! diese Typen sind derzeit inkonsistent
    long nBaseType;

    void Init();

public:

             ChartType()                                { Init(); }
             ChartType( const SvxChartStyle eStyle )    { Init(); SetType( eStyle ); }
             ChartType( const ChartModel* pModel )      { Init(); SetType( pModel ); }
             ChartType( SfxItemSet* pAttr )             { Init(); SetType( pAttr );  }

             //noch etwas gehackt um den Basetype zu setzen, es wird erstmal ein default
             //SetType(SvxChartType) aufgerufen, da Bars,Pie...Typ im attrset nicht
             //vorhanden ist
    virtual ~ChartType(){};


    SvxChartStyle GetChartStyle() const;

    void SetType(const SvxChartStyle eChartStyle);
    void SetType(const ChartModel* pModel);
    void SetType(const SfxItemSet* pAttr);

    void GetAttrSet(SfxItemSet *pAttr);

    void SetBaseType(const long nBase) {nBaseType=nBase;};
    long GetBaseType() const           {return nBaseType;};
    long GetBaseType(const SvxChartStyle eChartStyle) const;

    BOOL HasLines() const {return bHasLines;};
    BOOL HasLines(const SvxChartStyle eChartStyle) const;

    BOOL IsDonut() const {return bIsDonut;};
    BOOL IsDonut(const SvxChartStyle eChartStyle) const;

    BOOL IsPercent(const SvxChartStyle eChartStyle) const;
    BOOL IsPercent()    const {return bIsPercent;};

    BOOL Is3D(const SvxChartStyle eChartStyle) const;
    BOOL Is3D()         const {return bIs3D;};

    BOOL HasSplines() const {return nSplineType!=SPLINE_NONE;};
    BOOL HasSplines(const SvxChartStyle eChartStyle) const;

    long GetSplineType() const {return nSplineType;};
    long GetSplineType(const SvxChartStyle eChartStyle) const;

    BOOL IsVertical() const {return bIsVertical;};
    BOOL IsVertical(const SvxChartStyle eChartStyle) const;

    BOOL IsStacked(const SvxChartStyle eChartStyle) const;
    BOOL IsStacked()    const {return bIsStacked;};

    BOOL HasSymbols(const SvxChartStyle eChartStyle) const;
    BOOL HasSymbols()   const {return nSymbolType!=SVX_SYMBOLTYPE_NONE;};

    BOOL IsDeep3D(const SvxChartStyle eChartStyle) const;
    BOOL IsDeep3D()     const {return bIsDeep3D;};
};

} //namespace binfilter
