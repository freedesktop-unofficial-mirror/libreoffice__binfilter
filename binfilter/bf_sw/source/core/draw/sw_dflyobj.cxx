/*************************************************************************
 *
 *  $RCSfile: sw_dflyobj.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 15:15:35 $
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

#ifndef _XPOLY_HXX //autogen
#include <bf_svx/xpoly.hxx>
#endif
#ifndef _SVDTRANS_HXX
#include <bf_svx/svdtrans.hxx>
#endif
#ifndef _SVX_PROTITEM_HXX //autogen
#include <bf_svx/protitem.hxx>
#endif
#ifndef _SVX_OPAQITEM_HXX //autogen
#include <bf_svx/opaqitem.hxx>
#endif
#ifndef _SVDPAGE_HXX //autogen
#include <bf_svx/svdpage.hxx>
#endif


#ifndef _FMTCLDS_HXX //autogen
#include <fmtclds.hxx>
#endif
#ifndef _FMTORNT_HXX //autogen
#include <fmtornt.hxx>
#endif
#ifndef _FMTFSIZE_HXX //autogen
#include <fmtfsize.hxx>
#endif
#ifndef _FMTURL_HXX //autogen
#include <fmturl.hxx>
#endif
#include "frmsh.hxx"
#include "viewsh.hxx"
#include "viewimp.hxx"
#include "cntfrm.hxx"
#include "frmatr.hxx"
#include "doc.hxx"
#include "dview.hxx"
#include "dflyobj.hxx"
#include "flyfrm.hxx"
#include "frmfmt.hxx"
#include "viewopt.hxx"
#include "frmtool.hxx"
#include "flyfrms.hxx"
#include "ndnotxt.hxx"
#include "grfatr.hxx"
#include "pagefrm.hxx"

static FASTBOOL bInResize = FALSE;

/*N*/ TYPEINIT1( SwFlyDrawObj, SdrObject )
/*N*/ TYPEINIT1( SwVirtFlyDrawObj, SdrVirtObj )

/*************************************************************************
|*
|*  SwFlyDrawObj::Ctor
|*
|*  Ersterstellung      MA 18. Apr. 95
|*  Letzte Aenderung    MA 28. May. 96
|*
*************************************************************************/
/*N*/ SwFlyDrawObj::SwFlyDrawObj()
/*N*/ {
/*N*/   bNotPersistent = TRUE;
/*N*/   mpLocalItemSet = NULL;
/*N*/ }

/*N*/ SwFlyDrawObj::~SwFlyDrawObj()
/*N*/ {
/*N*/   if(mpLocalItemSet)
/*?*/       delete mpLocalItemSet;
/*N*/ }

//STRIP001 SfxItemSet* SwFlyDrawObj::CreateNewItemSet(SfxItemPool& rPool)
//STRIP001 {
//STRIP001  return new SfxItemSet(rPool);
//STRIP001 }

//STRIP001 const SfxItemSet& SwFlyDrawObj::GetItemSet() const
//STRIP001 {
//STRIP001  if(!mpLocalItemSet)
//STRIP001  {
//STRIP001      ((SwFlyDrawObj*)this)->mpLocalItemSet =
//STRIP001      ((SwFlyDrawObj*)this)->CreateNewItemSet((SfxItemPool&)(*GetItemPool()));
//STRIP001      DBG_ASSERT(mpLocalItemSet, "Could not create an SfxItemSet(!)");
//STRIP001  }
//STRIP001
//STRIP001  return *mpLocalItemSet;
//STRIP001 }

/*************************************************************************
|*
|*  SwFlyDrawObj::Paint()
|*
|*  Ersterstellung      MA 08. Dec. 94
|*  Letzte Aenderung    MA 20. May. 95
|*
*************************************************************************/

//STRIP001 FASTBOOL __EXPORT SwFlyDrawObj::Paint(ExtOutputDevice& rOut, const SdrPaintInfoRec& rInfoRec) const
//STRIP001 {
//STRIP001  return TRUE;
//STRIP001 }

/*************************************************************************
|*
|*  SwFlyDrawObj::Factory-Methoden
|*
|*  Ersterstellung      MA 23. Feb. 95
|*  Letzte Aenderung    MA 23. Feb. 95
|*
*************************************************************************/

/*N*/ UINT32 __EXPORT SwFlyDrawObj::GetObjInventor() const
/*N*/ {
/*N*/   return SWGInventor;
/*N*/ }


