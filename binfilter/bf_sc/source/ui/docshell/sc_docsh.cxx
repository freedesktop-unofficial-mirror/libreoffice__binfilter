/*************************************************************************
 *
 *  $RCSfile: sc_docsh.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:39:40 $
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
#include "ui_pch.hxx"
#endif

#pragma hdrstop

#include "scitems.hxx"
#include <bf_svx/eeitem.hxx>
#ifndef _SVX_SVXENUM_HXX
#include <bf_svx/svxenum.hxx>
#endif
#ifndef _SVX_ALGITEM_HXX
#include <bf_svx/algitem.hxx>
#endif

#define ITEMID_FIELD EE_FEATURE_FIELD

#include <svtools/securityoptions.hxx>
#include <tools/stream.hxx>
#include <tools/string.hxx>
#include <tools/urlobj.hxx>
#include <vcl/msgbox.hxx>
#include <vcl/virdev.hxx>
#include <vcl/waitobj.hxx>
#include <svtools/ctrltool.hxx>
#include <svtools/sfxecode.hxx>
#include <svtools/zforlist.hxx>
#include <bf_sfx2/app.hxx>
#include <bf_sfx2/bindings.hxx>
#include <bf_sfx2/dinfdlg.hxx>
#include <bf_sfx2/docfile.hxx>
#include <bf_sfx2/docfilt.hxx>
#include <bf_sfx2/evntconf.hxx>
#include <bf_sfx2/sfx.hrc>
#include <bf_sfx2/topfrm.hxx>
#include <bf_svx/srchitem.hxx>
#include <bf_svx/svxmsbas.hxx>
#include <bf_offmgr/app.hxx>
#include <bf_offmgr/fltrcfg.hxx>
#include <so3/clsids.hxx>
#include <unotools/charclass.hxx>
#ifndef _SV_VIRDEV_HXX
#include <vcl/virdev.hxx>
#endif

#ifndef _SFXREQUEST_HXX
#include <bf_sfx2/request.hxx>
#endif
#ifndef _COM_SUN_STAR_DOCUMENT_UPDATEDOCMODE_HPP_
#include <com/sun/star/document/UpdateDocMode.hpp>
#endif

#include <sot/formats.hxx>
#define SOT_FORMATSTR_ID_STARCALC_30 SOT_FORMATSTR_ID_STARCALC

#ifndef SO2_DECL_SVSTORAGESTREAM_DEFINED
#define SO2_DECL_SVSTORAGESTREAM_DEFINED
SO2_DECL_REF(SvStorageStream)
#endif

// INCLUDE ---------------------------------------------------------------

#include "cell.hxx"
#include "global.hxx"
#include "filter.hxx"
#include "scmod.hxx"
#include "tabvwsh.hxx"
#include "docfunc.hxx"
#include "imoptdlg.hxx"
#include "impex.hxx"
#include "scresid.hxx"
#include "bf_sc.hrc"
#include "globstr.hrc"
#include "tpstat.hxx"
#include "scerrors.hxx"
#include "brdcst.hxx"
#include "stlpool.hxx"
#include "autostyl.hxx"
#include "attrib.hxx"
#include "asciiopt.hxx"
#include "waitoff.hxx"
#include "docpool.hxx"      // LoadCompleted
#include "progress.hxx"
#include "pntlock.hxx"
#include "collect.hxx"
#include "docuno.hxx"
#include "appoptio.hxx"
#include "detdata.hxx"
#include "printfun.hxx"
#include "dociter.hxx"
#include "cellform.hxx"
#include "chartlis.hxx"
#include "hints.hxx"
#include "xmlwrap.hxx"
#include "drwlayer.hxx"
#include "refreshtimer.hxx"
#include "dbcolect.hxx"
#include "scextopt.hxx"

#include "docsh.hxx"

#ifndef _RTL_LOGFILE_HXX_
#include <rtl/logfile.hxx>
#endif
namespace binfilter {

// STATIC DATA -----------------------------------------------------------

//  Stream-Namen im Storage

const sal_Char __FAR_DATA ScDocShell::pStarCalcDoc[] = STRING_SCSTREAM;     // "StarCalcDocument"
const sal_Char __FAR_DATA ScDocShell::pStyleName[] = "SfxStyleSheets";

//  Filter-Namen (wie in sclib.cxx)

static const sal_Char __FAR_DATA pFilterSc50[]      = "StarCalc 5.0";
//static const sal_Char __FAR_DATA pFilterSc50Temp[]    = "StarCalc 5.0 Vorlage/Template";
static const sal_Char __FAR_DATA pFilterSc40[]      = "StarCalc 4.0";
//static const sal_Char __FAR_DATA pFilterSc40Temp[]    = "StarCalc 4.0 Vorlage/Template";
static const sal_Char __FAR_DATA pFilterSc30[]      = "StarCalc 3.0";
//static const sal_Char __FAR_DATA pFilterSc30Temp[]    = "StarCalc 3.0 Vorlage/Template";
static const sal_Char __FAR_DATA pFilterSc10[]      = "StarCalc 1.0";
static const sal_Char __FAR_DATA pFilterXML[]       = "StarOffice XML (Calc)";
static const sal_Char __FAR_DATA pFilterAscii[]     = "Text - txt - csv (StarCalc)";
static const sal_Char __FAR_DATA pFilterLotus[]     = "Lotus";
static const sal_Char __FAR_DATA pFilterExcel4[]    = "MS Excel 4.0";
static const sal_Char __FAR_DATA pFilterEx4Temp[]   = "MS Excel 4.0 Vorlage/Template";
static const sal_Char __FAR_DATA pFilterExcel5[]    = "MS Excel 5.0/95";
static const sal_Char __FAR_DATA pFilterEx5Temp[]   = "MS Excel 5.0/95 Vorlage/Template";
static const sal_Char __FAR_DATA pFilterExcel95[]   = "MS Excel 95";
static const sal_Char __FAR_DATA pFilterEx95Temp[]  = "MS Excel 95 Vorlage/Template";
static const sal_Char __FAR_DATA pFilterExcel97[]   = "MS Excel 97";
static const sal_Char __FAR_DATA pFilterEx97Temp[]  = "MS Excel 97 Vorlage/Template";
static const sal_Char __FAR_DATA pFilterDBase[]     = "dBase";
static const sal_Char __FAR_DATA pFilterDif[]       = "DIF";
static const sal_Char __FAR_DATA pFilterSylk[]      = "SYLK";
static const sal_Char __FAR_DATA pFilterHtml[]      = "HTML (StarCalc)";
static const sal_Char __FAR_DATA pFilterHtmlWebQ[]  = "calc_HTML_WebQuery";
static const sal_Char __FAR_DATA pFilterRtf[]       = "Rich Text Format (StarCalc)";

//----------------------------------------------------------------------

#define ScDocShell
#include "scslots.hxx"


/*N*/ SFX_IMPL_INTERFACE(ScDocShell,SfxObjectShell, ScResId(SCSTR_DOCSHELL))
/*N*/ {}

//  GlobalName der aktuellen Version:
/*N*/ SFX_IMPL_OBJECTFACTORY_DLL(ScDocShell, SFXOBJECTSHELL_STD_NORMAL,
/*N*/                           SvGlobalName(BF_SO3_SC_CLASSID), Sc)

/*N*/ TYPEINIT1( ScDocShell, SfxObjectShell );      // SfxInPlaceObject: kein Type-Info ?

//------------------------------------------------------------------

/*N*/ void __EXPORT ScDocShell::FillClass( SvGlobalName* pClassName,
/*N*/                                       ULONG* pFormat,
/*N*/                                       String* pAppName,
/*N*/                                       String* pFullTypeName,
/*N*/                                       String* pShortTypeName,
/*N*/                                       long nFileFormat ) const
/*N*/ {
/*N*/   SfxInPlaceObject::FillClass( pClassName, pFormat, pAppName,
/*N*/                               pFullTypeName, pShortTypeName, nFileFormat );
/*N*/
/*N*/   if ( nFileFormat == SOFFICE_FILEFORMAT_31 )
/*N*/   {
/*N*/       *pClassName     = SvGlobalName( BF_SO3_SC_CLASSID_30 );
/*N*/       *pFormat        = SOT_FORMATSTR_ID_STARCALC_30;
/*N*/       *pAppName       = String( ScResId( SCSTR_30_APPLICATION ) );
/*N*/       *pFullTypeName  = String( ScResId( SCSTR_30_LONG_DOCNAME ) );
/*N*/       *pShortTypeName = String( ScResId( SCSTR_SHORT_SCDOC_NAME ) );
/*N*/   }
/*N*/   else if ( nFileFormat == SOFFICE_FILEFORMAT_40 )
/*N*/   {
/*N*/       *pClassName     = SvGlobalName( BF_SO3_SC_CLASSID_40 );
/*N*/       *pFormat        = SOT_FORMATSTR_ID_STARCALC_40;
/*N*/       *pAppName       = String( ScResId( SCSTR_40_APPLICATION ) );
/*N*/       *pFullTypeName  = String( ScResId( SCSTR_40_LONG_DOCNAME ) );
/*N*/       *pShortTypeName = String( ScResId( SCSTR_SHORT_SCDOC_NAME ) );
/*N*/   }
/*N*/   else if ( nFileFormat == SOFFICE_FILEFORMAT_50 )
/*N*/   {
/*N*/       *pClassName     = SvGlobalName( BF_SO3_SC_CLASSID_50 );
/*N*/       *pFormat        = SOT_FORMATSTR_ID_STARCALC_50;
/*N*/       *pAppName       = String( ScResId( SCSTR_50_APPLICATION ) );
/*N*/       *pFullTypeName  = String( ScResId( SCSTR_50_LONG_DOCNAME ) );
/*N*/       *pShortTypeName = String( ScResId( SCSTR_SHORT_SCDOC_NAME ) );
/*N*/   }
/*N*/   else if ( nFileFormat == SOFFICE_FILEFORMAT_60 )
/*N*/   {
/*N*/       // for binfilter, we need the FormatIDs to be set. Not setting them
            // has always been an error (!)
/*N*/       *pClassName     = SvGlobalName( BF_SO3_SC_CLASSID_60 );
/*N*/       *pFormat        = SOT_FORMATSTR_ID_STARCALC_60;
/*N*/       *pAppName       = String( ScResId( SCSTR_APPLICATION ) );
/*N*/
/*N*/       *pFullTypeName  = String( ScResId( SCSTR_LONG_SCDOC_NAME ) );
/*N*/       *pShortTypeName = String( ScResId( SCSTR_SHORT_SCDOC_NAME ) );

/*N*/   }
/*N*/   else
/*N*/       DBG_ERROR("wat fuer ne Version?");
/*N*/ }

//------------------------------------------------------------------

//STRIP001 void ScDocShell::DoEnterHandler()
//STRIP001 {
//STRIP001  ScTabViewShell* pViewSh = ScTabViewShell::GetActiveViewShell();
//STRIP001  if (pViewSh)
//STRIP001      if (pViewSh->GetViewData()->GetDocShell() == this)
//STRIP001          SC_MOD()->InputEnterHandler();
//STRIP001 }

//------------------------------------------------------------------

//STRIP001 USHORT ScDocShell::GetSaveTab()
//STRIP001 {
//STRIP001  USHORT nTab = 0;
//STRIP001  ScTabViewShell* pSh = GetBestViewShell();
//STRIP001  if (pSh)
//STRIP001  {
//STRIP001      const ScMarkData& rMark = pSh->GetViewData()->GetMarkData();
//STRIP001      for ( nTab = 0; nTab <= MAXTAB; nTab++ )    // erste markierte Tabelle
//STRIP001          if ( rMark.GetTableSelect( nTab ) )
//STRIP001              break;
//STRIP001  }
//STRIP001  return nTab;
//STRIP001 }

//------------------------------------------------------------------

