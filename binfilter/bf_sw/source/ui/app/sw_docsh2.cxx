/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_docsh2.cxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 23:58:59 $
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


/*N*/ void SwDoc::SetInfo( const SfxDocumentInfo& rInfo )
/*N*/ {
DBG_BF_ASSERT(0, "STRIP"); //STRIP001   if( pDocShell )
/*N*/ }

/*N*/ void SwDocShell::Execute(SfxRequest& rReq)
/*N*/ {
/*?*/ DBG_BF_ASSERT(0, "STRIP"); //STRIP001     const SfxItemSet* pArgs = rReq.GetArgs();
/*N*/ }


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


/* -----------------------------14.12.99 16:52--------------------------------

 ---------------------------------------------------------------------------*/
/*?*/ void  SwDocShell::ToggleBrowserMode(BOOL bSet, SwView* pView )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*?*/ }

/*N*/ULONG SwDocShell::LoadStylesFromFile( const String& rURL,
/*N*/                   SwgReaderOption& rOpt, BOOL bUnoCall )
/*N*/{
/*N*/   ULONG nErr = 0;DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/   return nErr;
/*N*/ }

}
