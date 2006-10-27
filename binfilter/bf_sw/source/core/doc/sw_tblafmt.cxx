/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_tblafmt.cxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 22:27:53 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/



#pragma hdrstop

#define ITEMID_BOXINFO      SID_ATTR_BORDER_INNER



#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _ZFORMAT_HXX //autogen
#include <svtools/zformat.hxx>
#endif
#ifndef _SVX_DIALOGS_HRC
#include <bf_svx/dialogs.hrc>
#endif

#define READ_OLDVERS        // erstmal noch alte Versionen lesen

#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _TBLAFMT_HXX
#include <tblafmt.hxx>
#endif
#ifndef _CELLATR_HXX
#include <cellatr.hxx>
#endif
#ifndef _ERRHDL_HXX //autogen
#include <errhdl.hxx>
#endif
#include "so3/staticbaseurl.hxx"
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
/*N*/ }

#ifdef READ_OLDVERS

/*?*/BOOL SwBoxAutoFmt::LoadOld( SvStream& rStream, USHORT aLoadVer[] )
/*?*/{
/*?*/   DBG_BF_ASSERT(0, "STRIP"); return FALSE; //STRIP001 SfxPoolItem* pNew;
/*N*/ }

#endif


/*?*/BOOL SwBoxAutoFmt::Save( SvStream& rStream ) const
/*?*/{
/*?*/DBG_BF_ASSERT(0, "STRIP");return FALSE;//STRIP001  aFont.Store( rStream, aFont.GetVersion(SOFFICE_FILEFORMAT_40)  );
/*N*/ }


/*?*/BOOL SwBoxAutoFmt::SaveVerionNo( SvStream& rStream ) const
/*?*/{
DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001      rStream << aFont.GetVersion( SOFFICE_FILEFORMAT_40 );
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
/*?*/               sal_uInt32 nKey = 0;
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
/*N*/   return bRet;
/*N*/ }

#ifdef READ_OLDVERS

/*?*/BOOL SwTableAutoFmt::LoadOld( SvStream& rStream, USHORT aLoadVer[] )
/*?*/{
/*?*/   BOOL    bRet = TRUE; DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/   return bRet;
/*N*/ }
#endif


/*N*/BOOL SwTableAutoFmt::Save( SvStream& rStream ) const
/*N*/{
/*N*/   DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001 USHORT nVal = AUTOFORMAT_DATA_ID;
/*N*/ }


/*N*/ SwTableAutoFmtTbl::SwTableAutoFmtTbl()
/*N*/ {
DBG_BF_ASSERT(0, "STRIP"); //STRIP001   String sNm;
/*N*/ }

/*N*/ BOOL SwTableAutoFmtTbl::Load()
/*N*/ {
/*N*/   BOOL bRet = FALSE;DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/   return bRet;
/*N*/ }

/*N*/ BOOL SwTableAutoFmtTbl::Save() const
/*N*/ {
DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001 SvtPathOptions aPathOpt;
/*N*/ }

/*N*/ BOOL SwTableAutoFmtTbl::Load( SvStream& rStream )
/*N*/ {
/*N*/   DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001 BOOL bRet = 0 == rStream.GetError();
/*N*/ }


/*N*/ BOOL SwTableAutoFmtTbl::Save( SvStream& rStream ) const
/*N*/ {
/*N*/ DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001    BOOL bRet = 0 == rStream.GetError();
/*N*/ }



}
