/*************************************************************************
 *
 *  $RCSfile: svx_svdopage.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:22:20 $
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

#include "svdopage.hxx"
#include "svdglob.hxx"  // Stringcache
#include "svdstr.hrc"   // Objektname
#include "svdtrans.hxx"
#include "svdetc.hxx"
#include "svdio.hxx"
#include "svdxout.hxx"
#include "svdmodel.hxx"
#include "svdpage.hxx"
#include "svdpagv.hxx"
#include "svdoutl.hxx"

#ifndef INCLUDED_SVTOOLS_COLORCFG_HXX
#include <svtools/colorcfg.hxx>
#endif

#ifndef _SFXITEMSET_HXX
#include <svtools/itemset.hxx>
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ TYPEINIT1(SdrPageObj,SdrObject);

/*N*/ SdrPageObj::SdrPageObj(USHORT nNewPageNum):
/*N*/   mpPageItemSet(0L),
/*N*/   nPageNum(nNewPageNum),
/*N*/   bPainting(FALSE),
/*N*/   bNotifying(FALSE)
/*N*/ {
/*N*/ }

/*?*/ SdrPageObj::SdrPageObj(const Rectangle& rRect, USHORT nNewPageNum):
/*?*/   mpPageItemSet(0L),
/*?*/   nPageNum(nNewPageNum),
/*?*/   bPainting(FALSE),
/*?*/   bNotifying(FALSE)
/*?*/ {
/*?*/   aOutRect=rRect;
/*?*/ }

