/*************************************************************************
 *
 *  $RCSfile: pormulti.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:41:05 $
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

#ifndef _PORMULTI_HXX
#define _PORMULTI_HXX

#include "porlay.hxx"
#include "porexp.hxx"
class SfxPoolItem;
namespace binfilter {

class SwTxtFormatInfo;
class SwFldPortion;
class SwTxtCursor;
class SwLineLayout;
class SwBlankPortion;
class SwTxtPaintInfo;
class SwTxtAttr;

class SwFont;

/*-----------------02.02.01 15:01-------------------
 * SwMultiCreator is a small structur to create a multiportion.
 * It contains the kind of multiportion and a textattribute
 * or a poolitem.
 * The GetMultiCreator-function fills this structur and
 * the Ctor of the SwMultiPortion uses it.
 * --------------------------------------------------*/

#define SW_MC_DOUBLE    0
#define SW_MC_RUBY      1
#define SW_MC_ROTATE    2
#ifdef BIDI
#define SW_MC_BIDI      3
#endif

struct SwMultiCreator
{
    const SwTxtAttr* pAttr;
    const SfxPoolItem* pItem;
    BYTE nId;
#ifdef BIDI
    BYTE nLevel;
#endif
};

/*-----------------25.10.00 16:19-------------------
 * A two-line-portion (SwMultiPortion) could have surrounding brackets,
 * in this case the structur SwBracket will be used.
 * --------------------------------------------------*/

struct SwBracket
{
    xub_StrLen nStart;      // Start of text attribute determins the font
    KSHORT nAscent;         // Ascent of the brackets
    KSHORT nHeight;         // Height of them
    KSHORT nPreWidth;       // Width of the opening bracket
    KSHORT nPostWidth;      // Width of the closing bracket
    sal_Unicode cPre;       // Initial character, e.g. '('
    sal_Unicode cPost;      // Final character, e.g. ')'
    BYTE nPreScript;        // Script of the initial character
    BYTE nPostScript;       // Script of the final character
};

/*-----------------16.10.00 12:45-------------------
 * The SwMultiPortion is line portion inside a line portion,
 * it's a group of portions,
 * e.g. a double line portion in a line
 * or phonetics (ruby)
 * or combined characters
 * or a rotated portion.
 * --------------------------------------------------*/

