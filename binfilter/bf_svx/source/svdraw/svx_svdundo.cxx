/*************************************************************************
 *
 *  $RCSfile: svx_svdundo.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 16:33:06 $
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

#include "svdundo.hxx"
// auto strip #include "svditext.hxx"
// auto strip #include "svdotext.hxx"
// auto strip #include "svdobj.hxx"
// auto strip #include "svdpage.hxx"
// auto strip #include "svdlayer.hxx"
// auto strip #include "svdmodel.hxx"
// auto strip #include "svdview.hxx"
#include "svdstr.hrc"   // Namen aus der Resource
// auto strip #include "svdglob.hxx"  // StringCache
#include "scene3d.hxx"

// auto strip #ifndef _OUTLOBJ_HXX //autogen
// auto strip #include <outlobj.hxx>
// auto strip #endif

// #i11426#
// auto strip #ifndef _SVDOGRP_HXX
// auto strip #include <svdogrp.hxx>
// auto strip #endif

// #109587#
// auto strip #ifndef _SVDCAPT_HXX
// auto strip #include <svdocapt.hxx>
// auto strip #endif

// #109587#
// auto strip #ifndef _SFX_WHITER_HXX
// auto strip #include <svtools/whiter.hxx>
// auto strip #endif
namespace binfilter {

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 TYPEINIT1(SdrUndoAction,SfxUndoAction);

//STRIP001 BOOL SdrUndoAction::CanRepeat(SfxRepeatTarget& rView) const
//STRIP001 {
//STRIP001  SdrView* pV=PTR_CAST(SdrView,&rView);
//STRIP001  if (pV!=NULL) return CanSdrRepeat(*pV);
//STRIP001  return FALSE;
//STRIP001 }

//STRIP001 void SdrUndoAction::Repeat(SfxRepeatTarget& rView)
//STRIP001 {
//STRIP001  SdrView* pV=PTR_CAST(SdrView,&rView);
//STRIP001  if (pV!=NULL) SdrRepeat(*pV);
//STRIP001  DBG_ASSERT(pV!=NULL,"Repeat: Uebergebenes SfxRepeatTarget ist keine SdrView");
//STRIP001 }

//STRIP001 XubString SdrUndoAction::GetRepeatComment(SfxRepeatTarget& rView) const
//STRIP001 {
//STRIP001  SdrView* pV=PTR_CAST(SdrView,&rView);
//STRIP001  if (pV!=NULL) return GetSdrRepeatComment(*pV);
//STRIP001  return String();
//STRIP001 }

//STRIP001 FASTBOOL SdrUndoAction::CanSdrRepeat(SdrView& rView) const
//STRIP001 {
//STRIP001  return FALSE;
//STRIP001 }

//STRIP001 void SdrUndoAction::SdrRepeat(SdrView& rView)
//STRIP001 {
//STRIP001 }

//STRIP001 XubString SdrUndoAction::GetSdrRepeatComment(SdrView& rView) const
//STRIP001 {
//STRIP001  return String();
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ SdrUndoGroup::SdrUndoGroup(SdrModel& rNewMod)
/*N*/ : SdrUndoAction(rNewMod),
/*N*/   aBuf(1024,32,32),
/*N*/   eFunction(SDRREPFUNC_OBJ_NONE)      /*#72642#*/
/*N*/ {}

/*?*/ SdrUndoGroup::SdrUndoGroup(SdrModel& rNewMod,const String& rStr)
/*?*/ : SdrUndoAction(rNewMod),
/*?*/   aBuf(1024,32,32),
/*?*/   aComment(rStr),
/*?*/   eFunction(SDRREPFUNC_OBJ_NONE)
/*?*/ {}

/*N*/ SdrUndoGroup::~SdrUndoGroup()
/*N*/ {
/*N*/   Clear();
/*N*/ }

/*N*/ void SdrUndoGroup::Clear()
/*N*/ {
/*N*/   for (ULONG nu=0; nu<GetActionCount(); nu++) {
/*N*/       SdrUndoAction* pAct=GetAction(nu);
/*N*/       delete pAct;
/*N*/   }
/*N*/   aBuf.Clear();
/*N*/ }

/*N*/ void SdrUndoGroup::AddAction(SdrUndoAction* pAct)
/*N*/ {
/*N*/   aBuf.Insert(pAct,CONTAINER_APPEND);
/*N*/ }

//STRIP001 void SdrUndoGroup::Undo()
//STRIP001 {
//STRIP001  for (ULONG nu=GetActionCount(); nu>0;) {
//STRIP001      nu--;
//STRIP001      SdrUndoAction* pAct=GetAction(nu);
//STRIP001      pAct->Undo();
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrUndoGroup::Redo()
//STRIP001 {
//STRIP001  for (ULONG nu=0; nu<GetActionCount(); nu++) {
//STRIP001      SdrUndoAction* pAct=GetAction(nu);
//STRIP001      pAct->Redo();
//STRIP001  }
//STRIP001 }

//STRIP001 XubString SdrUndoGroup::GetComment() const
//STRIP001 {
//STRIP001  XubString aRet(aComment);
//STRIP001  sal_Char aSearchText[] = "%O";
//STRIP001  String aSearchString(aSearchText, sizeof(aSearchText-1));
//STRIP001
//STRIP001  aRet.SearchAndReplace(aSearchString, aObjDescription);
//STRIP001
//STRIP001  return aRet;
//STRIP001 }

//STRIP001 FASTBOOL SdrUndoGroup::CanSdrRepeat(SdrView& rView) const
//STRIP001 {
//STRIP001  switch (eFunction) {
//STRIP001      case SDRREPFUNC_OBJ_NONE            :  return FALSE;
//STRIP001      case SDRREPFUNC_OBJ_DELETE          :  return rView.HasMarkedObj();
//STRIP001      case SDRREPFUNC_OBJ_COMBINE_POLYPOLY:  return rView.IsCombinePossible(FALSE);
//STRIP001      case SDRREPFUNC_OBJ_COMBINE_ONEPOLY :  return rView.IsCombinePossible(TRUE);
//STRIP001      case SDRREPFUNC_OBJ_DISMANTLE_POLYS :  return rView.IsDismantlePossible(FALSE);
//STRIP001      case SDRREPFUNC_OBJ_DISMANTLE_LINES :  return rView.IsDismantlePossible(TRUE);
//STRIP001      case SDRREPFUNC_OBJ_CONVERTTOPOLY   :  return rView.IsConvertToPolyObjPossible(FALSE);
//STRIP001      case SDRREPFUNC_OBJ_CONVERTTOPATH   :  return rView.IsConvertToPathObjPossible(FALSE);
//STRIP001      case SDRREPFUNC_OBJ_GROUP           :  return rView.IsGroupPossible();
//STRIP001      case SDRREPFUNC_OBJ_UNGROUP         :  return rView.IsUnGroupPossible();
//STRIP001      case SDRREPFUNC_OBJ_PUTTOTOP        :  return rView.IsToTopPossible();
//STRIP001      case SDRREPFUNC_OBJ_PUTTOBTM        :  return rView.IsToBtmPossible();
//STRIP001      case SDRREPFUNC_OBJ_MOVTOTOP        :  return rView.IsToTopPossible();
//STRIP001      case SDRREPFUNC_OBJ_MOVTOBTM        :  return rView.IsToBtmPossible();
//STRIP001      case SDRREPFUNC_OBJ_REVORDER        :  return rView.IsReverseOrderPossible();
//STRIP001      case SDRREPFUNC_OBJ_IMPORTMTF       :  return rView.IsImportMtfPossible();
//STRIP001  } // switch
//STRIP001  return FALSE;
//STRIP001 }

//STRIP001 void SdrUndoGroup::SdrRepeat(SdrView& rView)
//STRIP001 {
//STRIP001  switch (eFunction) {
//STRIP001      case SDRREPFUNC_OBJ_NONE            :  break;
//STRIP001      case SDRREPFUNC_OBJ_DELETE          :  rView.DeleteMarked();                break;
//STRIP001      case SDRREPFUNC_OBJ_COMBINE_POLYPOLY:  rView.CombineMarkedObjects(FALSE);   break;
//STRIP001      case SDRREPFUNC_OBJ_COMBINE_ONEPOLY :  rView.CombineMarkedObjects(TRUE);    break;
//STRIP001      case SDRREPFUNC_OBJ_DISMANTLE_POLYS :  rView.DismantleMarkedObjects(FALSE); break;
//STRIP001      case SDRREPFUNC_OBJ_DISMANTLE_LINES :  rView.DismantleMarkedObjects(TRUE);  break;
//STRIP001      case SDRREPFUNC_OBJ_CONVERTTOPOLY   :  rView.ConvertMarkedToPolyObj(FALSE); break;
//STRIP001      case SDRREPFUNC_OBJ_CONVERTTOPATH   :  rView.ConvertMarkedToPathObj(FALSE); break;
//STRIP001      case SDRREPFUNC_OBJ_GROUP           :  rView.GroupMarked();                 break;
//STRIP001      case SDRREPFUNC_OBJ_UNGROUP         :  rView.UnGroupMarked();               break;
//STRIP001      case SDRREPFUNC_OBJ_PUTTOTOP        :  rView.PutMarkedToTop();              break;
//STRIP001      case SDRREPFUNC_OBJ_PUTTOBTM        :  rView.PutMarkedToBtm();              break;
//STRIP001      case SDRREPFUNC_OBJ_MOVTOTOP        :  rView.MovMarkedToTop();              break;
//STRIP001      case SDRREPFUNC_OBJ_MOVTOBTM        :  rView.MovMarkedToBtm();              break;
//STRIP001      case SDRREPFUNC_OBJ_REVORDER        :  rView.ReverseOrderOfMarked();        break;
//STRIP001      case SDRREPFUNC_OBJ_IMPORTMTF       :  rView.DoImportMarkedMtf();           break;
//STRIP001  } // switch
//STRIP001 }

