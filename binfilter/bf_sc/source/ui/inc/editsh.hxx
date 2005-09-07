/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: editsh.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 19:45:30 $
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

#ifndef SC_EDITSH_HXX
#define SC_EDITSH_HXX

#ifndef _SFX_SHELL_HXX //autogen
#include <bf_sfx2/shell.hxx>
#endif
#ifndef _SFXMODULE_HXX //autogen
#include <bf_sfx2/module.hxx>
#endif
#ifndef _LINK_HXX
#include <tools/link.hxx>
#endif

#include "shellids.hxx"
class TransferableDataHelper;
class TransferableClipboardListener;
namespace binfilter {

class EditView;
class ScViewData;
class ScInputHandler;
class SvxURLField;

class ScEditShell : public SfxShell
{
//STRIP001 private:
//STRIP001  EditView*   pEditView;
//STRIP001  ScViewData* pViewData;
//STRIP001  TransferableClipboardListener* pClipEvtLstnr;
//STRIP001  BOOL        bPastePossible;
//STRIP001  BOOL        bIsInsertMode;

//STRIP001  const SvxURLField* GetURLField();
//STRIP001  ScInputHandler* GetMyInputHdl();
//STRIP001
//STRIP001  DECL_LINK( ClipboardChanged, TransferableDataHelper* );

public:
//STRIP001  TYPEINFO();
    SFX_DECL_INTERFACE(SCID_EDIT_SHELL);

    ScEditShell(EditView* pView, ScViewData* pData){DBG_BF_ASSERT(0, "STRIP");} //STRIP001 ScEditShell(EditView* pView, ScViewData* pData);
//STRIP001                  ~ScEditShell();
//STRIP001
//STRIP001  void    SetEditView(EditView* pView);
//STRIP001
    void    Execute(SfxRequest& rReq){DBG_BF_ASSERT(0, "STRIP");} //STRIP001 //STRIP001     void    Execute(SfxRequest& rReq);
    void    ExecuteTrans(SfxRequest& rReq){DBG_BF_ASSERT(0, "STRIP");} //STRIP001 //STRIP001    void    ExecuteTrans(SfxRequest& rReq);
    void    GetState(SfxItemSet &rSet){DBG_BF_ASSERT(0, "STRIP");} //STRIP001 //STRIP001    void    GetState(SfxItemSet &rSet);
    void    GetClipState(SfxItemSet& rSet){DBG_BF_ASSERT(0, "STRIP");} //STRIP001 //STRIP001    void    GetClipState(SfxItemSet& rSet);
//STRIP001
    void    ExecuteAttr(SfxRequest& rReq){DBG_BF_ASSERT(0, "STRIP");} //STRIP001 //STRIP001     void    ExecuteAttr(SfxRequest& rReq);
    void    GetAttrState(SfxItemSet &rSet){DBG_BF_ASSERT(0, "STRIP");} //STRIP001 //STRIP001    void    GetAttrState(SfxItemSet &rSet);
//STRIP001
    void    ExecuteUndo(SfxRequest& rReq){DBG_BF_ASSERT(0, "STRIP");} //STRIP001 //STRIP001     void    ExecuteUndo(SfxRequest& rReq);
    void    GetUndoState(SfxItemSet &rSet){DBG_BF_ASSERT(0, "STRIP");} //STRIP001 //STRIP001    void    GetUndoState(SfxItemSet &rSet);
//STRIP001
//STRIP001  String  GetSelectionText( BOOL bWholeWord );
};



} //namespace binfilter
#endif

