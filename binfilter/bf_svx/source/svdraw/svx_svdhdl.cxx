/*************************************************************************
 *
 *  $RCSfile: svx_svdhdl.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:46:13 $
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

#include "svdhdl.hxx"
#include "svdtouch.hxx"
#include "svdpagv.hxx"
#include "svdetc.hxx"
#include "svdmrkv.hxx"

#ifndef _WINDOW_HXX //autogen
#include <vcl/window.hxx>
#endif

#ifndef _VIRDEV_HXX //autogen
#include <vcl/virdev.hxx>
#endif

#ifndef _POLY_HXX //autogen
#include <vcl/poly.hxx>
#endif

#ifndef _SV_BMPACC_HXX
#include <vcl/bmpacc.hxx>
#endif

#ifndef _B2D_MTRI_HXX
#include <goodies/b2dmtri.hxx>
#endif

#ifndef _B3D_B3DCOLOR_HXX
#include <goodies/b3dcolor.hxx>
#endif

#include "sxekitm.hxx"
#include "sxesitm.hxx"
#include "svdstr.hrc"
#include "svdglob.hxx"

#include "svdmodel.hxx"
#include "gradtrns.hxx"
#include "xflgrit.hxx"
#include "svdundo.hxx"
#include "dialmgr.hxx"
#include "xflftrit.hxx"

// #105678#
#ifndef _SVDOPATH_HXX
#include "svdopath.hxx"
#endif
namespace binfilter {

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 class SdrHdlBitmapSet
//STRIP001 {
//STRIP001  BitmapEx                aRect_7x7[5];
//STRIP001  BitmapEx                aRect_9x9[5];
//STRIP001  BitmapEx                aRect_11x11[5];
//STRIP001  BitmapEx                aRect_13x13[5];
//STRIP001  BitmapEx                aCirc_7x7[5];
//STRIP001  BitmapEx                aCirc_9x9[5];
//STRIP001  BitmapEx                aCirc_11x11[5];
//STRIP001  BitmapEx                aElli_7x9[5];
//STRIP001  BitmapEx                aElli_9x11[5];
//STRIP001  BitmapEx                aElli_9x7[5];
//STRIP001  BitmapEx                aElli_11x9[5];
//STRIP001  BitmapEx                aRectPlus_7x7[5];
//STRIP001  BitmapEx                aRectPlus_9x9[5];
//STRIP001  BitmapEx                aRectPlus_11x11[5];
//STRIP001  BitmapEx                aCrosshair;
//STRIP001  BitmapEx                aGlue;
//STRIP001  BitmapEx                aAnchor;
//STRIP001  BitmapEx                aAnchorPressed;
//STRIP001
//STRIP001  void FillBitmapsFromResource(UINT16 nResId);
//STRIP001
//STRIP001 public:
//STRIP001  SdrHdlBitmapSet(UINT16 nResId);
//STRIP001  ~SdrHdlBitmapSet();
//STRIP001
//STRIP001  BitmapEx& GetBitmapEx(BitmapMarkerKind eKindOfMarker, UINT16 nInd=0);
//STRIP001 };

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 SdrHdlBitmapSet::SdrHdlBitmapSet(UINT16 nResId)
//STRIP001 {
//STRIP001  FillBitmapsFromResource(nResId);
//STRIP001 }

//STRIP001 SdrHdlBitmapSet::~SdrHdlBitmapSet()
//STRIP001 {
//STRIP001 }

//STRIP001 void SdrHdlBitmapSet::FillBitmapsFromResource(UINT16 nResId)
//STRIP001 {
//STRIP001  // #101928# change color used for transparent parts to 0x00ff00ff (ImageList standard)
//STRIP001  Color aColTransparent(0x00ff00ff);
//STRIP001  OutputDevice* pOut = Application::GetDefaultDevice();
//STRIP001  Bitmap aBitmap(ResId(nResId, ImpGetResMgr()));
//STRIP001  BitmapEx aMarkersBitmap(aBitmap, aColTransparent);
//STRIP001
//STRIP001  for(UINT16 a=0;a<5;a++)
//STRIP001  {
//STRIP001      UINT16 nYPos = a * 11;
//STRIP001
//STRIP001      aRect_7x7[a] = aMarkersBitmap; aRect_7x7[a].Crop(Rectangle(Point(0, nYPos), Size(7, 7)));
//STRIP001      aRect_7x7[a] = BitmapEx( aRect_7x7[a].GetBitmap().CreateDisplayBitmap( pOut ),
//STRIP001          aRect_7x7[a].GetMask().CreateDisplayBitmap( pOut ) );
//STRIP001
//STRIP001      aRect_9x9[a] = aMarkersBitmap; aRect_9x9[a].Crop(Rectangle(Point(7, nYPos), Size(9, 9)));
//STRIP001      aRect_9x9[a] = BitmapEx( aRect_9x9[a].GetBitmap().CreateDisplayBitmap( pOut ),
//STRIP001          aRect_9x9[a].GetMask().CreateDisplayBitmap( pOut ) );
//STRIP001
//STRIP001      aRect_11x11[a] = aMarkersBitmap; aRect_11x11[a].Crop(Rectangle(Point(16, nYPos), Size(11, 11)));
//STRIP001      aRect_11x11[a] = BitmapEx( aRect_11x11[a].GetBitmap().CreateDisplayBitmap( pOut ),
//STRIP001          aRect_11x11[a].GetMask().CreateDisplayBitmap( pOut ) );
//STRIP001
//STRIP001      aCirc_7x7[a] = aMarkersBitmap; aCirc_7x7[a].Crop(Rectangle(Point(27, nYPos), Size(7, 7)));
//STRIP001      aCirc_7x7[a] = BitmapEx( aCirc_7x7[a].GetBitmap().CreateDisplayBitmap( pOut ),
//STRIP001          aCirc_7x7[a].GetMask().CreateDisplayBitmap( pOut ) );
//STRIP001
//STRIP001      aCirc_9x9[a] = aMarkersBitmap; aCirc_9x9[a].Crop(Rectangle(Point(34, nYPos), Size(9, 9)));
//STRIP001      aCirc_9x9[a] = BitmapEx( aCirc_9x9[a].GetBitmap().CreateDisplayBitmap( pOut ),
//STRIP001          aCirc_9x9[a].GetMask().CreateDisplayBitmap( pOut ) );
//STRIP001
//STRIP001      aCirc_11x11[a] = aMarkersBitmap; aCirc_11x11[a].Crop(Rectangle(Point(43, nYPos), Size(11, 11)));
//STRIP001      aCirc_11x11[a] = BitmapEx( aCirc_11x11[a].GetBitmap().CreateDisplayBitmap( pOut ),
//STRIP001          aCirc_11x11[a].GetMask().CreateDisplayBitmap( pOut ) );
//STRIP001
//STRIP001      aElli_7x9[a] = aMarkersBitmap; aElli_7x9[a].Crop(Rectangle(Point(54, nYPos), Size(7, 9)));
//STRIP001      aElli_7x9[a] = BitmapEx( aElli_7x9[a].GetBitmap().CreateDisplayBitmap( pOut ),
//STRIP001          aElli_7x9[a].GetMask().CreateDisplayBitmap( pOut ) );
//STRIP001
//STRIP001      aElli_9x11[a] = aMarkersBitmap; aElli_9x11[a].Crop(Rectangle(Point(61, nYPos), Size(9, 11)));
//STRIP001      aElli_9x11[a] = BitmapEx( aElli_9x11[a].GetBitmap().CreateDisplayBitmap( pOut ),
//STRIP001          aElli_9x11[a].GetMask().CreateDisplayBitmap( pOut ) );
//STRIP001
//STRIP001      aElli_9x7[a] = aMarkersBitmap; aElli_9x7[a].Crop(Rectangle(Point(70, nYPos), Size(9, 7)));
//STRIP001      aElli_9x7[a] = BitmapEx( aElli_9x7[a].GetBitmap().CreateDisplayBitmap( pOut ),
//STRIP001          aElli_9x7[a].GetMask().CreateDisplayBitmap( pOut ) );
//STRIP001
//STRIP001      aElli_11x9[a] = aMarkersBitmap; aElli_11x9[a].Crop(Rectangle(Point(79, nYPos), Size(11, 9)));
//STRIP001      aElli_11x9[a] = BitmapEx( aElli_11x9[a].GetBitmap().CreateDisplayBitmap( pOut ),
//STRIP001          aElli_11x9[a].GetMask().CreateDisplayBitmap( pOut ) );
//STRIP001
//STRIP001      aRectPlus_7x7[a] = aMarkersBitmap; aRectPlus_7x7[a].Crop(Rectangle(Point(90, nYPos), Size(7, 7)));
//STRIP001      aRectPlus_7x7[a] = BitmapEx( aRectPlus_7x7[a].GetBitmap().CreateDisplayBitmap( pOut ),
//STRIP001          aRectPlus_7x7[a].GetMask().CreateDisplayBitmap( pOut ) );
//STRIP001
//STRIP001      aRectPlus_9x9[a] = aMarkersBitmap; aRectPlus_9x9[a].Crop(Rectangle(Point(97, nYPos), Size(9, 9)));
//STRIP001      aRectPlus_9x9[a] = BitmapEx( aRectPlus_9x9[a].GetBitmap().CreateDisplayBitmap( pOut ),
//STRIP001          aRectPlus_9x9[a].GetMask().CreateDisplayBitmap( pOut ) );
//STRIP001
//STRIP001      aRectPlus_11x11[a] = aMarkersBitmap; aRectPlus_11x11[a].Crop(Rectangle(Point(106, nYPos), Size(11, 11)));
//STRIP001      aRectPlus_11x11[a] = BitmapEx( aRectPlus_11x11[a].GetBitmap().CreateDisplayBitmap( pOut ),
//STRIP001          aRectPlus_11x11[a].GetMask().CreateDisplayBitmap( pOut ) );
//STRIP001  }
//STRIP001
//STRIP001  aRect_13x13[0] = aMarkersBitmap; aRect_13x13[0].Crop(Rectangle(Point(71, 53), Size(13, 13)));
//STRIP001  aRect_13x13[0] = BitmapEx( aRect_13x13[0].GetBitmap().CreateDisplayBitmap( pOut ),
//STRIP001      aRect_13x13[0].GetMask().CreateDisplayBitmap( pOut ) );
//STRIP001  aRect_13x13[1] = aMarkersBitmap; aRect_13x13[1].Crop(Rectangle(Point(85, 53), Size(13, 13)));
//STRIP001  aRect_13x13[1] = BitmapEx( aRect_13x13[1].GetBitmap().CreateDisplayBitmap( pOut ),
//STRIP001      aRect_13x13[1].GetMask().CreateDisplayBitmap( pOut ) );
//STRIP001  aRect_13x13[2] = aMarkersBitmap; aRect_13x13[2].Crop(Rectangle(Point(72, 65), Size(13, 13)));
//STRIP001  aRect_13x13[2] = BitmapEx( aRect_13x13[2].GetBitmap().CreateDisplayBitmap( pOut ),
//STRIP001      aRect_13x13[2].GetMask().CreateDisplayBitmap( pOut ) );
//STRIP001  aRect_13x13[3] = aMarkersBitmap; aRect_13x13[3].Crop(Rectangle(Point(85, 65), Size(13, 13)));
//STRIP001  aRect_13x13[3] = BitmapEx( aRect_13x13[3].GetBitmap().CreateDisplayBitmap( pOut ),
//STRIP001      aRect_13x13[3].GetMask().CreateDisplayBitmap( pOut ) );
//STRIP001  aRect_13x13[4] = aMarkersBitmap; aRect_13x13[4].Crop(Rectangle(Point(98, 65), Size(13, 13)));
//STRIP001  aRect_13x13[4] = BitmapEx( aRect_13x13[4].GetBitmap().CreateDisplayBitmap( pOut ),
//STRIP001      aRect_13x13[4].GetMask().CreateDisplayBitmap( pOut ) );
//STRIP001
//STRIP001  aCrosshair = aMarkersBitmap; aCrosshair.Crop(Rectangle(Point(0, 55), Size(15, 15)));
//STRIP001  aCrosshair = BitmapEx( aCrosshair.GetBitmap().CreateDisplayBitmap( pOut ),
//STRIP001      aCrosshair.GetMask().CreateDisplayBitmap( pOut ) );
//STRIP001
//STRIP001  aGlue = aMarkersBitmap; aGlue.Crop(Rectangle(Point(15, 61), Size(9, 9)));
//STRIP001  aGlue = BitmapEx( aGlue.GetBitmap().CreateDisplayBitmap( pOut ),
//STRIP001      aGlue.GetMask().CreateDisplayBitmap( pOut ) );
//STRIP001
//STRIP001  aAnchor = aMarkersBitmap; aAnchor.Crop(Rectangle(Point(24, 55), Size(24, 23)));
//STRIP001  aAnchor = BitmapEx( aAnchor.GetBitmap().CreateDisplayBitmap( pOut ),
//STRIP001      aAnchor.GetMask().CreateDisplayBitmap( pOut ) );
//STRIP001
//STRIP001  aAnchorPressed = aMarkersBitmap; aAnchorPressed.Crop(Rectangle(Point(48, 55), Size(24, 23)));
//STRIP001  aAnchorPressed = BitmapEx( aAnchorPressed.GetBitmap().CreateDisplayBitmap( pOut ),
//STRIP001      aAnchorPressed.GetMask().CreateDisplayBitmap( pOut ) );
//STRIP001 }

//STRIP001 BitmapEx& SdrHdlBitmapSet::GetBitmapEx(BitmapMarkerKind eKindOfMarker, UINT16 nInd)
//STRIP001 {
//STRIP001  switch(eKindOfMarker)
//STRIP001  {
//STRIP001      case Rect_7x7: return aRect_7x7[nInd]; break;
//STRIP001      case Rect_9x9: return aRect_9x9[nInd]; break;
//STRIP001      case Rect_11x11: return aRect_11x11[nInd]; break;
//STRIP001      case Rect_13x13: return aRect_13x13[nInd]; break;
//STRIP001      case Circ_7x7: return aCirc_7x7[nInd]; break;
//STRIP001      case Circ_9x9: return aCirc_9x9[nInd]; break;
//STRIP001      case Circ_11x11: return aCirc_11x11[nInd]; break;
//STRIP001      case Elli_7x9: return aElli_7x9[nInd]; break;
//STRIP001      case Elli_9x11: return aElli_9x11[nInd]; break;
//STRIP001      case Elli_9x7: return aElli_9x7[nInd]; break;
//STRIP001      case Elli_11x9: return aElli_11x9[nInd]; break;
//STRIP001      case RectPlus_7x7: return aRectPlus_7x7[nInd]; break;
//STRIP001      case RectPlus_9x9: return aRectPlus_9x9[nInd]; break;
//STRIP001      case RectPlus_11x11: return aRectPlus_11x11[nInd]; break;
//STRIP001      case Crosshair: return aCrosshair; break;
//STRIP001      case Glue: return aGlue; break;
//STRIP001      case Anchor: return aAnchor; break;
//STRIP001      // #98388# add AnchorPressed to be able to aninate anchor control
//STRIP001      case AnchorPressed: return aAnchorPressed; break;
//STRIP001
//STRIP001      // #101688# AnchorTR for SW
//STRIP001      case AnchorTR: return aAnchor; break;
//STRIP001      case AnchorPressedTR: return aAnchorPressed; break;
//STRIP001
//STRIP001      default: DBG_ERROR( "unknown kind of marker" ); return aRect_7x7[nInd]; break;
//STRIP001  }
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 SdrHdlBitmapSet* SdrHdl::pSimpleSet = NULL;
//STRIP001 SdrHdlBitmapSet* SdrHdl::pModernSet = NULL;

// #101928#
//STRIP001 SdrHdlBitmapSet* SdrHdl::pHighContrastSet = NULL;

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ SdrHdl::SdrHdl()//STRIP001 :
//STRIP001     pObj(NULL),
//STRIP001     pPV(NULL),
//STRIP001     pHdlList(NULL),
//STRIP001     nDrehWink(0),
//STRIP001     eKind(HDL_MOVE),
//STRIP001     bSelect(FALSE),
//STRIP001     b1PixMore(FALSE),
//STRIP001     nObjHdlNum(0),
//STRIP001     nPolyNum(0),
//STRIP001     nPPntNum(0),
//STRIP001     bPlusHdl(FALSE),
//STRIP001     nSourceHdlNum(0)
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  if(!pSimpleSet)
//STRIP001      pSimpleSet = new SdrHdlBitmapSet(SIP_SA_MARKERS);
//STRIP001  DBG_ASSERT(pSimpleSet, "Could not construct SdrHdlBitmapSet()!");
//STRIP001
//STRIP001  if(!pModernSet)
//STRIP001      pModernSet = new SdrHdlBitmapSet(SIP_SA_FINE_MARKERS);
//STRIP001  DBG_ASSERT(pModernSet, "Could not construct SdrHdlBitmapSet()!");
//STRIP001
//STRIP001  // #101928#
//STRIP001  if(!pHighContrastSet)
//STRIP001      pHighContrastSet = new SdrHdlBitmapSet(SIP_SA_ACCESSIBILITY_MARKERS);
//STRIP001  DBG_ASSERT(pHighContrastSet, "Could not construct SdrHdlBitmapSet()!");
/*N*/ }

