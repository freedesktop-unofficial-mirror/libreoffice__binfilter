/*************************************************************************
 *
 *  $RCSfile: starmath_node.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: aw $ $Date: 2004-02-13 14:30:36 $
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

#pragma hdrstop
#define APPEND(str,ascii) str.AppendAscii(RTL_CONSTASCII_STRINGPARAM(ascii))

#ifndef _SV_GEN_HXX //autogen
#include <tools/gen.hxx>
#endif
#ifndef _FRACT_HXX //autogen
#include <tools/fract.hxx>
#endif
#ifndef INCLUDED_RTL_MATH_HXX
#include <rtl/math.hxx>
#endif
#ifndef _COLOR_HXX //autogen
#include <tools/color.hxx>
#endif
#ifndef _SV_METRIC_HXX //autogen
#include <vcl/metric.hxx>
#endif
#ifndef _SV_LINEINFO_HXX
#include <vcl/lineinfo.hxx>
#endif
#ifndef _SV_OUTDEV_HXX //autogen
#include <vcl/outdev.hxx>
#endif
#ifndef _SFXMODULE_HXX //autogen
#include <bf_sfx2/module.hxx>
#endif


#ifndef NODE_HXX
#include "node.hxx"
#endif
#ifndef RECT_HXX
#include <rect.hxx>
#endif
#ifndef SYMBOL_HXX
#include "symbol.hxx"
#endif
#ifndef _SMMOD_HXX
#include "smmod.hxx"
#endif
#ifndef DOCUMENT_HXX
#include <document.hxx>
#endif
#ifndef VIEW_HXX
#include <view.hxx>
#endif
#ifndef _MATHTYPE_HXX
#include "mathtype.hxx"
#endif

#include <math.h>
#include <float.h>
namespace binfilter {

// define this to draw rectangles for debugging
//#define SM_RECT_DEBUG

////////////////////////////////////////
// SmTmpDevice
// Allows for font and color changes. The original settings will be restored
// in the destructor.
// It's main purpose is to allow for the "const" in the 'OutputDevice'
// argument in the 'Arrange' functions and restore changes made in the 'Draw'
// functions.
// Usually a MapMode of 1/100th mm will be used.
//

/*N*/ class SmTmpDevice
/*N*/ {
/*N*/   OutputDevice  &rOutDev;
/*N*/
/*N*/   // disallow use of copy-constructor and assignment-operator
/*N*/   SmTmpDevice(const SmTmpDevice &rTmpDev);
/*N*/   SmTmpDevice & operator = (const SmTmpDevice &rTmpDev);
/*N*/
/*N*/     Color   Impl_GetColor( const Color& rColor );
/*N*/
/*N*/ public:
/*N*/     SmTmpDevice(OutputDevice &rTheDev, BOOL bUseMap100th_mm);
/*N*/     ~SmTmpDevice()  { rOutDev.Pop(); }
/*N*/
/*N*/     void SetFont(const Font &rNewFont);
/*N*/
/*N*/     void SetLineColor( const Color& rColor )    { rOutDev.SetLineColor( Impl_GetColor(rColor) ); }
/*N*/     void SetFillColor( const Color& rColor )    { rOutDev.SetFillColor( Impl_GetColor(rColor) ); }
/*N*/     void SetTextColor( const Color& rColor )    { rOutDev.SetTextColor( Impl_GetColor(rColor) ); }
/*N*/
/*N*/     operator OutputDevice & () { return rOutDev; }
/*N*/ };


/*N*/ SmTmpDevice::SmTmpDevice(OutputDevice &rTheDev, BOOL bUseMap100th_mm) :
/*N*/   rOutDev(rTheDev)
/*N*/ {
/*N*/     rOutDev.Push( PUSH_FONT | PUSH_MAPMODE |
/*N*/                   PUSH_LINECOLOR | PUSH_FILLCOLOR | PUSH_TEXTCOLOR );
/*N*/     if (bUseMap100th_mm  &&  MAP_100TH_MM != rOutDev.GetMapMode().GetMapUnit())
/*N*/     {
/*?*/         DBG_ERROR( "incorrect MapMode?" );
/*?*/         rOutDev.SetMapMode( MAP_100TH_MM );     //Immer fuer 100% fomatieren
/*N*/     }
/*N*/ }


/*N*/ Color SmTmpDevice::Impl_GetColor( const Color& rColor )
/*N*/ {
/*N*/     ColorData nNewCol = rColor.GetColor();
/*N*/     if (COL_AUTO == nNewCol)
/*N*/     {
/*N*/         if (OUTDEV_PRINTER == rOutDev.GetOutDevType())
/*N*/             nNewCol = COL_BLACK;
/*N*/         else
/*N*/         {
/*N*/             Color aBgCol( rOutDev.GetBackground().GetColor() );
/*N*/             if (OUTDEV_WINDOW == rOutDev.GetOutDevType())
/*N*/                 aBgCol = ((Window &) rOutDev).GetDisplayBackground().GetColor();
/*N*/
/*N*/             nNewCol = SM_MOD1()->GetColorConfig().GetColorValue(svtools::FONTCOLOR).nColor;
/*N*/
/*N*/             Color aTmpColor( nNewCol );
/*N*/             if (aBgCol.IsDark() && aTmpColor.IsDark())
/*N*/                 nNewCol = COL_WHITE;
/*N*/             else if (aBgCol.IsBright() && aTmpColor.IsBright())
/*N*/                 nNewCol = COL_BLACK;
/*N*/         }
/*N*/     }
/*N*/     return Color( nNewCol );
/*N*/ }


/*N*/ void SmTmpDevice::SetFont(const Font &rNewFont)
/*N*/ {
/*N*/     rOutDev.SetFont( rNewFont );
/*N*/     rOutDev.SetTextColor( Impl_GetColor( rNewFont.GetColor() ) );
/*N*/ }


///////////////////////////////////////////////////////////////////////////


/*N*/ SmNode::SmNode(SmNodeType eNodeType, const SmToken &rNodeToken)
/*N*/ {
/*N*/   eType      = eNodeType;
/*N*/   eScaleMode = SCALE_NONE;
/*N*/   aNodeToken = rNodeToken;
/*N*/     nAccIndex  = -1;
/*N*/ }


/*N*/ SmNode::~SmNode()
/*N*/ {
/*N*/ }


/*N*/ BOOL SmNode::IsVisible() const
/*N*/ {
/*N*/     return FALSE;
/*N*/ }


/*N*/ USHORT SmNode::GetNumSubNodes() const
/*N*/ {
/*N*/   return 0;
/*N*/ }


/*N*/ SmNode * SmNode::GetSubNode(USHORT nIndex)
/*N*/ {
/*N*/   return NULL;
/*N*/ }


/*N*/ SmNode * SmNode::GetLeftMost()
/*N*/   //  returns leftmost node of current subtree.
/*N*/   //! (this assumes the one with index 0 is always the leftmost subnode
/*N*/   //! for the current node).
/*N*/ {
/*N*/   SmNode *pNode = GetNumSubNodes() > 0 ?
/*N*/                       GetSubNode(0) : NULL;
/*N*/
/*N*/   return pNode ? pNode->GetLeftMost() : this;
/*N*/ }


//STRIP001 void SmNode::SetPhantom(BOOL bIsPhantomP)
//STRIP001 {
//STRIP001  if (! (Flags() & FLG_VISIBLE))
//STRIP001      bIsPhantom = bIsPhantomP;
//STRIP001
//STRIP001  SmNode *pNode;
//STRIP001  USHORT  nSize = GetNumSubNodes();
//STRIP001  for (USHORT i = 0; i < nSize; i++)
//STRIP001      if (pNode = GetSubNode(i))
//STRIP001          pNode->SetPhantom(bIsPhantom);
//STRIP001 }


/*N*/ void SmNode::SetColor(const Color& rColor)
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  if (! (Flags() & FLG_COLOR))
//STRIP001      GetFont().SetColor(rColor);
//STRIP001
//STRIP001  SmNode *pNode;
//STRIP001  USHORT  nSize = GetNumSubNodes();
//STRIP001  for (USHORT i = 0; i < nSize; i++)
//STRIP001      if (pNode = GetSubNode(i))
//STRIP001          pNode->SetColor(rColor);
/*N*/ }


/*N*/ void SmNode::SetAttribut(USHORT nAttrib)
/*N*/ {
/*N*/   if (   nAttrib == ATTR_BOLD  &&  !(Flags() & FLG_BOLD)
/*N*/       || nAttrib == ATTR_ITALIC  &&  !(Flags() & FLG_ITALIC))
/*N*/       nAttributes |= nAttrib;
/*N*/
/*N*/   SmNode *pNode;
/*N*/   USHORT nSize = GetNumSubNodes();
/*N*/   for (USHORT i = 0; i < nSize; i++)
/*N*/       if (pNode = GetSubNode(i))
/*N*/           pNode->SetAttribut(nAttrib);
/*N*/ }


/*N*/ void SmNode::ClearAttribut(USHORT nAttrib)
/*N*/ {
/*N*/   if (   nAttrib == ATTR_BOLD  &&  !(Flags() & FLG_BOLD)
/*N*/       || nAttrib == ATTR_ITALIC  &&  !(Flags() & FLG_ITALIC))
/*N*/       nAttributes &= ~nAttrib;
/*N*/
/*N*/   SmNode *pNode;
/*N*/   USHORT nSize = GetNumSubNodes();
/*N*/   for (USHORT i = 0; i < nSize; i++)
/*N*/       if (pNode = GetSubNode(i))
/*N*/           pNode->ClearAttribut(nAttrib);
/*N*/ }


/*N*/ void SmNode::SetFont(const SmFace &rFace)
/*N*/ {
/*N*/   if (!(Flags() & FLG_FONT))
/*N*/       GetFont() = rFace;
/*N*/
/*N*/   SmNode *pNode;
/*N*/   USHORT  nSize = GetNumSubNodes();
/*N*/   for (USHORT i = 0; i < nSize; i++)
/*N*/       if (pNode = GetSubNode(i))
/*N*/           pNode->SetFont(rFace);
/*N*/ }


/*N*/ void SmNode::SetFontSize(const Fraction &rSize, USHORT nType)
/*N*/   //! 'rSize' is in units of pts
/*N*/ {
/*N*/   Size  aSize;
/*N*/
/*N*/   if (!(Flags() & FLG_SIZE))
/*N*/   {
/*N*/       Fraction  aVal (SmPtsTo100th_mm(rSize.GetNumerator()),
/*N*/                       rSize.GetDenominator());
/*N*/       //long    nHeight = ::rtl::math::round(aVal);
/*N*/       long      nHeight = (long)aVal;
/*N*/
/*N*/       aSize = GetFont().GetSize();
/*N*/       aSize.Width() = 0;
/*N*/       switch(nType)
/*N*/       {
/*N*/           case FNTSIZ_ABSOLUT:
/*N*/               aSize.Height() = nHeight;
/*N*/               break;
/*N*/
/*N*/           case FNTSIZ_PLUS:
/*?*/               aSize.Height() += nHeight;
/*?*/               break;
/*N*/
/*N*/           case FNTSIZ_MINUS:
/*?*/               aSize.Height() -= nHeight;
/*?*/               break;
/*N*/
/*N*/           case FNTSIZ_MULTIPLY:
/*N*/               aSize.Height()  = (long) (Fraction(aSize.Height()) * rSize);
/*N*/               break;
/*N*/
/*N*/           case FNTSIZ_DIVIDE:
/*?*/               if (rSize != Fraction(0L))
/*?*/                   aSize.Height()  = (long) (Fraction(aSize.Height()) / rSize);
/*N*/               break;
/*N*/       }
/*N*/
/*N*/       // check the requested size against maximum value
/*N*/       static int __READONLY_DATA  nMaxVal = SmPtsTo100th_mm(128);
/*N*/       if (aSize.Height() > nMaxVal)
/*?*/           aSize.Height() = nMaxVal;
/*N*/
/*N*/       GetFont().SetSize(aSize);
/*N*/   }
/*N*/
/*N*/   SmNode *pNode;
/*N*/   USHORT  nSize = GetNumSubNodes();
/*N*/   for (USHORT i = 0;  i < nSize;  i++)
/*N*/       if (pNode = GetSubNode(i))
/*N*/           pNode->SetFontSize(rSize, nType);
/*N*/ }


/*N*/ void SmNode::SetSize(const Fraction &rSize)
/*N*/ {
/*N*/   GetFont() *= rSize;
/*N*/
/*N*/   SmNode *pNode;
/*N*/   USHORT  nSize = GetNumSubNodes();
/*N*/   for (USHORT i = 0;  i < nSize;  i++)
/*N*/       if (pNode = GetSubNode(i))
/*N*/           pNode->SetSize(rSize);
/*N*/ }


/*N*/ void SmNode::SetRectHorAlign(RectHorAlign eHorAlign, BOOL bApplyToSubTree )
/*N*/ {
/*N*/   if (!(Flags() & FLG_HORALIGN))
/*N*/       eRectHorAlign = eHorAlign;
/*N*/
/*N*/     if (bApplyToSubTree)
/*N*/     {
/*N*/         SmNode *pNode;
/*N*/         USHORT  nSize = GetNumSubNodes();
/*N*/         for (USHORT i = 0; i < nSize; i++)
/*?*/             if (pNode = GetSubNode(i))
/*?*/                 pNode->SetRectHorAlign(eHorAlign);
/*N*/     }
/*N*/ }


/*N*/ void SmNode::PrepareAttributes()
/*N*/ {
/*N*/   GetFont().SetWeight((Attributes() & ATTR_BOLD)   ? WEIGHT_BOLD   : WEIGHT_NORMAL);
/*N*/   GetFont().SetItalic((Attributes() & ATTR_ITALIC) ? ITALIC_NORMAL : ITALIC_NONE);
/*N*/ }


/*N*/ void SmNode::Prepare(const SmFormat &rFormat, const SmDocShell &rDocShell)
/*N*/ {
/*N*/ #if OSL_DEBUG_LEVEL > 1
/*N*/   bIsDebug    = TRUE;
/*N*/ #else
/*N*/   bIsDebug    = FALSE;
/*N*/ #endif
/*N*/   bIsPhantom  = FALSE;
/*N*/   nFlags      = 0;
/*N*/   nAttributes = 0;
/*N*/
/*N*/   switch (rFormat.GetHorAlign())
/*N*/   {   case AlignLeft:     eRectHorAlign = RHA_LEFT;   break;
/*N*/       case AlignCenter:   eRectHorAlign = RHA_CENTER; break;
/*?*/       case AlignRight:    eRectHorAlign = RHA_RIGHT;  break;
/*N*/   }
/*N*/
/*N*/   GetFont() = rFormat.GetFont(FNT_MATH);
/*N*/     //GetFont().SetCharSet(RTL_TEXTENCODING_SYMBOL);
/*N*/     DBG_ASSERT( GetFont().GetCharSet() == RTL_TEXTENCODING_UNICODE,
/*N*/             "unexpected CharSet" );
/*N*/   GetFont().SetWeight(WEIGHT_NORMAL);
/*N*/   GetFont().SetItalic(ITALIC_NONE);
/*N*/
/*N*/   SmNode *pNode;
/*N*/   USHORT      nSize = GetNumSubNodes();
/*N*/   for (USHORT i = 0; i < nSize; i++)
/*N*/       if (pNode = GetSubNode(i))
/*N*/           pNode->Prepare(rFormat, rDocShell);
/*N*/ }


//STRIP001 void  SmNode::ToggleDebug() const
//STRIP001  // toggle 'bIsDebug' in current subtree
//STRIP001 {
//STRIP001 #if OSL_DEBUG_LEVEL > 1
//STRIP001  SmNode *pThis = (SmNode *) this;
//STRIP001
//STRIP001  pThis->bIsDebug = bIsDebug ? FALSE : TRUE;
//STRIP001
//STRIP001  SmNode *pNode;
//STRIP001  USHORT      nSize = GetNumSubNodes();
//STRIP001  for (USHORT i = 0; i < nSize; i++)
//STRIP001      if (pNode = pThis->GetSubNode(i))
//STRIP001          pNode->ToggleDebug();
//STRIP001 #endif
//STRIP001 }


#ifdef MAC
#pragma segment FrmNode_02

#else

#endif


/*N*/ void SmNode::Move(const Point& rPosition)
/*N*/ {
/*N*/   if (rPosition.X() == 0  &&  rPosition.Y() == 0)
/*N*/       return;
/*N*/
/*N*/   SmRect::Move(rPosition);
/*N*/
/*N*/   SmNode *pNode;
/*N*/   USHORT  nSize = GetNumSubNodes();
/*N*/   for (USHORT i = 0;  i < nSize;  i++)
/*N*/       if (pNode = GetSubNode(i))
/*N*/           pNode->Move(rPosition);
/*N*/ }


