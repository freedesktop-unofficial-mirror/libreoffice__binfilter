/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */


#ifndef __GLOBFUNC_HXX
#define __GLOBFUNC_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_svx/label3d.hxx>

#include "schgroup.hxx"
#include "objid.hxx"
#include "datapoin.hxx"
#include "datarow.hxx"
#include "objadj.hxx"
#include <bf_svx/chrtitem.hxx>

#include <com/sun/star/drawing/XShape.hpp>
#include <com/sun/star/uno/Reference.h>

#include <vector>
namespace binfilter {

//Item-Debugging
#ifdef DBG_UTIL
    class ChartModel;
    extern void Dbg_DebugItems(SfxItemSet& rSet,ChartModel* pModel);
    #define DBG_ITEMS(a,b) Dbg_DebugItems(a,b)
#else
    #define DBG_ITEMS(a,b)
#endif

//hunderstel Grad (centi-degrees)in Rad
#define CDEG2RAD(fAngle) (  (double)(fAngle)*F_PI/18000.0 )

void AxisAttrOld2New(SfxItemSet &rDestSet,BOOL bClear,long nId);

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

double SizeBounds (double,
                   double,
                   BOOL);

void IncValue(double& rValue,
              double  fInc,
              BOOL    bLogarithm);

void DecValue(double& rValue,
              double  fInc,
              BOOL    bLogarithm);


Color RGBColor(ColorData nColorName);

String StackString(const String& aString);



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

/** Creates an SchObjGroup containing SdrPathObjects, which are created from the
    XPolygons given in the vector rPolygons.  The items in rItems are applied to
    all of the created objects.

    Note: The ChartModel is needed for the CTOR of SchObjGroup.
 */
SdrObject * CreateErrorGroup(
    ChartModel * pModel,
    const ::std::vector< XPolygon > & rPolygons,
    const SfxItemSet & rItems );



void CreateChartGroup( SchObjGroup* &, SdrObjList* & );




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


/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
