/*************************************************************************
 *
 *  $RCSfile: starmath_symbol.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:40:22 $
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

#pragma hdrstop

#ifndef _OSL_MUTEX_HXX_
#include <osl/mutex.hxx>
#endif
#ifndef _UCBHELPER_CONTENT_HXX
#include <ucbhelper/content.hxx>
#endif
#ifndef _SV_MSGBOX_HXX //autogen
#include <vcl/msgbox.hxx>
#endif

#ifndef _SV_RESARY_HXX
#include <tools/resary.hxx>
#endif

#ifndef _SFXDISPATCH_HXX //autogen
#include <bf_sfx2/dispatch.hxx>
#endif
#ifndef _SFXDOCFILE_HXX
#include <bf_sfx2/docfile.hxx>
#endif

#include "symbol.hxx"
#include "view.hxx"
#include "utility.hxx"
#include "dialog.hxx"
#include "config.hxx"
#include "cfgitem.hxx"
#include "smmod.hxx"
#include "starmath.hrc"
namespace binfilter {


using namespace ::com::sun::star;
using namespace ::com::sun::star::ucb;
using namespace ::com::sun::star::uno;
using namespace ::rtl;

// Das hier muss auch mal alles "uberarbeitet werden. Insbesondere die nicht
// funktionierende und bei l"oschen/"andern von Symbolen nicht gepflegte
// Hash Tabelle!!!  Diese aktualisert sich erst im Wertzuweisungsoperator
// beim Verlassen des 'SmSymDefineDialog's!

/**************************************************************************/
/*
**
**  MACRO DEFINTION
**
**/

#define SF_SM20IDENT 0x03031963L
#define SF_IDENT     0x30334D53L


//STRIP001 SV_IMPL_PTRARR( SymbolArray, SmSym * );

/**************************************************************************/
/*
**
**  DATA DEFINITION
**
**/

long                SF_Ident = SF_IDENT;

/**************************************************************************/
/*
**
**  CLASS IMPLEMENTATION
**
**/

/*N*/ SmSym::SmSym() :
/*N*/   Name(C2S("unknown")),
/*N*/   Character('\0'),
/*N*/   pHashNext(0),
/*N*/   pSymSetManager(0),
/*N*/   bPredefined(FALSE),
/*N*/     bDocSymbol(FALSE),
/*N*/   aSetName(C2S("unknown"))
/*N*/ {
/*N*/   aExportName = Name;
/*N*/   Face.SetTransparent(TRUE);
/*N*/     Face.SetAlign(ALIGN_BASELINE);
/*N*/ }


/*N*/ SmSym::SmSym(const SmSym& rSymbol)
/*N*/ {
/*N*/   pSymSetManager = 0;
/*N*/     *this = rSymbol;
/*N*/ }


/*N*/ SmSym::SmSym(const String& rName, const Font& rFont, sal_Unicode aChar,
/*N*/            const String& rSet, BOOL bIsPredefined)
/*N*/ {
/*N*/   Name        = aExportName   = rName;
/*N*/
/*N*/     Face        = rFont;
/*N*/   Face.SetTransparent(TRUE);
/*N*/     Face.SetAlign(ALIGN_BASELINE);
/*N*/
/*N*/     Character   = aChar;
/*N*/     if (RTL_TEXTENCODING_SYMBOL == rFont.GetCharSet())
/*?*/         Character |= 0xF000;
/*N*/   aSetName    = rSet;
/*N*/   bPredefined = bIsPredefined;
/*N*/     bDocSymbol  = FALSE;
/*N*/
/*N*/   pHashNext      = 0;
/*N*/   pSymSetManager = 0;
/*N*/ }