/*N*/ SdrPageObj::~SdrPageObj()
/*N*/ {
/*N*/   if(mpPageItemSet)
/*?*/       delete mpPageItemSet;
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
// ItemSet access

/*N*/ const SfxItemSet& SdrPageObj::GetItemSet() const
/*N*/ {
/*N*/   if(!mpPageItemSet)
/*N*/       ((SdrPageObj*)this)->mpPageItemSet = ((SdrPageObj*)this)->CreateNewItemSet((SfxItemPool&)(*GetItemPool()));
/*N*/   return *mpPageItemSet;
/*N*/ }

/*N*/ SfxItemSet* SdrPageObj::CreateNewItemSet(SfxItemPool& rPool)
/*N*/ {
/*N*/   return new SfxItemSet(rPool);
/*N*/ }

/*N*/ void SdrPageObj::ItemChange(const sal_uInt16 nWhich, const SfxPoolItem* pNewItem)
/*N*/ {
/*N*/   // #86481# simply ignore item setting on page objects
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void __EXPORT SdrPageObj::SFX_NOTIFY(SfxBroadcaster& rBC, const TypeId&, const SfxHint& rHint, const TypeId&)
/*N*/ {
/*N*/   SdrHint* pSdrHint = PTR_CAST(SdrHint, &rHint);
/*N*/
/*N*/   if(pSdrHint)
/*N*/   {
/*N*/       SdrHintKind eHint = pSdrHint->GetKind();
/*N*/
/*N*/       if(eHint == HINT_PAGEORDERCHG)
/*N*/       {
/*N*/           SendRepaintBroadcast();
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           const SdrPage* pChangedPage = pSdrHint->GetPage();
/*N*/
/*N*/           if(pSdrHint->GetObject() != this
/*N*/               && pModel
/*N*/               && bInserted
/*N*/               && pChangedPage
/*N*/               && pChangedPage != pPage)
/*N*/           {
/*N*/               const SdrPage* pShownPage = pModel->GetPage(nPageNum);
/*N*/
/*N*/               if(pShownPage)
/*N*/               {
/*N*/                   if(pShownPage == pChangedPage)
/*N*/                   {
/*N*/                       if(eHint == HINT_OBJCHG || eHint == HINT_OBJLISTCLEARED)
/*N*/                       {
/*N*/                           // do nothing, else loop with HINT_OBJCHG cause
/*N*/                           // it can not be decided if hint comes from 21 lines
/*N*/                           // above (SendRepaintBroadcast())or normally from
/*N*/                           // object. Doing nothing leads to not updating
/*N*/                           // object moves on a 2nd opened view showing the page
/*N*/                           // as handout or notice page. (AW 06052000)
/*N*/                           //
/*N*/                           // one solution would be to invalidate without using
/*N*/                           // SendRepaintBroadcast(), so I made some tries, but it
/*N*/                           // did'nt work:
/*N*/                           //
/*N*/                           //SdrHint aHint(*this);
/*N*/                           //aHint.SetNeedRepaint(TRUE);
/*N*/                           //aHint.SetKind(HINT_PAGECHG);
/*N*/                           //pModel->Broadcast(aHint);
/*N*/                           //SdrPageView* pPV;
/*N*/                           //if(pModel && (pPV = pModel->GetPaintingPageView()))
/*N*/                           //{
/*N*/                           //  pPV->InvalidateAllWin(pSdrHint->GetRect(), TRUE);
/*N*/                           //}
/*N*/                           // GetPageView(pChangedPage);
/*N*/                           // SdrPageView::InvalidateAllWin(pSdrHint->GetRect(), TRUE);
/*N*/                       }
/*N*/                       else
/*N*/                       {
/*N*/                           // send normal
/*N*/                           SendRepaintBroadcast();
/*N*/                       }
/*N*/                   }
/*N*/                   else if(pChangedPage->IsMasterPage())
/*N*/                   {
/*N*/                       UINT16 nMaPgAnz = pShownPage->GetMasterPageCount();
/*N*/                       BOOL bDone(FALSE);
/*N*/
/*N*/                       for(UINT16 i=0; i<nMaPgAnz && !bDone; i++)
/*N*/                       {
/*N*/                           const SdrPage* pMaster = pShownPage->GetMasterPage(i);
/*N*/
/*N*/                           if(pMaster == pChangedPage)
/*N*/                           {
/*N*/                               if(eHint == HINT_OBJCHG || eHint == HINT_OBJLISTCLEARED)
/*N*/                               {
/*N*/                                   // see comment above...
/*N*/                               }
/*N*/                               else
/*N*/                               {
/*N*/                                   // send normal
/*N*/                                   SendRepaintBroadcast();
/*N*/                                   bDone = TRUE;
/*N*/                               }
/*N*/                           }
/*N*/                       }
/*N*/                   }
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }


/*N*/ void SdrPageObj::SetModel(SdrModel* pNewModel)
/*N*/ {
/*N*/   SdrModel* pOldMod=pModel;
/*N*/   SdrObject::SetModel(pNewModel);
/*N*/   if (pModel!=pOldMod) {
/*N*/       if (pOldMod!=NULL) EndListening(*pOldMod);
/*N*/       if (pModel!=NULL) StartListening(*pModel);
/*N*/   }
/*N*/ }


/*N*/ UINT16 SdrPageObj::GetObjIdentifier() const
/*N*/ {
/*N*/   return UINT16(OBJ_PAGE);
/*N*/ }


//STRIP001 void SdrPageObj::TakeObjInfo(SdrObjTransformInfoRec& rInfo) const
//STRIP001 {
//STRIP001  rInfo.bRotateFreeAllowed=FALSE;
//STRIP001  rInfo.bRotate90Allowed  =FALSE;
//STRIP001  rInfo.bMirrorFreeAllowed=FALSE;
//STRIP001  rInfo.bMirror45Allowed  =FALSE;
//STRIP001  rInfo.bMirror90Allowed  =FALSE;
//STRIP001  rInfo.bTransparenceAllowed = FALSE;
//STRIP001  rInfo.bGradientAllowed = FALSE;
//STRIP001  rInfo.bShearAllowed     =FALSE;
//STRIP001  rInfo.bEdgeRadiusAllowed=FALSE;
//STRIP001  rInfo.bNoOrthoDesired   =FALSE;
//STRIP001  rInfo.bCanConvToPath    =FALSE;
//STRIP001  rInfo.bCanConvToPoly    =FALSE;
//STRIP001  rInfo.bCanConvToPathLineToArea=FALSE;
//STRIP001  rInfo.bCanConvToPolyLineToArea=FALSE;
//STRIP001 }

//STRIP001 FASTBOOL SdrPageObj::Paint(ExtOutputDevice& rXOut, const SdrPaintInfoRec& rInfoRec) const
//STRIP001 {
//STRIP001  // Hidden objects on masterpages, draw nothing
//STRIP001  if((rInfoRec.nPaintMode & SDRPAINTMODE_MASTERPAGE) && bNotVisibleAsMaster)
//STRIP001      return TRUE;
//STRIP001
//STRIP001  Color aBackgroundColor( 0xffffff );
//STRIP001
//STRIP001  SdrPageView* pPV = NULL;
//STRIP001  if( pModel && ( pPV = pModel->GetPaintingPageView() ) )
//STRIP001      pPV->SetPaintingPageObj( (SdrPageObj*) this );
//STRIP001
//STRIP001  FASTBOOL bOk=TRUE;
//STRIP001  SdrPage* pMainPage= pModel==NULL ? NULL : pModel->GetPage(nPageNum);
//STRIP001  FASTBOOL bWindow    =rXOut.GetOutDev()->GetOutDevType()==OUTDEV_WINDOW;
//STRIP001  FASTBOOL bPrinter   =rXOut.GetOutDev()->GetOutDevType()==OUTDEV_PRINTER;
//STRIP001  FASTBOOL bPageValid =pMainPage!=NULL;
//STRIP001  FASTBOOL bPaintArea =bPainting && bPageValid; // Grau fuellen, wenn Rekursion
//STRIP001  FASTBOOL bPaintFrame=bPaintArea || bWindow || bPageValid; // Nur auf dem Drucker bei ungueltiter PageNum kein Rahmen Zeichnen
//STRIP001  FASTBOOL bPaintObjs =!bPainting && bPageValid;
//STRIP001
//STRIP001  if(bPaintArea)
//STRIP001  {
//STRIP001      OutputDevice& rOut=*rXOut.GetOutDev();
//STRIP001         svtools::ColorConfig aColorConfig;
//STRIP001         svtools::ColorConfigValue aDocColor( aColorConfig.GetColorValue( svtools::DOCCOLOR ) );
//STRIP001         svtools::ColorConfigValue aBorderColor( aColorConfig.GetColorValue( svtools::DOCBOUNDARIES ) );
//STRIP001
//STRIP001      rOut.SetFillColor( aDocColor.nColor );
//STRIP001      rOut.SetLineColor( aBorderColor.bIsVisible ? aBorderColor.nColor: aDocColor.nColor );
//STRIP001      rOut.DrawRect(aOutRect);
//STRIP001  }
//STRIP001
//STRIP001  if(bPaintObjs)
//STRIP001  {
//STRIP001      // Casten auf nonconst. Flag setzen um Rekursion zu erkennen, wenn
//STRIP001      // naemlich das PageObj auf der Seite sitzt, die es anzeigen soll
//STRIP001      // oder auf einer MasterPage dieser Seite, ...
//STRIP001      ((SdrPageObj*)this)->bPainting=TRUE;
//STRIP001      if (pModel!=NULL) {
//STRIP001          SdrPage* pMainPage=pModel->GetPage(nPageNum);
//STRIP001
//STRIP001          if( pPV && pMainPage )
//STRIP001          {
//STRIP001              SdrOutliner& rOutl=pModel->GetDrawOutliner(NULL);
//STRIP001              aBackgroundColor = rOutl.GetBackgroundColor();
//STRIP001
//STRIP001              rOutl.SetBackgroundColor( pMainPage->GetBackgroundColor(pPV) );
//STRIP001          }
//STRIP001
//STRIP001          if (pMainPage!=NULL) {
//STRIP001              // Checken, ob das setzen eines Clippings erforderlich ist
//STRIP001              Rectangle aPageRect(0,0,pMainPage->GetWdt(),pMainPage->GetHgt());
//STRIP001              FASTBOOL bClipIt=!aPageRect.IsInside(pMainPage->GetAllObjBoundRect());
//STRIP001              if (!bClipIt) { // MasterPages auch checken
//STRIP001                  USHORT nMaPgAnz=pMainPage->GetMasterPageCount();
//STRIP001                  for (USHORT i=0; i<nMaPgAnz && !bClipIt; i++) {
//STRIP001                      SdrPage* pPg=pMainPage->GetMasterPage(i);
//STRIP001                      bClipIt=!aPageRect.IsInside(pPg->GetAllObjBoundRect());
//STRIP001                  }
//STRIP001              }
//STRIP001              FASTBOOL bClip0=FALSE;
//STRIP001              Region aClip0;
//STRIP001              if (bClipIt) {
//STRIP001                  // Hier koennte ich mal noch einbauen, dass eine eventuelle
//STRIP001                  // Metafileaufzeichnung pausiert wird, damit keine
//STRIP001                  // SetClipRegion-Actions erzeugt werden.
//STRIP001                  bClip0=rXOut.GetOutDev()->IsClipRegion();
//STRIP001                  aClip0=rXOut.GetOutDev()->GetClipRegion();
//STRIP001              }
//STRIP001 #ifndef NORELMAPMODE
//STRIP001              Point aZero;
//STRIP001              Fraction aFact1(1,1);
//STRIP001              Point aOfs(aOutRect.TopLeft());
//STRIP001              rXOut.GetOutDev()->SetMapMode(MapMode(MAP_RELATIVE,aOfs,aFact1,aFact1));
//STRIP001              long nXMul=aOutRect.GetWidth();     // SJ: #99149# fixed problem with
//STRIP001              long nYMul=aOutRect.GetHeight();    // one pixel wide preview objects
//STRIP001              long nXDiv=pMainPage->GetWdt();
//STRIP001              long nYDiv=pMainPage->GetHgt();
//STRIP001              Fraction aXScl(nXMul,nXDiv);
//STRIP001              Fraction aYScl(nYMul,nYDiv);
//STRIP001              // nun auf 10 Binaerstellen kuerzen (ca. 3 Dezimalstellen). Joe, 01-12-1995, BugId 21483
//STRIP001              Kuerzen(aXScl,10); // auf 7 Binaerstellen Kuerzen = ca. 2 Dezimalstellen
//STRIP001              Kuerzen(aYScl,10); // auf 7 Binaerstellen Kuerzen = ca. 2 Dezimalstellen
//STRIP001              nXMul=aXScl.GetNumerator();
//STRIP001              nXDiv=aXScl.GetDenominator();
//STRIP001              nYMul=aYScl.GetNumerator();
//STRIP001              nYDiv=aYScl.GetDenominator();
//STRIP001              rXOut.GetOutDev()->SetMapMode(MapMode(MAP_RELATIVE,aZero,aXScl,aYScl));
//STRIP001 #else
//STRIP001              MapMode aMapMerk(rXOut.GetOutDev()->GetMapMode());
//STRIP001              MapMode aMapNeu(aMapMerk);
//STRIP001              Point aOrg(aMapNeu.GetOrigin());
//STRIP001              Fraction aSclx(aMapNeu.GetScaleX());
//STRIP001              Fraction aScly(aMapNeu.GetScaleY());
//STRIP001              Point aOfs(aOutRect.TopLeft());
//STRIP001              aOrg+=aOfs;
//STRIP001              ResizePoint(aOrg,Point(),Fraction(pMainPage->GetWdt(),aOutRect.GetWidth()),
//STRIP001                                       Fraction(pMainPage->GetHgt(),aOutRect.GetHeight()));
//STRIP001              aSclx*=Fraction(aOutRect.GetWidth(),pMainPage->GetWdt());
//STRIP001              aScly*=Fraction(aOutRect.GetHeight(),pMainPage->GetHgt());
//STRIP001              // nun auf 10 Binaerstellen kuerzen (ca. 3 Dezimalstellen). Joe, 01-12-1995, BugId 21483
//STRIP001              Kuerzen(aSclx,10); // auf 7 Binaerstellen Kuerzen = ca. 2 Dezimalstellen
//STRIP001              Kuerzen(aScly,10); // auf 7 Binaerstellen Kuerzen = ca. 2 Dezimalstellen
//STRIP001              aMapNeu.SetOrigin(aOrg);
//STRIP001              aMapNeu.SetScaleX(aSclx);
//STRIP001              aMapNeu.SetScaleY(aScly);
//STRIP001              rXOut.GetOutDev()->SetMapMode(aMapNeu);
//STRIP001 #endif
//STRIP001              if (bClipIt) {
//STRIP001                  // Hier koennte ich mal noch einbauen, dass eine eventuelle
//STRIP001                  // Metafileaufzeichnung pausiert wird, damit keine
//STRIP001                  // SetClipRegion-Actions erzeugt werden.
//STRIP001                  rXOut.GetOutDev()->IntersectClipRegion(aPageRect);
//STRIP001              }
//STRIP001              SdrPaintInfoRec aInfoRec(rInfoRec);
//STRIP001              aInfoRec.aCheckRect=Rectangle(); // alles Malen!
//STRIP001              USHORT nMaPgAnz=pMainPage->GetMasterPageCount();
//STRIP001              USHORT i=0;
//STRIP001              do {
//STRIP001                  aInfoRec.nPaintMode=rInfoRec.nPaintMode & ~SDRPAINTMODE_MASTERPAGE;
//STRIP001                  aInfoRec.nPaintMode&=~SDRPAINTMODE_GLUEPOINTS;
//STRIP001                  aInfoRec.nPaintMode|=SDRPAINTMODE_ANILIKEPRN;
//STRIP001                  SdrPage* pPg;
//STRIP001                  const SetOfByte* pMLayers=NULL;
//STRIP001                  if (i<nMaPgAnz) {
//STRIP001                      pPg=pMainPage->GetMasterPage(i);
//STRIP001                      pMLayers=&pMainPage->GetMasterPageVisibleLayers(i);
//STRIP001                      aInfoRec.nPaintMode|=SDRPAINTMODE_MASTERPAGE;
//STRIP001                  }
//STRIP001                  else
//STRIP001                      pPg=pMainPage;
//STRIP001
//STRIP001                  i++;
//STRIP001                  if (pPg!=NULL)
//STRIP001                  {   // ansonsten evtl. ungueltige Masterpage
//STRIP001                      ULONG nObjAnz=pPg->GetObjCount();
//STRIP001                      for ( ULONG i=0; i<nObjAnz; i++ )
//STRIP001                      {
//STRIP001                          if( i == 0 && pPg->IsMasterPage() && pMainPage->GetBackgroundObj() )
//STRIP001                          {
//STRIP001                              SdrObject* pBackgroundObj = pMainPage->GetBackgroundObj();
//STRIP001                              if( pBackgroundObj->GetLogicRect() != aPageRect )
//STRIP001                              {
//STRIP001                                  pBackgroundObj->SetLogicRect( aPageRect );
//STRIP001                                  pBackgroundObj->RecalcBoundRect();
//STRIP001                              }
//STRIP001                              pBackgroundObj->Paint( rXOut, aInfoRec );
//STRIP001                          }
//STRIP001                          else
//STRIP001                          {
//STRIP001                              SdrObject* pObj=pPg->GetObj(i);
//STRIP001                              const Rectangle& rBoundRect=pObj->GetBoundRect();
//STRIP001                              if (rInfoRec.aPaintLayer.IsSet(pObj->GetLayer()) &&        // Layer des Obj nicht sichtbar
//STRIP001                                  (pMLayers==NULL || pMLayers->IsSet(pObj->GetLayer()))) // MasterPageLayer visible
//STRIP001                              {
//STRIP001                                   pObj->Paint(rXOut,aInfoRec);
//STRIP001                              }
//STRIP001                          }
//STRIP001                      }
//STRIP001                  }
//STRIP001              } while (i<=nMaPgAnz);
//STRIP001 #ifndef NORELMAPMODE
//STRIP001              rXOut.GetOutDev()->SetMapMode(MapMode(MAP_RELATIVE,aZero,Fraction(nXDiv,nXMul),Fraction(nYDiv,nYMul)));
//STRIP001              aOfs.X()=-aOfs.X();
//STRIP001              aOfs.Y()=-aOfs.Y();
//STRIP001              rXOut.GetOutDev()->SetMapMode(MapMode(MAP_RELATIVE,aOfs,aFact1,aFact1));
//STRIP001 #else
//STRIP001              rXOut.GetOutDev()->SetMapMode(aMapMerk);
//STRIP001 #endif
//STRIP001              if (bClipIt) {
//STRIP001                  if (bClip0) rXOut.GetOutDev()->SetClipRegion(aClip0);
//STRIP001                  else rXOut.GetOutDev()->SetClipRegion();
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      // IsInPainting-Flag zuruecksetzen
//STRIP001      ((SdrPageObj*)this)->bPainting=FALSE;
//STRIP001  }
//STRIP001
//STRIP001  if(bPaintFrame)
//STRIP001  {
//STRIP001         svtools::ColorConfig aColorConfig;
//STRIP001         svtools::ColorConfigValue aColor( aColorConfig.GetColorValue( svtools::OBJECTBOUNDARIES ) );
//STRIP001
//STRIP001      if( aColor.bIsVisible )
//STRIP001      {
//STRIP001          OutputDevice& rOut=*rXOut.GetOutDev();
//STRIP001          rOut.SetFillColor();
//STRIP001          rOut.SetLineColor( aColor.nColor );
//STRIP001          rOut.DrawRect(aOutRect);
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if (bOk && (rInfoRec.nPaintMode & SDRPAINTMODE_GLUEPOINTS) !=0) {
//STRIP001      bOk=PaintGluePoints(rXOut,rInfoRec);
//STRIP001  }
//STRIP001
//STRIP001  if( pPV )
//STRIP001  {
//STRIP001      pPV->SetPaintingPageObj( NULL );
//STRIP001
//STRIP001      SdrPage* pPage = pPV->GetPage();
//STRIP001      if( pPage )
//STRIP001      {
//STRIP001          SdrOutliner& rOutl=pModel->GetDrawOutliner(NULL);
//STRIP001          rOutl.SetBackgroundColor( aBackgroundColor );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001
//STRIP001  return bOk;
//STRIP001 }


//STRIP001 void SdrPageObj::operator=(const SdrObject& rObj)
//STRIP001 {
//STRIP001  SdrObject::operator=(rObj);
//STRIP001  nPageNum=((const SdrPageObj&)rObj).nPageNum;
//STRIP001 }


//STRIP001 void SdrPageObj::TakeObjNameSingul(XubString& rName) const
//STRIP001 {
//STRIP001  rName=ImpGetResStr(STR_ObjNameSingulPAGE);
//STRIP001
//STRIP001  String aName( GetName() );
//STRIP001  if(aName.Len())
//STRIP001  {
//STRIP001      rName += sal_Unicode(' ');
//STRIP001      rName += sal_Unicode('\'');
//STRIP001      rName += aName;
//STRIP001      rName += sal_Unicode('\'');
//STRIP001  }
//STRIP001 }


//STRIP001 void SdrPageObj::TakeObjNamePlural(XubString& rName) const
//STRIP001 {
//STRIP001  rName=ImpGetResStr(STR_ObjNamePluralPAGE);
//STRIP001 }


/*N*/ const Rectangle& SdrPageObj::GetBoundRect() const
/*N*/ {
/*N*/   return SdrObject::GetBoundRect();
/*N*/ }


/*N*/ const Rectangle& SdrPageObj::GetSnapRect() const
/*N*/ {
/*N*/   return SdrObject::GetSnapRect();
/*N*/ }


/*N*/ const Rectangle& SdrPageObj::GetLogicRect() const
/*N*/ {
/*N*/   return SdrObject::GetLogicRect();
/*N*/ }


/*N*/ void SdrPageObj::NbcSetSnapRect(const Rectangle& rRect)
/*N*/ {
/*N*/   SdrObject::NbcSetSnapRect(rRect);
/*N*/ }


/*N*/ void SdrPageObj::NbcSetLogicRect(const Rectangle& rRect)
/*N*/ {
/*N*/   SdrObject::NbcSetLogicRect(rRect);
/*N*/ }


//STRIP001 void SdrPageObj::TakeXorPoly(XPolyPolygon& rPoly, FASTBOOL bDetail) const
//STRIP001 {
//STRIP001  SdrObject::TakeXorPoly(rPoly,bDetail);
//STRIP001 }

//STRIP001 void SdrPageObj::TakeContour(XPolyPolygon& rXPoly, SdrContourType eType) const
//STRIP001 {
//STRIP001 }


/*N*/ void SdrPageObj::WriteData(SvStream& rOut) const
/*N*/ {
/*N*/   SdrObject::WriteData(rOut);
/*N*/   SdrDownCompat aCompat(rOut,STREAM_WRITE); // Fuer Abwaertskompatibilitaet (Lesen neuer Daten mit altem Code)
/*N*/ #ifdef DBG_UTIL
/*N*/   aCompat.SetID("SdrPageObj");
/*N*/ #endif
/*N*/   rOut<<nPageNum;
/*N*/ }

/*N*/ void SdrPageObj::ReadData(const SdrObjIOHeader& rHead, SvStream& rIn)
/*N*/ {
/*N*/   if (rIn.GetError()!=0) return;
/*N*/   SdrObject::ReadData(rHead,rIn);
/*N*/   SdrDownCompat aCompat(rIn,STREAM_READ); // Fuer Abwaertskompatibilitaet (Lesen neuer Daten mit altem Code)
/*N*/ #ifdef DBG_UTIL
/*N*/   aCompat.SetID("SdrPageObj");
/*N*/ #endif
/*N*/   rIn>>nPageNum;
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////


