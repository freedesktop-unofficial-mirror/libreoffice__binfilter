/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */

#include <com/sun/star/frame/XDesktop.hpp>
#include <com/sun/star/uno/Reference.h>

#include <tools/urlobj.hxx>
#include <bf_svtools/rectitem.hxx>
#include <bf_svtools/intitem.hxx>
#include <bf_svtools/eitem.hxx>
#include <bf_svtools/stritem.hxx>
#include <bf_svtools/pathoptions.hxx>

#ifdef _MSC_VER
#pragma hdrstop
#endif

#include "appuno.hxx"
#include "objsh.hxx"
#include "app.hxx"
#include "appdata.hxx"
#include "appimp.hxx"
#include "dlgcont.hxx"

#include "scriptcont.hxx"

#define ITEMID_SEARCH SID_SEARCH_ITEM


#include <legacysmgr/legacy_binfilters_smgr.hxx>
#include "bf_so3/staticbaseurl.hxx"
#include <boost/scoped_ptr.hpp>

namespace binfilter {

using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::frame;
using namespace ::com::sun::star::script;

//--------------------------------------------------------------------

namespace
{
    class AppBasicManagerHolder
    {
    private:
        SfxScriptLibraryContainer* m_pBasicCont;
        SfxDialogLibraryContainer* m_pDialogCont;
        BasicManager* m_pAppBasicManager;
    public:
        AppBasicManagerHolder();
        BasicManager* getBasicManager() { return m_pAppBasicManager; };
        ~AppBasicManagerHolder();
    };

    boost::scoped_ptr<AppBasicManagerHolder> s_pAppBasicManager;

    AppBasicManagerHolder::AppBasicManagerHolder()
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

        m_pAppBasicManager = new BasicManager(new StarBASIC, &aAppBasicDir);

        // Als Destination das erste Dir im Pfad:
        String aFileName( aAppBasic.getName() );
        aAppBasic = INetURLObject( aAppBasicDir.GetToken(1) );
        DBG_ASSERT( aAppBasic.GetProtocol() != INET_PROT_NOT_VALID, "Invalid URL!" );
        aAppBasic.insertName( aFileName );
        m_pAppBasicManager->SetStorageName( aAppBasic.PathToFileName() );

        // globale Variablen
        StarBASIC *pBas = m_pAppBasicManager->GetLib(0);
        sal_Bool bBasicWasModified = pBas->IsModified();

        // Basic container
        m_pBasicCont = new SfxScriptLibraryContainer
            ( DEFINE_CONST_UNICODE( "StarBasic" ), m_pAppBasicManager );
        m_pBasicCont->acquire();    // Hold via UNO
        Reference< XLibraryContainer > xBasicCont = static_cast< XLibraryContainer* >( m_pBasicCont );
        m_pBasicCont->setBasicManager( m_pAppBasicManager );

        // Dialog container
        m_pDialogCont = new SfxDialogLibraryContainer( NULL );
        m_pDialogCont->acquire();   // Hold via UNO
        Reference< XLibraryContainer > xDialogCont = static_cast< XLibraryContainer* >( m_pDialogCont );

        LibraryContainerInfo* pInfo = new LibraryContainerInfo
            ( xBasicCont, xDialogCont, static_cast< OldBasicPassword* >( m_pBasicCont ) );
        m_pAppBasicManager->SetLibraryContainerInfo( pInfo );

        // Durch MakeVariable wird das Basic modifiziert.
        if ( !bBasicWasModified )
            pBas->SetModified( sal_False );
    }

    AppBasicManagerHolder::~AppBasicManagerHolder()
    {
        m_pDialogCont->release();
        m_pBasicCont->release();
        BasicManager::LegacyDeleteBasicManager(m_pAppBasicManager);
    }
}

//========================================================================

StarBASIC* SfxApplication::GetBasic_Impl() const
{
    if (!s_pAppBasicManager)
        return NULL;
    return s_pAppBasicManager->getBasicManager()->GetLib(0);
}

//=========================================================================

BasicManager* SfxApplication::GetBasicManager()
{
    if ( pAppData_Impl->nBasicCallLevel == 0 )
        // sicherheitshalber
        EnterBasicCall();

    if (!s_pAppBasicManager)
        s_pAppBasicManager.reset(new AppBasicManagerHolder);

    return s_pAppBasicManager->getBasicManager();
}

//--------------------------------------------------------------------

/*N*/ StarBASIC* SfxApplication::GetBasic()
/*N*/ {
/*N*/   return GetBasicManager()->GetLib(0);
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void SfxApplication::EnterBasicCall()
/*N*/ {
/*N*/   if ( 1 == ++pAppData_Impl->nBasicCallLevel )
/*N*/   {
/*N*/       OSL_TRACE( "SfxShellObject: BASIC-on-demand" );
/*N*/
/*N*/       // zuerst das BASIC laden
/*N*/       GetBasic();
/*N*/   }
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void SfxApplication::LeaveBasicCall()
/*N*/ {
/*N*/   --pAppData_Impl->nBasicCallLevel;
/*N*/ }

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
