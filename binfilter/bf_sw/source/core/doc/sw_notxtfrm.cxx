/*************************************************************************
 *
 *  $RCSfile: sw_notxtfrm.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:40:52 $
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

#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif

#ifndef _URLOBJ_HXX //autogen
#include <tools/urlobj.hxx>
#endif
#ifndef _SV_PRINT_HXX
#include <vcl/print.hxx>
#endif
#ifndef _SV_VIRDEV_HXX //autogen
#include <vcl/virdev.hxx>
#endif
#ifndef _TL_POLY_HXX
#include <tools/poly.hxx>
#endif

#ifndef _GOODIES_IMAPOBJ_HXX
#include <svtools/imapobj.hxx>
#endif
#ifndef _IMAP_HXX //autogen
#include <svtools/imap.hxx>
#endif
#ifndef SVTOOLS_URIHELPER_HXX
#include <svtools/urihelper.hxx>
#endif
#ifndef _IPOBJ_HXX //autogen
#include <so3/ipobj.hxx>
#endif
#ifndef _IPENV_HXX //autogen
#include <so3/ipenv.hxx>
#endif
#ifndef _SOERR_HXX //autogen
#include <so3/soerr.hxx>
#endif
#ifndef _SFX_PROGRESS_HXX //autogen
#include <bf_sfx2/progress.hxx>
#endif
#ifndef _SFXDOCFILE_HXX //autogen
#include <bf_sfx2/docfile.hxx>
#endif
#ifndef _SFX_PRINTER_HXX //autogen
#include <bf_sfx2/printer.hxx>
#endif
#ifndef _SVX_UDLNITEM_HXX //autogen
#include <bf_svx/udlnitem.hxx>
#endif
#ifndef _SVX_COLRITEM_HXX //autogen
#include <bf_svx/colritem.hxx>
#endif
#ifndef _XOUTBMP_HXX //autogen
#include <bf_svx/xoutbmp.hxx>
#endif
#ifndef _WINDOW_HXX //autogen
#include <vcl/window.hxx>
#endif

#ifndef _FMTURL_HXX
#include <fmturl.hxx>
#endif
#ifndef _FMTSRND_HXX
#include <fmtsrnd.hxx>
#endif
#ifndef _FRMFMT_HXX
#include <frmfmt.hxx>
#endif
#ifndef _SWRECT_HXX
#include <swrect.hxx>
#endif
#ifndef _FESH_HXX
#include <fesh.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _FLYFRM_HXX
#include <flyfrm.hxx>
#endif
#ifndef _FRMTOOL_HXX
#include <frmtool.hxx>
#endif
#ifndef _VIEWOPT_HXX
#include <viewopt.hxx>
#endif
#ifndef _VIEWIMP_HXX
#include <viewimp.hxx>
#endif
#ifndef _PAM_HXX
#include <pam.hxx>
#endif
#ifndef _HINTS_HXX
#include <hints.hxx>
#endif
#ifndef _ROOTFRM_HXX
#include <rootfrm.hxx>
#endif
#ifndef _DFLYOBJ_HXX
#include <dflyobj.hxx>
#endif
#ifndef _PAGEFRM_HXX
#include <pagefrm.hxx>
#endif
#ifndef _NOTXTFRM_HXX
#include <notxtfrm.hxx>
#endif
#ifndef _GRFATR_HXX
#include <grfatr.hxx>
#endif
#ifndef _CHARATR_HXX
#include <charatr.hxx>
#endif
#ifndef _FMTORNT_HXX
#include <fmtornt.hxx>
#endif
#ifndef _NDNOTXT_HXX
#include <ndnotxt.hxx>
#endif
#ifndef _NDGRF_HXX
#include <ndgrf.hxx>
#endif
#ifndef _NDOLE_HXX
#include <ndole.hxx>
#endif
#ifndef _SWREGION_HXX
#include <swregion.hxx>
#endif
#ifndef _POOLFMT_HXX
#include <poolfmt.hxx>
#endif
#ifndef _FRMSH_HXX
#include <frmsh.hxx>
#endif

#ifndef _MDIEXP_HXX
#include <mdiexp.hxx>
#endif
#ifndef _SWWAIT_HXX
#include <swwait.hxx>
#endif
#ifndef _COMCORE_HRC
#include <comcore.hrc>
#endif
#ifndef _ACCESSIBILITYOPTIONS_HXX
#include <accessibilityoptions.hxx>
#endif
namespace binfilter {

#define DEFTEXTSIZE  12

// OD 25.09.2002 #99739# - insert declaration of global methods <SwAlignRect>
//     and <SwAlignGrtRect>.
//     Methods are implemented in /core/layout/paintfrm.cxx
// OD 24.01.2003 #106593# - no longer needed, included in <frmtool.hxx>
//extern void MA_FASTCALL SwAlignRect( SwRect &rRect, ViewShell *pSh );
//extern void SwAlignGrfRect( SwRect *pGrfRect, const OutputDevice &rOut );

//Zum asynchronen (erstmaligem) anfordern von Grafiken
//STRIP001 class SwRequestGraphic : public SwClient
//STRIP001 {
//STRIP001  Timer aTimer;
//STRIP001  ViewShell* pSh;
//STRIP001 public:
//STRIP001  SwRequestGraphic( ViewShell& rVSh, SwGrfNode& rNd );
//STRIP001  virtual void Modify( SfxPoolItem *pOld, SfxPoolItem *pNew );
//STRIP001  DECL_STATIC_LINK( SwRequestGraphic, RequestGraphic, void *);
//STRIP001 };


extern void ClrContourCache( const SdrObject *pObj ); // TxtFly.Cxx


//STRIP001 inline BOOL GetRealURL( const SwGrfNode& rNd, String& rTxt )
//STRIP001 {
//STRIP001  BOOL bRet = rNd.GetFileFilterNms( &rTxt, 0 );
//STRIP001  if( bRet )
//STRIP001      rTxt = URIHelper::removePassword( rTxt, INetURLObject::WAS_ENCODED,
//STRIP001                                      INetURLObject::DECODE_UNAMBIGUOUS);
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 SwRequestGraphic::SwRequestGraphic( ViewShell& rVSh, SwGrfNode& rNd )
//STRIP001  : SwClient( &rNd ), pSh( &rVSh )
//STRIP001 {
//STRIP001  aTimer.SetTimeout( 1 );
//STRIP001  aTimer.SetTimeoutHdl( STATIC_LINK( this, SwRequestGraphic, RequestGraphic ) );
//STRIP001  aTimer.Start();
//STRIP001 }


//STRIP001 void SwRequestGraphic::Modify( SfxPoolItem *pOld, SfxPoolItem *pNew )
//STRIP001 {
//STRIP001  if( pOld && RES_OBJECTDYING == pOld->Which() &&
//STRIP001      ((SwPtrMsgPoolItem *)pOld)->pObject == pRegisteredIn )
//STRIP001  {
//STRIP001      pRegisteredIn->Remove( this );
//STRIP001      aTimer.Stop();
//STRIP001      delete this;
//STRIP001  }
//STRIP001 }


//STRIP001 IMPL_STATIC_LINK( SwRequestGraphic, RequestGraphic, void*, EMPTYARG )
//STRIP001 {
//STRIP001  if ( pThis->GetRegisteredIn() && GRAPHIC_DEFAULT ==
//STRIP001      ((SwGrfNode*)pThis->GetRegisteredIn())->GetGrf().GetType() )
//STRIP001  {
//STRIP001      SwGrfNode* pGrfNd = (SwGrfNode*)pThis->GetRegisteredIn();
//STRIP001      ViewShell* pVSh, *pTmpSh;
//STRIP001      pGrfNd->GetDoc()->GetEditShell( &pVSh );
//STRIP001      if( pVSh )
//STRIP001      {
//STRIP001          pTmpSh = pVSh;
//STRIP001          // existiert die Shell noch?
//STRIP001          do {
//STRIP001              if( pThis->pSh == pTmpSh )
//STRIP001              {
//STRIP001                  CurrShell aTmp( pTmpSh );
//STRIP001                  pGrfNd->SetTransferPriority( SFX_TFPRIO_VISIBLE_HIGHRES_GRAPHIC );
//STRIP001                  pGrfNd->SwapIn();
//STRIP001              }
//STRIP001          } while( pVSh != ( pTmpSh = (ViewShell*)pTmpSh->GetNext()) );
//STRIP001      }
//STRIP001  }
//STRIP001  delete pThis;
//STRIP001  return 0;
//STRIP001 }


//STRIP001 void lcl_PaintReplacement( const SwRect &rRect, const String &rText,
//STRIP001                         const ViewShell &rSh, const SwNoTxtFrm *pFrm,
//STRIP001                         FASTBOOL bDefect )
//STRIP001 {
//STRIP001  static Font *pFont = 0;
//STRIP001  if ( !pFont )
//STRIP001  {
//STRIP001      pFont = new Font();
//STRIP001      pFont->SetWeight( WEIGHT_BOLD );
//STRIP001      pFont->SetStyleName( aEmptyStr );
//STRIP001      pFont->SetName( String::CreateFromAscii(
//STRIP001                             RTL_CONSTASCII_STRINGPARAM( "Arial Unicode" )));
//STRIP001      pFont->SetFamily( FAMILY_SWISS );
//STRIP001      pFont->SetTransparent( TRUE );
//STRIP001  }
//STRIP001
//STRIP001  Color aCol( COL_RED );
//STRIP001  FontUnderline eUnderline = UNDERLINE_NONE;
//STRIP001  const SwFmtURL &rURL = pFrm->FindFlyFrm()->GetFmt()->GetURL();
//STRIP001  if( rURL.GetURL().Len() || rURL.GetMap() )
//STRIP001  {
//STRIP001      FASTBOOL bVisited = FALSE;
//STRIP001      if ( rURL.GetMap() )
//STRIP001      {
//STRIP001          ImageMap *pMap = (ImageMap*)rURL.GetMap();
//STRIP001          for( USHORT i = 0; i < pMap->GetIMapObjectCount(); i++ )
//STRIP001          {
//STRIP001              IMapObject *pObj = pMap->GetIMapObject( i );
//STRIP001              if( rSh.GetDoc()->IsVisitedURL( pObj->GetURL() ) )
//STRIP001              {
//STRIP001                  bVisited = TRUE;
//STRIP001                  break;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      else if ( rURL.GetURL().Len() )
//STRIP001          bVisited = rSh.GetDoc()->IsVisitedURL( rURL.GetURL() );
//STRIP001
//STRIP001      SwFmt *pFmt = rSh.GetDoc()->GetFmtFromPool( bVisited ?
//STRIP001              RES_POOLCHR_INET_VISIT : RES_POOLCHR_INET_NORMAL );
//STRIP001      aCol = pFmt->GetColor().GetValue();
//STRIP001      eUnderline = pFmt->GetUnderline().GetUnderline();
//STRIP001  }
//STRIP001
//STRIP001  pFont->SetUnderline( eUnderline );
//STRIP001  pFont->SetColor( aCol );
//STRIP001
//STRIP001  const Bitmap& rBmp = SwNoTxtFrm::GetBitmap( bDefect );
//STRIP001  ((Graphic*)0)->Draw( rSh.GetOut(), rText, *pFont, rBmp,
//STRIP001                       rRect.Pos(), rRect.SSize() );
//STRIP001 }

//STRIP001 const Bitmap& SwNoTxtFrm::GetBitmap( BOOL bErrorBmp )
//STRIP001 {
//STRIP001  Bitmap** ppRet;
//STRIP001  USHORT nResId;
//STRIP001  if( bErrorBmp )
//STRIP001  {
//STRIP001      ppRet = &pErrorBmp;
//STRIP001      nResId = RID_GRAPHIC_ERRORBMP;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      ppRet = &pReplaceBmp;
//STRIP001      nResId = RID_GRAPHIC_REPLACEBMP;
//STRIP001  }
//STRIP001
//STRIP001  if( !*ppRet )
//STRIP001      *ppRet = new Bitmap( SW_RES( nResId ) );
//STRIP001  return **ppRet;
//STRIP001 }

/*************************************************************************
|*
|*    SwGrfFrm::SwGrfFrm(ViewShell * const,SwGrfNode *)
|*
|*    Beschreibung
|*    Ersterstellung    JP 05.03.91
|*    Letzte Aenderung  MA 03. Mar. 93
|*
*************************************************************************/


