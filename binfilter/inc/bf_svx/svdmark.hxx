/*************************************************************************
 *
 *  $RCSfile: svdmark.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:28:50 $
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

#ifndef _SVDMARK_HXX
#define _SVDMARK_HXX

#ifndef _CONTNR_HXX //autogen
#include <tools/contnr.hxx>
#endif

#ifndef _STRING_HXX //autogen
#include <tools/string.hxx>
#endif
class Rectangle;
namespace binfilter {

class SdrPage;
class SdrObjList;
class SdrObject;
class SdrPageView;

// Ein Container fuer USHORTs (im Prinzip ein dynamisches Array)
class SdrUShortCont {
    Container aArr;
    FASTBOOL bSorted;
    FASTBOOL bDelDups;
private:
//STRIP001  void CheckSort(ULONG nPos);
public:
    SdrUShortCont(USHORT nBlock, USHORT nInit, USHORT nResize): aArr(nBlock,nInit,nResize), bSorted(TRUE), bDelDups(TRUE) {}
    SdrUShortCont(const SdrUShortCont& rCont): aArr(rCont.aArr), bSorted(rCont.bSorted), bDelDups(rCont.bDelDups) {}
    SdrUShortCont& operator=(const SdrUShortCont& rCont)     { aArr=rCont.aArr; bSorted=rCont.bSorted; bDelDups=rCont.bDelDups; return *this; }
    FASTBOOL       operator==(const SdrUShortCont& rCont) const { return aArr==rCont.aArr; }
    FASTBOOL       operator!=(const SdrUShortCont& rCont) const { return aArr!=rCont.aArr; }
    void     Clear()                                           { aArr.Clear(); bSorted=TRUE; }
//STRIP001  void     Sort();
//STRIP001  void     ForceSort()                                       { if (!bSorted) Sort(); }
//STRIP001  void     Insert(USHORT nElem, ULONG nPos=CONTAINER_APPEND) { aArr.Insert((void*)ULONG(nElem),nPos); if (bSorted) CheckSort(nPos); }
    void     Remove(ULONG nPos)                                { aArr.Remove(nPos); }
//STRIP001  void     Replace(USHORT nElem, ULONG nPos)                 { aArr.Replace((void*)ULONG(nElem),nPos); if (bSorted) CheckSort(nPos); }
    USHORT   GetObject(ULONG nPos) const                       { return USHORT(ULONG(aArr.GetObject(nPos))); }
    ULONG    GetPos(USHORT nElem) const                        { return aArr.GetPos((void*)(ULONG)nElem); }
    ULONG    GetCount() const                                  { return aArr.Count(); }
    FASTBOOL Exist(USHORT nElem) const                         { return aArr.GetPos((void*)(ULONG)nElem)!=CONTAINER_ENTRY_NOTFOUND; }
};

class SdrMark { // Alles was eine View ueber ein markiertes Objekt wissen muss
protected:
    SdrObject*     pObj;
    SdrPageView*   pPageView;
    SdrUShortCont* pPoints;     // Markierte Punkte
    SdrUShortCont* pLines;      // Markierte Linienabschnitte
    SdrUShortCont* pGluePoints; // Markierte Klebepunkte (deren Id's)
    FASTBOOL       bCon1;       // fuer Connectoren
    FASTBOOL       bCon2;       // fuer Connectoren
    USHORT         nUser;       // z.B. fuer CopyObjects, mitkopieren von Edges
public:
    SdrMark(SdrObject* pNewObj=NULL, SdrPageView* pNewPageView=NULL): pObj(pNewObj), pPageView(pNewPageView), pPoints(NULL), pLines(NULL), pGluePoints(NULL), bCon1(FALSE), bCon2(FALSE), nUser(0) {}
    SdrMark(const SdrMark& rMark): pObj(NULL), pPageView(NULL), pPoints(NULL), pLines(NULL), pGluePoints(NULL), bCon1(FALSE), bCon2(FALSE), nUser(0) { *this=rMark; }
    ~SdrMark()                                          { if (pPoints!=NULL) delete pPoints; if (pLines!=NULL) delete pLines; if (pGluePoints!=NULL) delete pGluePoints; }
//STRIP001  SdrMark&     operator=(const SdrMark& rMark);
//STRIP001  FASTBOOL     operator==(const SdrMark& rMark) const;
//STRIP001  FASTBOOL     operator!=(const SdrMark& rMark) const { return !operator==(rMark); }
    SdrObject*   GetObj() const                         { return pObj; }
//STRIP001  SdrPage*     GetPage() const;
//STRIP001  SdrObjList*  GetObjList() const;
    SdrPageView* GetPageView() const                    { return pPageView; }
    void         SetObj(SdrObject* pNewObj)             { pObj =pNewObj; }
    void         SetPageView(SdrPageView* pNewPageView) { pPageView=pNewPageView; }
    void         SetCon1(FASTBOOL bOn)                  { bCon1=bOn; }
    FASTBOOL     IsCon1() const                         { return bCon1; }
    void         SetCon2(FASTBOOL bOn)                  { bCon2=bOn; }
    FASTBOOL     IsCon2() const                         { return bCon2; }
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
    FASTBOOL  bPointNameOk;
    FASTBOOL  bGluePointNameOk;
    FASTBOOL  bNameOk;
    FASTBOOL  bSorted;
private:
    // Nicht implementiert:
    FASTBOOL operator==(const SdrMarkList& rCmpMarkList) const;
private:
    const XubString& GetPointMarkDescription(FASTBOOL bGlue) const;
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

    void  InsertEntry(const SdrMark& rMark, FASTBOOL bChkSort=TRUE);
//STRIP001  void  DeleteMark(ULONG nNum);
//STRIP001  void  DeleteMarkNum(ULONG nNum) /* nur uebergangsweise */        { DeleteMark(nNum); }
//STRIP001  void  ReplaceMark(const SdrMark& rNewMark, ULONG nNum);

    // bReverse kann einen Performancevorteil bringen, wenn sicher ist,
    // dass die SrcList genau verkehrt herum ist.
