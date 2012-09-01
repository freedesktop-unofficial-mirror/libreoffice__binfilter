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

#include <vcl/keycodes.hxx>

#include "swafopt.hxx"
namespace binfilter {

/*------------------------------------------------------------------------
 Beschreibung:
------------------------------------------------------------------------*/

/*N*/ SvxSwAutoFmtFlags& SvxSwAutoFmtFlags::operator=( const SvxSwAutoFmtFlags& rAFFlags )
/*N*/ {
/*N*/   bAutoCorrect = rAFFlags.bAutoCorrect;
/*N*/   bReplaceQuote = rAFFlags.bReplaceQuote;
/*N*/   bCptlSttSntnc = rAFFlags.bCptlSttSntnc;
/*N*/   bCptlSttWrd = rAFFlags.bCptlSttWrd;
/*N*/   bChkFontAttr = rAFFlags.bChkFontAttr;
/*N*/
/*N*/   bChgUserColl = rAFFlags.bChgUserColl;
/*N*/   bChgEnumNum = rAFFlags.bChgEnumNum;
/*N*/   bDelEmptyNode = rAFFlags.bDelEmptyNode;
/*N*/   bSetNumRule = rAFFlags.bSetNumRule;
/*N*/   bAFmtByInput = rAFFlags.bAFmtByInput;
/*N*/
/*N*/   bChgFracionSymbol = rAFFlags.bChgFracionSymbol;
/*N*/   bChgOrdinalNumber = rAFFlags.bChgOrdinalNumber;
/*N*/   bChgToEnEmDash = rAFFlags.bChgToEnEmDash;
/*N*/   bChgWeightUnderl = rAFFlags.bChgWeightUnderl;
/*N*/   bSetINetAttr = rAFFlags.bSetINetAttr;
/*N*/   bSetBorder = rAFFlags.bSetBorder;
/*N*/   bCreateTable = rAFFlags.bCreateTable;
/*N*/   bReplaceStyles = rAFFlags.bReplaceStyles;
/*N*/   bAFmtDelSpacesAtSttEnd = rAFFlags.bAFmtDelSpacesAtSttEnd;
/*N*/   bAFmtDelSpacesBetweenLines = rAFFlags.bAFmtDelSpacesBetweenLines;
/*N*/   bAFmtByInpDelSpacesAtSttEnd = rAFFlags.bAFmtByInpDelSpacesAtSttEnd;
/*N*/   bAFmtByInpDelSpacesBetweenLines = rAFFlags.bAFmtByInpDelSpacesBetweenLines;
/*N*/
/*N*/   bDummy = rAFFlags.bDummy;
/*N*/
/*N*/   bDummy5 = rAFFlags.bDummy5;
/*N*/   bDummy6 = rAFFlags.bDummy6;
/*N*/   bDummy7 = rAFFlags.bDummy7;
/*N*/   bDummy8 = rAFFlags.bDummy8;
/*N*/
/*N*/   bWithRedlining = rAFFlags.bWithRedlining;
/*N*/
/*N*/   bRightMargin = rAFFlags.bRightMargin;
/*N*/   nRightMargin = rAFFlags.nRightMargin;
/*N*/
/*N*/   cBullet = rAFFlags.cBullet;
/*N*/   aBulletFont = rAFFlags.aBulletFont;
/*N*/
/*N*/   cByInputBullet = rAFFlags.cByInputBullet;
/*N*/   aByInputBulletFont = rAFFlags.aByInputBulletFont;
/*N*/
/*N*/   bAutoCompleteWords = rAFFlags.bAutoCompleteWords;
/*N*/   bAutoCmpltCollectWords = rAFFlags.bAutoCmpltCollectWords;
/*N*/     bAutoCmpltKeepList = rAFFlags.bAutoCmpltKeepList;
/*N*/   bAutoCmpltEndless = rAFFlags.bAutoCmpltEndless;
/*N*/   bAutoCmpltAppendBlanc = rAFFlags.bAutoCmpltAppendBlanc;
/*N*/   bAutoCmpltShowAsTip = rAFFlags.bAutoCmpltShowAsTip;
/*N*/   pAutoCmpltList = rAFFlags.pAutoCmpltList;
/*N*/   nAutoCmpltExpandKey = rAFFlags.nAutoCmpltExpandKey;
/*N*/
/*N*/   nAutoCmpltWordLen = rAFFlags.nAutoCmpltWordLen;
/*N*/   nAutoCmpltListLen = rAFFlags.nAutoCmpltListLen;
/*N*/
/*N*/   return *this;
/*N*/ }

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
