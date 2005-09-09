/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: cscoitem.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 13:12:59 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/
#ifndef _SVX_CSCOITEM_HXX
#define _SVX_CSCOITEM_HXX

// include ---------------------------------------------------------------

#ifndef _STRING_HXX //autogen
#include <tools/string.hxx>
#endif
#ifndef _SVX_COLRITEM_HXX
#include <bf_svx/colritem.hxx>
#endif
namespace binfilter {

// class SvxCharSetColorItem ---------------------------------------------

/*  [Beschreibung]

    PB: wird nur intern im Reader des Writers benoetigt
*/

class SvxCharSetColorItem : public SvxColorItem
{
    rtl_TextEncoding eFrom;
public:
    TYPEINFO();

    SvxCharSetColorItem( const USHORT nId = ITEMID_CHARSETCOLOR );
    SvxCharSetColorItem( const Color& aColor, const rtl_TextEncoding eFrom,
                     const USHORT nId = ITEMID_CHARSETCOLOR );

    // "pure virtual Methoden" vom SfxPoolItem
//STRIP001  virtual SfxItemPresentation GetPresentation( SfxItemPresentation ePres,
//STRIP001                                  SfxMapUnit eCoreMetric,
//STRIP001                                  SfxMapUnit ePresMetric,
//STRIP001                                     String &rText, const IntlWrapper * = 0 ) const;

    virtual SfxPoolItem*     Clone( SfxItemPool *pPool = 0 ) const;
    virtual SfxPoolItem*     Create(SvStream &, USHORT) const;
    virtual SvStream&        Store(SvStream &, USHORT nItemVersion) const;

    inline rtl_TextEncoding&    GetCharSet() { return eFrom; }
    inline rtl_TextEncoding     GetCharSet() const { return eFrom; }

    inline SvxCharSetColorItem& operator=(const SvxCharSetColorItem& rColor)
    {
        SetValue( rColor.GetValue() );
        eFrom = rColor.GetCharSet();
        return *this;
    }
};

}//end of namespace binfilter
#endif

