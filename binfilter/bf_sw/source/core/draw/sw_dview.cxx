/*************************************************************************
 *
 *  $RCSfile: sw_dview.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 17:18:55 $
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

#include "hintids.hxx"

// auto strip #ifndef _SVX_PROTITEM_HXX //autogen
// auto strip #include <bf_svx/protitem.hxx>
// auto strip #endif
// auto strip #ifndef _SVDPAGV_HXX //autogen
// auto strip #include <bf_svx/svdpagv.hxx>
// auto strip #endif
// auto strip #ifndef _FM_FMMODEL_HXX
// auto strip #include <bf_svx/fmmodel.hxx>
// auto strip #endif
// auto strip #ifndef _IPOBJ_HXX //autogen
// auto strip #include <so3/ipobj.hxx>
// auto strip #endif


// auto strip #include "swtypes.hxx"
// auto strip #include "pagefrm.hxx"
// auto strip #include "rootfrm.hxx"
// auto strip #include "cntfrm.hxx"

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

// auto strip #include "flyfrm.hxx"
#include "frmfmt.hxx"
// auto strip #include "dflyobj.hxx"
#include "dcontact.hxx"
// auto strip #include "frmatr.hxx"
#include "viewsh.hxx"
#include "viewimp.hxx"
#include "dview.hxx"
// auto strip #include "dpage.hxx"
// auto strip #include "doc.hxx"
// auto strip #include "mdiexp.hxx"

// auto strip #ifndef _NDOLE_HXX //autogen
// auto strip #include <ndole.hxx>
// auto strip #endif
#ifndef _FMTANCHR_HXX //autogen
#include <fmtanchr.hxx>
#endif
// auto strip #include "shellres.hxx"

// #i7672#
// auto strip #ifndef _OUTLINER_HXX //autogen
// auto strip #include <bf_svx/outliner.hxx>
// auto strip #endif

// OD 18.06.2003 #108784#
// auto strip #ifndef _SVDVMARK_HXX //autogen
// auto strip #include <bf_svx/svdvmark.hxx>
// auto strip #endif
#include <vector>
namespace binfilter {

class SwSdrHdl : public SdrHdl
{
public:
    SwSdrHdl(const Point& rPnt, bool bTopRight ) :
        SdrHdl( rPnt, bTopRight ? HDL_ANCHOR_TR : HDL_ANCHOR ) {}
//STRIP001     virtual BOOL IsFocusHdl() const;
};

//STRIP001 BOOL SwSdrHdl::IsFocusHdl() const
//STRIP001 {
//STRIP001     if( HDL_ANCHOR == eKind || HDL_ANCHOR_TR == eKind )
//STRIP001         return TRUE;
//STRIP001     return SdrHdl::IsFocusHdl();
//STRIP001 }

//STRIP001 const SwFrm *lcl_FindAnchor( const SdrObject *pObj, FASTBOOL bAll )
//STRIP001 {
//STRIP001  const SwVirtFlyDrawObj *pVirt = pObj->IsWriterFlyFrame() ?
//STRIP001                                          (SwVirtFlyDrawObj*)pObj : 0;
//STRIP001  if ( pVirt )
//STRIP001  {
//STRIP001      if ( bAll || !pVirt->GetFlyFrm()->IsFlyInCntFrm() )
//STRIP001          return pVirt->GetFlyFrm()->GetAnchor();
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      const SwDrawContact *pCont = (const SwDrawContact*)GetUserCall(pObj);
//STRIP001      if ( pCont )
//STRIP001          return pCont->GetAnchor();
//STRIP001  }
//STRIP001  return 0;
//STRIP001 }

/*************************************************************************
|*
|*  SwDrawView::Ctor
|*
|*  Ersterstellung      OK 18.11.94
|*  Letzte Aenderung    MA 22. Jul. 96
|*
*************************************************************************/



/*N*/ SwDrawView::SwDrawView( SwViewImp &rI, SdrModel *pMd, OutputDevice *pOutDev) :
/*N*/   FmFormView( (FmFormModel*)pMd, pOutDev ),
/*N*/   rImp( rI )
/*N*/ {
/*N*/   SetPageVisible( FALSE );
/*N*/   SetBordVisible( FALSE );
/*N*/   SetGridVisible( FALSE );
/*N*/   SetHlplVisible( FALSE );
/*N*/   SetGlueVisible( FALSE );
/*N*/   SetFrameDragSingles( TRUE );
/*N*/   SetVirtualObjectBundling( TRUE );
/*N*/   SetSwapAsynchron( TRUE );
/*N*/
/*N*/   EnableExtendedKeyInputDispatcher( FALSE );
/*N*/   EnableExtendedMouseEventDispatcher( FALSE );
/*N*/   EnableExtendedCommandEventDispatcher( FALSE );
/*N*/
/*N*/   SetHitTolerancePixel( GetMarkHdlSizePixel()/2 );
/*N*/
/*N*/   SetPrintPreview( rI.GetShell()->IsPreView() );
/*N*/ }

