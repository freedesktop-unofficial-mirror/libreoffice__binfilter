/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xmlmetae.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 17:40:55 $
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

#ifndef _XMLOFF_XMLMETAE_HXX
#define _XMLOFF_XMLMETAE_HXX

#ifndef _COM_SUN_STAR_DOCUMENT_XDOCUMENTINFO_HPP_
#include <com/sun/star/document/XDocumentInfo.hpp>
#endif
#ifndef _COM_SUN_STAR_XML_SAX_XDOCUMENTHANDLER_HPP_
#include <com/sun/star/xml/sax/XDocumentHandler.hpp>
#endif
#ifndef _COM_SUN_STAR_XML_SAX_XATTRIBUTELIST_HPP_
#include <com/sun/star/xml/sax/XAttributeList.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
#include <com/sun/star/beans/XPropertySet.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_DATETIME_HPP_
#include <com/sun/star/util/DateTime.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_LOCALE_HPP_
#include <com/sun/star/lang/Locale.hpp>
#endif
#ifndef _XMLOFF_XMLTOKEN_HXX
#include <bf_xmloff/xmltoken.hxx>
#endif
class Time;

namespace com { namespace sun { namespace star { namespace frame {
    class XModel;
} } } }
namespace binfilter {

class SvXMLNamespaceMap;
class SvXMLAttributeList;
class SvXMLExport;

class SfxXMLMetaExport
{
private:
    SvXMLExport&                                        rExport;
    ::com::sun::star::uno::Reference<
        ::com::sun::star::document::XDocumentInfo>      xDocInfo;
    ::com::sun::star::uno::Reference<
        ::com::sun::star::beans::XPropertySet>          xInfoProp;
    ::com::sun::star::lang::Locale                      aLocale;

    void    SimpleStringElement( const ::rtl::OUString& rPropertyName,
                                 sal_uInt16 nNamespace,
                             enum ::binfilter::xmloff::token::XMLTokenEnum eElementName );
    void    SimpleDateTimeElement( const ::rtl::OUString& rPropertyName,
                                   sal_uInt16 nNamespace,
                             enum ::binfilter::xmloff::token::XMLTokenEnum eElementName );

public:
    SfxXMLMetaExport( SvXMLExport& rExport,
                      const ::com::sun::star::uno::Reference<
                        ::com::sun::star::frame::XModel>& rDocModel );

    virtual ~SfxXMLMetaExport();

    // core API
    void Export();

    static ::rtl::OUString GetISODateTimeString(
                        const ::com::sun::star::util::DateTime& rDateTime );
    static ::rtl::OUString GetISODurationString( const Time& rTime );
};

}//end of namespace binfilter
#endif // _XMLOFF_XMLMETAE_HXX

