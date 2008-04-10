/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: svx_swafopt.cxx,v $
 * $Revision: 1.7 $
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/

#ifdef _MSC_VER
#pragma hdrstop
#endif

#ifndef _SV_KEYCODES_HXX //autogen
#include <vcl/keycodes.hxx>
#endif

#include "swafopt.hxx"
namespace binfilter {

/*------------------------------------------------------------------------
 Beschreibung:
------------------------------------------------------------------------*/

/*N*/ SvxSwAutoFmtFlags::SvxSwAutoFmtFlags()
/*N*/   : aBulletFont( String::CreateFromAscii(
/*N*/                       RTL_CONSTASCII_STRINGPARAM( "StarSymbol" )),
/*N*/                   Size( 0, 14 ) )
/*N*/ {
/*N*/   bReplaceQuote =
/*N*/   bAutoCorrect =
/*N*/   bCptlSttSntnc =
/*N*/   bCptlSttWrd =
/*N*/   bChkFontAttr =
/*N*/   bChgUserColl =
/*N*/   bChgEnumNum =
/*N*/   bChgFracionSymbol =
/*N*/   bChgOrdinalNumber =
/*N*/   bChgToEnEmDash =
/*N*/   bChgWeightUnderl =
/*N*/   bSetINetAttr =
/*N*/   bAFmtDelSpacesAtSttEnd =
/*N*/   bAFmtDelSpacesBetweenLines =
/*N*/   bAFmtByInpDelSpacesAtSttEnd =
/*N*/   bAFmtByInpDelSpacesBetweenLines =
/*N*/   bDummy = TRUE;
/*N*/
/*N*/   bReplaceStyles =
/*N*/   bDelEmptyNode =
/*N*/   bWithRedlining =
/*N*/   bAutoCmpltEndless =
/*N*/   bAutoCmpltAppendBlanc =
/*N*/   bAutoCmpltShowAsTip = FALSE;
/*N*/
/*N*/   bSetBorder =
/*N*/   bCreateTable =
/*N*/   bSetNumRule =
/*N*/   bAFmtByInput =
/*N*/   bRightMargin =
/*N*/   bAutoCompleteWords =
/*N*/     bAutoCmpltCollectWords =
/*N*/     bAutoCmpltKeepList = TRUE;
/*N*/
/*N*/     bDummy5 = bDummy6 = bDummy7 = bDummy8 =
/*N*/        FALSE;
/*N*/
/*N*/   nRightMargin = 50;      // dflt. 50 %
/*N*/   nAutoCmpltExpandKey = KEY_RETURN;
/*N*/
/*N*/   aBulletFont.SetCharSet( RTL_TEXTENCODING_SYMBOL );
/*N*/   aBulletFont.SetFamily( FAMILY_DONTKNOW );
/*N*/   aBulletFont.SetPitch( PITCH_DONTKNOW );
/*N*/   aBulletFont.SetWeight( WEIGHT_DONTKNOW );
/*N*/   aBulletFont.SetTransparent( TRUE );
/*N*/
/*N*/   cBullet = 0x2022;
/*N*/   cByInputBullet = cBullet;
/*N*/   aByInputBulletFont = aBulletFont;
/*N*/
/*N*/   nAutoCmpltWordLen = 10;
/*N*/   nAutoCmpltListLen = 500;
/*N*/   pAutoCmpltList = 0;
/*N*/ }


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
