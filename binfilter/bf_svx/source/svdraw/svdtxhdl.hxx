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

#ifndef _SVDTXHDL_HXX
#define _SVDTXHDL_HXX

#include <bf_svtools/bf_solar.h>

#include <vcl/virdev.hxx>


namespace binfilter {

//************************************************************
//   Vorausdeklarationen
//************************************************************

class SdrOutliner;
class DrawPortionInfo;
class SdrTextObj;
class SdrObjGroup;
class SdrModel;
class ExtOutputDevice;

//************************************************************
//   ImpTextPortionHandler
//************************************************************

class ImpTextPortionHandler
{
    VirtualDevice               aVDev;
    Rectangle                   aFormTextBoundRect;
    SdrOutliner&                rOutliner;
    const SdrTextObj&           rTextObj;
    ExtOutputDevice*            pXOut;

    // Variablen fuer ConvertToPathObj
    SdrObjGroup*                pGroup;
    SdrModel*                   pModel;
    bool                    bToPoly;

    // Variablen fuer DrawFitText
    Point                       aPos;
    Fraction                    aXFact;
    Fraction                    aYFact;

    // Variablen fuer DrawTextToPath
    // #101498#
    //Polygon                       aPoly;
    //long                      nTextWidth;
    ULONG                       nParagraph;
    BOOL                        bToLastPoint;
    BOOL                        bDraw;
    void*                       mpRecordPortions;

private:
    // #101498#
    void SortedAddFormTextRecordPortion(DrawPortionInfo* pInfo);
    void DrawFormTextRecordPortions(Polygon aPoly);
    void ClearFormTextRecordPortions();
    sal_uInt32 GetFormTextPortionsLength(OutputDevice* pOut);

public:
    ImpTextPortionHandler(SdrOutliner& rOutln, const SdrTextObj& rTxtObj);

    void DrawTextToPath(ExtOutputDevice& rXOut, bool bDrawEffect=TRUE);

    // wird von DrawTextToPath() gesetzt:
    const Rectangle& GetFormTextBoundRect() const { return aFormTextBoundRect; }


    // #101498#
    DECL_LINK(FormTextRecordPortionHdl, DrawPortionInfo*);
    //DECL_LINK(FormTextWidthHdl,DrawPortionInfo*);
    //DECL_LINK(FormTextDrawHdl,DrawPortionInfo*);
};

////////////////////////////////////////////////////////////////////////////////////////////////////

}//end of namespace binfilter
#endif //_SVDTXHDL_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