/*N*/ UINT16 __EXPORT SwFlyDrawObj::GetObjIdentifier()  const
/*N*/ {
/*N*/   return SwFlyDrawObjIdentifier;
/*N*/ }


//STRIP001 UINT16 __EXPORT SwFlyDrawObj::GetObjVersion() const
//STRIP001 {
//STRIP001  return SwDrawFirst;
//STRIP001 }

/*************************************************************************
|*
|*  SwVirtFlyDrawObj::CToren, Dtor
|*
|*  Ersterstellung      MA 08. Dec. 94
|*  Letzte Aenderung    MA 28. May. 96
|*
*************************************************************************/

/*N*/ SwVirtFlyDrawObj::SwVirtFlyDrawObj(SdrObject& rNew, SwFlyFrm* pFly) :
/*N*/   SdrVirtObj( rNew ),
/*N*/   pFlyFrm( pFly )
/*N*/ {
/*N*/   bNotPersistent = bNeedColorRestore = bWriterFlyFrame = TRUE;
/*N*/   const SvxProtectItem &rP = pFlyFrm->GetFmt()->GetProtect();
/*N*/   bMovProt = rP.IsPosProtected();
/*N*/   bSizProt = rP.IsSizeProtected();
/*N*/ }


/*N*/ __EXPORT SwVirtFlyDrawObj::~SwVirtFlyDrawObj()
/*N*/ {
/*N*/   if ( GetPage() )    //Der SdrPage die Verantwortung entziehen.
/*N*/       GetPage()->RemoveObject( GetOrdNum() );
/*N*/ }

/*************************************************************************
|*
|*  SwVirtFlyDrawObj::GetFmt()
|*
|*  Ersterstellung      MA 08. Dec. 94
|*  Letzte Aenderung    MA 08. Dec. 94
|*
*************************************************************************/

//STRIP001 const SwFrmFmt *SwVirtFlyDrawObj::GetFmt() const
//STRIP001 {
//STRIP001  return GetFlyFrm()->GetFmt();
//STRIP001 }


/*N*/ SwFrmFmt *SwVirtFlyDrawObj::GetFmt()
/*N*/ {
/*N*/   return GetFlyFrm()->GetFmt();
/*N*/ }

/*************************************************************************
|*
|*  SwVirtFlyDrawObj::Paint()
|*
|*  Ersterstellung      MA 20. Dec. 94
|*  Letzte Aenderung    MA 18. Dec. 95
|*
*************************************************************************/

//STRIP001 FASTBOOL __EXPORT SwVirtFlyDrawObj::Paint(ExtOutputDevice& rOut, const SdrPaintInfoRec& rInfoRec) const
//STRIP001 {
//STRIP001  if ( !pFlyFrm->IsFlyInCntFrm() ) //FlyInCnt werden von den TxtPortions gepaintet.
//STRIP001  {
//STRIP001      //Rect auf den Fly begrenzen.
//STRIP001      SwRect aRect( rInfoRec.aDirtyRect );
//STRIP001      if ( rInfoRec.aDirtyRect.IsEmpty() )
//STRIP001          aRect = GetFlyFrm()->Frm();
//STRIP001      pFlyFrm->Paint( aRect );
//STRIP001  }
//STRIP001  return TRUE;
//STRIP001 }

/*************************************************************************
|*
|*  SwVirtFlyDrawObj::CheckHit()
|*  Beschreibung        Das Teil ist genau dann getroffen wenn
|*                      1. der Point im Rand des Frm liegt.
|*                      2. der Point im heissen Bereich liegt.
|*                      3. der Point in der Flaeche liegt und es sich um
|*                         einen Rahmen mit NoTxtFrm handelt und dieser
|*                         keine URL traegt.
|*                      3a nicht aber wenn ueber dem Fly noch ein Fly liegt,
|*                         und der Point in dessen Flaeche nicht steht.
|*                      4. der Point in der Flaeche liegt und der Rahmen
|*                         selektiert ist.
|*  Ersterstellung      MA 08. Dec. 94
|*  Letzte Aenderung    JP 25.03.96
|*
*************************************************************************/

