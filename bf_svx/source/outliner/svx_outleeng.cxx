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

#define _OUTLINER_CXX
#include <outleeng.hxx>
#include <paralist.hxx>
#include <outliner.hrc>



#include "eerdll.hxx"

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
/*N*/           aBulletArea = pOwner->ImpCalcBulletArea( nPara );
/*N*/   }
/*N*/   return aBulletArea;
/*N*/ }

/*N*/ void OutlinerEditEng::ParagraphInserted( USHORT nNewParagraph )
/*N*/ {
/*N*/   pOwner->ParagraphInserted( nNewParagraph );
/*N*/ }

/*N*/ void OutlinerEditEng::ParagraphDeleted( USHORT nDeletedParagraph )
/*N*/ {
/*N*/   pOwner->ParagraphDeleted( nDeletedParagraph );
/*N*/ }


/*N*/ void OutlinerEditEng::ParaAttribsChanged( USHORT nPara )
/*N*/ {
/*N*/   pOwner->ParaAttribsChanged( nPara );
/*N*/ }

/*N*/ void OutlinerEditEng::ParagraphHeightChanged( USHORT nPara )
/*N*/ {
/*N*/   EditEngine::ParagraphHeightChanged( nPara );
/*N*/ }


/*N*/ XubString OutlinerEditEng::GetUndoComment( USHORT nUndoId ) const
/*N*/ {
/*N*/ #ifndef SVX_LIGHT
/*N*/   switch( nUndoId )
/*N*/   {
/*N*/       case OLUNDO_DEPTH:
/*?*/           return EditResId( RID_OUTLUNDO_DEPTH ).toString();
/*N*/
/*N*/       case OLUNDO_EXPAND:
/*?*/           return EditResId( RID_OUTLUNDO_EXPAND ).toString();
/*N*/
/*N*/       case OLUNDO_COLLAPSE:
/*?*/           return EditResId( RID_OUTLUNDO_COLLAPSE ).toString();
/*N*/
/*N*/       case OLUNDO_ATTR:
/*N*/           return EditResId( RID_OUTLUNDO_ATTR ).toString();
/*N*/
/*N*/       case OLUNDO_INSERT:
/*?*/           return EditResId( RID_OUTLUNDO_INSERT ).toString();
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

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