/*N*/ SwNoTxtFrm::SwNoTxtFrm(SwNoTxtNode * const pNode)
/*N*/   : SwCntntFrm(pNode)
/*N*/ {
/*N*/   InitCtor();
/*N*/ }

// Initialisierung: z.Zt. Eintragen des Frames im Cache


/*N*/ void SwNoTxtFrm::InitCtor()
/*N*/ {
/*N*/     nType = FRMC_NOTXT;
/*N*/   // Das Gewicht der Grafik ist 0, wenn sie noch nicht
/*N*/   // gelesen ist, < 0, wenn ein Lesefehler auftrat und
/*N*/   // Ersatzdarstellung angewendet werden musste und >0,
/*N*/   // wenn sie zur Verfuegung steht.
/*N*/   nWeight = 0;
/*N*/ }

/*************************************************************************
|*
|*    SwNoTxtNode::MakeFrm()
|*
|*    Beschreibung
|*    Ersterstellung    JP 05.03.91
|*    Letzte Aenderung  MA 03. Mar. 93
|*
*************************************************************************/


/*N*/ SwCntntFrm *SwNoTxtNode::MakeFrm()
/*N*/ {
/*N*/   return new SwNoTxtFrm(this);
/*N*/ }

/*************************************************************************
|*
|*    SwNoTxtFrm::~SwNoTxtFrm()
|*
|*    Beschreibung
|*    Ersterstellung    JP 05.03.91
|*    Letzte Aenderung  MA 30. Apr. 96
|*
*************************************************************************/

