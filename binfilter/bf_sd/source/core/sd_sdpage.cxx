/*************************************************************************
 *
 *  $RCSfile: sd_sdpage.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 14:58:21 $
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

#ifndef _SV_SVAPP_HXX
#include <vcl/svapp.hxx>
#endif

#include "eetext.hxx"       // definiert ITEMID_... fuer frmitems und textitem
#ifndef _EEITEM_HXX //autogen
#include <bf_svx/eeitem.hxx>
#endif
#ifndef _SVDSURO_HXX //autogen
#include <bf_svx/svdsuro.hxx>
#endif
#ifndef _SVDOUTL_HXX //autogen
#include <bf_svx/svdoutl.hxx>
#endif
#include <bf_svx/editdata.hxx>
#include <bf_svx/pageitem.hxx>
#include <bf_svx/lrspitem.hxx>
#include <bf_svx/bulitem.hxx>
#ifndef _SVX_FHGTITEM_HXX //autogen
#include <bf_svx/fhgtitem.hxx>
#endif
#ifndef _OUTLOBJ_HXX //autogen
#include <bf_svx/outlobj.hxx>
#endif
#ifndef _SVDOOLE2_HXX //autogen
#include <bf_svx/svdoole2.hxx>
#endif
#ifndef _SVDOGRAF_HXX //autogen
#include <bf_svx/svdograf.hxx>
#endif
#ifndef _SVDOPAGE_HXX //autogen
#include <bf_svx/svdopage.hxx>
#endif
#ifndef _SVDOPAGE_HXX //autogen
#include <bf_svx/svdopage.hxx>
#endif
#ifndef _SFX_PRINTER_HXX //autogen
#include <bf_sfx2/printer.hxx>
#endif
#ifndef _BASMGR_HXX //autogen
#include <basic/basmgr.hxx>
#endif
#ifndef _SVX_PBINITEM_HXX //autogen
#include <bf_svx/pbinitem.hxx>
#endif
#ifndef _SVDUNDO_HXX //autogen
#include <bf_svx/svdundo.hxx>
#endif
#ifndef _SFXSMPLHINT_HXX //autogen
#include <svtools/smplhint.hxx>
#endif
#ifndef _SVX_ADJITEM_HXX
#include <bf_svx/adjitem.hxx>
#endif
#ifndef _EDITOBJ_HXX
#include <bf_svx/editobj.hxx>
#endif
#ifndef _SVX_SRIPTTYPEITEM_HXX
#include <bf_svx/scripttypeitem.hxx>
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
#include "sdoutl.hxx"

#include "misc.hxx"
#include "eetext.hxx"
#include "drawdoc.hxx"
#include "sdpage.hxx"
#include "pglink.hxx"
#include "sdresid.hxx"
#include "stlsheet.hxx"
#include "glob.hrc"
#include "glob.hxx"

#define MAX_PRESOBJ     5              // Max. Anzahl Praesentationsobjekte

using namespace ::com::sun::star;

/*N*/ TYPEINIT2( SdPage, FmFormPage, SdrObjUserCall );

/*************************************************************************
|*
|*      Ctor
|*
\************************************************************************/

