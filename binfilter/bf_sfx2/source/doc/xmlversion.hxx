/*************************************************************************
 *
 *  $RCSfile: xmlversion.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 14:54:03 $
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
#ifndef _SFX_XMLVERSION_HXX
#define _SFX_XMLVERSION_HXX

#ifndef _SVSTOR_HXX
#include <so3/svstor.hxx>
#endif

// auto strip #ifndef _XMLOFF_XMLICTXT_HXX
// auto strip #include <bf_xmloff/xmlictxt.hxx>
// auto strip #endif

//#ifndef _XMLOFF_XMLITMAP_HXX
//#include <bf_xmloff/xmlitmap.hxx>
//#endif

#ifndef _XMLOFF_XMLEXP_HXX
#include <bf_xmloff/xmlexp.hxx>
#endif

#ifndef _XMLOFF_XMLIMP_HXX
#include <bf_xmloff/xmlimp.hxx>
#endif

// auto strip #ifndef _XMLOFF_NMSPMAP_HXX
// auto strip #include <bf_xmloff/nmspmap.hxx>
// auto strip #endif

// auto strip #ifndef _XMLOFF_XMLNMSPE_HXX
// auto strip #include <bf_xmloff/xmlnmspe.hxx>
// auto strip #endif

// auto strip #ifndef _XMLOFF_XMLTOKEN_HXX
// auto strip #include <bf_xmloff/xmltoken.hxx>
// auto strip #endif
class DateTime;
namespace binfilter {

class SfxVersionTableDtor;

// ------------------------------------------------------------------------
class SfxXMLVersListExport_Impl : public SvXMLExport
{
private:
    const SfxVersionTableDtor *mpVersions;
public:
    // #110680#
    SfxXMLVersListExport_Impl(
        const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory > xServiceFactory,
        const SfxVersionTableDtor *pVersions,
        const ::rtl::OUString &rFileName,
        ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XDocumentHandler > &rHandler );
    virtual     ~SfxXMLVersListExport_Impl() {}

    sal_uInt32  exportDoc( enum ::binfilter::xmloff::token::XMLTokenEnum eClass );
    void        _ExportAutoStyles() {}
    void        _ExportMasterStyles () {}
    void        _ExportContent() {}
};

// ------------------------------------------------------------------------
class SfxXMLVersListImport_Impl : public SvXMLImport
{
private:
    SfxVersionTableDtor *mpVersions;

protected:

    // This method is called after the namespace map has been updated, but
    // before a context for the current element has been pushed.
    virtual SvXMLImportContext *CreateContext( sal_uInt16 nPrefix,
                    const ::rtl::OUString& rLocalName,
                    const ::com::sun::star::uno::Reference<
                    ::com::sun::star::xml::sax::XAttributeList > & xAttrList );

public:

    // #110680#
    SfxXMLVersListImport_Impl(
        const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory > xServiceFactory,
        SfxVersionTableDtor *pVersions );
    ~SfxXMLVersListImport_Impl() throw();

    SfxVersionTableDtor*     GetList() { return mpVersions; }
};

// ------------------------------------------------------------------------
class SfxXMLVersListContext_Impl : public SvXMLImportContext
{
private:
    SfxXMLVersListImport_Impl & rLocalRef;

public:

    SfxXMLVersListContext_Impl( SfxXMLVersListImport_Impl& rImport,
                           sal_uInt16 nPrefix,
                           const ::rtl::OUString& rLocalName,
                           const ::com::sun::star::uno::Reference<
                           ::com::sun::star::xml::sax::XAttributeList > & xAttrList );

    ~SfxXMLVersListContext_Impl();

    virtual SvXMLImportContext *CreateChildContext( sal_uInt16 nPrefix,
                           const ::rtl::OUString& rLocalName,
                           const ::com::sun::star::uno::Reference<
                           ::com::sun::star::xml::sax::XAttributeList > & xAttrList );

};

// ------------------------------------------------------------------------
class SfxXMLVersionContext_Impl : public SvXMLImportContext
{
private:
    SfxXMLVersListImport_Impl&  rLocalRef;

    static sal_Bool         ParseISODateTimeString(
                                const ::rtl::OUString& rString,
                                DateTime& rDateTime );

public:

    SfxXMLVersionContext_Impl( SfxXMLVersListImport_Impl& rImport,
                          sal_uInt16 nPrefix,
                          const ::rtl::OUString& rLocalName,
                          const ::com::sun::star::uno::Reference<
                          ::com::sun::star::xml::sax::XAttributeList > & xAttrList );

    ~SfxXMLVersionContext_Impl();
};


// ------------------------------------------------------------------------
class SfxXMLVersList_Impl
{
public:
    static void     WriteInfo( SvStorageRef xRoot,
                               const SfxVersionTableDtor *mpVersions );
    static sal_Bool ReadInfo( SvStorageRef xRoot, SfxVersionTableDtor *pList );
};



}//end of namespace binfilter
#endif
