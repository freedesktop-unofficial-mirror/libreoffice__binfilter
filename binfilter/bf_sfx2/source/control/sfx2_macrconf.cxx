/*************************************************************************
 *
 *  $RCSfile: sfx2_macrconf.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:06 $
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

#ifndef _SB_SBSTAR_HXX //autogen
#include <basic/sbstar.hxx>
#endif
#ifndef _BASMGR_HXX //autogen
#include <basic/basmgr.hxx>
#endif
#ifndef _SBX_HXX //autogen
#include <svtools/sbx.hxx>
#endif
#ifndef _SFXINTITEM_HXX //autogen
#include <svtools/intitem.hxx>
#endif
#ifndef _SB_SBMETH_HXX //autogen
#include <basic/sbmeth.hxx>
#endif
#ifndef _SB_SBMOD_HXX //autogen
#include <basic/sbmod.hxx>
#endif
#ifndef _BASIC_SBUNO_HXX
#include <basic/sbuno.hxx>
#endif

#include <osl/mutex.hxx>

#include <com/sun/star/script/XEngine.hpp>

#ifndef _COM_SUN_STAR_DOCUMENT_MACROEXECMODE_HPP_
#include <com/sun/star/document/MacroExecMode.hpp>
#endif

#pragma hdrstop

#ifndef _UNOTOOLS_PROCESSFACTORY_HXX
#include <comphelper/processfactory.hxx>
#endif
#ifndef _UNOTOOLS_INTLWRAPPER_HXX
#include <unotools/intlwrapper.hxx>
#endif

#include "msgpool.hxx"
#include "macrconf.hxx"
#include "sfxbasic.hxx"
#include "sfx.hrc"
#include "app.hxx"
#include "objsh.hxx"
#include "dispatch.hxx"
#include "minfitem.hxx"
#include "imgmgr.hxx"
#include "evntconf.hxx"
#include "docfile.hxx"
#include "genlink.hxx"
#include <viewfrm.hxx>
#include <appdata.hxx>
#include "objshimp.hxx"
#include "request.hxx"

#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif

static const sal_uInt16 nCompatVersion = 2;
static const sal_uInt16 nVersion = 3;

// Static member
SfxMacroConfig* SfxMacroConfig::pMacroConfig = NULL;

/*N*/ SfxMacroConfig* SfxMacroConfig::GetOrCreate()
/*N*/ {DBG_ASSERT(0, "STRIP"); return 0;//STRIP001
//STRIP001  ::osl::MutexGuard aGuard( ::osl::Mutex::getGlobalMutex() );
//STRIP001  if ( !pMacroConfig )
//STRIP001      pMacroConfig = new SfxMacroConfig;
//STRIP001  return pMacroConfig;
/*N*/ }

/*N*/ void SfxMacroConfig::Release_Impl()
/*N*/ {
/*N*/   ::osl::MutexGuard aGuard( ::osl::Mutex::getGlobalMutex() );
/*N*/   DELETEZ( pMacroConfig );
/*N*/ }

//==========================================================================

/*?*/ struct SfxMacroConfig_Impl
/*?*/ {
/*?*/   SfxMacroInfoArr_Impl    aArr;
/*?*/   sal_uInt32                  nEventId;
/*?*/   sal_Bool                    bWaitingForCallback;
/*?*/
/*?*/                           SfxMacroConfig_Impl()
/*?*/                           : nEventId( 0 )
/*?*/                           , bWaitingForCallback( sal_False )
/*?*/                           {}
/*?*/ };

//==========================================================================

/*?*/ SbMethod* SfxQueryMacro_Impl( BasicManager* pMgr , const String& rMacro,
/*?*/   const String &rLibName, const String& rModule )
/*?*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  IntlWrapper aIntlWrapper( ::legacy_binfilters::getLegacyProcessServiceFactory(), Application::GetSettings().GetLocale() );
//STRIP001  const CollatorWrapper* pCollator = aIntlWrapper.getCollator();
//STRIP001  sal_uInt16 nLibCount = pMgr->GetLibCount();
//STRIP001  for ( sal_uInt16 nLib = 0; nLib < nLibCount; ++nLib )
//STRIP001  {
//STRIP001      if ( COMPARE_EQUAL == pCollator->compareString( pMgr->GetLibName( nLib ), rLibName ) )
//STRIP001      {
//STRIP001          StarBASIC* pLib = pMgr->GetLib( nLib );
//STRIP001          if( !pLib )
//STRIP001          {
//STRIP001              pMgr->LoadLib( nLib );
//STRIP001              pLib = pMgr->GetLib( nLib );
//STRIP001          }
//STRIP001
//STRIP001          if( pLib )
//STRIP001          {
//STRIP001              sal_uInt16 nModCount = pLib->GetModules()->Count();
//STRIP001              for( sal_uInt16 nMod = 0; nMod < nModCount; ++nMod )
//STRIP001              {
//STRIP001                  SbModule* pMod = (SbModule*)pLib->GetModules()->Get( nMod );
//STRIP001                  if ( pMod && COMPARE_EQUAL == pCollator->compareString( pMod->GetName(), rModule ) )
//STRIP001                  {
//STRIP001                      SbMethod* pMethod = (SbMethod*)pMod->Find( rMacro, SbxCLASS_METHOD );
//STRIP001                      if( pMethod )
//STRIP001                          return pMethod;
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
/*?*/   return 0;
/*?*/ }

