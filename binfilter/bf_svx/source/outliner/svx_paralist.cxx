/*************************************************************************
 *
 *  $RCSfile: svx_paralist.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:22:16 $
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

#include <paralist.hxx>
#include <outliner.hxx>     // nur wegen Paragraph, muss geaendert werden!
#include <numdef.hxx>

/*N*/ DBG_NAME(Paragraph);

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

//STRIP001 Paragraph::Paragraph( const Paragraph& rPara )
//STRIP001  : aBulSize( rPara.aBulSize ), aBulText( rPara.aBulText )
//STRIP001 {
//STRIP001  DBG_CTOR( Paragraph, 0 );
//STRIP001
//STRIP001  nDepth = rPara.nDepth;
//STRIP001  nFlags = rPara.nFlags;
//STRIP001  bVisible = rPara.bVisible;
//STRIP001 }

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

//STRIP001 void ParagraphList::MoveParagraphs( ULONG nStart, ULONG nDest, ULONG nCount )
//STRIP001 {
//STRIP001  if ( ( nDest < nStart ) || ( nDest >= ( nStart + nCount ) ) )
//STRIP001  {
//STRIP001      ULONG n;
//STRIP001      ParagraphList aParas;
//STRIP001      for ( n = 0; n < nCount; n++ )
//STRIP001      {
//STRIP001          Paragraph* pPara = GetParagraph( nStart );
//STRIP001          aParas.Insert( pPara, LIST_APPEND );
//STRIP001          Remove( nStart );
//STRIP001      }
//STRIP001
//STRIP001      if ( nDest > nStart )
//STRIP001          nDest -= nCount;
//STRIP001
//STRIP001      for ( n = 0; n < nCount; n++ )
//STRIP001      {
//STRIP001          Paragraph* pPara = aParas.GetParagraph( n );
//STRIP001          Insert( pPara, nDest++ );
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001      DBG_ERROR( "MoveParagraphs: Invalid Parameters" );
//STRIP001 }

//STRIP001 Paragraph* ParagraphList::NextVisible( Paragraph* pPara ) const
//STRIP001 {
//STRIP001  ULONG n = GetAbsPos( pPara );
//STRIP001
//STRIP001  Paragraph* p = GetParagraph( ++n );
//STRIP001  while ( p && !p->IsVisible() )
//STRIP001      p = GetParagraph( ++n );
//STRIP001
//STRIP001  return p;
//STRIP001 }

//STRIP001 Paragraph* ParagraphList::PrevVisible( Paragraph* pPara ) const
//STRIP001 {
//STRIP001  ULONG n = GetAbsPos( pPara );
//STRIP001
//STRIP001  Paragraph* p = n ? GetParagraph( --n ) : NULL;
//STRIP001  while ( p && !p->IsVisible() )
//STRIP001      p = n ? GetParagraph( --n ) : NULL;
//STRIP001
//STRIP001  return p;
//STRIP001 }

//STRIP001 Paragraph* ParagraphList::LastVisible() const
//STRIP001 {
//STRIP001  ULONG n = GetParagraphCount();
//STRIP001
//STRIP001  Paragraph* p = n ? GetParagraph( --n ) : NULL;
//STRIP001  while ( p && !p->IsVisible() )
//STRIP001      p = n ? GetParagraph( --n ) : NULL;
//STRIP001
//STRIP001  return p;
//STRIP001 }

//STRIP001 BOOL ParagraphList::HasChilds( Paragraph* pParagraph ) const
//STRIP001 {
//STRIP001  ULONG n = GetAbsPos( pParagraph );
//STRIP001  Paragraph* pNext = GetParagraph( ++n );
//STRIP001  return ( pNext && ( pNext->GetDepth() > pParagraph->GetDepth() ) ) ? TRUE : FALSE;
//STRIP001 }

