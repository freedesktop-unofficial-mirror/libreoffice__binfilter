/*************************************************************************
 *
 *  $RCSfile: sc_validat.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 14:36:19 $
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

// INCLUDE ---------------------------------------------------------------

#include "scitems.hxx"
#include <bf_sfx2/app.hxx>
#include <bf_sfx2/docfile.hxx>
#include <bf_sfx2/objsh.hxx>
#include <basic/sbmeth.hxx>
#include <basic/sbmod.hxx>
#include <basic/sbstar.hxx>

#ifndef _BASMGR_HXX //autogen
#include <basic/basmgr.hxx>
#endif

#include <svtools/sbx.hxx>
#include <svtools/zforlist.hxx>
#include <vcl/msgbox.hxx>
#include <tools/urlobj.hxx>
#include <rtl/math.hxx>
#include <math.h>


#include "validat.hxx"
#include "document.hxx"
#include "cell.hxx"
#include "patattr.hxx"
#include "rechead.hxx"
#include "globstr.hrc"

//------------------------------------------------------------------------

/*N*/ SV_IMPL_OP_PTRARR_SORT( ScValidationEntries_Impl, ScValidationDataPtr );

//------------------------------------------------------------------------

//
//  Eintrag fuer Gueltigkeit (es gibt nur eine Bedingung)
//

/*N*/ ScValidationData::ScValidationData( ScValidationMode eMode, ScConditionMode eOper,
/*N*/                           const String& rExpr1, const String& rExpr2,
/*N*/                           ScDocument* pDocument, const ScAddress& rPos,
/*N*/                           BOOL bCompileEnglish, BOOL bCompileXML ) :
/*N*/   ScConditionEntry( eOper, rExpr1, rExpr2, pDocument, rPos, bCompileEnglish, bCompileXML ),
/*N*/   nKey( 0 ),
/*N*/   eDataMode( eMode )
/*N*/ {
/*N*/   bShowInput = bShowError = FALSE;
/*N*/   eErrorStyle = SC_VALERR_STOP;
/*N*/ }

/*N*/ ScValidationData::ScValidationData( ScValidationMode eMode, ScConditionMode eOper,
/*N*/                           const ScTokenArray* pArr1, const ScTokenArray* pArr2,
/*N*/                           ScDocument* pDocument, const ScAddress& rPos ) :
/*N*/   ScConditionEntry( eOper, pArr1, pArr2, pDocument, rPos ),
/*N*/   nKey( 0 ),
/*N*/   eDataMode( eMode )
/*N*/ {
/*N*/   bShowInput = bShowError = FALSE;
/*N*/   eErrorStyle = SC_VALERR_STOP;
/*N*/ }

/*N*/ ScValidationData::ScValidationData( const ScValidationData& r ) :
/*N*/   ScConditionEntry( r ),
/*N*/   nKey( r.nKey ),
/*N*/   eDataMode( r.eDataMode ),
/*N*/   bShowInput( r.bShowInput ),
/*N*/   bShowError( r.bShowError ),
/*N*/   eErrorStyle( r.eErrorStyle ),
/*N*/   aInputTitle( r.aInputTitle ),
/*N*/   aInputMessage( r.aInputMessage ),
/*N*/   aErrorTitle( r.aErrorTitle ),
/*N*/   aErrorMessage( r.aErrorMessage )
/*N*/ {
/*N*/   //  Formeln per RefCount kopiert
/*N*/ }

/*N*/ ScValidationData::ScValidationData( ScDocument* pDocument, const ScValidationData& r ) :
/*N*/   ScConditionEntry( pDocument, r ),
/*N*/   nKey( r.nKey ),
/*N*/   eDataMode( r.eDataMode ),
/*N*/   bShowInput( r.bShowInput ),
/*N*/   bShowError( r.bShowError ),
/*N*/   eErrorStyle( r.eErrorStyle ),
/*N*/   aInputTitle( r.aInputTitle ),
/*N*/   aInputMessage( r.aInputMessage ),
/*N*/   aErrorTitle( r.aErrorTitle ),
/*N*/   aErrorMessage( r.aErrorMessage )
/*N*/ {
/*N*/   //  Formeln wirklich kopiert
/*N*/ }

