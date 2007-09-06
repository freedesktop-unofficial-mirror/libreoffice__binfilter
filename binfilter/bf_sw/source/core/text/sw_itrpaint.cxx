/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_itrpaint.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 12:34:10 $
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


#ifdef _MSC_VER
#pragma hdrstop
#endif


#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#include "txtatr.hxx"  // SwINetFmt


#ifndef _PAGEDESC_HXX
#include <pagedesc.hxx> // SwPageDesc
#endif

#include "itrpaint.hxx"
#include "pormulti.hxx"
namespace binfilter {

/*************************************************************************
 *                  IsUnderlineBreak
 *
 * Returns, if we have an underline breaking situation
 * Adding some more conditions here means you also have to change them
 * in SwTxtPainter::CheckSpecialUnderline
 *************************************************************************/
/*N*/ sal_Bool IsUnderlineBreak( const SwLinePortion& rPor, const SwFont& rFnt )
/*N*/ {
/*N*/     return UNDERLINE_NONE == rFnt.GetUnderline() ||
/*N*/            rPor.IsFlyPortion() || rPor.IsFlyCntPortion() ||
/*N*/            rPor.IsBreakPortion() || rPor.IsMarginPortion() ||
/*N*/            rPor.IsHolePortion() ||
/*N*/           ( rPor.IsMultiPortion() && ! ((SwMultiPortion&)rPor).IsBidi() ) ||
/*N*/            rFnt.GetEscapement() < 0 || rFnt.IsWordLineMode() ||
/*N*/            SVX_CASEMAP_KAPITAELCHEN == rFnt.GetCaseMap();
/*N*/ }

/*************************************************************************
 *                  SwTxtPainter::CtorInit()
 *************************************************************************/
/*N*/ void SwTxtPainter::CtorInit( SwTxtFrm *pFrm, SwTxtPaintInfo *pNewInf )
/*N*/ {
/*N*/   SwTxtCursor::CtorInit( pFrm, pNewInf );
/*N*/   pInf = pNewInf;
/*N*/   SwFont *pFnt = GetFnt();
/*N*/   GetInfo().SetFont( pFnt );
/*N*/ #ifndef PRODUCT
/*N*/   if( ALIGN_BASELINE != pFnt->GetAlign() )
/*N*/   {
/*?*/       ASSERT( ALIGN_BASELINE == pFnt->GetAlign(),
/*?*/               "+SwTxtPainter::CTOR: font alignment revolution" );
/*?*/       pFnt->SetAlign( ALIGN_BASELINE );
/*N*/   }
/*N*/ #endif
/*N*/   bPaintDrop = sal_False;
/*N*/ }


/*************************************************************************
 *                    SwTxtPainter::CalcPaintOfst()
 *************************************************************************/

/*************************************************************************
 *                    SwTxtPainter::DrawTextLine()
 *
 * Es gibt zwei Moeglichkeiten bei transparenten Font auszugeben:
 * 1) DrawRect auf die ganze Zeile und die DrawText hinterher
 *    (objektiv schnell, subjektiv langsam).
 * 2) Fuer jede Portion ein DrawRect mit anschliessendem DrawText
 *    ausgefuehrt (objektiv langsam, subjektiv schnell).
 * Da der User in der Regel subjektiv urteilt, wird die 2. Methode
 * als Default eingestellt.
 *************************************************************************/

}
