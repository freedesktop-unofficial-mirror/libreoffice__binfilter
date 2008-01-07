/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sfx2_macrconf.cxx,v $
 *
 *  $Revision: 1.9 $
 *
 *  last change: $Author: obo $ $Date: 2008-01-07 08:20:34 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/

#ifdef _MSC_VER
#pragma hdrstop
#endif

#include "macrconf.hxx"
#include "sfx.hrc"
#include "app.hxx"
#include "objshimp.hxx"

namespace binfilter {

static const sal_uInt16 nCompatVersion = 2;
static const sal_uInt16 nVersion = 3;

// Static member
SfxMacroConfig* SfxMacroConfig::pMacroConfig = NULL;

/*N*/ SfxMacroConfig* SfxMacroConfig::GetOrCreate()
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001
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
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*?*/   return 0;
/*?*/ }

/*?*/ SbMethod* SfxQueryMacro( BasicManager* pMgr , const String& rMacro )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return NULL;//STRIP001
/*?*/ }

/*?*/ ErrCode SfxCallMacro( BasicManager* pMgr, const String& rCode,
/*?*/                     SbxArray *pArgs, SbxValue *pRet )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001
/*?*/ }

//==========================================================================

/*?*/ SfxMacroInfo::SfxMacroInfo( const String& rURL ) :
/*?*/     bAppBasic(TRUE),
/*?*/   nSlotId(0),
/*?*/   nRefCnt(0),
/*?*/   pHelpText(0)
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*?*/ }

/*?*/ SfxMacroInfo::SfxMacroInfo( SfxObjectShell *pDoc ) :
/*?*/   bAppBasic(pDoc == NULL),
/*?*/   nSlotId(0),
/*?*/   nRefCnt(0),
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
/*?*/   pHelpText(0)
/*?*/ {
/*?*/   bAppBasic = (pDoc == 0);
/*?*/ }

//==========================================================================

/*?*/ SfxMacroInfo::SfxMacroInfo(SfxObjectShell *pDoc, const String& rQualifiedName )
/*?*/ : nSlotId(0),
/*?*/   nRefCnt(0),
/*?*/   pHelpText(0)
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*?*/ }

//==========================================================================

/*?*/ SfxMacroInfo::SfxMacroInfo(SfxMacroInfo& rOther) :
/*?*/   bAppBasic(rOther.bAppBasic),
/*?*/   aLibName(rOther.aLibName),
/*?*/   aModuleName(rOther.aModuleName),
/*?*/   aMethodName(rOther.aMethodName),
/*?*/   nSlotId(rOther.nSlotId),
/*?*/   nRefCnt(0),
/*?*/   pHelpText(0)
/*?*/ {}

//==========================================================================

/*?*/ SfxMacroInfo::~SfxMacroInfo()
/*?*/ {
/*?*/   delete pHelpText;
/*?*/ }

//==========================================================================

/*?*/ sal_Bool SfxMacroInfo::operator==(const SfxMacroInfo& rOther) const
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001
/*?*/ }

//==========================================================================

/*?*/ String SfxMacroInfo::GetMacroName() const
/*?*/ {DBG_BF_ASSERT(0, "STRIP");return String(); //STRIP001
/*?*/ }

//==========================================================================

/*?*/ String SfxMacroInfo::GetQualifiedName() const
/*?*/ {DBG_BF_ASSERT(0, "STRIP");return String();
/*?*/ }

/*?*/ String SfxMacroInfo::GetFullQualifiedName() const
/*?*/ {DBG_BF_ASSERT(0, "STRIP");return String();
/*?*/ }

/*?*/ String SfxMacroInfo::GetURL() const
/*?*/ {DBG_BF_ASSERT(0, "STRIP");return String();
/*?*/ }

//==========================================================================

/*?*/ BasicManager* SfxMacroInfo::GetBasicManager() const
/*?*/ {DBG_BF_ASSERT(0, "STRIP");return NULL; //STRIP001
/*?*/ }

//==========================================================================