/*N*/ void SmNode::Arrange(const OutputDevice &rDev, const SmFormat &rFormat)
/*N*/ {
/*N*/   SmNode *pNode;
/*N*/   USHORT  nSize = GetNumSubNodes();
/*N*/   for (USHORT i = 0;  i < nSize;  i++)
/*N*/       if (pNode = GetSubNode(i))
/*N*/           pNode->Arrange(rDev, rFormat);
/*N*/ }

/*N*/ void SmNode::CreateTextFromNode(String &rText)
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  SmNode *pNode;
//STRIP001  USHORT  nSize = GetNumSubNodes();
//STRIP001  if (nSize > 1)
//STRIP001      rText.Append('{');
//STRIP001  for (USHORT i = 0;  i < nSize;  i++)
//STRIP001      if (pNode = GetSubNode(i))
//STRIP001          pNode->CreateTextFromNode(rText);
//STRIP001  if (nSize > 1)
//STRIP001  {
//STRIP001      rText.EraseTrailingChars();
//STRIP001      APPEND(rText,"} ");
//STRIP001  }
/*N*/ }


/*N*/ void SmNode::AdaptToX(const OutputDevice &rDev, ULONG nWidth)
/*N*/ {
/*N*/ }


/*N*/ void SmNode::AdaptToY(const OutputDevice &rDev, ULONG nHeight)
/*N*/ {
/*N*/ }


/*N*/ void SmNode::Draw(OutputDevice &rDev, const Point &rPosition) const
/*N*/ {
/*N*/   if (IsPhantom())
/*N*/       return;
/*N*/
/*N*/   const SmNode *pNode;
/*N*/   USHORT  nSize = GetNumSubNodes();
/*N*/   for (USHORT i = 0; i < nSize; i++)
/*N*/       if (pNode = GetSubNode(i))
/*N*/       {   Point  aOffset (pNode->GetTopLeft() - GetTopLeft());
/*N*/           pNode->Draw(rDev, rPosition + aOffset);
/*N*/       }
/*N*/
/*N*/ #ifdef SM_RECT_DEBUG
/*N*/   if (!IsDebug())
/*N*/       return;
/*N*/
/*N*/   int  nRFlags = SM_RECT_CORE | SM_RECT_ITALIC | SM_RECT_LINES | SM_RECT_MID;
/*N*/   SmRect::Draw(rDev, rPosition, nRFlags);
/*N*/ #endif
/*N*/ }

