/*************************************************************************
 *
 *  $RCSfile: svdundo.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:48 $
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

#ifndef _SVDUNDO_HXX
#define _SVDUNDO_HXX

#ifndef _SOLAR_HRC
#include <svtools/solar.hrc>
#endif

#ifndef _UNDO_HXX //autogen
#include <svtools/undo.hxx>
#endif

#ifndef _CONTNR_HXX //autogen
#include <tools/contnr.hxx>
#endif

#ifndef _GEN_HXX //autogen
#include <tools/gen.hxx>
#endif

#ifndef _SVDTYPES_HXX
#include <bf_svx/svdtypes.hxx> // fuer enum RepeatFuncts
#endif
#include <tools/debug.hxx>
//************************************************************
//   Vorausdeklarationen
//************************************************************

class SfxItemSet;
class SfxStyleSheet;
class SdrView;
class SdrPageView;
class SdrModel;
class SdrObject;
class SdrPage;
class SdrObjList;
class SdrLayer;
class SdrLayerAdmin;
class SdrObjGeoData;
class OutlinerParaObject;
class SdrMasterPageDescriptor;

//************************************************************
//   SdrUndoAction
//
// Abstrakte Basisklasse fuer alle UndoActions der DrawingEngine
//
//************************************************************

class SdrUndoAction : public SfxUndoAction
{
protected:
    SdrModel&                   rMod;

protected:
    SdrUndoAction(SdrModel& rNewMod)
    :   rMod(rNewMod)
    {}

public:
//STRIP001  TYPEINFO();
//STRIP001  virtual BOOL CanRepeat(SfxRepeatTarget& rView) const;
//STRIP001  virtual void Repeat(SfxRepeatTarget& rView);

//STRIP001  virtual String GetRepeatComment(SfxRepeatTarget& rView) const;
//STRIP001  virtual String GetSdrRepeatComment(SdrView& rView) const;

//STRIP001  virtual FASTBOOL CanSdrRepeat(SdrView& rView) const;
//STRIP001  virtual void SdrRepeat(SdrView& rView);
};

//************************************************************
//   SdrUndoGroup
//
// Zusammenfassung beliebig vieler einzelner UndoActions zu einer einzigen
// UndoAction. Beim Undo() werden die Einzelactions rueckwaets aufgerufen
// (die zuletzt angehaengte zuerst...), beim Redo() dagegen entspricht die
// Aufrufreihenfolge der Einfuegereihenfolge.
//
//************************************************************

class SdrUndoGroup : public SdrUndoAction
{
protected:
    Container                   aBuf;

    // Beschreibung der Action, nicht expandiert (beinhaltet %O)
    String                      aComment;
    String                      aObjDescription;

    SdrRepeatFunc               eFunction;

public:
    SdrUndoGroup(SdrModel& rNewMod);
    SdrUndoGroup(SdrModel& rNewMod,const String& rStr);
    virtual ~SdrUndoGroup();

    void Clear();
    ULONG GetActionCount() const { return aBuf.Count(); }
    SdrUndoAction* GetAction(ULONG nNum) const { return (SdrUndoAction*)(aBuf.GetObject(nNum)); }
    void AddAction(SdrUndoAction* pAct);

    void SetComment(const String& rStr) { aComment=rStr; }
//STRIP001  void SetObjDescription(const String& rStr) { aObjDescription=rStr; }
//STRIP001  virtual String GetComment() const;
//STRIP001  virtual String GetSdrRepeatComment(SdrView& rView) const;

//STRIP001  virtual void Undo();
//STRIP001  virtual void Redo();

//STRIP001  virtual FASTBOOL CanSdrRepeat(SdrView& rView) const;
//STRIP001  virtual void SdrRepeat(SdrView& rView);
//STRIP001  void SetRepeatFunction(SdrRepeatFunc eFunc) { eFunction=eFunc; }
//STRIP001  SdrRepeatFunc GetRepeatFunction() const { return eFunction; }
};

//************************************************************
//   SdrUndoObj
//
// Abstrakte Basisklasse fuer alle UndoActions die mit Objekten zu tun haben.
//
//************************************************************

class SdrUndoObj : public SdrUndoAction
{
protected:
    SdrObject*                  pObj;

protected:
    SdrUndoObj(SdrObject& rNewObj);
//STRIP001
//STRIP001  void ImpTakeDescriptionStr(USHORT nStrCacheID, String& rStr, FASTBOOL bRepeat=FALSE) const;
//STRIP001
//STRIP001  // #94278# new method for evtl. PageChange at UNDO/REDO
//STRIP001  void ImpShowPageOfThisObject();
};

//************************************************************
//   SdrUndoAttrObj
//
// Aenderung der Objektattribute.
// Action direkt vor dem Setzen der neuen Attribute konstruieren.
// Auch fuer StyleSheets
//
//************************************************************

//STRIP001 class SdrUndoAttrObj : public SdrUndoObj
//STRIP001 {
//STRIP001 protected:
//STRIP001  SfxItemSet*                 pUndoSet;
//STRIP001  SfxItemSet*                 pRedoSet;
//STRIP001  SfxItemSet*                 pRepeatSet;
//STRIP001
//STRIP001  // oder besser den StyleSheetNamen merken?
//STRIP001  SfxStyleSheet*              pUndoStyleSheet;
//STRIP001  SfxStyleSheet*              pRedoStyleSheet;
//STRIP001  SfxStyleSheet*              pRepeatStyleSheet;
//STRIP001  FASTBOOL                    bStyleSheet;
//STRIP001  FASTBOOL                    bHaveToTakeRedoSet;
//STRIP001
//STRIP001  // Bei Zuweisung von TextItems auf ein Zeichenobjekt mit Text:
//STRIP001  OutlinerParaObject*         pTextUndo;
//STRIP001  // #i8508#
//STRIP001  // The text rescue mechanism needs also to be implemented for redo actions.
//STRIP001  OutlinerParaObject*         pTextRedo;
//STRIP001
//STRIP001  // Wenn sich um ein Gruppenobjekt handelt:
//STRIP001  SdrUndoGroup*               pUndoGroup;
//STRIP001
//STRIP001 public:
//STRIP001  SdrUndoAttrObj(SdrObject& rNewObj, FASTBOOL bStyleSheet1=FALSE, FASTBOOL bSaveText=FALSE);
//STRIP001  virtual ~SdrUndoAttrObj();
//STRIP001  void SetRepeatAttr(const SfxItemSet& rSet);
//STRIP001  virtual void Undo();
//STRIP001  virtual void Redo();
//STRIP001
//STRIP001  virtual String GetComment() const;
//STRIP001  virtual String GetSdrRepeatComment(SdrView& rView) const;
//STRIP001
//STRIP001  virtual void SdrRepeat(SdrView& rView);
//STRIP001  virtual FASTBOOL CanSdrRepeat(SdrView& rView) const;
//STRIP001 };

//************************************************************
//   SdrUndoMoveObj
//
// Blosses verschieben eines Objektes.
// Action direkt vor dem Verschieben konstruieren.
//
//************************************************************

class SdrUndoMoveObj : public SdrUndoObj
{
protected:
    Size                        aDistance;     // Entfernung, um die verschoben wird

public:
//STRIP001  SdrUndoMoveObj(SdrObject& rNewObj): SdrUndoObj(rNewObj) {}
    SdrUndoMoveObj(SdrObject& rNewObj, const Size& rDist): SdrUndoObj(rNewObj),aDistance(rDist) {}
//STRIP001
//STRIP001  void SetDistance(const Size& rDist) { aDistance=rDist; }
//STRIP001  const Size& GetDistance() const { return aDistance; }
//STRIP001
//STRIP001  virtual void Undo();
//STRIP001  virtual void Redo();
//STRIP001
//STRIP001  virtual String GetComment() const;
//STRIP001  virtual String GetSdrRepeatComment(SdrView& rView) const;
//STRIP001
//STRIP001  virtual void SdrRepeat(SdrView& rView);
//STRIP001  virtual FASTBOOL CanSdrRepeat(SdrView& rView) const;
};

//************************************************************
//   SdrUndoGeoObj
//
// Aenderung der Geometrie eines Objektes.
// Action direkt vor der geometrischen Transformation konstruieren.
//
//************************************************************

class SdrUndoGeoObj : public SdrUndoObj
{
protected:
    SdrObjGeoData*              pUndoGeo;
    SdrObjGeoData*              pRedoGeo;
    // Wenn sich um ein Gruppenobjekt handelt:
    SdrUndoGroup*               pUndoGroup;

public:
    SdrUndoGeoObj(SdrObject& rNewObj);
    virtual ~SdrUndoGeoObj();

//STRIP001  virtual void Undo();
//STRIP001  virtual void Redo();

//STRIP001  virtual String GetComment() const;
};

//************************************************************
//   SdrUndoObjList
//
// Manipulationen an einer ObjList: Neues Obj, DeleteObj, SetObjZLevel, Grouping, ...
// Abstrakte Basisklasse.
//
//************************************************************

class SdrUndoObjList : public SdrUndoObj {
    FASTBOOL                    bOwner;

protected:
    SdrObjList*                 pObjList;
    SdrView*                    pView;      // um bei ObjDel, Undo die
    SdrPageView*                pPageView;  // Selektion widerherstellen zu koennen
    UINT32                      nOrdNum;
    // Bei einem Undo/Redo findet moeglicherweise Uebereignung des Objektes
    // statt. Im Dtor wird das Obj deleted, wenn bOwner==TRUE

protected:
    SdrUndoObjList(SdrObject& rNewObj, FASTBOOL bOrdNumDirect=FALSE);
    virtual ~SdrUndoObjList();

    void SetView(SdrView* pView1, SdrPageView* pPageView1) { pView=pView1; pPageView=pPageView1; }
    BOOL IsOwner() { return bOwner; }
//STRIP001  void SetOwner(BOOL bNew);
};

//************************************************************
//   SdrUndoRemoveObj
//
// Entfernen Objekts aus einer Objektliste. Innerhalb einer UndoGroup
// mit korrospondierenden Inserts zu verwenden.
// Action vor dem entfernen aus der ObjList konstruieren.
//
//************************************************************

class SdrUndoRemoveObj : public SdrUndoObjList
{
public:
    SdrUndoRemoveObj(SdrObject& rNewObj, FASTBOOL bOrdNumDirect=FALSE)
    : SdrUndoObjList(rNewObj,bOrdNumDirect) {}

//STRIP001  virtual void Undo();
//STRIP001  virtual void Redo();
};

//************************************************************
//   SdrUndoInsertObj
//
// Einfuegen Objekts in eine Objektliste. Innerhalb einer UndoGroup
// mit korrospondierenden Removes zu verwenden.
// Action vor dem entfernen aus der ObjList konstruieren.
//
//************************************************************

class SdrUndoInsertObj : public SdrUndoObjList
{
public:
    SdrUndoInsertObj(SdrObject& rNewObj, FASTBOOL bOrdNumDirect=FALSE)
    :   SdrUndoObjList(rNewObj,bOrdNumDirect) {}
//STRIP001
//STRIP001  virtual void Undo();
//STRIP001  virtual void Redo();
};

//************************************************************
//   SdrUndoDelObj
//
// Loeschen eines Objekts.
// Action vor dem entfernen aus der ObjList konstruieren.
//
//************************************************************

class SdrUndoDelObj : public SdrUndoRemoveObj
{
public:
    SdrUndoDelObj(SdrObject& rNewObj, FASTBOOL bOrdNumDirect=FALSE)
    :   SdrUndoRemoveObj(rNewObj,bOrdNumDirect) {DBG_ASSERT(0, "STRIP")}//STRIP001      :   SdrUndoRemoveObj(rNewObj,bOrdNumDirect) { SetOwner(TRUE); }

//STRIP001  virtual void Undo();
//STRIP001  virtual void Redo();
//STRIP001
//STRIP001  virtual String GetComment() const;
//STRIP001  virtual String GetSdrRepeatComment(SdrView& rView) const;
//STRIP001
//STRIP001  virtual void SdrRepeat(SdrView& rView);
//STRIP001  virtual FASTBOOL CanSdrRepeat(SdrView& rView) const;
};

//************************************************************
//   SdrUndoNewObj
//
// Einfuegen eines neuen Objektes.
// Action nach dem einfuegen in die ObjList konstruieren.
//
//************************************************************

//STRIP001 class SdrUndoNewObj : public SdrUndoInsertObj
//STRIP001 {
//STRIP001 public:
//STRIP001  SdrUndoNewObj(SdrObject& rNewObj, FASTBOOL bOrdNumDirect=FALSE)
//STRIP001  :   SdrUndoInsertObj(rNewObj,bOrdNumDirect) {}
//STRIP001
//STRIP001  virtual void Undo();
//STRIP001  virtual void Redo();
//STRIP001
//STRIP001  virtual String GetComment() const;
//STRIP001 };

//************************************************************
//   SdrUndoReplaceObj
//
// Austausch eines Objektes.
// Action vor dem Replace an der ObjList konstruieren.
//
//************************************************************

//STRIP001 class SdrUndoReplaceObj : public SdrUndoObj
//STRIP001 {
//STRIP001  FASTBOOL                    bOldOwner;
//STRIP001  FASTBOOL                    bNewOwner;
//STRIP001
//STRIP001 protected:
//STRIP001  SdrObjList*                 pObjList;
//STRIP001  UINT32                      nOrdNum;
//STRIP001  SdrObject*                  pNewObj;
//STRIP001
//STRIP001 public:
//STRIP001  SdrUndoReplaceObj(SdrObject& rOldObj1, SdrObject& rNewObj1, FASTBOOL bOrdNumDirect=FALSE);
//STRIP001  virtual ~SdrUndoReplaceObj();
//STRIP001
//STRIP001  virtual void Undo();
//STRIP001  virtual void Redo();
//STRIP001
//STRIP001  BOOL IsNewOwner() { return bNewOwner; }
//STRIP001  void SetNewOwner(BOOL bNew);
//STRIP001
//STRIP001  BOOL IsOldOwner() { return bOldOwner; }
//STRIP001  void SetOldOwner(BOOL bNew);
//STRIP001 };

//************************************************************
//   SdrUndoCopyObj
//
// Kopieren eines Objekts
// Action nach dem einfuegen in die ObjList konstruieren.
//
//************************************************************

//STRIP001 class SdrUndoCopyObj : public SdrUndoNewObj
//STRIP001 {
//STRIP001 public:
//STRIP001  SdrUndoCopyObj(SdrObject& rNewObj, FASTBOOL bOrdNumDirect=FALSE)
//STRIP001  :   SdrUndoNewObj(rNewObj,bOrdNumDirect) {}
//STRIP001
//STRIP001  virtual String GetComment() const;
//STRIP001 };

//************************************************************
//   SdrUndoObjOrdNum
//************************************************************

//STRIP001 class SdrUndoObjOrdNum : public SdrUndoObj
//STRIP001 {
//STRIP001 protected:
//STRIP001  UINT32                      nOldOrdNum;
//STRIP001  UINT32                      nNewOrdNum;
//STRIP001
//STRIP001 public:
//STRIP001  SdrUndoObjOrdNum(SdrObject& rNewObj, UINT32 nOldOrdNum1, UINT32 nNewOrdNum1);
//STRIP001
//STRIP001  virtual void Undo();
//STRIP001  virtual void Redo();
//STRIP001
//STRIP001  virtual String   GetComment() const;
//STRIP001 };

//////////////////////////////////////////////////////////////////////////////
// #i11702#

class SdrUndoObjectLayerChange : public SdrUndoObj
{
protected:
    SdrLayerID                  maOldLayer;
    SdrLayerID                  maNewLayer;

public:
    SdrUndoObjectLayerChange(SdrObject& rObj, SdrLayerID aOldLayer, SdrLayerID aNewLayer);

    virtual void Undo();
    virtual void Redo();
};

//************************************************************
//   SdrUndoObjSetText
//************************************************************

//STRIP001 class SdrUndoObjSetText : public SdrUndoObj
//STRIP001 {
//STRIP001 protected:
//STRIP001  OutlinerParaObject*         pOldText;
//STRIP001  OutlinerParaObject*         pNewText;
//STRIP001  FASTBOOL                    bNewTextAvailable;
//STRIP001  BOOL                        bEmptyPresObj;
//STRIP001
//STRIP001 public:
//STRIP001  SdrUndoObjSetText(SdrObject& rNewObj);
//STRIP001  virtual ~SdrUndoObjSetText();
//STRIP001
//STRIP001  FASTBOOL IsDifferent() const { return pOldText!=pNewText; }
//STRIP001  void AfterSetText();
//STRIP001
//STRIP001  virtual void Undo();
//STRIP001  virtual void Redo();
//STRIP001
//STRIP001  virtual String GetComment() const;
//STRIP001  virtual String GetSdrRepeatComment(SdrView& rView) const;
//STRIP001
//STRIP001  virtual void SdrRepeat(SdrView& rView);
//STRIP001  virtual FASTBOOL CanSdrRepeat(SdrView& rView) const;
//STRIP001 };

////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  @@     @@@@  @@  @@ @@@@@ @@@@@
//  @@    @@  @@ @@  @@ @@    @@  @@
//  @@    @@  @@ @@  @@ @@    @@  @@
//  @@    @@@@@@  @@@@  @@@@  @@@@@
//  @@    @@  @@   @@   @@    @@  @@
//  @@    @@  @@   @@   @@    @@  @@
//  @@@@@ @@  @@   @@   @@@@@ @@  @@
//
////////////////////////////////////////////////////////////////////////////////////////////////////

//************************************************************
//   SdrUndoLayer
//
// Abstrakte Basisklasse fuer alle UndoActions die mit SdrLayer zu tun haben.
//
//************************************************************

//STRIP001 class SdrUndoLayer : public SdrUndoAction
//STRIP001 {
//STRIP001 protected:
//STRIP001  SdrLayer*                   pLayer;
//STRIP001  SdrLayerAdmin*              pLayerAdmin;
//STRIP001  USHORT                      nNum;
//STRIP001  FASTBOOL                    bItsMine;
//STRIP001
//STRIP001 protected:
//STRIP001  SdrUndoLayer(USHORT nLayerNum, SdrLayerAdmin& rNewLayerAdmin, SdrModel& rNewModel);
//STRIP001  virtual ~SdrUndoLayer();
//STRIP001 };

//************************************************************
//   SdrUndoNewLayer
//
// Einfuegen eines neuen Layer. Action nach dem Einfuegen konstruieren.
//
//************************************************************

//STRIP001 class SdrUndoNewLayer : public SdrUndoLayer
//STRIP001 {
//STRIP001 public:
//STRIP001  SdrUndoNewLayer(USHORT nLayerNum, SdrLayerAdmin& rNewLayerAdmin, SdrModel& rNewModel)
//STRIP001  : SdrUndoLayer(nLayerNum,rNewLayerAdmin,rNewModel) {}
//STRIP001
//STRIP001  virtual void Undo();
//STRIP001  virtual void Redo();
//STRIP001
//STRIP001  virtual String GetComment() const;
//STRIP001 };

//************************************************************
//   SdrUndoDelLayer
//
// Loeschen eines Layer. Action vor dem Remove konstruieren
//
//************************************************************

//STRIP001 class SdrUndoDelLayer : public SdrUndoLayer
//STRIP001 {
//STRIP001 public:
//STRIP001  SdrUndoDelLayer(USHORT nLayerNum, SdrLayerAdmin& rNewLayerAdmin, SdrModel& rNewModel)
//STRIP001  : SdrUndoLayer(nLayerNum,rNewLayerAdmin,rNewModel) { bItsMine=TRUE; }
//STRIP001
//STRIP001  virtual void Undo();
//STRIP001  virtual void Redo();
//STRIP001
//STRIP001  virtual String GetComment() const;
//STRIP001 };

//************************************************************
//   SdrUndoMoveLayer
//
// Verschieben eines Layer. Action vor dem Verschieben konstruieren.
//
//************************************************************

//STRIP001 class SdrUndoMoveLayer : public SdrUndoLayer
//STRIP001 {
//STRIP001  USHORT                      nNeuPos;
//STRIP001
//STRIP001 public:
//STRIP001  SdrUndoMoveLayer(USHORT nLayerNum, SdrLayerAdmin& rNewLayerAdmin, SdrModel& rNewModel, USHORT nNeuPos1)
//STRIP001  :   SdrUndoLayer(nLayerNum,rNewLayerAdmin,rNewModel), nNeuPos(nNeuPos1) {}
//STRIP001
//STRIP001  virtual void Undo();
//STRIP001  virtual void Redo();
//STRIP001
//STRIP001  virtual String GetComment() const;
//STRIP001 };

////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  @@@@@   @@@@   @@@@  @@@@@  @@@@
//  @@  @@ @@  @@ @@  @@ @@    @@  @@
//  @@  @@ @@  @@ @@     @@    @@
//  @@@@@  @@@@@@ @@ @@@ @@@@   @@@@
//  @@     @@  @@ @@  @@ @@        @@
//  @@     @@  @@ @@  @@ @@    @@  @@
//  @@     @@  @@  @@@@@ @@@@@  @@@@
//
////////////////////////////////////////////////////////////////////////////////////////////////////

//************************************************************
//   SdrUndoPage
//
// Abstrakte Basisklasse fuer alle UndoActions die mit SdrPages zu tun haben.
//
//************************************************************

class SdrUndoPage : public SdrUndoAction
{
protected:
    SdrPage*                    pPage;

protected:
//STRIP001  void ImpInsertPage(USHORT nNum);
//STRIP001  void ImpRemovePage(USHORT nNum);
//STRIP001  void ImpMovePage(USHORT nOldNum, USHORT nNewNum);
//STRIP001
protected:
    SdrUndoPage(SdrPage& rNewPg);
//STRIP001
//STRIP001  void ImpTakeDescriptionStr(USHORT nStrCacheID, String& rStr, USHORT n=0, FASTBOOL bRepeat=FALSE) const;
};

//************************************************************
//   SdrUndoPageList
//
// Manipulationen an einer PageList: Neue Page, DeletePage, MovePage(ChangePageNum)
// Abstrakte Basisklasse.
//
//************************************************************

class SdrUndoPageList : public SdrUndoPage
{
protected:
    USHORT                      nPageNum;

    // Bei einem Undo/Redo findet moeglicherweise Uebereignung der Page
    // statt. Im Dtor wird die Page deleted, wenn bItsMine==TRUE
    FASTBOOL                    bItsMine;

protected:
    SdrUndoPageList(SdrPage& rNewPg);
    virtual ~SdrUndoPageList();
};

//************************************************************
//   SdrUndoDelPage
//
// Loeschen einer Page.
// Action vor dem entfernen aus der List konstruieren.
//
//************************************************************

//STRIP001 class SdrUndoDelPage : public SdrUndoPageList
//STRIP001 {
//STRIP001  // Beim loeschen einer MasterPage merke ich mir in dieser UndoGroup
//STRIP001  // alle Beziehungen der Zeichenseiten zu der geloeschten MasterPage
//STRIP001  SdrUndoGroup*               pUndoGroup;
//STRIP001
//STRIP001 public:
//STRIP001  SdrUndoDelPage(SdrPage& rNewPg);
//STRIP001  virtual ~SdrUndoDelPage();
//STRIP001
//STRIP001  virtual void Undo();
//STRIP001  virtual void Redo();
//STRIP001
//STRIP001  virtual String GetComment() const;
//STRIP001  virtual String GetSdrRepeatComment(SdrView& rView) const;
//STRIP001
//STRIP001  virtual void SdrRepeat(SdrView& rView);
//STRIP001  virtual FASTBOOL CanSdrRepeat(SdrView& rView) const;
//STRIP001 };

//************************************************************
//   SdrUndoNewPage
//
// Einfuegen einer neuen Page.
// Action nach dem einfuegen in die Liste konstruieren.
//
//************************************************************

class SdrUndoNewPage : public SdrUndoPageList
{
public:
    SdrUndoNewPage(SdrPage& rNewPg): SdrUndoPageList(rNewPg) {}
//STRIP001
//STRIP001  virtual void Undo();
//STRIP001  virtual void Redo();
//STRIP001
//STRIP001  virtual String GetComment() const;
};

//************************************************************
//   SdrUndoCopyPage
//
// Kopieren einer Page
// Action nach dem einfuegen in die Liste konstruieren.
//
//************************************************************

//STRIP001 class SdrUndoCopyPage : public SdrUndoNewPage
//STRIP001 {
//STRIP001 public:
//STRIP001  SdrUndoCopyPage(SdrPage& rNewPg): SdrUndoNewPage(rNewPg) {}
//STRIP001
//STRIP001  virtual String GetComment() const;
//STRIP001  virtual String GetSdrRepeatComment(SdrView& rView) const;
//STRIP001
//STRIP001  virtual void SdrRepeat(SdrView& rView);
//STRIP001  virtual FASTBOOL CanSdrRepeat(SdrView& rView) const;
//STRIP001 };

//************************************************************
//   SdrUndoSetPageNum
//
// Verschieben der Page innerhalb der Liste
// Action vor dem Verschieben der Page konstruieren.
//
//************************************************************

//STRIP001 class SdrUndoSetPageNum : public SdrUndoPage
//STRIP001 {
//STRIP001 protected:
//STRIP001  USHORT                      nOldPageNum;
//STRIP001  USHORT                      nNewPageNum;
//STRIP001
//STRIP001 public:
//STRIP001  SdrUndoSetPageNum(SdrPage& rNewPg, USHORT nOldPageNum1, USHORT nNewPageNum1)
//STRIP001  :   SdrUndoPage(rNewPg),nOldPageNum(nOldPageNum1),nNewPageNum(nNewPageNum1) {}
//STRIP001
//STRIP001  virtual void Undo();
//STRIP001  virtual void Redo();
//STRIP001
//STRIP001  virtual String GetComment() const;
//STRIP001 };

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

//************************************************************
//   SdrUndoPageMasterPage
//
// Abstrakte Basisklasse fuer alle UndoActions die mit
// MasterPage-Beziehungen zu tun haben.
//
//************************************************************

//STRIP001 class SdrUndoPageMasterPage : public SdrUndoPage
//STRIP001 {
//STRIP001 protected:
//STRIP001  SdrMasterPageDescriptor*    pMasterDescriptor;
//STRIP001  SdrMasterPageDescriptor*    pNewMasterDescriptor;
//STRIP001  USHORT                      nMasterNum;
//STRIP001  USHORT                      nNewMasterNum;
//STRIP001
//STRIP001 protected:
//STRIP001  // Achtung! nMasterDescriptorNum ist nicht die Seitennummer
//STRIP001  // der MasterPage sondern die Position des MasterPage-Verweises
//STRIP001  // an der Page // (eine Page kann auf beliebig viele MasterPages
//STRIP001  // verweisen)
//STRIP001  SdrUndoPageMasterPage(SdrPage& rNewPg, USHORT nMasterDescriptorNum);
//STRIP001
//STRIP001 public:
//STRIP001  virtual ~SdrUndoPageMasterPage();
//STRIP001 };

//************************************************************
//   SdrUndoPageInsertMasterPage
//
// Setzen einer MasterPage an einer Zeichenseite.
// Action nach dem Einfuegen des MasterPageDescriptors erzeugen.
//
//************************************************************

//STRIP001 class SdrUndoPageInsertMasterPage : public SdrUndoPageMasterPage
//STRIP001 {
//STRIP001 public:
//STRIP001  SdrUndoPageInsertMasterPage(SdrPage& rNewPg, USHORT nMasterDescriptorNum)
//STRIP001  :   SdrUndoPageMasterPage(rNewPg,nMasterDescriptorNum) {}
//STRIP001
//STRIP001  virtual void Undo();
//STRIP001  virtual void Redo();
//STRIP001
//STRIP001  virtual String GetComment() const;
//STRIP001 };

//************************************************************
//   SdrUndoPageRemoveMasterPage
//
// Entfernen einer MasterPage von einer Zeichenseite.
// Action vor dem Entfernen des MasterPageDescriptors erzeugen.
//
//************************************************************

//STRIP001 class SdrUndoPageRemoveMasterPage : public SdrUndoPageMasterPage
//STRIP001 {
//STRIP001 public:
//STRIP001  SdrUndoPageRemoveMasterPage(SdrPage& rNewPg, USHORT nMasterDescriptorNum)
//STRIP001  :   SdrUndoPageMasterPage(rNewPg,nMasterDescriptorNum) {}
//STRIP001
//STRIP001  virtual void Undo();
//STRIP001  virtual void Redo();
//STRIP001
//STRIP001  virtual String GetComment() const;
//STRIP001 };

//************************************************************
//   SdrUndoPageMoveMasterPage
//
// Verschieben einer MasterPage an einer Zeichenseite (Aendern
// der Reihenfolge der MasterPageDescriptorList).
// Action vor dem Umsortieren des MasterPageDescriptors erzeugen.
//
//************************************************************

//STRIP001 class SdrUndoPageMoveMasterPage : public SdrUndoPageMasterPage
//STRIP001 {
//STRIP001 public:
//STRIP001  SdrUndoPageMoveMasterPage(SdrPage& rNewPg, USHORT nMasterDescriptorNum, USHORT nNewPos)
//STRIP001  :   SdrUndoPageMasterPage(rNewPg,nMasterDescriptorNum) { nNewMasterNum=nNewPos; }
//STRIP001
//STRIP001  virtual void Undo();
//STRIP001  virtual void Redo();
//STRIP001
//STRIP001  virtual String GetComment() const;
//STRIP001 };

//************************************************************
//   SdrUndoPageChangeMasterPage
//
// Aenderung des MasterPageDescriptors (z.B. Aendern der VisibleLayer).
// Action vor der Aenderung am MasterPageDescriptor erzeugen.
//
//************************************************************

//STRIP001 class SdrUndoPageChangeMasterPage : public SdrUndoPageMasterPage
//STRIP001 {
//STRIP001 public:
//STRIP001  SdrUndoPageChangeMasterPage(SdrPage& rNewPg, USHORT nMasterDescriptorNum)
//STRIP001  :   SdrUndoPageMasterPage(rNewPg,nMasterDescriptorNum) {}
//STRIP001
//STRIP001  virtual void Undo();
//STRIP001  virtual void Redo();
//STRIP001
//STRIP001  virtual String GetComment() const;
//STRIP001 };

////////////////////////////////////////////////////////////////////////////////////////////////////

#endif //_SVDUNDO_HXX

