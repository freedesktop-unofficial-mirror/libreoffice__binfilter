/*************************************************************************
 *
 *  $RCSfile: sw_rdhnt.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 15:33:03 $
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

#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif

#ifndef _SVX_PAPERINF_HXX //autogen
#include <bf_svx/paperinf.hxx>
#endif
#ifndef _SFXMACITEM_HXX //autogen
#include <svtools/macitem.hxx>
#endif
#ifndef _SVX_WRLMITEM_HXX //autogen
#include <bf_svx/wrlmitem.hxx>
#endif
#ifndef _SVX_BRSHITEM_HXX //autogen
#include <bf_svx/brshitem.hxx>
#endif
#ifndef _SVX_PROTITEM_HXX //autogen
#include <bf_svx/protitem.hxx>
#endif
#ifndef _SVX_OPAQITEM_HXX //autogen
#include <bf_svx/opaqitem.hxx>
#endif
#ifndef _SVX_PRNTITEM_HXX //autogen
#include <bf_svx/prntitem.hxx>
#endif
#ifndef _SVX_ULSPITEM_HXX //autogen
#include <bf_svx/ulspitem.hxx>
#endif
#ifndef _SVX_LRSPITEM_HXX //autogen
#include <bf_svx/lrspitem.hxx>
#endif
#ifndef _SVX_PBINITEM_HXX //autogen
#include <bf_svx/pbinitem.hxx>
#endif
#ifndef _SVX_BRKITEM_HXX //autogen
#include <bf_svx/brkitem.hxx>
#endif
#ifndef _SVX_SHADITEM_HXX //autogen
#include <bf_svx/shaditem.hxx>
#endif
#ifndef _SVX_BOXITEM_HXX //autogen
#include <bf_svx/boxitem.hxx>
#endif
#ifndef _SVX_UDLNITEM_HXX //autogen
#include <bf_svx/udlnitem.hxx>
#endif
#ifndef _SVX_HYZNITEM_HXX //autogen
#include <bf_svx/hyznitem.hxx>
#endif
#ifndef _SVX_TSTPITEM_HXX //autogen
#include <bf_svx/tstpitem.hxx>
#endif
#ifndef _SVX_ORPHITEM_HXX //autogen
#include <bf_svx/orphitem.hxx>
#endif
#ifndef _SVX_WIDWITEM_HXX //autogen
#include <bf_svx/widwitem.hxx>
#endif
#ifndef _SVX_SPLTITEM_HXX //autogen
#include <bf_svx/spltitem.hxx>
#endif
#ifndef _SVX_ADJITEM_HXX //autogen
#include <bf_svx/adjitem.hxx>
#endif
#ifndef _SVX_LSPCITEM_HXX //autogen
#include <bf_svx/lspcitem.hxx>
#endif
#ifndef _SVX_NHYPITEM_HXX //autogen
#include <bf_svx/nhypitem.hxx>
#endif
#ifndef _SVX_PRSZITEM_HXX //autogen
#include <bf_svx/prszitem.hxx>
#endif
#ifndef _SVX_FHGTITEM_HXX //autogen
#include <bf_svx/fhgtitem.hxx>
#endif
#ifndef _SVX_ESCPITEM_HXX //autogen
#include <bf_svx/escpitem.hxx>
#endif
#ifndef _SVX_LANGITEM_HXX //autogen
#include <bf_svx/langitem.hxx>
#endif
#ifndef _SVX_CMAPITEM_HXX //autogen
#include <bf_svx/cmapitem.hxx>
#endif
#ifndef _SVX_CRSDITEM_HXX //autogen
#include <bf_svx/crsditem.hxx>
#endif
#ifndef _SVX_KERNITEM_HXX //autogen
#include <bf_svx/kernitem.hxx>
#endif
#ifndef _SVX_CNTRITEM_HXX //autogen
#include <bf_svx/cntritem.hxx>
#endif
#ifndef _SVX_SHDDITEM_HXX //autogen
#include <bf_svx/shdditem.hxx>
#endif
#ifndef _SVX_CSCOITEM_HXX //autogen
#include <bf_svx/cscoitem.hxx>
#endif
#ifndef _SVX_WGHTITEM_HXX //autogen
#include <bf_svx/wghtitem.hxx>
#endif
#ifndef _SVX_POSTITEM_HXX //autogen
#include <bf_svx/postitem.hxx>
#endif
#ifndef _SVX_FONTITEM_HXX //autogen
#include <bf_svx/fontitem.hxx>
#endif


#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _SWTYPES_HXX
#include <swtypes.hxx>      //fuer MIN_BORDER_DIST
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>
#endif
#ifndef _PARATR_HXX
#include <paratr.hxx>
#endif
#ifndef _FLDBAS_HXX
#include <fldbas.hxx>
#endif
#ifndef _FMTHBSH_HXX //autogen
#include <fmthbsh.hxx>
#endif
#ifndef _FMTRFMRK_HXX //autogen
#include <fmtrfmrk.hxx>
#endif
#ifndef _FMTFLD_HXX //autogen
#include <fmtfld.hxx>
#endif
#ifndef _FMTFLCNT_HXX //autogen
#include <fmtflcnt.hxx>
#endif
#ifndef _FCHRFMT_HXX //autogen
#include <fchrfmt.hxx>
#endif
#ifndef _FMTFTN_HXX //autogen
#include <fmtftn.hxx>
#endif
#ifndef _FMTPDSC_HXX //autogen
#include <fmtpdsc.hxx>
#endif
#ifndef _FMTCLDS_HXX //autogen
#include <fmtclds.hxx>
#endif
#ifndef _FMTFSIZE_HXX //autogen
#include <fmtfsize.hxx>
#endif
#ifndef _FMTFORDR_HXX //autogen
#include <fmtfordr.hxx>
#endif
#ifndef _FMTHDFT_HXX //autogen
#include <fmthdft.hxx>
#endif
#ifndef _FMTCNTNT_HXX //autogen
#include <fmtcntnt.hxx>
#endif
#ifndef _FMTANCHR_HXX //autogen
#include <fmtanchr.hxx>
#endif
#ifndef _FMTORNT_HXX //autogen
#include <fmtornt.hxx>
#endif
#ifndef _FMTSRND_HXX //autogen
#include <fmtsrnd.hxx>
#endif
#ifndef _RDSWG_HXX
#include <rdswg.hxx>
#endif
#ifndef _PAGEDESC_HXX
#include <pagedesc.hxx>
#endif
#ifndef _GRFATR_HXX
#include <grfatr.hxx>
#endif
#ifndef _OLDHNTID_HXX
#include <oldhntid.hxx>
#endif
#ifndef _SWGIDS_HXX
#include <swgids.hxx>
#endif
#ifndef _TOX_HXX
#include <tox.hxx>
#endif



//////////////////////////////// CHRATR.HXX ////////////////////////////////

//STRIP001 static USHORT InSWG_SwFont
//STRIP001 ( SwSwgReader& rPar, SfxItemSet* pSet, SwTxtNode* pNd, xub_StrLen nBgn, xub_StrLen nEnd )
//STRIP001 {
//STRIP001  long nNext = rPar.r.getskip();
//STRIP001  BYTE eFamily, eFontPitch, eFontCharSet;
//STRIP001  rPar.r >> eFamily
//STRIP001         >> eFontPitch
//STRIP001         >> eFontCharSet;
//STRIP001  String aName  = rPar.GetText( FALSE );
//STRIP001  String aStyle;
//STRIP001  if( rPar.r.tell() < nNext )
//STRIP001      aStyle = rPar.GetText( FALSE );
//STRIP001
//STRIP001  // irgendwann wandelte sich der StarBats vom ANSI- zum SYMBOL-Font
//STRIP001  if( SWG_VER_COMPAT >= rPar.aHdr.nVersion &&
//STRIP001      RTL_TEXTENCODING_SYMBOL !=
//STRIP001              eFontCharSet && aName.EqualsAscii( "StarBats" ) )
//STRIP001      eFontCharSet = RTL_TEXTENCODING_SYMBOL;
//STRIP001  SvxFontItem aAttr
//STRIP001      ( (FontFamily) eFamily, aName, aStyle,
//STRIP001        (FontPitch) eFontPitch,
//STRIP001        (rtl_TextEncoding) eFontCharSet );
//STRIP001  if( pSet ) pSet->Put( aAttr );
//STRIP001  else pNd->Insert( aAttr, nBgn, nEnd, SETATTR_NOTXTATRCHR );
//STRIP001  return aAttr.Which();
//STRIP001 }

//STRIP001 static USHORT InSWG_SvxPostureItem
//STRIP001 ( SwSwgReader& rPar, SfxItemSet* pSet, SwTxtNode* pNd, xub_StrLen nBgn, xub_StrLen nEnd )
//STRIP001 {
//STRIP001  BYTE nPosture;
//STRIP001  rPar.r >> nPosture;
//STRIP001  // backxxx war nie drin und wird nie drin sein!
//STRIP001  if( nPosture == 2 || nPosture == 4 ) return 0;
//STRIP001  if( nPosture > 1 ) nPosture = 2;
//STRIP001  SvxPostureItem aAttr( (const FontItalic) nPosture );
//STRIP001  if( pSet ) pSet->Put( aAttr );
//STRIP001  else pNd->Insert( aAttr, nBgn, nEnd, SETATTR_NOTXTATRCHR );
//STRIP001  return aAttr.Which();
//STRIP001 }

//STRIP001 static USHORT InSWG_SvxWeightItem
//STRIP001 ( SwSwgReader& rPar, SfxItemSet* pSet, SwTxtNode* pNd, xub_StrLen nBgn, xub_StrLen nEnd )
//STRIP001 {
//STRIP001  BYTE nWeight;
//STRIP001  rPar.r >> nWeight;
//STRIP001  nWeight = ( nWeight <= 4 ) ? WEIGHT_NORMAL : WEIGHT_BOLD;
//STRIP001  SvxWeightItem aAttr( (const FontWeight) nWeight );
//STRIP001  if( pSet ) pSet->Put( aAttr );
//STRIP001  else pNd->Insert( aAttr, nBgn, nEnd, SETATTR_NOTXTATRCHR );
//STRIP001  return aAttr.Which();
//STRIP001 }

//STRIP001 static USHORT InSWG_SwShadowed
//STRIP001 ( SwSwgReader& rPar, SfxItemSet* pSet, SwTxtNode* pNd, xub_StrLen nBgn, xub_StrLen nEnd )
//STRIP001 {
//STRIP001  BYTE nState;
//STRIP001  rPar.r >> nState;
//STRIP001  SvxShadowedItem aAttr( nState );
//STRIP001  if( pSet ) pSet->Put( aAttr );
//STRIP001  else pNd->Insert( aAttr, nBgn, nEnd, SETATTR_NOTXTATRCHR );
//STRIP001  return aAttr.Which();
//STRIP001 }

//STRIP001 static USHORT InSWG_SwContour
//STRIP001 ( SwSwgReader& rPar, SfxItemSet* pSet, SwTxtNode* pNd, xub_StrLen nBgn, xub_StrLen nEnd )
//STRIP001 {
//STRIP001  BYTE nState;
//STRIP001  rPar.r >> nState;
//STRIP001  SvxContourItem aAttr( nState );
//STRIP001  if( pSet ) pSet->Put( aAttr );
//STRIP001  else pNd->Insert( aAttr, nBgn, nEnd, SETATTR_NOTXTATRCHR );
//STRIP001  return aAttr.Which();
//STRIP001 }

//STRIP001 static USHORT InSWG_SwKerning
//STRIP001 ( SwSwgReader& rPar, SfxItemSet* pSet, SwTxtNode* pNd, xub_StrLen nBgn, xub_StrLen nEnd )
//STRIP001 {
//STRIP001  BYTE nState;    // ignored
//STRIP001  long frKernZ, frKernN;
//STRIP001  rPar.r >> nState >> frKernZ >> frKernN;
//STRIP001  // Alt = Punkte, neu = Twips
//STRIP001  short nKern = nState ? (short) (frKernZ * 20 / frKernN ) : 0;
//STRIP001  SvxKerningItem aAttr( nKern );
//STRIP001  if( pSet ) pSet->Put( aAttr );
//STRIP001  else pNd->Insert( aAttr, nBgn, nEnd, SETATTR_NOTXTATRCHR );
//STRIP001  return aAttr.Which();
//STRIP001 }

//STRIP001 static USHORT InSWG_SwCrossedOut
//STRIP001 ( SwSwgReader& rPar, SfxItemSet* pSet, SwTxtNode* pNd, xub_StrLen nBgn, xub_StrLen nEnd )
//STRIP001 {
//STRIP001  BYTE chCross, bCrossOutSpaces, nState;
//STRIP001  rPar.r >> chCross >> bCrossOutSpaces >> nState;
//STRIP001  SvxCrossedOutItem aAttr( (FontStrikeout) nState );
//STRIP001  if( pSet ) pSet->Put( aAttr );
//STRIP001  else pNd->Insert( aAttr, nBgn, nEnd, SETATTR_NOTXTATRCHR );
//STRIP001  if( bCrossOutSpaces ) {
//STRIP001      SvxWordLineModeItem aMode( FALSE );
//STRIP001      if( pSet ) pSet->Put( aMode );
//STRIP001      else pNd->Insert( aMode, nBgn, nEnd, SETATTR_NOTXTATRCHR );
//STRIP001  }
//STRIP001  return aAttr.Which();
//STRIP001 }

//STRIP001 static USHORT InSWG_SvxCaseMapItem
//STRIP001 ( SwSwgReader& rPar, SfxItemSet* pSet, SwTxtNode* pNd, xub_StrLen nBgn, xub_StrLen nEnd )
//STRIP001 {
//STRIP001  BYTE nCaseMap;
//STRIP001  rPar.r >> nCaseMap;
//STRIP001  SvxCaseMapItem aAttr( (const SvxCaseMap) nCaseMap );
//STRIP001  if( pSet ) pSet->Put( aAttr );
//STRIP001  else pNd->Insert( aAttr, nBgn, nEnd, SETATTR_NOTXTATRCHR );
//STRIP001  return aAttr.Which();
//STRIP001 }

//STRIP001 static USHORT InSWG_SwUnderline
//STRIP001 ( SwSwgReader& rPar, SfxItemSet* pSet, SwTxtNode* pNd, xub_StrLen nBgn, xub_StrLen nEnd )
//STRIP001 {
//STRIP001  BYTE nState, bUnderlineSpaces;
//STRIP001  rPar.r >> nState >> bUnderlineSpaces;
//STRIP001  SvxUnderlineItem aAttr( (FontUnderline) nState );
//STRIP001  if( pSet ) pSet->Put( aAttr );
//STRIP001  else pNd->Insert( aAttr, nBgn, nEnd, SETATTR_NOTXTATRCHR );
//STRIP001  if( bUnderlineSpaces ) {
//STRIP001      SvxWordLineModeItem aMode( FALSE );
//STRIP001      if( pSet ) pSet->Put( aMode );
//STRIP001      else pNd->Insert( aMode, nBgn, nEnd, SETATTR_NOTXTATRCHR );
//STRIP001  }
//STRIP001  return aAttr.Which();
//STRIP001 }

//STRIP001 static USHORT InSWG_SwLanguage
//STRIP001 ( SwSwgReader& rPar, SfxItemSet* pSet, SwTxtNode* pNd, xub_StrLen nBgn, xub_StrLen nEnd )
//STRIP001 {
//STRIP001  USHORT nLanguage;
//STRIP001  rPar.r >> nLanguage;
//STRIP001  if( !nLanguage )
//STRIP001      nLanguage = LANGUAGE_SYSTEM;
//STRIP001  else if( nLanguage == 0x400 )
//STRIP001      nLanguage = LANGUAGE_DONTKNOW;
//STRIP001 //   else
//STRIP001 //       rPar.TestLanguage( nLanguage );
//STRIP001  SvxLanguageItem aAttr( (LanguageType) nLanguage );
//STRIP001  if( pSet ) pSet->Put( aAttr );
//STRIP001  else pNd->Insert( aAttr, nBgn, nEnd, SETATTR_NOTXTATRCHR );
//STRIP001  return aAttr.Which();
//STRIP001 }

//STRIP001 static USHORT InSWG_SwEscapement
//STRIP001 ( SwSwgReader& rPar, SfxItemSet* pSet, SwTxtNode* pNd, xub_StrLen nBgn, xub_StrLen nEnd )
//STRIP001 {
//STRIP001  BYTE eEscape;
//STRIP001  long frEscapementZ, frEscapementN, frProportionZ, frProportionN;
//STRIP001  rPar.r >> eEscape >> frEscapementZ >> frEscapementN
//STRIP001         >> frProportionZ >> frProportionN;
//STRIP001  short nEsc = (short) ( frEscapementZ * 100 / frEscapementN );
//STRIP001  short nProp = (short) ( frProportionZ * 100 / frProportionN );
//STRIP001  switch( eEscape) {
//STRIP001      case SVX_ESCAPEMENT_OFF:
//STRIP001          nEsc = 0; nProp = 100; break;
//STRIP001      case SVX_ESCAPEMENT_SUBSCRIPT:
//STRIP001          nEsc = -nEsc; break;
//STRIP001  }
//STRIP001  SvxEscapementItem aAttr( nEsc, (BYTE) nProp );
//STRIP001  if( pSet ) pSet->Put( aAttr );
//STRIP001  else pNd->Insert( aAttr, nBgn, nEnd, SETATTR_NOTXTATRCHR );
//STRIP001  return aAttr.Which();
//STRIP001 }

//STRIP001 static USHORT InSWG_SwSize
//STRIP001 ( SwSwgReader& rPar, SfxItemSet* pSet, SwTxtNode* pNd, xub_StrLen nBgn, xub_StrLen nEnd )
//STRIP001 {
//STRIP001  long nSize;
//STRIP001  rPar.r >> nSize;
//STRIP001  SvxFontHeightItem aAttr( (USHORT) nSize );
//STRIP001  if( pSet ) pSet->Put( aAttr );
//STRIP001  else pNd->Insert( aAttr, nBgn, nEnd, SETATTR_NOTXTATRCHR );
//STRIP001  return aAttr.Which();
//STRIP001 }

//STRIP001 static USHORT InSWG_SwPropSize
//STRIP001 ( SwSwgReader& rPar, SfxItemSet* pSet, SwTxtNode* pNd, xub_StrLen nBgn, xub_StrLen nEnd )
//STRIP001 {
//STRIP001  long frPropSizeZ, frPropSizeN;
//STRIP001  rPar.r >> frPropSizeZ >> frPropSizeN;
//STRIP001  USHORT nFrac = (USHORT) ( frPropSizeZ * 100 / frPropSizeN );
//STRIP001  SvxPropSizeItem aAttr( nFrac, ITEMID_PROPSIZE );
//STRIP001  if( pSet ) pSet->Put( aAttr );
//STRIP001  else pNd->Insert( aAttr, nBgn, nEnd, SETATTR_NOTXTATRCHR );
//STRIP001  return aAttr.Which();
//STRIP001 }

//STRIP001 static USHORT InSWG_SwColor
//STRIP001 ( SwSwgReader& rPar, SfxItemSet* pSet, SwTxtNode* pNd, xub_StrLen nBgn, xub_StrLen nEnd )
//STRIP001 {
//STRIP001  USHORT red, green, blue;
//STRIP001  rPar.r >> red >> green >> blue;
//STRIP001  if( rPar.r.size() )
//STRIP001  {
//STRIP001      // Es ist noch etwas da, also ist es ein CharSetColor-Attribut
//STRIP001      BYTE cSet;
//STRIP001      rPar.r >> cSet;
//STRIP001      Color aColor( red, green, blue );
//STRIP001      SvxCharSetColorItem aAttr( aColor, (rtl_TextEncoding) cSet );
//STRIP001      if( pSet ) pSet->Put( aAttr );
//STRIP001      else pNd->Insert( aAttr, nBgn, nEnd, SETATTR_NOTXTATRCHR );
//STRIP001      return aAttr.Which();
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      SvxColorItem aAttr( Color( red, green, blue ) );
//STRIP001      if( pSet ) pSet->Put( aAttr );
//STRIP001      else pNd->Insert( aAttr, nBgn, nEnd, SETATTR_NOTXTATRCHR );
//STRIP001      return aAttr.Which();
//STRIP001  }
//STRIP001 }

//STRIP001 static USHORT InSWG_SwNoHyphenHere
//STRIP001 ( SwSwgReader& rPar, SfxItemSet* pSet, SwTxtNode* pNd, xub_StrLen nBgn, xub_StrLen nEnd )
//STRIP001 {
//STRIP001  BYTE bOn;
//STRIP001  rPar.r >> bOn;
//STRIP001  SvxNoHyphenItem aAttr;
//STRIP001  aAttr.SetValue( (BOOL) bOn );
//STRIP001  if( pSet ) pSet->Put( aAttr );
//STRIP001  else pNd->Insert( aAttr, nBgn, nEnd, SETATTR_NOTXTATRCHR );
//STRIP001  return aAttr.Which();
//STRIP001 }

//STRIP001 static USHORT InSWG_SwSoftHyphen
//STRIP001 ( SwSwgReader& rPar, SfxItemSet* pSet, SwTxtNode* pNd, xub_StrLen nBgn, xub_StrLen nEnd )
//STRIP001 {
//STRIP001  if( !pSet )
//STRIP001      pNd->Insert( CHAR_SOFTHYPHEN, SwIndex( pNd, nBgn ));
//STRIP001  return 0;
//STRIP001 }

//STRIP001 static USHORT InSWG_SwHardBlank
//STRIP001 ( SwSwgReader& rPar, SfxItemSet* pSet, SwTxtNode* pNd, xub_StrLen nBgn, xub_StrLen nEnd )
//STRIP001 {
//STRIP001  if( !pSet )
//STRIP001      pNd->Insert( CHAR_HARDBLANK, SwIndex( pNd, nBgn ));
//STRIP001  return 0;
//STRIP001 }

//STRIP001 static USHORT InSWG_SwRefMark
//STRIP001 ( SwSwgReader& rPar, SfxItemSet* pSet, SwTxtNode* pNd, xub_StrLen nBgn, xub_StrLen nEnd )
//STRIP001 {
//STRIP001  USHORT nMark;   // wird ignoriert
//STRIP001  rPar.r >> nMark;
//STRIP001  String aName = rPar.GetText( FALSE );
//STRIP001  if( pSet ) return 0;
//STRIP001  SwFmtRefMark aFmtAttr( aName );
//STRIP001  pNd->Insert( aFmtAttr, nBgn, nEnd, SETATTR_NOTXTATRCHR );
//STRIP001  return aFmtAttr.Which();
//STRIP001 }

//STRIP001 static USHORT InSWG_SwField
//STRIP001 ( SwSwgReader& rPar, SfxItemSet* pSet, SwTxtNode* pNd, xub_StrLen nBgn, xub_StrLen nEnd )
//STRIP001 {
//STRIP001  if( !rPar.r.size() ) return 0;
//STRIP001  SwField* pFld = rPar.InField();
//STRIP001  if( !pFld ) return 0;
//STRIP001  SwFmtFld aAttr( *pFld );
//STRIP001  delete pFld;
//STRIP001  if( pSet ) pSet->Put( aAttr );
//STRIP001  else pNd->Insert( aAttr, nBgn, nEnd, SETATTR_NOTXTATRCHR );
//STRIP001  return aAttr.Which();
//STRIP001 }

//STRIP001 static USHORT InSWG_SwFlyCnt
//STRIP001 ( SwSwgReader& rPar, SfxItemSet* pSet, SwTxtNode* pNd, xub_StrLen nBgn, xub_StrLen nEnd )
//STRIP001 {
//STRIP001  if( pSet )
//STRIP001      return 0;
//STRIP001  if( rPar.r.peek() != SWG_FLYFMT )
//STRIP001      return 0;
//STRIP001
//STRIP001  USHORT eSave_StartNodeType = rPar.eStartNodeType;
//STRIP001  rPar.eStartNodeType = SwFlyStartNode;
//STRIP001
//STRIP001  rPar.r.next();
//STRIP001  SwFlyFrmFmt* pFmt = (SwFlyFrmFmt*) rPar.InFormat( NULL );
//STRIP001  SwFmtFlyCnt aAttr( pFmt );
//STRIP001  rPar.eStartNodeType = eSave_StartNodeType;
//STRIP001
//STRIP001  if( pSet )
//STRIP001      pSet->Put( aAttr );
//STRIP001  else
//STRIP001      pNd->Insert( aAttr, nBgn, nEnd, SETATTR_NOTXTATRCHR );
//STRIP001  return aAttr.Which();
//STRIP001 }

//STRIP001 static USHORT InSWG_SwTOXMark
//STRIP001 ( SwSwgReader& rPar, SfxItemSet* pSet, SwTxtNode* pNd, xub_StrLen nBgn, xub_StrLen nEnd )
//STRIP001 {
//STRIP001  if( pSet ) return 0;
//STRIP001  // Flags:
//STRIP001  // 0x01 - hat eigenen Verz.-Namen
//STRIP001  // 0x02 - hat alternate Text
//STRIP001  // 0x04 - hat Primaeren Key
//STRIP001  // 0x08 - hat Sekundaeren Key
//STRIP001  BYTE nType, bFlags;
//STRIP001  const SwTOXType* pType = NULL;
//STRIP001  rPar.r >> nType >> bFlags;
//STRIP001  TOXTypes eType = (TOXTypes) nType;
//STRIP001  if( bFlags & 0x01 )
//STRIP001  {
//STRIP001      String aName( rPar.GetText( FALSE ) );
//STRIP001      USHORT n = rPar.pDoc->GetTOXTypeCount( eType );
//STRIP001      // Entsprechenden TOXtype suchen
//STRIP001      for( USHORT i = 0; i < n; i++ )
//STRIP001      {
//STRIP001          pType = rPar.pDoc->GetTOXType( eType, i );
//STRIP001          if( pType && pType->GetTypeName() == aName )
//STRIP001              break;
//STRIP001          pType = NULL;
//STRIP001      }
//STRIP001      // neu registrieren, falls noch nicht vorhanden
//STRIP001      if( !pType )
//STRIP001      {
//STRIP001          rPar.pDoc->InsertTOXType( SwTOXType( eType, aName ) );
//STRIP001          pType = rPar.pDoc->GetTOXType( eType, n );
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001      pType = rPar.pDoc->GetTOXType( eType, 0 );
//STRIP001  if( pType )
//STRIP001  {
//STRIP001      SwTOXMark aMark( pType );
//STRIP001      if( bFlags & 0x02 )
//STRIP001          aMark.SetAlternativeText( rPar.GetText( FALSE ) );
//STRIP001      switch( nType )
//STRIP001      {
//STRIP001          case TOX_INDEX:
//STRIP001              if( bFlags & 0x04 )
//STRIP001                  aMark.SetPrimaryKey( rPar.GetText( FALSE ) );
//STRIP001
//STRIP001              if( bFlags & 0x08 )
//STRIP001                  aMark.SetSecondaryKey( rPar.GetText( FALSE ) );
//STRIP001
//STRIP001              break;
//STRIP001          case TOX_USER:
//STRIP001          case TOX_CONTENT: {
//STRIP001              USHORT nLevel;
//STRIP001              rPar.r >> nLevel;
//STRIP001              aMark.SetLevel( nLevel );
//STRIP001              } break;
//STRIP001          default:
//STRIP001              rPar.Error(); return 0;
//STRIP001      }
//STRIP001      // TOXMark mit Alternativtext aber ohne 0xff. Sowas konnte man
//STRIP001      // ueber die UI zwar erstellen, weil's aber ein Bug ist werden
//STRIP001      // die jetzt ignoriert.
//STRIP001      if( !aMark.IsAlternativeText() ||
//STRIP001          (rPar.GetReadTxt() && rPar.GetReadTxt()->Len() >= nBgn &&
//STRIP001              '\xff' == rPar.GetReadTxt()->GetChar(nBgn) ))
//STRIP001      {
//STRIP001          // Bug 31560: several txo marks w/o end at the same position
//STRIP001          if( aMark.IsAlternativeText() &&
//STRIP001              pNd->GetTxtAttr( nBgn, aMark.Which() ) )
//STRIP001          {
//STRIP001              ASSERT( !aMark.IsAlternativeText(),
//STRIP001                      "several TOXMark without end at same position" );
//STRIP001              return 0;
//STRIP001          }
//STRIP001
//STRIP001          pNd->Insert( aMark, nBgn, nEnd, SETATTR_NOTXTATRCHR );
//STRIP001      }
//STRIP001      return aMark.Which();
//STRIP001  }
//STRIP001  rPar.Error(); return 0;
//STRIP001 }

//STRIP001 static USHORT InSWG_SwCharFmt
//STRIP001 ( SwSwgReader& rPar, SfxItemSet* pSet, SwTxtNode* pNd, xub_StrLen nBgn, xub_StrLen nEnd )
//STRIP001 {
//STRIP001  USHORT nIdx;
//STRIP001  rPar.r >> nIdx;
//STRIP001  if( (nIdx == IDX_NO_VALUE) ||
//STRIP001      ((nIdx&IDX_TYPEMASK) == IDX_COLLECTION) ) // bug fix #24427#
//STRIP001      return 0;
//STRIP001  SwCharFmt* pChFmt = (SwCharFmt*) rPar.FindFmt( nIdx, SWG_CHARFMT );
//STRIP001  SwFmtCharFmt aAttr( pChFmt );
//STRIP001  if( pSet ) pSet->Put( aAttr );
//STRIP001  else pNd->Insert( aAttr, nBgn, nEnd, SETATTR_NOTXTATRCHR );
//STRIP001  return aAttr.Which();
//STRIP001 }

//STRIP001 static USHORT InSWG_SwFtn
//STRIP001 ( SwSwgReader& rPar, SfxItemSet* pSet, SwTxtNode* pNd, xub_StrLen nBgn, xub_StrLen nEnd )
//STRIP001 {
//STRIP001  if( pSet ) return 0;
//STRIP001  String aNumber = rPar.GetText( FALSE );
//STRIP001  USHORT nNumber;
//STRIP001  rPar.r >> nNumber;
//STRIP001  SwFmtFtn aAttr;
//STRIP001  aAttr.SetNumStr( aNumber );
//STRIP001  aAttr.SetNumber( nNumber );
//STRIP001  // Der Footnote-Hint ist somewhat special. Er erhaelt
//STRIP001  // eine Section, wenn er in den TextNode eingefuegt wird (Brech!)
//STRIP001  // Daher muss der Text getrennt geparst werden (in FillTxtNode())
//STRIP001  if( pSet ) pSet->Put( aAttr );
//STRIP001  else pNd->Insert( aAttr, nBgn, nEnd, SETATTR_NOTXTATRCHR );
//STRIP001  return aAttr.Which();
//STRIP001 }

///////////////////////////// PARATR.HXX ///////////////////////////////////

//STRIP001 static USHORT InSWG_SwLineSpacing
//STRIP001 ( SwSwgReader& rPar, SfxItemSet* pSet, SwTxtNode*, xub_StrLen, xub_StrLen )
//STRIP001 {
//STRIP001  long frPropLineSpaceZ, frPropLineSpaceN;
//STRIP001  sal_Char nLineSpaceRule, nInterLineSpaceRule;
//STRIP001  short nInterLineSpace, nLineHeight;
//STRIP001  rPar.r >> frPropLineSpaceZ >> frPropLineSpaceN
//STRIP001         >> nLineSpaceRule   >> nInterLineSpaceRule
//STRIP001         >> nInterLineSpace  >> nLineHeight;
//STRIP001  short nFrac = (short) ( frPropLineSpaceZ * 100 / frPropLineSpaceN );
//STRIP001  SvxLineSpacingItem aAttr( nLineHeight );
//STRIP001  aAttr.SetInterLineSpace( nInterLineSpace );
//STRIP001  aAttr.SetPropLineSpace( (BYTE)nFrac );
//STRIP001  aAttr.GetLineSpaceRule() = (SvxLineSpace) nLineSpaceRule;
//STRIP001  aAttr.GetInterLineSpaceRule() = (SvxInterLineSpace) nInterLineSpaceRule;
//STRIP001  pSet->Put( aAttr );
//STRIP001  return aAttr.Which();
//STRIP001 }

//STRIP001 static USHORT InSWG_SwAdjust
//STRIP001 ( SwSwgReader& rPar, SfxItemSet* pSet, SwTxtNode*, xub_StrLen, xub_StrLen )
//STRIP001 {
//STRIP001  sal_Char eAdjustment;
//STRIP001  rPar.r >> eAdjustment;
//STRIP001  SvxAdjustItem aAttr( (SvxAdjust) eAdjustment );
//STRIP001  pSet->Put( aAttr );
//STRIP001  return aAttr.Which();
//STRIP001 }

//STRIP001 static USHORT InSWG_SwSplit
//STRIP001 ( SwSwgReader& rPar, SfxItemSet* pSet, SwTxtNode*, xub_StrLen, xub_StrLen )
//STRIP001 {
//STRIP001  sal_Char bSplit;
//STRIP001  rPar.r >> bSplit;
//STRIP001  SvxFmtSplitItem aAttr( (BOOL) bSplit );
//STRIP001  pSet->Put( aAttr );
//STRIP001  return aAttr.Which();
//STRIP001 }

//STRIP001 static USHORT InSWG_SwWidows
//STRIP001 ( SwSwgReader& rPar, SfxItemSet* pSet, SwTxtNode*, xub_StrLen, xub_StrLen )
//STRIP001 {
//STRIP001  long nTwips;
//STRIP001  short nLines;
//STRIP001  rPar.r >> nLines >> nTwips;
//STRIP001  SvxWidowsItem aAttr( (BYTE) nLines );
//STRIP001  pSet->Put( aAttr );
//STRIP001  return aAttr.Which();
//STRIP001 }

//STRIP001 static USHORT InSWG_SwOrphans
//STRIP001 ( SwSwgReader& rPar, SfxItemSet* pSet, SwTxtNode*, xub_StrLen, xub_StrLen )
//STRIP001 {
//STRIP001  long nTwips;
//STRIP001  short nLines;
//STRIP001  rPar.r >> nLines >> nTwips;
//STRIP001  SvxOrphansItem aAttr( (BYTE) nLines );
//STRIP001  pSet->Put( aAttr );
//STRIP001  return aAttr.Which();
//STRIP001 }

//STRIP001 static USHORT InSWG_SwTabStop
//STRIP001 ( SwSwgReader& rPar, SfxItemSet* pSet, SwTxtNode*, xub_StrLen, xub_StrLen )
//STRIP001 {
//STRIP001  short nTabs;
//STRIP001  rPar.r >> nTabs;
//STRIP001  SvxTabStopItem aAttr( 0, 0 );
//STRIP001  for( int i = 0; i < nTabs; i++ )
//STRIP001  {
//STRIP001      long nPos;
//STRIP001      BYTE eAdjust, cDecimal, cFill;
//STRIP001      rPar.r >> nPos >> eAdjust >> cDecimal >> cFill;
//STRIP001      if( !i || SVX_TAB_ADJUST_DEFAULT != eAdjust )
//STRIP001          aAttr.Insert( SvxTabStop
//STRIP001              ( (SwTwips) nPos, (SvxTabAdjust) eAdjust, cDecimal, cFill ) );
//STRIP001  }
//STRIP001  pSet->Put( aAttr );
//STRIP001  return aAttr.Which();
//STRIP001 }

//STRIP001 static USHORT InSWG_SwHyphenZone
//STRIP001 ( SwSwgReader& rPar, SfxItemSet* pSet, SwTxtNode*, xub_StrLen, xub_StrLen )
//STRIP001 {
//STRIP001  BYTE bHyphen, bHyphenPageEnd;
//STRIP001  USHORT nMinLead, nMinTrail, nMaxHyphens;
//STRIP001  rPar.r >> bHyphen >> bHyphenPageEnd >> nMinLead >> nMinTrail >> nMaxHyphens;
//STRIP001  SvxHyphenZoneItem aAttr;
//STRIP001  aAttr.SetHyphen( BOOL( bHyphen != 0 ) );
//STRIP001  aAttr.SetPageEnd( BOOL( bHyphenPageEnd != 0 ) );
//STRIP001  aAttr.GetMinLead() = (BYTE) nMinLead;
//STRIP001  aAttr.GetMinTrail() = (BYTE) nMinTrail;
//STRIP001  aAttr.GetMaxHyphens() = (BYTE) nMaxHyphens;
//STRIP001  pSet->Put( aAttr );
//STRIP001  return aAttr.Which();
//STRIP001 }

//STRIP001 static USHORT InSWG_SwDropCaps
//STRIP001 ( SwSwgReader& rPar, SfxItemSet* pSet, SwTxtNode*, xub_StrLen, xub_StrLen )
//STRIP001 {
//STRIP001  USHORT nLines, nChars, nDistance, nX, nY, nFmt;
//STRIP001  rPar.r >> nLines >> nChars >> nDistance >> nX >> nY >> nFmt;
//STRIP001  SwFmtDrop aAttr;
//STRIP001  aAttr.GetLines() = (BYTE) nLines;
//STRIP001  aAttr.GetChars() = (BYTE) nChars;
//STRIP001  aAttr.GetDistance() = nDistance;
//STRIP001  aAttr.GetWholeWord() = FALSE;
//STRIP001  if( nFmt != IDX_NO_VALUE )
//STRIP001  {
//STRIP001      SwCharFmt* pSet = (SwCharFmt*) rPar.FindFmt( nFmt, SWG_CHARFMT );
//STRIP001      aAttr.SetCharFmt( pSet );
//STRIP001  }
//STRIP001  pSet->Put( aAttr );
//STRIP001  return aAttr.Which();
//STRIP001 }

/////////////////////////////// FRMATR.HXX ///////////////////////////////

//STRIP001 static USHORT InSWG_SwBox
//STRIP001 ( SwSwgReader& rPar, SfxItemSet* pSet, SwTxtNode*, xub_StrLen, xub_StrLen )
//STRIP001 {
//STRIP001  short nDistance;
//STRIP001  rPar.r >> nDistance;
//STRIP001  SvxBoxItem aAttr;
//STRIP001  aAttr.SetDistance( nDistance );
//STRIP001
//STRIP001  BOOL bDone = FALSE;
//STRIP001  while( !bDone )
//STRIP001  {
//STRIP001      BYTE ch = rPar.r.next();
//STRIP001      switch( ch )
//STRIP001      {
//STRIP001          case SWG_TOP:
//STRIP001          case SWG_LEFT:
//STRIP001          case SWG_RIGHT:
//STRIP001          case SWG_BOTTOM:break;
//STRIP001          default: bDone = TRUE;
//STRIP001      }
//STRIP001      if( !bDone )
//STRIP001      {
//STRIP001          USHORT red, green, blue;
//STRIP001          short nOutline, nInline, nDistance;
//STRIP001          rPar.r >> red >> green >> blue;
//STRIP001          rPar.r >> nOutline >> nInline >> nDistance;
//STRIP001          Color aClr( red, green, blue );
//STRIP001          SvxBorderLine aBorder( &aClr, nOutline, nInline, nDistance );
//STRIP001          switch( ch )
//STRIP001          {
//STRIP001              case SWG_TOP:    aAttr.SetLine( &aBorder, BOX_LINE_TOP ); break;
//STRIP001              case SWG_LEFT:   aAttr.SetLine( &aBorder, BOX_LINE_LEFT ); break;
//STRIP001              case SWG_RIGHT:  aAttr.SetLine( &aBorder, BOX_LINE_RIGHT ); break;
//STRIP001              case SWG_BOTTOM: aAttr.SetLine( &aBorder, BOX_LINE_BOTTOM ); break;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  if ( rPar.aHdr.nVersion < SWG_VER_NEWALIGN )
//STRIP001  {
//STRIP001      //Wenn mindestens eine Line gesetzt wurde, so wird jetzt ein minimaler
//STRIP001      //Abstand eingetragen.
//STRIP001      if ( (aAttr.GetTop()    || aAttr.GetLeft() ||
//STRIP001            aAttr.GetBottom() || aAttr.GetRight()   ) &&
//STRIP001            nDistance < MIN_BORDER_DIST)
//STRIP001      {
//STRIP001          aAttr.SetDistance( MIN_BORDER_DIST );
//STRIP001      }
//STRIP001  }
//STRIP001  pSet->Put( aAttr );
//STRIP001  return aAttr.Which();
//STRIP001 }

//STRIP001 static USHORT InSWG_SwFmtShadow
//STRIP001 ( SwSwgReader& rPar, SfxItemSet* pSet, SwTxtNode*, xub_StrLen, xub_StrLen )
//STRIP001 {
//STRIP001  BYTE cLoc;
//STRIP001  USHORT nWidth;
//STRIP001  rPar.r >> cLoc >> nWidth;
//STRIP001  Color aCol( rPar.InBrush() );
//STRIP001  SvxShadowItem aAttr( RES_SHADOW, &aCol, nWidth, (SvxShadowLocation) cLoc );
//STRIP001  pSet->Put( aAttr );
//STRIP001  return aAttr.Which();
//STRIP001 }

//STRIP001 static USHORT InSWG_SwFmtPageDesc
//STRIP001 ( SwSwgReader& rPar, SfxItemSet* pSet, SwTxtNode*, xub_StrLen, xub_StrLen )
//STRIP001 {
//STRIP001  // Dieser Hint kann bereits eingelesen werden, ehe die
//STRIP001  // Seitenbeschreibungen drin sind. Also, bitte erst mal speichern!
//STRIP001  // Das benoetigte Set muss leider "per Hand" nachgetragen werden
//STRIP001  // (siehe rdfmts.cxx)
//STRIP001
//STRIP001  // Komischerweise gibt es immer noch leere PageDesc-Hints:
//STRIP001  if( !rPar.r.size() )
//STRIP001  {
//STRIP001      SwFmtPageDesc aAttr( NULL );
//STRIP001      pSet->Put( aAttr );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      String aName( rPar.GetText( FALSE ) );
//STRIP001      USHORT nOff = 0;
//STRIP001      rPar.r >> nOff;
//STRIP001      if( aName.Len() )
//STRIP001          rPar.AddPageDescLink( aName, nOff );
//STRIP001      //JP 29.05.00: set always the hint into the AttrSet, because in
//STRIP001      //             InsertMode the NodeAttrSet for PageDescLink only created
//STRIP001      //             if there Attributes exists.
//STRIP001      SwFmtPageDesc aAttr( NULL );
//STRIP001      pSet->Put( aAttr );
//STRIP001  }
//STRIP001  return 0;
//STRIP001 }

//STRIP001 static USHORT InSWG_SwFmtMacro
//STRIP001 ( SwSwgReader& rPar, SfxItemSet* pSet, SwTxtNode*, xub_StrLen, xub_StrLen )
//STRIP001 {
//STRIP001  if( rPar.r.peek() != SWG_MACROTBL )
//STRIP001      return 0;
//STRIP001  rPar.r.next();
//STRIP001  SvxMacroItem aAttr;
//STRIP001  short nMacro;
//STRIP001  rPar.r >> nMacro;
//STRIP001  for( short i = 0; i < nMacro; i++ )
//STRIP001  {
//STRIP001      USHORT nEvent;
//STRIP001      rPar.r >> nEvent;
//STRIP001      String aLib = rPar.GetText();
//STRIP001      String aMac = rPar.GetText();
//STRIP001      aAttr.SetMacro( nEvent, SvxMacro( aMac, aLib, STARBASIC ) );
//STRIP001  }
//STRIP001  pSet->Put( aAttr );
//STRIP001  return aAttr.Which();
//STRIP001 }

//STRIP001 static USHORT InSWG_SwFmtCol
//STRIP001 ( SwSwgReader& rPar, SfxItemSet* pSet, SwTxtNode*, xub_StrLen, xub_StrLen )
//STRIP001 {
//STRIP001  // Die Longs muessen runtergerechnet werden
//STRIP001  sal_Char nLineAdj, bOrtho;
//STRIP001  short nGutterWidth;
//STRIP001  long  nHeightNum, nHeightDenom, nWishWidth;
//STRIP001  rPar.r.long4();
//STRIP001  rPar.r >> nLineAdj
//STRIP001         >> bOrtho
//STRIP001         >> nGutterWidth
//STRIP001         >> nWishWidth
//STRIP001         >> nHeightNum
//STRIP001         >> nHeightDenom;
//STRIP001  USHORT nMax = ( nWishWidth == LONG_MAX )
//STRIP001              ? USHRT_MAX
//STRIP001              : (USHORT) nWishWidth;
//STRIP001  ASSERT( nWishWidth == LONG_MAX || nWishWidth <= 65535L, "WishWidth zu gross" );
//STRIP001  long nFactor = nWishWidth / nMax;
//STRIP001  SwFmtCol aAttr;
//STRIP001  USHORT nLineWidth;
//STRIP001  Color aLineColor;
//STRIP001  rPar.InPen(nLineWidth, aLineColor);
//STRIP001  USHORT nCol;
//STRIP001  rPar.r >> nCol;
//STRIP001  if( nCol )
//STRIP001  {
//STRIP001      for( USHORT i = 0; i < nCol; i++ )
//STRIP001      {
//STRIP001          long nWishWidth;
//STRIP001          USHORT nLeft, nUpper, nRight, nLower;
//STRIP001          rPar.r >> nWishWidth >> nLeft >> nUpper >> nRight >> nLower;
//STRIP001          SwColumn* pCol = new SwColumn;
//STRIP001          pCol->SetWishWidth( (USHORT) ( nWishWidth / nFactor ) );
//STRIP001          pCol->SetLeft( nLeft );
//STRIP001          pCol->SetUpper( nUpper );
//STRIP001          pCol->SetRight( nRight );
//STRIP001          pCol->SetLower( nLower );
//STRIP001          aAttr.GetColumns().Insert( pCol, i );
//STRIP001      }
//STRIP001  }
//STRIP001  aAttr.SetLineColor( aLineColor );
//STRIP001  aAttr.SetLineWidth( nLineWidth );
//STRIP001  aAttr.SetWishWidth( (USHORT) nWishWidth );
//STRIP001  aAttr.SetLineHeight( (BYTE) ( nHeightNum * 100 / nHeightDenom ) );
//STRIP001  aAttr.SetLineAdj( (SwColLineAdj) nLineAdj );
//STRIP001  // temporaerer Bug Fix
//STRIP001  if( nCol )
//STRIP001      // Wert direkt mit dem Silberhammer einschlagen.
//STRIP001      aAttr._SetOrtho( (BOOL) bOrtho );
//STRIP001  rPar.r.long3();
//STRIP001  pSet->Put( aAttr );
//STRIP001  return aAttr.Which();
//STRIP001 }

//STRIP001 static USHORT InSWG_SwFmtFrmSize
//STRIP001 ( SwSwgReader& rPar, SfxItemSet* pSet, SwTxtNode*, xub_StrLen, xub_StrLen )
//STRIP001 {
//STRIP001  BYTE nSizeType;
//STRIP001  long nWidth, nHeight;
//STRIP001  rPar.r >> nSizeType;
//STRIP001  rPar.r.long4();
//STRIP001  rPar.r >> nWidth >> nHeight;
//STRIP001  rPar.r.long3();
//STRIP001  if( rPar.IsTableBoxFrmFmt() )
//STRIP001  {
//STRIP001      // FrmSize-Attribut in TableBoxes: umdrehen!
//STRIP001      long n = nWidth;
//STRIP001      nWidth = nHeight;
//STRIP001      nHeight = n;
//STRIP001  }
//STRIP001  else if( nSizeType == ATT_FIX_SIZE
//STRIP001        && nWidth == LONG_MAX
//STRIP001        && nHeight == LONG_MAX )
//STRIP001  {
//STRIP001      // Uninitialisertes FrmSize-Attribut: setze auf DIN A4
//STRIP001      Size aSzA4 = SvxPaperInfo::GetPaperSize( SVX_PAPER_A4 );
//STRIP001      nWidth = aSzA4.Width();
//STRIP001      nHeight = aSzA4.Height();
//STRIP001  }
//STRIP001
//STRIP001  SwFmtFrmSize aAttr( (SwFrmSize) nSizeType, nWidth, nHeight );
//STRIP001  pSet->Put( aAttr );
//STRIP001  return aAttr.Which();
//STRIP001 }

//STRIP001 static USHORT InSWG_SwFmtFillOrder
//STRIP001 ( SwSwgReader& rPar, SfxItemSet* pSet, SwTxtNode*, xub_StrLen, xub_StrLen )
//STRIP001 {
//STRIP001  BYTE nFillOrder;
//STRIP001  rPar.r >> nFillOrder;
//STRIP001  SwFmtFillOrder aAttr( (SwFillOrder) nFillOrder );
//STRIP001  pSet->Put( aAttr );
//STRIP001  return aAttr.Which();
//STRIP001 }

//STRIP001 static USHORT InSWG_SwPageBreak
//STRIP001 ( SwSwgReader& rPar, SfxItemSet* pSet, SwTxtNode*, xub_StrLen, xub_StrLen )
//STRIP001 {
//STRIP001  BYTE nBreak, nIsAuto;
//STRIP001  rPar.r >> nBreak >> nIsAuto;
//STRIP001  if( nBreak != (SvxBreak) SVX_BREAK_NONE )
//STRIP001      nBreak += (SvxBreak) SVX_BREAK_COLUMN_BOTH;
//STRIP001  SvxFmtBreakItem aAttr( (SvxBreak) nBreak );
//STRIP001  pSet->Put( aAttr );
//STRIP001  return aAttr.Which();
//STRIP001 }

//STRIP001 static USHORT InSWG_SwColBreak
//STRIP001 ( SwSwgReader& rPar, SfxItemSet* pSet, SwTxtNode*, xub_StrLen, xub_StrLen )
//STRIP001 {
//STRIP001  BYTE nBreak, nIsAuto;
//STRIP001  rPar.r >> nBreak >> nIsAuto;
//STRIP001  SvxFmtBreakItem aAttr( (SvxBreak) nBreak );
//STRIP001  pSet->Put( aAttr );
//STRIP001  return aAttr.Which();
//STRIP001 }

//STRIP001 static USHORT InSWG_SwFmtPaperBin
//STRIP001 ( SwSwgReader& rPar, SfxItemSet* pSet, SwTxtNode*, xub_StrLen, xub_StrLen )
//STRIP001 {
//STRIP001  short nTray;
//STRIP001  rPar.r >> nTray;
//STRIP001  SvxPaperBinItem aAttr( RES_PAPER_BIN,  (BYTE) nTray );
//STRIP001  pSet->Put( aAttr );
//STRIP001  return aAttr.Which();
//STRIP001 }

//STRIP001 static USHORT InSWG_SwLRSpace
//STRIP001 ( SwSwgReader& rPar, SfxItemSet* pSet, SwTxtNode*, xub_StrLen, xub_StrLen )
//STRIP001 {
//STRIP001  long left, right, firstline;
//STRIP001  rPar.r >> left >> right >> firstline;
//STRIP001  SvxLRSpaceItem aAttr;
//STRIP001  aAttr.SetTxtLeft( (USHORT) left );
//STRIP001  aAttr.SetRight( (USHORT) right );
//STRIP001  aAttr.SetTxtFirstLineOfst( USHORT(firstline) );
//STRIP001  pSet->Put( aAttr );
//STRIP001  return aAttr.Which();
//STRIP001 }

//STRIP001 static USHORT InSWG_SwULSpace
//STRIP001 ( SwSwgReader& rPar, SfxItemSet* pSet, SwTxtNode*, xub_StrLen, xub_StrLen )
//STRIP001 {
//STRIP001  long upper, lower;
//STRIP001  rPar.r >> upper >> lower;
//STRIP001  SvxULSpaceItem aAttr;
//STRIP001  aAttr.SetUpper( (USHORT) upper );
//STRIP001  aAttr.SetLower( (USHORT) lower );
//STRIP001  pSet->Put( aAttr );
//STRIP001  return aAttr.Which();
//STRIP001 }

//STRIP001 static USHORT InSWG_SwFmtHeader
//STRIP001 ( SwSwgReader& rPar, SfxItemSet* pSet, SwTxtNode*, xub_StrLen, xub_StrLen )
//STRIP001 {
//STRIP001  BYTE bActive;
//STRIP001  SwFrmFmt* pFmt = NULL;
//STRIP001  rPar.r >> bActive;
//STRIP001  if( rPar.r.peek() == SWG_FREEFMT )
//STRIP001  {
//STRIP001      USHORT eSave_StartNodeType = rPar.eStartNodeType;
//STRIP001      rPar.eStartNodeType = SwHeaderStartNode;
//STRIP001
//STRIP001      rPar.r.next();
//STRIP001      pFmt = (SwFrmFmt*) rPar.InFormat( NULL );
//STRIP001      rPar.RegisterFmt( *pFmt );
//STRIP001      SwFmtHeader aAttr( pFmt );
//STRIP001      aAttr.SetActive( BOOL( bActive ) );
//STRIP001      pSet->Put( aAttr );
//STRIP001      rPar.eStartNodeType = eSave_StartNodeType;
//STRIP001
//STRIP001      return aAttr.Which();
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      SwFmtHeader aAttr( BOOL( bActive != 0 ) );
//STRIP001      pSet->Put( aAttr );
//STRIP001      return aAttr.Which();
//STRIP001  }
//STRIP001 }

//STRIP001 static USHORT InSWG_SwFmtFooter
//STRIP001 ( SwSwgReader& rPar, SfxItemSet* pSet, SwTxtNode*, xub_StrLen, xub_StrLen )
//STRIP001 {
//STRIP001  BYTE bActive;
//STRIP001  SwFrmFmt* pFmt = NULL;
//STRIP001  rPar.r >> bActive;
//STRIP001  if( rPar.r.peek() == SWG_FREEFMT )
//STRIP001  {
//STRIP001      USHORT eSave_StartNodeType = rPar.eStartNodeType;
//STRIP001      rPar.eStartNodeType = SwFooterStartNode;
//STRIP001
//STRIP001      rPar.r.next();
//STRIP001      pFmt = (SwFrmFmt*) rPar.InFormat( NULL );
//STRIP001      rPar.RegisterFmt( *pFmt );
//STRIP001      SwFmtFooter aAttr( pFmt );
//STRIP001      aAttr.SetActive( BOOL( bActive != 0 ) );
//STRIP001      pSet->Put( aAttr );
//STRIP001      rPar.eStartNodeType = eSave_StartNodeType;
//STRIP001
//STRIP001      return aAttr.Which();
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      SwFmtFooter aAttr( BOOL( bActive != 0 ) );
//STRIP001      pSet->Put( aAttr );
//STRIP001      return aAttr.Which();
//STRIP001  }
//STRIP001 }

//STRIP001 static USHORT InSWG_SwFmtCntnt
//STRIP001 ( SwSwgReader& rPar, SfxItemSet* pSet, SwTxtNode*, xub_StrLen, xub_StrLen )
//STRIP001 {
//STRIP001  SwFmtCntnt aAttr( rPar.InSection() );
//STRIP001  pSet->Put( aAttr );
//STRIP001  return aAttr.Which();
//STRIP001 }

//STRIP001 static USHORT InSWG_SwFmtPrint
//STRIP001 ( SwSwgReader& rPar, SfxItemSet* pSet, SwTxtNode*, xub_StrLen, xub_StrLen )
//STRIP001 {
//STRIP001  BYTE bActive;
//STRIP001  rPar.r >> bActive;
//STRIP001  SvxPrintItem aAttr( RES_PRINT, BOOL (bActive != 0 ) );
//STRIP001  pSet->Put( aAttr );
//STRIP001  return aAttr.Which();
//STRIP001 }

//STRIP001 static USHORT InSWG_SwFmtOpaque
//STRIP001 ( SwSwgReader& rPar, SfxItemSet* pSet, SwTxtNode*, xub_StrLen, xub_StrLen )
//STRIP001 {
//STRIP001  BYTE bActive;
//STRIP001  rPar.r >> bActive;
//STRIP001  SvxOpaqueItem aAttr( RES_OPAQUE, BOOL( bActive != 0 ) );
//STRIP001  pSet->Put( aAttr );
//STRIP001  return aAttr.Which();
//STRIP001 }

//STRIP001 static USHORT InSWG_SwFmtProtect
//STRIP001 ( SwSwgReader& rPar, SfxItemSet* pSet, SwTxtNode*, xub_StrLen, xub_StrLen )
//STRIP001 {
//STRIP001  BYTE bProtFrame, bProtCntnt;
//STRIP001  rPar.r >> bProtFrame >> bProtCntnt;
//STRIP001  SvxProtectItem aAttr;
//STRIP001  aAttr.SetPosProtect( BOOL( bProtFrame != 0 ) );
//STRIP001  aAttr.SetSizeProtect( BOOL( bProtFrame != 0 ) );
//STRIP001  aAttr.SetCntntProtect( BOOL( bProtCntnt != 0 ) );
//STRIP001  pSet->Put( aAttr );
//STRIP001  return aAttr.Which();
//STRIP001 }

//STRIP001 static USHORT InSWG_SwFmtSurround
//STRIP001 ( SwSwgReader& rPar, SfxItemSet* pSet, SwTxtNode*, xub_StrLen, xub_StrLen )
//STRIP001 {
//STRIP001  BYTE nType, bGold;
//STRIP001  rPar.r >> nType >> bGold;
//STRIP001  SwFmtSurround aAttr( (SwSurround) nType );
//STRIP001  if( bGold )
//STRIP001      aAttr.SetSurround( SURROUND_IDEAL );
//STRIP001  pSet->Put( aAttr );
//STRIP001  return aAttr.Which();
//STRIP001 }

//STRIP001 static USHORT InSWG_SwFmtVertOrient
//STRIP001 ( SwSwgReader& rPar, SfxItemSet* pSet, SwTxtNode*, xub_StrLen, xub_StrLen )
//STRIP001 {
//STRIP001  long nPos;
//STRIP001  BYTE nOrient, nRelation;
//STRIP001  rPar.r >> nPos >> nOrient >> nRelation;
//STRIP001  if( VERT_NONE == (SwVertOrient)nOrient )
//STRIP001      nRelation = FRAME;
//STRIP001  SwFmtVertOrient aAttr( (SwTwips) nPos, (SwVertOrient) nOrient,
//STRIP001                         (SwRelationOrient) nRelation );
//STRIP001  pSet->Put( aAttr );
//STRIP001  return aAttr.Which();
//STRIP001 }

//STRIP001 static USHORT InSWG_SwFmtHoriOrient
//STRIP001 ( SwSwgReader& rPar, SfxItemSet* pSet, SwTxtNode*, xub_StrLen, xub_StrLen )
//STRIP001 {
//STRIP001  long nPos;
//STRIP001  BYTE nOrient, nRelation;
//STRIP001  BYTE nAnchor;
//STRIP001  short nColumn;
//STRIP001  rPar.r >> nPos >> nOrient >> nRelation;
//STRIP001  rPar.r >> nAnchor >> nColumn;
//STRIP001  if( HORI_NONE == (SwHoriOrient)nOrient )
//STRIP001      nRelation = FRAME;
//STRIP001  SwFmtHoriOrient aAttr
//STRIP001      ( (SwTwips) nPos, (SwHoriOrient) nOrient, (SwRelationOrient) nRelation );
//STRIP001  pSet->Put( aAttr );
//STRIP001  return aAttr.Which();
//STRIP001 }

//STRIP001 static USHORT InSWG_SwFmtAnchor
//STRIP001 ( SwSwgReader& rPar, SfxItemSet* pSet, SwTxtNode*, xub_StrLen, xub_StrLen )
//STRIP001 {
//STRIP001  BYTE cType;
//STRIP001  USHORT nPage, nCol, nCntnt;
//STRIP001  rPar.r >> cType >> nPage >> nCol >> nCntnt;
//STRIP001  // auf globale Variable zuweisen:
//STRIP001  rPar.nCntntCol = (xub_StrLen)nCntnt;
//STRIP001
//STRIP001  //RndId -> AnchorId mappen weil derzeit noch altes Attributformat
//STRIP001  //gelesen und geschrieben wird.
//STRIP001  switch ( cType )
//STRIP001  {
//STRIP001      case  1: cType = FLY_PAGE;      break;
//STRIP001      case 14: cType = FLY_AT_CNTNT;  break;
//STRIP001      case 15: cType = FLY_IN_CNTNT;  break;
//STRIP001      default: ASSERT( FALSE, "ungueltige AnchorId." );
//STRIP001  }
//STRIP001
//STRIP001  SwFmtAnchor aAttr( (RndStdIds) cType, nPage + rPar.nPage1 );
//STRIP001  pSet->Put( aAttr );
//STRIP001  return aAttr.Which();
//STRIP001 }

//STRIP001 static USHORT InSWG_SwFmtBackground
//STRIP001 ( SwSwgReader& rPar, SfxItemSet* pSet, SwTxtNode*, xub_StrLen, xub_StrLen )
//STRIP001 {
//STRIP001  BYTE bActive;
//STRIP001  rPar.r >> bActive;
//STRIP001  Color aCol = rPar.InBrush();
//STRIP001  SvxBrushItem aAttr( aCol, RES_BACKGROUND );
//STRIP001  pSet->Put( aAttr );
//STRIP001  return aAttr.Which();
//STRIP001 }

/////////////////////////////// GRFATR.HXX /////////////////////////////////

//STRIP001 static USHORT InSWG_SwMirrorGrf
//STRIP001 ( SwSwgReader& rPar, SfxItemSet* pSet, SwTxtNode*, xub_StrLen, xub_StrLen )
//STRIP001 {
//STRIP001  BYTE nState;
//STRIP001  rPar.r >> nState;
//STRIP001  SwMirrorGrf aAttr( nState );
//STRIP001  pSet->Put( aAttr );
//STRIP001  return aAttr.Which();
//STRIP001 }

//STRIP001 static USHORT InSWG_SwCropGrf
//STRIP001 ( SwSwgReader& rPar, SfxItemSet* pSet, SwTxtNode*, xub_StrLen, xub_StrLen )
//STRIP001 {
//STRIP001  long top, left, right, bottom;
//STRIP001  rPar.r >> top >> left >> right >> bottom;
//STRIP001  SwCropGrf aCrop( -left, -right, -top, -bottom );
//STRIP001  pSet->Put( aCrop );
//STRIP001  return aCrop.Which();
//STRIP001 }

//////////////////////////////////////////////////////////////////////////////

//STRIP001 xub_StrLen InSWG_Nothing( SwSwgReader&, SfxItemSet*, SwTxtNode*, xub_StrLen, xub_StrLen )
//STRIP001 {
//STRIP001  return 0;
//STRIP001 }

//STRIP001 typedef USHORT ( *SwHintFn )( SwSwgReader&, SfxItemSet*, SwTxtNode*, xub_StrLen, xub_StrLen );

//STRIP001 SwHintFn __READONLY_DATA aChrInAttrs[] =
//STRIP001 {
//STRIP001 /* OLDRES_CHRATR_CASEMAP */          InSWG_SvxCaseMapItem,
//STRIP001 /* OLDRES_CHRATR_CHARWIDTH */            InSWG_Nothing,
//STRIP001 /* OLDRES_CHRATR_COLOR */                InSWG_SwColor,
//STRIP001 /* OLDRES_CHRATR_CONTOUR */          InSWG_SwContour,
//STRIP001 /* OLDRES_CHRATR_CROSSEDOUT  */          InSWG_SwCrossedOut,
//STRIP001 /* OLDRES_CHRATR_ESCAPEMENT  */          InSWG_SwEscapement,
//STRIP001 /* OLDRES_CHRATR_FONT    */              InSWG_SwFont,
//STRIP001 /* OLDRES_CHRATR_FONTSIZE    */          InSWG_SwSize,
//STRIP001 /* OLDRES_CHRATR_INVERTED    */          InSWG_Nothing,
//STRIP001 /* OLDRES_CHRATR_KERNING */          InSWG_SwKerning,
//STRIP001 /* OLDRES_CHRATR_LANGUAGE    */          InSWG_SwLanguage,
//STRIP001 /* OLDRES_CHRATR_MIRRORED    */          InSWG_Nothing,
//STRIP001 /* OLDRES_CHRATR_POSTURE */          InSWG_SvxPostureItem,
//STRIP001 /* OLDRES_CHRATR_PROPORTIONALFONTSIZE*/  InSWG_SwPropSize,
//STRIP001 /* OLDRES_CHRATR_SHADOWED    */          InSWG_SwShadowed,
//STRIP001 /* OLDRES_CHRATR_UNDERLINE */            InSWG_SwUnderline,
//STRIP001 /* OLDRES_CHRATR_WEIGHT  */              InSWG_SvxWeightItem,
//STRIP001 /* OLDRES_CHRATR_WRITINGDIRECTION    */  InSWG_Nothing,
//STRIP001 /* OLDRES_CHRATR_FIELD           */      InSWG_SwField,
//STRIP001 /* OLDRES_CHRATR_NOLINEBREAK     */  InSWG_Nothing,
//STRIP001 /* OLDRES_CHRATR_NOHYPHEN            */  InSWG_SwNoHyphenHere,
//STRIP001 /* OLDRES_CHRATR_SOFTHYPH            */  InSWG_SwSoftHyphen,
//STRIP001 /* OLDRES_CHRATR_FTN             */  InSWG_SwFtn,
//STRIP001 /* OLDRES_CHRATR_HARDBLANK           */  InSWG_SwHardBlank,
//STRIP001 };