//STRIP001 XubString SdrUndoGroup::GetSdrRepeatComment(SdrView& rView) const
//STRIP001 {
//STRIP001  XubString aRet(aComment);
//STRIP001  sal_Char aSearchText[] = "%O";
//STRIP001  String aSearchString(aSearchText, sizeof(aSearchText-1));
//STRIP001
//STRIP001  aRet.SearchAndReplace(aSearchString, ImpGetResStr(STR_ObjNameSingulPlural));
//STRIP001
//STRIP001  return aRet;
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
//
//   @@@@   @@@@@   @@@@@@  @@@@@   @@@@   @@@@@@   @@@@
//  @@  @@  @@  @@      @@  @@     @@  @@    @@    @@  @@
//  @@  @@  @@  @@      @@  @@     @@        @@    @@
//  @@  @@  @@@@@       @@  @@@@   @@        @@     @@@@
//  @@  @@  @@  @@      @@  @@     @@        @@        @@
//  @@  @@  @@  @@  @@  @@  @@     @@  @@    @@    @@  @@
//   @@@@   @@@@@    @@@@   @@@@@   @@@@     @@     @@@@
//
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ SdrUndoObj::SdrUndoObj(SdrObject& rNewObj):
/*N*/   SdrUndoAction(*rNewObj.GetModel()),
/*N*/   pObj(&rNewObj)
/*N*/ {
/*N*/ }

//STRIP001 void SdrUndoObj::ImpTakeDescriptionStr(USHORT nStrCacheID, XubString& rStr, FASTBOOL bRepeat) const
//STRIP001 {
//STRIP001  rStr = ImpGetResStr(nStrCacheID);
//STRIP001  sal_Char aSearchText[] = "%O";
//STRIP001  String aSearchString(aSearchText, sizeof(aSearchText-1));
//STRIP001
//STRIP001  xub_StrLen nPos = rStr.Search(aSearchString);
//STRIP001
//STRIP001  if(nPos != STRING_NOTFOUND)
//STRIP001  {
//STRIP001      rStr.Erase(nPos, 2);
//STRIP001
//STRIP001      if(bRepeat)
//STRIP001      {
//STRIP001          rStr.Insert(ImpGetResStr(STR_ObjNameSingulPlural), nPos);
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          XubString aStr;
//STRIP001
//STRIP001          pObj->TakeObjNameSingul(aStr);
//STRIP001          rStr.Insert(aStr, nPos);
//STRIP001      }
//STRIP001  }
//STRIP001 }

// #94278# common call method for evtl. page change when UNDO/REDO
// is triggered
//STRIP001 void SdrUndoObj::ImpShowPageOfThisObject()
//STRIP001 {
//STRIP001  if(pObj && pObj->IsInserted() && pObj->GetPage() && pObj->GetModel())
//STRIP001  {
//STRIP001      SdrHint aHint(HINT_SWITCHTOPAGE);
//STRIP001
//STRIP001      aHint.SetObject(pObj);
//STRIP001      aHint.SetPage(pObj->GetPage());
//STRIP001
//STRIP001      pObj->GetModel()->Broadcast(aHint);
//STRIP001  }
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 SdrUndoAttrObj::SdrUndoAttrObj(SdrObject& rNewObj, FASTBOOL bStyleSheet1, FASTBOOL bSaveText):
//STRIP001  SdrUndoObj(rNewObj),
//STRIP001  pUndoSet(NULL),
//STRIP001  pRedoSet(NULL),
//STRIP001  pRepeatSet(NULL),
//STRIP001  pUndoStyleSheet(NULL),
//STRIP001  pRedoStyleSheet(NULL),
//STRIP001  pRepeatStyleSheet(NULL),
//STRIP001  pTextUndo(NULL),
//STRIP001
//STRIP001  // #i8508#
//STRIP001  pTextRedo(NULL),
//STRIP001
//STRIP001  pUndoGroup(NULL),
//STRIP001  bHaveToTakeRedoSet(TRUE)
//STRIP001 {
//STRIP001  bStyleSheet = bStyleSheet1;
//STRIP001  pUndoSet = rNewObj.CreateNewItemSet(*((SfxItemPool*)SdrObject::GetGlobalDrawObjectItemPool()));
//STRIP001  pRedoSet = rNewObj.CreateNewItemSet(*((SfxItemPool*)SdrObject::GetGlobalDrawObjectItemPool()));
//STRIP001
//STRIP001  SdrObjList* pOL = rNewObj.GetSubList();
//STRIP001  BOOL bIsGroup(pOL!=NULL && pOL->GetObjCount());
//STRIP001  BOOL bIs3DScene(bIsGroup && pObj->ISA(E3dScene));
//STRIP001
//STRIP001  if(bIsGroup)
//STRIP001  {
//STRIP001      // Aha, Gruppenobjekt
//STRIP001      pUndoGroup = new SdrUndoGroup(*pObj->GetModel());
//STRIP001      sal_uInt32 nObjAnz(pOL->GetObjCount());
//STRIP001
//STRIP001      for(sal_uInt32 nObjNum(0); nObjNum < nObjAnz; nObjNum++)
//STRIP001      {
//STRIP001          pUndoGroup->AddAction(
//STRIP001              new SdrUndoAttrObj(*pOL->GetObj(nObjNum), bStyleSheet1));
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if(!bIsGroup || bIs3DScene)
//STRIP001  {
//STRIP001      pUndoSet->Put(pObj->GetItemSet());
//STRIP001
//STRIP001      if(bStyleSheet)
//STRIP001          pUndoStyleSheet = pObj->GetStyleSheet();
//STRIP001
//STRIP001      if(bSaveText)
//STRIP001      {
//STRIP001          pTextUndo = pObj->GetOutlinerParaObject();
//STRIP001          if(pTextUndo)
//STRIP001              pTextUndo = pTextUndo->Clone();
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 SdrUndoAttrObj::~SdrUndoAttrObj()
//STRIP001 {
//STRIP001  if(pUndoSet)
//STRIP001      delete pUndoSet;
//STRIP001  if(pRedoSet)
//STRIP001      delete pRedoSet;
//STRIP001  if(pRepeatSet)
//STRIP001      delete pRepeatSet;
//STRIP001  if(pUndoGroup)
//STRIP001      delete pUndoGroup;
//STRIP001  if(pTextUndo)
//STRIP001      delete pTextUndo;
//STRIP001
//STRIP001  // #i8508#
//STRIP001  if(pTextRedo)
//STRIP001      delete pTextRedo;
//STRIP001 }

//STRIP001 void SdrUndoAttrObj::SetRepeatAttr(const SfxItemSet& rSet)
//STRIP001 {
//STRIP001  if(pRepeatSet)
//STRIP001      delete pRepeatSet;
//STRIP001
//STRIP001  pRepeatSet = pObj->CreateNewItemSet(*((SfxItemPool*)SdrObject::GetGlobalDrawObjectItemPool()));
//STRIP001
//STRIP001  pRepeatSet->Put(rSet);
//STRIP001 }

