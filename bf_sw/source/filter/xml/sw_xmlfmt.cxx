/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */


#ifdef _MSC_VER
#pragma hdrstop
#endif

#include <rtl/ustrbuf.hxx>

#include <tools/urlobj.hxx>

#ifndef _SVSTDARR_STRINGSSORT_DECL
#define _SVSTDARR_STRINGSSORT
#include <bf_svtools/svstdarr.hxx>
#endif

#include <bf_xmloff/nmspmap.hxx>

#include <format.hxx>

#include <osl/diagnose.h>

#include <fmtcol.hxx>
#include <hints.hxx>
#include <unoobj.hxx>

#include <poolfmt.hxx>
#include <charfmt.hxx>
#include <frmfmt.hxx>
#include <paratr.hxx>

#include <horiornt.hxx>

#include <doc.hxx>
#include "docary.hxx"
#include "unostyle.hxx"
#include "fmtpdsc.hxx"
#include "pagedesc.hxx"

#include <bf_xmloff/xmlnmspe.hxx>
#include <bf_xmloff/i18nmap.hxx>
#include <bf_xmloff/xmltkmap.hxx>
#include "xmlitem.hxx"
#include <bf_xmloff/xmlstyle.hxx>
#include <bf_xmloff/xmltoken.hxx>
#include <bf_xmloff/txtstyli.hxx>
#include <bf_xmloff/txtimp.hxx>
#include <bf_xmloff/families.hxx>
#include <bf_xmloff/XMLTextMasterStylesContext.hxx>
#include <bf_xmloff/XMLTextShapeStyleContext.hxx>
#include <bf_xmloff/XMLGraphicsDefaultStyle.hxx>

#include <numrule.hxx>
#include "xmlimp.hxx"
#include "xmltbli.hxx"
#include "cellatr.hxx"
#include <SwStyleNameMapper.hxx>
namespace binfilter {


using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::style;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::container;
using namespace ::binfilter::xmloff::token;

using rtl::OUString;
using rtl::OUStringBuffer;

class SwXMLConditionParser_Impl
{
    OUString sInput;

    sal_uInt32 nCondition;
    sal_uInt32 nSubCondition;

    sal_Int32 nPos;
    sal_Int32 nLength;

    inline sal_Bool SkipWS();
    inline sal_Bool MatchChar( sal_Unicode c );
    inline sal_Bool MatchName( OUString& rName );
    inline sal_Bool MatchNumber( sal_uInt32& rNumber );

public:

    SwXMLConditionParser_Impl( const OUString& rInp );

    sal_Bool IsValid() const { return 0 != nCondition; }

    sal_uInt32 GetCondition() const { return nCondition; }
    sal_uInt32 GetSubCondition() const { return nSubCondition; }
};

inline sal_Bool SwXMLConditionParser_Impl::SkipWS()
{
    while( nPos < nLength && ' ' == sInput[nPos] )
        nPos++;
    return sal_True;
}

inline sal_Bool SwXMLConditionParser_Impl::MatchChar( sal_Unicode c )
{
    sal_Bool bRet = sal_False;
    if( nPos < nLength && c == sInput[nPos] )
    {
        nPos++;
        bRet = sal_True;
    }
    return bRet;
}

inline sal_Bool SwXMLConditionParser_Impl::MatchName( OUString& rName )
{
    OUStringBuffer sBuffer( nLength );
    while( nPos < nLength &&
           ( ('a' <= sInput[nPos] && sInput[nPos] <= 'z') ||
              '-' == sInput[nPos] ) )
    {
        sBuffer.append( sInput[nPos] );
        nPos++;
    }
    rName = sBuffer.makeStringAndClear();
    return rName.getLength() > 0;
}

inline sal_Bool SwXMLConditionParser_Impl::MatchNumber( sal_uInt32& rNumber )
{
    OUStringBuffer sBuffer( nLength );
    while( nPos < nLength && '0' <= sInput[nPos] && sInput[nPos] <= '9' )
    {
        sBuffer.append( sInput[nPos] );
        nPos++;
    }

    OUString sNum( sBuffer.makeStringAndClear() );
    if( sNum.getLength() )
        rNumber = sNum.toInt32();
    return sNum.getLength() > 0;
}

SwXMLConditionParser_Impl::SwXMLConditionParser_Impl( const OUString& rInp ) :
    sInput( rInp ),
    nCondition( 0 ),
    nSubCondition( 0 ),
    nPos( 0 ),
    nLength( rInp.getLength() )
{
    OUString sFunc;
    sal_Bool bHasSub = sal_False;
    sal_uInt32 nSub = 0;
    sal_Bool bOK = SkipWS() && MatchName( sFunc ) && SkipWS() &&
               MatchChar( '(' ) && SkipWS() && MatchChar( ')' ) && SkipWS();
    if( bOK && MatchChar( '=' ) )
    {
        bOK = SkipWS() && MatchNumber( nSub ) && SkipWS();
        bHasSub = sal_True;
    }

    bOK &= nPos == nLength;

    if( bOK )
    {
        if( IsXMLToken( sFunc, XML_ENDNOTE ) && !bHasSub )
            nCondition = PARA_IN_ENDNOTE;
        else if( IsXMLToken( sFunc, XML_FOOTER ) && !bHasSub )
            nCondition = PARA_IN_FOOTER;
        else if( IsXMLToken( sFunc, XML_FOOTNOTE ) && !bHasSub )
            nCondition = PARA_IN_FOOTENOTE;
        else if( IsXMLToken( sFunc, XML_HEADER ) && !bHasSub )
            nCondition = PARA_IN_HEADER;
        else if( IsXMLToken( sFunc, XML_LIST_LEVEL) &&
                nSub >=1 && nSub <= MAXLEVEL )
        {
            nCondition = PARA_IN_LIST;
            nSubCondition = nSub-1;
        }
        else if( IsXMLToken( sFunc, XML_OUTLINE_LEVEL) &&
                 nSub >=1 && nSub <= MAXLEVEL )
        {
            nCondition = PARA_IN_OUTLINE;
            nSubCondition = nSub-1;
        }
        else if( IsXMLToken( sFunc, XML_SECTION ) && !bHasSub )
        {
            nCondition = PARA_IN_SECTION;
        }
        else if( IsXMLToken( sFunc, XML_TABLE ) && !bHasSub )
        {
            nCondition = PARA_IN_TABLEBODY;
        }
        else if( IsXMLToken( sFunc, XML_TABLE_HEADER ) && !bHasSub )
        {
            nCondition = PARA_IN_TABLEHEAD;
        }
        else if( IsXMLToken( sFunc, XML_TEXT_BOX ) && !bHasSub )
        {
            nCondition = PARA_IN_FRAME;
        }
    }
}

// ---------------------------------------------------------------------

class SwXMLConditionContext_Impl : public SvXMLImportContext
{
    sal_uInt32 nCondition;
    sal_uInt32 nSubCondition;

