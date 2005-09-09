/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: nlbkitem.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 13:56:46 $
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
#ifndef _SVX_NLBKITEM_HXX
#define _SVX_NLBKITEM_HXX

// include ---------------------------------------------------------------

#ifndef _SFXENUMITEM_HXX //autogen
#include <svtools/eitem.hxx>
#endif
namespace binfilter {

// class SvxNoLinebreakItem ----------------------------------------------

/*  [Beschreibung]

    PB: ???
*/

class SvxNoLinebreakItem : public SfxBoolItem
{
public:
    TYPEINFO();

    SvxNoLinebreakItem( const BOOL bBreak = TRUE,
                        const USHORT nId = ITEMID_NOLINEBREAK );

    // "pure virtual Methoden" vom SfxPoolItem
//STRIP001  virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;
//STRIP001  virtual SfxPoolItem*    Create(SvStream &, USHORT) const;
//STRIP001  virtual SvStream&       Store(SvStream &, USHORT nItemVersion) const;
//STRIP001
//STRIP001  virtual SfxItemPresentation GetPresentation( SfxItemPresentation ePres,
//STRIP001                                  SfxMapUnit eCoreMetric,
//STRIP001                                  SfxMapUnit ePresMetric,
//STRIP001                                     String &rText, const IntlWrapper * = 0 ) const;
//STRIP001
//STRIP001  inline SvxNoLinebreakItem& operator=(const SvxNoLinebreakItem& rLB)
//STRIP001      {
//STRIP001          SetValue( rLB.GetValue() );
//STRIP001          return *this;
//STRIP001      }
};

}//end of namespace binfilter
#endif

