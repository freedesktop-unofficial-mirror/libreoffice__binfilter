/*************************************************************************
 *
 *  $RCSfile: obj3d.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:36 $
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

#ifndef _E3D_OBJ3D_HXX
#define _E3D_OBJ3D_HXX

#ifndef _SVDOATTR_HXX //autogen
#include <bf_svx/svdoattr.hxx>
#endif

#ifndef _SVDOBJ_HXX //autogen
#include <bf_svx/svdobj.hxx>
#endif

#ifndef _VOLUME3D_HXX
#include <bf_svx/volume3d.hxx>
#endif

#ifndef _SVX_MATRIX3D_HXX
#include <bf_svx/matrix3d.hxx>
#endif

#ifndef _DEF3D_HXX
#include <bf_svx/def3d.hxx>
#endif

#ifndef _SVDPAGE_HXX
#include <bf_svx/svdpage.hxx>
#endif

#ifndef _E3D_DEFLT3D_HXX
#include <bf_svx/deflt3d.hxx>
#endif

#ifndef _SV_BITMAP_HXX
#include <vcl/bitmap.hxx>
#endif

#ifndef _B3D_B3DGEOM_HXX
#include <goodies/b3dgeom.hxx>
#endif

#ifndef _B3D_MATRIL3D_HXX
#include <goodies/matril3d.hxx>
#endif

#ifndef _B3D_B3DTEX_HXX
#include <goodies/b3dtex.hxx>
#endif

#ifndef _B3D_B3DLIGHT_HXX
#include <goodies/b3dlight.hxx>
#endif

#ifndef _B3D_BASE3D_HXX
#include <goodies/base3d.hxx>
#endif

#ifndef _SVX3DITEMS_HXX
#include <bf_svx/svx3ditems.hxx>
#endif

#ifndef _SVX_XFLCLIT_HXX
#include <bf_svx/xflclit.hxx>
#endif

//************************************************************
//   Vorausdeklarationen
//************************************************************

class SfxPoolItem;
class Viewport3D;
class E3dLightList;
class E3dScene;
class E3dPolyScene;
class Base3D;
class PolyPolygon3D;

/*************************************************************************
|*
|* Defines fuer nDrawFlag in Paint3D
|*
\************************************************************************/

#define E3D_DRAWFLAG_FILLED                     0x0001
#define E3D_DRAWFLAG_OUTLINE                    0x0002
#define E3D_DRAWFLAG_TRANSPARENT                0x0004
#define E3D_DRAWFLAG_GHOSTED                    0x0008

/*************************************************************************
|*
|* GeoData relevant fuer Undo-Actions
|*
\************************************************************************/

class E3DObjGeoData : public SdrObjGeoData
{
public:
    Volume3D                    aLocalBoundVol;     // umschliessendes Volumen des Objekts
    Matrix4D                    aTfMatrix;          // lokale Transformation

    E3DObjGeoData() {}
};

/*************************************************************************
|*
|* Liste fuer 3D-Objekte
|*
\************************************************************************/

class E3dObjList : public SdrObjList
{
public:
    TYPEINFO();
    E3dObjList(SdrModel* pNewModel, SdrPage* pNewPage, E3dObjList* pNewUpList=NULL);
    E3dObjList(const E3dObjList& rSrcList);
    virtual ~E3dObjList();

    virtual void NbcInsertObject(SdrObject* pObj, ULONG nPos=CONTAINER_APPEND,
        const SdrInsertReason* pReason=NULL);
//STRIP001  virtual SdrObject* NbcRemoveObject(ULONG nObjNum);
    virtual SdrObject* RemoveObject(ULONG nObjNum);
};

/*************************************************************************
|*
|* Basisklasse fuer 3D-Objekte
|*
\************************************************************************/

class E3dObject : public SdrAttrObj
{
    // Aus der E3dObjList und E3dDragMethod alles erlauben
    friend class E3dObjList;
    friend class E3dDragMethod;

 protected:
    E3dObjList*     pSub;               // Subliste (Childobjekte)

    Volume3D        aBoundVol;          // umschliessendes Volumen mit allen Childs
    Volume3D        aLocalBoundVol;     // umschliessendes Volumen des Objekts
    Matrix4D        aTfMatrix;          // lokale Transformation
    Matrix4D        aFullTfMatrix;      // globale Transformation (inkl. Parents)

