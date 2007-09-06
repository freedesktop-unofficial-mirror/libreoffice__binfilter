/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sd_sdmod.cxx,v $
 *
 *  $Revision: 1.9 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 11:22:10 $
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

#ifndef _SV_VIRDEV_HXX
#include <vcl/virdev.hxx>
#endif
#ifndef _ZFORLIST_HXX
#include <svtools/zforlist.hxx>
#endif

#ifndef _EHDL_HXX
#include <svtools/ehdl.hxx>
#endif

#define ITEMID_SEARCH           SID_SEARCH_ITEM
#include <bf_svx/svxids.hrc>
#include <bf_offmgr/ofaids.hrc>

#ifdef _MSC_VER
#pragma hdrstop
#endif

#define _SD_DLL                 // fuer SD_MOD()
#include "sdresid.hxx"
#include "optsitem.hxx"
#include "docshell.hxx"
#include "drawdoc.hxx"
#include "app.hrc"
#include "glob.hrc"
#include "strings.hrc"
#include "res_bmp.hrc"

#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif

namespace binfilter {

/*N*/ TYPEINIT1( SdModuleDummy, SfxModule );
/*N*/ TYPEINIT1( SdModule, SdModuleDummy );

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
/*N*/   pNumberFormatter( NULL )
/*N*/ {
/*N*/   SetName( UniString::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM( "StarDraw" ) ) );  // Nicht uebersetzen!
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

} //namespace binfilter