/*N*/ SdPage::SdPage(SdDrawDocument& rNewDoc, StarBASIC* pBasic, BOOL bMasterPage) :
/*N*/   FmFormPage(rNewDoc, pBasic, bMasterPage),
/*N*/   SdrObjUserCall(),
/*N*/   bSelected(FALSE),
/*N*/   eFadeSpeed(FADE_SPEED_MEDIUM),
/*N*/   eFadeEffect(::com::sun::star::presentation::FadeEffect_NONE),
/*N*/   ePresChange(PRESCHANGE_MANUAL),
/*N*/   nTime(1),
/*N*/   bSoundOn(FALSE),
/*N*/   bExcluded(FALSE),
/*N*/   eAutoLayout(AUTOLAYOUT_NONE),
/*N*/   bOwnArrangement(FALSE),
/*N*/   ePageKind(PK_STANDARD),
/*N*/   bScaleObjects(TRUE),
/*N*/   pPageLink(NULL),
/*N*/   bBackgroundFullSize( FALSE ),
/*N*/   nPaperBin(PAPERBIN_PRINTER_SETTINGS),
/*N*/   mpItems(NULL)
/*N*/ {
/*N*/   // Der Layoutname der Seite wird von SVDRAW benutzt, um die Praesentations-
/*N*/   // vorlagen der Gliederungsobjekte zu ermitteln. Darum enthaelt er bereits
/*N*/   // den Bezeichner fuer die Gliederung (STR_LAYOUT_OUTLINE).
/*N*/   aLayoutName  = String(SdResId(STR_LAYOUT_DEFAULT_NAME));
/*N*/   aLayoutName.AppendAscii( RTL_CONSTASCII_STRINGPARAM( SD_LT_SEPARATOR ));
/*N*/   aLayoutName += String(SdResId(STR_LAYOUT_OUTLINE));
/*N*/
/*N*/   eCharSet = gsl_getSystemTextEncoding();
/*N*/
/*N*/   Size aPageSize(GetSize());
/*N*/
/*N*/   if (aPageSize.Width() > aPageSize.Height())
/*N*/   {
/*N*/       eOrientation = ORIENTATION_LANDSCAPE;
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       eOrientation = ORIENTATION_PORTRAIT;
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* Dtor
|*
\************************************************************************/

/*N*/ SdPage::~SdPage()
/*N*/ {
/*N*/   DisconnectLink();
/*N*/
/*N*/   EndListenOutlineText();
/*N*/
/*N*/   if( mpItems )
/*?*/       delete mpItems;
/*N*/ }


/*************************************************************************
|*
|* Pruefen, ob ein bestimmtes Praesentationobjekt existiert
|* USHORT nIndex: Index des Objekttypes
|*  1.Objekt des Types -> Index = 1
|*  2.Objekt des Types -> Index = 2 usw.
|*
\************************************************************************/

/*N*/ SdrObject* SdPage::GetPresObj(PresObjKind eObjKind, USHORT nIndex)
/*N*/ {
/*N*/   USHORT nObjFound = 0;          // Index des gewuenschten Objekttypes
/*N*/   SdrObject* pObj = NULL;
/*N*/   SdrObject* pObjFound = NULL;
/*N*/   USHORT nIdx = 0;
/*N*/   USHORT nCnt = (USHORT) aPresObjList.Count();
/*N*/
/*N*/   while (nIdx < nCnt && nObjFound != nIndex)
/*N*/   {
         /**************************************************************
         * Ist das Objekt in der Praesentationsobjektliste vorhanden?
         **************************************************************/
/*N*/       pObj = (SdrObject*) aPresObjList.GetObject(nIdx);
/*N*/
/*N*/       if (pObj)
/*N*/       {
/*N*/           if (eObjKind == GetPresObjKind(pObj) )
/*N*/               nObjFound++;    // Uebereinstimmendes Objekt gefunden
/*N*/       }
/*N*/
/*N*/       nIdx++;
/*N*/   }
/*N*/
/*N*/   if (nObjFound == nIndex)
/*N*/   {
/*N*/       // Gewuenschstes Objekt in PresObjList gefunden
/*N*/       pObjFound = pObj;
/*N*/   }
/*N*/   else if (eObjKind==PRESOBJ_TITLE || eObjKind==PRESOBJ_OUTLINE)
/*N*/   {
        /**************************************************************
        * Ist das Objekt auf der Seite vorhanden?
        **************************************************************/
/*N*/       nObjFound = 0;
/*N*/       nIdx = 0;
/*N*/       nCnt = (USHORT) GetObjCount();
/*N*/
/*N*/       while (nIdx < nCnt && nObjFound != nIndex)
/*N*/       {
/*N*/           pObj = GetObj(nIdx);
/*N*/           SdrObjKind eSdrObjKind = (SdrObjKind) pObj->GetObjIdentifier();
/*N*/
/*N*/           if (pObj->GetObjInventor() == SdrInventor &&
/*N*/               (eObjKind==PRESOBJ_TITLE   && eSdrObjKind == OBJ_TITLETEXT ||
/*N*/                eObjKind==PRESOBJ_OUTLINE && eSdrObjKind == OBJ_OUTLINETEXT))
/*N*/           {
/*N*/               nObjFound++;    // Uebereinstimmendes Objekt gefunden
/*N*/           }
/*N*/
/*N*/           nIdx++;
/*N*/       }
/*N*/
/*N*/       if (nObjFound == nIndex)
/*N*/       {
/*N*/           // Gewuenschtes Objekt auf der Seite gefunden
/*N*/           pObjFound = pObj;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return(pObjFound);
/*N*/ }



/*************************************************************************
|*
|* Es werden Praesentationsobjekte auf der Page erzeugt.
|* Alle Praesentationsobjekte erhalten einen UserCall auf die Page.
|*
\************************************************************************/

/*N*/ SdrObject* SdPage::CreatePresObj(PresObjKind eObjKind, BOOL bVertical, const Rectangle& rRect,
/*N*/                                BOOL bInsert)
/*N*/ {
    /**************************************************************************
    * Praesentationsobjekte werden erzeugt
    **************************************************************************/
/*N*/   SdrObject* pSdrObj = NULL;
/*N*/
/*N*/   if (eObjKind == PRESOBJ_TITLE)
/*N*/   {
/*N*/       pSdrObj = new SdrRectObj(OBJ_TITLETEXT);
/*N*/
/*N*/       if (bMaster)
/*N*/       {
/*N*/           pSdrObj->SetNotVisibleAsMaster(TRUE);
/*N*/       }
/*N*/   }
/*N*/   else if (eObjKind == PRESOBJ_OUTLINE)
/*N*/   {
/*N*/       pSdrObj = new SdrRectObj(OBJ_OUTLINETEXT);
/*N*/
/*N*/       if (bMaster)
/*N*/       {
/*N*/           pSdrObj->SetNotVisibleAsMaster(TRUE);
/*N*/       }
/*N*/   }
/*N*/   else if (eObjKind == PRESOBJ_NOTES)
/*N*/   {
/*N*/       pSdrObj = new SdrRectObj(OBJ_TEXT);
/*N*/
/*N*/       if (bMaster)
/*N*/       {
/*N*/           pSdrObj->SetNotVisibleAsMaster(TRUE);
/*N*/       }
/*N*/   }
/*N*/   else if (eObjKind == PRESOBJ_TEXT)
/*N*/   {
/*N*/       pSdrObj = new SdrRectObj(OBJ_TEXT);
/*N*/   }
/*N*/   else if (eObjKind == PRESOBJ_GRAPHIC)
/*N*/   {
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001 Graphic aGraphic ( SdResId(BMP_PRESOBJ_GRAPHIC) );
//STRIP001 /*?*/        OutputDevice &aOutDev = *Application::GetDefaultDevice();
//STRIP001 /*?*/        aOutDev.Push();
//STRIP001 /*?*/
//STRIP001 /*?*/        aOutDev.SetMapMode( aGraphic.GetPrefMapMode() );
//STRIP001 /*?*/        Size aSizePix = aOutDev.LogicToPixel( aGraphic.GetPrefSize() );
//STRIP001 /*?*/        aOutDev.SetMapMode(MAP_100TH_MM);
//STRIP001 /*?*/
//STRIP001 /*?*/        Size aSize = aOutDev.PixelToLogic(aSizePix);
//STRIP001 /*?*/        Point aPnt (0, 0);
//STRIP001 /*?*/        Rectangle aRect (aPnt, aSize);
//STRIP001 /*?*/        pSdrObj = new SdrGrafObj(aGraphic, aRect);
//STRIP001 /*?*/        aOutDev.Pop();
/*?*/   }
/*N*/   else if (eObjKind == PRESOBJ_OBJECT)
/*N*/   {
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001 pSdrObj = new SdrOle2Obj();
//STRIP001 /*?*/        Graphic aGraphic( SdResId(BMP_PRESOBJ_OBJECT) );
//STRIP001 /*?*/        ( (SdrOle2Obj*) pSdrObj)->SetGraphic(&aGraphic);
/*?*/   }
/*N*/   else if (eObjKind == PRESOBJ_CHART)
/*N*/   {
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001 pSdrObj = new SdrOle2Obj();
//STRIP001 /*?*/        ( (SdrOle2Obj*) pSdrObj)->SetProgName( String( RTL_CONSTASCII_USTRINGPARAM( "StarChart" )));
//STRIP001 /*?*/        Graphic aGraphic( SdResId(BMP_PRESOBJ_CHART) );
//STRIP001 /*?*/        ( (SdrOle2Obj*) pSdrObj)->SetGraphic(&aGraphic);
/*?*/   }
/*N*/   else if (eObjKind == PRESOBJ_ORGCHART)
/*N*/   {
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001 pSdrObj = new SdrOle2Obj();
//STRIP001 /*?*/        ( (SdrOle2Obj*) pSdrObj)->SetProgName( String( RTL_CONSTASCII_USTRINGPARAM( "StarOrg" )));
//STRIP001 /*?*/        Graphic aGraphic( SdResId(BMP_PRESOBJ_ORGCHART) );
//STRIP001 /*?*/        ( (SdrOle2Obj*) pSdrObj)->SetGraphic(&aGraphic);
/*?*/   }
/*N*/   else if (eObjKind == PRESOBJ_TABLE)
/*N*/   {
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001 pSdrObj = new SdrOle2Obj();
//STRIP001 /*?*/        ( (SdrOle2Obj*) pSdrObj)->SetProgName( String( RTL_CONSTASCII_USTRINGPARAM( "StarCalc" )));
//STRIP001 /*?*/        Graphic aGraphic( SdResId(BMP_PRESOBJ_TABLE) );
//STRIP001 /*?*/        ( (SdrOle2Obj*) pSdrObj)->SetGraphic(&aGraphic);
/*?*/   }
/*?*/ #ifdef STARIMAGE_AVAILABLE
/*?*/   else if (eObjKind == PRESOBJ_IMAGE)
/*?*/   {
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001 pSdrObj = new SdrOle2Obj();
//STRIP001 /*?*/        ( (SdrOle2Obj*) pSdrObj)->SetProgName( String( RTL_CONSTASCII_USTRINGPARAM( "StarImage" )));
//STRIP001 /*?*/        Graphic aGraphic( SdResId(BMP_PRESOBJ_IMAGE) );
//STRIP001 /*?*/        ( (SdrOle2Obj*) pSdrObj)->SetGraphic(&aGraphic);
/*?*/   }
/*?*/ #endif
/*N*/   else if (eObjKind == PRESOBJ_BACKGROUND)
/*N*/   {
/*N*/       pSdrObj = new SdrRectObj();
/*N*/       pSdrObj->SetMoveProtect(TRUE);
/*N*/       pSdrObj->SetResizeProtect(TRUE);
/*N*/       pSdrObj->SetMarkProtect(TRUE);
/*N*/   }
/*N*/   else if (eObjKind == PRESOBJ_HANDOUT)
/*N*/   {
/*N*/       //Erste Standardseite am SdrPageObj vermerken
/*N*/       SdrPage* pPage = ( (SdDrawDocument*) pModel )->GetSdPage(0, PK_STANDARD);
/*N*/       pSdrObj = new SdrPageObj( pPage->GetPageNum() );
/*N*/       pSdrObj->SetResizeProtect(TRUE);
/*N*/   }
/*N*/   else if (eObjKind == PRESOBJ_PAGE)
/*N*/   {
/*N*/       //Notizseite am SdrPageObj vermerken
/*N*/       pSdrObj = new SdrPageObj( GetPageNum() - 1 );
/*N*/       pSdrObj->SetResizeProtect(TRUE);
/*N*/   }
/*N*/
/*N*/   if (pSdrObj)
/*N*/   {
/*N*/       // #107228# We need to put the shape that will be inserted
/*N*/       // into the aPresObjList always. This is because the accessibility
/*N*/       // api creates a XShape wrapper during the call to InsertObject.
/*N*/       // The creation fails if this is not in the aPresObjList at this point.
/*N*/       // We will remove it from the aPresObjList after InsertObject since
/*N*/       // this is needed for the correct working of SetAutoLayout
/*N*/       const bool bIsAlreadyInserted = aPresObjList.GetPos(pSdrObj) != LIST_ENTRY_NOTFOUND;
/*N*/
/*N*/       if( !bIsAlreadyInserted )
/*N*/           aPresObjList.Insert(pSdrObj, LIST_APPEND);
/*N*/
/*N*/       pSdrObj->SetEmptyPresObj(TRUE);
/*N*/       pSdrObj->SetLogicRect(rRect);
/*N*/
/*N*/       InsertObject(pSdrObj);
/*N*/
/*N*/       if( !bIsAlreadyInserted && !bInsert )
/*N*/           aPresObjList.Remove( pSdrObj );
/*N*/
/*N*/       if ( pSdrObj->ISA(SdrTextObj) )
/*N*/       {
/*N*/           // #96243# Tell the object EARLY that it is vertical to have the
/*N*/           // defaults for AutoGrowWidth/Height reversed
/*N*/           if(bVertical)
/*?*/               ((SdrTextObj*)pSdrObj)->SetVerticalWriting(TRUE);
/*N*/
/*N*/           SfxItemSet aTempAttr( ((SdDrawDocument*) pModel)->GetPool() );
/*N*/           if( bVertical )
/*N*/               aTempAttr.Put( SdrTextMinFrameWidthItem( rRect.GetSize().Width() ) );
/*N*/           else
/*N*/               aTempAttr.Put( SdrTextMinFrameHeightItem( rRect.GetSize().Height() ) );

/*N*/           if (bMaster)
/*N*/           {
/*N*/               // Bei Praesentationsobjekten auf der MasterPage soll die
/*N*/               // Groesse vom Benutzwer frei waehlbar sein
/*N*/
/*N*/               // #96243# potential problem: This action was still NOT
/*N*/               // adapted for vertical text. This sure needs to be done.
/*N*/               if(bVertical)
/*N*/                   aTempAttr.Put(SdrTextAutoGrowWidthItem(FALSE));
/*N*/               else
/*N*/                   aTempAttr.Put(SdrTextAutoGrowHeightItem(FALSE));
/*N*/           }
/*N*/
/*N*/           pSdrObj->SetItemSet(aTempAttr);
/*N*/       }
/*N*/
/*N*/       String aString = GetPresObjText(eObjKind);
/*N*/       if ( aString.Len() && pSdrObj->ISA(SdrTextObj) )
/*N*/       {
/*N*/           SdrOutliner* pOutliner = ( (SdDrawDocument*) GetModel() )->GetInternalOutliner();
/*N*/
/*N*/           USHORT nOutlMode = pOutliner->GetMode();
/*N*/           pOutliner->Init( OUTLINERMODE_TEXTOBJECT );
/*N*/           pOutliner->SetMinDepth(0);
/*N*/           pOutliner->SetStyleSheet( 0, NULL );
/*N*/           pOutliner->SetVertical( bVertical );
/*N*/
/*N*/           String aEmptyStr;
/*N*/           SetObjText( (SdrTextObj*) pSdrObj, (SdrOutliner*)pOutliner, eObjKind, aString );
/*N*/
/*N*/           pOutliner->Init( nOutlMode );
/*N*/           pOutliner->SetStyleSheet( 0, NULL );
/*N*/       }
/*N*/
/*N*/       pSdrObj->SetUserCall(this);
/*N*/       pSdrObj->RecalcBoundRect();
/*N*/
/*N*/       if (bMaster)
/*N*/       {
/*N*/           SdrLayerAdmin& rLayerAdmin = pModel->GetLayerAdmin();
/*N*/
/*N*/           if (eObjKind == PRESOBJ_BACKGROUND)
/*N*/           {
/*N*/               // Hintergrund der MasterPage
/*N*/               pSdrObj->SetLayer( rLayerAdmin.
/*N*/                   GetLayerID(String(SdResId(STR_LAYER_BCKGRND)), FALSE) );
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               // Hintergrundobjekte der MasterPage
/*N*/               pSdrObj->SetLayer( rLayerAdmin.
/*N*/                   GetLayerID(String(SdResId(STR_LAYER_BCKGRNDOBJ)), FALSE) );
/*N*/           }
/*N*/       }
/*N*/
/*N*/       // Objekt am StyleSheet anmelden
/*N*/       // #95114# Set style only when one was found (as in 5.2)
/*N*/       // pSdrObj->NbcSetStyleSheet( GetStyleSheetForPresObj(eObjKind), FALSE );
/*N*/       SfxStyleSheet* pSheetForPresObj = GetStyleSheetForPresObj(eObjKind);
/*N*/       if(pSheetForPresObj)
/*N*/           pSdrObj->SetStyleSheet(pSheetForPresObj, FALSE);
/*N*/
/*N*/       if (eObjKind == PRESOBJ_OUTLINE)
/*N*/       {
/*N*/           for (USHORT nLevel = 1; nLevel < 10; nLevel++)
/*N*/           {
/*N*/               String aName(aLayoutName);
/*N*/               aName += sal_Unicode( ' ' );
/*N*/               aName += String::CreateFromInt32( nLevel );
/*N*/               SfxStyleSheet* pSheet = (SfxStyleSheet*)pModel->GetStyleSheetPool()->
/*N*/                           Find(aName, SD_LT_FAMILY);
/*N*/               DBG_ASSERT(pSheet, "Vorlage fuer Gliederungsobjekt nicht gefunden");
/*N*/               if (pSheet)
/*N*/                   pSdrObj->StartListening(*pSheet);
/*N*/           }
/*N*/       }
/*N*/
/*N*/       if ( eObjKind == PRESOBJ_OBJECT   ||
/*N*/            eObjKind == PRESOBJ_CHART    ||
/*N*/            eObjKind == PRESOBJ_ORGCHART ||
/*N*/            eObjKind == PRESOBJ_TABLE    ||
/*N*/ #ifdef STARIMAGE_AVAILABLE
/*N*/            eObjKind == PRESOBJ_IMAGE    ||
/*N*/ #endif
/*N*/            eObjKind == PRESOBJ_GRAPHIC )
/*N*/       {
/*?*/           SfxItemSet aSet( ((SdDrawDocument*) pModel)->GetPool() );
/*?*/           aSet.Put( SdrTextContourFrameItem( TRUE ) );
/*?*/           aSet.Put( SvxAdjustItem( SVX_ADJUST_CENTER ) );
/*?*/
/*?*/           pSdrObj->SetItemSet(aSet);
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return(pSdrObj);
/*N*/ }

/*************************************************************************
|*
|* Es werden Praesentationsobjekte auf der Page erzeugt.
|* Alle Praesentationsobjekte erhalten einen UserCall auf die Page.
|*
\************************************************************************/

/*N*/ SfxStyleSheet* SdPage::GetStyleSheetForPresObj(PresObjKind eObjKind)
/*N*/ {
/*N*/   String aName(GetLayoutName());
/*N*/   String aSep( RTL_CONSTASCII_USTRINGPARAM( SD_LT_SEPARATOR ));
/*N*/   USHORT nPos = aName.Search(aSep);
/*N*/   if (nPos != STRING_NOTFOUND)
/*N*/   {
/*N*/       nPos += aSep.Len();
/*N*/       aName.Erase(nPos);
/*N*/   }
/*N*/
/*N*/   switch (eObjKind)
/*N*/   {
/*N*/       case PRESOBJ_OUTLINE:
/*N*/       {
/*N*/           aName = GetLayoutName();
/*N*/           aName += sal_Unicode( ' ' );
/*N*/           aName += String::CreateFromInt32( 1 );
/*N*/       }
/*N*/       break;
/*N*/
/*N*/       case PRESOBJ_TITLE:
/*N*/           aName += String(SdResId(STR_LAYOUT_TITLE));
/*N*/           break;
/*N*/
/*N*/       case PRESOBJ_BACKGROUND:
/*N*/           aName += String(SdResId(STR_LAYOUT_BACKGROUND));
/*N*/           break;
/*N*/
/*N*/       case PRESOBJ_NOTES:
/*N*/           aName += String(SdResId(STR_LAYOUT_NOTES));
/*N*/           break;
/*N*/
/*N*/       case PRESOBJ_TEXT:
/*N*/       {
/*N*/           aName += String(SdResId(STR_LAYOUT_SUBTITLE));
/*N*/       }
/*N*/       break;
/*N*/
/*N*/       default:
/*N*/           break;
/*N*/   }
/*N*/
/*N*/   SfxStyleSheetBasePool* pStShPool = pModel->GetStyleSheetPool();
/*N*/   SfxStyleSheetBase*     pResult   = pStShPool->Find(aName, SD_LT_FAMILY);
/*N*/   return (SfxStyleSheet*)pResult;
/*N*/ }

/*************************************************************************
|*
|* Das Praesentationsobjekt rObj hat sich geaendert und wird nicht mehr
|* durch das Praesentationsobjekt der MasterPage referenziert.
|* Der UserCall wird geloescht.
|*
\************************************************************************/

/*N*/ void SdPage::Changed(const SdrObject& rObj, SdrUserCallType eType, const Rectangle& rOldBoundRect)
/*N*/ {
/*N*/   if (!bOwnArrangement)
/*N*/   {
/*N*/       switch (eType)
/*N*/       {
/*N*/           case SDRUSERCALL_MOVEONLY:
/*N*/           case SDRUSERCALL_RESIZE:
/*N*/           {
/*N*/               if( pModel->isLocked() )
/*N*/                   break;
/*N*/
/*N*/               SdrObject* pObj = (SdrObject*) &rObj;
/*N*/
/*N*/               if (pObj)
/*N*/               {
/*N*/                   if (!bMaster)
/*N*/                   {
/*N*/                       // Objekt wurde vom Benutzer veraendert und hoert damit nicht
/*N*/                       // mehr auf die MasterPage-Objekte
/*N*/                       pObj->SetUserCall(NULL);
/*N*/                   }
/*N*/                   else if (pModel)
/*N*/                   {
/*N*/                       // MasterPage-Objekt wurde veraendert, daher
/*N*/                       // Objekte auf allen Seiten anpassen
/*N*/                       PageKind ePgKind = GetPageKind();
/*N*/                       USHORT nPageCount = ((SdDrawDocument*) pModel)->GetSdPageCount(ePageKind);
/*N*/
/*N*/                       for (USHORT i = 0; i < nPageCount; i++)
/*N*/                       {
/*N*/                           SdPage* pPage = ((SdDrawDocument*) pModel)->GetSdPage(i, ePageKind);
/*N*/
/*N*/                           if (pPage && pPage->GetMasterPage(0) == this)
/*N*/                           {
/*N*/                               // Seite hoert auf diese MasterPage, daher
/*N*/                               // AutoLayout anpassen
/*N*/                               pPage->SetAutoLayout(pPage->GetAutoLayout());
/*N*/                           }
/*N*/                       }
/*N*/                   }
/*N*/               }
/*N*/           }
/*N*/           break;

/*N*/           case SDRUSERCALL_DELETE:
/*N*/           case SDRUSERCALL_REMOVED:
/*N*/           {
/*N*/               if (!bMaster &&
/*N*/                   aPresObjList.GetPos((void*) &rObj) != LIST_ENTRY_NOTFOUND)
/*N*/               {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001                  // #107844#
//STRIP001                  // Handling of non-empty and empty PresObjs was moved to UndoActionHdl
//STRIP001                  // to allow adding the correct SdrUndoUserCallObj. This may be done here, too,
//STRIP001                  // but it makes more sense to handle all changes to PresObjs in a central
//STRIP001                  // place where the Undo is needed to be fetched anyways.
//STRIP001
//STRIP001                  // In die Liste fuers Undo eintragen, da dieses Objekt
//STRIP001                  // durch das Default-Praesentationsobjekt ersetzt werden
//STRIP001                  // soll.
//STRIP001                  // Im UndoActionHdl des DrawDocs wird der UserCall
//STRIP001                  // auf NULL gesetzt und das Obj aus der Liste ausgetragen
//STRIP001                  ((SdrObject&) rObj).SetUserCall(this);
//STRIP001                  List* pList = ((SdDrawDocument*) pModel)->GetDeletedPresObjList();
//STRIP001                  pList->Insert((void*) &rObj, LIST_APPEND);
/*N*/               }
/*N*/           }
/*N*/           break;

            default:
            break;
        }
    }
/*N*/ }

/*************************************************************************
|*
|* Erzeugt auf einer MasterPage Hintergrund, Titel- und Layout-Bereich
|*
\************************************************************************/

/*N*/ void SdPage::CreateTitleAndLayout(BOOL bInit, BOOL bAPICall )
/*N*/ {
/*N*/   SdPage* pMasterPage = this;
/*N*/
/*N*/   if (!bMaster)
/*N*/   {
/*N*/       pMasterPage = (SdPage*) GetMasterPage(0);
/*N*/   }
/*N*/
/*N*/   if (!pMasterPage)
/*N*/   {
/*N*/       return;
/*N*/   }

    /**************************************************************************
    * Hintergrund, Titel- und Layout-Bereich werden angelegt
    **************************************************************************/
/*N*/   SdrObject* pMasterTitle = NULL;
/*N*/   SdrObject* pMasterOutline = NULL;
/*N*/   SdrObject* pMasterBackground = NULL;
/*N*/
/*N*/
/*N*/   ULONG nMasterIndex = 0;
/*N*/   ULONG nMasterCount = pMasterPage->GetPresObjList()->Count();
/*N*/   SdrObject* pMasterObj = NULL;
/*N*/
/*N*/   for (nMasterIndex = 0; nMasterIndex < nMasterCount; nMasterIndex++)
/*N*/   {
        /******************************************************************
        * Schleife ueber alle Praesentationsobjekte der MasterPage
        ******************************************************************/
/*N*/       pMasterObj = (SdrObject*) pMasterPage->GetPresObjList()->GetObject(nMasterIndex);
/*N*/
/*N*/       if (pMasterObj && pMasterObj->GetObjInventor() == SdrInventor)
/*N*/       {
/*N*/           UINT16 nId = pMasterObj->GetObjIdentifier();
/*N*/
/*N*/           if (nId == OBJ_TITLETEXT)
/*N*/           {
/*N*/               pMasterTitle = pMasterObj;
/*N*/           }
/*N*/           else if ((ePageKind!=PK_NOTES && nId == OBJ_OUTLINETEXT) ||
/*N*/                    (ePageKind==PK_NOTES && nId == OBJ_TEXT) )
/*N*/           {
/*N*/               pMasterOutline = pMasterObj;
/*N*/           }
/*N*/           else if (nId == OBJ_RECT && pMasterObj->IsEmptyPresObj() )
/*N*/           {
/*N*/               pMasterBackground = pMasterObj;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if (!pMasterBackground && ePageKind == PK_STANDARD)
/*N*/   {
        /******************************************************************
        * Hintergrundobjekt
        ******************************************************************/
/*N*/       Point aBackgroundPos ( GetLftBorder(), GetUppBorder() );
/*N*/       Size aBackgroundSize ( GetSize() );
/*N*/       aBackgroundSize.Width()  -= GetLftBorder() + GetRgtBorder() - 1;
/*N*/       aBackgroundSize.Height() -= GetUppBorder() + GetLwrBorder() - 1;
/*N*/       Rectangle aBackgroundRect (aBackgroundPos, aBackgroundSize);
/*N*/       pMasterPage->CreatePresObj(PRESOBJ_BACKGROUND, FALSE, aBackgroundRect, TRUE);
/*N*/   }
/*N*/
/*N*/   BOOL bDeletePresObjOnMaster = FALSE;
/*N*/
/*N*/   if ((eAutoLayout == AUTOLAYOUT_NONE) && !bAPICall)
/*N*/   {
/*N*/       // Die aktuelle Seite soll kein AutoLayout haben!
/*N*/       // Sind die Praesentationsobjekte auf der MasterPage noch notwendig?
/*N*/       bDeletePresObjOnMaster = TRUE;
/*N*/       USHORT nPgCount = ((SdDrawDocument*) pModel)->GetSdPageCount(ePageKind);
/*N*/
/*N*/       for (USHORT i = 0; i < nPgCount && bDeletePresObjOnMaster; i++)
/*N*/       {
/*N*/           SdPage* pPage = ((SdDrawDocument*) pModel)->GetSdPage(i, ePageKind);
/*N*/
/*N*/           if (pPage                                  &&
/*N*/               pPage->GetMasterPage(0) == pMasterPage &&
/*N*/               pPage->GetAutoLayout() != AUTOLAYOUT_NONE)
/*N*/           {
/*N*/               // Seite referenziert die aktuelle MasterPage
/*N*/               // und hat ein gueltiges (kein leeres!)  AutoLayout
/*N*/               bDeletePresObjOnMaster = FALSE;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if (bDeletePresObjOnMaster && !bMaster)
/*N*/   {
/*N*/       // Kein AutoLayout auf der MasterPage erforderlich
/*N*/       // (Hintergrundobjekt muss jedoch erzeugt werden)
/*N*/
/*N*/       List* pMasterPresObjList = pMasterPage->GetPresObjList();
/*N*/
/*N*/       if (pMasterTitle)
/*N*/       {
/*N*/           pMasterPresObjList->Remove(pMasterTitle);
/*N*/           delete pMasterPage->RemoveObject(pMasterTitle->GetOrdNum());
/*N*/       }
/*N*/
/*N*/       if (pMasterOutline)
/*N*/       {
/*N*/           pMasterPresObjList->Remove(pMasterOutline);
/*N*/           delete pMasterPage->RemoveObject(pMasterOutline->GetOrdNum());
/*N*/       }
/*N*/
/*N*/       return;
/*N*/   }
/*N*/
/*N*/   if ( ePageKind == PK_HANDOUT && bInit )
/*N*/   {
        /******************************************************************
        * Handzettel-Seite
        ******************************************************************/
/*N*/
/*N*/       // alle bisherigen Praesentations-Objekte loeschen
/*N*/       List* pPresObjList = pMasterPage->GetPresObjList();
/*N*/
/*N*/       for (ULONG i = 0; i < pPresObjList->Count(); i++)
/*N*/       {
/*N*/           SdrObject* pObj = (SdrObject*) pPresObjList->GetObject(i);
/*N*/           delete pMasterPage->RemoveObject(pObj->GetOrdNum());
/*N*/       }
/*N*/
/*N*/       pMasterPage->GetPresObjList()->Clear();
/*N*/
/*N*/       Size    aArea = GetSize();
/*N*/       long    nX = GetLftBorder();
/*N*/       long    nY = GetUppBorder();
/*N*/       long    nGapW = (nX + GetRgtBorder()) / 2;
/*N*/       long    nGapH = (nY + GetLwrBorder()) / 2;
/*N*/       USHORT  nColCnt, nRowCnt;
/*N*/
/*N*/       if ( !nGapW )
/*?*/       {
/*?*/           nGapW = aArea.Width() / 10;
/*?*/           nX = nGapW;
/*?*/       }
/*N*/       if ( !nGapH )
/*?*/       {
/*?*/           nGapH = aArea.Height() / 10;
/*?*/           nY = nGapH;
/*?*/       }
/*N*/
/*N*/       switch ( pMasterPage->GetAutoLayout() )
/*N*/       {
/*N*/           case AUTOLAYOUT_HANDOUT1: nColCnt = 1; nRowCnt = 1; break;
/*N*/           case AUTOLAYOUT_HANDOUT2: nColCnt = 1; nRowCnt = 2; break;
/*N*/           case AUTOLAYOUT_HANDOUT3: nColCnt = 1; nRowCnt = 3; break;
/*N*/           case AUTOLAYOUT_HANDOUT4: nColCnt = 2; nRowCnt = 2; break;
/*N*/           case AUTOLAYOUT_HANDOUT6: nColCnt = 2; nRowCnt = 3; break;
/*N*/           default: nColCnt = 1; nRowCnt = 1; break;
/*N*/       }
/*N*/       aArea.Width() -= nGapW * 2;
/*N*/       aArea.Height() -= nGapH * 2;
/*N*/
/*N*/       if ( nGapW < aArea.Width() / 10 )
/*N*/           nGapW = aArea.Width() / 10;
/*N*/       if ( nGapH < aArea.Height() / 10 )
/*N*/           nGapH = aArea.Height() / 10;
/*N*/
/*N*/       // bei Querformat Reihen und Spalten vertauschen
/*N*/       if ( aArea.Width() > aArea.Height() )
/*N*/       {
/*N*/           USHORT nTmp = nRowCnt;
/*N*/           nRowCnt = nColCnt;
/*N*/           nColCnt = nTmp;
/*N*/       }
/*N*/
/*N*/       Size aPartArea, aSize;
/*N*/       aPartArea.Width()  = ((aArea.Width()  + nGapW) / nColCnt) - nGapW;
/*N*/       aPartArea.Height() = ((aArea.Height() + nGapH) / nRowCnt) - nGapH;
/*N*/
/*N*/       SdrPage* pPage = ((SdDrawDocument*) pModel)->
/*N*/                           GetSdPage(0, PK_STANDARD);
/*N*/       if ( pPage )
/*N*/       {   // tatsaechliche Seitengroesse in das Handout-Rechteck skalieren
/*N*/           double fH = (double) aPartArea.Width()  / pPage->GetWdt();
/*N*/           double fV = (double) aPartArea.Height() / pPage->GetHgt();
/*N*/
/*N*/           if ( fH > fV )
/*N*/               fH = fV;
/*N*/           aSize.Width()  = (long) (fH * pPage->GetWdt());
/*N*/           aSize.Height() = (long) (fH * pPage->GetHgt());
/*N*/
/*N*/           nX += (aPartArea.Width() - aSize.Width()) / 2;
/*N*/           nY += (aPartArea.Height()- aSize.Height())/ 2;
/*N*/       }
/*N*/       else
/*N*/           aSize = aPartArea;
/*N*/
/*N*/       Point aPos(nX, nY);
/*N*/       USHORT nPgNum = 0;
/*N*/
/*N*/       for (USHORT nRow = 0; nRow < nRowCnt; nRow++)
/*N*/       {
/*N*/           aPos.X() = nX;
/*N*/
/*N*/           for (USHORT nCol = 0; nCol < nColCnt; nCol++)
/*N*/           {
/*N*/               Rectangle aRect(aPos, aSize);
/*N*/               SdrPageObj* pPageObj = (SdrPageObj*) pMasterPage->
/*N*/               CreatePresObj(PRESOBJ_HANDOUT, FALSE, aRect, TRUE);
/*N*/
/*N*/               pPageObj->SetPageNum( 2 * nPgNum + 1);
/*N*/
/*N*/               nPgNum++;
/*N*/               aPos.X() += aPartArea.Width() + nGapW;
/*N*/           }
/*N*/           aPos.Y() += aPartArea.Height() + nGapH;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if ( !bDeletePresObjOnMaster )
/*N*/   {
/*N*/       if (!pMasterTitle && ePageKind != PK_HANDOUT)
/*N*/       {
             /******************************************************************
             * Standard- oder Notiz-Seite: Titelbereich
             ******************************************************************/
/*N*/           Rectangle aTitleRect = GetTitleRect();
/*N*/           pMasterPage->CreatePresObj(PRESOBJ_TITLE, FALSE, aTitleRect, TRUE);
/*N*/       }
/*N*/
/*N*/       if (!pMasterOutline  && ePageKind != PK_HANDOUT)
/*N*/       {
             /******************************************************************
             * Standard- oder Notiz-Seite: Layoutbereich
            ******************************************************************/
/*N*/           Rectangle aLayoutRect = GetLayoutRect();
/*N*/
/*N*/           if (ePageKind == PK_STANDARD)
/*N*/           {
/*N*/               pMasterPage->CreatePresObj(PRESOBJ_OUTLINE, FALSE, aLayoutRect, TRUE);
/*N*/           }
/*N*/           else if (ePageKind == PK_NOTES)
/*N*/           {
/*N*/               pMasterPage->CreatePresObj(PRESOBJ_NOTES, FALSE, aLayoutRect, TRUE);
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/  }


/*************************************************************************
|*
|* Titelbereich zurueckgeben
|*
\************************************************************************/

/*N*/ Rectangle SdPage::GetTitleRect() const
/*N*/ {
/*N*/   Rectangle aTitleRect;
/*N*/
/*N*/   if (ePageKind != PK_HANDOUT)
/*N*/   {
        /******************************************************************
        * Standard- oder Notiz-Seite: Titelbereich
        ******************************************************************/
/*N*/       Point aTitlePos ( GetLftBorder(), GetUppBorder() );
/*N*/       Size aTitleSize ( GetSize() );
/*N*/       aTitleSize.Width()  -= GetLftBorder() + GetRgtBorder();
/*N*/       aTitleSize.Height() -= GetUppBorder() + GetLwrBorder();
/*N*/
/*N*/       if (ePageKind == PK_STANDARD)
/*N*/       {
/*N*/           aTitlePos.X() += long( aTitleSize.Width() * 0.0735 );
/*N*/           aTitlePos.Y() += long( aTitleSize.Height() * 0.083 );
/*N*/           aTitleSize.Width() = long( aTitleSize.Width() * 0.854 );
/*N*/           aTitleSize.Height() = long( aTitleSize.Height() * 0.167 );
/*N*/       }
/*N*/       else if (ePageKind == PK_NOTES)
/*N*/       {
/*N*/           // Hoehe beschraenken
/*N*/           aTitleSize.Height() = (long) (aTitleSize.Height() / 2.5);
/*N*/
/*N*/           Point aPos = aTitlePos;
/*N*/           aPos.Y() += long( aTitleSize.Height() * 0.083 );
/*N*/           Size aPartArea = aTitleSize;
/*N*/           Size aSize;
/*N*/
/*N*/           SdrPage* pPage = pModel->GetPage( GetPageNum() - 1 );
/*N*/
/*N*/           if ( pPage )
/*N*/           {
/*N*/               // tatsaechliche Seitengroesse in das Handout-Rechteck skalieren
/*N*/               double fH = (double) aPartArea.Width()  / pPage->GetWdt();
/*N*/               double fV = (double) aPartArea.Height() / pPage->GetHgt();
/*N*/
/*N*/               if ( fH > fV )
/*N*/                   fH = fV;
/*N*/               aSize.Width()  = (long) (fH * pPage->GetWdt());
/*N*/               aSize.Height() = (long) (fH * pPage->GetHgt());
/*N*/
/*N*/               aPos.X() += (aPartArea.Width() - aSize.Width()) / 2;
/*N*/               aPos.Y() += (aPartArea.Height()- aSize.Height())/ 2;
/*N*/           }
/*N*/
/*N*/           aTitlePos = aPos;
/*N*/           aTitleSize = aSize;
/*N*/       }
/*N*/
/*N*/       aTitleRect.SetPos(aTitlePos);
/*N*/       aTitleRect.SetSize(aTitleSize);
/*N*/   }
/*N*/
/*N*/   return aTitleRect;
/*N*/ }


/*************************************************************************
|*
|* Gliederungsbereich zurueckgeben
|*
\************************************************************************/

/*N*/ Rectangle SdPage::GetLayoutRect() const
/*N*/ {
/*N*/   Rectangle aLayoutRect;
/*N*/
/*N*/   if (ePageKind != PK_HANDOUT)
/*N*/   {
/*N*/       Point aLayoutPos ( GetLftBorder(), GetUppBorder() );
/*N*/       Size aLayoutSize ( GetSize() );
/*N*/       aLayoutSize.Width()  -= GetLftBorder() + GetRgtBorder();
/*N*/       aLayoutSize.Height() -= GetUppBorder() + GetLwrBorder();
/*N*/
/*N*/       if (ePageKind == PK_STANDARD)
/*N*/       {
/*N*/           aLayoutPos.X() += long( aLayoutSize.Width() * 0.0735 );
/*N*/           aLayoutPos.Y() += long( aLayoutSize.Height() * 0.278 );
/*N*/           aLayoutSize.Width() = long( aLayoutSize.Width() * 0.854 );
/*N*/           aLayoutSize.Height() = long( aLayoutSize.Height() * 0.630 );
/*N*/           aLayoutRect.SetPos(aLayoutPos);
/*N*/           aLayoutRect.SetSize(aLayoutSize);
/*N*/       }
/*N*/       else if (ePageKind == PK_NOTES)
/*N*/       {
/*N*/           aLayoutPos.X() += long( aLayoutSize.Width() * 0.0735 );
/*N*/           aLayoutPos.Y() += long( aLayoutSize.Height() * 0.472 );
/*N*/           aLayoutSize.Width() = long( aLayoutSize.Width() * 0.854 );
/*N*/           aLayoutSize.Height() = long( aLayoutSize.Height() * 0.444 );
/*N*/           aLayoutRect.SetPos(aLayoutPos);
/*N*/           aLayoutRect.SetSize(aLayoutSize);
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return aLayoutRect;
/*N*/ }


/**************************************************************************
|*
|* Diese Methode weist ein AutoLayout zu
|*
\*************************************************************************/

/*N*/ void SdPage::SetAutoLayout(AutoLayout eLayout, BOOL bInit, BOOL bAPICall )
/*N*/ {
/*N*/   eAutoLayout = eLayout;
/*N*/   bOwnArrangement = TRUE;
/*N*/
/*N*/   CreateTitleAndLayout(bInit, bAPICall);
/*N*/
/*N*/   if ((eAutoLayout == AUTOLAYOUT_NONE && aPresObjList.Count() == 0) ||
/*N*/       bMaster)
/*N*/   {
/*N*/       // MasterPage oder:
/*N*/       // Kein AutoLayout gewuenscht und keine Praesentationsobjekte
/*N*/       // vorhanden, also ist nichts zu tun
/*N*/       bOwnArrangement = FALSE;
/*N*/       return;
/*N*/   }
/*N*/
/*N*/   USHORT nIndex = 0;
/*N*/   ULONG nCount = aPresObjList.Count();
/*N*/   SdrObject* pObj = NULL;
/*N*/
/*N*/   for (nIndex = 0; nIndex < nCount; nIndex++)
/*N*/   {
/*N*/       pObj = (SdrObject*) aPresObjList.GetObject(nIndex);
/*N*/
/*N*/       if ( !pObj || pObj->GetPage() != this )
/*N*/       {
/*?*/           aPresObjList.Remove( pObj );
/*N*/       }
/*N*/   }
/*N*/
/*N*/   ULONG nMasterIndex = 0;
/*N*/   SdPage* pMasterPage = (SdPage*) GetMasterPage(0);
/*N*/   List* pList = pMasterPage->GetPresObjList();
/*N*/   ULONG nMasterCount = pList->Count();
/*N*/   SdrObject* pMasterObj = NULL;
/*N*/
/*N*/   Rectangle aTitleRect;
/*N*/   Rectangle aLayoutRect;
/*N*/   BOOL bFound = FALSE;
/*N*/
/*N*/   for (nMasterIndex = 0; nMasterIndex < nMasterCount; nMasterIndex++)
/*N*/   {
        /**********************************************************************
        * Schleife ueber alle Praesentationsobjekte der MasterPage
        **********************************************************************/
/*N*/       bFound = FALSE;
/*N*/       pMasterObj = (SdrObject*) pList->GetObject(nMasterIndex);
/*N*/
/*N*/       if (pMasterObj && pMasterObj->GetObjInventor() == SdrInventor)
/*N*/       {
/*N*/           UINT16 nId = pMasterObj->GetObjIdentifier();
/*N*/
/*N*/           if (nId == OBJ_TITLETEXT )
/*N*/           {
/*N*/               aTitleRect = pMasterObj->GetLogicRect();
/*N*/           }
/*N*/
/*N*/           if ((ePageKind!=PK_NOTES && nId == OBJ_OUTLINETEXT) ||
/*N*/               (ePageKind==PK_NOTES && nId == OBJ_TEXT))
/*N*/           {
/*N*/               aLayoutRect = pMasterObj->GetLogicRect();
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if (aTitleRect.IsEmpty() && ePageKind != PK_HANDOUT)
/*N*/   {
        /**********************************************************************
        * Titelobj. auf MasterPage nicht vorhanden -> Defaultgroesse bestimmen
        **********************************************************************/
/*N*/       aTitleRect = GetTitleRect();
/*N*/   }
/*N*/
/*N*/   if (aLayoutRect.IsEmpty() && ePageKind != PK_HANDOUT)
/*N*/   {
        /**********************************************************************
        * Gliederungsobj. auf MasterPage nicht vorhanden -> Defaultgroesse bestimmen
        **********************************************************************/
/*N*/       aLayoutRect = GetLayoutRect();
/*N*/   }
/*N*/
/*N*/   Rectangle   aRect0( aTitleRect );
/*N*/   Rectangle   aRect1( aLayoutRect );
/*N*/   Rectangle   aRect2( aLayoutRect );
/*N*/   Rectangle   aRect3( aLayoutRect );
/*N*/   Rectangle   aRect4( aLayoutRect );
/*N*/   Size        aTitleSize( aTitleRect.GetSize() );
/*N*/   Point       aTitlePos( aTitleRect.TopLeft() );
/*N*/   Size        aLayoutSize( aLayoutRect.GetSize() );
/*N*/   Point       aLayoutPos( aLayoutRect.TopLeft() );
/*N*/   Size        aTempSize;
/*N*/   Point       aTempPnt;
/*N*/   PresObjKind nObjKind[ MAX_PRESOBJ ];
/*N*/   List        aObjList;
/*N*/     sal_Bool    bRightToLeft = ( GetModel() && static_cast< SdDrawDocument* >( GetModel() )->GetDefaultWritingMode() == ::com::sun::star::text::WritingMode_RL_TB );
/*N*/
/*N*/   for (nIndex = 0; nIndex < MAX_PRESOBJ; nIndex++)
/*N*/   {
/*N*/       nObjKind[nIndex] = PRESOBJ_NONE;
/*N*/   }
/*N*/
/*N*/
/*N*/   switch (eAutoLayout)
/*N*/   {
/*N*/       case AUTOLAYOUT_NONE:
/*N*/       {
            /******************************************************************
            * Notwendig fuer Objekte aus dem Gliederungsmodus
            ******************************************************************/
/*N*/           nObjKind[0] = PRESOBJ_TITLE;
/*N*/           pObj = GetPresObj(nObjKind[0]);
/*N*/
/*N*/           if ( pObj && pObj->GetUserCall() )
/*N*/           {
/*?*/               pObj->SetLogicRect(aRect0);
/*?*/               pObj->SetUserCall(this);
/*N*/           }
/*N*/
/*N*/           if (pObj && !pObj->IsEmptyPresObj() || !bInit)
/*N*/               aObjList.Insert(pObj, LIST_APPEND);
/*N*/
/*N*/           nObjKind[1] = PRESOBJ_OUTLINE;
/*N*/           pObj = GetPresObj(nObjKind[1]);
/*N*/
/*N*/           if ( pObj && pObj->GetUserCall() )
/*N*/           {
/*?*/               pObj->SetLogicRect(aRect1);
/*?*/               pObj->SetUserCall(this);
/*N*/           }
/*N*/
/*N*/           if (pObj && !pObj->IsEmptyPresObj() || !bInit)
/*N*/               aObjList.Insert(pObj, LIST_APPEND);
/*N*/       }
/*N*/       break;
/*N*/
/*N*/       case AUTOLAYOUT_NOTES:
/*N*/       {
/*N*/           nObjKind[0] = PRESOBJ_PAGE;
/*N*/           pObj = GetPresObj(nObjKind[0]);
/*N*/           InsertPresObj(pObj, nObjKind[0], FALSE, aRect0, bInit, aObjList);
/*N*/
/*N*/           nObjKind[1] = PRESOBJ_NOTES;
/*N*/           pObj = GetPresObj(nObjKind[1]);
/*N*/           InsertPresObj(pObj, nObjKind[1], FALSE, aRect1, bInit, aObjList);
/*N*/       }
/*N*/       break;
/*N*/
/*N*/       case AUTOLAYOUT_TITLE:
/*N*/       {
/*N*/           nObjKind[0] = PRESOBJ_TITLE;
/*N*/           pObj = GetPresObj(nObjKind[0]);
/*N*/           InsertPresObj(pObj, nObjKind[0], FALSE, aRect0, bInit, aObjList);
/*N*/
/*N*/           nObjKind[1] = PRESOBJ_TEXT;
/*N*/           pObj = GetPresObj(nObjKind[1]);
/*N*/           InsertPresObj(pObj, nObjKind[1], FALSE, aRect1, bInit, aObjList);
/*N*/       }
/*N*/       break;
/*N*/
/*N*/       case AUTOLAYOUT_ENUM:
/*N*/       {
/*N*/           nObjKind[0] = PRESOBJ_TITLE;
/*N*/           pObj = GetPresObj(nObjKind[0]);
/*N*/           InsertPresObj(pObj, nObjKind[0], FALSE, aRect0, bInit, aObjList);
/*N*/
/*N*/           nObjKind[1] = PRESOBJ_OUTLINE;
/*N*/           pObj = GetPresObj(nObjKind[1]);
/*N*/           InsertPresObj(pObj, nObjKind[1], FALSE, aRect1, bInit, aObjList);
/*N*/       }
/*N*/       break;
/*N*/
/*N*/       case AUTOLAYOUT_CHART:
/*N*/       {
/*?*/           nObjKind[0] = PRESOBJ_TITLE;
/*?*/           pObj = GetPresObj(nObjKind[0]);
/*?*/           InsertPresObj(pObj, nObjKind[0], FALSE, aRect0, bInit, aObjList);
/*?*/
/*?*/           nObjKind[1] = PRESOBJ_CHART;
/*?*/           pObj = GetPresObj(nObjKind[1]);
/*?*/           InsertPresObj(pObj, nObjKind[1], FALSE, aRect1, bInit, aObjList);
/*?*/       }
/*?*/       break;
/*?*/
/*?*/       case AUTOLAYOUT_2TEXT:
/*?*/       {
/*?*/           aLayoutSize.Width()  = long (aLayoutSize.Width() * 0.488);
/*?*/           aRect1 = Rectangle (aLayoutPos, aLayoutSize);
/*?*/
/*?*/           aLayoutPos.X() = long (aLayoutPos.X() + aLayoutSize.Width() * 1.05);
/*?*/           aRect2 = Rectangle (aLayoutPos, aLayoutSize);
/*?*/
/*?*/             if( bRightToLeft )
/*?*/                 ::std::swap< Rectangle >( aRect1, aRect2 );
/*?*/
/*?*/           nObjKind[0] = PRESOBJ_TITLE;
/*?*/           pObj = GetPresObj(nObjKind[0]);
/*?*/           InsertPresObj(pObj, nObjKind[0], FALSE, aRect0, bInit, aObjList);
/*?*/
/*?*/           nObjKind[1] = PRESOBJ_OUTLINE;
/*?*/           pObj = GetPresObj(nObjKind[1]);
/*?*/           USHORT nIndex = 1;
/*?*/           if ( InsertPresObj(pObj, nObjKind[1], FALSE, aRect1, bInit, aObjList) )
/*?*/               nIndex++;
/*?*/
/*?*/           nObjKind[2] = PRESOBJ_OUTLINE;
/*?*/           pObj = GetPresObj(nObjKind[2], nIndex);
/*?*/           InsertPresObj(pObj, nObjKind[2], FALSE, aRect2, bInit, aObjList);
/*?*/       }
/*?*/       break;
/*?*/
/*?*/       case AUTOLAYOUT_TEXTCHART:
/*?*/       {
/*?*/           aLayoutSize.Width()  = long (aLayoutSize.Width() * 0.488);
/*?*/           aRect1 = Rectangle (aLayoutPos, aLayoutSize);
/*?*/
/*?*/           aLayoutPos.X() = long (aLayoutPos.X() + aLayoutSize.Width() * 1.05);
/*?*/           aRect2 = Rectangle (aLayoutPos, aLayoutSize);
/*?*/
/*?*/             if( bRightToLeft )
/*?*/                 ::std::swap< Rectangle >( aRect1, aRect2 );
/*?*/
/*?*/           nObjKind[0] = PRESOBJ_TITLE;
/*?*/           pObj = GetPresObj(nObjKind[0]);
/*?*/           InsertPresObj(pObj, nObjKind[0], FALSE, aRect0, bInit, aObjList);
/*?*/
/*?*/           nObjKind[1] = PRESOBJ_OUTLINE;
/*?*/           pObj = GetPresObj(nObjKind[1]);
/*?*/           InsertPresObj(pObj, nObjKind[1], FALSE, aRect1, bInit, aObjList);
/*?*/
/*?*/           nObjKind[2] = PRESOBJ_CHART;
/*?*/           pObj = GetPresObj(nObjKind[2]);
/*?*/           InsertPresObj(pObj, nObjKind[2], FALSE, aRect2, bInit, aObjList);
/*?*/       }
/*?*/       break;
/*?*/
/*?*/       case AUTOLAYOUT_ORG:
/*?*/       {
/*?*/           nObjKind[0] = PRESOBJ_TITLE;
/*?*/           pObj = GetPresObj(nObjKind[0]);
/*?*/           InsertPresObj(pObj, nObjKind[0], FALSE, aRect0, bInit, aObjList);
/*?*/
/*?*/           nObjKind[1] = PRESOBJ_ORGCHART;
/*?*/           pObj = GetPresObj(nObjKind[1]);
/*?*/           InsertPresObj(pObj, nObjKind[1], FALSE, aRect1, bInit, aObjList);
/*?*/       }
/*?*/       break;
/*?*/
/*?*/       case AUTOLAYOUT_TEXTCLIP:
/*?*/       {
/*?*/           aLayoutSize.Width()  = long (aLayoutSize.Width() * 0.488);
/*?*/           aRect1 = Rectangle (aLayoutPos, aLayoutSize);
/*?*/
/*?*/           aLayoutPos.X() = long (aLayoutPos.X() + aLayoutSize.Width() * 1.05);
/*?*/           aRect2 = Rectangle (aLayoutPos, aLayoutSize);
/*?*/
/*?*/             if( bRightToLeft )
/*?*/                 ::std::swap< Rectangle >( aRect1, aRect2 );
/*?*/
/*?*/           nObjKind[0] = PRESOBJ_TITLE;
/*?*/           pObj = GetPresObj(nObjKind[0]);
/*?*/           InsertPresObj(pObj, nObjKind[0], FALSE, aRect0, bInit, aObjList);
/*?*/
/*?*/           nObjKind[1] = PRESOBJ_OUTLINE;
/*?*/           pObj = GetPresObj(nObjKind[1]);
/*?*/           InsertPresObj(pObj, nObjKind[1], FALSE, aRect1, bInit, aObjList);
/*?*/
/*?*/           nObjKind[2] = PRESOBJ_GRAPHIC;
/*?*/           pObj = GetPresObj(nObjKind[2]);
/*?*/           InsertPresObj(pObj, nObjKind[2], FALSE, aRect2, bInit, aObjList);
/*?*/       }
/*?*/       break;
/*?*/
/*?*/       case AUTOLAYOUT_CHARTTEXT:
/*?*/       {
/*?*/           aLayoutSize.Width()  = long (aLayoutSize.Width() * 0.488);
/*?*/           aRect1 = Rectangle (aLayoutPos, aLayoutSize);
/*?*/
/*?*/           aLayoutPos.X() = long (aLayoutPos.X() + aLayoutSize.Width() * 1.05);
/*?*/           aRect2 = Rectangle (aLayoutPos, aLayoutSize);
/*?*/
/*?*/             if( bRightToLeft )
/*?*/                 ::std::swap< Rectangle >( aRect1, aRect2 );
/*?*/
/*?*/           nObjKind[0] = PRESOBJ_TITLE;
/*?*/           pObj = GetPresObj(nObjKind[0]);
/*?*/           InsertPresObj(pObj, nObjKind[0], FALSE, aRect0, bInit, aObjList);
/*?*/
/*?*/           nObjKind[1] = PRESOBJ_CHART;
/*?*/           pObj = GetPresObj(nObjKind[1]);
/*?*/           InsertPresObj(pObj, nObjKind[1], FALSE, aRect1, bInit, aObjList);
/*?*/
/*?*/           nObjKind[2] = PRESOBJ_OUTLINE;
/*?*/           pObj = GetPresObj(nObjKind[2]);
/*?*/           InsertPresObj(pObj, nObjKind[2], FALSE, aRect2, bInit, aObjList);
/*?*/       }
/*?*/       break;
/*?*/
/*?*/       case AUTOLAYOUT_TAB:
/*?*/       {
/*?*/           nObjKind[0] = PRESOBJ_TITLE;
/*?*/           pObj = GetPresObj(nObjKind[0]);
/*?*/           InsertPresObj(pObj, nObjKind[0], FALSE, aRect0, bInit, aObjList);
/*?*/
/*?*/           nObjKind[1] = PRESOBJ_TABLE;
/*?*/           pObj = GetPresObj(nObjKind[1]);
/*?*/           InsertPresObj(pObj, nObjKind[1], FALSE, aRect1, bInit, aObjList);
/*?*/       }
/*?*/       break;
/*?*/
/*?*/       case AUTOLAYOUT_CLIPTEXT:
/*?*/       {
/*?*/           aLayoutSize.Width()  = long (aLayoutSize.Width() * 0.488);
/*?*/           aRect1 = Rectangle (aLayoutPos, aLayoutSize);
/*?*/
/*?*/           aLayoutPos.X() = long (aLayoutPos.X() + aLayoutSize.Width() * 1.05);
/*?*/           aRect2 = Rectangle (aLayoutPos, aLayoutSize);
/*?*/
/*?*/             if( bRightToLeft )
/*?*/                 ::std::swap< Rectangle >( aRect1, aRect2 );
/*?*/
/*?*/           nObjKind[0] = PRESOBJ_TITLE;
/*?*/           pObj = GetPresObj(nObjKind[0]);
/*?*/           InsertPresObj(pObj, nObjKind[0], FALSE, aRect0, bInit, aObjList);
/*?*/
/*?*/           nObjKind[1] = PRESOBJ_GRAPHIC;
/*?*/           pObj = GetPresObj(nObjKind[1]);
/*?*/           InsertPresObj(pObj, nObjKind[1], FALSE, aRect1, bInit, aObjList);
/*?*/
/*?*/           nObjKind[2] = PRESOBJ_OUTLINE;
/*?*/           pObj = GetPresObj(nObjKind[2]);
/*?*/           InsertPresObj(pObj, nObjKind[2], FALSE, aRect2, bInit, aObjList);
/*?*/       }
/*?*/       break;
/*?*/
/*?*/       case AUTOLAYOUT_TEXTOBJ:
/*?*/       {
/*?*/           aLayoutSize.Width()  = long (aLayoutSize.Width() * 0.488);
/*?*/           aRect1 = Rectangle (aLayoutPos, aLayoutSize);
/*?*/
/*?*/           aLayoutPos.X() = long (aLayoutPos.X() + aLayoutSize.Width() * 1.05);
/*?*/           aRect2 = Rectangle (aLayoutPos, aLayoutSize);
/*?*/
/*?*/             if( bRightToLeft )
/*?*/                 ::std::swap< Rectangle >( aRect1, aRect2 );
/*?*/
/*?*/           nObjKind[0] = PRESOBJ_TITLE;
/*?*/           pObj = GetPresObj(nObjKind[0]);
/*?*/           InsertPresObj(pObj, nObjKind[0], FALSE, aRect0, bInit, aObjList);
/*?*/
/*?*/           nObjKind[1] = PRESOBJ_OUTLINE;
/*?*/           pObj = GetPresObj(nObjKind[1]);
/*?*/           InsertPresObj(pObj, nObjKind[1], FALSE, aRect1, bInit, aObjList);
/*?*/
/*?*/           nObjKind[2] = PRESOBJ_OBJECT;
/*?*/           pObj = GetPresObj(nObjKind[2]);
/*?*/           InsertPresObj(pObj, nObjKind[2], FALSE, aRect2, bInit, aObjList);
/*?*/       }
/*?*/       break;
/*?*/
/*?*/       case AUTOLAYOUT_OBJ:
/*?*/       {
/*?*/           nObjKind[0] = PRESOBJ_TITLE;
/*?*/           pObj = GetPresObj(nObjKind[0]);
/*?*/           InsertPresObj(pObj, nObjKind[0], FALSE, aRect0, bInit, aObjList);
/*?*/
/*?*/           nObjKind[1] = PRESOBJ_OBJECT;
/*?*/           pObj = GetPresObj(nObjKind[1]);
/*?*/           InsertPresObj(pObj, nObjKind[1], FALSE, aRect1, bInit, aObjList);
/*?*/       }
/*?*/       break;
/*?*/
/*?*/       case AUTOLAYOUT_TEXT2OBJ:
/*?*/       {
/*?*/           aTempPnt = aLayoutPos;
/*?*/           aTempSize = aLayoutSize;
/*?*/           aLayoutSize.Height() = long (aLayoutSize.Height() * 0.477);
/*?*/           aLayoutSize.Width() = long (aLayoutSize.Width() * 0.488);
/*?*/           aLayoutPos.X() = long (aLayoutPos.X() + aLayoutSize.Width() * 1.05);
/*?*/           aRect2 = Rectangle (aLayoutPos, aLayoutSize);
/*?*/
/*?*/           aLayoutPos.Y() = long (aLayoutPos.Y() + aLayoutSize.Height() * 1.095);
/*?*/           aRect3 = Rectangle (aLayoutPos, aLayoutSize);
/*?*/
/*?*/           aLayoutPos = aTempPnt;
/*?*/           aLayoutSize = aTempSize;
/*?*/           aLayoutSize.Width() = long (aLayoutSize.Width() * 0.488);
/*?*/           aRect1 = Rectangle (aLayoutPos, aLayoutSize);
/*?*/
/*?*/             if( bRightToLeft )
/*?*/             {
/*?*/                 ::std::swap< long >( aRect1.Left(), aRect2.Left() );
/*?*/                 aRect3.Left() = aRect2.Left();
/*?*/             }
/*?*/
/*?*/           nObjKind[0] = PRESOBJ_TITLE;
/*?*/           pObj = GetPresObj(nObjKind[0]);
/*?*/           InsertPresObj(pObj, nObjKind[0], FALSE, aRect0, bInit, aObjList);
/*?*/
/*?*/           nObjKind[1] = PRESOBJ_OUTLINE;
/*?*/           pObj = GetPresObj(nObjKind[1]);
/*?*/           InsertPresObj(pObj, nObjKind[1], FALSE, aRect1, bInit, aObjList);
/*?*/
/*?*/           nObjKind[2] = PRESOBJ_OBJECT;
/*?*/           pObj = GetPresObj(nObjKind[2]);
/*?*/           USHORT nIndex = 1;
/*?*/           if ( InsertPresObj(pObj, nObjKind[2], FALSE, aRect2, bInit, aObjList) )
/*?*/               nIndex++;
/*?*/
/*?*/           nObjKind[3] = PRESOBJ_OBJECT;
/*?*/           pObj = GetPresObj(nObjKind[3], nIndex);
/*?*/           InsertPresObj(pObj, nObjKind[3], FALSE, aRect3, bInit, aObjList);
/*?*/       }
/*?*/       break;
/*?*/
/*?*/       case AUTOLAYOUT_OBJTEXT:
/*?*/       {
/*?*/           aLayoutSize.Width()  = long (aLayoutSize.Width() * 0.488);
/*?*/           aRect1 = Rectangle (aLayoutPos, aLayoutSize);
/*?*/
/*?*/           aLayoutPos.X() = long (aLayoutPos.X() + aLayoutSize.Width() * 1.05);
/*?*/           aRect2 = Rectangle (aLayoutPos, aLayoutSize);
/*?*/
/*?*/             if( bRightToLeft )
/*?*/                 ::std::swap< Rectangle >( aRect1, aRect2 );
/*?*/
/*?*/           nObjKind[0] = PRESOBJ_TITLE;
/*?*/           pObj = GetPresObj(nObjKind[0]);
/*?*/           InsertPresObj(pObj, nObjKind[0], FALSE, aRect0, bInit, aObjList);
/*?*/
/*?*/           nObjKind[1] = PRESOBJ_OBJECT;
/*?*/           pObj = GetPresObj(nObjKind[1]);
/*?*/           InsertPresObj(pObj, nObjKind[1], FALSE, aRect1, bInit, aObjList);
/*?*/
/*?*/           nObjKind[2] = PRESOBJ_OUTLINE;
/*?*/           pObj = GetPresObj(nObjKind[2]);
/*?*/           InsertPresObj(pObj, nObjKind[2], FALSE, aRect2, bInit, aObjList);
/*?*/       }
/*?*/       break;
/*?*/
/*?*/       case AUTOLAYOUT_OBJOVERTEXT:
/*?*/       {
/*?*/           aLayoutSize.Height() = long (aLayoutSize.Height() * 0.477);
/*?*/           aRect1 = Rectangle (aLayoutPos, aLayoutSize);
/*?*/
/*?*/           aLayoutPos.Y() = long (aLayoutPos.Y() + aLayoutSize.Height() * 1.095);
/*?*/           aRect2 = Rectangle (aLayoutPos, aLayoutSize);
/*?*/
/*?*/           nObjKind[0] = PRESOBJ_TITLE;
/*?*/           pObj = GetPresObj(nObjKind[0]);
/*?*/           InsertPresObj(pObj, nObjKind[0], FALSE, aRect0, bInit, aObjList);
/*?*/
/*?*/           nObjKind[1] = PRESOBJ_OBJECT;
/*?*/           pObj = GetPresObj(nObjKind[1]);
/*?*/           InsertPresObj(pObj, nObjKind[1], FALSE, aRect1, bInit, aObjList);
/*?*/
/*?*/           nObjKind[2] = PRESOBJ_OUTLINE;
/*?*/           pObj = GetPresObj(nObjKind[2]);
/*?*/           InsertPresObj(pObj, nObjKind[2], FALSE, aRect2, bInit, aObjList);
/*?*/       }
/*?*/       break;
/*?*/
/*?*/       case AUTOLAYOUT_2OBJTEXT:
/*?*/       {
/*?*/           aTempPnt = aLayoutPos;
/*?*/           aTempSize = aLayoutSize;
/*?*/           aLayoutSize.Height() = long (aLayoutSize.Height() * 0.477);
/*?*/           aLayoutSize.Width() = long (aLayoutSize.Width() * 0.488);
/*?*/           aRect1 = Rectangle (aLayoutPos, aLayoutSize);
/*?*/
/*?*/           aLayoutPos.Y() = long (aLayoutPos.Y() + aLayoutSize.Height() * 1.095);
/*?*/           aRect2 = Rectangle (aLayoutPos, aLayoutSize);
/*?*/
/*?*/           aLayoutPos = aTempPnt;
/*?*/           aLayoutSize = aTempSize;
/*?*/           aLayoutSize.Width() = long (aLayoutSize.Width() * 0.488);
/*?*/           aLayoutPos.X() = long (aLayoutPos.X() + aLayoutSize.Width() * 1.05);
/*?*/           aRect3 = Rectangle (aLayoutPos, aLayoutSize);
/*?*/
/*?*/             if( bRightToLeft )
/*?*/             {
/*?*/                 ::std::swap< long >( aRect1.Left(), aRect2.Left() );
/*?*/                 aRect3.Left() = aRect2.Left();
/*?*/             }
/*?*/
/*?*/           nObjKind[0] = PRESOBJ_TITLE;
/*?*/           pObj = GetPresObj(nObjKind[0]);
/*?*/           InsertPresObj(pObj, nObjKind[0], FALSE, aRect0, bInit, aObjList);
/*?*/
/*?*/           nObjKind[1] = PRESOBJ_OBJECT;
/*?*/           pObj = GetPresObj(nObjKind[1]);
/*?*/           USHORT nIndex = 1;
/*?*/           if ( InsertPresObj(pObj, nObjKind[1], FALSE, aRect1, bInit, aObjList) )
/*?*/               nIndex++;
/*?*/
/*?*/           nObjKind[2] = PRESOBJ_OBJECT;
/*?*/           pObj = GetPresObj(nObjKind[2], nIndex);
/*?*/           InsertPresObj(pObj, nObjKind[2], FALSE, aRect2, bInit, aObjList);
/*?*/
/*?*/           nObjKind[3] = PRESOBJ_OUTLINE;
/*?*/           pObj = GetPresObj(nObjKind[3]);
/*?*/           InsertPresObj(pObj, nObjKind[3], FALSE, aRect3, bInit, aObjList);
/*?*/       }
/*?*/       break;
/*?*/
/*?*/       case AUTOLAYOUT_2OBJOVERTEXT:
/*?*/       {
/*?*/           aLayoutSize.Height() = long (aLayoutSize.Height() * 0.477);
/*?*/           aLayoutSize.Width() = long (aLayoutSize.Width() * 0.488);
/*?*/           aRect1 = Rectangle (aLayoutPos, aLayoutSize);
/*?*/
/*?*/           aTempPnt = aLayoutPos;
/*?*/           aLayoutPos.X() = long (aLayoutPos.X() + aLayoutSize.Width() * 1.05);
/*?*/           aRect2 = Rectangle (aLayoutPos, aLayoutSize);
/*?*/
/*?*/           aLayoutPos.X() = aTempPnt.X();
/*?*/           aLayoutPos.Y() = long (aLayoutPos.Y() + aLayoutSize.Height() * 1.095);
/*?*/           aLayoutSize.Width() = long (aLayoutSize.Width() / 0.488);
/*?*/           aRect3 = Rectangle (aLayoutPos, aLayoutSize);
/*?*/
/*?*/           nObjKind[0] = PRESOBJ_TITLE;
/*?*/           pObj = GetPresObj(nObjKind[0]);
/*?*/           InsertPresObj(pObj, nObjKind[0], FALSE, aRect0, bInit, aObjList);
/*?*/
/*?*/           nObjKind[1] = PRESOBJ_OBJECT;
/*?*/           pObj = GetPresObj(nObjKind[1]);
/*?*/           USHORT nIndex = 1;
/*?*/           if ( InsertPresObj(pObj, nObjKind[1], FALSE, aRect1, bInit, aObjList) )
/*?*/               nIndex++;
/*?*/
/*?*/           nObjKind[2] = PRESOBJ_OBJECT;
/*?*/           pObj = GetPresObj(nObjKind[2], nIndex);
/*?*/           InsertPresObj(pObj, nObjKind[2], FALSE, aRect2, bInit, aObjList);
/*?*/
/*?*/           nObjKind[3] = PRESOBJ_OUTLINE;
/*?*/           pObj = GetPresObj(nObjKind[3]);
/*?*/           InsertPresObj(pObj, nObjKind[3], FALSE, aRect3, bInit, aObjList);
/*?*/       }
/*?*/       break;
/*?*/
/*?*/       case AUTOLAYOUT_TEXTOVEROBJ:
/*?*/       {
/*?*/           aLayoutSize.Height() = long (aLayoutSize.Height() * 0.477);
/*?*/           aRect1 = Rectangle (aLayoutPos, aLayoutSize);
/*?*/
/*?*/           aLayoutPos.Y() = long (aLayoutPos.Y() + aLayoutSize.Height() * 1.095);
/*?*/           aRect2 = Rectangle (aLayoutPos, aLayoutSize);
/*?*/
/*?*/           nObjKind[0] = PRESOBJ_TITLE;
/*?*/           pObj = GetPresObj(nObjKind[0]);
/*?*/           InsertPresObj(pObj, nObjKind[0], FALSE, aRect0, bInit, aObjList);
/*?*/
/*?*/           nObjKind[1] = PRESOBJ_OUTLINE;
/*?*/           pObj = GetPresObj(nObjKind[1]);
/*?*/           InsertPresObj(pObj, nObjKind[1], FALSE, aRect1, bInit, aObjList);
/*?*/
/*?*/           nObjKind[2] = PRESOBJ_OBJECT;
/*?*/           pObj = GetPresObj(nObjKind[2]);
/*?*/           InsertPresObj(pObj, nObjKind[2], FALSE, aRect2, bInit, aObjList);
/*?*/       }
/*?*/       break;
/*?*/
/*?*/       case AUTOLAYOUT_4OBJ:
/*?*/       {
/*?*/           ULONG nX = long (aLayoutPos.X());
/*?*/           ULONG nY = long (aLayoutPos.Y());
/*?*/
/*?*/           aLayoutSize.Height() = long (aLayoutSize.Height() * 0.477);
/*?*/           aLayoutSize.Width()  = long (aLayoutSize.Width() * 0.488);
/*?*/           aRect1 = Rectangle (aLayoutPos, aLayoutSize);
/*?*/
/*?*/           aLayoutPos.X() = long (nX + aLayoutSize.Width() * 1.05);
/*?*/           aRect2 = Rectangle (aLayoutPos, aLayoutSize);
/*?*/
/*?*/           aLayoutPos.Y() = long (aLayoutPos.Y() + aLayoutSize.Height() * 1.095);
/*?*/           aRect3 = Rectangle (aLayoutPos, aLayoutSize);
/*?*/
/*?*/           aLayoutPos.X() = nX;
/*?*/           aRect4 = Rectangle (aLayoutPos, aLayoutSize);
/*?*/
/*?*/           nObjKind[0] = PRESOBJ_TITLE;
/*?*/           pObj = GetPresObj(nObjKind[0]);
/*?*/           InsertPresObj(pObj, nObjKind[0], FALSE, aRect0, bInit, aObjList);
/*?*/
/*?*/           nObjKind[1] = PRESOBJ_OBJECT;
/*?*/           pObj = GetPresObj(nObjKind[1]);
/*?*/           USHORT nIndex = 1;
/*?*/           if ( InsertPresObj(pObj, nObjKind[1], FALSE, aRect1, bInit, aObjList) )
/*?*/               nIndex++;
/*?*/
/*?*/           nObjKind[2] = PRESOBJ_OBJECT;
/*?*/           pObj = GetPresObj(nObjKind[2], nIndex);
/*?*/           if ( InsertPresObj(pObj, nObjKind[2], FALSE, aRect2, bInit, aObjList) )
/*?*/               nIndex++;
/*?*/
/*?*/           nObjKind[3] = PRESOBJ_OBJECT;
/*?*/           pObj = GetPresObj(nObjKind[3], nIndex);
/*?*/           if ( InsertPresObj(pObj, nObjKind[3], FALSE, aRect3, bInit, aObjList) )
/*?*/               nIndex++;
/*?*/
/*?*/           nObjKind[4] = PRESOBJ_OBJECT;
/*?*/           pObj = GetPresObj(nObjKind[4], nIndex);
/*?*/           InsertPresObj(pObj, nObjKind[4], FALSE, aRect4, bInit, aObjList);
/*?*/       }
/*?*/       break;
/*N*/
/*N*/       case AUTOLAYOUT_ONLY_TITLE:
/*N*/       {
/*N*/           nObjKind[0] = PRESOBJ_TITLE;
/*N*/           pObj = GetPresObj(nObjKind[0]);
/*N*/           InsertPresObj(pObj, nObjKind[0], FALSE, aRect0, bInit, aObjList);
/*N*/       }
/*N*/       break;
/*N*/
/*N*/       case AUTOLAYOUT_VERTICAL_TITLE_TEXT_CHART:
/*N*/       {
/*?*/           Size aSize( aRect0.GetSize().Height(), aRect1.BottomLeft().Y() - aRect0.TopLeft().Y() );
/*?*/           aRect0.SetSize( aSize );
/*?*/           aRect0.SetPos( aTitleRect.TopRight() - Point( aSize.Width(), 0 ) );
/*?*/           nObjKind[0] = PRESOBJ_TITLE;
/*?*/           pObj = GetPresObj(nObjKind[0]);
/*?*/           InsertPresObj(pObj, nObjKind[0], TRUE, aRect0, bInit, aObjList);
/*?*/           pObj = GetPresObj(nObjKind[0]);
/*?*/           if ( pObj )
/*?*/           {
/*?*/               pObj->SetItem( SdrTextAutoGrowWidthItem(TRUE) );
/*?*/               pObj->SetItem( SdrTextAutoGrowHeightItem(FALSE) );
/*?*/           }
/*?*/           Size aLayoutSize ( GetSize() );
/*?*/           aLayoutSize.Height() -= GetUppBorder() + GetLwrBorder();
/*?*/           aSize.Height() = long ( aRect0.GetSize().Height() * 0.47 );
/*?*/           aSize.Width() = long( aLayoutSize.Width() * 0.7 );
/*?*/           aRect1.SetPos( aTitleRect.TopLeft() );
/*?*/           aRect1.SetSize( aSize );
/*?*/           nObjKind[1] = PRESOBJ_OUTLINE;
/*?*/           pObj = GetPresObj(nObjKind[1]);
/*?*/           InsertPresObj(pObj, nObjKind[1], TRUE, aRect1, bInit, aObjList);
/*?*/           pObj = GetPresObj(nObjKind[1]);
/*?*/           if ( pObj )
/*?*/           {
/*?*/               pObj->SetItem( SdrTextAutoGrowWidthItem(TRUE) );
/*?*/               pObj->SetItem( SdrTextAutoGrowHeightItem(FALSE) );
/*?*/
/*?*/               // #90790#
/*?*/               pObj->SetItem( SdrTextVertAdjustItem(SDRTEXTVERTADJUST_TOP) );
/*?*/               pObj->SetItem( SdrTextHorzAdjustItem(SDRTEXTHORZADJUST_RIGHT) );
/*?*/ //                pObj->SetLogicRect( aRect1 );   // sj: #98326#
/*?*/           }
/*?*/           aSize.Height() = aRect0.GetSize().Height();
/*?*/           Point aPos( aTitleRect.TopLeft() );
/*?*/           aPos.Y() += long ( aSize.Height() * 0.53 );
/*?*/           aRect2.SetPos( aPos );
/*?*/           aSize.Height() = long ( aRect0.GetSize().Height() * 0.47 );
/*?*/           aRect2.SetSize( aSize );
/*?*/           nObjKind[2] = PRESOBJ_CHART;
/*?*/           pObj = GetPresObj(nObjKind[2]);
/*?*/           InsertPresObj(pObj, nObjKind[2], FALSE, aRect2, bInit, aObjList);
/*?*/       }
/*?*/       break;
/*?*/
/*?*/       case AUTOLAYOUT_VERTICAL_TITLE_VERTICAL_OUTLINE:
/*?*/       {
/*?*/           Size aSize( aRect0.GetSize().Height(), aRect1.BottomLeft().Y() - aRect0.TopLeft().Y() );
/*?*/           aRect0.SetSize( aSize );
/*?*/           aRect0.SetPos( aTitleRect.TopRight() - Point( aSize.Width(), 0 ) );
/*?*/           nObjKind[0] = PRESOBJ_TITLE;
/*?*/           pObj = GetPresObj(nObjKind[0]);
/*?*/           InsertPresObj(pObj, nObjKind[0], TRUE, aRect0, bInit, aObjList);
/*?*/           pObj = GetPresObj(nObjKind[0]);
/*?*/           if ( pObj )
/*?*/           {
/*?*/               pObj->SetItem( SdrTextAutoGrowWidthItem(TRUE) );
/*?*/               pObj->SetItem( SdrTextAutoGrowHeightItem(FALSE) );
/*?*/           }
/*?*/           Size aLayoutSize ( GetSize() );
/*?*/           aLayoutSize.Height() -= GetUppBorder() + GetLwrBorder();
/*?*/           aSize.Height() = aRect0.GetSize().Height();
/*?*/           aSize.Width() = long( aLayoutSize.Width() * 0.7 );
/*?*/           aRect1.SetPos( aTitleRect.TopLeft() );
/*?*/           aRect1.SetSize( aSize );
/*?*/           nObjKind[1] = PRESOBJ_OUTLINE;
/*?*/           pObj = GetPresObj(nObjKind[1]);
/*?*/           InsertPresObj(pObj, nObjKind[1], TRUE, aRect1, bInit, aObjList);
/*?*/           pObj = GetPresObj(nObjKind[1]);
/*?*/           if ( pObj )
/*?*/           {
/*?*/               pObj->SetItem( SdrTextAutoGrowWidthItem(TRUE) );
/*?*/               pObj->SetItem( SdrTextAutoGrowHeightItem(FALSE) );
/*?*/
/*?*/               // #90790#
/*?*/               pObj->SetItem( SdrTextVertAdjustItem(SDRTEXTVERTADJUST_TOP) );
/*?*/               pObj->SetItem( SdrTextHorzAdjustItem(SDRTEXTHORZADJUST_RIGHT) );
/*?*/           }
/*?*/       }
/*?*/       break;
/*?*/
/*?*/       case AUTOLAYOUT_TITLE_VERTICAL_OUTLINE:
/*?*/       {
/*?*/           nObjKind[0] = PRESOBJ_TITLE;
/*?*/           pObj = GetPresObj(nObjKind[0]);
/*?*/           InsertPresObj(pObj, nObjKind[0], FALSE, aRect0, bInit, aObjList);
/*?*/
/*?*/           nObjKind[1] = PRESOBJ_OUTLINE;
/*?*/           pObj = GetPresObj(nObjKind[1]);
/*?*/           InsertPresObj(pObj, nObjKind[1], TRUE, aRect1, bInit, aObjList);
/*?*/           pObj = GetPresObj(nObjKind[1]);
/*?*/           if ( pObj )
/*?*/           {
/*?*/               pObj->SetItem( SdrTextAutoGrowWidthItem(TRUE) );
/*?*/               pObj->SetItem( SdrTextAutoGrowHeightItem(FALSE) );
/*?*/
/*?*/               // #90790#
/*?*/               pObj->SetItem( SdrTextVertAdjustItem(SDRTEXTVERTADJUST_TOP) );
/*?*/               pObj->SetItem( SdrTextHorzAdjustItem(SDRTEXTHORZADJUST_RIGHT) );
/*?*/           }
/*?*/       }
/*?*/       break;
/*?*/
/*?*/       case AUTOLAYOUT_TITLE_VERTICAL_OUTLINE_CLIPART:
/*?*/       {
/*?*/           aLayoutSize.Width()  = long (aLayoutSize.Width() * 0.488);
/*?*/           aRect1 = Rectangle (aLayoutPos, aLayoutSize);
/*?*/
/*?*/           aLayoutPos.X() = long (aLayoutPos.X() + aLayoutSize.Width() * 1.05);
/*?*/           aRect2 = Rectangle (aLayoutPos, aLayoutSize);
/*?*/
/*?*/           nObjKind[0] = PRESOBJ_TITLE;
/*?*/           pObj = GetPresObj(nObjKind[0]);
/*?*/           InsertPresObj(pObj, nObjKind[0], FALSE, aRect0, bInit, aObjList);
/*?*/
/*?*/           nObjKind[1] = PRESOBJ_GRAPHIC;
/*?*/           pObj = GetPresObj(nObjKind[1]);
/*?*/           InsertPresObj(pObj, nObjKind[1], FALSE, aRect1, bInit, aObjList);
/*?*/
/*?*/           nObjKind[2] = PRESOBJ_OUTLINE;
/*?*/           pObj = GetPresObj(nObjKind[2]);
/*?*/           InsertPresObj(pObj, nObjKind[2], TRUE, aRect2, bInit, aObjList);
/*?*/           pObj = GetPresObj(nObjKind[2]);
/*?*/           if ( pObj )
/*?*/           {
/*?*/               pObj->SetItem( SdrTextAutoGrowWidthItem(TRUE) );
/*?*/               pObj->SetItem( SdrTextAutoGrowHeightItem(FALSE) );
/*?*/
/*?*/               // #90790#
/*?*/               pObj->SetItem( SdrTextVertAdjustItem(SDRTEXTVERTADJUST_TOP) );
/*?*/               pObj->SetItem( SdrTextHorzAdjustItem(SDRTEXTHORZADJUST_RIGHT) );
/*?*/           }
/*N*/       }
/*N*/       break;
/*N*/
/*N*/       default:
/*N*/       break;
/*N*/   }
/*N*/
/*N*/   nCount = aPresObjList.Count();
/*N*/
/*N*/   for (nIndex=0; nIndex<nCount; nIndex++)
/*N*/   {
/*N*/       pObj = (SdrObject*) aPresObjList.GetObject(nIndex);
/*N*/
/*N*/       if (pObj && aObjList.GetPos(pObj) == LIST_ENTRY_NOTFOUND)
/*N*/       {
/*?*/           if ( pObj->IsEmptyPresObj() )
/*?*/           {
/*?*/               delete RemoveObject( pObj->GetOrdNum() );
/*?*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   aPresObjList.Clear();
/*N*/   aPresObjList = aObjList;
/*N*/
/*N*/   bOwnArrangement = FALSE;
/*N*/ }

/*************************************************************************
|*
|* Objekt einfuegen
|*
\************************************************************************/

/*N*/ void SdPage::NbcInsertObject(SdrObject* pObj, ULONG nPos, const SdrInsertReason* pReason)
/*N*/ {
/*N*/   FmFormPage::NbcInsertObject(pObj, nPos, pReason);
/*N*/
/*N*/   ((SdDrawDocument*) pModel)->InsertObject(pObj, this);
/*N*/
/*N*/   SdrLayerID nId = pObj->GetLayer();
/*N*/   if( bMaster )
/*N*/   {
/*N*/       if( nId == 0 )
/*N*/           pObj->NbcSetLayer( 2 );     // wrong layer. corrected to BackgroundObj layer
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       if( nId == 2 )
/*N*/           pObj->NbcSetLayer( 0 );     // wrong layer. corrected to layout layer
/*N*/   }
/*N*/ }


/*************************************************************************
|*
|* Objekt loeschen
|*
\************************************************************************/

/*N*/ SdrObject* SdPage::RemoveObject(ULONG nObjNum)
/*N*/ {
/*N*/   SdrObject* pObj = FmFormPage::RemoveObject(nObjNum);

/*N*/   if (pObj && pObj->GetUserCall()!=this &&
/*N*/       aPresObjList.GetPos(pObj) != LIST_ENTRY_NOTFOUND)
/*N*/   {
        // Objekt hat keinen UserCall auf diese Seite, es ist jedoch noch in
        // der PresObjList eingetragen -> austragen
/*?*/       Changed(*pObj, SDRUSERCALL_REMOVED, pObj->GetBoundRect());
/*N*/   }

/*N*/   ((SdDrawDocument*) pModel)->RemoveObject(pObj, this);

/*N*/   return(pObj);
/*N*/ }

/*************************************************************************
|*
|* Objekt loeschen, ohne Broadcast
|*
\************************************************************************/

//STRIP001 SdrObject* SdPage::NbcRemoveObject(ULONG nObjNum)
//STRIP001 {
//STRIP001  SdrObject* pObj = FmFormPage::NbcRemoveObject(nObjNum);
//STRIP001
//STRIP001  if (pObj && pObj->GetUserCall()!=this &&
//STRIP001      aPresObjList.GetPos(pObj) != LIST_ENTRY_NOTFOUND)
//STRIP001  {
//STRIP001      // Objekt hat keinen UserCall auf diese Seite, es ist jedoch noch in
//STRIP001      // der PresObjList eingetragen -> austragen
//STRIP001      Changed(*pObj, SDRUSERCALL_REMOVED, pObj->GetBoundRect());
//STRIP001  }
//STRIP001
//STRIP001  ((SdDrawDocument*) pModel)->RemoveObject(pObj, this);
//STRIP001
//STRIP001  return(pObj);
//STRIP001 }

/*************************************************************************
|*
|*
|*
\************************************************************************/

// #95876# Also overload ReplaceObject methods to realize when
// objects are removed with this mechanism instead of RemoveObject
//STRIP001 SdrObject* SdPage::NbcReplaceObject(SdrObject* pNewObj, ULONG nObjNum)
//STRIP001 {
//STRIP001  SdrObject* pOldObj = FmFormPage::NbcReplaceObject(pNewObj, nObjNum);
//STRIP001  if(pOldObj && pOldObj->GetUserCall()!=this && aPresObjList.GetPos(pOldObj) != LIST_ENTRY_NOTFOUND)
//STRIP001      Changed(*pOldObj, SDRUSERCALL_REMOVED, pOldObj->GetBoundRect());
//STRIP001  return pOldObj;
//STRIP001 }

// #95876# Also overload ReplaceObject methods to realize when
// objects are removed with this mechanism instead of RemoveObject
//STRIP001 SdrObject* SdPage::ReplaceObject(SdrObject* pNewObj, ULONG nObjNum)
//STRIP001 {
//STRIP001  SdrObject* pOldObj = FmFormPage::ReplaceObject(pNewObj, nObjNum);
//STRIP001  if(pOldObj && pOldObj->GetUserCall()!=this && aPresObjList.GetPos(pOldObj) != LIST_ENTRY_NOTFOUND)
//STRIP001      Changed(*pOldObj, SDRUSERCALL_REMOVED, pOldObj->GetBoundRect());
//STRIP001  return pOldObj;
//STRIP001 }

/*************************************************************************
|*
|*
|*
\************************************************************************/

/*N*/ void SdPage::SetSize(const Size& aSize)
/*N*/ {
/*N*/   Size aOldSize = GetSize();
/*N*/
/*N*/   if (aSize != aOldSize)
/*N*/   {
/*N*/       FmFormPage::SetSize(aSize);
/*N*/       AdjustBackgroundSize();
/*N*/
/*N*/       if (aOldSize.Height() == 10 && aOldSize.Width() == 10)
/*N*/       {
/*N*/           // Die Seite bekommt erstmalig eine gueltige Groesse gesetzt,
/*N*/           // daher wird nun die Orientation initialisiert
/*N*/           if (aSize.Width() > aSize.Height())
/*N*/           {
/*N*/               eOrientation = ORIENTATION_LANDSCAPE;
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               eOrientation = ORIENTATION_PORTRAIT;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }


/*************************************************************************
|*
|*
|*
\************************************************************************/

/*N*/ void SdPage::SetBorder(INT32 nLft, INT32 nUpp, INT32 nRgt, INT32 nLwr)
/*N*/ {
/*N*/   if (nLft != GetLftBorder() || nUpp != GetUppBorder() ||
/*N*/       nRgt != GetRgtBorder() || nLwr != GetLwrBorder() )
/*N*/   {
/*N*/       FmFormPage::SetBorder(nLft, nUpp, nRgt, nLwr);
/*N*/       AdjustBackgroundSize();
/*N*/   }
/*N*/ }


/*************************************************************************
|*
|*
|*
\************************************************************************/

/*N*/ void SdPage::SetLftBorder(INT32 nBorder)
/*N*/ {
/*N*/   if (nBorder != GetLftBorder() )
/*N*/   {
/*N*/       FmFormPage::SetLftBorder(nBorder);
/*N*/       AdjustBackgroundSize();
/*N*/   }
/*N*/ }


/*************************************************************************
|*
|*
|*
\************************************************************************/

/*N*/ void SdPage::SetRgtBorder(INT32 nBorder)
/*N*/ {
/*N*/   if (nBorder != GetRgtBorder() )
/*N*/   {
/*N*/       FmFormPage::SetRgtBorder(nBorder);
/*N*/       AdjustBackgroundSize();
/*N*/   }
/*N*/ }


/*************************************************************************
|*
|*
|*
\************************************************************************/

/*N*/ void SdPage::SetUppBorder(INT32 nBorder)
/*N*/ {
/*N*/   if (nBorder != GetUppBorder() )
/*N*/   {
/*N*/       FmFormPage::SetUppBorder(nBorder);
/*N*/       AdjustBackgroundSize();
/*N*/   }
/*N*/ }


/*************************************************************************
|*
|*
|*
\************************************************************************/

/*N*/ void SdPage::SetLwrBorder(INT32 nBorder)
/*N*/ {
/*N*/   if (nBorder != GetLwrBorder() )
/*N*/   {
/*N*/       FmFormPage::SetLwrBorder(nBorder);
/*N*/       AdjustBackgroundSize();
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* Setzt BackgroundFullSize und ruft dann AdjustBackground auf
|*
\************************************************************************/

/*N*/ void SdPage::SetBackgroundFullSize( BOOL bIn )
/*N*/ {
/*N*/   if( bIn != bBackgroundFullSize )
/*?*/   {
/*?*/       bBackgroundFullSize = bIn;
        AdjustBackgroundSize();
    }
/*N*/ }

/*************************************************************************
|*
|* Alle Objekte an neue Seitengroesse anpassen
|*
|* bScaleAllObj: Alle Objekte werden in die neue Flaeche innerhalb der
|* Seitenraender skaliert. Dabei werden die Position, Groesse und bei
|* Praesentationsobjekten auf der MasterPage auch die Schrifthoehe der
|* Praesentationsvorlagen skaliert.
|*
\************************************************************************/

//STRIP001 void SdPage::ScaleObjects(const Size& rNewPageSize, const Rectangle& rNewBorderRect, BOOL bScaleAllObj)
//STRIP001 {
//STRIP001  bOwnArrangement = TRUE;
//STRIP001  bScaleObjects = bScaleAllObj;
//STRIP001  SdrObject* pObj = NULL;
//STRIP001  Point aRefPnt(0, 0);
//STRIP001  Size aNewPageSize(rNewPageSize);
//STRIP001  INT32 nLeft  = rNewBorderRect.Left();
//STRIP001  INT32 nRight = rNewBorderRect.Right();
//STRIP001  INT32 nUpper = rNewBorderRect.Top();
//STRIP001  INT32 nLower = rNewBorderRect.Bottom();
//STRIP001
//STRIP001  // Negative Werte stehen fuer nicht zu aendernde Werte
//STRIP001  // -> aktuelle Werte verwenden
//STRIP001  if (aNewPageSize.Width() < 0)
//STRIP001  {
//STRIP001      aNewPageSize.Width() = GetWdt();
//STRIP001  }
//STRIP001  if (aNewPageSize.Height() < 0)
//STRIP001  {
//STRIP001      aNewPageSize.Height() = GetHgt();
//STRIP001  }
//STRIP001  if (nLeft < 0)
//STRIP001  {
//STRIP001      nLeft = GetLftBorder();
//STRIP001  }
//STRIP001  if (nRight < 0)
//STRIP001  {
//STRIP001      nRight = GetRgtBorder();
//STRIP001  }
//STRIP001  if (nUpper < 0)
//STRIP001  {
//STRIP001      nUpper = GetUppBorder();
//STRIP001  }
//STRIP001  if (nLower < 0)
//STRIP001  {
//STRIP001      nLower = GetLwrBorder();
//STRIP001  }
//STRIP001
//STRIP001  Point aBackgroundPos(nLeft, nUpper);
//STRIP001  Size aBackgroundSize(aNewPageSize);
//STRIP001  Rectangle aBorderRect (aBackgroundPos, aBackgroundSize);
//STRIP001
//STRIP001  if (bScaleObjects)
//STRIP001  {
//STRIP001      aBackgroundSize.Width()  -= nLeft  + nRight;
//STRIP001      aBackgroundSize.Height() -= nUpper + nLower;
//STRIP001      aBorderRect.SetSize(aBackgroundSize);
//STRIP001      aNewPageSize = aBackgroundSize;
//STRIP001  }
//STRIP001
//STRIP001  long nOldWidth  = GetWdt() - GetLftBorder() - GetRgtBorder();
//STRIP001  long nOldHeight = GetHgt() - GetUppBorder() - GetLwrBorder();
//STRIP001
//STRIP001  Fraction aFractX = Fraction(aNewPageSize.Width(), nOldWidth);
//STRIP001  Fraction aFractY = Fraction(aNewPageSize.Height(), nOldHeight);
//STRIP001
//STRIP001  ULONG nObjCnt = (bScaleObjects ? GetObjCount() : 0);
//STRIP001
//STRIP001  for (ULONG nObj = 0; nObj < nObjCnt; nObj++)
//STRIP001  {
//STRIP001      BOOL bIsPresObjOnMaster = FALSE;
//STRIP001      SfxStyleSheet* pSheet = NULL;
//STRIP001
//STRIP001      if (bScaleObjects)
//STRIP001      {
//STRIP001          // Alle Objekte
//STRIP001          pObj = GetObj(nObj);
//STRIP001
//STRIP001          if (bMaster && aPresObjList.GetPos(pObj) != LIST_ENTRY_NOTFOUND)
//STRIP001          {
//STRIP001              // Es ist ein Praesentationsobjekt auf der MasterPage
//STRIP001              bIsPresObjOnMaster = TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          // Nur Praesentationsobjekte
//STRIP001          pObj = (SdrObject*) aPresObjList.GetObject(nObj);
//STRIP001
//STRIP001          if (bMaster)
//STRIP001          {
//STRIP001              bIsPresObjOnMaster = TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      if (pObj)
//STRIP001      {
//STRIP001          USHORT nIndexBackground = 0;
//STRIP001          // #88084# remember aTopLeft as original TopLeft
//STRIP001          Point aTopLeft(pObj->GetBoundRect().TopLeft());
//STRIP001
//STRIP001          if (bIsPresObjOnMaster &&
//STRIP001              (ePageKind == PK_HANDOUT ||
//STRIP001               pObj == GetPresObj(PRESOBJ_BACKGROUND, nIndexBackground)))
//STRIP001          {
//STRIP001              /**************************************************************
//STRIP001              * 1. Praesentationsobjekte auf Handzettelseite sollen nur positioniert werden
//STRIP001              * 2. Hintergrundobjekt wird nicht skaliert
//STRIP001              **************************************************************/
//STRIP001          }
//STRIP001          else if (!pObj->IsEdgeObj())
//STRIP001          {
//STRIP001              /**************************************************************
//STRIP001              * Objekt skalieren
//STRIP001              **************************************************************/
//STRIP001              if (bScaleObjects)
//STRIP001              {
//STRIP001                  // #88084# use aTopLeft as original TopLeft
//STRIP001                  aRefPnt = aTopLeft;
//STRIP001              }
//STRIP001
//STRIP001              pObj->Resize(aRefPnt, aFractX, aFractY);
//STRIP001
//STRIP001              if (bScaleObjects)
//STRIP001              {
//STRIP001                  SdrObjKind eObjKind = (SdrObjKind) pObj->GetObjIdentifier();
//STRIP001
//STRIP001                  if (bIsPresObjOnMaster)
//STRIP001                  {
//STRIP001                      /**********************************************************
//STRIP001                      * Praesentationsvorlage: Texthoehe anpassen
//STRIP001                      **********************************************************/
//STRIP001                      USHORT nIndexTitle = 0;
//STRIP001                      USHORT nIndexOutline = 0;
//STRIP001                      USHORT nIndexNotes = 0;
//STRIP001
//STRIP001                      if (pObj == GetPresObj(PRESOBJ_TITLE, nIndexTitle))
//STRIP001                      {
//STRIP001                          SfxStyleSheet* pSheet = GetStyleSheetForPresObj(PRESOBJ_TITLE);
//STRIP001
//STRIP001                          if (pSheet)
//STRIP001                          {
//STRIP001                              SfxItemSet& rSet = pSheet->GetItemSet();
//STRIP001
//STRIP001                              SvxFontHeightItem& rOldHgt = (SvxFontHeightItem&) rSet.Get(EE_CHAR_FONTHEIGHT);
//STRIP001                              ULONG nFontHeight = rOldHgt.GetHeight();
//STRIP001                              nFontHeight = long(nFontHeight * (double) aFractY);
//STRIP001                              rSet.Put(SvxFontHeightItem(nFontHeight, 100, EE_CHAR_FONTHEIGHT));
//STRIP001
//STRIP001                              if( SFX_ITEM_AVAILABLE == rSet.GetItemState( EE_CHAR_FONTHEIGHT_CJK ) )
//STRIP001                              {
//STRIP001                                  rOldHgt = (SvxFontHeightItem&) rSet.Get(EE_CHAR_FONTHEIGHT_CJK);
//STRIP001                                  nFontHeight = rOldHgt.GetHeight();
//STRIP001                                  nFontHeight = long(nFontHeight * (double) aFractY);
//STRIP001                                  rSet.Put(SvxFontHeightItem(nFontHeight, 100, EE_CHAR_FONTHEIGHT_CJK));
//STRIP001                              }
//STRIP001
//STRIP001                              if( SFX_ITEM_AVAILABLE == rSet.GetItemState( EE_CHAR_FONTHEIGHT_CTL ) )
//STRIP001                              {
//STRIP001                                  rOldHgt = (SvxFontHeightItem&) rSet.Get(EE_CHAR_FONTHEIGHT_CTL);
//STRIP001                                  nFontHeight = rOldHgt.GetHeight();
//STRIP001                                  nFontHeight = long(nFontHeight * (double) aFractY);
//STRIP001                                  rSet.Put(SvxFontHeightItem(nFontHeight, 100, EE_CHAR_FONTHEIGHT_CTL));
//STRIP001                              }
//STRIP001
//STRIP001                              pSheet->Broadcast(SfxSimpleHint(SFX_HINT_DATACHANGED));
//STRIP001                          }
//STRIP001                      }
//STRIP001                      else if (pObj == GetPresObj(PRESOBJ_OUTLINE, nIndexOutline))
//STRIP001                      {
//STRIP001                          ULONG nHeight = pObj->GetLogicRect().GetSize().Height() / 9;
//STRIP001                          String aName(GetLayoutName());
//STRIP001                          aName += sal_Unicode( ' ' );
//STRIP001
//STRIP001                          for (USHORT i=1; i<=9; i++)
//STRIP001                          {
//STRIP001                              String aLayoutName(aName);
//STRIP001                              aLayoutName += String::CreateFromInt32( (sal_Int32)i );
//STRIP001                              SfxStyleSheet* pSheet = (SfxStyleSheet*)
//STRIP001                              ((SdDrawDocument*) pModel)->GetStyleSheetPool()->
//STRIP001                              Find(aLayoutName, SD_LT_FAMILY);
//STRIP001
//STRIP001                              if (pSheet)
//STRIP001                              {
//STRIP001                                  // Neue Fonthoehe berechnen
//STRIP001                                  SfxItemSet aTempSet(pSheet->GetItemSet());
//STRIP001
//STRIP001                                  SvxFontHeightItem& rOldHgt = (SvxFontHeightItem&) aTempSet.Get(EE_CHAR_FONTHEIGHT);
//STRIP001                                  ULONG nFontHeight = rOldHgt.GetHeight();
//STRIP001                                  nFontHeight = long(nFontHeight * (double) aFractY);
//STRIP001                                  aTempSet.Put(SvxFontHeightItem(nFontHeight, 100, EE_CHAR_FONTHEIGHT));
//STRIP001
//STRIP001                                  if( SFX_ITEM_AVAILABLE == aTempSet.GetItemState( EE_CHAR_FONTHEIGHT_CJK ) )
//STRIP001                                  {
//STRIP001                                      rOldHgt = (SvxFontHeightItem&) aTempSet.Get(EE_CHAR_FONTHEIGHT_CJK);
//STRIP001                                      nFontHeight = rOldHgt.GetHeight();
//STRIP001                                      nFontHeight = long(nFontHeight * (double) aFractY);
//STRIP001                                      aTempSet.Put(SvxFontHeightItem(nFontHeight, 100, EE_CHAR_FONTHEIGHT_CJK));
//STRIP001                                  }
//STRIP001
//STRIP001                                  if( SFX_ITEM_AVAILABLE == aTempSet.GetItemState( EE_CHAR_FONTHEIGHT_CTL ) )
//STRIP001                                  {
//STRIP001                                      rOldHgt = (SvxFontHeightItem&) aTempSet.Get(EE_CHAR_FONTHEIGHT_CTL);
//STRIP001                                      nFontHeight = rOldHgt.GetHeight();
//STRIP001                                      nFontHeight = long(nFontHeight * (double) aFractY);
//STRIP001                                      aTempSet.Put(SvxFontHeightItem(nFontHeight, 100, EE_CHAR_FONTHEIGHT_CTL));
//STRIP001                                  }
//STRIP001
//STRIP001                                  // Bullet anpassen
//STRIP001                                  ((SdStyleSheet*) pSheet)->AdjustToFontHeight(aTempSet, FALSE);
//STRIP001
//STRIP001                                  // Sonderbehandlung: die INVALIDS auf NULL-Pointer
//STRIP001                                  // zurueckgesetzen (sonst landen INVALIDs oder
//STRIP001                                  // Pointer auf die DefaultItems in der Vorlage;
//STRIP001                                  // beides wuerde die Attribut-Vererbung unterbinden)
//STRIP001                                  aTempSet.ClearInvalidItems();
//STRIP001
//STRIP001                                  // Sonderbehandlung: nur die gueltigen Anteile des
//STRIP001                                  // BulletItems
//STRIP001                                  if (aTempSet.GetItemState(EE_PARA_BULLET) == SFX_ITEM_AVAILABLE)
//STRIP001                                  {
//STRIP001                                      SvxBulletItem aOldBulItem((SvxBulletItem&) pSheet->GetItemSet().Get(EE_PARA_BULLET));
//STRIP001                                      SvxBulletItem& rNewBulItem = (SvxBulletItem&) aTempSet.Get(EE_PARA_BULLET);
//STRIP001                                      aOldBulItem.CopyValidProperties(rNewBulItem);
//STRIP001                                      aTempSet.Put(aOldBulItem);
//STRIP001                                  }
//STRIP001
//STRIP001                                  pSheet->GetItemSet().Put(aTempSet);
//STRIP001
//STRIP001                                  pSheet->Broadcast(SfxSimpleHint(SFX_HINT_DATACHANGED));
//STRIP001                              }
//STRIP001                          }
//STRIP001                      }
//STRIP001                      else if (pObj == GetPresObj(PRESOBJ_NOTES, nIndexNotes))
//STRIP001                      {
//STRIP001                          SfxStyleSheet* pSheet = GetStyleSheetForPresObj(PRESOBJ_NOTES);
//STRIP001
//STRIP001                          if (pSheet)
//STRIP001                          {
//STRIP001                              ULONG nHeight = pObj->GetLogicRect().GetSize().Height();
//STRIP001                              ULONG nFontHeight = (ULONG) (nHeight * 0.0741);
//STRIP001                              SfxItemSet& rSet = pSheet->GetItemSet();
//STRIP001                              rSet.Put( SvxFontHeightItem(nFontHeight, EE_CHAR_FONTHEIGHT ));
//STRIP001                              rSet.Put( SvxFontHeightItem(nFontHeight, EE_CHAR_FONTHEIGHT_CJK ));
//STRIP001                              rSet.Put( SvxFontHeightItem(nFontHeight, EE_CHAR_FONTHEIGHT_CTL ));
//STRIP001                              pSheet->Broadcast(SfxSimpleHint(SFX_HINT_DATACHANGED));
//STRIP001                          }
//STRIP001                      }
//STRIP001                  }
//STRIP001                  else if ( eObjKind != OBJ_TITLETEXT   &&
//STRIP001                            eObjKind != OBJ_OUTLINETEXT &&
//STRIP001                            pObj->ISA(SdrTextObj)       &&
//STRIP001                            pObj->GetOutlinerParaObject() )
//STRIP001                  {
//STRIP001                      /******************************************************
//STRIP001                      * Normales Textobjekt: Texthoehe anpassen
//STRIP001                      ******************************************************/
//STRIP001                      ULONG nScriptType = pObj->GetOutlinerParaObject()->GetTextObject().GetScriptType();
//STRIP001                      USHORT nWhich = EE_CHAR_FONTHEIGHT;
//STRIP001                      if ( nScriptType == SCRIPTTYPE_ASIAN )
//STRIP001                          nWhich = EE_CHAR_FONTHEIGHT_CJK;
//STRIP001                      else if ( nScriptType == SCRIPTTYPE_COMPLEX )
//STRIP001                          nWhich = EE_CHAR_FONTHEIGHT_CTL;
//STRIP001
//STRIP001                      // #88084# use more modern method to scale the text height
//STRIP001                      sal_uInt32 nFontHeight = ((SvxFontHeightItem&)pObj->GetItem(nWhich)).GetHeight();
//STRIP001                      sal_uInt32 nNewFontHeight = sal_uInt32((double)nFontHeight * (double)aFractY);
//STRIP001                      pObj->SetItem(SvxFontHeightItem(nNewFontHeight, 100, nWhich));
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          if (bScaleObjects && !pObj->IsEdgeObj())
//STRIP001          {
//STRIP001              /**************************************************************
//STRIP001              * Objektposition skalieren
//STRIP001              **************************************************************/
//STRIP001              Point aNewPos;
//STRIP001
//STRIP001              // #76447# corrected scaling; only distances may be scaled
//STRIP001              // #88084# use aTopLeft as original TopLeft
//STRIP001              aNewPos.X() = long((aTopLeft.X() - GetLftBorder()) * (double)aFractX) + nLeft;
//STRIP001              aNewPos.Y() = long((aTopLeft.Y() - GetUppBorder()) * (double)aFractY) + nUpper;
//STRIP001
//STRIP001              Size aVec(aNewPos.X() - aTopLeft.X(), aNewPos.Y() - aTopLeft.Y());
//STRIP001
//STRIP001              if (aVec.Height() != 0 || aVec.Width() != 0)
//STRIP001              {
//STRIP001                  pObj->NbcMove(aVec);
//STRIP001              }
//STRIP001
//STRIP001              Rectangle aBoundRect = pObj->GetBoundRect();
//STRIP001
//STRIP001              if (!aBorderRect.IsInside(aBoundRect))
//STRIP001              {
//STRIP001                  /**********************************************************
//STRIP001                  * Objekt liegt nicht vollstaendig innerhalb der Raender
//STRIP001                  * -> Position korrigieren
//STRIP001                  **********************************************************/
//STRIP001                  Point aOldPos(aBoundRect.TopLeft());
//STRIP001                  Point aNewPos(aOldPos);
//STRIP001
//STRIP001                  // Position links oben ggf. korrigieren
//STRIP001                  aNewPos.X() = Max(aNewPos.X(), aBorderRect.Left());
//STRIP001                  aNewPos.Y() = Max(aNewPos.Y(), aBorderRect.Top());
//STRIP001                  Size aVec(aNewPos.X() - aOldPos.X(), aNewPos.Y() - aOldPos.Y());
//STRIP001
//STRIP001                  if (aVec.Height() != 0 || aVec.Width() != 0)
//STRIP001                  {
//STRIP001                      pObj->NbcMove(aVec);
//STRIP001                  }
//STRIP001
//STRIP001                  // Position rechts unten ggf. korrigieren
//STRIP001                  aOldPos = aBoundRect.BottomRight();
//STRIP001                  aNewPos = aOldPos;
//STRIP001                  aNewPos.X() = Min(aNewPos.X(), aBorderRect.Right());
//STRIP001                  aNewPos.Y() = Min(aNewPos.Y(), aBorderRect.Bottom());
//STRIP001                  aVec = Size(aNewPos.X() - aOldPos.X(), aNewPos.Y() - aOldPos.Y());
//STRIP001
//STRIP001                  if (aVec.Height() != 0 || aVec.Width() != 0)
//STRIP001                  {
//STRIP001                      pObj->NbcMove(aVec);
//STRIP001                  }
//STRIP001              }
//STRIP001
//STRIP001              pObj->SendRepaintBroadcast();
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  bOwnArrangement = FALSE;
//STRIP001 }

/*************************************************************************
|*
|*
|*
\************************************************************************/

/*N*/ BOOL SdPage::InsertPresObj(SdrObject* pObj, PresObjKind eObjKind, BOOL bVertical,
/*N*/                           Rectangle aRect, BOOL bInit, List& rObjList)
/*N*/ {
/*N*/   BOOL bIncrement = FALSE;
/*N*/
/*N*/   if (!pObj && bInit)
/*N*/   {
/*N*/       pObj = CreatePresObj(eObjKind, bVertical, aRect);
/*N*/   }
/*N*/   else if ( pObj && (pObj->GetUserCall() || bInit) )
/*N*/   {
/*N*/       if ( pObj->ISA(SdrGrafObj) && !pObj->IsEmptyPresObj() )
/*N*/           ( (SdrGrafObj*) pObj)->AdjustToMaxRect( aRect, FALSE );
/*N*/       else
/*N*/           pObj->SetLogicRect(aRect);
/*N*/
/*N*/       pObj->SetUserCall(this);
/*N*/
/*N*/       if ( pObj->ISA(SdrTextObj) )
/*N*/       {
/*N*/           if( ((SdrTextObj*) pObj)->IsVerticalWriting() != bVertical )
/*N*/           {
/*N*/               ((SdrTextObj*) pObj)->SetVerticalWriting( bVertical );
/*N*/
/*N*/               // #94826# here make sure the correct anchoring is used when the object
/*N*/               // is re-used but orientation is changed
/*N*/               if(PRESOBJ_OUTLINE == eObjKind)
/*N*/               {
/*N*/                   if(bVertical)
/*N*/                   {
/*N*/                       // vertical activated on once horizontal outline object
/*N*/                       ((SdrTextObj*) pObj)->SetItem(SdrTextHorzAdjustItem(SDRTEXTHORZADJUST_RIGHT));
/*N*/                   }
/*N*/                   else
/*N*/                   {
/*N*/                       // horizontal activated on once vertical outline object
/*N*/                       ((SdrTextObj*) pObj)->SetItem(SdrTextHorzAdjustItem(SDRTEXTHORZADJUST_BLOCK));
/*N*/                   }
/*N*/               }
/*N*/           }
/*N*/
/*N*/           if( !bMaster )
/*N*/           {
/*N*/               if ( ((SdrTextObj*) pObj)->IsAutoGrowHeight() )
/*N*/               {
/*N*/                   // switch off AutoGrowHeight, set new MinHeight
/*N*/                   SfxItemSet aTempAttr( ((SdDrawDocument*) pModel)->GetPool() );
/*N*/                   SdrTextMinFrameHeightItem aMinHeight( aRect.GetSize().Height() );
/*N*/                   aTempAttr.Put( aMinHeight );
/*N*/                   aTempAttr.Put( SdrTextAutoGrowHeightItem(FALSE) );
/*N*/                   pObj->SetItemSet(aTempAttr);
/*N*/                   pObj->SetLogicRect(aRect);
/*N*/
/*N*/                   // switch on AutoGrowHeight
/*N*/                   SfxItemSet aAttr( ((SdDrawDocument*) pModel)->GetPool() );
/*N*/                   aAttr.Put( SdrTextAutoGrowHeightItem(TRUE) );
/*N*/
/*N*/                   pObj->SetItemSet(aAttr);
/*N*/               }
/*N*/
/*N*/               if ( ((SdrTextObj*) pObj)->IsAutoGrowWidth() )
/*N*/               {
/*N*/                   // switch off AutoGrowWidth , set new MinWidth
/*N*/                   SfxItemSet aTempAttr( ((SdDrawDocument*) pModel)->GetPool() );
/*N*/                   SdrTextMinFrameWidthItem aMinWidth( aRect.GetSize().Width() );
/*N*/                   aTempAttr.Put( aMinWidth );
/*N*/                   aTempAttr.Put( SdrTextAutoGrowWidthItem(FALSE) );
/*N*/                   pObj->SetItemSet(aTempAttr);
/*N*/                   pObj->SetLogicRect(aRect);
/*N*/
/*N*/                   // switch on AutoGrowWidth
/*N*/                   SfxItemSet aAttr( ((SdDrawDocument*) pModel)->GetPool() );
/*N*/                   aAttr.Put( SdrTextAutoGrowWidthItem(TRUE) );
/*N*/                   pObj->SetItemSet(aAttr);
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if (pObj)
/*N*/   {
/*N*/       bIncrement = TRUE;
/*N*/       rObjList.Insert(pObj, LIST_APPEND);
/*N*/
/*N*/       if (eObjKind == PRESOBJ_OUTLINE && pObj->IsEmptyPresObj())
/*N*/       {
/*N*/           // Gibt es ev. noch ein Untertitel?
/*N*/           SdrObject* pSubtitle = GetPresObj(PRESOBJ_TEXT);
/*N*/
/*N*/           if (pSubtitle)
/*N*/           {
/*?*/               // Text des Untertitels in das PRESOBJ_OUTLINE setzen
/*?*/               OutlinerParaObject* pOutlParaObj = pSubtitle->GetOutlinerParaObject();
/*?*/
/*?*/               if (pOutlParaObj)
/*?*/               {
/*?*/                   if (!pSubtitle->IsEmptyPresObj())
/*?*/                   {
/*?*/                       // Text umsetzen
/*?*/                       SdOutliner* pOutl = ( (SdDrawDocument*) pModel )->GetInternalOutliner( TRUE );
/*?*/                       pOutl->Clear();
/*?*/                       pOutl->SetText( *pOutlParaObj );
/*?*/                       pOutl->SetMinDepth(1, TRUE);
/*?*/                       pOutlParaObj = pOutl->CreateParaObject();
/*?*/                       pObj->SetOutlinerParaObject( pOutlParaObj );
/*?*/                       pOutl->Clear();
/*?*/                       pObj->SetEmptyPresObj(FALSE);
/*?*/                   }
/*?*/
/*?*/                   for (USHORT nLevel = 1; nLevel < 10; nLevel++)
/*?*/                   {
/*?*/                       // Neue Vorlage zuweisen
/*?*/                       String aName(aLayoutName);
/*?*/                       aName += sal_Unicode( ' ' );
/*?*/                       aName += String::CreateFromInt32( nLevel );
/*?*/                       SfxStyleSheet* pSheet = (SfxStyleSheet*) pModel->GetStyleSheetPool()->Find(aName, SD_LT_FAMILY);
/*?*/
/*?*/                       if (pSheet)
/*?*/                       {
/*?*/                           if (nLevel == 1)
/*?*/                           {
/*?*/                               SfxStyleSheet* pSubtitleSheet = GetStyleSheetForPresObj(PRESOBJ_TEXT);
/*?*/
/*?*/                               if (pSubtitleSheet)
/*?*/                                   pOutlParaObj->ChangeStyleSheetName(SD_LT_FAMILY, pSubtitleSheet->GetName(),
/*?*/                                                                                    pSheet->GetName());
/*?*/                           }
/*?*/
/*?*/                           pObj->StartListening(*pSheet);
/*?*/                       }
/*?*/                   }
/*?*/
/*?*/                   // LRSpace-Item loeschen
/*?*/                   SfxItemSet aSet(((SdDrawDocument*) pModel)->GetPool(), EE_PARA_LRSPACE, EE_PARA_LRSPACE );
/*?*/
/*?*/                   aSet.Put(pObj->GetItemSet());
/*?*/
/*?*/                   aSet.ClearItem(EE_PARA_LRSPACE);
/*?*/
/*?*/                   pObj->SetItemSet(aSet);
/*?*/
/*?*/                   // Untertitel loeschen
/*?*/                   aPresObjList.Remove(pSubtitle);
/*?*/                   RemoveObject( pObj->GetOrdNum() );
/*?*/                   ReplaceObject( pObj, pSubtitle->GetOrdNum() );
/*?*/                   ( (SdDrawDocument*) pModel)->RemoveObject( pSubtitle, this );
/*?*/                   delete pSubtitle;
/*?*/               }
/*N*/           }
/*N*/       }
/*N*/       else if (eObjKind == PRESOBJ_TEXT && pObj->IsEmptyPresObj())
/*N*/       {
/*N*/           // Gibt es ev. noch ein Gliederungsobjekt?
/*N*/           SdrObject* pOutlineObj = GetPresObj(PRESOBJ_OUTLINE);
/*N*/
/*N*/           if (pOutlineObj)
/*N*/           {
/*?*/               // Text des Gliederungsobjekts in das PRESOBJ_TITLE setzen
/*?*/               OutlinerParaObject* pOutlParaObj = pOutlineObj->GetOutlinerParaObject();
/*?*/
/*?*/               if (pOutlParaObj)
/*?*/               {
/*?*/                   if (!pOutlineObj->IsEmptyPresObj())
/*?*/                   {
/*?*/                       // Text umsetzen
/*?*/                       SdOutliner* pOutl = ( (SdDrawDocument*) pModel )->GetInternalOutliner();
/*?*/                       pOutl->Clear();
/*?*/                       pOutl->SetText( *pOutlParaObj );
/*?*/                       pOutl->SetMinDepth(0, TRUE);
/*?*/                       pOutlParaObj = pOutl->CreateParaObject();
/*?*/                       pObj->SetOutlinerParaObject( pOutlParaObj );
/*?*/                       pOutl->Clear();
/*?*/                       pObj->SetEmptyPresObj(FALSE);
/*?*/                   }
/*?*/
/*?*/                   // Linken Einzug zuruecksetzen
/*?*/                   SfxItemSet aSet(((SdDrawDocument*) pModel)->GetPool(), EE_PARA_LRSPACE, EE_PARA_LRSPACE );
/*?*/
/*?*/                   aSet.Put(pObj->GetItemSet());
/*?*/
/*?*/                   const SvxLRSpaceItem& rLRItem = (const SvxLRSpaceItem&) aSet.Get(EE_PARA_LRSPACE);
/*?*/                   SvxLRSpaceItem aNewLRItem(rLRItem);
/*?*/                   aNewLRItem.SetTxtLeft(0);
/*?*/                   aSet.Put(aNewLRItem);
/*?*/
/*?*/                   pObj->SetItemSet(aSet);
/*?*/
/*?*/                   SfxStyleSheet* pSheet = GetStyleSheetForPresObj(PRESOBJ_TEXT);
/*?*/
/*?*/                   if (pSheet)
/*?*/                       pObj->SetStyleSheet(pSheet, TRUE);
/*?*/
/*?*/                   // Gliederungsobjekt loeschen
/*?*/                   aPresObjList.Remove(pOutlineObj);
/*?*/                   RemoveObject( pObj->GetOrdNum() );
/*?*/                   ReplaceObject( pObj, pOutlineObj->GetOrdNum() );
/*?*/                   ( (SdDrawDocument*) pModel)->RemoveObject( pOutlineObj, this );
/*?*/                   delete pOutlineObj;
/*?*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return(bIncrement);
/*N*/ }


/*************************************************************************
|*
|* Liefert den PresObjKind eines Objektes zurueck
|*
\************************************************************************/

/*N*/ PresObjKind SdPage::GetPresObjKind(SdrObject* pObj)
/*N*/ {
/*N*/   PresObjKind eObjKind = PRESOBJ_NONE;
/*N*/
/*N*/   if (pObj && aPresObjList.GetPos(pObj) != LIST_ENTRY_NOTFOUND &&
/*N*/       pObj->GetObjInventor() == SdrInventor)
/*N*/   {
/*N*/
/*N*/       SdrObjKind eSdrObjKind = (SdrObjKind) pObj->GetObjIdentifier();
/*N*/
/*N*/       if (eSdrObjKind==OBJ_TITLETEXT)
/*N*/       {
/*N*/           eObjKind = PRESOBJ_TITLE;
/*N*/       }
/*N*/       else if (eSdrObjKind==OBJ_OUTLINETEXT)
/*N*/       {
/*N*/           eObjKind = PRESOBJ_OUTLINE;
/*N*/       }
/*N*/       else if (eSdrObjKind==OBJ_TEXT && ePageKind==PK_NOTES)
/*N*/       {
/*N*/           eObjKind = PRESOBJ_NOTES;
/*N*/       }
/*N*/       else if (eSdrObjKind==OBJ_TEXT && ePageKind!=PK_NOTES)
/*N*/       {
/*N*/           eObjKind = PRESOBJ_TEXT;
/*N*/       }
/*N*/       else if (eSdrObjKind==OBJ_GRAF)
/*N*/       {
/*N*/           eObjKind = PRESOBJ_GRAPHIC;
/*N*/       }
/*N*/       else if (eSdrObjKind==OBJ_RECT)
/*N*/       {
/*N*/           eObjKind = PRESOBJ_BACKGROUND;
/*N*/       }
/*N*/       else if (eSdrObjKind==OBJ_PAGE && ePageKind==PK_HANDOUT)
/*N*/       {
/*N*/           eObjKind = PRESOBJ_HANDOUT;
/*N*/       }
/*N*/       else if (eSdrObjKind==OBJ_PAGE && ePageKind!=PK_HANDOUT)
/*N*/       {
/*N*/           eObjKind = PRESOBJ_PAGE;
/*N*/       }
/*N*/       else if (eSdrObjKind==OBJ_OLE2)
/*N*/       {
/*N*/           String aName = ( (SdrOle2Obj*) pObj)->GetProgName();
/*N*/
/*N*/           if (aName.EqualsAscii( "StarChart" ))
/*N*/           {
/*N*/               eObjKind = PRESOBJ_CHART;
/*N*/           }
/*N*/           else if (aName.EqualsAscii( "StarOrg" ))
/*N*/           {
/*N*/               eObjKind = PRESOBJ_ORGCHART;
/*N*/           }
/*N*/           else if (aName.EqualsAscii( "StarCalc" ))
/*N*/           {
/*N*/               eObjKind = PRESOBJ_TABLE;
/*N*/           }
/*N*/ #ifdef STARIMAGE_AVAILABLE
/*N*/           else if (aName.EqualsAscii( "StarImage" ))
/*N*/           {
/*N*/               eObjKind = PRESOBJ_IMAGE;
/*N*/           }
/*N*/ #endif
/*N*/           else
/*N*/           {
/*N*/               eObjKind = PRESOBJ_OBJECT;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return(eObjKind);
/*N*/ }

/*************************************************************************
|*
|* BASIC anfordern
|*
\************************************************************************/

//STRIP001 void SdPage::RequestBasic()
//STRIP001 {
//STRIP001  SdDrawDocShell* pDocShell = ( (SdDrawDocument*) GetModel() )->GetDocSh();
//STRIP001
//STRIP001  if (pDocShell)
//STRIP001  {
//STRIP001      SetBasic( pDocShell->GetBasicManager()->GetLib(0) );
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|* Text des Objektes setzen
|*
\************************************************************************/

/*N*/ void SdPage::SetObjText(SdrTextObj* pObj, SdrOutliner* pOutliner,
/*N*/                       PresObjKind eObjKind,
/*N*/                       const String& rString )
/*N*/ {
/*N*/   if ( pObj )
/*N*/   {
/*N*/       DBG_ASSERT( pObj->ISA(SdrTextObj), "SetObjText: Kein SdrTextObj!" );
/*N*/       Outliner* pOutl = pOutliner;
/*N*/
/*N*/       if (!pOutliner)
/*N*/       {
/*?*/           SfxItemPool* pPool = ((SdDrawDocument*) GetModel())->GetDrawOutliner().GetEmptyItemSet().GetPool();
/*?*/           pOutl = new Outliner( pPool, OUTLINERMODE_OUTLINEOBJECT );
/*?*/           pOutl->SetRefDevice( SD_MOD()->GetRefDevice( *( (SdDrawDocument*) GetModel() )->GetDocSh() ) );
/*?*/           pOutl->SetEditTextObjectPool(pPool);
/*?*/           pOutl->SetStyleSheetPool((SfxStyleSheetPool*)GetModel()->GetStyleSheetPool());
/*?*/           pOutl->SetMinDepth(0);
/*?*/           pOutl->EnableUndo(FALSE);
/*?*/           pOutl->SetUpdateMode( FALSE );
/*N*/       }
/*N*/
/*N*/       USHORT nOutlMode = pOutl->GetMode();
/*N*/       USHORT nMinDepth = pOutl->GetMinDepth();
/*N*/       Size aPaperSize = pOutl->GetPaperSize();
/*N*/       BOOL bUpdateMode = pOutl->GetUpdateMode();
/*N*/       pOutl->SetUpdateMode(FALSE);
/*N*/       pOutl->SetParaAttribs( 0, pOutl->GetEmptyItemSet() );

        // #95114# Always set the object's StyleSheet at the Outliner to
        // use the current objects StyleSheet. Thus it's the same as in
        // SetText(...).
        // #95114# Moved this implementation from where SetObjText(...) was called
        // to inside this method to work even when outliner is fetched here.
/*N*/       pOutl->SetStyleSheet(0, pObj->GetStyleSheet());
/*N*/
/*N*/       String aString;
/*N*/
/*N*/       if (eObjKind == PRESOBJ_OUTLINE)
/*N*/       {
/*N*/           pOutl->Init( OUTLINERMODE_OUTLINEOBJECT );
/*N*/           pOutl->SetMinDepth(1);
/*N*/
/*N*/           aString += sal_Unicode( '\t' );
/*N*/           aString += rString;
/*N*/
/*N*/           if (bMaster)
/*N*/           {
/*N*/               pOutl->SetStyleSheet( 0, GetStyleSheetForPresObj(eObjKind) );
/*N*/               aString += String::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM( "\n\t\t" ));
/*N*/               aString += String ( SdResId( STR_PRESOBJ_MPOUTLLAYER2 ) );
/*N*/
/*N*/               aString += String::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM( "\n\t\t\t" ));
/*N*/               aString += String ( SdResId( STR_PRESOBJ_MPOUTLLAYER3 ) );
/*N*/
/*N*/               aString += String::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM( "\n\t\t\t\t" ));
/*N*/               aString += String ( SdResId( STR_PRESOBJ_MPOUTLLAYER4 ) );
/*N*/
/*N*/               aString += String::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM( "\n\t\t\t\t\t" ));
/*N*/               aString += String ( SdResId( STR_PRESOBJ_MPOUTLLAYER5 ) );
/*N*/
/*N*/               aString += String::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM( "\n\t\t\t\t\t\t" ));
/*N*/               aString += String ( SdResId( STR_PRESOBJ_MPOUTLLAYER6 ) );
/*N*/
/*N*/               aString += String::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM( "\n\t\t\t\t\t\t\t" ));
/*N*/               aString += String ( SdResId( STR_PRESOBJ_MPOUTLLAYER7 ) );
/*N*/
/*N*/               aString += String::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM( "\n\t\t\t\t\t\t\t\t" ));
/*N*/               aString += String ( SdResId( STR_PRESOBJ_MPOUTLLAYER8 ) );
/*N*/
/*N*/               aString += String::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM( "\n\t\t\t\t\t\t\t\t\t" ));
/*N*/               aString += String ( SdResId( STR_PRESOBJ_MPOUTLLAYER9 ) );
/*N*/           }
/*N*/       }
/*N*/       else if (eObjKind == PRESOBJ_TITLE)
/*N*/       {
/*N*/           pOutl->Init( OUTLINERMODE_TITLEOBJECT );
/*N*/           pOutl->SetMinDepth(0);
/*N*/           aString += rString;
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           pOutl->Init( OUTLINERMODE_TEXTOBJECT );
/*N*/           pOutl->SetMinDepth(0);
/*N*/           aString += rString;
/*N*/       }
/*N*/
/*N*/       pOutl->SetPaperSize( pObj->GetLogicRect().GetSize() );
/*N*/
/*N*/       pOutl->SetText( aString, pOutl->GetParagraph( 0 ) );
/*N*/
/*N*/       // MT: Wird nicht gebraucht...
/*N*/       // pOutl->SetUpdateMode(TRUE);
/*N*/
/*N*/       ( (SdrTextObj*) pObj)->SetOutlinerParaObject( pOutl->CreateParaObject() );
/*N*/
/*N*/       if (!pOutliner)
/*?*/       {
/*?*/           delete pOutl;
/*?*/           pOutl = NULL;
/*?*/       }
/*N*/       else
/*N*/       {
/*N*/           // Outliner restaurieren
/*N*/           pOutl->Init( nOutlMode );
/*N*/           pOutl->SetParaAttribs( 0, pOutl->GetEmptyItemSet() );
/*N*/           pOutl->SetUpdateMode( bUpdateMode );
/*N*/           pOutl->SetMinDepth( nMinDepth );
/*N*/           pOutl->SetPaperSize( aPaperSize );
/*N*/       }
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* Link & Daten von einem VControl empfangen
|*
\************************************************************************/

//STRIP001 void SdPage::SetLinkData(const String& rLinkName, const String& rLinkData)
//STRIP001 {
//STRIP001 }

/*************************************************************************
|*
|* Layoutname setzen
|*
\************************************************************************/
/*N*/ void SdPage::SetLayoutName(String aName)
/*N*/ {
/*N*/   aLayoutName = aName;
/*N*/
/*N*/   if( bMaster )
/*N*/   {
/*N*/       String aSep( RTL_CONSTASCII_USTRINGPARAM(SD_LT_SEPARATOR) );
/*N*/       USHORT nPos = aLayoutName.Search( aSep );
/*N*/       if ( nPos != STRING_NOTFOUND )
/*N*/       {
/*N*/           aPageName = aLayoutName;
/*N*/           aPageName.Erase( nPos );
/*N*/       }
/*N*/   }
/*N*/ }


/*************************************************************************
|*
|* Seitenname zurueckgeben und ggf. generieren
|*
\************************************************************************/

/*N*/ const String& SdPage::GetName()
/*N*/ {
/*N*/   if (aPageName.Len() == 0)
/*N*/   {
/*N*/       if ((ePageKind == PK_STANDARD || ePageKind == PK_NOTES) &&
/*N*/           !bMaster)
/*N*/       {
            /**********************************************************************
            * Defaultname fuer Handzettelseiten
            **********************************************************************/
/*N*/           // Seitennummer per Methode holen, denn die Drawing Engine laesst
/*N*/           // die Nummern bis zur naechsten Anforderung unsortiert
/*N*/           USHORT  nNum = (GetPageNum() + 1) / 2;
/*N*/           BOOL    bUpper = FALSE;
/*N*/
/*N*/           aCreatedPageName = String(SdResId(STR_PAGE));
/*N*/           aCreatedPageName += sal_Unicode( ' ' );
/*N*/           aCreatedPageName += ((SdDrawDocument*) GetModel())->CreatePageNumValue(nNum);
/*N*/       }
/*N*/       else
/*N*/       {
             /******************************************************************
             * Defaultname fuer Handzettelseiten
             ******************************************************************/
/*N*/           aCreatedPageName = String(SdResId(STR_LAYOUT_DEFAULT_NAME));
/*N*/       }
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       aCreatedPageName = aPageName;
/*N*/   }
/*N*/
/*N*/   if (ePageKind == PK_NOTES)
/*N*/   {
/*N*/       aCreatedPageName += sal_Unicode( ' ' );
/*N*/       aCreatedPageName += String(SdResId(STR_NOTES));
/*N*/   }
/*N*/   else if (ePageKind == PK_HANDOUT && bMaster)
/*N*/   {
/*N*/       aCreatedPageName += String::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM( " (" ));
/*N*/       aCreatedPageName += String(SdResId(STR_HANDOUT));
/*N*/       aCreatedPageName += sal_Unicode( ')' );
/*N*/   }
/*N*/
/*N*/   return aCreatedPageName;
/*N*/ }


/*************************************************************************
|*
|*
|*
\************************************************************************/

/*N*/ void SdPage::AdjustBackgroundSize()
/*N*/ {
/*N*/   SdrObject* pObj = GetPresObj(PRESOBJ_BACKGROUND);

/*N*/   if (pObj)
/*N*/   {
/*N*/       // Hintergrund-Objekt verschieben
/*N*/       pObj->SetMoveProtect(FALSE);
/*N*/       pObj->SetResizeProtect(FALSE);
/*N*/       bOwnArrangement = TRUE;
/*N*/
/*N*/       Point aBackgroundPos;
/*N*/       Size aBackgroundSize( GetSize() );
/*N*/
/*N*/       if( !bBackgroundFullSize )
/*N*/       {
/*N*/           aBackgroundPos = Point( GetLftBorder(), GetUppBorder() );
/*N*/           aBackgroundSize.Width()  -= GetLftBorder() + GetRgtBorder() - 1;
/*N*/           aBackgroundSize.Height() -= GetUppBorder() + GetLwrBorder() - 1;
/*N*/       }
/*N*/       Rectangle aBackgroundRect (aBackgroundPos, aBackgroundSize);
/*N*/       pObj->SetLogicRect(aBackgroundRect);
/*N*/       bOwnArrangement = FALSE;
/*N*/       pObj->SetMoveProtect(TRUE);
/*N*/       pObj->SetResizeProtect(TRUE);
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|*
|*
\************************************************************************/

/*N*/ void SdPage::SetOrientation( Orientation eOrient)
/*N*/ {
/*N*/   eOrientation = eOrient;
/*N*/ }

/*************************************************************************
|*
|*
|*
\************************************************************************/

/*N*/ Orientation SdPage::GetOrientation() const
/*N*/ {
/*N*/   return eOrientation;
/*N*/ }

/*************************************************************************
|*
|* Liefert den Default-Text eines PresObjektes zurueck
|*
\************************************************************************/

/*N*/ String SdPage::GetPresObjText(PresObjKind eObjKind)
/*N*/ {
/*N*/   String aString;
/*N*/
/*N*/   if (eObjKind == PRESOBJ_TITLE)
/*N*/   {
/*N*/       if (bMaster)
/*N*/       {
/*N*/           if (ePageKind != PK_NOTES)
/*N*/           {
/*N*/               aString = String ( SdResId( STR_PRESOBJ_MPTITLE ) );
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               aString = String ( SdResId( STR_PRESOBJ_MPNOTESTITLE ) );
/*N*/           }
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           aString = String ( SdResId( STR_PRESOBJ_TITLE ) );
/*N*/       }
/*N*/   }
/*N*/   else if (eObjKind == PRESOBJ_OUTLINE)
/*N*/   {
/*N*/       if (bMaster)
/*N*/       {
/*N*/           aString = String ( SdResId( STR_PRESOBJ_MPOUTLINE ) );
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           aString = String ( SdResId( STR_PRESOBJ_OUTLINE ) );
/*N*/       }
/*N*/   }
/*N*/   else if (eObjKind == PRESOBJ_NOTES)
/*N*/   {
/*N*/       if (bMaster)
/*N*/       {
/*N*/           aString = String ( SdResId( STR_PRESOBJ_MPNOTESTEXT ) );
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           aString = String ( SdResId( STR_PRESOBJ_NOTESTEXT ) );
/*N*/       }
/*N*/   }
/*N*/   else if (eObjKind == PRESOBJ_TEXT)
/*N*/   {
/*N*/       aString = String ( SdResId( STR_PRESOBJ_TEXT ) );
/*N*/   }
/*N*/   else if (eObjKind == PRESOBJ_GRAPHIC)
/*N*/   {
/*N*/       aString = String ( SdResId( STR_PRESOBJ_GRAPHIC ) );
/*N*/   }
/*N*/   else if (eObjKind == PRESOBJ_OBJECT)
/*N*/   {
/*N*/       aString = String ( SdResId( STR_PRESOBJ_OBJECT ) );
/*N*/   }
/*N*/   else if (eObjKind == PRESOBJ_CHART)
/*N*/   {
/*N*/       aString = String ( SdResId( STR_PRESOBJ_CHART ) );
/*N*/   }
/*N*/   else if (eObjKind == PRESOBJ_ORGCHART)
/*N*/   {
/*N*/       aString = String ( SdResId( STR_PRESOBJ_ORGCHART ) );
/*N*/   }
/*N*/   else if (eObjKind == PRESOBJ_TABLE)
/*N*/   {
/*N*/       aString = String ( SdResId( STR_PRESOBJ_TABLE ) );
/*N*/   }
/*N*/ #ifdef STARIMAGE_AVAILABLE
/*N*/   else if (eObjKind == PRESOBJ_IMAGE)
/*N*/   {
/*N*/       aString = String ( SdResId( STR_PRESOBJ_IMAGE ) );
/*N*/   }
/*N*/ #endif
/*N*/
/*N*/   return(aString);
/*N*/ }

/*N*/ extern uno::Reference< uno::XInterface > createUnoPageImpl( SdPage* pPage );

/*N*/ uno::Reference< uno::XInterface > SdPage::createUnoPage()
/*N*/ {
/*N*/   return createUnoPageImpl( this );
/*N*/ }
