/*************************************************************************
 *
 *  $RCSfile: sw_dbg_lay.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 15:27:12 $
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

/* -----------------08.01.99 14:55-------------------
 * Und hier die Beschreibung:
 *
 * Durch die PROTOCOL-Makros wird es ermoeglicht, Ereignisse im Frame-Methoden zu protokollieren.
 * In protokollwuerdigen Stellen in Frame-Methoden muss entweder ein PROTOCOL(...) oder bei Methoden,
 * bei denen auch das Verlassen der Methode mitprotokolliert werden soll, ein PROTOCOL_ENTER(...)-Makro
 * stehen.
 * Die Parameter der PROTOCOL-Makros sind
 * 1.   Ein Pointer auf einen SwFrm, also meist "this" oder "rThis"
 * 2.   Die Funktionsgruppe z.B. PROT_MAKEALL, hierueber wird (inline) entschieden, ob dies
 *      zur Zeit protokolliert werden soll oder nicht.
 * 3.   Die Aktion, im Normalfall 0, aber z.B. ein ACT_START bewirkt eine Einrueckung in der
 *      Ausgabedatei, ein ACT_END nimmt dies wieder zurueck. Auf diese Art wird z.B. durch
 *      PROTOCOL_ENTER am Anfang einer Methode eingerueckt und beim Verlassen wieder zurueck.
 * 4.   Der vierte Parameter ist ein void-Pointer, damit man irgendetwas uebergeben kann,
 *      was in das Protokoll einfliessen kann, typesches Beispiel bei PROT_GROW muss man
 *      einen Pointer auf den Wert, um den gegrowt werden soll, uebergeben.
 *
 *
 * Das Protokoll ist die Datei "dbg_lay.out" im aktuellen (BIN-)Verzeichnis.
 * Es enthaelt Zeilen mit FrmId, Funktionsgruppe sowie weiteren Infos.
 *
 * Was genau protokolliert wird, kann auf folgende Arten eingestellt werden:
 * 1.   Die statische Variable SwProtokoll::nRecord enthaelt die Funktionsgruppen,
 *      die aufgezeichnet werden sollen.
 *      Ein Wert von z.B. PROT_GROW bewirkt, das Aufrufe von SwFrm::Grow dokumentiert werden,
 *      PROT_MAKEALL protokolliert Aufrufe von xxx::MakeAll.
 *      Die PROT_XY-Werte koennen oderiert werden.
 *      Default ist Null, es wird keine Methode aufgezeichnet.
 * 2.   In der SwImplProtocol-Klasse gibt es einen Filter fuer Frame-Typen,
 *      nur die Methodenaufrufe von Frame-Typen, die dort gesetzt sind, werden protokolliert.
 *      Der Member nTypes kann auf Werte wie FRM_PAGE, FRM_SECTION gesetzt und oderiert werden.
 *      Default ist 0xFFFF, d.h. alle Frame-Typen.
 * 3.   In der SwImplProtocol-Klasse gibt es einen ArrayPointer auf FrmIds, die zu ueberwachen sind.
 *      Ist der Pointer Null, so werden alle Frames protokolliert, ansonsten nur Frames,
 *      die in dem Array vermerkt sind.
 *
 * Eine Aufzeichnung in Gang zu setzen, erfordert entweder Codemanipulation, z.B. in
 * SwProtocol::Init() einen anderen Default fuer nRecord setzen oder Debuggermanipulation.
 * Im Debugger gibt verschiedene, sich anbietende Stellen:
 * 1.   In SwProtocol::Init() einen Breakpoint setzen und dort nRecord manipulieren, ggf.
 *      FrmIds eintragen, dann beginnt die Aufzeichnung bereits beim Programmstart.
 * 2.   Waehrend des Programmlaufs einen Breakpoint vor irgendein PROTOCOL oder PROTOCOL_ENTER-
 *      Makro setzen, dann am SwProtocol::nRecord das unterste Bit setzen (PROT_INIT). Dies
 *      bewirkt, dass die Funktionsgruppe des folgenden Makros aktiviert und in Zukunft
 *      protokolliert wird.
 * 3.   Spezialfall von 2.: Wenn man 2. in der Methode SwRootFrm::Paint(..) anwendet, werden
 *      die Aufzeichnungseinstellung aus der Datei "dbg_lay.ini" ausgelesen!
 *      In dieser INI-Datei kann es Kommentarzeilen geben, diese beginnen mit '#', dann
 *      sind die Sektionen "[frmid]", "[frmtype]" und "[record]" relevant.
 *      Nach [frmid] koennen die FrameIds der zu protokollierenden Frames folgen. Gibt es
 *      dort keine Eintraege, werden alle Frames aufgezeichnet.
 *      Nach [frmtype] koennen FrameTypen folgen, die aufgezeichnet werden sollen, da der
 *      Default hier allerdings USHRT_MAX ist, werden sowieso alle aufgezeichnet. Man kann
 *      allerdings auch Typen entfernen, in dem man ein '!' vor den Wert setzt, z.B.
 *      !0xC000 nimmt die SwCntntFrms aus der Aufzeichnung heraus.
 *      Nach [record] folgen die Funktionsgruppen, die aufgezeichnet werden sollen, Default
 *      ist hier 0, also keine. Auch hier kann man mit einem vorgestellten '!' Funktionen
 *      wieder entfernen.
 *      Hier mal ein Beispiel fuer eine INI-Datei:
 *      ------------------------------------------
 *          #Funktionen: Alle, ausser PRTAREA
 *          [record] 0xFFFFFFE !0x200
 *          [frmid]
 *          #folgende FrmIds:
 *          1 2 12 13 14 15
 *          #keine Layoutframes ausser ColumnFrms
 *          [frmtype] !0x3FFF 0x4
 *      ------------------------------------------
 *
 * Wenn die Aufzeichnung erstmal laeuft, kann man in SwImplProtocol::_Record(...) mittels
 * Debugger vielfaeltige Manipulationen vornehmen, z.B. bezueglich FrameTypen oder FrmIds.
 *
 * --------------------------------------------------*/

