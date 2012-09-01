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
#ifndef _TXTFTN_HXX
#define _TXTFTN_HXX

#include <bf_svtools/bf_solar.h>

#include <txatbase.hxx>
namespace binfilter {

class SwNodeIndex;
class SwTxtNode;
class SwNodes;
class SwDoc;

// ATT_FTN **********************************************************

class SwTxtFtn : public SwTxtAttr
{
    SwNodeIndex *pStartNode;
    SwTxtNode* pMyTxtNd;
    USHORT nSeqNo;

    // Zuweisung und Copy-Ctor sind nicht erlaubt.
    SwTxtFtn& operator=( const SwTxtFtn &rTxtFtn );
    SwTxtFtn( const SwTxtFtn &rTxtFtn );

public:
    SwTxtFtn( const SwFmtFtn& rAttr, xub_StrLen nStart );
    ~SwTxtFtn();

    inline SwNodeIndex *GetStartNode() const { return pStartNode; }
    void SetStartNode( const SwNodeIndex *pNode, BOOL bDelNodes = TRUE );
    void SetNumber( const USHORT nNumber, const String* = 0 );

    // erfrage und setze den TxtNode Pointer
    inline const SwTxtNode& GetTxtNode() const;
    void ChgTxtNode( const SwTxtNode* pNew ) { pMyTxtNd = (SwTxtNode*)pNew; }

        // lege eine neue leere TextSection fuer diese Fussnote an
    void MakeNewTextSection( SwNodes& rNodes );

        // loesche die FtnFrame aus der Seite
    void DelFrms();
        // bedingten Absatzvorlagen checken

        // fuer die Querverweise auf Fussnoten
    USHORT SetSeqRefNo();
    void SetSeqNo( USHORT n )               { nSeqNo = n; } // fuer die Reader
    USHORT GetSeqRefNo() const              { return nSeqNo; }

    static void SetUniqueSeqRefNo( SwDoc& rDoc );
};

inline const SwTxtNode& SwTxtFtn::GetTxtNode() const
{
    OSL_ENSURE( pMyTxtNd, "SwTxtFtn:: wo ist mein TextNode?" );
    return *pMyTxtNd;
}

} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
