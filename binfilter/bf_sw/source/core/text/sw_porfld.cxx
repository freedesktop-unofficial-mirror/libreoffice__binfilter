/*************************************************************************
 *
 *  $RCSfile: sw_porfld.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 17:53:09 $
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

#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif

#ifndef _COM_SUN_STAR_I18N_SCRIPTTYPE_HDL_
#include <com/sun/star/i18n/ScriptType.hdl>
#endif

// auto strip #ifndef _GRAPH_HXX //autogen
// auto strip #include <vcl/graph.hxx>
// auto strip #endif
// auto strip #ifndef _SVX_BRSHITEM_HXX //autogen
// auto strip #include <bf_svx/brshitem.hxx>
// auto strip #endif
// auto strip #ifndef _METRIC_HXX //autogen
// auto strip #include <vcl/metric.hxx>
// auto strip #endif
// auto strip #ifndef _OUTDEV_HXX //autogen
// auto strip #include <vcl/outdev.hxx>
// auto strip #endif

// auto strip #ifndef _FRMSH_HXX
// auto strip #include <frmsh.hxx>
// auto strip #endif
#ifndef _VIEWOPT_HXX
#include <viewopt.hxx>  // SwViewOptions
#endif
// auto strip #ifndef _ERRHDL_HXX
// auto strip #include <errhdl.hxx>
// auto strip #endif
// auto strip #ifndef _TXTCFG_HXX
// auto strip #include <txtcfg.hxx>
// auto strip #endif
// auto strip #ifndef _SW_PORTIONHANDLER_HXX
// auto strip #include <SwPortionHandler.hxx>
// auto strip #endif
// auto strip #ifndef _PORLAY_HXX
// auto strip #include <porlay.hxx>
// auto strip #endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

// auto strip #ifndef _PORFLD_HXX
// auto strip #include <porfld.hxx>
// auto strip #endif
#ifndef _INFTXT_HXX
#include <inftxt.hxx>
#endif
#ifndef _BLINK_HXX
#include <blink.hxx>    // pBlink
#endif
// auto strip #ifndef _FRMTOOL_HXX
// auto strip #include <frmtool.hxx>  // DrawGraphic
// auto strip #endif
// auto strip #ifndef _VIEWSH_HXX
// auto strip #include <viewsh.hxx>
// auto strip #endif
// auto strip #ifndef _DOCSH_HXX
// auto strip #include <docsh.hxx>
// auto strip #endif
// auto strip #ifndef _DOC_HXX
// auto strip #include <doc.hxx>
// auto strip #endif
#ifndef _BREAKIT_HXX
#include <breakit.hxx>
#endif
// auto strip #ifndef _PORRST_HXX
// auto strip #include <porrst.hxx>
// auto strip #endif
#ifndef _PORFTN_HXX
#include <porftn.hxx>   // SwFtnPortion
#endif
// auto strip #ifndef _ACCESSIBILITYOPTIONS_HXX
// auto strip #include <accessibilityoptions.hxx>
// auto strip #endif
namespace binfilter {

using namespace ::com::sun::star;

/*************************************************************************
 *                      class SwFldPortion
 *************************************************************************/

/*N*/ SwLinePortion *SwFldPortion::Compress()
/*N*/ { return (GetLen() || aExpand.Len() || SwLinePortion::Compress()) ? this : 0; }

/*N*/ SwFldPortion *SwFldPortion::Clone( const XubString &rExpand ) const
/*N*/ {
/*N*/   SwFont *pNewFnt;
/*N*/   if( 0 != ( pNewFnt = pFnt ) )
/*?*/       pNewFnt = new SwFont( *pFnt );
/*N*/     SwFldPortion* pClone = new SwFldPortion( rExpand, pNewFnt );
/*N*/     pClone->SetNextOffset( nNextOffset );
/*N*/     return pClone;
/*N*/ }

/*N*/ void SwFldPortion::TakeNextOffset( const SwFldPortion* pFld )
/*N*/ {
/*N*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 //STRIP001    ASSERT( pFld, "TakeNextOffset: Missing Source" );
//STRIP001  nNextOffset = pFld->GetNextOffset();
//STRIP001  aExpand.Erase( 0, nNextOffset );
//STRIP001  bFollow = sal_True;
/*N*/ }

/*N*/ SwFldPortion::SwFldPortion( const XubString &rExpand, SwFont *pFnt )
/*N*/   : aExpand(rExpand), pFnt(pFnt), nViewWidth(0), nNextOffset(0),
/*N*/     bFollow( sal_False ), bHasFollow( sal_False )
/*N*/ {
/*N*/   SetWhichPor( POR_FLD );
/*N*/ }

/*N*/ SwFldPortion::SwFldPortion( const SwFldPortion& rFld )
/*N*/     : aExpand( rFld.GetExp() ),
/*N*/       bCenter( rFld.IsCenter() ),
/*N*/       bFollow( rFld.IsFollow() ),
/*N*/       bHasFollow( rFld.HasFollow() ),
/*N*/       bHide( rFld.IsHide() ),
/*N*/       bLeft( rFld.IsLeft() ),
/*N*/       nNextOffset( rFld.GetNextOffset() )
/*N*/ {
/*N*/     if ( rFld.HasFont() )
/*N*/         pFnt = new SwFont( *rFld.GetFont() );
/*N*/     else
/*N*/         pFnt = 0;
/*N*/
/*N*/     SetWhichPor( POR_FLD );
/*N*/ }

/*N*/ SwFldPortion::~SwFldPortion()
/*N*/ {
/*N*/   delete pFnt;
/*N*/   if( pBlink )
            {DBG_BF_ASSERT(0, "STRIP");} //STRIP001 /*?*/       pBlink->Delete( this );
/*N*/ }

/*************************************************************************
 *               virtual SwFldPortion::GetViewWidth()
 *************************************************************************/

//STRIP001 KSHORT SwFldPortion::GetViewWidth( const SwTxtSizeInfo &rInf ) const
//STRIP001 {
//STRIP001  // Wir stehen zwar im const, aber nViewWidth sollte erst im letzten
//STRIP001  // Moment errechnet werden:
//STRIP001  SwFldPortion* pThis = (SwFldPortion*)this;
//STRIP001     if( !Width() && rInf.OnWin() && !rInf.GetOpt().IsPagePreview() &&
//STRIP001             !rInf.GetOpt().IsReadonly() && SwViewOption::IsFieldShadings() )
//STRIP001  {
//STRIP001      if( !nViewWidth )
//STRIP001          pThis->nViewWidth = rInf.GetTxtSize( ' ' ).Width();
//STRIP001  }
//STRIP001  else
//STRIP001      pThis->nViewWidth = 0;
//STRIP001  return nViewWidth;
//STRIP001 }

/*************************************************************************
 *                 virtual SwFldPortion::Format()
 *************************************************************************/

// 8653: in keinem Fall nur SetLen(0);

/*************************************************************************
 *   Hilfsklasse SwFldSlot
 **************************************************************************/

class SwFldSlot
{
    const XubString *pOldTxt;
    XubString aTxt;
    xub_StrLen nIdx;
    xub_StrLen nLen;
    sal_Bool bOn;
    SwTxtFormatInfo *pInf;
public:
    SwFldSlot( const SwTxtFormatInfo* pNew, const SwFldPortion *pPor );
    ~SwFldSlot();
};

