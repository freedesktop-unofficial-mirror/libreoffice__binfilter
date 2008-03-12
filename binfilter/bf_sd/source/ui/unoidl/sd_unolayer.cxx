/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sd_unolayer.cxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 07:52:18 $
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

#ifdef _MSC_VER
#pragma hdrstop
#endif

#include <rtl/uuid.h>

#include <bf_sd/drawdoc.hxx>
#include <bf_svx/svdpagv.hxx>
#include <bf_svx/unoshape.hxx>

#include "bf_sd/docshell.hxx"

#include <drawdoc.hxx>
#include <unolayer.hxx>
#include "unoprnms.hxx"

#include "unohelp.hxx"
#include "frmview.hxx"

#include "strings.hrc"
#include "sdresid.hxx"
#include "glob.hrc"

#include "unokywds.hxx"
#include "unowcntr.hxx"

namespace binfilter {

using namespace ::rtl;
using namespace ::vos;
using namespace ::com::sun::star;

#define WID_LAYER_LOCKED    1
#define WID_LAYER_PRINTABLE 2
#define WID_LAYER_VISIBLE   3
#define WID_LAYER_NAME      4

const SfxItemPropertyMap* ImplGetSdLayerPropertyMap()
{
    static const SfxItemPropertyMap aSdLayerPropertyMap_Impl[] =
    {
        { MAP_CHAR_LEN(UNO_NAME_LAYER_LOCKED),      WID_LAYER_LOCKED,   &::getBooleanCppuType(),            0, 0 },
        { MAP_CHAR_LEN(UNO_NAME_LAYER_PRINTABLE),   WID_LAYER_PRINTABLE,&::getBooleanCppuType(),            0, 0 },
        { MAP_CHAR_LEN(UNO_NAME_LAYER_VISIBLE),     WID_LAYER_VISIBLE,  &::getBooleanCppuType(),            0, 0 },
        { MAP_CHAR_LEN(UNO_NAME_LAYER_NAME),        WID_LAYER_NAME,     &::getCppuType((const OUString*)0), 0, 0 },
        { 0,0,0,0,0}
    };

    return aSdLayerPropertyMap_Impl;
}

String SdLayer::convertToInternalName( const OUString& rName )
{
    if( rName.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM(sUNO_LayerName_background) ) )
    {
        return String( RTL_CONSTASCII_USTRINGPARAM( "LAYER_BCKGRND" ));
    }
    else if( rName.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM(sUNO_LayerName_background_objects) ) )
    {
        return String( RTL_CONSTASCII_USTRINGPARAM( "LAYER_BACKGRNDOBJ" ));
    }
    else if( rName.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM(sUNO_LayerName_layout) ) )
    {
        return  String( RTL_CONSTASCII_USTRINGPARAM( "LAYER_LAYOUT" ));
    }
    else if( rName.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM(sUNO_LayerName_controls) ) )
    {
        return String( RTL_CONSTASCII_USTRINGPARAM( "LAYER_CONTROLS" ));
    }
    else if( rName.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM(sUNO_LayerName_measurelines) ) )
    {
        return String( RTL_CONSTASCII_USTRINGPARAM( "LAYER_MEASURELINES" ));
    }
    else
    {
        return String( rName );
    }
}

OUString SdLayer::convertToExternalName( const String& rName )
{
    const String aCompare( rName );
    if( rName == String( RTL_CONSTASCII_USTRINGPARAM( "LAYER_BCKGRND" )) )
    {
        return OUString( RTL_CONSTASCII_USTRINGPARAM(sUNO_LayerName_background) );
    }
    else if( rName == String( RTL_CONSTASCII_USTRINGPARAM( "LAYER_BACKGRNDOBJ" )) )
    {
        return OUString( RTL_CONSTASCII_USTRINGPARAM(sUNO_LayerName_background_objects) );
    }
    else if( rName == String( RTL_CONSTASCII_USTRINGPARAM( "LAYER_LAYOUT" )) )
    {
        return OUString( RTL_CONSTASCII_USTRINGPARAM(sUNO_LayerName_layout) );
    }
    else if( rName == String( RTL_CONSTASCII_USTRINGPARAM( "LAYER_CONTROLS" )) )
    {
        return OUString( RTL_CONSTASCII_USTRINGPARAM(sUNO_LayerName_controls) );
    }
    else if( rName == String( RTL_CONSTASCII_USTRINGPARAM( "LAYER_MEASURELINES" )) )
    {
        return OUString( RTL_CONSTASCII_USTRINGPARAM(sUNO_LayerName_measurelines) );
    }
    else
    {
        return OUString( rName );
    }
}

