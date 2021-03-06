/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2000, 2010 Oracle and/or its affiliates.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/

#define _SVX_USE_UNOGLOBALS_

#include "svdoole2.hxx"

#include <bf_so3/outplace.hxx>

#ifndef SVX_LIGHT
#include <sot/clsids.hxx>
#ifndef _SFX_FRMDESCRHXX
#include <bf_sfx2/frmdescr.hxx>
#endif
#endif
#include <vcl/svapp.hxx>

#include "svdmodel.hxx"
#include "shapeimpl.hxx"

#include "unoshprp.hxx"

#include "svdstr.hrc"

#include <bf_sfx2/frameobj.hxx>

namespace binfilter {

///////////////////////////////////////////////////////////////////////

using namespace ::osl;
using namespace ::rtl;
using namespace ::cppu;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::beans;

///////////////////////////////////////////////////////////////////////

SvxOle2Shape::SvxOle2Shape( SdrObject* pObject, const SfxItemPropertyMap* pPropertySet ) throw ()
: SvxShape( pObject, pPropertySet  )
{
}

SvxOle2Shape::~SvxOle2Shape() throw()
{
}

::com::sun::star::uno::Any SAL_CALL SvxOle2Shape::queryAggregation( const ::com::sun::star::uno::Type & rType ) throw(::com::sun::star::uno::RuntimeException)
{
    Any aAny;
    SvxShape::tryQueryAggregation( rType, aAny );
    return aAny;
}

//XPropertySet
void SAL_CALL SvxOle2Shape::setPropertyValue( const OUString& aPropertyName, const Any& aValue )    throw( UnknownPropertyException, PropertyVetoException, IllegalArgumentException, WrappedTargetException, RuntimeException )
{
    ::SolarMutexGuard aGuard;

    if( aPropertyName.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( "CLSID" ) ) )
    {
#ifndef SVX_LIGHT
        OUString aCLSID;
        if( aValue >>= aCLSID )
        {
            // init a ole object with a global name
            if( pObj )
            {
                // to force creation of the corresponding stripped OLE, translate
                // wanted CLSID to BF_* CLSID.
                if(0L == aCLSID.compareTo(SvGlobalName(SO3_SW_CLASSID).GetHexName()))
                {
                    aCLSID = SvGlobalName(BF_SO3_SW_CLASSID).GetHexName();
                }
                else if(0L == aCLSID.compareTo(SvGlobalName(SO3_SWWEB_CLASSID).GetHexName()))
                {
                    aCLSID = SvGlobalName(BF_SO3_SWWEB_CLASSID).GetHexName();
                }
                else if(0L == aCLSID.compareTo(SvGlobalName(SO3_SC_CLASSID).GetHexName()))
                {
                    aCLSID = SvGlobalName(BF_SO3_SC_CLASSID).GetHexName();
                }
                else if(0L == aCLSID.compareTo(SvGlobalName(SO3_SDRAW_CLASSID).GetHexName()))
                {
                    aCLSID = SvGlobalName(BF_SO3_SDRAW_CLASSID).GetHexName();
                }
                else if(0L == aCLSID.compareTo(SvGlobalName(SO3_SIMPRESS_CLASSID).GetHexName()))
                {
                    aCLSID = SvGlobalName(BF_SO3_SIMPRESS_CLASSID).GetHexName();
                }
                else if(0L == aCLSID.compareTo(SvGlobalName(SO3_SCH_CLASSID).GetHexName()))
                {
                    aCLSID = SvGlobalName(BF_SO3_SCH_CLASSID).GetHexName();
                }
                else if(0L == aCLSID.compareTo(SvGlobalName(SO3_SM_CLASSID).GetHexName()))
                {
                    aCLSID = SvGlobalName(BF_SO3_SM_CLASSID).GetHexName();
                }

                SvGlobalName aClassName;
                if( aClassName.MakeId( aCLSID ) )
                {
                    if( createObject( aClassName ) )
                        return;
                }
            }
        }

        throw IllegalArgumentException();
#endif
    }
    else if( aPropertyName.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( "ThumbnailGraphicURL" ) ) )
    {
#ifndef SVX_LIGHT
        // only allow setting of thumbnail for player
        return;
#else
        OUString aURL;
        if( aValue >>= aURL )
        {
            SdrOle2Obj* pOle = PTR_CAST( SdrOle2Obj, pObj );
            if( pOle )
            {
                BfGraphicObject aGrafObj( CreateGraphicObjectFromURL( aURL ) );
                pOle->SetGraphic( &aGrafObj.GetGraphic() );
            }
            return;
        }

        throw IllegalArgumentException();
#endif
    }
    else if( aPropertyName.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( UNO_NAME_OLE2_PERSISTNAME ) ) )
    {
        OUString aPersistName;

        if( aValue >>= aPersistName )
        {
            SdrOle2Obj* pOle = PTR_CAST( SdrOle2Obj, pObj );

            if( pOle )
                pOle->SetPersistName( aPersistName );

            return;
        }

        throw IllegalArgumentException();
    }

    SvxShape::setPropertyValue( aPropertyName, aValue );
}

