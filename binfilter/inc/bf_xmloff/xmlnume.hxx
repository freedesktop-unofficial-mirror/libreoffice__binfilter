/*************************************************************************
 *
 *  $RCSfile: xmlnume.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: aw $ $Date: 2003-12-05 09:18:07 $
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

#ifndef _XMLOFF_XMLNUME_HXX
#define _XMLOFF_XMLNUME_HXX

#ifndef _RTL_USTRING_HXX_
#include <rtl/ustring.hxx>
#endif
#ifndef _VCL_MAPUNIT_HXX
#include <vcl/mapunit.hxx>
#endif

#ifndef _XMLOFF_ATTRLIST_HXX
#include <bf_xmloff/attrlist.hxx>
#endif

namespace com { namespace sun { namespace star {
    namespace style { class XStyle; }
    namespace container { class XIndexReplace; }
    namespace beans { struct PropertyValue; }
} } }
namespace binfilter {

class SvXMLNamespaceMap;
class SvXMLUnitConverter;
class SvXMLExportItemMapper;
class SvXMLExport;
class XMLTextListAutoStylePool;

class SvxXMLNumRuleExport
{
    SvXMLExport& rExport;
    const ::rtl::OUString sCDATA;
    const ::rtl::OUString sWS;
    const ::rtl::OUString sNumberingRules;
    const ::rtl::OUString sIsPhysical;
    const ::rtl::OUString sIsContinuousNumbering;

    void exportLevelStyles(
            const ::com::sun::star::uno::Reference<
                ::com::sun::star::container::XIndexReplace > & xNumRule,
            sal_Bool bOutline=sal_False );

    void exportLevelStyle(
            sal_Int32 nLevel,
            const ::com::sun::star::uno::Sequence<
                ::com::sun::star::beans::PropertyValue>& rProps,
            sal_Bool bOutline=sal_False );

protected:

    // This method may be overloaded to add attributes to the <list-style>
    // element.
    virtual void AddListStyleAttributes();

    sal_Bool exportStyle( const ::com::sun::star::uno::Reference<
                            ::com::sun::star::style::XStyle >& rStyle );
    void exportOutline();

    SvXMLExport& GetExport() { return rExport; }

     virtual ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexReplace >  GetUNONumRule() const;

public:

    SvxXMLNumRuleExport( SvXMLExport& rExport );
    virtual ~SvxXMLNumRuleExport();

    void exportStyles( sal_Bool bUsed,
                       XMLTextListAutoStylePool *pPool,
                       sal_Bool bExportChapterNumbering = sal_True );
    void exportNumberingRule(
            const ::rtl::OUString& rName,
            const ::com::sun::star::uno::Reference<
                ::com::sun::star::container::XIndexReplace > & xNumRule );

    void Export( const ::rtl::OUString& rOutline, sal_Bool bContNumbering );
    void ExportOutline();
#if SUPD < 627
    static const sal_Char *GetNumFormatValue( sal_Int16 eNumType );
    static const sal_Char *GetNumLetterSync( sal_Int16 eNumType );
#endif
};

}//end of namespace binfilter
#endif  //  _XMLOFF_XMLNUME_HXX

