/*************************************************************************
 *
 *  $RCSfile: sd_drawdoc4.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:39:56 $
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

#ifndef SVX_LIGHT
#include <tools/urlobj.hxx>
#include <bf_sfx2/docfile.hxx>
#ifndef _SFXDISPATCH_HXX //autogen
#include <bf_sfx2/dispatch.hxx>
#endif
#ifndef _OFF_APP_HXX //autogen
#include <bf_offmgr/app.hxx>
#endif
#ifndef _OSPLCFG_HXX
#include <bf_offmgr/osplcfg.hxx>
#endif
#include "sdoutl.hxx"
#ifndef _COMPHELPER_PROCESSFACTORY_HXX_
#include <comphelper/processfactory.hxx>
#endif#else
#ifndef _OUTLINER_HXX //autogen wg. Outliner
#include <bf_svx/outliner.hxx>
#endif
#ifdef MAC
#include "::ui:inc:docshell.hxx"
#else
#ifdef UNX
#include "../ui/inc/docshell.hxx"
#else
#include "..\ui\inc\docshell.hxx"
#endif
#endif
#endif // !SVX_LIGHT

#ifndef _EEITEM_HXX //autogen
#include <bf_svx/eeitem.hxx>
#endif

#include <eetext.hxx>

#define ITEMID_SEARCH               SID_SEARCH_ITEM
#define ITEMID_LANGUAGE             EE_CHAR_LANGUAGE
#define ITEMID_EMPHASISMARK         EE_CHAR_EMPHASISMARK
#define ITEMID_CHARRELIEF           EE_CHAR_RELIEF
#define ITEMID_FRAMEDIR             EE_PARA_WRITINGDIR

#include <bf_svx/svxids.hrc>
#include <bf_svx/srchitem.hxx>
#include <bf_svx/lrspitem.hxx>
#include <bf_svx/ulspitem.hxx>
#include <bf_svx/lspcitem.hxx>
#include <bf_svx/adjitem.hxx>
#include <bf_svx/dialogs.hrc>
#include <bf_svx/dialmgr.hxx>                   // SVX_RESSTR
#include <bf_svx/bulitem.hxx>
#include <bf_svx/xtable.hxx>
#ifndef _SVX_XIT_HXX //autogen
#include <bf_svx/xit.hxx>
#endif
#ifndef _SVX_XLINEIT0_HXX //autogen
#include <bf_svx/xlineit0.hxx>
#endif
#ifndef _SDSHITM_HXX //autogen
#include <bf_svx/sdshitm.hxx>
#endif
#ifndef _SVDOTEXT_HXX //autogen
#include <bf_svx/svdotext.hxx>
#endif
#ifndef SVX_XFILLIT0_HXX //autogen
#include <bf_svx/xfillit0.hxx>
#endif
#ifndef _SDSHCITM_HXX //autogen
#include <bf_svx/sdshcitm.hxx>
#endif
#ifndef _EDITSTAT_HXX //autogen
#include <bf_svx/editstat.hxx>
#endif
#ifndef _SVX_COLRITEM_HXX //autogen
#include <bf_svx/colritem.hxx>
#endif
#ifndef _SVX_FHGTITEM_HXX //autogen
#include <bf_svx/fhgtitem.hxx>
#endif
#ifndef _SVX_WGHTITEM_HXX //autogen
#include <bf_svx/wghtitem.hxx>
#endif
#ifndef _SVX_POSTITEM_HXX //autogen
#include <bf_svx/postitem.hxx>
#endif
#ifndef _SVX_CRSDITEM_HXX //autogen
#include <bf_svx/crsditem.hxx>
#endif
#ifndef _SVX_UDLNITEM_HXX //autogen
#include <bf_svx/udlnitem.hxx>
#endif
#ifndef _SVX_ITEM_HXX //autogen
#include <bf_svx/cntritem.hxx>
#endif
#ifndef _SVX_EMPHITEM_HXX
#include <bf_svx/emphitem.hxx>
#endif
#ifndef _SVX_FONTITEM_HXX //autogen
#include <bf_svx/fontitem.hxx>
#endif
#ifndef _SVX_SHDDITEM_HXX //autogen
#include <bf_svx/shdditem.hxx>
#endif
#ifndef _SVX_XBTMPIT_HXX //autogen
#include <bf_svx/xbtmpit.hxx>
#endif
#ifndef _SVX_XFLHTIT_HXX //autogen
#include <bf_svx/xflhtit.hxx>
#endif
#ifndef _SVX_XFLGRIT_HXX //autogen
#include <bf_svx/xflgrit.hxx>
#endif
#ifndef _SVX_XFLCLIT_HXX //autogen
#include <bf_svx/xflclit.hxx>
#endif
#ifndef _SVX_XLNEDCIT_HXX //autogen
#include <bf_svx/xlnedcit.hxx>
#endif
#ifndef _SVX_XLNSTCIT_HXX //autogen
#include <bf_svx/xlnstcit.hxx>
#endif
#ifndef _SVX_XLNEDWIT_HXX //autogen
#include <bf_svx/xlnedwit.hxx>
#endif
#ifndef _SVX_XLNSTWIT_HXX //autogen
#include <bf_svx/xlnstwit.hxx>
#endif
#ifndef _SVX_XLNEDIT_HXX //autogen
#include <bf_svx/xlnedit.hxx>
#endif
#ifndef _SVX_CHARRELIEFITEM_HXX
#include <bf_svx/charreliefitem.hxx>
#endif
#ifndef _SVX_XLNSTIT_HXX //autogen
#include <bf_svx/xlnstit.hxx>
#endif
#ifndef _SVX_XLNDSIT_HXX //autogen
#include <bf_svx/xlndsit.hxx>
#endif
#ifndef _SVX_XLNWTIT_HXX //autogen
#include <bf_svx/xlnwtit.hxx>
#endif
#ifndef _SVX_XLNCLIT_HXX //autogen
#include <bf_svx/xlnclit.hxx>
#endif
#ifndef _SVDITER_HXX //autogen
#include <bf_svx/svditer.hxx>
#endif
#ifndef _SVDOGRP_HXX //autogen
#include <bf_svx/svdogrp.hxx>
#endif
#ifndef _SHL_HXX //autogen
#include <tools/shl.hxx>
#endif
#ifndef _SVX_NUMITEM_HXX
#include <bf_svx/numitem.hxx>
#endif
#ifndef _MyEDITENG_HXX //autogen
#include <bf_svx/editeng.hxx>
#endif
#ifndef _UNO_LINGU_HXX
#include <bf_svx/unolingu.hxx>
#endif
#ifndef _COM_SUN_STAR_LINGUISTIC2_XHYPHENATOR_HPP_
#include <com/sun/star/linguistic2/XHyphenator.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_XMULTISERVICEFACTORY_HPP_
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#endif
#ifndef _SFXITEMPOOL_HXX
#include <svtools/itempool.hxx>
#endif
#ifndef _OUTLOBJ_HXX
#include <bf_svx/outlobj.hxx>
#endif
#ifndef _SFXVIEWFRM_HXX
#include <bf_sfx2/viewfrm.hxx>
#endif
#ifndef _SVX_LANGITEM_HXX
#include <bf_svx/langitem.hxx>
#endif
#ifndef _SVX_FRMDIRITEM_HXX
#include <bf_svx/frmdiritem.hxx>
#endif

#include "sdresid.hxx"
#include "drawdoc.hxx"
#include "sdpage.hxx"
#include "glob.hrc"
#include "glob.hxx"
#include "stlpool.hxx"
#include "helpids.h"
#include "sdiocmpt.hxx"
namespace binfilter {

using namespace ::rtl;
using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::linguistic2;

/*************************************************************************
|*
|* CreateLayoutTemplates, Layoutvorlagen erzeugen
|*
|* Z.Zt. (31.03.95) speichert der StyleSheetPool nur diejenigen Sheets, die
|* ein ItemSet haben. Damit alle Sheets gespeichert werden, wird die ItemSet-
|* Erzeugung mit einem GetItemSet-Aufruf erzwungen.
|* Dies kann entfallen, sobald der Pool auch Sheets ohne ItemSet speichert.
|*
\************************************************************************/