/*N*/ SdrHdl::SdrHdl(const Point& rPnt, SdrHdlKind eNewKind)//STRIP001 :
//STRIP001     aPos(rPnt),
//STRIP001     pObj(NULL),
//STRIP001     pPV(NULL),
//STRIP001     pHdlList(NULL),
//STRIP001     nDrehWink(0),
//STRIP001     eKind(eNewKind),
//STRIP001     bSelect(FALSE),
//STRIP001     b1PixMore(FALSE),
//STRIP001     nObjHdlNum(0),
//STRIP001     nPolyNum(0),
//STRIP001     nPPntNum(0),
//STRIP001     bPlusHdl(FALSE),
//STRIP001     nSourceHdlNum(0)
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  if(!pSimpleSet)
//STRIP001      pSimpleSet = new SdrHdlBitmapSet(SIP_SA_MARKERS);
//STRIP001  DBG_ASSERT(pSimpleSet, "Could not construct SdrHdlBitmapSet()!");
//STRIP001
//STRIP001  if(!pModernSet)
//STRIP001      pModernSet = new SdrHdlBitmapSet(SIP_SA_FINE_MARKERS);
//STRIP001  DBG_ASSERT(pModernSet, "Could not construct SdrHdlBitmapSet()!");
//STRIP001
//STRIP001  // #101928#
//STRIP001  if(!pHighContrastSet)
//STRIP001      pHighContrastSet = new SdrHdlBitmapSet(SIP_SA_ACCESSIBILITY_MARKERS);
//STRIP001  DBG_ASSERT(pHighContrastSet, "Could not construct SdrHdlBitmapSet()!");
/*N*/ }

/*N*/ SdrHdl::~SdrHdl()
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  GetRidOfIAObject();
/*N*/ }

//STRIP001 void SdrHdl::Set1PixMore(BOOL bJa)
//STRIP001 {
//STRIP001  if(b1PixMore != bJa)
//STRIP001  {
//STRIP001      b1PixMore = bJa;
//STRIP001
//STRIP001      // create new display
//STRIP001      Touch();
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrHdl::SetDrehWink(long n)
//STRIP001 {
//STRIP001  if(nDrehWink != n)
//STRIP001  {
//STRIP001      nDrehWink = n;
//STRIP001
//STRIP001      // create new display
//STRIP001      Touch();
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrHdl::SetPos(const Point& rPnt)
//STRIP001 {
//STRIP001  if(aPos != rPnt)
//STRIP001  {
//STRIP001      // remember new position
//STRIP001      aPos = rPnt;
//STRIP001
//STRIP001      // create new display
//STRIP001      Touch();
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrHdl::SetSelected(BOOL bJa)
//STRIP001 {
//STRIP001  if(bSelect != bJa)
//STRIP001  {
//STRIP001      // remember new value
//STRIP001      bSelect = bJa;
//STRIP001
//STRIP001      // create new display
//STRIP001      Touch();
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrHdl::SetHdlList(SdrHdlList* pList)
//STRIP001 {
//STRIP001  if(pHdlList != pList)
//STRIP001  {
//STRIP001      // rememver list
//STRIP001      pHdlList = pList;
//STRIP001
//STRIP001      // now its possible to create graphic representation
//STRIP001      Touch();
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrHdl::SetObj(SdrObject* pNewObj)
//STRIP001 {
//STRIP001  if(pObj != pNewObj)
//STRIP001  {
//STRIP001      // remember new object
//STRIP001      pObj = pNewObj;
//STRIP001
//STRIP001      // graphic representation may have changed
//STRIP001      Touch();
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrHdl::Touch()
//STRIP001 {
//STRIP001  // force update of graphic representation
//STRIP001  CreateB2dIAObject();
//STRIP001 }

//STRIP001 void SdrHdl::GetRidOfIAObject()
//STRIP001 {
//STRIP001  aIAOGroup.Delete();
//STRIP001 }

