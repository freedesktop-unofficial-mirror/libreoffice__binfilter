/*************************************************************************
 *
 *  $RCSfile: sd_unopres.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 14:08:14 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/

// auto strip #ifndef _COM_SUN_STAR_PRESENTATION_XPRESENTATIONPAGE_HPP_
// auto strip #include <com/sun/star/presentation/XPresentationPage.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_PRESENTATION_XPRESENTATIONSUPPLIER_HPP_
// auto strip #include <com/sun/star/presentation/XPresentationSupplier.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_PRESENTATION_XPRESENTATION_HPP_
// auto strip #include <com/sun/star/presentation/XPresentation.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_PRESENTATION_XCUSTOMPRESENTATIONSUPPLIER_HPP_
// auto strip #include <com/sun/star/presentation/XCustomPresentationSupplier.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_PRESENTATION_CLICKACTION_HPP_
// auto strip #include <com/sun/star/presentation/ClickAction.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_PRESENTATION_FADEEFFECT_HPP_
// auto strip #include <com/sun/star/presentation/FadeEffect.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_PRESENTATION_ANIMATIONEFFECT_HPP_
// auto strip #include <com/sun/star/presentation/AnimationEffect.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_PRESENTATION_PRESENTATIONRANGE_HPP_
// auto strip #include <com/sun/star/presentation/PresentationRange.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_PRESENTATION_ANIMATIONSPEED_HPP_
// auto strip #include <com/sun/star/presentation/AnimationSpeed.hpp>
// auto strip #endif

// auto strip #ifndef _VOS_MUTEX_HXX_ //autogen
// auto strip #include <vos/mutex.hxx>
// auto strip #endif

// auto strip #ifndef _SFX_ITEMPROP_HXX
// auto strip #include <svtools/itemprop.hxx>
// auto strip #endif

#include <bf_sfx2/dispatch.hxx>

#include <bf_svx/dialogs.hrc>              // fuer SID_REHEARSE_TIMINGS
#include <bf_svx/unoprov.hxx>

// auto strip #include "drawdoc.hxx"
// auto strip #include "unomodel.hxx"
#include "unopres.hxx"
#include "unocpres.hxx"
#include "app.hrc"                      // SID_LIVE_PRESENTATION
#include "viewshel.hxx"
// auto strip #include "drawview.hxx"
#ifndef SVX_LIGHT
#include "docshell.hxx"
#endif
#include "fuslshow.hxx"
#include "sdattr.hxx"
#include "cusshow.hxx"
#include "unoprnms.hxx"
#include "unohelp.hxx"
#include "unopage.hxx"
namespace binfilter {

using namespace ::rtl;
using namespace ::cppu;
using namespace ::vos;
using namespace ::com::sun::star;

const SfxItemPropertyMap* ImplGetPresentationPropertyMap()
{
    // [ACHTUNG] Erster Parameter muss sortiert vorliegen
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
        { MAP_CHAR_LEN(UNO_NAME_SHOW_LIVEMODUS),    SID_LIVE_PRESENTATION,          &::getBooleanCppuType(),                0, 0 },
        { MAP_CHAR_LEN(UNO_NAME_SHOW_MOUSEVISIBLE),ATTR_PRESENT_MOUSE,              &::getBooleanCppuType(),                0, 0 },
        { MAP_CHAR_LEN(UNO_NAME_SHOW_PAUSE),        ATTR_PRESENT_PAUSE_TIMEOUT,     &::getCppuType((const sal_Int32*)0),    0, 0 },
        { MAP_CHAR_LEN(UNO_NAME_SHOW_STARTWITHNAV),ATTR_PRESENT_NAVIGATOR,          &::getBooleanCppuType(),                0, 0 },
        { MAP_CHAR_LEN(UNO_NAME_SHOW_USEPEN),       ATTR_PRESENT_PEN,               &::getBooleanCppuType(),                0, 0 },
        { MAP_CHAR_LEN("IsTransitionOnClick"),      ATTR_PRESENT_CHANGE_PAGE,       &::getBooleanCppuType(),                0, 0 },
        { MAP_CHAR_LEN("IsShowLogo"),               ATTR_PRESENT_SHOW_PAUSELOGO,    &::getBooleanCppuType(),                0, 0 },
        { 0,0,0,0,0}

    };

    return aPresentationPropertyMap_Impl;
}

SfxItemPropertyMap map_impl[] = { 0,0,0,0 };

///////////////////////////////////////////////////////////////////////////////

SdXPresentation::SdXPresentation(SdXImpressDocument& rMyModel) throw()
:   maPropSet(ImplGetPresentationPropertyMap()), mrModel(rMyModel)
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
    OGuard aGuard( Application::GetSolarMutex() );
    return maPropSet.getPropertySetInfo();
 }

void SAL_CALL SdXPresentation::setPropertyValue( const OUString& aPropertyName, const uno::Any& aValue )
    throw(beans::UnknownPropertyException, beans::PropertyVetoException, lang::IllegalArgumentException, lang::WrappedTargetException, uno::RuntimeException)
{
    OGuard aGuard( Application::GetSolarMutex() );

    SdDrawDocument* pDoc = mrModel.GetDoc();
    if(pDoc == NULL)
        throw uno::RuntimeException();

    const SfxItemPropertyMap* pMap = maPropSet.getPropertyMapEntry(aPropertyName);

    sal_Bool bValuesChanged = sal_False;

    switch( pMap ? pMap->nWID : -1 )
    {
    case ATTR_PRESENT_ALL:
    {
        sal_Bool bVal;

        if(! sd::any2bool( aValue, bVal ) )
            throw lang::IllegalArgumentException();

        if( pDoc->GetPresAll() != bVal )
        {
            pDoc->SetPresAll( bVal );
            bValuesChanged = sal_True;
            if( bVal )
                pDoc->SetCustomShow( false );
        }
        break;
    }
    case ATTR_PRESENT_CHANGE_PAGE:
    {
        sal_Bool bVal;

        if(! sd::any2bool( aValue, bVal ) )
            throw lang::IllegalArgumentException();

        if ( bVal == pDoc->GetPresLockedPages() )
        {
            bValuesChanged = sal_True;
            pDoc->SetPresLockedPages( !bVal );
        }
        break;
    }

    case ATTR_PRESENT_ANIMATION_ALLOWED:
    {
        sal_Bool bVal;

        if(! sd::any2bool( aValue, bVal ) )
            throw lang::IllegalArgumentException();

        if(pDoc->IsAnimationAllowed() != bVal)
        {
            bValuesChanged = sal_True;
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
            bValuesChanged = sal_True;
        }
        break;
    }
    case ATTR_PRESENT_ENDLESS:
    {
        sal_Bool bVal;

        if(! sd::any2bool( aValue, bVal ) )
            throw lang::IllegalArgumentException();

        if(pDoc->GetPresEndless() != bVal)
        {
            bValuesChanged = sal_True;
            pDoc->SetPresEndless(bVal);
        }
        break;
    }
    case ATTR_PRESENT_FULLSCREEN:
    {
        sal_Bool bVal;

        if(! sd::any2bool( aValue, bVal ) )
            throw lang::IllegalArgumentException();

        if(pDoc->GetPresFullScreen() != bVal)
        {
            bValuesChanged = sal_True;
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

        bValuesChanged = sal_True;
        break;
    }
    case SID_LIVE_PRESENTATION:
    {
#ifndef SVX_LIGHT
        SdDrawDocShell* pDocSh = mrModel.GetDocShell();
        SdViewShell* pViewSh = pDocSh?pDocSh->GetViewShell():NULL;
        FuSlideShow* pFuSlideShow = pViewSh?pViewSh->GetSlideShow():NULL;

        if(pFuSlideShow != NULL)
        {
            sal_Bool bVal;

            if(! sd::any2bool( aValue, bVal ) )
                throw lang::IllegalArgumentException();

            if(pFuSlideShow->IsLivePresentation() != bVal)
            {
                ( pViewSh ? pViewSh->GetViewFrame() : SfxViewFrame::Current() )->GetDispatcher()->Execute(
                    SID_LIVE_PRESENTATION, SFX_CALLMODE_SYNCHRON | SFX_CALLMODE_RECORD );
                bValuesChanged = sal_True;
            }
        }
#endif
        break;
    }
    case ATTR_PRESENT_MANUEL:
    {
        sal_Bool bVal;

        if(! sd::any2bool( aValue, bVal ) )
            throw lang::IllegalArgumentException();

        if(pDoc->GetPresManual() != bVal)
        {
            bValuesChanged = sal_True;
            pDoc->SetPresManual(bVal);
        }
        break;
    }
    case ATTR_PRESENT_MOUSE:
    {
        sal_Bool bVal;

        if(! sd::any2bool( aValue, bVal ) )
            throw lang::IllegalArgumentException();

        if(pDoc->GetPresMouseVisible() != bVal)
        {
            bValuesChanged = sal_True;
            pDoc->SetPresMouseVisible(bVal);
        }
        break;
    }
    case ATTR_PRESENT_ALWAYS_ON_TOP:
    {
        sal_Bool bVal;

        if(! sd::any2bool( aValue, bVal ) )
            throw lang::IllegalArgumentException();

        if(pDoc->GetPresAlwaysOnTop() != bVal)
        {
            bValuesChanged = sal_True;
            pDoc->SetPresAlwaysOnTop(bVal);
        }
        break;
    }
    case ATTR_PRESENT_NAVIGATOR:
    {
        sal_Bool bVal;

        if(! sd::any2bool( aValue, bVal ) )
            throw lang::IllegalArgumentException();

        if(pDoc->GetStartPresWithNavigator() != bVal)
        {
            bValuesChanged = sal_True;
            pDoc->SetStartPresWithNavigator(bVal);
        }
        break;
    }
    case ATTR_PRESENT_PEN:
    {
        sal_Bool bVal;

        if(! sd::any2bool( aValue, bVal ) )
            throw lang::IllegalArgumentException();

        if(pDoc->GetPresMouseAsPen() != bVal)
        {
            bValuesChanged = sal_True;
            pDoc->SetPresMouseAsPen(bVal);
        }
        break;
    }
    case ATTR_PRESENT_PAUSE_TIMEOUT:
    {
        sal_Int32 nValue;
        if(!(aValue >>= nValue) || (nValue < 0))
            throw lang::IllegalArgumentException();

        pDoc->SetPresPause( (sal_uInt32)nValue );
        break;
    }
    case ATTR_PRESENT_SHOW_PAUSELOGO:
    {
        sal_Bool bVal;

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
    OGuard aGuard( Application::GetSolarMutex() );

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
    case SID_LIVE_PRESENTATION:
    {
#ifndef SVX_LIGHT
        SdDrawDocShell* pDocSh = mrModel.GetDocShell();

        SdViewShell* pViewSh = pDocSh?pDocSh->GetViewShell():NULL;
        if(pViewSh != NULL)
        {
            FuSlideShow* pFuSlideShow = pViewSh->GetSlideShow();
            sd::bool2any( pFuSlideShow && pFuSlideShow->IsLivePresentation(), any );
        }
#endif
        break;
    }
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

void SAL_CALL SdXPresentation::addPropertyChangeListener( const OUString& aPropertyName, const uno::Reference< beans::XPropertyChangeListener >& xListener )
    throw(beans::UnknownPropertyException, lang::WrappedTargetException, uno::RuntimeException)
{
}

void SAL_CALL SdXPresentation::removePropertyChangeListener( const OUString& aPropertyName, const uno::Reference< beans::XPropertyChangeListener >& aListener )
    throw(beans::UnknownPropertyException, lang::WrappedTargetException, uno::RuntimeException)
{
}

void SAL_CALL SdXPresentation::addVetoableChangeListener( const OUString& PropertyName, const uno::Reference< beans::XVetoableChangeListener >& aListener )
    throw(beans::UnknownPropertyException, lang::WrappedTargetException, uno::RuntimeException)
{
}

void SAL_CALL SdXPresentation::removeVetoableChangeListener( const OUString& PropertyName, const uno::Reference< beans::XVetoableChangeListener >& aListener )
    throw(beans::UnknownPropertyException, lang::WrappedTargetException, uno::RuntimeException)
{
}

// XPresentation
void SAL_CALL SdXPresentation::start(  )
    throw(uno::RuntimeException)
{
    OGuard aGuard( Application::GetSolarMutex() );

#ifndef SVX_LIGHT
    SdDrawDocShell* pDocSh = mrModel.GetDocShell();
    SdViewShell* pViewSh = pDocSh?pDocSh->GetViewShell():NULL;
    FuSlideShow* pFuSlideShow = pViewSh?pViewSh->GetSlideShow():NULL;

    // nur starten wenn die Presentation noch nicht laeuft
    if(pFuSlideShow == NULL)
    {
        ( pViewSh ? pViewSh->GetViewFrame() : SfxViewFrame::Current() )->GetDispatcher()->Execute(
            SID_PRESENTATION, SFX_CALLMODE_SYNCHRON | SFX_CALLMODE_RECORD );
    }
#endif

}

void SAL_CALL SdXPresentation::end(  )
    throw(uno::RuntimeException)
{
    OGuard aGuard( Application::GetSolarMutex() );

#ifndef SVX_LIGHT
    SdDrawDocShell* pDocSh = mrModel.GetDocShell();
    SdViewShell* pViewSh = pDocSh?pDocSh->GetViewShell():NULL;
    FuSlideShow* pFuSlideShow = pViewSh?pViewSh->GetSlideShow():NULL;

    if(pFuSlideShow)
    {
        // Live modus verlassen!!
        if(pFuSlideShow->IsLivePresentation())
        {
            ( pViewSh ? pViewSh->GetViewFrame() : SfxViewFrame::Current() )->GetDispatcher()->Execute(
                SID_LIVE_PRESENTATION, SFX_CALLMODE_SYNCHRON | SFX_CALLMODE_RECORD );
        }
        pFuSlideShow->Terminate();
    }
#endif
}

void SAL_CALL SdXPresentation::rehearseTimings(  )
    throw(uno::RuntimeException)
{
    OGuard aGuard( Application::GetSolarMutex() );

#ifndef SVX_LIGHT
    SdDrawDocShell* pDocSh = mrModel.GetDocShell();
    SdViewShell* pViewSh = pDocSh?pDocSh->GetViewShell():NULL;

    ( pViewSh ? pViewSh->GetViewFrame() : SfxViewFrame::Current() )->GetDispatcher()->Execute(
        SID_REHEARSE_TIMINGS, SFX_CALLMODE_SYNCHRON | SFX_CALLMODE_RECORD );
#endif
}


}
