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

#ifndef _SD_DOCSHELL_HXX
#define _SD_DOCSHELL_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_sfx2/docfac.hxx>
#include <bf_sfx2/interno.hxx>
#include <bf_sfx2/objsh.hxx>
#include <sot/factory.hxx>
#include <bf_so3/factory.hxx>

#include "glob.hxx"
#include "sdmod.hxx"
#include "pres.hxx"
class SvStream;

namespace binfilter {
class FontList;
class SfxStyleSheetBasePool;

#ifndef SO2_DECL_SVSTORAGESTREAM_DEFINED
#define SO2_DECL_SVSTORAGESTREAM_DEFINED
SO2_DECL_REF(SvStorageStream)
#endif

class SfxStatusBarManager;
class SdStyleSheetPool;
class FrameView;
class SdDrawDocument;
class SdView;
class SdPage;
class SfxPrinter;
struct SdrDocumentStreamInfo;
struct SpellCallbackInfo;
class SvxNameDialog;

// ------------------
// - SdDrawDocShell -
// ------------------

class SdDrawDocShell : public SfxObjectShell, public SfxInPlaceObject
{
protected:

    SfxProgress*            pProgress;
    SdDrawDocument*         pDoc;
    SfxPrinter*             pPrinter;
    DocumentType            eDocType;
    UINT16                  nStyleFamily;
    const USHORT*           pFilterSIDs;
    USHORT                  nFilterCount;
    BOOL                    bFilterEnable;
    BOOL                    bUIActive;
    BOOL                    bSdDataObj;
    BOOL                    bInDestruction;
    BOOL                    bOwnPrinter;
    BOOL                    mbNewDocument;

    void                    Construct();

public:
    void                    UpdateRefDevice();
    virtual void            Deactivate( BOOL bMDI );
    virtual BOOL            InitNew( SvStorage * );
    virtual BOOL            Load( SvStorage * );
    virtual void            HandsOff();
    virtual BOOL            Save() {return false;}
    virtual void            SetVisArea(const Rectangle& rRect);
    virtual Rectangle       GetVisArea(USHORT nAspect) const;
    virtual Printer*        GetDocumentPrinter();
    virtual SfxStyleSheetBasePool* GetStyleSheetPool();
    virtual void            FillClass(SvGlobalName* pClassName, ULONG*  pFormat, String* pAppName, String* pFullTypeName, String* pShortTypeName, long nFileFormat = SOFFICE_FILEFORMAT_CURRENT) const;
    virtual void            SetModified( BOOL = TRUE );

    static SfxPrinter* CreatePrinter( SvStream& rIn, SdDrawDocument& rDoc );
public:

                            TYPEINFO();
                            SFX_DECL_OBJECTFACTORY_DLL(SdDrawDocShell, SD_MOD());

                            SdDrawDocShell(SfxObjectCreateMode eMode = SFX_CREATE_MODE_EMBEDDED, BOOL bSdDataObj=FALSE, DocumentType=DOCUMENT_TYPE_IMPRESS);
                            SdDrawDocShell(SdDrawDocument* pDoc, SfxObjectCreateMode eMode = SFX_CREATE_MODE_EMBEDDED, BOOL bSdDataObj=FALSE, DocumentType=DOCUMENT_TYPE_IMPRESS);
                            ~SdDrawDocShell();

    SdDrawDocument*         GetDoc();
    DocumentType            GetDocumentType() const { return eDocType; }

    SfxPrinter*             GetPrinter(BOOL bCreate);
    void                    SetPrinter(SfxPrinter *pNewPrinter);

    BOOL                    IsUIActive() { return bUIActive; }
    BOOL                    IsInDestruction() const { return bInDestruction; }


    void                    UpdateTablePointers();

    void                    SetSlotFilter(BOOL bEnable = FALSE, USHORT nCount = 0, const USHORT* pSIDs = NULL) { bFilterEnable = bEnable; nFilterCount = nCount; pFilterSIDs = pSIDs; }

    UINT16                  GetStyleFamily() const { return nStyleFamily; }
    void                    SetStyleFamily( UINT16 nSF ) { nStyleFamily = nSF; }

    bool                    IsNewPageNameValid( String & rInOutPageName, bool bResetStringIfStandardName = false );

    virtual OutputDevice* GetDocumentRefDev (void);

    DECL_LINK( RenameSlideHdl, SvxNameDialog* );

};

#ifndef SV_DECL_SDDRAWDOCSHELL_DEFINED
#define SV_DECL_SDDRAWDOCSHELL_DEFINED
SV_DECL_REF(SdDrawDocShell)
#endif

SV_IMPL_REF (SdDrawDocShell)

} //namespace binfilter
#endif // _SD_DOCSHELL_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
