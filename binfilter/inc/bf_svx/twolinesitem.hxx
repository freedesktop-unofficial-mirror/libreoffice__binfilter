/*************************************************************************
 *
 *  $RCSfile: twolinesitem.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:29:19 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/
#ifndef _SVX_TWOLINESITEM_HXX
#define _SVX_TWOLINESITEM_HXX

#ifndef _SAL_TYPES_H_
#include <sal/types.h>
#endif
#ifndef _SFXPOOLITEM_HXX
#include <svtools/poolitem.hxx>
#endif
#ifndef _SVX_SVXIDS_HRC
#include <bf_svx/svxids.hrc>
#endif

class SvXMLUnitConverter;
#ifdef _USE_NAMESPACE
namespace rtl
{
#endif
    class OUString;
#ifdef _USE_NAMESPACE
}
#endif
namespace binfilter {

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
//STRIP001  SvxTwoLinesItem( const SvxTwoLinesItem& rAttr );
    virtual ~SvxTwoLinesItem();

    // "pure virtual Methoden" vom SfxPoolItem
    virtual int             operator==( const SfxPoolItem& ) const;
    virtual SfxPoolItem*    Clone( SfxItemPool* pPool = 0 ) const;
//STRIP001  virtual SfxPoolItem*    Create(SvStream &, USHORT nVer) const;
//STRIP001  virtual SvStream&       Store(SvStream &, USHORT nIVer) const;
//STRIP001  virtual SfxItemPresentation GetPresentation( SfxItemPresentation ePres,
//STRIP001                                  SfxMapUnit eCoreMetric,
//STRIP001                                  SfxMapUnit ePresMetric,
//STRIP001                                  String &rText,
//STRIP001                                     const IntlWrapper* pIntl = 0 ) const;

//STRIP001  virtual sal_Bool        QueryValue( ::com::sun::star::uno::Any& rVal,
//STRIP001                                      BYTE nMemberId = 0 ) const;
//STRIP001  virtual sal_Bool        PutValue( const ::com::sun::star::uno::Any& rVal,
//STRIP001                                      BYTE nMemberId = 0 );

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