    OUString sApplyStyle;

    void ParseCondition( const OUString& rCond );

public:

    SwXMLConditionContext_Impl(
            SvXMLImport& rInImport, sal_uInt16 nPrfx,
            const OUString& rLName,
            const Reference< xml::sax::XAttributeList > & xAttrList );
    virtual ~SwXMLConditionContext_Impl();

    sal_Bool IsValid() const { return 0 != nCondition; }

    sal_uInt32 GetCondition() const { return nCondition; }
    sal_uInt32 GetSubCondition() const { return nSubCondition; }
    const OUString& GetApplyStyle() const { return sApplyStyle; }
};

SwXMLConditionContext_Impl::SwXMLConditionContext_Impl(
            SvXMLImport& rInImport, sal_uInt16 nPrfx,
            const OUString& rLName,
            const Reference< xml::sax::XAttributeList > & xAttrList ) :
    SvXMLImportContext( rInImport, nPrfx, rLName ),
    nCondition( 0 ),
    nSubCondition( 0 )
{
    sal_Int16 nAttrCount = xAttrList.is() ? xAttrList->getLength() : 0;
    for( sal_Int16 i=0; i < nAttrCount; i++ )
    {
        const OUString& rAttrName = xAttrList->getNameByIndex( i );
        OUString aLclLocalName;
        sal_uInt16 nLclPrefix =
            GetImport().GetNamespaceMap().GetKeyByAttrName( rAttrName,
                                                            &aLclLocalName );
        const OUString& rValue = xAttrList->getValueByIndex( i );

        // TODO: use a map here
        if( XML_NAMESPACE_STYLE == nLclPrefix )
        {
            if( IsXMLToken( aLclLocalName, XML_CONDITION ) )
            {
                SwXMLConditionParser_Impl aCondParser( rValue );
                if( aCondParser.IsValid() )
                {
                    nCondition = aCondParser.GetCondition();
                    nSubCondition = aCondParser.GetSubCondition();
                }
            }
            else if( IsXMLToken( aLclLocalName, XML_APPLY_STYLE_NAME ) )
            {
                sApplyStyle = rValue;
            }
        }
    }
}

SwXMLConditionContext_Impl::~SwXMLConditionContext_Impl()
{
}

// ---------------------------------------------------------------------

typedef SwXMLConditionContext_Impl *SwXMLConditionContextPtr;
SV_DECL_PTRARR( SwXMLConditions_Impl, SwXMLConditionContextPtr, 5, 2 )

class SwXMLTextStyleContext_Impl : public XMLTextStyleContext
{
    SwXMLConditions_Impl    *pConditions;

protected:

    virtual Reference < XStyle > Create();

public:

    TYPEINFO();

    SwXMLTextStyleContext_Impl( SwXMLImport& rInImport, sal_uInt16 nPrfx,
            const OUString& rLName,
            const Reference< xml::sax::XAttributeList > & xAttrList,
            sal_uInt16 nInFamily,
            SvXMLStylesContext& rStyles );
    virtual ~SwXMLTextStyleContext_Impl();

    virtual SvXMLImportContext *CreateChildContext(
            sal_uInt16 nInPrefix,
            const OUString& rLocalName,
            const Reference< xml::sax::XAttributeList > & xAttrList );

