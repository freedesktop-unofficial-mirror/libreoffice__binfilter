/*************************************************************************
 *
 *  $RCSfile: sfx2_appdde.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:40:06 $
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

#ifndef _SV_WRKWIN_HXX //autogen
#include <vcl/wrkwin.hxx>
#endif
#ifndef _SFXRECTITEM_HXX //autogen
#include <svtools/rectitem.hxx>
#endif
#ifndef _SFXENUMITEM_HXX //autogen
#include <svtools/eitem.hxx>
#endif
#ifndef _SFXINTITEM_HXX //autogen
#include <svtools/intitem.hxx>
#endif
#ifndef _SB_SBSTAR_HXX //autogen
#include <basic/sbstar.hxx>
#endif
#ifndef _SFXSTRITEM_HXX //autogen
#include <svtools/stritem.hxx>
#endif
#ifndef _SVDDE_HXX //autogen
#include <svtools/svdde.hxx>
#endif
#ifndef _LNKBASE_HXX //autogen
#include <so3/lnkbase.hxx>
#endif
#ifndef _LINKMGR_HXX //autogen
#include <so3/linkmgr.hxx>
#endif
#include <tools/urlobj.hxx>
#include <svtools/pathoptions.hxx>
#pragma hdrstop

#include "app.hxx"
#include "appdata.hxx"
#include "objsh.hxx"
#include "viewfrm.hxx"
#include "topfrm.hxx"
#include "dispatch.hxx"
#include "sfxtypes.hxx"
#include "sfxsids.hrc"
#if SUPD<613//MUSTINI
#include "inimgr.hxx"
#endif
#include "helper.hxx"
namespace binfilter {

//========================================================================

/*N*/ String SfxDdeServiceName_Impl( const String& sIn )
/*N*/ {
/*N*/   ByteString sTemp = U2S( sIn );
/*N*/   ByteString sReturn;
/*N*/
/*N*/   for ( sal_uInt16 n = sTemp.Len(); n; --n )
/*N*/       if ( sTemp.Copy( n-1, 1 ).IsAlphaNumericAscii() )
/*N*/           sReturn += sTemp.GetChar(n-1);
/*N*/
/*N*/   return S2U( sReturn );
/*N*/ }


class ImplDdeService : public DdeService
{
public:
    ImplDdeService( const String& rNm )
        : DdeService( rNm )
    {}
    virtual BOOL MakeTopic( const String& );

    virtual String  Topics();
//  virtual String  Formats();
//  virtual String  SysItems();
//  virtual String  Status();

    virtual BOOL SysTopicExecute( const String* pStr );
};

class SfxDdeTriggerTopic_Impl : public DdeTopic
{
public:
    SfxDdeTriggerTopic_Impl()
    : DdeTopic( DEFINE_CONST_UNICODE("TRIGGER") )
    {}

    virtual BOOL Execute( const String* );
};

class SfxDdeDocTopic_Impl : public DdeTopic
{
public:
    SfxObjectShell* pSh;
    DdeData aData;
    ::com::sun::star::uno::Sequence< sal_Int8 > aSeq;

    SfxDdeDocTopic_Impl( SfxObjectShell* pShell )
        : DdeTopic( pShell->GetTitle(SFX_TITLE_FULLNAME) ), pSh( pShell )
    {}

    virtual DdeData* Get( ULONG );
    virtual BOOL Put( const DdeData* );
    virtual BOOL Execute( const String* );
    virtual BOOL StartAdviseLoop();
    virtual BOOL MakeItem( const String& rItem );

// wird benoetigt?
//  virtual void Connect( long n );
//  virtual void Disconnect( long n );
//  virtual void StopAdviseLoop();

};


SV_DECL_PTRARR( SfxDdeDocTopics_Impl, SfxDdeDocTopic_Impl * const, 4, 4 )
SV_IMPL_PTRARR( SfxDdeDocTopics_Impl, SfxDdeDocTopic_Impl * const )

//========================================================================