/** */
SdLayer::SdLayer( SdLayerManager* pLayerManager_, SdrLayer* pSdrLayer_ ) throw()
: aPropSet(ImplGetSdLayerPropertyMap()),
  pLayerManager(pLayerManager_), pLayer(pSdrLayer_),
  mxLayerManager(pLayerManager_)
{
}

SdLayer::~SdLayer() throw()
{
}

UNO3_GETIMPLEMENTATION_IMPL( SdLayer );

OUString SAL_CALL SdLayer::getImplementationName()
    throw(uno::RuntimeException)
{
    return OUString( OUString::createFromAscii(sUNO_SdLayer) );
}

sal_Bool SAL_CALL SdLayer::supportsService( const OUString& ServiceName )
    throw(uno::RuntimeException)
{
    return SvxServiceInfoHelper::supportsService( ServiceName, getSupportedServiceNames() );
}

uno::Sequence< OUString > SAL_CALL SdLayer::getSupportedServiceNames()
    throw(uno::RuntimeException)
{
    OUString aServiceName( OUString::createFromAscii(sUNO_Service_DrawingLayer) );
    uno::Sequence< OUString > aSeq( &aServiceName, 1 );
    return aSeq;
}

// beans::XPropertySet
uno::Reference< beans::XPropertySetInfo > SAL_CALL SdLayer::getPropertySetInfo(  )
    throw(uno::RuntimeException)
{
    OGuard aGuard( Application::GetSolarMutex() );
    return aPropSet.getPropertySetInfo();
}

void SAL_CALL SdLayer::setPropertyValue( const OUString& aPropertyName, const uno::Any& aValue )
    throw(beans::UnknownPropertyException, beans::PropertyVetoException, lang::IllegalArgumentException, lang::WrappedTargetException, uno::RuntimeException)
{
    OGuard aGuard( Application::GetSolarMutex() );

    if(pLayer == NULL || pLayerManager == NULL)
        throw uno::RuntimeException();

    const SfxItemPropertyMap* pMap = aPropSet.getPropertyMapEntry(aPropertyName);

    switch( pMap ? pMap->nWID : -1 )
    {
    case WID_LAYER_LOCKED:
    {
        sal_Bool bValue;
        if(!sd::any2bool( aValue, bValue ))
            throw lang::IllegalArgumentException();
        set( LOCKED, bValue );
        break;
    }
    case WID_LAYER_PRINTABLE:
    {
        sal_Bool bValue;
        if(!sd::any2bool( aValue, bValue ))
            throw lang::IllegalArgumentException();
        set( PRINTABLE, bValue );
        break;
    }
    case WID_LAYER_VISIBLE:
    {
        sal_Bool bValue;
        if(!sd::any2bool( aValue, bValue ))
            throw lang::IllegalArgumentException();
        set( VISIBLE, bValue );
        break;
    }
    case WID_LAYER_NAME:
    {
        OUString aName;
        if(!(aValue >>= aName))
            throw lang::IllegalArgumentException();

        pLayer->SetName(SdLayer::convertToInternalName( aName ) );
        break;
    }
    default:
        throw beans::UnknownPropertyException();
        break;
    }
}

uno::Any SAL_CALL SdLayer::getPropertyValue( const OUString& PropertyName )
    throw(beans::UnknownPropertyException, lang::WrappedTargetException, uno::RuntimeException)
{
    OGuard aGuard( Application::GetSolarMutex() );

    if(pLayer == NULL || pLayerManager == NULL)
        throw uno::RuntimeException();

    const SfxItemPropertyMap* pMap = aPropSet.getPropertyMapEntry(PropertyName);

    uno::Any aValue;

    switch( pMap ? pMap->nWID : -1 )
    {
    case WID_LAYER_LOCKED:
        sd::bool2any( get( LOCKED ), aValue );
        break;
    case WID_LAYER_PRINTABLE:
        sd::bool2any( get( PRINTABLE ), aValue );
        break;
    case WID_LAYER_VISIBLE:
        sd::bool2any( get( VISIBLE ), aValue );
        break;
    case WID_LAYER_NAME:
    {
        OUString aRet( SdLayer::convertToExternalName( pLayer->GetName() ) );
        aValue <<= aRet;
        break;
    }
    default:
        throw beans::UnknownPropertyException();
        break;
    }

    return aValue;
}