/*N*/ SwFldSlot::SwFldSlot( const SwTxtFormatInfo* pNew, const SwFldPortion *pPor )
/*N*/ {
/*N*/   bOn = pPor->GetExpTxt( *pNew, aTxt );
/*N*/
/*N*/   // Der Text wird ausgetauscht...
/*N*/   if( bOn )
/*N*/   {
/*N*/         pInf = (SwTxtFormatInfo*)pNew;
/*N*/       nIdx = pInf->GetIdx();
/*N*/       nLen = pInf->GetLen();
/*N*/       pOldTxt = &(pInf->GetTxt());
/*N*/       pInf->SetLen( aTxt.Len() );
/*N*/       if( pPor->IsFollow() )
/*N*/         {
/*N*/             pInf->SetFakeLineStart( nIdx > pInf->GetLineStart() );
/*N*/             pInf->SetIdx( 0 );
/*N*/         }
/*N*/       else
/*N*/       {
/*N*/           XubString aTmp( aTxt );
/*N*/           aTxt = *pOldTxt;
/*N*/           aTxt.Erase( nIdx, 1 );
/*N*/           aTxt.Insert( aTmp, nIdx );
/*N*/       }
/*N*/       pInf->SetTxt( aTxt );
/*N*/   }
/*N*/ }

/*N*/ SwFldSlot::~SwFldSlot()
/*N*/ {
/*N*/   if( bOn )
/*N*/   {
/*N*/       pInf->SetTxt( *pOldTxt );
/*N*/       pInf->SetIdx( nIdx );
/*N*/       pInf->SetLen( nLen );
/*N*/         pInf->SetFakeLineStart( sal_False );
/*N*/   }
/*N*/ }

/*N*/ BYTE SwFldPortion::ScriptChange( const SwTxtSizeInfo &rInf, xub_StrLen& rFull )
/*N*/ {
/*N*/   BYTE nRet = 0;
/*N*/   const String& rTxt = rInf.GetTxt();
/*N*/   rFull += rInf.GetIdx();
/*N*/   if( rFull > rTxt.Len() )
/*?*/       rFull = rTxt.Len();
/*N*/   if( rFull && pBreakIt->xBreak.is() )
/*N*/   {
/*N*/       BYTE nActual = pFnt ? pFnt->GetActual() : rInf.GetFont()->GetActual();
/*N*/       xub_StrLen nChg = rInf.GetIdx();
/*N*/       USHORT nScript;
/*N*/       {
/*N*/           nScript = i18n::ScriptType::LATIN;
/*N*/           if( nActual )
/*N*/               nScript = nActual == SW_CJK ? i18n::ScriptType::ASIAN
/*N*/                                           : i18n::ScriptType::COMPLEX;
/*N*/           nChg = (xub_StrLen)pBreakIt->xBreak->endOfScript(rTxt,nChg,nScript);
/*N*/       }
/*N*/       if( rFull > nChg )
/*N*/       {
/*?*/           nRet = nActual;
/*?*/           nScript = pBreakIt->xBreak->getScriptType( rTxt, nChg );
/*?*/           if( i18n::ScriptType::ASIAN == nScript )
/*?*/               nRet += SW_CJK;
/*?*/           else if( i18n::ScriptType::COMPLEX == nScript )
/*?*/               nRet += SW_CTL;
/*?*/           rFull = nChg;
/*N*/       }
/*N*/   }
/*N*/   rFull -= rInf.GetIdx();
/*N*/   return nRet;
/*N*/ }

/*N*/ void SwFldPortion::CheckScript( const SwTxtSizeInfo &rInf )
/*N*/ {
/*N*/   String aTxt;
/*N*/   if( GetExpTxt( rInf, aTxt ) && aTxt.Len() && pBreakIt->xBreak.is() )
/*N*/   {
/*N*/       BYTE nActual = pFnt ? pFnt->GetActual() : rInf.GetFont()->GetActual();
/*N*/       USHORT nScript;
/*N*/       {
/*N*/           nScript = pBreakIt->xBreak->getScriptType( aTxt, 0 );
/*N*/           xub_StrLen nChg = 0;
/*N*/           USHORT nCnt = 0;
/*N*/           if( i18n::ScriptType::WEAK == nScript )
/*N*/           {
/*N*/               nChg =(xub_StrLen)pBreakIt->xBreak->endOfScript(aTxt,0,nScript);
/*N*/               if( nChg < aTxt.Len() )
/*?*/                   nScript = pBreakIt->xBreak->getScriptType( aTxt, nChg );
/*N*/           }
/*N*/       }
/*N*/       BYTE nTmp;
/*N*/       switch ( nScript ) {
/*N*/           case i18n::ScriptType::LATIN : nTmp = SW_LATIN; break;
/*N*/           case i18n::ScriptType::ASIAN : nTmp = SW_CJK; break;
/*N*/           case i18n::ScriptType::COMPLEX : nTmp = SW_CTL; break;
/*N*/           default: nTmp = nActual;
/*N*/       }
/*N*/       if( nTmp != nActual )
/*N*/       {
/*?*/           if( !pFnt )
/*?*/               pFnt = new SwFont( *rInf.GetFont() );
/*?*/           pFnt->SetActual( nTmp );
/*N*/       }
/*N*/   }
/*N*/ }