#ifdef PRODUCT
#error Wer fummelt denn an den makefiles rum?
#endif


#pragma hdrstop

#include "dbg_lay.hxx"

#ifndef _STREAM_HXX //autogen
#include <tools/stream.hxx>
#endif

#ifndef _SVSTDARR_HXX
#define _SVSTDARR_USHORTS
#define _SVSTDARR_USHORTSSORT
#define _SVSTDARR_LONGS
#include <svtools/svstdarr.hxx>
#endif

#include <stdio.h>

#include "frame.hxx"
#include "layfrm.hxx"
#include "flyfrm.hxx"
#include "txtfrm.hxx"
#include "ndtxt.hxx"
#include "dflyobj.hxx"
#ifndef _FNTCACHE_HXX
#include <fntcache.hxx>
#endif

/*N*/ ULONG SwProtocol::nRecord = 0;
/*N*/ SwImplProtocol* SwProtocol::pImpl = NULL;

//STRIP001 ULONG lcl_GetFrameId( const SwFrm* pFrm )
//STRIP001 {
//STRIP001 #ifndef PRODUCT
//STRIP001     static BOOL bFrameId = FALSE;
//STRIP001     if( bFrameId )
//STRIP001         return pFrm->GetFrmId();
//STRIP001 #endif
//STRIP001     if( pFrm && pFrm->IsTxtFrm() )
//STRIP001         return ((SwTxtFrm*)pFrm)->GetTxtNode()->GetIndex();
//STRIP001     return 0;
//STRIP001 }

/*N*/ class SwImplProtocol
/*N*/ {
//STRIP001  SvFileStream *pStream;      // Ausgabestream
//STRIP001  SvUShortsSort *pFrmIds;     // welche FrmIds sollen aufgezeichnet werden ( NULL == alle )
//STRIP001     SvLongs *pVar;              // Variables
//STRIP001     ByteString aLayer;          // Einrueckung der Ausgabe ("  " pro Start/End)
//STRIP001  USHORT nTypes;              // welche Typen sollen aufgezeichnet werden
//STRIP001  USHORT nLineCount;          // Ausgegebene Zeilen
//STRIP001  USHORT nMaxLines;           // Maximal auszugebende Zeilen
//STRIP001  BYTE nInitFile;             // Bereich (FrmId,FrmType,Record) beim Einlesen der INI-Datei
//STRIP001  BYTE nTestMode;             // Special fuer Testformatierung, es wird ggf. nur
//STRIP001                              // innerhalb einer Testformatierung aufgezeichnet.
//STRIP001  void _Record( const SwFrm* pFrm, ULONG nFunction, ULONG nAct, void* pParam );
//STRIP001  BOOL NewStream();
//STRIP001  void CheckLine( ByteString& rLine );
//STRIP001  void SectFunc( ByteString &rOut, const SwFrm* pFrm, ULONG nAct, void* pParam );
/*N*/ public:
    SwImplProtocol(){DBG_ASSERT(0, "STRIP");} //STRIP001 SwImplProtocol();
//STRIP001  ~SwImplProtocol();
//STRIP001  // Aufzeichnen
//STRIP001  void Record( const SwFrm* pFrm, ULONG nFunction, ULONG nAct, void* pParam )
//STRIP001      { if( pStream ) _Record( pFrm, nFunction, nAct, pParam ); }
//STRIP001  BOOL InsertFrm( USHORT nFrmId );    // FrmId aufnehmen zum Aufzeichnen
//STRIP001  BOOL DeleteFrm( USHORT nFrmId );    // FrmId entfernen, diesen nicht mehr Aufzeichnen
//STRIP001  void FileInit();                    // Auslesen der INI-Datei
//STRIP001  void ChkStream() { if( !pStream ) NewStream(); }
//STRIP001     void SnapShot( const SwFrm* pFrm, ULONG nFlags );
//STRIP001     void GetVar( const USHORT nNo, long& rVar )
//STRIP001         { if( pVar && nNo < pVar->Count() ) rVar = (*pVar)[ nNo ]; }
/*N*/ };

/* -----------------11.01.99 10:43-------------------
 * Durch das PROTOCOL_ENTER-Makro wird ein SwEnterLeave-Objekt erzeugt,
 * wenn die aktuelle Funktion aufgezeichnet werden soll, wird ein
 * SwImplEnterLeave-Objekt angelegt. Der Witz dabei ist, das der Ctor
 * des Impl-Objekt am Anfang der Funktion und automatisch der Dtor beim
 * Verlassen der Funktion gerufen wird. In der Basis-Implementierung ruft
 * der Ctor lediglich ein PROTOCOL(..) mit ACT_START und im Dtor ein
 * PROTOCOL(..) mit ACT_END.
 * Es lassen sich Ableitungen der Klasse bilden, um z.B. beim Verlassen
 * einer Funktion Groessenaenderungen des Frames zu dokumentieren u.v.a.m.
 * Dazu braucht dann nur noch in SwEnterLeave::Ctor(...) die gewuenschte
 * SwImplEnterLeave-Klasse angelegt zu werden.
 *
 * --------------------------------------------------*/

//STRIP001 class SwImplEnterLeave
//STRIP001 {
//STRIP001 protected:
//STRIP001  const SwFrm* pFrm;              // Der Frame,
//STRIP001  ULONG nFunction, nAction;       // die Funktion, ggf. die Aktion
//STRIP001  void* pParam;                   // und weitere Parameter
//STRIP001 public:
//STRIP001  SwImplEnterLeave( const SwFrm* pF, ULONG nFunct, ULONG nAct, void* pPar )
//STRIP001      : pFrm( pF ), nFunction( nFunct ), nAction( nAct ), pParam( pPar ) {}
//STRIP001  virtual void Enter();           // Ausgabe beim Eintritt
//STRIP001  virtual void Leave();           // Ausgabe beim Verlassen
//STRIP001 };