void SAL_CALL SdLayer::addPropertyChangeListener( const OUString& aPropertyName, const uno::Reference< beans::XPropertyChangeListener >& xListener ) throw(beans::UnknownPropertyException, lang::WrappedTargetException, uno::RuntimeException) {}
void SAL_CALL SdLayer::removePropertyChangeListener( const OUString& aPropertyName, const uno::Reference< beans::XPropertyChangeListener >& aListener ) throw(beans::UnknownPropertyException, lang::WrappedTargetException, uno::RuntimeException) {}
void SAL_CALL SdLayer::addVetoableChangeListener( const OUString& PropertyName, const uno::Reference< beans::XVetoableChangeListener >& aListener ) throw(beans::UnknownPropertyException, lang::WrappedTargetException, uno::RuntimeException) {}
void SAL_CALL SdLayer::removeVetoableChangeListener( const OUString& PropertyName, const uno::Reference< beans::XVetoableChangeListener >& aListener ) throw(beans::UnknownPropertyException, lang::WrappedTargetException, uno::RuntimeException) {}

/** */
sal_Bool SdLayer::get( LayerAttribute what ) throw()
{
    if(pLayer&&pLayerManager&&pLayerManager->rModel.GetDoc() )
    {
        List* pFrameViewList = pLayerManager->rModel.GetDoc()->GetFrameViewList();
        if( pFrameViewList && pFrameViewList->Count() )
        {
            FrameView* pFrameView = (FrameView*) pFrameViewList->GetObject(0);

            if( pFrameView )
            {
                SdrLayerAdmin& rLayerAdmin = pLayerManager->rModel.GetDoc()->GetLayerAdmin();
                BYTE id = rLayerAdmin.GetLayerID(pLayer->GetName(), sal_False);

                switch(what)
                {
                case VISIBLE:   return pFrameView->GetVisibleLayers().IsSet(id);
                case PRINTABLE: return pFrameView->GetPrintableLayers().IsSet(id);
                case LOCKED:    return pFrameView->GetLockedLayers().IsSet(id);
                }
            }
        }
    }
    return sal_False;
}

void SdLayer::set( LayerAttribute what, sal_Bool flag ) throw()
{
    if(pLayer&&pLayerManager&&pLayerManager->rModel.GetDoc() )
    {
        List* pFrameViewList = pLayerManager->rModel.GetDoc()->GetFrameViewList();
        if( pFrameViewList && pFrameViewList->Count() )
        {
            FrameView* pFrameView = (FrameView*) pFrameViewList->GetObject(0);

            if( pFrameView )
            {
                SdrLayerAdmin& rLayerAdmin = pLayerManager->rModel.GetDoc()->GetLayerAdmin();
                BYTE id = rLayerAdmin.GetLayerID(pLayer->GetName(), sal_False);

                SetOfByte aSet;
                switch(what)
                {
                case VISIBLE:   aSet = pFrameView->GetVisibleLayers(); break;
                case PRINTABLE: aSet = pFrameView->GetPrintableLayers(); break;
                case LOCKED:    aSet = pFrameView->GetLockedLayers(); break;
                }

                aSet.Set(id,flag);

                switch(what)
                {
                case VISIBLE:   pFrameView->SetVisibleLayers(aSet); break;
                case PRINTABLE: pFrameView->SetPrintableLayers(aSet); break;
                case LOCKED:    pFrameView->SetLockedLayers(aSet); break;
                }
            }
        }
    }
}




//=====  ::com::sun::star::container::XChild  =================================

uno::Reference<uno::XInterface> SAL_CALL SdLayer::getParent (void)
    throw (::com::sun::star::uno::RuntimeException)
{
    return uno::Reference<uno::XInterface> (mxLayerManager, uno::UNO_QUERY);
}


void SAL_CALL SdLayer::setParent (const uno::Reference<uno::XInterface >& rxParent)
    throw (::com::sun::star::lang::NoSupportException,
        ::com::sun::star::uno::RuntimeException)
{
    throw lang::NoSupportException ();
}




//=============================================================================
// class SdLayerManager
//=============================================================================

/** */
SdLayerManager::SdLayerManager( SdXImpressDocument& rMyModel ) throw()
:rModel(rMyModel)
{
    mpLayers = new SvUnoWeakContainer;
}

/** */
SdLayerManager::~SdLayerManager() throw()
{
    delete mpLayers;
}

// uno helper
UNO3_GETIMPLEMENTATION_IMPL( SdLayerManager );

// XServiceInfo
OUString SAL_CALL SdLayerManager::getImplementationName()
    throw(uno::RuntimeException)
{
    return OUString( OUString::createFromAscii(sUNO_SdLayerManager) );
}

