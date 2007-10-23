/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: ipmenu.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: vg $ $Date: 2007-10-23 13:43:16 $
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

#ifndef _IPMENU_HXX
#define _IPMENU_HXX

#ifndef _MENU_HXX //autogen
#include <vcl/menu.hxx>
#endif

#ifndef INCLUDED_SO3DLLAPI_H
#include "bf_so3/so3dllapi.h"
#endif

/********************** SvInPlaceMenuBar *********************************
*************************************************************************/
class SO3_DLLPUBLIC SvInPlaceMenuBar : public MenuBar
{
private:
    USHORT nCount0, nCount1, nCount2;
    using       Menu::InsertItem;
    SO3_DLLPRIVATE void        InsertItem( Menu & rFromMenu, USHORT nPos );
public:
                SvInPlaceMenuBar( const ResId & rId );
                SvInPlaceMenuBar( MenuBar * pBar,
                                  USHORT nPos0 = 0, USHORT nCount0 = 0,
                                  USHORT nPos1 = 0, USHORT nCount1 = 0,
                                  USHORT nPos2 = 0, USHORT nCount2 = 0 );
                ~SvInPlaceMenuBar();
    SvInPlaceMenuBar * GetBlocks( USHORT * p0, USHORT * p1, USHORT * p2 )
                {
                    *p0 = nCount0;
                    *p1 = nCount1;
                    *p2 = nCount2;
                    return this;
                }
    void        PushSelectHdl( const Link & rLink );
    void        PopSelectHdl();
    void        PushActivateHdl( const Link & rLink );
    void        PopActivateHdl();
    void        PushDeactivateHdl( const Link & rLink );
    void        PopDeactivateHdl();
    void        PushHighlightHdl( const Link & rLink );
    void        PopHighlightHdl();

    USHORT      GetCount0() const { return nCount0; }
    USHORT      GetCount1() const { return nCount1; }
    USHORT      GetCount2() const { return nCount2; }
};


#endif // _IPMENU_HXX