//STRIP001 BOOL ParagraphList::HasHiddenChilds( Paragraph* pParagraph ) const
//STRIP001 {
//STRIP001  ULONG n = GetAbsPos( pParagraph );
//STRIP001  Paragraph* pNext = GetParagraph( ++n );
//STRIP001  return ( pNext && ( pNext->GetDepth() > pParagraph->GetDepth() ) && !pNext->IsVisible() ) ? TRUE : FALSE;
//STRIP001 }

//STRIP001 BOOL ParagraphList::HasVisibleChilds( Paragraph* pParagraph ) const
//STRIP001 {
//STRIP001  ULONG n = GetAbsPos( pParagraph );
//STRIP001  Paragraph* pNext = GetParagraph( ++n );
//STRIP001  return ( pNext && ( pNext->GetDepth() > pParagraph->GetDepth() ) && pNext->IsVisible() ) ? TRUE : FALSE;
//STRIP001 }

//STRIP001 ULONG ParagraphList::GetChildCount( Paragraph* pParent ) const
//STRIP001 {
//STRIP001  ULONG nChildCount = 0;
//STRIP001  ULONG n = GetAbsPos( pParent );
//STRIP001  Paragraph* pPara = GetParagraph( ++n );
//STRIP001  while ( pPara && ( pPara->GetDepth() > pParent->GetDepth() ) )
//STRIP001  {
//STRIP001      nChildCount++;
//STRIP001      pPara = GetParagraph( ++n );
//STRIP001  }
//STRIP001  return nChildCount;
//STRIP001 }

//STRIP001 Paragraph* ParagraphList::GetParent( Paragraph* pParagraph, USHORT& rRelPos ) const
//STRIP001 {
//STRIP001  rRelPos = 0;
//STRIP001  ULONG n = GetAbsPos( pParagraph );
//STRIP001  Paragraph* pPrev = GetParagraph( --n );
//STRIP001  while ( pPrev && ( pPrev->GetDepth() >= pParagraph->GetDepth() ) )
//STRIP001  {
//STRIP001      if ( pPrev->GetDepth() == pParagraph->GetDepth() )
//STRIP001          rRelPos++;
//STRIP001      pPrev = GetParagraph( --n );
//STRIP001  }
//STRIP001
//STRIP001  return pPrev;
//STRIP001 }

//STRIP001 void ParagraphList::Expand( Paragraph* pParent )
//STRIP001 {
//STRIP001  ULONG nChildCount = GetChildCount( pParent );
//STRIP001  ULONG nPos = GetAbsPos( pParent );
//STRIP001
//STRIP001  for ( ULONG n = 1; n <= nChildCount; n++  )
//STRIP001  {
//STRIP001      Paragraph* pPara = GetParagraph( nPos+n );
//STRIP001      if ( !( pPara->IsVisible() ) )
//STRIP001      {
//STRIP001          pPara->bVisible = TRUE;
//STRIP001          aVisibleStateChangedHdl.Call( pPara );
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void ParagraphList::Collapse( Paragraph* pParent )
//STRIP001 {
//STRIP001  ULONG nChildCount = GetChildCount( pParent );
//STRIP001  ULONG nPos = GetAbsPos( pParent );
//STRIP001
//STRIP001  for ( ULONG n = 1; n <= nChildCount; n++  )
//STRIP001  {
//STRIP001      Paragraph* pPara = GetParagraph( nPos+n );
//STRIP001      if ( pPara->IsVisible() )
//STRIP001      {
//STRIP001          pPara->bVisible = FALSE;
//STRIP001          aVisibleStateChangedHdl.Call( pPara );
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 ULONG ParagraphList::GetVisPos( Paragraph* pPara )
//STRIP001 {
//STRIP001  ULONG nVisPos = 0;
//STRIP001  ULONG nPos = GetAbsPos( pPara );
//STRIP001  for ( ULONG n = 0; n < nPos; n++ )
//STRIP001  {
//STRIP001      Paragraph* pPara = GetParagraph( n );
//STRIP001      if ( pPara->IsVisible() )
//STRIP001          nVisPos++;
//STRIP001  }
//STRIP001  return nVisPos;
//STRIP001 }