/*?*/ SbMethod* SfxQueryMacro( BasicManager* pMgr , const String& rMacro )
/*?*/ {DBG_ASSERT(0, "STRIP"); return NULL;//STRIP001
//STRIP001  sal_uInt16 nLast = 0;
//STRIP001  String aMacro = rMacro;
//STRIP001  String aLibName = aMacro.GetToken( 0, '.', nLast );
//STRIP001  String aModule = aMacro.GetToken( 0, '.', nLast );
//STRIP001  aMacro.Erase( 0, nLast );
//STRIP001
//STRIP001  return SfxQueryMacro_Impl( pMgr, aMacro, aLibName, aModule );
/*?*/ }

/*?*/ ErrCode SfxCallMacro( BasicManager* pMgr, const String& rCode,
/*?*/                     SbxArray *pArgs, SbxValue *pRet )
/*?*/ {DBG_ASSERT(0, "STRIP"); return 0;//STRIP001
//STRIP001  ErrCode nErr;
//STRIP001  SfxApplication *pApp = SFX_APP();
//STRIP001  pApp->EnterBasicCall();
//STRIP001  SbMethod* pMethod = SfxQueryMacro( pMgr, rCode );
//STRIP001  if ( pMethod )
//STRIP001  {
//STRIP001      if ( pArgs )
//STRIP001          pMethod->SetParameters( pArgs );
//STRIP001      nErr = pMethod->Call( pRet );
//STRIP001  }
//STRIP001  else
//STRIP001      nErr = ERRCODE_BASIC_PROC_UNDEFINED;
//STRIP001
//STRIP001  pApp->LeaveBasicCall();
//STRIP001  return nErr;
/*?*/ }

//==========================================================================

/*?*/ SfxMacroInfo::SfxMacroInfo( const String& rURL ) :
/*?*/     bAppBasic(TRUE),
/*?*/   nSlotId(0),
/*?*/   nRefCnt(0),
/*?*/   pSlot(0),
/*?*/   pHelpText(0)
/*?*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001     if ( rURL.CompareToAscii( "macro:", 6 ) == COMPARE_EQUAL )
//STRIP001     {
//STRIP001         String aTmp = rURL.Copy( 6 );
//STRIP001         if ( aTmp.GetTokenCount('/') > 3 )
//STRIP001         {
//STRIP001             // 'macro:///lib.mod.proc(args)' => Macro via App-BASIC-Mgr
//STRIP001             // 'macro://[docname|.]/lib.mod.proc(args)' => Macro via zugehoerigen Doc-BASIC-Mgr
//STRIP001             if ( aTmp.CompareToAscii("///", 3 ) != COMPARE_EQUAL )
//STRIP001                 bAppBasic = FALSE;
//STRIP001             aTmp = rURL.GetToken( 3, '/' );
//STRIP001             if ( aTmp.GetTokenCount('.') == 3 )
//STRIP001             {
//STRIP001                 aLibName = aTmp.GetToken( 0, '.' );
//STRIP001                 aModuleName = aTmp.GetToken( 1, '.' );
//STRIP001                 aMethodName = aTmp.GetToken( 2, '.' );
//STRIP001
//STRIP001              // Remove arguments to be compatible
//STRIP001              aMethodName.SearchAndReplaceAscii( "()", String(), std::max( aMethodName.Len()-2, 0 ));
//STRIP001             }
//STRIP001         }
//STRIP001
//STRIP001      DBG_ASSERT( aLibName.Len() && aModuleName.Len() && aMethodName.Len(), "Wrong macro URL!" );
//STRIP001     }
//STRIP001  else
//STRIP001      aMethodName = rURL;
/*?*/ }

/*?*/ SfxMacroInfo::SfxMacroInfo( SfxObjectShell *pDoc ) :
/*?*/   bAppBasic(pDoc == NULL),
/*?*/   nSlotId(0),
/*?*/   nRefCnt(0),
/*?*/   pSlot(0),
/*?*/   pHelpText(0)
/*?*/ {}

//==========================================================================

/*?*/ SfxMacroInfo::SfxMacroInfo(SfxObjectShell *pDoc, const String& rLibName,
/*?*/       const String& rModuleName, const String& rMethodName) :
/*?*/   aLibName(rLibName),
/*?*/   aModuleName(rModuleName),
/*?*/   aMethodName(rMethodName),
/*?*/   nSlotId(0),
/*?*/   nRefCnt(0),
/*?*/   pSlot(0),
/*?*/   pHelpText(0)
/*?*/ {
/*?*/   bAppBasic = (pDoc == 0);
/*?*/ }

//==========================================================================

/*?*/ SfxMacroInfo::SfxMacroInfo(SfxObjectShell *pDoc, const String& rQualifiedName )
/*?*/ : nSlotId(0),
/*?*/   nRefCnt(0),
/*?*/   pSlot(0),
/*?*/   pHelpText(0)
/*?*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  sal_uInt16 nCount = rQualifiedName.GetTokenCount('.');
//STRIP001  aMethodName = rQualifiedName.GetToken( nCount-1, '.' );
//STRIP001  if ( nCount > 1 )
//STRIP001      aModuleName = rQualifiedName.GetToken( nCount-2, '.' );
//STRIP001  if ( nCount > 2 )
//STRIP001      aLibName = rQualifiedName.GetToken( 0, '.' );
//STRIP001  bAppBasic = (pDoc == 0);
/*?*/ }

//==========================================================================