//STRIP001 void SdrUndoAttrObj::Undo()
//STRIP001 {
//STRIP001  BOOL bIs3DScene(pObj && pObj->ISA(E3dScene));
//STRIP001
//STRIP001  // #94278# Trigger PageChangeCall
//STRIP001  ImpShowPageOfThisObject();
//STRIP001
//STRIP001  if(!pUndoGroup || bIs3DScene)
//STRIP001  {
//STRIP001      if(bHaveToTakeRedoSet)
//STRIP001      {
//STRIP001          bHaveToTakeRedoSet = FALSE;
//STRIP001          pRedoSet->Put(pObj->GetItemSet());
//STRIP001          if(bStyleSheet)
//STRIP001              pRedoStyleSheet=pObj->GetStyleSheet();
//STRIP001
//STRIP001          if(pTextUndo)
//STRIP001          {
//STRIP001              // #i8508#
//STRIP001              pTextRedo = pObj->GetOutlinerParaObject();
//STRIP001
//STRIP001              if(pTextRedo)
//STRIP001                  pTextRedo = pTextRedo->Clone();
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      if(bStyleSheet)
//STRIP001      {
//STRIP001          pRedoStyleSheet = pObj->GetStyleSheet();
//STRIP001          pObj->SetStyleSheet(pUndoStyleSheet, TRUE);
//STRIP001      }
//STRIP001
//STRIP001      SdrBroadcastItemChange aItemChange(*pObj);
//STRIP001
//STRIP001      // #105122# Since ClearItem sets back everything to normal
//STRIP001      // it also sets fit-to-size text to non-fit-to-size text and
//STRIP001      // switches on autogrowheight (the default). That may lead to
//STRIP001      // loosing the geometry size info for the object when it is
//STRIP001      // re-layouted from AdjustTextFrameWidthAndHeight(). This makes
//STRIP001      // rescuing the size of the object necessary.
//STRIP001      const Rectangle aSnapRect = pObj->GetSnapRect();
//STRIP001
//STRIP001      // #109587#
//STRIP001      if(pObj->ISA(SdrCaptionObj))
//STRIP001      {
//STRIP001          // do a more smooth item deletion here, else the text
//STRIP001          // rect will be reformatted, especially when information regarding
//STRIP001          // vertical text is changed. When clearing only set items it's
//STRIP001          // slower, but safer regarding such information (it's not changed
//STRIP001          // usually)
//STRIP001          SfxWhichIter aIter(*pUndoSet);
//STRIP001          sal_uInt16 nWhich(aIter.FirstWhich());
//STRIP001
//STRIP001          while(nWhich)
//STRIP001          {
//STRIP001              if(SFX_ITEM_SET != pUndoSet->GetItemState(nWhich, sal_False))
//STRIP001              {
//STRIP001                  pObj->ClearItem(nWhich);
//STRIP001              }
//STRIP001
//STRIP001              nWhich = aIter.NextWhich();
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          pObj->ClearItem();
//STRIP001      }
//STRIP001
//STRIP001      pObj->SetItemSet(*pUndoSet);
//STRIP001
//STRIP001      // #105122# Restore prev size here when it was changed.
//STRIP001      if(aSnapRect != pObj->GetSnapRect())
//STRIP001      {
//STRIP001          pObj->NbcSetSnapRect(aSnapRect);
//STRIP001      }
//STRIP001
//STRIP001      pObj->BroadcastItemChange(aItemChange);
//STRIP001
//STRIP001      if(pTextUndo)
//STRIP001      {
//STRIP001          pObj->SetOutlinerParaObject(pTextUndo->Clone());
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if(pUndoGroup)
//STRIP001  {
//STRIP001      pUndoGroup->Undo();
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrUndoAttrObj::Redo()
//STRIP001 {
//STRIP001  BOOL bIs3DScene(pObj && pObj->ISA(E3dScene));
//STRIP001
//STRIP001  if(!pUndoGroup || bIs3DScene)
//STRIP001  {
//STRIP001      if(bStyleSheet)
//STRIP001      {
//STRIP001          pUndoStyleSheet = pObj->GetStyleSheet();
//STRIP001          pObj->SetStyleSheet(pRedoStyleSheet, TRUE);
//STRIP001      }
//STRIP001
//STRIP001      SdrBroadcastItemChange aItemChange(*pObj);
//STRIP001
//STRIP001      // #105122#
//STRIP001      const Rectangle aSnapRect = pObj->GetSnapRect();
//STRIP001
//STRIP001      // #109587#
//STRIP001      if(pObj->ISA(SdrCaptionObj))
//STRIP001      {
//STRIP001          // do a more smooth item deletion here, else the text
//STRIP001          // rect will be reformatted, especially when information regarding
//STRIP001          // vertical text is changed. When clearing only set items it's
//STRIP001          // slower, but safer regarding such information (it's not changed
//STRIP001          // usually)
//STRIP001          SfxWhichIter aIter(*pRedoSet);
//STRIP001          sal_uInt16 nWhich(aIter.FirstWhich());
//STRIP001
//STRIP001          while(nWhich)
//STRIP001          {
//STRIP001              if(SFX_ITEM_SET != pRedoSet->GetItemState(nWhich, sal_False))
//STRIP001              {
//STRIP001                  pObj->ClearItem(nWhich);
//STRIP001              }
//STRIP001
//STRIP001              nWhich = aIter.NextWhich();
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          pObj->ClearItem();
//STRIP001      }
//STRIP001
//STRIP001      pObj->SetItemSet(*pRedoSet);
//STRIP001
//STRIP001      // #105122# Restore prev size here when it was changed.
//STRIP001      if(aSnapRect != pObj->GetSnapRect())
//STRIP001      {
//STRIP001          pObj->NbcSetSnapRect(aSnapRect);
//STRIP001      }
//STRIP001
//STRIP001      pObj->BroadcastItemChange(aItemChange);
//STRIP001
//STRIP001      // #i8508#
//STRIP001      if(pTextRedo)
//STRIP001      {
//STRIP001          pObj->SetOutlinerParaObject(pTextRedo->Clone());
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if(pUndoGroup)
//STRIP001  {
//STRIP001      pUndoGroup->Redo();
//STRIP001  }
//STRIP001
//STRIP001  // #94278# Trigger PageChangeCall
//STRIP001  ImpShowPageOfThisObject();
//STRIP001 }

//STRIP001 XubString SdrUndoAttrObj::GetComment() const
//STRIP001 {
//STRIP001  XubString aStr;
//STRIP001
//STRIP001  if(bStyleSheet)
//STRIP001  {
//STRIP001      ImpTakeDescriptionStr(STR_EditSetStylesheet, aStr);
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      ImpTakeDescriptionStr(STR_EditSetAttributes, aStr);
//STRIP001  }
//STRIP001
//STRIP001  return aStr;
//STRIP001 }

//STRIP001 void SdrUndoAttrObj::SdrRepeat(SdrView& rView)
//STRIP001 {
//STRIP001  if(pRepeatSet)
//STRIP001  {
//STRIP001      rView.SetAttrToMarked(*pRepeatSet, FALSE);
//STRIP001  }
//STRIP001 }

//STRIP001 FASTBOOL SdrUndoAttrObj::CanSdrRepeat(SdrView& rView) const
//STRIP001 {
//STRIP001  return (pRepeatSet!=0L && rView.HasMarkedObj());
//STRIP001 }

//STRIP001 XubString SdrUndoAttrObj::GetSdrRepeatComment(SdrView& rView) const
//STRIP001 {
//STRIP001  XubString aStr;
//STRIP001
//STRIP001  if(bStyleSheet)
//STRIP001  {
//STRIP001      ImpTakeDescriptionStr(STR_EditSetStylesheet, aStr, TRUE);
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      ImpTakeDescriptionStr(STR_EditSetAttributes, aStr, TRUE);
//STRIP001  }
//STRIP001
//STRIP001  return aStr;
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 void SdrUndoMoveObj::Undo()
//STRIP001 {
//STRIP001  // #94278# Trigger PageChangeCall
//STRIP001  ImpShowPageOfThisObject();
//STRIP001
//STRIP001  pObj->Move(Size(-aDistance.Width(),-aDistance.Height()));
//STRIP001 }

//STRIP001 void SdrUndoMoveObj::Redo()
//STRIP001 {
//STRIP001  pObj->Move(Size(aDistance.Width(),aDistance.Height()));
//STRIP001
//STRIP001  // #94278# Trigger PageChangeCall
//STRIP001  ImpShowPageOfThisObject();
//STRIP001 }

//STRIP001 XubString SdrUndoMoveObj::GetComment() const
//STRIP001 {
//STRIP001  XubString aStr;
//STRIP001  ImpTakeDescriptionStr(STR_EditMove,aStr);
//STRIP001  return aStr;
//STRIP001 }

//STRIP001 void SdrUndoMoveObj::SdrRepeat(SdrView& rView)
//STRIP001 {
//STRIP001  rView.MoveMarkedObj(aDistance);
//STRIP001 }

//STRIP001 FASTBOOL SdrUndoMoveObj::CanSdrRepeat(SdrView& rView) const
//STRIP001 {
//STRIP001  return rView.HasMarkedObj();
//STRIP001 }

//STRIP001 XubString SdrUndoMoveObj::GetSdrRepeatComment(SdrView& rView) const
//STRIP001 {
//STRIP001  XubString aStr;
//STRIP001  ImpTakeDescriptionStr(STR_EditMove,aStr,TRUE);
//STRIP001  return aStr;
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ SdrUndoGeoObj::SdrUndoGeoObj(SdrObject& rNewObj):
/*N*/   SdrUndoObj(rNewObj),
/*N*/   pUndoGeo(NULL),
/*N*/   pRedoGeo(NULL),
/*N*/   pUndoGroup(NULL)
/*N*/ {
/*N*/   SdrObjList* pOL=rNewObj.GetSubList();
/*N*/   if (pOL!=NULL && pOL->GetObjCount() && !rNewObj.ISA(E3dScene))
/*N*/   {
/*?*/       // Aha, Gruppenobjekt
/*?*/       // AW: Aber keine 3D-Szene, dann nur fuer die Szene selbst den Undo anlegen
/*?*/       pUndoGroup=new SdrUndoGroup(*pObj->GetModel());
/*?*/       ULONG nObjAnz=pOL->GetObjCount();
/*?*/       for (ULONG nObjNum=0; nObjNum<nObjAnz; nObjNum++) {
/*?*/           pUndoGroup->AddAction(new SdrUndoGeoObj(*pOL->GetObj(nObjNum)));
/*?*/       }
/*N*/   } else {
/*N*/       pUndoGeo=pObj->GetGeoData();
/*N*/   }
/*N*/ }

/*N*/ SdrUndoGeoObj::~SdrUndoGeoObj()
/*N*/ {
/*N*/   if (pUndoGeo!=NULL) delete pUndoGeo;
/*N*/   if (pRedoGeo!=NULL) delete pRedoGeo;
/*N*/   if (pUndoGroup!=NULL) delete pUndoGroup;
/*N*/ }

//STRIP001 void SdrUndoGeoObj::Undo()
//STRIP001 {
//STRIP001  // #94278# Trigger PageChangeCall
//STRIP001  ImpShowPageOfThisObject();
//STRIP001
//STRIP001  if(pUndoGroup)
//STRIP001  {
//STRIP001      // #97172#
//STRIP001      pObj->SendRepaintBroadcast();
//STRIP001
//STRIP001      pUndoGroup->Undo();
//STRIP001
//STRIP001      // #97172#
//STRIP001      pObj->SendRepaintBroadcast();
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if (pRedoGeo!=NULL) delete pRedoGeo;
//STRIP001      pRedoGeo=pObj->GetGeoData();
//STRIP001      pObj->SetGeoData(*pUndoGeo);
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrUndoGeoObj::Redo()
//STRIP001 {
//STRIP001  if(pUndoGroup)
//STRIP001  {
//STRIP001      // #97172#
//STRIP001      pObj->SendRepaintBroadcast();
//STRIP001
//STRIP001      pUndoGroup->Redo();
//STRIP001
//STRIP001      // #97172#
//STRIP001      pObj->SendRepaintBroadcast();
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if (pUndoGeo!=NULL) delete pUndoGeo;
//STRIP001      pUndoGeo=pObj->GetGeoData();
//STRIP001      pObj->SetGeoData(*pRedoGeo);
//STRIP001  }
//STRIP001
//STRIP001  // #94278# Trigger PageChangeCall
//STRIP001  ImpShowPageOfThisObject();
//STRIP001 }

