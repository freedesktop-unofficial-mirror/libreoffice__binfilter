/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: pbinitem.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 14:09:25 $
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
#ifndef _SVX_PBINITEM_HXX
#define _SVX_PBINITEM_HXX

// include ---------------------------------------------------------------

#ifndef _SFXINTITEM_HXX //autogen
#include <svtools/intitem.hxx>
#endif
#ifndef _SVX_SVXIDS_HRC
#include <bf_svx/svxids.hrc>
#endif
namespace binfilter {

// define ----------------------------------------------------------------

#define PAPERBIN_PRINTER_SETTINGS   ((BYTE)0xFF)

// class SvxPaperBinItem -------------------------------------------------

/*  [Beschreibung]

    Dieses Item beschreibt die Auswahl eines Papierschachts des Drucker.
*/

class SvxPaperBinItem : public SfxByteItem
{
public:
    TYPEINFO();

    inline SvxPaperBinItem( const USHORT nId = ITEMID_PAPERBIN,
                            const BYTE nTray = PAPERBIN_PRINTER_SETTINGS );
    inline SvxPaperBinItem &operator=( const SvxPaperBinItem &rCpy );

    // "pure virtual Methoden" vom SfxPoolItem
    virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;
    virtual SfxPoolItem*    Create( SvStream &, USHORT ) const;
    virtual SvStream&       Store( SvStream &, USHORT nItemVersion ) const;
//STRIP001  virtual SfxItemPresentation GetPresentation( SfxItemPresentation ePres,
//STRIP001                                           SfxMapUnit eCoreMetric,
//STRIP001                                           SfxMapUnit ePresMetric,
//STRIP001                                              String &rText, const IntlWrapper * = 0 ) const;
};

inline SvxPaperBinItem::SvxPaperBinItem( const USHORT nId, const BYTE nT )
    : SfxByteItem( nId, nT )
{}

inline SvxPaperBinItem &SvxPaperBinItem::operator=(
    const SvxPaperBinItem &rCpy )
{
    SetValue( rCpy.GetValue() );
    return *this;
}

}//end of namespace binfilter
#endif

