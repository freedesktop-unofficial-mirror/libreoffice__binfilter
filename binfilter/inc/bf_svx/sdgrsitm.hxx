/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sdgrsitm.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 13:04:11 $
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

#ifndef _SDGRSITM_HXX
#define _SDGRSITM_HXX

#ifndef _SVDDEF_HXX
#include <bf_svx/svddef.hxx>
#endif
#ifndef _SFXITEMSET_HXX
#include <bf_svtools/itemset.hxx>
#endif
#ifndef _SFXPOOLITEM_HXX
#include <bf_svtools/poolitem.hxx>
#endif
namespace binfilter {

// ------------------
// - SdrGrafSetItem -
// ------------------

class SdrGrafSetItem : public SfxSetItem
{
public:

    TYPEINFO();

    SdrGrafSetItem( SfxItemSet* pItemSet ) : SfxSetItem( SDRATTRSET_GRAF, pItemSet ) {}
    SdrGrafSetItem( SfxItemPool* pItemPool ) : SfxSetItem( SDRATTRSET_GRAF, new SfxItemSet( *pItemPool, SDRATTR_GRAF_FIRST, SDRATTR_GRAF_LAST ) ) {}
    SdrGrafSetItem( const SdrGrafSetItem& rAttr, SfxItemPool* pItemPool = NULL ) : SfxSetItem( rAttr, pItemPool ) {}
    virtual SfxPoolItem* Clone( SfxItemPool* pToPool ) const;
    virtual SfxPoolItem* Create( SvStream& rStream, USHORT nVersion ) const;
};

}//end of namespace binfilter
#endif // _SDGRSITM_HXX
