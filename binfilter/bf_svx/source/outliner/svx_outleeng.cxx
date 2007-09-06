/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_outleeng.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 11:45:03 $
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

#define _OUTLINER_CXX
#include <outleeng.hxx>
#include <paralist.hxx>
#include <outliner.hrc>



#ifndef _EERDLL_HXX
#include "eerdll.hxx"
#endif

namespace binfilter {

/*N*/ OutlinerEditEng::OutlinerEditEng( Outliner* pEngOwner, SfxItemPool* pPool )
/*N*/  : EditEngine( pPool )
/*N*/ {
/*N*/   pOwner = pEngOwner;
/*N*/ }

/*N*/ OutlinerEditEng::~OutlinerEditEng()
/*N*/ {
/*N*/ }


/*N*/ Rectangle OutlinerEditEng::GetBulletArea( USHORT nPara )
/*N*/ {
/*N*/   Rectangle aBulletArea = Rectangle( Point(), Point() );
/*N*/   if ( nPara < pOwner->pParaList->GetParagraphCount() )
/*N*/   {
/*N*/       if ( pOwner->ImplHasBullet( nPara ) )
/*N*/           aBulletArea = pOwner->ImpCalcBulletArea( nPara, FALSE, FALSE );
/*N*/   }
/*N*/   return aBulletArea;
/*N*/ }

/*N*/ void OutlinerEditEng::ParagraphInserted( USHORT nNewParagraph )
/*N*/ {
/*N*/   pOwner->ParagraphInserted( nNewParagraph );
/*N*/
/*N*/     EditEngine::ParagraphInserted( nNewParagraph );
/*N*/ }

/*N*/ void OutlinerEditEng::ParagraphDeleted( USHORT nDeletedParagraph )
/*N*/ {
/*N*/   pOwner->ParagraphDeleted( nDeletedParagraph );
/*N*/
/*N*/     EditEngine::ParagraphDeleted( nDeletedParagraph );
/*N*/ }


/*N*/ void OutlinerEditEng::ParaAttribsChanged( USHORT nPara )
/*N*/ {
/*N*/   pOwner->ParaAttribsChanged( nPara );
/*N*/ }

/*N*/ void OutlinerEditEng::ParagraphHeightChanged( USHORT nPara )
/*N*/ {
/*N*/   pOwner->ParagraphHeightChanged( nPara );
/*N*/
/*N*/     EditEngine::ParagraphHeightChanged( nPara );
/*N*/ }


/*N*/ XubString OutlinerEditEng::GetUndoComment( USHORT nUndoId ) const
/*N*/ {
/*N*/ #ifndef SVX_LIGHT
/*N*/   switch( nUndoId )
/*N*/   {
/*N*/       case OLUNDO_DEPTH:
/*?*/           return XubString( EditResId( RID_OUTLUNDO_DEPTH ));
/*N*/
/*N*/       case OLUNDO_EXPAND:
/*?*/           return XubString( EditResId( RID_OUTLUNDO_EXPAND ));
/*N*/
/*N*/       case OLUNDO_COLLAPSE:
/*?*/           return XubString( EditResId( RID_OUTLUNDO_COLLAPSE ));
/*N*/
/*N*/       case OLUNDO_ATTR:
/*N*/           return XubString( EditResId( RID_OUTLUNDO_ATTR ));
/*N*/
/*N*/       case OLUNDO_INSERT:
/*?*/           return XubString( EditResId( RID_OUTLUNDO_INSERT ));
/*N*/
/*N*/       default:
/*N*/           return EditEngine::GetUndoComment( nUndoId );
/*N*/   }
/*N*/ #else // SVX_LIGHT
/*N*/   XubString aString;
/*N*/   return aString;
/*N*/ #endif
/*N*/ }

// #101498#
/*N*/ void OutlinerEditEng::DrawingText( const Point& rStartPos, const XubString& rText, USHORT nTextStart, USHORT nTextLen, const sal_Int32* pDXArray, const SvxFont& rFont, USHORT nPara, USHORT nIndex, BYTE nRightToLeft)
/*N*/ {
/*N*/   if ( nIndex == 0 )
/*N*/   {
/*N*/       // Dann das Bullet 'malen', dort wird bStrippingPortions ausgewertet
/*N*/       // und Outliner::DrawingText gerufen
/*N*/
/*N*/       // DrawingText liefert die BaseLine, DrawBullet braucht Top().
/*N*/       Point aCorrectedPos( rStartPos );
/*N*/       aCorrectedPos.Y() = GetDocPosTopLeft( nPara ).Y();
/*N*/       aCorrectedPos.Y() += GetFirstLineOffset( nPara );
/*N*/       pOwner->PaintBullet( nPara, aCorrectedPos, Point(), 0, GetRefDevice() );
/*N*/   }
/*N*/
/*N*/   // #101498#
/*N*/   pOwner->DrawingText(rStartPos,rText,nTextStart,nTextLen,pDXArray,rFont,nPara,nIndex,nRightToLeft);
/*N*/ }



/*N*/ XubString OutlinerEditEng::CalcFieldValue( const SvxFieldItem& rField, USHORT nPara, USHORT nPos, Color*& rpTxtColor, Color*& rpFldColor )
/*N*/ {
/*N*/   return pOwner->CalcFieldValue( rField, nPara, nPos, rpTxtColor, rpFldColor );
/*N*/ }
}