/*N*/ ScValidationData::ScValidationData( SvStream& rStream, ScMultipleReadHeader& rHdr,
/*N*/                                   ScDocument* pDocument ) :
/*N*/   ScConditionEntry( rStream, rHdr, pDocument )
/*N*/ {
/*N*/   //  im Datei-Header sind getrennte Eintraege fuer ScConditionEntry und ScValidationData
/*N*/
/*N*/   rHdr.StartEntry();
/*N*/
/*N*/   //  1) Key
/*N*/   //  2) eDataMode
/*N*/   //  3) bShowInput
/*N*/   //  4) aInputTitle
/*N*/   //  5) aInputMessage
/*N*/   //  6) bShowError
/*N*/   //  7) aErrorTitle
/*N*/   //  8) aErrorMessage
/*N*/   //  9) eErrorStyle
/*N*/
/*N*/   USHORT nDummy;
/*N*/   rStream >> nKey;
/*N*/   rStream >> nDummy;
/*N*/   eDataMode = (ScValidationMode) nDummy;
/*N*/   rStream >> bShowInput;
/*N*/   rStream.ReadByteString( aInputTitle, rStream.GetStreamCharSet() );
/*N*/   rStream.ReadByteString( aInputMessage, rStream.GetStreamCharSet() );
/*N*/   rStream >> bShowError;
/*N*/   rStream.ReadByteString( aErrorTitle, rStream.GetStreamCharSet() );
/*N*/   rStream.ReadByteString( aErrorMessage, rStream.GetStreamCharSet() );
/*N*/   rStream >> nDummy;
/*N*/   eErrorStyle = (ScValidErrorStyle) nDummy;
/*N*/
/*N*/   rHdr.EndEntry();
/*N*/ }

/*N*/ ScValidationData::~ScValidationData()
/*N*/ {
/*N*/ }

/*N*/ void ScValidationData::Store(SvStream& rStream, ScMultipleWriteHeader& rHdr) const
/*N*/ {
/*N*/   //  im Datei-Header sind getrennte Eintraege fuer ScConditionEntry und ScValidationData
/*N*/
/*N*/   StoreCondition( rStream, rHdr );
/*N*/
/*N*/   rHdr.StartEntry();
/*N*/
/*N*/   //  1) Key
/*N*/   //  2) eDataMode
/*N*/   //  3) bShowInput
/*N*/   //  4) aInputTitle
/*N*/   //  5) aInputMessage
/*N*/   //  6) bShowError
/*N*/   //  7) aErrorTitle
/*N*/   //  8) aErrorMessage
/*N*/   //  9) eErrorStyle
/*N*/
/*N*/   rStream << nKey;
/*N*/   rStream << (USHORT) eDataMode;
/*N*/   rStream << bShowInput;
/*N*/   rStream.WriteByteString( aInputTitle, rStream.GetStreamCharSet() );
/*N*/   rStream.WriteByteString( aInputMessage, rStream.GetStreamCharSet() );
/*N*/   rStream << bShowError;
/*N*/   rStream.WriteByteString( aErrorTitle, rStream.GetStreamCharSet() );
/*N*/   rStream.WriteByteString( aErrorMessage, rStream.GetStreamCharSet() );
/*N*/   rStream << (USHORT) eErrorStyle;
/*N*/
/*N*/   rHdr.EndEntry();
/*N*/ }

/*N*/ BOOL ScValidationData::IsEmpty() const
/*N*/ {
/*N*/   String aEmpty;
/*N*/   ScValidationData aDefault( SC_VALID_ANY, SC_COND_EQUAL, aEmpty, aEmpty, GetDocument(), ScAddress() );
/*N*/   return EqualEntries( aDefault );
/*N*/ }

/*N*/ BOOL ScValidationData::EqualEntries( const ScValidationData& r ) const
/*N*/ {
/*N*/       //  gleiche Parameter eingestellt (ohne Key)
/*N*/
/*N*/   return ScConditionEntry::operator==(r) &&
/*N*/           eDataMode       == r.eDataMode &&
/*N*/           bShowInput      == r.bShowInput &&
/*N*/           bShowError      == r.bShowError &&
/*N*/           eErrorStyle     == r.eErrorStyle &&
/*N*/           aInputTitle     == r.aInputTitle &&
/*N*/           aInputMessage   == r.aInputMessage &&
/*N*/           aErrorTitle     == r.aErrorTitle &&
/*N*/           aErrorMessage   == r.aErrorMessage;
/*N*/ }