/*?*/ SfxMacroInfo::SfxMacroInfo(SfxMacroInfo& rOther) :
/*?*/   bAppBasic(rOther.bAppBasic),
/*?*/   aLibName(rOther.aLibName),
/*?*/   aModuleName(rOther.aModuleName),
/*?*/   aMethodName(rOther.aMethodName),
/*?*/   nSlotId(rOther.nSlotId),
/*?*/   pSlot(0),
/*?*/   nRefCnt(0),
/*?*/   pHelpText(0)
/*?*/ {}

//==========================================================================

/*?*/ SfxMacroInfo::~SfxMacroInfo()
/*?*/ {
/*?*/   delete pSlot;
/*?*/   delete pHelpText;
/*?*/ }

//==========================================================================

/*?*/ sal_Bool SfxMacroInfo::operator==(const SfxMacroInfo& rOther) const
/*?*/ {DBG_ASSERT(0, "STRIP"); return FALSE;//STRIP001
//STRIP001  if ( GetQualifiedName() == rOther.GetQualifiedName() &&
//STRIP001          bAppBasic   == rOther.bAppBasic )
//STRIP001      return sal_True;
//STRIP001  else
//STRIP001      return sal_False;
/*?*/ }

//==========================================================================

/*?*/ String SfxMacroInfo::GetMacroName() const
/*?*/ {DBG_ASSERT(0, "STRIP");return String(); //STRIP001
//STRIP001  String aMacroName = aMethodName;
//STRIP001  aMacroName += '(';
//STRIP001  aMacroName += aLibName;
//STRIP001  aMacroName += '.';
//STRIP001  aMacroName += aModuleName;
//STRIP001  aMacroName += ')';
//STRIP001  return aMacroName;
/*?*/ }

//==========================================================================

/*?*/ String SfxMacroInfo::GetQualifiedName() const
/*?*/ {DBG_ASSERT(0, "STRIP");return String();
//STRIP001  String aMacroName;
//STRIP001  if( aMacroName.Len() || aLibName.Len() )
//STRIP001  {
//STRIP001      // Altes Format
//STRIP001      aMacroName = aLibName;
//STRIP001      aMacroName += '.';
//STRIP001      aMacroName += aModuleName;
//STRIP001      aMacroName += '.';
//STRIP001  }
//STRIP001
//STRIP001  // Wg. ::com::sun::star::script::JavaScript kein Zerlegen des Strings mehr
//STRIP001  aMacroName += aMethodName;
//STRIP001  return aMacroName;
/*?*/ }

/*?*/ String SfxMacroInfo::GetFullQualifiedName() const
/*?*/ {DBG_ASSERT(0, "STRIP");return String();
//STRIP001  // Liefert nur Unsinn, wenn f"ur ein ::com::sun::star::script::JavaScript aufgerufen !
//STRIP001  String aRet;
//STRIP001  if ( bAppBasic )
//STRIP001      aRet = SFX_APP()->GetName();
//STRIP001  aRet += '.';
//STRIP001  aRet += GetQualifiedName();
//STRIP001  return aRet;
/*?*/ }

/*?*/ String SfxMacroInfo::GetURL() const
/*?*/ {DBG_ASSERT(0, "STRIP");return String();
//STRIP001  if ( !aLibName.Len() )
//STRIP001      return aMethodName;
//STRIP001
//STRIP001     // 'macro:///lib.mod.proc(args)' => Macro via App-BASIC-Mgr
//STRIP001     // 'macro://[docname|.]/lib.mod.proc(args)' => Macro via zugehoerigen Doc-BASIC-Mgr
//STRIP001     // 'macro://obj.method(args)' => Object via App-BASIC-Mgr
//STRIP001     String aURL( String::CreateFromAscii("macro://") );
//STRIP001     if ( !bAppBasic )
//STRIP001         aURL += '.';
//STRIP001     aURL += '/';
//STRIP001     aURL += aLibName;
//STRIP001     aURL += '.';
//STRIP001     aURL += aModuleName;
//STRIP001     aURL += '.';
//STRIP001     aURL += aMethodName;
//STRIP001     aURL += String::CreateFromAscii("()");
//STRIP001
//STRIP001     return aURL;
/*?*/ }

//==========================================================================

/*?*/ BasicManager* SfxMacroInfo::GetBasicManager() const
/*?*/ {DBG_ASSERT(0, "STRIP");return NULL; //STRIP001
//STRIP001  if (bAppBasic)
//STRIP001  {
//STRIP001      return SFX_APP()->GetBasicManager();
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      SfxObjectShell *pDocShell = SfxObjectShell::Current();
//STRIP001      return pDocShell ? pDocShell->GetBasicManager() :
//STRIP001                     SFX_APP()->GetBasicManager();
//STRIP001  }
/*?*/ }

//==========================================================================

/*?*/ String SfxMacroInfo::GetBasicName() const
/*?*/ {DBG_ASSERT(0, "STRIP");return String();//STRIP001
//STRIP001  if (bAppBasic)
//STRIP001  {
//STRIP001      return SFX_APP()->GetName();
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      SfxObjectShell *pDocShell = SfxObjectShell::Current();
//STRIP001      if ( pDocShell )
//STRIP001          return pDocShell->GetTitle();
//STRIP001      else
//STRIP001          return SFX_APP()->GetName();
//STRIP001  }
/*?*/ }

/*?*/ String SfxMacroInfo::GetHelpText() const
/*?*/ {DBG_ASSERT(0, "STRIP");return String();
    //STRIP001 if ( pHelpText )
//STRIP001      return *pHelpText;
//STRIP001  return String();
/*?*/ }

