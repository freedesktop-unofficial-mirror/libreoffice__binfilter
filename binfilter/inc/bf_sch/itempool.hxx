/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: itempool.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 11:47:16 $
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

#ifndef _SCH_ITEMPOOL_HXX
#define _SCH_ITEMPOOL_HXX

// auto strip #ifndef _SFXPOOLITEM_HXX //autogen
// auto strip #include <svtools/poolitem.hxx>
// auto strip #endif
#ifndef _SFXITEMPOOL_HXX //autogen
#include <svtools/itempool.hxx>
#endif
namespace binfilter {


/*************************************************************************
|*
|* Pool fuer zu speichernde Chart-Items
|*
\************************************************************************/

class SchItemPool: public SfxItemPool
{
private:
    SfxPoolItem**   ppPoolDefaults;
    SfxItemInfo*    pItemInfos;

public:
    SchItemPool();
//STRIP001  SchItemPool(const SchItemPool& rPool);
    virtual ~SchItemPool();

//STRIP001  virtual SfxItemPool* Clone() const;
//STRIP001  SfxMapUnit GetMetric(USHORT nWhich) const;
};

} //namespace binfilter
#endif // _SCH_ITEMPOOL_HXX