/*N*/ SwNoTxtFrm::~SwNoTxtFrm()
/*N*/ {
/*N*/   StopAnimation();
/*N*/ }

/*************************************************************************
|*
|*    void SwNoTxtFrm::Modify( SwHint * pOld, SwHint * pNew )
|*
|*    Beschreibung
|*    Ersterstellung    JP 05.03.91
|*    Letzte Aenderung  JP 05.03.91
|*
*************************************************************************/

//STRIP001 void SetOutDev( ViewShell *pSh, OutputDevice *pOut )
//STRIP001 {
//STRIP001  pSh->pOut = pOut;
//STRIP001 }




//STRIP001 void lcl_ClearArea( const SwFrm &rFrm,
//STRIP001                  OutputDevice &rOut, const SwRect& rPtArea,
//STRIP001                  const SwRect &rGrfArea, BOOL bIsOLE )
//STRIP001 {
//STRIP001  SwRegionRects aRegion( rPtArea, 4, 4 );
//STRIP001  aRegion -= rGrfArea;
//STRIP001
//STRIP001  if ( aRegion.Count() )
//STRIP001  {
//STRIP001      const SvxBrushItem *pItem; const Color *pCol; SwRect aOrigRect;
//STRIP001      if ( rFrm.GetBackgroundBrush( pItem, pCol, aOrigRect, FALSE ) )
//STRIP001          for( USHORT i = 0; i < aRegion.Count(); ++i )
//STRIP001              ::DrawGraphic( pItem, &rOut, aOrigRect, aRegion[i] );
//STRIP001      else
//STRIP001      {
//STRIP001          rOut.Push( PUSH_FILLCOLOR );
//STRIP001          rOut.SetFillColor( rFrm.GetShell()->Imp()->GetRetoucheColor());
//STRIP001          for( USHORT i = 0; i < aRegion.Count(); ++i )
//STRIP001              rOut.DrawRect( aRegion[i].SVRect() );
//STRIP001          rOut.Pop();
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|*    void SwNoTxtFrm::Paint()
|*
|*    Beschreibung
|*    Ersterstellung    JP 05.03.91
|*    Letzte Aenderung  MA 10. Jan. 97
|*
*************************************************************************/

/*N*/ void SwNoTxtFrm::Paint( const SwRect &rRect ) const
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  if ( Frm().IsEmpty() )
//STRIP001      return;
//STRIP001
//STRIP001  const ViewShell* pSh = GetShell();
//STRIP001  if( !pSh->GetViewOptions()->IsGraphic() )
//STRIP001  {
//STRIP001      StopAnimation();
//STRIP001          // OD 10.01.2003 #i6467# - no paint of placeholder for page preview
//STRIP001      if ( pSh->GetWin() && !pSh->IsPreView() )
//STRIP001      {
//STRIP001          const SwNoTxtNode* pNd = GetNode()->GetNoTxtNode();
//STRIP001          String aTxt( pNd->GetAlternateText() );
//STRIP001          if ( !aTxt.Len() && pNd->IsGrfNode() )
//STRIP001              GetRealURL( *(SwGrfNode*)pNd, aTxt );
//STRIP001          if( !aTxt.Len() )
//STRIP001              aTxt = FindFlyFrm()->GetFmt()->GetName();
//STRIP001          lcl_PaintReplacement( Frm(), aTxt, *pSh, this, FALSE );
//STRIP001      }
//STRIP001      return;
//STRIP001  }
//STRIP001        if( pSh->GetAccessibilityOptions()->IsStopAnimatedGraphics() )
//STRIP001         StopAnimation();
//STRIP001
//STRIP001  if ( pSh->Imp()->IsPaintInScroll() && pSh->GetWin() && rRect != Frm() &&
//STRIP001       HasAnimation() )
//STRIP001  {
//STRIP001      pSh->GetWin()->Invalidate( Frm().SVRect() );
//STRIP001      return;
//STRIP001  }
//STRIP001
//STRIP001
//STRIP001  SfxProgress::EnterLock(); //Keine Progress-Reschedules im Paint (SwapIn)
//STRIP001
//STRIP001  OutputDevice *pOut = pSh->GetOut();
//STRIP001  pOut->Push();
//STRIP001  BOOL bClip = TRUE;
//STRIP001  PolyPolygon aPoly;
//STRIP001
//STRIP001     SwNoTxtNode& rNoTNd = *(SwNoTxtNode*)GetNode();
//STRIP001  SwGrfNode* pGrfNd = rNoTNd.GetGrfNode();
//STRIP001     if( pGrfNd )
//STRIP001      pGrfNd->SetFrameInPaint( TRUE );
//STRIP001
//STRIP001      // OD 16.04.2003 #i13147# - add 2nd parameter with value <sal_True> to
//STRIP001     // method call <FindFlyFrm().GetContour(..)> to indicate that it is called
//STRIP001     // for paint in order to avoid load of the intrinsic graphic.
//STRIP001     if ( ( !pOut->GetConnectMetaFile() ||
//STRIP001            !pSh->GetWin() ) &&
//STRIP001          FindFlyFrm()->GetContour( aPoly, sal_True )
//STRIP001        )
//STRIP001  {
//STRIP001      pOut->SetClipRegion( aPoly );
//STRIP001      bClip = FALSE;
//STRIP001  }
//STRIP001
//STRIP001  SwRect aOrigPaint( rRect );
//STRIP001  if ( HasAnimation() && pSh->GetWin() )
//STRIP001  {
//STRIP001      aOrigPaint = Frm(); aOrigPaint += Prt().Pos();
//STRIP001  }
//STRIP001
//STRIP001  SwRect aGrfArea( Frm() );
//STRIP001  SwRect aPaintArea( aGrfArea );
//STRIP001  aPaintArea._Intersection( aOrigPaint );
//STRIP001
//STRIP001  SwRect aNormal( Frm().Pos() + Prt().Pos(), Prt().SSize() );
//STRIP001  aNormal.Justify(); //Normalisiertes Rechteck fuer die Vergleiche
//STRIP001
//STRIP001  BOOL bIsOleNode = GetNode()->IsOLENode();
//STRIP001  if( aPaintArea.IsOver( aNormal ) )
//STRIP001  {
//STRIP001      // berechne die 4 zu loeschenden Rechtecke
//STRIP001      if( pSh->GetWin() )
//STRIP001          ::lcl_ClearArea( *this, *pSh->GetOut(), aPaintArea, aNormal,
//STRIP001                          bIsOleNode );
//STRIP001
//STRIP001      // in der Schnittmenge vom PaintBereich und der Bitmap liegt
//STRIP001      // der absolut sichtbare Bereich vom Frame
//STRIP001      aPaintArea._Intersection( aNormal );
//STRIP001
//STRIP001      if ( bClip )
//STRIP001          pOut->IntersectClipRegion( aPaintArea.SVRect() );
//STRIP001         /// OD 25.09.2002 #99739# - delete unused 3rd parameter
//STRIP001         PaintPicture( pOut, aGrfArea );
//STRIP001  }
//STRIP001  else
//STRIP001      // wenn nicht sichtbar, loesche einfach den angegebenen Bereich
//STRIP001      lcl_ClearArea( *this, *pSh->GetOut(), aPaintArea, SwRect(),
//STRIP001                      bIsOleNode );
//STRIP001     if( pGrfNd )
//STRIP001      pGrfNd->SetFrameInPaint( FALSE );
//STRIP001
//STRIP001  pOut->Pop();
//STRIP001  SfxProgress::LeaveLock();
/*N*/ }