//STRIP001 SwHintFn __READONLY_DATA aFontInAttrs[] =
//STRIP001 {
//STRIP001 /* OLDRES_TXTATR_CHARWIDTH */            InSWG_Nothing,
//STRIP001 /* OLDRES_TXTATR_COLOR */                InSWG_SwColor,
//STRIP001 /* OLDRES_TXTATR_CONTOUR */          InSWG_SwContour,
//STRIP001 /* OLDRES_TXTATR_CROSSEDOUT  */          InSWG_SwCrossedOut,
//STRIP001 /* OLDRES_TXTATR_FONT    */              InSWG_SwFont,
//STRIP001 /* OLDRES_TXTATR_FONTSIZE    */          InSWG_SwSize,
//STRIP001 /* OLDRES_TXTATR_INVERTED    */          InSWG_Nothing,
//STRIP001 /* OLDRES_TXTATR_LANGUAGE    */          InSWG_SwLanguage,
//STRIP001 /* OLDRES_TXTATR_MIRRORED    */          InSWG_Nothing,
//STRIP001 /* OLDRES_TXTATR_POSTURE */          InSWG_SvxPostureItem,
//STRIP001 /* OLDRES_TXTATR_PROPORTIONALFONTSIZE*/  InSWG_SwPropSize,
//STRIP001 /* OLDRES_TXTATR_SHADOWED    */          InSWG_SwShadowed,
//STRIP001 /* OLDRES_TXTATR_UNDERLINE */            InSWG_SwUnderline,
//STRIP001 /* OLDRES_TXTATR_WEIGHT  */              InSWG_SvxWeightItem,
//STRIP001 /* OLDRES_TXTATR_CHARFMT */          InSWG_SwCharFmt,
//STRIP001 };

