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


#include "sdiocmpt.hxx"
#include "cusshow.hxx"
#include "sdpage.hxx"
#include "drawdoc.hxx"

#include <bf_tools/list.hxx>
// #90477#
#include <tools/tenccvt.hxx>
namespace binfilter {

using namespace ::com::sun::star;

/*************************************************************************
|*
|* Ctor
|*
\************************************************************************/
/*N*/ SdCustomShow::SdCustomShow(SdDrawDocument* pDrawDoc)
/*N*/   : List(),
/*N*/   pDoc(pDrawDoc)
/*N*/ {
/*N*/ }

/*************************************************************************
|*
|* Copy-Ctor
|*
\************************************************************************/
/*N*/ SdCustomShow::SdCustomShow( const SdCustomShow& rShow )
/*N*/   : List( rShow )
/*N*/ {
/*N*/   aName = rShow.GetName();
/*N*/   pDoc = rShow.GetDoc();
/*N*/ }

/*N*/ SdCustomShow::SdCustomShow(SdDrawDocument* pDrawDoc, ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > xShow )
/*N*/   : List(),
/*N*/   pDoc(pDrawDoc),
/*N*/   mxUnoCustomShow( xShow )
/*N*/ {
/*N*/ }

/*************************************************************************
|*
|* Dtor
|*
\************************************************************************/
/*N*/ SdCustomShow::~SdCustomShow()
/*N*/ {
/*N*/   uno::Reference< uno::XInterface > xShow( mxUnoCustomShow );
/*N*/   uno::Reference< lang::XComponent > xComponent( xShow, uno::UNO_QUERY );
/*N*/   if( xComponent.is() )
/*N*/       xComponent->dispose();
/*N*/ }


/*************************************************************************
|*
|* Inserter fuer SvStream zum Speichern
|*
\************************************************************************/
/*N*/ SvStream& operator << (SvStream& rOut, const SdCustomShow& rCustomShow)
/*N*/ {
/*N*/   // Letzter Parameter ist die aktuelle Versionsnummer des Codes
/*N*/   SdIOCompat aIO(rOut, STREAM_WRITE, 0);
/*N*/
/*N*/   // Name
/*N*/   // #90477# rOut.WriteByteString( rCustomShow.aName, ::GetStoreCharSet( osl_getThreadTextEncoding() ) );
/*N*/   rOut.WriteUniOrByteString(rCustomShow.aName,
/*N*/       GetSOStoreTextEncoding(osl_getThreadTextEncoding()));
/*N*/
/*N*/   // Anzahl Seiten
/*N*/   UINT32 nCount = rCustomShow.Count();
/*N*/   rOut << nCount;
/*N*/
/*N*/   for (UINT32 i = 0; i < nCount; i++)
/*N*/   {
/*N*/       // Seite aus Liste holen
/*N*/       SdPage* pPage = (SdPage*) rCustomShow.GetObject(i);
/*N*/
/*N*/       if (pPage)
/*N*/       {
/*N*/           // SdPage-Seitennummer
/*N*/           UINT16 nPageNum = (pPage->GetPageNum() - 1) / 2;
/*N*/           rOut << nPageNum;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return rOut;
/*N*/ }

/*************************************************************************
|*
|* Extractor fuer SvStream zum Laden
|*
\************************************************************************/
/*N*/ SvStream& operator >> (SvStream& rIn, SdCustomShow& rCustomShow)
/*N*/ {
/*N*/   SdIOCompat aIO(rIn, STREAM_READ);
/*N*/
/*N*/   // Name
/*N*/   // #90477# rIn.ReadByteString( rCustomShow.aName, ::GetStoreCharSet( osl_getThreadTextEncoding() ) );
/*N*/   rCustomShow.aName = rIn.ReadUniOrByteString(
/*N*/       GetSOLoadTextEncoding(osl_getThreadTextEncoding()));
/*N*/
/*N*/   // Anzahl Seiten
/*N*/   UINT32 nCount = 0;
/*N*/   rIn >> nCount;
/*N*/
/*N*/   rCustomShow.Clear();
/*N*/
/*N*/   for (UINT32 i = 0; i < nCount; i++)
/*N*/   {
/*N*/       // Seitennummer
/*N*/       UINT16 nPageNum;
/*N*/       rIn >> nPageNum;
/*N*/
/*N*/       // Seite in Liste einfuegen
/*N*/       SdPage* pPage = (SdPage*) rCustomShow.pDoc->GetSdPage(nPageNum, PK_STANDARD);
/*N*/       rCustomShow.Insert(pPage, LIST_APPEND);
/*N*/   }
/*N*/
/*N*/   return rIn;
/*N*/ }

/*N*/ extern uno::Reference< uno::XInterface > createUnoCustomShow( SdCustomShow* pShow );

/*N*/ uno::Reference< uno::XInterface > SdCustomShow::getUnoCustomShow()
/*N*/ {
/*N*/   // try weak reference first
/*N*/   uno::Reference< uno::XInterface > xShow( mxUnoCustomShow );
/*N*/
/*N*/   if( !xShow.is() )
/*N*/   {
/*N*/       xShow = createUnoCustomShow( this );
/*N*/   }
/*N*/
/*N*/   return xShow;
/*N*/ }
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
