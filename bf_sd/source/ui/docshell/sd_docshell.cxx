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

#define ITEMID_FONTLIST                 SID_ATTR_CHAR_FONTLIST
#define ITEMID_COLOR_TABLE              SID_COLOR_TABLE
#define ITEMID_GRADIENT_LIST            SID_GRADIENT_LIST
#define ITEMID_HATCH_LIST               SID_HATCH_LIST
#define ITEMID_BITMAP_LIST              SID_BITMAP_LIST
#define ITEMID_DASH_LIST                SID_DASH_LIST
#define ITEMID_LINEEND_LIST             SID_LINEEND_LIST
#define ITEMID_SEARCH                   SID_SEARCH_ITEM

#include <com/sun/star/document/PrinterIndependentLayout.hpp>

#include <comphelper/classids.hxx>

#include <tools/urlobj.hxx>
#include <sot/formats.hxx>

#include <bf_svtools/ctrltool.hxx>
#include <bf_svtools/flagitem.hxx>
#include <bf_svtools/itemset.hxx>

#include <bf_sfx2/docfile.hxx>
#include <bf_sfx2/app.hxx>
#include <bf_sfx2/printer.hxx>
#include <bf_svx/svxids.hrc>
#include <bf_svx/flstitem.hxx>
#include <bf_svx/drawitem.hxx>
#include <bf_sfx2/docfilt.hxx>

#include "sdresid.hxx"
#include "strings.hrc"
#include "optsitem.hxx"
#include "sdattr.hxx"
#include "bf_sd/docshell.hxx"
#include "drawdoc.hxx"
#include "unomodel.hxx"
#include "sdfilter.hxx"
#include "sdpage.hxx"
#include "sdbinfilter.hxx"
#include "sdoutl.hxx"