//STRIP001 class SwSizeEnterLeave : public SwImplEnterLeave
//STRIP001 {
//STRIP001  long nFrmHeight;
//STRIP001 public:
//STRIP001  SwSizeEnterLeave( const SwFrm* pF, ULONG nFunct, ULONG nAct, void* pPar )
//STRIP001      : SwImplEnterLeave( pF, nFunct, nAct, pPar ), nFrmHeight( pF->Frm().Height() ) {}
//STRIP001  virtual void Leave();           // Ausgabe der Groessenaenderung
//STRIP001 };

//STRIP001 class SwUpperEnterLeave : public SwImplEnterLeave
//STRIP001 {
//STRIP001  USHORT nFrmId;
//STRIP001 public:
//STRIP001  SwUpperEnterLeave( const SwFrm* pF, ULONG nFunct, ULONG nAct, void* pPar )
//STRIP001      : SwImplEnterLeave( pF, nFunct, nAct, pPar ), nFrmId( 0 ) {}
//STRIP001  virtual void Enter();           // Ausgabe
//STRIP001  virtual void Leave();           // Ausgabe der FrmId des Uppers
//STRIP001 };

//STRIP001 class SwFrmChangesLeave : public SwImplEnterLeave
//STRIP001 {
//STRIP001  SwRect aFrm;
//STRIP001 public:
//STRIP001  SwFrmChangesLeave( const SwFrm* pF, ULONG nFunct, ULONG nAct, void* pPar )
//STRIP001      : SwImplEnterLeave( pF, nFunct, nAct, pPar ), aFrm( pF->Frm() ) {}
//STRIP001  virtual void Enter();           // keine Ausgabe
//STRIP001  virtual void Leave();           // Ausgabe bei Aenderung der Frm-Area
//STRIP001 };

//STRIP001 void SwProtocol::Record( const SwFrm* pFrm, ULONG nFunction, ULONG nAct, void* pParam )
//STRIP001 {
//STRIP001  if( Start() )
//STRIP001  {   // Hier landen wir, wenn im Debugger SwProtocol::nRecord mit PROT_INIT(0x1) oderiert wurde
//STRIP001      BOOL bFinit = FALSE; // Dies bietet im Debugger die Moeglichkeit,
//STRIP001      if( bFinit )         // die Aufzeichnung dieser Action zu beenden
//STRIP001      {
//STRIP001          nRecord &= ~nFunction;  // Diese Funktion nicht mehr aufzeichnen
//STRIP001          nRecord &= ~PROT_INIT;  // PROT_INIT stets zuruecksetzen
//STRIP001          return;
//STRIP001      }
//STRIP001      nRecord |= nFunction;       // Aufzeichnung dieser Funktion freischalten
//STRIP001      nRecord &= ~PROT_INIT;      // PROT_INIT stets zuruecksetzen
//STRIP001      if( pImpl )
//STRIP001          pImpl->ChkStream();
//STRIP001  }
//STRIP001  if( !pImpl )                        // Impl-Object anlegen, wenn noetig
//STRIP001      pImpl = new SwImplProtocol();
//STRIP001  pImpl->Record( pFrm, nFunction, nAct, pParam ); // ...und Aufzeichnen
//STRIP001 }

// Die folgende Funktion wird beim Anziehen der Writer-DLL durch TxtInit(..) aufgerufen
// und ermoeglicht dem Debuggenden Funktionen und/oder FrmIds freizuschalten

/*N*/ void SwProtocol::Init()
/*N*/ {
/*N*/   nRecord = 0;
/*N*/   XubString aName( "dbg_lay.go", RTL_TEXTENCODING_MS_1252 );
/*N*/   SvFileStream aStream( aName, STREAM_READ );
/*N*/   if( aStream.IsOpen() )
/*N*/   {
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001 pImpl = new SwImplProtocol();
//STRIP001 /*?*/        pImpl->FileInit();
/*N*/   }
/*N*/     aStream.Close();
/*N*/ }

// Ende der Aufzeichnung

/*N*/ void SwProtocol::Stop()
/*N*/ {
/*N*/    if( pImpl )
/*N*/    {
/*?*/       delete pImpl;
/*?*/       pImpl = NULL;
/*?*/         if( pFntCache )
/*?*/             pFntCache->Flush();
/*N*/    }
/*N*/    nRecord = 0;
/*N*/ }

// Creates a more or less detailed snapshot of the layout structur

//STRIP001 void SwProtocol::SnapShot( const SwFrm* pFrm, ULONG nFlags )
//STRIP001 {
//STRIP001     if( pImpl )
//STRIP001         pImpl->SnapShot( pFrm, nFlags );
//STRIP001 }

//STRIP001 void SwProtocol::GetVar( const USHORT nNo, long& rVar )
//STRIP001 {
//STRIP001     if( pImpl )
//STRIP001         pImpl->GetVar( nNo, rVar );
//STRIP001 }

//STRIP001 SwImplProtocol::SwImplProtocol()
//STRIP001     : pStream( NULL ), pFrmIds( NULL ), pVar( NULL ), nTypes( 0xffff ),
//STRIP001     nTestMode( 0 ), nLineCount( 0 ), nMaxLines( USHRT_MAX )
//STRIP001 {
//STRIP001  NewStream();
//STRIP001 }

//STRIP001 BOOL SwImplProtocol::NewStream()
//STRIP001 {
//STRIP001  XubString aName( "dbg_lay.out", RTL_TEXTENCODING_MS_1252 );
//STRIP001  nLineCount = 0;
//STRIP001  pStream = new SvFileStream( aName, STREAM_WRITE | STREAM_TRUNC );
//STRIP001  if( pStream->GetError() )
//STRIP001  {
//STRIP001      delete pStream;
//STRIP001      pStream = NULL;
//STRIP001  }
//STRIP001  return 0 != pStream;
//STRIP001 }

