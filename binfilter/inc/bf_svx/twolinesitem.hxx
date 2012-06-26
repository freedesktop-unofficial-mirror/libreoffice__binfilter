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
#ifndef _SVX_TWOLINESITEM_HXX
#define _SVX_TWOLINESITEM_HXX

#include <sal/types.h>
#include <bf_svtools/poolitem.hxx>
#include <bf_svx/svxids.hrc>

namespace rtl
{
    class OUString;
}
namespace binfilter {
class SvXMLUnitConverter;
class SvxTwoLinesItem : public SfxPoolItem
{
    sal_Unicode cStartBracket, cEndBracket;
    sal_Bool bOn;
public:
    TYPEINFO();
    SvxTwoLinesItem( sal_Bool bOn = TRUE,
                     sal_Unicode nStartBracket = 0,
                     sal_Unicode nEndBracket = 0,
                     sal_uInt16 nId = ITEMID_TWOLINES );
/*NBFF*/    SvxTwoLinesItem( const SvxTwoLinesItem& rAttr );
    virtual ~SvxTwoLinesItem();

    // "pure virtual Methoden" vom SfxPoolItem
    virtual int             operator==( const SfxPoolItem& ) const;
    virtual SfxPoolItem*    Clone( SfxItemPool* pPool = 0 ) const;
/*NBFF*/    virtual SfxPoolItem*    Create(SvStream &, USHORT nVer) const;
/*NBFF*/    virtual SvStream&       Store(SvStream &rStream, USHORT) const { return rStream; }
/*NBFF*/    virtual SfxItemPresentation GetPresentation( SfxItemPresentation ePres,
/*NBFF*/                                    SfxMapUnit eCoreMetric,
/*NBFF*/                                    SfxMapUnit ePresMetric,
/*NBFF*/                                    String &rText,
/*NBFF*/                                     const ::IntlWrapper* pIntl = 0 ) const;

/*NBFF*/    virtual bool          QueryValue( ::com::sun::star::uno::Any& rVal,
/*NBFF*/                                        BYTE nMemberId = 0 ) const;
/*NBFF*/    virtual bool          PutValue( const ::com::sun::star::uno::Any& rVal,
/*NBFF*/                                        BYTE nMemberId = 0 );

    virtual USHORT          GetVersion( USHORT nFFVer ) const;

    SvxTwoLinesItem&        operator=( const SvxTwoLinesItem& rCpy )
    {
        SetValue( rCpy.GetValue() );
        SetStartBracket( rCpy.GetStartBracket() );
        SetEndBracket( rCpy.GetEndBracket() );
        return *this;
    }

    sal_Bool GetValue() const                   { return bOn; }
    void SetValue( sal_Bool bFlag )             { bOn = bFlag; }

    sal_Unicode GetStartBracket() const         { return cStartBracket; }
    void SetStartBracket( sal_Unicode c )       { cStartBracket = c; }

    sal_Unicode GetEndBracket() const           { return cEndBracket; }
    void SetEndBracket( sal_Unicode c )         { cEndBracket = c; }
};

}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
