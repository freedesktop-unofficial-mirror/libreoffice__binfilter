/*************************************************************************
 *
 *  $RCSfile: svx_editdoc2.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:40:25 $
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

#include <eeng_pch.hxx>

#pragma hdrstop

#ifndef _SFXSMPLHINT_HXX //autogen
#include <svtools/smplhint.hxx>
#endif
#include <tools/rtti.hxx>
#include <lspcitem.hxx>
#include <adjitem.hxx>
#include <tstpitem.hxx>

#include <editdoc.hxx>
#include <impedit.hxx>
#include <editdbg.hxx>

#include <numitem.hxx>

#include "akrnitem.hxx"
#include "cntritem.hxx"
#include "colritem.hxx"
#include "crsditem.hxx"
#include "escpitem.hxx"
#include "fhgtitem.hxx"
#include "fontitem.hxx"
#include "kernitem.hxx"
#include "lrspitem.hxx"
#include "postitem.hxx"
#include "shdditem.hxx"
#include "udlnitem.hxx"
#include "ulspitem.hxx"
#include "wghtitem.hxx"
#include "wrlmitem.hxx"
#include <charscaleitem.hxx>

#include <vcl/svapp.hxx>    // Fuer AppWindow...
namespace binfilter {

/*N*/ DBG_NAME( EE_ParaPortion )

/*N*/ SV_IMPL_VARARR( CharPosArray, long );

/*

BOOL EditStyleSheet::HasStyleAsAnyParent( SfxStyleSheet& rStyle )
{
    if ( GetParent() == rStyle.GetName() )
        return TRUE;

    if ( GetParent().Len() && ( GetParent() != GetName() ) )
    {
        EditStyleSheet* pS = (EditStyleSheet*)GetPool().Find( GetParent(), rStyle.GetFamily() );
        if ( pS )
            return pS->HasStyleAsAnyParent( rStyle );
    }
    return FALSE;
}

*/

// -------------------------------------------------------------------------
// class TextPortionList
// -------------------------------------------------------------------------
/*N*/ TextPortionList::TextPortionList()
/*N*/ {
/*N*/ }

/*N*/ TextPortionList::~TextPortionList()
/*N*/ {
/*N*/   Reset();
/*N*/ }

/*N*/ void TextPortionList::Reset()
/*N*/ {
/*N*/   for ( USHORT nPortion = 0; nPortion < Count(); nPortion++ )
/*N*/       delete GetObject( nPortion );
/*N*/   Remove( 0, Count() );
/*N*/ }

/*N*/ void TextPortionList::DeleteFromPortion( USHORT nDelFrom )
/*N*/ {
/*N*/   DBG_ASSERT( ( nDelFrom < Count() ) || ( (nDelFrom == 0) && (Count() == 0) ), "DeleteFromPortion: Out of range" );
/*N*/   for ( USHORT nP = nDelFrom; nP < Count(); nP++ )
/*N*/       delete GetObject( nP );
/*N*/   Remove( nDelFrom, Count()-nDelFrom );
/*N*/ }

/*N*/ USHORT TextPortionList::FindPortion( USHORT nCharPos, USHORT& nPortionStart, BOOL bPreferStartingPortion )
/*N*/ {
/*N*/   // Bei nCharPos an Portion-Grenze wird die linke Portion gefunden
/*N*/   USHORT nTmpPos = 0;
/*N*/   for ( USHORT nPortion = 0; nPortion < Count(); nPortion++ )
/*N*/   {
/*N*/       TextPortion* pPortion = GetObject( nPortion );
/*N*/       nTmpPos += pPortion->GetLen();
/*N*/       if ( nTmpPos >= nCharPos )
/*N*/       {
/*N*/             // take this one if we don't prefer the starting portion, or if it's the last one
/*N*/             if ( ( nTmpPos != nCharPos ) || !bPreferStartingPortion || ( nPortion == Count() - 1 ) )
/*N*/             {
/*N*/               nPortionStart = nTmpPos - pPortion->GetLen();
/*N*/               return nPortion;
/*N*/             }
/*N*/       }
/*N*/   }
/*?*/   DBG_ERROR( "FindPortion: Nicht gefunden!" );
/*?*/   return ( Count() - 1 );
/*N*/ }