//STRIP001 SdrObject* __EXPORT SwVirtFlyDrawObj::CheckHit( const Point& rPnt, USHORT nTol,
//STRIP001                                  const SetOfByte* pVisiLayer) const
//STRIP001 {
//STRIP001  Rectangle aHitRect( pFlyFrm->Frm().Pos(), pFlyFrm->Frm().SSize() );
//STRIP001  if ( nTol )
//STRIP001  {
//STRIP001      Rectangle aExclude( aHitRect );
//STRIP001      aHitRect.Top()    -= nTol;
//STRIP001      aHitRect.Bottom() += nTol;
//STRIP001      aHitRect.Left()   -= nTol;
//STRIP001      aHitRect.Right()  += nTol;
//STRIP001      if( aHitRect.IsInside( rPnt ) )
//STRIP001      {
//STRIP001 //           const SwFmtURL &rURL = pFlyFrm->GetFmt()->GetURL();
//STRIP001          if( pFlyFrm->Lower() && pFlyFrm->Lower()->IsNoTxtFrm()
//STRIP001              /*
//STRIP001              JP 07.08.96: nach Umstellung von JOE zur 330 darf das nicht
//STRIP001                          mehr sein!
//STRIP001              && !rURL.GetURL().Len() && !rURL.GetMap()
//STRIP001              */ )
//STRIP001          {
//STRIP001                          // #107513#
//STRIP001              // This test needs to be done outside, since also drawing layer HitTest
//STRIP001              // methods are called. Not all drawing objects are derived and the
//STRIP001              // CheckHit() overloaded. That's an conceptual error here.
//STRIP001              return (SdrObject*)this;
//STRIP001
//STRIP001              //Vor dem Return noch 3a (siehe oben) pruefen.
//STRIP001              //SdrPage *pPg = GetPage();
//STRIP001              //for ( UINT32 i = GetOrdNumDirect()+1; i < pPg->GetObjCount(); ++i )
//STRIP001              //{
//STRIP001              //  SdrObject *pObj = pPg->GetObj( i );
//STRIP001              //  if ( pObj->IsWriterFlyFrame() &&
//STRIP001              //       ((SwVirtFlyDrawObj*)pObj)->GetBoundRect().IsInside( rPnt ) )
//STRIP001              //      return 0;
//STRIP001              //}
//STRIP001              //return (SdrObject*)this;
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              ViewShell *pShell = pFlyFrm->GetShell();
//STRIP001
//STRIP001              //4. Getroffen wenn das Objekt selektiert ist.
//STRIP001              if ( pShell )
//STRIP001              {
//STRIP001                  const SdrMarkList &rMrkList = pShell->
//STRIP001                                          Imp()->GetDrawView()->GetMarkList();
//STRIP001                  for ( USHORT i = 0; i < rMrkList.GetMarkCount(); ++i )
//STRIP001                      if ( long(this) == long(rMrkList.GetMark(i)->GetObj()) )
//STRIP001                          return (SdrObject*)this;
//STRIP001              }
//STRIP001
//STRIP001              const Rectangle aPrtRect( pFlyFrm->Frm().Pos() + pFlyFrm->Prt().Pos(),
//STRIP001                                        pFlyFrm->Prt().SSize() );
//STRIP001              aExclude.Top()    += Max( long(nTol), aPrtRect.Top()   - aHitRect.Top() );
//STRIP001              aExclude.Bottom() -= Max( long(nTol), aHitRect.Bottom()- aPrtRect.Bottom());
//STRIP001              aExclude.Left()   += Max( long(nTol), aPrtRect.Left()  - aHitRect.Left() );
//STRIP001              aExclude.Right()  -= Max( long(nTol), aHitRect.Right() - aPrtRect.Right() );
//STRIP001              return aExclude.IsInside( rPnt ) ? 0 : (SdrObject*)this;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001      return aHitRect.IsInside( rPnt ) ? (SdrObject*)this : 0;
//STRIP001  return 0;
//STRIP001 }

/*************************************************************************
|*
|*  SwVirtFlyDrawObj::TakeObjInfo()
|*
|*  Ersterstellung      MA 03. May. 95
|*  Letzte Aenderung    MA 03. May. 95
|*
*************************************************************************/

//STRIP001 void __EXPORT SwVirtFlyDrawObj::TakeObjInfo( SdrObjTransformInfoRec& rInfo ) const
//STRIP001 {
//STRIP001  rInfo.bSelectAllowed     = rInfo.bMoveAllowed =
//STRIP001  rInfo.bResizeFreeAllowed = rInfo.bResizePropAllowed = TRUE;
//STRIP001
//STRIP001  rInfo.bRotateFreeAllowed = rInfo.bRotate90Allowed =
//STRIP001  rInfo.bMirrorFreeAllowed = rInfo.bMirror45Allowed =
//STRIP001  rInfo.bMirror90Allowed   = rInfo.bShearAllowed    =
//STRIP001  rInfo.bCanConvToPath     = rInfo.bCanConvToPoly   =
//STRIP001  rInfo.bCanConvToPathLineToArea = rInfo.bCanConvToPolyLineToArea = FALSE;
//STRIP001 }