/*?*/ String SfxMacroConfig::RequestHelp( sal_uInt16 nId )
/*?*/ {DBG_ASSERT(0, "STRIP");return String();
//STRIP001  SfxMacroInfo *pInfo = SFX_APP()->GetMacroConfig()->GetMacroInfo( nId );
//STRIP001  if ( !pInfo )
//STRIP001      return String();
//STRIP001
//STRIP001  if ( !pInfo->pHelpText )
//STRIP001  {
//STRIP001      SbMethod *pMethod =
//STRIP001          SfxQueryMacro_Impl( pInfo->GetBasicManager(), pInfo->aMethodName,
//STRIP001              pInfo->aLibName, pInfo->aModuleName );
//STRIP001      if ( pMethod && pMethod->GetInfo() )
//STRIP001          pInfo->pHelpText = new String( pMethod->GetInfo()->GetComment() );
//STRIP001  }
//STRIP001
//STRIP001  return pInfo->GetHelpText();
/*?*/ }

/*?*/ void SfxMacroInfo::SetHelpText( const String& rName )
/*?*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  if ( !pHelpText )
//STRIP001      pHelpText = new String;
//STRIP001  *pHelpText = rName;
/*?*/ }

//==========================================================================

/*?*/ SvStream& operator >> (SvStream& rStream, SfxMacroInfo& rInfo)
/*?*/ {
/*?*/   sal_uInt16 nAppBasic, nFileVersion;
/*?*/   String aDocName;
/*?*/
/*?*/   rStream >> nFileVersion;
/*?*/   if ( nVersion < nCompatVersion )
/*?*/   {
/*?*/       // In der 1.Version ohne Versionskennung
/*?*/       nAppBasic = nVersion;
/*?*/       nFileVersion = 1;
/*?*/       rStream.ReadByteString(aDocName,RTL_TEXTENCODING_UTF8);
/*?*/       rStream.ReadByteString(rInfo.aLibName,RTL_TEXTENCODING_UTF8);
/*?*/       rStream.ReadByteString(rInfo.aModuleName,RTL_TEXTENCODING_UTF8);
/*?*/       rStream.ReadByteString(rInfo.aMethodName,RTL_TEXTENCODING_UTF8);
/*?*/   }
/*?*/   else
/*?*/   {
/*?*/       String aInput;
/*?*/       rStream >> nAppBasic;
/*?*/       rStream.ReadByteString(aDocName,RTL_TEXTENCODING_UTF8);                 // Vorsicht: kann bei AppName Unsinn sein!
/*?*/       rStream.ReadByteString(rInfo.aLibName,RTL_TEXTENCODING_UTF8);
/*?*/       rStream.ReadByteString(rInfo.aModuleName,RTL_TEXTENCODING_UTF8);
/*?*/       rStream.ReadByteString(aInput,RTL_TEXTENCODING_UTF8);
/*?*/
/*?*/       if ( nFileVersion == nCompatVersion )
/*?*/           rInfo.aMethodName = aInput;
/*?*/       else
/*?*/       {
/*?*/           sal_uInt16 nCount = aInput.GetTokenCount('.');
/*?*/           rInfo.aMethodName = aInput.GetToken( nCount-1, '.' );
/*?*/           if ( nCount > 1 )
/*?*/               rInfo.aModuleName = aInput.GetToken( nCount-2, '.' );
/*?*/           if ( nCount > 2 )
/*?*/               rInfo.aLibName = aInput.GetToken( 0, '.' );
/*?*/       }
/*?*/   }
/*?*/
/*?*/   rInfo.bAppBasic = (sal_Bool) nAppBasic;
/*?*/   return rStream;
/*?*/ }

/*?*/ int SfxMacroInfo::Load( SvStream& rStream )
/*?*/ {
/*?*/     rStream >> (*this);
/*?*/     nSlotId = SFX_APP()->GetMacroConfig()->GetSlotId(this);
/*?*/     return 0;
/*?*/ }

//==========================================================================

/*?*/ SvStream& operator << (SvStream& rStream, const SfxMacroInfo& rInfo)
/*?*/ {
/*?*/   if ( rInfo.bAppBasic )
/*?*/   {
/*?*/       rStream << nVersion
/*?*/               << (sal_uInt16) rInfo.bAppBasic;
/*?*/       rStream.WriteByteString(rInfo.GetBasicName(),RTL_TEXTENCODING_UTF8);
/*?*/       rStream.WriteByteString(rInfo.aLibName,RTL_TEXTENCODING_UTF8);
/*?*/       rStream.WriteByteString(rInfo.aModuleName,RTL_TEXTENCODING_UTF8);
/*?*/       rStream.WriteByteString(rInfo.aMethodName,RTL_TEXTENCODING_UTF8);
/*?*/   }
/*?*/   else
/*?*/   {
/*?*/       rStream << nVersion
/*?*/               << (sal_uInt16) rInfo.bAppBasic;
/*?*/       rStream.WriteByteString(SFX_APP()->GetName(),RTL_TEXTENCODING_UTF8);
/*?*/       rStream.WriteByteString(rInfo.aLibName,RTL_TEXTENCODING_UTF8);
/*?*/       rStream.WriteByteString(rInfo.aModuleName,RTL_TEXTENCODING_UTF8);
/*?*/       rStream.WriteByteString(rInfo.aMethodName,RTL_TEXTENCODING_UTF8);
/*?*/   }
/*?*/
/*?*/   return rStream;
/*?*/ }

