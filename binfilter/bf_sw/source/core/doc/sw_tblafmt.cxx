/*************************************************************************
 *
 *  $RCSfile: sw_tblafmt.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 17:13:21 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/



#pragma hdrstop

#define ITEMID_BOXINFO      SID_ATTR_BORDER_INNER


// auto strip #ifndef _TOOLS_RESID_HXX
// auto strip #include <tools/resid.hxx>
// auto strip #endif
// auto strip #ifndef _STREAM_HXX //autogen
// auto strip #include <tools/stream.hxx>
// auto strip #endif
// auto strip #ifndef _SHL_HXX
// auto strip #include <tools/shl.hxx>
// auto strip #endif
// auto strip #ifndef _SV_SVAPP_HXX
// auto strip #include <vcl/svapp.hxx>
// auto strip #endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif
// auto strip #ifndef _ERRHDL_HXX
// auto strip #include <errhdl.hxx>
// auto strip #endif

// auto strip #ifndef _SFXDOCFILE_HXX
// auto strip #include <bf_sfx2/docfile.hxx>
// auto strip #endif
// auto strip #ifndef SVTOOLS_URIHELPER_HXX
// auto strip #include <svtools/urihelper.hxx>
// auto strip #endif
// auto strip #ifndef _ZFORLIST_HXX //autogen
// auto strip #include <svtools/zforlist.hxx>
// auto strip #endif
#ifndef _ZFORMAT_HXX //autogen
#include <svtools/zformat.hxx>
#endif
// auto strip #ifndef INCLUDED_SVTOOLS_PATHOPTIONS_HXX
// auto strip #include <svtools/pathoptions.hxx>
// auto strip #endif
// auto strip #ifndef _SFXAPP_HXX
// auto strip #include <bf_sfx2/app.hxx>
// auto strip #endif
// auto strip #ifndef _SVX_DIALMGR_HXX
// auto strip #include <bf_svx/dialmgr.hxx>
// auto strip #endif
#ifndef _SVX_DIALOGS_HRC
#include <bf_svx/dialogs.hrc>
#endif

#define READ_OLDVERS        // erstmal noch alte Versionen lesen

// auto strip #ifndef _SWTYPES_HXX
// auto strip #include <swtypes.hxx>
// auto strip #endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
// auto strip #ifndef _POOLFMT_HXX
// auto strip #include <poolfmt.hxx>
// auto strip #endif
#ifndef _TBLAFMT_HXX
#include <tblafmt.hxx>
#endif
#ifndef _CELLATR_HXX
#include <cellatr.hxx>
#endif
// auto strip #ifndef _SWSTYLENAMEMAPPER_HXX
// auto strip #include <SwStyleNameMapper.hxx>
// auto strip #endif
#ifndef _ERRHDL_HXX //autogen
#include <errhdl.hxx>
#endif
namespace binfilter {

// bis SO5PF
const USHORT AUTOFORMAT_ID_X        = 9501;
const USHORT AUTOFORMAT_ID_358      = 9601;
const USHORT AUTOFORMAT_DATA_ID_X   = 9502;

// ab SO5
//! in nachfolgenden Versionen muss der Betrag dieser IDs groesser sein
const USHORT AUTOFORMAT_ID_504      = 9801;
const USHORT AUTOFORMAT_DATA_ID_504 = 9802;

const USHORT AUTOFORMAT_ID_552      = 9901;
const USHORT AUTOFORMAT_DATA_ID_552 = 9902;

// --- from 641 on: CJK and CTL font settings
const USHORT AUTOFORMAT_ID_641      = 10001;
const USHORT AUTOFORMAT_DATA_ID_641 = 10002;

// current version
const USHORT AUTOFORMAT_ID          = AUTOFORMAT_ID_641;
const USHORT AUTOFORMAT_DATA_ID     = AUTOFORMAT_DATA_ID_641;


#ifdef READ_OLDVERS
const USHORT AUTOFORMAT_OLD_ID      = 8201;
const USHORT AUTOFORMAT_OLD_ID1     = 8301;
const USHORT AUTOFORMAT_OLD_DATA_ID = 8202;
#endif


/*N*/ SwBoxAutoFmt* SwTableAutoFmt::pDfltBoxAutoFmt = 0;

#define sAutoTblFmtName "autotbl.fmt"

// SwTable Auto-Format-Tabelle
SV_IMPL_PTRARR( _SwTableAutoFmtTbl, SwTableAutoFmt* )


//  Struct mit Versionsnummern der Items

//STRIP001 struct SwAfVersions
//STRIP001 {
//STRIP001 public:
//STRIP001  USHORT nFontVersion;
//STRIP001  USHORT nFontHeightVersion;
//STRIP001  USHORT nWeightVersion;
//STRIP001  USHORT nPostureVersion;
//STRIP001  USHORT nUnderlineVersion;
//STRIP001  USHORT nCrossedOutVersion;
//STRIP001  USHORT nContourVersion;
//STRIP001  USHORT nShadowedVersion;
//STRIP001  USHORT nColorVersion;
//STRIP001  USHORT nBoxVersion;
//STRIP001  USHORT nBrushVersion;
//STRIP001
//STRIP001  USHORT nAdjustVersion;
//STRIP001
//STRIP001  USHORT nHorJustifyVersion;
//STRIP001  USHORT nVerJustifyVersion;
//STRIP001  USHORT nOrientationVersion;
//STRIP001  USHORT nMarginVersion;
//STRIP001  USHORT nBoolVersion;
//STRIP001  USHORT nInt32Version;
//STRIP001  USHORT nRotateModeVersion;
//STRIP001
//STRIP001  USHORT nNumFmtVersion;
//STRIP001
//STRIP001  SwAfVersions();
//STRIP001  void Load( SvStream& rStream, USHORT nVer );
//STRIP001 };

//STRIP001 SwAfVersions::SwAfVersions() :
//STRIP001  nFontVersion(0),
//STRIP001  nFontHeightVersion(0),
//STRIP001  nWeightVersion(0),
//STRIP001  nPostureVersion(0),
//STRIP001  nUnderlineVersion(0),
//STRIP001  nCrossedOutVersion(0),
//STRIP001  nContourVersion(0),
//STRIP001  nShadowedVersion(0),
//STRIP001  nColorVersion(0),
//STRIP001  nBoxVersion(0),
//STRIP001  nBrushVersion(0),
//STRIP001  nAdjustVersion(0),
//STRIP001  nHorJustifyVersion(0),
//STRIP001  nVerJustifyVersion(0),
//STRIP001  nOrientationVersion(0),
//STRIP001  nMarginVersion(0),
//STRIP001  nBoolVersion(0),
//STRIP001  nInt32Version(0),
//STRIP001  nRotateModeVersion(0),
//STRIP001  nNumFmtVersion(0)
//STRIP001 {
//STRIP001 }

//STRIP001 void SwAfVersions::Load( SvStream& rStream, USHORT nVer )
//STRIP001 {
//STRIP001  rStream >> nFontVersion;
//STRIP001  rStream >> nFontHeightVersion;
//STRIP001  rStream >> nWeightVersion;
//STRIP001  rStream >> nPostureVersion;
//STRIP001  rStream >> nUnderlineVersion;
//STRIP001  rStream >> nCrossedOutVersion;
//STRIP001  rStream >> nContourVersion;
//STRIP001  rStream >> nShadowedVersion;
//STRIP001  rStream >> nColorVersion;
//STRIP001  rStream >> nBoxVersion;
//STRIP001  rStream >> nBrushVersion;
//STRIP001  rStream >> nAdjustVersion;
//STRIP001  rStream >> nHorJustifyVersion;
//STRIP001  rStream >> nVerJustifyVersion;
//STRIP001  rStream >> nOrientationVersion;
//STRIP001  rStream >> nMarginVersion;
//STRIP001  rStream >> nBoolVersion;
//STRIP001  if ( nVer >= AUTOFORMAT_ID_504 )
//STRIP001  {
//STRIP001      rStream >> nInt32Version;
//STRIP001      rStream >> nRotateModeVersion;
//STRIP001  }
//STRIP001  rStream >> nNumFmtVersion;
//STRIP001 }

