/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_doctxm.cxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 22:25:32 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/


#pragma hdrstop

#include <limits.h>

#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif

#define _SVSTDARR_STRINGSSORT

#ifndef _SWDOCSH_HXX
#include <docsh.hxx>
#endif

#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif

#ifndef _FMTINFMT_HXX
#include <fmtinfmt.hxx>
#endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>
#endif
#ifndef _DOCTXM_HXX
#include <doctxm.hxx>
#endif
#ifndef _TXMSRT_HXX
#include <txmsrt.hxx>
#endif
#ifndef _POOLFMT_HXX
#include <poolfmt.hxx>
#endif
#ifndef _ROOTFRM_HXX
#include <rootfrm.hxx>
#endif
#ifndef _SWUNDO_HXX
#include <swundo.hxx>
#endif
#ifndef _DOCARY_HXX
#include <docary.hxx>
#endif
#ifndef _TXTFLD_HXX
#include <txtfld.hxx>
#endif
#ifndef _CHPFLD_HXX
#include <chpfld.hxx>
#endif
namespace binfilter {

const sal_Unicode cNumRepl      = '@';
const sal_Unicode cEndPageNum   = '~';
const sal_Char __FAR_DATA sPageDeli[] = ", ";

/*N*/ SV_IMPL_PTRARR(SwTOXSortTabBases, SwTOXSortTabBasePtr)

/*N*/ TYPEINIT2( SwTOXBaseSection, SwTOXBase, SwSection );  // fuers RTTI

struct LinkStruct
{
    SwFmtINetFmt    aINetFmt;
    xub_StrLen nStartTextPos, nEndTextPos;

