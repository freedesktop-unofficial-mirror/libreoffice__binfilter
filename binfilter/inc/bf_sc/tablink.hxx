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

#ifndef SC_TABLINK_HXX
#define SC_TABLINK_HXX

#include <bf_svtools/bf_solar.h>

#include "refreshtimer.hxx"

#include <bf_so3/embobj.hxx>

#include <bf_so3/lnkbase.hxx>
namespace binfilter {

#ifndef SO2_DECL_SVEMBEDDEDOBJECT_DEFINED
#define SO2_DECL_SVEMBEDDEDOBJECT_DEFINED
SO2_DECL_REF(SvEmbeddedObject)
#endif

class ScDocShell;
class SfxObjectShell;

class ScTableLink : public ::binfilter::SvBaseLink, public ScRefreshTimer
{
private:
    ScDocShell* pDocShell;      // Container
    String      aFileName;
    String      aFilterName;
    String      aOptions;
    BOOL        bInCreate;
    BOOL        bInEdit;
    BOOL        bAddUndo;
    BOOL        bDoPaint;

public:
    TYPEINFO();
    ScTableLink( ScDocShell* pDocSh, const String& rFile,
                    const String& rFilter, const String& rOpt, ULONG nRefresh );
    ScTableLink( SfxObjectShell* pShell, const String& rFile,
                    const String& rFilter, const String& rOpt, ULONG nRefresh );
    virtual ~ScTableLink();
    virtual void DataChanged( const String& rMimeType,
                              const ::com::sun::star::uno::Any & rValue );


    BOOL    Refresh(const String& rNewFile, const String& rNewFilter,
                    const String* pNewOptions /* = NULL */, ULONG nNewRefresh );
    void    SetInCreate(BOOL bSet)      { bInCreate = bSet; }
    void    SetAddUndo(BOOL bSet)       { bAddUndo = bSet; }
    void    SetPaint(BOOL bSet)         { bDoPaint = bSet; }

    const String& GetFileName() const   { return aFileName; }
    const String& GetFilterName() const { return aFilterName; }
    const String& GetOptions() const    { return aOptions; }


    DECL_LINK( RefreshHdl, ScTableLink* );

};


class ScDocument;
class SfxMedium;

class ScDocumentLoader
{
private:
    ScDocShell*         pDocShell;
    SvEmbeddedObjectRef aRef;
    SfxMedium*          pMedium;

public:
                        ScDocumentLoader( const String& rFileName,
                                            String& rFilterName, String& rOptions,
                                            UINT32 nRekCnt = 0, BOOL bWithInteraction = FALSE );
                        ~ScDocumentLoader();
    ScDocument*         GetDocument();
    ScDocShell*         GetDocShell()       { return pDocShell; }
    BOOL                IsError() const;

    static String       GetOptions( SfxMedium& rMedium );
    static void         GetFilterName( const String& rFileName,
                                        String& rFilter, String& rOptions,
                                        BOOL bWithContent = FALSE );
    static void         RemoveAppPrefix( String& rFilterName );
};

} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