//STRIP001 USHORT TextPortionList::GetStartPos( USHORT nPortion )
//STRIP001 {
//STRIP001     USHORT nPos = 0;
//STRIP001  for ( USHORT n = 0; n < nPortion; n++ )
//STRIP001  {
//STRIP001      TextPortion* pPortion = GetObject( n );
//STRIP001      nPos += pPortion->GetLen();
//STRIP001  }
//STRIP001     return nPos;
//STRIP001 }


// -------------------------------------------------------------------------
// class ExtraPortionInfo
// -------------------------------------------------------------------------

/*N*/ ExtraPortionInfo::ExtraPortionInfo()
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001     nOrgWidth = 0;
//STRIP001     nWidthFullCompression = 0;
//STRIP001     nMaxCompression100thPercent = 0;
//STRIP001     nAsianCompressionTypes = 0;
//STRIP001     nPortionOffsetX = 0;
//STRIP001     bFirstCharIsRightPunktuation = FALSE;
//STRIP001     bCompressed = FALSE;
//STRIP001     pOrgDXArray = NULL;
/*N*/ }

/*N*/ ExtraPortionInfo::~ExtraPortionInfo()
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001     delete[] pOrgDXArray;
/*N*/ }

//STRIP001 void ExtraPortionInfo::SaveOrgDXArray( const long* pDXArray, USHORT nLen )
//STRIP001 {
//STRIP001     delete[] pOrgDXArray;
//STRIP001     pOrgDXArray = new long[nLen];
//STRIP001     memcpy( pOrgDXArray, pDXArray, nLen*sizeof(long) );
//STRIP001 }

//STRIP001 void ExtraPortionInfo::DestroyOrgDXArray()
//STRIP001 {
//STRIP001     delete[] pOrgDXArray;
//STRIP001     pOrgDXArray = NULL;
//STRIP001 }


// -------------------------------------------------------------------------
// class ParaPortion
// -------------------------------------------------------------------------
/*N*/ ParaPortion::ParaPortion( ContentNode* pN )
/*N*/ {
/*N*/   DBG_CTOR( EE_ParaPortion, 0 );
/*N*/
/*N*/   pNode               = pN;
/*N*/   bInvalid            = TRUE;
/*N*/   bVisible            = TRUE;
/*N*/   bSimple             = FALSE;
/*N*/   bForceRepaint       = FALSE;
/*N*/   nInvalidPosStart    = 0;
/*N*/   nInvalidDiff        = 0;
/*N*/   nHeight             = 0;
/*N*/   nFirstLineOffset    = 0;
/*N*/   nBulletX            = 0;
/*N*/ }

/*N*/ ParaPortion::~ParaPortion()
/*N*/ {
/*N*/   DBG_DTOR( EE_ParaPortion, 0 );
/*N*/ }