/*M*/ sal_Bool SwFldPortion::Format( SwTxtFormatInfo &rInf )
/*M*/ {
/*M*/   // Scope wegen aDiffTxt::DTOR!
/*M*/   xub_StrLen nRest;
/*M*/   sal_Bool bFull;
/*M*/   sal_Bool bEOL = sal_False;
/*M*/   long nTxtRest = rInf.GetTxt().Len() - rInf.GetIdx();
/*M*/   {
/*M*/       SwFldSlot aDiffTxt( &rInf, this );
/*N*/         SwLayoutModeModifier aLayoutModeModifier( *rInf.GetOut() );
/*N*/         aLayoutModeModifier.SetAuto();
/*N*/
/*M*/       const xub_StrLen nOldFullLen = rInf.GetLen();
/*M*/       const MSHORT nFollow = IsFollow() ? 0 : 1;
/*M*/       xub_StrLen nFullLen;
/*M*/       // In Numerierungen kennen wir keine Platzhalter, sondern
/*M*/       // nur "normale" Zeichen.
/*M*/       if( InNumberGrp() )
/*M*/           nFullLen = nOldFullLen;
/*M*/       else
/*M*/       {
/*M*/           nFullLen = rInf.ScanPortionEnd( rInf.GetIdx(),
/*N*/                     rInf.GetIdx() + nOldFullLen ) - rInf.GetIdx();
/*M*/           if( nFullLen && CH_BREAK == aExpand.GetChar( nFullLen - 1 ) )
/*M*/               --nFullLen;
/*M*/
/*M*/             if ( STRING_LEN != rInf.GetUnderScorePos() &&
/*M*/                  rInf.GetUnderScorePos() > rInf.GetIdx() )
/*M*/                 rInf.SetUnderScorePos( rInf.GetIdx() );
/*M*/       }
/*M*/       BYTE nScriptChg = ScriptChange( rInf, nFullLen );
/*M*/       rInf.SetLen( nFullLen );
/*M*/       if( pFnt )
/*M*/           pFnt->GoMagic( rInf.GetVsh(), pFnt->GetActual() );
/*M*/
/*M*/       SwFontSave aSave( rInf, pFnt );
/*M*/
/*M*/       // 8674: Laenge muss 0 sein, bei bFull nach Format ist die Laenge
/*M*/       // gesetzt und wird in nRest uebertragen. Ansonsten bleibt die
/*M*/       // Laenge erhalten und wuerde auch in nRest einfliessen!
/*M*/       SetLen(0);
/*M*/
/*M*/       // So komisch es aussieht, die Abfrage auf GetLen() muss wegen der
/*M*/       // ExpandPortions _hinter_ aDiffTxt (vgl. SoftHyphs)
/*M*/       // sal_False returnen wegen SetFull ...
/*M*/       if( !nFullLen )
/*M*/       {
/*M*/           // nicht Init(), weil wir Hoehe und Ascent brauchen
/*M*/           Width(0);
/*M*/           bFull = rInf.Width() <= rInf.GetPos().X();
/*M*/       }
/*M*/       else
/*M*/       {
/*M*/           xub_StrLen nOldLineStart = rInf.GetLineStart();
/*M*/           if( IsFollow() )
/*M*/               rInf.SetLineStart( 0 );
/*M*/           rInf.SetNotEOL( nFullLen == nOldFullLen && nTxtRest > nFollow );
/*M*/
/*M*/             // the height depending on the fields font is set,
/*M*/             // this is required for SwTxtGuess::Guess
/*M*/             Height( rInf.GetTxtHeight() );
/*M*/             // If a kerning portion is inserted after our field portion,
/*M*/             // the ascent and height must be known
/*M*/             SetAscent( rInf.GetAscent() );
/*M*/             bFull = SwTxtPortion::Format( rInf );
/*M*/           rInf.SetNotEOL( sal_False );
/*M*/           rInf.SetLineStart( nOldLineStart );
/*M*/       }
/*M*/       xub_StrLen nTmpLen = GetLen();
/*M*/       bEOL = !nTmpLen && nFollow && bFull;
/*M*/       nRest = nOldFullLen - nTmpLen;
/*M*/
/*M*/         // Das Zeichen wird in der ersten Portion gehalten.
/*M*/       // Unbedingt nach Format!
/*M*/       SetLen( nFollow );
/*M*/
/*M*/         if( nRest )
/*M*/       {
/*M*/           // aExpand ist noch nicht gekuerzt worden, der neue Ofst
/*M*/           // ergibt sich durch nRest.
/*M*/             xub_StrLen nNextOfst = aExpand.Len() - nRest;
/*M*/
/*M*/             if ( IsQuoVadisPortion() )
/*?*/                { DBG_BF_ASSERT(0, "STRIP"); }//STRIP001 nNextOfst += ((SwQuoVadisPortion*)this)->GetContTxt().Len();
/*M*/
/*M*/           XubString aNew( aExpand, nNextOfst, STRING_LEN );
/*M*/           aExpand.Erase( nNextOfst, STRING_LEN );
/*M*/
/*M*/           // Trailingspace et al. !
/*M*/           switch( aNew.GetChar( 0 ))
/*M*/           {
/*M*/               case CH_BREAK  : bFull = sal_True;
/*M*/                           // kein break;
/*M*/               case ' ' :
/*M*/               case CH_TAB    :
/*M*/                 case CHAR_HARDHYPHEN:               // non-breaking hyphen
/*N*/                 case CHAR_SOFTHYPHEN:
/*N*/                 case CHAR_HARDBLANK:
/*M*/               {
/*M*/                   aNew.Erase( 0, 1 );
/*M*/                   ++nNextOfst;
/*M*/                   break;
/*M*/               }
/*M*/               default: ;
/*M*/           }
/*M*/
/*M*/           if( aNew.Len() || IsQuoVadisPortion() )
/*M*/           {
/*M*/               // sal_True, weil es ein FollowFeld ist
/*M*/               // SwFont *pFont = new SwFont( rInf.GetFont()->GetFnt() );
/*M*/               SwFldPortion *pFld = Clone( aNew );
/*M*/               if( !pFld->GetFont() )
/*M*/               {
/*M*/                   SwFont *pNewFnt = new SwFont( *rInf.GetFont() );
/*M*/                   pFld->SetFont( pNewFnt );
/*M*/               }
/*M*/               pFld->SetFollow( sal_True );
/*M*/               SetHasFollow( sal_True );
/*M*/               // In nNextOffset steht bei einem neuangelegten Feld zunaechst
/*M*/               // der Offset, an dem es selbst im Originalstring beginnt.
/*M*/               // Wenn beim Formatieren ein FollowFeld angelegt wird, wird
/*M*/               // der Offset dieses FollowFelds in nNextOffset festgehalten.
/*M*/               nNextOffset += nNextOfst;
/*M*/               pFld->SetNextOffset( nNextOffset );
/*M*/               rInf.SetRest( pFld );
/*M*/           }
/*M*/       }
/*M*/   }
/*M*/
/*M*/   if( bEOL && rInf.GetLast() && !rInf.GetUnderFlow() )
/*M*/       rInf.GetLast()->FormatEOL( rInf );
/*M*/   return bFull;
/*M*/ }

/*************************************************************************
 *               virtual SwFldPortion::Paint()
 *************************************************************************/

//STRIP001 void SwFldPortion::Paint( const SwTxtPaintInfo &rInf ) const
//STRIP001 {
//STRIP001  SwFontSave aSave( rInf, pFnt );
//STRIP001
//STRIP001  ASSERT( GetLen() <= 1, "SwFldPortion::Paint: rest-portion polution?" );
//STRIP001  if( Width() )
//STRIP001  {
//STRIP001      // Dies ist eine freizuegige Auslegung der Hintergrundbelegung ...
//STRIP001      rInf.DrawViewOpt( *this, POR_FLD );
//STRIP001      SwExpandPortion::Paint( rInf );
//STRIP001  }
//STRIP001 }

/*************************************************************************
 *              virtual SwFldPortion::GetExpTxt()
 *************************************************************************/

/*N*/ sal_Bool SwFldPortion::GetExpTxt( const SwTxtSizeInfo &rInf, XubString &rTxt ) const
/*N*/ {
/*N*/   rTxt = aExpand;
/*N*/     if( !rTxt.Len() && rInf.OnWin() &&
/*N*/         !rInf.GetOpt().IsPagePreview() && !rInf.GetOpt().IsReadonly() &&
/*N*/             SwViewOption::IsFieldShadings() &&
/*N*/             !HasFollow() )
/*N*/       rTxt = ' ';
/*N*/   return sal_True;
/*N*/ }

/*************************************************************************
 *              virtual SwFldPortion::HandlePortion()
 *************************************************************************/

//STRIP001 void SwFldPortion::HandlePortion( SwPortionHandler& rPH ) const
//STRIP001 {
//STRIP001     rPH.Special( GetLen(), aExpand, GetWhichPor() );
//STRIP001 }

/*************************************************************************
 *                virtual SwFldPortion::GetTxtSize()
 *************************************************************************/

/*N*/ SwPosSize SwFldPortion::GetTxtSize( const SwTxtSizeInfo &rInf ) const
/*N*/ {
/*N*/   SwFontSave aSave( rInf, pFnt );
/*N*/   SwPosSize aSize( SwExpandPortion::GetTxtSize( rInf ) );
/*N*/   return aSize;
/*N*/ }

/*************************************************************************
 *                      class SwHiddenPortion
 *************************************************************************/
//STRIP001
//STRIP001 SwFldPortion *SwHiddenPortion::Clone(const XubString &rExpand ) const
//STRIP001 {
//STRIP001  SwFont *pNewFnt;
//STRIP001  if( 0 != ( pNewFnt = pFnt ) )
//STRIP001      pNewFnt = new SwFont( *pFnt );
//STRIP001  return new SwHiddenPortion( rExpand, pNewFnt );
//STRIP001 }

/*************************************************************************
 *               virtual SwHiddenPortion::Paint()
 *************************************************************************/

//STRIP001 void SwHiddenPortion::Paint( const SwTxtPaintInfo &rInf ) const
//STRIP001 {
//STRIP001  if( Width() )
//STRIP001  {
//STRIP001      SwFontSave aSave( rInf, pFnt );
//STRIP001      rInf.DrawViewOpt( *this, POR_HIDDEN );
//STRIP001      SwExpandPortion::Paint( rInf );
//STRIP001  }
//STRIP001 }

/*************************************************************************
 *              virtual SwHiddenPortion::GetExpTxt()
 *************************************************************************/

/*N*/ sal_Bool SwHiddenPortion::GetExpTxt( const SwTxtSizeInfo &rInf, XubString &rTxt ) const
/*N*/ {
/*N*/   // Nicht auf IsHidden() abfragen !
/*N*/   return SwFldPortion::GetExpTxt( rInf, rTxt );
/*N*/ }

/*************************************************************************
 *                      class SwNumberPortion
 *************************************************************************/

