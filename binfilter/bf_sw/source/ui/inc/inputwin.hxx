/*************************************************************************
 *
 *  $RCSfile: inputwin.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:55:20 $
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
#ifndef SW_INPUTWIN_HXX
#define SW_INPUTWIN_HXX


#ifndef _MENU_HXX //autogen
#include <vcl/menu.hxx>
#endif
#ifndef _SFX_CHILDWIN_HXX //autogen
#include <bf_sfx2/childwin.hxx>
#endif
#ifndef _TOOLBOX_HXX //autogen
#include <vcl/toolbox.hxx>
#endif
#ifndef _EDIT_HXX //autogen
#include <vcl/edit.hxx>
#endif
namespace binfilter {

class SwFldMgr;
class SwWrtShell;
class SwView;
class SfxDispatcher;

//========================================================================
class InputEdit : public Edit
{
public:
                    InputEdit(Window* pParent, WinBits nStyle) :
                        Edit(pParent , nStyle){}
//STRIP001
//STRIP001  void            UpdateRange(const String& aSel,
//STRIP001                              const String& aTblName );
//STRIP001
protected:
//STRIP001  virtual void    KeyInput( const KeyEvent&  );
};

//========================================================================

//STRIP001 class SwInputWindow : public ToolBox
//STRIP001 {
//STRIP001 friend class InputEdit;
//STRIP001
//STRIP001  Edit            aPos;
//STRIP001  InputEdit       aEdit;
//STRIP001  PopupMenu       aPopMenu;
//STRIP001  SwFldMgr*       pMgr;
//STRIP001  SwWrtShell*     pWrtShell;
//STRIP001  SwView*         pView;
//STRIP001     SfxBindings*    pBindings;
//STRIP001  String          aAktTableName, sOldFml;
//STRIP001  USHORT          nActionCnt;
//STRIP001
//STRIP001  BOOL            bFirst : 1;  //Initialisierungen beim ersten Aufruf
//STRIP001  BOOL            bActive : 1; //fuer Hide/Show beim Dokumentwechsel
//STRIP001  BOOL            bIsTable : 1;
//STRIP001  BOOL            bDelSel : 1;
//STRIP001  BOOL            bDoesUndo : 1;
//STRIP001  BOOL            bResetUndo : 1;
//STRIP001  BOOL            bCallUndo : 1;
//STRIP001
//STRIP001
//STRIP001 //STRIP001   void DelBoxCntnt();
//STRIP001 //STRIP001   DECL_LINK( ModifyHdl, InputEdit* );

//STRIP001 protected:
//STRIP001  virtual void    Resize();
//STRIP001  virtual void    Click();
//STRIP001  DECL_LINK( MenuHdl, Menu * );
//STRIP001  void            ApplyFormula();
//STRIP001  void            CancelFormula();
//STRIP001 public:
//STRIP001                     SwInputWindow( Window* pParent, SfxBindings* pBindings );
//STRIP001  virtual         ~SwInputWindow();


//STRIP001  void            SelectHdl( ToolBox*);
//STRIP001  virtual void    Show();
//STRIP001  BOOL            IsActive(){ return bActive; };
//STRIP001  DECL_LINK( SelTblCellsNotify, SwWrtShell * );
//STRIP001
//STRIP001  void            SetFormula( const String& rFormula, BOOL bDelSel = TRUE );
//STRIP001  const SwView*   GetView() const{return pView;}
//STRIP001 };

class SwInputChild : public SfxChildWindow
{
    BOOL            bObjVis;
    SfxDispatcher*  pDispatch;
public:
    SwInputChild( Window* ,
                        USHORT nId,
                        SfxBindings*,
                        SfxChildWinInfo*  );
    ~SwInputChild();
    SFX_DECL_CHILDWINDOW( SwInputChild );
//STRIP001  void            SetFormula( const String& rFormula, BOOL bDelSel = TRUE )
//STRIP001                      { ((SwInputWindow*)pWindow)->SetFormula(
//STRIP001                                  rFormula, bDelSel ); }
//STRIP001  const SwView*   GetView() const{return ((SwInputWindow*)pWindow)->GetView();}
//STRIP001
};

//==================================================================

} //namespace binfilter
#endif