/*N*/ void ParaPortion::MarkInvalid( USHORT nStart, short nDiff )
/*N*/ {
/*N*/   if ( bInvalid == FALSE )
/*N*/   {
/*N*/ //        nInvalidPosEnd = nStart;    // ??? => CreateLines
/*N*/       nInvalidPosStart = ( nDiff >= 0 ) ? nStart : ( nStart + nDiff );
/*N*/       nInvalidDiff = nDiff;
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       // Einfaches hintereinander tippen
/*N*/       if ( ( nDiff > 0 ) && ( nInvalidDiff > 0 ) &&
/*N*/            ( ( nInvalidPosStart+nInvalidDiff ) == nStart ) )
/*N*/       {
/*N*/           nInvalidDiff += nDiff;
/*N*/       }
/*N*/       // Einfaches hintereinander loeschen
/*N*/       else if ( ( nDiff < 0 ) && ( nInvalidDiff < 0 ) && ( nInvalidPosStart == nStart ) )
/*N*/       {
/*?*/           nInvalidPosStart += nDiff;
/*?*/           nInvalidDiff += nDiff;
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/ //            nInvalidPosEnd = pNode->Len();
/*N*/           DBG_ASSERT( ( nDiff >= 0 ) || ( (nStart+nDiff) >= 0 ), "MarkInvalid: Diff out of Range" );
/*N*/           nInvalidPosStart = Min( nInvalidPosStart, (USHORT) ( nDiff < 0 ? nStart+nDiff : nDiff ) );
/*N*/           nInvalidDiff = 0;
/*N*/           bSimple = FALSE;
/*N*/       }
/*N*/   }
/*N*/   bInvalid = TRUE;
/*N*/   aScriptInfos.Remove( 0, aScriptInfos.Count() );
/*N*/   aWritingDirectionInfos.Remove( 0, aWritingDirectionInfos.Count() );
/*N*/ //    aExtraCharInfos.Remove( 0, aExtraCharInfos.Count() );
/*N*/ }

/*N*/ void ParaPortion::MarkSelectionInvalid( USHORT nStart, USHORT nEnd )
/*N*/ {
/*N*/   if ( bInvalid == FALSE )
/*N*/   {
/*N*/       nInvalidPosStart = nStart;
/*N*/ //        nInvalidPosEnd = nEnd;
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       nInvalidPosStart = Min( nInvalidPosStart, nStart );
/*N*/ //        nInvalidPosEnd = pNode->Len();
/*N*/   }
/*N*/   nInvalidDiff = 0;
/*N*/   bInvalid = TRUE;
/*N*/   bSimple = FALSE;
/*N*/   aScriptInfos.Remove( 0, aScriptInfos.Count() );
/*N*/   aWritingDirectionInfos.Remove( 0, aWritingDirectionInfos.Count() );
/*N*/ //    aExtraCharInfos.Remove( 0, aExtraCharInfos.Count() );
/*N*/ }

/*N*/ USHORT ParaPortion::GetLineNumber( USHORT nIndex )
/*N*/ {
/*N*/   DBG_ASSERTWARNING( aLineList.Count(), "Leere ParaPortion in GetLine!" );
/*N*/   DBG_ASSERT( bVisible, "Wozu GetLine() bei einem unsichtbaren Absatz?" );
/*N*/
/*N*/   for ( USHORT nLine = 0; nLine < aLineList.Count(); nLine++ )
/*N*/   {
/*N*/       if ( aLineList[nLine]->IsIn( nIndex ) )
/*N*/           return nLine;
/*N*/   }
/*N*/
/*?*/   // Dann sollte es am Ende der letzten Zeile sein!
/*?*/   DBG_ASSERT( nIndex == aLineList[ aLineList.Count() - 1 ]->GetEnd(), "Index voll daneben!" );
/*?*/   return (aLineList.Count()-1);
/*N*/ }

//STRIP001 void ParaPortion::SetVisible( BOOL bMakeVisible )
//STRIP001 {
//STRIP001  bVisible = bMakeVisible;
//STRIP001 }