//STRIP001 SwHintFn __READONLY_DATA aEtcInAttrs[] =
//STRIP001 {
//STRIP001 /* OLDRES_TXTATR_WRITINGDIRECTION    */  InSWG_Nothing,
//STRIP001 /* OLDRES_TXTATR_KERNING */          InSWG_SwKerning,
//STRIP001 /* OLDRES_TXTATR_NOLINEBREAK */      InSWG_Nothing,
//STRIP001 /* OLDRES_TXTATR_NOHYPHEN    */          InSWG_SwNoHyphenHere,
//STRIP001 /* OLDRES_TXTATR_INSERTED    */          InSWG_Nothing,
//STRIP001 /* OLDRES_TXTATR_DELETED */          InSWG_Nothing,
//STRIP001 /* OLDRES_TXTATR_ESCAPEMENT  */          InSWG_SwEscapement,
//STRIP001 /* OLDRES_TXTATR_CASEMAP */          InSWG_SvxCaseMapItem,
//STRIP001 /* OLDRES_TXTATR_FIELD */                InSWG_SwField,
//STRIP001 /* OLDRES_TXTATR_FLYCNT */               InSWG_SwFlyCnt,
//STRIP001 /* OLDRES_TXTATR_TOXMARK */          InSWG_SwTOXMark,
//STRIP001 /* OLDRES_TXTATR_SOFTHYPH            */  InSWG_SwSoftHyphen,
//STRIP001 /* OLDRES_TXTATR_FTN             */  InSWG_SwFtn,
//STRIP001 /* OLDRES_TXTATR_HARDBLANK           */  InSWG_SwHardBlank,
//STRIP001 /* OLDRES_TXTATR_REFMARK         */  InSWG_SwRefMark,
//STRIP001 };