//STRIP001 BOOL SfxAppEvent_Impl( ApplicationEvent &rAppEvent,
//STRIP001                     const String &rCmd, const String &rEvent )
//STRIP001
//STRIP001 /*   [Beschreibung]
//STRIP001
//STRIP001  Pr"uft, ob 'rCmd' das Event 'rEvent' ist (ohne '(') und baut
//STRIP001  aus diesem dann ein <ApplicationEvent> zusammen, das per
//STRIP001  <Application::AppEvent()> ausgef"uhrt werden kann. Ist 'rCmd' das
//STRIP001  angegegeben Event 'rEvent', dann wird TRUE zur"uckgegeben, sonst FALSE.
//STRIP001
//STRIP001
//STRIP001  [Beispiel]
//STRIP001
//STRIP001  rCmd = "Open(\"d:\doc\doc.sdw\")"
//STRIP001  rEvent = "Open"
//STRIP001 */
//STRIP001
//STRIP001 {
//STRIP001  String aEvent( rEvent );
//STRIP001  aEvent += 0x0028 ;// "(" = 28h
//STRIP001     if ( rCmd.CompareIgnoreCaseToAscii( aEvent, aEvent.Len() ) == COMPARE_EQUAL )
//STRIP001  {
//STRIP001      String aData( rCmd );
//STRIP001      aData.Erase( 0, aEvent.Len() );
//STRIP001      if ( aData.Len() > 2 )
//STRIP001      {
//STRIP001          // in das ApplicationEvent-Format wandeln
//STRIP001          aData.Erase( aData.Len()-1, 1 );
//STRIP001          for ( USHORT n = 0; n < aData.Len(); ++n )
//STRIP001          {
//STRIP001              if ( aData.GetChar(n) == 0x0022 ) // " = 22h
//STRIP001                  for ( ; aData.GetChar(++n) != 0x0022 ; )
//STRIP001                      /* empty loop */ ;
//STRIP001              else if ( aData.GetChar(n) == 0x0020 ) // SPACE = 20h
//STRIP001                  aData.SetChar(n, '\n');
//STRIP001          }
//STRIP001          aData.EraseAllChars( 0x0022 );
//STRIP001          ApplicationAddress aAddr;
//STRIP001          rAppEvent = ApplicationEvent( String(), aAddr, U2S(rEvent), aData );
//STRIP001          return TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return FALSE;
//STRIP001 }

//-------------------------------------------------------------------------

//STRIP001 long SfxApplication::DdeExecute
//STRIP001 (
//STRIP001  const String&   rCmd        // in unserer BASIC-Syntax formuliert
//STRIP001 )
//STRIP001
//STRIP001 /*   [Beschreibung]
//STRIP001
//STRIP001  Diese Methode kann vom Applikationsentwickler "uberladen werden,
//STRIP001  um an seine SfxApplication-Subklasse gerichtete DDE-Kommandos
//STRIP001  zu empfangen.
//STRIP001
//STRIP001  Die Basisimplementierung versteht die API-Funktionalit"at der
//STRIP001  betreffenden SfxApplication-Subklasse in BASIC-Syntax. R"uckgabewerte
//STRIP001  k"onnen dabei leider nicht "ubertragen werden.
//STRIP001 */
//STRIP001
//STRIP001 {
//STRIP001  // Print oder Open-Event?
//STRIP001  ApplicationEvent aAppEvent;
//STRIP001  if ( SfxAppEvent_Impl( aAppEvent, rCmd, DEFINE_CONST_UNICODE("Print") ) ||
//STRIP001       SfxAppEvent_Impl( aAppEvent, rCmd, DEFINE_CONST_UNICODE("Open") ) )
//STRIP001      GetpApp()->AppEvent( aAppEvent );
//STRIP001  else
//STRIP001  {
//STRIP001      // alle anderen per BASIC
//STRIP001      EnterBasicCall();
//STRIP001      StarBASIC* pBasic = GetBasic();
//STRIP001      DBG_ASSERT( pBasic, "Wo ist mein Basic???" );
//STRIP001      SbxVariable* pRet = pBasic->Execute( rCmd );
//STRIP001      LeaveBasicCall();
//STRIP001      if( !pRet )
//STRIP001      {
//STRIP001          SbxBase::ResetError();
//STRIP001          return 0;
//STRIP001      }
//STRIP001  }
//STRIP001  return 1;
//STRIP001 }

