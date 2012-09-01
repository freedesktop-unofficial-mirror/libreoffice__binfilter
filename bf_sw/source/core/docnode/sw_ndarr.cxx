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

#include <index.hxx>
#include <ndarr.hxx>
namespace binfilter {


void SwNds::Insert(const SwNodePtr &aElement, const SwIndex & aPos)
{
    theArr.Insert((const ElementPtr&) aElement, aPos.GetIndex());
    SwIndexReg::Update(aPos, 1);
}

void SwNds::Insert(const SwNodePtr* pElement, USHORT nLen, const SwIndex & aPos)
{
    theArr.Insert((const ElementPtr*) pElement, nLen, aPos.GetIndex());
    SwIndexReg::Update(aPos, nLen);
}

void SwNds::Remove(const SwIndex & aPos, USHORT nLen)
{
    if(nLen)
    {
        theArr.Remove(aPos.GetIndex(), nLen);
        SwIndexReg::Update(aPos, nLen, TRUE);
    }
}

BOOL SwNds::Move( const SwIndex & rOldPos, const SwIndex & rNewPos )
{
    register USHORT nDelPos = rOldPos.GetIndex(),
                    nInsPos = rNewPos.GetIndex();
    if( nDelPos == nInsPos || nDelPos +1 == nInsPos )
        return FALSE;
    theArr.Move( nDelPos, nInsPos );
    SwIndexReg::MoveIdx( rOldPos, rNewPos );
    return TRUE;
}

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