//STRIP001 XubString SdrUndoGeoObj::GetComment() const
//STRIP001 {
//STRIP001  XubString aStr;
//STRIP001  ImpTakeDescriptionStr(STR_DragMethObjOwn,aStr);
//STRIP001  return aStr;
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ SdrUndoObjList::SdrUndoObjList(SdrObject& rNewObj, FASTBOOL bOrdNumDirect):
/*N*/   pView(NULL),
/*N*/   pPageView(NULL),
/*N*/   SdrUndoObj(rNewObj),
/*N*/   bOwner(FALSE)
/*N*/ {
/*N*/   pObjList=pObj->GetObjList();
/*N*/   if (bOrdNumDirect) {
/*?*/       nOrdNum=pObj->GetOrdNumDirect();
/*N*/   } else {
/*N*/       nOrdNum=pObj->GetOrdNum();
/*N*/   }
/*N*/ }
/*N*/
/*N*/ SdrUndoObjList::~SdrUndoObjList()
/*N*/ {
/*N*/   if (pObj!=NULL && IsOwner())
/*N*/   {
/*N*/       // Attribute muessen wieder in den regulaeren Pool
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 SetOwner(FALSE);
/*?*/
/*?*/       // nun loeschen
//STRIP001 /*?*/        delete pObj;
/*N*/   }
/*N*/ }

//STRIP001 void SdrUndoObjList::SetOwner(BOOL bNew)
//STRIP001 {
//STRIP001  if(bNew != bOwner)
//STRIP001  {
//STRIP001      // Besitzuebergang des Objektes. Hier muss auch die Speicherung der
//STRIP001      // Items des Objektes zwischen dem allgemeinen Pool und dem Pool des
//STRIP001      // Undo-Managers wechseln
//STRIP001      if(bNew)
//STRIP001      {
//STRIP001          pObj->MigrateItemPool(&rMod.GetItemPool(), ((SfxItemPool*)SdrObject::GetGlobalDrawObjectItemPool()));
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          pObj->MigrateItemPool(((SfxItemPool*)SdrObject::GetGlobalDrawObjectItemPool()), &rMod.GetItemPool());
//STRIP001          pObj->SetStyleSheet(pObj->GetStyleSheet(), TRUE);
//STRIP001      }
//STRIP001
//STRIP001      // umsetzen
//STRIP001      bOwner = bNew;
//STRIP001  }
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 void SdrUndoRemoveObj::Undo()
//STRIP001 {
//STRIP001  // #94278# Trigger PageChangeCall
//STRIP001  ImpShowPageOfThisObject();
//STRIP001
//STRIP001  DBG_ASSERT(!pObj->IsInserted(),"UndoRemoveObj: pObj ist bereits Inserted");
//STRIP001  if (!pObj->IsInserted())
//STRIP001  {
//STRIP001      // #i11426#
//STRIP001      // For UNDOs in Calc/Writer it is necessary to adapt the anchor
//STRIP001      // pos of the target object.
//STRIP001      Point aOwnerAnchorPos(0, 0);
//STRIP001
//STRIP001      if(pObjList
//STRIP001          && pObjList->GetOwnerObj()
//STRIP001          && pObjList->GetOwnerObj()->ISA(SdrObjGroup))
//STRIP001      {
//STRIP001          aOwnerAnchorPos = pObjList->GetOwnerObj()->GetAnchorPos();
//STRIP001      }
//STRIP001
//STRIP001      SdrInsertReason aReason(SDRREASON_UNDO);
//STRIP001      pObjList->InsertObject(pObj,nOrdNum,&aReason);
//STRIP001
//STRIP001      // #i11426#
//STRIP001      if(aOwnerAnchorPos.X() || aOwnerAnchorPos.Y())
//STRIP001      {
//STRIP001          pObj->NbcSetAnchorPos(aOwnerAnchorPos);
//STRIP001      }
//STRIP001
//STRIP001      if(pObjList->GetOwnerObj() && pObjList->GetOwnerObj()->ISA(E3dObject) && pObj->ISA(E3dObject))
//STRIP001      {
//STRIP001          E3dScene* pScene = ((E3dObject*)pObjList->GetOwnerObj())->GetScene();
//STRIP001          if(pScene)
//STRIP001              pScene->CorrectSceneDimensions();
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrUndoRemoveObj::Redo()
//STRIP001 {
//STRIP001  DBG_ASSERT(pObj->IsInserted(),"RedoRemoveObj: pObj ist nicht Inserted");
//STRIP001  if (pObj->IsInserted()) {
//STRIP001      SdrObject* pChkObj=pObjList->RemoveObject(nOrdNum);
//STRIP001      DBG_ASSERT(pChkObj==pObj,"RedoRemoveObj: RemoveObjNum!=pObj");
//STRIP001      if(pObjList->GetOwnerObj() && pObjList->GetOwnerObj()->ISA(E3dObject) && pObj->ISA(E3dObject))
//STRIP001      {
//STRIP001          E3dScene* pScene = ((E3dObject*)pObjList->GetOwnerObj())->GetScene();
//STRIP001          if(pScene)
//STRIP001              pScene->CorrectSceneDimensions();
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // #94278# Trigger PageChangeCall
//STRIP001  ImpShowPageOfThisObject();
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 void SdrUndoInsertObj::Undo()
//STRIP001 {
//STRIP001  // #94278# Trigger PageChangeCall
//STRIP001  ImpShowPageOfThisObject();
//STRIP001
//STRIP001  DBG_ASSERT(pObj->IsInserted(),"UndoInsertObj: pObj ist nicht Inserted");
//STRIP001  if (pObj->IsInserted()) {
//STRIP001      SdrObject* pChkObj=pObjList->RemoveObject(nOrdNum);
//STRIP001      DBG_ASSERT(pChkObj==pObj,"UndoInsertObj: RemoveObjNum!=pObj");
//STRIP001      if(pObjList->GetOwnerObj() && pObjList->GetOwnerObj()->ISA(E3dObject) && pObj->ISA(E3dObject))
//STRIP001      {
//STRIP001          E3dScene* pScene = ((E3dObject*)pObjList->GetOwnerObj())->GetScene();
//STRIP001          if(pScene)
//STRIP001              pScene->CorrectSceneDimensions();
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrUndoInsertObj::Redo()
//STRIP001 {
//STRIP001  DBG_ASSERT(!pObj->IsInserted(),"RedoInsertObj: pObj ist bereits Inserted");
//STRIP001  if (!pObj->IsInserted()) {
//STRIP001      SdrInsertReason aReason(SDRREASON_UNDO);
//STRIP001      pObjList->InsertObject(pObj,nOrdNum,&aReason);
//STRIP001      if(pObjList->GetOwnerObj() && pObjList->GetOwnerObj()->ISA(E3dObject) && pObj->ISA(E3dObject))
//STRIP001      {
//STRIP001          E3dScene* pScene = ((E3dObject*)pObjList->GetOwnerObj())->GetScene();
//STRIP001          if(pScene)
//STRIP001              pScene->CorrectSceneDimensions();
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // #94278# Trigger PageChangeCall
//STRIP001  ImpShowPageOfThisObject();
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 void SdrUndoDelObj::Undo()
//STRIP001 {
//STRIP001  SdrUndoRemoveObj::Undo();
//STRIP001  DBG_ASSERT(IsOwner(),"UndoDeleteObj: pObj gehoert nicht der UndoAction");
//STRIP001  SetOwner(FALSE);
//STRIP001 }

//STRIP001 void SdrUndoDelObj::Redo()
//STRIP001 {
//STRIP001  SdrUndoRemoveObj::Redo();
//STRIP001  DBG_ASSERT(!IsOwner(),"RedoDeleteObj: pObj gehoert bereits der UndoAction");
//STRIP001  SetOwner(TRUE);
//STRIP001 }

//STRIP001 XubString SdrUndoDelObj::GetComment() const
//STRIP001 {
//STRIP001  XubString aStr;
//STRIP001  ImpTakeDescriptionStr(STR_EditDelete,aStr);
//STRIP001  return aStr;
//STRIP001 }

//STRIP001 void SdrUndoDelObj::SdrRepeat(SdrView& rView)
//STRIP001 {
//STRIP001  rView.DeleteMarked();
//STRIP001 }

//STRIP001 FASTBOOL SdrUndoDelObj::CanSdrRepeat(SdrView& rView) const
//STRIP001 {
//STRIP001  return rView.HasMarkedObj();
//STRIP001 }

//STRIP001 XubString SdrUndoDelObj::GetSdrRepeatComment(SdrView& rView) const
//STRIP001 {
//STRIP001  XubString aStr;
//STRIP001  ImpTakeDescriptionStr(STR_EditDelete,aStr,TRUE);
//STRIP001  return aStr;
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 void SdrUndoNewObj::Undo()
//STRIP001 {
//STRIP001  SdrUndoInsertObj::Undo();
//STRIP001  DBG_ASSERT(!IsOwner(),"RedoNewObj: pObj gehoert bereits der UndoAction");
//STRIP001  SetOwner(TRUE);
//STRIP001 }

