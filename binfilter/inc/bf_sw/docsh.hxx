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
#ifndef _SWDOCSH_HXX
#define _SWDOCSH_HXX

#include <bf_svtools/bf_solar.h>

#include <vcl/timer.hxx>
#include <bf_sfx2/docfac.hxx>
#include <bf_sfx2/interno.hxx>
#include <bf_sfx2/objsh.hxx>
#include <swdll.hxx>
#include <shellid.hxx>

#include <bf_svtools/lstner.hxx>

class   SfxStyleSheetBasePool;
class   FontList;
class   PushButton;
class   FixedText;

namespace binfilter {

class   SwDoc;
class   Sw3Io;
class   SfxDocumentInfoDialog;
class   SwView;
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

    // DocInfo dem Doc melden
    //
    // OLE-Geraffel

    // Methoden fuer StyleSheets

    void                    InitDraw();
    void                    SubInitNew();   // fuer InitNew und HtmlSourceModus

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
    virtual BOOL            Save() {return false;}

    // fuer VorlagenPI
    virtual SfxStyleSheetBasePool*  GetStyleSheetPool();

    // Fuer Organizer



    const SwView *GetView() const { return pView; }
    SwView       *GetView()       { return pView; }

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

    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString >  GetEventNames();
};

} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
