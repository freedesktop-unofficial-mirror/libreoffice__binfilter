/*************************************************************************
 *
 *  $RCSfile: sw_fltglbls.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:20:50 $
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

#include "doc.hxx"
#include "pam.hxx"
#include "swtable.hxx"
#include "fltglbls.hxx"




//------------------------------------------------------------------------
FilterGlobals::FilterGlobals( SwDoc& rDoc, const SwPaM& rPam )
    : aStandard( String::CreateFromAscii("General") ),
    aTblFmts( 0, 10 )
{
    pD = &rDoc;         // "globaler" Dokument-Pointer
    pPam = new SwPaM( *rPam.GetPoint() );
    pTable = 0;
    pNumFormatter = 0;

    eDefLanguage = LANGUAGE_SYSTEM;
    nDefFormat = 0xFFFFFFFF;

    nColStart = nRowStart = 1;
    nColEnd = nRowEnd = 0;
    nAnzCols = nAnzRows = 0;
}

FilterGlobals::~FilterGlobals()
{
    // JP 13.08.98: TabellenUmrandungen optimieren - Bug 53525
    for( USHORT n = aTblFmts.Count(); n; )
    {
        SwTable* pTbl = SwTable::FindTable( (SwFrmFmt*)aTblFmts[ --n ] );
        if( pTbl )
            pTbl->GCBorderLines();
    }

    delete pPam;
}

//------------------------------------------------------------------------
void FilterGlobals::SetRange( USHORT nCS, USHORT nCE, USHORT nRS, USHORT nRE )
{
    if( nCE < nCS )
    {
        if( nCS == 0 )
            nCE = 0;
        else
            nCE = nCS - 1;
    }

    if( nRE < nRS )
    {
        if( nRS == 0 )
            nRE = 0;
        else
            nRE = nRS - 1;
    }

    nColStart = nCS;
    nColEnd = nCE;
    nRowStart = nRS;
    nRowEnd = nRE;
    nAnzCols = 1 + nCE - nCS;
    nAnzRows = 1 + nRE - nRS;
}



BOOL FilterGlobals::ColRangeLimitter( USHORT &rCS, USHORT &rCE )
{
    //  PREC:   rCS <= rCE
    //  POST:   wenn [rCS, rCE] und [nColStart,nColEnd] disjunkte Intervalle,
    //              return = FALSE;
    //          sonst
    //              return = TRUE
    //              rCS = MAX(rCS,nColStart)
    //              rCE = MIN(rCE,nColEnd)
    BOOL bRet;
    DBG_ASSERT( rCS <= rCE,
        "-FilterGlobals::ColRangeLimitter(): Startspalte > Endspalte!" );
    if( rCS > nColEnd || rCE < nColStart )
        bRet = FALSE;
    else
        {
        bRet = TRUE;
        if( rCS < nColStart )   rCS = nColStart;
        if( rCE > nColEnd )     rCE = nColEnd;
        }
    return bRet;
}

void FilterGlobals::InsertText( USHORT nCol, USHORT nRow, const String& rStr )
{
    pPam->GetPoint()->nNode = *pTable->GetTabLines()[ nRow ]->
                                        GetTabBoxes()[ nCol ]->GetSttNd();
    pPam->Move( fnMoveForward, fnGoCntnt );

    pD->Insert( *pPam, rStr );
}

void FilterGlobals::CreateTable()
{
    pTable = pD->InsertTable( *pPam->GetPoint(),
                                AnzRows(),  // nRows
                                AnzCols(),  // nCols
                                HORI_LEFT );        // SwHoriOrient

    // JP 13.08.98: TabellenUmrandungen optimieren - Bug 53525
    void* p = pTable->GetFrmFmt();
    aTblFmts.Insert( p, aTblFmts.Count() );
}

void FilterGlobals::InsertAttr( const SfxPoolItem& rItem )
{
    SfxItemSet aTxtAttr( pD->GetAttrPool(), rItem.Which(), rItem.Which() );
    aTxtAttr.Put( rItem );
    pD->Insert( *pLotGlob->pPam, aTxtAttr );
}


