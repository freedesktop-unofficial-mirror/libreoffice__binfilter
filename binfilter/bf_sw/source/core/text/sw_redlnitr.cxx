/*************************************************************************
 *
 *  $RCSfile: sw_redlnitr.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 15:35:29 $
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

#include "hintids.hxx"

#ifndef _SFX_WHITER_HXX //autogen
#include <svtools/whiter.hxx>
#endif
#ifndef _SHL_HXX
#include <tools/shl.hxx>
#endif
#ifndef _COM_SUN_STAR_I18N_SCRIPTTYPE_HDL_
#include <com/sun/star/i18n/ScriptType.hdl>
#endif

#ifndef _SWMODULE_HXX
#include <swmodule.hxx>
#endif
#ifndef _REDLINE_HXX
#include <redline.hxx>      // SwRedline
#endif
#ifndef _TXTATR_HXX
#include <txtatr.hxx>       // SwTxt ...
#endif
#ifndef _DOCARY_HXX
#include <docary.hxx>       // SwRedlineTbl
#endif
#ifndef _ITRATR_HXX
#include <itratr.hxx>       // SwAttrIter
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>        // SwTxtNode
#endif
#ifndef _SWFNTCCH_HXX
#include <swfntcch.hxx>     // SwFontAccess
#endif
#ifndef _DOC_HXX
#include <doc.hxx>          // SwDoc
#endif
#ifndef _TXATBASE_HXX
#include <txatbase.hxx>     // SwTxtAttr
#endif
#ifndef _ROOTFRM_HXX
#include <rootfrm.hxx>
#endif
#ifndef _FRMSH_HXX
#include <frmsh.hxx>
#endif
#ifndef _BREAKIT_HXX
#include <breakit.hxx>
#endif
#ifndef _ATRHNDL_HXX
#include <atrhndl.hxx>
#endif

//////////////////////////

#ifndef _SV_KEYCODES_HXX //autogen
#include <vcl/keycodes.hxx>
#endif
#ifndef _VCL_CMDEVT_HXX //autogen
#include <vcl/cmdevt.hxx>
#endif

#ifndef _SV_SETTINGS_HXX //autogen
#include <vcl/settings.hxx>
#endif

#ifndef _TXTFRM_HXX
#include <txtfrm.hxx>       // SwTxtFrm
#endif
#ifndef _APP_HXX //autogen
#include <vcl/svapp.hxx>
#endif
#ifndef _REDLNITR_HXX
#include <redlnitr.hxx>
#endif
#ifndef _EXTINPUT_HXX
#include <extinput.hxx>
#endif

#ifndef _SFX_PRINTER_HXX //autogen
#include <bf_sfx2/printer.hxx>
#endif
#ifndef _WINDOW_HXX //autogen
#include <vcl/window.hxx>
#endif
#ifndef _VIEWSH_HXX
#include <viewsh.hxx>   // ViewShell
#endif

using namespace ::com::sun::star;

extern BYTE WhichFont( xub_StrLen nIdx, const String* pTxt,
                       const SwScriptInfo* pSI );

/*************************************************************************
 *                      SwAttrIter::CtorInit()
 *************************************************************************/