/*N*/ BOOL ScDocShell::LoadCalc( SvStorage* pStor )     // StarCalc 3, 4 or 5 file
/*N*/ {
/*N*/   //  MacroCallMode is no longer needed, state is kept in SfxObjectShell now
/*N*/
/*N*/   BOOL bRet = TRUE;
/*N*/
/*N*/   SvStorageStreamRef aPoolStm = pStor->OpenStream( String::CreateFromAscii(pStyleName), STREAM_STD_READ );
/*N*/   SvStorageStreamRef aDocStm  = pStor->OpenStream( String::CreateFromAscii(pStarCalcDoc), STREAM_STD_READ );
/*N*/   ULONG nPoolErr = aPoolStm->GetError();
/*N*/   ULONG nDocErr  = aDocStm->GetError();
/*N*/
/*N*/   ScProgress* pProgress = NULL;
/*N*/   SfxObjectCreateMode eShellMode = GetCreateMode();
/*N*/   if ( eShellMode == SFX_CREATE_MODE_STANDARD && !nDocErr )
/*N*/   {
/*N*/       ULONG nCurPos = aDocStm->Tell();
/*N*/       ULONG nEndPos = aDocStm->Seek( STREAM_SEEK_TO_END );
/*N*/       aDocStm->Seek( nCurPos );
/*N*/       ULONG nRange = nEndPos - nCurPos;
/*N*/       pProgress = new ScProgress( this, ScGlobal::GetRscString(STR_LOAD_DOC), nRange );
/*N*/   }
/*N*/
/*N*/   if ( nPoolErr == ERRCODE_IO_NOTEXISTS && nDocErr == ERRCODE_IO_NOTEXISTS )
/*N*/   {
/*?*/       //  leerer Storage = leeres Dokument -> wie InitNew
/*?*/
/*?*/       aDocument.MakeTable(0);
/*?*/       Size aSize( (long) ( STD_COL_WIDTH           * HMM_PER_TWIPS * OLE_STD_CELLS_X ),
/*?*/                   (long) ( ScGlobal::nStdRowHeight * HMM_PER_TWIPS * OLE_STD_CELLS_Y ) );
/*?*/       // hier muss auch der Start angepasst werden
/*?*/       SetVisAreaOrSize( Rectangle( Point(), aSize ), TRUE );
/*?*/       aDocument.GetStyleSheetPool()->CreateStandardStyles();
/*?*/       aDocument.UpdStlShtPtrsFrmNms();
/*N*/   }
/*N*/   else if ( !nPoolErr && !nDocErr )
/*N*/   {
/*N*/       aPoolStm->SetVersion(pStor->GetVersion());
/*N*/       aDocStm->SetVersion(pStor->GetVersion());
/*N*/
/*N*/       aDocument.Clear();          // keine Referenzen auf Pool behalten!
/*N*/
/*N*/       RemoveItem( SID_ATTR_CHAR_FONTLIST );
/*N*/       RemoveItem( ITEMID_COLOR_TABLE );
/*N*/       RemoveItem( ITEMID_GRADIENT_LIST );
/*N*/       RemoveItem( ITEMID_HATCH_LIST );
/*N*/       RemoveItem( ITEMID_BITMAP_LIST );
/*N*/       RemoveItem( ITEMID_DASH_LIST );
/*N*/       RemoveItem( ITEMID_LINEEND_LIST );
/*N*/
/*N*/       aDocument.LoadPool( *aPoolStm, FALSE );     // FALSE: RefCounts nicht laden
/*N*/       bRet = (aPoolStm->GetError() == 0);
/*N*/
/*N*/       if ( !bRet )
/*N*/       {
/*N*/           pStor->SetError( aPoolStm->GetError() );
/*N*/           DBG_ERROR( "Fehler im Pool-Stream" );
/*N*/       }
/*N*/       else if (eShellMode != SFX_CREATE_MODE_ORGANIZER)
/*N*/       {
/*N*/           //  ViewOptions are not completely stored (to avoid warnings),
/*N*/           //  so must be initialized from global settings.
/*N*/           //! This can be removed if a new file format loads all ViewOptions !!!
/*N*/
/*N*/           aDocument.SetViewOptions( SC_MOD()->GetViewOptions() );
/*N*/
/*N*/           ULONG nErrCode = aPoolStm->GetErrorCode();
/*N*/           const ByteString aStrKey = pStor->GetKey();
/*N*/           const BOOL   bKeySet = (aStrKey.Len() > 0);
/*N*/
/*N*/           if ( bKeySet )
/*?*/               aDocStm->SetKey( aStrKey );         // Passwort setzen
/*N*/
/*N*/           bRet = aDocument.Load( *aDocStm, pProgress );
/*N*/
/*N*/           if ( !bRet && bKeySet ) // Passwort falsch
/*N*/           {
/*?*/               SetError( ERRCODE_SFX_WRONGPASSWORD );
/*?*/               pStor->SetError( ERRCODE_SFX_WRONGPASSWORD );
/*N*/           }
/*N*/
/*N*/           if ( aDocStm->GetError() )
/*N*/           {
/*?*/               //  Zeile-8192-Meldung braucht nur zu kommen, wenn die Zeilen
/*?*/               //  beschraenkt sind, sonst ist "falsches Format" besser
/*?*/ #ifdef SC_LIMIT_ROWS
/*?*/               if ( aDocument.HasLostData() )                  // zuviele Zeilen?
/*?*/                   pStor->SetError( SCERR_IMPORT_8K_LIMIT );
/*?*/               else
/*?*/ #endif
/*?*/                   pStor->SetError( aDocStm->GetError() );
/*?*/               bRet = FALSE;
/*?*/               DBG_ERROR( "Fehler im Document-Stream" );
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               if ( !(nErrCode & ERRCODE_WARNING_MASK) )
/*N*/                   nErrCode = aDocStm->GetErrorCode();
/*N*/               if ( nErrCode & ERRCODE_WARNING_MASK )
/*?*/                   SetError( nErrCode );
/*N*/           }
/*N*/
/*N*/           if (bRet)
/*N*/           {
/*N*/               aDocument.UpdateFontCharSet();
/*N*/
/*N*/               UpdateLinks();              // verknuepfte Tabellen in Link-Manager
/*N*/               RemoveUnknownObjects();     // unbekannte Ole-Objekte loeschen
/*N*/           }
/*N*/       }
/*N*/       else            // SFX_CREATE_MODE_ORGANIZER
/*N*/       {
/*?*/           //  UpdateStdNames is called from ScDocument::Load, but is also needed
/*?*/           //  if only the styles are loaded!
/*?*/           ScStyleSheetPool* pStylePool = aDocument.GetStyleSheetPool();
/*?*/           if (pStylePool)
/*?*/               pStylePool->UpdateStdNames();   // correct style names for different languages
/*N*/       }
/*N*/
/*N*/       if (bRet)
/*N*/           aDocument.GetPool()->MyLoadCompleted();
/*N*/   }
/*N*/   else
/*N*/   {
/*?*/       DBG_ERROR( "Stream-Fehler");
/*?*/       bRet = FALSE;
/*N*/   }
/*N*/
/*N*/   if (!aDocument.HasTable(0))
/*?*/       aDocument.MakeTable(0);
/*N*/
/*N*/   if (eShellMode == SFX_CREATE_MODE_EMBEDDED)
/*N*/   {
/*N*/       USHORT nVisTab = aDocument.GetVisibleTab();
/*N*/       BOOL bHasVis = aDocument.HasTable(nVisTab);
/*N*/       if ( SfxInPlaceObject::GetVisArea().IsEmpty() || !bHasVis )
/*N*/       {
/*?*/           if (!bHasVis)
/*?*/           {
/*?*/               nVisTab = 0;
/*?*/               aDocument.SetVisibleTab(nVisTab);
/*?*/           }
/*?*/           USHORT nStartCol,nStartRow;
/*?*/           aDocument.GetDataStart( nVisTab, nStartCol, nStartRow );
/*?*/           USHORT nEndCol,nEndRow;
/*?*/           aDocument.GetPrintArea( nVisTab, nEndCol, nEndRow );
/*?*/           if (nStartCol>nEndCol)
/*?*/               nStartCol = nEndCol;
/*?*/           if (nStartRow>nEndRow)
/*?*/               nStartRow = nEndRow;
/*?*/           // hier muss auch der Start angepasst werden
/*?*/           SetVisAreaOrSize( aDocument.GetMMRect( nStartCol,nStartRow, nEndCol,nEndRow, nVisTab ),
/*?*/                               TRUE );
/*N*/       }
/*N*/   }
/*N*/
/*N*/   delete pProgress;
/*N*/
/*N*/   return bRet;
/*N*/ }