//STRIP001 static SwHintFn __READONLY_DATA aParInAttrs[] =
//STRIP001 {
//STRIP001 /* OLDRES_PARATR_LINESPACING */      InSWG_SwLineSpacing,
//STRIP001 /* OLDRES_PARATR_FIRSTLINEOFFSET */  InSWG_Nothing,      // nicht mehr da
//STRIP001 /* OLDRES_PARATR_ADJUST  */              InSWG_SwAdjust,
//STRIP001 /* OLDRES_PARATR_SPLIT       */          InSWG_SwSplit,
//STRIP001 /* OLDRES_PARATR_WIDOWS  */              InSWG_SwWidows,
//STRIP001 /* OLDRES_PARATR_ORPHANS */          InSWG_SwOrphans,
//STRIP001 /* OLDRES_PARATR_TABSTOP */          InSWG_SwTabStop,
//STRIP001 /* OLDRES_PARATR_HYPHENZONE */           InSWG_SwHyphenZone,
//STRIP001 /* OLDRES_PARATR_DROP       */           InSWG_SwDropCaps,
//STRIP001 };

//STRIP001 static SwHintFn __READONLY_DATA aAddInAttrs[] =
//STRIP001 {
//STRIP001 /* OLDRES_ADD_POSTIT */              InSWG_Nothing,
//STRIP001 /* OLDRES_ADD_INSERTS    */              InSWG_Nothing,
//STRIP001 /* OLDRES_ADD_AUTOTEXT */                InSWG_Nothing,
//STRIP001 /* OLDRES_ADD_OTHERCONTENT */            InSWG_Nothing,
//STRIP001 };