    UINT16          nLogicalGroup;      // logische Gruppe fuer StarChart
    UINT16          nObjTreeLevel;      // Ebene in der Objekt-Hierarchie
    UINT16          nPartOfParent;      // Objekt ist (Bau-)Teil des Parents,
                                        // wenn ungleich 0; kann objektspezifische
                                        // Codewerte enthalten
    E3dDragDetail   eDragDetail;        // Detailstufe fuer Wireframes

    // Flags
    unsigned        bTfHasChanged           : 1;
    unsigned        bBoundVolValid          : 1;
    unsigned        bIsSelected             : 1;

 public:
    virtual void SetBoundVolInvalid();

 protected:
    virtual void SetTransformChanged();
    virtual void NewObjectInserted(const E3dObject* p3DObj);
    virtual void StructureChanged(const E3dObject* p3DObj);
    virtual void ForceDefaultAttr();
    virtual void RecalcBoundVolume();

    BOOL    ImpCheckSubRecords (const SdrObjIOHeader& rHead,
                                SvStream&             rIn);
    void    SetObjTreeLevel(USHORT nNewLevel);
//STRIP001  void    ImpCreateWireframePoly(XPolyPolygon& rXPP,
//STRIP001                                 E3dDragDetail eDetail = E3DDETAIL_DEFAULT);

    // Wie in SdrAttrObj:
    SfxItemPool* ImpGetItemPool(const SfxPoolItem* pAlternateItem1,
                                const SfxPoolItem* pAlternateItem2) const;
    SfxItemPool* ImpGetItemPool() const;
    const SfxPoolItem* ImpSetNewAttr(const SfxPoolItem* pAkt,
                                     const SfxPoolItem* pNew,
                                     FASTBOOL bChg = TRUE);

 public:
    TYPEINFO();
    E3dObject();
    E3dObject(BOOL bIsFromChart);

    virtual void RecalcSnapRect();
    virtual void RecalcBoundRect();
    virtual void SetRectsDirty(FASTBOOL bNotMyself=FALSE);

    virtual ~E3dObject();

    virtual UINT32  GetObjInventor() const;
    virtual UINT16  GetObjIdentifier() const;

//STRIP001  virtual void    TakeObjInfo(SdrObjTransformInfoRec& rInfo) const;

    virtual SdrLayerID  GetLayer() const;
    virtual void        NbcSetLayer(SdrLayerID nLayer);

    virtual void        SetObjList(SdrObjList* pNewObjList);
    virtual void        SetPage(SdrPage* pNewPage);
    virtual void        SetModel(SdrModel* pNewModel);
//STRIP001  virtual void        NbcMove(const Size& rSize);
/*N*/   virtual void NbcResize(const Point& rRef, const Fraction& xFact, const Fraction& yFact);

    virtual SdrObjList* GetSubList() const;

//STRIP001  virtual void    TakeXorPoly(XPolyPolygon& rPoly, FASTBOOL bDetail) const;
//STRIP001  virtual USHORT  GetHdlCount() const;
//STRIP001  virtual void    AddToHdlList(SdrHdlList& rHdlList) const;
//STRIP001  virtual FASTBOOL HasSpecialDrag() const;

    // 3D-Zeichenmethode
//STRIP001  virtual void Paint3D(ExtOutputDevice& rOut, Base3D* pBase3D,
//STRIP001      const SdrPaintInfoRec& rInfoRec, UINT16 nDrawFlags=0);

    // Objekt als Kontur in das Polygon einfuegen
//STRIP001  virtual void TakeContour3D(XPolyPolygon& rPoly);

    // Schatten fuer 3D-Objekte zeichnen
//STRIP001  virtual void DrawShadows(Base3D *pBase3D, ExtOutputDevice& rXOut,
//STRIP001      const Rectangle& rBound, const Volume3D& rVolume,
//STRIP001      const SdrPaintInfoRec& rInfoRec);

    // 3D-Objekt in die Gruppe einfuegen; Eigentumsuebergang!
    virtual void Insert3DObj(E3dObject* p3DObj);
    void Remove3DObj(E3dObject* p3DObj);

    E3dObject* GetParentObj() const;
    virtual E3dScene* GetScene() const;

