/*************************************************************************
 *
 *  $RCSfile: svdsuro.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:28:59 $
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

#ifndef _SVDSURO_HXX
#define _SVDSURO_HXX

#ifndef _SVDTYPES_HXX
#include <bf_svx/svdtypes.hxx>
#endif
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
    void ImpMakeSurrogate();
    void ImpFindObj();
    void ImpRead(SvStream& rIn);
    void ImpWriteValue(SvStream& rOut, UINT32 nVal, unsigned nByteAnz) const;
    void ImpReadValue(SvStream& rIn, UINT32& rVal, unsigned nByteAnz) const;
#endif // __PRIVATE
public:
//    TYPEINFO();

    // Konstruktor zum Schreiben
    // pObj ist das referenzierte Objekt.
    // Wird ueber pRefObj ein Referenzobjekt angegeben, so muss dieses
    // auch beim spaeteren Einlesen wieder angegeben werden (fuer Verweis
    // von einem Zeichenobjekt auf ein anderes). Diese Verwendung ist platz-
    // und zeitsparender, wenn sich beide Objekte auf derselben Page oder
    // noch besser in der selben ObjList befinden.
    // (pRefObj hat einen Verweis auf pObj).
    SdrObjSurrogate(SdrObject* pObj1, const SdrObject* pRefObj1=NULL);

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

