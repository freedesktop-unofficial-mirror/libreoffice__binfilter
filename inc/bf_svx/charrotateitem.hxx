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
#ifndef _SVX_CHARROTATEITEM_HXX
#define _SVX_CHARROTATEITEM_HXX

#include <bf_svtools/intitem.hxx>
#include <bf_svx/svxids.hrc>
namespace binfilter {

// class SvxCharRotateItem ----------------------------------------------

/* [Description]

    This item defines a character rotation value (0,1 degree). Currently
    character can only be rotated 90,0 and 270,0 degrees.
    The flag FitToLine defines only a UI-Information -
    if true it must also create a SvxCharScaleItem.

*/

class SvxCharRotateItem : public SfxUInt16Item
{
    sal_Bool bFitToLine;
public:
    TYPEINFO();

    SvxCharRotateItem( sal_uInt16 nValue = 0,
                       sal_Bool bFitIntoLine = sal_False,
                       const sal_uInt16 nId = ITEMID_CHARROTATE );

/*NBFF*/    virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;
/*NBFF*/    virtual SfxPoolItem*    Create(SvStream &, USHORT) const;
/*NBFF*/    virtual SvStream&  Store(SvStream & rStrm, USHORT) const { return rStrm; }
    virtual USHORT          GetVersion( USHORT nFileVersion ) const;

/*NBFF*/    virtual SfxItemPresentation GetPresentation( SfxItemPresentation ePres,
/*NBFF*/                                    SfxMapUnit eCoreMetric,
/*NBFF*/                                    SfxMapUnit ePresMetric,
/*NBFF*/                                    String &rText,
/*NBFF*/                                     const ::IntlWrapper * = 0 ) const;

/*NBFF*/    virtual bool PutValue( const ::com::sun::star::uno::Any& rVal,
/*NBFF*/                                    BYTE nMemberId );
/*NBFF*/    virtual bool QueryValue( ::com::sun::star::uno::Any& rVal,
/*NBFF*/                                BYTE nMemberId ) const;

/*NBFF*/    inline SvxCharRotateItem& operator=( const SvxCharRotateItem& rItem )
/*NBFF*/    {
/*NBFF*/        SetValue( rItem.GetValue() );
/*NBFF*/        SetFitToLine( rItem.IsFitToLine() );
/*NBFF*/        return *this;
/*NBFF*/    }

/*NBFF*/    virtual int              operator==( const SfxPoolItem& ) const;

    // our currently only degree values
/*NBFF*/    void SetTopToBotton()                   { SetValue( 2700 ); }
/*NBFF*/    void SetBottomToTop()                   { SetValue(  900 ); }
/*NBFF*/    sal_Bool IsTopToBotton() const          { return 2700 == GetValue(); }
/*NBFF*/    sal_Bool IsBottomToTop() const          { return  900 == GetValue(); }
/*NBFF*/
/*NBFF*/    sal_Bool IsFitToLine() const            { return bFitToLine; }
/*NBFF*/    void SetFitToLine( sal_Bool b )         { bFitToLine = b; }
};

}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