/*N*/ SwNumberPortion::SwNumberPortion( const XubString &rExpand, SwFont *pFnt,
/*N*/                   const sal_Bool bLft, const sal_Bool bCntr, const KSHORT nMinDst )
/*N*/       : SwFldPortion( rExpand, pFnt ), nFixWidth(0), nMinDist( nMinDst )
/*N*/ {
/*N*/   SetWhichPor( POR_NUMBER );
/*N*/   SetLeft( bLft );
/*N*/   SetHide( sal_False );
/*N*/   SetCenter( bCntr );
/*N*/ }

//STRIP001 xub_StrLen SwNumberPortion::GetCrsrOfst( const MSHORT ) const
//STRIP001 {
//STRIP001  return 0;
//STRIP001 }

//STRIP001 SwFldPortion *SwNumberPortion::Clone( const XubString &rExpand ) const
//STRIP001 {
//STRIP001  SwFont *pNewFnt;
//STRIP001  if( 0 != ( pNewFnt = pFnt ) )
//STRIP001      pNewFnt = new SwFont( *pFnt );
//STRIP001  return new SwNumberPortion( rExpand, pNewFnt, IsLeft(), IsCenter(),
//STRIP001      nMinDist );
//STRIP001 }

/*************************************************************************
 *                 virtual SwNumberPortion::Format()
 *************************************************************************/

// 5010: Wir sind in der Lage, mehrzeilige NumFelder anzulegen!
// 3689: Fies ist, wenn man in der Dialogbox soviel Davor-Text
// eingibt, bis die Zeile ueberlaeuft.
// Man muss die Fly-Ausweichmanoever beachten!

/*M*/ sal_Bool SwNumberPortion::Format( SwTxtFormatInfo &rInf )
/*M*/ {
/*M*/   SetHide( sal_False );
/*M*/   const sal_Bool bFull = SwFldPortion::Format( rInf );
/*M*/   SetLen( 0 );
/*M*/     // a numbering portion can be contained in a rotated portion!!!
/*M*/     nFixWidth = rInf.IsMulti() ? Height() : Width();
/*M*/   rInf.SetNumDone( !rInf.GetRest() );
/*M*/   if( rInf.IsNumDone() )
/*M*/   {
/*M*/ //        SetAscent( rInf.GetAscent() );
/*M*/         ASSERT( Height() && nAscent, "NumberPortions without Height | Ascent" )
/*M*/
/*M*/       long nDiff = rInf.Left() - rInf.First() + rInf.ForcedLeftMargin();
/*M*/       // Ein Vorschlag von Juergen und Volkmar:
/*M*/       // Der Textteil hinter der Numerierung sollte immer
/*M*/       // mindestens beim linken Rand beginnen.
/*M*/       if( nDiff < 0 )
/*M*/           nDiff = 0;
/*M*/       else if ( nDiff > rInf.X() )
/*M*/           nDiff -= rInf.X();
/*M*/       if( nDiff < nFixWidth + nMinDist )
/*M*/           nDiff = nFixWidth + nMinDist;
/*M*/       // 2739: Numerierung weicht Fly aus, kein nDiff in der zweiten Runde
/*M*/       // fieser Sonderfall: FlyFrm liegt in dem Bereich,
/*M*/       // den wir uns gerade unter den Nagel reissen wollen.
/*M*/       // Die NumberPortion wird als verborgen markiert.
/*M*/       if( nDiff > rInf.Width() )
/*M*/       {
/*M*/           nDiff = rInf.Width();
/*M*/           SetHide( sal_True );
/*M*/       }
/*M*/
/*M*/         // A numbering portion can be inside a SwRotatedPortion. Then the
/*M*/         // Height has to be changed
/*M*/         if ( rInf.IsMulti() )
/*M*/         {
/*M*/             if ( Height() < nDiff )
/*M*/                 Height( KSHORT( nDiff ) );
/*M*/         }
/*M*/         else if( Width() < nDiff )
/*M*/             Width( KSHORT(nDiff) );
/*M*/   }
/*M*/   return bFull;
/*M*/ }

//STRIP001 void SwNumberPortion::FormatEOL( SwTxtFormatInfo &rInf )
//STRIP001 {
/*  Ein FormatEOL deutet daraufhin, dass der folgende Text
 *  nicht mit auf die Zeile passte. Damit die Numerierung mitwandert,
 *  wird diese NumberPortion verborgen.
 */

    // This caused trouble with flys anchored as characters.
    // If one of these is numbered but does not fit to the line,
    // it calls this function, causing a loop because both the number
    // portion and the fly portion go to the next line
//    SetHide( sal_True );
//STRIP001 }

/*************************************************************************
 *               virtual SwNumberPortion::Paint()
 *************************************************************************/

//STRIP001 void SwNumberPortion::Paint( const SwTxtPaintInfo &rInf ) const
//STRIP001 {
//STRIP001 /*   Eine verborgene NumberPortion wird nicht angezeigt, es sei denn, es gibt
//STRIP001  *   Textportions in dieser Zeile oder es gibt ueberhaupt nur eine einzige Zeile.
//STRIP001  */
//STRIP001  if ( IsHide() && rInf.GetParaPortion() && rInf.GetParaPortion()->GetNext() )
//STRIP001  {
//STRIP001      SwLinePortion *pTmp = GetPortion();
//STRIP001      while ( pTmp && !pTmp->InTxtGrp() )
//STRIP001          pTmp = pTmp->GetPortion();
//STRIP001      if ( !pTmp )
//STRIP001          return;
//STRIP001  }
//STRIP001
//STRIP001     // calculate the width of the number portion, including follows
//STRIP001     const KSHORT nOldWidth = Width();
//STRIP001     USHORT nSumWidth = 0;
//STRIP001     USHORT nOffset = 0;
//STRIP001
//STRIP001     const SwLinePortion* pTmp = this;
//STRIP001     while ( pTmp && pTmp->InNumberGrp() )
//STRIP001     {
//STRIP001         nSumWidth += pTmp->Width();
//STRIP001         if ( ((SwNumberPortion*)pTmp)->HasFollow() )
//STRIP001             pTmp = pTmp->GetPortion();
//STRIP001         else
//STRIP001         {
//STRIP001             nOffset = pTmp->Width() - ((SwNumberPortion*)pTmp)->nFixWidth;
//STRIP001             break;
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001     // The master portion takes care for painting the background of the
//STRIP001     // follow field portions
//STRIP001     if ( ! IsFollow() )
//STRIP001     {
//STRIP001         SwLinePortion *pThis = (SwLinePortion*)this;
//STRIP001         pThis->Width( nSumWidth );
//STRIP001         rInf.DrawViewOpt( *this, POR_NUMBER );
//STRIP001         pThis->Width( nOldWidth );
//STRIP001     }
//STRIP001
//STRIP001  if( aExpand.Len() )
//STRIP001  {
//STRIP001      const SwFont *pTmpFnt = rInf.GetFont();
//STRIP001      sal_Bool bPaintSpace = ( UNDERLINE_NONE != pTmpFnt->GetUnderline() ||
//STRIP001                           STRIKEOUT_NONE != pTmpFnt->GetStrikeout() ) &&
//STRIP001                          !pTmpFnt->IsWordLineMode();
//STRIP001      if( bPaintSpace && pFnt )
//STRIP001          bPaintSpace = ( UNDERLINE_NONE != pFnt->GetUnderline() ||
//STRIP001                           STRIKEOUT_NONE != pFnt->GetStrikeout() ) &&
//STRIP001                          !pFnt->IsWordLineMode();
//STRIP001
//STRIP001      SwFontSave aSave( rInf, pFnt );
//STRIP001
//STRIP001         if( nFixWidth == Width() && ! HasFollow() )
//STRIP001          SwExpandPortion::Paint( rInf );
//STRIP001      else
//STRIP001      {
//STRIP001          // logisches const: Width wird wieder zurueckgesetzt
//STRIP001          SwLinePortion *pThis = (SwLinePortion*)this;
//STRIP001          bPaintSpace = bPaintSpace && nFixWidth < nOldWidth;
//STRIP001          KSHORT nSpaceOffs = nFixWidth;
//STRIP001          pThis->Width( nFixWidth );
//STRIP001
//STRIP001          if( ( IsLeft() && ! rInf.GetTxtFrm()->IsRightToLeft() ) ||
//STRIP001                 ( ! IsLeft() && ! IsCenter() && rInf.GetTxtFrm()->IsRightToLeft() ) )
//STRIP001              SwExpandPortion::Paint( rInf );
//STRIP001          else
//STRIP001          {
//STRIP001              SwTxtPaintInfo aInf( rInf );
//STRIP001              if( nOffset < nMinDist )
//STRIP001                  nOffset = 0;
//STRIP001              else
//STRIP001              {
//STRIP001                  if( IsCenter() )
//STRIP001                  {
//STRIP001                      nOffset /= 2;
//STRIP001                      if( nOffset < nMinDist )
//STRIP001                          nOffset = 2 * nOffset - nMinDist;
//STRIP001                  }
//STRIP001                  else
//STRIP001                      nOffset -= nMinDist;
//STRIP001              }
//STRIP001              aInf.X( aInf.X() + nOffset );
//STRIP001              SwExpandPortion::Paint( aInf );
//STRIP001              if( bPaintSpace )
//STRIP001                  nSpaceOffs += nOffset;
//STRIP001          }
//STRIP001          if( bPaintSpace && nOldWidth > nSpaceOffs )
//STRIP001          {
//STRIP001              SwTxtPaintInfo aInf( rInf );
//STRIP001 static sal_Char __READONLY_DATA sDoubleSpace[] = "  ";
//STRIP001              aInf.X( aInf.X() + nSpaceOffs );
//STRIP001              pThis->Width( nOldWidth - nSpaceOffs + 12 );
//STRIP001              {
//STRIP001                  SwTxtSlotLen aDiffTxt( &aInf, this, sDoubleSpace );
//STRIP001                  aInf.DrawText( *this, aInf.GetLen(), sal_True );
//STRIP001              }
//STRIP001          }
//STRIP001          pThis->Width( nOldWidth );
//STRIP001      }
//STRIP001  }
//STRIP001 }


