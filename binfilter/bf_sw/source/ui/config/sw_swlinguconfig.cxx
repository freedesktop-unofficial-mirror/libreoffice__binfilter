/*************************************************************************
 *
 *  $RCSfile: sw_swlinguconfig.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:20:15 $
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

// #107253#
#ifndef _SWLINGUCONFIG_HXX
#include <swlinguconfig.hxx>
#endif

#ifndef _SVTOOLS_LINGUCFG_HXX_
#include <svtools/lingucfg.hxx>
#endif

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

//STRIP001 sal_Bool SwLinguConfig::SetProperty(const rtl::OUString &rPropertyName, const com::sun::star::uno::Any &rValue)
//STRIP001 {
//STRIP001  ImplCreateOnDemand();
//STRIP001  return mpImplLinguConfig->SetProperty(rPropertyName, rValue);
//STRIP001 }

/*N*/ sal_Bool SwLinguConfig::GetOptions(SvtLinguOptions &rOptions) const
/*N*/ {
/*N*/   ImplCreateOnDemand();
/*N*/   return mpImplLinguConfig->GetOptions(rOptions);
/*N*/ }

//STRIP001 com::sun::star::uno::Any SwLinguConfig::GetProperty(const rtl::OUString &rPropertyName) const
//STRIP001 {
//STRIP001  ImplCreateOnDemand();
//STRIP001  return mpImplLinguConfig->GetProperty(rPropertyName);
//STRIP001 }

// eof
