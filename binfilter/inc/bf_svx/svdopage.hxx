/*************************************************************************
 *
 *  $RCSfile: svdopage.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:42 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/

#ifndef _SVDOPAGE_HXX
#define _SVDOPAGE_HXX

#ifndef _SVDOBJ_HXX
#include <bf_svx/svdobj.hxx>
#endif

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
//STRIP001  virtual void TakeObjInfo(SdrObjTransformInfoRec& rInfo) const;
//STRIP001  virtual FASTBOOL Paint(ExtOutputDevice& rOut, const SdrPaintInfoRec& rInfoRec) const;
//STRIP001  virtual void operator=(const SdrObject& rObj);

//STRIP001  virtual void TakeObjNameSingul(String& rName) const;
//STRIP001  virtual void TakeObjNamePlural(String& rName) const;

    virtual const Rectangle& GetBoundRect() const;
    virtual const Rectangle& GetSnapRect() const;
    virtual const Rectangle& GetLogicRect() const;
    virtual void NbcSetSnapRect(const Rectangle& rRect);
    virtual void NbcSetLogicRect(const Rectangle& rRect);
//STRIP001  virtual void TakeXorPoly(XPolyPolygon& rPoly, FASTBOOL bDetail) const;
//STRIP001  virtual void TakeContour(XPolyPolygon& rXPoly, SdrContourType eType) const;
    virtual void WriteData(SvStream& rOut) const;
    virtual void ReadData(const SdrObjIOHeader& rHead, SvStream& rIn);

    // ItemSet access
    virtual SfxItemSet* CreateNewItemSet(SfxItemPool& rPool);
    virtual const SfxItemSet& GetItemSet() const;
    // #86481# simply ignore item setting on page objects
    virtual void ItemChange(const sal_uInt16 nWhich, const SfxPoolItem* pNewItem = 0);
};

////////////////////////////////////////////////////////////////////////////////////////////////////

#endif //_SVDOPAGE_HXX