/*N*/ SmSym& SmSym::operator = (const SmSym& rSymbol)
/*N*/ {
/*N*/   Name        = rSymbol.Name;
/*N*/   Face        = rSymbol.Face;
/*N*/   Character   = rSymbol.Character;
/*N*/   aSetName    = rSymbol.aSetName;
/*N*/   bPredefined = rSymbol.bPredefined;
/*N*/     bDocSymbol  = rSymbol.bDocSymbol;
/*N*/   aExportName = rSymbol.aExportName;
/*N*/
/*N*/   pHashNext = 0;
/*N*/
/*N*/     if (pSymSetManager)
/*?*/       pSymSetManager->SetModified(TRUE);
/*N*/
/*N*/   return *this;
/*N*/ }

//STRIP001 void SmSym::SetSymbolName(const String& rName)
//STRIP001 {
//STRIP001  Name    = rName;
//STRIP001
//STRIP001  if (pSymSetManager)
//STRIP001      pSymSetManager->SetModified(TRUE);
//STRIP001 }

//STRIP001 SvStream& operator << (SvStream& rStream, const SmSym& rSymbol)
//STRIP001 {
//STRIP001  rStream.WriteByteString( ExportString(rSymbol.Name) );
//STRIP001  rStream << rSymbol.Face;
//STRIP001
//STRIP001  rtl_TextEncoding eEnc = rSymbol.Face.GetCharSet();
//STRIP001  if (RTL_TEXTENCODING_DONTKNOW == eEnc)
//STRIP001      eEnc = RTL_TEXTENCODING_SYMBOL;
//STRIP001  rStream << ByteString::ConvertFromUnicode( rSymbol.Character, eEnc );
//STRIP001
//STRIP001  return rStream;
//STRIP001 }

//STRIP001 SvStream& operator >> (SvStream& rStream, SmSym& rSymbol)
//STRIP001 {
//STRIP001     ByteString aByteStr;
//STRIP001
//STRIP001     rStream.ReadByteString( aByteStr );
//STRIP001     rSymbol.Name = ImportString( aByteStr );
//STRIP001  if (SF_Ident == SF_SM20IDENT)
//STRIP001      ReadSM20Font(rStream, rSymbol.Face);
//STRIP001  else
//STRIP001      rStream >> rSymbol.Face;
//STRIP001  sal_Char cTemp;
//STRIP001  rStream >> cTemp;
//STRIP001
//STRIP001  rtl_TextEncoding eEnc = rSymbol.Face.GetCharSet();
//STRIP001  if (RTL_TEXTENCODING_DONTKNOW == eEnc)
//STRIP001      eEnc = RTL_TEXTENCODING_SYMBOL;
//STRIP001  rSymbol.Character = ByteString::ConvertToUnicode( cTemp, eEnc );
//STRIP001
//STRIP001  return rStream;
//STRIP001 }

/**************************************************************************/

//STRIP001 SmSymSet::SmSymSet() :
//STRIP001  Name(C2S("unknown")),
//STRIP001  pSymSetManager(0)
//STRIP001 {
//STRIP001  SymbolList.Clear();
//STRIP001 }

//STRIP001 SmSymSet::SmSymSet(const SmSymSet& rSymbolSet)
//STRIP001 {
//STRIP001  pSymSetManager = 0;
//STRIP001     *this = rSymbolSet;
//STRIP001 }

/*N*/ SmSymSet::SmSymSet(const String& rName)
/*N*/ {
/*N*/   Name = rName;
/*N*/   SymbolList.Clear();
/*N*/
/*N*/   pSymSetManager = 0;
/*N*/ }

//STRIP001 SmSymSet::~SmSymSet()
//STRIP001 {
//STRIP001  for (int i = 0; i < GetCount(); i++)
//STRIP001      delete SymbolList.GetObject(i);
//STRIP001 }

//STRIP001 SmSymSet& SmSymSet::operator = (const SmSymSet& rSymbolSet)
//STRIP001 {
//STRIP001  int i;
//STRIP001  for (i = 0; i < GetCount(); i++)
//STRIP001      delete SymbolList.GetObject(i);
//STRIP001
//STRIP001  Name = rSymbolSet.Name;
//STRIP001  SymbolList.Clear();
//STRIP001  for (i = 0; i < rSymbolSet.GetCount(); i++)
//STRIP001      AddSymbol(new SmSym(rSymbolSet.GetSymbol(i)));
//STRIP001
//STRIP001  if (pSymSetManager)
//STRIP001      pSymSetManager->SetModified(TRUE);
//STRIP001
//STRIP001  return *this;
//STRIP001 }

