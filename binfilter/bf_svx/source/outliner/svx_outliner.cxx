/*************************************************************************
 *
 *  $RCSfile: svx_outliner.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:40:37 $
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

#include <outl_pch.hxx>

#pragma hdrstop

#include <math.h>

#ifndef _SFXSTYLE_HXX //autogen
#include <svtools/style.hxx>
#endif
#ifndef _WRKWIN_HXX //autogen
#include <vcl/wrkwin.hxx>
#endif
//#ifndef _SYSTEM_HXX //autogen
//#include <vcl/system.hxx>
//#endif

#define _OUTLINER_CXX
#include <outliner.hxx>
#include <paralist.hxx>
#include <outlobj.hxx>
#include <outleeng.hxx>
#include <outlundo.hxx>
#include <eeitem.hxx>
#include <editstat.hxx>
#include <scripttypeitem.hxx>

#ifndef _EDITOBJ_HXX //autogen
#include <editobj.hxx>
#endif

#ifndef _SFXITEMSET_HXX //autogen
#include <svtools/itemset.hxx>
#endif

#ifndef _SFX_WHITER_HXX //autogen
#include <svtools/whiter.hxx>
#endif

#ifndef _SV_METRIC_HXX //autogen
#include <vcl/metric.hxx>
#endif

#ifndef _SVX_NUMITEM_HXX
#include <numitem.hxx>
#endif

#ifndef _SVX_ADJITEM_HXX
#include <adjitem.hxx>
#endif

#ifndef _SV_GRAPH_HXX //autogen
#include <vcl/graph.hxx>
#endif

#ifndef _GRFMGR_HXX
#include <goodies/grfmgr.hxx>
#endif

#ifndef _SVX_SVXFONT_HXX
#include <svxfont.hxx>
#endif

#ifndef _SVX_BRSHITEM_HXX
#include <brshitem.hxx>
#endif

#ifndef _SFXITEMPOOL_HXX
#include <svtools/itempool.hxx>
#endif

// #101498# calculate if it's RTL or not
#include <unicode/ubidi.h>
namespace binfilter {

/*N*/ #define DEFAULT_SCALE 75

/*N*/ static const USHORT nDefStyles = 3;   // Sonderbehandlung fuer die ersten 3 Ebenen
/*N*/ static const USHORT nDefBulletIndent = 800;
/*N*/ static const USHORT nDefBulletWidth = 700;
/*N*/ static const USHORT   pDefBulletIndents[nDefStyles]=  { 1400, 800, 800 };
/*N*/ static const USHORT   pDefBulletWidths[nDefStyles] =  { 1000, 850, 700 };

/*N*/ USHORT lcl_ImplGetDefBulletWidth( USHORT nDepth )
/*N*/ {
/*N*/   return ( nDepth < nDefStyles ) ? pDefBulletWidths[nDepth] : nDefBulletWidth;
/*N*/ }

/*N*/ USHORT lcl_ImplGetDefBulletIndent( USHORT nDepth )
/*N*/ {
/*N*/   USHORT nI = 0;
/*N*/   for ( USHORT n = 0; n <= nDepth; n++ )
/*N*/       nI += ( n < nDefStyles ) ? pDefBulletIndents[n] : nDefBulletIndent;
/*N*/   return nI;
/*N*/ }

/*N*/ SvxLRSpaceItem lcl_ImplGetDefLRSpaceItem( USHORT nDepth, MapUnit eMapUnit )
/*N*/ {
/*N*/   SvxLRSpaceItem aLRSpace( EE_PARA_OUTLLRSPACE );
/*N*/
/*N*/   long nWidth = OutputDevice::LogicToLogic( (long) lcl_ImplGetDefBulletWidth( nDepth ), MAP_100TH_MM, eMapUnit );
/*N*/   long nIndent = OutputDevice::LogicToLogic( (long) lcl_ImplGetDefBulletIndent( nDepth ), MAP_100TH_MM, eMapUnit );
/*N*/   aLRSpace.SetTxtLeft( (USHORT) nIndent );
/*N*/   aLRSpace.SetTxtFirstLineOfst( - (short)nWidth );
/*N*/
/*N*/   return aLRSpace;
/*N*/ }

// ----------------------------------------------------------------------
// Outliner
// ----------------------------------------------------------------------
/*N*/ DBG_NAME(Outliner)

/*N*/ void Outliner::ImplCheckDepth( USHORT& rnDepth ) const
/*N*/ {
/*N*/   if( rnDepth < nMinDepth )
/*N*/       rnDepth = nMinDepth;
/*N*/   else if( rnDepth > nMaxDepth )
/*N*/       rnDepth = nMaxDepth;
/*N*/ }

/*N*/ Paragraph* Outliner::Insert(const XubString& rText, ULONG nAbsPos, USHORT nDepth)
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); return NULL;//STRIP001
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  DBG_ASSERT(pParaList->GetParagraphCount(),"Insert:No Paras");
//STRIP001
//STRIP001  Paragraph* pPara;
//STRIP001
//STRIP001     ImplCheckDepth( nDepth );
//STRIP001
//STRIP001  ULONG nParagraphCount = pParaList->GetParagraphCount();
//STRIP001  if( nAbsPos > nParagraphCount )
//STRIP001      nAbsPos = nParagraphCount;
//STRIP001
//STRIP001  if( bFirstParaIsEmpty )
//STRIP001  {
//STRIP001      pPara = pParaList->GetParagraph( 0 );
//STRIP001      if( pPara->GetDepth() != nDepth )
//STRIP001      {
//STRIP001          nDepthChangedHdlPrevDepth = pPara->GetDepth();
//STRIP001          pPara->SetDepth( nDepth );
//STRIP001          pHdlParagraph = pPara;
//STRIP001          DepthChangedHdl();
//STRIP001      }
//STRIP001      pPara->nFlags |= PARAFLAG_HOLDDEPTH;
//STRIP001      SetText( rText, pPara );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      BOOL bUpdate = pEditEngine->GetUpdateMode();
//STRIP001      pEditEngine->SetUpdateMode( FALSE );
//STRIP001         ImplBlockInsertionCallbacks( TRUE );
//STRIP001      pPara = new Paragraph( nDepth );
//STRIP001      pParaList->Insert( pPara, nAbsPos );
//STRIP001      pEditEngine->InsertParagraph( (USHORT)nAbsPos, String() );
//STRIP001      DBG_ASSERT(pPara==pParaList->GetParagraph(nAbsPos),"Insert:Failed");
//STRIP001      ImplInitDepth( (USHORT)nAbsPos, nDepth, FALSE );
//STRIP001      pHdlParagraph = pPara;
//STRIP001      ParagraphInsertedHdl();
//STRIP001      pPara->nFlags |= PARAFLAG_HOLDDEPTH;
//STRIP001      SetText( rText, pPara );
//STRIP001      ImplBlockInsertionCallbacks( FALSE );
//STRIP001      pEditEngine->SetUpdateMode( bUpdate );
//STRIP001  }
//STRIP001  bFirstParaIsEmpty = FALSE;
//STRIP001  DBG_ASSERT(pEditEngine->GetParagraphCount()==pParaList->GetParagraphCount(),"SetText failed")
//STRIP001  return pPara;
/*N*/ }


