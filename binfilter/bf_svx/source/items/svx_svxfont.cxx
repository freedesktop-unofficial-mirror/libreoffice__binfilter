/*************************************************************************
 *
 *  $RCSfile: svx_svxfont.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:45:15 $
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

// include ----------------------------------------------------------------

#ifndef _OUTDEV_HXX //autogen
#include <vcl/outdev.hxx>
#endif
#ifndef _PRINT_HXX //autogen
#include <vcl/print.hxx>
#endif
#ifndef _SV_POLY_HXX //autogen
#include <vcl/poly.hxx>
#endif
#ifndef _UNOTOOLS_CHARCLASS_HXX
#include <unotools/charclass.hxx>
#endif
#ifndef _UNO_LINGU_HXX
#include <unolingu.hxx>
#endif
#ifndef _COM_SUN_STAR_I18N_KCHARACTERTYPE_HPP_
#include <com/sun/star/i18n/KCharacterType.hpp>
#endif
#pragma hdrstop

#define ITEMID_ESCAPEMENT   0

#define _SVX_SVXFONT_CXX

#include "svxfont.hxx"
#include "escpitem.hxx"
namespace binfilter {

// Minimum: Prozentwert fuers kernen
#define MINKERNPERCENT 5

// prop. Groesse der Kleinbuchstaben bei Kapitaelchen
#define KAPITAELCHENPROP 66

#ifndef REDUCEDSVXFONT
    const sal_Unicode CH_BLANK = sal_Unicode(' ');      // ' ' Leerzeichen
    static sal_Char __READONLY_DATA sDoubleSpace[] = "  ";
#endif

/*************************************************************************
 *                      class SvxFont
 *************************************************************************/

/*N*/ SvxFont::SvxFont()
/*N*/ {
/*N*/   nKern = nEsc = 0;
/*N*/   nPropr = 100;
/*N*/   eCaseMap = SVX_CASEMAP_NOT_MAPPED;
/*N*/   eLang = LANGUAGE_SYSTEM;
/*N*/ }

/*N*/ SvxFont::SvxFont( const Font &rFont )
/*N*/   : Font( rFont )
/*N*/ {
/*N*/   nKern = nEsc = 0;
/*N*/   nPropr = 100;
/*N*/   eCaseMap = SVX_CASEMAP_NOT_MAPPED;
/*N*/   eLang = LANGUAGE_SYSTEM;
/*N*/ }

/*************************************************************************
 *                      class SvxFont: Copy-Ctor
 *************************************************************************/

/*N*/ SvxFont::SvxFont( const SvxFont &rFont )
/*N*/   : Font( rFont )
/*N*/ {
/*N*/   nKern = rFont.GetFixKerning();
/*N*/   nEsc  = rFont.GetEscapement();
/*N*/   nPropr = rFont.GetPropr();
/*N*/   eCaseMap = rFont.GetCaseMap();
/*N*/   eLang = rFont.GetLanguage();
/*N*/ }

/*************************************************************************
 *               static SvxFont::DrawArrow
 *************************************************************************/

//STRIP001 void SvxFont::DrawArrow( OutputDevice &rOut, const Rectangle& rRect,
//STRIP001  const Size& rSize, const Color& rCol, BOOL bLeft )
//STRIP001 {
//STRIP001  long nLeft = ( rRect.Left() + rRect.Right() - rSize.Width() )/ 2;
//STRIP001  long nRight = nLeft + rSize.Width();
//STRIP001  long nMid = ( rRect.Top() + rRect.Bottom() ) / 2;
//STRIP001  long nTop = nMid - rSize.Height() / 2;
//STRIP001  long nBottom = nTop + rSize.Height();
//STRIP001  if( nLeft < rRect.Left() )
//STRIP001  {
//STRIP001      nLeft = rRect.Left();
//STRIP001      nRight = rRect.Right();
//STRIP001  }
//STRIP001  if( nTop < rRect.Top() )
//STRIP001  {
//STRIP001      nTop = rRect.Top();
//STRIP001      nBottom = rRect.Bottom();
//STRIP001  }
//STRIP001  Polygon aPoly;
//STRIP001  Point aTmp( bLeft ? nLeft : nRight, nMid );
//STRIP001  Point aNxt( bLeft ? nRight : nLeft, nTop );
//STRIP001  aPoly.Insert( 0, aTmp );
//STRIP001  aPoly.Insert( 0, aNxt );
//STRIP001  aNxt.Y() = nBottom;
//STRIP001  aPoly.Insert( 0, aNxt );
//STRIP001  aPoly.Insert( 0, aTmp );
//STRIP001  Color aOldLineColor = rOut.GetLineColor();
//STRIP001  Color aOldFillColor = rOut.GetFillColor();
//STRIP001  rOut.SetFillColor( rCol );
//STRIP001  rOut.SetLineColor( Color( COL_BLACK ) );
//STRIP001  rOut.DrawPolygon( aPoly );
//STRIP001  rOut.DrawLine( aTmp, aNxt );
//STRIP001  rOut.SetLineColor( aOldLineColor );
//STRIP001  rOut.SetFillColor( aOldFillColor );
//STRIP001 }