/*N*/ void SwAttrIter::CtorInit( SwTxtNode& rTxtNode, SwScriptInfo& rScrInf, SwTxtFrm* pFrm )
/*N*/ {
/*N*/   // Beim HTML-Import kann es vorkommen, dass kein Layout existiert.
/*N*/   SwRootFrm *pRootFrm = rTxtNode.GetDoc()->GetRootFrm();
/*N*/   pShell = pRootFrm ? pRootFrm->GetShell() : 0;
/*N*/
/*N*/     pScriptInfo = &rScrInf;
/*N*/   pAttrSet = &rTxtNode.GetSwAttrSet();
/*N*/     pHints = rTxtNode.GetpSwpHints();
/*N*/
/*N*/     SwFontAccess aFontAccess( &rTxtNode.GetAnyFmtColl(), pShell );
/*N*/
/*N*/     delete pFnt;
/*N*/     pFnt = new SwFont( *aFontAccess.Get()->GetFont() );
/*N*/
/*N*/     // set font to vertical if frame layout is vertical
/*N*/     sal_Bool bVertLayout = sal_False;
/*N*/     sal_Bool bRTL = sal_False;
/*N*/     if ( pFrm )
/*N*/     {
/*N*/         if ( pFrm->IsVertical() )
/*N*/         {
/*N*/             bVertLayout = sal_True;
/*N*/             pFnt->SetVertical( pFnt->GetOrientation(), sal_True );
/*N*/         }
/*N*/         bRTL = pFrm->IsRightToLeft();
/*N*/     }
/*N*/
/*N*/     // Initialize the default attribute of the attribute handler
/*N*/     // based on the attribute array cached together with the font.
/*N*/     // If any further attributes for the paragraph are given in pAttrSet
/*N*/     // consider them during construction of the default array, and apply
/*N*/     // them to the font
/*N*/     aAttrHandler.Init( aFontAccess.Get()->GetDefault(),
/*N*/                        rTxtNode.HasSwAttrSet() ? pAttrSet : 0,
/*N*/                        *rTxtNode.GetDoc(), pShell, *pFnt, bVertLayout );
/*N*/
/*N*/   aMagicNo[SW_LATIN] = aMagicNo[SW_CJK] = aMagicNo[SW_CTL] = NULL;
/*N*/
/*N*/   // determine script changes if not already done for current paragraph
/*N*/   ASSERT( pScriptInfo, "No script info available");
/*N*/     if ( pScriptInfo->GetInvalidity() != STRING_LEN )
/*N*/          pScriptInfo->InitScriptInfo( rTxtNode, bRTL );
/*N*/
/*N*/   if ( pBreakIt->xBreak.is() )
/*N*/   {
/*N*/         pFnt->SetActual( WhichFont( 0, 0, pScriptInfo ) );
/*N*/
/*N*/         xub_StrLen nChg = 0;
/*N*/       USHORT nCnt = 0;
/*N*/
/*N*/         do
/*N*/       {
/*N*/           nChg = pScriptInfo->GetScriptChg( nCnt );
/*N*/             USHORT nScript = pScriptInfo->GetScriptType( nCnt++ );
/*N*/           BYTE nTmp = 4;
/*N*/           switch ( nScript ) {
/*N*/               case i18n::ScriptType::ASIAN :
/*N*/                   if( !aMagicNo[SW_CJK] ) nTmp = SW_CJK; break;
/*N*/               case i18n::ScriptType::COMPLEX :
/*N*/                   if( !aMagicNo[SW_CTL] ) nTmp = SW_CTL; break;
/*N*/               default:
/*N*/                   if( !aMagicNo[SW_LATIN ] ) nTmp = SW_LATIN;
/*N*/           }
/*N*/           if( nTmp < 4 )
/*N*/           {
/*N*/               pFnt->ChkMagic( pShell, nTmp );
/*N*/               pFnt->GetMagic( aMagicNo[ nTmp ], aFntIdx[ nTmp ], nTmp );
/*N*/           }
/*N*/       } while( nChg < rTxtNode.GetTxt().Len() );
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       pFnt->ChkMagic( pShell, SW_LATIN );
/*N*/       pFnt->GetMagic( aMagicNo[ SW_LATIN ], aFntIdx[ SW_LATIN ], SW_LATIN );
/*N*/   }
/*N*/
/*N*/     nStartIndex = nEndIndex = nPos = nChgCnt = 0;
/*N*/   nPropFont = 0;
/*N*/   SwDoc* pDoc = rTxtNode.GetDoc();
/*N*/
/*N*/   const SwExtTextInput* pExtInp = pDoc->GetExtTextInput( rTxtNode );
/*N*/   sal_Bool bShow = ::IsShowChanges( pDoc->GetRedlineMode() );
/*N*/     if( pExtInp || bShow )
/*N*/   {
/*N*/       MSHORT nRedlPos = pDoc->GetRedlinePos( rTxtNode );
/*N*/       if( pExtInp || MSHRT_MAX != nRedlPos )
/*N*/       {
/*N*/           const SvUShorts* pArr = 0;
/*N*/           xub_StrLen nInputStt = 0;
/*N*/           if( pExtInp )
/*N*/           {
/*N*/               pArr = &pExtInp->GetAttrs();
/*N*/               nInputStt = pExtInp->Start()->nContent.GetIndex();
/*N*/                 Seek( 0 );
/*N*/           }
/*N*/
/*N*/             pRedln = new SwRedlineItr( rTxtNode, *pFnt, aAttrHandler, nRedlPos,
/*N*/                                         bShow, pArr, nInputStt );
/*N*/
/*N*/           if( pRedln->IsOn() )
/*N*/               ++nChgCnt;
/*N*/       }
/*N*/   }
/*N*/ }