    virtual void Finish( sal_Bool bOverwrite );
};

TYPEINIT1( SwXMLTextStyleContext_Impl, XMLTextStyleContext );

Reference < XStyle > SwXMLTextStyleContext_Impl::Create()
{
    Reference < XStyle > xNewStyle;

    if( pConditions && XML_STYLE_FAMILY_TEXT_PARAGRAPH == GetFamily() )
    {
        Reference< XMultiServiceFactory > xFactory( GetImport().GetModel(),
                                                    UNO_QUERY );
        if( xFactory.is() )
        {
            OUString sServiceName( RTL_CONSTASCII_USTRINGPARAM(
                        "com.sun.star.style.ConditionalParagraphStyle" ) );
            Reference < XInterface > xIfc =
                xFactory->createInstance( sServiceName );
            if( xIfc.is() )
                xNewStyle = Reference < XStyle >( xIfc, UNO_QUERY );
        }
    }
    else
    {
        xNewStyle = XMLTextStyleContext::Create();
    }

    return xNewStyle;
}

SwXMLTextStyleContext_Impl::SwXMLTextStyleContext_Impl( SwXMLImport& rInImport,
        sal_uInt16 nPrfx, const OUString& rLName,
        const Reference< xml::sax::XAttributeList > & xAttrList,
        sal_uInt16 nInFamily,
        SvXMLStylesContext& rStyles ) :
    XMLTextStyleContext( rInImport, nPrfx, rLName, xAttrList, rStyles, nInFamily ),
    pConditions( 0 )
{
}

SwXMLTextStyleContext_Impl::~SwXMLTextStyleContext_Impl()
{
    if( pConditions )
    {
        while( pConditions->Count() )
        {
            SwXMLConditionContext_Impl *pCond = pConditions->GetObject(0);
            pConditions->Remove( 0UL );
            pCond->ReleaseRef();
        }
        delete pConditions;
    }
}

SvXMLImportContext *SwXMLTextStyleContext_Impl::CreateChildContext(
        sal_uInt16 nInPrefix,
        const OUString& rLocalName,
        const Reference< xml::sax::XAttributeList > & xAttrList )
{
    SvXMLImportContext *pContext = 0;

    if( XML_NAMESPACE_STYLE == nInPrefix && IsXMLToken( rLocalName, XML_MAP ) )
    {
        SwXMLConditionContext_Impl *pCond =
            new SwXMLConditionContext_Impl( GetImport(), nInPrefix,
                                            rLocalName, xAttrList );
        if( pCond->IsValid() )
        {
            if( !pConditions )
               pConditions = new SwXMLConditions_Impl;
            pConditions->Insert( pCond, pConditions->Count() );
            pCond->AddRef();
        }
        pContext = pCond;
    }

    if( !pContext )
        pContext = XMLTextStyleContext::CreateChildContext( nInPrefix, rLocalName,
                                                          xAttrList );

    return pContext;
}

void SwXMLTextStyleContext_Impl::Finish( sal_Bool bOverwrite )
{
    XMLTextStyleContext::Finish( bOverwrite );

    if( !pConditions || XML_STYLE_FAMILY_TEXT_PARAGRAPH != GetFamily() )
        return;

    Reference < XStyle > xLclStyle = GetStyle();
    if( !xLclStyle.is() )
        return;

    const SwXStyle* pStyle = 0;
    Reference<XUnoTunnel> xStyleTunnel( xLclStyle, UNO_QUERY);
    if( xStyleTunnel.is() )
    {
        pStyle = (SwXStyle*)xStyleTunnel->getSomething(
                                            SwXStyle::getUnoTunnelId() );
    }
    if( !pStyle )
        return;

    const SwDoc *pDoc = pStyle->GetDoc();

    SwTxtFmtColl *pColl = pDoc->FindTxtFmtCollByName( pStyle->GetStyleName() );
    OSL_ENSURE( pColl, "Text collection not found" );
    if( !pColl || RES_CONDTXTFMTCOLL != pColl->Which() )
        return;

    sal_uInt16 nCount = pConditions->Count();
    String aString;
    for( sal_uInt16 i = 0; i < nCount; i++ )
    {
        const SwXMLConditionContext_Impl *pCond = (*pConditions)[i];
        SwStyleNameMapper::FillUIName( pCond->GetApplyStyle(),
                                      aString,
                                      GET_POOLID_TXTCOLL,
                                      sal_True);
    }
}

// ---------------------------------------------------------------------

class SwXMLItemSetStyleContext_Impl : public SvXMLStyleContext
{
    OUString                sMasterPageName;
    SfxItemSet              *pItemSet;

    OUString                sDataStyleName;

    sal_Bool                bHasMasterPageName : 1;
    sal_Bool                bPageDescConnected : 1;
    sal_Bool                bDataStyleIsResolved;

    SvXMLImportContext *CreateItemSetContext(
            sal_uInt16 nInPrefix,
            const OUString& rLName,
            const Reference< xml::sax::XAttributeList > & xAttrList);

protected:

    virtual void SetAttribute( sal_uInt16 nPrefixKey,
                               const OUString& rLocalName,
                               const OUString& rValue );

