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

#include "unoviwed.hxx"
#include "editview.hxx"
#include "editeng.hxx"
#include "svdotext.hxx"
namespace binfilter {

SvxEditEngineViewForwarder::~SvxEditEngineViewForwarder()
{
    DBG_BF_ASSERT(0, "STRIP");
}

BOOL SvxEditEngineViewForwarder::IsValid() const
{
    DBG_BF_ASSERT(0, "STRIP");
    return sal_True;
}

Rectangle SvxEditEngineViewForwarder::GetVisArea() const
{
    OutputDevice* pOutDev = mrView.GetWindow();

    if( pOutDev )
    {
        Rectangle aVisArea = mrView.GetVisArea();

        // figure out map mode from edit engine
        EditEngine* pEditEngine = mrView.GetEditEngine();

        if( pEditEngine )
        {
            MapMode aMapMode(pOutDev->GetMapMode());
            aVisArea = OutputDevice::LogicToLogic( aVisArea,
                                                   pEditEngine->GetRefMapMode(),
                                                   aMapMode.GetMapUnit() );
            aMapMode.SetOrigin(Point());
            return pOutDev->LogicToPixel( aVisArea, aMapMode );
        }
    }

    return Rectangle();
}

Point SvxEditEngineViewForwarder::LogicToPixel( const Point& rPoint, const MapMode& rMapMode ) const
{
    OutputDevice* pOutDev = mrView.GetWindow();

    if( pOutDev )
    {
        MapMode aMapMode(pOutDev->GetMapMode());
        Point aPoint( OutputDevice::LogicToLogic( rPoint, rMapMode,
                                                  aMapMode.GetMapUnit() ) );
        aMapMode.SetOrigin(Point());
        return pOutDev->LogicToPixel( aPoint, aMapMode );
    }

    return Point();
}

Point SvxEditEngineViewForwarder::PixelToLogic( const Point& rPoint, const MapMode& rMapMode ) const
{
    OutputDevice* pOutDev = mrView.GetWindow();

    if( pOutDev )
    {
        MapMode aMapMode(pOutDev->GetMapMode());
        aMapMode.SetOrigin(Point());
        Point aPoint( pOutDev->PixelToLogic( rPoint, aMapMode ) );
        return OutputDevice::LogicToLogic( aPoint,
                                           aMapMode.GetMapUnit(),
                                           rMapMode );
    }

    return Point();
}

sal_Bool SvxEditEngineViewForwarder::GetSelection( ESelection& rSelection ) const
{
    rSelection = mrView.GetSelection();
    return sal_True;
}

sal_Bool SvxEditEngineViewForwarder::SetSelection( const ESelection& rSelection )
{
    mrView.SetSelection( rSelection );
    return sal_True;
}

sal_Bool SvxEditEngineViewForwarder::Copy()
{
    DBG_BF_ASSERT(0, "STRIP");
    return sal_True;
}

sal_Bool SvxEditEngineViewForwarder::Cut()
{
    DBG_BF_ASSERT(0, "STRIP");
    return sal_True;
}

sal_Bool SvxEditEngineViewForwarder::Paste()
{
    DBG_BF_ASSERT(0, "STRIP");
    return sal_True;
}

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