//  ---------------------------------------------------------------------------

/*?*/SwBoxAutoFmt::SwBoxAutoFmt()
/*?*/   : aFont( *(SvxFontItem*)GetDfltAttr( RES_CHRATR_FONT ) ),
/*?*/    aCJKFont( *(SvxFontItem*)GetDfltAttr( RES_CHRATR_CJK_FONT ) ),
/*?*/    aCJKHeight( 240, 100, RES_CHRATR_CJK_FONTSIZE ),
/*?*/    aCJKWeight( WEIGHT_NORMAL, RES_CHRATR_CJK_WEIGHT ),
/*?*/    aCJKPosture( ITALIC_NONE, RES_CHRATR_CJK_POSTURE ),
/*?*/    aCTLFont( *(SvxFontItem*)GetDfltAttr( RES_CHRATR_CTL_FONT ) ),
/*?*/    aCTLHeight( 240, 100, RES_CHRATR_CTL_FONTSIZE ),
/*?*/    aCTLWeight( WEIGHT_NORMAL, RES_CHRATR_CTL_WEIGHT ),
/*?*/    aCTLPosture( ITALIC_NONE, RES_CHRATR_CTL_POSTURE ),
/*?*/   aRotateMode( SVX_ROTATE_MODE_STANDARD, 0 )
/*?*/{
/*?*/   eSysLanguage = eNumFmtLanguage = ::binfilter::GetAppLanguage();
/*?*/   aBox.SetDistance( 55 );
/*?*/}


/*?*/SwBoxAutoFmt::SwBoxAutoFmt( const SwBoxAutoFmt& rNew )
/*?*/   : aFont( rNew.aFont ),
/*?*/   aHeight( rNew.aHeight ),
/*?*/   aWeight( rNew.aWeight ),
/*?*/   aPosture( rNew.aPosture ),
/*?*/    aCJKFont( rNew.aCJKFont ),
/*?*/    aCJKHeight( rNew.aCJKHeight ),
/*?*/    aCJKWeight( rNew.aCJKWeight ),
/*?*/    aCJKPosture( rNew.aCJKPosture ),
/*?*/    aCTLFont( rNew.aCTLFont ),
/*?*/    aCTLHeight( rNew.aCTLHeight ),
/*?*/    aCTLWeight( rNew.aCTLWeight ),
/*?*/    aCTLPosture( rNew.aCTLPosture ),
/*?*/   aUnderline( rNew.aUnderline ),
/*?*/   aCrossedOut( rNew.aCrossedOut ),
/*?*/   aContour( rNew.aContour ),
/*?*/   aShadowed( rNew.aShadowed ),
/*?*/   aColor( rNew.aColor ),
/*?*/   aAdjust( rNew.aAdjust ),
/*?*/   aBox( rNew.aBox ),
/*?*/   aBackground( rNew.aBackground ),
/*?*/   aHorJustify( rNew.aHorJustify ),
/*?*/   aVerJustify( rNew.aVerJustify ),
/*?*/   aOrientation( rNew.aOrientation ),
/*?*/   aMargin( rNew.aMargin ),
/*?*/   aLinebreak( rNew.aLinebreak ),
/*?*/   aRotateAngle( rNew.aRotateAngle ),
/*?*/   aRotateMode( rNew.aRotateMode ),
/*?*/   sNumFmtString( rNew.sNumFmtString ),
/*?*/   eSysLanguage( rNew.eSysLanguage ),
/*?*/   eNumFmtLanguage( rNew.eNumFmtLanguage )
/*?*/{
/*?*/}


/*?*/SwBoxAutoFmt::~SwBoxAutoFmt()
/*?*/{
/*?*/}

#if USED

/*?*/int SwBoxAutoFmt::operator==( const SwBoxAutoFmt& rCmp ) const
/*?*/{
DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001  return  aFont == rCmp.aFont &&
//STRIP001          aHeight == rCmp.aHeight &&
//STRIP001          aWeight == rCmp.aWeight &&
//STRIP001          aPosture == rCmp.aPosture &&
//STRIP001             aCJKFont == rCmp.aCJKFont &&
//STRIP001             aCJKHeight == rCmp.aCJKHeight &&
//STRIP001             aCJKWeight == rCmp.aCJKWeight &&
//STRIP001             aCJKPosture == rCmp.aCJKPosture &&
//STRIP001             aCTLFont == rCmp.aCTLFont &&
//STRIP001             aCTLHeight == rCmp.aCTLHeight &&
//STRIP001             aCTLWeight == rCmp.aCTLWeight &&
//STRIP001             aCTLPosture == rCmp.aCTLPosture &&
//STRIP001          aUnderline == rCmp.aUnderline &&
//STRIP001          aCrossedOut == rCmp.aCrossedOut &&
//STRIP001          aContour == rCmp.aContour &&
//STRIP001          aShadowed == rCmp.aShadowed &&
//STRIP001          aColor == rCmp.aColor &&
//STRIP001          aAdjust == rCmp.aAdjust &&
//STRIP001          aBox == rCmp.aBox &&
//STRIP001          aBackground == rCmp.aBackground;
/*N*/ }
#endif


/*?*/SwBoxAutoFmt& SwBoxAutoFmt::operator=( const SwBoxAutoFmt& rNew )
/*?*/{
/*?*/   aFont = rNew.aFont;
/*?*/   aHeight = rNew.aHeight;
/*?*/   aWeight = rNew.aWeight;
/*?*/   aPosture = rNew.aPosture;
/*?*/    aCJKFont = rNew.aCJKFont;
/*?*/    aCJKHeight = rNew.aCJKHeight;
/*?*/    aCJKWeight = rNew.aCJKWeight;
/*?*/    aCJKPosture = rNew.aCJKPosture;
/*?*/    aCTLFont = rNew.aCTLFont;
/*?*/    aCTLHeight = rNew.aCTLHeight;
/*?*/    aCTLWeight = rNew.aCTLWeight;
/*?*/    aCTLPosture = rNew.aCTLPosture;
/*?*/   aUnderline = rNew.aUnderline;
/*?*/   aCrossedOut = rNew.aCrossedOut;
/*?*/   aContour = rNew.aContour;
/*?*/   aShadowed = rNew.aShadowed;
/*?*/   aColor = rNew.aColor;
/*?*/   SetAdjust( rNew.aAdjust );
/*?*/   aBox = rNew.aBox;
/*?*/   aBackground = rNew.aBackground;
/*?*/
/*?*/   aHorJustify = rNew.aHorJustify;
/*?*/   aVerJustify = rNew.aVerJustify;
/*?*/   aOrientation = rNew.aOrientation;
/*?*/   aMargin = rNew.aMargin;
/*?*/   aLinebreak.SetValue( rNew.aLinebreak.GetValue() );
/*?*/   aRotateAngle.SetValue( rNew.aRotateAngle.GetValue() );
/*?*/   aRotateMode.SetValue( rNew.aRotateMode.GetValue() );
/*?*/
/*?*/   sNumFmtString = rNew.sNumFmtString;
/*?*/   eSysLanguage = rNew.eSysLanguage;
/*?*/   eNumFmtLanguage = rNew.eNumFmtLanguage;
/*?*/
/*?*/   return *this;
/*?*/}


