/*************************************************************************
 *
 *  $RCSfile: sd_sdoutl.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 14:18:29 $
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

// auto strip #ifndef _SV_WRKWIN_HXX
// auto strip #include <vcl/wrkwin.hxx>
// auto strip #endif
#ifndef _EEITEMID_HXX //autogen
#include <bf_svx/eeitemid.hxx>
#endif

#ifndef _EEITEM_HXX //autogen
#include <bf_svx/eeitem.hxx>
#endif

// auto strip #ifndef _SVX_FONTITEM_HXX //autogen
// auto strip #include <bf_svx/fontitem.hxx>
// auto strip #endif
// auto strip #ifndef _SVX_FHGTITEM_HXX //autogen
// auto strip #include <bf_svx/fhgtitem.hxx>
// auto strip #endif
#ifdef ITEMID_SEARCH
#undef ITEMID_SEARCH
#endif
#define ITEMID_SEARCH           SID_SEARCH_ITEM
#ifndef _SVXIDS_HRC
#include <bf_svx/svxids.hrc>
#endif
// auto strip #ifndef _SRCHITEM_HXX
// auto strip #include <bf_svx/srchitem.hxx>
// auto strip #endif
// auto strip #ifndef _OSPLCFG_HXX
// auto strip #include <bf_offmgr/osplcfg.hxx>
// auto strip #endif
// auto strip #ifndef _SVX_COLRITEM_HXX //autogen
// auto strip #include <bf_svx/colritem.hxx>
// auto strip #endif
#ifndef _EEITEM_HXX //autogen
#include <bf_svx/eeitem.hxx>
#endif
#ifndef _EDITSTAT_HXX //autogen
#include <bf_svx/editstat.hxx>
#endif
// auto strip #ifndef _SV_OUTDEV_HXX //autogen
// auto strip #include <vcl/outdev.hxx>
// auto strip #endif
// auto strip #ifndef _DLGUTIL_HXX
// auto strip #include <bf_svx/dlgutil.hxx>
// auto strip #endif
// auto strip #ifndef _XTABLE_HXX
// auto strip #include <bf_svx/xtable.hxx>
// auto strip #endif
// auto strip #ifndef _SV_MSGBOX_HXX //autogen
// auto strip #include <vcl/msgbox.hxx>
// auto strip #endif
// auto strip #ifndef _SFXDISPATCH_HXX //autogen
// auto strip #include <bf_sfx2/dispatch.hxx>
// auto strip #endif
// auto strip #ifndef _SFX_PRINTER_HXX //autogen
// auto strip #include <bf_sfx2/printer.hxx>
// auto strip #endif
// auto strip #ifndef _SVXERR_HXX //autogen
// auto strip #include <bf_svx/svxerr.hxx>
// auto strip #endif
// auto strip #ifndef _SVDOTEXT_HXX //autogen
// auto strip #include <bf_svx/svdotext.hxx>
// auto strip #endif
#ifndef _UNO_LINGU_HXX
#include <bf_svx/unolingu.hxx>
#endif
// auto strip #ifndef _OFFAPP_HXX //autogen
// auto strip #include <bf_offmgr/app.hxx>
// auto strip #endif
// auto strip #ifndef _SVDITER_HXX //autogen
// auto strip #include <bf_svx/svditer.hxx>
// auto strip #endif
// auto strip #include <comphelper/extract.hxx>
// auto strip #ifndef _COM_SUN_STAR_LINGUISTIC2_XSPELLCHECKER1_HPP_
// auto strip #include <com/sun/star/linguistic2/XSpellChecker1.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
// auto strip #include <com/sun/star/beans/XPropertySet.hpp>
// auto strip #endif
// auto strip #ifndef _COMPHELPER_PROCESSFACTORY_HXX_
// auto strip #include <comphelper/processfactory.hxx>
// auto strip #endif
#ifndef _EEITEM_HXX
#include <bf_svx/eeitem.hxx>
#endif
#ifndef _FORBIDDENCHARACTERSTABLE_HXX
#include <bf_svx/forbiddencharacterstable.hxx>
#endif
// auto strip #ifndef _SVX_SRCHDLG_HXX
// auto strip #include <bf_svx/srchdlg.hxx>
// auto strip #endif
#ifndef _SVTOOLS_LINGUPROPS_HXX_
#include <svtools/linguprops.hxx>
#endif
#ifndef _SVTOOLS_LINGUCFG_HXX_
#include <svtools/lingucfg.hxx>
#endif
// auto strip #ifndef _MyEDITENG_HXX
// auto strip #include <bf_svx/editeng.hxx>
// auto strip #endif

#include "strings.hrc"
#include "sdstring.hrc"
// auto strip #include "eetext.hxx"
// auto strip #include "sdpage.hxx"
// auto strip #include "app.hxx"
#include "sdoutl.hxx"
// auto strip #include "sdwindow.hxx"
// auto strip #include "sdresid.hxx"
// auto strip #include "drviewsh.hxx"
// auto strip #include "outlnvsh.hxx"
#include "drawdoc.hxx"
#include "docshell.hxx"
// auto strip #include "frmview.hxx"
// auto strip #include "optsitem.hxx"
#include "drawview.hxx"
namespace binfilter {

using namespace ::rtl;
using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::linguistic2;

} class SfxStyleSheetPool; namespace binfilter {//STRIP009



/*************************************************************************
|*
|* Ctor
|*
\************************************************************************/