//--------------------------------------------------------------------

//STRIP001 long SfxApplication::DdeGetData
//STRIP001 (
//STRIP001  const String&   rItem,                  // das anzusprechende Item
//STRIP001  const String& rMimeType,                // in: Format
//STRIP001  ::com::sun::star::uno::Any & rValue     // out: angeforderte Daten
//STRIP001 )
//STRIP001
//STRIP001 /*   [Beschreibung]
//STRIP001
//STRIP001  Diese Methode kann vom Applikationsentwickler "uberladen werden,
//STRIP001  um an seine SfxApplication-Subklasse gerichtete DDE-Daten-Anforderungen
//STRIP001  zu empfangen.
//STRIP001
//STRIP001  Die Basisimplementierung liefert keine Daten und gibt 0 zur"uck.
//STRIP001 */
//STRIP001
//STRIP001 {
//STRIP001  return 0;
//STRIP001 }

//--------------------------------------------------------------------

//STRIP001 long SfxApplication::DdeSetData
//STRIP001 (
//STRIP001  const String&   rItem,      // das anzusprechende Item
//STRIP001  const String& rMimeType,                // in: Format
//STRIP001  const ::com::sun::star::uno::Any & rValue   // out: angeforderte Daten
//STRIP001 )
//STRIP001
//STRIP001 /*   [Beschreibung]
//STRIP001
//STRIP001  Diese Methode kann vom Applikationsentwickler "uberladen werden,
//STRIP001  um an seine SfxApplication-Subklasse gerichtete DDE-Daten
//STRIP001  zu empfangen.
//STRIP001
//STRIP001  Die Basisimplementierung nimmt keine Daten entgegen und liefert 0 zur"uck.
//STRIP001 */
//STRIP001
//STRIP001 {
//STRIP001  return 0;
//STRIP001 }

//--------------------------------------------------------------------

//STRIP001 ::so3::SvLinkSource* SfxApplication::DdeCreateLinkSource
//STRIP001 (
//STRIP001  const String&   rItem      // das zu erzeugende Item
//STRIP001 )
//STRIP001
//STRIP001 /*   [Beschreibung]
//STRIP001
//STRIP001  Diese Methode kann vom Applikationsentwickler "uberladen werden,
//STRIP001  um an seiner SfxApplication-Subklasse einen DDE-Hotlink einzurichten
//STRIP001
//STRIP001  Die Basisimplementierung erzeugt keinen und liefert 0 zur"uck.
//STRIP001 */
//STRIP001
//STRIP001 {
//STRIP001  return 0;
//STRIP001 }

//========================================================================

/*?*/ long SfxObjectShell::DdeExecute
/*?*/ (
/*?*/   const String&   rCmd        // in unserer BASIC-Syntax formuliert
/*?*/ )

//STRIP001 /*   [Beschreibung]
//STRIP001
//STRIP001  Diese Methode kann vom Applikationsentwickler "uberladen werden,
//STRIP001  um an seine SfxObjectShell-Subklasse gerichtete DDE-Kommandos
//STRIP001  zu empfangen.
//STRIP001
//STRIP001  Die Basisimplementierung f"uhrt nichts aus und liefert 0 zur"uck.
//STRIP001 */
//STRIP001
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001
//STRIP001  StarBASIC* pBasic = GetBasic();
//STRIP001  DBG_ASSERT( pBasic, "Wo ist mein Basic???" ) ;
//STRIP001  SbxVariable* pRet = pBasic->Execute( rCmd );
//STRIP001  if( !pRet )
//STRIP001  {
//STRIP001      SbxBase::ResetError();
//STRIP001      return 0;
//STRIP001  }
//STRIP001
//STRIP001  return 1;
/*?*/ }