/*N*/ void Outliner::ParagraphInserted( USHORT nPara )
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/
/*N*/   if ( bBlockInsCallback )
/*N*/       return;
/*N*/
/*N*/   if( bPasting || pEditEngine->IsInUndo() )
/*N*/   {
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 Paragraph* pPara = new Paragraph( 0xffff );
//STRIP001 /*?*/        pParaList->Insert( pPara, nPara );
//STRIP001 /*?*/        if( pEditEngine->IsInUndo() )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            pPara->nFlags = PARAFLAG_SETBULLETTEXT;
//STRIP001 /*?*/            pPara->bVisible = TRUE;
//STRIP001 /*?*/            const SfxUInt16Item& rLevel = (const SfxUInt16Item&) pEditEngine->GetParaAttrib( nPara, EE_PARA_OUTLLEVEL );
//STRIP001 /*?*/            pPara->SetDepth( rLevel.GetValue() );
//STRIP001 /*?*/        }
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       USHORT nDepth = 0;
/*N*/       if ( nPara )
/*N*/           nDepth = pParaList->GetParagraph( nPara-1 )->GetDepth();
/*N*/
/*N*/       Paragraph* pPara = new Paragraph( nDepth );
/*N*/       pParaList->Insert( pPara, nPara );
/*N*/
/*N*/       if( !pEditEngine->IsInUndo() )
/*N*/       {
/*N*/           ImplCalcBulletText( nPara, TRUE, FALSE );
/*N*/           pHdlParagraph = pPara;
/*N*/           ParagraphInsertedHdl();
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ void Outliner::ParagraphDeleted( USHORT nPara )
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/
/*N*/   if ( bBlockInsCallback || ( nPara == EE_PARA_ALL ) )
/*N*/       return;
/*N*/
/*N*/   Paragraph* pPara = pParaList->GetParagraph( nPara );
/*N*/   USHORT nDepth = pPara->GetDepth();
/*N*/
/*N*/   if( !pEditEngine->IsInUndo() )
/*N*/   {
/*N*/       pHdlParagraph = pPara;
/*N*/       ParagraphRemovingHdl();
/*N*/   }
/*N*/
/*N*/   pParaList->Remove( nPara );
/*N*/   delete pPara;
/*N*/
/*N*/   if( !pEditEngine->IsInUndo() && !bPasting )
/*N*/   {
/*N*/       pPara = pParaList->GetParagraph( nPara );
/*N*/       if ( pPara && ( pPara->GetDepth() > nDepth ) )
/*N*/       {
/*?*/           ImplCalcBulletText( nPara, TRUE, FALSE );
/*?*/           // naechsten auf gleicher Ebene suchen...
/*?*/           while ( pPara && pPara->GetDepth() > nDepth )
/*?*/               pPara = pParaList->GetParagraph( ++nPara );
/*N*/       }
/*N*/
/*N*/       if ( pPara && ( pPara->GetDepth() == nDepth ) )
/*?*/           ImplCalcBulletText( nPara, TRUE, FALSE );
/*N*/   }
/*N*/ }

/*N*/ void Outliner::Init( USHORT nMode )
/*N*/ {
/*N*/   nOutlinerMode = nMode;
/*N*/
/*N*/   Clear();
/*N*/
/*N*/   ULONG nCtrl = pEditEngine->GetControlWord();
/*N*/   nCtrl &= ~(EE_CNTRL_OUTLINER|EE_CNTRL_OUTLINER2);
/*N*/
/*N*/   switch ( ImplGetOutlinerMode() )
/*N*/   {
/*N*/       case OUTLINERMODE_TEXTOBJECT:
/*N*/       {
/*N*/           SetMinDepth( 0 );
/*N*/           SetMaxDepth( 9 );
/*N*/       }
/*N*/       break;
/*N*/       case OUTLINERMODE_TITLEOBJECT:
/*N*/       {
/*N*/           SetMinDepth( 0 );
/*N*/           SetMaxDepth( 9 );
/*N*/       }
/*N*/       break;
/*N*/       case OUTLINERMODE_OUTLINEOBJECT:
/*N*/       {
/*N*/           SetMinDepth( 1 );
/*N*/           SetMaxDepth( 9 );
/*N*/           nCtrl |= EE_CNTRL_OUTLINER2;
/*N*/       }
/*N*/       break;
/*N*/       case OUTLINERMODE_OUTLINEVIEW:
/*N*/       {
/*?*/           SetMinDepth( 0 );
/*?*/           SetMaxDepth( 9 );
/*?*/           nCtrl |= EE_CNTRL_OUTLINER;
/*N*/       }
/*N*/       break;
/*N*/       default: DBG_ERROR( "Outliner::Init - Invalid Mode!" );
/*N*/   }
/*N*/
/*N*/   pEditEngine->SetControlWord( nCtrl );
/*N*/
/*N*/   ImplInitDepth( 0, GetMinDepth(), FALSE );
/*N*/
/*N*/ #ifndef SVX_LIGHT
/*N*/   GetUndoManager().Clear();
/*N*/ #endif
/*N*/ }

/*N*/ void Outliner::SetMinDepth( USHORT nDepth, BOOL bCheckParagraphs )
/*N*/ {
/*N*/   if( nMinDepth != nDepth )
/*N*/   {
/*N*/       nMinDepth = nDepth;
/*N*/
/*N*/       if( bCheckParagraphs && nMinDepth )
/*N*/       {
/*?*/           // Prueft nur dass kein Absatz kleiner ist,
/*?*/           // es werden keine Ebenen proportional verschoben!
/*?*/           USHORT nParagraphs = (USHORT)pParaList->GetParagraphCount();
/*?*/           for ( USHORT nPara = 0; nPara < nParagraphs; nPara++ )
/*?*/           {
/*?*/               Paragraph* pPara = pParaList->GetParagraph( nPara );
/*?*/               if( pPara->GetDepth() < nMinDepth )
/*?*/               {
/*?*/                   SetDepth( pPara, nMinDepth );
/*?*/               }
/*?*/           }
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ void Outliner::SetMaxDepth( USHORT nDepth, BOOL bCheckParagraphs )
/*N*/ {
/*N*/   if( nMaxDepth != nDepth )
/*N*/   {
/*?*/       nMaxDepth = Min( nDepth, (USHORT)(SVX_MAX_NUM-1) );
/*?*/
/*?*/       if( bCheckParagraphs )
/*?*/       {
/*?*/           USHORT nParagraphs = (USHORT)pParaList->GetParagraphCount();
/*?*/           for ( USHORT nPara = 0; nPara < nParagraphs; nPara++ )
/*?*/           {
/*?*/               Paragraph* pPara = pParaList->GetParagraph( nPara );
/*?*/               if( pPara->GetDepth() > nMaxDepth )
/*?*/               {
/*?*/                   SetDepth( pPara, nMaxDepth );
/*?*/               }
/*?*/           }
/*?*/       }
/*N*/   }
/*N*/ }

/*N*/ USHORT Outliner::GetDepth( USHORT nPara ) const
/*N*/ {
/*N*/   Paragraph* pPara = pParaList->GetParagraph( nPara );
/*N*/   DBG_ASSERT( pPara, "Outliner::GetDepth - Paragraph not found!" );
/*N*/   return pPara ? pPara->GetDepth() : 0;
/*N*/ }

/*N*/ void Outliner::SetDepth( Paragraph* pPara, USHORT nNewDepth )
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/
/*N*/     ImplCheckDepth( nNewDepth );
/*N*/
/*N*/   if ( nNewDepth != pPara->GetDepth() )
/*N*/   {
/*N*/       nDepthChangedHdlPrevDepth = pPara->GetDepth();
/*N*/       pHdlParagraph = pPara;
/*N*/
/*N*/       ImplInitDepth( (USHORT) GetAbsPos( pPara ), nNewDepth, TRUE );
/*N*/
/*N*/       DepthChangedHdl();
/*N*/   }
/*N*/ }

/*N*/ OutlinerParaObject* Outliner::CreateParaObject( USHORT nStartPara, USHORT nCount ) const
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/
/*N*/   if ( ( nStartPara + nCount ) > pParaList->GetParagraphCount() )
/*N*/       nCount = pParaList->GetParagraphCount() - nStartPara;
/*N*/
/*N*/   if( !nCount )
/*N*/       return NULL;
/*N*/
/*N*/   OutlinerParaObject* pPObj = new OutlinerParaObject( nCount );
/*N*/   pPObj->pText = pEditEngine->CreateTextObject( nStartPara, nCount );
/*N*/   pPObj->SetOutlinerMode( GetMode() );
/*N*/   pPObj->bIsEditDoc = ( ImplGetOutlinerMode() == OUTLINERMODE_TEXTOBJECT ) ? TRUE : FALSE;
/*N*/
/*N*/   USHORT nLastPara = nStartPara + nCount - 1;
/*N*/   for ( USHORT nPara = nStartPara; nPara <= nLastPara; nPara++ )
/*N*/       pPObj->pDepthArr[ nPara-nStartPara] = GetDepth( nPara );
/*N*/
/*N*/   return pPObj;
/*N*/ }

/*N*/ void Outliner::SetText( const XubString& rText, Paragraph* pPara )
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   DBG_ASSERT(pPara,"SetText:No Para")
/*N*/
/*N*/   BOOL bUpdate = pEditEngine->GetUpdateMode();
/*N*/   pEditEngine->SetUpdateMode( FALSE );
/*N*/   ImplBlockInsertionCallbacks( TRUE );
/*N*/
/*N*/   USHORT nPara = (USHORT)pParaList->GetAbsPos( pPara );
/*N*/
/*N*/   if( !rText.Len() )
/*N*/   {
/*N*/       pEditEngine->SetText( nPara, rText );
/*N*/       ImplInitDepth( nPara, pPara->GetDepth(), FALSE );
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       XubString aText( rText );
/*N*/       aText.ConvertLineEnd( LINEEND_LF );
/*N*/
/*N*/       if( aText.GetChar( aText.Len()-1 ) == '\x0A' )
/*?*/           aText.Erase( aText.Len()-1, 1 ); // letzten Umbruch loeschen
/*N*/
/*N*/       USHORT nCount = aText.GetTokenCount( '\x0A' );
/*N*/       USHORT nPos = 0;
/*N*/       USHORT nInsPos = nPara+1;
/*N*/       while( nCount > nPos )
/*N*/       {
/*N*/           XubString aStr = aText.GetToken( nPos, '\x0A' );
/*N*/
/*N*/           USHORT nCurDepth;
/*N*/           if( nPos )
/*N*/           {
/*N*/               pPara = new Paragraph( 0 );
/*N*/               nCurDepth = 0;
/*N*/           }
/*N*/           else
/*N*/               nCurDepth = pPara->GetDepth();
/*N*/
/*N*/           // Im Outliner-Modus die Tabulatoren filtern und die
/*N*/           // Einrueckung ueber ein LRSpaceItem einstellen
/*N*/           // Im EditEngine-Modus ueber Maltes Tabulatoren einruecken
/*N*/           if( ( ImplGetOutlinerMode() == OUTLINERMODE_OUTLINEOBJECT ) ||
/*N*/               ( ImplGetOutlinerMode() == OUTLINERMODE_OUTLINEVIEW ) )
/*N*/           {
/*N*/               // Tabs raus
/*N*/               USHORT nTabs = 0;
/*N*/               while ( ( nTabs < aStr.Len() ) && ( aStr.GetChar( nTabs ) == '\t' ) )
/*N*/                   nTabs++;
/*N*/               if ( nTabs )
/*N*/                   aStr.Erase( 0, nTabs );
/*N*/
/*N*/               // Tiefe beibehalten ?  (siehe Outliner::Insert)
/*N*/               if( !(pPara->nFlags & PARAFLAG_HOLDDEPTH) )
/*N*/               {
/*N*/                   nCurDepth = nTabs;
/*N*/                   ImplCheckDepth( nCurDepth );
/*N*/                   pPara->SetDepth( nCurDepth );
/*N*/                   pPara->nFlags &= (~PARAFLAG_HOLDDEPTH);
/*N*/               }
/*N*/           }
/*N*/           if( nPos ) // nicht mit dem ersten Absatz
/*N*/           {
/*N*/               pParaList->Insert( pPara, nInsPos );
/*N*/               pEditEngine->InsertParagraph( nInsPos, aStr );
/*N*/               pHdlParagraph = pPara;
/*N*/               ParagraphInsertedHdl();
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               nInsPos--;
/*N*/               pEditEngine->SetText( nInsPos, aStr );
/*N*/           }
/*N*/           ImplInitDepth( nInsPos, nCurDepth, FALSE );
/*N*/           nInsPos++;
/*N*/           nPos++;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   DBG_ASSERT(pParaList->GetParagraphCount()==pEditEngine->GetParagraphCount(),"SetText failed!")
/*N*/   bFirstParaIsEmpty = FALSE;
/*N*/   ImplBlockInsertionCallbacks( FALSE );
/*N*/   pEditEngine->SetUpdateMode( bUpdate );
/*N*/ }

// pView == 0 -> Tabulatoren nicht beachten

//STRIP001 BOOL Outliner::ImpConvertEdtToOut(Paragraph* pPara,ULONG nPara,EditView* pView)
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  DBG_ASSERT(pPara,"FilterTabs:No Para");
//STRIP001
//STRIP001  BOOL bConverted = FALSE;
//STRIP001  USHORT nTabs = 0;
//STRIP001  ESelection aDelSel;
//STRIP001
//STRIP001  const SfxItemSet& rAttrs = pEditEngine->GetParaAttribs( (USHORT)nPara );
//STRIP001  BOOL bAlreadyOutliner = rAttrs.GetItemState( EE_PARA_OUTLLRSPACE ) == SFX_ITEM_ON ? TRUE : FALSE;
//STRIP001
//STRIP001  XubString aName;
//STRIP001  XubString aHeading_US( RTL_CONSTASCII_USTRINGPARAM( "Heading" ) );
//STRIP001  XubString aHeading_GERM( RTL_CONSTASCII_USTRINGPARAM( "berschrift" ) );
//STRIP001  XubString aNumber_GERM( RTL_CONSTASCII_USTRINGPARAM( "Numerierung" ) );
//STRIP001
//STRIP001  XubString aStr( pEditEngine->GetText( (USHORT)nPara ) );
//STRIP001  xub_Unicode* pPtr = (xub_Unicode*)aStr.GetBuffer();
//STRIP001
//STRIP001  USHORT nHeadingNumberStart = 0;
//STRIP001  USHORT nNumberingNumberStart = 0;
//STRIP001  SfxStyleSheet* pStyle= pEditEngine->GetStyleSheet( (USHORT)nPara );
//STRIP001  if( pStyle )
//STRIP001  {
//STRIP001      aName = pStyle->GetName();
//STRIP001      USHORT nSearch;
//STRIP001      if ( ( nSearch = aName.Search( aHeading_US ) ) != STRING_NOTFOUND )
//STRIP001          nHeadingNumberStart = nSearch + aHeading_US.Len();
//STRIP001      else if ( ( nSearch = aName.Search( aHeading_GERM ) ) != STRING_NOTFOUND )
//STRIP001          nHeadingNumberStart = nSearch + aHeading_GERM.Len();
//STRIP001      else if ( ( nSearch = aName.Search( aNumber_GERM ) ) != STRING_NOTFOUND )
//STRIP001          nNumberingNumberStart = nSearch + aNumber_GERM.Len();
//STRIP001  }
//STRIP001
//STRIP001  if ( nHeadingNumberStart || nNumberingNumberStart )
//STRIP001  {
//STRIP001      // PowerPoint-Import ?
//STRIP001      if( nHeadingNumberStart && ( aStr.Len() >= 2 ) &&
//STRIP001              ( pPtr[0] != '\t' ) && ( pPtr[1] == '\t' ) )
//STRIP001      {
//STRIP001          // Bullet & Tab raus
//STRIP001          aDelSel = ESelection( (USHORT)nPara, 0, (USHORT)nPara, 2 );
//STRIP001      }
//STRIP001
//STRIP001      USHORT nPos = nHeadingNumberStart ? nHeadingNumberStart : nNumberingNumberStart;
//STRIP001      String aLevel = aName.Copy( nPos );
//STRIP001      aLevel.EraseLeadingChars( ' ' );
//STRIP001      nTabs = aLevel.ToInt32();
//STRIP001      if( nTabs )
//STRIP001          nTabs--; // ebene 0 = "heading 1"
//STRIP001      bConverted = TRUE;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      //  Fuehrende Tabulatoren filtern
//STRIP001      while( *pPtr == '\t' )
//STRIP001      {
//STRIP001          pPtr++;
//STRIP001          nTabs++;
//STRIP001      }
//STRIP001      // Tabulatoren aus dem Text entfernen
//STRIP001      if( nTabs )
//STRIP001          aDelSel = ESelection( (USHORT)nPara, 0, (USHORT)nPara, nTabs );
//STRIP001
//STRIP001      //  LRSpaceItem aufaddieren
//STRIP001      const SvxLRSpaceItem& rIndent=(const SvxLRSpaceItem&)rAttrs.Get( bAlreadyOutliner ? EE_PARA_OUTLLRSPACE : EE_PARA_LRSPACE );
//STRIP001      USHORT nIndent = rIndent.GetTxtLeft();
//STRIP001      if( nIndent )
//STRIP001      {
//STRIP001          USHORT nOffs = nIndent / (USHORT)pEditEngine->GetDefTab();
//STRIP001          if( !nOffs )
//STRIP001              nOffs = 1;  // immer mind. 1 Tab
//STRIP001          nTabs += nOffs;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if ( aDelSel.HasRange() )
//STRIP001  {
//STRIP001      if ( pView )
//STRIP001      {
//STRIP001          pView->SetSelection( aDelSel );
//STRIP001          pView->DeleteSelected();
//STRIP001      }
//STRIP001      else
//STRIP001          pEditEngine->QuickDelete( aDelSel );
//STRIP001  }
//STRIP001
//STRIP001  // MT: OutlLevel wird beim RTF-Import von der EditEngine eingestellt,
//STRIP001  // weil String-Vergleich vom Vorlagen-Namen unbrauchbar
//STRIP001     // Und für das Binaer-Format gilt der Level sowieso...
//STRIP001     // => Einiges von oben kann bestimmt entfallen, oder?
//STRIP001     USHORT nOutlLevel = nMinDepth;
//STRIP001     if ( nPara )
//STRIP001     {
//STRIP001      const SfxUInt16Item& rLevel = (const SfxUInt16Item&) pEditEngine->GetParaAttrib( nPara, EE_PARA_OUTLLEVEL );
//STRIP001      nOutlLevel = rLevel.GetValue();
//STRIP001     }
//STRIP001     ImplCheckDepth( nOutlLevel );
//STRIP001
//STRIP001     SfxItemSet aOldAttrs( GetParaAttribs( nPara ) );
//STRIP001  ImplInitDepth( nPara, nOutlLevel, FALSE );
//STRIP001  if ( !ImplHasBullet( nPara ) && aOldAttrs.GetItemState( EE_PARA_LRSPACE ) == SFX_ITEM_ON )
//STRIP001  {
//STRIP001         // #96298# ImplInitDepth overwrite LRSpace to depth default, but we want to keep it,
//STRIP001         // when hard set in RTF
//STRIP001      SfxItemSet aAttrs( GetParaAttribs( nPara ) );
//STRIP001      aAttrs.Put( aOldAttrs.Get( EE_PARA_LRSPACE ) );
//STRIP001      SetParaAttribs( nPara, aAttrs );
//STRIP001  }
//STRIP001
//STRIP001  return bConverted;
//STRIP001 }

/*N*/ void Outliner::SetText( const OutlinerParaObject& rPObj )
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/
/*N*/   BOOL bUpdate = pEditEngine->GetUpdateMode();
/*N*/   pEditEngine->SetUpdateMode( FALSE );
/*N*/
/*N*/   BOOL bUndo = pEditEngine->IsUndoEnabled();
/*N*/   EnableUndo( FALSE );
/*N*/
/*N*/   Init( rPObj.GetOutlinerMode() );
/*N*/
/*N*/   ImplBlockInsertionCallbacks( TRUE );
/*N*/   pEditEngine->SetText( *(rPObj.pText) );
/*N*/   bFirstParaIsEmpty = FALSE;
/*N*/
/*N*/   pParaList->Clear( TRUE );
/*N*/   for( USHORT nCurPara = 0; nCurPara < rPObj.nCount; nCurPara++ )
/*N*/   {
/*N*/         USHORT nDepth = rPObj.pDepthArr[ nCurPara ];
/*N*/         ImplCheckDepth( nDepth );
/*N*/       Paragraph* pPara = new Paragraph( nDepth );
/*N*/       pParaList->Insert( pPara, LIST_APPEND );
/*N*/       ImplCheckNumBulletItem( nCurPara );
/*N*/   }
/*N*/
/*N*/   ImplCheckParagraphs( 0, (USHORT) (pParaList->GetParagraphCount()-1) );
/*N*/
/*N*/   EnableUndo( bUndo );
/*N*/   ImplBlockInsertionCallbacks( FALSE );
/*N*/   pEditEngine->SetUpdateMode( bUpdate );
/*N*/
/*N*/   DBG_ASSERT( pParaList->GetParagraphCount()==rPObj.Count(),"SetText failed")
/*N*/   DBG_ASSERT( pEditEngine->GetParagraphCount()==rPObj.Count(),"SetText failed")
/*N*/ }

//STRIP001 void Outliner::AddText( const OutlinerParaObject& rPObj )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  Paragraph* pPara;
//STRIP001
//STRIP001  ULONG nCount = rPObj.Count();
//STRIP001
//STRIP001  BOOL bUpdate = pEditEngine->GetUpdateMode();
//STRIP001  pEditEngine->SetUpdateMode( FALSE );
//STRIP001
//STRIP001  ImplBlockInsertionCallbacks( TRUE );
//STRIP001  ULONG nPara;
//STRIP001  if( bFirstParaIsEmpty )
//STRIP001  {
//STRIP001      pParaList->Clear( TRUE );
//STRIP001      pEditEngine->SetText( *(rPObj.pText) );
//STRIP001      nPara = 0;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      nPara = pParaList->GetParagraphCount();
//STRIP001      pEditEngine->InsertParagraph( EE_PARA_APPEND, *(rPObj.pText) );
//STRIP001  }
//STRIP001  bFirstParaIsEmpty = FALSE;
//STRIP001
//STRIP001  for( USHORT n = 0; n < rPObj.nCount; n++ )
//STRIP001  {
//STRIP001      pPara = new Paragraph( rPObj.pDepthArr[ n ] );
//STRIP001      pParaList->Insert( pPara, LIST_APPEND );
//STRIP001      USHORT nP = nPara+n;
//STRIP001      DBG_ASSERT(pParaList->GetAbsPos(pPara)==nP,"AddText:Out of sync")
//STRIP001      ImplInitDepth( nP, pPara->GetDepth(), FALSE );
//STRIP001  }
//STRIP001  DBG_ASSERT( pEditEngine->GetParagraphCount()==pParaList->GetParagraphCount(), "SetText: OutOfSync" );
//STRIP001
//STRIP001  ImplCheckParagraphs( (USHORT)nPara, (USHORT) (pParaList->GetParagraphCount()-1) );
//STRIP001
//STRIP001  ImplBlockInsertionCallbacks( FALSE );
//STRIP001  pEditEngine->SetUpdateMode( bUpdate );
//STRIP001 }

//STRIP001 void __EXPORT Outliner::FieldClicked( const SvxFieldItem& rField, USHORT nPara, USHORT nPos )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001
//STRIP001  if ( aFieldClickedHdl.IsSet() )
//STRIP001  {
//STRIP001      EditFieldInfo aFldInfo( this, rField, nPara, nPos );
//STRIP001      aFldInfo.SetSimpleClick( TRUE );
//STRIP001      aFieldClickedHdl.Call( &aFldInfo );
//STRIP001  }
//STRIP001 }


//STRIP001 void __EXPORT Outliner::FieldSelected( const SvxFieldItem& rField, USHORT nPara, USHORT nPos )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  if ( !aFieldClickedHdl.IsSet() )
//STRIP001      return;
//STRIP001
//STRIP001  EditFieldInfo aFldInfo( this, rField, nPara, nPos );
//STRIP001  aFldInfo.SetSimpleClick( FALSE );
//STRIP001  aFieldClickedHdl.Call( &aFldInfo );
//STRIP001 }


/*N*/ XubString __EXPORT Outliner::CalcFieldValue( const SvxFieldItem& rField, USHORT nPara, USHORT nPos, Color*& rpTxtColor, Color*& rpFldColor )
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   if ( !aCalcFieldValueHdl.IsSet() )
/*N*/       return String( ' ' );
/*N*/
/*N*/   EditFieldInfo aFldInfo( this, rField, nPara, nPos );
/*N*/   // Die FldColor ist mit COL_LIGHTGRAY voreingestellt.
/*N*/   if ( rpFldColor )
/*N*/       aFldInfo.SetFldColor( *rpFldColor );
/*N*/
/*N*/   aCalcFieldValueHdl.Call( &aFldInfo );
/*N*/   if ( aFldInfo.GetTxtColor() )
/*N*/   {
/*N*/       delete rpTxtColor;
/*N*/       rpTxtColor = new Color( *aFldInfo.GetTxtColor() );
/*N*/   }
/*N*/
/*N*/   delete rpFldColor;
/*N*/   rpFldColor = aFldInfo.GetFldColor() ? new Color( *aFldInfo.GetFldColor() ) : 0;
/*N*/
/*N*/   return aFldInfo.GetRepresentation();
/*N*/ }

/*N*/ void Outliner::SetStyleSheet( ULONG nPara, SfxStyleSheet* pStyle )
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   pEditEngine->SetStyleSheet( (USHORT)nPara, pStyle );
/*N*/
/*N*/   Paragraph* pPara = pParaList->GetParagraph( nPara );
/*N*/   pPara->nFlags |= PARAFLAG_SETBULLETTEXT;
/*N*/
/*N*/   ImplCheckNumBulletItem( (USHORT) nPara );
/*N*/ }

