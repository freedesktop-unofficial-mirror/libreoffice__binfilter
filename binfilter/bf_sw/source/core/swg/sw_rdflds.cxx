/*************************************************************************
 *
 *  $RCSfile: sw_rdflds.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:51:01 $
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
namespace binfilter {


//STRIP001 #pragma hdrstop
//STRIP001
//STRIP001 #include <stdlib.h>  // strtod()
//STRIP001
//STRIP001 #ifndef _LINKMGR_HXX //autogen
//STRIP001 #include <so3/linkmgr.hxx>
//STRIP001 #endif
//STRIP001 #ifndef _DATETIME_HXX
//STRIP001 #include <tools/datetime.hxx>
//STRIP001 #endif
//STRIP001
//STRIP001 #include "doc.hxx"
//STRIP001 #include "rdswg.hxx"
//STRIP001 #include "fldbas.hxx"
//STRIP001 #include "docufld.hxx"
//STRIP001 #include "chpfld.hxx"
//STRIP001 #include "ddefld.hxx"
//STRIP001 #include "expfld.hxx"
//STRIP001 #include "reffld.hxx"
//STRIP001 #include "usrfld.hxx"
//STRIP001 #include "dbfld.hxx"
//STRIP001 #include "flddat.hxx"
//STRIP001 #include "numrule.hxx"
//STRIP001
//STRIP001 static ULONG  nNewFldFmt;                        // Aktueller Format-Wert
//STRIP001
//STRIP001
//STRIP001 static SwDBFieldType* In_SwDBFieldType( SwSwgReader& rPar )
//STRIP001 {
//STRIP001  // MS: An den Typen DBName und FeldName uebergeben
//STRIP001  SwDBFieldType aType( rPar.pDoc, rPar.GetText(), rPar.pDoc->GetDBData() );
//STRIP001  // altes Expand wegwerfen
//STRIP001  if( rPar.aHdr.nVersion < SWG_VER_POOLIDS )
//STRIP001      rPar.GetText( FALSE );
//STRIP001
//STRIP001  //JP 13.02.96: Bug 25321 - Felder ohne Namen nie einlesen
//STRIP001  if( !aType.GetName().Len() )
//STRIP001      return 0;
//STRIP001
//STRIP001  return (SwDBFieldType*) rPar.pDoc->InsertFldType( aType );
//STRIP001 }
//STRIP001
//STRIP001 static SwUserFieldType* In_SwUserFieldType( SwSwgReader& rPar )
//STRIP001 {
//STRIP001  SwUserFieldType aType( rPar.pDoc, rPar.GetText() );
//STRIP001  aType.SetContent( rPar.GetText() );
//STRIP001
//STRIP001  //JP 13.02.96: Bug 25321 - Felder ohne Namen nie einlesen
//STRIP001  if( !aType.GetName().Len() )
//STRIP001      return 0;
//STRIP001
//STRIP001  SwUserFieldType* p = (SwUserFieldType*) rPar.pDoc->InsertFldType( aType );
//STRIP001
//STRIP001  sal_Char* dummy;
//STRIP001  ByteString aVal = rPar.GetAsciiText();
//STRIP001
//STRIP001  USHORT nType;
//STRIP001  if( rPar.aHdr.nVersion >= SWG_VER_POOLIDS )
//STRIP001      rPar.r >> nType;
//STRIP001
//STRIP001  if( !rPar.bNew && p->GetDepends() )
//STRIP001      return p;
//STRIP001
//STRIP001  p->SetValue( strtod( aVal.GetBuffer(), &dummy ) );
//STRIP001
//STRIP001  if( rPar.aHdr.nVersion >= SWG_VER_POOLIDS )
//STRIP001  {
//STRIP001      // hot fix
//STRIP001      if( !nType )
//STRIP001          nType = GSE_STRING;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      nType = (USHORT)nNewFldFmt & 3;
//STRIP001      nNewFldFmt &= ~3;
//STRIP001
//STRIP001      // Anfuehrungsstriche alter Vars wegschmeissen
//STRIP001      String aTmp(aType.GetContent());
//STRIP001      if(nType & GSE_STRING)
//STRIP001      {
//STRIP001          aTmp = aTmp.Copy(1, aTmp.Len() - 2);
//STRIP001          p->SetContent(aTmp);
//STRIP001      }
//STRIP001  }
//STRIP001  p->SetType( nType );
//STRIP001  return p;
//STRIP001 }
//STRIP001
//STRIP001 /* MS: Diese Felder gibt es nicht mehr
//STRIP001
//STRIP001 static SwRegFieldType* In_SwRegFieldType( SwSwgReader& rPar )
//STRIP001 {
//STRIP001  BYTE nCount;
//STRIP001  long nEditTime;
//STRIP001  rPar.r.long4();
//STRIP001  rPar.r >> nCount;
//STRIP001  aType.aTitle = rPar.GetText();
//STRIP001  rPar.r >> nEditTime;
//STRIP001  SwRegFieldType aType;
//STRIP001  aType.aEditTime.SetTime( nEditTime );
//STRIP001  for( BYTE i = 0; ( i < nCount ) && rPar.r.good(); i++ )
//STRIP001  {
//STRIP001      aType.aInfo[ i ].aAuthor = rPar.GetText();
//STRIP001      ULONG nDate;
//STRIP001      long  nTime;
//STRIP001      rPar.r >> nDate >> nTime;
//STRIP001      aType.aInfo[ i ].aDateTime.SetDate( nDate );
//STRIP001      aType.aInfo[ i ].aDateTime.SetTime( nTime );
//STRIP001  }
//STRIP001  rPar.r.long3();
//STRIP001  return (SwRegFieldType*) rPar.pDoc->InsertFldType( aType );
//STRIP001 }
//STRIP001
//STRIP001
//STRIP001 static SwVarRegFieldType* In_SwVarRegFieldType( SwSwgReader& rPar )
//STRIP001 {
//STRIP001  USHORT nType;
//STRIP001  rPar.r >> nType;
//STRIP001  SwVarRegFieldType aType( rPar.GetText(), nType );
//STRIP001  aType.SetValue( rPar.GetText() );
//STRIP001  return (SwVarRegFieldType*) rPar.pDoc->InsertFldType( aType );
//STRIP001 }
//STRIP001
//STRIP001 End Of Comment MS: */
//STRIP001
//STRIP001 static SwDDEFieldType* In_SwDDEFieldType( SwSwgReader& rPar )
//STRIP001 {
//STRIP001  USHORT nType;
//STRIP001  rPar.r >> nType;
//STRIP001  String aName( rPar.GetText() );
//STRIP001  String aCmd( rPar.GetText() );
//STRIP001  if( !nType )
//STRIP001         nType = ::so3::LINKUPDATE_ONCALL;
//STRIP001  else
//STRIP001         nType = ::so3::LINKUPDATE_ALWAYS;
//STRIP001
//STRIP001  // die ersten beiden Blanks gegen den neuen Trenner austauschen
//STRIP001  xub_StrLen nFnd = aCmd.Search( ' ' );
//STRIP001  if( STRING_NOTFOUND != nFnd )
//STRIP001         aCmd.SetChar( nFnd, ::so3::cTokenSeperator );
//STRIP001  nFnd = aCmd.Search( ' ', nFnd );
//STRIP001  if( STRING_NOTFOUND != nFnd )
//STRIP001         aCmd.SetChar( nFnd, ::so3::cTokenSeperator );
//STRIP001
//STRIP001  //JP 13.02.96: Bug 25321 - Felder ohne Namen nie einlesen
//STRIP001  if( !aName.Len() || !aCmd.Len() )
//STRIP001      return 0;
//STRIP001
//STRIP001  SwDDEFieldType aType( aName, aCmd, nType );
//STRIP001  return (SwDDEFieldType*) rPar.pDoc->InsertFldType( aType );
//STRIP001 }
//STRIP001
//STRIP001 static SwSetExpFieldType* In_SwSetExpFieldType( SwSwgReader& rPar )
//STRIP001 {
//STRIP001  USHORT nType;
//STRIP001  rPar.r >> nType;
//STRIP001  String aName( rPar.GetText() );
//STRIP001
//STRIP001  //JP 13.02.96: Bug 25321 - Felder ohne Namen nie einlesen
//STRIP001  if( !aName.Len() )
//STRIP001      return 0;
//STRIP001
//STRIP001  SwSetExpFieldType aType( rPar.pDoc, aName, nType );
//STRIP001  return (SwSetExpFieldType*) rPar.pDoc->InsertFldType( aType );
//STRIP001 }
//STRIP001
//STRIP001 /////////////////////////////////////////////////////////////////////////////
//STRIP001
//STRIP001 static SwField* In_SwDBField( SwSwgReader& rPar, SwDBFieldType* pType, USHORT nSub )
//STRIP001 {
//STRIP001  pType = In_SwDBFieldType( rPar );
//STRIP001
//STRIP001  //JP 13.02.96: Bug 25321 - Felder ohne Namen nie einlesen
//STRIP001  if( !pType )
//STRIP001      return 0;
//STRIP001
//STRIP001  SwDBField* pFld = new SwDBField( pType );
//STRIP001  pFld->SetSubType(nSub);
//STRIP001  if( rPar.aHdr.nVersion >= SWG_VER_POOLIDS )
//STRIP001  {   // Expansion laden
//STRIP001      pFld->InitContent(rPar.GetText( FALSE ));
//STRIP001  }
//STRIP001  return pFld;
//STRIP001 }
//STRIP001
//STRIP001 static SwField* In_SwUserField( SwSwgReader& rPar, SwUserFieldType* pType,
//STRIP001                              USHORT nSub )
//STRIP001 {
//STRIP001  pType = In_SwUserFieldType( rPar );
//STRIP001
//STRIP001  //JP 13.02.96: Bug 25321 - Felder ohne Namen nie einlesen
//STRIP001  if( !pType )
//STRIP001      return 0;
//STRIP001
//STRIP001  return new SwUserField( pType, nSub );    // MS: Hier kann auch das Format mit
//STRIP001                                      // uebergeben werden
//STRIP001  if( UF_STRING & pType->GetType() )
//STRIP001      nNewFldFmt = 0; // Warum auch immer!
//STRIP001
//STRIP001 }
//STRIP001
//STRIP001 static SwField* In_SwFileNameField( SwSwgReader&, SwFileNameFieldType* pType )
//STRIP001 {
//STRIP001  return new SwFileNameField( pType );
//STRIP001 }
//STRIP001
//STRIP001 static SwField* In_SwDBNameField( SwSwgReader& rPar, SwDBNameFieldType* pType )
//STRIP001 {
//STRIP001  return new SwDBNameField( pType, rPar.pDoc->GetDBData() );
//STRIP001 }
//STRIP001
//STRIP001 static SwField* In_SwDateField( SwSwgReader&, SwDateTimeFieldType* pType )
//STRIP001 {
//STRIP001  return new SwDateTimeField( pType, DATEFLD );
//STRIP001 }
//STRIP001
//STRIP001 static SwField* In_SwTimeField( SwSwgReader&, SwDateTimeFieldType* pType )
//STRIP001 {
//STRIP001  return new SwDateTimeField( pType, TIMEFLD );
//STRIP001 }
//STRIP001
//STRIP001 static SwField* In_SwPageNumberField( SwSwgReader& rPar, SwPageNumberFieldType* pType )
//STRIP001 {
//STRIP001  USHORT nOff = 0;
//STRIP001  USHORT nSub = PG_RANDOM;
//STRIP001  if( rPar.aHdr.nVersion >= SWG_VER_POOLIDS )
//STRIP001  {   rPar.r >> nOff;
//STRIP001      rPar.r >> nSub;
//STRIP001  }
//STRIP001  return new SwPageNumberField( pType, nSub, nNewFldFmt, nOff );
//STRIP001 }
//STRIP001
//STRIP001 static SwField* In_SwAuthorField( SwSwgReader&, SwAuthorFieldType* pType )
//STRIP001 {
//STRIP001  return new SwAuthorField( pType );
//STRIP001 }
//STRIP001
//STRIP001 static SwField* In_SwChapterField( SwSwgReader&, SwChapterFieldType* pType )
//STRIP001 {
//STRIP001  return new SwChapterField( pType );
//STRIP001 }
//STRIP001
//STRIP001 static SwField* In_SwDocStatField( SwSwgReader& rPar, SwDocStatFieldType* pType )
//STRIP001 {
//STRIP001  USHORT nSubType = 0;
//STRIP001  if( rPar.aHdr.nVersion < SWG_VER_POOLIDS )
//STRIP001  {
//STRIP001      // Im Format stand der Subtyp:
//STRIP001      nSubType = (USHORT)nNewFldFmt;
//STRIP001      nNewFldFmt = SVX_NUM_ARABIC;
//STRIP001  } else rPar.r >> nSubType;
//STRIP001  return new SwDocStatField( pType, nSubType, nNewFldFmt );
//STRIP001 }
//STRIP001
//STRIP001 static SwField* In_SwHiddenTxtField( SwSwgReader& rPar, SwHiddenTxtFieldType* pType )
//STRIP001 {
//STRIP001  BYTE cFlags;
//STRIP001  USHORT nSubType = TYP_HIDDENTXTFLD;
//STRIP001  rPar.r >> cFlags;
//STRIP001  String aText( rPar.GetText() );
//STRIP001  String aCond;
//STRIP001  aCond = rPar.GetText();
//STRIP001  if( rPar.aHdr.nVersion >= SWG_VER_FRAMES3 )
//STRIP001      rPar.r >> nSubType;
//STRIP001  BOOL bCond = BOOL( ( cFlags & 0x02 ) != 0 );
//STRIP001  BOOL bIsHidden = BOOL( ( cFlags & 0x01 ) != 0 );
//STRIP001
//STRIP001  if( rPar.aHdr.nVersion < SWG_VER_POOLIDS )
//STRIP001      bCond = BOOL( !bCond );
//STRIP001
//STRIP001  if( bCond && TYP_CONDTXTFLD != nSubType )
//STRIP001  {
//STRIP001 // steht im sw3field.cxx
//STRIP001 extern void lcl_sw3io_ChkHiddenExp( String& );
//STRIP001      lcl_sw3io_ChkHiddenExp( aCond );
//STRIP001      bIsHidden = !bIsHidden;
//STRIP001  }
//STRIP001
//STRIP001  SwHiddenTxtField* pFld = new SwHiddenTxtField( pType,
//STRIP001              bCond,
//STRIP001              aEmptyStr, aText,
//STRIP001              bIsHidden, nSubType );
//STRIP001  pFld->SetPar1( aCond );
//STRIP001  return pFld;
//STRIP001 }
//STRIP001
//STRIP001 static SwField* In_SwGetRefField( SwSwgReader& rPar, SwGetRefFieldType* pType )
//STRIP001 {
//STRIP001  String aName( rPar.GetText() );
//STRIP001  String aText( rPar.GetText( FALSE ) );
//STRIP001  SwGetRefField* pFld = new SwGetRefField( pType, aName, 0, 0, 0 );
//STRIP001  if( aText.Len() )
//STRIP001      pFld->SetExpand( aText );
//STRIP001  return pFld;
//STRIP001 }
//STRIP001
//STRIP001 static SwField* In_SwPostItField( SwSwgReader& rPar, SwPostItFieldType* pType )
//STRIP001 {
//STRIP001  ULONG nDate;
//STRIP001  rPar.r.long4();
//STRIP001  rPar.r >> nDate;
//STRIP001  rPar.r.long3();
//STRIP001  String aAuthor( rPar.GetText() );
//STRIP001  String aText( rPar.GetText() );
//STRIP001  return new SwPostItField( pType, aAuthor, aText, Date( nDate ) );
//STRIP001 }
//STRIP001
//STRIP001 static SwField* In_SwFixDateField( SwSwgReader& rPar, SwDateTimeFieldType* pType )
//STRIP001 {
//STRIP001  long nVal;
//STRIP001  rPar.r.long4();
//STRIP001  rPar.r >> nVal;
//STRIP001  rPar.r.long3();
//STRIP001  SwDateTimeField* pFld = new SwDateTimeField( pType, DATEFLD|FIXEDFLD );
//STRIP001     Time aTmpTime;
//STRIP001     Date aTmpDate(nVal);
//STRIP001     DateTime aDT(aTmpDate, aTmpTime);
//STRIP001     pFld->SetDateTime( aDT );
//STRIP001  return pFld;
//STRIP001 }
//STRIP001
//STRIP001 static SwField* In_SwFixTimeField( SwSwgReader& rPar, SwDateTimeFieldType* pType )
//STRIP001 {
//STRIP001  long nVal;
//STRIP001  rPar.r.long4();
//STRIP001  rPar.r >> nVal;
//STRIP001  rPar.r.long3();
//STRIP001  SwDateTimeField* pFld = new SwDateTimeField( pType );
//STRIP001     Date aTmpDate;
//STRIP001     DateTime aDT(aTmpDate, Time(nVal));
//STRIP001     pFld->SetDateTime( aDT );
//STRIP001  return pFld;
//STRIP001 }
//STRIP001
//STRIP001 /* MS: RegFields werden nicht mehr gebraucht
//STRIP001
//STRIP001 static SwField* In_SwRegField( SwSwgReader& rPar, SwRegFieldType* pType )
//STRIP001 {
//STRIP001  pType = In_SwRegFieldType( rPar );
//STRIP001  if( !pType ) return NULL;
//STRIP001  USHORT nType;
//STRIP001  rPar.r >> nType;
//STRIP001  return new SwRegField( pType, nType );
//STRIP001 }
//STRIP001
//STRIP001 static SwField* In_SwVarRegField( SwSwgReader& rPar, SwVarRegFieldType* pType )
//STRIP001 {
//STRIP001  pType = In_SwVarRegFieldType( rPar );
//STRIP001  return new SwVarRegField( pType );
//STRIP001 }
//STRIP001 */
//STRIP001
//STRIP001 static SwField* In_SwDDEField( SwSwgReader& rPar, SwDDEFieldType* pType )
//STRIP001 {
//STRIP001  pType = In_SwDDEFieldType( rPar );
//STRIP001  //JP 13.02.96: Bug 25321 - Felder ohne Namen nie einlesen
//STRIP001  if( !pType )
//STRIP001      return 0;
//STRIP001  return new SwDDEField( pType );
//STRIP001 }
//STRIP001
//STRIP001 static SwField* In_SwInputField( SwSwgReader& rPar, SwInputFieldType* pType )
//STRIP001 {
//STRIP001  SwInputField* pFld = new SwInputField( pType, aEmptyStr, aEmptyStr );
//STRIP001  // Prompt
//STRIP001  pFld->SetPar2( rPar.GetText() );
//STRIP001  // Content
//STRIP001  pFld->SetPar1( rPar.GetText() );
//STRIP001  USHORT nSubType;
//STRIP001
//STRIP001  if( rPar.aHdr.nVersion < SWG_VER_POOLIDS )
//STRIP001  {   // Im Format stand der Subtyp:
//STRIP001      nSubType   = (USHORT)nNewFldFmt & 0x03;
//STRIP001      nNewFldFmt = 0;
//STRIP001  }
//STRIP001  else
//STRIP001      rPar.r >> nSubType;
//STRIP001  pFld->SetSubType( nSubType );
//STRIP001  return pFld;
//STRIP001 }
//STRIP001
//STRIP001 static SwField* In_SwMacroField( SwSwgReader& rPar, SwMacroFieldType* pType )
//STRIP001 {
//STRIP001  String aName;
//STRIP001  String aText;
//STRIP001  if( rPar.aHdr.nVersion < SWG_VER_POOLIDS ) {
//STRIP001      aName = rPar.GetText();
//STRIP001      String aLib( rPar.GetText() );
//STRIP001      String aTmp(aLib);
//STRIP001      aTmp += ':';
//STRIP001      aTmp += aName;
//STRIP001      aName = aTmp;
//STRIP001  } else {
//STRIP001      aName = rPar.GetText();
//STRIP001      aText = rPar.GetText();
//STRIP001  }
//STRIP001  return new SwMacroField( pType, aName, aText );
//STRIP001 }
//STRIP001
//STRIP001 static SwField* In_SwTblField( SwSwgReader& rPar, SwTblFieldType* pType, USHORT nSub )
//STRIP001 {
//STRIP001  BYTE bInTbl; // wird ignoriert
//STRIP001  rPar.r >> bInTbl;
//STRIP001  String aFormel = rPar.GetText();
//STRIP001  String aTxt    = rPar.GetText( FALSE );
//STRIP001  SwTblField* pFld = new SwTblField( pType, aFormel );
//STRIP001  pFld->SetSubType(nSub);
//STRIP001  if( !bInTbl && aTxt.Len() )
//STRIP001      pFld->ChgExpStr( aTxt );
//STRIP001  return pFld;
//STRIP001 }
//STRIP001
//STRIP001 static SwField* In_SwGetExpField( SwSwgReader& rPar, SwGetExpFieldType* pType, USHORT nSub )
//STRIP001 {
//STRIP001  SwGetExpField* p = new SwGetExpField( pType, rPar.GetText() );
//STRIP001  USHORT nSubType = GSE_EXPR;
//STRIP001  if( rPar.aHdr.nVersion >= SWG_VER_POOLIDS )
//STRIP001  {
//STRIP001      String s = rPar.GetText();
//STRIP001      p->ChgExpStr( s );
//STRIP001      if( rPar.aHdr.nVersion >= SWG_VER_GETEXP )
//STRIP001          rPar.r >> nSubType;
//STRIP001  }
//STRIP001  else
//STRIP001  {   nSubType = (USHORT)nNewFldFmt & 3;
//STRIP001      nNewFldFmt &= ~3;
//STRIP001  }
//STRIP001  p->SetSubType(nSubType|nSub);
//STRIP001  if( GSE_STRING & nSubType )
//STRIP001      nNewFldFmt = 0;
//STRIP001
//STRIP001  // Falls sich das Feld in einem Shared-Format befindet,
//STRIP001  // mus es nach dem Lesen ge-updated werden
//STRIP001 //   if( rPar.nStatus & SWGSTAT_SHAREDFMT )
//STRIP001 //       rPar.nStatus |= SWGSTAT_UPDATEEXPR;
//STRIP001  return p;
//STRIP001 }
//STRIP001
//STRIP001 static SwField* In_SwSetExpField( SwSwgReader& rPar, SwSetExpFieldType* pType, USHORT nSub )
//STRIP001 {
//STRIP001  pType = In_SwSetExpFieldType( rPar );
//STRIP001  //JP 13.02.96: Bug 25321 - Felder ohne Namen nie einlesen
//STRIP001  if( !pType )
//STRIP001      return 0;
//STRIP001  BYTE cFlags;
//STRIP001  rPar.r >> cFlags;
//STRIP001  String aFrml( rPar.GetText() );
//STRIP001  SwSetExpField* pFld = new SwSetExpField( pType, aFrml, pType->GetType());
//STRIP001  if( cFlags & 0x02 )
//STRIP001      pFld->ChgExpStr( rPar.GetText() );
//STRIP001  if( cFlags & 0x01 )
//STRIP001      pFld->SetInputFlag(TRUE);
//STRIP001
//STRIP001  if( rPar.aHdr.nVersion < SWG_VER_POOLIDS )
//STRIP001  {
//STRIP001      USHORT nSubType = (USHORT)nNewFldFmt & 3;
//STRIP001      nNewFldFmt &= ~3;
//STRIP001      pFld->SetSubType( nSubType | (cFlags & 1 ) );
//STRIP001
//STRIP001      // bei alten Vars Anfuehrungsstriche entfernen
//STRIP001      if(nSubType & GSE_STRING)
//STRIP001      {
//STRIP001          aFrml = aFrml.Copy(1, aFrml.Len() - 2);
//STRIP001          pFld->ChgExpStr( aFrml );
//STRIP001          pFld->SetPar2( aFrml );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  aFrml = pFld->GetExpStr();
//STRIP001 //   pFld->SetValue( strtod( (const sal_Char*)aFrml, &dummy ) );
//STRIP001  // TODO: unicode: is this correct?
//STRIP001  pFld->SetValue( aFrml.ToDouble() );
//STRIP001
//STRIP001  // Hack: fuer Seq-Felder wurde das Original-Format im Subtyp uebergeben,
//STRIP001  // aber nur, wenn es auch als entsprechendes Format in Frage kommt.
//STRIP001  // (SUB_VISIBLE und SUB_CMD sind disjunkt).
//STRIP001  USHORT nSubType = ((SwSetExpField *)pFld)->GetSubType();
//STRIP001  if( nSub >= (USHORT)SVX_NUM_CHARS_UPPER_LETTER &&
//STRIP001      nSub <= (USHORT)SVX_NUM_BITMAP )
//STRIP001  {
//STRIP001      if( GSE_SEQ & nSubType )
//STRIP001          nNewFldFmt = nSub;
//STRIP001      nSub = 0;
//STRIP001  }
//STRIP001  nSubType |= nSub;
//STRIP001  pFld->SetSubType( nSubType );
//STRIP001  if( GSE_STRING & nSubType )
//STRIP001      nNewFldFmt = 0; // Warum auch immer
//STRIP001
//STRIP001  // neue Felder: Subtyp bereits im Feldtyp!
//STRIP001  // Falls sich das Feld in einem Shared-Format befindet,
//STRIP001  // mus es nach dem Lesen ge-updated werden
//STRIP001 //   if( rPar.nStatus & SWGSTAT_SHAREDFMT )
//STRIP001 //       rPar.nStatus |= SWGSTAT_UPDATEEXPR;
//STRIP001  return pFld;
//STRIP001 }
//STRIP001
//STRIP001 static SwField* In_SwHiddenParaField( SwSwgReader& rPar, SwHiddenParaFieldType* pType )
//STRIP001 {
//STRIP001  BYTE bHidden;
//STRIP001  rPar.r >> bHidden;
//STRIP001  String aCond( rPar.GetText() );
//STRIP001  SwHiddenParaField* pFld = new SwHiddenParaField( pType, aCond );
//STRIP001  pFld->SetHidden( (BOOL) bHidden );
//STRIP001  return pFld;
//STRIP001 }
//STRIP001
//STRIP001 static SwField* In_SwDocInfoField( SwSwgReader& rPar, SwDocInfoFieldType* pType,
//STRIP001                                 USHORT nSubType   )
//STRIP001 {
//STRIP001  BYTE nType;
//STRIP001  rPar.r >> nType;
//STRIP001  return new SwDocInfoField( pType, (USHORT)nType | nSubType );
//STRIP001 }
//STRIP001
//STRIP001 static SwField* In_SwTemplNameField( SwSwgReader& rPar, SwTemplNameFieldType* pType )
//STRIP001 {
//STRIP001  return new SwTemplNameField( pType, nNewFldFmt );
//STRIP001 }
//STRIP001
//STRIP001 static SwField* In_SwDBNextSetField( SwSwgReader& rPar, SwDBNextSetFieldType* pType )
//STRIP001 {
//STRIP001  String aCond(rPar.GetText());
//STRIP001  String aName(rPar.GetText());
//STRIP001  return new SwDBNextSetField( pType, aCond, aName, rPar.pDoc->GetDBData() );
//STRIP001 }
//STRIP001
//STRIP001 static SwField* In_SwDBNumSetField( SwSwgReader& rPar, SwDBNumSetFieldType* pType )
//STRIP001 {
//STRIP001  String aCond(rPar.GetText());
//STRIP001  String aPar2(rPar.GetText());
//STRIP001  return new SwDBNumSetField( pType, aCond, aPar2, rPar.pDoc->GetDBData());
//STRIP001 }
//STRIP001
//STRIP001 static SwField* In_SwDBSetNumberField( SwSwgReader& rPar, SwDBSetNumberFieldType* pType )
//STRIP001 {
//STRIP001  SwDBSetNumberField* pFld = new SwDBSetNumberField( pType, rPar.pDoc->GetDBData() );
//STRIP001  if( rPar.aHdr.nVersion >= SWG_VER_FRAMES3 )
//STRIP001  {
//STRIP001      long n;
//STRIP001      rPar.r.long4();
//STRIP001      rPar.r >> n;
//STRIP001      rPar.r.long3();
//STRIP001      pFld->SetSetNumber( n );
//STRIP001  }
//STRIP001  return pFld;
//STRIP001 }
//STRIP001
//STRIP001 static SwField* In_SwExtUserField( SwSwgReader& rPar, SwExtUserFieldType* pType )
//STRIP001 {
//STRIP001  String aData = rPar.GetText();
//STRIP001  USHORT nSubType;
//STRIP001  rPar.r >> nSubType;
//STRIP001
//STRIP001  SwExtUserField* pFld = new SwExtUserField( pType, nSubType );
//STRIP001  pType->SetData( aData );
//STRIP001  return pFld;
//STRIP001 }
//STRIP001
//STRIP001 /////////////////////////////////////////////////////////////////////////////
//STRIP001
//STRIP001 extern void sw3io_ConvertFromOldField( SwDoc& rDoc, USHORT& rWhich,
//STRIP001                                     USHORT& rSubType, ULONG &rFmt,
//STRIP001                                     USHORT nVersion );
//STRIP001
//STRIP001 SwField* SwSwgReader::InField()
//STRIP001 {
//STRIP001  long endfld = r.getskip();
//STRIP001  short nFld;
//STRIP001  USHORT nOldFldFmt;
//STRIP001  USHORT nSubType = 0;
//STRIP001
//STRIP001  r >> nFld >> nOldFldFmt;
//STRIP001  nNewFldFmt = nOldFldFmt;
//STRIP001
//STRIP001  if( nFld == -1 )
//STRIP001  {
//STRIP001      // war unbekanntes Feld, ignorieren
//STRIP001      r.skip(); return NULL;
//STRIP001  }
//STRIP001  nFld += RES_FIELDS_BEGIN;
//STRIP001
//STRIP001  UINT16 nRealWhich = nFld;
//STRIP001  sw3io_ConvertFromOldField( *pDoc, nRealWhich, nSubType, nNewFldFmt, 0 );
//STRIP001
//STRIP001  SwField* pFld = NULL;
//STRIP001  SwFieldType* pType = pDoc->GetSysFldType( (const RES_FIELDS) nRealWhich );
//STRIP001  switch( nFld )
//STRIP001  {
//STRIP001      case RES_DBFLD:
//STRIP001          pFld = In_SwDBField( *this, NULL, nSubType );
//STRIP001          break;
//STRIP001      case RES_USERFLD:
//STRIP001          pFld = In_SwUserField( *this, NULL, nSubType );
//STRIP001          break;
//STRIP001      case RES_FILENAMEFLD:
//STRIP001          pFld = In_SwFileNameField( *this, (SwFileNameFieldType*) pType );
//STRIP001          break;
//STRIP001      case RES_DBNAMEFLD:
//STRIP001          pFld = In_SwDBNameField( *this, (SwDBNameFieldType*) pType );
//STRIP001          break;
//STRIP001      case RES_DATEFLD:
//STRIP001          pFld = In_SwDateField( *this, (SwDateTimeFieldType*) pType );
//STRIP001          break;
//STRIP001      case RES_TIMEFLD:
//STRIP001          pFld = In_SwTimeField( *this, (SwDateTimeFieldType*) pType );
//STRIP001          break;
//STRIP001      case RES_PAGENUMBERFLD:
//STRIP001          pFld = In_SwPageNumberField( *this, (SwPageNumberFieldType*) pType );
//STRIP001          break;
//STRIP001      case RES_AUTHORFLD:
//STRIP001          pFld = In_SwAuthorField( *this, (SwAuthorFieldType*) pType );
//STRIP001          break;
//STRIP001      case RES_CHAPTERFLD:
//STRIP001          pFld = In_SwChapterField( *this, (SwChapterFieldType*) pType );
//STRIP001          break;
//STRIP001      case RES_DOCSTATFLD:
//STRIP001          pFld = In_SwDocStatField( *this, (SwDocStatFieldType*) pType );
//STRIP001          break;
//STRIP001      case RES_GETREFFLD:
//STRIP001          pFld = In_SwGetRefField( *this, (SwGetRefFieldType*) pType );
//STRIP001          break;
//STRIP001      case RES_HIDDENTXTFLD:
//STRIP001          pFld = In_SwHiddenTxtField( *this, (SwHiddenTxtFieldType*) pType );
//STRIP001          break;
//STRIP001      case RES_POSTITFLD:
//STRIP001          pFld = In_SwPostItField( *this, (SwPostItFieldType*) pType );
//STRIP001          break;
//STRIP001      case RES_FIXDATEFLD:
//STRIP001          pFld = In_SwFixDateField( *this, (SwDateTimeFieldType*) pType );
//STRIP001          break;
//STRIP001      case RES_FIXTIMEFLD:
//STRIP001          pFld = In_SwFixTimeField( *this, (SwDateTimeFieldType*) pType );
//STRIP001          break;
//STRIP001      /*
//STRIP001          MS: gibst nicht mehr
//STRIP001
//STRIP001      case RES_REGFLD:
//STRIP001          pFld = In_SwRegField( *this, NULL );
//STRIP001          break;
//STRIP001      case RES_VARREGFLD:
//STRIP001          pFld = In_SwVarRegField( *this, NULL );
//STRIP001          break;
//STRIP001      */
//STRIP001      case RES_DDEFLD:
//STRIP001          pFld = In_SwDDEField( *this, NULL );
//STRIP001          break;
//STRIP001      case RES_INPUTFLD:
//STRIP001          pFld = In_SwInputField( *this, (SwInputFieldType*) pType );
//STRIP001          break;
//STRIP001      case RES_MACROFLD:
//STRIP001          pFld = In_SwMacroField( *this, (SwMacroFieldType*) pType );
//STRIP001          break;
//STRIP001      case RES_TABLEFLD:
//STRIP001          pFld = In_SwTblField( *this, (SwTblFieldType*) pType, nSubType );
//STRIP001          break;
//STRIP001      case RES_GETEXPFLD:
//STRIP001          pFld = In_SwGetExpField( *this, (SwGetExpFieldType*) pType, nSubType );
//STRIP001          break;
//STRIP001      case RES_SETEXPFLD:
//STRIP001          pFld = In_SwSetExpField( *this, NULL, nSubType );
//STRIP001          break;
//STRIP001      case RES_HIDDENPARAFLD:
//STRIP001          pFld = In_SwHiddenParaField( *this, (SwHiddenParaFieldType*) pType );
//STRIP001          break;
//STRIP001      case RES_DOCINFOFLD:
//STRIP001          pFld = In_SwDocInfoField( *this, (SwDocInfoFieldType*) pType, nSubType );
//STRIP001          break;
//STRIP001      case RES_TEMPLNAMEFLD:
//STRIP001          pFld = In_SwTemplNameField( *this, (SwTemplNameFieldType*) pType );
//STRIP001          break;
//STRIP001      case RES_DBNEXTSETFLD:
//STRIP001          pFld = In_SwDBNextSetField( *this, (SwDBNextSetFieldType*) pType );
//STRIP001          break;
//STRIP001      case RES_DBNUMSETFLD:
//STRIP001          pFld = In_SwDBNumSetField( *this, (SwDBNumSetFieldType*) pType );
//STRIP001          break;
//STRIP001      case RES_DBSETNUMBERFLD:
//STRIP001          pFld = In_SwDBSetNumberField( *this, (SwDBSetNumberFieldType*) pType );
//STRIP001          break;
//STRIP001      case RES_EXTUSERFLD:
//STRIP001          pFld = In_SwExtUserField( *this, (SwExtUserFieldType*) pType );
//STRIP001          break;
//STRIP001  }
//STRIP001  r.skip( endfld );
//STRIP001
//STRIP001  if( !r )
//STRIP001      delete pFld, pFld = NULL;
//STRIP001  if( pFld )
//STRIP001      pFld->ChangeFormat( nNewFldFmt );
//STRIP001  return pFld;
//STRIP001 }
//STRIP001
//STRIP001 // Einlesen aller Feldtypen, die keine Systemtypen sind
//STRIP001
//STRIP001 void SwSwgReader::InFieldTypes()
//STRIP001 {
//STRIP001  USHORT nFields;
//STRIP001  r >> nFields;
//STRIP001  for( USHORT i = 0; i < nFields && r.good(); i++ )
//STRIP001  {
//STRIP001      if( aHdr.nVersion >= SWG_VER_POOLIDS )
//STRIP001      {
//STRIP001          if( r.next() != SWG_DATA )
//STRIP001          {
//STRIP001              Error(); break;
//STRIP001          }
//STRIP001          long nextrec = r.getskip();
//STRIP001          InFieldType();
//STRIP001          r.skip( nextrec );
//STRIP001      } else InFieldType();
//STRIP001  }
//STRIP001  if( r.good() )
//STRIP001      r.next();
//STRIP001 }

//STRIP001 SwFieldType* SwSwgReader::InFieldType()
//STRIP001 {
//STRIP001  BYTE ch;
//STRIP001  SwFieldType* p = NULL;
//STRIP001  r >> ch;
//STRIP001  ch += RES_FIELDS_BEGIN;
//STRIP001  switch( ch )
//STRIP001  {
//STRIP001      case RES_DBFLD:
//STRIP001          p = In_SwDBFieldType( *this ); break;
//STRIP001      case RES_USERFLD:
//STRIP001          p = In_SwUserFieldType( *this ); break;
//STRIP001      /*
//STRIP001          MS: Gibts nicht mehr
//STRIP001
//STRIP001      case RES_REGFLD:
//STRIP001          p = In_SwRegFieldType( *this ); break;
//STRIP001      case RES_VARREGFLD:
//STRIP001          p = In_SwVarRegFieldType( *this ); break;
//STRIP001      */
//STRIP001      case RES_DDEFLD:
//STRIP001          p = In_SwDDEFieldType( *this ); break;
//STRIP001      case RES_SETEXPFLD:
//STRIP001          p = In_SwSetExpFieldType( *this ); break;
//STRIP001  }
//STRIP001  return p;
//STRIP001 }



}