/*************************************************************************
 *                      SvxFont::CalcCaseMap
 *************************************************************************/

/*N*/ XubString SvxFont::CalcCaseMap( const XubString &rTxt ) const
/*N*/ {
/*N*/   if( !IsCaseMap() || !rTxt.Len() ) return rTxt;
/*N*/   XubString aTxt( rTxt );
/*N*/   // Ich muss mir noch die Sprache besorgen
/*N*/   const LanguageType eLng = LANGUAGE_DONTKNOW == eLang
/*N*/                           ? LANGUAGE_SYSTEM : eLang;
/*N*/
/*N*/   CharClass aCharClass( SvxCreateLocale( eLng ) );
/*N*/
/*N*/   switch( eCaseMap )
/*N*/   {
/*N*/       case SVX_CASEMAP_KAPITAELCHEN:
/*N*/       case SVX_CASEMAP_VERSALIEN:
/*N*/       {
/*N*/           aCharClass.toUpper( aTxt );
/*N*/           break;
/*N*/       }
/*N*/
/*N*/       case SVX_CASEMAP_GEMEINE:
/*N*/       {
/*?*/           aCharClass.toLower( aTxt );
/*?*/           break;
/*?*/       }
/*?*/       case SVX_CASEMAP_TITEL:
/*?*/       {
/*?*/           // Jeder Wortbeginn wird gross geschrieben,
/*?*/           // der Rest des Wortes wird unbesehen uebernommen.
/*?*/           // Bug: wenn das Attribut mitten im Wort beginnt.
/*?*/           BOOL bBlank = TRUE;
/*?*/
/*?*/           for( UINT32 i = 0; i < aTxt.Len(); ++i )
/*?*/           {
/*?*/               if( sal_Unicode(' ') == aTxt.GetChar(i) || sal_Unicode('\t') == aTxt.GetChar(i) )
/*?*/                   bBlank = TRUE;
/*?*/               else
/*?*/               {
/*?*/                   if( bBlank )
/*?*/                   {
/*?*/                       String aTemp( aTxt.GetChar( i ) );
/*?*/                       aCharClass.toUpper( aTemp );
/*?*/                       aTxt.Replace( i, 1, aTemp );
/*?*/                   }
/*?*/                   bBlank = FALSE;
/*?*/               }
/*?*/           }
/*?*/           break;
/*?*/       }
/*?*/       default:
/*?*/       {
/*?*/           DBG_ASSERT(!this, "SvxFont::CaseMapTxt: unknown casemap");
/*N*/           break;
/*N*/       }
/*N*/   }
/*N*/   return aTxt;
/*N*/ }

/*************************************************************************
 * Hier beginnen die Methoden, die im Writer nicht benutzt werden koennen,
 * deshalb kann man diesen Bereich durch setzen von REDUCEDSVXFONT ausklammern.
 *************************************************************************/
#ifndef REDUCEDSVXFONT

/*************************************************************************
 *                      class SvxDoCapitals
 * die virtuelle Methode Do wird von SvxFont::DoOnCapitals abwechselnd mit
 * den "Gross-" und "Kleinbuchstaben"-Teilen aufgerufen.
 * Die Ableitungen von SvxDoCapitals erfuellen diese Methode mit Leben.
 *************************************************************************/

class SvxDoCapitals
{
protected:
    OutputDevice *pOut;
    const XubString &rTxt;
    const xub_StrLen nIdx;
    const xub_StrLen nLen;

public:
    SvxDoCapitals( OutputDevice *pOut, const XubString &rTxt,
                   const xub_StrLen nIdx, const xub_StrLen nLen )
        : pOut(pOut), rTxt(rTxt), nIdx(nIdx), nLen(nLen)
        { }

//STRIP001  virtual void DoSpace( const BOOL bDraw );
//STRIP001  virtual void SetSpace();
//STRIP001  virtual void Do( const XubString &rTxt,
//STRIP001                   const xub_StrLen nIdx, const xub_StrLen nLen,
//STRIP001                   const BOOL bUpper ) = 0;

    inline OutputDevice *GetOut() { return pOut; }
    inline const XubString &GetTxt() const { return rTxt; }
    inline const xub_StrLen GetIdx() const { return nIdx; }
    inline const xub_StrLen GetLen() const { return nLen; }
};

//STRIP001 void SvxDoCapitals::DoSpace( const BOOL bDraw ) { }

//STRIP001 void SvxDoCapitals::SetSpace() { }

//STRIP001 void SvxDoCapitals::Do( const XubString &rTxt, const xub_StrLen nIdx,
//STRIP001  const xub_StrLen nLen, const BOOL bUpper ) { }

/*************************************************************************
 *                  SvxFont::DoOnCapitals() const
 * zerlegt den String in Gross- und Kleinbuchstaben und ruft jeweils die
 * Methode SvxDoCapitals::Do( ) auf.
 *************************************************************************/

