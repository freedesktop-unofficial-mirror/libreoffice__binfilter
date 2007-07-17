/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sd_sdoutl.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: obo $ $Date: 2007-07-17 10:24:06 $
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

#ifndef _EEITEMID_HXX //autogen
#include <bf_svx/eeitemid.hxx>
#endif

#ifndef _EEITEM_HXX //autogen
#include <bf_svx/eeitem.hxx>
#endif

#ifdef ITEMID_SEARCH
#undef ITEMID_SEARCH
#endif
#define ITEMID_SEARCH           SID_SEARCH_ITEM
#ifndef _SVXIDS_HRC
#include <bf_svx/svxids.hrc>
#endif
#ifndef _EEITEM_HXX //autogen
#include <bf_svx/eeitem.hxx>
#endif
#ifndef _EDITSTAT_HXX //autogen
#include <bf_svx/editstat.hxx>
#endif
#ifndef _UNO_LINGU_HXX
#include <bf_svx/unolingu.hxx>
#endif
#ifndef _EEITEM_HXX
#include <bf_svx/eeitem.hxx>
#endif
#ifndef _FORBIDDENCHARACTERSTABLE_HXX
#include <bf_svx/forbiddencharacterstable.hxx>
#endif
#ifndef _SVTOOLS_LINGUPROPS_HXX_
#include <svtools/linguprops.hxx>
#endif
#ifndef _SVTOOLS_LINGUCFG_HXX_
#include <svtools/lingucfg.hxx>
#endif

#include "strings.hrc"
#include "sdstring.hrc"
#include "sdoutl.hxx"
#include "drawdoc.hxx"
#include "docshell.hxx"
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
/*N*/     mpParaObj(NULL)
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




/*************************************************************************
|*
|* Spelling: Pruefung starten
|*
\************************************************************************/





/** Free all resources acquired during the search/spell check.  After a
    spell check the start position is restored here.
*/




/*************************************************************************
|*
|* Spelling: naechstes TextObjekt pruefen
|*
\************************************************************************/





/** Go to next match.
*/
















/** Try to detect whether the document or the view (shell) has changed since
    the last time <member>StartSearchAndReplace()</member> has been called.
*/
















/** The main purpose of this method is to iterate over all shape objects of
    the search area (current selection, current view, or whole document)
    until a text object has been found that contains at least one match or
    until no such object can be found anymore.   These two conditions are
    expressed by setting one of the flags <member>mbFoundObject</member> or
    <member>mbEndOfSearch</member> to <TRUE/>.
*/
















































/*************************************************************************
|*
|* SpellChecker: Error-LinkHdl
|*
\************************************************************************/

















/** See task #95227# for discussion about correct parent for dialogs/info boxes.
*/












}