/*************************************************************************
 *                      class SwBulletPortion
 *************************************************************************/

/*N*/ SwBulletPortion::SwBulletPortion( const xub_Unicode cBullet, SwFont *pFont,
/*N*/                   const sal_Bool bLft, const sal_Bool bCntr, const KSHORT nMinDst )
/*N*/   : SwNumberPortion( XubString( cBullet ), pFont, bLft, bCntr, nMinDst )
/*N*/ {
/*N*/   SetWhichPor( POR_BULLET );
/*N*/ }

/*************************************************************************
 *                      class SwGrfNumPortion
 *************************************************************************/

#define GRFNUM_SECURE 10

//STRIP001 SwGrfNumPortion::SwGrfNumPortion(
//STRIP001      SwFrm *pFrm,
//STRIP001      const SvxBrushItem* pGrfBrush,
//STRIP001      const SwFmtVertOrient* pGrfOrient, const Size& rGrfSize,
//STRIP001      const sal_Bool bLft, const sal_Bool bCntr, const KSHORT nMinDst ) :
//STRIP001  SwNumberPortion( aEmptyStr, NULL, bLft, bCntr, nMinDst ),
//STRIP001  pBrush( new SvxBrushItem() ), nId( 0 )
//STRIP001 {
//STRIP001  SetWhichPor( POR_GRFNUM );
//STRIP001  SetAnimated( sal_False );
//STRIP001  bReplace = sal_False;
//STRIP001  if( pGrfBrush )
//STRIP001  {
//STRIP001      *pBrush = *pGrfBrush;
//STRIP001      SwDocShell *pSh = pFrm->GetShell()->GetDoc()->GetDocShell();
//STRIP001      const Graphic* pGraph = pGrfBrush->GetGraphic( pSh );
//STRIP001      if( pGraph )
//STRIP001          SetAnimated( pGraph->IsAnimated() );
//STRIP001      else
//STRIP001          bReplace = sal_True;
//STRIP001  }
//STRIP001  if( pGrfOrient )
//STRIP001  {
//STRIP001      nYPos = pGrfOrient->GetPos();
//STRIP001      eOrient = pGrfOrient->GetVertOrient();
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      nYPos = 0;
//STRIP001      eOrient = VERT_TOP;
//STRIP001  }
//STRIP001  Width( rGrfSize.Width() + 2 * GRFNUM_SECURE );
//STRIP001  nFixWidth = Width();
//STRIP001  nGrfHeight = rGrfSize.Height() + 2 * GRFNUM_SECURE;
//STRIP001  Height( KSHORT(nGrfHeight) );
//STRIP001  bNoPaint = sal_False;
//STRIP001 }

//STRIP001 SwGrfNumPortion::~SwGrfNumPortion()
//STRIP001 {
//STRIP001  if ( IsAnimated() )
//STRIP001      ( (Graphic*) pBrush->GetGraphic() )->StopAnimation( 0, nId );
//STRIP001  delete pBrush;
//STRIP001 }

//STRIP001 void SwGrfNumPortion::StopAnimation( OutputDevice *pOut )
//STRIP001 {
//STRIP001  if ( IsAnimated() )
//STRIP001      ( (Graphic*) pBrush->GetGraphic() )->StopAnimation( pOut, nId );
//STRIP001 }

//STRIP001 sal_Bool SwGrfNumPortion::Format( SwTxtFormatInfo &rInf )
//STRIP001 {
//STRIP001  SetHide( sal_False );
//STRIP001  Width( nFixWidth );
//STRIP001  const sal_Bool bFull = rInf.Width() < rInf.X() + Width();
//STRIP001  const sal_Bool bFly = rInf.GetFly() ||
//STRIP001      ( rInf.GetLast() && rInf.GetLast()->IsFlyPortion() );
//STRIP001  SetAscent( GetRelPos() > 0 ? GetRelPos() : 0 );
//STRIP001  if( GetAscent() > Height() )
//STRIP001      Height( GetAscent() );
//STRIP001
//STRIP001  if( bFull )
//STRIP001  {
//STRIP001      Width( rInf.Width() - (KSHORT)rInf.X() );
//STRIP001      if( bFly )
//STRIP001      {
//STRIP001          SetLen( 0 );
//STRIP001          SetNoPaint( sal_True );
//STRIP001          rInf.SetNumDone( sal_False );
//STRIP001          return sal_True;
//STRIP001      }
//STRIP001  }
//STRIP001  rInf.SetNumDone( sal_True );
//STRIP001  long nDiff = rInf.Left() - rInf.First() + rInf.ForcedLeftMargin();
//STRIP001  // Ein Vorschlag von Juergen und Volkmar:
//STRIP001  // Der Textteil hinter der Numerierung sollte immer
//STRIP001  // mindestens beim linken Rand beginnen.
//STRIP001  if( nDiff < 0 )
//STRIP001      nDiff = 0;
//STRIP001  else if ( nDiff > rInf.X() )
//STRIP001      nDiff -= rInf.X();
//STRIP001  if( nDiff < nFixWidth + nMinDist )
//STRIP001      nDiff = nFixWidth + nMinDist;
//STRIP001  // 2739: Numerierung weicht Fly aus, kein nDiff in der zweiten Runde
//STRIP001  // fieser Sonderfall: FlyFrm liegt in dem Bereich,
//STRIP001  // den wir uns gerade unter den Nagel reissen wollen.
//STRIP001  // Die NumberPortion wird als verborgen markiert.
//STRIP001  if( nDiff > rInf.Width() )
//STRIP001  {
//STRIP001      nDiff = rInf.Width();
//STRIP001      if( bFly )
//STRIP001          SetHide( sal_True );
//STRIP001  }
//STRIP001
//STRIP001  if( Width() < nDiff )
//STRIP001      Width( KSHORT(nDiff) );
//STRIP001  return bFull;
//STRIP001 }

