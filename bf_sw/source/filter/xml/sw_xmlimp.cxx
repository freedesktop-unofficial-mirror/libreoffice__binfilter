/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2000, 2010 Oracle and/or its affiliates.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/


#ifdef _MSC_VER
#pragma hdrstop
#endif

#include <com/sun/star/text/XTextDocument.hpp>
#include <com/sun/star/text/XTextRange.hpp>
#include <com/sun/star/text/XText.hpp>
#include <com/sun/star/drawing/XDrawPage.hpp>
#include <com/sun/star/drawing/XDrawPageSupplier.hpp>
#include <com/sun/star/drawing/XShapes.hpp>
#include <com/sun/star/container/XIndexAccess.hpp>
#include <bf_xmloff/xmlnmspe.hxx>
#include <bf_xmloff/xmltkmap.hxx>
#include <bf_xmloff/xmlictxt.hxx>
#include <bf_xmloff/txtimp.hxx>
#include <bf_xmloff/nmspmap.hxx>
#include <bf_xmloff/XMLTextShapeImportHelper.hxx>
#include <bf_xmloff/XMLFontStylesContext.hxx>
#include <bf_xmloff/ProgressBarHelper.hxx>
#include <com/sun/star/i18n/XForbiddenCharacters.hpp>
#include <com/sun/star/document/PrinterIndependentLayout.hpp>

#include <horiornt.hxx>

#include <doc.hxx>

#include <osl/diagnose.h>

#include <viscrs.hxx>
#include <unoobj.hxx>
#include "unocrsr.hxx"
#include <poolfmt.hxx>
#include <ndtxt.hxx>
#include <pam.hxx>

#include "xmlimp.hxx"

#include <bf_xmloff/DocumentSettingsContext.hxx>

#include <docsh.hxx>

#include <bf_svx/unolingu.hxx>
#include <bf_svx/xmlgrhlp.hxx>
#include <bf_svx/xmleohlp.hxx>
#include <bf_sfx2/printer.hxx>

#include <ForbiddenCharactersEnum.hxx>
#include <bf_xmloff/xmluconv.hxx>
#include <bf_svtools/saveopt.hxx>

// for locking SolarMutex: svapp + mutex
#include <vcl/svapp.hxx>
#include <sal/macros.h>
#include <osl/mutex.hxx>
namespace binfilter {


using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::text;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::i18n;
using namespace ::com::sun::star::drawing;
using namespace ::binfilter::xmloff::token;

using rtl::OUString;

struct OUStringEquals
{
    sal_Bool operator()( const ::rtl::OUString &r1,
                         const ::rtl::OUString &r2) const
    {
        return r1 == r2;
    }
};

//----------------------------------------------------------------------------

enum SwXMLDocTokens
{
    XML_TOK_DOC_FONTDECLS,
    XML_TOK_DOC_STYLES,
    XML_TOK_DOC_AUTOSTYLES,
    XML_TOK_DOC_MASTERSTYLES,
    XML_TOK_DOC_META,
    XML_TOK_DOC_BODY,
    XML_TOK_DOC_SCRIPT,
    XML_TOK_DOC_SETTINGS,
    XML_TOK_OFFICE_END=XML_TOK_UNKNOWN
};

static SvXMLTokenMapEntry aDocTokenMap[] =
{
    { XML_NAMESPACE_OFFICE, XML_FONT_DECLS,     XML_TOK_DOC_FONTDECLS   },
    { XML_NAMESPACE_OFFICE, XML_STYLES,         XML_TOK_DOC_STYLES      },
    { XML_NAMESPACE_OFFICE, XML_AUTOMATIC_STYLES, XML_TOK_DOC_AUTOSTYLES    },
    { XML_NAMESPACE_OFFICE, XML_MASTER_STYLES,   XML_TOK_DOC_MASTERSTYLES   },
    { XML_NAMESPACE_OFFICE, XML_META,           XML_TOK_DOC_META        },
    { XML_NAMESPACE_OFFICE, XML_BODY,           XML_TOK_DOC_BODY        },
    { XML_NAMESPACE_OFFICE, XML_SCRIPT,         XML_TOK_DOC_SCRIPT      },
    { XML_NAMESPACE_OFFICE, XML_SETTINGS,       XML_TOK_DOC_SETTINGS    },
    XML_TOKEN_MAP_END
};

class SwXMLDocContext_Impl : public SvXMLImportContext
{
    const SwXMLImport& GetSwImport() const
        { return (const SwXMLImport&)GetImport(); }
    SwXMLImport& GetSwImport() { return (SwXMLImport&)GetImport(); }

public:

    SwXMLDocContext_Impl( SwXMLImport& rInImport, sal_uInt16 nPrfx,
                const OUString& rLName,
                const Reference< xml::sax::XAttributeList > & xAttrList );
    virtual ~SwXMLDocContext_Impl();

