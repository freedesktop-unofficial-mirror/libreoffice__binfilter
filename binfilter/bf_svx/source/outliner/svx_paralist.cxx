/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_paralist.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 11:45:50 $
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

#include <paralist.hxx>
#include <outliner.hxx>     // nur wegen Paragraph, muss geaendert werden!
#include <numdef.hxx>
namespace binfilter {

/*N*/ DBG_NAME(Paragraph)

/*N*/ Paragraph::Paragraph( USHORT nDDepth )
/*N*/   : aBulSize( -1, -1)
/*N*/ {
/*N*/   DBG_CTOR( Paragraph, 0 );
/*N*/
/*N*/     DBG_ASSERT( ( nDDepth < SVX_MAX_NUM ) || ( nDDepth == 0xFFFF ), "Paragraph-CTOR: nDepth invalid!" );
/*N*/
/*N*/   nDepth = nDDepth;
/*N*/   nFlags = 0;
/*N*/   bVisible = TRUE;
/*N*/ }


/*N*/ Paragraph::~Paragraph()
/*N*/ {
/*N*/   DBG_DTOR( Paragraph, 0 );
/*N*/ }

/*N*/ void ParagraphList::Clear( BOOL bDestroyParagraphs )
/*N*/ {
/*N*/   if ( bDestroyParagraphs )
/*N*/   {
/*N*/       for ( ULONG n = GetParagraphCount(); n; )
/*N*/       {
/*N*/           Paragraph* pPara = GetParagraph( --n );
/*N*/           delete pPara;
/*N*/       }
/*N*/   }
/*N*/   List::Clear();
/*N*/ }









/*NBFF*/ Paragraph* ParagraphList::GetParent( Paragraph* pParagraph, USHORT& rRelPos ) const
/*NBFF*/ {
/*NBFF*/    rRelPos = 0;
/*NBFF*/    ULONG n = GetAbsPos( pParagraph );
/*NBFF*/    Paragraph* pPrev = GetParagraph( --n );
/*NBFF*/    while ( pPrev && ( pPrev->GetDepth() >= pParagraph->GetDepth() ) )
/*NBFF*/    {
/*NBFF*/        if ( pPrev->GetDepth() == pParagraph->GetDepth() )
/*NBFF*/            rRelPos++;
/*NBFF*/        pPrev = GetParagraph( --n );
/*NBFF*/    }
/*NBFF*/
/*NBFF*/    return pPrev;
/*NBFF*/ }



}