//STRIP001 SwImplProtocol::~SwImplProtocol()
//STRIP001 {
//STRIP001     if( pStream )
//STRIP001     {
//STRIP001         pStream->Close();
//STRIP001         delete pStream;
//STRIP001     }
//STRIP001  delete pFrmIds;
//STRIP001     delete pVar;
//STRIP001 }

/* -----------------11.01.99 11:03-------------------
 * SwImplProtocol::CheckLine analysiert eine Zeile der INI-Datei
 * --------------------------------------------------*/

//STRIP001 void SwImplProtocol::CheckLine( ByteString& rLine )
//STRIP001 {
//STRIP001  rLine = rLine.ToLowerAscii(); // Gross/Kleinschreibung ist einerlei
//STRIP001  while( STRING_LEN > rLine.SearchAndReplace( '\t', ' ' ) )
//STRIP001      ; //nothing                 // Tabs werden durch Blanks ersetzt
//STRIP001  if( '#' == rLine.GetChar(0) )   // Kommentarzeilen beginnen mit '#'
//STRIP001      return;
//STRIP001  if( '[' == rLine.GetChar(0) )   // Bereiche: FrmIds, Typen oder Funktionen
//STRIP001  {
//STRIP001      ByteString aTmp = rLine.GetToken( 0, ']' );
//STRIP001      if( "[frmid" == aTmp )      // Bereich FrmIds
//STRIP001      {
//STRIP001          nInitFile = 1;
//STRIP001          delete pFrmIds;
//STRIP001          pFrmIds = NULL;         // Default: Alle Frames aufzeichnen
//STRIP001      }
//STRIP001      else if( "[frmtype" == aTmp )// Bereich Typen
//STRIP001      {
//STRIP001          nInitFile = 2;
//STRIP001          nTypes = USHRT_MAX;     // Default: Alle FrmaeTypen aufzeichnen
//STRIP001      }
//STRIP001      else if( "[record" == aTmp )// Bereich Funktionen
//STRIP001      {
//STRIP001          nInitFile = 3;
//STRIP001          SwProtocol::SetRecord( 0 );// Default: Keine Funktion wird aufgezeichnet
//STRIP001      }
//STRIP001      else if( "[test" == aTmp )// Bereich Funktionen
//STRIP001      {
//STRIP001          nInitFile = 4; // Default:
//STRIP001          nTestMode = 0; // Ausserhalb der Testformatierung wird aufgezeichnet
//STRIP001      }
//STRIP001      else if( "[max" == aTmp )// maximale Zeilenzahl
//STRIP001      {
//STRIP001          nInitFile = 5; // Default:
//STRIP001          nMaxLines = USHRT_MAX;
//STRIP001      }
//STRIP001         else if( "[var" == aTmp )// variables
//STRIP001      {
//STRIP001             nInitFile = 6;
//STRIP001             if( !pVar )
//STRIP001                 pVar = new SvLongs( 5, 5 );
//STRIP001         }
//STRIP001      else
//STRIP001          nInitFile = 0;          // Nanu: Unbekannter Bereich?
//STRIP001      rLine.Erase( 0, aTmp.Len() + 1 );
//STRIP001  }
//STRIP001  USHORT nToks = rLine.GetTokenCount( ' ' );  // Blanks (oder Tabs) sind die Trenner
//STRIP001  for( USHORT i=0; i < nToks; ++i )
//STRIP001  {
//STRIP001      ByteString aTok = rLine.GetToken( i, ' ' );
//STRIP001      BOOL bNo = FALSE;
//STRIP001      if( '!' == aTok.GetChar(0) )
//STRIP001      {
//STRIP001          bNo = TRUE;                 // Diese(n) Funktion/Typ entfernen
//STRIP001          aTok.Erase( 0, 1 );
//STRIP001      }
//STRIP001      if( aTok.Len() )
//STRIP001      {
//STRIP001          ULONG nVal;
//STRIP001          sscanf( aTok.GetBuffer(), "%li", &nVal );
//STRIP001          switch ( nInitFile )
//STRIP001          {
//STRIP001              case 1: InsertFrm( USHORT( nVal ) );    // FrmId aufnehmen
//STRIP001                      break;
//STRIP001              case 2: {
//STRIP001                          USHORT nNew = (USHORT)nVal;
//STRIP001                          if( bNo )
//STRIP001                              nTypes &= ~nNew;    // Typ entfernen
//STRIP001                          else
//STRIP001                              nTypes |= nNew;     // Typ aufnehmen
//STRIP001                      }
//STRIP001                      break;
//STRIP001              case 3: {
//STRIP001                          ULONG nOld = SwProtocol::Record();
//STRIP001                          if( bNo )
//STRIP001                              nOld &= ~nVal;      // Funktion entfernen
//STRIP001                          else
//STRIP001                              nOld |= nVal;       // Funktion aufnehmen
//STRIP001                          SwProtocol::SetRecord( nOld );
//STRIP001                      }
//STRIP001                      break;
//STRIP001              case 4: {
//STRIP001                          BYTE nNew = (BYTE)nVal;
//STRIP001                          if( bNo )
//STRIP001                              nTestMode &= ~nNew; // TestMode zuruecksetzen
//STRIP001                          else
//STRIP001                              nTestMode |= nNew;      // TestMode setzen
//STRIP001                      }
//STRIP001                      break;
//STRIP001              case 5: nMaxLines = (USHORT)nVal;
//STRIP001                      break;
//STRIP001                 case 6: pVar->Insert( (long)nVal, pVar->Count() );
//STRIP001                         break;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

