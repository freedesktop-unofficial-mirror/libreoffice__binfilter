/*************************************************************************
 *
 *  $RCSfile: tbxform.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:22:01 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/
#ifndef _SVX_TBXFORM_HXX
#define _SVX_TBXFORM_HXX

#ifndef _SFXTBXCTRL_HXX //autogen
#include <bf_sfx2/tbxctrl.hxx>
#endif

#ifndef _SFXTBXMGR_HXX //autogen
#include <bf_sfx2/tbxmgr.hxx>
#endif

#ifndef _SV_FIELD_HXX //autogen
#include <vcl/field.hxx>
#endif

#ifndef _SV_DIALOG_HXX //autogen
#include <vcl/dialog.hxx>
#endif

#ifndef _SV_BUTTON_HXX //autogen
#include <vcl/button.hxx>
#endif

//========================================================================

//STRIP001 class FmInputRecordNoDialog : public ModalDialog
//STRIP001 {
//STRIP001 public:
//STRIP001  FixedText       m_aLabel;
//STRIP001  NumericField    m_aRecordNo;
//STRIP001  OKButton        m_aOk;
//STRIP001  CancelButton    m_aCancel;
//STRIP001
//STRIP001 public:
//STRIP001  FmInputRecordNoDialog(Window * pParent);
//STRIP001
//STRIP001  void SetValue(double dNew) { m_aRecordNo.SetValue(dNew); }
//STRIP001  long GetValue() const { return m_aRecordNo.GetValue(); }
//STRIP001 };

//========================================================================
//STRIP001 class SvxFmAbsRecWin : public NumericField
//STRIP001 {
//STRIP001  SfxToolBoxControl*  m_pController;
//STRIP001      // for invalidating our content whe losing the focus
//STRIP001 public:
//STRIP001  SvxFmAbsRecWin( Window* _pParent, SfxToolBoxControl* _pController );
//STRIP001  ~SvxFmAbsRecWin();
//STRIP001
//STRIP001  virtual void KeyInput( const KeyEvent& rKeyEvt );
//STRIP001  virtual void LoseFocus();
//STRIP001
//STRIP001 protected:
//STRIP001  virtual void FirePosition( sal_Bool _bForce );
//STRIP001 };


//========================================================================
//STRIP001 class SvxFmConfigWin : public SfxPopupWindow
//STRIP001 {
//STRIP001 private:
//STRIP001  SfxToolBoxManager aTbx;
//STRIP001  Link aSelectLink;
//STRIP001
//STRIP001  DECL_LINK( TbxSelectHdl, ToolBox* );
//STRIP001
//STRIP001 public:
//STRIP001  SvxFmConfigWin( USHORT nId, ResId aRIdWin, ResId aRIdTbx, SfxBindings& rBindings );
//STRIP001  ~SvxFmConfigWin();
//STRIP001
//STRIP001  void            StartSelection()
//STRIP001                      { aTbx.GetToolBox().StartSelection(); }
//STRIP001  void            Update();
//STRIP001  virtual void    PopupModeEnd();
//STRIP001 };


//========================================================================
class SvxFmTbxCtlConfig : public SfxToolBoxControl
{
private:
    UINT16 nLastSlot;

public:
    SFX_DECL_TOOLBOX_CONTROL();

    SvxFmTbxCtlConfig( USHORT nId, ToolBox& rTbx, SfxBindings& );
    ~SvxFmTbxCtlConfig() {}

//STRIP001  virtual void                Select( USHORT nModifier );
    virtual void                StateChanged( USHORT nSID, SfxItemState eState,
                                              const SfxPoolItem* pState );
//STRIP001  virtual SfxPopupWindowType  GetPopupWindowType() const;
//STRIP001  virtual SfxPopupWindow*     CreatePopupWindow();
};

//========================================================================
class FixedText;
class SvxFmTbxCtlAbsRec : public SfxToolBoxControl
{
public:
    SFX_DECL_TOOLBOX_CONTROL();

    SvxFmTbxCtlAbsRec( USHORT nId, ToolBox& rTbx, SfxBindings& rBindings );
//STRIP001  ~SvxFmTbxCtlAbsRec();

//STRIP001  virtual Window* CreateItemWindow( Window* pParent );

//STRIP001  virtual void    StateChanged( USHORT nSID, SfxItemState eState,
//STRIP001                                const SfxPoolItem* pState );
};

//========================================================================
class SvxFmTbxCtlRecText : public SfxToolBoxControl
{
public:
    SFX_DECL_TOOLBOX_CONTROL();

    SvxFmTbxCtlRecText( USHORT nId, ToolBox& rTbx, SfxBindings& rBindings );
//STRIP001  ~SvxFmTbxCtlRecText();
//STRIP001
//STRIP001  virtual Window* CreateItemWindow( Window* pParent );
};

//========================================================================
class SvxFmTbxCtlRecFromText : public SfxToolBoxControl
{
public:
    SFX_DECL_TOOLBOX_CONTROL();

    SvxFmTbxCtlRecFromText( USHORT nId, ToolBox& rTbx, SfxBindings& rBindings );
//STRIP001  ~SvxFmTbxCtlRecFromText();
//STRIP001
//STRIP001  virtual Window* CreateItemWindow( Window* pParent );
};

//========================================================================
class SvxFmTbxCtlRecTotal : public SfxToolBoxControl
{
    FixedText* pFixedText;

public:
    SFX_DECL_TOOLBOX_CONTROL();

    SvxFmTbxCtlRecTotal( USHORT nId, ToolBox& rTbx, SfxBindings& rBindings );
//STRIP001  ~SvxFmTbxCtlRecTotal();
//STRIP001
//STRIP001  virtual Window* CreateItemWindow( Window* pParent );
//STRIP001  virtual void    StateChanged( USHORT nSID, SfxItemState eState,
//STRIP001                                const SfxPoolItem* pState );
};

/*
//========================================================================
class SvxFmTbxCtlFilterText : public SfxToolBoxControl
{
    FixedText* pFixedText;
    XubString aText;
public:
    SFX_DECL_TOOLBOX_CONTROL();

    SvxFmTbxCtlFilterText( USHORT nId, ToolBox& rTbx, SfxBindings& rBindings );
    ~SvxFmTbxCtlFilterText();

    virtual Window* CreateItemWindow( Window* pParent );
    virtual void    StateChanged( USHORT nSID, SfxItemState eState,
                                  const SfxPoolItem* pState );
};
*/

//========================================================================
class SvxFmTbxNextRec : public SfxToolBoxControl
{
public:
    SFX_DECL_TOOLBOX_CONTROL();
    SvxFmTbxNextRec( USHORT nId, ToolBox& rTbx, SfxBindings& rBindings );
};

//========================================================================
class SvxFmTbxPrevRec : public SfxToolBoxControl
{
public:
    SFX_DECL_TOOLBOX_CONTROL();
    SvxFmTbxPrevRec( USHORT nId, ToolBox& rTbx, SfxBindings& rBindings );
};


#endif

