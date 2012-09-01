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

#ifndef _SCH_DOCSHELL_HXX
#define _SCH_DOCSHELL_HXX

#include <bf_svtools/bf_solar.h>

#include "schdll0.hxx"

#include <bf_sfx2/docfac.hxx>

#include <bf_sfx2/shell.hxx>

#include <bf_svx/flstitem.hxx>

#include <bf_sfx2/objsh.hxx>
#include <bf_sfx2/interno.hxx>
#include <schdll0.hxx>
#include <bf_sfx2/request.hxx>

#include <bf_so3/svstor.hxx>

#include "chtmodel.hxx"

#include <bf_sfx2/docfile.hxx>

#include "glob.hxx"

#include <com/sun/star/chart/ChartDataChangeEvent.hpp>
namespace binfilter {

#ifndef SO2_DECL_SVSTORAGESTREAM_DEFINED
#define SO2_DECL_SVSTORAGESTREAM_DEFINED
SO2_DECL_REF(SvStorageStream)
#endif

class FontList;
class SfxUndoManager;
class SfxStyleSheetBasePool;
class SdStyleSheetPool;
class SfxProgress;
class SfxPrinter;
class SfxMenuBarManager;

/*************************************************************************
|*
|* Document-Shell fuer Draw-Dokumente
|*
\************************************************************************/

class SchChartDocShell: public SfxObjectShell, public SfxInPlaceObject
{
 private:
    ChartModel*         pChDoc;
    SfxUndoManager*     pUndoManager;
    SfxPrinter*         pPrinter;
    FontList*           pFontList;
    SfxProgress*        pProgress;
    BOOL                bInitNewNoNewDoc;
    BOOL                bOwnPrinter;
    BOOL                mbClipboardExport;

    void Construct() throw();

     // #61907# bei deaktivierung des InPlaceEdit evtl. gebufferte neue Daten
    // ?bernehmen
 protected:

 public:
    TYPEINFO();

    SFX_DECL_OBJECTFACTORY_DLL(SchChartDocShell,SCH_MOD());

    SchChartDocShell(SfxObjectCreateMode eMode = SFX_CREATE_MODE_EMBEDDED) throw();
    ~SchChartDocShell() throw();


    virtual BOOL InitNew(SvStorage*) throw();
    virtual BOOL Load(SvStorage*) throw();
    virtual BOOL Save() throw() {return false;}

    virtual Rectangle GetVisArea(USHORT nAspect) const throw();
    virtual void SetVisArea(const Rectangle& rRect) throw();


    virtual SfxUndoManager* GetUndoManager() throw();

    SfxPrinter* GetPrinter() throw();
    void SetPrinter( SfxPrinter *pNewPrinter, BOOL bIsDeletedHere = FALSE ) throw();

    virtual void     OnDocumentPrinterChanged(Printer* pNewPrinter) throw();

    /** @return if the chart is embedded in a document, this may be a virtual
                device for layout, or a printer, according to what is set in the
                container.  Otherwise GetPrinter() is called.
     */
    OutputDevice * GetRefDevice();

    ChartModel& GetDoc() { return *pChDoc; }
    ChartModel* GetModelPtr() { return pChDoc; }
    void SetModelPtr( ChartModel* pModel ) { pChDoc = pModel; }

    virtual SfxStyleSheetBasePool* GetStyleSheetPool() throw();

    void UpdateTablePointers() throw();

    virtual void FillClass(SvGlobalName* pClassName,
                           ULONG*  pFormat,
                           String* pAppName,
                           String* pFullTypeName,
                           String* pShortTypeName,
                           long    nFileFormat = SOFFICE_FILEFORMAT_CURRENT ) const throw();

    virtual ULONG GetMiscStatus() const throw();

    virtual void    SetModified( BOOL = TRUE ) throw();

    void DataModified( ::com::sun::star::chart::ChartDataChangeEvent& ) throw();

    /// if this flag is set the XML export always exports the table
    void SetClipboardExport( BOOL bSet = sal_False )
        { mbClipboardExport = bSet; }
    BOOL GetClipboardExport() const
        { return mbClipboardExport; }

};

SO2_DECL_IMPL_REF(SchChartDocShell)

} //namespace binfilter
#endif      // _SCH_DOCSHELL_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
