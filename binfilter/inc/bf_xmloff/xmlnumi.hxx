/*************************************************************************
 *
 *  $RCSfile: xmlnumi.hxx,v $
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

#ifndef _XMLOFF_XMLNUMI_HXX
#define _XMLOFF_XMLNUMI_HXX

#ifndef _COM_SUN_STAR_CONTAINER_XINDEXREPLACE_HPP_
#include <com/sun/star/container/XIndexReplace.hpp>
#endif

#include <bf_xmloff/xmlstyle.hxx>

#ifndef _COM_SUN_STAR_STYLE_NUMBERINGTYPE_HPP_
#include <com/sun/star/style/NumberingType.hpp>
#endif

namespace com { namespace sun { namespace star { namespace frame { class XModel; } } } }
namespace binfilter {
class SvI18NMap;
class SvxXMLListStyle_Impl;

class SvxXMLListStyleContext : public SvXMLStyleContext
{
    const ::rtl::OUString       sIsPhysical;
    const ::rtl::OUString       sNumberingRules;
    const ::rtl::OUString       sName;
    const ::rtl::OUString       sIsContinuousNumbering;
    const ::rtl::OUString       sIsNumbering;

    ::com::sun::star::uno::Reference <
        ::com::sun::star::container::XIndexReplace > xNumRules;

    SvxXMLListStyle_Impl        *pLevelStyles;

    sal_Int16                   nLevels;
    sal_Bool                    bConsecutive : 1;
    sal_Bool                    bOutline : 1;

protected:

    virtual void SetAttribute( sal_uInt16 nPrefixKey,
                               const ::rtl::OUString& rLocalName,
                               const ::rtl::OUString& rValue );

public:

    TYPEINFO();

    SvxXMLListStyleContext(
            SvXMLImport& rImport, sal_uInt16 nPrfx,
            const ::rtl::OUString& rLName,
            const ::com::sun::star::uno::Reference<
                    ::com::sun::star::xml::sax::XAttributeList >& xAttrList,
            sal_Bool bOutl=sal_False );

    virtual ~SvxXMLListStyleContext();

    virtual SvXMLImportContext *CreateChildContext(
            sal_uInt16 nPrefix,
            const ::rtl::OUString& rLocalName,
            const ::com::sun::star::uno::Reference<
                    ::com::sun::star::xml::sax::XAttributeList >& xAttrList );

    void FillUnoNumRule(
            const ::com::sun::star::uno::Reference<
                    ::com::sun::star::container::XIndexReplace > & rNumRule,
            const SvI18NMap *pI18NMap ) const;

    const ::com::sun::star::uno::Reference <
        ::com::sun::star::container::XIndexReplace >& GetNumRules() const
        { return xNumRules; }
    sal_Bool IsOutline() const { return bOutline; }
    sal_Bool IsConsecutive() const { return bConsecutive; }
    sal_Int16 GetLevels() const { return nLevels; }

    static ::com::sun::star::uno::Reference <
        ::com::sun::star::container::XIndexReplace >
    SvxXMLListStyleContext::CreateNumRule(
        const ::com::sun::star::uno::Reference <
            ::com::sun::star::frame::XModel > & rModel );

    static void SvxXMLListStyleContext::SetDefaultStyle(
        const ::com::sun::star::uno::Reference <
            ::com::sun::star::container::XIndexReplace > & rNumRule,
        sal_Int16 nLevel,
        sal_Bool bOrdered );

#if SUPD < 627
    static sal_Int16 GetNumType( const ::rtl::OUString& rNumFmt,
            const ::rtl::OUString& rLetterSync,
            sal_Int16 eDflt = ::com::sun::star::style::NumberingType::ARABIC,
            sal_Bool bNumberNone = sal_False );
#endif

    virtual void CreateAndInsertLate( sal_Bool bOverwrite );

    void CreateAndInsertAuto() const;
};

}//end of namespace binfilter
#endif  //  _XMLOFF_XMLNUMI_HXX