/* -----------------11.01.99 11:17-------------------
 * SwImplProtocol::FileInit() liest die Datei "dbg_lay.ini"
 * im aktuellen Verzeichnis und wertet sie aus.
 * --------------------------------------------------*/
//STRIP001 void SwImplProtocol::FileInit()
//STRIP001 {
//STRIP001  XubString aName( "dbg_lay.ini", RTL_TEXTENCODING_MS_1252 );
//STRIP001  SvFileStream aStream( aName, STREAM_READ );
//STRIP001  if( aStream.IsOpen() )
//STRIP001  {
//STRIP001      ByteString aLine;
//STRIP001      nInitFile = 0;
//STRIP001      while( !aStream.IsEof() )
//STRIP001      {
//STRIP001          sal_Char c;
//STRIP001          aStream >> c;
//STRIP001          if( '\n' == c || '\r' == c )    // Zeilenende
//STRIP001          {
//STRIP001              aLine.EraseLeadingChars();
//STRIP001              aLine.EraseTrailingChars();
//STRIP001              if( aLine.Len() )
//STRIP001                  CheckLine( aLine );     // Zeile auswerten
//STRIP001              aLine.Erase();
//STRIP001          }
//STRIP001          else
//STRIP001              aLine += c;
//STRIP001      }
//STRIP001      if( aLine.Len() )
//STRIP001          CheckLine( aLine );     // letzte Zeile auswerten
//STRIP001  }
//STRIP001     aStream.Close();
//STRIP001 }

/* -----------------11.01.99 11:20-------------------
 * lcl_Start sorgt fuer Einrueckung um zwei Blanks bei ACT_START
 * und nimmt diese bei ACT_END wieder zurueck.
 * --------------------------------------------------*/
//STRIP001 void lcl_Start( ByteString& rOut, ByteString& rLay, ULONG nAction )
//STRIP001 {
//STRIP001  if( nAction == ACT_START )
//STRIP001  {
//STRIP001      rLay += "  ";
//STRIP001      rOut += " On";
//STRIP001  }
//STRIP001  else if( nAction == ACT_END )
//STRIP001  {
//STRIP001      if( rLay.Len() > 1 )
//STRIP001      {
//STRIP001          rLay.Erase( rLay.Len() - 2 );
//STRIP001          rOut.Erase( 0, 2 );
//STRIP001      }
//STRIP001      rOut += " Off";
//STRIP001  }
//STRIP001 }

/* -----------------11.01.99 11:21-------------------
 * lcl_Flags gibt das ValidSize-, ValidPos- und ValidPrtArea-Flag ("Sz","Ps","PA")
 * des Frames aus, "+" fuer valid, "-" fuer invalid.
 * --------------------------------------------------*/

//STRIP001 void lcl_Flags( ByteString& rOut, const SwFrm* pFrm )
//STRIP001 {
//STRIP001  rOut += " Sz";
//STRIP001  rOut += pFrm->GetValidSizeFlag() ? '+' : '-';
//STRIP001  rOut += " Ps";
//STRIP001  rOut += pFrm->GetValidPosFlag() ? '+' : '-';
//STRIP001  rOut += " PA";
//STRIP001  rOut += pFrm->GetValidPrtAreaFlag() ? '+' : '-';
//STRIP001 }

/* -----------------11.01.99 11:23-------------------
 * lcl_FrameType gibt den Typ des Frames in Klartext aus.
 * --------------------------------------------------*/

//STRIP001 void lcl_FrameType( ByteString& rOut, const SwFrm* pFrm )
//STRIP001 {
//STRIP001  if( pFrm->IsTxtFrm() )
//STRIP001      rOut += "Txt ";
//STRIP001  else if( pFrm->IsLayoutFrm() )
//STRIP001  {
//STRIP001      if( pFrm->IsPageFrm() )
//STRIP001          rOut += "Page ";
//STRIP001      else if( pFrm->IsColumnFrm() )
//STRIP001          rOut += "Col ";
//STRIP001      else if( pFrm->IsBodyFrm() )
//STRIP001      {
//STRIP001          if( pFrm->GetUpper() && pFrm->IsColBodyFrm() )
//STRIP001              rOut += "(Col)";
//STRIP001          rOut += "Body ";
//STRIP001      }
//STRIP001      else if( pFrm->IsRootFrm() )
//STRIP001          rOut += "Root ";
//STRIP001      else if( pFrm->IsCellFrm() )
//STRIP001          rOut += "Cell ";
//STRIP001      else if( pFrm->IsTabFrm() )
//STRIP001          rOut += "Tab ";
//STRIP001      else if( pFrm->IsRowFrm() )
//STRIP001          rOut += "Row ";
//STRIP001      else if( pFrm->IsSctFrm() )
//STRIP001          rOut += "Sect ";
//STRIP001      else if( pFrm->IsHeaderFrm() )
//STRIP001          rOut += "Header ";
//STRIP001      else if( pFrm->IsFooterFrm() )
//STRIP001          rOut += "Footer ";
//STRIP001      else if( pFrm->IsFtnFrm() )
//STRIP001          rOut += "Ftn ";
//STRIP001      else if( pFrm->IsFtnContFrm() )
//STRIP001          rOut += "FtnCont ";
//STRIP001      else if( pFrm->IsFlyFrm() )
//STRIP001          rOut += "Fly ";
//STRIP001      else
//STRIP001          rOut += "Layout ";
//STRIP001  }
//STRIP001  else if( pFrm->IsNoTxtFrm() )
//STRIP001      rOut += "NoTxt ";
//STRIP001  else
//STRIP001      rOut += "Not impl. ";
//STRIP001 }

/* -----------------11.01.99 11:25-------------------
 * SwImplProtocol::Record(..) wird nur gerufen, wenn das PROTOCOL-Makro
 * feststellt, dass die Funktion aufgezeichnet werden soll ( SwProtocol::nRecord ).
 * In dieser Methode werden noch die beiden weiteren Einschraenkungen ueberprueft,
 * ob die FrmId und der FrameType zu den aufzuzeichnenden gehoeren.
 * --------------------------------------------------*/

