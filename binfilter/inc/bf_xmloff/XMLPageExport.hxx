/*************************************************************************
 *
 *  $RCSfile: XMLPageExport.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: aw $ $Date: 2003-12-05 09:17:55 $
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

#ifndef _XMLOFF_XMLPAGEEXPORT_HXX
#define _XMLOFF_XMLPAGEEXPORT_HXX

#ifndef _RTL_USTRING_HXX_
#include <rtl/ustring.hxx>
#endif
#ifndef __SGI_STL_VECTOR
#include <vector>
#endif
#ifndef _XMLOFF_ATTRLIST_HXX
#include <bf_xmloff/attrlist.hxx>
#endif
#ifndef _UNIVERSALL_REFERENCE_HXX
#include <bf_xmloff/uniref.hxx>
#endif

#ifndef _COM_SUN_STAR_CONTAINER_XINDEXACCESS_HPP_
#include <com/sun/star/container/XIndexAccess.hpp>
#endif

namespace com { namespace sun { namespace star {
    namespace style { class XStyle; }
    namespace container { class XIndexReplace; }
    namespace beans { class XPropertySet; }
} } }
namespace binfilter {

class SvXMLExport;
class XMLPropertyHandlerFactory;
class XMLPropertySetMapper;
class SvXMLExportPropertyMapper;

//______________________________________________________________________________

struct XMLPageExportNameEntry
{
    ::rtl::OUString         sPageMasterName;
    ::rtl::OUString         sStyleName;
};

//______________________________________________________________________________

class XMLPageExport : public UniRefBase
{
    SvXMLExport& rExport;

    const ::rtl::OUString sIsPhysical;
    const ::rtl::OUString sFollowStyle;

    ::com::sun::star::uno::Reference<
        ::com::sun::star::container::XIndexAccess > xPageStyles;

    ::std::vector< XMLPageExportNameEntry > aNameVector;
    sal_Bool findPageMasterName( const ::rtl::OUString& rStyleName, ::rtl::OUString& rPMName ) const;

    UniReference < XMLPropertyHandlerFactory > xPageMasterPropHdlFactory;
    UniReference < XMLPropertySetMapper > xPageMasterPropSetMapper;
    UniReference < SvXMLExportPropertyMapper > xPageMasterExportPropMapper;

protected:

    SvXMLExport& GetExport() { return rExport; }

    virtual void collectPageMasterAutoStyle(
                const ::com::sun::star::uno::Reference <
                    ::com::sun::star::beans::XPropertySet > & rPropSet,
                ::rtl::OUString& rPageMasterName );

    virtual void exportMasterPageContent(
                const ::com::sun::star::uno::Reference <
                    ::com::sun::star::beans::XPropertySet > & rPropSet,
                 sal_Bool bAutoStyles );

    sal_Bool exportStyle(
                const ::com::sun::star::uno::Reference<
                    ::com::sun::star::style::XStyle >& rStyle,
                sal_Bool bAutoStyles );

    void exportStyles( sal_Bool bUsed, sal_Bool bAutoStyles );

public:
    XMLPageExport( SvXMLExport& rExp );
    ~XMLPageExport();

    void    collectAutoStyles( sal_Bool bUsed )     { exportStyles( bUsed, sal_True ); }
    void    exportAutoStyles();
    void    exportMasterStyles( sal_Bool bUsed )    { exportStyles( bUsed, sal_False ); }
};

}//end of namespace binfilter
#endif  //  _XMLOFF_XMLTEXTMASTERPAGEEXPORT_HXX

