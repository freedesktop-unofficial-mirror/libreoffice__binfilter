/*************************************************************************
 *
 *  $RCSfile: sw_authfld.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:49:34 $
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


//STRIP001 #pragma hdrstop
//STRIP001
//STRIP001 #define _SVSTDARR_STRINGSDTOR
//STRIP001 #define _SVSTDARR_USHORTS
//STRIP001 #define _SVSTDARR_LONGS
//STRIP001 #define _SVSTDARR_ULONGS
//STRIP001
//STRIP001 #ifndef _HINTIDS_HXX
//STRIP001 #include <hintids.hxx>
//STRIP001 #endif
//STRIP001
//STRIP001 #include <svtools/svstdarr.hxx>
//STRIP001 #ifndef _UNO_LINGU_HXX
//STRIP001 #include <bf_svx/unolingu.hxx>
//STRIP001 #endif
//STRIP001 #ifndef _SVX_LANGITEM_HXX
//STRIP001 #include <bf_svx/langitem.hxx>
//STRIP001 #endif
//STRIP001 #ifndef _COM_SUN_STAR_BEANS_PROPERTYVALUES_HPP_
//STRIP001 #include <com/sun/star/beans/PropertyValues.hpp>
//STRIP001 #endif
//STRIP001 #ifndef _COM_SUN_STAR_LANG_LOCALE_HPP_
//STRIP001 #include <com/sun/star/lang/Locale.hpp>
//STRIP001 #endif
//STRIP001
//STRIP001 #ifndef _SWTYPES_HXX
//STRIP001 #include <swtypes.hxx>
//STRIP001 #endif
//STRIP001 #ifndef _AUTHFLD_HXX
//STRIP001 #include <authfld.hxx>
//STRIP001 #endif
//STRIP001 #ifndef _EXPFLD_HXX
//STRIP001 #include <expfld.hxx>
//STRIP001 #endif
//STRIP001 #ifndef _PAM_HXX
//STRIP001 #include <pam.hxx>
//STRIP001 #endif
//STRIP001 #ifndef _CNTFRM_HXX
//STRIP001 #include <cntfrm.hxx>
//STRIP001 #endif
//STRIP001 #ifndef _TOX_HXX
//STRIP001 #include <tox.hxx>
//STRIP001 #endif
//STRIP001 #ifndef _TXMSRT_HXX
//STRIP001 #include <txmsrt.hxx>
//STRIP001 #endif
//STRIP001 #ifndef _DOCTXM_HXX
//STRIP001 #include <doctxm.hxx>
//STRIP001 #endif
//STRIP001 #ifndef _FMTFLD_HXX
//STRIP001 #include <fmtfld.hxx>
//STRIP001 #endif
//STRIP001 #ifndef _TXTFLD_HXX
//STRIP001 #include <txtfld.hxx>
//STRIP001 #endif
//STRIP001 #ifndef _NDTXT_HXX
//STRIP001 #include <ndtxt.hxx>
//STRIP001 #endif
//STRIP001 #ifndef _DOC_HXX
//STRIP001 #include <doc.hxx>
//STRIP001 #endif
//STRIP001 #ifndef _UNOFLDMID_H
//STRIP001 #include <unofldmid.h>
//STRIP001 #endif
//STRIP001 #ifndef _UNOPRNMS_HXX
//STRIP001 #include <unoprnms.hxx>
//STRIP001 #endif
//STRIP001 namespace binfilter {
//STRIP001
//STRIP001 using namespace ::com::sun::star::uno;
//STRIP001 using namespace ::com::sun::star::beans;
//STRIP001 using namespace ::com::sun::star::lang;
//STRIP001 using namespace ::rtl;

//STRIP001 #define C2U(cChar) ::rtl::OUString::createFromAscii(cChar)

//STRIP001 typedef SwAuthEntry* SwAuthEntryPtr;
//STRIP001 SV_DECL_PTRARR_DEL( SwAuthDataArr, SwAuthEntryPtr, 5, 5 )
//STRIP001 SV_IMPL_PTRARR( SwAuthDataArr, SwAuthEntryPtr )


//STRIP001 typedef SwTOXSortKey* TOXSortKeyPtr;
//STRIP001 SV_DECL_PTRARR_DEL( SortKeyArr, TOXSortKeyPtr, 5, 5 )
//STRIP001 SV_IMPL_PTRARR( SortKeyArr, TOXSortKeyPtr )


/* -----------------16.09.99 11:53-------------------

 --------------------------------------------------*/
//STRIP001 SwAuthEntry::SwAuthEntry(const SwAuthEntry& rCopy)
//STRIP001  : nRefCount(0)
//STRIP001 {
//STRIP001  for(USHORT i = 0; i < AUTH_FIELD_END; i++)
//STRIP001      aAuthFields[i] = rCopy.aAuthFields[i];
//STRIP001 }
// --------------------------------------------------------
//STRIP001 BOOL     SwAuthEntry::operator==(const SwAuthEntry& rComp)
//STRIP001 {
//STRIP001  for(USHORT i = 0; i < AUTH_FIELD_END; i++)
//STRIP001      if(aAuthFields[i] != rComp.aAuthFields[i])
//STRIP001          return FALSE;
//STRIP001  return TRUE;
//STRIP001 }
// --------------------------------------------------------
//STRIP001 BOOL SwAuthEntry::GetFirstAuthorField(USHORT& nPos, String& rToFill)const
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001      for(USHORT i = 0; i < AUTH_FIELD_END; i++)
//STRIP001          if(aAuthFields[i].Len())
//STRIP001          {
//STRIP001              rToFill = aAuthFields[i];
//STRIP001              nPos = i;
//STRIP001              bRet = TRUE;
//STRIP001              break;
//STRIP001          }
//STRIP001  return bRet;
//STRIP001 }
// --------------------------------------------------------
//STRIP001 BOOL SwAuthEntry::GetNextAuthorField(USHORT& nPos, String& rToFill)const
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001  if(AUTH_FIELD_END > ++nPos)
//STRIP001  {
//STRIP001      for(USHORT i = nPos; i < AUTH_FIELD_END; i++)
//STRIP001          if(aAuthFields[i].Len())
//STRIP001          {
//STRIP001              rToFill = aAuthFields[i];
//STRIP001              nPos = i;
//STRIP001              bRet = TRUE;
//STRIP001              break;
//STRIP001          }
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