/*************************************************************************
 * SwRedlineItr - Der Redline-Iterator
 *
 * Folgende Informationen/Zustaende gibt es im RedlineIterator:
 *
 * nFirst ist der erste Index der RedlineTbl, der mit dem Absatz ueberlappt.
 *
 * nAct ist der zur Zeit aktive ( wenn bOn gesetzt ist ) oder der naechste
 * in Frage kommende Index.
 * nStart und nEnd geben die Grenzen des Objekts innerhalb des Absatzes an.
 *
 * Wenn bOn gesetzt ist, ist der Font entsprechend manipuliert worden.
 *
 * Wenn nAct auf MSHRT_MAX gesetzt wurde ( durch Reset() ), so ist zur Zeit
 * kein Redline aktiv, nStart und nEnd sind invalid.
 *************************************************************************/

//STRIP001 SwRedlineItr::SwRedlineItr( const SwTxtNode& rTxtNd, SwFont& rFnt,
//STRIP001     SwAttrHandler& rAH, MSHORT nRed, sal_Bool bShw, const SvUShorts *pArr,
//STRIP001     xub_StrLen nExtStart )
//STRIP001     : rDoc( *rTxtNd.GetDoc() ), rNd( rTxtNd ), rAttrHandler( rAH ),
//STRIP001    nNdIdx( rTxtNd.GetIndex() ), nFirst( nRed ),
//STRIP001    nAct( MSHRT_MAX ), bOn( sal_False ), pSet(0), bShow( bShw )
//STRIP001 {
//STRIP001     if( pArr )
//STRIP001         pExt = new SwExtend( *pArr, nExtStart );
//STRIP001     else
//STRIP001         pExt = NULL;
//STRIP001  Seek( rFnt, 0, STRING_LEN );
//STRIP001 }

//STRIP001 SwRedlineItr::~SwRedlineItr()
//STRIP001 {
//STRIP001  Clear( NULL );
//STRIP001  delete pSet;
//STRIP001  delete pExt;
//STRIP001 }

// Der Return-Wert von SwRedlineItr::Seek gibt an, ob der aktuelle Font
// veraendert wurde durch Verlassen (-1) oder Betreten eines Bereichs (+1)