    const Volume3D& GetLocalBoundVolume() { return aLocalBoundVol; }
    virtual const Volume3D& GetBoundVolume();
    Vector3D GetCenter();

    // komplette Transformation inklusive aller Parents berechnen
//STRIP001  virtual void GetFullTransform(Matrix4D& rMatrix) const;
    virtual const Matrix4D& GetFullTransform();

    // Transformationsmatrix abfragen bzw. (zurueck)setzen
    virtual const Matrix4D& GetTransform() const;
    virtual void NbcSetTransform(const Matrix4D& rMatrix);
    virtual void NbcResetTransform();
    virtual void SetTransform(const Matrix4D& rMatrix);
//STRIP001  virtual void ResetTransform();

    // Translation
//STRIP001  virtual void NbcTranslate(const Vector3D& rTrans);
//STRIP001  virtual void Translate(const Vector3D& rTrans);
    // Skalierung
//STRIP001  virtual void NbcScaleX  (double fSx);
//STRIP001  virtual void NbcScaleY  (double fSy);
//STRIP001  virtual void NbcScaleZ  (double fSz);
//STRIP001  virtual void NbcScale   (double fSx, double fSy, double fSz);
//STRIP001  virtual void NbcScale   (double fS);

//STRIP001  virtual void ScaleX (double fSx);
//STRIP001  virtual void ScaleY (double fSy);
//STRIP001  virtual void ScaleZ (double fSz);
//STRIP001  virtual void Scale  (double fSx, double fSy, double fSz);
//STRIP001  virtual void Scale  (double fS);

    // Rotation mit Winkel in Radiant
//STRIP001  virtual void NbcRotateX(double fAng);
//STRIP001  virtual void NbcRotateY(double fAng);
//STRIP001  virtual void NbcRotateZ(double fAng);

//STRIP001  virtual void RotateX(double fAng);
//STRIP001  virtual void RotateY(double fAng);
//STRIP001  virtual void RotateZ(double fAng);

    // [FG] 2D-Rotationen, werden hier als Rotationen um die Z-Achse, die in den Bildschirm zeigt,
    //      implementiert plus eine Verschiebung der Scene. Dies bedeutet auch die Scene (E3dScene)
    //      muss diese Routine in der Klasse als virtual definieren.
//STRIP001  virtual void NbcRotate(const Point& rRef, long nWink, double sn, double cs);

    // Transformation auf die Koordinaten (nicht auf die lokale Matrix)
    // eines Objekts und seiner Childs anwenden; Objekte, die eigene
    // Koordinaten speichern, muessen diese Methode implementieren
    // Wireframe-Darstellung des Objekts erzeugen und die Linien als
    // Punkt-Paare in rPoly3D ablegen
//STRIP001  virtual void CreateWireframe(Polygon3D& rWirePoly, const Matrix4D* pTf = NULL,
//STRIP001      E3dDragDetail eDetail = E3DDETAIL_DEFAULT);

    // TakeObjName...() ist fuer die Anzeige in der UI, z.B. "3 Rahmen selektiert".
//STRIP001  virtual void TakeObjNameSingul(String& rName) const;
//STRIP001  virtual void TakeObjNamePlural(String& rName) const;

    USHORT GetObjTreeLevel() const { return nObjTreeLevel; }

    FASTBOOL HasLogicalGroup() { return ( nLogicalGroup > 0 ); }
    USHORT GetLogicalGroup() { return nLogicalGroup; }
//STRIP001  void SetLogicalGroup(USHORT nGroup);

    void SetDragDetail(E3dDragDetail eDetail)   { eDragDetail = eDetail; }
    E3dDragDetail GetDragDetail()               { return eDragDetail; }

    void    SetPartOfParent(UINT16 nPartCode = 1) { nPartOfParent = nPartCode; }
    UINT16  GetPartCode()   { return nPartOfParent; }
    FASTBOOL IsPartOfParent() const { return (nPartOfParent != 0); }

//STRIP001  virtual void operator=(const SdrObject&);

    // ItemSet access
    virtual const SfxItemSet& GetItemSet() const;
    virtual SfxItemSet* CreateNewItemSet(SfxItemPool& rPool);

    // private support routines for ItemSet access. NULL pointer means clear item.
    virtual void ItemChange(const sal_uInt16 nWhich, const SfxPoolItem* pNewItem = 0);

