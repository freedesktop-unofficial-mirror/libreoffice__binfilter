/*************************************************************************
 *
 *  $RCSfile: SettingsExportHelper.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: aw $ $Date: 2003-12-05 09:17:50 $
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

#ifndef _XMLOFF_SETTINGSEXPORTHELPER_HXX
#define _XMLOFF_SETTINGSEXPORTHELPER_HXX

#ifndef _COM_SUN_STAR_AWT_RECTANGLE_HPP_
#include <com/sun/star/awt/Rectangle.hpp>
#endif
#ifndef _COM_SUN_STAR_FORMULA_SYMBOLDESCRIPTOR_HPP_
#include <com/sun/star/formula/SymbolDescriptor.hpp>
#endif

#ifndef _XMLOFF_XMLEXP_HXX
#include <bf_xmloff/xmlexp.hxx>
#endif

namespace com
{
    namespace sun { namespace star {
        namespace container { class XNameAccess; class XIndexAccess; }
        namespace util { struct DateTime; }
    } }
}
namespace binfilter {

class XMLSettingsExportHelper
{
    SvXMLExport&    rExport;

    void CallTypeFunction(const ::com::sun::star::uno::Any& rAny,
                        const ::rtl::OUString& rName) const;

    void exportBool(const sal_Bool bValue, const ::rtl::OUString& rName) const;
    void exportByte(const sal_Int8 nValue, const ::rtl::OUString& rName) const;
    void exportShort(const sal_Int16 nValue, const ::rtl::OUString& rName) const;
    void exportInt(const sal_Int32 nValue, const ::rtl::OUString& rName) const;
    void exportLong(const sal_Int64 nValue, const ::rtl::OUString& rName) const;
    void exportDouble(const double fValue, const ::rtl::OUString& rName) const;
    void exportString(const ::rtl::OUString& sValue, const ::rtl::OUString& rName) const;
    void exportDateTime(const ::com::sun::star::util::DateTime& aValue, const ::rtl::OUString& rName) const;
    void exportSequencePropertyValue(
        const ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue>& aProps,
        const ::rtl::OUString& rName) const;
    void exportbase64Binary(
        const ::com::sun::star::uno::Sequence<sal_Int8>& aProps,
        const ::rtl::OUString& rName) const;
    void exportMapEntry(const ::com::sun::star::uno::Any& rAny,
                        const ::rtl::OUString& rName,
                        const sal_Bool bNameAccess) const;
    void exportNameAccess(
        const ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameAccess>& aNamed,
        const ::rtl::OUString& rName) const;
    void exportIndexAccess(
        const ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexAccess> aIndexed,
        const ::rtl::OUString rName) const;

    void exportSymbolDescriptors(
                    const ::com::sun::star::uno::Sequence < ::com::sun::star::formula::SymbolDescriptor > &rProps,
                    const ::rtl::OUString rName) const;
    void exportForbiddenCharacters(
                    const ::com::sun::star::uno::Any &rAny,
                    const ::rtl::OUString rName) const;

public:
    XMLSettingsExportHelper(SvXMLExport& rExport);
    ~XMLSettingsExportHelper();

    void exportSettings(
        const ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue>& aProps,
        const ::rtl::OUString& rName) const;
};

}//end of namespace binfilter
#endif

