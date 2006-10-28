/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svdopage.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 04:09:08 $
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

#ifndef _SVDOPAGE_HXX
#define _SVDOPAGE_HXX

#ifndef _SVDOBJ_HXX
#include <bf_svx/svdobj.hxx>
#endif
namespace binfilter {

////////////////////////////////////////////////////////////////////////////////////////////////////

class SdrPageObj : public SdrObject
{
    SfxItemSet*             mpPageItemSet;
    sal_uInt16              nPageNum;
    BOOL                    bPainting;  // Verriegelungsflag
    BOOL                    bNotifying; // Verriegelungsflag

protected:
    virtual void SFX_NOTIFY(SfxBroadcaster& rBC, const TypeId& rBCType, const SfxHint& rHint, const TypeId& rHintType);

public:
    TYPEINFO();
    SdrPageObj(USHORT nNewPageNum=0);
    SdrPageObj(const Rectangle& rRect, USHORT nNewPageNum=0);
    ~SdrPageObj();

    virtual void SetModel(SdrModel* pNewModel);
    USHORT GetPageNum() const { return nPageNum; }
    void SetPageNum(USHORT nNewPageNum)
        { NbcSetPageNum(nNewPageNum); SetChanged(); SendRepaintBroadcast(GetBoundRect()); }
    void NbcSetPageNum(USHORT nNewPageNum) { nPageNum=nNewPageNum; }

    virtual UINT16 GetObjIdentifier() const;


    virtual const Rectangle& GetBoundRect() const;
    virtual const Rectangle& GetSnapRect() const;
    virtual const Rectangle& GetLogicRect() const;
    virtual void NbcSetSnapRect(const Rectangle& rRect);
    virtual void NbcSetLogicRect(const Rectangle& rRect);
    virtual void WriteData(SvStream& rOut) const;
    virtual void ReadData(const SdrObjIOHeader& rHead, SvStream& rIn);

    // ItemSet access
    virtual SfxItemSet* CreateNewItemSet(SfxItemPool& rPool);
    virtual const SfxItemSet& GetItemSet() const;
    // #86481# simply ignore item setting on page objects
    virtual void ItemChange(const sal_uInt16 nWhich, const SfxPoolItem* pNewItem = 0);
};

////////////////////////////////////////////////////////////////////////////////////////////////////

}//end of namespace binfilter
#endif //_SVDOPAGE_HXX