/*N*/ void SdDrawDocument::CreateLayoutTemplates()
/*N*/ {
/*N*/   SdStyleSheetPool*       pStyleSheetPool = (SdStyleSheetPool*)GetStyleSheetPool();
/*N*/   SfxStyleSheetBase*      pSheet = NULL;
/*N*/   String                  aHelpFile;
/*N*/   String                  aStdName = String(SdResId(STR_STANDARD_STYLESHEET_NAME));
/*N*/
/*N*/   // ---- Standardvorlage -----------------------------------------------
/*N*/
/*N*/   // nicht benutzt, nicht benutzerdefiniert
/*N*/   // SB hatte wahrscheinlich Probleme mit SFXSTYLEBIT_AUTO, da dann gar nichts
/*N*/   // mehr im Gestalter angezeigt wird. Dieses Problem ist zu 364 j behoben worden
/*N*/   // USHORT nMask = SFXSTYLEBIT_ALL & ~(SFXSTYLEBIT_USED | SFXSTYLEBIT_USERDEF);
/*N*/   USHORT nMask = SFXSTYLEBIT_AUTO;
/*N*/
/*N*/   String aName(aStdName);
/*N*/   pSheet = &(pStyleSheetPool->Make(aName, SFX_STYLE_FAMILY_PARA, nMask));
/*N*/   pSheet->SetHelpId( aHelpFile, HID_STANDARD_STYLESHEET_NAME );
/*N*/   SfxItemSet& rISet = pSheet->GetItemSet();
/*N*/   SfxItemPool* pPool = rISet.GetPool();
/*N*/
/*N*/   String   aNullStr;
/*N*/
/*N*/   XPolygon aNullPol;
/*N*/   Color    aNullCol(RGB_Color(COL_BLACK));
/*N*/
/*N*/   XDash     aNullDash;
/*N*/   XGradient aNullGrad(aNullCol,RGB_Color(COL_WHITE));
/*N*/             aNullGrad.SetStartIntens( 100 );
/*N*/             aNullGrad.SetEndIntens( 100 );
/*N*/   XHatch    aNullHatch(aNullCol);
/*N*/
/*N*/                   // Linienattribute (Extended OutputDevice)
/*N*/   rISet.Put(XLineStyleItem(XLINE_SOLID));
/*N*/   rISet.Put(XLineColorItem(String(), RGB_Color(COL_BLACK)));
/*N*/   rISet.Put(XLineWidthItem(0));
/*N*/   rISet.Put(XLineDashItem(pPool,aNullDash));
/*N*/   rISet.Put(XLineStartItem(pPool,aNullPol));
/*N*/   rISet.Put(XLineEndItem(pPool,aNullPol));
/*N*/   rISet.Put(XLineStartWidthItem(300));
/*N*/   rISet.Put(XLineEndWidthItem(300));
/*N*/   rISet.Put(XLineStartCenterItem());
/*N*/   rISet.Put(XLineEndCenterItem());
/*N*/
/*N*/                   // Fuellattribute (Extended OutputDevice)
/*N*/   rISet.Put(XFillStyleItem(XFILL_SOLID));
/*N*/   rISet.Put(XFillColorItem(String(), Color(0,184,255))); // "Blau 7"
/*N*/
/*N*/   rISet.Put(XFillGradientItem(pPool,aNullGrad));
/*N*/   rISet.Put(XFillHatchItem(pPool,aNullHatch));
/*N*/ #ifndef SVX_LIGHT
/*N*/     Size    aNullSize( 32, 32 );
/*N*/     Color   aNullColor( COL_WHITE );
/*N*/   Bitmap  aNullBmp( aNullSize, 8 );
/*N*/     aNullBmp.Erase( aNullColor );
/*N*/   rISet.Put(XFillBitmapItem(pPool,aNullBmp));
/*N*/ #else
/*N*/   // leave it empty to avoid resource usage
/*N*/   rISet.Put(XFillBitmapItem());
/*N*/ #endif
/*N*/
/*N*/                   // Schattenattribute (Drawing Engine)
/*N*/   rISet.Put(SdrShadowItem(FALSE));
/*N*/   rISet.Put(SdrShadowColorItem(aNullStr, RGB_Color(COL_GRAY)));
/*N*/   rISet.Put(SdrShadowXDistItem(300));         // 3 mm Schattendistanz
/*N*/   rISet.Put(SdrShadowYDistItem(300));
/*N*/
/*N*/   Font aLatinFont, aCJKFont, aCTLFont;
/*N*/
/*N*/   getDefaultFonts( aLatinFont, aCJKFont, aCTLFont );
/*N*/
/*N*/   SvxFontItem aSvxFontItem( aLatinFont.GetFamily(), aLatinFont.GetName(), aLatinFont.GetStyleName(), aLatinFont.GetPitch(),
/*N*/                             aLatinFont.GetCharSet(), EE_CHAR_FONTINFO );
/*N*/
/*N*/   SvxFontItem aSvxFontItemCJK( aCJKFont.GetFamily(), aCJKFont.GetName(), aCJKFont.GetStyleName(), aCJKFont.GetPitch(),
/*N*/                                aCJKFont.GetCharSet(), EE_CHAR_FONTINFO_CJK );
/*N*/
/*N*/   SvxFontItem aSvxFontItemCTL( aCTLFont.GetFamily(), aCTLFont.GetName(), aCTLFont.GetStyleName(), aCTLFont.GetPitch(),
/*N*/                                aCTLFont.GetCharSet(), EE_CHAR_FONTINFO_CTL );
/*N*/
/*N*/   rISet.Put( aSvxFontItem );
/*N*/   rISet.Put( aSvxFontItemCJK );
/*N*/   rISet.Put( aSvxFontItemCTL );
/*N*/
/*N*/   rISet.Put( SvxFontHeightItem( 846, 100, EE_CHAR_FONTHEIGHT ) );     // 24 pt
/*N*/   rISet.Put( SvxFontHeightItem( 846, 100, EE_CHAR_FONTHEIGHT_CJK ) ); // 24 pt
/*N*/   rISet.Put( SvxFontHeightItem( 846, 100, EE_CHAR_FONTHEIGHT_CTL ) ); // 24 pt
/*N*/
/*N*/   rISet.Put( SvxWeightItem( WEIGHT_NORMAL, EE_CHAR_WEIGHT ) );
/*N*/   rISet.Put( SvxWeightItem( WEIGHT_NORMAL, EE_CHAR_WEIGHT_CJK ) );
/*N*/   rISet.Put( SvxWeightItem( WEIGHT_NORMAL, EE_CHAR_WEIGHT_CTL ) );
/*N*/
/*N*/   rISet.Put( SvxPostureItem( ITALIC_NONE, EE_CHAR_ITALIC ) );
/*N*/   rISet.Put( SvxPostureItem( ITALIC_NONE, EE_CHAR_ITALIC_CJK ) );
/*N*/   rISet.Put( SvxPostureItem( ITALIC_NONE, EE_CHAR_ITALIC_CTL ) );
/*N*/
/*N*/   rISet.Put(SvxContourItem(FALSE));
/*N*/   rISet.Put(SvxShadowedItem(FALSE));
/*N*/   rISet.Put(SvxUnderlineItem(UNDERLINE_NONE));
/*N*/   rISet.Put(SvxCrossedOutItem(STRIKEOUT_NONE));
/*N*/   rISet.Put(SvxEmphasisMarkItem(EMPHASISMARK_NONE));
/*N*/   rISet.Put(SvxCharReliefItem(RELIEF_NONE));
/*N*/   rISet.Put(SvxColorItem(Color(COL_AUTO)));
/*N*/
/*N*/     // Absatzattribute (Edit Engine)
/*N*/   rISet.Put(SvxLRSpaceItem());
/*N*/   rISet.Put(SvxULSpaceItem());

    // only change paragraph text direction,
    // if this is a new document and
    // text direction is set explicitly to RTL
/*
    if( pDocSh &&
        pDocSh->IsNewDocument() &&
        SD_MOD()->GetDefaultWritingMode() == ::com::sun::star::text::WritingMode_RL_TB )
    {
        SvxAdjustItem           aAdjust( SVX_ADJUST_RIGHT );
        SvxFrameDirectionItem   aFrameDirectionItem( FRMDIR_HORI_RIGHT_TOP, EE_PARA_WRITINGDIR );

        rISet.Put( aAdjust );
        rISet.Put( aFrameDirectionItem );

        pItemPool->SetPoolDefaultItem( aAdjust );
        pItemPool->SetPoolDefaultItem( aFrameDirectionItem );
    }
    else
        rISet.Put( SvxAdjustItem() );
*/

/*N*/   rISet.Put(SvxLineSpacingItem());
/*N*/
/*N*/   // Bullet
/*N*/   // BulletItem und BulletFont fuer Titel und Gliederung
/*N*/   SvxBulletItem aBulletItem(EE_PARA_BULLET);
/*N*/                           // die sind in allen Ebenen identisch
/*N*/   aBulletItem.SetStyle(BS_BULLET);
/*N*/   aBulletItem.SetStart(1);
/*N*/   aBulletItem.SetScale(45);           // in Prozent
/*N*/
/*N*/   Font aBulletFont( pStyleSheetPool->GetBulletFont() );
/*N*/   aBulletFont.SetSize(Size(0,846));       // 24 pt
/*N*/   aBulletItem.SetFont(aBulletFont);
/*N*/   aBulletItem.SetSymbol( 0x25CF );                    // Punkt
/*N*/   rISet.Put(aBulletItem);
/*N*/
/*N*/   SfxUInt16Item aBulletStateItem(EE_PARA_BULLETSTATE, 0); // Bullets nicht sichtbar
/*N*/   rISet.Put(aBulletStateItem);
/*N*/
/*N*/   // Neues BulletItem
/*N*/   pStyleSheetPool->PutNumBulletItem( pSheet, aBulletFont );
/*N*/
/*N*/   SfxItemSet* pISet = NULL;
/*N*/
/*N*/   // ---- Objekt mit Pfeilspitze ----------------------------------------
/*N*/
/*N*/   aName = String(SdResId(STR_POOLSHEET_OBJWITHARROW));
/*N*/   pSheet = &(pStyleSheetPool->Make(aName, SFX_STYLE_FAMILY_PARA, nMask));
/*N*/   pSheet->SetParent(aStdName);
/*N*/   pSheet->SetHelpId( aHelpFile, HID_POOLSHEET_OBJWITHARROW );
/*N*/   pISet = &pSheet->GetItemSet();
/*N*/
/*N*/   pISet->Put(XLineStyleItem(XLINE_SOLID));
/*N*/   pISet->Put(XLineColorItem(String(), RGB_Color(COL_BLACK)));
/*N*/   pISet->Put(XLineWidthItem(150));
/*N*/
/*N*/   XPolygon aArrow(4);                          //      []
/*N*/   aArrow[0]=Point(10,0);                        // 0,4__[]__2,4
/*N*/   aArrow[1]=Point(0,30);                      //    \    /
/*N*/   aArrow[2]=Point(20,30);                        //     \  /
/*N*/   aArrow[3]=Point(10,0);                        //      \/1,0
/*N*/ #ifdef SVX_LIGHT
/*N*/   pISet->Put(XLineStartItem(SdResId(STR_POOLSHEET_ARROW),aArrow));
/*N*/ #else
/*N*/   pISet->Put(XLineStartItem(SVX_RESSTR(RID_SVXSTR_ARROW),aArrow));
/*N*/ #endif
/*N*/
/*N*/   pISet->Put(XLineStartWidthItem(700));
/*N*/   pISet->Put(XLineEndWidthItem(300));
/*N*/   pISet->Put(XLineStartCenterItem(TRUE));
/*N*/
/*N*/   // ---- Objekt mit Schatten -------------------------------------------
/*N*/
/*N*/   aName = String(SdResId(STR_POOLSHEET_OBJWITHSHADOW));
/*N*/   pSheet = &(pStyleSheetPool->Make(aName, SFX_STYLE_FAMILY_PARA, nMask));
/*N*/   pSheet->SetParent(aStdName);
/*N*/   pSheet->SetHelpId( aHelpFile, HID_POOLSHEET_OBJWITHSHADOW );
/*N*/   pISet = &pSheet->GetItemSet();
/*N*/
/*N*/   pISet->Put(SdrShadowItem(TRUE));
/*N*/   pISet->Put(SdrShadowColorItem(aNullStr, RGB_Color(COL_GRAY)));
/*N*/   pISet->Put(SdrShadowXDistItem(300));        // 3 mm Schattendistanz
/*N*/   pISet->Put(SdrShadowYDistItem(300));
/*N*/
/*N*/   // ---- Objekt ohne Fllung -------------------------------------------
/*N*/
/*N*/   aName = String(SdResId(STR_POOLSHEET_OBJWITHOUTFILL));
/*N*/   pSheet = &(pStyleSheetPool->Make(aName, SFX_STYLE_FAMILY_PARA, nMask));
/*N*/   pSheet->SetParent(aStdName);
/*N*/   pSheet->SetHelpId( aHelpFile, HID_POOLSHEET_OBJWITHOUTFILL );
/*N*/   pISet = &pSheet->GetItemSet();
/*N*/
/*N*/   pISet->Put(XFillStyleItem(XFILL_NONE));
/*N*/
/*N*/   // ---- Text ----------------------------------------------------------
/*N*/
/*N*/   aName = String(SdResId(STR_POOLSHEET_TEXT));
/*N*/   pSheet = &(pStyleSheetPool->Make(aName, SFX_STYLE_FAMILY_PARA, nMask));
/*N*/   pSheet->SetParent(aStdName);
/*N*/   pSheet->SetHelpId( aHelpFile, HID_POOLSHEET_TEXT );
/*N*/   pISet = &pSheet->GetItemSet();
/*N*/
/*N*/   pISet->Put(XLineStyleItem(XLINE_NONE));
/*N*/   pISet->Put(XFillStyleItem(XFILL_NONE));
/*N*/
/*N*/   // ---- Textk”rper ----------------------------------------------------
/*N*/
/*N*/   aName = String(SdResId(STR_POOLSHEET_TEXTBODY));
/*N*/   pSheet = &(pStyleSheetPool->Make(aName, SFX_STYLE_FAMILY_PARA, nMask));
/*N*/   pSheet->SetParent(aStdName);
/*N*/   pSheet->SetHelpId( aHelpFile, HID_POOLSHEET_TEXTBODY );
/*N*/   pISet = &pSheet->GetItemSet();
/*N*/
/*N*/   pISet->Put(XLineStyleItem(XLINE_NONE));
/*N*/   pISet->Put(XFillStyleItem(XFILL_NONE));
/*N*/
/*N*/   pISet->Put(SvxFontHeightItem(564));         // 16 pt
/*N*/
/*N*/   // ---- Textk”rper mit Blocksatz --------------------------------------
/*N*/
/*N*/   aName = String(SdResId(STR_POOLSHEET_TEXTBODY_JUSTIFY));
/*N*/   pSheet = &(pStyleSheetPool->Make(aName, SFX_STYLE_FAMILY_PARA, nMask));
/*N*/   pSheet->SetParent(aStdName);
/*N*/   pSheet->SetHelpId( aHelpFile, HID_POOLSHEET_TEXTBODY_JUSTIFY );
/*N*/   pISet = &pSheet->GetItemSet();
/*N*/
/*N*/   pISet->Put(XLineStyleItem(XLINE_NONE));
/*N*/   pISet->Put(XFillStyleItem(XFILL_NONE));
/*N*/
/*N*/   pISet->Put(SvxAdjustItem(SVX_ADJUST_BLOCK));
/*N*/
/*N*/   // ---- Textkoerper mit Einzug -----------------------------------------
/*N*/
/*N*/   aName = String(SdResId(STR_POOLSHEET_TEXTBODY_INDENT));
/*N*/   pSheet = &(pStyleSheetPool->Make(aName, SFX_STYLE_FAMILY_PARA, nMask));
/*N*/   pSheet->SetParent(aStdName);
/*N*/   pSheet->SetHelpId( aHelpFile, HID_POOLSHEET_TEXTBODY_INDENT );
/*N*/   pISet = &pSheet->GetItemSet();
/*N*/
/*N*/   pISet->Put(XLineStyleItem(XLINE_NONE));
/*N*/   pISet->Put(XFillStyleItem(XFILL_NONE));
/*N*/
/*N*/   SvxLRSpaceItem aLRSpaceItem;
/*N*/   aLRSpaceItem.SetTxtFirstLineOfst(600);      // Erstzeileneinzug 6mm, rechts 0
/*N*/   pISet->Put(aLRSpaceItem);
/*N*/
/*N*/   // SvxLRSpaceItem hart gesetzt: NumBulletItem anpassen
/*N*/   SvxNumBulletItem aNumBullet( (const SvxNumBulletItem&) pISet->Get(EE_PARA_NUMBULLET) );
/*N*/   EditEngine::ImportBulletItem( aNumBullet, 0, NULL, &aLRSpaceItem );
/*N*/   pISet->Put( aNumBullet );
/*N*/
/*N*/   // ---- Titel ---------------------------------------------------------
/*N*/
/*N*/   aName = String(SdResId(STR_POOLSHEET_TITLE));
/*N*/   pSheet = &(pStyleSheetPool->Make(aName, SFX_STYLE_FAMILY_PARA, nMask));
/*N*/   pSheet->SetParent(aStdName);
/*N*/   pSheet->SetHelpId( aHelpFile, HID_POOLSHEET_TITLE );
/*N*/   pISet = &pSheet->GetItemSet();
/*N*/
/*N*/   pISet->Put(XLineStyleItem(XLINE_NONE));
/*N*/   pISet->Put(XFillStyleItem(XFILL_NONE));
/*N*/
/*N*/   pISet->Put(SvxFontHeightItem(1551));        // 44 pt
/*N*/
/*N*/   // ---- Titel1 --------------------------------------------------------
/*N*/
/*N*/   aName = String(SdResId(STR_POOLSHEET_TITLE1));
/*N*/   pSheet = &(pStyleSheetPool->Make(aName, SFX_STYLE_FAMILY_PARA, nMask));
/*N*/   pSheet->SetParent(aStdName);
/*N*/   pSheet->SetHelpId( aHelpFile, HID_POOLSHEET_TITLE1 );
/*N*/   pISet = &pSheet->GetItemSet();
/*N*/
/*N*/   pISet->Put(XLineStyleItem(XLINE_NONE));
/*N*/   pISet->Put(XFillStyleItem(XFILL_SOLID));
/*N*/   pISet->Put(XFillColorItem(String(), RGB_Color(COL_CYAN)));
/*N*/
/*N*/   pISet->Put(SdrShadowItem(TRUE));
/*N*/   pISet->Put(SdrShadowColorItem(aNullStr, RGB_Color(COL_GRAY)));
/*N*/   pISet->Put(SdrShadowXDistItem(200));        // 2 mm Schattendistanz
/*N*/   pISet->Put(SdrShadowYDistItem(200));
/*N*/
/*N*/   pISet->Put(SvxFontHeightItem(846));         // 24 pt
/*N*/
/*N*/   pISet->Put(SvxAdjustItem(SVX_ADJUST_CENTER));
/*N*/
/*N*/   // ---- Titel2 --------------------------------------------------------
/*N*/
/*N*/   aName = String(SdResId(STR_POOLSHEET_TITLE2));
/*N*/   pSheet = &(pStyleSheetPool->Make(aName, SFX_STYLE_FAMILY_PARA, nMask));
/*N*/   pSheet->SetParent(aStdName);
/*N*/   pSheet->SetHelpId( aHelpFile, HID_POOLSHEET_TITLE2 );
/*N*/   pISet = &pSheet->GetItemSet();
/*N*/
/*N*/   pISet->Put(XLineWidthItem(50));
/*N*/
/*N*/   // Farbe nicht aus der Farbtabelle holen, denn da kann diese Farbe
/*N*/   // geloescht oder veraendert sein
/*N*/   Color aOrange4(255, 204, 153);
/*N*/   pISet->Put(XFillColorItem(String(), aOrange4));
/*N*/
/*N*/   pISet->Put(SdrShadowItem(TRUE));
/*N*/   pISet->Put(SdrShadowColorItem(aNullStr, RGB_Color(COL_GRAY)));
/*N*/   pISet->Put(SdrShadowXDistItem(200));        // 2 mm Schattendistanz
/*N*/   pISet->Put(SdrShadowYDistItem(200));
/*N*/
/*N*/   pISet->Put(SvxFontHeightItem(1270));        // 36 pt
/*N*/
/*N*/   SvxLRSpaceItem aLRSpItem(0, 200, 200);
/*N*/   pISet->Put( aLRSpItem );    // Erstzeileneinzug 0 mm, links und rechts 2 mm
/*N*/   // SvxLRSpaceItem hart gesetzt: NumBulletItem anpassen
/*N*/   SvxNumBulletItem aNmBullet( (const SvxNumBulletItem&) pISet->Get(EE_PARA_NUMBULLET) );
/*N*/   EditEngine::ImportBulletItem( aNmBullet, 0, NULL, &aLRSpItem );
/*N*/   pISet->Put( aNmBullet );
/*N*/
/*N*/   pISet->Put(SvxULSpaceItem(100, 100));       // Absatzrand oben/unten 1 mm
/*N*/
/*N*/   pISet->Put(SvxAdjustItem(SVX_ADJUST_CENTER));
/*N*/
/*N*/   // ---- Ueberschrift ---------------------------------------------------
/*N*/
/*N*/   aName = String(SdResId(STR_POOLSHEET_HEADLINE));
/*N*/   pSheet = &(pStyleSheetPool->Make(aName, SFX_STYLE_FAMILY_PARA, nMask));
/*N*/   pSheet->SetParent(aStdName);
/*N*/   pSheet->SetHelpId( aHelpFile, HID_POOLSHEET_HEADLINE );
/*N*/   pISet = &pSheet->GetItemSet();
/*N*/
/*N*/   pISet->Put(XLineStyleItem(XLINE_NONE));
/*N*/   pISet->Put(XFillStyleItem(XFILL_NONE));
/*N*/
/*N*/   pISet->Put(SvxFontHeightItem(846));         // 24 pt
/*N*/
/*N*/   pISet->Put(SvxULSpaceItem(420, 210));       // Absatzrand oben 4,2 mm,
/*N*/                                               // unten 2,1 mm
/*N*/
/*N*/   // ---- Ueberschrift1 --------------------------------------------------
/*N*/
/*N*/   aName = String(SdResId(STR_POOLSHEET_HEADLINE1));
/*N*/   pSheet = &(pStyleSheetPool->Make(aName, SFX_STYLE_FAMILY_PARA, nMask));
/*N*/   pSheet->SetParent(aStdName);
/*N*/   pSheet->SetHelpId( aHelpFile, HID_POOLSHEET_HEADLINE1 );
/*N*/   pISet = &pSheet->GetItemSet();
/*N*/
/*N*/   pISet->Put(XLineStyleItem(XLINE_NONE));
/*N*/   pISet->Put(XFillStyleItem(XFILL_NONE));
/*N*/
/*N*/   pISet->Put(SvxWeightItem(WEIGHT_BOLD));
/*N*/
/*N*/   pISet->Put(SvxFontHeightItem(635));         // 18 pt
/*N*/
/*N*/   pISet->Put(SvxULSpaceItem(420, 210));       // Absatzrand oben 4,2 mm,
/*N*/                                               // unten 2,1 mm
/*N*/
/*N*/   // ---- Ueberschrift2 --------------------------------------------------
/*N*/
/*N*/   aName = String(SdResId(STR_POOLSHEET_HEADLINE2));
/*N*/   pSheet = &(pStyleSheetPool->Make(aName, SFX_STYLE_FAMILY_PARA, nMask));
/*N*/   pSheet->SetParent(aStdName);
/*N*/   pSheet->SetHelpId( aHelpFile, HID_POOLSHEET_HEADLINE2 );
/*N*/   pISet = &pSheet->GetItemSet();
/*N*/
/*N*/   pISet->Put(XLineStyleItem(XLINE_NONE));
/*N*/   pISet->Put(XFillStyleItem(XFILL_NONE));
/*N*/
/*N*/   pISet->Put(SvxPostureItem(ITALIC_NORMAL));
/*N*/   pISet->Put(SvxWeightItem(WEIGHT_BOLD));
/*N*/
/*N*/   pISet->Put(SvxFontHeightItem(494));         // 14 pt
/*N*/
/*N*/   pISet->Put(SvxULSpaceItem(420, 210));       // Absatzrand oben 4,2 mm,
/*N*/                                               // unten 2,1 mm
/*N*/
/*N*/   // ---- Bemassung --------------------------------------------------
/*N*/
/*N*/   aName = String(SdResId(STR_POOLSHEET_MEASURE));
/*N*/   pSheet = &(pStyleSheetPool->Make(aName, SFX_STYLE_FAMILY_PARA, nMask));
/*N*/   pSheet->SetParent(aStdName);
/*N*/   pSheet->SetHelpId( aHelpFile, HID_POOLSHEET_MEASURE );
/*N*/   pISet = &pSheet->GetItemSet();
/*N*/
/*N*/   pISet->Put(XFillStyleItem(XFILL_NONE));
/*N*/
/*N*/   pISet->Put(SvxFontHeightItem(423));         // 12 pt
/*N*/
/*N*/ #ifdef SVX_LIGHT
/*N*/   // avoid SVX resources
/*N*/   pISet->Put(XLineStartItem(SdResId(STR_POOLSHEET_ARROW),aArrow));
/*N*/ #else
/*N*/   pISet->Put(XLineStartItem(SVX_RESSTR(RID_SVXSTR_ARROW),aArrow));
/*N*/ #endif
/*N*/   pISet->Put(XLineStartWidthItem(200));
/*N*/ #ifdef SVX_LIGHT
/*N*/   pISet->Put(XLineEndItem(SdResId(STR_POOLSHEET_ARROW),aArrow));
/*N*/ #else
/*N*/   pISet->Put(XLineEndItem(SVX_RESSTR(RID_SVXSTR_ARROW),aArrow));
/*N*/ #endif
/*N*/   pISet->Put(XLineEndWidthItem(200));
/*N*/   pISet->Put(XLineStyleItem(XLINE_SOLID));
/*N*/
/*

    invalidierte Items koennen nicht gespeichert werden;
    da muessen wir uns was anderes ueberlegen

    // ---- leere Vorlage --------------------------------------------------

    aName = String(SdResId(STR_EMPTY_STYLESHEET_NAME));
    pSheet = &(pStyleSheetPool->Make(aName, SFX_STYLE_FAMILY_PARA, nMask));
    pISet = &pSheet->GetItemSet();
    pISet->InvalidateAllItems();      // alle auf DONTCARE setzen
*/
/*N*/
/*N*/
/*N*/   // Praesentationsvorlagen fuer das Standardlayout erzeugen
/*N*/   String aPrefix = String(SdResId(STR_LAYOUT_DEFAULT_NAME));
/*N*/   pStyleSheetPool->CreateLayoutStyleSheets(aPrefix);
/*N*/ }


