/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xmloff_ximppage.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 01:46:55 $
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

#pragma hdrstop



#ifndef _XMLOFF_XMLNMSPE_HXX
#include "xmlnmspe.hxx"
#endif



#ifndef _XMLOFF_ANIMIMP_HXX
#include "animimp.hxx"
#endif



#ifndef _XIMPSTYLE_HXX
#include "ximpstyl.hxx"
#endif
namespace binfilter {

using namespace ::rtl;
using namespace ::com::sun::star;
using namespace ::binfilter::xmloff::token;

//////////////////////////////////////////////////////////////////////////////

TYPEINIT1( SdXMLGenericPageContext, SvXMLImportContext );

SdXMLGenericPageContext::SdXMLGenericPageContext(
    SvXMLImport& rImport,
    USHORT nPrfx, const OUString& rLocalName,
    const uno::Reference< xml::sax::XAttributeList>& xAttrList,
    uno::Reference< drawing::XShapes >& rShapes)
:   SvXMLImportContext( rImport, nPrfx, rLocalName ),
    mxShapes( rShapes )
{
}

//////////////////////////////////////////////////////////////////////////////

SdXMLGenericPageContext::~SdXMLGenericPageContext()
{
}

//////////////////////////////////////////////////////////////////////////////

void SdXMLGenericPageContext::StartElement( const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& xAttrList )
{
    GetImport().GetShapeImport()->pushGroupForSorting( mxShapes );

#ifndef SVX_LIGHT
    if( GetImport().IsFormsSupported() )
        GetImport().GetFormImport()->startPage( uno::Reference< drawing::XDrawPage >::query( mxShapes ) );
#endif
}

//////////////////////////////////////////////////////////////////////////////

SvXMLImportContext* SdXMLGenericPageContext::CreateChildContext( USHORT nPrefix,
    const OUString& rLocalName,
    const uno::Reference< xml::sax::XAttributeList>& xAttrList )
{
    SvXMLImportContext* pContext = 0L;

    if( nPrefix == XML_NAMESPACE_PRESENTATION && IsXMLToken( rLocalName, XML_ANIMATIONS ) )
    {
        pContext = new XMLAnimationsContext( GetImport(), nPrefix, rLocalName, xAttrList );
    }
    else if( nPrefix == XML_NAMESPACE_OFFICE && IsXMLToken( rLocalName, XML_FORMS ) )
    {
#ifndef SVX_LIGHT
        if( GetImport().IsFormsSupported() )
            pContext = GetImport().GetFormImport()->createOfficeFormsContext( GetImport(), nPrefix, rLocalName );
#endif
    }
    else
    {
        // call GroupChildContext function at common ShapeImport
        pContext = GetImport().GetShapeImport()->CreateGroupChildContext(
            GetImport(), nPrefix, rLocalName, xAttrList, mxShapes);
    }

    // call parent when no own context was created
    if(!pContext)
        pContext = SvXMLImportContext::CreateChildContext(nPrefix, rLocalName, xAttrList);

    return pContext;
}

//////////////////////////////////////////////////////////////////////////////

void SdXMLGenericPageContext::EndElement()
{
    GetImport().GetShapeImport()->popGroupAndSort();

#ifndef SVX_LIGHT
    if( GetImport().IsFormsSupported() )
        GetImport().GetFormImport()->endPage();
#endif
}

void SdXMLGenericPageContext::SetLayout()
{
    // set PresentationPageLayout?
    if(GetSdImport().IsImpress() && maPageLayoutName.getLength())
    {
        sal_Int32 nType = -1;

        const SvXMLImportContext* pContext = GetSdImport().GetShapeImport()->GetStylesContext();

        if( pContext && pContext->ISA( SvXMLStyleContext ) )
        {
            const SdXMLStylesContext* pStyles = (SdXMLStylesContext*)pContext;
            if(pStyles)
            {
                const SvXMLStyleContext* pStyle = pStyles->FindStyleChildContext( XML_STYLE_FAMILY_SD_PRESENTATIONPAGELAYOUT_ID, maPageLayoutName);

                if(pStyle && pStyle->ISA(SdXMLPresentationPageLayoutContext))
                {
                    SdXMLPresentationPageLayoutContext* pLayout = (SdXMLPresentationPageLayoutContext*)pStyle;
                    nType = pLayout->GetTypeId();
                }
            }

        }
        if( -1 == nType )
        {
            uno::Reference< container::XNameAccess > xPageLayouts( GetSdImport().getPageLayouts() );
            if( xPageLayouts.is() )
            {
                if( xPageLayouts->hasByName( maPageLayoutName ) )
                    xPageLayouts->getByName( maPageLayoutName ) >>= nType;
            }

        }

        if( -1 != nType )
        {
            uno::Reference <beans::XPropertySet> xPropSet(mxShapes, uno::UNO_QUERY);
            if(xPropSet.is())
            {
                OUString aPropName(RTL_CONSTASCII_USTRINGPARAM("Layout"));
                uno::Reference< beans::XPropertySetInfo > xInfo( xPropSet->getPropertySetInfo() );
                if( xInfo.is() && xInfo->hasPropertyByName( aPropName ) )
                    xPropSet->setPropertyValue(aPropName, uno::makeAny( (sal_Int16)nType ) );
            }
        }
    }
}

void SdXMLGenericPageContext::DeleteAllShapes()
{
    // now delete all up-to-now contained shapes; they have been created
    // when setting the presentation page layout.
    while(mxShapes->getCount())
    {
        uno::Reference< drawing::XShape > xShape;
        uno::Any aAny(mxShapes->getByIndex(0L));

        aAny >>= xShape;

        if(xShape.is())
        {
            mxShapes->remove(xShape);
        }
    }
}

void SdXMLGenericPageContext::SetPageMaster( OUString& rsPageMasterName )
{
    if( GetSdImport().GetShapeImport()->GetStylesContext() )
    {
        // look for PageMaster with this name

        // #80012# GetStylesContext() replaced with GetAutoStylesContext()
        const SvXMLStylesContext* pAutoStyles = GetSdImport().GetShapeImport()->GetAutoStylesContext();

        const SvXMLStyleContext* pStyle = pAutoStyles ? pAutoStyles->FindStyleChildContext(XML_STYLE_FAMILY_SD_PAGEMASTERCONEXT_ID, rsPageMasterName) : NULL;

        if(pStyle && pStyle->ISA(SdXMLPageMasterContext))
        {
            const SdXMLPageMasterContext* pPageMaster = (SdXMLPageMasterContext*)pStyle;
            const SdXMLPageMasterStyleContext* pPageMasterContext = pPageMaster->GetPageMasterStyle();

            if(pPageMasterContext)
            {
                uno::Reference< drawing::XDrawPage > xMasterPage(GetLocalShapesContext(), uno::UNO_QUERY);
                if(xMasterPage.is())
                {
                    // set sizes for this masterpage
                    uno::Reference <beans::XPropertySet> xPropSet(xMasterPage, uno::UNO_QUERY);
                    if(xPropSet.is())
                    {
                        uno::Any aAny;

                        aAny <<= pPageMasterContext->GetBorderBottom();
                        xPropSet->setPropertyValue(
                            OUString(RTL_CONSTASCII_USTRINGPARAM("BorderBottom")), aAny);

                        aAny <<= pPageMasterContext->GetBorderLeft();
                        xPropSet->setPropertyValue(
                            OUString(RTL_CONSTASCII_USTRINGPARAM("BorderLeft")), aAny);

                        aAny <<= pPageMasterContext->GetBorderRight();
                        xPropSet->setPropertyValue(
                            OUString(RTL_CONSTASCII_USTRINGPARAM("BorderRight")), aAny);

                        aAny <<= pPageMasterContext->GetBorderTop();
                        xPropSet->setPropertyValue(
                            OUString(RTL_CONSTASCII_USTRINGPARAM("BorderTop")), aAny);

                        aAny <<= pPageMasterContext->GetWidth();
                        xPropSet->setPropertyValue(
                            OUString(RTL_CONSTASCII_USTRINGPARAM("Width")), aAny);

                        aAny <<= pPageMasterContext->GetHeight();
                        xPropSet->setPropertyValue(
                            OUString(RTL_CONSTASCII_USTRINGPARAM("Height")), aAny);

                        aAny <<= pPageMasterContext->GetOrientation();
                        xPropSet->setPropertyValue(
                            OUString(RTL_CONSTASCII_USTRINGPARAM("Orientation")), aAny);
                    }
                }
            }
        }

    }
}
}//end of namespace binfilter