    const SwXMLImport& GetSwImport() const
            { return (const SwXMLImport&)GetImport(); }
    SwXMLImport& GetSwImport() { return (SwXMLImport&)GetImport(); }

public:

    TYPEINFO();

    SwXMLItemSetStyleContext_Impl(
            SwXMLImport& rInImport, sal_uInt16 nPrfx,
            const OUString& rLName,
            const Reference< xml::sax::XAttributeList > & xAttrList,
            sal_uInt16 nInFamily);
    virtual ~SwXMLItemSetStyleContext_Impl();

    virtual SvXMLImportContext *CreateChildContext(
            sal_uInt16 nInPrefix,
            const OUString& rLocalName,
            const Reference< xml::sax::XAttributeList > & xAttrList );

    // The item set may be empty!
    SfxItemSet *GetItemSet() { return pItemSet; }
    const SfxItemSet *GetItemSet() const { return pItemSet; }

    const OUString& GetMasterPageName() const { return sMasterPageName; }
    sal_Bool HasMasterPageName() const { return bHasMasterPageName; }

    sal_Bool IsPageDescConnected() const { return bPageDescConnected; }
    void ConnectPageDesc();

    sal_Bool ResolveDataStyleName();
};

void SwXMLItemSetStyleContext_Impl::SetAttribute( sal_uInt16 nPrefixKey,
                                           const OUString& rLocalName,
                                           const OUString& rValue )
{
    if( XML_NAMESPACE_STYLE == nPrefixKey )
    {
        if ( IsXMLToken( rLocalName, XML_MASTER_PAGE_NAME ) )
        {
            sMasterPageName = rValue;
            bHasMasterPageName = sal_True;
        }
        else if ( IsXMLToken( rLocalName, XML_DATA_STYLE_NAME ) )
        {
            // if we have a valid data style name
            if (rValue.getLength() > 0)
            {
                sDataStyleName = rValue;
                bDataStyleIsResolved = sal_False;   // needs to be resolved
            }
        }
        else
        {
            SvXMLStyleContext::SetAttribute( nPrefixKey, rLocalName, rValue );
        }
    }
    else
    {
        SvXMLStyleContext::SetAttribute( nPrefixKey, rLocalName, rValue );
    }
}

SvXMLImportContext *SwXMLItemSetStyleContext_Impl::CreateItemSetContext(
        sal_uInt16 nInPrefix, const OUString& rLName,
        const Reference< xml::sax::XAttributeList > & xAttrList )
{
    OSL_ENSURE( !pItemSet,
            "SwXMLItemSetStyleContext_Impl::CreateItemSetContext: item set exists" );

    SvXMLImportContext *pContext = 0;

    Reference<XUnoTunnel> xCrsrTunnel( GetImport().GetTextImport()->GetCursor(),
                                       UNO_QUERY);
    OSL_ENSURE( xCrsrTunnel.is(), "missing XUnoTunnel for Cursor" );
    OTextCursorHelper *pTxtCrsr = (OTextCursorHelper*)xCrsrTunnel->getSomething(
                                        OTextCursorHelper::getUnoTunnelId() );
    OSL_ENSURE( pTxtCrsr, "SwXTextCursor missing" );
    SfxItemPool& rItemPool = pTxtCrsr->GetDoc()->GetAttrPool();
    switch( GetFamily() )
    {
    case XML_STYLE_FAMILY_TABLE_TABLE:
        pItemSet = new SfxItemSet( rItemPool, aTableSetRange );
        break;
    case XML_STYLE_FAMILY_TABLE_COLUMN:
        pItemSet = new SfxItemSet( rItemPool, RES_FRM_SIZE, RES_FRM_SIZE, 0 );
        break;
    case XML_STYLE_FAMILY_TABLE_ROW:
        pItemSet = new SfxItemSet( rItemPool, aTableLineSetRange );
        break;
    case XML_STYLE_FAMILY_TABLE_CELL:
        pItemSet = new SfxItemSet( rItemPool, aTableBoxSetRange );
        break;
    default:
        OSL_ENSURE( !this,
        "SwXMLItemSetStyleContext_Impl::CreateItemSetContext: unknown family" );
        break;
    }
    if( pItemSet )
        pContext = GetSwImport().CreateTableItemImportContext(
                                nInPrefix, rLName, xAttrList, GetFamily(),
                                *pItemSet );
    if( !pContext )
    {
        delete pItemSet;
        pItemSet = 0;
    }

    return pContext;
}

TYPEINIT1( SwXMLItemSetStyleContext_Impl, SvXMLStyleContext );

SwXMLItemSetStyleContext_Impl::SwXMLItemSetStyleContext_Impl( SwXMLImport& rInImport,
        sal_uInt16 nPrfx, const OUString& rLName,
        const Reference< xml::sax::XAttributeList > & xAttrList,
        sal_uInt16 nInFamily ) :
    SvXMLStyleContext( rInImport, nPrfx, rLName, xAttrList, nInFamily ),
    pItemSet( 0 ),
    sDataStyleName(),
    bHasMasterPageName( sal_False ),
    bPageDescConnected( sal_False ),
    bDataStyleIsResolved( sal_True )
{
}

SwXMLItemSetStyleContext_Impl::~SwXMLItemSetStyleContext_Impl()
{
    delete pItemSet;
}

SvXMLImportContext *SwXMLItemSetStyleContext_Impl::CreateChildContext(
        sal_uInt16 nInPrefix,
        const OUString& rLocalName,
        const Reference< xml::sax::XAttributeList > & xAttrList )
{
    SvXMLImportContext *pContext = 0;

    if( XML_NAMESPACE_STYLE == nInPrefix )
    {
        if( IsXMLToken( rLocalName, XML_PROPERTIES ) )
        {
            pContext = CreateItemSetContext( nInPrefix, rLocalName, xAttrList );
        }
    }

    if( !pContext )
        pContext = SvXMLStyleContext::CreateChildContext( nInPrefix, rLocalName,
                                                          xAttrList );

    return pContext;
}

void SwXMLItemSetStyleContext_Impl::ConnectPageDesc()
{
    if( bPageDescConnected || !HasMasterPageName() )
        return;
    bPageDescConnected = sal_True;

    Reference<XUnoTunnel> xCrsrTunnel( GetImport().GetTextImport()->GetCursor(),
                                       UNO_QUERY);
    OSL_ENSURE( xCrsrTunnel.is(), "missing XUnoTunnel for Cursor" );
    OTextCursorHelper *pTxtCrsr = (OTextCursorHelper*)xCrsrTunnel->getSomething(
                                        OTextCursorHelper::getUnoTunnelId() );
    OSL_ENSURE( pTxtCrsr, "SwXTextCursor missing" );
    SwDoc *pDoc = pTxtCrsr->GetDoc();

    String sName;
    SwStyleNameMapper::FillUIName( GetMasterPageName(),
                                   sName,
                                   GET_POOLID_PAGEDESC,
                                   sal_True);
    SwPageDesc *pPageDesc = pDoc->FindPageDescByName( sName );
    if( !pPageDesc )
    {
        // If the page style is a pool style, then we maybe have to create it
        // first if it hasn't been used by now.
        sal_uInt16 nPoolId = SwStyleNameMapper::GetPoolIdFromUIName( sName, GET_POOLID_PAGEDESC );
        if( USHRT_MAX != nPoolId )
            pPageDesc = pDoc->GetPageDescFromPoolSimple( nPoolId, FALSE );
    }

    if( !pPageDesc )
        return;

    if( !pItemSet )
    {
        SfxItemPool& rItemPool = pDoc->GetAttrPool();
        pItemSet = new SfxItemSet( rItemPool, aTableSetRange );
    }

    const SfxPoolItem *pItem;
    SwFmtPageDesc *pFmtPageDesc = 0;
    if( SFX_ITEM_SET == pItemSet->GetItemState( RES_PAGEDESC, sal_False,
                                                &pItem ) )
    {
         if( ((SwFmtPageDesc *)pItem)->GetPageDesc() != pPageDesc )
            pFmtPageDesc = new SwFmtPageDesc( *(SwFmtPageDesc *)pItem );
    }
    else
        pFmtPageDesc = new SwFmtPageDesc();

    if( pFmtPageDesc )
    {
        pPageDesc->Add( pFmtPageDesc );
        pItemSet->Put( *pFmtPageDesc );
        delete pFmtPageDesc;
    }
}

sal_Bool SwXMLItemSetStyleContext_Impl::ResolveDataStyleName()
{
    // resolve, if not already done
    if (! bDataStyleIsResolved)
    {
        // get the format key
        sal_Int32 nFormat =
            GetImport().GetTextImport()->GetDataStyleKey(sDataStyleName);

        // if the key is valid, insert Item into ItemSet
        if( -1 != nFormat )
        {
            if( !pItemSet )
            {
                Reference<XUnoTunnel> xCrsrTunnel( GetImport().GetTextImport()->GetCursor(),
                                                   UNO_QUERY);
                OSL_ENSURE( xCrsrTunnel.is(), "missing XUnoTunnel for Cursor" );
                OTextCursorHelper *pTxtCrsr = (OTextCursorHelper*)xCrsrTunnel->getSomething(
                                                    OTextCursorHelper::getUnoTunnelId() );
                OSL_ENSURE( pTxtCrsr, "SwXTextCursor missing" );
                SwDoc *pDoc = pTxtCrsr->GetDoc();

                SfxItemPool& rItemPool = pDoc->GetAttrPool();
                pItemSet = new SfxItemSet( rItemPool, aTableBoxSetRange );
            }
            SwTblBoxNumFormat aNumFormatItem(nFormat);
            pItemSet->Put(aNumFormatItem);
        }

        // now resolved
        bDataStyleIsResolved = sal_True;
        return sal_True;
    }
    else
    {
        // was already resolved; nothing to do
        return sal_False;
    }
}

// ---------------------------------------------------------------------
//
class SwXMLStylesContext_Impl : public SvXMLStylesContext
{
    sal_Bool bAutoStyles;

