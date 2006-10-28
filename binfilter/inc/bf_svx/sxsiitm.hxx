/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sxsiitm.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 04:17:22 $
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
#ifndef _SXSIITM_HXX
#define _SXSIITM_HXX

#ifndef _SXFIITM_HXX
#include <bf_svx/sxfiitm.hxx>
#endif
namespace binfilter {

class SdrScaleItem: public SdrFractionItem {
public:
    TYPEINFO();
    SdrScaleItem(USHORT nId=0): SdrFractionItem(nId,Fraction(1,1)) {}
    SdrScaleItem(USHORT nId, const Fraction& rVal): SdrFractionItem(nId,rVal) {}
    SdrScaleItem(USHORT nId, SvStream& rIn): SdrFractionItem(nId,rIn) {}
    virtual SfxPoolItem*     Create(SvStream&, USHORT nVer) const;
    virtual SfxPoolItem*     Clone(SfxItemPool *pPool=NULL) const;
};

}//end of namespace binfilter
#endif