//STRIP001 void SdrHdl::CreateB2dIAObject()
//STRIP001 {
//STRIP001  // first throw away old one
//STRIP001  GetRidOfIAObject();
//STRIP001
//STRIP001  if(pHdlList && pHdlList->GetView() && !pHdlList->GetView()->IsMarkHdlHidden())
//STRIP001  {
//STRIP001      BitmapColorIndex eColIndex = LightGreen;
//STRIP001      BitmapMarkerKind eKindOfMarker = Rect_7x7;
//STRIP001
//STRIP001         BOOL bRot = pHdlList->IsRotateShear();
//STRIP001         if(pObj)
//STRIP001             eColIndex = (bSelect) ? Cyan : LightCyan;
//STRIP001         if(bRot)
//STRIP001      {
//STRIP001          // Drehhandles in Rot
//STRIP001             if(pObj && bSelect)
//STRIP001              eColIndex = Red;
//STRIP001          else
//STRIP001              eColIndex = LightRed;
//STRIP001         }
//STRIP001
//STRIP001      switch(eKind)
//STRIP001      {
//STRIP001          case HDL_MOVE:
//STRIP001          {
//STRIP001              eKindOfMarker = (b1PixMore) ? Rect_9x9 : Rect_7x7;
//STRIP001              break;
//STRIP001          }
//STRIP001          case HDL_UPLFT:
//STRIP001          case HDL_UPRGT:
//STRIP001          case HDL_LWLFT:
//STRIP001          case HDL_LWRGT:
//STRIP001          {
//STRIP001              // corner handles
//STRIP001              if(bRot)
//STRIP001              {
//STRIP001                  eKindOfMarker = Circ_7x7;
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  eKindOfMarker = Rect_7x7;
//STRIP001              }
//STRIP001              break;
//STRIP001          }
//STRIP001          case HDL_UPPER:
//STRIP001          case HDL_LOWER:
//STRIP001          {
//STRIP001              // Upper/Lower handles
//STRIP001              if(bRot)
//STRIP001              {
//STRIP001                  eKindOfMarker = Elli_9x7;
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  eKindOfMarker = Rect_7x7;
//STRIP001              }
//STRIP001              break;
//STRIP001          }
//STRIP001          case HDL_LEFT:
//STRIP001          case HDL_RIGHT:
//STRIP001          {
//STRIP001              // Left/Right handles
//STRIP001              if(bRot)
//STRIP001              {
//STRIP001                  eKindOfMarker = Elli_7x9;
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  eKindOfMarker = Rect_7x7;
//STRIP001              }
//STRIP001              break;
//STRIP001          }
//STRIP001          case HDL_POLY:
//STRIP001          {
//STRIP001              if(bRot)
//STRIP001              {
//STRIP001                  eKindOfMarker = (b1PixMore) ? Circ_9x9 : Circ_7x7;
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  eKindOfMarker = (b1PixMore) ? Rect_9x9 : Rect_7x7;
//STRIP001              }
//STRIP001              break;
//STRIP001          }
//STRIP001          case HDL_BWGT: // weight at poly
//STRIP001          {
//STRIP001              eKindOfMarker = Circ_7x7;
//STRIP001              break;
//STRIP001          }
//STRIP001          case HDL_CIRC:
//STRIP001          {
//STRIP001              eKindOfMarker = Rect_11x11;
//STRIP001              break;
//STRIP001          }
//STRIP001          case HDL_REF1:
//STRIP001          case HDL_REF2:
//STRIP001          {
//STRIP001              eKindOfMarker = Crosshair;
//STRIP001              break;
//STRIP001          }
//STRIP001          case HDL_GLUE:
//STRIP001          {
//STRIP001              eKindOfMarker = Glue;
//STRIP001              break;
//STRIP001          }
//STRIP001          case HDL_ANCHOR:
//STRIP001          {
//STRIP001              eKindOfMarker = Anchor;
//STRIP001              break;
//STRIP001          }
//STRIP001          case HDL_USER:
//STRIP001          {
//STRIP001              break;
//STRIP001          }
//STRIP001          // #101688# top right anchor for SW
//STRIP001          case HDL_ANCHOR_TR:
//STRIP001          {
//STRIP001              eKindOfMarker = AnchorTR;
//STRIP001              break;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      for(UINT16 a=0;a<pHdlList->GetView()->GetWinCount();a++)
//STRIP001      {
//STRIP001          SdrViewWinRec& rRec = pHdlList->GetView()->GetWinRec(a);
//STRIP001          Point aMoveOutsideOffset(0, 0);
//STRIP001
//STRIP001          // add offset if necessary
//STRIP001          if(rRec.pWin && pHdlList->IsMoveOutside())
//STRIP001          {
//STRIP001              Size aOffset = rRec.pWin->PixelToLogic(Size(4, 4));
//STRIP001
//STRIP001              if(eKind == HDL_UPLFT || eKind == HDL_UPPER || eKind == HDL_UPRGT)
//STRIP001                  aMoveOutsideOffset.Y() -= aOffset.Width();
//STRIP001              if(eKind == HDL_LWLFT || eKind == HDL_LOWER || eKind == HDL_LWRGT)
//STRIP001                  aMoveOutsideOffset.Y() += aOffset.Height();
//STRIP001              if(eKind == HDL_UPLFT || eKind == HDL_LEFT  || eKind == HDL_LWLFT)
//STRIP001                  aMoveOutsideOffset.X() -= aOffset.Width();
//STRIP001              if(eKind == HDL_UPRGT || eKind == HDL_RIGHT || eKind == HDL_LWRGT)
//STRIP001                  aMoveOutsideOffset.X() += aOffset.Height();
//STRIP001          }
//STRIP001
//STRIP001          // Manager may be zero when printing or drawing to VDevs
//STRIP001          if(rRec.pIAOManager)
//STRIP001          {
//STRIP001              B2dIAObject* pNew = CreateMarkerObject(
//STRIP001                  rRec.pIAOManager,
//STRIP001                  aPos + aMoveOutsideOffset,
//STRIP001                  eColIndex,
//STRIP001                  eKindOfMarker);
//STRIP001
//STRIP001              if(pNew)
//STRIP001              {
//STRIP001                  // set as B2DIAObject
//STRIP001                  aIAOGroup.InsertIAO(pNew);
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 BitmapMarkerKind SdrHdl::GetNextBigger(BitmapMarkerKind eKnd) const
//STRIP001 {
//STRIP001  BitmapMarkerKind eRetval(eKnd);
//STRIP001
//STRIP001  switch(eKnd)
//STRIP001  {
//STRIP001      case Rect_7x7:          eRetval = Rect_9x9;         break;
//STRIP001      case Rect_9x9:          eRetval = Rect_11x11;       break;
//STRIP001      case Rect_11x11:        eRetval = Rect_13x13;       break;
//STRIP001      //case Rect_13x13:      eRetval = ; break;
//STRIP001
//STRIP001      case Circ_7x7:          eRetval = Circ_9x9;         break;
//STRIP001      case Circ_9x9:          eRetval = Circ_11x11;       break;
//STRIP001      //case Circ_11x11:      eRetval = ; break;
//STRIP001
//STRIP001      case Elli_7x9:          eRetval = Elli_9x11;        break;
//STRIP001      //case Elli_9x11:           eRetval = ; break;
//STRIP001
//STRIP001      case Elli_9x7:          eRetval = Elli_11x9;        break;
//STRIP001      //case Elli_11x9:           eRetval = ; break;
//STRIP001
//STRIP001      case RectPlus_7x7:      eRetval = RectPlus_9x9;     break;
//STRIP001      case RectPlus_9x9:      eRetval = RectPlus_11x11;   break;
//STRIP001      //case RectPlus_11x11:  eRetval = ; break;
//STRIP001
//STRIP001      //case Crosshair:           eRetval = ; break;
//STRIP001      //case Glue:                eRetval = ; break;
//STRIP001
//STRIP001      // #98388# let anchor blink with it's pressed state
//STRIP001      case Anchor:            eRetval = AnchorPressed;    break;
//STRIP001
//STRIP001      // #101688# same for AnchorTR
//STRIP001      case AnchorTR:          eRetval = AnchorPressedTR;  break;
//STRIP001  }
//STRIP001
//STRIP001  return eRetval;
//STRIP001 }

// #101928#
//STRIP001 BitmapEx& SdrHdl::ImpGetBitmapEx(BitmapMarkerKind eKindOfMarker, sal_uInt16 nInd, sal_Bool bFine, sal_Bool bIsHighContrast)
//STRIP001 {
//STRIP001  if(bIsHighContrast)
//STRIP001  {
//STRIP001      return pHighContrastSet->GetBitmapEx(eKindOfMarker, nInd);
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if(bFine)
//STRIP001      {
//STRIP001          return pModernSet->GetBitmapEx(eKindOfMarker, nInd);
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          return pSimpleSet->GetBitmapEx(eKindOfMarker, nInd);
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 B2dIAObject* SdrHdl::CreateMarkerObject(B2dIAOManager* pMan, Point aPos, BitmapColorIndex eColIndex, BitmapMarkerKind eKindOfMarker)
//STRIP001 {
//STRIP001  B2dIAObject* pRetval = 0L;
//STRIP001  sal_Bool bIsFineHdl(pHdlList->IsFineHdl());
//STRIP001  const StyleSettings& rStyleSettings = Application::GetSettings().GetStyleSettings();
//STRIP001  sal_Bool bIsHighContrast(rStyleSettings.GetHighContrastMode());
//STRIP001
//STRIP001  // support bigger sizes
//STRIP001  sal_Bool bForceBiggerSize(sal_False);
//STRIP001
//STRIP001  if(pHdlList->GetHdlSize() > 3)
//STRIP001  {
//STRIP001      bForceBiggerSize = sal_True;
//STRIP001  }
//STRIP001
//STRIP001  // #101928# ...for high contrast, too.
//STRIP001  if(!bForceBiggerSize && bIsHighContrast)
//STRIP001  {
//STRIP001      // #107925#
//STRIP001      // ...but not for anchors, else they will not blink when activated
//STRIP001      if(Anchor != eKindOfMarker && AnchorTR != eKindOfMarker)
//STRIP001      {
//STRIP001          bForceBiggerSize = sal_True;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if(bForceBiggerSize)
//STRIP001  {
//STRIP001      eKindOfMarker = GetNextBigger(eKindOfMarker);
//STRIP001  }
//STRIP001
//STRIP001  // #97016# II This handle has the focus, visualize it
//STRIP001  if(IsFocusHdl() && pHdlList && pHdlList->GetFocusHdl() == this)
//STRIP001  {
//STRIP001      // create animated handle
//STRIP001      BitmapMarkerKind eNextBigger = GetNextBigger(eKindOfMarker);
//STRIP001
//STRIP001      if(eNextBigger == eKindOfMarker)
//STRIP001      {
//STRIP001          // this may happen for the not supported getting-bigger types.
//STRIP001          // Choose an alternative here
//STRIP001          switch(eKindOfMarker)
//STRIP001          {
//STRIP001              case Rect_13x13:        eNextBigger = Rect_11x11;   break;
//STRIP001              case Circ_11x11:        eNextBigger = Elli_11x9;    break;
//STRIP001              case Elli_9x11:         eNextBigger = Elli_11x9;    break;
//STRIP001              case Elli_11x9:         eNextBigger = Elli_9x11;    break;
//STRIP001              case RectPlus_11x11:    eNextBigger = Rect_13x13;   break;
//STRIP001
//STRIP001              case Crosshair:
//STRIP001                  eNextBigger = Glue;
//STRIP001                  break;
//STRIP001
//STRIP001              case Glue:
//STRIP001                  eNextBigger = Crosshair;
//STRIP001                  break;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      // create animated hdl
//STRIP001      // #101928# use ImpGetBitmapEx(...) now
//STRIP001      BitmapEx& rBmpEx1 = ImpGetBitmapEx(eKindOfMarker, (sal_uInt16)eColIndex, bIsFineHdl, bIsHighContrast);
//STRIP001      BitmapEx& rBmpEx2 = ImpGetBitmapEx(eNextBigger, (sal_uInt16)eColIndex, bIsFineHdl, bIsHighContrast);
//STRIP001
//STRIP001      if(eKindOfMarker == Anchor || eKindOfMarker == AnchorPressed)
//STRIP001      {
//STRIP001          // #98388# when anchor is used take upper left as reference point inside the handle
//STRIP001          pRetval = new B2dIAOAnimBmapExRef(pMan, aPos, &rBmpEx1, &rBmpEx2);
//STRIP001      }
//STRIP001      else if(eKindOfMarker == AnchorTR || eKindOfMarker == AnchorPressedTR)
//STRIP001      {
//STRIP001          // #101688# AnchorTR for SW, take top right as (0,0)
//STRIP001          pRetval = new B2dIAOAnimBmapExRef(pMan, aPos, &rBmpEx1, &rBmpEx2,
//STRIP001              (UINT16)(rBmpEx1.GetSizePixel().Width() - 1), 0,
//STRIP001              (UINT16)(rBmpEx2.GetSizePixel().Width() - 1), 0);
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          // create centered handle as default
//STRIP001          pRetval = new B2dIAOAnimBmapExRef(pMan, aPos, &rBmpEx1, &rBmpEx2,
//STRIP001              (UINT16)(rBmpEx1.GetSizePixel().Width() - 1) >> 1,
//STRIP001              (UINT16)(rBmpEx1.GetSizePixel().Height() - 1) >> 1,
//STRIP001              (UINT16)(rBmpEx2.GetSizePixel().Width() - 1) >> 1,
//STRIP001              (UINT16)(rBmpEx2.GetSizePixel().Height() - 1) >> 1);
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      // create normal handle
//STRIP001      // #101928# use ImpGetBitmapEx(...) now
//STRIP001      BitmapEx& rBmpEx = ImpGetBitmapEx(eKindOfMarker, (sal_uInt16)eColIndex, bIsFineHdl, bIsHighContrast);
//STRIP001
//STRIP001      if(eKindOfMarker == Anchor || eKindOfMarker == AnchorPressed)
//STRIP001      {
//STRIP001          // #98388# upper left as reference point inside the handle for AnchorPressed, too
//STRIP001          pRetval = new B2dIAOBitmapExReference(pMan, aPos, &rBmpEx);
//STRIP001      }
//STRIP001      else if(eKindOfMarker == AnchorTR || eKindOfMarker == AnchorPressedTR)
//STRIP001      {
//STRIP001          // #101688# AnchorTR for SW, take top right as (0,0)
//STRIP001          pRetval = new B2dIAOBitmapExReference(pMan, aPos, &rBmpEx,
//STRIP001              (UINT16)(rBmpEx.GetSizePixel().Width() - 1), 0);
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          // create centered handle as default
//STRIP001          pRetval = new B2dIAOBitmapExReference(pMan, aPos, &rBmpEx,
//STRIP001              (UINT16)(rBmpEx.GetSizePixel().Width() - 1) >> 1,
//STRIP001              (UINT16)(rBmpEx.GetSizePixel().Height() - 1) >> 1);
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return pRetval;
//STRIP001 }