/*N*/ SdOutliner::SdOutliner( SdDrawDocument* pDoc, USHORT nMode )
/*N*/     : SdrOutliner( &pDoc->GetItemPool(), nMode ),
/*N*/   mpDrawDocument(pDoc),
/*N*/     mbOwnOutlineView(false),
/*N*/   mpOutlineView(NULL),
/*N*/   mpViewShell(NULL),
/*N*/   mpView(NULL),
/*N*/   mbStringFound(FALSE),
/*N*/   mbEndOfSearch(FALSE),
/*N*/     mbFoundObject(FALSE),
/*N*/   mbError(FALSE),
/*N*/     mbDirectionIsForward(true),
/*N*/     mbRestrictSearchToSelection(false),
/*N*/     mpObj(NULL),
/*N*/   mpTextObj(NULL),
/*N*/     mpParaObj(NULL),
/*N*/     mpSearchItem(NULL)
/*N*/ {
/*N*/   SetStyleSheetPool((SfxStyleSheetPool*) mpDrawDocument->GetStyleSheetPool());
/*N*/   SetEditTextObjectPool( &pDoc->GetItemPool() );
/*N*/   SetCalcFieldValueHdl(LINK(SD_MOD(), SdModule, CalcFieldValueHdl));
/*N*/   SetForbiddenCharsTable( pDoc->GetForbiddenCharsTable() );
/*N*/
/*N*/   ULONG nCntrl = GetControlWord();
/*N*/   nCntrl |= EE_CNTRL_ALLOWBIGOBJS;
/*N*/   nCntrl |= EE_CNTRL_URLSFXEXECUTE;
/*N*/   nCntrl |= EE_CNTRL_MARKFIELDS;
/*N*/   nCntrl |= EE_CNTRL_AUTOCORRECT;
/*N*/
/*N*/   BOOL bHideSpell = TRUE;
/*N*/   BOOL bOnlineSpell = FALSE;
/*N*/
/*N*/   SdDrawDocShell* pDocSh = mpDrawDocument->GetDocSh();
/*N*/
/*N*/   if (pDocSh)
/*N*/   {
/*N*/       bHideSpell = mpDrawDocument->GetHideSpell();
/*N*/       bOnlineSpell = mpDrawDocument->GetOnlineSpell();
/*N*/   }
/*N*/   else
/*N*/   {
/*?*/       bHideSpell = sal_True;
/*?*/       bOnlineSpell = sal_False;
/*?*/
/*?*/       try
/*?*/       {
/*?*/             const SvtLinguConfig    aLinguConfig;
/*?*/             Any                     aAny;
/*?*/
/*?*/           aAny = aLinguConfig.GetProperty( ::rtl::OUString::createFromAscii( UPN_IS_SPELL_HIDE ) );
/*?*/           aAny >>= bHideSpell;
/*?*/
/*?*/           aAny = aLinguConfig.GetProperty( ::rtl::OUString::createFromAscii( UPN_IS_SPELL_AUTO ) );
/*?*/           aAny >>= bOnlineSpell;
/*?*/       }
/*?*/       catch( ... )
/*?*/       {
/*?*/           DBG_ERROR( "Ill. type in linguistic property" );
/*?*/       }
/*N*/   }
/*N*/
/*N*/   if (bHideSpell)
/*N*/       nCntrl |= EE_CNTRL_NOREDLINES;  else
/*N*/       nCntrl &= ~EE_CNTRL_NOREDLINES;
/*N*/
/*N*/   if (bOnlineSpell)
/*N*/       nCntrl |= EE_CNTRL_ONLINESPELLING;
/*N*/   else
/*N*/       nCntrl &= ~EE_CNTRL_ONLINESPELLING;
/*N*/
/*N*/   SetControlWord(nCntrl);
/*N*/
/*N*/   Reference< XSpellChecker1 > xSpellChecker( LinguMgr::GetSpellChecker() );
/*N*/   if ( xSpellChecker.is() )
/*N*/       SetSpeller( xSpellChecker );
/*N*/
/*N*/   Reference< XHyphenator > xHyphenator( LinguMgr::GetHyphenator() );
/*N*/   if( xHyphenator.is() )
/*N*/       SetHyphenator( xHyphenator );
/*N*/
/*N*/   SetDefaultLanguage( Application::GetSettings().GetLanguage() );
/*N*/ }




/// Nothing spectecular in the destructor.
/*N*/ SdOutliner::~SdOutliner (void)
/*N*/ {}




/** Prepare find&replace or spellchecking.  This distinguishes between three
    cases:
    <ol>
    <li>The current shell is a <type>SdDrawViewShell</type>: Create a
    <type>OutlinerView</type> object and search all objects of (i) the
    current mark list, (ii) of the current view, or (iii) of all the view
    combinations:
    <ol>
    <li>Draw view, slide view</li>
    <li>Draw view, background view</li>
    <li>Notes view, slide view</li>
    <li>Notes view, background view</li>
    <li>Handout view, slide view</li>
    <li>Handout view, background view</li>
    </ol>

    <li>When the current shell is a <type>SdOutlineViewShell</type> then
    directly operate on it.  No switching into other views takes place.</li>

    <li>For a <type>SdSlideViewShell</type> no action is performed.</li>
    </ol>
*/
//STRIP001 void SdOutliner::PrepareSpelling (void)
//STRIP001 {
//STRIP001  SetRefDevice( SD_MOD()->GetRefDevice( *mpDrawDocument->GetDocSh() ) );
//STRIP001
//STRIP001     SetViewShell (PTR_CAST(SdViewShell, SfxViewShell::Current()));
//STRIP001
//STRIP001  if (mpViewShell != NULL)
//STRIP001  {
//STRIP001      mbStringFound = FALSE;
//STRIP001
//STRIP001         // Supposed that we are not located at the very beginning/end of the
//STRIP001         // document then there may be a match in the document prior/after
//STRIP001         // the current position.
//STRIP001         mbMatchMayExist = TRUE;
//STRIP001
//STRIP001         maObjectIterator = ::sd::outliner::Iterator();
//STRIP001         maSearchStartPosition = ::sd::outliner::Iterator();
//STRIP001      RememberStartPosition();
//STRIP001
//STRIP001      if ( mpViewShell->ISA(SdDrawViewShell) )
//STRIP001      {
//STRIP001             // Create a new outline view to do the search on.
//STRIP001          mpOutlineView = new OutlinerView( this, mpWindow );
//STRIP001             mbOwnOutlineView = true;
//STRIP001          ULONG nStat = mpOutlineView->GetControlWord();
//STRIP001          nStat &= ~EV_CNTRL_AUTOSCROLL;
//STRIP001          mpOutlineView->SetControlWord(nStat);
//STRIP001          InsertView( mpOutlineView );
//STRIP001          SetUpdateMode(FALSE);
//STRIP001          mpOutlineView->SetOutputArea( Rectangle( Point(), Size(1, 1) ) );
//STRIP001          SetPaperSize( Size(1, 1) );
//STRIP001          SetText( String(), GetParagraph( 0 ) );
//STRIP001
//STRIP001             meOriginalEditMode = ((SdDrawViewShell*) mpViewShell)->GetEditMode();
//STRIP001      }
//STRIP001      else if ( mpViewShell->ISA(SdOutlineViewShell) )
//STRIP001      {
//STRIP001          mpOutlineView = GetView(0);
//STRIP001             mbOwnOutlineView = false;
//STRIP001      }
//STRIP001         // else do nothing.
//STRIP001
//STRIP001         HandleChangedSelection ();
//STRIP001  }
//STRIP001     ClearModifyFlag();
//STRIP001 }




/*************************************************************************
|*
|* Spelling: Pruefung starten
|*
\************************************************************************/

