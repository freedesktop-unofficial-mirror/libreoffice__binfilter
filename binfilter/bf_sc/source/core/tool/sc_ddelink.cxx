/*************************************************************************
 *
 *  $RCSfile: sc_ddelink.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 14:43:04 $
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

#ifndef _LIST_HXX //autogen
#include <tools/list.hxx>
#endif
#include <bf_svx/linkmgr.hxx>
#include <bf_sfx2/bindings.hxx>
#include <svtools/zforlist.hxx>

#include "ddelink.hxx"
#include "brdcst.hxx"
#include "document.hxx"
#include "scmatrix.hxx"
#include "patattr.hxx"
#include "rechead.hxx"
#include "rangeseq.hxx"
#include "bf_sc.hrc"
#include "hints.hxx"

/*N*/ TYPEINIT2(ScDdeLink,::so3::SvBaseLink,SfxBroadcaster);

#ifdef PM2
#define DDE_TXT_ENCODING    RTL_TEXTENCODING_IBM_850
#else
#define DDE_TXT_ENCODING    RTL_TEXTENCODING_MS_1252
#endif

/*N*/ BOOL ScDdeLink::bIsInUpdate = FALSE;

//------------------------------------------------------------------------

/*N*/ ScDdeLink::ScDdeLink( ScDocument* pD, const String& rA, const String& rT, const String& rI,
/*N*/                       BYTE nM ) :
/*N*/   ::so3::SvBaseLink(so3::LINKUPDATE_ALWAYS,FORMAT_STRING),
/*N*/   pDoc( pD ),
/*N*/   aAppl( rA ),
/*N*/   aTopic( rT ),
/*N*/   aItem( rI ),
/*N*/   nMode( nM ),
/*N*/   pResult( NULL ),
/*N*/   bNeedUpdate( FALSE )
/*N*/ {
/*N*/ }

/*N*/ __EXPORT ScDdeLink::~ScDdeLink()
/*N*/ {
/*N*/   // Verbindung aufheben
/*N*/
/*N*/   delete pResult;
/*N*/ }

/*N*/ ScDdeLink::ScDdeLink( ScDocument* pD, const ScDdeLink& rOther ) :
/*N*/   ::so3::SvBaseLink(so3::LINKUPDATE_ALWAYS,FORMAT_STRING),
/*N*/   pDoc    ( pD ),
/*N*/   aAppl   ( rOther.aAppl ),
/*N*/   aTopic  ( rOther.aTopic ),
/*N*/   aItem   ( rOther.aItem ),
/*N*/   nMode   ( rOther.nMode ),
/*N*/   pResult ( NULL ),
/*N*/   bNeedUpdate( FALSE )
/*N*/ {
/*N*/   if (rOther.pResult)
/*N*/       pResult = rOther.pResult->Clone();
/*N*/ }

/*N*/ ScDdeLink::ScDdeLink( ScDocument* pD, SvStream& rStream, ScMultipleReadHeader& rHdr ) :
/*N*/   ::so3::SvBaseLink(so3::LINKUPDATE_ALWAYS,FORMAT_STRING),
/*N*/   pDoc( pD ),
/*N*/   pResult( NULL ),
/*N*/   bNeedUpdate( FALSE )
/*N*/ {
/*N*/   rHdr.StartEntry();
/*N*/
/*N*/   rtl_TextEncoding eCharSet = rStream.GetStreamCharSet();
/*N*/   rStream.ReadByteString( aAppl, eCharSet );
/*N*/   rStream.ReadByteString( aTopic, eCharSet );
/*N*/   rStream.ReadByteString( aItem, eCharSet );
/*N*/
/*N*/   BOOL bHasValue;
/*N*/   rStream >> bHasValue;
/*N*/   if ( bHasValue )
/*N*/       pResult = new ScMatrix( rStream );
/*N*/
/*N*/   if (rHdr.BytesLeft())       // neu in 388b und der 364w (RealTime-Client) Version
/*N*/       rStream >> nMode;
/*N*/   else
/*N*/       nMode = SC_DDE_DEFAULT;
/*N*/
/*N*/   rHdr.EndEntry();
/*N*/ }

