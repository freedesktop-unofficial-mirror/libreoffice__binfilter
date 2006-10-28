/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sxmtpitm.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 04:16:58 $
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
#ifndef _SXMTPITM_HXX
#define _SXMTPITM_HXX

#ifndef _SVDDEF_HXX //autogen
#include <bf_svx/svddef.hxx>
#endif

#ifndef _SFXENUMITEM_HXX //autogen
#include <svtools/eitem.hxx>
#endif
namespace binfilter {

enum SdrMeasureTextHPos {SDRMEASURE_TEXTHAUTO,SDRMEASURE_TEXTLEFTOUTSIDE,SDRMEASURE_TEXTINSIDE,SDRMEASURE_TEXTRIGHTOUTSIDE};
enum SdrMeasureTextVPos {SDRMEASURE_TEXTVAUTO,SDRMEASURE_ABOVE,SDRMEASURETEXT_BREAKEDLINE,SDRMEASURE_BELOW,SDRMEASURETEXT_VERTICALCENTERED};

//------------------------------
// class SdrMeasureTextHPosItem
//------------------------------
class SdrMeasureTextHPosItem: public SfxEnumItem {
public:
    TYPEINFO();
    SdrMeasureTextHPosItem(SdrMeasureTextHPos ePos=SDRMEASURE_TEXTHAUTO): SfxEnumItem(SDRATTR_MEASURETEXTHPOS,ePos) {}
    SdrMeasureTextHPosItem(SvStream& rIn)                               : SfxEnumItem(SDRATTR_MEASURETEXTHPOS,rIn)    {}
    virtual SfxPoolItem*   Clone(SfxItemPool* pPool=NULL) const;
    virtual SfxPoolItem*   Create(SvStream& rIn, USHORT nVer) const;
    virtual USHORT         GetValueCount() const; // { return 4; }
            SdrMeasureTextHPos GetValue() const { return (SdrMeasureTextHPos)SfxEnumItem::GetValue(); }


};

//------------------------------
// class SdrMeasureTextVPosItem
//------------------------------
class SdrMeasureTextVPosItem: public SfxEnumItem {
public:
    TYPEINFO();
    SdrMeasureTextVPosItem(SdrMeasureTextVPos ePos=SDRMEASURE_TEXTVAUTO): SfxEnumItem(SDRATTR_MEASURETEXTVPOS,ePos) {}
    SdrMeasureTextVPosItem(SvStream& rIn)                               : SfxEnumItem(SDRATTR_MEASURETEXTVPOS,rIn)    {}
    virtual SfxPoolItem*   Clone(SfxItemPool* pPool=NULL) const;
    virtual SfxPoolItem*   Create(SvStream& rIn, USHORT nVer) const;
    virtual USHORT         GetValueCount() const; // { return 5; }
            SdrMeasureTextVPos GetValue() const { return (SdrMeasureTextVPos)SfxEnumItem::GetValue(); }


};

}//end of namespace binfilter
#endif
