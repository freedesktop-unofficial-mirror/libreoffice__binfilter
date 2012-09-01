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

#include <bf_svtools/pathoptions.hxx>

#include <com/sun/star/lang/XServiceInfo.hpp>
#include <com/sun/star/container/XNameContainer.hpp>

#include <cppuhelper/implbase2.hxx>

#include "xtable.hxx"
namespace binfilter {

using namespace ::com::sun::star;
using namespace ::rtl;
using namespace ::cppu;

class SvxUnoColorTable : public WeakImplHelper2< container::XNameContainer, lang::XServiceInfo >
{
private:
    XColorTable*    pTable;

public:
    SvxUnoColorTable() throw();
    virtual ~SvxUnoColorTable() throw();

    // XServiceInfo
    virtual OUString SAL_CALL getImplementationName(  ) throw( uno::RuntimeException );
    virtual sal_Bool SAL_CALL supportsService( const  OUString& ServiceName ) throw( uno::RuntimeException);
    virtual uno::Sequence<  OUString > SAL_CALL getSupportedServiceNames(  ) throw( uno::RuntimeException);

    static OUString getImplementationName_Static() throw()
    {
        return OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.drawing.SvxUnoColorTable"));
    }

    static uno::Sequence< OUString >  getSupportedServiceNames_Static(void) throw();

    // XNameContainer
    virtual void SAL_CALL insertByName( const  OUString& aName, const  uno::Any& aElement ) throw( lang::IllegalArgumentException, container::ElementExistException, lang::WrappedTargetException, uno::RuntimeException);
    virtual void SAL_CALL removeByName( const  OUString& Name ) throw( container::NoSuchElementException, lang::WrappedTargetException, uno::RuntimeException);

    // XNameReplace
    virtual void SAL_CALL replaceByName( const  OUString& aName, const  uno::Any& aElement ) throw( lang::IllegalArgumentException, container::NoSuchElementException, lang::WrappedTargetException, uno::RuntimeException);

    // XNameAccess
    virtual uno::Any SAL_CALL getByName( const  OUString& aName ) throw( container::NoSuchElementException, lang::WrappedTargetException, uno::RuntimeException);

    virtual uno::Sequence<  OUString > SAL_CALL getElementNames(  ) throw( uno::RuntimeException);

    virtual sal_Bool SAL_CALL hasByName( const  OUString& aName ) throw( uno::RuntimeException);

    // XElementAccess
    virtual uno::Type SAL_CALL getElementType(  ) throw( uno::RuntimeException);
    virtual sal_Bool SAL_CALL hasElements(  ) throw( uno::RuntimeException);
};

SvxUnoColorTable::SvxUnoColorTable() throw()
{
    pTable = new XColorTable( SvtPathOptions().GetPalettePath() );
}

SvxUnoColorTable::~SvxUnoColorTable() throw()
{
    delete pTable;
}

sal_Bool SAL_CALL SvxUnoColorTable::supportsService( const  OUString& ServiceName ) throw(uno::RuntimeException)
{
    uno::Sequence< OUString > aSNL( getSupportedServiceNames() );
    const OUString * pArray = aSNL.getConstArray();

    for( INT32 i = 0; i < aSNL.getLength(); i++ )
        if( pArray[i] == ServiceName )
            return TRUE;

    return FALSE;
}

OUString SAL_CALL SvxUnoColorTable::getImplementationName() throw( uno::RuntimeException )
{
    return OUString( RTL_CONSTASCII_USTRINGPARAM("SvxUnoColorTable") );
}

uno::Sequence< OUString > SAL_CALL SvxUnoColorTable::getSupportedServiceNames(  )
    throw( uno::RuntimeException )
{
    return getSupportedServiceNames_Static();
}

uno::Sequence< OUString > SvxUnoColorTable::getSupportedServiceNames_Static(void) throw()
{
    uno::Sequence< OUString > aSNS( 1 );
    aSNS.getArray()[0] = OUString( RTL_CONSTASCII_USTRINGPARAM("com.sun.star.drawing.ColorTable" ));
    return aSNS;
}

// XNameContainer
void SAL_CALL SvxUnoColorTable::insertByName( const OUString& aName, const uno::Any& aElement )
    throw( lang::IllegalArgumentException, container::ElementExistException, lang::WrappedTargetException, uno::RuntimeException )
{
    if( hasByName( aName ) )
        throw container::ElementExistException();

    INT32 nColor = 0;
    if( aElement >>= nColor )
        throw lang::IllegalArgumentException();

    if( pTable )
    {
        XColorEntry* pEntry = new XColorEntry( Color( (ColorData)nColor ), aName  );
        pTable->Insert( pEntry, pTable->Count() );
    }
}

void SAL_CALL SvxUnoColorTable::removeByName( const OUString& /*rName*/ )
    throw( container::NoSuchElementException, lang::WrappedTargetException, uno::RuntimeException)
{DBG_BF_ASSERT(0, "STRIP");
}

// XNameReplace
void SAL_CALL SvxUnoColorTable::replaceByName( const OUString& aName, const uno::Any& aElement )
    throw( lang::IllegalArgumentException, container::NoSuchElementException, lang::WrappedTargetException, uno::RuntimeException )
{
    INT32 nColor = 0;
    if( aElement >>= nColor )
        throw lang::IllegalArgumentException();

    long nIndex = pTable ? ((XPropertyList*)pTable)->Get( aName ) : -1;
    if( nIndex == -1  )
        throw container::NoSuchElementException();

    XColorEntry* pEntry = new XColorEntry( Color( (ColorData)nColor ), aName );
    delete pTable->Replace( nIndex, pEntry );
}

// XNameAccess
uno::Any SAL_CALL SvxUnoColorTable::getByName( const  OUString& /*rName*/ )
    throw( container::NoSuchElementException,  lang::WrappedTargetException, uno::RuntimeException)
{DBG_BF_ASSERT(0, "STRIP");     uno::Any aAny; return aAny;
}

uno::Sequence< OUString > SAL_CALL SvxUnoColorTable::getElementNames(  )
    throw( uno::RuntimeException )
{
    const long nCount = pTable ? pTable->Count() : 0;

    uno::Sequence< OUString > aSeq( nCount );

    return aSeq;
}

sal_Bool SAL_CALL SvxUnoColorTable::hasByName( const OUString& aName )
    throw( uno::RuntimeException )
{
    long nIndex = pTable ? ((XPropertyList*)pTable)->Get( aName ) : -1;
    return nIndex != -1;
}

// XElementAccess
uno::Type SAL_CALL SvxUnoColorTable::getElementType(  )
    throw( uno::RuntimeException )
{
    return ::getCppuType((const sal_Int32*)0);
}

sal_Bool SAL_CALL SvxUnoColorTable::hasElements(  )
    throw( uno::RuntimeException )
{
    return pTable && pTable->Count() != 0;
}

/**
 * Create a colortable
 */
uno::Reference< uno::XInterface > SAL_CALL SvxUnoColorTable_createInstance(const uno::Reference< lang::XMultiServiceFactory > & /*rSMgr*/) throw(uno::Exception)
{
    return *new SvxUnoColorTable();
}

//
// export this service
//
}

