/*************************************************************************
 *
 *  $RCSfile: sc_asciiopt.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:18:18 $
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
#include "ui_pch.hxx"
#endif

#pragma hdrstop

#include "global.hxx"
#include "scresid.hxx"
#include "impex.hxx"
#include "asciiopt.hxx"
#include "asciiopt.hrc"

#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif
#ifndef _RTL_TENCINFO_H
#include <rtl/tencinfo.h>
#endif
#ifndef _UNOTOOLS_TRANSLITERATIONWRAPPER_HXX
#include <unotools/transliterationwrapper.hxx>
#endif


// ============================================================================

//! TODO make dynamic
#ifdef WIN
const sal_Int32 ASCIIDLG_MAXROWS                = 10000;
#else
const sal_Int32 ASCIIDLG_MAXROWS                = 32000;
#endif

static const sal_Char __FAR_DATA pStrFix[] = "FIX";
static const sal_Char __FAR_DATA pStrMrg[] = "MRG";


// ============================================================================

/*N*/ ScAsciiOptions::ScAsciiOptions() :
/*N*/   bFixedLen       ( FALSE ),
/*N*/   aFieldSeps      ( ';' ),
/*N*/   bMergeFieldSeps ( FALSE ),
/*N*/   cTextSep        ( 34 ),
/*N*/   eCharSet        ( gsl_getSystemTextEncoding() ),
/*N*/   bCharSetSystem  ( FALSE ),
/*N*/   nStartRow       ( 1 ),
/*N*/   nInfoCount      ( 0 ),
/*N*/     pColStart       ( NULL ),
/*N*/   pColFormat      ( NULL )
/*N*/ {
/*N*/ }


/*N*/ ScAsciiOptions::ScAsciiOptions(const ScAsciiOptions& rOpt) :
/*N*/   bFixedLen       ( rOpt.bFixedLen ),
/*N*/   aFieldSeps      ( rOpt.aFieldSeps ),
/*N*/   bMergeFieldSeps ( rOpt.bMergeFieldSeps ),
/*N*/   cTextSep        ( rOpt.cTextSep ),
/*N*/   eCharSet        ( rOpt.eCharSet ),
/*N*/   bCharSetSystem  ( rOpt.bCharSetSystem ),
/*N*/   nStartRow       ( rOpt.nStartRow ),
/*N*/   nInfoCount      ( rOpt.nInfoCount )
/*N*/ {
/*N*/   if (nInfoCount)
/*N*/   {
/*N*/       pColStart = new xub_StrLen[nInfoCount];
/*N*/       pColFormat = new BYTE[nInfoCount];
/*N*/       for (USHORT i=0; i<nInfoCount; i++)
/*N*/       {
/*N*/           pColStart[i] = rOpt.pColStart[i];
/*N*/           pColFormat[i] = rOpt.pColFormat[i];
/*N*/       }
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       pColStart = NULL;
/*N*/       pColFormat = NULL;
/*N*/   }
/*N*/ }


/*N*/ ScAsciiOptions::~ScAsciiOptions()
/*N*/ {
/*N*/   delete[] pColStart;
/*N*/   delete[] pColFormat;
/*N*/ }


//STRIP001 void ScAsciiOptions::SetColInfo( USHORT nCount, const xub_StrLen* pStart, const BYTE* pFormat )
//STRIP001 {
//STRIP001  delete[] pColStart;
//STRIP001  delete[] pColFormat;
//STRIP001
//STRIP001  nInfoCount = nCount;
//STRIP001
//STRIP001  if (nInfoCount)
//STRIP001  {
//STRIP001      pColStart = new xub_StrLen[nInfoCount];
//STRIP001      pColFormat = new BYTE[nInfoCount];
//STRIP001      for (USHORT i=0; i<nInfoCount; i++)
//STRIP001      {
//STRIP001          pColStart[i] = pStart[i];
//STRIP001          pColFormat[i] = pFormat[i];
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      pColStart = NULL;
//STRIP001      pColFormat = NULL;
//STRIP001  }
//STRIP001 }


//STRIP001 void ScAsciiOptions::SetColumnInfo( const ScCsvExpDataVec& rDataVec )
//STRIP001 {
//STRIP001  delete[] pColStart;
//STRIP001     pColStart = NULL;
//STRIP001  delete[] pColFormat;
//STRIP001     pColFormat = NULL;
//STRIP001
//STRIP001     nInfoCount = static_cast< sal_uInt16 >( rDataVec.size() );
//STRIP001     if( nInfoCount )
//STRIP001  {
//STRIP001         pColStart = new xub_StrLen[ nInfoCount ];
//STRIP001         pColFormat = new sal_uInt8[ nInfoCount ];
//STRIP001         for( sal_uInt16 nIx = 0; nIx < nInfoCount; ++nIx )
//STRIP001      {
//STRIP001             pColStart[ nIx ] = rDataVec[ nIx ].mnIndex;
//STRIP001             pColFormat[ nIx ] = rDataVec[ nIx ].mnType;
//STRIP001      }
//STRIP001  }
//STRIP001 }


//STRIP001 ScAsciiOptions&  ScAsciiOptions::operator=( const ScAsciiOptions& rCpy )
//STRIP001 {
//STRIP001  SetColInfo( rCpy.nInfoCount, rCpy.pColStart, rCpy.pColFormat );
//STRIP001
//STRIP001  bFixedLen       = rCpy.bFixedLen;
//STRIP001  aFieldSeps      = rCpy.aFieldSeps;
//STRIP001  bMergeFieldSeps = rCpy.bMergeFieldSeps;
//STRIP001  cTextSep        = rCpy.cTextSep;
//STRIP001  eCharSet        = rCpy.eCharSet;
//STRIP001  bCharSetSystem  = rCpy.bCharSetSystem;
//STRIP001  nStartRow       = rCpy.nStartRow;
//STRIP001
//STRIP001  return *this;
//STRIP001 }


