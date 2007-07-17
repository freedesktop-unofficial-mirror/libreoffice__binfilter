/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sfx2_appdata.cxx,v $
 *
 *  $Revision: 1.9 $
 *
 *  last change: $Author: obo $ $Date: 2007-07-17 10:34:23 $
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
#ifndef _CONFIG_HXX
#include <tools/config.hxx>
#endif

#define _SVSTDARR_STRINGS
#include <svtools/svstdarr.hxx>

#include "app.hxx"
#include "appdata.hxx"
#include "doctempl.hxx"
#include "docfile.hxx"
#include "imestatuswindow.hxx"

#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif
namespace binfilter {

/*N*/ SfxAppData_Impl::SfxAppData_Impl( SfxApplication* pApp ) :
/*N*/       pProgress(0),
/*N*/       pPool(0),
/*N*/       pDdeService( 0 ),
/*N*/       pDocTopics( 0 ),
/*N*/       pEventConfig(0),
/*N*/       nBasicCallLevel(0),
/*N*/       nRescheduleLocks(0),
/*N*/       nInReschedule(0),
/*N*/       pInitLinkList(0),
            pSfxFrameObjectFactoryPtr(0),
            pThisDocument(0),
/*N*/       pMatcher( 0 ),
/*N*/       pCancelMgr( 0 ),
/*N*/       pTriggerTopic(0),
/*N*/       pDdeService2(0),
/*N*/       pMiscConfig(0),
/*N*/       bInQuit(sal_False),
/*N*/       bInException( sal_False ),
/*N*/       m_xImeStatusWindow(new sfx2::appl::ImeStatusWindow(
/*N*/                                *pApp, ::legacy_binfilters::getLegacyProcessServiceFactory()))
/*N*/ {
/*N*/ }

/*N*/ SfxAppData_Impl::~SfxAppData_Impl()
/*N*/ {
/*N*/   DeInitDDE();
/*N*/   delete pCancelMgr;
/*N*/ }
}
