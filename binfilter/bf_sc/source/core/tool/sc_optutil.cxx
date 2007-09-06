/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sc_optutil.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 10:48:35 $
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
#endif

#ifdef _MSC_VER
#pragma hdrstop
#endif


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




}
