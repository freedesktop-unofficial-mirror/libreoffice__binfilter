/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: objsh.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 03:05:14 $
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
#ifndef _SFX_OBJSH_HXX
#define _SFX_OBJSH_HXX

//________________________________________________________________________________________________________________
//  include uno header first!
//________________________________________________________________________________________________________________

#ifndef _COM_SUN_STAR_FRAME_XFRAME_HPP_
#include <com/sun/star/frame/XFrame.hpp>
#endif
#ifndef _COM_SUN_STAR_UNO_REFERENCE_H_
#include <com/sun/star/uno/Reference.h>
#endif
#ifndef _COM_SUN_STAR_UNO_SEQUENCE_HXX_
#include <com/sun/star/uno/Sequence.hxx>
#endif
#ifndef _COM_SUN_STAR_SCRIPT_XLIBRARYCONTAINER_HPP_
#include <com/sun/star/script/XLibraryContainer.hpp>
#endif

//________________________________________________________________________________________________________________
//  include something else
//________________________________________________________________________________________________________________

#if _SOLAR__PRIVATE
#ifndef _TIMER_HXX //autogen
#include <vcl/timer.hxx>
#endif
#endif
#ifndef _SFXPOOLITEM_HXX //autogen
#include <svtools/poolitem.hxx>
#endif
#ifndef _SO2DEFS_HXX //autogen
#include <so3/so2defs.hxx>
#endif
#ifndef _PERSIST_HXX //autogen
#include <so3/persist.hxx>
#endif
#ifndef _TIMER_HXX //autogen
#include <vcl/timer.hxx>
#endif
#ifndef _SV_BITMAP_HXX
#include <vcl/bitmap.hxx>
#endif
#include <so3/svstor.hxx>

#ifndef _RSCSFX_HXX //autogen
#include <rsc/rscsfx.hxx>
#endif

#include <bf_sfx2/shell.hxx>

#ifndef _COM_SUN_STAR_FRAME_XMODEL_HPP_
#include <com/sun/star/frame/XModel.hpp>
#endif
namespace so3 {
 class SvLinkSource;
};
class SbxValue;
class SvxMacro;
class SbxArray;
class BasicManager;
class SfxStyleSheetBasePool;
class SfxStyleSheetPool;
class SbMethod;
class StarBASIC;
class Printer;
class SvKeyValueIterator;
class SvPseudoObject;
class SvEmbeddedInfoObject;
class SvEmbeddedObject;
class GDIMetaFile;
class Bitmap;
class INetURLObject;
namespace binfilter {


class SfxMedium;
class SfxInPlaceObject;
class SfxObjectFactory;
class SfxDocumentInfo;
class SfxDocumentInfoDialog;
class SfxEventConfigItem_Impl;
class INote;
class SfxFrame;
class SfxConfigManager;
class SfxBaseModel;
class SfxModule;
class SvData;
class SfxProgress;
class IndexBitSet;
class SfxTopFrame;
class SfxAcceleratorManager;
class SfxMenuBarManager;

//STRIP008 namespace so3 {
//STRIP008 class SvLinkSource;
//STRIP008 };

typedef sal_uInt32 SfxObjectShellFlags;
#define SFXOBJECTSHELL_HASOPENDOC      0x01L
#define SFXOBJECTSHELL_DONTREPLACE     0x02L
#define SFXOBJECTSHELL_HASMENU         0x04L
#define SFXOBJECTSHELL_DONTLOADFILTERS 0x08L
#define SFXOBJECTSHELL_DONTCLOSE       0x10L
#define SFXOBJECTSHELL_NODOCINFO       0x20L
#define SFXOBJECTSHELL_STD_NORMAL      ( SFXOBJECTSHELL_HASOPENDOC )
#define SFXOBJECTSHELL_STD_SPECIAL     ( SFXOBJECTSHELL_DONTLOADFILTERS )
#define SFXOBJECTSHELL_UNDEFINED       0xf000000

//--------------------------------------------------------------------

#define SFX_TITLE_TITLE    0
#define SFX_TITLE_FILENAME 1
#define SFX_TITLE_FULLNAME 2
#define SFX_TITLE_APINAME  3
#define SFX_TITLE_DETECT   4
#define SFX_TITLE_CAPTION  5
#define SFX_TITLE_PICKLIST 6
#define SFX_TITLE_HISTORY  7
#define SFX_TITLE_MAXLEN   10   // ab hier sind das L"angenbegrenzungen

#define SFX_LOADED_MAINDOCUMENT 1
#define SFX_LOADED_IMAGES       2
#define SFX_LOADED_ALL          3

//--------------------------------------------------------------------

#define SEQUENCE                ::com::sun::star::uno::Sequence
#define OUSTRING                ::rtl::OUString

//--------------------------------------------------------------------

DECLARE_TABLE( SfxEventListTable, String* )

//--------------------------------------------------------------------

enum SfxObjectCreateMode
{
    SFX_CREATE_MODE_EMBEDDED,
    SFX_CREATE_MODE_STANDARD,
    SFX_CREATE_MODE_PREVIEW,
    SFX_CREATE_MODE_ORGANIZER,
    SFX_CREATE_MODE_PLUGIN,
    SFX_CREATE_MODE_INTERNAL
};

/*====================================================================

Die Klasse SfxObjectShell ist die Basisklasse f"ur SFx-Objekte, also
f"ur Dokumente und Teile von Dokumenten, die als selbst"andige Objekte
in fremde Objekte integriert werden k"onnen.

----------------------------------------------------------------------*/

enum SfxTitleQuery
{
    SFX_TITLE_QUERY_SAVE_NAME_PROPOSAL
};

class SfxImageManager;
class SfxToolBoxConfig;

class SfxObjectShell: public SfxShell, virtual public SvPersist
{
friend struct ModifyBlocker_Impl;
friend class SfxDocumentManager;
friend class SFX_OBJECTSHELL_FRIEND;

