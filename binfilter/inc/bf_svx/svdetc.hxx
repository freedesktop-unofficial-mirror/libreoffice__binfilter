/*************************************************************************
 *
 *  $RCSfile: svdetc.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: kz $ $Date: 2004-07-30 14:53:17 $
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

#ifndef _SVDETC_HXX
#define _SVDETC_HXX

#ifndef _STRING_HXX //autogen
#include <tools/string.hxx>
#endif

#ifndef _CONTNR_HXX //autogen
#include <tools/contnr.hxx>
#endif

#ifndef _OUTDEV_HXX //autogen
#include <vcl/outdev.hxx>
#endif

#ifndef _SHL_HXX //autogen
#include <tools/shl.hxx>
#endif

#ifndef _OUTLINER_HXX //autogen
#include <bf_svx/outliner.hxx>
#endif
namespace com { namespace sun { namespace star { namespace lang {
    struct Locale;
}}}}
class SvtSysLocale;
class CharClass;
class LocaleDataWrapper;
class SfxItemSet;
class Link;
class AutoTimer;
namespace binfilter {

////////////////////////////////////////////////////////////////////////////////////////////////////

// ExchangeFormat-Id der DrawingEngine holen. Daten koennen dann per
//   static BOOL CopyData(pData,nLen,nFormat);
// bereitgestellt werden, wobei pData/nLen einen SvMemoryStream beschreiben in
// dem ein SdrModel gestreamt wird an dem fuer die Zeitdauer des Streamens das
// Flag SdrModel::SetStreamingSdrModel(TRUE) gesetzt wird.
// ULONG SdrGetExchangeFormat(); -- JP 18.01.99 - dafuer gibt es ein define

class SdrOutliner;
class SdrModel;

//STRIP008 namespace com { namespace sun { namespace star { namespace lang {
//STRIP008  struct Locale;
//STRIP008 }}}}

// Globale Defaulteinstellungen fuer die DrawingEngine.
// Diese Einstellungen sollte man direkt beim Applikationsstart
// vornehmen, noch bevor andere Methoden der Engine gerufen werden.
class SdrEngineDefaults
{
friend class SdrAttrObj;
    String     aFontName;
    FontFamily eFontFamily;
    Color      aFontColor;
    ULONG      nFontHeight;
    MapUnit    eMapUnit;
    Fraction   aMapFraction;

private:
    static SdrEngineDefaults& GetDefaults();

public:
    SdrEngineDefaults();
    // Default Fontname ist "Times New Roman"
    static void       SetFontName(const String& rFontName) { GetDefaults().aFontName=rFontName; }
    static String     GetFontName()                        { return GetDefaults().aFontName; }
    // Default FontFamily ist FAMILY_ROMAN
    static void       SetFontFamily(FontFamily eFam)       { GetDefaults().eFontFamily=eFam; }
    static FontFamily GetFontFamily()                      { return GetDefaults().eFontFamily; }
    // Default FontColor ist COL_BLACK
    static void       SetFontColor(const Color& rColor)    { GetDefaults().aFontColor=rColor; }
    static Color      GetFontColor()                       { return GetDefaults().aFontColor; }
    // Default FontHeight ist 847. Die Fonthoehe wird in logischen Einheiten
    // (MapUnit/MapFraction (siehe unten)) angegeben. Die Defaulteinstellung
    // 847/100mm entspricht also ca. 24 Point. Verwendet man stattdessen
    // beispielsweise Twips (SetMapUnit(MAP_TWIP)) (20 Twip = 1 Point) muss
    // man als Fonthoehe 480 angeben um 24 Point als default zu erhalten.
    static void       SetFontHeight(ULONG nHeight)         { GetDefaults().nFontHeight=nHeight; }
    static ULONG      GetFontHeight()                      { return GetDefaults().nFontHeight; }
    // Der MapMode wird fuer den globalen Outliner benoetigt.
    // Gleichzeitig bekommt auch jedes neu instanziierte SdrModel
    // diesen MapMode default zugewiesen.
    // Default MapUnit ist MAP_100TH_MM
    static void       SetMapUnit(MapUnit eMap)             { GetDefaults().eMapUnit=eMap; }
    static MapUnit    GetMapUnit()                         { return GetDefaults().eMapUnit; }
    // Default MapFraction ist 1/1.
    static void       SetMapFraction(const Fraction& rMap) { GetDefaults().aMapFraction=rMap; }
    static Fraction   GetMapFraction()                     { return GetDefaults().aMapFraction; }
    // Der Aufruf der folgenden Methode veranlasst die Engine
    // ihre sprachabhaengigen Resourcen neu zu initiallisieren.
    // Bereits bestehende Undotexte, etc. bleiben jedoch in der
    // sprache erhalten, in der sie erzeugt wurden.
//STRIP001  static void       LanguageHasChanged();

    // Einen Outliner mit den engineglobalen
    // Defaulteinstellungen auf dem Heap erzeugen.
    // Ist pMod<>NULL, dann wird der MapMode des uebergebenen
    // Models verwendet. Die resultierende Default-Fonthoehe bleibt
    // jedoch dieselbe (die logische Fonthoehe wird umgerechnet).
    friend SdrOutliner* SdrMakeOutliner( USHORT nOutlinerMode, SdrModel* pMod );
};

// Liefert eine Ersatzdarstellung fuer einen XFillStyle
// Bei XFILL_NONE gibt's FALSE und rCol bleibt unveraendert.
FASTBOOL GetDraftFillColor(const SfxItemSet& rSet, Color& rCol);

// Ein Container fuer USHORTs (im Prinzip ein dynamisches Array)
class UShortCont {
    Container aArr;
public:
    UShortCont(USHORT nBlock, USHORT nInit, USHORT nResize): aArr(nBlock,nInit,nResize) {}
    void   Clear()                                           { aArr.Clear(); }
    void   Insert(USHORT nElem, ULONG nPos=CONTAINER_APPEND) { aArr.Insert((void*)ULONG(nElem),nPos); }
    void   Remove(ULONG nPos)                                { aArr.Remove(nPos); }
    void   Replace(USHORT nElem, ULONG nPos)                 { aArr.Replace((void*)ULONG(nElem),nPos); }
    USHORT GetObject(ULONG nPos)                       const { return USHORT(ULONG(aArr.GetObject(nPos))); }
    ULONG  GetPos(USHORT nElem)                        const { return aArr.GetPos((void*)(ULONG)nElem); }
    ULONG  GetCount()                                  const { return aArr.Count(); }
    void   Sort();
};

class ContainerSorter {
protected:
    Container& rCont;
private:
#if _SOLAR__PRIVATE
    void ImpSubSort(long nL, long nR) const;
#endif // __PRIVATE
public:
    ContainerSorter(Container& rNewCont): rCont(rNewCont) {}
#if SUPD>358
    void DoSort(ULONG a=0, ULONG b=0xFFFFFFFF) const;
#else
    void DoSort();
    void DoSort(ULONG a, ULONG b=0xFFFFFFFF) const;
#endif
#ifdef This_Is_Just_For_A_Comment
    Compare() muss returnieren:
      -1 falls *pElem1<*pElem2
       0 falls *pElem1=*pElem2
      +1 falls *pElem1>*pElem2
#endif
    virtual int Compare(const void* pElem1, const void* pElem2) const = 0;
private: // damit keiner vergessen wird
//STRIP001 virtual
//STRIP001 #if SUPD <= 355
//STRIP001      FASTBOOL
//STRIP001 #else
//STRIP001      void
//STRIP001 #endif
//STRIP001               Is1stLessThan2nd(const void* pElem1, const void* pElem2) const;
//  virtual FASTBOOL Is1stLessThan2nd(const void* pElem1, const void* pElem2) const=NULL;
};

////////////////////////////////////////////////////////////////////////////////////////////////////

#if _SOLAR__PRIVATE
#define SDRHDC_SAVEPEN                1 /* Save Linecolor                     */
#define SDRHDC_SAVEBRUSH              2 /* Save Fillcolorn                    */
#define SDRHDC_SAVEFONT               4 /* Save Font                          */
#define SDRHDC_SAVEPENANDBRUSH        3 /* Save Line- and FillColor           */
#define SDRHDC_SAVEPENANDBRUSHANDFONT 7 /* Save Font, Line- and fillcolor     */
#define SDRHDC_SAVECLIPPING           8 /* Save Clipping                      */
#define SDRHDC_SAVEALL               15 /* Save Clipping, Font, fill- and linecolor */

