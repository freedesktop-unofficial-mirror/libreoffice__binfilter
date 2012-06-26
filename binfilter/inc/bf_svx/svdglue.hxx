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

#ifndef _SVDGLUE_HXX
#define _SVDGLUE_HXX

#include <bf_svtools/bf_solar.h>

class Window;
class OutputDevice;
class SvStream;
namespace binfilter {
class SdrObject;
}//end of namespace binfilter
#include <tools/contnr.hxx>
#include <tools/gen.hxx>
namespace binfilter {
////////////////////////////////////////////////////////////////////////////////////////////////////

#define SDRESC_SMART  0x0000
#define SDRESC_LEFT   0x0001
#define SDRESC_RIGHT  0x0002
#define SDRESC_TOP    0x0004
#define SDRESC_BOTTOM 0x0008
#define SDRESC_LO    0x0010 /* ni */
#define SDRESC_LU    0x0020 /* ni */
#define SDRESC_RO    0x0040 /* ni */
#define SDRESC_RU    0x0080 /* ni */
#define SDRESC_HORZ  (SDRESC_LEFT|SDRESC_RIGHT)
#define SDRESC_VERT  (SDRESC_TOP|SDRESC_BOTTOM)
#define SDRESC_ALL   0x00FF

#define SDRHORZALIGN_CENTER   0x0000
#define SDRHORZALIGN_LEFT     0x0001
#define SDRHORZALIGN_RIGHT    0x0002
#define SDRHORZALIGN_DONTCARE 0x0010
#define SDRVERTALIGN_CENTER   0x0000
#define SDRVERTALIGN_TOP      0x0100
#define SDRVERTALIGN_BOTTOM   0x0200
#define SDRVERTALIGN_DONTCARE 0x1000

class SdrGluePoint {
    // Bezugspunkt ist SdrObject::GetSnapRect().Center()
    // bNoPercent=FALSE: Position ist -5000..5000 (1/100)% bzw. 0..10000 (je nach Align)
    // bNoPercent=TRUE : Position ist in log Einh, rel zum Bezugspunkt
    Point    aPos;
    USHORT   nEscDir;
    USHORT   nId;
    USHORT   nAlign;
    bool bNoPercent:1;
    bool bReallyAbsolute:1; // Temporaer zu setzen fuer Transformationen am Bezugsobjekt
public:
    SdrGluePoint(): nEscDir(SDRESC_SMART),nId(0),nAlign(0) { bNoPercent=FALSE; bReallyAbsolute=FALSE; }
    SdrGluePoint(const Point& rNewPos, bool bNewPercent=TRUE, USHORT nNewAlign=0): aPos(rNewPos),nEscDir(SDRESC_SMART),nId(0),nAlign(nNewAlign) { bNoPercent=!bNewPercent; bReallyAbsolute=FALSE; }
    bool operator==(const SdrGluePoint& rCmpGP) const   { return aPos==rCmpGP.aPos && nEscDir==rCmpGP.nEscDir && nId==rCmpGP.nId && nAlign==rCmpGP.nAlign && bNoPercent==rCmpGP.bNoPercent && bReallyAbsolute==rCmpGP.bReallyAbsolute; }
    bool operator!=(const SdrGluePoint& rCmpGP) const   { return !operator==(rCmpGP); }
    const Point& GetPos() const                             { return aPos; }
    void         SetPos(const Point& rNewPos)               { aPos=rNewPos; }
    USHORT       GetEscDir() const                          { return nEscDir; }
    void         SetEscDir(USHORT nNewEsc)                  { nEscDir=nNewEsc; }
    /*bool   IsEscapeSmart() const                      { return nEscDir==SDRESC_SMART; }
    void         SetEscapeSmart()                           { nEscDir=SDRESC_SMART; }
    bool     IsEscapeLeft() const                       { return (nEscDir&SDRESC_LEFT)!=0; }
    void         SetEscapeLeft(bool bOn)                { nEscDir=bOn ? (nEscDir|SDRESC_LEFT) : (nEscDir&~SDRESC_LEFT); }
    bool     IsEscapeRight() const                      { return (nEscDir&SDRESC_RIGHT)!=0; }
    void         SetEscapeRight(bool bOn)               { nEscDir=bOn ? (nEscDir|SDRESC_RIGHT) : (nEscDir&~SDRESC_RIGHT); }
    bool     IsEscapeTop() const                        { return (nEscDir&SDRESC_TOP)!=0; }
    void         SetEscapeTop(bool bOn)                 { nEscDir=bOn ? (nEscDir|SDRESC_TOP) : (nEscDir&~SDRESC_TOP); }
    bool     IsEscapeBottom() const                     { return (nEscDir&SDRESC_BOTTOM)!=0; }
    void         SetEscapeBottom(bool bOn)              { nEscDir=bOn ? (nEscDir|SDRESC_BOTTOM) : (nEscDir&~SDRESC_BOTTOM); }*/
    USHORT       GetId() const                              { return nId; }
    void         SetId(USHORT nNewId)                       { nId=nNewId; }
    bool     IsPercent() const                          { return !bNoPercent; }
    void         SetPercent(bool bOn)                   { bNoPercent=!bOn; }
    // Temporaer zu setzen fuer Transformationen am Bezugsobjekt
    bool     IsReallyAbsolute() const                   { return bReallyAbsolute; }
    USHORT       GetAlign() const                           { return nAlign; }
    void         SetAlign(USHORT nAlg)                      { nAlign=nAlg; }
    USHORT       GetHorzAlign() const                       { return nAlign&0x00FF; }
    void         SetHorzAlign(USHORT nAlg)                  { nAlign=(nAlign&0xFF00)|(nAlg&0x00FF); }
    USHORT       GetVertAlign() const                       { return nAlign&0xFF00; }
    void         SetVertAlign(USHORT nAlg)                  { nAlign=(nAlign&0x00FF)|(nAlg&0xFF00); }
    Point        GetAbsolutePos(const SdrObject& rObj) const;
    friend SvStream& operator<<(SvStream& rOut, const SdrGluePoint& rGP);
    friend SvStream& operator>>(SvStream& rIn, SdrGluePoint& rGP);
};

#define SDRGLUEPOINT_NOTFOUND 0xFFFF

class SdrGluePointList {
    Container aList;
//    bool bSorted; // Muss noch implementiert werden oder?
    // Eigentlich sollte die GluePointList stets sortiert sein (solange die
    // Id's ausreichen)
protected:
    SdrGluePoint* GetObject(USHORT i) const { return (SdrGluePoint*)(aList.GetObject(i)); }
public:
    SdrGluePointList(): aList(1024,4,4) {}
    SdrGluePointList(const SdrGluePointList& rSrcList): aList(1024,4,4)     { *this=rSrcList; }
    ~SdrGluePointList()                                                     { Clear(); }
    void                Clear();
    USHORT              GetCount() const                                    { return USHORT(aList.Count()); }
    // Beim Insert wird dem Objekt (also dem GluePoint) automatisch eine Id zugewiesen.
    // ReturnCode ist der Index des neuen GluePoints in der Liste
    USHORT              Insert(const SdrGluePoint& rGP);
    void                Delete(USHORT nPos)                                 { delete (SdrGluePoint*)aList.Remove(nPos); }
    SdrGluePoint&       operator[](USHORT nPos)                             { return *GetObject(nPos); }
    const SdrGluePoint& operator[](USHORT nPos) const                       { return *GetObject(nPos); }
    USHORT              FindGluePoint(USHORT nId) const;
    // Temporaer zu setzen fuer Transformationen am Bezugsobjekt
    friend SvStream& operator<<(SvStream& rOut, const SdrGluePointList& rGPL);
    friend SvStream& operator>>(SvStream& rIn, SdrGluePointList& rGPL);
};

////////////////////////////////////////////////////////////////////////////////////////////////////

}//end of namespace binfilter
#endif //_SVDGLUE_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