    SwXMLItemSetStyleContext_Impl *GetSwStyle( sal_uInt16 i ) const;

    SwXMLImport& GetSwImport() { return (SwXMLImport&)GetImport(); }
    const SwXMLImport& GetSwImport() const
            { return (const SwXMLImport&)GetImport(); }

protected:

    virtual SvXMLStyleContext *CreateStyleStyleChildContext( sal_uInt16 nInFamily,
        sal_uInt16 nInPrefix, const OUString& rLocalName,
        const Reference< xml::sax::XAttributeList > & xAttrList );
    virtual SvXMLStyleContext *CreateDefaultStyleStyleChildContext(
        sal_uInt16 nInFamily, sal_uInt16 nInPrefix, const OUString& rLocalName,
        const Reference< xml::sax::XAttributeList > & xAttrList );
    // HACK
    virtual UniReference < SvXMLImportPropertyMapper > GetImportPropertyMapper(
                        sal_uInt16 nInFamily ) const;

    virtual ::com::sun::star::uno::Reference <
                    ::com::sun::star::container::XNameContainer >
        GetStylesContainer( sal_uInt16 nInFamily ) const;
    virtual ::rtl::OUString GetServiceName( sal_uInt16 nInFamily ) const;
    // HACK

public:

    TYPEINFO();

