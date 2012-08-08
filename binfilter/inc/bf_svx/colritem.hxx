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
#ifndef _SVX_COLRITEM_HXX
#define _SVX_COLRITEM_HXX

#include <bf_svtools/poolitem.hxx>
#include <bf_svx/svxids.hrc>
#include <tools/color.hxx>

namespace rtl
{
    class OUString;
}
namespace binfilter {
class SvXMLUnitConverter;

// class SvxColorItem ----------------------------------------------------

/*  [Beschreibung]

    Dieses Item beschreibt eine Farbe.
*/

#define VERSION_USEAUTOCOLOR    1

class SvxColorItem : public SfxPoolItem
{
private:
    Color                   mColor;

public:
    TYPEINFO();

    SvxColorItem( const USHORT nId = ITEMID_COLOR );
    SvxColorItem( const Color& aColor, const USHORT nId = ITEMID_COLOR );
    SvxColorItem( SvStream& rStrm, const USHORT nId = ITEMID_COLOR );
    SvxColorItem( const SvxColorItem& rCopy );
    ~SvxColorItem();

    // "pure virtual Methoden" vom SfxPoolItem
    virtual int              operator==( const SfxPoolItem& ) const;
    virtual bool            QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;
    virtual bool            PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 );
    virtual USHORT          GetVersion( USHORT nFileVersion ) const;


    virtual SfxPoolItem*     Clone( SfxItemPool *pPool = 0 ) const;
    virtual SfxPoolItem*     Create(SvStream &, USHORT) const;
    virtual SvStream& Store(SvStream &rStream, USHORT) const { return rStream; }

    inline SvxColorItem& operator=(const SvxColorItem& rColor)
    {
        SetValue( rColor.GetValue() );
        return *this;
    }

    const   Color&          GetValue() const
                            {
                                return mColor;
                            }
            void            SetValue( const Color& rNewCol );

};

}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
