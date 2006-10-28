/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: bf_migrateexports.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 02:22:46 $
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
#include <stdio.h>

#include <osl/thread.h>


#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>
#endif

#ifndef _BF_MIGRATEFILTER_HXX
#include <bf_migratefilter.hxx>
#endif
namespace binfilter {

using namespace ::rtl;
using namespace ::cppu;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::registry;

extern "C"
{

//==================================================================================================
void SAL_CALL component_getImplementationEnvironment(const sal_Char** ppEnvTypeName, uno_Environment** ppEnv)
{
    *ppEnvTypeName = CPPU_CURRENT_LANGUAGE_BINDING_NAME;
}

//==================================================================================================
sal_Bool SAL_CALL component_writeInfo(void* pServiceManager, void* pRegistryKey)
{
    if(pRegistryKey)
    {
        try
        {
            sal_Bool bLegacySmgrWriteInfoDidWork(legacysmgr_component_writeInfo
                ( reinterpret_cast<XMultiServiceFactory*>( pServiceManager), reinterpret_cast<XRegistryKey*> (pRegistryKey) ));
            OSL_ENSURE(bLegacySmgrWriteInfoDidWork, "### LegacyServiceManager writeInfo failed!" );

            Reference< XRegistryKey > xNewKey;
            xNewKey = reinterpret_cast< XRegistryKey * >(pRegistryKey)->createKey(bf_MigrateFilter_getImplementationName());
            xNewKey = xNewKey->createKey(OUString::createFromAscii("/UNO/SERVICES"));

            const Sequence< OUString > & rSNL = bf_MigrateFilter_getSupportedServiceNames();
            const OUString * pArray = rSNL.getConstArray();

            for(sal_Int32 nPos(rSNL.getLength()); nPos--; )
                xNewKey->createKey(pArray[nPos]);

            return sal_True;
        }
        catch (InvalidRegistryException &)
        {
            OSL_ENSURE(sal_False, "### InvalidRegistryException!");
        }
    }

    return sal_False;
}

//==================================================================================================
void* SAL_CALL component_getFactory(const sal_Char* pImplName, void* pServiceManager, void* pRegistryKey)
{
    void* pRet = 0;

    OUString implName = OUString::createFromAscii(pImplName);

    if(pServiceManager && implName.equals(bf_MigrateFilter_getImplementationName()))
    {
        Reference< XSingleServiceFactory > xFactory(createSingleFactory(
            reinterpret_cast< XMultiServiceFactory * >(pServiceManager),
            OUString::createFromAscii(pImplName),
            bf_MigrateFilter_createInstance, bf_MigrateFilter_getSupportedServiceNames()));

        if(xFactory.is())
        {
            xFactory->acquire();
            pRet = xFactory.get();
        }

        // init LegacyServiceFactory
        legacysmgr_component_getFactory(
            pImplName,
            reinterpret_cast< XMultiServiceFactory *>(pServiceManager),
            reinterpret_cast<XRegistryKey*> (pRegistryKey) );
    }

    return pRet;
}
}

// eof
}