/*************************************************************************
|*
|*  SwDrawView::AddCustomHdl()
|*
|*  Gets called every time the handles need to be build
|*
|*  Ersterstellung      AW 06. Sep. 99
|*  Letzte Aenderung    AW 06. Sep. 99
|*
*************************************************************************/

/*M*/ void SwDrawView::AddCustomHdl()
/*M*/ {
/*M*/   const SdrMarkList &rMrkList = GetMarkList();
/*M*/
/*M*/   if(rMrkList.GetMarkCount() != 1 || !GetUserCall(rMrkList.GetMark( 0 )->GetObj()))
/*M*/       return;
/*M*/
/*?*/   SdrObject *pObj = rMrkList.GetMark(0)->GetObj();
/*?*/   const SwFmtAnchor &rAnchor = ::binfilter::FindFrmFmt(pObj)->GetAnchor();
/*?*/
/*?*/   if(FLY_IN_CNTNT == rAnchor.GetAnchorId())
/*?*/       return;
/*?*/ DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/    const SwFrm* pAnch;
//STRIP001 /*?*/    if(0 == (pAnch = CalcAnchor()))
//STRIP001 /*?*/        return;
//STRIP001 /*?*/
//STRIP001 /*?*/    ViewShell &rSh = *Imp().GetShell();
//STRIP001 /*?*/    Point aPos(aAnchorPoint);
//STRIP001 /*?*/
//STRIP001 /*?*/    if(FLY_AUTO_CNTNT == rAnchor.GetAnchorId())
//STRIP001 /*?*/    {
//STRIP001 /*?*/        SwRect aAutoPos;
//STRIP001 /*?*/        pAnch->GetCharRect(aAutoPos, *rAnchor.GetCntntAnchor());
//STRIP001 /*?*/        aPos = aAutoPos.Pos();
//STRIP001 /*?*/    }
//STRIP001 /*?*/
//STRIP001 /*?*/    // add anchor handle:
//STRIP001 /*?*/     aHdl.AddHdl( new SwSdrHdl( aPos, pAnch->IsVertical() ||
//STRIP001 /*?*/                                      pAnch->IsRightToLeft() ) );
/*M*/ }

/*************************************************************************
|*
|*  SwDrawView::GetMaxToTopObj(), _GetMaxToTopObj()
|*
|*  Ersterstellung      MA 13. Jan. 95
|*  Letzte Aenderung    MA 18. Mar. 97
|*
*************************************************************************/


//STRIP001 SdrObject* SwDrawView::GetMaxToTopObj( SdrObject* pObj ) const
//STRIP001 {
//STRIP001  if ( GetUserCall(pObj) )
//STRIP001  {
//STRIP001      const SwFrm *pAnch = ::lcl_FindAnchor( pObj, FALSE );
//STRIP001      if ( pAnch )
//STRIP001      {
//STRIP001          //Das oberste Obj innerhalb des Ankers darf nicht ueberholt
//STRIP001          //werden.
//STRIP001          const SwFlyFrm *pFly = pAnch->FindFlyFrm();
//STRIP001          if ( pFly )
//STRIP001          {
//STRIP001              const SwPageFrm *pPage = pFly->FindPageFrm();
//STRIP001              if ( pPage->GetSortedObjs() )
//STRIP001              {
//STRIP001                  UINT32 nOrdNum = 0;
//STRIP001                  for ( USHORT i = 0; i < pPage->GetSortedObjs()->Count(); ++i )
//STRIP001                  {
//STRIP001                      const SdrObject *pO = (*pPage->GetSortedObjs())[i];
//STRIP001
//STRIP001                      if ( pO->GetOrdNumDirect() > nOrdNum )
//STRIP001                      {
//STRIP001                          const SwFrm *pAnch = ::lcl_FindAnchor( pO, FALSE );
//STRIP001                          if ( pFly->IsAnLower( pAnch ) )
//STRIP001                          {
//STRIP001                              nOrdNum = pO->GetOrdNumDirect();
//STRIP001                          }
//STRIP001                      }
//STRIP001                  }
//STRIP001                  if ( nOrdNum )
//STRIP001                  {
//STRIP001                      SdrPage *pPage = GetModel()->GetPage( 0 );
//STRIP001                      ++nOrdNum;
//STRIP001                      if ( nOrdNum < pPage->GetObjCount() )
//STRIP001                      {
//STRIP001                          return pPage->GetObj( nOrdNum );
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return 0;
//STRIP001 }