//STRIP001 void SmSymSet::SetName(String& rName)
//STRIP001 {
//STRIP001  Name = rName;
//STRIP001
//STRIP001  if (pSymSetManager)
//STRIP001      pSymSetManager->SetModified(TRUE);
//STRIP001 }

/*N*/ USHORT SmSymSet::AddSymbol(SmSym* pSymbol)
/*N*/ {
/*N*/   DBG_ASSERT(pSymbol, "Kein Symbol");
/*N*/
/*N*/     if (pSymbol)
/*N*/         pSymbol->SetSetName( GetName() );
/*N*/   SymbolList.Insert(pSymbol, LIST_APPEND);
/*N*/   DBG_ASSERT(SymbolList.GetPos(pSymbol) == SymbolList.Count() - 1,
/*N*/       "Sm : ... ergibt falschen return Wert");
/*N*/
/*N*/   if (pSymSetManager)
/*N*/       pSymSetManager->SetModified(TRUE);
/*N*/
/*N*/   return (USHORT) SymbolList.Count() - 1;
/*N*/ }

//STRIP001 void SmSymSet::DeleteSymbol(USHORT SymbolNo)
//STRIP001 {
//STRIP001  delete RemoveSymbol(SymbolNo);
//STRIP001 }

//STRIP001 SmSym *  SmSymSet::RemoveSymbol(USHORT SymbolNo)
//STRIP001 {
//STRIP001  DBG_ASSERT(SymbolList.GetObject(SymbolNo), "Symbol nicht vorhanden");
//STRIP001
//STRIP001  SmSym *pSym = SymbolList.GetObject(SymbolNo);
//STRIP001  SymbolList.Remove(SymbolNo);
//STRIP001
//STRIP001  if (pSymSetManager)
//STRIP001      pSymSetManager->SetModified(TRUE);
//STRIP001
//STRIP001  return pSym;
//STRIP001 }

//STRIP001 USHORT SmSymSet::GetSymbolPos(const String& rName)
//STRIP001 {
//STRIP001  for (USHORT i = 0; i < GetCount(); i++)
//STRIP001      if (SymbolList.GetObject(i)->GetName() == rName)
//STRIP001          return (i);
//STRIP001
//STRIP001  return SYMBOL_NONE;
//STRIP001 }

//STRIP001 SvStream& operator << (SvStream& rStream, const SmSymSet& rSymbolSet)
//STRIP001 {
//STRIP001  rStream.WriteByteString(ExportString(rSymbolSet.Name));
//STRIP001  rStream << rSymbolSet.GetCount();
//STRIP001
//STRIP001  for (int i = 0; i < rSymbolSet.GetCount(); i++)
//STRIP001      rStream << rSymbolSet.GetSymbol(i);
//STRIP001
//STRIP001  return rStream;
//STRIP001 }


//STRIP001 SvStream& operator >> (SvStream& rStream, SmSymSet& rSymbolSet)
//STRIP001 {
//STRIP001  USHORT      n;
//STRIP001  SmSym     *pSymbol;
//STRIP001     ByteString aByteStr;
//STRIP001
//STRIP001     rStream.ReadByteString( aByteStr );
//STRIP001     rSymbolSet.Name = ImportString( aByteStr );
//STRIP001  rStream >> n;
//STRIP001
//STRIP001  for (int i = 0; i < n; i++)
//STRIP001  {
//STRIP001      if ((pSymbol = new SmSym) == 0)
//STRIP001          break;
//STRIP001
//STRIP001      rStream >> *pSymbol;
//STRIP001      rSymbolSet.AddSymbol(pSymbol);
//STRIP001  }
//STRIP001
//STRIP001  return rStream;
//STRIP001 }

