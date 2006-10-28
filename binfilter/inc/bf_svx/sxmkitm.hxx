/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sxmkitm.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 04:16:48 $
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
#ifndef _SXMKITM_HXX
#define _SXMKITM_HXX

#ifndef _SVDDEF_HXX //autogen
#include <bf_svx/svddef.hxx>
#endif

#ifndef _SFXENUMITEM_HXX //autogen
#include <svtools/eitem.hxx>
#endif
namespace binfilter {

enum SdrMeasureKind     {SDRMEASURE_STD,SDRMEASURE_RADIUS}; // n.i.

//------------------------------
// class SdrMeasureKindItem (n.i.)
//------------------------------
class SdrMeasureKindItem: public SfxEnumItem {
public:
    TYPEINFO();
    SdrMeasureKindItem(SdrMeasureKind eKind=SDRMEASURE_STD): SfxEnumItem(SDRATTR_MEASUREKIND,eKind) {}
    SdrMeasureKindItem(SvStream& rIn)                      : SfxEnumItem(SDRATTR_MEASUREKIND,rIn)    {}
    virtual SfxPoolItem*   Clone(SfxItemPool* pPool=NULL) const;
    virtual SfxPoolItem*   Create(SvStream& rIn, USHORT nVer) const;
    virtual USHORT         GetValueCount() const; // { return 2; }
            SdrMeasureKind GetValue() const { return (SdrMeasureKind)SfxEnumItem::GetValue(); }


};

}//end of namespace binfilter
#endif