//STRIP001 static SwHintFn __READONLY_DATA aFrmInAttrs[] =
//STRIP001 {
//STRIP001 /* OLDRES_FILL_ORDER */              InSWG_SwFmtFillOrder,
//STRIP001 /* OLDRES_FRM_SIZE */                    InSWG_SwFmtFrmSize,
//STRIP001 /* OLDRES_PAGE_BREAK */                  InSWG_SwPageBreak,
//STRIP001 /* OLDRES_SEL_PAGE */                    InSWG_Nothing,
//STRIP001 /* OLDRES_PAPER_TRAY */              InSWG_SwFmtPaperBin,
//STRIP001 /* OLDRES_FRM_RNDREQUEST */              InSWG_Nothing,
//STRIP001 /* OLDRES_FRM_RNDSUPPLY */               InSWG_Nothing,
//STRIP001 /* OLDRES_LR_SPACE */                    InSWG_SwLRSpace,
//STRIP001 /* OLDRES_UL_SPACE */                    InSWG_SwULSpace,
//STRIP001 /* OLDRES_CNTNT */                       InSWG_SwFmtCntnt,
//STRIP001 /* OLDRES_HEADER */                      InSWG_SwFmtHeader,
//STRIP001 /* OLDRES_FOOTER */                      InSWG_SwFmtFooter,
//STRIP001 /* OLDRES_FLY_PRINT */                   InSWG_SwFmtPrint,
//STRIP001 /* OLDRES_FLY_OPAQUE */                  InSWG_SwFmtOpaque,
//STRIP001 /* OLDRES_FLY_PROTECT */             InSWG_SwFmtProtect,
//STRIP001 /* OLDRES_FLY_MAINCNTNT */               InSWG_SwFmtSurround,
//STRIP001 /* OLDRES_FLY_VERT_ORIENT */         InSWG_SwFmtVertOrient,
//STRIP001 /* OLDRES_FLY_HORI_ORIENT */         InSWG_SwFmtHoriOrient,
//STRIP001 /* OLDRES_FLY_GENERIC */             InSWG_Nothing,
//STRIP001 /* OLDRES_FLY_ANCHOR */                  InSWG_SwFmtAnchor,
//STRIP001 /* OLDRES_BACKGROUND */                  InSWG_SwFmtBackground,
//STRIP001 /* OLDRES_BOX    */                      InSWG_SwBox,
//STRIP001 /* OLDRES_SHADOW */                      InSWG_SwFmtShadow,
//STRIP001 /* OLDRES_PAGEDESC */                    InSWG_SwFmtPageDesc,
//STRIP001 /* OLDRES_FRMMACRO */                    InSWG_SwFmtMacro,
//STRIP001 /* OLDRES_COL_BREAK */                   InSWG_SwColBreak,
//STRIP001 /* OLDRES_COL */                     InSWG_SwFmtCol
//STRIP001 };