/*N*/ void ParaPortion::CorrectValuesBehindLastFormattedLine( USHORT nLastFormattedLine )
/*N*/ {
/*N*/   USHORT nLines = aLineList.Count();
/*N*/   DBG_ASSERT( nLines, "CorrectPortionNumbersFromLine: Leere Portion?" );
/*N*/   if ( nLastFormattedLine < ( nLines - 1 ) )
/*N*/   {
/*?*/       const EditLine* pLastFormatted = aLineList[ nLastFormattedLine ];
/*?*/       const EditLine* pUnformatted = aLineList[ nLastFormattedLine+1 ];
/*?*/       short nPortionDiff = pUnformatted->GetStartPortion() - pLastFormatted->GetEndPortion();
/*?*/       short nTextDiff = pUnformatted->GetStart() - pLastFormatted->GetEnd();
/*?*/       nTextDiff++;    // LastFormatted->GetEnd() war incl. => 1 zuviel abgezogen!
/*?*/
/*?*/       // Die erste unformatierte muss genau eine Portion hinter der letzten der
/*?*/       // formatierten beginnen:
/*?*/       // Wenn in der geaenderten Zeile eine Portion gesplittet wurde,
/*?*/       // kann nLastEnd > nNextStart sein!
/*?*/       short nPDiff = -( nPortionDiff-1 );
/*?*/       short nTDiff = -( nTextDiff-1 );
/*?*/       if ( nPDiff || nTDiff )
/*?*/       {
/*?*/           for ( USHORT nL = nLastFormattedLine+1; nL < nLines; nL++ )
/*?*/           {
/*?*/               EditLine* pLine = aLineList[ nL ];
/*?*/
/*?*/               pLine->GetStartPortion() += nPDiff;
/*?*/               pLine->GetEndPortion() += nPDiff;
/*?*/
/*?*/               pLine->GetStart() += nTDiff;
/*?*/               pLine->GetEnd() += nTDiff;
/*?*/
/*?*/               pLine->SetValid();
/*?*/           }
/*?*/       }
/*N*/   }
/*N*/   DBG_ASSERT( aLineList[ aLineList.Count()-1 ]->GetEnd() == pNode->Len(), "CorrectLines: Ende stimmt nicht!" );
/*N*/ }

// -------------------------------------------------------------------------
// class ParaPortionList
// -------------------------------------------------------------------------
/*N*/ ParaPortionList::ParaPortionList()
/*N*/ {
/*N*/ }

/*N*/ ParaPortionList::~ParaPortionList()
/*N*/ {
/*N*/   Reset();
/*N*/ }

/*N*/ void ParaPortionList::Reset()
/*N*/ {
/*N*/   for ( USHORT nPortion = 0; nPortion < Count(); nPortion++ )
/*N*/       delete GetObject( nPortion );
/*N*/   Remove( 0, Count() );
/*N*/ }

/*N*/ long ParaPortionList::GetYOffset( ParaPortion* pPPortion )
/*N*/ {
/*N*/   long nHeight = 0;
/*N*/   for ( USHORT nPortion = 0; nPortion < Count(); nPortion++ )
/*N*/   {
/*N*/       ParaPortion* pTmpPortion = GetObject(nPortion);
/*N*/       if ( pTmpPortion == pPPortion )
/*N*/           return nHeight;
/*?*/       nHeight += pTmpPortion->GetHeight();
/*?*/   }
/*?*/   DBG_ERROR( "GetYOffset: Portion nicht gefunden" );
/*?*/   return nHeight;
/*N*/ }

/*N*/ USHORT ParaPortionList::FindParagraph( long nYOffset )
/*N*/ {
/*N*/   long nY = 0;
/*N*/   for ( USHORT nPortion = 0; nPortion < Count(); nPortion++ )
/*N*/   {
/*N*/       nY += GetObject(nPortion)->GetHeight(); // sollte auch bei !bVisible richtig sein!
/*N*/       if ( nY > nYOffset )
/*N*/           return nPortion;
/*N*/   }
/*N*/   return 0xFFFF;  // solte mal ueber EE_PARA_NOT_FOUND erreicht werden!
/*N*/ }

//STRIP001 void ParaPortionList::DbgCheck( EditDoc& rDoc )
//STRIP001 {
//STRIP001 #ifdef DBG_UTIL
//STRIP001  DBG_ASSERT( Count() == rDoc.Count(), "ParaPortionList::DbgCheck() - Count() ungleich!" );
//STRIP001  for ( USHORT i = 0; i < Count(); i++ )
//STRIP001  {
//STRIP001      DBG_ASSERT( SaveGetObject(i), "ParaPortionList::DbgCheck() - Null-Pointer in Liste!" );
//STRIP001      DBG_ASSERT( GetObject(i)->GetNode(), "ParaPortionList::DbgCheck() - Null-Pointer in Liste(2)!" );
//STRIP001      DBG_ASSERT( GetObject(i)->GetNode() == rDoc.GetObject(i), "ParaPortionList::DbgCheck() - Eintraege kreuzen sich!" );
//STRIP001  }
//STRIP001 #endif
//STRIP001 }


