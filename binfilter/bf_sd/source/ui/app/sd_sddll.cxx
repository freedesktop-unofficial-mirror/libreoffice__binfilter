/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sd_sddll.cxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 07:32:20 $
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

#include <bf_svx/svdobj.hxx>
#include <bf_svtools/moduleoptions.hxx>

#include "bf_sd/grdocsh.hxx"
#include "sdresid.hxx"
#include "sdobjfac.hxx"
#include "cfgids.hxx"

namespace binfilter {

void SdDLL::Init()
{
    // the SdModule must be created
    SdModuleDummy** ppShlPtr = (SdModuleDummy**) GetAppData(BF_SHL_DRAW);
    SvFactory* pDrawFact    = (SvFactory*)(*ppShlPtr)->pSdDrawDocShellFactory;
    SvFactory* pGraphicFact = (SvFactory*)(*ppShlPtr)->pSdGraphicDocShellFactory;
    delete (*ppShlPtr);
    (*ppShlPtr) = new SdModule(pDrawFact, pGraphicFact);
    (*ppShlPtr)->pSdDrawDocShellFactory    = pDrawFact;
    (*ppShlPtr)->pSdGraphicDocShellFactory = pGraphicFact;

    SdrObjFactory::InsertMakeUserDataHdl(LINK(&aSdObjectFactory, SdObjectFactory, MakeUserData));
}

void SdDLL::Exit()
{
    SdrObjFactory::RemoveMakeUserDataHdl(LINK(&aSdObjectFactory, SdObjectFactory, MakeUserData));

    SdModuleDummy** ppShlPtr = (SdModuleDummy**) GetAppData(BF_SHL_DRAW);
    delete (*ppShlPtr);
    (*ppShlPtr) = NULL;
}
}