/*?*/#define READ( aItem, aItemType, nVers )\
/*?*/   pNew = aItem.Create(rStream, nVers ); \
/*?*/   aItem = *(aItemType*)pNew; \
/*?*/   delete pNew;

/*?*/BOOL SwBoxAutoFmt::Load( SvStream& rStream, const SwAfVersions& rVersions, USHORT nVer )
/*?*/{
DBG_BF_ASSERT(0, "STRIP");return FALSE; //STRIP001  SfxPoolItem* pNew;
//STRIP001  READ( aFont,        SvxFontItem         , rVersions.nFontVersion)
//STRIP001
//STRIP001  if( rStream.GetStreamCharSet() == aFont.GetCharSet() )
//STRIP001      aFont.GetCharSet() = ::gsl_getSystemTextEncoding();
//STRIP001
//STRIP001  READ( aHeight,      SvxFontHeightItem   , rVersions.nFontHeightVersion)
//STRIP001  READ( aWeight,      SvxWeightItem       , rVersions.nWeightVersion)
//STRIP001  READ( aPosture,     SvxPostureItem      , rVersions.nPostureVersion)
//STRIP001     // --- from 641 on: CJK and CTL font settings
//STRIP001     if( AUTOFORMAT_DATA_ID_641 <= nVer )
//STRIP001     {
//STRIP001         READ( aCJKFont,        SvxFontItem         , rVersions.nFontVersion)
//STRIP001         READ( aCJKHeight,      SvxFontHeightItem   , rVersions.nFontHeightVersion)
//STRIP001         READ( aCJKWeight,      SvxWeightItem       , rVersions.nWeightVersion)
//STRIP001         READ( aCJKPosture,     SvxPostureItem      , rVersions.nPostureVersion)
//STRIP001         READ( aCTLFont,        SvxFontItem         , rVersions.nFontVersion)
//STRIP001         READ( aCTLHeight,      SvxFontHeightItem   , rVersions.nFontHeightVersion)
//STRIP001         READ( aCTLWeight,      SvxWeightItem       , rVersions.nWeightVersion)
//STRIP001         READ( aCTLPosture,     SvxPostureItem      , rVersions.nPostureVersion)
//STRIP001     }
//STRIP001  READ( aUnderline,   SvxUnderlineItem    , rVersions.nUnderlineVersion)
//STRIP001  READ( aCrossedOut,  SvxCrossedOutItem   , rVersions.nCrossedOutVersion)
//STRIP001  READ( aContour,     SvxContourItem      , rVersions.nContourVersion)
//STRIP001  READ( aShadowed,    SvxShadowedItem     , rVersions.nShadowedVersion)
//STRIP001  READ( aColor,       SvxColorItem        , rVersions.nColorVersion)
//STRIP001
//STRIP001  READ( aBox,         SvxBoxItem          , rVersions.nBoxVersion)
//STRIP001  READ( aBackground,  SvxBrushItem        , rVersions.nBrushVersion)
//STRIP001
//STRIP001  pNew = aAdjust.Create(rStream, rVersions.nAdjustVersion );
//STRIP001  SetAdjust( *(SvxAdjustItem*)pNew );
//STRIP001  delete pNew;
//STRIP001
//STRIP001  READ( aHorJustify,  SvxHorJustifyItem   , rVersions.nHorJustifyVersion)
//STRIP001  READ( aVerJustify,  SvxVerJustifyItem   , rVersions.nVerJustifyVersion)
//STRIP001  READ( aOrientation, SvxOrientationItem  , rVersions.nOrientationVersion)
//STRIP001  READ( aMargin,      SvxMarginItem       , rVersions.nMarginVersion)
//STRIP001
//STRIP001  pNew = aLinebreak.Create(rStream, rVersions.nBoolVersion );
//STRIP001  aLinebreak.SetValue( ((SfxBoolItem*)pNew)->GetValue() );
//STRIP001  delete pNew;
//STRIP001
//STRIP001  if ( nVer >= AUTOFORMAT_DATA_ID_504 )
//STRIP001  {
//STRIP001      pNew = aRotateAngle.Create( rStream, rVersions.nInt32Version );
//STRIP001      aRotateAngle.SetValue( ((SfxInt32Item*)pNew)->GetValue() );
//STRIP001      delete pNew;
//STRIP001      pNew = aRotateMode.Create( rStream, rVersions.nRotateModeVersion );
//STRIP001      aRotateMode.SetValue( ((SvxRotateModeItem*)pNew)->GetValue() );
//STRIP001      delete pNew;
//STRIP001  }
//STRIP001
//STRIP001  if( 0 == rVersions.nNumFmtVersion )
//STRIP001  {
//STRIP001      USHORT eSys, eLge;
//STRIP001      rStream.ReadByteString( sNumFmtString, rStream.GetStreamCharSet() )
//STRIP001              >> eSys >> eLge;
//STRIP001      eSysLanguage = (LanguageType) eSys;
//STRIP001      eNumFmtLanguage = (LanguageType) eLge;
//STRIP001      if ( eSysLanguage == LANGUAGE_SYSTEM )      // von alten Versionen (Calc)
//STRIP001          eSysLanguage = ::GetAppLanguage();
//STRIP001  }
//STRIP001
//STRIP001  return 0 == rStream.GetError();
/*N*/ }

#ifdef READ_OLDVERS

/*?*/BOOL SwBoxAutoFmt::LoadOld( SvStream& rStream, USHORT aLoadVer[] )
/*?*/{
/*?*/   DBG_BF_ASSERT(0, "STRIP"); return FALSE; //STRIP001 SfxPoolItem* pNew;
//STRIP001  READ( aFont,        SvxFontItem         , 0)
//STRIP001
//STRIP001  if( rStream.GetStreamCharSet() == aFont.GetCharSet() )
//STRIP001      aFont.GetCharSet() = ::gsl_getSystemTextEncoding();
//STRIP001
//STRIP001  READ( aHeight,      SvxFontHeightItem   , 1)
//STRIP001  READ( aWeight,      SvxWeightItem       , 2)
//STRIP001  READ( aPosture,     SvxPostureItem      , 3)
//STRIP001  READ( aUnderline,   SvxUnderlineItem    , 4)
//STRIP001  READ( aCrossedOut,  SvxCrossedOutItem   , 5)
//STRIP001  READ( aContour,     SvxContourItem      , 6)
//STRIP001  READ( aShadowed,    SvxShadowedItem     , 7)
//STRIP001  READ( aColor,       SvxColorItem        , 8)
//STRIP001
//STRIP001  pNew = aAdjust.Create(rStream, aLoadVer[ 9 ] );
//STRIP001  SetAdjust( *(SvxAdjustItem*)pNew );
//STRIP001  delete pNew;
//STRIP001
//STRIP001  READ( aBox,         SvxBoxItem          , 10)
//STRIP001  READ( aBackground,  SvxBrushItem        , 11)
//STRIP001
//STRIP001  return 0 == rStream.GetError();
/*N*/ }

#endif