//STRIP001 short SwRedlineItr::_Seek( SwFont& rFnt, xub_StrLen nNew, xub_StrLen nOld )
//STRIP001 {
//STRIP001  short nRet = 0;
//STRIP001  if( ExtOn() )
//STRIP001         return 0; // Abkuerzung: wenn wir innerhalb eines ExtendTextInputs sind
//STRIP001          // kann es keine anderen Attributwechsel (auch nicht durch Redlining) geben
//STRIP001  if( bShow )
//STRIP001  {
//STRIP001      if( bOn )
//STRIP001      {
//STRIP001          if( nNew >= nEnd )
//STRIP001          {
//STRIP001              --nRet;
//STRIP001              _Clear( &rFnt );    // Wir gehen hinter den aktuellen Bereich
//STRIP001              ++nAct;             // und pruefen gleich den naechsten
//STRIP001          }
//STRIP001          else if( nNew < nStart )
//STRIP001          {
//STRIP001              --nRet;
//STRIP001              _Clear( &rFnt );    // Wir gehen vor den aktuellen Bereich
//STRIP001              if( nAct > nFirst )
//STRIP001                  nAct = nFirst;  // Die Pruefung muss von vorne beginnen
//STRIP001              else
//STRIP001                  return nRet + EnterExtend( rFnt, nNew ); // Es gibt keinen vor uns.
//STRIP001          }
//STRIP001          else
//STRIP001              return nRet + EnterExtend( rFnt, nNew ); // Wir sind im gleichen Bereich geblieben.
//STRIP001      }
//STRIP001      if( MSHRT_MAX == nAct || nOld > nNew )
//STRIP001          nAct = nFirst;
//STRIP001
//STRIP001      nStart = STRING_LEN;
//STRIP001      nEnd = STRING_LEN;
//STRIP001
//STRIP001      for( ; nAct < rDoc.GetRedlineTbl().Count() ; ++nAct )
//STRIP001      {
//STRIP001             rDoc.GetRedlineTbl()[ nAct ]->CalcStartEnd( nNdIdx, nStart, nEnd );
//STRIP001
//STRIP001             if( nNew < nEnd )
//STRIP001          {
//STRIP001              if( nNew >= nStart ) // der einzig moegliche Kandidat
//STRIP001              {
//STRIP001                  bOn = sal_True;
//STRIP001                  const SwRedline *pRed = rDoc.GetRedlineTbl()[ nAct ];
//STRIP001
//STRIP001                  if (pSet)
//STRIP001                      pSet->ClearItem();
//STRIP001                  else
//STRIP001                  {
//STRIP001                      SwAttrPool& rPool = (SwAttrPool& )rDoc.GetAttrPool();
//STRIP001                      pSet = new SfxItemSet(rPool, RES_CHRATR_BEGIN, RES_CHRATR_END-1);
//STRIP001                  }
//STRIP001
//STRIP001                  if( 1 < pRed->GetStackCount() )
//STRIP001                      FillHints( pRed->GetAuthor( 1 ), pRed->GetType( 1 ) );
//STRIP001                  FillHints( pRed->GetAuthor(), pRed->GetType() );
//STRIP001
//STRIP001                  SfxWhichIter aIter( *pSet );
//STRIP001                  register MSHORT nWhich = aIter.FirstWhich();
//STRIP001                  while( nWhich )
//STRIP001                  {
//STRIP001                      const SfxPoolItem* pItem;
//STRIP001                      if( ( nWhich < RES_CHRATR_END ) &&
//STRIP001                          ( SFX_ITEM_SET == pSet->GetItemState( nWhich, sal_True, &pItem ) ) )
//STRIP001                      {
//STRIP001                          SwTxtAttr* pAttr = ((SwTxtNode&)rNd).MakeTmpTxtAttr(*pItem);
//STRIP001                             pAttr->SetPriorityAttr( sal_True );
//STRIP001                          aHints.C40_INSERT( SwTxtAttr, pAttr, aHints.Count());
//STRIP001                             rAttrHandler.PushAndChg( *pAttr, rFnt );
//STRIP001                          if( RES_CHRATR_COLOR == nWhich )
//STRIP001                              rFnt.SetNoCol( sal_True );
//STRIP001                      }
//STRIP001                      nWhich = aIter.NextWhich();
//STRIP001                  }
//STRIP001
//STRIP001                  ++nRet;
//STRIP001              }
//STRIP001              break;
//STRIP001          }
//STRIP001          nStart = STRING_LEN;
//STRIP001          nEnd = STRING_LEN;
//STRIP001      }
//STRIP001  }
//STRIP001  return nRet + EnterExtend( rFnt, nNew );
//STRIP001 }

//STRIP001 void SwRedlineItr::FillHints( MSHORT nAuthor, SwRedlineType eType )
//STRIP001 {
//STRIP001  switch ( eType )
//STRIP001  {
//STRIP001      case REDLINE_INSERT:
//STRIP001          SW_MOD()->GetInsertAuthorAttr(nAuthor, *pSet);
//STRIP001          break;
//STRIP001      case REDLINE_DELETE:
//STRIP001          SW_MOD()->GetDeletedAuthorAttr(nAuthor, *pSet);
//STRIP001          break;
//STRIP001      case REDLINE_FORMAT:
//STRIP001      case REDLINE_FMTCOLL:
//STRIP001          SW_MOD()->GetFormatAuthorAttr(nAuthor, *pSet);
//STRIP001          break;
//STRIP001  }
//STRIP001 }

//STRIP001 void SwRedlineItr::ChangeTxtAttr( SwFont* pFnt, SwTxtAttr &rHt, sal_Bool bChg )
//STRIP001 {
//STRIP001  ASSERT( IsOn(), "SwRedlineItr::ChangeTxtAttr: Off?" );
//STRIP001
//STRIP001     if( !bShow && !pExt )
//STRIP001         return;
//STRIP001
//STRIP001     if( bChg )
//STRIP001     {
//STRIP001         if ( pExt && pExt->IsOn() )
//STRIP001             rAttrHandler.PushAndChg( rHt, *pExt->GetFont() );
//STRIP001         else
//STRIP001             rAttrHandler.PushAndChg( rHt, *pFnt );
//STRIP001     }
//STRIP001     else
//STRIP001     {
//STRIP001         ASSERT( ! pExt || ! pExt->IsOn(), "Pop of attribute during opened extension" )
//STRIP001         rAttrHandler.PopAndChg( rHt, *pFnt );
//STRIP001     }
//STRIP001 }