//STRIP001 void SwImplProtocol::_Record( const SwFrm* pFrm, ULONG nFunction, ULONG nAct, void* pParam )
//STRIP001 {
//STRIP001  USHORT nSpecial = 0;
//STRIP001  if( nSpecial )  // Debugger-Manipulationsmoeglichkeit
//STRIP001  {
//STRIP001         USHORT nId = USHORT(lcl_GetFrameId( pFrm ));
//STRIP001      switch ( nSpecial )
//STRIP001      {
//STRIP001          case 1: InsertFrm( nId ); break;
//STRIP001          case 2: DeleteFrm( nId ); break;
//STRIP001          case 3: delete pFrmIds; pFrmIds = NULL; break;
//STRIP001          case 4: delete pStream; pStream = NULL; break;
//STRIP001      }
//STRIP001      return;
//STRIP001  }
//STRIP001  if( !pStream && !NewStream() )
//STRIP001      return; // Immer noch kein Stream
//STRIP001
//STRIP001     if( pFrmIds && !pFrmIds->Seek_Entry( USHORT(lcl_GetFrameId( pFrm )) ) )
//STRIP001         return; // gehoert nicht zu den gewuenschten FrmIds
//STRIP001
//STRIP001  if( !(pFrm->GetType() & nTypes) )
//STRIP001      return; // Der Typ ist unerwuenscht
//STRIP001
//STRIP001  if( 1 == nTestMode && nFunction != PROT_TESTFORMAT )
//STRIP001      return; // Wir sollen nur innerhalb einer Testformatierung aufzeichnen
//STRIP001  BOOL bTmp = FALSE;
//STRIP001  ByteString aOut = aLayer;
//STRIP001     aOut += ByteString::CreateFromInt64( lcl_GetFrameId( pFrm ) );
//STRIP001  aOut += ' ';
//STRIP001  lcl_FrameType( aOut, pFrm );    // dann den FrameType
//STRIP001  switch ( nFunction )            // und die Funktion
//STRIP001  {
//STRIP001         case PROT_SNAPSHOT: lcl_Flags( aOut, pFrm );
//STRIP001                             break;
//STRIP001      case PROT_MAKEALL:  aOut += "MakeAll";
//STRIP001                          lcl_Start( aOut, aLayer, nAct );
//STRIP001                          if( nAct == ACT_START )
//STRIP001                              lcl_Flags( aOut, pFrm );
//STRIP001                          break;
//STRIP001      case PROT_MOVE_FWD: bTmp = TRUE; // NoBreak
//STRIP001      case PROT_MOVE_BWD: aOut += ( nFunction == bTmp ) ? "Fwd" : "Bwd";
//STRIP001                          lcl_Start( aOut, aLayer, nAct );
//STRIP001                          if( pParam )
//STRIP001                          {
//STRIP001                              aOut += ' ';
//STRIP001                                 aOut += ByteString::CreateFromInt32( *((USHORT*)pParam) );
//STRIP001                          }
//STRIP001                          break;
//STRIP001      case PROT_GROW_TST: if( ACT_START != nAct )
//STRIP001                              return;
//STRIP001                          aOut += "TestGrow";
//STRIP001                          break;
//STRIP001      case PROT_SHRINK_TST: if( ACT_START != nAct )
//STRIP001                              return;
//STRIP001                          aOut += "TestShrink";
//STRIP001                          break;
//STRIP001      case PROT_ADJUSTN :
//STRIP001      case PROT_SHRINK:   bTmp = TRUE; // NoBreak
//STRIP001      case PROT_GROW:     aOut += !bTmp ? "Grow" :
//STRIP001                                  ( nFunction == PROT_SHRINK ? "Shrink" : "AdjustNgbhd" );
//STRIP001                          lcl_Start( aOut, aLayer, nAct );
//STRIP001                          if( pParam )
//STRIP001                          {
//STRIP001                              aOut += ' ';
//STRIP001                                 aOut += ByteString::CreateFromInt64( *((long*)pParam) );
//STRIP001                          }
//STRIP001                          break;
//STRIP001      case PROT_POS:      break;
//STRIP001      case PROT_PRTAREA:  aOut += "PrtArea";
//STRIP001                          lcl_Start( aOut, aLayer, nAct );
//STRIP001                          break;
//STRIP001      case PROT_SIZE:     aOut += "Size";
//STRIP001                          lcl_Start( aOut, aLayer, nAct );
//STRIP001                          aOut += ' ';
//STRIP001                             aOut += ByteString::CreateFromInt64( pFrm->Frm().Height() );
//STRIP001                          break;
//STRIP001      case PROT_LEAF:     aOut += "Prev/NextLeaf";
//STRIP001                          lcl_Start( aOut, aLayer, nAct );
//STRIP001                          aOut += ' ';
//STRIP001                          if( pParam )
//STRIP001                          {
//STRIP001                              aOut += ' ';
//STRIP001                                 aOut += ByteString::CreateFromInt64( lcl_GetFrameId( (SwFrm*)pParam ) );
//STRIP001                          }
//STRIP001                          break;
//STRIP001      case PROT_FILE_INIT: FileInit();
//STRIP001                           aOut = "Initialize";
//STRIP001                          break;
//STRIP001      case PROT_SECTION:  SectFunc( aOut, pFrm, nAct, pParam );
//STRIP001                          break;
//STRIP001      case PROT_CUT:      bTmp = TRUE; // NoBreak
//STRIP001      case PROT_PASTE:    aOut += bTmp ? "Cut from " : "Paste to ";
//STRIP001                             aOut += ByteString::CreateFromInt64( lcl_GetFrameId( (SwFrm*)pParam ) );
//STRIP001                          break;
//STRIP001      case PROT_TESTFORMAT: aOut += "Test";
//STRIP001                          lcl_Start( aOut, aLayer, nAct );
//STRIP001                          if( ACT_START == nAct )
//STRIP001                              nTestMode |= 2;
//STRIP001                          else
//STRIP001                              nTestMode &= ~2;
//STRIP001                          break;
//STRIP001      case PROT_FRMCHANGES:
//STRIP001                          {
//STRIP001                              SwRect& rFrm = *((SwRect*)pParam);
//STRIP001                              if( pFrm->Frm().Pos() != rFrm.Pos() )
//STRIP001                              {
//STRIP001                                  aOut += "PosChg: (";
//STRIP001                                     aOut += ByteString::CreateFromInt64(rFrm.Left());
//STRIP001                                  aOut += ", ";
//STRIP001                                     aOut += ByteString::CreateFromInt64(rFrm.Top());
//STRIP001                                  aOut += ") (";
//STRIP001                                     aOut += ByteString::CreateFromInt64(pFrm->Frm().Left());
//STRIP001                                  aOut += ", ";
//STRIP001                                     aOut += ByteString::CreateFromInt64(pFrm->Frm().Top());
//STRIP001                                  aOut += ") ";
//STRIP001                              }
//STRIP001                              if( pFrm->Frm().Height() != rFrm.Height() )
//STRIP001                              {
//STRIP001                                  aOut += "Height: ";
//STRIP001                                     aOut += ByteString::CreateFromInt64(rFrm.Height());
//STRIP001                                  aOut += " -> ";
//STRIP001                                     aOut += ByteString::CreateFromInt64(pFrm->Frm().Height());
//STRIP001                                  aOut += " ";
//STRIP001                              }
//STRIP001                              if( pFrm->Frm().Width() != rFrm.Width() )
//STRIP001                              {
//STRIP001                                  aOut += "Width: ";
//STRIP001                                     aOut += ByteString::CreateFromInt64(rFrm.Width());
//STRIP001                                  aOut += " -> ";
//STRIP001                                     aOut += ByteString::CreateFromInt64(pFrm->Frm().Width());
//STRIP001                                  aOut += " ";
//STRIP001                              }
//STRIP001                              break;
//STRIP001                          }
//STRIP001  }
//STRIP001  *pStream << aOut.GetBuffer() << endl;   // Ausgabe
//STRIP001  pStream->Flush();   // Gleich auf die Platte, damit man mitlesen kann
//STRIP001  if( ++nLineCount >= nMaxLines )     // Maximale Ausgabe erreicht?
//STRIP001      SwProtocol::SetRecord( 0 );        // => Ende der Aufzeichnung
//STRIP001 }