/*?*/BOOL SwBoxAutoFmt::Save( SvStream& rStream ) const
/*?*/{
/*?*/DBG_BF_ASSERT(0, "STRIP");return FALSE;//STRIP001  aFont.Store( rStream, aFont.GetVersion(SOFFICE_FILEFORMAT_40)  );
//STRIP001  aHeight.Store( rStream, aHeight.GetVersion(SOFFICE_FILEFORMAT_40) );
//STRIP001  aWeight.Store( rStream, aWeight.GetVersion(SOFFICE_FILEFORMAT_40) );
//STRIP001  aPosture.Store( rStream, aPosture.GetVersion(SOFFICE_FILEFORMAT_40) );
//STRIP001     aCJKFont.Store( rStream, aCJKFont.GetVersion(SOFFICE_FILEFORMAT_40)  );
//STRIP001     aCJKHeight.Store( rStream, aCJKHeight.GetVersion(SOFFICE_FILEFORMAT_40) );
//STRIP001     aCJKWeight.Store( rStream, aCJKWeight.GetVersion(SOFFICE_FILEFORMAT_40) );
//STRIP001     aCJKPosture.Store( rStream, aCJKPosture.GetVersion(SOFFICE_FILEFORMAT_40) );
//STRIP001     aCTLFont.Store( rStream, aCTLFont.GetVersion(SOFFICE_FILEFORMAT_40)  );
//STRIP001     aCTLHeight.Store( rStream, aCTLHeight.GetVersion(SOFFICE_FILEFORMAT_40) );
//STRIP001     aCTLWeight.Store( rStream, aCTLWeight.GetVersion(SOFFICE_FILEFORMAT_40) );
//STRIP001     aCTLPosture.Store( rStream, aCTLPosture.GetVersion(SOFFICE_FILEFORMAT_40) );
//STRIP001  aUnderline.Store( rStream, aUnderline.GetVersion(SOFFICE_FILEFORMAT_40) );
//STRIP001  aCrossedOut.Store( rStream, aCrossedOut.GetVersion(SOFFICE_FILEFORMAT_40) );
//STRIP001  aContour.Store( rStream, aContour.GetVersion(SOFFICE_FILEFORMAT_40) );
//STRIP001  aShadowed.Store( rStream, aShadowed.GetVersion(SOFFICE_FILEFORMAT_40) );
//STRIP001  aColor.Store( rStream, aColor.GetVersion(SOFFICE_FILEFORMAT_40) );
//STRIP001  aBox.Store( rStream, aBox.GetVersion(SOFFICE_FILEFORMAT_40) );
//STRIP001  aBackground.Store( rStream, aBackground.GetVersion(SOFFICE_FILEFORMAT_40) );
//STRIP001
//STRIP001  aAdjust.Store( rStream, aAdjust.GetVersion(SOFFICE_FILEFORMAT_40) );
//STRIP001
//STRIP001  aHorJustify.Store( rStream, aHorJustify.GetVersion(SOFFICE_FILEFORMAT_40) );
//STRIP001  aVerJustify.Store( rStream, aVerJustify.GetVersion(SOFFICE_FILEFORMAT_40) );
//STRIP001  aOrientation.Store( rStream, aOrientation.GetVersion(SOFFICE_FILEFORMAT_40) );
//STRIP001  aMargin.Store( rStream, aMargin.GetVersion(SOFFICE_FILEFORMAT_40) );
//STRIP001  aLinebreak.Store( rStream, aLinebreak.GetVersion(SOFFICE_FILEFORMAT_40) );
//STRIP001  // Calc Rotation ab SO5
//STRIP001  aRotateAngle.Store( rStream, aRotateAngle.GetVersion(SOFFICE_FILEFORMAT_40) );
//STRIP001  aRotateMode.Store( rStream, aRotateMode.GetVersion(SOFFICE_FILEFORMAT_40) );
//STRIP001
//STRIP001  rStream.WriteByteString( sNumFmtString, rStream.GetStreamCharSet() )
//STRIP001      << (USHORT)eSysLanguage << (USHORT)eNumFmtLanguage;
//STRIP001
//STRIP001  return 0 == rStream.GetError();
/*N*/ }


/*?*/BOOL SwBoxAutoFmt::SaveVerionNo( SvStream& rStream ) const
/*?*/{
DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001      rStream << aFont.GetVersion( SOFFICE_FILEFORMAT_40 );
//STRIP001  rStream << aHeight.GetVersion( SOFFICE_FILEFORMAT_40 );
//STRIP001  rStream << aWeight.GetVersion( SOFFICE_FILEFORMAT_40 );
//STRIP001  rStream << aPosture.GetVersion( SOFFICE_FILEFORMAT_40 );
//STRIP001  rStream << aUnderline.GetVersion( SOFFICE_FILEFORMAT_40 );
//STRIP001  rStream << aCrossedOut.GetVersion( SOFFICE_FILEFORMAT_40 );
//STRIP001  rStream << aContour.GetVersion( SOFFICE_FILEFORMAT_40 );
//STRIP001  rStream << aShadowed.GetVersion( SOFFICE_FILEFORMAT_40 );
//STRIP001  rStream << aColor.GetVersion( SOFFICE_FILEFORMAT_40 );
//STRIP001  rStream << aBox.GetVersion( SOFFICE_FILEFORMAT_40 );
//STRIP001  rStream << aBackground.GetVersion( SOFFICE_FILEFORMAT_40 );
//STRIP001
//STRIP001  rStream << aAdjust.GetVersion( SOFFICE_FILEFORMAT_40 );
//STRIP001
//STRIP001  rStream << aHorJustify.GetVersion( SOFFICE_FILEFORMAT_40 );
//STRIP001  rStream << aVerJustify.GetVersion( SOFFICE_FILEFORMAT_40 );
//STRIP001  rStream << aOrientation.GetVersion( SOFFICE_FILEFORMAT_40 );
//STRIP001  rStream << aMargin.GetVersion( SOFFICE_FILEFORMAT_40 );
//STRIP001  rStream << aLinebreak.GetVersion( SOFFICE_FILEFORMAT_40 );
//STRIP001  rStream << aRotateAngle.GetVersion( SOFFICE_FILEFORMAT_40 );
//STRIP001  rStream << aRotateMode.GetVersion( SOFFICE_FILEFORMAT_40 );
//STRIP001
//STRIP001  rStream << (USHORT)0;       // NumberFormat
//STRIP001
//STRIP001  return 0 == rStream.GetError();
/*N*/ }

/*  */


/*?*/SwTableAutoFmt::SwTableAutoFmt( const String& rName )
/*?*/   : aName( rName ), nStrResId( USHRT_MAX )
/*?*/{
/*?*/   bInclFont = TRUE;
/*?*/   bInclJustify = TRUE;
/*?*/   bInclFrame = TRUE;
/*?*/   bInclBackground = TRUE;
/*?*/   bInclValueFormat = TRUE;
/*?*/   bInclWidthHeight = TRUE;
/*?*/
/*?*/   memset( aBoxAutoFmt, 0, sizeof( aBoxAutoFmt ) );
/*?*/}


/*?*/SwTableAutoFmt::SwTableAutoFmt( const SwTableAutoFmt& rNew )
/*?*/{
/*?*/   for( BYTE n = 0; n < 16; ++n )
/*?*/       aBoxAutoFmt[ n ] = 0;
/*?*/   *this = rNew;
/*?*/}

