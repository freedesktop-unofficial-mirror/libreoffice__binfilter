/*************************************************************************
 *
 *  $RCSfile: SwXMLSectionList.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: aw $ $Date: 2003-12-05 15:11:31 $
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
#ifndef _SW_XMLSECTIONLIST_HXX
#define _SW_XMLSECTIONLIST_HXX

#ifndef _XMLOFF_XMLICTXT_HXX
#include <bf_xmloff/xmlictxt.hxx>
#endif
#ifndef _XMLOFF_XMLIMP_HXX
#include <bf_xmloff/xmlimp.hxx>
#endif
class SvStrings;
namespace binfilter {



class SwXMLSectionList : public SvXMLImport
{
//STRIP001 protected:
//STRIP001  // This method is called after the namespace map has been updated, but
//STRIP001  // before a context for the current element has been pushed.
//STRIP001  virtual SvXMLImportContext *CreateContext( sal_uInt16 nPrefix,
//STRIP001                const ::rtl::OUString& rLocalName,
//STRIP001                const ::com::sun::star::uno::Reference<
//STRIP001                  ::com::sun::star::xml::sax::XAttributeList > & xAttrList );
public:
     SvStrings & rSectionList;

    // #110680#
    SwXMLSectionList(
        const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory > xServiceFactory,
        SvStrings & rNewSectionList );

//STRIP001  virtual ~SwXMLSectionList ( )
//STRIP001      throw();
};

//STRIP001 class SvXMLSectionListContext : public SvXMLImportContext
//STRIP001 {
//STRIP001 private:
//STRIP001  SwXMLSectionList & rLocalRef;
//STRIP001 public:
//STRIP001  SvXMLSectionListContext ( SwXMLSectionList& rImport,
//STRIP001                         sal_uInt16 nPrefix,
//STRIP001                         const ::rtl::OUString& rLocalName,
//STRIP001                         const ::com::sun::star::uno::Reference<
//STRIP001                         ::com::sun::star::xml::sax::XAttributeList > & xAttrList );
//STRIP001  virtual SvXMLImportContext *CreateChildContext( sal_uInt16 nPrefix,
//STRIP001                         const ::rtl::OUString& rLocalName,
//STRIP001                         const ::com::sun::star::uno::Reference<
//STRIP001                         ::com::sun::star::xml::sax::XAttributeList > & xAttrList );
//STRIP001  ~SvXMLSectionListContext ( void );
//STRIP001 };

//STRIP001 class SvXMLIgnoreSectionListContext : public SvXMLImportContext
//STRIP001 {
//STRIP001 private:
//STRIP001  SwXMLSectionList & rLocalRef;
//STRIP001 public:
//STRIP001  SvXMLIgnoreSectionListContext ( SwXMLSectionList& rImport,
//STRIP001                         sal_uInt16 nPrefix,
//STRIP001                         const ::rtl::OUString& rLocalName,
//STRIP001                         const ::com::sun::star::uno::Reference<
//STRIP001                         ::com::sun::star::xml::sax::XAttributeList > & xAttrList );
//STRIP001  virtual SvXMLImportContext *CreateChildContext( sal_uInt16 nPrefix,
//STRIP001                         const ::rtl::OUString& rLocalName,
//STRIP001                         const ::com::sun::star::uno::Reference<
//STRIP001                         ::com::sun::star::xml::sax::XAttributeList > & xAttrList );
//STRIP001  ~SvXMLIgnoreSectionListContext ( void );
//STRIP001 };
} //namespace binfilter
#endif
