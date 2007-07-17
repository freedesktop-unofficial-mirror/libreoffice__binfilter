/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: schdll0.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: obo $ $Date: 2007-07-17 12:30:52 $
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

#ifndef _SCHDLL0_HXX
#define _SCHDLL0_HXX

#include <so3/pseudo.hxx>

#ifndef _SFXMODULE_HXX //autogen
#include <bf_sfx2/module.hxx>
#endif
#ifndef _TOOLS_RESMGR_HXX //autogen
#include <tools/resmgr.hxx>
#endif

class SotFactory;
class SvFactory;
namespace binfilter {

/*************************************************************************
|*
|* This tricky class keeps pointers to the SvFactories while
|* the DLL isn`t loaded. A pointer to the one instance is available
|* through SD_MOD() (shared-lib-app-data).
|*
\************************************************************************/

class SchModuleDummy : public SfxModule
{
public:
    TYPEINFO();

                // SvFactory name convention:
                // 'p' + SfxObjectShell-subclass + 'Factory'
    SotFactory *pSchChartDocShellFactory;  // Namensaufbau zwingend!!

    SchModuleDummy(ResMgr    *pResMgr,
                   BOOL      bDummy,
                   SotFactory *pObjFact) :
        SfxModule(pResMgr, bDummy, (SfxObjectFactory*) pObjFact, NULL),
        pSchChartDocShellFactory(pObjFact)
    {
    }

    virtual SfxModule *Load ();

    static const SvGlobalName GetID(USHORT nFileFormat);
    static USHORT HasID (const SvGlobalName& rID);

};

#ifndef _SCH_DLL                      // Das define muss im Draw gesetzt werden
#define SCH_MOD() ( *(SchModuleDummy**) GetAppData(BF_SHL_SCH) )
#endif

} //namespace binfilter
#endif
