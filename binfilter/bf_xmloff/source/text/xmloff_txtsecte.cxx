/*************************************************************************
 *
 *  $RCSfile: xmloff_txtsecte.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 20:36:33 $
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

// auto strip #ifndef _XMLOFF_TXTPARAE_HXX
// auto strip #include "txtparae.hxx"
// auto strip #endif

// auto strip #ifndef _TOOLS_DEBUG_HXX
// auto strip #include <tools/debug.hxx>
// auto strip #endif

// auto strip #ifndef _RTL_USTRING_HXX_
// auto strip #include <rtl/ustring.hxx>
// auto strip #endif

// auto strip #ifndef _RTL_USTRBUF_HXX_
// auto strip #include <rtl/ustrbuf.hxx>
// auto strip #endif

#include <vector>


// auto strip #ifndef _COM_SUN_STAR_LANG_XSERVICEINFO_HPP_
// auto strip #include <com/sun/star/lang/XServiceInfo.hpp>
// auto strip #endif

// auto strip #ifndef _COM_SUN_STAR_CONTAINER_XINDEXREPLACE_HPP_
// auto strip #include <com/sun/star/container/XIndexReplace.hpp>
// auto strip #endif

// auto strip #ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
// auto strip #include <com/sun/star/beans/XPropertySet.hpp>
// auto strip #endif

// auto strip #ifndef _COM_SUN_STAR_BEANS_PROPERTYVALUE_HPP_
// auto strip #include <com/sun/star/beans/PropertyValue.hpp>
// auto strip #endif

#ifndef _COM_SUN_STAR_BEANS_PROPERTYVALUES_HPP_
#include <com/sun/star/beans/PropertyValues.hpp>
#endif

// auto strip #ifndef _COM_SUN_STAR_BEANS_PROPERTYSTATE_HPP_
// auto strip #include <com/sun/star/beans/PropertyState.hpp>
// auto strip #endif

// auto strip #ifndef _COM_SUN_STAR_TEXT_XTEXT_HPP_
// auto strip #include <com/sun/star/text/XText.hpp>
// auto strip #endif

#ifndef _COM_SUN_STAR_TEXT_XTEXTSECTION_HPP_
#include <com/sun/star/text/XTextSection.hpp>
#endif

// auto strip #ifndef _COM_SUN_STAR_TEXT_SECTIONFILELINK_HPP_
// auto strip #include <com/sun/star/text/SectionFileLink.hpp>
// auto strip #endif

// auto strip #ifndef _COM_SUN_STAR_CONTAINER_XNAMED_HPP_
// auto strip #include <com/sun/star/container/XNamed.hpp>
// auto strip #endif

// auto strip #ifndef _COM_SUN_STAR_TEXT_XDOCUMENTINDEX_HPP_
// auto strip #include <com/sun/star/text/XDocumentIndex.hpp>
// auto strip #endif

// auto strip #ifndef _XMLOFF_XMLNMSPE_HXX
// auto strip #include "xmlnmspe.hxx"
// auto strip #endif

// auto strip #ifndef _XMLOFF_FAMILIES_HXX_
// auto strip #include "families.hxx"
// auto strip #endif

// auto strip #ifndef _XMLOFF_XMLUCONV_HXX
// auto strip #include "xmluconv.hxx"
// auto strip #endif

// auto strip #ifndef _XMLOFF_NMSPMAP_HXX
// auto strip #include "nmspmap.hxx"
// auto strip #endif

#ifndef _XMLOFF_XMLEXP_HXX
#include "xmlexp.hxx"
#endif

// auto strip #ifndef _XMLOFF_XMLTKMAP_HXX
// auto strip #include "xmltkmap.hxx"
// auto strip #endif

#ifndef _XMLOFF_XMLTEXTNUMRULEINFO_HXX
#include "XMLTextNumRuleInfo.hxx"
#endif

#ifndef _XMLOFF_XMLSECTIONEXPORT_HXX_
#include "XMLSectionExport.hxx"
#endif

#ifndef _XMLOFF_XMLREDLINEEXPORT_HXX
#include "XMLRedlineExport.hxx"
#endif
#ifndef _XMLOFF_MULTIPROPERTYSETHELPER_HXX
#include "MultiPropertySetHelper.hxx"
#endif
namespace binfilter {

using namespace ::com::sun::star;
using namespace ::com::sun::star::text;
using namespace ::com::sun::star::uno;
using namespace ::std;

using ::rtl::OUString;
using ::rtl::OUStringBuffer;
using ::com::sun::star::beans::XPropertySet;
using ::com::sun::star::beans::PropertyValue;
using ::com::sun::star::beans::PropertyValues;
using ::com::sun::star::beans::PropertyState;
using ::com::sun::star::container::XIndexReplace;
using ::com::sun::star::container::XNamed;
using ::com::sun::star::lang::XServiceInfo;

Reference<XText> lcl_findXText(const Reference<XTextSection>& rSect)
{
    Reference<XText> xText;

    Reference<XTextContent> xTextContent(rSect, UNO_QUERY);
    if (xTextContent.is())
    {
        xText = xTextContent->getAnchor()->getText();
    }

    return xText;
}

void XMLTextParagraphExport::exportListAndSectionChange(
    Reference<XTextSection> & rPrevSection,
    const Reference<XTextContent> & rNextSectionContent,
    const XMLTextNumRuleInfo& rPrevRule,
    const XMLTextNumRuleInfo& rNextRule,
    sal_Bool bAutoStyles)
{
    Reference<XTextSection> xNextSection;

    // first: get current XTextSection
    Reference<XPropertySet> xPropSet(rNextSectionContent, UNO_QUERY);
    if (xPropSet.is())
    {
        if (xPropSet->getPropertySetInfo()->hasPropertyByName(sTextSection))
        {
            Any aAny = xPropSet->getPropertyValue(sTextSection);
            aAny >>= xNextSection;
        }
        // else: no current section
    }

    exportListAndSectionChange(rPrevSection, xNextSection,
                               rPrevRule, rNextRule, bAutoStyles);
}

void XMLTextParagraphExport::exportListAndSectionChange(
    Reference<XTextSection> & rPrevSection,
    MultiPropertySetHelper& rPropSetHelper,
    sal_Int16 nTextSectionId,
    const Reference<XTextContent> & rNextSectionContent,
    const XMLTextNumRuleInfo& rPrevRule,
    const XMLTextNumRuleInfo& rNextRule,
    sal_Bool bAutoStyles)
{
    Reference<XTextSection> xNextSection;

    // first: get current XTextSection
    Reference<XPropertySet> xPropSet(rNextSectionContent, UNO_QUERY);
    if (xPropSet.is())
    {
        if( !rPropSetHelper.checkedProperties() )
            rPropSetHelper.hasProperties( xPropSet->getPropertySetInfo() );
        if( rPropSetHelper.hasProperty( nTextSectionId ))
        {
            Any aAny = rPropSetHelper.getValue( nTextSectionId , xPropSet,
                                                    sal_True );
            aAny >>= xNextSection;
        }
        // else: no current section
    }

    exportListAndSectionChange(rPrevSection, xNextSection,
                               rPrevRule, rNextRule, bAutoStyles);
}

void XMLTextParagraphExport::exportListAndSectionChange(
    Reference<XTextSection> & rPrevSection,
    const Reference<XTextSection> & rNextSection,
    const XMLTextNumRuleInfo& rPrevRule,
    const XMLTextNumRuleInfo& rNextRule,
    sal_Bool bAutoStyles)
{
    // old != new? -> maybe we have to start or end a new section
    if (rPrevSection != rNextSection)
    {
        // a new section started, or an old one gets closed!

        // close old list
        XMLTextNumRuleInfo aEmptyNumRule;
        if ( !bAutoStyles )
            exportListChange(rPrevRule, aEmptyNumRule);

        // Build stacks of old and new sections
        // Sections on top of mute sections should not be on the stack
        vector<Reference<XTextSection> > aOldStack;
        Reference<XTextSection> aCurrent = rPrevSection;
        while(aCurrent.is())
        {
            // if we have a mute section, ignore all its children
            // (all previous ones)
            if (pSectionExport->IsMuteSection(aCurrent))
                aOldStack.clear();

            aOldStack.push_back(aCurrent);
            aCurrent = aCurrent->getParentSection();
        }

        vector<Reference<XTextSection> > aNewStack;
        aCurrent = rNextSection;
        sal_Bool bMute = sal_False;
        while(aCurrent.is())
        {
            // if we have a mute section, ignore all its children
            // (all previous ones)
            if (pSectionExport->IsMuteSection(aCurrent))
            {
                aNewStack.clear();
                bMute = sal_True;
            }

            aNewStack.push_back(aCurrent);
            aCurrent = aCurrent->getParentSection();
        }

        // compare the two stacks
        vector<Reference<XTextSection> > ::reverse_iterator aOld =
            aOldStack.rbegin();
        vector<Reference<XTextSection> > ::reverse_iterator aNew =
            aNewStack.rbegin();
        // compare bottom sections and skip equal section
        while ( (aOld != aOldStack.rend()) &&
                (aNew != aNewStack.rend()) &&
                (*aOld) == (*aNew) )
        {
            aOld++;
            aNew++;
        }

        // close all elements of aOld ...
        // (order: newest to oldest)
        if (aOld != aOldStack.rend())
        {
            vector<Reference<XTextSection> > ::iterator aOldForward =
                aOldStack.begin();
            while ((aOldForward != aOldStack.end()) &&
                   (*aOldForward != *aOld))
            {
                if ( !bAutoStyles && (NULL != pRedlineExport) )
                    pRedlineExport->ExportStartOrEndRedline(*aOldForward,
                                                                sal_False);
                pSectionExport->ExportSectionEnd(*aOldForward, bAutoStyles);
                aOldForward++;
            }
            if (aOldForward != aOldStack.end())
            {
                if ( !bAutoStyles && (NULL != pRedlineExport) )
                    pRedlineExport->ExportStartOrEndRedline(*aOldForward,
                                                            sal_False);
                pSectionExport->ExportSectionEnd(*aOldForward, bAutoStyles);
            }
        }

        // ...then open all of aNew
        // (order: oldest to newest)
        while (aNew != aNewStack.rend())
        {
            if ( !bAutoStyles && (NULL != pRedlineExport) )
                pRedlineExport->ExportStartOrEndRedline(*aNew, sal_True);
            pSectionExport->ExportSectionStart(*aNew, bAutoStyles);
            aNew++;
        }

        // start new list
        if ( !bAutoStyles && !bMute )
            exportListChange(aEmptyNumRule, rNextRule);
    }
    else
    {
        // list change, if sections have not changed
        if ( !bAutoStyles )
            exportListChange(rPrevRule, rNextRule);
    }

    // save old section (old numRule gets saved in calling method)
    rPrevSection = rNextSection;
}

}//end of namespace binfilter