/*************************************************************************
|*
|*  SwVirtFlyDrawObj::Groessenermittlung
|*
|*  Ersterstellung      MA 12. Jan. 95
|*  Letzte Aenderung    MA 10. Nov. 95
|*
*************************************************************************/

/*N*/ void SwVirtFlyDrawObj::SetRect() const
/*N*/ {
/*N*/   if ( GetFlyFrm()->Frm().HasArea() )
/*N*/       ((SwVirtFlyDrawObj*)this)->aOutRect = GetFlyFrm()->Frm().SVRect();
/*N*/   else
/*?*/       ((SwVirtFlyDrawObj*)this)->aOutRect = Rectangle();
/*N*/ }


/*N*/ const Rectangle& __EXPORT SwVirtFlyDrawObj::GetBoundRect() const
/*N*/ {
/*N*/   SetRect();
/*N*/   return aOutRect;
/*N*/ }


//STRIP001 void __EXPORT SwVirtFlyDrawObj::RecalcBoundRect()
//STRIP001 {
//STRIP001  SetRect();
//STRIP001 }


//STRIP001 void __EXPORT SwVirtFlyDrawObj::RecalcSnapRect()
//STRIP001 {
//STRIP001  SetRect();
//STRIP001 }


/*N*/ const Rectangle& __EXPORT SwVirtFlyDrawObj::GetSnapRect()  const
/*N*/ {
/*N*/   SetRect();
/*N*/   return aOutRect;
/*N*/ }


//STRIP001 void __EXPORT SwVirtFlyDrawObj::SetSnapRect(const Rectangle& rRect)
//STRIP001 {
//STRIP001  Rectangle aTmp( aOutRect );
//STRIP001  SetRect();
//STRIP001  SetChanged();
//STRIP001  SendRepaintBroadcast();
//STRIP001  if (pUserCall!=NULL)
//STRIP001      pUserCall->Changed(*this, SDRUSERCALL_RESIZE, aTmp);
//STRIP001 }


//STRIP001 void __EXPORT SwVirtFlyDrawObj::NbcSetSnapRect(const Rectangle& rRect)
//STRIP001 {
//STRIP001  SetRect();
//STRIP001 }


//STRIP001 const Rectangle& __EXPORT SwVirtFlyDrawObj::GetLogicRect() const
//STRIP001 {
//STRIP001  SetRect();
//STRIP001  return aOutRect;
//STRIP001 }


//STRIP001 void __EXPORT SwVirtFlyDrawObj::SetLogicRect(const Rectangle& rRect)
//STRIP001 {
//STRIP001  Rectangle aTmp( aOutRect );
//STRIP001  SetRect();
//STRIP001  SetChanged();
//STRIP001  SendRepaintBroadcast();
//STRIP001  if (pUserCall!=NULL)
//STRIP001      pUserCall->Changed(*this, SDRUSERCALL_RESIZE, aTmp);
//STRIP001 }


//STRIP001 void __EXPORT SwVirtFlyDrawObj::NbcSetLogicRect(const Rectangle& rRect)
//STRIP001 {
//STRIP001  SetRect();
//STRIP001 }


//STRIP001 void __EXPORT SwVirtFlyDrawObj::TakeXorPoly(XPolyPolygon& rPoly, FASTBOOL ) const
//STRIP001 {
//STRIP001  rPoly = XPolyPolygon( XPolygon( GetFlyFrm()->Frm().SVRect() ) );
//STRIP001 }

/*************************************************************************
|*
|*  SwVirtFlyDrawObj::Move() und Resize()
|*
|*  Ersterstellung      MA 12. Jan. 95
|*  Letzte Aenderung    MA 26. Jul. 96
|*
*************************************************************************/

