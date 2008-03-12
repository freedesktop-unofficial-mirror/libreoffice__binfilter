/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: request.hxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 11:38:52 $
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
#ifndef _SFXREQUEST_HXX
#define _SFXREQUEST_HXX

#include <tools/rtti.hxx>

namespace binfilter {

class SfxPoolItem;
class SfxItemSet;


    class SfxRequest
{
public:
    static const SfxPoolItem* GetItem( const SfxItemSet*, USHORT nSlotId,
                                       FASTBOOL bDeep = FALSE,
                                       TypeId aType = 0 );
};

#define SFX_ITEMSET_ARG(pArgs, pItem, ItemType, nSlotId, bDeep) \
    const ItemType *pItem = (const ItemType*) \
        SfxRequest::GetItem( pArgs, nSlotId, bDeep, TYPE(ItemType) )

}//end of namespace binfilter
#endif
