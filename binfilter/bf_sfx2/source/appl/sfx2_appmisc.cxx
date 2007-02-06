/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sfx2_appmisc.cxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: vg $ $Date: 2007-02-06 12:45:07 $
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

#ifndef _SV_STATUS_HXX
#include <vcl/status.hxx>
#endif
#ifndef _SV_MSGBOX_HXX
#include <vcl/msgbox.hxx>
#endif
#ifndef _VOS_PROCESS_HXX //autogen
#include <vos/process.hxx>
#endif
#ifndef _XCEPTION_HXX_
#include <vos/xception.hxx>
#endif
#ifndef _SFX_WHITER_HXX //autogen
#include <svtools/whiter.hxx>
#endif
#ifndef _SFXSTRITEM_HXX //autogen
#include <svtools/stritem.hxx>
#endif
#ifndef _SFXINTITEM_HXX //autogen
#include <svtools/intitem.hxx>
#endif
#ifndef _SFXENUMITEM_HXX //autogen
#include <svtools/eitem.hxx>
#endif
#ifndef _FILTER_HXX //autogen
#include <svtools/filter.hxx>
#endif
#ifndef INCLUDED_SVTOOLS_INTERNALOPTIONS_HXX
#include <svtools/internaloptions.hxx>
#endif
#ifndef INCLUDED_SVTOOLS_PATHOPTIONS_HXX
#include <svtools/pathoptions.hxx>
#endif

#ifndef _COM_SUN_STAR_REGISTRY_INVALIDREGISTRYEXCEPTION_HPP_
#include <com/sun/star/registry/InvalidRegistryException.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_PropertyValue_HPP_
#include <com/sun/star/beans/PropertyValue.hpp>
#endif
#ifndef _COM_SUN_STAR_FRAME_XFRAME_HPP_
#include <com/sun/star/frame/XFrame.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_XURLTRANSFORMER_HPP_
#include <com/sun/star/util/XURLTransformer.hpp>
#endif
#ifndef _COM_SUN_STAR_FRAME_XFRAMESSUPPLIER_HPP_
#include <com/sun/star/frame/XFramesSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_UNO_REFERENCE_H_
#include <com/sun/star/uno/Reference.h>
#endif
#ifndef _CONFIG_HXX
#include <tools/config.hxx>
#endif
#include <tools/rcid.h>
#include <vos/mutex.hxx>
#pragma hdrstop
#ifndef _UTL_CONFIGMGR_HXX_
#include <unotools/configmgr.hxx>
#endif
#ifndef _COM_SUN_STAR_FRAME_XDESKTOP_HPP_
#include <com/sun/star/frame/XDesktop.hpp>
#endif

#include <unotools/ucbstreamhelper.hxx>
#include <framework/menuconfiguration.hxx>
#include <comphelper/processfactory.hxx>
#include <unotools/localfilehelper.hxx>
#include <unotools/bootstrap.hxx>
#include <svtools/moduleoptions.hxx>
#include <osl/file.hxx>

#include "sfxresid.hxx"
#include "app.hxx"
#include "appdata.hxx"
#include "arrdecl.hxx"
#include "cfgmgr.hxx"
#include "cfgitem.hxx"
#include "tbxctrl.hxx"

#ifndef _SVTOOLS_IMGDEF_HXX
#include <svtools/imgdef.hxx>
#endif

#include "tbxconf.hxx"
#include "stbitem.hxx"
#include "accitem.hxx"
#include "mnuitem.hxx"
#include "docfac.hxx"
#include "docfile.hxx"
#include "docfilt.hxx"
#include "request.hxx"
#include "bindings.hxx"
#include "dispatch.hxx"
#include "workwin.hxx"
//#include "iodlg.hxx"
#include "fcontnr.hxx"
#include "sfxlocal.hrc"
#include "sfx.hrc"
#include "app.hrc"
#include "templdlg.hxx"
#include "module.hxx"
#include "msgpool.hxx"
#include "topfrm.hxx"
#include "openflag.hxx"
#include "viewsh.hxx"
#include "appimp.hxx"
//#include "bmkmenu.hxx"
#include "objface.hxx"
#include "helper.hxx"   // SfxContentHelper::Kill()

#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif

using namespace ::vos;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::util;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::container;

