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

#include <doc.hxx>
#include <txttxmrk.hxx>
#include <tox.hxx>
namespace binfilter {

/*N*/ SwTxtTOXMark::SwTxtTOXMark( const SwTOXMark& rAttr,
/*N*/                   xub_StrLen nStart2, xub_StrLen* pEnde )
/*N*/   : SwTxtAttrEnd( rAttr, nStart2, nStart2 ),
/*N*/   pEnd( 0 ),
/*N*/   pMyTxtNd( 0 )
/*N*/ {
/*N*/   ((SwTOXMark&)rAttr).pTxtAttr = this;
/*N*/   if( !rAttr.GetAlternativeText().Len() )
/*N*/   {
/*N*/       nEnd = *pEnde;
/*N*/       pEnd = &nEnd;
/*N*/   }
/*N*/   SetDontMergeAttr( TRUE );
/*N*/   SetDontMoveAttr( TRUE );
/*N*/   SetOverlapAllowedAttr( TRUE );
/*N*/ }

/*N*/ SwTxtTOXMark::~SwTxtTOXMark()
/*N*/ {
/*N*/ }

/*N*/ xub_StrLen* SwTxtTOXMark::GetEnd()
/*N*/ {
/*N*/   return pEnd;
/*N*/ }

/*N*/ void SwTxtTOXMark::CopyTOXMark( SwDoc* pDoc )
/*N*/ {
/*N*/   SwTOXMark& rTOX = (SwTOXMark&)GetTOXMark();
/*N*/   TOXTypes    eType   = rTOX.GetTOXType()->GetType();
/*N*/   USHORT      nCount  = pDoc->GetTOXTypeCount( eType );
/*N*/   const SwTOXType* pType = 0;
/*N*/   const XubString& rNm = rTOX.GetTOXType()->GetTypeName();
/*N*/
/*N*/   // kein entsprechender Verzeichnistyp vorhanden -> anlegen
/*N*/   // sonst verwenden
/*N*/   for(USHORT i=0; i < nCount; ++i)
/*N*/   {
/*N*/       const SwTOXType* pSrcType = pDoc->GetTOXType(eType, i);
/*N*/       if(pSrcType->GetTypeName() == rNm )
/*N*/       {
/*N*/           pType = pSrcType;
/*N*/           break;
/*N*/       }
/*N*/   }
/*N*/   // kein entsprechender Typ vorhanden -> neu erzeugen
/*N*/   //
/*N*/   if(!pType)
/*N*/   {
/*N*/       pDoc->InsertTOXType( SwTOXType( eType, rNm ) );
/*N*/       pType = pDoc->GetTOXType(eType, 0);
/*N*/   }
/*N*/   // Verzeichnistyp umhaengen
/*N*/   //
/*N*/   ((SwTOXType*)pType)->Add( &rTOX );
/*N*/ }
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
