/*************************************************************************
 *
 *  $RCSfile: sw_txmsrt.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: pjunck $ $Date: 2004-10-27 13:37:11 $
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

// auto strip #ifndef _TOOLS_RESID_HXX
// auto strip #include <tools/resid.hxx>
// auto strip #endif
#ifndef _UNOTOOLS_CHARCLASS_HXX
#include <unotools/charclass.hxx>
#endif
#ifndef _COM_SUN_STAR_I18N_COLLATOROPTIONS_HPP_
#include <com/sun/star/i18n/CollatorOptions.hpp>
#endif
#ifndef _UNO_LINGU_HXX
#include <bf_svx/unolingu.hxx>
#endif

#ifndef _TXTFLD_HXX
#include <txtfld.hxx>
#endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif
// auto strip #ifndef _ERRHDL_HXX
// auto strip #include <errhdl.hxx>
// auto strip #endif

// auto strip #ifndef _DOC_HXX
// auto strip #include <doc.hxx>
// auto strip #endif
// auto strip #ifndef _DOCARY_HXX
// auto strip #include <docary.hxx>
// auto strip #endif
#ifndef _CNTFRM_HXX
#include <cntfrm.hxx>
#endif
// auto strip #ifndef _NODE_HXX
// auto strip #include <node.hxx>
// auto strip #endif
// auto strip #ifndef _FRMATR_HXX
// auto strip #include <frmatr.hxx>
// auto strip #endif
#ifndef _PAM_HXX
#include <pam.hxx>
#endif
#ifndef _TXTTXMRK_HXX //autogen
#include <txttxmrk.hxx>
#endif
// auto strip #ifndef _FRMFMT_HXX //autogen
// auto strip #include <frmfmt.hxx>
// auto strip #endif
#ifndef _FMTFLD_HXX
#include <fmtfld.hxx>
#endif
#ifndef _TXMSRT_HXX
#include <txmsrt.hxx>
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>
#endif
// auto strip #ifndef _TXTATR_HXX
// auto strip #include <txtatr.hxx>
// auto strip #endif
// auto strip #ifndef _FMTCOL_HXX
// auto strip #include <fmtcol.hxx>
// auto strip #endif
// auto strip #ifndef _SWTABLE_HXX
// auto strip #include <swtable.hxx>
// auto strip #endif
#ifndef _EXPFLD_HXX
#include <expfld.hxx>
#endif
// auto strip #ifndef _NUMRULE_HXX
// auto strip #include <numrule.hxx>
// auto strip #endif
#ifndef _AUTHFLD_HXX
#include <authfld.hxx>
#endif
#ifndef _TOXWRAP_HXX
#include <toxwrap.hxx>
#endif

#ifndef _COMCORE_HRC
#include <comcore.hrc>
#endif
namespace binfilter {

extern BOOL IsFrameBehind( const SwTxtNode& rMyNd, xub_StrLen nMySttPos,
                           const SwTxtNode& rBehindNd, xub_StrLen nSttPos );

using namespace ::com::sun::star::uno;
using namespace ::rtl;
/*--------------------------------------------------------------------
    Beschreibung: Strings initialisieren
 --------------------------------------------------------------------*/

//STRIP001 USHORT SwTOXSortTabBase::nOpt = 0;

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

//STRIP001 String SwTOXInternational::ToUpper( const String& rStr, xub_StrLen nPos ) const
//STRIP001 {
//STRIP001  return pCharClass->toUpper( rStr, nPos, 1 );
//STRIP001 }
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

//STRIP001 String SwTOXInternational::GetIndexKey( const String& rTxt, const String& rTxtReading,
//STRIP001                                         const ::com::sun::star::lang::Locale& rLocale ) const
//STRIP001 {
//STRIP001     return pIndexWrapper->GetIndexKey( rTxt, rTxtReading, rLocale );
//STRIP001 }

//STRIP001 String SwTOXInternational::GetFollowingText( BOOL bMorePages ) const
//STRIP001 {
//STRIP001  return pIndexWrapper->GetFollowingText( bMorePages );
//STRIP001 }

/*--------------------------------------------------------------------
     Beschreibung:  SortierElement fuer Verzeichniseintraege
 --------------------------------------------------------------------*/