/**************************************************************************/

/*N*/ SmSymSetManager_Impl::SmSymSetManager_Impl(
/*N*/         SmSymSetManager &rMgr, USHORT HashTableSize ) :
/*N*/
/*N*/     rSymSetMgr    (rMgr)
/*N*/ {
/*N*/     NoSymbolSets    = 0;
/*N*/     NoHashEntries   = HashTableSize;
/*N*/     HashEntries     = new SmSym *[NoHashEntries];
/*N*/     memset( HashEntries, 0, sizeof(SmSym *) * NoHashEntries );
/*N*/     Modified        = FALSE;
/*N*/ }


//STRIP001 SmSymSetManager_Impl::~SmSymSetManager_Impl()
//STRIP001 {
//STRIP001     for (USHORT i = 0;  i < NoSymbolSets;  ++i)
//STRIP001         delete SymbolSets.Get(i);
//STRIP001     SymbolSets.Clear();
//STRIP001
//STRIP001     NoSymbolSets = 0;
//STRIP001     if (HashEntries)
//STRIP001     {
//STRIP001         delete[] HashEntries;
//STRIP001         HashEntries = 0;
//STRIP001     }
//STRIP001     NoHashEntries = 0;
//STRIP001     Modified = FALSE;
//STRIP001 }


//STRIP001 SmSymSetManager_Impl & SmSymSetManager_Impl::operator = ( const SmSymSetManager_Impl &rImpl )
//STRIP001 {
//STRIP001     //! rMySymSetMgr remains unchanged
//STRIP001
//STRIP001     NoHashEntries   = rImpl.NoHashEntries;
//STRIP001     if (HashEntries)
//STRIP001         delete [] HashEntries;
//STRIP001     HashEntries = new SmSym *[NoHashEntries];
//STRIP001     memset( HashEntries, 0, sizeof(SmSym *) * NoHashEntries );
//STRIP001
//STRIP001     NoSymbolSets    = 0;
//STRIP001     SymbolSets.Clear();
//STRIP001     for (USHORT i = 0;  i < rImpl.NoSymbolSets;  ++i)
//STRIP001     {
//STRIP001         rSymSetMgr.AddSymbolSet( new SmSymSet( *rImpl.rSymSetMgr.GetSymbolSet(i) ) );
//STRIP001     }
//STRIP001     DBG_ASSERT( NoSymbolSets == rImpl.NoSymbolSets,
//STRIP001             "incorrect number of symbolsets" );
//STRIP001
//STRIP001     Modified        = TRUE;
//STRIP001     return *this;
//STRIP001 }

/**************************************************************************/

//STRIP001 static osl::Mutex & lcl_GetSymSetMgrMutex()
//STRIP001 {
//STRIP001  static osl::Mutex   aMutex;
//STRIP001  return aMutex;
//STRIP001 }


//STRIP001 void SmSymSetManager::SFX_NOTIFY(SfxBroadcaster& rBC, const TypeId& rBCType,
//STRIP001                            const SfxHint& rHint, const TypeId& rHintType)
//STRIP001 {
//STRIP001 }


/*N*/ UINT32 SmSymSetManager::GetHashIndex(const String& rSymbolName)
/*N*/ {
/*N*/     UINT32 x = 1;
/*N*/   for (xub_StrLen i = 0; i < rSymbolName.Len(); i++)
/*N*/         x += x * rSymbolName.GetChar(i) + i;
/*N*/
/*N*/   return x % pImpl->NoHashEntries;
/*N*/ }


