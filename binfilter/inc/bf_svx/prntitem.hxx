/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: prntitem.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 03:54:36 $
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
#ifndef _SVX_PRNTITEM_HXX
#define _SVX_PRNTITEM_HXX

// include ---------------------------------------------------------------

#ifndef _SFXENUMITEM_HXX //autogen
#include <svtools/eitem.hxx>
#endif
namespace binfilter {

// class SvxPrintItem ----------------------------------------------------

/*
[Beschreibung]
Dieses Item beschreibt eine logische Variable "Drucken ja oder nein".
*/

class SvxPrintItem : public SfxBoolItem
{
public:
    TYPEINFO();

    SvxPrintItem( const USHORT nId = ITEMID_PRINT, const BOOL bPrt = TRUE );
    inline SvxPrintItem &operator=( const SvxPrintItem &rCpy );

    // "pure virtual Methoden" vom SfxPoolItem
    virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;
    virtual SfxPoolItem*    Create(SvStream &, USHORT) const;
    virtual SvStream&       Store(SvStream &, USHORT nItemVersion ) const;

};

inline SvxPrintItem::SvxPrintItem( const USHORT nId, const BOOL bPrt )
    : SfxBoolItem( nId, bPrt )
{}

inline SvxPrintItem &SvxPrintItem::operator=( const SvxPrintItem &rCpy )
{
    SetValue( rCpy.GetValue() );
    return *this;
}

}//end of namespace binfilter
#endif