    // #107770# PostItemChange support is necessary here to support the same propagating
    // of scene items like it is done in ItemChange() for E3dObject.
    virtual void PostItemChange(const sal_uInt16 nWhich);

    virtual void ItemSetChanged(const SfxItemSet& rSet);

    virtual void NbcSetStyleSheet(SfxStyleSheet* pNewStyleSheet, FASTBOOL bDontRemoveHardAttr);

    virtual void WriteData(SvStream& rOut) const;
    virtual void ReadData(const SdrObjIOHeader& rHead, SvStream& rIn);
    virtual void AfterRead();

    virtual SdrObjGeoData *NewGeoData() const;
    virtual void          SaveGeoData(SdrObjGeoData& rGeo) const;
    virtual void          RestGeoData(const SdrObjGeoData& rGeo);

    void ForceDefaultAttrAgain ();

    // diese Funktionen schreiben nur die Member von E3dObject wird auch von E3dSphere
    // gerufen.
    void ReadOnlyOwnMembers(const SdrObjIOHeader& rHead, SvStream& rIn);
    void WriteOnlyOwnMembers(SvStream& rOut) const;

    // Selektion Setzen/Lesen
    BOOL GetSelected() { return bIsSelected; }
//STRIP001  void SetSelected(BOOL bNew);

    // Aufbrechen
//STRIP001  virtual BOOL IsBreakObjPossible();
    virtual SdrAttrObj* GetBreakObj();
};

/*************************************************************************
|*
|* Klasse fuer alle zusammengesetzen Objekte (Cube, Lathe, Scene, Extrude)
|* Diese Klasse erspart ein paar ISA-Abfragen und sie beschleunigt das
|* Verhalten ungemein, da alle Attribute usw. fuer die untergeordneten
|* Polygone hierueber gehalten werden. Die Polygone duerfen nur Attribute
|* halten, wenn sie direkt einer Szene untergeordnet sind.
|*
\************************************************************************/

class E3dCompoundObject : public E3dObject
{
    virtual void ForceDefaultAttr();

protected:
    // Die Darstellungsgeometrie dieses Objektes
    B3dGeometry             aDisplayGeometry;

    // Material des Objektes
    Color                   aMaterialAmbientColor;
    B3dMaterial             aBackMaterial;

    // Attribute zur Geometrieerzeugung
    unsigned                bCreateNormals              : 1;
    unsigned                bCreateTexture              : 1;

    // Wird zwischen Vorder- und Hintergrundmaterial unterschieden
    unsigned                bUseDifferentBackMaterial   : 1;

    // Attribut zum Datei lesen altes format
    unsigned                bBytesLeft                  : 1;

    // Switch, ob bei Geometrieerzeugung E3dPolyObj's erzeugt
    // werden sollen (z.B. zum speichern)
    unsigned                bCreateE3dPolyObj           : 1;

    // Geometrie gueltig?
    unsigned                bGeometryValid              : 1;

protected:
    // Hilfsfunktionen zur Geometrieerzeugung
    void GrowPoly(
        PolyPolygon3D& rPolyPolyGrow,
        PolyPolygon3D& rPolyPolyNormals,
        double fFactor);

    void RotatePoly(
        PolyPolygon3D& rPolyPolyRotate,
        Matrix4D& rRotMat);

    void ScalePoly(
        PolyPolygon3D& rPolyPolyScale,
        double fFactor);

//STRIP001  void AddNormals(
//STRIP001      PolyPolygon3D& rPolyPolyDest,
//STRIP001      const PolyPolygon3D& rPolyPolySource);

    void CreateFront(
        const PolyPolygon3D& rPolyPoly3D,
        const PolyPolygon3D& rFrontNormals,
        BOOL bCreateNormals = TRUE,
        BOOL bCreateTexture = TRUE);
    void AddFrontNormals(
        const PolyPolygon3D& rPolyPoly3D,
        PolyPolygon3D& rNormalsFront,
        Vector3D& rOffset);

    void CreateBack(
        const PolyPolygon3D& rPolyPoly3D,
        const PolyPolygon3D& rBackNormals,
        BOOL bCreateNormals = TRUE,
        BOOL bCreateTexture = TRUE);
    void AddBackNormals(
        const PolyPolygon3D& rPolyPoly3D,
        PolyPolygon3D& rNormalsBack,
        Vector3D& rOffset);