/*N*/ BOOL ScDocShell::SaveCalc( SvStorage* pStor )         // Calc 3, 4 or 5 file
/*N*/ {
/*N*/   BOOL bRet = TRUE;
/*N*/
/*N*/   ScProgress* pProgress = NULL;
/*N*/   SfxObjectCreateMode eShellMode = GetCreateMode();
/*N*/   if ( eShellMode == SFX_CREATE_MODE_STANDARD )
/*N*/   {
/*N*/       ULONG nRange = aDocument.GetWeightedCount() + 1;
/*N*/       pProgress = new ScProgress( this, ScGlobal::GetRscString(STR_SAVE_DOC), nRange );
/*N*/   }
/*N*/
/*N*/   SvStorageStreamRef aPoolStm = pStor->OpenStream( String::CreateFromAscii(pStyleName) );
/*N*/   if( !aPoolStm->GetError() )
/*N*/   {
/*N*/       aPoolStm->SetVersion(pStor->GetVersion());
/*N*/       aPoolStm->SetSize(0);
/*N*/       bRet = aDocument.SavePool( *aPoolStm );
/*N*/       if ( aPoolStm->GetErrorCode() && !pStor->GetErrorCode() )
/*?*/           pStor->SetError(aPoolStm->GetErrorCode());
/*N*/   }
/*N*/   else
/*N*/   {
/*?*/       DBG_ERROR( "Stream Error" );
/*?*/       bRet = FALSE;
/*N*/   }
/*N*/
/*N*/   if ( bRet && eShellMode != SFX_CREATE_MODE_ORGANIZER )
/*N*/   {
/*N*/       SvStorageStreamRef aDocStm  = pStor->OpenStream( String::CreateFromAscii(pStarCalcDoc) );
/*N*/       if( !aDocStm->GetError() )
/*N*/       {
/*N*/           aDocStm->SetVersion(pStor->GetVersion());
/*N*/           aDocStm->SetKey(pStor->GetKey());               // Passwort setzen
/*N*/           aDocStm->SetSize(0);
/*N*/           bRet = aDocument.Save( *aDocStm, pProgress );
/*N*/           DBG_ASSERT( bRet, "Error while saving" );
/*N*/
/*N*/           if ( aDocument.HasLostData() )
/*N*/           {
/*?*/               //  Warnung, dass nicht alles gespeichert wurde
/*?*/
/*?*/               if (!pStor->GetError())
/*?*/                   pStor->SetError(SCWARN_EXPORT_MAXROW);
/*?*/           }
/*N*/           else if ( aDocStm->GetErrorCode() && !pStor->GetErrorCode() )
/*?*/               pStor->SetError(aDocStm->GetErrorCode());
/*N*/           else if ( OFF_APP()->GetFilterOptions()->IsLoadExcelBasicStorage() )
/*N*/           {
/*N*/               //  #75497# warning if MS VBA macros are lost
/*N*/               //  GetSaveWarningOfMSVBAStorage checks if sub-storage with VBA macros is present
/*N*/               //  (only possible when editing Excel documents -- storage is not copied to
/*N*/               //  StarCalc files)
/*N*/               ULONG nVBAWarn = SvxImportMSVBasic::GetSaveWarningOfMSVBAStorage( *this );
/*N*/               if ( nVBAWarn && !pStor->GetErrorCode() )
/*?*/                   pStor->SetError( nVBAWarn );
/*?*/           }
/*N*/       }
/*N*/       else
/*N*/       {
/*?*/           DBG_ERROR( "Stream Error" );
/*?*/           bRet = FALSE;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   delete pProgress;
/*N*/
/*N*/   return bRet;
/*N*/ }

/*N*/ void ScDocShell::BeforeXMLLoading()
/*N*/ {
/*N*/   // prevent unnecessary broadcasts and updates
/*N*/     DBG_ASSERT(pModificator == NULL, "The Modificator should not exist");
/*N*/   pModificator = new ScDocShellModificator( *this );
/*N*/
/*N*/     aDocument.SetImportingXML( TRUE );
/*N*/   // prevent unnecessary broadcasts and "half way listeners"
/*N*/   aDocument.SetInsertingFromOtherDoc( TRUE );
/*N*/
/*N*/   if (GetCreateMode() != SFX_CREATE_MODE_ORGANIZER)
/*N*/       ScColumn::bDoubleAlloc = sal_True;
/*N*/ }

/*N*/ void ScDocShell::AfterXMLLoading(sal_Bool bRet)
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  if (GetCreateMode() != SFX_CREATE_MODE_ORGANIZER)
//STRIP001  {
//STRIP001      UpdateLinks();
//STRIP001      // don't prevent establishing of listeners anymore
//STRIP001      aDocument.SetInsertingFromOtherDoc( FALSE );
//STRIP001      if ( bRet )
//STRIP001      {
//STRIP001          ScChartListenerCollection* pChartListener = aDocument.GetChartListenerCollection();
//STRIP001          if (pChartListener)
//STRIP001              pChartListener->UpdateDirtyCharts();
//STRIP001
//STRIP001          // #95582#; set the table names of linked tables to the new path
//STRIP001          USHORT nTabCount = aDocument.GetTableCount();
//STRIP001          for (USHORT i = 0; i < nTabCount; ++i)
//STRIP001          {
//STRIP001              if (aDocument.IsLinked( i ))
//STRIP001              {
//STRIP001                  String aName;
//STRIP001                  aDocument.GetName(i, aName);
//STRIP001                  String aLinkTabName = aDocument.GetLinkTab(i);
//STRIP001                  xub_StrLen nLinkTabNameLength = aLinkTabName.Len();
//STRIP001                  xub_StrLen nNameLength = aName.Len();
//STRIP001                  if (nLinkTabNameLength < nNameLength)
//STRIP001                  {
//STRIP001
//STRIP001                      // remove the quottes on begin and end of the docname and restore the escaped quotes
//STRIP001                      const sal_Unicode* pNameBuffer = aName.GetBuffer();
//STRIP001                      if ( *pNameBuffer == '\'' && // all docnames have to have a ' character on the first pos
//STRIP001                          ScGlobal::UnicodeStrChr( pNameBuffer, SC_COMPILER_FILE_TAB_SEP ) )
//STRIP001                      {
//STRIP001                          ::rtl::OUStringBuffer aDocURLBuffer;
//STRIP001                          BOOL bQuote = TRUE;         // Dokumentenname ist immer quoted
//STRIP001                          ++pNameBuffer;
//STRIP001                          while ( bQuote && *pNameBuffer )
//STRIP001                          {
//STRIP001                              if ( *pNameBuffer == '\'' && *(pNameBuffer-1) != '\\' )
//STRIP001                                  bQuote = FALSE;
//STRIP001                              else if( !(*pNameBuffer == '\\' && *(pNameBuffer+1) == '\'') )
//STRIP001                                  aDocURLBuffer.append(*pNameBuffer);     // falls escaped Quote: nur Quote in den Namen
//STRIP001                              ++pNameBuffer;
//STRIP001                          }
//STRIP001
//STRIP001
//STRIP001                          if( *pNameBuffer == SC_COMPILER_FILE_TAB_SEP )  // after the last quote of the docname should be the # char
//STRIP001                          {
//STRIP001                              xub_StrLen nIndex = nNameLength - nLinkTabNameLength;
//STRIP001                              INetURLObject aINetURLObject(aDocURLBuffer.makeStringAndClear());
//STRIP001                              if( aName.Equals(aLinkTabName, nIndex, nLinkTabNameLength) &&
//STRIP001                                  (aName.GetChar(nIndex - 1) == '#') && // before the table name should be the # char
//STRIP001                                  !aINetURLObject.HasError()) // the docname should be a valid URL
//STRIP001                              {
//STRIP001                                  aName = ScGlobal::GetDocTabName( aDocument.GetLinkDoc( i ), aDocument.GetLinkTab( i ) );
//STRIP001                                  aDocument.RenameTab(i, aName, TRUE, TRUE);
//STRIP001                              }
//STRIP001                              // else;  nothing has to happen, because it is a user given name
//STRIP001                          }
//STRIP001                          // else;  nothing has to happen, because it is a user given name
//STRIP001                      }
//STRIP001                      // else;  nothing has to happen, because it is a user given name
//STRIP001                  }
//STRIP001                  // else;  nothing has to happen, because it is a user given name
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      ScColumn::bDoubleAlloc = sal_False;
//STRIP001     }
//STRIP001     else
//STRIP001      aDocument.SetInsertingFromOtherDoc( FALSE );
//STRIP001
//STRIP001  aDocument.SetImportingXML( FALSE );
//STRIP001
//STRIP001     if (pModificator)
//STRIP001     {
//STRIP001         delete pModificator;
//STRIP001         pModificator = NULL;
//STRIP001     }
//STRIP001     else
//STRIP001         DBG_ERROR("The Modificator should exist");
/*N*/ }

/*N*/ BOOL ScDocShell::LoadXML( SfxMedium* pMedium, SvStorage* pStor )
/*N*/ {
/*N*/     RTL_LOGFILE_CONTEXT_AUTHOR ( aLog, "sc", "sb99857", "ScDocShell::LoadXML" );
/*N*/
/*N*/   //  MacroCallMode is no longer needed, state is kept in SfxObjectShell now
/*N*/
/*N*/   // no Seek(0) here - always loading from storage, GetInStream must not be called
/*N*/
/*N*/     BeforeXMLLoading();
/*N*/
/*N*/   ScXMLImportWrapper aImport( aDocument, pMedium, pStor );
/*N*/
/*N*/     sal_Bool bRet(sal_False);
/*N*/   if (GetCreateMode() != SFX_CREATE_MODE_ORGANIZER)
/*N*/       bRet = aImport.Import(sal_False);
/*N*/   else
/*N*/       bRet = aImport.Import(sal_True);
/*N*/
/*N*/     AfterXMLLoading(bRet);
/*N*/
/*N*/   //! row heights...
/*N*/
/*N*/   return bRet;
/*N*/ }

/*N*/ BOOL ScDocShell::SaveXML( SfxMedium* pMedium, SvStorage* pStor )
/*N*/ {
/*N*/     RTL_LOGFILE_CONTEXT_AUTHOR ( aLog, "sc", "sb99857", "ScDocShell::SaveXML" );
/*N*/
/*N*/   ScXMLImportWrapper aImport( aDocument, pMedium, pStor );
/*N*/   sal_Bool bRet(sal_False);
/*N*/   if (GetCreateMode() != SFX_CREATE_MODE_ORGANIZER)
/*N*/       bRet = aImport.Export(sal_False);
/*N*/   else
/*N*/       bRet = aImport.Export(sal_True);
/*N*/   return bRet;
/*N*/ }

/*N*/ BOOL __EXPORT ScDocShell::Load( SvStorage* pStor )
/*N*/ {
/*N*/   RTL_LOGFILE_CONTEXT_AUTHOR ( aLog, "sc", "nn93723", "ScDocShell::Load" );
/*N*/
/*N*/   ScRefreshTimerProtector( aDocument.GetRefreshTimerControlAddress() );
/*N*/
/*N*/   DBG_ASSERT( pStor, "Load without storage?" );
/*N*/   BOOL bXML = ( pStor->GetVersion() >= SOFFICE_FILEFORMAT_60 );
/*N*/
/*N*/   //  only the latin script language is loaded
/*N*/   //  -> initialize the others from options (before loading)
/*N*/   InitOptions();
/*N*/
/*N*/   GetUndoManager()->Clear();
/*N*/
/*N*/   BOOL bRet = SfxInPlaceObject::Load( pStor );
/*N*/   if( bRet )
/*N*/   {
/*N*/         if (GetMedium())
/*N*/         {
/*N*/             SFX_ITEMSET_ARG( GetMedium()->GetItemSet(), pUpdateDocItem, SfxUInt16Item, SID_UPDATEDOCMODE, sal_False);
/*N*/             nCanUpdate = pUpdateDocItem ? pUpdateDocItem->GetValue() : ::com::sun::star::document::UpdateDocMode::NO_UPDATE;
/*N*/         }
/*N*/
/*N*/         if (bXML)
/*N*/       {
/*N*/           //  prepare a valid document for XML filter
/*N*/           //  (for ConvertFrom, InitNew is called before)
/*N*/           aDocument.MakeTable(0);
/*N*/           aDocument.GetStyleSheetPool()->CreateStandardStyles();
/*N*/           aDocument.UpdStlShtPtrsFrmNms();
/*N*/
/*N*/           bRet = LoadXML( GetMedium(), pStor );
/*N*/       }
/*N*/       else
/*N*/           bRet = LoadCalc( pStor );
/*N*/   }
/*N*/
/*N*/   if (!bRet && !pStor->GetError())
/*?*/       pStor->SetError( SVSTREAM_FILEFORMAT_ERROR );
/*N*/
/*N*/   if (pStor->GetError())
/*?*/       SetError( pStor->GetError() );
/*N*/
/*N*/   InitItems();
/*N*/   CalcOutputFactor();
/*N*/
/*N*/   // #73762# invalidate eventually temporary table areas
/*N*/   if ( bRet )
/*N*/       aDocument.InvalidateTableArea();
/*N*/
/*N*/   bIsEmpty = FALSE;
/*N*/   FinishedLoading( SFX_LOADED_MAINDOCUMENT | SFX_LOADED_IMAGES );
/*N*/   return bRet;
/*N*/ }


/*N*/ void __EXPORT ScDocShell::SFX_NOTIFY( SfxBroadcaster& rBC, const TypeId& rBCType,
/*N*/                        const SfxHint& rHint, const TypeId& rHintType )
/*N*/ {
/*N*/   if (rHint.ISA(SfxSimpleHint))                               // ohne Parameter
/*N*/   {
/*N*/       ULONG nSlot = ((const SfxSimpleHint&)rHint).GetId();
/*N*/       switch ( nSlot )
/*N*/       {
/*N*/           case SFX_HINT_TITLECHANGED:
/*N*/               aDocument.SetName( SfxShell::GetName() );
/*N*/               //  RegisterNewTargetNames gibts nicht mehr
/*N*/               SFX_APP()->Broadcast(SfxSimpleHint( SC_HINT_DOCNAME_CHANGED )); // Navigator
/*N*/               break;
/*N*/       }
/*N*/   }
/*N*/   else if (rHint.ISA(SfxStyleSheetHint))                      // Vorlagen geaendert
/*N*/       NotifyStyle((const SfxStyleSheetHint&) rHint);
/*N*/   else if (rHint.ISA(ScAutoStyleHint))
/*N*/   {
/*?*/       //! direct call for AutoStyles
/*?*/
/*?*/       //  this is called synchronously from ScInterpreter::ScStyle,
/*?*/       //  modifying the document must be asynchronous
/*?*/       //  (handled by AddInitial)
/*?*/
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 ScAutoStyleHint& rStlHint = (ScAutoStyleHint&)rHint;
//STRIP001 /*?*/        ScRange aRange = rStlHint.GetRange();
//STRIP001 /*?*/        String aName1 = rStlHint.GetStyle1();
//STRIP001 /*?*/        String aName2 = rStlHint.GetStyle2();
//STRIP001 /*?*/        UINT32 nTimeout = rStlHint.GetTimeout();
//STRIP001 /*?*/
//STRIP001 /*?*/        if (!pAutoStyleList)
//STRIP001 /*?*/            pAutoStyleList = new ScAutoStyleList(this);
//STRIP001 /*?*/        pAutoStyleList->AddInitial( aRange, aName1, nTimeout, aName2 );
/*N*/   }
/*N*/ }

    // Inhalte fuer Organizer laden


//STRIP001 BOOL __EXPORT ScDocShell::LoadFrom( SvStorage* pStor )
//STRIP001 {
//STRIP001  RTL_LOGFILE_CONTEXT_AUTHOR ( aLog, "sc", "nn93723", "ScDocShell::LoadFrom" );
//STRIP001
//STRIP001  ScRefreshTimerProtector( aDocument.GetRefreshTimerControlAddress() );
//STRIP001
//STRIP001  DBG_ASSERT( pStor, "Nanu... LoadFrom ohne Storage?" );
//STRIP001  BOOL bXML = ( pStor->GetVersion() >= SOFFICE_FILEFORMAT_60 );
//STRIP001
//STRIP001  WaitObject aWait( GetDialogParent() );
//STRIP001
//STRIP001  BOOL bRet = FALSE;
//STRIP001
//STRIP001     if (GetMedium())
//STRIP001     {
//STRIP001         SFX_ITEMSET_ARG( GetMedium()->GetItemSet(), pUpdateDocItem, SfxUInt16Item, SID_UPDATEDOCMODE, sal_False);
//STRIP001         nCanUpdate = pUpdateDocItem ? pUpdateDocItem->GetValue() : ::com::sun::star::document::UpdateDocMode::NO_UPDATE;
//STRIP001     }
//STRIP001
//STRIP001  if ( bXML )
//STRIP001  {
//STRIP001      //  until loading/saving only the styles in XML is implemented,
//STRIP001      //  load the whole file
//STRIP001
//STRIP001      bRet = LoadXML( GetMedium(), pStor );
//STRIP001      InitItems();
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      SvStorageStreamRef aPoolStm = pStor->OpenStream( String::CreateFromAscii(pStyleName), STREAM_STD_READ );
//STRIP001      if ( !aPoolStm->GetError() )
//STRIP001      {
//STRIP001          aPoolStm->SetVersion(pStor->GetVersion());
//STRIP001
//STRIP001          aDocument.Clear();                      // keine Referenzen auf Pool behalten!
//STRIP001          RemoveItem( SID_ATTR_CHAR_FONTLIST );
//STRIP001          RemoveItem( ITEMID_COLOR_TABLE );
//STRIP001          RemoveItem( ITEMID_GRADIENT_LIST );
//STRIP001          RemoveItem( ITEMID_HATCH_LIST );
//STRIP001          RemoveItem( ITEMID_BITMAP_LIST );
//STRIP001          RemoveItem( ITEMID_DASH_LIST );
//STRIP001          RemoveItem( ITEMID_LINEEND_LIST );
//STRIP001
//STRIP001          aDocument.LoadPool( *aPoolStm, TRUE );      // TRUE: RefCounts aus Datei laden
//STRIP001          bRet = (aPoolStm->GetError() == 0);
//STRIP001          DBG_ASSERT( bRet, "Error in pool stream" );
//STRIP001
//STRIP001          //  UpdateStdNames is called from ScDocument::Load, but is also needed
//STRIP001          //  if only the styles are loaded!
//STRIP001          ScStyleSheetPool* pStylePool = aDocument.GetStyleSheetPool();
//STRIP001          if (pStylePool)
//STRIP001              pStylePool->UpdateStdNames();   // correct style names for different languages
//STRIP001
//STRIP001          //  Hier auf keinen Fall LoadCompleted, weil ohne Laden der Tabellen die RefCounts
//STRIP001          //  nicht hochgezaehlt wurden.
//STRIP001          //  Die Items wuerden dann geloescht, und beim Speichern wuerde Muell herauskommen.
//STRIP001          //  Darum die Ref-Counts aus der Datei laden (TRUE bei LoadPool).
//STRIP001          //  (Bug #37635#)
//STRIP001
//STRIP001          InitItems();
//STRIP001          //  CalcOutputFactor interessiert hier nicht
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  SfxObjectShell::LoadFrom( pStor );
//STRIP001
//STRIP001  return bRet;
//STRIP001 }


/*N*/ BOOL __EXPORT ScDocShell::ConvertFrom( SfxMedium& rMedium )
/*N*/ {
/*N*/   RTL_LOGFILE_CONTEXT_AUTHOR ( aLog, "sc", "nn93723", "ScDocShell::ConvertFrom" );
/*N*/
/*N*/   BOOL bRet = FALSE;              // FALSE heisst Benutzerabbruch !!
/*N*/                                   // bei Fehler: Fehler am Stream setzen!!
/*N*/
/*N*/   ScRefreshTimerProtector( aDocument.GetRefreshTimerControlAddress() );
/*N*/
/*N*/   GetUndoManager()->Clear();
/*N*/
/*N*/   // ob nach dem Import optimale Spaltenbreiten gesetzt werden sollen
/*N*/   BOOL bSetColWidths = FALSE;
/*N*/   BOOL bSetSimpleTextColWidths = FALSE;
/*N*/   BOOL bSimpleColWidth[MAXCOL+1];
/*N*/   memset( bSimpleColWidth, 1, (MAXCOL+1) * sizeof(BOOL) );
/*N*/   ScRange aColWidthRange;
/*N*/   // ob nach dem Import optimale Zeilenhoehen gesetzt werden sollen
/*N*/   BOOL bSetRowHeights = FALSE;
/*N*/
/*N*/   aConvFilterName.Erase(); //@ #BugId 54198
/*N*/
/*N*/   //  Alle Filter brauchen die komplette Datei am Stueck (nicht asynchron),
/*N*/   //  darum vorher per CreateFileStream dafuer sorgen, dass die komplette
/*N*/   //  Datei uebertragen wird.
/*N*/   rMedium.GetPhysicalName();  //! CreateFileStream direkt rufen, wenn verfuegbar
/*N*/
/*N*/     SFX_ITEMSET_ARG( rMedium.GetItemSet(), pUpdateDocItem, SfxUInt16Item, SID_UPDATEDOCMODE, sal_False);
/*N*/     nCanUpdate = pUpdateDocItem ? pUpdateDocItem->GetValue() : ::com::sun::star::document::UpdateDocMode::NO_UPDATE;
/*N*/
/*N*/     const SfxFilter* pFilter = rMedium.GetFilter();
/*N*/   if (pFilter)
/*N*/   {
/*N*/       String aFltName = pFilter->GetFilterName();
/*N*/
/*N*/       aConvFilterName=aFltName; //@ #BugId 54198
/*N*/
/*N*/       BOOL bCalc3 = ( aFltName.EqualsAscii(pFilterSc30) );
/*N*/       BOOL bCalc4 = ( aFltName.EqualsAscii(pFilterSc40) );
/*N*/       if (!bCalc3 && !bCalc4)
/*N*/           aDocument.SetInsertingFromOtherDoc( TRUE );
/*N*/
/*N*/       if (bCalc3 || bCalc4)                   // Calc3/4 - "Import"
/*N*/       {
/*?*/           //  wait cursor is handled with progress bar
/*?*/           SvStorage* pStor = rMedium.GetStorage();
/*?*/           if ( pStor )
/*?*/           {
/*?*/               bRet = SfxInPlaceObject::Load( pStor );
/*?*/               if( bRet )
/*?*/                   bRet = LoadCalc( pStor );
/*?*/               if (!bRet && !pStor->GetError())
/*?*/                   pStor->SetError( SVSTREAM_FILEFORMAT_ERROR );
/*?*/           }
/*?*/           else
/*?*/               DBG_ERROR("Calc3/4: kein Storage");
/*N*/       }
/*N*/       else if (aFltName.EqualsAscii(pFilterXML))
/*?*/       {   DBG_BF_ASSERT(0, "STRIP"); }//STRIP001 bRet = LoadXML( &rMedium, NULL );
/*N*/       else if (aFltName.EqualsAscii(pFilterSc10))
/*N*/       {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); //STRIP001       SvStream* pStream = rMedium.GetInStream();
//STRIP001 /*?*/            if (pStream)
//STRIP001 /*?*/            {
//STRIP001 /*?*/                FltError eError = ScImportStarCalc10( *pStream, &aDocument );
//STRIP001 /*?*/                if (eError != eERR_OK)
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    if (!GetError())
//STRIP001 /*?*/                        SetError(eError);
//STRIP001 /*?*/                }
//STRIP001 /*?*/                else
//STRIP001 /*?*/                    bRet = TRUE;
//STRIP001 /*?*/            }
/*N*/       }
/*N*/       else if (aFltName.EqualsAscii(pFilterLotus))
/*N*/       {
DBG_BF_ASSERT(0, "STRIP"); //STRIP001 //STRIP001 /*N*/ //           SvStream* pStream = rMedium.GetInStream();
//STRIP001 /*N*/ //         if (pStream)
//STRIP001 /*?*/            {
//STRIP001 /*?*/                String sItStr;
//STRIP001 /*?*/                SfxItemSet*  pSet = rMedium.GetItemSet();
//STRIP001 /*?*/                const SfxPoolItem* pItem;
//STRIP001 /*?*/                if ( pSet && SFX_ITEM_SET ==
//STRIP001 /*?*/                     pSet->GetItemState( SID_FILE_FILTEROPTIONS, TRUE, &pItem ) )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    sItStr = ((const SfxStringItem*)pItem)->GetValue();
//STRIP001 /*?*/                }
//STRIP001 /*?*/
//STRIP001 /*?*/                if (sItStr.Len() == 0)
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    //  default for lotus import (from API without options):
//STRIP001 /*?*/                    //  IBM_437 encoding
//STRIP001 /*?*/
//STRIP001 /*?*/                    sItStr = ScGlobal::GetCharsetString( RTL_TEXTENCODING_IBM_437 );
//STRIP001 /*?*/                }
//STRIP001 /*?*/
//STRIP001 /*?*/                ScColumn::bDoubleAlloc = TRUE;
//STRIP001 /*?*/                FltError eError = ScImportLotus123( rMedium, &aDocument,
//STRIP001 /*?*/                                    ScGlobal::GetCharsetValue(sItStr));
//STRIP001 /*?*/                ScColumn::bDoubleAlloc = FALSE;
//STRIP001 /*?*/                if (eError != eERR_OK)
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    if (!GetError())
//STRIP001 /*?*/                        SetError(eError);
//STRIP001 /*?*/
//STRIP001 /*?*/                    if( ( eError & ERRCODE_WARNING_MASK ) == ERRCODE_WARNING_MASK )
//STRIP001 /*?*/                        bRet = TRUE;
//STRIP001 /*?*/                }
//STRIP001 /*?*/                else
//STRIP001 /*?*/                    bRet = TRUE;
//STRIP001 /*?*/
//STRIP001 /*?*/ //             rMedium.CloseInStream();
//STRIP001 /*?*/            }
/*N*/       }
/*N*/       else if ( aFltName.EqualsAscii(pFilterExcel4) || aFltName.EqualsAscii(pFilterExcel5) ||
/*N*/                  aFltName.EqualsAscii(pFilterExcel95) || aFltName.EqualsAscii(pFilterExcel97) ||
/*N*/                  aFltName.EqualsAscii(pFilterEx4Temp) || aFltName.EqualsAscii(pFilterEx5Temp) ||
/*N*/                  aFltName.EqualsAscii(pFilterEx95Temp) || aFltName.EqualsAscii(pFilterEx97Temp) )
/*N*/       {
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 EXCIMPFORMAT eFormat = EIF_AUTO;
//STRIP001 /*?*/            if ( aFltName.EqualsAscii(pFilterExcel4) || aFltName.EqualsAscii(pFilterEx4Temp) )
//STRIP001 /*?*/                eFormat = EIF_BIFF_LE4;
//STRIP001 /*?*/            else if ( aFltName.EqualsAscii(pFilterExcel5) || aFltName.EqualsAscii(pFilterExcel95) ||
//STRIP001 /*?*/                      aFltName.EqualsAscii(pFilterEx5Temp) || aFltName.EqualsAscii(pFilterEx95Temp) )
//STRIP001 /*?*/                eFormat = EIF_BIFF5;
//STRIP001 /*?*/            else if ( aFltName.EqualsAscii(pFilterExcel97) || aFltName.EqualsAscii(pFilterEx97Temp) )
//STRIP001 /*?*/                eFormat = EIF_BIFF8;
//STRIP001 /*?*/
//STRIP001 /*?*/            MakeDrawLayer();                //! im Filter
//STRIP001 /*?*/             CalcOutputFactor();             // #93255# prepare update of row height
//STRIP001 /*?*/            ScColumn::bDoubleAlloc = TRUE;
//STRIP001 /*?*/            FltError eError = ScImportExcel( rMedium, &aDocument, eFormat );
//STRIP001 /*?*/            ScColumn::bDoubleAlloc = FALSE;
//STRIP001 /*?*/            aDocument.UpdateFontCharSet();
//STRIP001 /*?*/            if ( aDocument.IsChartListenerCollectionNeedsUpdate() )
//STRIP001 /*?*/                aDocument.UpdateChartListenerCollection();              //! fuer alle Importe?
//STRIP001 /*?*/
//STRIP001 /*?*/            // #75299# all graphics objects must have names
//STRIP001 /*?*/            aDocument.EnsureGraphicNames();
//STRIP001 /*?*/
//STRIP001 /*?*/            if (eError == SCWARN_IMPORT_RANGE_OVERFLOW)
//STRIP001 /*?*/            {
//STRIP001 /*?*/                if (!GetError())
//STRIP001 /*?*/                    SetError(eError);
//STRIP001 /*?*/                bRet = TRUE;
//STRIP001 /*?*/            }
//STRIP001 /*?*/            else if (eError != eERR_OK)
//STRIP001 /*?*/            {
//STRIP001 /*?*/                if (!GetError())
//STRIP001 /*?*/                    SetError(eError);
//STRIP001 /*?*/            }
//STRIP001 /*?*/            else
//STRIP001 /*?*/                bRet = TRUE;
//STRIP001 /*?*/
//STRIP001 /*?*/             // #93255# update of row height done inside of Excel filter to speed up chart import
//STRIP001 /*?*/ //            bSetRowHeights = TRUE;      //  #75357# optimal row heights must be updated
/*N*/       }
/*N*/       else if (aFltName.EqualsAscii(pFilterAscii))
/*N*/       {
/*N*/           SfxItemSet*  pSet = rMedium.GetItemSet();
/*N*/           const SfxPoolItem* pItem;
/*N*/           ScAsciiOptions aOptions;
/*N*/           BOOL bOptInit = FALSE;
/*N*/
/*N*/           if ( pSet && SFX_ITEM_SET ==
/*N*/                pSet->GetItemState( SID_FILE_FILTEROPTIONS, TRUE, &pItem ) )
/*N*/           {
/*N*/               aOptions.ReadFromString( ((const SfxStringItem*)pItem)->GetValue() );
/*N*/               bOptInit = TRUE;
/*N*/           }
/*N*/
/*N*/           if ( !bOptInit )
/*N*/           {
/*?*/               //  default for ascii import (from API without options):
/*?*/               //  ISO8859-1/MS_1252 encoding, comma, double quotes
/*?*/
/*?*/               aOptions.SetCharSet( RTL_TEXTENCODING_MS_1252 );
/*?*/               aOptions.SetFieldSeps( (sal_Unicode) ',' );
/*?*/               aOptions.SetTextSep( (sal_Unicode) '"' );
/*N*/           }
/*N*/
/*N*/           FltError eError = eERR_OK;
/*N*/           BOOL bOverflow = FALSE;
/*N*/
/*N*/           if( ! rMedium.IsStorage() )
/*N*/           {
/*N*/               ScImportExport  aImpEx( &aDocument );
/*N*/               aImpEx.SetExtOptions( aOptions );
/*N*/
/*N*/               SvStream* pInStream = rMedium.GetInStream();
/*N*/               if (pInStream)
/*N*/               {
/*N*/                   pInStream->SetStreamCharSet( aOptions.GetCharSet() );
/*N*/                   pInStream->Seek( 0 );
/*N*/                   bRet = aImpEx.ImportStream( *pInStream );
/*N*/                   eError = bRet ? eERR_OK : SCERR_IMPORT_CONNECT;
/*N*/                   aDocument.StartAllListeners();
/*N*/                   aDocument.SetDirty();
/*N*/                   bOverflow = aImpEx.IsOverflow();
/*N*/               }
/*N*/               else
/*N*/                   DBG_ERROR( "No Stream" );
/*N*/           }
/*N*/
/*N*/           if (eError != eERR_OK)
/*N*/           {
/*N*/               if (!GetError())
/*N*/                   SetError(eError);
/*N*/           }
/*N*/           else if ( bOverflow )
/*N*/           {
/*N*/               if (!GetError())
/*N*/                   SetError(SCWARN_IMPORT_RANGE_OVERFLOW);
/*N*/           }
/*N*/           bSetColWidths = TRUE;
/*N*/           bSetSimpleTextColWidths = TRUE;
/*N*/       }
/*N*/       else if (aFltName.EqualsAscii(pFilterDBase))
/*N*/       {
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 String sItStr;
//STRIP001 /*?*/            SfxItemSet*  pSet = rMedium.GetItemSet();
//STRIP001 /*?*/            const SfxPoolItem* pItem;
//STRIP001 /*?*/            if ( pSet && SFX_ITEM_SET ==
//STRIP001 /*?*/                 pSet->GetItemState( SID_FILE_FILTEROPTIONS, TRUE, &pItem ) )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                sItStr = ((const SfxStringItem*)pItem)->GetValue();
//STRIP001 /*?*/            }
//STRIP001 /*?*/
//STRIP001 /*?*/            if (sItStr.Len() == 0)
//STRIP001 /*?*/            {
//STRIP001 /*?*/                //  default for dBase import (from API without options):
//STRIP001 /*?*/                //  IBM_850 encoding
//STRIP001 /*?*/
//STRIP001 /*?*/                sItStr = ScGlobal::GetCharsetString( RTL_TEXTENCODING_IBM_850 );
//STRIP001 /*?*/            }
//STRIP001 /*?*/
//STRIP001 /*?*/            ULONG eError = DBaseImport( rMedium.GetPhysicalName(),
//STRIP001 /*?*/                    ScGlobal::GetCharsetValue(sItStr), bSimpleColWidth );
//STRIP001 /*?*/
//STRIP001 /*?*/            if (eError != eERR_OK)
//STRIP001 /*?*/            {
//STRIP001 /*?*/                if (!GetError())
//STRIP001 /*?*/                    SetError(eError);
//STRIP001 /*?*/                bRet = ( eError == SCWARN_IMPORT_RANGE_OVERFLOW );
//STRIP001 /*?*/            }
//STRIP001 /*?*/            else
//STRIP001 /*?*/                bRet = TRUE;
//STRIP001 /*?*/
//STRIP001 /*?*/            aColWidthRange.aStart.SetRow( 1 );  // Spaltenheader nicht
//STRIP001 /*?*/            bSetColWidths = TRUE;
//STRIP001 /*?*/            bSetSimpleTextColWidths = TRUE;
//STRIP001 /*?*/            // Memo-Felder fuehren zu einem bSimpleColWidth[nCol]==FALSE
//STRIP001 /*?*/            for ( USHORT nCol=0; nCol <= MAXCOL && !bSetRowHeights; nCol++ )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                if ( !bSimpleColWidth[nCol] )
//STRIP001 /*?*/                    bSetRowHeights = TRUE;
//STRIP001 /*?*/            }
/*N*/       }
/*N*/       else if (aFltName.EqualsAscii(pFilterDif))
/*N*/       {
/*?*/           SvStream* pStream = rMedium.GetInStream();
/*?*/           if (pStream)
/*?*/           {
/*?*/               DBG_BF_ASSERT(0, "STRIP"); //STRIP001 FltError eError;
//STRIP001 /*?*/                String sItStr;
//STRIP001 /*?*/                SfxItemSet*  pSet = rMedium.GetItemSet();
//STRIP001 /*?*/                const SfxPoolItem* pItem;
//STRIP001 /*?*/                if ( pSet && SFX_ITEM_SET ==
//STRIP001 /*?*/                     pSet->GetItemState( SID_FILE_FILTEROPTIONS, TRUE, &pItem ) )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    sItStr = ((const SfxStringItem*)pItem)->GetValue();
//STRIP001 /*?*/                }
//STRIP001 /*?*/
//STRIP001 /*?*/                if (sItStr.Len() == 0)
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    //  default for DIF import (from API without options):
//STRIP001 /*?*/                    //  ISO8859-1/MS_1252 encoding
//STRIP001 /*?*/
//STRIP001 /*?*/                    sItStr = ScGlobal::GetCharsetString( RTL_TEXTENCODING_MS_1252 );
//STRIP001 /*?*/                }
//STRIP001 /*?*/
//STRIP001 /*?*/                eError = ScImportDif( *pStream, &aDocument, ScAddress(0,0,0),
//STRIP001 /*?*/                                    ScGlobal::GetCharsetValue(sItStr));
//STRIP001 /*?*/                if (eError != eERR_OK)
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    if (!GetError())
//STRIP001 /*?*/                        SetError(eError);
//STRIP001 /*?*/
//STRIP001 /*?*/                    if( ( eError & ERRCODE_WARNING_MASK ) == ERRCODE_WARNING_MASK )
//STRIP001 /*?*/                        bRet = TRUE;
//STRIP001 /*?*/                }
//STRIP001 /*?*/                else
//STRIP001 /*?*/                    bRet = TRUE;
//STRIP001 /*?*/
//STRIP001 /*?*/                rMedium.CloseInStream();
/*?*/           }
/*?*/           bSetColWidths = TRUE;
/*?*/           bSetSimpleTextColWidths = TRUE;
/*N*/       }
/*N*/       else if (aFltName.EqualsAscii(pFilterSylk))
/*N*/       {
/*?*/           FltError eError = SCERR_IMPORT_UNKNOWN;
/*?*/           if( !rMedium.IsStorage() )
/*?*/           {
/*?*/               ScImportExport aImpEx( &aDocument );
/*?*/
/*?*/               SvStream* pInStream = rMedium.GetInStream();
/*?*/               if (pInStream)
/*?*/               {
/*?*/                   pInStream->Seek( 0 );
/*?*/                   bRet = aImpEx.ImportStream( *pInStream, SOT_FORMATSTR_ID_SYLK );
/*?*/                   eError = bRet ? eERR_OK : SCERR_IMPORT_UNKNOWN;
/*?*/                   aDocument.StartAllListeners();
/*?*/                   aDocument.SetDirty();
/*?*/               }
/*?*/               else
/*?*/                   DBG_ERROR( "No Stream" );
/*?*/           }
/*?*/
/*?*/           if ( eError != eERR_OK && !GetError() )
/*?*/               SetError(eError);
/*?*/           bSetColWidths = TRUE;
/*?*/           bSetSimpleTextColWidths = TRUE;
/*N*/       }
/*N*/       else if (aFltName.EqualsAscii(pFilterRtf))
/*N*/       {
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 FltError eError = SCERR_IMPORT_UNKNOWN;
//STRIP001 /*?*/            if( !rMedium.IsStorage() )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                SvStream* pInStream = rMedium.GetInStream();
//STRIP001 /*?*/                if (pInStream)
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    pInStream->Seek( 0 );
//STRIP001 /*?*/                    ScRange aRange;
//STRIP001 /*?*/                    eError = ScImportRTF( *pInStream, &aDocument, aRange );
//STRIP001 /*?*/                    if (eError != eERR_OK)
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        if (!GetError())
//STRIP001 /*?*/                            SetError(eError);
//STRIP001 /*?*/
//STRIP001 /*?*/                        if( ( eError & ERRCODE_WARNING_MASK ) == ERRCODE_WARNING_MASK )
//STRIP001 /*?*/                            bRet = TRUE;
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                    else
//STRIP001 /*?*/                        bRet = TRUE;
//STRIP001 /*?*/                    aDocument.StartAllListeners();
//STRIP001 /*?*/                    aDocument.SetDirty();
//STRIP001 /*?*/                    bSetColWidths = TRUE;
//STRIP001 /*?*/                    bSetRowHeights = TRUE;
//STRIP001 /*?*/                }
//STRIP001 /*?*/                else
//STRIP001 /*?*/                    DBG_ERROR( "No Stream" );
//STRIP001 /*?*/            }
//STRIP001 /*?*/
//STRIP001 /*?*/            if ( eError != eERR_OK && !GetError() )
//STRIP001 /*?*/                SetError(eError);
/*N*/       }
/*N*/       else if (aFltName.EqualsAscii(pFilterHtml) || aFltName.EqualsAscii(pFilterHtmlWebQ))
/*N*/       {
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 FltError eError = SCERR_IMPORT_UNKNOWN;
//STRIP001 /*?*/            BOOL bWebQuery = aFltName.EqualsAscii(pFilterHtmlWebQ);
//STRIP001 /*?*/            if( !rMedium.IsStorage() )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                SvStream* pInStream = rMedium.GetInStream();
//STRIP001 /*?*/                if (pInStream)
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    pInStream->Seek( 0 );
//STRIP001 /*?*/                    ScRange aRange;
//STRIP001 /*?*/                    // HTML macht eigenes ColWidth/RowHeight
//STRIP001 /*?*/                    CalcOutputFactor();
//STRIP001 /*?*/                    eError = ScImportHTML( *pInStream, &aDocument, aRange,
//STRIP001 /*?*/                                            GetOutputFactor(), !bWebQuery );
//STRIP001 /*?*/                    if (eError != eERR_OK)
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        if (!GetError())
//STRIP001 /*?*/                            SetError(eError);
//STRIP001 /*?*/
//STRIP001 /*?*/                        if( ( eError & ERRCODE_WARNING_MASK ) == ERRCODE_WARNING_MASK )
//STRIP001 /*?*/                            bRet = TRUE;
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                    else
//STRIP001 /*?*/                        bRet = TRUE;
//STRIP001 /*?*/                    aDocument.StartAllListeners();
//STRIP001 /*?*/                    aDocument.SetDirty();
//STRIP001 /*?*/                }
//STRIP001 /*?*/                else
//STRIP001 /*?*/                    DBG_ERROR( "No Stream" );
//STRIP001 /*?*/            }
//STRIP001 /*?*/
//STRIP001 /*?*/            if ( eError != eERR_OK && !GetError() )
//STRIP001 /*?*/                SetError(eError);
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           if (!GetError())
/*N*/               SetError(SCERR_IMPORT_NI);
/*N*/       }
/*N*/
/*N*/       if (!bCalc3)
/*N*/           aDocument.SetInsertingFromOtherDoc( FALSE );
/*N*/   }
/*N*/   else
/*N*/       DBG_ERROR("Kein Filter bei ConvertFrom");
/*N*/
/*N*/   InitItems();
/*N*/   CalcOutputFactor();
/*N*/   if ( bRet && (bSetColWidths || bSetRowHeights) )
/*N*/   {   // Spaltenbreiten/Zeilenhoehen anpassen, Basis 100% Zoom
/*N*/       Fraction aZoom( 1, 1 );
/*N*/       double nPPTX = ScGlobal::nScreenPPTX * (double) aZoom
/*N*/           / GetOutputFactor();    // Faktor ist Drucker zu Bildschirm
/*N*/       double nPPTY = ScGlobal::nScreenPPTY * (double) aZoom;
/*N*/       VirtualDevice aVirtDev;
/*N*/       //  all sheets (for Excel import)
/*N*/       USHORT nTabCount = aDocument.GetTableCount();
/*N*/       for (USHORT nTab=0; nTab<nTabCount; nTab++)
/*N*/       {
/*N*/           USHORT nEndCol, nEndRow;
/*N*/           aDocument.GetCellArea( nTab, nEndCol, nEndRow );
/*N*/           aColWidthRange.aEnd.SetCol( nEndCol );
/*N*/           aColWidthRange.aEnd.SetRow( nEndRow );
/*N*/           ScMarkData aMark;
/*N*/           aMark.SetMarkArea( aColWidthRange );
/*N*/           aMark.MarkToMulti();
/*N*/           // Reihenfolge erst Breite dann Hoehe ist wichtig (vergl. hund.rtf)
/*N*/           if ( bSetColWidths )
/*N*/           {
/*N*/               for ( USHORT nCol=0; nCol <= nEndCol; nCol++ )
/*N*/               {
/*N*/                   USHORT nWidth = aDocument.GetOptimalColWidth(
/*N*/                       nCol, nTab, &aVirtDev, nPPTX, nPPTY, aZoom, aZoom, FALSE, &aMark,
/*N*/                       (bSetSimpleTextColWidths && bSimpleColWidth[nCol]) );
/*N*/                   aDocument.SetColWidth( nCol, nTab,
/*N*/                       nWidth + (USHORT)ScGlobal::nLastColWidthExtra );
/*N*/               }
/*N*/           }
/*N*/ //            if ( bSetRowHeights )
/*N*/ //            {
/*N*/ //                //  nExtra must be 0
/*N*/ //                aDocument.SetOptimalHeight( 0, nEndRow, nTab, 0, &aVirtDev,
/*N*/ //                    nPPTX, nPPTY, aZoom, aZoom, FALSE );
/*N*/ //            }
/*N*/       }
/*N*/       if ( bSetRowHeights )
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 UpdateAllRowHeights();        // with vdev or printer, depending on configuration
/*N*/   }
/*N*/   FinishedLoading( SFX_LOADED_MAINDOCUMENT | SFX_LOADED_IMAGES );
/*N*/
/*N*/   // #73762# invalidate eventually temporary table areas
/*N*/   if ( bRet )
/*N*/       aDocument.InvalidateTableArea();
/*N*/
/*N*/   bIsEmpty = FALSE;
/*N*/
/*N*/   return bRet;
/*N*/ }