/*************************************************************************
|*
|* Anzahl der Seiten, die eine masterPage referenzieren
|*
\************************************************************************/

/*N*/ USHORT SdDrawDocument::GetMasterPageUserCount(SdrPage* pMaster) const
/*N*/ {
/*N*/   USHORT nResult = 0;
/*N*/   USHORT nPage;
/*N*/   USHORT nPageCount = GetPageCount();
/*N*/
/*N*/   for (nPage = 0; nPage < nPageCount; nPage++)
/*N*/   {
/*N*/       const SdrPage* pPage = GetPage(nPage);
/*N*/       for (USHORT nPos = 0; nPos < pPage->GetMasterPageCount(); nPos++)
/*N*/       {
/*N*/           if (pMaster == pPage->GetMasterPage(nPos))
/*N*/           {
/*N*/               nResult++;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   return nResult;
/*N*/ }


/*************************************************************************
|*
|* OnlineSpelling im Hintergrund beenden
|*
\************************************************************************/

/*N*/ #ifndef SVX_LIGHT
/*N*/ void SdDrawDocument::StopOnlineSpelling()
/*N*/ {
/*N*/   if (pOnlineSpellingTimer && pOnlineSpellingTimer->IsActive())
/*?*/   {
/*?*/       pOnlineSpellingTimer->Stop();
/*?*/   }

/*N*/   delete pOnlineSpellingTimer;
/*N*/   pOnlineSpellingTimer = NULL;

/*N*/   delete pOnlineSpellingList;
/*N*/   pOnlineSpellingList = NULL;
/*N*/ }
/*N*/ #endif // !SVX_LIGHT


/*************************************************************************
|*
|* OnlineSpelling im Hintergrund starten
|*
\************************************************************************/

/*N*/ #ifndef SVX_LIGHT
/*N*/ void SdDrawDocument::StartOnlineSpelling(BOOL bForceSpelling)
/*N*/ {
/*N*/   if (bOnlineSpell && (bForceSpelling || bInitialOnlineSpellingEnabled) &&
/*N*/       pDocSh && !pDocSh->IsReadOnly() )
/*?*/   {
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 StopOnlineSpelling();
//STRIP001
//STRIP001 /*?*/        SdOutliner* pOutl = GetInternalOutliner(TRUE);
//STRIP001
//STRIP001 /*?*/        Reference< XSpellChecker1 > xSpellChecker( LinguMgr::GetSpellChecker() );
//STRIP001 /*?*/        if ( xSpellChecker.is() )
//STRIP001 /*?*/            pOutl->SetSpeller( xSpellChecker );
//STRIP001
//STRIP001 /*?*/        Reference< XHyphenator > xHyphenator( LinguMgr::GetHyphenator() );
//STRIP001 /*?*/        if( xHyphenator.is() )
//STRIP001 /*?*/            pOutl->SetHyphenator( xHyphenator );
//STRIP001
//STRIP001 /*?*/        pOutl->SetDefaultLanguage( eLanguage );
//STRIP001
//STRIP001 /*?*/        SdPage* pPage = NULL;
//STRIP001 /*?*/        SdrObject* pObj = NULL;
//STRIP001 /*?*/        pOnlineSpellingList = new List(64, 32);
//STRIP001
//STRIP001      // Um im OnlineSpellingHdl mit List::Next() arbeiten zu  koennen,
//STRIP001      // wird ein Position 0 ein Dummy-Objekt (NULL-Pointer) eingefuegt
//STRIP001 /*?*/        pOnlineSpellingList->Insert(NULL, LIST_APPEND);
//STRIP001
//STRIP001 /*?*/        for (USHORT nPage = 0; nPage < GetPageCount(); nPage++)
//STRIP001 /*?*/        {
//STRIP001          // Alle Pages durchsuchen
//STRIP001 /*?*/            DBG_BF_ASSERT(0, "STRIP"); //STRIP001 FillOnlineSpellingList((SdPage*) GetPage(nPage));
//STRIP001 /*?*/        }
//STRIP001
//STRIP001 /*?*/        for (nPage = 0; nPage < GetMasterPageCount(); nPage++)
//STRIP001 /*?*/        {
//STRIP001          // Alle MasterPages durchsuchen
//STRIP001 /*?*/            FillOnlineSpellingList((SdPage*) GetMasterPage(nPage));
//STRIP001 /*?*/        }
//STRIP001
//STRIP001 /*?*/        pOnlineSpellingList->Seek(ULONG(0));
//STRIP001 /*?*/        pOnlineSpellingTimer = new Timer();
//STRIP001 /*?*/        pOnlineSpellingTimer->SetTimeoutHdl( LINK(this, SdDrawDocument, OnlineSpellingHdl) );
//STRIP001 /*?*/        pOnlineSpellingTimer->SetTimeout(250);
//STRIP001 /*?*/        pOnlineSpellingTimer->Start();
/*?*/   }
/*N*/ }
/*N*/ #endif // !SVX_LIGHT


/*************************************************************************
|*
|* OnlineSpelling-Liste fuellen
|*
\************************************************************************/

//STRIP001 #ifndef SVX_LIGHT
//STRIP001 void SdDrawDocument::FillOnlineSpellingList(SdPage* pPage)
//STRIP001 {
//STRIP001  SdrObject* pObj = NULL;
//STRIP001  SdrObjListIter aIter(*pPage, IM_FLAT);
//STRIP001
//STRIP001  while (aIter.IsMore())
//STRIP001  {
//STRIP001      pObj = aIter.Next();
//STRIP001
//STRIP001      if (pObj->GetOutlinerParaObject())
//STRIP001      {
//STRIP001          // Textobjekt gefunden
//STRIP001          pOnlineSpellingList->Insert(pObj, LIST_APPEND);
//STRIP001      }
//STRIP001      else if (pObj->GetObjIdentifier() == OBJ_GRUP)
//STRIP001      {
//STRIP001          // Gruppenobjekt gefunden
//STRIP001          SdrObjListIter aGroupIter(*((SdrObjGroup*)pObj)->GetSubList(),
//STRIP001                                    IM_DEEPNOGROUPS);
//STRIP001
//STRIP001          BOOL bSubTextObjFound = FALSE;
//STRIP001
//STRIP001          while (aGroupIter.IsMore() && !bSubTextObjFound)
//STRIP001          {
//STRIP001              if (aGroupIter.Next()->GetOutlinerParaObject())
//STRIP001              {
//STRIP001                  // Textobjekt im Gruppenobjekt gefunden
//STRIP001                  bSubTextObjFound = TRUE;
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          if (bSubTextObjFound)
//STRIP001          {
//STRIP001              pOnlineSpellingList->Insert(pObj, LIST_APPEND);
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }
//STRIP001 #endif // !SVX_LIGHT


/*************************************************************************
|*
|* OnlineSpelling im Hintergrund
|*
\************************************************************************/

//STRIP001 #ifndef SVX_LIGHT
//STRIP001 IMPL_LINK(SdDrawDocument, OnlineSpellingHdl, Timer*, pTimer)
//STRIP001 {
//STRIP001  if (pOnlineSpellingList!=NULL
//STRIP001         && ( !bOnlineSpell ||
//STRIP001             pOnlineSpellingList->GetCurPos() < pOnlineSpellingList->Count() + 1))
//STRIP001  {
//STRIP001      /**********************************************************************
//STRIP001      * Naechstes Objekt spellen
//STRIP001      **********************************************************************/
//STRIP001      SdrObject* pObj = (SdrObject*) pOnlineSpellingList->Next();
//STRIP001
//STRIP001      if (pObj)
//STRIP001      {
//STRIP001          if (pObj->GetOutlinerParaObject() && pObj->ISA(SdrTextObj))
//STRIP001          {
//STRIP001              // Textobjekt spellen
//STRIP001              SpellObject((SdrTextObj*) pObj);
//STRIP001          }
//STRIP001          else if (pObj->GetObjIdentifier() == OBJ_GRUP)
//STRIP001          {
//STRIP001              // Gruppenobjekt gefunden
//STRIP001              SdrObjListIter aGroupIter(*((SdrObjGroup*)pObj)->GetSubList(),
//STRIP001                                        IM_DEEPNOGROUPS);
//STRIP001
//STRIP001              SdrObject* pSubObj = NULL;
//STRIP001
//STRIP001              while (aGroupIter.IsMore())
//STRIP001              {
//STRIP001                  pSubObj = aGroupIter.Next();
//STRIP001
//STRIP001                  if (pSubObj->GetOutlinerParaObject() && pSubObj->ISA(SdrTextObj))
//STRIP001                  {
//STRIP001                      // Textobjekt im Gruppenobjekt gefunden
//STRIP001                      SpellObject((SdrTextObj*) pSubObj);
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      // Weitersuchen
//STRIP001      pOnlineSpellingTimer->Start();
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      // Spelling wurde initial durchgefuehrt
//STRIP001      bInitialOnlineSpellingEnabled = FALSE;
//STRIP001
//STRIP001      // Suche beenden
//STRIP001      StopOnlineSpelling();
//STRIP001
//STRIP001      delete pOnlineSearchItem;
//STRIP001      pOnlineSearchItem = NULL;
//STRIP001  }
//STRIP001
//STRIP001  return(0);
//STRIP001 }
//STRIP001 #endif // !SVX_LIGHT


/*************************************************************************
|*
|* Objekt spellen (fuer OnlineSpelling)
|*
\************************************************************************/

//STRIP001 #ifndef SVX_LIGHT
//STRIP001 void SdDrawDocument::SpellObject(SdrTextObj* pObj)
//STRIP001 {
//STRIP001  if (pObj && pObj->GetOutlinerParaObject() /* && pObj != pView->GetTextEditObject() */)
//STRIP001  {
//STRIP001      bHasOnlineSpellErrors = FALSE;
//STRIP001      SdOutliner* pOutl = GetInternalOutliner(TRUE);
//STRIP001      pOutl->SetUpdateMode(TRUE);
//STRIP001      Link aEvtHdl = pOutl->GetStatusEventHdl();
//STRIP001      pOutl->SetStatusEventHdl(LINK(this, SdDrawDocument, OnlineSpellEventHdl));
//STRIP001
//STRIP001      USHORT nOldOutlMode = pOutl->GetMode();
//STRIP001      USHORT nOutlMode = OUTLINERMODE_TEXTOBJECT;
//STRIP001      if (((SdrTextObj*) pObj)->GetObjInventor() == SdrInventor &&
//STRIP001          ((SdrTextObj*) pObj)->GetObjIdentifier() == OBJ_OUTLINETEXT)
//STRIP001      {
//STRIP001          nOutlMode = OUTLINERMODE_OUTLINEOBJECT;
//STRIP001          pOutl->SetMinDepth(1);
//STRIP001      }
//STRIP001      pOutl->Init( nOutlMode );
//STRIP001
//STRIP001      // Text in den Outliner setzen
//STRIP001      pOutl->SetText(*((SdrTextObj*) pObj)->GetOutlinerParaObject());
//STRIP001
//STRIP001      if (!pOnlineSearchItem || pOutl->HasText(*pOnlineSearchItem))
//STRIP001      {
//STRIP001          // Spelling
//STRIP001          pOutl->CompleteOnlineSpelling();
//STRIP001
//STRIP001          if (bHasOnlineSpellErrors)
//STRIP001          {
//STRIP001              // Text aus Outliner holen
//STRIP001              BOOL bModified = IsChanged();
//STRIP001              ((SdrTextObj*) pObj)->SetOutlinerParaObject( pOutl->CreateParaObject() );
//STRIP001              SetChanged(bModified);
//STRIP001              pObj->SendRepaintBroadcast();
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      pOutl->SetStatusEventHdl(aEvtHdl);
//STRIP001      pOutl->SetUpdateMode(FALSE);
//STRIP001      pOutl->Init( nOldOutlMode );
//STRIP001      bHasOnlineSpellErrors = FALSE;
//STRIP001  }
//STRIP001 }
//STRIP001 #endif // !SVX_LIGHT


/*************************************************************************
|*
|* Objekt wurde ins Model eingefuegt
|*
\************************************************************************/

/*N*/ #ifndef SVX_LIGHT
/*N*/ void SdDrawDocument::InsertObject(SdrObject* pObj, SdPage* pPage)
/*N*/ {
/*N*/   if (pOnlineSpellingList)
/*N*/   {
/*?*/       if (pObj->GetOutlinerParaObject())
/*?*/       {
/*?*/           // Objekt in OnlineSpelling-Liste aufnehmen
/*?*/           pOnlineSpellingList->Insert(pObj, LIST_APPEND);
/*?*/       }
/*N*/   }
/*N*/ }
/*N*/ #endif // !SVX_LIGHT



/*************************************************************************
|*
|* Objekt wurde aus dem Model entfernt
|*
\************************************************************************/

#ifndef SVX_LIGHT
/*N*/ void SdDrawDocument::RemoveObject(SdrObject* pObj, SdPage* pPage)
/*N*/ {
/*N*/   if (pOnlineSpellingList)
/*N*/   {
/*?*/       if (pObj->GetOutlinerParaObject())
/*?*/       {
/*?*/           // Objekt in OnlineSpelling-Liste durch NULL-Pointer ersetzt
/*?*/           pOnlineSpellingList->Replace(NULL, pObj);
/*?*/       }
/*N*/   }
/*N*/ }
#endif // !SVX_LIGHT



/*************************************************************************
|*
|* Callback fuer ExecuteSpellPopup()
|*
\************************************************************************/

//STRIP001 #ifndef SVX_LIGHT
//STRIP001 IMPL_LINK(SdDrawDocument, OnlineSpellEventHdl, EditStatus*, pEditStat)
//STRIP001 {
//STRIP001  ULONG nStat = pEditStat->GetStatusWord();
//STRIP001  bHasOnlineSpellErrors = (nStat & EE_STAT_WRONGWORDCHANGED) != 0;
//STRIP001
//STRIP001  return(0);
//STRIP001 }
//STRIP001 #endif // !SVX_LIGHT


/*************************************************************************
|*
|* Callback fuer ExecuteSpellPopup()
|*
\************************************************************************/

// #91457# removed link and replaced with Imp method
//STRIP001 #ifndef SVX_LIGHT
//STRIP001 void SdDrawDocument::ImpOnlineSpellCallback(SpellCallbackInfo* pInfo, SdrObject* pObj, SdrOutliner* pOutl)
//STRIP001 {
//STRIP001  delete pOnlineSearchItem;
//STRIP001  pOnlineSearchItem = NULL;
//STRIP001
//STRIP001  USHORT nCommand = pInfo->nCommand;
//STRIP001
//STRIP001  if (nCommand == SPELLCMD_IGNOREWORD
//STRIP001      // #91457# restart when add to dictionary takes place, too.
//STRIP001      || nCommand == SPELLCMD_ADDTODICTIONARY)
//STRIP001  {
//STRIP001      if(pObj && pOutl && pObj->ISA(SdrTextObj))
//STRIP001      {
//STRIP001          BOOL bModified(IsChanged());
//STRIP001          ((SdrTextObj*)pObj)->SetOutlinerParaObject(pOutl->CreateParaObject());
//STRIP001          SetChanged(bModified);
//STRIP001          pObj->SendRepaintBroadcast();
//STRIP001      }
//STRIP001
//STRIP001      pOnlineSearchItem = new SvxSearchItem();
//STRIP001      pOnlineSearchItem->SetSearchString(pInfo->aWord);
//STRIP001      StartOnlineSpelling();
//STRIP001  }
//STRIP001  else if (nCommand == SPELLCMD_STARTSPELLDLG)
//STRIP001  {
//STRIP001      SfxViewFrame::Current()->GetDispatcher()->Execute( SID_SPELLING, SFX_CALLMODE_ASYNCHRON );
//STRIP001  }
//STRIP001 }
//STRIP001 #endif // !SVX_LIGHT

/*************************************************************************
|*
|* Sprachabhaengige Namen der StandardLayer durch eindeutigen Namen ersetzen
|*
\************************************************************************/

/*N*/ #ifndef SVX_LIGHT
/*N*/ void SdDrawDocument::MakeUniqueLayerNames()
/*N*/ {
/*N*/   String aLayerLayout(SdResId(STR_LAYER_LAYOUT));
/*N*/   String aLayerBckgrnd(SdResId(STR_LAYER_BCKGRND));
/*N*/   String aLayerBckgrndObj(SdResId(STR_LAYER_BCKGRNDOBJ));
/*N*/   String aLayerControls(SdResId(STR_LAYER_CONTROLS));
/*N*/   String aLayerMeasurelines(SdResId(STR_LAYER_MEASURELINES));
/*N*/   SdrLayerAdmin& rLayerAdmin = GetLayerAdmin();
/*N*/   USHORT nStandardLayer = 5;
/*N*/   USHORT nLayerCount = Min(rLayerAdmin.GetLayerCount(), nStandardLayer);
/*N*/
/*N*/   for (USHORT nLayer = 0; nLayer < nLayerCount; nLayer++)
/*N*/   {
/*N*/       // Die sprachabhaengigen Namen der Default-Layer werden nicht mehr
/*N*/       // gespeichert. Es werden stattdessen eindeutige Namen verwendet.
/*N*/       SdrLayer* pLayer = rLayerAdmin.GetLayer(nLayer);
/*N*/
/*N*/       if (pLayer)
/*N*/       {
/*N*/           String aLayerName(pLayer->GetName());
/*N*/
/*N*/           if (aLayerName == aLayerLayout)
/*N*/           {
/*N*/               pLayer->SetName( String( RTL_CONSTASCII_USTRINGPARAM( "LAYER_LAYOUT" )));
/*N*/           }
/*N*/           else if (aLayerName == aLayerBckgrnd)
/*N*/           {
/*N*/               pLayer->SetName( String( RTL_CONSTASCII_USTRINGPARAM( "LAYER_BCKGRND" )));
/*N*/           }
/*N*/           else if (aLayerName == aLayerBckgrndObj)
/*N*/           {
/*N*/               pLayer->SetName( String( RTL_CONSTASCII_USTRINGPARAM( "LAYER_BACKGRNDOBJ" )));
/*N*/           }
/*N*/           else if (aLayerName == aLayerControls)
/*N*/           {
/*N*/               pLayer->SetName( String( RTL_CONSTASCII_USTRINGPARAM( "LAYER_CONTROLS" )));
/*N*/           }
/*N*/           else if (aLayerName == aLayerMeasurelines)
/*N*/           {
/*N*/               pLayer->SetName( String( RTL_CONSTASCII_USTRINGPARAM( "LAYER_MEASURELINES" )));
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }
/*N*/ #endif // !SVX_LIGHT



/*************************************************************************
|*
|* Eindeutige Namen der StandardLayer durch sprachabhaengige Namen ersetzen
|*
\************************************************************************/

/*N*/ #ifndef SVX_LIGHT
/*N*/ void SdDrawDocument::RestoreLayerNames()
/*N*/ {
/*N*/   SdrLayerAdmin& rLayerAdmin = GetLayerAdmin();
/*N*/   USHORT nLayerCount = rLayerAdmin.GetLayerCount();
/*N*/
/*N*/   if (nFileFormatVersion < 13)
/*N*/   {
/*N*/       USHORT nStandardLayer = 5;
/*N*/       nLayerCount = Min(nLayerCount, nStandardLayer);
/*N*/
/*N*/       for (USHORT nLayer = 0; nLayer < nLayerCount; nLayer++)
/*N*/       {
/*N*/           SdrLayer* pLayer = rLayerAdmin.GetLayer(nLayer);
/*N*/
/*N*/           if (pLayer)
/*N*/           {
/*N*/               String aDefaultLayerName;
/*N*/
/*N*/               if (nLayer == 0)
/*N*/               {
/*N*/                   aDefaultLayerName = String(SdResId(STR_LAYER_LAYOUT));
/*N*/               }
/*N*/               else if (nLayer == 1)
/*N*/               {
/*N*/                   aDefaultLayerName = String(SdResId(STR_LAYER_BCKGRND));
/*N*/               }
/*N*/               else if (nLayer == 2)
/*N*/               {
/*N*/                   aDefaultLayerName = String(SdResId(STR_LAYER_BCKGRNDOBJ));
/*N*/               }
/*N*/               else if (nLayer == 3)
/*N*/               {
/*N*/                   aDefaultLayerName = String(SdResId(STR_LAYER_CONTROLS));
/*N*/               }
/*N*/               else if (nLayer == 4)
/*N*/               {
/*?*/                   aDefaultLayerName = String(SdResId(STR_LAYER_MEASURELINES));
/*N*/               }
/*N*/
/*N*/               if (pLayer->GetName() != aDefaultLayerName)
/*N*/               {
/*N*/                   pLayer->SetName(aDefaultLayerName);
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       for (USHORT nLayer = 0; nLayer < nLayerCount; nLayer++)
/*N*/       {
/*N*/           SdrLayer* pLayer = rLayerAdmin.GetLayer(nLayer);
/*N*/
/*N*/           if (pLayer)
/*N*/           {
/*N*/               String aLayerName(pLayer->GetName());
/*N*/
/*N*/               if (aLayerName.EqualsAscii( "LAYER_LAYOUT" ))
/*N*/               {
/*N*/                   pLayer->SetName(String(SdResId(STR_LAYER_LAYOUT)));
/*N*/               }
/*N*/               else if (aLayerName.EqualsAscii( "LAYER_BCKGRND" ))
/*N*/               {
/*N*/                   pLayer->SetName(String(SdResId(STR_LAYER_BCKGRND)));
/*N*/               }
/*N*/               else if (aLayerName.EqualsAscii( "LAYER_BACKGRNDOBJ" ))
/*N*/               {
/*N*/                   pLayer->SetName(String(SdResId(STR_LAYER_BCKGRNDOBJ)));
/*N*/               }
/*N*/               else if (aLayerName.EqualsAscii( "LAYER_CONTROLS" ))
/*N*/               {
/*N*/                   pLayer->SetName(String(SdResId(STR_LAYER_CONTROLS)));
/*N*/               }
/*N*/               else if (aLayerName.EqualsAscii( "LAYER_MEASURELINES" ))
/*N*/               {
/*N*/                   pLayer->SetName(String(SdResId(STR_LAYER_MEASURELINES)));
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }
/*N*/ #endif // !SVX_LIGHT


/*************************************************************************
|*
|* Formatierte Seitennummer zurueckgeben (1, I, i, a, usw.)
|*
\************************************************************************/

/*N*/ String SdDrawDocument::CreatePageNumValue(USHORT nNum) const
/*N*/ {
/*N*/   String aPageNumValue;
/*N*/   BOOL bUpper = FALSE;
/*N*/
/*N*/   switch (ePageNumType)
/*N*/   {
/*N*/       case SVX_CHARS_UPPER_LETTER:
/*N*/           aPageNumValue += (sal_Unicode)(char)((nNum - 1) % 26 + 'A');
/*N*/           break;
/*N*/       case SVX_CHARS_LOWER_LETTER:
/*N*/           aPageNumValue += (sal_Unicode)(char)((nNum - 1) % 26 + 'a');
/*N*/           break;
/*N*/       case SVX_ROMAN_UPPER:
/*N*/           bUpper = TRUE;
/*N*/       case SVX_ROMAN_LOWER:
/*N*/           aPageNumValue += SvxNumberFormat::CreateRomanString(nNum, bUpper);
/*N*/           break;
/*N*/       case SVX_NUMBER_NONE:
/*N*/           aPageNumValue.Erase();
/*N*/           aPageNumValue += sal_Unicode(' ');
/*N*/           break;
/*N*/       default:
/*N*/           aPageNumValue += String::CreateFromInt32( (sal_Int32)nNum );
/*N*/   }
/*N*/
/*N*/   return(aPageNumValue);
/*N*/ }



/*************************************************************************
|*
|* Layout-Template umbenennen
|* Zu beachten ist, das rOldLayoutName im Gegensatz zu rNewName den
|* kompletten Layout(!)-Namen enthaelt (inkl. ~LT~)!
|*
\************************************************************************/

/*N*/ void SdDrawDocument::RenameLayoutTemplate(const String& rOldLayoutName, const String& rNewName)
/*N*/ {
/*N*/   String aOldName(rOldLayoutName);
/*N*/   USHORT nPos = aOldName.SearchAscii( SD_LT_SEPARATOR );
/*N*/
/*N*/   // erase everything after '~LT~'
/*N*/   aOldName.Erase(nPos + sizeof(SD_LT_SEPARATOR) - 1 );
/*N*/   USHORT nLen = aOldName.Len();
/*N*/
/*N*/   List aReplList;
/*N*/   SfxStyleSheetIterator aIter(pStyleSheetPool, SD_LT_FAMILY);
/*N*/   SfxStyleSheetBase* pSheet = aIter.First();
/*N*/
/*N*/   while (pSheet)
/*N*/   {
/*N*/       String aSheetName = pSheet->GetName();
/*N*/
/*N*/       // if the sheetname starts with aOldName + "~LT~"
/*N*/       if (aSheetName.Match(aOldName) == nLen)
/*N*/       {
/*N*/           aSheetName.Erase(0, nLen - sizeof(SD_LT_SEPARATOR) + 1 );
/*N*/           aSheetName.Insert(rNewName, 0);
/*N*/
/*N*/           StyleReplaceData* pReplData = new StyleReplaceData;
/*N*/           pReplData->nFamily    = pSheet->GetFamily();
/*N*/           pReplData->nNewFamily = pSheet->GetFamily();
/*N*/           pReplData->aName      = pSheet->GetName();
/*N*/           pReplData->aNewName   = aSheetName;
/*N*/           aReplList.Insert(pReplData, LIST_APPEND);
/*N*/
/*N*/           pSheet->SetName(aSheetName);
/*N*/       }
/*N*/
/*N*/       pSheet = aIter.Next();
/*N*/   }
/*N*/
/*N*/   // jetzt noch den Layoutnamen der Zeichen- und der Notizseite
/*N*/   // sowie ihrer Masterpages setzen
/*N*/   String aPageLayoutName(rNewName);
/*N*/   aPageLayoutName.AppendAscii( RTL_CONSTASCII_STRINGPARAM( SD_LT_SEPARATOR ));
/*N*/   aPageLayoutName += String(SdResId(STR_LAYOUT_OUTLINE));
/*N*/
/*N*/   // an allen Seiten, die das jetzt umbeannte Layout benutzen, die
/*N*/   // Textobjekte von der Aenderung unterrichten und Layoutnamen setzen
/*N*/   USHORT nPage;
/*N*/   for (nPage = 0; nPage < GetPageCount(); nPage++)
/*N*/   {
/*N*/       SdPage* pPage = (SdPage*) GetPage(nPage);
/*N*/       String aTemp(pPage->GetLayoutName());
/*N*/
/*N*/       if (aTemp == rOldLayoutName)
/*N*/       {
/*N*/           pPage->SetLayoutName(aPageLayoutName);
/*N*/
/*N*/           for (ULONG nObj = 0; nObj < pPage->GetObjCount(); nObj++)
/*N*/           {
/*N*/               SdrObject* pObj = pPage->GetObj(nObj);
/*N*/
/*N*/               if (pObj->GetObjInventor() == SdrInventor)
/*N*/               {
/*N*/                   switch( pObj->GetObjIdentifier() )
/*N*/                   {
/*N*/                       case OBJ_TEXT:
/*N*/                       case OBJ_OUTLINETEXT:
/*N*/                       case OBJ_TITLETEXT:
/*N*/                       {
/*N*/                           OutlinerParaObject* pOPO = ((SdrTextObj*) pObj)->GetOutlinerParaObject();
/*N*/
/*N*/                           if (pOPO)
/*N*/                           {
/*N*/                               StyleReplaceData* pReplData = (StyleReplaceData*) aReplList.First();
/*N*/
/*N*/                               while( pReplData )
/*N*/                               {
/*N*/                                   pOPO->ChangeStyleSheets( pReplData->aName, pReplData->nFamily, pReplData->aNewName, pReplData->nNewFamily );
/*N*/                                   pReplData = (StyleReplaceData*) aReplList.Next();
/*N*/                               }
/*N*/                           }
/*N*/                       }
/*N*/                       break;
/*N*/
/*N*/                       default:
/*N*/                       break;
/*N*/                   }
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   // und nochmal fuer die Masterpages
/*N*/   // die betroffenen Masterpages erhalten als Seitennamen den Namen
/*N*/   // des Layouts
/*N*/   for (nPage = 0; nPage < GetMasterPageCount(); nPage++)
/*N*/   {
/*N*/       SdPage* pPage = (SdPage*) GetMasterPage(nPage);
/*N*/       String aTemp(pPage->GetLayoutName());
/*N*/
/*N*/       if (aTemp == rOldLayoutName)
/*N*/       {
/*N*/           pPage->SetLayoutName(aPageLayoutName);
/*N*/           pPage->SetName(rNewName);
/*N*/
/*N*/           for (ULONG nObj = 0; nObj < pPage->GetObjCount(); nObj++)
/*N*/           {
/*N*/               SdrObject* pObj = pPage->GetObj(nObj);
/*N*/
/*N*/               if (pObj->GetObjInventor() == SdrInventor)
/*N*/               {
/*N*/                   switch(pObj->GetObjIdentifier())
/*N*/                   {
/*N*/                       case OBJ_TEXT:
/*N*/                       case OBJ_OUTLINETEXT:
/*N*/                       case OBJ_TITLETEXT:
/*N*/                       {
/*N*/                           OutlinerParaObject* pOPO = ((SdrTextObj*)pObj)->GetOutlinerParaObject();
/*N*/
/*N*/                           if (pOPO)
/*N*/                           {
/*N*/                               StyleReplaceData* pReplData = (StyleReplaceData*) aReplList.First();
/*N*/
/*N*/                               while( pReplData )
/*N*/                               {
/*N*/                                   pOPO->ChangeStyleSheets( pReplData->aName, pReplData->nFamily, pReplData->aNewName, pReplData->nNewFamily );
/*N*/                                   pReplData = (StyleReplaceData*) aReplList.Next();
/*N*/                               }
/*N*/                           }
/*N*/                       }
/*N*/                       break;
/*N*/
/*N*/                       default:
/*N*/                       break;
/*N*/                   }
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* Outliner-Defaults setzen (Pool-Defaults)
|*
\************************************************************************/
/*N*/ void SdDrawDocument::SetTextDefaults() const
/*N*/ {
/*N*/   // BulletItem und BulletFont fuer Titel und Gliederung
/*N*/   SvxBulletItem aBulletItem(EE_PARA_BULLET);
/*N*/   Font aBulletFont( ((SdStyleSheetPool*) pStyleSheetPool)->GetBulletFont() );
/*N*/   aBulletFont.SetSize(Size(0,846));       // 24 pt
/*N*/   aBulletItem.SetFont(aBulletFont);
/*N*/   aBulletItem.SetStyle(BS_BULLET);
/*N*/   aBulletItem.SetStart(1);
/*N*/   aBulletItem.SetScale(45);               // in Prozent
/*N*/   aBulletItem.SetSymbol( 0x25CF );                // Punkt
/*N*/   pItemPool->SetPoolDefaultItem( aBulletItem );
/*N*/
/*N*/   // Bullets nicht sichtbar
/*N*/   SfxUInt16Item aBulletStateItem(EE_PARA_BULLETSTATE, 0);
/*N*/   pItemPool->SetPoolDefaultItem( aBulletStateItem );
/*N*/
/*N*/   // Neues BulletItem
/*N*/   SvxNumberFormat aNumberFormat(SVX_NUM_CHAR_SPECIAL);
/*N*/   aNumberFormat.SetBulletFont(&aBulletFont);
/*N*/   aNumberFormat.SetBulletChar( 0x25CF );  // StarBats: 0xF000 + 34
/*N*/   aNumberFormat.SetBulletRelSize(45);
/*N*/   aNumberFormat.SetBulletColor(Color(COL_AUTO));
/*N*/   aNumberFormat.SetStart(1);
/*N*/   aNumberFormat.SetNumAdjust(SVX_ADJUST_LEFT);
/*N*/
/*N*/   SvxNumRule aNumRule( NUM_BULLET_REL_SIZE|NUM_BULLET_COLOR|NUM_CHAR_TEXT_DISTANCE, 10 , FALSE);
/*N*/
/*N*/   aNumberFormat.SetLSpace( 0 );
/*N*/   aNumberFormat.SetAbsLSpace( 0 );
/*N*/   aNumberFormat.SetFirstLineOffset( 0 );
/*N*/   aNumRule.SetLevel( 0, aNumberFormat );
/*N*/
/*N*/   for( USHORT i = 1; i < 10; i++ )
/*N*/   {
/*N*/       const short nLSpace = (i + 1) * 600;
/*N*/       aNumberFormat.SetLSpace(nLSpace);
/*N*/       aNumberFormat.SetAbsLSpace(nLSpace);
/*N*/       aNumberFormat.SetFirstLineOffset(-600);
/*N*/       aNumRule.SetLevel( i, aNumberFormat );
/*N*/   }
/*N*/
/*N*/   SvxNumBulletItem aNumBulletItem( aNumRule, EE_PARA_NUMBULLET );
/*N*/   pItemPool->SetPoolDefaultItem( aNumBulletItem );
/*N*/ }

/*************************************************************************
|*
|*
|*
\************************************************************************/

/*N*/ ::com::sun::star::text::WritingMode SdDrawDocument::GetDefaultWritingMode() const
/*N*/ {
/*N*/     const SfxPoolItem*                  pItem = ( pItemPool ? pItemPool->GetPoolDefaultItem( EE_PARA_WRITINGDIR ) : NULL );
/*N*/     ::com::sun::star::text::WritingMode eRet = ::com::sun::star::text::WritingMode_LR_TB;
/*N*/
/*N*/     if( pItem )
/*N*/     {
/*N*/         switch( ( (SvxFrameDirectionItem&)( *pItem ) ).GetValue() )
/*N*/         {
/*N*/             case( FRMDIR_HORI_LEFT_TOP ): eRet = ::com::sun::star::text::WritingMode_LR_TB; break;
/*?*/             case( FRMDIR_HORI_RIGHT_TOP ): eRet = ::com::sun::star::text::WritingMode_RL_TB; break;
/*?*/             case( FRMDIR_VERT_TOP_RIGHT ): eRet = ::com::sun::star::text::WritingMode_TB_RL; break;
/*?*/
/*?*/             default:
/*?*/                 DBG_ERROR( "Frame direction not supported yet" );
/*N*/             break;
/*N*/         }
/*N*/     }
/*N*/
/*N*/     return eRet;
/*N*/ }

//STRIP001 void SdDrawDocument::SetDefaultWritingMode(::com::sun::star::text::WritingMode eMode )
//STRIP001 {
//STRIP001  if( pItemPool )
//STRIP001  {
//STRIP001      SvxFrameDirection nVal;
//STRIP001      switch( eMode )
//STRIP001      {
//STRIP001      case ::com::sun::star::text::WritingMode_LR_TB: nVal = FRMDIR_HORI_LEFT_TOP; break;
//STRIP001      case ::com::sun::star::text::WritingMode_RL_TB: nVal = FRMDIR_HORI_RIGHT_TOP; break;
//STRIP001      case ::com::sun::star::text::WritingMode_TB_RL: nVal = FRMDIR_VERT_TOP_RIGHT; break;
//STRIP001      default:
//STRIP001          DBG_ERROR( "Frame direction not supported yet" );
//STRIP001          return;
//STRIP001      }
//STRIP001
//STRIP001      SvxFrameDirectionItem aModeItem( nVal, EE_PARA_WRITINGDIR );
//STRIP001      pItemPool->SetPoolDefaultItem( aModeItem );
//STRIP001
//STRIP001         SvxAdjustItem aAdjust;
//STRIP001
//STRIP001      if( eMode == ::com::sun::star::text::WritingMode_RL_TB )
//STRIP001          aAdjust.SetEnumValue( SVX_ADJUST_RIGHT );
//STRIP001
//STRIP001      pItemPool->SetPoolDefaultItem( aAdjust );
//STRIP001
//STRIP001
//STRIP001  }
//STRIP001 }

/*N*/ void SdDrawDocument::getDefaultFonts( Font& rLatinFont, Font& rCJKFont, Font& rCTLFont )
/*N*/ {
/*N*/   LanguageType eLatin = GetLanguage( EE_CHAR_LANGUAGE );
/*N*/
/*N*/   //  #108374# / #107782#: If the UI language is Korean, the default Latin font has to
/*N*/   //  be queried for Korean, too (the Latin language from the document can't be Korean).
/*N*/   //  This is the same logic as in SwDocShell::InitNew.
/*N*/   LanguageType eUiLanguage = Application::GetSettings().GetUILanguage();
/*N*/   switch( eUiLanguage )
/*N*/   {
/*N*/       case LANGUAGE_KOREAN:
/*N*/       case LANGUAGE_KOREAN_JOHAB:
/*N*/           eLatin = eUiLanguage;
/*N*/       break;
/*N*/   }
/*N*/
/*N*/   rLatinFont = OutputDevice::GetDefaultFont( DEFAULTFONT_LATIN_PRESENTATION, eLatin, DEFAULTFONT_FLAGS_ONLYONE );
/*N*/   rCJKFont = OutputDevice::GetDefaultFont( DEFAULTFONT_CJK_PRESENTATION, GetLanguage( EE_CHAR_LANGUAGE_CJK ), DEFAULTFONT_FLAGS_ONLYONE );
/*N*/   rCTLFont = OutputDevice::GetDefaultFont( DEFAULTFONT_CTL_PRESENTATION, GetLanguage( EE_CHAR_LANGUAGE_CTL ), DEFAULTFONT_FLAGS_ONLYONE ) ;
/*N*/ }
}
