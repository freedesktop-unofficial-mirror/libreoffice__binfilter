/*************************************************************************
 *
 *  $RCSfile: sc_callform.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:26:26 $
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

#ifndef _SV_SVAPP_HXX //autogen
#include <vcl/svapp.hxx>
#endif
#ifndef _VOS_MODULE_HXX_
#include <vos/module.hxx>
#endif
#ifndef _OSL_FILE_HXX_
#include <osl/file.hxx>
#endif
#ifndef _UNOTOOLS_TRANSLITERATIONWRAPPER_HXX
#include <unotools/transliterationwrapper.hxx>
#endif

#include "callform.hxx"
#include "global.hxx"
#include "adiasync.hxx"
#include <tools/debug.hxx>
namespace binfilter {

using namespace ::vos;

//------------------------------------------------------------------------

extern "C" {

typedef void (CALLTYPE* ExFuncPtr1)(void*);
typedef void (CALLTYPE* ExFuncPtr2)(void*, void*);
typedef void (CALLTYPE* ExFuncPtr3)(void*, void*, void*);
typedef void (CALLTYPE* ExFuncPtr4)(void*, void*, void*, void*);
typedef void (CALLTYPE* ExFuncPtr5)(void*, void*, void*, void*, void*);
typedef void (CALLTYPE* ExFuncPtr6)(void*, void*, void*, void*, void*, void*);
typedef void (CALLTYPE* ExFuncPtr7)(void*, void*, void*, void*, void*, void*, void*);
typedef void (CALLTYPE* ExFuncPtr8)(void*, void*, void*, void*, void*, void*, void*, void*);
typedef void (CALLTYPE* ExFuncPtr9)(void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef void (CALLTYPE* ExFuncPtr10)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef void (CALLTYPE* ExFuncPtr11)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef void (CALLTYPE* ExFuncPtr12)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef void (CALLTYPE* ExFuncPtr13)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef void (CALLTYPE* ExFuncPtr14)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef void (CALLTYPE* ExFuncPtr15)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef void (CALLTYPE* ExFuncPtr16)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);

typedef void (CALLTYPE* GetFuncCountPtr)(USHORT& nCount);
typedef void (CALLTYPE* GetFuncDataPtr)
    (USHORT& nNo, sal_Char* pFuncName, USHORT& nParamCount, ParamType* peType, sal_Char* pInternalName);

typedef void (CALLTYPE* SetLanguagePtr)( USHORT& nLanguage );
typedef void (CALLTYPE* GetParamDesc)
    (USHORT& nNo, USHORT& nParam, sal_Char* pName, sal_Char* pDesc );

typedef void (CALLTYPE* IsAsync) ( USHORT&      nNo,
                                   ParamType*   peType );
typedef void (CALLTYPE* Advice)  ( USHORT&      nNo,
                                   AdvData&     pfCallback );
typedef void (CALLTYPE* Unadvice)( double&      nHandle );

typedef void (CALLTYPE* FARPROC) ( void );

}

#if defined(OS2) && defined(BLC)
#define GETFUNCTIONCOUNT        "_GetFunctionCount"
#define GETFUNCTIONDATA         "_GetFunctionData"
#define SETLANGUAGE             "_SetLanguage"
#define GETPARAMDESC            "_GetParameterDescription"
#define ISASYNC                 "_IsAsync"
#define ADVICE                  "_Advice"
#define UNADVICE                "_Unadvice"
#else // Pascal oder extern "C"
#define GETFUNCTIONCOUNT        "GetFunctionCount"
#define GETFUNCTIONDATA         "GetFunctionData"
#define SETLANGUAGE             "SetLanguage"
#define GETPARAMDESC            "GetParameterDescription"
#define ISASYNC                 "IsAsync"
#define ADVICE                  "Advice"
#define UNADVICE                "Unadvice"
#endif

#define LIBFUNCNAME( name ) \
    (String::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM( name ) ))

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

/*N*/ FuncData::FuncData(const String& rIName) :
/*N*/   pModuleData     (NULL),
/*N*/   aInternalName   (rIName),
/*N*/ //  aFuncName     (""),
/*N*/   nNumber         (0),
/*N*/   nParamCount     (0),
/*N*/   eAsyncType      (NONE)
/*N*/ {
/*N*/   for (USHORT i = 0; i < MAXFUNCPARAM; i++)
/*N*/       eParamType[i] = PTR_DOUBLE;
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 FuncData::FuncData(const ModuleData*pModule,
//STRIP001                 const String&    rIName,
//STRIP001                 const String&    rFName,
//STRIP001                       USHORT nNo,
//STRIP001                  USHORT  nCount,
//STRIP001                 const ParamType* peType,
//STRIP001                  ParamType  eType) :
//STRIP001  pModuleData     (pModule),
//STRIP001  aInternalName   (rIName),
//STRIP001  aFuncName       (rFName),
//STRIP001  nNumber         (nNo),
//STRIP001  nParamCount     (nCount),
//STRIP001  eAsyncType      (eType)
//STRIP001 {
//STRIP001  for (USHORT i = 0; i < MAXFUNCPARAM; i++)
//STRIP001      eParamType[i] = peType[i];
//STRIP001 }

//------------------------------------------------------------------------

/*N*/ FuncData::FuncData(const FuncData& rData) :
/*N*/   pModuleData     (rData.pModuleData),
/*N*/   aInternalName   (rData.aInternalName),
/*N*/   aFuncName       (rData.aFuncName),
/*N*/   nNumber         (rData.nNumber),
/*N*/   nParamCount     (rData.nParamCount),
/*N*/   eAsyncType      (rData.eAsyncType)
/*N*/ {
/*N*/   for (USHORT i = 0; i < MAXFUNCPARAM; i++)
/*N*/       eParamType[i] = rData.eParamType[i];
/*N*/ }

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

/*N*/ short FuncCollection::Compare(DataObject* pKey1, DataObject* pKey2) const
/*N*/ {
            DBG_ASSERT(0, "STRIP"); return 0; //STRIP001 return (short) ScGlobal::pTransliteration->compareString(
//STRIP001      ((FuncData*)pKey1)->aInternalName, ((FuncData*)pKey2)->aInternalName );
/*N*/ }

//------------------------------------------------------------------------

/*N*/ BOOL FuncCollection::SearchFunc( const String& rName, USHORT& rIndex ) const
/*N*/ {
/*N*/   FuncData aDataObj(rName);
/*N*/   return Search( &aDataObj, rIndex );
/*N*/ }

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
/*N*/ class ModuleData : public DataObject
/*N*/ {
/*N*/ friend class ModuleCollection;
/*N*/   String      aName;
/*N*/   OModule*    pInstance;
/*N*/ public:
/*N*/   ModuleData(const String& rStr, OModule* pInst) : aName (rStr), pInstance (pInst) {}
/*N*/   ModuleData(const ModuleData& rData) : aName (rData.aName) {pInstance = new OModule(aName);}
/*N*/   ~ModuleData() { delete pInstance; }
/*N*/   virtual DataObject* Clone() const { return new ModuleData(*this); }
/*N*/
/*N*/   const   String&         GetName() const { return aName; }
/*N*/           OModule*        GetInstance() const { return pInstance; }
/*N*/           void            FreeInstance() { delete pInstance; pInstance = 0; }
/*N*/ };

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
/*N*/ class ModuleCollection : public SortedCollection
/*N*/ {
/*N*/ public:
/*N*/   ModuleCollection(USHORT nLim = 4, USHORT nDel = 4, BOOL bDup = FALSE) : SortedCollection ( nLim, nDel, bDup ) {}
/*N*/   ModuleCollection(const ModuleCollection& rModuleCollection) : SortedCollection ( rModuleCollection ) {}
/*N*/
/*N*/   virtual DataObject*     Clone() const { return new ModuleCollection(*this); }
/*N*/           ModuleData*     operator[]( const USHORT nIndex) const {return (ModuleData*)At(nIndex);}
    virtual short           Compare(DataObject* pKey1, DataObject* pKey2) const{DBG_ASSERT(0, "STRIP"); return 0;} //STRIP001 virtual short         Compare(DataObject* pKey1, DataObject* pKey2) const;
//STRIP001          BOOL            SearchModule( const String& rName,
//STRIP001                                        const ModuleData*& rpModule ) const;
/*N*/ };

/*N*/ #pragma code_seg("SCSTATICS")
/*N*/
/*N*/ static ModuleCollection aModuleCollection;
/*N*/
/*N*/ #pragma code_seg()

//------------------------------------------------------------------------

//STRIP001 short ModuleCollection::Compare(DataObject* pKey1, DataObject* pKey2) const
//STRIP001 {
//STRIP001     return (short) ScGlobal::pTransliteration->compareString(
//STRIP001      ((ModuleData*)pKey1)->aName, ((ModuleData*)pKey2)->aName );
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 BOOL ModuleCollection::SearchModule( const String& rName,
//STRIP001                                   const ModuleData*& rpModule ) const
//STRIP001 {
//STRIP001  USHORT nIndex;
//STRIP001  ModuleData aSearchModule(rName, 0);
//STRIP001  BOOL bFound = Search( &aSearchModule, nIndex );
//STRIP001  if (bFound)
//STRIP001      rpModule = (ModuleData*)At(nIndex);
//STRIP001  else
//STRIP001      rpModule = 0;
//STRIP001  return bFound;
//STRIP001 }

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

//STRIP001 BOOL InitExternalFunc(const ::rtl::OUString& rModuleName)
//STRIP001 {
//STRIP001  String aModuleName( rModuleName );
//STRIP001
//STRIP001  // Module schon geladen?
//STRIP001  const ModuleData* pTemp;
//STRIP001  if (aModuleCollection.SearchModule(aModuleName, pTemp))
//STRIP001      return FALSE;
//STRIP001
//STRIP001  ::rtl::OUString aNP;
//STRIP001  aNP = rModuleName;
//STRIP001
//STRIP001  BOOL bRet = FALSE;
//STRIP001  OModule* pLib = new OModule( aNP );
//STRIP001  if (pLib->isLoaded())
//STRIP001  {
//STRIP001      FARPROC fpGetCount = (FARPROC)pLib->getSymbol(LIBFUNCNAME(GETFUNCTIONCOUNT));
//STRIP001      FARPROC fpGetData = (FARPROC)pLib->getSymbol(LIBFUNCNAME(GETFUNCTIONDATA));
//STRIP001      if ((fpGetCount != NULL) && (fpGetData != NULL))
//STRIP001      {
//STRIP001          FARPROC fpIsAsync = (FARPROC)pLib->getSymbol(LIBFUNCNAME(ISASYNC));
//STRIP001          FARPROC fpAdvice = (FARPROC)pLib->getSymbol(LIBFUNCNAME(ADVICE));
//STRIP001          FARPROC fpSetLanguage = (FARPROC)pLib->getSymbol(LIBFUNCNAME(SETLANGUAGE));
//STRIP001          if ( fpSetLanguage )
//STRIP001          {
//STRIP001                 LanguageType eLanguage = Application::GetSettings().GetUILanguage();
//STRIP001              USHORT nLanguage = (USHORT) eLanguage;
//STRIP001              (*((SetLanguagePtr)fpSetLanguage))( nLanguage );
//STRIP001          }
//STRIP001
//STRIP001          // Module in die Collection aufnehmen
//STRIP001          ModuleData* pModuleData = new ModuleData(aModuleName, pLib);
//STRIP001          aModuleCollection.Insert(pModuleData);
//STRIP001
//STRIP001          // Schnittstelle initialisieren
//STRIP001          AdvData pfCallBack = &ScAddInAsyncCallBack;
//STRIP001          FuncData* pFuncData;
//STRIP001          FuncCollection* pFuncCol = ScGlobal::GetFuncCollection();
//STRIP001          USHORT nCount;
//STRIP001          (*((GetFuncCountPtr)fpGetCount))(nCount);
//STRIP001          for (USHORT i=0; i < nCount; i++)
//STRIP001          {
//STRIP001              sal_Char cFuncName[256];
//STRIP001              sal_Char cInternalName[256];
//STRIP001              USHORT nParamCount;
//STRIP001              ParamType eParamType[MAXFUNCPARAM];
//STRIP001              ParamType eAsyncType = NONE;
//STRIP001              // #62113# alles initialisieren, falls das AddIn sich schlecht verhaelt
//STRIP001              cFuncName[0] = 0;
//STRIP001              cInternalName[0] = 0;
//STRIP001              nParamCount = 0;
//STRIP001              for ( USHORT j=0; j<MAXFUNCPARAM; j++ )
//STRIP001              {
//STRIP001                  eParamType[j] = NONE;
//STRIP001              }
//STRIP001              (*((GetFuncDataPtr)fpGetData))(i, cFuncName, nParamCount,
//STRIP001                                             eParamType, cInternalName);
//STRIP001              if( fpIsAsync )
//STRIP001              {
//STRIP001                  (*((IsAsync)fpIsAsync))(i, &eAsyncType);
//STRIP001                  if ( fpAdvice && eAsyncType != NONE )
//STRIP001                      (*((Advice)fpAdvice))( i, pfCallBack );
//STRIP001              }
//STRIP001              String aInternalName( cInternalName, osl_getThreadTextEncoding() );
//STRIP001              String aFuncName( cFuncName, osl_getThreadTextEncoding() );
//STRIP001              pFuncData = new FuncData( pModuleData,
//STRIP001                                        aInternalName,
//STRIP001                                        aFuncName,
//STRIP001                                        i,
//STRIP001                                        nParamCount,
//STRIP001                                        eParamType,
//STRIP001                                        eAsyncType );
//STRIP001              pFuncCol->Insert(pFuncData);
//STRIP001          }
//STRIP001          bRet = TRUE;
//STRIP001      }
//STRIP001      else
//STRIP001          delete pLib;
//STRIP001  }
//STRIP001  else
//STRIP001      delete pLib;
//STRIP001  return bRet;
//STRIP001 }

//------------------------------------------------------------------------

/*N*/ void ExitExternalFunc()
/*N*/ {
/*N*/   USHORT nCount = aModuleCollection.GetCount();
/*N*/   for (USHORT i=0; i<nCount; i++)
/*N*/   {
/*?*/       ModuleData* pData = aModuleCollection[i];
/*?*/       pData->FreeInstance();
/*N*/   }
/*N*/ }

//------------------------------------------------------------------------

/*N*/ BOOL FuncData::Call(void** ppParam)
/*N*/ {
/*N*/   BOOL bRet = FALSE;
/*N*/   OModule* pLib = pModuleData->GetInstance();
/*N*/   FARPROC fProc = (FARPROC)pLib->getSymbol(aFuncName);
/*N*/   if (fProc != NULL)
/*N*/   {
/*N*/       switch (nParamCount)
/*N*/       {
/*N*/           case 1 :
/*N*/               (*((ExFuncPtr1)fProc))(ppParam[0]);
/*N*/               bRet = TRUE;
/*N*/               break;
/*N*/           case 2 :
/*N*/               (*((ExFuncPtr2)fProc))(ppParam[0], ppParam[1]);
/*N*/               bRet = TRUE;
/*N*/               break;
/*N*/           case 3 :
/*N*/               (*((ExFuncPtr3)fProc))(ppParam[0], ppParam[1], ppParam[2]);
/*N*/               bRet = TRUE;
/*N*/               break;
/*N*/           case 4 :
/*N*/               (*((ExFuncPtr4)fProc))(ppParam[0], ppParam[1], ppParam[2], ppParam[3]);
/*N*/               bRet = TRUE;
/*N*/               break;
/*N*/           case 5 :
/*N*/               (*((ExFuncPtr5)fProc))(ppParam[0], ppParam[1], ppParam[2], ppParam[3], ppParam[4]);
/*N*/               bRet = TRUE;
/*N*/               break;
/*N*/           case 6 :
/*N*/               (*((ExFuncPtr6)fProc))(ppParam[0], ppParam[1], ppParam[2], ppParam[3], ppParam[4], ppParam[5]);
/*N*/               bRet = TRUE;
/*N*/               break;
/*N*/           case 7 :
/*N*/               (*((ExFuncPtr7)fProc))( ppParam[0], ppParam[1], ppParam[2], ppParam[3], ppParam[4], ppParam[5],
/*N*/                                       ppParam[6]);
/*N*/               bRet = TRUE;
/*N*/               break;
/*N*/           case 8 :
/*N*/               (*((ExFuncPtr8)fProc))( ppParam[0], ppParam[1], ppParam[2], ppParam[3], ppParam[4], ppParam[5],
/*N*/                                       ppParam[6], ppParam[7]);
/*N*/               bRet = TRUE;
/*N*/               break;
/*N*/           case 9 :
/*N*/               (*((ExFuncPtr9)fProc))( ppParam[0], ppParam[1], ppParam[2], ppParam[3], ppParam[4], ppParam[5],
/*N*/                                       ppParam[6], ppParam[7], ppParam[8]);
/*N*/               bRet = TRUE;
/*N*/               break;
/*N*/           case 10 :
/*N*/               (*((ExFuncPtr10)fProc))( ppParam[0], ppParam[1], ppParam[2], ppParam[3], ppParam[4], ppParam[5],
/*N*/                                       ppParam[6], ppParam[7], ppParam[8], ppParam[9]);
/*N*/               bRet = TRUE;
/*N*/               break;
/*N*/           case 11 :
/*N*/               (*((ExFuncPtr11)fProc))( ppParam[0], ppParam[1], ppParam[2], ppParam[3], ppParam[4], ppParam[5],
/*N*/                                       ppParam[6], ppParam[7], ppParam[8], ppParam[9], ppParam[10]);
/*N*/               bRet = TRUE;
/*N*/               break;
/*N*/           case 12:
/*N*/               (*((ExFuncPtr12)fProc))( ppParam[0], ppParam[1], ppParam[2], ppParam[3], ppParam[4], ppParam[5],
/*N*/                                       ppParam[6], ppParam[7], ppParam[8], ppParam[9], ppParam[10], ppParam[11]);
/*N*/               bRet = TRUE;
/*N*/               break;
/*N*/           case 13:
/*N*/               (*((ExFuncPtr13)fProc))( ppParam[0], ppParam[1], ppParam[2], ppParam[3], ppParam[4], ppParam[5],
/*N*/                                       ppParam[6], ppParam[7], ppParam[8], ppParam[9], ppParam[10], ppParam[11],
/*N*/                                       ppParam[12]);
/*N*/               bRet = TRUE;
/*N*/               break;
/*N*/           case 14 :
/*N*/               (*((ExFuncPtr14)fProc))( ppParam[0], ppParam[1], ppParam[2], ppParam[3], ppParam[4], ppParam[5],
/*N*/                                       ppParam[6], ppParam[7], ppParam[8], ppParam[9], ppParam[10], ppParam[11],
/*N*/                                       ppParam[12], ppParam[13]);
/*N*/               bRet = TRUE;
/*N*/               break;
/*N*/           case 15 :
/*N*/               (*((ExFuncPtr15)fProc))( ppParam[0], ppParam[1], ppParam[2], ppParam[3], ppParam[4], ppParam[5],
/*N*/                                       ppParam[6], ppParam[7], ppParam[8], ppParam[9], ppParam[10], ppParam[11],
/*N*/                                       ppParam[12], ppParam[13], ppParam[14]);
/*N*/               bRet = TRUE;
/*N*/               break;
/*N*/           case 16 :
/*N*/               (*((ExFuncPtr16)fProc))( ppParam[0], ppParam[1], ppParam[2], ppParam[3], ppParam[4], ppParam[5],
/*N*/                                       ppParam[6], ppParam[7], ppParam[8], ppParam[9], ppParam[10], ppParam[11],
/*N*/                                       ppParam[12], ppParam[13], ppParam[14], ppParam[15]);
/*N*/               bRet = TRUE;
/*N*/               break;
/*N*/           default : break;
/*N*/       }
/*N*/   }
/*N*/   return bRet;
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 BOOL FuncData::Advice( AdvData pfCallback )
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001  OModule* pLib = pModuleData->GetInstance();
//STRIP001  FARPROC fProc = (FARPROC)pLib->getSymbol(LIBFUNCNAME(ADVICE));
//STRIP001  if (fProc != NULL)
//STRIP001  {
//STRIP001      ((::Advice)fProc)(nNumber, pfCallback);
//STRIP001      bRet = TRUE;
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 BOOL FuncData::Unadvice( double nHandle )
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001  OModule* pLib = pModuleData->GetInstance();
//STRIP001  FARPROC fProc = (FARPROC)pLib->getSymbol(LIBFUNCNAME(UNADVICE));
//STRIP001  if (fProc != NULL)
//STRIP001  {
//STRIP001      ((::Unadvice)fProc)(nHandle);
//STRIP001      bRet = TRUE;
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 const String& FuncData::GetModuleName() const
//STRIP001 {
//STRIP001  // DBG_ASSERT( pModuleData, "Keine Arme, keine Kekse" ):
//STRIP001  return pModuleData->GetName();
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 BOOL FuncData::GetParamDesc( String& aName, String& aDesc, USHORT nParam )
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001  if ( nParam <= nParamCount )
//STRIP001  {
//STRIP001      OModule* pLib = pModuleData->GetInstance();
//STRIP001      FARPROC fProc = (FARPROC) pLib->getSymbol( LIBFUNCNAME(GETPARAMDESC) );
//STRIP001      if ( fProc != NULL )
//STRIP001      {
//STRIP001          sal_Char pcName[256];
//STRIP001          sal_Char pcDesc[256];
//STRIP001          *pcName = *pcDesc = 0;
//STRIP001          USHORT nFuncNo = nNumber;   // nicht per Reference versauen lassen..
//STRIP001          ((::GetParamDesc)fProc)( nFuncNo, nParam, pcName, pcDesc );
//STRIP001          aName = String( pcName, osl_getThreadTextEncoding() );
//STRIP001          aDesc = String( pcDesc, osl_getThreadTextEncoding() );
//STRIP001          bRet = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  if ( !bRet )
//STRIP001  {
//STRIP001      aName.Erase();
//STRIP001      aDesc.Erase();
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }


}