//STRIP001 BOOL SdrHdl::IsHit(const Point& rPnt, const OutputDevice& rOut) const
//STRIP001 {
//STRIP001  if(aIAOGroup.GetIAOCount())
//STRIP001  {
//STRIP001      Point aPixelPos(rOut.LogicToPixel(rPnt));
//STRIP001      return aIAOGroup.IsHit(aPixelPos);
//STRIP001  }
//STRIP001  else
//STRIP001      return FALSE;
//STRIP001 }

//STRIP001 Pointer SdrHdl::GetPointer() const
//STRIP001 {
//STRIP001     PointerStyle ePtr=POINTER_MOVE;
//STRIP001     BOOL bSize=eKind>=HDL_UPLFT && eKind<=HDL_LWRGT;
//STRIP001     // Fuer Resize von gedrehten Rechtecken die Mauszeiger etwas mitdrehen
//STRIP001     if (bSize && nDrehWink!=0) {
//STRIP001         long nHdlWink=0;
//STRIP001         switch (eKind) {
//STRIP001             case HDL_UPLFT: nHdlWink=13500; break;
//STRIP001             case HDL_UPPER: nHdlWink=9000;  break;
//STRIP001             case HDL_UPRGT: nHdlWink=4500;  break;
//STRIP001             case HDL_LEFT : nHdlWink=0;     break;
//STRIP001             case HDL_RIGHT: nHdlWink=0;     break;
//STRIP001             case HDL_LWLFT: nHdlWink=4500;  break;
//STRIP001             case HDL_LOWER: nHdlWink=9000;  break;
//STRIP001             case HDL_LWRGT: nHdlWink=13500; break;
//STRIP001         }
//STRIP001         nHdlWink+=nDrehWink+2249; // und etwas drauf (zum runden)
//STRIP001         while (nHdlWink<0) nHdlWink+=18000;
//STRIP001         while (nHdlWink>=18000) nHdlWink-=18000;
//STRIP001         nHdlWink/=4500;
//STRIP001         switch ((BYTE)nHdlWink) {
//STRIP001             case 0: ePtr=POINTER_ESIZE;    break;
//STRIP001             case 1: ePtr=POINTER_NESIZE; break;
//STRIP001             case 2: ePtr=POINTER_SSIZE;    break;
//STRIP001             case 3: ePtr=POINTER_SESIZE; break;
//STRIP001         } // switch
//STRIP001     }
//STRIP001     if (ePtr==POINTER_MOVE) {
//STRIP001         BOOL bRot=pHdlList!=NULL && pHdlList->IsRotateShear();
//STRIP001         BOOL bDis=pHdlList!=NULL && pHdlList->IsDistortShear();
//STRIP001         if (bSize && pHdlList!=NULL && (bRot || bDis)) {
//STRIP001             switch (eKind) {
//STRIP001                 case HDL_UPLFT: case HDL_UPRGT:
//STRIP001                 case HDL_LWLFT: case HDL_LWRGT: ePtr=bRot ? POINTER_ROTATE : POINTER_REFHAND; break;
//STRIP001                 case HDL_LEFT : case HDL_RIGHT: ePtr=POINTER_VSHEAR; break;
//STRIP001                 case HDL_UPPER: case HDL_LOWER: ePtr=POINTER_HSHEAR; break;
//STRIP001             }
//STRIP001         } else {
//STRIP001             switch (eKind) {
//STRIP001                 case HDL_UPLFT: ePtr=POINTER_SESIZE;  break;
//STRIP001                 case HDL_UPPER: ePtr=POINTER_SSIZE;     break;
//STRIP001                 case HDL_UPRGT: ePtr=POINTER_NESIZE;  break;
//STRIP001                 case HDL_LEFT : ePtr=POINTER_ESIZE;     break;
//STRIP001                 case HDL_RIGHT: ePtr=POINTER_ESIZE;     break;
//STRIP001                 case HDL_LWLFT: ePtr=POINTER_NESIZE;  break;
//STRIP001                 case HDL_LOWER: ePtr=POINTER_SSIZE;     break;
//STRIP001                 case HDL_LWRGT: ePtr=POINTER_SESIZE;  break;
//STRIP001                 case HDL_POLY : ePtr=POINTER_MOVEPOINT; break;
//STRIP001                 case HDL_CIRC : ePtr=POINTER_HAND;      break;
//STRIP001                 case HDL_REF1 : ePtr=POINTER_REFHAND;   break;
//STRIP001                 case HDL_REF2 : ePtr=POINTER_REFHAND;   break;
//STRIP001                 case HDL_BWGT : ePtr=POINTER_MOVEBEZIERWEIGHT; break;
//STRIP001                 case HDL_GLUE : ePtr=POINTER_MOVEPOINT; break;
//STRIP001             }
//STRIP001         }
//STRIP001     }
//STRIP001     return Pointer(ePtr);
//STRIP001 }

// #97016# II
//STRIP001 BOOL SdrHdl::IsFocusHdl() const
//STRIP001 {
//STRIP001  switch(eKind)
//STRIP001  {
//STRIP001      case HDL_UPLFT:     // Oben links
//STRIP001      case HDL_UPPER:     // Oben
//STRIP001      case HDL_UPRGT:     // Oben rechts
//STRIP001      case HDL_LEFT:      // Links
//STRIP001      case HDL_RIGHT:     // Rechts
//STRIP001      case HDL_LWLFT:     // Unten links
//STRIP001      case HDL_LOWER:     // Unten
//STRIP001      case HDL_LWRGT:     // Unten rechts
//STRIP001      {
//STRIP001          // if it's a activated TextEdit, it's moved to extended points
//STRIP001          if(pHdlList && pHdlList->IsMoveOutside())
//STRIP001              return FALSE;
//STRIP001          else
//STRIP001              return TRUE;
//STRIP001
//STRIP001          break;
//STRIP001      }
//STRIP001
//STRIP001      case HDL_MOVE:      // Handle zum Verschieben des Objekts
//STRIP001      case HDL_POLY:      // Punktselektion an Polygon oder Bezierkurve
//STRIP001      case HDL_BWGT:      // Gewicht an einer Bezierkurve
//STRIP001      case HDL_CIRC:      // Winkel an Kreissegmenten, Eckenradius am Rect
//STRIP001      case HDL_REF1:      // Referenzpunkt 1, z.B. Rotationsmitte
//STRIP001      case HDL_REF2:      // Referenzpunkt 2, z.B. Endpunkt der Spiegelachse
//STRIP001      //case HDL_MIRX:        // Die Spiegelachse selbst
//STRIP001      case HDL_GLUE:      // GluePoint
//STRIP001
//STRIP001      // #98388# do NOT activate here, let SW implement their own SdrHdl and
//STRIP001      // overload IsFocusHdl() there to make the anchor accessible
//STRIP001      //case HDL_ANCHOR:      // anchor symbol (SD, SW)
//STRIP001      // #101688# same for AnchorTR
//STRIP001      //case HDL_ANCHOR_TR:   // anchor symbol (SD, SW)
//STRIP001
//STRIP001      //case HDL_TRNS:        // interactive transparence
//STRIP001      //case HDL_GRAD:        // interactive gradient
//STRIP001      //case HDL_COLR:        // interactive color
//STRIP001      case HDL_USER:
//STRIP001      {
//STRIP001          return TRUE;
//STRIP001          break;
//STRIP001      }
//STRIP001
//STRIP001      default:
//STRIP001      {
//STRIP001          return FALSE;
//STRIP001          break;
//STRIP001      }
//STRIP001  }
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////
// class SdrHdlColor

//STRIP001 SdrHdlColor::SdrHdlColor(const Point& rRef, Color aCol, const Size& rSize, BOOL bLum)
//STRIP001 :    SdrHdl(rRef, HDL_COLR),
//STRIP001  aMarkerSize(rSize),
//STRIP001  bUseLuminance(bLum)
//STRIP001 {
//STRIP001  if(IsUseLuminance())
//STRIP001      aCol = GetLuminance(aCol);
//STRIP001
//STRIP001  // remember color
//STRIP001  aMarkerColor = aCol;
//STRIP001 }

//STRIP001 SdrHdlColor::~SdrHdlColor()
//STRIP001 {
//STRIP001 }

