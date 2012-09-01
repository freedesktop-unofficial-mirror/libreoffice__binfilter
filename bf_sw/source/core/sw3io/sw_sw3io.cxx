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
#include <stdio.h>
#define _SVSTDARR_USHORTS
#include <bf_svtools/zforlist.hxx>

#include <horiornt.hxx>

#include "doc.hxx"

#include <osl/diagnose.h>

#include "pam.hxx"
#include "rootfrm.hxx"
#include "swerror.h"
#include "sw3io.hxx"
#include "sw3imp.hxx"
#include "ndgrf.hxx"
namespace binfilter {


/*N*/ Sw3Io::Sw3Io( SwDoc& r )
/*N*/ {
/*N*/   pImp = new Sw3IoImp( *this );
/*N*/   pImp->pDoc = &r;
/*N*/   r.AddLink();
/*N*/ }


/*N*/ Sw3Io::~Sw3Io()
/*N*/ {
/*N*/   delete pImp;
/*N*/ }


/*N*/ ULONG Sw3Io::Load( SvStorage* pStor, SwPaM* pPaM )
/*N*/ {
/*N*/   // Wenn ein PaM angegeben ist, wird eingefuegt!
/*N*/   // Beim Einfuegen werden vorhandene Vorlagen nicht uebergeplaettet
/*N*/   pImp->pOldRoot = pImp->pRoot;
/*N*/   pImp->pRoot = pStor;
/*N*/   BOOL bGood = pImp->OpenStreams( FALSE );
/*N*/   // Wenn die Streams nicht alle da sind, ist es KEIN FEHLER,
/*N*/   // da ein OLE-Container u.U. nicht voll ist.
/*N*/   if( !bGood )
/*N*/   {
/*?*/       pImp->pRoot = pImp->pOldRoot;
/*?*/       pImp->pOldRoot.Clear();
/*?*/       return pImp->nRes;
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       if ( pPaM )
/*N*/       {
/*?*/           pImp->bInsert = TRUE;
/*?*/           pImp->bInsIntoHdrFtr = pImp->pDoc->IsInHeaderFooter(
/*N*/                                                   pPaM->GetPoint()->nNode );
/*N*/       }
/*N*/       else
/*N*/           pImp->bInsert = pImp->bInsIntoHdrFtr = FALSE;
/*N*/
/*N*/       if( pImp->bNormal )                 // nur setzen wenn normal gelesen wird,
/*N*/           pImp->bAdditive = pImp->bInsert;// sonst ist es schon gueltig
/*N*/
/*N*/       pImp->OutputMode( FALSE );
/*N*/       // Man nehme die Doc-Groesse
/*N*/       pImp->pContents->Seek( STREAM_SEEK_TO_END );
/*N*/       ULONG nSize = pImp->pContents->Tell();
/*N*/       pImp->pContents->Seek( 0L );
/*N*/       pImp->OpenPercentBar( 0L, nSize );
/*N*/       if( pImp->bNormal )
/*N*/           pImp->LoadDrawingLayer();
/*N*/       if( ( pImp->bNormal || pImp->bTxtColls || pImp->bCharFmts || pImp->bFrmFmts ) && !pImp->nRes )
/*N*/           pImp->LoadStyleSheets( BOOL( !pImp->bAdditive ) );
/*N*/       if( ( pImp->bNormal || pImp->bNumRules || pImp->bPageDescs ) && !pImp->nRes )
/*N*/           pImp->LoadNumRules();
/*N*/       if( ( pImp->bNormal || pImp->bPageDescs ) && !pImp->nRes )
/*N*/           pImp->LoadPageStyles();
/*N*/       if( pImp->bNormal && !pImp->nRes )
/*N*/           pImp->LoadContents( pPaM );
/*N*/       pImp->ClosePercentBar();
/*N*/
/*N*/       //Benachrichtigungen fuer OLE-Objekte
/*N*/       if ( pImp->bInsert ) //Eingefuege wurden markiert
/*?*/           pImp->pDoc->PrtOLENotify( FALSE );
/*N*/       else if ( pImp->pDoc->IsOLEPrtNotifyPending() ||//Drucker geaendert
/*N*/                 pImp->nVersion < SWG_OLEPRTNOTIFY )   //Ruecksicht auf Math, dass
/*N*/                                                       //sowieso Hautpanwender ist.
/*N*/       {
/*N*/           pImp->pDoc->PrtOLENotify( TRUE );
/*N*/       }
/*N*/
/*N*/       // unbenutzte OLE-Objekte l?schen, falls ein 3.0-Dok
/*N*/       // geladen wird
/*N*/       if( pImp->nVersion<=SWG_SHORTFIELDS &&
/*N*/           pImp->bNormal && !pImp->bBlock && !pImp->bInsert && !pImp->nRes  )
/*N*/           pImp->RemoveUnusedObjects();
/*N*/
/*N*/       if( pImp->nRes )
/*?*/           pImp->nRes |= ERRCODE_CLASS_READ;
/*N*/       else if( pImp->bNoDrawings )
/*?*/           pImp->nRes = WARN_SWG_NO_DRAWINGS;
/*N*/       else if( pImp->nWarn )
/*?*/           pImp->nRes = pImp->nWarn | ERRCODE_CLASS_READ;
/*N*/
/*N*/       pImp->CloseStreams();
/*N*/       if( pPaM || pImp->bBlock )
/*?*/           pImp->pRoot = pImp->pOldRoot, pImp->pOldRoot.Clear();
/*N*/
/*N*/       SvNumberFormatter* pN;
/*N*/       if( pImp->bInsert &&
/*N*/           0 != ( pN = pImp->pDoc->GetNumberFormatter( FALSE ) ))
/*?*/           pN->ClearMergeTable();
/*N*/   }
/*N*/   return pImp->nRes;
/*N*/ }

/*N*/ void Sw3Io::HandsOff()
/*N*/ {
/*N*/   pImp->pRoot.Clear();
/*N*/ }

// Ende eines Save/SaveAs/HandsOff.
// Falls der Storage gewechselt hat, muessen die Streams
// neu geoeffnet werden.

/*N*/ void Sw3Io::SetReadOptions( const SwgReaderOption& rOpt, BOOL bOverwrite )
/*N*/ {
/*N*/   pImp->SetReadOptions( rOpt, bOverwrite );
/*N*/ }

// Erzeugen eines eindeutigen Stream-Namens in einem Storage

/*N*/ String Sw3Io::UniqueName( SvStorage* pStg, const sal_Char* p )
/*N*/ {
/*N*/   String aName;
/*N*/   sal_Char cBuf[ 32 ];
/*N*/
/*N*/   // Man nehme die Adresse von cBuf auf dem Stack als Anfangswert
/*N*/   // aber nur ein einziges mal (bug fix 20976)
/*N*/   static ULONG nId = (ULONG) cBuf;
/*N*/
/*N*/   nId++;
/*N*/   for( ;; )
/*N*/   {
/*N*/       snprintf( cBuf, sizeof(cBuf), "%s%08lX", p, nId );
/*N*/       aName.AssignAscii( cBuf );
/*N*/       if( !pStg->IsContained( aName ) )
/*N*/           break;
/*N*/       nId++;
/*N*/   }
/*N*/   return aName;
/*N*/ }




}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
