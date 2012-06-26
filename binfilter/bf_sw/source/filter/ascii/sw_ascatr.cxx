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

#include <hintids.hxx>

#include <tools/stream.hxx>
#ifndef _SVSTDARR_HXX
#define _SVSTDARR_USHORTS
#endif

#include <pam.hxx>

#include <horiornt.hxx>

#include <doc.hxx>
#include <ndtxt.hxx>
#include <wrtasc.hxx>
#include <txtfld.hxx>
#include <fmtftn.hxx>
#include <fmtfld.hxx>
#include <fldbas.hxx>
#include <ftninfo.hxx>
namespace binfilter {

/*
 * Dieses File enthaelt alle Ausgabe-Funktionen des ASCII-Writers;
 * fuer alle Nodes, Attribute, Formate und Chars.
 */

class SwASC_AttrIter
{
    SwASCWriter& rWrt;
    const SwTxtNode& rNd;
    xub_StrLen nAktSwPos;

    xub_StrLen SearchNext( xub_StrLen nStartPos );

public:
    SwASC_AttrIter( SwASCWriter& rWrt, const SwTxtNode& rNd, xub_StrLen nStt );

    void NextPos()      { nAktSwPos = SearchNext( nAktSwPos + 1 ); }

    xub_StrLen WhereNext() const        { return nAktSwPos; }
    BOOL OutAttr( xub_StrLen nSwPos );
};


/*N*/ SwASC_AttrIter::SwASC_AttrIter( SwASCWriter& rWr, const SwTxtNode& rTxtNd,
/*N*/                               xub_StrLen nStt )
/*N*/   : rWrt( rWr ), rNd( rTxtNd ), nAktSwPos( 0 )
/*N*/ {
/*N*/   nAktSwPos = SearchNext( nStt + 1 );
/*N*/ }


/*N*/ xub_StrLen SwASC_AttrIter::SearchNext( xub_StrLen nStartPos )
/*N*/ {
/*N*/   register xub_StrLen nMinPos = STRING_MAXLEN;
/*N*/   const SwpHints* pTxtAttrs = rNd.GetpSwpHints();
/*N*/   if( pTxtAttrs )
/*N*/   {
/*?*/       register USHORT i;
/*?*/       register xub_StrLen nPos;
/*?*/       const xub_StrLen * pPos;
/*?*/
/*?*/ // kann noch optimiert werden, wenn ausgenutzt wird, dass die TxtAttrs
/*?*/ // nach der Anfangsposition geordnet sind. Dann muessten
/*?*/ // allerdings noch 2 Indices gemerkt werden
/*?*/       for( i = 0; i < pTxtAttrs->Count(); i++ )
/*?*/       {
/*?*/           const SwTxtAttr* pHt = (*pTxtAttrs)[i];
/*?*/           nPos = *pHt->GetStart();    // gibt erstes Attr-Zeichen
/*?*/           pPos = pHt->GetEnd();
/*?*/           if( !pPos )
/*?*/           {
/*?*/               if( nPos >= nStartPos && nPos <= nMinPos )
/*?*/                   nMinPos = nPos;
/*?*/
/*?*/               if( ( ++nPos ) >= nStartPos && nPos < nMinPos )
/*?*/                   nMinPos = nPos;
/*?*/           }
/*?*/       }
/*N*/   }
/*N*/   return nMinPos;
/*N*/ }


/*N*/ BOOL SwASC_AttrIter::OutAttr( xub_StrLen nSwPos )
/*N*/ {
/*N*/   BOOL bRet = FALSE;
/*N*/   const SwpHints* pTxtAttrs = rNd.GetpSwpHints();
/*N*/   if( pTxtAttrs )
/*N*/   {
/*?*/       register USHORT i;
/*?*/       for( i = 0; i < pTxtAttrs->Count(); i++ )
/*?*/       {
/*?*/           const SwTxtAttr* pHt = (*pTxtAttrs)[i];
/*?*/           const xub_StrLen * pEnd = pHt->GetEnd();
/*?*/           if( !pEnd && nSwPos == *pHt->GetStart() )
/*?*/           {
/*?*/               bRet = TRUE;
/*?*/               String sOut;
/*?*/               switch( pHt->Which() )
/*?*/               {
/*?*/               case RES_TXTATR_FIELD:
/*?*/                   sOut = ((SwTxtFld*)pHt)->GetFld().GetFld()->Expand();
/*?*/                   break;
/*?*/
/*?*/               case RES_TXTATR_HARDBLANK:
                        {DBG_BF_ASSERT(0, "STRIP");}
/*?*/                   break;
/*?*/
/*?*/               case RES_TXTATR_FTN:
/*?*/                   {
/*?*/                       const SwFmtFtn& rFtn = pHt->GetFtn();
/*?*/                       if( rFtn.GetNumStr().Len() )
/*?*/                           sOut = rFtn.GetNumStr();
/*?*/                       else if( rFtn.IsEndNote() )
/*?*/                           sOut = rWrt.pDoc->GetEndNoteInfo().aFmt.
/*?*/                                           GetNumStr( rFtn.GetNumber() );
/*?*/                       else
/*?*/                           sOut = rWrt.pDoc->GetFtnInfo().aFmt.
/*?*/                                           GetNumStr( rFtn.GetNumber() );
/*?*/                   }
/*?*/                   break;
/*?*/               }
/*?*/               if( sOut.Len() )
/*?*/                   rWrt.Strm().WriteUnicodeOrByteText( sOut );
/*?*/           }
/*?*/           else if( nSwPos < *pHt->GetStart() )
/*?*/               break;
/*?*/       }
/*N*/   }
/*N*/   return bRet;
/*N*/ }


//------------------------
/* Ausgabe der Nodes */
//------------------------

/*N*/ static Writer& OutASC_SwTxtNode( Writer& rWrt, SwCntntNode& rNode )
/*N*/ {
/*N*/   const SwTxtNode& rNd = (SwTxtNode&)rNode;
/*N*/
/*N*/   xub_StrLen nStrPos = rWrt.pCurPam->GetPoint()->nContent.GetIndex();
/*N*/   xub_StrLen nNodeEnde = rNd.Len(), nEnde = nNodeEnde;
/*N*/   BOOL bLastNd =  rWrt.pCurPam->GetPoint()->nNode == rWrt.pCurPam->GetMark()->nNode;
/*N*/   if( bLastNd )
/*N*/       nEnde = rWrt.pCurPam->GetMark()->nContent.GetIndex();
/*N*/
/*N*/   SwASC_AttrIter aAttrIter( (SwASCWriter&)rWrt, rNd, nStrPos );
/*N*/
/*N*/   if( !nStrPos )
/*N*/       rWrt.Strm().WriteUnicodeOrByteText( rNd.GetNumString() );
/*N*/
/*N*/   String aStr( rNd.GetTxt() );
/*N*/   if( rWrt.bASCII_ParaAsBlanc )
/*?*/       aStr.SearchAndReplaceAll( 0x0A, ' ' );
/*N*/
/*N*/   do {
/*N*/       xub_StrLen nNextAttr = aAttrIter.WhereNext();
/*N*/
/*N*/       if( nNextAttr > nEnde )
/*N*/           nNextAttr = nEnde;
/*N*/
/*N*/       if( !aAttrIter.OutAttr( nStrPos ))
/*N*/           rWrt.Strm().WriteUnicodeOrByteText(
/*N*/                               aStr.Copy( nStrPos, nNextAttr - nStrPos ));
/*N*/       nStrPos = nNextAttr;
/*N*/       aAttrIter.NextPos();
/*N*/   } while( nStrPos < nEnde );
/*N*/
/*N*/   if( !bLastNd ||
/*N*/       (( !rWrt.bWriteClipboardDoc && !rWrt.bASCII_NoLastLineEnd )
/*N*/           && !nStrPos && nEnde == nNodeEnde ))
/*?*/       rWrt.Strm().WriteUnicodeOrByteText( ((SwASCWriter&)rWrt).GetLineEnd());
/*N*/
/*N*/   return rWrt;
/*N*/ }

/*
 * lege hier jetzt die Tabellen fuer die ASCII-Funktions-Pointer auf
 * die Ausgabe-Funktionen an.
 * Es sind lokale Strukturen, die nur innerhalb der ASCII-DLL
 * bekannt sein muessen.
 */

SwNodeFnTab aASCNodeFnTab = {
/* RES_TXTNODE  */                   OutASC_SwTxtNode,
/* RES_GRFNODE  */                   0,
/* RES_OLENODE  */                   0
};

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