    struct SfxObjectShell_Impl* pImp;               // interne Daten

    SfxMedium *                 pMedium;            // Beschreibung der Datei bzw. des Storage, in dem sich das Objekt befindet
    SfxStyleSheetBasePool*      pStyleSheetPool;    // StyleSheets
    SfxObjectCreateMode         eCreateMode;        // Zweck des Objekts
    sal_uInt16                  nViewNo;            // Numerierung der MDIWins
    sal_Bool                    bHasName :1,        // sal_True := bestehendes Objekt, sal_False := es ist ein neues Objekt
                                bIsTmp :1;          // temp. Storage

private:
#if _SOLAR__PRIVATE
    void                        Construct_Impl();
    SfxDocumentInfo&            UpdateTime_Impl(SfxDocumentInfo &);
    sal_Bool                    MakeBackup_Impl(const String &rName,
                                                sal_Bool bCopyAllways = sal_False);
    void                        SetEAs_Impl( SfxMedium &rMedium );
    sal_Bool                    SaveTo_Impl(SfxMedium &rMedium, const SfxItemSet* pSet, BOOL bPrepareForDirectAccess );
    sal_Bool                    ConnectTmpStorage_Impl( SvStorage* pStg);
    sal_Bool                    IsOwnStorageFormat_Impl(const SfxMedium &) const;
    sal_Bool                    SaveInfoAndConfig_Impl( SvStorageRef pNewStg );
#endif

protected:
                                SfxObjectShell(SfxObjectCreateMode);
    virtual                     ~SfxObjectShell();

    virtual void                ModifyChanged();
    virtual sal_Bool            Close();

#if _SOLAR__PRIVATE
    void                        StartLoading_Impl();
#endif

    // add optional to the storage the XML format as a zip stream
    void                        AddXMLAsZipToTheStorage( SvStorage& rRoot );

public:
                                TYPEINFO();
                                SFX_DECL_INTERFACE(SFX_INTERFACE_SFXDOCSH);

    SfxObjectFactory*           _pFactory;          // um im Dtor daranzukommen

    /* Stampit #111050# allow writer to set this event id here hardly!
       Please replace ith by a better solution! */
    void                        Stamp_SetActivateEvent(sal_uInt16);

