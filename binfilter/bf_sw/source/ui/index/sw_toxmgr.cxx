/*************************************************************************
 *
 *  $RCSfile: sw_toxmgr.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:19:58 $
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

#ifndef _WRTSH_HXX
#include <wrtsh.hxx>
#endif
#ifndef _SHELLRES_HXX
#include <shellres.hxx>
#endif
#ifndef _SWWAIT_HXX
#include <swwait.hxx>
#endif
#ifndef _SWVIEW_HXX
#include <view.hxx>
#endif
#ifndef _TOXMGR_HXX
#include <toxmgr.hxx>
#endif
#ifndef _AUTHFLD_HXX
#include <authfld.hxx>
#endif
#ifndef _CRSSKIP_HXX
#include <crsskip.hxx>
#endif

#ifndef _GLOBALS_HRC
#include <globals.hrc>
#endif

/*-----------------23.01.98 07:41-------------------
    Standard - Verzeichnisnamen herausreichen
--------------------------------------------------*/
/*N*/ const String& SwTOXBase::GetTOXName(TOXTypes eType)
/*N*/ {
/*N*/   const String* pRet;
/*N*/   ShellResource* pShellRes = ViewShell::GetShellRes();
/*N*/   switch(eType)
/*N*/   {
/*N*/       case  TOX_CONTENT      :    pRet = &pShellRes->aTOXContentName;       break;
/*N*/       case  TOX_INDEX        :    pRet = &pShellRes->aTOXIndexName;         break;
/*?*/       case  TOX_USER         :    pRet = &pShellRes->aTOXUserName;          break;
/*?*/       case  TOX_ILLUSTRATIONS:    pRet = &pShellRes->aTOXIllustrationsName; break;
/*?*/       case  TOX_OBJECTS      :    pRet = &pShellRes->aTOXObjectsName;       break;
/*?*/       case  TOX_TABLES       :    pRet = &pShellRes->aTOXTablesName;        break;
/*?*/       case  TOX_AUTHORITIES :     pRet = &pShellRes->aTOXAuthoritiesName;   break;
/*N*/   }
/*N*/   return *pRet;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: Handhabung der Verzeichnisse durch TOXMgr
 --------------------------------------------------------------------*/


//STRIP001 SwTOXMgr::SwTOXMgr(SwWrtShell* pShell):
//STRIP001  pSh(pShell)
//STRIP001 {
//STRIP001  GetTOXMarks();
//STRIP001  SetCurTOXMark(0);
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung: Aktuelle TOXMarks behandeln
 --------------------------------------------------------------------*/


//STRIP001 USHORT SwTOXMgr::GetTOXMarks()
//STRIP001 {
//STRIP001  return pSh->GetCurTOXMarks(aCurMarks);
//STRIP001 }


//STRIP001 SwTOXMark* SwTOXMgr::GetTOXMark(USHORT nId)
//STRIP001 {
//STRIP001  if(aCurMarks.Count() > 0)
//STRIP001      return aCurMarks[nId];
//STRIP001  return 0;
//STRIP001 }


//STRIP001 void SwTOXMgr::DeleteTOXMark()
//STRIP001 {
//STRIP001  SwTOXMark* pNext = 0;
//STRIP001  if( pCurTOXMark )
//STRIP001  {
//STRIP001      pNext = (SwTOXMark*)&pSh->GotoTOXMark( *pCurTOXMark, TOX_NXT );
//STRIP001      if( pNext == pCurTOXMark )
//STRIP001          pNext = 0;
//STRIP001
//STRIP001      pSh->DeleteTOXMark( pCurTOXMark );
//STRIP001      pSh->SetModified();
//STRIP001  }
//STRIP001  // zur naechsten wandern
//STRIP001  pCurTOXMark = pNext;
//STRIP001 }
/* -----------------20.08.99 10:48-------------------

 --------------------------------------------------*/
//STRIP001 void SwTOXMgr::InsertTOXMark(const SwTOXMarkDescription& rDesc)
//STRIP001 {
//STRIP001  SwTOXMark* pMark = 0;
//STRIP001  switch(rDesc.GetTOXType())
//STRIP001  {
//STRIP001      case  TOX_CONTENT:
//STRIP001      {
//STRIP001          ASSERT(rDesc.GetLevel() > 0 && rDesc.GetLevel() <= MAXLEVEL,
//STRIP001                                          ungueltiger Level InsertTOCMark);
//STRIP001          pMark = new SwTOXMark(pSh->GetTOXType(TOX_CONTENT, 0));
//STRIP001          pMark->SetLevel(rDesc.GetLevel());
//STRIP001
//STRIP001          if(rDesc.GetAltStr())
//STRIP001              pMark->SetAlternativeText(*rDesc.GetAltStr());
//STRIP001      }
//STRIP001      break;
//STRIP001      case  TOX_INDEX:
//STRIP001      {
//STRIP001          pMark = new SwTOXMark(pSh->GetTOXType(TOX_INDEX, 0));
//STRIP001
//STRIP001          if( rDesc.GetPrimKey() && rDesc.GetPrimKey()->Len() )
//STRIP001          {
//STRIP001              pMark->SetPrimaryKey( *rDesc.GetPrimKey() );
//STRIP001              if(rDesc.GetPhoneticReadingOfPrimKey())
//STRIP001                  pMark->SetPrimaryKeyReading( *rDesc.GetPhoneticReadingOfPrimKey() );
//STRIP001
//STRIP001              if( rDesc.GetSecKey() && rDesc.GetSecKey()->Len() )
//STRIP001              {
//STRIP001                  pMark->SetSecondaryKey( *rDesc.GetSecKey() );
//STRIP001                  if(rDesc.GetPhoneticReadingOfSecKey())
//STRIP001                      pMark->SetSecondaryKeyReading( *rDesc.GetPhoneticReadingOfSecKey() );
//STRIP001              }
//STRIP001          }
//STRIP001          if(rDesc.GetAltStr())
//STRIP001              pMark->SetAlternativeText(*rDesc.GetAltStr());
//STRIP001          if(rDesc.GetPhoneticReadingOfAltStr())
//STRIP001              pMark->SetTextReading( *rDesc.GetPhoneticReadingOfAltStr() );
//STRIP001          pMark->SetMainEntry(rDesc.IsMainEntry());
//STRIP001      }
//STRIP001      break;
//STRIP001      case  TOX_USER:
//STRIP001      {
//STRIP001          ASSERT(rDesc.GetLevel() > 0 && rDesc.GetLevel() <= MAXLEVEL,
//STRIP001                                          ungueltiger Level InsertTOCMark);
//STRIP001          USHORT nId = rDesc.GetTOUName() ?
//STRIP001              GetUserTypeID(*rDesc.GetTOUName()) : 0;
//STRIP001          pMark = new SwTOXMark(pSh->GetTOXType(TOX_USER, nId));
//STRIP001          pMark->SetLevel(rDesc.GetLevel());
//STRIP001
//STRIP001          if(rDesc.GetAltStr())
//STRIP001              pMark->SetAlternativeText(*rDesc.GetAltStr());
//STRIP001      }
//STRIP001      break;
//STRIP001  }
//STRIP001  pSh->StartAllAction();
//STRIP001  pSh->SwEditShell::Insert(*pMark);
//STRIP001  pSh->EndAllAction();
//STRIP001 }
/*--------------------------------------------------------------------
    Beschreibung: Update eines TOXMarks
 --------------------------------------------------------------------*/


//STRIP001 void SwTOXMgr::UpdateTOXMark(const SwTOXMarkDescription& rDesc)
//STRIP001 {
//STRIP001  ASSERT(pCurTOXMark, "kein aktuelles TOXMark");
//STRIP001
//STRIP001  pSh->StartAllAction();
//STRIP001  if(pCurTOXMark->GetTOXType()->GetType() == TOX_INDEX)
//STRIP001  {
//STRIP001      if(rDesc.GetPrimKey() && rDesc.GetPrimKey()->Len() )
//STRIP001      {
//STRIP001          pCurTOXMark->SetPrimaryKey( *rDesc.GetPrimKey() );
//STRIP001          if(rDesc.GetPhoneticReadingOfPrimKey())
//STRIP001              pCurTOXMark->SetPrimaryKeyReading( *rDesc.GetPhoneticReadingOfPrimKey() );
//STRIP001          else
//STRIP001              pCurTOXMark->SetPrimaryKeyReading( aEmptyStr );
//STRIP001
//STRIP001          if( rDesc.GetSecKey() && rDesc.GetSecKey()->Len() )
//STRIP001          {
//STRIP001              pCurTOXMark->SetSecondaryKey( *rDesc.GetSecKey() );
//STRIP001              if(rDesc.GetPhoneticReadingOfSecKey())
//STRIP001                  pCurTOXMark->SetSecondaryKeyReading( *rDesc.GetPhoneticReadingOfSecKey() );
//STRIP001              else
//STRIP001                  pCurTOXMark->SetSecondaryKeyReading( aEmptyStr );
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              pCurTOXMark->SetSecondaryKey( aEmptyStr );
//STRIP001              pCurTOXMark->SetSecondaryKeyReading( aEmptyStr );
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          pCurTOXMark->SetPrimaryKey( aEmptyStr );
//STRIP001          pCurTOXMark->SetPrimaryKeyReading( aEmptyStr );
//STRIP001          pCurTOXMark->SetSecondaryKey( aEmptyStr );
//STRIP001          pCurTOXMark->SetSecondaryKeyReading( aEmptyStr );
//STRIP001      }
//STRIP001      if(rDesc.GetPhoneticReadingOfAltStr())
//STRIP001          pCurTOXMark->SetTextReading( *rDesc.GetPhoneticReadingOfAltStr() );
//STRIP001      else
//STRIP001          pCurTOXMark->SetTextReading( aEmptyStr );
//STRIP001      pCurTOXMark->SetMainEntry(rDesc.IsMainEntry());
//STRIP001  }
//STRIP001  else
//STRIP001      pCurTOXMark->SetLevel(rDesc.GetLevel());
//STRIP001
//STRIP001  if(rDesc.GetAltStr())
//STRIP001  {
//STRIP001      // JP 26.08.96: Bug 30344 - entweder der Text aus dem Doc oder
//STRIP001      //                          ein Alternativ-Text, beides gibts nicht!
//STRIP001      BOOL bReplace = pCurTOXMark->IsAlternativeText();
//STRIP001      if( bReplace )
//STRIP001          pCurTOXMark->SetAlternativeText( *rDesc.GetAltStr() );
//STRIP001      else
//STRIP001      {
//STRIP001          SwTOXMark aCpy( *pCurTOXMark );
//STRIP001          aCurMarks.Remove(0, aCurMarks.Count());
//STRIP001          pSh->DeleteTOXMark(pCurTOXMark);
//STRIP001          aCpy.SetAlternativeText( *rDesc.GetAltStr() );
//STRIP001          pSh->SwEditShell::Insert( aCpy );
//STRIP001          pCurTOXMark = 0;
//STRIP001      }
//STRIP001  }
//STRIP001  pSh->SetModified();
//STRIP001  pSh->EndAllAction();
//STRIP001  // Bug 36207 pCurTOXMark zeigt hier in den Wald!
//STRIP001  if(!pCurTOXMark)
//STRIP001  {
//STRIP001      pSh->Left(CRSR_SKIP_CHARS, FALSE, 1, FALSE );
//STRIP001      pSh->GetCurTOXMarks(aCurMarks);
//STRIP001      SetCurTOXMark(0);
//STRIP001  }
//STRIP001 }


/*--------------------------------------------------------------------
    Beschreibung:   UserTypeID ermitteln
 --------------------------------------------------------------------*/


//STRIP001 USHORT SwTOXMgr::GetUserTypeID(const String& rStr)
//STRIP001 {
//STRIP001  USHORT nSize = pSh->GetTOXTypeCount(TOX_USER);
//STRIP001  for(USHORT i=0; i < nSize; ++i)
//STRIP001  {
//STRIP001      const SwTOXType* pTmp = pSh->GetTOXType(TOX_USER, i);
//STRIP001      if(pTmp && pTmp->GetTypeName() == rStr)
//STRIP001          return i;
//STRIP001  }
//STRIP001  SwTOXType aUserType(TOX_USER, rStr);
//STRIP001  pSh->InsertTOXType(aUserType);
//STRIP001  return nSize;
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung: Traveling zwischen den TOXMarks
 --------------------------------------------------------------------*/


//STRIP001 void SwTOXMgr::NextTOXMark(BOOL bSame)
//STRIP001 {
//STRIP001  ASSERT(pCurTOXMark, "kein aktuelles TOXMark");
//STRIP001  if( pCurTOXMark )
//STRIP001  {
//STRIP001      SwTOXSearch eDir = bSame ? TOX_SAME_NXT : TOX_NXT;
//STRIP001      pCurTOXMark = (SwTOXMark*)&pSh->GotoTOXMark( *pCurTOXMark, eDir );
//STRIP001  }
//STRIP001 }


//STRIP001 void SwTOXMgr::PrevTOXMark(BOOL bSame)
//STRIP001 {
//STRIP001  ASSERT(pCurTOXMark, "kein aktuelles TOXMark");
//STRIP001  if( pCurTOXMark )
//STRIP001  {
//STRIP001      SwTOXSearch eDir = bSame ? TOX_SAME_PRV : TOX_PRV;
//STRIP001      pCurTOXMark = (SwTOXMark*)&pSh->GotoTOXMark(*pCurTOXMark, eDir );
//STRIP001  }
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung: Stichwortverzeichnis einfuegen
 --------------------------------------------------------------------*/
//STRIP001 const SwTOXBase* SwTOXMgr::GetCurTOX()
//STRIP001 {
//STRIP001  return pSh->GetCurTOX();
//STRIP001 }

//STRIP001 const SwTOXType* SwTOXMgr::GetTOXType(TOXTypes eTyp, USHORT nId) const
//STRIP001 {
//STRIP001  return pSh->GetTOXType(eTyp, nId);
//STRIP001 }

//STRIP001 void SwTOXMgr::SetCurTOXMark(USHORT nId)
//STRIP001 {
//STRIP001  pCurTOXMark = (nId < aCurMarks.Count()) ? aCurMarks[nId] : 0;
//STRIP001 }

/* -----------------01.07.99 16:23-------------------

 --------------------------------------------------*/

//STRIP001 BOOL SwTOXMgr::UpdateOrInsertTOX(const SwTOXDescription& rDesc,
//STRIP001                                  SwTOXBase** ppBase,
//STRIP001                                  const SfxItemSet* pSet)
//STRIP001 {
//STRIP001  SwWait aWait( *pSh->GetView().GetDocShell(), TRUE );
//STRIP001  BOOL bRet = TRUE;
//STRIP001  const SwTOXBase* pCurTOX = ppBase && *ppBase ? *ppBase : GetCurTOX();
//STRIP001  SwTOXBase* pTOX = (SwTOXBase*)pCurTOX;
//STRIP001  TOXTypes eCurTOXType = rDesc.GetTOXType();
//STRIP001  if(pCurTOX && !ppBase && pSh->HasSelection())
//STRIP001      pSh->DelRight();
//STRIP001
//STRIP001  switch(eCurTOXType)
//STRIP001  {
//STRIP001      case TOX_INDEX :
//STRIP001      {
//STRIP001          if(!pCurTOX || (ppBase && !(*ppBase)))
//STRIP001          {
//STRIP001              const SwTOXType* pType = pSh->GetTOXType(eCurTOXType, 0);
//STRIP001              SwForm aForm(eCurTOXType);
//STRIP001              pTOX = new SwTOXBase(pType, aForm, TOX_MARK, pType->GetTypeName());
//STRIP001          }
//STRIP001          pTOX->SetOptions(rDesc.GetIndexOptions());
//STRIP001          pTOX->SetMainEntryCharStyle(rDesc.GetMainEntryCharStyle());
//STRIP001          pSh->SetTOIAutoMarkURL(rDesc.GetAutoMarkURL());
//STRIP001          pSh->ApplyAutoMark();
//STRIP001      }
//STRIP001      break;
//STRIP001      case TOX_CONTENT :
//STRIP001      {
//STRIP001          if(!pCurTOX || (ppBase && !(*ppBase)))
//STRIP001          {
//STRIP001              const SwTOXType* pType = pSh->GetTOXType(eCurTOXType, 0);
//STRIP001              SwForm aForm(eCurTOXType);
//STRIP001              pTOX = new SwTOXBase(pType, aForm, rDesc.GetContentOptions(), pType->GetTypeName());
//STRIP001          }
//STRIP001          pTOX->SetCreate(rDesc.GetContentOptions());
//STRIP001          pTOX->SetLevel(rDesc.GetLevel());
//STRIP001      }
//STRIP001      break;
//STRIP001      case TOX_USER :
//STRIP001      {
//STRIP001          if(!pCurTOX || (ppBase && !(*ppBase)))
//STRIP001          {
//STRIP001              USHORT nPos  = 0;
//STRIP001              USHORT nSize = pSh->GetTOXTypeCount(eCurTOXType);
//STRIP001              for(USHORT i=0; rDesc.GetTOUName() && i < nSize; ++i)
//STRIP001              {   const SwTOXType* pType = pSh->GetTOXType(TOX_USER, i);
//STRIP001                  if(pType->GetTypeName() == *rDesc.GetTOUName())
//STRIP001                  {   nPos = i;
//STRIP001                      break;
//STRIP001                  }
//STRIP001              }
//STRIP001              const SwTOXType* pType = pSh->GetTOXType(eCurTOXType, nPos);
//STRIP001
//STRIP001              SwForm aForm(eCurTOXType);
//STRIP001              pTOX = new SwTOXBase(pType, aForm, rDesc.GetContentOptions(), pType->GetTypeName());
//STRIP001
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              SwTOXBase* pTOX = (SwTOXBase*)pCurTOX;
//STRIP001              pTOX->SetCreate(rDesc.GetContentOptions());
//STRIP001          }
//STRIP001          pTOX->SetLevelFromChapter(rDesc.IsLevelFromChapter());
//STRIP001      }
//STRIP001      break;
//STRIP001      case TOX_OBJECTS:
//STRIP001      case TOX_TABLES:
//STRIP001      case TOX_AUTHORITIES:
//STRIP001      case TOX_ILLUSTRATIONS:
//STRIP001      {
//STRIP001          //Special handling for TOX_AUTHORITY
//STRIP001          if(TOX_AUTHORITIES == eCurTOXType)
//STRIP001          {
//STRIP001              SwAuthorityFieldType* pFType = (SwAuthorityFieldType*)
//STRIP001                                              pSh->GetFldType(RES_AUTHORITY, aEmptyStr);
//STRIP001                 if(!pFType)
//STRIP001                     pFType = (SwAuthorityFieldType*)pSh->InsertFldType(
//STRIP001                                     SwAuthorityFieldType(pSh->GetDoc()));
//STRIP001                  pFType->SetPreSuffix(rDesc.GetAuthBrackets().GetChar(0),
//STRIP001                      rDesc.GetAuthBrackets().GetChar(1));
//STRIP001                  pFType->SetSequence(rDesc.IsAuthSequence());
//STRIP001                  SwTOXSortKey rArr[3];
//STRIP001                  rArr[0] = rDesc.GetSortKey1();
//STRIP001                  rArr[1] = rDesc.GetSortKey2();
//STRIP001                  rArr[2] = rDesc.GetSortKey3();
//STRIP001                  pFType->SetSortKeys(3, rArr);
//STRIP001                  pFType->SetSortByDocument(rDesc.IsSortByDocument());
//STRIP001                     pFType->SetLanguage(rDesc.GetLanguage());
//STRIP001                     pFType->SetSortAlgorithm(rDesc.GetSortAlgorithm());
//STRIP001
//STRIP001                  pFType->UpdateFlds();
//STRIP001              }
//STRIP001          // TODO: consider properties of the current TOXType
//STRIP001          if(!pCurTOX || (ppBase && !(*ppBase)))
//STRIP001          {
//STRIP001              const SwTOXType* pType = pSh->GetTOXType(eCurTOXType, 0);
//STRIP001              SwForm aForm(eCurTOXType);
//STRIP001              pTOX = new SwTOXBase(
//STRIP001                  pType, aForm,
//STRIP001                  TOX_AUTHORITIES == eCurTOXType ? TOX_MARK : 0, pType->GetTypeName());
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              if((!ppBase || !(*ppBase)) && pSh->HasSelection())
//STRIP001                  pSh->DelRight();
//STRIP001              pTOX = (SwTOXBase*)pCurTOX;
//STRIP001          }
//STRIP001 //           pTOX->SetOptions(rDesc.GetIndexOptions());
//STRIP001          pTOX->SetFromObjectNames(rDesc.IsCreateFromObjectNames());
//STRIP001          pTOX->SetOLEOptions(rDesc.GetOLEOptions());
//STRIP001      }
//STRIP001      break;
//STRIP001  }
//STRIP001
//STRIP001
//STRIP001  DBG_ASSERT(pTOX, "no TOXBase created!" )
//STRIP001  if(!pTOX)
//STRIP001      return FALSE;
//STRIP001  pTOX->SetFromChapter(rDesc.IsFromChapter());
//STRIP001  pTOX->SetSequenceName(rDesc.GetSequenceName());
//STRIP001  pTOX->SetCaptionDisplay(rDesc.GetCaptionDisplay());
//STRIP001  pTOX->SetProtected(rDesc.IsReadonly());
//STRIP001
//STRIP001  for(USHORT nLevel = 0; nLevel < MAXLEVEL; nLevel++)
//STRIP001      pTOX->SetStyleNames(rDesc.GetStyleNames(nLevel), nLevel);
//STRIP001
//STRIP001  if(rDesc.GetTitle())
//STRIP001      pTOX->SetTitle(*rDesc.GetTitle());
//STRIP001  if(rDesc.GetForm())
//STRIP001      pTOX->SetTOXForm(*rDesc.GetForm());
//STRIP001     pTOX->SetLanguage(rDesc.GetLanguage());
//STRIP001     pTOX->SetSortAlgorithm(rDesc.GetSortAlgorithm());
//STRIP001
//STRIP001     if(!pCurTOX || (ppBase && !(*ppBase)) )
//STRIP001  {
//STRIP001      // wird ppBase uebergeben, dann wird das TOXBase hier nur erzeugt
//STRIP001      // und dann ueber den Dialog in ein Globaldokument eingefuegt
//STRIP001      if(ppBase)
//STRIP001          (*ppBase) = pTOX;
//STRIP001      else
//STRIP001      {
//STRIP001          pSh->InsertTableOf(*pTOX, pSet);
//STRIP001          delete pTOX;
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001      bRet = pSh->UpdateTableOf(*pTOX, pSet);
//STRIP001
//STRIP001  return bRet;
//STRIP001 }
/* -----------------20.10.99 14:11-------------------

 --------------------------------------------------*/
//STRIP001 void SwTOXDescription::SetSortKeys(SwTOXSortKey eKey1,
//STRIP001                      SwTOXSortKey eKey2,
//STRIP001                          SwTOXSortKey eKey3)
//STRIP001 {
//STRIP001  SwTOXSortKey aArr[3];
//STRIP001  USHORT nPos = 0;
//STRIP001  if(AUTH_FIELD_END > eKey1.eField)
//STRIP001      aArr[nPos++] = eKey1;
//STRIP001  if(AUTH_FIELD_END > eKey2.eField)
//STRIP001      aArr[nPos++] = eKey2;
//STRIP001  if(AUTH_FIELD_END > eKey3.eField)
//STRIP001      aArr[nPos++] = eKey3;
//STRIP001
//STRIP001  eSortKey1 = aArr[0];
//STRIP001  eSortKey2 = aArr[1];
//STRIP001  eSortKey3 = aArr[2];
//STRIP001 }

/* -----------------10.09.99 10:02-------------------

 --------------------------------------------------*/
//STRIP001 void SwTOXDescription::ApplyTo(SwTOXBase& rTOXBase)
//STRIP001 {
//STRIP001  for(USHORT i = 0; i < MAXLEVEL; i++)
//STRIP001      rTOXBase.SetStyleNames(GetStyleNames(i), i);
//STRIP001  rTOXBase.SetTitle(GetTitle() ? *GetTitle() : aEmptyStr);
//STRIP001  rTOXBase.SetCreate(GetContentOptions());
//STRIP001
//STRIP001  if(GetTOXType() == TOX_INDEX)
//STRIP001      rTOXBase.SetOptions(GetIndexOptions());
//STRIP001  if(GetTOXType() != TOX_INDEX)
//STRIP001      rTOXBase.SetLevel(GetLevel());
//STRIP001  rTOXBase.SetFromObjectNames(IsCreateFromObjectNames());
//STRIP001  rTOXBase.SetSequenceName(GetSequenceName());
//STRIP001  rTOXBase.SetCaptionDisplay(GetCaptionDisplay());
//STRIP001  rTOXBase.SetFromChapter(IsFromChapter());
//STRIP001  rTOXBase.SetProtected(IsReadonly());
//STRIP001  rTOXBase.SetOLEOptions(GetOLEOptions());
//STRIP001  rTOXBase.SetLevelFromChapter(IsLevelFromChapter());
//STRIP001     rTOXBase.SetLanguage(eLanguage);
//STRIP001     rTOXBase.SetSortAlgorithm(sSortAlgorithm);
//STRIP001
//STRIP001 }



