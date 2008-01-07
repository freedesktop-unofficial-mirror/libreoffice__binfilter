/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svdpool.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: obo $ $Date: 2008-01-07 08:29:54 $
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

#ifndef _SVDPOOL_HXX
#define _SVDPOOL_HXX

#ifndef _XPOOL_HXX
#include <bf_svx/xpool.hxx>
#endif

#ifndef _SVDDEF_HXX
#include <bf_svx/svddef.hxx>
#endif
namespace binfilter {

class XLineAttrSetItem;
class XFillAttrSetItem;
class XTextAttrSetItem;
class SdrShadowSetItem;
class SdrOutlinerSetItem;
class SdrMiscSetItem;

////////////////////////////////////////////////////////////////////////////////////////////////////

class SdrItemPool: public XOutdevItemPool {
//-/#ifdef SDRDEFITEMCACHE
//-/friend class SdrAttrObj;
//-/    const XLineAttrSetItem*   pDefLineAttr;
//-/    const XFillAttrSetItem*   pDefFillAttr;
//-/    const XTextAttrSetItem*   pDefTextAttr;
//-/    const SdrShadowSetItem*   pDefShadAttr;
//-/    const SdrOutlinerSetItem* pDefOutlAttr;
//-/    const SdrMiscSetItem*     pDefMiscAttr;
//-/    const XLineAttrSetItem*   pDefTextFrameLineAttr;
//-/    const XFillAttrSetItem*   pDefTextFrameFillAttr;
//-/    const XTextAttrSetItem*   pDefTextFrameTextAttr;
//-/    const SdrShadowSetItem*   pDefTextFrameShadAttr;
//-/    const SdrOutlinerSetItem* pDefTextFrameOutlAttr;
//-/    const SdrMiscSetItem*     pDefTextFrameMiscAttr;
//-/#endif
private:
    void Ctor(SfxItemPool* pMaster, USHORT nAttrStart, USHORT nAttrEnd);
//-/    void ImpMakeDefItems();
public:
    // Kontstruktion des Pools als MasterPool
    SdrItemPool(USHORT nAttrStart=SDRATTR_START, USHORT nAttrEnd=SDRATTR_END,
        FASTBOOL bLoadRefCounts = TRUE);

    // Damit meine SetItems mit dem MasterPool konstruiert werden koennen.
    // Der SdrItemPool wird dabei automatisch als Secondary an den
    // uebergebenen MasterPool bzw. an's Ende einer bestehenden Pool-Kette
    // angehaengt.
    SdrItemPool(SfxItemPool* pMaster, USHORT nAttrStart=SDRATTR_START, USHORT nAttrEnd=SDRATTR_END,
        FASTBOOL bLoadRefCounts = TRUE);

    SdrItemPool(const SdrItemPool& rPool);
    virtual ~SdrItemPool();
    virtual SfxItemPool* Clone() const;

    // liefert nur einen String, wenn die DLL mit DBG_UTIL uebersetzt ist
};

////////////////////////////////////////////////////////////////////////////////////////////////////

}//end of namespace binfilter
#endif // _SVDPOOL_HXX