    SwXMLStylesContext_Impl(
            SwXMLImport& rInImport, sal_uInt16 nPrfx,
            const OUString& rLName ,
            const Reference< xml::sax::XAttributeList > & xAttrList,
            sal_Bool bAuto );
    virtual ~SwXMLStylesContext_Impl();

    virtual sal_Bool InsertStyleFamily( sal_uInt16 nInFamily ) const;

    virtual void EndElement();
};

TYPEINIT1( SwXMLStylesContext_Impl, SvXMLStylesContext );

inline SwXMLItemSetStyleContext_Impl *SwXMLStylesContext_Impl::GetSwStyle(
        sal_uInt16 i ) const
{
    return PTR_CAST( SwXMLItemSetStyleContext_Impl, GetStyle( i ) );
}

SvXMLStyleContext *SwXMLStylesContext_Impl::CreateStyleStyleChildContext(
        sal_uInt16 nInFamily, sal_uInt16 nInPrefix, const OUString& rLocalName,
        const Reference< xml::sax::XAttributeList > & xAttrList )
{
    SvXMLStyleContext *pStyle = 0;

    switch( nInFamily )
    {
    case XML_STYLE_FAMILY_TEXT_PARAGRAPH:
        pStyle = new SwXMLTextStyleContext_Impl( GetSwImport(), nInPrefix,
                            rLocalName, xAttrList, nInFamily, *this );
        break;
    case XML_STYLE_FAMILY_TABLE_TABLE:
    case XML_STYLE_FAMILY_TABLE_COLUMN:
    case XML_STYLE_FAMILY_TABLE_ROW:
    case XML_STYLE_FAMILY_TABLE_CELL:
        pStyle = new SwXMLItemSetStyleContext_Impl( GetSwImport(), nInPrefix,
                            rLocalName, xAttrList, nInFamily  );
        break;
    case XML_STYLE_FAMILY_SD_GRAPHICS_ID:
        // As long as there are no element items, we can use the text
        // style class.
        pStyle = new XMLTextShapeStyleContext( GetImport(), nInPrefix,
                            rLocalName, xAttrList, *this, nInFamily );
        break;
    default:
        pStyle = SvXMLStylesContext::CreateStyleStyleChildContext( nInFamily,
                                                                   nInPrefix,
                                                              rLocalName,
                                                              xAttrList );
        break;
    }

    return pStyle;
}

SvXMLStyleContext *SwXMLStylesContext_Impl::CreateDefaultStyleStyleChildContext(
        sal_uInt16 nInFamily, sal_uInt16 nInPrefix, const OUString& rLocalName,
        const uno::Reference< xml::sax::XAttributeList > & xAttrList )
{
    SvXMLStyleContext *pStyle = 0;

    switch( nInFamily )
    {
    case XML_STYLE_FAMILY_TEXT_PARAGRAPH:
        pStyle = new XMLTextStyleContext( GetImport(), nInPrefix, rLocalName,
                                          xAttrList, *this, nInFamily,
                                          sal_True );
        break;
    case XML_STYLE_FAMILY_SD_GRAPHICS_ID:
        // There are no writer specific defaults for graphic styles!
        pStyle = new XMLGraphicsDefaultStyle( GetImport(), nInPrefix,
                            rLocalName, xAttrList, *this );
        break;
    default:
        pStyle = SvXMLStylesContext::CreateDefaultStyleStyleChildContext( nInFamily,
                                                                   nInPrefix,
                                                              rLocalName,
                                                              xAttrList );
        break;
    }

    return pStyle;
}


SwXMLStylesContext_Impl::SwXMLStylesContext_Impl(
        SwXMLImport& rInImport, sal_uInt16 nPrfx, const OUString& rLName,
        const Reference< xml::sax::XAttributeList > & xAttrList,
        sal_Bool bAuto ) :
    SvXMLStylesContext( rInImport, nPrfx, rLName, xAttrList ),
    bAutoStyles( bAuto )
{
}

SwXMLStylesContext_Impl::~SwXMLStylesContext_Impl()
{
}

sal_Bool SwXMLStylesContext_Impl::InsertStyleFamily( sal_uInt16 nInFamily ) const
{
    const SwXMLImport& rSwImport = GetSwImport();
    sal_uInt16 nStyleFamilyMask = rSwImport.GetStyleFamilyMask();

    sal_Bool bIns = sal_True;
    switch( nInFamily )
    {
    case XML_STYLE_FAMILY_TEXT_PARAGRAPH:
        bIns = (nStyleFamilyMask & SFX_STYLE_FAMILY_PARA) != 0;
        break;
    case XML_STYLE_FAMILY_TEXT_TEXT:
        bIns = (nStyleFamilyMask & SFX_STYLE_FAMILY_CHAR) != 0;
        break;
    case XML_STYLE_FAMILY_SD_GRAPHICS_ID:
        bIns = (nStyleFamilyMask & SFX_STYLE_FAMILY_FRAME) != 0;
        break;
    case XML_STYLE_FAMILY_TEXT_LIST:
        bIns = (nStyleFamilyMask & SFX_STYLE_FAMILY_PSEUDO) != 0;
        break;
    case XML_STYLE_FAMILY_TEXT_OUTLINE:
    case XML_STYLE_FAMILY_TEXT_FOOTNOTECONFIG:
    case XML_STYLE_FAMILY_TEXT_ENDNOTECONFIG:
    case XML_STYLE_FAMILY_TEXT_LINENUMBERINGCONFIG:
    case XML_STYLE_FAMILY_TEXT_BIBLIOGRAPHYCONFIG:
        bIns = !(rSwImport.IsInsertMode() || rSwImport.IsStylesOnlyMode() ||
                 rSwImport.IsBlockMode());
        break;
    default:
        bIns = SvXMLStylesContext::InsertStyleFamily( nInFamily );
        break;
    }

    return bIns;
}

UniReference < SvXMLImportPropertyMapper > SwXMLStylesContext_Impl::GetImportPropertyMapper(
                        sal_uInt16 nInFamily ) const
{
    UniReference < SvXMLImportPropertyMapper > xMapper;
//  if( XML_STYLE_FAMILY_SD_GRAPHICS_ID == nInFamily )
//      xMapper = ((SvXMLImport *)&GetImport())->GetTextImport()
//                   ->GetFrameImportPropertySetMapper();
//  else
        xMapper = SvXMLStylesContext::GetImportPropertyMapper( nInFamily );

    return xMapper;
}

Reference < XNameContainer > SwXMLStylesContext_Impl::GetStylesContainer(
                                                sal_uInt16 nInFamily ) const
{
    Reference < XNameContainer > xStyles;
    if( XML_STYLE_FAMILY_SD_GRAPHICS_ID == nInFamily )
        xStyles = ((SvXMLImport *)&GetImport())->GetTextImport()->GetFrameStyles();
    else
        xStyles = SvXMLStylesContext::GetStylesContainer( nInFamily );

    return xStyles;
}

OUString SwXMLStylesContext_Impl::GetServiceName( sal_uInt16 nInFamily ) const
{
    String sServiceName;
    if( XML_STYLE_FAMILY_SD_GRAPHICS_ID == nInFamily )
        sServiceName = OUString( RTL_CONSTASCII_USTRINGPARAM("com.sun.star.style.FrameStyle") );
    else
        sServiceName = SvXMLStylesContext::GetServiceName( nInFamily );

    return sServiceName;
}

void SwXMLStylesContext_Impl::EndElement()
{
    GetSwImport().InsertStyles( bAutoStyles );
}

// ---------------------------------------------------------------------
//
class SwXMLMasterStylesContext_Impl : public XMLTextMasterStylesContext
{
protected:
    virtual sal_Bool InsertStyleFamily( sal_uInt16 nInFamily ) const;