//--------------------------------------------------------------------

/*?*/ long SfxObjectShell::DdeGetData
/*?*/ (
/*?*/   const String&   rItem,                      // das anzusprechende Item
/*?*/   const String& rMimeType,                    // in: Format
/*?*/   ::com::sun::star::uno::Any & rValue     // out: angeforderte Daten
/*?*/ )
//STRIP001
//STRIP001 /*   [Beschreibung]
//STRIP001
//STRIP001  Diese Methode kann vom Applikationsentwickler "uberladen werden,
//STRIP001  um an seine SfxObjectShell-Subklasse gerichtete DDE-Daten-Anforderungen
//STRIP001  zu empfangen.
//STRIP001
//STRIP001  Die Basisimplementierung liefert keine Daten und gibt 0 zur"uck.
//STRIP001 */
//STRIP001
{DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001
//STRIP001  return 0;
/*?*/ }

//--------------------------------------------------------------------

/*?*/ long SfxObjectShell::DdeSetData
/*?*/ (
/*?*/   const String&   rItem,                      // das anzusprechende Item
/*?*/   const String& rMimeType,                    // in: Format
/*?*/   const ::com::sun::star::uno::Any & rValue   // out: angeforderte Daten
/*?*/ )
/*?*/
/*  [Beschreibung]

    Diese Methode kann vom Applikationsentwickler "uberladen werden,
    um an seine SfxObjectShell-Subklasse gerichtete DDE-Daten
    zu empfangen.

    Die Basisimplementierung nimmt keine Daten entgegen und liefert 0 zur"uck.
*/
/*?*/
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001
//STRIP001  return 0;
/*?*/ }

//--------------------------------------------------------------------

/*?*/ ::so3::SvLinkSource* SfxObjectShell::DdeCreateLinkSource
/*?*/ (
/*?*/   const String&   rItem      // das zu erzeugende Item
/*?*/ )

//STRIP001 /*   [Beschreibung]
//STRIP001
//STRIP001  Diese Methode kann vom Applikationsentwickler "uberladen werden,
//STRIP001  um an seiner SfxObjectShell-Subklasse einen DDE-Hotlink einzurichten
//STRIP001
//STRIP001  Die Basisimplementierung erzeugt keinen und liefert 0 zur"uck.
//STRIP001 */
//STRIP001
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001
//STRIP001  return 0;
/*?*/ }

//========================================================================

/*?*/ long SfxViewFrame::DdeExecute
/*?*/ (
/*?*/   const String&   rCmd        // in unserer BASIC-Syntax formuliert
/*?*/ )
//STRIP001
//STRIP001 /*   [Beschreibung]
//STRIP001
//STRIP001  Diese Methode kann vom Applikationsentwickler "uberladen werden,
//STRIP001  um an seine SfxViewFrame-Subklasse gerichtete DDE-Kommandos
//STRIP001  zu empfangen.
//STRIP001
//STRIP001  Die Basisimplementierung versteht die API-Funktionalit"at des
//STRIP001  betreffenden SfxViewFrame, der darin dargestellten SfxViewShell und
//STRIP001  der betreffenden SfxObjectShell-Subklasse in BASIC-Syntax.
//STRIP001  R"uckgabewerte k"onnen dabei leider nicht "ubertragen werden.
//STRIP001 */
//STRIP001
{DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001
//STRIP001  if ( GetObjectShell() )
//STRIP001      return GetObjectShell()->DdeExecute( rCmd );
//STRIP001
//STRIP001  return 0;
/*?*/ }

//--------------------------------------------------------------------