/*?*/ sal_Bool SfxMacroInfo::Compare( const SvxMacro& rMacro ) const
/*?*/ {
/*?*/   String aName = rMacro.GetLibName();
/*?*/   aName += '.';
/*?*/   aName += rMacro.GetMacName();
/*?*/   if ( GetFullQualifiedName() == aName )
/*?*/       return sal_True;
/*?*/   return sal_False;
/*?*/ }

//==========================================================================

/*?*/ SfxMacroConfig::SfxMacroConfig()
/*?*/ {
DBG_ASSERT(0, "STRIP"); //STRIP001  pImp = new SfxMacroConfig_Impl;
/*?*/ }

//==========================================================================

/*?*/ SfxMacroConfig::~SfxMacroConfig()
/*?*/ {
/*?*/   if ( pImp->nEventId )
/*?*/       Application::RemoveUserEvent( pImp->nEventId );
/*?*/   delete pImp;
/*?*/ }

//==========================================================================

/*?*/ SFX_STATE_STUB( SfxApplication, MacroState_Impl )
/*?*/ SFX_EXEC_STUB( SfxApplication, MacroExec_Impl )

/*?*/ sal_uInt16 SfxMacroConfig::GetSlotId(SfxMacroInfoPtr pInfo)
/*?*/ {DBG_ASSERT(0, "STRIP"); return 0;//STRIP001
//STRIP001  sal_uInt16 nCount = pImp->aArr.Count();      // Macro suchen
//STRIP001  sal_uInt16 i;
//STRIP001  for (i=0; i<nCount; i++)
//STRIP001      if ((*(pImp->aArr)[i]) == (*pInfo))
//STRIP001          break;
//STRIP001
//STRIP001  if (i == nCount)
//STRIP001  {                                   // Macro noch unbekannt
//STRIP001      nCount = aIdArray.Count();
//STRIP001      sal_uInt16 n;
//STRIP001      for (n=0; n<nCount; n++) // freie SlotId suchen
//STRIP001          if (aIdArray[n] > SID_MACRO_START + n)
//STRIP001              break;
//STRIP001
//STRIP001      sal_uInt16 nNewSlotId = SID_MACRO_START + n;
//STRIP001      if ( nNewSlotId > SID_MACRO_END )
//STRIP001          return 0;
//STRIP001      aIdArray.Insert( SID_MACRO_START + n, n );
//STRIP001
//STRIP001      SfxSlot *pNewSlot = new SfxSlot;
//STRIP001      pNewSlot->nSlotId = SID_MACRO_START + n;
//STRIP001      pNewSlot->nGroupId = 0;
//STRIP001      pNewSlot->nFlags = SFX_SLOT_ASYNCHRON;
//STRIP001      pNewSlot->nMasterSlotId = 0;
//STRIP001      pNewSlot->nValue = 0;
//STRIP001      pNewSlot->fnExec = SFX_STUB_PTR(SfxApplication,MacroExec_Impl);
//STRIP001      pNewSlot->fnState = SFX_STUB_PTR(SfxApplication,MacroState_Impl);
//STRIP001      pNewSlot->pType = 0; HACK(SFX_TYPE(SfxVoidItem))
//STRIP001      pNewSlot->pName = pNewSlot->pMethodName = U2S(pInfo->aMethodName).getStr();
//STRIP001      pNewSlot->pLinkedSlot = 0;
//STRIP001      pNewSlot->nArgDefCount = 0;
//STRIP001      pNewSlot->pFirstArgDef = 0;
//STRIP001         pNewSlot->pUnoName = 0;
//STRIP001
//STRIP001      if (nCount)
//STRIP001      {
//STRIP001          SfxSlot *pSlot = (pImp->aArr)[0]->pSlot;
//STRIP001          pNewSlot->pNextSlot = pSlot->pNextSlot;
//STRIP001          pSlot->pNextSlot = pNewSlot;
//STRIP001      }
//STRIP001      else
//STRIP001          pNewSlot->pNextSlot = pNewSlot;
//STRIP001
//STRIP001      // Macro uebernehmen
//STRIP001      SfxMacroInfoPtr pNewInfo = new SfxMacroInfo(*pInfo);
//STRIP001      pNewInfo->nSlotId = SID_MACRO_START + n;
//STRIP001      pImp->aArr.Insert(pNewInfo,n);
//STRIP001      pNewInfo->pSlot = pNewSlot;
//STRIP001      pInfo->nSlotId = pNewInfo->nSlotId;
//STRIP001      pNewInfo->nRefCnt++;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      pInfo->nSlotId = (pImp->aArr)[i]->nSlotId;
//STRIP001      (pImp->aArr)[i]->nRefCnt++;
//STRIP001  }
//STRIP001
//STRIP001  return pInfo->nSlotId;
/*?*/ }

//==========================================================================