/*N*/ void ScDdeLink::Store( SvStream& rStream, ScMultipleWriteHeader& rHdr ) const
/*N*/ {
/*N*/   rHdr.StartEntry();
/*N*/
/*N*/   rtl_TextEncoding eCharSet = rStream.GetStreamCharSet();
/*N*/   rStream.WriteByteString( aAppl, eCharSet );
/*N*/   rStream.WriteByteString( aTopic, eCharSet );
/*N*/   rStream.WriteByteString( aItem, eCharSet );
/*N*/
/*N*/   BOOL bHasValue = ( pResult != NULL );
/*N*/   rStream << bHasValue;
/*N*/   if (bHasValue)
/*N*/       pResult->Store( rStream );
/*N*/
/*N*/   if( rStream.GetVersion() > SOFFICE_FILEFORMAT_40 )      // nicht bei 4.0 Export
/*N*/       rStream << nMode;                                   // seit 388b
/*N*/
/*N*/   //  Links mit Mode != SC_DDE_DEFAULT werden bei 4.0 Export komplett weggelassen
/*N*/   //  (aus ScDocument::SaveDdeLinks)
/*N*/
/*N*/   rHdr.EndEntry();
/*N*/ }

/*N*/ void __EXPORT ScDdeLink::DataChanged( const String& rMimeType,
/*N*/                               const ::com::sun::star::uno::Any & rValue )
/*N*/ {
/*?*/   DBG_ASSERT(0, "STRIP"); //STRIP001 //   wir koennen nur Strings...
//STRIP001  if ( FORMAT_STRING != SotExchange::GetFormatIdFromMimeType( rMimeType ))
//STRIP001      return;
//STRIP001
//STRIP001  String aLinkStr;
//STRIP001  ScByteSequenceToString::GetString( aLinkStr, rValue, DDE_TXT_ENCODING );
//STRIP001  aLinkStr.ConvertLineEnd(LINEEND_LF);
//STRIP001
//STRIP001  //  wenn String mit Zeilenende aufhoert, streichen:
//STRIP001
//STRIP001  xub_StrLen nLen = aLinkStr.Len();
//STRIP001  if (nLen && aLinkStr.GetChar(nLen-1) == '\n')
//STRIP001      aLinkStr.Erase(nLen-1);
//STRIP001
//STRIP001  String aLine;
//STRIP001  USHORT nCols = 1;       // Leerstring -> eine leere Zelle
//STRIP001  USHORT nRows = 1;
//STRIP001  if (aLinkStr.Len())
//STRIP001  {
//STRIP001      nRows = (USHORT) aLinkStr.GetTokenCount( '\n' );
//STRIP001      aLine = aLinkStr.GetToken( 0, '\n' );
//STRIP001      if (aLine.Len())
//STRIP001          nCols = (USHORT) aLine.GetTokenCount( '\t' );
//STRIP001  }
//STRIP001
//STRIP001  if (!nRows || !nCols)               // keine Daten
//STRIP001  {
//STRIP001      DELETEZ(pResult);
//STRIP001  }
//STRIP001  else                                // Daten aufteilen
//STRIP001  {
//STRIP001      //  Matrix immer neu anlegen, damit bIsString nicht durcheinanderkommt
//STRIP001      delete pResult;
//STRIP001      pResult = new ScMatrix( nCols, nRows );
//STRIP001
//STRIP001      SvNumberFormatter* pFormatter = pDoc->GetFormatTable();
//STRIP001
//STRIP001      //  nMode bestimmt, wie der Text interpretiert wird (#44455#/#49783#):
//STRIP001      //  SC_DDE_DEFAULT - Zahlformat aus Zellvorlage "Standard"
//STRIP001      //  SC_DDE_ENGLISH - Standard-Zahlformat fuer English/US
//STRIP001      //  SC_DDE_TEXT    - ohne NumberFormatter direkt als String
//STRIP001      ULONG nStdFormat = 0;
//STRIP001      if ( nMode == SC_DDE_DEFAULT )
//STRIP001      {
//STRIP001          ScPatternAttr* pDefPattern = pDoc->GetDefPattern();     // enthaelt Standard-Vorlage
//STRIP001          if ( pDefPattern )
//STRIP001              nStdFormat = pDefPattern->GetNumberFormat( pFormatter );
//STRIP001      }
//STRIP001      else if ( nMode == SC_DDE_ENGLISH )
//STRIP001          nStdFormat = pFormatter->GetStandardIndex(LANGUAGE_ENGLISH_US);
//STRIP001
//STRIP001      String aEntry;
//STRIP001      for (USHORT nR=0; nR<nRows; nR++)
//STRIP001      {
//STRIP001          aLine = aLinkStr.GetToken( (xub_StrLen) nR, '\n' );
//STRIP001          for (USHORT nC=0; nC<nCols; nC++)
//STRIP001          {
//STRIP001              aEntry = aLine.GetToken( (xub_StrLen) nC, '\t' );
//STRIP001              ULONG nIndex = nStdFormat;
//STRIP001              double fVal;
//STRIP001              if ( nMode != SC_DDE_TEXT && pFormatter->IsNumberFormat( aEntry, nIndex, fVal ) )
//STRIP001                  pResult->PutDouble( fVal, nC, nR );
//STRIP001              else
//STRIP001                  pResult->PutString( aEntry, nC, nR );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  //  Es hat sich was getan...
//STRIP001
//STRIP001  if (HasListeners())
//STRIP001  {
//STRIP001      Broadcast( ScHint( SC_HINT_DATACHANGED, ScAddress( 0 ), NULL ) );
//STRIP001      pDoc->TrackFormulas();      // muss sofort passieren
//STRIP001      pDoc->StartTrackTimer();
//STRIP001
//STRIP001      //  StartTrackTimer ruft asynchron TrackFormulas, Broadcast(FID_DATACHANGED),
//STRIP001      //  ResetChanged, SetModified und Invalidate(SID_SAVEDOC/SID_DOC_MODIFIED)
//STRIP001      //  TrackFormulas zusaetzlich nochmal sofort, damit nicht z.B. durch IdleCalc
//STRIP001      //  eine Formel berechnet wird, die noch im FormulaTrack steht (#61676#)
//STRIP001
//STRIP001      //  notify Uno objects (for XRefreshListener)
//STRIP001      //  must be after TrackFormulas
//STRIP001      //! do this asynchronously?
//STRIP001      ScLinkRefreshedHint aHint;
//STRIP001      aHint.SetDdeLink( aAppl, aTopic, aItem, nMode );
//STRIP001      pDoc->BroadcastUno( aHint );
//STRIP001  }
/*N*/ }