//STRIP001 static SwHintFn __READONLY_DATA aGrfInAttrs[] =
//STRIP001 {
//STRIP001 /* OLDRES_GRFATR_GRFSIZE */          InSWG_Nothing,
//STRIP001 /* OLDRES_GRFATR_MIRRORGRF */            InSWG_SwMirrorGrf,
//STRIP001 /* OLDRES_GRFATR_GRFOFFSET */            InSWG_Nothing,
//STRIP001 /* OLDRES_GRFATR_ALIGNGRF    */          InSWG_Nothing,
//STRIP001 /* OLDRES_GRFATR_CROPGRF */          InSWG_SwCropGrf
//STRIP001 };

//STRIP001 #if defined GCC || defined HPUX
//STRIP001 struct HintFns
//STRIP001 #else
//STRIP001 static struct HintFns
//STRIP001 #endif
//STRIP001 {
//STRIP001  const SwHintFn* pHintTab;
//STRIP001  short     nHintId1;
//STRIP001 }
//STRIP001 #if defined GCC || defined HPUX
//STRIP001 ;
//STRIP001 static __READONLY_DATA HintFns aHintFns[] =
//STRIP001 #else
//STRIP001 __READONLY_DATA aHintFns[] =
//STRIP001 #endif
//STRIP001 {
//STRIP001  { aChrInAttrs,  OLDRES_CHRATR_BEGIN },
//STRIP001  { aFontInAttrs, OLDFONT_TXTATR_BEGIN},
//STRIP001  { aEtcInAttrs,  OLDETC_TXTATR_BEGIN },
//STRIP001  { aParInAttrs,  OLDRES_PARATR_BEGIN },
//STRIP001  { aAddInAttrs,  OLDRES_ADD_BEGIN    },
//STRIP001  { aFrmInAttrs,  OLDRES_FRMATR_BEGIN },
//STRIP001  { aGrfInAttrs,  OLDRES_GRFATR_BEGIN }