// --------------------------------------------------------

/* -----------------14.09.99 16:15-------------------

 --------------------------------------------------*/
//STRIP001 SwAuthorityFieldType::SwAuthorityFieldType(SwDoc* pDoc)
//STRIP001  : SwFieldType( RES_AUTHORITY ),
//STRIP001  m_pDoc(pDoc),
//STRIP001  m_pDataArr(new SwAuthDataArr ),
//STRIP001  m_pSequArr(new SvLongs(5, 5)),
//STRIP001  m_pSortKeyArr(new SortKeyArr(3, 3)),
//STRIP001  m_bSortByDocument(TRUE),
//STRIP001  m_bIsSequence(FALSE),
//STRIP001  m_cPrefix('['),
//STRIP001     m_cSuffix(']'),
//STRIP001     m_eLanguage((LanguageType)::GetAppLanguage())
//STRIP001 {
//STRIP001 }

//STRIP001 SwAuthorityFieldType::SwAuthorityFieldType( const SwAuthorityFieldType& rFType)
//STRIP001  : SwFieldType( RES_AUTHORITY ),
//STRIP001  m_pDataArr(new SwAuthDataArr ),
//STRIP001  m_pSequArr(new SvLongs(5, 5)),
//STRIP001  m_pSortKeyArr(new SortKeyArr(3, 3)),
//STRIP001  m_bSortByDocument(rFType.m_bSortByDocument),
//STRIP001  m_bIsSequence(rFType.m_bIsSequence),
//STRIP001  m_cPrefix(rFType.m_cPrefix),
//STRIP001     m_cSuffix(rFType.m_cSuffix),
//STRIP001     m_eLanguage(rFType.m_eLanguage),
//STRIP001     m_sSortAlgorithm(rFType.m_sSortAlgorithm)
//STRIP001 {
//STRIP001  for(USHORT i = 0; i < rFType.m_pSortKeyArr->Count(); i++)
//STRIP001      m_pSortKeyArr->Insert((*rFType.m_pSortKeyArr)[i], i);
//STRIP001 }

/* -----------------17.09.99 13:52-------------------

 --------------------------------------------------*/
//STRIP001 SwAuthorityFieldType::~SwAuthorityFieldType()
//STRIP001 {
//STRIP001 //   DBG_ASSERT(!m_pDataArr->Count(), "Array is not empty")
//STRIP001  m_pSortKeyArr->DeleteAndDestroy(0, m_pSortKeyArr->Count());
//STRIP001  delete m_pSortKeyArr;
//STRIP001  delete m_pSequArr;
//STRIP001  delete m_pDataArr;
//STRIP001 }
/*-- 14.09.99 16:22:09---------------------------------------------------

  -----------------------------------------------------------------------*/
//STRIP001 SwFieldType*     SwAuthorityFieldType::Copy()  const
//STRIP001 {
//STRIP001  return new SwAuthorityFieldType(m_pDoc);
//STRIP001 }
/* -----------------17.09.99 13:43-------------------

 --------------------------------------------------*/
//STRIP001 void SwAuthorityFieldType::RemoveField(long nHandle)
//STRIP001 {
//STRIP001 #ifdef DBG_UTIL
//STRIP001  BOOL bRemoved = FALSE;
//STRIP001 #endif
//STRIP001  for(USHORT j = 0; j < m_pDataArr->Count(); j++)
//STRIP001  {
//STRIP001      SwAuthEntry* pTemp = m_pDataArr->GetObject(j);
//STRIP001      long nRet = (long)(void*)pTemp;
//STRIP001      if(nRet == nHandle)
//STRIP001      {
//STRIP001 #ifdef DBG_UTIL
//STRIP001          bRemoved = TRUE;
//STRIP001 #endif
//STRIP001          pTemp->RemoveRef();
//STRIP001          if(!pTemp->GetRefCount())
//STRIP001          {
//STRIP001              m_pDataArr->DeleteAndDestroy(j, 1);
//STRIP001              //re-generate positions of the fields
//STRIP001              DelSequenceArray();
//STRIP001          }
//STRIP001          break;
//STRIP001      }
//STRIP001  }
//STRIP001 #ifdef DBG_UTIL
//STRIP001  DBG_ASSERT(bRemoved, "Field unknown" )
//STRIP001 #endif
//STRIP001 }
/* -----------------17.09.99 13:43-------------------

 --------------------------------------------------*/