/*N*/ const SmNode * SmNode::FindTokenAt(USHORT nRow, USHORT nCol) const
/*N*/   // returns (first) ** visible ** (sub)node with the tokens text at
/*N*/   // position 'nRow', 'nCol'.
/*N*/   //! (there should be exactly one such node if any)
/*N*/ {
/*N*/   if (    IsVisible()
/*N*/       &&  nRow == GetToken().nRow
/*N*/       &&  nCol >= GetToken().nCol  &&  nCol < GetToken().nCol + GetToken().aText.Len())
/*N*/       return this;
/*N*/   else
/*N*/   {
/*N*/       USHORT  nNumSubNodes = GetNumSubNodes();
/*N*/       for (USHORT  i = 0;  i < nNumSubNodes;  i++)
/*N*/       {   const SmNode *pNode = GetSubNode(i);
/*N*/
/*N*/           if (!pNode)
/*N*/               continue;
/*N*/
/*N*/           const SmNode *pResult = pNode->FindTokenAt(nRow, nCol);
/*N*/           if (pResult)
/*N*/               return pResult;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return 0;
/*N*/ }


//STRIP001 const SmNode * SmNode::FindRectClosestTo(const Point &rPoint) const
//STRIP001 {
//STRIP001  long          nDist   = LONG_MAX;
//STRIP001  const SmNode *pResult = 0;
//STRIP001
//STRIP001  if (IsVisible())
//STRIP001      pResult = this;
//STRIP001  else
//STRIP001  {
//STRIP001      USHORT  nNumSubNodes = GetNumSubNodes();
//STRIP001      for (USHORT  i = 0;  i < nNumSubNodes;  i++)
//STRIP001      {   const SmNode *pNode = GetSubNode(i);
//STRIP001
//STRIP001          if (!pNode)
//STRIP001              continue;
//STRIP001
//STRIP001          long  nTmp;
//STRIP001          const SmNode *pFound = pNode->FindRectClosestTo(rPoint);
//STRIP001          if (pFound  &&  (nTmp = pFound->OrientedDist(rPoint)) < nDist)
//STRIP001          {   nDist   = nTmp;
//STRIP001              pResult = pFound;
//STRIP001
//STRIP001              // quit immediately if 'rPoint' is inside the *should not
//STRIP001              // overlap with other rectangles* part.
//STRIP001              // This (partly) serves for getting the attributes in eg
//STRIP001              // "bar overstrike a".
//STRIP001              // ('nDist < 0' is used as *quick shot* to avoid evaluation of
//STRIP001              // the following expression, where the result is already determined)
//STRIP001              if (nDist < 0  &&  pFound->IsInsideRect(rPoint))
//STRIP001                  break;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return pResult;
//STRIP001 }

//STRIP001 void SmNode::GetAccessibleText( String &rText ) const
//STRIP001 {
//STRIP001     DBG_ERROR( "SmNode: GetAccessibleText not overloaded" );
//STRIP001 }

//STRIP001 const SmNode * SmNode::FindNodeWithAccessibleIndex(xub_StrLen nAccIndex) const
//STRIP001 {
//STRIP001  const SmNode *pResult = 0;
//STRIP001
//STRIP001     sal_Int32 nIdx = GetAccessibleIndex();
//STRIP001     String aTxt;
//STRIP001     if (nIdx >= 0)
//STRIP001         GetAccessibleText( aTxt );  // get text if used in following 'if' statement
//STRIP001
//STRIP001     if (nIdx >= 0
//STRIP001         &&  nIdx <= nAccIndex  &&  nAccIndex < nIdx + aTxt.Len())
//STRIP001      pResult = this;
//STRIP001  else
//STRIP001  {
//STRIP001      USHORT  nNumSubNodes = GetNumSubNodes();
//STRIP001      for (USHORT  i = 0;  i < nNumSubNodes;  i++)
//STRIP001         {
//STRIP001             const SmNode *pNode = GetSubNode(i);
//STRIP001          if (!pNode)
//STRIP001              continue;
//STRIP001
//STRIP001             pResult = pNode->FindNodeWithAccessibleIndex(nAccIndex);
//STRIP001             if (pResult)
//STRIP001                 return pResult;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return pResult;
//STRIP001 }

///////////////////////////////////////////////////////////////////////////

//STRIP001 SmStructureNode::SmStructureNode( const SmStructureNode &rNode ) :
//STRIP001     SmNode( rNode.GetType(), rNode.GetToken() )
//STRIP001 {
//STRIP001     ULONG i;
//STRIP001     for (i = 0;  i < aSubNodes.GetSize();  i++)
//STRIP001         delete aSubNodes.Get(i);
//STRIP001     aSubNodes.Clear();
//STRIP001
//STRIP001     ULONG nSize = rNode.aSubNodes.GetSize();
//STRIP001     aSubNodes.SetSize( nSize );
//STRIP001     for (i = 0;  i < nSize;  ++i)
//STRIP001     {
//STRIP001         SmNode *pNode = rNode.aSubNodes.Get(i);
//STRIP001         aSubNodes.Put( i, pNode ? new SmNode( *pNode ) : 0 );
//STRIP001     }
//STRIP001 }


/*N*/ SmStructureNode::~SmStructureNode()
/*N*/ {
/*N*/   SmNode *pNode;
/*N*/
/*N*/   for (USHORT i = 0;  i < GetNumSubNodes();  i++)
/*N*/       if (pNode = GetSubNode(i))
/*N*/           delete pNode;
/*N*/ }


//STRIP001 SmStructureNode & SmStructureNode::operator = ( const SmStructureNode &rNode )
//STRIP001 {
//STRIP001     SmNode::operator = ( rNode );
//STRIP001
//STRIP001     ULONG i;
//STRIP001     for (i = 0;  i < aSubNodes.GetSize();  i++)
//STRIP001         delete aSubNodes.Get(i);
//STRIP001     aSubNodes.Clear();
//STRIP001
//STRIP001     ULONG nSize = rNode.aSubNodes.GetSize();
//STRIP001     aSubNodes.SetSize( nSize );
//STRIP001     for (i = 0;  i < nSize;  ++i)
//STRIP001     {
//STRIP001         SmNode *pNode = rNode.aSubNodes.Get(i);
//STRIP001         aSubNodes.Put( i, pNode ? new SmNode( *pNode ) : 0 );
//STRIP001     }
//STRIP001
//STRIP001     return *this;
//STRIP001 }


/*N*/ void SmStructureNode::SetSubNodes(SmNode *pFirst, SmNode *pSecond, SmNode *pThird)
/*N*/ {
/*N*/   if (pFirst)
/*N*/       aSubNodes.Put(0, pFirst);
/*N*/   if (pSecond)
/*N*/       aSubNodes.Put(1, pSecond);
/*N*/   if (pThird)
/*N*/       aSubNodes.Put(2, pThird);
/*N*/ }


/*N*/ void SmStructureNode::SetSubNodes(const SmNodeArray &rNodeArray)
/*N*/ {
/*N*/   aSubNodes = rNodeArray;
/*N*/ }


/*N*/ BOOL SmStructureNode::IsVisible() const
/*N*/ {
/*N*/   return FALSE;
/*N*/ }


/*N*/ USHORT SmStructureNode::GetNumSubNodes() const
/*N*/ {
/*N*/   return (USHORT) aSubNodes.GetSize();
/*N*/ }


/*N*/ SmNode * SmStructureNode::GetSubNode(USHORT nIndex)
/*N*/ {
/*N*/   return aSubNodes.Get(nIndex);
/*N*/ }


//STRIP001 void SmStructureNode::GetAccessibleText( String &rText ) const
//STRIP001 {
//STRIP001     USHORT nNodes = GetNumSubNodes();
//STRIP001     for (USHORT i = 0;  i < nNodes;  ++i)
//STRIP001     {
//STRIP001         const SmNode *pNode = ((SmStructureNode *) this)->GetSubNode(i);
//STRIP001         if (pNode)
//STRIP001         {
//STRIP001             if (pNode->IsVisible())
//STRIP001                 ((SmStructureNode *) pNode)->nAccIndex = rText.Len();
//STRIP001             pNode->GetAccessibleText( rText );
//STRIP001 //            if (rText.Len()  &&  ' ' != rText.GetChar( rText.Len() - 1 ))
//STRIP001 //                rText += String::CreateFromAscii( " " );
//STRIP001         }
//STRIP001     }
//STRIP001 }

///////////////////////////////////////////////////////////////////////////


/*N*/ BOOL SmVisibleNode::IsVisible() const
/*N*/ {
/*N*/   return TRUE;
/*N*/ }


/*N*/ USHORT SmVisibleNode::GetNumSubNodes() const
/*N*/ {
/*N*/   return 0;
/*N*/ }


//STRIP001 SmNode * SmVisibleNode::GetSubNode(USHORT nIndex)
//STRIP001 {
//STRIP001  return NULL;
//STRIP001 }


///////////////////////////////////////////////////////////////////////////

//STRIP001 void SmGraphicNode::GetAccessibleText( String &rText ) const
//STRIP001 {
//STRIP001     rText += GetToken().aText;
//STRIP001 }

///////////////////////////////////////////////////////////////////////////


//STRIP001 void SmExpressionNode::CreateTextFromNode(String &rText)
//STRIP001 {
//STRIP001  SmNode *pNode;
//STRIP001  USHORT  nSize = GetNumSubNodes();
//STRIP001  if (nSize > 1)
//STRIP001      rText.Append('{');
//STRIP001  for (USHORT i = 0;  i < nSize;  i++)
//STRIP001      if (pNode = GetSubNode(i))
//STRIP001      {
//STRIP001          pNode->CreateTextFromNode(rText);
//STRIP001          //Just a bit of foo to make unary +asd -asd +-asd -+asd look nice
//STRIP001          if (pNode->GetType() == NMATH)
//STRIP001              if ((nSize != 2) || ((rText.GetChar(rText.Len()-1) != '+') &&
//STRIP001                  (rText.GetChar(rText.Len()-1) != '-')))
//STRIP001                  rText.Append(' ');
//STRIP001      }
//STRIP001
//STRIP001  if (nSize > 1)
//STRIP001  {
//STRIP001      rText.EraseTrailingChars();
//STRIP001      APPEND(rText,"} ");
//STRIP001  }
//STRIP001 }


///////////////////////////////////////////////////////////////////////////

/*N*/ void SmTableNode::Arrange(const OutputDevice &rDev, const SmFormat &rFormat)
/*N*/   // arranges all subnodes in one column
/*N*/ {
/*N*/   Point rPosition;
/*N*/
/*N*/   USHORT  nWidth  = 0;
/*N*/   USHORT  nHeight = 0;
/*N*/   SmNode *pNode;
/*N*/   USHORT  nSize   = GetNumSubNodes();
/*N*/
/*N*/   // make distance depend on font size
/*N*/   long  nDist = +(rFormat.GetDistance(DIS_VERTICAL)
/*N*/                   * GetFont().GetSize().Height()) / 100L;
/*N*/
/*N*/   if (nSize < 1)
/*N*/       return;
/*N*/
/*N*/   // arrange subnodes and get maximum width of them
/*N*/   long  nMaxWidth = 0,
/*N*/         nTmp;
/*N*/     USHORT i;
/*N*/   for (i = 0; i < nSize;  i++)
/*N*/       if (pNode = GetSubNode(i))
/*N*/       {   pNode->Arrange(rDev, rFormat);
/*N*/           if ((nTmp = pNode->GetItalicWidth()) > nMaxWidth)
/*N*/               nMaxWidth = nTmp;
/*N*/       }
/*N*/
/*N*/   Point  aPos;
/*N*/   SmRect::operator = (SmRect(nMaxWidth, 0));
/*N*/   for (i = 0;  i < nSize;  i++)
/*N*/   {   if (pNode = GetSubNode(i))
/*N*/       {   const SmRect &rNodeRect = pNode->GetRect();
/*N*/           const SmNode *pCoNode   = pNode->GetLeftMost();
/*N*/           SmTokenType   eType     = pCoNode->GetToken().eType;
/*N*/             RectHorAlign  eHorAlign = pCoNode->GetRectHorAlign();
/*N*/
/*N*/           aPos = rNodeRect.AlignTo(*this, RP_BOTTOM,
/*N*/                       eHorAlign, RVA_BASELINE);
/*N*/           if (i)
/*N*/               aPos.Y() += nDist;
/*N*/           pNode->MoveTo(aPos);
/*N*/           ExtendBy(rNodeRect, nSize > 1 ? RCP_NONE : RCP_ARG);
/*N*/       }
/*N*/   }
/*N*/ }


//STRIP001 SmNode * SmTableNode::GetLeftMost()
//STRIP001 {
//STRIP001  return this;
//STRIP001 }


/**************************************************************************/


/*N*/ void SmLineNode::Prepare(const SmFormat &rFormat, const SmDocShell &rDocShell)
/*N*/ {
/*N*/   SmNode::Prepare(rFormat, rDocShell);
/*N*/
/*N*/   //! wir verwenden hier den 'FNT_VARIABLE' Font, da er vom Ascent und Descent
/*N*/   //! ia besser zum Rest der Formel passt als der 'FNT_MATH' Font.
/*N*/   GetFont() = rFormat.GetFont(FNT_VARIABLE);
/*N*/   Flags() |= FLG_FONT;
/*N*/ }


/**************************************************************************/


/*N*/ void SmLineNode::Arrange(const OutputDevice &rDev, const SmFormat &rFormat)
/*N*/   // arranges all subnodes in one row with some extra space between
/*N*/ {
/*N*/   SmNode *pNode;
/*N*/   USHORT  nSize = GetNumSubNodes();
/*N*/   USHORT i;
/*N*/   for (i = 0; i < nSize;  i++)
/*N*/       if (pNode = GetSubNode(i))
/*N*/           pNode->Arrange(rDev, rFormat);
/*N*/
/*N*/     SmTmpDevice  aTmpDev ((OutputDevice &) rDev, TRUE);
/*N*/   aTmpDev.SetFont(GetFont());
/*N*/
/*N*/   // provide an empty rectangle with alignment parameters for the "current"
/*N*/   // font (in order to make "a^1 {}_2^3 a_4" work correct, that is, have the
/*N*/   // same sub-/supscript positions.)
/*N*/   //! be sure to use a character that has explicitly defined HiAttribut
/*N*/   //! line in rect.cxx such as 'a' in order to make 'vec a' look same to
/*N*/   //! 'vec {a}'.
/*N*/   SmRect::operator = (SmRect(aTmpDev, &rFormat, C2S("a"),
/*N*/                              GetFont().GetBorderWidth()));
/*N*/   // make sure that the rectangle occupies (almost) no space
/*N*/   SetWidth(1);
/*N*/   SetItalicSpaces(0, 0);
/*N*/
/*N*/   if (nSize < 1)
/*N*/       return;
/*N*/
/*N*/   // make distance depend on font size
/*N*/   long  nDist = +(rFormat.GetDistance(DIS_HORIZONTAL)
/*N*/                   * GetFont().GetSize().Height()) / 100L;
/*N*/
/*N*/   Point   aPos;
/*N*/   for (i = 0;  i < nSize;  i++)
/*N*/       if (pNode = GetSubNode(i))
/*N*/       {
/*N*/           aPos = pNode->AlignTo(*this, RP_RIGHT, RHA_CENTER, RVA_BASELINE);
/*N*/
/*N*/           // no horizontal space before first node
/*N*/           if (i)
/*N*/               aPos.X() += nDist;
/*N*/
/*N*/           pNode->MoveTo(aPos);
/*N*/             ExtendBy( *pNode, RCP_XOR );
/*N*/       }
/*N*/ }


/**************************************************************************/


/*N*/ void SmExpressionNode::Arrange(const OutputDevice &rDev, const SmFormat &rFormat)
/*N*/   // as 'SmLineNode::Arrange' but keeps alignment of leftmost subnode
/*N*/ {
/*N*/   DBG_ASSERT(GetNumSubNodes() > 0, "Sm: keine subnodes");
/*N*/
/*N*/   SmLineNode::Arrange(rDev, rFormat);
/*N*/
/*N*/   //  copy alignment of leftmost subnode if any
/*N*/     SmNode *pNode = GetLeftMost();
/*N*/   if (pNode)
/*N*/         SetRectHorAlign(pNode->GetRectHorAlign(), FALSE);
/*N*/ }


/**************************************************************************/


/*N*/ void SmUnHorNode::Arrange(const OutputDevice &rDev, const SmFormat &rFormat)
/*N*/ {
/*N*/   BOOL  bIsPostfix = GetToken().eType == TFACT;
/*N*/
/*N*/   SmNode *pOper = GetSubNode(bIsPostfix ? 1 : 0),
/*N*/          *pBody = GetSubNode(bIsPostfix ? 0 : 1);
/*N*/   DBG_ASSERT(pOper, "Sm: NULL pointer");
/*N*/   DBG_ASSERT(pBody, "Sm: NULL pointer");
/*N*/
/*N*/   pOper->SetSize(Fraction (rFormat.GetRelSize(SIZ_OPERATOR), 100));
/*N*/   pOper->Arrange(rDev, rFormat);
/*N*/   pBody->Arrange(rDev, rFormat);
/*N*/
/*N*/   Point  aPos = pOper->AlignTo(*pBody, bIsPostfix ? RP_RIGHT : RP_LEFT,
/*N*/                       RHA_CENTER, RVA_BASELINE);
/*N*/   // add a bit space between operator and argument
/*N*/   // (worst case -{1 over 2} where - and over have almost no space inbetween)
/*N*/   long  nDelta = pOper->GetFont().GetSize().Height() / 20;
/*N*/   if (bIsPostfix)
/*N*/       aPos.X() += nDelta;
/*N*/   else
/*N*/       aPos.X() -= nDelta;
/*N*/   pOper->MoveTo(aPos);
/*N*/
/*N*/   SmRect::operator = (*pBody);
/*N*/   long  nOldBot = GetBottom();
/*N*/
/*N*/   ExtendBy(*pOper, RCP_XOR);
/*N*/
/*N*/   // workaround for Bug 50865: "a^2 a^+2" have different baselines
/*N*/   // for exponents (if size of exponent is large enough)
/*N*/   SetBottom(nOldBot);
/*N*/ }


/**************************************************************************/


/*N*/ void SmRootNode::GetHeightVerOffset(const SmRect &rRect,
/*N*/                                   long &rHeight, long &rVerOffset) const
/*N*/   // calculate height and vertical offset of root sign suitable for 'rRect'
/*N*/ {
/*N*/   rVerOffset = (rRect.GetBottom() - rRect.GetAlignB()) / 2;
/*N*/   rHeight    = rRect.GetHeight() - rVerOffset;
/*N*/
/*N*/   DBG_ASSERT(rHeight    >= 0, "Sm : Ooops...");
/*N*/   DBG_ASSERT(rVerOffset >= 0, "Sm : Ooops...");
/*N*/ }


/*N*/ Point SmRootNode::GetExtraPos(const SmRect &rRootSymbol,
/*N*/                             const SmRect &rExtra) const
/*N*/ {
/*N*/   const Size &rSymSize = rRootSymbol.GetSize();
/*N*/
/*N*/   Point  aPos = rRootSymbol.GetTopLeft()
/*N*/           + Point((rSymSize.Width()  * 70) / 100,
/*N*/                   (rSymSize.Height() * 52) / 100);
/*N*/
/*N*/   // from this calculate topleft edge of 'rExtra'
/*N*/   aPos.X() -= rExtra.GetWidth() + rExtra.GetItalicRightSpace();
/*N*/   aPos.Y() -= rExtra.GetHeight();
/*N*/   // if there's enough space move a bit less to the right
/*N*/   // examples: "nroot i a", "nroot j a"
/*N*/   // (it looks better if we don't use italic-spaces here)
/*N*/   long  nX = rRootSymbol.GetLeft() + (rSymSize.Width() * 30) / 100;
/*N*/   if (aPos.X() > nX)
/*?*/       aPos.X() = nX;
/*N*/
/*N*/   return aPos;
/*N*/ }


/*N*/ void SmRootNode::Arrange(const OutputDevice &rDev, const SmFormat &rFormat)
/*N*/ {
/*N*/   //! pExtra needs to have the smaller index than pRootSym in order to
/*N*/   //! not to get the root symbol but the pExtra when clicking on it in the
/*N*/   //! GraphicWindow. (That is because of the simplicity of the algorithm
/*N*/   //! that finds the node corresponding to a mouseclick in the window.)
/*N*/   SmNode *pExtra   = GetSubNode(0),
/*N*/          *pRootSym = GetSubNode(1),
/*N*/          *pBody    = GetSubNode(2);
/*N*/   DBG_ASSERT(pRootSym, "Sm: NULL pointer");
/*N*/   DBG_ASSERT(pBody,    "Sm: NULL pointer");
/*N*/
/*N*/   pBody->Arrange(rDev, rFormat);
/*N*/
/*N*/   long  nHeight,
/*N*/         nVerOffset;
/*N*/   GetHeightVerOffset(*pBody, nHeight, nVerOffset);
/*N*/   nHeight += rFormat.GetDistance(DIS_ROOT)
/*N*/              * GetFont().GetSize().Height() / 100L;
/*N*/
/*N*/     // font specialist advised to change the width first
/*N*/     pRootSym->AdaptToY(rDev, nHeight);
/*N*/   pRootSym->AdaptToX(rDev, pBody->GetItalicWidth());
/*N*/
/*N*/   pRootSym->Arrange(rDev, rFormat);
/*N*/
/*N*/   Point  aPos = pRootSym->AlignTo(*pBody, RP_LEFT, RHA_CENTER, RVA_BASELINE);
/*N*/   //! overrride calulated vertical position
/*N*/   aPos.Y()  = pRootSym->GetTop() + pBody->GetBottom() - pRootSym->GetBottom();
/*N*/   aPos.Y() -= nVerOffset;
/*N*/   pRootSym->MoveTo(aPos);
/*N*/
/*N*/   if (pExtra)
/*N*/   {   pExtra->SetSize(Fraction(rFormat.GetRelSize(SIZ_INDEX), 100));
/*N*/       pExtra->Arrange(rDev, rFormat);
/*N*/
/*N*/       aPos = GetExtraPos(*pRootSym, *pExtra);
/*N*/       pExtra->MoveTo(aPos);
/*N*/   }
/*N*/
/*N*/   SmRect::operator = (*pBody);
/*N*/   ExtendBy(*pRootSym, RCP_THIS);
/*N*/   if (pExtra)
/*N*/       ExtendBy(*pExtra, RCP_THIS, (BOOL) TRUE);
/*N*/ }


//STRIP001 void SmRootNode::CreateTextFromNode(String &rText)
//STRIP001 {
//STRIP001  SmNode *pExtra = GetSubNode(0);
//STRIP001  if (pExtra)
//STRIP001  {
//STRIP001      APPEND(rText,"nroot ");
//STRIP001      pExtra->CreateTextFromNode(rText);
//STRIP001  }
//STRIP001  else
//STRIP001      APPEND(rText,"sqrt ");
//STRIP001  GetSubNode(2)->CreateTextFromNode(rText);
//STRIP001 }


/**************************************************************************/


/*N*/ void SmBinHorNode::Arrange(const OutputDevice &rDev, const SmFormat &rFormat)
/*N*/ {
/*N*/   SmNode *pLeft  = GetSubNode(0),
/*N*/          *pOper  = GetSubNode(1),
/*N*/          *pRight = GetSubNode(2);
/*N*/   DBG_ASSERT(pLeft  != NULL, "Sm: NULL pointer");
/*N*/   DBG_ASSERT(pOper  != NULL, "Sm: NULL pointer");
/*N*/   DBG_ASSERT(pRight != NULL, "Sm: NULL pointer");
/*N*/
/*N*/   pOper->SetSize(Fraction (rFormat.GetRelSize(SIZ_OPERATOR), 100));
/*N*/
/*N*/   pLeft ->Arrange(rDev, rFormat);
/*N*/   pOper ->Arrange(rDev, rFormat);
/*N*/     pRight->Arrange(rDev, rFormat);
/*N*/
/*N*/   const SmRect &rOpRect = pOper->GetRect();
/*N*/
/*N*/   long nDist = (rOpRect.GetWidth() *
/*N*/                rFormat.GetDistance(DIS_HORIZONTAL)) / 100L;
/*N*/
/*N*/   SmRect::operator = (*pLeft);
/*N*/
/*N*/   Point aPos;
/*N*/   aPos = pOper->AlignTo(*this, RP_RIGHT, RHA_CENTER, RVA_BASELINE);
/*N*/   aPos.X() += nDist;
/*N*/   pOper->MoveTo(aPos);
/*N*/   ExtendBy(*pOper, RCP_XOR);
/*N*/
/*N*/   aPos = pRight->AlignTo(*this, RP_RIGHT, RHA_CENTER, RVA_BASELINE);
/*N*/   aPos.X() += nDist;
/*N*/
/*N*/   pRight->MoveTo(aPos);
/*N*/   ExtendBy(*pRight, RCP_XOR);
/*N*/ }


/**************************************************************************/


/*N*/ void SmBinVerNode::Arrange(const OutputDevice &rDev, const SmFormat &rFormat)
/*N*/ {
/*N*/   SmNode *pNum   = GetSubNode(0),
/*N*/          *pLine  = GetSubNode(1),
/*N*/          *pDenom = GetSubNode(2);
/*N*/   DBG_ASSERT(pNum,   "Sm : NULL pointer");
/*N*/   DBG_ASSERT(pLine,  "Sm : NULL pointer");
/*N*/   DBG_ASSERT(pDenom, "Sm : NULL pointer");
/*N*/
/*N*/   BOOL  bIsTextmode = rFormat.IsTextmode();
/*N*/   if (bIsTextmode)
/*N*/   {
/*?*/       Fraction  aFraction(rFormat.GetRelSize(SIZ_INDEX), 100);
/*?*/       pNum  ->SetSize(aFraction);
/*?*/       pLine ->SetSize(aFraction);
/*?*/       pDenom->SetSize(aFraction);
/*N*/   }
/*N*/
/*N*/   pNum  ->Arrange(rDev, rFormat);
/*N*/   pDenom->Arrange(rDev, rFormat);
/*N*/
/*N*/   long  nFontHeight = GetFont().GetSize().Height(),
/*N*/         nExtLen     = nFontHeight * rFormat.GetDistance(DIS_FRACTION) / 100L,
/*N*/         nThick      = nFontHeight * rFormat.GetDistance(DIS_STROKEWIDTH) / 100L,
/*N*/         nWidth      = Max(pNum->GetItalicWidth(), pDenom->GetItalicWidth()),
/*N*/         nNumDist    = bIsTextmode ? 0 :
/*N*/                           nFontHeight * rFormat.GetDistance(DIS_NUMERATOR)   / 100L,
/*N*/         nDenomDist  = bIsTextmode ? 0 :
/*N*/                           nFontHeight * rFormat.GetDistance(DIS_DENOMINATOR) / 100L;
/*N*/
    // font specialist advised to change the width first
/*N*/     pLine->AdaptToY(rDev, nThick);
/*N*/   pLine->AdaptToX(rDev, nWidth + 2 * nExtLen);
/*N*/   pLine->Arrange(rDev, rFormat);
/*N*/
/*N*/   // get horizontal alignment for numerator
/*N*/   const SmNode *pLM       = pNum->GetLeftMost();
/*N*/     RectHorAlign  eHorAlign = pLM->GetRectHorAlign();
/*N*/
/*N*/   // move numerator to its position
/*N*/   Point  aPos = pNum->AlignTo(*pLine, RP_TOP, eHorAlign, RVA_BASELINE);
/*N*/   aPos.Y() -= nNumDist;
/*N*/   pNum->MoveTo(aPos);
/*N*/
/*N*/   // get horizontal alignment for denominator
/*N*/   pLM       = pDenom->GetLeftMost();
/*N*/     eHorAlign = pLM->GetRectHorAlign();
/*N*/
/*N*/   // move denominator to its position
/*N*/   aPos = pDenom->AlignTo(*pLine, RP_BOTTOM, eHorAlign, RVA_BASELINE);
/*N*/   aPos.Y() += nDenomDist;
/*N*/   pDenom->MoveTo(aPos);
/*N*/
/*N*/   SmRect::operator = (*pNum);
/*N*/   ExtendBy(*pDenom, RCP_NONE).ExtendBy(*pLine, RCP_NONE, pLine->GetCenterY());
/*N*/ }

//STRIP001 void SmBinVerNode::CreateTextFromNode(String &rText)
//STRIP001 {
//STRIP001  SmNode *pNum   = GetSubNode(0),
//STRIP001         *pLine  = GetSubNode(1),
//STRIP001         *pDenom = GetSubNode(2);
//STRIP001  pNum->CreateTextFromNode(rText);
//STRIP001  APPEND(rText,"over ");
//STRIP001  pDenom->CreateTextFromNode(rText);
//STRIP001 }


/*N*/ SmNode * SmBinVerNode::GetLeftMost()
/*N*/ {
/*N*/   return this;
/*N*/ }


/**************************************************************************/


//STRIP001 double Det(const Point &rHeading1, const Point &rHeading2)
//STRIP001  // gibt den Wert der durch die beiden Punkte gebildeten Determinante
//STRIP001  // zurück
//STRIP001 {
//STRIP001  return rHeading1.X() * rHeading2.Y() - rHeading1.Y() * rHeading2.X();
//STRIP001 }


//STRIP001 BOOL IsPointInLine(const Point &rPoint1,
//STRIP001                 const Point &rPoint2, const Point &rHeading2)
//STRIP001  // ergibt TRUE genau dann, wenn der Punkt 'rPoint1' zu der Gerade gehört die
//STRIP001  // durch den Punkt 'rPoint2' geht und den Richtungsvektor 'rHeading2' hat
//STRIP001 {
//STRIP001  DBG_ASSERT(rHeading2 != Point(), "Sm : 0 vector");
//STRIP001
//STRIP001  BOOL bRes = FALSE;
//STRIP001  const double eps = 5.0 * DBL_EPSILON;
//STRIP001
//STRIP001  double fLambda;
//STRIP001  if (labs(rHeading2.X()) > labs(rHeading2.Y()))
//STRIP001  {
//STRIP001      fLambda = (rPoint1.X() - rPoint2.X()) / (double) rHeading2.X();
//STRIP001      bRes = fabs(rPoint1.Y() - (rPoint2.Y() + fLambda * rHeading2.Y())) < eps;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      fLambda = (rPoint1.Y() - rPoint2.Y()) / (double) rHeading2.Y();
//STRIP001      bRes = fabs(rPoint1.X() - (rPoint2.X() + fLambda * rHeading2.X())) < eps;
//STRIP001  }
//STRIP001
//STRIP001  return bRes;
//STRIP001 }


//STRIP001 USHORT GetLineIntersectionPoint(Point &rResult,
//STRIP001                              const Point& rPoint1, const Point &rHeading1,
//STRIP001                              const Point& rPoint2, const Point &rHeading2)
//STRIP001 {
//STRIP001  DBG_ASSERT(rHeading1 != Point(), "Sm : 0 vector");
//STRIP001  DBG_ASSERT(rHeading2 != Point(), "Sm : 0 vector");
//STRIP001
//STRIP001  USHORT nRes = 1;
//STRIP001  const double eps = 5.0 * DBL_EPSILON;
//STRIP001
//STRIP001  // sind die Richtumgsvektoren linear abhängig ?
//STRIP001  double  fDet = Det(rHeading1, rHeading2);
//STRIP001  if (fabs(fDet) < eps)
//STRIP001  {
//STRIP001      nRes    = IsPointInLine(rPoint1, rPoint2, rHeading2) ? USHRT_MAX : 0;
//STRIP001      rResult = nRes ? rPoint1 : Point();
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      // hier achten wir nicht auf Rechengenauigkeit
//STRIP001      // (das würde aufwendiger und lohnt sich hier kaum)
//STRIP001      double fLambda = (    (rPoint1.Y() - rPoint2.Y()) * rHeading2.X()
//STRIP001                          - (rPoint1.X() - rPoint2.X()) * rHeading2.Y())
//STRIP001                       / fDet;
//STRIP001      rResult = Point(rPoint1.X() + (long) (fLambda * rHeading1.X()),
//STRIP001                      rPoint1.Y() + (long) (fLambda * rHeading1.Y()));
//STRIP001  }
//STRIP001
//STRIP001  return nRes;
//STRIP001 }



//STRIP001 SmBinDiagonalNode::SmBinDiagonalNode(const SmToken &rNodeToken)
//STRIP001 :    SmStructureNode(NBINDIAGONAL, rNodeToken)
//STRIP001 {
//STRIP001  bAscending = FALSE;
//STRIP001  SetNumSubNodes(3);
//STRIP001 }


//STRIP001 void SmBinDiagonalNode::GetOperPosSize(Point &rPos, Size &rSize,
//STRIP001                      const Point &rDiagPoint, double fAngleDeg) const
//STRIP001  // gibt die Position und Größe für den Diagonalstrich zurück.
//STRIP001  // Vor.: das SmRect des Nodes gibt die Begrenzung vor(!), muß also selbst
//STRIP001  //      bereits bekannt sein.
//STRIP001
//STRIP001 {
//STRIP001  const double  fPi   = 3.1415926535897932384626433;
//STRIP001  double  fAngleRad   = fAngleDeg / 180.0 * fPi;
//STRIP001  long    nRectLeft   = GetItalicLeft(),
//STRIP001          nRectRight  = GetItalicRight(),
//STRIP001          nRectTop    = GetTop(),
//STRIP001          nRectBottom = GetBottom();
//STRIP001  Point   aRightHdg     (100, 0),
//STRIP001          aDownHdg      (0, 100),
//STRIP001          aDiagHdg      ( (long)(100.0 * cos(fAngleRad)),
//STRIP001                          (long)(-100.0 * sin(fAngleRad)) );
//STRIP001
//STRIP001  long  nLeft, nRight, nTop, nBottom;     // Ränder des Rechtecks für die
//STRIP001                                          // Diagonale
//STRIP001  Point aPoint;
//STRIP001  if (IsAscending())
//STRIP001  {
//STRIP001      //
//STRIP001      // obere rechte Ecke bestimmen
//STRIP001      //
//STRIP001      GetLineIntersectionPoint(aPoint,
//STRIP001          Point(nRectLeft, nRectTop), aRightHdg,
//STRIP001          rDiagPoint, aDiagHdg);
//STRIP001      //
//STRIP001      // gibt es einen Schnittpunkt mit dem oberen Rand ?
//STRIP001      if (aPoint.X() <= nRectRight)
//STRIP001      {
//STRIP001          nRight = aPoint.X();
//STRIP001          nTop   = nRectTop;
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          // es mu?einen Schnittpunkt mit dem rechten Rand geben!
//STRIP001          GetLineIntersectionPoint(aPoint,
//STRIP001              Point(nRectRight, nRectTop), aDownHdg,
//STRIP001              rDiagPoint, aDiagHdg);
//STRIP001
//STRIP001          nRight = nRectRight;
//STRIP001          nTop   = aPoint.Y();
//STRIP001      }
//STRIP001
//STRIP001      //
//STRIP001      // untere linke Ecke bestimmen
//STRIP001      //
//STRIP001      GetLineIntersectionPoint(aPoint,
//STRIP001          Point(nRectLeft, nRectBottom), aRightHdg,
//STRIP001          rDiagPoint, aDiagHdg);
//STRIP001      //
//STRIP001      // gibt es einen Schnittpunkt mit dem unteren Rand ?
//STRIP001      if (aPoint.X() >= nRectLeft)
//STRIP001      {
//STRIP001          nLeft   = aPoint.X();
//STRIP001          nBottom = nRectBottom;
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          // es mu?einen Schnittpunkt mit dem linken Rand geben!
//STRIP001          GetLineIntersectionPoint(aPoint,
//STRIP001              Point(nRectLeft, nRectTop), aDownHdg,
//STRIP001              rDiagPoint, aDiagHdg);
//STRIP001
//STRIP001          nLeft   = nRectLeft;
//STRIP001          nBottom = aPoint.Y();
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      //
//STRIP001      // obere linke Ecke bestimmen
//STRIP001      //
//STRIP001      GetLineIntersectionPoint(aPoint,
//STRIP001          Point(nRectLeft, nRectTop), aRightHdg,
//STRIP001          rDiagPoint, aDiagHdg);
//STRIP001      //
//STRIP001      // gibt es einen Schnittpunkt mit dem oberen Rand ?
//STRIP001      if (aPoint.X() >= nRectLeft)
//STRIP001      {
//STRIP001          nLeft = aPoint.X();
//STRIP001          nTop  = nRectTop;
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          // es mu?einen Schnittpunkt mit dem linken Rand geben!
//STRIP001          GetLineIntersectionPoint(aPoint,
//STRIP001              Point(nRectLeft, nRectTop), aDownHdg,
//STRIP001              rDiagPoint, aDiagHdg);
//STRIP001
//STRIP001          nLeft = nRectLeft;
//STRIP001          nTop  = aPoint.Y();
//STRIP001      }
//STRIP001
//STRIP001      //
//STRIP001      // untere rechte Ecke bestimmen
//STRIP001      //
//STRIP001      GetLineIntersectionPoint(aPoint,
//STRIP001          Point(nRectLeft, nRectBottom), aRightHdg,
//STRIP001          rDiagPoint, aDiagHdg);
//STRIP001      //
//STRIP001      // gibt es einen Schnittpunkt mit dem unteren Rand ?
//STRIP001      if (aPoint.X() <= nRectRight)
//STRIP001      {
//STRIP001          nRight  = aPoint.X();
//STRIP001          nBottom = nRectBottom;
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          // es mu?einen Schnittpunkt mit dem rechten Rand geben!
//STRIP001          GetLineIntersectionPoint(aPoint,
//STRIP001              Point(nRectRight, nRectTop), aDownHdg,
//STRIP001              rDiagPoint, aDiagHdg);
//STRIP001
//STRIP001          nRight  = nRectRight;
//STRIP001          nBottom = aPoint.Y();
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  rSize = Size(nRight - nLeft + 1, nBottom - nTop + 1);
//STRIP001  rPos.X() = nLeft;
//STRIP001  rPos.Y() = nTop;
//STRIP001 }


//STRIP001 void SmBinDiagonalNode::Arrange(const OutputDevice &rDev, const SmFormat &rFormat)
//STRIP001 {
//STRIP001  //! die beiden Argumente müssen in den Subnodes vor dem Operator kommen,
//STRIP001  //! damit das anklicken im GraphicWindow den FormulaCursor richtig setzt
//STRIP001  //! (vgl SmRootNode)
//STRIP001  SmNode *pLeft  = GetSubNode(0),
//STRIP001         *pRight = GetSubNode(1);
//STRIP001  DBG_ASSERT(pLeft, "Sm : NULL pointer");
//STRIP001  DBG_ASSERT(pRight, "Sm : NULL pointer");
//STRIP001
//STRIP001  DBG_ASSERT(GetSubNode(2)->GetType() == NPOLYLINE, "Sm : falscher Nodetyp");
//STRIP001  SmPolyLineNode *pOper = (SmPolyLineNode *) GetSubNode(2);
//STRIP001  DBG_ASSERT(pOper, "Sm : NULL pointer");
//STRIP001
//STRIP001  //! some routines being called extract some info from the OutputDevice's
//STRIP001  //! font (eg the space to be used for borders OR the font name(!!)).
//STRIP001  //! Thus the font should reflect the needs and has to be set!
//STRIP001     SmTmpDevice  aTmpDev ((OutputDevice &) rDev, TRUE);
//STRIP001  aTmpDev.SetFont(GetFont());
//STRIP001
//STRIP001  pLeft->Arrange(aTmpDev, rFormat);
//STRIP001  pRight->Arrange(aTmpDev, rFormat);
//STRIP001
//STRIP001  // implizit die Weite (incl Rand) des Diagonalstrichs ermitteln
//STRIP001  pOper->Arrange(aTmpDev, rFormat);
//STRIP001
//STRIP001  long nDelta = pOper->GetWidth() * 8 / 10;
//STRIP001
//STRIP001  // TopLeft Position vom rechten Argument ermitteln
//STRIP001  Point aPos;
//STRIP001  aPos.X() = pLeft->GetItalicRight() + nDelta + pRight->GetItalicLeftSpace();
//STRIP001  if (IsAscending())
//STRIP001      aPos.Y() = pLeft->GetBottom() + nDelta;
//STRIP001  else
//STRIP001      aPos.Y() = pLeft->GetTop() - nDelta - pRight->GetHeight();
//STRIP001
//STRIP001  pRight->MoveTo(aPos);
//STRIP001
//STRIP001  // neue Baseline bestimmen
//STRIP001  long nBaseline = IsAscending() ? (pLeft->GetBottom() + pRight->GetTop()) / 2
//STRIP001                      : (pLeft->GetTop() + pRight->GetBottom()) / 2;
//STRIP001  Point  aLogCenter ((pLeft->GetItalicRight() + pRight->GetItalicLeft()) / 2,
//STRIP001                     nBaseline);
//STRIP001
//STRIP001  SmRect::operator = (*pLeft);
//STRIP001  ExtendBy(*pRight, RCP_NONE);
//STRIP001
//STRIP001
//STRIP001  // Position und Größe des Diagonalstrich ermitteln
//STRIP001  Size  aSize;
//STRIP001  GetOperPosSize(aPos, aSize, aLogCenter, IsAscending() ? 60.0 : -60.0);
//STRIP001
//STRIP001     // font specialist advised to change the width first
//STRIP001     pOper->AdaptToY(aTmpDev, aSize.Height());
//STRIP001     pOper->AdaptToX(aTmpDev, aSize.Width());
//STRIP001  // und diese wirksam machen
//STRIP001  pOper->Arrange(aTmpDev, rFormat);
//STRIP001
//STRIP001  pOper->MoveTo(aPos);
//STRIP001
//STRIP001  ExtendBy(*pOper, RCP_NONE, nBaseline);
//STRIP001 }


/**************************************************************************/


/*N*/ void SmSubSupNode::Arrange(const OutputDevice &rDev, const SmFormat &rFormat)
/*N*/ {
/*N*/   DBG_ASSERT(GetNumSubNodes() == 1 + SUBSUP_NUM_ENTRIES,
/*N*/              "Sm: falsche Anzahl von subnodes");
/*N*/
/*N*/   SmNode *pBody = GetBody();
/*N*/   DBG_ASSERT(pBody, "Sm: NULL pointer");
/*N*/
/*N*/   long  nOrigHeight = pBody->GetFont().GetSize().Height();
/*N*/
/*N*/   pBody->Arrange(rDev, rFormat);
/*N*/
/*N*/   const SmRect &rBodyRect = pBody->GetRect();
/*N*/   SmRect::operator = (rBodyRect);
/*N*/
/*N*/   // line that separates sub- and supscript rectangles
/*N*/   long  nDelimLine = SmFromTo(GetAlignB(), GetAlignT(), 0.4);
/*N*/
/*N*/   Point  aPos;
/*N*/   long   nDelta, nDist;
/*N*/
/*N*/   // iterate over all possible sub-/supscripts
/*N*/   SmRect  aTmpRect (rBodyRect);
/*N*/   for (int i = 0;  i < SUBSUP_NUM_ENTRIES;  i++)
/*N*/   {   SmSubSup  eSubSup = (SmSubSup) i;   // cast
/*N*/       SmNode *pSubSup = GetSubSup(eSubSup);
/*N*/
/*N*/       if (!pSubSup)
/*N*/           continue;
/*N*/
/*N*/       // switch position of limits if we are in textmode
/*N*/       if (rFormat.IsTextmode()  &&  (GetToken().nGroup & TGLIMIT))
/*N*/           switch (eSubSup)
/*?*/           {   case CSUB:  eSubSup = RSUB;     break;
/*?*/               case CSUP:  eSubSup = RSUP;     break;
/*N*/           }
/*N*/
/*N*/       // prevent sub-/supscripts from diminishing in size
/*N*/       // (as would be in "a_{1_{2_{3_4}}}")
/*N*/       if (GetFont().GetSize().Height() > rFormat.GetBaseSize().Height() / 3)
/*N*/       {
/*N*/           USHORT nIndex = (eSubSup == CSUB  ||  eSubSup == CSUP) ?
/*N*/                                   SIZ_LIMITS : SIZ_INDEX;
/*N*/           Fraction  aFraction ( rFormat.GetRelSize(nIndex), 100 );
/*N*/           pSubSup->SetSize(aFraction);
/*N*/       }
/*N*/
/*N*/       pSubSup->Arrange(rDev, rFormat);
/*N*/
/*N*/       BOOL  bIsTextmode = rFormat.IsTextmode();
/*N*/       nDist = 0;
/*N*/
/*N*/       //! be sure that CSUB, CSUP are handled before the other cases!
/*N*/       switch (eSubSup)
/*N*/       {   case RSUB :
/*N*/           case LSUB :
/*N*/               if (!bIsTextmode)
/*N*/                   nDist = nOrigHeight
/*N*/                           * rFormat.GetDistance(DIS_SUBSCRIPT) / 100L;
/*N*/               aPos  = pSubSup->GetRect().AlignTo(aTmpRect,
/*N*/                               eSubSup == LSUB ? RP_LEFT : RP_RIGHT,
/*N*/                               RHA_CENTER, RVA_BOTTOM);
/*N*/               aPos.Y() += nDist;
/*N*/               nDelta = nDelimLine - aPos.Y();
/*N*/               if (nDelta > 0)
/*N*/                   aPos.Y() += nDelta;
/*N*/               break;
/*N*/           case RSUP :
/*N*/           case LSUP :
/*N*/               if (!bIsTextmode)
/*N*/                   nDist = nOrigHeight
/*N*/                           * rFormat.GetDistance(DIS_SUPERSCRIPT) / 100L;
/*N*/               aPos  = pSubSup->GetRect().AlignTo(aTmpRect,
/*N*/                               eSubSup == LSUP ? RP_LEFT : RP_RIGHT,
/*N*/                               RHA_CENTER, RVA_TOP);
/*N*/               aPos.Y() -= nDist;
/*N*/               nDelta = aPos.Y() + pSubSup->GetHeight() - nDelimLine;
/*N*/               if (nDelta > 0)
/*?*/                   aPos.Y() -= nDelta;
/*N*/               break;
/*N*/           case CSUB :
/*N*/               if (!bIsTextmode)
/*N*/                   nDist = nOrigHeight
/*N*/                           * rFormat.GetDistance(DIS_LOWERLIMIT) / 100L;
/*N*/               aPos = pSubSup->GetRect().AlignTo(rBodyRect, RP_BOTTOM,
/*N*/                               RHA_CENTER, RVA_BASELINE);
/*N*/               aPos.Y() += nDist;
/*N*/               break;
/*N*/           case CSUP :
/*N*/               if (!bIsTextmode)
/*N*/                   nDist = nOrigHeight
/*N*/                           * rFormat.GetDistance(DIS_UPPERLIMIT) / 100L;
/*N*/               aPos = pSubSup->GetRect().AlignTo(rBodyRect, RP_TOP,
/*N*/                               RHA_CENTER, RVA_BASELINE);
/*N*/               aPos.Y() -= nDist;
/*N*/               break;
/*N*/           default :
/*N*/               DBG_ASSERT(FALSE, "Sm: unbekannter Fall");
/*N*/       }
/*N*/
/*N*/       pSubSup->MoveTo(aPos);
/*N*/       ExtendBy(*pSubSup, RCP_THIS, (BOOL) TRUE);
/*N*/
/*N*/       // update rectangle to which  RSUB, RSUP, LSUB, LSUP
/*N*/       // will be aligned to
/*N*/       if (eSubSup == CSUB  ||  eSubSup == CSUP)
/*N*/           aTmpRect = *this;
/*N*/   }
/*N*/ }

//STRIP001 void SmSubSupNode::CreateTextFromNode(String &rText)
//STRIP001 {
//STRIP001  SmNode *pNode;
//STRIP001  GetSubNode(0)->CreateTextFromNode(rText);
//STRIP001
//STRIP001  if (pNode = GetSubNode(LSUB+1))
//STRIP001  {
//STRIP001      APPEND(rText,"lsub ");
//STRIP001      pNode->CreateTextFromNode(rText);
//STRIP001  }
//STRIP001  if (pNode = GetSubNode(LSUP+1))
//STRIP001  {
//STRIP001      APPEND(rText,"lsup ");
//STRIP001      pNode->CreateTextFromNode(rText);
//STRIP001  }
//STRIP001  if (pNode = GetSubNode(CSUB+1))
//STRIP001  {
//STRIP001      APPEND(rText,"csub ");
//STRIP001      pNode->CreateTextFromNode(rText);
//STRIP001  }
//STRIP001  if (pNode = GetSubNode(CSUP+1))
//STRIP001  {
//STRIP001      APPEND(rText,"csup ");
//STRIP001      pNode->CreateTextFromNode(rText);
//STRIP001  }
//STRIP001  if (pNode = GetSubNode(RSUB+1))
//STRIP001  {
//STRIP001      rText.EraseTrailingChars();
//STRIP001      rText.Append('_');
//STRIP001      pNode->CreateTextFromNode(rText);
//STRIP001  }
//STRIP001  if (pNode = GetSubNode(RSUP+1))
//STRIP001  {
//STRIP001      rText.EraseTrailingChars();
//STRIP001      rText.Append('^');
//STRIP001      pNode->CreateTextFromNode(rText);
//STRIP001  }
//STRIP001 }


/**************************************************************************/

//STRIP001 void SmBraceNode::CreateTextFromNode(String &rText)
//STRIP001 {
//STRIP001  if (GetScaleMode() == SCALE_HEIGHT)
//STRIP001      APPEND(rText,"left ");
//STRIP001     {
//STRIP001         String aStr;
//STRIP001      GetSubNode(0)->CreateTextFromNode(aStr);
//STRIP001         aStr.EraseLeadingAndTrailingChars();
//STRIP001         aStr.EraseLeadingChars('\\');
//STRIP001         if (aStr.Len())
//STRIP001         {
//STRIP001             if (aStr.EqualsAscii("divides"))
//STRIP001                 APPEND(rText,"lline");
//STRIP001             else if (aStr.EqualsAscii("parallel"))
//STRIP001                 APPEND(rText,"ldline");
//STRIP001             else if (aStr.EqualsAscii("<"))
//STRIP001                 APPEND(rText,"langle");
//STRIP001             else
//STRIP001                 rText.Append(aStr);
//STRIP001          rText.Append(' ');
//STRIP001         }
//STRIP001         else
//STRIP001             APPEND(rText,"none ");
//STRIP001     }
//STRIP001  GetSubNode(1)->CreateTextFromNode(rText);
//STRIP001  if (GetScaleMode() == SCALE_HEIGHT)
//STRIP001      APPEND(rText,"right ");
//STRIP001     {
//STRIP001         String aStr;
//STRIP001      GetSubNode(2)->CreateTextFromNode(aStr);
//STRIP001         aStr.EraseLeadingAndTrailingChars();
//STRIP001         aStr.EraseLeadingChars('\\');
//STRIP001         if (aStr.Len())
//STRIP001         {
//STRIP001             if (aStr.EqualsAscii("divides"))
//STRIP001                 APPEND(rText,"rline");
//STRIP001             else if (aStr.EqualsAscii("parallel"))
//STRIP001                 APPEND(rText,"rdline");
//STRIP001             else if (aStr.EqualsAscii(">"))
//STRIP001                 APPEND(rText,"rangle");
//STRIP001             else
//STRIP001                 rText.Append(aStr);
//STRIP001          rText.Append(' ');
//STRIP001         }
//STRIP001         else
//STRIP001             APPEND(rText,"none ");
//STRIP001     }
//STRIP001  rText.Append(' ');
//STRIP001
//STRIP001 }

/*N*/ void SmBraceNode::Arrange(const OutputDevice &rDev, const SmFormat &rFormat)
/*N*/ {
/*N*/   SmNode *pLeft  = GetSubNode(0),
/*N*/          *pBody  = GetSubNode(1),
/*N*/          *pRight = GetSubNode(2);
/*N*/   DBG_ASSERT(pLeft,  "Sm: NULL pointer");
/*N*/   DBG_ASSERT(pBody,  "Sm: NULL pointer");
/*N*/   DBG_ASSERT(pRight, "Sm: NULL pointer");
/*N*/
/*N*/   pBody->Arrange(rDev, rFormat);
/*N*/
/*N*/   BOOL  bIsScaleNormal = rFormat.IsScaleNormalBrackets(),
/*N*/         bScale         = pBody->GetHeight() > 0  &&
/*N*/                          (GetScaleMode() == SCALE_HEIGHT  ||  bIsScaleNormal),
/*N*/         bIsABS         = GetToken().eType == TABS;
/*N*/
/*N*/   long  nFaceHeight = GetFont().GetSize().Height();
/*N*/
/*N*/   // Übergröße in % ermitteln
/*N*/   USHORT  nPerc = 0;
/*N*/   if (!bIsABS && bScale)
/*N*/   {   // im Fall von Klammern mit Übergröße...
/*N*/       int  nIndex = GetScaleMode() == SCALE_HEIGHT ?
/*N*/                           DIS_BRACKETSIZE : DIS_NORMALBRACKETSIZE;
/*N*/       nPerc = rFormat.GetDistance(nIndex);
/*N*/   }
/*N*/
/*N*/   // ermitteln der Höhe für die Klammern
/*N*/   long  nBraceHeight;
/*N*/   if (bScale)
/*N*/   {
/*N*/       nBraceHeight = pBody->GetType() == NBRACEBODY ?
/*N*/                             ((SmBracebodyNode *) pBody)->GetBodyHeight()
/*N*/                           : pBody->GetHeight();
/*N*/       nBraceHeight += 2 * (nBraceHeight * nPerc / 100L);
/*N*/   }
/*N*/   else
/*N*/       nBraceHeight = nFaceHeight;
/*N*/
/*N*/   // Abstand zum Argument
/*N*/   nPerc = bIsABS ? 0 : rFormat.GetDistance(DIS_BRACKETSPACE);
/*N*/   long  nDist = nFaceHeight * nPerc / 100L;
/*N*/
/*N*/   // sofern erwünscht skalieren der Klammern auf die gewünschte Größe
/*N*/   if (bScale)
/*N*/   {
/*N*/       Size  aSize (pLeft->GetFont().GetSize());
/*N*/       DBG_ASSERT(pRight->GetFont().GetSize() == aSize,
/*N*/                   "Sm : unterschiedliche Fontgrößen");
/*N*/       aSize.Width() = Min((long) nBraceHeight * 60L / 100L,
/*N*/                           rFormat.GetBaseSize().Height() * 3L / 2L);
/*N*/         // correction factor since change from StarMath to StarSymbol font
/*N*/         // because of the different font width in the FontMetric
/*N*/         aSize.Width() *= 182;
/*N*/         aSize.Width() /= 267;
/*N*/
/*N*/       xub_Unicode cChar = pLeft->GetToken().cMathChar;
/*N*/       if (cChar != MS_LINE  &&  cChar != MS_DLINE)
/*N*/           pLeft ->GetFont().SetSize(aSize);
/*N*/
/*N*/       cChar = pRight->GetToken().cMathChar;
/*N*/       if (cChar != MS_LINE  &&  cChar != MS_DLINE)
/*N*/           pRight->GetFont().SetSize(aSize);
/*N*/
/*N*/       pLeft ->AdaptToY(rDev, nBraceHeight);
/*N*/       pRight->AdaptToY(rDev, nBraceHeight);
/*N*/   }
/*N*/
/*N*/   pLeft ->Arrange(rDev, rFormat);
/*N*/   pRight->Arrange(rDev, rFormat);
/*N*/
/*N*/   // damit auch "\(a\) - (a) - left ( a right )" vernünftig aussieht
/*N*/   RectVerAlign  eVerAlign = bScale ? RVA_CENTERY : RVA_BASELINE;
/*N*/
/*N*/   Point         aPos;
/*N*/   aPos = pLeft->AlignTo(*pBody, RP_LEFT, RHA_CENTER, eVerAlign);
/*N*/   aPos.X() -= nDist;
/*N*/   pLeft->MoveTo(aPos);
/*N*/
/*N*/   aPos = pRight->AlignTo(*pBody, RP_RIGHT, RHA_CENTER, eVerAlign);
/*N*/   aPos.X() += nDist;
/*N*/   pRight->MoveTo(aPos);
/*N*/
/*N*/   SmRect::operator = (*pBody);
/*N*/   ExtendBy(*pLeft, RCP_THIS).ExtendBy(*pRight, RCP_THIS);
/*N*/ }


/**************************************************************************/


/*N*/ void SmBracebodyNode::Arrange(const OutputDevice &rDev, const SmFormat &rFormat)
/*N*/ {
/*N*/   USHORT  nNumSubNodes = GetNumSubNodes();
/*N*/   if (nNumSubNodes == 0)
/*N*/       return;
/*N*/
/*N*/   // arrange arguments
/*N*/   USHORT i;
/*N*/   for (i = 0;  i < nNumSubNodes;  i += 2)
/*N*/       GetSubNode(i)->Arrange(rDev, rFormat);
/*N*/
/*N*/   // build reference rectangle with necessary info for vertical alignment
/*N*/   SmRect  aRefRect (*GetSubNode(0));
/*N*/   for (i = 0;  i < nNumSubNodes;  i += 2)
/*N*/   {
/*N*/       SmRect aTmpRect (*GetSubNode(i));
/*N*/       Point  aPos = aTmpRect.AlignTo(aRefRect, RP_RIGHT, RHA_CENTER, RVA_BASELINE);
/*N*/       aTmpRect.MoveTo(aPos);
/*N*/       aRefRect.ExtendBy(aTmpRect, RCP_XOR);
/*N*/   }
/*N*/
/*N*/   nBodyHeight = aRefRect.GetHeight();
/*N*/
/*N*/   // scale separators to required height and arrange them
/*N*/   BOOL bScale  = GetScaleMode() == SCALE_HEIGHT  ||  rFormat.IsScaleNormalBrackets();
/*N*/   long nHeight = bScale ? aRefRect.GetHeight() : GetFont().GetSize().Height();
/*N*/   int  nIndex  = GetScaleMode() == SCALE_HEIGHT ?
/*N*/                       DIS_BRACKETSIZE : DIS_NORMALBRACKETSIZE;
/*N*/   USHORT nPerc   = rFormat.GetDistance(nIndex);
/*N*/   if (bScale)
/*N*/       nHeight += 2 * (nHeight * nPerc / 100L);
/*N*/   for (i = 1;  i < nNumSubNodes;  i += 2)
/*N*/   {
/*?*/       SmNode *pNode = GetSubNode(i);
/*?*/       pNode->AdaptToY(rDev, nHeight);
/*?*/       pNode->Arrange(rDev, rFormat);
/*N*/   }
/*N*/
/*N*/   // horizontal distance between argument and brackets or separators
/*N*/   long  nDist = GetFont().GetSize().Height()
/*N*/                 * rFormat.GetDistance(DIS_BRACKETSPACE) / 100L;
/*N*/
/*N*/   SmNode *pLeft = GetSubNode(0);
/*N*/   SmRect::operator = (*pLeft);
/*N*/   for (i = 1;  i < nNumSubNodes;  i++)
/*N*/   {
/*?*/       BOOL          bIsSeparator = i % 2 != 0;
/*?*/       RectVerAlign  eVerAlign    = bIsSeparator ? RVA_CENTERY : RVA_BASELINE;
/*?*/
/*?*/       SmNode *pRight = GetSubNode(i);
/*?*/       Point  aPosX = pRight->AlignTo(*pLeft,   RP_RIGHT, RHA_CENTER, eVerAlign),
/*?*/              aPosY = pRight->AlignTo(aRefRect, RP_RIGHT, RHA_CENTER, eVerAlign);
/*?*/       aPosX.X() += nDist;
/*?*/
/*?*/       pRight->MoveTo(Point(aPosX.X(), aPosY.Y()));
/*?*/       ExtendBy(*pRight, bIsSeparator ? RCP_THIS : RCP_XOR);
/*?*/
/*?*/       pLeft = pRight;
/*N*/   }
/*N*/ }


/**************************************************************************/


//STRIP001 void SmVerticalBraceNode::Arrange(const OutputDevice &rDev, const SmFormat &rFormat)
//STRIP001 {
//STRIP001  SmNode *pBody   = GetSubNode(0),
//STRIP001         *pBrace  = GetSubNode(1),
//STRIP001         *pScript = GetSubNode(2);
//STRIP001  DBG_ASSERT(pBody,   "Sm: NULL pointer!");
//STRIP001  DBG_ASSERT(pBrace,  "Sm: NULL pointer!");
//STRIP001  DBG_ASSERT(pScript, "Sm: NULL pointer!");
//STRIP001
//STRIP001     SmTmpDevice  aTmpDev ((OutputDevice &) rDev, TRUE);
//STRIP001  aTmpDev.SetFont(GetFont());
//STRIP001
//STRIP001  pBody->Arrange(aTmpDev, rFormat);
//STRIP001
//STRIP001  // Groesse wie bei Grenzen fuer diesen Teil
//STRIP001  pScript->SetSize( Fraction( rFormat.GetRelSize(SIZ_LIMITS), 100 ) );
//STRIP001  // etwas hoehere Klammern als normal
//STRIP001  pBrace ->SetSize( Fraction(3, 2) );
//STRIP001
//STRIP001  long  nItalicWidth = pBody->GetItalicWidth();
//STRIP001  if (nItalicWidth > 0)
//STRIP001      pBrace->AdaptToX(aTmpDev, nItalicWidth);
//STRIP001
//STRIP001  pBrace ->Arrange(aTmpDev, rFormat);
//STRIP001  pScript->Arrange(aTmpDev, rFormat);
//STRIP001
//STRIP001  // die relativen Position und die Abstaende zueinander bestimmen
//STRIP001  RectPos  eRectPos;
//STRIP001  long nFontHeight = pBody->GetFont().GetSize().Height();
//STRIP001  long nDistBody   = nFontHeight * rFormat.GetDistance(DIS_ORNAMENTSIZE),
//STRIP001       nDistScript = nFontHeight;
//STRIP001  if (GetToken().eType == TOVERBRACE)
//STRIP001  {
//STRIP001      eRectPos = RP_TOP;
//STRIP001      nDistBody    = - nDistBody;
//STRIP001      nDistScript *= - rFormat.GetDistance(DIS_UPPERLIMIT);
//STRIP001  }
//STRIP001  else // TUNDERBRACE
//STRIP001  {
//STRIP001      eRectPos = RP_BOTTOM;
//STRIP001      nDistScript *= + rFormat.GetDistance(DIS_LOWERLIMIT);
//STRIP001  }
//STRIP001  nDistBody   /= 100L;
//STRIP001  nDistScript /= 100L;
//STRIP001
//STRIP001  Point  aPos = pBrace->AlignTo(*pBody, eRectPos, RHA_CENTER, RVA_BASELINE);
//STRIP001  aPos.Y() += nDistBody;
//STRIP001  pBrace->MoveTo(aPos);
//STRIP001
//STRIP001  aPos = pScript->AlignTo(*pBrace, eRectPos, RHA_CENTER, RVA_BASELINE);
//STRIP001  aPos.Y() += nDistScript;
//STRIP001  pScript->MoveTo(aPos);
//STRIP001
//STRIP001  SmRect::operator = (*pBody);
//STRIP001  ExtendBy(*pBrace, RCP_THIS).ExtendBy(*pScript, RCP_THIS);
//STRIP001 }


/**************************************************************************/

#ifdef MAC
#pragma segment FrmNode_03
#endif


/*N*/ SmNode * SmOperNode::GetSymbol()
/*N*/ {
/*N*/   SmNode *pNode = GetSubNode(0);
/*N*/   DBG_ASSERT(pNode, "Sm: NULL pointer!");
/*N*/
/*N*/   if (pNode->GetType() == NSUBSUP)
/*N*/       pNode = ((SmSubSupNode *) pNode)->GetBody();
/*N*/
/*N*/   DBG_ASSERT(pNode, "Sm: NULL pointer!");
/*N*/   return pNode;
/*N*/ }


/*N*/ long SmOperNode::CalcSymbolHeight(const SmNode &rSymbol,
/*N*/                                 const SmFormat &rFormat) const
/*N*/   // returns the font height to be used for operator-symbol
/*N*/ {
/*N*/   long  nHeight = GetFont().GetSize().Height();
/*N*/
/*N*/   SmTokenType  eType = GetToken().eType;
/*N*/   if (eType == TLIM  ||  eType == TLIMINF ||  eType == TLIMSUP)
/*N*/       return nHeight;
/*N*/
/*N*/   if (!rFormat.IsTextmode())
/*N*/   {
/*N*/       // set minimum size ()
/*N*/       nHeight += (nHeight * 20L) / 100L;
/*N*/
/*N*/       nHeight += nHeight
/*N*/                  * rFormat.GetDistance(DIS_OPERATORSIZE) / 100L;
/*N*/       nHeight = nHeight * 686L / 845L;
/*N*/   }
/*N*/
/*N*/     // correct user-defined symbols to match height of sum from used font
/*N*/   if (rSymbol.GetToken().eType == TSPECIAL)
/*?*/       nHeight = nHeight * 845L / 686L;
/*N*/
/*N*/   return nHeight;
/*N*/ }


/*N*/ void SmOperNode::Arrange(const OutputDevice &rDev, const SmFormat &rFormat)
/*N*/ {
/*N*/   SmNode *pOper = GetSubNode(0);
/*N*/   SmNode *pBody = GetSubNode(1);
/*N*/
/*N*/   DBG_ASSERT(pOper, "Sm: Subnode fehlt");
/*N*/   DBG_ASSERT(pBody, "Sm: Subnode fehlt");
/*N*/
/*N*/   SmNode *pSymbol = GetSymbol();
/*N*/   pSymbol->SetSize(Fraction(CalcSymbolHeight(*pSymbol, rFormat),
/*N*/                             pSymbol->GetFont().GetSize().Height()));
/*N*/
/*N*/   pBody->Arrange(rDev, rFormat);
/*N*/   pOper->Arrange(rDev, rFormat);
/*N*/
/*N*/   long  nOrigHeight = GetFont().GetSize().Height(),
/*N*/         nDist = nOrigHeight
/*N*/                 * rFormat.GetDistance(DIS_OPERATORSPACE) / 100L;
/*N*/
/*N*/   Point aPos = pOper->AlignTo(*pBody, RP_LEFT, RHA_CENTER, /*RVA_CENTERY*/RVA_MID);
/*N*/   aPos.X() -= nDist;
/*N*/   pOper->MoveTo(aPos);
/*N*/
/*N*/   SmRect::operator = (*pBody);
/*N*/   ExtendBy(*pOper, RCP_THIS);
/*N*/ }


/**************************************************************************/


//STRIP001 void SmAlignNode::Arrange(const OutputDevice &rDev, const SmFormat &rFormat)
//STRIP001  // setzt im ganzen subtree (incl aktuellem node) das alignment
//STRIP001 {
//STRIP001  DBG_ASSERT(GetNumSubNodes() > 0, "Sm: SubNode fehlt");
//STRIP001
//STRIP001  SmNode  *pNode = GetSubNode(0);
//STRIP001
//STRIP001  RectHorAlign  eHorAlign;
//STRIP001  switch (GetToken().eType)
//STRIP001  {
//STRIP001      case TALIGNL:   eHorAlign = RHA_LEFT;   break;
//STRIP001      case TALIGNC:   eHorAlign = RHA_CENTER; break;
//STRIP001      case TALIGNR:   eHorAlign = RHA_RIGHT;  break;
//STRIP001  }
//STRIP001  SetRectHorAlign(eHorAlign);
//STRIP001
//STRIP001  pNode->Arrange(rDev, rFormat);
//STRIP001
//STRIP001  SmRect::operator = (pNode->GetRect());
//STRIP001 }


/**************************************************************************/


/*N*/ void SmAttributNode::Arrange(const OutputDevice &rDev, const SmFormat &rFormat)
/*N*/ {
/*N*/   SmNode *pAttr = GetSubNode(0),
/*N*/          *pBody = GetSubNode(1);
/*N*/   DBG_ASSERT(pBody, "Sm: Body fehlt");
/*N*/   DBG_ASSERT(pAttr, "Sm: Attribut fehlt");
/*N*/
/*N*/   pBody->Arrange(rDev, rFormat);
/*N*/
/*N*/   if (GetScaleMode() == SCALE_WIDTH)
/*?*/       pAttr->AdaptToX(rDev, pBody->GetItalicWidth());
/*N*/   pAttr->Arrange(rDev, rFormat);
/*N*/
/*N*/   // get relative position of attribut
/*N*/   RectVerAlign  eVerAlign;
/*N*/   long          nDist = 0;
/*N*/   switch (GetToken().eType)
/*N*/   {   case TUNDERLINE :
/*?*/           eVerAlign = RVA_ATTRIBUT_LO;
/*?*/           break;
/*N*/       case TOVERSTRIKE :
/*?*/           eVerAlign = RVA_ATTRIBUT_MID;
/*?*/           break;
/*N*/       default :
/*N*/           eVerAlign = RVA_ATTRIBUT_HI;
/*N*/           if (pBody->GetType() == NATTRIBUT)
/*?*/               nDist = GetFont().GetSize().Height()
/*?*/                       * rFormat.GetDistance(DIS_ORNAMENTSPACE) / 100L;
/*N*/   }
/*N*/   Point  aPos = pAttr->AlignTo(*pBody, RP_ATTRIBUT, RHA_CENTER, eVerAlign);
/*N*/   aPos.Y() -= nDist;
/*N*/   pAttr->MoveTo(aPos);
/*N*/
/*N*/   SmRect::operator = (*pBody);
/*N*/   ExtendBy(*pAttr, RCP_THIS, (BOOL) TRUE);
/*N*/ }


/**************************************************************************/




//STRIP001 void SmFontNode::CreateTextFromNode(String &rText)
//STRIP001 {
//STRIP001  switch (GetToken().eType)
//STRIP001  {
//STRIP001      case TBOLD:
//STRIP001          APPEND(rText,"bold ");
//STRIP001          break;
//STRIP001      case TNBOLD:
//STRIP001          APPEND(rText,"nbold ");
//STRIP001          break;
//STRIP001      case TITALIC:
//STRIP001          APPEND(rText,"italic ");
//STRIP001          break;
//STRIP001      case TNITALIC:
//STRIP001          APPEND(rText,"nitalic ");
//STRIP001          break;
//STRIP001      case TPHANTOM:
//STRIP001          APPEND(rText,"phantom ");
//STRIP001          break;
//STRIP001      case TSIZE:
//STRIP001          {
//STRIP001              APPEND(rText,"size ");
//STRIP001              switch (nSizeType)
//STRIP001              {
//STRIP001                  case FNTSIZ_PLUS:
//STRIP001                      rText.Append('+');
//STRIP001                      break;
//STRIP001                  case FNTSIZ_MINUS:
//STRIP001                      rText.Append('-');
//STRIP001                      break;
//STRIP001                  case FNTSIZ_MULTIPLY:
//STRIP001                      rText.Append('*');
//STRIP001                      break;
//STRIP001                  case FNTSIZ_DIVIDE:
//STRIP001                      rText.Append('/');
//STRIP001                      break;
//STRIP001                  case FNTSIZ_ABSOLUT:
//STRIP001                  default:
//STRIP001                      break;
//STRIP001              }
//STRIP001                 rText += String( ::rtl::math::doubleToUString(
//STRIP001                             static_cast<double>(aFontSize),
//STRIP001                             rtl_math_StringFormat_Automatic,
//STRIP001                             rtl_math_DecimalPlaces_Max, '.', sal_True));
//STRIP001              rText.Append(' ');
//STRIP001          }
//STRIP001          break;
//STRIP001      case TBLACK:
//STRIP001          APPEND(rText,"color black ");
//STRIP001          break;
//STRIP001      case TWHITE:
//STRIP001          APPEND(rText,"color white ");
//STRIP001          break;
//STRIP001      case TRED:
//STRIP001          APPEND(rText,"color red ");
//STRIP001          break;
//STRIP001      case TGREEN:
//STRIP001          APPEND(rText,"color green ");
//STRIP001          break;
//STRIP001      case TBLUE:
//STRIP001          APPEND(rText,"color blue ");
//STRIP001          break;
//STRIP001      case TCYAN:
//STRIP001          APPEND(rText,"color cyan ");
//STRIP001          break;
//STRIP001      case TMAGENTA:
//STRIP001          APPEND(rText,"color magenta ");
//STRIP001          break;
//STRIP001      case TYELLOW:
//STRIP001          APPEND(rText,"color yellow ");
//STRIP001          break;
//STRIP001      case TSANS:
//STRIP001          APPEND(rText,"font sans ");
//STRIP001          break;
//STRIP001      case TSERIF:
//STRIP001          APPEND(rText,"font serif ");
//STRIP001          break;
//STRIP001      case TFIXED:
//STRIP001          APPEND(rText,"font fixed ");
//STRIP001          break;
//STRIP001      default:
//STRIP001          break;
//STRIP001  }
//STRIP001  GetSubNode(1)->CreateTextFromNode(rText);
//STRIP001 }


/*N*/ void SmFontNode::Prepare(const SmFormat &rFormat, const SmDocShell &rDocShell)
/*N*/ {
/*N*/   //! prepare subnodes first
/*N*/   SmNode::Prepare(rFormat, rDocShell);
/*N*/
/*N*/   int  nFnt = -1;
/*N*/   switch (GetToken().eType)
/*N*/   {
/*?*/       case TFIXED:    nFnt = FNT_FIXED;   break;
/*N*/       case TSANS:     nFnt = FNT_SANS;    break;
/*?*/       case TSERIF:    nFnt = FNT_SERIF;   break;
/*N*/   }
/*N*/   if (nFnt != -1)
/*N*/   {   GetFont() = rFormat.GetFont(nFnt);
/*N*/       SetFont(GetFont());
/*N*/   }
/*N*/
/*N*/   //! prevent overwrites of this font by 'Arrange' or 'SetFont' calls of
/*N*/   //! other font nodes (those with lower depth in the tree)
/*N*/   Flags() |= FLG_FONT;
/*N*/ }


/*N*/ void SmFontNode::Arrange(const OutputDevice &rDev, const SmFormat &rFormat)
/*N*/ {
/*N*/   SmNode *pNode = GetSubNode(1);
/*N*/   DBG_ASSERT(pNode, "Sm: SubNode fehlt");
/*N*/
/*N*/   switch (GetToken().eType)
/*N*/   {   case TSIZE :
/*N*/           pNode->SetFontSize(aFontSize, nSizeType);
/*N*/           break;
/*N*/       case TSANS :
/*N*/       case TSERIF :
/*N*/       case TFIXED :
/*N*/           pNode->SetFont(GetFont());
/*N*/           break;
/*N*/       case TUNKNOWN : break;  // no assertion on "font <?> <?>"
/*N*/
/*?*/       case TPHANTOM : DBG_ASSERT(0, "STRIP"); break; //STRIP001 SetPhantom(TRUE);             break;
/*N*/       case TBOLD :    SetAttribut(ATTR_BOLD);         break;
/*N*/       case TITALIC :  SetAttribut(ATTR_ITALIC);       break;
/*?*/       case TNBOLD :   ClearAttribut(ATTR_BOLD);       break;
/*N*/       case TNITALIC : ClearAttribut(ATTR_ITALIC);     break;
/*N*/
/*?*/       case TBLACK :   SetColor(Color(COL_BLACK));     break;
/*?*/       case TWHITE :   SetColor(Color(COL_WHITE));     break;
/*?*/       case TRED :     SetColor(Color(COL_RED));       break;
/*?*/       case TGREEN :   SetColor(Color(COL_GREEN));     break;
/*?*/       case TBLUE :    SetColor(Color(COL_BLUE));      break;
/*?*/       case TCYAN :    SetColor(Color(COL_CYAN));      break;
/*?*/       case TMAGENTA : SetColor(Color(COL_MAGENTA));   break;
/*?*/       case TYELLOW :  SetColor(Color(COL_YELLOW));    break;
/*N*/
/*N*/       default:
/*?*/           DBG_ASSERT(FALSE, "Sm: unbekannter Fall");
/*N*/   }
/*N*/
/*N*/   pNode->Arrange(rDev, rFormat);
/*N*/
/*N*/   SmRect::operator = (pNode->GetRect());
/*N*/ }


/*N*/ void SmFontNode::SetSizeParameter(const Fraction& rValue, USHORT Type)
/*N*/ {
/*N*/   nSizeType = Type;
/*N*/   aFontSize = rValue;
/*N*/ }


/**************************************************************************/


/*N*/ SmPolyLineNode::SmPolyLineNode(const SmToken &rNodeToken)
/*N*/ : SmGraphicNode(NPOLYLINE, rNodeToken)
/*N*/ {
/*N*/   aPoly.SetSize(2);
/*N*/   nWidth = 0;
/*N*/ }


/*N*/ void SmPolyLineNode::AdaptToX(const OutputDevice &rDev, ULONG nWidth)
/*N*/ {
/*N*/   aToSize.Width() = nWidth;
/*N*/ }


/*N*/ void SmPolyLineNode::AdaptToY(const OutputDevice &rDev, ULONG nHeight)
/*N*/ {
/*N*/   GetFont().FreezeBorderWidth();
/*N*/   aToSize.Height() = nHeight;
/*N*/ }


/*N*/ void SmPolyLineNode::Arrange(const OutputDevice &rDev, const SmFormat &rFormat)
/*N*/ {
/*N*/   //! some routines being called extract some info from the OutputDevice's
/*N*/   //! font (eg the space to be used for borders OR the font name(!!)).
/*N*/   //! Thus the font should reflect the needs and has to be set!
/*N*/     SmTmpDevice  aTmpDev ((OutputDevice &) rDev, TRUE);
/*N*/   aTmpDev.SetFont(GetFont());
/*N*/
/*N*/   long  nBorderwidth = GetFont().GetBorderWidth();
/*N*/
/*N*/   //
/*N*/   // Das Polygon mit den beiden Endpunkten bilden
/*N*/   //
/*N*/   DBG_ASSERT(aPoly.GetSize() == 2, "Sm : falsche Anzahl von Punkten");
/*N*/   Point  aPointA, aPointB;
/*N*/   if (GetToken().eType == TWIDESLASH)
/*N*/   {
/*N*/       aPointA.X() = nBorderwidth;
/*N*/       aPointA.Y() = aToSize.Height() - nBorderwidth;
/*N*/       aPointB.X() = aToSize.Width() - nBorderwidth;
/*N*/       aPointB.Y() = nBorderwidth;
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       DBG_ASSERT(GetToken().eType == TWIDEBACKSLASH, "Sm : unerwartetes Token");
/*N*/       aPointA.X() =
/*N*/       aPointA.Y() = nBorderwidth;
/*N*/       aPointB.X() = aToSize.Width() - nBorderwidth;
/*N*/       aPointB.Y() = aToSize.Height() - nBorderwidth;
/*N*/   }
/*N*/   aPoly.SetPoint(aPointA, 0);
/*N*/   aPoly.SetPoint(aPointB, 1);
/*N*/
/*N*/   long  nThick       = GetFont().GetSize().Height()
/*N*/                           * rFormat.GetDistance(DIS_STROKEWIDTH) / 100L;
/*N*/   nWidth = nThick + 2 * nBorderwidth;
/*N*/
/*N*/   SmRect::operator = (SmRect(aToSize.Width(), aToSize.Height()));
/*N*/ }


/*N*/ void SmPolyLineNode::Draw(OutputDevice &rDev, const Point &rPosition) const
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  if (IsPhantom())
//STRIP001      return;
//STRIP001
//STRIP001  long nBorderwidth = GetFont().GetBorderWidth();
//STRIP001
//STRIP001  LineInfo  aInfo;
//STRIP001  aInfo.SetWidth(nWidth - 2 * nBorderwidth);
//STRIP001
//STRIP001  Point aOffset (Point() - aPoly.GetBoundRect().TopLeft()
//STRIP001                 + Point(nBorderwidth, nBorderwidth)),
//STRIP001        aPos (rPosition + aOffset);
//STRIP001  ((Polygon &) aPoly).Move(aPos.X(), aPos.Y());
//STRIP001
//STRIP001     SmTmpDevice  aTmpDev ((OutputDevice &) rDev, FALSE);
//STRIP001     aTmpDev.SetLineColor( GetFont().GetColor() );
//STRIP001
//STRIP001     rDev.DrawPolyLine(aPoly, aInfo);
//STRIP001
//STRIP001 #ifdef SM_RECT_DEBUG
//STRIP001  if (!IsDebug())
//STRIP001      return;
//STRIP001
//STRIP001  int  nRFlags = SM_RECT_CORE | SM_RECT_ITALIC | SM_RECT_LINES | SM_RECT_MID;
//STRIP001  SmRect::Draw(rDev, rPosition, nRFlags);
//STRIP001 #endif
/*N*/ }


/**************************************************************************/

/*N*/ void SmRootSymbolNode::AdaptToX(const OutputDevice &rDev, ULONG nWidth)
/*N*/ {
/*N*/     nBodyWidth = nWidth;
/*N*/ }


/*N*/ void SmRootSymbolNode::AdaptToY(const OutputDevice &rDev, ULONG nHeight)
/*N*/ {
/*N*/     // etwas extra Länge damit der horizontale Balken später über dem
/*N*/     // Argument positioniert ist
/*N*/     SmMathSymbolNode::AdaptToY(rDev, nHeight + nHeight / 10L);
/*N*/ }


//STRIP001 void SmRootSymbolNode::Draw(OutputDevice &rDev, const Point &rPosition) const
//STRIP001 {
//STRIP001  if (IsPhantom())
//STRIP001      return;
//STRIP001
//STRIP001  // draw root-sign itself
//STRIP001     SmMathSymbolNode::Draw(rDev, rPosition);
//STRIP001
//STRIP001     static String aBarStr( (sal_Unicode) MS_BAR );
//STRIP001     SmTmpDevice  aTmpDev( (OutputDevice &) rDev, TRUE );
//STRIP001     aTmpDev.SetFillColor(GetFont().GetColor());
//STRIP001     rDev.SetLineColor();
//STRIP001     aTmpDev.SetFont( GetFont() );
//STRIP001
//STRIP001     // since the width is always unscaled it corresponds ot the _original_
//STRIP001     // _unscaled_ font height to be used, we use that to calculate the
//STRIP001     // bar height. Thus it is independent of the arguments height.
//STRIP001     // ( see display of sqrt QQQ versus sqrt stack{Q#Q#Q#Q} )
//STRIP001     long nBarHeight = GetWidth() * 7L / 100L;
//STRIP001     long nBarWidth = nBodyWidth + GetBorderWidth();
//STRIP001     Point aBarOffset( GetWidth(), +GetBorderWidth() );
//STRIP001     Point aBarPos( rPosition + aBarOffset );
//STRIP001
//STRIP001     Rectangle  aBar(aBarPos, Size( nBarWidth, nBarHeight) );
//STRIP001     //! avoid GROWING AND SHRINKING of drawn rectangle when constantly
//STRIP001     //! increasing zoomfactor.
//STRIP001     //  This is done by shifting it's output-position to a point that
//STRIP001     //  corresponds exactly to a pixel on the output device.
//STRIP001     Point  aDrawPos( rDev.PixelToLogic(rDev.LogicToPixel(aBar.TopLeft())) );
//STRIP001     //aDrawPos.X() = aBar.Left();     //! don't change X position
//STRIP001     aBar.SetPos( aDrawPos );
//STRIP001
//STRIP001     rDev.DrawRect( aBar );
//STRIP001
//STRIP001 #ifdef SM_RECT_DEBUG
//STRIP001  if (!IsDebug())
//STRIP001      return;
//STRIP001
//STRIP001  int  nRFlags = SM_RECT_CORE | SM_RECT_ITALIC | SM_RECT_LINES | SM_RECT_MID;
//STRIP001  SmRect::Draw(rDev, rPosition, nRFlags);
//STRIP001 #endif
//STRIP001 }


/**************************************************************************/


/*N*/ void SmRectangleNode::AdaptToX(const OutputDevice &rDev, ULONG nWidth)
/*N*/ {
/*N*/   aToSize.Width() = nWidth;
/*N*/ }


/*N*/ void SmRectangleNode::AdaptToY(const OutputDevice &rDev, ULONG nHeight)
/*N*/ {
/*N*/   GetFont().FreezeBorderWidth();
/*N*/   aToSize.Height() = nHeight;
/*N*/ }


/*N*/ void SmRectangleNode::Arrange(const OutputDevice &rDev, const SmFormat &rFormat)
/*N*/ {
/*N*/   long  nFontHeight = GetFont().GetSize().Height();
/*N*/   long  nWidth  = aToSize.Width(),
/*N*/         nHeight = aToSize.Height();
/*N*/   if (nHeight == 0)
/*?*/       nHeight = nFontHeight / 30;
/*N*/   if (nWidth == 0)
/*?*/       nWidth  = nFontHeight / 3;
/*N*/
/*N*/     SmTmpDevice  aTmpDev ((OutputDevice &) rDev, TRUE);
/*N*/   aTmpDev.SetFont(GetFont());
/*N*/
/*N*/   // add some borderspace
/*N*/   ULONG  nBorderWidth = GetFont().GetBorderWidth();
/*N*/   //nWidth  += nBorderWidth;
/*N*/   nHeight += 2 * nBorderWidth;
/*N*/
/*N*/   //! use this method in order to have 'SmRect::HasAlignInfo() == TRUE'
/*N*/   //! and thus having the attribut-fences updated in 'SmRect::ExtendBy'
/*N*/   SmRect::operator = (SmRect(nWidth, nHeight));
/*N*/ }


/*N*/ void SmRectangleNode::Draw(OutputDevice &rDev, const Point &rPosition) const
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  if (IsPhantom())
//STRIP001      return;
//STRIP001
//STRIP001     SmTmpDevice  aTmpDev ((OutputDevice &) rDev, FALSE);
//STRIP001     aTmpDev.SetFillColor(GetFont().GetColor());
//STRIP001     rDev.SetLineColor();
//STRIP001     aTmpDev.SetFont(GetFont());
//STRIP001
//STRIP001     ULONG  nBorderWidth = GetFont().GetBorderWidth();
//STRIP001
//STRIP001  // get rectangle and remove borderspace
//STRIP001  Rectangle  aTmp (AsRectangle() + rPosition - GetTopLeft());
//STRIP001  aTmp.Left()   += nBorderWidth;
//STRIP001  aTmp.Right()  -= nBorderWidth;
//STRIP001  aTmp.Top()    += nBorderWidth;
//STRIP001  aTmp.Bottom() -= nBorderWidth;
//STRIP001
//STRIP001  DBG_ASSERT(aTmp.GetHeight() > 0  &&  aTmp.GetWidth() > 0,
//STRIP001             "Sm: leeres Rechteck");
//STRIP001
//STRIP001  //! avoid GROWING AND SHRINKING of drawn rectangle when constantly
//STRIP001  //! increasing zoomfactor.
//STRIP001  //  This is done by shifting it's output-position to a point that
//STRIP001  //  corresponds exactly to a pixel on the output device.
//STRIP001     Point  aPos (rDev.PixelToLogic(rDev.LogicToPixel(aTmp.TopLeft())));
//STRIP001  aTmp.SetPos(aPos);
//STRIP001
//STRIP001     rDev.DrawRect(aTmp);
//STRIP001
//STRIP001 #ifdef SM_RECT_DEBUG
//STRIP001  if (!IsDebug())
//STRIP001      return;
//STRIP001
//STRIP001  int  nRFlags = SM_RECT_CORE | SM_RECT_ITALIC | SM_RECT_LINES | SM_RECT_MID;
//STRIP001  SmRect::Draw(rDev, rPosition, nRFlags);
//STRIP001 #endif
/*N*/ }


