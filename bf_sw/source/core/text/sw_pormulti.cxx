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

#include <hintids.hxx>

#include <com/sun/star/i18n/ScriptType.hdl>
#include <bf_svx/twolinesitem.hxx>
#include <bf_svx/charrotateitem.hxx>

#include <charfmt.hxx>
#include <txtinet.hxx>
#include <fchrfmt.hxx>
#include <pormulti.hxx>     // SwMultiPortion
#include <itrform2.hxx>     // SwTxtFormatter

#include <horiornt.hxx>

#include <porfld.hxx>       // SwFldPortion
namespace binfilter {

using namespace ::com::sun::star;
extern sal_Bool IsUnderlineBreak( const SwLinePortion& rPor, const SwFont& rFnt );
extern BYTE WhichFont( xub_StrLen nIdx, const String* pTxt,
                       const SwScriptInfo* pSI );

/*--------------------------------------------------
 * SwTxtFormatter::MakeRestPortion(..)
 * When a fieldportion at the end of line breaks and needs a following
 * fieldportion in the next line, then the "restportion" of the formatinfo
 * has to be set. Normally this happens during the formatting of the first
 * part of the fieldportion.
 * But sometimes the formatting starts at the line with the following part,
 * exspecally when the following part is on the next page.
 * In this case the MakeRestPortion-function has to create the following part.
 * The first parameter is the line that contains possibly a first part
 * of a field. When the function finds such field part, it creates the right
 * restportion. This may be a multiportion, e.g. if the field is surrounded by
 * a doubleline- or ruby-portion.
 * The second parameter is the start index of the line.
 * --------------------------------------------------*/

/*N*/ SwLinePortion* SwTxtFormatter::MakeRestPortion( const SwLineLayout* pLine,
/*N*/   xub_StrLen nPos1 )
/*N*/ {
/*N*/   if( !nPos1 )
/*N*/       return NULL;
/*N*/   xub_StrLen nMultiPos = nPos1 - pLine->GetLen();
/*N*/   const SwMultiPortion *pMulti1 = NULL;
/*N*/   const SwLinePortion* pPor = pLine->GetFirstPortion();
/*N*/   SwFldPortion *pFld = NULL;
/*N*/   while( pPor )
/*N*/   {
/*N*/       if( pPor->GetLen() )
/*N*/       {
/*N*/           if( !pMulti1 )
/*N*/           {
/*N*/               nMultiPos += pPor->GetLen();
/*N*/           }
/*N*/       }
/*N*/       if( pPor->InFldGrp() )
/*N*/       {
/*?*/           pFld = (SwFldPortion*)pPor;
/*N*/       }
/*N*/       else if( pPor->IsMultiPortion() )
/*N*/       {
/*?*/ #ifdef BIDI
/*?*/             OSL_ENSURE( !pMulti1 || pMulti1->IsBidi(),
/*?*/                     "Nested multiportions are forbidden." );
/*?*/ #else
/*?*/           OSL_ENSURE( !pMulti1, "Nested multiportions are forbidden." );
/*?*/ #endif
/*?*/
/*?*/           pFld = NULL;
/*N*/       }
/*N*/       pPor = pPor->GetPortion();
/*N*/   }
/*N*/   if( pFld && !pFld->HasFollow() )
/*N*/       pFld = NULL;
/*N*/
/*N*/   SwLinePortion *pRest = NULL;
/*N*/   if( pFld )
/*N*/   {
/*?*/       const SwTxtAttr *pHint = GetAttr( nPos1 - 1 );
/*?*/       if( pHint && pHint->Which() == RES_TXTATR_FIELD )
/*?*/       {
/*?*/           pRest = NewFldPortion( GetInfo(), pHint );
/*?*/           if( !pRest->InFldGrp() )
/*?*/           {
/*?*/               delete pRest;
/*?*/               pRest = NULL;
/*?*/           }
/*?*/       }
/*N*/   }
/*N*/   if( !pMulti1 )
/*N*/       return pRest;

/*?*/   return pRest;
/*N*/ }

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
