/*************************************************************************
 *
 *  $RCSfile: dwfunctr.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:18:25 $
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
#ifndef _SC_DWFUNCTR_HXX
#define _SC_DWFUNCTR_HXX

#ifndef _SFX_CHILDWIN_HXX //autogen
#include <bf_sfx2/childwin.hxx>
#endif

#ifndef _SFXDOCKWIN_HXX //autogen
#include <bf_sfx2/dockwin.hxx>
#endif

#ifndef _SFXLSTNER_HXX //autogen
#include <svtools/lstner.hxx>
#endif

#ifndef _STDCTRL_HXX //autogen
#include <svtools/stdctrl.hxx>
#endif

#ifndef _LSTBOX_HXX //autogen
#include <vcl/lstbox.hxx>
#endif

#ifndef _IMAGEBTN_HXX //autogen
#include <vcl/imagebtn.hxx>
#endif

#ifndef _COMBOBOX_HXX //autogen
#include <vcl/combobox.hxx>
#endif

#ifndef SC_ANYREFDG_HXX
#include "anyrefdg.hxx"
#endif

#ifndef SC_FUNCUTL_HXX
#include "funcutl.hxx"
#endif

#ifndef SC_SCGLOB_HXX
#include "global.hxx"       // ScAddress
#endif

#ifndef SC_PRIVSPLT_HXX
#include "privsplt.hxx"
#endif

#ifndef LRU_MAX
#define LRU_MAX 10
#endif
/*************************************************************************
|*
|* Ableitung vom SfxChildWindow als "Behaelter" fuer Controller
|*
\************************************************************************/

class ScFunctionChildWindow : public SfxChildWindow
{
 public:
     ScFunctionChildWindow( Window* pParent, USHORT nId, SfxBindings* pBindings,SfxChildWinInfo* pInfo):SfxChildWindow( pParent, nId ){DBG_ASSERT(0, "STRIP")}; //STRIP001 ScFunctionChildWindow( Window*, USHORT, SfxBindings*,
//STRIP001      SfxChildWinInfo* );

    SFX_DECL_CHILDWINDOW(ScFunctionChildWindow);
};

/*************************************************************************
|*
|* ScFuncDockWin
|*
\************************************************************************/

//STRIP001 class ScFunctionDockWin : public SfxDockingWindow, public SfxListener
//STRIP001 {
//STRIP001
//STRIP001 private:
//STRIP001  Timer               aTimer;
//STRIP001  ScPrivatSplit       aPrivatSplit;
//STRIP001  ListBox             aCatBox;
//STRIP001  ListBox             aFuncList;
//STRIP001  ListBox             aDDFuncList;
//STRIP001  ListBox*            pAllFuncList;
//STRIP001
//STRIP001  SfxChildAlignment   eSfxNewAlignment;
//STRIP001  SfxChildAlignment   eSfxOldAlignment;
//STRIP001  ImageButton         aInsertButton;
//STRIP001  FixedText           aFiFuncDesc;
//STRIP001  USHORT              nLeftSlot;
//STRIP001  USHORT              nRightSlot;
//STRIP001  ULONG               nMinWidth;
//STRIP001  ULONG               nMinHeight;
//STRIP001  Size                aOldSize;
//STRIP001  BOOL                bSizeFlag;
//STRIP001  BOOL                bInit;
//STRIP001  short               nDockMode;
//STRIP001  Point               aSplitterInitPos;
//STRIP001  ScFuncDesc*         pFuncDesc;
//STRIP001  USHORT              nArgs;
//STRIP001  String**            pArgArr;
//STRIP001
//STRIP001
//STRIP001  ScFuncDesc*     aLRUList[LRU_MAX];

//STRIP001  void            UpdateFunctionList();
//STRIP001  void            UpdateLRUList();
//STRIP001  void            DoEnter(BOOL bOk); //@@ ???
//STRIP001  void            SetDescription();
//STRIP001  void            SetLeftRightSize();
//STRIP001  void            SetTopBottonSize();
//STRIP001  void            SetMyWidthLeRi(Size &aNewSize);
//STRIP001  void            SetMyHeightLeRi(Size &aNewSize);
//STRIP001  void            SetMyWidthToBo(Size &aNewSize);
//STRIP001  void            SetMyHeightToBo(Size &aNewSize);
//STRIP001  void            UseSplitterInitPos();
//STRIP001
//STRIP001                  DECL_LINK( SetSelectionHdl, void* );
//STRIP001                  DECL_LINK( SelHdl, ListBox* );
//STRIP001                  DECL_LINK(SetSplitHdl,ScPrivatSplit*);
//STRIP001                  DECL_LINK( TimerHdl, Timer*);

//STRIP001 protected:

//STRIP001  virtual BOOL    Close();
//STRIP001  virtual void    Resize();
//STRIP001  virtual void    Resizing( Size& rSize );
//STRIP001  virtual void    SetSize();
//STRIP001  virtual void    ToggleFloatingMode();
//STRIP001  virtual void    StateChanged( StateChangedType nStateChange );
//STRIP001
//STRIP001
//STRIP001  virtual SfxChildAlignment CheckAlignment(SfxChildAlignment,
//STRIP001                              SfxChildAlignment eAlign);

//STRIP001 public:
//STRIP001                  ScFunctionDockWin(  SfxBindings* pBindings,
//STRIP001                                      SfxChildWindow *pCW,
//STRIP001                                      Window* pParent,
//STRIP001                                      const ResId& rResId );

//STRIP001                  ~ScFunctionDockWin();
//STRIP001
//STRIP001  virtual void    SFX_NOTIFY( SfxBroadcaster& rBC, const TypeId& rBCType,
//STRIP001                          const SfxHint& rHint, const TypeId& rHintType );
//STRIP001
//STRIP001  void            SetSlotIDs( USHORT nLeft, USHORT nRight )
//STRIP001                      { nLeftSlot = nLeft; nRightSlot = nRight; }
//STRIP001
//STRIP001  void            InitLRUList();
//STRIP001
//STRIP001  void            Initialize (SfxChildWinInfo* pInfo);
//STRIP001  virtual void    FillInfo(SfxChildWinInfo&) const;
//STRIP001 };

#endif