/*N*/SwTableAutoFmt& SwTableAutoFmt::operator=( const SwTableAutoFmt& rNew )
/*N*/{
/*?*/   for( BYTE n = 0; n < 16; ++n )
/*?*/   {
/*?*/       if( aBoxAutoFmt[ n ] )
/*?*/           delete aBoxAutoFmt[ n ];
/*?*/
/*?*/       SwBoxAutoFmt* pFmt = rNew.aBoxAutoFmt[ n ];
/*?*/       if( pFmt )      // ist gesetzt -> kopieren
/*?*/           aBoxAutoFmt[ n ] = new SwBoxAutoFmt( *pFmt );
/*?*/       else            // sonst default
/*?*/           aBoxAutoFmt[ n ] = 0;
/*?*/   }
/*?*/
/*?*/   aName = rNew.aName;
/*?*/   nStrResId = rNew.nStrResId;
/*?*/   bInclFont = rNew.bInclFont;
/*?*/   bInclJustify = rNew.bInclJustify;
/*?*/   bInclFrame = rNew.bInclFrame;
/*?*/   bInclBackground = rNew.bInclBackground;
/*?*/   bInclValueFormat = rNew.bInclValueFormat;
/*?*/   bInclWidthHeight = rNew.bInclWidthHeight;
/*?*/
/*?*/   return *this;
/*?*/}


/*?*/SwTableAutoFmt::~SwTableAutoFmt()
/*?*/{
/*?*/   SwBoxAutoFmt** ppFmt = aBoxAutoFmt;
/*?*/   for( BYTE n = 0; n < 16; ++n, ++ppFmt )
/*?*/       if( *ppFmt )
/*?*/           delete *ppFmt;
/*?*/}


/*N*/void SwTableAutoFmt::SetBoxFmt( const SwBoxAutoFmt& rNew, BYTE nPos )
/*N*/{
/*?*/   DBG_BF_ASSERT(0, "STRIP"); //STRIP001 ASSERT( 0 <= nPos && nPos < 16, "falscher Bereich" );
//STRIP001 /*?*/
//STRIP001 /*?*/    SwBoxAutoFmt* pFmt = aBoxAutoFmt[ nPos ];
//STRIP001 /*?*/    if( pFmt )      // ist gesetzt -> kopieren
//STRIP001 /*?*/        *aBoxAutoFmt[ nPos ] = rNew;
//STRIP001 /*?*/    else            // sonst neu setzen
//STRIP001 /*?*/        aBoxAutoFmt[ nPos ] = new SwBoxAutoFmt( rNew );
/*N*/}


/*?*/const SwBoxAutoFmt& SwTableAutoFmt::GetBoxFmt( BYTE nPos ) const
/*?*/{
/*?*/   ASSERT( 0 <= nPos && nPos < 16, "falscher Bereich" );
/*?*/
/*?*/   SwBoxAutoFmt* pFmt = aBoxAutoFmt[ nPos ];
/*?*/   if( pFmt )      // ist gesetzt -> kopieren
/*?*/       return *pFmt;
/*?*/   else            // sonst den default returnen
/*?*/   {
/*?*/       // falls noch nicht vorhanden:
/*?*/       if( !pDfltBoxAutoFmt )
/*?*/           pDfltBoxAutoFmt = new SwBoxAutoFmt;
/*?*/       return *pDfltBoxAutoFmt;
/*?*/   }
/*?*/}



/*?*/SwBoxAutoFmt& SwTableAutoFmt::UpdateFromSet( BYTE nPos,
/*?*/                                           const SfxItemSet& rSet,
/*?*/                                           UpdateFlags eFlags,
/*?*/                                           SvNumberFormatter* pNFmtr )
/*?*/{
/*?*/   ASSERT( 0 <= nPos && nPos < 16, "falscher Bereich" );
/*?*/
/*?*/   SwBoxAutoFmt* pFmt = aBoxAutoFmt[ nPos ];
/*?*/   if( !pFmt )     // ist gesetzt -> kopieren
/*?*/   {
/*?*/       pFmt = new SwBoxAutoFmt;
/*?*/       aBoxAutoFmt[ nPos ] = pFmt;
/*?*/   }
/*?*/
/*?*/   if( UPDATE_CHAR & eFlags )
/*?*/   {
/*?*/       pFmt->SetFont( (SvxFontItem&)rSet.Get( RES_CHRATR_FONT ) );
/*?*/       pFmt->SetHeight( (SvxFontHeightItem&)rSet.Get( RES_CHRATR_FONTSIZE ) );
/*?*/       pFmt->SetWeight( (SvxWeightItem&)rSet.Get( RES_CHRATR_WEIGHT ) );
/*?*/       pFmt->SetPosture( (SvxPostureItem&)rSet.Get( RES_CHRATR_POSTURE ) );
/*?*/        pFmt->SetCJKFont( (SvxFontItem&)rSet.Get( RES_CHRATR_CJK_FONT ) );
/*?*/        pFmt->SetCJKHeight( (SvxFontHeightItem&)rSet.Get( RES_CHRATR_CJK_FONTSIZE ) );
/*?*/        pFmt->SetCJKWeight( (SvxWeightItem&)rSet.Get( RES_CHRATR_CJK_WEIGHT ) );
/*?*/        pFmt->SetCJKPosture( (SvxPostureItem&)rSet.Get( RES_CHRATR_CJK_POSTURE ) );
/*?*/        pFmt->SetCTLFont( (SvxFontItem&)rSet.Get( RES_CHRATR_CTL_FONT ) );
/*?*/        pFmt->SetCTLHeight( (SvxFontHeightItem&)rSet.Get( RES_CHRATR_CTL_FONTSIZE ) );
/*?*/        pFmt->SetCTLWeight( (SvxWeightItem&)rSet.Get( RES_CHRATR_CTL_WEIGHT ) );
/*?*/        pFmt->SetCTLPosture( (SvxPostureItem&)rSet.Get( RES_CHRATR_CTL_POSTURE ) );
/*?*/       pFmt->SetUnderline( (SvxUnderlineItem&)rSet.Get( RES_CHRATR_UNDERLINE ) );
/*?*/       pFmt->SetCrossedOut( (SvxCrossedOutItem&)rSet.Get( RES_CHRATR_CROSSEDOUT ) );
/*?*/       pFmt->SetContour( (SvxContourItem&)rSet.Get( RES_CHRATR_CONTOUR ) );
/*?*/       pFmt->SetShadowed( (SvxShadowedItem&)rSet.Get( RES_CHRATR_SHADOWED ) );
/*?*/       pFmt->SetColor( (SvxColorItem&)rSet.Get( RES_CHRATR_COLOR ) );
/*?*/       pFmt->SetAdjust( (SvxAdjustItem&)rSet.Get( RES_PARATR_ADJUST ) );
/*?*/   }
/*?*/   if( UPDATE_BOX & eFlags )
/*?*/   {
/*?*/       pFmt->SetBox( (SvxBoxItem&)rSet.Get( RES_BOX ) );
/*?*/       pFmt->SetBackground( (SvxBrushItem&)rSet.Get( RES_BACKGROUND ) );
/*?*/
/*?*/       const SwTblBoxNumFormat* pNumFmtItem;
/*?*/       const SvNumberformat* pNumFormat = 0;
/*?*/       if( SFX_ITEM_SET == rSet.GetItemState( RES_BOXATR_FORMAT, TRUE,
/*?*/           (const SfxPoolItem**)&pNumFmtItem ) && pNFmtr &&
/*?*/           0 != (pNumFormat = pNFmtr->GetEntry( pNumFmtItem->GetValue() )) )
/*?*/           pFmt->SetValueFormat( ((SvNumberformat*)pNumFormat)->GetFormatstring(),
/*?*/                                   pNumFormat->GetLanguage(),
/*?*/                                   ::binfilter::GetAppLanguage() );
/*?*/       else
/*?*/       {
/*?*/           // defaulten
/*?*/           pFmt->SetValueFormat( aEmptyStr, LANGUAGE_SYSTEM,
/*?*/                                   ::binfilter::GetAppLanguage() );
/*?*/       }
/*?*/   }
/*?*/   // den Rest koennen wir nicht, StarCalc spezifisch
/*?*/
/*?*/   return *pFmt;
/*?*/}