//STRIP001 void Outliner::SetVisible( Paragraph* pPara, BOOL bVisible )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  DBG_ASSERT( pPara, "SetVisible: pPara = NULL" );
//STRIP001
//STRIP001  pPara->bVisible = bVisible;
//STRIP001  ULONG nPara = pParaList->GetAbsPos( pPara );
//STRIP001  pEditEngine->ShowParagraph( (USHORT)nPara, bVisible );
//STRIP001 }

/*N*/ void Outliner::ImplCheckNumBulletItem( USHORT nPara )
/*N*/ {
/*N*/   Paragraph* pPara = pParaList->GetParagraph( nPara );
/*N*/
/*N*/   // Wenn es ein SvxNumBulletItem gibt, ueberschreibt dieses die
/*N*/   // Einstellungen von BulletItem und LRSpaceItem.
/*N*/     const SvxNumberFormat* pFmt = ImplGetBullet( nPara );
/*N*/   if ( pFmt )
/*N*/   {
/*N*/       SvxLRSpaceItem aNewLRSpace( EE_PARA_LRSPACE );
/*N*/       aNewLRSpace.SetTxtFirstLineOfst( pFmt->GetFirstLineOffset() );
/*N*/       aNewLRSpace.SetTxtLeft( pFmt->GetAbsLSpace() );
/*N*/       if ( pEditEngine->HasParaAttrib( nPara, EE_PARA_LRSPACE ) )
/*N*/       {
/*N*/           const SvxLRSpaceItem& rOldLRSpace = (const SvxLRSpaceItem&)pEditEngine->GetParaAttrib( nPara, EE_PARA_LRSPACE );
/*N*/           aNewLRSpace.SetRight( rOldLRSpace.GetRight() );
/*N*/       }
/*N*/       SfxItemSet aAttrs( pEditEngine->GetParaAttribs( nPara ) );
/*N*/       aAttrs.Put( aNewLRSpace);
/*N*/       pPara->aBulSize.Width() = -1;
/*N*/       pEditEngine->SetParaAttribs( nPara, aAttrs );
/*N*/   }
/*N*/ }

