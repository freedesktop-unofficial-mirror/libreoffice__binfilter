/*************************************************************************
 *
 *  $RCSfile: sc_editutil.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 14:43:29 $
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

// System - Includes -----------------------------------------------------

#ifdef PCH
#include "core_pch.hxx"
#endif

#pragma hdrstop

// INCLUDE ---------------------------------------------------------------

#include "scitems.hxx"
#include <bf_svx/eeitem.hxx>
#define ITEMID_FIELD EE_FEATURE_FIELD

#include <bf_svx/algitem.hxx>
#include <svtools/colorcfg.hxx>
#include <bf_svx/editview.hxx>
#include <bf_svx/editstat.hxx>
#include <bf_svx/escpitem.hxx>
#include <bf_svx/flditem.hxx>
#include <vcl/system.hxx>
#include <vcl/svapp.hxx>
#include <vcl/outdev.hxx>
#include <svtools/inethist.hxx>
#ifndef INCLUDED_SVTOOLS_SYSLOCALE_HXX
#include <svtools/syslocale.hxx>
#endif
#ifndef _SVSTDARR_USHORTS
#define _SVSTDARR_USHORTS
#include <svtools/svstdarr.hxx>
#endif

#include "editutil.hxx"
#include "global.hxx"
#include "attrib.hxx"
#include "document.hxx"
#include "docpool.hxx"
#include "patattr.hxx"
#include "scmod.hxx"
#include "inputopt.hxx"

// STATIC DATA -----------------------------------------------------------

//  Delimiters zusaetzlich zu EditEngine-Default:

const sal_Char __FAR_DATA ScEditUtil::pCalcDelimiters[] = "=();+-*/^&<>";


//------------------------------------------------------------------------

/*N*/ String ScEditUtil::ModifyDelimiters( const String& rOld )
/*N*/ {
/*N*/   String aRet = rOld;
/*N*/   aRet.EraseAllChars( '_' );  // underscore is used in function argument names
/*N*/   aRet.AppendAscii( RTL_CONSTASCII_STRINGPARAM( pCalcDelimiters ) );
/*N*/   return aRet;
/*N*/ }