#include <osl/diagnose.h>

#include <cppuhelper/factory.hxx>
#include <uno/lbnames.h>
namespace binfilter {
//------the following is added for sfx2 integrate with svx
extern "C" {
void* SAL_CALL sfx2_component_getFactory(   const   sal_Char*   pImplementationName ,
                                                 void*      pServiceManager     ,
                                                 void*      pRegistryKey        );

}

extern "C"
{

void SAL_CALL writeInfo( registry::XRegistryKey * pRegistryKey, const OUString& rImplementationName, const uno::Sequence< OUString >& rServices )
{
    uno::Reference< registry::XRegistryKey > xNewKey(
        pRegistryKey->createKey(
            OUString( RTL_CONSTASCII_USTRINGPARAM("/") ) + rImplementationName + OUString(RTL_CONSTASCII_USTRINGPARAM( "/UNO/SERVICES") ) ) );

    for( sal_Int32 i = 0; i < rServices.getLength(); i++ )
        xNewKey->createKey( rServices.getConstArray()[i]);
}

SAL_DLLPUBLIC_EXPORT void * SAL_CALL component_getFactory( const sal_Char * pImplName, void * pServiceManager, void * pRegistryKey )
{
    void * pRet = 0;
    if( pServiceManager  )
    {
        uno::Reference< lang::XSingleServiceFactory > xFactory;

        if( rtl_str_compare( pImplName, "com.sun.star.drawing.SvxUnoColorTable" ) == 0 )
        {
            xFactory = createSingleFactory( reinterpret_cast< lang::XMultiServiceFactory * >( pServiceManager ),
                SvxUnoColorTable::getImplementationName_Static(),
                SvxUnoColorTable_createInstance,
                SvxUnoColorTable::getSupportedServiceNames_Static() );
        }
#ifndef SVX_LIGHT
        /*else if( svx::GraphicExporter_getImplementationName().equalsAscii( pImplName ) )
        {
            xFactory = ::cppu::createSingleFactory( reinterpret_cast< lang::XMultiServiceFactory * >( pServiceManager ),
                svx::GraphicExporter_getImplementationName(),
                svx::GraphicExporter_createInstance,
                svx::GraphicExporter_getSupportedServiceNames() );
        }*/
#endif
        if( xFactory.is())
        {
            xFactory->acquire();
            pRet = xFactory.get();
        }
    }
    if (0==pRet)// added for sfx2 moudle integration with svx
    {
        pRet=sfx2_component_getFactory(pImplName,pServiceManager,pRegistryKey);
    }

    return pRet;
}

}


}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