//STRIP001 long SwAuthorityFieldType::AddField(const String& rFieldContents)
//STRIP001 {
//STRIP001  long nRet = 0;
//STRIP001  SwAuthEntry* pEntry = new SwAuthEntry;
//STRIP001  for( USHORT i = 0; i < AUTH_FIELD_END; ++i )
//STRIP001      pEntry->SetAuthorField( (ToxAuthorityField)i,
//STRIP001                      rFieldContents.GetToken( i, TOX_STYLE_DELIMITER ));
//STRIP001
//STRIP001  for(USHORT j = 0; j < m_pDataArr->Count() && pEntry; j++)
//STRIP001  {
//STRIP001      SwAuthEntry* pTemp = m_pDataArr->GetObject(j);
//STRIP001      if(*pTemp == *pEntry)
//STRIP001      {
//STRIP001          DELETEZ(pEntry);
//STRIP001          nRet = (long)(void*)pTemp;
//STRIP001          pTemp->AddRef();
//STRIP001      }
//STRIP001  }
//STRIP001  //if it is a new Entry - insert
//STRIP001  if(pEntry)
//STRIP001  {
//STRIP001      nRet = (long)(void*)pEntry;
//STRIP001      pEntry->AddRef();
//STRIP001      m_pDataArr->Insert(pEntry, m_pDataArr->Count());
//STRIP001      //re-generate positions of the fields
//STRIP001      DelSequenceArray();
//STRIP001  }
//STRIP001  return nRet;
//STRIP001 }
/* -----------------17.09.99 14:18-------------------

 --------------------------------------------------*/
//STRIP001 BOOL SwAuthorityFieldType::AddField(long nHandle)
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001  for( USHORT j = 0; j < m_pDataArr->Count(); j++ )
//STRIP001  {
//STRIP001      SwAuthEntry* pTemp = m_pDataArr->GetObject(j);
//STRIP001      long nTmp = (long)(void*)pTemp;
//STRIP001      if( nTmp == nHandle )
//STRIP001      {
//STRIP001          bRet = TRUE;
//STRIP001          pTemp->AddRef();
//STRIP001          //re-generate positions of the fields
//STRIP001          DelSequenceArray();
//STRIP001          break;
//STRIP001      }
//STRIP001  }
//STRIP001  DBG_ASSERT(bRet, "::AddField(long) failed");
//STRIP001  return bRet;
//STRIP001 }
/* -----------------17.09.99 14:52-------------------

 --------------------------------------------------*/
//STRIP001 const SwAuthEntry*   SwAuthorityFieldType::GetEntryByHandle(long nHandle) const
//STRIP001 {
//STRIP001  const SwAuthEntry* pRet = 0;
//STRIP001  for(USHORT j = 0; j < m_pDataArr->Count(); j++)
//STRIP001  {
//STRIP001      const SwAuthEntry* pTemp = m_pDataArr->GetObject(j);
//STRIP001      long nTmp = (long)(void*)pTemp;
//STRIP001      if( nTmp == nHandle )
//STRIP001      {
//STRIP001          pRet = pTemp;
//STRIP001          break;
//STRIP001      }
//STRIP001  }
//STRIP001  ASSERT( pRet, "invalid Handle" );
//STRIP001  return pRet;
//STRIP001 }
/* -----------------21.09.99 13:34-------------------

 --------------------------------------------------*/
//STRIP001 void SwAuthorityFieldType::GetAllEntryIdentifiers(
//STRIP001              SvStringsDtor& rToFill )const
//STRIP001 {
//STRIP001  for(USHORT j = 0; j < m_pDataArr->Count(); j++)
//STRIP001  {
//STRIP001      SwAuthEntry* pTemp = m_pDataArr->GetObject(j);
//STRIP001      rToFill.Insert( new String( pTemp->GetAuthorField(
//STRIP001                  AUTH_FIELD_IDENTIFIER )), rToFill.Count() );
//STRIP001  }
//STRIP001 }
/* -----------------21.09.99 13:34-------------------

 --------------------------------------------------*/
//STRIP001 const SwAuthEntry*   SwAuthorityFieldType::GetEntryByIdentifier(
//STRIP001                              const String& rIdentifier)const
//STRIP001 {
//STRIP001  const SwAuthEntry* pRet = 0;
//STRIP001  for( USHORT j = 0; j < m_pDataArr->Count(); ++j )
//STRIP001  {
//STRIP001      const SwAuthEntry* pTemp = m_pDataArr->GetObject(j);
//STRIP001      if( rIdentifier == pTemp->GetAuthorField( AUTH_FIELD_IDENTIFIER ))
//STRIP001      {
//STRIP001          pRet = pTemp;
//STRIP001          break;
//STRIP001      }
//STRIP001  }
//STRIP001  return pRet;
//STRIP001 }
/* -----------------------------21.12.99 13:20--------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 void SwAuthorityFieldType::ChangeEntryContent(const SwAuthEntry* pNewEntry)
//STRIP001 {
//STRIP001  for( USHORT j = 0; j < m_pDataArr->Count(); ++j )
//STRIP001  {
//STRIP001      SwAuthEntry* pTemp = m_pDataArr->GetObject(j);
//STRIP001      if(pTemp->GetAuthorField(AUTH_FIELD_IDENTIFIER) ==
//STRIP001                  pNewEntry->GetAuthorField(AUTH_FIELD_IDENTIFIER))
//STRIP001      {
//STRIP001          for(USHORT i = 0; i < AUTH_FIELD_END; i++)
//STRIP001              pTemp->SetAuthorField((ToxAuthorityField) i,
//STRIP001                  pNewEntry->GetAuthorField((ToxAuthorityField)i));
//STRIP001          break;
//STRIP001      }
//STRIP001  }
//STRIP001 }
/*-- 11.10.99 08:49:22---------------------------------------------------
    Description:    appends a new entry (if new) and returns the array position

  -----------------------------------------------------------------------*/
