/*************************************************************************
 *
 *  $RCSfile: sw_docsh2.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2005-01-11 11:53:42 $
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

#define ITEMID_COLOR_TABLE      SID_COLOR_TABLE

#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif

#ifndef _URLOBJ_HXX //autogen
#include <tools/urlobj.hxx>
#endif
#ifndef _UNOTOOLS_TEMPFILE_HXX
#include <unotools/tempfile.hxx>
#endif
#ifndef _WRKWIN_HXX //autogen
#include <vcl/wrkwin.hxx>
#endif
#ifndef _MSGBOX_HXX //autogen
#include <vcl/msgbox.hxx>
#endif
#ifndef _LCKBITEM_HXX
#include <svtools/lckbitem.hxx>
#endif
#ifndef _SFXENUMITEM_HXX //autogen
#include <svtools/eitem.hxx>
#endif
#ifndef _SFXMACITEM_HXX //autogen
#include <svtools/macitem.hxx>
#endif
#ifndef _ZFORLIST_HXX //autogen
#include <svtools/zforlist.hxx>
#endif
#ifndef _ZFORMAT_HXX //autogen
#include <svtools/zformat.hxx>
#endif
#ifndef INCLUDED_SVTOOLS_PATHOPTIONS_HXX
#include <svtools/pathoptions.hxx>
#endif
#ifndef _TRANSFER_HXX
#include <svtools/transfer.hxx>
#endif
#ifndef _SFXDOCINF_HXX //autogen
#include <bf_sfx2/docinf.hxx>
#endif
#ifndef _SFX_DINFDLG_HXX //autogen
#include <bf_sfx2/dinfdlg.hxx>
#endif
#ifndef _SFXREQUEST_HXX //autogen
#include <bf_sfx2/request.hxx>
#endif
#ifndef _SFXDISPATCH_HXX //autogen
#include <bf_sfx2/dispatch.hxx>
#endif
#ifndef _SFXNEW_HXX //autogen
#include <bf_sfx2/new.hxx>
#endif
#ifndef _FILEDLGHELPER_HXX
#include <bf_sfx2/filedlghelper.hxx>
#endif
#ifndef _SFX_PRINTER_HXX //autogen
#include <bf_sfx2/printer.hxx>
#endif
#ifndef _SFX_EVENTCONF_HXX //autogen
#include <bf_sfx2/evntconf.hxx>
#endif
#ifndef _SFXECODE_HXX //autogen
#include <svtools/sfxecode.hxx>
#endif
#ifndef _SFXDOCFILE_HXX //autogen
#include <bf_sfx2/docfile.hxx>
#endif
#ifndef _SFX_DOCFILT_HACK_HXX //autogen
#include <bf_sfx2/docfilt.hxx>
#endif
#ifndef _SFXFRAME_HXX
#include <bf_sfx2/frame.hxx>
#endif
#ifndef _SVX_SVXIDS_HRC //autogen
#include <bf_svx/svxids.hrc>
#endif
#ifndef _SVX_DRAWITEM_HXX //autogen
#include <bf_svx/drawitem.hxx>
#endif
#ifndef _MySVXACORR_HXX //autogen
#include <bf_svx/svxacorr.hxx>
#endif
#ifndef _SVX_LANGITEM_HXX //autogen
#include <bf_svx/langitem.hxx>
#endif
#ifndef _SVX_FMSHELL_HXX //autogen
#include <bf_svx/fmshell.hxx>
#endif
#ifndef _OFA_HTMLCFG_HXX //autogen
#include <bf_offmgr/htmlcfg.hxx>
#endif
#ifndef _OFF_OFAITEM_HXX //autogen
#include <bf_offmgr/ofaitem.hxx>
#endif
#ifndef _OFF_APP_HXX //autogen
#include <bf_offmgr/app.hxx>
#endif

#ifndef _SB_SBSTAR_HXX //autogen
#include <basic/sbstar.hxx>
#endif
#ifndef _BASMGR_HXX //autogen
#include <basic/basmgr.hxx>
#endif
#ifndef _SVSTOR_HXX //autogen
#include <so3/svstor.hxx>
#endif
#ifndef _SO_CLSIDS_HXX
#include <so3/clsids.hxx>
#endif

#ifndef _SWUNODEF_HXX
#include <swunodef.hxx>
#endif

#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif

#ifndef _FMTCOL_HXX //autogen
#include <fmtcol.hxx>
#endif
#ifndef _SWEVENT_HXX //autogen
#include <swevent.hxx>
#endif
#ifndef _VIEW_HXX
#include <view.hxx>         // fuer die aktuelle Sicht
#endif
#ifndef _DOCSH_HXX
#include <docsh.hxx>        // Dokumenterzeugung
#endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _WRTSH_HXX
#include <wrtsh.hxx>
#endif
#ifndef _FLDBAS_HXX
#include <fldbas.hxx>
#endif
#ifndef _VIEWOPT_HXX
#include <viewopt.hxx>
#endif
#ifndef _GLOBDOC_HXX
#include <globdoc.hxx>
#endif
#ifndef _DOCSTDLG_HXX
#include <docstdlg.hxx>     // fuer Dokument Style
#endif
#ifndef _FLDWRAP_HXX
#include <fldwrap.hxx>
#endif
#ifndef _REDLNDLG_HXX
#include <redlndlg.hxx>
#endif
#ifndef _ABSTRACT_HXX
#include <abstract.hxx>     // SwInsertAbstractDialog
#endif
#ifndef _DOCSTYLE_HXX
#include <docstyle.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _PAGEDESC_HXX
#include <pagedesc.hxx>
#endif
#ifndef _SHELLIO_HXX
#include <shellio.hxx>
#endif
#ifndef _PVIEW_HXX
#include <pview.hxx>
#endif
#ifndef _SRCVIEW_HXX
#include <srcview.hxx>
#endif
#ifndef _POOLFMT_HXX
#include <poolfmt.hxx>
#endif
#ifndef _USRPREF_HXX
#include <usrpref.hxx>
#endif
#ifndef _WDOCSH_HXX
#include <wdocsh.hxx>
#endif
#ifndef _UNOTXDOC_HXX
#include <unotxdoc.hxx>
#endif
#ifndef _ACMPLWRD_HXX
#include <acmplwrd.hxx>
#endif
#ifndef _SWMODULE_HXX
#include <swmodule.hxx>
#endif
#ifndef _UNOOBJ_HXX
#include <unoobj.hxx>
#endif
#ifndef _SWWAIT_HXX
#include <swwait.hxx>
#endif

#ifndef _CMDID_H
#include <cmdid.h>
#endif
#ifndef _GLOBALS_H
#include <globals.h>
#endif
#ifndef _HELPID_H
#include <helpid.h>
#endif
#ifndef _APP_HRC
#include <app.hrc>
#endif
#ifndef _POOLFMT_HRC
#include <poolfmt.hrc>
#endif
#ifndef _GLOBALS_HRC
#include <globals.hrc>
#endif
#ifndef _COM_SUN_STAR_UI_DIALOGS_XFILEPICKER_HPP_
#include <com/sun/star/ui/dialogs/XFilePicker.hpp>
#endif
#ifndef _COM_SUN_STAR_UI_DIALOGS_XFILTERMANAGER_HPP_
#include <com/sun/star/ui/dialogs/XFilterManager.hpp>
#endif
#ifndef _COM_SUN_STAR_UI_DIALOGS_XFILEPICKERCONTROLACCESS_HPP_
#include <com/sun/star/ui/dialogs/XFilePickerControlAccess.hpp>
#endif
#ifndef _COM_SUN_STAR_UI_DIALOGS_EXTENDEDFILEPICKERELEMENTIDS_HPP_
#include <com/sun/star/ui/dialogs/ExtendedFilePickerElementIds.hpp>
#endif
#ifndef _COM_SUN_STAR_UI_DIALOGS_LISTBOXCONTROLACTIONS_HPP_
#include <com/sun/star/ui/dialogs/ListboxControlActions.hpp>
#endif
#ifndef _COM_SUN_STAR_UI_DIALOGS_COMMONFILEPICKERELEMENTIDS_HPP_
#include <com/sun/star/ui/dialogs/CommonFilePickerElementIds.hpp>
#endif
#ifndef  _COM_SUN_STAR_UI_DIALOGS_TEMPLATEDESCRIPTION_HPP_
#include <com/sun/star/ui/dialogs/TemplateDescription.hpp>
#endif

#ifndef _SWSTYLENAMEMAPPER_HXX
#include <SwStyleNameMapper.hxx>
#endif

#include <sw3io.hxx>
#include "so3/staticbaseurl.hxx"
namespace binfilter {

using namespace ::com::sun::star::ui::dialogs;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star;
using namespace ::rtl;
using namespace sfx2;

//STRIP001 extern FASTBOOL FindPhyStyle( SwDoc& , const String& , SfxStyleFamily );

/*--------------------------------------------------------------------
    Beschreibung:   DocInfo setzen am SFX
 --------------------------------------------------------------------*/


//STRIP001 BOOL SwDocShell::SetDocumentInfo(const SfxDocumentInfo& rInfo)
//STRIP001 {
//STRIP001  SfxDocumentInfo& rOldInfo = GetDocInfo();
//STRIP001  BOOL bRet = !(rOldInfo == rInfo);
//STRIP001  if( bRet )
//STRIP001  {
//STRIP001      rOldInfo = rInfo;
//STRIP001      Broadcast( SfxDocumentInfoHint( &rOldInfo ) );
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung:   DocInfo kreieren (virtuell)
 --------------------------------------------------------------------*/


//STRIP001 SfxDocumentInfoDialog* SwDocShell::CreateDocumentInfoDialog(
//STRIP001                              Window *pParent, const SfxItemSet &rSet)
//STRIP001 {
//STRIP001  SfxDocumentInfoDialog* pDlg = new SfxDocumentInfoDialog(pParent, rSet);
//STRIP001 //   const SfxDocumentInfoItem& rItem = (const SfxDocumentInfoItem&)rSet.Get(SID_DOCINFO);
//STRIP001 //   if(rItem.IsOwnFormat())
//STRIP001  //nur mit Statistik, wenn dieses Doc auch angezeigt wird, nicht
//STRIP001  //aus dem Doc-Manager
//STRIP001  SwDocShell* pDocSh = (SwDocShell*) SfxObjectShell::Current();
//STRIP001  if( pDocSh == this )
//STRIP001  {
//STRIP001      //Nicht fuer SourceView.
//STRIP001      SfxViewShell *pVSh = SfxViewShell::Current();
//STRIP001      if ( pVSh && !pVSh->ISA(SwSrcView) )
//STRIP001          pDlg->AddTabPage(TP_DOC_STAT, SW_RESSTR(STR_DOC_STAT),
//STRIP001                                                  SwDocStatPage::Create, 0);
//STRIP001  }
//STRIP001  return pDlg;
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung:   Benachrichtigung bei geaenderter DocInfo
 --------------------------------------------------------------------*/