class SwMultiPortion : public SwLinePortion
{
     SwLineLayout aRoot;        // One or more lines
     SwFldPortion *pFldRest;    // Field rest from the previous line
     sal_Bool bTab1     :1; // First line tabulator
     sal_Bool bTab2     :1; // Second line includes tabulator
     sal_Bool bDouble   :1; // Double line
     sal_Bool bRuby     :1; // Phonetics
 #ifdef BIDI
    sal_Bool bBidi      :1;
 #endif
     sal_Bool bTop      :1; // Phonetic position
     sal_Bool bFormatted :1; // Already formatted
    sal_Bool bFollowFld :1; // Field follow inside
    sal_uInt8 nDirection:2; // Direction (0/90/180/270 degrees)
    sal_Bool bFlyInCntnt:1; // Fly as character inside
protected:
SwMultiPortion( xub_StrLen nEnd ) : pFldRest( 0 ), bTab1( sal_False ),
 #ifdef BIDI
         bTab2( sal_False ), bDouble( sal_False ), bRuby( sal_False ),
         bBidi( sal_False ), bFormatted( sal_False ), bFollowFld( sal_False ),
         nDirection( 0 ), bFlyInCntnt( sal_False )
 #else
         bTab2( sal_False ),    bDouble( sal_False ), bRuby( sal_False ),
         bFormatted( sal_False ), bFollowFld( sal_False ), nDirection( 0 ),
         bFlyInCntnt( sal_False )
 #endif
         { SetWhichPor( POR_MULTI ); SetLen( nEnd ); }
//STRIP001  inline void SetDouble() { bDouble = sal_True; }
//STRIP001  inline void SetRuby() { bRuby = sal_True; }
//STRIP001 #ifdef BIDI
//STRIP001     inline void SetBidi() { bBidi = sal_True; }
//STRIP001 #endif
//STRIP001  inline void SetTop( sal_Bool bNew ) { bTop = bNew; }
//STRIP001  inline void SetTab1( sal_Bool bNew ) { bTab1 = bNew; }
//STRIP001  inline void SetTab2( sal_Bool bNew ) { bTab2 = bNew; }
//STRIP001  inline void SetDirection( sal_uInt8 nNew ) { nDirection = nNew; }
//STRIP001  inline sal_Bool GetTab1() const { return bTab1; }
//STRIP001  inline sal_Bool GetTab2() const { return bTab2; }
public:
//STRIP001      ~SwMultiPortion();
     const SwLineLayout& GetRoot() const { return aRoot; }
     SwLineLayout& GetRoot() { return aRoot; }
//STRIP001  SwFldPortion* GetFldRest() { return pFldRest; }
//STRIP001  void SetFldRest( SwFldPortion* pNew ) { pFldRest = pNew; }
//STRIP001
    inline sal_Bool HasTabulator() const{DBG_BF_ASSERT(0, "STRIP"); return FALSE;} //STRIP001   inline sal_Bool HasTabulator() const { return bTab1 || bTab2; }
//STRIP001  inline sal_Bool IsFormatted() const { return bFormatted; }
//STRIP001  inline void SetFormatted() { bFormatted = sal_True; }
    inline sal_Bool IsFollowFld() const { return bFollowFld; }
//STRIP001  inline void SetFollowFld() { bFollowFld = sal_True; }
    inline sal_Bool HasFlyInCntnt() const { return bFlyInCntnt; }
//STRIP001  inline void SetFlyInCntnt( sal_Bool bNew ) { bFlyInCntnt = bNew; }
    inline sal_Bool IsDouble() const{DBG_BF_ASSERT(0, "STRIP"); return FALSE;} //STRIP001   inline sal_Bool IsDouble() const { return bDouble; }
//STRIP001  inline sal_Bool IsRuby() const { return bRuby; }
#ifdef BIDI
    inline sal_Bool IsBidi() const { return bBidi; }
#endif
//STRIP001  inline sal_Bool OnTop() const { return bTop; }
//STRIP001  void ActualizeTabulator();
//STRIP001
//STRIP001  virtual void Paint( const SwTxtPaintInfo &rInf ) const;
//STRIP001  virtual long CalcSpacing( short nSpaceAdd, const SwTxtSizeInfo &rInf ) const;
//STRIP001 #ifdef BIDI
//STRIP001     virtual sal_Bool ChgSpaceAdd( SwLineLayout* pCurr, short nSpaceAdd ) const;
//STRIP001 #endif
//STRIP001
//STRIP001  // Summarize the internal lines to calculate the (external) size
//STRIP001  void CalcSize( SwTxtFormatter& rLine, SwTxtFormatInfo &rInf );
//STRIP001
//STRIP001 #ifndef BIDI
//STRIP001  inline sal_Bool ChgSpaceAdd( SwLineLayout* pCurr, short nSpaceAdd );
//STRIP001 #endif
//STRIP001  inline sal_Bool HasBrackets() const;
    inline sal_Bool HasRotation() const { return 0 != (1 & nDirection); }
//STRIP001  inline sal_Bool IsRevers() const { return 0 != (2 & nDirection); }
//STRIP001  inline sal_uInt8 GetDirection() const { return nDirection; }
//STRIP001  inline USHORT GetFontRotation() const
//STRIP001      { return ( HasRotation() ? ( IsRevers() ? 2700 : 900 ) : 0 ); }
//STRIP001
//STRIP001     // Accessibility: pass information about this portion to the PortionHandler
//STRIP001     virtual void HandlePortion( SwPortionHandler& rPH ) const;
//STRIP001
    OUTPUT_OPERATOR
};