/*N*/ void Outliner::ImplSetLevelDependendStyleSheet( USHORT nPara, SfxStyleSheet* pLevelStyle )
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/
/*N*/   DBG_ASSERT( ( ImplGetOutlinerMode() == OUTLINERMODE_OUTLINEOBJECT ) || ( ImplGetOutlinerMode() == OUTLINERMODE_OUTLINEVIEW ), "SetLevelDependendStyleSheet: Wrong Mode!" );
/*N*/
/*N*/     SfxStyleSheet* pStyle = pLevelStyle;
/*N*/     if ( !pStyle )
/*N*/         pStyle = GetStyleSheet( nPara );
/*N*/
/*N*/   if ( pStyle )
/*N*/   {
/*N*/       String aNewStyleSheetName( pStyle->GetName() );
/*N*/       aNewStyleSheetName.Erase( aNewStyleSheetName.Len()-1, 1 );
/*N*/       aNewStyleSheetName += String::CreateFromInt32( GetDepth( nPara ) );
/*N*/       SfxStyleSheet* pNewStyle = (SfxStyleSheet*)GetStyleSheetPool()->Find( aNewStyleSheetName, pStyle->GetFamily() );
/*N*/       DBG_ASSERT( pNewStyle, "AutoStyleSheetName - Style not found!" );
/*N*/       if ( pNewStyle && ( pNewStyle != GetStyleSheet( nPara ) ) )
/*N*/       {
/*N*/           SfxItemSet aOldAttrs( GetParaAttribs( nPara ) );
/*N*/           SetStyleSheet( nPara, pNewStyle );
/*N*/           if ( aOldAttrs.GetItemState( EE_PARA_NUMBULLET ) == SFX_ITEM_ON )
/*N*/           {
/*N*/               SfxItemSet aAttrs( GetParaAttribs( nPara ) );
/*N*/               aAttrs.Put( aOldAttrs.Get( EE_PARA_NUMBULLET ) );
/*N*/               SetParaAttribs( nPara, aAttrs );
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ void Outliner::ImplInitDepth( USHORT nPara, USHORT nDepth, BOOL bCreateUndo, BOOL bUndoAction )
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/
/*N*/     DBG_ASSERT( ( nDepth >= nMinDepth ) && ( nDepth <= nMaxDepth ), "ImplInitDepth - Depth is invalid!" );
/*N*/
/*N*/   Paragraph* pPara = pParaList->GetParagraph( nPara );
/*N*/   USHORT nOldDepth = pPara->GetDepth();
/*N*/   pPara->SetDepth( nDepth );
/*N*/
/*N*/   // Bei IsInUndo brauchen Attribute und Style nicht eingestellt werden,
/*N*/   // dort werden die alten Werte durch die EditEngine restauriert.
/*N*/
/*N*/   if( !IsInUndo() )
/*N*/   {
/*N*/       BOOL bUpdate = pEditEngine->GetUpdateMode();
/*N*/       pEditEngine->SetUpdateMode( FALSE );
/*N*/
/*N*/       BOOL bUndo = bCreateUndo && IsUndoEnabled();
/*N*/       if ( bUndo && bUndoAction )
/*?*/           UndoActionStart( OLUNDO_DEPTH );
/*N*/
/*N*/       SfxItemSet aAttrs( pEditEngine->GetParaAttribs( nPara ) );
/*N*/       aAttrs.Put( SfxUInt16Item( EE_PARA_OUTLLEVEL, nDepth ) );
/*N*/       // MT: OUTLLRSPACE immer default, sollte mal irgendwie eingestellt werden...
/*N*/       aAttrs.Put( lcl_ImplGetDefLRSpaceItem( nDepth, GetRefMapMode().GetMapUnit() ) );
/*N*/       pEditEngine->SetParaAttribs( nPara, aAttrs );
/*N*/       ImplCheckNumBulletItem( nPara );
/*N*/       ImplCalcBulletText( nPara, FALSE, FALSE );
/*N*/
/*N*/ #ifndef SVX_LIGHT
/*N*/       if ( bUndo )
/*N*/       {
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 InsertUndo( new OutlinerUndoChangeDepth( this, nPara, nOldDepth, nDepth ) );
//STRIP001 /*?*/            if ( bUndoAction )
//STRIP001 /*?*/                UndoActionEnd( OLUNDO_DEPTH );
/*N*/       }
/*N*/ #endif
/*N*/
/*N*/       pEditEngine->SetUpdateMode( bUpdate );
/*N*/   }
/*N*/ }

/*N*/ void Outliner::SetParaAttribs( ULONG nPara, const SfxItemSet& rSet, bool bApiCall /* = false */ )
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/
/*N*/   Paragraph* pPara = pParaList->GetParagraph( nPara );
/*N*/   if( pPara )
/*N*/   {
/*N*/       if ( !pEditEngine->IsInUndo() && pEditEngine->IsUndoEnabled() )
/*N*/           UndoActionStart( OLUNDO_ATTR );
/*N*/
/*N*/       BOOL bLRSpaceChanged =
/*N*/           ( rSet.GetItemState( EE_PARA_LRSPACE ) == SFX_ITEM_ON  ) &&
/*N*/           ( !(rSet.Get( EE_PARA_LRSPACE ) == pEditEngine->GetParaAttrib( (USHORT)nPara, EE_PARA_LRSPACE ) ) );
/*N*/
/*N*/       pEditEngine->SetParaAttribs( (USHORT)nPara, rSet );
/*N*/
/*N*/       if( bLRSpaceChanged )
/*N*/       {
/*N*/           const SvxNumBulletItem& rNumBullet = (const SvxNumBulletItem&)pEditEngine->GetParaAttrib( (USHORT)nPara, EE_PARA_NUMBULLET );
/*N*/           Paragraph* pPara = pParaList->GetParagraph( nPara );
/*N*/           const USHORT nDepth = pPara->GetDepth();
/*N*/           if ( rNumBullet.GetNumRule()->GetLevelCount() > nDepth )
/*N*/           {
/*N*/               SvxNumBulletItem* pNewNumBullet = (SvxNumBulletItem*) rNumBullet.Clone();
/*N*/               EditEngine::ImportBulletItem( *pNewNumBullet, nDepth, NULL, (SvxLRSpaceItem*)&rSet.Get( EE_PARA_LRSPACE ) );
/*N*/               SfxItemSet aAttribs( rSet );
/*N*/               aAttribs.Put( *pNewNumBullet );
/*N*/               pEditEngine->SetParaAttribs( (USHORT)nPara, aAttribs );
/*N*/               delete pNewNumBullet;
/*N*/           }
/*N*/       }
/*N*/
/*N*/       ImplCheckNumBulletItem( (USHORT)nPara );
/*N*/       ImplCheckParagraphs( (USHORT)nPara, (USHORT)nPara );
/*N*/
/*N*/       if ( !pEditEngine->IsInUndo() && pEditEngine->IsUndoEnabled() )
/*N*/           UndoActionEnd( OLUNDO_ATTR );
/*N*/   }
/*N*/ }

//STRIP001 BOOL Outliner::Expand( Paragraph* pPara )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001
//STRIP001  if ( pParaList->HasHiddenChilds( pPara ) )
//STRIP001  {
//STRIP001      OLUndoExpand* pUndo;
//STRIP001 #ifndef SVX_LIGHT
//STRIP001      BOOL bUndo = IsUndoEnabled() && !IsInUndo();
//STRIP001      if( bUndo )
//STRIP001      {
//STRIP001          UndoActionStart( OLUNDO_EXPAND );
//STRIP001          pUndo = new OLUndoExpand( this, OLUNDO_EXPAND );
//STRIP001          pUndo->pParas = 0;
//STRIP001          pUndo->nCount = (USHORT)pParaList->GetAbsPos( pPara );
//STRIP001      }
//STRIP001 #else
//STRIP001      BOOL bUndo = sal_False;
//STRIP001 #endif
//STRIP001      pHdlParagraph = pPara;
//STRIP001      bIsExpanding = TRUE;
//STRIP001      pParaList->Expand( pPara );
//STRIP001      ExpandHdl();
//STRIP001      InvalidateBullet( pPara, pParaList->GetAbsPos(pPara) );
//STRIP001      if( bUndo )
//STRIP001      {
//STRIP001          InsertUndo( pUndo );
//STRIP001          UndoActionEnd( OLUNDO_EXPAND );
//STRIP001      }
//STRIP001      return TRUE;
//STRIP001  }
//STRIP001  return FALSE;
//STRIP001 }


//STRIP001 BOOL Outliner::Collapse( Paragraph* pPara )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  if ( pParaList->HasVisibleChilds( pPara ) ) // expandiert
//STRIP001  {
//STRIP001      OLUndoExpand* pUndo;
//STRIP001      BOOL bUndo = FALSE;
//STRIP001 #ifndef SVX_LIGHT
//STRIP001      if( !IsInUndo() && IsUndoEnabled() )
//STRIP001          bUndo = TRUE;
//STRIP001      if( bUndo )
//STRIP001      {
//STRIP001          UndoActionStart( OLUNDO_COLLAPSE );
//STRIP001          pUndo = new OLUndoExpand( this, OLUNDO_COLLAPSE );
//STRIP001          pUndo->pParas = 0;
//STRIP001          pUndo->nCount = (USHORT)pParaList->GetAbsPos( pPara );
//STRIP001      }
//STRIP001 #endif
//STRIP001      pHdlParagraph = pPara;
//STRIP001      bIsExpanding = FALSE;
//STRIP001      pParaList->Collapse( pPara );
//STRIP001      ExpandHdl();
//STRIP001      InvalidateBullet( pPara, pParaList->GetAbsPos(pPara) );
//STRIP001      if( bUndo )
//STRIP001      {
//STRIP001          InsertUndo( pUndo );
//STRIP001          UndoActionEnd( OLUNDO_COLLAPSE );
//STRIP001      }
//STRIP001      return TRUE;
//STRIP001  }
//STRIP001  return FALSE;
//STRIP001 }


/*N*/ Font Outliner::ImpCalcBulletFont( USHORT nPara ) const
/*N*/ {
/*N*/   const SvxNumberFormat* pFmt = ImplGetBullet( nPara );
/*N*/   DBG_ASSERT( pFmt && ( pFmt->GetNumberingType() != SVX_NUM_BITMAP ) && ( pFmt->GetNumberingType() != SVX_NUM_NUMBER_NONE ), "ImpCalcBulletFont: Missing or BitmapBullet!" );
/*N*/
/*N*/     Font aStdFont;  //#107508#
/*N*/     if ( !pEditEngine->IsFlatMode() )
/*N*/     {
/*N*/         ESelection aSel( nPara, 0, nPara, 0 );
/*N*/         aStdFont = EditEngine::CreateFontFromItemSet( pEditEngine->GetAttribs( aSel ), GetScriptType( aSel ) );
/*N*/     }
/*N*/     else
/*N*/     {
/*?*/         DBG_BF_ASSERT(0, "STRIP");//STRIP001 aStdFont = pEditEngine->GetStandardFont( nPara );
/*N*/     }
/*N*/
/*N*/   Font aBulletFont;
/*N*/   if ( pFmt->GetNumberingType() == SVX_NUM_CHAR_SPECIAL )
/*N*/     {
/*N*/       aBulletFont = *pFmt->GetBulletFont();
/*N*/     }
/*N*/   else
/*N*/     {
/*?*/       aBulletFont = aStdFont;
/*?*/         aBulletFont.SetUnderline( UNDERLINE_NONE );
/*?*/         aBulletFont.SetStrikeout( STRIKEOUT_NONE );
/*?*/         aBulletFont.SetEmphasisMark( EMPHASISMARK_NONE );
/*?*/         aBulletFont.SetRelief( RELIEF_NONE );
/*N*/     }
/*N*/
/*N*/     // #107508# Use original scale...
/*N*/   USHORT nScale = /* pEditEngine->IsFlatMode() ? DEFAULT_SCALE : */ pFmt->GetBulletRelSize();
/*N*/   ULONG nScaledLineHeight = aStdFont.GetSize().Height();
/*N*/   nScaledLineHeight *= nScale*10;
/*N*/   nScaledLineHeight /= 1000;
/*N*/
/*N*/     aBulletFont.SetAlign( ALIGN_BOTTOM );
/*N*/   aBulletFont.SetSize( Size( 0, nScaledLineHeight ) );
/*N*/   BOOL bVertical = IsVertical();
/*N*/     aBulletFont.SetVertical( bVertical );
/*N*/     aBulletFont.SetOrientation( bVertical ? 2700 : 0 );
/*N*/
/*N*/   Color aColor( COL_AUTO );
/*N*/   if( !pEditEngine->IsFlatMode() && !( pEditEngine->GetControlWord() & EE_CNTRL_NOCOLORS ) )
/*N*/     {
/*N*/       aColor = pFmt->GetBulletColor();
/*N*/     }
/*N*/
/*N*/     if ( ( aColor == COL_AUTO ) || ( IsForceAutoColor() ) )
/*N*/         aColor = pEditEngine->GetAutoColor();
/*N*/
/*N*/     aBulletFont.SetColor( aColor );
/*N*/   return aBulletFont;
/*N*/ }

/*N*/ void Outliner::PaintBullet( USHORT nPara, const Point& rStartPos,
/*N*/   const Point& rOrigin, short nOrientation, OutputDevice* pOutDev )
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/
/*N*/   if ( ImplHasBullet( nPara ) )
/*N*/   {
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 BOOL bVertical = IsVertical();
//STRIP001 /*?*/
//STRIP001 /*?*/         BOOL bRightToLeftPara = pEditEngine->IsRightToLeft( nPara );
//STRIP001 /*?*/
//STRIP001 /*?*/        Rectangle aBulletArea( ImpCalcBulletArea( nPara, TRUE, FALSE ) );
//STRIP001 /*?*/
//STRIP001 /*?*/         Paragraph* pPara = pParaList->GetParagraph( nPara );
//STRIP001 /*?*/        const SvxNumberFormat* pFmt = ImplGetBullet( nPara );
//STRIP001 /*?*/        if ( pFmt && ( pFmt->GetNumberingType() != SVX_NUM_NUMBER_NONE ) )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            if( pFmt->GetNumberingType() != SVX_NUM_BITMAP )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                Font aBulletFont( ImpCalcBulletFont( nPara ) );
//STRIP001 /*?*/                 // #2338# Use base line
//STRIP001 /*?*/                 BOOL bSymbol = pFmt->GetNumberingType() == SVX_NUM_CHAR_SPECIAL;
//STRIP001 /*?*/                 aBulletFont.SetAlign( bSymbol ? ALIGN_BOTTOM : ALIGN_BASELINE );
//STRIP001 /*?*/                Font aOldFont = pOutDev->GetFont();
//STRIP001 /*?*/                pOutDev->SetFont( aBulletFont );
//STRIP001 /*?*/
//STRIP001 /*?*/                 ParagraphInfos     aParaInfos = pEditEngine->GetParagraphInfos( nPara );
//STRIP001 /*?*/                Point aTextPos;
//STRIP001 /*?*/                if ( !bVertical )
//STRIP001 /*?*/                 {
//STRIP001 /*?*/ //                 aTextPos.Y() = rStartPos.Y() + aBulletArea.Bottom();
//STRIP001 /*?*/                     aTextPos.Y() = rStartPos.Y() + ( bSymbol ? aBulletArea.Bottom() : aParaInfos.nFirstLineMaxAscent );
//STRIP001 /*?*/                     if ( !bRightToLeftPara )
//STRIP001 /*?*/                        aTextPos.X() = rStartPos.X() + aBulletArea.Left();
//STRIP001 /*?*/                     else
//STRIP001 /*?*/                         aTextPos.X() = rStartPos.X() + GetPaperSize().Width() - aBulletArea.Left();
//STRIP001 /*?*/                 }
//STRIP001 /*?*/                else
//STRIP001 /*?*/                {
//STRIP001 /*?*/ //                 aTextPos.X() = rStartPos.X() - aBulletArea.Bottom();
//STRIP001 /*?*/                    aTextPos.X() = rStartPos.X() - ( bSymbol ? aBulletArea.Bottom() : aParaInfos.nFirstLineMaxAscent );
//STRIP001 /*?*/                    aTextPos.Y() = rStartPos.Y() + aBulletArea.Left();
//STRIP001 /*?*/                }
//STRIP001 /*?*/
//STRIP001 /*?*/                if ( !bStrippingPortions )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    if ( nOrientation )
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        // Sowohl TopLeft als auch BottomLeft nicht ganz richtig, da
//STRIP001 /*?*/                        // in EditEngine BaseLine...
//STRIP001 /*?*/                        double nRealOrientation = nOrientation*F_PI1800;
//STRIP001 /*?*/                        double nCos = cos( nRealOrientation );
//STRIP001 /*?*/                        double nSin = sin( nRealOrientation );
//STRIP001 /*?*/                        Point aRotatedPos;
//STRIP001 /*?*/                        // Translation...
//STRIP001 /*?*/                        aTextPos -= rOrigin;
//STRIP001 /*?*/                        // Rotation...
//STRIP001 /*?*/                        aRotatedPos.X()=(long)   (nCos*aTextPos.X() + nSin*aTextPos.Y());
//STRIP001 /*?*/                        aRotatedPos.Y()=(long) - (nSin*aTextPos.X() - nCos*aTextPos.Y());
//STRIP001 /*?*/                        aTextPos = aRotatedPos;
//STRIP001 /*?*/                        // Translation...
//STRIP001 /*?*/                        aTextPos += rOrigin;
//STRIP001 /*?*/                        Font aRotatedFont( aBulletFont );
//STRIP001 /*?*/                        aRotatedFont.SetLineOrientation( nOrientation );
//STRIP001 /*?*/                        pOutDev->SetFont( aRotatedFont );
//STRIP001 /*?*/                    }
//STRIP001 /*?*/
//STRIP001 /*?*/                     // #105803# VCL will care for brackets and so on...
//STRIP001 /*?*/                     ULONG nLayoutMode = pOutDev->GetLayoutMode();
//STRIP001 /*?*/                     nLayoutMode &= ~(TEXT_LAYOUT_BIDI_RTL|TEXT_LAYOUT_COMPLEX_DISABLED|TEXT_LAYOUT_BIDI_STRONG);
//STRIP001 /*?*/                     if ( bRightToLeftPara )
//STRIP001 /*?*/                         nLayoutMode |= TEXT_LAYOUT_BIDI_RTL;
//STRIP001 /*?*/                     pOutDev->SetLayoutMode( nLayoutMode );
//STRIP001 /*?*/
//STRIP001 /*?*/                    pOutDev->DrawText( aTextPos, pPara->GetText() );
//STRIP001 /*?*/
//STRIP001 /*?*/                    // HACK #47227#
//STRIP001 /*?*/                    // Seitennummer im Gliederungsmodus ausgeben...
//STRIP001 /*?*/                    if ( (pPara->GetDepth() == 0 ) && ( pEditEngine->GetControlWord() & EE_CNTRL_OUTLINER ) )
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        long nPage = nFirstPage-1;
//STRIP001 /*?*/                        for ( USHORT n = 0; n <= nPara; n++ )
//STRIP001 /*?*/                        {
//STRIP001 /*?*/                            Paragraph* p = pParaList->GetParagraph( n );
//STRIP001 /*?*/                            if ( p->GetDepth() == 0 )
//STRIP001 /*?*/                                nPage++;
//STRIP001 /*?*/                        }
//STRIP001 /*?*/
//STRIP001 /*?*/                         long nFontHeight = 0;
//STRIP001 /*?*/                         if ( !pEditEngine->IsFlatMode() )
//STRIP001 /*?*/                         {
//STRIP001 /*?*/                            const SvxFontHeightItem& rFH = (const SvxFontHeightItem&)pEditEngine->GetParaAttrib( nPara, EE_CHAR_FONTHEIGHT );
//STRIP001 /*?*/                             nFontHeight = rFH.GetHeight();
//STRIP001 /*?*/                             nFontHeight /= 5;
//STRIP001 /*?*/                         }
//STRIP001 /*?*/                         else
//STRIP001 /*?*/                         {
//STRIP001 /*?*/                            const SvxFontHeightItem& rFH = (const SvxFontHeightItem&)pEditEngine->GetEmptyItemSet().Get( EE_CHAR_FONTHEIGHT );
//STRIP001 /*?*/                             nFontHeight = rFH.GetHeight();
//STRIP001 /*?*/                             nFontHeight *= 10;
//STRIP001 /*?*/                             nFontHeight /= 25;
//STRIP001 /*?*/                         }
//STRIP001 /*?*/                        Size aFontSz( 0, nFontHeight );
//STRIP001 /*?*/
//STRIP001 /*?*/                         LanguageType eLang = pEditEngine->GetDefaultLanguage();
//STRIP001 /*?*/                         // USHORT nScriptType = GetScriptTypeOfLanguage( eLang );
//STRIP001 /*?*/                        Font aNewFont( OutputDevice::GetDefaultFont( DEFAULTFONT_SANS_UNICODE, eLang, 0 ) );
//STRIP001 /*?*/                        aNewFont.SetSize( aFontSz );
//STRIP001 /*?*/                        aNewFont.SetAlign( aBulletFont.GetAlign() );
//STRIP001 /*?*/                        aNewFont.SetVertical( bVertical );
//STRIP001 /*?*/                        aNewFont.SetOrientation( bVertical ? 2700 : 0 );
//STRIP001 /*?*/                         aNewFont.SetColor( aBulletFont.GetColor() );
//STRIP001 /*?*/                        pOutDev->SetFont( aNewFont );
//STRIP001 /*?*/                        String aPageText = String::CreateFromInt32( nPage );
//STRIP001 /*?*/                        Size aTextSz;
//STRIP001 /*?*/                        aTextSz.Width() = pOutDev->GetTextWidth( aPageText );
//STRIP001 /*?*/                        aTextSz.Height() = pOutDev->GetTextHeight();
//STRIP001 /*?*/                         long nBulletHeight = !bVertical ? aBulletArea.GetHeight() : aBulletArea.GetWidth();
//STRIP001 /*?*/                        if ( !bVertical )
//STRIP001 /*?*/                        {
//STRIP001 /*?*/                            aTextPos.Y() -= nBulletHeight / 2;
//STRIP001 /*?*/                            aTextPos.Y() += aTextSz.Height() / 2;
//STRIP001 /*?*/                             if ( !bRightToLeftPara )
//STRIP001 /*?*/                             {
//STRIP001 /*?*/                                aTextPos.X() -= aTextSz.Width();
//STRIP001 /*?*/                                aTextPos.X() -= aTextSz.Height() / 8;
//STRIP001 /*?*/                             }
//STRIP001 /*?*/                             else
//STRIP001 /*?*/                             {
//STRIP001 /*?*/                                aTextPos.X() += aTextSz.Width();
//STRIP001 /*?*/                                aTextPos.X() += aTextSz.Height() / 8;
//STRIP001 /*?*/                             }
//STRIP001 /*?*/                        }
//STRIP001 /*?*/                        else
//STRIP001 /*?*/                        {
//STRIP001 /*?*/                            aTextPos.Y() -= aTextSz.Width();
//STRIP001 /*?*/                            aTextPos.Y() -= aTextSz.Height() / 8;
//STRIP001 /*?*/                            aTextPos.X() += nBulletHeight / 2;
//STRIP001 /*?*/                            aTextPos.X() -= aTextSz.Height() / 2;
//STRIP001 /*?*/                        }
//STRIP001 /*?*/                        pOutDev->DrawText( aTextPos, aPageText );
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                }
//STRIP001 /*?*/                else
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    Font aSvxFont( aBulletFont );
//STRIP001 /*?*/                    long* pBuf = new long[ pPara->GetText().Len() ];
//STRIP001 /*?*/                    pOutDev->GetTextArray( pPara->GetText(), pBuf );
//STRIP001 /*?*/                    // aTextPos ist Bottom, jetzt die Baseline liefern:
//STRIP001 /*?*/                    FontMetric aMetric( pOutDev->GetFontMetric() );
//STRIP001 /*?*/                    aTextPos.Y() -= aMetric.GetDescent();
//STRIP001 /*?*/
//STRIP001 /*?*/                    // #101498#
//STRIP001 /*?*/                    DrawingText( aTextPos, pPara->GetText(), 0, pPara->GetText().Len(), pBuf, aSvxFont, nPara, 0xFFFF, 0xFF);
//STRIP001 /*?*/
//STRIP001 /*?*/                    delete[] pBuf;
//STRIP001 /*?*/                }
//STRIP001 /*?*/                pOutDev->SetFont( aOldFont );
//STRIP001 /*?*/            }
//STRIP001 /*?*/            else
//STRIP001 /*?*/            {
//STRIP001 /*?*/                if ( !bStrippingPortions )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    if ( pFmt->GetBrush()->GetGraphicObject() )
//STRIP001 /*?*/                     {
//STRIP001 /*?*/                        Point aBulletPos;
//STRIP001 /*?*/                         if ( !bVertical )
//STRIP001 /*?*/                         {
//STRIP001 /*?*/                            aBulletPos.Y() = rStartPos.Y() + aBulletArea.Top();
//STRIP001 /*?*/                             if ( !bRightToLeftPara )
//STRIP001 /*?*/                                aBulletPos.X() = rStartPos.X() + aBulletArea.Left();
//STRIP001 /*?*/                             else
//STRIP001 /*?*/                                 aBulletPos.X() = rStartPos.X() + GetPaperSize().Width() - aBulletArea.Right();
//STRIP001 /*?*/                         }
//STRIP001 /*?*/                        else
//STRIP001 /*?*/                        {
//STRIP001 /*?*/                            aBulletPos.X() = rStartPos.X() - aBulletArea.Bottom();
//STRIP001 /*?*/                            aBulletPos.Y() = rStartPos.Y() + aBulletArea.Left();
//STRIP001 /*?*/                        }
//STRIP001 /*?*/
//STRIP001 /*?*/                         // MT: Remove CAST when KA made the Draw-Method const
//STRIP001 /*?*/                        ((GraphicObject*)pFmt->GetBrush()->GetGraphicObject())->Draw( pOutDev, aBulletPos, pPara->aBulSize );
//STRIP001 /*?*/                     }
//STRIP001 /*?*/                }
//STRIP001 /*?*/            }
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/        // Bei zusammengeklappten Absaetzen einen Strich vor den Text malen.
//STRIP001 /*?*/        if( pParaList->HasChilds(pPara) && !pParaList->HasVisibleChilds(pPara) &&
//STRIP001 /*?*/                !bStrippingPortions && !nOrientation )
//STRIP001 /*?*/        {
//STRIP001 /*?*/             long nWidth = pOutDev->PixelToLogic( Size( 10, 0 ) ).Width();
//STRIP001 /*?*/
//STRIP001 /*?*/             Point aStartPos, aEndPos;
//STRIP001 /*?*/            if ( !bVertical )
//STRIP001 /*?*/             {
//STRIP001 /*?*/                aStartPos.Y() = rStartPos.Y() + aBulletArea.Bottom();
//STRIP001 /*?*/                 if ( !bRightToLeftPara )
//STRIP001 /*?*/                    aStartPos.X() = rStartPos.X() + aBulletArea.Right();
//STRIP001 /*?*/                 else
//STRIP001 /*?*/                     aStartPos.X() = rStartPos.X() + GetPaperSize().Width() - aBulletArea.Left();
//STRIP001 /*?*/                 aEndPos = aStartPos;
//STRIP001 /*?*/                 aEndPos.X() += nWidth;
//STRIP001 /*?*/             }
//STRIP001 /*?*/            else
//STRIP001 /*?*/            {
//STRIP001 /*?*/                aStartPos.X() = rStartPos.X() - aBulletArea.Bottom();
//STRIP001 /*?*/                aStartPos.Y() = rStartPos.Y() + aBulletArea.Right();
//STRIP001 /*?*/                 aEndPos = aStartPos;
//STRIP001 /*?*/                 aEndPos.Y() += nWidth;
//STRIP001 /*?*/            }
//STRIP001 /*?*/
//STRIP001 /*?*/            const Color& rOldLineColor = pOutDev->GetLineColor();
//STRIP001 /*?*/            pOutDev->SetLineColor( Color( COL_BLACK ) );
//STRIP001 /*?*/            pOutDev->DrawLine( aStartPos, aEndPos );
//STRIP001 /*?*/            pOutDev->SetLineColor( rOldLineColor );
//STRIP001 /*?*/        }
/*N*/   }
/*N*/ }

