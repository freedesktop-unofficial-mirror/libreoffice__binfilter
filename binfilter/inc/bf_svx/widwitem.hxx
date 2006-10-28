/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: widwitem.hxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 04:24:04 $
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
#ifndef _SVX_WIDWITEM_HXX
#define _SVX_WIDWITEM_HXX

// include ---------------------------------------------------------------

#ifndef _SFXINTITEM_HXX //autogen
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

// class SvxWidowsItem ---------------------------------------------------

/*
[Beschreibung]
Dieses Item beschreibt die Anzahl der Zeilen fuer die Hurenkinderregelung.
*/

class SvxWidowsItem: public SfxByteItem
{
    friend SvStream & operator<<( SvStream & aS, SvxWidowsItem & );
public:
    TYPEINFO();

    SvxWidowsItem( const BYTE nL=0, const USHORT nId = ITEMID_WIDOWS );

    // "pure virtual Methoden" vom SfxPoolItem
    virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;
    virtual SfxPoolItem*    Create( SvStream &, USHORT ) const;


    inline SvxWidowsItem& operator=( const SvxWidowsItem& rWidows )
    {
        SetValue( rWidows.GetValue() );
        return *this;
    }
};

}//end of namespace binfilter
#endif