//STRIP001 void SdrHdlColor::CreateB2dIAObject()
//STRIP001 {
//STRIP001  // first throw away old one
//STRIP001  GetRidOfIAObject();
//STRIP001
//STRIP001  if(pHdlList && pHdlList->GetView() && !pHdlList->GetView()->IsMarkHdlHidden())
//STRIP001  {
//STRIP001      for(UINT16 a=0;a<pHdlList->GetView()->GetWinCount();a++)
//STRIP001      {
//STRIP001          SdrViewWinRec& rRec = pHdlList->GetView()->GetWinRec(a);
//STRIP001
//STRIP001          // Manager may be zero when printing or drawing to VDevs
//STRIP001          if(rRec.pIAOManager)
//STRIP001          {
//STRIP001              Bitmap aBmpCol(CreateColorDropper(aMarkerColor));
//STRIP001              B2dIAObject* pNew = new B2dIAOBitmapObj(rRec.pIAOManager, aPos, aBmpCol,
//STRIP001                  (UINT16)(aBmpCol.GetSizePixel().Width() - 1) >> 1,
//STRIP001                  (UINT16)(aBmpCol.GetSizePixel().Height() - 1) >> 1);
//STRIP001              DBG_ASSERT(pNew, "Got NO new IAO!");
//STRIP001              aIAOGroup.InsertIAO(pNew);
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 Bitmap SdrHdlColor::CreateColorDropper(Color aCol)
//STRIP001 {
//STRIP001  // get the Bitmap
//STRIP001  Bitmap aRetval(aMarkerSize, 24);
//STRIP001  aRetval.Erase(aCol);
//STRIP001
//STRIP001  // get write access
//STRIP001  BitmapWriteAccess* pWrite = aRetval.AcquireWriteAccess();
//STRIP001  DBG_ASSERT(pWrite, "Got NO write access to a new Bitmap !!!");
//STRIP001
//STRIP001  if(pWrite)
//STRIP001  {
//STRIP001      // draw outer border
//STRIP001      INT32 nWidth = aMarkerSize.Width();
//STRIP001      INT32 nHeight = aMarkerSize.Height();
//STRIP001
//STRIP001      pWrite->SetLineColor(Color(COL_LIGHTGRAY));
//STRIP001      pWrite->DrawLine(Point(0, 0), Point(0, nHeight - 1));
//STRIP001      pWrite->DrawLine(Point(1, 0), Point(nWidth - 1, 0));
//STRIP001      pWrite->SetLineColor(Color(COL_GRAY));
//STRIP001      pWrite->DrawLine(Point(1, nHeight - 1), Point(nWidth - 1, nHeight - 1));
//STRIP001      pWrite->DrawLine(Point(nWidth - 1, 1), Point(nWidth - 1, nHeight - 2));
//STRIP001
//STRIP001      // draw lighter UpperLeft
//STRIP001      B3dColor aMixCol(aCol);
//STRIP001      B3dColor aFactor(0x40, 0x40, 0x40);
//STRIP001      aMixCol += aFactor;
//STRIP001      pWrite->SetLineColor((Color)aMixCol);
//STRIP001      pWrite->DrawLine(Point(1, 1), Point(1, nHeight - 2));
//STRIP001      pWrite->DrawLine(Point(2, 1), Point(nWidth - 2, 1));
//STRIP001
//STRIP001      // draw darker LowerRight
//STRIP001      aMixCol = aCol;
//STRIP001      aMixCol -= aFactor;
//STRIP001      pWrite->SetLineColor((Color)aMixCol);
//STRIP001      pWrite->DrawLine(Point(2, nHeight - 2), Point(nWidth - 2, nHeight - 2));
//STRIP001      pWrite->DrawLine(Point(nWidth - 2, 2), Point(nWidth - 2, nHeight - 3));
//STRIP001
//STRIP001      // get rid of write access
//STRIP001      delete pWrite;
//STRIP001  }
//STRIP001
//STRIP001  return aRetval;
//STRIP001 }

//STRIP001 Color SdrHdlColor::GetLuminance(const Color& rCol)
//STRIP001 {
//STRIP001  UINT8 aLum = rCol.GetLuminance();
//STRIP001  Color aRetval(aLum, aLum, aLum);
//STRIP001  return aRetval;
//STRIP001 }

//STRIP001 void SdrHdlColor::CallColorChangeLink()
//STRIP001 {
//STRIP001  aColorChangeHdl.Call(this);
//STRIP001 }

//STRIP001 void SdrHdlColor::SetColor(Color aNew, BOOL bCallLink)
//STRIP001 {
//STRIP001  if(IsUseLuminance())
//STRIP001      aNew = GetLuminance(aNew);
//STRIP001
//STRIP001  if(aMarkerColor != aNew)
//STRIP001  {
//STRIP001      // remember new color
//STRIP001      aMarkerColor = aNew;
//STRIP001
//STRIP001      // create new display
//STRIP001      Touch();
//STRIP001
//STRIP001      // tell about change
//STRIP001      if(bCallLink)
//STRIP001          CallColorChangeLink();
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrHdlColor::SetSize(const Size& rNew)
//STRIP001 {
//STRIP001  if(rNew != aMarkerSize)
//STRIP001  {
//STRIP001      // remember new size
//STRIP001      aMarkerSize = rNew;
//STRIP001
//STRIP001      // create new display
//STRIP001      Touch();
//STRIP001  }
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////
// class SdrHdlGradient

//STRIP001 SdrHdlGradient::SdrHdlGradient(const Point& rRef1, const Point& rRef2, BOOL bGrad)
//STRIP001 :    SdrHdl(rRef1, bGrad ? HDL_GRAD : HDL_TRNS),
//STRIP001  a2ndPos(rRef2),
//STRIP001  bGradient(bGrad),
//STRIP001  pColHdl1(NULL),
//STRIP001  pColHdl2(NULL)
//STRIP001 {
//STRIP001 }

//STRIP001 SdrHdlGradient::~SdrHdlGradient()
//STRIP001 {
//STRIP001 }

//STRIP001 void SdrHdlGradient::Set2ndPos(const Point& rPnt)
//STRIP001 {
//STRIP001  if(a2ndPos != rPnt)
//STRIP001  {
//STRIP001      // remember new position
//STRIP001      a2ndPos = rPnt;
//STRIP001
//STRIP001      // create new display
//STRIP001      Touch();
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrHdlGradient::CreateB2dIAObject()
//STRIP001 {
//STRIP001  // first throw away old one
//STRIP001  GetRidOfIAObject();
//STRIP001
//STRIP001  if(pHdlList && pHdlList->GetView() && !pHdlList->GetView()->IsMarkHdlHidden())
//STRIP001  {
//STRIP001      for(UINT16 a=0;a<pHdlList->GetView()->GetWinCount();a++)
//STRIP001      {
//STRIP001          SdrViewWinRec& rRec = pHdlList->GetView()->GetWinRec(a);
//STRIP001
//STRIP001          // Manager may be zero when printing or drawing to VDevs
//STRIP001          if(rRec.pIAOManager)
//STRIP001          {
//STRIP001              // striped line in between
//STRIP001              Vector2D aVec(a2ndPos.X() - aPos.X(), a2ndPos.Y() - aPos.Y());
//STRIP001              double fVecLen = aVec.GetLength();
//STRIP001              double fLongPercentArrow = (1.0 - 0.05) * fVecLen;
//STRIP001              double fHalfArrowWidth = (0.05 * 0.5) * fVecLen;
//STRIP001              aVec.Normalize();
//STRIP001              Vector2D aPerpend(-aVec.Y(), aVec.X());
//STRIP001              INT32 nMidX = (INT32)(aPos.X() + aVec.X() * fLongPercentArrow);
//STRIP001              INT32 nMidY = (INT32)(aPos.Y() + aVec.Y() * fLongPercentArrow);
//STRIP001              Point aMidPoint(nMidX, nMidY);
//STRIP001              B2dIAObject* pNew = new B2dIAOLineStriped(rRec.pIAOManager, aPos, aMidPoint, 4);
//STRIP001              DBG_ASSERT(pNew, "Got NO new IAO!");
//STRIP001              pNew->SetBaseColor(IsGradient() ? Color(COL_BLACK) : Color(COL_BLUE));
//STRIP001              aIAOGroup.InsertIAO(pNew);
//STRIP001
//STRIP001              // arrowhead
//STRIP001              Point aLeft(aMidPoint.X() + (INT32)(aPerpend.X() * fHalfArrowWidth),
//STRIP001                          aMidPoint.Y() + (INT32)(aPerpend.Y() * fHalfArrowWidth));
//STRIP001              Point aRight(aMidPoint.X() - (INT32)(aPerpend.X() * fHalfArrowWidth),
//STRIP001                          aMidPoint.Y() - (INT32)(aPerpend.Y() * fHalfArrowWidth));
//STRIP001              pNew = new B2dIAOBitmapTriangle(rRec.pIAOManager, aLeft, a2ndPos, aRight, IsGradient() ? Color(COL_BLACK) : Color(COL_BLUE));
//STRIP001              DBG_ASSERT(pNew, "Got NO new IAO!");
//STRIP001              aIAOGroup.InsertIAO(pNew);
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 IMPL_LINK(SdrHdlGradient, ColorChangeHdl, SdrHdl*, pHdl)
//STRIP001 {
//STRIP001  if(GetObj())
//STRIP001      FromIAOToItem(GetObj(), TRUE, TRUE);
//STRIP001  return NULL;
//STRIP001 }

//STRIP001 void SdrHdlGradient::FromIAOToItem(SdrObject* pObj, BOOL bSetItemOnObject, BOOL bUndo)
//STRIP001 {
//STRIP001  // from IAO positions and colors to gradient
//STRIP001  const SfxItemSet& rSet = pObj->GetItemSet();
//STRIP001
//STRIP001  GradTransformer aGradTransformer;
//STRIP001  GradTransGradient aOldGradTransGradient;
//STRIP001  GradTransGradient aGradTransGradient;
//STRIP001  GradTransVector aGradTransVector;
//STRIP001
//STRIP001  String aString;
//STRIP001
//STRIP001  aGradTransVector.aPos1 = GetPos();
//STRIP001  aGradTransVector.aPos2 = Get2ndPos();
//STRIP001  if(pColHdl1)
//STRIP001      aGradTransVector.aCol1 = pColHdl1->GetColor();
//STRIP001  if(pColHdl2)
//STRIP001      aGradTransVector.aCol2 = pColHdl2->GetColor();
//STRIP001
//STRIP001  if(IsGradient())
//STRIP001      aOldGradTransGradient.aGradient = ((XFillGradientItem&)rSet.Get(XATTR_FILLGRADIENT)).GetValue();
//STRIP001  else
//STRIP001      aOldGradTransGradient.aGradient = ((XFillFloatTransparenceItem&)rSet.Get(XATTR_FILLFLOATTRANSPARENCE)).GetValue();
//STRIP001
//STRIP001  // transform vector data to gradient
//STRIP001  aGradTransformer.VecToGrad(aGradTransVector, aGradTransGradient, aOldGradTransGradient, pObj, bMoveSingleHandle, bMoveFirstHandle);
//STRIP001
//STRIP001  if(bSetItemOnObject)
//STRIP001  {
//STRIP001      SdrModel* pModel = pObj->GetModel();
//STRIP001      SfxItemSet aNewSet(pModel->GetItemPool());
//STRIP001
//STRIP001      if(IsGradient())
//STRIP001      {
//STRIP001          aString = String();
//STRIP001          XFillGradientItem aNewGradItem(aString, aGradTransGradient.aGradient);
//STRIP001          aNewSet.Put(aNewGradItem);
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          aString = String();
//STRIP001          XFillFloatTransparenceItem aNewTransItem(aString, aGradTransGradient.aGradient);
//STRIP001          aNewSet.Put(aNewTransItem);
//STRIP001      }
//STRIP001
//STRIP001      if(bUndo)
//STRIP001      {
//STRIP001          pModel->BegUndo(SVX_RESSTR(IsGradient() ? SIP_XA_FILLGRADIENT : SIP_XA_FILLTRANSPARENCE));
//STRIP001          pModel->AddUndo(new SdrUndoAttrObj(*pObj));
//STRIP001          pModel->EndUndo();
//STRIP001      }
//STRIP001
//STRIP001      pObj->SetItemSetAndBroadcast(aNewSet);
//STRIP001  }
//STRIP001
//STRIP001  // back transformation, set values on pIAOHandle
//STRIP001  aGradTransformer.GradToVec(aGradTransGradient, aGradTransVector, pObj);
//STRIP001
//STRIP001  SetPos(aGradTransVector.aPos1);
//STRIP001  Set2ndPos(aGradTransVector.aPos2);
//STRIP001  if(pColHdl1)
//STRIP001  {
//STRIP001      pColHdl1->SetPos(aGradTransVector.aPos1);
//STRIP001      pColHdl1->SetColor(aGradTransVector.aCol1);
//STRIP001  }
//STRIP001  if(pColHdl2)
//STRIP001  {
//STRIP001      pColHdl2->SetPos(aGradTransVector.aPos2);
//STRIP001      pColHdl2->SetColor(aGradTransVector.aCol2);
//STRIP001  }
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 SdrHdlLine::~SdrHdlLine() {}