    virtual SvXMLImportContext *CreateChildContext( sal_uInt16 nInPrefix,
                const OUString& rLocalName,
                const Reference< xml::sax::XAttributeList > & xAttrList );
};

SwXMLDocContext_Impl::SwXMLDocContext_Impl( SwXMLImport& rInImport,
                sal_uInt16 nPrfx, const OUString& rLName,
                const Reference< xml::sax::XAttributeList > & xAttrList ) :
    SvXMLImportContext( rInImport, nPrfx, rLName )
{
    // process document class
    // global-text is handled via document shell;
    // we only handle label documents
    sal_Int16 nLength = xAttrList->getLength();
    for(sal_Int16 nAttr = 0; nAttr < nLength; nAttr++)
    {
        OUString sLocalName;
        sal_uInt16 nLclPrefix = GetImport().GetNamespaceMap().
            GetKeyByAttrName( xAttrList->getNameByIndex(nAttr),
                              &sLocalName );

        if ( (XML_NAMESPACE_OFFICE == nLclPrefix) &&
             IsXMLToken( sLocalName, XML_CLASS ) )
        {
            if ( IsXMLToken( xAttrList->getValueByIndex(nAttr), XML_LABEL ) )
            {
                // OK, we need to set label mode. To do this, tunnel
                // to get the SwDoc, then set label mode.

                Reference<XText> xText(GetImport().GetModel(), UNO_QUERY);
                Reference<XUnoTunnel> xTunnel(
                    GetImport().GetTextImport()->GetText(), UNO_QUERY);
                DBG_ASSERT(xTunnel.is(), "I can't get the Tunnel");
                SwXText* pText = (SwXText*)xTunnel->getSomething(
                    SwXText::getUnoTunnelId());
                if (NULL != pText)
                {
                    SwDoc* pDoc = pText->GetDoc();
                    if (NULL != pDoc)
                        pDoc->SetLabelDoc();
                }
            }
        }
    }
}

SwXMLDocContext_Impl::~SwXMLDocContext_Impl()
{
}

SvXMLImportContext *SwXMLDocContext_Impl::CreateChildContext(
        sal_uInt16 nInPrefix,
        const OUString& rLocalName,
        const Reference< xml::sax::XAttributeList > & xAttrList )
{
    SvXMLImportContext *pContext = 0;

    const SvXMLTokenMap& rTokenMap = GetSwImport().GetDocElemTokenMap();
    switch( rTokenMap.Get( nInPrefix, rLocalName ) )
    {
    case XML_TOK_DOC_FONTDECLS:
        pContext = GetSwImport().CreateFontDeclsContext( rLocalName,
                                                             xAttrList );
        break;
    case XML_TOK_DOC_STYLES:
        GetSwImport().GetProgressBarHelper()->Increment( PROGRESS_BAR_STEP );
        pContext = GetSwImport().CreateStylesContext( rLocalName, xAttrList,
                                                      sal_False );
        break;
    case XML_TOK_DOC_AUTOSTYLES:
        // don't use the autostyles from the styles-document for the progress
        if ( ! IsXMLToken( GetLocalName(), XML_DOCUMENT_STYLES ) )
            GetSwImport().GetProgressBarHelper()->Increment
                ( PROGRESS_BAR_STEP );
        pContext = GetSwImport().CreateStylesContext( rLocalName, xAttrList,
                                                      sal_True );
        break;
//  case XML_TOK_DOC_USESTYLES:
//      pContext = GetSwImport().CreateUseStylesContext( rLocalName,
//                                                       xAttrList );
//      break;
    case XML_TOK_DOC_MASTERSTYLES:
        pContext = GetSwImport().CreateMasterStylesContext( rLocalName,
                                                            xAttrList );
        break;
    case XML_TOK_DOC_META:
        pContext = GetSwImport().CreateMetaContext( rLocalName );
        break;
    case XML_TOK_DOC_SCRIPT:
        pContext = GetSwImport().CreateScriptContext( rLocalName );
        break;
    case XML_TOK_DOC_BODY:
        GetSwImport().GetProgressBarHelper()->Increment( PROGRESS_BAR_STEP );
        pContext = GetSwImport().CreateBodyContext( rLocalName );
        break;
    case XML_TOK_DOC_SETTINGS:
        pContext = new XMLDocumentSettingsContext ( GetImport(), nInPrefix, rLocalName, xAttrList );
        break;
    }

    if( !pContext )
        pContext = new SvXMLImportContext( GetImport(), nInPrefix, rLocalName );


    return pContext;
}

//----------------------------------------------------------------------------

const SvXMLTokenMap& SwXMLImport::GetDocElemTokenMap()
{
    if( !pDocElemTokenMap )
        pDocElemTokenMap = new SvXMLTokenMap( aDocTokenMap );

    return *pDocElemTokenMap;
}

SvXMLImportContext *SwXMLImport::CreateContext(
        sal_uInt16 nInPrefix,
        const OUString& rLocalName,
        const Reference< xml::sax::XAttributeList > & xAttrList )
{
    SvXMLImportContext *pContext = 0;

    if( XML_NAMESPACE_OFFICE==nInPrefix &&
        ( IsXMLToken( rLocalName, XML_DOCUMENT ) ||
          IsXMLToken( rLocalName, XML_DOCUMENT_META ) ||
          IsXMLToken( rLocalName, XML_DOCUMENT_SETTINGS ) ||
          IsXMLToken( rLocalName, XML_DOCUMENT_STYLES ) ||
          IsXMLToken( rLocalName, XML_DOCUMENT_CONTENT ) ))
        pContext = new SwXMLDocContext_Impl( *this, nInPrefix, rLocalName,
                                             xAttrList );
    else
        pContext = SvXMLImport::CreateContext( nInPrefix, rLocalName, xAttrList );

    return pContext;
}

// #110680#
SwXMLImport::SwXMLImport(
    const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory > xServiceFactory,
    sal_uInt16 nImportFlags)
:   SvXMLImport( xServiceFactory, nImportFlags ),
    pSttNdIdx( 0 ),
    pTableItemMapper( 0 ),
    pDocElemTokenMap( 0 ),
    pTableElemTokenMap( 0 ),
    pTableCellAttrTokenMap( 0 ),
    pGraphicResolver( 0 ),
    pEmbeddedResolver( 0 ),
    nStyleFamilyMask( SFX_STYLE_FAMILY_ALL ),
    bLoadDoc( sal_True ),
    bInsert( sal_False ),
    bBlock( sal_False ),
    bShowProgress( sal_True ),
    bOrganizerMode( sal_False ),
    bPreserveRedlineMode( sal_True )
{
    _InitItemImport();

}

#ifdef XML_CORE_API
// #110680#
SwXMLImport::SwXMLImport(
    const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory > xServiceFactory,
    SwDoc& rDoc,
    const SwPaM& rPaM,
    sal_Bool bLDoc,
    sal_Bool bInsertMode,
    sal_uInt16 nStyleFamMask,
    const ::com::sun::star::uno::Reference< ::com::sun::star::frame::XModel > & rModel,
    const ::com::sun::star::uno::Reference< ::com::sun::star::document::XGraphicObjectResolver > & rEGO,
    SvStorage *pPkg )
:   SvXMLImport( xServiceFactory, rModel, rEGO ),
    bLoadDoc( bLDoc ),
    bInsert( bInsertMode ),
    nStyleFamilyMask( nStyleFamMask ),
    pDocElemTokenMap( 0 ),
    pTableElemTokenMap( 0 ),
    pTableCellAttrTokenMap( 0 ),
    pTableItemMapper( 0 ),
    pSttNdIdx( 0 ),
    bShowProgress( sal_True ),
    bPreserveRedlineMode( sal_True ),
    xPackage( pPkg )
{
    _InitItemImport();

    Reference < XTextRange > xTextRange =
        SwXTextRange::CreateTextRangeFromPosition( &rDoc, *rPaM.GetPoint(), 0 );
    Reference < XText > xText = xTextRange->getText();
    Reference < XTextCursor > xTextCursor =
        xText->createTextCursorByRange( xTextRange );
    GetTextImport()->SetCursor( xTextCursor );
}
#endif

SwXMLImport::~SwXMLImport() throw ()
{
    delete pDocElemTokenMap;
    delete pTableElemTokenMap;
    delete pTableCellAttrTokenMap;
    _FinitItemImport();
}

const Sequence< sal_Int8 > & SwXMLImport::getUnoTunnelId() throw()
{
    static uno::Sequence< sal_Int8 > aSeq = ::binfilter::CreateUnoTunnelId();
    return aSeq;
}

sal_Int64 SAL_CALL SwXMLImport::getSomething( const Sequence< sal_Int8 >& rId )
    throw(RuntimeException)
{
    if( rId.getLength() == 16
        && 0 == rtl_compareMemory( getUnoTunnelId().getConstArray(),
                                        rId.getConstArray(), 16 ) )
    {
            return (sal_Int64)this;
    }
    return SvXMLImport::getSomething( rId );
}

OTextCursorHelper *lcl_xml_GetSwXTextCursor( const Reference < XTextCursor >& rTextCursor )
{
    Reference<XUnoTunnel> xCrsrTunnel( rTextCursor, UNO_QUERY );
    OSL_ENSURE( xCrsrTunnel.is(), "missing XUnoTunnel for Cursor" );
    if( !xCrsrTunnel.is() )
        return 0;
    OTextCursorHelper *pTxtCrsr =
        (OTextCursorHelper *)xCrsrTunnel->getSomething(
                                            OTextCursorHelper::getUnoTunnelId() );
    OSL_ENSURE( pTxtCrsr, "SwXTextCursor missing" );
    return pTxtCrsr;
}

void SwXMLImport::startDocument( void )
    throw( xml::sax::SAXException, uno::RuntimeException )
{
    // delegate to parent
    SvXMLImport::startDocument();

    DBG_ASSERT( GetModel().is(), "model is missing" );
    if( !GetModel().is() )
        return;

    // this method will modify the document directly -> lock SolarMutex
    SolarMutexGuard aGuard;

    // There only is a text cursor by now if we are in insert mode. In any
    // other case we have to create one at the start of the document.
    // We also might change into the insert mode later, so we have to make
    // sure to first set the insert mode and then create the text import
    // helper. Otherwise it won't have the insert flag set!
    OTextCursorHelper *pTxtCrsr = 0;
    Reference < XTextCursor > xTextCursor;
    if( HasTextImport() )
           xTextCursor = GetTextImport()->GetCursor();
    if( !xTextCursor.is() )
    {
        Reference < XTextDocument > xTextDoc( GetModel(), UNO_QUERY );
        Reference < XText > xText = xTextDoc->getText();
        xTextCursor = xText->createTextCursor();
        SwDoc *pDoc = 0;
        if( IMPORT_ALL == getImportFlags() )
        {
            pTxtCrsr = lcl_xml_GetSwXTextCursor( xTextCursor );
            OSL_ENSURE( pTxtCrsr, "SwXTextCursor missing" );
            if( !pTxtCrsr )
                return;

            pDoc = pTxtCrsr->GetDoc();
            OSL_ENSURE( pDoc, "SwDoc missing" );
            if( !pDoc )
                return;
        }
        GetTextImport()->SetCursor( xTextCursor );
    }

    if( (getImportFlags() & (IMPORT_CONTENT|IMPORT_MASTERSTYLES)) == 0 )
        return;

    if( !pTxtCrsr  )
        pTxtCrsr = lcl_xml_GetSwXTextCursor( xTextCursor );
    OSL_ENSURE( pTxtCrsr, "SwXTextCursor missing" );
    if( !pTxtCrsr )
        return;

    SwDoc *pDoc = pTxtCrsr->GetDoc();
    OSL_ENSURE( pDoc, "SwDoc missing" );
    if( !pDoc )
        return;

    if( (getImportFlags() & IMPORT_CONTENT) != 0 && !IsStylesOnlyMode() )
    {
        pSttNdIdx = new SwNodeIndex( pDoc->GetNodes() );
        if( IsInsertMode() )
        {
            SwPaM *pPaM = pTxtCrsr->GetPaM();
            const SwPosition* pPos = pPaM->GetPoint();

            // Split once and remember the node that has been splitted.
            pDoc->SplitNode( *pPos );
            *pSttNdIdx = pPos->nNode.GetIndex()-1;

            // Split again.
            pDoc->SplitNode( *pPos );

            // Insert all content into the new node
            pPaM->Move( fnMoveBackward );
            pDoc->SetTxtFmtColl
                ( *pPaM, pDoc->GetTxtCollFromPoolSimple(RES_POOLCOLL_STANDARD,
                                                        FALSE) );
        }
    }

    // We need a draw model to be able to set the z order
    pDoc->MakeDrawModel();

    if( !GetGraphicResolver().is() )
    {
        pGraphicResolver = SvXMLGraphicHelper::Create( GRAPHICHELPER_MODE_READ );
        Reference< document::XGraphicObjectResolver > xLclGraphicResolver( pGraphicResolver );
        SetGraphicResolver( xLclGraphicResolver );
    }

    if( !GetEmbeddedResolver().is() )
    {
        SvPersist *pPersist = pDoc->GetPersist();
        if( pPersist )
        {
            pEmbeddedResolver = SvXMLEmbeddedObjectHelper::Create(
                                            *pPersist,
                                            EMBEDDEDOBJECTHELPER_MODE_READ );
            Reference< document::XEmbeddedObjectResolver > xLclEmbeddedResolver( pEmbeddedResolver );
            SetEmbeddedResolver( xLclEmbeddedResolver );
        }
    }
}

void SwXMLImport::endDocument( void )
    throw( xml::sax::SAXException, uno::RuntimeException )
{
    DBG_ASSERT( GetModel().is(), "model missing; maybe startDocument wasn't called?" );
    if( !GetModel().is() )
        return;

    // this method will modify the document directly -> lock SolarMutex
    SolarMutexGuard aGuard;

    if( pGraphicResolver )
        SvXMLGraphicHelper::Destroy( pGraphicResolver );
    if( pEmbeddedResolver )
        SvXMLEmbeddedObjectHelper::Destroy( pEmbeddedResolver );
    // Clear the shape import to sort the shapes  (and not in the
    // destructor that might be called after the import has finished
    // for Java filters.
    if( HasShapeImport() )
        ClearShapeImport();


    SwDoc *pDoc = 0;
    if( (getImportFlags() & IMPORT_CONTENT) != 0 && !IsStylesOnlyMode() )
    {
        Reference<XUnoTunnel> xCrsrTunnel( GetTextImport()->GetCursor(),
                                              UNO_QUERY);
        OSL_ENSURE( xCrsrTunnel.is(), "missing XUnoTunnel for Cursor" );
        OTextCursorHelper *pTxtCrsr =
                (OTextCursorHelper*)xCrsrTunnel->getSomething(
                                            OTextCursorHelper::getUnoTunnelId() );
        OSL_ENSURE( pTxtCrsr, "SwXTextCursor missing" );
        SwPaM *pPaM = pTxtCrsr->GetPaM();
        if( IsInsertMode() && pSttNdIdx->GetIndex() )
        {
            // If we are in insert mode, join the splitted node that is in front
            // of the new content with the first new node. Or in other words:
            // Revert the first split node.
            SwTxtNode* pTxtNode = pSttNdIdx->GetNode().GetTxtNode();
            SwNodeIndex aNxtIdx( *pSttNdIdx );
            if( pTxtNode && pTxtNode->CanJoinNext( &aNxtIdx ) &&
                pSttNdIdx->GetIndex() + 1 == aNxtIdx.GetIndex() )
            {
                // If the PaM points to the first new node, move the PaM to the
                // end of the previous node.
                if( pPaM->GetPoint()->nNode == aNxtIdx )
                {
                    pPaM->GetPoint()->nNode = *pSttNdIdx;
                    pPaM->GetPoint()->nContent.Assign( pTxtNode,
                                            pTxtNode->GetTxt().Len() );
                }

#ifdef DBG_UTIL
                // !!! This should be impossible !!!!
                OSL_ENSURE( pSttNdIdx->GetIndex()+1 !=
                                        pPaM->GetBound( sal_True ).nNode.GetIndex(),
                        "PaM.Bound1 point to new node " );
                OSL_ENSURE( pSttNdIdx->GetIndex()+1 !=
                                        pPaM->GetBound( sal_False ).nNode.GetIndex(),
                        "PaM.Bound2 points to new node" );

                if( pSttNdIdx->GetIndex()+1 ==
                                        pPaM->GetBound( sal_True ).nNode.GetIndex() )
                {
                    sal_uInt16 nCntPos =
                            pPaM->GetBound( sal_True ).nContent.GetIndex();
                    pPaM->GetBound( sal_True ).nContent.Assign( pTxtNode,
                            pTxtNode->GetTxt().Len() + nCntPos );
                }
                if( pSttNdIdx->GetIndex()+1 ==
                                pPaM->GetBound( sal_False ).nNode.GetIndex() )
                {
                    sal_uInt16 nCntPos =
                            pPaM->GetBound( sal_False ).nContent.GetIndex();
                    pPaM->GetBound( sal_False ).nContent.Assign( pTxtNode,
                            pTxtNode->GetTxt().Len() + nCntPos );
                }
#endif
                // If the first new node isn't empty, convert  the node's text
                // attributes into hints. Otherwise, set the new node's
                // paragraph style at the previous (empty) node.
                SwTxtNode* pDelNd = aNxtIdx.GetNode().GetTxtNode();
                if( pTxtNode->GetTxt().Len() )
                    pDelNd->FmtToTxtAttr( pTxtNode );
                else
                    pTxtNode->ChgFmtColl( pDelNd->GetTxtColl() );
                pTxtNode->JoinNext();
            }
        }

        SwPosition* pPos = pPaM->GetPoint();
        DBG_ASSERT( !pPos->nContent.GetIndex(), "last paragraph isn't empty" );
        if( !pPos->nContent.GetIndex() )
        {
            SwTxtNode* pCurrNd;
            ULONG nNodeIdx = pPos->nNode.GetIndex();
            pDoc = pPaM->GetDoc();

            DBG_ASSERT( pPos->nNode.GetNode().IsCntntNode(),
                        "insert position is not a content node" );
            if( !IsInsertMode() )
            {
                // If we're not in insert mode, the last node is deleted.
                const SwNode *pPrev = pDoc->GetNodes()[nNodeIdx -1];
                if( pPrev->IsCntntNode() ||
                     ( pPrev->IsEndNode() &&
                      pPrev->StartOfSectionNode()->IsSectionNode() ) )
                {
                    SwCntntNode* pCNd = pPaM->GetCntntNode();
                    if( pCNd && pCNd->StartOfSectionIndex()+2 <
                        pCNd->EndOfSectionIndex() )
                    {
                        pPaM->GetBound(sal_True).nContent.Assign( 0, 0 );
                        pPaM->GetBound(sal_False).nContent.Assign( 0, 0 );
                        pDoc->GetNodes().Delete( pPaM->GetPoint()->nNode );
                    }
                }
            }
            else if( 0 != (pCurrNd = pDoc->GetNodes()[nNodeIdx]->GetTxtNode()) )
            {
                // Id we're in insert mode, the empty node is joined with
                // the next and the previous one.
                if( pCurrNd->CanJoinNext( &pPos->nNode ))
                {
                    SwTxtNode* pNextNd = pPos->nNode.GetNode().GetTxtNode();
                    pPos->nContent.Assign( pNextNd, 0 );
                    pPaM->SetMark(); pPaM->DeleteMark();
                    pNextNd->JoinPrev();

                    // Remove line break that has been inserted by the import,
                    // but only if one has been inserted!
                    if( pNextNd->CanJoinPrev(/* &pPos->nNode*/ ) &&
                         *pSttNdIdx != pPos->nNode )
                    {
//                      SwTxtNode* pPrevNd = pPos->nNode.GetNode().GetTxtNode();
//                      pPos->nContent.Assign( pPrevNd, 0 );
//                      pPaM->SetMark(); pPaM->DeleteMark();
//                      pPrevNd->JoinNext();
                        pNextNd->JoinPrev();
                    }
                }
                else if( !pCurrNd->GetTxt().Len() )
                {
                    pPos->nContent.Assign( 0, 0 );
                    pPaM->SetMark(); pPaM->DeleteMark();
                    pDoc->GetNodes().Delete( pPos->nNode, 1 );
                    pPaM->Move( fnMoveBackward );
                }
            }
        }
    }

    /* #108146# Was called too early. Moved from
        SwXMLBodyContext_Impl::EndElement */

    GetTextImport()->RedlineAdjustStartNodeCursor( sal_False );

    if( (getImportFlags() & IMPORT_CONTENT) != 0 ||
        ((getImportFlags() & IMPORT_MASTERSTYLES) != 0 && IsStylesOnlyMode()) )
    {
        // pDoc might be 0. In this case UpdateTxtCollCondition is looking
        // for it itself.
        UpdateTxtCollConditions( pDoc );
    }

    GetTextImport()->ResetCursor();

    delete pSttNdIdx;
    pSttNdIdx = 0;

    if( (getImportFlags() == IMPORT_ALL ) )
    {
        // Notify math objects. If we are in the package filter this will
        // be done by the filter object itself
        if( IsInsertMode() )
            pDoc->PrtOLENotify( FALSE );
        else if ( pDoc->IsOLEPrtNotifyPending() )
            pDoc->PrtOLENotify( TRUE );
    }

    // delegate to parent: takes care of error handling
    SvXMLImport::endDocument();
}


// Locally derive XMLTextShapeImportHelper, so we can take care of the
// form import This is Writer, but not text specific, so it should go
// here!
class SvTextShapeImportHelper : public XMLTextShapeImportHelper
{
    // hold own reference form import helper, because the SvxImport
    // stored in the superclass, from whom we originally got the
    // reference, is already destroyed when we want to use it in the
    // destructor
    UniReference< ::binfilter::xmloff::OFormLayerXMLImport > rFormImport;