//STRIP001 void SwGrfNumPortion::Paint( const SwTxtPaintInfo &rInf ) const
//STRIP001 {
//STRIP001  if( DontPaint() )
//STRIP001      return;
//STRIP001 /*   Eine verborgene NumberPortion wird nicht angezeigt, es sei denn, es gibt
//STRIP001  *   Textportions in dieser Zeile oder es gibt ueberhaupt nur eine einzige Zeile.
//STRIP001  */
//STRIP001  if ( IsHide() && rInf.GetParaPortion() && rInf.GetParaPortion()->GetNext() )
//STRIP001  {
//STRIP001      SwLinePortion *pTmp = GetPortion();
//STRIP001      while ( pTmp && !pTmp->InTxtGrp() )
//STRIP001          pTmp = pTmp->GetPortion();
//STRIP001      if ( !pTmp )
//STRIP001          return;
//STRIP001  }
//STRIP001  Point aPos( rInf.X() + GRFNUM_SECURE, rInf.Y() - GetRelPos() + GRFNUM_SECURE );
//STRIP001  long nTmpWidth = Max( (long)0, (long)(nFixWidth - 2 * GRFNUM_SECURE) );
//STRIP001  Size aSize( nTmpWidth, GetGrfHeight() - 2 * GRFNUM_SECURE );
//STRIP001
//STRIP001
//STRIP001     const sal_Bool bLeft = ( IsLeft() && ! rInf.GetTxtFrm()->IsRightToLeft() ) ||
//STRIP001                            ( ! IsLeft() && ! IsCenter() && rInf.GetTxtFrm()->IsRightToLeft() );
//STRIP001
//STRIP001
//STRIP001  if( nFixWidth < Width() && !bLeft )
//STRIP001  {
//STRIP001      KSHORT nOffset = Width() - nFixWidth;
//STRIP001      if( nOffset < nMinDist )
//STRIP001          nOffset = 0;
//STRIP001      else
//STRIP001      {
//STRIP001          if( IsCenter() )
//STRIP001          {
//STRIP001              nOffset /= 2;
//STRIP001              if( nOffset < nMinDist )
//STRIP001                  nOffset = Width() - nFixWidth - nMinDist;
//STRIP001          }
//STRIP001          else
//STRIP001              nOffset -= nMinDist;
//STRIP001      }
//STRIP001      aPos.X() += nOffset;
//STRIP001  }
//STRIP001
//STRIP001  if( bReplace )
//STRIP001  {
//STRIP001      KSHORT nTmpH = GetPortion() ? GetPortion()->GetAscent() : 120;
//STRIP001      aSize = Size( nTmpH, nTmpH );
//STRIP001      aPos.Y() = rInf.Y() - nTmpH;
//STRIP001  }
//STRIP001  SwRect aTmp( aPos, aSize );
//STRIP001
//STRIP001  sal_Bool bDraw = sal_True;
//STRIP001
//STRIP001  if ( IsAnimated() )
//STRIP001  {
//STRIP001      bDraw = !rInf.GetOpt().IsGraphic();
//STRIP001      if( !nId )
//STRIP001      {
//STRIP001          SetId( long( rInf.GetTxtFrm() ) );
//STRIP001          rInf.GetTxtFrm()->SetAnimation();
//STRIP001      }
//STRIP001      if( aTmp.IsOver( rInf.GetPaintRect() ) && !bDraw )
//STRIP001      {
//STRIP001          rInf.NoteAnimation();
//STRIP001             ViewShell* pViewShell = 0;
//STRIP001             if( OUTDEV_VIRDEV == rInf.GetOut()->GetOutDevType() )
//STRIP001          {
//STRIP001              ( (Graphic*) pBrush->GetGraphic() )->StopAnimation(0,nId);
//STRIP001              rInf.GetTxtFrm()->GetShell()->InvalidateWindows( aTmp );
//STRIP001          }
//STRIP001             // first check accessibility options before starting animation
//STRIP001             else if ( 0 != (pViewShell = rInf.GetTxtFrm()->GetShell()) &&
//STRIP001                      ! pViewShell->GetAccessibilityOptions()->IsStopAnimatedGraphics() &&
//STRIP001                       ! pViewShell->IsPreView() )
//STRIP001             {
//STRIP001              ( (Graphic*) pBrush->GetGraphic() )->StartAnimation(
//STRIP001                  (OutputDevice*)rInf.GetOut(), aPos, aSize, nId );
//STRIP001             }
//STRIP001             else
//STRIP001                 bDraw = sal_True;
//STRIP001      }
//STRIP001      if( bDraw )
//STRIP001          ( (Graphic*) pBrush->GetGraphic() )->StopAnimation( 0, nId );
//STRIP001  }
//STRIP001
//STRIP001     SwRect aRepaint( rInf.GetPaintRect() );
//STRIP001  const SwTxtFrm& rFrm = *rInf.GetTxtFrm();
//STRIP001     if( rFrm.IsVertical() )
//STRIP001     {
//STRIP001         rFrm.SwitchHorizontalToVertical( aTmp );
//STRIP001         rFrm.SwitchHorizontalToVertical( aRepaint );
//STRIP001     }
//STRIP001
//STRIP001 #ifdef BIDI
//STRIP001     if( rFrm.IsRightToLeft() )
//STRIP001     {
//STRIP001         rFrm.SwitchLTRtoRTL( aTmp );
//STRIP001         rFrm.SwitchLTRtoRTL( aRepaint );
//STRIP001     }
//STRIP001 #endif
//STRIP001
//STRIP001  if( bDraw && aTmp.HasArea() )
//STRIP001      DrawGraphic( pBrush, (OutputDevice*)rInf.GetOut(),
//STRIP001             aTmp, aRepaint, bReplace ? GRFNUM_REPLACE : GRFNUM_YES );
//STRIP001 }

