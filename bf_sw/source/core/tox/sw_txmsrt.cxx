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


#ifdef _MSC_VER
#pragma hdrstop
#endif

#include <unotools/charclass.hxx>
#include <com/sun/star/i18n/CollatorOptions.hpp>
#include <bf_svx/unolingu.hxx>

#include <txtfld.hxx>

#include <horiornt.hxx>

#include <cntfrm.hxx>
#include <pam.hxx>
#include <txttxmrk.hxx>
#include <fmtfld.hxx>
#include <txmsrt.hxx>
#include <ndtxt.hxx>
#include <expfld.hxx>
#include <authfld.hxx>
#include <toxwrap.hxx>

#include <comcore.hrc>
namespace binfilter {

extern BOOL IsFrameBehind( const SwTxtNode& rMyNd, xub_StrLen nMySttPos,
                           const SwTxtNode& rBehindNd, xub_StrLen nSttPos );

using namespace ::com::sun::star::uno;
using namespace ::rtl;
/*--------------------------------------------------------------------
    Beschreibung: Strings initialisieren
 --------------------------------------------------------------------*/


SV_IMPL_VARARR( SwTOXSources, SwTOXSource )


SwTOXInternational::SwTOXInternational( LanguageType nLang, USHORT nOpt,
                                        const String& rSortAlgorithm ) :
    eLang( nLang ),
    sSortAlgorithm(rSortAlgorithm),
    nOptions( nOpt )
{
    Init();
}

 SwTOXInternational::SwTOXInternational( const SwTOXInternational& rIntl ) :
     eLang( rIntl.eLang ),
     sSortAlgorithm(rIntl.sSortAlgorithm),
     nOptions( rIntl.nOptions )
 {
   Init();
 }

 void SwTOXInternational::Init()
 {
    pIndexWrapper = new IndexEntrySupplierWrapper();

     const ::com::sun::star::lang::Locale aLcl( SvxCreateLocale( eLang ) );
     pIndexWrapper->SetLocale( aLcl );

     if(!sSortAlgorithm.Len())
     {
         Sequence < OUString > aSeq( pIndexWrapper->GetAlgorithmList( aLcl ));
         if(aSeq.getLength())
             sSortAlgorithm = aSeq.getConstArray()[0];
     }

     if ( nOptions & TOI_CASE_SENSITIVE )
         pIndexWrapper->LoadAlgorithm( aLcl, sSortAlgorithm, 0 );
     else
         pIndexWrapper->LoadAlgorithm( aLcl, sSortAlgorithm, SW_COLLATOR_IGNORES );

    pCharClass = new CharClass( aLcl );

 }

