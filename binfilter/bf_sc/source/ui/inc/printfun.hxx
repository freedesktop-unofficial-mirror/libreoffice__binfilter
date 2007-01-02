/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: printfun.hxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: hr $ $Date: 2007-01-02 17:05:03 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/

#ifndef SC_PRINTFUN_HXX
#define SC_PRINTFUN_HXX


#ifndef SC_PAGEPAR_HXX
#include "pagepar.hxx"
#endif

#ifndef SC_EDITUTIL_HXX
#include "editutil.hxx"
#endif

#ifndef _PRINT_HXX //autogen
#include <vcl/print.hxx>
#endif
class SfxItemSet;
class MultiSelection;
namespace binfilter {

class SfxPrinter;
class SfxProgress;
class ScDocShell;
class ScDocument;
class ScViewData;
class ScPageHFItem;
class EditTextObject;
class ScHeaderEditEngine;
class ScPageBreakData;
class ScPreviewLocationData;
class ScPrintOptions;
class SvxBoxItem;
class SvxBrushItem;
class SvxShadowItem;
class FmFormView;

#define RANGENO_NORANGE             USHRT_MAX

#define PRINT_HEADER_WIDTH          (1.0 * TWIPS_PER_CM)
#define PRINT_HEADER_HEIGHT         (12.8 * TWIPS_PER_POINT)
#define PRINT_HEADER_FONTHEIGHT     200


                                            //  Einstellungen fuer Kopf-/Fusszeilen
struct ScPrintHFParam
{
    BOOL                bEnable;
    BOOL                bDynamic;
    BOOL                bShared;
    long                nHeight;            //  insgesamt (Hoehe+Abstand+Rahmen)
    long                nManHeight;         //  eingestellte Groesse (Min. bei dynamisch)
    USHORT              nDistance;
    USHORT              nLeft;              //  Raender
    USHORT              nRight;
    const ScPageHFItem* pLeft;
    const ScPageHFItem* pRight;
    const SvxBoxItem*   pBorder;
    const SvxBrushItem* pBack;
    const SvxShadowItem* pShadow;
};


// "Ersatz" fuer SV-JobSetup:

class ScJobSetup
{
public:
    ScJobSetup( SfxPrinter* pPrinter );
};

struct ScPrintState                         //  Variablen aus ScPrintFunc retten
{
    USHORT  nPrintTab;
    USHORT  nStartCol;
    USHORT  nStartRow;
    USHORT  nEndCol;
    USHORT  nEndRow;
    USHORT  nZoom;
    USHORT  nPagesX;
    USHORT  nPagesY;
    long    nTabPages;
    long    nTotalPages;
    long    nPageStart;
    long    nDocPages;
};

class ScPageRowEntry
{
private:
    USHORT  nStartRow;
    USHORT  nEndRow;
    USHORT  nPagesX;
    BOOL*   pHidden;
    //!     Anzahl wirklich sichtbarer cachen???

public:
            ScPageRowEntry()    { nStartRow = nEndRow = nPagesX = 0; pHidden = NULL; }
            ~ScPageRowEntry()   { delete[] pHidden; }


    USHORT  GetStartRow() const     { return nStartRow; }
    USHORT  GetEndRow() const       { return nEndRow; }
    USHORT  GetPagesX() const       { return nPagesX; }
    void    SetStartRow(USHORT n)   { nStartRow = n; }
    void    SetEndRow(USHORT n)     { nEndRow = n; }

    void    SetPagesX(USHORT nNew);

};

class ScPrintFunc
{
private:
    ScDocShell*         pDocShell;
    ScDocument*         pDoc;
    SfxPrinter*         pPrinter;
    OutputDevice*       pDev;
    FmFormView*         pDrawView;

    MapMode             aOldPrinterMode;    //  MapMode vor dem Aufruf

    Point               aSrcOffset;         //  Papier-1/100 mm
    Point               aOffset;            //  mit Faktor aus Seitenformat skaliert
    USHORT              nManualZoom;        //  Zoom in Preview (Prozent)
    BOOL                bClearWin;          //  Ausgabe vorher loeschen
    BOOL                bUseStyleColor;
    BOOL                bIsRender;

    USHORT              nPrintTab;
    long                nPageStart;         //  Offset fuer erste Seite
    long                nDocPages;          //  Seiten im Dokument

    const ScRange*      pUserArea;          //  Selektion, wenn im Dialog eingestellt

    const SfxItemSet*   pParamSet;          //  eingestellte Vorlage
    BOOL                bState;             //  aus State-struct erzeugt