/**************************************************************************/


/*N*/ void SmTextNode::Prepare(const SmFormat &rFormat, const SmDocShell &rDocShell)
/*N*/ {
/*N*/   SmNode::Prepare(rFormat, rDocShell);
/*N*/
/*N*/     // default setting for horizontal alignment of nodes with TTEXT
/*N*/     // content is as alignl (cannot be done in Arrange since it would
/*N*/     // override the settings made by an SmAlignNode before)
/*N*/     if (TTEXT == GetToken().eType)
/*N*/         SetRectHorAlign( RHA_LEFT );
/*N*/
/*N*/     aText = GetToken().aText;
/*N*/   GetFont() = rFormat.GetFont(GetFontDesc());
/*N*/
/*N*/   if (GetFont().GetItalic() == ITALIC_NORMAL)
/*N*/       Attributes() |= ATTR_ITALIC;
/*N*/   if (GetFont().GetWeight() == WEIGHT_BOLD)
/*?*/       Attributes() |= ATTR_BOLD;
/*N*/
/*N*/ };


/*N*/ void SmTextNode::Arrange(const OutputDevice &rDev, const SmFormat &rFormat)
/*N*/ {
/*N*/   PrepareAttributes();
/*N*/
/*N*/   USHORT  nSizeDesc = GetFontDesc() == FNT_FUNCTION ?
/*N*/                           SIZ_FUNCTION : SIZ_TEXT;
/*N*/   GetFont() *= Fraction (rFormat.GetRelSize(nSizeDesc), 100);
/*N*/
/*N*/     SmTmpDevice  aTmpDev ((OutputDevice &) rDev, TRUE);
/*N*/   aTmpDev.SetFont(GetFont());
/*N*/
/*N*/   SmRect::operator = (SmRect(aTmpDev, &rFormat, aText, GetFont().GetBorderWidth()));
/*N*/ }

