/*************************************************************************
 *
 *  $RCSfile: sd_sdmod.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:19:25 $
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

#ifndef INCLUDED_SVTOOLS_PATHOPTIONS_HXX
#include <svtools/pathoptions.hxx>
#endif
#ifndef _SVTOOLS_LANGUAGEOPTIONS_HXX
#include <svtools/languageoptions.hxx>
#endif
#ifndef _UNOTOOLS_UCBSTREAMHELPER_HXX
#include <unotools/ucbstreamhelper.hxx>
#endif
#ifndef _URLOBJ_HXX
#include <tools/urlobj.hxx>
#endif
#ifndef _SV_VIRDEV_HXX
#include <vcl/virdev.hxx>
#endif
#ifndef _SFXAPP_HXX //autogen
#include <bf_sfx2/app.hxx>
#endif
#ifndef _SV_STATUS_HXX //autogen
#include <vcl/status.hxx>
#endif
#ifndef _SFXINTITEM_HXX //autogen
#include <svtools/intitem.hxx>
#endif
#ifndef _SFXMSG_HXX //autogen
#include <bf_sfx2/msg.hxx>
#endif
#ifndef _SFXOBJFACE_HXX //autogen
#include <bf_sfx2/objface.hxx>
#endif
#ifndef _SFX_PRINTER_HXX
#include <bf_sfx2/printer.hxx>
#endif
#ifndef _SVX_PSZCTRL_HXX //autogen
#include <bf_svx/pszctrl.hxx>
#endif
#ifndef _SVX_ZOOMCTRL_HXX //autogen
#include <bf_svx/zoomctrl.hxx>
#endif
#ifndef _SVX_MODCTRL_HXX //autogen
#include <bf_svx/modctrl.hxx>
#endif
#ifndef _ZFORLIST_HXX
#include <svtools/zforlist.hxx>
#endif
#ifndef _COMPHELPER_PROCESSFACTORY_HXX_
#include <comphelper/processfactory.hxx>
#endif

#ifndef _EHDL_HXX
#include <svtools/ehdl.hxx>
#endif

#define ITEMID_SEARCH           SID_SEARCH_ITEM
#include <bf_svx/svxids.hrc>
#include <bf_offmgr/ofaids.hrc>
#include <bf_svx/srchitem.hxx>

#pragma hdrstop

#define _SD_DLL                 // fuer SD_MOD()
#include "sderror.hxx"
#include "sdmod.hxx"
#include "sddll.hxx"
#include "sdresid.hxx"
#include "optsitem.hxx"
#include "docshell.hxx"
#include "drawdoc.hxx"
#include "app.hrc"
#include "glob.hrc"
#include "strings.hrc"
#include "res_bmp.hrc"
#include "cfgids.hxx"

#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif

/*N*/ TYPEINIT1( SdModuleDummy, SfxModule );
/*N*/ TYPEINIT1( SdModule, SdModuleDummy );

/*N*/ #define SdModule
/*N*/ #include "sdslots.hxx"


/*N*/ SFX_IMPL_INTERFACE(SdModule, SfxModule, SdResId(STR_APPLICATIONOBJECTBAR))
/*N*/ {
/*N*/   SFX_STATUSBAR_REGISTRATION(RID_DRAW_STATUSBAR);
/*N*/ }

/*N*/ SFX_IMPL_MODULE_DLL(Sd)

/*************************************************************************
|*
|* Ctor
|*
\************************************************************************/

/*N*/ SdModule::SdModule(SvFactory* pDrawObjFact, SvFactory* pGraphicObjFact)
/*N*/ :   SdModuleDummy(SFX_APP()->CreateResManager("bf_sd"), FALSE,        //STRIP005
/*N*/                 pDrawObjFact, pGraphicObjFact),
/*N*/   bWaterCan(FALSE),
/*N*/   pTransferClip(NULL),
/*N*/   pTransferDrag(NULL),
/*N*/     pTransferSelection(NULL),
/*N*/   pImpressOptions(NULL),
/*N*/   pDrawOptions(NULL),
/*N*/   pSearchItem(NULL),
/*N*/   pNumberFormatter( NULL )
/*N*/ {
/*N*/   SetName( UniString::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM( "StarDraw" ) ) );  // Nicht uebersetzen!
/*N*/   pSearchItem = new SvxSearchItem(ITEMID_SEARCH);
/*N*/   pSearchItem->SetAppFlag(SVX_SEARCHAPP_DRAW);
/*N*/   StartListening( *SFX_APP() );
/*N*/
/*N*/   mpErrorHdl = new SfxErrorHandler( RID_SD_ERRHDL,
/*N*/                                        ERRCODE_AREA_SD,
/*N*/                                        ERRCODE_AREA_SD_END,
/*N*/                                        GetResMgr() );
/*N*/
/*N*/     mpVirtualRefDevice = new VirtualDevice;
/*N*/     mpVirtualRefDevice->SetMapMode( MAP_100TH_MM );
/*N*/ }



