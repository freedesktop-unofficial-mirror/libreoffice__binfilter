/*************************************************************************
 *
 *  $RCSfile: sc_progress.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:26:33 $
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
#include "core_pch.hxx"
#endif

#pragma hdrstop

//------------------------------------------------------------------------

#include <bf_sfx2/app.hxx>
#include <bf_sfx2/objsh.hxx>
#include <bf_sfx2/progress.hxx>
#include <bf_sfx2/docfile.hxx>
#include <bf_sfx2/sfxsids.hrc>
#include <svtools/eitem.hxx>
#include <svtools/itemset.hxx>

#define SC_PROGRESS_CXX
#include "progress.hxx"
#include "document.hxx"
#include "global.hxx"
#include "globstr.hrc"
namespace binfilter {



static ScProgress theDummyInterpretProgress;
SfxProgress*    ScProgress::pGlobalProgress = NULL;
ULONG           ScProgress::nGlobalRange = 0;
ULONG           ScProgress::nGlobalPercent = 0;
BOOL            ScProgress::bGlobalNoUserBreak = TRUE;
ScProgress*     ScProgress::pInterpretProgress = &theDummyInterpretProgress;
ScProgress*     ScProgress::pOldInterpretProgress = NULL;
ULONG           ScProgress::nInterpretProgress = 0;
BOOL            ScProgress::bAllowInterpretProgress = TRUE;
ScDocument*     ScProgress::pInterpretDoc;
BOOL            ScProgress::bIdleWasDisabled = FALSE;


//STRIP001 BOOL lcl_IsHiddenDocument( SfxObjectShell* pObjSh )
//STRIP001 {
//STRIP001  if (pObjSh)
//STRIP001  {
//STRIP001      SfxMedium* pMed = pObjSh->GetMedium();
//STRIP001      if (pMed)
//STRIP001      {
//STRIP001          SfxItemSet* pSet = pMed->GetItemSet();
//STRIP001          const SfxPoolItem* pItem;
//STRIP001          if ( pSet && SFX_ITEM_SET == pSet->GetItemState( SID_HIDDEN, TRUE, &pItem ) &&
//STRIP001                      ((const SfxBoolItem*)pItem)->GetValue() )
//STRIP001              return TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  return FALSE;
//STRIP001 }

/*N*/ ScProgress::ScProgress( SfxObjectShell* pObjSh, const String& rText,
/*N*/                       ULONG nRange, BOOL bAllDocs, BOOL bWait )
/*N*/ {
/*N*/
/*N*/   if ( pGlobalProgress || SfxProgress::GetActiveProgress( NULL ) )
/*N*/   {
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001 if ( lcl_IsHiddenDocument(pObjSh) )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            // loading a hidden document while a progress is active is possible - no error
//STRIP001 /*?*/            pProgress = NULL;
//STRIP001 /*?*/        }
//STRIP001 /*?*/        else
//STRIP001 /*?*/        {
//STRIP001 /*?*/            DBG_ERROR( "ScProgress: there can be only one!" );
//STRIP001 /*?*/            pProgress = NULL;
//STRIP001 /*?*/        }
/*N*/   }
/*N*/   else if ( SFX_APP()->IsDowning() )
/*N*/   {
/*N*/       //  kommt vor z.B. beim Speichern des Clipboard-Inhalts als OLE beim Beenden
/*N*/       //  Dann wuerde ein SfxProgress wild im Speicher rummuellen
/*N*/       //! Soll das so sein ???
/*N*/
/*N*/       pProgress = NULL;
/*N*/   }
/*N*/   else if ( pObjSh && ( pObjSh->GetCreateMode() == SFX_CREATE_MODE_EMBEDDED ||
/*N*/                         pObjSh->GetProgress() ) )
/*N*/   {
/*N*/       //  #62808# no own progress for embedded objects,
/*N*/       //  #73633# no second progress if the document already has one
/*N*/
/*N*/       pProgress = NULL;
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       pProgress = new SfxProgress( pObjSh, rText, nRange, bAllDocs, bWait );
/*N*/       pGlobalProgress = pProgress;
/*N*/       nGlobalRange = nRange;
/*N*/       nGlobalPercent = 0;
/*N*/       bGlobalNoUserBreak = TRUE;
/*N*/   }
/*N*/ }