/*?*/ long SfxViewFrame::DdeGetData
/*?*/ (
/*?*/   const String&   rItem,                  // das anzusprechende Item
/*?*/   const String& rMimeType,                // in: Format
/*?*/   ::com::sun::star::uno::Any & rValue     // out: angeforderte Daten
/*?*/ )
//STRIP001
//STRIP001 /*   [Beschreibung]
//STRIP001
//STRIP001  Diese Methode kann vom Applikationsentwickler "uberladen werden,
//STRIP001  um an seine SfxViewFrame-Subklasse gerichtete DDE-Daten-Anforderungen
//STRIP001  zu empfangen.
//STRIP001
//STRIP001  Die Basisimplementierung liefert keine Daten und gibt 0 zur"uck.
//STRIP001 */
//STRIP001
{DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001
//STRIP001  return 0;
/*?*/ }

//--------------------------------------------------------------------

/*?*/ long SfxViewFrame::DdeSetData
/*?*/ (
/*?*/   const String&   rItem,                      // das anzusprechende Item
/*?*/   const String& rMimeType,                    // in: Format
/*?*/   const ::com::sun::star::uno::Any & rValue   // out: angeforderte Daten
/*?*/ )
//STRIP001
//STRIP001 /*   [Beschreibung]
//STRIP001
//STRIP001  Diese Methode kann vom Applikationsentwickler "uberladen werden,
//STRIP001  um an seine SfxViewFrame-Subklasse gerichtete DDE-Daten
//STRIP001  zu empfangen.
//STRIP001
//STRIP001  Die Basisimplementierung nimmt keine Daten entgegen und liefert 0 zur"uck.
//STRIP001 */
//STRIP001
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001
//STRIP001  return 0;
/*?*/ }

//--------------------------------------------------------------------

/*?*/ ::so3::SvLinkSource* SfxViewFrame::DdeCreateLinkSource
/*?*/ (
/*?*/   const String&   rItem      // das zu erzeugende Item
/*?*/ )
//STRIP001
//STRIP001 /*   [Beschreibung]
//STRIP001
//STRIP001  Diese Methode kann vom Applikationsentwickler "uberladen werden,
//STRIP001  um an seiner SfxViewFrame-Subklasse einen DDE-Hotlink einzurichten
//STRIP001
//STRIP001  Die Basisimplementierung erzeugt keinen und liefert 0 zur"uck.
//STRIP001 */
//STRIP001
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001
//STRIP001  return 0;
/*?*/ }


//========================================================================

/*N*/ BOOL SfxApplication::InitializeDde()
/*N*/ {
/*N*/   DBG_ASSERT( !pAppData_Impl->pDdeService,
/*N*/               "Dde kann nicht mehrfach initialisiert werden" )
/*N*/
/*N*/   pAppData_Impl->pDdeService = new ImplDdeService( Application::GetAppName() );
/*N*/   int nError = pAppData_Impl->pDdeService->GetError();
/*N*/   if( !nError )
/*N*/   {
/*N*/       pAppData_Impl->pDocTopics = new SfxDdeDocTopics_Impl;
/*N*/
/*N*/       // wir wollen auf jedenfall RTF unterstuetzen!
/*N*/       pAppData_Impl->pDdeService->AddFormat( FORMAT_RTF );
/*N*/
/*N*/       // Config-Pfad als Topic wegen Mehrfachstart
/*N*/         INetURLObject aOfficeLockFile( SvtPathOptions().GetUserConfigPath() );
/*N*/       aOfficeLockFile.insertName( DEFINE_CONST_UNICODE( "soffice.lck" ) );
/*N*/         String aService( SfxDdeServiceName_Impl(
/*N*/                   aOfficeLockFile.GetMainURL(INetURLObject::DECODE_TO_IURI) ) );
/*N*/       aService.ToUpperAscii();
/*N*/       pAppData_Impl->pDdeService2 = new ImplDdeService( aService );
/*N*/       pAppData_Impl->pTriggerTopic = new SfxDdeTriggerTopic_Impl;
/*N*/       pAppData_Impl->pDdeService2->AddTopic( *pAppData_Impl->pTriggerTopic );
/*N*/   }
/*N*/   return !nError;
/*N*/ }

