/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: docsh.hxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: obo $ $Date: 2007-07-17 12:57:04 $
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
#ifndef _SWDOCSH_HXX
#define _SWDOCSH_HXX

#ifndef _TIMER_HXX //autogen
#include <vcl/timer.hxx>
#endif
#ifndef _SFX_OBJFAC_HXX //autogen
#include <bf_sfx2/docfac.hxx>
#endif
#ifndef _SFX_INTERNO_HXX //autogen
#include <bf_sfx2/interno.hxx>
#endif
#ifndef _SFX_OBJSH_HXX //autogen
#include <bf_sfx2/objsh.hxx>
#endif
#ifndef SW_SWDLL_HXX
#include <swdll.hxx>
#endif
#ifndef _SHELLID_HXX
#include <shellid.hxx>
#endif

#include <svtools/lstner.hxx>

class   SfxStyleSheetBasePool;
class   FontList;
class   PushButton;
class   FixedText;

namespace binfilter {

class   SwDoc;
class   Sw3Io;
class   SfxDocumentInfoDialog;
class   SwView;
class   SwWrtShell;
class   SwFEShell;
class   Reader;
class   SwReader;
class   SwCrsrShell;
class   SwSrcView;
class   SwPaM;
class   SwgReaderOption;

class SwDocShell: public SfxObjectShell, public SfxInPlaceObject,
                  public SfxListener
{
    SwDoc*                  pDoc;           // Document
    Sw3Io*                  pIo;            // Reader / Writer
    SfxStyleSheetBasePool*  pBasePool;      // Durchreiche fuer Formate
    FontList*               pFontList;      // aktuelle FontListe

    // Nix geht ohne die WrtShell (historische Gruende)
    // RuekwaertsPointer auf die View (historische Gruende)
    // Dieser gilt solange bis im Activate ein neuer gesetzt wird
    // oder dieser im Dtor der View geloescht wird
    //
    SwView*                 pView;
    SwWrtShell*             pWrtShell;

    Timer                   aFinishedTimer; // Timer fuers ueberpriefen der
                                            // Grafik-Links. Sind alle da,
                                            // dann ist Doc voll. geladen

    SvPersistRef            xOLEChildList;  // fuers RemoveOLEObjects
    sal_Int16               nUpdateDocMode; // contains the ::com::sun::star::document::UpdateDocMode

    // Methoden fuer den Zugriff aufs Doc
    void                    AddLink();
    void                    RemoveLink();

    // Hint abfangen fuer DocInfo
    virtual void            Notify( SfxBroadcaster& rBC, const SfxHint& rHint );

    // FileIO
    virtual BOOL            InitNew(SvStorage* pNewStor);
    virtual BOOL            Load(SvStorage* pStor);
    virtual BOOL            LoadFrom(SvStorage* pStor);
    virtual BOOL            ConvertFrom( SfxMedium &rMedium );
    virtual void            HandsOff();
    virtual BOOL            SaveAs(SvStorage * pNewStor );
    virtual BOOL            SaveCompleted(SvStorage * pNewStor );

    // DocInfo dem Doc melden
    //
    // OLE-Geraffel

    // Methoden fuer StyleSheets

    void                    InitDraw();
    void                    SubInitNew();   // fuer InitNew und HtmlSourceModus
    inline void             SetWrtShell(SwWrtShell* pShell)
                                { pWrtShell = pShell; }

    void                    RemoveOLEObjects();
    void                    CalcLayoutForOLEObjects();

    void                    Init_Impl();
    DECL_STATIC_LINK( SwDocShell, IsLoadFinished, void* );

public:

    // aber selbst implementieren
    SFX_DECL_OBJECTFACTORY_DLL(SwDocShell, SW_DLL());
    TYPEINFO();

    //Das Doc wird fuer SO-Datenaustausch benoetigt!
    SwDocShell(SfxObjectCreateMode eMode = SFX_CREATE_MODE_EMBEDDED);
    SwDocShell( SwDoc *pDoc, SfxObjectCreateMode eMode = SFX_CREATE_MODE_STANDARD );
    ~SwDocShell();

    // OLE 2.0-Benachrichtigung
    DECL_LINK( Ole2ModifiedHdl, void * );

    // OLE-Geraffel
    virtual void      SetVisArea( const Rectangle &rRect );
    virtual Rectangle GetVisArea( USHORT nAspect ) const;
    virtual Printer  *GetDocumentPrinter();
    virtual OutputDevice* GetDocumentRefDev();
    virtual void      OnDocumentPrinterChanged( Printer * pNewPrinter );
    virtual ULONG     GetMiscStatus() const;

    virtual void            SetModified( BOOL = TRUE );

    // Doc rausreichen aber VORSICHT
    inline SwDoc*           GetDoc() { return pDoc; }
    void                    UpdateFontList();
    void                    UpdateChildWindows();

    // DocumentInfo neu setzen

    // globaler IO
    virtual BOOL            Save();
    inline BOOL                 SaveAsChilds( SvStorage *pStor );
    inline BOOL                 SaveCompletedChilds( SvStorage *pStor );

    // fuer VorlagenPI
    virtual SfxStyleSheetBasePool*  GetStyleSheetPool();

    // Fuer Organizer



    const SwView *GetView() const { return pView; }
    SwView       *GetView()       { return pView; }

    // Zugriff auf die zur SwView gehoerige SwWrtShell
          SwWrtShell *GetWrtShell()       { return pWrtShell; }
    const SwWrtShell *GetWrtShell() const { return pWrtShell; }

    // fuer die Core - die kennt die DocShell aber keine WrtShell!
    const SwFEShell *GetFEShell() const
                { return ((SwDocShell*)this)->GetFEShell(); }


    // Fuer Einfuegen Dokument
    Reader* StartConvertFrom(SfxMedium& rMedium, SwReader** ppRdr,
                        SwCrsrShell* pCrsrSh = 0, SwPaM* pPaM = 0);

    // Anforderung der pIo-Struktur fuer den Zugriff auf Substorages
    // und Streams
    Sw3Io* GetIoSystem() { return pIo; }

    virtual void FillClass( SvGlobalName * pClassName,
                                   ULONG * pClipFormat,
                                   String * pAppName,
                                   String * pLongUserName,
                                   String * pUserName,
                                   long nVersion = SOFFICE_FILEFORMAT_CURRENT ) const;


    // Seitenvorlagedialog anzeigen, ggf. auf Spaltenpage

    // Timer starten fuers ueberpruefen der Grafik-Links. Sind alle
    // vollstaendig geladen, dann ist das Doc fertig
    void StartLoadFinishedTimer();

    // eine Uebertragung wird abgebrochen (wird aus dem SFX gerufen)
    virtual void CancelTransfers();

    // Doc aus Html-Source neu laden

    // embedded alle lokalen Links (Bereiche/Grafiken)
    sal_Int16   GetUpdateDocMode() const {return nUpdateDocMode;}

    //Activate wait cursor for all windows of this document
    //Optionally all dispatcher could be Locked
    //Usually locking should be done using the class: SwWaitObject!
    void EnterWait( BOOL bLockDispatcher );
    void LeaveWait( BOOL bLockDispatcher );

    ULONG LoadStylesFromFile( const String& rURL, SwgReaderOption& rOpt,
                                BOOL bUnoCall );

#if SUPD>620
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString >  GetEventNames();
#endif
};

inline BOOL SwDocShell::SaveAsChilds( SvStorage *pStor )
{
    return SfxInPlaceObject::SaveAsChilds( pStor );
}

inline BOOL SwDocShell::SaveCompletedChilds( SvStorage *pStor )
{
    return SfxInPlaceObject::SaveCompletedChilds( pStor );
}
} //namespace binfilter
#endif