/*N*/ void SmSymSetManager::EnterHashTable(SmSym& rSymbol)
/*N*/ {
/*N*/     int j = GetHashIndex( rSymbol.GetName() );
/*N*/     if (pImpl->HashEntries[j] == 0)
/*N*/         pImpl->HashEntries[j] = &rSymbol;
/*N*/     else
/*N*/     {
/*N*/         SmSym *p = pImpl->HashEntries[j];
/*N*/         while (p->pHashNext)
/*N*/             p = p->pHashNext;
/*N*/         p->pHashNext = &rSymbol;
/*N*/     }
/*N*/     rSymbol.pHashNext = 0;
/*N*/ }


/*N*/ void SmSymSetManager::EnterHashTable(SmSymSet& rSymbolSet)
/*N*/ {
/*N*/   for (int i = 0; i < rSymbolSet.GetCount(); i++)
/*N*/         EnterHashTable( *rSymbolSet.SymbolList.GetObject(i) );
/*N*/ }

/*N*/ void SmSymSetManager::FillHashTable()
/*N*/ {
/*N*/   if (pImpl->HashEntries)
/*N*/   {
/*N*/       memset( pImpl->HashEntries, 0, pImpl->NoHashEntries * sizeof(SmSym *) );
/*N*/
/*N*/       for (UINT32 i = 0; i < pImpl->NoSymbolSets; i++)
/*N*/           EnterHashTable( *GetSymbolSet( (USHORT) i ) );
/*N*/   }
/*N*/ }

//STRIP001 void SmSymSetManager::Init()
//STRIP001 {
//STRIP001  SmModule *pp = SM_MOD1();
//STRIP001  StartListening(*pp->GetConfig());
//STRIP001 }


//STRIP001 void SmSymSetManager::Exit()
//STRIP001 {
//STRIP001  SmModule *pp = SM_MOD1();
//STRIP001  EndListening(*pp->GetConfig());
//STRIP001 }


/*N*/ SmSymSetManager::SmSymSetManager(USHORT HashTableSize)
/*N*/ {
/*N*/     pImpl = new SmSymSetManager_Impl( *this, HashTableSize );
/*N*/ }


//STRIP001 SmSymSetManager::SmSymSetManager(const SmSymSetManager& rSymbolSetManager)
//STRIP001 {
//STRIP001     pImpl = new SmSymSetManager_Impl( *this, rSymbolSetManager.pImpl->NoHashEntries );
//STRIP001     *pImpl = *rSymbolSetManager.pImpl;
//STRIP001 }


//STRIP001 SmSymSetManager::~SmSymSetManager()
//STRIP001 {
//STRIP001     delete pImpl;
//STRIP001     pImpl = 0;
//STRIP001 }

//STRIP001 SmSymSetManager& SmSymSetManager::operator = (const SmSymSetManager& rSymbolSetManager)
//STRIP001 {
//STRIP001     *pImpl = *rSymbolSetManager.pImpl;
//STRIP001  return *this;
//STRIP001 }

/*N*/ USHORT SmSymSetManager::AddSymbolSet(SmSymSet* pSymbolSet)
/*N*/ {
/*N*/   if (pImpl->NoSymbolSets >= pImpl->SymbolSets.GetSize())
/*?*/       pImpl->SymbolSets.SetSize(pImpl->NoSymbolSets + 1);
/*N*/
/*N*/   pImpl->SymbolSets.Put(pImpl->NoSymbolSets++, pSymbolSet);
/*N*/
/*N*/   pSymbolSet->pSymSetManager = this;
/*N*/
/*N*/   for (int i = 0; i < pSymbolSet->GetCount(); i++)
/*?*/       pSymbolSet->SymbolList.GetObject(i)->pSymSetManager = this;
/*N*/
/*N*/   FillHashTable();
/*N*/   pImpl->Modified = TRUE;
/*N*/
/*N*/   return (USHORT) (pImpl->NoSymbolSets - 1);
/*N*/ }

/*N*/ void SmSymSetManager::ChangeSymbolSet(SmSymSet* pSymbolSet)
/*N*/ {
/*N*/   if (pSymbolSet)
/*N*/   {
/*N*/       FillHashTable();
/*N*/       pImpl->Modified = TRUE;
/*N*/   }
/*N*/ }

