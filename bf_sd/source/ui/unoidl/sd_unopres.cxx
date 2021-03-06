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

#include <bf_svx/dialogs.hrc>              // fuer SID_REHEARSE_TIMINGS
#include <bf_svx/unoprov.hxx>
#include <vcl/svapp.hxx>

#include "unopres.hxx"
#include "unocpres.hxx"
#include "bf_sd/docshell.hxx"
#include "sdattr.hxx"
#include "cusshow.hxx"
#include "unoprnms.hxx"
#include "unohelp.hxx"
#include "unopage.hxx"

#include <osl/mutex.hxx>

namespace binfilter {

using namespace ::rtl;
using namespace ::cppu;
using namespace ::com::sun::star;

const SfxItemPropertyMap* ImplGetPresentationPropertyMap()
{
    static const SfxItemPropertyMap aPresentationPropertyMap_Impl[] =
    {
        { MAP_CHAR_LEN("IsShowAll"),                ATTR_PRESENT_ALL,               &::getBooleanCppuType(),                0, 0 },
        { MAP_CHAR_LEN(UNO_NAME_SHOW_ALLOWANIM),    ATTR_PRESENT_ANIMATION_ALLOWED, &::getBooleanCppuType(),                0, 0 },
        { MAP_CHAR_LEN(UNO_NAME_SHOW_CUSTOMSHOW),   ATTR_PRESENT_CUSTOMSHOW,        &::getCppuType((const OUString*)0),     0, 0 },
        { MAP_CHAR_LEN(UNO_NAME_SHOW_FIRSTPAGE),    ATTR_PRESENT_DIANAME,           &::getCppuType((const OUString*)0),     0, 0 },
        { MAP_CHAR_LEN(UNO_NAME_SHOW_ONTOP),        ATTR_PRESENT_ALWAYS_ON_TOP,     &::getBooleanCppuType(),                0, 0 },
        { MAP_CHAR_LEN(UNO_NAME_SHOW_AUTOMATIC),    ATTR_PRESENT_MANUEL,            &::getBooleanCppuType(),                0, 0 },
        { MAP_CHAR_LEN(UNO_NAME_SHOW_ENDLESS),      ATTR_PRESENT_ENDLESS,           &::getBooleanCppuType(),                0, 0 },
        { MAP_CHAR_LEN(UNO_NAME_SHOW_FULLSCREEN),   ATTR_PRESENT_FULLSCREEN,        &::getBooleanCppuType(),                0, 0 },
        { MAP_CHAR_LEN(UNO_NAME_SHOW_MOUSEVISIBLE),ATTR_PRESENT_MOUSE,              &::getBooleanCppuType(),                0, 0 },
        { MAP_CHAR_LEN(UNO_NAME_SHOW_PAUSE),        ATTR_PRESENT_PAUSE_TIMEOUT,     &::getCppuType((const sal_Int32*)0),    0, 0 },
        { MAP_CHAR_LEN(UNO_NAME_SHOW_STARTWITHNAV),ATTR_PRESENT_NAVIGATOR,          &::getBooleanCppuType(),                0, 0 },
        { MAP_CHAR_LEN(UNO_NAME_SHOW_USEPEN),       ATTR_PRESENT_PEN,               &::getBooleanCppuType(),                0, 0 },
        { MAP_CHAR_LEN("IsTransitionOnClick"),      ATTR_PRESENT_CHANGE_PAGE,       &::getBooleanCppuType(),                0, 0 },
        { MAP_CHAR_LEN("IsShowLogo"),               ATTR_PRESENT_SHOW_PAUSELOGO,    &::getBooleanCppuType(),                0, 0 },
        { 0,0,0,0,0,0 }

    };

    return aPresentationPropertyMap_Impl;
}

///////////////////////////////////////////////////////////////////////////////

SdXPresentation::SdXPresentation(SdXImpressDocument& rMyModel) throw()
    : mrModel(rMyModel)
    , maPropSet(ImplGetPresentationPropertyMap())
{
}

SdXPresentation::~SdXPresentation() throw()
{
}

// XServiceInfo
OUString SAL_CALL SdXPresentation::getImplementationName(  )
    throw(uno::RuntimeException)
{
    return OUString( RTL_CONSTASCII_USTRINGPARAM("SdXPresentation") );
}

sal_Bool SAL_CALL SdXPresentation::supportsService( const OUString& ServiceName )
    throw(uno::RuntimeException)
{
    return SvxServiceInfoHelper::supportsService( ServiceName, getSupportedServiceNames(  ) );
}

uno::Sequence< OUString > SAL_CALL SdXPresentation::getSupportedServiceNames(  )
    throw(uno::RuntimeException)
{
    OUString aService( RTL_CONSTASCII_USTRINGPARAM("com.sun.star.presentation.Presentation") );
    uno::Sequence< OUString > aSeq( &aService, 1 );
    return aSeq;
}

// XPropertySet
uno::Reference< beans::XPropertySetInfo > SAL_CALL SdXPresentation::getPropertySetInfo()
    throw(uno::RuntimeException)
{
    SolarMutexGuard aGuard;
    return maPropSet.getPropertySetInfo();
 }

void SAL_CALL SdXPresentation::setPropertyValue( const OUString& aPropertyName, const uno::Any& aValue )
    throw(beans::UnknownPropertyException, beans::PropertyVetoException, lang::IllegalArgumentException, lang::WrappedTargetException, uno::RuntimeException)
{
    SolarMutexGuard aGuard;

    SdDrawDocument* pDoc = mrModel.GetDoc();
    if(pDoc == NULL)
        throw uno::RuntimeException();

    const SfxItemPropertyMap* pMap = maPropSet.getPropertyMapEntry(aPropertyName);

    switch( pMap ? pMap->nWID : -1 )
    {
    case ATTR_PRESENT_ALL:
    {
        sal_Bool bVal(sal_False);

        if(! sd::any2bool( aValue, bVal ) )
            throw lang::IllegalArgumentException();

        if( pDoc->GetPresAll() != bVal )
        {
            pDoc->SetPresAll( bVal );
            if( bVal )
                pDoc->SetCustomShow( false );
        }
        break;
    }
    case ATTR_PRESENT_CHANGE_PAGE:
    {
        sal_Bool bVal(sal_False);

        if(! sd::any2bool( aValue, bVal ) )
            throw lang::IllegalArgumentException();

        if ( bVal == pDoc->GetPresLockedPages() )
        {
            pDoc->SetPresLockedPages( !bVal );
        }
        break;
    }

    case ATTR_PRESENT_ANIMATION_ALLOWED:
    {
        sal_Bool bVal(sal_False);

        if(! sd::any2bool( aValue, bVal ) )
            throw lang::IllegalArgumentException();

        if(pDoc->IsAnimationAllowed() != bVal)
        {
            pDoc->SetAnimationAllowed(bVal);
        }
        break;
    }
    case ATTR_PRESENT_CUSTOMSHOW:
    {
        OUString aShow;
        if(!(aValue >>= aShow))
            throw lang::IllegalArgumentException();

        const String aShowName( aShow );

        List* pCustomShowList = pDoc->GetCustomShowList(sal_False);
        if(pCustomShowList)
        {
            SdCustomShow* pCustomShow;
            for( pCustomShow = (SdCustomShow*) pCustomShowList->First(); pCustomShow != NULL; pCustomShow = (SdCustomShow*) pCustomShowList->Next() )
            {
                if( pCustomShow->GetName() == aShowName )
                    break;
            }

            pDoc->SetCustomShow( true );
        }
        break;
    }
    case ATTR_PRESENT_ENDLESS:
    {
        sal_Bool bVal(sal_False);

        if(! sd::any2bool( aValue, bVal ) )
            throw lang::IllegalArgumentException();

        if(pDoc->GetPresEndless() != bVal)
        {
            pDoc->SetPresEndless(bVal);
        }
        break;
    }
    case ATTR_PRESENT_FULLSCREEN:
    {
        sal_Bool bVal(sal_False);

        if(! sd::any2bool( aValue, bVal ) )
            throw lang::IllegalArgumentException();

        if(pDoc->GetPresFullScreen() != bVal)
        {
            pDoc->SetPresFullScreen(bVal);
        }
        break;
    }
    case ATTR_PRESENT_DIANAME:
    {
        OUString aPresPage;

        aValue >>= aPresPage;
        pDoc->SetPresPage(SdDrawPage::getUiNameFromPageApiName(aPresPage));
        pDoc->SetCustomShow(false);
        pDoc->SetPresAll(false);

        break;
    }
    case ATTR_PRESENT_MANUEL:
    {
        sal_Bool bVal(sal_False);

        if(! sd::any2bool( aValue, bVal ) )
            throw lang::IllegalArgumentException();

        if(pDoc->GetPresManual() != bVal)
        {
            pDoc->SetPresManual(bVal);
        }
        break;
    }
    case ATTR_PRESENT_MOUSE:
    {
        sal_Bool bVal(sal_False);

        if(! sd::any2bool( aValue, bVal ) )
            throw lang::IllegalArgumentException();

        if(pDoc->GetPresMouseVisible() != bVal)
        {
            pDoc->SetPresMouseVisible(bVal);
        }
        break;
    }
    case ATTR_PRESENT_ALWAYS_ON_TOP:
    {
        sal_Bool bVal(sal_False);

        if(! sd::any2bool( aValue, bVal ) )
            throw lang::IllegalArgumentException();

        if(pDoc->GetPresAlwaysOnTop() != bVal)
        {
            pDoc->SetPresAlwaysOnTop(bVal);
        }
        break;
    }
    case ATTR_PRESENT_NAVIGATOR:
    {
        sal_Bool bVal(sal_False);

        if(! sd::any2bool( aValue, bVal ) )
            throw lang::IllegalArgumentException();

        if(pDoc->GetStartPresWithNavigator() != bVal)
        {
            pDoc->SetStartPresWithNavigator(bVal);
        }
        break;
    }
    case ATTR_PRESENT_PEN:
    {
        sal_Bool bVal(sal_False);

        if(! sd::any2bool( aValue, bVal ) )
            throw lang::IllegalArgumentException();

        if(pDoc->GetPresMouseAsPen() != bVal)
        {
            pDoc->SetPresMouseAsPen(bVal);
        }
        break;
    }
    case ATTR_PRESENT_PAUSE_TIMEOUT:
    {
        sal_Int32 nValue(0);
        if(!(aValue >>= nValue) || (nValue < 0))
            throw lang::IllegalArgumentException();

        pDoc->SetPresPause( (sal_uInt32)nValue );
        break;
    }
    case ATTR_PRESENT_SHOW_PAUSELOGO:
    {
        sal_Bool bVal(sal_False);

        if(! sd::any2bool( aValue, bVal ) )
            throw lang::IllegalArgumentException();

        pDoc->SetPresShowLogo( bVal );
    }
    }

    mrModel.SetModified();
}

uno::Any SAL_CALL SdXPresentation::getPropertyValue( const OUString& PropertyName )
    throw(beans::UnknownPropertyException, lang::WrappedTargetException, uno::RuntimeException)
{
    SolarMutexGuard aGuard;

    uno::Any any;

    SdDrawDocument* pDoc = mrModel.GetDoc();
    if(pDoc == NULL)
        throw uno::RuntimeException();

    const SfxItemPropertyMap* pMap = maPropSet.getPropertyMapEntry(PropertyName);

    switch( pMap ? pMap->nWID : -1 )
    {
    case ATTR_PRESENT_ALL:
        any <<= (sal_Bool) ( !pDoc->IsCustomShow() && pDoc->GetPresAll() );
        break;
    case ATTR_PRESENT_CHANGE_PAGE:
        sd::bool2any( !pDoc->GetPresLockedPages(), any );
        break;
    case ATTR_PRESENT_ANIMATION_ALLOWED:
        sd::bool2any( pDoc->IsAnimationAllowed(), any );
        break;
    case ATTR_PRESENT_CUSTOMSHOW:
    {
        List* pList = pDoc->GetCustomShowList(sal_False);
        SdCustomShow* pShow = (pList && pDoc->IsCustomShow())?(SdCustomShow*)pList->GetCurObject():NULL;
        OUString aShowName;

        if(pShow)
            aShowName = pShow->GetName();

        any <<= aShowName;
        break;
    }
    case ATTR_PRESENT_ENDLESS:
        sd::bool2any( pDoc->GetPresEndless(), any );
        break;
    case ATTR_PRESENT_FULLSCREEN:
        sd::bool2any( pDoc->GetPresFullScreen(), any );
        break;
    case ATTR_PRESENT_DIANAME:
        {
            OUString aSlideName;

            if( !pDoc->IsCustomShow() && !pDoc->GetPresAll() )
                aSlideName = SdDrawPage::getPageApiNameFromUiName( pDoc->GetPresPage() );

            any <<= aSlideName;
        }
        break;
    case ATTR_PRESENT_MANUEL:
        sd::bool2any( pDoc->GetPresManual(), any );
        break;
    case ATTR_PRESENT_MOUSE:
        sd::bool2any( pDoc->GetPresMouseVisible(), any );
        break;
    case ATTR_PRESENT_ALWAYS_ON_TOP:
        sd::bool2any( pDoc->GetPresAlwaysOnTop(), any );
        break;
    case ATTR_PRESENT_NAVIGATOR:
        sd::bool2any( pDoc->GetStartPresWithNavigator(), any );
        break;
    case ATTR_PRESENT_PEN:
        sd::bool2any( pDoc->GetPresMouseAsPen(), any );
        break;
    case ATTR_PRESENT_PAUSE_TIMEOUT:
        any <<= (sal_Int32)pDoc->GetPresPause();
        break;
    case ATTR_PRESENT_SHOW_PAUSELOGO:
        sd::bool2any( pDoc->IsPresShowLogo(), any );
        break;
    }

    return any;
}

void SAL_CALL SdXPresentation::addPropertyChangeListener( const OUString& /*aPropertyName*/, const uno::Reference< beans::XPropertyChangeListener >& /*xListener*/ )    throw(beans::UnknownPropertyException, lang::WrappedTargetException, uno::RuntimeException)
{
}

void SAL_CALL SdXPresentation::removePropertyChangeListener( const OUString& /*aPropertyName*/, const uno::Reference< beans::XPropertyChangeListener >& /*aListener*/ ) throw(beans::UnknownPropertyException, lang::WrappedTargetException, uno::RuntimeException)
{
}

void SAL_CALL SdXPresentation::addVetoableChangeListener( const OUString& /*PropertyName*/, const uno::Reference< beans::XVetoableChangeListener >& /*aListener*/ ) throw(beans::UnknownPropertyException, lang::WrappedTargetException, uno::RuntimeException)
{
}

void SAL_CALL SdXPresentation::removeVetoableChangeListener( const OUString& /*PropertyName*/, const uno::Reference< beans::XVetoableChangeListener >& /*aListener*/ )  throw(beans::UnknownPropertyException, lang::WrappedTargetException, uno::RuntimeException)
{
}

// XPresentation
void SAL_CALL SdXPresentation::start(  ) throw(uno::RuntimeException)
{
}

void SAL_CALL SdXPresentation::end(  ) throw(uno::RuntimeException)
{
}

void SAL_CALL SdXPresentation::rehearseTimings(  ) throw(uno::RuntimeException)
{
}


}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