//STRIP001 USHORT   SwAuthorityFieldType::AppendField( const SwAuthEntry& rInsert )
//STRIP001 {
//STRIP001  USHORT nRet = 0;
//STRIP001  for( nRet = 0; nRet < m_pDataArr->Count(); ++nRet )
//STRIP001  {
//STRIP001      SwAuthEntry* pTemp = m_pDataArr->GetObject( nRet );
//STRIP001      if( *pTemp == rInsert )
//STRIP001      {
//STRIP001          break;
//STRIP001          //ref count unchanged
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  //if it is a new Entry - insert
//STRIP001  if( nRet == m_pDataArr->Count() )
//STRIP001      m_pDataArr->Insert( new SwAuthEntry( rInsert ), nRet );
//STRIP001
//STRIP001  return nRet;
//STRIP001 }

/*-- 11.10.99 08:49:23---------------------------------------------------

  -----------------------------------------------------------------------*/
//STRIP001 void SwAuthorityFieldType::MergeFieldType( const SwAuthorityFieldType& rNew,
//STRIP001                                          SvUShorts& rMap )
//STRIP001 {
//STRIP001  DBG_ASSERT( !rMap.Count(), "array not empty!")
//STRIP001  for( USHORT i = 0; i < rNew.m_pDataArr->Count(); ++i )
//STRIP001  {
//STRIP001      USHORT  nNewPos = AppendField(*rNew.m_pDataArr->GetObject(i));
//STRIP001      rMap.Insert(nNewPos, i);
//STRIP001  }
//STRIP001 }

/*-- 11.10.99 08:49:23---------------------------------------------------
    Description:    After import is done some of the array members may have a

  -----------------------------------------------------------------------*/
//STRIP001 void SwAuthorityFieldType::RemoveUnusedFields()
//STRIP001 {
//STRIP001  for( USHORT j = m_pDataArr->Count(); j; )
//STRIP001  {
//STRIP001      SwAuthEntry* pTemp = m_pDataArr->GetObject( --j );
//STRIP001      if( !pTemp->GetRefCount() )
//STRIP001      {
//STRIP001          m_pDataArr->Remove( j );
//STRIP001          delete pTemp;
//STRIP001      }
//STRIP001  }
//STRIP001  DelSequenceArray();
//STRIP001 }

/*-- 11.10.99 08:49:24---------------------------------------------------

  -----------------------------------------------------------------------*/
//STRIP001 long SwAuthorityFieldType::GetHandle(USHORT nPos)
//STRIP001 {
//STRIP001  long nRet = 0;
//STRIP001  if( nPos < m_pDataArr->Count() )
//STRIP001  {
//STRIP001      SwAuthEntry* pTemp = m_pDataArr->GetObject(nPos);
//STRIP001      nRet = (long)(void*)pTemp;
//STRIP001  }
//STRIP001  return nRet;
//STRIP001 }
/* -----------------20.10.99 13:38-------------------

 --------------------------------------------------*/
//STRIP001 USHORT   SwAuthorityFieldType::GetPosition(long nHandle)
//STRIP001 {
//STRIP001  USHORT j = 0;
//STRIP001  for( ; j < m_pDataArr->Count(); ++j )
//STRIP001  {
//STRIP001      const SwAuthEntry* pTemp = m_pDataArr->GetObject(j);
//STRIP001      long nTmp = (long)(void*)pTemp;
//STRIP001      if( nTmp == nHandle )
//STRIP001          break;
//STRIP001  }
//STRIP001  if( j == m_pDataArr->Count() )
//STRIP001      j = USHRT_MAX;
//STRIP001
//STRIP001  ASSERT( USHRT_MAX != j, "handle not found" );
//STRIP001  return j;
//STRIP001 }

/*-- 11.10.99 08:51:03---------------------------------------------------

  -----------------------------------------------------------------------*/
//STRIP001 USHORT   SwAuthorityFieldType::GetEntryCount() const
//STRIP001 {
//STRIP001  return m_pDataArr->Count();
//STRIP001 }
/*-- 11.10.99 08:51:03---------------------------------------------------

  -----------------------------------------------------------------------*/
//STRIP001 const SwAuthEntry*   SwAuthorityFieldType::GetEntryByPosition(USHORT nPos) const
//STRIP001 {
//STRIP001  if(nPos < m_pDataArr->Count())
//STRIP001      return m_pDataArr->GetObject(nPos);
//STRIP001  DBG_ERROR("wrong index")
//STRIP001  return 0;
//STRIP001 }
/* -----------------19.10.99 13:46-------------------

 --------------------------------------------------*/