/*N*/ void ScValidationData::ResetInput()
/*N*/ {
/*N*/   bShowInput = FALSE;
/*N*/ }

/*N*/ void ScValidationData::ResetError()
/*N*/ {
/*N*/   bShowError = FALSE;
/*N*/ }

/*N*/ void ScValidationData::SetInput( const String& rTitle, const String& rMsg )
/*N*/ {
/*N*/   bShowInput = TRUE;
/*N*/   aInputTitle = rTitle;
/*N*/   aInputMessage = rMsg;
/*N*/ }

/*N*/ void ScValidationData::SetError( const String& rTitle, const String& rMsg,
/*N*/                                   ScValidErrorStyle eStyle )
/*N*/ {
/*N*/   bShowError = TRUE;
/*N*/   eErrorStyle = eStyle;
/*N*/   aErrorTitle = rTitle;
/*N*/   aErrorMessage = rMsg;
/*N*/ }

/*N*/ BOOL ScValidationData::GetErrMsg( String& rTitle, String& rMsg,
/*N*/                                   ScValidErrorStyle& rStyle ) const
/*N*/ {
/*N*/   rTitle = aErrorTitle;
/*N*/   rMsg   = aErrorMessage;
/*N*/   rStyle = eErrorStyle;
/*N*/   return bShowError;
/*N*/ }

    // TRUE -> Abbruch