    // Document-Shell Iterator
    static SfxObjectShell*      GetFirst( const TypeId* pType = 0,
                                          sal_Bool bOnlyVisible = sal_True );
    static SfxObjectShell*      GetNext( const SfxObjectShell& rPrev,
                                         const TypeId* pType = 0,
                                         sal_Bool bOnlyVisible = sal_True );
    static SfxObjectShell*      Current();
    static sal_uInt16               Count();
    static SfxObjectShell*      GetWorkingDocument();
    static void                 SetWorkingDocument( SfxObjectShell* pDoc );

    virtual void                Invalidate(USHORT nId = 0);

    void                        SetFlags( SfxObjectShellFlags eFlags );
    SfxObjectShellFlags         GetFlags( ) const ;

    SfxModule*                  GetModule() const;

    virtual SfxObjectFactory&   GetFactory() const;
    SfxInPlaceObject*           GetInPlaceObject() const;
    SfxMedium *                 GetMedium() const { return pMedium; }
    void                        ForgetMedium() { pMedium = 0; }
    SfxDocumentInfo&            GetDocInfo();
    void                        UpdateDocInfoForSave(  );
    void                        FlushDocInfo();
    sal_Bool                    HasName() const { return bHasName; }
    virtual String              GetAPIName() const;
    void                        SetHasName( sal_Bool bSet = sal_True ) { bHasName = bSet; }
    sal_Bool                    IsReadOnly() const;
    sal_Bool                    IsReadOnlyMedium() const;
    sal_Bool                    IsReadOnlyUI() const;
    void                        SetNoName();
    sal_Bool                    IsInModalMode() const;
    sal_Bool                    HasModalViews() const;
    sal_Bool                    IsInPrepareClose() const;
    sal_Bool                    IsHelpDocument() const;
#if _SOLAR__PRIVATE
    void                        SetMacroMode_Impl(sal_Bool bModal=sal_True);
#endif

    void                        ResetError();
    sal_uInt32                  GetError() const;
    sal_uInt32                  GetErrorCode() const;
    void                        SetError(sal_uInt32 rErr);

    virtual sal_Bool            LoadOwnFormat( SfxMedium& pMedium );
    virtual sal_Bool            SaveAsOwnFormat( SfxMedium& pMedium );

    virtual sal_Bool            DoInitNew( SvStorage * pStor );
    virtual void                DoHandsOff();
    void                        DoHandsOffNoMediumClose();
    virtual sal_Bool            DoLoad( SvStorage * pStor );

    virtual sal_Bool            DoLoad( const String& rFileName,
                                        StreamMode nStreamMode,
                                        StorageMode nStorageMode );

    virtual sal_Bool            DoLoad( SfxMedium * pMedium );
    virtual sal_Bool            DoSave();
    sal_Bool                    DoSaveAs( SfxMedium &rNewStor );
    virtual sal_Bool            DoSaveAs( SvStorage * pNewStor );
    virtual sal_Bool            DoSaveCompleted( SvStorage * pNewStor = NULL );
    virtual sal_Bool            DoSaveCompleted( SfxMedium * pNewStor);

    virtual sal_Bool            ConvertFrom( SfxMedium &rMedium );
    sal_Bool                    ImportFrom( SfxMedium &rMedium );
    sal_Bool                    ExportTo( SfxMedium &rMedium );
    virtual sal_Bool            ConvertTo( SfxMedium &rMedium );

    virtual String              QueryTitle( SfxTitleQuery ) const;

    sal_Bool                    IsBasic( const String & rCode, SbxObject * pVCtrl = NULL );

    ErrCode                     CallBasic( const String& rMacro, const String& rBasicName,
                                    SbxObject* pVCtrl, SbxArray* pArgs = 0, SbxValue* pRet = 0 );
    ErrCode                     Call( const String & rCode, sal_Bool bIsBasicReturn, SbxObject * pVCtrl = NULL );

    ErrCode                     CallScript(
        const String & rScriptType, const String & rCode, ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface >  & rSource,
        void* pArgs = NULL, void* pRet = NULL );