    LinkStruct( const String& rURL, xub_StrLen nStart, xub_StrLen nEnd )
        : aINetFmt( rURL, aEmptyStr),
        nStartTextPos( nStart),
        nEndTextPos(nEnd) {}
};

typedef LinkStruct* LinkStructPtr;


/*--------------------------------------------------------------------
     Beschreibung: aktuelle Verzeichnismarkierungen ermitteln
 --------------------------------------------------------------------*/


/*N*/ USHORT SwDoc::GetCurTOXMark( const SwPosition& rPos,
/*N*/                               SwTOXMarks& rArr ) const
/*N*/ {
/*N*/   // suche an der Position rPos nach allen SwTOXMark's
/*N*/   SwTxtNode* pTxtNd = GetNodes()[ rPos.nNode ]->GetTxtNode();
/*N*/   // kein TextNode oder kein HintsArray vorhanden ??
/*N*/   if( !pTxtNd || !pTxtNd->GetpSwpHints() )
/*N*/       return 0;
/*N*/
/*N*/   const SwpHints & rHts = *pTxtNd->GetpSwpHints();
/*N*/   const SwTxtAttr* pHt;
/*N*/   xub_StrLen nSttIdx;
/*N*/   const xub_StrLen *pEndIdx;
/*N*/
/*N*/   xub_StrLen nAktPos = rPos.nContent.GetIndex();
/*N*/
/*N*/   for( USHORT n = 0; n < rHts.Count(); ++n )
/*N*/   {
/*N*/       if( RES_TXTATR_TOXMARK != (pHt = rHts[n])->Which() )
/*N*/           continue;
/*N*/       if( ( nSttIdx = *pHt->GetStart() ) < nAktPos )
/*N*/       {
/*N*/           // pruefe Ende mit ab
/*N*/           if( 0 == ( pEndIdx = pHt->GetEnd() ) ||
/*N*/               *pEndIdx <= nAktPos )
/*N*/               continue;       // weiter suchen
/*N*/       }
/*N*/       else if( nSttIdx > nAktPos )
/*N*/           // ist Start vom Hint groesser als rPos, dann abbrechen. Denn
/*N*/           // die Attribute sind nach Start sortiert !
/*N*/           break;
/*N*/
/*?*/       const SwTOXMark* pTMark = &pHt->GetTOXMark();
/*?*/       rArr.Insert( pTMark, rArr.Count() );
/*N*/   }
/*N*/   return rArr.Count();
/*N*/ }

/*--------------------------------------------------------------------
     Beschreibung: Marke loeschen
 --------------------------------------------------------------------*/

/*N*/ void SwDoc::Delete( SwTOXMark* pTOXMark )
/*N*/ {
DBG_BF_ASSERT(0, "STRIP"); //STRIP001   // hole den TextNode und
/*N*/ }

/*--------------------------------------------------------------------
     Beschreibung: Traveln zwischen TOXMarks
 --------------------------------------------------------------------*/



/*  */

/*N*/ const SwTOXBaseSection* SwDoc::InsertTableOf( const SwPosition& rPos,
/*N*/                                               const SwTOXBase& rTOX,
/*N*/                                               const SfxItemSet* pSet,
/*N*/                                               BOOL bExpand )
/*N*/ {
/*N*/   StartUndo( UNDO_INSTOX );
/*N*/
/*N*/   SwTOXBaseSection* pNew = new SwTOXBaseSection( rTOX );
/*N*/   String sSectNm( rTOX.GetTOXName() );
/*N*/   sSectNm = GetUniqueTOXBaseName( *rTOX.GetTOXType(), &sSectNm );
/*N*/   pNew->SetTOXName(sSectNm);
/*N*/   pNew->SwSection::SetName(sSectNm);
/*N*/   SwPaM aPam( rPos );
/*N*/   SwSection* pSect = Insert( aPam, *pNew, pSet, FALSE );
/*N*/   if( pSect )
/*N*/   {
/*N*/       SwSectionNode* pSectNd = pSect->GetFmt()->GetSectionNode();
/*N*/       SwSection* pCl = pNew;
/*N*/       pSect->GetFmt()->Add( pCl );
/*N*/       pSectNd->SetNewSection( pNew );
/*N*/
/*N*/       if( bExpand )
/*N*/         {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/         }
/*N*/       else if( 1 == rTOX.GetTitle().Len() && IsInReading() )
/*N*/       // insert title of TOX
/*N*/       {
/*?*/           // then insert the headline section
/*?*/           SwNodeIndex aIdx( *pSectNd, +1 );
/*?*/
/*?*/           SwTxtNode* pHeadNd = GetNodes().MakeTxtNode( aIdx,
/*?*/                           GetTxtCollFromPool( RES_POOLCOLL_STANDARD ) );
/*?*/
/*?*/           String sNm( pNew->GetTOXName() );
/*?*/ // ??Resource
/*?*/ sNm.AppendAscii( RTL_CONSTASCII_STRINGPARAM( "_Head" ));
/*?*/
/*?*/           SwSection aSect( TOX_HEADER_SECTION, sNm );
/*?*/
/*?*/           SwNodeIndex aStt( *pHeadNd ); aIdx--;
/*?*/           SwSectionFmt* pSectFmt = MakeSectionFmt( 0 );
/*?*/           GetNodes().InsertSection( aStt, *pSectFmt, aSect, &aIdx,
/*?*/                                               TRUE, FALSE );
/*?*/       }
/*N*/   }
/*N*/   else
/*?*/       delete pNew, pNew = 0;

/*N*/   EndUndo( UNDO_INSTOX );
/*N*/
/*N*/   return pNew;
/*N*/ }



/*N*/ const SwTOXBaseSection* SwDoc::InsertTableOf( ULONG nSttNd, ULONG nEndNd,
/*N*/                                               const SwTOXBase& rTOX,
/*N*/                                               const SfxItemSet* pSet )
/*N*/ {
/*N*/   // check for recursiv TOX
/*N*/   SwNode* pNd = GetNodes()[ nSttNd ];
/*N*/   SwSectionNode* pSectNd = pNd->FindSectionNode();
/*N*/   while( pSectNd )
/*N*/   {
/*?*/       SectionType eT = pSectNd->GetSection().GetType();
/*?*/       if( TOX_HEADER_SECTION == eT || TOX_CONTENT_SECTION == eT )
/*?*/           return 0;
/*?*/       pSectNd = pSectNd->FindStartNode()->FindSectionNode();
/*N*/   }
/*N*/
/*N*/   // create SectionNode around the Nodes
/*N*/   SwTOXBaseSection* pNew = new SwTOXBaseSection( rTOX );
/*N*/
/*N*/   String sSectNm( rTOX.GetTOXName() );
/*N*/   sSectNm = GetUniqueTOXBaseName(*rTOX.GetTOXType(), &sSectNm);
/*N*/   pNew->SetTOXName(sSectNm);
/*N*/   pNew->SwSection::SetName(sSectNm);
/*N*/
/*N*/   SwNodeIndex aStt( GetNodes(), nSttNd ), aEnd( GetNodes(), nEndNd );
/*N*/   SwSectionFmt* pFmt = MakeSectionFmt( 0 );
/*N*/   if(pSet)
/*?*/       pFmt->SetAttr(*pSet);
/*N*/
/*N*/ //    --aEnd;     // im InsertSection ist Ende inclusive
/*N*/
/*N*/   pSectNd = GetNodes().InsertSection( aStt, *pFmt, *pNew, &aEnd );
/*N*/   if( pSectNd )
/*N*/   {
/*N*/       SwSection* pCl = pNew;
/*N*/       pFmt->Add( pCl );
/*N*/       pSectNd->SetNewSection( pNew );
/*N*/   }
/*N*/   else
/*N*/   {
/*?*/       delete pNew, pNew = 0;
/*?*/       DelSectionFmt( pFmt );
/*N*/   }
/*N*/
/*N*/   return pNew;
/*N*/ }

/*--------------------------------------------------------------------
     Beschreibung: Aktuelles Verzeichnis ermitteln
 --------------------------------------------------------------------*/

/*N*/ const SwTOXBase* SwDoc::GetCurTOX( const SwPosition& rPos ) const
/*N*/ {
/*N*/   const SwNode& rNd = rPos.nNode.GetNode();
/*N*/   const SwSectionNode* pSectNd = rNd.FindSectionNode();
/*N*/   while( pSectNd )
/*N*/   {
/*N*/       SectionType eT = pSectNd->GetSection().GetType();
/*N*/       if( TOX_CONTENT_SECTION == eT )
/*N*/       {
/*N*/           ASSERT( pSectNd->GetSection().ISA( SwTOXBaseSection ),
/*N*/                   "keine TOXBaseSection!" );
/*N*/           SwTOXBaseSection& rTOXSect = (SwTOXBaseSection&)
/*N*/                                               pSectNd->GetSection();
/*N*/           return &rTOXSect;
/*N*/       }
/*?*/       pSectNd = pSectNd->FindStartNode()->FindSectionNode();
/*N*/   }
/*N*/   return 0;
/*N*/ }
/* -----------------01.09.99 16:01-------------------

 --------------------------------------------------*/
/*N*/ const SwAttrSet& SwDoc::GetTOXBaseAttrSet(const SwTOXBase& rTOXBase) const
/*N*/ {
/*N*/   ASSERT( rTOXBase.ISA( SwTOXBaseSection ), "no TOXBaseSection!" );
/*N*/   const SwTOXBaseSection& rTOXSect = (const SwTOXBaseSection&)rTOXBase;
/*N*/   SwSectionFmt* pFmt = rTOXSect.GetFmt();
/*N*/   ASSERT( pFmt, "invalid TOXBaseSection!" );
/*N*/   return pFmt->GetAttrSet();
/*N*/ }
/* -----------------02.09.99 07:48-------------------

 --------------------------------------------------*/
/* -----------------02.09.99 08:06-------------------

 --------------------------------------------------*/

/*--------------------------------------------------------------------
     Beschreibung: Verzeichnis loeschen
 --------------------------------------------------------------------*/


/*N*/ BOOL SwDoc::DeleteTOX( const SwTOXBase& rTOXBase, BOOL bDelNodes )
/*N*/ {
/*N*/  DBG_BF_ASSERT(0, "STRIP"); return TRUE;//STRIP001    // its only delete the TOX, not the nodes
/*N*/ }

/*--------------------------------------------------------------------
     Beschreibung:  Verzeichnistypen verwalten
 --------------------------------------------------------------------*/

/*N*/ USHORT SwDoc::GetTOXTypeCount(TOXTypes eTyp) const
/*N*/ {
/*N*/   const SwTOXTypePtr * ppTTypes = pTOXTypes->GetData();
/*N*/   USHORT nCnt = 0;
/*N*/   for( USHORT n = 0; n < pTOXTypes->Count(); ++n, ++ppTTypes )
/*N*/       if( eTyp == (*ppTTypes)->GetType() )
/*N*/           ++nCnt;
/*N*/   return nCnt;
/*N*/ }
/*--------------------------------------------------------------------

 --------------------------------------------------------------------*/
/*N*/ const SwTOXType* SwDoc::GetTOXType( TOXTypes eTyp, USHORT nId ) const
/*N*/ {
/*N*/   const SwTOXTypePtr * ppTTypes = pTOXTypes->GetData();
/*N*/   USHORT nCnt = 0;
/*N*/   for( USHORT n = 0; n < pTOXTypes->Count(); ++n, ++ppTTypes )
/*N*/       if( eTyp == (*ppTTypes)->GetType() && nCnt++ == nId )
/*N*/           return (*ppTTypes);
/*N*/   return 0;
/*N*/ }

#ifdef USED



#endif

/*--------------------------------------------------------------------

 --------------------------------------------------------------------*/
/*N*/ const SwTOXType* SwDoc::InsertTOXType( const SwTOXType& rTyp )
/*N*/ {
/*N*/   SwTOXType * pNew = new SwTOXType( rTyp );
/*N*/   pTOXTypes->Insert( pNew, pTOXTypes->Count() );
/*N*/   return pNew;
/*N*/ }
/*--------------------------------------------------------------------

 --------------------------------------------------------------------*/
/*N*/ String SwDoc::GetUniqueTOXBaseName( const SwTOXType& rType,
/*N*/                                   const String* pChkStr ) const
/*N*/ {
/*N*/   if(pChkStr && !pChkStr->Len())
/*N*/       pChkStr = 0;
/*N*/   String aName( rType.GetTypeName() );
/*N*/   xub_StrLen nNmLen = aName.Len();
/*N*/
/*N*/   USHORT nNum, nTmp, nFlagSize = ( pSectionFmtTbl->Count() / 8 ) +2;
/*N*/   BYTE* pSetFlags = new BYTE[ nFlagSize ];
/*N*/   memset( pSetFlags, 0, nFlagSize );
/*N*/
/*N*/   const SwSectionNode* pSectNd;
/*N*/   const SwSection* pSect;
        USHORT n=0;
/*N*/   for( n = 0; n < pSectionFmtTbl->Count(); ++n )
/*N*/       if( 0 != ( pSectNd = (*pSectionFmtTbl)[ n ]->GetSectionNode( FALSE ) )&&
/*N*/            TOX_CONTENT_SECTION == (pSect = &pSectNd->GetSection())->GetType())
/*N*/       {
/*N*/           const String& rNm = pSect->GetName();
/*N*/           if( rNm.Match( aName ) == nNmLen )
/*N*/           {
/*N*/               // Nummer bestimmen und das Flag setzen
/*N*/               nNum = (USHORT)rNm.Copy( nNmLen ).ToInt32();
/*N*/               if( nNum-- && nNum < pSectionFmtTbl->Count() )
/*N*/                   pSetFlags[ nNum / 8 ] |= (0x01 << ( nNum & 0x07 ));
/*N*/           }
/*N*/           if( pChkStr && pChkStr->Equals( rNm ) )
/*N*/               pChkStr = 0;
/*N*/       }
/*N*/
/*N*/   if( !pChkStr )
/*N*/   {
/*N*/       // alle Nummern entsprechend geflag, also bestimme die richtige Nummer
/*N*/       nNum = pSectionFmtTbl->Count();
/*N*/       for( n = 0; n < nFlagSize; ++n )
/*N*/           if( 0xff != ( nTmp = pSetFlags[ n ] ))
/*N*/           {
/*N*/               // also die Nummer bestimmen
/*N*/               nNum = n * 8;
/*N*/               while( nTmp & 1 )
/*N*/                   ++nNum, nTmp >>= 1;
/*N*/               break;
/*N*/           }
/*N*/   }
/*N*/   delete [] pSetFlags;
/*N*/   if( pChkStr )
/*N*/       return *pChkStr;
/*N*/   return aName += String::CreateFromInt32( ++nNum );
/*N*/ }

/*--------------------------------------------------------------------

 --------------------------------------------------------------------*/
/*N*/ BOOL SwDoc::SetTOXBaseName(const SwTOXBase& rTOXBase, const String& rName)
/*N*/ {
/*N*/   ASSERT( rTOXBase.ISA( SwTOXBaseSection ),
/*N*/                   "keine TOXBaseSection!" );
/*N*/   SwTOXBaseSection* pTOX = (SwTOXBaseSection*)&rTOXBase;
/*N*/
/*N*/   String sTmp = GetUniqueTOXBaseName(*rTOXBase.GetTOXType(), &rName);
/*N*/   BOOL bRet = sTmp == rName;
/*N*/   if(bRet)
/*N*/   {
/*?*/       pTOX->SetTOXName(rName);
/*?*/       pTOX->SwTOXBaseSection::SetName(rName);
/*?*/       SetModified();
/*N*/   }
/*N*/   return bRet;
/*N*/ }
/*--------------------------------------------------------------------

 --------------------------------------------------------------------*/


/*  */



/*--------------------------------------------------------------------
     Beschreibung: Verzeichnis-Klasse
 --------------------------------------------------------------------*/

/*N*/ SwTOXBaseSection::SwTOXBaseSection( const SwTOXBase& rBase )
/*N*/   : SwTOXBase( rBase ), SwSection( TOX_CONTENT_SECTION, aEmptyStr )
/*N*/ {
/*N*/   SetProtect( rBase.IsProtected() );
/*N*/   SwSection::SetName( GetTOXName() );
/*N*/ }


/*N*/ SwTOXBaseSection::~SwTOXBaseSection()
/*N*/ {
/*N*/ }



/*--------------------------------------------------------------------
     Beschreibung: Verzeichnisinhalt zusammensammeln
 --------------------------------------------------------------------*/

/*N*/ void SwTOXBaseSection::Update(const SfxItemSet* pAttr,
/*N*/                               const bool        _bNewTOX )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/ }