//STRIP001 void SvxFont::DoOnCapitals(SvxDoCapitals &rDo, const xub_StrLen nPartLen) const
//STRIP001 {
//STRIP001  OutputDevice *pOut = rDo.GetOut();
//STRIP001  const XubString &rTxt = rDo.GetTxt();
//STRIP001  const xub_StrLen nIdx = rDo.GetIdx();
//STRIP001  const xub_StrLen nLen = STRING_LEN == nPartLen ? rDo.GetLen() : nPartLen;
//STRIP001
//STRIP001  const XubString aTxt( CalcCaseMap( rTxt ) );
//STRIP001  const USHORT nTxtLen = Min( rTxt.Len(), nLen );
//STRIP001  USHORT nPos = 0;
//STRIP001  USHORT nOldPos = nPos;
//STRIP001
//STRIP001  // #108210#
//STRIP001  // Test if string length differ between original and CaseMapped
//STRIP001  sal_Bool bCaseMapLengthDiffers(aTxt.Len() != rTxt.Len());
//STRIP001
//STRIP001  const LanguageType eLng = LANGUAGE_DONTKNOW == eLang
//STRIP001                          ? LANGUAGE_SYSTEM : eLang;
//STRIP001
//STRIP001  CharClass   aCharClass( SvxCreateLocale( eLng ) );
//STRIP001  String      aCharString;
//STRIP001
//STRIP001  while( nPos < nTxtLen )
//STRIP001  {
//STRIP001      // Erst kommen die Upper-Chars dran
//STRIP001
//STRIP001      // 4251: Es gibt Zeichen, die Upper _und_ Lower sind (z.B. das Blank).
//STRIP001      // Solche Zweideutigkeiten fuehren ins Chaos, deswegen werden diese
//STRIP001      // Zeichen der Menge Lower zugeordnet !
//STRIP001
//STRIP001      while( nPos < nTxtLen )
//STRIP001      {
//STRIP001          aCharString = rTxt.GetChar( nPos + nIdx );
//STRIP001          sal_Int32 nCharacterType = aCharClass.getCharacterType( aCharString, 0 );
//STRIP001          if ( nCharacterType & ::com::sun::star::i18n::KCharacterType::LOWER )
//STRIP001              break;
//STRIP001          if ( ! ( nCharacterType & ::com::sun::star::i18n::KCharacterType::UPPER ) )
//STRIP001              break;
//STRIP001          ++nPos;
//STRIP001      }
//STRIP001      if( nOldPos != nPos )
//STRIP001      {
//STRIP001          if(bCaseMapLengthDiffers)
//STRIP001          {
//STRIP001              // #108210#
//STRIP001              // If strings differ work preparing the necessary snippet to address that
//STRIP001              // potential difference
//STRIP001              const XubString aSnippet(rTxt, nIdx + nOldPos, nPos-nOldPos);
//STRIP001              XubString aNewText = CalcCaseMap(aSnippet);
//STRIP001
//STRIP001              rDo.Do( aNewText, 0, aNewText.Len(), TRUE );
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              rDo.Do( aTxt, nIdx + nOldPos, nPos-nOldPos, TRUE );
//STRIP001          }
//STRIP001
//STRIP001          nOldPos = nPos;
//STRIP001      }
//STRIP001      // Nun werden die Lower-Chars verarbeitet (ohne Blanks)
//STRIP001      while( nPos < nTxtLen )
//STRIP001      {
//STRIP001          sal_uInt32  nCharacterType = aCharClass.getCharacterType( aCharString, 0 );
//STRIP001          if ( ( nCharacterType & ::com::sun::star::i18n::KCharacterType::UPPER ) )
//STRIP001              break;
//STRIP001          if ( CH_BLANK == aCharString )
//STRIP001              break;
//STRIP001          if( ++nPos < nTxtLen )
//STRIP001              aCharString = rTxt.GetChar( nPos + nIdx );
//STRIP001      }
//STRIP001      if( nOldPos != nPos )
//STRIP001      {
//STRIP001          if(bCaseMapLengthDiffers)
//STRIP001          {
//STRIP001              // #108210#
//STRIP001              // If strings differ work preparing the necessary snippet to address that
//STRIP001              // potential difference
//STRIP001              const XubString aSnippet(rTxt, nIdx + nOldPos, nPos - nOldPos);
//STRIP001              XubString aNewText = CalcCaseMap(aSnippet);
//STRIP001
//STRIP001              rDo.Do( aNewText, 0, aNewText.Len(), FALSE );
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              rDo.Do( aTxt, nIdx + nOldPos, nPos-nOldPos, FALSE );
//STRIP001          }
//STRIP001
//STRIP001          nOldPos = nPos;
//STRIP001      }
//STRIP001      // Nun werden die Blanks verarbeitet
//STRIP001      while( nPos < nTxtLen && CH_BLANK == aCharString && ++nPos < nTxtLen )
//STRIP001          aCharString = rTxt.GetChar( nPos + nIdx );
//STRIP001
//STRIP001      if( nOldPos != nPos )
//STRIP001      {
//STRIP001          rDo.DoSpace( FALSE );
//STRIP001
//STRIP001          if(bCaseMapLengthDiffers)
//STRIP001          {
//STRIP001              // #108210#
//STRIP001              // If strings differ work preparing the necessary snippet to address that
//STRIP001              // potential difference
//STRIP001              const XubString aSnippet(rTxt, nIdx + nOldPos, nPos - nOldPos);
//STRIP001              XubString aNewText = CalcCaseMap(aSnippet);
//STRIP001
//STRIP001              rDo.Do( aNewText, 0, aNewText.Len(), FALSE );
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              rDo.Do( aTxt, nIdx + nOldPos, nPos - nOldPos, FALSE );
//STRIP001          }
//STRIP001
//STRIP001          nOldPos = nPos;
//STRIP001          rDo.SetSpace();
//STRIP001      }
//STRIP001  }
//STRIP001  rDo.DoSpace( TRUE );
//STRIP001 }