//STRIP001 void SdrUndoNewObj::Redo()
//STRIP001 {
//STRIP001  SdrUndoInsertObj::Redo();
//STRIP001  DBG_ASSERT(IsOwner(),"RedoNewObj: pObj gehoert nicht der UndoAction");
//STRIP001  SetOwner(FALSE);
//STRIP001 }

//STRIP001 XubString SdrUndoNewObj::GetComment() const
//STRIP001 {
//STRIP001  XubString aStr;
//STRIP001  ImpTakeDescriptionStr(STR_UndoInsertObj,aStr);
//STRIP001  return aStr;
//STRIP001 }

//STRIP001 SdrUndoReplaceObj::SdrUndoReplaceObj(SdrObject& rOldObj1, SdrObject& rNewObj1, FASTBOOL bOrdNumDirect):
//STRIP001  SdrUndoObj(rOldObj1),
//STRIP001  pNewObj(&rNewObj1),
//STRIP001  bOldOwner(FALSE),
//STRIP001  bNewOwner(FALSE)
//STRIP001 {
//STRIP001  SetOldOwner(TRUE);
//STRIP001
//STRIP001  pObjList=pObj->GetObjList();
//STRIP001  if (bOrdNumDirect) {
//STRIP001      nOrdNum=pObj->GetOrdNumDirect();
//STRIP001  } else {
//STRIP001      nOrdNum=pObj->GetOrdNum();
//STRIP001  }
//STRIP001 }

//STRIP001 SdrUndoReplaceObj::~SdrUndoReplaceObj()
//STRIP001 {
//STRIP001  if (pObj!=NULL && IsOldOwner())
//STRIP001  {
//STRIP001      // Attribute muessen wieder in den regulaeren Pool
//STRIP001      SetOldOwner(FALSE);
//STRIP001
//STRIP001      // nun loeschen
//STRIP001      delete pObj;
//STRIP001  }
//STRIP001  if (pNewObj!=NULL && IsNewOwner())
//STRIP001  {
//STRIP001      // Attribute muessen wieder in den regulaeren Pool
//STRIP001      SetNewOwner(FALSE);
//STRIP001
//STRIP001      // nun loeschen
//STRIP001      delete pNewObj;
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrUndoReplaceObj::Undo()
//STRIP001 {
//STRIP001  // #94278# Trigger PageChangeCall
//STRIP001  ImpShowPageOfThisObject();
//STRIP001
//STRIP001  if (IsOldOwner() && !IsNewOwner()) {
//STRIP001      DBG_ASSERT(!pObj->IsInserted(),"SdrUndoReplaceObj::Undo(): Altes Objekt ist bereits inserted!");
//STRIP001      DBG_ASSERT(pNewObj->IsInserted(),"SdrUndoReplaceObj::Undo(): Neues Objekt ist nicht inserted!");
//STRIP001      SetOldOwner(FALSE);
//STRIP001      SetNewOwner(TRUE);
//STRIP001      SdrObject* pCompObj=pObjList->ReplaceObject(pObj,nOrdNum);
//STRIP001  } else {
//STRIP001      DBG_ERROR("SdrUndoReplaceObj::Undo(): IsMine-Flags stehen verkehrt. Doppelter Undo-Aufruf?");
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrUndoReplaceObj::Redo()
//STRIP001 {
//STRIP001  if (!IsOldOwner() && IsNewOwner()) {
//STRIP001      DBG_ASSERT(!pNewObj->IsInserted(),"SdrUndoReplaceObj::Redo(): Neues Objekt ist bereits inserted!");
//STRIP001      DBG_ASSERT(pObj->IsInserted(),"SdrUndoReplaceObj::Redo(): Altes Objekt ist nicht inserted!");
//STRIP001      SetOldOwner(TRUE);
//STRIP001      SetNewOwner(FALSE);
//STRIP001      SdrObject* pCompObj=pObjList->ReplaceObject(pNewObj,nOrdNum);
//STRIP001  } else {
//STRIP001      DBG_ERROR("SdrUndoReplaceObj::Redo(): IsMine-Flags stehen verkehrt. Doppelter Redo-Aufruf?");
//STRIP001  }
//STRIP001
//STRIP001  // #94278# Trigger PageChangeCall
//STRIP001  ImpShowPageOfThisObject();
//STRIP001 }

//STRIP001 void SdrUndoReplaceObj::SetNewOwner(BOOL bNew)
//STRIP001 {
//STRIP001  if(bNew != bNewOwner)
//STRIP001  {
//STRIP001      // Besitzuebergang des Objektes. Hier muss auch die Speicherung der
//STRIP001      // Items des Objektes zwischen dem allgemeinen Pool und dem Pool des
//STRIP001      // Undo-Managers wechseln
//STRIP001      if(bNew)
//STRIP001      {
//STRIP001          pNewObj->MigrateItemPool(&rMod.GetItemPool(), ((SfxItemPool*)SdrObject::GetGlobalDrawObjectItemPool()));
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          pNewObj->MigrateItemPool(((SfxItemPool*)SdrObject::GetGlobalDrawObjectItemPool()), &rMod.GetItemPool());
//STRIP001      }
//STRIP001
//STRIP001      // umsetzen
//STRIP001      bNewOwner = bNew;
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrUndoReplaceObj::SetOldOwner(BOOL bNew)
//STRIP001 {
//STRIP001  if(bNew != bOldOwner)
//STRIP001  {
//STRIP001      // Besitzuebergang des Objektes. Hier muss auch die Speicherung der
//STRIP001      // Items des Objektes zwischen dem allgemeinen Pool und dem Pool des
//STRIP001      // Undo-Managers wechseln
//STRIP001      if(bNew)
//STRIP001      {
//STRIP001          pObj->MigrateItemPool(&rMod.GetItemPool(), ((SfxItemPool*)SdrObject::GetGlobalDrawObjectItemPool()));
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          pObj->MigrateItemPool(((SfxItemPool*)SdrObject::GetGlobalDrawObjectItemPool()), &rMod.GetItemPool());
//STRIP001      }
//STRIP001
//STRIP001      // umsetzen
//STRIP001      bOldOwner = bNew;
//STRIP001  }
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 XubString SdrUndoCopyObj::GetComment() const
//STRIP001 {
//STRIP001  XubString aStr;
//STRIP001  ImpTakeDescriptionStr(STR_UndoCopyObj,aStr);
//STRIP001  return aStr;
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////
// #i11702#

//STRIP001 SdrUndoObjectLayerChange::SdrUndoObjectLayerChange(SdrObject& rObj, SdrLayerID aOldLayer, SdrLayerID aNewLayer)
//STRIP001 :    SdrUndoObj(rObj),
//STRIP001  maOldLayer(aOldLayer),
//STRIP001  maNewLayer(aNewLayer)
//STRIP001 {
//STRIP001 }
//STRIP001
//STRIP001 void SdrUndoObjectLayerChange::Undo()
//STRIP001 {
//STRIP001  ImpShowPageOfThisObject();
//STRIP001  pObj->SetLayer(maOldLayer);
//STRIP001 }
//STRIP001
//STRIP001 void SdrUndoObjectLayerChange::Redo()
//STRIP001 {
//STRIP001  pObj->SetLayer(maNewLayer);
//STRIP001  ImpShowPageOfThisObject();
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 SdrUndoObjOrdNum::SdrUndoObjOrdNum(SdrObject& rNewObj, UINT32 nOldOrdNum1, UINT32 nNewOrdNum1):
//STRIP001  SdrUndoObj(rNewObj),
//STRIP001  nOldOrdNum(nOldOrdNum1),
//STRIP001  nNewOrdNum(nNewOrdNum1)
//STRIP001 {
//STRIP001 }

//STRIP001 void SdrUndoObjOrdNum::Undo()
//STRIP001 {
//STRIP001  // #94278# Trigger PageChangeCall
//STRIP001  ImpShowPageOfThisObject();
//STRIP001
//STRIP001  SdrObjList* pOL=pObj->GetObjList();
//STRIP001  if (pOL==NULL) {
//STRIP001      DBG_ERROR("UndoObjOrdNum: pObj hat keine ObjList");
//STRIP001      return;
//STRIP001  }
//STRIP001  pOL->SetObjectOrdNum(nNewOrdNum,nOldOrdNum);
//STRIP001 }

//STRIP001 void SdrUndoObjOrdNum::Redo()
//STRIP001 {
//STRIP001  SdrObjList* pOL=pObj->GetObjList();
//STRIP001  if (pOL==NULL) {
//STRIP001      DBG_ERROR("RedoObjOrdNum: pObj hat keine ObjList");
//STRIP001      return;
//STRIP001  }
//STRIP001  pOL->SetObjectOrdNum(nOldOrdNum,nNewOrdNum);
//STRIP001
//STRIP001  // #94278# Trigger PageChangeCall
//STRIP001  ImpShowPageOfThisObject();
//STRIP001 }

//STRIP001 XubString SdrUndoObjOrdNum::GetComment() const
//STRIP001 {
//STRIP001  XubString aStr;
//STRIP001  ImpTakeDescriptionStr(STR_UndoObjOrdNum,aStr);
//STRIP001  return aStr;
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 SdrUndoObjSetText::SdrUndoObjSetText(SdrObject& rNewObj):
//STRIP001  SdrUndoObj(rNewObj),
//STRIP001  pOldText(NULL),
//STRIP001  pNewText(NULL),
//STRIP001  bNewTextAvailable(FALSE),
//STRIP001  bEmptyPresObj(FALSE)
//STRIP001 {
//STRIP001  pOldText=rNewObj.GetOutlinerParaObject();
//STRIP001  bEmptyPresObj = rNewObj.IsEmptyPresObj();
//STRIP001  if (pOldText!=NULL)
//STRIP001      pOldText=pOldText->Clone();
//STRIP001 }