//STRIP001 void __EXPORT SwVirtFlyDrawObj::NbcMove(const Size& rSiz)
//STRIP001 {
//STRIP001  MoveRect( aOutRect, rSiz );
//STRIP001  const Point aOldPos( GetFlyFrm()->Frm().Pos() );
//STRIP001  const Point aNewPos( aOutRect.TopLeft() );
//STRIP001  const SwRect aFlyRect( aOutRect );
//STRIP001
//STRIP001  //Wenn der Fly eine automatische Ausrichtung hat (rechts oder oben),
//STRIP001  //so soll die Automatik erhalten bleiben
//STRIP001  SwFrmFmt *pFmt = GetFlyFrm()->GetFmt();
//STRIP001  const SwHoriOrient eHori = pFmt->GetHoriOrient().GetHoriOrient();
//STRIP001  const SwVertOrient eVert = pFmt->GetVertOrient().GetVertOrient();
//STRIP001  const SwRelationOrient eRelHori = pFmt->GetHoriOrient().GetRelationOrient();
//STRIP001  const SwRelationOrient eRelVert = pFmt->GetVertOrient().GetRelationOrient();
//STRIP001  //Bei Absatzgebundenen Flys muss ausgehend von der neuen Position ein
//STRIP001  //neuer Anker gesetzt werden. Anker und neue RelPos werden vom Fly selbst
//STRIP001  //berechnet und gesetzt.
//STRIP001     if( GetFlyFrm()->IsFlyAtCntFrm() )
//STRIP001      ((SwFlyAtCntFrm*)GetFlyFrm())->SetAbsPos( aNewPos );
//STRIP001  else
//STRIP001  {
//STRIP001      const SwFrmFmt *pFmt = GetFmt();
//STRIP001      const SwFmtVertOrient &rVert = pFmt->GetVertOrient();
//STRIP001      const SwFmtHoriOrient &rHori = pFmt->GetHoriOrient();
//STRIP001      long lXDiff = aNewPos.X() - aOldPos.X();
//STRIP001      if( rHori.IsPosToggle() && HORI_NONE == eHori &&
//STRIP001          !GetFlyFrm()->FindPageFrm()->OnRightPage() )
//STRIP001          lXDiff = -lXDiff;
//STRIP001
//STRIP001 #ifdef BIDI
//STRIP001         if( GetFlyFrm()->GetAnchor()->IsRightToLeft() &&
//STRIP001             HORI_NONE == eHori )
//STRIP001             lXDiff = -lXDiff;
//STRIP001 #endif
//STRIP001
//STRIP001         long lYDiff = aNewPos.Y() - aOldPos.Y();
//STRIP001 #ifdef VERTICAL_LAYOUT
//STRIP001         if( GetFlyFrm()->GetAnchor()->IsVertical() )
//STRIP001         {
//STRIP001             lXDiff -= rVert.GetPos();
//STRIP001             lYDiff += rHori.GetPos();
//STRIP001         }
//STRIP001         else
//STRIP001         {
//STRIP001             lXDiff += rHori.GetPos();
//STRIP001             lYDiff += rVert.GetPos();
//STRIP001         }
//STRIP001
//STRIP001 #ifdef BIDI
//STRIP001         if( GetFlyFrm()->GetAnchor()->IsRightToLeft() &&
//STRIP001          HORI_NONE != eHori )
//STRIP001          lXDiff = GetFlyFrm()->GetAnchor()->Frm().Width() -
//STRIP001                   aFlyRect.Width() - lXDiff;
//STRIP001 #endif
//STRIP001
//STRIP001         const Point aTmp( lXDiff, lYDiff );
//STRIP001 #else
//STRIP001      const Point aTmp( rHori.GetPos() + lXDiff,
//STRIP001                        rVert.GetPos() + lYDiff );
//STRIP001 #endif
//STRIP001      GetFlyFrm()->ChgRelPos( aTmp );
//STRIP001  }
//STRIP001
//STRIP001  SwAttrSet aSet( pFmt->GetDoc()->GetAttrPool(),
//STRIP001                                          RES_VERT_ORIENT, RES_HORI_ORIENT );
//STRIP001  SwFmtHoriOrient aHori( pFmt->GetHoriOrient() );
//STRIP001  SwFmtVertOrient aVert( pFmt->GetVertOrient() );
//STRIP001  FASTBOOL bPut = FALSE;
//STRIP001
//STRIP001  if( !GetFlyFrm()->IsFlyLayFrm() &&
//STRIP001      ::GetHtmlMode(pFmt->GetDoc()->GetDocShell()) )
//STRIP001  {
//STRIP001      //Im HTML-Modus sind nur automatische Ausrichtungen erlaubt.
//STRIP001      //Einzig einen Snap auf Links/Rechts bzw. Linker-/Rechter-Rand koennen
//STRIP001      //wir versuchen.
//STRIP001      SwFrm *pAnch = GetFlyFrm()->GetAnchor();
//STRIP001      BOOL bNextLine = FALSE;
//STRIP001
//STRIP001      if( !GetFlyFrm()->IsAutoPos() || REL_PG_FRAME != aHori.GetRelationOrient() )
//STRIP001      {
//STRIP001          if( REL_CHAR == eRelHori )
//STRIP001          {
//STRIP001              aHori.SetHoriOrient( HORI_LEFT );
//STRIP001              aHori.SetRelationOrient( REL_CHAR );
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              bNextLine = TRUE;
//STRIP001              //Horizontale Ausrichtung:
//STRIP001              const FASTBOOL bLeftFrm =
//STRIP001                  aFlyRect.Left() < pAnch->Frm().Left() + pAnch->Prt().Left(),
//STRIP001                  bLeftPrt = aFlyRect.Left() + aFlyRect.Width() <
//STRIP001                             pAnch->Frm().Left() + pAnch->Prt().Width()/2;
//STRIP001              if ( bLeftFrm || bLeftPrt )
//STRIP001              {
//STRIP001                  aHori.SetHoriOrient( HORI_LEFT );
//STRIP001                  aHori.SetRelationOrient( bLeftFrm ? FRAME : PRTAREA );
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  const FASTBOOL bRightFrm = aFlyRect.Left() >
//STRIP001                                     pAnch->Frm().Left() + pAnch->Prt().Width();
//STRIP001                  aHori.SetHoriOrient( HORI_RIGHT );
//STRIP001                  aHori.SetRelationOrient( bRightFrm ? FRAME : PRTAREA );
//STRIP001              }
//STRIP001          }
//STRIP001          aSet.Put( aHori );
//STRIP001      }
//STRIP001      //Vertikale Ausrichtung bleibt grundsaetzlich schlicht erhalten,
//STRIP001      //nur bei nicht automatischer Ausrichtung wird umgeschaltet.
//STRIP001      BOOL bRelChar = REL_CHAR == eRelVert;
//STRIP001      aVert.SetVertOrient( eVert != VERT_NONE ? eVert :
//STRIP001              GetFlyFrm()->IsFlyInCntFrm() ? VERT_CHAR_CENTER :
//STRIP001              bRelChar && bNextLine ? VERT_CHAR_TOP : VERT_TOP );
//STRIP001      if( bRelChar )
//STRIP001          aVert.SetRelationOrient( REL_CHAR );
//STRIP001      else
//STRIP001          aVert.SetRelationOrient( PRTAREA );
//STRIP001      aSet.Put( aVert );
//STRIP001      bPut = TRUE;
//STRIP001  }
//STRIP001
//STRIP001  //Automatische Ausrichtungen wollen wir moeglichst nicht verlieren.
//STRIP001  if ( !bPut && bInResize )
//STRIP001  {
//STRIP001      if ( HORI_NONE != eHori )
//STRIP001      {
//STRIP001          aHori.SetHoriOrient( eHori );
//STRIP001          aHori.SetRelationOrient( eRelHori );
//STRIP001          aSet.Put( aHori );
//STRIP001          bPut = TRUE;
//STRIP001      }
//STRIP001      if ( VERT_NONE != eVert )
//STRIP001      {
//STRIP001          aVert.SetVertOrient( eVert );
//STRIP001          aVert.SetRelationOrient( eRelVert );
//STRIP001          aSet.Put( aVert );
//STRIP001          bPut = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  if ( bPut )
//STRIP001      pFmt->SetAttr( aSet );
//STRIP001 }