/*N*/ void __EXPORT ScDocShell::HandsOff()
/*N*/ {
/*N*/   ScDrawLayer* pDrawLayer = aDocument.GetDrawLayer();
/*N*/
/*N*/   SfxInPlaceObject::HandsOff();
/*N*/
/*N*/   if( pDrawLayer )
/*N*/       pDrawLayer->ReleasePictureStorage();
/*N*/ }


/*N*/ BOOL __EXPORT ScDocShell::Save()
/*N*/ {
/*N*/   RTL_LOGFILE_CONTEXT_AUTHOR ( aLog, "sc", "nn93723", "ScDocShell::Save" );
/*N*/
/*N*/   ScRefreshTimerProtector( aDocument.GetRefreshTimerControlAddress() );
/*N*/
/*N*/   SvStorage* pStor = GetStorage();
/*N*/   DBG_ASSERT( pStor, "Save: no storage" );
/*N*/   BOOL bXML = ( pStor->GetVersion() >= SOFFICE_FILEFORMAT_60 );
/*N*/
/*N*/   //  DoEnterHandler hier nicht (wegen AutoSave), ist im ExecuteSave
/*N*/
/*N*/   ScChartListenerCollection* pCharts = aDocument.GetChartListenerCollection();
/*N*/   if (pCharts)
/*N*/       pCharts->UpdateDirtyCharts();                   // Charts, die noch upgedated werden muessen
/*N*/   if (pAutoStyleList)
/*?*/       {DBG_BF_ASSERT(0, "STRIP");} //STRIP001 pAutoStyleList->ExecuteAllNow();                // Vorlagen-Timeouts jetzt ausfuehren
/*N*/   if (GetCreateMode()== SFX_CREATE_MODE_STANDARD)
/*N*/       SvInPlaceObject::SetVisArea( Rectangle() );     // normal bearbeitet -> keine VisArea
/*N*/
/*N*/   // #77577# save additionally XML in storage
/*N*/   if ( GetCreateMode() != SFX_CREATE_MODE_EMBEDDED && !bXML )
/*N*/       AddXMLAsZipToTheStorage( *pStor );
/*N*/
/*N*/   //  wait cursor is handled with progress bar
/*N*/   BOOL bRet = SfxInPlaceObject::Save();
/*N*/   if( bRet )
/*N*/   {
/*N*/       if (bXML)
/*N*/           bRet = SaveXML( NULL, pStor );
/*N*/       else
/*N*/           bRet = SaveCalc( pStor );
/*N*/   }
/*N*/   return bRet;
/*N*/ }