/* -----------------13.01.99 11:39-------------------
 * SwImplProtocol::SectFunc(...) wird von SwImplProtocol::_Record(..) gerufen,
 * hier werden die Ausgaben rund um SectionFrms abgehandelt.
 * --------------------------------------------------*/

//STRIP001 void SwImplProtocol::SectFunc( ByteString &rOut, const SwFrm* pFrm, ULONG nAct, void* pParam )
//STRIP001 {
//STRIP001  BOOL bTmp = FALSE;
//STRIP001  switch( nAct )
//STRIP001  {
//STRIP001      case ACT_MERGE:         rOut += "Merge Section ";
//STRIP001                                 rOut += ByteString::CreateFromInt64( lcl_GetFrameId( (SwFrm*)pParam ) );
//STRIP001                              break;
//STRIP001      case ACT_CREATE_MASTER: bTmp = TRUE; // NoBreak
//STRIP001      case ACT_CREATE_FOLLOW: rOut += "Create Section ";
//STRIP001                              rOut += bTmp ? "Master to " : "Follow from ";
//STRIP001                                 rOut += ByteString::CreateFromInt64( lcl_GetFrameId( (SwFrm*)pParam ) );
//STRIP001                              break;
//STRIP001      case ACT_DEL_MASTER:    bTmp = TRUE; // NoBreak
//STRIP001      case ACT_DEL_FOLLOW:    rOut += "Delete Section ";
//STRIP001                              rOut += bTmp ? "Master to " : "Follow from ";
//STRIP001                                 rOut += ByteString::CreateFromInt64( lcl_GetFrameId( (SwFrm*)pParam ) );
//STRIP001                              break;
//STRIP001  }
//STRIP001 }

/* -----------------11.01.99 11:31-------------------
 * SwImplProtocol::InsertFrm(..) nimmt eine neue FrmId zum Aufzeichnen auf,
 * wenn pFrmIds==NULL, werden alle aufgezeichnet, sobald durch InsertFrm(..)
 * pFrmIds angelegt wird, werden nur noch die enthaltenen FrmIds aufgezeichnet.
 * --------------------------------------------------*/

//STRIP001 BOOL SwImplProtocol::InsertFrm( USHORT nId )
//STRIP001 {
//STRIP001  if( !pFrmIds )
//STRIP001      pFrmIds = new SvUShortsSort(5,5);
//STRIP001  if( pFrmIds->Seek_Entry( nId ) )
//STRIP001      return FALSE;
//STRIP001  pFrmIds->Insert( nId );
//STRIP001  return TRUE;
//STRIP001 }

/* -----------------11.01.99 11:52-------------------
 * SwImplProtocol::DeleteFrm(..) entfernt eine FrmId aus dem pFrmIds-Array,
 * so dass diese Frame nicht mehr aufgezeichnet wird.
 * --------------------------------------------------*/
//STRIP001 BOOL SwImplProtocol::DeleteFrm( USHORT nId )
//STRIP001 {
//STRIP001  USHORT nPos;
//STRIP001  if( !pFrmIds || !pFrmIds->Seek_Entry( nId, &nPos ) )
//STRIP001      return FALSE;
//STRIP001  pFrmIds->Remove( nPos );
//STRIP001  return TRUE;
//STRIP001 }