/*N*/ String ScEditUtil::GetSpaceDelimitedString( const EditEngine& rEngine )
/*N*/ {
/*N*/   String aRet;
/*N*/   USHORT nParCount = rEngine.GetParagraphCount();
/*N*/   for (USHORT nPar=0; nPar<nParCount; nPar++)
/*N*/   {
/*N*/       if (nPar > 0)
/*N*/           aRet += ' ';
/*N*/       aRet += rEngine.GetText( nPar );
/*N*/   }
/*N*/   return aRet;
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 Rectangle ScEditUtil::GetEditArea( const ScPatternAttr* pPattern, BOOL bForceToTop )
//STRIP001 {
//STRIP001  // bForceToTop = always align to top, for editing
//STRIP001  // (FALSE for querying URLs etc.)
//STRIP001
//STRIP001  USHORT i;
//STRIP001
//STRIP001  if (!pPattern)
//STRIP001      pPattern = pDoc->GetPattern( nCol, nRow, nTab );
//STRIP001
//STRIP001  Point aStartPos = aScrPos;
//STRIP001
//STRIP001  const ScMergeAttr* pMerge = (const ScMergeAttr*)&pPattern->GetItem(ATTR_MERGE);
//STRIP001  long nCellX = (long) ( pDoc->GetColWidth(nCol,nTab) * nPPTX );
//STRIP001  if ( pMerge->GetColMerge() > 1 )
//STRIP001  {
//STRIP001      USHORT nCountX = pMerge->GetColMerge();
//STRIP001      for (i=1; i<nCountX; i++)
//STRIP001          nCellX += (long) ( pDoc->GetColWidth(nCol+i,nTab) * nPPTX );
//STRIP001  }
//STRIP001  long nCellY = (long) ( pDoc->GetRowHeight(nRow,nTab) * nPPTY );
//STRIP001  if ( pMerge->GetRowMerge() > 1 )
//STRIP001  {
//STRIP001      USHORT nCountY = pMerge->GetRowMerge();
//STRIP001      for (i=1; i<nCountY; i++)
//STRIP001          nCellY += (long) ( pDoc->GetRowHeight(nRow+i,nTab) * nPPTY );
//STRIP001  }
//STRIP001
//STRIP001  const SvxMarginItem* pMargin = (const SvxMarginItem*)&pPattern->GetItem(ATTR_MARGIN);
//STRIP001  USHORT nIndent = 0;
//STRIP001  if ( ((const SvxHorJustifyItem&)pPattern->GetItem(ATTR_HOR_JUSTIFY)).GetValue() ==
//STRIP001              SVX_HOR_JUSTIFY_LEFT )
//STRIP001      nIndent = ((const SfxUInt16Item&)pPattern->GetItem(ATTR_INDENT)).GetValue();
//STRIP001  long nPixDifX   = (long) ( ( pMargin->GetLeftMargin() + nIndent ) * nPPTX );
//STRIP001  aStartPos.X()   += nPixDifX;
//STRIP001  nCellX          -= nPixDifX + (long) ( pMargin->GetRightMargin() * nPPTX );     // wegen Umbruch etc.
//STRIP001
//STRIP001  //  vertikale Position auf die in der Tabelle anpassen
//STRIP001
//STRIP001  long nPixDifY;
//STRIP001  long nTopMargin = (long) ( pMargin->GetTopMargin() * nPPTY );
//STRIP001  SvxCellVerJustify eJust = (SvxCellVerJustify) ((const SvxVerJustifyItem&)pPattern->
//STRIP001                                              GetItem(ATTR_VER_JUSTIFY)).GetValue();
//STRIP001
//STRIP001  //  asian vertical is always edited top-aligned
//STRIP001  BOOL bAsianVertical = (SvxCellOrientation)((const SvxOrientationItem&)
//STRIP001          pPattern->GetItem(ATTR_ORIENTATION)).GetValue() == SVX_ORIENTATION_STACKED &&
//STRIP001      ((const SfxBoolItem&)pPattern->GetItem( ATTR_VERTICAL_ASIAN )).GetValue();
//STRIP001
//STRIP001  if ( eJust == SVX_VER_JUSTIFY_TOP ||
//STRIP001          ( bForceToTop && ( SC_MOD()->GetInputOptions().GetTextWysiwyg() || bAsianVertical ) ) )
//STRIP001      nPixDifY = nTopMargin;
//STRIP001  else
//STRIP001  {
//STRIP001      MapMode aMode = pDev->GetMapMode();
//STRIP001      pDev->SetMapMode( MAP_PIXEL );
//STRIP001
//STRIP001      long nTextHeight = pDoc->GetNeededSize( nCol, nRow, nTab,
//STRIP001                                              pDev, nPPTX, nPPTY, aZoomX, aZoomY, FALSE );
//STRIP001      if (!nTextHeight)
//STRIP001      {                                   // leere Zelle
//STRIP001          Font aFont;
//STRIP001          // font color doesn't matter here
//STRIP001          pPattern->GetFont( aFont, SC_AUTOCOL_BLACK, pDev, &aZoomY );
//STRIP001          pDev->SetFont(aFont);
//STRIP001          nTextHeight = pDev->GetTextHeight() + nTopMargin +
//STRIP001                          (long) ( pMargin->GetBottomMargin() * nPPTY );
//STRIP001      }
//STRIP001
//STRIP001      pDev->SetMapMode(aMode);
//STRIP001
//STRIP001      if ( nTextHeight > nCellY + nTopMargin || bForceToTop )
//STRIP001          nPixDifY = 0;                           // zu gross -> oben anfangen
//STRIP001      else
//STRIP001      {
//STRIP001          if ( eJust == SVX_VER_JUSTIFY_CENTER )
//STRIP001              nPixDifY = nTopMargin + ( nCellY - nTextHeight ) / 2;
//STRIP001          else
//STRIP001              nPixDifY = nCellY - nTextHeight + nTopMargin;       // JUSTIFY_BOTTOM
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  aStartPos.Y() += nPixDifY;
//STRIP001  nCellY      -= nPixDifY;
//STRIP001
//STRIP001                                                      //  -1 -> Gitter nicht ueberschreiben
//STRIP001  return Rectangle( aStartPos, Size(nCellX-1,nCellY-1) );
//STRIP001 }

//------------------------------------------------------------------------

/*N*/ ScEditAttrTester::ScEditAttrTester( EditEngine* pEng ) :
/*N*/   pEngine( pEng ),
/*N*/   pEditAttrs( NULL ),
/*N*/   bNeedsObject( FALSE ),
/*N*/   bNeedsCellAttr( FALSE )
/*N*/ {
/*N*/   if ( pEngine->GetParagraphCount() > 1 )
/*N*/   {
/*N*/       bNeedsObject = TRUE;            //! Zellatribute finden ?
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       const SfxPoolItem* pItem = NULL;
/*N*/       pEditAttrs = new SfxItemSet( pEngine->GetAttribs(
/*N*/                                       ESelection(0,0,0,pEngine->GetTextLen(0)) ) );
/*N*/       const SfxItemPool* pEditPool = pEditAttrs->GetPool();
/*N*/
/*N*/       for (USHORT nId = EE_CHAR_START; nId <= EE_CHAR_END && !bNeedsObject; nId++)
/*N*/       {
/*N*/           SfxItemState eState = pEditAttrs->GetItemState( nId, FALSE, &pItem );
/*N*/           if (eState == SFX_ITEM_DONTCARE)
/*N*/               bNeedsObject = TRUE;
/*N*/           else if (eState == SFX_ITEM_SET)
/*N*/           {
/*N*/               if ( nId == EE_CHAR_ESCAPEMENT || nId == EE_CHAR_PAIRKERNING ||
/*N*/                       nId == EE_CHAR_KERNING || nId == EE_CHAR_XMLATTRIBS )
/*N*/               {
/*N*/                   //  Escapement and kerning are kept in EditEngine because there are no
/*N*/                   //  corresponding cell format items. User defined attributes are kept in
/*N*/                   //  EditEngine because "user attributes applied to all the text" is different
/*N*/                   //  from "user attributes applied to the cell".
/*N*/
/*N*/                   if ( *pItem != pEditPool->GetDefaultItem(nId) )
/*N*/                       bNeedsObject = TRUE;
/*N*/               }
/*N*/               else
/*N*/                   if (!bNeedsCellAttr)
/*N*/                       if ( *pItem != pEditPool->GetDefaultItem(nId) )
/*N*/                           bNeedsCellAttr = TRUE;
/*N*/               //  SetDefaults an der EditEngine setzt Pool-Defaults
/*N*/           }
/*N*/       }
/*N*/
/*N*/       //  Feldbefehle enthalten?
/*N*/
/*N*/       SfxItemState eFieldState = pEditAttrs->GetItemState( EE_FEATURE_FIELD, FALSE );
/*N*/       if ( eFieldState == SFX_ITEM_DONTCARE || eFieldState == SFX_ITEM_SET )
/*N*/           bNeedsObject = TRUE;
/*N*/
/*N*/       //  not converted characters?
/*N*/
/*N*/       SfxItemState eConvState = pEditAttrs->GetItemState( EE_FEATURE_NOTCONV, FALSE );
/*N*/       if ( eConvState == SFX_ITEM_DONTCARE || eConvState == SFX_ITEM_SET )
/*N*/           bNeedsObject = TRUE;
/*N*/   }
/*N*/ }

/*N*/ ScEditAttrTester::~ScEditAttrTester()
/*N*/ {
/*N*/   delete pEditAttrs;
/*N*/ }


//------------------------------------------------------------------------

/*N*/ ScEnginePoolHelper::ScEnginePoolHelper( SfxItemPool* pEnginePoolP,
/*N*/               BOOL bDeleteEnginePoolP )
/*N*/           :
/*N*/           pEnginePool( pEnginePoolP ),
/*N*/           bDeleteEnginePool( bDeleteEnginePoolP ),
/*N*/           pDefaults( NULL ),
/*N*/           bDeleteDefaults( FALSE )
/*N*/ {
/*N*/ }


/*N*/ ScEnginePoolHelper::ScEnginePoolHelper( const ScEnginePoolHelper& rOrg )
/*N*/           :
/*N*/           pEnginePool( rOrg.bDeleteEnginePool ? rOrg.pEnginePool->Clone() : rOrg.pEnginePool ),
/*N*/           bDeleteEnginePool( rOrg.bDeleteEnginePool ),
/*N*/           pDefaults( NULL ),
/*N*/           bDeleteDefaults( FALSE )
/*N*/ {
/*N*/ }


/*N*/ ScEnginePoolHelper::~ScEnginePoolHelper()
/*N*/ {
/*N*/   if ( bDeleteDefaults )
/*N*/       delete pDefaults;
/*N*/   if ( bDeleteEnginePool )
/*N*/       delete pEnginePool;
/*N*/ }


//------------------------------------------------------------------------

/*N*/ ScEditEngineDefaulter::ScEditEngineDefaulter( SfxItemPool* pEnginePoolP,
/*N*/               BOOL bDeleteEnginePoolP )
/*N*/           :
/*N*/           ScEnginePoolHelper( pEnginePoolP, bDeleteEnginePoolP ),
/*N*/           EditEngine( pEnginePoolP )
/*N*/ {
/*N*/   //  All EditEngines use ScGlobal::GetEditDefaultLanguage as DefaultLanguage.
/*N*/   //  DefaultLanguage for InputHandler's EditEngine is updated later.
/*N*/
/*N*/   SetDefaultLanguage( ScGlobal::GetEditDefaultLanguage() );
/*N*/ }


/*N*/ ScEditEngineDefaulter::ScEditEngineDefaulter( const ScEditEngineDefaulter& rOrg )
/*N*/           :
/*N*/           ScEnginePoolHelper( rOrg ),
/*N*/           EditEngine( pEnginePool )
/*N*/ {
/*N*/   SetDefaultLanguage( ScGlobal::GetEditDefaultLanguage() );
/*N*/ }


/*N*/ ScEditEngineDefaulter::~ScEditEngineDefaulter()
/*N*/ {
/*N*/ }


/*N*/ void ScEditEngineDefaulter::SetDefaults( const SfxItemSet& rSet, BOOL bRememberCopy )
/*N*/ {
/*N*/   if ( bRememberCopy )
/*N*/   {
/*N*/       if ( bDeleteDefaults )
/*N*/           delete pDefaults;
/*N*/       pDefaults = new SfxItemSet( rSet );
/*N*/       bDeleteDefaults = TRUE;
/*N*/   }
/*N*/   const SfxItemSet& rNewSet = bRememberCopy ? *pDefaults : rSet;
/*N*/   BOOL bUndo = IsUndoEnabled();
/*N*/   EnableUndo( FALSE );
/*N*/   BOOL bUpdateMode = GetUpdateMode();
/*N*/   if ( bUpdateMode )
/*N*/       SetUpdateMode( FALSE );
/*N*/   USHORT nPara = GetParagraphCount();
/*N*/   for ( USHORT j=0; j<nPara; j++ )
/*N*/   {
/*N*/       SetParaAttribs( j, rNewSet );
/*N*/   }
/*N*/   if ( bUpdateMode )
/*N*/       SetUpdateMode( TRUE );
/*N*/   if ( bUndo )
/*N*/       EnableUndo( TRUE );
/*N*/ }


/*N*/ void ScEditEngineDefaulter::SetDefaults( SfxItemSet* pSet, BOOL bTakeOwnership )
/*N*/ {
/*N*/   if ( bDeleteDefaults )
/*N*/       delete pDefaults;
/*N*/   pDefaults = pSet;
/*N*/   bDeleteDefaults = bTakeOwnership;
/*N*/   if ( pDefaults )
/*N*/       SetDefaults( *pDefaults, FALSE );
/*N*/ }


//STRIP001 void ScEditEngineDefaulter::SetDefaultItem( const SfxPoolItem& rItem )
//STRIP001 {
//STRIP001  if ( !pDefaults )
//STRIP001  {
//STRIP001      pDefaults = new SfxItemSet( GetEmptyItemSet() );
//STRIP001      bDeleteDefaults = TRUE;
//STRIP001  }
//STRIP001  pDefaults->Put( rItem );
//STRIP001  SetDefaults( *pDefaults, FALSE );
//STRIP001 }


/*N*/ void ScEditEngineDefaulter::SetText( const EditTextObject& rTextObject )
/*N*/ {
/*N*/   BOOL bUpdateMode = GetUpdateMode();
/*N*/   if ( bUpdateMode )
/*N*/       SetUpdateMode( FALSE );
/*N*/   EditEngine::SetText( rTextObject );
/*N*/   if ( pDefaults )
/*N*/       SetDefaults( *pDefaults, FALSE );
/*N*/   if ( bUpdateMode )
/*N*/       SetUpdateMode( TRUE );
/*N*/ }

/*N*/ void ScEditEngineDefaulter::SetTextNewDefaults( const EditTextObject& rTextObject,
/*N*/           const SfxItemSet& rSet, BOOL bRememberCopy )
/*N*/ {
/*N*/   BOOL bUpdateMode = GetUpdateMode();
/*N*/   if ( bUpdateMode )
/*N*/       SetUpdateMode( FALSE );
/*N*/   EditEngine::SetText( rTextObject );
/*N*/   SetDefaults( rSet, bRememberCopy );
/*N*/   if ( bUpdateMode )
/*N*/       SetUpdateMode( TRUE );
/*N*/ }

/*N*/ void ScEditEngineDefaulter::SetTextNewDefaults( const EditTextObject& rTextObject,
/*N*/           SfxItemSet* pSet, BOOL bTakeOwnership )
/*N*/ {
/*N*/   BOOL bUpdateMode = GetUpdateMode();
/*N*/   if ( bUpdateMode )
/*?*/       SetUpdateMode( FALSE );
/*N*/   EditEngine::SetText( rTextObject );
/*N*/   SetDefaults( pSet, bTakeOwnership );
/*N*/   if ( bUpdateMode )
/*?*/       SetUpdateMode( TRUE );
/*N*/ }


/*N*/ void ScEditEngineDefaulter::SetText( const String& rText )
/*N*/ {
/*N*/   BOOL bUpdateMode = GetUpdateMode();
/*N*/   if ( bUpdateMode )
/*N*/       SetUpdateMode( FALSE );
/*N*/   EditEngine::SetText( rText );
/*N*/   if ( pDefaults )
/*?*/       SetDefaults( *pDefaults, FALSE );
/*N*/   if ( bUpdateMode )
/*N*/       SetUpdateMode( TRUE );
/*N*/ }

/*N*/ void ScEditEngineDefaulter::SetTextNewDefaults( const String& rText,
/*N*/           const SfxItemSet& rSet, BOOL bRememberCopy )
/*N*/ {
/*N*/   BOOL bUpdateMode = GetUpdateMode();
/*N*/   if ( bUpdateMode )
/*N*/       SetUpdateMode( FALSE );
/*N*/   EditEngine::SetText( rText );
/*N*/   SetDefaults( rSet, bRememberCopy );
/*N*/   if ( bUpdateMode )
/*N*/       SetUpdateMode( TRUE );
/*N*/ }

/*N*/ void ScEditEngineDefaulter::SetTextNewDefaults( const String& rText,
/*N*/           SfxItemSet* pSet, BOOL bTakeOwnership )
/*N*/ {
/*N*/   BOOL bUpdateMode = GetUpdateMode();
/*N*/   if ( bUpdateMode )
/*?*/       SetUpdateMode( FALSE );
/*N*/   EditEngine::SetText( rText );
/*N*/   SetDefaults( pSet, bTakeOwnership );
/*N*/   if ( bUpdateMode )
/*?*/       SetUpdateMode( TRUE );
/*N*/ }

//STRIP001 void ScEditEngineDefaulter::RepeatDefaults()
//STRIP001 {
//STRIP001     if ( pDefaults )
//STRIP001     {
//STRIP001         USHORT nPara = GetParagraphCount();
//STRIP001         for ( USHORT j=0; j<nPara; j++ )
//STRIP001             SetParaAttribs( j, *pDefaults );
//STRIP001     }
//STRIP001 }

//STRIP001 void ScEditEngineDefaulter::RemoveParaAttribs()
//STRIP001 {
//STRIP001  SfxItemSet* pCharItems = NULL;
//STRIP001  BOOL bUpdateMode = GetUpdateMode();
//STRIP001  if ( bUpdateMode )
//STRIP001      SetUpdateMode( FALSE );
//STRIP001  USHORT nParCount = GetParagraphCount();
//STRIP001  for (USHORT nPar=0; nPar<nParCount; nPar++)
//STRIP001  {
//STRIP001      const SfxItemSet& rParaAttribs = GetParaAttribs( nPar );
//STRIP001      USHORT nWhich;
//STRIP001      for (nWhich = EE_CHAR_START; nWhich <= EE_CHAR_END; nWhich ++)
//STRIP001      {
//STRIP001          const SfxPoolItem* pParaItem;
//STRIP001          if ( rParaAttribs.GetItemState( nWhich, FALSE, &pParaItem ) == SFX_ITEM_SET )
//STRIP001          {
//STRIP001              //  if defaults are set, use only items that are different from default
//STRIP001              if ( !pDefaults || *pParaItem != pDefaults->Get(nWhich) )
//STRIP001              {
//STRIP001                  if (!pCharItems)
//STRIP001                      pCharItems = new SfxItemSet( GetEmptyItemSet() );
//STRIP001                  pCharItems->Put( *pParaItem );
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      if ( pCharItems )
//STRIP001      {
//STRIP001          SvUShorts aPortions;
//STRIP001          GetPortions( nPar, aPortions );
//STRIP001
//STRIP001          //  loop through the portions of the paragraph, and set only those items
//STRIP001          //  that are not overridden by existing character attributes
//STRIP001
//STRIP001          USHORT nPCount = aPortions.Count();
//STRIP001          USHORT nStart = 0;
//STRIP001          for ( USHORT nPos=0; nPos<nPCount; nPos++ )
//STRIP001          {
//STRIP001              USHORT nEnd = aPortions.GetObject( nPos );
//STRIP001              ESelection aSel( nPar, nStart, nPar, nEnd );
//STRIP001              SfxItemSet aOldCharAttrs = GetAttribs( aSel );
//STRIP001              SfxItemSet aNewCharAttrs = *pCharItems;
//STRIP001              for (nWhich = EE_CHAR_START; nWhich <= EE_CHAR_END; nWhich ++)
//STRIP001              {
//STRIP001                  //  Clear those items that are different from existing character attributes.
//STRIP001                  //  Where no character attributes are set, GetAttribs returns the paragraph attributes.
//STRIP001                  const SfxPoolItem* pItem;
//STRIP001                  if ( aNewCharAttrs.GetItemState( nWhich, FALSE, &pItem ) == SFX_ITEM_SET &&
//STRIP001                       *pItem != aOldCharAttrs.Get(nWhich) )
//STRIP001                  {
//STRIP001                      aNewCharAttrs.ClearItem(nWhich);
//STRIP001                  }
//STRIP001              }
//STRIP001              if ( aNewCharAttrs.Count() )
//STRIP001                  QuickSetAttribs( aNewCharAttrs, aSel );
//STRIP001
//STRIP001              nStart = nEnd;
//STRIP001          }
//STRIP001
//STRIP001          DELETEZ( pCharItems );
//STRIP001      }
//STRIP001
//STRIP001      if ( rParaAttribs.Count() )
//STRIP001      {
//STRIP001          //  clear all paragraph attributes (including defaults),
//STRIP001          //  so they are not contained in resulting EditTextObjects
//STRIP001
//STRIP001          SetParaAttribs( nPar, SfxItemSet( *rParaAttribs.GetPool(), rParaAttribs.GetRanges() ) );
//STRIP001      }
//STRIP001  }
//STRIP001  if ( bUpdateMode )
//STRIP001      SetUpdateMode( TRUE );
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 ScTabEditEngine::ScTabEditEngine( ScDocument* pDoc )
//STRIP001      : ScEditEngineDefaulter( pDoc->GetEnginePool() )
//STRIP001 {
//STRIP001  SetEditTextObjectPool( pDoc->GetEditPool() );
//STRIP001  Init((const ScPatternAttr&)pDoc->GetPool()->GetDefaultItem(ATTR_PATTERN));
//STRIP001 }

//STRIP001 ScTabEditEngine::ScTabEditEngine( const ScPatternAttr& rPattern,
//STRIP001          SfxItemPool* pEnginePool, SfxItemPool* pTextObjectPool )
//STRIP001      : ScEditEngineDefaulter( pEnginePool )
//STRIP001 {
//STRIP001  if ( pTextObjectPool )
//STRIP001      SetEditTextObjectPool( pTextObjectPool );
//STRIP001  Init( rPattern );
//STRIP001 }

//STRIP001 void ScTabEditEngine::Init( const ScPatternAttr& rPattern )
//STRIP001 {
//STRIP001  SetRefMapMode(MAP_100TH_MM);
//STRIP001  SfxItemSet* pEditDefaults = new SfxItemSet( GetEmptyItemSet() );
//STRIP001  rPattern.FillEditItemSet( pEditDefaults );
//STRIP001  SetDefaults( pEditDefaults );
//STRIP001  // wir haben keine StyleSheets fuer Text
//STRIP001  SetControlWord( GetControlWord() & ~EE_CNTRL_RTFSTYLESHEETS );
//STRIP001 }

//------------------------------------------------------------------------
//      Feldbefehle fuer Kopf- und Fusszeilen
//------------------------------------------------------------------------

//
//      Zahlen aus \sw\source\core\doc\numbers.cxx
//

//STRIP001 String lcl_GetRomanStr( USHORT nNo )
//STRIP001 {
//STRIP001  String aStr;
//STRIP001  if( nNo < 4000 )        // mehr kann nicht dargestellt werden
//STRIP001  {
//STRIP001 //       i, ii, iii, iv, v, vi, vii, vii, viii, ix
//STRIP001 //                           (Dummy),1000,500,100,50,10,5,1
//STRIP001      sal_Char *cRomanArr = "mdclxvi--";  // +2 Dummy-Eintraege !!
//STRIP001      USHORT nMask = 1000;
//STRIP001      while( nMask )
//STRIP001      {
//STRIP001          BYTE nZahl = BYTE(nNo / nMask);
//STRIP001          BYTE nDiff = 1;
//STRIP001          nNo %= nMask;
//STRIP001
//STRIP001          if( 5 < nZahl )
//STRIP001          {
//STRIP001              if( nZahl < 9 )
//STRIP001                  aStr += *(cRomanArr-1);
//STRIP001              ++nDiff;
//STRIP001              nZahl -= 5;
//STRIP001          }
//STRIP001          switch( nZahl )
//STRIP001          {
//STRIP001          case 3:     { aStr += *cRomanArr; }
//STRIP001          case 2:     { aStr += *cRomanArr; }
//STRIP001          case 1:     { aStr += *cRomanArr; }
//STRIP001                      break;
//STRIP001
//STRIP001          case 4:     {
//STRIP001                        aStr += *cRomanArr;
//STRIP001                        aStr += *(cRomanArr-nDiff);
//STRIP001                      }
//STRIP001                      break;
//STRIP001          case 5:     { aStr += *(cRomanArr-nDiff); }
//STRIP001                      break;
//STRIP001          }
//STRIP001
//STRIP001          nMask /= 10;            // zur naechsten Dekade
//STRIP001          cRomanArr += 2;
//STRIP001      }
//STRIP001  }
//STRIP001  return aStr;
//STRIP001 }

//STRIP001 String lcl_GetCharStr( USHORT nNo )
//STRIP001 {
//STRIP001  DBG_ASSERT( nNo, "0 ist eine ungueltige Nummer !!" );
//STRIP001  String aStr;
//STRIP001
//STRIP001  const USHORT coDiff = 'Z' - 'A' +1;
//STRIP001  USHORT nCalc;
//STRIP001
//STRIP001  do {
//STRIP001      nCalc = nNo % coDiff;
//STRIP001      if( !nCalc )
//STRIP001          nCalc = coDiff;
//STRIP001      aStr.Insert( (sal_Unicode)('a' - 1 + nCalc ), 0 );
//STRIP001      nNo -= nCalc;
//STRIP001      if( nNo )
//STRIP001          nNo /= coDiff;
//STRIP001  } while( nNo );
//STRIP001  return aStr;
//STRIP001 }

/*N*/ String lcl_GetNumStr( USHORT nNo, SvxNumType eType )
/*N*/ {
/*N*/   String aTmpStr( '0' );
/*N*/   if( nNo )
/*N*/   {
/*N*/       switch( eType )
/*N*/       {
/*?*/       case SVX_CHARS_UPPER_LETTER:
/*?*/       case SVX_CHARS_LOWER_LETTER:
/*?*/           DBG_ASSERT(0, "STRIP"); //STRIP001 aTmpStr = lcl_GetCharStr( nNo );
/*?*/           break;
/*?*/
/*?*/       case SVX_ROMAN_UPPER:
/*?*/       case SVX_ROMAN_LOWER:
/*?*/           DBG_ASSERT(0, "STRIP"); //STRIP001 aTmpStr = lcl_GetRomanStr( nNo );
/*?*/           break;
/*?*/
/*?*/       case SVX_NUMBER_NONE:
/*?*/           aTmpStr.Erase();
/*?*/           break;
/*?*/
/*?*/ //        CHAR_SPECIAL:
/*?*/ //            ????
/*?*/
/*?*/ //        case ARABIC:    ist jetzt default
/*N*/       default:
/*N*/           aTmpStr = String::CreateFromInt32( nNo );
/*N*/           break;
/*N*/       }
/*N*/
/*N*/       if( SVX_CHARS_UPPER_LETTER == eType || SVX_ROMAN_UPPER == eType )
/*N*/           aTmpStr.ToUpperAscii();
/*N*/   }
/*N*/   return aTmpStr;
/*N*/ }

/*N*/ ScHeaderFieldData::ScHeaderFieldData()
/*N*/ {
/*N*/   nPageNo = nTotalPages = 0;
/*N*/   eNumType = SVX_ARABIC;
/*N*/ }

/*N*/ ScHeaderEditEngine::ScHeaderEditEngine( SfxItemPool* pEnginePool, BOOL bDeleteEnginePool )
/*N*/       : ScEditEngineDefaulter( pEnginePool, bDeleteEnginePool )
/*N*/ {
/*N*/ }

/*N*/ String __EXPORT ScHeaderEditEngine::CalcFieldValue( const SvxFieldItem& rField,
/*N*/                                   USHORT nPara, USHORT nPos,
/*N*/                                   Color*& rTxtColor, Color*& rFldColor )
/*N*/ {
/*N*/   String aRet;
/*N*/   const SvxFieldData* pFieldData = rField.GetField();
/*N*/   if ( pFieldData )
/*N*/   {
/*N*/       TypeId aType = pFieldData->Type();
/*N*/       if (aType == TYPE(SvxPageField))
/*N*/           aRet = lcl_GetNumStr( (USHORT)aData.nPageNo,aData.eNumType );
/*N*/       else if (aType == TYPE(SvxPagesField))
/*?*/           aRet = lcl_GetNumStr( (USHORT)aData.nTotalPages,aData.eNumType );
/*N*/       else if (aType == TYPE(SvxTimeField))
/*N*/             aRet = ScGlobal::pLocaleData->getTime(aData.aTime);
/*N*/       else if (aType == TYPE(SvxFileField))
/*N*/           aRet = aData.aTitle;
/*N*/       else if (aType == TYPE(SvxExtFileField))
/*N*/       {
/*?*/           switch ( ((const SvxExtFileField*)pFieldData)->GetFormat() )
/*?*/           {
/*?*/               case SVXFILEFORMAT_FULLPATH :
/*?*/                   aRet = aData.aLongDocName;
/*?*/               break;
/*?*/               default:
/*?*/                   aRet = aData.aShortDocName;
/*?*/           }
/*N*/       }
/*N*/       else if (aType == TYPE(SvxTableField))
/*N*/           aRet = aData.aTabName;
/*N*/       else if (aType == TYPE(SvxDateField))
/*N*/             aRet = ScGlobal::pLocaleData->getDate(aData.aDate);
/*N*/       else
/*N*/       {
/*N*/           //DBG_ERROR("unbekannter Feldbefehl");
/*N*/           aRet = '?';
/*N*/       }
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       DBG_ERROR("FieldData ist 0");
/*N*/       aRet = '?';
/*N*/   }
/*N*/
/*N*/   return aRet;
/*N*/ }

//------------------------------------------------------------------------
//
//                          Feld-Daten
//
//------------------------------------------------------------------------

/*N*/ ScFieldEditEngine::ScFieldEditEngine( SfxItemPool* pEnginePool,
/*N*/           SfxItemPool* pTextObjectPool, BOOL bDeleteEnginePool )
/*N*/       :
/*N*/       ScEditEngineDefaulter( pEnginePool, bDeleteEnginePool ),
/*N*/       bExecuteURL( TRUE )
/*N*/ {
/*N*/   if ( pTextObjectPool )
/*N*/       SetEditTextObjectPool( pTextObjectPool );
/*N*/   //  EE_CNTRL_URLSFXEXECUTE nicht, weil die Edit-Engine den ViewFrame nicht kennt
/*N*/   // wir haben keine StyleSheets fuer Text
/*N*/   SetControlWord( (GetControlWord() | EE_CNTRL_MARKFIELDS) & ~EE_CNTRL_RTFSTYLESHEETS );
/*N*/ }

/*N*/ String __EXPORT ScFieldEditEngine::CalcFieldValue( const SvxFieldItem& rField,
/*N*/                                   USHORT nPara, USHORT nPos,
/*N*/                                   Color*& rTxtColor, Color*& rFldColor )
/*N*/ {
/*N*/   String aRet;
/*N*/   const SvxFieldData* pFieldData = rField.GetField();
/*N*/
/*N*/   if ( pFieldData )
/*N*/   {
/*N*/       TypeId aType = pFieldData->Type();
/*N*/
/*N*/       if (aType == TYPE(SvxURLField))
/*N*/       {
/*N*/           String aURL = ((const SvxURLField*)pFieldData)->GetURL();
/*N*/
/*N*/           switch ( ((const SvxURLField*)pFieldData)->GetFormat() )
/*N*/           {
/*N*/               case SVXURLFORMAT_APPDEFAULT: //!!! einstellbar an App???
/*N*/               case SVXURLFORMAT_REPR:
/*N*/                   aRet = ((const SvxURLField*)pFieldData)->GetRepresentation();
/*N*/                   break;
/*N*/
/*N*/               case SVXURLFORMAT_URL:
/*N*/                   aRet = aURL;
/*N*/                   break;
/*N*/           }
/*N*/
/*N*/             svtools::ColorConfigEntry eEntry =
/*N*/                 INetURLHistory::GetOrCreate()->QueryUrl( aURL ) ? svtools::LINKSVISITED : svtools::LINKS;
/*N*/           rTxtColor = new Color( SC_MOD()->GetColorConfig().GetColorValue(eEntry).nColor );
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           //DBG_ERROR("unbekannter Feldbefehl");
/*N*/           aRet = '?';
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if (!aRet.Len())        // leer ist baeh
/*N*/       aRet = ' ';         // Space ist Default der Editengine
/*N*/
/*N*/   return aRet;
/*N*/ }

//STRIP001 void __EXPORT ScFieldEditEngine::FieldClicked( const SvxFieldItem& rField, USHORT, USHORT )
//STRIP001 {
//STRIP001  const SvxFieldData* pFld = rField.GetField();
//STRIP001
//STRIP001  if ( pFld && pFld->ISA( SvxURLField ) && bExecuteURL )
//STRIP001  {
//STRIP001      const SvxURLField* pURLField = (const SvxURLField*) pFld;
//STRIP001      ScGlobal::OpenURL( pURLField->GetURL(), pURLField->GetTargetFrame() );
//STRIP001  }
//STRIP001 }