/**************************************************************************
 *                    SvxFont::SetPhysFont()
 *************************************************************************/

/*N*/ void SvxFont::SetPhysFont( OutputDevice *pOut ) const
/*N*/ {
/*N*/   const Font& rCurrentFont = pOut->GetFont();
/*N*/   if ( nPropr == 100 )
/*N*/   {
/*N*/       if ( !rCurrentFont.IsSameInstance( *this ) )
/*N*/           pOut->SetFont( *this );
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       Font aNewFont( *this );
/*N*/       Size aSize( aNewFont.GetSize() );
/*N*/       aNewFont.SetSize( Size( aSize.Width() * nPropr / 100L,
/*N*/                                   aSize.Height() * nPropr / 100L ) );
/*N*/       if ( !rCurrentFont.IsSameInstance( aNewFont ) )
/*N*/           pOut->SetFont( aNewFont );
/*N*/   }
/*N*/ }

/*************************************************************************
 *                    SvxFont::ChgPhysFont()
 *************************************************************************/

//STRIP001 Font SvxFont::ChgPhysFont( OutputDevice *pOut ) const
//STRIP001 {
//STRIP001  Font aOldFont( pOut->GetFont() );
//STRIP001  SetPhysFont( pOut );
//STRIP001  return aOldFont;
//STRIP001 }

/*************************************************************************
 *                    SvxFont::GetPhysTxtSize()
 *************************************************************************/

//STRIP001 Size SvxFont::GetPhysTxtSize( const OutputDevice *pOut, const XubString &rTxt,
//STRIP001                       const xub_StrLen nIdx, const xub_StrLen nLen ) const
//STRIP001 {
//STRIP001  if ( !IsCaseMap() && !IsKern() )
//STRIP001      return Size( pOut->GetTextWidth( rTxt, nIdx, nLen ),
//STRIP001                   pOut->GetTextHeight() );
//STRIP001
//STRIP001  Size aTxtSize;
//STRIP001  aTxtSize.setHeight( pOut->GetTextHeight() );
//STRIP001  if ( !IsCaseMap() )
//STRIP001      aTxtSize.setWidth( pOut->GetTextWidth( rTxt, nIdx, nLen ) );
//STRIP001  else
//STRIP001  {
//STRIP001      // #108210#
//STRIP001      const XubString aNewText = CalcCaseMap(rTxt);
//STRIP001      sal_Bool bCaseMapLengthDiffers(aNewText.Len() != rTxt.Len());
//STRIP001      sal_Int32 nWidth(0L);
//STRIP001
//STRIP001      if(bCaseMapLengthDiffers)
//STRIP001      {
//STRIP001          // If strings differ work preparing the necessary snippet to address that
//STRIP001          // potential difference
//STRIP001          const XubString aSnippet(rTxt, nIdx, nLen);
//STRIP001          XubString aNewText = CalcCaseMap(aSnippet);
//STRIP001          nWidth = pOut->GetTextWidth( aNewText, 0, aNewText.Len() );
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          nWidth = pOut->GetTextWidth( aNewText, nIdx, nLen );
//STRIP001      }
//STRIP001
//STRIP001      aTxtSize.setWidth(nWidth);
//STRIP001  }
//STRIP001
//STRIP001  if( IsKern() && ( nLen > 1 ) )
//STRIP001      aTxtSize.Width() += ( ( nLen-1 ) * long( nKern ) );
//STRIP001
//STRIP001  return aTxtSize;
//STRIP001 }