    /** calls a StarBasic script without magic
    @param _rMacroName
        specifies the name of the method to execute
    @param _rLocation
        specifies the location of the script to execute. Allowed values are "application" and "document".
    @param _pArguments
        This is a pointer to a Sequence< Any >. All elements of the Sequence are wrapped into Basic objects
        and passed as arguments to the method specified by <arg>_rMacroName</arg>
    @param _pReturn
        If not <NULL/>, the Any pointed to by this argument contains the return value of the (synchronous) call
        to the StarBasic macro
    */
    ErrCode                     CallStarBasicScript(
        const String& _rMacroName,
        const String& _rLocation,
        void* _pArguments = NULL,
        void* _pReturn = NULL
    );

    BOOL                        DoMacroQuery( const String& rScriptType );
    void                        AdjustMacroMode( const String& rScriptType );

    SvKeyValueIterator*         GetHeaderAttributes();
    void                        ClearHeaderAttributesForSourceViewHack();
    void                        SetHeaderAttributesForSourceViewHack();
    SbMethod*                   GetMethod_Impl( const String& rMacro );

    SvEmbeddedInfoObject*       InsertObject( SvEmbeddedObject * pObj,
                                              const String & rName );

    SfxConfigManager*           GetConfigManager( BOOL bCreate = FALSE );
    void                        SetConfigManager(SfxConfigManager *pMgr);
    sal_Bool                    HasTemplateConfig() const;

    sal_Bool                    IsTemplate() const;
    void                        SetTemplate(sal_Bool bIs);

    static sal_uInt32           HandleFilter( SfxMedium* pMedium, SfxObjectShell* pDoc );

    virtual sal_Bool            LoadFrom( SvStorage * pStor );
    virtual void                ViewAssigned();
    virtual sal_uInt16          PrepareClose( sal_Bool bUI = sal_True, sal_Bool bForBrowsing = sal_False );
    virtual sal_Bool            IsInformationLost();
    virtual sal_Bool            Save();
    virtual sal_Bool            SaveAs( SvStorage * pNewStg );
    virtual Size                GetFirstPageSize();
    virtual sal_Bool            DoClose();
    virtual void                PrepareReload();
    virtual GDIMetaFile*        GetPreviewMetaFile( sal_Bool bFullContent = sal_False ) const;
    virtual void                CancelTransfers();
    // Transfer IFace
    void                        AbortImport();
    sal_Bool                    IsAbortingImport() const;
    void                        RegisterTransfer( SfxMedium& rMedium );
    sal_Bool                    IsReloading() const;
    void                        FinishedLoading( sal_uInt16 nWhich = SFX_LOADED_ALL );
    sal_Bool                    IsLoading() const;
    void                        SetAutoLoad( const INetURLObject&, sal_uInt32 nTime, sal_Bool bReload = sal_True );
    void                        LockAutoLoad( sal_Bool bLock );
    sal_Bool                    IsAutoLoadLocked() const;
    void                        NotifyReloadAvailable();
    sal_Bool                    IsSecure();

    // Misc
    sal_Bool                    IsPreview() const;
    SfxObjectCreateMode         GetCreateMode() const { return eCreateMode; }
    virtual void                MemoryError();
    SfxProgress*                GetProgress() const;
    void                        SetWaitCursor( BOOL bSet ) const;

//(mba)    virtual SotObjectRef        CreateAggObj( const SotFactory* pFact );

    // Naming Interface
    void                        SetTitle( const String& rTitle );
    String                      GetTitle( sal_uInt16 nMaxLen = 0 ) const;
    void                        InvalidateName();   // Zuruecksetzen auf unbenannt
#if _SOLAR__PRIVATE
    void                        SetLastMark_Impl( const String & );
    const String&               GetLastMark_Impl() const;
    sal_Bool                    DoInitNew_Impl( const String& rName );
#endif

    // DDE-Interface
    virtual long                DdeExecute( const String& rCmd );
    virtual long                DdeGetData( const String& rItem,
                                            const String& rMimeType,
                                        ::com::sun::star::uno::Any & rValue );
    virtual long                DdeSetData( const String& rItem,
                                            const String& rMimeType,
                                const ::com::sun::star::uno::Any & rValue );
    virtual ::so3::SvLinkSource* DdeCreateLinkSource( const String& rItem );

