/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */


#ifdef _MSC_VER
#pragma hdrstop
#endif

#include <atrhndl.hxx>
#include <bf_svtools/itemiter.hxx>
#include <bf_svx/cmapitem.hxx>
#include <bf_svx/colritem.hxx>
#include <bf_svx/cntritem.hxx>
#include <bf_svx/crsditem.hxx>
#include <bf_svx/escpitem.hxx>
#include <bf_svx/fontitem.hxx>
#include <bf_svx/fhgtitem.hxx>
#include <bf_svx/kernitem.hxx>
#include <bf_svx/charreliefitem.hxx>
#include <bf_svx/langitem.hxx>
#include <bf_svx/postitem.hxx>
#include <bf_svx/shdditem.hxx>
#include <bf_svx/udlnitem.hxx>
#include <bf_svx/wghtitem.hxx>
#include <bf_svx/wrlmitem.hxx>
#include <bf_svx/akrnitem.hxx>
#include <bf_svx/blnkitem.hxx>
#include <bf_svx/charrotateitem.hxx>
#include <bf_svx/emphitem.hxx>
#include <bf_svx/charscaleitem.hxx>
#include <bf_svx/twolinesitem.hxx>
#include <charfmt.hxx>
#include <fchrfmt.hxx>
#include <bf_svx/brshitem.hxx>
#include <txtinet.hxx>

#include <horiornt.hxx>