/*N*/ Size SvxFont::GetPhysTxtSize( const OutputDevice *pOut, const XubString &rTxt )
/*N*/ {
/*N*/   if ( !IsCaseMap() && !IsKern() )
/*N*/       return Size( pOut->GetTextWidth( rTxt ), pOut->GetTextHeight() );
/*N*/
/*?*/   Size aTxtSize;
/*?*/   aTxtSize.setHeight( pOut->GetTextHeight() );
/*?*/   if ( !IsCaseMap() )
/*?*/       aTxtSize.setWidth( pOut->GetTextWidth( rTxt ) );
/*?*/   else
/*?*/       aTxtSize.setWidth( pOut->GetTextWidth( CalcCaseMap( rTxt ) ) );
/*?*/
/*?*/   if( IsKern() && ( rTxt.Len() > 1 ) )
/*?*/       aTxtSize.Width() += ( ( rTxt.Len()-1 ) * long( nKern ) );
/*?*/
/*?*/   return aTxtSize;
/*N*/ }

/*N*/ Size SvxFont::QuickGetTextSize( const OutputDevice *pOut, const XubString &rTxt,
/*N*/                        const USHORT nIdx, const USHORT nLen, long* pDXArray ) const
/*N*/ {
/*N*/   if ( !IsCaseMap() && !IsKern() )
/*N*/       return Size( pOut->GetTextArray( rTxt, pDXArray, nIdx, nLen ),
/*N*/                    pOut->GetTextHeight() );
/*N*/
/*N*/   Size aTxtSize;
/*N*/   aTxtSize.setHeight( pOut->GetTextHeight() );
/*N*/   if ( !IsCaseMap() )
/*N*/       aTxtSize.setWidth( pOut->GetTextArray( rTxt, pDXArray, nIdx, nLen ) );
/*N*/   else
/*?*/       aTxtSize.setWidth( pOut->GetTextArray( CalcCaseMap( rTxt ),
/*?*/                          pDXArray, nIdx, nLen ) );
/*N*/
/*N*/   if( IsKern() && ( nLen > 1 ) )
/*N*/   {
/*N*/       aTxtSize.Width() += ( ( nLen-1 ) * long( nKern ) );
/*N*/
/*N*/       if ( pDXArray )
/*N*/       {
/*N*/           for ( xub_StrLen i = 0; i < nLen; i++ )
/*N*/               pDXArray[i] += ( (i+1) * long( nKern ) );
/*N*/           // Der letzte ist um ein nKern zu gross:
/*N*/           pDXArray[nLen-1] -= nKern;
/*N*/       }
/*N*/   }
/*N*/   return aTxtSize;
/*N*/ }

/*************************************************************************
 *                    SvxFont::GetTxtSize()
 *************************************************************************/

//STRIP001 Size SvxFont::GetTxtSize( const OutputDevice *pOut, const XubString &rTxt,
//STRIP001                       const xub_StrLen nIdx, const xub_StrLen nLen )
//STRIP001 {
//STRIP001  xub_StrLen nTmp = nLen;
//STRIP001  if ( nTmp == STRING_LEN )   // schon initialisiert?
//STRIP001      nTmp = rTxt.Len();
//STRIP001  Font aOldFont( ChgPhysFont((OutputDevice *)pOut) );
//STRIP001  Size aTxtSize;
//STRIP001  if( IsCapital() && rTxt.Len() )
//STRIP001  {
//STRIP001      aTxtSize = GetCapitalSize( pOut, rTxt, nIdx, nTmp );
//STRIP001  }
//STRIP001  else aTxtSize = GetPhysTxtSize(pOut,rTxt,nIdx,nTmp);
//STRIP001  ((OutputDevice *)pOut)->SetFont( aOldFont );
//STRIP001  return aTxtSize;
//STRIP001 }

/*************************************************************************
 *                    SvxFont::DrawText()
 *************************************************************************/

//STRIP001 void SvxFont::DrawText( OutputDevice *pOut,
//STRIP001             const Point &rPos, const XubString &rTxt,
//STRIP001             const xub_StrLen nIdx, const xub_StrLen nLen ) const
//STRIP001 {
//STRIP001  if( !nLen || !rTxt.Len() )  return;
//STRIP001  xub_StrLen nTmp = nLen;
//STRIP001  if ( nTmp == STRING_LEN )   // schon initialisiert?
//STRIP001      nTmp = rTxt.Len();
//STRIP001  Point aPos( rPos );
//STRIP001  if ( nEsc )
//STRIP001  {
//STRIP001      Size aSize = (this->GetSize());
//STRIP001      aPos.Y() -= ((nEsc*long(aSize.Height()))/ 100L);
//STRIP001  }
//STRIP001  Font aOldFont( ChgPhysFont( pOut ) );
//STRIP001
//STRIP001  if ( IsCapital() )
//STRIP001      DrawCapital( pOut, aPos, rTxt, nIdx, nTmp );
//STRIP001  else
//STRIP001  {
//STRIP001      Size aSize = GetPhysTxtSize( pOut, rTxt, nIdx, nTmp );
//STRIP001
//STRIP001      if ( !IsCaseMap() )
//STRIP001          pOut->DrawStretchText( aPos, aSize.Width(), rTxt, nIdx, nTmp );
//STRIP001      else
//STRIP001          pOut->DrawStretchText( aPos, aSize.Width(), CalcCaseMap( rTxt ),
//STRIP001                                 nIdx, nTmp );
//STRIP001  }
//STRIP001  pOut->SetFont(aOldFont);
//STRIP001 }