/*--------------------------------------------------------------------
     Beschreibung: AlphaDelimitter einfuegen
 --------------------------------------------------------------------*/



/*--------------------------------------------------------------------
     Beschreibung: Template  auswerten
 --------------------------------------------------------------------*/



/*--------------------------------------------------------------------
     Beschreibung: Aus Markierungen erzeugen
 --------------------------------------------------------------------*/



/*--------------------------------------------------------------------
     Beschreibung:  Verzeichnisinhalt aus Gliederungsebene generieren
 --------------------------------------------------------------------*/



/*--------------------------------------------------------------------
     Beschreibung: Verzeichnisinhalt aus Vorlagenbereichen generieren
 --------------------------------------------------------------------*/


/* -----------------14.07.99 09:59-------------------
    Description: generate content from sequence fields
 --------------------------------------------------*/
/* -----------------15.09.99 14:18-------------------

 --------------------------------------------------*/

/*--------------------------------------------------------------------
     Beschreibung:  Verzeichnisinhalt aus Inhaltsformen generieren
                    OLE, Grafik, Frame
                    Achtung: Spezielle Section !
 --------------------------------------------------------------------*/
/*
            nPos = pNd->GetIndex();
            if( nPos < pNd->GetNodes().GetEndOfExtras().GetIndex() )
            {
                // dann die "Anker" (Body) Position holen.
                Point aPt;
                const SwCntntFrm* pFrm = pNd->GetFrm( &aPt, 0, FALSE );
                if( pFrm )
                {
                    SwPosition aPos( *pNd );
                    SwDoc* pDoc = (SwDoc*)pNd->GetDoc();
#ifndef PRODUCT
                    ASSERT( GetBodyTxtNode( pDoc, aPos, pFrm ),
                            "wo steht der Absatz" );
#else
                    GetBodyTxtNode( pDoc, aPos, pFrm );
#endif
                    nPos = aPos.nNode.GetIndex();
                    nCntPos = aPos.nContent.GetIndex();
                }
            }



 */