//STRIP001 class SwDoubleLinePortion : public SwMultiPortion
//STRIP001 {
//STRIP001  SwBracket* pBracket;    // Surrounding brackets
//STRIP001  SwTwips nLineDiff;      // Difference of the width of the both lines
//STRIP001  xub_StrLen nBlank1;     // Number of blanks in the first line
//STRIP001  xub_StrLen nBlank2;     // Number of blanks in the second line
//STRIP001 public:
//STRIP001     SwDoubleLinePortion( SwDoubleLinePortion& rDouble, xub_StrLen nEnd );
//STRIP001  SwDoubleLinePortion( const SwMultiCreator& rCreate, xub_StrLen nEnd );
//STRIP001  ~SwDoubleLinePortion();
//STRIP001
//STRIP001  inline SwBracket* GetBrackets() const { return pBracket; }
//STRIP001  void SetBrackets( const SwDoubleLinePortion& rDouble );
//STRIP001  void PaintBracket( SwTxtPaintInfo& rInf, short nSpc, sal_Bool bOpen ) const;
//STRIP001  void FormatBrackets( SwTxtFormatInfo &rInf, SwTwips& nMaxWidth );
//STRIP001  inline KSHORT PreWidth() const { return pBracket->nPreWidth; };
//STRIP001  inline KSHORT PostWidth() const { return pBracket->nPostWidth; }
//STRIP001  inline void ClearBrackets()
//STRIP001      { pBracket->nPreWidth = pBracket->nPostWidth=0; Width( 0 ); }
//STRIP001  inline KSHORT BracketWidth(){ return PreWidth() + PostWidth(); }
//STRIP001
//STRIP001  void CalcBlanks( SwTxtFormatInfo &rInf );
//STRIP001 #ifndef BIDI
//STRIP001  sal_Bool ChangeSpaceAdd( SwLineLayout* pCurr, short nSpaceAdd );
//STRIP001 #endif
//STRIP001  static void ResetSpaceAdd( SwLineLayout* pCurr );
//STRIP001  inline SwTwips GetLineDiff() const { return nLineDiff; }
//STRIP001  inline xub_StrLen GetSpaceCnt() const
//STRIP001      { return ( nLineDiff < 0 ) ? nBlank2 : nBlank1; }
//STRIP001  inline xub_StrLen GetSmallerSpaceCnt() const
//STRIP001      { return ( nLineDiff < 0 ) ? nBlank1 : nBlank2; }
//STRIP001  inline xub_StrLen GetBlank1() const { return nBlank1; }
//STRIP001  inline xub_StrLen GetBlank2() const { return nBlank2; }
//STRIP001
//STRIP001  virtual long CalcSpacing( short nSpaceAdd, const SwTxtSizeInfo &rInf ) const;
//STRIP001 #ifdef BIDI
//STRIP001     virtual sal_Bool ChgSpaceAdd( SwLineLayout* pCurr, short nSpaceAdd ) const;
//STRIP001 #endif
//STRIP001 };

//STRIP001 class SwRubyPortion : public SwMultiPortion
//STRIP001 {
//STRIP001  xub_StrLen nRubyOffset;
//STRIP001  USHORT nAdjustment;
//STRIP001  void _Adjust( SwTxtFormatInfo &rInf);
//STRIP001 public:
//STRIP001 #ifdef BIDI
//STRIP001     SwRubyPortion( const SwRubyPortion& rRuby, xub_StrLen nEnd );
//STRIP001 #else
//STRIP001  SwRubyPortion( xub_StrLen nEnd, USHORT nAdj, USHORT nPos, xub_StrLen nOfst )
//STRIP001      : SwMultiPortion( nEnd ), nRubyOffset( nOfst ), nAdjustment( nAdj )
//STRIP001      { SetRuby(); SetTop(!nPos); }
//STRIP001 #endif
//STRIP001
//STRIP001     SwRubyPortion( const SwMultiCreator& rCreate, const SwFont& rFnt,
//STRIP001                    const SwDoc& rDoc, xub_StrLen nEnd, xub_StrLen nOffs,
//STRIP001                    const sal_Bool* pForceRubyPos );
//STRIP001
//STRIP001     void CalcRubyOffset();
//STRIP001  inline void Adjust( SwTxtFormatInfo &rInf )
//STRIP001      { if(nAdjustment && GetRoot().GetNext()) _Adjust(rInf); }
//STRIP001  inline USHORT GetAdjustment() const { return nAdjustment; }
//STRIP001  inline xub_StrLen GetRubyOffset() const { return nRubyOffset; }
//STRIP001 };

