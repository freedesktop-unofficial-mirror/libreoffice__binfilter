/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: module.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: obo $ $Date: 2007-07-17 12:39:46 $
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
#ifndef _SFXMODULE_HXX
#define _SFXMODULE_HXX  // intern
#define _SFXMOD_HXX     // extern

#ifndef _SFX_SHELL_HXX
#include <bf_sfx2/shell.hxx>
#endif

#ifndef _SAL_TYPES_H_
#include <sal/types.h>
#endif

class ResMgr;

namespace binfilter {

class SfxObjectFactory;
class SfxObjectFactory;
class SfxModuleArr_Impl;
class SfxModule_Impl;
class SfxSlotPool;

class ISfxModule
{
public:
    virtual                 ~ISfxModule(){};
    virtual ResMgr*         GetResMgr() = 0;
};

//====================================================================

class SfxModule : public SfxShell, public ISfxModule
{
private:
    ResMgr*                     pResMgr;
    sal_Bool                    bDummy : 1;

protected:
    virtual sal_Bool                QueryUnload();

public:
                                TYPEINFO();

                                SfxModule( ResMgr* pMgrP, sal_Bool bDummy,
                                    SfxObjectFactory* pFactoryP, ... );
                                ~SfxModule();

    virtual SfxModule*          Load();
    virtual void                Free();
    sal_Bool                        IsLoaded() const { return !bDummy; }

    virtual ResMgr*             GetResMgr();

#if _SOLAR__PRIVATE
    static SfxModuleArr_Impl&   GetModules_Impl();
#endif
};

#define SFX_IMPL_MODULE_LIBRARY( LibName )                                  \
                                                                            \
        extern "C" void _CDECLARE_ Init##LibName##Dll()                     \
        {                                                                   \
            LibName##DLL::Init();                                           \
        }                                                                   \
        extern "C" void _CDECLARE_ DeInit##LibName##Dll()                   \
        {                                                                   \
            LibName##DLL::Exit();                                           \
        }

}//end of namespace binfilter
#endif