    // hold reference to the one page (if it exists) for calling startPage()
    // and endPage. If !xPage.is(), then this document doesn't have a
    // XDrawPage.
    Reference<drawing::XDrawPage> xPage;

public:

    SvTextShapeImportHelper(SvXMLImport& rImp);
    virtual ~SvTextShapeImportHelper();
};

SvTextShapeImportHelper::SvTextShapeImportHelper(SvXMLImport& rImp) :
    XMLTextShapeImportHelper(rImp)
{
    Reference<drawing::XDrawPageSupplier> xSupplier(rImp.GetModel(),UNO_QUERY);
    if (xSupplier.is())
    {
        if (rImp.GetFormImport().is())
        {
            rImp.GetFormImport()->startPage(xSupplier->getDrawPage());
            rFormImport = rImp.GetFormImport();
        }

        xPage  = xSupplier->getDrawPage();
        Reference<XShapes> xShapes( xPage, UNO_QUERY );
        XMLShapeImportHelper::startPage( xShapes );
    }
}

SvTextShapeImportHelper::~SvTextShapeImportHelper()
{
    rFormImport->endPage();

    if (xPage.is())
    {
        Reference<XShapes> xShapes( xPage, UNO_QUERY );
        XMLShapeImportHelper::endPage(xShapes);
    }
}


XMLShapeImportHelper* SwXMLImport::CreateShapeImport()
{
    return new SvTextShapeImportHelper( *this );
}

SvXMLImportContext *SwXMLImport::CreateFontDeclsContext(
        const OUString& rLocalName,
        const Reference< xml::sax::XAttributeList > & xAttrList )
{
    XMLFontStylesContext *pFSContext =
            new XMLFontStylesContext( *this, XML_NAMESPACE_OFFICE,
                                      rLocalName, xAttrList,
                                      osl_getThreadTextEncoding() );
    SetFontDecls( pFSContext );
    return pFSContext;
}
void SwXMLImport::SetViewSettings(const Sequence < PropertyValue > & aViewProps)
{
    if (IsInsertMode() || IsStylesOnlyMode() || IsBlockMode() || IsOrganizerMode() || !GetModel().is() )
        return;

    // this method will modify the document directly -> lock SolarMutex
    SolarMutexGuard aGuard;

    Reference < XTextDocument > xTextDoc( GetModel(), UNO_QUERY );
    Reference < XText > xText = xTextDoc->getText();
    Reference<XUnoTunnel> xTextTunnel( xText, UNO_QUERY);
    OSL_ENSURE( xTextTunnel.is(), "missing XUnoTunnel for Cursor" );
    if( !xTextTunnel.is() )
        return;

    SwXText *pText = (SwXText *)xTextTunnel->getSomething(
                                        SwXText::getUnoTunnelId() );
    OSL_ENSURE( pText, "SwXText missing" );
    if( !pText )
        return;

    SwDoc *pDoc = pText->GetDoc();
    Rectangle aRect;
    if( pDoc->GetDocShell() )
        aRect = ((SfxInPlaceObject *)pDoc->GetDocShell())->GetVisArea();

    sal_Int32 nCount = aViewProps.getLength();
    const PropertyValue *pValue = aViewProps.getConstArray();

    long nTmp(0);
    sal_Bool bShowRedlineChanges = sal_False, bBrowseMode = sal_False,
             bShowFooter = sal_False, bShowHeader = sal_False;
    sal_Bool bChangeShowRedline = sal_False, bChangeBrowseMode = sal_False,
             bChangeFooter = sal_False, bChangeHeader = sal_False;

    sal_Bool bTwip = pDoc->GetDocShell()->SfxInPlaceObject::GetMapUnit ( ) == MAP_TWIP;

    for (sal_Int32 i = 0; i < nCount ; i++)
    {
        if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM ( "ViewAreaTop" ) ) )
        {
            pValue->Value >>= nTmp;
            aRect.setY( bTwip ? MM100_TO_TWIP ( nTmp ) : nTmp );
        }
        else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM ( "ViewAreaLeft" ) ) )
        {
            pValue->Value >>= nTmp;
            aRect.setX( bTwip ? MM100_TO_TWIP ( nTmp ) : nTmp );
        }
        else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM ( "ViewAreaWidth" ) ) )
        {
            pValue->Value >>= nTmp;
            Size aSize( aRect.GetSize() );
            aSize.Width() = bTwip ? MM100_TO_TWIP ( nTmp ) : nTmp;
            aRect.SetSize( aSize );
        }
        else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM ( "ViewAreaHeight" ) ) )
        {
            pValue->Value >>= nTmp;
            Size aSize( aRect.GetSize() );
            aSize.Height() = bTwip ? MM100_TO_TWIP ( nTmp ) : nTmp;
            aRect.SetSize( aSize );
        }
        else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM ( "ShowRedlineChanges" ) ) )
        {
            bShowRedlineChanges = *(sal_Bool *)(pValue->Value.getValue());
            bChangeShowRedline = sal_True;
        }
        else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM ( "ShowHeaderWhileBrowsing" ) ) )
        {
            bShowHeader = *(sal_Bool *)(pValue->Value.getValue());
            bChangeFooter = sal_True;
        }
        else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM ( "ShowFooterWhileBrowsing" ) ) )
        {
            bShowFooter = *(sal_Bool *)(pValue->Value.getValue());
            bChangeHeader = sal_True;
        }
        else if (pValue->Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM ( "InBrowseMode" ) ) )
        {
            bBrowseMode = *(sal_Bool *)(pValue->Value.getValue());
            bChangeBrowseMode = sal_True;
        }
        pValue++;
    }
    if( pDoc->GetDocShell() )
        pDoc->GetDocShell()->SetVisArea ( aRect );

    if (bChangeHeader)
        pDoc->SetHeadInBrowse ( bShowHeader );
    if (bChangeFooter)
        pDoc->SetFootInBrowse ( bShowFooter );
    if (bChangeBrowseMode)
        pDoc->SetBrowseMode ( bBrowseMode );
    if (bChangeShowRedline)
        GetTextImport()->SetShowChanges( bShowRedlineChanges );
}

