/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sc_optutil.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 17:13:28 $
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

#ifdef PCH
// auto strip #include "core_pch.hxx"
#endif

#pragma hdrstop

// auto strip #include <vcl/svapp.hxx>

#include "optutil.hxx"
#include "global.hxx"       // for pSysLocale

#ifndef INCLUDED_SVTOOLS_SYSLOCALE_HXX
#include <svtools/syslocale.hxx>
#endif
namespace binfilter {

//------------------------------------------------------------------

// static
/*N*/ BOOL ScOptionsUtil::IsMetricSystem()
/*N*/ {
/*N*/   //! which language should be used here - system language or installed office language?
/*N*/
/*N*/ //    MeasurementSystem eSys = Application::GetAppInternational().GetMeasurementSystem();
/*N*/     MeasurementSystem eSys = ScGlobal::pLocaleData->getMeasurementSystemEnum();
/*N*/
/*N*/   return ( eSys == MEASURE_METRIC );
/*N*/ }

//------------------------------------------------------------------

/*N*/ ScLinkConfigItem::ScLinkConfigItem( const ::rtl::OUString rSubTree ) :
/*N*/   ConfigItem( rSubTree )
/*N*/ {
/*N*/ }

/*N*/ void ScLinkConfigItem::SetCommitLink( const Link& rLink )
/*N*/ {
/*N*/   aCommitLink = rLink;
/*N*/ }

//STRIP001 void ScLinkConfigItem::Notify( const ::com::sun::star::uno::Sequence<rtl::OUString>& aPropertyNames )
//STRIP001 {
//STRIP001  //! not implemented yet...
//STRIP001 }

//STRIP001 void ScLinkConfigItem::Commit()
//STRIP001 {
//STRIP001  aCommitLink.Call( this );
//STRIP001 }


}