/*N*/ ScProgress::ScProgress() :
/*N*/       pProgress( NULL )
/*N*/ { // DummyInterpret
/*N*/ }


/*N*/ ScProgress::~ScProgress()
/*N*/ {
/*N*/   if ( pProgress )
/*N*/   {
/*N*/       delete pProgress;
/*N*/       pGlobalProgress = NULL;
/*N*/       nGlobalRange = 0;
/*N*/       nGlobalPercent = 0;
/*N*/       bGlobalNoUserBreak = TRUE;
/*N*/   }
/*N*/ }


// static

//STRIP001 void ScProgress::SetAllowInterpret( BOOL bAllow )
//STRIP001 {    // Grundzustand: Allow, Dummy gesetzt, pOld==NULL
//STRIP001  if ( !bAllow && bAllowInterpretProgress )
//STRIP001  {   // vorherigen/Dummy merken und Dummy setzen
//STRIP001      pOldInterpretProgress = pInterpretProgress;
//STRIP001      pInterpretProgress = &theDummyInterpretProgress;
//STRIP001      bAllowInterpretProgress = FALSE;
//STRIP001  }
//STRIP001  else if ( bAllow && !bAllowInterpretProgress )
//STRIP001  {   // Dummy weg und vorherigen/Dummy setzen
//STRIP001      pInterpretProgress = pOldInterpretProgress;
//STRIP001      pOldInterpretProgress = NULL;
//STRIP001      bAllowInterpretProgress = TRUE;
//STRIP001  }
//STRIP001 }


// static

//STRIP001 void ScProgress::CreateInterpretProgress( ScDocument* pDoc, BOOL bWait )
//STRIP001 {
//STRIP001  if ( bAllowInterpretProgress )
//STRIP001  {
//STRIP001      if ( nInterpretProgress )
//STRIP001          nInterpretProgress++;
//STRIP001      else if ( pDoc->GetAutoCalc() )
//STRIP001      {
//STRIP001          nInterpretProgress = 1;
//STRIP001          bIdleWasDisabled = pDoc->IsIdleDisabled();
//STRIP001          pDoc->DisableIdle( TRUE );
//STRIP001             // Interpreter may be called in many circumstances, also if another
//STRIP001             // progress bar is active, for example while adapting row heights.
//STRIP001             // Keep the dummy interpret progress.
//STRIP001             if ( !pGlobalProgress )
//STRIP001                 pInterpretProgress = new ScProgress( pDoc->GetDocumentShell(),
//STRIP001                     ScGlobal::GetRscString( STR_PROGRESS_CALCULATING ),
//STRIP001                     pDoc->GetFormulaCodeInTree(), FALSE, bWait );
//STRIP001          pInterpretDoc = pDoc;
//STRIP001      }
//STRIP001  }
//STRIP001 }


// static

//STRIP001 void ScProgress::DeleteInterpretProgress()
//STRIP001 {
//STRIP001  if ( bAllowInterpretProgress && nInterpretProgress )
//STRIP001  {
//STRIP001      if ( --nInterpretProgress == 0 )
//STRIP001      {
//STRIP001          if ( pInterpretProgress != &theDummyInterpretProgress )
//STRIP001          {
//STRIP001              delete pInterpretProgress;
//STRIP001              pInterpretProgress = &theDummyInterpretProgress;
//STRIP001          }
//STRIP001             if ( pInterpretDoc )
//STRIP001                 pInterpretDoc->DisableIdle( bIdleWasDisabled );
//STRIP001      }
//STRIP001  }
//STRIP001 }



}