//STRIP001  void  Merge(const SdrMarkList& rSrcList, FASTBOOL bReverse=FALSE);

    // Alle Entrys einer bestimmten PageView rauswerfen inkl delete
    FASTBOOL  DeletePageView (const SdrPageView& rPV);
    // Alle Objekte einer Seiteansicht markieren
//STRIP001  FASTBOOL  InsertPageView(const SdrPageView& rPV);

    void SetNameDirty()                                              { bNameOk=FALSE; bPointNameOk=FALSE; bGluePointNameOk=FALSE; }

    // Eine verbale Beschreibung der markierten Objekte z.B.:
    // "27 Linien", "12 Objekte", "Polygon" oder auch "Kein Objekt"
//STRIP001  const String& GetMarkDescription() const;
//STRIP001  const String& GetPointMarkDescription() const                    { return GetPointMarkDescription(FALSE); }
    const String& GetGluePointMarkDescription() const                { return GetPointMarkDescription(TRUE); }

    // Schliesslich kann sich eine Mehrfach-Markierung
    // ueber mehrere Seiten erstrecken ...
//STRIP001  USHORT GetPageViewAnz() const;
//STRIP001  SdrPageView* GetPageView(USHORT nNum) const;
    // pPage=NULL: Die Markierungen aller! Seiten beruecksichtigen
    FASTBOOL TakeBoundRect(SdrPageView* pPageView, Rectangle& rRect) const;
    FASTBOOL TakeSnapRect(SdrPageView* pPageView, Rectangle& rRect) const;

    // Es werden saemtliche Entries kopiert!
    void operator=(const SdrMarkList& rLst);

};
// Die Klasse kopiert alle eingefuegten MarkEntrys auf den Heap. Die Verwendung
// ist z.B. wie folgt gedacht:
//     InsertEntry(SdrMark(pObj,pPage));

}//end of namespace binfilter
#endif //_SVDMARK_HXX