//STRIP001 ContentAttribsInfo::ContentAttribsInfo( const SfxItemSet& rParaAttribs ) :
//STRIP001      aPrevParaAttribs( rParaAttribs)
//STRIP001 {
//STRIP001 }


/*N*/ void ConvertItem( SfxPoolItem& rPoolItem, MapUnit eSourceUnit, MapUnit eDestUnit )
/*N*/ {
/*N*/   DBG_ASSERT( eSourceUnit != eDestUnit, "ConvertItem - Why?!" );
/*N*/
/*N*/   switch ( rPoolItem.Which() )
/*N*/   {
/*N*/       case EE_PARA_LRSPACE:
/*N*/       {DBG_BF_ASSERT(0, "STRIP");//STRIP001
//STRIP001          DBG_ASSERT( rPoolItem.IsA( TYPE( SvxLRSpaceItem ) ), "ConvertItem: Ungueltiges Item!" );
//STRIP001          SvxLRSpaceItem& rItem = (SvxLRSpaceItem&)rPoolItem;
//STRIP001          rItem.SetTxtFirstLineOfst( OutputDevice::LogicToLogic( rItem.GetTxtFirstLineOfst(), eSourceUnit, eDestUnit ) );
//STRIP001          rItem.SetTxtLeft( OutputDevice::LogicToLogic( rItem.GetTxtLeft(), eSourceUnit, eDestUnit ) );
//STRIP001 //           rItem.SetLeft( OutputDevice::LogicToLogic( rItem.GetLeft(), eSourceUnit, eDestUnit ) ); // #96298# SetLeft manipulates nTxtLeft!
//STRIP001          rItem.SetRight( OutputDevice::LogicToLogic( rItem.GetRight(), eSourceUnit, eDestUnit ) );
/*N*/       }
/*N*/       break;
/*N*/       case EE_PARA_ULSPACE:
/*N*/       {DBG_BF_ASSERT(0, "STRIP");//STRIP001
//STRIP001          DBG_ASSERT( rPoolItem.IsA( TYPE( SvxULSpaceItem ) ), "ConvertItem: Ungueltiges Item!" );
//STRIP001          SvxULSpaceItem& rItem = (SvxULSpaceItem&)rPoolItem;
//STRIP001          rItem.SetUpper( OutputDevice::LogicToLogic( rItem.GetUpper(), eSourceUnit, eDestUnit ) );
//STRIP001          rItem.SetLower( OutputDevice::LogicToLogic( rItem.GetLower(), eSourceUnit, eDestUnit ) );
/*N*/       }
/*N*/       break;
/*N*/       case EE_PARA_SBL:
/*N*/       {DBG_BF_ASSERT(0, "STRIP");//STRIP001
//STRIP001          DBG_ASSERT( rPoolItem.IsA( TYPE( SvxLineSpacingItem ) ), "ConvertItem: Ungueltiges Item!" );
//STRIP001          SvxLineSpacingItem& rItem = (SvxLineSpacingItem&)rPoolItem;
//STRIP001             // #96298# SetLineHeight changes also eLineSpace!
//STRIP001          if ( rItem.GetLineSpaceRule() == SVX_LINE_SPACE_MIN )
//STRIP001              rItem.SetLineHeight( OutputDevice::LogicToLogic( rItem.GetLineHeight(), eSourceUnit, eDestUnit ) );
/*N*/       }
/*N*/       break;
/*N*/       case EE_PARA_TABS:
/*N*/       {DBG_BF_ASSERT(0, "STRIP");//STRIP001
//STRIP001          DBG_ASSERT( rPoolItem.IsA( TYPE( SvxTabStopItem ) ), "ConvertItem: Ungueltiges Item!" );
//STRIP001          SvxTabStopItem& rItem = (SvxTabStopItem&)rPoolItem;
//STRIP001          SvxTabStopItem aNewItem( EE_PARA_TABS );
//STRIP001          for ( USHORT i = 0; i < rItem.Count(); i++ )
//STRIP001          {
//STRIP001              const SvxTabStop& rTab = rItem[i];
//STRIP001              SvxTabStop aNewStop( OutputDevice::LogicToLogic( rTab.GetTabPos(), eSourceUnit, eDestUnit ), rTab.GetAdjustment(), rTab.GetDecimal(), rTab.GetFill() );
//STRIP001              aNewItem.Insert( aNewStop );
//STRIP001          }
//STRIP001          rItem = aNewItem;
/*N*/       }
/*N*/       break;
/*N*/       case EE_CHAR_FONTHEIGHT:
/*N*/       case EE_CHAR_FONTHEIGHT_CJK:
/*N*/       case EE_CHAR_FONTHEIGHT_CTL:
/*N*/       {DBG_BF_ASSERT(0, "STRIP");//STRIP001
//STRIP001          DBG_ASSERT( rPoolItem.IsA( TYPE( SvxFontHeightItem ) ), "ConvertItem: Ungueltiges Item!" );
//STRIP001          SvxFontHeightItem& rItem = (SvxFontHeightItem&)rPoolItem;
//STRIP001          rItem.SetHeight( OutputDevice::LogicToLogic( rItem.GetHeight(), eSourceUnit, eDestUnit ) );
/*N*/       }
/*N*/       break;
/*N*/   }
/*N*/ }