//STRIP001 SdrUndoObjSetText::~SdrUndoObjSetText()
//STRIP001 {
//STRIP001  if ( pOldText )
//STRIP001      delete pOldText;
//STRIP001  if ( pNewText )
//STRIP001      delete pNewText;
//STRIP001 }

//STRIP001 void SdrUndoObjSetText::AfterSetText()
//STRIP001 {
//STRIP001  if (!bNewTextAvailable)
//STRIP001  {
//STRIP001      pNewText=pObj->GetOutlinerParaObject();
//STRIP001      if (pNewText!=NULL) pNewText=pNewText->Clone();
//STRIP001      bNewTextAvailable=TRUE;
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrUndoObjSetText::Undo()
//STRIP001 {
//STRIP001  // #94278# Trigger PageChangeCall
//STRIP001  ImpShowPageOfThisObject();
//STRIP001
//STRIP001  // alten Text sichern fuer Redo
//STRIP001  if (!bNewTextAvailable)
//STRIP001      AfterSetText();
//STRIP001  // Text fuer Undo kopieren, denn SetOutlinerParaObject() ist Eigentumsuebereignung
//STRIP001  OutlinerParaObject* pText1=pOldText;
//STRIP001  if (pText1!=NULL)
//STRIP001      pText1=pText1->Clone();
//STRIP001  pObj->SetOutlinerParaObject(pText1);
//STRIP001  pObj->SetEmptyPresObj( bEmptyPresObj );
//STRIP001 }

//STRIP001 void SdrUndoObjSetText::Redo()
//STRIP001 {
//STRIP001  // Text fuer Undo kopieren, denn SetOutlinerParaObject() ist Eigentumsuebereignung
//STRIP001  OutlinerParaObject* pText1=pNewText;
//STRIP001  if (pText1!=NULL) pText1=pText1->Clone();
//STRIP001  pObj->SetOutlinerParaObject(pText1);
//STRIP001
//STRIP001  // #94278# Trigger PageChangeCall
//STRIP001  ImpShowPageOfThisObject();
//STRIP001 }

//STRIP001 XubString SdrUndoObjSetText::GetComment() const
//STRIP001 {
//STRIP001  XubString aStr;
//STRIP001  ImpTakeDescriptionStr(STR_UndoObjSetText,aStr);
//STRIP001  return aStr;
//STRIP001 }

//STRIP001 XubString SdrUndoObjSetText::GetSdrRepeatComment(SdrView& rView) const
//STRIP001 {
//STRIP001  XubString aStr;
//STRIP001  ImpTakeDescriptionStr(STR_UndoObjSetText,aStr);
//STRIP001  return aStr;
//STRIP001 }

//STRIP001 void SdrUndoObjSetText::SdrRepeat(SdrView& rView)
//STRIP001 {
//STRIP001  if (bNewTextAvailable && rView.HasMarkedObj()) {
//STRIP001      const SdrMarkList& rML=rView.GetMarkList();
//STRIP001      XubString aStr;
//STRIP001      ImpTakeDescriptionStr(STR_UndoObjSetText,aStr);
//STRIP001      rView.BegUndo(aStr);
//STRIP001      ULONG nAnz=rML.GetMarkCount();
//STRIP001      for (ULONG nm=0; nm<nAnz; nm++) {
//STRIP001          SdrObject* pObj=rML.GetMark(nm)->GetObj();
//STRIP001          SdrTextObj* pTextObj=PTR_CAST(SdrTextObj,pObj);
//STRIP001          if (pTextObj!=NULL) {
//STRIP001              rView.AddUndo(new SdrUndoObjSetText(*pTextObj));
//STRIP001              OutlinerParaObject* pText1=pNewText;
//STRIP001              if (pText1!=NULL) pText1=pText1->Clone();
//STRIP001              pTextObj->SetOutlinerParaObject(pText1);
//STRIP001          }
//STRIP001      }
//STRIP001      rView.EndUndo();
//STRIP001  }
//STRIP001 }

//STRIP001 FASTBOOL SdrUndoObjSetText::CanSdrRepeat(SdrView& rView) const
//STRIP001 {
//STRIP001  FASTBOOL bOk=FALSE;
//STRIP001  if (bNewTextAvailable && rView.HasMarkedObj()) {
//STRIP001      bOk=TRUE;
//STRIP001  }
//STRIP001  return bOk;
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  @@      @@@@   @@  @@  @@@@@  @@@@@
//  @@     @@  @@  @@  @@  @@     @@  @@
//  @@     @@  @@  @@  @@  @@     @@  @@
//  @@     @@@@@@   @@@@   @@@@   @@@@@
//  @@     @@  @@    @@    @@     @@  @@
//  @@     @@  @@    @@    @@     @@  @@
//  @@@@@  @@  @@    @@    @@@@@  @@  @@
//
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 SdrUndoLayer::SdrUndoLayer(USHORT nLayerNum, SdrLayerAdmin& rNewLayerAdmin, SdrModel& rNewModel):
//STRIP001  SdrUndoAction(rNewModel),
//STRIP001  pLayer(rNewLayerAdmin.GetLayer(nLayerNum)),
//STRIP001  pLayerAdmin(&rNewLayerAdmin),
//STRIP001  nNum(nLayerNum),
//STRIP001  bItsMine(FALSE)
//STRIP001 {
//STRIP001 }

//STRIP001 SdrUndoLayer::~SdrUndoLayer()
//STRIP001 {
//STRIP001  if (bItsMine) {
//STRIP001      delete pLayer;
//STRIP001  }
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 void SdrUndoNewLayer::Undo()
//STRIP001 {
//STRIP001  DBG_ASSERT(!bItsMine,"SdrUndoNewLayer::Undo(): Layer gehoert bereits der UndoAction");
//STRIP001  bItsMine=TRUE;
//STRIP001  SdrLayer* pCmpLayer=pLayerAdmin->RemoveLayer(nNum);
//STRIP001  DBG_ASSERT(pCmpLayer==pLayer,"SdrUndoNewLayer::Undo(): Removter Layer ist != pLayer");
//STRIP001 }

//STRIP001 void SdrUndoNewLayer::Redo()
//STRIP001 {
//STRIP001  DBG_ASSERT(bItsMine,"SdrUndoNewLayer::Undo(): Layer gehoert nicht der UndoAction");
//STRIP001  bItsMine=FALSE;
//STRIP001  pLayerAdmin->InsertLayer(pLayer,nNum);
//STRIP001 }

//STRIP001 XubString SdrUndoNewLayer::GetComment() const
//STRIP001 {
//STRIP001  return ImpGetResStr(STR_UndoNewLayer);
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 void SdrUndoDelLayer::Undo()
//STRIP001 {
//STRIP001  DBG_ASSERT(bItsMine,"SdrUndoDelLayer::Undo(): Layer gehoert nicht der UndoAction");
//STRIP001  bItsMine=FALSE;
//STRIP001  pLayerAdmin->InsertLayer(pLayer,nNum);
//STRIP001 }

//STRIP001 void SdrUndoDelLayer::Redo()
//STRIP001 {
//STRIP001  DBG_ASSERT(!bItsMine,"SdrUndoDelLayer::Undo(): Layer gehoert bereits der UndoAction");
//STRIP001  bItsMine=TRUE;
//STRIP001  SdrLayer* pCmpLayer=pLayerAdmin->RemoveLayer(nNum);
//STRIP001  DBG_ASSERT(pCmpLayer==pLayer,"SdrUndoDelLayer::Redo(): Removter Layer ist != pLayer");
//STRIP001 }

//STRIP001 XubString SdrUndoDelLayer::GetComment() const
//STRIP001 {
//STRIP001  return ImpGetResStr(STR_UndoDelLayer);
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 void SdrUndoMoveLayer::Undo()
//STRIP001 {
//STRIP001  SdrLayer* pCmpLayer=pLayerAdmin->RemoveLayer(nNeuPos);
//STRIP001  DBG_ASSERT(pCmpLayer==pLayer,"SdrUndoMoveLayer::Undo(): Removter Layer ist != pLayer");
//STRIP001  pLayerAdmin->InsertLayer(pLayer,nNum);
//STRIP001 }

//STRIP001 void SdrUndoMoveLayer::Redo()
//STRIP001 {
//STRIP001  SdrLayer* pCmpLayer=pLayerAdmin->RemoveLayer(nNum);
//STRIP001  DBG_ASSERT(pCmpLayer==pLayer,"SdrUndoMoveLayer::Redo(): Removter Layer ist != pLayer");
//STRIP001  pLayerAdmin->InsertLayer(pLayer,nNeuPos);
//STRIP001 }

//STRIP001 XubString SdrUndoMoveLayer::GetComment() const
//STRIP001 {
//STRIP001  return ImpGetResStr(STR_UndoMovLayer);
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  @@@@@    @@@@    @@@@   @@@@@   @@@@
//  @@  @@  @@  @@  @@  @@  @@     @@  @@
//  @@  @@  @@  @@  @@      @@     @@
//  @@@@@   @@@@@@  @@ @@@  @@@@    @@@@
//  @@      @@  @@  @@  @@  @@         @@
//  @@      @@  @@  @@  @@  @@     @@  @@
//  @@      @@  @@   @@@@@  @@@@@   @@@@
//
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ SdrUndoPage::SdrUndoPage(SdrPage& rNewPg):
/*N*/   SdrUndoAction(*rNewPg.GetModel()), pPage(&rNewPg)
/*N*/ { }