//STRIP001 void Outliner::InvalidateBullet( Paragraph* pPara, ULONG nPara )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001
//STRIP001  long nLineHeight = (long)pEditEngine->GetLineHeight((USHORT)nPara );
//STRIP001  OutlinerView* pView = aViewList.First();
//STRIP001  while( pView )
//STRIP001  {
//STRIP001      Point aPos( pView->pEditView->GetWindowPosTopLeft((USHORT)nPara ) );
//STRIP001      Rectangle aRect( pView->GetOutputArea() );
//STRIP001      aRect.Right() = aPos.X();
//STRIP001      aRect.Top() = aPos.Y();
//STRIP001      aRect.Bottom() = aPos.Y();
//STRIP001      aRect.Bottom() += nLineHeight;
//STRIP001
//STRIP001      pView->GetWindow()->Invalidate( aRect );
//STRIP001      pView = aViewList.Next();
//STRIP001  }
//STRIP001 }

/*N*/ ULONG Outliner::Read( SvStream& rInput, USHORT eFormat, SvKeyValueIterator* pHTTPHeaderAttrs )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); return 0; //STRIP001
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001
//STRIP001  BOOL bOldUndo = pEditEngine->IsUndoEnabled();
//STRIP001  EnableUndo( FALSE );
//STRIP001
//STRIP001  BOOL bUpdate = pEditEngine->GetUpdateMode();
//STRIP001  pEditEngine->SetUpdateMode( FALSE );
//STRIP001
//STRIP001  Clear();
//STRIP001
//STRIP001  ImplBlockInsertionCallbacks( TRUE );
//STRIP001  ULONG nRet = pEditEngine->Read( rInput, (EETextFormat)eFormat, pHTTPHeaderAttrs );
//STRIP001
//STRIP001  bFirstParaIsEmpty = FALSE;
//STRIP001
//STRIP001  USHORT nParas = pEditEngine->GetParagraphCount();
//STRIP001      pParaList->Clear( TRUE );
//STRIP001  USHORT n;
//STRIP001  for ( n = 0; n < nParas; n++ )
//STRIP001  {
//STRIP001      Paragraph* pPara = new Paragraph( 0 );
//STRIP001      pParaList->Insert( pPara, LIST_APPEND );
//STRIP001
//STRIP001      if ( eFormat == EE_FORMAT_BIN )
//STRIP001      {
//STRIP001          USHORT nDepth = 0;
//STRIP001          const SfxItemSet& rAttrs = pEditEngine->GetParaAttribs( n );
//STRIP001          const SfxUInt16Item& rLevel = (const SfxUInt16Item&) rAttrs.Get( EE_PARA_OUTLLEVEL );
//STRIP001          nDepth = rLevel.GetValue();
//STRIP001          ImplInitDepth( n, nDepth, FALSE );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if ( eFormat != EE_FORMAT_BIN )
//STRIP001  {
//STRIP001      ImpFilterIndents( 0, nParas-1 );
//STRIP001  }
//STRIP001
//STRIP001  for ( n = 0; n < nParas; n++ )
//STRIP001  {
//STRIP001      // Handler rufen, Outliner war leer. Aber nicht fuer den ersten
//STRIP001      pHdlParagraph = pParaList->GetParagraph( n );
//STRIP001      ParagraphInsertedHdl();
//STRIP001  }
//STRIP001
//STRIP001     ImplBlockInsertionCallbacks( FALSE );
//STRIP001  pEditEngine->SetUpdateMode( bUpdate );
//STRIP001  EnableUndo( bOldUndo );
//STRIP001
//STRIP001  return nRet;
/*N*/ }


//STRIP001 void Outliner::ImpFilterIndents( ULONG nFirstPara, ULONG nLastPara )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001
//STRIP001  BOOL bUpdate = pEditEngine->GetUpdateMode();
//STRIP001  pEditEngine->SetUpdateMode( FALSE );
//STRIP001
//STRIP001  Paragraph* pLastConverted = NULL;
//STRIP001  for( ULONG nPara = nFirstPara; nPara <= nLastPara; nPara++ )
//STRIP001  {
//STRIP001      Paragraph* pPara = pParaList->GetParagraph( nPara );
//STRIP001      if( ImpConvertEdtToOut( pPara, nPara ) )
//STRIP001      {
//STRIP001          pLastConverted = pPara;
//STRIP001      }
//STRIP001      else if ( pLastConverted )
//STRIP001      {
//STRIP001          // Normale Absaetze unter der Ueberschrift anordnen...
//STRIP001          pPara->SetDepth( pLastConverted->GetDepth() );
//STRIP001      }
//STRIP001
//STRIP001      ImplInitDepth( (USHORT)nPara, pPara->GetDepth(), FALSE );
//STRIP001  }
//STRIP001
//STRIP001  pEditEngine->SetUpdateMode( bUpdate );
//STRIP001 }

/*N*/ #ifndef SVX_LIGHT
/*N*/ SfxUndoManager&   Outliner::GetUndoManager()
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   return pEditEngine->GetUndoManager();
/*N*/ }
/*N*/ #endif

//STRIP001 void Outliner::ImpTextPasted( ULONG nStartPara, USHORT nCount )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001
//STRIP001  BOOL bUpdate = pEditEngine->GetUpdateMode();
//STRIP001  pEditEngine->SetUpdateMode( FALSE );
//STRIP001
//STRIP001  const ULONG nStart = nStartPara;
//STRIP001
//STRIP001  Paragraph* pPara = pParaList->GetParagraph( nStartPara );
//STRIP001  Paragraph* pLastConverted = NULL;
//STRIP001  while( nCount && pPara )
//STRIP001  {
//STRIP001      if( ImplGetOutlinerMode() != OUTLINERMODE_TEXTOBJECT )
//STRIP001      {
//STRIP001          USHORT nPrevDepth = pPara->GetDepth();
//STRIP001          if( ImpConvertEdtToOut( pPara, nStartPara ) )
//STRIP001              pLastConverted = pPara;
//STRIP001          else if ( pLastConverted )
//STRIP001          {
//STRIP001              // Normale Absaetze unter der Ueberschrift anordnen...
//STRIP001              pPara->SetDepth( pLastConverted->GetDepth() );
//STRIP001          }
//STRIP001          // Tiefe des Absatzes hat sich geaendert.
//STRIP001          if( pPara->GetDepth() != nPrevDepth )
//STRIP001          {
//STRIP001              pHdlParagraph = pPara;
//STRIP001              if( nPrevDepth == 0xffff )
//STRIP001              {
//STRIP001                  // neuer Absatz -> InsertedHdl rufen
//STRIP001                  ParagraphInsertedHdl();
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  if( nStartPara == nStart )
//STRIP001                     {
//STRIP001                      // die Einrueckebene des Startabsatzes bleibt
//STRIP001                      // immer erhalten (leere Absaetze bekommen
//STRIP001                      // die Absatzattribute des eingefuegten Absatzes,
//STRIP001                      // diese sind aber erst nach dem Paste bekannt,
//STRIP001                      // d.h. es muesste dann ggf. der ParagraphIndenting
//STRIP001                      // Handler gerufen werden (also u.U. vor UND nach
//STRIP001                      // dem Paste)
//STRIP001
//STRIP001                         // MT 08/01: Changed the behavior a little bit: Only reset Depth when it was 0,
//STRIP001                         // because a page would be deleted, but to late to ask the user.
//STRIP001                         if ( nPrevDepth == 0 )
//STRIP001                             pPara->SetDepth( 0 );
//STRIP001                     }
//STRIP001                  else if( (!nStartPara && pPara->GetDepth()) || (pPara->GetDepth() < nMinDepth) )
//STRIP001                     {
//STRIP001                      pPara->SetDepth( nMinDepth );
//STRIP001                     }
//STRIP001
//STRIP001                  if( pPara->GetDepth() != nPrevDepth )
//STRIP001                  {
//STRIP001                      // alter Absatz -> DepthChangedHdl rufen
//STRIP001                      nDepthChangedHdlPrevDepth = nPrevDepth;
//STRIP001                      DepthChangedHdl();
//STRIP001                  }
//STRIP001              }
//STRIP001              ImplInitDepth( (USHORT)nStartPara, pPara->GetDepth(), FALSE );
//STRIP001          }
//STRIP001          else if( nStartPara == nStart )
//STRIP001             {
//STRIP001              ImplInitDepth( (USHORT)nStartPara, pPara->GetDepth(), FALSE );
//STRIP001             }
//STRIP001      }
//STRIP001      else // EditEngine-Modus
//STRIP001      {
//STRIP001          USHORT nDepth = 0;
//STRIP001          const SfxItemSet& rAttrs = pEditEngine->GetParaAttribs( (USHORT)nStartPara );
//STRIP001          if ( rAttrs.GetItemState( EE_PARA_OUTLLEVEL ) == SFX_ITEM_ON )
//STRIP001          {
//STRIP001              const SfxUInt16Item& rLevel = (const SfxUInt16Item&) rAttrs.Get( EE_PARA_OUTLLEVEL );
//STRIP001              nDepth = rLevel.GetValue();
//STRIP001          }
//STRIP001          if ( nDepth != GetDepth( nStartPara ) )
//STRIP001              ImplInitDepth( (USHORT)nStartPara, nDepth, FALSE );
//STRIP001      }
//STRIP001
//STRIP001      nCount--;
//STRIP001      nStartPara++;
//STRIP001      pPara = pParaList->GetParagraph( nStartPara );
//STRIP001  }
//STRIP001
//STRIP001  pEditEngine->SetUpdateMode( bUpdate );
//STRIP001
//STRIP001  DBG_ASSERT(pParaList->GetParagraphCount()==pEditEngine->GetParagraphCount(),"ImpTextPasted failed");
//STRIP001 }



