/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_SwXMLSectionList.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 12:28:09 $
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

#define _SVSTDARR_STRINGSDTOR
#define _SVSTDARR_STRINGS
#include <svtools/svstdarr.hxx>
#ifndef _SW_XMLSECTIONLIST_HXX
#include <SwXMLSectionList.hxx>
#endif
#ifndef _XMLOFF_XMLTOKEN_HXX
#include <bf_xmloff/xmltoken.hxx>
#endif
#ifndef _XMLOFF_NMSPMAP_HXX
#include <bf_xmloff/nmspmap.hxx>
#endif
#ifndef _XMLOFF_XMLNMSPE_HXX
#include <bf_xmloff/xmlnmspe.hxx>
#endif
#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif

using namespace ::com::sun::star::uno;
using namespace ::com::sun::star;
using namespace ::rtl;
using namespace ::binfilter::xmloff::token;
#include <tools/debug.hxx>  //STRIP001
namespace binfilter {
sal_Char __READONLY_DATA sXML_np__block_list[] = "_block-list";

// #110680#
/*N*/ SwXMLSectionList::SwXMLSectionList(
/*N*/   const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory > xServiceFactory,
/*N*/   SvStrings & rNewSectionList)
/*N*/ : SvXMLImport( xServiceFactory ),
/*N*/   rSectionList ( rNewSectionList )
/*N*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); //STRIP001 GetNamespaceMap().Add( OUString ( RTL_CONSTASCII_USTRINGPARAM ( sXML_np__block_list ) ),
/*N*/ }






}
