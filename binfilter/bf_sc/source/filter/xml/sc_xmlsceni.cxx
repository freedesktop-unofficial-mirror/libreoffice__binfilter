/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sc_xmlsceni.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 11:00:18 $
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

#ifdef PCH
#endif

#ifdef _MSC_VER
#pragma hdrstop
#endif

// INCLUDE ---------------------------------------------------------------

#include "document.hxx"
#include "xmlimprt.hxx"
#include "xmlsceni.hxx"
#include "attrib.hxx"

#ifndef _SC_XMLCONVERTER_HXX
#include "XMLConverter.hxx"
#endif

#include <bf_xmloff/nmspmap.hxx>
#ifndef _XMLOFF_XMLUCONV_HXX
#include <bf_xmloff/xmluconv.hxx>
#endif
namespace binfilter {

using namespace ::com::sun::star;
using namespace xmloff::token;

//------------------------------------------------------------------

ScXMLTableScenarioContext::ScXMLTableScenarioContext(
        ScXMLImport& rImport,
        USHORT nPrfx,
        const OUString& rLName,
        const uno::Reference< xml::sax::XAttributeList >& xAttrList ):
    SvXMLImportContext( rImport, nPrfx, rLName ),
    aBorderColor( COL_BLACK ),
    bDisplayBorder( sal_True ),
    bCopyBack( sal_True ),
    bCopyStyles( sal_True ),
    bCopyFormulas( sal_True ),
    bIsActive( sal_False )
{
    rImport.LockSolarMutex();
    sal_Int16 nAttrCount = xAttrList.is() ? xAttrList->getLength() : 0;
    const SvXMLTokenMap& rAttrTokenMap = GetScImport().GetTableScenarioAttrTokenMap();
    for( sal_Int16 i = 0; i < nAttrCount; i++ )
    {
        OUString sAttrName = xAttrList->getNameByIndex( i );
        OUString aLocalName;
        USHORT nPrefix = GetScImport().GetNamespaceMap().GetKeyByAttrName(
                                            sAttrName, &aLocalName );
        OUString sValue = xAttrList->getValueByIndex( i );

        switch( rAttrTokenMap.Get( nPrefix, aLocalName ) )
        {
            case XML_TOK_TABLE_SCENARIO_ATTR_DISPLAY_BORDER:
            {
                bDisplayBorder = IsXMLToken(sValue, XML_TRUE);
            }
            break;
            case XML_TOK_TABLE_SCENARIO_ATTR_BORDER_COLOR:
            {
                SvXMLUnitConverter::convertColor(aBorderColor, sValue);
            }
            break;
            case XML_TOK_TABLE_SCENARIO_ATTR_COPY_BACK:
            {
                bCopyBack = IsXMLToken(sValue, XML_TRUE);
            }
            break;
            case XML_TOK_TABLE_SCENARIO_ATTR_COPY_STYLES:
            {
                bCopyStyles = IsXMLToken(sValue, XML_TRUE);
            }
            break;
            case XML_TOK_TABLE_SCENARIO_ATTR_COPY_FORMULAS:
            {
                bCopyFormulas = IsXMLToken(sValue, XML_TRUE);
            }
            break;
            case XML_TOK_TABLE_SCENARIO_ATTR_IS_ACTIVE:
            {
                bIsActive = IsXMLToken(sValue, XML_TRUE);
            }
            break;
            case XML_TOK_TABLE_SCENARIO_ATTR_SCENARIO_RANGES:
            {
                ScXMLConverter::GetRangeListFromString(
                    aScenarioRanges, sValue, GetScImport().GetDocument() );
            }
            break;
            case XML_TOK_TABLE_SCENARIO_ATTR_COMMENT:
            {
                sComment = sValue;
            }
            break;
        }
    }
}

ScXMLTableScenarioContext::~ScXMLTableScenarioContext()
{
    GetScImport().UnlockSolarMutex();
}

SvXMLImportContext *ScXMLTableScenarioContext::CreateChildContext(
        USHORT nPrefix,
        const OUString& rLName,
        const uno::Reference< xml::sax::XAttributeList >& xAttrList )
{
    return new SvXMLImportContext( GetImport(), nPrefix, rLName );
}

void ScXMLTableScenarioContext::EndElement()
{
    sal_Int16   nCurrTable( GetScImport().GetTables().GetCurrentSheet() );
    ScDocument* pDoc = GetScImport().GetDocument();
    if (pDoc)
    {
        pDoc->SetScenario( nCurrTable, TRUE );
        USHORT nFlags( 0 );
        if( bDisplayBorder )
            nFlags |= SC_SCENARIO_SHOWFRAME;
        if( bCopyBack )
            nFlags |= SC_SCENARIO_TWOWAY;
        if( bCopyStyles )
            nFlags |= SC_SCENARIO_ATTRIB;
        if( !bCopyFormulas )
            nFlags |= SC_SCENARIO_VALUE;
        pDoc->SetScenarioData( nCurrTable, String( sComment ), aBorderColor, nFlags );
        for( sal_Int32 i = 0; i < static_cast<sal_Int32>(aScenarioRanges.Count()); i++ )
        {
            ScRange* pRange = aScenarioRanges.GetObject( i );
            if( pRange )
                pDoc->ApplyFlagsTab( pRange->aStart.Col(), pRange->aStart.Row(),
                    pRange->aEnd.Col(), pRange->aEnd.Row(), nCurrTable, SC_MF_SCENARIO );
        }
        pDoc->SetActiveScenario( nCurrTable, bIsActive );
    }
}

}
