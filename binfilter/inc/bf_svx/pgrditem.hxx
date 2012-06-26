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
#ifndef _SVX_PGRDITEM_HXX
#define _SVX_PGRDITEM_HXX

#include <bf_svtools/bf_solar.h>

// include ---------------------------------------------------------------

#include <bf_svtools/eitem.hxx>
namespace binfilter {

// class SvxParaGridItem -------------------------------------------------

/*
    [Beschreibung]
    Paragraph snap to grid
*/

class SvxParaGridItem : public SfxBoolItem
{
public:
    TYPEINFO();

    SvxParaGridItem( const BOOL bSnapToGrid = TRUE,
                     const USHORT nId = ITEMID_PARAGRID );

    // "pure virtual Methoden" vom SfxPoolItem
    virtual SfxPoolItem*    Clone( SfxItemPool* = NULL ) const { return NULL; } // DBG_BF_ASSERT
    virtual SfxPoolItem*    Create(SvStream&, USHORT) const { return NULL; } // DBG_BF_ASSERT
    virtual USHORT          GetVersion( USHORT nFileVersion ) const;

    virtual SfxItemPresentation GetPresentation( SfxItemPresentation ePres,
                                    SfxMapUnit eCoreMetric,
                                    SfxMapUnit ePresMetric,
                                    String &rText, const ::IntlWrapper * = 0 ) const;
};

}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
