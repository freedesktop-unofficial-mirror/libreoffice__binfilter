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

#include <com/sun/star/text/ChapterFormat.hpp>

#include <horiornt.hxx>

#include <doc.hxx>
#include <frame.hxx>        // SwChapterFieldType::ChangeExpansion()
#include <ndtxt.hxx>
#include <chpfld.hxx>
#include <expfld.hxx>       // fuer GetBodyTxtNode
#include <unofldmid.h>
namespace binfilter {

using namespace ::com::sun::star;

/*--------------------------------------------------------------------
    Beschreibung: SwChapterFieldType
 --------------------------------------------------------------------*/


/*N*/ SwChapterFieldType::SwChapterFieldType()
/*N*/   : SwFieldType( RES_CHAPTERFLD )
/*N*/ {
/*N*/ }


SwFieldType* SwChapterFieldType::Copy() const
{
    return new SwChapterFieldType();
}


/*--------------------------------------------------------------------
    Beschreibung: Kapittelfeld
 --------------------------------------------------------------------*/


/*N*/ SwChapterField::SwChapterField(SwChapterFieldType* pTyp, sal_uInt32 nFmt)
/*N*/   : SwField(pTyp, nFmt), nLevel( 0 )
/*N*/ {}


/*N*/ String SwChapterField::Expand() const
/*N*/ {
/*N*/   String sStr( sNumber );
/*N*/   switch( GetFormat() )
/*N*/   {
/*N*/       case CF_TITLE:      sStr = sTitle;  break;
/*N*/
/*N*/       case CF_NUMBER:
/*N*/       case CF_NUM_TITLE:  sStr.Insert( sPre, 0 );
/*N*/                           sStr += sPost;
/*N*/                           if( CF_NUM_TITLE == GetFormat() )
/*N*/                               sStr += sTitle;
/*N*/                           break;
/*N*/
/*?*/       case CF_NUM_NOPREPST_TITLE: sStr += sTitle; break;
/*N*/   }
/*N*/   return sStr;
/*N*/ }


/*N*/ SwField* SwChapterField::Copy() const
/*N*/ {
/*N*/   SwChapterField *pTmp =
/*N*/       new SwChapterField((SwChapterFieldType*)GetTyp(), GetFormat());
/*N*/   pTmp->nLevel = nLevel;
/*N*/   pTmp->sTitle = sTitle;
/*N*/   pTmp->sNumber = sNumber;
/*N*/   pTmp->sPost = sPost;
/*N*/   pTmp->sPre = sPre;
/*N*/
/*N*/   return pTmp;
/*N*/ }


/*N*/ void SwChapterField::ChangeExpansion( const SwFrm* pFrm,
/*N*/                                     const SwTxtNode* pTxtNd,
/*N*/                                     sal_Bool bSrchNum )
/*N*/ {
/*N*/   OSL_ENSURE( pFrm, "in welchem Frame stehe ich denn?" );
/*N*/   SwDoc* pDoc = (SwDoc*)pTxtNd->GetDoc();
/*N*/   SwPosition aPos( pDoc->GetNodes().GetEndOfContent() );
/*N*/
/*N*/   if( pFrm->IsInDocBody() )
/*N*/       aPos.nNode = *pTxtNd;
/*N*/   else if( 0 == (pTxtNd = GetBodyTxtNode( *pDoc, aPos, *pFrm )) )
/*N*/       // kein TxtNode (Formatierung Kopf/Fusszeile)
/*?*/       return;
/*N*/
/*N*/   OSL_ENSURE( pTxtNd, "Wo steht das Feld" );
/*N*/   pTxtNd = pTxtNd->FindOutlineNodeOfLevel( nLevel );
/*N*/   if( pTxtNd )
/*N*/   {
/*N*/       if( bSrchNum )
/*N*/       {
/*N*/           const SwTxtNode* pONd = pTxtNd;
/*N*/           do {
/*N*/               if( pONd && pONd->GetTxtColl() )
/*N*/               {
/*N*/                   BYTE nPrevLvl = nLevel;
/*N*/                   nLevel = GetRealLevel( pONd->GetTxtColl()->
/*N*/                                           GetOutlineLevel() );
/*N*/                   if( nPrevLvl < nLevel )
/*?*/                       nLevel = nPrevLvl;
/*N*/                   else if( SVX_NUM_NUMBER_NONE != pDoc->GetOutlineNumRule()
/*N*/                           ->Get( nLevel ).GetNumberingType() )
/*N*/                   {
/*?*/                       pTxtNd = pONd;
/*?*/                       break;
/*N*/                   }
/*N*/
/*N*/                   if( !nLevel-- )
/*N*/                       break;
/*N*/                   pONd = pTxtNd->FindOutlineNodeOfLevel( nLevel );
/*N*/               }
/*N*/               else
/*?*/                   break;
/*N*/           } while( sal_True );
/*N*/       }
/*N*/
/*N*/       const SwNodeNum& rNum = *pTxtNd->GetOutlineNum();
/*N*/       // nur die Nummer besorgen, ohne Pre-/Post-fixstrings
/*N*/       sNumber = pDoc->GetOutlineNumRule()->MakeNumString( rNum, sal_False );
/*N*/
/*N*/       if( NO_NUM > rNum.GetLevel() && !( NO_NUMLEVEL & rNum.GetLevel() ) )
/*N*/       {
/*N*/           const SwNumFmt& rNFmt = pDoc->GetOutlineNumRule()->Get( rNum.GetLevel() );
/*N*/           sPost = rNFmt.GetSuffix();
/*N*/           sPre = rNFmt.GetPrefix();
/*N*/       }
/*N*/       else
/*?*/           sPost = aEmptyStr, sPre = aEmptyStr;
/*N*/
/*N*/       sTitle = pTxtNd->GetExpandTxt();
/*N*/
/*N*/       for( xub_StrLen i = 0; i < sTitle.Len(); ++i )
/*N*/           if( ' ' > sTitle.GetChar( i ) )
/*?*/               sTitle.Erase( i--, 1 );
/*N*/   }
/*N*/   else
/*N*/   {
/*?*/       sNumber = aEmptyStr;
/*?*/       sTitle = aEmptyStr;
/*?*/       sPost = aEmptyStr;
/*?*/       sPre = aEmptyStr;
/*N*/   }
/*N*/ }


/*N*/ BOOL SwChapterField::QueryValue( ::com::sun::star::uno::Any& rAny, BYTE nMId ) const
/*N*/ {
/*N*/     nMId &= ~CONVERT_TWIPS;
/*N*/   switch( nMId )
/*N*/   {
/*N*/   case FIELD_PROP_BYTE1:
/*N*/       rAny <<= (sal_Int8)nLevel;
/*N*/       break;
/*N*/
/*N*/   case FIELD_PROP_USHORT1:
/*N*/       {
/*N*/           sal_Int16 nRet;
/*N*/           switch( GetFormat() )
/*N*/           {
/*N*/               case CF_NUMBER: nRet = text::ChapterFormat::NUMBER; break;
/*N*/               case CF_TITLE:  nRet = text::ChapterFormat::NAME; break;
/*N*/               case CF_NUMBER_NOPREPST:
/*N*/                   nRet = text::ChapterFormat::DIGIT;
/*N*/               break;
/*N*/               case CF_NUM_NOPREPST_TITLE:
/*?*/                   nRet = text::ChapterFormat::NO_PREFIX_SUFFIX;
/*?*/               break;
/*N*/               case CF_NUM_TITLE:
/*N*/               default:        nRet = text::ChapterFormat::NAME_NUMBER;
/*N*/           }
/*N*/           rAny <<= nRet;
/*N*/       }
/*N*/       break;
/*N*/
/*N*/   default:
/*?*/       OSL_FAIL("illegal property");
/*N*/   }
/*N*/   return sal_True;
/*N*/ }

BOOL SwChapterField::PutValue( const ::com::sun::star::uno::Any& rAny, BYTE nMId )
{
    BOOL bRet = TRUE;
    nMId &= ~CONVERT_TWIPS;

    switch( nMId )
    {
    case FIELD_PROP_BYTE1:
        {
            sal_Int8 nTmp(0);
            rAny >>= nTmp;
            if(nTmp >= 0 && nTmp < MAXLEVEL)
                nLevel = nTmp;
            else
                bRet = FALSE;
        }
        break;

    case FIELD_PROP_USHORT1:
        {
            sal_Int16 nVal(0);
            rAny >>= nVal;
            switch( nVal )
            {
            case text::ChapterFormat::NAME:             SetFormat(CF_TITLE); break;
            case text::ChapterFormat::NUMBER:           SetFormat(CF_NUMBER); break;
            case text::ChapterFormat::NO_PREFIX_SUFFIX: SetFormat(CF_NUM_NOPREPST_TITLE); break;
            case text::ChapterFormat::DIGIT:            SetFormat(CF_NUMBER_NOPREPST); break;
            default:                                    SetFormat(CF_NUM_TITLE);
            }
        }
        break;

    default:
        OSL_FAIL("illegal property");
        bRet = FALSE;
    }
    return bRet;
}

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