/*N*/ BOOL __EXPORT ScDocShell::SaveAs( SvStorage* pStor )
/*N*/ {
/*N*/   RTL_LOGFILE_CONTEXT_AUTHOR ( aLog, "sc", "nn93723", "ScDocShell::SaveAs" );
/*N*/
/*N*/   ScRefreshTimerProtector( aDocument.GetRefreshTimerControlAddress() );
/*N*/
/*N*/   DBG_ASSERT( pStor, "SaveAs without storage?" );
/*N*/   BOOL bXML = ( pStor->GetVersion() >= SOFFICE_FILEFORMAT_60 );
/*N*/
/*N*/   //  DoEnterHandler hier nicht (wegen AutoSave), ist im ExecuteSave
/*N*/
/*N*/   ScChartListenerCollection* pCharts = aDocument.GetChartListenerCollection();
/*N*/   if (pCharts)
/*N*/       pCharts->UpdateDirtyCharts();                   // Charts, die noch upgedated werden muessen
/*N*/   if (pAutoStyleList)
/*?*/       {DBG_BF_ASSERT(0, "STRIP");} //STRIP001 pAutoStyleList->ExecuteAllNow();                // Vorlagen-Timeouts jetzt ausfuehren
/*N*/   if (GetCreateMode()== SFX_CREATE_MODE_STANDARD)
/*N*/       SvInPlaceObject::SetVisArea( Rectangle() );     // normal bearbeitet -> keine VisArea
/*N*/
/*N*/   // #77577# save additionally XML in storage
/*N*/   if ( GetCreateMode() != SFX_CREATE_MODE_EMBEDDED && !bXML )
/*N*/       AddXMLAsZipToTheStorage( *pStor );
/*N*/
/*N*/   //  wait cursor is handled with progress bar
/*N*/   BOOL bRet = SfxInPlaceObject::SaveAs( pStor );
/*N*/   if( bRet )
/*N*/   {
/*N*/       if (bXML)
/*N*/           bRet = SaveXML( NULL, pStor );
/*N*/       else
/*N*/           bRet = SaveCalc( pStor );
/*N*/   }
/*N*/
/*N*/   return bRet;
/*N*/ }


//STRIP001 BOOL __EXPORT ScDocShell::IsInformationLost()
//STRIP001 {
//STRIP001 /*
//STRIP001  const SfxFilter *pFilt = GetMedium()->GetFilter();
//STRIP001  BOOL bRet = pFilt && pFilt->IsAlienFormat() && bNoInformLost;
//STRIP001  if (bNoInformLost)                  // nur einmal!!
//STRIP001      bNoInformLost = FALSE;
//STRIP001  return bRet;
//STRIP001 */
//STRIP001  //!!! bei Gelegenheit ein korrekte eigene Behandlung einbauen
//STRIP001
//STRIP001  return SfxObjectShell::IsInformationLost();
//STRIP001 }


// Xcl-like column width measured in characters of standard font.
//STRIP001 xub_StrLen lcl_ScDocShell_GetColWidthInChars( USHORT nWidth )
//STRIP001 {
//STRIP001     // double fColScale = 1.0;
//STRIP001  double  f = nWidth;
//STRIP001  f *= 1328.0 / 25.0;
//STRIP001  f += 90.0;
//STRIP001  f *= 1.0 / 23.0;
//STRIP001  // f /= fColScale * 256.0;
//STRIP001  f /= 256.0;
//STRIP001
//STRIP001  return xub_StrLen( f );
//STRIP001 }


//STRIP001 void lcl_ScDocShell_GetFixedWidthString( String& rStr, const ScDocument& rDoc,
//STRIP001         USHORT nTab, USHORT nCol, BOOL bValue, SvxCellHorJustify eHorJust )
//STRIP001 {
//STRIP001     xub_StrLen nLen = lcl_ScDocShell_GetColWidthInChars(
//STRIP001             rDoc.GetColWidth( nCol, nTab ) );
//STRIP001     if ( nLen < rStr.Len() )
//STRIP001     {
//STRIP001         if ( bValue )
//STRIP001             rStr.AssignAscii( "###" );
//STRIP001         rStr.Erase( nLen );
//STRIP001     }
//STRIP001     if ( nLen > rStr.Len() )
//STRIP001     {
//STRIP001         if ( bValue && eHorJust == SVX_HOR_JUSTIFY_STANDARD )
//STRIP001             eHorJust = SVX_HOR_JUSTIFY_RIGHT;
//STRIP001         switch ( eHorJust )
//STRIP001         {
//STRIP001             case SVX_HOR_JUSTIFY_RIGHT:
//STRIP001             {
//STRIP001                 String aTmp;
//STRIP001                 aTmp.Fill( nLen - rStr.Len() );
//STRIP001                 rStr.Insert( aTmp, 0 );
//STRIP001             }
//STRIP001             break;
//STRIP001             case SVX_HOR_JUSTIFY_CENTER:
//STRIP001             {
//STRIP001                 xub_StrLen nLen2 = (nLen - rStr.Len()) / 2;
//STRIP001                 String aTmp;
//STRIP001                 aTmp.Fill( nLen2 );
//STRIP001                 rStr.Insert( aTmp, 0 );
//STRIP001                 rStr.Expand( nLen );
//STRIP001             }
//STRIP001             break;
//STRIP001             default:
//STRIP001                 rStr.Expand( nLen );
//STRIP001         }
//STRIP001     }
//STRIP001 }


//STRIP001 void lcl_ScDocShell_WriteEmptyFixedWidthString( SvStream& rStream,
//STRIP001         const ScDocument& rDoc, USHORT nTab, USHORT nCol )
//STRIP001 {
//STRIP001     String aString;
//STRIP001     lcl_ScDocShell_GetFixedWidthString( aString, rDoc, nTab, nCol, FALSE,
//STRIP001             SVX_HOR_JUSTIFY_STANDARD );
//STRIP001     rStream.WriteUnicodeOrByteText( aString );
//STRIP001 }


