/*************************************************************************
 *
 *  $RCSfile: sch_ChartTitle.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:34:09 $
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
#include "ChartTitle.hxx"

#include "mapprov.hxx"
#include "defines.hxx"

// header for class OGuard
#ifndef _VOS_MUTEX_HXX_
#include <vos/mutex.hxx>
#endif
// header for class Application
#ifndef _SV_SVAPP_HXX
#include <vcl/svapp.hxx>
#endif
#ifndef _RTL_UUID_H_
#include <rtl/uuid.h>
#endif
#ifndef _CPPUHELPER_QUERYINTERFACE_HXX_
#include <cppuhelper/queryinterface.hxx>
#endif

#include "schattr.hxx"
#ifndef _SVX_CHRTITEM_HXX //autogen
#define ITEMID_CHARTTEXTORIENT  SCHATTR_TEXT_ORIENT
#include <bf_svx/chrtitem.hxx>
#endif
#include "chtmodel.hxx"
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
    return ::rtl::OUString::createFromAscii( "ChartTitle" );
}

uno::Sequence< ::rtl::OUString > SAL_CALL ChartTitle::getSupportedServiceNames()
    throw( uno::RuntimeException )
{
    ::vos::OGuard aGuard( Application::GetSolarMutex() );

    uno::Sequence< ::rtl::OUString > aSeq( 4 );
    aSeq[ 0 ] = ::rtl::OUString::createFromAscii( "com.sun.star.chart.ChartTitle" );
    aSeq[ 1 ] = ::rtl::OUString::createFromAscii( "com.sun.star.drawing.Shape" );
    aSeq[ 2 ] = ::rtl::OUString::createFromAscii( "com.sun.star.style.CharacterProperties" );
    aSeq[ 3 ] = ::rtl::OUString::createFromAscii( "com.sun.star.xml.UserDefinedAttributeSupplier" );

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
    return ::rtl::OUString::createFromAscii( "com.sun.star.chart.ChartTitle" );
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

ChartTitle* ChartTitle::getImplementation( uno::Reference< uno::XInterface > xData ) throw()
{
    uno::Reference< lang::XUnoTunnel > xUT( xData, uno::UNO_QUERY );
    if( xUT.is() )
        return (ChartTitle*)xUT->getSomething( ChartTitle::getUnoTunnelId() );
    else
        return NULL;
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