/*************************************************************************
|*
|*  SwDrawView::GetMaxToBtmObj()
|*
|*  Ersterstellung      MA 13. Jan. 95
|*  Letzte Aenderung    MA 05. Sep. 96
|*
*************************************************************************/


//STRIP001 SdrObject* SwDrawView::GetMaxToBtmObj(SdrObject* pObj) const
//STRIP001 {
//STRIP001  if ( GetUserCall(pObj) )
//STRIP001  {
//STRIP001      const SwFrm *pAnch = ::lcl_FindAnchor( pObj, FALSE );
//STRIP001      if ( pAnch )
//STRIP001      {
//STRIP001          //Der Fly des Ankers darf nicht "unterflogen" werden.
//STRIP001          const SwFlyFrm *pFly = pAnch->FindFlyFrm();
//STRIP001          if ( pFly )
//STRIP001          {
//STRIP001              SdrObject *pRet = (SdrObject*)pFly->GetVirtDrawObj();
//STRIP001              return pRet != pObj ? pRet : 0;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return 0;
//STRIP001 }

/*************************************************************************
|*
|*  SwDrawView::ObjOrderChanged()
|*
|*  Ersterstellung      MA 31. Jul. 95
|*  Letzte Aenderung    MA 18. Mar. 97
|*
*************************************************************************/

//STRIP001 inline BOOL lcl_IsChild( SdrObject *pParent, SdrObject *pChild )
//STRIP001 {
//STRIP001  if ( pParent->IsWriterFlyFrame() )
//STRIP001  {
//STRIP001      const SwFrm *pAnch = lcl_FindAnchor( pChild, FALSE );
//STRIP001      if ( pAnch && ((SwVirtFlyDrawObj*)pParent)->GetFlyFrm()->IsAnLower( pAnch ))
//STRIP001      {
//STRIP001          return TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  return FALSE;
//STRIP001 }

//STRIP001 inline SdrObject *lcl_FindParent( SdrObject *pObj )
//STRIP001 {
//STRIP001  const SwFrm *pAnch = lcl_FindAnchor( pObj, FALSE );
//STRIP001  if ( pAnch && pAnch->IsInFly() )
//STRIP001      return (SdrObject*)pAnch->FindFlyFrm()->GetVirtDrawObj();
//STRIP001  return 0;
//STRIP001 }



