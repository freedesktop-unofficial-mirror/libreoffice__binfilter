/*************************************************************************
 *
 *  $RCSfile: sw_SwXMLSectionList.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:41:03 $
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
 *  Contributor(s): Martin Gallwey (gallwey@sun.com)
 *
 *
 ************************************************************************/
#pragma hdrstop

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
//STRIP001                         GetXMLToken ( XML_N_BLOCK_LIST),
//STRIP001                         XML_NAMESPACE_BLOCKLIST );
/*N*/ }

//STRIP001 SwXMLSectionList::~SwXMLSectionList ( void )
//STRIP001  throw()
//STRIP001 {
//STRIP001 }

//STRIP001 SvXMLImportContext *SwXMLSectionList::CreateContext(
//STRIP001      sal_uInt16 nPrefix,
//STRIP001      const OUString& rLocalName,
//STRIP001      const Reference< xml::sax::XAttributeList > & xAttrList )
//STRIP001 {
//STRIP001  SvXMLImportContext *pContext = 0;
//STRIP001
//STRIP001  if  (nPrefix == XML_NAMESPACE_OFFICE && IsXMLToken ( rLocalName, XML_BODY ) ||
//STRIP001       nPrefix == XML_NAMESPACE_TEXT &&
//STRIP001      (IsXMLToken ( rLocalName, XML_P ) ||
//STRIP001       IsXMLToken ( rLocalName, XML_H ) ||
//STRIP001       IsXMLToken ( rLocalName, XML_A ) ||
//STRIP001       IsXMLToken ( rLocalName, XML_SPAN ) ||
//STRIP001       IsXMLToken ( rLocalName, XML_SECTION ) ||
//STRIP001       IsXMLToken ( rLocalName, XML_INDEX_BODY ) ||
//STRIP001       IsXMLToken ( rLocalName, XML_INDEX_TITLE )||
//STRIP001       IsXMLToken ( rLocalName, XML_INSERTION ) ||
//STRIP001       IsXMLToken ( rLocalName, XML_DELETION ) ) )
//STRIP001      pContext = new SvXMLSectionListContext (*this, nPrefix, rLocalName, xAttrList);
//STRIP001  else
//STRIP001      pContext = SvXMLImport::CreateContext( nPrefix, rLocalName, xAttrList );
//STRIP001  return pContext;
//STRIP001 }

//STRIP001 SvXMLSectionListContext::SvXMLSectionListContext(
//STRIP001    SwXMLSectionList& rImport,
//STRIP001    sal_uInt16 nPrefix,
//STRIP001    const OUString& rLocalName,
//STRIP001    const ::com::sun::star::uno::Reference<
//STRIP001    ::com::sun::star::xml::sax::XAttributeList > & xAttrList ) :
//STRIP001    rLocalRef(rImport),
//STRIP001    SvXMLImportContext ( rImport, nPrefix, rLocalName )
//STRIP001 {
//STRIP001 }

//STRIP001 SvXMLImportContext *SvXMLSectionListContext::CreateChildContext(
//STRIP001  sal_uInt16 nPrefix,
//STRIP001  const OUString& rLocalName,
//STRIP001  const Reference< xml::sax::XAttributeList > & xAttrList )
//STRIP001 {
//STRIP001  SvXMLImportContext *pContext = 0;
//STRIP001  String sName;
//STRIP001
//STRIP001  if (nPrefix == XML_NAMESPACE_TEXT && ( IsXMLToken ( rLocalName, XML_SECTION ) ||
//STRIP001                                         IsXMLToken ( rLocalName, XML_BOOKMARK) ) )
//STRIP001  {
//STRIP001      sal_Int16 nAttrCount = xAttrList.is() ? xAttrList->getLength() : 0;
//STRIP001
//STRIP001      for (sal_Int16 i=0; i < nAttrCount; i++)
//STRIP001      {
//STRIP001          const OUString& rAttrName = xAttrList->getNameByIndex( i );
//STRIP001          OUString aLocalName;
//STRIP001          sal_uInt16 nPrefix = rLocalRef.GetNamespaceMap().GetKeyByAttrName( rAttrName, &aLocalName);
//STRIP001          const OUString& rAttrValue = xAttrList->getValueByIndex( i );
//STRIP001          if (XML_NAMESPACE_TEXT == nPrefix && IsXMLToken ( aLocalName, XML_NAME ) )
//STRIP001              sName = rAttrValue;
//STRIP001      }
//STRIP001      if ( sName.Len() )
//STRIP001          rLocalRef.rSectionList.Insert ( new String(sName), rLocalRef.rSectionList.Count() );
//STRIP001  }
//STRIP001
//STRIP001  pContext = new SvXMLSectionListContext (rLocalRef, nPrefix, rLocalName, xAttrList);
//STRIP001  return pContext;
//STRIP001 }
//STRIP001 SvXMLSectionListContext::~SvXMLSectionListContext ( void )
//STRIP001 {
//STRIP001 }

//STRIP001 SvXMLIgnoreSectionListContext::SvXMLIgnoreSectionListContext(
//STRIP001    SwXMLSectionList& rImport,
//STRIP001    sal_uInt16 nPrefix,
//STRIP001    const OUString& rLocalName,
//STRIP001    const ::com::sun::star::uno::Reference<
//STRIP001    ::com::sun::star::xml::sax::XAttributeList > & xAttrList ) :
//STRIP001    rLocalRef(rImport),
//STRIP001    SvXMLImportContext ( rImport, nPrefix, rLocalName )
//STRIP001 {
//STRIP001 }

//STRIP001 SvXMLIgnoreSectionListContext::~SvXMLIgnoreSectionListContext ( void )
//STRIP001 {
//STRIP001 }
//STRIP001 SvXMLImportContext *SvXMLIgnoreSectionListContext::CreateChildContext(
//STRIP001  sal_uInt16 nPrefix,
//STRIP001  const OUString& rLocalName,
//STRIP001  const Reference< xml::sax::XAttributeList > & xAttrList )
//STRIP001 {
//STRIP001  return  new SvXMLIgnoreSectionListContext (rLocalRef, nPrefix, rLocalName, xAttrList);
//STRIP001 }
}