//STRIP001 void ScDocShell::AsciiSave( SvStream& rStream, const ScImportOptions& rAsciiOpt )
//STRIP001 {
//STRIP001     sal_Unicode cDelim    = rAsciiOpt.nFieldSepCode;
//STRIP001     sal_Unicode cStrDelim = rAsciiOpt.nTextSepCode;
//STRIP001     CharSet eCharSet      = rAsciiOpt.eCharSet;
//STRIP001     BOOL bFixedWidth      = rAsciiOpt.bFixedWidth;
//STRIP001
//STRIP001  CharSet eOldCharSet = rStream.GetStreamCharSet();
//STRIP001  rStream.SetStreamCharSet( eCharSet );
//STRIP001  USHORT nOldNumberFormatInt = rStream.GetNumberFormatInt();
//STRIP001     ByteString aStrDelimEncoded;    // only used if not Unicode
//STRIP001     UniString aStrDelimDecoded;     // only used if context encoding
//STRIP001     BOOL bContextOrNotAsciiEncoding;
//STRIP001  if ( eCharSet == RTL_TEXTENCODING_UNICODE )
//STRIP001     {
//STRIP001      rStream.StartWritingUnicodeText();
//STRIP001         bContextOrNotAsciiEncoding = FALSE;
//STRIP001     }
//STRIP001     else
//STRIP001     {
//STRIP001         aStrDelimEncoded = ByteString( cStrDelim, eCharSet );
//STRIP001         rtl_TextEncodingInfo aInfo;
//STRIP001         aInfo.StructSize = sizeof(aInfo);
//STRIP001         if ( rtl_getTextEncodingInfo( eCharSet, &aInfo ) )
//STRIP001         {
//STRIP001             bContextOrNotAsciiEncoding =
//STRIP001                 (((aInfo.Flags & RTL_TEXTENCODING_INFO_CONTEXT) != 0) ||
//STRIP001                  ((aInfo.Flags & RTL_TEXTENCODING_INFO_ASCII) == 0));
//STRIP001             if ( bContextOrNotAsciiEncoding )
//STRIP001                 aStrDelimDecoded = String( aStrDelimEncoded, eCharSet );
//STRIP001         }
//STRIP001         else
//STRIP001             bContextOrNotAsciiEncoding = FALSE;
//STRIP001     }
//STRIP001
//STRIP001  USHORT nStartCol = 0;
//STRIP001  USHORT nStartRow = 0;
//STRIP001  USHORT nTab = GetSaveTab();
//STRIP001  USHORT nEndCol, nEndRow;
//STRIP001  aDocument.GetCellArea( nTab, nEndCol, nEndRow );
//STRIP001
//STRIP001  ScProgress aProgress( this, ScGlobal::GetRscString( STR_SAVE_DOC ), nEndRow );
//STRIP001
//STRIP001  String aString;
//STRIP001
//STRIP001  ScTabViewShell* pViewSh = PTR_CAST(ScTabViewShell, SfxViewShell::Current());
//STRIP001  const ScViewOptions& rOpt = (pViewSh)
//STRIP001                              ? pViewSh->GetViewData()->GetOptions()
//STRIP001                              : aDocument.GetViewOptions();
//STRIP001  BOOL bShowFormulas = rOpt.GetOption( VOPT_FORMULAS );
//STRIP001  BOOL bTabProtect = aDocument.IsTabProtected( nTab );
//STRIP001
//STRIP001  USHORT nCol;
//STRIP001  USHORT nRow;
//STRIP001  USHORT nNextCol = nStartCol;
//STRIP001  USHORT nNextRow = nStartRow;
//STRIP001  USHORT nEmptyCol, nEmptyRow;
//STRIP001  SvNumberFormatter& rFormatter = *aDocument.GetFormatTable();
//STRIP001
//STRIP001  ScHorizontalCellIterator aIter( &aDocument, nTab, nStartCol, nStartRow,
//STRIP001      nEndCol, nEndRow );
//STRIP001  ScBaseCell* pCell;
//STRIP001  while ( pCell = aIter.GetNext( nCol, nRow ) )
//STRIP001     {
//STRIP001         BOOL bProgress = FALSE;      // only upon line change
//STRIP001         if ( nNextRow < nRow )
//STRIP001         {   // empty rows or/and empty columns up to end of row
//STRIP001             bProgress = TRUE;
//STRIP001             for ( nEmptyCol = nNextCol; nEmptyCol < nEndCol; nEmptyCol++ )
//STRIP001             {   // remaining columns of last row
//STRIP001                 if ( bFixedWidth )
//STRIP001                     lcl_ScDocShell_WriteEmptyFixedWidthString( rStream,
//STRIP001                             aDocument, nTab, nEmptyCol );
//STRIP001                 else if ( cDelim != 0 )
//STRIP001                     rStream.WriteUniOrByteChar( cDelim );
//STRIP001             }
//STRIP001             endlub( rStream );
//STRIP001             nNextRow++;
//STRIP001             for ( nEmptyRow = nNextRow; nEmptyRow < nRow; nEmptyRow++ )
//STRIP001             {   // completely empty rows
//STRIP001                 for ( nEmptyCol = nStartCol; nEmptyCol < nEndCol; nEmptyCol++ )
//STRIP001                 {
//STRIP001                     if ( bFixedWidth )
//STRIP001                         lcl_ScDocShell_WriteEmptyFixedWidthString( rStream,
//STRIP001                                 aDocument, nTab, nEmptyCol );
//STRIP001                     else if ( cDelim != 0 )
//STRIP001                         rStream.WriteUniOrByteChar( cDelim );
//STRIP001                 }
//STRIP001                 endlub( rStream );
//STRIP001             }
//STRIP001             for ( nEmptyCol = nStartCol; nEmptyCol < nCol; nEmptyCol++ )
//STRIP001             {   // empty columns at beginning of row
//STRIP001                 if ( bFixedWidth )
//STRIP001                     lcl_ScDocShell_WriteEmptyFixedWidthString( rStream,
//STRIP001                             aDocument, nTab, nEmptyCol );
//STRIP001                 else if ( cDelim != 0 )
//STRIP001                     rStream.WriteUniOrByteChar( cDelim );
//STRIP001             }
//STRIP001             nNextRow = nRow;
//STRIP001         }
//STRIP001         else if ( nNextCol < nCol )
//STRIP001         {   // empty columns in same row
//STRIP001             for ( nEmptyCol = nNextCol; nEmptyCol < nCol; nEmptyCol++ )
//STRIP001             {   // columns in between
//STRIP001                 if ( bFixedWidth )
//STRIP001                     lcl_ScDocShell_WriteEmptyFixedWidthString( rStream,
//STRIP001                             aDocument, nTab, nEmptyCol );
//STRIP001                 else if ( cDelim != 0 )
//STRIP001                     rStream.WriteUniOrByteChar( cDelim );
//STRIP001             }
//STRIP001         }
//STRIP001         if ( nCol == nEndCol )
//STRIP001         {
//STRIP001             bProgress = TRUE;
//STRIP001             nNextCol = nStartCol;
//STRIP001             nNextRow = nRow + 1;
//STRIP001         }
//STRIP001         else
//STRIP001             nNextCol = nCol + 1;
//STRIP001
//STRIP001         CellType eType = pCell->GetCellType();
//STRIP001         if ( bTabProtect )
//STRIP001         {
//STRIP001             const ScProtectionAttr* pProtAttr =
//STRIP001                 (const ScProtectionAttr*) aDocument.GetAttr(
//STRIP001                                                             nCol, nRow, nTab, ATTR_PROTECTION );
//STRIP001             if ( pProtAttr->GetHideCell() ||
//STRIP001                     ( eType == CELLTYPE_FORMULA && bShowFormulas &&
//STRIP001                       pProtAttr->GetHideFormula() ) )
//STRIP001                 eType = CELLTYPE_NONE;   // hide
//STRIP001         }
//STRIP001         BOOL bString;
//STRIP001         switch ( eType )
//STRIP001         {
//STRIP001             case CELLTYPE_NOTE:
//STRIP001             case CELLTYPE_NONE:
//STRIP001                 aString.Erase();
//STRIP001                 bString = FALSE;
//STRIP001                 break;
//STRIP001             case CELLTYPE_FORMULA :
//STRIP001                 {
//STRIP001                     USHORT nErrCode;
//STRIP001                     if ( bShowFormulas )
//STRIP001                     {
//STRIP001                         ((ScFormulaCell*)pCell)->GetFormula( aString );
//STRIP001                         bString = TRUE;
//STRIP001                     }
//STRIP001                     else if ( nErrCode = ((ScFormulaCell*)pCell)->GetErrCode() )
//STRIP001                     {
//STRIP001                         aString = ScGlobal::GetErrorString( nErrCode );
//STRIP001                         bString = TRUE;
//STRIP001                     }
//STRIP001                     else if ( ((ScFormulaCell*)pCell)->IsValue() )
//STRIP001                     {
//STRIP001                         ULONG nFormat;
//STRIP001                         aDocument.GetNumberFormat( nCol, nRow, nTab, nFormat );
//STRIP001                         if ( bFixedWidth )
//STRIP001                         {
//STRIP001                             Color* pDummy;
//STRIP001                             ScCellFormat::GetString( pCell, nFormat, aString, &pDummy, rFormatter );
//STRIP001                         }
//STRIP001                         else
//STRIP001                             ScCellFormat::GetInputString( pCell, nFormat, aString, rFormatter );
//STRIP001                         bString = FALSE;
//STRIP001                     }
//STRIP001                     else
//STRIP001                     {
//STRIP001                         ((ScFormulaCell*)pCell)->GetString( aString );
//STRIP001                         bString = TRUE;
//STRIP001                     }
//STRIP001                 }
//STRIP001                 break;
//STRIP001             case CELLTYPE_STRING :
//STRIP001                 ((ScStringCell*)pCell)->GetString( aString );
//STRIP001                 bString = TRUE;
//STRIP001                 break;
//STRIP001             case CELLTYPE_EDIT :
//STRIP001                 ((ScEditCell*)pCell)->GetString( aString );
//STRIP001                 bString = TRUE;
//STRIP001                 break;
//STRIP001             case CELLTYPE_VALUE :
//STRIP001                 {
//STRIP001                     ULONG nFormat;
//STRIP001                     aDocument.GetNumberFormat( nCol, nRow, nTab, nFormat );
//STRIP001                     if ( bFixedWidth )
//STRIP001                     {
//STRIP001                         Color* pDummy;
//STRIP001                         ScCellFormat::GetString( pCell, nFormat, aString, &pDummy, rFormatter );
//STRIP001                     }
//STRIP001                     else
//STRIP001                         ScCellFormat::GetInputString( pCell, nFormat, aString, rFormatter );
//STRIP001                     bString = FALSE;
//STRIP001                 }
//STRIP001                 break;
//STRIP001             default:
//STRIP001                 DBG_ERROR( "ScDocShell::AsciiSave: unknown CellType" );
//STRIP001                 aString.Erase();
//STRIP001                 bString = FALSE;
//STRIP001         }
//STRIP001
//STRIP001         if ( bFixedWidth )
//STRIP001         {
//STRIP001             SvxCellHorJustify eHorJust = (SvxCellHorJustify)
//STRIP001                 ((const SvxHorJustifyItem*) aDocument.GetAttr( nCol, nRow,
//STRIP001                 nTab, ATTR_HOR_JUSTIFY ))->GetValue();
//STRIP001             lcl_ScDocShell_GetFixedWidthString( aString, aDocument, nTab, nCol,
//STRIP001                     !bString, eHorJust );
//STRIP001             rStream.WriteUnicodeOrByteText( aString );
//STRIP001         }
//STRIP001         else if ( bString )
//STRIP001         {
//STRIP001             if ( cStrDelim != 0 ) //@ BugId 55355
//STRIP001             {
//STRIP001                 if ( eCharSet == RTL_TEXTENCODING_UNICODE )
//STRIP001                 {
//STRIP001                     xub_StrLen nPos = aString.Search( cStrDelim );
//STRIP001                     while ( nPos != STRING_NOTFOUND )
//STRIP001                     {
//STRIP001                         aString.Insert( cStrDelim, nPos );
//STRIP001                         nPos = aString.Search( cStrDelim, nPos+2 );
//STRIP001                     }
//STRIP001                     rStream.WriteUniOrByteChar( cStrDelim, eCharSet );
//STRIP001                     rStream.WriteUnicodeText( aString );
//STRIP001                     rStream.WriteUniOrByteChar( cStrDelim, eCharSet );
//STRIP001                 }
//STRIP001                 else
//STRIP001                 {
//STRIP001                     // #105549# This is nasty. The Unicode to byte encoding
//STRIP001                     // may convert typographical quotation marks to ASCII
//STRIP001                     // quotation marks, which may interfer with the delimiter,
//STRIP001                     // so we have to escape delimiters after the string has
//STRIP001                     // been encoded. Since this may happen also with UTF-8
//STRIP001                     // encoded typographical quotation marks if such was
//STRIP001                     // specified as a delimiter we have to check for the full
//STRIP001                     // encoded delimiter string, not just one character.
//STRIP001                     // Now for RTL_TEXTENCODING_ISO_2022_... and similar brain
//STRIP001                     // dead encodings where one code point (and especially a
//STRIP001                     // low ASCII value) may represent different characters, we
//STRIP001                     // have to convert forth and back and forth again. Same for
//STRIP001                     // UTF-7 since it is a context sensitive encoding too.
//STRIP001
//STRIP001                     if ( bContextOrNotAsciiEncoding )
//STRIP001                     {
//STRIP001                         // to byte encoding
//STRIP001                         ByteString aStrEnc( aString, eCharSet );
//STRIP001                         // back to Unicode
//STRIP001                         UniString aStrDec( aStrEnc, eCharSet );
//STRIP001                         // search on re-decoded string
//STRIP001                         xub_StrLen nPos = aStrDec.Search( aStrDelimDecoded );
//STRIP001                         while ( nPos != STRING_NOTFOUND )
//STRIP001                         {
//STRIP001                             aStrDec.Insert( aStrDelimDecoded, nPos );
//STRIP001                             nPos = aStrDec.Search( aStrDelimDecoded,
//STRIP001                                     nPos+1+aStrDelimDecoded.Len() );
//STRIP001                         }
//STRIP001                         // write byte re-encoded
//STRIP001                         rStream.WriteUniOrByteChar( cStrDelim, eCharSet );
//STRIP001                         rStream.WriteUnicodeOrByteText( aStrDec, eCharSet );
//STRIP001                         rStream.WriteUniOrByteChar( cStrDelim, eCharSet );
//STRIP001                     }
//STRIP001                     else
//STRIP001                     {
//STRIP001                         ByteString aStrEnc( aString, eCharSet );
//STRIP001                         // search on encoded string
//STRIP001                         xub_StrLen nPos = aStrEnc.Search( aStrDelimEncoded );
//STRIP001                         while ( nPos != STRING_NOTFOUND )
//STRIP001                         {
//STRIP001                             aStrEnc.Insert( aStrDelimEncoded, nPos );
//STRIP001                             nPos = aStrEnc.Search( aStrDelimEncoded,
//STRIP001                                     nPos+1+aStrDelimEncoded.Len() );
//STRIP001                         }
//STRIP001                         // write byte encoded
//STRIP001                         rStream.Write( aStrDelimEncoded.GetBuffer(),
//STRIP001                                 aStrDelimEncoded.Len() );
//STRIP001                         rStream.Write( aStrEnc.GetBuffer(), aStrEnc.Len() );
//STRIP001                         rStream.Write( aStrDelimEncoded.GetBuffer(),
//STRIP001                                 aStrDelimEncoded.Len() );
//STRIP001                     }
//STRIP001                 }
//STRIP001             }
//STRIP001             else
//STRIP001                 rStream.WriteUnicodeOrByteText( aString );
//STRIP001         }
//STRIP001         else
//STRIP001             rStream.WriteUnicodeOrByteText( aString );
//STRIP001
//STRIP001         if( nCol < nEndCol )
//STRIP001         {
//STRIP001             if(cDelim!=0) //@ BugId 55355
//STRIP001                 rStream.WriteUniOrByteChar( cDelim );
//STRIP001         }
//STRIP001         else
//STRIP001             endlub( rStream );
//STRIP001
//STRIP001         if ( bProgress )
//STRIP001             aProgress.SetStateOnPercent( nRow );
//STRIP001     }
//STRIP001
//STRIP001  // write out empty if requested
//STRIP001  if ( nNextRow <= nEndRow )
//STRIP001  {
//STRIP001         for ( nEmptyCol = nNextCol; nEmptyCol < nEndCol; nEmptyCol++ )
//STRIP001         {    // remaining empty columns of last row
//STRIP001             if ( bFixedWidth )
//STRIP001                 lcl_ScDocShell_WriteEmptyFixedWidthString( rStream,
//STRIP001                         aDocument, nTab, nEmptyCol );
//STRIP001             else if ( cDelim != 0 )
//STRIP001                 rStream.WriteUniOrByteChar( cDelim );
//STRIP001         }
//STRIP001      endlub( rStream );
//STRIP001      nNextRow++;
//STRIP001  }
//STRIP001  for ( nEmptyRow = nNextRow; nEmptyRow <= nEndRow; nEmptyRow++ )
//STRIP001  {   // entire empty rows
//STRIP001         for ( nEmptyCol = nStartCol; nEmptyCol < nEndCol; nEmptyCol++ )
//STRIP001         {
//STRIP001             if ( bFixedWidth )
//STRIP001                 lcl_ScDocShell_WriteEmptyFixedWidthString( rStream,
//STRIP001                         aDocument, nTab, nEmptyCol );
//STRIP001             else if ( cDelim != 0 )
//STRIP001                 rStream.WriteUniOrByteChar( cDelim );
//STRIP001         }
//STRIP001      endlub( rStream );
//STRIP001  }
//STRIP001
//STRIP001  rStream.SetStreamCharSet( eOldCharSet );
//STRIP001  rStream.SetNumberFormatInt( nOldNumberFormatInt );
//STRIP001 }