//STRIP001 void SwDrawView::ObjOrderChanged( SdrObject* pObj, ULONG nOldPos,
//STRIP001                                        ULONG nNewPos )
//STRIP001 {
//STRIP001  SdrPage *pPg = GetModel()->GetPage( 0 );
//STRIP001  if ( pPg->IsObjOrdNumsDirty() )
//STRIP001      pPg->RecalcObjOrdNums();
//STRIP001  const BOOL bBtm = nOldPos > nNewPos;
//STRIP001  ULONG nMoveTo = ULONG_MAX;
//STRIP001
//STRIP001  //Wenn ein Object nach oben geschoben werden soll, so muss es wenigstens
//STRIP001  //seine Kinder plus einem ueberspringen.
//STRIP001  if ( !bBtm && nNewPos < pPg->GetObjCount() - 1 )
//STRIP001  {
//STRIP001      ULONG nPos = nOldPos;
//STRIP001      SdrObject *pTmp = pPg->GetObj( nPos );
//STRIP001      while ( pTmp == pObj || lcl_IsChild( pObj, pTmp ) )
//STRIP001      {
//STRIP001          ++nPos;
//STRIP001          pTmp = pPg->GetObj( nPos );
//STRIP001      }
//STRIP001      if ( nPos > nNewPos )
//STRIP001          nMoveTo = nPos;
//STRIP001  }
//STRIP001  if ( nMoveTo != ULONG_MAX )
//STRIP001  {
//STRIP001      if ( nMoveTo <= nNewPos )
//STRIP001          ++nMoveTo;
//STRIP001      pPg->SetObjectOrdNum( nNewPos, nMoveTo );
//STRIP001      if ( pPg->IsObjOrdNumsDirty() )
//STRIP001          pPg->RecalcObjOrdNums();
//STRIP001      nNewPos = nMoveTo;
//STRIP001      nMoveTo = ULONG_MAX;
//STRIP001  }
//STRIP001
//STRIP001  //Kein Objekt darf in eine Schachtelung von Rahmen/Objekten eindringen,
//STRIP001  //die Kette muss ggf. uebersprungen werden.
//STRIP001  if ( bBtm )
//STRIP001  {
//STRIP001      if ( nNewPos > 0 )
//STRIP001      {
//STRIP001          SdrObject *pMax = GetMaxToBtmObj( pObj ),
//STRIP001                    *pO = pPg->GetObj( nNewPos + 1 ),
//STRIP001                    *pPre = pO;
//STRIP001          while ( pO && 0 != (pO = GetMaxToBtmObj( pO )))
//STRIP001          {
//STRIP001              if ( pO != pMax )
//STRIP001                  nMoveTo = pO->GetOrdNumDirect();
//STRIP001              if ( pO == pPre )
//STRIP001                  break;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if ( nNewPos < pPg->GetObjCount() - 1 )
//STRIP001      {
//STRIP001          ULONG nPos = nNewPos;
//STRIP001          SdrObject *pMyParent = lcl_FindParent( pObj ),
//STRIP001                    *pNxt      = pPg->GetObj( nPos + 1 ),
//STRIP001                    *pNxtParent= lcl_FindParent( pNxt );
//STRIP001          while ( pNxtParent && pNxtParent != pMyParent )
//STRIP001          {
//STRIP001              nMoveTo = ++nPos;
//STRIP001              if ( nPos < pPg->GetObjCount() - 1 )
//STRIP001              {
//STRIP001                  pNxt       = pPg->GetObj( nPos + 1 );
//STRIP001                  pNxtParent = lcl_FindParent( pNxt );
//STRIP001              }
//STRIP001              else
//STRIP001                  break;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  if ( nMoveTo != ULONG_MAX )
//STRIP001  {
//STRIP001      pPg->SetObjectOrdNum( nNewPos, nMoveTo );
//STRIP001      if ( pPg->IsObjOrdNumsDirty() )
//STRIP001          pPg->RecalcObjOrdNums();
//STRIP001      nNewPos = nMoveTo;
//STRIP001  }
//STRIP001
//STRIP001  if ( pObj->IsWriterFlyFrame() )
//STRIP001  {
//STRIP001      //Ein Rahmen wurde in seiner Order veraendert. Hier muss nachtraeglich
//STRIP001      //dafuer gesorgt werden, dass seine 'Kinder' nachgezogen werden.
//STRIP001      const SwFlyFrm *pFly = ((SwVirtFlyDrawObj*)pObj)->GetFlyFrm();
//STRIP001      if ( pPg->IsObjOrdNumsDirty() )
//STRIP001          pPg->RecalcObjOrdNums();
//STRIP001
//STRIP001 #ifdef ACCESSIBLE_LAYOUT
//STRIP001      rImp.DisposeAccessibleFrm( pFly );
//STRIP001      rImp.AddAccessibleFrm( pFly );
//STRIP001 #endif
//STRIP001
//STRIP001      if ( bBtm )
//STRIP001          ++nNewPos;
//STRIP001      BOOL bFound = FALSE;
//STRIP001      for ( ULONG i = nOldPos; i < pPg->GetObjCount(); ++i )
//STRIP001      {
//STRIP001          SdrObject *pO = pPg->GetObj( i );
//STRIP001          if ( pO == pObj )
//STRIP001              break;
//STRIP001          const SwFrm *pAnch;
//STRIP001          const BOOL bFly = pO->IsWriterFlyFrame();
//STRIP001          if ( bFly )
//STRIP001              pAnch = ((SwVirtFlyDrawObj*)pO)->GetFlyFrm()->GetAnchor();
//STRIP001          else
//STRIP001              pAnch = ((SwDrawContact*)GetUserCall(pO))->GetAnchor();
//STRIP001          const SwFlyFrm *pF = pAnch ? pAnch->FindFlyFrm() : NULL;
//STRIP001          if ( pF && (pF == pFly || pFly->IsUpperOf( pAnch->FindFlyFrm())))
//STRIP001          {
//STRIP001              //Kind gefunden, verschieben.
//STRIP001              pPg->SetObjectOrdNum( i, nNewPos );
//STRIP001              pPg->RecalcObjOrdNums();
//STRIP001              --i;    //keinen auslassen
//STRIP001 #ifdef ACCESSIBLE_LAYOUT
//STRIP001              if ( bFly )
//STRIP001              {
//STRIP001                  const SwFlyFrm *pFF =
//STRIP001                      static_cast< const SwVirtFlyDrawObj *>(pO)->GetFlyFrm();
//STRIP001                  rImp.DisposeAccessibleFrm( pFF );
//STRIP001                  rImp.AddAccessibleFrm( pFF );
//STRIP001              }
//STRIP001 #endif
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 #ifdef ACCESSIBLE_LAYOUT
//STRIP001  else
//STRIP001  {
//STRIP001      rImp.DisposeAccessibleObj( pObj );
//STRIP001      rImp.AddAccessibleObj( pObj );
//STRIP001  }
//STRIP001 #endif
//STRIP001 }