    void CreateInBetween(
        const PolyPolygon3D& rPolyPolyFront,
        const PolyPolygon3D& rPolyPolyBack,
        const PolyPolygon3D& rFrontNormals,
        const PolyPolygon3D& rBackNormals,
        BOOL bCreateNormals = TRUE,
        double fSurroundFactor=1.0,
        double fTextureStart=0.0,
        double fTextureDepth=1.0,
        BOOL bRotateTexture90=FALSE);
    void AddInBetweenNormals(
        const PolyPolygon3D& rPolyPolyFront,
        const PolyPolygon3D& rPolyPolyBack,
        PolyPolygon3D& rNormals,
        BOOL bSmoothed = TRUE);

    // Geometrieerzeugung
    void AddGeometry(
        const PolyPolygon3D& rPoly3D,
        BOOL bHintIsComplex=TRUE,
        BOOL bOutline=FALSE);
    void AddGeometry(
        const PolyPolygon3D& rPoly3D,
        const PolyPolygon3D& rVector3D,
        BOOL bHintIsComplex=TRUE,
        BOOL bOutline=FALSE);
    void AddGeometry(
        const PolyPolygon3D& rPoly3D,
        const PolyPolygon3D& rVector3D,
        const PolyPolygon3D& rNormal3D,
        BOOL bHintIsComplex=TRUE,
        BOOL bOutline=FALSE);
    void StartCreateGeometry();

    // Segmenterzeugung
    void ImpCreateSegment(
        const PolyPolygon3D& rFront,        // vorderes Polygon
        const PolyPolygon3D& rBack,         // hinteres Polygon
        const PolyPolygon3D* pPrev = 0L,    // smooth uebergang zu Vorgaenger
        const PolyPolygon3D* pNext = 0L,    // smooth uebergang zu Nachfolger
        BOOL bCreateFront = TRUE,           // vorderen Deckel erzeugen
        BOOL bCreateBack = TRUE,            // hinteren Deckel erzeugen
        double fPercentDiag = 0.05,         // Anteil des Deckels an der Tiefe
        BOOL bSmoothLeft = TRUE,            // Glaetten der umlaufenden Normalen links
        BOOL bSmoothRight = TRUE,           // Glaetten der umlaufenden Normalen rechts
        BOOL bSmoothFrontBack = FALSE,      // Glaetten der Abschlussflaechen
        double fSurroundFactor = 1.0,       // Wertebereich der Texturkoordinaten im Umlauf
        double fTextureStart = 0.0,         // TexCoor ueber Extrude-Tiefe
        double fTextureDepth = 1.0,         // TexCoor ueber Extrude-Tiefe
        BOOL bCreateTexture = TRUE,
        BOOL bCreateNormals = TRUE,
        BOOL bCharacterExtrude = FALSE,     // FALSE=exakt, TRUE=ohne Ueberschneidungen
        BOOL bRotateTexture90 = FALSE,      // Textur der Seitenflaechen um 90 Grad kippen
        PolyPolygon3D* pLineGeometry = NULL // For creation of line geometry
        );

    // #78972# Create vertical polygons for line polygon
    void ImpCompleteLinePolygon(PolyPolygon3D& rLinePolyPoly, sal_uInt16 nPolysPerRun, BOOL bClosed);

    void SetDefaultAttributes(E3dDefaultAttributes& rDefault);

    // convert given PolyPolygon3D to screen coor
//STRIP001  XPolyPolygon TransformToScreenCoor(const PolyPolygon3D &rExtrudePoly);

public :
    TYPEINFO();

    E3dCompoundObject();
    E3dCompoundObject(E3dDefaultAttributes& rDefault);
    virtual ~E3dCompoundObject();

    // DoubleSided: TRUE/FALSE
    BOOL GetDoubleSided() const
        { return ((const Svx3DDoubleSidedItem&)GetUnmergedItemSet().Get(SDRATTR_3DOBJ_DOUBLE_SIDED)).GetValue(); }

    // NormalsKind: 0 == FALSE/FALSE, 1 == TRUE/FALSE, else == TRUE/TRUE
    sal_uInt16 GetNormalsKind() const
        { return ((const Svx3DNormalsKindItem&)GetUnmergedItemSet().Get(SDRATTR_3DOBJ_NORMALS_KIND)).GetValue(); }