//STRIP001 void SmTextNode::CreateTextFromNode(String &rText)
//STRIP001 {
//STRIP001     BOOL bQuoted=FALSE;
//STRIP001  if (GetToken().eType == TTEXT)
//STRIP001     {
//STRIP001      rText.Append('\"');
//STRIP001         bQuoted=TRUE;
//STRIP001     }
//STRIP001     else
//STRIP001     {
//STRIP001         SmParser aParseTest;
//STRIP001         SmNode *pTable = aParseTest.Parse(GetToken().aText);
//STRIP001         bQuoted=TRUE;
//STRIP001         if ( (pTable->GetType() == NTABLE) && (pTable->GetNumSubNodes() == 1) )
//STRIP001         {
//STRIP001             SmNode *pResult = pTable->GetSubNode(0);
//STRIP001             if ( (pResult->GetType() == NLINE) &&
//STRIP001                 (pResult->GetNumSubNodes() == 1) )
//STRIP001             {
//STRIP001                 pResult = pResult->GetSubNode(0);
//STRIP001                 if ( (pResult->GetType() == NEXPRESSION) &&
//STRIP001                     (pResult->GetNumSubNodes() == 1) )
//STRIP001                 {
//STRIP001                     pResult = pResult->GetSubNode(0);
//STRIP001                     if (pResult->GetType() == NTEXT)
//STRIP001                         bQuoted=FALSE;
//STRIP001                 }
//STRIP001             }
//STRIP001         }
//STRIP001         delete pTable;
//STRIP001
//STRIP001         if ((GetToken().eType == TIDENT) && (GetFontDesc() == FNT_FUNCTION))
//STRIP001         {
//STRIP001             //Search for existing functions and remove extraenous keyword
//STRIP001             APPEND(rText,"func ");
//STRIP001         }
//STRIP001         else if (bQuoted)
//STRIP001             APPEND(rText,"italic ");
//STRIP001
//STRIP001         if (bQuoted)
//STRIP001             rText.Append('\"');
//STRIP001
//STRIP001     }
//STRIP001
//STRIP001  rText.Append(GetToken().aText);
//STRIP001
//STRIP001  if (bQuoted)
//STRIP001      rText.Append('\"');
//STRIP001  rText.Append(' ');
//STRIP001 }

