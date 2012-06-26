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

#include <paralist.hxx>
#include <outliner.hxx>     // nur wegen Paragraph, muss geaendert werden!
#include <numdef.hxx>
namespace binfilter {

/*N*/ DBG_NAME(Paragraph)

/*N*/ Paragraph::Paragraph( USHORT nDDepth )
/*N*/   : aBulSize( -1, -1)
/*N*/ {
/*N*/   DBG_CTOR( Paragraph, 0 );
/*N*/
/*N*/     DBG_ASSERT( ( nDDepth < SVX_MAX_NUM ) || ( nDDepth == 0xFFFF ), "Paragraph-CTOR: nDepth invalid!" );
/*N*/
/*N*/   nDepth = nDDepth;
/*N*/   nFlags = 0;
/*N*/   bVisible = TRUE;
/*N*/ }


Paragraph::~Paragraph()
{
    DBG_DTOR( Paragraph, 0 );
}

void ParagraphList::Clear( BOOL bDestroyParagraphs )
{
    if ( bDestroyParagraphs )
    {
        for ( ULONG n = GetParagraphCount(); n; )
        {
            Paragraph* pPara = GetParagraph( --n );
            delete pPara;
        }
    }
    aList.clear();
}


/*NBFF*/ Paragraph* ParagraphList::GetParent( Paragraph* pParagraph, USHORT& rRelPos ) const
/*NBFF*/ {
/*NBFF*/    rRelPos = 0;
/*NBFF*/    ULONG n = GetAbsPos( pParagraph );
/*NBFF*/    Paragraph* pPrev = GetParagraph( --n );
/*NBFF*/    while ( pPrev && ( pPrev->GetDepth() >= pParagraph->GetDepth() ) )
/*NBFF*/    {
/*NBFF*/        if ( pPrev->GetDepth() == pParagraph->GetDepth() )
/*NBFF*/            rRelPos++;
/*NBFF*/        pPrev = GetParagraph( --n );
/*NBFF*/    }
/*NBFF*/
/*NBFF*/    return pPrev;
/*NBFF*/ }



}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