//STRIP001 BOOL ScAsciiOptions::operator==( const ScAsciiOptions& rCmp ) const
//STRIP001 {
//STRIP001  if ( bFixedLen       == rCmp.bFixedLen &&
//STRIP001       aFieldSeps      == rCmp.aFieldSeps &&
//STRIP001       bMergeFieldSeps == rCmp.bMergeFieldSeps &&
//STRIP001       cTextSep        == rCmp.cTextSep &&
//STRIP001       eCharSet        == rCmp.eCharSet &&
//STRIP001       bCharSetSystem  == rCmp.bCharSetSystem &&
//STRIP001       nStartRow       == rCmp.nStartRow &&
//STRIP001       nInfoCount      == rCmp.nInfoCount )
//STRIP001  {
//STRIP001      DBG_ASSERT( !nInfoCount || (pColStart && pColFormat && rCmp.pColStart && rCmp.pColFormat),
//STRIP001                   "0-Zeiger in ScAsciiOptions" );
//STRIP001      for (USHORT i=0; i<nInfoCount; i++)
//STRIP001          if ( pColStart[i] != rCmp.pColStart[i] ||
//STRIP001               pColFormat[i] != rCmp.pColFormat[i] )
//STRIP001              return FALSE;
//STRIP001
//STRIP001      return TRUE;
//STRIP001  }
//STRIP001  return FALSE;
//STRIP001 }

//
//  Der Options-String darf kein Semikolon mehr enthalten (wegen Pickliste)
//  darum ab Version 336 Komma stattdessen
//