//STRIP001 void ScDdeLink::NewData(USHORT nCols, USHORT nRows)
//STRIP001 {
//STRIP001  delete pResult;
//STRIP001  pResult = new ScMatrix( nCols, nRows );
//STRIP001 }

//STRIP001 void ScDdeLink::ResetValue()
//STRIP001 {
//STRIP001  DELETEZ(pResult);
//STRIP001
//STRIP001  //  Es hat sich was getan...
//STRIP001  //  Tracking, FID_DATACHANGED etc. passiert von aussen
//STRIP001
//STRIP001  if (HasListeners())
//STRIP001      Broadcast( ScHint( SC_HINT_DATACHANGED, ScAddress( 0 ), NULL ) );
//STRIP001 }

//STRIP001 void __EXPORT ScDdeLink::ListenersGone()
//STRIP001 {
//STRIP001  BOOL bWas = bIsInUpdate;
//STRIP001  bIsInUpdate = TRUE;             // Remove() kann Reschedule ausloesen??!?
//STRIP001
//STRIP001  ScDocument* pStackDoc = pDoc;   // member pDoc can't be used after removing the link
//STRIP001
//STRIP001  SvxLinkManager* pLinkMgr = pDoc->GetLinkManager();
//STRIP001  pLinkMgr->Remove( this);        // deletes this
//STRIP001
//STRIP001  if ( !pLinkMgr->GetLinks().Count() )            // letzten geloescht ?
//STRIP001  {
//STRIP001      SfxBindings* pBindings = pStackDoc->GetViewBindings();      // don't use member pDoc!
//STRIP001      if (pBindings)
//STRIP001          pBindings->Invalidate( SID_LINKS );
//STRIP001  }
//STRIP001
//STRIP001  bIsInUpdate = bWas;
//STRIP001 }

/*N*/ void ScDdeLink::TryUpdate()
/*N*/ {
/*N*/   if (bIsInUpdate)
/*N*/       bNeedUpdate = TRUE;         // kann jetzt nicht ausgefuehrt werden
/*N*/   else
/*N*/   {
/*N*/       bIsInUpdate = TRUE;
/*N*/       //Application::Reschedule();    //! OS/2-Simulation
/*N*/         pDoc->IncInDdeLinkUpdate();
/*N*/       Update();
/*N*/         pDoc->DecInDdeLinkUpdate();
/*N*/       bIsInUpdate = FALSE;
/*N*/       bNeedUpdate = FALSE;
/*N*/   }
/*N*/ }


