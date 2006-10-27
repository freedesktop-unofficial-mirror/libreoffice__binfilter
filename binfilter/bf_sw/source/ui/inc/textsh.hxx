/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: textsh.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 00:57:24 $
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

#ifndef _SWTEXTSH_HXX
#define _SWTEXTSH_HXX

#ifndef _SWBASESH_HXX
#include <basesh.hxx>
#endif
class Button;
namespace binfilter {


class SvxHyperlinkItem;

class SwTextShell: public SwBaseShell
{


public:
    SFX_DECL_INTERFACE(SW_TEXTSHELL);
    TYPEINFO();


    void    GetState(SfxItemSet &);

    void    ExecInsert(SfxRequest &){DBG_BF_ASSERT(0, "STRIP");} ;//STRIP001    void    ExecInsert(SfxRequest &);
    void    StateInsert(SfxItemSet&);
    void    ExecEnterNum(SfxRequest &){DBG_BF_ASSERT(0, "STRIP");} ;//STRIP001  void    ExecEnterNum(SfxRequest &);
    void    ExecBasicMove(SfxRequest &){DBG_BF_ASSERT(0, "STRIP");} ;//STRIP001     void    ExecBasicMove(SfxRequest &);
    void    ExecMove(SfxRequest &){DBG_BF_ASSERT(0, "STRIP");} ;//STRIP001  void    ExecMove(SfxRequest &);
    void    ExecMovePage(SfxRequest &){DBG_BF_ASSERT(0, "STRIP");} ;//STRIP001  void    ExecMovePage(SfxRequest &);
    void    ExecMoveCol(SfxRequest &){DBG_BF_ASSERT(0, "STRIP");} ;//STRIP001   void    ExecMoveCol(SfxRequest &);
    void    ExecMoveLingu(SfxRequest &){DBG_BF_ASSERT(0, "STRIP");} ;//STRIP001     void    ExecMoveLingu(SfxRequest &);
    void    ExecMoveMisc(SfxRequest &){DBG_BF_ASSERT(0, "STRIP");} ;//STRIP001  void    ExecMoveMisc(SfxRequest &);
    void    StateField(SfxItemSet &);
    void    ExecIdx(SfxRequest &){DBG_BF_ASSERT(0, "STRIP");}  ;//STRIP001  void    ExecIdx(SfxRequest &);
    void    GetIdxState(SfxItemSet &);
    void    ExecGlossary(SfxRequest &);//STRIP001   void    ExecGlossary(SfxRequest &);

    void    ExecCharAttr(SfxRequest &){DBG_BF_ASSERT(0, "STRIP");} ;//STRIP001  void    ExecCharAttr(SfxRequest &);
    void    ExecCharAttrArgs(SfxRequest &){DBG_BF_ASSERT(0, "STRIP");} ;//STRIP001  void    ExecCharAttrArgs(SfxRequest &);
    void    ExecParaAttr(SfxRequest &){DBG_BF_ASSERT(0, "STRIP");} ;//STRIP001  void    ExecParaAttr(SfxRequest &);
    void    ExecParaAttrArgs(SfxRequest &){DBG_BF_ASSERT(0, "STRIP");} ;//STRIP001  void    ExecParaAttrArgs(SfxRequest &);
    void    ExecAttr(SfxRequest &);
    void    ExecDB(SfxRequest &){DBG_BF_ASSERT(0, "STRIP");} ;//STRIP001    void    ExecDB(SfxRequest &);
    void    ExecTransliteration(SfxRequest &){DBG_BF_ASSERT(0, "STRIP");} ;//STRIP001   void    ExecTransliteration(SfxRequest &);

    void    GetAttrState(SfxItemSet &);

             SwTextShell(SwView &rView);
    virtual ~SwTextShell();
};

} //namespace binfilter
#endif
