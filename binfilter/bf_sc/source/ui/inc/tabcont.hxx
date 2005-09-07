/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: tabcont.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 20:18:26 $
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

//STRIP001  void            DoDrag( const Region& rRegion );

    USHORT          GetMaxId() const;
//STRIP001  USHORT          GetPrivatDropPos(const Point& rPos );

//STRIP001 protected:
//STRIP001  virtual void    Select();
//STRIP001  virtual void    Command( const CommandEvent& rCEvt );
//STRIP001  virtual void    MouseButtonDown( const MouseEvent& rMEvt );
//STRIP001  virtual void    MouseButtonUp( const MouseEvent& rMEvt );

//STRIP001  virtual sal_Int8 AcceptDrop( const AcceptDropEvent& rEvt );
//STRIP001  virtual sal_Int8 ExecuteDrop( const ExecuteDropEvent& rEvt );

//STRIP001  virtual void    StartDrag( sal_Int8 nAction, const Point& rPosPixel );

//STRIP001  virtual long    StartRenaming();
//STRIP001  virtual long    AllowRenaming();
//STRIP001  virtual void    EndRenaming();

public:
                    ScTabControl( Window* pParent, ScViewData* pData );
                    ~ScTabControl();

    void            UpdateStatus();
//STRIP001  void            ActivateView(BOOL bActivate);
};



} //namespace binfilter
#endif