/*N*/ void SfxAppData_Impl::DeInitDDE()
/*N*/ {
/*N*/     DELETEZ( pTriggerTopic );
/*N*/     DELETEZ( pDdeService2 );
/*N*/     DELETEZ( pDocTopics );
/*N*/     DELETEZ( pDdeService );
/*N*/ }

//--------------------------------------------------------------------

//STRIP001 void SfxApplication::AddDdeTopic( SfxObjectShell* pSh )
//STRIP001 {
//STRIP001  DBG_ASSERT( pAppData_Impl->pDocTopics, "es gibt gar keinen Dde-Service" )
//STRIP001  //OV: Im Serverbetrieb ist DDE abgeklemmt!
//STRIP001  if( !pAppData_Impl->pDocTopics )
//STRIP001      return;
//STRIP001
//STRIP001  // doppeltes Eintragen verhindern
//STRIP001  String sShellNm;
//STRIP001  BOOL bFnd = FALSE;
//STRIP001  for( USHORT n = pAppData_Impl->pDocTopics->Count(); n; )
//STRIP001      if( (*pAppData_Impl->pDocTopics)[ --n ]->pSh == pSh )
//STRIP001      {
//STRIP001          // JP 18.03.96 - Bug 26470
//STRIP001          //  falls das Document unbenannt wurde, ist trotzdem ein
//STRIP001          //  neues Topics anzulegen!
//STRIP001          if( !bFnd )
//STRIP001          {
//STRIP001              bFnd = TRUE;
//STRIP001              (sShellNm = pSh->GetTitle(SFX_TITLE_FULLNAME)).ToLowerAscii();
//STRIP001          }
//STRIP001          String sNm( (*pAppData_Impl->pDocTopics)[ n ]->GetName() );
//STRIP001          if( sShellNm == sNm.ToLowerAscii() )
//STRIP001              return ;
//STRIP001      }
//STRIP001
//STRIP001  const SfxDdeDocTopic_Impl* pTopic = new SfxDdeDocTopic_Impl( pSh );
//STRIP001  pAppData_Impl->pDocTopics->Insert( pTopic,
//STRIP001                                     pAppData_Impl->pDocTopics->Count() );
//STRIP001  pAppData_Impl->pDdeService->AddTopic( *pTopic );
//STRIP001 }

/*N*/ void SfxApplication::RemoveDdeTopic( SfxObjectShell* pSh )
/*N*/ {
/*N*/   DBG_ASSERT( pAppData_Impl->pDocTopics, "es gibt gar keinen Dde-Service" )
/*N*/   //OV: Im Serverbetrieb ist DDE abgeklemmt!
/*N*/   if( !pAppData_Impl->pDocTopics )
/*N*/       return;
/*N*/
/*N*/   SfxDdeDocTopic_Impl* pTopic;
/*N*/   for( USHORT n = pAppData_Impl->pDocTopics->Count(); n; )
/*?*/       if( ( pTopic = (*pAppData_Impl->pDocTopics)[ --n ])->pSh == pSh )
/*?*/       {
/*?*/           pAppData_Impl->pDdeService->RemoveTopic( *pTopic );
/*?*/           pAppData_Impl->pDocTopics->DeleteAndDestroy( n );
/*?*/       }
/*N*/ }

//STRIP001 const DdeService* SfxApplication::GetDdeService() const
//STRIP001 {
//STRIP001  return pAppData_Impl->pDdeService;
//STRIP001 }

/*N*/ DdeService* SfxApplication::GetDdeService()
/*N*/ {
/*N*/   return pAppData_Impl->pDdeService;
/*N*/ }

//--------------------------------------------------------------------