/*************************************************************************
|*
|* Dtor
|*
\************************************************************************/

/*N*/ SdModule::~SdModule()
/*N*/ {
/*N*/   delete pSearchItem;

/*N*/   if( pNumberFormatter )
/*N*/       delete pNumberFormatter;

/*N*/   delete mpErrorHdl;
/*N*/     delete static_cast< VirtualDevice* >( mpVirtualRefDevice );
/*N*/ }


/*************************************************************************
|*
|* Statusbar erzeugen
|*
\************************************************************************/

#define AUTOSIZE_WIDTH  180
#define TEXT_WIDTH(s)   rStatusBar.GetTextWidth((s))

//STRIP001 void SdModule::FillStatusBar(StatusBar& rStatusBar)
//STRIP001 {
//STRIP001  // Hinweis
//STRIP001  rStatusBar.InsertItem( SID_CONTEXT, TEXT_WIDTH( String().Fill( 30, 'x' ) ), // vorher 52
//STRIP001                          SIB_IN | SIB_LEFT | SIB_AUTOSIZE );
//STRIP001
//STRIP001  // Groesse und Position
//STRIP001  rStatusBar.InsertItem( SID_ATTR_SIZE, SvxPosSizeStatusBarControl::GetDefItemWidth(rStatusBar), // vorher 42
//STRIP001                          SIB_IN | SIB_USERDRAW );
//STRIP001                          // SIB_AUTOSIZE | SIB_LEFT | SIB_OWNERDRAW );
//STRIP001
//STRIP001  // Massstab
//STRIP001  rStatusBar.InsertItem( SID_ATTR_ZOOM, SvxZoomStatusBarControl::GetDefItemWidth(rStatusBar), SIB_IN | SIB_CENTER );
//STRIP001 /*
//STRIP001  // Einfuege- / Uberschreibmodus
//STRIP001  rStatusBar.InsertItem( SID_ATTR_INSERT, TEXT_WIDTH( "EINFG" ),
//STRIP001                          SIB_IN | SIB_CENTER );
//STRIP001
//STRIP001  // Selektionsmodus
//STRIP001  rStatusBar.InsertItem( SID_STATUS_SELMODE, TEXT_WIDTH( "ERG" ),
//STRIP001                          SIB_IN | SIB_CENTER );
//STRIP001 */
//STRIP001  // Dokument geaendert
//STRIP001  rStatusBar.InsertItem( SID_DOC_MODIFIED, SvxModifyControl::GetDefItemWidth(rStatusBar) );
//STRIP001
//STRIP001
//STRIP001  // Seite
//STRIP001  rStatusBar.InsertItem( SID_STATUS_PAGE, TEXT_WIDTH( String().Fill( 24, 'X' ) ),
//STRIP001                          SIB_IN | SIB_LEFT );
//STRIP001
//STRIP001  // Praesentationslayout
//STRIP001  rStatusBar.InsertItem( SID_STATUS_LAYOUT, TEXT_WIDTH( String().Fill( 10, 'X' ) ),
//STRIP001                          SIB_IN | SIB_LEFT | SIB_AUTOSIZE );
//STRIP001 }



/*************************************************************************
|*
|* Modul laden (nur Attrappe fuer das Linken der DLL)
|*
\************************************************************************/

SfxModule* SdModuleDummy::Load()
{
    return (NULL);
}

/*************************************************************************
|*
|* Modul laden
|*
\************************************************************************/

SfxModule* SdModule::Load()
{
    return (this);
}

/*************************************************************************
|*
|* get notifications
|*
\************************************************************************/