//STRIP001 void SdrUndoPage::ImpInsertPage(USHORT nNum)
//STRIP001 {
//STRIP001  DBG_ASSERT(!pPage->IsInserted(),"SdrUndoPage::ImpInsertPage(): pPage ist bereits Inserted");
//STRIP001  if (!pPage->IsInserted()) {
//STRIP001      if (pPage->IsMasterPage()) {
//STRIP001          rMod.InsertMasterPage(pPage,nNum);
//STRIP001      } else {
//STRIP001          rMod.InsertPage(pPage,nNum);
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrUndoPage::ImpRemovePage(USHORT nNum)
//STRIP001 {
//STRIP001  DBG_ASSERT(pPage->IsInserted(),"SdrUndoPage::ImpRemovePage(): pPage ist nicht Inserted");
//STRIP001  if (pPage->IsInserted()) {
//STRIP001      SdrPage* pChkPg=NULL;
//STRIP001      if (pPage->IsMasterPage()) {
//STRIP001          pChkPg=rMod.RemoveMasterPage(nNum);
//STRIP001      } else {
//STRIP001          pChkPg=rMod.RemovePage(nNum);
//STRIP001      }
//STRIP001      DBG_ASSERT(pChkPg==pPage,"SdrUndoPage::ImpRemovePage(): RemovePage!=pPage");
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrUndoPage::ImpMovePage(USHORT nOldNum, USHORT nNewNum)
//STRIP001 {
//STRIP001  DBG_ASSERT(pPage->IsInserted(),"SdrUndoPage::ImpMovePage(): pPage ist nicht Inserted");
//STRIP001  if (pPage->IsInserted()) {
//STRIP001      if (pPage->IsMasterPage()) {
//STRIP001          rMod.MoveMasterPage(nOldNum,nNewNum);
//STRIP001      } else {
//STRIP001          rMod.MovePage(nOldNum,nNewNum);
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrUndoPage::ImpTakeDescriptionStr(USHORT nStrCacheID, XubString& rStr, USHORT n, FASTBOOL bRepeat) const
//STRIP001 {
//STRIP001  rStr=ImpGetResStr(nStrCacheID);
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ SdrUndoPageList::SdrUndoPageList(SdrPage& rNewPg):
/*N*/   SdrUndoPage(rNewPg),
/*N*/   bItsMine(FALSE)
/*N*/ {
/*N*/   nPageNum=rNewPg.GetPageNum();
/*N*/ }

