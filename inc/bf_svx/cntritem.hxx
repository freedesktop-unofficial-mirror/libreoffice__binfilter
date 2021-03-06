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
#ifndef _SVX_ITEM_HXX
#define _SVX_ITEM_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_svtools/eitem.hxx>
#include <bf_svx/svxids.hrc>
namespace binfilter {

// class SvxContourItem --------------------------------------------------

/*
    [Beschreibung]
    Dieses Item beschreibt, ob Konturschrift eingestellt ist.
*/

class SvxContourItem : public SfxBoolItem
{
public:
    TYPEINFO();

    SvxContourItem( const BOOL bContoured = FALSE,
                    const USHORT nId = ITEMID_CONTOUR );

    // "pure virtual Methoden" vom SfxPoolItem
    virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;
    virtual SfxPoolItem*    Create(SvStream &, USHORT) const;
    virtual SvStream& Store(SvStream &rStream, USHORT) const { return rStream; }


    inline SvxContourItem& operator=(const SvxContourItem& rCont)
    {
        SetValue(rCont.GetValue());
        return *this;
    }
};

}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
