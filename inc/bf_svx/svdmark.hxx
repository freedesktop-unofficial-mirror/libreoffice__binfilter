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

#ifndef _SVDMARK_HXX
#define _SVDMARK_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_tools/contnr.hxx>

#include <bf_tools/string.hxx>
class Rectangle;
namespace binfilter {

class SdrPage;
class SdrObjList;
class SdrObject;
class SdrPageView;

// Ein Container fuer USHORTs (im Prinzip ein dynamisches Array)
class SdrUShortCont {
    Container aArr;
    bool bSorted;
    bool bDelDups;
private:
public:
    SdrUShortCont(USHORT nBlock, USHORT nInit, USHORT nResize): aArr(nBlock,nInit,nResize), bSorted(TRUE), bDelDups(TRUE) {}
    SdrUShortCont(const SdrUShortCont& rCont): aArr(rCont.aArr), bSorted(rCont.bSorted), bDelDups(rCont.bDelDups) {}
    SdrUShortCont& operator=(const SdrUShortCont& rCont)     { aArr=rCont.aArr; bSorted=rCont.bSorted; bDelDups=rCont.bDelDups; return *this; }
    bool       operator==(const SdrUShortCont& rCont) const { return aArr==rCont.aArr; }
    bool       operator!=(const SdrUShortCont& rCont) const { return aArr!=rCont.aArr; }
    void     Clear()                                           { aArr.Clear(); bSorted=TRUE; }
    void     Remove(ULONG nPos)                                { aArr.Remove(nPos); }
    USHORT   GetObject(ULONG nPos) const                       { return USHORT(ULONG(aArr.GetObject(nPos))); }
    ULONG    GetCount() const                                  { return aArr.Count(); }
};

class SdrMark { // Alles was eine View ueber ein markiertes Objekt wissen muss
protected:
    SdrObject*     pObj;
    SdrPageView*   pPageView;
    SdrUShortCont* pPoints;     // Markierte Punkte
    SdrUShortCont* pLines;      // Markierte Linienabschnitte
    SdrUShortCont* pGluePoints; // Markierte Klebepunkte (deren Id's)
    bool       bCon1;       // fuer Connectoren
    bool       bCon2;       // fuer Connectoren
    USHORT         nUser;       // z.B. fuer CopyObjects, mitkopieren von Edges
public:
    SdrMark(SdrObject* pNewObj=NULL, SdrPageView* pNewPageView=NULL): pObj(pNewObj), pPageView(pNewPageView), pPoints(NULL), pLines(NULL), pGluePoints(NULL), bCon1(FALSE), bCon2(FALSE), nUser(0) {}
    SdrMark(const SdrMark& rMark): pObj(NULL), pPageView(NULL), pPoints(NULL), pLines(NULL), pGluePoints(NULL), bCon1(FALSE), bCon2(FALSE), nUser(0) { *this=rMark; }
    ~SdrMark()                                          { if (pPoints!=NULL) delete pPoints; if (pLines!=NULL) delete pLines; if (pGluePoints!=NULL) delete pGluePoints; }
    SdrObject*   GetObj() const                         { return pObj; }
    SdrPageView* GetPageView() const                    { return pPageView; }
    void         SetObj(SdrObject* pNewObj)             { pObj =pNewObj; }
    void         SetPageView(SdrPageView* pNewPageView) { pPageView=pNewPageView; }
    void         SetCon1(bool bOn)                  { bCon1=bOn; }
    bool     IsCon1() const                         { return bCon1; }
    void         SetCon2(bool bOn)                  { bCon2=bOn; }
    bool     IsCon2() const                         { return bCon2; }
    void         SetUser(USHORT nVal)                   { nUser=nVal; }
    USHORT       GetUser() const                        { return nUser; }
    const SdrUShortCont* GetMarkedPoints() const        { return pPoints;     }
    const SdrUShortCont* GetMarkedLines() const         { return pLines;      }
    const SdrUShortCont* GetMarkedGluePoints() const    { return pGluePoints; }
    SdrUShortCont*       GetMarkedPoints()              { return pPoints;     }
    SdrUShortCont*       GetMarkedLines()               { return pLines;      }
    SdrUShortCont*       GetMarkedGluePoints()          { return pGluePoints; }
    SdrUShortCont*       ForceMarkedPoints()            { if (pPoints==NULL) pPoints=new SdrUShortCont(1024,32,32); return pPoints; }
    SdrUShortCont*       ForceMarkedLines()             { if (pLines==NULL) pLines=new SdrUShortCont(1024,32,32); return pLines; }
    SdrUShortCont*       ForceMarkedGluePoints()        { if (pGluePoints==NULL) pGluePoints=new SdrUShortCont(1024,32,32); return pGluePoints; }
};

class SdrMarkList {
protected:
    Container aList;
    String    aMarkName;
    String    aPointName;
    String    aGluePointName;
    bool  bPointNameOk;
    bool  bGluePointNameOk;
    bool  bNameOk;
    bool  bSorted;
private:
    // Nicht implementiert:
    bool operator==(const SdrMarkList& rCmpMarkList) const;
private:
    const XubString& GetPointMarkDescription(bool bGlue) const;
protected:
public:
    SdrMarkList()                        : aList(1024,64,64),bPointNameOk(FALSE),bGluePointNameOk(FALSE),bNameOk(FALSE),bSorted(TRUE) { }
    SdrMarkList(const SdrMarkList& rLst) : aList(1024,64,64)        { *this=rLst; }
    ~SdrMarkList()                                                  { Clear(); }
    void     Clear();
    // Sicherstellen, das die Liste sortiert ist:
    void     ForceSort();
    void     SetUnsorted()                                           { bSorted=FALSE; }
    ULONG    GetMarkCount() const                                    { return aList.Count(); }
    SdrMark* GetMark(ULONG nNum) const                               { return (SdrMark*)(aList.GetObject(nNum)); }

    // FindObject() sucht nach einer Markierung eines SdrObject.
    // Die Methode ist nicht const, da ein ForceSort gerufen wird!
    // Rueckgabewert ist der Index der gefundenen Mark-Entry bzw.
    // CONTAINER_ENTRY_NOTFOUND.
    ULONG FindObject(const SdrObject* pObj);

    // bReverse kann einen Performancevorteil bringen, wenn sicher ist,
    // dass die SrcList genau verkehrt herum ist.

    // Alle Entrys einer bestimmten PageView rauswerfen inkl delete
    bool  DeletePageView (const SdrPageView& rPV);
    // Alle Objekte einer Seiteansicht markieren

    void SetNameDirty()                                              { bNameOk=FALSE; bPointNameOk=FALSE; bGluePointNameOk=FALSE; }

    // Eine verbale Beschreibung der markierten Objekte z.B.:
    // "27 Linien", "12 Objekte", "Polygon" oder auch "Kein Objekt"
    const String& GetGluePointMarkDescription() const                { return GetPointMarkDescription(TRUE); }

    // Schliesslich kann sich eine Mehrfach-Markierung
    // ueber mehrere Seiten erstrecken ...
    // pPage=NULL: Die Markierungen aller! Seiten beruecksichtigen
    bool TakeBoundRect(SdrPageView* pPageView, Rectangle& rRect) const;
    bool TakeSnapRect(SdrPageView* pPageView, Rectangle& rRect) const;

    // Es werden saemtliche Entries kopiert!
    void operator=(const SdrMarkList& rLst);

};

}//end of namespace binfilter
#endif //_SVDMARK_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