//STRIP001 void Outliner::ImpDropped( OutlinerView* pOutlView )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001
//STRIP001  // MT 06/00 - Was soll das hier?
//STRIP001  // Diese Methode muss mal ueberarbeitet werden...
//STRIP001  EditView* pView = pOutlView->pEditView;
//STRIP001
//STRIP001  ULONG nParas = pParaList->GetParagraphCount();
//STRIP001  for ( ULONG nPara = 0; nPara < nParas; nPara++ )
//STRIP001  {
//STRIP001      Paragraph* pPara = pParaList->GetParagraph( nPara );
//STRIP001      USHORT nCurDepth = pPara->GetDepth();
//STRIP001      if( nCurDepth == 0xffff )
//STRIP001      {
//STRIP001          ImpConvertEdtToOut( pPara, nPara, pView );
//STRIP001          pHdlParagraph = pPara;
//STRIP001          ParagraphInsertedHdl();
//STRIP001          ImplInitDepth( (USHORT)nPara, pPara->GetDepth(), FALSE );
//STRIP001      }
//STRIP001      else if( pPara->nFlags & PARAFLAG_DROPTARGET )
//STRIP001      {
//STRIP001          ImpConvertEdtToOut( pPara, nPara, pView );
//STRIP001          if( pPara->nDepth != nCurDepth ||
//STRIP001              (pPara->nFlags & PARAFLAG_DROPTARGET_EMPTY) )
//STRIP001          {
//STRIP001              // auf alten Wert zuruecksetzen
//STRIP001              pPara->SetDepth( nCurDepth );
//STRIP001
//STRIP001              // und neu attributieren
//STRIP001              ImplInitDepth( (USHORT)nPara, pPara->GetDepth(), FALSE );
//STRIP001          }
//STRIP001          pPara->nFlags &= (~PARAFLAG_DROPTARGET|PARAFLAG_DROPTARGET_EMPTY);
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 long Outliner::IndentingPagesHdl( OutlinerView* pView )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  if( !aIndentingPagesHdl.IsSet() )
//STRIP001      return 1;
//STRIP001  return aIndentingPagesHdl.Call( pView );
//STRIP001 }

//STRIP001 BOOL Outliner::ImpCanIndentSelectedPages( OutlinerView* pCurView )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  // Die selektierten Seiten muessen vorher durch ImpCalcSelectedPages
//STRIP001  // schon eingestellt sein
//STRIP001
//STRIP001  // Wenn der erste Absatz auf Ebene 0 liegt darf er auf keinen Fall
//STRIP001  // eingerueckt werden, evtl folgen aber weitere auf Ebene 0.
//STRIP001  if ( ( (ULONG)pHdlParagraph == 0 ) && ( ImplGetOutlinerMode() != OUTLINERMODE_TEXTOBJECT ) )
//STRIP001  {
//STRIP001      if ( nDepthChangedHdlPrevDepth == 1 )   // ist die einzige Seite
//STRIP001          return FALSE;
//STRIP001      else
//STRIP001          pCurView->ImpCalcSelectedPages( FALSE );    // ohne die erste
//STRIP001  }
//STRIP001  return (BOOL)IndentingPagesHdl( pCurView );
//STRIP001 }

//STRIP001
//STRIP001 BOOL Outliner::ImpCanDeleteSelectedPages( OutlinerView* pCurView )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  // Die selektierten Seiten muessen vorher durch ImpCalcSelectedPages
//STRIP001  // schon eingestellt sein
//STRIP001  return (BOOL)RemovingPagesHdl( pCurView );
//STRIP001 }

/*N*/ Outliner::Outliner( SfxItemPool* pPool, USHORT nMode )
/*N*/ {
/*N*/   DBG_CTOR( Outliner, 0 );
/*N*/
/*N*/   bStrippingPortions  = FALSE;
/*N*/   bPasting            = FALSE;
/*N*/
/*N*/   nFirstPage          = 1;
/*N*/   bBlockInsCallback   = FALSE;
/*N*/
/*N*/   nMinDepth           = 0;
/*N*/   nMaxDepth           = 9;
/*N*/
/*N*/     pOverwriteLevel0Bullet = NULL;
/*N*/
/*N*/   pParaList = new ParagraphList;
/*N*/   pParaList->SetVisibleStateChangedHdl( LINK( this, Outliner, ParaVisibleStateChangedHdl ) );
/*N*/   Paragraph* pPara = new Paragraph( 0 );
/*N*/   pParaList->Insert( pPara, LIST_APPEND );
/*N*/   bFirstParaIsEmpty = TRUE;
/*N*/
/*N*/   pEditEngine = new OutlinerEditEng( this, pPool );
/*N*/     pEditEngine->SetBeginMovingParagraphsHdl( LINK( this, Outliner, BeginMovingParagraphsHdl ) );
/*N*/     pEditEngine->SetEndMovingParagraphsHdl( LINK( this, Outliner, EndMovingParagraphsHdl ) );
/*N*/     pEditEngine->SetBeginPasteOrDropHdl( LINK( this, Outliner, BeginPasteOrDropHdl ) );
/*N*/     pEditEngine->SetEndPasteOrDropHdl( LINK( this, Outliner, EndPasteOrDropHdl ) );
/*N*/
/*N*/   Init( nMode );
/*N*/ }

/*N*/ Outliner::~Outliner()
/*N*/ {
/*N*/   DBG_DTOR(Outliner,0);
/*N*/
/*N*/   pParaList->Clear( TRUE );
/*N*/   delete pParaList;
/*N*/     delete pOverwriteLevel0Bullet;
/*N*/   delete pEditEngine;
/*N*/ }

//STRIP001 ULONG Outliner::InsertView( OutlinerView* pView, ULONG nIndex )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001
//STRIP001  aViewList.Insert( pView, nIndex );
//STRIP001  pEditEngine->InsertView(  pView->pEditView, (USHORT)nIndex );
//STRIP001  return aViewList.GetPos( pView );
//STRIP001 }

//STRIP001 OutlinerView* Outliner::RemoveView( OutlinerView* pView )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001
//STRIP001  ULONG nPos = aViewList.GetPos( pView );
//STRIP001  if ( nPos != LIST_ENTRY_NOTFOUND )
//STRIP001  {
//STRIP001      pView->pEditView->HideCursor(); // HACK wg. BugId 10006
//STRIP001      pEditEngine->RemoveView(  pView->pEditView );
//STRIP001      aViewList.Remove( nPos );
//STRIP001  }
//STRIP001  return NULL;    // MT: return ueberfluessig
//STRIP001 }

//STRIP001 OutlinerView* Outliner::RemoveView( ULONG nIndex )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001
//STRIP001  EditView* pEditView = pEditEngine->GetView( (USHORT)nIndex );
//STRIP001  pEditView->HideCursor(); // HACK wg. BugId 10006
//STRIP001
//STRIP001  pEditEngine->RemoveView( (USHORT)nIndex );
//STRIP001  aViewList.Remove( nIndex );
//STRIP001  return NULL;    // MT: return ueberfluessig
//STRIP001 }


//STRIP001 OutlinerView* Outliner::GetView( ULONG nIndex ) const
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  return aViewList.GetObject( nIndex );
//STRIP001 }

//STRIP001 ULONG Outliner::GetViewCount() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  return aViewList.Count();
//STRIP001 }

/*N*/ void Outliner::ParagraphInsertedHdl()
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   aParaInsertedHdl.Call( this );
/*N*/ }


/*N*/ void Outliner::ParagraphRemovingHdl()
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   aParaRemovingHdl.Call( this );
/*N*/ }


/*N*/ void Outliner::DepthChangedHdl()
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   aDepthChangedHdl.Call( this );
/*N*/ }


/*N*/ ULONG Outliner::GetAbsPos( Paragraph* pPara )
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   DBG_ASSERT(pPara,"GetAbsPos:No Para")
/*N*/   return pParaList->GetAbsPos( pPara );
/*N*/ }

/*N*/ void Outliner::ParagraphHeightChanged( USHORT )
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   // MT: Kann wohl weg...
/*N*/ }

/*N*/ ULONG Outliner::GetParagraphCount() const
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   return pParaList->GetParagraphCount();
/*N*/ }

/*N*/ Paragraph* Outliner::GetParagraph( ULONG nAbsPos ) const
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   return pParaList->GetParagraph( nAbsPos );
/*N*/ }

//STRIP001 BOOL Outliner::HasChilds( Paragraph* pParagraph ) const
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  return pParaList->HasChilds( pParagraph );
//STRIP001 }

/*N*/ BOOL Outliner::ImplHasBullet( USHORT nPara ) const
/*N*/ {
/*N*/   const SfxUInt16Item& rBulletState = (const SfxUInt16Item&) pEditEngine->GetParaAttrib( nPara, EE_PARA_BULLETSTATE );
/*N*/   BOOL bBullet = rBulletState.GetValue() ? TRUE : FALSE;
/*N*/   if ( !pParaList->GetParagraph( nPara )->GetDepth() && ( pEditEngine->GetControlWord() & EE_CNTRL_OUTLINER ) )
/*N*/   {
/*N*/       // Im Gliederungsmodus immer ein Bullet auf Ebene 0!
/*N*/       bBullet = TRUE;
/*N*/   }
/*N*/   else if ( bBullet )
/*N*/   {
/*N*/       const SvxNumberFormat* pFmt = ImplGetBullet( nPara );
/*N*/       if ( !pFmt || ( pFmt->GetNumberingType() == SVX_NUM_NUMBER_NONE ) )
/*N*/           bBullet = FALSE;
/*N*/   }
/*N*/   return bBullet;
/*N*/ }

/*N*/ const SvxNumberFormat* Outliner::ImplGetBullet( USHORT nPara ) const
/*N*/ {
/*N*/     const SvxNumberFormat* pFmt = NULL;
/*N*/
/*N*/     USHORT nDepth = pParaList->GetParagraph( nPara )->GetDepth();
/*N*/
/*N*/     if ( !nDepth && pOverwriteLevel0Bullet )
/*N*/     {
/*N*/         pFmt = pOverwriteLevel0Bullet;
/*N*/     }
/*N*/     else
/*N*/     {
/*N*/         const SvxNumBulletItem& rNumBullet = (const SvxNumBulletItem&) pEditEngine->GetParaAttrib( nPara, EE_PARA_NUMBULLET );
/*N*/         if ( rNumBullet.GetNumRule()->GetLevelCount() > nDepth )
/*N*/             pFmt = rNumBullet.GetNumRule()->Get( nDepth );
/*N*/     }
/*N*/
/*N*/     return pFmt;
/*N*/ }

/*N*/ Size Outliner::ImplGetBulletSize( USHORT nPara )
/*N*/ {
/*N*/   Paragraph* pPara = pParaList->GetParagraph( nPara );
/*N*/
/*N*/   if( pPara->aBulSize.Width() == -1 )
/*N*/   {
/*N*/       const SvxNumberFormat* pFmt = ImplGetBullet( nPara );
/*N*/       DBG_ASSERT( pFmt, "ImplGetBulletSize - no Bullet!" );
/*N*/
/*N*/       if ( pFmt->GetNumberingType() == SVX_NUM_NUMBER_NONE )
/*N*/       {
/*?*/           pPara->aBulSize = Size( 0, 0 );
/*N*/       }
/*N*/       else if( pFmt->GetNumberingType() != SVX_NUM_BITMAP )
/*N*/       {
/*N*/           String aBulletText = ImplGetBulletText( nPara );
/*N*/           OutputDevice* pRefDev = pEditEngine->GetRefDevice();
/*N*/           Font aBulletFont( ImpCalcBulletFont( nPara ) );
/*N*/           Font aRefFont( pRefDev->GetFont());
/*N*/           pRefDev->SetFont( aBulletFont );
/*N*/           pPara->aBulSize.Width() = pRefDev->GetTextWidth( aBulletText );
/*N*/           pPara->aBulSize.Height() = pRefDev->GetTextHeight();
/*N*/           pRefDev->SetFont( aRefFont );
/*N*/       }
/*N*/       else
/*N*/       {
/*?*/           pPara->aBulSize = OutputDevice::LogicToLogic( pFmt->GetGraphicSize(), MAP_100TH_MM, pEditEngine->GetRefDevice()->GetMapMode() );
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return pPara->aBulSize;
/*N*/ }

/*N*/ void Outliner::ImplCheckParagraphs( USHORT nStart, USHORT nEnd )
/*N*/ {
/*N*/   DBG_CHKTHIS( Outliner, 0 );
/*N*/
/*N*/   // Sicherstellen dass es ein Bullet und ein LR-Space gibt.
/*N*/
/*N*/   for ( USHORT n = nStart; n <= nEnd; n++ )
/*N*/   {
/*N*/       Paragraph* pPara = pParaList->GetParagraph( n );
/*N*/       BOOL bHasLRSpace = pEditEngine->HasParaAttrib( n, EE_PARA_OUTLLRSPACE );
/*N*/       BOOL bHasLevel = pEditEngine->HasParaAttrib( n, EE_PARA_OUTLLEVEL );
/*N*/       if ( !bHasLRSpace || !bHasLevel )
/*N*/       {
/*N*/           SfxItemSet aAttrs( pEditEngine->GetParaAttribs( n ) );
/*N*/
/*N*/           // MT 05/00: Default-Item muss erstmal richtig sein => Dann koennen diese ganzen komischen Defaults weg!!!
/*N*/ //            const SvxNumBulletItem& rNumBullet = (const SvxNumBulletItem&) pEditEngine->GetParaAttrib( n, EE_PARA_NUMBULLET );
/*N*/ //            const SvxNumberFormat* pFmt = NULL;
/*N*/ //            if ( ( rNumBullet.GetNumRule()->GetLevelCount() > pPara->GetDepth() ) &&
/*N*/ //                 ( ( pFtm = rNumBullet.GetNumRule()->Get( pPara->GetDepth() ) != NULL ) )
/*N*/ //            {
/*N*/ //            }
/*N*/           if ( !bHasLRSpace )
/*N*/           {
/*N*/               SvxLRSpaceItem aLRSpaceItem = lcl_ImplGetDefLRSpaceItem( pPara->GetDepth(), GetRefMapMode().GetMapUnit() );
/*N*/               aAttrs.Put( aLRSpaceItem );
/*N*/           }
/*N*/           if ( !bHasLevel )
/*N*/           {
/*N*/               SfxUInt16Item aLevelItem( EE_PARA_OUTLLEVEL, pPara->GetDepth() );
/*N*/               aAttrs.Put( aLevelItem );
/*N*/           }
/*N*/           pEditEngine->SetParaAttribs( n, aAttrs );
/*N*/       }
/*N*/
/*N*/       pPara->Invalidate();
/*N*/       ImplCalcBulletText( n, FALSE, FALSE );
/*N*/   }
/*N*/ }

/*N*/ void Outliner::SetRefDevice( OutputDevice* pRefDev )
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   pEditEngine->SetRefDevice( pRefDev );
/*N*/   for ( USHORT n = (USHORT) pParaList->GetParagraphCount(); n; )
/*N*/   {
/*N*/       Paragraph* pPara = pParaList->GetParagraph( --n );
/*N*/       pPara->Invalidate();
/*N*/   }
/*N*/ }

/*N*/ void Outliner::ParaAttribsChanged( USHORT nPara )
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/
/*N*/   // Der Outliner hat kein eigenes Undo, wenn Absaetz getrennt/verschmolzen werden.
/*N*/   // Beim ParagraphInserted ist das Attribut EE_PARA_OUTLLEVEL
/*N*/   // ggf. noch nicht eingestellt, dies wird aber benoetigt um die Tiefe
/*N*/   // des Absatzes zu bestimmen.
/*N*/
/*N*/   if( pEditEngine->IsInUndo() )
/*N*/   {
/*?*/       if ( pParaList->GetParagraphCount() == pEditEngine->GetParagraphCount() )
/*?*/       {
/*?*/           Paragraph* pPara = pParaList->GetParagraph( nPara );
/*?*/           const SfxUInt16Item& rLevel = (const SfxUInt16Item&) pEditEngine->GetParaAttrib( nPara, EE_PARA_OUTLLEVEL );
/*?*/           if ( pPara->GetDepth() != rLevel.GetValue() )
/*?*/           {
/*?*/               USHORT nMin = Min( pPara->GetDepth(), (USHORT)rLevel.GetValue() );
/*?*/               pPara->SetDepth( rLevel.GetValue() );
/*?*/               ImplCalcBulletText( nPara, TRUE, TRUE );
/*?*/           }
/*?*/       }
/*N*/   }
/*N*/ }