//STRIP001 void __EXPORT SwVirtFlyDrawObj::NbcResize(const Point& rRef,
//STRIP001          const Fraction& xFact, const Fraction& yFact)
//STRIP001 {
//STRIP001  ResizeRect( aOutRect, rRef, xFact, yFact );
//STRIP001
//STRIP001     SWRECTFN( GetFlyFrm() )
//STRIP001     SwFrm* pTmpFrm = GetFlyFrm()->GetAnchor();
//STRIP001     if( !pTmpFrm )
//STRIP001         pTmpFrm = GetFlyFrm();
//STRIP001     SWRECTFNX( pTmpFrm )
//STRIP001
//STRIP001 #ifdef BIDI
//STRIP001     const sal_Bool bRTL = pTmpFrm->IsRightToLeft();
//STRIP001
//STRIP001     const Point aNewPos( bVertX || bRTL ?
//STRIP001                       aOutRect.Right() + 1 :
//STRIP001                       aOutRect.Left(),
//STRIP001                          aOutRect.Top() );
//STRIP001 #else
//STRIP001     const Point aNewPos( bVertX  ? aOutRect.Right() + 1 : aOutRect.Left(),
//STRIP001                          aOutRect.Top() );
//STRIP001 #endif
//STRIP001
//STRIP001  Size aSz( aOutRect.Right() - aOutRect.Left() + 1,
//STRIP001            aOutRect.Bottom()- aOutRect.Top()  + 1 );
//STRIP001  if( aSz != GetFlyFrm()->Frm().SSize() )
//STRIP001  {
//STRIP001      //Die Breite darf bei Spalten nicht zu schmal werden
//STRIP001      if ( GetFlyFrm()->Lower() && GetFlyFrm()->Lower()->IsColumnFrm() )
//STRIP001      {
//STRIP001          SwBorderAttrAccess aAccess( SwFrm::GetCache(), GetFlyFrm() );
//STRIP001          const SwBorderAttrs &rAttrs = *aAccess.Get();
//STRIP001          long nMin = rAttrs.CalcLeftLine()+rAttrs.CalcRightLine();
//STRIP001          const SwFmtCol& rCol = rAttrs.GetAttrSet().GetCol();
//STRIP001          if ( rCol.GetColumns().Count() > 1 )
//STRIP001          {
//STRIP001              for ( USHORT i = 0; i < rCol.GetColumns().Count(); ++i )
//STRIP001              {
//STRIP001                  nMin += rCol.GetColumns()[i]->GetLeft() +
//STRIP001                          rCol.GetColumns()[i]->GetRight() +
//STRIP001                          MINFLY;
//STRIP001              }
//STRIP001              nMin -= MINFLY;
//STRIP001          }
//STRIP001          aSz.Width() = Max( aSz.Width(), nMin );
//STRIP001      }
//STRIP001
//STRIP001      SwFrmFmt *pFmt = GetFmt();
//STRIP001      const SwFmtFrmSize aOldFrmSz( pFmt->GetFrmSize() );
//STRIP001      GetFlyFrm()->ChgSize( aSz );
//STRIP001      SwFmtFrmSize aFrmSz( pFmt->GetFrmSize() );
//STRIP001      if ( aFrmSz.GetWidthPercent() || aFrmSz.GetHeightPercent() )
//STRIP001      {
//STRIP001          long nRelWidth, nRelHeight;
//STRIP001          const SwFrm *pRel = GetFlyFrm()->IsFlyLayFrm() ?
//STRIP001                              GetFlyFrm()->GetAnchor() :
//STRIP001                              GetFlyFrm()->GetAnchor()->GetUpper();
//STRIP001          const ViewShell *pSh = GetFlyFrm()->GetShell();
//STRIP001          if ( pSh && pRel->IsBodyFrm() && pFmt->GetDoc()->IsBrowseMode() &&
//STRIP001               pSh->VisArea().HasArea() )
//STRIP001          {
//STRIP001              nRelWidth  = pSh->VisArea().Width();
//STRIP001              nRelHeight = pSh->VisArea().Height();
//STRIP001              const Size aBorder = pSh->GetOut()->PixelToLogic( pSh->GetBrowseBorder() );
//STRIP001              nRelWidth  -= 2*aBorder.Width();
//STRIP001              nRelHeight -= 2*aBorder.Height();
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              nRelWidth  = pRel->Prt().Width();
//STRIP001              nRelHeight = pRel->Prt().Height();
//STRIP001          }
//STRIP001          if ( aFrmSz.GetWidthPercent() && aFrmSz.GetWidthPercent() != 0xFF &&
//STRIP001               aOldFrmSz.GetWidth() != aFrmSz.GetWidth() )
//STRIP001              aFrmSz.SetWidthPercent( BYTE(aSz.Width() * 100L / nRelWidth + 0.5) );
//STRIP001          if ( aFrmSz.GetHeightPercent() && aFrmSz.GetHeightPercent() != 0xFF &&
//STRIP001               aOldFrmSz.GetHeight() != aFrmSz.GetHeight() )
//STRIP001              aFrmSz.SetHeightPercent( BYTE(aSz.Height() * 100L / nRelHeight + 0.5) );
//STRIP001          pFmt->GetDoc()->SetAttr( aFrmSz, *pFmt );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  //Position kann auch veraendert sein!
//STRIP001 #ifdef BIDI
//STRIP001     const Point aOldPos( bVertX || bRTL ?
//STRIP001                          GetFlyFrm()->Frm().TopRight() :
//STRIP001                          GetFlyFrm()->Frm().Pos() );
//STRIP001 #else
//STRIP001     const Point aOldPos( (GetFlyFrm()->Frm().*fnRectX->fnGetPos)() );
//STRIP001 #endif
//STRIP001
//STRIP001     if ( aNewPos != aOldPos )
//STRIP001  {
//STRIP001      //Kann sich durch das ChgSize veraendert haben!
//STRIP001 #ifdef BIDI
//STRIP001         if( bVertX || bRTL )
//STRIP001 #else
//STRIP001         if( bVertX )
//STRIP001 #endif
//STRIP001         {
//STRIP001             if( aOutRect.TopRight() != aNewPos )
//STRIP001             {
//STRIP001                 SwTwips nDeltaX = aNewPos.X() - aOutRect.Right();
//STRIP001                 SwTwips nDeltaY = aNewPos.Y() - aOutRect.Top();
//STRIP001                 MoveRect( aOutRect, Size( nDeltaX, nDeltaY ) );
//STRIP001             }
//STRIP001         }
//STRIP001         else if ( aOutRect.TopLeft() != aNewPos )
//STRIP001          aOutRect.SetPos( aNewPos );
//STRIP001      bInResize = TRUE;
//STRIP001      NbcMove( Size( 0, 0 ) );
//STRIP001      bInResize = FALSE;
//STRIP001  }
//STRIP001 }