/*?*/void SwTableAutoFmt::UpdateToSet( BYTE nPos, SfxItemSet& rSet,
/*?*/               UpdateFlags eFlags, SvNumberFormatter* pNFmtr ) const
/*?*/{
/*?*/   const SwBoxAutoFmt& rChg = GetBoxFmt( nPos );
/*?*/
/*?*/   if( UPDATE_CHAR & eFlags )
/*?*/   {
/*?*/       if( IsFont() )
/*?*/       {
/*?*/           rSet.Put( rChg.GetFont() );
/*?*/           rSet.Put( rChg.GetHeight() );
/*?*/           rSet.Put( rChg.GetWeight() );
/*?*/           rSet.Put( rChg.GetPosture() );
/*?*/             // #103065# do not insert empty CJK font
/*?*/             const SvxFontItem& rCJKFont = rChg.GetCJKFont();
/*?*/             if( rCJKFont.GetStyleName().Len() )
/*?*/             {
/*?*/                 rSet.Put( rChg.GetCJKFont() );
/*?*/                 rSet.Put( rChg.GetCJKHeight() );
/*?*/                 rSet.Put( rChg.GetCJKWeight() );
/*?*/                 rSet.Put( rChg.GetCJKPosture() );
/*?*/             }
/*?*/             else
/*?*/             {
/*?*/                 rSet.Put( rChg.GetHeight(), RES_CHRATR_CJK_FONTSIZE );
/*?*/                 rSet.Put( rChg.GetWeight(), RES_CHRATR_CJK_WEIGHT );
/*?*/                 rSet.Put( rChg.GetPosture(), RES_CHRATR_CJK_POSTURE );
/*?*/             }
/*?*/             // #103065# do not insert empty CTL font
/*?*/             const SvxFontItem& rCTLFont = rChg.GetCTLFont();
/*?*/             if( rCTLFont.GetStyleName().Len() )
/*?*/             {
/*?*/                 rSet.Put( rChg.GetCTLFont() );
/*?*/                 rSet.Put( rChg.GetCTLHeight() );
/*?*/                 rSet.Put( rChg.GetCTLWeight() );
/*?*/                 rSet.Put( rChg.GetCTLPosture() );
/*?*/             }
/*?*/             else
/*?*/             {
/*?*/                 rSet.Put( rChg.GetHeight(), RES_CHRATR_CTL_FONTSIZE );
/*?*/                 rSet.Put( rChg.GetWeight(), RES_CHRATR_CTL_WEIGHT );
/*?*/                 rSet.Put( rChg.GetPosture(), RES_CHRATR_CTL_POSTURE );
/*?*/             }
/*?*/           rSet.Put( rChg.GetUnderline() );
/*?*/           rSet.Put( rChg.GetCrossedOut() );
/*?*/           rSet.Put( rChg.GetContour() );
/*?*/           rSet.Put( rChg.GetShadowed() );
/*?*/           rSet.Put( rChg.GetColor() );
/*?*/       }
/*?*/       if( IsJustify() )
/*?*/           rSet.Put( rChg.GetAdjust() );
/*?*/   }
/*?*/
/*?*/   if( UPDATE_BOX & eFlags )
/*?*/   {
/*?*/       if( IsFrame() )
/*?*/           rSet.Put( rChg.GetBox() );
/*?*/       if( IsBackground() )
/*?*/           rSet.Put( rChg.GetBackground() );
/*?*/
/*?*/       if( IsValueFormat() && pNFmtr )
/*?*/       {
/*?*/           String sFmt; LanguageType eLng, eSys;
/*?*/           rChg.GetValueFormat( sFmt, eLng, eSys );
/*?*/           if( sFmt.Len() )
/*?*/           {
/*?*/               ULONG nKey = 0;
/*?*/               if ( eLng == LANGUAGE_SYSTEM && eSys != ::binfilter::GetAppLanguage() )
/*?*/               {
/*?*/                   //  #53381# wenn System beim Speichern etwas anderes war,
/*?*/                   //  muss konvertiert werden (geht nur mit eingebauten Formaten)
/*?*/                   ULONG nOrig = pNFmtr->GetEntryKey( sFmt, eSys );
/*?*/                   if ( nOrig != NUMBERFORMAT_ENTRY_NOT_FOUND )
/*?*/                       nKey = pNFmtr->GetFormatForLanguageIfBuiltIn( nOrig,
/*?*/                                       ::binfilter::GetAppLanguage() );
/*?*/               }
/*?*/               else    // sonst einfach suchen oder anlegen
/*?*/               {
/*?*/                   nKey = pNFmtr->GetEntryKey( sFmt, eLng );
/*?*/                   if( NUMBERFORMAT_ENTRY_NOT_FOUND == nKey )
/*?*/                   {
/*?*/                       xub_StrLen nCheckPos;
/*?*/                       short nType;
/*?*/                       pNFmtr->PutEntry( sFmt, nCheckPos, nType, nKey, eLng );
/*?*/                   }
/*?*/               }
/*?*/               rSet.Put( SwTblBoxNumFormat( nKey ));
/*?*/           }
/*?*/           else
/*?*/               rSet.ClearItem( RES_BOXATR_FORMAT );
/*?*/       }
/*?*/   }
/*?*/
/*?*/   // den Rest koennen wir nicht, StarCalc spezifisch
/*?*/}


/*?*/BOOL SwTableAutoFmt::Load( SvStream& rStream, const SwAfVersions& rVersions )
/*?*/{
/*?*/   BOOL    bRet = TRUE;DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  USHORT  nVal = 0;
//STRIP001  rStream >> nVal;
//STRIP001  bRet = 0 == rStream.GetError();
//STRIP001
//STRIP001  if( bRet && (nVal == AUTOFORMAT_DATA_ID_X ||
//STRIP001          (AUTOFORMAT_DATA_ID_504 <= nVal && nVal <= AUTOFORMAT_DATA_ID)) )
//STRIP001  {
//STRIP001      BOOL b;
//STRIP001      rStream.ReadByteString( aName, rStream.GetStreamCharSet() );
//STRIP001      if( AUTOFORMAT_DATA_ID_552 <= nVal )
//STRIP001      {
//STRIP001          rStream >> nStrResId;
//STRIP001          USHORT nId = RID_SVXSTR_TBLAFMT_BEGIN + nStrResId;
//STRIP001          if( RID_SVXSTR_TBLAFMT_BEGIN <= nId &&
//STRIP001              nId < RID_SVXSTR_TBLAFMT_END )
//STRIP001          {
//STRIP001              aName = SVX_RESSTR( nId );
//STRIP001          }
//STRIP001          else
//STRIP001              nStrResId = USHRT_MAX;
//STRIP001      }
//STRIP001      rStream >> b; bInclFont = b;
//STRIP001      rStream >> b; bInclJustify = b;
//STRIP001      rStream >> b; bInclFrame = b;
//STRIP001      rStream >> b; bInclBackground = b;
//STRIP001      rStream >> b; bInclValueFormat = b;
//STRIP001      rStream >> b; bInclWidthHeight = b;
//STRIP001
//STRIP001      bRet = 0 == rStream.GetError();
//STRIP001
//STRIP001      for( BYTE i = 0; i < 16; ++i )
//STRIP001      {
//STRIP001          SwBoxAutoFmt* pFmt = new SwBoxAutoFmt;
//STRIP001          bRet = pFmt->Load( rStream, rVersions, nVal );
//STRIP001          if( bRet )
//STRIP001              aBoxAutoFmt[ i ] = pFmt;
//STRIP001          else
//STRIP001          {
//STRIP001              delete pFmt;
//STRIP001              break;
//STRIP001          }
//STRIP001      }
//STRIP001  }
/*N*/   return bRet;
/*N*/ }