/*************************************************************************
|*
|*  SwDrawView::TakeDragLimit()
|*
|*  Ersterstellung      AMA 26. Apr. 96
|*  Letzte Aenderung    MA 03. May. 96
|*
*************************************************************************/


//STRIP001 BOOL SwDrawView::TakeDragLimit( SdrDragMode eMode,
//STRIP001                                          Rectangle& rRect ) const
//STRIP001 {
//STRIP001  const SdrMarkList &rMrkList = GetMarkList();
//STRIP001  BOOL bRet = FALSE;
//STRIP001  if( 1 == rMrkList.GetMarkCount() )
//STRIP001  {
//STRIP001      const SdrObject *pObj = rMrkList.GetMark( 0 )->GetObj();
//STRIP001      SwRect aRect;
//STRIP001      if( ::CalcClipRect( pObj, aRect, eMode == SDRDRAG_MOVE ) )
//STRIP001      {
//STRIP001          rRect = aRect.SVRect();
//STRIP001          bRet = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

/*************************************************************************
|*
|*  SwDrawView::CalcAnchor()
|*
|*  Ersterstellung      MA 13. Jan. 95
|*  Letzte Aenderung    MA 08. Nov. 96
|*
*************************************************************************/


//STRIP001 const SwFrm *SwDrawView::CalcAnchor()
//STRIP001 {
//STRIP001  const SdrMarkList &rMrkList = GetMarkList();
//STRIP001  if ( rMrkList.GetMarkCount() != 1 )
//STRIP001      return NULL;
//STRIP001
//STRIP001     SdrObject* pObj = rMrkList.GetMark( 0 )->GetObj();
//STRIP001
//STRIP001  //Fuer Absatzgebundene Objekte suchen, andernfalls einfach nur
//STRIP001  //der aktuelle Anker. Nur suchen wenn wir gerade draggen.
//STRIP001  const SwFrm *pAnch;
//STRIP001     Rectangle aMyRect;
//STRIP001  const BOOL bFly = pObj->IsWriterFlyFrame();
//STRIP001  if ( bFly )
//STRIP001  {
//STRIP001      pAnch = ((SwVirtFlyDrawObj*)pObj)->GetFlyFrm()->GetAnchor();
//STRIP001         aMyRect = ((SwVirtFlyDrawObj*)pObj)->GetFlyFrm()->Frm().SVRect();
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001         SwDrawContact *pC = (SwDrawContact*)GetUserCall(pObj);
//STRIP001         // OD 17.06.2003 #108784# - determine correct anchor position for
//STRIP001         // 'virtual' drawing objects.
//STRIP001         if ( pObj->ISA(SwDrawVirtObj) )
//STRIP001         {
//STRIP001             pAnch = static_cast<SwDrawVirtObj*>(pObj)->GetAnchorFrm();
//STRIP001         }
//STRIP001         else
//STRIP001         {
//STRIP001             pAnch = pC->GetAnchor();
//STRIP001         }
//STRIP001      if( !pAnch )
//STRIP001      {
//STRIP001          pC->ConnectToLayout();
//STRIP001             // OD 17.06.2003 #108784# - determine correct anchor position for
//STRIP001             // 'virtual' drawing objects.
//STRIP001             if ( pObj->ISA(SwDrawVirtObj) )
//STRIP001             {
//STRIP001                 pAnch = static_cast<SwDrawVirtObj*>(pObj)->GetAnchorFrm();
//STRIP001             }
//STRIP001             else
//STRIP001             {
//STRIP001                 pAnch = pC->GetAnchor();
//STRIP001             }
//STRIP001      }
//STRIP001         aMyRect = pObj->GetSnapRect();
//STRIP001  }
//STRIP001
//STRIP001     const sal_Bool bTopRight = pAnch && ( pAnch->IsVertical() ||
//STRIP001                                           pAnch->IsRightToLeft() );
//STRIP001
//STRIP001     const Point aMyPt = bTopRight ? aMyRect.TopRight() : aMyRect.TopLeft();
//STRIP001
//STRIP001     Point aPt;
//STRIP001     if ( IsAction() )
//STRIP001     {
//STRIP001         if ( !TakeDragObjAnchorPos( aPt, bTopRight ) )
//STRIP001             return NULL;
//STRIP001     }
//STRIP001     else
//STRIP001     {
//STRIP001         Rectangle aRect = pObj->GetSnapRect();
//STRIP001         aPt = bTopRight ? aRect.TopRight() : aRect.TopLeft();
//STRIP001     }
//STRIP001
//STRIP001     if ( aPt != aMyPt )
//STRIP001  {
//STRIP001      if ( pAnch->IsCntntFrm() )
//STRIP001         {
//STRIP001             // OD 26.06.2003 #108784# - allow drawing objects in header/footer,
//STRIP001             // but exclude control objects.
//STRIP001             bool bBodyOnly = CheckControlLayer( pObj );
//STRIP001             pAnch = ::FindAnchor( (SwCntntFrm*)pAnch, aPt, bBodyOnly );
//STRIP001         }
//STRIP001      else if ( !bFly )
//STRIP001         {
//STRIP001             const SwRect aRect( aPt.X(), aPt.Y(), 1, 1 );
//STRIP001
//STRIP001             SwDrawContact* pContact = (SwDrawContact*)GetUserCall(pObj);
//STRIP001          if( pContact->GetAnchor() && pContact->GetAnchor()->IsPageFrm() )
//STRIP001              pAnch = pContact->GetPage();
//STRIP001          else
//STRIP001              pAnch = pContact->FindPage( aRect );
//STRIP001      }
//STRIP001  }
//STRIP001  if( pAnch && !pAnch->IsProtected() )
//STRIP001         aAnchorPoint = pAnch->GetFrmAnchorPos( ::HasWrap( pObj ) );
//STRIP001  else
//STRIP001      pAnch = 0;
//STRIP001  return pAnch;
//STRIP001 }