//STRIP001 void SwGrfNumPortion::SetBase( long nLnAscent, long nLnDescent,
//STRIP001                             long nFlyAsc, long nFlyDesc )
//STRIP001 {
//STRIP001  if ( GetOrient() != VERT_NONE )
//STRIP001  {
//STRIP001      SetRelPos( 0 );
//STRIP001      if ( GetOrient() == VERT_CENTER )
//STRIP001          SetRelPos( GetGrfHeight() / 2 );
//STRIP001      else if ( GetOrient() == VERT_TOP )
//STRIP001          SetRelPos( GetGrfHeight() - GRFNUM_SECURE );
//STRIP001      else if ( GetOrient() == VERT_BOTTOM )
//STRIP001          ;
//STRIP001      else if ( GetOrient() == VERT_CHAR_CENTER )
//STRIP001          SetRelPos( ( GetGrfHeight() + nLnAscent - nLnDescent ) / 2 );
//STRIP001      else if ( GetOrient() == VERT_CHAR_TOP )
//STRIP001          SetRelPos( nLnAscent );
//STRIP001      else if ( GetOrient() == VERT_CHAR_BOTTOM )
//STRIP001          SetRelPos( GetGrfHeight() - nLnDescent );
//STRIP001      else
//STRIP001      {
//STRIP001          if( GetGrfHeight() >= nFlyAsc + nFlyDesc )
//STRIP001          {
//STRIP001              // wenn ich genauso gross bin wie die Zeile, brauche ich mich
//STRIP001              // nicht an der Zeile nicht weiter ausrichten, ich lasse
//STRIP001              // dann auch den max. Ascent der Zeile unveraendert
//STRIP001
//STRIP001              SetRelPos( nFlyAsc );
//STRIP001          }
//STRIP001          else if ( GetOrient() == VERT_LINE_CENTER )
//STRIP001              SetRelPos( ( GetGrfHeight() + nFlyAsc - nFlyDesc ) / 2 );
//STRIP001          else if ( GetOrient() == VERT_LINE_TOP )
//STRIP001              SetRelPos( nFlyAsc );
//STRIP001          else if ( GetOrient() == VERT_LINE_BOTTOM )
//STRIP001              SetRelPos( GetGrfHeight() - nFlyDesc );
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void SwTxtFrm::StopAnimation( OutputDevice *pOut )
//STRIP001 {
//STRIP001  ASSERT( HasAnimation(), "SwTxtFrm::StopAnimation: Which Animation?" );
//STRIP001  if( HasPara() )
//STRIP001  {
//STRIP001      SwLineLayout *pLine = GetPara();
//STRIP001      while( pLine )
//STRIP001      {
//STRIP001          SwLinePortion *pPor = pLine->GetPortion();
//STRIP001          while( pPor )
//STRIP001          {
//STRIP001              if( pPor->IsGrfNumPortion() )
//STRIP001                  ((SwGrfNumPortion*)pPor)->StopAnimation( pOut );
//STRIP001              // Die Numerierungsportion sitzt immer vor dem ersten Zeichen,
//STRIP001              // deshalb koennen wir abbrechen, sobald wir eine Portion mit
//STRIP001              // einer Laenge > 0 erreicht haben.
//STRIP001              pPor = pPor->GetLen() ? 0 : pPor->GetPortion();
//STRIP001          }
//STRIP001          pLine = pLine->GetLen() ? 0 : pLine->GetNext();
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*************************************************************************
 * SwCombinedPortion::SwCombinedPortion(..)
 * initializes the script array and clears the width array
 *************************************************************************/

/*N*/ SwCombinedPortion::SwCombinedPortion( const XubString &rTxt )
/*N*/    : SwFldPortion( rTxt )
/*N*/ {
DBG_BF_ASSERT(0, "STRIP"); //STRIP001 //STRIP001    SetLen(1);
//STRIP001  SetWhichPor( POR_COMBINED );
//STRIP001  if( aExpand.Len() > 6 )
//STRIP001      aExpand.Erase( 6 );
//STRIP001  // Initialization of the scripttype array,
//STRIP001  // the arrays of width and position are filled by the format function
//STRIP001  if( pBreakIt->xBreak.is() )
//STRIP001  {
//STRIP001      BYTE nScr = SW_SCRIPTS;
//STRIP001      for( USHORT i = 0; i < rTxt.Len(); ++i )
//STRIP001      {
//STRIP001          USHORT nScript = pBreakIt->xBreak->getScriptType( rTxt, i );
//STRIP001          switch ( nScript ) {
//STRIP001              case i18n::ScriptType::LATIN : nScr = SW_LATIN; break;
//STRIP001              case i18n::ScriptType::ASIAN : nScr = SW_CJK; break;
//STRIP001              case i18n::ScriptType::COMPLEX : nScr = SW_CTL; break;
//STRIP001          }
//STRIP001          aScrType[i] = nScr;
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      for( USHORT i = 0; i < 6; aScrType[i++] = 0 )
//STRIP001          ; // nothing
//STRIP001  }
//STRIP001  memset( &aWidth, 0, sizeof(aWidth) );
/*N*/ }

/*************************************************************************
 * SwCombinedPortion::Paint(..)
 *************************************************************************/

//STRIP001 void SwCombinedPortion::Paint( const SwTxtPaintInfo &rInf ) const
//STRIP001 {
//STRIP001  ASSERT( GetLen() <= 1, "SwFldPortion::Paint: rest-portion polution?" );
//STRIP001  if( Width() )
//STRIP001  {
//STRIP001      rInf.DrawBackBrush( *this );
//STRIP001      rInf.DrawViewOpt( *this, POR_FLD );
//STRIP001
//STRIP001         // do we have to repaint a post it portion?
//STRIP001         if( rInf.OnWin() && pPortion && !pPortion->Width() )
//STRIP001             pPortion->PrePaint( rInf, this );
//STRIP001
//STRIP001      USHORT nCount = aExpand.Len();
//STRIP001      if( !nCount )
//STRIP001          return;
//STRIP001      ASSERT( nCount < 7, "Too much combined characters" );
//STRIP001
//STRIP001      // the first character of the second row
//STRIP001      USHORT nTop = ( nCount + 1 ) / 2;
//STRIP001
//STRIP001      SwFont aTmpFont( *rInf.GetFont() );
//STRIP001      aTmpFont.SetProportion( nProportion );  // a smaller font
//STRIP001      SwFontSave aFontSave( rInf, &aTmpFont );
//STRIP001
//STRIP001      USHORT i = 0;
//STRIP001      Point aOldPos = rInf.GetPos();
//STRIP001      Point aOutPos( aOldPos.X(), aOldPos.Y() - nUpPos );// Y of the first row
//STRIP001      while( i < nCount )
//STRIP001      {
//STRIP001          if( i == nTop ) // change the row
//STRIP001              aOutPos.Y() = aOldPos.Y() + nLowPos;    // Y of the second row
//STRIP001          aOutPos.X() = aOldPos.X() + aPos[i];        // X position
//STRIP001          const BYTE nAct = aScrType[i];              // script type
//STRIP001          aTmpFont.SetActual( nAct );
//STRIP001          // if there're more than 4 characters to display, we choose fonts
//STRIP001          // with 2/3 of the original font width.
//STRIP001          if( aWidth[ nAct ] )
//STRIP001          {
//STRIP001              Size aTmpSz = aTmpFont.GetSize( nAct );
//STRIP001              if( aTmpSz.Width() != aWidth[ nAct ] )
//STRIP001              {
//STRIP001                  aTmpSz.Width() = aWidth[ nAct ];
//STRIP001                  aTmpFont.SetSize( aTmpSz, nAct );
//STRIP001              }
//STRIP001          }
//STRIP001          ((SwTxtPaintInfo&)rInf).SetPos( aOutPos );
//STRIP001          rInf.DrawText( aExpand, *this, i, 1 );
//STRIP001          ++i;
//STRIP001      }
//STRIP001      // rInf is const, so we have to take back our manipulations
//STRIP001      ((SwTxtPaintInfo&)rInf).SetPos( aOldPos );
//STRIP001  }
//STRIP001 }

/*************************************************************************
 * SwCombinedPortion::Format(..)
 *************************************************************************/

