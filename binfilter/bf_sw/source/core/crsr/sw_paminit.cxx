/*************************************************************************
 *
 *  $RCSfile: sw_paminit.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 15:08:46 $
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

#ifndef _PAMTYP_HXX
#include <pamtyp.hxx>
#endif


/*N*/ static SwMoveFnCollection aFwrd = {
/*N*/   /* fnNd         */  &GoNext,
/*N*/   /* fnNds        */  &GoNextNds,
/*N*/   /* fnDoc        */  &GoEndDoc,
/*N*/   /* fnSections   */  &GoEndSection,
/*N*/   /* fnCmpOp      */  &SwPosition::operator<,
/*N*/   /* fnGetHint    */  &GetFrwrdTxtHint,
/*N*/   /* fnSearch     */  &utl::TextSearch::SearchFrwrd,
/*N*/   /* fnSection    */  &SwNodes::GoStartOfSection
/*N*/ };

/*N*/ static SwMoveFnCollection aBwrd = {
/*N*/   /* fnNd         */  &GoPrevious,
/*N*/   /* fnNds        */  &GoPreviousNds,
/*N*/   /* fnDoc        */  &GoStartDoc,
/*N*/   /* fnSections   */  &GoStartSection,
/*N*/   /* fnCmpOp      */  &SwPosition::operator>,
/*N*/   /* fnGetHint    */  &GetBkwrdTxtHint,
/*N*/   /* fnSearch     */  &utl::TextSearch::SearchBkwrd,
/*N*/   /* fnSection    */  &SwNodes::GoEndOfSection
/*N*/ };

/*N*/ SwGoInDoc fnGoDoc         = &GoInDoc;
/*N*/ SwGoInDoc fnGoSection = &GoInSection;
/*N*/ SwGoInDoc fnGoNode        = &GoInNode;
/*N*/ SwGoInDoc fnGoCntnt       = &GoInCntnt;
/*N*/ SwGoInDoc fnGoCntntCells= &GoInCntntCells;

/*N*/ SwWhichPara fnParaPrev    = &GoPrevPara;
/*N*/ SwWhichPara fnParaCurr    = &GoCurrPara;
/*N*/ SwWhichPara fnParaNext    = &GoNextPara;
/*N*/ SwPosPara fnParaStart = &aFwrd;
/*N*/ SwPosPara fnParaEnd       = &aBwrd;

/*N*/ SwWhichSection fnSectionPrev  = &GoPrevSection;
/*N*/ SwWhichSection fnSectionCurr  = &GoCurrSection;
/*N*/ SwWhichSection fnSectionNext  = &GoNextSection;
/*N*/ SwPosSection fnSectionStart       = &aFwrd;
/*N*/ SwPosSection fnSectionEnd     = &aBwrd;

// Travelling in Tabellen
/*N*/ FASTBOOL GotoPrevTable( SwPaM&, SwPosTable, FASTBOOL bInReadOnly );
/*N*/ FASTBOOL GotoCurrTable( SwPaM&, SwPosTable, FASTBOOL bInReadOnly );
/*N*/ FASTBOOL GotoNextTable( SwPaM&, SwPosTable, FASTBOOL bInReadOnly );

/*N*/ SwWhichTable fnTablePrev = &GotoPrevTable;
/*N*/ SwWhichTable fnTableCurr = &GotoCurrTable;
/*N*/ SwWhichTable fnTableNext = &GotoNextTable;
/*N*/ SwPosTable fnTableStart = &aFwrd;
/*N*/ SwPosTable fnTableEnd = &aBwrd;

// Travelling in Bereichen
/*N*/ FASTBOOL GotoPrevRegion( SwPaM&, SwPosRegion, FASTBOOL bInReadOnly );
/*N*/ FASTBOOL GotoCurrRegion( SwPaM&, SwPosRegion, FASTBOOL bInReadOnly );
/*N*/ FASTBOOL GotoCurrRegionAndSkip( SwPaM&, SwPosRegion, FASTBOOL bInReadOnly );
/*N*/ FASTBOOL GotoNextRegion( SwPaM&, SwPosRegion, FASTBOOL bInReadOnly );

/*N*/ SwWhichRegion fnRegionPrev = &GotoPrevRegion;
/*N*/ SwWhichRegion fnRegionCurr = &GotoCurrRegion;
/*N*/ SwWhichRegion fnRegionCurrAndSkip = &GotoCurrRegionAndSkip;
/*N*/ SwWhichRegion fnRegionNext = &GotoNextRegion;
/*N*/ SwPosRegion fnRegionStart = &aFwrd;
/*N*/ SwPosRegion fnRegionEnd = &aBwrd;
/*N*/
/*N*/ SwMoveFn fnMoveBackward   = &aBwrd;
/*N*/ SwMoveFn fnMoveForward    = &aFwrd;


#ifdef USED

// JP 30.11.95:
//  war fuer die CFRONT-Compiler noetig, jetzt sollte das nicht mehr
//  benoetigt werden.

/*N*/ void _InitPam()
/*N*/ {
/*N*/   aBwrd.fnNd      =  &GoPrevious;
/*N*/   aBwrd.fnNds     =  &GoPreviousNds;
/*N*/   aBwrd.fnDoc     =  &GoStartDoc;
/*N*/   aBwrd.fnSections=  &GoStartSection;
/*N*/   aBwrd.fnCmpOp   =  &SwPosition::operator>;
/*N*/   aBwrd.fnGetHint =  &GetBkwrdTxtHint;
/*N*/   aBwrd.fnSearch  =  &SearchText::SearchBkwrd;
/*N*/   aBwrd.fnSection =  &SwNodes::GoEndOfSection;
/*N*/
/*N*/   aFwrd.fnNd      =  &GoNext;
/*N*/   aFwrd.fnNds     =  &GoNextNds;
/*N*/   aFwrd.fnDoc     =  &GoEndDoc;
/*N*/   aFwrd.fnSections=  &GoEndSection;
/*N*/   aFwrd.fnCmpOp   =  &SwPosition::operator<;
/*N*/   aFwrd.fnGetHint =  &GetFrwrdTxtHint;
/*N*/   aFwrd.fnSearch  =  &SearchText::SearchFrwrd;
/*N*/   aFwrd.fnSection =  &SwNodes::GoStartOfSection;
/*N*/ }
#endif


