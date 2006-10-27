/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: tabcont.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 16:26:18 $
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

#ifndef SC_TABCONT_HXX
#define SC_TABCONT_HXX

#ifndef _TABBAR_HXX //autogen wg. TabBar
#include <svtools/tabbar.hxx>
#endif

#ifndef _TRANSFER_HXX
#include <svtools/transfer.hxx>
#endif
namespace binfilter {


class ScViewData;

// ---------------------------------------------------------------------------

//  initial size
#define SC_TABBAR_DEFWIDTH      270


class ScTabControl : public TabBar, public DropTargetHelper, public DragSourceHelper
{
private:
    ScViewData*     pViewData;
    BOOL            bErrorShown;
    BOOL            bAddDown;
    USHORT          nTabSwitchId;
    long            nQueryCount;


    USHORT          GetMaxId() const;





public:
                    ScTabControl( Window* pParent, ScViewData* pData );
                    ~ScTabControl();

    void            UpdateStatus();
};



} //namespace binfilter
#endif