#ifdef READ_OLDVERS

/*?*/BOOL SwTableAutoFmt::LoadOld( SvStream& rStream, USHORT aLoadVer[] )
/*?*/{
/*?*/   BOOL    bRet = TRUE; DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  USHORT  nVal = 0;
//STRIP001  rStream >> nVal;
//STRIP001  bRet = 0 == rStream.GetError();
//STRIP001
//STRIP001  if( bRet && ( AUTOFORMAT_OLD_DATA_ID == nVal ))
//STRIP001  {
//STRIP001      BOOL b;
//STRIP001      rStream.ReadByteString( aName, rStream.GetStreamCharSet() );
//STRIP001      rStream >> b; bInclFont = b;
//STRIP001      rStream >> b; bInclJustify = b;
//STRIP001      rStream >> b; bInclFrame = b;
//STRIP001      rStream >> b; bInclBackground = b;
//STRIP001      bRet = (rStream.GetError() == 0);
//STRIP001
//STRIP001      for( int i = 0; i < 16; i++)
//STRIP001      {
//STRIP001          SwBoxAutoFmt* pFmt = new SwBoxAutoFmt;
//STRIP001          bRet = pFmt->LoadOld( rStream, aLoadVer );
//STRIP001          if( bRet )
//STRIP001              aBoxAutoFmt[ i ] = pFmt;
//STRIP001          else
//STRIP001          {
//STRIP001              delete pFmt;
//STRIP001              break;
//STRIP001          }
//STRIP001      }
//STRIP001  }
/*N*/   return bRet;
/*N*/ }
#endif


/*N*/BOOL SwTableAutoFmt::Save( SvStream& rStream ) const
/*N*/{
/*N*/   DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001 USHORT nVal = AUTOFORMAT_DATA_ID;
//STRIP001  BOOL b;
//STRIP001  rStream << nVal;
//STRIP001  rStream.WriteByteString( aName, rStream.GetStreamCharSet() );
//STRIP001  rStream << nStrResId;
//STRIP001  rStream << ( b = bInclFont );
//STRIP001  rStream << ( b = bInclJustify );
//STRIP001  rStream << ( b = bInclFrame );
//STRIP001  rStream << ( b = bInclBackground );
//STRIP001  rStream << ( b = bInclValueFormat );
//STRIP001  rStream << ( b = bInclWidthHeight );
//STRIP001
//STRIP001  BOOL bRet = 0 == rStream.GetError();
//STRIP001
//STRIP001  for( int i = 0; bRet && i < 16; ++i )
//STRIP001  {
//STRIP001      SwBoxAutoFmt* pFmt = aBoxAutoFmt[ i ];
//STRIP001      if( !pFmt )     // nicht gesetzt -> default schreiben
//STRIP001      {
//STRIP001          // falls noch nicht vorhanden:
//STRIP001          if( !pDfltBoxAutoFmt )
//STRIP001              pDfltBoxAutoFmt = new SwBoxAutoFmt;
//STRIP001          pFmt = pDfltBoxAutoFmt;
//STRIP001      }
//STRIP001      bRet = pFmt->Save( rStream );
//STRIP001  }
//STRIP001  return bRet;
/*N*/ }


/*N*/ SwTableAutoFmtTbl::SwTableAutoFmtTbl()
/*N*/ {
DBG_BF_ASSERT(0, "STRIP"); //STRIP001   String sNm;
//STRIP001  SwTableAutoFmt* pNew = new SwTableAutoFmt(
//STRIP001                          SwStyleNameMapper::GetUIName( RES_POOLCOLL_STANDARD, sNm ) );
//STRIP001
//STRIP001  SwBoxAutoFmt aNew;
//STRIP001
//STRIP001  BYTE i;
//STRIP001
//STRIP001  Color aColor( COL_BLUE );
//STRIP001  SvxBrushItem aBrushItem( aColor );
//STRIP001  aNew.SetBackground( aBrushItem );
//STRIP001  aNew.SetColor( Color( COL_WHITE ));
//STRIP001
//STRIP001  for( i = 0; i < 4; ++i )
//STRIP001      pNew->SetBoxFmt( aNew, i );
//STRIP001
//STRIP001  // 70% Grau
//STRIP001  aBrushItem.SetColor( RGB_COLORDATA( 0x4d, 0x4d, 0x4d ) );
//STRIP001  aNew.SetBackground( aBrushItem );
//STRIP001  for( i = 4; i <= 12; i += 4 )
//STRIP001      pNew->SetBoxFmt( aNew, i );
//STRIP001
//STRIP001  // 20% Grau
//STRIP001  aBrushItem.SetColor( RGB_COLORDATA( 0xcc, 0xcc, 0xcc ) );
//STRIP001  aNew.SetBackground( aBrushItem );
//STRIP001  aColor.SetColor( COL_BLACK );
//STRIP001  aNew.SetColor( aColor );
//STRIP001  for( i = 7; i <= 15; i += 4 )
//STRIP001      pNew->SetBoxFmt( aNew, i );
//STRIP001  for( i = 13; i <= 14; ++i )
//STRIP001      pNew->SetBoxFmt( aNew, i );
//STRIP001
//STRIP001  aBrushItem.SetColor( Color( COL_WHITE ) );
//STRIP001  aNew.SetBackground( aBrushItem );
//STRIP001  for( i = 5; i <= 6; ++i )
//STRIP001      pNew->SetBoxFmt( aNew, i );
//STRIP001  for( i = 9; i <= 10; ++i )
//STRIP001      pNew->SetBoxFmt( aNew, i );
//STRIP001
//STRIP001
//STRIP001  SvxBoxItem aBox;
//STRIP001  aBox.SetDistance( 55 );
//STRIP001  SvxBorderLine aLn( &aColor, DEF_LINE_WIDTH_0 );
//STRIP001  aBox.SetLine( &aLn, BOX_LINE_LEFT );
//STRIP001  aBox.SetLine( &aLn, BOX_LINE_BOTTOM );
//STRIP001
//STRIP001  for( i = 0; i <= 15; ++i )
//STRIP001  {
//STRIP001      aBox.SetLine( i <= 3 ? &aLn : 0, BOX_LINE_TOP );
//STRIP001      aBox.SetLine( (3 == ( i & 3 )) ? &aLn : 0, BOX_LINE_RIGHT );
//STRIP001      ((SwBoxAutoFmt&)pNew->GetBoxFmt( i )).SetBox( aBox );
//STRIP001  }
//STRIP001
//STRIP001  Insert( pNew, Count() );
/*N*/ }