/*N*/ void SmTextNode::Draw(OutputDevice &rDev, const Point& rPosition) const
/*N*/ {
/*N*/   if (IsPhantom()  ||  aText.Len() == 0  ||  aText.GetChar(0) == xub_Unicode('\0'))
/*N*/       return;
/*N*/
/*N*/     SmTmpDevice  aTmpDev ((OutputDevice &) rDev, FALSE);
/*N*/     aTmpDev.SetFont(GetFont());
/*N*/
/*N*/     Point  aPos (rPosition);
/*N*/   aPos.Y() += GetBaselineOffset();
/*N*/   // auf Pixelkoordinaten runden
/*N*/     aPos = rDev.PixelToLogic( rDev.LogicToPixel(aPos) );
/*N*/
/*N*/     rDev.DrawStretchText(aPos, GetWidth(), aText);
/*N*/
/*N*/ #ifdef SM_RECT_DEBUG
/*N*/   if (!IsDebug())
/*N*/       return;
/*N*/
/*N*/   int  nRFlags = SM_RECT_CORE | SM_RECT_ITALIC | SM_RECT_LINES | SM_RECT_MID;
/*N*/   SmRect::Draw(rDev, rPosition, nRFlags);
/*N*/ #endif
/*N*/ }

//STRIP001 void SmTextNode::GetAccessibleText( String &rText ) const
//STRIP001 {
//STRIP001     rText += aText;
//STRIP001 }

