/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: tbinsert.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 20:21:12 $
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

//STRIP001  virtual void            Select( BOOL bMod1 = FALSE );

public:
    SFX_DECL_TOOLBOX_CONTROL();

    ScTbxInsertCtrl( USHORT nId, ToolBox& rTbx, SfxBindings& rBind );
    ~ScTbxInsertCtrl();

//STRIP001  virtual SfxPopupWindowType  GetPopupWindowType() const;
//STRIP001  virtual SfxPopupWindow*     CreatePopupWindow();
    virtual void                StateChanged( USHORT nSID,
                                              SfxItemState eState,
                                              const SfxPoolItem* pState );
};

//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------

//STRIP001 class ScTbxInsertPopup : public SfxPopupWindow
//STRIP001 {
//STRIP001  SfxToolBoxManager   aTbx;
//STRIP001  ResId               aRIdWinTemp;
//STRIP001  ResId               aRIdTbxTemp;
//STRIP001
//STRIP001  Link                aTbxClickHdl;
//STRIP001
//STRIP001  DECL_LINK( TbxSelectHdl, ToolBox* );
//STRIP001  DECL_LINK( TbxClickHdl, ToolBox* );
//STRIP001
//STRIP001 protected:
//STRIP001  virtual void        PopupModeEnd();
//STRIP001
//STRIP001 public:
//STRIP001  ScTbxInsertPopup( USHORT nId, WindowAlign eAlign,
//STRIP001                      const ResId& rRIdWin, const ResId& rRIdTbx,
//STRIP001                      SfxBindings& rBindings );
//STRIP001  ~ScTbxInsertPopup();
//STRIP001
//STRIP001  virtual SfxPopupWindow* Clone() const;
//STRIP001  void StartSelection();
//STRIP001 };



} //namespace binfilter
#endif