Any SAL_CALL SvxOle2Shape::getPropertyValue( const OUString& PropertyName ) throw( UnknownPropertyException, WrappedTargetException, RuntimeException)
{
    ::SolarMutexGuard aGuard;

    if( PropertyName.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( "ThumbnailGraphicURL" ) ) )
    {
        OUString    aURL;
        SdrOle2Obj* pOle = PTR_CAST( SdrOle2Obj, pObj );

        if( pOle )
        {
            Graphic* pGraphic = pOle->GetGraphic();

            if( pGraphic )
            {
                BfGraphicObject aObj( *pGraphic );
                aURL = OUString(RTL_CONSTASCII_USTRINGPARAM(UNO_NAME_GRAPHOBJ_URLPREFIX));
                aURL += OUString::createFromAscii( aObj.GetUniqueID().GetBuffer() );
            }
        }
        return makeAny( aURL );
    }
    else if( PropertyName.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( UNO_NAME_OLE2_PERSISTNAME ) ) )
    {
        OUString    aPersistName;
        SdrOle2Obj* pOle = PTR_CAST( SdrOle2Obj, pObj );

        if( pOle )
        {
            aPersistName = pOle->GetPersistName();
            if( aPersistName.getLength() )
            {
                SvPersist *pPersist = pObj->GetModel()->GetPersist();
                if( (NULL == pPersist) || ( NULL == pPersist->Find( static_cast< SdrOle2Obj* >( pObj )->GetPersistName() ) ) )
                    aPersistName = OUString();
            }
        }

        return makeAny( aPersistName );
    }

    return SvxShape::getPropertyValue( PropertyName );
}


sal_Bool SvxOle2Shape::createObject( const SvGlobalName &aClassName )
{
    const SvInPlaceObjectRef& rIPRef = static_cast< SdrOle2Obj* >( pObj )->GetObjRef();

    if( rIPRef.Is() )
        return sal_False;

    // create storage and inplace object
    String              aEmptyStr;
    SvStorageRef        aStor;
    const SotFactory* pFact = SvFactory::Find( aClassName );
    SvInPlaceObjectRef aIPObj;
    if ( pFact )
    {
        aStor = new SvStorage( aEmptyStr, STREAM_STD_READWRITE );
        aIPObj = &((SvFactory*)SvInPlaceObject::ClassFactory())->CreateAndInit( aClassName,aStor );
    }
    else
    {
        aStor = new SvStorage( FALSE, aEmptyStr, STREAM_STD_READWRITE );
        String aFileName;
        BOOL bOk;
        SvGlobalName aName( aClassName );
        aIPObj = SvOutPlaceObject::InsertObject( NULL, &aStor, bOk, aName, aFileName );
    }

    SvPersist*          pPersist = pModel->GetPersist();
    sal_Bool            bOk = sal_False;
    String              aPersistName;
    OUString            aTmpStr;
    Any                 aAny( getPropertyValue( OUString(RTL_CONSTASCII_USTRINGPARAM( UNO_NAME_OLE2_PERSISTNAME )) ) );

    if( aAny >>= aTmpStr )
        aPersistName = aTmpStr;

    // if we already have a shape name check if its a unique
    // storage name
    if( aPersistName.Len() && !pPersist->Find( aPersistName ) )
    {
        SvInfoObjectRef xSub = new SvEmbeddedInfoObject( aIPObj, aPersistName );
        bOk = pPersist->Move( xSub, aPersistName );
    }
    else
    {
        // generate a unique name
        String aStr( aPersistName = String( RTL_CONSTASCII_USTRINGPARAM("Object ") ) );

        // for-Schleife wegen Storage Bug 46033
        for( sal_uInt32 i = 1, n = 0; n < 100; n++ )
        {
            do
            {
                aStr = aPersistName;
                aStr += String::CreateFromInt32( i++ );
            }
            while( pPersist->Find( aStr ) );

            SvInfoObjectRef xSub( new SvEmbeddedInfoObject( aIPObj, aStr ) );

            if( pPersist->Move( xSub, aStr ) ) // Eigentuemer Uebergang
            {
                bOk = sal_True;
                aPersistName = aStr;
                break;
            }
        }
    }

    DBG_ASSERT( bOk, "could not create move ole stream!" );

    if( bOk )
    {
        aAny <<= ( aTmpStr = aPersistName );
        setPropertyValue( OUString(RTL_CONSTASCII_USTRINGPARAM( UNO_NAME_OLE2_PERSISTNAME )), aAny );
    }

    static_cast< SdrOle2Obj* >( pObj )->SetObjRef( aIPObj );
    Rectangle aRect = static_cast< SdrOle2Obj* >( pObj )->GetLogicRect();
    if ( aRect.GetWidth() == 100 && aRect.GetHeight() == 100 )
    {
        // default size
        aRect.SetSize( aIPObj->GetVisArea().GetSize() );
        static_cast< SdrOle2Obj* >( pObj )->SetLogicRect( aRect );
    }
    else
        aIPObj->SetVisAreaSize( static_cast< SdrOle2Obj* >( pObj )->GetLogicRect().GetSize() );
    return bOk;
}

