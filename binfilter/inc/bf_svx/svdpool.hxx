/*************************************************************************
 *
 *  $RCSfile: svdpool.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:48 $
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

#ifndef _SVDPOOL_HXX
#define _SVDPOOL_HXX

#ifndef _XPOOL_HXX
#include <bf_svx/xpool.hxx>
#endif

#ifndef _SVDDEF_HXX
#include <bf_svx/svddef.hxx>
#endif

//-/#if SUPD>=366 //|| defined(JOEDEBUG)
//-/#define SDRDEFITEMCACHE
//-/#endif

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
//STRIP001  virtual SfxItemPresentation GetPresentation(const SfxPoolItem& rItem,
//STRIP001      SfxItemPresentation ePresentation,
//STRIP001      SfxMapUnit          ePresentationMetric,
//STRIP001      String&             rText,
//STRIP001         const IntlWrapper * pIntlWrapper
//STRIP001      = 0) const;

//STRIP001  static FASTBOOL TakeItemName(USHORT nWhich, String& rItemName);
    // liefert nur einen String, wenn die DLL mit DBG_UTIL uebersetzt ist
//STRIP001  static BOOL TakeWhichName(USHORT nWhich, ByteString& rItemName);
};

////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // _SVDPOOL_HXX