/*N*/ void SvxFont::QuickDrawText( OutputDevice *pOut,
/*N*/   const Point &rPos, const XubString &rTxt,
/*N*/   const xub_StrLen nIdx, const xub_StrLen nLen, const long* pDXArray ) const
/*N*/ {
/*N*/   // Font muss ins OutputDevice selektiert sein...
/*N*/   if ( !IsCaseMap() && !IsCapital() && !IsKern() && !IsEsc() )
/*N*/   {
/*N*/       pOut->DrawTextArray( rPos, rTxt, pDXArray, nIdx, nLen );
/*N*/       return;
/*N*/   }
/*N*/
/*?*/   Point aPos( rPos );
/*?*/
/*?*/     if ( nEsc )
/*?*/     {
/*?*/         long nDiff = GetSize().Height();
/*?*/         nDiff *= nEsc;
/*?*/         nDiff /= 100;
/*?*/
/*?*/         if ( !IsVertical() )
/*?*/           aPos.Y() -= nDiff;
/*?*/         else
/*?*/             aPos.X() += nDiff;
/*?*/     }
/*?*/
/*?*/   if( IsCapital() )
/*?*/   {
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001 /*?*/        DBG_ASSERT( !pDXArray, "DrawCapital nicht fuer TextArray!" );
//STRIP001 /*?*/        DrawCapital( pOut, aPos, rTxt, nIdx, nLen );
/*?*/   }
/*?*/   else
/*?*/   {
/*?*/       if ( IsKern() && !pDXArray )
/*?*/       {
/*?*/           DBG_ASSERT(0, "STRIP"); //STRIP001 /*?*/            Size aSize = GetPhysTxtSize( pOut, rTxt, nIdx, nLen );
//STRIP001 /*?*/
//STRIP001 /*?*/            if ( !IsCaseMap() )
//STRIP001 /*?*/                pOut->DrawStretchText( aPos, aSize.Width(), rTxt, nIdx, nLen );
//STRIP001 /*?*/            else
//STRIP001 /*?*/                pOut->DrawStretchText( aPos, aSize.Width(), CalcCaseMap( rTxt ), nIdx, nLen );
/*?*/       }
/*?*/       else
/*?*/       {
/*?*/           if ( !IsCaseMap() )
/*?*/               pOut->DrawTextArray( aPos, rTxt, pDXArray, nIdx, nLen );
/*?*/           else
/*?*/               pOut->DrawTextArray( aPos, CalcCaseMap( rTxt ), pDXArray, nIdx, nLen );
/*?*/       }
/*?*/   }
/*N*/ }

// -----------------------------------------------------------------------

//STRIP001 void SvxFont::DrawPrev( OutputDevice *pOut, Printer* pPrinter,
//STRIP001                      const Point &rPos, const XubString &rTxt,
//STRIP001                      const xub_StrLen nIdx, const xub_StrLen nLen ) const
//STRIP001 {
//STRIP001  if ( !nLen || !rTxt.Len() )
//STRIP001      return;
//STRIP001  xub_StrLen nTmp = nLen;
//STRIP001
//STRIP001  if ( nTmp == STRING_LEN )   // schon initialisiert?
//STRIP001      nTmp = rTxt.Len();
//STRIP001  Point aPos( rPos );
//STRIP001
//STRIP001  if ( nEsc )
//STRIP001  {
//STRIP001      short nTmpEsc;
//STRIP001      if( DFLT_ESC_AUTO_SUPER == nEsc )
//STRIP001          nTmpEsc = 33;
//STRIP001      else if( DFLT_ESC_AUTO_SUB == nEsc )
//STRIP001          nTmpEsc = -20;
//STRIP001      else
//STRIP001          nTmpEsc = nEsc;
//STRIP001      Size aSize = ( this->GetSize() );
//STRIP001      aPos.Y() -= ( ( nTmpEsc * long( aSize.Height() ) ) / 100L );
//STRIP001  }
//STRIP001  Font aOldFont( ChgPhysFont( pOut ) );
//STRIP001  Font aOldPrnFont( ChgPhysFont( pPrinter ) );
//STRIP001
//STRIP001  if ( IsCapital() )
//STRIP001      DrawCapital( pOut, aPos, rTxt, nIdx, nTmp );
//STRIP001  else
//STRIP001  {
//STRIP001      Size aSize = GetPhysTxtSize( pPrinter, rTxt, nIdx, nTmp );
//STRIP001
//STRIP001      if ( !IsCaseMap() )
//STRIP001          pOut->DrawStretchText( aPos, aSize.Width(), rTxt, nIdx, nTmp );
//STRIP001      else
//STRIP001      {
//STRIP001          // #108210#
//STRIP001          const XubString aNewText = CalcCaseMap(rTxt);
//STRIP001          sal_Bool bCaseMapLengthDiffers(aNewText.Len() != rTxt.Len());
//STRIP001
//STRIP001          if(bCaseMapLengthDiffers)
//STRIP001          {
//STRIP001              // If strings differ work preparing the necessary snippet to address that
//STRIP001              // potential difference
//STRIP001              const XubString aSnippet(rTxt, nIdx, nTmp);
//STRIP001              XubString aNewText = CalcCaseMap(aSnippet);
//STRIP001
//STRIP001              pOut->DrawStretchText( aPos, aSize.Width(), aNewText, 0, aNewText.Len() );
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              pOut->DrawStretchText( aPos, aSize.Width(), CalcCaseMap( rTxt ), nIdx, nTmp );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  pOut->SetFont(aOldFont);
//STRIP001  pPrinter->SetFont( aOldPrnFont );
//STRIP001 }