/*N*/ BOOL SwTableAutoFmtTbl::Load()
/*N*/ {
/*N*/   BOOL bRet = FALSE;DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  String sNm( String::CreateFromAscii(
//STRIP001              RTL_CONSTASCII_STRINGPARAM( sAutoTblFmtName )));
//STRIP001  SvtPathOptions aOpt;
//STRIP001  if( aOpt.SearchFile( sNm, SvtPathOptions::PATH_USERCONFIG ))
//STRIP001  {
//STRIP001      SfxMedium aStream( sNm, STREAM_STD_READ, TRUE );
//STRIP001      bRet = Load( *aStream.GetInStream() );
//STRIP001  }
//STRIP001  else
//STRIP001      bRet = FALSE;
/*N*/   return bRet;
/*N*/ }

/*N*/ BOOL SwTableAutoFmtTbl::Save() const
/*N*/ {
DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001 SvtPathOptions aPathOpt;
//STRIP001  String sNm( URIHelper::SmartRelToAbs( aPathOpt.GetUserConfigPath() ));
//STRIP001  sNm += INET_PATH_TOKEN;
//STRIP001  sNm.AppendAscii( RTL_CONSTASCII_STRINGPARAM( sAutoTblFmtName ));
//STRIP001  SfxMedium aStream(sNm, STREAM_STD_WRITE, TRUE );
//STRIP001  return Save( *aStream.GetOutStream() ) && aStream.Commit();
/*N*/ }

/*N*/ BOOL SwTableAutoFmtTbl::Load( SvStream& rStream )
/*N*/ {
/*N*/   DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001 BOOL bRet = 0 == rStream.GetError();
//STRIP001  if (bRet)
//STRIP001  {
//STRIP001      // Achtung hier muss ein allgemeiner Header gelesen werden
//STRIP001      USHORT nVal = 0;
//STRIP001      rStream >> nVal;
//STRIP001      bRet = 0 == rStream.GetError();
//STRIP001
//STRIP001      if( bRet )
//STRIP001      {
//STRIP001          SwAfVersions aVersions;
//STRIP001
//STRIP001          if( nVal == AUTOFORMAT_ID_358 ||
//STRIP001                  (AUTOFORMAT_ID_504 <= nVal && nVal <= AUTOFORMAT_ID) )
//STRIP001          {
//STRIP001              UINT16 nFileVers = SOFFICE_FILEFORMAT_40;
//STRIP001              BYTE nChrSet, nCnt;
//STRIP001              long nPos = rStream.Tell();
//STRIP001              rStream >> nCnt >> nChrSet;
//STRIP001 //               if( 4 <= nCnt )
//STRIP001 //                   rStream >> nFileVers;
//STRIP001              if( rStream.Tell() != ULONG(nPos + nCnt) )
//STRIP001              {
//STRIP001                  ASSERT( !this, "Der Header enthaelt mehr/neuere Daten" );
//STRIP001                  rStream.Seek( nPos + nCnt );
//STRIP001              }
//STRIP001              rStream.SetStreamCharSet( (CharSet)nChrSet );
//STRIP001              rStream.SetVersion( nFileVers );
//STRIP001          }
//STRIP001
//STRIP001          if( nVal == AUTOFORMAT_ID_358 || nVal == AUTOFORMAT_ID_X ||
//STRIP001                  (AUTOFORMAT_ID_504 <= nVal && nVal <= AUTOFORMAT_ID) )
//STRIP001          {
//STRIP001              aVersions.Load( rStream, nVal );        // Item-Versionen
//STRIP001
//STRIP001              SwTableAutoFmt* pNew;
//STRIP001              USHORT nAnz = 0;
//STRIP001              rStream >> nAnz;
//STRIP001
//STRIP001              bRet = 0 == rStream.GetError();
//STRIP001
//STRIP001              for( USHORT i = 0; i < nAnz; ++i )
//STRIP001              {
//STRIP001                  pNew = new SwTableAutoFmt( aEmptyStr );
//STRIP001                  bRet = pNew->Load( rStream, aVersions );
//STRIP001                  if( bRet )
//STRIP001                  {
//STRIP001                      Insert( pNew, Count() );
//STRIP001                  }
//STRIP001                  else
//STRIP001                  {
//STRIP001                      delete pNew;
//STRIP001                      break;
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001 #ifdef READ_OLDVERS
//STRIP001          else if( AUTOFORMAT_OLD_ID == nVal || AUTOFORMAT_OLD_ID1 == nVal )
//STRIP001          {
//STRIP001              SwTableAutoFmt* pNew;
//STRIP001              USHORT nAnz = 0;
//STRIP001              rStream >> nAnz;
//STRIP001
//STRIP001              USHORT aArr[ 12 ];
//STRIP001              memset( aArr, 0, 12 * sizeof( USHORT ) );
//STRIP001              if( AUTOFORMAT_OLD_ID1 == nVal )
//STRIP001                  for( USHORT n = 0; n < 12; ++n )
//STRIP001                      rStream >> aArr[ n ];
//STRIP001
//STRIP001              bRet = 0 == rStream.GetError();
//STRIP001
//STRIP001              for( USHORT i = 0; i < nAnz; ++i )
//STRIP001              {
//STRIP001                  pNew = new SwTableAutoFmt( aEmptyStr );
//STRIP001                  bRet = pNew->LoadOld( rStream, aArr );
//STRIP001                  if( bRet )
//STRIP001                  {
//STRIP001                      Insert( pNew, Count() );
//STRIP001                  }
//STRIP001                  else
//STRIP001                  {
//STRIP001                      delete pNew;
//STRIP001                      break;
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001 #endif
//STRIP001      }
//STRIP001  }
//STRIP001  return bRet;
/*N*/ }


/*N*/ BOOL SwTableAutoFmtTbl::Save( SvStream& rStream ) const
/*N*/ {
/*N*/ DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001    BOOL bRet = 0 == rStream.GetError();
//STRIP001  if (bRet)
//STRIP001  {
//STRIP001      rStream.SetVersion( SOFFICE_FILEFORMAT_40 );
//STRIP001
//STRIP001      // Achtung hier muss ein allgemeiner Header gespeichert werden
//STRIP001      USHORT nVal = AUTOFORMAT_ID;
//STRIP001      rStream << nVal
//STRIP001              << (BYTE)2      // Anzahl von Zeichen des Headers incl. diesem
//STRIP001              << (BYTE)GetStoreCharSet( ::gsl_getSystemTextEncoding(),
//STRIP001                                          SOFFICE_FILEFORMAT_40 );
//STRIP001 //               << (BYTE)4      // Anzahl von Zeichen des Headers incl. diesem
//STRIP001 //               << (BYTE)::GetSystemCharSet()
//STRIP001 //               << (UNIT16)SOFFICE_FILEFORMAT_NOW;
//STRIP001      bRet = 0 == rStream.GetError();
//STRIP001
//STRIP001      //-----------------------------------------------------------
//STRIP001      // die VersionsNummer fuer alle Attribute schreiben
//STRIP001      (*this)[ 0 ]->GetBoxFmt( 0 ).SaveVerionNo( rStream );
//STRIP001
//STRIP001      rStream << (USHORT)(Count() - 1);
//STRIP001      bRet = 0 == rStream.GetError();
//STRIP001
//STRIP001      for( USHORT i = 1; bRet && i < Count(); ++i )
//STRIP001      {
//STRIP001          SwTableAutoFmt* pFmt = (*this)[ i ];
//STRIP001          bRet = pFmt->Save( rStream );
//STRIP001      }
//STRIP001  }
//STRIP001  rStream.Flush();
//STRIP001  return bRet;
/*N*/ }



}