//STRIP001 void ConvertAndPutItems( SfxItemSet& rDest, const SfxItemSet& rSource, const MapUnit* pSourceUnit, const MapUnit* pDestUnit )
//STRIP001 {
//STRIP001  const SfxItemPool* pSourcePool = rSource.GetPool();
//STRIP001  const SfxItemPool* pDestPool = rDest.GetPool();
//STRIP001
//STRIP001  for ( USHORT nWhich = EE_PARA_START; nWhich <= EE_CHAR_END; nWhich++ )
//STRIP001  {
//STRIP001      // Wenn moeglich ueber SlotID gehen...
//STRIP001
//STRIP001      USHORT nSourceWhich = nWhich;
//STRIP001      USHORT nSlot = pDestPool->GetTrueSlotId( nWhich );
//STRIP001      if ( nSlot )
//STRIP001      {
//STRIP001          USHORT nW = pSourcePool->GetTrueWhich( nSlot );
//STRIP001          if ( nW )
//STRIP001              nSourceWhich = nW;
//STRIP001      }
//STRIP001
//STRIP001      if ( rSource.GetItemState( nSourceWhich, FALSE ) == SFX_ITEM_ON )
//STRIP001      {
//STRIP001          MapUnit eSourceUnit = pSourceUnit ? *pSourceUnit : (MapUnit)pSourcePool->GetMetric( nSourceWhich );
//STRIP001          MapUnit eDestUnit = pDestUnit ? *pDestUnit : (MapUnit)pDestPool->GetMetric( nWhich );
//STRIP001          if ( eSourceUnit != eDestUnit )
//STRIP001          {
//STRIP001              SfxPoolItem* pItem = rSource.Get( nSourceWhich ).Clone();
//STRIP001 //               pItem->SetWhich( nWhich );
//STRIP001              ConvertItem( *pItem, eSourceUnit, eDestUnit );
//STRIP001              rDest.Put( *pItem, nWhich );
//STRIP001              delete pItem;
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              rDest.Put( rSource.Get( nSourceWhich ), nWhich );
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          // MT 3.3.99: Waere so eigentlich richtig, aber schon seit Jahren nicht so...
//STRIP001 //           rDest.ClearItem( nWhich );
//STRIP001      }
//STRIP001  }
//STRIP001 }

}