//STRIP001 USHORT   SwAuthorityFieldType::GetSequencePos(long nHandle)
//STRIP001 {
//STRIP001  //find the field in a sorted array of handles,
//STRIP001 #ifdef DBG_UTIL
//STRIP001  sal_Bool bCurrentFieldWithoutTextNode = sal_False;
//STRIP001 #endif
//STRIP001  if(m_pSequArr->Count() && m_pSequArr->Count() != m_pDataArr->Count())
//STRIP001      DelSequenceArray();
//STRIP001  if(!m_pSequArr->Count())
//STRIP001  {
//STRIP001      SwTOXSortTabBases aSortArr;
//STRIP001      SwClientIter aIter( *this );
//STRIP001
//STRIP001         SwTOXInternational aIntl(m_eLanguage, 0, m_sSortAlgorithm);
//STRIP001
//STRIP001      for( SwFmtFld* pFmtFld = (SwFmtFld*)aIter.First( TYPE(SwFmtFld) );
//STRIP001                              pFmtFld; pFmtFld = (SwFmtFld*)aIter.Next() )
//STRIP001      {
//STRIP001          SwAuthorityField* pAFld = (SwAuthorityField*)pFmtFld->GetFld();
//STRIP001          const SwTxtFld* pTxtFld = pFmtFld->GetTxtFld();
//STRIP001          if(!pTxtFld || !pTxtFld->GetpTxtNode())
//STRIP001          {
//STRIP001 #ifdef DBG_UTIL
//STRIP001              if(nHandle == pAFld->GetHandle())
//STRIP001                  bCurrentFieldWithoutTextNode = sal_True;
//STRIP001 #endif
//STRIP001              continue;
//STRIP001          }
//STRIP001             const SwTxtNode& rFldTxtNode = pTxtFld->GetTxtNode();
//STRIP001             SwPosition aFldPos(rFldTxtNode);
//STRIP001             SwDoc& rDoc = *(SwDoc*)rFldTxtNode.GetDoc();
//STRIP001             SwCntntFrm *pFrm = rFldTxtNode.GetFrm();
//STRIP001             const SwTxtNode* pTxtNode = 0;
//STRIP001             if(pFrm && !pFrm->IsInDocBody())
//STRIP001                 pTxtNode = GetBodyTxtNode( rDoc, aFldPos, *pFrm );
//STRIP001             //if no text node could be found or the field is in the document
//STRIP001             //body the directly available text node will be used
//STRIP001             if(!pTxtNode)
//STRIP001                 pTxtNode = &rFldTxtNode;
//STRIP001             ULONG nPos = pTxtNode->GetIndex();
//STRIP001             if( pTxtNode->GetTxt().Len() && pTxtNode->GetFrm() &&
//STRIP001                 pTxtNode->GetNodes().IsDocNodes() )
//STRIP001          {
//STRIP001                 SwTOXAuthority* pNew = new SwTOXAuthority( *pTxtNode,
//STRIP001                                                          *pFmtFld, aIntl );
//STRIP001
//STRIP001              for(short i = 0; i < aSortArr.Count(); ++i)
//STRIP001              {
//STRIP001                  SwTOXSortTabBase* pOld = aSortArr[i];
//STRIP001                  if(*pOld == *pNew)
//STRIP001                  {
//STRIP001                      //only the first occurence in the document
//STRIP001                      //has to be in the array
//STRIP001                      if(*pOld < *pNew)
//STRIP001                          DELETEZ(pNew);
//STRIP001                      else // remove the old content
//STRIP001                          aSortArr.DeleteAndDestroy( i, 1 );
//STRIP001                      break;
//STRIP001                  }
//STRIP001              }
//STRIP001              //if it still exists - insert at the correct position
//STRIP001              if(pNew)
//STRIP001              {
//STRIP001                  for(short j = 0; j < aSortArr.Count(); ++j)
//STRIP001                  {
//STRIP001                      SwTOXSortTabBase* pOld = aSortArr[j];
//STRIP001                      if(*pNew < *pOld)
//STRIP001                          break;
//STRIP001                  }
//STRIP001                  aSortArr.Insert(pNew, j );
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      for(USHORT i = 0; i < aSortArr.Count(); i++)
//STRIP001      {
//STRIP001          const SwTOXSortTabBase& rBase = *aSortArr[i];
//STRIP001          SwFmtFld& rFmtFld = ((SwTOXAuthority&)rBase).GetFldFmt();
//STRIP001          SwAuthorityField* pAFld = (SwAuthorityField*)rFmtFld.GetFld();
//STRIP001          m_pSequArr->Insert(pAFld->GetHandle(), i);
//STRIP001      }
//STRIP001      aSortArr.DeleteAndDestroy(0, aSortArr.Count());
//STRIP001  }
//STRIP001  //find nHandle
//STRIP001  USHORT nRet = 0;
//STRIP001  for(USHORT i = 0; i < m_pSequArr->Count(); i++)
//STRIP001  {
//STRIP001      if((*m_pSequArr)[i] == nHandle)
//STRIP001      {
//STRIP001          nRet = i + 1;
//STRIP001          break;
//STRIP001      }
//STRIP001  }
//STRIP001  ASSERT(bCurrentFieldWithoutTextNode || nRet, "Handle not found")
//STRIP001  return nRet;
//STRIP001 }
/* -----------------------------15.11.00 17:33--------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 BOOL    SwAuthorityFieldType::QueryValue( Any& rVal, BYTE nMId ) const
//STRIP001 {
//STRIP001     nMId &= ~CONVERT_TWIPS;
//STRIP001  switch( nMId )
//STRIP001  {
//STRIP001  case FIELD_PROP_PAR1:
//STRIP001  case FIELD_PROP_PAR2:
//STRIP001      {
//STRIP001          OUString sVal;
//STRIP001          sal_Unicode uRet = FIELD_PROP_PAR1 == nMId ? m_cPrefix : m_cSuffix;
//STRIP001          if(uRet)
//STRIP001              sVal = OUString(uRet);
//STRIP001          rVal <<= sVal;
//STRIP001      }
//STRIP001      break;
//STRIP001  case FIELD_PROP_PAR3:
//STRIP001         rVal <<= OUString(GetSortAlgorithm());
//STRIP001      break;
//STRIP001
//STRIP001  case FIELD_PROP_BOOL1:
//STRIP001  case FIELD_PROP_BOOL2:
//STRIP001      {
//STRIP001          sal_Bool bVal = FIELD_PROP_BOOL1 == nMId ? m_bIsSequence: m_bSortByDocument;
//STRIP001          rVal.setValue(&bVal, ::getBooleanCppuType());
//STRIP001      }
//STRIP001      break;
//STRIP001
//STRIP001  case FIELD_PROP_LOCALE:
//STRIP001         rVal <<= SvxCreateLocale(GetLanguage());
//STRIP001      break;
//STRIP001
//STRIP001  case FIELD_PROP_PROP_SEQ:
//STRIP001      {
//STRIP001          Sequence<PropertyValues> aRet(m_pSortKeyArr->Count());
//STRIP001          PropertyValues* pValues = aRet.getArray();
//STRIP001          OUString sProp1( C2U(SW_PROP_NAME_STR(UNO_NAME_SORT_KEY)) ),
//STRIP001                   sProp2( C2U(SW_PROP_NAME_STR(UNO_NAME_IS_SORT_ASCENDING)));
//STRIP001          for(sal_uInt16 i = 0; i < m_pSortKeyArr->Count(); i++)
//STRIP001          {
//STRIP001              const SwTOXSortKey* pKey = (*m_pSortKeyArr)[i];
//STRIP001              pValues[i].realloc(2);
//STRIP001              PropertyValue* pValue = pValues[i].getArray();
//STRIP001              pValue[0].Name = sProp1;
//STRIP001              pValue[0].Value <<= sal_Int16(pKey->eField);
//STRIP001              pValue[1].Name = sProp2;
//STRIP001              pValue[1].Value.setValue(&pKey->bSortAscending, ::getBooleanCppuType());
//STRIP001          }
//STRIP001          rVal <<= aRet;
//STRIP001      }
//STRIP001      break;
//STRIP001  default:
//STRIP001      DBG_ERROR("illegal property");
//STRIP001  }
//STRIP001  return TRUE;
//STRIP001 }
/* -----------------------------15.11.00 17:33--------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 BOOL SwAuthorityFieldType::PutValue( const Any& rAny, BYTE nMId )
//STRIP001 {
//STRIP001     nMId &= ~CONVERT_TWIPS;
//STRIP001  sal_Bool bRet = TRUE;
//STRIP001  String sTmp;
//STRIP001  switch( nMId )
//STRIP001  {
//STRIP001  case FIELD_PROP_PAR1:
//STRIP001  case FIELD_PROP_PAR2:
//STRIP001     {
//STRIP001         ::GetString( rAny, sTmp );
//STRIP001         sal_Unicode uSet = sTmp.GetChar(0);
//STRIP001         if( FIELD_PROP_PAR1 == nMId )
//STRIP001             m_cPrefix = uSet;
//STRIP001         else
//STRIP001             m_cSuffix = uSet;
//STRIP001     }
//STRIP001     break;
//STRIP001  case FIELD_PROP_PAR3:
//STRIP001      SetSortAlgorithm( ::GetString( rAny, sTmp ));
//STRIP001      break;
//STRIP001
//STRIP001  case FIELD_PROP_BOOL1:
//STRIP001      m_bIsSequence = *(sal_Bool*)rAny.getValue();
//STRIP001      break;
//STRIP001  case FIELD_PROP_BOOL2:
//STRIP001      m_bSortByDocument = *(sal_Bool*)rAny.getValue();
//STRIP001      break;
//STRIP001
//STRIP001  case FIELD_PROP_LOCALE:
//STRIP001      {
//STRIP001          Locale aLocale;
//STRIP001          if( 0 != (bRet = rAny >>= aLocale ))
//STRIP001              SetLanguage( SvxLocaleToLanguage( aLocale ));
//STRIP001      }
//STRIP001      break;
//STRIP001
//STRIP001  case FIELD_PROP_PROP_SEQ:
//STRIP001      {
//STRIP001          Sequence<PropertyValues> aSeq;
//STRIP001          if( 0 != (bRet = rAny >>= aSeq) )
//STRIP001          {
//STRIP001              m_pSortKeyArr->DeleteAndDestroy(0, m_pSortKeyArr->Count());
//STRIP001              const PropertyValues* pValues = aSeq.getConstArray();
//STRIP001              for(sal_Int32 i = 0; i < aSeq.getLength() && i < USHRT_MAX / 4; i++)
//STRIP001              {
//STRIP001                  const PropertyValue* pValue = pValues[i].getConstArray();
//STRIP001                  SwTOXSortKey* pSortKey = new SwTOXSortKey;
//STRIP001                  for(sal_Int32 j = 0; j < pValues[i].getLength(); j++)
//STRIP001                  {
//STRIP001                      if(pValue[j].Name.equalsAsciiL(SW_PROP_NAME(UNO_NAME_SORT_KEY)))
//STRIP001                      {
//STRIP001                          sal_Int16 nVal = -1; pValue[j].Value >>= nVal;
//STRIP001                          if(nVal >= 0 && nVal < AUTH_FIELD_END)
//STRIP001                              pSortKey->eField = (ToxAuthorityField) nVal;
//STRIP001                          else
//STRIP001                              bRet = FALSE;
//STRIP001                      }
//STRIP001                      else if(pValue[j].Name.equalsAsciiL(SW_PROP_NAME(UNO_NAME_IS_SORT_ASCENDING)))
//STRIP001                      {
//STRIP001                          pSortKey->bSortAscending = *(sal_Bool*)pValue[j].Value.getValue();
//STRIP001                      }
//STRIP001                  }
//STRIP001                  m_pSortKeyArr->Insert(pSortKey, m_pSortKeyArr->Count());
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      break;
//STRIP001  default:
//STRIP001      DBG_ERROR("illegal property");
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }
/* -----------------19.10.99 13:25-------------------

 --------------------------------------------------*/
