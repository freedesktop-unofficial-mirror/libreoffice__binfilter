/*************************************************************************
 *
 *  $RCSfile: sc_rangenam.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: aw $ $Date: 2004-02-27 18:54:41 $
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

#ifdef PCH
#include "core_pch.hxx"
#endif

#pragma hdrstop

//------------------------------------------------------------------------

#include <tools/debug.hxx>
#include <string.h>
#include <unotools/collatorwrapper.hxx>
#ifndef _UNOTOOLS_TRANSLITERATIONWRAPPER_HXX
#include <unotools/transliterationwrapper.hxx>
#endif

#include "rangenam.hxx"
#include "global.hxx"
#include "compiler.hxx"
#include "rangeutl.hxx"
#include "rechead.hxx"
#include "refupdat.hxx"
#include "document.hxx"
#include "indexmap.hxx"
namespace binfilter {


//========================================================================
// ScRangeData
//========================================================================

// Interner ctor fuer das Suchen nach einem Index

/*N*/ ScRangeData::ScRangeData( USHORT n )
/*N*/          : nIndex( n ), pCode( NULL ), bModified( FALSE )
/*N*/ {}

/*N*/ ScRangeData::ScRangeData( ScDocument* pDok,
/*N*/                         const String& rName,
/*N*/                         const String& rSymbol,
/*N*/                           const ScAddress& rAddress,
/*N*/                         RangeType nType,
/*N*/                         BOOL bEnglish ) :
/*N*/               aName       ( rName ),
/*N*/               aPos        ( rAddress ),
/*N*/               eType       ( nType ),
/*N*/               pDoc        ( pDok ),
/*N*/               nIndex      ( 0 ),
/*N*/               nExportIndex( 0 ),
/*N*/               pCode       ( NULL ),
/*N*/               bModified   ( FALSE )
/*N*/ {
/*N*/   if (rSymbol.Len() > 0)
/*N*/   {
/*N*/       ScCompiler aComp( pDoc, aPos );
/*N*/       aComp.SetCompileEnglish(bEnglish);
/*N*/       pCode = aComp.CompileString( rSymbol );
/*N*/       if( !pCode->GetError() )
/*N*/       {
/*N*/           pCode->Reset();
/*N*/           ScToken* p = pCode->GetNextReference();
/*N*/           if( p )// genau eine Referenz als erstes
/*N*/           {
/*N*/               if( p->GetType() == svSingleRef )
/*N*/                   eType = eType | RT_ABSPOS;
/*N*/               else
/*N*/                   eType = eType | RT_ABSAREA;
/*N*/           }
/*N*/           // ggf. den Fehlercode wg. unvollstaendiger Formel setzen!
/*N*/           // Dies ist fuer die manuelle Eingabe
/*N*/           aComp.CompileTokenArray();
/*N*/           pCode->DelRPN();
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ ScRangeData::ScRangeData( ScDocument* pDok,
/*N*/                         const String& rName,
/*N*/                         const ScTokenArray& rArr,
/*N*/                           const ScAddress& rAddress,
/*N*/                         RangeType nType ) :
/*N*/               aName       ( rName ),
/*N*/               aPos        ( rAddress ),
/*N*/               eType       ( nType ),
/*N*/               pDoc        ( pDok ),
/*N*/               nIndex      ( 0 ),
/*N*/               nExportIndex( 0 ),
/*N*/               pCode       ( new ScTokenArray( rArr ) ),
/*N*/               bModified   ( FALSE )
/*N*/ {
/*N*/   if( !pCode->GetError() )
/*N*/   {
/*N*/       pCode->Reset();
/*N*/       ScToken* p = pCode->GetNextReference();
/*N*/       if( p )// genau eine Referenz als erstes
/*N*/       {
/*N*/           if( p->GetType() == svSingleRef )
/*N*/               eType = eType | RT_ABSPOS;
/*N*/           else
/*N*/               eType = eType | RT_ABSAREA;
/*N*/       }
/*N*/       // Die Importfilter haben diesen Test nicht,
/*N*/       // da die benannten Bereiche z.T. noch unvollstaendig sind.
/*N*/ //        if( !pCode->GetCodeLen() )
/*N*/ //        {
/*N*/ //            // ggf. den Fehlercode wg. unvollstaendiger Formel setzen!
/*N*/ //            ScCompiler aComp( pDok, aPos, *pCode );
/*N*/ //            aComp.CompileTokenArray();
/*N*/ //            pCode->DelRPN();
/*N*/ //        }
/*N*/   }
/*N*/ }

/*?*/ ScRangeData::ScRangeData( ScDocument* pDok,
/*?*/                         const String& rName,
/*?*/                         const ScAddress& rTarget ) :
/*?*/               aName       ( rName ),
/*?*/               aPos        ( rTarget ),
/*?*/               eType       ( RT_NAME ),
/*?*/               pDoc        ( pDok ),
/*?*/               nIndex      ( 0 ),
/*?*/               nExportIndex( 0 ),
/*?*/               pCode       ( new ScTokenArray ),
/*?*/               bModified   ( FALSE )
/*?*/ {
/*?*/   SingleRefData aRefData;
/*?*/   aRefData.InitAddress( rTarget );
/*?*/   aRefData.SetFlag3D( TRUE );
/*?*/   pCode->AddSingleReference( aRefData );
/*?*/   ScCompiler aComp( pDoc, aPos, *pCode );
/*?*/   aComp.CompileTokenArray();
/*?*/   if ( !pCode->GetError() )
/*?*/       eType |= RT_ABSPOS;
/*?*/ }

/*N*/ ScRangeData::ScRangeData(const ScRangeData& rScRangeData) :
/*N*/   aName   (rScRangeData.aName),
/*N*/   aPos        (rScRangeData.aPos),
/*N*/   eType       (rScRangeData.eType),
/*N*/   pDoc        (rScRangeData.pDoc),
/*N*/   nIndex      (rScRangeData.nIndex),
/*N*/   pCode       (rScRangeData.pCode ? rScRangeData.pCode->Clone() : new ScTokenArray),      // echte Kopie erzeugen (nicht copy-ctor)
/*N*/   bModified   (rScRangeData.bModified)
/*N*/ {}

/*N*/ ScRangeData::~ScRangeData()
/*N*/ {
/*N*/   delete pCode;
/*N*/ }

/*N*/ DataObject* ScRangeData::Clone() const
/*N*/ {
/*N*/   return new ScRangeData(*this);
/*N*/ }

/*N*/ ScRangeData::ScRangeData
/*N*/   ( SvStream& rStream, ScMultipleReadHeader& rHdr, USHORT nVer )
/*N*/          : pCode      ( new ScTokenArray ),
/*N*/            bModified  (FALSE)
/*N*/
/*N*/ {
/*N*/   rHdr.StartEntry();
/*N*/
/*N*/   if( nVer >= SC_NEW_TOKEN_ARRAYS )
/*N*/   {
/*N*/       UINT32 nPos;
/*N*/       BYTE nData;
/*N*/       rStream.ReadByteString( aName, rStream.GetStreamCharSet() );
/*N*/       rStream >> nPos >> eType >> nIndex >> nData;
/*N*/       if( nData & 0x0F )
/*?*/           rStream.SeekRel( nData & 0x0F );
/*N*/       aPos = ScAddress( nPos );
/*N*/       pCode->Load( rStream, nVer, aPos );
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       UINT16 nTokLen, r, c, t;
/*N*/       rStream.ReadByteString( aName, rStream.GetStreamCharSet() );
/*N*/       rStream >> c >> r >> t >> eType >> nIndex >> nTokLen;
/*N*/       aPos.Set( c, r, t );
/*N*/       if( nTokLen )
/*N*/           pCode->Load30( rStream, aPos );
/*N*/   }
/*N*/
/*N*/   rHdr.EndEntry();
/*N*/ }

/*N*/ BOOL ScRangeData::Store
/*N*/   ( SvStream& rStream, ScMultipleWriteHeader& rHdr ) const
/*N*/ {
/*N*/   rHdr.StartEntry();
/*N*/
/*N*/   rStream.WriteByteString( aName, rStream.GetStreamCharSet() );
/*N*/   rStream << (UINT32) aPos << eType << nIndex << (BYTE) 0x00;
/*N*/   pCode->Store( rStream, aPos );
/*N*/
/*N*/   rHdr.EndEntry();
/*N*/   return TRUE;
/*N*/ }

/*N*/ BOOL ScRangeData::IsBeyond( USHORT nMaxRow ) const
/*N*/ {
/*N*/   if ( aPos.Row() > nMaxRow )
/*N*/       return TRUE;
/*N*/
/*N*/   ScToken* t;
/*N*/   pCode->Reset();
/*N*/   while ( t = pCode->GetNextReference() )
/*N*/       if ( t->GetSingleRef().nRow > nMaxRow ||
/*N*/               (t->GetType() == svDoubleRef &&
/*N*/               t->GetDoubleRef().Ref2.nRow > nMaxRow) )
/*N*/           return TRUE;
/*N*/
/*N*/   return FALSE;
/*N*/ }

//STRIP001 void ScRangeData::GuessPosition()
//STRIP001 {
//STRIP001  //  setzt eine Position, mit der alle relative Referenzen bei CalcAbsIfRel
//STRIP001  //  ohne Fehler verabsolutiert werden koennen
//STRIP001
//STRIP001  DBG_ASSERT(aPos == ScAddress(), "die Position geht jetzt verloren");
//STRIP001
//STRIP001  INT16 nMinCol = 0;
//STRIP001  INT16 nMinRow = 0;
//STRIP001  INT16 nMinTab = 0;
//STRIP001
//STRIP001  ScToken* t;
//STRIP001  pCode->Reset();
//STRIP001  while ( t = pCode->GetNextReference() )
//STRIP001  {
//STRIP001      SingleRefData& rRef1 = t->GetSingleRef();
//STRIP001      if ( rRef1.IsColRel() && rRef1.nRelCol < nMinCol )
//STRIP001          nMinCol = rRef1.nRelCol;
//STRIP001      if ( rRef1.IsRowRel() && rRef1.nRelRow < nMinRow )
//STRIP001          nMinRow = rRef1.nRelRow;
//STRIP001      if ( rRef1.IsTabRel() && rRef1.nRelTab < nMinTab )
//STRIP001          nMinTab = rRef1.nRelTab;
//STRIP001
//STRIP001      if ( t->GetType() == svDoubleRef )
//STRIP001      {
//STRIP001          SingleRefData& rRef2 = t->GetDoubleRef().Ref2;
//STRIP001          if ( rRef2.IsColRel() && rRef2.nRelCol < nMinCol )
//STRIP001              nMinCol = rRef2.nRelCol;
//STRIP001          if ( rRef2.IsRowRel() && rRef2.nRelRow < nMinRow )
//STRIP001              nMinRow = rRef2.nRelRow;
//STRIP001          if ( rRef2.IsTabRel() && rRef2.nRelTab < nMinTab )
//STRIP001              nMinTab = rRef2.nRelTab;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  aPos = ScAddress( (USHORT)(-nMinCol), (USHORT)(-nMinRow), (USHORT)(-nMinTab) );
//STRIP001
//STRIP001  //! Test
//STRIP001 //   DBG_ERROR(String("Pos ")+String((USHORT)(-nMinCol))+String("/")+
//STRIP001 //           String((USHORT)(-nMinRow))+String("/")+String((USHORT)(-nMinTab)));
//STRIP001 }

/*N*/ void ScRangeData::GetSymbol   (String& rSymbol) const
/*N*/ {
/*N*/   ScCompiler aScComp(pDoc, aPos, *pCode);
/*N*/   aScComp.CreateStringFromTokenArray( rSymbol );
/*N*/ }

/*N*/ void ScRangeData::GetEnglishSymbol    (String& rSymbol, BOOL bCompileXML) const
/*N*/ {
/*N*/   ScCompiler aScComp(pDoc, aPos, *pCode);
/*N*/   aScComp.SetCompileEnglish( TRUE );
/*N*/   aScComp.SetCompileXML( bCompileXML );
/*N*/   aScComp.CreateStringFromTokenArray( rSymbol );
/*N*/ }

/*N*/ void ScRangeData::UpdateSymbol(   String& rSymbol, const ScAddress& rPos,
/*N*/                               BOOL bEnglish, BOOL bCompileXML )
/*N*/ {
/*N*/   ScTokenArray* pTemp = pCode->Clone();
/*N*/   ScCompiler aComp( pDoc, rPos, *pTemp );
/*N*/   aComp.SetCompileEnglish( bEnglish );
/*N*/   aComp.SetCompileXML( bCompileXML );
/*N*/   aComp.MoveRelWrap();
/*N*/   aComp.CreateStringFromTokenArray( rSymbol );
/*N*/   delete pTemp;
/*N*/ }

/*N*/ void ScRangeData::UpdateSymbol(   ::rtl::OUStringBuffer& rBuffer, const ScAddress& rPos,
/*N*/                               BOOL bEnglish, BOOL bCompileXML )
/*N*/ {
/*N*/   ScTokenArray* pTemp = pCode->Clone();
/*N*/   ScCompiler aComp( pDoc, rPos, *pTemp );
/*N*/   aComp.SetCompileEnglish( bEnglish );
/*N*/   aComp.SetCompileXML( bCompileXML );
/*N*/   aComp.MoveRelWrap();
/*N*/   aComp.CreateStringFromTokenArray( rBuffer );
/*N*/   delete pTemp;
/*N*/ }

/*N*/ void ScRangeData::UpdateReference(    UpdateRefMode eUpdateRefMode,
/*N*/                                   const ScRange& r,
/*N*/                                   short nDx, short nDy, short nDz )
/*N*/ {
/*N*/   BOOL bChanged = FALSE;
/*N*/
/*N*/   pCode->Reset();
/*N*/   if( pCode->GetNextReference() )
/*N*/   {
/*N*/       ScCompiler aComp( pDoc, aPos, *pCode );
/*N*/       BOOL bRelRef = aComp.UpdateNameReference( eUpdateRefMode, r,
/*N*/                                                   nDx, nDy, nDz,
/*N*/                                                   bChanged);
/*N*/       if (eType&RT_SHARED)
/*N*/       {
/*N*/           if (bRelRef)
/*N*/               eType = eType | RT_SHAREDMOD;
/*N*/           else
/*N*/               eType = eType & ~RT_SHAREDMOD;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   bModified = bChanged;
/*N*/ }


//STRIP001 void ScRangeData::UpdateTranspose( const ScRange& rSource, const ScAddress& rDest )
//STRIP001 {
//STRIP001  BOOL bChanged = FALSE;
//STRIP001
//STRIP001  ScToken* t;
//STRIP001  pCode->Reset();
//STRIP001
//STRIP001  for( t = pCode->GetNextReference(); t; t = pCode->GetNextReference() )
//STRIP001  {
//STRIP001      if( t->GetType() != svIndex )
//STRIP001      {
//STRIP001          SingleDoubleRefModifier aMod( *t );
//STRIP001          ComplRefData& rRef = aMod.Ref();
//STRIP001          if (!rRef.Ref1.IsColRel() && !rRef.Ref1.IsRowRel() &&
//STRIP001                  (!rRef.Ref1.IsFlag3D() || !rRef.Ref1.IsTabRel()) &&
//STRIP001              ( t->GetType() == svSingleRef ||
//STRIP001              (!rRef.Ref2.IsColRel() && !rRef.Ref2.IsRowRel() &&
//STRIP001                  (!rRef.Ref2.IsFlag3D() || !rRef.Ref2.IsTabRel()))))
//STRIP001          {
//STRIP001              if ( ScRefUpdate::UpdateTranspose( pDoc, rSource, rDest, rRef ) != UR_NOTHING )
//STRIP001                  bChanged = TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  bModified = bChanged;
//STRIP001 }

//STRIP001 void ScRangeData::UpdateGrow( const ScRange& rArea, USHORT nGrowX, USHORT nGrowY )
//STRIP001 {
//STRIP001  BOOL bChanged = FALSE;
//STRIP001
//STRIP001  ScToken* t;
//STRIP001  pCode->Reset();
//STRIP001
//STRIP001  for( t = pCode->GetNextReference(); t; t = pCode->GetNextReference() )
//STRIP001  {
//STRIP001      if( t->GetType() != svIndex )
//STRIP001      {
//STRIP001          SingleDoubleRefModifier aMod( *t );
//STRIP001          ComplRefData& rRef = aMod.Ref();
//STRIP001          if (!rRef.Ref1.IsColRel() && !rRef.Ref1.IsRowRel() &&
//STRIP001                  (!rRef.Ref1.IsFlag3D() || !rRef.Ref1.IsTabRel()) &&
//STRIP001              ( t->GetType() == svSingleRef ||
//STRIP001              (!rRef.Ref2.IsColRel() && !rRef.Ref2.IsRowRel() &&
//STRIP001                  (!rRef.Ref2.IsFlag3D() || !rRef.Ref2.IsTabRel()))))
//STRIP001          {
//STRIP001              if ( ScRefUpdate::UpdateGrow( rArea,nGrowX,nGrowY, rRef ) != UR_NOTHING )
//STRIP001                  bChanged = TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  bModified = bChanged;           // muss direkt hinterher ausgewertet werden
//STRIP001 }

//STRIP001 BOOL ScRangeData::operator== (const ScRangeData& rData) const        // fuer Undo
//STRIP001 {
//STRIP001  if ( nIndex != rData.nIndex ||
//STRIP001       aName  != rData.aName  ||
//STRIP001       aPos   != rData.aPos   ||
//STRIP001       eType  != rData.eType     ) return FALSE;
//STRIP001
//STRIP001  USHORT nLen = pCode->GetLen();
//STRIP001  if ( nLen != rData.pCode->GetLen() ) return FALSE;
//STRIP001
//STRIP001  ScToken** ppThis = pCode->GetArray();
//STRIP001  ScToken** ppOther = rData.pCode->GetArray();
//STRIP001
//STRIP001  for ( USHORT i=0; i<nLen; i++ )
//STRIP001      if ( ppThis[i] != ppOther[i] && !(*ppThis[i] == *ppOther[i]) )
//STRIP001          return FALSE;
//STRIP001
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 BOOL ScRangeData::IsRangeAtCursor( const ScAddress& rPos, BOOL bStartOnly ) const
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001  ScRange aRange;
//STRIP001  if ( IsReference(aRange) )
//STRIP001  {
//STRIP001      if ( bStartOnly )
//STRIP001          bRet = ( rPos == aRange.aStart );
//STRIP001      else
//STRIP001          bRet = ( aRange.In( rPos ) );
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 BOOL ScRangeData::IsRangeAtBlock( const ScRange& rBlock ) const
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001  ScRange aRange;
//STRIP001  if ( IsReference(aRange) )
//STRIP001      bRet = ( rBlock == aRange );
//STRIP001  return bRet;
//STRIP001 }

/*N*/ BOOL ScRangeData::IsReference( ScRange& rRange ) const
/*N*/ {
/*N*/   BOOL bIs = FALSE;
/*N*/   if ( eType & ( RT_ABSAREA | RT_REFAREA | RT_ABSPOS ) )
/*N*/       if ( pCode )
/*N*/           return pCode->IsReference( rRange );
/*N*/
/*N*/   return bIs;
/*N*/ }

//STRIP001 void ScRangeData::UpdateTabRef(USHORT nOldTable, USHORT nFlag, USHORT nNewTable)
//STRIP001 {
//STRIP001  pCode->Reset();
//STRIP001  if( pCode->GetNextReference() )
//STRIP001  {
//STRIP001      ScRangeData* pRangeData;        // darf nicht dereferenziert werden!!
//STRIP001      BOOL bChanged;
//STRIP001      ScCompiler aComp( pDoc, aPos, *pCode );
//STRIP001      switch (nFlag)
//STRIP001      {
//STRIP001          case 1:                                     // einfache InsertTab (doc.cxx)
//STRIP001              pRangeData = aComp.UpdateInsertTab(nOldTable, TRUE );   // und CopyTab (doc2.cxx)
//STRIP001              break;
//STRIP001          case 2:                                     // einfaches delete (doc.cxx)
//STRIP001              pRangeData = aComp.UpdateDeleteTab(nOldTable, FALSE, TRUE, bChanged);
//STRIP001              break;
//STRIP001          case 3:                                     // move (doc2.cxx)
//STRIP001          {
//STRIP001              pRangeData = aComp.UpdateMoveTab(nOldTable, nNewTable, TRUE );
//STRIP001          }
//STRIP001              break;
//STRIP001          default:
//STRIP001          {
//STRIP001              DBG_ERROR("ScRangeName::UpdateTabRef: Unknown Flag");
//STRIP001          }
//STRIP001              break;
//STRIP001      }
//STRIP001      if (eType&RT_SHARED)
//STRIP001      {
//STRIP001          if (pRangeData)
//STRIP001              eType = eType | RT_SHAREDMOD;
//STRIP001          else
//STRIP001              eType = eType & ~RT_SHAREDMOD;
//STRIP001      }
//STRIP001  }
//STRIP001 }

//  wie beim Uebernehmen von Namen in Excel

/*N*/ void ScRangeData::MakeValidName( String& rName )      // static
/*N*/ {
/*N*/   if (!ScCompiler::HasCharTable())
/*N*/       ScCompiler::Init();
/*N*/
/*N*/   //  ungueltige Zeichen vorne weglassen
/*N*/   xub_StrLen nPos = 0;
/*N*/   xub_StrLen nLen = rName.Len();
/*N*/   while ( nPos < nLen && !ScCompiler::IsWordChar( rName.GetChar(nPos) ) )
/*N*/       ++nPos;
/*N*/   if ( nPos>0 )
/*N*/       rName.Erase(0,nPos);
/*N*/
/*N*/   //  wenn vorne ein ungueltiges Anfangszeichen steht, '_' davor
/*N*/   if ( rName.Len() && !ScCompiler::IsCharWordChar( rName.GetChar(0) ) )
/*N*/       rName.Insert('_',0);
/*N*/
/*N*/   //  ungueltige durch '_' ersetzen
/*N*/   nLen = rName.Len();
/*N*/   for (nPos=0; nPos<nLen; nPos++)
/*N*/   {
/*N*/       if ( !ScCompiler::IsWordChar( rName.GetChar(nPos) ) )
/*N*/           rName.SetChar( nPos, '_' );
/*N*/   }
/*N*/
/*N*/   // Name darf keine Referenz beinhalten, wie in IsNameValid
/*N*/   BOOL bOk;
/*N*/   do
/*N*/   {
/*N*/       bOk = TRUE;
/*N*/       ScRange aRange;
/*N*/       if( aRange.Parse( rName, NULL ) )
/*N*/           bOk = FALSE;
/*N*/       else
/*N*/       {
/*N*/           ScAddress aAddr;
/*N*/           if ( aAddr.Parse( rName, NULL ) )
/*N*/               bOk = FALSE;
/*N*/       }
/*N*/       if ( !bOk )
/*N*/       {   //! Range Parse auch bei Bereich mit ungueltigem Tabellennamen gueltig
/*N*/           //! Address Parse dito, Name erzeugt deswegen bei Compile ein #REF!
/*N*/           if ( rName.SearchAndReplace( ':', '_' ) == STRING_NOTFOUND
/*N*/             && rName.SearchAndReplace( '.', '_' ) == STRING_NOTFOUND )
/*N*/               rName.Insert('_',0);
/*N*/       }
/*N*/   } while ( !bOk );
/*N*/ }

//STRIP001 BOOL ScRangeData::IsNameValid( const String& rName, ScDocument* pDoc )
//STRIP001 {
//STRIP001     /*  If changed, ScfTools::ConvertToScDefinedName (sc/source/filter/ftools/ftools.cxx)
//STRIP001         needs to be changed too. */
//STRIP001  xub_StrLen nPos = 0;
//STRIP001  xub_StrLen nLen = rName.Len();
//STRIP001  if ( !nLen || !ScCompiler::IsCharWordChar( rName.GetChar(nPos++) ) )
//STRIP001      return FALSE;
//STRIP001  while ( nPos < nLen )
//STRIP001  {
//STRIP001      if ( !ScCompiler::IsWordChar( rName.GetChar(nPos++) ) )
//STRIP001          return FALSE;
//STRIP001  }
//STRIP001  // Parse nicht auf VALID pruefen, es reicht, wenn irgendein Bestandteil
//STRIP001  // erkannt wurde
//STRIP001  ScRange aRange;
//STRIP001  if( aRange.Parse( rName, pDoc ) )
//STRIP001      return FALSE;
//STRIP001  else
//STRIP001  {
//STRIP001      ScAddress aAddr;
//STRIP001      if ( aAddr.Parse( rName, pDoc ) )
//STRIP001          return FALSE;
//STRIP001  }
//STRIP001  return TRUE;
//STRIP001 }


/*N*/ USHORT ScRangeData::GetErrCode()
/*N*/ {
/*N*/   return pCode ? pCode->GetError() : 0;
/*N*/ }

/*N*/ BOOL ScRangeData::HasReferences() const
/*N*/ {
/*N*/   pCode->Reset();
/*N*/   return BOOL( pCode->GetNextReference() != NULL );
/*N*/ }

// bei TransferTab von einem in ein anderes Dokument anpassen,
// um Referenzen auf die eigene Tabelle mitzubekommen

//STRIP001 void ScRangeData::TransferTabRef( USHORT nOldTab, USHORT nNewTab )
//STRIP001 {
//STRIP001  short nTabDiff = nNewTab - nOldTab;
//STRIP001  short nPosDiff = nNewTab - aPos.Tab();
//STRIP001  aPos.SetTab( nNewTab );
//STRIP001  ScToken* t;
//STRIP001  pCode->Reset();
//STRIP001  while ( t = pCode->GetNextReference() )
//STRIP001  {
//STRIP001      SingleRefData& rRef1 = t->GetSingleRef();
//STRIP001      if ( rRef1.IsTabRel() )
//STRIP001          rRef1.nTab += nPosDiff;
//STRIP001      else
//STRIP001          rRef1.nTab += nTabDiff;
//STRIP001      if ( t->GetType() == svDoubleRef )
//STRIP001      {
//STRIP001          SingleRefData& rRef2 = t->GetDoubleRef().Ref2;
//STRIP001          if ( rRef2.IsTabRel() )
//STRIP001              rRef2.nTab += nPosDiff;
//STRIP001          else
//STRIP001              rRef2.nTab += nTabDiff;
//STRIP001      }
//STRIP001  }
//STRIP001 }


/*N*/ void ScRangeData::ReplaceRangeNamesInUse( const ScIndexMap& rMap )
/*N*/ {
/*N*/   BOOL bCompile = FALSE;
/*N*/   for ( ScToken* p = pCode->First(); p; p = pCode->Next() )
/*N*/   {
/*N*/       if ( p->GetOpCode() == ocName )
/*N*/       {
/*?*/           DBG_ASSERT(0, "STRIP"); //STRIP001 USHORT nIndex = p->GetIndex();
//STRIP001 /*?*/            USHORT nNewIndex = rMap.Find( nIndex );
//STRIP001 /*?*/            if ( nIndex != nNewIndex )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                p->SetIndex( nNewIndex );
//STRIP001 /*?*/                bCompile = TRUE;
//STRIP001 /*?*/            }
/*N*/       }
/*N*/   }
/*N*/   if ( bCompile )
/*N*/   {
/*N*/       ScCompiler aComp( pDoc, aPos, *pCode );
/*N*/       aComp.CompileTokenArray();
/*N*/   }
/*N*/ }


/*N*/ void ScRangeData::ValidateTabRefs()
/*N*/ {
/*N*/   //  try to make sure all relative references and the reference position
/*N*/   //  are within existing tables, so they can be represented as text
/*N*/   //  (if the range of used tables is more than the existing tables,
/*N*/   //  the result may still contain invalid tables, because the relative
/*N*/   //  references aren't changed so formulas stay the same)
/*N*/
/*N*/   //  find range of used tables
/*N*/
/*N*/   USHORT nMinTab = aPos.Tab();
/*N*/   USHORT nMaxTab = nMinTab;
/*N*/   ScToken* t;
/*N*/   pCode->Reset();
/*N*/   while ( t = pCode->GetNextReference() )
/*N*/   {
/*N*/       SingleRefData& rRef1 = t->GetSingleRef();
/*N*/       if ( rRef1.IsTabRel() && !rRef1.IsTabDeleted() )
/*N*/       {
/*N*/           if ( rRef1.nTab < nMinTab )
/*N*/               nMinTab = rRef1.nTab;
/*N*/           if ( rRef1.nTab > nMaxTab )
/*N*/               nMaxTab = rRef1.nTab;
/*N*/       }
/*N*/       if ( t->GetType() == svDoubleRef )
/*N*/       {
/*N*/           SingleRefData& rRef2 = t->GetDoubleRef().Ref2;
/*N*/           if ( rRef2.IsTabRel() && !rRef2.IsTabDeleted() )
/*N*/           {
/*?*/               if ( rRef2.nTab < nMinTab )
/*?*/                   nMinTab = rRef2.nTab;
/*?*/               if ( rRef2.nTab > nMaxTab )
/*?*/                   nMaxTab = rRef2.nTab;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   USHORT nTabCount = pDoc->GetTableCount();
/*N*/   if ( nMaxTab >= nTabCount && nMinTab > 0 )
/*N*/   {
/*?*/       //  move position and relative tab refs
/*?*/       //  The formulas that use the name are not changed by this
/*?*/
/*?*/       USHORT nMove = nMinTab;
/*?*/       aPos.SetTab( aPos.Tab() - nMove );
/*?*/
/*?*/       pCode->Reset();
/*?*/       while ( t = pCode->GetNextReference() )
/*?*/       {
/*?*/           SingleRefData& rRef1 = t->GetSingleRef();
/*?*/           if ( rRef1.IsTabRel() && !rRef1.IsTabDeleted() )
/*?*/               rRef1.nTab -= nMove;
/*?*/           if ( t->GetType() == svDoubleRef )
/*?*/           {
/*?*/               SingleRefData& rRef2 = t->GetDoubleRef().Ref2;
/*?*/               if ( rRef2.IsTabRel() && !rRef2.IsTabDeleted() )
/*?*/                   rRef2.nTab -= nMove;
/*?*/           }
/*?*/       }
/*N*/   }
/*N*/ }


/*N*/ int
/*N*/ #ifdef WNT
/*N*/ __cdecl
/*N*/ #endif
/*N*/ ScRangeData::QsortNameCompare( const void* p1, const void* p2 )
/*N*/ {
/*N*/   return (int) ScGlobal::pCollator->compareString(
/*N*/           (*(const ScRangeData**)p1)->aName,
/*N*/           (*(const ScRangeData**)p2)->aName );
/*N*/ }


//========================================================================
// ScRangeName
//========================================================================

/*N*/ ScRangeName::ScRangeName(const ScRangeName& rScRangeName, ScDocument* pDocument) :
/*N*/               SortedCollection ( rScRangeName ),
/*N*/               pDoc ( pDocument ),
/*N*/               nSharedMaxIndex (rScRangeName.nSharedMaxIndex)
/*N*/ {
/*N*/   for (USHORT i = 0; i < nCount; i++)
/*N*/   {
/*N*/       ((ScRangeData*)At(i))->SetDocument(pDocument);
/*N*/       ((ScRangeData*)At(i))->SetIndex(((ScRangeData*)rScRangeName.At(i))->GetIndex());
/*N*/   }
/*N*/ }

/*N*/ short ScRangeName::Compare(DataObject* pKey1, DataObject* pKey2) const
/*N*/ {
/*N*/   USHORT i1 = ((ScRangeData*)pKey1)->GetIndex();
/*N*/   USHORT i2 = ((ScRangeData*)pKey2)->GetIndex();
/*N*/   return (short) i1 - (short) i2;
/*N*/ }

/*N*/ BOOL ScRangeName::SearchName( const String& rName, USHORT& rIndex ) const
/*N*/ {
/*N*/   USHORT i = 0;
/*N*/   while (i < nCount)
/*N*/   {
/*N*/       String aName;
/*N*/       ((*this)[i])->GetName( aName );
/*N*/         if ( ScGlobal::pTransliteration->isEqual( aName, rName ) )
/*N*/       {
/*N*/           rIndex = i;
/*N*/           return TRUE;
/*N*/       }
/*N*/       i++;
/*N*/   }
/*N*/   return FALSE;
/*N*/ }

/*N*/ BOOL ScRangeName::Load( SvStream& rStream, USHORT nVer )
/*N*/ {
/*N*/   BOOL bSuccess = TRUE;
/*N*/   USHORT nNewCount;
/*N*/
/*N*/   while( nCount > 0 )
/*?*/       AtFree(0);                  // alles loeschen
/*N*/
/*N*/   ScMultipleReadHeader aHdr( rStream );
/*N*/
/*N*/   USHORT nDummy;
/*N*/   if( nVer >= SC_NEW_TOKEN_ARRAYS )
/*N*/       rStream >> nSharedMaxIndex >> nNewCount;
/*N*/   else
/*N*/       rStream >> nSharedMaxIndex >> nDummy >> nNewCount;
/*N*/   for (USHORT i=0; i<nNewCount && bSuccess; i++)
/*N*/   {
/*N*/       ScRangeData* pData = new ScRangeData( rStream, aHdr, nVer );
/*N*/       pData->SetDocument(pDoc);
/*N*/       Insert( pData );
/*N*/       if( rStream.GetError() != SVSTREAM_OK )
/*N*/           bSuccess = FALSE;
/*N*/   }
/*N*/   return bSuccess;
/*N*/ }

/*N*/ BOOL ScRangeName::Store( SvStream& rStream ) const
/*N*/ {
/*N*/   ScMultipleWriteHeader aHdr( rStream );
/*N*/
/*N*/   USHORT i;
/*N*/   USHORT nSaveCount = nCount;
/*N*/   USHORT nSaveMaxRow = pDoc->GetSrcMaxRow();
/*N*/   if ( nSaveMaxRow < MAXROW )
/*N*/   {
/*N*/       nSaveCount = 0;
/*N*/       for (i=0; i<nCount; i++)
/*N*/       if ( !((const ScRangeData*)At(i))->IsBeyond(nSaveMaxRow) )
/*N*/               ++nSaveCount;
/*N*/
/*N*/       if ( nSaveCount < nCount )
/*?*/           pDoc->SetLostData();            // Warnung ausgeben
/*N*/   }
/*N*/
/*N*/   rStream << nSharedMaxIndex << nSaveCount;
/*N*/   BOOL bSuccess = TRUE;
/*N*/
/*N*/   for (i=0; i<nCount && bSuccess; i++)
/*N*/   {
/*N*/       const ScRangeData* pRangeData = (const ScRangeData*)At(i);
/*N*/       if ( nSaveMaxRow == MAXROW || !pRangeData->IsBeyond(nSaveMaxRow) )
/*N*/           bSuccess = pRangeData->Store( rStream, aHdr );
/*N*/   }
/*N*/
/*N*/   return bSuccess;
/*N*/ }

/*N*/ void ScRangeName::UpdateReference(    UpdateRefMode eUpdateRefMode,
/*N*/                                   const ScRange& rRange,
/*N*/                                   short nDx, short nDy, short nDz )
/*N*/ {
/*N*/   for (USHORT i=0; i<nCount; i++)
/*N*/       ((ScRangeData*)pItems[i])->UpdateReference(eUpdateRefMode, rRange,
/*N*/                                                  nDx, nDy, nDz);
/*N*/ }

//STRIP001 void ScRangeName::UpdateTranspose( const ScRange& rSource, const ScAddress& rDest )
//STRIP001 {
//STRIP001  for (USHORT i=0; i<nCount; i++)
//STRIP001      ((ScRangeData*)pItems[i])->UpdateTranspose( rSource, rDest );
//STRIP001 }

//STRIP001 void ScRangeName::UpdateGrow( const ScRange& rArea, USHORT nGrowX, USHORT nGrowY )
//STRIP001 {
//STRIP001  for (USHORT i=0; i<nCount; i++)
//STRIP001      ((ScRangeData*)pItems[i])->UpdateGrow( rArea, nGrowX, nGrowY );
//STRIP001 }

//STRIP001 BOOL ScRangeName::IsEqual(DataObject* pKey1, DataObject* pKey2) const
//STRIP001 {
//STRIP001  return *(ScRangeData*)pKey1 == *(ScRangeData*)pKey2;
//STRIP001 }

/*N*/ BOOL ScRangeName::Insert(DataObject* pDataObject)
/*N*/ {
/*N*/   if (!((ScRangeData*)pDataObject)->GetIndex())       // schon gesetzt?
/*N*/   {
/*N*/       ((ScRangeData*)pDataObject)->SetIndex( GetEntryIndex() );
/*N*/   }
/*N*/
/*N*/   return SortedCollection::Insert(pDataObject);
/*N*/ }

// Suche nach einem freien Index

/*N*/ USHORT ScRangeName::GetEntryIndex()
/*N*/ {
/*N*/   USHORT nLast = 0;
/*N*/   for ( USHORT i = 0; i < nCount; i++ )
/*N*/   {
/*N*/       USHORT nIdx = ((ScRangeData*)pItems[i])->GetIndex();
/*N*/       if( nIdx > nLast )
/*N*/       {
/*N*/           nLast = nIdx;
/*N*/       }
/*N*/   }
/*N*/   return nLast + 1;
/*N*/ }

/*N*/ ScRangeData* ScRangeName::FindIndex( USHORT nIndex )
/*N*/ {
/*N*/   ScRangeData aDataObj( nIndex );
/*N*/   USHORT n;
/*N*/   if( Search( &aDataObj, n ) )
/*N*/       return (*this)[ n ];
/*N*/   else
/*N*/       return NULL;
/*N*/ }

//STRIP001 ScRangeData* ScRangeName::GetRangeAtCursor( const ScAddress& rPos, BOOL bStartOnly ) const
//STRIP001 {
//STRIP001  if ( pItems )
//STRIP001  {
//STRIP001      for ( USHORT i = 0; i < nCount; i++ )
//STRIP001          if ( ((ScRangeData*)pItems[i])->IsRangeAtCursor( rPos, bStartOnly ) )
//STRIP001              return (ScRangeData*)pItems[i];
//STRIP001  }
//STRIP001  return NULL;
//STRIP001 }

//STRIP001 ScRangeData* ScRangeName::GetRangeAtBlock( const ScRange& rBlock ) const
//STRIP001 {
//STRIP001  if ( pItems )
//STRIP001  {
//STRIP001      for ( USHORT i = 0; i < nCount; i++ )
//STRIP001          if ( ((ScRangeData*)pItems[i])->IsRangeAtBlock( rBlock ) )
//STRIP001              return (ScRangeData*)pItems[i];
//STRIP001  }
//STRIP001  return NULL;
//STRIP001 }

/*N*/ void ScRangeName::UpdateTabRef(USHORT nOldTable, USHORT nFlag, USHORT nNewTable)
/*N*/ {
/*N*/   for (USHORT i=0; i<nCount; i++)
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001 ((ScRangeData*)pItems[i])->UpdateTabRef(nOldTable, nFlag, nNewTable);
/*N*/ }




}
