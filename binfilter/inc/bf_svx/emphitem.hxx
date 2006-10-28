/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: emphitem.hxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 03:31:04 $
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
#ifndef _SVX_EMPHITEM_HXX
#define _SVX_EMPTITEM_HXX

// include ---------------------------------------------------------------

#ifndef _VCL_VCLENUM_HXX
#include <vcl/vclenum.hxx>
#endif
#ifndef _SFXINTITEM_HXX
#include <svtools/intitem.hxx>
#endif
#ifndef _SVX_SVXIDS_HRC
#include <bf_svx/svxids.hrc>
#endif

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
    virtual SvStream&       Store(SvStream &, USHORT nItemVersion) const;
    virtual USHORT          GetVersion( USHORT nFileVersion ) const;

    virtual sal_Bool        QueryValue( ::com::sun::star::uno::Any& rVal,
                                            BYTE nMemberId = 0 ) const;
    virtual sal_Bool        PutValue( const ::com::sun::star::uno::Any& rVal,
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