    SwXMLImport& GetSwImport() { return (SwXMLImport&)GetImport(); }
    const SwXMLImport& GetSwImport() const
            { return (const SwXMLImport&)GetImport(); }

public:

    TYPEINFO();

    SwXMLMasterStylesContext_Impl(
            SwXMLImport& rInImport, sal_uInt16 nPrfx,
            const OUString& rLName ,
            const Reference< xml::sax::XAttributeList > & xAttrList );
    virtual ~SwXMLMasterStylesContext_Impl();
    virtual void EndElement();
};

TYPEINIT1( SwXMLMasterStylesContext_Impl, XMLTextMasterStylesContext );

SwXMLMasterStylesContext_Impl::SwXMLMasterStylesContext_Impl(
        SwXMLImport& rInImport, sal_uInt16 nPrfx,
        const OUString& rLName ,
        const Reference< xml::sax::XAttributeList > & xAttrList ) :
    XMLTextMasterStylesContext( rInImport, nPrfx, rLName, xAttrList )
{
}

SwXMLMasterStylesContext_Impl::~SwXMLMasterStylesContext_Impl()
{
}

sal_Bool SwXMLMasterStylesContext_Impl::InsertStyleFamily( sal_uInt16 nInFamily ) const
{
    sal_Bool bIns;

    const SwXMLImport& rSwImport = GetSwImport();
    sal_uInt16 nStyleFamilyMask = rSwImport.GetStyleFamilyMask();
    if( XML_STYLE_FAMILY_MASTER_PAGE == nInFamily )
        bIns = (nStyleFamilyMask & SFX_STYLE_FAMILY_PAGE) != 0;
    else
        bIns = XMLTextMasterStylesContext::InsertStyleFamily( nInFamily );

    return bIns;
}

void SwXMLMasterStylesContext_Impl::EndElement()
{
    FinishStyles( !GetSwImport().IsInsertMode() );
    GetSwImport().FinishStyles();
}
// ---------------------------------------------------------------------

SvXMLImportContext *SwXMLImport::CreateStylesContext(
        const OUString& rLocalName,
        const Reference< xml::sax::XAttributeList > & xAttrList,
        sal_Bool bAuto )
{
    SvXMLStylesContext *pContext =
        new SwXMLStylesContext_Impl( *this, XML_NAMESPACE_OFFICE, rLocalName,
                                       xAttrList, bAuto );
    if( bAuto )
        SetAutoStyles( pContext );
    else
        SetStyles( pContext );

    return pContext;
}

SvXMLImportContext *SwXMLImport::CreateMasterStylesContext(
        const OUString& rLocalName,
        const Reference< xml::sax::XAttributeList > & xAttrList )
{
    SvXMLStylesContext *pContext =
        new SwXMLMasterStylesContext_Impl( *this, XML_NAMESPACE_OFFICE, rLocalName,
                                          xAttrList );
    SetMasterStyles( pContext );

    return pContext;
}

void SwXMLImport::InsertStyles( sal_Bool bAuto )
{
    if( !bAuto && GetStyles() )
        GetStyles()->CopyStylesToDoc( !IsInsertMode(), sal_False );
}

void SwXMLImport::FinishStyles()
{
    if( GetStyles() )
        GetStyles()->FinishStyles( !IsInsertMode() );
}

void SwXMLImport::UpdateTxtCollConditions( SwDoc *pDoc )
{
    if( !pDoc )
    {
        Reference<XUnoTunnel> xCrsrTunnel( GetTextImport()->GetCursor(),
                                              UNO_QUERY);
        OSL_ENSURE( xCrsrTunnel.is(), "missing XUnoTunnel for Cursor" );
        OTextCursorHelper *pTxtCrsr =
                (OTextCursorHelper*)xCrsrTunnel->getSomething(
                                            OTextCursorHelper::getUnoTunnelId() );
        OSL_ENSURE( pTxtCrsr, "SwXTextCursor missing" );
        pDoc = pTxtCrsr->GetDoc();

        OSL_ENSURE( pDoc, "document missing" );
    }

    const SwTxtFmtColls& rColls = *pDoc->GetTxtFmtColls();
    sal_uInt16 nCount = rColls.Count();
    for( sal_uInt16 i=0; i < nCount; i++ )
    {
        SwTxtFmtColl *pColl = rColls[i];
        if( pColl && RES_CONDTXTFMTCOLL == pColl->Which() )
        {
            const SwFmtCollConditions& rConditions =
                ((const SwConditionTxtFmtColl *)pColl)->GetCondColls();
            sal_Bool bSendModify = sal_False;
            for( sal_uInt16 j=0; j < rConditions.Count() && !bSendModify; j++ )
            {
                const SwCollCondition& rCond = *rConditions[j];
                switch( rCond.GetCondition() )
                {
                case PARA_IN_TABLEHEAD:
                case PARA_IN_TABLEBODY:
                case PARA_IN_FOOTER:
                case PARA_IN_HEADER:
                    bSendModify = sal_True;
                    break;
                }
            }
            if( bSendModify )
            {
                SwCondCollCondChg aMsg( pColl );
                pColl->Modify( &aMsg, &aMsg );
            }
        }
    }
}

sal_Bool SwXMLImport::FindAutomaticStyle(
        sal_uInt16 nInFamily,
        const OUString& rName,
        const SfxItemSet **ppItemSet,
        OUString *pParent ) const
{
    SwXMLItemSetStyleContext_Impl *pStyle = 0;
    if( GetAutoStyles() )
    {
        pStyle = PTR_CAST( SwXMLItemSetStyleContext_Impl,
              GetAutoStyles()->
                    FindStyleChildContext( nInFamily, rName,
                                           sal_True ) );
        if( pStyle )
        {
            if( ppItemSet )
            {
                if( XML_STYLE_FAMILY_TABLE_TABLE == pStyle->GetFamily() &&
                    pStyle->HasMasterPageName() &&
                    !pStyle->IsPageDescConnected() )
                    pStyle->ConnectPageDesc();
                (*ppItemSet) = pStyle->GetItemSet();

                // resolve data style name late
                if( XML_STYLE_FAMILY_TABLE_CELL == pStyle->GetFamily() &&
                    pStyle->ResolveDataStyleName() )
                {
                    (*ppItemSet) = pStyle->GetItemSet();
                }

            }

            if( pParent )
                *pParent = pStyle->GetParent();
        }
    }

    return pStyle != 0;
}
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