//STRIP001 void SwAuthorityFieldType::Modify( SfxPoolItem *pOld, SfxPoolItem *pNew )
//STRIP001 {
//STRIP001  //re-generate positions of the fields
//STRIP001  DelSequenceArray();
//STRIP001  SwModify::Modify( pOld, pNew );
//STRIP001 }
/* -----------------20.10.99 13:38-------------------

 --------------------------------------------------*/
//STRIP001 USHORT SwAuthorityFieldType::GetSortKeyCount() const
//STRIP001 {
//STRIP001  return m_pSortKeyArr->Count();
//STRIP001 }
/* -----------------20.10.99 13:38-------------------

 --------------------------------------------------*/
//STRIP001 const SwTOXSortKey*  SwAuthorityFieldType::GetSortKey(USHORT nIdx) const
//STRIP001 {
//STRIP001  SwTOXSortKey* pRet = 0;
//STRIP001  if(m_pSortKeyArr->Count() > nIdx)
//STRIP001      pRet = (*m_pSortKeyArr)[nIdx];
//STRIP001  DBG_ASSERT(pRet, "Sort key not found")
//STRIP001  return pRet;
//STRIP001 }
/* -----------------20.10.99 13:38-------------------

 --------------------------------------------------*/
//STRIP001 void SwAuthorityFieldType::SetSortKeys(USHORT nKeyCount, SwTOXSortKey aKeys[])
//STRIP001 {
//STRIP001  m_pSortKeyArr->DeleteAndDestroy(0, m_pSortKeyArr->Count());
//STRIP001  USHORT nArrIdx = 0;
//STRIP001  for(USHORT i = 0; i < nKeyCount; i++)
//STRIP001      if(aKeys[i].eField < AUTH_FIELD_END)
//STRIP001          m_pSortKeyArr->Insert(new SwTOXSortKey(aKeys[i]), nArrIdx++);
//STRIP001 }

