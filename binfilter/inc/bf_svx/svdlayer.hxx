/*************************************************************************
 *
 *  $RCSfile: svdlayer.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:42 $
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

#ifndef _SVDLAYER_HXX
#define _SVDLAYER_HXX

#ifndef _STRING_HXX //autogen
#include <tools/string.hxx>
#endif

#ifndef _STREAM_HXX //autogen
#include <tools/stream.hxx>
#endif

#ifndef _SVDSOB_HXX //autogen
#include <bf_svx/svdsob.hxx>
#endif

#ifndef _SVDTYPES_HXX
#include <bf_svx/svdtypes.hxx> // fuer typedef SdrLayerID
#endif

class SdrModel;
class SdrLayerSet;

class SdrLayer {
friend class SdrLayerSet;
friend class SdrLayerAdmin;
protected:
    String     aName;
    SdrModel*  pModel; // zum Broadcasten
    UINT16     nType;  // 0=Userdefined,1=Standardlayer
    SdrLayerID nID;
protected:
    SdrLayer(SdrLayerID nNewID, const String& rNewName)       { nID=nNewID; aName=rNewName; nType=0; pModel=NULL; }
    void SetID(SdrLayerID nNewID)                             { nID=nNewID; }
public:
    SdrLayer(): pModel(NULL),nType(0),nID(0)                  {}
//STRIP001  FASTBOOL      operator==(const SdrLayer& rCmpLayer) const;
//STRIP001  FASTBOOL      operator!=(const SdrLayer& rCmpLayer) const { return !operator==(rCmpLayer); }
    void          SetName(const String& rNewName);
    const String& GetName() const                             { return aName; }
    SdrLayerID    GetID() const                               { return nID; }
    void          SetModel(SdrModel* pNewModel)               { pModel=pNewModel; }
    SdrModel*     GetModel() const                            { return pModel; }
    // Einem SdrLayer kann man sagen dass er ein (der) Standardlayer sein soll.
    // Es wird dann laenderspeziefisch der passende Name gesetzt. SetName()
    // setzt das Flag "StandardLayer" ggf. zurueck auf "Userdefined".
//STRIP001  void          SetStandardLayer(FASTBOOL bStd=TRUE);
    FASTBOOL      IsStandardLayer() const                     { return nType==1; }
    friend SvStream& operator>>(SvStream& rIn, SdrLayer& rLayer);
    friend SvStream& operator<<(SvStream& rOut, const SdrLayer& rLayer);
};

////////////////////////////////////////////////////////////////////////////////////////////////////

// Der Layerset merkt sich eine Menge von LayerID's.
// Wird die ID eines zum Set gehoerigen Layer geaendert, so gehoert
// dieser damit nichtmehr zum Set ...
// Beim Einblenden eines Layerset in einer View werden alle Member-
// Layer sichtbar und alle Excluded-Layer unsichtbat geschaltet.
// alle anderen Layer bleiben unberuehrt.
class SdrLayerSet {
friend class SdrLayerAdmin;
friend class SdrView;
protected:
    //SdrLayerAdmin& rAd; // Admin, um Layernamen herauszufinden, ...
    String    aName;
    SetOfByte aMember;
    SetOfByte aExclude;
    SdrModel* pModel; // zum Broadcasten
protected:
    // Broadcasting ueber's Model und setzen des Modified-Flags
//STRIP001  void            Broadcast() const;
public:
    SdrLayerSet(): pModel(NULL) {}
    SdrLayerSet(const String& rNewName): aName(rNewName), pModel(NULL) {}
//STRIP001  FASTBOOL        operator==(const SdrLayerSet& rCmpLayerSet) const;
//STRIP001  FASTBOOL        operator!=(const SdrLayerSet& rCmpLayerSet) const { return !operator==(rCmpLayerSet); }
//STRIP001  void            SetName(const String& rNewName)        { aName=rNewName; Broadcast(); }
//STRIP001  const String&   GetName() const                        { return aName; }
    void            SetModel(SdrModel* pNewModel)          { pModel=pNewModel; }
//STRIP001  SdrModel*       GetModel() const                       { return pModel; }
//STRIP001  FASTBOOL        IsMember(SdrLayerID nLayID) const      { return aMember.IsSet(nLayID); }
//STRIP001  void            AddMember(SdrLayerID nLayID)           { if (nLayID!=SDRLAYER_NOTFOUND) aMember.Set(nLayID); Broadcast(); }
//STRIP001  void            DelMember(SdrLayerID nLayID)           { aMember.Clear(nLayID); Broadcast(); }
//    void            AddAll()                               { aMember.SetAll(); }
//STRIP001  void            DelAll()                               { aMember.ClearAll(); Broadcast(); }
//STRIP001  USHORT          GetMemberCount() const                 { return aMember.GetSetCount(); }
//STRIP001  SdrLayerID      GetMemberID(USHORT i) const            { return aMember.GetSetBit(i); }
//STRIP001  FASTBOOL        IsExcluded(SdrLayerID nLayID) const    { return aExclude.IsSet(nLayID); }
//STRIP001  void            AddExcluded(SdrLayerID nLayID)         { if (nLayID!=SDRLAYER_NOTFOUND) aExclude.Set(nLayID); Broadcast(); }
//STRIP001  void            DelExcluded(SdrLayerID nLayID)         { aExclude.Clear(nLayID); Broadcast(); }
//    void            ExcludeAll()                           { aExclude.SetAll(); }
//STRIP001  void            UnExcludeAll()                         { aExclude.ClearAll(); Broadcast(); }
//STRIP001  USHORT          GetExcludedCount() const               { return aExclude.GetSetCount(); }
//STRIP001  SdrLayerID      GetExcludedID(USHORT i) const          { return aExclude.GetSetBit(i); }
    friend SvStream& operator>>(SvStream& rIn, SdrLayerSet& rSet);
    friend SvStream& operator<<(SvStream& rOut, const SdrLayerSet& rSet);
};

// Beim Aendern von Layerdaten muss man derzeit
// noch selbst das Modify-Flag am Model setzen.
#define SDRLAYER_MAXCOUNT 255
class SdrLayerAdmin {
friend class SdrView;
friend class SdrModel;
friend class SdrPage;
//friend class MyScr; // debug
protected:
    Container      aLayer;
    Container      aLSets;
    SdrLayerAdmin* pParent; // Der Admin der Seite kennt den Admin des Docs
    SdrModel*      pModel; // zum Broadcasten
    String         aControlLayerName;
protected:
    // Eine noch nicht verwendete LayerID raussuchen. Sind bereits alle
    // verbraucht, so gibt's 'ne 0. Wer sicher gehen will, muss vorher
    // GetLayerCount()<SDRLAYER_MAXCOUNT abfragen, denn sonst sind alle
    // vergeben.
    SdrLayerID           GetUniqueLayerID() const;
    // Broadcasting ueber's Model und setzen des Modified-Flags
    void                 Broadcast(FASTBOOL bLayerSet) const;
public:
    SdrLayerAdmin(SdrLayerAdmin* pNewParent=NULL);
    SdrLayerAdmin(const SdrLayerAdmin& rSrcLayerAdmin);
    ~SdrLayerAdmin();
//STRIP001  const SdrLayerAdmin& operator=(const SdrLayerAdmin& rSrcLayerAdmin);
//STRIP001  FASTBOOL             operator==(const SdrLayerAdmin& rCmpLayerAdmin) const;
//STRIP001  FASTBOOL             operator!=(const SdrLayerAdmin& rCmpLayerAdmin) const       { return !operator==(rCmpLayerAdmin); }
    SdrLayerAdmin*       GetParent() const                                           { return pParent; }
    void                 SetParent(SdrLayerAdmin* pNewParent)                        { pParent=pNewParent; }
    void                 SetModel(SdrModel* pNewModel);
    SdrModel*            GetModel() const                                            { return pModel; }
    void                 InsertLayer(SdrLayer* pLayer, USHORT nPos=0xFFFF)           { aLayer.Insert(pLayer,nPos); pLayer->SetModel(pModel); Broadcast(FALSE); }
    SdrLayer*            RemoveLayer(USHORT nPos);
    // Alle Layer loeschen
    void               ClearLayer();
    // Neuer Layer wird angelegt und eingefuegt
    SdrLayer*          NewLayer(const String& rName, USHORT nPos=0xFFFF);
    void               DeleteLayer(SdrLayer* pLayer)                                 { aLayer.Remove(pLayer); delete pLayer; Broadcast(FALSE); }
//STRIP001  void               MoveLayer(SdrLayer* pLayer, USHORT nNewPos=0xFFFF);
//STRIP001  SdrLayer*          MoveLayer(USHORT nPos, USHORT nNewPos);
    // Neuer Layer, Name wird aus der Resource geholt
//STRIP001  SdrLayer*          NewStandardLayer(USHORT nPos=0xFFFF);

    // Iterieren ueber alle Layer
    USHORT             GetLayerCount() const                                         { return USHORT(aLayer.Count()); }
    SdrLayer*          GetLayer(USHORT i)                                            { return (SdrLayer*)(aLayer.GetObject(i)); }
    const SdrLayer*    GetLayer(USHORT i) const                                      { return (SdrLayer*)(aLayer.GetObject(i)); }

//STRIP001  USHORT             GetLayerPos(SdrLayer* pLayer) const;

    SdrLayer*          GetLayer(const String& rName, FASTBOOL bInherited)            { return (SdrLayer*)(((const SdrLayerAdmin*)this)->GetLayer(rName,bInherited)); }
    const SdrLayer*    GetLayer(const String& rName, FASTBOOL bInherited) const;
          SdrLayerID   GetLayerID(const String& rName, FASTBOOL bInherited) const;
          SdrLayer*    GetLayerPerID(USHORT nID)                                     { return (SdrLayer*)(((const SdrLayerAdmin*)this)->GetLayerPerID(nID)); }
    const SdrLayer*    GetLayerPerID(USHORT nID) const;

    void               InsertLayerSet(SdrLayerSet* pSet, USHORT nPos=0xFFFF)         { aLSets.Insert(pSet,nPos); pSet->SetModel(pModel); Broadcast(TRUE); }
    // Alle LayerSets loeschen
    void               ClearLayerSets();
    // Neuer Layerset wird angelegt und eingefuegt
//STRIP001  SdrLayerSet*       NewLayerSet(const String& rName, USHORT nPos=0xFFFF);
//STRIP001  SdrLayerSet*       RemoveLayerSet(SdrLayerSet* pSet);
    void               DeleteLayerSet(SdrLayerSet* pSet)                             { aLSets.Remove(pSet); delete pSet; Broadcast(TRUE); }
//STRIP001  void               MoveLayerSet(SdrLayerSet* pSet, USHORT nNewPos=0xFFFF);
    // Iterieren ueber alle LayerSets
    USHORT             GetLayerSetCount() const                                      { return USHORT(aLSets.Count()); }
    SdrLayerSet*       GetLayerSet(USHORT i)                                         { return (SdrLayerSet*)(aLSets.GetObject(i)); }
    const SdrLayerSet* GetLayerSet(USHORT i) const                                   { return (SdrLayerSet*)(aLSets.GetObject(i)); }

//STRIP001  SdrLayerSet*       GetLayerSet(const String& rName, FASTBOOL bInherited)         { return (SdrLayerSet*)(((const SdrLayerAdmin*)this)->GetLayerSet(rName,bInherited)); }
//STRIP001  const SdrLayerSet* GetLayerSet(const String& rName, FASTBOOL bInherited) const;

    void               SetControlLayerName(const String& rNewName) { aControlLayerName=rNewName; }
    const String&      GetControlLayerName() const                 { return aControlLayerName; }
};

/*
Anmerkung zu den Layer - Gemischt symbolisch/ID-basierendes Interface
    Einen neuen Layer macht man sich mit:
      pLayerAdmin->NewLayer("Der neue Layer");
    Der Layer wird dann automatisch an das Ende der Liste angehaengt.
    Entsprechdes gilt fuer Layersets gleichermassen.
    Das Interface am SdrLayerSet basiert auf LayerID's. Die App muss sich
    dafuer am SdrLayerAdmin eine ID abholen:
        SdrLayerID nLayerID=pLayerAdmin->GetLayerID("Der neue Layer");
    Wird der Layer nicht gefunden, so liefert die Methode SDRLAYER_NOTFOUND
    zurueck. Die Methoden mit ID-Interface fangen diesen Wert jedoch i.d.R
    sinnvoll ab.
    Hat man nicht nur den Namen, sondern gar einen SdrLayer*, so kann man
    sich die ID natuerlich wesentlich schneller direkt vom Layer abholen.
bInherited:
    TRUE: Wird der Layer/LayerSet nicht gefunden, so wird im Parent-LayerAdmin
          nachgesehen, ob es dort einen entsprechende Definition gibt.
    FALSE: Es wird nur dieser LayerAdmin durchsucht.
    Jeder LayerAdmin einer Seite hat einen Parent-LayerAdmin, nämlich den des
    Model. Das Model selbst hat keinen Parent.
*/

#endif //_SVDLAYER_HXX

