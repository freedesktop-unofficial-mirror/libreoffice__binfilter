/*************************************************************************
 *
 *  $RCSfile: globfunc.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:25:27 $
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


#ifndef __GLOBFUNC_HXX
#define __GLOBFUNC_HXX

#ifndef _E3D_LABEL3D_HXX //autogen
#include <bf_svx/label3d.hxx>
#endif

#include "schgroup.hxx"
#include "objid.hxx"
#include "datapoin.hxx"
#include "datarow.hxx"
#include "objadj.hxx"
#ifndef _SVX_CHRTITEM_HXX //autogen
#include <bf_svx/chrtitem.hxx>
#endif

#ifndef _COM_SUN_STAR_DRAWING_XSHAPE_HPP_
#include <com/sun/star/drawing/XShape.hpp>
#endif
#ifndef _COM_SUN_STAR_UNO_REFERENCE_H_
#include <com/sun/star/uno/Reference.h>
#endif

#include <vector>
namespace binfilter {

//Item-Debugging
#ifdef DBG_UTIL
    class ChartModel;
    extern void Dbg_DebugItems(SfxItemSet& rSet,ChartModel* pModel,long num = 32);
    #define DBG_ITEMS(a,b) Dbg_DebugItems(a,b)
    #define DBG_ITEMSX(a,b,c) Dbg_DebugItems(a,b,c)
#else
    #define DBG_ITEMS(a,b)
    #define DBG_ITEMSX(a,b,c)
#endif

//hunderstel Grad (centi-degrees)in Rad
#define CDEG2RAD(fAngle) (  (double)(fAngle)*F_PI/18000.0 )

void AxisAttrOld2New(SfxItemSet &rDestSet,BOOL bClear,long nId);
void AxisAttrNew2Old(SfxItemSet &rDestSet,long nId,BOOL bClear);

Size GetRotatedTextSize(const Size& rSize,const long nDegrees);
long GetTextRotation(SfxItemSet &rAttr);
long GetTextRotation(SfxItemSet &rAttr,SvxChartTextOrient eOrient);

SdrObject *SetObjectAttr (SdrObject  *pObj,
                          UINT16     nID,
                          BOOL       bProtect,
                          BOOL       bResize,
                          SfxItemSet *pAttr);

SdrObjList *CreateGroup (SdrObjList &rObjList,
                         UINT16     nID,
                         ULONG      nIndex = CONTAINER_APPEND);

SchObjGroup *CreateSimpleGroup (UINT16 nID,
                                BOOL   bProtect,
                                BOOL   bResize);


void CubicSpline (XPolygon &pKnownPoints,
                  int      n,
                  int      splineSize,
                  XPolygon &pSplines);

void TVector (int    n,
              int    k,
              double *t);

double TLeft (double x,
              int    i,
              int    k,
              double *t);

double TRight (double x,
               int    i,
               int    k,
               double *t);

void BVector (double x,
              int    n,
              int    k,
              double *b,
              double *t);

void BSPoint (int      n,
              Point    &p1,
              Point    &p2,
              XPolygon &pKnownPoints,
              double   *b);

void approxMesh (int      splineSize,
                 XPolygon &pSplines,
                 XPolygon &pKnownPoints,
                 int      n,
                 int      k);

double SizeBounds (double,
                   double,
                   BOOL);

void IncValue(double& rValue,
              double  fInc,
              BOOL    bLogarithm);

void DecValue(double& rValue,
              double  fInc,
              BOOL    bLogarithm);

//STRIP001 double CalcFact(double fValue,
//STRIP001              BOOL   bLogarithm,
//STRIP001              double fMinValue,
//STRIP001              double fMaxValue);

Color RGBColor(ColorData nColorName);

String StackString(const String& aString);

//STRIP001 String UnstackString(const String& aString);

//STRIP001 Color SetBrightness(const SfxItemSet &rSourceAttr,
//STRIP001                  SfxItemSet       &rDestAttr,
//STRIP001                  double           fLightFactor);

void AdjustRect (Rectangle          &rRect,
                 ChartAdjust        eAdjust);

Size AdjustRotatedRect (const Rectangle &rRect,
                        ChartAdjust     eAdjust,
                        const Rectangle &rOldRect);

void SetAdjust(ChartAdjust        &eAdjust,
               SvxChartTextOrient eOrient);

void SetTextPos(SdrTextObj  &rTextObj,
                const Point &rPos,SfxItemSet* pAttr);

void AdjustTextSize(SdrTextObj &rTextObj,
                    const Size &rTextSize);

Size GetOutputSize(SdrTextObj& rTextObj);

void SegmentDescr (DataDescription &rDescr,
                   const Rectangle &rRect,
                   long            nStartAng,
                   long            nEndAng,
                   long            nHeight,
                   double          a,
                   double          b);

/** Create a text object for a donut segment.
    @descr  For the given descriptive text of a donut segment a text
        object is created and displayed.  In contrast to the other SegmentDescr
        function the text object is positioned centered around the point that
        lies half way between the start and end angle at a distance of the given
        radius from the donut's center.
    @param  rDescr  The object that represents the description.  It's position is
        calculated in this function.
    @param  rRect   The bounding box of the donut.  Used for determing the donut's
        center.
    @param  nStartAng   Starting angle of the segement.
    @param  nEndAng End angle of the segement.  nStartAngle does not have to be
        lower than or equal to nEndAng (this feature seems to be used as a flag
        but I (AF) don't know what it indicates).
    @param  fRadius Radius at which the text object's reference point will be set.
        A typical value will be half way between the donut ring's inner and outer
        radius so that the text object will be centered in the segment.
*/
void SegmentDescr (DataDescription &rDescr,
                   const Rectangle &rRect,
                   long            nStartAng,
                   long            nEndAng,
                   double          fRadius);

