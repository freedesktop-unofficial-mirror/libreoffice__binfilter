/*************************************************************************
 *
 *  $RCSfile: sc_documen8.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 11:05:26 $
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

#ifdef PCH
// auto strip #include "core_pch.hxx"
#endif

#pragma hdrstop

#include "scitems.hxx"
// auto strip #include <bf_svx/eeitem.hxx>
#define ITEMID_FIELD EE_FEATURE_FIELD

// auto strip #include <tools/string.hxx>
// auto strip #include <bf_svx/editobj.hxx>
// auto strip #include <bf_svx/editstat.hxx>
#include <bf_svx/frmdiritem.hxx>
#include <bf_svx/langitem.hxx>
#include <bf_svx/linkmgr.hxx>
// auto strip #include <bf_svx/scripttypeitem.hxx>
// auto strip #include <bf_svx/unolingu.hxx>
// auto strip #include <bf_sfx2/objsh.hxx>
#include <bf_sfx2/printer.hxx>
#include <bf_sfx2/viewfrm.hxx>
#include <bf_sfx2/viewsh.hxx>
#include <svtools/flagitem.hxx>
// auto strip #include <svtools/intitem.hxx>
#define _SVSTDARR_USHORTS
// auto strip #include <svtools/svstdarr.hxx>
// auto strip #include <svtools/zforlist.hxx>
#include <svtools/zformat.hxx>
#include <bf_sfx2/misccfg.hxx>
#include <bf_sfx2/app.hxx>
// auto strip #include <unotools/transliterationwrapper.hxx>
// auto strip #include <svtools/securityoptions.hxx>

// auto strip #include <vcl/msgbox.hxx>

// auto strip #include "global.hxx"
// auto strip #include "table.hxx"
// auto strip #include "column.hxx"
// auto strip #include "cell.hxx"
#include "poolhelp.hxx"
#include "docpool.hxx"
#include "stlpool.hxx"
// auto strip #include "stlsheet.hxx"
#include "docoptio.hxx"
#include "viewopti.hxx"
// auto strip #include "scextopt.hxx"
// auto strip #include "scdebug.hxx"
#include "rechead.hxx"
#include "ddelink.hxx"
#include "scmatrix.hxx"
#include "arealink.hxx"
// auto strip #include "dociter.hxx"
#include "patattr.hxx"
// auto strip #include "hints.hxx"
#include "editutil.hxx"
// auto strip #include "progress.hxx"
#include "document.hxx"
// auto strip #include "chartlis.hxx"
#include "refupdat.hxx"
// auto strip #include "validat.hxx"        // fuer HasMacroCalls
// auto strip #include "markdata.hxx"
#include "scmod.hxx"
#include "globstr.hrc"
#include "bf_sc.hrc"
namespace binfilter {

#define GET_SCALEVALUE(set,id)  ((const SfxUInt16Item&)(set.Get( id ))).GetValue()

//  states for online spelling in the visible range (0 is set initially)
#define VSPL_START  0
#define VSPL_DONE   1


// STATIC DATA -----------------------------------------------------------



//------------------------------------------------------------------------

/*N*/ void ScDocument::ImplLoadDocOptions( SvStream& rStream )
/*N*/ {
/*N*/   USHORT d,m,y;
/*N*/
/*N*/   DBG_ASSERT( pDocOptions, "No DocOptions to load! :-(" );
/*N*/
/*N*/   pDocOptions->Load( rStream );
/*N*/
/*N*/   if ( pDocOptions->GetStdPrecision() > 20 ) //!!! ist 20 als Maximum konstant ???
/*N*/   {
/*?*/       DBG_ERROR( "Document options corrupted. Setting to defaults." );
/*?*/       pDocOptions->ResetDocOptions();
/*N*/   }
/*N*/
/*N*/   pDocOptions->GetDate( d,m,y );
/*N*/   SvNumberFormatter* pFormatter = xPoolHelper->GetFormTable();
/*N*/   pFormatter->ChangeNullDate( d,m,y );
/*N*/   pFormatter->ChangeStandardPrec( pDocOptions->GetStdPrecision() );
/*N*/   pFormatter->SetYear2000( pDocOptions->GetYear2000() );
/*N*/ }

//------------------------------------------------------------------------