//STRIP001 void SdrHdlLine::CreateB2dIAObject()
//STRIP001 {
//STRIP001  // first throw away old one
//STRIP001  GetRidOfIAObject();
//STRIP001
//STRIP001  if(pHdlList && pHdlList->GetView() && !pHdlList->GetView()->IsMarkHdlHidden() && pHdl1 && pHdl2)
//STRIP001  {
//STRIP001      for(UINT16 a=0;a<pHdlList->GetView()->GetWinCount();a++)
//STRIP001      {
//STRIP001          SdrViewWinRec& rRec = pHdlList->GetView()->GetWinRec(a);
//STRIP001
//STRIP001          // Manager may be zero when printing or drawing to VDevs
//STRIP001          if(rRec.pIAOManager)
//STRIP001          {
//STRIP001              B2dIAObject* pNew = new B2dIAOLine(
//STRIP001                  rRec.pIAOManager,
//STRIP001                  pHdl1->GetPos(),
//STRIP001                  pHdl2->GetPos());
//STRIP001
//STRIP001              if(pNew)
//STRIP001              {
//STRIP001                  // color(?)
//STRIP001                  pNew->SetBaseColor(Color(COL_LIGHTRED));
//STRIP001
//STRIP001                  // set as B2DIAObject
//STRIP001                  aIAOGroup.InsertIAO(pNew);
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 BOOL SdrHdlLine::IsHit(const Point& rPnt, const OutputDevice& rOut) const
//STRIP001 {
//STRIP001  if(aIAOGroup.GetIAOCount())
//STRIP001  {
//STRIP001      Point aPixelPos(rOut.LogicToPixel(rPnt));
//STRIP001      return aIAOGroup.IsHit(aPixelPos, 2);
//STRIP001  }
//STRIP001  else
//STRIP001      return FALSE;
//STRIP001 }

//STRIP001 Pointer SdrHdlLine::GetPointer() const
//STRIP001 {
//STRIP001     return Pointer(POINTER_REFHAND);
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 SdrHdlBezWgt::~SdrHdlBezWgt() {}

//STRIP001 void SdrHdlBezWgt::CreateB2dIAObject()
//STRIP001 {
//STRIP001  // call parent
//STRIP001  SdrHdl::CreateB2dIAObject();
//STRIP001
//STRIP001  // create lines
//STRIP001  if(pHdlList && pHdlList->GetView() && !pHdlList->GetView()->IsMarkHdlHidden())
//STRIP001  {
//STRIP001      for(UINT16 a=0;a<pHdlList->GetView()->GetWinCount();a++)
//STRIP001      {
//STRIP001          SdrViewWinRec& rRec = pHdlList->GetView()->GetWinRec(a);
//STRIP001
//STRIP001          // Manager may be zero when printing or drawing to VDevs
//STRIP001          if(rRec.pIAOManager)
//STRIP001          {
//STRIP001              B2dIAObject* pNew = new B2dIAOLine(
//STRIP001                  rRec.pIAOManager,
//STRIP001                  pHdl1->GetPos(),
//STRIP001                  aPos);
//STRIP001
//STRIP001              if(pNew)
//STRIP001              {
//STRIP001                  // line part is not hittable
//STRIP001                  pNew->SetHittable(FALSE);
//STRIP001
//STRIP001                  // color(?)
//STRIP001                  pNew->SetBaseColor(Color(COL_LIGHTBLUE));
//STRIP001
//STRIP001                  // set as B2DIAObject
//STRIP001                  aIAOGroup.InsertIAO(pNew);
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 E3dVolumeMarker::E3dVolumeMarker(const XPolyPolygon& rXPP)
//STRIP001 {
//STRIP001  aWireframePoly = rXPP;
//STRIP001 }

//STRIP001 void E3dVolumeMarker::CreateB2dIAObject()
//STRIP001 {
//STRIP001  // create lines
//STRIP001  if(pHdlList && pHdlList->GetView() && !pHdlList->GetView()->IsMarkHdlHidden())
//STRIP001  {
//STRIP001      for(UINT16 a=0;a<pHdlList->GetView()->GetWinCount();a++)
//STRIP001      {
//STRIP001          SdrViewWinRec& rRec = pHdlList->GetView()->GetWinRec(a);
//STRIP001
//STRIP001          // Manager may be zero when printing or drawing to VDevs
//STRIP001          if(rRec.pIAOManager)
//STRIP001          {
//STRIP001              UINT16 nCnt = aWireframePoly.Count();
//STRIP001              for(UINT16 i = 0; i < nCnt; i++)
//STRIP001              {
//STRIP001                  B2dIAObject* pNew = new B2dIAOLine(
//STRIP001                      rRec.pIAOManager,
//STRIP001                      aWireframePoly[i][0],
//STRIP001                      aWireframePoly[i][1]);
//STRIP001
//STRIP001                  if(pNew)
//STRIP001                  {
//STRIP001                      // color(?)
//STRIP001                      pNew->SetBaseColor(Color(COL_BLACK));
//STRIP001
//STRIP001                      // set as B2DIAObject
//STRIP001                      aIAOGroup.InsertIAO(pNew);
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 ImpEdgeHdl::~ImpEdgeHdl()
//STRIP001 {
//STRIP001 }

//STRIP001 void ImpEdgeHdl::CreateB2dIAObject()
//STRIP001 {
//STRIP001  if(nObjHdlNum <= 1 && pObj)
//STRIP001  {
//STRIP001      // first throw away old one
//STRIP001      GetRidOfIAObject();
//STRIP001
//STRIP001      BitmapColorIndex eColIndex = LightCyan;
//STRIP001      BitmapMarkerKind eKindOfMarker = Rect_7x7;
//STRIP001
//STRIP001      if(pHdlList && pHdlList->GetView() && !pHdlList->GetView()->IsMarkHdlHidden())
//STRIP001      {
//STRIP001          const SdrEdgeObj* pEdge = (SdrEdgeObj*)pObj;
//STRIP001
//STRIP001          if(pEdge->GetConnectedNode(nObjHdlNum == 0) != NULL)
//STRIP001              eColIndex = LightRed;
//STRIP001
//STRIP001          if(nPPntNum < 2)
//STRIP001          {
//STRIP001              // Handle with plus sign inside
//STRIP001              eKindOfMarker = Circ_7x7;
//STRIP001          }
//STRIP001
//STRIP001          for(UINT16 a=0;a<pHdlList->GetView()->GetWinCount();a++)
//STRIP001          {
//STRIP001              SdrViewWinRec& rRec = pHdlList->GetView()->GetWinRec(a);
//STRIP001
//STRIP001              // Manager may be zero when printing or drawing to VDevs
//STRIP001              if(rRec.pIAOManager)
//STRIP001              {
//STRIP001                  B2dIAObject* pNew = CreateMarkerObject(
//STRIP001                      rRec.pIAOManager,
//STRIP001                      aPos,
//STRIP001                      eColIndex,
//STRIP001                      eKindOfMarker);
//STRIP001
//STRIP001                  if(pNew)
//STRIP001                  {
//STRIP001                      // set as B2DIAObject
//STRIP001                      aIAOGroup.InsertIAO(pNew);
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      // call parent
//STRIP001      SdrHdl::CreateB2dIAObject();
//STRIP001  }
//STRIP001 }

//STRIP001 void ImpEdgeHdl::SetLineCode(SdrEdgeLineCode eCode)
//STRIP001 {
//STRIP001  if(eLineCode != eCode)
//STRIP001  {
//STRIP001      // remember new value
//STRIP001      eLineCode = eCode;
//STRIP001
//STRIP001      // create new display
//STRIP001      CreateB2dIAObject();
//STRIP001  }
//STRIP001 }

//STRIP001 Pointer ImpEdgeHdl::GetPointer() const
//STRIP001 {
//STRIP001     SdrEdgeObj* pEdge=PTR_CAST(SdrEdgeObj,pObj);
//STRIP001     if (pEdge==NULL) return SdrHdl::GetPointer();
//STRIP001     if (nObjHdlNum<=1) return Pointer(POINTER_MOVEPOINT); //Pointer(POINTER_DRAW_CONNECT);
//STRIP001     if (IsHorzDrag()) return Pointer(POINTER_ESIZE);
//STRIP001     else return Pointer(POINTER_SSIZE);
//STRIP001 }

//STRIP001 BOOL ImpEdgeHdl::IsHorzDrag() const
//STRIP001 {
//STRIP001     SdrEdgeObj* pEdge=PTR_CAST(SdrEdgeObj,pObj);
//STRIP001     if (pEdge==NULL) return FALSE;
//STRIP001     if (nObjHdlNum<=1) return FALSE;
//STRIP001
//STRIP001  SdrEdgeKind eKind = ((SdrEdgeKindItem&)(pEdge->GetItem(SDRATTR_EDGEKIND))).GetValue();
//STRIP001
//STRIP001  const SdrEdgeInfoRec& rInfo=pEdge->aEdgeInfo;
//STRIP001     if (eKind==SDREDGE_ORTHOLINES || eKind==SDREDGE_BEZIER) {
//STRIP001         return !rInfo.ImpIsHorzLine(eLineCode,*pEdge->pEdgeTrack);
//STRIP001     } else if (eKind==SDREDGE_THREELINES) {
//STRIP001         long nWink=nObjHdlNum==2 ? rInfo.nAngle1 : rInfo.nAngle2;
//STRIP001         if (nWink==0 || nWink==18000) return TRUE;
//STRIP001         else return FALSE;
//STRIP001     }
//STRIP001     return FALSE;
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 ImpMeasureHdl::~ImpMeasureHdl()
//STRIP001 {
//STRIP001 }