class ImpClipMerk;
class ImpColorMerk;
class ImpSdrHdcMerk
{
    ImpColorMerk* pFarbMerk;
    ImpClipMerk*  pClipMerk;
    Color*        pLineColorMerk;
    USHORT        nMode;
public:
    ImpSdrHdcMerk(const OutputDevice& rOut, USHORT nNewMode=SDRHDC_SAVEALL, FASTBOOL bAutoMerk=TRUE);
    ~ImpSdrHdcMerk();
    void Save(const OutputDevice& rOut);
//STRIP001  FASTBOOL IsSaved() const                 { return pFarbMerk!=NULL || pClipMerk!=NULL || pLineColorMerk!=NULL; }
    void Restore(OutputDevice& rOut, USHORT nMask=SDRHDC_SAVEALL) const;
};
#endif // __PRIVATE

////////////////////////////////////////////////////////////////////////////////////////////////////

// Ein ItemSet auf Outliner- bzw. EditEngine-Items durchsuchen
// Liefert TRUE, wenn der Set solchen Items enthaelt.
//STRIP001 BOOL SearchOutlinerItems(const SfxItemSet& rSet, BOOL bInklDefaults, BOOL* pbOnlyEE=NULL);

// zurueck erhaelt man einen neuen WhichTable den
// man dann irgendwann mit delete platthauen muss.
//STRIP001 USHORT* RemoveWhichRange(const USHORT* pOldWhichTable, USHORT nRangeBeg, USHORT nRangeEnd);

////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////