//STRIP001 Rectangle *SwDrawView::IsAnchorAtPos( const Point &rPt ) const
//STRIP001 {
//STRIP001  SdrHdl* pHdl = aHdl.GetHdl(HDL_ANCHOR);
//STRIP001  if ( ! pHdl )
//STRIP001      pHdl = aHdl.GetHdl(HDL_ANCHOR_TR);
//STRIP001
//STRIP001  if(pHdl)
//STRIP001  {
//STRIP001      const ViewShell &rSh = *Imp().GetShell();
//STRIP001      const OutputDevice *pOut = rSh.GetOut();
//STRIP001
//STRIP001      if(pHdl->IsHit(rPt, *pOut))
//STRIP001      {
//STRIP001          B2dIAObject* pIAO = pHdl->GetIAOGroup().GetIAObject(0);
//STRIP001
//STRIP001          if(pIAO && pIAO->ISA(B2dIAOBitmapExReference))
//STRIP001          {
//STRIP001              Rectangle aRect(
//STRIP001                  pIAO->GetBasePosition(),
//STRIP001                  pOut->PixelToLogic(((B2dIAOBitmapExReference*)pIAO)->GetBitmapEx()->GetSizePixel()));
//STRIP001              return new Rectangle(aRect);
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return NULL;
//STRIP001 }

/*************************************************************************
|*
|*  SwDrawView::ShowDragXor(), HideDragXor()
|*
|*  Ersterstellung      MA 17. Jan. 95
|*  Letzte Aenderung    MA 27. Jan. 95
|*
*************************************************************************/


//STRIP001 void SwDrawView::ShowDragAnchor()
//STRIP001 {
//STRIP001  SdrHdl* pHdl = aHdl.GetHdl(HDL_ANCHOR);
//STRIP001  if ( ! pHdl )
//STRIP001      pHdl = aHdl.GetHdl(HDL_ANCHOR_TR);
//STRIP001
//STRIP001  if(pHdl)
//STRIP001  {
//STRIP001      CalcAnchor();
//STRIP001      pHdl->SetPos(aAnchorPoint);
//STRIP001      RefreshAllIAOManagers();
//STRIP001  }
//STRIP001 }



/*************************************************************************
|*
|*  SwDrawView::MarkListHasChanged()
|*
|*  Ersterstellung      OM 02. Feb. 95
|*  Letzte Aenderung    OM 07. Jul. 95
|*
*************************************************************************/


/*N*/ void SwDrawView::MarkListHasChanged()
/*N*/ {
/*N*/   Imp().GetShell()->DrawSelChanged(this);
/*N*/   FmFormView::MarkListHasChanged();
/*N*/ }

