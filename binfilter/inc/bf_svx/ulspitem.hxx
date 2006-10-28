/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: ulspitem.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 04:21:12 $
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
#ifndef _SVX_ULSPITEM_HXX
#define _SVX_ULSPITEM_HXX

// include ---------------------------------------------------------------

#ifndef _SFXPOOLITEM_HXX //autogen
#include <svtools/poolitem.hxx>
#endif
#ifndef _SVX_SVXIDS_HRC
#include <bf_svx/svxids.hrc>
#endif

namespace rtl
{
    class OUString;
}
namespace binfilter {

// class SvxULSpaceItem --------------------------------------------------

/*
[Beschreibung]
Dieses Item beschreibt den oberen und unteren Rand einer Seite oder Absatz.
*/

#define ULSPACE_16_VERSION  ((USHORT)0x0001)

class SvxULSpaceItem : public SfxPoolItem
{
    USHORT nUpper;  //Oberer Rand
    USHORT nLower;  //Unterer Rand
    USHORT nPropUpper, nPropLower;      // relativ oder absolut (=100%)
public:
    TYPEINFO();

    SvxULSpaceItem( const USHORT nId = ITEMID_ULSPACE );
    SvxULSpaceItem( const USHORT nUp, const USHORT nLow,
                    const USHORT nId = ITEMID_ULSPACE );
    inline SvxULSpaceItem& operator=( const SvxULSpaceItem &rCpy );

    // "pure virtual Methoden" vom SfxPoolItem
    virtual int              operator==( const SfxPoolItem& ) const;

    virtual sal_Bool             QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;
    virtual sal_Bool             PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 );


    virtual SfxPoolItem*     Clone( SfxItemPool *pPool = 0 ) const;
    virtual SfxPoolItem*     Create(SvStream &, USHORT) const;
    virtual SvStream&        Store(SvStream &, USHORT nItemVersion ) const;
    virtual USHORT           GetVersion( USHORT nFileVersion ) const;

    inline void SetUpper( const USHORT nU, const USHORT nProp = 100 );
    inline void SetLower( const USHORT nL, const USHORT nProp = 100 );

    void SetUpperValue( const USHORT nU ) { nUpper = nU; }
    void SetLowerValue( const USHORT nL ) { nLower = nL; }
    void SetPropUpper( const USHORT nU ) { nPropUpper = nU; }
    void SetPropLower( const USHORT nL ) { nPropLower = nL; }

    USHORT GetUpper() const { return nUpper; }
    USHORT GetLower() const { return nLower; }
    USHORT GetPropUpper() const { return nPropUpper; }
    USHORT GetPropLower() const { return nPropLower; }
};

inline SvxULSpaceItem &SvxULSpaceItem::operator=( const SvxULSpaceItem &rCpy )
{
    nUpper = rCpy.GetUpper();
    nLower = rCpy.GetLower();
    nPropUpper = rCpy.GetPropUpper();
    nPropLower = rCpy.GetPropLower();
    return *this;
}

inline void SvxULSpaceItem::SetUpper( const USHORT nU, const USHORT nProp )
{
    nUpper = USHORT((ULONG(nU) * nProp ) / 100); nPropUpper = nProp;
}
inline void SvxULSpaceItem::SetLower( const USHORT nL, const USHORT nProp )
{
    nLower = USHORT((ULONG(nL) * nProp ) / 100); nPropLower = nProp;
}

}//end of namespace binfilter
#endif

