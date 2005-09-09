/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: XMLTextMasterPageContext.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 17:27:26 $
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
#ifndef _XMLOFF_TEXTMASTERPAGECONTEXT_HXX_
#define _XMLOFF_TEXTMASTERPAGECONTEXT_HXX_

#ifndef _XMLOFF_XMLSTYLE_HXX_
#include <bf_xmloff/xmlstyle.hxx>
#endif

namespace com { namespace sun { namespace star {
    namespace style { class XStyle; }
} } }
namespace binfilter {

class XMLTextMasterPageContext : public SvXMLStyleContext
{
    const ::rtl::OUString sIsPhysical;
    const ::rtl::OUString sPageStyleLayout;
    const ::rtl::OUString sFollowStyle;
    ::rtl::OUString       sFollow;
    ::rtl::OUString       sPageMasterName;

    ::com::sun::star::uno::Reference < ::com::sun::star::style::XStyle > xStyle;

    sal_Bool bInsertHeader;
    sal_Bool bInsertFooter;
    sal_Bool bInsertHeaderLeft;
    sal_Bool bInsertFooterLeft;
    sal_Bool bHeaderInserted;
    sal_Bool bFooterInserted;
    sal_Bool bHeaderLeftInserted;
    sal_Bool bFooterLeftInserted;

    ::com::sun::star::uno::Reference <
        ::com::sun::star::style::XStyle > Create();
protected:
    ::com::sun::star::uno::Reference <
        ::com::sun::star::style::XStyle > GetStyle() { return xStyle; }
public:

    TYPEINFO();

    XMLTextMasterPageContext( SvXMLImport& rImport, sal_uInt16 nPrfx,
            const ::rtl::OUString& rLName,
            const ::com::sun::star::uno::Reference<
                ::com::sun::star::xml::sax::XAttributeList > & xAttrList,
            sal_Bool bOverwrite );
    virtual ~XMLTextMasterPageContext();

    virtual SvXMLImportContext *CreateChildContext(
            sal_uInt16 nPrefix,
            const ::rtl::OUString& rLocalName,
            const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList > & xAttrList );

    virtual SvXMLImportContext *CreateHeaderFooterContext(
            sal_uInt16 nPrefix,
            const ::rtl::OUString& rLocalName,
            const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList > & xAttrList,
            const sal_Bool bFooter,
            const sal_Bool bLeft );

    virtual void Finish( sal_Bool bOverwrite );
};

}//end of namespace binfilter
#endif
