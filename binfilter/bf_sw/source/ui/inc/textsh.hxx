/*************************************************************************
 *
 *  $RCSfile: textsh.hxx,v $
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

#ifndef _SWTEXTSH_HXX
#define _SWTEXTSH_HXX

#ifndef _SWBASESH_HXX
#include <basesh.hxx>
#endif

class Button;
//STRIP001 class SwFldMgr;
class SvxHyperlinkItem;

class SwTextShell: public SwBaseShell
{
//STRIP001  SwFldMgr*   pPostItFldMgr;

//STRIP001     void InsertSymbol( SfxRequest& );
//STRIP001  void InsertHyperlink(const SvxHyperlinkItem& rHlnkItem);
//STRIP001     BOOL InsertGraphicDlg( SfxRequest& );
//STRIP001     void ChangeHeaderOrFooter(const String& rStyleName, BOOL bHeader, BOOL bOn, BOOL bShowWarning);

public:
    SFX_DECL_INTERFACE(SW_TEXTSHELL);
    TYPEINFO();

//STRIP001  DECL_LINK( PostItNextHdl, Button * );
//STRIP001  DECL_LINK( PostItPrevHdl, Button * );
//STRIP001  DECL_LINK( RedlineNextHdl, Button * );
//STRIP001  DECL_LINK( RedlinePrevHdl, Button * );

//STRIP001  void    Execute(SfxRequest &);
    void    GetState(SfxItemSet &);

    void    ExecInsert(SfxRequest &){DBG_ASSERT(0, "STRIP");} ;//STRIP001   void    ExecInsert(SfxRequest &);
    void    StateInsert(SfxItemSet&);
//STRIP001  void    ExecDelete(SfxRequest &);
    void    ExecEnterNum(SfxRequest &){DBG_ASSERT(0, "STRIP");} ;//STRIP001     void    ExecEnterNum(SfxRequest &);
    void    ExecBasicMove(SfxRequest &){DBG_ASSERT(0, "STRIP");} ;//STRIP001    void    ExecBasicMove(SfxRequest &);
    void    ExecMove(SfxRequest &){DBG_ASSERT(0, "STRIP");} ;//STRIP001     void    ExecMove(SfxRequest &);
    void    ExecMovePage(SfxRequest &){DBG_ASSERT(0, "STRIP");} ;//STRIP001     void    ExecMovePage(SfxRequest &);
    void    ExecMoveCol(SfxRequest &){DBG_ASSERT(0, "STRIP");} ;//STRIP001  void    ExecMoveCol(SfxRequest &);
    void    ExecMoveLingu(SfxRequest &){DBG_ASSERT(0, "STRIP");} ;//STRIP001    void    ExecMoveLingu(SfxRequest &);
    void    ExecMoveMisc(SfxRequest &){DBG_ASSERT(0, "STRIP");} ;//STRIP001     void    ExecMoveMisc(SfxRequest &);
//STRIP001  void    ExecField(SfxRequest &rReq);
    void    StateField(SfxItemSet &);
    void    ExecIdx(SfxRequest &){DBG_ASSERT(0, "STRIP");}  ;//STRIP001     void    ExecIdx(SfxRequest &);
    void    GetIdxState(SfxItemSet &);
    void    ExecGlossary(SfxRequest &);//STRIP001   void    ExecGlossary(SfxRequest &);

    void    ExecCharAttr(SfxRequest &){DBG_ASSERT(0, "STRIP");} ;//STRIP001     void    ExecCharAttr(SfxRequest &);
    void    ExecCharAttrArgs(SfxRequest &){DBG_ASSERT(0, "STRIP");} ;//STRIP001     void    ExecCharAttrArgs(SfxRequest &);
    void    ExecParaAttr(SfxRequest &){DBG_ASSERT(0, "STRIP");} ;//STRIP001     void    ExecParaAttr(SfxRequest &);
    void    ExecParaAttrArgs(SfxRequest &){DBG_ASSERT(0, "STRIP");} ;//STRIP001     void    ExecParaAttrArgs(SfxRequest &);
    void    ExecAttr(SfxRequest &);
    void    ExecDB(SfxRequest &){DBG_ASSERT(0, "STRIP");} ;//STRIP001   void    ExecDB(SfxRequest &);
    void    ExecTransliteration(SfxRequest &){DBG_ASSERT(0, "STRIP");} ;//STRIP001  void    ExecTransliteration(SfxRequest &);

    void    GetAttrState(SfxItemSet &);

             SwTextShell(SwView &rView);
    virtual ~SwTextShell();
};

#endif