/*?*/ String SfxMacroInfo::GetBasicName() const
/*?*/ {DBG_BF_ASSERT(0, "STRIP");return String();//STRIP001
/*?*/ }

/*?*/ String SfxMacroInfo::GetHelpText() const
/*?*/ {DBG_BF_ASSERT(0, "STRIP");return String();
    //STRIP001 if ( pHelpText )
/*?*/ }

/*?*/ String SfxMacroConfig::RequestHelp( sal_uInt16 nId )
/*?*/ {DBG_BF_ASSERT(0, "STRIP");return String();
/*?*/ }

/*?*/ void SfxMacroInfo::SetHelpText( const String& rName )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
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
/*?*/     nSlotId = SfxMacroConfig::GetOrCreate()->GetSlotId(this);
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
DBG_BF_ASSERT(0, "STRIP"); //STRIP001   pImp = new SfxMacroConfig_Impl;
/*?*/ }

//==========================================================================

/*?*/ SfxMacroConfig::~SfxMacroConfig()
/*?*/ {
/*?*/   if ( pImp->nEventId )
/*?*/       Application::RemoveUserEvent( pImp->nEventId );
/*?*/   delete pImp;
/*?*/ }

//==========================================================================

/*?*/ sal_uInt16 SfxMacroConfig::GetSlotId(SfxMacroInfoPtr pInfo)
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001
/*?*/ }

//==========================================================================

/*?*/ void SfxMacroConfig::ReleaseSlotId(sal_uInt16 nId)
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*?*/ }

//==========================================================================

/*?*/ void SfxMacroConfig::RegisterSlotId(sal_uInt16 nId)
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*?*/ }

//==========================================================================

/*?*/ const SfxMacroInfoPtr SfxMacroConfig::GetMacroInfo(sal_uInt16 nId) const
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*?*/   return 0;
/*?*/ }

//==========================================================================

/*?*/ const SfxMacroInfoPtr SfxMacroConfig::GetMacroInfo_Impl( const SvxMacro *pMacro ) const
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*?*/   return 0;
/*?*/ }

//==========================================================================

/*?*/ sal_Bool SfxMacroConfig::ExecuteMacro( sal_uInt16 nId, const String& rArgs ) const
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001
/*?*/ }

/*?*/ sal_Bool SfxMacroConfig::ExecuteMacro( SfxObjectShell *pSh, const SvxMacro* pMacro, const String& rArgs ) const
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001
/*?*/ }

/*?*/ sal_Bool SfxMacroConfig::CheckMacro( SfxObjectShell *pSh, const SvxMacro* pMacro ) const
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001
/*?*/ }

//==========================================================================

/*?*/ sal_Bool SfxMacroConfig::CheckMacro( sal_uInt16 nId ) const
/*?*/ {DBG_BF_ASSERT(0, "STRIP");return FALSE; //STRIP001
/*?*/ }

//==========================================================================

/*?*/ IMPL_LINK( SfxMacroConfig, CallbackHdl_Impl, SfxMacroConfig*, pConfig )
/*?*/ {
    DBG_BF_ASSERT(0, "STRIP"); //STRIP001 pImp->bWaitingForCallback = sal_False;
/*?*/   return 0;
/*?*/ }

/*?*/ IMPL_LINK( SfxMacroConfig, EventHdl_Impl, SfxMacroInfo*, pInfo )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*?*/   pImp->nEventId = 0;
/*?*/   return 0;
/*?*/ }

/*?*/ sal_Bool SfxMacroConfig::IsBasic( SbxObject* pVCtrl, const String& rCode, BasicManager* pMgr )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001
/*?*/ }

/*?*/ ErrCode SfxMacroConfig::Call( SbxObject* pVCtrl,
/*?*/   const String& rCode, BasicManager* pMgr, SbxArray *pArgs, SbxValue *pRet )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001
/*?*/ }

/*N*/ sal_Bool SfxMacroConfig::IsMacroSlot( sal_uInt16 nId )
/*N*/ {
/*N*/   return ( nId >= SID_MACRO_START && nId <= SID_MACRO_END );
/*N*/ }


}
