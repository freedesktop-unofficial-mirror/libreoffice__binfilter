/*************************************************************************
 *
 *  $RCSfile: docsh.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: vg $ $Date: 2004-12-23 10:42:13 $
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
#ifndef SC_DOCSHELL_HXX
#define SC_DOCSHELL_HXX


#ifndef _SFX_OBJSH_HXX //autogen
#include <bf_sfx2/objsh.hxx>
#endif

#ifndef _SFX_INTERNO_HXX //autogen
#include <bf_sfx2/interno.hxx>
#endif

#ifndef _SFX_OBJFAC_HXX //autogen
#include <bf_sfx2/docfac.hxx>
#endif

#ifndef _SFXVIEWSH_HXX //autogen
#include <bf_sfx2/viewsh.hxx>
#endif


#ifndef SC_SCDLL_HXX
#include "scdll.hxx"
#endif

#include "document.hxx"
#include "shellids.hxx"
#include "refreshtimer.hxx"
class FontList;
class PrintDialog;
class SfxStyleSheetBasePool;
class SfxStyleSheetHint;
class INetURLObject;
class VirtualDevice;
namespace binfilter {

class ScEditEngineDefaulter;
struct ChartSelectionInfo;

class ScPaintItem;
class ScViewData;
class ScDocFunc;
class ScPivot;
class ScDrawLayer;
class ScTabViewShell;
class ScSbxDocHelper;
class ScAutoStyleList;
class ScRange;
class ScMarkData;
class ScPaintLockData;
class ScJobSetup;
class ScChangeAction;
class ScImportOptions;
class ScDocShellModificator;

//==================================================================

//enum ScDBFormat { SC_FORMAT_SDF, SC_FORMAT_DBF };

                                    // Extra-Flags fuer Repaint
#define SC_PF_LINES         1
#define SC_PF_TESTMERGE     2

class ScDocShell: public SfxObjectShell, public SfxInPlaceObject, public SfxListener
{
    static const sal_Char __FAR_DATA pStarCalcDoc[];
    static const sal_Char __FAR_DATA pStyleName[];

    ScDocument          aDocument;

    String              aDdeTextFmt;
    String              aConvFilterName; //@ #BugId 54198

    double              nPrtToScreenFactor;
    FontList*           pFontList;
    SfxUndoManager*     pUndoManager;
    ScDocFunc*          pDocFunc;

    //SfxObjectCreateMode   eShellMode;

    BOOL                bIsInplace;         // wird von der View gesetzt
    BOOL                bHeaderOn;
    BOOL                bFooterOn;
    BOOL                bNoInformLost;
    BOOL                bIsEmpty;
    BOOL                bIsInUndo;
    BOOL                bDocumentModifiedPending;
    USHORT              nDocumentLock;
    sal_Int16           nCanUpdate;  // stores the UpdateDocMode from loading a document till update links
    BOOL                bUpdateEnabled;

    ScSbxDocHelper*     pDocHelper;

    ScAutoStyleList*    pAutoStyleList;
    ScPaintLockData*    pPaintLockData;
    ScJobSetup*         pOldJobSetup;

    VirtualDevice*      pVirtualDevice_100th_mm;

    ScDocShellModificator* pModificator; // #109979#; is used to load XML (created in BeforeXMLLoading and destroyed in AfterXMLLoading)

    String              aUserData;      // #116578# loaded manually, as no view is created

    void            InitItems();
//STRIP001  void            DoEnterHandler();
    void            InitOptions();
    void            ResetDrawObjectShell();

//STRIP001  BOOL            GetTabParam( const SfxItemSet* pArgs, USHORT nId, USHORT& rTab );
    BOOL            LoadCalc( SvStorage* pStor );
    BOOL            SaveCalc( SvStorage* pStor );
    BOOL            LoadXML( SfxMedium* pMedium, SvStorage* pStor );
    BOOL            SaveXML( SfxMedium* pMedium, SvStorage* pStor );
//STRIP001  USHORT          GetSaveTab();
    void            UpdateAllRowHeights();

    void            RemoveUnknownObjects();

//STRIP001  ULONG           DBaseImport( const String& rFullFileName, CharSet eCharSet,
//STRIP001                               BOOL bSimpleColWidth[MAXCOL+1] );
//STRIP001  ULONG           DBaseExport( const String& rFullFileName, CharSet eCharSet,
//STRIP001                               BOOL& bHasMemo );

//STRIP001  static BOOL     MoveFile( const INetURLObject& rSource, const INetURLObject& rDest );
//STRIP001  static BOOL     KillFile( const INetURLObject& rURL );
//STRIP001  static BOOL     IsDocument( const INetURLObject& rURL );

    void            LockPaint_Impl(BOOL bDoc);
    void            UnlockPaint_Impl(BOOL bDoc);
    void            LockDocument_Impl(USHORT nNew);
    void            UnlockDocument_Impl(USHORT nNew);

protected:

    virtual void SFX_NOTIFY( SfxBroadcaster& rBC, const TypeId& rBCType,
                         const SfxHint& rHint, const TypeId& rHintType );

public:
                    TYPEINFO();

                    SFX_DECL_INTERFACE(SCID_DOC_SHELL);
                    SFX_DECL_OBJECTFACTORY_DLL( ScDocShell, SC_DLL() );

                    ScDocShell( const ScDocShell& rDocShell );
                    ScDocShell( SfxObjectCreateMode eMode = SFX_CREATE_MODE_EMBEDDED );
                    ~ScDocShell();

//STRIP001  virtual void    Activate();
//STRIP001  virtual void    Deactivate();

    virtual SfxUndoManager*     GetUndoManager();

    virtual void    FillClass( SvGlobalName * pClassName,
                               ULONG * pFormat,
                               String * pAppName,
                               String * pFullTypeName,
                               String * pShortTypeName,
                               long nFileFormat = SOFFICE_FILEFORMAT_CURRENT ) const;

    virtual BOOL    InitNew( SvStorage * );
    virtual BOOL    Load( SvStorage * );
//STRIP001  virtual BOOL    LoadFrom( SvStorage * );
    virtual BOOL    ConvertFrom( SfxMedium &rMedium );
    virtual void    HandsOff();
    virtual BOOL    Save();
    virtual BOOL    SaveAs( SvStorage * pNewStor );
//STRIP001  virtual BOOL    ConvertTo( SfxMedium &rMedium );
//STRIP001  virtual USHORT  PrepareClose( BOOL bUI = TRUE, BOOL bForBrowsing = FALSE );
//STRIP001  virtual void    PrepareReload();
//STRIP001  virtual BOOL    IsInformationLost();
//STRIP001  virtual void    LoadStyles( SfxObjectShell &rSource );
//STRIP001  virtual BOOL    Insert( SfxObjectShell &rSource,
//STRIP001                              USHORT nSourceIdx1, USHORT nSourceIdx2, USHORT nSourceIdx3,
//STRIP001                              USHORT &nIdx1, USHORT &nIdx2, USHORT &nIdx3, USHORT &rIdxDeleted );

    virtual BOOL    SaveCompleted( SvStorage * pNewStor );      // SfxInPlaceObject
    virtual BOOL    DoSaveCompleted( SfxMedium * pNewStor);     // SfxObjectShell

//STRIP001  virtual void    Draw( OutputDevice *, const JobSetup & rSetup,
//STRIP001                              USHORT nAspect = ASPECT_CONTENT );

    virtual void    SetVisArea( const Rectangle & rVisArea );
    virtual Rectangle GetVisArea( USHORT nAspect ) const;

    virtual Printer* GetDocumentPrinter();

    virtual void    SetModified( BOOL = TRUE );

    void            SetVisAreaOrSize( const Rectangle& rVisArea, BOOL bModifyStart );

//STRIP001  virtual SfxDocumentInfoDialog*  CreateDocumentInfoDialog( Window *pParent,
//STRIP001                                                            const SfxItemSet &rSet );

//STRIP001  void    GetDocStat( ScDocStat& rDocStat );

    ScDocument*     GetDocument()   { return &aDocument; }
    ScDocFunc&      GetDocFunc()    { return *pDocFunc; }

    SfxPrinter*     GetPrinter();
    USHORT          SetPrinter( SfxPrinter* pNewPrinter, USHORT nDiffFlags = SFX_PRINTER_ALL );

//STRIP001  void            UpdateFontList();

//STRIP001  String          CreateObjectName( const String& rPrefix );

    ScDrawLayer*    MakeDrawLayer();

//STRIP001  void            AsciiSave( SvStream& rStream, const ScImportOptions& rOpt );

    void            GetSbxState( SfxItemSet &rSet ){DBG_BF_ASSERT(0, "STRIP");} //STRIP001 void         GetSbxState( SfxItemSet &rSet );
    void            GetDrawObjState( SfxItemSet &rSet ){DBG_BF_ASSERT(0, "STRIP");} //STRIP001 void         GetDrawObjState( SfxItemSet &rSet );

    void            Execute( SfxRequest& rReq );
    void            GetState( SfxItemSet &rSet ){DBG_BF_ASSERT(0, "STRIP");} //STRIP001 void            GetState( SfxItemSet &rSet );
//STRIP001  void            ExecutePageStyle ( SfxViewShell& rCaller, SfxRequest& rReq, USHORT nCurTab );
    void            GetStatePageStyle( SfxViewShell& rCaller, SfxItemSet& rSet, USHORT nCurTab );

//STRIP001  void            CompareDocument( ScDocument& rOtherDoc );
//STRIP001  void            MergeDocument( ScDocument& rOtherDoc );

//STRIP001  ScChangeAction* GetChangeAction( const ScAddress& rPos );
//STRIP001  void            SetChangeComment( ScChangeAction* pAction, const String& rComment );
//STRIP001  void            ExecuteChangeCommentDialog( ScChangeAction* pAction, Window* pParent,BOOL bPrevNext=TRUE );
                    /// Protect/unprotect ChangeTrack and return <TRUE/> if
                    /// protection was successfully changed.
                    /// If bJustQueryIfProtected==TRUE protection is not
                    /// changed and <TRUE/> is returned if not protected or
                    /// password was entered correctly.
//STRIP001     BOOL            ExecuteChangeProtectionDialog( BOOL bJustQueryIfProtected = FALSE );

//STRIP001  void            SetPrintZoom( USHORT nTab, USHORT nScale, USHORT nPages );
//STRIP001  BOOL            AdjustPrintZoom( const ScRange& rRange );

    void            LoadStylesArgs( ScDocShell& rSource, BOOL bReplace, BOOL bCellStyles, BOOL bPageStyles );

    void            PageStyleModified( const String& rStyleName, BOOL bApi );

    void            NotifyStyle( const SfxStyleSheetHint& rHint );
//STRIP001  void            DoAutoStyle( const ScRange& rRange, const String& rStyle );

    Window*         GetDialogParent();
    void            ErrorMessage( USHORT nGlobStrId );
    BOOL            IsEditable() const;

    BOOL            AdjustRowHeight( USHORT nStartRow, USHORT nEndRow, USHORT nTab );

//STRIP001  void            PivotUpdate( ScPivot* pOldPivot, ScPivot* pNewPivot,
//STRIP001                                  BOOL bRecord = TRUE, BOOL bApi = FALSE );
//STRIP001  void            RefreshPivotTables( const ScRange& rSource );
    void            DoConsolidate( const ScConsolidateParam& rParam, BOOL bRecord = TRUE );
    void            UseScenario( USHORT nTab, const String& rName, BOOL bRecord = TRUE );
    USHORT          MakeScenario( USHORT nTab, const String& rName, const String& rComment,
                                    const Color& rColor, USHORT nFlags,
                                    ScMarkData& rMark, BOOL bRecord = TRUE );
    void            ModifyScenario( USHORT nTab, const String& rName, const String& rComment,
                                    const Color& rColor, USHORT nFlags );
    BOOL            MoveTable( USHORT nSrcTab, USHORT nDestTab, BOOL bCopy, BOOL bRecord );

    void            DoRecalc( BOOL bApi );
    void            DoHardRecalc( BOOL bApi );

//STRIP001  void            PreparePrint( PrintDialog* pPrintDialog, ScMarkData* pMarkData );
//STRIP001  void            Print( SfxProgress& rProgress, PrintDialog* pPrintDialog,
//STRIP001                          ScMarkData* pMarkData, Window* pDialogParent,
//STRIP001                          BOOL bForceSelected );

//STRIP001  void            UpdateOle( const ScViewData* pViewData, BOOL bSnapSize = FALSE );
    BOOL            IsOle();

    void            DBAreaDeleted( USHORT nTab, USHORT nX1, USHORT nY1, USHORT nX2, USHORT nY2 );
    ScDBData*       GetDBData( const ScRange& rMarked, ScGetDBMode eMode, BOOL bForceMark );

    void            UpdateLinks();          // Link-Eintraege aktuallisieren
    BOOL            ReloadTabLinks();       // Links ausfuehren (Inhalt aktualisieren)

//STRIP001  void            PostEditView( ScEditEngineDefaulter* pEditEngine, const ScAddress& rCursorPos );

    void            PostPaint( USHORT nStartCol, USHORT nStartRow, USHORT nStartTab,
                            USHORT nEndCol, USHORT nEndRow, USHORT nEndTab, USHORT nPart,
                            USHORT nExtFlags = 0 );
    void            PostPaint( const ScRange& rRange, USHORT nPart, USHORT nExtFlags = 0 );

    void            PostPaintCell( USHORT nCol, USHORT nRow, USHORT nTab );
    void            PostPaintGridAll();
    void            PostPaintExtras();

    void            PostDataChanged();

    void            SetDocumentModified( BOOL bIsModified = TRUE );
    void            SetDrawModified( BOOL bIsModified = TRUE );

    void            LockPaint();
    void            UnlockPaint();
    USHORT          GetLockCount() const;
    void            SetLockCount(USHORT nNew);

    void            LockDocument();
    void            UnlockDocument();

//STRIP001  DECL_LINK( ChartSelectionHdl, ChartSelectionInfo* );

    virtual SfxStyleSheetBasePool*  GetStyleSheetPool();

//STRIP001  void            SetInplace( BOOL bInplace );
    BOOL            IsEmpty() const;
    void            ResetEmpty();

    BOOL            IsInUndo() const                { return bIsInUndo; }
//STRIP001  void            SetInUndo(BOOL bSet);

    void            CalcOutputFactor();
    double          GetOutputFactor() const;
//STRIP001  void            GetPageOnFromPageStyleSet( const SfxItemSet* pStyleSet,
//STRIP001                                             USHORT            nCurTab,
//STRIP001                                             BOOL&             rbHeader,
//STRIP001                                             BOOL&             rbFooter );

//STRIP001  virtual long DdeGetData( const String& rItem, const String& rMimeType,
//STRIP001                              ::com::sun::star::uno::Any & rValue );
//STRIP001  virtual long DdeSetData( const String& rItem, const String& rMimeType,
//STRIP001                              const ::com::sun::star::uno::Any & rValue );
//STRIP001  virtual ::so3::SvLinkSource* DdeCreateLinkSource( const String& rItem );

    const String& GetDdeTextFmt() const { return aDdeTextFmt; }

    SfxBindings*    GetViewBindings();

    ScTabViewShell* GetBestViewShell();
    ScSbxDocHelper* GetDocHelperObject() { return pDocHelper; }

    void            SetDocumentModifiedPending( BOOL bVal )
                        { bDocumentModifiedPending = bVal; }
    BOOL            IsDocumentModifiedPending() const
                        { return bDocumentModifiedPending; }

    BOOL            IsUpdateEnabled() const
                        { return bUpdateEnabled; }
    void            SetUpdateEnabled(BOOL bValue)
                        { bUpdateEnabled = bValue; }

    VirtualDevice*  GetVirtualDevice_100th_mm();

    static ScViewData* GetViewData();
    static USHORT      GetCurTab();

//STRIP001  static ScDocShell* GetShellByNum( USHORT nDocNo );
    static String   GetOwnFilterName();
    static String   GetWebQueryFilterName();
    static String   GetAsciiFilterName();
    static String   GetLotusFilterName();
    static String   GetDBaseFilterName();
    static String   GetDifFilterName();
    static BOOL     HasAutomaticTableName( const String& rFilter );

    DECL_LINK( RefreshDBDataHdl, ScDBData* );

    void            BeforeXMLLoading();
    void            AfterXMLLoading(sal_Bool bRet);

    const String&   GetUserData() const { return aUserData; }   // #116578#
};

SO2_DECL_REF(ScDocShell)
SO2_IMPL_REF(ScDocShell)


// Vor Modifizierungen des Dokuments anlegen und danach zerstoeren.
// Merkt sich im Ctor AutoCalcShellDisabled und IdleDisabled, schaltet sie ab
// und stellt sie im Dtor wieder her, AutoCalcShellDisabled ggbf. auch vor
// einem ScDocShell SetDocumentModified.
// SetDocumentModified hierdran aufrufen statt an der ScDocShell.
// Im Dtor wird wenn ScDocShell bDocumentModifiedPending gesetzt ist und
// bAutoCalcShellDisabled nicht gesetzt ist ein SetDocumentModified gerufen.
class ScDocShellModificator
{
            ScDocShell&     rDocShell;
    ScRefreshTimerProtector aProtector;
            BOOL            bAutoCalcShellDisabled;
            BOOL            bIdleDisabled;

                            // not implemented
                            ScDocShellModificator( const ScDocShellModificator& );
    ScDocShellModificator&  operator=( const ScDocShellModificator& );

public:
                            ScDocShellModificator( ScDocShell& );
                            ~ScDocShellModificator();
            void            SetDocumentModified();
};



} //namespace binfilter
#endif


