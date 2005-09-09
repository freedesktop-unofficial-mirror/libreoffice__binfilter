/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: bolnitem.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 13:05:27 $
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
#ifndef _SVX_BOLNITEM_HXX
#define _SVX_BOLNITEM_HXX

// include ---------------------------------------------------------------

#ifndef _SFXPOOLITEM_HXX //autogen
#include <svtools/poolitem.hxx>
#endif
namespace binfilter {

// class SvxLineItem -----------------------------------------------------

/*
[Beschreibung]
Dieses Item transportiert eine SvxBorderLine.
*/

class SvxBorderLine;

class SvxLineItem : public SfxPoolItem
{
public:
    TYPEINFO();
//STRIP001
    SvxLineItem( const USHORT nId = ITEMID_LINE );
//STRIP001  SvxLineItem( const SvxLineItem& rCpy );
//STRIP001  ~SvxLineItem();
//STRIP001  SvxLineItem &operator=( const SvxLineItem& rLine );
//STRIP001
//STRIP001  virtual sal_Bool             QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;
//STRIP001  virtual sal_Bool             PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 );
    virtual int              operator==( const SfxPoolItem& ) const;
//STRIP001  virtual SfxItemPresentation GetPresentation( SfxItemPresentation ePres,
//STRIP001                                  SfxMapUnit eCoreMetric,
//STRIP001                                  SfxMapUnit ePresMetric,
//STRIP001                                     String &rText, const IntlWrapper * = 0 ) const;
//STRIP001
    virtual SfxPoolItem*     Clone( SfxItemPool *pPool = 0 ) const;
//STRIP001  virtual SfxPoolItem*     Create(SvStream &, USHORT) const;
//STRIP001  virtual SvStream&        Store(SvStream &, USHORT nItemVersion ) const;
//STRIP001  virtual int              ScaleMetrics( long nMult, long nDiv );
//STRIP001  virtual int              HasMetrics() const;
//STRIP001
//STRIP001  const   SvxBorderLine*  GetLine     () const { return pLine; }
    void                    SetLine     ( const SvxBorderLine *pNew );
//STRIP001
private:
    SvxBorderLine*  pLine;
};

}//end of namespace binfilter
#endif