    // NormalsInvert: TRUE/FALSE
    BOOL GetNormalsInvert() const
        { return ((const Svx3DNormalsInvertItem&)GetUnmergedItemSet().Get(SDRATTR_3DOBJ_NORMALS_INVERT)).GetValue(); }

    // TextureProjX: 0 == FALSE/FALSE, 1 == TRUE/FALSE, else == TRUE/TRUE
    sal_uInt16 GetTextureProjectionX() const
        { return ((const Svx3DTextureProjectionXItem&)GetUnmergedItemSet().Get(SDRATTR_3DOBJ_TEXTURE_PROJ_X)).GetValue(); }

    // TextureProjY: 0 == FALSE/FALSE, 1 == TRUE/FALSE, else == TRUE/TRUE
    sal_uInt16 GetTextureProjectionY() const
        { return ((const Svx3DTextureProjectionYItem&)GetUnmergedItemSet().Get(SDRATTR_3DOBJ_TEXTURE_PROJ_Y)).GetValue(); }

    // Shadow3D: TRUE/FALSE
    BOOL GetShadow3D() const
        { return ((const Svx3DShadow3DItem&)GetUnmergedItemSet().Get(SDRATTR_3DOBJ_SHADOW_3D)).GetValue(); }

    // MaterialColor: Color
    Color GetMaterialColor() const
        { return ((const Svx3DMaterialColorItem&)GetUnmergedItemSet().Get(SDRATTR_3DOBJ_MAT_COLOR)).GetValue(); }

    // MaterialEmission: Color
    Color GetMaterialEmission() const
        { return ((const Svx3DMaterialEmissionItem&)GetUnmergedItemSet().Get(SDRATTR_3DOBJ_MAT_EMISSION)).GetValue(); }

    // MaterialSpecular: Color
    Color GetMaterialSpecular() const
        { return ((const Svx3DMaterialSpecularItem&)GetUnmergedItemSet().Get(SDRATTR_3DOBJ_MAT_SPECULAR)).GetValue(); }

    // MaterialSpecularIntensity:
    sal_uInt16 GetMaterialSpecularIntensity() const
        { return ((const Svx3DMaterialSpecularIntensityItem&)GetUnmergedItemSet().Get(SDRATTR_3DOBJ_MAT_SPECULAR_INTENSITY)).GetValue(); }

    // TextureKind: 1 == Base3DTextureLuminance, 2 == Base3DTextureIntensity, 3 == Base3DTextureColor
    Base3DTextureKind GetTextureKind() const
        { return (Base3DTextureKind)((const Svx3DTextureKindItem&)GetUnmergedItemSet().Get(SDRATTR_3DOBJ_TEXTURE_KIND)).GetValue(); }

    // TextureMode: 1 == Base3DTextureReplace, 2 == Base3DTextureModulate, 3 == Base3DTextureBlend
    Base3DTextureMode GetTextureMode() const
        { return (Base3DTextureMode)((const Svx3DTextureModeItem&)GetUnmergedItemSet().Get(SDRATTR_3DOBJ_TEXTURE_MODE)).GetValue(); }

    // TextureFilter: TRUE/FALSE
    BOOL GetTextureFilter() const
        { return ((const Svx3DTextureFilterItem&)GetUnmergedItemSet().Get(SDRATTR_3DOBJ_TEXTURE_FILTER)).GetValue(); }

    virtual UINT16 GetObjIdentifier() const;
    virtual void RecalcSnapRect();
    virtual void RecalcBoundRect();
    virtual const Volume3D& GetBoundVolume();

    // private support routines for ItemSet access. NULL pointer means clear item.
    virtual void PostItemChange(const sal_uInt16 nWhich);

    // Hittest, wird an Geometrie weitergegeben
    virtual SdrObject* CheckHit(const Point& rPnt, USHORT nTol,
        const SetOfByte* pVisiLayer) const;

    virtual void WriteData(SvStream& rOut) const;
    virtual void ReadData(const SdrObjIOHeader& rHead, SvStream& rIn);

    // 3D-Zeichenmethode
//STRIP001  virtual void Paint3D(ExtOutputDevice& rOut, Base3D* pBase3D,
//STRIP001      const SdrPaintInfoRec& rInfoRec, UINT16 nDrawFlags=0);

