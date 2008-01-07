/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xpool.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: obo $ $Date: 2008-01-07 08:31:12 $
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

#ifndef _XPOOL_HXX
#define _XPOOL_HXX

#ifndef _SFXITEMPOOL_HXX //autogen
#include <svtools/itempool.hxx>
#endif
#ifndef _XDEF_HXX
#include <bf_svx/xdef.hxx>
#endif
namespace binfilter {

/*************************************************************************
|*
|* Klassendeklaration
|*
\************************************************************************/

class XOutdevItemPool: public SfxItemPool
{
protected:
    SfxPoolItem**   ppPoolDefaults;
    SfxItemInfo*    pItemInfos;
/*    USHORT*         pVersion1Map;
    USHORT*         pVersion2Map;
    USHORT*         pVersion3Map;
    USHORT*         pVersion4Map;*/
    USHORT          nStart, nEnd;

private:
    void Ctor(SfxItemPool* pMaster, USHORT nAttrStart, USHORT nAttrEnd);

public:
    // Kontstruktion des Pools als MasterPool
    XOutdevItemPool(USHORT nAttrStart = XATTR_START,
                    USHORT nAttrEnd = XATTR_END,
                    FASTBOOL bLoadRefCounts = TRUE);

    // Damit meine SetItems mit dem MasterPool konstruiert werden koennen.
    // Der SdrItemPool wird dabei automatisch als Secondary an den
    // uebergebenen MasterPool bzw. an's Ende einer bestehenden Pool-Kette
    // angehaengt.
    XOutdevItemPool(SfxItemPool* pMaster,
                    USHORT nAttrStart = XATTR_START,
                    USHORT nAttrEnd = XATTR_END,
                    FASTBOOL bLoadRefCounts = TRUE);

    XOutdevItemPool(const XOutdevItemPool& rPool);

    virtual SfxItemPool* Clone() const;

    ~XOutdevItemPool();
};

}//end of namespace binfilter
#endif      // _XPOOL_HXX