 SwTOXInternational::~SwTOXInternational()
 {
    delete pCharClass;
    delete pIndexWrapper;
 }

inline BOOL SwTOXInternational::IsNumeric( const String& rStr ) const
{
    return pCharClass->isNumeric( rStr );
}

sal_Int32 SwTOXInternational::Compare( const String& rTxt1, const String& rTxtReading1,
                                       const ::com::sun::star::lang::Locale& rLocale1,
                                       const String& rTxt2, const String& rTxtReading2,
                                       const ::com::sun::star::lang::Locale& rLocale2 ) const
{
    return pIndexWrapper->CompareIndexEntry( rTxt1, rTxtReading1, rLocale1,
                                             rTxt2, rTxtReading2, rLocale2 );
}



/*--------------------------------------------------------------------
     Beschreibung:  SortierElement fuer Verzeichniseintraege
 --------------------------------------------------------------------*/


SwTOXSortTabBase::SwTOXSortTabBase( TOXSortType nTyp, const SwCntntNode* pNd,
                                    const SwTxtTOXMark* pMark,
                                    const SwTOXInternational* pInter,
                                    const ::com::sun::star::lang::Locale* pLocale )
    : pTOXNd( 0 )
    , pTxtMark( pMark )
    , pTOXIntl( pInter )
    , nPos( 0 )
    , nCntPos( 0 )
    , nType( nTyp )
    , bValidTxt( FALSE )
{
    if ( pLocale )
        aLocale = *pLocale;

    if( pNd )
    {
        xub_StrLen n = 0;
        if( pTxtMark )
            n = *pTxtMark->GetStart();
        SwTOXSource aTmp( pNd, n,
                    pTxtMark ? pTxtMark->GetTOXMark().IsMainEntry() : FALSE );
        aTOXSources.Insert( aTmp, aTOXSources.Count() );

        nPos = pNd->GetIndex();

        switch( nTyp )
        {
        case TOX_SORT_CONTENT:
        case TOX_SORT_PARA:
        case TOX_SORT_TABLE:
            // falls sie in Sonderbereichen stehen, sollte man die
            // Position im Body besorgen
            if( nPos < pNd->GetNodes().GetEndOfExtras().GetIndex() )
            {
                // dann die "Anker" (Body) Position holen.
                Point aPt;
                const SwCntntFrm* pFrm = pNd->GetFrm( &aPt, 0, FALSE );
                if( pFrm )
                {
                    SwPosition aPos( *pNd );
                    const SwDoc& rDoc = *pNd->GetDoc();
#ifdef DBG_UTIL
                    OSL_ENSURE( GetBodyTxtNode( rDoc, aPos, *pFrm ),
                            "wo steht der Absatz" );
#else
                    GetBodyTxtNode( rDoc, aPos, *pFrm );
#endif
                    nPos = aPos.nNode.GetIndex();
                    nCntPos = aPos.nContent.GetIndex();
                }
            }
            else
                nCntPos = n;
            break;
        default:
            break;
        }
    }
}


String SwTOXSortTabBase::GetURL() const
{
    return aEmptyStr;
}

void SwTOXSortTabBase::FillText( SwTxtNode& rNd, const SwIndex& rInsPos,
                                    USHORT ) const
{
    String sMyTxt;
    String sMyTxtReading;

    GetTxt( sMyTxt, sMyTxtReading );

    rNd.Insert( sMyTxt, rInsPos );
}

BOOL SwTOXSortTabBase::operator==( const SwTOXSortTabBase& rCmp )
{
    BOOL bRet = nPos == rCmp.nPos && nCntPos == rCmp.nCntPos &&
            (!aTOXSources[0].pNd || !rCmp.aTOXSources[0].pNd ||
            aTOXSources[0].pNd == rCmp.aTOXSources[0].pNd );

    if( TOX_SORT_CONTENT == nType )
    {
        bRet = bRet && pTxtMark && rCmp.pTxtMark &&
                *pTxtMark->GetStart() == *rCmp.pTxtMark->GetStart();

        if( bRet )
        {
            // beide Pointer vorhanden -> vergleiche Text
            // beide Pointer nicht vorhanden -> vergleiche AlternativText
            const xub_StrLen *pEnd  = pTxtMark->GetEnd(),
                             *pEndCmp = rCmp.pTxtMark->GetEnd();

            String sMyTxt;
            String sMyTxtReading;
            GetTxt( sMyTxt, sMyTxtReading );

            String sOtherTxt;
            String sOtherTxtReading;
            rCmp.GetTxt( sOtherTxt, sOtherTxtReading );

            bRet = ( ( pEnd && pEndCmp ) || ( !pEnd && !pEndCmp ) ) &&
                    pTOXIntl->IsEqual( sMyTxt, sMyTxtReading, GetLocale(),
                                       sOtherTxt, sOtherTxtReading, rCmp.GetLocale() );
        }
    }
    return bRet;
}

BOOL SwTOXSortTabBase::operator<( const SwTOXSortTabBase& rCmp )
{
    if( nPos < rCmp.nPos )
        return TRUE;

    if( nPos == rCmp.nPos )
    {
        if( nCntPos < rCmp.nCntPos )
            return TRUE;

        if( nCntPos == rCmp.nCntPos )
        {
            const SwNode* pFirst = aTOXSources[0].pNd;
            const SwNode* pNext = rCmp.aTOXSources[0].pNd;

            if( pFirst && pFirst == pNext )
            {
                if( TOX_SORT_CONTENT == nType && pTxtMark && rCmp.pTxtMark )
                {
                    if( *pTxtMark->GetStart() < *rCmp.pTxtMark->GetStart() )
                        return TRUE;

                    if( *pTxtMark->GetStart() == *rCmp.pTxtMark->GetStart() )
                    {
                        const xub_StrLen *pEnd = pTxtMark->GetEnd(),
                                         *pEndCmp = rCmp.pTxtMark->GetEnd();

                        String sMyTxt;
                        String sMyTxtReading;
                        GetTxt( sMyTxt, sMyTxtReading );

                        String sOtherTxt;
                        String sOtherTxtReading;
                        rCmp.GetTxt( sOtherTxt, sOtherTxtReading );

                        // beide Pointer vorhanden -> vergleiche Text
                        // beide Pointer nicht vorhanden -> vergleiche AlternativText
                        if( ( pEnd && pEndCmp ) || ( !pEnd && !pEndCmp ) )
                            pTOXIntl->IsEqual( sMyTxt, sMyTxtReading, GetLocale(),
                                               sOtherTxt, sOtherTxtReading, rCmp.GetLocale() );

                        if( pEnd && !pEndCmp )
                            return TRUE;
                    }
                }
            }
            else if( pFirst && pFirst->IsTxtNode() &&
                     pNext && pNext->IsTxtNode() )
                    return ::binfilter::IsFrameBehind( *(SwTxtNode*)pNext, nCntPos,
                                            *(SwTxtNode*)pFirst, nCntPos );
        }
    }
    return FALSE;
}

/*--------------------------------------------------------------------
     Beschreibung: sortierter Stichworteintrag
 --------------------------------------------------------------------*/



//
// Stichworte vergleichen. Bezieht sich nur auf den Text
//



//
// kleiner haengt nur vom Text ab


//


//
// Das Stichwort selbst


//






/*--------------------------------------------------------------------
     Beschreibung: Schluessel und Trennzeichen
 --------------------------------------------------------------------*/












/*--------------------------------------------------------------------
     Beschreibung: sortierter Inhaltsverz. Eintrag
 --------------------------------------------------------------------*/




//  Der Text des Inhalts
//



//
// Die Ebene fuer Anzeige
//



/*--------------------------------------------------------------------
     Beschreibung: Verzeichnis aus Absaetzen zusammengesammelt
 --------------------------------------------------------------------*/

// bei Sortierung von OLE/Grafiken aufpassen !!!
// Die Position darf nicht die im Dokument,
// sondern muss die vom "Henkel" sein  !!











/*--------------------------------------------------------------------
    Beschreibung: Tabelle
 --------------------------------------------------------------------*/









SwTOXAuthority::SwTOXAuthority( const SwCntntNode& rNd,
                SwFmtFld& rField, const SwTOXInternational& rIntl ) :
    SwTOXSortTabBase( TOX_SORT_AUTHORITY, &rNd, 0, &rIntl ),
    m_rField(rField)
{
    if(rField.GetTxtFld())
        nCntPos = *rField.GetTxtFld()->GetStart();
}

USHORT SwTOXAuthority::GetLevel() const
{
    String sText(((SwAuthorityField*)m_rField.GetFld())->
                        GetFieldText(AUTH_FIELD_AUTHORITY_TYPE));
    USHORT nRet = 0;
    if( pTOXIntl->IsNumeric( sText ) )
    {
        nRet = (USHORT)sText.ToInt32();
        nRet++;
    }
    if(nRet >= AUTH_TYPE_END)
        nRet = 0;
    return nRet;
 }

void SwTOXAuthority::_GetText( String& rTxt, String& /*rTxtReading*/ )
{
    //
    rTxt = m_rField.GetFld()->Expand();
}


void    SwTOXAuthority::FillText( SwTxtNode& rNd,
                        const SwIndex& rInsPos, USHORT nAuthField ) const
{
    SwAuthorityField* pField = (SwAuthorityField*)m_rField.GetFld();
    String sText;
    if(AUTH_FIELD_IDENTIFIER == nAuthField)
    {
        sText = pField->Expand();
        const SwAuthorityFieldType* pType = (const SwAuthorityFieldType*)pField->GetTyp();
        sal_Unicode cChar = pType->GetPrefix();
        if(cChar && cChar != ' ')
        sText.Erase(0, 1);
        cChar = pType->GetSuffix();
        if(cChar && cChar != ' ')
        sText.Erase(sText.Len() - 1, 1);
    }
    else if(AUTH_FIELD_AUTHORITY_TYPE == nAuthField)
    {
        USHORT nLevel = GetLevel();
        if(nLevel)
            sText = SwAuthorityFieldType::GetAuthTypeName((ToxAuthorityType) --nLevel);
    }
    else
        sText = (pField->GetFieldText((ToxAuthorityField) nAuthField));
    rNd.Insert( sText, rInsPos );
}

BOOL    SwTOXAuthority::operator==( const SwTOXSortTabBase& rCmp)
{
    return nType == rCmp.nType &&
            ((SwAuthorityField*)m_rField.GetFld())->GetHandle() ==
                ((SwAuthorityField*)((SwTOXAuthority&)rCmp).m_rField.GetFld())->GetHandle();
}

BOOL    SwTOXAuthority::operator<( const SwTOXSortTabBase& rBase)
{
    BOOL bRet = FALSE;
    SwAuthorityField* pField = (SwAuthorityField*)m_rField.GetFld();
    SwAuthorityFieldType* pType = (SwAuthorityFieldType*)
                                                pField->GetTyp();
    if(pType->IsSortByDocument())
        bRet = SwTOXSortTabBase::operator<(rBase);
    else
    {
        SwAuthorityField* pCmpField = (SwAuthorityField*)
                        ((SwTOXAuthority&)rBase).m_rField.GetFld();


        for(USHORT i = 0; i < pType->GetSortKeyCount(); i++)
        {
            const SwTOXSortKey* pKey = pType->GetSortKey(i);
            String sMyTxt = pField->GetFieldText(pKey->eField);
            String sMyTxtReading;
            String sOtherTxt = pCmpField->GetFieldText(pKey->eField);
            String sOtherTxtReading;

            sal_Int32 nComp = pTOXIntl->Compare( sMyTxt, sMyTxtReading, GetLocale(),
                                                 sOtherTxt, sOtherTxtReading, rBase.GetLocale() );

            if( nComp )
            {
                bRet = (-1 == nComp) == pKey->bSortAscending;
                break;
            }
        }
    }
    return bRet;
}

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
