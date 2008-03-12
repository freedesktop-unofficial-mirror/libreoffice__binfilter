/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_svdedxv.cxx,v $
 *
 *  $Revision: 1.9 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 09:35:34 $
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


#include "svdedxv.hxx"
#include <bf_svtools/solar.hrc>

#ifndef _STRING_H
#include <tools/string.h>
#endif










#include "svditext.hxx"
#include "svdoutl.hxx"
#include "svdstr.hrc"   // Namen aus der Resource



// #98988#
namespace binfilter {

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void SdrObjEditView::ImpClearVars()
/*N*/ {
/*N*/     bQuickTextEditMode=TRUE;
/*N*/     bMacroMode=TRUE;
/*N*/     pTextEditObj=NULL;
/*N*/     pTextEditOutliner=NULL;
/*N*/     pTextEditOutlinerView=NULL;
/*N*/     pTextEditPV=NULL;
/*N*/     pTextEditWin=NULL;
/*N*/     pTextEditCursorMerker=NULL;
/*N*/     pEditPara=NULL;
/*N*/     bTextEditNewObj=FALSE;
/*N*/     bMacroDown=FALSE;
/*N*/     pMacroObj=NULL;
/*N*/     pMacroPV=NULL;
/*N*/     pMacroWin=NULL;
/*N*/     nMacroTol=0;
/*N*/     bTextEditDontDelete=FALSE;
/*N*/     bTextEditOnlyOneView=FALSE;
/*N*/ }

/*N*/ SdrObjEditView::SdrObjEditView(SdrModel* pModel1, OutputDevice* pOut):
/*N*/     SdrGlueEditView(pModel1,pOut)
/*N*/ {
/*N*/     ImpClearVars();
/*N*/ }

/*?*/ SdrObjEditView::SdrObjEditView(SdrModel* pModel1, ExtOutputDevice* pXOut):
/*?*/     SdrGlueEditView(pModel1,pXOut)
/*?*/ {
/*?*/     ImpClearVars();
/*?*/ }

/*N*/ SdrObjEditView::~SdrObjEditView()
/*N*/ {
/*N*/   pTextEditWin = NULL;            // Damit es in EndTextEdit kein ShowCursor gibt
/*N*/   if (IsTextEdit()){DBG_BF_ASSERT(0, "STRIP"); }//STRIP001  EndTextEdit();
/*N*/     if (pTextEditOutliner!=NULL) {
/*?*/         delete pTextEditOutliner;
/*N*/     }
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ BOOL SdrObjEditView::IsAction() const
/*N*/ {
/*N*/     return IsMacroObj() || SdrGlueEditView::IsAction();
/*N*/ }




/*N*/ void SdrObjEditView::BrkAction()
/*N*/ {
/*N*/     BrkMacroObj();
/*N*/     SdrGlueEditView::BrkAction();
/*N*/ }


/*N*/ void __EXPORT SdrObjEditView::SFX_NOTIFY(SfxBroadcaster& rBC, const TypeId& rBCType, const SfxHint& rHint, const TypeId& rHintType)
/*N*/ {
/*N*/     SdrGlueEditView::SFX_NOTIFY(rBC,rBCType,rHint,rHintType);
/*N*/     // Printerwechsel waerend des Editierens
/*N*/     SdrHint* pSdrHint=PTR_CAST(SdrHint,&rHint);
/*N*/     if (pSdrHint!=NULL && pTextEditOutliner!=NULL) {
/*?*/         SdrHintKind eKind=pSdrHint->GetKind();
/*?*/         if (eKind==HINT_REFDEVICECHG) {
/*?*/             pTextEditOutliner->SetRefDevice(pMod->GetRefDevice());
/*?*/         }
/*?*/         if (eKind==HINT_DEFAULTTABCHG) {
/*?*/             pTextEditOutliner->SetDefTab(pMod->GetDefaultTabulator());
/*?*/         }
/*?*/         if (eKind==HINT_DEFFONTHGTCHG) {
/*?*/             // ...
/*?*/         }
/*?*/         if (eKind==HINT_MODELSAVED) { // #43095#
/*?*/             DBG_BF_ASSERT(0, "STRIP"); //STRIP001 pTextEditOutliner->ClearModifyFlag();
/*?*/         }
/*N*/     }
/*N*/ }

/*N*/ void SdrObjEditView::ModelHasChanged()
/*N*/ {
/*N*/     SdrGlueEditView::ModelHasChanged();
/*N*/     if (IsTextEdit() && !pTextEditObj->IsInserted()) {DBG_BF_ASSERT(0, "STRIP"); }//STRIP001 EndTextEdit(); // Objekt geloescht
/*N*/     // TextEditObj geaendert?
/*N*/     if (IsTextEdit()) {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/     }
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  @@@@@@ @@@@@ @@   @@ @@@@@@  @@@@@ @@@@@  @@ @@@@@@
//    @@   @@    @@@ @@@   @@    @@    @@  @@ @@   @@
//    @@   @@     @@@@@    @@    @@    @@  @@ @@   @@
//    @@   @@@@    @@@     @@    @@@@  @@  @@ @@   @@
//    @@   @@     @@@@@    @@    @@    @@  @@ @@   @@
//    @@   @@    @@@ @@@   @@    @@    @@  @@ @@   @@
//    @@   @@@@@ @@   @@   @@    @@@@@ @@@@@  @@   @@
//
////////////////////////////////////////////////////////////////////////////////////////////////////







/*N*/ BOOL SdrObjEditView::BegTextEdit(SdrObject* pObj, SdrPageView* pPV, Window* pWin,
/*N*/   SdrOutliner* pGivenOutliner, OutlinerView* pGivenOutlinerView,
/*N*/   BOOL bDontDeleteOutliner, BOOL bOnlyOneView)
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001
/*N*/ }


/*N*/ SdrEndTextEditKind SdrObjEditView::EndTextEdit(BOOL bDontDeleteReally)
/*N*/ {DBG_BF_ASSERT(0, "STRIP");SdrEndTextEditKind eRet=SDRENDTEXTEDIT_UNCHANGED; return eRet; //STRIP001
/*N*/ }



/*N*/ BOOL SdrObjEditView::IsTextEditHit(const Point& rHit, short nTol) const
/*N*/ {
/*N*/     BOOL bOk=FALSE;
/*N*/     if (pTextEditObj!=NULL) {
/*?*/         nTol=ImpGetHitTolLogic(nTol,NULL);
/*?*/         // nur drittel Toleranz hier, damit die Handles
/*?*/         // noch vernuenftig getroffen werden koennen
/*?*/         nTol=nTol/3;
/*?*/         nTol=0; // Joe am 6.3.1997: Keine Hittoleranz mehr hier
/*?*/         if (!bOk) {
/*?*/             DBG_BF_ASSERT(0, "STRIP"); //STRIP001 Rectangle aEditArea;
/*?*/         }
/*N*/     }
/*N*/     return bOk;
/*N*/ }

/*N*/ BOOL SdrObjEditView::IsTextEditFrameHit(const Point& rHit) const
/*N*/ {
/*N*/     BOOL bOk=FALSE;
/*N*/     if (pTextEditObj!=NULL) {
/*?*/         DBG_BF_ASSERT(0, "STRIP"); //STRIP001 SdrTextObj* pText=PTR_CAST(SdrTextObj,pTextEditObj);
/*N*/     }
/*N*/     return bOk;
/*N*/ }


/*N*/ void SdrObjEditView::DelWin(OutputDevice* pWin1)
/*N*/ {
/*N*/     SdrGlueEditView::DelWin(pWin1);
/*N*/     if (pTextEditObj!=NULL && !bTextEditOnlyOneView && pWin1->GetOutDevType()==OUTDEV_WINDOW) {
/*?*/         DBG_BF_ASSERT(0, "STRIP"); //STRIP001 for (ULONG i=pTextEditOutliner->GetViewCount(); i>0;) {
/*N*/     }
/*N*/ }

/*N*/ BOOL SdrObjEditView::IsTextEditInSelectionMode() const
/*N*/ {
/*N*/     return pTextEditOutliner!=NULL && pTextEditOutliner->IsInSelectionMode();
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  @@   @@  @@@@   @@@@  @@@@@   @@@@   @@   @@  @@@@  @@@@@  @@@@@
//  @@@ @@@ @@  @@ @@  @@ @@  @@ @@  @@  @@@ @@@ @@  @@ @@  @@ @@
//  @@@@@@@ @@  @@ @@     @@  @@ @@  @@  @@@@@@@ @@  @@ @@  @@ @@
//  @@@@@@@ @@@@@@ @@     @@@@@  @@  @@  @@@@@@@ @@  @@ @@  @@ @@@@
//  @@ @ @@ @@  @@ @@     @@  @@ @@  @@  @@ @ @@ @@  @@ @@  @@ @@
//  @@   @@ @@  @@ @@  @@ @@  @@ @@  @@  @@   @@ @@  @@ @@  @@ @@
//  @@   @@ @@  @@  @@@@  @@  @@  @@@@   @@   @@  @@@@  @@@@@  @@@@@
//
////////////////////////////////////////////////////////////////////////////////////////////////////





/*N*/ void SdrObjEditView::BrkMacroObj()
/*N*/ {
/*N*/     if (pMacroObj!=NULL) {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/     }
/*N*/ }


}
