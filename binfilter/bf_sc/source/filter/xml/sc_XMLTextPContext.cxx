/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sc_XMLTextPContext.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 10:56:25 $
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

#ifndef _SC_XMLTEXTPCONTEXT_HXX
#include "XMLTextPContext.hxx"
#endif
#ifndef SC_XMLIMPRT_HXX
#include "xmlimprt.hxx"
#endif
#ifndef SC_XMLCELLI_HXX
#include "xmlcelli.hxx"
#endif

#ifndef _XMLOFF_XMLNMSPE_HXX
#include <bf_xmloff/xmlnmspe.hxx>
#endif
#ifndef _XMLOFF_NMSPMAP_HXX
#include <bf_xmloff/nmspmap.hxx>
#endif

namespace binfilter {

using namespace ::com::sun::star;
using namespace xmloff::token;

class ScXMLTextTContext : public SvXMLImportContext
{
    const ScXMLImport& GetScImport() const { return (const ScXMLImport&)GetImport(); }
    ScXMLImport& GetScImport() { return (ScXMLImport&)GetImport(); }
public:
    ScXMLTextTContext( ScXMLImport& rImport, USHORT nPrfx,
                        const ::rtl::OUString& rLName,
                        const ::com::sun::star::uno::Reference<
                                        ::com::sun::star::xml::sax::XAttributeList>& xAttrList,
                        ScXMLTextPContext* pTextPContext);

    virtual ~ScXMLTextTContext();
};


ScXMLTextTContext::ScXMLTextTContext( ScXMLImport& rImport,
                                      USHORT nPrfx,
                                      const ::rtl::OUString& rLName,
                                      const ::com::sun::star::uno::Reference<
                                      ::com::sun::star::xml::sax::XAttributeList>& xAttrList,
                                      ScXMLTextPContext* pTextPContext) :
    SvXMLImportContext( rImport, nPrfx, rLName )
{
    if (pTextPContext)
    {
        sal_Int16 nAttrCount = xAttrList.is() ? xAttrList->getLength() : 0;
        ::rtl::OUString aLocalName;
        ::rtl::OUString sValue;
        sal_Int32 nCount(1);
        for( sal_Int16 i=0; i < nAttrCount; i++ )
        {
            sal_uInt16 nPrefix = GetScImport().GetNamespaceMap().GetKeyByAttrName(
                                                xAttrList->getNameByIndex( i ), &aLocalName );
            sValue = xAttrList->getValueByIndex( i );

            if ((nPrefix == XML_NAMESPACE_TEXT) && IsXMLToken(aLocalName, XML_C))
                nCount = sValue.toInt32();
        }
        pTextPContext->AddSpaces(nCount);
    }
}

ScXMLTextTContext::~ScXMLTextTContext()
{
}

//------------------------------------------------------------------

ScXMLTextPContext::ScXMLTextPContext( ScXMLImport& rImport,
                                      USHORT nPrfx,
                                      const ::rtl::OUString& rLName,
                                      const ::com::sun::star::uno::Reference<
                                      ::com::sun::star::xml::sax::XAttributeList>& xTempAttrList,
                                      ScXMLTableRowCellContext* pTempCellContext) :
    SvXMLImportContext( rImport, nPrfx, rLName ),
    pTextPContext(NULL),
    pCellContext(pTempCellContext),
    sOUText(),
    sLName(rLName),
    xAttrList(xTempAttrList),
    nPrefix(nPrfx),
    bIsOwn(sal_True)
{
    // here are no attributes
}

ScXMLTextPContext::~ScXMLTextPContext()
{
    if (pTextPContext)
        delete pTextPContext;
}

void ScXMLTextPContext::AddSpaces(sal_Int32 nSpaceCount)
{
    sal_Char* pChars = new sal_Char[nSpaceCount];
    memset(pChars, ' ', nSpaceCount);
    sOUText.appendAscii(pChars, nSpaceCount);
}

SvXMLImportContext *ScXMLTextPContext::CreateChildContext( USHORT nTempPrefix,
                                            const ::rtl::OUString& rLName,
                                            const ::com::sun::star::uno::Reference<
                                          ::com::sun::star::xml::sax::XAttributeList>& xTempAttrList )
{
    SvXMLImportContext *pContext = NULL;
    if (!pTextPContext &&
        (nTempPrefix == XML_NAMESPACE_TEXT) &&
        IsXMLToken(rLName, XML_S))
        pContext = new ScXMLTextTContext( GetScImport(), nTempPrefix, rLName, xTempAttrList, this);
    else
    {
        if (!pTextPContext)
        {
            pCellContext->SetCursorOnTextImport(sOUText.makeStringAndClear());
            pTextPContext = GetScImport().GetTextImport()->CreateTextChildContext(
                                    GetScImport(), nPrefix, sLName, xAttrList);
        }
        if (pTextPContext)
            pContext = pTextPContext->CreateChildContext(nTempPrefix, rLName, xTempAttrList);
    }

    if( !pContext )
        pContext = new SvXMLImportContext( GetScImport(), nTempPrefix, rLName );

    return pContext;
}

void ScXMLTextPContext::Characters( const ::rtl::OUString& rChars )
{
    if (!pTextPContext)
        sOUText.append(rChars);
    else
        pTextPContext->Characters(rChars);
}

void ScXMLTextPContext::EndElement()
{
    if (!pTextPContext)
        pCellContext->SetString(sOUText.makeStringAndClear());
//      GetScImport().GetTextImport()->GetCursor()->setString(sOUText.makeStringAndClear());
    else
    {
        pTextPContext->EndElement();
        GetScImport().SetRemoveLastChar(sal_True);
    }
}

}
