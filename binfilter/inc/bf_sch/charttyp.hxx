/*************************************************************************
 *
 *  $RCSfile: charttyp.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:25:24 $
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


//STRIP001  BOOL CleanUp();
    SvxChartStyle GetChartStyle() const;

    void SetType(const SvxChartStyle eChartStyle);
    void SetType(const ChartModel* pModel);
    void SetType(const SfxItemSet* pAttr);

    void GetAttrSet(SfxItemSet *pAttr);

//STRIP001  BOOL SetDefaultBaseType(long nDefault=-1);
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