//STRIP001 void SwRedlineItr::_Clear( SwFont* pFnt )
//STRIP001 {
//STRIP001  ASSERT( bOn, "SwRedlineItr::Clear: Off?" );
//STRIP001  bOn = sal_False;
//STRIP001  while( aHints.Count() )
//STRIP001  {
//STRIP001      SwTxtAttr *pPos = aHints[ 0 ];
//STRIP001      aHints.Remove(0);
//STRIP001         if( pFnt )
//STRIP001             rAttrHandler.PopAndChg( *pPos, *pFnt );
//STRIP001         else
//STRIP001             rAttrHandler.Pop( *pPos );
//STRIP001      delete pPos;
//STRIP001  }
//STRIP001  if( pFnt )
//STRIP001      pFnt->SetNoCol( sal_False );
//STRIP001 }

//STRIP001 xub_StrLen SwRedlineItr::_GetNextRedln( xub_StrLen nNext )
//STRIP001 {
//STRIP001  nNext = NextExtend( nNext );
//STRIP001  if( !bShow || MSHRT_MAX == nFirst )
//STRIP001      return nNext;
//STRIP001  if( MSHRT_MAX == nAct )
//STRIP001  {
//STRIP001      nAct = nFirst;
//STRIP001         rDoc.GetRedlineTbl()[ nAct ]->CalcStartEnd( nNdIdx, nStart, nEnd );
//STRIP001  }
//STRIP001  if( bOn || !nStart )
//STRIP001  {
//STRIP001      if( nEnd < nNext )
//STRIP001          nNext = nEnd;
//STRIP001  }
//STRIP001  else if( nStart < nNext )
//STRIP001      nNext = nStart;
//STRIP001  return nNext;
//STRIP001 }

//STRIP001 sal_Bool SwRedlineItr::_ChkSpecialUnderline() const
//STRIP001 {
//STRIP001  // Wenn die Unterstreichung oder das Escapement vom Redling kommt,
//STRIP001  // wenden wir immer das SpecialUnderlining, d.h. die Unterstreichung
//STRIP001  // unter der Grundlinie an.
//STRIP001  for( MSHORT i = 0; i < aHints.Count(); ++i )
//STRIP001  {
//STRIP001      SwTxtAttr *pPos = aHints[ i ];
//STRIP001      MSHORT nWhich = aHints[i]->Which();
//STRIP001      if( RES_CHRATR_UNDERLINE == nWhich ||
//STRIP001          RES_CHRATR_ESCAPEMENT == nWhich )
//STRIP001          return sal_True;
//STRIP001  }
//STRIP001  return sal_False;
//STRIP001 }