//STRIP001 BOOL ScValidationData::DoMacro( const ScAddress& rPos, const String& rInput,
//STRIP001                              ScFormulaCell* pCell, Window* pParent ) const
//STRIP001 {
//STRIP001  ScDocument* pDocument = GetDocument();
//STRIP001  SfxObjectShell* pDocSh = pDocument->GetDocumentShell();
//STRIP001  if ( !pDocSh || !pDocument->CheckMacroWarn() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  BOOL bDone = FALSE;
//STRIP001  BOOL bRet = FALSE;                      // Standard: kein Abbruch
//STRIP001  SfxApplication* pSfxApp = SFX_APP();
//STRIP001  pSfxApp->EnterBasicCall();              // Dok-Basic anlegen etc.
//STRIP001
//STRIP001  //  Wenn das Dok waehrend eines Basic-Calls geladen wurde,
//STRIP001  //  ist das Sbx-Objekt evtl. nicht angelegt (?)
//STRIP001 //   pDocSh->GetSbxObject();
//STRIP001
//STRIP001  //  keine Sicherheitsabfrage mehr vorneweg (nur CheckMacroWarn), das passiert im CallBasic
//STRIP001
//STRIP001 #if 0
//STRIP001  // Makro-Name liegt in folgender Form vor:
//STRIP001  // "Macroname.Modulname.Libname.Dokumentname" oder
//STRIP001  // "Macroname.Modulname.Libname.Applikationsname"
//STRIP001  String aMacroName = aErrorTitle.GetToken(0, '.');
//STRIP001  String aModulName = aErrorTitle.GetToken(1, '.');
//STRIP001  String aLibName   = aErrorTitle.GetToken(2, '.');
//STRIP001  String aDocName   = aErrorTitle.GetToken(3, '.');
//STRIP001 #endif
//STRIP001
//STRIP001  //  Funktion ueber den einfachen Namen suchen,
//STRIP001  //  dann aBasicStr, aMacroStr fuer SfxObjectShell::CallBasic zusammenbauen
//STRIP001
//STRIP001  StarBASIC* pRoot = pDocSh->GetBasic();
//STRIP001  SbxVariable* pVar = pRoot->Find( aErrorTitle, SbxCLASS_METHOD );
//STRIP001  if ( pVar && pVar->ISA(SbMethod) )
//STRIP001  {
//STRIP001      SbMethod* pMethod = (SbMethod*)pVar;
//STRIP001      SbModule* pModule = pMethod->GetModule();
//STRIP001      SbxObject* pObject = pModule->GetParent();
//STRIP001      StarBASIC* pBasic = PTR_CAST(StarBASIC,pObject);
//STRIP001      DBG_ASSERT(pBasic, "Kein Basic gefunden!");
//STRIP001      String aMacroStr = pObject->GetName();
//STRIP001      aMacroStr += '.';
//STRIP001      aMacroStr += pModule->GetName();
//STRIP001      aMacroStr += '.';
//STRIP001      aMacroStr += pMethod->GetName();
//STRIP001      String aBasicStr;
//STRIP001
//STRIP001      //  #95867# the distinction between document- and app-basic has to be done
//STRIP001      //  by checking the parent (as in ScInterpreter::ScMacro), not by looping
//STRIP001      //  over all open documents, because this may be called from within loading,
//STRIP001      //  when SfxObjectShell::GetFirst/GetNext won't find the document.
//STRIP001
//STRIP001      if ( pObject->GetParent() )
//STRIP001          aBasicStr = pObject->GetParent()->GetName();    // Dokumentenbasic
//STRIP001      else
//STRIP001          aBasicStr = SFX_APP()->GetName();               // Applikationsbasic
//STRIP001
//STRIP001      //  Parameter fuer Makro
//STRIP001      SbxArrayRef refPar = new SbxArray;
//STRIP001
//STRIP001      //  1) eingegebener / berechneter Wert
//STRIP001      String aValStr = rInput;
//STRIP001      double nValue;
//STRIP001      BOOL bIsValue = FALSE;
//STRIP001      if ( pCell )                // wenn Zelle gesetzt, aus Interpret gerufen
//STRIP001      {
//STRIP001          bIsValue = pCell->IsValue();
//STRIP001          if ( bIsValue )
//STRIP001              nValue  = pCell->GetValue();
//STRIP001          else
//STRIP001              pCell->GetString( aValStr );
//STRIP001      }
//STRIP001      if ( bIsValue )
//STRIP001          refPar->Get(1)->PutDouble( nValue );
//STRIP001      else
//STRIP001          refPar->Get(1)->PutString( aValStr );
//STRIP001
//STRIP001      //  2) Position der Zelle
//STRIP001      String aPosStr;
//STRIP001      rPos.Format( aPosStr, SCA_VALID | SCA_TAB_3D, pDocument );
//STRIP001      refPar->Get(2)->PutString( aPosStr );
//STRIP001
//STRIP001      //  use link-update flag to prevent closing the document
//STRIP001      //  while the macro is running
//STRIP001      BOOL bWasInLinkUpdate = pDocument->IsInLinkUpdate();
//STRIP001      if ( !bWasInLinkUpdate )
//STRIP001          pDocument->SetInLinkUpdate( TRUE );
//STRIP001
//STRIP001      if ( pCell )
//STRIP001          pDocument->LockTable( rPos.Tab() );
//STRIP001      SbxVariableRef refRes = new SbxVariable;
//STRIP001      ErrCode eRet = pDocSh->CallBasic( aMacroStr, aBasicStr, NULL, refPar, refRes );
//STRIP001      if ( pCell )
//STRIP001          pDocument->UnlockTable( rPos.Tab() );
//STRIP001
//STRIP001      if ( !bWasInLinkUpdate )
//STRIP001          pDocument->SetInLinkUpdate( FALSE );
//STRIP001
//STRIP001      //  Eingabe abbrechen, wenn Basic-Makro FALSE zurueckgibt
//STRIP001      if ( eRet == ERRCODE_NONE && refRes->GetType() == SbxBOOL && refRes->GetBool() == FALSE )
//STRIP001          bRet = TRUE;
//STRIP001      bDone = TRUE;
//STRIP001  }
//STRIP001  pSfxApp->LeaveBasicCall();
//STRIP001
//STRIP001  if ( !bDone && !pCell )         // Makro nicht gefunden (nur bei Eingabe)
//STRIP001  {
//STRIP001      //! andere Fehlermeldung, wenn gefunden, aber nicht bAllowed ??
//STRIP001
//STRIP001      ErrorBox aBox( pParent, WinBits(WB_OK),
//STRIP001                      ScGlobal::GetRscString( STR_VALID_MACRONOTFOUND ) );
//STRIP001      aBox.Execute();
//STRIP001  }
//STRIP001
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 void ScValidationData::DoCalcError( ScFormulaCell* pCell ) const
//STRIP001 {
//STRIP001  if ( eErrorStyle == SC_VALERR_MACRO )
//STRIP001      DoMacro( pCell->aPos, EMPTY_STRING, pCell, NULL );
//STRIP001 }

    // TRUE -> Abbruch

