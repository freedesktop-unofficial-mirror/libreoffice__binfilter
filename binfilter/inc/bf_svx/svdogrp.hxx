/*************************************************************************
 *
 *  $RCSfile: svdogrp.hxx,v $
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

#ifndef _SVDOGRP_HXX
#define _SVDOGRP_HXX

#ifndef _DATETIME_HXX //autogen
#include <tools/datetime.hxx>
#endif

#ifndef _SVDOBJ_HXX
#include <bf_svx/svdobj.hxx>
#endif
class SdrObjListIter;
class SfxItemSet;
namespace binfilter {

//************************************************************
//   Vorausdeklarationen
//************************************************************

class ImpSdrObjGroupLink;
class SdrObjList;

//************************************************************
//   Defines
//************************************************************

#define SDRUSERDATA_OBJGROUPLINK    0

//************************************************************
//   Hilfsklasse ImpSdrObjGroupLinkUserData
//************************************************************

class ImpSdrObjGroupLinkUserData : public SdrObjUserData
{
    friend class                SdrObjGroup;
    friend class                ImpSdrObjGroupLink;

    SdrObject*                  pObj;
    String                      aFileName;   // Name des referenzierten Dokuments
    XubString                   aObjName;    // Name des referenzierten Objekts
    DateTime                    aFileDate0;  // Unnoetiges neuladen vermeiden
    Rectangle                   aSnapRect0;  // Letztes bekanntes SnapRect des Originals
    long                        nDrehWink0;  // Letzter bekannter Drehwinkel des Originals
    long                        nShearWink0; // Letzter bekannter Shearwinkel des Originals

    ImpSdrObjGroupLink*         pLink;
    ULONG                       nObjNum;     // des referenzierten Objekts
    USHORT                      nPageNum;    // zum schnelleren wiederauffinden
    FASTBOOL                    bMasterPage; // Liegt im Referenzdokoment auf einer Masterpage

    FASTBOOL                    bOrigPos;    // Objekt hat immer die Position des Referenzobjekts
    FASTBOOL                    bOrigSize;   // Objekt hat immer die Groesse des Referenzobjekts
    FASTBOOL                    bOrigRotate; // Objekt hat immer die Drehung des Referenzobjekts
    FASTBOOL                    bOrigShear;  // Objekt hat immer den Shearwinkel des Referenzobjekts

public:
    TYPEINFO();

    ImpSdrObjGroupLinkUserData(SdrObject* pObj1);
    virtual ~ImpSdrObjGroupLinkUserData();

    virtual SdrObjUserData* Clone(SdrObject* pObj1) const;
    virtual void WriteData(SvStream& rOut);
    virtual void ReadData(SvStream& rIn);
    virtual void AfterRead();
};

//************************************************************
//   SdrObjGroup
//************************************************************

class SdrObjGroup : public SdrObject
{
    friend class                ImpSdrObjGroupLink;
    friend class                ImpSdrObjGroupLinkUserData;

protected:
    SfxItemSet*                 mpGroupItemSet;
    SdrObjList*                 pSub;    // Subliste (Kinder)
    long                        nDrehWink;
    long                        nShearWink;

    String                      aName;

    Point                       aRefPoint; // Referenzpunkt innerhalb der Objektgruppe
    FASTBOOL                    bRefPoint; // Ist ein RefPoint gesetzt?

private:
    ImpSdrObjGroupLinkUserData* GetLinkUserData() const;
    void ImpLinkAnmeldung();
    void ImpLinkAbmeldung();

public:
    TYPEINFO();
    SdrObjGroup();
    virtual ~SdrObjGroup();

    // Folgende 5 Methoden zur Verwendung von Verknuepfungen zu Gruppenobjekten
    // in fremden Dokumenten.
    // !!! Derzeit werden noch keine Ringreferenzen abgefangen !!!
    // GruppenLinks koennen durchaus selber auch gruppiert werden. Nach betreten
    // einer gelinkten Gruppe kann zwar noch selektiert, jedoch nichts mehr
    // veraendert werden (ReadOnly). Das Referenzgruppenobjekt im fremden
    // Dokument darf nicht gruppiert sein, muss sich also immer auf dem Root-
    // Level der Page befinden.
    // Transformationen auf den gesamten Gruppenlink sind zwar vorgesehen,
    // jedoch noch nicht implementiert.
    // Zur Verwendung von GruppenLinks muessen die Methoden
    //   virtual const SdrModel* SdrModel::LoadModel(const String& rFileName);
    //   virtual const SdrModel* SdrModel::DisposeLoadedModels();
    // ueberladen werden (siehe SvdModel.HXX), die ein neues Model alloziiert
    // und in den Speicher laed bzw. zuvor geladene Models verwirft.
    // Ansonsten muss die App I.d.R. nur SetGroupLink() rufen - der Rest geschieht
    // von selbst (SfxLinkManager). Die Methode LoadGroup() kann ausserdem
    // verwendet werden, um eine benannte Gruppe aus einem fremden Dokument zu
    // laden (ohne Verknuepfung).
//STRIP001  void SetGroupLink(const String& rFileName, const String& rObjName);
    void ReleaseGroupLink();
    FASTBOOL IsLinkedGroup() const { return pPlusData!=NULL && GetLinkUserData()!=NULL; }
//STRIP001  FASTBOOL ReloadLinkedGroup(FASTBOOL bForceLoad=FALSE);

    // pnPgNum, etc. ist zum schnelleren wiederauffinden gedacht
//STRIP001  FASTBOOL LoadGroup(const String& rFileName, const String& rObjName, USHORT* pnPgNum=NULL, FASTBOOL* pbMasterPg=NULL, ULONG* pnObjNum=NULL);

    virtual UINT16 GetObjIdentifier() const;
//STRIP001  virtual void TakeObjInfo(SdrObjTransformInfoRec& rInfo) const;
    virtual SdrLayerID GetLayer() const;
    virtual void NbcSetLayer(SdrLayerID nLayer);
    virtual void SetObjList(SdrObjList* pNewObjList);
    virtual void SetPage(SdrPage* pNewPage);
    virtual void SetModel(SdrModel* pNewModel);
//STRIP001  virtual FASTBOOL HasRefPoint() const;
//STRIP001  virtual Point GetRefPoint() const;
//STRIP001  virtual void SetRefPoint(const Point& rPnt);
    virtual SdrObjList* GetSubList() const;

    virtual const Rectangle& GetBoundRect() const;
    virtual const Rectangle& GetSnapRect() const;
    virtual FASTBOOL Paint(ExtOutputDevice& rOut, const SdrPaintInfoRec& rInfoRec) const;
//STRIP001  virtual SdrObject* CheckHit(const Point& rPnt, USHORT nTol, const SetOfByte* pVisiLayer) const;
    virtual void operator=(const SdrObject& rObj);

//STRIP001  virtual void TakeObjNameSingul(String& rName) const;
//STRIP001  virtual void TakeObjNamePlural(String& rName) const;

//STRIP001  virtual FASTBOOL HasSetName() const;

    virtual void SetName(const String& rStr);
    virtual String GetName() const;

    virtual void RecalcSnapRect();
    virtual void TakeXorPoly(XPolyPolygon& rPoly, FASTBOOL bDetail) const;
//STRIP001  virtual void TakeContour(XPolyPolygon& rXPoly, SdrContourType eType) const;

//STRIP001  virtual FASTBOOL BegDrag(SdrDragStat& rDrag)  const;
//STRIP001  virtual FASTBOOL BegCreate(SdrDragStat& rStat);

    virtual long GetRotateAngle() const;
    virtual long GetShearAngle(FASTBOOL bVertical=FALSE) const;

    virtual void Move(const Size& rSiz);
    virtual void Resize(const Point& rRef, const Fraction& xFact, const Fraction& yFact);
//STRIP001  virtual void Rotate(const Point& rRef, long nWink, double sn, double cs);
//STRIP001  virtual void Mirror(const Point& rRef1, const Point& rRef2);
//STRIP001  virtual void Shear(const Point& rRef, long nWink, double tn, FASTBOOL bVShear);
    virtual void SetAnchorPos(const Point& rPnt);
    virtual void SetRelativePos(const Point& rPnt);
    virtual void SetSnapRect(const Rectangle& rRect);
//STRIP001  virtual void SetLogicRect(const Rectangle& rRect);

    virtual void NbcMove(const Size& rSiz);
    virtual void NbcResize(const Point& rRef, const Fraction& xFact, const Fraction& yFact);
//STRIP001  virtual void NbcRotate(const Point& rRef, long nWink, double sn, double cs);
//STRIP001  virtual void NbcMirror(const Point& rRef1, const Point& rRef2);
//STRIP001  virtual void NbcShear(const Point& rRef, long nWink, double tn, FASTBOOL bVShear);
    virtual void NbcSetAnchorPos(const Point& rPnt);
//STRIP001  virtual void NbcSetRelativePos(const Point& rPnt);
    virtual void NbcSetSnapRect(const Rectangle& rRect);
    virtual void NbcSetLogicRect(const Rectangle& rRect);

    // ItemSet access
    virtual const SfxItemSet& GetItemSet() const;
    virtual SfxItemSet* CreateNewItemSet(SfxItemPool& rPool);
    virtual void ItemSetChanged(const SfxItemSet& rSet);

    // private support routines for ItemSet access. NULL pointer means clear item.
    virtual void ItemChange(const sal_uInt16 nWhich, const SfxPoolItem* pNewItem = 0);

    // pre- and postprocessing for objects for saving
    virtual void PreSave();
    virtual void PostSave();

    virtual void NbcSetStyleSheet(SfxStyleSheet* pNewStyleSheet, FASTBOOL bDontRemoveHardAttr);
    virtual void SetStyleSheet(SfxStyleSheet* pNewStyleSheet, FASTBOOL bDontRemoveHardAttr);
    virtual SfxStyleSheet* GetStyleSheet() const;

//STRIP001  virtual void NbcReformatText();
    virtual void ReformatText();
//STRIP001  virtual void BurnInStyleSheetAttributes( BOOL bPseudoSheetsOnly=FALSE );

    virtual void RestartAnimation(SdrPageView* pPageView) const;

//STRIP001  virtual SdrObject* DoConvertToPolyObj(BOOL bBezier) const;

    virtual void WriteData(SvStream& rOut) const;
    virtual void ReadData(const SdrObjIOHeader& rHead, SvStream& rIn);
    virtual void AfterRead();

    // ItemPool fuer dieses Objekt wechseln
//STRIP001  virtual void MigrateItemPool(SfxItemPool* pSrcPool, SfxItemPool* pDestPool, SdrModel* pNewModel = NULL );
};

}//end of namespace binfilter
#endif //_SVDOGRP_HXX