    // Objekt als Kontur in das Polygon einfuegen
//STRIP001  virtual void TakeContour3D(XPolyPolygon& rPoly);

    // Schatten fuer 3D-Objekte zeichnen
//STRIP001  virtual void DrawShadows(Base3D *pBase3D, ExtOutputDevice& rXOut,
//STRIP001      const Rectangle& rBound, const Volume3D& rVolume,
//STRIP001      const SdrPaintInfoRec& rInfoRec);

    // #78972#
//STRIP001  void ImpGetShadowPolygon(PolyPolygon3D& rPoly);
//STRIP001  void ImpDrawShadowPolygon(PolyPolygon3D& rPoly, ExtOutputDevice& rXOut);

    // Bitmaps fuer 3D-Darstellung von Gradients und Hatches holen
//STRIP001  AlphaMask GetAlphaMask(const SfxItemSet& rSet, const Size& rSizePixel);
//STRIP001  Bitmap GetGradientBitmap(const SfxItemSet&);
//STRIP001  Bitmap GetHatchBitmap(const SfxItemSet&);

    // Geometrieerzeugung
    void DestroyGeometry();
    virtual void CreateGeometry();
    void ReCreateGeometry(BOOL bCreateOldGeometry=FALSE);

    // Give out simple line geometry
//STRIP001  virtual void GetLineGeometry(PolyPolygon3D& rLinePolyPolygon) const;

    // Parameter Geometrieerzeugung setzen/lesen
    BOOL GetCreateNormals() const { return bCreateNormals; }
//STRIP001  void SetCreateNormals(BOOL bNew);

    BOOL GetCreateTexture() const { return bCreateTexture; }
//STRIP001  void SetCreateTexture(BOOL bNew);

    // Unterstuetzung Objekte lesen
    BOOL AreBytesLeft() const { return bBytesLeft; }

    // Copy-Operator
//STRIP001  virtual void operator=(const SdrObject&);

    // Ausgabeparameter an 3D-Kontext setzen
//STRIP001  void SetBase3DParams(ExtOutputDevice& rOut, Base3D*,
//STRIP001      BOOL& bDrawObject, BOOL& bDrawOutline, UINT16 nDrawFlags, BOOL bGhosted,
//STRIP001      BOOL bIsLineDraft = FALSE, BOOL bIsFillDraft = FALSE);
private:
//STRIP001  void ImpSet3DParForFill(ExtOutputDevice& rOut, Base3D* pBase3D,
//STRIP001      BOOL& bDrawObject, UINT16 nDrawFlags, BOOL bGhosted, BOOL bIsFillDraft);
//STRIP001  void ImpSet3DParForLine(ExtOutputDevice& rOut, Base3D* pBase3D,
//STRIP001      BOOL& bDrawOutline, UINT16 nDrawFlags, BOOL bGhosted, BOOL bIsLineDraft);
public:

    // DisplayGeometry rausruecken
    B3dGeometry& GetDisplayGeometry();

    // Transformation auf die Geometrie anwenden
//STRIP001  void CenterObject(const Vector3D& rCenter = Vector3D());

    // Schattenattribute holen
//STRIP001  Color GetShadowColor();
//STRIP001  BOOL DrawShadowAsOutline();
//STRIP001  INT32 GetShadowXDistance();
//STRIP001  INT32 GetShadowYDistance();
//STRIP001  UINT16 GetShadowTransparence();
    BOOL DoDrawShadow();

    // WireFrame Darstellung eines Objektes
//STRIP001  void DrawObjectWireframe(ExtOutputDevice& rOut);

    // Nromalen invertiert benutzen
private:
    void SetInvertNormals(BOOL bNew);
public:

    // Material des Objektes
    const Color& GetMaterialAmbientColor() const { return aMaterialAmbientColor; }
    void SetMaterialAmbientColor(const Color& rColor);

    const B3dMaterial& GetBackMaterial() const { return aBackMaterial; }
//STRIP001  void SetBackMaterial(const B3dMaterial& rNew);
    BOOL GetUseDifferentBackMaterial() const { return bUseDifferentBackMaterial; }
//STRIP001  void SetUseDifferentBackMaterial(BOOL bNew);
};

#endif          // _E3D_OBJ3D_HXX