/*?*/ void SfxMacroConfig::ReleaseSlotId(sal_uInt16 nId)
/*?*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  DBG_ASSERT( IsMacroSlot( nId ), "SlotId ist kein Macro!");
//STRIP001
//STRIP001  sal_uInt16 nCount = pImp->aArr.Count();
//STRIP001  for (sal_uInt16 i=0; i<nCount; i++)
//STRIP001  {
//STRIP001      SfxMacroInfo *pInfo = (pImp->aArr)[i];
//STRIP001      if (pInfo->nSlotId == nId)
//STRIP001      {
//STRIP001          pInfo->nRefCnt--;
//STRIP001          if (pInfo->nRefCnt == 0)
//STRIP001          {
//STRIP001              // Slot wird nicht mehr referenziert, also holen
//STRIP001              SfxSlot *pSlot = pInfo->pSlot;
//STRIP001
//STRIP001              // Slot aus der Verkettung rausnehmen
//STRIP001              while (pSlot->pNextSlot != pInfo->pSlot)
//STRIP001                  pSlot = (SfxSlot*) pSlot->pNextSlot;
//STRIP001              pSlot->pNextSlot = pInfo->pSlot->pNextSlot;
//STRIP001
//STRIP001              // Slot selbst kurz schlie\sen
//STRIP001              pSlot = pInfo->pSlot;
//STRIP001              pSlot->pNextSlot = pSlot;
//STRIP001
//STRIP001              // MacroInfo aus Array entfernen, damit sie kein Unheil
//STRIP001              // anrichten kann
//STRIP001              pImp->aArr.Remove(i);
//STRIP001
//STRIP001              // SlotId wieder freigeben
//STRIP001              sal_uInt16 nCount = aIdArray.Count();
//STRIP001              for (sal_uInt16 n=0; n<nCount; n++)
//STRIP001              {
//STRIP001                  if (aIdArray[n] == nId)
//STRIP001                  {
//STRIP001                      aIdArray.Remove(n);
//STRIP001                      break;
//STRIP001                  }
//STRIP001              }
//STRIP001
//STRIP001              // Sofern nicht die Applikation heruntergefahren wird, mu\s
//STRIP001              // der Slot asynchron gel"oscht werden, falls er in seinem
//STRIP001              // eigenen Execute abgeschossen wird!
//STRIP001                 if ( !SFX_APP()->Get_Impl()->bInQuit )
//STRIP001                     pImp->nEventId = Application::PostUserEvent( LINK(this, SfxMacroConfig, EventHdl_Impl), pInfo );
//STRIP001              else
//STRIP001                  EventHdl_Impl( pInfo );
//STRIP001          }
//STRIP001          return;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  DBG_ERROR("Macro-SlotId nicht gefunden!");
/*?*/ }

//==========================================================================

/*?*/ void SfxMacroConfig::RegisterSlotId(sal_uInt16 nId)
/*?*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  DBG_ASSERT( IsMacroSlot( nId ), "SlotId ist kein Macro!");
//STRIP001
//STRIP001  sal_uInt16 nCount = pImp->aArr.Count();
//STRIP001  for (sal_uInt16 i=0; i<nCount; i++)
//STRIP001  {
//STRIP001      if ((pImp->aArr)[i]->nSlotId == nId)
//STRIP001      {
//STRIP001          (pImp->aArr)[i]->nRefCnt++;
//STRIP001          return;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  DBG_ERROR("Macro-SlotId nicht gefunden!");
/*?*/ }

//==========================================================================

/*?*/ const SfxMacroInfoPtr SfxMacroConfig::GetMacroInfo(sal_uInt16 nId) const
/*?*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  sal_uInt16 nCount = pImp->aArr.Count();
//STRIP001  for (sal_uInt16 i=0; i<nCount; i++)
//STRIP001      if ((pImp->aArr)[i]->nSlotId == nId)
//STRIP001          return (pImp->aArr)[i];
//STRIP001
/*?*/   return 0;
/*?*/ }

//==========================================================================

/*?*/ const SfxMacroInfoPtr SfxMacroConfig::GetMacroInfo_Impl( const SvxMacro *pMacro ) const
/*?*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  sal_uInt16 nCount = pImp->aArr.Count();
//STRIP001  for (sal_uInt16 i=0; i<nCount; i++)
//STRIP001      if ((pImp->aArr)[i]->Compare(*pMacro) )
//STRIP001          return (pImp->aArr)[i];
/*?*/   return 0;
/*?*/ }

//==========================================================================

/*?*/ sal_Bool SfxMacroConfig::ExecuteMacro( sal_uInt16 nId, const String& rArgs ) const
/*?*/ {DBG_ASSERT(0, "STRIP"); return FALSE;//STRIP001
//STRIP001  const SfxMacroInfoPtr pInfo = GetMacroInfo( nId );
//STRIP001  if ( !pInfo )
//STRIP001      return sal_False;
//STRIP001
//STRIP001  SfxObjectShell* pSh = SfxObjectShell::Current();
//STRIP001
//STRIP001  SvxMacro aMacro( pInfo->GetQualifiedName(), pInfo->GetBasicName(), STARBASIC );
//STRIP001  sal_Bool bRet = ExecuteMacro( pSh, &aMacro, rArgs );
//STRIP001
//STRIP001  // Release, da im Dispatcher-Execute ein Register gemacht wurde
//STRIP001  ((SfxMacroConfig*)this)->ReleaseSlotId( nId );
//STRIP001  return bRet;
/*?*/ }