/*N*/ SdrUndoPageList::~SdrUndoPageList()
/*N*/ {
/*N*/   if(bItsMine && pPage)
/*N*/   {
/*?*/       delete pPage;
/*?*/       pPage = 0L;
/*N*/   }
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 SdrUndoDelPage::SdrUndoDelPage(SdrPage& rNewPg):
//STRIP001  SdrUndoPageList(rNewPg),
//STRIP001  pUndoGroup(NULL)
//STRIP001 {
//STRIP001  bItsMine=TRUE;
//STRIP001  // Und nun ggf. die MasterPage-Beziehungen merken
//STRIP001  if (pPage->IsMasterPage()) {
//STRIP001      USHORT nMasterPageNum=pPage->GetPageNum();
//STRIP001      USHORT nPageAnz=rMod.GetPageCount();
//STRIP001      for (USHORT nPageNum=0; nPageNum<nPageAnz; nPageNum++) {
//STRIP001          SdrPage* pDrawPage=rMod.GetPage(nPageNum);
//STRIP001          USHORT nMasterAnz=pDrawPage->GetMasterPageCount();
//STRIP001          for (USHORT nMasterNum=nMasterAnz; nMasterNum>0;) { // Rueckwaerts, da die Beziehungen auch rueckwaerts entfernt werden
//STRIP001              nMasterNum--;
//STRIP001              USHORT nReferencedMaster=pDrawPage->GetMasterPageNum(nMasterNum);
//STRIP001              if (nReferencedMaster==nMasterPageNum) { // Aha, betroffen
//STRIP001                  if (pUndoGroup==NULL) {
//STRIP001                      pUndoGroup=new SdrUndoGroup(rMod);
//STRIP001                  }
//STRIP001                  pUndoGroup->AddAction(new SdrUndoPageRemoveMasterPage(*pDrawPage,nMasterNum));
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 SdrUndoDelPage::~SdrUndoDelPage()
//STRIP001 {
//STRIP001  if (pUndoGroup!=NULL) {
//STRIP001      delete pUndoGroup;
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrUndoDelPage::Undo()
//STRIP001 {
//STRIP001  ImpInsertPage(nPageNum);
//STRIP001  if (pUndoGroup!=NULL) { // MasterPage-Beziehungen wiederherstellen
//STRIP001      pUndoGroup->Undo();
//STRIP001  }
//STRIP001  DBG_ASSERT(bItsMine,"UndoDeletePage: pPage gehoert nicht der UndoAction");
//STRIP001  bItsMine=FALSE;
//STRIP001 }

//STRIP001 void SdrUndoDelPage::Redo()
//STRIP001 {
//STRIP001  ImpRemovePage(nPageNum);
//STRIP001  // Die MasterPage-Beziehungen werden ggf. von selbst geloesst
//STRIP001  DBG_ASSERT(!bItsMine,"RedoDeletePage: pPage gehoert bereits der UndoAction");
//STRIP001  bItsMine=TRUE;
//STRIP001 }

//STRIP001 XubString SdrUndoDelPage::GetComment() const
//STRIP001 {
//STRIP001  XubString aStr;
//STRIP001  ImpTakeDescriptionStr(STR_UndoDelPage,aStr,0,FALSE);
//STRIP001  return aStr;
//STRIP001 }

//STRIP001 XubString SdrUndoDelPage::GetSdrRepeatComment(SdrView& rView) const
//STRIP001 {
//STRIP001  XubString aStr;
//STRIP001  ImpTakeDescriptionStr(STR_UndoDelPage,aStr,0,FALSE);
//STRIP001  return aStr;
//STRIP001 }

//STRIP001 void SdrUndoDelPage::SdrRepeat(SdrView& rView)
//STRIP001 {
//STRIP001 }

//STRIP001 FASTBOOL SdrUndoDelPage::CanSdrRepeat(SdrView& rView) const
//STRIP001 {
//STRIP001  return FALSE;
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 void SdrUndoNewPage::Undo()
//STRIP001 {
//STRIP001  ImpRemovePage(nPageNum);
//STRIP001  DBG_ASSERT(!bItsMine,"UndoNewPage: pPage gehoert bereits der UndoAction");
//STRIP001  bItsMine=TRUE;
//STRIP001 }

//STRIP001 void SdrUndoNewPage::Redo()
//STRIP001 {
//STRIP001  ImpInsertPage(nPageNum);
//STRIP001  DBG_ASSERT(bItsMine,"RedoNewPage: pPage gehoert nicht der UndoAction");
//STRIP001  bItsMine=FALSE;
//STRIP001 }

//STRIP001 XubString SdrUndoNewPage::GetComment() const
//STRIP001 {
//STRIP001  XubString aStr;
//STRIP001  ImpTakeDescriptionStr(STR_UndoNewPage,aStr,0,FALSE);
//STRIP001  return aStr;
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 XubString SdrUndoCopyPage::GetComment() const
//STRIP001 {
//STRIP001  XubString aStr;
//STRIP001  ImpTakeDescriptionStr(STR_UndoCopPage,aStr,0,FALSE);
//STRIP001  return aStr;
//STRIP001 }

//STRIP001 XubString SdrUndoCopyPage::GetSdrRepeatComment(SdrView& rView) const
//STRIP001 {
//STRIP001  XubString aStr;
//STRIP001  ImpTakeDescriptionStr(STR_UndoCopPage,aStr,0,FALSE);
//STRIP001  return aStr;
//STRIP001 }

//STRIP001 void SdrUndoCopyPage::SdrRepeat(SdrView& rView)
//STRIP001 {
//STRIP001
//STRIP001 }

//STRIP001 FASTBOOL SdrUndoCopyPage::CanSdrRepeat(SdrView& rView) const
//STRIP001 {
//STRIP001  return FALSE;
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 void SdrUndoSetPageNum::Undo()
//STRIP001 {
//STRIP001  ImpMovePage(nNewPageNum,nOldPageNum);
//STRIP001 }

//STRIP001 void SdrUndoSetPageNum::Redo()
//STRIP001 {
//STRIP001  ImpMovePage(nOldPageNum,nNewPageNum);
//STRIP001 }

//STRIP001 XubString SdrUndoSetPageNum::GetComment() const
//STRIP001 {
//STRIP001  XubString aStr;
//STRIP001  ImpTakeDescriptionStr(STR_UndoMovPage,aStr,0,FALSE);
//STRIP001  return aStr;
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  @@   @@  @@@@   @@@@  @@@@@@ @@@@@ @@@@@   @@@@@   @@@@   @@@@  @@@@@  @@@@
//  @@@ @@@ @@  @@ @@  @@   @@   @@    @@  @@  @@  @@ @@  @@ @@  @@ @@    @@  @@
//  @@@@@@@ @@  @@ @@       @@   @@    @@  @@  @@  @@ @@  @@ @@     @@    @@
//  @@@@@@@ @@@@@@  @@@@    @@   @@@@  @@@@@   @@@@@  @@@@@@ @@ @@@ @@@@   @@@@
//  @@ @ @@ @@  @@     @@   @@   @@    @@  @@  @@     @@  @@ @@  @@ @@        @@
//  @@   @@ @@  @@ @@  @@   @@   @@    @@  @@  @@     @@  @@ @@  @@ @@    @@  @@
//  @@   @@ @@  @@  @@@@    @@   @@@@@ @@  @@  @@     @@  @@  @@@@@ @@@@@  @@@@
//
////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 SdrUndoPageMasterPage::SdrUndoPageMasterPage(SdrPage& rNewPg, USHORT nMasterDescriptorNum):
//STRIP001      SdrUndoPage(rNewPg), pMasterDescriptor(NULL),
//STRIP001      pNewMasterDescriptor(NULL), nMasterNum(0), nNewMasterNum(0)
//STRIP001 {
//STRIP001  nMasterNum=nMasterDescriptorNum;
//STRIP001  SdrMasterPageDescriptor* pDscr=&rNewPg.GetMasterPageDescriptor(nMasterDescriptorNum);
//STRIP001  if (pDscr!=NULL) { // den betroffenen MasterPageDescriptor kopieren
//STRIP001      pMasterDescriptor=new SdrMasterPageDescriptor(*pDscr);
//STRIP001  } else {
//STRIP001 #ifdef DBGUTIL
//STRIP001      String aMsg("SdrUndoPageMasterPage::Ctor(): Descriptornummer "); aMsg+=nMasterNum;
//STRIP001      aMsg+="\nKein MasterPageDescriptor an dieser Position gefunden.";
//STRIP001      DBG_ERROR(aMsg.GetStr());
//STRIP001 #endif
//STRIP001  }
//STRIP001 }

//STRIP001 SdrUndoPageMasterPage::~SdrUndoPageMasterPage()
//STRIP001 {
//STRIP001  if (pMasterDescriptor!=NULL) delete pMasterDescriptor;
//STRIP001  if (pNewMasterDescriptor!=NULL) delete pNewMasterDescriptor;
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 void SdrUndoPageInsertMasterPage::Undo()
//STRIP001 {
//STRIP001 #ifdef DBGUTIL
//STRIP001  String aMsg("SdrUndoPageInsertMasterPage::Undo(): Descriptornummer "); aMsg+=nMasterNum;
//STRIP001  if (pMasterDescriptor!=NULL) {
//STRIP001      aMsg+=" (MasterPage-Nummer im gemerkten Descriptor ist ";
//STRIP001      aMsg+=pMasterDescriptor->GetPageNum();
//STRIP001      aMsg+=')';
//STRIP001  } else {
//STRIP001      aMsg+=" (kein Descriptor gemerkt)";
//STRIP001  }
//STRIP001  aMsg+="\n";
//STRIP001  if (nMasterNum>=pPage->GetMasterPageCount()) {
//STRIP001      aMsg+="An der Seite sind nur ";
//STRIP001      aMsg+=pPage->GetMasterPageCount();
//STRIP001      aMsg+=" Descriptoren vorhanden.";
//STRIP001      DBG_ERROR(aMsg.GetStr());
//STRIP001  } else if (pMasterDescriptor!=NULL && *pMasterDescriptor!=*pPage->GetMasterPageDescriptor(nMasterNum)) {
//STRIP001      aMsg+="Aktueller und gemerkter Descriptor enthalten unterschiedliche MasterPage-Nummern";
//STRIP001      DBG_ERROR(aMsg.GetStr());
//STRIP001  }
//STRIP001 #endif
//STRIP001  pPage->RemoveMasterPage(nMasterNum);
//STRIP001 }

//STRIP001 void SdrUndoPageInsertMasterPage::Redo()
//STRIP001 {
//STRIP001  if (pMasterDescriptor!=NULL) {
//STRIP001      pPage->InsertMasterPage(*pMasterDescriptor,nMasterNum);
//STRIP001  } else {
//STRIP001 #ifdef DBGUTIL
//STRIP001      String aMsg("SdrUndoPageInsertMasterPage::Redo(): Descriptornummer "); aMsg+=nMasterNum;
//STRIP001      aMsg+="Kein MasterPageDescriptor gemerkt.";
//STRIP001      DBG_ERROR(aMsg.GetStr());
//STRIP001 #endif
//STRIP001  }
//STRIP001 }

//STRIP001 XubString SdrUndoPageInsertMasterPage::GetComment() const
//STRIP001 {
//STRIP001  XubString aStr;
//STRIP001  ImpTakeDescriptionStr(STR_UndoNewPageMasterDscr,aStr,0,FALSE);
//STRIP001  return aStr;
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 void SdrUndoPageRemoveMasterPage::Undo()
//STRIP001 {
//STRIP001  if (pMasterDescriptor!=NULL) {
//STRIP001      pPage->InsertMasterPage(*pMasterDescriptor,nMasterNum);
//STRIP001  } else {
//STRIP001 #ifdef DBGUTIL
//STRIP001      String aMsg("SdrUndoPageRemoveMasterPage::Undo(): Descriptornummer "); aMsg+=nMasterNum;
//STRIP001      aMsg+="Kein MasterPageDescriptor gemerkt.";
//STRIP001      DBG_ERROR(aMsg.GetStr());
//STRIP001 #endif
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrUndoPageRemoveMasterPage::Redo()
//STRIP001 {
//STRIP001 #ifdef DBGUTIL
//STRIP001  String aMsg("SdrUndoPageRemoveMasterPage::Redo(): Descriptornummer "); aMsg+=nMasterNum;
//STRIP001  if (pMasterDescriptor!=NULL) {
//STRIP001      aMsg+=" (MasterPage-Nummer im gemerkten Descriptor ist ";
//STRIP001      aMsg+=pMasterDescriptor->GetPageNum();
//STRIP001      aMsg+=')';
//STRIP001  } else {
//STRIP001      aMsg+=" (kein Descriptor gemerkt)";
//STRIP001  }
//STRIP001  aMsg+="\n";
//STRIP001  if (nMasterNum>=pPage->GetMasterPageCount()) {
//STRIP001      aMsg+="An der Seite sind nur ";
//STRIP001      aMsg+=pPage->GetMasterPageCount();
//STRIP001      aMsg+=" Descriptoren vorhanden.";
//STRIP001      DBG_ERROR(aMsg.GetStr());
//STRIP001  } else if (pMasterDescriptor!=NULL && *pMasterDescriptor!=*pPage->GetMasterPageDescriptor(nMasterNum)) {
//STRIP001      aMsg+="Aktueller und gemerkter Descriptor enthalten unterschiedliche MasterPage-Nummern";
//STRIP001      DBG_ERROR(aMsg.GetStr());
//STRIP001  }
//STRIP001 #endif
//STRIP001  pPage->RemoveMasterPage(nMasterNum);
//STRIP001 }

//STRIP001 XubString SdrUndoPageRemoveMasterPage::GetComment() const
//STRIP001 {
//STRIP001  XubString aStr;
//STRIP001  ImpTakeDescriptionStr(STR_UndoDelPageMasterDscr,aStr,0,FALSE);
//STRIP001  return aStr;
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 void SdrUndoPageMoveMasterPage::Undo()
//STRIP001 {
//STRIP001  pPage->MoveMasterPage(nNewMasterNum,nMasterNum);
//STRIP001 }

//STRIP001 void SdrUndoPageMoveMasterPage::Redo()
//STRIP001 {
//STRIP001  pPage->MoveMasterPage(nMasterNum,nNewMasterNum);
//STRIP001 }

//STRIP001 XubString SdrUndoPageMoveMasterPage::GetComment() const
//STRIP001 {
//STRIP001  XubString aStr;
//STRIP001  ImpTakeDescriptionStr(STR_UndoMovPageMasterDscr,aStr,0,FALSE);
//STRIP001  return aStr;
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 void SdrUndoPageChangeMasterPage::Undo()
//STRIP001 {
//STRIP001  if (pNewMasterDescriptor==NULL) {
//STRIP001      SdrMasterPageDescriptor* pDscr=&pPage->GetMasterPageDescriptor(nMasterNum);
//STRIP001      if (pDscr!=NULL) { // den neuen MasterPageDescriptor merken fuer Redo
//STRIP001          pNewMasterDescriptor=new SdrMasterPageDescriptor(*pDscr);
//STRIP001      } else {
//STRIP001 #ifdef DBGUTIL
//STRIP001          String aMsg("SdrUndoPageChangeMasterPage::Undo(): Descriptornummer "); aMsg+=nMasterNum;
//STRIP001          aMsg+="\nKein MasterPageDescriptor an dieser Position gefunden.";
//STRIP001          DBG_ERROR(aMsg.GetStr());
//STRIP001 #endif
//STRIP001      }
//STRIP001  }
//STRIP001  if (pMasterDescriptor!=NULL) {
//STRIP001      pPage->SetMasterPageDescriptor(*pMasterDescriptor,nMasterNum);
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrUndoPageChangeMasterPage::Redo()
//STRIP001 {
//STRIP001  if (pNewMasterDescriptor!=NULL) {
//STRIP001      pPage->SetMasterPageDescriptor(*pNewMasterDescriptor,nMasterNum);
//STRIP001  }
//STRIP001 }

//STRIP001 XubString SdrUndoPageChangeMasterPage::GetComment() const
//STRIP001 {
//STRIP001  XubString aStr;
//STRIP001  ImpTakeDescriptionStr(STR_UndoChgPageMasterDscr,aStr,0,FALSE);
//STRIP001  return aStr;
//STRIP001 }

}
