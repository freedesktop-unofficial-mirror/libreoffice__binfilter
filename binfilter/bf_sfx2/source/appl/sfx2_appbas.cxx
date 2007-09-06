/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sfx2_appbas.cxx,v $
 *
 *  $Revision: 1.13 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 11:23:36 $
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

#ifndef _COM_SUN_STAR_FRAME_XDESKTOP_HPP_
#include <com/sun/star/frame/XDesktop.hpp>
#endif
#ifndef _COM_SUN_STAR_UNO_REFERENCE_H_
#include <com/sun/star/uno/Reference.h>
#endif

#ifndef _URLOBJ_HXX
#include <tools/urlobj.hxx>
#endif
#ifndef _SFXRECTITEM_HXX //autogen
#include <svtools/rectitem.hxx>
#endif
#ifndef _SFXINTITEM_HXX //autogen
#include <svtools/intitem.hxx>
#endif
#ifndef _SFXENUMITEM_HXX //autogen
#include <svtools/eitem.hxx>
#endif

#include <svtools/stritem.hxx>


#include <svtools/pathoptions.hxx>

#ifdef _MSC_VER
#pragma hdrstop
#endif

#include "docinf.hxx"
#include "appuno.hxx"
#include "objsh.hxx"
#include "app.hxx"
#include "appdata.hxx"
#include "appimp.hxx"
#include "dlgcont.hxx"

#ifndef _BASMGR_HXX
#include "bf_basic/basmgr.hxx"
#endif

#include "scriptcont.hxx"

#define ITEMID_SEARCH SID_SEARCH_ITEM


#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif
#include "so3/staticbaseurl.hxx"