//STRIP001 sal_Bool SwRedlineItr::CheckLine( xub_StrLen nChkStart, xub_StrLen nChkEnd )
//STRIP001 {
//STRIP001  if( nFirst == MSHRT_MAX )
//STRIP001      return sal_False;
//STRIP001  if( nChkEnd == nChkStart ) // Leerzeilen gucken ein Zeichen weiter.
//STRIP001      ++nChkEnd;
//STRIP001  xub_StrLen nOldStart = nStart;
//STRIP001  xub_StrLen nOldEnd = nEnd;
//STRIP001  xub_StrLen nOldAct = nAct;
//STRIP001  sal_Bool bRet = sal_False;
//STRIP001
//STRIP001  for( nAct = nFirst; nAct < rDoc.GetRedlineTbl().Count() ; ++nAct )
//STRIP001  {
//STRIP001         rDoc.GetRedlineTbl()[ nAct ]->CalcStartEnd( nNdIdx, nStart, nEnd );
//STRIP001      if( nChkEnd < nStart )
//STRIP001          break;
//STRIP001      if( nChkStart <= nEnd && ( nChkEnd > nStart || STRING_LEN == nEnd ) )
//STRIP001      {
//STRIP001          bRet = sal_True;
//STRIP001          break;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  nStart = nOldStart;
//STRIP001  nEnd = nOldEnd;
//STRIP001  nAct = nOldAct;
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 void SwExtend::ActualizeFont( SwFont &rFnt, MSHORT nAttr )
//STRIP001 {
//STRIP001  if ( nAttr & EXTTEXTINPUT_ATTR_UNDERLINE )
//STRIP001      rFnt.SetUnderline( UNDERLINE_SINGLE );
//STRIP001  else if ( nAttr & EXTTEXTINPUT_ATTR_BOLDUNDERLINE )
//STRIP001      rFnt.SetUnderline( UNDERLINE_BOLD );
//STRIP001  else if ( nAttr & EXTTEXTINPUT_ATTR_DOTTEDUNDERLINE )
//STRIP001      rFnt.SetUnderline( UNDERLINE_DOTTED );
//STRIP001  else if ( nAttr & EXTTEXTINPUT_ATTR_DASHDOTUNDERLINE )
//STRIP001      rFnt.SetUnderline( UNDERLINE_DOTTED );
//STRIP001
//STRIP001  if ( nAttr & EXTTEXTINPUT_ATTR_REDTEXT )
//STRIP001      rFnt.SetColor( Color( COL_RED ) );
//STRIP001
//STRIP001  if ( nAttr & EXTTEXTINPUT_ATTR_HIGHLIGHT )
//STRIP001  {
//STRIP001      const StyleSettings& rStyleSettings = GetpApp()->GetSettings().GetStyleSettings();
//STRIP001      rFnt.SetColor( rStyleSettings.GetHighlightTextColor() );
//STRIP001         rFnt.SetBackColor( new Color( rStyleSettings.GetHighlightColor() ) );
//STRIP001  }
//STRIP001  if ( nAttr & EXTTEXTINPUT_ATTR_GRAYWAVELINE )
//STRIP001      rFnt.SetGreyWave( sal_True );
//STRIP001 }

//STRIP001 short SwExtend::Enter( SwFont& rFnt, xub_StrLen nNew )
//STRIP001 {
//STRIP001  ASSERT( !Inside(), "SwExtend: Enter without Leave" );
//STRIP001  ASSERT( !pFnt, "SwExtend: Enter with Font" );
//STRIP001  nPos = nNew;
//STRIP001  if( Inside() )
//STRIP001  {
//STRIP001      pFnt = new SwFont( rFnt );
//STRIP001         ActualizeFont( rFnt, rArr[ nPos - nStart ] );
//STRIP001      return 1;
//STRIP001  }
//STRIP001  return 0;
//STRIP001 }

//STRIP001 sal_Bool SwExtend::_Leave( SwFont& rFnt, xub_StrLen nNew )
//STRIP001 {
//STRIP001  ASSERT( Inside(), "SwExtend: Leave without Enter" );
//STRIP001  MSHORT nOldAttr = rArr[ nPos - nStart ];
//STRIP001  nPos = nNew;
//STRIP001  if( Inside() )
//STRIP001  {   // Wir sind innerhalb des ExtendText-Bereichs geblieben
//STRIP001      MSHORT nAttr = rArr[ nPos - nStart ];
//STRIP001      if( nOldAttr != nAttr ) // Gibt es einen (inneren) Attributwechsel?
//STRIP001      {
//STRIP001             rFnt = *pFnt;
//STRIP001             ActualizeFont( rFnt, nAttr );
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001         rFnt = *pFnt;
//STRIP001      delete pFnt;
//STRIP001      pFnt = NULL;
//STRIP001      return sal_True;
//STRIP001  }
//STRIP001  return sal_False;
//STRIP001 }

//STRIP001 xub_StrLen SwExtend::Next( xub_StrLen nNext )
//STRIP001 {
//STRIP001  if( nPos < nStart )
//STRIP001  {
//STRIP001      if( nNext > nStart )
//STRIP001          nNext = nStart;
//STRIP001  }
//STRIP001  else if( nPos < nEnd )
//STRIP001  {
//STRIP001      MSHORT nIdx = nPos - nStart;
//STRIP001      MSHORT nAttr = rArr[ nIdx ];
//STRIP001      while( ++nIdx < rArr.Count() && nAttr == rArr[ nIdx ] )
//STRIP001          ; //nothing
//STRIP001      nIdx += nStart;
//STRIP001      if( nNext > nIdx )
//STRIP001          nNext = nIdx;
//STRIP001  }
//STRIP001  return nNext;
//STRIP001 }