// #i7672#
/*N*/ void SwDrawView::ModelHasChanged()
/*N*/ {
    // The ModelHasChanged() call in DrawingLayer also updates
    // a eventually active text edit view (OutlinerView). This also leads
    // to newly setting the background color for that edit view. Thus,
    // this method rescues the current background color if a OutlinerView
    // exists and re-establishes it then. To be more safe, the OutlinerView
    // will be fetched again (maybe textedit has ended).
/*N*/   OutlinerView* pView = GetTextEditOutlinerView();
/*N*/   Color aBackColor;
/*N*/   sal_Bool bColorWasSaved(sal_False);
/*N*/
/*N*/   if(pView)
/*N*/   {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/        aBackColor = pView->GetBackgroundColor();
//STRIP001 /*?*/        bColorWasSaved = sal_True;
/*N*/   }
/*N*/
/*N*/   // call parent
/*N*/   FmFormView::ModelHasChanged();
/*N*/
/*N*/   if(bColorWasSaved)
/*N*/   {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/        pView = GetTextEditOutlinerView();
//STRIP001 /*?*/
//STRIP001 /*?*/        if(pView)
//STRIP001 /*?*/        {
//STRIP001 /*?*/            pView->SetBackgroundColor(aBackColor);
//STRIP001 /*?*/        }
/*N*/   }
/*N*/ }

//STRIP001 void SwDrawView::MakeVisible( const Rectangle &rRect, Window &rWin )
//STRIP001 {
//STRIP001  ASSERT( rImp.GetShell()->GetWin() && &rWin, "MakeVisible, unknown Window");
//STRIP001  rImp.GetShell()->MakeVisible( SwRect( rRect ) );
//STRIP001 }

#if SUPD<500
#define SVOBJ_MISCSTATUS_NOTRESIZEABLE 0
#endif

//STRIP001 void SwDrawView::CheckPossibilities()
//STRIP001 {
//STRIP001  FmFormView::CheckPossibilities();
//STRIP001
//STRIP001  //Zusaetzlich zu den bestehenden Flags der Objekte selbst, die von der
//STRIP001  //DrawingEngine ausgewertet werden, koennen weitere Umstaende zu einem
//STRIP001  //Schutz fuehren.
//STRIP001  //Objekte, die in Rahmen verankert sind, muessen genau dann geschuetzt
//STRIP001  //sein, wenn der Inhalt des Rahmens geschuetzt ist.
//STRIP001  //OLE-Objekte konnen selbst einen Resize-Schutz wuenschen (StarMath)
//STRIP001
//STRIP001  const SdrMarkList &rMrkList = GetMarkList();
//STRIP001  FASTBOOL bProtect = FALSE,
//STRIP001           bSzProtect = FALSE;
//STRIP001  for ( USHORT i = 0; !bProtect && i < rMrkList.GetMarkCount(); ++i )
//STRIP001  {
//STRIP001      const SdrObject *pObj = rMrkList.GetMark( i )->GetObj();
//STRIP001      const SwFrm *pFrm = NULL;
//STRIP001      if ( pObj->IsWriterFlyFrame() )
//STRIP001      {
//STRIP001          const SwFlyFrm *pFly = ((SwVirtFlyDrawObj*)pObj)->GetFlyFrm();
//STRIP001          if ( pFly  )
//STRIP001          {
//STRIP001              pFrm = pFly->GetAnchor();
//STRIP001              if ( pFly->Lower() && pFly->Lower()->IsNoTxtFrm() )
//STRIP001              {
//STRIP001                  SwOLENode *pNd = ((SwCntntFrm*)pFly->Lower())->GetNode()->GetOLENode();
//STRIP001                  if ( pNd )
//STRIP001                  {
//STRIP001                      SvInPlaceObjectRef aRef = pNd->GetOLEObj().GetOleRef();
//STRIP001                      if ( aRef.Is() )
//STRIP001                      {
//STRIP001                          bSzProtect = SVOBJ_MISCSTATUS_NOTRESIZEABLE & aRef->GetMiscStatus()
//STRIP001                                          ? TRUE : FALSE;
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          SwDrawContact *pC = (SwDrawContact*)GetUserCall(pObj);
//STRIP001          if( pC )
//STRIP001              pFrm = pC->GetAnchor();
//STRIP001      }
//STRIP001      if ( pFrm )
//STRIP001          bProtect = pFrm->IsProtected(); //Rahmen, Bereiche usw.
//STRIP001      if ( FLY_IN_CNTNT == ::FindFrmFmt( (SdrObject*)pObj )->GetAnchor().GetAnchorId() &&
//STRIP001           rMrkList.GetMarkCount() > 1 )
//STRIP001          bProtect = TRUE;
//STRIP001  }
//STRIP001  bMoveProtect    |= bProtect;
//STRIP001  bResizeProtect  |= bProtect | bSzProtect;
//STRIP001 }