//STRIP001 void Outliner::StyleSheetChanged( SfxStyleSheet* pStyle )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001
//STRIP001  // Die EditEngine ruft StyleSheetChanged auch fuer abgeleitete Styles.
//STRIP001  // MT: Hier wurde frueher alle Absaetze durch ein ImpRecalcParaAttribs
//STRIP001  // gejagt, die die besagte Vorlage haben, warum?
//STRIP001  // => Eigentlich kann sich nur die Bullet-Repraesentation aendern...
//STRIP001
//STRIP001  USHORT nParas = (USHORT)pParaList->GetParagraphCount();
//STRIP001  for( USHORT nPara = 0; nPara < nParas; nPara++ )
//STRIP001  {
//STRIP001      if ( pEditEngine->GetStyleSheet( nPara ) == pStyle )
//STRIP001      {
//STRIP001          ImplCheckNumBulletItem( nPara );
//STRIP001          ImplCalcBulletText( nPara, FALSE, FALSE );
//STRIP001             // #97333# EditEngine formats changed paragraphs before calling this method,
//STRIP001             // so they are not reformatted now and use wrong bullet indent
//STRIP001             pEditEngine->QuickMarkInvalid( ESelection( nPara, 0, nPara, 0 ) );
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*N*/ Rectangle Outliner::ImpCalcBulletArea( USHORT nPara, BOOL bAdjust, BOOL bReturnPaperPos )
/*N*/ {
/*N*/   // Bullet-Bereich innerhalb des Absatzes...
/*N*/   Rectangle aBulletArea;
/*N*/
/*N*/   const SvxNumberFormat* pFmt = ImplGetBullet( nPara );
/*N*/   if ( pFmt )
/*N*/   {
/*N*/       Point aTopLeft;
/*N*/       Size aBulletSize( ImplGetBulletSize( nPara ) );
/*N*/
/*N*/         BOOL bOutlineMode = ( pEditEngine->GetControlWord() & EE_CNTRL_OUTLINER ) != 0;
/*N*/
/*N*/         const SvxLRSpaceItem& rLR = (const SvxLRSpaceItem&) pEditEngine->GetParaAttrib( nPara, bOutlineMode ? EE_PARA_OUTLLRSPACE : EE_PARA_LRSPACE );
/*N*/       aTopLeft.X() = rLR.GetTxtLeft() + rLR.GetTxtFirstLineOfst();
/*N*/
/*N*/
/*N*/       long nBulletWidth = Max( (long) -rLR.GetTxtFirstLineOfst(), (long) ((-pFmt->GetFirstLineOffset()) + pFmt->GetCharTextDistance()) );
/*N*/       if ( nBulletWidth < aBulletSize.Width() )   // Bullet macht sich Platz
/*N*/           nBulletWidth = aBulletSize.Width();
/*N*/
/*N*/       if ( bAdjust && !bOutlineMode )
/*N*/       {{DBG_BF_ASSERT(0, "STRIP");}//STRIP001
//STRIP001 /*?*/            // Bei zentriert/rechtsbuendig anpassen
//STRIP001 /*?*/            const SvxAdjustItem& rItem = (const SvxAdjustItem&)pEditEngine->GetParaAttrib( nPara, EE_PARA_JUST );
//STRIP001 /*?*/            if ( ( !pEditEngine->IsRightToLeft( nPara ) && ( rItem.GetAdjust() != SVX_ADJUST_LEFT ) ) ||
//STRIP001 /*?*/                 ( pEditEngine->IsRightToLeft( nPara ) && ( rItem.GetAdjust() != SVX_ADJUST_RIGHT ) ) )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                {DBG_BF_ASSERT(0, "STRIP");}//STRIP001 aTopLeft.X() = pEditEngine->GetFirstLineStartX( nPara ) - nBulletWidth;
//STRIP001 /*?*/            }
/*N*/       }
/*N*/
/*N*/       // Vertikal:
/*N*/       ParagraphInfos aInfos = pEditEngine->GetParagraphInfos( nPara );
/*N*/       if ( aInfos.bValid )
/*N*/       {
/*?*/           aTopLeft.Y() = /* aInfos.nFirstLineOffset + */ // #91076# nFirstLineOffset is already added to the StartPos (PaintBullet) from the EditEngine
/*?*/                           aInfos.nFirstLineHeight - aInfos.nFirstLineTextHeight
/*?*/                           + aInfos.nFirstLineTextHeight / 2
/*?*/                           - aBulletSize.Height() / 2;
/*?*/           // ggf. lieber auf der Baseline ausgeben...
/*?*/           if( ( pFmt->GetNumberingType() != SVX_NUM_NUMBER_NONE ) && ( pFmt->GetNumberingType() != SVX_NUM_BITMAP ) && ( pFmt->GetNumberingType() != SVX_NUM_CHAR_SPECIAL ) )
/*?*/           {
/*?*/               Font aBulletFont( ImpCalcBulletFont( nPara ) );
/*?*/               if ( aBulletFont.GetCharSet() != RTL_TEXTENCODING_SYMBOL )
/*?*/               {
/*?*/                   OutputDevice* pRefDev = pEditEngine->GetRefDevice();
/*?*/                   Font aOldFont = pRefDev->GetFont();
/*?*/                   pRefDev->SetFont( aBulletFont );
/*?*/                   FontMetric aMetric( pRefDev->GetFontMetric() );
/*?*/                   // Leading der ersten Zeile...
/*?*/                   aTopLeft.Y() = /* aInfos.nFirstLineOffset + */ aInfos.nFirstLineMaxAscent;
/*?*/                   aTopLeft.Y() -= aMetric.GetAscent();
/*?*/                   pRefDev->SetFont( aOldFont );
/*?*/               }
/*?*/           }
/*N*/       }
/*N*/
/*N*/       // Horizontal:
/*N*/       if( pFmt->GetNumAdjust() == SVX_ADJUST_RIGHT )
/*N*/       {
/*?*/           aTopLeft.X() += nBulletWidth - aBulletSize.Width();
/*N*/       }
/*N*/       else if( pFmt->GetNumAdjust() == SVX_ADJUST_CENTER )
/*N*/       {
/*?*/           aTopLeft.X() += ( nBulletWidth - aBulletSize.Width() ) / 2;
/*N*/       }
/*N*/
/*N*/       if ( aTopLeft.X() < 0 )     // dann draengeln
/*?*/           aTopLeft.X() = 0;
/*N*/
/*N*/       aBulletArea = Rectangle( aTopLeft, aBulletSize );
/*N*/   }
/*N*/     if ( bReturnPaperPos )
/*N*/     {
/*?*/         DBG_BF_ASSERT(0, "STRIP"); //STRIP001 Size aBulletSize( aBulletArea.GetSize() );
//STRIP001 /*?*/         Point aBulletDocPos( aBulletArea.TopLeft() );
//STRIP001 /*?*/         aBulletDocPos.Y() += pEditEngine->GetDocPosTopLeft( nPara ).Y();
//STRIP001 /*?*/         Point aBulletPos( aBulletDocPos );
//STRIP001 /*?*/
//STRIP001 /*?*/        if ( IsVertical() )
//STRIP001 /*?*/        {
//STRIP001 /*?*/             aBulletPos.Y() = aBulletDocPos.X();
//STRIP001 /*?*/             aBulletPos.X() = GetPaperSize().Width() - aBulletDocPos.Y();
//STRIP001 /*?*/             // Rotate:
//STRIP001 /*?*/             aBulletPos.X() -= aBulletSize.Height();
//STRIP001 /*?*/             Size aSz( aBulletSize );
//STRIP001 /*?*/             aBulletSize.Width() = aSz.Height();
//STRIP001 /*?*/             aBulletSize.Height() = aSz.Width();
//STRIP001 /*?*/        }
//STRIP001 /*?*/         else if ( pEditEngine->IsRightToLeft( nPara ) )
//STRIP001 /*?*/         {
//STRIP001 /*?*/             aBulletPos.X() = GetPaperSize().Width() - aBulletDocPos.X() - aBulletSize.Width();
//STRIP001 /*?*/         }
//STRIP001 /*?*/
//STRIP001 /*?*/        aBulletArea = Rectangle( aBulletPos, aBulletSize );
/*N*/     }
/*N*/   return aBulletArea;
/*N*/ }

//STRIP001 void Outliner::ExpandHdl()
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  aExpandHdl.Call( this );
//STRIP001 }

//STRIP001 void Outliner::OverwriteLevel0Bullet( const SvxNumberFormat& rNumberFormat )
//STRIP001 {
//STRIP001     delete pOverwriteLevel0Bullet;
//STRIP001     pOverwriteLevel0Bullet = new SvxNumberFormat( rNumberFormat );
//STRIP001 }

/*N*/ EBulletInfo Outliner::GetBulletInfo( USHORT nPara )
/*N*/ {
/*N*/     EBulletInfo aInfo;
/*N*/
/*N*/     aInfo.nParagraph = nPara;
/*N*/     aInfo.bVisible = ImplHasBullet( nPara );
/*N*/
/*N*/     const SvxNumberFormat* pFmt = ImplGetBullet( nPara );
/*N*/     aInfo.nType = pFmt ? pFmt->GetNumberingType() : 0;
/*N*/
/*N*/     if( pFmt )
/*N*/     {
/*N*/         if( pFmt->GetNumberingType() != SVX_NUM_BITMAP )
/*N*/         {
/*N*/             aInfo.aText = ImplGetBulletText( nPara );
/*N*/
/*N*/             if( pFmt->GetBulletFont() )
/*N*/                 aInfo.aFont = *pFmt->GetBulletFont();
/*N*/         }
/*N*/         else if ( pFmt->GetBrush()->GetGraphicObject() )
/*N*/         {
/*N*/             aInfo.aGraphic = pFmt->GetBrush()->GetGraphicObject()->GetGraphic();
/*N*/         }
/*N*/     }
/*N*/
/*N*/     if ( aInfo.bVisible )
/*N*/     {
/*N*/         aInfo.aBounds = ImpCalcBulletArea( nPara, TRUE, TRUE );
/*N*/     }
/*N*/
/*N*/     return aInfo;
/*N*/ }

/*N*/ XubString Outliner::GetText( Paragraph* pParagraph, ULONG nCount ) const
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/
/*N*/   XubString aText;
/*N*/   USHORT nStartPara = (USHORT) pParaList->GetAbsPos( pParagraph );
/*N*/   for ( USHORT n = 0; n < nCount; n++ )
/*N*/   {
/*N*/       aText += pEditEngine->GetText( nStartPara + n );
/*N*/       if ( (n+1) < (USHORT)nCount )
/*N*/           aText += '\n';
/*N*/   }
/*N*/   return aText;
/*N*/ }

//STRIP001 void Outliner::Remove( Paragraph* pPara, ULONG nParaCount )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001
//STRIP001  ULONG nPos = pParaList->GetAbsPos( pPara );
//STRIP001  if( !nPos && ( nParaCount >= pParaList->GetParagraphCount() ) )
//STRIP001  {
//STRIP001      Clear();
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      for( USHORT n = 0; n < (USHORT)nParaCount; n++ )
//STRIP001          pEditEngine->RemoveParagraph( (USHORT) nPos );
//STRIP001  }
//STRIP001 }

/*N*/ void Outliner::StripPortions()
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   bStrippingPortions = TRUE;
/*N*/   pEditEngine->StripPortions();
/*N*/   bStrippingPortions = FALSE;
/*N*/ }

// #101498#
/*N*/ void Outliner::DrawingText( const Point& rStartPos, const XubString& rText, USHORT nTextStart, USHORT nTextLen, const long* pDXArray,const SvxFont& rFont, USHORT nPara, USHORT nIndex, BYTE nRightToLeft)
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/
/*N*/   // #101498#
/*N*/   DrawPortionInfo aInfo( rStartPos, rText, nTextStart, nTextLen, rFont, nPara, nIndex, pDXArray, nRightToLeft);
/*N*/
/*N*/   aDrawPortionHdl.Call( &aInfo );
/*N*/ }

//STRIP001 long Outliner::RemovingPagesHdl( OutlinerView* pView )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  return aRemovingPagesHdl.IsSet() ? aRemovingPagesHdl.Call( pView ) : TRUE;
//STRIP001 }

//STRIP001 BOOL Outliner::ImpCanDeleteSelectedPages( OutlinerView* pCurView, USHORT nFirstPage, USHORT nPages )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001
//STRIP001  nDepthChangedHdlPrevDepth = nPages;
//STRIP001  pHdlParagraph = (Paragraph*)nFirstPage;
//STRIP001  return (BOOL)RemovingPagesHdl( pCurView );
//STRIP001 }

/*N*/ SfxItemSet Outliner::GetParaAttribs( ULONG nPara )
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   return pEditEngine->GetParaAttribs( (USHORT)nPara );
/*N*/ }

/*N*/ IMPL_LINK( Outliner, ParaVisibleStateChangedHdl, Paragraph*, pPara )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001
//STRIP001  ULONG nPara = pParaList->GetAbsPos( pPara );
//STRIP001  pEditEngine->ShowParagraph( (USHORT)nPara, pPara->IsVisible() );
//STRIP001
/*N*/   return 0;
/*N*/ }

