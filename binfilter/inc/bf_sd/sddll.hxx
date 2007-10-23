/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sddll.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: vg $ $Date: 2007-10-23 14:20:33 $
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

#ifndef _SDDLL_HXX
#define _SDDLL_HXX

#include <bf_so3/pseudo.hxx>

#ifndef _SFXMODULE_HXX //autogen
#include <bf_sfx2/module.hxx>
#endif
#ifndef _SFXDEFS_HXX //autogen
#include <bf_sfx2/sfxdefs.hxx>
#endif
class SvFactory;
class SotFactory;
namespace binfilter {

class SfxMedium;
class SfxFilter;

/*************************************************************************
|*
|* This class is a wrapper for a Load-On-Demand-DLL. One instance
|* per SfxApplication will be created for the runtime of
|* SfxApplication-subclass::Main().
|*
|* Remember: Do export this class! It is used by the application.
|*
\************************************************************************/

class SdDLL
{
protected:
    static void     RegisterFactorys();
    static void     RegisterInterfaces();
    static void     RegisterControllers();

public:
                    // Ctor/Dtor must be linked to the application
                    SdDLL();
                    ~SdDLL();

                    // static-init/exit-code must be linked to the application
    static void     LibInit();  // called from SfxApplication-subclass::Init()
    static void     LibExit();  // called from SfxApplication-subclass::Exit()

                    // DLL-init/exit-code must be linked to the DLL only
    static void     Init();     // called directly after loading the DLL
    static void     Exit();     // called directly befor unloading the DLL

    static ULONG    DetectFilter(SfxMedium& rMedium, const SfxFilter** pFilter,
                                 SfxFilterFlags nMust, SfxFilterFlags nDont);
};

/*************************************************************************
|*
|* This tricky class keeps pointers to the SvFactories while
|* the DLL isn`t loaded. A pointer to the one instance is available
|* through SD_MOD() (shared-lib-app-data).
|*
\************************************************************************/

class SdModuleDummy : public SfxModule
{
public:
    TYPEINFO();

                // SvFactory name convention:
                // 'p' + SfxObjectShell-subclass + 'Factory'
    SotFactory* pSdDrawDocShellFactory;
    SotFactory* pSdGraphicDocShellFactory;

               SdModuleDummy(ResMgr* pResMgr, BOOL bDummy,
                             SotFactory* pDrawObjFact, SotFactory* pGraphicObjFact)
               : SfxModule(pResMgr, bDummy,
                            // Der erste Factory-Pointer muss gueltig sein!
                           (SfxObjectFactory*) (pDrawObjFact ? pDrawObjFact    : pGraphicObjFact),
                           (SfxObjectFactory*) (pDrawObjFact ? pGraphicObjFact : pDrawObjFact),
                           0L),
                 pSdDrawDocShellFactory( pDrawObjFact ),
                 pSdGraphicDocShellFactory( pGraphicObjFact )
               {}

    virtual SfxModule*  Load();

    static SvGlobalName GetID(USHORT nFileFormat);
    static USHORT       HasID(const SvGlobalName& rName);
};

#ifndef _SD_DLL                      // Das define muss im Draw gesetzt werden
#define SD_MOD() ( *(SdModuleDummy**) GetAppData(BF_SHL_DRAW) )
#endif

} //namespace binfilter
#endif                               // _SDDLL_HXX

