/*************************************************************************
 *
 *  $RCSfile: authfld.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:58 $
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
#ifndef _AUTHFLD_HXX
#define _AUTHFLD_HXX

#ifndef _FLDBAS_HXX
#include <fldbas.hxx>
#endif
#ifndef _TOXE_HXX
#include <toxe.hxx>
#endif

#define _SVSTDARR_LONGS
#include <svtools/svstdarr.hxx>

class SwAuthDataArr;
/* -----------------21.09.99 13:32-------------------

 --------------------------------------------------*/
class SwAuthEntry
{
    String      aAuthFields[AUTH_FIELD_END];
    USHORT      nRefCount;
public:
    SwAuthEntry() : nRefCount(0){DBG_ASSERT(0, "STRIP"); }//STRIP001  SwAuthEntry() : nRefCount(0){}
//STRIP001  SwAuthEntry( const SwAuthEntry& rCopy );
//STRIP001  BOOL            operator==(const SwAuthEntry& rComp);
//STRIP001
//STRIP001  BOOL                    GetFirstAuthorField(USHORT& nPos, String& rToFill)const;
//STRIP001  BOOL                    GetNextAuthorField(USHORT& nPos, String& rToFill)const;
//STRIP001  inline const String&    GetAuthorField(ToxAuthorityField ePos)const;
//STRIP001  inline void             SetAuthorField(ToxAuthorityField ePos,
//STRIP001                                          const String& rField);
//STRIP001
//STRIP001  void            AddRef()                { ++nRefCount; }
//STRIP001  void            RemoveRef()             { --nRefCount; }
//STRIP001  USHORT          GetRefCount()           { return nRefCount; }
};
/* -----------------20.10.99 16:49-------------------

 --------------------------------------------------*/
struct SwTOXSortKey
{
    ToxAuthorityField   eField;
    BOOL                bSortAscending;
    SwTOXSortKey() :
        eField(AUTH_FIELD_END),
        bSortAscending(TRUE){}
};

/* -----------------14.09.99 16:15-------------------

 --------------------------------------------------*/
class SvUShorts;
class SwAuthorityField;
class SortKeyArr;
class SwAuthorityFieldType : public SwFieldType
{
//STRIP001  SwDoc*          m_pDoc;
//STRIP001  SwAuthDataArr*  m_pDataArr;
//STRIP001  SvLongs*        m_pSequArr;
//STRIP001  SortKeyArr*     m_pSortKeyArr;
//STRIP001  sal_Unicode     m_cPrefix;
//STRIP001  sal_Unicode     m_cSuffix;
//STRIP001  BOOL            m_bIsSequence :1;
//STRIP001  BOOL            m_bSortByDocument :1;
//STRIP001     LanguageType    m_eLanguage;
//STRIP001     String          m_sSortAlgorithm;
//STRIP001
//STRIP001  const SwAuthorityFieldType& operator=( const SwAuthorityFieldType& );

public:
    SwAuthorityFieldType(SwDoc* pDoc): SwFieldType( RES_AUTHORITY ){DBG_ASSERT(0, "STRIP");} //STRIP001 SwAuthorityFieldType(SwDoc* pDoc);
//STRIP001  SwAuthorityFieldType( const SwAuthorityFieldType& );
//STRIP001  ~SwAuthorityFieldType();
//STRIP001
    virtual SwFieldType* Copy()    const{DBG_ASSERT(0, "STRIP"); return NULL;} //STRIP001 virtual SwFieldType* Copy()    const;
//STRIP001  virtual void        Modify( SfxPoolItem *pOld, SfxPoolItem *pNew );
//STRIP001
//STRIP001  virtual BOOL        QueryValue( com::sun::star::uno::Any& rVal, BYTE nMId ) const;
//STRIP001  virtual BOOL        PutValue( const com::sun::star::uno::Any& rVal, BYTE nMId );
//STRIP001
//STRIP001  inline SwDoc*   GetDoc() const                      { return m_pDoc; }
//STRIP001  inline void     SetDoc(SwDoc* pNewDoc)              { m_pDoc = pNewDoc; }
//STRIP001
//STRIP001  void                RemoveField(long nHandle);
//STRIP001  long                AddField(const String& rFieldContents);
//STRIP001  BOOL                AddField(long nHandle);
//STRIP001  void                DelSequenceArray()
//STRIP001                      {
//STRIP001                          m_pSequArr->Remove(0, m_pSequArr->Count());
//STRIP001                      }
//STRIP001
//STRIP001  const SwAuthEntry*  GetEntryByHandle(long nHandle) const;
//STRIP001
//STRIP001  void                GetAllEntryIdentifiers( SvStringsDtor& rToFill )const;
//STRIP001  const SwAuthEntry*  GetEntryByIdentifier(const String& rIdentifier)const;
//STRIP001
//STRIP001  void                ChangeEntryContent(const SwAuthEntry* pNewEntry);
//STRIP001  // import interface
//STRIP001  USHORT              AppendField(const SwAuthEntry& rInsert);
//STRIP001  void                MergeFieldType(const SwAuthorityFieldType& rNew, SvUShorts& rMap);
//STRIP001  void                RemoveUnusedFields();
//STRIP001  long                GetHandle(USHORT nPos);
//STRIP001  USHORT              GetPosition(long nHandle);
//STRIP001
//STRIP001  USHORT              GetEntryCount() const;
//STRIP001  const SwAuthEntry*  GetEntryByPosition(USHORT nPos) const;
//STRIP001
//STRIP001  USHORT              GetSequencePos(long nHandle);
//STRIP001
//STRIP001  BOOL                IsSequence() const      {return m_bIsSequence;}
//STRIP001  void                SetSequence(BOOL bSet)
//STRIP001                          {
//STRIP001                              DelSequenceArray();
//STRIP001                              m_bIsSequence = bSet;
//STRIP001                          }
//STRIP001
//STRIP001  void                SetPreSuffix( sal_Unicode cPre, sal_Unicode cSuf)
//STRIP001                          {
//STRIP001                              m_cPrefix = cPre;
//STRIP001                              m_cSuffix = cSuf;
//STRIP001                          }
//STRIP001  sal_Unicode         GetPrefix() const { return m_cPrefix;}
//STRIP001  sal_Unicode         GetSuffix() const { return m_cSuffix;}
//STRIP001
//STRIP001  BOOL                IsSortByDocument() const {return m_bSortByDocument;}
//STRIP001  void                SetSortByDocument(BOOL bSet)
//STRIP001                          {
//STRIP001                              DelSequenceArray();
//STRIP001                              m_bSortByDocument = bSet;
//STRIP001                          }
//STRIP001
//STRIP001  USHORT              GetSortKeyCount() const ;
//STRIP001  const SwTOXSortKey* GetSortKey(USHORT nIdx) const ;
//STRIP001  void                SetSortKeys(USHORT nKeyCount, SwTOXSortKey nKeys[]);
//STRIP001
//STRIP001  //initui.cxx
//STRIP001  static const String&    GetAuthFieldName(ToxAuthorityField eType);
//STRIP001  static const String&    GetAuthTypeName(ToxAuthorityType eType);
//STRIP001
//STRIP001     LanguageType    GetLanguage() const {return m_eLanguage;}
//STRIP001     void            SetLanguage(LanguageType nLang)  {m_eLanguage = nLang;}
//STRIP001
//STRIP001     const String&   GetSortAlgorithm()const {return m_sSortAlgorithm;}
//STRIP001     void            SetSortAlgorithm(const String& rSet) {m_sSortAlgorithm = rSet;}
//STRIP001
};
/* -----------------14.09.99 16:15-------------------

 --------------------------------------------------*/