/** replace marked <SwDrawVirtObj>-objects by its reference object for delete
    marked objects.

    OD 18.06.2003 #108784#

    @author OD
*/
//STRIP001 void SwDrawView::ReplaceMarkedDrawVirtObjs( SdrMarkView& _rMarkView )
//STRIP001 {
//STRIP001     SdrPageView* pDrawPageView = _rMarkView.GetPageViewPgNum(0);
//STRIP001     const SdrMarkList& rMarkList = _rMarkView.GetMarkList();
//STRIP001
//STRIP001     if( rMarkList.GetMarkCount() )
//STRIP001     {
//STRIP001         // collect marked objects in a local data structure
//STRIP001         std::vector<SdrObject*> aMarkedObjs;
//STRIP001         for( sal_uInt32 i = 0; i < rMarkList.GetMarkCount(); ++i )
//STRIP001         {
//STRIP001             SdrObject* pMarkedObj = rMarkList.GetMark( i )->GetObj();
//STRIP001             aMarkedObjs.push_back( pMarkedObj );
//STRIP001         }
//STRIP001         // unmark all objects
//STRIP001         _rMarkView.UnmarkAllObj();
//STRIP001         // re-mark objects, but for marked <SwDrawVirtObj>-objects marked its
//STRIP001         // reference object.
//STRIP001         while ( !aMarkedObjs.empty() )
//STRIP001         {
//STRIP001             SdrObject* pMarkObj = aMarkedObjs.back();
//STRIP001             if ( pMarkObj->ISA(SwDrawVirtObj) )
//STRIP001             {
//STRIP001                 SdrObject* pRefObj = &(static_cast<SwDrawVirtObj*>(pMarkObj)->ReferencedObj());
//STRIP001                 if ( !_rMarkView.IsObjMarked( pRefObj )  )
//STRIP001                 {
//STRIP001                     _rMarkView.MarkObj( pRefObj, pDrawPageView );
//STRIP001                 }
//STRIP001             }
//STRIP001             else
//STRIP001             {
//STRIP001                 _rMarkView.MarkObj( pMarkObj, pDrawPageView );
//STRIP001             }
//STRIP001
//STRIP001             aMarkedObjs.pop_back();
//STRIP001         }
//STRIP001         // sort marked list in order to assure consistent state in drawing layer
//STRIP001         _rMarkView.SortMarkList();
//STRIP001     }
//STRIP001 }

//STRIP001 void SwDrawView::DeleteMarked()
//STRIP001 {
//STRIP001  SwDoc* pDoc = Imp().GetShell()->GetDoc();
//STRIP001     if ( pDoc->GetRootFrm() )
//STRIP001      pDoc->GetRootFrm()->StartAllAction();
//STRIP001  pDoc->StartUndo();
//STRIP001     // OD 18.06.2003 #108784# - replace marked <SwDrawVirtObj>-objects by its
//STRIP001     // reference objects.
//STRIP001     {
//STRIP001         SdrPageView* pDrawPageView = rImp.GetPageView();
//STRIP001         if ( pDrawPageView )
//STRIP001         {
//STRIP001             SdrMarkView* pMarkView = PTR_CAST( SdrMarkView, &(pDrawPageView->GetView()) );
//STRIP001             if ( pMarkView )
//STRIP001             {
//STRIP001                 ReplaceMarkedDrawVirtObjs( *pMarkView );
//STRIP001             }
//STRIP001         }
//STRIP001     }
//STRIP001     if ( pDoc->DeleteSelection( *this ) )
//STRIP001  {
//STRIP001      FmFormView::DeleteMarked();
//STRIP001      ::FrameNotify( Imp().GetShell(), FLY_DRAG_END );
//STRIP001  }
//STRIP001  pDoc->EndUndo();
//STRIP001  if( pDoc->GetRootFrm() )
//STRIP001      pDoc->GetRootFrm()->EndAllAction();
//STRIP001 }

/********
JP 02.10.98: sollte als Fix fuer 57153 gelten, hatte aber Nebenwirkungen,
            wie Bug 57475
const SdrMarkList& SwDrawView::GetMarkList() const
{
    FlushComeBackTimer();
    return FmFormView::GetMarkList();
}
*************/









}
