/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2000, 2010 Oracle and/or its affiliates.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/


#ifdef _MSC_VER
#pragma hdrstop
#endif




#include <fchrfmt.hxx>

#include <horiornt.hxx>

#include <fmtclds.hxx>
#include <hfspacingitem.hxx>
#include <paratr.hxx>
#include <pagedesc.hxx>
#include <attrdesc.hrc>
namespace binfilter {

/*N*/ TYPEINIT2(SwFmtCharFmt,SfxPoolItem,SwClient);

// erfrage die Attribut-Beschreibung
/*N*/ void SwAttrSet::GetPresentation(
/*N*/       SfxItemPresentation /*ePres*/,
/*N*/       SfxMapUnit /*eCoreMetric*/,
/*N*/       SfxMapUnit /*ePresMetric*/,
/*N*/       String & /*rText*/ ) const
/*N*/ {
DBG_BF_ASSERT(0, "STRIP");
}


/*N*/ void SwPageDesc::GetPresentation(
/*N*/       SfxItemPresentation /*ePres*/,
/*N*/       SfxMapUnit /*eCoreMetric*/,
/*N*/       SfxMapUnit /*ePresMetric*/,
/*N*/       String &rText ) const
/*N*/ {
/*N*/   rText = GetName();
/*N*/ }


// ATT_CHARFMT *********************************************


/*N*/ SfxItemPresentation SwFmtCharFmt::GetPresentation
/*N*/ (
/*N*/   SfxItemPresentation /*ePres*/,
/*N*/   SfxMapUnit          /*eCoreUnit*/,
/*N*/   SfxMapUnit          /*ePresUnit*/,
/*N*/   String&             /*rText*/,
/*N*/     const ::IntlWrapper* /*pIntl*/
/*N*/ ) const
/*N*/ {DBG_BF_ASSERT(0, "STRIP");
/*N*/   return SFX_ITEM_PRESENTATION_NONE;
/*N*/ }

// ATT_INETFMT *********************************************




/*************************************************************************
|*    class     SwFmtDrop
*************************************************************************/



/*************************************************************************
|*    class     SwRegisterItem
*************************************************************************/



/*************************************************************************
|*    class     SwNumRuleItem
*************************************************************************/


/*************************************************************************
|*    class     SwParaConnectBorderItem
*************************************************************************/

/*N*/ SfxItemPresentation SwParaConnectBorderItem::GetPresentation
/*N*/ (
/*N*/     SfxItemPresentation ePres,
/*N*/     SfxMapUnit          eCoreUnit,
/*N*/     SfxMapUnit          ePresUnit,
/*N*/     XubString&          rText,
/*N*/     const ::IntlWrapper*        pIntl
/*N*/ )   const
/*N*/ {
/*N*/     // no UI support available
/*N*/     return SfxBoolItem::GetPresentation( ePres, eCoreUnit, ePresUnit, rText, pIntl );
/*N*/ }



/******************************************************************************
 *  Frame-Attribute:
 ******************************************************************************/



//Kopfzeile, fuer Seitenformate
//Client von FrmFmt das den Header beschreibt.



//Fusszeile, fuer Seitenformate
//Client von FrmFmt das den Footer beschreibt.






//VertOrientation, wie und woran orientiert --
//  sich der FlyFrm in der Vertikalen -----------



//HoriOrientation, wie und woran orientiert --
//  sich der FlyFrm in der Hoizontalen ----------



//FlyAnchor, Anker des Freifliegenden Rahmen ----





//Der ColumnDescriptor --------------------------



//URL's und Maps




//SwFmtEditInReadonly











//SwHeaderAndFooterEatSpacingItem


/*M*/ SfxItemPresentation SwHeaderAndFooterEatSpacingItem::GetPresentation
/*M*/ (
/*M*/   SfxItemPresentation /*ePres*/,
/*M*/   SfxMapUnit          /*eCoreUnit*/,
/*M*/   SfxMapUnit          /*ePresUnit*/,
/*M*/   String&             /*rText*/,
/*M*/   const ::IntlWrapper*  /*pIntl*/
/*M*/ ) const
/*M*/ {
/*M*/   return SFX_ITEM_PRESENTATION_NONE;
/*M*/ }



}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
