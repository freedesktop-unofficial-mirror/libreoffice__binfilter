/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_gctable.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 22:26:18 $
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

#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif


#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif
#ifndef _TBLRWCL_HXX
#include <tblrwcl.hxx>
#endif
#ifndef _SWTBLFMT_HXX
#include <swtblfmt.hxx>
#endif
namespace binfilter {











// suche das "Ende" der vorgegebene BorderLine. Returnt wird die "Layout"Pos!










/*  */

struct _GCLinePara
{
    SwTableLines* pLns;
    SwShareBoxFmts* pShareFmts;

    _GCLinePara( SwTableLines& rLns, _GCLinePara* pPara = 0 )
        : pLns( &rLns ), pShareFmts( pPara ? pPara->pShareFmts : 0 )
    {}
};

/*N*/ BOOL lcl_MergeGCBox( const SwTableBox*& rpTblBox, void* pPara )
/*N*/ {
/*N*/   SwTableBox*& rpBox = (SwTableBox*&)rpTblBox;
/*N*/   USHORT n, nLen = rpBox->GetTabLines().Count();
/*N*/   if( nLen )
/*N*/   {
/*N*/       // ACHTUNG: die Anzahl der Lines kann sich aendern!
/*N*/       _GCLinePara aPara( rpBox->GetTabLines(), (_GCLinePara*)pPara );
/*N*/       for( n = 0; n < rpBox->GetTabLines().Count() &&
/*N*/           lcl_MergeGCLine( *(rpBox->GetTabLines().GetData() + n), &aPara );
/*N*/           ++n )
/*N*/           ;
/*N*/
/*N*/       if( 1 == rpBox->GetTabLines().Count() )
/*N*/       {
/*N*/           // Box mit einer Line, dann verschiebe alle Boxen der Line
/*N*/           // hinter diese Box in der Parent-Line und loesche diese Box
/*?*/           SwTableLine* pInsLine = rpBox->GetUpper();
/*?*/           SwTableLine* pCpyLine = rpBox->GetTabLines()[0];
/*?*/           USHORT nInsPos = pInsLine->GetTabBoxes().C40_GETPOS( SwTableBox, rpBox );
/*?*/           for( n = 0; n < pCpyLine->GetTabBoxes().Count(); ++n )
/*?*/               pCpyLine->GetTabBoxes()[n]->SetUpper( pInsLine );
/*?*/
/*?*/           pInsLine->GetTabBoxes().Insert( &pCpyLine->GetTabBoxes(), nInsPos+1 );
/*?*/           pCpyLine->GetTabBoxes().Remove( 0, n );
/*?*/           // loesche alte die Box mit der Line
/*?*/           pInsLine->GetTabBoxes().DeleteAndDestroy( nInsPos );
/*?*/
/*?*/           return FALSE;       // neu aufsetzen
/*N*/       }
/*N*/   }
/*N*/   return TRUE;
/*N*/ }

/*N*/ BOOL lcl_MergeGCLine( const SwTableLine*& rpLine, void* pPara )
/*N*/ {
/*N*/   SwTableLine* pLn = (SwTableLine*)rpLine;
/*N*/   USHORT nLen = pLn->GetTabBoxes().Count();
/*N*/   if( nLen )
/*N*/   {
/*N*/       _GCLinePara* pGCPara = (_GCLinePara*)pPara;
/*N*/       while( 1 == nLen )
/*N*/       {
/*N*/           // es gibt eine Box mit Lines
/*N*/           SwTableBox* pBox = pLn->GetTabBoxes()[0];
/*N*/           if( !pBox->GetTabLines().Count() )
/*N*/               break;
/*N*/
/*N*/           SwTableLine* pLine = pBox->GetTabLines()[0];
/*N*/
/*N*/           // pLine wird zu der aktuellen, also der rpLine,
/*N*/           // die restlichen werden ins LinesArray hinter der akt.
/*N*/           // verschoben.
/*N*/           // Das LinesArray ist im pPara!
/*N*/           nLen = pBox->GetTabLines().Count();
/*N*/
/*N*/           SwTableLines& rLns = *pGCPara->pLns;
/*N*/           const SwTableLine* pTmp = pLn;
/*N*/           USHORT nInsPos = rLns.GetPos( pTmp );
/*N*/           ASSERT( USHRT_MAX != nInsPos, "Line nicht gefunden!" );
/*N*/
/*N*/           SwTableBox* pUpper = pLn->GetUpper();
/*N*/
/*N*/           rLns.Remove( nInsPos, 1 );      // die Line dem aus Array loeschen
/*N*/           rLns.Insert( &pBox->GetTabLines(), nInsPos );
/*N*/
/*N*/           // JP 31.03.99: Bug 60000 - die Attribute der zu loeschenden
/*N*/           // Line an die "eingefuegten" uebertragen
/*N*/           const SfxPoolItem* pItem;
/*N*/           if( SFX_ITEM_SET == pLn->GetFrmFmt()->GetItemState(
/*N*/                                   RES_BACKGROUND, TRUE, &pItem ))
/*N*/           {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/           }
/*N*/
/*N*/           pBox->GetTabLines().Remove( 0, nLen );  // Lines aus Array loeschen
/*N*/
/*N*/           delete pLn;
/*N*/
/*N*/           // Abhaengigkeit neu setzen
/*N*/           while( nLen-- )
/*N*/               rLns[ nInsPos++ ]->SetUpper( pUpper );
/*N*/
/*N*/           pLn = pLine;                        // und neu setzen
/*N*/           nLen = pLn->GetTabBoxes().Count();
/*N*/       }
/*N*/
/*N*/       // ACHTUNG: die Anzahl der Boxen kann sich aendern!
/*N*/       for( nLen = 0; nLen < pLn->GetTabBoxes().Count(); ++nLen )
/*N*/           if( !lcl_MergeGCBox( *(pLn->GetTabBoxes().GetData() + nLen ), pPara ))
/*N*/               --nLen;
/*N*/   }
/*N*/   return TRUE;
/*N*/ }

        // Struktur ein wenig aufraeumen
/*N*/ void SwTable::GCLines()
/*N*/ {
/*N*/   // ACHTUNG: die Anzahl der Lines kann sich aendern!
/*N*/   _GCLinePara aPara( GetTabLines() );
/*N*/   SwShareBoxFmts aShareFmts;
/*N*/   aPara.pShareFmts = &aShareFmts;
/*N*/   for( USHORT n = 0; n < GetTabLines().Count() &&
/*N*/           lcl_MergeGCLine( *(GetTabLines().GetData() + n ), &aPara ); ++n )
/*N*/       ;
/*N*/ }


}
