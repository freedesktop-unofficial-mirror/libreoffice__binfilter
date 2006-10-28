/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: udlnitem.hxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 04:20:45 $
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
#ifndef _SVX_UDLNITEM_HXX
#define _SVX_UDLNITEM_HXX

// include ---------------------------------------------------------------

#ifndef _SFXENUMITEM_HXX //autogen
#include <svtools/eitem.hxx>
#endif
#ifndef _SVX_SVXIDS_HRC
#include <bf_svx/svxids.hrc>
#endif
#ifndef _VCL_VCLENUM_HXX
#include <vcl/vclenum.hxx>
#endif
#ifndef _TOOLS_COLOR_HXX
#include <tools/color.hxx>
#endif

namespace rtl
{
    class OUString;
}
namespace binfilter {
class SvXMLUnitConverter;

// class SvxUnderlineItem ------------------------------------------------

/*  [Beschreibung]

    Dieses Item beschreibt, ob und wie unterstrichen ist.
*/

class SvxUnderlineItem : public SfxEnumItem
{
    Color mColor;
public:
    TYPEINFO();

    SvxUnderlineItem( const FontUnderline eSt = UNDERLINE_NONE,
                      const USHORT nId = ITEMID_UNDERLINE );

    // "pure virtual Methoden" vom SfxPoolItem

    virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;
    virtual SfxPoolItem*    Create(SvStream &, USHORT) const;
    virtual SvStream&       Store(SvStream &, USHORT nItemVersion) const;
    virtual USHORT          GetValueCount() const;

    virtual sal_Bool        QueryValue( ::com::sun::star::uno::Any& rVal,
                                        BYTE nMemberId = 0 ) const;
    virtual sal_Bool        PutValue( const ::com::sun::star::uno::Any& rVal,
                                        BYTE nMemberId = 0 );

    // MS VC4.0 kommt durcheinander
    void                    SetValue( USHORT nNewVal )
                                {SfxEnumItem::SetValue(nNewVal); }
    virtual int             HasBoolValue() const;
    virtual BOOL            GetBoolValue() const;

    virtual int              operator==( const SfxPoolItem& ) const;

    inline SvxUnderlineItem& operator=(const SvxUnderlineItem& rUnderline)
        {
            SetValue( rUnderline.GetValue() );
            SetColor( rUnderline.GetColor() );
            return *this;
        }

    // enum cast
    FontUnderline           GetUnderline() const
                                { return (FontUnderline)GetValue(); }
    void                    SetUnderline ( FontUnderline eNew )
                                { SetValue((USHORT) eNew); }

    const Color&            GetColor() const                { return mColor; }
    void                    SetColor( const Color& rCol )   { mColor = rCol; }
};

}//end of namespace binfilter
#endif // #ifndef _SVX_UDLNITEM_HXX