void SwXMLImport::SetConfigurationSettings(const Sequence < PropertyValue > & aConfigProps)
{
    // this method will modify the document directly -> lock SolarMutex
    SolarMutexGuard aGuard;

    Reference< lang::XMultiServiceFactory > xFac( GetModel(), UNO_QUERY );
    if( !xFac.is() )
        return;

    Reference< XPropertySet > xProps( xFac->createInstance( OUString( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.document.Settings" ) ) ), UNO_QUERY );
    if( !xProps.is() )
        return;

    Reference< XPropertySetInfo > xInfo( xProps->getPropertySetInfo() );
    if( !xInfo.is() )
        return;

    // static array of setting names which are not loaded.
    // This table is created with the iout commended procedure. This will
    // be need if anybody add more or change strings!!!
    /*
        program to calculate the best hash parameters for the property names.
-----------------------------------------------------------------
#include <stdio.h>
#include <string.h>

#include <sal/macros.h>

 const char* aNmArr[] = {
 "ForbiddenCharacters" ,
 "IsKernAsianPunctuation" ,
 "CharacterCompressionType" ,
 "LinkUpdateMode" ,
 "FieldAutoUpdate" ,
 "ChartAutoUpdate" ,
 "AddParaTableSpacing" ,
 "AddParaTableSpacingAtStart" ,
 "PrintAnnotationMode" ,
 "PrintBlackFonts" ,
 "PrintControls" ,
 "PrintDrawings" ,
 "PrintGraphics" ,
 "PrintLeftPages" ,
 "PrintPageBackground" ,
 "PrintProspect" ,
 "PrintReversed" ,
 "PrintRightPages" ,
 "PrintFaxName" ,
 "PrintPaperFromSetup" ,
 "PrintTables" ,
 "PrintSingleJobs",
 "UpdateFromTemplate",
 "PrinterIndependentLayout"
  };
#define TBL_MAX 100
int aArr[ TBL_MAX ];
int nPrime, nSub;

unsigned long calc_hash( const char* p )
{
    unsigned long ii = 0;
    while( *p )
        ii = (ii * nPrime) ^ ( *p++ - nSub );
    return ii;
}
int Chk_Unique_hashValue( unsigned short nTblSize )
{
    memset( aArr, 0, sizeof( aArr ) );
    unsigned long ii;
    for( int n = 0; n < SAL_N_ELEMENTS( aNmArr ); ++n )
    {
        ii = calc_hash( aNmArr[ n ] ) % nTblSize;
        if( aArr[ ii ] )
            break;
        aArr[ ii ] = 1;
    }
    return n == SAL_N_ELEMENTS( aNmArr );
}

void Show_Result( unsigned short nTblSize )
{
    printf( "\nTblSz = %d\n", nTblSize );
    for( int n = 0; n < SAL_N_ELEMENTS( aNmArr ); ++n )
    {
        unsigned long ii = calc_hash( aNmArr[ n ] ) % nTblSize;
        printf( "%-30s -> %3d\n", aNmArr[ n ], ii );
    }
}

void main()
{
    int nPrm = nPrime, nSb = nSub;
    unsigned short nLTbl = TBL_MAX, nTblSize;

    for( nSub = ' '; nSub < 127; ++nSub )
        for( nPrime = 13 ; nPrime < 99; ++nPrime )
            for( nTblSize = SAL_N_ELEMENTS( aNmArr );
                    nTblSize < TBL_MAX; ++nTblSize )
                if( Chk_Unique_hashValue( nTblSize ))
                {
                    if( nLTbl > nTblSize )
                    {
                        nLTbl = nTblSize;
                        nPrm = nPrime;
                        nSb = nSub;
                    }
                    break;
                }

    nPrime = nPrm;
    nSub = nSb;
    nTblSize = nLTbl;

    Show_Result( nTblSize );
    printf( "\nPrime: %d, nSub: %d, TblSz = %d - %d", nPrime, nSub,
            SAL_N_ELEMENTS( aNmArr ), nTblSize );
}
-----------------------------------------------------------------
    */
        static const struct {
                const sal_Char* pName;
                sal_uInt16 nLen;
    }  aNotSetArr[40] = {
/* 0*/      {0,0},
/* 1*/      {RTL_CONSTASCII_STRINGPARAM( "PrintTables" )},
/* 2*/      {RTL_CONSTASCII_STRINGPARAM( "ForbiddenCharacters" )},
/* 3*/      {0,0},
/* 4*/      {0,0},
/* 5*/      {RTL_CONSTASCII_STRINGPARAM( "AddParaTableSpacingAtStart" )},
/* 6*/      {0,0},
/* 7*/      {RTL_CONSTASCII_STRINGPARAM( "CharacterCompressionType" )},
/* 8*/      {0,0},
/* 9*/      {RTL_CONSTASCII_STRINGPARAM( "PrintDrawings" )},
/*10*/      {RTL_CONSTASCII_STRINGPARAM( "PrintRightPages" )},
/*11*/      {RTL_CONSTASCII_STRINGPARAM( "PrintPageBackground" )},
/*12*/      {RTL_CONSTASCII_STRINGPARAM( "LinkUpdateMode" )},
/*13*/      {RTL_CONSTASCII_STRINGPARAM( "UpdateFromTemplate" )},
/*14*/      {0,0},
/*15*/      {RTL_CONSTASCII_STRINGPARAM( "PrintBlackFonts" )},
/*16*/      {RTL_CONSTASCII_STRINGPARAM( "PrintSingleJobs" )},
/*17*/      {RTL_CONSTASCII_STRINGPARAM( "ChartAutoUpdate" )},
/*18*/      {RTL_CONSTASCII_STRINGPARAM( "IsKernAsianPunctuation" )},
/*19*/      {RTL_CONSTASCII_STRINGPARAM( "AddParaTableSpacing" )},
/*20*/      {0,0},
/*21*/      {0,0},
/*22*/      {0,0},
/*23*/      {0,0},
/*24*/      {RTL_CONSTASCII_STRINGPARAM( "PrintReversed" )},
/*25*/      {RTL_CONSTASCII_STRINGPARAM( "FieldAutoUpdate" )},
/*26*/      {RTL_CONSTASCII_STRINGPARAM( "PrintProspect" )},
/*27*/      {0,0},
/*28*/      {RTL_CONSTASCII_STRINGPARAM( "PrintControls" )},
/*29*/      {0,0},
/*30*/      {RTL_CONSTASCII_STRINGPARAM( "PrintAnnotationMode" )},
/*31*/      {RTL_CONSTASCII_STRINGPARAM( "PrintGraphics" )},
/*32*/      {RTL_CONSTASCII_STRINGPARAM( "PrinterIndependentLayout" )},
/*33*/      {0,0},
/*34*/      {0,0},
/*35*/      {RTL_CONSTASCII_STRINGPARAM( "PrintPaperFromSetup" )},
/*36*/      {RTL_CONSTASCII_STRINGPARAM( "PrintLeftPages" )},
/*37*/      {RTL_CONSTASCII_STRINGPARAM( "PrintFaxName" )},
/*38*/      {0,0},
/*39*/      {0,0},
    };
    const ULONG nPrime = 51;
    const ULONG nSub = 51;

    sal_Int32 nCount = aConfigProps.getLength();
    const PropertyValue* pValues = aConfigProps.getConstArray();

    SvtSaveOptions aSaveOpt;
    BOOL bIsUserSetting = aSaveOpt.IsLoadUserSettings(),
         bSet = bIsUserSetting;

    // for some properties we don't want to use the application
    // default if they're missing. So we watch for them in the loop
    // below, and set them if not found
    bool bPrinterIndependentLayout = false;

    while( nCount-- )
    {
        ULONG nHash = 0;
        if( !bIsUserSetting )
        {
            // test over the hash value if the entry is in the table.
            const sal_Unicode* p = pValues->Name.getStr();
            for( ULONG nLen = pValues->Name.getLength(); nLen; --nLen, ++p )
                nHash = (nHash * nPrime) ^ ( *p - nSub );
            nHash %= SAL_N_ELEMENTS( aNotSetArr );
            bSet = 0 == aNotSetArr[ nHash ].pName ||
                    !pValues->Name.equalsAsciiL(
                            aNotSetArr[ nHash ].pName,
                            aNotSetArr[ nHash ].nLen );
        }

        if( bSet )
        {
            try
            {
                if( xInfo->hasPropertyByName( pValues->Name ) )
                {
                    xProps->setPropertyValue( pValues->Name, pValues->Value );
                }

                // did we find any of the non-default cases?
                if( pValues->Name.equalsAsciiL(RTL_CONSTASCII_STRINGPARAM("PrinterIndependentLayout")) )
                    bPrinterIndependentLayout = true;

            }
            catch( Exception& )
            {
                OSL_FAIL( "SwXMLImport::SetConfigurationSettings: Exception!" );
            }
        }
        pValues++;
    }

    // finally, treat the non-default cases
    if( ! bPrinterIndependentLayout )
    {
        Any aAny;
        sal_Int16 nTmp = document::PrinterIndependentLayout::DISABLED;
        aAny <<= nTmp;
        xProps->setPropertyValue(
            OUString( RTL_CONSTASCII_USTRINGPARAM("PrinterIndependentLayout") ),
            aAny );
    }

    Reference < XTextDocument > xTextDoc( GetModel(), UNO_QUERY );
    Reference < XText > xText = xTextDoc->getText();
    Reference<XUnoTunnel> xTextTunnel( xText, UNO_QUERY);
    OSL_ENSURE( xTextTunnel.is(), "missing XUnoTunnel for Cursor" );
    if( xTextTunnel.is() )
    {
        SwXText *pText = (SwXText *)xTextTunnel->getSomething(
                                        SwXText::getUnoTunnelId() );
        OSL_ENSURE( pText, "SwXText missing" );
        if( pText )
        {
            SwDoc *pDoc = pText->GetDoc();
            if( pDoc )
            {
                // If the printer is known, then the OLE objects will
                // already have correct sizes, and we don't have to call
                // PrtOLENotify again. Otherwise we have to call it.
                // The flag might be set from setting the printer, so it
                // it is required to clear it.
                SfxPrinter *pPrinter = pDoc->GetPrt( sal_False );
                if( pPrinter )
                    pDoc->SetOLEPrtNotifyPending( !pPrinter->IsKnown() );
            }
        }
    }
}


void SwXMLImport::initialize(
    const Sequence<Any>& aArguments )
    throw( uno::Exception, uno::RuntimeException)
{
    // delegate to super class
    SvXMLImport::initialize(aArguments);

    // we are only looking for a PropertyValue "PreserveRedlineMode"
    sal_Int32 nLength = aArguments.getLength();
    for(sal_Int32 i = 0; i < nLength; i++)
    {
        if (aArguments[i].getValueType() ==
            ::getCppuType((const beans::PropertyValue*)0) )
        {
            beans::PropertyValue aValue;
            aArguments[i] >>= aValue;

            if (aValue.Name.equalsAsciiL(
                RTL_CONSTASCII_STRINGPARAM("PreserveRedlineMode")))
            {
                bPreserveRedlineMode = *(sal_Bool*)aValue.Value.getValue();
            }
        }
    }
}


//
// UNO component registration helper functions
//

OUString SAL_CALL SwXMLImport_getImplementationName() throw()
{
    return OUString( RTL_CONSTASCII_USTRINGPARAM(
        "com.sun.star.comp.Writer.XMLImporter" ) );
}

uno::Sequence< OUString > SAL_CALL SwXMLImport_getSupportedServiceNames()
    throw()
{
    const OUString aServiceName( SwXMLImport_getImplementationName() );
    const uno::Sequence< OUString > aSeq( &aServiceName, 1 );
    return aSeq;
}

uno::Reference< uno::XInterface > SAL_CALL SwXMLImport_createInstance(
        const uno::Reference< lang::XMultiServiceFactory > & rSMgr)
    throw( uno::Exception )
{
    // #110680#
    // return (cppu::OWeakObject*)new SwXMLImport(IMPORT_ALL);
    return (cppu::OWeakObject*)new SwXMLImport( rSMgr, IMPORT_ALL );
}

OUString SAL_CALL SwXMLImportStyles_getImplementationName() throw()
{
    return OUString( RTL_CONSTASCII_USTRINGPARAM(
        "com.sun.star.comp.Writer.XMLStylesImporter" ) );
}

uno::Sequence< OUString > SAL_CALL SwXMLImportStyles_getSupportedServiceNames()
    throw()
{
    const OUString aServiceName( SwXMLImportStyles_getImplementationName() );
    const uno::Sequence< OUString > aSeq( &aServiceName, 1 );
    return aSeq;
}

uno::Reference< uno::XInterface > SAL_CALL SwXMLImportStyles_createInstance(
        const uno::Reference< lang::XMultiServiceFactory > & rSMgr)
    throw( uno::Exception )
{
    // #110680#
    //return (cppu::OWeakObject*)new SwXMLImport(
    //  IMPORT_STYLES | IMPORT_MASTERSTYLES | IMPORT_AUTOSTYLES |
    //  IMPORT_FONTDECLS );
    return (cppu::OWeakObject*)new SwXMLImport(
        rSMgr,
        IMPORT_STYLES | IMPORT_MASTERSTYLES | IMPORT_AUTOSTYLES |
        IMPORT_FONTDECLS );
}

OUString SAL_CALL SwXMLImportContent_getImplementationName() throw()
{
    return OUString( RTL_CONSTASCII_USTRINGPARAM(
        "com.sun.star.comp.Writer.XMLContentImporter" ) );
}

uno::Sequence< OUString > SAL_CALL SwXMLImportContent_getSupportedServiceNames()
    throw()
{
    const OUString aServiceName( SwXMLImportContent_getImplementationName() );
    const uno::Sequence< OUString > aSeq( &aServiceName, 1 );
    return aSeq;
}

uno::Reference< uno::XInterface > SAL_CALL SwXMLImportContent_createInstance(
        const uno::Reference< lang::XMultiServiceFactory > & rSMgr)
    throw( uno::Exception )
{
    // #110680#
    //return (cppu::OWeakObject*)new SwXMLImport(
    //  IMPORT_AUTOSTYLES | IMPORT_CONTENT | IMPORT_SCRIPTS |
    //  IMPORT_FONTDECLS );
    return (cppu::OWeakObject*)new SwXMLImport(
        rSMgr,
        IMPORT_AUTOSTYLES | IMPORT_CONTENT | IMPORT_SCRIPTS |
        IMPORT_FONTDECLS );
}

OUString SAL_CALL SwXMLImportMeta_getImplementationName() throw()
{
    return OUString( RTL_CONSTASCII_USTRINGPARAM(
        "com.sun.star.comp.Writer.XMLMetaImporter" ) );
}

uno::Sequence< OUString > SAL_CALL SwXMLImportMeta_getSupportedServiceNames()
    throw()
{
    const OUString aServiceName( SwXMLImportMeta_getImplementationName() );
    const uno::Sequence< OUString > aSeq( &aServiceName, 1 );
    return aSeq;
}

uno::Reference< uno::XInterface > SAL_CALL SwXMLImportMeta_createInstance(
        const uno::Reference< lang::XMultiServiceFactory > & rSMgr)
    throw( uno::Exception )
{
    // #110680#
    // return (cppu::OWeakObject*)new SwXMLImport( IMPORT_META );
    return (cppu::OWeakObject*)new SwXMLImport( rSMgr, IMPORT_META );
}

OUString SAL_CALL SwXMLImportSettings_getImplementationName() throw()
{
    return OUString( RTL_CONSTASCII_USTRINGPARAM(
        "com.sun.star.comp.Writer.XMLSettingsImporter" ) );
}

uno::Sequence< OUString > SAL_CALL SwXMLImportSettings_getSupportedServiceNames()
    throw()
{
    const OUString aServiceName( SwXMLImportSettings_getImplementationName() );
    const uno::Sequence< OUString > aSeq( &aServiceName, 1 );
    return aSeq;
}

uno::Reference< uno::XInterface > SAL_CALL SwXMLImportSettings_createInstance(
        const uno::Reference< lang::XMultiServiceFactory > & rSMgr)
    throw( uno::Exception )
{
    // #110680#
    // return (cppu::OWeakObject*)new SwXMLImport( IMPORT_SETTINGS );
    return (cppu::OWeakObject*)new SwXMLImport( rSMgr, IMPORT_SETTINGS );
}


// XServiceInfo
// override empty method from parent class
OUString SAL_CALL SwXMLImport::getImplementationName()
    throw(RuntimeException)
{
    switch( getImportFlags() )
    {
        case IMPORT_ALL:
            return SwXMLImport_getImplementationName();
            break;
        case (IMPORT_STYLES|IMPORT_MASTERSTYLES|IMPORT_AUTOSTYLES|IMPORT_FONTDECLS):
            return SwXMLImportStyles_getImplementationName();
            break;
        case (IMPORT_AUTOSTYLES|IMPORT_CONTENT|IMPORT_SCRIPTS|IMPORT_FONTDECLS):
            return SwXMLImportContent_getImplementationName();
            break;
        case IMPORT_META:
            return SwXMLImportMeta_getImplementationName();
            break;
        case IMPORT_SETTINGS:
            return SwXMLImportSettings_getImplementationName();
            break;
        default:
            // generic name for 'unknown' cases
            return OUString( RTL_CONSTASCII_USTRINGPARAM(
                "com.sun.star.comp.Writer.SwXMLImport" ) );
            break;
    }
}
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