//STRIP001 void ImpMeasureHdl::CreateB2dIAObject()
//STRIP001 {
//STRIP001  // first throw away old one
//STRIP001  GetRidOfIAObject();
//STRIP001
//STRIP001  if(pHdlList && pHdlList->GetView() && !pHdlList->GetView()->IsMarkHdlHidden())
//STRIP001  {
//STRIP001      BitmapColorIndex eColIndex = LightCyan;
//STRIP001      BitmapMarkerKind eKindOfMarker = Rect_9x9;
//STRIP001
//STRIP001      if(nObjHdlNum > 1)
//STRIP001      {
//STRIP001          eKindOfMarker = Rect_7x7;
//STRIP001      }
//STRIP001
//STRIP001      if(bSelect)
//STRIP001      {
//STRIP001          eColIndex = Cyan;
//STRIP001      }
//STRIP001
//STRIP001      for(UINT16 a=0;a<pHdlList->GetView()->GetWinCount();a++)
//STRIP001      {
//STRIP001          SdrViewWinRec& rRec = pHdlList->GetView()->GetWinRec(a);
//STRIP001
//STRIP001          // Manager may be zero when printing or drawing to VDevs
//STRIP001          if(rRec.pIAOManager)
//STRIP001          {
//STRIP001              B2dIAObject* pNew = CreateMarkerObject(
//STRIP001                  rRec.pIAOManager,
//STRIP001                  aPos,
//STRIP001                  eColIndex,
//STRIP001                  eKindOfMarker);
//STRIP001
//STRIP001              if(pNew)
//STRIP001              {
//STRIP001                  // set as B2DIAObject
//STRIP001                  aIAOGroup.InsertIAO(pNew);
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 Pointer ImpMeasureHdl::GetPointer() const
//STRIP001 {
//STRIP001     switch (nObjHdlNum) {
//STRIP001         case 0: case 1: return Pointer(POINTER_HAND);
//STRIP001         case 2: case 3: return Pointer(POINTER_MOVEPOINT);
//STRIP001         case 4: case 5: return SdrHdl::GetPointer(); // wird dann entsprechend gedreht
//STRIP001     } // switch
//STRIP001     return Pointer(POINTER_NOTALLOWED);
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ class ImpSdrHdlListSorter: public ContainerSorter {
/*N*/ public:
/*N*/     ImpSdrHdlListSorter(Container& rNewCont): ContainerSorter(rNewCont) {}
/*N*/     virtual int Compare(const void* pElem1, const void* pElem2) const;
/*N*/ };