//STRIP001 BOOL __EXPORT ScDocShell::ConvertTo( SfxMedium &rMed )
//STRIP001 {
//STRIP001  RTL_LOGFILE_CONTEXT_AUTHOR ( aLog, "sc", "nn93723", "ScDocShell::ConvertTo" );
//STRIP001
//STRIP001  ScRefreshTimerProtector( aDocument.GetRefreshTimerControlAddress() );
//STRIP001
//STRIP001     //  #i6500# don't call DoEnterHandler here (doesn't work with AutoSave),
//STRIP001     //  it's already in ExecuteSave (as for Save and SaveAs)
//STRIP001
//STRIP001  if (pAutoStyleList)
//STRIP001      pAutoStyleList->ExecuteAllNow();                // Vorlagen-Timeouts jetzt ausfuehren
//STRIP001  if (GetCreateMode()== SFX_CREATE_MODE_STANDARD)
//STRIP001      SvInPlaceObject::SetVisArea( Rectangle() );     // normal bearbeitet -> keine VisArea
//STRIP001
//STRIP001  DBG_ASSERT( rMed.GetFilter(), "Filter == 0" );
//STRIP001
//STRIP001  BOOL bRet = FALSE;
//STRIP001  String aFltName = rMed.GetFilter()->GetFilterName();
//STRIP001
//STRIP001 /*
//STRIP001  if (aFltName.EqualsAscii(pFilterLotus))
//STRIP001  {
//STRIP001      SvStream* pStream = rMed.GetOutStream();
//STRIP001      if (pStream)
//STRIP001      {
//STRIP001          FltError eError = ScExportLotus123( *pStream, &aDocument, ExpWK1,
//STRIP001                                              CHARSET_IBMPC_437 );
//STRIP001          bRet = eError == eERR_OK;
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001 */
//STRIP001  if ( aFltName.EqualsAscii(pFilterSc30) || aFltName.EqualsAscii(pFilterSc40) )
//STRIP001  {
//STRIP001      //  Calc3/4 - "Export"
//STRIP001      //! wird nicht gerufen (geht ueber Save/SaveAs) - wird das noch gebraucht ???????
//STRIP001
//STRIP001      DBG_ERROR("ConvertTo fuer altes Calc gibt's noch...");
//STRIP001      SvStorage* pStor = rMed.GetStorage();
//STRIP001      if ( pStor )
//STRIP001      {
//STRIP001          //  wait cursor is handled with progress bar
//STRIP001          bRet = SfxInPlaceObject::SaveAs( pStor );
//STRIP001          if( bRet )
//STRIP001              bRet = SaveCalc( pStor );
//STRIP001
//STRIP001          String aShortTypeName = String( ScResId(SCSTR_SHORT_SCDOC_NAME) );  // "Dokument"
//STRIP001          if ( aFltName.EqualsAscii(pFilterSc30) )
//STRIP001          {
//STRIP001              //  Ole-Geraffel auf 3.0-Werte setzen:
//STRIP001              SvGlobalName aName( BF_SO3_SC_CLASSID_30 );
//STRIP001              UINT32 nClip = SOT_FORMATSTR_ID_STARCALC_30;
//STRIP001              pStor->SetClass( aName, nClip, aShortTypeName );
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              //  Ole-Geraffel auf 4.0-Werte setzen:
//STRIP001              SvGlobalName aName( BF_SO3_SC_CLASSID_40 );
//STRIP001              UINT32 nClip = SOT_FORMATSTR_ID_STARCALC_40;
//STRIP001              pStor->SetClass( aName, nClip, aShortTypeName );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  else if (aFltName.EqualsAscii(pFilterXML))
//STRIP001  {
//STRIP001      bRet = SaveXML( &rMed, NULL );
//STRIP001  }
//STRIP001  else if (aFltName.EqualsAscii(pFilterExcel5) || aFltName.EqualsAscii(pFilterExcel95) ||
//STRIP001           aFltName.EqualsAscii(pFilterExcel97) || aFltName.EqualsAscii(pFilterEx5Temp) ||
//STRIP001           aFltName.EqualsAscii(pFilterEx95Temp) || aFltName.EqualsAscii(pFilterEx97Temp))
//STRIP001  {
//STRIP001      WaitObject aWait( GetDialogParent() );
//STRIP001
//STRIP001      ScTabViewShell* pViewShell = GetBestViewShell();
//STRIP001      if( pViewShell )
//STRIP001      {
//STRIP001             ScExtDocOptions* pExtDocOpt = aDocument.GetExtDocOptions();
//STRIP001             if( !pExtDocOpt )
//STRIP001                 aDocument.SetExtDocOptions( pExtDocOpt = new ScExtDocOptions );
//STRIP001          pViewShell->GetViewData()->WriteExtOptions( *pExtDocOpt );
//STRIP001      }
//STRIP001
//STRIP001      BOOL bFake97 = ( aFltName.EqualsAscii(pFilterExcel97) || aFltName.EqualsAscii(pFilterEx97Temp) );
//STRIP001      FltError eError = ScExportExcel5( rMed, &aDocument, bFake97, RTL_TEXTENCODING_MS_1252 );
//STRIP001
//STRIP001      if (eError && !GetError())
//STRIP001          SetError(eError);
//STRIP001
//STRIP001      if( ( eError & ERRCODE_WARNING_MASK ) == ERRCODE_WARNING_MASK )
//STRIP001          bRet = TRUE;
//STRIP001      else
//STRIP001          bRet = eError == eERR_OK;
//STRIP001  }
//STRIP001  else if (aFltName.EqualsAscii(pFilterAscii))
//STRIP001  {
//STRIP001      SvStream* pStream = rMed.GetOutStream();
//STRIP001      if (pStream)
//STRIP001      {
//STRIP001          String sItStr;
//STRIP001          SfxItemSet*  pSet = rMed.GetItemSet();
//STRIP001          const SfxPoolItem* pItem;
//STRIP001          if ( pSet && SFX_ITEM_SET ==
//STRIP001               pSet->GetItemState( SID_FILE_FILTEROPTIONS, TRUE, &pItem ) )
//STRIP001          {
//STRIP001              sItStr = ((const SfxStringItem*)pItem)->GetValue();
//STRIP001          }
//STRIP001
//STRIP001          if ( sItStr.Len() == 0 )
//STRIP001          {
//STRIP001              //  default for ascii export (from API without options):
//STRIP001              //  ISO8859-1/MS_1252 encoding, comma, double quotes
//STRIP001
//STRIP001              ScImportOptions aDefOptions( ',', '"', RTL_TEXTENCODING_MS_1252 );
//STRIP001              sItStr = aDefOptions.BuildString();
//STRIP001          }
//STRIP001
//STRIP001          WaitObject aWait( GetDialogParent() );
//STRIP001          ScImportOptions aOptions( sItStr );
//STRIP001          AsciiSave( *pStream, aOptions );
//STRIP001          bRet = TRUE;
//STRIP001
//STRIP001          if (aDocument.GetTableCount() > 1)
//STRIP001              if (!rMed.GetError())
//STRIP001                  rMed.SetError(SCWARN_EXPORT_ASCII);
//STRIP001      }
//STRIP001  }
//STRIP001  else if (aFltName.EqualsAscii(pFilterDBase))
//STRIP001  {
//STRIP001      String sCharSet;
//STRIP001      SfxItemSet* pSet = rMed.GetItemSet();
//STRIP001      const SfxPoolItem* pItem;
//STRIP001      if ( pSet && SFX_ITEM_SET ==
//STRIP001           pSet->GetItemState( SID_FILE_FILTEROPTIONS, TRUE, &pItem ) )
//STRIP001      {
//STRIP001          sCharSet = ((const SfxStringItem*)pItem)->GetValue();
//STRIP001      }
//STRIP001
//STRIP001      if (sCharSet.Len() == 0)
//STRIP001      {
//STRIP001          //  default for dBase export (from API without options):
//STRIP001          //  IBM_850 encoding
//STRIP001
//STRIP001          sCharSet = ScGlobal::GetCharsetString( RTL_TEXTENCODING_IBM_850 );
//STRIP001      }
//STRIP001
//STRIP001      WaitObject aWait( GetDialogParent() );
//STRIP001 // HACK damit Sba geoffnetes TempFile ueberschreiben kann
//STRIP001      rMed.CloseOutStream();
//STRIP001      BOOL bHasMemo = FALSE;
//STRIP001
//STRIP001      ULONG eError = DBaseExport( rMed.GetPhysicalName(),
//STRIP001                      ScGlobal::GetCharsetValue(sCharSet), bHasMemo );
//STRIP001
//STRIP001      if ( eError != eERR_OK && (eError & ERRCODE_WARNING_MASK) )
//STRIP001      {
//STRIP001 //!          if ( !rMed.GetError() )
//STRIP001 //!              rMed.SetError( eError );
//STRIP001          eError = eERR_OK;
//STRIP001      }
//STRIP001 //!      else if ( aDocument.GetTableCount() > 1 && !rMed.GetError() )
//STRIP001 //!          rMed.SetError( SCWARN_EXPORT_ASCII );
//STRIP001
//STRIP001      INetURLObject aTmpFile( rMed.GetPhysicalName(), INET_PROT_FILE );
//STRIP001      if ( bHasMemo )
//STRIP001          aTmpFile.setExtension( String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("dbt")) );
//STRIP001      if ( eError != eERR_OK )
//STRIP001      {
//STRIP001          if (!GetError())
//STRIP001              SetError(eError);
//STRIP001          if ( bHasMemo && IsDocument( aTmpFile ) )
//STRIP001              KillFile( aTmpFile );
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          bRet = TRUE;
//STRIP001          if ( bHasMemo )
//STRIP001          {
//STRIP001              SfxStringItem* pNameItem =
//STRIP001                  (SfxStringItem*) rMed.GetItemSet()->GetItem( SID_FILE_NAME );
//STRIP001              INetURLObject aDbtFile( pNameItem->GetValue(), INET_PROT_FILE );
//STRIP001              aDbtFile.setExtension( String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("dbt")) );
//STRIP001              if ( IsDocument( aDbtFile ) && !KillFile( aDbtFile ) )
//STRIP001                  bRet = FALSE;
//STRIP001              if ( bRet && !MoveFile( aTmpFile, aDbtFile ) )
//STRIP001                  bRet = FALSE;
//STRIP001              if ( !bRet )
//STRIP001              {
//STRIP001                  KillFile( aTmpFile );
//STRIP001                  if ( !GetError() )
//STRIP001                      SetError( SCERR_EXPORT_DATA );
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  else if (aFltName.EqualsAscii(pFilterDif))
//STRIP001  {
//STRIP001      SvStream* pStream = rMed.GetOutStream();
//STRIP001      if (pStream)
//STRIP001      {
//STRIP001          String sItStr;
//STRIP001          SfxItemSet*  pSet = rMed.GetItemSet();
//STRIP001          const SfxPoolItem* pItem;
//STRIP001          if ( pSet && SFX_ITEM_SET ==
//STRIP001               pSet->GetItemState( SID_FILE_FILTEROPTIONS, TRUE, &pItem ) )
//STRIP001          {
//STRIP001              sItStr = ((const SfxStringItem*)pItem)->GetValue();
//STRIP001          }
//STRIP001
//STRIP001          if (sItStr.Len() == 0)
//STRIP001          {
//STRIP001              //  default for DIF export (from API without options):
//STRIP001              //  ISO8859-1/MS_1252 encoding
//STRIP001
//STRIP001              sItStr = ScGlobal::GetCharsetString( RTL_TEXTENCODING_MS_1252 );
//STRIP001          }
//STRIP001
//STRIP001          WaitObject aWait( GetDialogParent() );
//STRIP001          ScExportDif( *pStream, &aDocument, ScAddress(0,0,0),
//STRIP001              ScGlobal::GetCharsetValue(sItStr) );
//STRIP001          bRet = TRUE;
//STRIP001
//STRIP001          if (aDocument.GetTableCount() > 1)
//STRIP001              if (!rMed.GetError())
//STRIP001                  rMed.SetError(SCWARN_EXPORT_ASCII);
//STRIP001      }
//STRIP001  }
//STRIP001  else if (aFltName.EqualsAscii(pFilterSylk))
//STRIP001  {
//STRIP001      SvStream* pStream = rMed.GetOutStream();
//STRIP001      if ( pStream )
//STRIP001      {
//STRIP001          WaitObject aWait( GetDialogParent() );
//STRIP001
//STRIP001          USHORT nEndCol, nEndRow;
//STRIP001          aDocument.GetCellArea( 0, nEndCol, nEndRow );
//STRIP001          ScRange aRange( 0,0,0, nEndCol,nEndRow,0 );
//STRIP001
//STRIP001          ScImportExport aImExport( &aDocument, aRange );
//STRIP001             aImExport.SetFormulas( TRUE );
//STRIP001          bRet = aImExport.ExportStream( *pStream, SOT_FORMATSTR_ID_SYLK );
//STRIP001      }
//STRIP001  }
//STRIP001  else if (aFltName.EqualsAscii(pFilterHtml))
//STRIP001  {
//STRIP001      SvStream* pStream = rMed.GetOutStream();
//STRIP001      if ( pStream )
//STRIP001      {
//STRIP001             WaitObject aWait( GetDialogParent() );
//STRIP001          ScImportExport aImExport( &aDocument );
//STRIP001          aImExport.SetStreamPath( rMed.GetName() );
//STRIP001          bRet = aImExport.ExportStream( *pStream, SOT_FORMATSTR_ID_HTML );
//STRIP001             if ( bRet && aImExport.GetNonConvertibleChars().Len() )
//STRIP001                 SetError( *new StringErrorInfo(
//STRIP001                     SCWARN_EXPORT_NONCONVERTIBLE_CHARS,
//STRIP001                     aImExport.GetNonConvertibleChars(),
//STRIP001                     ERRCODE_BUTTON_OK | ERRCODE_MSG_INFO ) );
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if (GetError())
//STRIP001          SetError(SCERR_IMPORT_NI);
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }


/*N*/ BOOL __EXPORT ScDocShell::SaveCompleted( SvStorage * pStor )
/*N*/ {
/*N*/   return SfxInPlaceObject::SaveCompleted( pStor );
/*N*/ }


/*N*/ BOOL __EXPORT ScDocShell::DoSaveCompleted( SfxMedium * pNewStor )
/*N*/ {
/*N*/   BOOL bRet = SfxObjectShell::DoSaveCompleted( pNewStor );
/*N*/
/*N*/   //  SC_HINT_DOC_SAVED fuer Wechsel ReadOnly -> Read/Write
/*N*/   Broadcast( SfxSimpleHint( SC_HINT_DOC_SAVED ) );
/*N*/   return bRet;
/*N*/ }


//STRIP001 USHORT __EXPORT ScDocShell::PrepareClose( BOOL bUI, BOOL bForBrowsing )
//STRIP001 {
//STRIP001  if(SC_MOD()->GetCurRefDlgId()>0)
//STRIP001  {
//STRIP001      SfxViewFrame* pFrame = SfxViewFrame::GetFirst( this, TYPE(SfxTopViewFrame) );
//STRIP001      if( pFrame )
//STRIP001      {
//STRIP001          SfxViewShell* p = pFrame->GetViewShell();
//STRIP001          ScTabViewShell* pViewSh = PTR_CAST(ScTabViewShell,p);
//STRIP001          if(pViewSh!=NULL)
//STRIP001          {
//STRIP001              Window *pWin=pViewSh->GetWindow();
//STRIP001              if(pWin!=NULL) pWin->GrabFocus();
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      return FALSE;
//STRIP001  }
//STRIP001  if ( aDocument.IsInLinkUpdate() || aDocument.IsInInterpreter() )
//STRIP001  {
//STRIP001      ErrorMessage(STR_CLOSE_ERROR_LINK);
//STRIP001      return FALSE;
//STRIP001  }
//STRIP001
//STRIP001  DoEnterHandler();
//STRIP001
//STRIP001  USHORT nRet = SfxObjectShell::PrepareClose( bUI, bForBrowsing );
//STRIP001  if (nRet == TRUE)                       // TRUE = schliessen
//STRIP001      aDocument.DisableIdle(TRUE);        // nicht mehr drin rumpfuschen !!!
//STRIP001
//STRIP001  return nRet;
//STRIP001 }

//STRIP001 void ScDocShell::PrepareReload()
//STRIP001 {
//STRIP001  SfxObjectShell::PrepareReload();    // tut nichts?
//STRIP001
//STRIP001  //  Das Disconnect von DDE-Links kann Reschedule ausloesen.
//STRIP001  //  Wenn die DDE-Links erst im Dokument-dtor geloescht werden, kann beim Reload
//STRIP001  //  aus diesem Reschedule das DDE-Link-Update fuer das neue Dokument ausgeloest
//STRIP001  //  werden. Dabei verklemmt sicht dann irgendwas.
//STRIP001  //  -> Beim Reload die DDE-Links des alten Dokuments vorher disconnecten
//STRIP001
//STRIP001  aDocument.DisconnectDdeLinks();
//STRIP001 }


/*N*/ String ScDocShell::GetOwnFilterName()         // static
/*N*/ {
/*N*/   return String::CreateFromAscii(pFilterSc50);
/*N*/ }

/*N*/ String ScDocShell::GetWebQueryFilterName()        // static
/*N*/ {
/*N*/   return String::CreateFromAscii(pFilterHtmlWebQ);
/*N*/ }

/*N*/ String ScDocShell::GetAsciiFilterName()           // static
/*N*/ {
/*N*/   return String::CreateFromAscii(pFilterAscii);
/*N*/ }

/*N*/ String ScDocShell::GetLotusFilterName()           // static
/*N*/ {
/*N*/   return String::CreateFromAscii(pFilterLotus);
/*N*/ }

/*N*/ String ScDocShell::GetDBaseFilterName()           // static
/*N*/ {
/*N*/   return String::CreateFromAscii(pFilterDBase);
/*N*/ }

/*N*/ String ScDocShell::GetDifFilterName()         // static
/*N*/ {
/*N*/   return String::CreateFromAscii(pFilterDif);
/*N*/ }

