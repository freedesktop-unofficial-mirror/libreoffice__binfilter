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
#include "ChartTitle.hxx"

#include "mapprov.hxx"

// header for class OGuard
// header for class Application
#include <vcl/svapp.hxx>
#include <rtl/uuid.h>

#include "schattr.hxx"
#ifndef _SVX_CHRTITEM_HXX //autogen
#define ITEMID_CHARTTEXTORIENT  SCHATTR_TEXT_ORIENT

#include <bf_svtools/eitem.hxx>

#endif
#include "globfunc.hxx"
namespace binfilter {

using namespace ::com::sun::star;

ChartTitle::ChartTitle( ChartModel* pModel, sal_Int32 nObjectId ) :
        ChXChartObject( CHMAP_TITLE, pModel, nObjectId )
{
}

ChartTitle::~ChartTitle()
{}

// XServiceInfo
::rtl::OUString SAL_CALL ChartTitle::getImplementationName()
    throw( uno::RuntimeException )
{
    return ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "ChartTitle" ));
}

uno::Sequence< ::rtl::OUString > SAL_CALL ChartTitle::getSupportedServiceNames()
    throw( uno::RuntimeException )
{
    SolarMutexGuard aGuard;

    uno::Sequence< ::rtl::OUString > aSeq( 4 );
    aSeq[ 0 ] = ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.chart.ChartTitle" ));
    aSeq[ 1 ] = ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.drawing.Shape" ));
    aSeq[ 2 ] = ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.style.CharacterProperties" ));
    aSeq[ 3 ] = ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.xml.UserDefinedAttributeSupplier" ));

    return aSeq;
}

// XTypeProvider
uno::Sequence< sal_Int8 > SAL_CALL ChartTitle::getImplementationId()
    throw( uno::RuntimeException )
{
    static uno::Sequence< sal_Int8 > aId;
    if( aId.getLength() == 0 )
    {
        aId.realloc( 16 );
        rtl_createUuid( (sal_uInt8 *)aId.getArray(), 0, sal_True );
    }
    return aId;
}

// XShapeDescriptor
::rtl::OUString SAL_CALL ChartTitle::getShapeType()
    throw( uno::RuntimeException )
{
    return ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.chart.ChartTitle" ));
}

// XUnoTunnel
sal_Int64 SAL_CALL ChartTitle::getSomething( const uno::Sequence< sal_Int8 >& aIdentifier )
    throw( uno::RuntimeException )
{
    if( aIdentifier.getLength() == 16 && 0 == rtl_compareMemory( getUnoTunnelId().getConstArray(),
                                                                 aIdentifier.getConstArray(), 16 ) )
    {
        return (sal_Int64)this;
    }
    return ChXChartObject::getSomething( aIdentifier );
}

// helpers for XUnoTunnel
const uno::Sequence< sal_Int8 > & ChartTitle::getUnoTunnelId() throw()
{
    static uno::Sequence< sal_Int8 > * pSeq = 0;
    if( !pSeq )
    {
        osl::Guard< osl::Mutex > aGuard( osl::Mutex::getGlobalMutex() );
        if( !pSeq )
        {
            static uno::Sequence< sal_Int8 > aSeq( 16 );
            rtl_createUuid( (sal_uInt8*)aSeq.getArray(), 0, sal_True );
            pSeq = &aSeq;
        }
    }
    return *pSeq;
}

void ChartTitle::GetPropertyValue( const SfxItemPropertyMap & rProperty,
                                   ::com::sun::star::uno::Any & rValue,
                                   SfxItemSet & rAttributes )
{
    switch( rProperty.nWID )
    {
        //  Axis title rotation angle.
        case SCHATTR_TEXT_DEGREES:
            {
                //  Automatic text orientation is changed into corresponding
                //  rotation angle.
                SvxChartTextOrient eOrientation =
                    ((const SvxChartTextOrientItem&)rAttributes.Get(
                        SCHATTR_TEXT_ORIENT)).GetValue();
                if (eOrientation == CHTXTORIENT_AUTOMATIC)
                {
                    switch (mnWhichId)
                    {
                        case CHOBJID_DIAGRAM_TITLE_X_AXIS:
                            if (mpModel->IsXVertikal())
                                eOrientation = CHTXTORIENT_BOTTOMTOP;
                            else
                                eOrientation = CHTXTORIENT_AUTOMATIC;
                            break;

                        case CHOBJID_DIAGRAM_TITLE_Y_AXIS:
                            if (mpModel->IsXVertikal())
                                eOrientation = CHTXTORIENT_AUTOMATIC;
                            else
                                eOrientation = CHTXTORIENT_BOTTOMTOP;
                            break;

                        case CHOBJID_DIAGRAM_TITLE_Z_AXIS:
                            if (mpModel->IsXVertikal())
                                eOrientation = CHTXTORIENT_TOPBOTTOM;
                            else
                                eOrientation = CHTXTORIENT_AUTOMATIC;
                            break;

                        default:
                            eOrientation = CHTXTORIENT_AUTOMATIC;
                            break;
                    }
                }
                // GetTextRotation is in globfunc and returns the value of the
                // rotation item (SCHATTR_TEXT_DEGREES) if set, otherwise
                // defaults according to the orientation
                rValue <<= static_cast< sal_Int32 >( GetTextRotation (rAttributes, eOrientation) );
            }
            break;

        default:
            ChXChartObject::GetPropertyValue( rProperty, rValue, rAttributes );
    }
}
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