//STRIP001 void ShowErrorLineY (BOOL              bIsVertical,
//STRIP001                   double            fErrorUp,
//STRIP001                   double            fErrorDown,
//STRIP001                   SfxItemSet        &rAttr,
//STRIP001                   const  Point&     rPos,
//STRIP001                   SvxChartIndicate  eMyIndicate,
//STRIP001                   SdrObjList        *pList,
//STRIP001                      ChartModel *      pModel);

//STRIP001 void InsertPolygon (SdrObjList *pList,
//STRIP001                  XPolygon   &rPolygon,
//STRIP001                  SfxItemSet &rAttr);

/** Creates an SchObjGroup containing SdrPathObjects, which are created from the
    XPolygons given in the vector rPolygons.  The items in rItems are applied to
    all of the created objects.

    Note: The ChartModel is needed for the CTOR of SchObjGroup.
 */
SdrObject * CreateErrorGroup(
    ChartModel * pModel,
    const ::std::vector< XPolygon > & rPolygons,
    const SfxItemSet & rItems );

//STRIP001 SdrObject *Create2DPolyObj (SfxItemSet &rAttr,
//STRIP001                          Point      aLeftBottom,
//STRIP001                          Point      aLeftTop,
//STRIP001                          Point      aRightTop,
//STRIP001                          Point      aRightBottom);

//STRIP001 SdrObjList *CreateGroupList (SdrObjList *pList,long nID);

void CreateChartGroup( SchObjGroup* &, SdrObjList* & );

//STRIP001 void CopySetsFrom40To31 (const SfxItemSet &rSourceSet,SfxItemSet &rDestSet);

//STRIP001 void CompareSets (const SfxItemSet &rSourceSet,SfxItemSet &rDestSet);

//STRIP001 void ClearDblItems(const SfxItemSet &rSourceSet,SfxItemSet &rDestSet);

/** Intersect two SfxItemSets in the following way: Modify rDestSet such that
    after this function completes there are only items left that are contained
    in both sets and have equal content (using the != operator of SfxPoolItem)

    Items that are set in either of the itemsets but are not equal are
    invalidated.  This is useful for dialogs.  For a template-like usage, you
    can remove the invalid items by calling ClearInvalidItems() at the result.

    Note: The Intersect method of SfxItemSet works differently for equal and
          non-equal which-ranges.  If the ranges are equal it does something
          like this method, otherwise it just removes items which are not
          contained in the which range of the other item set.

    @param rSourceSet is the item set which will be iterated over
    @param rDestSet   is the item set which is modified such that the condition
                      described above is maintained.
 */
void IntersectSets( const SfxItemSet &  rSource, SfxItemSet &  rDest );

Point SetPointOfRectangle (const Rectangle& rRect, ChartAdjust eAdjust);

void ItemsToFont(const SfxItemSet& rSet,Font& rFont);

BOOL ChIsPointInsideRectangle( const Point& rPoint, const Rectangle& rRect );

//STRIP001 void GlobalGenerate3DAttrDefaultItem( INT16 nWID, SfxItemSet& rSet );

namespace   sch {
        /** @descr  Extract an item for a given which id from one of two item
                sets.  If the the second item set rOverride is valid and
                defines the requested item then return that item, else extract
                the item from the base set.  This has the same effect as merging
                the override item set into the base set but with the advantage
                that no item set has to be copied or even modified.
            @param  nWhich  Specifies the requested item.
            @param  rBaseSet    The item set from which the item is taken if
                it the override item set is not valid or does not contain it.
            @param  rOverrideSet    The item set first search for the requested
                item.
            @param  bOverrideIsValid    If TRUE then rOverrideSet is search for the
                requested item prior to rBaseSet.  If it is FALSE then
                rOverrideSet is ignored.
        */
        inline const SfxPoolItem *  GetItem (USHORT nWhich,
                                    const SfxItemSet & rBaseSet,
                                    const SfxItemSet & rOverrideSet,
                                    BOOL bOverrideIsValid)
        {
            const SfxPoolItem * pItem;

            if (    bOverrideIsValid
                &&  rOverrideSet.GetItemState (
                        nWhich, TRUE, &pItem) == SFX_ITEM_SET)
                return pItem;
            else
                return rBaseSet.GetItem (nWhich);
        }
}

} //namespace binfilter
#endif


