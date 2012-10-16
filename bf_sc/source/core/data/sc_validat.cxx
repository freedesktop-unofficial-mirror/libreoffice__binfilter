/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */

#ifdef _MSC_VER
#pragma hdrstop
#endif




#include <math.h>


#include "validat.hxx"
#include "patattr.hxx"
#include "rechead.hxx"
#include "globstr.hrc"
namespace binfilter {

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
/*N*/   aInputTitle = rStream.ReadUniOrByteString( rStream.GetStreamCharSet() );
/*N*/   aInputMessage = rStream.ReadUniOrByteString( rStream.GetStreamCharSet() );
/*N*/   rStream >> bShowError;
/*N*/   aErrorTitle = rStream.ReadUniOrByteString( rStream.GetStreamCharSet() );
/*N*/   aErrorMessage = rStream.ReadUniOrByteString( rStream.GetStreamCharSet() );
/*N*/   rStream >> nDummy;
/*N*/   eErrorStyle = (ScValidErrorStyle) nDummy;
/*N*/
/*N*/   rHdr.EndEntry();
/*N*/ }

/*N*/ ScValidationData::~ScValidationData()
/*N*/ {
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

//------------------------------------------------------------------------

/*N*/ ScValidationDataList::ScValidationDataList(const ScValidationDataList& rList)
/*N*/     : ScValidationEntries_Impl()
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

/*N*/ ScValidationData* ScValidationDataList::GetData( sal_uInt32 nKey )
/*N*/ {
/*N*/   //! binaer suchen
/*N*/
/*N*/   USHORT nCount = Count();
/*N*/   for (USHORT i=0; i<nCount; i++)
/*N*/       if ((*this)[i]->GetKey() == nKey)
/*N*/           return (*this)[i];
/*N*/
/*N*/   OSL_FAIL("ScValidationDataList: Eintrag nicht gefunden");
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

/*N*/ void ScValidationDataList::CompileXML()
/*N*/ {
/*N*/   USHORT nCount = Count();
/*N*/   for (USHORT i=0; i<nCount; i++)
/*N*/       (*this)[i]->CompileXML();
/*N*/ }
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