namespace binfilter {

using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::frame;
using namespace ::com::sun::star::script;

//--------------------------------------------------------------------

namespace
{
    static BasicManager*& lcl_getAppBasicManager()
    {
        static BasicManager* s_pAppBasicManager = NULL;
        return s_pAppBasicManager;
    }
}

//========================================================================

StarBASIC* SfxApplication::GetBasic_Impl() const
{
    BasicManager* pBasMgr = lcl_getAppBasicManager();
    return pBasMgr ? pBasMgr->GetLib(0) : NULL;
}

//=========================================================================
/*N*/ sal_uInt16 SfxApplication::SaveBasicManager() const
/*N*/ {
/*N*/   return 0;
/*N*/ }

//--------------------------------------------------------------------
/*N*/ sal_uInt16 SfxApplication::SaveDialogContainer() const
/*N*/ {
/*N*/   // Save Dialog Container
/*N*/   sal_Bool bComplete = sal_False;
/*N*/   if( pImp->pDialogLibContainer )
/*N*/       pImp->pDialogLibContainer->storeLibraries( bComplete );
/*N*/   return 0;
/*N*/ }

//--------------------------------------------------------------------
/*N*/ sal_uInt16 SfxApplication::SaveBasicContainer() const
/*N*/ {
/*N*/   // Save Dialog Container
/*N*/   sal_Bool bComplete = sal_False;
/*N*/   if( pImp->pBasicLibContainer )
/*N*/       pImp->pBasicLibContainer->storeLibraries( bComplete );
/*N*/   return 0;
/*N*/ }

//--------------------------------------------------------------------


//--------------------------------------------------------------------

BasicManager* SfxApplication::GetBasicManager()
{
    if ( pAppData_Impl->nBasicCallLevel == 0 )
        // sicherheitshalber
        EnterBasicCall();

    BasicManager*& pBasMgr = lcl_getAppBasicManager();
    if ( !pBasMgr )
    {
        // Directory bestimmen
        SvtPathOptions aPathCFG;
        String aAppBasicDir( aPathCFG.GetBasicPath() );
        if ( !aAppBasicDir.Len() )
            aPathCFG.SetBasicPath( String::CreateFromAscii("$(prog)") );

        // #58293# soffice.new nur im ::com::sun::star::sdbcx::User-Dir suchen => erstes Verzeichnis
        String aAppFirstBasicDir = aAppBasicDir.GetToken(1);

        // Basic erzeugen und laden
        // MT: #47347# AppBasicDir ist jetzt ein PATH!
        INetURLObject aAppBasic( SvtPathOptions().SubstituteVariable( String::CreateFromAscii("$(progurl)") ) );
        aAppBasic.insertName( Application::GetAppName() );

        pBasMgr = new BasicManager( new StarBASIC, &aAppBasicDir );

        // Als Destination das erste Dir im Pfad:
        String aFileName( aAppBasic.getName() );
        aAppBasic = INetURLObject( aAppBasicDir.GetToken(1) );
        DBG_ASSERT( aAppBasic.GetProtocol() != INET_PROT_NOT_VALID, "Invalid URL!" );
        aAppBasic.insertName( aFileName );
        pBasMgr->SetStorageName( aAppBasic.PathToFileName() );

        // globale Variablen
        StarBASIC *pBas = pBasMgr->GetLib(0);
        sal_Bool bBasicWasModified = pBas->IsModified();

/*
        Reference< ::com::sun::star::lang::XMultiServiceFactory > xSMgr = ::comphelper::getProcessServiceFactory();
        Any aDesktop;
        Reference< XDesktop > xDesktop( xSMgr->createInstance(::rtl::OUString::createFromAscii("com.sun.star.frame.Desktop")), UNO_QUERY );
        aDesktop <<= xDesktop ;
        SbxObjectRef xUnoObj = GetSbUnoObject( DEFINE_CONST_UNICODE("StarDesktop"), aDesktop );
        xUnoObj->SetFlag( SBX_DONTSTORE );
        pBas->Insert( xUnoObj );
        //pBas->setRoot( xDesktop );
*/

        // Basic container
        SfxScriptLibraryContainer* pBasicCont = new SfxScriptLibraryContainer
            ( DEFINE_CONST_UNICODE( "StarBasic" ), pBasMgr );
        pBasicCont->acquire();  // Hold via UNO
        Reference< XLibraryContainer > xBasicCont = static_cast< XLibraryContainer* >( pBasicCont );
//        pAppData_Impl->pBasicLibContainer = pBasicCont;
        pBasicCont->setBasicManager( pBasMgr );

        // Dialog container
        SfxDialogLibraryContainer* pDialogCont = new SfxDialogLibraryContainer( NULL );
        pDialogCont->acquire(); // Hold via UNO
        Reference< XLibraryContainer > xDialogCont = static_cast< XLibraryContainer* >( pDialogCont );
//        pAppData_Impl->pDialogLibContainer = pDialogCont;

        LibraryContainerInfo* pInfo = new LibraryContainerInfo
            ( xBasicCont, xDialogCont, static_cast< OldBasicPassword* >( pBasicCont ) );
        pBasMgr->SetLibraryContainerInfo( pInfo );

/*      Any aBasicCont;
        aBasicCont <<= xBasicCont;
        xUnoObj = GetSbUnoObject( DEFINE_CONST_UNICODE("BasicLibraries"), aBasicCont );
        pBas->Insert( xUnoObj );

        Any aDialogCont;
        aDialogCont <<= xDialogCont;
        xUnoObj = GetSbUnoObject( DEFINE_CONST_UNICODE("DialogLibraries"), aDialogCont );
        pBas->Insert( xUnoObj );

        Any aAny;
        SfxObjectShell* pDoc = SfxObjectShell::Current();
        if ( pDoc )
        {
            Reference< XInterface > xInterface ( pDoc->GetModel(), UNO_QUERY );
            aAny <<= xInterface;
        }

        SFX_APP()->Get_Impl()->pThisDocument = pDoc;
        xUnoObj = GetSbUnoObject( DEFINE_CONST_UNICODE("ThisComponent"), aAny );
        xUnoObj->SetFlag( SBX_DONTSTORE );
        pBas->Insert( xUnoObj );
*/

        // Konstanten
//ASDBG     RegisterBasicConstants( "so", aConstants, sizeof(aConstants)/sizeof(SfxConstant) );

        // Durch MakeVariable wird das Basic modifiziert.
        if ( !bBasicWasModified )
            pBas->SetModified( sal_False );
    }

    return pBasMgr;
}

//--------------------------------------------------------------------


//--------------------------------------------------------------------

/*?*/ Reference< XLibraryContainer > SfxApplication::GetBasicContainer()
/*?*/ {DBG_BF_ASSERT(0, "STRIP");   Reference< XLibraryContainer > xRet; return xRet;//STRIP001
/*?*/ }

//--------------------------------------------------------------------

/*N*/ StarBASIC* SfxApplication::GetBasic()
/*N*/ {
/*N*/   return GetBasicManager()->GetLib(0);
/*N*/ }

//--------------------------------------------------------------------


//--------------------------------------------------------------------

/*N*/ void SfxApplication::EnterBasicCall()
/*N*/ {
/*N*/   if ( 1 == ++pAppData_Impl->nBasicCallLevel )
/*N*/   {
/*N*/       DBG_TRACE( "SfxShellObject: BASIC-on-demand" );
/*N*/
/*N*/       // das kann l"anger dauern, da Progress nicht geht, wenigstens Sanduhr
/*N*/ //(mba)/task        SfxWaitCursor aWait;
/*N*/
/*N*/       // zuerst das BASIC laden
/*N*/       GetBasic();
/*
        // als erstes SfxShellObject das SbxObject der SfxApplication erzeugen
        SbxObject *pSbx = GetSbxObject();
        DBG_ASSERT( pSbx, "SfxShellObject: can't create SbxObject for SfxApplication" );

        // die SbxObjects aller Module erzeugen
        SfxModuleArr_Impl& rArr = GetModules_Impl();
        for ( sal_uInt16 n = 0; n < rArr.Count(); ++n )
        {
            SfxModule *pMod = rArr.GetObject(n);
            if ( pMod->IsLoaded() )
            {
                pSbx = pMod->GetSbxObject();
                DBG_ASSERT( pSbx, "SfxModule: can't create SbxObject" );
            }
        }

        // die SbxObjects aller Tasks erzeugen
        for ( SfxTask *pTask = SfxTask::GetFirst(); pTask; pTask = SfxTask::GetNext( *pTask ) )
            pTask->GetSbxObject();

        // die SbxObjects aller SfxObjectShells erzeugen (ggf. Frame-los!)
        for ( SfxObjectShell *pObjSh = SfxObjectShell::GetFirst( NULL, sal_False );
              pObjSh;
              pObjSh = SfxObjectShell::GetNext(*pObjSh, NULL, sal_False) )
        {
            // kein IP-Object oder wenn doch dann initialisiert?
            SvStorageRef aStorage;
            if ( !pObjSh->IsHandsOff() )
                aStorage = pObjSh->GetStorage();
            if ( !pObjSh->GetInPlaceObject() || aStorage.Is() )
            {
                DBG( DbgOutf( "SfxShellObject: BASIC-on-demand for %s",
                              pObjSh->SfxShell::GetName().GetBuffer() ) );
                pSbx = pObjSh->GetSbxObject();
                DBG_ASSERT( pSbx, "SfxShellObject: can't create SbxObject" );
            }
        }

        // die SbxObjects der SfxShells auf den Stacks der Frames erzeugen
        for ( SfxViewFrame *pFrame = SfxViewFrame::GetFirst(0,0,sal_False);
              pFrame;
              pFrame = SfxViewFrame::GetNext(*pFrame,0,0,sal_False) )
        {
            // den Dispatcher des Frames rausholen
            SfxDispatcher *pDispat = pFrame->GetDispatcher();
            pDispat->Flush();

            // "uber alle SfxShells auf dem Stack des Dispatchers iterieren
            // Frame selbst wird ausgespart, da er indirekt angezogen wird,
            // sofern er ein Dokument enth"alt.
            for ( sal_uInt16 nStackIdx = pDispat->GetShellLevel(*pFrame);
                  0 != nStackIdx;
                  --nStackIdx )
            {
                DBG( DbgOutf( "SfxShellObject: BASIC-on-demand for level %u", nStackIdx-1 ); )
                pSbx = pDispat->GetShell(nStackIdx - 1)->GetSbxObject();
                DBG_ASSERT( pSbx, "SfxShellObject: can't create SbxObject" );
            }

            if ( !pFrame->GetObjectShell() )
            {
                DBG( DbgOutf( "SfxShellObject: BASIC-on-demand for empty frame" ); )
                pSbx = pFrame->GetSbxObject();
                DBG_ASSERT( pSbx, "SfxShellObject: can't create SbxObject" );
            }
        }
*/
        // Factories anmelden
//        SbxBase::AddFactory( new SfxSbxObjectFactory_Impl );
/*N*/   }
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void SfxApplication::LeaveBasicCall()
/*N*/ {
/*N*/   --pAppData_Impl->nBasicCallLevel;
/*N*/ }

}