//STRIP001 void __EXPORT SwVirtFlyDrawObj::Move(const Size& rSiz)
//STRIP001 {
//STRIP001  NbcMove( rSiz );
//STRIP001  SetChanged();
//STRIP001  GetFmt()->GetDoc()->SetNoDrawUndoObj( TRUE );
//STRIP001 }


//STRIP001 void __EXPORT SwVirtFlyDrawObj::Resize(const Point& rRef,
//STRIP001                  const Fraction& xFact, const Fraction& yFact)
//STRIP001 {
//STRIP001  NbcResize( rRef, xFact, yFact );
//STRIP001  SetChanged();
//STRIP001  GetFmt()->GetDoc()->SetNoDrawUndoObj( TRUE );
//STRIP001 }


//STRIP001 Pointer  __EXPORT SwVirtFlyDrawObj::GetMacroPointer(
//STRIP001  const SdrObjMacroHitRec& rRec) const
//STRIP001 {
//STRIP001  return Pointer( POINTER_REFHAND );
//STRIP001 }


//STRIP001 FASTBOOL __EXPORT SwVirtFlyDrawObj::HasMacro() const
//STRIP001 {
//STRIP001  const SwFmtURL &rURL = pFlyFrm->GetFmt()->GetURL();
//STRIP001  return rURL.GetMap() || rURL.GetURL().Len();
//STRIP001 }


