/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_unoviwed.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-08 07:34:06 $
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

// auto strip #ifndef _SV_OUTDEV_HXX
// auto strip #include <vcl/outdev.hxx>
// auto strip #endif

// auto strip #ifndef _SV_WINDOW_HXX
// auto strip #include <vcl/window.hxx>
// auto strip #endif

#include "unoviwed.hxx"
#include "editview.hxx"
#include "editeng.hxx"
#include "svdotext.hxx"
namespace binfilter {


SvxEditEngineViewForwarder::SvxEditEngineViewForwarder( EditView& rView ) :
    mrView( rView )
{
}

SvxEditEngineViewForwarder::~SvxEditEngineViewForwarder()
{
}

BOOL SvxEditEngineViewForwarder::IsValid() const
{
    return sal_True;
}

Rectangle SvxEditEngineViewForwarder::GetVisArea() const
{
    OutputDevice* pOutDev = mrView.GetWindow();

    if( pOutDev )
    {
        Rectangle aVisArea = mrView.GetVisArea();

        // figure out map mode from edit engine
        EditEngine* pEditEngine = mrView.GetEditEngine();

        if( pEditEngine )
        {
            MapMode aMapMode(pOutDev->GetMapMode());
            aVisArea = OutputDevice::LogicToLogic( aVisArea,
                                                   pEditEngine->GetRefMapMode(),
                                                   aMapMode.GetMapUnit() );
            aMapMode.SetOrigin(Point());
            return pOutDev->LogicToPixel( aVisArea, aMapMode );
        }
    }

    return Rectangle();
}

Point SvxEditEngineViewForwarder::LogicToPixel( const Point& rPoint, const MapMode& rMapMode ) const
{
    OutputDevice* pOutDev = mrView.GetWindow();

    if( pOutDev )
    {
        MapMode aMapMode(pOutDev->GetMapMode());
        Point aPoint( OutputDevice::LogicToLogic( rPoint, rMapMode,
                                                  aMapMode.GetMapUnit() ) );
        aMapMode.SetOrigin(Point());
        return pOutDev->LogicToPixel( aPoint, aMapMode );
    }

    return Point();
}

Point SvxEditEngineViewForwarder::PixelToLogic( const Point& rPoint, const MapMode& rMapMode ) const
{
    OutputDevice* pOutDev = mrView.GetWindow();

    if( pOutDev )
    {
        MapMode aMapMode(pOutDev->GetMapMode());
        aMapMode.SetOrigin(Point());
        Point aPoint( pOutDev->PixelToLogic( rPoint, aMapMode ) );
        return OutputDevice::LogicToLogic( aPoint,
                                           aMapMode.GetMapUnit(),
                                           rMapMode );
    }

    return Point();
}

sal_Bool SvxEditEngineViewForwarder::GetSelection( ESelection& rSelection ) const
{
    rSelection = mrView.GetSelection();
    return sal_True;
}

sal_Bool SvxEditEngineViewForwarder::SetSelection( const ESelection& rSelection )
{
    mrView.SetSelection( rSelection );
    return sal_True;
}

sal_Bool SvxEditEngineViewForwarder::Copy()
{
    mrView.Copy();
    return sal_True;
}

sal_Bool SvxEditEngineViewForwarder::Cut()
{
    mrView.Cut();
    return sal_True;
}

sal_Bool SvxEditEngineViewForwarder::Paste()
{
    mrView.Paste();
    return sal_True;
}
}
