/*************************************************************************
 *
 *  $RCSfile: sw_gcc_outl.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:49:04 $
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

#include <format.hxx>
namespace binfilter {

#if ( defined GCC && defined C272 )

#if ( defined SINIX || defined HPUX || defined LINUX )
const SwFmtCol &SwFmt::GetCol(BOOL bInP) const
    { return aSet.GetCol(bInP); }
const SwFmtAnchor &SwFmt::GetAnchor(BOOL bInP) const
    { return aSet.GetAnchor(bInP); }
const SwFmtHoriOrient &SwFmt::GetHoriOrient(BOOL bInP) const
    { return aSet.GetHoriOrient(bInP); }
const SwFmtSurround &SwFmt::GetSurround(BOOL bInP) const
    { return aSet.GetSurround(bInP); }
const SwFmtFooter &SwFmt::GetFooter(BOOL bInP) const
    { return aSet.GetFooter(bInP); }
const SwFmtHeader &SwFmt::GetHeader(BOOL bInP) const
    { return aSet.GetHeader(bInP); }
const SwFmtFillOrder &SwFmt::GetFillOrder(BOOL bInP) const
    { return aSet.GetFillOrder(bInP); }
const SwFmtFrmSize &SwFmt::GetFrmSize(BOOL bInP) const
    { return aSet.GetFrmSize(bInP); }
#endif
#if ( defined HPUX )
const SvxPaperBinItem &SwFmt::GetPaperBin(BOOL bInP) const
    { return aSet.GetPaperBin(bInP); }
const SvxLRSpaceItem &SwFmt::GetLRSpace(BOOL bInP) const
    { return aSet.GetLRSpace(bInP); }
const SvxULSpaceItem &SwFmt::GetULSpace(BOOL bInP) const
    { return aSet.GetULSpace(bInP); }
const SwFmtCntnt &SwFmt::GetCntnt(BOOL bInP) const
    { return aSet.GetCntnt(bInP); }
const SvxPrintItem &SwFmt::GetPrint(BOOL bInP) const
    { return aSet.GetPrint(bInP); }
const SvxOpaqueItem &SwFmt::GetOpaque(BOOL bInP) const
    { return aSet.GetOpaque(bInP); }
const SvxProtectItem &SwFmt::GetProtect(BOOL bInP) const
    { return aSet.GetProtect(bInP); }
const SwFmtVertOrient &SwFmt::GetVertOrient(BOOL bInP) const
    { return aSet.GetVertOrient(bInP); }
const SvxBoxItem &SwFmt::GetBox(BOOL bInP) const
    { return aSet.GetBox(bInP); }
const SvxFmtKeepItem &SwFmt::GetKeep(BOOL bInP) const
    { return aSet.GetKeep(bInP); }
const SvxBrushItem &SwFmt::GetBackground(BOOL bInP) const
    { return aSet.GetBackground(bInP); }
const SvxShadowItem &SwFmt::GetShadow(BOOL bInP) const
    { return aSet.GetShadow(bInP); }
const SwFmtPageDesc &SwFmt::GetPageDesc(BOOL bInP) const
    { return aSet.GetPageDesc(bInP); }
const SvxFmtBreakItem &SwFmt::GetBreak(BOOL bInP) const
    { return aSet.GetBreak(bInP); }
const SvxMacroItem &SwFmt::GetMacro(BOOL bInP) const
    { return aSet.GetMacro(bInP); }
#endif

#endif


#if defined(MACOSX) && ( __GNUC__ < 3 )
// GrP revisit with gcc3

// fmtfordr.hxx
 const SwFmtFillOrder &SwAttrSet::GetFillOrder(BOOL bInP) const
    { return (const SwFmtFillOrder&)Get( RES_FILL_ORDER,bInP); }
 const SwFmtFillOrder &SwFmt::GetFillOrder(BOOL bInP) const
    { return aSet.GetFillOrder(bInP); }

// fmtfsize.hxx
 const SwFmtFrmSize &SwAttrSet::GetFrmSize(BOOL bInP) const
    { return (const SwFmtFrmSize&)Get( RES_FRM_SIZE,bInP); }
 const SwFmtFrmSize &SwFmt::GetFrmSize(BOOL bInP) const
    { return aSet.GetFrmSize(bInP); }

// fmtatr.hxx
 const SvxPaperBinItem &SwAttrSet::GetPaperBin(BOOL bInP) const
    { return (const SvxPaperBinItem&)Get( RES_PAPER_BIN,bInP); }
 const SvxPaperBinItem &SwFmt::GetPaperBin(BOOL bInP) const
    { return aSet.GetPaperBin(bInP); }
 const SvxLRSpaceItem &SwAttrSet::GetLRSpace(BOOL bInP) const
    { return (const SvxLRSpaceItem&)Get( RES_LR_SPACE,bInP); }
 const SvxLRSpaceItem &SwFmt::GetLRSpace(BOOL bInP) const
    { return aSet.GetLRSpace(bInP); }
 const SvxULSpaceItem &SwAttrSet::GetULSpace(BOOL bInP) const
    { return (const SvxULSpaceItem&)Get( RES_UL_SPACE,bInP); }
 const SvxULSpaceItem &SwFmt::GetULSpace(BOOL bInP) const
    { return aSet.GetULSpace(bInP); }

// fmtcntnt.hxx
 const SwFmtCntnt &SwAttrSet::GetCntnt(BOOL bInP) const
    { return (const SwFmtCntnt&)Get( RES_CNTNT,bInP); }
 const SwFmtCntnt &SwFmt::GetCntnt(BOOL bInP) const
    { return aSet.GetCntnt(bInP); }

// fmthdft.hxx
 const SwFmtHeader &SwAttrSet::GetHeader(BOOL bInP) const
    { return (const SwFmtHeader&)Get( RES_HEADER,bInP); }
 const SwFmtHeader &SwFmt::GetHeader(BOOL bInP) const
    { return aSet.GetHeader(bInP); }
 const SwFmtFooter &SwAttrSet::GetFooter(BOOL bInP) const
    { return (const SwFmtFooter&)Get( RES_FOOTER,bInP); }
 const SwFmtFooter &SwFmt::GetFooter(BOOL bInP) const
    { return aSet.GetFooter(bInP); }

// fmtatr.hxx
 const SvxPrintItem &SwAttrSet::GetPrint(BOOL bInP) const
    { return (const SvxPrintItem&)Get( RES_PRINT,bInP); }
 const SvxPrintItem &SwFmt::GetPrint(BOOL bInP) const
    { return aSet.GetPrint(bInP); }
 const SvxOpaqueItem &SwAttrSet::GetOpaque(BOOL bInP) const
    { return (const SvxOpaqueItem&)Get( RES_OPAQUE,bInP); }
 const SvxOpaqueItem &SwFmt::GetOpaque(BOOL bInP) const
    { return aSet.GetOpaque(bInP); }
 const SvxProtectItem &SwAttrSet::GetProtect(BOOL bInP) const
    { return (const SvxProtectItem&)Get( RES_PROTECT,bInP); }
 const SvxProtectItem &SwFmt::GetProtect(BOOL bInP) const
    { return aSet.GetProtect(bInP); }

// fmtsrnd.hxx
 const SwFmtSurround &SwAttrSet::GetSurround(BOOL bInP) const
    { return (const SwFmtSurround&)Get( RES_SURROUND,bInP); }
 const SwFmtSurround &SwFmt::GetSurround(BOOL bInP) const
    { return aSet.GetSurround(bInP); }

// fmtornt.hxx
 const SwFmtVertOrient &SwAttrSet::GetVertOrient(BOOL bInP) const
    { return (const SwFmtVertOrient&)Get( RES_VERT_ORIENT,bInP); }
 const SwFmtVertOrient &SwFmt::GetVertOrient(BOOL bInP) const
    { return aSet.GetVertOrient(bInP); }
 const SwFmtHoriOrient &SwAttrSet::GetHoriOrient(BOOL bInP) const
    { return (const SwFmtHoriOrient&)Get( RES_HORI_ORIENT,bInP); }
 const SwFmtHoriOrient &SwFmt::GetHoriOrient(BOOL bInP) const
    { return aSet.GetHoriOrient(bInP); }

// fmtanchr.hxx
const SwFmtAnchor &SwAttrSet::GetAnchor(BOOL bInP) const
    { return (const SwFmtAnchor&)Get( RES_ANCHOR,bInP); }
const SwFmtAnchor &SwFmt::GetAnchor(BOOL bInP) const
     { return aSet.GetAnchor(bInP); }

// fmtatr.hxx
 const SvxBoxItem &SwAttrSet::GetBox(BOOL bInP) const
    { return (const SvxBoxItem&)Get( RES_BOX,bInP); }
 const SvxBoxItem &SwFmt::GetBox(BOOL bInP) const
    { return aSet.GetBox(bInP); }
 const SvxFmtKeepItem &SwAttrSet::GetKeep(BOOL bInP) const
    { return (const SvxFmtKeepItem&)Get( RES_KEEP,bInP); }
 const SvxFmtKeepItem &SwFmt::GetKeep(BOOL bInP) const
    { return aSet.GetKeep(bInP); }
 const SvxBrushItem &SwAttrSet::GetBackground(BOOL bInP) const
    { return (const SvxBrushItem&)Get( RES_BACKGROUND,bInP); }
 const SvxBrushItem &SwFmt::GetBackground(BOOL bInP) const
    { return aSet.GetBackground(bInP); }
 const SvxShadowItem &SwAttrSet::GetShadow(BOOL bInP) const
    { return (const SvxShadowItem&)Get( RES_SHADOW,bInP); }
 const SvxShadowItem &SwFmt::GetShadow(BOOL bInP) const
    { return aSet.GetShadow(bInP); }

// fmtpdsc.hxx
 const SwFmtPageDesc &SwAttrSet::GetPageDesc(BOOL bInP) const
    { return (const SwFmtPageDesc&)Get( RES_PAGEDESC,bInP); }
 const SwFmtPageDesc &SwFmt::GetPageDesc(BOOL bInP) const
    { return aSet.GetPageDesc(bInP); }

// fmtatr.hxx
 const SvxFmtBreakItem &SwAttrSet::GetBreak(BOOL bInP) const
    { return (const SvxFmtBreakItem&)Get( RES_BREAK,bInP); }
 const SvxFmtBreakItem &SwFmt::GetBreak(BOOL bInP) const
    { return aSet.GetBreak(bInP); }

// fmtclds.hxx
 const SwFmtCol &SwAttrSet::GetCol(BOOL bInP) const
    { return (const SwFmtCol&)Get( RES_COL,bInP); }
 const SwFmtCol &SwFmt::GetCol(BOOL bInP) const
    { return aSet.GetCol(bInP); }

// fmtatr.hxx
 const SvxMacroItem &SwAttrSet::GetMacro(BOOL bInP) const
    { return (const SvxMacroItem&)Get( RES_FRMMACRO,bInP); }
 const SvxMacroItem &SwFmt::GetMacro(BOOL bInP) const
    { return aSet.GetMacro(bInP); }

// fmturl.hxx
const SwFmtURL &SwAttrSet::GetURL(BOOL bInP) const
    { return (const SwFmtURL&)Get( RES_URL,bInP); }
const SwFmtURL &SwFmt::GetURL(BOOL bInP) const
    { return aSet.GetURL(bInP); }

// fmteiro.hxx
 const SwFmtEditInReadonly &SwAttrSet::GetEditInReadonly(BOOL bInP) const
    { return (const SwFmtEditInReadonly&)Get( RES_EDIT_IN_READONLY,bInP); }
 const SwFmtEditInReadonly &SwFmt::GetEditInReadonly(BOOL bInP) const
    { return aSet.GetEditInReadonly(bInP); }

// fmtlsplt.hxx
 const SwFmtLayoutSplit &SwAttrSet::GetLayoutSplit(BOOL bInP) const
    { return (const SwFmtLayoutSplit&)Get( RES_LAYOUT_SPLIT,bInP); }
 const SwFmtLayoutSplit &SwFmt::GetLayoutSplit(BOOL bInP) const
    { return aSet.GetLayoutSplit(bInP); }

// fmtcnct.hxx
const SwFmtChain &SwAttrSet::GetChain(BOOL bInP) const
    { return (const SwFmtChain&)Get( RES_CHAIN,bInP); }
const SwFmtChain &SwFmt::GetChain(BOOL bInP) const
    { return aSet.GetChain(bInP); }

// fmtline.hxx
 const SwFmtLineNumber &SwAttrSet::GetLineNumber(BOOL bInP) const
    { return (const SwFmtLineNumber&)Get( RES_LINENUMBER,bInP); }
 const SwFmtLineNumber &SwFmt::GetLineNumber(BOOL bInP) const
    { return aSet.GetLineNumber(bInP); }

// fmtftntx.hxx
 const SwFmtFtnAtTxtEnd &SwAttrSet::GetFtnAtTxtEnd(BOOL bInP) const
    { return (const SwFmtFtnAtTxtEnd&)Get( RES_FTN_AT_TXTEND, bInP); }
 const SwFmtFtnAtTxtEnd &SwFmt::GetFtnAtTxtEnd(BOOL bInP) const
    { return aSet.GetFtnAtTxtEnd(bInP); }
 const SwFmtEndAtTxtEnd &SwAttrSet::GetEndAtTxtEnd(BOOL bInP) const
    { return (const SwFmtEndAtTxtEnd&)Get( RES_END_AT_TXTEND, bInP); }
 const SwFmtEndAtTxtEnd &SwFmt::GetEndAtTxtEnd(BOOL bInP) const
    { return aSet.GetEndAtTxtEnd(bInP); }

// fmtclbl.hxx
 const SwFmtNoBalancedColumns &SwAttrSet::GetBalancedColumns(BOOL bInP) const
    { return (const SwFmtNoBalancedColumns&)Get( RES_COLUMNBALANCE, bInP ); }
 const SwFmtNoBalancedColumns &SwFmt::GetBalancedColumns(BOOL bInP) const
    { return aSet.GetBalancedColumns( bInP ); }

// grfatr.hxx
 const SwMirrorGrf &SwAttrSet::GetMirrorGrf(BOOL bInP) const
    { return (const SwMirrorGrf&)Get( RES_GRFATR_MIRRORGRF,bInP); }
 const SwMirrorGrf &SwFmt::GetMirrorGrf(BOOL bInP) const
    { return aSet.GetMirrorGrf(bInP); }

// cellatr.hxx
 const SwTblBoxNumFormat      &SwAttrSet::GetTblBoxNumFmt(BOOL bInP) const
    {   return (const SwTblBoxNumFormat&)Get( RES_BOXATR_FORMAT,bInP); }
 const SwTblBoxFormula            &SwAttrSet::GetTblBoxFormula(BOOL bInP) const
    {   return (const SwTblBoxFormula&)Get( RES_BOXATR_FORMULA,bInP); }
 const SwTblBoxValue                      &SwAttrSet::GetTblBoxValue(BOOL bInP) const
    {   return (const SwTblBoxValue&)Get( RES_BOXATR_VALUE, bInP); }
 const SwTblBoxNumFormat        &SwFmt::GetTblBoxNumFmt(BOOL bInP) const
    {   return aSet.GetTblBoxNumFmt(bInP); }
 const SwTblBoxFormula      &SwFmt::GetTblBoxFormula(BOOL bInP) const
    {   return aSet.GetTblBoxFormula(bInP); }
 const SwTblBoxValue            &SwFmt::GetTblBoxValue(BOOL bInP) const
    {   return aSet.GetTblBoxValue(bInP); }

// charatr.hxx
 const SvxFontItem         &SwAttrSet::GetFont(BOOL bInP) const
    {   return (const SvxFontItem&)Get( RES_CHRATR_FONT,bInP); }
 const SvxFontItem             &SwFmt::GetFont(BOOL bInP) const
    {   return aSet.GetFont(bInP); }

// frmatr.hxx
 const SvxFrameDirectionItem &SwAttrSet::GetFrmDir(BOOL bInP) const
    { return (const SvxFrameDirectionItem&)Get( RES_FRAMEDIR,bInP); }
 const SvxFrameDirectionItem    &SwFmt::GetFrmDir(BOOL bInP) const
    { return aSet.GetFrmDir(bInP); }

#include <node.hxx>
#include <ndole.hxx>
#include <ndtxt.hxx>
#include <ndnotxt.hxx>
#include <ndgrf.hxx>

/* [ed] 4/27/02 I changed all of the static casts below to dynamic casts.  While
   debugging swriter, I noticed these functions weren't properly offsetting the
   pointers to this to upcast the objects.  Instead, they returned the straight
   pointer to the SwNode instead of the ponter to the start of the record of the
   appropriate node type.

   All of these are essentially trying to just mimic RTTI anyway. */

