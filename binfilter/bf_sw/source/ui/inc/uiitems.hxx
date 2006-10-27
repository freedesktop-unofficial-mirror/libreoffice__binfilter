/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: uiitems.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 00:58:19 $
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
#ifndef _UIITEMS_HXX
#define _UIITEMS_HXX

#include "pagedesc.hxx"
#include "cmdid.h"
#ifndef _SFXINTITEM_HXX
#include <svtools/intitem.hxx>
#endif
class IntlWrapper;
namespace binfilter {
class SwNumRule;


/*--------------------------------------------------------------------
    Beschreibung: Container fuer FootNote
 --------------------------------------------------------------------*/
class SwPageFtnInfoItem : public SfxPoolItem
{
    SwPageFtnInfo aFtnInfo;

public:

    SwPageFtnInfoItem(const USHORT nId, SwPageFtnInfo& rInfo);
    SwPageFtnInfoItem(const SwPageFtnInfoItem& rItem );
    ~SwPageFtnInfoItem();

    virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;
    virtual int             operator==( const SfxPoolItem& ) const;

    virtual BOOL             QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;
    virtual BOOL             PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 );

    SwPageFtnInfo& GetPageFtnInfo()             { return aFtnInfo; }
    const SwPageFtnInfo& GetPageFtnInfo() const { return aFtnInfo; }
    void SetPageFtnInfo(SwPageFtnInfo& rInf)    { aFtnInfo = rInf; }
};

/*******************************************************************/





/*******************************************************************/






/* -----------------17.06.98 17:40-------------------
 *
 * --------------------------------------------------*/


} //namespace binfilter
#endif // _UIITEMS_HXX
