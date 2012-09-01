/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */

#ifndef _SVDSURO_HXX
#define _SVDSURO_HXX

#include <bf_svx/svdtypes.hxx>
class SvStream;
namespace binfilter {

////////////////////////////////////////////////////////////////////////////////////////////////////

class SdrPage;
class SdrModel;
class SdrObject;
class SdrObjList;

class SdrObjSurrogate {
protected:
    const SdrObject*  pRefObj;
    SdrObject*  pObj;
    const SdrObjList* pList;
    const SdrObjList* pRootList;
    const SdrPage*    pPage;
    const SdrModel*   pModel;
    SdrObjListKind eList;
    UINT32      nOrdNum;         // Ordnungsnummer des Obj in seiner Liste
    UINT32*     pGrpOrdNums;     // Ordnungsnummern der Gruppenobjekte auf dem Path zum Zielobj
    UINT16      nGrpLevel;
    UINT16      nPageNum;
#if _SOLAR__PRIVATE
private:
    void ImpClearVars();
    void ImpFindObj();
    void ImpRead(SvStream& rIn);
    void ImpWriteValue(SvStream& rOut, UINT32 nVal, unsigned nByteAnz) const;
    void ImpReadValue(SvStream& rIn, UINT32& rVal, unsigned nByteAnz) const;
#endif // __PRIVATE
public:
    // Konstruktoren zum Lesen
    // Lesen eines absoluten Surrogats.
    SdrObjSurrogate(const SdrModel& rMod, SvStream& rIn);
    // Lesen eines relativen Surrogats. Muss verwendet werden, wenn das
    // Surrogat unter Angabe eines Referenzobjektes geschrieben wurde.
    SdrObjSurrogate(const SdrObject& rRefObj1, SvStream& rIn);

    ~SdrObjSurrogate();

    // GetObject() funktioniert nur sicher, wenn das gesamte Model
    // eingestreamt ist.
    SdrObject* GetObject();

    friend SvStream& operator<<(SvStream& rOut, const SdrObjSurrogate& rSurro);
};

/*
Ein SdrObjSurrogat ist eine Ersatzdarstellung zur Realisierung einer
persistenten Verbindung zu einem Zeichenobjekt. Anwendungsfaelle (Beispiele):
  - Virtuelles Objekt und Symbolreferenzierung
  - LayoutObjekt
  - Texterweiterungsrahmen
  - Konnektoren
Beim Rausstreamen eines SdrObjSurrogate wird die Listenart und die
Ordnungsnummer des Objekts in dieser Liste geschrieben, sowie ggf.
Angaben ueber die Seitennummer und das Grouping-Level (zzgl. der
Ordnungszahlen der Objektgruppen).
Wichtig ist zu wissen, dass die Verbindungen beim Einlesen erst
nach vollstaendigem Einlesen des SdrModel wiederhergestellt werden
koennen. Aus diesem Grund gibt es nach dem Einlesen des Models ein
Post-Processing (Methode AfterRead() wird noch im Stream-Operator
des Models am Model, an allen Pages und allen Objekten gerufen),
in dem allen Objekten Gelegenheit gegeben wird, nun die ersehnten
SdrObject* zu erlangen.

Surrogate koennen nur auf Objekte zeigen, die Member einer dem
Model bekannten Listen sind (DrawPages,MasterPages)

Internes Datenformat im Stream
1 Byte: Bit0-Bit4=Listenkennung. Siehe SdrObjListKind in SdrPage.HXX
        Bit5     =TRUE bedeutet Objekt ist gruppiert (so.)
        Bit6-Bit7=Byteanzahl m der Ordnungsnummern
                  00=1Byte, 01=2Byte, 10=reserviert, 11=4Byte
wenn Listenkennung!=OBJLIST_UNKNOWN
  m Bytes: Ordnungsnummer des referenzierten Objekts
  wenn eine Page  angegeben ist (SdrIsPageKind(Listenkennung)=TRUE)
    2 Byte: USHORT : Seitennummer
  wenn Bit5=TRUE
    2 Byte: USHORT : Tiefe n der Objektschachtelung
    n*m Bytes      : Ordnungsnummern der jeweiligen Gruppenobjekte

Virtuelle Objekte und Symbolreferenzierungen benoetigen z.B. bei Ordnungszahlen
bis 255 (also z.B. die ersten 256 Symbole) 2 Bytes im Stream.
Bei Referenzierung eines Objektes das in einem Gruppenobjekt steckt kommen
mind. 3 Bytes hinzu. Im unguenstigsten Fall liegt dieses Objekt auf einer
anderen Seite (z.B. Texterweiterungsrahmen), was bedeutet, dass weitere 2 Bytes
fuer die Seitennummer benoetigt werden.
Ein absolutes Surrogat welches ein nichtgruppiertes Objekt auf einer Page
repraesentiert benoetigt demzufolge mind. 4 Bytes und maximal 7 Bytes.
Ein NULL-Surrogat schreibt stets nur 1 Byte in den Stream, naemlich eine 0.
*/

////////////////////////////////////////////////////////////////////////////////////////////////////

}//end of namespace binfilter
#endif //_SVDSURO_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