// ndole.hxx
 SwOLENode *SwNode::GetOLENode()
{
     return ND_OLENODE == nNodeType ? dynamic_cast<SwOLENode *>(this) : 0;
}
 const SwOLENode *SwNode::GetOLENode() const
{
     return ND_OLENODE == nNodeType ? dynamic_cast<const SwOLENode *>(this) : 0;
}

// ndtxt.hxx
       SwTxtNode   *SwNode::GetTxtNode()
{
     return ND_TEXTNODE == nNodeType ? dynamic_cast<SwTxtNode *>(this) : 0;
}
 const SwTxtNode   *SwNode::GetTxtNode() const
{
     return ND_TEXTNODE == nNodeType ? dynamic_cast<const SwTxtNode *>(this) : 0;
}

// ndnotxt.hxx
 SwNoTxtNode *SwNode::GetNoTxtNode()
{
    return ND_NOTXTNODE & nNodeType ? dynamic_cast<SwNoTxtNode *>(this) : 0;
}
 const SwNoTxtNode *SwNode::GetNoTxtNode() const
{
    return ND_NOTXTNODE & nNodeType ? dynamic_cast<const SwNoTxtNode *>(this) : 0;
}

// ndgrf.hxx
       SwGrfNode     *SwNode::GetGrfNode()
{
     return ND_GRFNODE == nNodeType ? dynamic_cast<SwGrfNode *>(this) : 0;
}
 const SwGrfNode   *SwNode::GetGrfNode() const
{
     return ND_GRFNODE == nNodeType ? dynamic_cast<const SwGrfNode *>(this) : 0;
}

// defined MACOSX
#endif
}
