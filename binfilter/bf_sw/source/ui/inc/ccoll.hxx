/*************************************************************************
 *
 *  $RCSfile: ccoll.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:20:00 $
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
#ifndef _CCOLL_HXX
#define _CCOLL_HXX

#ifndef _SFXPOOLITEM_HXX //autogen
#include <svtools/poolitem.hxx>
#endif

#ifndef _STRING_HXX //autogen
#include <tools/string.hxx>
#endif

#ifndef _SFXTABDLG_HXX //autogen
#include <bf_sfx2/tabdlg.hxx>
#endif

#ifndef _FIXED_HXX //autogen
#include <vcl/fixed.hxx>
#endif

#ifndef _BUTTON_HXX //autogen
#include <vcl/button.hxx>
#endif

#ifndef _SVTABBX_HXX //autogen
#include <svtools/svtabbx.hxx>
#endif

#ifndef _LSTBOX_HXX //autogen
#include <vcl/lstbox.hxx>
#endif

#ifndef _TOOLS_RESARY_HXX
#include <tools/resary.hxx>
#endif

#include "cmdid.h"

class SwWrtShell;
class SwFmt;
class SwCollCondition;


//***********************************************************

struct CollName {
//      const char* pStr;
        ULONG nCnd;
        ULONG nSubCond;
    };

//***********************************************************

#define COND_COMMAND_COUNT 28

struct CommandStruct
{
    ULONG nCnd;
    ULONG nSubCond;
};


//***********************************************************

class SwCondCollItem : public SfxPoolItem
{
    static CommandStruct        aCmds[COND_COMMAND_COUNT];

    String                      sStyles[COND_COMMAND_COUNT];

public:
    SwCondCollItem(USHORT nWhich = FN_COND_COLL);
    ~SwCondCollItem();

                                TYPEINFO();

    virtual SfxPoolItem*        Clone( SfxItemPool *pPool = 0 ) const;
    virtual int                 operator==( const SfxPoolItem& ) const;

    static const CommandStruct* GetCmds();

    const String&               GetStyle(USHORT nPos) const;
    void                        SetStyle( const String* pStyle, USHORT nPos);

};

//***********************************************************

//STRIP001 class SwCondCollPage : public SfxTabPage
//STRIP001 {
//STRIP001     FixedLine           aConditionFL;
//STRIP001  CheckBox            aConditionCB;
//STRIP001
//STRIP001  FixedText           aContextFT;
//STRIP001  FixedText           aUsedFT;
//STRIP001  SvTabListBox        aTbLinks;
//STRIP001
//STRIP001  FixedText           aStyleFT;
//STRIP001  ListBox             aStyleLB;
//STRIP001  ListBox             aFilterLB;
//STRIP001
//STRIP001  PushButton          aRemovePB;
//STRIP001  PushButton          aAssignPB;
//STRIP001
//STRIP001  String              sNoTmpl;
//STRIP001  ResStringArray      aStrArr;
//STRIP001
//STRIP001  SwWrtShell          &rSh;
//STRIP001  const CommandStruct*pCmds;
//STRIP001  SwFmt*              pFmt;
//STRIP001
//STRIP001  CollName*           pNms;
//STRIP001
//STRIP001  BOOL                bNewTemplate;
//STRIP001
//STRIP001
//STRIP001          SwCondCollPage(Window *pParent, const SfxItemSet &rSet);
//STRIP001  virtual ~SwCondCollPage();
//STRIP001
//STRIP001  virtual int     DeactivatePage(SfxItemSet *pSet);
//STRIP001
//STRIP001  DECL_LINK( OnOffHdl, CheckBox* );
//STRIP001  DECL_LINK( AssignRemoveHdl, PushButton*);
//STRIP001  DECL_LINK( SelectHdl, ListBox* );
//STRIP001
//STRIP001 public:
//STRIP001
//STRIP001  static SfxTabPage *Create(Window *pParent, const SfxItemSet &rSet);
//STRIP001  static USHORT* GetRanges();
//STRIP001
//STRIP001  virtual BOOL FillItemSet(      SfxItemSet &rSet);
//STRIP001  virtual void Reset      (const SfxItemSet &rSet);
//STRIP001
//STRIP001  void SetCollection( SwFmt* pFormat, BOOL bNew );
//STRIP001 };



#endif

