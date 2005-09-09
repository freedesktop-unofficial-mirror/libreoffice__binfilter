/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: itemdata.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 13:41:50 $
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
#ifndef _SVX_ITEMDATA_HXX
#define _SVX_ITEMDATA_HXX

#ifndef _SHL_HXX //autogen
#include <tools/shl.hxx>
#endif
#ifndef _PSTM_HXX //autogen
#include <tools/pstm.hxx>
#endif
namespace binfilter {

class SvxGlobalItemData
{
private:
    SvClassManager* pClassMgr;

public:
                    SvxGlobalItemData();
                    ~SvxGlobalItemData()    { delete pClassMgr; }

    SvClassManager& GetClassManager();
};

#define ITEMDATA() (*(SvxGlobalItemData**)GetAppData( BF_SHL_ITEM ) )

inline SvxGlobalItemData::SvxGlobalItemData()
{
    pClassMgr = 0;
    *(SvxGlobalItemData**)GetAppData(BF_SHL_ITEM) = this;
}

inline SvClassManager& SvxGlobalItemData::GetClassManager()
{
    if ( !pClassMgr )
        pClassMgr = new SvClassManager;
    return *pClassMgr;
}

}//end of namespace binfilter
#endif

