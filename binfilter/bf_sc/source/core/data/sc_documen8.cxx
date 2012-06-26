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

#include "scitems.hxx"
#define ITEMID_FIELD EE_FEATURE_FIELD

#include <bf_svx/frmdiritem.hxx>
#include <bf_svx/langitem.hxx>
#include <bf_svx/linkmgr.hxx>
#include <bf_sfx2/printer.hxx>
#include <bf_svtools/flagitem.hxx>
#define _SVSTDARR_USHORTS
#include <bf_svtools/zformat.hxx>
#include <bf_sfx2/misccfg.hxx>
#include <bf_sfx2/app.hxx>


#include "poolhelp.hxx"
#include "docpool.hxx"
#include "stlpool.hxx"
#include "docoptio.hxx"
#include "viewopti.hxx"
#include "rechead.hxx"
#include "ddelink.hxx"
#include "scmatrix.hxx"
#include "arealink.hxx"
#include "patattr.hxx"
#include "editutil.hxx"
#include "document.hxx"
#include "refupdat.hxx"
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
/*?*/       OSL_FAIL( "Document options corrupted. Setting to defaults." );
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

//------------------------------------------------------------------------


//  SPELL_MAXCELLS muss mindestens 256 sein, solange am Iterator keine
//  Start-Spalte gesetzt werden kann

//! SPELL_MAXTEST fuer Timer und Idle unterschiedlich ???

//  SPELL_MAXTEST now divided between visible and rest of document

#define SPELL_MAXTEST_VIS   1
#define SPELL_MAXTEST_ALL   3
#define SPELL_MAXCELLS      256

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

/*N*/ void ScDocument::SetInLinkUpdate(BOOL bSet)
/*N*/ {
/*N*/   //  called from TableLink and AreaLink
/*N*/
/*N*/   DBG_ASSERT( bInLinkUpdate != bSet, "SetInLinkUpdate twice" );
/*N*/   bInLinkUpdate = bSet;
/*N*/ }


/*N*/ USHORT ScDocument::GetDdeLinkCount() const
/*N*/ {
/*N*/   USHORT nDdeCount = 0;
/*N*/   if (pLinkManager)
/*N*/   {
/*N*/       const ::binfilter::SvBaseLinks& rLinks = pLinkManager->GetLinks();
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
/*N*/       const ::binfilter::SvBaseLinks& rLinks = pLinkManager->GetLinks();
/*N*/       USHORT nCount = rLinks.Count();
/*N*/       for (USHORT i=0; i<nCount; i++)
/*N*/       {
/*N*/           ::binfilter::SvBaseLink* pBase = *rLinks[i];
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
/*N*/       const ::binfilter::SvBaseLinks& rLinks = pLinkManager->GetLinks();
/*N*/       USHORT nCount = rLinks.Count();
/*N*/       for (USHORT i=0; i<nCount; i++)
/*N*/       {
/*N*/           ::binfilter::SvBaseLink* pBase = *rLinks[i];
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
/*N*/       const ::binfilter::SvBaseLinks& rLinks = pLinkManager->GetLinks();
/*N*/       USHORT nCount = rLinks.Count();
/*N*/       for (USHORT i=0; i<nCount; i++)
/*N*/       {
/*N*/           ::binfilter::SvBaseLink* pBase = *rLinks[i];
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

//------------------------------------------------------------------------

/*N*/ void ScDocument::UpdateRefAreaLinks( UpdateRefMode eUpdateRefMode,
/*N*/                            const ScRange& rRange, short nDx, short nDy, short nDz )
/*N*/ {
/*N*/     if (pLinkManager)
/*N*/     {
/*N*/         const ::binfilter::SvBaseLinks& rLinks = pLinkManager->GetLinks();
/*N*/         USHORT nCount = rLinks.Count();
/*N*/         for (USHORT i=0; i<nCount; i++)
/*N*/         {
/*?*/             ::binfilter::SvBaseLink* pBase = *rLinks[i];
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

/*N*/ void ScDocument::LoadAreaLinks(SvStream& rStream)
/*N*/ {
/*N*/   ScMultipleReadHeader aHdr( rStream );
/*N*/
/*N*/   if (!pShell)
/*N*/   {
/*N*/       OSL_FAIL("AreaLinks koennen nicht ohne Shell geladen werden");
/*N*/       return;
/*N*/   }
/*N*/
/*N*/   String aFile, aFilter, aOptions, aSource;
/*N*/   ScRange aDestArea;
/*N*/
/*N*/   USHORT nCount;
/*N*/   rStream >> nCount;
/*N*/ }

//------------------------------------------------------------------------

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