#include <doc.hxx>
#include <viewsh.hxx>   // ViewShell
#include <viewopt.hxx>  // SwViewOptions
namespace binfilter {

#define STACK_INCREMENT 4

/*************************************************************************
 *                      Attribute to Stack Mapping
 *
 * Attributes applied to a text are pushed on different stacks. For each
 * stack, the top most attribute on the stack is valid. Because some
 * kinds of attributes have to be pushed to the same stacks we map their
 * ids to stack ids
 * Attention: The first NUM_DEFAULT_VALUES ( defined in swfntcch.hxx == 34 )
 * are stored in the defaultitem-cache, if you add one, you have to increase
 * NUM_DEFAULT_VALUES.
 *************************************************************************/

const BYTE StackPos[ RES_TXTATR_WITHEND_END - RES_CHRATR_BEGIN + 1 ] = {
     0, //                                       //  0
     1, // RES_CHRATR_CASEMAP = RES_CHRATR_BEGIN //  1
     0, // RES_CHRATR_CHARSETCOLOR,              //  2
     2, // RES_CHRATR_COLOR,                     //  3
     3, // RES_CHRATR_CONTOUR,                   //  4
     4, // RES_CHRATR_CROSSEDOUT,                //  5
     5, // RES_CHRATR_ESCAPEMENT,                //  6
     6, // RES_CHRATR_FONT,                      //  7
     7, // RES_CHRATR_FONTSIZE,                  //  8
     8, // RES_CHRATR_KERNING,                   //  9
     9, // RES_CHRATR_LANGUAGE,                  // 10
    10, // RES_CHRATR_POSTURE,                   // 11
     0, // RES_CHRATR_PROPORTIONALFONTSIZE,      // 12
    11, // RES_CHRATR_SHADOWED,                  // 13
    12, // RES_CHRATR_UNDERLINE,                 // 14
    13, // RES_CHRATR_WEIGHT,                    // 15
    14, // RES_CHRATR_WORDLINEMODE,              // 16
    15, // RES_CHRATR_AUTOKERN,                  // 17
    16, // RES_CHRATR_BLINK,                     // 18
    17, // RES_CHRATR_NOHYPHEN,                  // 19
     0, // RES_CHRATR_NOLINEBREAK,               // 20
    18, // RES_CHRATR_BACKGROUND,                // 21
    19, // RES_CHRATR_CJK_FONT,                  // 22
    20, // RES_CHRATR_CJK_FONTSIZE,              // 23
    21, // RES_CHRATR_CJK_LANGUAGE,              // 24
    22, // RES_CHRATR_CJK_POSTURE,               // 25
    23, // RES_CHRATR_CJK_WEIGHT,                // 26
    24, // RES_CHRATR_CTL_FONT,                  // 27
    25, // RES_CHRATR_CTL_FONTSIZE,              // 28
    26, // RES_CHRATR_CTL_LANGUAGE,              // 29
    27, // RES_CHRATR_CTL_POSTURE,               // 30
    28, // RES_CHRATR_CTL_WEIGHT,                // 31
    29, // RES_CHRATR_ROTATE,                    // 32
    30, // RES_CHRATR_EMPHASIS_MARK,             // 33
    31, // RES_CHRATR_TWO_LINES,                 // 34
    32, // RES_CHRATR_SCALEW,                    // 35
    33, // RES_CHRATR_RELIEF,                    // 36
     0, // RES_CHRATR_DUMMY1,                    // 37
     0, // RES_TXTATR_INETFMT                    // 38
     0, // RES_TXTATR_DUMMY4,                    // 39
    34, // RES_TXTATR_REFMARK,                   // 40
    35, // RES_TXTATR_TOXMARK,                   // 41
     0, // RES_TXTATR_CHARFMT,                   // 42
     0, // RES_TXTATR_DUMMY5,                    // 43
    36, // RES_TXTATR_CJK_RUBY,                  // 44
     0, // RES_TXTATR_UNKNOWN_CONTAINER,         // 45
     0, // RES_TXTATR_DUMMY6,                    // 46
     0  // RES_TXTATR_DUMMY7,                    // 47
};

/*************************************************************************
 *                      lcl_ChgHyperLinkColor
 * returns if the color attribute has to be changed for hyperlinks
 *************************************************************************/

/*M*/ sal_Bool lcl_ChgHyperLinkColor( const SwTxtAttr& rAttr,
/*M*/                                 const SfxPoolItem& rItem,
/*M*/                                 const ViewShell* pShell )
/*M*/ {
/*M*/     return pShell && pShell->GetWin() &&
/*M*/            ! pShell->GetViewOptions()->IsPagePreview() &&
/*M*/            RES_TXTATR_INETFMT == rAttr.Which() &&
/*M*/            RES_CHRATR_COLOR == rItem.Which() &&
/*M*/            ( (((SwTxtINetFmt&)rAttr).IsVisited() && SwViewOption::IsVisitedLinks()) ||
/*M*/            (!((SwTxtINetFmt&)rAttr).IsVisited() && SwViewOption::IsLinks()) );
/*M*/ }


/*************************************************************************
 *                      SwAttrHandler::SwAttrStack::SwAttrStack()
 *************************************************************************/

/*N*/ inline SwAttrHandler::SwAttrStack::SwAttrStack()
/*N*/     : nCount( 0 ), nSize( INITIAL_NUM_ATTR )
/*N*/ {
/*N*/     pArray = pInitialArray;
/*N*/ }

/*************************************************************************
 *                      SwAttrHandler::SwAttrStack::Insert()
 *************************************************************************/

/*N*/ void SwAttrHandler::SwAttrStack::Insert( const SwTxtAttr& rAttr, const USHORT nPos )
/*N*/ {
/*N*/     // do we still have enough space?
/*N*/     if ( nCount >= nSize )
/*N*/     {
/*?*/          // we are still in our initial array
/*?*/         if ( INITIAL_NUM_ATTR == nSize )
/*?*/         {
/*?*/             nSize += STACK_INCREMENT;
/*?*/             pArray = new SwTxtAttr*[ nSize ];
/*?*/             // copy from pInitArray to new Array
/*?*/             memcpy( pArray, pInitialArray,
/*?*/                     INITIAL_NUM_ATTR * sizeof(SwTxtAttr*)
/*?*/                     );
/*?*/         }
/*?*/         // we are in new memory
/*?*/         else
/*?*/         {
/*?*/             nSize += STACK_INCREMENT;
/*?*/             SwTxtAttr** pTmpArray = new SwTxtAttr*[ nSize ];
/*?*/             // copy from pArray to new Array
/*?*/             memcpy( pTmpArray, pArray, nCount * sizeof(SwTxtAttr*) );
/*?*/             // free old array
/*?*/             delete [] pArray;
/*?*/             pArray = pTmpArray;
/*?*/         }
/*?*/     }
/*N*/
/*N*/     OSL_ENSURE( nPos <= nCount, "wrong position for insert operation");
/*N*/
/*N*/     if ( nPos < nCount )
/*N*/         memmove( pArray + nPos + 1, pArray + nPos,
/*N*/                 ( nCount - nPos ) * sizeof(SwTxtAttr*)
/*N*/                 );
/*N*/     pArray[ nPos ] = (SwTxtAttr*)&rAttr;
/*N*/
/*N*/     nCount++;
/*N*/ }

/*************************************************************************
 *                      SwAttrHandler::SwAttrStack::Remove()
 *************************************************************************/

/*N*/ void SwAttrHandler::SwAttrStack::Remove( const SwTxtAttr& rAttr )
/*N*/ {
/*N*/     USHORT nPos = Pos( rAttr );
/*N*/     if ( nPos < nCount )
/*N*/     {
/*N*/         memmove( pArray + nPos, pArray + nPos + 1,
/*N*/                 ( nCount - 1 - nPos ) * sizeof(SwTxtAttr*)
/*N*/                 );
/*N*/         nCount--;
/*N*/     }
/*N*/ }

/*************************************************************************
 *                      SwAttrHandler::SwAttrStack::Top()
 *************************************************************************/

/*N*/ const SwTxtAttr* SwAttrHandler::SwAttrStack::Top() const
/*N*/ {
/*N*/     return nCount ? pArray[ nCount - 1 ] : 0;
/*N*/ }

/*************************************************************************
 *                      SwAttrHandler::SwAttrStack::Pos()
 *************************************************************************/

/*N*/ USHORT SwAttrHandler::SwAttrStack::Pos( const SwTxtAttr& rAttr ) const
/*N*/ {
/*N*/     if ( ! nCount )
/*N*/         // empty stack
/*?*/         return USHRT_MAX;
/*N*/
/*N*/     for ( USHORT nIdx = nCount; nIdx > 0; )
/*N*/     {
/*N*/         if ( &rAttr == pArray[ --nIdx ] )
/*N*/             return nIdx;
/*N*/     }
/*N*/
/*N*/     // element not found
/*N*/     return USHRT_MAX;
/*N*/ }

/*************************************************************************
 *                      SwAttrHandler::SwAttrHandler()
 *************************************************************************/

/*M*/ SwAttrHandler::SwAttrHandler()
/*M*/  : pShell( 0 )
/*M*/  , bVertLayout( sal_False )
/*M*/  , pFnt( 0 )
/*M*/
/*N*/ {
/*N*/     memset( pDefaultArray, 0, NUM_DEFAULT_VALUES * sizeof(SfxPoolItem*) );
/*N*/ }

/*N*/ SwAttrHandler::~SwAttrHandler()
/*N*/ {
/*N*/     delete pFnt;
/*N*/ }

/*************************************************************************
 *                      SwAttrHandler::Init()
 *************************************************************************/


/*M*/ void SwAttrHandler::Init( const SfxPoolItem** pPoolItem, const SwAttrSet* pAS,
/*M*/                           const SwDoc& rDoc, const ViewShell* pSh,
/*M*/                           SwFont& rFnt, sal_Bool bVL )
/*M*/ {
/*M*/     // initialize default array
/*M*/     memcpy( pDefaultArray, pPoolItem,
/*M*/             NUM_DEFAULT_VALUES * sizeof(SfxPoolItem*) );
/*M*/
/*M*/     pDoc = &rDoc;
/*M*/     pShell = pSh;
/*M*/
/*M*/     // do we have to apply additional paragraph attributes?
/*M*/     bVertLayout = bVL;
/*M*/
/*M*/     if ( pAS && pAS->Count() )
/*M*/     {
/*M*/         SfxItemIter aIter( *pAS );
/*M*/         register USHORT nWhich;
/*M*/         const SfxPoolItem* pItem = aIter.GetCurItem();
/*M*/         while( TRUE )
/*M*/         {
/*M*/             nWhich = pItem->Which();
/*M*/             if( RES_CHRATR_BEGIN <= nWhich && RES_CHRATR_END > nWhich )
/*M*/             {
/*M*/                 pDefaultArray[ StackPos[ nWhich ] ] = pItem;
/*M*/                 FontChg( *pItem, rFnt, sal_True );
/*M*/             }
/*M*/
/*M*/             if( aIter.IsAtEnd() )
/*M*/                 break;
/*M*/
/*M*/             pItem = aIter.NextItem();
/*M*/         }
/*M*/     }
/*M*/
/*M*/     // It is possible, that Init is called more than once, e.g., in a
/*M*/     // SwTxtFrm::FormatOnceMore situation.
/*M*/     delete pFnt;
/*M*/     pFnt = new SwFont( rFnt );
/*M*/ }

/*N*/ void SwAttrHandler::Reset( )
/*N*/ {
/*N*/     for ( USHORT i = 0; i < NUM_ATTRIBUTE_STACKS; i++ )
/*N*/         aAttrStack[ i ].Reset();
/*N*/ }

/*************************************************************************
 *                      SwAttrHandler::PushAndChg()
 *************************************************************************/

/*M*/ void SwAttrHandler::PushAndChg( const SwTxtAttr& rAttr, SwFont& rFnt )
/*M*/ {
/*M*/     // these special attributes in fact represent a collection of attributes
/*M*/     // they have to be pushed to each stack they belong to
/*M*/     if ( RES_TXTATR_INETFMT == rAttr.Which() ||
/*M*/          RES_TXTATR_CHARFMT == rAttr.Which() )
/*M*/     {
/*M*/         SwCharFmt* pFmt;
/*M*/         if( RES_TXTATR_INETFMT == rAttr.Which() )
/*M*/             pFmt = ((SwTxtINetFmt&)rAttr).GetCharFmt();
/*M*/         else
/*M*/             pFmt = rAttr.GetCharFmt().GetCharFmt();
/*M*/
/*M*/         if ( !pFmt )
/*M*/             return;
/*M*/
/*M*/         for ( USHORT i = RES_CHRATR_BEGIN; i < RES_CHRATR_END; i++)
/*M*/         {
/*M*/             const SfxPoolItem* pItem;
/*M*/             BOOL bRet = SFX_ITEM_SET ==
/*M*/                  pFmt->GetItemState( i, TRUE, &pItem );
/*M*/             if ( bRet )
/*M*/             {
/*M*/                 // we push rAttr onto the appropriate stack
/*M*/                 if ( Push( rAttr, *pItem , rFnt ) )
/*M*/                 {
/*M*/                     // we let pItem change rFnt
/*M*/                     if ( !lcl_ChgHyperLinkColor( rAttr, *pItem, pShell ) )
/*M*/                         FontChg( *pItem, rFnt, sal_True );
/*M*/                 }
/*M*/             }
/*M*/         }
/*M*/     }
/*M*/     // this is the usual case, we have a basic attribute, push it onto the
/*M*/     // stack and change the font
/*M*/     else
/*M*/     {
/*M*/         if ( Push( rAttr, rAttr.GetAttr(), rFnt ) )
/*M*/             // we let pItem change rFnt
/*M*/             FontChg( rAttr.GetAttr(), rFnt, sal_True );
/*M*/     }
/*M*/ }

/*************************************************************************
 *                      SwAttrHandler::Push()
 *************************************************************************/

/*M*/ sal_Bool SwAttrHandler::Push( const SwTxtAttr& rAttr, const SfxPoolItem& rItem, SwFont& /*rFnt*/ )
/*M*/ {
/*M*/     OSL_ENSURE( rItem.Which() < RES_TXTATR_WITHEND_END ||
/*M*/             RES_UNKNOWNATR_CONTAINER == rItem.Which() ,
/*M*/             "I do not want this attribute, nWhich >= RES_TXTATR_WITHEND_END" );
/*M*/
/*M*/     // robust
/*M*/     if ( RES_TXTATR_WITHEND_END <= rItem.Which() ||
/*M*/          RES_UNKNOWNATR_CONTAINER == rItem.Which() )
/*M*/         return sal_False;
/*M*/
/*M*/     USHORT nStack = StackPos[ rItem.Which() ];
/*M*/
/*M*/     // attributes originating from redlining have highest priority
/*M*/     // second priority are hyperlink attributes, which have a color replacement
/*M*/     const SwTxtAttr* pTopAttr = aAttrStack[ nStack ].Top();
/*M*/     if ( ! pTopAttr || rAttr.IsPriorityAttr() ||
/*M*/             ( ! pTopAttr->IsPriorityAttr() &&
/*M*/               ! lcl_ChgHyperLinkColor( *pTopAttr, rItem, pShell ) ) )
/*M*/     {
/*M*/         aAttrStack[ nStack ].Push( rAttr );
/*M*/         return sal_True;
/*M*/     }
/*M*/
/*M*/     USHORT nPos = aAttrStack[ nStack ].Count();
/*M*/     OSL_ENSURE( nPos, "empty stack?" );
/*M*/     aAttrStack[ nStack ].Insert( rAttr, nPos - 1 );
/*M*/     return sal_False;
/*M*/ }

/*************************************************************************
 *                      SwAttrHandler::PopAndChg()
 *************************************************************************/

/*N*/ void SwAttrHandler::PopAndChg( const SwTxtAttr& rAttr, SwFont& rFnt )
/*N*/  {
/*N*/      // these special attributes in fact represent a collection of attributes
/*N*/      // they have to be removed from each stack they belong to
/*N*/      if ( RES_TXTATR_INETFMT == rAttr.Which() ||
/*N*/           RES_TXTATR_CHARFMT == rAttr.Which() )
/*N*/      {
/*N*/          SwCharFmt* pFmt;
/*N*/          if( RES_TXTATR_INETFMT == rAttr.Which() )
/*N*/              pFmt = ((SwTxtINetFmt&)rAttr).GetCharFmt();
/*N*/          else
/*N*/              pFmt = rAttr.GetCharFmt().GetCharFmt();
/*N*/
/*N*/          if ( !pFmt )
/*N*/              return;
/*N*/
/*N*/          for ( USHORT i = RES_CHRATR_BEGIN; i < RES_CHRATR_END; i++)
/*N*/          {
/*N*/              const SfxPoolItem* pItem;
/*N*/              BOOL bRet = SFX_ITEM_SET ==
/*N*/                   pFmt->GetItemState( i, TRUE, &pItem );
/*N*/              if ( bRet )
/*N*/              {
/*N*/                  // we remove rAttr from the appropriate stack
/*N*/                  USHORT nStackPos = StackPos[ i ];
/*N*/                  aAttrStack[ nStackPos ].Remove( rAttr );
/*N*/                  // reset font according to attribute on top of stack
/*N*/                  // or default value
/*N*/                  ActivateTop( rFnt, i );
/*N*/              }
/*N*/          }
/*N*/      }
/*N*/      // this is the usual case, we have a basic attribute, remove it from the
/*N*/      // stack and reset the font
/*N*/      else if ( RES_UNKNOWNATR_CONTAINER != rAttr.Which() )
/*N*/      {
/*N*/          aAttrStack[ StackPos[ rAttr.Which() ] ].Remove( rAttr );
/*N*/          // reset font according to attribute on top of stack
/*N*/          // or default value
/*N*/          ActivateTop( rFnt, rAttr.Which() );
/*N*/      }
/*N*/  }

/*************************************************************************
 *                      SwAttrHandler::ActivateTop()
 *************************************************************************/
/*M*/ void SwAttrHandler::ActivateTop( SwFont& rFnt, const USHORT nAttr )
/*M*/ {
/*M*/     OSL_ENSURE( nAttr < RES_TXTATR_WITHEND_END,
/*M*/             "I cannot activate this attribute, nWhich >= RES_TXTATR_WITHEND_END" );
/*M*/
/*M*/     const USHORT nStackPos = StackPos[ nAttr ];
/*M*/     const SwTxtAttr* pTopAt = aAttrStack[ nStackPos ].Top();
/*M*/     if ( pTopAt )
/*M*/     {
/*M*/         // check if top attribute is collection of attributes
/*M*/         if ( RES_TXTATR_INETFMT == pTopAt->Which() ||
/*M*/              RES_TXTATR_CHARFMT == pTopAt->Which() )
/*M*/         {
/*M*/             SwCharFmt* pFmtNext;
/*M*/             if( RES_TXTATR_INETFMT == pTopAt->Which() )
/*M*/                 pFmtNext = ((SwTxtINetFmt*)pTopAt)->GetCharFmt();
/*M*/             else
/*M*/                 pFmtNext = pTopAt->GetCharFmt().GetCharFmt();
/*M*/
/*M*/             const SfxPoolItem* pItemNext;
/*M*/             pFmtNext->GetItemState( nAttr, TRUE, &pItemNext );
/*M*/
/*M*/             if ( !lcl_ChgHyperLinkColor( *pTopAt, *pItemNext, pShell ) )
/*M*/                 FontChg( *pItemNext, rFnt, sal_False );
/*M*/         }
/*M*/         else
/*M*/             FontChg( pTopAt->GetAttr(), rFnt, sal_False );
/*M*/     }
/*M*/
/*M*/     // default value has to be set, we only have default values for char attribs
/*M*/     else if ( nStackPos < NUM_DEFAULT_VALUES )
/*M*/         FontChg( *pDefaultArray[ nStackPos ], rFnt, sal_False );
/*M*/
/*M*/     else if ( RES_TXTATR_REFMARK == nAttr )
/*M*/         rFnt.GetRef()--;
/*M*/     else if ( RES_TXTATR_TOXMARK == nAttr )
/*M*/         rFnt.GetTox()--;
/*M*/ }

/*************************************************************************
 *                      Font Changing Function
 *
 * When popping an attribute from the stack, the top mose remaining
 * attribute in the stack becomes valid. The following function change
 * a font depending on the stack id.
 *************************************************************************/

/*M*/ void SwAttrHandler::FontChg(const SfxPoolItem& rItem, SwFont& rFnt, sal_Bool bPush )
/*M*/ {
/*M*/     switch ( rItem.Which() )
/*M*/     {
/*M*/         case RES_CHRATR_CASEMAP :
/*M*/             rFnt.SetCaseMap( ((SvxCaseMapItem&)rItem).GetCaseMap() );
/*M*/             break;
/*M*/         case RES_CHRATR_COLOR :
/*M*/             rFnt.SetColor( ((SvxColorItem&)rItem).GetValue() );
/*M*/             break;
/*M*/         case RES_CHRATR_CONTOUR :
/*M*/             rFnt.SetOutline( ((SvxContourItem&)rItem).GetValue() );
/*M*/             break;
/*M*/         case RES_CHRATR_CROSSEDOUT :
/*M*/             rFnt.SetStrikeout( ((SvxCrossedOutItem&)rItem).GetStrikeout() );
/*M*/             break;
/*M*/         case RES_CHRATR_ESCAPEMENT :
/*M*/             rFnt.SetEscapement( ((SvxEscapementItem&)rItem).GetEsc() );
/*M*/             rFnt.SetProportion( ((SvxEscapementItem&)rItem).GetProp() );
/*M*/             break;
/*M*/         case RES_CHRATR_FONT :
/*M*/             rFnt.SetName( ((SvxFontItem&)rItem).GetFamilyName(), SW_LATIN );
/*M*/             rFnt.SetStyleName( ((SvxFontItem&)rItem).GetStyleName(), SW_LATIN );
/*M*/             rFnt.SetFamily( ((SvxFontItem&)rItem).GetFamily(), SW_LATIN );
/*M*/             rFnt.SetPitch( ((SvxFontItem&)rItem).GetPitch(), SW_LATIN );
/*M*/             rFnt.SetCharSet( ((SvxFontItem&)rItem).GetCharSet(), SW_LATIN );
/*M*/             break;
/*M*/         case RES_CHRATR_FONTSIZE :
/*M*/             rFnt.SetSize(Size(0,((SvxFontHeightItem&)rItem).GetHeight() ), SW_LATIN );
/*M*/             break;
/*M*/         case RES_CHRATR_KERNING :
/*M*/             rFnt.SetFixKerning( ((SvxKerningItem&)rItem).GetValue() );
/*M*/             break;
/*M*/         case RES_CHRATR_LANGUAGE :
/*M*/             rFnt.SetLanguage( ((SvxLanguageItem&)rItem).GetLanguage(), SW_LATIN );
/*M*/             break;
/*M*/         case RES_CHRATR_POSTURE :
/*M*/             rFnt.SetItalic( ((SvxPostureItem&)rItem).GetPosture(), SW_LATIN );
/*M*/             break;
/*M*/         case RES_CHRATR_SHADOWED :
/*M*/             rFnt.SetShadow( ((SvxShadowedItem&)rItem).GetValue() );
/*M*/             break;
/*M*/         case RES_CHRATR_UNDERLINE :
/*M*/             rFnt.SetUnderline( ((SvxUnderlineItem&)rItem).GetUnderline() );
/*M*/             rFnt.SetUnderColor( ((SvxUnderlineItem&)rItem).GetColor() );
/*M*/             break;
/*M*/         case RES_CHRATR_WEIGHT :
/*M*/             rFnt.SetWeight( ((SvxWeightItem&)rItem).GetWeight(), SW_LATIN );
/*M*/             break;
/*M*/         case RES_CHRATR_WORDLINEMODE :
/*M*/             rFnt.SetWordLineMode( ((SvxWordLineModeItem&)rItem).GetValue() );
/*M*/             break;
/*M*/         case RES_CHRATR_AUTOKERN :
/*M*/             if( ((SvxAutoKernItem&)rItem).GetValue() )
/*M*/                 rFnt.SetAutoKern( ( !pDoc || !pDoc->IsKernAsianPunctuation() ) ?
/*M*/                        KERNING_FONTSPECIFIC : KERNING_ASIAN );
/*M*/           else
/*M*/                 rFnt.SetAutoKern( 0 );
/*M*/             break;
/*M*/         case RES_CHRATR_BLINK :
/*M*/             rFnt.SetBlink( ((SvxBlinkItem&)rItem).GetValue() );
/*M*/             break;
/*M*/         case RES_CHRATR_BACKGROUND :
/*M*/             rFnt.SetBackColor(new Color( ((SvxBrushItem&)rItem).GetColor() ) );
/*M*/             break;
/*M*/         case RES_CHRATR_CJK_FONT :
/*M*/             rFnt.SetName( ((SvxFontItem&)rItem).GetFamilyName(), SW_CJK );
/*M*/             rFnt.SetStyleName( ((SvxFontItem&)rItem).GetStyleName(), SW_CJK );
/*M*/             rFnt.SetFamily( ((SvxFontItem&)rItem).GetFamily(), SW_CJK );
/*M*/             rFnt.SetPitch( ((SvxFontItem&)rItem).GetPitch(), SW_CJK );
/*M*/             rFnt.SetCharSet( ((SvxFontItem&)rItem).GetCharSet(), SW_CJK );
/*M*/             break;
/*M*/         case RES_CHRATR_CJK_FONTSIZE :
/*M*/             rFnt.SetSize(Size( 0, ((SvxFontHeightItem&)rItem).GetHeight()), SW_CJK);
/*M*/             break;
/*M*/         case RES_CHRATR_CJK_LANGUAGE :
/*M*/             rFnt.SetLanguage( ((SvxLanguageItem&)rItem).GetLanguage(), SW_CJK );
/*M*/             break;
/*M*/         case RES_CHRATR_CJK_POSTURE :
/*M*/             rFnt.SetItalic( ((SvxPostureItem&)rItem).GetPosture(), SW_CJK );
/*M*/             break;
/*M*/         case RES_CHRATR_CJK_WEIGHT :
/*M*/             rFnt.SetWeight( ((SvxWeightItem&)rItem).GetWeight(), SW_CJK );
/*M*/             break;
/*M*/         case RES_CHRATR_CTL_FONT :
/*M*/             rFnt.SetName( ((SvxFontItem&)rItem).GetFamilyName(), SW_CTL );
/*M*/             rFnt.SetStyleName( ((SvxFontItem&)rItem).GetStyleName(), SW_CTL );
/*M*/             rFnt.SetFamily( ((SvxFontItem&)rItem).GetFamily(), SW_CTL );
/*M*/             rFnt.SetPitch( ((SvxFontItem&)rItem).GetPitch(), SW_CTL );
/*M*/             rFnt.SetCharSet( ((SvxFontItem&)rItem).GetCharSet(), SW_CTL );
/*M*/             break;
/*M*/         case RES_CHRATR_CTL_FONTSIZE :
/*M*/             rFnt.SetSize(Size(0, ((SvxFontHeightItem&)rItem).GetHeight() ), SW_CTL);
/*M*/             break;
/*M*/         case RES_CHRATR_CTL_LANGUAGE :
/*M*/             rFnt.SetLanguage( ((SvxLanguageItem&)rItem).GetLanguage(), SW_CTL );
/*M*/             break;
/*M*/         case RES_CHRATR_CTL_POSTURE :
/*M*/             rFnt.SetItalic( ((SvxPostureItem&)rItem).GetPosture(), SW_CTL );
/*M*/             break;
/*M*/         case RES_CHRATR_CTL_WEIGHT :
/*M*/             rFnt.SetWeight( ((SvxWeightItem&)rItem).GetWeight(), SW_CTL );
/*M*/             break;
/*M*/         case RES_CHRATR_EMPHASIS_MARK :
/*M*/             rFnt.SetEmphasisMark(
/*M*/                      ((SvxEmphasisMarkItem&)rItem).GetEmphasisMark()
/*M*/                      );
/*M*/             break;
/*M*/         case RES_CHRATR_SCALEW :
/*M*/             rFnt.SetPropWidth( ((SvxCharScaleWidthItem&)rItem).GetValue() );
/*M*/             break;
/*M*/         case RES_CHRATR_RELIEF :
/*M*/             rFnt.SetRelief( (FontRelief)((SvxCharReliefItem&)rItem).GetValue() );
/*M*/             break;
/*M*/
/*M*/         case RES_CHRATR_ROTATE :
/*M*/         {
/*M*/             // rotate attribute is applied, when:
/*M*/             // 1. ruby stack is empty and
/*M*/             // 2. top of two line stack ( or default attribute )is an
/*M*/             //    deactivated two line attribute
/*M*/             sal_Bool bRuby = 0 !=
/*M*/                              aAttrStack[ StackPos[ RES_TXTATR_CJK_RUBY ] ].Count();
/*M*/
/*M*/             if ( bRuby )
/*M*/                 break;
/*M*/
/*M*/             USHORT nTwoLineStack = StackPos[ RES_CHRATR_TWO_LINES ];
/*M*/             sal_Bool bTwoLineAct = sal_False;
/*M*/             const SfxPoolItem* pTwoLineItem = 0;
/*M*/             const SwTxtAttr* pTwoLineAttr = aAttrStack[ nTwoLineStack ].Top();
/*M*/
/*M*/             if ( pTwoLineAttr )
/*?*/                 bTwoLineAct = ((SvxTwoLinesItem*)pTwoLineItem)->GetValue();
/*M*/             else
/*M*/                 bTwoLineAct =
/*M*/                     ((SvxTwoLinesItem*)pDefaultArray[ nTwoLineStack ])->GetValue();
/*M*/
/*M*/             if ( !bTwoLineAct )
/*M*/                 rFnt.SetVertical( ((SvxCharRotateItem&)rItem).GetValue(),
/*M*/                                    bVertLayout );
/*M*/
/*M*/             break;
/*M*/         }
/*M*/         case RES_CHRATR_TWO_LINES :
/*M*/         {
/*M*/             sal_Bool bRuby = 0 !=
/*M*/                     aAttrStack[ StackPos[ RES_TXTATR_CJK_RUBY ] ].Count();
/*M*/             sal_Bool bTwoLineAct = sal_False;
/*M*/
/*M*/             // two line is activated, if
/*M*/             // 1. no ruby attribute is set and
/*M*/             // 2. attribute is active
/*M*/             bTwoLineAct = ((SvxTwoLinesItem&)rItem).GetValue();
/*M*/
/*M*/             if ( !bRuby && bTwoLineAct )
/*M*/             {
/*M*/                 rFnt.SetVertical( 0, bVertLayout );
/*M*/                 break;
/*M*/             }
/*M*/
/*M*/             // a deactivating two line attribute is on top of stack,
/*M*/             // check if rotate attribute has to be enabled
/*M*/             if ( bRuby )
/*M*/                 break;
/*M*/
/*M*/             USHORT nRotateStack = StackPos[ RES_CHRATR_ROTATE ];
/*M*/             const SwTxtAttr* pRotateAttr = aAttrStack[ nRotateStack ].Top();
/*M*/
/*M*/             if ( !pRotateAttr )
/*M*/                 rFnt.SetVertical(
/*M*/                     ((SvxCharRotateItem*)pDefaultArray[ nRotateStack ])->GetValue(),
/*M*/                      bVertLayout
/*M*/                 );
/*M*/             break;
/*M*/         }
/*M*/         case RES_TXTATR_CJK_RUBY :
/*M*/             rFnt.SetVertical( 0, bVertLayout );
/*M*/             break;
/*M*/         case RES_TXTATR_REFMARK :
/*M*/             if ( bPush )
/*M*/                 rFnt.GetRef()++;
/*M*/             else
/*M*/                 rFnt.GetRef()--;
/*M*/             break;
/*M*/         case RES_TXTATR_TOXMARK :
/*M*/             if ( bPush )
/*M*/                 rFnt.GetTox()++;
/*M*/             else
/*M*/                 rFnt.GetTox()--;
/*M*/             break;
/*M*/     }
/*M*/ }

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
