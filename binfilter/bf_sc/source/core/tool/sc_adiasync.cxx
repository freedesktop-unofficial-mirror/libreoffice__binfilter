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

//------------------------------------------------------------------------

#include <bf_sfx2/objsh.hxx>

#include "adiasync.hxx"
#include "document.hxx"
#include "bf_sc.hrc"        // FID_DATACHANGED

#include <osl/thread.h>
namespace binfilter {


//------------------------------------------------------------------------

#ifdef _MSC_VER
#pragma code_seg("SCSTATICS")
#endif

ScAddInAsyncs theAddInAsyncTbl;
static ScAddInAsync aSeekObj;

#ifdef _MSC_VER
#pragma code_seg()
#endif


/*N*/ SV_IMPL_OP_PTRARR_SORT( ScAddInAsyncs, ScAddInAsyncPtr );

/*N*/ SV_IMPL_PTRARR_SORT( ScAddInDocs, ScAddInDocPtr );




/*N*/ ScAddInAsync::ScAddInAsync() :
/*N*/   SfxBroadcaster(),
/*N*/   nHandle( 0 )
/*N*/ { // nur fuer aSeekObj !
/*N*/ }



/*N*/ ScAddInAsync::ScAddInAsync( ULONG nHandleP, USHORT nIndex, ScDocument* pDoc ) :
/*N*/   SfxBroadcaster(),
/*N*/   pStr( NULL ),
/*N*/   nHandle( nHandleP ),
/*N*/   bValid( FALSE )
/*N*/ {
/*N*/   pDocs = new ScAddInDocs( 1, 1 );
/*N*/   pDocs->Insert( pDoc );
/*N*/   pFuncData = (FuncData*)ScGlobal::GetFuncCollection()->At(nIndex);
/*N*/   eType = pFuncData->GetAsyncType();
/*N*/   theAddInAsyncTbl.Insert( this );
/*N*/ }



/*N*/ ScAddInAsync::~ScAddInAsync()
/*N*/ {
/*N*/ }



/*N*/ ScAddInAsync* ScAddInAsync::Get( ULONG nHandleP )
/*N*/ {
/*N*/   USHORT nPos;
/*N*/   ScAddInAsync* pRet = 0;
/*N*/   aSeekObj.nHandle = nHandleP;
/*N*/   if ( theAddInAsyncTbl.Seek_Entry( &aSeekObj, &nPos ) )
/*N*/       pRet = theAddInAsyncTbl[ nPos ];
/*N*/   aSeekObj.nHandle = 0;
/*N*/   return pRet;
/*N*/ }






/*N*/ void ScAddInAsync::RemoveDocument( ScDocument* pDocumentP )
/*N*/ {
/*N*/   USHORT nPos = theAddInAsyncTbl.Count();
/*N*/   if ( nPos )
/*N*/   {
/*?*/       const ScAddInAsync** ppAsync =
/*?*/           (const ScAddInAsync**) theAddInAsyncTbl.GetData() + nPos - 1;
/*?*/       for ( ; nPos-- >0; ppAsync-- )
/*?*/       {   // rueckwaerts wg. Pointer-Aufrueckerei im Array
/*?*/           ScAddInDocs* p = ((ScAddInAsync*)*ppAsync)->pDocs;
/*?*/           USHORT nFoundPos;
/*?*/           if ( p->Seek_Entry( pDocumentP, &nFoundPos ) )
/*?*/           {
/*?*/               p->Remove( nFoundPos );
/*?*/               if ( p->Count() == 0 )
/*?*/               {   // dieses AddIn wird nicht mehr benutzt
/*?*/                   ScAddInAsync* pAsync = (ScAddInAsync*)*ppAsync;
/*?*/                   theAddInAsyncTbl.Remove( nPos );
/*?*/                   delete pAsync;
/*?*/                   ppAsync = (const ScAddInAsync**) theAddInAsyncTbl.GetData()
/*?*/                       + nPos;
/*?*/               }
/*?*/           }
/*?*/       }
/*N*/   }
/*N*/ }



}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