/*--------------------------------------------------------------------
     Beschreibung:  Tabelleneintraege zusammensuchen
 --------------------------------------------------------------------*/


/*--------------------------------------------------------------------
     Beschreibung:  String generieren anhand der Form
                    SonderZeichen 0-31 und 255 entfernen
 --------------------------------------------------------------------*/


// OD 18.03.2003 #106329# - add parameter <_TOXSectNdIdx> and <_pDefaultPageDesc>
// in order to control, which page description is used, no appropriate one is found.

/*--------------------------------------------------------------------
     Beschreibung: Seitennummer errechnen und nach dem Formatieren
                   eintragen
 --------------------------------------------------------------------*/

/*N*/ void SwTOXBaseSection::UpdatePageNum()
/*N*/ {
/*N*/   if( !aSortArr.Count() )
/*N*/       return ;

    // die aktuellen Seitennummern ins Verzeichnis eintragen
/*?*/   SwPageFrm*  pAktPage    = 0;
/*?*/   USHORT      nPage       = 0;
/*?*/   SwDoc* pDoc = (SwDoc*)GetFmt()->GetDoc();
/*?*/
/*?*/     SwTOXInternational aIntl( GetLanguage(),
/*?*/                               TOX_INDEX == GetTOXType()->GetType() ?
/*?*/                               GetOptions() : 0,
/*?*/                               GetSortAlgorithm() );
/*?*/
/*?*/   for( USHORT nCnt = 0; nCnt < aSortArr.Count(); ++nCnt )
/*?*/   {
/*?*/   }
/*?*/   // nach dem Setzen der richtigen Seitennummer, das Mapping-Array
/*?*/   // wieder loeschen !!
/*?*/   aSortArr.DeleteAndDestroy( 0, aSortArr.Count() );
/*N*/ }