/*?*/ sal_Bool SfxMacroConfig::ExecuteMacro( SfxObjectShell *pSh, const SvxMacro* pMacro, const String& rArgs ) const
/*?*/ {DBG_ASSERT(0, "STRIP"); return FALSE;//STRIP001
//STRIP001  SfxApplication *pApp = SFX_APP();
//STRIP001
//STRIP001  // Name des Macros oder Scripts bzw. ScriptCode
//STRIP001  String aCode( pMacro->GetMacName() );
//STRIP001  ErrCode nErr = ERRCODE_NONE;
//STRIP001
//STRIP001  // Ist es ein Basic-Macro ?
//STRIP001  ScriptType eSType = pMacro->GetScriptType();
//STRIP001  sal_Bool bIsBasic = eSType == STARBASIC;
//STRIP001  sal_Bool bIsStarScript = ( eSType == EXTENDED_STYPE && pMacro->GetLibName().SearchAscii( "StarScript" ) != STRING_NOTFOUND );
//STRIP001  sal_Bool bIsBasicLibBased = bIsBasic || bIsStarScript || !pSh;
//STRIP001
//STRIP001  if ( bIsBasicLibBased )
//STRIP001  {
//STRIP001      pApp->EnterBasicCall();
//STRIP001      BasicManager *pAppMgr = SFX_APP()->GetBasicManager();
//STRIP001      if( bIsBasic )
//STRIP001      {
//STRIP001          // BasicManager von Document?
//STRIP001          BasicManager *pMgr = pSh ? pSh->GetBasicManager() : NULL;
//STRIP001
//STRIP001          // Da leider der Name zwischendurch h"aufig gewechselt hat ...
//STRIP001          if( SFX_APP()->GetName() == pMacro->GetLibName() ||
//STRIP001                  pMacro->GetLibName().EqualsAscii("StarDesktop") )
//STRIP001              pMgr = pAppMgr;
//STRIP001          else if ( pMgr == pAppMgr )
//STRIP001              pMgr = NULL;
//STRIP001
//STRIP001             if ( pSh && pMgr && pMgr != pAppMgr )
//STRIP001             {
//STRIP001                 pSh->AdjustMacroMode( String() );
//STRIP001              if( pSh->Get_Impl()->nMacroMode == ::com::sun::star::document::MacroExecMode::NEVER_EXECUTE )
//STRIP001                  return sal_False;
//STRIP001             }
//STRIP001
//STRIP001             if ( pSh && pMgr && pMgr == pAppMgr )
//STRIP001          {
//STRIP001                 SbxBaseRef xOldVar;
//STRIP001              SbxVariable *pCompVar = pAppMgr->GetLib(0)->Find( DEFINE_CONST_UNICODE("ThisComponent"), SbxCLASS_PROPERTY );
//STRIP001                 ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface >  xInterface ( pSh->GetModel() , ::com::sun::star::uno::UNO_QUERY );
//STRIP001                 ::com::sun::star::uno::Any aAny;
//STRIP001                 aAny <<= xInterface;
//STRIP001              if ( pCompVar )
//STRIP001              {
//STRIP001                     xOldVar = pCompVar->GetObject();
//STRIP001                  pCompVar->PutObject( GetSbUnoObject( DEFINE_CONST_UNICODE("ThisComponent"), aAny ) );
//STRIP001              }
//STRIP001                 else
//STRIP001                 {
//STRIP001                     SbxObjectRef xUnoObj = GetSbUnoObject( DEFINE_CONST_UNICODE("ThisComponent"), aAny );
//STRIP001                     xUnoObj->SetFlag( SBX_DONTSTORE );
//STRIP001                     pAppMgr->GetLib(0)->Insert( xUnoObj );
//STRIP001                     pCompVar = pAppMgr->GetLib(0)->Find( DEFINE_CONST_UNICODE("ThisComponent"), SbxCLASS_PROPERTY );
//STRIP001                 }
//STRIP001
//STRIP001              nErr = Call( 0, aCode, pMgr );
//STRIP001              if ( pCompVar )
//STRIP001                     pCompVar->PutObject( xOldVar );
//STRIP001          }
//STRIP001          else if ( pMgr )
//STRIP001              nErr = Call( 0, aCode, pMgr );
//STRIP001          else
//STRIP001              nErr = SbxERR_NO_METHOD;
//STRIP001
//STRIP001      }
//STRIP001
//STRIP001      pApp->LeaveBasicCall();
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      nErr = SbxERR_NO_METHOD;
//STRIP001  }
//STRIP001
//STRIP001  return ( nErr == ERRCODE_NONE );
/*?*/ }

/*?*/ sal_Bool SfxMacroConfig::CheckMacro( SfxObjectShell *pSh, const SvxMacro* pMacro ) const
/*?*/ {DBG_ASSERT(0, "STRIP"); return FALSE;//STRIP001
//STRIP001  SfxApplication *pApp = SFX_APP();
//STRIP001
//STRIP001  // Name des Macros oder Scripts bzw. ScriptCode
//STRIP001  String aCode( pMacro->GetMacName() );
//STRIP001  ErrCode nErr = ERRCODE_NONE;
//STRIP001
//STRIP001  // BasicManager von Document oder Application
//STRIP001  pApp->EnterBasicCall();
//STRIP001  BasicManager *pAppMgr = SFX_APP()->GetBasicManager();
//STRIP001  BasicManager *pMgr = pSh ? pSh->GetBasicManager() : NULL;
//STRIP001
//STRIP001  // Da leider der Name zwischendurch h"aufig gewechselt hat ...
//STRIP001  if( SFX_APP()->GetName() == pMacro->GetLibName() ||
//STRIP001          pMacro->GetLibName().EqualsAscii("StarDesktop") )
//STRIP001      pMgr = pAppMgr;
//STRIP001  else if ( pMgr == pAppMgr )
//STRIP001      pMgr = NULL;
//STRIP001
//STRIP001  if ( !pMgr || !SfxQueryMacro( pMgr, aCode ) )
//STRIP001      nErr = SbxERR_NO_METHOD;
//STRIP001  pApp->LeaveBasicCall();
//STRIP001  return ( nErr == ERRCODE_NONE );
/*?*/ }

//==========================================================================