//===================================================================
namespace binfilter {

/*N*/ SV_IMPL_PTRARR( SfxTbxCtrlFactArr_Impl, SfxTbxCtrlFactory* );
/*N*/ SV_IMPL_PTRARR( SfxStbCtrlFactArr_Impl, SfxStbCtrlFactory* );
/*N*/ SV_IMPL_PTRARR( SfxMenuCtrlFactArr_Impl, SfxMenuCtrlFactory* );
/*N*/ SV_IMPL_PTRARR( SfxChildWinFactArr_Impl, SfxChildWinFactory* );

//===================================================================

#define SfxApplication
#include "sfxslots.hxx"

class SfxSpecialConfigError_Impl
{
    String aError;

public:

};




//====================================================================


/*N*/ SFX_IMPL_INTERFACE(SfxApplication,SfxShell,SfxResId(0))
/*N*/ {
/*N*/     SFX_CHILDWINDOW_REGISTRATION( SID_CUSTOMIZETOOLBOX );
/*N*/
/*N*/     // Menu ist auf dem Macintosh sowieso sichtbar
/*N*/     SFX_OBJECTBAR_REGISTRATION(
/*N*/             SFX_OBJECTBAR_FULLSCREEN | SFX_VISIBILITY_FULLSCREEN,
/*N*/             SfxResId(RID_FULLSCREENTOOLBOX) );
/*N*/     SFX_OBJECTBAR_REGISTRATION( SFX_OBJECTBAR_APPLICATION |
/*N*/             SFX_VISIBILITY_DESKTOP | SFX_VISIBILITY_STANDARD | SFX_VISIBILITY_CLIENT,
/*N*/             SfxResId(RID_ENVTOOLBOX) );
/*N*/
/*N*/     SFX_STATUSBAR_REGISTRATION(SfxResId(SFX_ITEMTYPE_STATBAR));
/*N*/ }

//--------------------------------------------------------------------

/*?*/ SfxViewFrame* SfxApplication::CreateViewFrame(
/*?*/     SfxObjectShell& rDoc, sal_uInt16 nViewId, sal_Bool bHidden )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return NULL;//STRIP001
/*?*/ }


//--------------------------------------------------------------------


//--------------------------------------------------------------------

/*N*/ void SfxApplication::FillStatusBar( StatusBar& rBar )
/*N*/
/*  [Beschreibung]

    Diese virtuelle Factory-Methode wird vom SFx gerufen, um die
    StatusBar f"ur das Applikationsfenster zu erzeugen. Im Ggs. zu
    den anderen Standard-Controllern Menu, Accelerator und ToolBoxen
    kann die Status-Zeile nur mit dieser Factory erzeugt werden,
    da in der SV-Resource keine StatusBar-Items angegeben werden k"oennen.
*/

/*N*/ {
/*N*/   rBar.InsertItem( SID_EXPLORER_SELECTIONSIZE, 200, SIB_IN|SIB_LEFT|SIB_AUTOSIZE );
/*N*/ }

//--------------------------------------------------------------------


//--------------------------------------------------------------------

//--------------------------------------------------------------------


//--------------------------------------------------------------------


//--------------------------------------------------------------------
#ifdef WNT
extern String GetUserID();
#endif

//------------------------------------------------------------------------

/*N*/ SfxProgress* SfxApplication::GetProgress() const

/*  [Beschreibung]

    Liefert den f"ur die gesamte Applikation laufenden SfxProgress
    oder 0, falls keiner f"ur die gesamte Applikation l"auft.


    [Querverweise]

    <SfxProgress::GetActiveProgress(SfxViewFrame*)>
    <SfxViewFrame::GetProgress()const>
*/

/*N*/ {
/*N*/     return pAppData_Impl->pProgress;
/*N*/ }

//------------------------------------------------------------------------


//------------------------------------------------------------------------



//------------------------------------------------------------------------