//STRIP001 sal_Bool SwCombinedPortion::Format( SwTxtFormatInfo &rInf )
//STRIP001 {
//STRIP001  USHORT nCount = aExpand.Len();
//STRIP001  if( !nCount )
//STRIP001  {
//STRIP001      Width( 0 );
//STRIP001      return sal_False;
//STRIP001  }
//STRIP001
//STRIP001  ASSERT( nCount < 7, "Too much combined characters" );
//STRIP001  // If there are leading "weak"-scripttyped characters in this portion,
//STRIP001  // they get the actual scripttype.
//STRIP001  USHORT i = 0;
//STRIP001  while( i < nCount && SW_SCRIPTS == aScrType[i] )
//STRIP001      aScrType[i++] = rInf.GetFont()->GetActual();
//STRIP001  if( nCount > 4 )
//STRIP001  {
//STRIP001      // more than four? Ok, then we need the 2/3 font width
//STRIP001      i = 0;
//STRIP001      while( i < aExpand.Len() )
//STRIP001      {
//STRIP001          ASSERT( aScrType[i] < SW_SCRIPTS, "Combined: Script fault" );
//STRIP001          if( !aWidth[ aScrType[i] ] )
//STRIP001          {
//STRIP001              rInf.GetOut()->SetFont( rInf.GetFont()->GetFnt( aScrType[i] ) );
//STRIP001              aWidth[ aScrType[i] ] = 2*
//STRIP001                          rInf.GetOut()->GetFontMetric().GetSize().Width()/3;
//STRIP001          }
//STRIP001          ++i;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  USHORT nTop = ( nCount + 1 ) / 2; // the first character of the second line
//STRIP001  ViewShell *pSh = rInf.GetTxtFrm()->GetShell();
//STRIP001  SwFont aTmpFont( *rInf.GetFont() );
//STRIP001  SwFontSave aFontSave( rInf, &aTmpFont );
//STRIP001  nProportion = 55;
//STRIP001  // In nMainAscent/Descent we store the ascent and descent
//STRIP001  // of the original surrounding font
//STRIP001  USHORT nMaxDescent, nMaxAscent, nMaxWidth;
//STRIP001  USHORT nMainDescent = rInf.GetFont()->GetHeight( pSh, rInf.GetOut() );
//STRIP001  const USHORT nMainAscent = rInf.GetFont()->GetAscent( pSh, rInf.GetOut() );
//STRIP001  nMainDescent -= nMainAscent;
//STRIP001  // we start with a 50% font, but if we notice that the combined portion
//STRIP001  // becomes bigger than the surrounding font, we check 45% and maybe 40%.
//STRIP001  do
//STRIP001  {
//STRIP001      nProportion -= 5;
//STRIP001      aTmpFont.SetProportion( nProportion );
//STRIP001      i = 0;
//STRIP001      memset( &aPos, 0, sizeof(aPos) );
//STRIP001      nMaxDescent = 0;
//STRIP001      nMaxAscent = 0;
//STRIP001      nMaxWidth = 0;
//STRIP001      nUpPos = nLowPos = 0;
//STRIP001
//STRIP001      // Now we get the width of all characters.
//STRIP001      // The ascent and the width of the first line are stored in the
//STRIP001      // ascent member of the portion, the descent in nLowPos.
//STRIP001      // The ascent, descent and width of the second line are stored in the
//STRIP001      // local nMaxAscent, nMaxDescent and nMaxWidth variables.
//STRIP001      while( i < nCount )
//STRIP001      {
//STRIP001          BYTE nScrp = aScrType[i];
//STRIP001          aTmpFont.SetActual( nScrp );
//STRIP001          if( aWidth[ nScrp ] )
//STRIP001          {
//STRIP001              Size aFontSize( aTmpFont.GetSize( nScrp ) );
//STRIP001              aFontSize.Width() = aWidth[ nScrp ];
//STRIP001              aTmpFont.SetSize( aFontSize, nScrp );
//STRIP001          }
//STRIP001
//STRIP001             SwDrawTextInfo aDrawInf( pSh, *rInf.GetOut(), 0, aExpand, i, 1 );
//STRIP001             Size aSize = aTmpFont._GetTxtSize( aDrawInf );
//STRIP001          USHORT nAsc = aTmpFont.GetAscent( pSh, rInf.GetOut() );
//STRIP001             aPos[ i ] = (USHORT)aSize.Width();
//STRIP001          if( i == nTop ) // enter the second line
//STRIP001          {
//STRIP001              nLowPos = nMaxDescent;
//STRIP001              Height( nMaxDescent + nMaxAscent );
//STRIP001              Width( nMaxWidth );
//STRIP001              SetAscent( nMaxAscent );
//STRIP001              nMaxAscent = 0;
//STRIP001              nMaxDescent = 0;
//STRIP001              nMaxWidth = 0;
//STRIP001          }
//STRIP001          nMaxWidth += aPos[ i++ ];
//STRIP001          if( nAsc > nMaxAscent )
//STRIP001              nMaxAscent = nAsc;
//STRIP001          if( aSize.Height() - nAsc > nMaxDescent )
//STRIP001              nMaxDescent = aSize.Height() - nAsc;
//STRIP001      }
//STRIP001      // for one or two characters we double the width of the portion
//STRIP001      if( nCount < 3 )
//STRIP001      {
//STRIP001          nMaxWidth *= 2;
//STRIP001          Width( 2*Width() );
//STRIP001          if( nCount < 2 )
//STRIP001          {
//STRIP001              Height( nMaxAscent + nMaxDescent );
//STRIP001              nLowPos = nMaxDescent;
//STRIP001          }
//STRIP001      }
//STRIP001      Height( Height() + nMaxDescent + nMaxAscent );
//STRIP001      nUpPos = nMaxAscent;
//STRIP001      SetAscent( Height() - nMaxDescent - nLowPos );
//STRIP001  } while( nProportion > 40 && ( GetAscent() > nMainAscent ||
//STRIP001                                  Height() - GetAscent() > nMainDescent ) );
//STRIP001  // if the combined portion is smaller than the surrounding text,
//STRIP001  // the portion grows. This looks better, if there's a character background.
//STRIP001  if( GetAscent() < nMainAscent )
//STRIP001  {
//STRIP001      Height( Height() + nMainAscent - GetAscent() );
//STRIP001      SetAscent( nMainAscent );
//STRIP001  }
//STRIP001  if( Height() < nMainAscent + nMainDescent )
//STRIP001      Height( nMainAscent + nMainDescent );
//STRIP001
//STRIP001  // We calculate the x positions of the characters in both lines..
//STRIP001  USHORT nTopDiff = 0;
//STRIP001  USHORT nBotDiff = 0;
//STRIP001  if( nMaxWidth > Width() )
//STRIP001  {
//STRIP001      nTopDiff = ( nMaxWidth - Width() ) / 2;
//STRIP001      Width( nMaxWidth );
//STRIP001  }
//STRIP001  else
//STRIP001      nBotDiff = ( Width() - nMaxWidth ) / 2;
//STRIP001  switch( nTop)
//STRIP001  {
//STRIP001      case 3: aPos[1] = aPos[0] + nTopDiff;  // no break
//STRIP001      case 2: aPos[nTop-1] = Width() - aPos[nTop-1];
//STRIP001  }
//STRIP001  aPos[0] = 0;
//STRIP001  switch( nCount )
//STRIP001  {
//STRIP001      case 5: aPos[4] = aPos[3] + nBotDiff;   // no break
//STRIP001      case 3: aPos[nTop] = nBotDiff;          break;
//STRIP001      case 6: aPos[4] = aPos[3] + nBotDiff;   // no break
//STRIP001      case 4: aPos[nTop] = 0;                 // no break
//STRIP001      case 2: aPos[nCount-1] = Width() - aPos[nCount-1];
//STRIP001  }
//STRIP001
//STRIP001  // Does the combined portion fit the line?
//STRIP001  const sal_Bool bFull = rInf.Width() < rInf.X() + Width();
//STRIP001  if( bFull )
//STRIP001  {
//STRIP001      if( rInf.GetLineStart() == rInf.GetIdx() && (!rInf.GetLast()->InFldGrp()
//STRIP001          || !((SwFldPortion*)rInf.GetLast())->IsFollow() ) )
//STRIP001             Width( (USHORT)( rInf.Width() - rInf.X() ) );
//STRIP001      else
//STRIP001      {
//STRIP001          Truncate();
//STRIP001          Width( 0 );
//STRIP001          SetLen( 0 );
//STRIP001          if( rInf.GetLast() )
//STRIP001              rInf.GetLast()->FormatEOL( rInf );
//STRIP001      }
//STRIP001  }
//STRIP001  return bFull;
//STRIP001 }

/*************************************************************************
 * SwCombinedPortion::GetViewWidth(..)
 *************************************************************************/

//STRIP001 KSHORT SwCombinedPortion::GetViewWidth( const SwTxtSizeInfo &rInf ) const
//STRIP001 {
//STRIP001  if( !GetLen() ) // for the dummy part at the end of the line, where
//STRIP001      return 0;   // the combined portion doesn't fit.
//STRIP001  return SwFldPortion::GetViewWidth( rInf );
//STRIP001 }
}