//STRIP001 };

//STRIP001 static USHORT __READONLY_DATA nAttrSizes[] =
//STRIP001 {
//STRIP001  OLDRES_CHRATR_END + 1 - OLDRES_CHRATR_BEGIN,
//STRIP001  OLDFONT_TXTATR_END - OLDFONT_TXTATR_BEGIN,
//STRIP001  OLDETC_TXTATR_END - OLDETC_TXTATR_BEGIN,
//STRIP001  OLDRES_PARATR_END - OLDRES_PARATR_BEGIN,
//STRIP001  OLDRES_ADD_END - OLDRES_ADD_BEGIN,
//STRIP001  OLDRES_FRMATR_END - OLDRES_FRMATR_BEGIN,
//STRIP001  OLDRES_GRFATR_END - OLDRES_GRFATR_BEGIN
//STRIP001 };

// Einlesen eines Format-Hints in ein Format
// Der Returnwert ist das Which-ID des eingelesenen Hints oder 0

//STRIP001 USHORT SwSwgReader::InHint( SfxItemSet& rSet )
//STRIP001 {
//STRIP001  USHORT nId = r.cur();
//STRIP001  long nextrec = r.getskip();
//STRIP001  SwHintFn pFn = NULL;
//STRIP001
//STRIP001  for( short i = 6; i >= 0; i-- )
//STRIP001  {
//STRIP001      USHORT id1 = aHdr.cAttrTab[ i ];
//STRIP001      if( nId >= id1 )
//STRIP001      {
//STRIP001          nId -= id1;
//STRIP001          // Ausserhalb des Bereiches?
//STRIP001          if( nId >= aHdr.cAttrSiz[ i ] ) {
//STRIP001              Error(); return 0;
//STRIP001          }
//STRIP001          // Interpretierbar?
//STRIP001          if( nId < nAttrSizes[ i ] )
//STRIP001              pFn = aHintFns[ i ].pHintTab[ nId ];
//STRIP001          break;
//STRIP001      }
//STRIP001  }
//STRIP001  USHORT nWhich = 0;
//STRIP001  if( pFn )
//STRIP001      nWhich =  (*pFn) ( *this, &rSet, NULL, 0, 0 );
//STRIP001  // Vorsicht! Der Fussnoten-Hint ist erst zum Teil geparst!!
//STRIP001  if( nWhich != RES_TXTATR_FTN )
//STRIP001      r.skip( nextrec );
//STRIP001  return nWhich;
//STRIP001 }

