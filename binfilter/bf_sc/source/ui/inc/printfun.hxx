/*************************************************************************
 *
 *  $RCSfile: printfun.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:39:44 $
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
//STRIP001
//STRIP001  Size        aUserSize;
//STRIP001  MapMode     aUserMapMode;
//STRIP001  Paper       ePaper;
//STRIP001  Orientation eOrientation;
//STRIP001  USHORT      nPaperBin;
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

//STRIP001          ScPageRowEntry(const ScPageRowEntry& r);
//STRIP001  const ScPageRowEntry& operator=(const ScPageRowEntry& r);

    USHORT  GetStartRow() const     { return nStartRow; }
    USHORT  GetEndRow() const       { return nEndRow; }
    USHORT  GetPagesX() const       { return nPagesX; }
    void    SetStartRow(USHORT n)   { nStartRow = n; }
    void    SetEndRow(USHORT n)     { nEndRow = n; }

    void    SetPagesX(USHORT nNew);
//STRIP001  void    SetHidden(USHORT nX);
//STRIP001  BOOL    IsHidden(USHORT nX) const;

//STRIP001  USHORT  CountVisible() const;
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

//STRIP001                  ScPrintFunc( OutputDevice* pOutDev, ScDocShell* pShell,
//STRIP001                               const ScPrintState& rState,
//STRIP001                               const ScPrintOptions* pOptions );

                    ~ScPrintFunc();

//STRIP001  static void     DrawToDev( ScDocument* pDoc, OutputDevice* pDev, double nPrintFactor,
//STRIP001                              const Rectangle& rBound, ScViewData* pViewData, BOOL bMetaFile );

    void            SetDrawView( FmFormView* pNew );

//STRIP001  void            SetOffset( const Point& rOfs );
//STRIP001  void            SetManualZoom( USHORT nNewZoom );
    void            SetDateTime( const Date& rDate, const Time& rTime );

//STRIP001  void            SetClearFlag( BOOL bFlag );
//STRIP001  void            SetUseStyleColor( BOOL bFlag );
    void            SetRenderFlag( BOOL bFlag );

    BOOL            UpdatePages();

//STRIP001  void            ApplyPrintSettings();       // aus DoPrint() schon gerufen
    long            DoPrint( const MultiSelection& rPageRanges,
                                long nStartPage, long nDisplayStart, BOOL bDoPrint,
                                SfxProgress* pProgress, ScPreviewLocationData* pLocationData );

                    //  Werte abfragen - sofort

    Size            GetPageSize() const { return aPageSize; }
//STRIP001  Size            GetDataSize() const;
//STRIP001  void            GetScaleData( Size& rPhysSize, long& rDocHdr, long& rDocFtr );
    long            GetFirstPageNo() const  { return aTableParam.nFirstPageNo; }

                    //  letzte Werte abfragen - nach DoPrint !!!

    double          GetScaleX() const { return nScaleX; }
    double          GetScaleY() const { return nScaleY; }
    long            GetTotalPages() const { return nTotalPages; }
    USHORT          GetZoom() const { return nZoom; }

    void            ResetBreaks( USHORT nTab );

//STRIP001  void            GetPrintState( ScPrintState& rState );
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

//STRIP001  BOOL            IsLeft( long nPageNo );
    BOOL            IsMirror( long nPageNo );
    void            ReplaceFields( long nPageNo );      // aendert Text in pEditEngine
//STRIP001  void            MakeTableString();                  // setzt aTableStr

//STRIP001  void            PrintPage( long nPageNo,
//STRIP001                                  USHORT nX1, USHORT nY1, USHORT nX2, USHORT nY2,
//STRIP001                                  BOOL bDoPrint, ScPreviewLocationData* pLocationData );
//STRIP001  void            PrintArea( USHORT nX1, USHORT nY1, USHORT nX2, USHORT nY2,
//STRIP001                                  long nScrX, long nScrY,
//STRIP001                                  BOOL bShLeft, BOOL bShTop, BOOL bShRight, BOOL bShBottom );
//STRIP001  void            LocateArea( USHORT nX1, USHORT nY1, USHORT nX2, USHORT nY2,
//STRIP001                                  long nScrX, long nScrY, BOOL bRepCol, BOOL bRepRow,
//STRIP001                                  ScPreviewLocationData& rLocationData );
//STRIP001  void            PrintColHdr( USHORT nX1, USHORT nX2, long nScrX, long nScrY );
//STRIP001  void            PrintRowHdr( USHORT nY1, USHORT nY2, long nScrX, long nScrY );
//STRIP001  void            LocateColHdr( USHORT nX1, USHORT nX2, long nScrX, long nScrY,
//STRIP001                              BOOL bRepCol, ScPreviewLocationData& rLocationData );
//STRIP001  void            LocateRowHdr( USHORT nY1, USHORT nY2, long nScrX, long nScrY,
//STRIP001                              BOOL bRepRow, ScPreviewLocationData& rLocationData );
//STRIP001  void            PrintHF( long nPageNo, BOOL bHeader, long nStartY,
//STRIP001                                  BOOL bDoPrint, ScPreviewLocationData* pLocationData );

//STRIP001  long            PrintNotes( long nPageNo, long nNoteStart, BOOL bDoPrint, ScPreviewLocationData* pLocationData );
//STRIP001  long            DoNotes( long nNoteStart, BOOL bDoPrint, ScPreviewLocationData* pLocationData );

//STRIP001  void            DrawBorder( long nScrX, long nScrY, long nScrW, long nScrH,
//STRIP001                                  const SvxBoxItem* pBorderData,
//STRIP001                                  const SvxBrushItem* pBackground,
//STRIP001                                  const SvxShadowItem* pShadow );

//STRIP001  void            FillPageData();
#endif
};



} //namespace binfilter
#endif

