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

#define ITEMID_FIELD EE_FEATURE_FIELD
#include <bf_svx/unofored.hxx>

#include "editsrc.hxx"
#include "editutil.hxx"
#include "docsh.hxx"
#include "docfunc.hxx"
#include "hints.hxx"
#include <vcl/svapp.hxx>
#include "AccessibleText.hxx"
namespace binfilter {

//------------------------------------------------------------------------

TYPEINIT1( ScHeaderFooterChangedHint, SfxHint );

ScHeaderFooterChangedHint::ScHeaderFooterChangedHint(USHORT nP) :
    nPart( nP )
{
}

ScHeaderFooterChangedHint::~ScHeaderFooterChangedHint()
{
}

//------------------------------------------------------------------------

ScSharedHeaderFooterEditSource::ScSharedHeaderFooterEditSource( ScHeaderFooterTextData* pData ) :
    pTextData( pData )
{
    //  pTextData is held by the ScHeaderFooterTextObj.
    //  Text range and cursor keep a reference to their parent text, so the text object is
    //  always alive and the TextData is valid as long as there are children.
}

ScSharedHeaderFooterEditSource::~ScSharedHeaderFooterEditSource()
{
}

SvxEditSource* ScSharedHeaderFooterEditSource::Clone() const
{
    return new ScSharedHeaderFooterEditSource( pTextData );
}

SvxTextForwarder* ScSharedHeaderFooterEditSource::GetTextForwarder()
{
    return pTextData->GetTextForwarder();
}

void ScSharedHeaderFooterEditSource::UpdateData()
{
    pTextData->UpdateData();
}

ScEditEngineDefaulter* ScSharedHeaderFooterEditSource::GetEditEngine()
{
    return pTextData->GetEditEngine();
}

//------------------------------------------------------------------------

//  each ScHeaderFooterEditSource object has its own ScHeaderFooterTextData

ScHeaderFooterEditSource::ScHeaderFooterEditSource( ScHeaderFooterContentObj* pContent,
                                                    USHORT nP ) :
    ScSharedHeaderFooterEditSource( new ScHeaderFooterTextData( *pContent, nP ) )
{
}

ScHeaderFooterEditSource::ScHeaderFooterEditSource( ScHeaderFooterContentObj& rContent,
                                                    USHORT nP ) :
    ScSharedHeaderFooterEditSource( new ScHeaderFooterTextData( rContent, nP ) )
{
}

ScHeaderFooterEditSource::~ScHeaderFooterEditSource()
{
    delete GetTextData();   // not accessed in ScSharedHeaderFooterEditSource dtor
}

SvxEditSource* ScHeaderFooterEditSource::Clone() const
{
    const ScHeaderFooterTextData* pData = GetTextData();
    return new ScHeaderFooterEditSource( pData->GetContentObj(), pData->GetPart() );
}

//------------------------------------------------------------------------

ScSharedCellEditSource::ScSharedCellEditSource( ScCellTextData* pData ) :
    pCellTextData( pData )
{
    //  pCellTextData is part of the ScCellTextObj.
    //  Text range and cursor keep a reference to their parent text, so the text object is
    //  always alive and the CellTextData is valid as long as there are children.
}

ScSharedCellEditSource::~ScSharedCellEditSource()
{
}

SvxEditSource* ScSharedCellEditSource::Clone() const
{
    return new ScSharedCellEditSource( pCellTextData );
}

SvxTextForwarder* ScSharedCellEditSource::GetTextForwarder()
{
    return pCellTextData->GetTextForwarder();
}

void ScSharedCellEditSource::UpdateData()
{
    pCellTextData->UpdateData();
}

void ScSharedCellEditSource::SetDoUpdateData(sal_Bool bValue)
{
    pCellTextData->SetDoUpdate(bValue);
}

sal_Bool ScSharedCellEditSource::IsDirty() const
{
    return pCellTextData->IsDirty();
}

ScEditEngineDefaulter* ScSharedCellEditSource::GetEditEngine()
{
    return pCellTextData->GetEditEngine();
}

//------------------------------------------------------------------------

//  each ScCellEditSource object has its own ScCellTextData

ScCellEditSource::ScCellEditSource( ScDocShell* pDocSh, const ScAddress& rP ) :
    ScSharedCellEditSource( new ScCellTextData( pDocSh, rP ) )
{
}

ScCellEditSource::~ScCellEditSource()
{
    delete GetCellTextData();   // not accessed in ScSharedCellEditSource dtor
}

SvxEditSource* ScCellEditSource::Clone() const
{
    const ScCellTextData* pData = GetCellTextData();
    return new ScCellEditSource( pData->GetDocShell(), pData->GetCellPos() );
}

//------------------------------------------------------------------------

ScAnnotationEditSource::ScAnnotationEditSource(ScDocShell* pDocSh, const ScAddress& rP) :
    pDocShell( pDocSh ),
    aCellPos( rP ),
    pEditEngine( NULL ),
    pForwarder( NULL ),
    bDataValid( FALSE )
{
    if (pDocShell)
        pDocShell->GetDocument()->AddUnoObject(*this);
}

ScAnnotationEditSource::~ScAnnotationEditSource()
{
    SolarMutexGuard aGuard;     //  needed for EditEngine dtor

    if (pDocShell)
        pDocShell->GetDocument()->RemoveUnoObject(*this);

    delete pForwarder;
    delete pEditEngine;
}

SvxEditSource* ScAnnotationEditSource::Clone() const
{
    return new ScAnnotationEditSource( pDocShell, aCellPos );
}

SvxTextForwarder* ScAnnotationEditSource::GetTextForwarder()
{
    if (!pEditEngine)
    {
        // Notizen haben keine Felder
        if ( pDocShell )
            pEditEngine = new ScEditEngineDefaulter(
                pDocShell->GetDocument()->GetEnginePool(), FALSE );
        else
        {
            SfxItemPool* pEnginePool = EditEngine::CreatePool();
            pEnginePool->FreezeIdRanges();
            pEditEngine = new ScEditEngineDefaulter( pEnginePool, TRUE );
        }
        pForwarder = new SvxEditEngineForwarder(*pEditEngine);
    }

    if (bDataValid)
        return pForwarder;

    if ( pDocShell )
    {
        ScPostIt aNote;
        ScDocument* pDoc = pDocShell->GetDocument();
        pDoc->GetNote( aCellPos.Col(), aCellPos.Row(), aCellPos.Tab(), aNote );

        pEditEngine->SetText( aNote.GetText() );        // incl. Umbrueche
    }

    bDataValid = TRUE;
    return pForwarder;
}

void ScAnnotationEditSource::UpdateData()
{
    if ( pDocShell && pEditEngine )
    {
        String aNewText = pEditEngine->GetText( LINEEND_LF );   // im SetNoteText passiert convertLineEnd
        ScDocFunc aFunc(*pDocShell);
        aFunc.SetNoteText( aCellPos, aNewText, TRUE );

        // bDataValid wird bei SetDocumentModified zurueckgesetzt
    }
}

void ScAnnotationEditSource::Notify( SfxBroadcaster& /*rBC*/, const SfxHint& rHint )
{
    if ( rHint.ISA( ScUpdateRefHint ) )
    {
        //! Ref-Update
    }
    else if ( rHint.ISA( SfxSimpleHint ) )
    {
        ULONG nId = ((const SfxSimpleHint&)rHint).GetId();
        if ( nId == SFX_HINT_DYING )
        {
            pDocShell = NULL;                       // ungueltig geworden

            DELETEZ( pForwarder );
            DELETEZ( pEditEngine );     // EditEngine uses document's pool
        }
        else if ( nId == SFX_HINT_DATACHANGED )
            bDataValid = FALSE;                     // Text muss neu geholt werden
    }
}


ScSimpleEditSource::ScSimpleEditSource( SvxTextForwarder* pForw ) :
    pForwarder( pForw )
{
    //  The same forwarder (and EditEngine) is shared by all children of the same Text object.
    //  Text range and cursor keep a reference to their parent text, so the text object is
    //  always alive and the forwarder is valid as long as there are children.
}

ScSimpleEditSource::~ScSimpleEditSource()
{
}

SvxEditSource* ScSimpleEditSource::Clone() const
{
    return new ScSimpleEditSource( pForwarder );
}

SvxTextForwarder* ScSimpleEditSource::GetTextForwarder()
{
    return pForwarder;
}

void ScSimpleEditSource::UpdateData()
{
    //  nothing
}


SAL_WNODEPRECATED_DECLARATIONS_PUSH
ScAccessibilityEditSource::ScAccessibilityEditSource( ::std::auto_ptr < ScAccessibleTextData > pAccessibleCellTextData )
    : mpAccessibleTextData(pAccessibleCellTextData)
{
}
SAL_WNODEPRECATED_DECLARATIONS_POP

ScAccessibilityEditSource::~ScAccessibilityEditSource()
{
}

SAL_WNODEPRECATED_DECLARATIONS_PUSH
SvxEditSource* ScAccessibilityEditSource::Clone() const
{
    return new ScAccessibilityEditSource(::std::auto_ptr < ScAccessibleTextData > (mpAccessibleTextData->Clone()));
}
SAL_WNODEPRECATED_DECLARATIONS_POP

SvxTextForwarder* ScAccessibilityEditSource::GetTextForwarder()
{
    return mpAccessibleTextData->GetTextForwarder();
}

SvxViewForwarder* ScAccessibilityEditSource::GetViewForwarder()
{
    return mpAccessibleTextData->GetViewForwarder();
}

SvxEditViewForwarder* ScAccessibilityEditSource::GetEditViewForwarder( sal_Bool bCreate )
{
    return mpAccessibleTextData->GetEditViewForwarder(bCreate);
}

void ScAccessibilityEditSource::UpdateData()
{
    mpAccessibleTextData->UpdateData();
}

SfxBroadcaster& ScAccessibilityEditSource::GetBroadcaster() const
{
    return mpAccessibleTextData->GetBroadcaster();
}

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