//STRIP001 SdrObject* SwVirtFlyDrawObj::CheckMacroHit( const SdrObjMacroHitRec& rRec ) const
//STRIP001 {
//STRIP001  const SwFmtURL &rURL = pFlyFrm->GetFmt()->GetURL();
//STRIP001  if( rURL.GetMap() || rURL.GetURL().Len() )
//STRIP001  {
//STRIP001      SwRect aRect;
//STRIP001      if ( pFlyFrm->Lower() && pFlyFrm->Lower()->IsNoTxtFrm() )
//STRIP001      {
//STRIP001          aRect = pFlyFrm->Prt();
//STRIP001          aRect += pFlyFrm->Frm().Pos();
//STRIP001      }
//STRIP001      else
//STRIP001          aRect = pFlyFrm->Frm();
//STRIP001
//STRIP001      if( aRect.IsInside( rRec.aPos ) )
//STRIP001      {
//STRIP001          SwRect aActRect( aRect );
//STRIP001          Size aActSz( aRect.SSize() );
//STRIP001          aRect.Pos().X() += rRec.nTol;
//STRIP001          aRect.Pos().Y() += rRec.nTol;
//STRIP001          aRect.SSize().Height()-= 2 * rRec.nTol;
//STRIP001          aRect.SSize().Width() -= 2 * rRec.nTol;
//STRIP001
//STRIP001          if( aRect.IsInside( rRec.aPos ) )
//STRIP001          {
//STRIP001              if( !rURL.GetMap() ||
//STRIP001                  pFlyFrm->GetFmt()->GetIMapObject( rRec.aPos, pFlyFrm ))
//STRIP001                  return (SdrObject*)this;
//STRIP001
//STRIP001              return 0;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return SdrObject::CheckMacroHit( rRec );
//STRIP001 }