/* -----------------14.09.99 16:15-------------------

 --------------------------------------------------*/
//STRIP001 SwAuthorityField::SwAuthorityField( SwAuthorityFieldType* pType,
//STRIP001                                  const String& rFieldContents )
//STRIP001  : SwField(pType)
//STRIP001 {
//STRIP001  nHandle = pType->AddField( rFieldContents );
//STRIP001 }
/* -----------------17.09.99 14:24-------------------

 --------------------------------------------------*/
//STRIP001 SwAuthorityField::SwAuthorityField( SwAuthorityFieldType* pType,
//STRIP001                                              long nSetHandle )
//STRIP001  : SwField( pType ),
//STRIP001  nHandle( nSetHandle )
//STRIP001 {
//STRIP001  pType->AddField( nHandle );
//STRIP001 }
/* -----------------15.09.99 15:00-------------------

 --------------------------------------------------*/
//STRIP001 SwAuthorityField::~SwAuthorityField()
//STRIP001 {
//STRIP001  ((SwAuthorityFieldType* )GetTyp())->RemoveField(nHandle);
//STRIP001 }
/*-- 14.09.99 16:20:59---------------------------------------------------

  -----------------------------------------------------------------------*/
//STRIP001 String   SwAuthorityField::Expand() const
//STRIP001 {
//STRIP001  SwAuthorityFieldType* pAuthType = (SwAuthorityFieldType*)GetTyp();
//STRIP001  String sRet;
//STRIP001  if(pAuthType->GetPrefix())
//STRIP001      sRet.Assign(pAuthType->GetPrefix());
//STRIP001
//STRIP001  if( pAuthType->IsSequence() )
//STRIP001  {
//STRIP001      sRet += String::CreateFromInt32( pAuthType->GetSequencePos( nHandle ));
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      const SwAuthEntry* pEntry = pAuthType->GetEntryByHandle(nHandle);
//STRIP001      //TODO: Expand to: identifier, number sequence, ...
//STRIP001      if(pEntry)
//STRIP001          sRet += pEntry->GetAuthorField(AUTH_FIELD_IDENTIFIER);
//STRIP001  }
//STRIP001  if(pAuthType->GetSuffix())
//STRIP001      sRet += pAuthType->GetSuffix();
//STRIP001  return sRet;
//STRIP001 }
/*-- 14.09.99 16:21:00---------------------------------------------------

  -----------------------------------------------------------------------*/
//STRIP001 SwField* SwAuthorityField::Copy() const
//STRIP001 {
//STRIP001  SwAuthorityFieldType* pAuthType = (SwAuthorityFieldType*)GetTyp();
//STRIP001  return new SwAuthorityField(pAuthType, nHandle);
//STRIP001 }
/* -----------------21.09.99 12:55-------------------

 --------------------------------------------------*/
//STRIP001 const String&    SwAuthorityField::GetFieldText(ToxAuthorityField eField) const
//STRIP001 {
//STRIP001  SwAuthorityFieldType* pAuthType = (SwAuthorityFieldType*)GetTyp();
//STRIP001  const SwAuthEntry* pEntry = pAuthType->GetEntryByHandle( nHandle );
//STRIP001  return pEntry->GetAuthorField( eField );
//STRIP001 }
/* -----------------21.09.99 14:57-------------------

 --------------------------------------------------*/
//STRIP001 void SwAuthorityField::SetPar1(const String& rStr)
//STRIP001 {
//STRIP001  SwAuthorityFieldType* pType = (SwAuthorityFieldType* )GetTyp();
//STRIP001  pType->RemoveField(nHandle);
//STRIP001  nHandle = pType->AddField(rStr);
//STRIP001 }
/* -----------------11.10.99 09:43-------------------

 --------------------------------------------------*/