    // Contents
    virtual SfxStyleSheetBasePool*  GetStyleSheetPool();
    void                            SetStyleSheetPool( SfxStyleSheetBasePool *pPool ) {
                                        pStyleSheetPool = pPool; }

    //determine the position of the "Automatic" filter in the stylist
    void                        SetAutoStyleFilterIndex(sal_uInt16 nSet);
    virtual sal_Bool            HasBasic() const;
    BasicManager*               GetBasicManager() const;
    ::com::sun::star::uno::Reference< ::com::sun::star::script::XLibraryContainer >
                                GetBasicContainer();
    StarBASIC*                  GetBasic() const;

    // Interface Dok-Inhalte, Organizer
#define INDEX_IGNORE USHRT_MAX

#define CONTENT_STYLE 0
#define CONTENT_CONFIG 1
#define CONTENT_MACRO 2
#define DEF_CONTENT_COUNT 1


    virtual sal_uInt16          GetContentCount(
                                        sal_uInt16 nIdx1 = INDEX_IGNORE,
                                        sal_uInt16 nIdx2 = INDEX_IGNORE );
    virtual void                GetContent( String &,
                                        Bitmap &rClosedBitmap,
                                        Bitmap &rOpenedBitmap,
                                        sal_Bool   &bCanDelete,
                                        sal_uInt16 nPos,
                                        sal_uInt16 nIdx1,
                                        sal_uInt16 nIdx2 = INDEX_IGNORE );

    virtual void                GetContent( String &,
                                        Bitmap &rClosedBitmap,
                                        Bitmap &rOpenedBitmap,
                                        BmpColorMode eColorMode,
                                        sal_Bool   &bCanDelete,
                                        sal_uInt16 nPos,
                                        sal_uInt16 nIdx1,
                                        sal_uInt16 nIdx2 = INDEX_IGNORE );






    virtual void                LoadStyles( SfxObjectShell &rSource );
    void                        ReadNote( INote * );
    void                        UpdateNote( INote * );

                                // F"ur Docs, die zum Formatieren die Viewgr"o\se
                                // ben"otigen
    Size                        GetActualSize() const;
    void                        SetActualSize( const Size& rSize );
    sal_Bool                    IsInFrame() const;
    void                        SetInFrame( sal_Bool );
    virtual SfxObjectShell*     GetObjectShell();
    void                        SetBaseURL( const String& rURL );
    const String&               GetBaseURL() const;

    virtual SfxFrame*           GetSmartSelf( SfxFrame* pSelf, SfxMedium& rMedium );

    void                        SetModel( SfxBaseModel* pModel );
    ::com::sun::star::uno::Reference< ::com::sun::star::frame::XModel > GetModel();
    // Nur uebergangsweise fuer die Applikationen !!!
    void                        SetBaseModel( SfxBaseModel* pModel );
    ::com::sun::star::uno::Reference< ::com::sun::star::frame::XModel > GetBaseModel();
    // Nur uebergangsweise fuer die Applikationen !!!

    virtual SEQUENCE< OUSTRING >    GetEventNames();
    SotStorageStreamRef         GetConfigurationStream( const String& rName, BOOL bCreate=FALSE );
    SvStorageRef                GetConfigurationStorage( SotStorage* pStor=NULL );

    String                      UpdateTitle( SfxMedium* pMed=NULL, USHORT nDocViewNo=0 );

#if _SOLAR__PRIVATE
    static SEQUENCE< OUSTRING > GetEventNames_Impl();
    void                        InitBasicManager_Impl( SvStorage *pStor, const String* pName = NULL );
    SfxObjectShell_Impl*        Get_Impl() { return pImp; }
    const SfxObjectShell_Impl*  Get_Impl() const { return pImp; }


    // Shell Interface
    void                        ExecFile_Impl(SfxRequest &);
    void                        GetState_Impl(SfxItemSet&);
    void                        PrintExec_Impl(SfxRequest &);
    void                        PrintState_Impl(SfxItemSet&);
    void                        ExecProps_Impl(SfxRequest &);
    void                        StateProps_Impl(SfxItemSet &);
    void                        ExecView_Impl(SfxRequest &);
    void                        StateView_Impl(SfxItemSet &);