namespace binfilter
{
TYPEINIT1( SdDrawDocShell, SfxObjectShell );

SFX_IMPL_OBJECTFACTORY_LOD(SdDrawDocShell, simpress, SvGlobalName(BF_SO3_SIMPRESS_CLASSID), Sd)

void SdDrawDocShell::Construct()
{
    bInDestruction = FALSE;
    SetSlotFilter();
    SetShell(this);

    pDoc = new SdDrawDocument(eDocType, this);
    SetModel( new SdXImpressDocument( this ) );
    SetPool( &pDoc->GetItemPool() );
    UpdateTablePointers();
    SetStyleFamily(5);
}

SdDrawDocShell::SdDrawDocShell(SfxObjectCreateMode eMode, BOOL bDataObject, DocumentType eDocumentType) :
    SfxObjectShell(eMode),
    pProgress(NULL),
    pDoc(NULL),
    pPrinter(NULL),
    eDocType(eDocumentType),
    bUIActive(FALSE),
    bSdDataObj(bDataObject),
    bOwnPrinter(FALSE),
    mbNewDocument( sal_True )
{
    Construct();
}

SdDrawDocShell::~SdDrawDocShell()
{
    bInDestruction = TRUE;

    if (bOwnPrinter)
        delete pPrinter;

    delete pDoc;

}

void SdDrawDocShell::Deactivate( BOOL )
{
}

void SdDrawDocShell::UpdateTablePointers()
{
    PutItem( SvxColorTableItem( pDoc->GetColorTable() ) );
    PutItem( SvxGradientListItem( pDoc->GetGradientList() ) );
    PutItem( SvxHatchListItem( pDoc->GetHatchList() ) );
    PutItem( SvxBitmapListItem( pDoc->GetBitmapList() ) );
    PutItem( SvxDashListItem( pDoc->GetDashList() ) );
    PutItem( SvxLineEndListItem( pDoc->GetLineEndList() ) );
}

void SdDrawDocShell::SetModified( BOOL bSet /* = TRUE */ )
{
    SfxInPlaceObject::SetModified( bSet );

    if( IsEnableSetModified() && pDoc )
        pDoc->NbcSetChanged( bSet );

    Broadcast( SfxSimpleHint( SFX_HINT_DOCCHANGED ) );
}


void SdDrawDocShell::SetVisArea(const Rectangle& rRect)
{
    if (GetCreateMode() == SFX_CREATE_MODE_EMBEDDED)
    {
        SfxInPlaceObject::SetVisArea(rRect);
    }
    else
    {
        SvEmbeddedObject::SetVisArea(rRect);
    }
}

Rectangle SdDrawDocShell::GetVisArea(USHORT nAspect) const
{
    Rectangle aLclVisArea;

    if( ( ASPECT_THUMBNAIL == nAspect ) || ( ASPECT_DOCPRINT == nAspect ) )
    {
         MapMode aSrcMapMode(MAP_PIXEL);
         MapMode aDstMapMode(MAP_100TH_MM);
         Size aSize = pDoc->GetSdPage(0, PK_STANDARD)->GetSize();
         aSrcMapMode.SetMapUnit(MAP_100TH_MM);

         aSize = Application::GetDefaultDevice()->LogicToLogic(aSize, &aSrcMapMode, &aDstMapMode);
         aLclVisArea.SetSize(aSize);
    }
    else
    {
        aLclVisArea = SfxInPlaceObject::GetVisArea(nAspect);
    }

    return (aLclVisArea);
}


SfxPrinter* SdDrawDocShell::GetPrinter(BOOL bCreate)
{
    if (bCreate && !pPrinter)
    {
        // ItemSet mit speziellem Poolbereich anlegen
        SfxItemSet* pSet = new SfxItemSet( GetPool(),
                            SID_PRINTER_NOTFOUND_WARN,  SID_PRINTER_NOTFOUND_WARN,
                            SID_PRINTER_CHANGESTODOC,   SID_PRINTER_CHANGESTODOC,
                            ATTR_OPTIONS_PRINT,         ATTR_OPTIONS_PRINT,
                            0 );
        // PrintOptionsSet setzen
        SdOptionsPrintItem aPrintItem( ATTR_OPTIONS_PRINT,
                            SD_MOD()->GetSdOptions(pDoc->GetDocumentType()));
        SfxFlagItem aFlagItem( SID_PRINTER_CHANGESTODOC );
        USHORT      nFlags = 0;

        nFlags =  (aPrintItem.IsWarningSize() ? SFX_PRINTER_CHG_SIZE : 0) |
                (aPrintItem.IsWarningOrientation() ? SFX_PRINTER_CHG_ORIENTATION : 0);
        aFlagItem.SetValue( nFlags );

        pSet->Put( aPrintItem );
        pSet->Put( SfxBoolItem( SID_PRINTER_NOTFOUND_WARN, aPrintItem.IsWarningPrinter() ) );
        pSet->Put( aFlagItem );

        pPrinter = new SfxPrinter(pSet);
        bOwnPrinter = TRUE;

        // Ausgabequalitaet setzen
        UINT16 nQuality = aPrintItem.GetOutputQuality();

        ULONG nMode = DRAWMODE_DEFAULT;

        if( nQuality == 1 )
            nMode = DRAWMODE_GRAYLINE | DRAWMODE_GRAYFILL | DRAWMODE_BLACKTEXT | DRAWMODE_GRAYBITMAP | DRAWMODE_GRAYGRADIENT;
        else if( nQuality == 2 )
            nMode = DRAWMODE_BLACKLINE | DRAWMODE_BLACKTEXT | DRAWMODE_WHITEFILL | DRAWMODE_GRAYBITMAP | DRAWMODE_WHITEGRADIENT;

        pPrinter->SetDrawMode( nMode );

        MapMode aMM (pPrinter->GetMapMode());
        aMM.SetMapUnit(MAP_100TH_MM);
        pPrinter->SetMapMode(aMM);
        UpdateRefDevice();
    }
    return pPrinter;
}

void SdDrawDocShell::SetPrinter(SfxPrinter *pNewPrinter)
{
    if ( pPrinter && bOwnPrinter && (pPrinter != pNewPrinter) )
    {
        delete pPrinter;
    }

    pPrinter = pNewPrinter;
    bOwnPrinter = TRUE;

    UpdateRefDevice();
}

Printer* SdDrawDocShell::GetDocumentPrinter()
{
    return GetPrinter(FALSE);
}

void SdDrawDocShell::UpdateRefDevice()
{
    if( pDoc )
    {
        // Determine the device for which the output will be formatted.
        OutputDevice* pRefDevice = NULL;
        switch (pDoc->GetPrinterIndependentLayout())
        {
            case ::com::sun::star::document::PrinterIndependentLayout::DISABLED:
                pRefDevice = pPrinter;
                break;

            case ::com::sun::star::document::PrinterIndependentLayout::ENABLED:
                pRefDevice = SD_MOD()->GetVirtualRefDevice();
                break;

            default:
                // We are confronted with an invalid or un-implemented
                // layout mode.  Use the printer as formatting device
                // as a fall-back.
                DBG_ASSERT(false, "SdDrawDocShell::UpdateRefDevice(): Unexpected printer layout mode");

                pRefDevice = pPrinter;
                break;
        }
        pDoc->SetRefDevice( pRefDevice );

        SdOutliner* pOutl = pDoc->GetOutliner( FALSE );

        if( pOutl )
/*?*/           pOutl->SetRefDevice( pRefDevice );

        SdOutliner* pInternalOutl = pDoc->GetInternalOutliner( FALSE );

        if( pInternalOutl )
            pInternalOutl->SetRefDevice( pRefDevice );
    }
}

BOOL SdDrawDocShell::InitNew( SvStorage * pStor )
{
    BOOL bRet = SfxInPlaceObject::InitNew( pStor );

    Rectangle aLclVisArea( Point(0, 0), Size(14100, 10000) );
    SetVisArea(aLclVisArea);

    if (bRet)
    {
        if( !bSdDataObj )
            pDoc->NewOrLoadCompleted(NEW_DOC);
    }
    return bRet;
}

BOOL SdDrawDocShell::Load( SvStorage* pStore )
{
    mbNewDocument = sal_False;

    ULONG   nStoreVer = pStore->GetVersion();
    BOOL    bRet = FALSE;
    BOOL    bXML = ( nStoreVer >= SOFFICE_FILEFORMAT_60 );
    BOOL    bBinary = ( nStoreVer < SOFFICE_FILEFORMAT_60 );

    if( bBinary || bXML )
    {
        bRet = SfxInPlaceObject::Load( pStore );

        if( bRet )
        {
            SdFilter*   pFilter = NULL;
            SfxMedium* pLclMedium = 0L;

            if( bBinary )
            {
                pLclMedium = new SfxMedium( pStore );
                pFilter = new SdBINFilter( *pLclMedium, *this, sal_True );
            }
            else if( bXML )
            {
                OSL_ASSERT("XML import removed");
            }

            bRet = pFilter ? pFilter->Import() : FALSE;


            if(pFilter)
                delete pFilter;
            if(pLclMedium)
                delete pLclMedium;
        }
    }
    else
        pStore->SetError( SVSTREAM_WRONGVERSION );

    if( bRet )
    {
        UpdateTablePointers();

        if( ( GetCreateMode() == SFX_CREATE_MODE_EMBEDDED ) && SfxInPlaceObject::GetVisArea( ASPECT_CONTENT ).IsEmpty() )
        {
            SdPage* pPage = pDoc->GetSdPage( 0, PK_STANDARD );
            if( pPage )
                SetVisArea( Rectangle( pPage->GetAllObjBoundRect() ) );
        }

        FinishedLoading( SFX_LOADED_ALL );
    }
    else
    {
            if( pStore->GetError() == ERRCODE_IO_BROKENPACKAGE )
                SetError( ERRCODE_IO_BROKENPACKAGE );
            pStore->SetError( SVSTREAM_WRONGVERSION );
    }

    return bRet;
}

void SdDrawDocShell::HandsOff()
{
    SfxInPlaceObject::HandsOff();

    if( pDoc )
        pDoc->HandsOff();
}

SdDrawDocument* SdDrawDocShell::GetDoc()
{
    return pDoc;
}

SfxStyleSheetBasePool* SdDrawDocShell::GetStyleSheetPool()
{
    return( (SfxStyleSheetBasePool*) pDoc->GetStyleSheetPool() );
}


void SdDrawDocShell::FillClass(SvGlobalName* pClassName,ULONG*  pFormat, String* pAppName, String* pFullTypeName, String* pShortTypeName, long    nFileFormat) const
{
    SfxInPlaceObject::FillClass(pClassName, pFormat, pAppName, pFullTypeName,
                                pShortTypeName, nFileFormat);

    if (nFileFormat == SOFFICE_FILEFORMAT_31)
    {
        *pClassName = SvGlobalName(BF_SO3_SIMPRESS_CLASSID_30);
        *pFormat = SOT_FORMATSTR_ID_STARDRAW;
        *pAppName = String(RTL_CONSTASCII_USTRINGPARAM("Sdraw 3.1"));
        *pFullTypeName = SdResId(STR_IMPRESS_DOCUMENT_FULLTYPE_31).toString();;
        *pShortTypeName = SdResId(STR_IMPRESS_DOCUMENT).toString();
    }
    else if (nFileFormat == SOFFICE_FILEFORMAT_40)
    {
        *pClassName = SvGlobalName(BF_SO3_SIMPRESS_CLASSID_40);
        *pFormat = SOT_FORMATSTR_ID_STARDRAW_40;
        *pFullTypeName = SdResId(STR_IMPRESS_DOCUMENT_FULLTYPE_40).toString();
        *pShortTypeName = SdResId(STR_IMPRESS_DOCUMENT).toString();
    }
    else
    {
        if (nFileFormat == SOFFICE_FILEFORMAT_50)
        {
            if (eDocType == DOCUMENT_TYPE_DRAW)
            {
                *pClassName = SvGlobalName(BF_SO3_SDRAW_CLASSID_50);
                *pFormat = SOT_FORMATSTR_ID_STARDRAW_50;
                *pFullTypeName = SdResId(STR_GRAPHIC_DOCUMENT_FULLTYPE_50).toString();
            }
            else
            {
                *pClassName = SvGlobalName(BF_SO3_SIMPRESS_CLASSID_50);
                *pFormat = SOT_FORMATSTR_ID_STARIMPRESS_50;
                *pFullTypeName = SdResId(STR_IMPRESS_DOCUMENT_FULLTYPE_50).toString();
            }
        }
        else if (nFileFormat == SOFFICE_FILEFORMAT_CURRENT)
        {
            *pFullTypeName = SdResId( (eDocType == DOCUMENT_TYPE_DRAW) ?
                                              STR_GRAPHIC_DOCUMENT_FULLTYPE_60 : STR_IMPRESS_DOCUMENT_FULLTYPE_60 ).toString();

                if(eDocType == DOCUMENT_TYPE_DRAW)
                {
                    *pClassName = SvGlobalName(BF_SO3_SDRAW_CLASSID_60);
                    *pFormat = SOT_FORMATSTR_ID_STARDRAW_60;
                }
                else
                {
                    *pClassName = SvGlobalName(BF_SO3_SIMPRESS_CLASSID_60);
                    *pFormat = SOT_FORMATSTR_ID_STARIMPRESS_60;
                }

        }

        *pShortTypeName = SdResId( (eDocType == DOCUMENT_TYPE_DRAW) ?
                                          STR_GRAPHIC_DOCUMENT : STR_IMPRESS_DOCUMENT ).toString();
    }
}

OutputDevice* SdDrawDocShell::GetDocumentRefDev (void)
{
    OutputDevice* pReferenceDevice = SfxInPlaceObject::GetDocumentRefDev ();
    if (pReferenceDevice == NULL && pDoc != NULL)
        pReferenceDevice = pDoc->GetRefDevice ();
    return pReferenceDevice;
}

SfxPrinter* SdDrawDocShell::CreatePrinter( SvStream& rIn, SdDrawDocument& rDoc )
{
    SfxItemSet* pSet = new SfxItemSet( rDoc.GetPool(),
                    SID_PRINTER_NOTFOUND_WARN,  SID_PRINTER_NOTFOUND_WARN,
                    SID_PRINTER_CHANGESTODOC,   SID_PRINTER_CHANGESTODOC,
                    ATTR_OPTIONS_PRINT,         ATTR_OPTIONS_PRINT,
                    0 );
    // PrintOptionsSet setzen
    SdOptionsPrintItem aPrintItem(ATTR_OPTIONS_PRINT,SD_MOD()->GetSdOptions(rDoc.GetDocumentType()) );

    pSet->Put( aPrintItem );
    pSet->Put( SfxBoolItem( SID_PRINTER_NOTFOUND_WARN, false ) );

    return SfxPrinter::Create(rIn, pSet);
}

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
