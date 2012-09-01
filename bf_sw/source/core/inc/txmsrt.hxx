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
#ifndef _TXMSRT_HXX
#define _TXMSRT_HXX

#include <bf_svtools/bf_solar.h>

#include <i18npool/lang.h>
#include <tox.hxx>
class CharClass;
namespace binfilter {


class SwCntntNode;
class SwTxtNode;
class SwTxtTOXMark;
class SwIndex;
class SwFmtFld;
class IndexEntrySupplierWrapper;

enum TOXSortType
{
    TOX_SORT_INDEX,
    TOX_SORT_CUSTOM,
    TOX_SORT_CONTENT,
    TOX_SORT_PARA,
    TOX_SORT_TABLE,
    TOX_SORT_AUTHORITY
};

struct SwTOXSource
{
    const SwCntntNode* pNd;
    xub_StrLen nPos;
    BOOL bMainEntry;

    SwTOXSource() : pNd(0), nPos(0), bMainEntry(FALSE) {}
    SwTOXSource( const SwCntntNode* pNode, xub_StrLen n, BOOL bMain )
        : pNd(pNode), nPos(n), bMainEntry(bMain)
    {}
};

SV_DECL_VARARR( SwTOXSources, SwTOXSource, 0, 10 )

class SwTOXInternational
{
    IndexEntrySupplierWrapper* pIndexWrapper;
    CharClass* pCharClass;
    LanguageType eLang;
     String sSortAlgorithm;
     USHORT nOptions;

    void Init();

public:
    SwTOXInternational( LanguageType nLang, USHORT nOptions,
                        const String& rSortAlgorithm );
    SwTOXInternational( const SwTOXInternational& );
    ~SwTOXInternational();

     sal_Int32 Compare( const String& rTxt1, const String& rTxtReading1,
                        const ::com::sun::star::lang::Locale& rLocale1,
                        const String& rTxt2, const String& rTxtReading2,
                        const ::com::sun::star::lang::Locale& rLocale2 ) const;

     inline BOOL IsEqual( const String& rTxt1, const String& rTxtReading1,
                          const ::com::sun::star::lang::Locale& rLocale1,
                          const String& rTxt2, const String& rTxtReading2,
                          const ::com::sun::star::lang::Locale& rLocale2 ) const
    {
         return 0 == Compare( rTxt1, rTxtReading1, rLocale1,
                              rTxt2, rTxtReading2, rLocale2 );
    }
    inline BOOL IsNumeric( const String& rStr ) const;
};

/*--------------------------------------------------------------------
     Beschreibung: Klassen fuer die Sortierung der Verzeichnisse
 --------------------------------------------------------------------*/

struct SwTOXSortTabBase
{
    SwTOXSources aTOXSources;
     ::com::sun::star::lang::Locale aLocale;
    const SwTxtNode* pTOXNd;
    const SwTxtTOXMark* pTxtMark;
    const SwTOXInternational* pTOXIntl;
    ULONG nPos;
    xub_StrLen nCntPos;
     USHORT nType;
    static USHORT nOpt;

    USHORT  GetType() const         { return nType; }
    USHORT  GetOptions() const      { return nOpt; }

    virtual ~SwTOXSortTabBase() {}

    virtual void    FillText( SwTxtNode& rNd, const SwIndex& rInsPos, USHORT nAuthField = 0) const;
    virtual USHORT  GetLevel()  const = 0;
    virtual BOOL    operator==( const SwTOXSortTabBase& );
    virtual BOOL    operator<( const SwTOXSortTabBase& );

    virtual String  GetURL() const;

     inline void GetTxt( String&, String& ) const;
     inline const ::com::sun::star::lang::Locale& GetLocale() const;

protected:
    SwTOXSortTabBase( TOXSortType nType,
                      const SwCntntNode* pTOXSrc,
                      const SwTxtTOXMark* pTxtMark,
                      const SwTOXInternational* pIntl,
                      const ::com::sun::star::lang::Locale* pLocale = NULL );

private:
    BOOL bValidTxt;
     String sSortTxt;
     String sSortTxtReading;

     virtual void _GetText( String&, String& ) = 0;
};

inline void SwTOXSortTabBase::GetTxt( String& rSortTxt,
                                      String& rSortTxtReading ) const
{
    if( !bValidTxt )
    {
        SwTOXSortTabBase* pThis = (SwTOXSortTabBase*)this;
        pThis->_GetText( pThis->sSortTxt, pThis->sSortTxtReading );
        pThis->bValidTxt = TRUE;
    }

     rSortTxt = sSortTxt;
     rSortTxtReading = sSortTxtReading;
 }

 inline const ::com::sun::star::lang::Locale& SwTOXSortTabBase::GetLocale() const
 {
     return aLocale;
 }

/*--------------------------------------------------------------------
     Beschreibung: fuer Sortierung nach Text
 --------------------------------------------------------------------*/



/*--------------------------------------------------------------------
     Beschreibung: fuer Sortierung nach Position
 --------------------------------------------------------------------*/




struct SwTOXAuthority : public SwTOXSortTabBase
{
private:
    SwFmtFld& m_rField;
    virtual void    FillText( SwTxtNode& rNd, const SwIndex& rInsPos, USHORT nAuthField = 0 ) const;
    virtual void _GetText( String&, String& );

public:
    SwTOXAuthority( const SwCntntNode& rNd, SwFmtFld& rField, const SwTOXInternational& rIntl );
    virtual ~SwTOXAuthority() {}
    SwFmtFld& GetFldFmt() {return m_rField;}

    virtual BOOL    operator==( const SwTOXSortTabBase& );
    virtual BOOL    operator<( const SwTOXSortTabBase& );
    virtual USHORT  GetLevel() const;
};


} //namespace binfilter
#endif // _TXMSRT_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