//STRIP001 void SmSymSetManager::DeleteSymbolSet(USHORT SymbolSetNo)
//STRIP001 {
//STRIP001  delete pImpl->SymbolSets.Get(SymbolSetNo);
//STRIP001  pImpl->NoSymbolSets--;
//STRIP001
//STRIP001  for (UINT32 i = SymbolSetNo; i < pImpl->NoSymbolSets; i++)
//STRIP001      pImpl->SymbolSets.Put(i, pImpl->SymbolSets.Get(i + 1));
//STRIP001
//STRIP001  FillHashTable();
//STRIP001
//STRIP001  pImpl->Modified = TRUE;
//STRIP001 }


/*N*/ USHORT SmSymSetManager::GetSymbolSetPos(const String& rSymbolSetName) const
/*N*/ {
/*N*/   for (USHORT i = 0; i < pImpl->NoSymbolSets; i++)
/*N*/       if (pImpl->SymbolSets.Get(i)->GetName() == rSymbolSetName)
/*N*/           return (i);
/*N*/
/*N*/   return SYMBOLSET_NONE;
/*N*/ }

/*N*/ SmSym *SmSymSetManager::GetSymbolByName(const String& rSymbolName)
/*N*/ {
/*N*/     SmSym *pSym = pImpl->HashEntries[GetHashIndex(rSymbolName)];
/*N*/     while (pSym)
/*N*/     {
/*N*/         if (pSym->Name == rSymbolName)
/*N*/             break;
/*N*/         pSym = pSym->pHashNext;
/*N*/     }
/*N*/
/*N*/   return pSym;
/*N*/ }


/*N*/ void SmSymSetManager::AddReplaceSymbol( const SmSym &rSymbol )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001     SmSym *pSym = GetSymbolByName( rSymbol.GetName() );
//STRIP001     if (pSym)
//STRIP001     {
//STRIP001         *pSym = rSymbol;
//STRIP001     }
//STRIP001     else
//STRIP001     {
//STRIP001         USHORT nPos = GetSymbolSetPos( rSymbol.GetSetName() );
//STRIP001         if (SYMBOLSET_NONE == nPos)
//STRIP001         {
//STRIP001             AddSymbolSet( new SmSymSet( rSymbol.GetSetName() ) );
//STRIP001             nPos = GetSymbolSetPos( rSymbol.GetSetName() );
//STRIP001         }
//STRIP001         DBG_ASSERT( nPos != SYMBOLSET_NONE, "SymbolSet not found");
//STRIP001         SmSym *pSym = new SmSym( rSymbol );
//STRIP001         GetSymbolSet( nPos )->AddSymbol( pSym );
//STRIP001         EnterHashTable( *pSym );
//STRIP001     }
//STRIP001     SetModified( TRUE );
/*N*/ }


/*N*/ USHORT SmSymSetManager::GetSymbolCount() const
/*N*/ {
/*N*/     USHORT nRes = 0;
/*N*/     USHORT nSets = GetSymbolSetCount();
/*N*/     for (USHORT i = 0;  i < nSets;  ++i)
/*N*/         nRes += GetSymbolSet(i)->GetCount();
/*N*/     return nRes;
/*N*/ }


/*N*/ const SmSym * SmSymSetManager::GetSymbolByPos( USHORT nPos ) const
/*N*/ {
/*N*/     const SmSym *pRes = 0;
/*N*/
/*N*/     INT16 nIdx = 0;
/*N*/     USHORT nSets = GetSymbolSetCount();
/*N*/     USHORT i = 0;
/*N*/     while (i < nSets  &&  !pRes)
/*N*/     {
/*N*/         USHORT nEntries = GetSymbolSet(i)->GetCount();
/*N*/         if (nPos < nIdx + nEntries)
/*N*/             pRes = &GetSymbolSet(i)->GetSymbol( nPos - nIdx );
/*N*/         else
/*N*/             nIdx += nEntries;
/*N*/         ++i;
/*N*/     }
/*N*/
/*N*/     return pRes;
/*N*/ }