class SwAuthorityField : public SwField
{
//STRIP001  long    nHandle;

public:
    SwAuthorityField(SwAuthorityFieldType* pType, const String& rFieldContents): SwField(pType){DBG_ASSERT(0, "STRIP");} //STRIP001 SwAuthorityField(SwAuthorityFieldType* pType, const String& rFieldContents);
    SwAuthorityField(SwAuthorityFieldType* pType, long nHandle): SwField(pType){DBG_ASSERT(0, "STRIP");} //STRIP001 SwAuthorityField(SwAuthorityFieldType* pType, long nHandle);
//STRIP001  ~SwAuthorityField();

//STRIP001  const String&       GetFieldText(ToxAuthorityField eField) const;

    virtual String      Expand() const{DBG_ASSERT(0, "STRIP"); String sRet; return sRet;} //STRIP001 virtual String     Expand() const;
    virtual SwField*    Copy() const{DBG_ASSERT(0, "STRIP"); return NULL;} //STRIP001 virtual SwField*  Copy() const;
//STRIP001  virtual void        SetPar1(const String& rStr);
//STRIP001  virtual SwFieldType* ChgTyp( SwFieldType* );

//STRIP001  virtual BOOL        QueryValue( com::sun::star::uno::Any& rVal, BYTE nMId ) const;
//STRIP001  virtual BOOL        PutValue( const com::sun::star::uno::Any& rVal, BYTE nMId );

//STRIP001  long                GetHandle() const       { return nHandle; }

    //import interface
//STRIP001  USHORT              GetHandlePosition() const;
};

// --- inlines -----------------------------------------------------------
//STRIP001 inline const String&     SwAuthEntry::GetAuthorField(ToxAuthorityField ePos)const
//STRIP001 {
//STRIP001  DBG_ASSERT(AUTH_FIELD_END > ePos, "wrong index")
//STRIP001  return aAuthFields[ePos];
//STRIP001 }
//STRIP001 inline void  SwAuthEntry::SetAuthorField(ToxAuthorityField ePos, const String& rField)
//STRIP001 {
//STRIP001  DBG_ASSERT(AUTH_FIELD_END > ePos, "wrong index")
//STRIP001  if(AUTH_FIELD_END > ePos)
//STRIP001      aAuthFields[ePos] = rField;
//STRIP001 }

#endif