/*?*/ sal_Bool SfxMacroConfig::CheckMacro( sal_uInt16 nId ) const
/*?*/ {DBG_ASSERT(0, "STRIP");return FALSE; //STRIP001
//STRIP001  const SfxMacroInfoPtr pInfo = GetMacroInfo( nId );
//STRIP001  if ( !pInfo )
//STRIP001      return sal_False;
//STRIP001
//STRIP001  // Basic nur initialisieren, wenn default nicht ::com::sun::star::script::JavaScript; dann mu\s
//STRIP001  // in IsBasic() sowieso das Basic angelegt werden
//STRIP001  SfxObjectShell* pSh = SfxObjectShell::Current();
//STRIP001
//STRIP001  SfxApplication *pApp = SFX_APP();
//STRIP001  pApp->EnterBasicCall();
//STRIP001
//STRIP001  // BasicManager von Document oder Application
//STRIP001  BasicManager *pAppMgr = SFX_APP()->GetBasicManager();
//STRIP001  BasicManager *pMgr = pSh ? pSh->GetBasicManager() : NULL;
//STRIP001
//STRIP001  if( SFX_APP()->GetName() == pInfo->GetBasicName() )
//STRIP001      pMgr = SFX_APP()->GetBasicManager();
//STRIP001  else if ( pMgr == pAppMgr )
//STRIP001      pMgr = NULL;
//STRIP001
//STRIP001  String aFull( pInfo->GetQualifiedName() );
//STRIP001  sal_Bool bIsBasic = pMgr ? IsBasic( 0, aFull, pMgr ) : sal_False;
//STRIP001  pApp->LeaveBasicCall();
//STRIP001  return bIsBasic;
/*?*/ }

//==========================================================================

/*?*/ IMPL_LINK( SfxMacroConfig, CallbackHdl_Impl, SfxMacroConfig*, pConfig )
/*?*/ {
    DBG_ASSERT(0, "STRIP"); //STRIP001 pImp->bWaitingForCallback = sal_False;
/*?*/   return 0;
/*?*/ }

/*?*/ IMPL_LINK( SfxMacroConfig, EventHdl_Impl, SfxMacroInfo*, pInfo )
/*?*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/    delete pInfo;
/*?*/   pImp->nEventId = 0;
/*?*/   return 0;
/*?*/ }

/*?*/ sal_Bool SfxMacroConfig::IsBasic( SbxObject* pVCtrl, const String& rCode, BasicManager* pMgr )
/*?*/ {DBG_ASSERT(0, "STRIP"); return FALSE;//STRIP001
//STRIP001 /*?*/    sal_Bool bFound;
//STRIP001 /*?*/    SFX_APP()->EnterBasicCall();
//STRIP001 /*?*/    bFound = SfxQueryMacro( pMgr, rCode ) != 0;
//STRIP001 /*?*/    SFX_APP()->LeaveBasicCall();
//STRIP001 /*?*/    return bFound;
/*?*/ }

/*?*/ ErrCode SfxMacroConfig::Call( SbxObject* pVCtrl,
/*?*/   const String& rCode, BasicManager* pMgr, SbxArray *pArgs, SbxValue *pRet )
/*?*/ {DBG_ASSERT(0, "STRIP"); return 0;//STRIP001
//STRIP001  SfxApplication *pApp = SFX_APP();
//STRIP001  pApp->EnterBasicCall();
//STRIP001  SbMethod* pMethod = SfxQueryMacro( pMgr, rCode );
//STRIP001  ErrCode nErr = 0;
//STRIP001  if( pMethod )
//STRIP001  {
//STRIP001      if ( pArgs )
//STRIP001          pMethod->SetParameters( pArgs );
//STRIP001      nErr = pMethod->Call( pRet );
//STRIP001  }
//STRIP001  else
//STRIP001      nErr = ERRCODE_BASIC_PROC_UNDEFINED;
//STRIP001
//STRIP001  pApp->LeaveBasicCall();
//STRIP001  return nErr;
/*?*/ }

#if SUPD<582
//STRIP001 void SfxMacroConfig::CallStarScript( const ::com::sun::star::uno::Reference< ::com::sun::star::script::XEngine > & rxEngine, const String & rCode,
//STRIP001  const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > & rSource, void *pArgs, void *pRet )
//STRIP001 {
//STRIP001  static String aCallPrefix( "();" );
//STRIP001
//STRIP001  ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Any >   aArgs;
//STRIP001  if( pArgs )
//STRIP001      aArgs = *(::com::sun::star::uno::Sequence< ::com::sun::star::uno::Any > *)pArgs;
//STRIP001
//STRIP001  // HACK!!! TODO: Klaeren, wie das wirklich laufen soll
//STRIP001  String aCode = rCode;
//STRIP001  aCode += aCallPrefix;
//STRIP001
//STRIP001  ::rtl::OUString aUCode = StringToOUString( aCode, RTL_TEXTENCODING_UTF8 );
//STRIP001  if ( pRet )
//STRIP001  {
//STRIP001      *((::com::sun::star::uno::Any*)pRet) = rxEngine->run( aUCode, rSource, aArgs );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      ::com::sun::star::uno::Reference< ::com::sun::star::script::XEngineListener >  xCB;
//STRIP001      rxEngine->runAsync( aUCode, rSource, aArgs, xCB );
//STRIP001  }
//STRIP001 }
#endif

/*N*/ sal_Bool SfxMacroConfig::IsMacroSlot( sal_uInt16 nId )
/*N*/ {
/*N*/   return ( nId >= SID_MACRO_START && nId <= SID_MACRO_END );
/*N*/ }


