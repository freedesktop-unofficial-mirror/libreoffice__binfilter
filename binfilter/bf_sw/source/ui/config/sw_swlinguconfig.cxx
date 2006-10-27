/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_swlinguconfig.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 00:05:25 $
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

// #107253#
#ifndef _SWLINGUCONFIG_HXX
#include <swlinguconfig.hxx>
#endif

#ifndef _SVTOOLS_LINGUCFG_HXX_
#include <svtools/lingucfg.hxx>
#endif
namespace binfilter {

// init static member
static SvtLinguConfig* mpImplLinguConfig = 0L;
static sal_uInt32 mnImplUseCount = 0L;

/*N*/ void ImplCreateOnDemand()
/*N*/ {
/*N*/   if(!mpImplLinguConfig && mnImplUseCount)
/*N*/   {
/*N*/       mpImplLinguConfig = new SvtLinguConfig();
/*N*/   }
/*N*/ }

/*N*/ SwLinguConfig::SwLinguConfig()
/*N*/ {
/*N*/   mnImplUseCount++;
/*N*/ }

/*N*/ SwLinguConfig::~SwLinguConfig()
/*N*/ {
/*N*/   mnImplUseCount--;
/*N*/
/*N*/   if(!mnImplUseCount && mpImplLinguConfig)
/*N*/   {
/*N*/       delete mpImplLinguConfig;
/*N*/       mpImplLinguConfig = 0L;
/*N*/   }
/*N*/ }


/*N*/ sal_Bool SwLinguConfig::GetOptions(SvtLinguOptions &rOptions) const
/*N*/ {
/*N*/   ImplCreateOnDemand();
/*N*/   return mpImplLinguConfig->GetOptions(rOptions);
/*N*/ }


// eof
}