// Hilfsklasse zur kommunikation zwischen dem Dialog
// zum aufbrechen von Metafiles (sd/source/ui/dlg/brkdlg.cxx),
// SdrEditView::DoImportMarkedMtf() und
// ImpSdrGDIMetaFileImport::DoImport()
//STRIP001 class SvdProgressInfo
//STRIP001 {
//STRIP001 private:
//STRIP001  ULONG nSumActionCount;  // Summe aller Actions
//STRIP001  ULONG nSumCurAction;    // Summe aller bearbeiteten Actions
//STRIP001
//STRIP001  ULONG nActionCount;     // Anzahl der Actions im akt. Obj.
//STRIP001  ULONG nCurAction;       // Anzahl bearbeiteter Act. im akt. Obj.
//STRIP001
//STRIP001  ULONG nInsertCount;     // Anzahl einzufuegender Act. im akt. Obj.
//STRIP001  ULONG nCurInsert;       // Anzahl bereits eingefuegter Actions
//STRIP001
//STRIP001  ULONG nObjCount;        // Anzahl der selektierten Objekte
//STRIP001  ULONG nCurObj;          // Aktuelles Objekt
//STRIP001
//STRIP001  Link *pLink;
//STRIP001
//STRIP001 public:
//STRIP001  SvdProgressInfo( Link *_pLink );
//STRIP001
//STRIP001  void Init( ULONG _nSumActionCount, ULONG _nObjCount );
//STRIP001
//STRIP001  BOOL SetNextObject();
//STRIP001
//STRIP001  void SetActionCount( ULONG _nActionCount );
//STRIP001  void SetInsertCount( ULONG _nInsertCount );
//STRIP001
//STRIP001  BOOL ReportActions( ULONG nAnzActions );
//STRIP001  BOOL ReportInserts( ULONG nAnzInserts );
//STRIP001
//STRIP001  ULONG GetSumActionCount() const { return nSumActionCount; };
//STRIP001  ULONG GetSumCurAction() const { return nSumCurAction; };
//STRIP001  ULONG GetObjCount() const { return nObjCount; };
//STRIP001  ULONG GetCurObj() const { return nCurObj; };
//STRIP001
//STRIP001  ULONG GetActionCount() const { return nActionCount; };
//STRIP001  ULONG GetCurAction() const { return nCurAction; };
//STRIP001
//STRIP001  ULONG GetInsertCount() const { return nInsertCount; };
//STRIP001  ULONG GetCurInsert() const { return nCurInsert; };
//STRIP001
//STRIP001  void ReportError();
//STRIP001  BOOL ReportRescales( ULONG nAnzRescales );
//STRIP001 };

class SdrLinkList
{
    Container aList;
protected:
    unsigned FindEntry(const Link& rLink) const;
public:
    SdrLinkList(): aList(1024,4,4)        {}
    ~SdrLinkList()                        { Clear(); }
    void Clear();
    unsigned GetLinkCount() const            { return (unsigned)aList.Count(); }
    Link& GetLink(unsigned nNum)             { return *((Link*)(aList.GetObject(nNum))); }
    const Link& GetLink(unsigned nNum) const { return *((Link*)(aList.GetObject(nNum))); }
    void InsertLink(const Link& rLink, unsigned nPos=0xFFFF);
    void RemoveLink(const Link& rLink);
    FASTBOOL HasLink(const Link& rLink) const { return FindEntry(rLink)!=0xFFFF; }
};

// Fuer die Factory in SvdObj.CXX
SdrLinkList& ImpGetUserMakeObjHdl();
SdrLinkList& ImpGetUserMakeObjUserDataHdl();

class SdrOle2Obj;

class OLEObjCache : public Container
{
    ULONG               nSize;
    AutoTimer*          pTimer;

    BOOL UnloadObj( SdrOle2Obj* pObj );
    DECL_LINK( UnloadCheckHdl, AutoTimer* );

public:
    OLEObjCache();
    ~OLEObjCache();

//STRIP001  void SetSize(ULONG nNewSize);
    void InsertObj(SdrOle2Obj* pObj);
    void RemoveObj(SdrOle2Obj* pObj);
};

class SdrGlobalData
{
public:
    SdrLinkList         aUserMakeObjHdl;
    SdrLinkList         aUserMakeObjUserDataHdl;
    SdrOutliner*        pOutliner;
    SdrEngineDefaults*  pDefaults;
    ResMgr*             pResMgr;
    String*             pStrCache;
    ULONG               nExchangeFormat;
    OLEObjCache         aOLEObjCache;
    const SvtSysLocale*         pSysLocale;     // follows always locale settings
    const CharClass*            pCharClass;     // follows always SysLocale
    const LocaleDataWrapper*    pLocaleData;    // follows always SysLocale

public:
    SdrGlobalData();
    ~SdrGlobalData();

    OLEObjCache&        GetOLEObjCache() { return aOLEObjCache; }
};

inline SdrGlobalData& GetSdrGlobalData()
{
    void** ppAppData=GetAppData(BF_SHL_SVD);
    if (*ppAppData==NULL) {
        *ppAppData=new SdrGlobalData;
    }
    return *((SdrGlobalData*)*ppAppData);
}

/////////////////////////////////////////////////////////////////////

}//end of namespace binfilter
#endif //_SVDETC_HXX