/*N*/ void SmSymSetManager::Load()
/*N*/ {
/*N*/     SmMathConfig &rCfg = *SM_MOD1()->GetConfig();
/*N*/
/*N*/     USHORT nCount = rCfg.GetSymbolCount();
/*N*/     USHORT i;
/*N*/     for (i = 0;  i < nCount;  ++i)
/*N*/     {
/*N*/         const SmSym *pSym = rCfg.GetSymbol(i);
/*N*/         if (pSym)
/*N*/         {
/*N*/             SmSymSet *pSymSet = 0;
/*N*/             const String &rSetName = pSym->GetSetName();
/*N*/             USHORT nSetPos = GetSymbolSetPos( rSetName );
/*N*/             if (SYMBOLSET_NONE != nSetPos)
/*N*/                 pSymSet = GetSymbolSet( nSetPos );
/*N*/             else
/*N*/             {
/*N*/                 pSymSet = new SmSymSet( rSetName );
/*N*/                 AddSymbolSet( pSymSet );
/*N*/             }
/*N*/
/*N*/             pSymSet->AddSymbol( new SmSym( *pSym ) );
/*N*/         }
/*N*/     }
/*N*/     // build HashTables
/*N*/     nCount = GetSymbolSetCount();
/*N*/     for (i = 0;  i < nCount;  ++i)
/*N*/         ChangeSymbolSet( GetSymbolSet( i ) );
/*N*/
/*N*/     if (0 == nCount)
/*N*/     {
/*N*/         DBG_ERROR( "no symbol set found" );
/*N*/         pImpl->Modified = FALSE;
/*N*/     }
/*N*/ }

//STRIP001 void SmSymSetManager::Save()
//STRIP001 {
//STRIP001     SmMathConfig &rCfg = *SM_MOD1()->GetConfig();
//STRIP001
//STRIP001     // get number of Symbols
//STRIP001     USHORT nSymbolCount = 0;
//STRIP001     USHORT nSetCount = GetSymbolSetCount();
//STRIP001     USHORT i;
//STRIP001     for (i = 0;  i < nSetCount;  ++i)
//STRIP001         nSymbolCount += GetSymbolSet( i )->GetCount();
//STRIP001
//STRIP001     if (nSymbolCount)
//STRIP001     {
//STRIP001         USHORT nSaveSymbolCnt = 0;
//STRIP001         const SmSym **pSymbols = new const SmSym* [ nSymbolCount ];
//STRIP001         const SmSym **pSym = pSymbols;
//STRIP001         for (i = 0;  i < nSetCount;  ++i)
//STRIP001         {
//STRIP001             const SmSymSet *pSymSet = GetSymbolSet( i );
//STRIP001             USHORT n = pSymSet->GetCount();
//STRIP001             for (USHORT j = 0;  j < n;  ++j)
//STRIP001             {
//STRIP001                 const SmSym &rSym = pSymSet->GetSymbol( j );
//STRIP001                 if (!rSym.IsDocSymbol())
//STRIP001                 {
//STRIP001                     *pSym++ = &rSym;
//STRIP001                     ++nSaveSymbolCnt;
//STRIP001                 }
//STRIP001             }
//STRIP001         }
//STRIP001         DBG_ASSERT(pSym - pSymbols == nSaveSymbolCnt, "wrong number of symbols" );
//STRIP001         rCfg.ReplaceSymbols( pSymbols, nSaveSymbolCnt );
//STRIP001         delete [] pSymbols;
//STRIP001     }
//STRIP001 }


//STRIP001 void ReadSM20SymSet(SvStream *pStream, SmSymSet *pSymbolSet)
//STRIP001 {
//STRIP001  SF_Ident = SF_SM20IDENT;
//STRIP001  *pStream >> *pSymbolSet;
//STRIP001  SF_Ident = SF_IDENT;
//STRIP001 }


}