// Einen Text-Hint einlesen und anfuegen. Der Which-ID oder
// 0 wird returned.

//STRIP001 USHORT SwSwgReader::InHint( SwTxtNode& rNd, xub_StrLen nBeg, xub_StrLen nEnd )
//STRIP001 {
//STRIP001  USHORT nId = r.cur();
//STRIP001  long nextrec = r.getskip();
//STRIP001  SwHintFn pFn = NULL;
//STRIP001
//STRIP001  for( short i = 6; i >= 0; i-- )
//STRIP001  {
//STRIP001      USHORT id1 = aHdr.cAttrTab[ i ];
//STRIP001      if( nId >= id1 )
//STRIP001      {
//STRIP001          nId -= id1;
//STRIP001          // Ausserhalb des Bereiches?
//STRIP001          if( nId >= aHdr.cAttrSiz[ i ] ) {
//STRIP001              Error(); return 0;
//STRIP001          }
//STRIP001          // Interpretierbar?
//STRIP001          if( nId < nAttrSizes[ i ] )
//STRIP001              pFn = aHintFns[ i ].pHintTab[ nId ];
//STRIP001          break;
//STRIP001      }
//STRIP001  }
//STRIP001  USHORT nWhich = 0;
//STRIP001  if( pFn )
//STRIP001      nWhich = (*pFn) ( *this, NULL, &rNd, nBeg, nEnd );
//STRIP001  // Vorsicht! Der Fussnoten-Hint ist erst zum Teil geparst!!
//STRIP001  if( nWhich != RES_TXTATR_FTN )
//STRIP001      r.skip( nextrec );
//STRIP001  return nWhich;
//STRIP001 }