/*************************************************************************
|*
|*    void lcl_CalcRect( Point & aPt, Size & aDim,
|*                   USHORT nMirror )
|*
|*    Beschreibung      Errechne die Position und die Groesse der Grafik im
|*                      Frame, entsprechen der aktuellen Grafik-Attribute
|*
|*    Parameter         Point&  die Position im Frame  ( auch Return-Wert )
|*                      Size&   die Groesse der Grafik ( auch Return-Wert )
|*                      MirrorGrf   akt. Spiegelungs-Attribut
|*    Ersterstellung    JP 04.03.91
|*    Letzte Aenderung  JP 31.08.94
|*
*************************************************************************/


//STRIP001 void lcl_CalcRect( Point& rPt, Size& rDim, USHORT nMirror )
//STRIP001 {
//STRIP001     if( nMirror == RES_MIRROR_GRF_VERT || nMirror == RES_MIRROR_GRF_BOTH )
//STRIP001     {
//STRIP001         rPt.X() += rDim.Width() -1;
//STRIP001         rDim.Width() = -rDim.Width();
//STRIP001     }
//STRIP001
//STRIP001     if( nMirror == RES_MIRROR_GRF_HOR || nMirror == RES_MIRROR_GRF_BOTH )
//STRIP001     {
//STRIP001         rPt.Y() += rDim.Height() -1;
//STRIP001         rDim.Height() = -rDim.Height();
//STRIP001     }
//STRIP001 }

/*************************************************************************
|*
|*    void SwNoTxtFrm::GetGrfArea()
|*
|*    Beschreibung      Errechne die Position und die Groesse der Bitmap
|*                      innerhalb des uebergebenem Rechtecks.
|*
|*    Ersterstellung    JP 03.09.91
|*    Letzte Aenderung  MA 11. Oct. 94
|*
*************************************************************************/

