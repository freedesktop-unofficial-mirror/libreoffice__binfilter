/*************************************************************************
 *
 *  $RCSfile: svdograf.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:28:53 $
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

#ifndef _SVDOGRAF_HXX
#define _SVDOGRAF_HXX

#ifndef _SV_GRAPH_HXX //autogen
#include <vcl/graph.hxx>
#endif
#ifndef _SVDORECT_HXX
#include <bf_svx/svdorect.hxx>
#endif
#ifndef _GRFMGR_HXX
#include <goodies/grfmgr.hxx>
#endif
class GraphicObject;
namespace binfilter {

// -----------
// - Defines -
// -----------

#define SDRGRAFOBJ_TRANSFORMATTR_NONE       0x00000000UL
#define SDRGRAFOBJ_TRANSFORMATTR_COLOR      0x00000001UL
#define SDRGRAFOBJ_TRANSFORMATTR_MIRROR     0x00000002UL
#define SDRGRAFOBJ_TRANSFORMATTR_ROTATE     0x00000004UL
#define SDRGRAFOBJ_TRANSFORMATTR_ALL        0xffffffffUL

// ---------------------
// - SdrGrafObjGeoData -
// ---------------------

class Animation;

class SdrGrafObjGeoData : public SdrRectObjGeoData
{
public:

    FASTBOOL    bMirrored;

                SdrGrafObjGeoData() :
                    bMirrored( FALSE ) {}
};

// --------------
// - SdrGrafObj -
// --------------

class SdrGrafSetItem;

class SdrGrafObj: public SdrRectObj
{

    friend class SdrGraphicLink;

protected:

    void                    ImpSetAttrToGrafInfo(); // Werte vom Pool kopieren
    void                    ImpSetGrafInfoToAttr(); // Werte in den Pool kopieren
    GraphicAttr             aGrafInfo;
    FASTBOOL                bCopyToPoolOnAfterRead;

    String                  aName;

    Rectangle               aCropRect;          // Wenn aCropRect nicht Empty ist, dann enthaelt es den sichtbaren
                                                // Ausschnitt der Grafik in logischen Eingeiten der Grafik! Also Bitmap->=Pixel
    String                  aFileName;          // Wenn es sich um einen Link handelt, steht hier der Dateiname drin.
    String                  aFilterName;
    GraphicObject*          pGraphic;           // Zur Beschleunigung von Bitmapausgaben, besonders von gedrehten.
    void*                   pReserve1;
    void*                   pReserve2;
    void*                   pReserve3;
    void*                   pReserve4;
    void*                   pReserve5;
    SdrGraphicLink*         pGraphicLink;       // Und hier noch ein Pointer fuer gelinkte Grafiken
    FASTBOOL                bMirrored;          // True bedeutet, die Grafik ist horizontal, d.h. ueber die Y-Achse gespiegelt auszugeben.
    ULONG                   nGrafStreamPos;
    FASTBOOL                bDummy1:1;
    FASTBOOL                bDummy2:1;

#if _SOLAR__PRIVATE

    void                    ImpLinkAnmeldung();
    void                    ImpLinkAbmeldung();
//STRIP001  FASTBOOL                ImpPaintEmptyPres(OutputDevice* pOutDev) const;
    void                    ImpPaintReplacement(OutputDevice* pOutDev, const XubString& rText, const Bitmap* pBmp, FASTBOOL bFill) const;

    sal_Bool                ImpUpdateGraphicLink() const;

                            DECL_LINK( ImpSwapHdl, GraphicObject* );
//STRIP001                          DECL_LINK( ImpAnimationHdl, Animation* );

#endif // __PRIVATE

public:

                            TYPEINFO();

                            SdrGrafObj();
                            SdrGrafObj(const Graphic& rGrf);
                            SdrGrafObj(const Graphic& rGrf, const Rectangle& rRect);
    virtual                 ~SdrGrafObj();

    void                    SetGraphicObject( const GraphicObject& rGrfObj );
    const GraphicObject&    GetGraphicObject() const;

    void                    SetGraphic(const Graphic& rGrf);
    const Graphic&          GetGraphic() const;

    Graphic                 GetTransformedGraphic( ULONG nTransformFlags = SDRGRAFOBJ_TRANSFORMATTR_ALL ) const;

    GraphicType             GetGraphicType() const;
//STRIP001  FASTBOOL                IsAnimated() const;
//STRIP001  FASTBOOL                IsTransparent() const;
//STRIP001  FASTBOOL                IsEPS() const;
//STRIP001  const MapMode&          GetGrafPrefMapMode() const;
//STRIP001  const Size&             GetGrafPrefSize() const;

    void                    SetGrafStreamURL( const String& rGraphicStreamURL );
    String                  GetGrafStreamURL() const;

    void                    ForceSwapIn() const;
    void                    ForceSwapOut() const;

    void                    SetGraphicLink(const String& rFileName, const String& rFilterName);
    void                    ReleaseGraphicLink();
    FASTBOOL                IsLinkedGraphic() const { return (BOOL)aFileName.Len(); }

//STRIP001  void                    SetFileName(const String& rFileName);
    const String&           GetFileName() const { return aFileName; }
//STRIP001  void                    SetFilterName(const String& rFilterName);
    const String&           GetFilterName() const { return aFilterName; }

//STRIP001  void                    StartAnimation(OutputDevice* pOutDev, const Point& rPoint, const Size& rSize, long nExtraData=0L);
//STRIP001  void                    StopAnimation(OutputDevice* pOutDev=NULL, long nExtraData=0L);
//STRIP001  void                    SetAnimationSupervisor(OutputDevice* pDisplayDev, BOOL bObjSupervises);
//STRIP001  void                    ResetAnimationLoopCount();
//STRIP001  Rectangle               GetAnimationRect(const OutputDevice* pOutDev) const;

//STRIP001  virtual FASTBOOL        HasSetName() const;

    virtual void            SetName(const String& rStr);
    virtual String          GetName() const;

//STRIP001  virtual void            TakeObjInfo(SdrObjTransformInfoRec& rInfo) const;
    virtual UINT16          GetObjIdentifier() const;
    virtual FASTBOOL        Paint(ExtOutputDevice& rOut, const SdrPaintInfoRec& rInfoRec) const;
    virtual SdrObject*      CheckHit(const Point& rPnt, USHORT nTol, const SetOfByte* pVisiLayer) const;

//STRIP001  virtual void            TakeObjNameSingul(String& rName) const;
//STRIP001  virtual void            TakeObjNamePlural(String& rName) const;

    virtual void            operator=(const SdrObject& rObj);
//STRIP001  virtual FASTBOOL        HasSpecialDrag() const;
//STRIP001  virtual USHORT          GetHdlCount() const;
//STRIP001  virtual SdrHdl*         GetHdl(USHORT nHdlNum) const;

    virtual void            NbcResize(const Point& rRef, const Fraction& xFact, const Fraction& yFact);
    virtual void            NbcRotate(const Point& rRef, long nWink, double sn, double cs);
//STRIP001  virtual void            NbcMirror(const Point& rRef1, const Point& rRef2);
//STRIP001  virtual void            NbcShear (const Point& rRef, long nWink, double tn, FASTBOOL bVShear);
    virtual void            NbcSetSnapRect(const Rectangle& rRect);
    virtual void            NbcSetLogicRect(const Rectangle& rRect);
    virtual SdrObjGeoData*  NewGeoData() const;
    virtual void            SaveGeoData(SdrObjGeoData& rGeo) const;
//STRIP001  virtual void            RestGeoData(const SdrObjGeoData& rGeo);
    virtual void            RestartAnimation(SdrPageView* pPageView) const;

    FASTBOOL                HasGDIMetaFile() const;
    const GDIMetaFile*      GetGDIMetaFile() const;

    virtual void            SetPage(SdrPage* pNewPage);
    virtual void            SetModel(SdrModel* pNewModel);
    virtual void            WriteData(SvStream& rOut) const;
    virtual void            ReadData(const SdrObjIOHeader& rHead, SvStream& rIn);
    void                    ReadDataTilV10(const SdrObjIOHeader& rHead, SvStream& rIn);

//STRIP001  virtual SdrObject*      DoConvertToPolyObj(BOOL bBezier) const;

    void                    AdjustToMaxRect( const Rectangle& rMaxRect, BOOL bShrinkOnly );

    virtual void            SFX_NOTIFY( SfxBroadcaster& rBC, const TypeId& rBCType,
                                        const SfxHint& rHint, const TypeId& rHintType );
    virtual void            ForceDefaultAttr();
    virtual void            NbcSetStyleSheet( SfxStyleSheet* pNewStyleSheet, FASTBOOL bDontRemoveHardAttr );

    // ItemSet access
    virtual SfxItemSet* CreateNewItemSet(SfxItemPool& rPool);

    // private support routines for ItemSet access. NULL pointer means clear item.
    virtual void ItemSetChanged(const SfxItemSet& rSet);

    // pre- and postprocessing for objects for saving
    virtual void PreSave();
    virtual void PostSave();

    virtual void            AfterRead();

    BOOL                    IsMirrored() { return bMirrored; }
    void                    SetMirrored( sal_Bool _bMirrored ) { bMirrored = _bMirrored; }
};

}//end of namespace binfilter
#endif //_SVDOGRAF_HXX

