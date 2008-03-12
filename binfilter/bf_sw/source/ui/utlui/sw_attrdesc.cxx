/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_attrdesc.cxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 10:55:08 $
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




#ifndef _FCHRFMT_HXX //autogen
#include <fchrfmt.hxx>
#endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _FMTCLDS_HXX //autogen
#include <fmtclds.hxx>
#endif
#ifndef _SW_HF_EAT_SPACINGITEM_HXX
#include <hfspacingitem.hxx>
#endif
#ifndef _PARATR_HXX
#include <paratr.hxx>
#endif
#ifndef _PAGEDESC_HXX
#include <pagedesc.hxx>
#endif
#ifndef _ATTRDESC_HRC
#include <attrdesc.hrc>
#endif
namespace binfilter {

/*N*/ TYPEINIT2(SwFmtCharFmt,SfxPoolItem,SwClient);

// erfrage die Attribut-Beschreibung
/*N*/ void SwAttrSet::GetPresentation(
/*N*/       SfxItemPresentation ePres,
/*N*/       SfxMapUnit eCoreMetric,
/*N*/       SfxMapUnit ePresMetric,
/*N*/       String &rText ) const
/*N*/ {
DBG_BF_ASSERT(0, "STRIP"); //STRIP001 static sal_Char __READONLY_DATA sKomma[] = ", ";
}


/*N*/ void SwPageDesc::GetPresentation(
/*N*/       SfxItemPresentation ePres,
/*N*/       SfxMapUnit eCoreMetric,
/*N*/       SfxMapUnit ePresMetric,
/*N*/       String &rText ) const
/*N*/ {
/*N*/   rText = GetName();
/*N*/ }


// ATT_CHARFMT *********************************************


/*N*/ SfxItemPresentation SwFmtCharFmt::GetPresentation
/*N*/ (
/*N*/   SfxItemPresentation ePres,
/*N*/   SfxMapUnit          eCoreUnit,
/*N*/   SfxMapUnit          ePresUnit,
/*N*/   String&             rText,
/*N*/     const ::IntlWrapper*        pIntl
/*N*/ ) const
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
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
/*    switch ( ePres )
    {
        case SFX_ITEM_PRESENTATION_NONE:
            rText.Erase();
            return SFX_ITEM_PRESENTATION_NONE;
        case SFX_ITEM_PRESENTATION_NAMELESS:
        case SFX_ITEM_PRESENTATION_COMPLETE:
        {
            USHORT nId = GetValue() ? STR_CONNECT_BORDER_ON : STR_CONNECT_BORDER_OFF;
            rText = SW_RESSTR( nId );
            return ePres;
        }
    }
    return SFX_ITEM_PRESENTATION_NONE;
 */
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
/*M*/   SfxItemPresentation ePres,
/*M*/   SfxMapUnit          eCoreUnit,
/*M*/   SfxMapUnit          ePresUnit,
/*M*/   String&             rText,
/*M*/     const ::IntlWrapper*        pIntl
/*M*/ ) const
/*M*/ {
//    rText.Erase();
//    switch ( ePres )
//    {
//        case SFX_ITEM_PRESENTATION_NONE:
//            rText.Erase();
//            break;
//        case SFX_ITEM_PRESENTATION_NAMELESS:
//        case SFX_ITEM_PRESENTATION_COMPLETE:
//        {
//            if ( GetValue() )
//                rText = SW_RESSTR(STR_EDIT_IN_READONLY);
//            return ePres;
//        }
//    }
/*M*/   return SFX_ITEM_PRESENTATION_NONE;
/*M*/ }


// ---------------------- Grafik-Attribute --------------------------












}