/*N*/ void SdModule::Notify( SfxBroadcaster& rBC, const SfxHint& rHint )
/*N*/ {
/*N*/   if( rHint.ISA( SfxSimpleHint ) &&
/*N*/       ( (SfxSimpleHint&) rHint ).GetId() == SFX_HINT_DEINITIALIZING )
/*N*/   {
/*N*/       delete pImpressOptions, pImpressOptions = NULL;
/*N*/       delete pDrawOptions, pDrawOptions = NULL;
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* Modul freigeben
|*
\************************************************************************/

void SdModule::Free()
{
}

/*************************************************************************
|*
|* Optionen zurueckgeben
|*
\************************************************************************/

/*N*/ SdOptions* SdModule::GetSdOptions(DocumentType eDocType)
/*N*/ {
/*N*/   SdOptions* pOptions = NULL;
/*N*/
/*N*/   if (eDocType == DOCUMENT_TYPE_DRAW)
/*N*/   {
/*N*/       if (!pDrawOptions)
/*N*/           pDrawOptions = new SdOptions( SDCFG_DRAW );
/*N*/
/*N*/       pOptions = pDrawOptions;
/*N*/   }
/*N*/   else if (eDocType == DOCUMENT_TYPE_IMPRESS)
/*N*/   {
/*N*/       if (!pImpressOptions)
/*N*/           pImpressOptions = new SdOptions( SDCFG_IMPRESS );
/*N*/
/*N*/       pOptions = pImpressOptions;
/*N*/   }
/*N*/   if( pOptions )
/*N*/   {
/*N*/       UINT16 nMetric = pOptions->GetMetric();
/*N*/
/*N*/       SdDrawDocShell* pDocSh = PTR_CAST( SdDrawDocShell, SfxObjectShell::Current() );
/*N*/       SdDrawDocument* pDoc = NULL;
/*N*/       if (pDocSh)
/*?*/           pDoc = pDocSh->GetDoc();
/*N*/
/*N*/       if( nMetric != 0xffff && pDoc && eDocType == pDoc->GetDocumentType() )
/*?*/           PutItem( SfxUInt16Item( SID_ATTR_METRIC, nMetric ) );
/*N*/   }
/*N*/
/*N*/   return(pOptions);
/*N*/ }

/*************************************************************************
|*
|* Optionen-Stream fuer interne Options oeffnen und zurueckgeben;
|* falls der Stream zum Lesen geoeffnet wird, aber noch nicht
|* angelegt wurde, wird ein 'leeres' RefObject zurueckgegeben
|*
\************************************************************************/

//STRIP001 SvStorageStreamRef SdModule::GetOptionStream( const String& rOptionName,
//STRIP001                                            SdOptionStreamMode eMode )
//STRIP001 {
//STRIP001  SdDrawDocShell*     pDocSh = PTR_CAST( SdDrawDocShell, SfxObjectShell::Current() );
//STRIP001  SvStorageStreamRef  xStm;
//STRIP001
//STRIP001  if( pDocSh )
//STRIP001  {
//STRIP001      DocumentType    eType = pDocSh->GetDoc()->GetDocumentType();
//STRIP001      String          aStmName;
//STRIP001
//STRIP001      if( !xOptionStorage.Is() )
//STRIP001      {
//STRIP001          INetURLObject aURL( SvtPathOptions().GetUserConfigPath() );
//STRIP001
//STRIP001          aURL.Append( UniString::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM( "drawing.cfg" ) ) );
//STRIP001
//STRIP001          SvStream* pStm = ::utl::UcbStreamHelper::CreateStream( aURL.GetMainURL( INetURLObject::NO_DECODE ), STREAM_READWRITE );
//STRIP001
//STRIP001          if( pStm )
//STRIP001              xOptionStorage = new SvStorage( pStm, TRUE );
//STRIP001      }
//STRIP001
//STRIP001      if( DOCUMENT_TYPE_DRAW == eType )
//STRIP001          aStmName.AssignAscii( RTL_CONSTASCII_STRINGPARAM( "Draw_" ) );
//STRIP001      else
//STRIP001          aStmName.AssignAscii( RTL_CONSTASCII_STRINGPARAM( "Impress_" ) );
//STRIP001
//STRIP001      aStmName += rOptionName;
//STRIP001
//STRIP001      if( SD_OPTION_STORE == eMode || xOptionStorage->IsContained( aStmName ) )
//STRIP001          xStm = xOptionStorage->OpenStream( aStmName );
//STRIP001  }
//STRIP001
//STRIP001  return xStm;
//STRIP001 }

/*************************************************************************
|*
\************************************************************************/

/*N*/ SvNumberFormatter* SdModule::GetNumberFormatter()
/*N*/ {
/*N*/   if( !pNumberFormatter )
/*N*/       pNumberFormatter = new SvNumberFormatter( ::legacy_binfilters::getLegacyProcessServiceFactory(), LANGUAGE_SYSTEM );
/*N*/
/*N*/   return pNumberFormatter;
/*N*/ }

/*************************************************************************
|*
\************************************************************************/

/*N*/ OutputDevice* SdModule::GetVirtualRefDevice (void)
/*N*/ {
/*N*/     return mpVirtualRefDevice;
/*N*/ }

/** This method is deprecated and only an alias to
    <member>GetVirtualRefDevice()</member>.  The given argument is ignored.
*/
/*N*/ OutputDevice* SdModule::GetRefDevice (SdDrawDocShell& rDocShell)
/*N*/ {
/*N*/     return GetVirtualRefDevice();
/*N*/ }


/*************************************************************************
|*
\************************************************************************/

//STRIP001 ::com::sun::star::text::WritingMode SdModule::GetDefaultWritingMode() const
//STRIP001 {
//STRIP001 /*
//STRIP001  const SvtLanguageOptions aLanguageOptions;
//STRIP001
//STRIP001     return( aLanguageOptions.IsCTLFontEnabled() ?
//STRIP001             ::com::sun::star::text::WritingMode_RL_TB :
//STRIP001             ::com::sun::star::text::WritingMode_LR_TB );
//STRIP001 */
//STRIP001  return ::com::sun::star::text::WritingMode_LR_TB;
//STRIP001 }