/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xmlversion.hxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: vg $ $Date: 2007-10-23 13:41:42 $
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
#ifndef _SFX_XMLVERSION_HXX
#define _SFX_XMLVERSION_HXX

#ifndef _SVSTOR_HXX
#include <bf_so3/svstor.hxx>
#endif


//#ifndef _XMLOFF_XMLITMAP_HXX
//#include <bf_xmloff/xmlitmap.hxx>
//#endif

#ifndef _XMLOFF_XMLEXP_HXX
#include <bf_xmloff/xmlexp.hxx>
#endif

#ifndef _XMLOFF_XMLIMP_HXX
#include <bf_xmloff/xmlimp.hxx>
#endif



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