//STRIP001 void SwNoTxtFrm::GetGrfArea( SwRect &rRect, SwRect* pOrigRect,
//STRIP001                           BOOL ) const
//STRIP001 {
//STRIP001     // JP 23.01.2001: currently only used for scaling, cropping and mirroring
//STRIP001     // the contour of graphics!
//STRIP001  //                  all other is handled by the GraphicObject
//STRIP001
//STRIP001  //In rRect wird das sichbare Rechteck der Grafik gesteckt.
//STRIP001  //In pOrigRect werden Pos+Size der Gesamtgrafik gesteck.
//STRIP001
//STRIP001  const SwAttrSet& rAttrSet = GetNode()->GetSwAttrSet();
//STRIP001  const SwCropGrf& rCrop = rAttrSet.GetCropGrf();
//STRIP001     USHORT nMirror = rAttrSet.GetMirrorGrf().GetValue();
//STRIP001
//STRIP001     if( rAttrSet.GetMirrorGrf().IsGrfToggle() )
//STRIP001     {
//STRIP001         if( !(FindPageFrm()->GetVirtPageNum() % 2) )
//STRIP001         {
//STRIP001             switch ( nMirror )
//STRIP001             {
//STRIP001                 case RES_DONT_MIRROR_GRF: nMirror = RES_MIRROR_GRF_VERT; break;
//STRIP001                 case RES_MIRROR_GRF_VERT: nMirror = RES_DONT_MIRROR_GRF; break;
//STRIP001                 case RES_MIRROR_GRF_HOR: nMirror = RES_MIRROR_GRF_BOTH; break;
//STRIP001                 default: nMirror = RES_MIRROR_GRF_HOR; break;
//STRIP001             }
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001  //Grafik wird vom Node eingelesen falls notwendig. Kann aber schiefgehen.
//STRIP001  long nLeftCrop, nRightCrop, nTopCrop, nBottomCrop;
//STRIP001  Size aOrigSz( ((SwNoTxtNode*)GetNode())->GetTwipSize() );
//STRIP001  if ( !aOrigSz.Width() )
//STRIP001  {
//STRIP001      aOrigSz.Width() = Prt().Width();
//STRIP001      nLeftCrop  = -rCrop.GetLeft();
//STRIP001      nRightCrop = -rCrop.GetRight();
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      nLeftCrop = Max( aOrigSz.Width() -
//STRIP001                          (rCrop.GetRight() + rCrop.GetLeft()), long(1) );
//STRIP001      const double nScale = double(Prt().Width())  / double(nLeftCrop);
//STRIP001      nLeftCrop  = long(nScale * -rCrop.GetLeft() );
//STRIP001      nRightCrop = long(nScale * -rCrop.GetRight() );
//STRIP001  }
//STRIP001
//STRIP001     // crop values have to be mirrored too
//STRIP001     if( nMirror == RES_MIRROR_GRF_VERT || nMirror == RES_MIRROR_GRF_BOTH )
//STRIP001     {
//STRIP001         long nTmpCrop = nLeftCrop;
//STRIP001         nLeftCrop = nRightCrop;
//STRIP001         nRightCrop= nTmpCrop;
//STRIP001     }
//STRIP001
//STRIP001  if( !aOrigSz.Height() )
//STRIP001  {
//STRIP001      aOrigSz.Height() = Prt().Height();
//STRIP001      nTopCrop   = -rCrop.GetTop();
//STRIP001      nBottomCrop= -rCrop.GetBottom();
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      nTopCrop = Max( aOrigSz.Height() - (rCrop.GetTop() + rCrop.GetBottom()), long(1) );
//STRIP001      const double nScale = double(Prt().Height()) / double(nTopCrop);
//STRIP001      nTopCrop   = long(nScale * -rCrop.GetTop() );
//STRIP001      nBottomCrop= long(nScale * -rCrop.GetBottom() );
//STRIP001  }
//STRIP001
//STRIP001     // crop values have to be mirrored too
//STRIP001     if( nMirror == RES_MIRROR_GRF_HOR || nMirror == RES_MIRROR_GRF_BOTH )
//STRIP001     {
//STRIP001         long nTmpCrop = nTopCrop;
//STRIP001         nTopCrop   = nBottomCrop;
//STRIP001         nBottomCrop= nTmpCrop;
//STRIP001     }
//STRIP001
//STRIP001  Size  aVisSz( Prt().SSize() );
//STRIP001  Size  aGrfSz( aVisSz );
//STRIP001  Point aVisPt( Frm().Pos() + Prt().Pos() );
//STRIP001  Point aGrfPt( aVisPt );
//STRIP001
//STRIP001  //Erst das 'sichtbare' Rect einstellen.
//STRIP001  if ( nLeftCrop > 0 )
//STRIP001  {
//STRIP001      aVisPt.X()  += nLeftCrop;
//STRIP001      aVisSz.Width() -= nLeftCrop;
//STRIP001  }
//STRIP001  if ( nTopCrop > 0 )
//STRIP001  {
//STRIP001      aVisPt.Y()   += nTopCrop;
//STRIP001      aVisSz.Height() -= nTopCrop;
//STRIP001  }
//STRIP001  if ( nRightCrop > 0 )
//STRIP001      aVisSz.Width() -= nRightCrop;
//STRIP001  if ( nBottomCrop > 0 )
//STRIP001      aVisSz.Height() -= nBottomCrop;
//STRIP001
//STRIP001  rRect.Pos  ( aVisPt );
//STRIP001  rRect.SSize( aVisSz );
//STRIP001
//STRIP001  //Ggf. Die Gesamtgrafik berechnen
//STRIP001  if ( pOrigRect )
//STRIP001  {
//STRIP001      Size aTmpSz( aGrfSz );
//STRIP001      aGrfPt.X()    += nLeftCrop;
//STRIP001      aTmpSz.Width() -= nLeftCrop + nRightCrop;
//STRIP001      aGrfPt.Y()      += nTopCrop;
//STRIP001      aTmpSz.Height()-= nTopCrop + nBottomCrop;
//STRIP001
//STRIP001         if( RES_DONT_MIRROR_GRF != nMirror )
//STRIP001             lcl_CalcRect( aGrfPt, aTmpSz, nMirror );
//STRIP001
//STRIP001      pOrigRect->Pos  ( aGrfPt );
//STRIP001      pOrigRect->SSize( aTmpSz );
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|*    Size SwNoTxtFrm::GetSize()
|*
|*    Beschreibung      Gebe die Groesse des umgebenen FLys und
|*                      damit die der Grafik zurueck.
|*    Ersterstellung    JP 04.03.91
|*    Letzte Aenderung  JP 31.08.94
|*
*************************************************************************/


/*N*/ const Size& SwNoTxtFrm::GetSize() const
/*N*/ {
/*N*/   // gebe die Groesse des Frames zurueck
/*N*/   const SwFrm *pFly = FindFlyFrm();
/*N*/   if( !pFly )
/*?*/       pFly = this;
/*N*/   return pFly->Prt().SSize();
/*N*/ }

/*************************************************************************
|*
|*    SwNoTxtFrm::MakeAll()
|*
|*    Ersterstellung    MA 29. Nov. 96
|*    Letzte Aenderung  MA 29. Nov. 96
|*
*************************************************************************/


/*N*/ void SwNoTxtFrm::MakeAll()
/*N*/ {
/*N*/   SwCntntNotify aNotify( this );
/*N*/   SwBorderAttrAccess aAccess( SwFrm::GetCache(), this );
/*N*/   const SwBorderAttrs &rAttrs = *aAccess.Get();
/*N*/
/*N*/   while ( !bValidPos || !bValidSize || !bValidPrtArea )
/*N*/   {
/*N*/       MakePos();
/*N*/
/*N*/       if ( !bValidSize )
/*N*/           Frm().Width( GetUpper()->Prt().Width() );
/*N*/
/*N*/       MakePrtArea( rAttrs );
/*N*/
/*N*/       if ( !bValidSize )
/*N*/       {   bValidSize = TRUE;
/*N*/           Format();
/*N*/       }
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|*    SwNoTxtFrm::Format()
|*
|*    Beschreibung      Errechne die Groesse der Bitmap, wenn noetig
|*    Ersterstellung    JP 11.03.91
|*    Letzte Aenderung  MA 13. Mar. 96
|*
*************************************************************************/


/*M*/ void SwNoTxtFrm::Format( const SwBorderAttrs * )
/*M*/ {
/*M*/   const Size aNewSize( GetSize() );
/*M*/
/*M*/   // hat sich die Hoehe geaendert?
/*M*/   SwTwips nChgHght = IsVertical() ?
/*M*/       (SwTwips)(aNewSize.Width() - Prt().Width()) :
/*M*/       (SwTwips)(aNewSize.Height() - Prt().Height());
/*M*/ #ifdef VERTICAL_LAYOUT
/*M*/   if( nChgHght > 0)
/*M*/         Grow( nChgHght );
/*M*/   else if( nChgHght < 0)
/*M*/         Shrink( Min(Prt().Height(), -nChgHght) );
/*M*/ #else
/*M*/   const SzPtr pVar = pVARSIZE;
/*M*/   if( nChgHght > 0)
/*M*/       Grow( nChgHght, pVar );
/*M*/   else if( nChgHght < 0)
/*M*/       Shrink( Min(Prt().Height(), -nChgHght), pVar );
/*M*/ #endif
/*M*/ }

/*************************************************************************
|*
|*    SwNoTxtFrm::GetCharRect()
|*
|*    Beschreibung
|*    Ersterstellung    SS 29-Apr-1991
|*    Letzte Aenderung  MA 10. Oct. 94
|*
|*************************************************************************/


/*N*/ BOOL SwNoTxtFrm::GetCharRect( SwRect &rRect, const SwPosition& rPos,
/*N*/                             SwCrsrMoveState *pCMS ) const
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  if ( &rPos.nNode.GetNode() != (SwNode*)GetNode() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  Calc();
//STRIP001  SwRect aFrameRect( Frm() );
//STRIP001  rRect = aFrameRect;
//STRIP001  rRect.Pos( Frm().Pos() + Prt().Pos() );
//STRIP001  rRect.SSize( Prt().SSize() );
//STRIP001
//STRIP001  rRect.Justify();
//STRIP001
//STRIP001  // liegt die Bitmap ueberhaupt im sichtbaren Berich ?
//STRIP001  if( !aFrameRect.IsOver( rRect ) )
//STRIP001  {
//STRIP001      // wenn nicht dann steht der Cursor auf dem Frame
//STRIP001      rRect = aFrameRect;
//STRIP001      rRect.Width( 1 );
//STRIP001  }
//STRIP001  else
//STRIP001      rRect._Intersection( aFrameRect );
//STRIP001
//STRIP001  if ( pCMS )
//STRIP001  {
//STRIP001      if ( pCMS->bRealHeight )
//STRIP001      {
//STRIP001          pCMS->aRealHeight.Y() = rRect.Height();
//STRIP001          pCMS->aRealHeight.X() = 0;
//STRIP001      }
//STRIP001  }
//STRIP001
/*N*/   return TRUE;
/*N*/ }


/*N*/ BOOL SwNoTxtFrm::GetCrsrOfst(SwPosition* pPos, Point& aPoint,
/*N*/                           const SwCrsrMoveState* ) const
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  SwCntntNode* pCNd = (SwCntntNode*)GetNode();
//STRIP001  pPos->nNode = *pCNd;
//STRIP001  pPos->nContent.Assign( pCNd, 0 );
/*N*/   return TRUE;
/*N*/ }

/*N*/ #define CLEARCACHE( pNd ) {\
/*N*/   (pNd)->GetGrfObj().ReleaseFromCache();\
/*N*/   SwFlyFrm* pFly = FindFlyFrm();\
/*N*/   if( pFly && pFly->GetFmt()->GetSurround().IsContour() )\
/*N*/   {\
/*N*/       ClrContourCache( pFly->GetVirtDrawObj() );\
/*N*/       pFly->NotifyBackground( FindPageFrm(), Prt(), PREP_FLY_ATTR_CHG );\
/*N*/   }\
/*N*/ }

/*N*/ void SwNoTxtFrm::Modify( SfxPoolItem* pOld, SfxPoolItem* pNew )
/*N*/ {
/*N*/   USHORT nWhich = pNew ? pNew->Which() : pOld ? pOld->Which() : 0;
/*N*/
/*N*/   if ( RES_GRAPHIC_PIECE_ARRIVED != nWhich &&
/*N*/        RES_GRAPHIC_ARRIVED != nWhich &&
/*N*/        RES_GRF_REREAD_AND_INCACHE != nWhich )
/*N*/       SwCntntFrm::Modify( pOld, pNew );
/*N*/
/*N*/   FASTBOOL bCompletePaint = TRUE;
/*N*/
/*N*/   switch( nWhich )
/*N*/   {
/*N*/   case RES_OBJECTDYING:
/*N*/       break;
/*N*/
/*?*/   case RES_GRF_REREAD_AND_INCACHE:
/*?*/       if( ND_GRFNODE == GetNode()->GetNodeType() )
/*?*/       {
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001   bCompletePaint = FALSE;
//STRIP001 /*?*/            SwGrfNode* pNd = (SwGrfNode*) GetNode();
//STRIP001 /*?*/
//STRIP001 /*?*/            ViewShell *pVSh = 0;
//STRIP001 /*?*/            pNd->GetDoc()->GetEditShell( &pVSh );
//STRIP001 /*?*/            if( pVSh )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                GraphicAttr aAttr;
//STRIP001 /*?*/                if( pNd->GetGrfObj().IsCached( pVSh->GetOut(), Point(),
//STRIP001 /*?*/                            Prt().SSize(), &pNd->GetGraphicAttr( aAttr, this ) ))
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    ViewShell *pSh = pVSh;
//STRIP001 /*?*/                    do {
//STRIP001 /*?*/                        SET_CURR_SHELL( pSh );
//STRIP001 /*?*/                        if( pSh->GetWin() )
//STRIP001 /*?*/                        {
//STRIP001 /*?*/                            if( pSh->IsPreView() )
//STRIP001 /*?*/                                ::RepaintPagePreview( pSh, Frm().SVRect() );
//STRIP001 /*?*/                            else
//STRIP001 /*?*/                                pSh->GetWin()->Invalidate( Frm().SVRect() );
//STRIP001 /*?*/                        }
//STRIP001 /*?*/                    } while( pVSh != (pSh = (ViewShell*)pSh->GetNext() ));
//STRIP001 /*?*/                }
//STRIP001 /*?*/                else
//STRIP001 /*?*/                    pNd->SwapIn();
//STRIP001 /*?*/            }
/*?*/       }
/*?*/       break;
/*?*/
/*N*/   case RES_UPDATE_ATTR:
/*N*/   case RES_FMT_CHG:
/*N*/       CLEARCACHE( (SwGrfNode*) GetNode() )
/*N*/       break;
/*N*/
/*N*/   case RES_ATTRSET_CHG:
/*N*/       {
                USHORT n;
/*N*/           for( n = RES_GRFATR_BEGIN; n < RES_GRFATR_END; ++n )
/*N*/               if( SFX_ITEM_SET == ((SwAttrSetChg*)pOld)->GetChgSet()->
/*N*/                               GetItemState( n, FALSE ))
/*N*/               {
/*N*/                   CLEARCACHE( (SwGrfNode*) GetNode() )
/*N*/                   break;
/*N*/               }
/*N*/           if( RES_GRFATR_END == n )           // not found
/*N*/               return ;
/*N*/       }
/*N*/       break;
/*N*/
/*N*/   case RES_GRAPHIC_PIECE_ARRIVED:
/*N*/   case RES_GRAPHIC_ARRIVED:
/*N*/       if ( GetNode()->GetNodeType() == ND_GRFNODE )
/*N*/       {
/*N*/           bCompletePaint = FALSE;
/*N*/           SwGrfNode* pNd = (SwGrfNode*) GetNode();
/*N*/
/*N*/           CLEARCACHE( pNd )
/*N*/
/*N*/           SwRect aRect( Frm() );
/*N*/
/*N*/           ViewShell *pVSh = 0;
/*N*/           pNd->GetDoc()->GetEditShell( &pVSh );
/*N*/             if( !pVSh )
/*N*/               break;
/*N*/
/*N*/           ViewShell *pSh = pVSh;
/*N*/           do {
/*N*/               SET_CURR_SHELL( pSh );
/*N*/               if( pSh->IsPreView() )
/*N*/               {
/*?*/                   if( pSh->GetWin() )
/*?*/                       ::binfilter::RepaintPagePreview( pSh, aRect );
/*?*/               }
/*?*/               else if ( pSh->VisArea().IsOver( aRect ) &&
/*?*/                    OUTDEV_WINDOW == pSh->GetOut()->GetOutDevType() )
/*?*/               {
/*?*/                     // OD 27.11.2002 #105519# - invalidate instead of painting
/*?*/                     pSh->GetWin()->Invalidate( aRect.SVRect() );
/*?*/               }
/*N*/
/*N*/               pSh = (ViewShell *)pSh->GetNext();
/*N*/           } while( pSh != pVSh );
/*N*/       }
/*N*/       break;
/*N*/
/*N*/   default:
/*?*/       if( !pNew || RES_GRFATR_BEGIN > nWhich || nWhich >= RES_GRFATR_END )
/*?*/           return;
/*N*/   }
/*N*/
/*N*/   if( bCompletePaint )
/*N*/   {
/*N*/       InvalidatePrt();
/*N*/       SetCompletePaint();
/*N*/   }
/*N*/ }

// Ausgabe der Grafik. Hier wird entweder eine QuickDraw-Bmp oder
// eine Grafik vorausgesetzt. Ist nichts davon vorhanden, wird
// eine Ersatzdarstellung ausgegeben.
/// OD 25.09.2002 #99739# - delete unused 3rd parameter.
/// OD 25.09.2002 #99739# - use aligned rectangle for drawing graphic.
/// OD 25.09.2002 #99739# - pixel-align coordinations for drawing graphic.
//STRIP001 void SwNoTxtFrm::PaintPicture( OutputDevice* pOut, const SwRect &rGrfArea ) const
//STRIP001 {
//STRIP001  ViewShell* pShell = GetShell();
//STRIP001  const FASTBOOL bPrn = pOut == pShell->GetPrt() ||
//STRIP001                        pOut->GetConnectMetaFile();
//STRIP001
//STRIP001  SwNoTxtNode& rNoTNd = *(SwNoTxtNode*)GetNode();
//STRIP001  SwGrfNode* pGrfNd = rNoTNd.GetGrfNode();
//STRIP001  SwOLENode* pOLENd = rNoTNd.GetOLENode();
//STRIP001
//STRIP001     /// OD 25.09.2002 #99739# - calculate aligned rectangle from parameter <rGrfArea>.
//STRIP001     ///     Use aligned rectangle <aAlignedGrfArea> instead of <rGrfArea> in
//STRIP001     ///     the following code.
//STRIP001     SwRect aAlignedGrfArea = rGrfArea;
//STRIP001     ::SwAlignRect( aAlignedGrfArea,  pShell );
//STRIP001     /// OD 25.09.2002 #99739#
//STRIP001     /// Because for drawing a graphic left-top-corner and size coordinations are
//STRIP001     /// used, these coordinations have to be determined on pixel level.
//STRIP001     ::SwAlignGrfRect( &aAlignedGrfArea, *pOut );
//STRIP001
//STRIP001     if( pGrfNd )
//STRIP001  {
//STRIP001      FASTBOOL bForceSwap = FALSE, bContinue = TRUE;
//STRIP001      GraphicObject& rGrfObj = pGrfNd->GetGrfObj();
//STRIP001
//STRIP001      GraphicAttr aGrfAttr;
//STRIP001      pGrfNd->GetGraphicAttr( aGrfAttr, this );
//STRIP001
//STRIP001      if( !bPrn )
//STRIP001      {
//STRIP001          if( GRAPHIC_DEFAULT == rGrfObj.GetType() &&
//STRIP001              pGrfNd->IsLinkedFile() )
//STRIP001          {
//STRIP001              Size aTmpSz;
//STRIP001              ::so3::SvLinkSource* pGrfObj = pGrfNd->GetLink()->GetObj();
//STRIP001              if( !pGrfObj ||
//STRIP001                  !pGrfObj->IsDataComplete() ||
//STRIP001                  !(aTmpSz = pGrfNd->GetTwipSize()).Width() ||
//STRIP001                  !aTmpSz.Height() || !pGrfNd->GetAutoFmtLvl() )
//STRIP001              {
//STRIP001                  pGrfNd->SetAutoFmtLvl( 1 );
//STRIP001                  new SwRequestGraphic( *GetShell(), *pGrfNd );//zerstoert sich selbst!
//STRIP001              }
//STRIP001              String aTxt( pGrfNd->GetAlternateText() );
//STRIP001              if ( !aTxt.Len() )
//STRIP001                  GetRealURL( *pGrfNd, aTxt );
//STRIP001                 ::lcl_PaintReplacement( aAlignedGrfArea, aTxt, *pShell, this, FALSE );
//STRIP001              bContinue = FALSE;
//STRIP001          }
//STRIP001             else if( rGrfObj.IsCached( pOut, aAlignedGrfArea.Pos(),
//STRIP001                                     aAlignedGrfArea.SSize(), &aGrfAttr ))
//STRIP001          {
//STRIP001                 rGrfObj.Draw( pOut, aAlignedGrfArea.Pos(), aAlignedGrfArea.SSize(),
//STRIP001                              &aGrfAttr );
//STRIP001              bContinue = FALSE;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      if( bContinue )
//STRIP001      {
//STRIP001          const FASTBOOL bSwapped = rGrfObj.IsSwappedOut();
//STRIP001          const FASTBOOL bSwappedIn = pGrfNd->SwapIn( bPrn );
//STRIP001          if( bSwappedIn && rGrfObj.GetGraphic().IsSupportedGraphic())
//STRIP001          {
//STRIP001              const FASTBOOL bAnimate = rGrfObj.IsAnimated() &&
//STRIP001                                             !pShell->IsPreView() &&
//STRIP001                             !pShell->GetAccessibilityOptions()->IsStopAnimatedGraphics();
//STRIP001              if( bAnimate &&
//STRIP001                  FindFlyFrm() != ::GetFlyFromMarked( 0, pShell ))
//STRIP001              {
//STRIP001                  OutputDevice* pVout;
//STRIP001                  if( pOut == pShell->GetOut() && SwRootFrm::FlushVout() )
//STRIP001                      pVout = pOut, pOut = pShell->GetOut();
//STRIP001                  else if( pShell->GetWin() &&
//STRIP001                           OUTDEV_VIRDEV == pOut->GetOutDevType() )
//STRIP001                      pVout = pOut, pOut = pShell->GetWin();
//STRIP001                  else
//STRIP001                      pVout = 0;
//STRIP001
//STRIP001                     ASSERT( OUTDEV_VIRDEV != pOut->GetOutDevType() ||
//STRIP001                             pShell->GetViewOptions()->IsPDFExport(),
//STRIP001                             "pOut sollte kein virtuelles Device sein" );
//STRIP001                     rGrfObj.StartAnimation( pOut, aAlignedGrfArea.Pos(),
//STRIP001                                         aAlignedGrfArea.SSize(), long(this),
//STRIP001                                      0, GRFMGR_DRAW_STANDARD, pVout );
//STRIP001              }
//STRIP001              else
//STRIP001                     rGrfObj.Draw( pOut, aAlignedGrfArea.Pos(), aAlignedGrfArea.SSize(),
//STRIP001                                  &aGrfAttr );
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              USHORT nResId = 0;
//STRIP001              if( bSwappedIn )
//STRIP001              {
//STRIP001                  if( GRAPHIC_NONE == rGrfObj.GetType() )
//STRIP001                      nResId = STR_COMCORE_READERROR;
//STRIP001                  else if ( !rGrfObj.GetGraphic().IsSupportedGraphic() )
//STRIP001                      nResId = STR_COMCORE_CANT_SHOW;
//STRIP001              }
//STRIP001              ((SwNoTxtFrm*)this)->nWeight = -1;
//STRIP001              String aText;
//STRIP001              if ( !nResId &&
//STRIP001                  !(aText = pGrfNd->GetAlternateText()).Len() &&
//STRIP001                   (!GetRealURL( *pGrfNd, aText ) || !aText.Len()))
//STRIP001              {
//STRIP001                  nResId = STR_COMCORE_READERROR;
//STRIP001              }
//STRIP001              if ( nResId )
//STRIP001                  aText = SW_RESSTR( nResId );
//STRIP001
//STRIP001                 ::lcl_PaintReplacement( aAlignedGrfArea, aText, *pShell, this, TRUE );
//STRIP001          }
//STRIP001
//STRIP001          //Beim Drucken duerfen wir nicht die Grafiken sammeln...
//STRIP001          if( bSwapped && bPrn )
//STRIP001              bForceSwap = TRUE;
//STRIP001      }
//STRIP001      if( bForceSwap )
//STRIP001          pGrfNd->SwapOut();
//STRIP001  }
//STRIP001  else if( pOLENd )
//STRIP001  {
//STRIP001      SvInPlaceObjectRef xRef( pOLENd->GetOLEObj().GetOleRef() );
//STRIP001
//STRIP001      // Im BrowseModus gibt es nicht unbedingt einen Drucker und
//STRIP001      // damit kein JobSetup, also legen wir eines an ...
//STRIP001      JobSetup* pJobSetup = (JobSetup*)pOLENd->GetDoc()->GetJobsetup();
//STRIP001      FASTBOOL bDummyJobSetup = 0 == pJobSetup;
//STRIP001      if( bDummyJobSetup )
//STRIP001          pJobSetup = new JobSetup();
//STRIP001         xRef->DoDraw( pOut, aAlignedGrfArea.Pos(), aAlignedGrfArea.SSize(), *pJobSetup );
//STRIP001      if( bDummyJobSetup )
//STRIP001          delete pJobSetup;  // ... und raeumen wieder auf.
//STRIP001
//STRIP001      //Objecte mit die beim Sichtbarwerden aktiviert werden wollen
//STRIP001      //werden jetzt Connected (Aktivieren wird vom Sfx erledigt).
//STRIP001      if( !bPrn && ((SVOBJ_MISCSTATUS_ACTIVATEWHENVISIBLE|
//STRIP001          SVOBJ_MISCSTATUS_ALWAYSACTIVATE) & xRef->GetMiscStatus()) &&
//STRIP001          pShell->ISA( SwCrsrShell ))
//STRIP001      {
//STRIP001          const SwFlyFrm *pFly = FindFlyFrm();
//STRIP001          ASSERT( pFly, "OLE not in FlyFrm" );
//STRIP001          ((SwFEShell*)pShell)->ConnectObj( xRef, pFly->Prt(), pFly->Frm());
//STRIP001      }
//STRIP001  }
//STRIP001 }


/*N*/ BOOL SwNoTxtFrm::IsTransparent() const
/*N*/ {
/*N*/   const ViewShell* pSh = GetShell();
/*N*/   if ( !pSh || !pSh->GetViewOptions()->IsGraphic() )
/*N*/       return TRUE;
/*N*/
/*N*/   const SwGrfNode *pNd;
/*N*/   if( 0 != (pNd = GetNode()->GetGrfNode()) )
/*N*/       return pNd->IsTransparent();
/*N*/
/*N*/   //#29381# OLE sind immer Transparent.
/*N*/   return TRUE;
/*N*/ }


/*N*/ void SwNoTxtFrm::StopAnimation( OutputDevice* pOut ) const
/*N*/ {
/*N*/   //animierte Grafiken anhalten
/*N*/   SwGrfNode* pGrfNd = (SwGrfNode*)GetNode()->GetGrfNode();
/*N*/   if( pGrfNd && pGrfNd->IsAnimated() )
/*N*/       pGrfNd->GetGrfObj().StopAnimation( pOut, long(this) );
/*N*/ }


/*N*/ BOOL SwNoTxtFrm::HasAnimation() const
/*N*/ {
/*N*/   const SwGrfNode* pGrfNd = GetNode()->GetGrfNode();
/*N*/   return pGrfNd && pGrfNd->IsAnimated();
/*N*/ }



}