/**************************************************************************/

//STRIP001 void SmMatrixNode::CreateTextFromNode(String &rText)
//STRIP001 {
//STRIP001  APPEND(rText,"matrix {");
//STRIP001  for (int i = 0;  i < nNumRows;  i++)
//STRIP001  {
//STRIP001      for (int j = 0;  j < nNumCols;  j++)
//STRIP001      {
//STRIP001          SmNode *pNode = GetSubNode(i * nNumCols + j);
//STRIP001          pNode->CreateTextFromNode(rText);
//STRIP001          if (j != nNumCols-1)
//STRIP001              APPEND(rText,"# ");
//STRIP001      }
//STRIP001      if (i != nNumRows-1)
//STRIP001          APPEND(rText,"## ");
//STRIP001  }
//STRIP001  rText.EraseTrailingChars();
//STRIP001  APPEND(rText,"} ");
//STRIP001 }


/*N*/ void SmMatrixNode::Arrange(const OutputDevice &rDev, const SmFormat &rFormat)
/*N*/ {
/*N*/   Point   aPosition,
/*N*/           aOffset;
/*N*/   SmNode *pNode;
/*N*/   int     i, j;
/*N*/
/*N*/   // initialize array that is to hold the maximum widhts of all
/*N*/   // elements (subnodes) in that column.
/*N*/   long *pColWidth = new long[nNumCols];
/*N*/   for (j = 0;  j  < nNumCols;  j++)
/*N*/       pColWidth[j] = 0;
/*N*/
/*N*/   // arrange subnodes and calculate the aboves arrays contents
/*N*/   for (i = GetNumSubNodes() - 1;  i >= 0; i--)
/*N*/       if (pNode = GetSubNode(i))
/*N*/       {   pNode->Arrange(rDev, rFormat);
/*N*/
/*N*/           int  nCol = i % nNumCols;
/*N*/           pColWidth[nCol]
/*N*/               = Max(pColWidth[nCol], pNode->GetItalicWidth());
/*N*/       }
/*N*/
/*N*/   // norm distance from which the following two are calcutated
/*N*/   const int  nNormDist = 3 * GetFont().GetSize().Height();
/*N*/
/*N*/   // define horizontal and vertical minimal distances that seperate
/*N*/   // the elements
/*N*/   long  nHorDist = nNormDist * rFormat.GetDistance(DIS_MATRIXCOL) / 100L,
/*N*/         nVerDist = nNormDist * rFormat.GetDistance(DIS_MATRIXROW) / 100L;
/*N*/
/*N*/   // build array that holds the leftmost position for each column
/*N*/   long *pColLeft = new long[nNumCols];
/*N*/   long  nX = 0;
/*N*/   for (j = 0;  j < nNumCols;  j++)
/*N*/   {   pColLeft[j] = nX;
/*N*/       nX += pColWidth[j] + nHorDist;
/*N*/   }
/*N*/
/*N*/   Point   aPos, aDelta;
/*N*/   SmRect  aLineRect;
/*N*/   SmRect::operator = (SmRect());
/*N*/   for (i = 0;  i < nNumRows;  i++)
/*N*/   {   aLineRect = SmRect();
/*N*/       for (j = 0;  j < nNumCols;  j++)
/*N*/       {   SmNode *pNode = GetSubNode(i * nNumCols + j);
/*N*/           DBG_ASSERT(pNode, "Sm: NULL pointer");
/*N*/
/*N*/           const SmRect &rNodeRect = pNode->GetRect();
/*N*/
/*N*/           // align all baselines in that row if possible
/*N*/           aPos = rNodeRect.AlignTo(aLineRect, RP_RIGHT, RHA_CENTER, RVA_BASELINE);
/*N*/           aPos.X() += nHorDist;
/*N*/
/*N*/           // get horizontal alignment
/*N*/           const SmNode *pCoNode   = pNode->GetLeftMost();
/*N*/           SmTokenType   eType     = pCoNode->GetToken().eType;
/*N*/             RectHorAlign  eHorAlign = pCoNode->GetRectHorAlign();
/*N*/
/*N*/           // caculate horizontal position of element depending on column
/*N*/           // and horizontal alignment
/*N*/           switch (eHorAlign)
/*N*/           {   case RHA_LEFT:
/*N*/                   aPos.X() = rNodeRect.GetLeft() + pColLeft[j];
/*N*/                   break;
/*N*/               case RHA_CENTER:
/*N*/                   aPos.X() = rNodeRect.GetLeft() + pColLeft[j]
/*N*/                              + pColWidth[j] / 2
/*N*/                              - rNodeRect.GetItalicCenterX();
/*N*/                   break;
/*N*/               case RHA_RIGHT:
/*?*/                   aPos.X() = rNodeRect.GetLeft() + pColLeft[j]
/*?*/                              + pColWidth[j] - rNodeRect.GetItalicWidth();
/*N*/                   break;
/*N*/           }
/*N*/
/*N*/           pNode->MoveTo(aPos);
/*N*/           aLineRect.ExtendBy(rNodeRect, RCP_XOR);
/*N*/       }
/*N*/
/*N*/       aPos = aLineRect.AlignTo(*this, RP_BOTTOM, RHA_CENTER, RVA_BASELINE);
/*N*/       aPos.Y() += nVerDist;
/*N*/
/*N*/       // move 'aLineRect' and rectangles in that line to final position
/*N*/       aDelta.X() = 0;     // since horizontal alignment is already done
/*N*/       aDelta.Y() = aPos.Y() - aLineRect.GetTop();
/*N*/       aLineRect.Move(aDelta);
/*N*/       for (j = 0;  j < nNumCols;  j++)
/*N*/           if (pNode = GetSubNode(i * nNumCols + j))
/*N*/               pNode->Move(aDelta);
/*N*/
/*N*/       ExtendBy(aLineRect, RCP_NONE);
/*N*/   }
/*N*/
/*N*/   delete [] pColLeft;
/*N*/   delete [] pColWidth;
/*N*/ }


