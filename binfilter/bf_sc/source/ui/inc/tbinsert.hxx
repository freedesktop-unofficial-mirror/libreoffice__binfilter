/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: tbinsert.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 16:28:09 $
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

#ifndef SC_TBINSERT_HXX
#define SC_TBINSERT_HXX

#ifndef _SFXTBXCTRL_HXX //autogen
#include <bf_sfx2/tbxctrl.hxx>
#endif

#ifndef _SFXTBXMGR_HXX //autogen
#include <bf_sfx2/tbxmgr.hxx>
#endif
namespace binfilter {

//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------

class ScTbxInsertCtrl : public SfxToolBoxControl
{
    USHORT                  nLastSlotId;


public:
    SFX_DECL_TOOLBOX_CONTROL();

    ScTbxInsertCtrl( USHORT nId, ToolBox& rTbx, SfxBindings& rBind );
    ~ScTbxInsertCtrl();

    virtual void                StateChanged( USHORT nSID,
                                              SfxItemState eState,
                                              const SfxPoolItem* pState );
};

//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------




} //namespace binfilter
#endif

