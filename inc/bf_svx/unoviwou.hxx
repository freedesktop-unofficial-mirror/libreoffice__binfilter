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

#ifndef _SVX_UNOVIWOU_HXX
#define _SVX_UNOVIWOU_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_svx/unoedsrc.hxx>
namespace binfilter {

class OutlinerView;

/// Specialization for Draw/Impress
class SvxDrawOutlinerViewForwarder : public SvxEditViewForwarder
{
private:
    OutlinerView&       mrOutlinerView;
    Point               maTextShapeTopLeft;

    Point               GetTextOffset() const;

public:
                        SvxDrawOutlinerViewForwarder( OutlinerView& rOutl, const Point& rShapePosTopLeft );
    virtual             ~SvxDrawOutlinerViewForwarder();

    virtual BOOL        IsValid() const;

    virtual Rectangle   GetVisArea() const;
    virtual Point       LogicToPixel( const Point& rPoint, const MapMode& rMapMode ) const;
    virtual Point       PixelToLogic( const Point& rPoint, const MapMode& rMapMode ) const;

    virtual sal_Bool    GetSelection( ESelection& rSelection ) const;
    virtual sal_Bool    SetSelection( const ESelection& rSelection );
    virtual sal_Bool    Copy()  { return sal_True; } // DBG_BF_ASSERT
    virtual sal_Bool    Cut()   { return sal_True; } // DBG_BF_ASSERT
    virtual sal_Bool    Paste() { return sal_True; } // DBG_BF_ASSERT
};

}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