/*N*/ void SmMatrixNode::SetRowCol(USHORT nMatrixRows, USHORT nMatrixCols)
/*N*/ {
/*N*/   nNumRows = nMatrixRows;
/*N*/   nNumCols = nMatrixCols;
/*N*/ }


/*N*/ SmNode * SmMatrixNode::GetLeftMost()
/*N*/ {
/*N*/   return this;
/*N*/ }


/**************************************************************************/


/*N*/ SmMathSymbolNode::SmMathSymbolNode(const SmToken &rNodeToken)
/*N*/ : SmSpecialNode(NMATH, rNodeToken, FNT_MATH)
/*N*/ {
/*N*/   xub_Unicode cChar = GetToken().cMathChar;
/*N*/   if ((xub_Unicode) '\0' != cChar)
/*N*/       SetText( cChar );
/*N*/ }

/*?*/ void SmMathSymbolNode::AdaptToX(const OutputDevice &rDev, ULONG nWidth)
/*?*/ {
/*?*/     // Since there is no function to do this, we try to approximate it:
/*?*/     Size  aFntSize (GetFont().GetSize());
/*?*/
/*?*/     //! however the result is a bit better with 'nWidth' as initial font width
/*?*/     aFntSize.Width() = nWidth;
/*?*/     GetFont().SetSize(aFntSize);
/*?*/
/*?*/     SmTmpDevice  aTmpDev ((OutputDevice &) rDev, TRUE);
/*?*/     aTmpDev.SetFont(GetFont());
/*?*/
/*?*/     // get denominator of error factor for width
/*?*/     long nBorderWidth = GetFont().GetBorderWidth();
/*?*/     long nDenom = SmRect(aTmpDev, NULL, GetText(), nBorderWidth).GetItalicWidth();
/*?*/
/*?*/     // scale fontwidth with this error factor
/*?*/     aFntSize.Width() *= nWidth;
/*?*/     aFntSize.Width() /= nDenom ? nDenom : 1;
/*?*/
/*?*/     GetFont().SetSize(aFntSize);
/*?*/ }

/*N*/ void SmMathSymbolNode::AdaptToY(const OutputDevice &rDev, ULONG nHeight)
/*N*/ {
/*N*/     GetFont().FreezeBorderWidth();
/*N*/     Size  aFntSize (GetFont().GetSize());
/*N*/
/*N*/     // da wir nur die Höhe skalieren wollen müsen wir hier ggf die Fontweite
/*N*/     // ermitteln um diese beizubehalten.
/*N*/     if (aFntSize.Width() == 0)
/*N*/     {
/*N*/         OutputDevice &rDevNC = (OutputDevice &) rDev;
/*N*/         rDevNC.Push(PUSH_FONT | PUSH_MAPMODE);
/*N*/         rDevNC.SetFont(GetFont());
/*N*/         aFntSize.Width() = rDev.GetFontMetric().GetSize().Width();
/*N*/         rDevNC.Pop();
/*N*/     }
/*N*/     DBG_ASSERT(aFntSize.Width() != 0, "Sm: ");
/*N*/
/*N*/     //! however the result is a bit better with 'nHeight' as initial
/*N*/     //! font height
/*N*/     aFntSize.Height() = nHeight;
/*N*/     GetFont().SetSize(aFntSize);
/*N*/
/*N*/     SmTmpDevice  aTmpDev ((OutputDevice &) rDev, TRUE);
/*N*/     aTmpDev.SetFont(GetFont());
/*N*/
/*N*/     // get denominator of error factor for height
/*N*/     long nBorderWidth = GetFont().GetBorderWidth();
/*N*/     long nDenom = SmRect(aTmpDev, NULL, GetText(), nBorderWidth).GetHeight();
/*N*/
/*N*/     // scale fontwidth with this error factor
/*N*/     aFntSize.Height() *= nHeight;
/*N*/     aFntSize.Height() /= nDenom ? nDenom : 1;
/*N*/
/*N*/     GetFont().SetSize(aFntSize);
/*N*/ }


/*N*/ void SmMathSymbolNode::Prepare(const SmFormat &rFormat, const SmDocShell &rDocShell)
/*N*/ {
/*N*/   SmNode::Prepare(rFormat, rDocShell);
/*N*/
/*N*/     DBG_ASSERT(GetFont().GetCharSet() == RTL_TEXTENCODING_SYMBOL  ||
/*N*/                GetFont().GetCharSet() == RTL_TEXTENCODING_UNICODE,
/*N*/         "incorrect charset for character from StarMath/StarSymbol font");
/*N*/
/*N*/   Flags() |= FLG_FONT | FLG_ITALIC;
/*N*/ };


/*N*/ void SmMathSymbolNode::Arrange(const OutputDevice &rDev, const SmFormat &rFormat)
/*N*/ {
/*N*/   const XubString &rText = GetText();
/*N*/
/*N*/   if (rText.Len() == 0  ||  rText.GetChar(0) == xub_Unicode('\0'))
/*N*/   {   SmRect::operator = (SmRect());
/*N*/       return;
/*N*/   }
/*N*/
/*N*/   PrepareAttributes();
/*N*/
/*N*/   GetFont() *= Fraction (rFormat.GetRelSize(SIZ_TEXT), 100);
/*N*/
/*N*/     SmTmpDevice  aTmpDev ((OutputDevice &) rDev, TRUE);
/*N*/   aTmpDev.SetFont(GetFont());
/*N*/
/*N*/   SmRect::operator = (SmRect(aTmpDev, &rFormat, rText, GetFont().GetBorderWidth()));
/*N*/ }

//STRIP001 void SmMathSymbolNode::CreateTextFromNode(String &rText)
//STRIP001 {
//STRIP001  String sStr;
//STRIP001  MathType::LookupChar(GetToken().cMathChar, sStr);
//STRIP001  rText.Append(sStr);
//STRIP001 }

//STRIP001 void SmRectangleNode::CreateTextFromNode(String &rText)
//STRIP001 {
//STRIP001     switch (GetToken().eType)
//STRIP001     {
//STRIP001     case TUNDERLINE:
//STRIP001         APPEND(rText,"underline ");
//STRIP001         break;
//STRIP001     case TOVERLINE:
//STRIP001         APPEND(rText,"overline ");
//STRIP001         break;
//STRIP001     case TOVERSTRIKE:
//STRIP001         APPEND(rText,"overstrike ");
//STRIP001         break;
//STRIP001     default:
//STRIP001         break;
//STRIP001     }
//STRIP001 }

//STRIP001 void SmAttributNode::CreateTextFromNode(String &rText)
//STRIP001 {
//STRIP001  SmNode *pNode;
//STRIP001  USHORT  nSize = GetNumSubNodes();
//STRIP001     DBG_ASSERT(nSize == 2, "Node missing members");
//STRIP001     rText.Append('{');
//STRIP001     sal_Unicode nLast=0;
//STRIP001     if (pNode = GetSubNode(0))
//STRIP001     {
//STRIP001         String aStr;
//STRIP001         pNode->CreateTextFromNode(aStr);
//STRIP001         if (aStr.Len() > 1)
//STRIP001             rText.Append(aStr);
//STRIP001         else
//STRIP001         {
//STRIP001             nLast = aStr.GetChar(0);
//STRIP001             switch (nLast)
//STRIP001             {
//STRIP001             case 0xAF:
//STRIP001                 APPEND(rText,"overline ");
//STRIP001                 break;
//STRIP001             case 0x2d9:
//STRIP001                 APPEND(rText,"dot ");
//STRIP001                 break;
//STRIP001             case 0x2dc:
//STRIP001                 APPEND(rText,"widetilde ");
//STRIP001                 break;
//STRIP001             case 0xA8:
//STRIP001                 APPEND(rText,"ddot ");
//STRIP001                 break;
//STRIP001             case 0xE082:
//STRIP001                 break;
//STRIP001             case 0xE09B:
//STRIP001                 APPEND(rText,"dddot ");
//STRIP001                 break;
//STRIP001             default:
//STRIP001                 rText.Append(nLast);
//STRIP001                 break;
//STRIP001             }
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001  if (nSize == 2)
//STRIP001      if (pNode = GetSubNode(1))
//STRIP001          pNode->CreateTextFromNode(rText);
//STRIP001
//STRIP001  rText.EraseTrailingChars();
//STRIP001
//STRIP001     if (nLast == 0xE082)
//STRIP001         APPEND(rText," overbrace {}");
//STRIP001
//STRIP001  APPEND(rText,"} ");
//STRIP001 }

/**************************************************************************/


/*N*/ void SmSpecialNode::Prepare(const SmFormat &rFormat, const SmDocShell &rDocShell)
/*N*/ {
/*N*/   SmNode::Prepare(rFormat, rDocShell);
/*N*/
/*N*/   const SmSym   *pSym;
/*N*/   SmModule  *pp = SM_MOD1();
/*N*/
/*N*/   Size  aOldSize = GetFont().GetSize();
/*N*/   if (pSym = rDocShell.GetSymSetManager().GetSymbolByName(GetToken().aText))
/*N*/     {
/*N*/         SetText( pSym->GetCharacter() );
/*N*/       GetFont() = pSym->GetFace();
/*N*/   }
/*N*/   else
/*N*/     {
/*N*/         SetText( GetToken().aText );
/*N*/       GetFont() = rFormat.GetFont(FNT_VARIABLE);
/*N*/   }
/*N*/   GetFont().SetSize(aOldSize);
/*N*/
/*N*/   //! eigentlich sollten nur WEIGHT_NORMAL und WEIGHT_BOLD vorkommen...
/*N*/   //! In der sms-Datei gibt es jedoch zB auch 'WEIGHT_ULTRALIGHT'
/*N*/   //! daher vergleichen wir hier mit  >  statt mit  !=  .
/*N*/   //! (Langfristig sollte die Notwendigkeit für 'PrepareAttribut', und damit
/*N*/   //! für dieses hier, mal entfallen.)
/*N*/     //
/*N*/     //! see also SmFontStyles::GetStyleName
/*N*/   if (GetFont().GetWeight() > WEIGHT_NORMAL)
/*?*/       SetAttribut(ATTR_BOLD);
/*N*/   if (GetFont().GetItalic() != ITALIC_NONE)
/*N*/       SetAttribut(ATTR_ITALIC);
/*N*/
/*N*/   Flags() |= FLG_FONT;
/*N*/ };


/*N*/ void SmSpecialNode::Arrange(const OutputDevice &rDev, const SmFormat &rFormat)
/*N*/ {
/*N*/   PrepareAttributes();
/*N*/
/*N*/     SmTmpDevice  aTmpDev ((OutputDevice &) rDev, TRUE);
/*N*/   aTmpDev.SetFont(GetFont());
/*N*/
/*N*/   SmRect::operator = (SmRect(aTmpDev, &rFormat, GetText(), GetFont().GetBorderWidth()));
/*N*/ }


/*N*/ void SmSpecialNode::Draw(OutputDevice &rDev, const Point& rPosition) const
/*N*/ {
/*N*/   //! since this chars might come from any font, that we may not have
/*N*/   //! set to ALIGN_BASELINE yet, we do it now.
/*N*/   ((SmSpecialNode *)this)->GetFont().SetAlign(ALIGN_BASELINE);
/*N*/
/*N*/   SmTextNode::Draw(rDev, rPosition);
/*N*/ }


/**************************************************************************/


//STRIP001 void SmGlyphSpecialNode::Arrange(const OutputDevice &rDev, const SmFormat &rFormat)
//STRIP001 {
//STRIP001  PrepareAttributes();
//STRIP001
//STRIP001     SmTmpDevice  aTmpDev ((OutputDevice &) rDev, TRUE);
//STRIP001  aTmpDev.SetFont(GetFont());
//STRIP001
//STRIP001  SmRect::operator = (SmRect(aTmpDev, &rFormat, GetText(),
//STRIP001                             GetFont().GetBorderWidth()).AsGlyphRect());
//STRIP001 }


/**************************************************************************/


/*N*/ void SmPlaceNode::Prepare(const SmFormat &rFormat, const SmDocShell &rDocShell)
/*N*/ {
/*N*/   SmNode::Prepare(rFormat, rDocShell);
/*N*/
/*N*/   GetFont().SetColor(COL_GRAY);
/*N*/   Flags() |= FLG_COLOR | FLG_FONT | FLG_ITALIC;
/*N*/ };


/*N*/ void SmPlaceNode::Arrange(const OutputDevice &rDev, const SmFormat &rFormat)
/*N*/ {
/*N*/   PrepareAttributes();
/*N*/
/*N*/     SmTmpDevice  aTmpDev ((OutputDevice &) rDev, TRUE);
/*N*/   aTmpDev.SetFont(GetFont());
/*N*/
/*N*/   SmRect::operator = (SmRect(aTmpDev, &rFormat, GetText(), GetFont().GetBorderWidth()));
/*N*/ }


/**************************************************************************/


/*N*/ void SmErrorNode::Prepare(const SmFormat &rFormat, const SmDocShell &rDocShell)
/*N*/ {
/*N*/   SmNode::Prepare(rFormat, rDocShell);
/*N*/
/*N*/   GetFont().SetColor(COL_RED);
/*N*/   Flags() |= FLG_VISIBLE | FLG_BOLD | FLG_ITALIC
/*N*/              | FLG_COLOR | FLG_FONT | FLG_SIZE;
/*N*/ }


/*N*/ void SmErrorNode::Arrange(const OutputDevice &rDev, const SmFormat &rFormat)
/*N*/ {
/*N*/   PrepareAttributes();
/*N*/
/*N*/     SmTmpDevice  aTmpDev ((OutputDevice &) rDev, TRUE);
/*N*/   aTmpDev.SetFont(GetFont());
/*N*/
/*N*/   const XubString &rText = GetText();
/*N*/   DBG_ASSERT(rText.Len() == 1  &&  rText.GetChar(0) == (xub_Unicode) MS_ERROR,
/*N*/               "Sm : Text ist kein ERROR Symbol");
/*N*/   SmRect::operator = (SmRect(aTmpDev, &rFormat, rText, GetFont().GetBorderWidth()));
/*N*/ }


/**************************************************************************/


/*N*/ void SmBlankNode::IncreaseBy(const SmToken &rToken)
/*N*/ {
/*N*/   switch(rToken.eType)
/*N*/   {
/*N*/       case TBLANK:    nNum += 4;  break;
/*?*/       case TSBLANK:   nNum += 1;  break;
/*N*/   }
/*N*/ }


/*N*/ void SmBlankNode::Prepare(const SmFormat &rFormat, const SmDocShell &rDocShell)
/*N*/ {
/*N*/   SmNode::Prepare(rFormat, rDocShell);
/*N*/
/*N*/   //! hier mu?sollte es lediglich nicht der StarMath Font sein,
/*N*/   //! damit für das in Arrange verwendete Zeichen ein "normales"
/*N*/   //! (ungecliptes) Rechteck erzeugt wird.
/*N*/   GetFont() = rFormat.GetFont(FNT_VARIABLE);
/*N*/
/*N*/   Flags() |= FLG_FONT | FLG_BOLD | FLG_ITALIC;
/*N*/ }


/*N*/ void SmBlankNode::Arrange(const OutputDevice &rDev, const SmFormat &rFormat)
/*N*/ {
/*N*/     SmTmpDevice  aTmpDev ((OutputDevice &) rDev, TRUE);
/*N*/   aTmpDev.SetFont(GetFont());
/*N*/
/*N*/   // Abstand von der Fonthöhe abhängig machen
/*N*/   // (damit er beim skalieren (zB size *2 {a ~ b}) mitwächst)
/*N*/   long  nDist  = GetFont().GetSize().Height() / 10L,
/*N*/         nSpace = nNum * nDist;
/*N*/
/*N*/   // ein SmRect mit Baseline und allem drum und dran besorgen
/*N*/   SmRect::operator = (SmRect(aTmpDev, &rFormat, XubString(xub_Unicode(' ')),
/*N*/                              GetFont().GetBorderWidth()));
/*N*/
/*N*/   // und dieses auf die gewünschte Breite bringen
/*N*/   SetItalicSpaces(0, 0);
/*N*/   SetWidth(nSpace);
/*N*/ }



}