                                            //  Parameter aus Vorlage:
    USHORT              nLeftMargin;
    USHORT              nTopMargin;
    USHORT              nRightMargin;
    USHORT              nBottomMargin;
    BOOL                bCenterHor;
    BOOL                bCenterVer;
    BOOL                bLandscape;
    BOOL                bSourceRangeValid;

    USHORT              nPageUsage;
    Size                aPageSize;          //  Drucker-Twips
    const SvxBoxItem*   pBorderItem;
    const SvxBrushItem* pBackgroundItem;
    const SvxShadowItem* pShadowItem;

    ScRange             aLastSourceRange;
    ScPrintHFParam      aHdr;
    ScPrintHFParam      aFtr;
    ScPageTableParam    aTableParam;
    ScPageAreaParam     aAreaParam;

                                            //  berechnete Werte:
    USHORT              nZoom;
    BOOL                bPrintCurrentTable;
    BOOL                bMultiArea;
    long                nTabPages;
    long                nTotalPages;

    USHORT              nObjectFlags;

    Rectangle           aPageRect;          //  Dokument-Twips

    MapMode             aLogicMode;         //  in DoPrint gesetzt
    MapMode             aOffsetMode;
    MapMode             aTwipMode;
    double              nScaleX;
    double              nScaleY;

    USHORT              nRepeatStartCol;
    USHORT              nRepeatEndCol;
    USHORT              nRepeatStartRow;
    USHORT              nRepeatEndRow;

    USHORT              nStartCol;
    USHORT              nStartRow;
    USHORT              nEndCol;
    USHORT              nEndRow;

    USHORT*             pPageEndX;          // Seitenaufteilung
    USHORT*             pPageEndY;
    ScPageRowEntry*     pPageRows;
    USHORT              nPagesX;
    USHORT              nPagesY;
    USHORT              nTotalY;

    ScHeaderEditEngine* pEditEngine;
    SfxItemSet*         pEditDefaults;

    ScHeaderFieldData   aFieldData;

    List                aNotePosList;       //  Reihenfolge der Notizen

    ScPageBreakData*    pPageData;          // zum Eintragen der Umbrueche etc.

public:
                    ScPrintFunc( ScDocShell* pShell, SfxPrinter* pNewPrinter, USHORT nTab,
                                 long nPage = 0, long nDocP = 0,
                                 const ScRange* pArea = NULL,
                                 const ScPrintOptions* pOptions = NULL,
                                 ScPageBreakData* pData = NULL );

                    // ctors for device other than printer - for preview and pdf:

                    ScPrintFunc( OutputDevice* pOutDev, ScDocShell* pShell, USHORT nTab,
                                 long nPage = 0, long nDocP = 0,
                                 const ScRange* pArea = NULL,
                                 const ScPrintOptions* pOptions = NULL );


                    ~ScPrintFunc();


    void            SetDrawView( FmFormView* pNew );

    void            SetDateTime( const Date& rDate, const Time& rTime );

    void            SetRenderFlag( BOOL bFlag );

    BOOL            UpdatePages();

    long            DoPrint( const MultiSelection& rPageRanges,
                                long nStartPage, long nDisplayStart, BOOL bDoPrint,
                                SfxProgress* pProgress, ScPreviewLocationData* pLocationData );

                    //  Werte abfragen - sofort

    Size            GetPageSize() const { return aPageSize; }
    long            GetFirstPageNo() const  { return aTableParam.nFirstPageNo; }

                    //  letzte Werte abfragen - nach DoPrint !!!

    double          GetScaleX() const { return nScaleX; }
    double          GetScaleY() const { return nScaleY; }
    long            GetTotalPages() const { return nTotalPages; }
    USHORT          GetZoom() const { return nZoom; }

    void            ResetBreaks( USHORT nTab );

    BOOL            GetLastSourceRange( ScRange& rRange ) const{DBG_BF_ASSERT(0, "STRIP"); return FALSE;} //STRIP001 BOOL           GetLastSourceRange( ScRange& rRange ) const;

#ifdef _PRINTFUN_CXX
private:
    void            Construct( const ScPrintOptions* pOptions );
    void            InitParam( const ScPrintOptions* pOptions );
    void            CalcZoom( USHORT nRangeNo );
    void            CalcPages();
    long            CountPages();
    long            CountNotePages();

    BOOL            AdjustPrintArea( BOOL bNew );

    Size            GetDocPageSize();

    long            TextHeight( const EditTextObject* pObject );
    void            MakeEditEngine();
    void            UpdateHFHeight( ScPrintHFParam& rParam );

    void            InitModes();

    void            ReplaceFields( long nPageNo );      // aendert Text in pEditEngine




#endif
};



} //namespace binfilter
#endif