/*N*/ void ScAsciiOptions::ReadFromString( const String& rString )
/*N*/ {
/*N*/   xub_StrLen nCount = rString.GetTokenCount(',');
/*N*/   String aToken;
/*N*/   xub_StrLen nSub;
/*N*/   xub_StrLen i;
/*N*/
/*N*/       //
/*N*/       //  Feld-Trenner
/*N*/       //
/*N*/
/*N*/   if ( nCount >= 1 )
/*N*/   {
/*N*/       bFixedLen = bMergeFieldSeps = FALSE;
/*N*/       aFieldSeps.Erase();
/*N*/
/*N*/       aToken = rString.GetToken(0,',');
/*N*/       if ( aToken.EqualsAscii(pStrFix) )
/*N*/           bFixedLen = TRUE;
/*N*/       nSub = aToken.GetTokenCount('/');
/*N*/       for ( i=0; i<nSub; i++ )
/*N*/       {
/*N*/           String aCode = aToken.GetToken( i, '/' );
/*N*/           if ( aCode.EqualsAscii(pStrMrg) )
/*N*/               bMergeFieldSeps = TRUE;
/*N*/           else
/*N*/           {
/*N*/               sal_Int32 nVal = aCode.ToInt32();
/*N*/               if ( nVal )
/*N*/                   aFieldSeps += (sal_Unicode) nVal;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/       //
/*N*/       //  Text-Trenner
/*N*/       //
/*N*/
/*N*/   if ( nCount >= 2 )
/*N*/   {
/*N*/       aToken = rString.GetToken(1,',');
/*N*/       sal_Int32 nVal = aToken.ToInt32();
/*N*/       cTextSep = (sal_Unicode) nVal;
/*N*/   }
/*N*/
/*N*/       //
/*N*/       //  Zeichensatz
/*N*/       //
/*N*/
/*N*/   if ( nCount >= 3 )
/*N*/   {
/*N*/       aToken = rString.GetToken(2,',');
/*N*/       eCharSet = ScGlobal::GetCharsetValue( aToken );
/*N*/   }
/*N*/
/*N*/       //
/*N*/       //  Startzeile
/*N*/       //
/*N*/
/*N*/   if ( nCount >= 4 )
/*N*/   {
/*N*/       aToken = rString.GetToken(3,',');
/*N*/       nStartRow = aToken.ToInt32();
/*N*/   }
/*N*/
/*N*/       //
/*N*/       //  Spalten-Infos
/*N*/       //
/*N*/
/*N*/   if ( nCount >= 5 )
/*N*/   {
/*N*/       delete[] pColStart;
/*N*/       delete[] pColFormat;
/*N*/
/*N*/       aToken = rString.GetToken(4,',');
/*N*/       nSub = aToken.GetTokenCount('/');
/*N*/       nInfoCount = nSub / 2;
/*N*/       if (nInfoCount)
/*N*/       {
/*N*/           pColStart = new xub_StrLen[nInfoCount];
/*N*/           pColFormat = new BYTE[nInfoCount];
/*N*/           for (USHORT nInfo=0; nInfo<nInfoCount; nInfo++)
/*N*/           {
/*N*/               pColStart[nInfo]  = (xub_StrLen) aToken.GetToken( 2*nInfo, '/' ).ToInt32();
/*N*/               pColFormat[nInfo] = (BYTE) aToken.GetToken( 2*nInfo+1, '/' ).ToInt32();
/*N*/           }
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           pColStart = NULL;
/*N*/           pColFormat = NULL;
/*N*/       }
/*N*/   }
/*N*/ }


/*N*/ String ScAsciiOptions::WriteToString() const
/*N*/ {
/*N*/   String aOutStr;
/*N*/
/*N*/       //
/*N*/       //  Feld-Trenner
/*N*/       //
/*N*/
/*N*/   if ( bFixedLen )
/*N*/       aOutStr.AppendAscii(pStrFix);
/*N*/   else if ( !aFieldSeps.Len() )
/*N*/       aOutStr += '0';
/*N*/   else
/*N*/   {
/*N*/       xub_StrLen nLen = aFieldSeps.Len();
/*N*/       for (xub_StrLen i=0; i<nLen; i++)
/*N*/       {
/*N*/           if (i)
/*N*/               aOutStr += '/';
/*N*/           aOutStr += String::CreateFromInt32(aFieldSeps.GetChar(i));
/*N*/       }
/*N*/       if ( bMergeFieldSeps )
/*N*/       {
/*N*/           aOutStr += '/';
/*N*/           aOutStr.AppendAscii(pStrMrg);
/*N*/       }
/*N*/   }
/*N*/
/*N*/   aOutStr += ',';                 // Token-Ende
/*N*/
/*N*/       //
/*N*/       //  Text-Trenner
/*N*/       //
/*N*/
/*N*/   aOutStr += String::CreateFromInt32(cTextSep);
/*N*/   aOutStr += ',';                 // Token-Ende
/*N*/
/*N*/       //
/*N*/       //  Zeichensatz
/*N*/       //
/*N*/
/*N*/   if ( bCharSetSystem )           // force "SYSTEM"
/*N*/       aOutStr += ScGlobal::GetCharsetString( RTL_TEXTENCODING_DONTKNOW );
/*N*/   else
/*N*/       aOutStr += ScGlobal::GetCharsetString( eCharSet );
/*N*/   aOutStr += ',';                 // Token-Ende
/*N*/
/*N*/       //
/*N*/       //  Startzeile
/*N*/       //
/*N*/
/*N*/   aOutStr += String::CreateFromInt32(nStartRow);
/*N*/   aOutStr += ',';                 // Token-Ende
/*N*/
/*N*/       //
/*N*/       //  Spalten-Infos
/*N*/       //
/*N*/
/*N*/   DBG_ASSERT( !nInfoCount || (pColStart && pColFormat), "0-Zeiger in ScAsciiOptions" );
/*N*/   for (USHORT nInfo=0; nInfo<nInfoCount; nInfo++)
/*N*/   {
/*N*/       if (nInfo)
/*N*/           aOutStr += '/';
/*N*/       aOutStr += String::CreateFromInt32(pColStart[nInfo]);
/*N*/       aOutStr += '/';
/*N*/       aOutStr += String::CreateFromInt32(pColFormat[nInfo]);
/*N*/   }
/*N*/
/*N*/   return aOutStr;
/*N*/ }

#if 0
//  Code, um die Spalten-Liste aus einem Excel-kompatiblen String zu erzeugen:
//  (im Moment nicht benutzt)

//STRIP001 void ScAsciiOptions::InterpretColumnList( const String& rString )
//STRIP001 {
//STRIP001  //  Eingabe ist 1-basiert, pColStart fuer FixedLen ist 0-basiert
//STRIP001
//STRIP001  //  Kommas durch Semikolon ersetzen
//STRIP001
//STRIP001  String aSemiStr = rString;
//STRIP001  USHORT nPos = 0;
//STRIP001  do
//STRIP001      nPos = aSemiStr.SearchAndReplace( ',', ';', nPos );
//STRIP001  while ( nPos != STRING_NOTFOUND );
//STRIP001
//STRIP001  //  Eintraege sortieren
//STRIP001
//STRIP001  USHORT nCount = aSemiStr.GetTokenCount();
//STRIP001  USHORT* pTemp = new USHORT[nCount+1];
//STRIP001  pTemp[0] = 1;                                   // erste Spalte faengt immer bei 1 an
//STRIP001  USHORT nFound = 1;
//STRIP001  USHORT i,j;
//STRIP001  for (i=0; i<nCount; i++)
//STRIP001  {
//STRIP001      USHORT nVal = (USHORT) aSemiStr.GetToken(i);
//STRIP001      if (nVal)
//STRIP001      {
//STRIP001          BOOL bThere = FALSE;
//STRIP001          nPos = 0;
//STRIP001          for (j=0; j<nFound; j++)
//STRIP001          {
//STRIP001              if ( pTemp[j] == nVal )
//STRIP001                  bThere = TRUE;
//STRIP001              else if ( pTemp[j] < nVal )
//STRIP001                  nPos = j+1;
//STRIP001          }
//STRIP001          if ( !bThere )
//STRIP001          {
//STRIP001              if ( nPos < nFound )
//STRIP001                  memmove( &pTemp[nPos+1], &pTemp[nPos], (nFound-nPos)*sizeof(USHORT) );
//STRIP001              pTemp[nPos] = nVal;
//STRIP001              ++nFound;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  //  Eintraege uebernehmen
//STRIP001
//STRIP001  delete[] pColStart;
//STRIP001  delete[] pColFormat;
//STRIP001  nInfoCount = nFound;
//STRIP001  if (nInfoCount)
//STRIP001  {
//STRIP001      pColStart = new USHORT[nInfoCount];
//STRIP001      pColFormat = new BYTE[nInfoCount];
//STRIP001      for (i=0; i<nInfoCount; i++)
//STRIP001      {
//STRIP001          pColStart[i] = pTemp[i] - 1;
//STRIP001          pColFormat[i] = SC_COL_STANDARD;
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      pColStart = NULL;
//STRIP001      pColFormat = NULL;
//STRIP001  }
//STRIP001
//STRIP001  bFixedLen = TRUE;           // sonst macht's keinen Sinn
//STRIP001
//STRIP001  //  aufraeumen
//STRIP001
//STRIP001  delete[] pTemp;
//STRIP001 }
#endif


// ============================================================================

void lcl_FillCombo( ComboBox& rCombo, const String& rList, sal_Unicode cSelect )
{
    DBG_ASSERT(0, "STRIP"); //STRIP001 xub_StrLen i;
//STRIP001  xub_StrLen nCount = rList.GetTokenCount('\t');
//STRIP001  for ( i=0; i<nCount; i+=2 )
//STRIP001      rCombo.InsertEntry( rList.GetToken(i,'\t') );
//STRIP001
//STRIP001  if ( cSelect )
//STRIP001  {
//STRIP001      String aStr;
//STRIP001      for ( i=0; i<nCount; i+=2 )
//STRIP001          if ( (sal_Unicode)rList.GetToken(i+1,'\t').ToInt32() == cSelect )
//STRIP001              aStr = rList.GetToken(i,'\t');
//STRIP001      if (!aStr.Len())
//STRIP001          aStr = cSelect;         // Ascii
//STRIP001
//STRIP001      rCombo.SetText(aStr);
//STRIP001  }
}

sal_Unicode lcl_CharFromCombo( ComboBox& rCombo, const String& rList )
{
    sal_Unicode c = 0;
    DBG_ASSERT(0, "STRIP"); //STRIP001 String aStr = rCombo.GetText();
//STRIP001  if ( aStr.Len() )
//STRIP001  {
//STRIP001      xub_StrLen nCount = rList.GetTokenCount('\t');
//STRIP001      for ( xub_StrLen i=0; i<nCount; i+=2 )
//STRIP001         {
//STRIP001             if ( ScGlobal::pTransliteration->isEqual( aStr, rList.GetToken(i,'\t') ) )
//STRIP001              c = (sal_Unicode)rList.GetToken(i+1,'\t').ToInt32();
//STRIP001         }
//STRIP001      if (!c)
//STRIP001          c = (sal_Unicode) aStr.ToInt32();       // Ascii
//STRIP001  }
    return c;
}


// ----------------------------------------------------------------------------

//STRIP001 ScImportAsciiDlg::ScImportAsciiDlg( Window* pParent,String aDatName,
//STRIP001                                  SvStream* pInStream, sal_Unicode cSep ) :
//STRIP001      ModalDialog ( pParent, ScResId( RID_SCDLG_ASCII ) ),
//STRIP001         pDatStream  ( pInStream ),
//STRIP001
//STRIP001      aRbFixed    ( this, ScResId( RB_FIXED ) ),
//STRIP001      aRbSeparated( this, ScResId( RB_SEPARATED ) ),
//STRIP001
//STRIP001      aCkbTab     ( this, ScResId( CKB_TAB ) ),
//STRIP001      aCkbSemicolon(this, ScResId( CKB_SEMICOLON ) ),
//STRIP001      aCkbComma   ( this, ScResId( CKB_COMMA  ) ),
//STRIP001      aCkbSpace   ( this, ScResId( CKB_SPACE   ) ),
//STRIP001      aCkbOther   ( this, ScResId( CKB_OTHER ) ),
//STRIP001      aEdOther    ( this, ScResId( ED_OTHER ) ),
//STRIP001
//STRIP001      aFtRow      ( this, ScResId( FT_AT_ROW  ) ),
//STRIP001      aNfRow      ( this, ScResId( NF_AT_ROW  ) ),
//STRIP001
//STRIP001      aFtCharSet  ( this, ScResId( FT_CHARSET ) ),
//STRIP001      aLbCharSet  ( this, ScResId( LB_CHARSET ) ),
//STRIP001         aFlSepOpt   ( this, ScResId( FL_SEPOPT ) ),
//STRIP001      aFtTextSep  ( this, ScResId( FT_TEXTSEP ) ),
//STRIP001      aCbTextSep  ( this, ScResId( CB_TEXTSEP ) ),
//STRIP001         aFlFieldOpt ( this, ScResId( FL_FIELDOPT ) ),
//STRIP001      aCkbAsOnce  ( this, ScResId( CB_ASONCE) ),
//STRIP001      aFtType     ( this, ScResId( FT_TYPE ) ),
//STRIP001      aLbType     ( this, ScResId( LB_TYPE1 ) ),
//STRIP001         maTableBox  ( this, ScResId( CTR_TABLEBOX ) ),
//STRIP001         aFlWidth    ( this, ScResId( FL_WIDTH ) ),
//STRIP001      aBtnOk      ( this, ScResId( BTN_OK ) ),
//STRIP001      aBtnCancel  ( this, ScResId( BTN_CANCEL ) ),
//STRIP001      aBtnHelp    ( this, ScResId( BTN_HELP ) ),
//STRIP001      aCharSetUser( ScResId( SCSTR_CHARSET_USER ) ),
//STRIP001      aColumnUser ( ScResId( SCSTR_COLUMN_USER ) ),
//STRIP001      aFldSepList ( ScResId( SCSTR_FIELDSEP ) ),
//STRIP001      aTextSepList( ScResId( SCSTR_TEXTSEP ) ),
//STRIP001      pRowPosArray( NULL ),
//STRIP001         pRowPosArrayUnicode( NULL ),
//STRIP001         bVFlag      ( FALSE )
//STRIP001 {
//STRIP001  FreeResource();
//STRIP001
//STRIP001  String aName = GetText();
//STRIP001  aName.AppendAscii(RTL_CONSTASCII_STRINGPARAM(" - ["));
//STRIP001  aName += aDatName;
//STRIP001  aName += ']';
//STRIP001  SetText( aName );
//STRIP001
//STRIP001  switch(cSep)
//STRIP001  {
//STRIP001         case '\t':  aCkbTab.Check();        break;
//STRIP001         case ';':   aCkbSemicolon.Check();  break;
//STRIP001         case ',':   aCkbComma.Check();      break;
//STRIP001         case ' ':   aCkbSpace.Check();      break;
//STRIP001         default:
//STRIP001             aCkbOther.Check();
//STRIP001             aEdOther.SetText( cSep );
//STRIP001  }
//STRIP001
//STRIP001  nArrayEndPos = nArrayEndPosUnicode = 0;
//STRIP001  USHORT nField;
//STRIP001  BOOL bPreselectUnicode = FALSE;
//STRIP001     if( pDatStream )
//STRIP001  {
//STRIP001      USHORT j;
//STRIP001      pRowPosArray=new ULONG[ASCIIDLG_MAXROWS+2];
//STRIP001      pRowPosArrayUnicode=new ULONG[ASCIIDLG_MAXROWS+2];
//STRIP001      ULONG *pPtrRowPos=pRowPosArray;
//STRIP001      ULONG *pPtrRowPosUnicode=pRowPosArrayUnicode;
//STRIP001      for(nField=0;nField<ASCIIDLG_MAXROWS;nField++)
//STRIP001      {
//STRIP001          *pPtrRowPos++=0;
//STRIP001          *pPtrRowPosUnicode++=0;
//STRIP001      }
//STRIP001      pDatStream->SetBufferSize(ASCIIDLG_MAXROWS);
//STRIP001      pDatStream->SetStreamCharSet( gsl_getSystemTextEncoding() );    //!???
//STRIP001      pDatStream->Seek( 0 );
//STRIP001         for ( j=0; j < CSV_PREVIEW_LINES; j++ )
//STRIP001      {
//STRIP001          pRowPosArray[nArrayEndPos++]=pDatStream->Tell();
//STRIP001          if(!pDatStream->ReadLine( aPreviewLine[j] ))
//STRIP001          {
//STRIP001              bVFlag=TRUE;
//STRIP001                 maTableBox.Execute( CSVCMD_SETLINECOUNT, j );
//STRIP001              break;
//STRIP001          }
//STRIP001      }
//STRIP001      nStreamPos = pDatStream->Tell();
//STRIP001
//STRIP001      pDatStream->Seek( 0 );
//STRIP001      pDatStream->StartReadingUnicodeText();
//STRIP001      ULONG nUniPos = pDatStream->Tell();
//STRIP001      if ( nUniPos > 0 )
//STRIP001          bPreselectUnicode = TRUE;   // read 0xfeff/0xfffe
//STRIP001      else
//STRIP001      {
//STRIP001          UINT16 n;
//STRIP001          *pDatStream >> n;
//STRIP001          // Assume that normal ASCII/ANSI/ISO/etc. text doesn't start with
//STRIP001          // control characters except CR,LF,TAB
//STRIP001          if ( (n & 0xff00) < 0x2000 )
//STRIP001          {
//STRIP001              switch ( n & 0xff00 )
//STRIP001              {
//STRIP001                  case 0x0900 :
//STRIP001                  case 0x0a00 :
//STRIP001                  case 0x0d00 :
//STRIP001                  break;
//STRIP001                  default:
//STRIP001                      bPreselectUnicode = TRUE;
//STRIP001              }
//STRIP001          }
//STRIP001          pDatStream->Seek( nUniPos );
//STRIP001      }
//STRIP001         for ( j=0; j < CSV_PREVIEW_LINES; j++ )
//STRIP001      {
//STRIP001          pRowPosArrayUnicode[nArrayEndPosUnicode++] = pDatStream->Tell();
//STRIP001          if( !pDatStream->ReadUniStringLine( aPreviewLineUnicode[j] ) )
//STRIP001              break;
//STRIP001          // #84386# Reading Unicode on ASCII/ANSI data won't find any line
//STRIP001          // ends and therefor tries to read the whole file into strings.
//STRIP001          // Check if first line is completely filled and don't try any further.
//STRIP001          if ( j == 0 && aPreviewLineUnicode[j].Len() == STRING_MAXLEN )
//STRIP001              break;
//STRIP001      }
//STRIP001      nStreamPosUnicode = pDatStream->Tell();
//STRIP001
//STRIP001      //  #107455# If the file content isn't unicode, ReadUniStringLine
//STRIP001      //  may try to seek beyond the file's end and cause a CANTSEEK error
//STRIP001      //  (depending on the stream type). The error code has to be cleared,
//STRIP001      //  or further read operations (including non-unicode) will fail.
//STRIP001      if ( pDatStream->GetError() == ERRCODE_IO_CANTSEEK )
//STRIP001          pDatStream->ResetError();
//STRIP001  }
//STRIP001
//STRIP001     aNfRow.SetModifyHdl( LINK( this, ScImportAsciiDlg, FirstRowHdl ) );
//STRIP001
//STRIP001     // *** Separator characters ***
//STRIP001     lcl_FillCombo( aCbTextSep, aTextSepList, 34 );      // Default "
//STRIP001
//STRIP001     Link aSeparatorHdl =LINK( this, ScImportAsciiDlg, SeparatorHdl );
//STRIP001     aCbTextSep.SetSelectHdl( aSeparatorHdl );
//STRIP001     aCbTextSep.SetModifyHdl( aSeparatorHdl );
//STRIP001     aCkbTab.SetClickHdl( aSeparatorHdl );
//STRIP001     aCkbSemicolon.SetClickHdl( aSeparatorHdl );
//STRIP001     aCkbComma.SetClickHdl( aSeparatorHdl );
//STRIP001     aCkbAsOnce.SetClickHdl( aSeparatorHdl );
//STRIP001     aCkbSpace.SetClickHdl( aSeparatorHdl );
//STRIP001     aCkbOther.SetClickHdl( aSeparatorHdl );
//STRIP001     aEdOther.SetModifyHdl( aSeparatorHdl );
//STRIP001
//STRIP001     // *** text encoding ListBox ***
//STRIP001  // all encodings allowed, including Unicode, but subsets are excluded
//STRIP001  aLbCharSet.FillFromTextEncodingTable( TRUE );
//STRIP001  // Insert one "SYSTEM" entry for compatibility in AsciiOptions and system
//STRIP001  // independent document linkage.
//STRIP001  aLbCharSet.InsertTextEncoding( RTL_TEXTENCODING_DONTKNOW, aCharSetUser );
//STRIP001  aLbCharSet.SelectTextEncoding( bPreselectUnicode ?
//STRIP001      RTL_TEXTENCODING_UNICODE : gsl_getSystemTextEncoding() );
//STRIP001     SetSelectedCharSet();
//STRIP001  aLbCharSet.SetSelectHdl( LINK( this, ScImportAsciiDlg, CharSetHdl ) );
//STRIP001
//STRIP001     // *** column type ListBox ***
//STRIP001  xub_StrLen nCount = aColumnUser.GetTokenCount();
//STRIP001  for (xub_StrLen i=0; i<nCount; i++)
//STRIP001         aLbType.InsertEntry( aColumnUser.GetToken( i ) );
//STRIP001
//STRIP001     aLbType.SetSelectHdl( LINK( this, ScImportAsciiDlg, LbColTypeHdl ) );
//STRIP001     aFtType.Disable();
//STRIP001     aLbType.Disable();
//STRIP001
//STRIP001     // *** table box preview ***
//STRIP001     maTableBox.SetUpdateTextHdl( LINK( this, ScImportAsciiDlg, UpdateTextHdl ) );
//STRIP001     maTableBox.InitTypes( aLbType );
//STRIP001     maTableBox.SetColTypeHdl( LINK( this, ScImportAsciiDlg, ColTypeHdl ) );
//STRIP001
//STRIP001  if(!bVFlag)
//STRIP001         maTableBox.Execute( CSVCMD_SETLINECOUNT, ASCIIDLG_MAXROWS );
//STRIP001
//STRIP001     aRbSeparated.SetClickHdl( LINK( this, ScImportAsciiDlg, RbSepFixHdl ) );
//STRIP001     aRbFixed.SetClickHdl( LINK( this, ScImportAsciiDlg, RbSepFixHdl ) );
//STRIP001
//STRIP001     SetupSeparatorCtrls();
//STRIP001     RbSepFixHdl( &aRbFixed );
//STRIP001
//STRIP001     maTableBox.Execute( CSVCMD_NEWCELLTEXTS );
//STRIP001 }


//STRIP001 ScImportAsciiDlg::~ScImportAsciiDlg()
//STRIP001 {
//STRIP001  delete[] pRowPosArray;
//STRIP001  delete[] pRowPosArrayUnicode;
//STRIP001
//STRIP001 }

//STRIP001 void ScImportAsciiDlg::GetOptions( ScAsciiOptions& rOpt )
//STRIP001 {
//STRIP001     rOpt.SetCharSet( meCharSet );
//STRIP001     rOpt.SetCharSetSystem( mbCharSetSystem );
//STRIP001     rOpt.SetFixedLen( aRbFixed.IsChecked() );
//STRIP001     rOpt.SetStartRow( (USHORT)aNfRow.GetValue() );
//STRIP001     maTableBox.FillColumnData( rOpt );
//STRIP001     if( aRbSeparated.IsChecked() )
//STRIP001     {
//STRIP001         rOpt.SetFieldSeps( GetSeparators() );
//STRIP001         rOpt.SetMergeSeps( aCkbAsOnce.IsChecked() );
//STRIP001         rOpt.SetTextSep( lcl_CharFromCombo( aCbTextSep, aTextSepList ) );
//STRIP001     }
//STRIP001 }

//STRIP001 void ScImportAsciiDlg::SetSelectedCharSet()
//STRIP001 {
//STRIP001     meCharSet = aLbCharSet.GetSelectTextEncoding();
//STRIP001     mbCharSetSystem = (meCharSet == RTL_TEXTENCODING_DONTKNOW);
//STRIP001     if( mbCharSetSystem )
//STRIP001         meCharSet = gsl_getSystemTextEncoding();
//STRIP001 }

//STRIP001 String ScImportAsciiDlg::GetSeparators() const
//STRIP001 {
//STRIP001     String aSepChars;
//STRIP001     if( aCkbTab.IsChecked() )
//STRIP001         aSepChars += '\t';
//STRIP001     if( aCkbSemicolon.IsChecked() )
//STRIP001         aSepChars += ';';
//STRIP001     if( aCkbComma.IsChecked() )
//STRIP001         aSepChars += ',';
//STRIP001     if( aCkbSpace.IsChecked() )
//STRIP001         aSepChars += ' ';
//STRIP001     if( aCkbOther.IsChecked() )
//STRIP001         aSepChars += aEdOther.GetText();
//STRIP001     return aSepChars;
//STRIP001 }

//STRIP001 void ScImportAsciiDlg::SetupSeparatorCtrls()
//STRIP001 {
//STRIP001     BOOL bEnable = aRbSeparated.IsChecked();
//STRIP001     aCkbTab.Enable( bEnable );
//STRIP001     aCkbSemicolon.Enable( bEnable );
//STRIP001     aCkbComma.Enable( bEnable );
//STRIP001     aCkbSpace.Enable( bEnable );
//STRIP001     aCkbOther.Enable( bEnable );
//STRIP001     aEdOther.Enable( bEnable );
//STRIP001     aCkbAsOnce.Enable( bEnable );
//STRIP001     aFtTextSep.Enable( bEnable );
//STRIP001     aCbTextSep.Enable( bEnable );
//STRIP001 }

//STRIP001 void ScImportAsciiDlg::UpdateVertical( bool bSwitchToFromUnicode )
//STRIP001 {
//STRIP001  if ( bSwitchToFromUnicode )
//STRIP001  {
//STRIP001      bVFlag = FALSE;
//STRIP001         maTableBox.Execute( CSVCMD_SETLINECOUNT, ASCIIDLG_MAXROWS );
//STRIP001  }
//STRIP001  ULONG nNew = 0;
//STRIP001     if(!bVFlag)
//STRIP001  {
//STRIP001         // dragging the scrollbar -> read entire file
//STRIP001      bVFlag=TRUE;
//STRIP001      ULONG nRows = 0;
//STRIP001
//STRIP001      pDatStream->Seek(0);
//STRIP001         if ( meCharSet == RTL_TEXTENCODING_UNICODE )
//STRIP001      {
//STRIP001          String aStringUnicode;
//STRIP001          pDatStream->StartReadingUnicodeText();
//STRIP001          ULONG* pPtrRowPos = pRowPosArrayUnicode;
//STRIP001          *pPtrRowPos++ = 0;
//STRIP001          while( pDatStream->ReadUniStringLine( aStringUnicode ) )
//STRIP001          {
//STRIP001              nRows++;
//STRIP001              if( nRows > ASCIIDLG_MAXROWS )
//STRIP001                  break;
//STRIP001              *pPtrRowPos++ = pDatStream->Tell();
//STRIP001          }
//STRIP001          nStreamPosUnicode = pDatStream->Tell();
//STRIP001
//STRIP001          if ( pDatStream->GetError() == ERRCODE_IO_CANTSEEK )    // #107455# reset seek error
//STRIP001              pDatStream->ResetError();
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          ByteString aString;
//STRIP001          ULONG* pPtrRowPos = pRowPosArray;
//STRIP001          *pPtrRowPos++ = 0;
//STRIP001          while( pDatStream->ReadLine( aString ) )
//STRIP001          {
//STRIP001              nRows++;
//STRIP001              if( nRows > ASCIIDLG_MAXROWS )
//STRIP001                  break;
//STRIP001              *pPtrRowPos++ = pDatStream->Tell();
//STRIP001          }
//STRIP001          nStreamPos = pDatStream->Tell();
//STRIP001      }
//STRIP001
//STRIP001         maTableBox.Execute( CSVCMD_SETLINECOUNT, nRows );
//STRIP001  }
//STRIP001
//STRIP001     nNew = maTableBox.GetFirstVisLine();
//STRIP001
//STRIP001     if ( meCharSet == RTL_TEXTENCODING_UNICODE )
//STRIP001  {
//STRIP001      if ( bVFlag || nNew <= nArrayEndPosUnicode )
//STRIP001          pDatStream->Seek( pRowPosArrayUnicode[nNew] );
//STRIP001      else
//STRIP001          pDatStream->Seek( nStreamPosUnicode );
//STRIP001         for ( USHORT j=0; j < CSV_PREVIEW_LINES; j++ )
//STRIP001      {
//STRIP001          if( !bVFlag && nNew+j >= nArrayEndPos )
//STRIP001          {
//STRIP001              pRowPosArrayUnicode[nNew+j] = pDatStream->Tell();
//STRIP001              nArrayEndPosUnicode = (USHORT) nNew+j;
//STRIP001          }
//STRIP001          // #84386# Reading Unicode on ASCII/ANSI data won't find any line
//STRIP001          // ends and therefor tries to read the whole file into strings.
//STRIP001          // Check if first line is completely filled and don't try any further.
//STRIP001          if( (!pDatStream->ReadUniStringLine( aPreviewLineUnicode[j] ) ||
//STRIP001               (j == 0 && aPreviewLineUnicode[j].Len() == STRING_MAXLEN)) &&
//STRIP001               !bVFlag )
//STRIP001          {
//STRIP001              bVFlag = TRUE;
//STRIP001                 maTableBox.Execute( CSVCMD_SETLINECOUNT, nArrayEndPosUnicode );
//STRIP001          }
//STRIP001      }
//STRIP001      nStreamPosUnicode = pDatStream->Tell();
//STRIP001
//STRIP001      if ( pDatStream->GetError() == ERRCODE_IO_CANTSEEK )    // #107455# reset seek error
//STRIP001          pDatStream->ResetError();
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if ( bVFlag || nNew <= nArrayEndPos )
//STRIP001          pDatStream->Seek( pRowPosArray[nNew] );
//STRIP001      else
//STRIP001          pDatStream->Seek( nStreamPos );
//STRIP001         for ( USHORT j=0; j < CSV_PREVIEW_LINES; j++ )
//STRIP001      {
//STRIP001          if( !bVFlag && nNew+j >= nArrayEndPos )
//STRIP001          {
//STRIP001              pRowPosArray[nNew+j] = pDatStream->Tell();
//STRIP001              nArrayEndPos = (USHORT) nNew+j;
//STRIP001          }
//STRIP001          if( !pDatStream->ReadLine( aPreviewLine[j] ) && !bVFlag )
//STRIP001          {
//STRIP001              bVFlag = TRUE;
//STRIP001                 maTableBox.Execute( CSVCMD_SETLINECOUNT, nArrayEndPos );
//STRIP001          }
//STRIP001      }
//STRIP001      nStreamPos = pDatStream->Tell();
//STRIP001  }
//STRIP001 }


// ----------------------------------------------------------------------------

//STRIP001 IMPL_LINK( ScImportAsciiDlg, RbSepFixHdl, RadioButton*, pButton )
//STRIP001 {
//STRIP001      DBG_ASSERT( pButton, "ScImportAsciiDlg::RbSepFixHdl - missing sender" );
//STRIP001
//STRIP001     if( (pButton == &aRbFixed) || (pButton == &aRbSeparated) )
//STRIP001  {
//STRIP001         SetPointer( Pointer( POINTER_WAIT ) );
//STRIP001         if( aRbFixed.IsChecked() )
//STRIP001             maTableBox.SetFixedWidthMode();
//STRIP001         else
//STRIP001             maTableBox.SetSeparatorsMode();
//STRIP001         SetPointer( Pointer( POINTER_ARROW ) );
//STRIP001
//STRIP001         SetupSeparatorCtrls();
//STRIP001  }
//STRIP001  return 0;
//STRIP001 }

//STRIP001 IMPL_LINK( ScImportAsciiDlg, SeparatorHdl, Control*, pCtrl )
//STRIP001 {
//STRIP001      DBG_ASSERT( pCtrl, "ScImportAsciiDlg::SeparatorHdl - missing sender" );
//STRIP001     DBG_ASSERT( !aRbFixed.IsChecked(), "ScImportAsciiDlg::SeparatorHdl - not allowed in fixed width" );
//STRIP001
//STRIP001     if( (pCtrl == &aCkbOther) && aCkbOther.IsChecked() )
//STRIP001         aEdOther.GrabFocus();
//STRIP001     else if( pCtrl == &aEdOther )
//STRIP001         aCkbOther.Check( aEdOther.GetText().Len() > 0 );
//STRIP001     maTableBox.Execute( CSVCMD_NEWCELLTEXTS );
//STRIP001      return 0;
//STRIP001 }

//STRIP001 IMPL_LINK( ScImportAsciiDlg, CharSetHdl, SvxTextEncodingBox*, pCharSetBox )
//STRIP001 {
//STRIP001    DBG_ASSERT( pCharSetBox, "ScImportAsciiDlg::CharSetHdl - missing sender" );
//STRIP001
//STRIP001     if( (pCharSetBox == &aLbCharSet) && (pCharSetBox->GetSelectEntryCount() == 1) )
//STRIP001     {
//STRIP001         SetPointer( Pointer( POINTER_WAIT ) );
//STRIP001         CharSet eOldCharSet = meCharSet;
//STRIP001         SetSelectedCharSet();
//STRIP001         if( (meCharSet == RTL_TEXTENCODING_UNICODE) != (eOldCharSet == RTL_TEXTENCODING_UNICODE) )
//STRIP001         {
//STRIP001             // switching to/from Unicode invalidates all positions
//STRIP001             if( pDatStream )
//STRIP001                 UpdateVertical( TRUE );
//STRIP001         }
//STRIP001         maTableBox.Execute( CSVCMD_NEWCELLTEXTS );
//STRIP001         SetPointer( Pointer( POINTER_ARROW ) );
//STRIP001     }
//STRIP001  return 0;
//STRIP001 }

//STRIP001 IMPL_LINK( ScImportAsciiDlg, FirstRowHdl, NumericField*, pNumField )
//STRIP001 {
//STRIP001     DBG_ASSERT( pNumField, "ScImportAsciiDlg::FirstRowHdl - missing sender" );
//STRIP001     maTableBox.Execute( CSVCMD_SETFIRSTIMPORTLINE, pNumField->GetValue() - 1 );
//STRIP001     return 0;
//STRIP001 }

//STRIP001 IMPL_LINK( ScImportAsciiDlg, LbColTypeHdl, ListBox*, pListBox )
//STRIP001 {
//STRIP001     DBG_ASSERT( pListBox, "ScImportAsciiDlg::LbColTypeHdl - missing sender" );
//STRIP001     if( pListBox == &aLbType )
//STRIP001         maTableBox.Execute( CSVCMD_SETCOLUMNTYPE, pListBox->GetSelectEntryPos() );
//STRIP001  return 0;
//STRIP001 }

//STRIP001 IMPL_LINK( ScImportAsciiDlg, UpdateTextHdl, ScCsvTableBox*, pTableBox )
//STRIP001 {
//STRIP001     DBG_ASSERT( pTableBox, "ScImportAsciiDlg::UpdateTextHdl - missing sender" );
//STRIP001
//STRIP001     BOOL bVFlag1 = bVFlag;
//STRIP001     if( pDatStream )
//STRIP001         UpdateVertical();
//STRIP001     if( bVFlag != bVFlag1 )
//STRIP001         UpdateVertical();
//STRIP001
//STRIP001  sal_Unicode cTextSep = lcl_CharFromCombo( aCbTextSep, aTextSepList );
//STRIP001     bool bMergeSep = (aCkbAsOnce.IsChecked() == TRUE);
//STRIP001
//STRIP001     if( meCharSet == RTL_TEXTENCODING_UNICODE )
//STRIP001         maTableBox.SetUniStrings( aPreviewLineUnicode, GetSeparators(), cTextSep, bMergeSep );
//STRIP001     else
//STRIP001         maTableBox.SetByteStrings( aPreviewLine, meCharSet, GetSeparators(), cTextSep, bMergeSep );
//STRIP001
//STRIP001     return 0;
//STRIP001 }

//STRIP001 IMPL_LINK( ScImportAsciiDlg, ColTypeHdl, ScCsvTableBox*, pTableBox )
//STRIP001 {
//STRIP001     DBG_ASSERT( pTableBox, "ScImportAsciiDlg::ColTypeHdl - missing sender" );
//STRIP001
//STRIP001     sal_Int32 nType = pTableBox->GetSelColumnType();
//STRIP001     sal_Int32 nTypeCount = aLbType.GetEntryCount();
//STRIP001     bool bEmpty = (nType == CSV_TYPE_MULTI);
//STRIP001     bool bEnable = ((0 <= nType) && (nType < nTypeCount)) || bEmpty;
//STRIP001
//STRIP001     aFtType.Enable( bEnable );
//STRIP001     aLbType.Enable( bEnable );
//STRIP001
//STRIP001     Link aSelHdl = aLbType.GetSelectHdl();
//STRIP001     aLbType.SetSelectHdl( Link() );
//STRIP001     if( bEmpty )
//STRIP001         aLbType.SetNoSelection();
//STRIP001     else if( bEnable )
//STRIP001         aLbType.SelectEntryPos( static_cast< sal_uInt16 >( nType ) );
//STRIP001     aLbType.SetSelectHdl( aSelHdl );
//STRIP001
//STRIP001     return 0;
//STRIP001 }