/*--------------------------------------------------------------------
     Beschreibung: Austausch der Seitennummer-Platzhalter
 --------------------------------------------------------------------*/

// search for the page no in the array of main entry page numbers



/*--------------------------------------------------------------------
     Beschreibung: Sortiert einfuegen in das SortArr
 --------------------------------------------------------------------*/


/*--------------------------------------------------------------------
     Beschreibung: Schluessel-Bereich suchen und evtl einfuegen
 --------------------------------------------------------------------*/



/*N*/ BOOL SwTOXBase::IsTOXBaseInReadonly() const
/*N*/ {
/*N*/   const SwTOXBaseSection *pSect = PTR_CAST(SwTOXBaseSection, this);
/*N*/   BOOL bRet = FALSE;
/*N*/   const SwSectionNode* pSectNode;
/*N*/   if(pSect && pSect->GetFmt() &&
/*N*/           0 != (pSectNode = pSect->GetFmt()->GetSectionNode()))
/*N*/   {
/*N*/       const SwDocShell* pDocSh;
/*N*/       bRet = (0 != (pDocSh = pSectNode->GetDoc()->GetDocShell()) &&
/*N*/                                                   pDocSh->IsReadOnly()) ||
/*N*/           (0 != (pSectNode = pSectNode->FindStartNode()->FindSectionNode())&&
/*N*/                   pSectNode->GetSection().IsProtectFlag());
/*N*/
/*N*/   }
/*N*/   return bRet;
/*N*/ }
/* -----------------17.08.99 13:29-------------------

 --------------------------------------------------*/



/*  */


}
