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

#include "svdoutl.hxx"
#include "svdotext.hxx"
#include <editstat.hxx>
namespace binfilter {


//TYPEINIT1( SdrOutliner, Outliner );

/*************************************************************************
|*
|* Ctor
|*
\************************************************************************/
/*N*/ SdrOutliner::SdrOutliner( SfxItemPool* pItemPool, USHORT nMode ):
/*N*/ Outliner( pItemPool, nMode ),
/*N*/ pTextObj( NULL )
/*N*/ {
/*N*/ }


/*************************************************************************
|*
|* Dtor
|*
\************************************************************************/
/*N*/ SdrOutliner::~SdrOutliner()
/*N*/ {
/*N*/ }

/*N*/ void SdrOutliner::SetTextObj( const SdrTextObj* pObj )
/*N*/ {
/*N*/   if( pObj && pObj != pTextObj )
/*N*/   {
/*N*/       SetUpdateMode(FALSE);
/*N*/       USHORT nLclOutlinerMode = OUTLINERMODE_OUTLINEOBJECT;
/*N*/       if ( !pObj->IsOutlText() )
/*N*/           nLclOutlinerMode = OUTLINERMODE_TEXTOBJECT;
/*N*/       Init( nLclOutlinerMode );
/*N*/
/*N*/       SetGlobalCharStretching(100,100);
/*N*/
/*N*/       ULONG nStat = GetControlWord();
/*N*/       nStat &= ~( EE_CNTRL_STRETCHING | EE_CNTRL_AUTOPAGESIZE );
/*N*/       SetControlWord(nStat);
/*N*/
/*N*/       Size aNullSize;
/*N*/       Size aMaxSize( 100000,100000 );
/*N*/       SetMinAutoPaperSize( aNullSize );
/*N*/       SetMaxAutoPaperSize( aMaxSize );
/*N*/       SetPaperSize( aMaxSize );
/*N*/       ClearPolygon();
/*N*/   }
/*N*/
/*N*/   pTextObj = pObj;
/*N*/ }

/*N*/ void SdrOutliner::SetTextObjNoInit( const SdrTextObj* pObj )
/*N*/ {
/*N*/   pTextObj = pObj;
/*N*/ }

/*N*/ XubString SdrOutliner::CalcFieldValue(const SvxFieldItem& rField, USHORT nPara, USHORT nPos,
/*N*/                                      Color*& rpTxtColor, Color*& rpFldColor)
/*N*/ {
/*N*/   bool bOk = FALSE;
/*N*/   XubString aRet;
/*N*/
/*N*/   if (pTextObj)
/*N*/       bOk = pTextObj->CalcFieldValue(rField, nPara, nPos, FALSE, rpTxtColor, rpFldColor, aRet);
/*N*/
/*N*/   if (!bOk)
/*N*/       aRet = Outliner::CalcFieldValue(rField, nPara, nPos, rpTxtColor, rpFldColor);
/*N*/
/*N*/   return aRet;
/*N*/ }





}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