/*N*/ IMPL_LINK( Outliner, BeginMovingParagraphsHdl, MoveParagraphsInfo*, pInfos )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001
//STRIP001  GetBeginMovingHdl().Call( this );
//STRIP001
/*N*/   return 0;
/*N*/ }

/*N*/ IMPL_LINK( Outliner, BeginPasteOrDropHdl, PasteOrDropInfos*, pInfos )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001     BOOL bCheckStyles = ( ( ImplGetOutlinerMode() == OUTLINERMODE_OUTLINEOBJECT ) || ( ImplGetOutlinerMode() == OUTLINERMODE_OUTLINEVIEW ) );
//STRIP001     if ( bCheckStyles )
//STRIP001     {
//STRIP001         UndoActionStart( EDITUNDO_DRAGANDDROP );
//STRIP001         for ( USHORT n = GetParagraphCount(); n; )
//STRIP001         {
//STRIP001             if ( GetDepth( --n ) )
//STRIP001             {
//STRIP001                 pInfos->pLevelNStyle = GetStyleSheet( n );
//STRIP001                 break;
//STRIP001             }
//STRIP001         }
//STRIP001         if ( ImplGetOutlinerMode() == OUTLINERMODE_OUTLINEVIEW )
//STRIP001             pInfos->pLevel0Style = GetStyleSheet( 0 );
//STRIP001     }
//STRIP001
/*N*/   return 0;
/*N*/ }

/*N*/ IMPL_LINK( Outliner, EndPasteOrDropHdl, PasteOrDropInfos*, pInfos )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001     if ( pInfos->nAction == EE_ACTION_PASTE )
//STRIP001     {
//STRIP001         bPasting = FALSE;
//STRIP001         ImpTextPasted( pInfos->nStartPara, pInfos->nEndPara - pInfos->nStartPara + 1 );
//STRIP001     }
//STRIP001     else
//STRIP001     {
//STRIP001         for ( USHORT nPara = pInfos->nStartPara; nPara <= pInfos->nEndPara; nPara++ )
//STRIP001         {
//STRIP001             USHORT nOutlLevel = nMinDepth;
//STRIP001             if ( nPara )
//STRIP001             {
//STRIP001              const SfxUInt16Item& rLevel = (const SfxUInt16Item&) pEditEngine->GetParaAttrib( nPara, EE_PARA_OUTLLEVEL );
//STRIP001              nOutlLevel = rLevel.GetValue();
//STRIP001             }
//STRIP001             ImplCheckDepth( nOutlLevel );
//STRIP001
//STRIP001             Paragraph* pPara = GetParagraph( nPara );
//STRIP001             if ( nOutlLevel != pPara->GetDepth() )
//STRIP001             {
//STRIP001              pHdlParagraph = pPara;
//STRIP001              nDepthChangedHdlPrevDepth = pPara->GetDepth();
//STRIP001              ImplInitDepth( nPara, nOutlLevel, FALSE );
//STRIP001                 pEditEngine->QuickMarkInvalid( ESelection( nPara, 0, nPara, 0 ) );
//STRIP001              DepthChangedHdl();
//STRIP001             }
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001     BOOL bCheckStyles = ( ( ImplGetOutlinerMode() == OUTLINERMODE_OUTLINEOBJECT ) || ( ImplGetOutlinerMode() == OUTLINERMODE_OUTLINEVIEW ) );
//STRIP001     if ( bCheckStyles )
//STRIP001     {
//STRIP001         BOOL bOutlineView = ( ImplGetOutlinerMode() == OUTLINERMODE_OUTLINEVIEW );
//STRIP001         for ( USHORT n = pInfos->nStartPara; n <= pInfos->nEndPara; n++ )
//STRIP001         {
//STRIP001             USHORT nDepth = GetDepth( n );
//STRIP001             Paragraph* pPara = GetParagraph( n );
//STRIP001
//STRIP001             // Prefer depth from pasted text
//STRIP001             // First paragraph in OutlineView cannot be on Level > 0!
//STRIP001             const SfxUInt16Item& rLevel = (const SfxUInt16Item&) pEditEngine->GetParaAttrib( n, EE_PARA_OUTLLEVEL );
//STRIP001             if ( ( nDepth < GetMinDepth() ) || ( rLevel.GetValue() != nDepth ) || ( bOutlineView && ( n == 0 ) && ( nDepth != 0 ) ) )
//STRIP001             {
//STRIP001                 nDepth = rLevel.GetValue();
//STRIP001                 if ( bOutlineView && !n )
//STRIP001                     nDepth = 0;
//STRIP001                 ImplCheckDepth( nDepth );
//STRIP001              ImplInitDepth( n, nDepth, TRUE );
//STRIP001             }
//STRIP001
//STRIP001             if ( bOutlineView && ( nDepth == 0 ) )
//STRIP001             {
//STRIP001                 if ( pInfos->pLevel0Style && ( GetStyleSheet( n ) != pInfos->pLevel0Style ) )
//STRIP001                 {
//STRIP001                  SetStyleSheet( n, pInfos->pLevel0Style );
//STRIP001                 }
//STRIP001             }
//STRIP001             else
//STRIP001             {
//STRIP001                 // ImplSetLevelDependendStyleSheet checks if stylesheet changes...
//STRIP001                 ImplSetLevelDependendStyleSheet( n, pInfos->pLevelNStyle );
//STRIP001             }
//STRIP001             ImplCheckNumBulletItem( n );
//STRIP001         }
//STRIP001         UndoActionEnd( EDITUNDO_DRAGANDDROP );
//STRIP001
//STRIP001     }
//STRIP001
/*N*/   return 0;
/*N*/ }

/*N*/ IMPL_LINK( Outliner, EndMovingParagraphsHdl, MoveParagraphsInfo*, pInfos )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001
//STRIP001  pParaList->MoveParagraphs( pInfos->nStartPara, pInfos->nDestPara, pInfos->nEndPara - pInfos->nStartPara + 1 );
//STRIP001  USHORT nChangesStart = Min( pInfos->nStartPara, pInfos->nDestPara );
//STRIP001  USHORT nParas = (USHORT)pParaList->GetParagraphCount();
//STRIP001  for ( USHORT n = nChangesStart; n < nParas; n++ )
//STRIP001      ImplCalcBulletText( n, FALSE, FALSE );
//STRIP001
//STRIP001     // ersten Absatz immer auf Ebene 0 stellen
//STRIP001  Paragraph* pStartPara = pParaList->GetParagraph( 0 );
//STRIP001  if( pStartPara->GetDepth() != GetMinDepth() )
//STRIP001  {
//STRIP001      SetDepth( pStartPara, GetMinDepth() );
//STRIP001      if ( ImplGetOutlinerMode() == OUTLINERMODE_OUTLINEOBJECT )
//STRIP001          ImplSetLevelDependendStyleSheet( 0 );
//STRIP001  }
//STRIP001
//STRIP001  aEndMovingHdl.Call( this );
//STRIP001
/*N*/     return 0;
/*N*/ }

/*N*/ void Outliner::ImplCalcBulletText( USHORT nPara, BOOL bRecalcLevel, BOOL bRecalcChilds )
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/
/*N*/   Paragraph* pPara = pParaList->GetParagraph( nPara );
/*N*/   USHORT nRelPos = 0xFFFF;
/*N*/
/*N*/   while ( pPara )
/*N*/   {
/*N*/       XubString aBulletText;
/*N*/       const SvxNumberFormat* pFmt = ImplGetBullet( nPara );
/*N*/       if( pFmt && ( pFmt->GetNumberingType() != SVX_NUM_BITMAP ) )
/*N*/       {
/*N*/           aBulletText += pFmt->GetPrefix();
/*N*/           if( pFmt->GetNumberingType() == SVX_NUM_CHAR_SPECIAL )
/*N*/           {
/*N*/               aBulletText += pFmt->GetBulletChar();
/*N*/           }
/*N*/           else if( pFmt->GetNumberingType() != SVX_NUM_NUMBER_NONE )
/*N*/           {
/*?*/               if ( nRelPos == 0xFFFF )
/*?*/                   {DBG_BF_ASSERT(0, "STRIP");} //STRIP001 pParaList->GetParent( pPara, nRelPos );
/*?*/               USHORT nNumber = nRelPos + pFmt->GetStart();
/*?*/               aBulletText += pFmt->GetNumStr( nNumber );
/*N*/           }
/*N*/           aBulletText += pFmt->GetSuffix();
/*N*/       }
/*N*/
/*N*/       if( aBulletText != pPara->GetText() )
/*N*/           pPara->SetText( aBulletText );
/*N*/
/*N*/       pPara->nFlags &= (~PARAFLAG_SETBULLETTEXT);
/*N*/
/*N*/       if ( bRecalcLevel )
/*N*/       {
/*N*/           if ( nRelPos != 0xFFFF )
/*N*/               nRelPos++;
/*N*/
/*N*/           USHORT nDepth = pPara->GetDepth();
/*N*/           pPara = pParaList->GetParagraph( ++nPara );
/*N*/           if ( !bRecalcChilds )
/*N*/           {
/*N*/               while ( pPara && ( pPara->GetDepth() > nDepth ) )
/*?*/                   pPara = pParaList->GetParagraph( ++nPara );
/*N*/           }
/*N*/
/*N*/           if ( pPara && ( pPara->GetDepth() < nDepth ) )
/*?*/               pPara = NULL;
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           pPara = NULL;
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ void Outliner::Clear()
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/
/*N*/   if( !bFirstParaIsEmpty )
/*N*/   {
/*N*/       ImplBlockInsertionCallbacks( TRUE );
/*N*/       pEditEngine->Clear();
/*N*/       pParaList->Clear( TRUE );
/*N*/       pParaList->Insert( new Paragraph( nMinDepth ), LIST_APPEND );
/*N*/       bFirstParaIsEmpty = TRUE;
/*N*/       ImplBlockInsertionCallbacks( FALSE );
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       pParaList->GetParagraph( 0 )->SetDepth( nMinDepth );
/*N*/   }
/*N*/ }

//STRIP001 void Outliner::SetFlatMode( BOOL bFlat )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001
//STRIP001  if( bFlat != pEditEngine->IsFlatMode() )
//STRIP001  {
//STRIP001      for ( USHORT nPara = (USHORT)pParaList->GetParagraphCount(); nPara; )
//STRIP001          pParaList->GetParagraph( --nPara )->aBulSize.Width() = -1;
//STRIP001
//STRIP001      pEditEngine->SetFlatMode( bFlat );
//STRIP001  }
//STRIP001 }

/*N*/ String Outliner::ImplGetBulletText( USHORT nPara )
/*N*/ {
/*N*/   Paragraph* pPara = pParaList->GetParagraph( nPara );
/*N*/   // MT: Optimierung mal wieder aktivieren...
/*N*/ //    if( pPara->nFlags & PARAFLAG_SETBULLETTEXT )
/*N*/       ImplCalcBulletText( nPara, FALSE, FALSE );
/*N*/   return pPara->GetText();
/*N*/ }

// this is needed for StarOffice Api
/*N*/ void Outliner::SetLevelDependendStyleSheet( USHORT nPara )
/*N*/ {
/*N*/   SfxItemSet aOldAttrs( pEditEngine->GetParaAttribs( nPara ) );
/*N*/   ImplSetLevelDependendStyleSheet( nPara );
/*N*/   pEditEngine->SetParaAttribs( nPara, aOldAttrs );
/*N*/ }

/*N*/ SV_IMPL_PTRARR( NotifyList, EENotifyPtr );

/*N*/ void Outliner::ImplBlockInsertionCallbacks( BOOL b )
/*N*/ {
/*N*/     if ( b )
/*N*/     {
/*N*/         bBlockInsCallback++;
/*N*/     }
/*N*/     else
/*N*/     {
/*N*/         DBG_ASSERT( bBlockInsCallback, "ImplBlockInsertionCallbacks ?!" );
/*N*/         bBlockInsCallback--;
/*N*/         if ( !bBlockInsCallback )
/*N*/         {
/*N*/             // Call blocked notify events...
/*N*/             while ( pEditEngine->aNotifyCache.Count() )
/*N*/             {
/*?*/                 EENotify* pNotify = pEditEngine->aNotifyCache[0];
/*?*/                 // Remove from list before calling, maybe we enter LeaveBlockNotifications while calling the handler...
/*?*/                 pEditEngine->aNotifyCache.Remove( 0 );
/*?*/                 pEditEngine->aOutlinerNotifyHdl.Call( pNotify );
/*?*/                 delete pNotify;
/*N*/             }
/*N*/         }
/*N*/     }
/*N*/ }


/*N*/ IMPL_LINK( Outliner, EditEngineNotifyHdl, EENotify*, pNotify )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001     if ( !bBlockInsCallback )
//STRIP001     {
//STRIP001         pEditEngine->aOutlinerNotifyHdl.Call( pNotify );
//STRIP001     }
//STRIP001     else
//STRIP001     {
//STRIP001         EENotify* pNewNotify = new EENotify( *pNotify );
//STRIP001         pEditEngine->aNotifyCache.Insert( pNewNotify, pEditEngine->aNotifyCache.Count() );
//STRIP001     }
//STRIP001
/*N*/     return 0;
/*N*/ }

/*N*/ sal_Bool DrawPortionInfo::IsRTL() const
/*N*/ {
/*N*/   if(0xFF == mnBiDiLevel)
/*N*/   {
/*?*/         // Use Bidi functions from icu 2.0 to calculate if this portion
/*?*/       // is RTL or not.
/*?*/         UErrorCode nError(U_ZERO_ERROR);
/*?*/         UBiDi* pBidi = ubidi_openSized(rText.Len(), 0, &nError);
/*?*/         nError = U_ZERO_ERROR;
/*?*/
/*?*/       // I do not have this info here. Is it necessary? I'll have to ask MT.
/*?*/       const BYTE nDefaultDir = UBIDI_LTR; //IsRightToLeft( nPara ) ? UBIDI_RTL : UBIDI_LTR;
/*?*/
/*?*/       ubidi_setPara(pBidi, rText.GetBuffer(), rText.Len(), nDefaultDir, NULL, &nError);
/*?*/         nError = U_ZERO_ERROR;
/*?*/
/*?*/         sal_Int32 nCount(ubidi_countRuns(pBidi, &nError));
/*?*/
/*?*/         int32_t nStart(0);
/*?*/         int32_t nEnd;
/*?*/         UBiDiLevel nCurrDir;
/*?*/
/*?*/       ubidi_getLogicalRun(pBidi, nStart, &nEnd, &nCurrDir);
/*?*/
/*?*/         ubidi_close(pBidi);
/*?*/
/*?*/       // remember on-demand calculated state
/*?*/       ((DrawPortionInfo*)this)->mnBiDiLevel = nCurrDir;
/*N*/   }
/*N*/
/*N*/   return (1 == (mnBiDiLevel % 2));
/*N*/ }

}
