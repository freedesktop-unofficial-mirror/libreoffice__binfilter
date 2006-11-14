/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: e3ditem.hxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: ihi $ $Date: 2006-11-14 12:21:08 $
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

#ifndef _SVXE3DITEM_HXX
#define _SVXE3DITEM_HXX

#ifndef _SFXPOOLITEM_HXX //autogen
#include <svtools/poolitem.hxx>
#endif
#ifndef _VECTOR3D_HXX
#include <bf_goodies/vector3d.hxx>
#endif
class SvStream;
namespace binfilter {

#ifndef _SVXVECT3DITEM_HXX
#define _SVXVECT3DITEM_HXX


DBG_NAMEEX(SvxVector3DItem)//STRIP008

class SvxVector3DItem: public SfxPoolItem
{
    Vector3D                aVal;

public:
                            TYPEINFO();
                            SvxVector3DItem();
                            SvxVector3DItem( USHORT nWhich, const Vector3D& rVal );
                            SvxVector3DItem( const SvxVector3DItem& );
                            ~SvxVector3DItem() {
                                 DBG_DTOR(SvxVector3DItem, 0); }

    virtual int             operator==( const SfxPoolItem& ) const;
    virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;
    virtual SfxPoolItem*    Create(SvStream &, USHORT nVersion) const;
    virtual SvStream&       Store(SvStream &, USHORT nItemVersion ) const;

    virtual sal_Bool             QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;
    virtual sal_Bool             PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 );

    const Vector3D&         GetValue() const { return aVal; }
            void            SetValue( const Vector3D& rNewVal ) {
                                 DBG_ASSERT( GetRefCount() == 0, "SetValue() with pooled item" );
                                 aVal = rNewVal;
                             }

    virtual USHORT GetVersion (USHORT nFileFormatVersion) const;
};

#endif

}//end of namespace binfilter
#endif