sal_Bool SAL_CALL SdLayerManager::supportsService( const OUString& ServiceName )
    throw(uno::RuntimeException)
{
    return SvxServiceInfoHelper::supportsService( ServiceName, getSupportedServiceNames() );
}

uno::Sequence< OUString > SAL_CALL SdLayerManager::getSupportedServiceNames()
    throw(uno::RuntimeException)
{
    OUString aServiceName( OUString::createFromAscii(sUNO_Service_DrawingLayerManager) );
    uno::Sequence< OUString > aSeq( &aServiceName, 1 );
    return aSeq;
}

// XLayerManager
uno::Reference< drawing::XLayer > SAL_CALL SdLayerManager::insertNewByIndex( sal_Int32 nIndex )
    throw(uno::RuntimeException)
{
    OGuard aGuard( Application::GetSolarMutex() );

    uno::Reference< drawing::XLayer > xLayer;

    if( rModel.pDoc )
    {
        SdrLayerAdmin& rLayerAdmin = rModel.pDoc->GetLayerAdmin();
        sal_uInt16 nLayerCnt = rLayerAdmin.GetLayerCount();
        sal_uInt16 nLayer = nLayerCnt - 2 + 1;
        String aLayerName;

        // Ueberpruefung auf schon vorhandene Namen
        while( aLayerName.Len()==0 || rLayerAdmin.GetLayer( aLayerName, sal_False) )
        {
            aLayerName = String(SdResId(STR_LAYER));
            aLayerName += String::CreateFromInt32( (sal_Int32)nLayer );
            nLayer++;
        }

        SdrLayerAdmin& rLA=rModel.pDoc->GetLayerAdmin();
        const sal_Int32 nMax=rLA.GetLayerCount();
        if (nIndex>nMax) nIndex=nMax;
        xLayer = GetLayer (rLA.NewLayer(aLayerName,(USHORT)nIndex));
        rModel.SetModified();
    }
    return xLayer;
}

void SAL_CALL SdLayerManager::remove( const uno::Reference< drawing::XLayer >& xLayer ) throw(container::NoSuchElementException, uno::RuntimeException)
{
}

void SAL_CALL SdLayerManager::attachShapeToLayer( const uno::Reference< drawing::XShape >& xShape, const uno::Reference< drawing::XLayer >& xLayer )
    throw(uno::RuntimeException)
{
    OGuard aGuard( Application::GetSolarMutex() );

    if(rModel.pDoc==NULL)
        return;

    SdLayer* pSdLayer = SdLayer::getImplementation(xLayer);
    SdrLayer* pSdrLayer = pSdLayer?pSdLayer->GetSdrLayer():NULL;
    if(pSdrLayer==NULL)
        return;

    SvxShape* pShape = SvxShape::getImplementation( xShape );
    SdrObject* pSdrObject = pShape?pShape->GetSdrObject():NULL;

    if(pSdrObject && pSdrLayer )
        pSdrObject->SetLayer(pSdrLayer->GetID());

    rModel.SetModified();
}

uno::Reference< drawing::XLayer > SAL_CALL SdLayerManager::getLayerForShape( const uno::Reference< drawing::XShape >& xShape ) throw(uno::RuntimeException)
{
    OGuard aGuard( Application::GetSolarMutex() );

    uno::Reference< drawing::XLayer >  xLayer;

    if(rModel.pDoc)
    {
        SvxShape* pShape = SvxShape::getImplementation( xShape );
        SdrObject* pObj = pShape?pShape->GetSdrObject():NULL;
        if(pObj)
        {
            SdrLayerID aId = pObj->GetLayer();
            SdrLayerAdmin& rLayerAdmin = rModel.pDoc->GetLayerAdmin();
            xLayer = GetLayer (rLayerAdmin.GetLayerPerID(aId));
        }
    }
    return xLayer;
}

// XIndexAccess
sal_Int32 SAL_CALL SdLayerManager::getCount()
    throw(uno::RuntimeException)
{
    OGuard aGuard( Application::GetSolarMutex() );

    if( rModel.pDoc )
    {
        SdrLayerAdmin& rLayerAdmin = rModel.pDoc->GetLayerAdmin();
        return rLayerAdmin.GetLayerCount();
    }

    return 0;
}

uno::Any SAL_CALL SdLayerManager::getByIndex( sal_Int32 nLayer )
    throw(lang::IndexOutOfBoundsException, lang::WrappedTargetException, uno::RuntimeException)
{
    OGuard aGuard( Application::GetSolarMutex() );

    if( nLayer >= getCount() || nLayer < 0 )
        throw lang::IndexOutOfBoundsException();

    uno::Any aAny;

    if( rModel.pDoc )
    {
        SdrLayerAdmin& rLayerAdmin = rModel.pDoc->GetLayerAdmin();
        uno::Reference<drawing::XLayer> xLayer (GetLayer (rLayerAdmin.GetLayer((sal_uInt16)nLayer)));
        aAny <<= xLayer;
    }
    return aAny;
}