/*N*/ BOOL ScDocShell::HasAutomaticTableName( const String& rFilter )       // static
/*N*/ {
/*N*/   //  TRUE for those filters that keep the default table name
/*N*/   //  (which is language specific)
/*N*/
/*N*/   return rFilter.EqualsAscii( pFilterAscii )
/*N*/       || rFilter.EqualsAscii( pFilterLotus )
/*N*/       || rFilter.EqualsAscii( pFilterExcel4 )
/*N*/       || rFilter.EqualsAscii( pFilterEx4Temp )
/*N*/       || rFilter.EqualsAscii( pFilterDBase )
/*N*/       || rFilter.EqualsAscii( pFilterDif )
/*N*/       || rFilter.EqualsAscii( pFilterSylk )
/*N*/       || rFilter.EqualsAscii( pFilterHtml )
/*N*/       || rFilter.EqualsAscii( pFilterRtf );
/*N*/ }

//==================================================================

#define __SCDOCSHELL_INIT \
        aDocument       ( SCDOCMODE_DOCUMENT, this ), \
        pUndoManager    ( NULL ), \
        pFontList       ( NULL ), \
        bHeaderOn       ( TRUE ), \
        bFooterOn       ( TRUE ), \
        pDocHelper      ( NULL ), \
        pAutoStyleList  ( NULL ), \
        pOldJobSetup    ( NULL ), \
        pPaintLockData  ( NULL ), \
        nPrtToScreenFactor( 1.0 ), \
        bIsEmpty        ( TRUE ), \
        bIsInUndo       ( FALSE ), \
        bDocumentModifiedPending( FALSE ), \
        nDocumentLock   ( 0 ), \
        nCanUpdate (::com::sun::star::document::UpdateDocMode::ACCORDING_TO_CONFIG), \
        bUpdateEnabled  ( TRUE ), \
        pVirtualDevice_100th_mm ( NULL ), \
        pModificator    ( NULL )

//------------------------------------------------------------------

/*N*/ ScDocShell::ScDocShell( const ScDocShell& rShell )
/*N*/   :   SfxObjectShell( rShell.GetCreateMode() ),
/*N*/       aDdeTextFmt(String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("TEXT"))),
/*N*/       bNoInformLost( TRUE ),
/*N*/       __SCDOCSHELL_INIT
/*N*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); //STRIP001 RTL_LOGFILE_CONTEXT_AUTHOR ( aLog, "sc", "nn93723", "ScDocShell::ScDocShell" );
//STRIP001 /*?*/
//STRIP001 /*?*/    SetPool( &SC_MOD()->GetPool() );
//STRIP001 /*?*/
//STRIP001 /*?*/    SetShell(this);
//STRIP001 /*?*/    bIsInplace = rShell.bIsInplace;
//STRIP001 /*?*/
//STRIP001 /*?*/    pDocFunc = new ScDocFunc(*this);
//STRIP001 /*?*/
//STRIP001 /*?*/    //  SetBaseModel needs exception handling
//STRIP001 /*?*/    ScModelObj::CreateAndSet( this );
//STRIP001 /*?*/
//STRIP001 /*?*/    StartListening(*this);
//STRIP001 /*?*/    SfxStyleSheetPool* pStlPool = aDocument.GetStyleSheetPool();
//STRIP001 /*?*/    if (pStlPool)
//STRIP001 /*?*/        StartListening(*pStlPool);
//STRIP001 /*?*/
//STRIP001 /*?*/    GetPageOnFromPageStyleSet( NULL, 0, bHeaderOn, bFooterOn );
//STRIP001 /*?*/    SetHelpId( HID_SCSHELL_DOCSH );
//STRIP001 /*?*/
//STRIP001 /*?*/    //  InitItems und CalcOutputFactor werden jetzt nach bei Load/ConvertFrom/InitNew gerufen
/*N*/ }

//------------------------------------------------------------------

/*N*/ ScDocShell::ScDocShell( SfxObjectCreateMode eMode )
/*N*/   :   SfxObjectShell( eMode ),
/*N*/       aDdeTextFmt(String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("TEXT"))),
/*N*/       bNoInformLost( TRUE ),
/*N*/       __SCDOCSHELL_INIT
/*N*/ {
/*N*/   RTL_LOGFILE_CONTEXT_AUTHOR ( aLog, "sc", "nn93723", "ScDocShell::ScDocShell" );
/*N*/
/*N*/   SetPool( &SC_MOD()->GetPool() );
/*N*/
/*N*/   SetShell(this);
/*N*/   bIsInplace = (eMode == SFX_CREATE_MODE_EMBEDDED);
/*N*/   //  wird zurueckgesetzt, wenn nicht inplace
/*N*/
/*N*/   pDocFunc = new ScDocFunc(*this);
/*N*/
/*N*/   //  SetBaseModel needs exception handling
/*N*/   ScModelObj::CreateAndSet( this );
/*N*/
/*N*/   StartListening(*this);
/*N*/   SfxStyleSheetPool* pStlPool = aDocument.GetStyleSheetPool();
/*N*/   if (pStlPool)
/*N*/       StartListening(*pStlPool);
/*N*/   SetHelpId( HID_SCSHELL_DOCSH );
/*N*/
/*N*/   aDocument.GetDBCollection()->SetRefreshHandler(
/*N*/       LINK( this, ScDocShell, RefreshDBDataHdl ) );
/*N*/
/*N*/   //  InitItems und CalcOutputFactor werden jetzt nach bei Load/ConvertFrom/InitNew gerufen
/*N*/ }

//------------------------------------------------------------------

/*N*/ __EXPORT ScDocShell::~ScDocShell()
/*N*/ {
/*N*/   ResetDrawObjectShell(); // #55570# falls der Drawing-Layer noch versucht, darauf zuzugreifen
/*N*/
/*N*/   SfxStyleSheetPool* pStlPool = aDocument.GetStyleSheetPool();
/*N*/   if (pStlPool)
/*N*/       EndListening(*pStlPool);
/*N*/   EndListening(*this);
/*N*/
/*N*/   delete pAutoStyleList;
/*N*/
/*N*/   SfxApplication *pSfxApp = SFX_APP();
/*N*/   if ( pSfxApp->GetDdeService() )             // DDE vor Dokument loeschen
/*N*/       pSfxApp->RemoveDdeTopic( this );
/*N*/
/*N*/   delete pDocFunc;
/*N*/   delete pUndoManager;
/*N*/   delete pFontList;
/*N*/
/*N*/   delete pPaintLockData;
/*N*/
/*N*/   delete pOldJobSetup;        // gesetzt nur bei Fehler in StartJob()
/*N*/
/*N*/   delete pVirtualDevice_100th_mm;
/*N*/
/*N*/     if (pModificator)
/*N*/     {
/*N*/         DBG_ERROR("The Modificator should not exist");
/*N*/         delete pModificator;
/*N*/     }
/*N*/ }

//------------------------------------------------------------------

/*N*/ SfxUndoManager* __EXPORT ScDocShell::GetUndoManager()
/*N*/ {
/*N*/   if (!pUndoManager)
/*N*/       pUndoManager = new SfxUndoManager;
/*N*/   return pUndoManager;
/*N*/ }

/*N*/ void ScDocShell::SetModified( BOOL bModified )
/*N*/ {
/*N*/   SfxInPlaceObject::SetModified( bModified );
/*N*/   Broadcast( SfxSimpleHint( SFX_HINT_DOCCHANGED ) );
/*N*/ }


/*N*/ void ScDocShell::SetDocumentModified( BOOL bIsModified /* = TRUE */ )
/*N*/ {
/*N*/   //  BroadcastUno muss auch mit pPaintLockData sofort passieren
/*N*/   //! auch bei SetDrawModified, wenn Drawing angebunden ist
/*N*/   //! dann eigener Hint???
/*N*/
/*N*/   if (bIsModified)
/*N*/       aDocument.BroadcastUno( SfxSimpleHint( SFX_HINT_DATACHANGED ) );
/*N*/
/*N*/   if ( pPaintLockData && bIsModified )
/*N*/   {
/*N*/       pPaintLockData->SetModified();          // spaeter...
/*N*/       return;
/*N*/   }
/*N*/
/*N*/   SetDrawModified( bIsModified );
/*N*/
/*N*/   if ( bIsModified )
/*N*/   {
/*N*/       if ( aDocument.IsAutoCalcShellDisabled() )
/*?*/           SetDocumentModifiedPending( TRUE );
/*N*/       else
/*N*/       {
/*N*/           SetDocumentModifiedPending( FALSE );
/*N*/             aDocument.InvalidateStyleSheetUsage();
/*N*/           aDocument.InvalidateTableArea();
/*N*/             aDocument.InvalidateLastTableOpParams();
/*N*/           aDocument.Broadcast( SC_HINT_DATACHANGED, BCA_BRDCST_ALWAYS, NULL );
/*N*/           if ( aDocument.IsForcedFormulaPending() && aDocument.GetAutoCalc() )
/*?*/           {   DBG_BF_ASSERT(0, "STRIP");} //STRIP001 aDocument.CalcFormulaTree( TRUE );
/*N*/           PostDataChanged();
/*N*/
/*N*/           //  Detective AutoUpdate:
/*N*/           //  Update if formulas were modified (DetectiveDirty) or the list contains
/*N*/           //  "Trace Error" entries (#75362# - Trace Error can look completely different
/*N*/           //  after changes to non-formula cells).
/*N*/
/*N*/           ScDetOpList* pList = aDocument.GetDetOpList();
/*N*/           if ( pList && ( aDocument.IsDetectiveDirty() || pList->HasAddError() ) &&
/*N*/                pList->Count() && !IsInUndo() && SC_MOD()->GetAppOptions().GetDetectiveAuto() )
/*N*/           {
/*N*/               GetDocFunc().DetectiveRefresh(TRUE);    // TRUE = caused by automatic update
/*N*/           }
/*N*/           aDocument.SetDetectiveDirty(FALSE);         // always reset, also if not refreshed
/*N*/       }
/*N*/   }
/*N*/ }

//  SetDrawModified - ohne Formel-Update
//  (Drawing muss auch beim normalen SetDocumentModified upgedated werden,
//   z.B. bei Tabelle loeschen etc.)

/*N*/ void ScDocShell::SetDrawModified( BOOL bIsModified /* = TRUE */ )
/*N*/ {
/*N*/   BOOL bUpdate = ( bIsModified != IsModified() );
/*N*/
/*N*/   SetModified( bIsModified );
/*N*/
/*N*/   if (bUpdate)
/*N*/   {
/*N*/       SfxBindings* pBindings = GetViewBindings();
/*N*/       if (pBindings)
/*N*/       {
/*N*/           pBindings->Invalidate( SID_SAVEDOC );
/*N*/           pBindings->Invalidate( SID_DOC_MODIFIED );
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if (bIsModified)
/*N*/   {
/*N*/       if ( aDocument.IsChartListenerCollectionNeedsUpdate() )
/*N*/       {
/*N*/           aDocument.UpdateChartListenerCollection();
/*N*/           SFX_APP()->Broadcast(SfxSimpleHint( SC_HINT_DRAW_CHANGED ));    // Navigator
/*N*/       }
/*N*/       SC_MOD()->AnythingChanged();
/*N*/   }
/*N*/ }

//STRIP001 void ScDocShell::SetInUndo(BOOL bSet)
//STRIP001 {
//STRIP001  bIsInUndo = bSet;
//STRIP001 }


//STRIP001 void ScDocShell::GetDocStat( ScDocStat& rDocStat )
//STRIP001 {
//STRIP001  SfxPrinter* pPrinter = GetPrinter();
//STRIP001
//STRIP001  aDocument.GetDocStat( rDocStat );
//STRIP001  rDocStat.nPageCount = 0;
//STRIP001
//STRIP001  if ( pPrinter )
//STRIP001      for ( USHORT i=0; i<rDocStat.nTableCount; i++ )
//STRIP001          rDocStat.nPageCount +=
//STRIP001              (USHORT) ScPrintFunc( this, pPrinter, i ).GetTotalPages();
//STRIP001 }


//STRIP001 SfxDocumentInfoDialog* __EXPORT ScDocShell::CreateDocumentInfoDialog(
//STRIP001                                       Window *pParent, const SfxItemSet &rSet )
//STRIP001 {
//STRIP001  SfxDocumentInfoDialog* pDlg   = new SfxDocumentInfoDialog( pParent, rSet );
//STRIP001  ScDocShell*            pDocSh = PTR_CAST(ScDocShell,SfxObjectShell::Current());
//STRIP001
//STRIP001  //nur mit Statistik, wenn dieses Doc auch angezeigt wird, nicht
//STRIP001  //aus dem Doc-Manager
//STRIP001
//STRIP001  if( pDocSh == this )
//STRIP001      pDlg->AddTabPage( 42,
//STRIP001                        ScGlobal::GetRscString( STR_DOC_STAT ),
//STRIP001                        ScDocStatPage::Create,
//STRIP001                        NULL );
//STRIP001
//STRIP001  return pDlg;
//STRIP001 }

/*N*/ Window* ScDocShell::GetDialogParent()
/*N*/ {
/*N*/   ScTabViewShell* pViewSh = ScTabViewShell::GetActiveViewShell();
/*N*/   if ( pViewSh )
/*?*/       {DBG_BF_ASSERT(0, "STRIP"); return NULL; }//STRIP001 return pViewSh->GetDialogParent();
/*N*/   else
/*N*/       return Application::GetDefDialogParent();
/*N*/ }

/*N*/ VirtualDevice* ScDocShell::GetVirtualDevice_100th_mm()
/*N*/ {
/*N*/   if (!pVirtualDevice_100th_mm)
/*N*/   {
/*N*/       pVirtualDevice_100th_mm = new VirtualDevice;
/*N*/       pVirtualDevice_100th_mm->SetMapMode( MAP_100TH_MM );
/*N*/   }
/*N*/   return pVirtualDevice_100th_mm;
/*N*/ }

// --- ScDocShellModificator ------------------------------------------

/*N*/ ScDocShellModificator::ScDocShellModificator( ScDocShell& rDS )
/*N*/       :
/*N*/       rDocShell( rDS ),
/*N*/       aProtector( rDS.GetDocument()->GetRefreshTimerControlAddress() )
/*N*/ {
/*N*/   ScDocument* pDoc = rDocShell.GetDocument();
/*N*/   bAutoCalcShellDisabled = pDoc->IsAutoCalcShellDisabled();
/*N*/   bIdleDisabled = pDoc->IsIdleDisabled();
/*N*/   pDoc->SetAutoCalcShellDisabled( TRUE );
/*N*/   pDoc->DisableIdle( TRUE );
/*N*/ }


/*N*/ ScDocShellModificator::~ScDocShellModificator()
/*N*/ {
/*N*/   ScDocument* pDoc = rDocShell.GetDocument();
/*N*/   pDoc->SetAutoCalcShellDisabled( bAutoCalcShellDisabled );
/*N*/   if ( !bAutoCalcShellDisabled && rDocShell.IsDocumentModifiedPending() )
/*?*/       rDocShell.SetDocumentModified();    // last one shuts off the lights
/*N*/   pDoc->DisableIdle( bIdleDisabled );
/*N*/ }


/*N*/ void ScDocShellModificator::SetDocumentModified()
/*N*/ {
/*N*/   ScDocument* pDoc = rDocShell.GetDocument();
/*N*/   if ( !pDoc->IsImportingXML() )
/*N*/   {
/*N*/       // AutoCalcShellDisabled temporaer restaurieren
/*N*/       BOOL bDisabled = pDoc->IsAutoCalcShellDisabled();
/*N*/       pDoc->SetAutoCalcShellDisabled( bAutoCalcShellDisabled );
/*N*/       rDocShell.SetDocumentModified();
/*N*/       pDoc->SetAutoCalcShellDisabled( bDisabled );
/*N*/   }
/*N*/   else
/*N*/   {
/*?*/       // uno broadcast is necessary for api to work
/*?*/       // -> must also be done during xml import
/*?*/       pDoc->BroadcastUno( SfxSimpleHint( SFX_HINT_DATACHANGED ) );
/*N*/   }
/*N*/ }
}