/*N*/ SvUShorts* SfxApplication::GetDisabledSlotList_Impl()
/*N*/ {
/*N*/   sal_Bool bError = sal_False;
/*N*/   SvUShorts* pList = pAppData_Impl->pDisabledSlotList;
/*N*/   if ( !pList )
/*N*/   {
/*N*/       // Gibt es eine Slotdatei ?
/*N*/         INetURLObject aUserObj( SvtPathOptions().GetUserConfigPath() );
/*N*/         aUserObj.insertName( DEFINE_CONST_UNICODE( "slots.cfg" ) );
/*N*/         SvStream* pStream = ::utl::UcbStreamHelper::CreateStream( aUserObj.GetMainURL( INetURLObject::NO_DECODE ), STREAM_STD_READ );
/*N*/         if ( !pStream || pStream->GetError() == ERRCODE_IO_NOTEXISTS )
/*N*/         {
/*N*/             delete pStream;
/*N*/             INetURLObject aObj( SvtPathOptions().GetConfigPath() );
/*N*/             aObj.insertName( DEFINE_CONST_UNICODE( "slots.cfg" ) );
/*N*/             pStream = ::utl::UcbStreamHelper::CreateStream( aObj.GetMainURL( INetURLObject::NO_DECODE ), STREAM_STD_READ );
/*N*/         }
/*N*/
/*N*/         BOOL bSlotsEnabled = SvtInternalOptions().SlotCFGEnabled();
/*N*/         BOOL bSlots = ( pStream && !pStream->GetError() );
/*N*/         if( bSlots && bSlotsEnabled )
/*N*/       {
/*N*/             // SlotDatei einlesen
/*?*/             String aTitle;
/*?*/             pStream->ReadByteString(aTitle);
/*?*/             if ( aTitle.CompareToAscii("SfxSlotFile" ) == COMPARE_EQUAL )
/*?*/             {
/*?*/                 sal_uInt16 nCount;
/*?*/                 (*pStream) >> nCount;
/*?*/                 pList = pAppData_Impl->pDisabledSlotList =
/*?*/                         new SvUShorts( nCount < 255 ? (sal_Int8) nCount : 255, 255 );
/*?*/
/*?*/                 sal_uInt16 nSlot;
/*?*/                 for ( sal_uInt16 n=0; n<nCount; n++ )
/*?*/                 {
/*?*/                     (*pStream) >> nSlot;
/*?*/                     pList->Insert( nSlot, n );
/*?*/                 }
/*?*/
/*?*/                 pStream->ReadByteString(aTitle);
/*?*/                 if ( aTitle.CompareToAscii("END" ) != COMPARE_EQUAL || pStream->GetError() )
/*?*/                 {
/*?*/                     // Lesen schief gegangen
/*?*/                     DELETEZ( pList );
/*?*/                     bError = sal_True;
/*?*/                 }
/*?*/             }
/*?*/             else
/*?*/             {
/*?*/                 // Streamerkennung  fehlgeschlagen
/*?*/                 bError = sal_True;
/*N*/             }
/*N*/       }
/*N*/         else if ( bSlots != bSlotsEnabled )
/*N*/       {
/*N*/           // Wenn kein Slotlist-Eintrag, dann darf auch keine SlotDatei
/*N*/           // vorhanden sein
/*N*/             bError = sal_True;
/*N*/       }
/*N*/
/*N*/         delete pStream;
/*N*/   }
/*N*/   else if ( pList == (SvUShorts*) -1L )
/*N*/   {
/*N*/       return NULL;
/*N*/   }
/*N*/
/*N*/   if ( !pList )
/*N*/       pAppData_Impl->pDisabledSlotList = (SvUShorts*) -1L;
/*N*/
/*N*/   if ( bError )
/*N*/   {
/*N*/       // Wenn ein Sloteintrag vorhanden ist, aber keine oder eine fehlerhafte
/*N*/       // SlotDatei, oder aber eine Slotdatei, aber kein Sloteintrag, dann
/*N*/       // gilt dies als fehlerhafte Konfiguration
/*?*/         DBG_BF_ASSERT(0, "STRIP"); //STRIP001 new SfxSpecialConfigError_Impl( String( SfxResId( RID_SPECIALCONFIG_ERROR ) ) );
/*N*/   }
/*N*/
/*N*/       return pList;
/*N*/ }




/*N*/ SfxModule* SfxApplication::GetActiveModule( SfxViewFrame *pFrame ) const
/*N*/ {
/*N*/   if ( !pFrame )
/*N*/       pFrame = SfxViewFrame::Current();
/*N*/   SfxObjectShell* pSh = 0;
/*N*/   if( pFrame ) pSh = pFrame->GetObjectShell();
/*N*/   return pSh ? pSh->GetModule() : 0;
/*N*/ }



/*N*/ SfxSlotPool& SfxApplication::GetSlotPool( SfxViewFrame *pFrame ) const
/*N*/ {
/*N*/   SfxModule *pMod = GetActiveModule( pFrame );
/*N*/   if ( pMod && pMod->GetSlotPool() )
/*N*/       return *pMod->GetSlotPool();
/*N*/   else
/*N*/       return *pSlotPool;
/*N*/ }



/*N*/ SfxAcceleratorManager* SfxApplication::GetGlobalAcceleratorManager() const
/*N*/ {
/*N*/     return pAcceleratorMgr;
/*N*/ }



/*N*/ ISfxTemplateCommon* SfxApplication::GetCurrentTemplateCommon( SfxBindings& rBindings )
/*N*/ {
/*N*/   if( pAppData_Impl->pTemplateCommon )
/*?*/       return pAppData_Impl->pTemplateCommon;
/*N*/   SfxChildWindow *pChild = rBindings.GetWorkWindow_Impl()->GetChildWindow_Impl(
/*N*/       SfxTemplateDialogWrapper::GetChildWindowId() );
/*N*/   if ( pChild )
/*N*/       return ((SfxTemplateDialog*) pChild->GetWindow())->GetISfxTemplateCommon();
/*N*/   return 0;
/*N*/ }



/*N*/ SfxCancelManager *SfxApplication::GetCancelManager() const
/*N*/ {
/*N*/   if ( !pAppData_Impl->pCancelMgr )
/*N*/   {
/*N*/       pAppData_Impl->pCancelMgr = new SfxCancelManager;
/*N*/       pAppData_Impl->StartListening( *pAppData_Impl->pCancelMgr );
/*N*/   }
/*N*/   return pAppData_Impl->pCancelMgr;
/*N*/ }


}