// -----------------------------------------------------------------------

/*N*/ SvxFont& SvxFont::operator=( const Font& rFont )
/*N*/ {
/*N*/   Font::operator=( rFont );
/*N*/   return *this;
/*N*/ }

/*N*/ SvxFont& SvxFont::operator=( const SvxFont& rFont )
/*N*/ {
/*N*/   Font::operator=( rFont );
/*N*/   eLang = rFont.eLang;
/*N*/   eCaseMap = rFont.eCaseMap;
/*N*/   nEsc = rFont.nEsc;
/*N*/   nPropr = rFont.nPropr;
/*N*/   nKern = rFont.nKern;
/*N*/   return *this;
/*N*/ }


/*************************************************************************
 *                    class SvxDoGetCapitalSize
 * wird von SvxFont::GetCapitalSize() zur Berechnung der TxtSize bei
 * eingestellten Kapitaelchen benutzt.
 *************************************************************************/

class SvxDoGetCapitalSize : public SvxDoCapitals
{
protected:
    SvxFont*    pFont;
    Size        aTxtSize;
    short       nKern;
public:
      SvxDoGetCapitalSize( SvxFont *pFnt, const OutputDevice *pOut,
                           const XubString &rTxt, const xub_StrLen nIdx,
                           const xub_StrLen nLen, const short nKrn )
            : SvxDoCapitals( (OutputDevice*)pOut, rTxt, nIdx, nLen ),
              pFont( pFnt ),
              nKern( nKrn )
            { }

//STRIP001  virtual void Do( const XubString &rTxt, const xub_StrLen nIdx,
//STRIP001                   const xub_StrLen nLen, const BOOL bUpper );

    inline const Size &GetSize() const { return aTxtSize; };
};

//STRIP001 void SvxDoGetCapitalSize::Do( const XubString &rTxt, const xub_StrLen nIdx,
//STRIP001                            const xub_StrLen nLen, const BOOL bUpper )
//STRIP001 {
//STRIP001  Size aPartSize;
//STRIP001  if ( !bUpper )
//STRIP001  {
//STRIP001      BYTE nProp = pFont->GetPropr();
//STRIP001      pFont->SetProprRel( KAPITAELCHENPROP );
//STRIP001      pFont->SetPhysFont( pOut );
//STRIP001      aPartSize.setWidth( pOut->GetTextWidth( rTxt, nIdx, nLen ) );
//STRIP001      aPartSize.setHeight( pOut->GetTextHeight() );
//STRIP001      aTxtSize.Height() = aPartSize.Height();
//STRIP001      pFont->SetPropr( nProp );
//STRIP001      pFont->SetPhysFont( pOut );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      aPartSize.setWidth( pOut->GetTextWidth( rTxt, nIdx, nLen ) );
//STRIP001      aPartSize.setHeight( pOut->GetTextHeight() );
//STRIP001  }
//STRIP001  aTxtSize.Width() += aPartSize.Width();
//STRIP001  aTxtSize.Width() += ( nLen * long( nKern ) );
//STRIP001 }

/*************************************************************************
 *                    SvxFont::GetCapitalSize()
 * berechnet TxtSize, wenn Kapitaelchen eingestellt sind.
 *************************************************************************/

//STRIP001 Size SvxFont::GetCapitalSize( const OutputDevice *pOut, const XubString &rTxt,
//STRIP001                           const xub_StrLen nIdx, const xub_StrLen nLen) const
//STRIP001 {
//STRIP001  // Start:
//STRIP001  SvxDoGetCapitalSize aDo( (SvxFont *)this, pOut, rTxt, nIdx, nLen, nKern );
//STRIP001  DoOnCapitals( aDo );
//STRIP001  Size aTxtSize( aDo.GetSize() );
//STRIP001
//STRIP001  // End:
//STRIP001  if( !aTxtSize.Height() )
//STRIP001  {
//STRIP001      aTxtSize.setWidth( 0 );
//STRIP001      aTxtSize.setHeight( pOut->GetTextHeight() );
//STRIP001  }
//STRIP001  return aTxtSize;
//STRIP001 }

/*************************************************************************
 *                     class SvxDoDrawCapital
 * wird von SvxFont::DrawCapital zur Ausgabe von Kapitaelchen benutzt.
 *************************************************************************/