//STRIP001 BOOL ScValidationData::DoError( Window* pParent, const String& rInput,
//STRIP001                              const ScAddress& rPos ) const
//STRIP001 {
//STRIP001  if ( eErrorStyle == SC_VALERR_MACRO )
//STRIP001      return DoMacro( rPos, rInput, NULL, pParent );
//STRIP001
//STRIP001  //  Fehlermeldung ausgeben
//STRIP001
//STRIP001  String aTitle = aErrorTitle;
//STRIP001  if (!aTitle.Len())
//STRIP001      aTitle = ScGlobal::GetRscString( STR_MSSG_DOSUBTOTALS_0 );  // application title
//STRIP001  String aMessage = aErrorMessage;
//STRIP001  if (!aMessage.Len())
//STRIP001      aMessage = ScGlobal::GetRscString( STR_VALID_DEFERROR );
//STRIP001
//STRIP001  //! ErrorBox / WarningBox / InfoBox ?
//STRIP001  //! (bei InfoBox immer nur OK-Button)
//STRIP001
//STRIP001  WinBits nStyle = 0;
//STRIP001  switch (eErrorStyle)
//STRIP001  {
//STRIP001      case SC_VALERR_STOP:
//STRIP001          nStyle = WB_OK | WB_DEF_OK;
//STRIP001          break;
//STRIP001      case SC_VALERR_WARNING:
//STRIP001          nStyle = WB_OK_CANCEL | WB_DEF_CANCEL;
//STRIP001          break;
//STRIP001      case SC_VALERR_INFO:
//STRIP001          nStyle = WB_OK_CANCEL | WB_DEF_OK;
//STRIP001          break;
//STRIP001  }
//STRIP001
//STRIP001  MessBox aBox( pParent, WinBits(nStyle), aTitle, aMessage );
//STRIP001  USHORT nRet = aBox.Execute();
//STRIP001
//STRIP001  return ( eErrorStyle == SC_VALERR_STOP || nRet == RET_CANCEL );
//STRIP001 }


/*N*/ BOOL ScValidationData::IsDataValid( const String& rTest, const ScPatternAttr& rPattern,
/*N*/                                   const ScAddress& rPos ) const
/*N*/ {
DBG_ASSERT(0, "STRIP"); //STRIP001  if ( eDataMode == SC_VALID_ANY )
//STRIP001      return TRUE;                        // alles erlaubt
//STRIP001
//STRIP001  if ( rTest.GetChar(0) == '=' )
//STRIP001      return FALSE;                       // Formeln sind sonst immer ungueltig
//STRIP001
//STRIP001  if ( !rTest.Len() )
//STRIP001      return IsIgnoreBlank();             // leer: wie eingestellt
//STRIP001
//STRIP001  SvNumberFormatter* pFormatter = GetDocument()->GetFormatTable();
//STRIP001
//STRIP001  //  Test, was es denn ist - wie in ScColumn::SetString
//STRIP001
//STRIP001  ULONG nFormat = rPattern.GetNumberFormat( pFormatter );
//STRIP001
//STRIP001  double nVal;
//STRIP001  BOOL bIsVal = pFormatter->IsNumberFormat( rTest, nFormat, nVal );
//STRIP001  ScBaseCell* pCell;
//STRIP001  if (bIsVal)
//STRIP001      pCell = new ScValueCell( nVal );
//STRIP001  else
//STRIP001      pCell = new ScStringCell( rTest );
//STRIP001
//STRIP001  BOOL bRet = IsDataValid( pCell, rPos );
//STRIP001
//STRIP001  pCell->Delete();
return FALSE;//STRIP001     return bRet;
/*N*/ }

