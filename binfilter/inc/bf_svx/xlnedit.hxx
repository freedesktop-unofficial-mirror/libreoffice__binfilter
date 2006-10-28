/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xlnedit.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 04:30:17 $
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

#ifndef _SVX_XLNEDIT_HXX
#define _SVX_XLNEDIT_HXX

#ifndef _XPOLY_HXX //autogen
#include <bf_svx/xpoly.hxx>
#endif
#ifndef _SVX_XIT_HXX //autogen
#include <bf_svx/xit.hxx>
#endif
namespace binfilter {

class SdrModel;

//----------------------
// class XLineEndItem
//----------------------
class XLineEndItem : public NameOrIndex
{
    XPolygon    aXPolygon;

public:
            TYPEINFO();
            XLineEndItem(long nIndex = -1);
            XLineEndItem(const String& rName, const XPolygon& rXPolygon);
            XLineEndItem(SfxItemPool* pPool, const XPolygon& rXPolygon);
            XLineEndItem(SfxItemPool* pPool );
            XLineEndItem(const XLineEndItem& rItem);
            XLineEndItem(SvStream& rIn);

    virtual int             operator==(const SfxPoolItem& rItem) const;
    virtual SfxPoolItem*    Clone(SfxItemPool* pPool = 0) const;
    virtual SfxPoolItem*    Create(SvStream& rIn, USHORT nVer) const;
    virtual SvStream&       Store(SvStream& rOut, USHORT nItemVersion ) const;

    virtual sal_Bool             QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;
    virtual sal_Bool             PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 );


    const XPolygon& GetValue(const XLineEndTable* pTable = 0) const;
    void            SetValue(const XPolygon& rXPolygon) { aXPolygon = rXPolygon; Detach(); }

    XLineEndItem* checkForUniqueItem( SdrModel* pModel ) const;
};

}//end of namespace binfilter
#endif
