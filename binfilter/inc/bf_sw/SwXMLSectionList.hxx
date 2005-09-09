/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: SwXMLSectionList.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 15:45:01 $
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