/*N*/ void ScDocument::ImplLoadViewOptions( SvStream& rStream )
/*N*/ {
/*N*/   DBG_ASSERT( pViewOptions, "No ViewOptions to load! :-(" );
/*N*/   rStream >> *pViewOptions;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ void ScDocument::ImplSaveDocOptions( SvStream& rStream ) const
/*N*/ {
/*N*/   DBG_ASSERT( pDocOptions, "No DocOptions to save! :-(" );
/*N*/   pDocOptions->Save( rStream );
/*N*/ }

//------------------------------------------------------------------------

/*N*/ void ScDocument::ImplSaveViewOptions( SvStream& rStream ) const
/*N*/ {
/*N*/   DBG_ASSERT( pViewOptions, "No ViewOptions to save! :-(" );
/*N*/   rStream << *pViewOptions;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ void ScDocument::ImplCreateOptions()
/*N*/ {
/*N*/   pDocOptions  = new ScDocOptions();
/*N*/   pViewOptions = new ScViewOptions();
/*N*/ }

//------------------------------------------------------------------------

/*N*/ void ScDocument::ImplDeleteOptions()
/*N*/ {
/*N*/   delete pDocOptions;
/*N*/   delete pViewOptions;
//STRIP001 /*N*/    delete pExtDocOptions;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ SfxPrinter* ScDocument::GetPrinter()
/*N*/ {
/*N*/   if ( !pPrinter )
/*N*/   {
/*N*/       SfxItemSet* pSet =
/*N*/           new SfxItemSet( *xPoolHelper->GetDocPool(),
/*N*/                           SID_PRINTER_NOTFOUND_WARN, SID_PRINTER_NOTFOUND_WARN,
/*N*/                           SID_PRINTER_CHANGESTODOC,  SID_PRINTER_CHANGESTODOC,
/*N*/                           SID_SCPRINTOPTIONS,        SID_SCPRINTOPTIONS,
/*N*/                           NULL );
/*N*/
/*N*/         SfxMiscCfg* pOffCfg = SFX_APP()->GetMiscConfig();
/*N*/       if ( pOffCfg )
/*N*/       {
/*N*/           USHORT nFlags = 0;
/*N*/             if ( pOffCfg->IsPaperOrientationWarning() )
/*N*/               nFlags |= SFX_PRINTER_CHG_ORIENTATION;
/*N*/           if ( pOffCfg->IsPaperSizeWarning() )
/*N*/               nFlags |= SFX_PRINTER_CHG_SIZE;
/*N*/           pSet->Put( SfxFlagItem( SID_PRINTER_CHANGESTODOC, nFlags ) );
/*N*/           pSet->Put( SfxBoolItem( SID_PRINTER_NOTFOUND_WARN, pOffCfg->IsNotFoundWarning() ) );
/*N*/       }
/*N*/
/*N*/       pPrinter = new SfxPrinter( pSet );
/*N*/       UpdateDrawPrinter();
/*N*/       pPrinter->SetDigitLanguage( SC_MOD()->GetOptDigitLanguage() );
/*N*/   }
/*N*/
/*N*/   return pPrinter;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ void ScDocument::SetPrinter( SfxPrinter* pNewPrinter )
/*N*/ {
/*N*/   if ( pNewPrinter == pPrinter )
/*N*/   {
/*N*/       //  #i6706# SetPrinter is called with the same printer again if
/*N*/       //  the JobSetup has changed. In that case just call UpdateDrawPrinter
/*N*/       //  (SetRefDevice for drawing layer) because of changed text sizes.
/*N*/       UpdateDrawPrinter();
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       SfxPrinter* pOld = pPrinter;
/*N*/       pPrinter = pNewPrinter;
/*N*/       UpdateDrawPrinter();
/*N*/       pPrinter->SetDigitLanguage( SC_MOD()->GetOptDigitLanguage() );
/*N*/       delete pOld;
/*N*/   }
/*N*/   InvalidateTextWidth();      // in both cases
/*N*/ }

//------------------------------------------------------------------------

/*N*/ void ScDocument::SetPrintOptions()
/*N*/ {
/*N*/   if ( !pPrinter ) GetPrinter(); // setzt pPrinter
/*N*/   DBG_ASSERT( pPrinter, "Error in printer creation :-/" );
/*N*/
/*N*/   if ( pPrinter )
/*N*/   {
/*N*/         SfxMiscCfg* pOffCfg = SFX_APP()->GetMiscConfig();
/*N*/       if ( pOffCfg )
/*N*/       {
/*N*/           SfxItemSet aOptSet( pPrinter->GetOptions() );
/*N*/
/*N*/           USHORT nFlags = 0;
/*N*/             if ( pOffCfg->IsPaperOrientationWarning() )
/*N*/               nFlags |= SFX_PRINTER_CHG_ORIENTATION;
/*N*/           if ( pOffCfg->IsPaperSizeWarning() )
/*N*/               nFlags |= SFX_PRINTER_CHG_SIZE;
/*N*/           aOptSet.Put( SfxFlagItem( SID_PRINTER_CHANGESTODOC, nFlags ) );
/*N*/           aOptSet.Put( SfxBoolItem( SID_PRINTER_NOTFOUND_WARN, pOffCfg->IsNotFoundWarning() ) );
/*N*/
/*N*/           pPrinter->SetOptions( aOptSet );
/*N*/       }
/*N*/   }
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 void ScDocument::ModifyStyleSheet( SfxStyleSheetBase& rStyleSheet,
//STRIP001                                 const SfxItemSet&  rChanges )
//STRIP001 {
//STRIP001  SfxItemSet& rSet = rStyleSheet.GetItemSet();
//STRIP001
//STRIP001  switch ( rStyleSheet.GetFamily() )
//STRIP001  {
//STRIP001      case SFX_STYLE_FAMILY_PAGE:
//STRIP001          {
//STRIP001              const USHORT nOldScale        = GET_SCALEVALUE(rSet,ATTR_PAGE_SCALE);
//STRIP001              const USHORT nOldScaleToPages = GET_SCALEVALUE(rSet,ATTR_PAGE_SCALETOPAGES);
//STRIP001              rSet.Put( rChanges );
//STRIP001              const USHORT nNewScale        = GET_SCALEVALUE(rSet,ATTR_PAGE_SCALE);
//STRIP001              const USHORT nNewScaleToPages = GET_SCALEVALUE(rSet,ATTR_PAGE_SCALETOPAGES);
//STRIP001
//STRIP001              if ( (nOldScale != nNewScale) || (nOldScaleToPages != nNewScaleToPages) )
//STRIP001                  InvalidateTextWidth( rStyleSheet.GetName() );
//STRIP001          }
//STRIP001          break;
//STRIP001
//STRIP001      case SFX_STYLE_FAMILY_PARA:
//STRIP001          {
//STRIP001              BOOL bNumFormatChanged;
//STRIP001              if ( ScGlobal::CheckWidthInvalidate( bNumFormatChanged,
//STRIP001                      rSet, rChanges ) )
//STRIP001                  InvalidateTextWidth( NULL, NULL, bNumFormatChanged );
//STRIP001              ULONG nOldFormat =
//STRIP001                  ((const SfxUInt32Item*)&rSet.Get(
//STRIP001                  ATTR_VALUE_FORMAT ))->GetValue();
//STRIP001              ULONG nNewFormat =
//STRIP001                  ((const SfxUInt32Item*)&rChanges.Get(
//STRIP001                  ATTR_VALUE_FORMAT ))->GetValue();
//STRIP001              LanguageType eNewLang, eOldLang;
//STRIP001              eNewLang = eOldLang = LANGUAGE_DONTKNOW;
//STRIP001              if ( nNewFormat != nOldFormat )
//STRIP001              {
//STRIP001                  SvNumberFormatter* pFormatter = GetFormatTable();
//STRIP001                  eOldLang = pFormatter->GetEntry( nOldFormat )->GetLanguage();
//STRIP001                  eNewLang = pFormatter->GetEntry( nNewFormat )->GetLanguage();
//STRIP001              }
//STRIP001
//STRIP001              // Bedeutung der Items in rChanges:
//STRIP001              //  Item gesetzt    - Aenderung uebernehmen
//STRIP001              //  Dontcare        - Default setzen
//STRIP001              //  Default         - keine Aenderung
//STRIP001              // ("keine Aenderung" geht nicht mit PutExtended, darum Schleife)
//STRIP001              for (USHORT nWhich = ATTR_PATTERN_START; nWhich <= ATTR_PATTERN_END; nWhich++)
//STRIP001              {
//STRIP001                  const SfxPoolItem* pItem;
//STRIP001                  SfxItemState eState = rChanges.GetItemState( nWhich, FALSE, &pItem );
//STRIP001                  if ( eState == SFX_ITEM_SET )
//STRIP001                      rSet.Put( *pItem );
//STRIP001                  else if ( eState == SFX_ITEM_DONTCARE )
//STRIP001                      rSet.ClearItem( nWhich );
//STRIP001                  // bei Default nichts
//STRIP001              }
//STRIP001
//STRIP001              if ( eNewLang != eOldLang )
//STRIP001                  rSet.Put(
//STRIP001                      SvxLanguageItem( eNewLang, ATTR_LANGUAGE_FORMAT ) );
//STRIP001          }
//STRIP001          break;
//STRIP001  }
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 void ScDocument::CopyStdStylesFrom( ScDocument* pSrcDoc )
//STRIP001 {
//STRIP001  xPoolHelper->GetStylePool()->CopyStdStylesFrom( pSrcDoc->xPoolHelper->GetStylePool() );
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 void ScDocument::InvalidateTextWidth( const String& rStyleName )
//STRIP001 {
//STRIP001  const USHORT nCount = GetTableCount();
//STRIP001  for ( USHORT i=0; i<nCount && pTab[i]; i++ )
//STRIP001      if ( pTab[i]->GetPageStyle() == rStyleName )
//STRIP001          InvalidateTextWidth( i );
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 void ScDocument::InvalidateTextWidth( USHORT nTab )
//STRIP001 {
//STRIP001  ScAddress aAdrFrom( 0,    0,        nTab );
//STRIP001  ScAddress aAdrTo  ( MAXCOL, MAXROW, nTab );
//STRIP001  InvalidateTextWidth( &aAdrFrom, &aAdrTo );
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 BOOL ScDocument::IsPageStyleInUse( const String& rStrPageStyle, USHORT* pInTab )
//STRIP001 {
//STRIP001  BOOL         bInUse = FALSE;
//STRIP001  const USHORT nCount = GetTableCount();
//STRIP001
//STRIP001  for ( USHORT i=0; !bInUse && i<nCount && pTab[i]; i++ )
//STRIP001      bInUse = ( pTab[i]->GetPageStyle() == rStrPageStyle );
//STRIP001
//STRIP001  if ( pInTab )
//STRIP001      *pInTab = i-1;
//STRIP001
//STRIP001  return bInUse;
//STRIP001 }

//------------------------------------------------------------------------

/*N*/ BOOL ScDocument::RemovePageStyleInUse( const String& rStyle )
/*N*/ {
/*N*/   BOOL bWasInUse = FALSE;
/*N*/   const USHORT nCount = GetTableCount();
/*N*/
/*N*/   for ( USHORT i=0; i<nCount && pTab[i]; i++ )
/*N*/       if ( pTab[i]->GetPageStyle() == rStyle )
/*N*/       {
/*N*/           bWasInUse = TRUE;
/*N*/           pTab[i]->SetPageStyle( ScGlobal::GetRscString(STR_STYLENAME_STANDARD) );
/*N*/       }
/*N*/
/*N*/   return bWasInUse;
/*N*/ }

//STRIP001 BOOL ScDocument::RenamePageStyleInUse( const String& rOld, const String& rNew )
//STRIP001 {
//STRIP001  BOOL bWasInUse = FALSE;
//STRIP001  const USHORT nCount = GetTableCount();
//STRIP001
//STRIP001  for ( USHORT i=0; i<nCount && pTab[i]; i++ )
//STRIP001      if ( pTab[i]->GetPageStyle() == rOld )
//STRIP001      {
//STRIP001          bWasInUse = TRUE;
//STRIP001          pTab[i]->SetPageStyle( rNew );
//STRIP001      }
//STRIP001
//STRIP001  return bWasInUse;
//STRIP001 }

//------------------------------------------------------------------------

/*M*/ BYTE ScDocument::GetEditTextDirection(USHORT nTab) const
/*M*/ {
/*M*/   EEHorizontalTextDirection eRet = EE_HTEXTDIR_DEFAULT;
/*M*/
/*M*/   String aStyleName = GetPageStyle( nTab );
/*M*/   SfxStyleSheetBase* pStyle = xPoolHelper->GetStylePool()->Find( aStyleName, SFX_STYLE_FAMILY_PAGE );
/*M*/   if ( pStyle )
/*M*/   {
/*M*/       SfxItemSet& rStyleSet = pStyle->GetItemSet();
/*M*/       SvxFrameDirection eDirection = (SvxFrameDirection)
/*M*/           ((const SvxFrameDirectionItem&)rStyleSet.Get( ATTR_WRITINGDIR )).GetValue();
/*M*/
/*M*/       if ( eDirection == FRMDIR_HORI_LEFT_TOP )
/*M*/           eRet = EE_HTEXTDIR_L2R;
/*M*/       else if ( eDirection == FRMDIR_HORI_RIGHT_TOP )
/*M*/           eRet = EE_HTEXTDIR_R2L;
/*M*/       // else (invalid for EditEngine): keep "default"
/*M*/   }
/*M*/
/*M*/   return eRet;
/*M*/ }

//------------------------------------------------------------------------

/*N*/ void ScDocument::InvalidateTextWidth( const ScAddress* pAdrFrom,
/*N*/                                     const ScAddress* pAdrTo,
/*N*/                                     BOOL bBroadcast )
/*N*/ {
/*N*/   bBroadcast = (bBroadcast && GetDocOptions().IsCalcAsShown() && !IsImportingXML());
/*N*/   if ( pAdrFrom && !pAdrTo )
/*N*/   {
/*?*/       const USHORT nTab = pAdrFrom->Tab();
/*?*/
/*?*/       if ( pTab[nTab] )
/*?*/           pTab[nTab]->InvalidateTextWidth( pAdrFrom, NULL, bBroadcast );
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       const USHORT nTabStart = pAdrFrom ? pAdrFrom->Tab() : 0;
/*N*/       const USHORT nTabEnd   = pAdrTo   ? pAdrTo->Tab()   : MAXTAB;
/*N*/
/*N*/       for ( USHORT nTab=nTabStart; nTab<=nTabEnd; nTab++ )
/*N*/           if ( pTab[nTab] )
/*N*/               pTab[nTab]->InvalidateTextWidth( pAdrFrom, pAdrTo, bBroadcast );
/*N*/   }
/*N*/ }

//------------------------------------------------------------------------

#define CALCMAX                 1000    // Berechnungen
#define ABORT_EVENTS            (INPUT_ANY & ~INPUT_TIMER & ~INPUT_OTHER)

/*N*/ BOOL ScDocument::IdleCalcTextWidth()          // TRUE = demnaechst wieder versuchen
{
DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001  if ( bIdleDisabled || IsInLinkUpdate() )
//STRIP001      return FALSE;
//STRIP001  bIdleDisabled = TRUE;
//STRIP001
//STRIP001 // ULONG nMs = 0;
//STRIP001 // USHORT nIter = 0;
//STRIP001
//STRIP001  const ULONG         nStart   = GetSysTicks();
//STRIP001  double              nPPTX    = 0.0;
//STRIP001  double              nPPTY    = 0.0;
//STRIP001  OutputDevice*       pDev     = NULL;
//STRIP001  MapMode             aOldMap;
//STRIP001  ScStyleSheet*       pStyle   = NULL;
//STRIP001  ScColumnIterator*   pColIter = NULL;
//STRIP001  ScTable*            pTable   = NULL;
//STRIP001  ScColumn*           pColumn  = NULL;
//STRIP001  ScBaseCell*         pCell    = NULL;
//STRIP001  USHORT              nTab     = aCurTextWidthCalcPos.Tab();
//STRIP001  USHORT              nRow     = aCurTextWidthCalcPos.Row();
//STRIP001  short               nCol     = aCurTextWidthCalcPos.Col();
//STRIP001  USHORT              nRestart = 0;
//STRIP001  USHORT              nZoom    = 0;
//STRIP001  BOOL                bNeedMore= FALSE;
//STRIP001
//STRIP001  if ( nRow > MAXROW )
//STRIP001      nRow = 0, nCol--;
//STRIP001  if ( nCol < 0 )
//STRIP001      nCol = MAXCOL, nTab++;
//STRIP001  if ( nTab > MAXTAB || !pTab[nTab] )
//STRIP001      nTab = 0;
//STRIP001
//STRIP001 //   DBG_ERROR( String("Start = ") + String(nTab) + String(',') + String(nCol) + String(',') + String(nRow)  );
//STRIP001
//STRIP001  //  SearchMask/Family muss gemerkt werden,
//STRIP001  //  damit z.B. der Organizer nicht durcheinanderkommt, wenn zwischendurch eine
//STRIP001  //  Query-Box aufgemacht wird !!!
//STRIP001
//STRIP001  ScStyleSheetPool* pStylePool = xPoolHelper->GetStylePool();
//STRIP001  USHORT nOldMask = pStylePool->GetSearchMask();
//STRIP001  SfxStyleFamily eOldFam = pStylePool->GetSearchFamily();
//STRIP001
//STRIP001  pTable = pTab[nTab];
//STRIP001  pStylePool->SetSearchMask( SFX_STYLE_FAMILY_PAGE, SFXSTYLEBIT_ALL );
//STRIP001  pStyle = (ScStyleSheet*)pStylePool->Find( pTable->aPageStyle,
//STRIP001                                            SFX_STYLE_FAMILY_PAGE );
//STRIP001
//STRIP001  if ( !pStyle )
//STRIP001      DBG_ERROR( "Missing StyleSheet :-/" );
//STRIP001
//STRIP001
//STRIP001  BOOL bProgress = FALSE;
//STRIP001  if ( pStyle && 0 == GET_SCALEVALUE(pStyle->GetItemSet(),ATTR_PAGE_SCALETOPAGES) )
//STRIP001  {
//STRIP001      USHORT nCount = 0;
//STRIP001
//STRIP001      nZoom    = GET_SCALEVALUE(pStyle->GetItemSet(),ATTR_PAGE_SCALE);
//STRIP001      Fraction aZoomFract( nZoom, 100 );
//STRIP001      pColumn  = &pTable->aCol[nCol];
//STRIP001      pColIter = new ScColumnIterator( pColumn, nRow, MAXROW );
//STRIP001
//STRIP001      while ( (nZoom > 0) && (nCount < CALCMAX) && (nRestart < 2) )
//STRIP001      {
//STRIP001          if ( pColIter->Next( nRow, pCell ) )
//STRIP001          {
//STRIP001              if ( TEXTWIDTH_DIRTY == pCell->GetTextWidth() )
//STRIP001              {
//STRIP001                  if ( !pDev )
//STRIP001                  {
//STRIP001                      pDev = GetPrinter();
//STRIP001                      aOldMap = pDev->GetMapMode();
//STRIP001                      pDev->SetMapMode( MAP_PIXEL );  // wichtig fuer GetNeededSize
//STRIP001
//STRIP001                      Point aPix1000 = pDev->LogicToPixel( Point(1000,1000), MAP_TWIP );
//STRIP001                      nPPTX = aPix1000.X() / 1000.0;
//STRIP001                      nPPTY = aPix1000.Y() / 1000.0;
//STRIP001                  }
//STRIP001                  if ( !bProgress && pCell->GetCellType() == CELLTYPE_FORMULA
//STRIP001                    && ((ScFormulaCell*)pCell)->GetDirty() )
//STRIP001                  {
//STRIP001                      ScProgress::CreateInterpretProgress( this, FALSE );
//STRIP001                      bProgress = TRUE;
//STRIP001                  }
//STRIP001
//STRIP001 //                   DBG_ERROR( String("t,c,r = ") + String(nTab) + String(',') + String(nCol) + String(',') + String(nRow)  );
//STRIP001 //                   DBG_ERROR( String("nOldWidth = ") + String(pCell->GetTextWidth()) );
//STRIP001
//STRIP001                  USHORT nNewWidth = (USHORT)GetNeededSize( nCol, nRow, nTab,
//STRIP001                                                            pDev, nPPTX, nPPTY,
//STRIP001                                                            aZoomFract,aZoomFract, TRUE,
//STRIP001                                                            TRUE );   // bTotalSize
//STRIP001
//STRIP001 //                   DBG_ERROR( String("nNewWidth = ") + String(nNewWidth) );
//STRIP001
//STRIP001                  pCell->SetTextWidth( nNewWidth );
//STRIP001
//STRIP001                  bNeedMore = TRUE;
//STRIP001              }
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              BOOL bNewTab = FALSE;
//STRIP001
//STRIP001              nRow = 0;
//STRIP001              nCol--;
//STRIP001
//STRIP001              if ( nCol < 0 )
//STRIP001              {
//STRIP001                  nCol = MAXCOL;
//STRIP001                  nTab++;
//STRIP001                  bNewTab = TRUE;
//STRIP001              }
//STRIP001
//STRIP001              if ( nTab > MAXTAB || !pTab[nTab] )
//STRIP001              {
//STRIP001                  nTab = 0;
//STRIP001                  nRestart++;
//STRIP001                  bNewTab = TRUE;
//STRIP001              }
//STRIP001
//STRIP001              if ( nRestart < 2 )
//STRIP001              {
//STRIP001                  if ( bNewTab )
//STRIP001                  {
//STRIP001                      pTable = pTab[nTab];
//STRIP001                      pStyle = (ScStyleSheet*)pStylePool->Find( pTable->aPageStyle,
//STRIP001                                                                SFX_STYLE_FAMILY_PAGE );
//STRIP001
//STRIP001                      if ( pStyle )
//STRIP001                      {
//STRIP001                          SfxItemSet& rSet = pStyle->GetItemSet();
//STRIP001                          if ( GET_SCALEVALUE( rSet, ATTR_PAGE_SCALETOPAGES ) == 0 )
//STRIP001                              nZoom = GET_SCALEVALUE(rSet, ATTR_PAGE_SCALE );
//STRIP001                          else
//STRIP001                              nZoom = 0;
//STRIP001                      }
//STRIP001                      else
//STRIP001                          DBG_ERROR( "Missing StyleSheet :-/" );
//STRIP001                  }
//STRIP001
//STRIP001                  if ( nZoom > 0 )
//STRIP001                  {
//STRIP001                      delete pColIter;
//STRIP001
//STRIP001                      pColumn  = &pTable->aCol[nCol];
//STRIP001                      pColIter = new ScColumnIterator( pColumn, nRow, MAXROW );
//STRIP001                  }
//STRIP001                  else
//STRIP001                      nTab++; // Tabelle nicht mit absolutem Zoom -> naechste
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001 // nIter = nCount;
//STRIP001
//STRIP001          nCount++;
//STRIP001
//STRIP001          // Idle Berechnung abbrechen, wenn Berechnungen laenger als
//STRIP001          // 50ms dauern, oder nach 32 Berechnungen mal nachschauen, ob
//STRIP001          // bestimmte Events anstehen, die Beachtung wuenschen:
//STRIP001
//STRIP001 // nMs = SysTicksToMs( GetSysTicks() - nStart );
//STRIP001
//STRIP001          if (   ( 50L < SysTicksToMs( GetSysTicks() - nStart ) )
//STRIP001              || ( !(nCount&31) && Application::AnyInput( ABORT_EVENTS ) ) )
//STRIP001              nCount = CALCMAX;
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001      nTab++; // Tabelle nicht mit absolutem Zoom -> naechste
//STRIP001
//STRIP001  if ( bProgress )
//STRIP001      ScProgress::DeleteInterpretProgress();
//STRIP001
//STRIP001  delete pColIter;
//STRIP001
//STRIP001 //   DBG_ERROR( String(nCount) + String(" End = ") + String(nTab) + String(',') + String(nCol) + String(',') + String(nRow)  );
//STRIP001
//STRIP001  if (pDev)
//STRIP001      pDev->SetMapMode(aOldMap);
//STRIP001
//STRIP001  aCurTextWidthCalcPos.SetTab( nTab );
//STRIP001  aCurTextWidthCalcPos.SetRow( nRow );
//STRIP001  aCurTextWidthCalcPos.SetCol( (USHORT)nCol );
//STRIP001
//STRIP001 // DBG_ERROR( String(nMs) + String(" ms (") + String(nIter) + String(')') );
//STRIP001
//STRIP001  pStylePool->SetSearchMask( eOldFam, nOldMask );
//STRIP001  bIdleDisabled = FALSE;
//STRIP001
//STRIP001  return bNeedMore;
}

//------------------------------------------------------------------------

//STRIP001 class ScSpellStatus
//STRIP001 {
//STRIP001 public:
//STRIP001  BOOL    bModified;
//STRIP001
//STRIP001  ScSpellStatus() : bModified(FALSE) {};
//STRIP001
//STRIP001  DECL_LINK (EventHdl, EditStatus*);
//STRIP001 };
//STRIP001
//STRIP001 IMPL_LINK( ScSpellStatus, EventHdl, EditStatus *, pStatus )
//STRIP001 {
//STRIP001  ULONG nStatus = pStatus->GetStatusWord();
//STRIP001  if ( nStatus & EE_STAT_WRONGWORDCHANGED )
//STRIP001      bModified = TRUE;
//STRIP001
//STRIP001  return 0;
//STRIP001 }

//  SPELL_MAXCELLS muss mindestens 256 sein, solange am Iterator keine
//  Start-Spalte gesetzt werden kann

//! SPELL_MAXTEST fuer Timer und Idle unterschiedlich ???

//  SPELL_MAXTEST now divided between visible and rest of document

#define SPELL_MAXTEST_VIS   1
#define SPELL_MAXTEST_ALL   3
#define SPELL_MAXCELLS      256

//STRIP001 BOOL ScDocument::OnlineSpellInRange( const ScRange& rSpellRange, ScAddress& rSpellPos,
//STRIP001                                   USHORT nMaxTest )
//STRIP001 {
//STRIP001  ScEditEngineDefaulter* pEngine = NULL;              //! am Dokument speichern
//STRIP001  SfxItemSet* pDefaults = NULL;
//STRIP001  ScSpellStatus aStatus;
//STRIP001
//STRIP001  USHORT nCellCount = 0;          // Zellen insgesamt
//STRIP001  USHORT nTestCount = 0;          // Aufrufe Spelling
//STRIP001  BOOL bChanged = FALSE;          // Aenderungen?
//STRIP001
//STRIP001  USHORT nCol = rSpellRange.aStart.Col();     // iterator always starts on the left edge
//STRIP001  USHORT nRow = rSpellPos.Row();
//STRIP001  USHORT nTab = rSpellPos.Tab();
//STRIP001  if ( !pTab[nTab] )                          // sheet deleted?
//STRIP001  {
//STRIP001      nTab = rSpellRange.aStart.Tab();
//STRIP001      nRow = rSpellRange.aStart.Row();
//STRIP001      if ( !pTab[nTab] )
//STRIP001      {
//STRIP001          //  may happen for visible range
//STRIP001          return FALSE;
//STRIP001      }
//STRIP001  }
//STRIP001  ScHorizontalCellIterator aIter( this, nTab,
//STRIP001                                  rSpellRange.aStart.Col(), nRow,
//STRIP001                                  rSpellRange.aEnd.Col(), rSpellRange.aEnd.Row() );
//STRIP001  ScBaseCell* pCell = aIter.GetNext( nCol, nRow );
//STRIP001  //  skip everything left of rSpellPos:
//STRIP001  while ( pCell && nRow == rSpellPos.Row() && nCol < rSpellPos.Col() )
//STRIP001      pCell = aIter.GetNext( nCol, nRow );
//STRIP001  while ( pCell )
//STRIP001  {
//STRIP001      CellType eType = pCell->GetCellType();
//STRIP001      if ( eType == CELLTYPE_STRING || eType == CELLTYPE_EDIT )
//STRIP001      {
//STRIP001          if (!pEngine)
//STRIP001          {
//STRIP001              //  #71154# ScTabEditEngine is needed
//STRIP001              //  because MapMode must be set for some old documents
//STRIP001              pEngine = new ScTabEditEngine( this );
//STRIP001              pEngine->SetControlWord( pEngine->GetControlWord() |
//STRIP001                          ( EE_CNTRL_ONLINESPELLING | EE_CNTRL_ALLOWBIGOBJS ) );
//STRIP001              pEngine->SetStatusEventHdl( LINK( &aStatus, ScSpellStatus, EventHdl ) );
//STRIP001              //  Delimiters hier wie in inputhdl.cxx !!!
//STRIP001              pEngine->SetWordDelimiters(
//STRIP001                          ScEditUtil::ModifyDelimiters( pEngine->GetWordDelimiters() ) );
//STRIP001              pDefaults = new SfxItemSet( pEngine->GetEmptyItemSet() );
//STRIP001
//STRIP001                 ::com::sun::star::uno::Reference< ::com::sun::star::linguistic2::XSpellChecker1> xXSpellChecker1( LinguMgr::GetSpellChecker() );
//STRIP001
//STRIP001              pEngine->SetSpeller( xXSpellChecker1 );
//STRIP001          }
//STRIP001
//STRIP001          const ScPatternAttr* pPattern = GetPattern( nCol, nRow, nTab );
//STRIP001          pPattern->FillEditItemSet( pDefaults );
//STRIP001          pEngine->SetDefaults( pDefaults, FALSE );               //! noetig ?
//STRIP001
//STRIP001          USHORT nCellLang = ((const SvxLanguageItem&)
//STRIP001                                  pPattern->GetItem(ATTR_FONT_LANGUAGE)).GetValue();
//STRIP001          if ( nCellLang == LANGUAGE_SYSTEM )
//STRIP001                 nCellLang = Application::GetSettings().GetLanguage();   // never use SYSTEM for spelling
//STRIP001          pEngine->SetDefaultLanguage( nCellLang );
//STRIP001
//STRIP001          if ( eType == CELLTYPE_STRING )
//STRIP001          {
//STRIP001              String aText;
//STRIP001              ((ScStringCell*)pCell)->GetString(aText);
//STRIP001              pEngine->SetText( aText );
//STRIP001          }
//STRIP001          else
//STRIP001              pEngine->SetText( *((ScEditCell*)pCell)->GetData() );
//STRIP001
//STRIP001          aStatus.bModified = FALSE;
//STRIP001          pEngine->CompleteOnlineSpelling();
//STRIP001          if ( aStatus.bModified )                // Fehler dazu oder weggekommen?
//STRIP001          {
//STRIP001              BOOL bNeedEdit = TRUE;                      //  Test auf einfachen Text
//STRIP001              if ( !pEngine->HasOnlineSpellErrors() )
//STRIP001              {
//STRIP001                  ScEditAttrTester aTester( pEngine );
//STRIP001                  bNeedEdit = aTester.NeedsObject();
//STRIP001              }
//STRIP001
//STRIP001              if ( bNeedEdit )
//STRIP001              {
//STRIP001                  EditTextObject* pNewData = pEngine->CreateTextObject();
//STRIP001                  if ( eType == CELLTYPE_EDIT )
//STRIP001                      ((ScEditCell*)pCell)->SetData( pNewData,
//STRIP001                          pEngine->GetEditTextObjectPool() );
//STRIP001                  else
//STRIP001                      PutCell( nCol, nRow, nTab, new ScEditCell( pNewData,
//STRIP001                          this, pEngine->GetEditTextObjectPool() ) );
//STRIP001                  delete pNewData;
//STRIP001              }
//STRIP001              else                    // einfacher String
//STRIP001                  PutCell( nCol, nRow, nTab, new ScStringCell( pEngine->GetText() ) );
//STRIP001
//STRIP001              //  Paint
//STRIP001              if (pShell)
//STRIP001              {
//STRIP001                  //  #47751# Seitenvorschau ist davon nicht betroffen
//STRIP001                  //  (sollte jedenfalls nicht)
//STRIP001                  ScPaintHint aHint( ScRange( nCol, nRow, nTab ), PAINT_GRID );
//STRIP001                  aHint.SetPrintFlag( FALSE );
//STRIP001                  pShell->Broadcast( aHint );
//STRIP001              }
//STRIP001
//STRIP001              bChanged = TRUE;
//STRIP001          }
//STRIP001
//STRIP001          if ( ++nTestCount >= nMaxTest )             // checked enough text?
//STRIP001              break;
//STRIP001      }
//STRIP001
//STRIP001      if ( ++nCellCount >= SPELL_MAXCELLS )           // seen enough cells?
//STRIP001          break;
//STRIP001
//STRIP001      pCell = aIter.GetNext( nCol, nRow );
//STRIP001  }
//STRIP001
//STRIP001  if ( pCell )
//STRIP001  {
//STRIP001      ++nCol;                                         // continue after last cell
//STRIP001      if ( nCol > rSpellRange.aEnd.Col() )
//STRIP001      {
//STRIP001          nCol = rSpellRange.aStart.Col();
//STRIP001          ++nRow;
//STRIP001          if ( nRow > rSpellRange.aEnd.Row() )
//STRIP001              pCell = NULL;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if (!pCell)         // end of range reached -> next sheet
//STRIP001  {
//STRIP001      ++nTab;
//STRIP001      if ( nTab > rSpellRange.aEnd.Tab() || !pTab[nTab] )
//STRIP001          nTab = rSpellRange.aStart.Tab();
//STRIP001      nCol = rSpellRange.aStart.Col();
//STRIP001      nRow = rSpellRange.aStart.Row();
//STRIP001
//STRIP001      nVisSpellState = VSPL_DONE;     //! only if this is for the visible range
//STRIP001  }
//STRIP001  rSpellPos.Set( nCol, nRow, nTab );
//STRIP001
//STRIP001  delete pDefaults;
//STRIP001  delete pEngine;         // bevor aStatus out of scope geht
//STRIP001
//STRIP001  return bChanged;
//STRIP001 }


/*N*/ BOOL ScDocument::ContinueOnlineSpelling()
/*N*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); //STRIP001 if ( bIdleDisabled || !pDocOptions->IsAutoSpell() || (pShell && pShell->IsReadOnly()) )
/*?*/       return FALSE;
//STRIP001
//STRIP001  //! use one EditEngine for both calls
//STRIP001
//STRIP001  //  #41504# first check visible range
//STRIP001  BOOL bResult = OnlineSpellInRange( aVisSpellRange, aVisSpellPos, SPELL_MAXTEST_VIS );
//STRIP001
//STRIP001  //  during first pass through visible range, always continue
//STRIP001  if ( nVisSpellState == VSPL_START )
//STRIP001      bResult = TRUE;
//STRIP001
//STRIP001  if (bResult)
//STRIP001  {
//STRIP001      //  if errors found, continue there
//STRIP001      OnlineSpellInRange( aVisSpellRange, aVisSpellPos, SPELL_MAXTEST_ALL );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      //  if nothing found there, continue with rest of document
//STRIP001      ScRange aTotalRange( 0,0,0, MAXCOL,MAXROW,MAXTAB );
//STRIP001      bResult = OnlineSpellInRange( aTotalRange, aOnlineSpellPos, SPELL_MAXTEST_ALL );
//STRIP001  }
//STRIP001  return bResult;
/*N*/ }


//STRIP001 void ScDocument::SetOnlineSpellPos( const ScAddress& rPos )
//STRIP001 {
//STRIP001  aOnlineSpellPos = rPos;
//STRIP001
//STRIP001  //  skip visible area for aOnlineSpellPos
//STRIP001  if ( aVisSpellRange.In( aOnlineSpellPos ) )
//STRIP001      aOnlineSpellPos = aVisSpellRange.aEnd;
//STRIP001 }

/*N*/ BOOL ScDocument::SetVisibleSpellRange( const ScRange& rNewRange )
/*N*/ {
/*N*/   BOOL bChange = ( aVisSpellRange != rNewRange );
/*N*/   if (bChange)
/*N*/   {
/*N*/       //  continue spelling through visible range when scrolling down
/*N*/       BOOL bContDown = ( nVisSpellState == VSPL_START && rNewRange.In( aVisSpellPos ) &&
/*N*/                           rNewRange.aStart.Row() >  aVisSpellRange.aStart.Row() &&
/*N*/                           rNewRange.aStart.Col() == aVisSpellRange.aStart.Col() &&
/*N*/                           rNewRange.aEnd.Col()   == aVisSpellRange.aEnd.Col() );
/*N*/
/*N*/       aVisSpellRange = rNewRange;
/*N*/
/*N*/       if ( !bContDown )
/*N*/       {
/*N*/           aVisSpellPos = aVisSpellRange.aStart;
/*N*/           nVisSpellState = VSPL_START;
/*N*/       }
/*N*/
/*N*/       //  skip visible area for aOnlineSpellPos
/*N*/       if ( aVisSpellRange.In( aOnlineSpellPos ) )
/*N*/           aOnlineSpellPos = aVisSpellRange.aEnd;
/*N*/   }
/*N*/   return bChange;
/*N*/ }

//STRIP001 void ScDocument::RemoveAutoSpellObj()
//STRIP001 {
//STRIP001  //  alle Spelling-Informationen entfernen
//STRIP001
//STRIP001  for (USHORT nTab=0; nTab<=MAXTAB && pTab[nTab]; nTab++)
//STRIP001      pTab[nTab]->RemoveAutoSpellObj();
//STRIP001 }

//------------------------------------------------------------------------

BOOL ScDocument::IdleCheckLinks()           // TRUE = demnaechst wieder versuchen
{
DBG_BF_ASSERT(0, "STRIP"); return FALSE; //STRIP001     BOOL bAnyLeft = FALSE;
//STRIP001
//STRIP001     if (pLinkManager)
//STRIP001     {
//STRIP001         const ::so3::SvBaseLinks& rLinks = pLinkManager->GetLinks();
//STRIP001         USHORT nCount = rLinks.Count();
//STRIP001         for (USHORT i=0; i<nCount; i++)
//STRIP001         {
//STRIP001             ::so3::SvBaseLink* pBase = *rLinks[i];
//STRIP001             if (pBase->ISA(ScDdeLink))
//STRIP001             {
//STRIP001                 ScDdeLink* pDdeLink = (ScDdeLink*)pBase;
//STRIP001                 if (pDdeLink->NeedsUpdate())
//STRIP001                 {
//STRIP001                     pDdeLink->TryUpdate();
//STRIP001                     if (pDdeLink->NeedsUpdate())        // war nix?
//STRIP001                         bAnyLeft = TRUE;
//STRIP001                 }
//STRIP001             }
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001  return bAnyLeft;
}

/*N*/ void ScDocument::SaveDdeLinks(SvStream& rStream) const
/*N*/ {
/*N*/   //  bei 4.0-Export alle mit Modus != DEFAULT weglassen
/*N*/   BOOL bExport40 = ( rStream.GetVersion() <= SOFFICE_FILEFORMAT_40 );
/*N*/
/*N*/   const ::so3::SvBaseLinks& rLinks = pLinkManager->GetLinks();
/*N*/   USHORT nCount = rLinks.Count();
/*N*/
/*N*/   //  erstmal zaehlen...
/*N*/
/*N*/   USHORT nDdeCount = 0;
/*N*/   USHORT i;
/*N*/   for (i=0; i<nCount; i++)
/*N*/   {
/*N*/       ::so3::SvBaseLink* pBase = *rLinks[i];
/*N*/       if (pBase->ISA(ScDdeLink))
/*?*/           if ( !bExport40 || ((ScDdeLink*)pBase)->GetMode() == SC_DDE_DEFAULT )
/*?*/               ++nDdeCount;
/*N*/   }
/*N*/
/*N*/   //  Header
/*N*/
/*N*/   ScMultipleWriteHeader aHdr( rStream );
/*N*/   rStream << nDdeCount;
/*N*/
/*N*/   //  Links speichern
/*N*/
/*N*/   for (i=0; i<nCount; i++)
/*N*/   {
/*N*/       ::so3::SvBaseLink* pBase = *rLinks[i];
/*N*/       if (pBase->ISA(ScDdeLink))
/*N*/       {
/*?*/           ScDdeLink* pLink = (ScDdeLink*)pBase;
/*?*/           if ( !bExport40 || pLink->GetMode() == SC_DDE_DEFAULT )
/*?*/               pLink->Store( rStream, aHdr );
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ void ScDocument::LoadDdeLinks(SvStream& rStream)
/*N*/ {
/*N*/   ScMultipleReadHeader aHdr( rStream );
/*N*/
/*N*/   USHORT nCount;
/*N*/   rStream >> nCount;
/*N*/   for (USHORT i=0; i<nCount; i++)
/*N*/   {
/*?*/       ScDdeLink* pLink = new ScDdeLink( this, rStream, aHdr );
/*?*/       pLinkManager->InsertDDELink( pLink,
/*?*/                           pLink->GetAppl(), pLink->GetTopic(), pLink->GetItem() );
/*N*/   }
/*N*/ }

/*N*/ BOOL ScDocument::HasDdeLinks() const
/*N*/ {
/*N*/   if (pLinkManager)           // Clipboard z.B. hat keinen LinkManager
/*N*/   {
/*N*/       const ::so3::SvBaseLinks& rLinks = pLinkManager->GetLinks();
/*N*/       USHORT nCount = rLinks.Count();
/*N*/       for (USHORT i=0; i<nCount; i++)
/*?*/           if ((*rLinks[i])->ISA(ScDdeLink))
/*?*/               return TRUE;
/*N*/   }
/*N*/
/*N*/   return FALSE;
/*N*/ }

/*N*/ void ScDocument::SetInLinkUpdate(BOOL bSet)
/*N*/ {
/*N*/   //  called from TableLink and AreaLink
/*N*/
/*N*/   DBG_ASSERT( bInLinkUpdate != bSet, "SetInLinkUpdate twice" );
/*N*/   bInLinkUpdate = bSet;
/*N*/ }

//STRIP001 BOOL ScDocument::IsInLinkUpdate() const
//STRIP001 {
//STRIP001     return bInLinkUpdate || IsInDdeLinkUpdate();
//STRIP001 }

/*N*/ void ScDocument::UpdateDdeLinks()
/*N*/ {
/*?*/     DBG_BF_ASSERT(0, "STRIP"); //STRIP001 if (pLinkManager)
//STRIP001     {
//STRIP001         const ::so3::SvBaseLinks& rLinks = pLinkManager->GetLinks();
//STRIP001         USHORT nCount = rLinks.Count();
//STRIP001         USHORT i;
//STRIP001
//STRIP001         //  #49226# falls das Updaten laenger dauert, erstmal alle Werte
//STRIP001         //  zuruecksetzen, damit nichts altes (falsches) stehen bleibt
//STRIP001         BOOL bAny = FALSE;
//STRIP001         for (i=0; i<nCount; i++)
//STRIP001         {
//STRIP001             ::so3::SvBaseLink* pBase = *rLinks[i];
//STRIP001             if (pBase->ISA(ScDdeLink))
//STRIP001             {
//STRIP001                 ((ScDdeLink*)pBase)->ResetValue();
//STRIP001                 bAny = TRUE;
//STRIP001             }
//STRIP001         }
//STRIP001         if (bAny)
//STRIP001         {
//STRIP001             //  Formeln berechnen und painten wie im TrackTimeHdl
//STRIP001             TrackFormulas();
//STRIP001             pShell->Broadcast( SfxSimpleHint( FID_DATACHANGED ) );
//STRIP001             ResetChanged( ScRange(0,0,0,MAXCOL,MAXROW,MAXTAB) );
//STRIP001
//STRIP001             //  wenn FID_DATACHANGED irgendwann mal asynchron werden sollte
//STRIP001             //  (z.B. mit Invalidate am Window), muss hier ein Update erzwungen werden.
//STRIP001         }
//STRIP001
//STRIP001         //  nun wirklich updaten...
//STRIP001         for (i=0; i<nCount; i++)
//STRIP001         {
//STRIP001             ::so3::SvBaseLink* pBase = *rLinks[i];
//STRIP001             if (pBase->ISA(ScDdeLink))
//STRIP001                 ((ScDdeLink*)pBase)->TryUpdate();       // bei DDE-Links TryUpdate statt Update
//STRIP001         }
//STRIP001     }
/*N*/ }

/*N*/ BOOL ScDocument::UpdateDdeLink( const String& rAppl, const String& rTopic, const String& rItem )
/*N*/ {
/*N*/   //  fuer refresh() per StarOne Api
/*N*/   //  ResetValue() fuer einzelnen Link nicht noetig
/*N*/   //! wenn's mal alles asynchron wird, aber auch hier
/*N*/
/*N*/   BOOL bFound = FALSE;
/*N*/     if (pLinkManager)
/*N*/     {
/*?*/         DBG_BF_ASSERT(0, "STRIP"); //STRIP001 const ::so3::SvBaseLinks& rLinks = pLinkManager->GetLinks();
//STRIP001         USHORT nCount = rLinks.Count();
//STRIP001         for (USHORT i=0; i<nCount; i++)
//STRIP001         {
//STRIP001             ::so3::SvBaseLink* pBase = *rLinks[i];
//STRIP001             if (pBase->ISA(ScDdeLink))
//STRIP001             {
//STRIP001                 ScDdeLink* pDdeLink = (ScDdeLink*)pBase;
//STRIP001                 if ( pDdeLink->GetAppl() == rAppl &&
//STRIP001                      pDdeLink->GetTopic() == rTopic &&
//STRIP001                      pDdeLink->GetItem() == rItem )
//STRIP001                 {
//STRIP001                     pDdeLink->TryUpdate();
//STRIP001                     bFound = TRUE;          // koennen theoretisch mehrere sein (Mode), darum weitersuchen
//STRIP001                 }
//STRIP001             }
//STRIP001         }
/*N*/     }
/*N*/   return bFound;
/*N*/ }

//STRIP001 void ScDocument::DisconnectDdeLinks()
//STRIP001 {
//STRIP001  if (pLinkManager)
//STRIP001  {
//STRIP001      const ::so3::SvBaseLinks& rLinks = pLinkManager->GetLinks();
//STRIP001      USHORT nCount = rLinks.Count();
//STRIP001      for (USHORT i=0; i<nCount; i++)
//STRIP001      {
//STRIP001          ::so3::SvBaseLink* pBase = *rLinks[i];
//STRIP001          if (pBase->ISA(ScDdeLink))
//STRIP001              pBase->Disconnect();            // bleibt im LinkManager eingetragen
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void ScDocument::CopyDdeLinks( ScDocument* pDestDoc ) const
//STRIP001 {
//STRIP001  if (bIsClip)        // aus Stream erzeugen
//STRIP001  {
//STRIP001      if (pClipData)
//STRIP001      {
//STRIP001          pClipData->Seek(0);
//STRIP001          pDestDoc->LoadDdeLinks(*pClipData);
//STRIP001      }
//STRIP001  }
//STRIP001     else if (pLinkManager)              // Links direkt kopieren
//STRIP001  {
//STRIP001      const ::so3::SvBaseLinks& rLinks = pLinkManager->GetLinks();
//STRIP001      USHORT nCount = rLinks.Count();
//STRIP001      for (USHORT i=0; i<nCount; i++)
//STRIP001      {
//STRIP001          ::so3::SvBaseLink* pBase = *rLinks[i];
//STRIP001          if (pBase->ISA(ScDdeLink))
//STRIP001          {
//STRIP001              ScDdeLink* pNew = new ScDdeLink( pDestDoc, *(ScDdeLink*)pBase );
//STRIP001
//STRIP001              pDestDoc->pLinkManager->InsertDDELink( pNew,
//STRIP001                              pNew->GetAppl(), pNew->GetTopic(), pNew->GetItem() );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*N*/ USHORT ScDocument::GetDdeLinkCount() const
/*N*/ {
/*N*/   USHORT nDdeCount = 0;
/*N*/   if (pLinkManager)
/*N*/   {
/*N*/       const ::so3::SvBaseLinks& rLinks = pLinkManager->GetLinks();
/*N*/       USHORT nCount = rLinks.Count();
/*N*/       for (USHORT i=0; i<nCount; i++)
/*N*/           if ((*rLinks[i])->ISA(ScDdeLink))
/*N*/               ++nDdeCount;
/*N*/   }
/*N*/   return nDdeCount;
/*N*/ }

/*N*/ BOOL ScDocument::GetDdeLinkData( USHORT nPos, String& rAppl, String& rTopic, String& rItem ) const
/*N*/ {
/*N*/   USHORT nDdeCount = 0;
/*N*/   if (pLinkManager)
/*N*/   {
/*N*/       const ::so3::SvBaseLinks& rLinks = pLinkManager->GetLinks();
/*N*/       USHORT nCount = rLinks.Count();
/*N*/       for (USHORT i=0; i<nCount; i++)
/*N*/       {
/*N*/           ::so3::SvBaseLink* pBase = *rLinks[i];
/*N*/           if (pBase->ISA(ScDdeLink))
/*N*/           {
/*N*/               if ( nDdeCount == nPos )
/*N*/               {
/*N*/                   ScDdeLink* pDde = (ScDdeLink*)pBase;
/*N*/                   rAppl  = pDde->GetAppl();
/*N*/                   rTopic = pDde->GetTopic();
/*N*/                   rItem  = pDde->GetItem();
/*N*/                   return TRUE;
/*N*/               }
/*N*/               ++nDdeCount;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   return FALSE;
/*N*/ }

/*N*/ BOOL ScDocument::GetDdeLinkMode(USHORT nPos, USHORT& nMode)
/*N*/ {
/*N*/   USHORT nDdeCount = 0;
/*N*/   if (pLinkManager)
/*N*/   {
/*N*/       const ::so3::SvBaseLinks& rLinks = pLinkManager->GetLinks();
/*N*/       USHORT nCount = rLinks.Count();
/*N*/       for (USHORT i=0; i<nCount; i++)
/*N*/       {
/*N*/           ::so3::SvBaseLink* pBase = *rLinks[i];
/*N*/           if (pBase->ISA(ScDdeLink))
/*N*/           {
/*N*/               if ( nDdeCount == nPos )
/*N*/               {
/*N*/                   ScDdeLink* pDde = (ScDdeLink*)pBase;
/*N*/                   nMode = pDde->GetMode();
/*N*/                   return TRUE;
/*N*/               }
/*N*/               ++nDdeCount;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   return FALSE;
/*N*/ }

/*N*/ BOOL ScDocument::GetDdeLinkResultDimension( USHORT nPos, USHORT& nCol, USHORT& nRow, ScMatrix*& pMatrix)
/*N*/ {
/*N*/   USHORT nDdeCount = 0;
/*N*/   if (pLinkManager)
/*N*/   {
/*N*/       const ::so3::SvBaseLinks& rLinks = pLinkManager->GetLinks();
/*N*/       USHORT nCount = rLinks.Count();
/*N*/       for (USHORT i=0; i<nCount; i++)
/*N*/       {
/*N*/           ::so3::SvBaseLink* pBase = *rLinks[i];
/*N*/           if (pBase->ISA(ScDdeLink))
/*N*/           {
/*N*/               if ( nDdeCount == nPos )
/*N*/               {
/*N*/                   ScDdeLink* pDde = (ScDdeLink*)pBase;
/*N*/                   pMatrix = pDde->GetResult();
/*N*/                   if (pMatrix)
/*N*/                   {
/*N*/                       pMatrix->GetDimensions(nCol, nRow);
/*N*/                       return TRUE;
/*N*/                   }
/*N*/               }
/*N*/               ++nDdeCount;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   return FALSE;
/*N*/ }

/*N*/ BOOL ScDocument::GetDdeLinkResult(const ScMatrix* pMatrix, USHORT nCol, USHORT nRow, String& rStrValue, double& rDoubValue, BOOL& bIsString)
/*N*/ {
DBG_BF_ASSERT(0, "STRIP"); //STRIP001   if (pMatrix)
//STRIP001  {
//STRIP001      BOOL bIsEmpty = pMatrix->IsEmpty(nCol, nRow);
//STRIP001         if (bIsEmpty)
//STRIP001         {
//STRIP001             bIsString = TRUE;
//STRIP001             rStrValue.Erase();
//STRIP001         }
//STRIP001         else
//STRIP001         {
//STRIP001             bIsString = pMatrix->IsString(nCol, nRow);
//STRIP001             if (bIsString)
//STRIP001                 rStrValue = pMatrix->GetString(nCol, nRow);
//STRIP001             else
//STRIP001                 rDoubValue = pMatrix->GetDouble(nCol, nRow);
//STRIP001         }
//STRIP001      return bIsEmpty;
//STRIP001  }
/*N*/   return TRUE;
/*N*/ }

/*N*/ void ScDocument::CreateDdeLink(const String& rAppl, const String& rTopic, const String& rItem, const BYTE nMode )
/*N*/ {
    //  DDE-Link anlegen und nicht updaten (z.B. fuer Excel-Import,
DBG_BF_ASSERT(0, "STRIP"); //STRIP001 //STRIP001    //  damit nicht ohne Nachfrage Verbindungen aufgebaut werden)
//STRIP001  //  zuerst suchen, ob schon vorhanden
//STRIP001  //! Dde-Links (zusaetzlich) effizienter am Dokument speichern?
//STRIP001     if (pLinkManager)
//STRIP001     {
//STRIP001         const ::so3::SvBaseLinks& rLinks = pLinkManager->GetLinks();
//STRIP001         USHORT nCount = rLinks.Count();
//STRIP001         for (USHORT i=0; i<nCount; i++)
//STRIP001         {
//STRIP001             ::so3::SvBaseLink* pBase = *rLinks[i];
//STRIP001             if (pBase->ISA(ScDdeLink))
//STRIP001             {
//STRIP001                 ScDdeLink* pLink = (ScDdeLink*)pBase;
//STRIP001                 if ( pLink->GetAppl() == rAppl &&
//STRIP001                      pLink->GetTopic() == rTopic &&
//STRIP001                      pLink->GetItem() == rItem &&
//STRIP001                      pLink->GetMode() == nMode )
//STRIP001                     return;                                     // dann nichts tun
//STRIP001             }
//STRIP001         }
//STRIP001
//STRIP001         //  neu anlegen, aber kein TryUpdate
//STRIP001         ScDdeLink* pNew = new ScDdeLink( this, rAppl, rTopic, rItem, nMode );
//STRIP001         pLinkManager->InsertDDELink( pNew, rAppl, rTopic, rItem );
//STRIP001     }
/*N*/ }

/*N*/ BOOL ScDocument::FindDdeLink(const String& rAppl, const String& rTopic, const String& rItem, const BYTE nMode, USHORT& nPos )
/*N*/ {
/*?*/     DBG_BF_ASSERT(0, "STRIP"); //STRIP001 if (pLinkManager)
//STRIP001     {
//STRIP001         const ::so3::SvBaseLinks& rLinks = pLinkManager->GetLinks();
//STRIP001         USHORT nCount = rLinks.Count();
//STRIP001         USHORT nDdeCount = 0;
//STRIP001         for (USHORT i=0; i<nCount; i++)
//STRIP001         {
//STRIP001             ::so3::SvBaseLink* pBase = *rLinks[i];
//STRIP001             if (pBase->ISA(ScDdeLink))
//STRIP001             {
//STRIP001                 ScDdeLink* pLink = (ScDdeLink*)pBase;
//STRIP001                 if ( pLink->GetAppl() == rAppl &&
//STRIP001                      pLink->GetTopic() == rTopic &&
//STRIP001                      pLink->GetItem() == rItem &&
//STRIP001                      (nMode == SC_DDE_IGNOREMODE || pLink->GetMode() == nMode) )
//STRIP001                 {
//STRIP001                     nPos = nDdeCount;
//STRIP001                     return TRUE;
//STRIP001                 }
//STRIP001                 nDdeCount++;
//STRIP001             }
//STRIP001         }
//STRIP001     }
/*N*/   return FALSE;
/*N*/ }

/*N*/ BOOL ScDocument::CreateDdeLinkResultDimension(USHORT nPos, USHORT nCols, USHORT nRows, ScMatrix*& pMatrix)
/*N*/ {
DBG_BF_ASSERT(0, "STRIP"); //STRIP001   USHORT nDdeCount = 0;
//STRIP001  if (pLinkManager)
//STRIP001  {
//STRIP001      const ::so3::SvBaseLinks& rLinks = pLinkManager->GetLinks();
//STRIP001      USHORT nCount = rLinks.Count();
//STRIP001      for (USHORT i=0; i<nCount; i++)
//STRIP001      {
//STRIP001          ::so3::SvBaseLink* pBase = *rLinks[i];
//STRIP001          if (pBase->ISA(ScDdeLink))
//STRIP001          {
//STRIP001              if ( nDdeCount == nPos )
//STRIP001              {
//STRIP001                  ScDdeLink* pDde = (ScDdeLink*)pBase;
//STRIP001                  pDde->NewData(nCols, nRows);
//STRIP001                  pMatrix = pDde->GetResult();
//STRIP001                  if (pMatrix)
//STRIP001                      return TRUE;
//STRIP001                  else
//STRIP001                      return FALSE;
//STRIP001              }
//STRIP001              ++nDdeCount;
//STRIP001          }
//STRIP001      }
//STRIP001  }
/*N*/   return FALSE;
/*N*/ }

void ScDocument::SetDdeLinkResult(ScMatrix* pMatrix, const USHORT nCol, const USHORT nRow, const String& rStrValue, const double& rDoubValue, BOOL bString, BOOL bEmpty)
{
DBG_BF_ASSERT(0, "STRIP"); //STRIP001   DBG_ASSERT(pMatrix, "there is no matrix");
//STRIP001  if (pMatrix)
//STRIP001  {
//STRIP001      if(bEmpty)
//STRIP001          pMatrix->PutEmpty(nCol, nRow);
//STRIP001      else
//STRIP001      {
//STRIP001          if (bString)
//STRIP001              pMatrix->PutString(rStrValue, nCol, nRow);
//STRIP001          else
//STRIP001              pMatrix->PutDouble(rDoubValue, nCol, nRow);
//STRIP001      }
//STRIP001  }
/*N*/ }

//------------------------------------------------------------------------

/*N*/ BOOL ScDocument::HasAreaLinks() const
/*N*/ {
/*N*/   if (pLinkManager)           // Clipboard z.B. hat keinen LinkManager
/*N*/   {
/*N*/       const ::so3::SvBaseLinks& rLinks = pLinkManager->GetLinks();
/*N*/       USHORT nCount = rLinks.Count();
/*N*/       for (USHORT i=0; i<nCount; i++)
/*?*/           if ((*rLinks[i])->ISA(ScAreaLink))
/*?*/               return TRUE;
/*N*/   }
/*N*/
/*N*/   return FALSE;
/*N*/ }

/*N*/ void ScDocument::UpdateAreaLinks()
/*N*/ {
/*?*/     DBG_BF_ASSERT(0, "STRIP"); //STRIP001 if (pLinkManager)
//STRIP001     {
//STRIP001         const ::so3::SvBaseLinks& rLinks = pLinkManager->GetLinks();
//STRIP001         USHORT nCount = rLinks.Count();
//STRIP001         for (USHORT i=0; i<nCount; i++)
//STRIP001         {
//STRIP001             ::so3::SvBaseLink* pBase = *rLinks[i];
//STRIP001             if (pBase->ISA(ScAreaLink))
//STRIP001                 pBase->Update();
//STRIP001         }
//STRIP001     }
/*N*/ }

/*N*/ void ScDocument::UpdateRefAreaLinks( UpdateRefMode eUpdateRefMode,
/*N*/                            const ScRange& rRange, short nDx, short nDy, short nDz )
/*N*/ {
/*N*/     if (pLinkManager)
/*N*/     {
/*N*/         const ::so3::SvBaseLinks& rLinks = pLinkManager->GetLinks();
/*N*/         USHORT nCount = rLinks.Count();
/*N*/         for (USHORT i=0; i<nCount; i++)
/*N*/         {
/*?*/             ::so3::SvBaseLink* pBase = *rLinks[i];
/*?*/             if (pBase->ISA(ScAreaLink))
/*?*/             {
/*?*/                 ScAreaLink* pLink = (ScAreaLink*) pBase;
/*?*/                 ScRange aOutRange = pLink->GetDestArea();
/*?*/
/*?*/                 USHORT nCol1 = aOutRange.aStart.Col();
/*?*/                 USHORT nRow1 = aOutRange.aStart.Row();
/*?*/                 USHORT nTab1 = aOutRange.aStart.Tab();
/*?*/                 USHORT nCol2 = aOutRange.aEnd.Col();
/*?*/                 USHORT nRow2 = aOutRange.aEnd.Row();
/*?*/                 USHORT nTab2 = aOutRange.aEnd.Tab();
/*?*/
/*?*/                 ScRefUpdateRes eRes =
/*?*/                     ScRefUpdate::Update( this, eUpdateRefMode,
/*?*/                         rRange.aStart.Col(), rRange.aStart.Row(), rRange.aStart.Tab(),
/*?*/                         rRange.aEnd.Col(), rRange.aEnd.Row(), rRange.aEnd.Tab(), nDx, nDy, nDz,
/*?*/                         nCol1, nRow1, nTab1, nCol2, nRow2, nTab2 );
/*?*/                 if ( eRes != UR_NOTHING )
/*?*/                     pLink->SetDestArea( ScRange( nCol1, nRow1, nTab1, nCol2, nRow2, nTab2 ) );
/*?*/             }
/*N*/         }
/*N*/     }
/*N*/ }

/*N*/ void ScDocument::SaveAreaLinks(SvStream& rStream) const
/*N*/ {
/*N*/   const ::so3::SvBaseLinks& rLinks = pLinkManager->GetLinks();
/*N*/   USHORT nCount = rLinks.Count();
/*N*/
/*N*/   //  erstmal zaehlen...
/*N*/
/*N*/   USHORT nAreaCount = 0;
/*N*/   USHORT i;
/*N*/   for (i=0; i<nCount; i++)
/*N*/       if ((*rLinks[i])->ISA(ScAreaLink))      // rLinks[i] = Pointer auf Ref
/*N*/           ++nAreaCount;
/*N*/
/*N*/   //  Header
/*N*/
/*N*/   ScMultipleWriteHeader aHdr( rStream );
/*N*/   rStream << nAreaCount;
/*N*/
/*N*/   //  Links speichern
/*N*/
/*N*/   for (i=0; i<nCount; i++)
/*N*/   {
/*N*/       ::so3::SvBaseLink* pBase = *rLinks[i];
/*N*/       if (pBase->ISA(ScAreaLink))
/*N*/       {
/*?*/           ScAreaLink* pLink = (ScAreaLink*)pBase;
/*?*/
/*?*/           aHdr.StartEntry();
/*?*/
/*?*/           rStream.WriteByteString( pLink->GetFile(), rStream.GetStreamCharSet() );
/*?*/           rStream.WriteByteString( pLink->GetFilter(), rStream.GetStreamCharSet() );
/*?*/           rStream.WriteByteString( pLink->GetSource(), rStream.GetStreamCharSet() );
/*?*/           rStream << pLink->GetDestArea();                // ScRange
/*?*/           rStream.WriteByteString( pLink->GetOptions(), rStream.GetStreamCharSet() );
/*?*/           //  filter options starting from 336
/*?*/
/*?*/           aHdr.EndEntry();
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ void ScDocument::LoadAreaLinks(SvStream& rStream)
/*N*/ {
/*N*/   ScMultipleReadHeader aHdr( rStream );
/*N*/
/*N*/   if (!pShell)
/*N*/   {
/*N*/       DBG_ERROR("AreaLinks koennen nicht ohne Shell geladen werden");
/*N*/       return;
/*N*/   }
/*N*/
/*N*/   String aFile, aFilter, aOptions, aSource;
/*N*/   ScRange aDestArea;
/*N*/
/*N*/   USHORT nCount;
/*N*/   rStream >> nCount;
/*N*/   for (USHORT i=0; i<nCount; i++)
/*N*/   {
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 aHdr.StartEntry();
/*?*/
//STRIP001 /*?*/        rStream.ReadByteString( aFile,   rStream.GetStreamCharSet() );
//STRIP001 /*?*/        rStream.ReadByteString( aFilter, rStream.GetStreamCharSet() );
//STRIP001 /*?*/        rStream.ReadByteString( aSource, rStream.GetStreamCharSet() );
//STRIP001 /*?*/        rStream >> aDestArea;
//STRIP001 /*?*/        if ( aHdr.BytesLeft() )         // Filter-Optionen ab 336
//STRIP001 /*?*/            rStream.ReadByteString( aOptions, rStream.GetStreamCharSet() );
//STRIP001 /*?*/        else
//STRIP001 /*?*/            aOptions.Erase();
//STRIP001 /*?*/        aHdr.EndEntry();
//STRIP001 /*?*/
//STRIP001 /*?*/        ScAreaLink* pLink = new ScAreaLink( pShell, aFile, aFilter, aOptions,
//STRIP001 /*?*/                                            aSource, aDestArea.aStart, 0 );
//STRIP001 /*?*/        pLink->SetInCreate( TRUE );
//STRIP001 /*?*/        pLink->SetDestArea( aDestArea );
//STRIP001 /*?*/        pLinkManager->InsertFileLink( *pLink, OBJECT_CLIENT_FILE, aFile, &aFilter, &aSource );
//STRIP001 /*?*/        pLink->Update();
//STRIP001 /*?*/        pLink->SetInCreate( FALSE );
/*N*/   }
/*N*/ }


//------------------------------------------------------------------------

// TimerDelays etc.
//STRIP001 void ScDocument::KeyInput( const KeyEvent& rKEvt )
//STRIP001 {
//STRIP001  if ( pChartListenerCollection->GetCount() )
//STRIP001      pChartListenerCollection->StartTimer();
//STRIP001 }

//  ----------------------------------------------------------------------------

/*N*/ BOOL ScDocument::CheckMacroWarn()
/*N*/ {
/*N*/   //  The check for macro configuration, macro warning and disabling is now handled
/*N*/   //  in SfxObjectShell::AdjustMacroMode, called by SfxObjectShell::CallBasic.
/*N*/
/*N*/   return TRUE;
/*N*/ }

//STRIP001 BOOL ScDocument::HasMacroCallsAfterLoad()
//STRIP001 {
//STRIP001     //  not used any longer
//STRIP001
//STRIP001     DBG_ERROR("obsolete method HasMacroCallsAfterLoad called");
//STRIP001     return FALSE;
//STRIP001 }

//------------------------------------------------------------------------

/*N*/ SfxBindings* ScDocument::GetViewBindings()
/*N*/ {
/*N*/   //  used to invalidate slots after changes to this document
/*N*/
/*N*/   if ( !pShell )
/*N*/       return NULL;        // no ObjShell -> no view
/*N*/
/*N*/   //  first check current view
/*N*/   SfxViewFrame* pViewFrame = SfxViewFrame::Current();
/*N*/   if ( pViewFrame && pViewFrame->GetObjectShell() != pShell )     // wrong document?
/*N*/       pViewFrame = NULL;
/*N*/
/*N*/   //  otherwise use first view for this doc
/*N*/   if ( !pViewFrame )
/*N*/       pViewFrame = SfxViewFrame::GetFirst( pShell );
/*N*/
/*N*/   if (pViewFrame)
/*N*/       return &pViewFrame->GetBindings();
/*N*/   else
/*N*/       return NULL;
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 void lcl_TransliterateEditEngine( ScEditEngineDefaulter& rEngine,
//STRIP001                              utl::TransliterationWrapper& rTranslitarationWrapper,
//STRIP001                              BOOL bConsiderLanguage, ScDocument* pDoc )
//STRIP001 {
//STRIP001  //! should use TransliterateText method of EditEngine instead, when available!
//STRIP001
//STRIP001  sal_uInt16 nLanguage = LANGUAGE_SYSTEM;
//STRIP001
//STRIP001  USHORT nParCount = rEngine.GetParagraphCount();
//STRIP001  for (USHORT nPar=0; nPar<nParCount; nPar++)
//STRIP001  {
//STRIP001      SvUShorts aPortions;
//STRIP001      rEngine.GetPortions( (USHORT)nPar, aPortions );
//STRIP001
//STRIP001      for ( USHORT nPos = aPortions.Count(); nPos; )
//STRIP001      {
//STRIP001          --nPos;
//STRIP001          USHORT nEnd = aPortions.GetObject( nPos );
//STRIP001          USHORT nStart = nPos ? aPortions.GetObject( nPos - 1 ) : 0;
//STRIP001
//STRIP001          ESelection aSel( nPar, nStart, nPar, nEnd );
//STRIP001          String aOldStr = rEngine.GetText( aSel );
//STRIP001          SfxItemSet aAttr = rEngine.GetAttribs( aSel );
//STRIP001
//STRIP001          if ( aAttr.GetItemState( EE_FEATURE_FIELD ) != SFX_ITEM_ON )    // fields are not touched
//STRIP001          {
//STRIP001              if ( bConsiderLanguage )
//STRIP001              {
//STRIP001                  BYTE nScript = pDoc->GetStringScriptType( aOldStr );
//STRIP001                  USHORT nWhich = ( nScript == SCRIPTTYPE_ASIAN ) ? EE_CHAR_LANGUAGE_CJK :
//STRIP001                                  ( ( nScript == SCRIPTTYPE_COMPLEX ) ? EE_CHAR_LANGUAGE_CTL :
//STRIP001                                                                          EE_CHAR_LANGUAGE );
//STRIP001                  nLanguage = ((const SvxLanguageItem&)aAttr.Get(nWhich)).GetValue();
//STRIP001              }
//STRIP001
//STRIP001              ::com::sun::star::uno::Sequence<sal_Int32> aOffsets;
//STRIP001              String aNewStr = rTranslitarationWrapper.transliterate( aOldStr, nLanguage, 0, aOldStr.Len(), &aOffsets );
//STRIP001
//STRIP001              if ( aNewStr != aOldStr )
//STRIP001              {
//STRIP001                  // replace string, keep attributes
//STRIP001
//STRIP001                  rEngine.QuickInsertText( aNewStr, aSel );
//STRIP001                  aSel.nEndPos = aSel.nStartPos + aNewStr.Len();
//STRIP001                  rEngine.QuickSetAttribs( aAttr, aSel );
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void ScDocument::TransliterateText( const ScMarkData& rMultiMark, sal_Int32 nType )
//STRIP001 {
//STRIP001  DBG_ASSERT( rMultiMark.IsMultiMarked(), "TransliterateText: no selection" );
//STRIP001
//STRIP001  utl::TransliterationWrapper aTranslitarationWrapper( xServiceManager, nType );
//STRIP001  BOOL bConsiderLanguage = aTranslitarationWrapper.needLanguageForTheMode();
//STRIP001  sal_uInt16 nLanguage = LANGUAGE_SYSTEM;
//STRIP001
//STRIP001  ScEditEngineDefaulter* pEngine = NULL;      // not using pEditEngine member because of defaults
//STRIP001
//STRIP001  USHORT nCount = GetTableCount();
//STRIP001  for (USHORT nTab = 0; nTab < nCount; nTab++)
//STRIP001      if ( pTab[nTab] && rMultiMark.GetTableSelect(nTab) )
//STRIP001      {
//STRIP001          USHORT nCol = 0;
//STRIP001          USHORT nRow = 0;
//STRIP001
//STRIP001          BOOL bFound = rMultiMark.IsCellMarked( nCol, nRow );
//STRIP001          if (!bFound)
//STRIP001              bFound = GetNextMarkedCell( nCol, nRow, nTab, rMultiMark );
//STRIP001
//STRIP001          while (bFound)
//STRIP001          {
//STRIP001              const ScBaseCell* pCell = GetCell( ScAddress( nCol, nRow, nTab ) );
//STRIP001              CellType eType = pCell ? pCell->GetCellType() : CELLTYPE_NONE;
//STRIP001
//STRIP001              if ( eType == CELLTYPE_STRING )
//STRIP001              {
//STRIP001                  String aOldStr;
//STRIP001                  ((const ScStringCell*)pCell)->GetString(aOldStr);
//STRIP001                  xub_StrLen nOldLen = aOldStr.Len();
//STRIP001
//STRIP001                  if ( bConsiderLanguage )
//STRIP001                  {
//STRIP001                      BYTE nScript = GetStringScriptType( aOldStr );      //! cell script type?
//STRIP001                      USHORT nWhich = ( nScript == SCRIPTTYPE_ASIAN ) ? ATTR_CJK_FONT_LANGUAGE :
//STRIP001                                      ( ( nScript == SCRIPTTYPE_COMPLEX ) ? ATTR_CTL_FONT_LANGUAGE :
//STRIP001                                                                              ATTR_FONT_LANGUAGE );
//STRIP001                      nLanguage = ((const SvxLanguageItem*)GetAttr( nCol, nRow, nTab, nWhich ))->GetValue();
//STRIP001                  }
//STRIP001
//STRIP001                  ::com::sun::star::uno::Sequence<sal_Int32> aOffsets;
//STRIP001                  String aNewStr = aTranslitarationWrapper.transliterate( aOldStr, nLanguage, 0, nOldLen, &aOffsets );
//STRIP001
//STRIP001                  if ( aNewStr != aOldStr )
//STRIP001                      PutCell( nCol, nRow, nTab, new ScStringCell( aNewStr ) );
//STRIP001              }
//STRIP001              else if ( eType == CELLTYPE_EDIT )
//STRIP001              {
//STRIP001                  if (!pEngine)
//STRIP001                      pEngine = new ScFieldEditEngine( GetEnginePool(), GetEditPool() );
//STRIP001
//STRIP001                  // defaults from cell attributes must be set so right language is used
//STRIP001                  const ScPatternAttr* pPattern = GetPattern( nCol, nRow, nTab );
//STRIP001                  SfxItemSet* pDefaults = new SfxItemSet( pEngine->GetEmptyItemSet() );
//STRIP001                  pPattern->FillEditItemSet( pDefaults );
//STRIP001                  pEngine->SetDefaults( pDefaults, TRUE );
//STRIP001
//STRIP001                  const EditTextObject* pData = ((const ScEditCell*)pCell)->GetData();
//STRIP001                  pEngine->SetText( *pData );
//STRIP001
//STRIP001                  pEngine->ClearModifyFlag();
//STRIP001
//STRIP001                  lcl_TransliterateEditEngine( *pEngine, aTranslitarationWrapper, bConsiderLanguage, this );
//STRIP001
//STRIP001                  if ( pEngine->IsModified() )
//STRIP001                  {
//STRIP001                      ScEditAttrTester aTester( pEngine );
//STRIP001                      if ( aTester.NeedsObject() )
//STRIP001                      {
//STRIP001                          // remove defaults (paragraph attributes) before creating text object
//STRIP001                          SfxItemSet* pEmpty = new SfxItemSet( pEngine->GetEmptyItemSet() );
//STRIP001                          pEngine->SetDefaults( pEmpty, TRUE );
//STRIP001
//STRIP001                          EditTextObject* pNewData = pEngine->CreateTextObject();
//STRIP001                          PutCell( nCol, nRow, nTab,
//STRIP001                              new ScEditCell( pNewData, this, pEngine->GetEditTextObjectPool() ) );
//STRIP001                          delete pNewData;
//STRIP001                      }
//STRIP001                      else
//STRIP001                      {
//STRIP001                          String aNewStr = pEngine->GetText();
//STRIP001                          PutCell( nCol, nRow, nTab, new ScStringCell( aNewStr ) );
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001
//STRIP001              bFound = GetNextMarkedCell( nCol, nRow, nTab, rMultiMark );
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001  delete pEngine;
//STRIP001 }

}