    // Laden-speichern public internals
    void                        PositionView_Impl();
    void                        UpdateFromTemplate_Impl();
    void                        Reload_Impl();
    sal_Bool                    CanReload_Impl();
    void                        SetNamedVisibility_Impl();
    sal_Bool                    DoSave_Impl( const SfxItemSet* pSet=0 );
    sal_Bool                    Save_Impl( const SfxItemSet* pSet=0 );
    void                        UpdatePickList_Impl();
    sal_Bool                    PreDoSaveAs_Impl(const String &rFileName, const String &rFiltName, SfxItemSet *);
    sal_Bool                    APISaveAs_Impl ( const String& aFileName, SfxItemSet* aParams );
    sal_Bool                    CommonSaveAs_Impl ( const INetURLObject& aURL, const String& aFilterName, SfxItemSet* aParams );

    // public-internals
    IndexBitSet&                GetNoSet_Impl();
    void                        SetProgress_Impl( SfxProgress *pProgress );
    sal_uInt16&                 GetAktViewNo() { return nViewNo; }
    void                        PostActivateEvent_Impl();
    void                        SetActivateEvent_Impl(sal_uInt16 );
    FASTBOOL                    SaveWindows_Impl( SvStorage &rStor ) const;
    SfxViewFrame*               LoadWindows_Impl( SfxTopFrame *pPrefered = 0 );

    // configuration items
    SfxEventConfigItem_Impl*    GetEventConfig_Impl( sal_Bool bForce=sal_False );
    SfxAcceleratorManager*      GetAccMgr_Impl();
    SfxMenuBarManager*          CreateMenuBarManager_Impl( SfxViewFrame* );
    SfxImageManager*            GetImageManager_Impl();
    SfxToolBoxConfig*           GetToolBoxConfig_Impl();
#endif
};

#if _SOLAR__PRIVATE
    struct ModifyBlocker_Impl
    {
        SfxObjectShell* pPersist;
        sal_Bool bWasEnabled;
        ModifyBlocker_Impl( SfxObjectShell* pPersistP ) : pPersist( pPersistP )
        {
            bWasEnabled = pPersistP->IsEnableSetModified();
            if ( bWasEnabled )
                pPersistP->EnableSetModified( sal_False );
        }
        ~ModifyBlocker_Impl()
        {
            if ( bWasEnabled )
                pPersist->EnableSetModified( bWasEnabled );
        }
    };
#endif

//--------------------------------------------------------------------

#ifndef SFX_DECL_OBJECTSHELL_DEFINED
#define SFX_DECL_OBJECTSHELL_DEFINED
SV_DECL_REF(SfxObjectShell)
SV_DECL_LOCK(SfxObjectShell)
#endif
SV_IMPL_REF(SfxObjectShell)
SV_IMPL_LOCK(SfxObjectShell)

SfxObjectShellRef MakeObjectShellForOrganizer_Impl( const String& rName, BOOL bWriting );

#if _SOLAR__PRIVATE
//--------------------------------------------------------------------
class AutoReloadTimer_Impl : public Timer
{
    String          aUrl;
    sal_Bool            bReload;
    SfxObjectShell*   pObjSh;

public:
    AutoReloadTimer_Impl( const String& rURL, sal_uInt32 nTime, sal_Bool bReloadP,
                          SfxObjectShell* pSh );
    virtual void Timeout();
};
#endif

//-------------------------------------------------------------------------

class SfxObjectShellItem: public SfxPoolItem
{
    SfxObjectShell*         pObjSh;

public:
                            TYPEINFO();
                            SfxObjectShellItem( SfxObjectShell *pObjShell ):
                                SfxPoolItem( 0 ),
                                pObjSh( pObjShell )
                            {}
                            SfxObjectShellItem( sal_uInt16 nWhich,
                                                SfxObjectShell *pObjShell ):
                                SfxPoolItem( nWhich ),
                                pObjSh( pObjShell )
                            {}

    virtual int             operator==( const SfxPoolItem& ) const;
    virtual String          GetValueText() const;
    virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;
    SfxObjectShell*         GetObjectShell() const
                            { return pObjSh; }
};

}//end of namespace binfilter
#endif