//STRIP001 class SwRotatedPortion : public SwMultiPortion
//STRIP001 {
//STRIP001 public:
//STRIP001  SwRotatedPortion( xub_StrLen nEnd, sal_uInt8 nDir = 1 )
//STRIP001      : SwMultiPortion( nEnd ) { SetDirection( nDir ); }
//STRIP001     SwRotatedPortion( const SwMultiCreator& rCreate, xub_StrLen nEnd,
//STRIP001                       sal_Bool bRTL );
//STRIP001 };

#ifdef BIDI
class SwBidiPortion : public SwMultiPortion
{
    BYTE nLevel;
    xub_StrLen nBlanks;     // Number of blanks

public:
   SwBidiPortion( xub_StrLen nEnd, BYTE nLv );

   inline BYTE GetLevel() const { return nLevel; }
    // Set/Get number of blanks for justified alignment
   inline void SetSpaceCnt( xub_StrLen nNew ) { nBlanks = nNew; }
   inline xub_StrLen GetSpaceCnt() const { return nBlanks; }
   // Calculates extra spacing based on number of blanks
//STRIP001  virtual long CalcSpacing( short nSpaceAdd, const SwTxtSizeInfo &rInf ) const;
 // Manipulate the spacing array at pCurr
//STRIP001    virtual sal_Bool ChgSpaceAdd( SwLineLayout* pCurr, short nSpaceAdd ) const;
};
#endif

// For cursor travelling in multiportions

//STRIP001 class SwTxtCursorSave
//STRIP001 {
//STRIP001  SwTxtCursor* pTxtCrsr;
//STRIP001  SwLineLayout* pCurr;
//STRIP001  SwTwips nWidth;
//STRIP001  xub_StrLen nStart;
//STRIP001  BYTE nOldProp;
//STRIP001  sal_Bool bSpaceChg;
//STRIP001 public:
//STRIP001 #ifdef BIDI
//STRIP001  SwTxtCursorSave( SwTxtCursor* pTxtCursor, SwMultiPortion* pMulti,
//STRIP001         SwTwips nY, USHORT& nX, xub_StrLen nCurrStart, short nSpaceAdd );
//STRIP001 #else
//STRIP001  SwTxtCursorSave( SwTxtCursor* pTxtCursor, SwMultiPortion* pMulti,
//STRIP001      SwTwips nY, xub_StrLen nCurrStart, short nSpaceAdd );
//STRIP001 #endif
//STRIP001  ~SwTxtCursorSave();
//STRIP001 };

/*************************************************************************
 *                  inline - Implementations
 *************************************************************************/

#ifndef BIDI
inline sal_Bool SwMultiPortion::ChgSpaceAdd(SwLineLayout* pCurr,short nSpaceAdd)
    { return IsDouble() ? ((SwDoubleLinePortion*)this)->ChangeSpaceAdd( pCurr,
                            nSpaceAdd ) : sal_False; }
#endif

//STRIP001 inline sal_Bool SwMultiPortion::HasBrackets() const
//STRIP001  { return IsDouble() ? 0 != ((SwDoubleLinePortion*)this)->GetBrackets()
//STRIP001    : sal_False; }

CLASSIO( SwMultiPortion )

} //namespace binfilter
#endif
