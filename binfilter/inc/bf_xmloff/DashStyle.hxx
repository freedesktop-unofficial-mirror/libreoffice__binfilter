/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: DashStyle.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 17:09:31 $
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

#ifndef _XMLOFF_DASHSTYLE_HXX
#define _XMLOFF_DASHSTYLE_HXX

#ifndef _SAL_TYPES_H_
#include <sal/types.h>
#endif

namespace com { namespace sun { namespace star {
    namespace uno { template<class A> class Reference; }
    namespace xml { namespace sax { class XAttributeList; } }
    namespace uno { class Any; }
} } }
namespace rtl { class OUString; }
namespace binfilter {
class SvXMLImport;
class SvXMLExport;

class XMLDashStyleImport
{
    SvXMLImport& rImport;

public:
    XMLDashStyleImport( SvXMLImport& rImport );
    ~XMLDashStyleImport();

    sal_Bool importXML(
        const ::com::sun::star::uno::Reference<
                ::com::sun::star::xml::sax::XAttributeList >& xAttrList,
        ::com::sun::star::uno::Any& rValue,
        ::rtl::OUString& rStrName );
};

class XMLDashStyleExport
{
    SvXMLExport& rExport;

public:
    XMLDashStyleExport( SvXMLExport& rExport );
    ~XMLDashStyleExport();

    sal_Bool exportXML( const ::rtl::OUString& rStrName,
                        const ::com::sun::star::uno::Any& rValue );
};

}//end of namespace binfilter
#endif // _XMLOFF_DASHSTYLE_HXX
