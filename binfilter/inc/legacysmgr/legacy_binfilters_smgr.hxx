#ifndef _LEGACYBINFILTERSMGR_HXX
#define _LEGACYBINFILTERSMGR_HXX

#include "com/sun/star/lang/XMultiServiceFactory.hpp"
#ifndef _COM_SUN_STAR_UNO_REFERENCE_HXX_
#include <com/sun/star/uno/Reference.hxx>
#endif
#include <com/sun/star/registry/XRegistryKey.hpp>
//#ifndef _UNO_ENVIRONMENT_H_
//#include <uno/environment.h>
//#endif
#include "cppuhelper/factory.hxx"
namespace legacy_binfilters
{

::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory > const & SAL_CALL getLegacyProcessServiceFactory();

} //namespace legacy_binfilters

extern "C"
{
//==================================================================================================
void SAL_CALL legacy_component_getImplementationEnvironment(
    sal_Char const ** ppEnvTypeName, uno_Environment ** ppEnv );
//==================================================================================================
sal_Bool SAL_CALL legacysmgr_component_writeInfo(
    ::com::sun::star::lang::XMultiServiceFactory * smgr, ::com::sun::star::registry::XRegistryKey * key );
void * SAL_CALL legacysmgr_component_getFactory(
    sal_Char const * implName, ::com::sun::star::lang::XMultiServiceFactory * smgr, ::com::sun::star::registry::XRegistryKey * key );
}
#endif