SwTOXSortTabBase::SwTOXSortTabBase( TOXSortType nTyp, const SwCntntNode* pNd,
                                    const SwTxtTOXMark* pMark,
                                    const SwTOXInternational* pInter,
                                    const ::com::sun::star::lang::Locale* pLocale )
    : pTxtMark( pMark ), pTOXNd( 0 ), nPos( 0 ), nType( nTyp ),
    pTOXIntl( pInter ), bValidTxt( FALSE ), nCntPos( 0 )
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
#ifndef PRODUCT
                    ASSERT( GetBodyTxtNode( rDoc, aPos, *pFrm ),
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


//STRIP001 SwTOXIndex::SwTOXIndex( const SwTxtNode& rNd,
//STRIP001                         const SwTxtTOXMark* pMark, USHORT nOptions,
//STRIP001                         BYTE nKyLevel,
//STRIP001                         const SwTOXInternational& rIntl,
//STRIP001                         const ::com::sun::star::lang::Locale& rLocale )
//STRIP001     : SwTOXSortTabBase( TOX_SORT_INDEX, &rNd, pMark, &rIntl, &rLocale ),
//STRIP001  nKeyLevel(nKyLevel)
//STRIP001 {
//STRIP001  nPos = rNd.GetIndex();
//STRIP001  nOpt = nOptions;
//STRIP001 }

//
// Stichworte vergleichen. Bezieht sich nur auf den Text
//


//STRIP001 BOOL SwTOXIndex::operator==( const SwTOXSortTabBase& rCmpBase )
//STRIP001 {
//STRIP001  SwTOXIndex& rCmp = (SwTOXIndex&)rCmpBase;
//STRIP001
//STRIP001  // In Abhaengigkeit von den Optionen Grosskleinschreibung beachten
//STRIP001  if(GetLevel() != rCmp.GetLevel() || nKeyLevel != rCmp.nKeyLevel)
//STRIP001      return FALSE;
//STRIP001
//STRIP001  ASSERT(pTxtMark, "pTxtMark == 0, Kein Stichwort");
//STRIP001  const SwTOXMark& rTOXMark = pTxtMark->GetTOXMark();
//STRIP001
//STRIP001     String sMyTxt;
//STRIP001     String sMyTxtReading;
//STRIP001     GetTxt( sMyTxt, sMyTxtReading );
//STRIP001
//STRIP001     String sOtherTxt;
//STRIP001     String sOtherTxtReading;
//STRIP001     rCmp.GetTxt( sOtherTxt, sOtherTxtReading );
//STRIP001
//STRIP001     BOOL bRet = pTOXIntl->IsEqual( sMyTxt, sMyTxtReading, GetLocale(),
//STRIP001                                    sOtherTxt, sOtherTxtReading, rCmp.GetLocale() );
//STRIP001
//STRIP001  // Wenn nicht zusammengefasst wird muss die Pos aus gewertet werden
//STRIP001  if(bRet && !(GetOptions() & TOI_SAME_ENTRY))
//STRIP001      bRet = nPos == rCmp.nPos;
//STRIP001
//STRIP001  return bRet;
//STRIP001 }

//
// kleiner haengt nur vom Text ab


//

//STRIP001 BOOL SwTOXIndex::operator<( const SwTOXSortTabBase& rCmpBase )
//STRIP001 {
//STRIP001  SwTOXIndex& rCmp = (SwTOXIndex&)rCmpBase;
//STRIP001
//STRIP001  ASSERT(pTxtMark, "pTxtMark == 0, Kein Stichwort");
//STRIP001  const SwTOXMark& rTOXMark = pTxtMark->GetTOXMark();
//STRIP001
//STRIP001     String sMyTxt;
//STRIP001     String sMyTxtReading;
//STRIP001     GetTxt( sMyTxt, sMyTxtReading );
//STRIP001
//STRIP001     String sOtherTxt;
//STRIP001     String sOtherTxtReading;
//STRIP001     rCmp.GetTxt( sOtherTxt, sOtherTxtReading );
//STRIP001
//STRIP001     BOOL bRet = GetLevel() == rCmp.GetLevel() &&
//STRIP001                 pTOXIntl->IsLess( sMyTxt, sMyTxtReading, GetLocale(),
//STRIP001                                   sOtherTxt, sOtherTxtReading, rCmp.GetLocale() );
//STRIP001
//STRIP001  // Wenn nicht zusammengefasst wird muss die Pos aus gewertet werden
//STRIP001  if( !bRet && !(GetOptions() & TOI_SAME_ENTRY) )
//STRIP001     {
//STRIP001         bRet = pTOXIntl->IsEqual( sMyTxt, sMyTxtReading, GetLocale(),
//STRIP001                                    sOtherTxt, sOtherTxtReading, rCmp.GetLocale() ) &&
//STRIP001                nPos < rCmp.nPos;
//STRIP001     }
//STRIP001
//STRIP001  return bRet;
//STRIP001 }

//
// Das Stichwort selbst


//

//STRIP001 void SwTOXIndex::_GetText( String& rTxt, String& rTxtReading )
//STRIP001 {
//STRIP001  ASSERT(pTxtMark, "pTxtMark == 0, Kein Stichwort");
//STRIP001  const SwTOXMark& rTOXMark = pTxtMark->GetTOXMark();
//STRIP001  switch(nKeyLevel)
//STRIP001  {
//STRIP001      case FORM_PRIMARY_KEY    :
//STRIP001         {
//STRIP001          rTxt = rTOXMark.GetPrimaryKey();
//STRIP001             rTxtReading = rTOXMark.GetPrimaryKeyReading();
//STRIP001         }
//STRIP001      break;
//STRIP001      case FORM_SECONDARY_KEY  :
//STRIP001         {
//STRIP001          rTxt = rTOXMark.GetSecondaryKey();
//STRIP001             rTxtReading = rTOXMark.GetSecondaryKeyReading();
//STRIP001         }
//STRIP001      break;
//STRIP001      case FORM_ENTRY          :
//STRIP001         {
//STRIP001          rTxt = rTOXMark.GetText();
//STRIP001             rTxtReading = rTOXMark.GetTextReading();
//STRIP001         }
//STRIP001      break;
//STRIP001  }
//STRIP001  // if TOI_INITIAL_CAPS is set, first character is to be capitalized
//STRIP001  if( TOI_INITIAL_CAPS & nOpt && pTOXIntl )
//STRIP001  {
//STRIP001      String sUpper( pTOXIntl->ToUpper( rTxt, 0 ));
//STRIP001      rTxt.Erase( 0, 1 ).Insert( sUpper, 0 );
//STRIP001  }
//STRIP001 }

//STRIP001 void SwTOXIndex::FillText( SwTxtNode& rNd, const SwIndex& rInsPos, USHORT ) const
//STRIP001 {
//STRIP001  const xub_StrLen* pEnd = pTxtMark->GetEnd();
//STRIP001  String sTmp;
//STRIP001     String sTmpReading;
//STRIP001  if( pEnd && !pTxtMark->GetTOXMark().IsAlternativeText() &&
//STRIP001          0 == (GetOptions() & TOI_KEY_AS_ENTRY))
//STRIP001  {
//STRIP001      sTmp = ((SwTxtNode*)aTOXSources[0].pNd)->GetExpandTxt(
//STRIP001                          *pTxtMark->GetStart(),
//STRIP001                          *pEnd - *pTxtMark->GetStart());
//STRIP001      if(TOI_INITIAL_CAPS&nOpt && pTOXIntl)
//STRIP001      {
//STRIP001          String sUpper( pTOXIntl->ToUpper( sTmp, 0 ));
//STRIP001          sTmp.Erase( 0, 1 ).Insert( sUpper, 0 );
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001         GetTxt( sTmp, sTmpReading );
//STRIP001
//STRIP001  rNd.Insert( sTmp, rInsPos );
//STRIP001 }



//STRIP001 USHORT SwTOXIndex::GetLevel() const
//STRIP001 {
//STRIP001  ASSERT(pTxtMark, "pTxtMark == 0, Kein Stichwort");
//STRIP001
//STRIP001  USHORT nForm = FORM_PRIMARY_KEY;
//STRIP001
//STRIP001  if( 0 == (GetOptions() & TOI_KEY_AS_ENTRY)&&
//STRIP001      pTxtMark->GetTOXMark().GetPrimaryKey().Len() )
//STRIP001  {
//STRIP001      nForm = FORM_SECONDARY_KEY;
//STRIP001      if( pTxtMark->GetTOXMark().GetSecondaryKey().Len() )
//STRIP001          nForm = FORM_ENTRY;
//STRIP001  }
//STRIP001  return nForm;
//STRIP001 }

/*--------------------------------------------------------------------
     Beschreibung: Schluessel und Trennzeichen
 --------------------------------------------------------------------*/


//STRIP001 SwTOXCustom::SwTOXCustom(const String& rStr, USHORT nLevel,
//STRIP001                          const SwTOXInternational& rIntl,
//STRIP001                          const ::com::sun::star::lang::Locale& rLocale )
//STRIP001     : SwTOXSortTabBase( TOX_SORT_CUSTOM, 0, 0, &rIntl, &rLocale ),
//STRIP001  aKey(rStr), nLev(nLevel)
//STRIP001 {
//STRIP001 }


//STRIP001 BOOL SwTOXCustom::operator==(const SwTOXSortTabBase& rCmpBase)
//STRIP001 {
//STRIP001     String sMyTxt;
//STRIP001     String sMyTxtReading;
//STRIP001     GetTxt( sMyTxt, sMyTxtReading );
//STRIP001
//STRIP001     String sOtherTxt;
//STRIP001     String sOtherTxtReading;
//STRIP001     rCmpBase.GetTxt( sOtherTxt, sOtherTxtReading );
//STRIP001
//STRIP001     return GetLevel() == rCmpBase.GetLevel() &&
//STRIP001            pTOXIntl->IsEqual( sMyTxt, sMyTxtReading, GetLocale(),
//STRIP001                               sOtherTxt, sOtherTxtReading, rCmpBase.GetLocale() );
//STRIP001 }


//STRIP001 BOOL SwTOXCustom::operator < (const SwTOXSortTabBase& rCmpBase)
//STRIP001 {
//STRIP001     String sMyTxt;
//STRIP001     String sMyTxtReading;
//STRIP001     GetTxt( sMyTxt, sMyTxtReading );
//STRIP001
//STRIP001     String sOtherTxt;
//STRIP001     String sOtherTxtReading;
//STRIP001     rCmpBase.GetTxt( sOtherTxt, sOtherTxtReading );
//STRIP001
//STRIP001     return  GetLevel() <= rCmpBase.GetLevel() &&
//STRIP001             pTOXIntl->IsLess( sMyTxt, sMyTxtReading, GetLocale(),
//STRIP001                               sOtherTxt, sOtherTxtReading, rCmpBase.GetLocale() );
//STRIP001 }


//STRIP001 USHORT SwTOXCustom::GetLevel() const
//STRIP001 {
//STRIP001  return nLev;
//STRIP001 }


//STRIP001 void SwTOXCustom::_GetText( String& rTxt, String &rTxtReading )
//STRIP001 {
//STRIP001  rTxt = aKey;
//STRIP001     /// !!!!!!!!!!!!!!
//STRIP001 }


/*--------------------------------------------------------------------
     Beschreibung: sortierter Inhaltsverz. Eintrag
 --------------------------------------------------------------------*/


//STRIP001 SwTOXContent::SwTOXContent( const SwTxtNode& rNd, const SwTxtTOXMark* pMark,
//STRIP001                      const SwTOXInternational& rIntl)
//STRIP001     : SwTOXSortTabBase( TOX_SORT_CONTENT, &rNd, pMark, &rIntl )
//STRIP001 {
//STRIP001 }


//  Der Text des Inhalts
//

//STRIP001 void SwTOXContent::_GetText( String& rTxt, String& rTxtReading )
//STRIP001 {
//STRIP001  const xub_StrLen* pEnd = pTxtMark->GetEnd();
//STRIP001  if( pEnd && !pTxtMark->GetTOXMark().IsAlternativeText() )
//STRIP001     {
//STRIP001      rTxt = ((SwTxtNode*)aTOXSources[0].pNd)->GetExpandTxt(
//STRIP001                                   *pTxtMark->GetStart(),
//STRIP001                                   *pEnd - *pTxtMark->GetStart() );
//STRIP001
//STRIP001         rTxtReading = pTxtMark->GetTOXMark().GetTextReading();
//STRIP001     }
//STRIP001  else
//STRIP001      rTxt = pTxtMark->GetTOXMark().GetAlternativeText();
//STRIP001 }

//STRIP001 void SwTOXContent::FillText( SwTxtNode& rNd, const SwIndex& rInsPos, USHORT ) const
//STRIP001 {
//STRIP001  const xub_StrLen* pEnd = pTxtMark->GetEnd();
//STRIP001  if( pEnd && !pTxtMark->GetTOXMark().IsAlternativeText() )
//STRIP001      ((SwTxtNode*)aTOXSources[0].pNd)->GetExpandTxt( rNd, &rInsPos,
//STRIP001                                  *pTxtMark->GetStart(),
//STRIP001                                  *pEnd - *pTxtMark->GetStart() );
//STRIP001  else
//STRIP001     {
//STRIP001         String sTmp, sTmpReading;
//STRIP001         GetTxt( sTmp, sTmpReading );
//STRIP001         rNd.Insert( sTmp, rInsPos );
//STRIP001     }
//STRIP001 }

//
// Die Ebene fuer Anzeige
//


//STRIP001 USHORT SwTOXContent::GetLevel() const
//STRIP001 {
//STRIP001  return pTxtMark->GetTOXMark().GetLevel();
//STRIP001 }

/*--------------------------------------------------------------------
     Beschreibung: Verzeichnis aus Absaetzen zusammengesammelt
 --------------------------------------------------------------------*/

// bei Sortierung von OLE/Grafiken aufpassen !!!
// Die Position darf nicht die im Dokument,
// sondern muss die vom "Henkel" sein  !!


//STRIP001 SwTOXPara::SwTOXPara( const SwCntntNode& rNd, SwTOXElement eT, USHORT nLevel )
//STRIP001  : SwTOXSortTabBase( TOX_SORT_PARA, &rNd, 0, 0 ),
//STRIP001  eType( eT ),
//STRIP001  m_nLevel(nLevel),
//STRIP001  nStartIndex(0),
//STRIP001  nEndIndex(STRING_LEN)
//STRIP001 {
//STRIP001 }


//STRIP001 void SwTOXPara::_GetText( String& rTxt, String& rTxtReading )
//STRIP001 {
//STRIP001  const SwCntntNode* pNd = aTOXSources[0].pNd;
//STRIP001  switch( eType )
//STRIP001  {
//STRIP001  case TOX_SEQUENCE:
//STRIP001  case TOX_TEMPLATE:
//STRIP001     case TOX_OUTLINELEVEL:
//STRIP001      {
//STRIP001          xub_StrLen nStt = nStartIndex;
//STRIP001 /* JP 22.01.98:
//STRIP001  Tabs ueberspringen - macht aber keinen Sinn, solange in der TOX-Form
//STRIP001  nicht die KapitelNummer eingestellt werden kann
//STRIP001          const String& rTmp = ((SwTxtNode*)pNd)->GetTxt();
//STRIP001          while( '\t' == rTmp.GetChar( nStt ) && nStt < rTmp.Len() )
//STRIP001              ++nStt;
//STRIP001 */
//STRIP001          rTxt = ((SwTxtNode*)pNd)->GetExpandTxt(
//STRIP001                  nStt,
//STRIP001                  STRING_NOTFOUND == nEndIndex ? STRING_LEN : nEndIndex - nStt);
//STRIP001      }
//STRIP001      break;
//STRIP001
//STRIP001  case TOX_OLE:
//STRIP001  case TOX_GRAPHIC:
//STRIP001  case TOX_FRAME:
//STRIP001      {
//STRIP001          // suche das FlyFormat, dort steht der Object/Grafik-Name
//STRIP001          SwFrmFmt* pFly = pNd->GetFlyFmt();
//STRIP001          if( pFly )
//STRIP001              rTxt = pFly->GetName();
//STRIP001          else
//STRIP001          {
//STRIP001              ASSERT( !this, "Grafik/Object ohne Namen" )
//STRIP001              USHORT nId = TOX_OLE == eType
//STRIP001                              ? STR_OBJECT_DEFNAME
//STRIP001                              : TOX_GRAPHIC == eType
//STRIP001                                  ? STR_GRAPHIC_DEFNAME
//STRIP001                                  : STR_FRAME_DEFNAME;
//STRIP001              rTxt = SW_RESSTR( nId );
//STRIP001          }
//STRIP001      }
//STRIP001      break;
//STRIP001  }
//STRIP001 }

//STRIP001 void SwTOXPara::FillText( SwTxtNode& rNd, const SwIndex& rInsPos, USHORT ) const
//STRIP001 {
//STRIP001     if( TOX_TEMPLATE == eType || TOX_SEQUENCE == eType  || TOX_OUTLINELEVEL == eType)
//STRIP001  {
//STRIP001      SwTxtNode* pSrc = (SwTxtNode*)aTOXSources[0].pNd;
//STRIP001      xub_StrLen nStt = nStartIndex;
//STRIP001 /* JP 22.01.98:
//STRIP001  Tabs ueberspringen - macht aber keinen Sinn, solange in der TOX-Form
//STRIP001  nicht die KapitelNummer eingestellt werden kann
//STRIP001      const String& rTxt = pSrc->GetTxt();
//STRIP001      while( '\t' == rTxt.GetChar( nStt ) && nStt < rTxt.Len() )
//STRIP001          ++nStt;
//STRIP001 */
//STRIP001      pSrc->GetExpandTxt( rNd, &rInsPos, nStt,
//STRIP001              nEndIndex == STRING_LEN ? STRING_LEN : nEndIndex - nStt,
//STRIP001                 FALSE, FALSE, TRUE );
//STRIP001  }
//STRIP001  else
//STRIP001     {
//STRIP001         String sTmp, sTmpReading;
//STRIP001         GetTxt( sTmp, sTmpReading );
//STRIP001          sTmp.SearchAndReplaceAll('\t', ' ');
//STRIP001         rNd.Insert( sTmp, rInsPos );
//STRIP001     }
//STRIP001 }


//STRIP001 USHORT SwTOXPara::GetLevel() const
//STRIP001 {
//STRIP001  USHORT nRet = m_nLevel;
//STRIP001  const SwCntntNode*  pNd = aTOXSources[0].pNd;
//STRIP001
//STRIP001     if( TOX_OUTLINELEVEL == eType && pNd->GetTxtNode() )
//STRIP001  {
//STRIP001      USHORT nTmp = ((SwTxtNode*)pNd)->GetTxtColl()->GetOutlineLevel();
//STRIP001      if(nTmp < NO_NUMBERING)
//STRIP001          nRet = nTmp + 1;
//STRIP001  }
//STRIP001  return nRet;
//STRIP001 }


//STRIP001 String SwTOXPara::GetURL() const
//STRIP001 {
//STRIP001  String aTxt;
//STRIP001  const SwCntntNode* pNd = aTOXSources[0].pNd;
//STRIP001  switch( eType )
//STRIP001  {
//STRIP001  case TOX_TEMPLATE:
//STRIP001     case TOX_OUTLINELEVEL:
//STRIP001      {
//STRIP001          if( MAXLEVEL >= ((SwTxtNode*)pNd)->GetTxtColl()->GetOutlineLevel())
//STRIP001          {
//STRIP001              aTxt = '#';
//STRIP001              const SwNodeNum* pNum = ((SwTxtNode*)pNd)->GetOutlineNum();
//STRIP001              if( pNum && pNd->GetDoc()->GetOutlineNumRule() )
//STRIP001              {
//STRIP001                  // dann noch die rel. Nummer davor setzen
//STRIP001                  const SwNumRule& rRule = *pNd->GetDoc()->GetOutlineNumRule();
//STRIP001                  const USHORT nCurrLevel = pNum->GetLevel();
//STRIP001                     if(nCurrLevel <= MAXLEVEL)
//STRIP001                      for( int n = 0; n <= nCurrLevel; ++n )
//STRIP001                  {
//STRIP001                      int nNum = pNum->GetLevelVal()[ n ];
//STRIP001                      nNum -= ( rRule.Get( n ).GetStart() - 1 );
//STRIP001                      ( aTxt += String::CreateFromInt32( nNum )) += '.';
//STRIP001                  }
//STRIP001              }
//STRIP001              aTxt += ((SwTxtNode*)pNd)->GetExpandTxt();
//STRIP001              ( aTxt += cMarkSeperator ).AppendAscii( pMarkToOutline );
//STRIP001          }
//STRIP001      }
//STRIP001      break;
//STRIP001
//STRIP001  case TOX_OLE:
//STRIP001  case TOX_GRAPHIC:
//STRIP001  case TOX_FRAME:
//STRIP001      {
//STRIP001          // suche das FlyFormat, dort steht der Object/Grafik-Name
//STRIP001          SwFrmFmt* pFly = pNd->GetFlyFmt();
//STRIP001          if( pFly )
//STRIP001          {
//STRIP001              (( aTxt = '#' ) += pFly->GetName() ) += cMarkSeperator;
//STRIP001              const sal_Char* pStr;
//STRIP001              switch( eType )
//STRIP001              {
//STRIP001              case TOX_OLE:       pStr = pMarkToOLE; break;
//STRIP001              case TOX_GRAPHIC:   pStr = pMarkToGraphic; break;
//STRIP001              case TOX_FRAME:     pStr = pMarkToFrame; break;
//STRIP001              default:            pStr = 0;
//STRIP001              }
//STRIP001              if( pStr )
//STRIP001                  aTxt.AppendAscii( pStr );
//STRIP001          }
//STRIP001      }
//STRIP001      break;
//STRIP001  }
//STRIP001  return aTxt;
//STRIP001 }


/*--------------------------------------------------------------------
    Beschreibung: Tabelle
 --------------------------------------------------------------------*/


//STRIP001 SwTOXTable::SwTOXTable( const SwCntntNode& rNd )
//STRIP001  : SwTOXSortTabBase( TOX_SORT_TABLE, &rNd, 0, 0 ),
//STRIP001  nLevel(FORM_ALPHA_DELIMITTER)
//STRIP001 {
//STRIP001 }


//STRIP001 void SwTOXTable::_GetText( String& rTxt, String& rTxtReading )
//STRIP001 {
//STRIP001  const SwNode* pNd = aTOXSources[0].pNd;
//STRIP001  if( pNd && 0 != ( pNd = pNd->FindTableNode() ) )
//STRIP001  {
//STRIP001      rTxt = ((SwTableNode*)pNd)->GetTable().GetFrmFmt()->GetName();
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      ASSERT( !this, "Wo ist meine Tabelle geblieben?" )
//STRIP001      rTxt = SW_RESSTR( STR_TABLE_DEFNAME );
//STRIP001  }
//STRIP001 }

//STRIP001 USHORT SwTOXTable::GetLevel() const
//STRIP001 {
//STRIP001  return nLevel;
//STRIP001 }


//STRIP001 String SwTOXTable::GetURL() const
//STRIP001 {
//STRIP001  String aTxt;
//STRIP001  const SwNode* pNd = aTOXSources[0].pNd;
//STRIP001  if( pNd && 0 != ( pNd = pNd->FindTableNode() ) )
//STRIP001  {
//STRIP001      aTxt = ((SwTableNode*)pNd)->GetTable().GetFrmFmt()->GetName();
//STRIP001      if( aTxt.Len() )
//STRIP001      {
//STRIP001          ( aTxt.Insert( '#', 0 ) += cMarkSeperator ).
//STRIP001                                          AppendAscii( pMarkToTable );
//STRIP001      }
//STRIP001  }
//STRIP001  return aTxt;
//STRIP001 }
/*-- 15.09.99 14:28:08---------------------------------------------------

  -----------------------------------------------------------------------*/

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
/*-- 15.09.99 14:28:08---------------------------------------------------

  -----------------------------------------------------------------------*/
void SwTOXAuthority::_GetText( String& rTxt, String& rTxtReading )
{
    //
    rTxt = m_rField.GetFld()->Expand();
}

/* -----------------21.09.99 12:50-------------------

 --------------------------------------------------*/
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
/* -----------------14.10.99 09:35-------------------

 --------------------------------------------------*/
BOOL    SwTOXAuthority::operator==( const SwTOXSortTabBase& rCmp)
{
    return nType == rCmp.nType &&
            ((SwAuthorityField*)m_rField.GetFld())->GetHandle() ==
                ((SwAuthorityField*)((SwTOXAuthority&)rCmp).m_rField.GetFld())->GetHandle();
}
/* -----------------21.10.99 09:52-------------------

 --------------------------------------------------*/
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