/*N*/ int ImpSdrHdlListSorter::Compare(const void* pElem1, const void* pElem2) const
/*N*/ {DBG_ASSERT(0, "STRIP"); return 0;//STRIP001
//STRIP001     SdrHdlKind eKind1=((SdrHdl*)pElem1)->GetKind();
//STRIP001     SdrHdlKind eKind2=((SdrHdl*)pElem2)->GetKind();
//STRIP001     // Level 1: Erst normale Handles, dann Glue, dann User, dann Plushandles, dann Retpunkt-Handles
//STRIP001     unsigned n1=1;
//STRIP001     unsigned n2=1;
//STRIP001     if (eKind1!=eKind2) {
//STRIP001         if (eKind1==HDL_REF1 || eKind1==HDL_REF2 || eKind1==HDL_MIRX) n1=5;
//STRIP001         else if (eKind1==HDL_GLUE) n1=2;
//STRIP001         else if (eKind1==HDL_USER) n1=3;
//STRIP001         if (eKind2==HDL_REF1 || eKind2==HDL_REF2 || eKind2==HDL_MIRX) n2=5;
//STRIP001         else if (eKind2==HDL_GLUE) n2=2;
//STRIP001         else if (eKind2==HDL_USER) n2=3;
//STRIP001     }
//STRIP001     if (((SdrHdl*)pElem1)->IsPlusHdl()) n1=4;
//STRIP001     if (((SdrHdl*)pElem2)->IsPlusHdl()) n2=4;
//STRIP001     if (n1==n2) {
//STRIP001         // Level 2: PageView (Pointer)
//STRIP001         SdrPageView* pPV1=((SdrHdl*)pElem1)->GetPageView();
//STRIP001         SdrPageView* pPV2=((SdrHdl*)pElem2)->GetPageView();
//STRIP001         if (pPV1==pPV2) {
//STRIP001             // Level 3: Position (x+y)
//STRIP001             SdrObject* pObj1=((SdrHdl*)pElem1)->GetObj();
//STRIP001             SdrObject* pObj2=((SdrHdl*)pElem2)->GetObj();
//STRIP001             if (pObj1==pObj2) {
//STRIP001                 USHORT nNum1=((SdrHdl*)pElem1)->GetObjHdlNum();
//STRIP001                 USHORT nNum2=((SdrHdl*)pElem2)->GetObjHdlNum();
//STRIP001                 if (nNum1==nNum2) { // #48763#
//STRIP001                     if (eKind1==eKind2) (long)pElem1<(long)pElem2 ? -1 : 1; // Notloesung, um immer die gleiche Sortierung zu haben
//STRIP001                     return (USHORT)eKind1<(USHORT)eKind2 ? -1 : 1;
//STRIP001                 } else return nNum1<nNum2 ? -1 : 1;
//STRIP001             } else {
//STRIP001                 return (long)pObj1<(long)pObj2 ? -1 : 1;
//STRIP001             }
//STRIP001         } else {
//STRIP001             return (long)pPV1<(long)pPV2 ? -1 : 1;
//STRIP001         }
//STRIP001     } else {
//STRIP001         return n1<n2 ? -1 : 1;
//STRIP001     }
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
// #97016# II

/*N*/ class ImplHdlListData
/*N*/ {
/*N*/ public:
/*N*/   sal_uInt32                  mnFocusIndex;
/*N*/   SdrMarkView*                pView;
/*N*/
/*N*/   ImplHdlListData(SdrMarkView* pV): mnFocusIndex(CONTAINER_ENTRY_NOTFOUND), pView(pV) {}
/*N*/ };

//STRIP001 SdrMarkView* SdrHdlList::GetView() const
//STRIP001 {
//STRIP001  return pImpl->pView;
//STRIP001 }

// #105678# Help struct for re-sorting handles
struct ImplHdlAndIndex
{
    SdrHdl*                     mpHdl;
    sal_uInt32                  mnIndex;
};

// #105678# Help method for sorting handles taking care of OrdNums, keeping order in
// single objects and re-sorting polygon handles intuitively
//STRIP001 extern "C" int __LOADONCALLAPI ImplSortHdlFunc( const void* pVoid1, const void* pVoid2 )
//STRIP001 {
//STRIP001  const ImplHdlAndIndex* p1 = (ImplHdlAndIndex*)pVoid1;
//STRIP001  const ImplHdlAndIndex* p2 = (ImplHdlAndIndex*)pVoid2;
//STRIP001
//STRIP001  if(p1->mpHdl->GetObj() == p2->mpHdl->GetObj())
//STRIP001  {
//STRIP001      if(p1->mpHdl->GetObj() && p1->mpHdl->GetObj()->ISA(SdrPathObj))
//STRIP001      {
//STRIP001          // same object and a path object
//STRIP001          if((p1->mpHdl->GetKind() == HDL_POLY || p1->mpHdl->GetKind() == HDL_BWGT)
//STRIP001              && (p2->mpHdl->GetKind() == HDL_POLY || p2->mpHdl->GetKind() == HDL_BWGT))
//STRIP001          {
//STRIP001              // both handles are point or control handles
//STRIP001              sal_uInt32 nInd1 = (p1->mpHdl->GetPolyNum() << 16) | p1->mpHdl->GetPointNum();
//STRIP001              sal_uInt32 nInd2 = (p2->mpHdl->GetPolyNum() << 16) | p2->mpHdl->GetPointNum();
//STRIP001
//STRIP001              if(nInd1 < nInd2)
//STRIP001              {
//STRIP001                  return -1;
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  return 1;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if(!p1->mpHdl->GetObj())
//STRIP001      {
//STRIP001          return -1;
//STRIP001      }
//STRIP001      else if(!p2->mpHdl->GetObj())
//STRIP001      {
//STRIP001          return 1;
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          // different objects, use OrdNum for sort
//STRIP001          const sal_uInt32 nOrdNum1 = p1->mpHdl->GetObj()->GetOrdNum();
//STRIP001          const sal_uInt32 nOrdNum2 = p2->mpHdl->GetObj()->GetOrdNum();
//STRIP001
//STRIP001          if(nOrdNum1 < nOrdNum2)
//STRIP001          {
//STRIP001              return -1;
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              return 1;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // fallback to indices
//STRIP001  if(p1->mnIndex < p2->mnIndex)
//STRIP001  {
//STRIP001      return -1;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      return 1;
//STRIP001  }
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////
// #97016# II

//STRIP001 void SdrHdlList::TravelFocusHdl(sal_Bool bForward)
//STRIP001 {
//STRIP001  // security correction
//STRIP001  if(pImpl->mnFocusIndex != CONTAINER_ENTRY_NOTFOUND && pImpl->mnFocusIndex >= GetHdlCount())
//STRIP001      pImpl->mnFocusIndex = CONTAINER_ENTRY_NOTFOUND;
//STRIP001
//STRIP001  if(aList.Count())
//STRIP001  {
//STRIP001      // take care of old handle
//STRIP001      const sal_uInt32 nOldHdlNum(pImpl->mnFocusIndex);
//STRIP001      SdrHdl* pOld = GetHdl(nOldHdlNum);
//STRIP001      sal_Bool bRefresh(sal_False);
//STRIP001
//STRIP001      if(pOld)
//STRIP001      {
//STRIP001          // switch off old handle
//STRIP001          pImpl->mnFocusIndex = CONTAINER_ENTRY_NOTFOUND;
//STRIP001          pOld->Touch();
//STRIP001          bRefresh = sal_True;
//STRIP001      }
//STRIP001
//STRIP001      // #105678# Alloc pointer array for sorted handle list
//STRIP001      ImplHdlAndIndex* pHdlAndIndex = new ImplHdlAndIndex[aList.Count()];
//STRIP001
//STRIP001      // #105678# build sorted handle list
//STRIP001      for(sal_uInt32 a(0); a < aList.Count(); a++)
//STRIP001      {
//STRIP001          pHdlAndIndex[a].mpHdl = (SdrHdl*)aList.GetObject(a);
//STRIP001          pHdlAndIndex[a].mnIndex = a;
//STRIP001      }
//STRIP001
//STRIP001      // #105678# qsort all entries
//STRIP001      qsort(pHdlAndIndex, aList.Count(), sizeof(ImplHdlAndIndex), ImplSortHdlFunc);
//STRIP001
//STRIP001      // #105678# look for old num in sorted array
//STRIP001      sal_uInt32 nOldHdl(nOldHdlNum);
//STRIP001
//STRIP001      if(nOldHdlNum != CONTAINER_ENTRY_NOTFOUND)
//STRIP001      {
//STRIP001          const SdrHdl* pOld = GetHdl(nOldHdlNum);
//STRIP001
//STRIP001          for(a = 0; a < aList.Count(); a++)
//STRIP001          {
//STRIP001              if(pHdlAndIndex[a].mpHdl == pOld)
//STRIP001              {
//STRIP001                  nOldHdl = a;
//STRIP001                  break;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      // #105678# build new HdlNum
//STRIP001      sal_uInt32 nNewHdl(nOldHdl);
//STRIP001
//STRIP001      // #105678# do the focus travel
//STRIP001      if(bForward)
//STRIP001      {
//STRIP001          if(nOldHdl != CONTAINER_ENTRY_NOTFOUND)
//STRIP001          {
//STRIP001              if(nOldHdl == aList.Count() - 1)
//STRIP001              {
//STRIP001                  // end forward run
//STRIP001                  nNewHdl = CONTAINER_ENTRY_NOTFOUND;
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  // simply the next handle
//STRIP001                  nNewHdl++;
//STRIP001              }
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              // start forward run at first entry
//STRIP001              nNewHdl = 0;
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          if(nOldHdl == CONTAINER_ENTRY_NOTFOUND)
//STRIP001          {
//STRIP001              // start backward run at last entry
//STRIP001              nNewHdl = aList.Count() - 1;
//STRIP001
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              if(nOldHdl == 0)
//STRIP001              {
//STRIP001                  // end backward run
//STRIP001                  nNewHdl = CONTAINER_ENTRY_NOTFOUND;
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  // simply the previous handle
//STRIP001                  nNewHdl--;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      // #105678# build new HdlNum
//STRIP001      sal_uInt32 nNewHdlNum(nNewHdl);
//STRIP001
//STRIP001      // look for old num in sorted array
//STRIP001      if(nNewHdl != CONTAINER_ENTRY_NOTFOUND)
//STRIP001      {
//STRIP001          SdrHdl* pNew = pHdlAndIndex[nNewHdl].mpHdl;
//STRIP001
//STRIP001          for(a = 0; a < aList.Count(); a++)
//STRIP001          {
//STRIP001              if((SdrHdl*)aList.GetObject(a) == pNew)
//STRIP001              {
//STRIP001                  nNewHdlNum = a;
//STRIP001                  break;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      // take care of next handle
//STRIP001      if(nOldHdlNum != nNewHdlNum)
//STRIP001      {
//STRIP001          pImpl->mnFocusIndex = nNewHdlNum;
//STRIP001          SdrHdl* pNew = GetHdl(pImpl->mnFocusIndex);
//STRIP001
//STRIP001          if(pNew)
//STRIP001          {
//STRIP001              pNew->Touch();
//STRIP001              bRefresh = sal_True;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      // if something has changed do a handle refresh
//STRIP001      if(bRefresh)
//STRIP001      {
//STRIP001          if(pImpl->pView)
//STRIP001              pImpl->pView->RefreshAllIAOManagers();
//STRIP001      }
//STRIP001
//STRIP001      // #105678# free mem again
//STRIP001      delete pHdlAndIndex;
//STRIP001  }
//STRIP001 }

/*N*/ SdrHdl* SdrHdlList::GetFocusHdl() const
/*N*/ {
/*N*/   if(pImpl->mnFocusIndex != CONTAINER_ENTRY_NOTFOUND && pImpl->mnFocusIndex < GetHdlCount())
/*?*/       return GetHdl(pImpl->mnFocusIndex);
/*N*/   else
/*?*/       return 0L;
/*N*/ }

//STRIP001 void SdrHdlList::SetFocusHdl(SdrHdl* pNew)
//STRIP001 {
//STRIP001  if(pNew)
//STRIP001  {
//STRIP001      SdrHdl* pActual = GetFocusHdl();
//STRIP001
//STRIP001      if(!pActual || pActual != pNew)
//STRIP001      {
//STRIP001          sal_uInt32 nNewHdlNum = GetHdlNum(pNew);
//STRIP001
//STRIP001          if(nNewHdlNum != CONTAINER_ENTRY_NOTFOUND)
//STRIP001          {
//STRIP001              sal_Bool bRefresh(sal_False);
//STRIP001              pImpl->mnFocusIndex = nNewHdlNum;
//STRIP001
//STRIP001              if(pActual)
//STRIP001              {
//STRIP001                  pActual->Touch();
//STRIP001                  bRefresh = sal_True;
//STRIP001              }
//STRIP001
//STRIP001              if(pNew)
//STRIP001              {
//STRIP001                  pNew->Touch();
//STRIP001                  bRefresh = sal_True;
//STRIP001              }
//STRIP001
//STRIP001              if(bRefresh)
//STRIP001              {
//STRIP001                  if(pImpl->pView)
//STRIP001                      pImpl->pView->RefreshAllIAOManagers();
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*N*/ void SdrHdlList::ResetFocusHdl()
/*N*/ {
/*N*/   SdrHdl* pHdl = GetFocusHdl();
/*N*/
/*N*/   pImpl->mnFocusIndex = CONTAINER_ENTRY_NOTFOUND;
/*N*/
/*N*/   if(pHdl)
/*N*/   {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/        pHdl->Touch();
//STRIP001 /*?*/
//STRIP001 /*?*/        if(pImpl->pView)
//STRIP001 /*?*/            pImpl->pView->RefreshAllIAOManagers();
/*N*/   }
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ SdrHdlList::SdrHdlList(SdrMarkView* pV)
/*N*/ : aList(1024,32,32),
/*N*/   pImpl(new ImplHdlListData(pV))
/*N*/   //#97016# II
/*N*/   //pView(pV)
/*N*/ {
/*N*/   nHdlSize = 3;
/*N*/   bRotateShear = FALSE;
/*N*/   bMoveOutside = FALSE;
/*N*/   bDistortShear = FALSE;
/*N*/   bFineHandles = FALSE;
/*N*/ }
/*N*/
/*N*/ SdrHdlList::~SdrHdlList()
/*N*/ {
/*N*/   Clear();
/*N*/   //#97016# II
/*N*/   delete pImpl;
/*N*/ }

//STRIP001 void SdrHdlList::SetHdlSize(USHORT nSiz)
//STRIP001 {
//STRIP001  if(nHdlSize != nSiz)
//STRIP001  {
//STRIP001      // remember new value
//STRIP001      nHdlSize = nSiz;
//STRIP001
//STRIP001      // propagate change to IAOs
//STRIP001      for(UINT32 i=0; i<GetHdlCount(); i++)
//STRIP001      {
//STRIP001          SdrHdl* pHdl = GetHdl(i);
//STRIP001          pHdl->Touch();
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrHdlList::SetMoveOutside(BOOL bOn)
//STRIP001 {
//STRIP001  if(bMoveOutside != bOn)
//STRIP001  {
//STRIP001      // remember new value
//STRIP001      bMoveOutside = bOn;
//STRIP001
//STRIP001      // propagate change to IAOs
//STRIP001      for(UINT32 i=0; i<GetHdlCount(); i++)
//STRIP001      {
//STRIP001          SdrHdl* pHdl = GetHdl(i);
//STRIP001          pHdl->Touch();
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*N*/ void SdrHdlList::SetRotateShear(BOOL bOn)
/*N*/ {
/*N*/   bRotateShear = bOn;
/*N*/ }

/*N*/ void SdrHdlList::SetDistortShear(BOOL bOn)
/*N*/ {
/*N*/   bDistortShear = bOn;
/*N*/ }

/*N*/ void SdrHdlList::SetFineHdl(BOOL bOn)
/*N*/ {
/*N*/   if(bFineHandles != bOn)
/*N*/   {
/*N*/       // remember new state
/*N*/       bFineHandles = bOn;
/*N*/
/*N*/       // propagate change to IAOs
/*N*/       for(UINT32 i=0; i<GetHdlCount(); i++)
/*N*/       {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/            SdrHdl* pHdl = GetHdl(i);
//STRIP001 /*?*/            pHdl->Touch();
/*N*/       }
/*N*/   }
/*N*/ }

//STRIP001 SdrHdl* SdrHdlList::RemoveHdl(ULONG nNum)
//STRIP001 {
//STRIP001  SdrHdl* pRetval = (SdrHdl*)aList.Remove(nNum);
//STRIP001
//STRIP001  return pRetval;
//STRIP001 }

/*N*/ void SdrHdlList::Clear()
/*N*/ {
/*N*/   for (ULONG i=0; i<GetHdlCount(); i++)
/*N*/   {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/        SdrHdl* pHdl=GetHdl(i);
//STRIP001 /*?*/        delete pHdl;
/*N*/   }
/*N*/   aList.Clear();
/*N*/
/*N*/   // immediately remove from display
/*N*/   if(pImpl->pView)
/*N*/       pImpl->pView->RefreshAllIAOManagers();
/*N*/
/*N*/   bRotateShear=FALSE;
/*N*/   bDistortShear=FALSE;
/*N*/ }

/*N*/ void SdrHdlList::Sort()
/*N*/ {
/*N*/   // #97016# II: remember current focused handle
/*N*/   SdrHdl* pPrev = GetFocusHdl();
/*N*/
/*N*/     ImpSdrHdlListSorter aSort(aList);
/*N*/     aSort.DoSort();

    // #97016# II: get now and compare
/*N*/   SdrHdl* pNow = GetFocusHdl();
/*N*/
/*N*/   if(pPrev != pNow)
/*N*/   {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/        sal_Bool bRefresh(sal_False);
//STRIP001 /*?*/
//STRIP001 /*?*/        if(pPrev)
//STRIP001 /*?*/        {
//STRIP001 /*?*/            pPrev->Touch();
//STRIP001 /*?*/            bRefresh = sal_True;
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/        if(pNow)
//STRIP001 /*?*/        {
//STRIP001 /*?*/            pNow->Touch();
//STRIP001 /*?*/            bRefresh = sal_True;
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/        if(bRefresh)
//STRIP001 /*?*/        {
//STRIP001 /*?*/            if(pImpl->pView)
//STRIP001 /*?*/                pImpl->pView->RefreshAllIAOManagers();
//STRIP001 /*?*/        }
/*N*/   }
/*N*/ }

//STRIP001 ULONG SdrHdlList::GetHdlNum(const SdrHdl* pHdl) const
//STRIP001 {
//STRIP001     if (pHdl==NULL) return CONTAINER_ENTRY_NOTFOUND;
//STRIP001     ULONG nPos=aList.GetPos(pHdl);
//STRIP001     return nPos;
//STRIP001 }

//STRIP001 void SdrHdlList::AddHdl(SdrHdl* pHdl, BOOL bAtBegin)
//STRIP001 {
//STRIP001     if (pHdl!=NULL) {
//STRIP001         if (bAtBegin) {
//STRIP001             aList.Insert(pHdl,ULONG(0));
//STRIP001         } else {
//STRIP001             aList.Insert(pHdl,CONTAINER_APPEND);
//STRIP001         }
//STRIP001         pHdl->SetHdlList(this);
//STRIP001     }
//STRIP001 }

/*N*/ SdrHdl* SdrHdlList::HitTest(const Point& rPnt, const OutputDevice& rOut, BOOL bBack, BOOL bNext, SdrHdl* pHdl0) const
/*N*/ {
/*N*/    SdrHdl* pRet=NULL;
/*N*/    ULONG nAnz=GetHdlCount();
/*N*/    ULONG nNum=bBack ? 0 : nAnz;
/*N*/    while ((bBack ? nNum<nAnz : nNum>0) && pRet==NULL) {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/        if (!bBack) nNum--;
//STRIP001 /*?*/        SdrHdl* pHdl=GetHdl(nNum);
//STRIP001 /*?*/        if (bNext) {
//STRIP001 /*?*/            if (pHdl==pHdl0) bNext=FALSE;
//STRIP001 /*?*/        } else {
//STRIP001 /*?*/            if (pHdl->IsHit(rPnt,rOut)) pRet=pHdl;
//STRIP001 /*?*/        }
//STRIP001 /*?*/        if (bBack) nNum++;
/*N*/    }
/*N*/    return pRet;
/*N*/ }

//STRIP001 SdrHdl* SdrHdlList::GetHdl(SdrHdlKind eKind1) const
//STRIP001 {
//STRIP001    SdrHdl* pRet=NULL;
//STRIP001    for (ULONG i=0; i<GetHdlCount() && pRet==NULL; i++) {
//STRIP001        SdrHdl* pHdl=GetHdl(i);
//STRIP001        if (pHdl->GetKind()==eKind1) pRet=pHdl;
//STRIP001    }
//STRIP001    return pRet;
//STRIP001 }

}