/*?*/ BOOL ImplDdeService::MakeTopic( const String& rNm )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001
//STRIP001  // Workaround gegen Event nach unserem Main() unter OS/2
//STRIP001  // passierte wenn man beim Beenden aus dem OffMgr die App neu startet
//STRIP001  if ( !Application::IsInExecute() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  // das Topic rNm wird gesucht, haben wir es ?
//STRIP001  // erstmal nur ueber die ObjectShells laufen und die mit dem
//STRIP001  // Namen heraussuchen:
//STRIP001  BOOL bRet = FALSE;
//STRIP001  String sNm( rNm );
//STRIP001  sNm.ToLowerAscii();
//STRIP001  TypeId aType( TYPE(SfxObjectShell) );
//STRIP001  SfxObjectShell* pShell = SfxObjectShell::GetFirst( &aType );
//STRIP001  while( pShell )
//STRIP001  {
//STRIP001      String sTmp( pShell->GetTitle(SFX_TITLE_FULLNAME) );
//STRIP001      sTmp.ToLowerAscii();
//STRIP001      if( sTmp == sNm )       // die wollen wir haben
//STRIP001      {
//STRIP001          SFX_APP()->AddDdeTopic( pShell );
//STRIP001          bRet = TRUE;
//STRIP001          break;
//STRIP001      }
//STRIP001      pShell = SfxObjectShell::GetNext( *pShell, &aType );
//STRIP001  }
//STRIP001
//STRIP001  if( !bRet )
//STRIP001  {
//STRIP001         INetURLObject aWorkPath( SvtPathOptions().GetWorkPath() );
//STRIP001      INetURLObject aFile;
//STRIP001      if ( aWorkPath.GetNewAbsURL( rNm, &aFile ) &&
//STRIP001           SfxContentHelper::IsDocument( aFile.GetMainURL( INetURLObject::NO_DECODE ) ) )
//STRIP001      {
//STRIP001          // File vorhanden
//STRIP001
//STRIP001          // dann versuche die Datei zu laden:
//STRIP001          SfxStringItem aName( SID_FILE_NAME, aFile.GetMainURL( INetURLObject::NO_DECODE ) );
//STRIP001          SfxBoolItem aNewView(SID_OPEN_NEW_VIEW, TRUE);
//STRIP001 //           SfxBoolItem aHidden(SID_HIDDEN, TRUE);
//STRIP001          // minimiert!
//STRIP001          SfxUInt16Item aViewStat( SID_VIEW_ZOOM_MODE, 0 );
//STRIP001          SfxRectangleItem aRectItem( SID_VIEW_POS_SIZE, Rectangle() );
//STRIP001
//STRIP001          SfxBoolItem aSilent(SID_SILENT, TRUE);
//STRIP001             SfxDispatcher* pDispatcher = SFX_APP()->GetDispatcher_Impl();
//STRIP001             const SfxPoolItem* pRet = pDispatcher->Execute( SID_OPENDOC,
//STRIP001                  SFX_CALLMODE_SYNCHRON,
//STRIP001                  &aName, &aNewView,
//STRIP001                  &aViewStat,&aRectItem/*aHidden*/,
//STRIP001                  &aSilent, 0L );
//STRIP001
//STRIP001          if( pRet && pRet->ISA( SfxViewFrameItem ) &&
//STRIP001              ((SfxViewFrameItem*)pRet)->GetFrame() &&
//STRIP001              0 != ( pShell = ((SfxViewFrameItem*)pRet)
//STRIP001                  ->GetFrame()->GetObjectShell() ) )
//STRIP001          {
//STRIP001              SFX_APP()->AddDdeTopic( pShell );
//STRIP001              bRet = TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return bRet;
/*?*/ }

/*?*/ String ImplDdeService::Topics()
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); String aRet; return aRet;//STRIP001
//STRIP001  String sRet;
//STRIP001  if( GetSysTopic() )
//STRIP001      sRet += GetSysTopic()->GetName();
//STRIP001
//STRIP001  TypeId aType( TYPE(SfxObjectShell) );
//STRIP001  SfxObjectShell* pShell = SfxObjectShell::GetFirst( &aType );
//STRIP001  while( pShell )
//STRIP001  {
//STRIP001      if( SfxViewFrame::GetFirst( pShell, TYPE(SfxTopViewFrame) ))
//STRIP001      {
//STRIP001          if( sRet.Len() )
//STRIP001              sRet += '\t';
//STRIP001          sRet += pShell->GetTitle(SFX_TITLE_FULLNAME);
//STRIP001      }
//STRIP001      pShell = SfxObjectShell::GetNext( *pShell, &aType );
//STRIP001  }
//STRIP001  if( sRet.Len() )
//STRIP001      sRet += DEFINE_CONST_UNICODE("\r\n");
//STRIP001  return sRet;
/*?*/ }

