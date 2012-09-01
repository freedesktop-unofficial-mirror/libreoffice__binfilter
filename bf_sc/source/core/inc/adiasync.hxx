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

#ifndef _SC_ADIASYNC_HXX
#define _SC_ADIASYNC_HXX

#include <bf_svtools/brdcst.hxx>

#include "callform.hxx"
class String;
namespace binfilter {

extern "C" {
void CALLTYPE ScAddInAsyncCallBack( double& nHandle, void* pData );
}


class ScAddInAsync;
typedef ScAddInAsync* ScAddInAsyncPtr;
SV_DECL_PTRARR_SORT( ScAddInAsyncs, ScAddInAsyncPtr, 4, 4 )
extern ScAddInAsyncs theAddInAsyncTbl;  // in adiasync.cxx

class ScDocument;
typedef ScDocument* ScAddInDocPtr;
SV_DECL_PTRARR_SORT( ScAddInDocs, ScAddInDocPtr, 1, 1 )


class ScAddInAsync : public SfxBroadcaster
{
private:
    union
    {
        double      nVal;               // aktueller Wert
        String*     pStr;
    };
    ScAddInDocs*    pDocs;              // Liste der benutzenden Dokumente
    FuncData*       pFuncData;          // Zeiger auf die Daten in der Collection
    ULONG           nHandle;            // wird von double auf ULONG gecasted
    ParamType       eType;              // PTR_DOUBLE oder PTR_STRING Ergebnis
    BOOL            bValid;             // ob Wert gueltig

public:
                    // cTor nur wenn ScAddInAsync::Get fehlschlaegt!
                    // nIndex: Index aus der FunctionCollection
                    ScAddInAsync( ULONG nHandle, USHORT nIndex,
                                    ScDocument* pDoc );
                    // default-cTor nur fuer das eine globale aSeekObj !!!
                    ScAddInAsync();
    virtual         ~ScAddInAsync();
    static ScAddInAsync*    Get( ULONG nHandle );
    static void     RemoveDocument( ScDocument* pDocument );
    BOOL            IsValid() const         { return bValid; }
    ParamType       GetType() const         { return eType; }
    double          GetValue() const        { return nVal; }
    const String&   GetString() const       { return *pStr; }
    BOOL            HasDocument( ScDocument* pDoc ) const
                        { return pDocs->Seek_Entry( pDoc ); }
    void            AddDocument( ScDocument* pDoc ) { pDocs->Insert( pDoc ); }

    // Vergleichsoperatoren fuer PtrArrSort
    BOOL operator < ( const ScAddInAsync& r ) { return nHandle <  r.nHandle; }
    BOOL operator ==( const ScAddInAsync& r ) { return nHandle == r.nHandle; }
};



} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