///////////////////////////////////////////////////////////////////////

// the following code is currently not working in the player
#ifndef SVX_LIGHT

static sal_Bool SvxImplFillCommandList( const Sequence< PropertyValue >& aCommandSequence, SvCommandList& aNewCommands )
{
    const sal_Int32 nCount = aCommandSequence.getLength();

    String aCommand, aArg;
    OUString aApiArg;
    for( sal_Int32 nIndex = 0; nIndex < nCount; nIndex++ )
    {
        aCommand = aCommandSequence[nIndex].Name;

        if( !( aCommandSequence[nIndex].Value >>= aApiArg ) )
            return sal_False;

        aArg = aApiArg;
        aNewCommands.Append( aCommand, aArg );
    }

    return sal_True;
}

static void SvxImplFillCommandSequence( const SvCommandList& aCommands, Sequence< PropertyValue >& aCommandSequence )
{
    const sal_Int32 nCount = aCommands.Count();
    aCommandSequence.realloc( nCount );

    for( sal_Int32 nIndex = 0; nIndex < nCount; nIndex++ )
    {
        const SvCommand& rCommand = aCommands[ nIndex ];

        aCommandSequence[nIndex].Name = rCommand.GetCommand();
        aCommandSequence[nIndex].Handle = -1;
        aCommandSequence[nIndex].Value = makeAny( OUString( rCommand.GetArgument() ) );
        aCommandSequence[nIndex].State = PropertyState_DIRECT_VALUE;

    }
}

///////////////////////////////////////////////////////////////////////