/*?*/ BOOL ImplDdeService::SysTopicExecute( const String* pStr )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001
//STRIP001  return (BOOL)SFX_APP()->DdeExecute( *pStr );
/*?*/ }

//--------------------------------------------------------------------

/*?*/ BOOL SfxDdeTriggerTopic_Impl::Execute( const String* pStr )
{DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001
//STRIP001 //    Application::GetAppWindow()->ToTop(TOTOP_RESTOREWHENMIN);
//STRIP001  return TRUE;
/*?*/ }

//--------------------------------------------------------------------
/*?*/ DdeData* SfxDdeDocTopic_Impl::Get( ULONG nFormat )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return NULL;//STRIP001
//STRIP001  String sMimeType( SotExchange::GetFormatMimeType( nFormat ));
//STRIP001  ::com::sun::star::uno::Any aValue;
//STRIP001  long nRet = pSh->DdeGetData( GetCurItem(), sMimeType, aValue );
//STRIP001  if( nRet && aValue.hasValue() && ( aValue >>= aSeq ) )
//STRIP001  {
//STRIP001      aData = DdeData( aSeq.getConstArray(), aSeq.getLength(), nFormat );
//STRIP001      return &aData;
//STRIP001  }
//STRIP001  aSeq.realloc( 0 );
//STRIP001  return 0;
/*?*/ }

/*?*/ BOOL SfxDdeDocTopic_Impl::Put( const DdeData* pData )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001
//STRIP001  aSeq = ::com::sun::star::uno::Sequence< sal_Int8 >(
//STRIP001                          (sal_Int8*)(const void*)*pData, (long)*pData );
//STRIP001  BOOL bRet;
//STRIP001  if( aSeq.getLength() )
//STRIP001  {
//STRIP001      ::com::sun::star::uno::Any aValue;
//STRIP001      aValue <<= aSeq;
//STRIP001      String sMimeType( SotExchange::GetFormatMimeType( pData->GetFormat() ));
//STRIP001      bRet = 0 != pSh->DdeSetData( GetCurItem(), sMimeType, aValue );
//STRIP001  }
//STRIP001  else
//STRIP001      bRet = FALSE;
//STRIP001  return bRet;
/*?*/ }

/*?*/ BOOL SfxDdeDocTopic_Impl::Execute( const String* pStr )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001
//STRIP001  long nRet = pStr ? pSh->DdeExecute( *pStr ) : 0;
//STRIP001  return 0 != nRet;
/*?*/ }

/*?*/ BOOL SfxDdeDocTopic_Impl::MakeItem( const String& rItem )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001
//STRIP001  AddItem( DdeItem( rItem ) );
//STRIP001  return TRUE;
/*?*/ }

/*?*/ BOOL SfxDdeDocTopic_Impl::StartAdviseLoop()
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001
//STRIP001  BOOL bRet = FALSE;
//STRIP001  ::so3::SvLinkSource* pNewObj = pSh->DdeCreateLinkSource( GetCurItem() );
//STRIP001  if( pNewObj )
//STRIP001  {
//STRIP001      // dann richten wir auch einen entsprechenden SvBaseLink ein
//STRIP001      String sNm, sTmp( Application::GetAppName() );
//STRIP001      ::so3::MakeLnkName( sNm, &sTmp, pSh->GetTitle(SFX_TITLE_FULLNAME), GetCurItem() );
//STRIP001      new ::so3::SvBaseLink( sNm, OBJECT_DDE_EXTERN, pNewObj );
//STRIP001      bRet = TRUE;
//STRIP001  }
//STRIP001  return bRet;
/*?*/ }


}