/*N*/ void SwDocShell::Notify( SfxBroadcaster&, const SfxHint& rHint )
/*N*/ {
/*N*/   if( !pDoc )
/*N*/   {
/*N*/ //MA: Kommt bei der OLE-Registration vor!
/*N*/ //        ASSERT( !this, "DocShell ist nicht richtig initialisiert!" );
/*N*/       return ;
/*N*/   }
/*N*/
/*N*/   USHORT nAction = 0;
/*N*/   if( rHint.ISA(SfxDocumentInfoHint) )
/*N*/       nAction = 1;
/*N*/   else if( rHint.ISA(SfxSimpleHint) )
/*N*/   {
/*N*/       // swithc for more actions
/*N*/       switch( ((SfxSimpleHint&) rHint).GetId() )
/*N*/       {
/*N*/       case SFX_HINT_TITLECHANGED:
/*N*/           if( GetMedium() )
/*N*/               nAction = 2;
/*N*/           break;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if( nAction )
/*N*/   {
/*N*/       BOOL bUnlockView;
/*N*/       if( pWrtShell )
/*N*/       {
/*N*/           bUnlockView = !pWrtShell->IsViewLocked();
/*N*/           pWrtShell->LockView( TRUE );    //lock visible section
/*N*/           pWrtShell->StartAllAction();
/*N*/       }
/*N*/       switch( nAction )
/*N*/       {
/*N*/       case 1:
/*N*/           pDoc->DocInfoChgd( *((SfxDocumentInfoHint&)rHint).GetObject() );
/*N*/           break;
/*N*/
/*N*/       case 2:
/*N*/           pDoc->GetSysFldType( RES_FILENAMEFLD )->UpdateFlds();
/*N*/           break;
/*N*/       }
/*N*/
/*N*/       if( pWrtShell )
/*N*/       {
/*N*/           pWrtShell->EndAllAction();
/*N*/           if( bUnlockView )
/*N*/               pWrtShell->LockView( FALSE );
/*N*/       }
/*N*/   }
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung:   Benachrichtigung Doc schliessen
 --------------------------------------------------------------------*/


//STRIP001 USHORT SwDocShell::PrepareClose( BOOL bUI, BOOL bForBrowsing )
//STRIP001 {
//STRIP001  USHORT nRet = SfxObjectShell::PrepareClose( bUI, bForBrowsing );
//STRIP001
//STRIP001  if( TRUE == nRet ) //Unbedingt auf TRUE abfragen! (RET_NEWTASK)
//STRIP001      EndListening( *this );
//STRIP001
//STRIP001  return nRet;
//STRIP001 }


/*N*/ void SwDoc::SetInfo( const SfxDocumentInfo& rInfo )
/*N*/ {
DBG_BF_ASSERT(0, "STRIP"); //STRIP001   if( pDocShell )
//STRIP001      pDocShell->SetDocumentInfo( rInfo );
//STRIP001
//STRIP001  // sollte nur beim "Konvertieren" von Dokumenten hier ankommen!
//STRIP001  else
//STRIP001  {
//STRIP001      // dann setzen wir uns die DocInfo. Nach dem Konvertieren wird diese
//STRIP001      // am Medium gesetzt. Erst dann ist die DocShell bekannt.
//STRIP001      delete pSwgInfo;
//STRIP001      pSwgInfo = new SfxDocumentInfo( rInfo );
//STRIP001
//STRIP001 // wenn beim Einlesen, dann kein Modify verschicken, diese sollten dann
//STRIP001 // richtig eingelesen werden oder spaetestens beim Expandieren die richtigen
//STRIP001 // Werte finden.
//STRIP001 //       GetSysFldType( RES_DOCINFOFLD )->UpdateFlds();
//STRIP001 //       GetSysFldType( RES_TEMPLNAMEFLD )->UpdateFlds();
//STRIP001  }
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung:   Organizer
 --------------------------------------------------------------------*/


//STRIP001 BOOL SwDocShell::Insert( SfxObjectShell &rSource,
//STRIP001  USHORT  nSourceIdx1,        // SourcePool: oberste Inhaltsebene (Vorlagen/Makros)
//STRIP001  USHORT  nSourceIdx2,        // Index in den Inhalt
//STRIP001  USHORT  nSourceIdx3,        // Index in die Inhaltsebene
//STRIP001  USHORT &rIdx1,              // und das gleiche fuer den DestinationPool
//STRIP001  USHORT &rIdx2,              //      ""
//STRIP001  USHORT &rIdx3,              //      ""
//STRIP001  USHORT &rRemovedIdx )       // falls doppelte geloescht werden, Pos zurueck
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001
//STRIP001  if (INDEX_IGNORE == rIdx1 && CONTENT_STYLE == nSourceIdx1)
//STRIP001      rIdx1 = CONTENT_STYLE;
//STRIP001
//STRIP001  if (CONTENT_STYLE == nSourceIdx1 && CONTENT_STYLE == rIdx1)
//STRIP001  {
//STRIP001      SfxStyleSheetBasePool* pHisPool  = rSource.GetStyleSheetPool();
//STRIP001      SwDocStyleSheetPool* pMyPool =
//STRIP001          (SwDocStyleSheetPool*)GetStyleSheetPool();
//STRIP001
//STRIP001      //  wir koennen nicht in uns selbst hin und her moven
//STRIP001      if( pHisPool == pMyPool )
//STRIP001          return FALSE;
//STRIP001
//STRIP001      if( INDEX_IGNORE == rIdx2 )
//STRIP001          rIdx2 = pMyPool->Count();
//STRIP001
//STRIP001      // erstmal auf die Such-Maske "positionieren"
//STRIP001      pHisPool->First();
//STRIP001      SfxStyleSheetBase* pHisSheet = (*pHisPool)[nSourceIdx2];
//STRIP001
//STRIP001      // wenn so eine Vorlage schon existiert: loeschen!
//STRIP001      const String& rOldName = pHisSheet->GetName();
//STRIP001      SfxStyleFamily eOldFamily( pHisSheet->GetFamily() );
//STRIP001
//STRIP001      // dflt. PageDesc und StandardZeichenvorlage nie loeschen !!!
//STRIP001      if( ( SFX_STYLE_FAMILY_PAGE == eOldFamily &&
//STRIP001            pDoc->GetPageDesc(0).GetName() == rOldName ) ||
//STRIP001            ( SFX_STYLE_FAMILY_CHAR == eOldFamily &&
//STRIP001              rOldName == *SwStyleNameMapper::GetTextUINameArray()[ RES_POOLCOLL_STANDARD -
//STRIP001                                              RES_POOLCOLL_TEXT_BEGIN ] ))
//STRIP001          return FALSE;
//STRIP001
//STRIP001      SfxStyleFamily eMyOldFamily( pMyPool->GetSearchFamily() );
//STRIP001      USHORT nMySrchMask = pMyPool->GetSearchMask();
//STRIP001
//STRIP001      SfxStyleSheetBase* pExist;
//STRIP001      if( ::FindPhyStyle( *pDoc, rOldName, eOldFamily ) )
//STRIP001      {
//STRIP001          // Bug 20365: nur uebernehmen, wenn das gewuenscht ist!
//STRIP001          if( ERRCODE_BUTTON_OK != ErrorHandler::HandleError(
//STRIP001              *new MessageInfo( ERRCODE_SFXMSG_STYLEREPLACE, rOldName )) )
//STRIP001          {
//STRIP001              return FALSE;
//STRIP001          }
//STRIP001
//STRIP001          // Da Replace den aStyleSheet-Member selbst benoetigt, muss
//STRIP001          // das Ergebnis vom Find kopiert werden (s.u.))
//STRIP001          SwDocStyleSheet aExist(
//STRIP001                  *(SwDocStyleSheet*)pMyPool->Find( rOldName, eOldFamily ) );
//STRIP001          pMyPool->Replace( *pHisSheet, aExist );
//STRIP001
//STRIP001          // An der Reihenfolge der Vorlagen im Pool aendert sich nichts.
//STRIP001          rIdx2 = rIdx1 = INDEX_IGNORE;
//STRIP001
//STRIP001          GetDoc()->SetModified();
//STRIP001
//STRIP001          return TRUE;
//STRIP001      }
//STRIP001
//STRIP001      pMyPool->SetSearchMask( eOldFamily, nMySrchMask );
//STRIP001
//STRIP001      // MIB 18.12.98: SwDocStyleSheetPool::Make liefert einen
//STRIP001      // Pointer auf SwDocStyleSheetPool::aStyleSheet zurueck.
//STRIP001      // Der gleiche Member von SwDocStyleSheetPool::Find benutzt.
//STRIP001      // Deshalb muss hier mit einer Kopie gearbeitet werden.
//STRIP001      // Vorsicht: SfxStyleSheetBase::SetFollow ruft seinerseits
//STRIP001      // ein SwDocStyleSheetPool::Find auf, do dass es nicht genuegt
//STRIP001      // die Find-Aufrufe in dieser Methode zu eleminieren.
//STRIP001
//STRIP001      SwDocStyleSheet aNewSheet( (SwDocStyleSheet&)pMyPool
//STRIP001              ->Make(rOldName, eOldFamily, pHisSheet->GetMask() ) );
//STRIP001      if( SFX_STYLE_FAMILY_PAGE == eOldFamily && rSource.ISA(SwDocShell) )
//STRIP001      {
//STRIP001          // gesondert behandeln!!
//STRIP001          SwPageDesc* pDestDsc = (SwPageDesc*)aNewSheet.GetPageDesc();
//STRIP001          SwPageDesc* pCpyDsc = (SwPageDesc*)((SwDocStyleSheet*)pHisSheet)->GetPageDesc();
//STRIP001          pDoc->CopyPageDesc( *pCpyDsc, *pDestDsc );
//STRIP001      }
//STRIP001      else
//STRIP001          // die neue Vorlage mit den Attributen fuellen
//STRIP001          aNewSheet.SetItemSet( pHisSheet->GetItemSet() );
//STRIP001
//STRIP001      pMyPool->SetSearchMask( SFX_STYLE_FAMILY_ALL, nMySrchMask );
//STRIP001
//STRIP001      if( aNewSheet.IsUserDefined() || aNewSheet.IsUsed() )
//STRIP001      {
//STRIP001          // Benutzte und Benutzer-definierte Vorlagen werden angezeigt.
//STRIP001          // Dshalb muss hier der Index der neuen Vorlage im Pool
//STRIP001          // ermittelt werden.
//STRIP001          pExist = pMyPool->First();
//STRIP001          USHORT nIdx = 0;
//STRIP001          while( pExist )
//STRIP001          {
//STRIP001              if( pExist->GetName() == rOldName &&
//STRIP001                 eOldFamily == pExist->GetFamily() )
//STRIP001              {
//STRIP001                  rIdx2 = nIdx;
//STRIP001                  break;
//STRIP001              }
//STRIP001              pExist = pMyPool->Next();
//STRIP001              nIdx++;
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          // Andere Vorlagen werden nicht angezeigt.
//STRIP001          rIdx1 = rIdx2 = INDEX_IGNORE;
//STRIP001      }
//STRIP001
//STRIP001 /*         pMyPool->Count();       //interne Liste neu fuellen lassen!!!!!
//STRIP001
//STRIP001      // suchen, um die richige Insert-Position returnen zu koennen
//STRIP001      pMyPool->Find( rOldName, SFX_STYLE_FAMILY_ALL, nMySrchMask );
//STRIP001      rIdx2 = pMyPool->GetFindPos();*/
//STRIP001
//STRIP001      // wer bekommt den Neuen als Parent? wer benutzt den Neuen als Follow?
//STRIP001      // (immer nur ueber die Instanziierten!!!)
//STRIP001      pMyPool->SetSearchMask( eOldFamily, nMySrchMask );
//STRIP001      pMyPool->SetOrganizerMode( TRUE );
//STRIP001      SfxStyleSheetBase* pTestSheet = pMyPool->First();
//STRIP001      while (pTestSheet)
//STRIP001      {
//STRIP001          if (pTestSheet->GetFamily() == eOldFamily &&
//STRIP001              pTestSheet->HasParentSupport()        &&
//STRIP001              pTestSheet->GetParent() == rOldName)
//STRIP001          {
//STRIP001              pTestSheet->SetParent(rOldName); // Verknuepfung neu aufbauen
//STRIP001          }
//STRIP001
//STRIP001          if (pTestSheet->GetFamily() == eOldFamily &&
//STRIP001              pTestSheet->HasFollowSupport()        &&
//STRIP001              pTestSheet->GetFollow() == rOldName)
//STRIP001          {
//STRIP001              pTestSheet->SetFollow(rOldName); // Verknuepfung neu aufbauen
//STRIP001          }
//STRIP001
//STRIP001          pTestSheet = pMyPool->Next();
//STRIP001      }
//STRIP001      pMyPool->SetOrganizerMode( SFX_CREATE_MODE_ORGANIZER == GetCreateMode() );
//STRIP001
//STRIP001      // hat der Neue einen Parent? wenn ja, mit gleichem Namen bei uns suchen
//STRIP001      if (pHisSheet->HasParentSupport())
//STRIP001      {
//STRIP001          const String& rParentName = pHisSheet->GetParent();
//STRIP001          if (0 != rParentName.Len())
//STRIP001          {
//STRIP001              SfxStyleSheetBase* pParentOfNew = pMyPool->Find(rParentName,
//STRIP001                                                              eOldFamily);
//STRIP001              if (pParentOfNew)
//STRIP001              {
//STRIP001                  aNewSheet.SetParent(rParentName);
//STRIP001              }
//STRIP001              pMyPool->SetSearchMask( eOldFamily, nMySrchMask );
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      // hat der Neue einen Follow? wenn ja, mit gleichem Namen bei uns suchen
//STRIP001      if (pHisSheet->HasFollowSupport())
//STRIP001      {
//STRIP001          const String& rFollowName = pHisSheet->GetFollow();
//STRIP001          if (0 != rFollowName.Len())
//STRIP001          {
//STRIP001              SfxStyleSheetBase* pFollowOfNew = pMyPool->Find(rFollowName,
//STRIP001                                                              eOldFamily);
//STRIP001              if (pFollowOfNew)
//STRIP001              {
//STRIP001                  aNewSheet.SetFollow(rFollowName);
//STRIP001              }
//STRIP001              pMyPool->SetSearchMask( eOldFamily, nMySrchMask );
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      // Bug 27347: alte Einstellung wieder setzen
//STRIP001      pMyPool->SetSearchMask( eMyOldFamily, nMySrchMask );
//STRIP001
//STRIP001      // Model geaendert
//STRIP001      ASSERT(pDoc, "Doc fehlt");
//STRIP001      GetDoc()->SetModified();
//STRIP001
//STRIP001      bRet = TRUE;
//STRIP001  }
//STRIP001  else
//STRIP001      bRet = SfxObjectShell::Insert( rSource,
//STRIP001                  nSourceIdx1,
//STRIP001                  nSourceIdx2,
//STRIP001                  nSourceIdx3,
//STRIP001                  rIdx1,
//STRIP001                  rIdx2,
//STRIP001                  rIdx3,
//STRIP001                  rRemovedIdx);
//STRIP001
//STRIP001  return bRet;
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung:   Vorlagen Remove
 --------------------------------------------------------------------*/


//STRIP001 BOOL SwDocShell::Remove(USHORT nIdx1,        // siehe Insert
//STRIP001                      USHORT nIdx2,
//STRIP001                      USHORT nIdx3)
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001
//STRIP001  if (CONTENT_STYLE == nIdx1)
//STRIP001  {
//STRIP001      SwDocStyleSheetPool* pMyPool = (SwDocStyleSheetPool*)GetStyleSheetPool();
//STRIP001
//STRIP001      pMyPool->First();       // vorm Zugriff Pool aktualisieren!!
//STRIP001      SfxStyleSheetBase* pMySheet = (*pMyPool)[nIdx2];
//STRIP001
//STRIP001      String aName( pMySheet->GetName() );
//STRIP001      SfxStyleFamily eFamily( pMySheet->GetFamily() );
//STRIP001
//STRIP001      // dflt. PageDesc und StandardZeichenvorlage nie loeschen !!!
//STRIP001      if( ( SFX_STYLE_FAMILY_PAGE == eFamily &&
//STRIP001            pDoc->GetPageDesc(0).GetName() == aName ) ||
//STRIP001            ( SFX_STYLE_FAMILY_CHAR == eFamily &&
//STRIP001              aName == *SwStyleNameMapper::GetTextUINameArray()[ RES_POOLCOLL_STANDARD -
//STRIP001                                              RES_POOLCOLL_TEXT_BEGIN ] ))
//STRIP001          return FALSE;
//STRIP001
//STRIP001      // also loeschen
//STRIP001      pMyPool->Erase( pMySheet );
//STRIP001
//STRIP001      // jetzt noch die Parents/Follows aller Instanziierten korrigieren
//STRIP001      pMyPool->SetOrganizerMode( TRUE );
//STRIP001      SfxStyleSheetBase* pTestSheet = pMyPool->First();
//STRIP001      while (pTestSheet)
//STRIP001      {
//STRIP001          if (pTestSheet->GetFamily() == eFamily &&
//STRIP001              pTestSheet->HasParentSupport()     &&
//STRIP001              pTestSheet->GetParent() == aName)
//STRIP001          {
//STRIP001              pTestSheet->SetParent( aEmptyStr ); // Verknuepfung aufloesen
//STRIP001          }
//STRIP001
//STRIP001          if (pTestSheet->GetFamily() == eFamily &&
//STRIP001              pTestSheet->HasFollowSupport()        &&
//STRIP001              pTestSheet->GetFollow() == aName)
//STRIP001          {
//STRIP001              pTestSheet->SetFollow( aEmptyStr ); // Verknuepfung aufloesen
//STRIP001          }
//STRIP001
//STRIP001          pTestSheet = pMyPool->Next();
//STRIP001      }
//STRIP001      pMyPool->SetOrganizerMode( SFX_CREATE_MODE_ORGANIZER == GetCreateMode() );
//STRIP001
//STRIP001      bRet = TRUE;
//STRIP001  }
//STRIP001  else
//STRIP001      bRet = SfxObjectShell::Remove(  nIdx1,
//STRIP001                                      nIdx2,
//STRIP001                                      nIdx3 );
//STRIP001
//STRIP001
//STRIP001  // Model geaendert
//STRIP001  ASSERT(pDoc, "Doc fehlt");
//STRIP001  GetDoc()->SetModified();
//STRIP001
//STRIP001  return bRet;
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/


/*N*/ void SwDocShell::Execute(SfxRequest& rReq)
/*N*/ {
/*?*/ DBG_BF_ASSERT(0, "STRIP"); //STRIP001     const SfxItemSet* pArgs = rReq.GetArgs();
//STRIP001 /*?*/    const SfxPoolItem* pItem;
//STRIP001 /*?*/    USHORT nWhich = rReq.GetSlot();
//STRIP001 /*?*/    BOOL bDone = FALSE;
//STRIP001 /*?*/    switch ( nWhich )
//STRIP001 /*?*/    {
//STRIP001 /*?*/         case SID_AUTO_CORRECT_DLG:
//STRIP001 /*?*/        {
//STRIP001 /*?*/            OfficeApplication *pOApp = OFF_APP();
//STRIP001 /*?*/
//STRIP001 /*?*/            SfxBoolItem aSwOptions( SID_AUTO_CORRECT_DLG, TRUE );
//STRIP001 /*?*/            SvxSwAutoFmtFlags* pAFlags = &pOApp->GetAutoCorrect()->GetSwFlags();
//STRIP001 /*?*/            SwAutoCompleteWord& rACW = SwDoc::GetAutoCompleteWords();
//STRIP001 /*?*/
//STRIP001 /*?*/            BOOL bOldLocked = rACW.IsLockWordLstLocked(),
//STRIP001 /*?*/                 bOldAutoCmpltCollectWords = pAFlags->bAutoCmpltCollectWords;
//STRIP001 /*?*/
//STRIP001 /*?*/            rACW.SetLockWordLstLocked( TRUE );
//STRIP001 /*?*/
//STRIP001 /*?*/            SvStringsISortDtor aTmpLst;
//STRIP001 /*?*/            aTmpLst.Insert( &rACW.GetWordList() );
//STRIP001 /*?*/            pAFlags->pAutoCmpltList = &aTmpLst;
//STRIP001 /*?*/
//STRIP001 /*?*/            SfxViewShell* pViewShell = GetView()
//STRIP001 /*?*/                                            ? (SfxViewShell*)GetView()
//STRIP001 /*?*/                                            : SfxViewShell::Current();
//STRIP001 /*?*/            SfxRequest aAppReq(SID_AUTO_CORRECT_DLG, SFX_CALLMODE_SYNCHRON, pOApp->GetPool());
//STRIP001 /*?*/            aAppReq.AppendItem(aSwOptions);
//STRIP001 /*?*/            pOApp->ExecuteSlot(aAppReq);
//STRIP001 /*?*/
//STRIP001 /*?*/            rACW.SetLockWordLstLocked( bOldLocked );
//STRIP001 /*?*/
//STRIP001 /*?*/            SwEditShell::SetAutoFmtFlags( pAFlags );
//STRIP001 /*?*/            rACW.SetMinWordLen( pAFlags->nAutoCmpltWordLen );
//STRIP001 /*?*/            rACW.SetMaxCount( pAFlags->nAutoCmpltListLen );
//STRIP001 /*?*/            if( pAFlags->pAutoCmpltList )  // any changes?
//STRIP001 /*?*/            {
//STRIP001 /*?*/                rACW.CheckChangedList( aTmpLst );
//STRIP001 /*?*/                // clear the temp WordList pointer
//STRIP001 /*?*/                pAFlags->pAutoCmpltList = 0;
//STRIP001 /*?*/            }
//STRIP001 /*?*/            // remove all pointer we never delete the strings
//STRIP001 /*?*/            aTmpLst.Remove( (USHORT)0, aTmpLst.Count() );
//STRIP001 /*?*/
//STRIP001 /*?*/            if( !bOldAutoCmpltCollectWords && bOldAutoCmpltCollectWords !=
//STRIP001 /*?*/                pAFlags->bAutoCmpltCollectWords )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                // call on all Docs the idle formatter to start
//STRIP001 /*?*/                // the collection of Words
//STRIP001 /*?*/                TypeId aType = TYPE(SwDocShell);
//STRIP001 /*?*/                for( SwDocShell *pDocSh = (SwDocShell*)SfxObjectShell::GetFirst(&aType);
//STRIP001 /*?*/                    pDocSh;
//STRIP001 /*?*/                    pDocSh = (SwDocShell*)SfxObjectShell::GetNext( *pDocSh, &aType ) )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    SwDoc* pTmp = pDocSh->GetDoc();
//STRIP001 /*?*/                    if ( pTmp->GetRootFrm() )
//STRIP001 /*?*/                        pTmp->InvalidateAutoCompleteFlag();
//STRIP001 /*?*/                }
//STRIP001 /*?*/            }
//STRIP001 /*?*/        }
//STRIP001 /*?*/        break;
//STRIP001 /*?*/
//STRIP001 /*?*/        case SID_PRINTPREVIEW:
//STRIP001 /*?*/            {
//STRIP001 /*?*/                BOOL bSet = FALSE, bFound = FALSE, bOnly = TRUE;
//STRIP001 /*?*/                SfxViewFrame *pTmpFrm = SfxViewFrame::GetFirst(this);
//STRIP001 /*?*/                SfxViewShell* pViewShell = SfxViewShell::Current();
//STRIP001 /*?*/                SwView* pView = PTR_CAST( SwView, pViewShell );
//STRIP001 /*?*/                BOOL bCurrent = IS_TYPE( SwPagePreView, pViewShell );
//STRIP001 /*?*/
//STRIP001 /*?*/                while( pTmpFrm )    // search PreView
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    if( IS_TYPE( SwView, pTmpFrm->GetViewShell()) )
//STRIP001 /*?*/                        bOnly = FALSE;
//STRIP001 /*?*/                    else if( IS_TYPE( SwPagePreView, pTmpFrm->GetViewShell()))
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        pTmpFrm->GetFrame()->Appear();
//STRIP001 /*?*/                        bFound = TRUE;
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                    if( bFound && !bOnly )
//STRIP001 /*?*/                        break;
//STRIP001 /*?*/                    pTmpFrm = pTmpFrm->GetNext(*pTmpFrm, this);
//STRIP001 /*?*/                }
//STRIP001 /*?*/
//STRIP001 /*?*/                if( pArgs && SFX_ITEM_SET ==
//STRIP001 /*?*/                    pArgs->GetItemState( SID_PRINTPREVIEW, FALSE, &pItem ))
//STRIP001 /*?*/                    bSet = ((SfxBoolItem*)pItem)->GetValue();
//STRIP001 /*?*/                else
//STRIP001 /*?*/                    bSet = !bCurrent;
//STRIP001 /*?*/
//STRIP001 /*?*/                USHORT nSlotId = 0;
//STRIP001 /*?*/                if( bSet && !bFound )   // Keine gefunden, daher neue Preview anlegen
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    //Keine neue anlegen fuer BrowseView!
//STRIP001 /*?*/                    if( !GetDoc()->IsBrowseMode() )
//STRIP001 /*?*/                        nSlotId = SID_VIEWSHELL1;
//STRIP001 /*?*/                }
//STRIP001 /*?*/                else if( bFound && !bSet )
//STRIP001 /*?*/                    nSlotId = bOnly ? SID_VIEWSHELL0 : SID_VIEWSHELL1;
//STRIP001 /*?*/
//STRIP001 /*?*/                if( nSlotId )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    //JP 23.8.2001: Bug 91360 - PagePreView in the WebDocShell
//STRIP001 /*?*/                    //              is found under Id ViewShell2.
//STRIP001 /*?*/                    if( ISA(SwWebDocShell) && SID_VIEWSHELL1 == nSlotId )
//STRIP001 /*?*/                        nSlotId = SID_VIEWSHELL2;
//STRIP001 /*?*/
//STRIP001 /*?*/                    if( pView && pView->GetDocShell() == this )
//STRIP001 /*?*/                        pTmpFrm = pView->GetViewFrame();
//STRIP001 /*?*/                    else
//STRIP001 /*?*/                        pTmpFrm = SfxViewFrame::GetFirst( this );
//STRIP001 /*?*/
//STRIP001 /*?*/                     pTmpFrm->GetDispatcher()->Execute( nSlotId, NULL, 0, SFX_CALLMODE_ASYNCHRON );
//STRIP001 /*?*/                }
//STRIP001 /*?*/
//STRIP001 /*?*/                rReq.SetReturnValue(SfxBoolItem(SID_PRINTPREVIEW, bSet ));
//STRIP001 /*?*/            }
//STRIP001 /*?*/            break;
//STRIP001 /*?*/        case SID_TEMPLATE_LOAD:
//STRIP001 /*?*/            {
//STRIP001 /*?*/                String aFileName;
//STRIP001 /*?*/                 static BOOL bText = TRUE;
//STRIP001 /*?*/                 static BOOL bFrame = FALSE;
//STRIP001 /*?*/                 static BOOL bPage =  FALSE;
//STRIP001 /*?*/                 static BOOL bNum =   FALSE;
//STRIP001 /*?*/                 static BOOL bMerge = FALSE;
//STRIP001 /*?*/                USHORT nRet = USHRT_MAX;
//STRIP001 /*?*/
//STRIP001 /*?*/                 USHORT nFlags = bFrame ? SFX_LOAD_FRAME_STYLES : 0;
//STRIP001 /*?*/                 if(bPage)
//STRIP001 /*?*/                     nFlags|= SFX_LOAD_PAGE_STYLES;
//STRIP001 /*?*/                 if(bNum)
//STRIP001 /*?*/                     nFlags|= SFX_LOAD_NUM_STYLES;
//STRIP001 /*?*/                 if(!nFlags || bText)
//STRIP001 /*?*/                     nFlags|= SFX_LOAD_TEXT_STYLES;
//STRIP001 /*?*/                 if(bMerge)
//STRIP001 /*?*/                     nFlags|= SFX_MERGE_STYLES;
//STRIP001 /*?*/
//STRIP001 /*?*/                 if ( pArgs )
//STRIP001 /*?*/                 {
//STRIP001 /*?*/                     SFX_REQUEST_ARG( rReq, pItem, SfxStringItem, SID_TEMPLATE_NAME, FALSE );
//STRIP001 /*?*/                     if ( pItem )
//STRIP001 /*?*/                     {
//STRIP001 /*?*/                         aFileName = pItem->GetValue();
//STRIP001 /*?*/                         SFX_REQUEST_ARG( rReq, pFlagsItem, SfxInt32Item, SID_TEMPLATE_LOAD, FALSE );
//STRIP001 /*?*/                         if ( pFlagsItem )
//STRIP001 /*?*/                             nFlags = (USHORT) pFlagsItem->GetValue();
//STRIP001 /*?*/                     }
//STRIP001 /*?*/                 }
//STRIP001 /*?*/
//STRIP001 /*?*/                 if ( !aFileName.Len() )
//STRIP001 /*?*/                 {
//STRIP001 /*?*/                     SvtPathOptions aPathOpt;
//STRIP001 /*?*/                     SfxNewFileDialog* pNewFileDlg =
//STRIP001 /*?*/                         new SfxNewFileDialog(&GetView()->GetViewFrame()->GetWindow(), SFXWB_LOAD_TEMPLATE);
//STRIP001 /*?*/                     pNewFileDlg->SetTemplateFlags(nFlags);
//STRIP001 /*?*/
//STRIP001 /*?*/                     nRet = pNewFileDlg->Execute();
//STRIP001 /*?*/                     if(RET_TEMPLATE_LOAD == nRet)
//STRIP001 /*?*/                     {
//STRIP001 /*?*/                         FileDialogHelper aDlgHelper( TemplateDescription::FILEOPEN_SIMPLE, 0 );
//STRIP001 /*?*/                         Reference < XFilePicker > xFP = aDlgHelper.GetFilePicker();
//STRIP001 /*?*/
//STRIP001 /*?*/                         xFP->setDisplayDirectory( aPathOpt.GetWorkPath() );
//STRIP001 /*?*/
//STRIP001 /*?*/                         SfxObjectFactory &rFact = GetFactory();
//STRIP001 /*?*/                         Reference<XFilterManager> xFltMgr(xFP, UNO_QUERY);
//STRIP001 /*?*/                         for( USHORT i = 0; i < rFact.GetFilterCount(); i++ )
//STRIP001 /*?*/                         {
//STRIP001 /*?*/                             const SfxFilter* pFlt = rFact.GetFilter( i );
//STRIP001 /*?*/                             if( pFlt && pFlt->IsAllowedAsTemplate() )
//STRIP001 /*?*/                             {
//STRIP001 /*?*/                                 const String sWild = ((WildCard&)pFlt->GetWildcard()).GetWildCard();
//STRIP001 /*?*/                                 xFltMgr->appendFilter( pFlt->GetUIName(), sWild );
//STRIP001 /*?*/                             }
//STRIP001 /*?*/
//STRIP001 /*?*/                             if( pFlt->GetUserData().EqualsAscii( FILTER_XML ))
//STRIP001 /*?*/                                 xFltMgr->setCurrentFilter( pFlt->GetUIName() ) ;
//STRIP001 /*?*/
//STRIP001 /*?*/                         }
//STRIP001 /*?*/
//STRIP001 /*?*/                         if( ERRCODE_NONE == aDlgHelper.Execute() )
//STRIP001 /*?*/                         {
//STRIP001 /*?*/                             aFileName = xFP->getFiles().getConstArray()[0];
//STRIP001 /*?*/                         }
//STRIP001 /*?*/                     }
//STRIP001 /*?*/                     else
//STRIP001 /*?*/                     {
//STRIP001 /*?*/                         aFileName = pNewFileDlg->GetTemplateFileName();
//STRIP001 /*?*/                     }
//STRIP001 /*?*/
//STRIP001 /*?*/                     nFlags = pNewFileDlg->GetTemplateFlags();
//STRIP001 /*?*/                     rReq.AppendItem( SfxStringItem( SID_TEMPLATE_NAME, aFileName ) );
//STRIP001 /*?*/                     rReq.AppendItem( SfxInt32Item( SID_TEMPLATE_LOAD, (long) nFlags ) );
//STRIP001 /*?*/                     delete pNewFileDlg;
//STRIP001 /*?*/                 }
//STRIP001 /*?*/
//STRIP001 /*?*/                 SwgReaderOption aOpt;
//STRIP001 /*?*/                 aOpt.SetTxtFmts(    bText = (0 != (nFlags&SFX_LOAD_TEXT_STYLES) ));
//STRIP001 /*?*/                 aOpt.SetFrmFmts(    bFrame = (0 != (nFlags&SFX_LOAD_FRAME_STYLES)));
//STRIP001 /*?*/                 aOpt.SetPageDescs(  bPage = (0 != (nFlags&SFX_LOAD_PAGE_STYLES )));
//STRIP001 /*?*/                 aOpt.SetNumRules(   bNum = (0 != (nFlags&SFX_LOAD_NUM_STYLES  )));
//STRIP001 /*?*/                 //different meaning between SFX_MERGE_STYLES and aOpt.SetMerge!
//STRIP001 /*?*/                 bMerge = 0 != (nFlags&SFX_MERGE_STYLES);
//STRIP001 /*?*/                 aOpt.SetMerge( !bMerge );
//STRIP001 /*?*/
//STRIP001 /*?*/                 if( aFileName.Len() )
//STRIP001 /*?*/                 {
//STRIP001 /*?*/                    SetError( LoadStylesFromFile( aFileName, aOpt, FALSE ));
//STRIP001 /*?*/                     if ( !GetError() )
//STRIP001 /*?*/                         rReq.Done();
//STRIP001 /*?*/                 }
//STRIP001 /*?*/             }
//STRIP001 /*?*/            break;
//STRIP001 /*?*/            case SID_SOURCEVIEW:
//STRIP001 /*?*/            {
//STRIP001 /*?*/                SfxViewShell* pViewShell = GetView()
//STRIP001 /*?*/                                            ? (SfxViewShell*)GetView()
//STRIP001 /*?*/                                            : SfxViewShell::Current();
//STRIP001 /*?*/                SfxViewFrame*  pViewFrm = pViewShell->GetViewFrame();
//STRIP001 /*?*/                SwSrcView* pSrcView = PTR_CAST(SwSrcView, pViewShell);
//STRIP001 /*?*/                if(!pSrcView)
//STRIP001 /*?*/                {
//STRIP001 /*?*/                     // 3 possible state:
//STRIP001 /*?*/                     // 1 - file unsaved -> save as HTML
//STRIP001 /*?*/                     // 2 - file modified and HTML filter active -> save
//STRIP001 /*?*/                     // 3 - file saved in non-HTML -> QueryBox to save as HTML
//STRIP001 /*?*/                     const SfxFilter* pHtmlFlt =
//STRIP001 /*?*/                                     SwIoSystem::GetFilterOfFormat(
//STRIP001 /*?*/                                         String::CreateFromAscii("HTML"),
//STRIP001 /*?*/                                         SwWebDocShell::Factory().GetFilterContainer() );
//STRIP001 /*?*/                     BOOL bHasName = HasName();
//STRIP001 /*?*/                     if(bHasName)
//STRIP001 /*?*/                     {
//STRIP001 /*?*/                         //check for filter type
//STRIP001 /*?*/                         const SfxFilter* pFlt = GetMedium()->GetFilter();
//STRIP001 /*?*/                         if(!pFlt || pFlt->GetUserData() != pHtmlFlt->GetUserData())
//STRIP001 /*?*/                         {
//STRIP001 /*?*/                             QueryBox aQuery(&pViewFrm->GetWindow(), SW_RES(MSG_SAVEAS_HTML_QUERY));
//STRIP001 /*?*/                             if(RET_YES == aQuery.Execute())
//STRIP001 /*?*/                                 bHasName = FALSE;
//STRIP001 /*?*/                             else
//STRIP001 /*?*/                                 break;
//STRIP001 /*?*/                         }
//STRIP001 /*?*/                     }
//STRIP001 /*?*/                     if(!bHasName)
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                         FileDialogHelper aDlgHelper( TemplateDescription::FILESAVE_AUTOEXTENSION, 0 );
//STRIP001 /*?*/                         aDlgHelper.AddFilter( pHtmlFlt->GetFilterName(), pHtmlFlt->GetDefaultExtension() );
//STRIP001 /*?*/                         aDlgHelper.SetCurrentFilter( pHtmlFlt->GetFilterName() );
//STRIP001 /*?*/                        if( ERRCODE_NONE != aDlgHelper.Execute())
//STRIP001 /*?*/                         {
//STRIP001 /*?*/                             break;
//STRIP001 /*?*/                         }
//STRIP001 /*?*/                         String sPath = aDlgHelper.GetPath();
//STRIP001 /*?*/                         SfxStringItem aName(SID_FILE_NAME, sPath);
//STRIP001 /*?*/                         SfxStringItem aFilter(SID_FILTER_NAME, pHtmlFlt->GetName());
//STRIP001 /*?*/                         const SfxBoolItem* pBool = (const SfxBoolItem*)
//STRIP001 /*?*/                                pViewFrm->GetDispatcher()->Execute(
//STRIP001 /*?*/                                         SID_SAVEASDOC, SFX_CALLMODE_SYNCHRON, &aName, &aFilter, 0L );
//STRIP001 /*?*/                        if(!pBool || !pBool->GetValue())
//STRIP001 /*?*/                             break;
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                    else
//STRIP001 /*?*/                         DoSave();
//STRIP001 /*?*/                }
//STRIP001 /*?*/ #ifdef DBG_UTIL
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    BOOL bWeb = 0 != PTR_CAST(SwWebDocShell, this);
//STRIP001 /*?*/                    DBG_ASSERT(bWeb == TRUE, "SourceView nur in der WebDocShell")
//STRIP001 /*?*/                }
//STRIP001 /*?*/ #endif
//STRIP001 /*?*/                // die SourceView ist fuer die SwWebDocShell die 1
//STRIP001 /*?*/                USHORT nSlot = SID_VIEWSHELL1;
//STRIP001 /*?*/                BOOL bSetModified = FALSE;
//STRIP001 /*?*/                SfxPrinter* pSavePrinter = 0;
//STRIP001 /*?*/                if( 0 != pSrcView)
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    SfxPrinter* pTemp = GetDoc()->GetPrt(FALSE);
//STRIP001 /*?*/                    if(pTemp)
//STRIP001 /*?*/                        pSavePrinter = new SfxPrinter(*pTemp);
//STRIP001 /*?*/                    bSetModified = IsModified() || pSrcView->IsModified();
//STRIP001 /*?*/                    if(pSrcView->IsModified()||pSrcView->HasSourceSaved())
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        utl::TempFile aTempFile;
//STRIP001 /*?*/                        aTempFile.EnableKillingFile();
//STRIP001 /*?*/                        pSrcView->SaveContent(aTempFile.GetURL());
//STRIP001 /*?*/                        bDone = TRUE;
//STRIP001 /*?*/                        SetActualSize(pSrcView->GetEditWin().GetSizePixel());
//STRIP001 /*?*/                        SfxEventConfiguration* pEvent = SFX_APP()->GetEventConfig();
//STRIP001 /*?*/                        SvxMacro aMac(aEmptyStr, aEmptyStr, STARBASIC);
//STRIP001 /*?*/                        pEvent->ConfigureEvent(SFX_EVENT_OPENDOC,       aMac, this);
//STRIP001 /*?*/                        pEvent->ConfigureEvent(SFX_EVENT_CLOSEDOC,      aMac, this);
//STRIP001 /*?*/                        pEvent->ConfigureEvent(SFX_EVENT_ACTIVATEDOC,   aMac, this);
//STRIP001 /*?*/                        pEvent->ConfigureEvent(SFX_EVENT_DEACTIVATEDOC, aMac, this);
//STRIP001 /*?*/                        ReloadFromHtml(aTempFile.GetURL(), pSrcView);
//STRIP001 /*?*/                        nSlot = 0;
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                    else
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        nSlot = SID_VIEWSHELL0;
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                }
//STRIP001  /*   OS 10.04.97 14.20: Im Web-Writer gibt es keinen Unterschied zwischen
//STRIP001                          Export in den SourceMode und dem Speichern des Docs
//STRIP001                  else if(IsModified())
//STRIP001                  {
//STRIP001                      USHORT nRet = QueryBox( SFX_APPWINDOW ,SW_RES(MSG_SAVE_HTML_QUERY)).Execute();
//STRIP001                      if(RET_YES == nRet)
//STRIP001                      {
//STRIP001                          S F X _DISPATCHER().Execute(SID_SAVEDOC,
//STRIP001                                      SFX_CALLMODE_SYNCHRON);
//STRIP001                          // der ReturnValue von SID_SAVEDOC ist etwas schwer verstaendlich
//STRIP001                          if(IsModified())
//STRIP001                              nSlot = 0;
//STRIP001                      }
//STRIP001                      else if( RET_CANCEL == nRet )
//STRIP001                      {
//STRIP001                          nSlot = 0;
//STRIP001                      }
//STRIP001                  }*/
//STRIP001 /*?*/                if(nSlot)
//STRIP001 /*?*/                    pViewFrm->GetDispatcher()->Execute(nSlot, SFX_CALLMODE_SYNCHRON);
//STRIP001 /*?*/                if(bSetModified)
//STRIP001 /*?*/                    GetDoc()->SetModified();
//STRIP001 /*?*/                if(pSavePrinter)
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    GetDoc()->SetPrt(pSavePrinter);
//STRIP001 /*?*/                    //pSavePrinter darf nicht wieder geloescht werden
//STRIP001 /*?*/                }
//STRIP001 /*?*/                pViewFrm->GetBindings().SetState(SfxBoolItem(SID_SOURCEVIEW, nSlot == SID_VIEWSHELL2));
//STRIP001 /*?*/            }
//STRIP001 /*?*/            break;
//STRIP001 /*?*/            case SID_GET_COLORTABLE:
//STRIP001 /*?*/            {
//STRIP001 /*?*/                SvxColorTableItem* pColItem = (SvxColorTableItem*)GetItem(SID_COLOR_TABLE);
//STRIP001 /*?*/                XColorTable* pTable = pColItem->GetColorTable();
//STRIP001 /*?*/                rReq.SetReturnValue(OfaPtrItem(SID_GET_COLORTABLE, pTable));
//STRIP001 /*?*/            }
//STRIP001 /*?*/            break;
//STRIP001 /*?*/        case FN_ABSTRACT_STARIMPRESS:
//STRIP001 /*?*/        case FN_ABSTRACT_NEWDOC:
//STRIP001 /*?*/        {
//STRIP001 /*?*/            SwInsertAbstractDlg* pDlg = new SwInsertAbstractDlg(0);
//STRIP001 /*?*/            if(RET_OK == pDlg->Execute())
//STRIP001 /*?*/            {
//STRIP001 /*?*/                BYTE nLevel = pDlg->GetLevel();
//STRIP001 /*?*/                BYTE nPara = pDlg->GetPara();
//STRIP001 /*?*/                SwDoc* pSmryDoc = new SwDoc();
//STRIP001 /*?*/                SfxObjectShellRef xDocSh( new SwDocShell( pSmryDoc, SFX_CREATE_MODE_STANDARD));
//STRIP001 /*?*/                xDocSh->DoInitNew( 0 );
//STRIP001 /*?*/
//STRIP001 /*?*/                 /*TODO #111050# call public made method of sfx (which was protected before!)
//STRIP001 /*?*/                   to force missing event OnNew ... */
//STRIP001 /*?*/                 xDocSh->Stamp_SetActivateEvent(SFX_EVENT_CREATEDOC);
//STRIP001 /*?*/
//STRIP001 /*?*/                BOOL bImpress = FN_ABSTRACT_STARIMPRESS == nWhich;
//STRIP001 /*?*/                pDoc->Summary( pSmryDoc, nLevel, nPara, bImpress );
//STRIP001 /*?*/                if( bImpress )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    WriterRef xWrt;
//STRIP001 /*?*/                    ::GetRTFWriter( aEmptyStr, xWrt );
//STRIP001 /*?*/                    SvMemoryStream *pStrm = new SvMemoryStream();
//STRIP001 /*?*/                    pStrm->SetBufferSize( 16348 );
//STRIP001 /*?*/                    SwWriter aWrt( *pStrm, *pSmryDoc );
//STRIP001 /*?*/                    ErrCode eErr = aWrt.Write( xWrt );
//STRIP001 /*?*/                    if( !ERRCODE_TOERROR( eErr ) )
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        pStrm->Seek( STREAM_SEEK_TO_END );
//STRIP001 /*?*/                        *pStrm << '\0';
//STRIP001 /*?*/                        pStrm->Seek( STREAM_SEEK_TO_BEGIN );
//STRIP001 /*?*/                        //Die Lockbytes werden owner des Stream*
//STRIP001 /*?*/                        SvLockBytes *pLockBytes = new SvLockBytes( pStrm, TRUE );
//STRIP001 /*?*/                        //Das Item wird owner des LockBytes*
//STRIP001 /*?*/                        SfxLockBytesItem aItem( SID_OUTLINE_TO_IMPRESS, pLockBytes );
//STRIP001 /*?*/                        SfxModule *pMod = (*(SfxModule**)GetAppData(BF_SHL_DRAW))->Load();
//STRIP001 /*?*/                        SfxItemSet aSet( pMod->GetPool(), SID_OUTLINE_TO_IMPRESS,
//STRIP001 /*?*/                                                            SID_OUTLINE_TO_IMPRESS );
//STRIP001 /*?*/                        aSet.Put( aItem );
//STRIP001 /*?*/                        SfxAllItemSet aArgs( pMod->GetPool() );
//STRIP001 /*?*/                        aArgs.Put( aSet );
//STRIP001 /*?*/                        SfxRequest aReq( SID_OUTLINE_TO_IMPRESS, 0, aArgs );
//STRIP001 /*?*/                        pMod->ExecuteSlot( aReq );
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                    else
//STRIP001 /*?*/                        ErrorHandler::HandleError(ErrCode( eErr ));
//STRIP001 /*?*/                }
//STRIP001 /*?*/                else
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    // Neues Dokument erzeugen.
//STRIP001 /*?*/                    SfxViewFrame *pFrame = SFX_APP()->CreateViewFrame( *xDocSh, 0 );
//STRIP001 /*?*/                    SwView      *pView = (SwView*) pFrame->GetViewShell();
//STRIP001 /*?*/
//STRIP001 /*?*/                    // Dokumenttitel setzen
//STRIP001 /*?*/                    String aTmp( SW_RES(STR_ABSTRACT_TITLE) );
//STRIP001 /*?*/                    aTmp += GetTitle();
//STRIP001 /*?*/                    xDocSh->SetTitle( aTmp );
//STRIP001 /*?*/                    pView->GetWrtShell().SetNewDoc();
//STRIP001 /*?*/                    pFrame->Show();
//STRIP001 /*?*/                    pSmryDoc->SetModified();
//STRIP001 /*?*/                }
//STRIP001 /*?*/
//STRIP001 /*?*/            }
//STRIP001 /*?*/            delete pDlg;
//STRIP001 /*?*/        }
//STRIP001 /*?*/        break;
//STRIP001 /*?*/        case FN_OUTLINE_TO_CLIPBOARD:
//STRIP001 /*?*/        case FN_OUTLINE_TO_IMPRESS:
//STRIP001 /*?*/            {
//STRIP001 /*?*/                WriterRef xWrt;
//STRIP001 /*?*/                ::GetRTFWriter( 'O', xWrt );
//STRIP001 /*?*/                SvMemoryStream *pStrm = new SvMemoryStream();
//STRIP001 /*?*/                pStrm->SetBufferSize( 16348 );
//STRIP001 /*?*/                SwWriter aWrt( *pStrm, *GetDoc() );
//STRIP001 /*?*/                ErrCode eErr = aWrt.Write( xWrt );
//STRIP001 /*?*/                if( !ERRCODE_TOERROR( eErr ) )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    pStrm->Seek( STREAM_SEEK_TO_END );
//STRIP001 /*?*/                    *pStrm << '\0';
//STRIP001 /*?*/                    pStrm->Seek( STREAM_SEEK_TO_BEGIN );
//STRIP001 /*?*/                    if ( nWhich == FN_OUTLINE_TO_IMPRESS )
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        //Die Lockbytes werden owner des Stream*
//STRIP001 /*?*/                        SvLockBytes *pLockBytes = new SvLockBytes( pStrm, TRUE );
//STRIP001 /*?*/                        //Das Item wird owner des LockBytes*
//STRIP001 /*?*/                        SfxLockBytesItem aItem( SID_OUTLINE_TO_IMPRESS, pLockBytes );
//STRIP001 /*?*/                        SfxModule *pMod = (*(SfxModule**)GetAppData(BF_SHL_DRAW))->Load();
//STRIP001 /*?*/                        SfxItemSet aSet( pMod->GetPool(), SID_OUTLINE_TO_IMPRESS,
//STRIP001 /*?*/                                                          SID_OUTLINE_TO_IMPRESS );
//STRIP001 /*?*/                        aSet.Put( aItem );
//STRIP001 /*?*/                        SfxAllItemSet aArgs( pMod->GetPool() );
//STRIP001 /*?*/                        aArgs.Put( aSet );
//STRIP001 /*?*/                        SfxRequest aReq( SID_OUTLINE_TO_IMPRESS, 0, aArgs );
//STRIP001 /*?*/                        pMod->ExecuteSlot( aReq );
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                    else
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        TransferDataContainer* pClipCntnr =
//STRIP001 /*?*/                                                    new TransferDataContainer;
//STRIP001 /*?*/                        STAR_REFERENCE( datatransfer::XTransferable )
//STRIP001 /*?*/                                                        xRef( pClipCntnr );
//STRIP001 /*?*/
//STRIP001 /*?*/                        pClipCntnr->CopyAnyData( FORMAT_RTF, (sal_Char*)
//STRIP001 /*?*/                                        pStrm->GetData(), pStrm->GetSize() );
//STRIP001 /*?*/                        pClipCntnr->CopyToClipboard(
//STRIP001 /*?*/                            GetView()? (Window*)&GetView()->GetEditWin() : 0 );
//STRIP001 /*?*/                        delete pStrm;
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                }
//STRIP001 /*?*/                else
//STRIP001 /*?*/                    ErrorHandler::HandleError(ErrCode( eErr ));
//STRIP001 /*?*/            }
//STRIP001 /*?*/            break;
//STRIP001 /*?*/            case SID_SPELLCHECKER_CHANGED:
//STRIP001 /*?*/                //! FALSE, TRUE, TRUE is on the save side but a probably overdone
//STRIP001 /*?*/                SW_MOD()->CheckSpellChanges(FALSE, TRUE, TRUE );
//STRIP001 /*?*/            break;
//STRIP001 /*?*/
//STRIP001 /*?*/            case SID_BROWSER_MODE:
//STRIP001 /*?*/            case FN_PRINT_LAYOUT:   //Fuer Web, genau umgekehrt zum BrowserMode
//STRIP001 /*?*/            {
//STRIP001 /*?*/                int eState = STATE_TOGGLE;
//STRIP001 /*?*/                BOOL bSet;
//STRIP001 /*?*/                const SfxPoolItem* pAttr=NULL;
//STRIP001 /*?*/                if ( pArgs && SFX_ITEM_SET == pArgs->GetItemState( nWhich , FALSE, &pAttr ))
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    bSet = ((SfxBoolItem*)pAttr)->GetValue();
//STRIP001 /*?*/                    if ( nWhich == FN_PRINT_LAYOUT )
//STRIP001 /*?*/                        bSet = !bSet;
//STRIP001 /*?*/                    eState = bSet ? STATE_ON : STATE_OFF;
//STRIP001 /*?*/                }
//STRIP001 /*?*/
//STRIP001 /*?*/                if ( STATE_TOGGLE == eState )
//STRIP001 /*?*/                    bSet = !GetDoc()->IsBrowseMode();
//STRIP001 /*?*/
//STRIP001 /*?*/                ToggleBrowserMode(bSet, 0);
//STRIP001 /*?*/
//STRIP001 /*?*/                // OS: numerische Reihenfolge beachten!
//STRIP001 /*?*/                static USHORT __READONLY_DATA aInva[] =
//STRIP001 /*?*/                                    {
//STRIP001 /*?*/                                         SID_NEWWINDOW,/*5620*/
//STRIP001 /*?*/                                         SID_BROWSER_MODE, /*6313*/
//STRIP001 /*?*/                                        SID_RULER_BORDERS, SID_RULER_PAGE_POS,
//STRIP001 /*?*/                                        SID_ATTR_LONG_LRSPACE,
//STRIP001 /*?*/                                        SID_HTML_MODE,
//STRIP001 /*?*/                                        SID_RULER_PROTECT,
//STRIP001 /*?*/                                        SID_AUTOSPELL_CHECK,
//STRIP001 /*?*/                                        SID_AUTOSPELL_MARKOFF,
//STRIP001 /*?*/                                        FN_RULER,       /*20211*/
//STRIP001 /*?*/                                         FN_VIEW_GRAPHIC,    /*20213*/
//STRIP001 /*?*/                                        FN_VIEW_BOUNDS,     /**/
//STRIP001 /*?*/                                         FN_VIEW_FIELDS,     /*20215*/
//STRIP001 /*?*/                                         FN_VLINEAL,             /*20216*/
//STRIP001 /*?*/                                         FN_VSCROLLBAR,      /*20217*/
//STRIP001 /*?*/                                         FN_HSCROLLBAR,      /*20218*/
//STRIP001 /*?*/                                         FN_VIEW_META_CHARS, /**/
//STRIP001 /*?*/                                        FN_VIEW_MARKS,      /**/
//STRIP001 /*?*/                                        FN_VIEW_FIELDNAME,  /**/
//STRIP001 /*?*/                                         FN_VIEW_TABLEGRID,  /*20227*/
//STRIP001 /*?*/                                         FN_PRINT_LAYOUT, /*20237*/
//STRIP001 /*?*/                                         FN_QRY_MERGE,   /*20364*/
//STRIP001 /*?*/                                        FN_STAT_HYPERLINKS, /*21186*/
//STRIP001 /*?*/                                        FN_INSERT_HEADER, /*21405*/
//STRIP001 /*?*/                                        FN_INSERT_FOOTER, /*21406*/
//STRIP001 /*?*/                                         0
//STRIP001 /*?*/                                    };
//STRIP001 /*?*/                // the view must not exist!
//STRIP001 /*?*/                SfxViewFrame *pTmpFrm = SfxViewFrame::GetFirst( this );
//STRIP001 /*?*/                if( pTmpFrm )
//STRIP001 /*?*/                    pTmpFrm->GetBindings().Invalidate( aInva );
//STRIP001 /*?*/                if ( !pAttr )
//STRIP001 /*?*/                    rReq.AppendItem( SfxBoolItem( nWhich, bSet ) );
//STRIP001 /*?*/                rReq.Done();
//STRIP001 /*?*/            }
//STRIP001 /*?*/            break;
//STRIP001 /*?*/
//STRIP001 /*?*/        case SID_MAIL_PREPAREEXPORT:
//STRIP001 /*?*/            {
//STRIP001 /*?*/                //pWrtShell is not set in page preview
//STRIP001 /*?*/                if(pWrtShell)
//STRIP001 /*?*/                    pWrtShell->StartAllAction();
//STRIP001 /*?*/                pDoc->UpdateFlds( 0 );
//STRIP001 /*?*/                pDoc->EmbedAllLinks();
//STRIP001 /*?*/                pDoc->RemoveInvisibleContent();
//STRIP001 /*?*/                if(pWrtShell)
//STRIP001 /*?*/                    pWrtShell->EndAllAction();
//STRIP001 /*?*/            }
//STRIP001 /*?*/            break;
//STRIP001 /*?*/
//STRIP001 /*?*/        case FN_NEW_HTML_DOC:
//STRIP001 /*?*/        case FN_NEW_GLOBAL_DOC:
//STRIP001 /*?*/            {
//STRIP001 /*?*/                bDone = FALSE;
//STRIP001 /*?*/                 BOOL bCreateHtml = FN_NEW_HTML_DOC == nWhich;
//STRIP001 /*?*/                 String aFileName, aTemplateName;
//STRIP001 /*?*/                 if( pArgs && SFX_ITEM_SET == pArgs->GetItemState( nWhich, FALSE, &pItem ) )
//STRIP001 /*?*/                 {
//STRIP001 /*?*/                     aFileName = ((const SfxStringItem*)pItem)->GetValue();
//STRIP001 /*?*/                     SFX_ITEMSET_ARG( pArgs, pTemplItem, SfxStringItem, SID_TEMPLATE_NAME, sal_False );
//STRIP001 /*?*/                     if ( pTemplItem )
//STRIP001 /*?*/                         aTemplateName = pTemplItem->GetValue();
//STRIP001 /*?*/                 }
//STRIP001 /*?*/
//STRIP001 /*?*/                 if ( !aFileName.Len() )
//STRIP001 /*?*/                 {
//STRIP001 /*?*/                     FileDialogHelper aDlgHelper( TemplateDescription::FILESAVE_AUTOEXTENSION_TEMPLATE, 0 );
//STRIP001 /*?*/                     //set HelpIds
//STRIP001 /*?*/                     const sal_Int16 nControlIds[] = {
//STRIP001 /*?*/                         CommonFilePickerElementIds::PUSHBUTTON_OK,
//STRIP001 /*?*/                         CommonFilePickerElementIds::PUSHBUTTON_CANCEL,
//STRIP001 /*?*/                         CommonFilePickerElementIds::LISTBOX_FILTER,
//STRIP001 /*?*/                         CommonFilePickerElementIds::CONTROL_FILEVIEW,
//STRIP001 /*?*/                         CommonFilePickerElementIds::EDIT_FILEURL,
//STRIP001 /*?*/                         ExtendedFilePickerElementIds::CHECKBOX_AUTOEXTENSION,
//STRIP001 /*?*/                         ExtendedFilePickerElementIds::LISTBOX_TEMPLATE,
//STRIP001 /*?*/                         0
//STRIP001 /*?*/                     };
//STRIP001 /*?*/                     sal_Int32 nHelpIds[8];
//STRIP001 /*?*/                     sal_Int32 nStartHelpId =
//STRIP001 /*?*/                         bCreateHtml ?
//STRIP001 /*?*/                             HID_SEND_HTML_CTRL_PUSHBUTTON_OK : HID_SEND_MASTER_CTRL_PUSHBUTTON_OK ;
//STRIP001 /*?*/                     for(int nHelp = 0; nHelp < 7; nHelp++)
//STRIP001 /*?*/                         nHelpIds[nHelp] = nStartHelpId++;
//STRIP001 /*?*/                     nHelpIds[7] = 0;
//STRIP001 /*?*/
//STRIP001 /*?*/                     aDlgHelper.SetControlHelpIds( nControlIds, nHelpIds );
//STRIP001 /*?*/ //                    aDlgHelper.SetDialogHelpId( bCreateHtml ? HID_SEND_HTML_DIALOG : HID_SEND_MASTER_DIALOG );
//STRIP001 /*?*/
//STRIP001 /*?*/                     Reference < XFilePicker > xFP = aDlgHelper.GetFilePicker();
//STRIP001 /*?*/
//STRIP001 /*?*/                     const SfxFilter* pFlt;
//STRIP001 /*?*/                     USHORT nStrId;
//STRIP001 /*?*/
//STRIP001 /*?*/                     if( bCreateHtml )
//STRIP001 /*?*/                     {
//STRIP001 /*?*/                         // fuer HTML gibts es nur einen Filter!!
//STRIP001 /*?*/                         pFlt = SwIoSystem::GetFilterOfFormat(
//STRIP001 /*?*/                                 String::CreateFromAscii("HTML"),
//STRIP001 /*?*/                                 SwWebDocShell::Factory().GetFilterContainer() );
//STRIP001 /*?*/                         nStrId = STR_LOAD_HTML_DOC;
//STRIP001 /*?*/                     }
//STRIP001 /*?*/                     else
//STRIP001 /*?*/                     {
//STRIP001 /*?*/                         // Fuer Global-Dokumente bieten wir jetzt auch nur
//STRIP001 /*?*/                         // noch den aktuellen an.
//STRIP001 /*?*/                         pFlt = SwIoSystem::GetFilterOfFormat(
//STRIP001 /*?*/                                 String::CreateFromAscii(FILTER_XML),
//STRIP001 /*?*/                                 SwGlobalDocShell::Factory().GetFilterContainer() );
//STRIP001 /*?*/                         nStrId = STR_LOAD_GLOBAL_DOC;
//STRIP001 /*?*/                     }
//STRIP001 /*?*/
//STRIP001 /*?*/                     if( pFlt )
//STRIP001 /*?*/                     {
//STRIP001 /*?*/                         Reference<XFilterManager> xFltMgr(xFP, UNO_QUERY);
//STRIP001 /*?*/                         const String sWild = ((WildCard&)pFlt->GetWildcard()).GetWildCard();
//STRIP001 /*?*/                         xFltMgr->appendFilter( pFlt->GetUIName(), sWild );
//STRIP001 /*?*/                         xFltMgr->setCurrentFilter( pFlt->GetUIName() ) ;
//STRIP001 /*?*/                     }
//STRIP001 /*?*/
//STRIP001 /*?*/                     Reference<XFilePickerControlAccess> xCtrlAcc(xFP, UNO_QUERY);
//STRIP001 /*?*/                     const USHORT nCount = pDoc->GetTxtFmtColls()->Count();
//STRIP001 /*?*/                     Sequence<OUString> aListBoxEntries(nCount);
//STRIP001 /*?*/                     OUString* pEntries = aListBoxEntries.getArray();
//STRIP001 /*?*/                     sal_Int32 nIdx = 0;
//STRIP001 /*?*/                     sal_Int16 nSelect = 0;
//STRIP001 /*?*/                     OUString sStartTemplate;
//STRIP001 /*?*/                     SwTxtFmtColl *pFnd = 0, *pAny = 0;
//STRIP001 /*?*/                     for(USHORT i = 0; i < nCount; ++i)
//STRIP001 /*?*/                     {
//STRIP001 /*?*/                         SwTxtFmtColl &rTxtColl =
//STRIP001 /*?*/                                         *pDoc->GetTxtFmtColls()->GetObject( i );
//STRIP001 /*?*/                         if( !rTxtColl.IsDefault() && rTxtColl.IsAtDocNodeSet() )
//STRIP001 /*?*/                         {
//STRIP001 /*?*/                             if( MAXLEVEL >= rTxtColl.GetOutlineLevel() && ( !pFnd ||
//STRIP001 /*?*/                                 pFnd->GetOutlineLevel() > rTxtColl.GetOutlineLevel() ))
//STRIP001 /*?*/                             {
//STRIP001 /*?*/                                     nSelect = (sal_Int16)nIdx;
//STRIP001 /*?*/                                     pFnd = &rTxtColl;
//STRIP001 /*?*/                                     sStartTemplate = rTxtColl.GetName();
//STRIP001 /*?*/                             }
//STRIP001 /*?*/                             else if( !pAny )
//STRIP001 /*?*/                                 pAny = &rTxtColl;
//STRIP001 /*?*/                             pEntries[nIdx++] = rTxtColl.GetName();
//STRIP001 /*?*/                         }
//STRIP001 /*?*/                     }
//STRIP001 /*?*/                     if(!sStartTemplate.getLength() && pAny)
//STRIP001 /*?*/                         sStartTemplate = pAny->GetName();
//STRIP001 /*?*/
//STRIP001 /*?*/                     aListBoxEntries.realloc(nIdx);
//STRIP001 /*?*/
//STRIP001 /*?*/                     try
//STRIP001 /*?*/                     {
//STRIP001 /*?*/                         Any aTemplates(&aListBoxEntries, ::getCppuType(&aListBoxEntries));
//STRIP001 /*?*/
//STRIP001 /*?*/                         xCtrlAcc->setValue( ExtendedFilePickerElementIds::LISTBOX_TEMPLATE,
//STRIP001 /*?*/                             ListboxControlActions::ADD_ITEMS , aTemplates );
//STRIP001 /*?*/                         Any aSelectPos(&nSelect, ::getCppuType(&nSelect));
//STRIP001 /*?*/                         xCtrlAcc->setValue( ExtendedFilePickerElementIds::LISTBOX_TEMPLATE,
//STRIP001 /*?*/                             ListboxControlActions::SET_SELECT_ITEM, aSelectPos );
//STRIP001 /*?*/                         xCtrlAcc->setLabel( ExtendedFilePickerElementIds::LISTBOX_TEMPLATE,
//STRIP001 /*?*/                                                 String(SW_RES( STR_FDLG_TEMPLATE_NAME )));
//STRIP001 /*?*/                     }
//STRIP001 /*?*/                     catch(Exception& rEx)
//STRIP001 /*?*/                     {
//STRIP001 /*?*/                         DBG_ERROR("control acces failed")
//STRIP001 /*?*/                     }
//STRIP001 /*?*/
//STRIP001 /*?*/                     xFP->setTitle( SW_RESSTR( nStrId ));
//STRIP001 /*?*/                     SvtPathOptions aPathOpt;
//STRIP001 /*?*/                     xFP->setDisplayDirectory( aPathOpt.GetWorkPath() );
//STRIP001 /*?*/                     if( ERRCODE_NONE == aDlgHelper.Execute())
//STRIP001 /*?*/                     {
//STRIP001 /*?*/                         aFileName = xFP->getFiles().getConstArray()[0];
//STRIP001 /*?*/                         Any aTemplateValue = xCtrlAcc->getValue(
//STRIP001 /*?*/                             ExtendedFilePickerElementIds::LISTBOX_TEMPLATE,
//STRIP001 /*?*/                             ListboxControlActions::GET_SELECTED_ITEM );
//STRIP001 /*?*/                         OUString sTmpl;
//STRIP001 /*?*/                         aTemplateValue >>= sTmpl;
//STRIP001 /*?*/                         aTemplateName = sTmpl;
//STRIP001 /*?*/                         if ( aFileName.Len() )
//STRIP001 /*?*/                         {
//STRIP001 /*?*/                             rReq.AppendItem( SfxStringItem( nWhich, aFileName ) );
//STRIP001 /*?*/                             if( aTemplateName.Len() )
//STRIP001 /*?*/                                 rReq.AppendItem( SfxStringItem( SID_TEMPLATE_NAME, aTemplateName ) );
//STRIP001 /*?*/                         }
//STRIP001 /*?*/                     }
//STRIP001 /*?*/                 }
//STRIP001 /*?*/
//STRIP001 /*?*/                const SwTxtFmtColl* pSplitColl = 0;
//STRIP001 /*?*/                 if ( aTemplateName.Len() )
//STRIP001 /*?*/                     pSplitColl = pDoc->FindTxtFmtCollByName(aTemplateName);
//STRIP001 /*?*/
//STRIP001 /*?*/                if( aFileName.Len() )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    if( PrepareClose( FALSE ) )
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        SwWait aWait( *this, TRUE );
//STRIP001 /*?*/                        bDone = bCreateHtml
//STRIP001 /*?*/                            ? pDoc->GenerateHTMLDoc( aFileName, pSplitColl )
//STRIP001 /*?*/                            : pDoc->GenerateGlobalDoc( aFileName, pSplitColl );
//STRIP001 /*?*/
//STRIP001 /*?*/                        if( bDone )
//STRIP001 /*?*/                        {
//STRIP001 /*?*/                            SfxStringItem aName( SID_FILE_NAME, aFileName );
//STRIP001 /*?*/                            SfxStringItem aReferer( SID_REFERER, aEmptyStr );
//STRIP001 /*?*/                             SfxViewShell* pViewShell = SfxViewShell::GetFirst();
//STRIP001 /*?*/                             while(pViewShell)
//STRIP001 /*?*/                             {
//STRIP001 /*?*/                                 //search for the view that created the call
//STRIP001 /*?*/                                 if(pViewShell->GetObjectShell() == this && pViewShell->GetDispatcher())
//STRIP001 /*?*/                                 {
//STRIP001 /*?*/                                     SfxFrameItem* pFrameItem = new SfxFrameItem( SID_DOCFRAME,
//STRIP001 /*?*/                                                         pViewShell->GetViewFrame() );
//STRIP001 /*?*/                                     SfxDispatcher* pDispatch = pViewShell->GetDispatcher();
//STRIP001 /*?*/                                     pDispatch->Execute(
//STRIP001 /*?*/                                             SID_OPENDOC,
//STRIP001 /*?*/                                             SFX_CALLMODE_ASYNCHRON,
//STRIP001 /*?*/                                             &aName,
//STRIP001 /*?*/                                             &aReferer,
//STRIP001 /*?*/                                             pFrameItem, 0L );
//STRIP001 /*?*/
//STRIP001 /*?*/                                     delete pFrameItem;
//STRIP001 /*?*/                                     break;
//STRIP001 /*?*/                                 }
//STRIP001 /*?*/                                 pViewShell = SfxViewShell::GetNext(*pViewShell);
//STRIP001 /*?*/                             }
//STRIP001 /*?*/                         }
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                    if( !bDone && !rReq.IsAPI() )
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        InfoBox( 0, SW_RESSTR( STR_CANTCREATE )).Execute();
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                }
//STRIP001 /*?*/            }
//STRIP001 /*?*/            rReq.SetReturnValue(SfxBoolItem( nWhich, bDone ));
//STRIP001 /*?*/            if (bDone)
//STRIP001 /*?*/                rReq.Done();
//STRIP001 /*?*/            else
//STRIP001 /*?*/                rReq.Ignore();
//STRIP001 /*?*/            break;
//STRIP001 /*?*/
//STRIP001 /*?*/        case SID_ATTR_YEAR2000:
//STRIP001 /*?*/            if ( pArgs && SFX_ITEM_SET == pArgs->GetItemState( nWhich , FALSE, &pItem ))
//STRIP001 /*?*/            {
//STRIP001 /*?*/                DBG_ASSERT(pItem->ISA(SfxUInt16Item), "falsches Item")
//STRIP001 /*?*/                USHORT nYear2K = ((SfxUInt16Item*)pItem)->GetValue();
//STRIP001 /*?*/                //ueber Views iterieren und den State an den FormShells setzen
//STRIP001 /*?*/
//STRIP001 /*?*/                SfxViewFrame* pVFrame = SfxViewFrame::GetFirst( this );
//STRIP001 /*?*/                SfxViewShell* pViewShell = pVFrame ? pVFrame->GetViewShell() : 0;
//STRIP001 /*?*/                SwView* pView = PTR_CAST(SwView, pViewShell);
//STRIP001 /*?*/                while(pView)
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    FmFormShell* pFormShell = pView->GetFormShell();
//STRIP001 /*?*/                    if(pFormShell)
//STRIP001 /*?*/                        pFormShell->SetY2KState(nYear2K);
//STRIP001 /*?*/                    pVFrame = SfxViewFrame::GetNext( *pVFrame, this );
//STRIP001 /*?*/                    pViewShell = pVFrame ? pVFrame->GetViewShell() : 0;
//STRIP001 /*?*/                    pView = PTR_CAST(SwView, pViewShell);
//STRIP001 /*?*/                }
//STRIP001 /*?*/                pDoc->GetNumberFormatter(TRUE)->SetYear2000(nYear2K);
//STRIP001 /*?*/            }
//STRIP001 /*?*/        break;
//STRIP001 /*?*/
//STRIP001 /*?*/        default: DBG_ERROR("falscher Dispatcher");
//STRIP001 /*?*/    }
/*N*/ }


/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

//STRIP001 long SwDocShell::DdeGetData( const String& rItem, const String& rMimeType,
//STRIP001                              ::com::sun::star::uno::Any & rValue )
//STRIP001 {
//STRIP001  return pDoc->GetData( rItem, rMimeType, rValue );
//STRIP001 }


/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

//STRIP001 long SwDocShell::DdeSetData( const String& rItem, const String& rMimeType,
//STRIP001                          const ::com::sun::star::uno::Any & rValue )
//STRIP001 {
//STRIP001  return pDoc->SetData( rItem, rMimeType, rValue );
//STRIP001 }


/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

//STRIP001 ::so3::SvLinkSource* SwDocShell::DdeCreateLinkSource( const String& rItem )
//STRIP001 {
//STRIP001  return pDoc->CreateLinkSource( rItem );
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

/*N*/ void SwDocShell::FillClass( SvGlobalName * pClassName,
/*N*/                                  ULONG * pClipFormat,
/*N*/                                  String * pAppName,
/*N*/                                  String * pLongUserName,
/*N*/                                  String * pUserName,
/*N*/                                  long nVersion ) const
/*N*/ {
/*N*/   SfxInPlaceObject::FillClass(pClassName, pClipFormat, pAppName, pLongUserName,
/*N*/                               pUserName, nVersion);
/*N*/
/*N*/   if (nVersion == SOFFICE_FILEFORMAT_31)
/*N*/   {
/*N*/ //        *pClassName     = SvGlobalName(0xDC5C7E40L, 0xB35C, 0x101B, 0x99, 0x61,
//                                     0x04, 0x02, 0x1C, 0x00, 0x70,0x02);
/*N*/       *pClassName     = SvGlobalName( BF_SO3_SW_CLASSID_30 );

/*N*/       *pClipFormat    = SOT_FORMATSTR_ID_STARWRITER_30;
/*N*/       pAppName->AssignAscii( "Swriter 3.1" );
/*N*/       *pLongUserName  = SW_RESSTR(STR_WRITER_DOCUMENT_FULLTYPE_31);
/*N*/   }
/*N*/   else if (nVersion == SOFFICE_FILEFORMAT_40)
/*N*/   {
//        *pClassName       = SvGlobalName(0xDC5C7E40L, 0xB35C, 0x101B, 0x99, 0x61,
//                                     0x04, 0x02, 0x1C, 0x00, 0x70,0x02);
/*N*/       *pClassName     = SvGlobalName( BF_SO3_SW_CLASSID_40 );
/*N*/
/*N*/       *pClipFormat    = SOT_FORMATSTR_ID_STARWRITER_40;
/*N*/       pAppName->AssignAscii( "StarWriter 4.0" );
/*N*/       *pLongUserName  = SW_RESSTR(STR_WRITER_DOCUMENT_FULLTYPE_40);
/*N*/   }
/*N*/   else if (nVersion == SOFFICE_FILEFORMAT_50)
/*N*/   {
/*N*/       *pClassName     = SvGlobalName( BF_SO3_SW_CLASSID_50 );
/*N*/       *pClipFormat    = SOT_FORMATSTR_ID_STARWRITER_50;
/*N*/       *pLongUserName = SW_RESSTR(STR_WRITER_DOCUMENT_FULLTYPE_50);
/*N*/   }
/*N*/   else if (nVersion == SOFFICE_FILEFORMAT_60)
/*N*/   {
/*N*/       *pLongUserName = SW_RESSTR(STR_WRITER_DOCUMENT_FULLTYPE);

            // for binfilter, we need the FormatIDs to be set. Not setting them
            // has always been an error (!)
             *pClassName        = SvGlobalName( BF_SO3_SW_CLASSID_60 );
             *pClipFormat   = SOT_FORMATSTR_ID_STARWRITER_60;

/*N*/   }
/*N*/   *pUserName = SW_RESSTR(STR_HUMAN_SWDOC_NAME);
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

/*N*/ void SwDocShell::SetModified( BOOL bSet )
/*N*/ {
/*N*/   SfxInPlaceObject::SetModified( bSet );
/*N*/   if( IsEnableSetModified() && !pDoc->IsInCallModified() )
/*N*/   {
/*N*/       EnableSetModified( FALSE );
/*N*/
/*N*/       if( bSet )
/*N*/       {
/*N*/           BOOL bOld = pDoc->IsModified();
/*N*/           pDoc->SetModified();
/*N*/           if( !bOld )
/*?*/               pDoc->SetUndoNoResetModified();
/*N*/       }
/*N*/       else
/*N*/           pDoc->ResetModified();
/*N*/
/*N*/       EnableSetModified( TRUE );
/*N*/   }
/*N*/   UpdateChildWindows();
/*N*/   Broadcast(SfxSimpleHint(SFX_HINT_DOCCHANGED));
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

/*N*/ void SwDocShell::UpdateChildWindows()
/*N*/ {
/*N*/   // Flddlg ggf neu initialisieren (z.B. fuer TYP_SETVAR)
/*N*/   if(!GetView())
/*N*/       return;
/*N*/   SfxViewFrame* pVFrame = GetView()->GetViewFrame();
/*N*/   SwFldDlgWrapper *pWrp = (SwFldDlgWrapper*)pVFrame->
/*N*/           GetChildWindow( SwFldDlgWrapper::GetChildWindowId() );
/*N*/   if( pWrp )
/*?*/       {DBG_BF_ASSERT(0, "STRIP");} //STRIP001 pWrp->ReInitDlg( this );

    // RedlineDlg ggf neu initialisieren
/*N*/   SwRedlineAcceptChild *pRed = (SwRedlineAcceptChild*)pVFrame->
/*N*/           GetChildWindow( SwRedlineAcceptChild::GetChildWindowId() );
/*N*/   if( pRed )
/*?*/   {DBG_BF_ASSERT(0, "STRIP");} //STRIP001     pRed->ReInitDlg( this );
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

//STRIP001 void SwDocShell::ReloadFromHtml( const String& rStreamName, SwSrcView* pSrcView )
//STRIP001 {
//STRIP001  BOOL bModified = IsModified();
//STRIP001
//STRIP001  // MIB 23.6.97: Die HTTP-Header-Felder muessen geloescht werden,
//STRIP001  // sonst gibt es welche aus Meta-Tags hinter doppelt und dreifach.
//STRIP001  ClearHeaderAttributesForSourceViewHack();
//STRIP001
//STRIP001  // MIB 24.07.97: Das Dokument-Basic muss auch noch d'ran glauben ...
//STRIP001  // Ein EnterBasicCall braucht man hier nicht, weil man nichts ruft und
//STRIP001  // in HTML-Dokument kein Dok-Basic vorhanden sein kann, das noch nicht
//STRIP001  // geladen wurde.
//STRIP001  OfficeApplication* pOffApp = OFF_APP();
//STRIP001  OfaHtmlOptions* pHtmlOptions = pOffApp->GetHtmlOptions();
//STRIP001  //#59620# HasBasic() zeigt an, dass es schon einen BasicManager an der DocShell
//STRIP001  //          gibt. Der wurde im HTML-Import immer angelegt, wenn Macros im Quelltext
//STRIP001  //          vorhanden sind.
//STRIP001  if( pHtmlOptions && pHtmlOptions->IsStarBasic() && HasBasic())
//STRIP001  {
//STRIP001      BasicManager *pBasicMan = GetBasicManager();
//STRIP001      if( pBasicMan && (pBasicMan != pOffApp->GetBasicManager()) )
//STRIP001      {
//STRIP001          USHORT nLibCount = pBasicMan->GetLibCount();
//STRIP001          while( nLibCount )
//STRIP001          {
//STRIP001              StarBASIC *pBasic = pBasicMan->GetLib( --nLibCount );
//STRIP001              if( pBasic )
//STRIP001              {
//STRIP001                  // Die IDE benachrichtigen
//STRIP001                  String aLibName( '[' );
//STRIP001                  ((aLibName += GetTitle()).AppendAscii( "]." ))
//STRIP001                          += pBasic->GetName();
//STRIP001                  SfxStringItem aStrItem( SID_BASICIDE_ARG_LIBNAME, aLibName );
//STRIP001
//STRIP001                  pSrcView->GetViewFrame()->GetDispatcher()->Execute(
//STRIP001                                          SID_BASICIDE_LIBREMOVED,
//STRIP001                                          SFX_CALLMODE_SYNCHRON,
//STRIP001                                          &aStrItem, 0L );
//STRIP001
//STRIP001                  // Aus der Standard-Lib werden nur die Module geloescht
//STRIP001                  if( nLibCount )
//STRIP001                      pBasicMan->RemoveLib( nLibCount, TRUE );
//STRIP001                  else
//STRIP001                      pBasic->Clear();
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          ASSERT( pBasicMan->GetLibCount() <= 1,
//STRIP001                  "Loschen des Basics hat nicht geklappt" );
//STRIP001      }
//STRIP001  }
//STRIP001     sal_Bool bWasBrowseMode = pDoc->IsBrowseMode();
//STRIP001  RemoveLink();
//STRIP001  delete pIo;
//STRIP001  pIo = 0;
//STRIP001  //jetzt muss auch das UNO-Model ueber das neue Doc informiert werden #51535#
//STRIP001  uno::Reference<text::XTextDocument> xDoc(GetBaseModel(), uno::UNO_QUERY);
//STRIP001  text::XTextDocument* pxDoc = xDoc.get();
//STRIP001  ((SwXTextDocument*)pxDoc)->InitNewDoc();
//STRIP001
//STRIP001
//STRIP001  AddLink();
//STRIP001  pDoc->SetBrowseMode(bWasBrowseMode);
//STRIP001  pSrcView->SetPool(&GetPool());
//STRIP001
//STRIP001
//STRIP001  String sBaseURL = so3::StaticBaseUrl::GetBaseURL();
//STRIP001  const String& rMedname = GetMedium()->GetName();
//STRIP001  so3::StaticBaseUrl::SetBaseURL( rMedname );
//STRIP001
//STRIP001  // fix #51032#: Die HTML-Vorlage muss noch gesetzt werden
//STRIP001  SetHTMLTemplate( *GetDoc() );   //Styles aus HTML.vor
//STRIP001
//STRIP001  SfxViewShell* pViewShell = GetView() ? (SfxViewShell*)GetView()
//STRIP001                                       : SfxViewShell::Current();
//STRIP001  SfxViewFrame*  pViewFrm = pViewShell->GetViewFrame();
//STRIP001  pViewFrm->GetDispatcher()->Execute( SID_VIEWSHELL0, SFX_CALLMODE_SYNCHRON );
//STRIP001
//STRIP001  SubInitNew();
//STRIP001
//STRIP001  SfxMedium aMed( rStreamName, STREAM_READ, FALSE );
//STRIP001  SwReader aReader( aMed, rMedname, pDoc );
//STRIP001  aReader.Read( *ReadHTML );
//STRIP001
//STRIP001  so3::StaticBaseUrl::SetBaseURL(sBaseURL);
//STRIP001     const SwView* pView = GetView();
//STRIP001     //in print layout the first page(s) may have been formatted as a mix of browse
//STRIP001     //and print layout
//STRIP001     if(!bWasBrowseMode && pView)
//STRIP001     {
//STRIP001         SwWrtShell& rWrtSh = pView->GetWrtShell();
//STRIP001         if( rWrtSh.GetLayout())
//STRIP001             rWrtSh.CheckBrowseView( TRUE );
//STRIP001     }
//STRIP001
//STRIP001
//STRIP001  // MIB 23.6.97: Die HTTP-Header-Attribute wieder in die DokInfo
//STRIP001  // uebernehmen. Die Base-URL ist hier egal, da TLX zum absolutieren die
//STRIP001  // vom Dokument nimmt.
//STRIP001  SetHeaderAttributesForSourceViewHack();
//STRIP001
//STRIP001  if(bModified && !IsReadOnly())
//STRIP001      SetModified();
//STRIP001  else
//STRIP001      pDoc->ResetModified();
//STRIP001 }

/* -----------------------------14.12.99 16:52--------------------------------

 ---------------------------------------------------------------------------*/
/*?*/ void  SwDocShell::ToggleBrowserMode(BOOL bSet, SwView* pView )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  GetDoc()->SetBrowseMode( bSet );
//STRIP001  UpdateFontList();
//STRIP001  SwView* pTempView = pView ? pView : (SwView*)GetView();
//STRIP001  if( pTempView )
//STRIP001  {
//STRIP001      pTempView->GetViewFrame()->GetBindings().Invalidate(FN_SHADOWCURSOR);
//STRIP001      if( !GetDoc()->GetPrt( FALSE ) )
//STRIP001          pTempView->SetPrinter( GetDoc()->GetPrt( TRUE ),
//STRIP001                  SFX_PRINTER_PRINTER|SFX_PRINTER_JOBSETUP );
//STRIP001
//STRIP001      //Wenn wir die BrowseView einschalten, darf es nur diese eine
//STRIP001      //Sicht auf das Dokument geben, alle anderen werden geschlossen.
//STRIP001      SfxViewFrame *pTmpFrm = SfxViewFrame::GetFirst(this, 0, FALSE);
//STRIP001      do {
//STRIP001          if( pTmpFrm != pTempView->GetViewFrame() )
//STRIP001          {
//STRIP001              pTmpFrm->DoClose();
//STRIP001              pTmpFrm = SfxViewFrame::GetFirst(this, 0, FALSE);
//STRIP001          }
//STRIP001          else
//STRIP001              pTmpFrm = pTmpFrm->GetNext(*pTmpFrm, this, 0, FALSE);
//STRIP001
//STRIP001      } while ( pTmpFrm );
//STRIP001
//STRIP001      pTempView->GetWrtShell().CheckBrowseView( TRUE );
//STRIP001      pTempView->CheckVisArea();
//STRIP001
//STRIP001      SvxZoomType eType;
//STRIP001      if( GetDoc()->IsBrowseMode() &&
//STRIP001          SVX_ZOOM_PERCENT != (eType = (SvxZoomType)pTempView->
//STRIP001                          GetWrtShell().GetViewOptions()->GetZoomType()) )
//STRIP001      {
//STRIP001          ((SwView*)GetView())->SetZoom( eType );
//STRIP001      }
//STRIP001      pTempView->InvalidateBorder();
//STRIP001      pTempView->SetNewWindowAllowed(!bSet);
//STRIP001  }
/*?*/ }

/*N*/ULONG SwDocShell::LoadStylesFromFile( const String& rURL,
/*N*/                   SwgReaderOption& rOpt, BOOL bUnoCall )
/*N*/{
/*N*/   ULONG nErr = 0;DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001
//STRIP001  // Create a URL from filename
//STRIP001  INetURLObject aURLObj( rURL );
//STRIP001  String sURL( aURLObj.GetMainURL( INetURLObject::NO_DECODE ) );
//STRIP001
//STRIP001  String sBaseURL( so3::StaticBaseUrl::GetBaseURL() );
//STRIP001  so3::StaticBaseUrl::SetBaseURL( sURL );
//STRIP001
//STRIP001  SwRead pRead = 0;
//STRIP001  SwReader* pReader = 0;
//STRIP001  SwPaM* pPam = 0;
//STRIP001
//STRIP001  // Filter bestimmen:
//STRIP001  const SfxFilter* pFlt = SwIoSystem::GetFileFilter( rURL, aEmptyStr );
//STRIP001  SfxMedium aMed( rURL, STREAM_STD_READ, FALSE );
//STRIP001  if( aMed.IsStorage() )
//STRIP001  {
//STRIP001         ULONG nVersion = pFlt ? pFlt->GetVersion() : 0;
//STRIP001         if( nVersion )
//STRIP001          aMed.GetStorage()->SetVersion( (long)nVersion );
//STRIP001         pRead = nVersion >= SOFFICE_FILEFORMAT_60 ? ReadXML : ReadSw3;
//STRIP001      // the SW3IO - Reader need the pam/wrtshell, because only then he
//STRIP001      // insert the styles!
//STRIP001      if( bUnoCall )
//STRIP001      {
//STRIP001          SwNodeIndex aIdx( pDoc->GetNodes().GetEndOfContent(), -1 );
//STRIP001          pPam = new SwPaM( aIdx );
//STRIP001          pReader = new SwReader( aMed, rURL, *pPam );
//STRIP001      }
//STRIP001      else
//STRIP001          pReader = new SwReader( aMed, rURL, *pWrtShell->GetCrsr() );
//STRIP001  }
//STRIP001  else if( pFlt )
//STRIP001  {
//STRIP001      if( pFlt->GetUserData().EqualsAscii( FILTER_SWG ) ||
//STRIP001          pFlt->GetUserData().EqualsAscii( FILTER_SWGV ))
//STRIP001          pRead = ReadSwg;
//STRIP001      pReader = new SwReader( aMed, rURL, pDoc );
//STRIP001  }
//STRIP001
//STRIP001  ASSERT( pRead, "no reader found" );
//STRIP001  if( pRead )
//STRIP001  {
//STRIP001      pRead->GetReaderOpt().SetTxtFmts( rOpt.IsTxtFmts() );
//STRIP001      pRead->GetReaderOpt().SetFrmFmts( rOpt.IsFrmFmts() );
//STRIP001      pRead->GetReaderOpt().SetPageDescs( rOpt.IsPageDescs() );
//STRIP001      pRead->GetReaderOpt().SetNumRules( rOpt.IsNumRules() );
//STRIP001      pRead->GetReaderOpt().SetMerge( rOpt.IsMerge() );
//STRIP001
//STRIP001      if( bUnoCall )
//STRIP001      {
//STRIP001          UnoActionContext aAction( pDoc );
//STRIP001          nErr = pReader->Read( *pRead );
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          pWrtShell->StartAllAction();
//STRIP001          nErr = pReader->Read( *pRead );
//STRIP001          pWrtShell->EndAllAction();
//STRIP001      }
//STRIP001  }
//STRIP001  delete pPam;
//STRIP001  delete pReader;
//STRIP001  so3::StaticBaseUrl::SetBaseURL( sBaseURL );
/*N*/   return nErr;
/*N*/ }




}
