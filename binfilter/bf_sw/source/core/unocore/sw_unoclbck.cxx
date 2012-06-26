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

#include <osl/diagnose.h>

#include <unoidx.hxx>
#include <unoclbck.hxx>

#include <horiornt.hxx>

#include <doc.hxx>
namespace binfilter {

SwUnoCallBack::SwUnoCallBack(SwModify *pToRegisterIn)   :
    SwModify(pToRegisterIn)
{
}

SwUnoCallBack::~SwUnoCallBack()
{
}

SwXReferenceMark* SwUnoCallBack::GetRefMark(const SwFmtRefMark& rMark)
{
    SwClientIter aIter( *this );
    SwXReferenceMark* pxRefMark = (SwXReferenceMark*)aIter.First( TYPE( SwXReferenceMark ));
    while(pxRefMark)
    {
        SwDoc* pDoc = pxRefMark->GetDoc();
        if(pDoc)
        {
            const SwFmtRefMark* pFmt = pDoc->GetRefMark(pxRefMark->GetMarkName());
            if(pFmt == &rMark)
                return pxRefMark;
        }
        pxRefMark = (SwXReferenceMark*)aIter.Next( );
    }
    return 0;
}

SwXFootnote* SwUnoCallBack::GetFootnote(const SwFmtFtn& rMark)
{
    SwClientIter aIter( *this );
    SwXFootnote* pxFootnote = (SwXFootnote*)aIter.First( TYPE( SwXFootnote ));
    while(pxFootnote)
    {
        SwDoc* pDoc = pxFootnote->GetDoc();
        if(pDoc)
        {
            const SwFmtFtn* pFtn = pxFootnote->FindFmt();
            if(pFtn == &rMark)
                return pxFootnote;
        }
        pxFootnote = (SwXFootnote*)aIter.Next( );
    }
    return 0;
}

SwXDocumentIndexMark* SwUnoCallBack::GetTOXMark(const SwTOXMark& rMark)
{
    SwClientIter aIter( *this );
    SwXDocumentIndexMark* pxIndexMark = (SwXDocumentIndexMark*)aIter.First( TYPE( SwXDocumentIndexMark ));
    while(pxIndexMark)
    {
        const SwTOXMark* pMark = pxIndexMark->GetTOXMark();
        if(pMark == &rMark)
            return pxIndexMark;

        pxIndexMark = (SwXDocumentIndexMark*)aIter.Next( );
    }
    return 0;
}

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