SvxAppletShape::SvxAppletShape( SdrObject* pObject ) throw()
: SvxOle2Shape( pObject, aSvxMapProvider.GetMap(SVXMAP_APPLET)  )
{
    SetShapeType( ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.drawing.AppletShape" ) ) );
}

SvxAppletShape::~SvxAppletShape() throw()
{
}

void SvxAppletShape::Create( SdrObject* pNewObj, SvxDrawPage* pNewPage ) throw ()
{
    SvxShape::Create( pNewObj, pNewPage );
    const SvGlobalName aAppletClassId( SO3_APPLET_CLASSID );
    createObject(aAppletClassId);
    SetShapeType( ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.drawing.AppletShape" ) ) );
}

//XPropertySet
void SAL_CALL SvxAppletShape::setPropertyValue( const OUString& aPropertyName, const Any& aValue )  throw( UnknownPropertyException, PropertyVetoException, IllegalArgumentException, WrappedTargetException, RuntimeException )
{
    ::SolarMutexGuard aGuard;

    sal_Bool bOwn = sal_False;

    const SfxItemPropertyMap* pMap = aPropSet.getPropertyMapEntry(aPropertyName);

    if( pMap && pObj && pModel )
    {
        if( pMap->nWID >= OWN_ATTR_APPLET_CODEBASE && pMap->nWID <= OWN_ATTR_APPLET_ISSCRIPT )
        {
            SvAppletObjectRef xApplet = SvAppletObjectRef( ((SdrOle2Obj*)pObj)->GetObjRef() );
            DBG_ASSERT( xApplet.Is(), "wrong ole object inside applet" );
            if( !xApplet.Is() )
                return;

            switch( pMap->nWID )
            {
                case OWN_ATTR_APPLET_CODEBASE:
                    {
                        OUString aCodeBase;
                        if( aValue >>= aCodeBase )
                        {
                            const String aStrCodeBase( aCodeBase );
                            xApplet->SetCodeBase( aStrCodeBase );
                            bOwn = sal_True;
                        }
                    }
                    break;
                case OWN_ATTR_APPLET_NAME:
                    {
                        OUString aName;
                        if( aValue >>= aName )
                        {
                            const String aStrName( aName );
                            xApplet->SetName( aStrName );
                            bOwn = sal_True;
                        }
                    }
                    break;
                case OWN_ATTR_APPLET_CODE:
                    {
                        OUString aCode;
                        if( aValue >>= aCode )
                        {
                            const String aStrCode( aCode );
                            xApplet->SetClass( aStrCode );
                            bOwn = sal_True;
                        }
                    }
                    break;
                case OWN_ATTR_APPLET_COMMANDS:
                    {
                        Sequence< PropertyValue > aCommandSequence;
                        if( aValue >>= aCommandSequence )
                        {
                            SvCommandList aNewCommands;
                            if( SvxImplFillCommandList( aCommandSequence, aNewCommands ) )
                            {
                                xApplet->SetCommandList( aNewCommands );
                                bOwn = sal_True;
                            }
                        }
                    }
                    break;
                case OWN_ATTR_APPLET_ISSCRIPT:
                    {
                        sal_Bool bScript = sal_False;
                        if( aValue >>= bScript )
                        {
                            xApplet->SetMayScript( bScript );
                            bOwn = sal_True;
                        }
                    }
                    break;
            }

            if( !bOwn )
                throw IllegalArgumentException();
        }
    }

    if( !bOwn )
        SvxOle2Shape::setPropertyValue( aPropertyName, aValue );

    if( pModel )
    {
        SvPersist* pPersist = pModel->GetPersist();
        if( pPersist && !pPersist->IsEnableSetModified() )
        {
            SdrOle2Obj* pOle = static_cast< SdrOle2Obj* >( pObj );
            if( pOle && ! pOle->IsEmpty() )
            {
                const SvInPlaceObjectRef& rIPRef = pOle->GetObjRef();

                if( rIPRef.Is() )
                    rIPRef->SetModified( sal_False );
            }
        }
    }
}

Any SAL_CALL SvxAppletShape::getPropertyValue( const OUString& PropertyName ) throw( UnknownPropertyException, WrappedTargetException, RuntimeException)
{
    ::SolarMutexGuard aGuard;

    const SfxItemPropertyMap* pMap = aPropSet.getPropertyMapEntry(PropertyName);

    if( pMap && pObj && pModel )
    {
        if( pMap->nWID >= OWN_ATTR_APPLET_CODEBASE && pMap->nWID <= OWN_ATTR_APPLET_ISSCRIPT )
        {
            SvAppletObjectRef xApplet = SvAppletObjectRef( ((SdrOle2Obj*)pObj)->GetObjRef() );
            DBG_ASSERT( xApplet.Is(), "wrong ole object inside applet" );
            if( xApplet.Is() )
            {

                switch( pMap->nWID )
                {
                    case OWN_ATTR_APPLET_CODEBASE:
                        return makeAny( OUString( xApplet->GetCodeBase() ) );
                    case OWN_ATTR_APPLET_NAME:
                        return makeAny( OUString( xApplet->GetName() ) );
                    case OWN_ATTR_APPLET_CODE:
                        return makeAny( OUString( xApplet->GetClass() ) );
                    case OWN_ATTR_APPLET_COMMANDS:
                        {
                            Sequence< PropertyValue > aCommandSequence;
                            SvxImplFillCommandSequence( xApplet->GetCommandList(), aCommandSequence );
                            return makeAny( aCommandSequence );
                        }
                    case OWN_ATTR_APPLET_ISSCRIPT:
                        return makeAny( (sal_Bool) xApplet->IsMayScript() );
                }
            }

            Any aAny;
            return aAny;
        }
    }

    return SvxOle2Shape::getPropertyValue( PropertyName );
}

///////////////////////////////////////////////////////////////////////

SvxPluginShape::SvxPluginShape( SdrObject* pObject ) throw()
: SvxOle2Shape( pObject, aSvxMapProvider.GetMap(SVXMAP_PLUGIN)  )
{
    SetShapeType( ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.drawing.PluginShape" ) ) );
}

SvxPluginShape::~SvxPluginShape() throw()
{
}

void SvxPluginShape::Create( SdrObject* pNewObj, SvxDrawPage* pNewPage ) throw ()
{
    SvxShape::Create( pNewObj, pNewPage );
    const SvGlobalName aPluginClassId( SO3_PLUGIN_CLASSID );
    createObject(aPluginClassId);
    SetShapeType( ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.drawing.PluginShape" ) ) );
}

//XPropertySet
void SAL_CALL SvxPluginShape::setPropertyValue( const OUString& aPropertyName, const Any& aValue )
    throw(UnknownPropertyException, PropertyVetoException, IllegalArgumentException, WrappedTargetException, RuntimeException)
{
    ::SolarMutexGuard aGuard;

    sal_Bool bOwn = sal_False;

    const SfxItemPropertyMap* pMap = aPropSet.getPropertyMapEntry(aPropertyName);

    if( pMap && pObj && pModel )
    {
        if( pMap->nWID >= OWN_ATTR_PLUGIN_MIMETYPE && pMap->nWID <= OWN_ATTR_PLUGIN_COMMANDS )
        {
            SvPlugInObjectRef xPlugin = SvPlugInObjectRef( ((SdrOle2Obj*)pObj)->GetObjRef() );
            DBG_ASSERT( xPlugin.Is(), "wrong ole object inside plugin" );
            if( !xPlugin.Is() )
                return;

            switch( pMap->nWID )
            {
                case OWN_ATTR_PLUGIN_MIMETYPE:
                    {
                        OUString aMimeType;
                        if( aValue >>= aMimeType )
                        {
                            const String aStrMimeType( aMimeType );
                            xPlugin->SetMimeType( aStrMimeType );
                            bOwn = sal_True;
                        }
                    }
                    break;
                case OWN_ATTR_PLUGIN_URL:
                    {
                        OUString aURL;
                        if( aValue >>= aURL )
                        {
                            xPlugin->SetURL( aURL );
                            bOwn = sal_True;
                        }
                    }
                    break;
                case OWN_ATTR_PLUGIN_COMMANDS:
                    {
                        Sequence< PropertyValue > aCommandSequence;
                        if( aValue >>= aCommandSequence )
                        {
                            SvCommandList aNewCommands;
                            if( SvxImplFillCommandList( aCommandSequence, aNewCommands ) )
                            {
                                xPlugin->SetCommandList( aNewCommands );
                                bOwn = sal_True;
                            }
                        }
                    }
                    break;
            }

            if( !bOwn )
                throw IllegalArgumentException();
        }
    }

    if( !bOwn )
        SvxOle2Shape::setPropertyValue( aPropertyName, aValue );

    if( pModel )
    {
        SvPersist* pPersist = pModel->GetPersist();
        if( pPersist && !pPersist->IsEnableSetModified() )
        {
            SdrOle2Obj* pOle = static_cast< SdrOle2Obj* >( pObj );
            if( pOle && ! pOle->IsEmpty() )
            {
                const SvInPlaceObjectRef& rIPRef = pOle->GetObjRef();

                if( rIPRef.Is() )
                    rIPRef->SetModified( sal_False );
            }
        }
    }
}

Any SAL_CALL SvxPluginShape::getPropertyValue( const OUString& PropertyName ) throw(UnknownPropertyException, WrappedTargetException, RuntimeException)
{
    ::SolarMutexGuard aGuard;

    const SfxItemPropertyMap* pMap = aPropSet.getPropertyMapEntry(PropertyName);

    if( pMap && pObj && pModel )
    {
        if( pMap->nWID >= OWN_ATTR_PLUGIN_MIMETYPE && pMap->nWID <= OWN_ATTR_PLUGIN_COMMANDS )
        {
            SvPlugInObjectRef xPlugin = SvPlugInObjectRef( ((SdrOle2Obj*)pObj)->GetObjRef() );
            DBG_ASSERT( xPlugin.Is(), "wrong ole object inside plugin" );
            if( xPlugin.Is() )
            {

                switch( pMap->nWID )
                {
                    case OWN_ATTR_PLUGIN_MIMETYPE:
                        return makeAny( OUString( xPlugin->GetMimeType() ) );
                    case OWN_ATTR_PLUGIN_URL:
                    {
                        OUString aURL;
                        DBG_ASSERT( xPlugin->GetURL(), "Plugin without a URL!" );
                        if( xPlugin->GetURL() )
                            aURL = xPlugin->GetURL()->GetMainURL( INetURLObject::NO_DECODE );
                        return makeAny( aURL );
                    }
                    case OWN_ATTR_PLUGIN_COMMANDS:
                        {
                            Sequence< PropertyValue > aCommandSequence;
                            SvxImplFillCommandSequence( xPlugin->GetCommandList(), aCommandSequence );
                            return makeAny( aCommandSequence );
                        }
                }
            }

            Any aAny;
            return aAny;
        }
    }

    return SvxOle2Shape::getPropertyValue( PropertyName );
}

///////////////////////////////////////////////////////////////////////

SvxFrameShape::SvxFrameShape( SdrObject* pObject ) throw()
: SvxOle2Shape( pObject, aSvxMapProvider.GetMap(SVXMAP_FRAME)  )
{
    SetShapeType( ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.drawing.FrameShape" ) ) );
}

SvxFrameShape::~SvxFrameShape() throw()
{
}

void SvxFrameShape::Create( SdrObject* pNewObj, SvxDrawPage* pNewPage ) throw ()
{
    SvxShape::Create( pNewObj, pNewPage );
    const SvGlobalName aIFrameClassId( BF_SO3_IFRAME_CLASSID );
    createObject(aIFrameClassId);
    SetShapeType( ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.drawing.FrameShape" ) ) );
}

//XPropertySet
void SAL_CALL SvxFrameShape::setPropertyValue( const OUString& aPropertyName, const Any& aValue )
    throw(UnknownPropertyException, PropertyVetoException, IllegalArgumentException, WrappedTargetException, RuntimeException)
{
    ::SolarMutexGuard aGuard;

    sal_Bool bOwn = sal_False;

    const SfxItemPropertyMap* pMap = aPropSet.getPropertyMapEntry(aPropertyName);

    Any aAny;
    if( pMap && pObj && pModel )
    {
        if( pMap->nWID >= OWN_ATTR_FRAME_URL && pMap->nWID <= OWN_ATTR_FRAME_MARGIN_HEIGHT )
        {
            return;
        }
    }

    if( !bOwn )
        SvxOle2Shape::setPropertyValue( aPropertyName, aValue );

    if( pModel )
    {
        SvPersist* pPersist = pModel->GetPersist();
        if( pPersist && !pPersist->IsEnableSetModified() )
        {
            SdrOle2Obj* pOle = static_cast< SdrOle2Obj* >( pObj );
            if( pOle && ! pOle->IsEmpty() )
            {
                const SvInPlaceObjectRef& rIPRef = pOle->GetObjRef();

                if( rIPRef.Is() )
                    rIPRef->SetModified( sal_False );
            }
        }
    }
}

Any SAL_CALL SvxFrameShape::getPropertyValue( const OUString& PropertyName ) throw(UnknownPropertyException, WrappedTargetException, RuntimeException)
{
    ::SolarMutexGuard aGuard;

    const SfxItemPropertyMap* pMap = aPropSet.getPropertyMapEntry(PropertyName);

    Any aAny;
    if( pMap && pObj && pModel )
    {
        if( pMap->nWID >= OWN_ATTR_FRAME_URL && pMap->nWID <= OWN_ATTR_FRAME_MARGIN_HEIGHT )
        {
            Any aLclAny;
            return aLclAny;
        }
    }

    return SvxOle2Shape::getPropertyValue( PropertyName );
}

#endif
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
