/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */
#ifndef _AUTHFLD_HXX
#define _AUTHFLD_HXX

#include <bf_svtools/bf_solar.h>

#include <fldbas.hxx>
#include <toxe.hxx>

#define _SVSTDARR_LONGS
#include <bf_svtools/svstdarr.hxx>
namespace binfilter {
class SvUShorts;
extern String& GetString( const ::com::sun::star::uno::Any& rAny, String& rStr );

class SwAuthDataArr;


class SwAuthEntry
{
    String      aAuthFields[AUTH_FIELD_END];
    USHORT      nRefCount;
public:
    SwAuthEntry() : nRefCount(0){}
    SwAuthEntry( const SwAuthEntry& rCopy );
    BOOL            operator==(const SwAuthEntry& rComp);

    inline const String&    GetAuthorField(ToxAuthorityField ePos)const;
    inline void             SetAuthorField(ToxAuthorityField ePos,
                                            const String& rField);

    void            AddRef()                { ++nRefCount; }
    void            RemoveRef()             { --nRefCount; }
    USHORT          GetRefCount()           { return nRefCount; }
};


struct SwTOXSortKey
{
    ToxAuthorityField   eField;
    BOOL                bSortAscending;
    SwTOXSortKey() :
        eField(AUTH_FIELD_END),
        bSortAscending(TRUE){}
};




class SwAuthorityField;
class SortKeyArr;
class SwAuthorityFieldType : public SwFieldType
{
    SwDoc*          m_pDoc;
    SwAuthDataArr*  m_pDataArr;
    SvLongs*        m_pSequArr;
    SortKeyArr*     m_pSortKeyArr;
    sal_Unicode     m_cPrefix;
    sal_Unicode     m_cSuffix;
    BOOL            m_bIsSequence :1;
    BOOL            m_bSortByDocument :1;
    LanguageType    m_eLanguage;
    String          m_sSortAlgorithm;

    const SwAuthorityFieldType& operator=( const SwAuthorityFieldType& );

public:
    SwAuthorityFieldType(SwDoc* pDoc);
    SwAuthorityFieldType( const SwAuthorityFieldType& );
    ~SwAuthorityFieldType();

    virtual SwFieldType* Copy()    const;
    virtual void        Modify( SfxPoolItem *pOld, SfxPoolItem *pNew );

    virtual BOOL        QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMId ) const;
    virtual BOOL        PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMId );

    inline SwDoc*   GetDoc() const                      { return m_pDoc; }
    inline void     SetDoc(SwDoc* pNewDoc)              { m_pDoc = pNewDoc; }

    void                RemoveField(long nHandle);
    long                AddField(const String& rFieldContents);
    BOOL                AddField(long nHandle);
    void                DelSequenceArray()
                        {
                            m_pSequArr->Remove(0, m_pSequArr->Count());
                        }

    const SwAuthEntry*  GetEntryByHandle(long nHandle) const;

    // import interface
    USHORT              AppendField(const SwAuthEntry& rInsert);
    long                GetHandle(USHORT nPos);

    USHORT              GetEntryCount() const;

    USHORT              GetSequencePos(long nHandle);

    BOOL                IsSequence() const      {return m_bIsSequence;}
    void                SetSequence(BOOL bSet)
                            {
                                DelSequenceArray();
                                m_bIsSequence = bSet;
                            }

    void                SetPreSuffix( sal_Unicode cPre, sal_Unicode cSuf)
                            {
                                m_cPrefix = cPre;
                                m_cSuffix = cSuf;
                            }
    sal_Unicode         GetPrefix() const { return m_cPrefix;}
    sal_Unicode         GetSuffix() const { return m_cSuffix;}

    BOOL                IsSortByDocument() const {return m_bSortByDocument;}
    void                SetSortByDocument(BOOL bSet)
                            {
                                DelSequenceArray();
                                m_bSortByDocument = bSet;
                            }

    USHORT              GetSortKeyCount() const ;
    const SwTOXSortKey* GetSortKey(USHORT nIdx) const ;
    void                SetSortKeys(USHORT nKeyCount, SwTOXSortKey nKeys[]);
    static const String&    GetAuthTypeName(ToxAuthorityType eType);

    LanguageType    GetLanguage() const {return m_eLanguage;}
    void            SetLanguage(LanguageType nLang)  {m_eLanguage = nLang;}

    const String&   GetSortAlgorithm()const {return m_sSortAlgorithm;}
    void            SetSortAlgorithm(const String& rSet) {m_sSortAlgorithm = rSet;}

};


class SwAuthorityField : public SwField
{
    long    nHandle;

public:
    SwAuthorityField(SwAuthorityFieldType* pType, const String& rFieldContents);
    SwAuthorityField(SwAuthorityFieldType* pType, long nHandle);
    ~SwAuthorityField();

    const String&       GetFieldText(ToxAuthorityField eField) const;

    virtual String      Expand() const;
    virtual SwField*    Copy() const;
    virtual void        SetPar1(const String& rStr);
    virtual SwFieldType* ChgTyp( SwFieldType* );

    virtual BOOL        QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMId ) const;
    virtual BOOL        PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMId );

    long                GetHandle() const       { return nHandle; }
};

// --- inlines -----------------------------------------------------------
inline const String&    SwAuthEntry::GetAuthorField(ToxAuthorityField ePos)const
{
    DBG_ASSERT(AUTH_FIELD_END > ePos, "wrong index");
    return aAuthFields[ePos];
}
inline void SwAuthEntry::SetAuthorField(ToxAuthorityField ePos, const String& rField)
{
    DBG_ASSERT(AUTH_FIELD_END > ePos, "wrong index");
    if(AUTH_FIELD_END > ePos)
        aAuthFields[ePos] = rField;
}

} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
