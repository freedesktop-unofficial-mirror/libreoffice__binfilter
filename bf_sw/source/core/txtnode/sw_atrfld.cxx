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

#include <horiornt.hxx>

#include "doc.hxx"          // Update fuer UserFields

#include <fmtfld.hxx>
#include <txtfld.hxx>
#include "reffld.hxx"
#include "ddefld.hxx"
#include "usrfld.hxx"
#include "expfld.hxx"
#include "ndtxt.hxx"        // SwTxtNode
#include "hints.hxx"
namespace binfilter {

/*N*/ TYPEINIT2( SwFmtFld, SfxPoolItem, SwClient )

/****************************************************************************
 *
 *  class SwFmtFld
 *
 ****************************************************************************/

    // Konstruktor fuers Default vom Attribut-Pool
/*N*/ SwFmtFld::SwFmtFld()
/*N*/   : SfxPoolItem( RES_TXTATR_FIELD ),
/*N*/   SwClient( 0 ),
/*N*/   pField( 0 ),
/*N*/   pTxtAttr( 0 )
/*N*/ {
/*N*/ }

/*N*/ SwFmtFld::SwFmtFld( const SwField &rFld )
/*N*/   : SfxPoolItem( RES_TXTATR_FIELD ),
/*N*/   SwClient( rFld.GetTyp() ),
/*N*/   pTxtAttr( 0 )
/*N*/ {
/*N*/   pField = rFld.Copy();
/*N*/ }

/*N*/ SwFmtFld::SwFmtFld( const SwFmtFld& rAttr )
/*N*/   : SfxPoolItem( RES_TXTATR_FIELD ),
/*N*/   SwClient( rAttr.GetFld()->GetTyp() ),
/*N*/   pTxtAttr( 0 )
/*N*/ {
/*N*/   pField = rAttr.GetFld()->Copy();
/*N*/ }

/*N*/ SwFmtFld::~SwFmtFld()
/*N*/ {
/*N*/   SwFieldType* pType = pField ? pField->GetTyp() : 0;
/*N*/
/*N*/   if (pType && pType->Which() == RES_DBFLD)
/*N*/       pType = 0;  // DB-Feldtypen zerstoeren sich selbst
/*N*/
/*N*/   delete pField;
/*N*/
/*N*/   // bei einige FeldTypen muessen wir den FeldTypen noch loeschen
/*N*/   if( pType && pType->IsLastDepend() )
/*N*/   {
/*N*/       BOOL bDel = FALSE;
/*N*/       switch( pType->Which() )
/*N*/       {
/*N*/       case RES_USERFLD:
/*N*/           bDel = ((SwUserFieldType*)pType)->IsDeleted();
/*N*/           break;
/*N*/
/*N*/       case RES_SETEXPFLD:
/*N*/           bDel = ((SwSetExpFieldType*)pType)->IsDeleted();
/*N*/           break;
/*N*/
/*N*/       case RES_DDEFLD:
/*N*/           bDel = ((SwDDEFieldType*)pType)->IsDeleted();
/*N*/           break;
/*N*/       }
/*N*/
/*N*/       if( bDel )
/*N*/       {
/*N*/           // vorm loeschen erstmal austragen
/*?*/           pType->Remove( this );
/*?*/           delete pType;
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ SfxPoolItem* SwFmtFld::Clone( SfxItemPool* ) const
/*N*/ {
/*N*/   return new SwFmtFld( *this );
/*N*/ }

/*N*/ void SwFmtFld::Modify( SfxPoolItem* pOld, SfxPoolItem* pNew )
/*N*/ {
/*N*/   if( !pTxtAttr )
/*N*/       return;
/*N*/
/*N*/   SwTxtNode* pTxtNd = (SwTxtNode*)&pTxtAttr->GetTxtNode();
/*N*/   OSL_ENSURE( pTxtNd, "wo ist denn mein Node?" );
/*N*/   if( pNew )
/*N*/   {
/*N*/       switch( pNew->Which() )
/*N*/       {
/*?*/       case RES_TXTATR_FLDCHG:
/*?*/               // "Farbe hat sich geaendert !"
/*?*/               // this, this fuer "nur Painten"
/*?*/               pTxtNd->Modify( this, this );
/*?*/               return;
/*?*/       case RES_REFMARKFLD_UPDATE:
/*?*/               // GetReferenz-Felder aktualisieren
/*?*/               if( RES_GETREFFLD == GetFld()->GetTyp()->Which() )
/*?*/                   ((SwGetRefField*)GetFld())->UpdateField();
/*?*/               break;
/*N*/       case RES_DOCPOS_UPDATE:
/*N*/               // Je nach DocPos aktualisieren (SwTxtFrm::Modify())
/*N*/               pTxtNd->Modify( pNew, this );
/*N*/               return;
/*N*/
/*N*/       case RES_ATTRSET_CHG:
/*N*/       case RES_FMT_CHG:
/*?*/               pTxtNd->Modify( pOld, pNew );
/*?*/               return;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   switch (GetFld()->GetTyp()->Which())
/*N*/   {
/*?*/       case RES_HIDDENPARAFLD:
/*?*/           if( !pOld || RES_HIDDENPARA_PRINT != pOld->Which() )
/*?*/               break;
/*?*/       case RES_DBSETNUMBERFLD:
/*?*/       case RES_DBNUMSETFLD:
/*?*/       case RES_DBNEXTSETFLD:
/*?*/       case RES_DBNAMEFLD:
/*?*/           pTxtNd->Modify( 0, pNew);
/*?*/           return;
/*N*/   }
/*N*/
/*N*/   pTxtAttr->Expand();
/*N*/ }

/*N*/ BOOL SwFmtFld::GetInfo( SfxPoolItem& rInfo ) const
/*N*/ {
/*N*/   const SwTxtNode* pTxtNd;
/*N*/   if( RES_AUTOFMT_DOCNODE != rInfo.Which() ||
/*N*/       !pTxtAttr || 0 == ( pTxtNd = pTxtAttr->GetpTxtNode() ) ||
/*N*/       &pTxtNd->GetNodes() != ((SwAutoFmtGetDocNode&)rInfo).pNodes )
/*N*/       return TRUE;
/*N*/
/*N*/   ((SwAutoFmtGetDocNode&)rInfo).pCntntNode = pTxtNd;
/*N*/   return FALSE;
/*N*/ }


/*N*/ BOOL SwFmtFld::IsFldInDoc() const
/*N*/ {
/*N*/   const SwTxtNode* pTxtNd;
/*N*/   return pTxtAttr && 0 != ( pTxtNd = pTxtAttr->GetpTxtNode() ) &&
/*N*/           pTxtNd->GetNodes().IsDocNodes();
/*N*/ }


/*************************************************************************
|*
|*                SwTxtFld::SwTxtFld()
|*
|*    Beschreibung      Attribut fuer automatischen Text, Ctor
|*
*************************************************************************/

/*N*/ SwTxtFld::SwTxtFld( const SwFmtFld& rAttr, xub_StrLen nStart2 )
/*N*/   : SwTxtAttr( rAttr, nStart2 ),
/*N*/   aExpand( rAttr.GetFld()->Expand() ),
/*N*/   pMyTxtNd( 0 )
/*N*/ {
/*N*/   ((SwFmtFld&)rAttr).pTxtAttr = this;
/*N*/ }

/*N*/ SwTxtFld::~SwTxtFld( )
/*N*/ {
/*N*/ }

/*************************************************************************
|*
|*                SwTxtFld::Expand()
|*
|*    Beschreibung      exandiert das Feld und tauscht den Text im Node
|*
*************************************************************************/

/*N*/ void SwTxtFld::Expand()
/*N*/ {
/*N*/   // Wenn das expandierte Feld sich nicht veraendert hat, wird returnt
/*N*/   OSL_ENSURE( pMyTxtNd, "wo ist denn mein Node?" );
/*N*/
/*N*/   const SwField* pFld = GetFld().GetFld();
/*N*/   XubString aNewExpand( pFld->Expand() );
/*N*/
/*N*/   if( aNewExpand == aExpand )
/*N*/   {
/*N*/       // Bei Seitennummernfeldern
/*N*/       const USHORT nWhich = pFld->GetTyp()->Which();
/*N*/       if( RES_CHAPTERFLD != nWhich && RES_PAGENUMBERFLD != nWhich &&
/*N*/           RES_REFPAGEGETFLD != nWhich &&
/*N*/           ( RES_GETEXPFLD != nWhich ||
/*N*/               ((SwGetExpField*)pFld)->IsInBodyTxt() ) )
/*N*/       {
/*N*/           // BP: das muesste man noch optimieren!
/*N*/           //JP 12.06.97: stimmt, man sollte auf jedenfall eine Status-
/*N*/           //              aenderung an die Frames posten
/*N*/           if( pMyTxtNd->CalcVisibleFlag() )
/*?*/               pMyTxtNd->Modify( 0, 0 );
/*N*/           return;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   aExpand = aNewExpand;
/*N*/
/*N*/   // 0, this fuer Formatieren
/*N*/   pMyTxtNd->Modify( 0, (SfxPoolItem*)&GetFld() );
/*N*/ }

/*************************************************************************
 *                      SwTxtFld::CopyFld()
 *************************************************************************/



}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
