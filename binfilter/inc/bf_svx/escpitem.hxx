/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: escpitem.hxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 03:31:28 $
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
#ifndef _SVX_ESCPITEM_HXX
#define _SVX_ESCPITEM_HXX

// include ---------------------------------------------------------------

#ifndef _SFXENUMITEM_HXX //autogen
#include <svtools/eitem.hxx>
#endif
#ifndef _SVX_SVXENUM_HXX
#include <bf_svx/svxenum.hxx>
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
// class SvxEscapementItem -----------------------------------------------

#define DFLT_ESC_SUPER   33     // 1/3
#define DFLT_ESC_SUB    -33     // auch 1/3 fr"uher 8/100
#define DFLT_ESC_PROP    58
#define DFLT_ESC_AUTO_SUPER 101
#define DFLT_ESC_AUTO_SUB  -101

/*  [Beschreibung]

    Dieses Item beschreibt die Schrift-Position.
*/

class SvxEscapementItem : public SfxEnumItemInterface
{
    short nEsc;
    BYTE  nProp;
public:
    TYPEINFO();

    SvxEscapementItem( const USHORT nId = ITEMID_ESCAPEMENT );
    SvxEscapementItem( const short nEsc, const BYTE nProp,
                   const USHORT nId = ITEMID_ESCAPEMENT  );

    // "pure virtual Methoden" vom SfxPoolItem
    virtual int              operator==( const SfxPoolItem& ) const;

    virtual sal_Bool             QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;
    virtual sal_Bool             PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 );

    virtual SfxPoolItem*     Clone( SfxItemPool *pPool = 0 ) const;
    virtual SfxPoolItem*     Create(SvStream &, USHORT) const;
    virtual SvStream&        Store(SvStream &, USHORT nItemVersion) const;

    inline void SetEscapement( const SvxEscapement eNew )
    {
        if( SVX_ESCAPEMENT_OFF == eNew )
            nEsc = 0, nProp = 100;
        else
            if( SVX_ESCAPEMENT_SUPERSCRIPT == eNew )
                nEsc = DFLT_ESC_SUPER, nProp = DFLT_ESC_PROP;
            else
                nEsc = DFLT_ESC_SUB, nProp = DFLT_ESC_PROP;
    }

    inline short &GetEsc() { return nEsc; }
    inline short GetEsc() const { return nEsc; }

    inline BYTE &GetProp() { return nProp; }
    inline BYTE GetProp() const { return nProp; }

    inline SvxEscapementItem& operator=(const SvxEscapementItem& rEsc)
        {
            nEsc  = rEsc.GetEsc();
            nProp = rEsc.GetProp();
            return *this;
        }

    virtual USHORT          GetValueCount() const;
    virtual USHORT          GetEnumValue() const;
    virtual void            SetEnumValue( USHORT nNewVal );
};

}//end of namespace binfilter
#endif