//STRIP001 void SdOutliner::StartSpelling (void)
//STRIP001 {
//STRIP001  BOOL bMultiDoc = FALSE;
//STRIP001     meMode = SPELL;
//STRIP001     mbDirectionIsForward = true;
//STRIP001     mpSearchItem = NULL;
//STRIP001
//STRIP001     //    InitPage (mnStartPageIndex);
//STRIP001
//STRIP001  if ( mpViewShell->ISA(SdDrawViewShell) )
//STRIP001      bMultiDoc = TRUE;
//STRIP001
//STRIP001  EESpellState eState = mpOutlineView->StartSpeller( bMultiDoc );
//STRIP001
//STRIP001  if (bMultiDoc)
//STRIP001  {
//STRIP001      ESelection aSelection;
//STRIP001      mpOutlineView->SetSelection(aSelection);
//STRIP001         mpView->UnmarkAllObj (mpView->GetPageViewPvNum(0));
//STRIP001      mpView->EndTextEdit();
//STRIP001  }
//STRIP001
//STRIP001     // Restore the start position before displaying a dialog.
//STRIP001     RestoreStartPosition ();
//STRIP001
//STRIP001  if (eState == EE_SPELL_NOLANGUAGE)
//STRIP001  {
//STRIP001         Window* pParent=GetParentForDialog();
//STRIP001      ErrorBox (pParent,
//STRIP001             WB_OK,
//STRIP001             String(SdResId(STR_NOLANGUAGE))).Execute();
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001         Window* pParent=GetParentForDialog();
//STRIP001      if (mpView->HasMarkedObj())
//STRIP001      {
//STRIP001          InfoBox(pParent,
//STRIP001                 String(SdResId(STR_END_SPELLING_OBJ))).Execute();
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          InfoBox(pParent,
//STRIP001                 String(SdResId(STR_END_SPELLING))).Execute();
//STRIP001      }
//STRIP001  }
//STRIP001 }




/** Free all resources acquired during the search/spell check.  After a
    spell check the start position is restored here.
*/
//STRIP001 void SdOutliner::EndSpelling (void)
//STRIP001 {
//STRIP001     mpViewShell = PTR_CAST( SdViewShell, SfxViewShell::Current() );
//STRIP001
//STRIP001     // When in <member>PrepareSpelling()</member> a new outline view has been
//STRIP001     // created then delete it here.
//STRIP001  sal_Bool bViewIsDrawViewShell(mpViewShell && mpViewShell->ISA(SdDrawViewShell));
//STRIP001  if ( bViewIsDrawViewShell )
//STRIP001  {
//STRIP001         SetStatusEventHdl(Link());
//STRIP001      mpView = mpViewShell->GetView();
//STRIP001         mpView->UnmarkAllObj (mpView->GetPageViewPvNum(0));
//STRIP001      mpView->EndTextEdit();
//STRIP001         // Make FuSelection the current function.
//STRIP001         mpViewShell->GetViewFrame()->GetDispatcher()->
//STRIP001             Execute(SID_OBJECT_SELECT, SFX_CALLMODE_SYNCHRON |
//STRIP001                 SFX_CALLMODE_RECORD);
//STRIP001
//STRIP001         // Remove and, if previously created by us, delete the outline view.
//STRIP001         RemoveView( mpOutlineView );
//STRIP001         if (mbOwnOutlineView)
//STRIP001             delete mpOutlineView;
//STRIP001
//STRIP001      SetUpdateMode(TRUE);
//STRIP001  }
//STRIP001
//STRIP001  // #95811# Before clearing the modify flag use it as a hint that
//STRIP001  // changes were done at SpellCheck
//STRIP001  if(IsModified())
//STRIP001  {
//STRIP001      if(mpView && mpView->ISA(SdOutlineView))
//STRIP001          ((SdOutlineView*)mpView)->PrepareClose(FALSE);
//STRIP001      if(mpDrawDocument && !mpDrawDocument->IsChanged())
//STRIP001          mpDrawDocument->SetChanged(TRUE);
//STRIP001  }
//STRIP001
//STRIP001  // #95811# now clear the modify flag to have a specified state of SdOutliner
//STRIP001  ClearModifyFlag();
//STRIP001
//STRIP001     // When spell checking then restore the start position.
//STRIP001     if (meMode == SPELL)
//STRIP001         RestoreStartPosition ();
//STRIP001
//STRIP001     mpViewShell = NULL;
//STRIP001     mpView = NULL;
//STRIP001     mpWindow = NULL;
//STRIP001     mpOutlineView = NULL;
//STRIP001 }




/*************************************************************************
|*
|* Spelling: naechstes TextObjekt pruefen
|*
\************************************************************************/

//STRIP001 BOOL SdOutliner::SpellNextDocument (void)
//STRIP001 {
//STRIP001  mpDrawDocument->GetDocSh()->SetWaitCursor( TRUE );
//STRIP001
//STRIP001     // Extract the search direction.
//STRIP001     BOOL bBackwards = FALSE;
//STRIP001  Reference<beans::XPropertySet>  xProperties (SvxGetLinguPropertySet());
//STRIP001  if (xProperties.is())
//STRIP001  {
//STRIP001      Any aValue = xProperties->getPropertyValue(OUString(
//STRIP001             RTL_CONSTASCII_USTRINGPARAM(UPN_IS_WRAP_REVERSE)));
//STRIP001      aValue >>= bBackwards;
//STRIP001  }
//STRIP001
//STRIP001     Initialize ( ! bBackwards);
//STRIP001
//STRIP001     mpWindow = mpViewShell->GetActiveWindow();
//STRIP001     mpOutlineView->SetWindow(mpWindow);
//STRIP001     ProvideNextTextObject ();
//STRIP001
//STRIP001  mpDrawDocument->GetDocSh()->SetWaitCursor( FALSE );
//STRIP001  ClearModifyFlag();
//STRIP001
//STRIP001  return !mbEndOfSearch;
//STRIP001 }




/** Go to next match.
*/
//STRIP001 BOOL SdOutliner::StartSearchAndReplace (const SvxSearchItem* pSearchItem)
//STRIP001 {
//STRIP001  mpDrawDocument->GetDocSh()->SetWaitCursor( TRUE );
//STRIP001     SetViewShell (PTR_CAST( SdViewShell, SfxViewShell::Current()));
//STRIP001
//STRIP001     meMode = SEARCH;
//STRIP001     mpSearchItem = pSearchItem;
//STRIP001
//STRIP001  mbFoundObject = FALSE;
//STRIP001
//STRIP001     Initialize ( ! mpSearchItem->GetBackward());
//STRIP001
//STRIP001     USHORT nCommand = mpSearchItem->GetCommand();
//STRIP001     BOOL bEndOfSearch;
//STRIP001     if (nCommand == SVX_SEARCHCMD_REPLACE_ALL)
//STRIP001         bEndOfSearch = SearchAndReplaceAll ();
//STRIP001     else
//STRIP001     {
//STRIP001         RememberStartPosition ();
//STRIP001         bEndOfSearch = SearchAndReplaceOnce ();
//STRIP001         //#107233# restore start position if nothing was found
//STRIP001         if(!mbStringFound)
//STRIP001             RestoreStartPosition ();
//STRIP001         else
//STRIP001             mnStartPageIndex = -1;
//STRIP001     }
//STRIP001     return bEndOfSearch;
//STRIP001 }




//STRIP001 void SdOutliner::Initialize (bool bDirectionIsForward)
//STRIP001 {
//STRIP001     bool bOldDirectionIsForward = mbDirectionIsForward;
//STRIP001     mbDirectionIsForward = bDirectionIsForward;
//STRIP001
//STRIP001     if (maObjectIterator == ::sd::outliner::Iterator())
//STRIP001     {
//STRIP001         // Initialize a new search.
//STRIP001         maObjectIterator = ::sd::outliner::OutlinerContainer(this).current();
//STRIP001         maCurrentPosition = *maObjectIterator;
//STRIP001
//STRIP001         // In case we are searching in an outline view then first remove the
//STRIP001         // current selection and place cursor at its start or end.
//STRIP001      if (mpViewShell->ISA(SdOutlineViewShell))
//STRIP001         {
//STRIP001             ESelection aSelection = mpOutlineView->GetSelection ();
//STRIP001             if (mbDirectionIsForward)
//STRIP001             {
//STRIP001                 aSelection.nEndPara = aSelection.nStartPara;
//STRIP001                 aSelection.nEndPos = aSelection.nStartPos;
//STRIP001             }
//STRIP001             else
//STRIP001             {
//STRIP001                 aSelection.nStartPara = aSelection.nEndPara;
//STRIP001                 aSelection.nStartPos = aSelection.nEndPos;
//STRIP001             }
//STRIP001             mpOutlineView->SetSelection (aSelection);
//STRIP001         }
//STRIP001
//STRIP001         // When not beginning the search at the beginning of the search area
//STRIP001         // then there may be matches before the current position.
//STRIP001         mbMatchMayExist = (maObjectIterator!=::sd::outliner::OutlinerContainer(this).begin());
//STRIP001     }
//STRIP001     else if (bOldDirectionIsForward != mbDirectionIsForward)
//STRIP001     {
//STRIP001         // Requested iteration direction has changed.  Turn arround the iterator.
//STRIP001         maObjectIterator.Reverse();
//STRIP001         // The iterator has pointed to the object one ahead/before the current
//STRIP001         // one.  Now move it to the one before/ahead the current one.
//STRIP001         ++maObjectIterator;
//STRIP001         ++maObjectIterator;
//STRIP001
//STRIP001         mbMatchMayExist = true;
//STRIP001     }
//STRIP001 }




//STRIP001 BOOL SdOutliner::SearchAndReplaceAll (void)
//STRIP001 {
//STRIP001     // Save the current position to be restored after having replaced all
//STRIP001     // matches.
//STRIP001     RememberStartPosition ();
//STRIP001
//STRIP001     if (mpViewShell->ISA(SdOutlineViewShell))
//STRIP001     {
//STRIP001         // Put the cursor to the beginning/end of the outliner.
//STRIP001         mpOutlineView->SetSelection (GetSearchStartPosition ());
//STRIP001
//STRIP001         // The outliner does all the work for us when we are in this mode.
//STRIP001         SearchAndReplaceOnce();
//STRIP001     }
//STRIP001     else if (mpViewShell->ISA(SdDrawViewShell))
//STRIP001     {
//STRIP001         // Go to beginning/end of document.
//STRIP001         maObjectIterator = ::sd::outliner::OutlinerContainer(this).begin();
//STRIP001         // Switch to the current object only if it is a valid text object.
//STRIP001         ::sd::outliner::IteratorPosition aNewPosition (*maObjectIterator);
//STRIP001         if (IsValidTextObject (aNewPosition))
//STRIP001         {
//STRIP001             maCurrentPosition = aNewPosition;
//STRIP001             SetObject (maCurrentPosition);
//STRIP001         }
//STRIP001
//STRIP001         // Search/replace until the end of the document is reached.
//STRIP001         bool bFoundMatch;
//STRIP001         do
//STRIP001         {
//STRIP001             bFoundMatch = ! SearchAndReplaceOnce();
//STRIP001         }
//STRIP001         while (bFoundMatch);
//STRIP001     }
//STRIP001
//STRIP001     RestoreStartPosition ();
//STRIP001
//STRIP001     return TRUE;
//STRIP001 }




//STRIP001 BOOL SdOutliner::SearchAndReplaceOnce (void)
//STRIP001 {
//STRIP001     DetectChange ();
//STRIP001
//STRIP001  DBG_ASSERT( mpOutlineView && GetEditEngine().HasView( &mpOutlineView->GetEditView() ), "SearchAndReplace without valid view!" );
//STRIP001
//STRIP001  if( NULL == mpOutlineView || !GetEditEngine().HasView( &mpOutlineView->GetEditView() ) )
//STRIP001      return true;
//STRIP001
//STRIP001  if (mpViewShell != NULL)
//STRIP001  {
//STRIP001      mpView = mpViewShell->GetView();
//STRIP001      mpWindow = mpViewShell->GetActiveWindow();
//STRIP001         DBG_ASSERT (mpOutlineView!=NULL, "SdOutliner::SearchAndReplaceOnce(): mpOutlineView!=NULL");
//STRIP001      mpOutlineView->SetWindow(mpWindow);
//STRIP001
//STRIP001      if ( mpViewShell->ISA(SdDrawViewShell) )
//STRIP001      {
//STRIP001             // When replacing we first check if there is a selection
//STRIP001             // indicating a match.  If there is then replace it.  The
//STRIP001             // following call to StartSearchAndReplace will then search for
//STRIP001             // the next match.
//STRIP001             if (meMode == SEARCH
//STRIP001                 && mpSearchItem->GetCommand() == SVX_SEARCHCMD_REPLACE)
//STRIP001                 if (mpOutlineView != NULL)
//STRIP001                     if (mpOutlineView->GetSelection().HasRange())
//STRIP001                         mpOutlineView->StartSearchAndReplace(*mpSearchItem);
//STRIP001
//STRIP001             // Search for the next match.
//STRIP001             ULONG nMatchCount = 0;
//STRIP001             if (mpSearchItem->GetCommand() != SVX_SEARCHCMD_REPLACE_ALL)
//STRIP001                 nMatchCount = mpOutlineView->StartSearchAndReplace(*mpSearchItem);
//STRIP001
//STRIP001             // Go to the next text object when there have been no matches in
//STRIP001             // the current object or the whole object has already been
//STRIP001             // processed.
//STRIP001             if (nMatchCount==0 || mpSearchItem->GetCommand()==SVX_SEARCHCMD_REPLACE_ALL)
//STRIP001             {
//STRIP001                 ProvideNextTextObject ();
//STRIP001
//STRIP001                 if ( ! mbEndOfSearch)
//STRIP001                 {
//STRIP001                     // Now that the mbEndOfSearch flag guards this block the
//STRIP001                     // following assertion and return should not be
//STRIP001                     // necessary anymore.
//STRIP001                     DBG_ASSERT( mpOutlineView && GetEditEngine().HasView(
//STRIP001                         &mpOutlineView->GetEditView() ), "SearchAndReplace without valid view!" );
//STRIP001                     if( NULL == mpOutlineView
//STRIP001                         || !GetEditEngine().HasView( &mpOutlineView->GetEditView() ) )
//STRIP001                     {
//STRIP001                         mpDrawDocument->GetDocSh()->SetWaitCursor( FALSE );
//STRIP001                         return true;
//STRIP001                     }
//STRIP001
//STRIP001                     if (meMode == SEARCH)
//STRIP001                         nMatchCount = mpOutlineView->StartSearchAndReplace(*mpSearchItem);
//STRIP001                 }
//STRIP001             }
//STRIP001      }
//STRIP001      else if ( mpViewShell->ISA(SdOutlineViewShell) )
//STRIP001      {
//STRIP001             mpDrawDocument->GetDocSh()->SetWaitCursor (FALSE);
//STRIP001             // The following loop is executed more then once only when a
//STRIP001             // wrap arround search is done.
//STRIP001             while (true)
//STRIP001             {
//STRIP001                 int nResult = mpOutlineView->StartSearchAndReplace(*mpSearchItem);
//STRIP001                 if (nResult == 0)
//STRIP001                 {
//STRIP001                     if (HandleFailedSearch ())
//STRIP001                         if (mpOutlineView != NULL)
//STRIP001                         {
//STRIP001                             mpOutlineView->SetSelection (GetSearchStartPosition ());
//STRIP001                             continue;
//STRIP001                         }
//STRIP001                 }
//STRIP001                 else
//STRIP001                     mbStringFound = true;
//STRIP001                 break;
//STRIP001             }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  mpDrawDocument->GetDocSh()->SetWaitCursor( FALSE );
//STRIP001
//STRIP001  return mbEndOfSearch;
//STRIP001 }




/** Try to detect whether the document or the view (shell) has changed since
    the last time <member>StartSearchAndReplace()</member> has been called.
*/
//STRIP001 void SdOutliner::DetectChange (void)
//STRIP001 {
//STRIP001     ::sd::outliner::IteratorPosition aPosition (maCurrentPosition);
//STRIP001
//STRIP001     SdDrawViewShell* pDrawViewShell = NULL;
//STRIP001     if (mpViewShell->ISA(SdDrawViewShell))
//STRIP001         pDrawViewShell = static_cast<SdDrawViewShell*>(mpViewShell);
//STRIP001
//STRIP001     // Detect whether the view has been switched from the outside.
//STRIP001     if (pDrawViewShell != NULL
//STRIP001         && (aPosition.meEditMode != pDrawViewShell->GetEditMode()
//STRIP001             || aPosition.mePageKind != pDrawViewShell->GetPageKind()))
//STRIP001     {
//STRIP001         // Either the edit mode or the page kind has changed.
//STRIP001         SetStatusEventHdl(Link());
//STRIP001
//STRIP001         SdrPageView* pPageView = mpView->GetPageViewPvNum(0);
//STRIP001         if (pPageView != NULL)
//STRIP001             mpView->UnmarkAllObj (pPageView);
//STRIP001         mpView->EndTextEdit();
//STRIP001         SetUpdateMode(FALSE);
//STRIP001         mpOutlineView->SetOutputArea( Rectangle( Point(), Size(1, 1) ) );
//STRIP001         if (meMode == SPELL)
//STRIP001             SetPaperSize( Size(1, 1) );
//STRIP001         SetText( String(), GetParagraph( 0 ) );
//STRIP001
//STRIP001         RememberStartPosition ();
//STRIP001
//STRIP001         mnPageCount = mpDrawDocument->GetSdPageCount(pDrawViewShell->GetPageKind());
//STRIP001         maObjectIterator = ::sd::outliner::OutlinerContainer(this).current();
//STRIP001     }
//STRIP001
//STRIP001     // Detect change of the set of selected objects.  If their number has
//STRIP001     // changed start again with the first selected object.
//STRIP001     else if (DetectSelectionChange())
//STRIP001  {
//STRIP001         HandleChangedSelection ();
//STRIP001         maObjectIterator = ::sd::outliner::OutlinerContainer(this).current();
//STRIP001  }
//STRIP001
//STRIP001     // Detect change of page count.  Restart search at first/last page in
//STRIP001     // that case.
//STRIP001  else if (aPosition.meEditMode == EM_PAGE
//STRIP001         && mpDrawDocument->GetSdPageCount(aPosition.mePageKind) != mnPageCount)
//STRIP001     {
//STRIP001         // The number of pages has changed.
//STRIP001         mnPageCount = mpDrawDocument->GetSdPageCount(aPosition.mePageKind);
//STRIP001         maObjectIterator = ::sd::outliner::OutlinerContainer(this).current();
//STRIP001     }
//STRIP001     else if (aPosition.meEditMode == EM_MASTERPAGE
//STRIP001         && mpDrawDocument->GetSdPageCount(aPosition.mePageKind) != mnPageCount)
//STRIP001  {
//STRIP001         // The number of master pages has changed.
//STRIP001         mnPageCount = mpDrawDocument->GetSdPageCount(aPosition.mePageKind);
//STRIP001         maObjectIterator = ::sd::outliner::OutlinerContainer(this).current();
//STRIP001  }
//STRIP001 }




//STRIP001 bool SdOutliner::DetectSelectionChange (void)
//STRIP001 {
//STRIP001     bool bSelectionHasChanged = false;
//STRIP001     ULONG nMarkCount = mpView->GetMarkList().GetMarkCount();
//STRIP001
//STRIP001     // If mpObj is NULL then we have not yet found our first match.
//STRIP001     // Detecting a change makes no sense.
//STRIP001     if (mpObj != NULL)
//STRIP001         switch (nMarkCount)
//STRIP001         {
//STRIP001             case 0:
//STRIP001                 // The selection has changed when previously there have been
//STRIP001                 // selected objects.
//STRIP001                 bSelectionHasChanged = mbRestrictSearchToSelection;
//STRIP001                 break;
//STRIP001             case 1:
//STRIP001                 // Check if the only selected object is not the one that we
//STRIP001                 // had selected.
//STRIP001                 if (mpView != NULL)
//STRIP001                 {
//STRIP001                     SdrMark* pMark = mpView->GetMarkList().GetMark(0);
//STRIP001                     if (pMark != NULL)
//STRIP001                         bSelectionHasChanged = (mpObj != pMark->GetObj ());
//STRIP001                 }
//STRIP001                 break;
//STRIP001             default:
//STRIP001                 // We had selected exactly one object.
//STRIP001                 bSelectionHasChanged = true;
//STRIP001                 break;
//STRIP001         }
//STRIP001
//STRIP001     return bSelectionHasChanged;
//STRIP001 }




//STRIP001 void SdOutliner::RememberStartPosition (void)
//STRIP001 {
//STRIP001     if (mpViewShell->ISA(SdDrawViewShell))
//STRIP001     {
//STRIP001         SdDrawViewShell* pDrawViewShell = static_cast<SdDrawViewShell*>(mpViewShell);
//STRIP001         if (pDrawViewShell != NULL)
//STRIP001         {
//STRIP001             meStartViewMode = pDrawViewShell->GetPageKind();
//STRIP001             meStartEditMode = pDrawViewShell->GetEditMode();
//STRIP001             mnStartPageIndex = pDrawViewShell->GetCurPageId() - 1;
//STRIP001         }
//STRIP001
//STRIP001         if (mpView != NULL)
//STRIP001         {
//STRIP001             mpStartEditedObject = mpView->GetTextEditObject();
//STRIP001             if (mpStartEditedObject != NULL)
//STRIP001             {
//STRIP001                 // Try to retrieve current caret position only when there is an
//STRIP001                 // edited object.
//STRIP001                 Outliner* pOutliner = static_cast<SdDrawView*>(mpView)->GetTextEditOutliner();
//STRIP001                 if (pOutliner!=NULL && pOutliner->GetViewCount()>0)
//STRIP001                 {
//STRIP001                     OutlinerView* pOutlinerView = pOutliner->GetView(0);
//STRIP001                     maStartSelection = pOutlinerView->GetSelection();
//STRIP001                 }
//STRIP001             }
//STRIP001         }
//STRIP001     }
//STRIP001     else if (mpViewShell->ISA(SdOutlineViewShell))
//STRIP001     {
//STRIP001         // Remember the current cursor position.
//STRIP001         maStartSelection = GetView(0)->GetSelection();
//STRIP001     }
//STRIP001     else
//STRIP001     {
//STRIP001         mnStartPageIndex = -1;
//STRIP001     }
//STRIP001 }




//STRIP001 void SdOutliner::RestoreStartPosition (void)
//STRIP001 {
//STRIP001     // Take a negative start page index as inidicater that restoring the
//STRIP001     // start position is not requested.
//STRIP001     if (mnStartPageIndex < 0)
//STRIP001         return;
//STRIP001
//STRIP001     if (mpViewShell->ISA(SdDrawViewShell))
//STRIP001     {
//STRIP001         SdDrawViewShell* pDrawViewShell = static_cast<SdDrawViewShell*>(mpViewShell);
//STRIP001         SetViewMode (meStartViewMode);
//STRIP001         if (pDrawViewShell != NULL)
//STRIP001             SetPage (meStartEditMode, mnStartPageIndex);
//STRIP001
//STRIP001         if (mpStartEditedObject != NULL)
//STRIP001         {
//STRIP001             SdrPageView* pPageView = mpView->GetPageViewPvNum(0);
//STRIP001             mpView->BegTextEdit (mpStartEditedObject);
//STRIP001             Outliner* pOutliner = static_cast<SdDrawView*>(mpView)->GetTextEditOutliner();
//STRIP001             if (pOutliner!=NULL && pOutliner->GetViewCount()>0)
//STRIP001             {
//STRIP001                 OutlinerView* pOutlinerView = pOutliner->GetView(0);
//STRIP001                 pOutlinerView->SetSelection(maStartSelection);
//STRIP001             }
//STRIP001         }
//STRIP001     }
//STRIP001     else if (mpViewShell->ISA(SdOutlineViewShell))
//STRIP001     {
//STRIP001         // Set cursor to its old position.
//STRIP001         GetView(0)->SetSelection (maStartSelection);
//STRIP001     }
//STRIP001 }




/** The main purpose of this method is to iterate over all shape objects of
    the search area (current selection, current view, or whole document)
    until a text object has been found that contains at least one match or
    until no such object can be found anymore.   These two conditions are
    expressed by setting one of the flags <member>mbFoundObject</member> or
    <member>mbEndOfSearch</member> to <TRUE/>.
*/
//STRIP001 void SdOutliner::ProvideNextTextObject (void)
//STRIP001 {
//STRIP001  mbEndOfSearch = FALSE;
//STRIP001  mbFoundObject = FALSE;
//STRIP001
//STRIP001     mpView->UnmarkAllObj (mpView->GetPageViewPvNum(0));
//STRIP001     try
//STRIP001     {
//STRIP001      mpView->EndTextEdit();
//STRIP001     }
//STRIP001     catch (::com::sun::star::uno::Exception e)
//STRIP001     {
//STRIP001         OSL_TRACE ("caught exception while ending text edit mode");
//STRIP001     }
//STRIP001  SetUpdateMode(FALSE);
//STRIP001  mpOutlineView->SetOutputArea( Rectangle( Point(), Size(1, 1) ) );
//STRIP001     if (meMode == SPELL)
//STRIP001         SetPaperSize( Size(1, 1) );
//STRIP001  SetText( String(), GetParagraph( 0 ) );
//STRIP001
//STRIP001  mpTextObj = NULL;
//STRIP001
//STRIP001     // Iterate until a valid text object has been found or the search ends.
//STRIP001  do
//STRIP001  {
//STRIP001      mpObj = NULL;
//STRIP001      mpParaObj = NULL;
//STRIP001
//STRIP001         if (maObjectIterator != ::sd::outliner::OutlinerContainer(this).end())
//STRIP001         {
//STRIP001             maCurrentPosition = *maObjectIterator;
//STRIP001             // Switch to the current object only if it is a valid text object.
//STRIP001             if (IsValidTextObject (maCurrentPosition))
//STRIP001                 mpObj = SetObject (maCurrentPosition);
//STRIP001             ++maObjectIterator;
//STRIP001
//STRIP001             if (mpObj != NULL)
//STRIP001             {
//STRIP001                 PutTextIntoOutliner ();
//STRIP001
//STRIP001                 if (mpViewShell != NULL)
//STRIP001                     if (meMode == SEARCH)
//STRIP001                         PrepareSearchAndReplace ();
//STRIP001                     else
//STRIP001                         PrepareSpellCheck ();
//STRIP001             }
//STRIP001         }
//STRIP001         else
//STRIP001         {
//STRIP001             mbEndOfSearch = true;
//STRIP001             EndOfSearch ();
//STRIP001         }
//STRIP001  }
//STRIP001  while ( ! (mbFoundObject || mbEndOfSearch));
//STRIP001 }




//STRIP001 void SdOutliner::EndOfSearch (void)
//STRIP001 {
//STRIP001     if (mbRestrictSearchToSelection)
//STRIP001         ShowEndOfSearchDialog ();
//STRIP001     else
//STRIP001     {
//STRIP001         // When no match has been found so far then terminate the search.
//STRIP001         if ( ! mbMatchMayExist)
//STRIP001         {
//STRIP001             ShowEndOfSearchDialog ();
//STRIP001             mbEndOfSearch = TRUE;
//STRIP001         }
//STRIP001         // Ask the user whether to wrap arround and continue the search or
//STRIP001         // to terminate.
//STRIP001         else if (ShowWrapArroundDialog ())
//STRIP001         {
//STRIP001             mbMatchMayExist = false;
//STRIP001             maObjectIterator = ::sd::outliner::OutlinerContainer(this).begin();
//STRIP001             mbEndOfSearch = FALSE;
//STRIP001         }
//STRIP001         else
//STRIP001         {
//STRIP001             // No wrap arround.
//STRIP001             mbEndOfSearch = TRUE;
//STRIP001         }
//STRIP001     }
//STRIP001 }




//STRIP001 void SdOutliner::InitPage (USHORT nPageIndex)
//STRIP001 {
//STRIP001     ::sd::outliner::IteratorPosition aPosition (*maObjectIterator);
//STRIP001     if (aPosition.meEditMode == EM_PAGE)
//STRIP001         mnPageCount = mpDrawDocument->GetSdPageCount(aPosition.mePageKind);
//STRIP001     else
//STRIP001         mnPageCount = mpDrawDocument->GetMasterSdPageCount(aPosition.mePageKind);
//STRIP001 }




//STRIP001 void SdOutliner::ShowEndOfSearchDialog (void)
//STRIP001 {
//STRIP001     if (meMode == SEARCH)
//STRIP001     {
//STRIP001         String aString;
//STRIP001
//STRIP001         if (mbStringFound)
//STRIP001             aString = String( SdResId(STR_END_SEARCHING) );
//STRIP001         else
//STRIP001             aString = String( SdResId(STR_STRING_NOTFOUND) );
//STRIP001
//STRIP001         Window* pParent = GetParentForDialog();
//STRIP001         if (pParent != NULL)
//STRIP001             InfoBox (pParent, aString).Execute();
//STRIP001     }
//STRIP001 }




//STRIP001 bool SdOutliner::ShowWrapArroundDialog (void)
//STRIP001 {
//STRIP001     bool bDoWrapArround = false;
//STRIP001
//STRIP001     // Determine whether to show the dialog.
//STRIP001     bool bShowDialog = false;
//STRIP001     if (mpSearchItem != NULL)
//STRIP001     {
//STRIP001         // When searching display the dialog only for single find&replace.
//STRIP001         USHORT nCommand = mpSearchItem->GetCommand();
//STRIP001         bShowDialog = (nCommand==SVX_SEARCHCMD_REPLACE)
//STRIP001             || (nCommand==SVX_SEARCHCMD_FIND);
//STRIP001     }
//STRIP001     else
//STRIP001         // Spell checking needs the dialog, too.
//STRIP001         bShowDialog = (meMode == SPELL);
//STRIP001
//STRIP001     if (bShowDialog)
//STRIP001     {
//STRIP001         // The question text depends on the search direction.
//STRIP001         BOOL bImpress = mpDrawDocument && mpDrawDocument->GetDocumentType() == DOCUMENT_TYPE_IMPRESS;
//STRIP001         USHORT nStringId;
//STRIP001         if (mbDirectionIsForward)
//STRIP001             nStringId = bImpress ? STR_SAR_WRAP_FORWARD : STR_SAR_WRAP_FORWARD_DRAW;
//STRIP001         else
//STRIP001             nStringId = bImpress ? STR_SAR_WRAP_BACKWARD : STR_SAR_WRAP_BACKWARD_DRAW;
//STRIP001
//STRIP001         // Pop up question box that asks the user whether
//STRIP001         // to wrap arround.
//STRIP001         Window* pParent = GetParentForDialog();
//STRIP001         if (pParent != NULL)
//STRIP001         {
//STRIP001             QueryBox aQuestionBox (pParent,
//STRIP001                 WB_YES_NO | WB_DEF_YES,
//STRIP001                 String(SdResId(nStringId)));
//STRIP001             aQuestionBox.SetImage (QueryBox::GetStandardImage());
//STRIP001             USHORT nBoxResult = aQuestionBox.Execute();
//STRIP001             bDoWrapArround = (nBoxResult == BUTTONID_YES);
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001     return bDoWrapArround;
//STRIP001 }




//STRIP001 bool SdOutliner::IsValidTextObject (const ::sd::outliner::IteratorPosition& rPosition)
//STRIP001 {
//STRIP001     SdrObject* pObject = rPosition.mpObject;
//STRIP001     return pObject != NULL
//STRIP001         && pObject->ISA(SdrTextObj)
//STRIP001         && static_cast<SdrTextObj*>(pObject)->HasText()
//STRIP001         && ! pObject->IsEmptyPresObj();
//STRIP001 }




//STRIP001 void SdOutliner::PutTextIntoOutliner (void)
//STRIP001 {
//STRIP001     if ( mpObj && mpObj->ISA(SdrTextObj)
//STRIP001         && static_cast<SdrTextObj*>(mpObj)->HasText()
//STRIP001         && !mpObj->IsEmptyPresObj() )
//STRIP001     {
//STRIP001         mpTextObj = (SdrTextObj*) mpObj;
//STRIP001         mpParaObj = mpTextObj->GetOutlinerParaObject();
//STRIP001
//STRIP001         if (mpParaObj != NULL)
//STRIP001         {
//STRIP001             SetText(*mpParaObj);
//STRIP001
//STRIP001             ClearModifyFlag();
//STRIP001         }
//STRIP001     }
//STRIP001     else
//STRIP001     {
//STRIP001         mpTextObj = NULL;
//STRIP001     }
//STRIP001 }




//STRIP001 void SdOutliner::PrepareSpellCheck (void)
//STRIP001 {
//STRIP001     EESpellState eState = HasSpellErrors();
//STRIP001     DBG_ASSERT(eState != EE_SPELL_NOSPELLER, "No SpellChecker");
//STRIP001
//STRIP001     if (eState == EE_SPELL_NOLANGUAGE)
//STRIP001     {
//STRIP001         mbError = TRUE;
//STRIP001         mbEndOfSearch = TRUE;
//STRIP001         Window* pParent=GetParentForDialog();
//STRIP001         ErrorBox (pParent,
//STRIP001             WB_OK,
//STRIP001             String(SdResId(STR_NOLANGUAGE))).Execute();
//STRIP001     }
//STRIP001     else if (eState != EE_SPELL_OK)
//STRIP001     {
//STRIP001         // When spell checking we have to test whether we have processed the
//STRIP001         // whole document and have reached the start page again.
//STRIP001         SdDrawViewShell* pDrawViewShell = static_cast<SdDrawViewShell*>(mpViewShell);
//STRIP001         if (meMode == SPELL)
//STRIP001             if (maSearchStartPosition == ::sd::outliner::Iterator())
//STRIP001                 // Remember the position of the first text object so that we
//STRIP001                 // know when we have processed the whole document.
//STRIP001                 maSearchStartPosition = maObjectIterator;
//STRIP001             else if (maSearchStartPosition == maObjectIterator)
//STRIP001             {
//STRIP001                 mbEndOfSearch = TRUE;
//STRIP001             }
//STRIP001
//STRIP001
//STRIP001         EnterEditMode ();
//STRIP001     }
//STRIP001 }




//STRIP001 void SdOutliner::PrepareSearchAndReplace (void)
//STRIP001 {
//STRIP001     ULONG nMatchCount = 0;
//STRIP001     if (HasText( *mpSearchItem ))
//STRIP001     {
//STRIP001         mbStringFound = TRUE;
//STRIP001         mbMatchMayExist = TRUE;
//STRIP001
//STRIP001         EnterEditMode ();
//STRIP001
//STRIP001         mpDrawDocument->GetDocSh()->SetWaitCursor( FALSE );
//STRIP001         // Start seach at the right end of the current object's text
//STRIP001         // depending on the search direction.
//STRIP001         mpOutlineView->SetSelection (GetSearchStartPosition ());
//STRIP001     }
//STRIP001 }




//STRIP001 void SdOutliner::SetViewMode (PageKind ePageKind)
//STRIP001 {
//STRIP001     if (ePageKind != ( (SdDrawViewShell*) mpViewShell)->GetPageKind())
//STRIP001     {
//STRIP001         // Restore old edit mode.
//STRIP001         SdDrawViewShell* pDrawViewShell = static_cast<SdDrawViewShell*>(mpViewShell);
//STRIP001         pDrawViewShell->ChangeEditMode(meOriginalEditMode, FALSE);
//STRIP001
//STRIP001         SetStatusEventHdl(Link());
//STRIP001         mpViewShell->GetFrameView()->SetPageKind(ePageKind);
//STRIP001         try
//STRIP001         {
//STRIP001             mpViewShell->GetViewFrame()->GetDispatcher()->Execute(
//STRIP001                 SID_VIEWSHELL0, SFX_CALLMODE_SYNCHRON | SFX_CALLMODE_RECORD );
//STRIP001         }
//STRIP001         catch (::com::sun::star::uno::Exception e)
//STRIP001         {
//STRIP001             OSL_TRACE ("caught exception while switching view shell");
//STRIP001         }
//STRIP001         SetViewShell (mpDrawDocument->GetDocSh()->GetViewShell());
//STRIP001
//STRIP001         // Update the number of pages so that
//STRIP001         // <member>DetectChange()</member> has the correct value to compare
//STRIP001         // to.
//STRIP001         mnPageCount = mpDrawDocument->GetSdPageCount(ePageKind);
//STRIP001
//STRIP001         // Save edit mode so that it can be restored when switching the view
//STRIP001         // shell again.
//STRIP001         meOriginalEditMode = pDrawViewShell->GetEditMode();
//STRIP001     }
//STRIP001 }




//STRIP001 void SdOutliner::SetPage (EditMode eEditMode, USHORT nPageIndex)
//STRIP001 {
//STRIP001     if ( ! mbRestrictSearchToSelection)
//STRIP001     {
//STRIP001         ( (SdDrawViewShell*) mpViewShell )->ChangeEditMode(eEditMode, FALSE);
//STRIP001         ( (SdDrawViewShell*) mpViewShell )->SwitchPage(nPageIndex);
//STRIP001     }
//STRIP001 }




//STRIP001 void SdOutliner::EnterEditMode (void)
//STRIP001 {
//STRIP001     mpOutlineView->SetOutputArea( Rectangle( Point(), Size(1, 1)));
//STRIP001     SetPaperSize( mpTextObj->GetLogicRect().GetSize() );
//STRIP001     SdrPageView* pPV = mpView->GetPageViewPvNum(0);
//STRIP001     FASTBOOL bIsNewObj = TRUE;
//STRIP001
//STRIP001     // Make FuText the current function.
//STRIP001     SfxUInt16Item aItem (SID_TEXTEDIT, 1);
//STRIP001     mpViewShell->GetViewFrame()->GetDispatcher()->
//STRIP001         Execute(SID_TEXTEDIT, SFX_CALLMODE_SYNCHRON |
//STRIP001             SFX_CALLMODE_RECORD, &aItem, 0L);
//STRIP001
//STRIP001     // To be consistent with the usual behaviour in the Office the text
//STRIP001     // object that is put into edit mode would have also to be selected.
//STRIP001     // Starting the text edit mode is not enough so we do it here by hand.
//STRIP001     mbExpectingSelectionChangeEvent = true;
//STRIP001     mpView->UnmarkAllObj (pPV);
//STRIP001     mpView->MarkObj (mpTextObj, pPV);
//STRIP001
//STRIP001     // Turn on the edit mode for the text object.
//STRIP001     mpView->BegTextEdit(mpTextObj, pPV, mpWindow, bIsNewObj, this,
//STRIP001         mpOutlineView, TRUE, TRUE);
//STRIP001
//STRIP001
//STRIP001     SetUpdateMode(TRUE);
//STRIP001     mbFoundObject = TRUE;
//STRIP001 }




/*************************************************************************
|*
|* SpellChecker: Error-LinkHdl
|*
\************************************************************************/

//STRIP001 IMPL_LINK_INLINE_START( SdOutliner, SpellError, void *, nLang )
//STRIP001 {
//STRIP001  mbError = TRUE;
//STRIP001  String aError( ::GetLanguageString( (LanguageType)(ULONG)nLang ) );
//STRIP001  ErrorHandler::HandleError(* new StringErrorInfo(
//STRIP001                              ERRCODE_SVX_LINGU_LANGUAGENOTEXISTS, aError) );
//STRIP001  return 0;
//STRIP001 }
//STRIP001 IMPL_LINK_INLINE_END( SdOutliner, SpellError, void *, nLang )




//STRIP001 ESelection SdOutliner::GetSearchStartPosition (void)
//STRIP001 {
//STRIP001     ESelection aPosition;
//STRIP001     if (mbDirectionIsForward)
//STRIP001     {
//STRIP001         // The default constructor uses the beginning of the text as default.
//STRIP001         aPosition = ESelection ();
//STRIP001     }
//STRIP001     else
//STRIP001     {
//STRIP001         // Retrieve the position after the last character in the last
//STRIP001         // paragraph.
//STRIP001         USHORT nParagraphCount = static_cast<USHORT>(GetParagraphCount());
//STRIP001         if (nParagraphCount == 0)
//STRIP001             aPosition = ESelection();
//STRIP001         else
//STRIP001         {
//STRIP001             xub_StrLen nLastParagraphLength = GetEditEngine().GetTextLen (
//STRIP001                 nParagraphCount-1);
//STRIP001             aPosition = ESelection (nParagraphCount-1, nLastParagraphLength);
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001     return aPosition;
//STRIP001 }




//STRIP001 bool SdOutliner::HasNoPreviousMatch (void)
//STRIP001 {
//STRIP001     DBG_ASSERT (mpOutlineView!=NULL, "outline view in SdOutliner::HasNoPreviousMatch is NULL");
//STRIP001
//STRIP001     // Detect whether the cursor stands at the beginning
//STRIP001     // resp. at the end of the text.
//STRIP001     return mpOutlineView->GetSelection().IsEqual (
//STRIP001         GetSearchStartPosition ()) == TRUE;
//STRIP001 }




//STRIP001 bool SdOutliner::HandleFailedSearch (void)
//STRIP001 {
//STRIP001     bool bContinueSearch = false;
//STRIP001
//STRIP001     if (mpOutlineView != NULL && mpSearchItem != NULL)
//STRIP001     {
//STRIP001         // Prepare to open a message box.  Get the search dialog's window.
//STRIP001         Window* pParent = GetParentForDialog();
//STRIP001
//STRIP001         // Detect whether there is/may be a prior match.  If there is then
//STRIP001         // ask the user whether to wrap arround.  Otherwise tell the user
//STRIP001         // that there is no match.
//STRIP001         if (HasNoPreviousMatch ())
//STRIP001         {
//STRIP001             // No match found in the whole presentation.  Tell the user.
//STRIP001             InfoBox aInfoBox (pParent,
//STRIP001                 String(SdResId(STR_SAR_NOT_FOUND)));
//STRIP001             USHORT nBoxResult = aInfoBox.Execute();
//STRIP001         }
//STRIP001
//STRIP001         else
//STRIP001         {
//STRIP001             // No further matches found.  Ask the user whether to wrap
//STRIP001             // arround and start again.
//STRIP001             bContinueSearch = ShowWrapArroundDialog ();
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001     return bContinueSearch;
//STRIP001 }




/** See task #95227# for discussion about correct parent for dialogs/info boxes.
*/
//STRIP001 Window* SdOutliner::GetParentForDialog (void)
//STRIP001 {
//STRIP001     Window* pParent = NULL;
//STRIP001
//STRIP001     if (meMode == SEARCH)
//STRIP001         pParent = ((SvxSearchDialog*)(SfxViewFrame::Current()->GetChildWindow(
//STRIP001             SvxSearchDialogWrapper::GetChildWindowId())->GetWindow()));
//STRIP001
//STRIP001     if (pParent == NULL)
//STRIP001      pParent = mpViewShell->GetActiveWindow();
//STRIP001
//STRIP001     if (pParent == NULL)
//STRIP001         pParent = Application::GetDefModalDialogParent();
//STRIP001
//STRIP001     return pParent;
//STRIP001 }




//STRIP001 SdrObject* SdOutliner::SetObject (const ::sd::outliner::IteratorPosition& rPosition)
//STRIP001 {
//STRIP001     SetViewMode (rPosition.mePageKind);
//STRIP001     SetPage (rPosition.meEditMode, (USHORT)rPosition.mnPageIndex);
//STRIP001     return rPosition.mpObject;
//STRIP001 }




//STRIP001 void SdOutliner::SetViewShell (SdViewShell* pViewShell)
//STRIP001 {
//STRIP001     if (mpViewShell != pViewShell)
//STRIP001     {
//STRIP001         // Set the new view shell.
//STRIP001         mpViewShell = pViewShell;
//STRIP001         if (mpViewShell != NULL)
//STRIP001         {
//STRIP001             mpView = mpViewShell->GetView();
//STRIP001
//STRIP001             mpWindow = mpViewShell->GetActiveWindow();
//STRIP001             if (mpOutlineView != NULL)
//STRIP001                 mpOutlineView->SetWindow(mpWindow);
//STRIP001         }
//STRIP001         else
//STRIP001         {
//STRIP001             mpView = NULL;
//STRIP001             mpWindow = NULL;
//STRIP001         }
//STRIP001     }
//STRIP001 }




//STRIP001 void SdOutliner::HandleChangedSelection (void)
//STRIP001 {
//STRIP001     maMarkListCopy.clear();
//STRIP001     mbRestrictSearchToSelection = (mpView->HasMarkedObj()==TRUE);
//STRIP001     if (mbRestrictSearchToSelection)
//STRIP001     {
//STRIP001         // Make a copy of the current mark list.
//STRIP001         const SdrMarkList& rMarkList = mpView->GetMarkList();
//STRIP001         ULONG nCount = rMarkList.GetMarkCount();
//STRIP001         if (nCount > 0)
//STRIP001         {
//STRIP001             maMarkListCopy.clear();
//STRIP001             maMarkListCopy.reserve (nCount);
//STRIP001             for (ULONG i=0; i<nCount; i++)
//STRIP001                 maMarkListCopy.push_back (rMarkList.GetMark(i)->GetObj ());
//STRIP001         }
//STRIP001         else
//STRIP001             // No marked object.  Is this case possible?
//STRIP001             mbRestrictSearchToSelection = false;
//STRIP001     }
//STRIP001 }
}
