/*************************************************************************
 *
 *  $RCSfile: svdhdl.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:28:49 $
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

#ifndef _SVDHDL_HXX
#define _SVDHDL_HXX

#ifndef _GEN_HXX //autogen
#include <tools/gen.hxx>
#endif

#ifndef _POINTR_HXX //autogen
#include <vcl/pointr.hxx>
#endif

#ifndef _CONTNR_HXX //autogen
#include <tools/contnr.hxx>
#endif

#ifndef _SOLAR_HRC
#include <svtools/solar.hrc>
#endif

#ifndef _B2D_MPNT_HXX
#include <goodies/b2dmpnt.hxx>
#endif

#ifndef _B2D_MLINE_HXX
#include <goodies/b2dmline.hxx>
#endif

#ifndef _B2D_MBMP_HXX
#include <goodies/b2dmbmp.hxx>
#endif

#include <bf_svx/xpoly.hxx>
#include <bf_svx/svdoedge.hxx>
class VirtualDevice;
class OutputDevice;
class Region;
class Window;
namespace binfilter {


class SdrHdlList;
class SdrObject;
class SdrPageView;
class SdrHdlBitmapSet;

////////////////////////////////////////////////////////////////////////////////////////////////////

// Jedes Objekt muss in der Lage seine Handles zu erzeugen. Diese werden dann
// bei einer Selektion abgeholt, bei der View angemeldet und sichtbar gemacht.
// Wird ein Handle von der Maus beruehrt (IsHit()), so wird von der View der
// entsprechende Mauszeiger vom Handle abgeholt und der App auf Anfrage zum
// reinschalten uebergeben.
// Handles wie z.B. der Rotationsmittelpunkt oder die Spiegelachse werden von
// der View generiert, wenn vom Controller der entsprechende Transformations-
// Modus selektiert wird.
// HDL_MOVE...HDL_LWRGT muessen im enum immer zusammen stehen bleiben!

enum SdrHdlKind
{
    HDL_MOVE,       // Handle zum Verschieben des Objekts
    HDL_UPLFT,      // Oben links
    HDL_UPPER,      // Oben
    HDL_UPRGT,      // Oben rechts
    HDL_LEFT,       // Links
    HDL_RIGHT,      // Rechts
    HDL_LWLFT,      // Unten links
    HDL_LOWER,      // Unten
    HDL_LWRGT,      // Unten rechts
    HDL_POLY,       // Punktselektion an Polygon oder Bezierkurve
    HDL_BWGT,       // Gewicht an einer Bezierkurve
    HDL_CIRC,       // Winkel an Kreissegmenten, Eckenradius am Rect
    HDL_REF1,       // Referenzpunkt 1, z.B. Rotationsmitte
    HDL_REF2,       // Referenzpunkt 2, z.B. Endpunkt der Spiegelachse
    HDL_MIRX,       // Die Spiegelachse selbst
    HDL_GLUE,       // GluePoint
    HDL_ANCHOR,     // anchor symbol (SD, SW)
    HDL_TRNS,       // interactive transparence
    HDL_GRAD,       // interactive gradient
    HDL_COLR,       // interactive color
    HDL_USER,
    HDL_ANCHOR_TR   // #101688# Anchor handle with (0,0) at top right for SW
};

////////////////////////////////////////////////////////////////////////////////////////////////////

enum BitmapColorIndex
{
    LightGreen,
    Cyan,
    LightCyan,
    Red,
    LightRed
};

////////////////////////////////////////////////////////////////////////////////////////////////////

enum BitmapMarkerKind
{
    Rect_7x7,
    Rect_9x9,
    Rect_11x11,
    Rect_13x13,
    Circ_7x7,
    Circ_9x9,
    Circ_11x11,
    Elli_7x9,
    Elli_9x11,
    Elli_9x7,
    Elli_11x9,
    RectPlus_7x7,
    RectPlus_9x9,
    RectPlus_11x11,
    Crosshair,
    Glue,
    Anchor,

    // #98388# add AnchorPressed to be able to aninate anchor control, too.
    AnchorPressed,

    // #101688# AnchorTR for SW
    AnchorTR,
    AnchorPressedTR
};

////////////////////////////////////////////////////////////////////////////////////////////////////

class SdrHdl
{
    friend class                SdrMarkView; // fuer den Zugriff auf nObjHdlNum
//STRIP001  friend class                SdrHdlList;
//STRIP001
//STRIP001  static SdrHdlBitmapSet*     pSimpleSet;
//STRIP001  static SdrHdlBitmapSet*     pModernSet;
//STRIP001
//STRIP001  // #101928#
//STRIP001  static SdrHdlBitmapSet*     pHighContrastSet;
//STRIP001
//STRIP001  // #101928#
//STRIP001  BitmapEx& ImpGetBitmapEx(BitmapMarkerKind eKindOfMarker, sal_uInt16 nInd, sal_Bool bFine, sal_Bool bIsHighContrast);
//STRIP001
//STRIP001 protected:
//STRIP001  SdrObject*                  pObj;      // Gehoert das Handle zu einem Objekt?
//STRIP001  SdrPageView*                pPV;       // Gehoert das Handle zu einem Objekt in einer bestimmten PageView?
//STRIP001  SdrHdlList*                 pHdlList;  // Zum Feststelen der Handlegroesse
//STRIP001
//STRIP001  // group of IAOs, normally only one
//STRIP001  B2dIAOGroup                 aIAOGroup;
//STRIP001
//STRIP001  Point                       aPos;
//STRIP001
//STRIP001  SdrHdlKind                  eKind;
//STRIP001
//STRIP001  long                        nDrehWink; // Handles bzw. Mauszeiger drehen
//STRIP001  USHORT                      nObjHdlNum; // wird von der MarkView benoetigt
//STRIP001  USHORT                      nPolyNum;  // Polygonpunktes
//STRIP001  USHORT                      nPPntNum;  // Punktnummer des Polygons
//STRIP001  USHORT                      nSourceHdlNum; // ist noch vollstaendig zu implementieren
//STRIP001
//STRIP001  unsigned                    bSelect : 1;   // Ein selektierter Polygonpunkt?
//STRIP001  unsigned                    b1PixMore : 1; // True=Handle wird 1 Pixel groesser dargestellt
//STRIP001  unsigned                    bPlusHdl : 1;  // u.a. fuer Hld-Paint Optimierung bei MarkPoint/UnmarkPoint, ...
//STRIP001
//STRIP001  // create marker for this kind
//STRIP001  virtual void CreateB2dIAObject();
//STRIP001
//STRIP001  // cleanup marker if one exists
//STRIP001  void GetRidOfIAObject();
//STRIP001
//STRIP001 protected:
//STRIP001  B2dIAObject* CreateMarkerObject(B2dIAOManager* pMan, Point aPos, BitmapColorIndex eColIndex, BitmapMarkerKind eKindOfMarker);
//STRIP001  BitmapMarkerKind GetNextBigger(BitmapMarkerKind eKnd) const;
//STRIP001
public:
    SdrHdl();
    SdrHdl(const Point& rPnt, SdrHdlKind eNewKind=HDL_MOVE);
    virtual ~SdrHdl();

//STRIP001  const B2dIAOGroup& GetIAOGroup() const { return aIAOGroup; }
//STRIP001
//STRIP001  void SetHdlList(SdrHdlList* pList);
    SdrHdlKind GetKind() const { DBG_ASSERT(0, "STRIP"); return HDL_MOVE; }//STRIP001   SdrHdlKind GetKind() const { return eKind; }
//STRIP001  void Touch();
//STRIP001
//STRIP001  const Point& GetPos() const { return aPos; }
//STRIP001  void SetPos(const Point& rPnt);
//STRIP001
//STRIP001  SdrPageView* GetPageView() const { return pPV; }
//STRIP001  void SetPageView(SdrPageView* pNewPV) { pPV=pNewPV; }
//STRIP001
    SdrObject* GetObj() const {DBG_ASSERT(0, "STRIP"); return NULL;  }//STRIP001    SdrObject* GetObj() const { return pObj;  }
//STRIP001  void SetObj(SdrObject* pNewObj);
//STRIP001
//STRIP001  BOOL IsSelected() const { return bSelect; }
//STRIP001  void SetSelected(BOOL bJa=TRUE);
//STRIP001
//STRIP001  void Set1PixMore(BOOL bJa=TRUE);
//STRIP001  void SetDrehWink(long n);
//STRIP001
//STRIP001  BOOL IsCornerHdl() const { return eKind==HDL_UPLFT || eKind==HDL_UPRGT || eKind==HDL_LWLFT || eKind==HDL_LWRGT; }
//STRIP001  BOOL IsVertexHdl() const { return eKind==HDL_UPPER || eKind==HDL_LOWER || eKind==HDL_LEFT  || eKind==HDL_RIGHT; }
//STRIP001
//STRIP001  void SetObjHdlNum(USHORT nNum) { nObjHdlNum=nNum; }
//STRIP001  USHORT GetObjHdlNum() const { return nObjHdlNum; }
//STRIP001
//STRIP001  void SetPolyNum(USHORT nNum) { nPolyNum=nNum; }
//STRIP001  USHORT GetPolyNum() const { return nPolyNum; }
//STRIP001
//STRIP001  void SetPointNum(USHORT nNum) { nPPntNum=nNum; }
//STRIP001  USHORT GetPointNum() const { return nPPntNum; }
//STRIP001
//STRIP001  void SetPlusHdl(BOOL bOn) { bPlusHdl=bOn; }
//STRIP001  BOOL IsPlusHdl() const { return bPlusHdl; }
//STRIP001
//STRIP001  void SetSourceHdlNum(USHORT nNum) { nSourceHdlNum=nNum; }
//STRIP001  USHORT GetSourceHdlNum() const { return nSourceHdlNum; }
//STRIP001
//STRIP001  virtual Pointer GetPointer() const;
//STRIP001  virtual BOOL IsHit(const Point& rPnt, const OutputDevice& rOut) const;
//STRIP001
//STRIP001  // #97016# II
//STRIP001  virtual BOOL IsFocusHdl() const;
};

////////////////////////////////////////////////////////////////////////////////////////////////////

#define SDR_HANDLE_COLOR_SIZE_NORMAL            Size(13, 13)
#define SDR_HANDLE_COLOR_SIZE_SELECTED          Size(17, 17)

//STRIP001 class SdrHdlColor : public SdrHdl
//STRIP001 {
//STRIP001 private:
//STRIP001  // size of colr markers
//STRIP001  Size                        aMarkerSize;
//STRIP001
//STRIP001  // color
//STRIP001  Color                       aMarkerColor;
//STRIP001
//STRIP001  // callback link when value changed
//STRIP001     Link                     aColorChangeHdl;
//STRIP001
//STRIP001  // use luminance values only
//STRIP001  unsigned                    bUseLuminance : 1;
//STRIP001
//STRIP001  // create marker for this kind
//STRIP001  virtual void CreateB2dIAObject();
//STRIP001
//STRIP001  // help functions
//STRIP001  Bitmap CreateColorDropper(Color aCol);
//STRIP001  Color GetLuminance(const Color& rCol);
//STRIP001  void CallColorChangeLink();
//STRIP001
//STRIP001 public:
//STRIP001  SdrHdlColor(const Point& rRef, Color aCol = Color(COL_BLACK), const Size& rSize = Size(11, 11), BOOL bLum = FALSE);
//STRIP001  virtual ~SdrHdlColor();
//STRIP001
//STRIP001  BOOL IsUseLuminance() const { return bUseLuminance; }
//STRIP001
//STRIP001  Color GetColor() const { return aMarkerColor; }
//STRIP001  void SetColor(Color aNew, BOOL bCallLink = FALSE);
//STRIP001
//STRIP001  const Size& GetSize() const { return aMarkerSize; }
//STRIP001  void SetSize(const Size& rNew);
//STRIP001
//STRIP001     void SetColorChangeHdl(const Link& rLink) { aColorChangeHdl = rLink; }
//STRIP001     const Link& GetColorChangeHdl() const { return aColorChangeHdl; }
//STRIP001 };

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 class SdrHdlGradient : public SdrHdl
//STRIP001 {
//STRIP001 private:
//STRIP001  // pointer to used color handles
//STRIP001  SdrHdlColor*                pColHdl1;
//STRIP001  SdrHdlColor*                pColHdl2;
//STRIP001
//STRIP001  // 2nd position
//STRIP001  Point                       a2ndPos;
//STRIP001
//STRIP001  // is this a gradient or a transparence
//STRIP001  unsigned                    bGradient : 1;
//STRIP001
//STRIP001  // select which handle to move
//STRIP001  unsigned                    bMoveSingleHandle : 1;
//STRIP001  unsigned                    bMoveFirstHandle : 1;
//STRIP001
//STRIP001  // create marker for this kind
//STRIP001  virtual void CreateB2dIAObject();
//STRIP001
//STRIP001 public:
//STRIP001  SdrHdlGradient(const Point& rRef1, const Point& rRef2, BOOL bGrad = TRUE);
//STRIP001  virtual ~SdrHdlGradient();
//STRIP001
//STRIP001  BOOL IsGradient() const { return bGradient; }
//STRIP001
//STRIP001  // set the associated color handles
//STRIP001  void SetColorHandles(SdrHdlColor* pL1, SdrHdlColor* pL2) { pColHdl1 = pL1; pColHdl2 = pL2; }
//STRIP001  SdrHdlColor* GetColorHdl1() const { return pColHdl1; }
//STRIP001  SdrHdlColor* GetColorHdl2() const { return pColHdl2; }
//STRIP001
//STRIP001  const Point& Get2ndPos() const { return a2ndPos; }
//STRIP001  void Set2ndPos(const Point& rPnt);
//STRIP001
//STRIP001  // the link called by the color handles
//STRIP001  DECL_LINK(ColorChangeHdl, SdrHdl*);
//STRIP001
//STRIP001  // transformation call, create gradient from this handle
//STRIP001  void FromIAOToItem(SdrObject* pObj, BOOL bSetItemOnObject, BOOL bUndo);
//STRIP001
//STRIP001  // selection flags for interaction
//STRIP001  BOOL IsMoveSingleHandle() const { return bMoveSingleHandle; }
//STRIP001  void SetMoveSingleHandle(BOOL bNew) { bMoveSingleHandle = bNew; }
//STRIP001  BOOL IsMoveFirstHandle() const { return bMoveFirstHandle; }
//STRIP001  void SetMoveFirstHandle(BOOL bNew) { bMoveFirstHandle = bNew; }
//STRIP001 };

////////////////////////////////////////////////////////////////////////////////////////////////////

// Spiegelachse
//STRIP001 class SdrHdlLine: public SdrHdl
//STRIP001 {
//STRIP001  // create marker for this kind
//STRIP001  virtual void CreateB2dIAObject();
//STRIP001
//STRIP001 protected:
//STRIP001  SdrHdl*                     pHdl1;
//STRIP001  SdrHdl*                     pHdl2;
//STRIP001
//STRIP001 public:
//STRIP001  SdrHdlLine(SdrHdl& rHdl1, SdrHdl& rHdl2, SdrHdlKind eNewKind=HDL_MIRX) { eKind=eNewKind; pHdl1=&rHdl1; pHdl2=&rHdl2; }
//STRIP001  virtual ~SdrHdlLine();
//STRIP001
//STRIP001  virtual Pointer GetPointer() const;
//STRIP001  virtual BOOL IsHit(const Point& rPnt, const OutputDevice& rOut) const;
//STRIP001 };

// Ein SdrHdlBezWgt hat Kenntnis von seinem "BasisHandle". Seine Draw-Methode
// zeichnet zusaetzlich eine Linie von seiner Position zur Position dieses
// BasisHandles.
//STRIP001 class SdrHdlBezWgt: public SdrHdl
//STRIP001 {
//STRIP001  // create marker for this kind
//STRIP001  virtual void CreateB2dIAObject();
//STRIP001
//STRIP001 protected:
//STRIP001  const SdrHdl* pHdl1;
//STRIP001
//STRIP001 public:
//STRIP001  // das ist kein Copy-Ctor!!!
//STRIP001  SdrHdlBezWgt(const SdrHdl* pRefHdl1, SdrHdlKind eNewKind=HDL_BWGT) { eKind=eNewKind; pHdl1=pRefHdl1; }
//STRIP001  virtual ~SdrHdlBezWgt();
//STRIP001 };

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 class E3dVolumeMarker : public SdrHdl
//STRIP001 {
//STRIP001  XPolyPolygon    aWireframePoly;
//STRIP001
//STRIP001  // create marker for this kind
//STRIP001  virtual void CreateB2dIAObject();
//STRIP001
//STRIP001 public:
//STRIP001  E3dVolumeMarker(const XPolyPolygon& rXPP);
//STRIP001 };

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 class ImpEdgeHdl: public SdrHdl
//STRIP001 {
//STRIP001  SdrEdgeLineCode eLineCode;
//STRIP001
//STRIP001  // create marker for this kind
//STRIP001  virtual void CreateB2dIAObject();
//STRIP001
//STRIP001 public:
//STRIP001  ImpEdgeHdl(const Point& rPnt, SdrHdlKind eNewKind): SdrHdl(rPnt,eNewKind),eLineCode(MIDDLELINE) {}
//STRIP001  virtual ~ImpEdgeHdl();
//STRIP001
//STRIP001  void SetLineCode(SdrEdgeLineCode eCode);
//STRIP001  SdrEdgeLineCode GetLineCode() const     { return eLineCode; }
//STRIP001  BOOL IsHorzDrag() const;
//STRIP001  virtual Pointer GetPointer() const;
//STRIP001 };

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 class ImpMeasureHdl: public SdrHdl
//STRIP001 {
//STRIP001  // create marker for this kind
//STRIP001  virtual void CreateB2dIAObject();
//STRIP001
//STRIP001 public:
//STRIP001  ImpMeasureHdl(const Point& rPnt, SdrHdlKind eNewKind): SdrHdl(rPnt,eNewKind) {}
//STRIP001  virtual ~ImpMeasureHdl();
//STRIP001
//STRIP001  virtual Pointer GetPointer() const;
//STRIP001 };

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

// #97016# II
class ImplHdlListData;

class SdrHdlList
{
protected:
    // #97016# II: use ImplHdlListData here to hold two data items
    //SdrMarkView*              pView;
    ImplHdlListData*            pImpl;

    Container                   aList;
    USHORT                      nHdlSize;

    unsigned                    bRotateShear : 1;
    unsigned                    bDistortShear : 1;
    unsigned                    bMoveOutside : 1;      // Handles nach aussen ruecken (fuer TextEdit)
    unsigned                    bFineHandles : 1;

private:
    SdrHdlList(const SdrHdlList&): aList(1024,64,64)  {}
    void operator=(const SdrHdlList&)                 {}
    BOOL operator==(const SdrHdlList&) const      { return FALSE; }
    BOOL operator!=(const SdrHdlList&) const      { return FALSE; }

public:
    SdrHdlList(SdrMarkView* pV);
    ~SdrHdlList();
    void Clear();

    // #97016# II
//STRIP001  void TravelFocusHdl(sal_Bool bForward);
    SdrHdl* GetFocusHdl() const;
//STRIP001  void SetFocusHdl(SdrHdl* pNew);
    void ResetFocusHdl();

    // Access to View
    // #97016# II: moved implementation to cxx
    SdrMarkView* GetView() const;

    // Sortierung: 1.Level Erst Refpunkt-Handles, dann normale Handles, dann Glue, dann User, dann Plushandles
    //             2.Level PageView (Pointer)
    //             3.Level Position (x+y)
    void     Sort();
    ULONG    GetHdlCount() const                       { return aList.Count(); }
    SdrHdl*  GetHdl(ULONG nNum) const                  { return (SdrHdl*)(aList.GetObject(nNum)); }
//STRIP001  ULONG    GetHdlNum(const SdrHdl* pHdl) const;
//STRIP001  void     SetHdlSize(USHORT nSiz);
    USHORT   GetHdlSize() const                        { return nHdlSize; }
//STRIP001  void     SetMoveOutside(BOOL bOn);
    BOOL IsMoveOutside() const                     { return bMoveOutside; }
    void     SetRotateShear(BOOL bOn);
    BOOL IsRotateShear() const                     { return bRotateShear; }
    void     SetDistortShear(BOOL bOn);
    BOOL IsDistortShear() const                    { return bDistortShear; }
    void     SetFineHdl(BOOL bOn);
    BOOL IsFineHdl() const                        { return bFineHandles; }

    // AddHdl uebernimmt das Handle in sein Eigentum. Es muss
    // also auf dem Heap stehen, da Clear() ein delete macht.
//STRIP001  void    AddHdl(SdrHdl* pHdl, BOOL bAtBegin=FALSE);
//STRIP001  SdrHdl* RemoveHdl(ULONG nNum);

    // Zuletzt eingefuegte Handles werden am ehesten getroffen
    // (wenn Handles uebereinander liegen).
    SdrHdl* HitTest(const Point& rPnt, const OutputDevice& rOut, BOOL bBack=FALSE, BOOL bNext=FALSE, SdrHdl* pHdl0=NULL) const;
//STRIP001  SdrHdl* GetHdl(SdrHdlKind eKind1) const;
};

}//end of namespace binfilter
#endif //_SVDHDL_HXX