/*-----------------20.9.2001 10:29------------------
 * SwProtocol::SnapShot(..)
 * creates a snapshot of the given frame and its content.
 * --------------------------------------------------*/
//STRIP001 void SwImplProtocol::SnapShot( const SwFrm* pFrm, ULONG nFlags )
//STRIP001 {
//STRIP001     while( pFrm )
//STRIP001     {
//STRIP001         _Record( pFrm, PROT_SNAPSHOT, 0, 0);
//STRIP001         if( pFrm->GetDrawObjs() && nFlags & SNAP_FLYFRAMES )
//STRIP001         {
//STRIP001             aLayer += "[ ";
//STRIP001             const SwDrawObjs &rObjs = *pFrm->GetDrawObjs();
//STRIP001          for ( USHORT i = 0; i < rObjs.Count(); ++i )
//STRIP001          {
//STRIP001              SdrObject *pO = rObjs[i];
//STRIP001              if ( pO->IsWriterFlyFrame() )
//STRIP001                     SnapShot( ((SwVirtFlyDrawObj*)pO)->GetFlyFrm(), nFlags );
//STRIP001             }
//STRIP001             if( aLayer.Len() > 1 )
//STRIP001                 aLayer.Erase( aLayer.Len() - 2 );
//STRIP001         }
//STRIP001         if( pFrm->IsLayoutFrm() && nFlags & SNAP_LOWER &&
//STRIP001             ( !pFrm->IsTabFrm() || nFlags & SNAP_TABLECONT ) )
//STRIP001         {
//STRIP001             aLayer += "  ";
//STRIP001             SnapShot( ((SwLayoutFrm*)pFrm)->Lower(), nFlags );
//STRIP001             if( aLayer.Len() > 1 )
//STRIP001                 aLayer.Erase( aLayer.Len() - 2 );
//STRIP001         }
//STRIP001         pFrm = pFrm->GetNext();
//STRIP001     }
//STRIP001 }

/* -----------------11.01.99 11:53-------------------
 * SwEnterLeave::Ctor(..) wird vom eigentlichen (inline-)Kontruktor gerufen,
 * wenn die Funktion aufgezeichnet werden soll.
 * Die Aufgabe ist es abhaengig von der Funktion das richtige SwImplEnterLeave-Objekt
 * zu erzeugen, alles weitere geschieht dann in dessen Ctor/Dtor.
 * --------------------------------------------------*/
//STRIP001 void SwEnterLeave::Ctor( const SwFrm* pFrm, ULONG nFunc, ULONG nAct, void* pPar )
//STRIP001 {
//STRIP001  switch( nFunc )
//STRIP001  {
//STRIP001      case PROT_ADJUSTN :
//STRIP001      case PROT_GROW:
//STRIP001      case PROT_SHRINK : pImpl = new SwSizeEnterLeave( pFrm, nFunc, nAct, pPar ); break;
//STRIP001      case PROT_MOVE_FWD:
//STRIP001      case PROT_MOVE_BWD : pImpl = new SwUpperEnterLeave( pFrm, nFunc, nAct, pPar ); break;
//STRIP001      case PROT_FRMCHANGES : pImpl = new SwFrmChangesLeave( pFrm, nFunc, nAct, pPar ); break;
//STRIP001      default: pImpl = new SwImplEnterLeave( pFrm, nFunc, nAct, pPar ); break;
//STRIP001  }
//STRIP001  pImpl->Enter();
//STRIP001 }

/* -----------------11.01.99 11:56-------------------
 * SwEnterLeave::Dtor() ruft lediglich den Destruktor des SwImplEnterLeave-Objekts,
 * ist nur deshalb nicht inline, damit die SwImplEnterLeave-Definition nicht
 * im dbg_lay.hxx zu stehen braucht.
 * --------------------------------------------------*/

//STRIP001 void SwEnterLeave::Dtor()
//STRIP001 {
//STRIP001  if( pImpl )
//STRIP001  {
//STRIP001      pImpl->Leave();
//STRIP001      delete pImpl;
//STRIP001  }
//STRIP001 }

//STRIP001 void SwImplEnterLeave::Enter()
//STRIP001 {
//STRIP001  SwProtocol::Record( pFrm, nFunction, ACT_START, pParam );
//STRIP001 }

//STRIP001 void SwImplEnterLeave::Leave()
//STRIP001 {
//STRIP001  SwProtocol::Record( pFrm, nFunction, ACT_END, pParam );
//STRIP001 }

//STRIP001 void SwSizeEnterLeave::Leave()
//STRIP001 {
//STRIP001  nFrmHeight = pFrm->Frm().Height() - nFrmHeight;
//STRIP001  SwProtocol::Record( pFrm, nFunction, ACT_END, &nFrmHeight );
//STRIP001 }

//STRIP001 void SwUpperEnterLeave::Enter()
//STRIP001 {
//STRIP001     nFrmId = pFrm->GetUpper() ? USHORT(lcl_GetFrameId( pFrm->GetUpper() )) : 0;
//STRIP001  SwProtocol::Record( pFrm, nFunction, ACT_START, &nFrmId );
//STRIP001 }

//STRIP001 void SwUpperEnterLeave::Leave()
//STRIP001 {
//STRIP001     nFrmId = pFrm->GetUpper() ? USHORT(lcl_GetFrameId( pFrm->GetUpper() )) : 0;
//STRIP001  SwProtocol::Record( pFrm, nFunction, ACT_END, &nFrmId );
//STRIP001 }

//STRIP001 void SwFrmChangesLeave::Enter()
//STRIP001 {
//STRIP001 }

//STRIP001 void SwFrmChangesLeave::Leave()
//STRIP001 {
//STRIP001  if( pFrm->Frm() != aFrm )
//STRIP001      SwProtocol::Record( pFrm, PROT_FRMCHANGES, 0, &aFrm );
//STRIP001 }


