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
#ifndef _SVX_EMPHITEM_HXX
#define _SVX_EMPTITEM_HXX

#include <vcl/vclenum.hxx>
#include <bf_svtools/intitem.hxx>
#include <bf_svx/svxids.hrc>

namespace rtl
{
    class OUString;
}
namespace binfilter {
class SvXMLUnitConverter;
// class SvxEmphasisMarkItem ----------------------------------------------

/* [Beschreibung]

    Dieses Item beschreibt die Font-Betonung.
*/

class SvxEmphasisMarkItem : public SfxUInt16Item
{
public:
    TYPEINFO();

    SvxEmphasisMarkItem(  const FontEmphasisMark eVal = EMPHASISMARK_NONE,
                          const USHORT nId = ITEMID_EMPHASISMARK );

    // "pure virtual Methoden" vom SfxPoolItem + SfxEnumItem

    virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;
    virtual SfxPoolItem*    Create(SvStream &, USHORT) const;
    virtual SvStream& Store(SvStream &rStream, USHORT) const { return rStream; }
    virtual USHORT          GetVersion( USHORT nFileVersion ) const;

    virtual bool            QueryValue( ::com::sun::star::uno::Any& rVal,
                                            BYTE nMemberId = 0 ) const;
    virtual bool            PutValue( const ::com::sun::star::uno::Any& rVal,
                                            BYTE nMemberId = 0 );

    inline SvxEmphasisMarkItem& operator=(const SvxEmphasisMarkItem& rItem )
    {
        SetValue( rItem.GetValue() );
        return *this;
    }

    // enum cast
    FontEmphasisMark        GetEmphasisMark() const
                                { return (FontEmphasisMark)GetValue(); }
    void                    SetEmphasisMark( FontEmphasisMark eNew )
                                { SetValue( (USHORT)eNew ); }
};

}//end of namespace binfilter
#endif // #ifndef _SVX_EMPHITEM_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