//STRIP001 USHORT   SwAuthorityField::GetHandlePosition() const
//STRIP001 {
//STRIP001  SwAuthorityFieldType* pAuthType = (SwAuthorityFieldType*)GetTyp();
//STRIP001  DBG_ASSERT(pAuthType, "no field type")
//STRIP001  return pAuthType->GetPosition(nHandle);
//STRIP001 }
/* -----------------------------15.11.00 17:33--------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 const char* aFieldNames[] =
//STRIP001 {
//STRIP001  "Identifier",
//STRIP001  "BibiliographicType",
//STRIP001  "Address",
//STRIP001  "Annote",
//STRIP001  "Author",
//STRIP001  "Booktitle",
//STRIP001  "Chapter",
//STRIP001  "Edition",
//STRIP001  "Editor",
//STRIP001  "Howpublished",
//STRIP001  "Institution",
//STRIP001  "Journal",
//STRIP001  "Month",
//STRIP001  "Note",
//STRIP001  "Number",
//STRIP001  "Organizations",
//STRIP001  "Pages",
//STRIP001  "Publisher",
//STRIP001  "School",
//STRIP001  "Series",
//STRIP001  "Title",
//STRIP001  "Report_Type",
//STRIP001  "Volume",
//STRIP001  "Year",
//STRIP001  "URL",
//STRIP001  "Custom1",
//STRIP001  "Custom2",
//STRIP001  "Custom3",
//STRIP001  "Custom4",
//STRIP001  "Custom5",
//STRIP001  "ISBN"
//STRIP001 };
/* -----------------------------16.11.00 12:27--------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 BOOL    SwAuthorityField::QueryValue( Any& rAny, BYTE nMId ) const
//STRIP001 {
//STRIP001     nMId &= ~CONVERT_TWIPS;
//STRIP001  if(!GetTyp())
//STRIP001      return FALSE;
//STRIP001  const SwAuthEntry* pAuthEntry = ((SwAuthorityFieldType*)GetTyp())->GetEntryByHandle(nHandle);
//STRIP001  if(!pAuthEntry)
//STRIP001      return FALSE;
//STRIP001  Sequence <PropertyValue> aRet(AUTH_FIELD_END);
//STRIP001  PropertyValue* pValues = aRet.getArray();
//STRIP001  for(sal_Int16 i = 0; i < AUTH_FIELD_END; i++)
//STRIP001  {
//STRIP001      pValues[i].Name = C2U(aFieldNames[i]);
//STRIP001      const String& rField = pAuthEntry->GetAuthorField((ToxAuthorityField) i);
//STRIP001      if(i == AUTH_FIELD_AUTHORITY_TYPE)
//STRIP001          pValues[i].Value <<= sal_Int16(rField.ToInt32());
//STRIP001      else
//STRIP001          pValues[i].Value <<= OUString(rField);
//STRIP001  }
//STRIP001  rAny <<= aRet;
//STRIP001  return FALSE;
//STRIP001 }
/* -----------------------------15.11.00 17:33--------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 sal_Int16 lcl_Find(const OUString& rFieldName)
//STRIP001 {
//STRIP001  for(sal_Int16 i = 0; i < AUTH_FIELD_END; i++)
//STRIP001      if(!rFieldName.compareToAscii(aFieldNames[i]))
//STRIP001          return i;
//STRIP001  return -1;
//STRIP001 }
//----------------------------------------------------------------------------
//STRIP001 BOOL SwAuthorityField::PutValue( const Any& rAny, BYTE nMId )
//STRIP001 {
//STRIP001     nMId &= ~CONVERT_TWIPS;
//STRIP001  if(!GetTyp() || !((SwAuthorityFieldType*)GetTyp())->GetEntryByHandle(nHandle))
//STRIP001      return FALSE;
//STRIP001
//STRIP001  Sequence <PropertyValue> aParam;
//STRIP001  if(!(rAny >>= aParam))
//STRIP001      return FALSE;
//STRIP001
//STRIP001  String sToSet;
//STRIP001  sToSet.Fill(AUTH_FIELD_ISBN, TOX_STYLE_DELIMITER);
//STRIP001  const PropertyValue* pParam = aParam.getConstArray();
//STRIP001  for(sal_Int32 i = 0; i < aParam.getLength(); i++)
//STRIP001  {
//STRIP001      sal_Int16 nFound = lcl_Find(pParam[i].Name);
//STRIP001      if(nFound >= 0)
//STRIP001      {
//STRIP001          OUString sContent;
//STRIP001          if(AUTH_FIELD_AUTHORITY_TYPE == nFound)
//STRIP001          {
//STRIP001              sal_Int16 nVal;
//STRIP001              pParam[i].Value >>= nVal;
//STRIP001              sContent = OUString::valueOf((sal_Int32)nVal);
//STRIP001          }
//STRIP001          else
//STRIP001              pParam[i].Value >>= sContent;
//STRIP001          sToSet.SetToken(nFound, TOX_STYLE_DELIMITER, sContent);
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  ((SwAuthorityFieldType*)GetTyp())->RemoveField(nHandle);
//STRIP001  nHandle = ((SwAuthorityFieldType*)GetTyp())->AddField(sToSet);
//STRIP001
//STRIP001  return FALSE;
//STRIP001 }
/* -----------------11.10.99 09:43-------------------

 --------------------------------------------------*/
//STRIP001 SwFieldType* SwAuthorityField::ChgTyp( SwFieldType* pFldTyp )
//STRIP001 {
//STRIP001  SwAuthorityFieldType* pSrcTyp = (SwAuthorityFieldType*)GetTyp(),
//STRIP001                      * pDstTyp = (SwAuthorityFieldType*)pFldTyp;
//STRIP001  if( pSrcTyp != pDstTyp )
//STRIP001  {
//STRIP001
//STRIP001      const SwAuthEntry* pEntry = pSrcTyp->GetEntryByHandle( nHandle );
//STRIP001      USHORT nHdlPos = pDstTyp->AppendField( *pEntry );
//STRIP001      pSrcTyp->RemoveField( nHandle );
//STRIP001      nHandle = pDstTyp->GetHandle( nHdlPos );
//STRIP001      pDstTyp->AddField( nHandle );
//STRIP001      SwField::ChgTyp( pFldTyp );
//STRIP001  }
//STRIP001  return pSrcTyp;
//STRIP001 }


//STRIP001 }