class SvxDoDrawCapital : public SvxDoCapitals
{
protected:
    SvxFont *pFont;
    Point aPos;
    Point aSpacePos;
    short nKern;
public:
    SvxDoDrawCapital( SvxFont *pFnt, OutputDevice *pOut, const XubString &rTxt,
                      const xub_StrLen nIdx, const xub_StrLen nLen,
                      const Point &rPos, const short nKrn )
        : SvxDoCapitals( pOut, rTxt, nIdx, nLen ),
          pFont( pFnt ),
          aPos( rPos ),
          aSpacePos( rPos ),
          nKern( nKrn )
        { }
//STRIP001  virtual void DoSpace( const BOOL bDraw );
//STRIP001  virtual void SetSpace();
//STRIP001  virtual void Do( const XubString &rTxt, const xub_StrLen nIdx,
//STRIP001                   const xub_StrLen nLen, const BOOL bUpper );
};

//STRIP001 void SvxDoDrawCapital::DoSpace( const BOOL bDraw )
//STRIP001 {
//STRIP001  if ( bDraw || pFont->IsWordLineMode() )
//STRIP001  {
//STRIP001      USHORT nDiff = (USHORT)(aPos.X() - aSpacePos.X());
//STRIP001      if ( nDiff )
//STRIP001      {
//STRIP001          BOOL bWordWise = pFont->IsWordLineMode();
//STRIP001          BOOL bTrans = pFont->IsTransparent();
//STRIP001          pFont->SetWordLineMode( FALSE );
//STRIP001          pFont->SetTransparent( TRUE );
//STRIP001          pFont->SetPhysFont( pOut );
//STRIP001          pOut->DrawStretchText( aSpacePos, nDiff, XubString( sDoubleSpace,
//STRIP001                          RTL_TEXTENCODING_MS_1252 ), 0, 2 );
//STRIP001          pFont->SetWordLineMode( bWordWise );
//STRIP001          pFont->SetTransparent( bTrans );
//STRIP001          pFont->SetPhysFont( pOut );
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void SvxDoDrawCapital::SetSpace()
//STRIP001 {
//STRIP001  if ( pFont->IsWordLineMode() )
//STRIP001      aSpacePos.X() = aPos.X();
//STRIP001 }

//STRIP001 void SvxDoDrawCapital::Do( const XubString &rTxt, const xub_StrLen nIdx,
//STRIP001                         const xub_StrLen nLen, const BOOL bUpper)
//STRIP001 {
//STRIP001  BYTE nProp;
//STRIP001  Size aPartSize;
//STRIP001
//STRIP001  // Einstellen der gewuenschten Fonts
//STRIP001  FontUnderline eUnder = pFont->GetUnderline();
//STRIP001  FontStrikeout eStrike = pFont->GetStrikeout();
//STRIP001  pFont->SetUnderline( UNDERLINE_NONE );
//STRIP001  pFont->SetStrikeout( STRIKEOUT_NONE );
//STRIP001  if ( !bUpper )
//STRIP001  {
//STRIP001      nProp = pFont->GetPropr();
//STRIP001      pFont->SetProprRel( KAPITAELCHENPROP );
//STRIP001  }
//STRIP001  pFont->SetPhysFont( pOut );
//STRIP001
//STRIP001  aPartSize.setWidth( pOut->GetTextWidth( rTxt, nIdx, nLen ) );
//STRIP001  aPartSize.setHeight( pOut->GetTextHeight() );
//STRIP001  long nWidth = aPartSize.Width();
//STRIP001  if ( nKern )
//STRIP001  {
//STRIP001      aPos.X() += (nKern/2);
//STRIP001      if ( nLen ) nWidth += (nLen*long(nKern));
//STRIP001  }
//STRIP001  pOut->DrawStretchText(aPos,nWidth-nKern,rTxt,nIdx,nLen);
//STRIP001
//STRIP001  // Font restaurieren
//STRIP001  pFont->SetUnderline( eUnder );
//STRIP001  pFont->SetStrikeout( eStrike );
//STRIP001  if ( !bUpper )
//STRIP001      pFont->SetPropr( nProp );
//STRIP001  pFont->SetPhysFont( pOut );
//STRIP001
//STRIP001  aPos.X() += nWidth-(nKern/2);
//STRIP001 }

/*************************************************************************
 * SvxFont::DrawCapital() gibt Kapitaelchen aus.
 *************************************************************************/

//STRIP001 void SvxFont::DrawCapital( OutputDevice *pOut,
//STRIP001             const Point &rPos, const XubString &rTxt,
//STRIP001             const xub_StrLen nIdx, const xub_StrLen nLen ) const
//STRIP001 {
//STRIP001  SvxDoDrawCapital aDo( (SvxFont *)this,pOut,rTxt,nIdx,nLen,rPos,nKern );
//STRIP001  DoOnCapitals( aDo );
//STRIP001 }

#endif // !REDUCEDSVXFONT


}