// XNameAccess
uno::Any SAL_CALL SdLayerManager::getByName( const OUString& aName )
    throw(container::NoSuchElementException, lang::WrappedTargetException, uno::RuntimeException)
{
    OGuard aGuard( Application::GetSolarMutex() );

    uno::Reference< drawing::XLayer >  xLayer;

    uno::Any aAny;

    if( rModel.pDoc )
    {
        SdrLayerAdmin& rLayerAdmin = rModel.pDoc->GetLayerAdmin();
        SdrLayer* pLayer = rLayerAdmin.GetLayer( SdLayer::convertToInternalName( aName ), FALSE );
        if( pLayer == NULL )
            throw container::NoSuchElementException();

        xLayer = GetLayer (pLayer);
        aAny <<= xLayer;
        return aAny;
    }

    throw container::NoSuchElementException();
    return aAny;
}

uno::Sequence< OUString > SAL_CALL SdLayerManager::getElementNames()
    throw(uno::RuntimeException)
{
    OGuard aGuard( Application::GetSolarMutex() );

    SdrLayerAdmin& rLayerAdmin = rModel.pDoc->GetLayerAdmin();
    const sal_uInt16 nLayerCount = rLayerAdmin.GetLayerCount();

    uno::Sequence< OUString > aSeq( nLayerCount );

    OUString* pStrings = aSeq.getArray();
    SdrLayer* pLayer;

    for( sal_uInt16 nLayer = 0; nLayer < nLayerCount; nLayer++ )
    {
        pLayer = rLayerAdmin.GetLayer( nLayer );
        if( pLayer )
            *pStrings++ = SdLayer::convertToExternalName( pLayer->GetName() );
    }

    return aSeq;
}

sal_Bool SAL_CALL SdLayerManager::hasByName( const OUString& aName ) throw(uno::RuntimeException)
{
    OGuard aGuard( Application::GetSolarMutex() );

    SdrLayerAdmin& rLayerAdmin = rModel.pDoc->GetLayerAdmin();

    return NULL != rLayerAdmin.GetLayer( SdLayer::convertToInternalName( aName ), FALSE );
}

// XElementAccess
uno::Type SAL_CALL SdLayerManager::getElementType()
    throw(uno::RuntimeException)
{
    return ITYPE( drawing::XLayer );
}

sal_Bool SAL_CALL SdLayerManager::hasElements() throw(uno::RuntimeException)
{
    return getCount() > 0;
}


namespace
{
/** Compare two pointers to <type>SdrLayer</type> objects.
    @param xRef
        The implementing SdLayer class provides the first pointer by the
        <member>SdLayer::GetSdrLayer</member> method.
    @param pSearchData
        This void pointer is the second pointer to an <type>SdrLayer</type>
        object.
    @return
        Return </True> if both pointers point to the same object.
*/
sal_Bool compare_layers (uno::WeakReference<uno::XInterface> xRef, void* pSearchData)
{
    uno::Reference<uno::XInterface> xLayer (xRef);
    if (xLayer.is())
    {
        SdLayer* pSdLayer = SdLayer::getImplementation (xRef);
        if (pSdLayer != NULL)
        {
            SdrLayer* pSdrLayer = pSdLayer->GetSdrLayer ();
            if (pSdrLayer == static_cast<SdrLayer*>(pSearchData))
                return sal_True;
        }
    }
    return sal_False;
}
}

uno::Reference<drawing::XLayer> SdLayerManager::GetLayer (SdrLayer* pLayer)
{
    uno::WeakReference<uno::XInterface> xRef;
    uno::Reference<drawing::XLayer>  xLayer;

    // Search existing xLayer for the given pLayer.
    if (mpLayers->findRef (xRef, (void*)pLayer, compare_layers))
        xLayer = uno::Reference<drawing::XLayer> (xRef, uno::UNO_QUERY);

    // Create the xLayer if necessary.
    if ( ! xLayer.is())
    {
        xLayer = new SdLayer (this, pLayer);

        // Remember the new xLayer for future calls.
        xRef = uno::Reference<uno::XInterface> (xLayer, uno::UNO_QUERY);
        mpLayers->insert (xRef);
    }

    return xLayer;
}

}