/*N*/ BOOL ScValidationData::IsDataValid( ScBaseCell* pCell, const ScAddress& rPos ) const
/*N*/ {
/*?*/   DBG_ASSERT(0, "STRIP"); return FALSE; //STRIP001 double nVal = 0.0;
//STRIP001  String aString;
//STRIP001  BOOL bIsVal = TRUE;
//STRIP001
//STRIP001  switch (pCell->GetCellType())
//STRIP001  {
//STRIP001      case CELLTYPE_VALUE:
//STRIP001          nVal = ((ScValueCell*)pCell)->GetValue();
//STRIP001          break;
//STRIP001      case CELLTYPE_STRING:
//STRIP001          ((ScStringCell*)pCell)->GetString( aString );
//STRIP001          bIsVal = FALSE;
//STRIP001          break;
//STRIP001      case CELLTYPE_EDIT:
//STRIP001          ((ScEditCell*)pCell)->GetString( aString );
//STRIP001          bIsVal = FALSE;
//STRIP001          break;
//STRIP001      case CELLTYPE_FORMULA:
//STRIP001          {
//STRIP001              ScFormulaCell* pFCell = (ScFormulaCell*)pCell;
//STRIP001              bIsVal = pFCell->IsValue();
//STRIP001              if ( bIsVal )
//STRIP001                  nVal  = pFCell->GetValue();
//STRIP001              else
//STRIP001                  pFCell->GetString( aString );
//STRIP001          }
//STRIP001          break;
//STRIP001      default:                        // Notizen, Broadcaster
//STRIP001          return IsIgnoreBlank();     // wie eingestellt
//STRIP001  }
//STRIP001
//STRIP001  BOOL bOk = TRUE;
//STRIP001  switch (eDataMode)
//STRIP001  {
//STRIP001      // SC_VALID_ANY schon oben
//STRIP001
//STRIP001      case SC_VALID_WHOLE:
//STRIP001      case SC_VALID_DECIMAL:
//STRIP001      case SC_VALID_DATE:         // Date/Time ist nur Formatierung
//STRIP001      case SC_VALID_TIME:
//STRIP001          bOk = bIsVal;
//STRIP001          if ( bOk && eDataMode == SC_VALID_WHOLE )
//STRIP001              bOk = ::rtl::math::approxEqual( nVal, floor(nVal+0.5) );        // ganze Zahlen
//STRIP001          if ( bOk )
//STRIP001              bOk = IsCellValid( pCell, rPos );
//STRIP001          break;
//STRIP001
//STRIP001      case SC_VALID_CUSTOM:
//STRIP001          //  fuer Custom muss eOp == SC_COND_DIRECT sein
//STRIP001          //! der Wert muss im Dokument stehen !!!!!!!!!!!!!!!!!!!!
//STRIP001          bOk = IsCellValid( pCell, rPos );
//STRIP001          break;
//STRIP001
//STRIP001      case SC_VALID_TEXTLEN:
//STRIP001          bOk = !bIsVal;          // nur Text
//STRIP001          if ( bOk )
//STRIP001          {
//STRIP001              double nLenVal = (double) aString.Len();
//STRIP001              ScValueCell aTmpCell( nLenVal );
//STRIP001              bOk = IsCellValid( &aTmpCell, rPos );
//STRIP001          }
//STRIP001          break;
//STRIP001
//STRIP001      case SC_VALID_LIST:
//STRIP001      default:
//STRIP001          DBG_ERROR("hammanochnich");
//STRIP001          break;
//STRIP001  }
//STRIP001
//STRIP001  return bOk;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ ScValidationDataList::ScValidationDataList(const ScValidationDataList& rList)
/*N*/ {
/*N*/   //  fuer Ref-Undo - echte Kopie mit neuen Tokens!
/*N*/
/*N*/   USHORT nCount = rList.Count();
/*N*/
/*N*/   for (USHORT i=0; i<nCount; i++)
/*N*/       InsertNew( rList[i]->Clone() );
/*N*/
/*N*/   //!     sortierte Eintraege aus rList schneller einfuegen ???
/*N*/ }

/*N*/ ScValidationDataList::ScValidationDataList(ScDocument* pNewDoc,
/*N*/                                           const ScValidationDataList& rList)
/*N*/ {
/*N*/   //  fuer neues Dokument - echte Kopie mit neuen Tokens!
/*N*/
/*N*/   USHORT nCount = rList.Count();
/*N*/
/*N*/   for (USHORT i=0; i<nCount; i++)
/*N*/       InsertNew( rList[i]->Clone(pNewDoc) );
/*N*/
/*N*/   //!     sortierte Eintraege aus rList schneller einfuegen ???
/*N*/ }

/*N*/ ScValidationData* ScValidationDataList::GetData( ULONG nKey )
/*N*/ {
/*N*/   //! binaer suchen
/*N*/
/*N*/   USHORT nCount = Count();
/*N*/   for (USHORT i=0; i<nCount; i++)
/*N*/       if ((*this)[i]->GetKey() == nKey)
/*N*/           return (*this)[i];
/*N*/
/*N*/   DBG_ERROR("ScValidationDataList: Eintrag nicht gefunden");
/*N*/   return NULL;
/*N*/ }

/*N*/ void ScValidationDataList::Load( SvStream& rStream, ScDocument* pDocument )
/*N*/ {
/*N*/   ScMultipleReadHeader aHdr( rStream );
/*N*/
/*N*/   USHORT nNewCount;
/*N*/   rStream >> nNewCount;
/*N*/
/*N*/   for (USHORT i=0; i<nNewCount; i++)
/*N*/   {
/*N*/       ScValidationData* pNew = new ScValidationData( rStream, aHdr, pDocument );
/*N*/       InsertNew( pNew );
/*N*/   }
/*N*/ }

/*N*/ void ScValidationDataList::Store( SvStream& rStream ) const
/*N*/ {
/*N*/   USHORT i;
/*N*/   ScMultipleWriteHeader aHdr( rStream );
/*N*/
/*N*/   USHORT nCount = Count();
/*N*/   USHORT nUsed = 0;
/*N*/   for (i=0; i<nCount; i++)
/*N*/       if ((*this)[i]->IsUsed())
/*N*/           ++nUsed;
/*N*/
/*N*/   rStream << nUsed;       // Anzahl der gespeicherten
/*N*/
/*N*/   for (i=0; i<nCount; i++)
/*N*/   {
/*N*/       const ScValidationData* pForm = (*this)[i];
/*N*/       if (pForm->IsUsed())
/*N*/           pForm->Store( rStream, aHdr );
/*N*/   }
/*N*/ }

/*N*/ void ScValidationDataList::ResetUsed()
/*N*/ {
/*N*/   USHORT nCount = Count();
/*N*/   for (USHORT i=0; i<nCount; i++)
/*N*/       (*this)[i]->SetUsed(FALSE);
/*N*/ }

/*N*/ void ScValidationDataList::CompileXML()
/*N*/ {
/*N*/   USHORT nCount = Count();
/*N*/   for (USHORT i=0; i<nCount; i++)
/*N*/       (*this)[i]->CompileXML();
/*N*/ }

//STRIP001 void ScValidationDataList::UpdateReference( UpdateRefMode eUpdateRefMode,
//STRIP001                              const ScRange& rRange, short nDx, short nDy, short nDz )
//STRIP001 {
//STRIP001  DBG_ERROR("ScValidationDataList::UpdateReference");
//STRIP001 }

//STRIP001 BOOL ScValidationDataList::operator==( const ScValidationDataList& r ) const
//STRIP001 {
//STRIP001  // fuer Ref-Undo - interne Variablen werden nicht verglichen
//STRIP001
//STRIP001  USHORT nCount = Count();
//STRIP001  BOOL bEqual = ( nCount == r.Count() );
//STRIP001  for (USHORT i=0; i<nCount && bEqual; i++)           // Eintraege sind sortiert
//STRIP001      if ( !(*this)[i]->EqualEntries(*r[i]) )         // Eintraege unterschiedlich ?
//STRIP001          bEqual = FALSE;
//STRIP001
//STRIP001  return bEqual;
//STRIP001 }




