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

#ifndef SC_AREALINK_HXX
#define SC_AREALINK_HXX

#include <bf_svtools/bf_solar.h>

#include "global.hxx"
#include "refreshtimer.hxx"

#include <bf_so3/lnkbase.hxx>
namespace binfilter {

class ScDocShell;
class SfxObjectShell;

class ScAreaLink : public ::binfilter::SvBaseLink, public ScRefreshTimer
{
private:
    ScDocShell* pDocShell;      // Container
    String      aFileName;
    String      aFilterName;
    String      aOptions;
    String      aSourceArea;
    ScRange     aDestArea;
    BOOL        bAddUndo;
    BOOL        bInCreate;
    BOOL        bDoInsert;      // wird fuer das erste Update auf FALSE gesetzt

    BOOL        FindExtRange( ScRange& rRange, ScDocument* pSrcDoc, const String& rAreaName );

public:
    TYPEINFO();
    ScAreaLink( SfxObjectShell* pShell, const String& rFile,
                    const String& rFilter, const String& rOpt,
                    const String& rArea, const ScRange& rDest, ULONG nRefresh );
    virtual ~ScAreaLink();

    virtual void DataChanged( const String& rMimeType,
                              const ::com::sun::star::uno::Any & rValue );


    BOOL    Refresh( const String& rNewFile, const String& rNewFilter,
                    const String& rNewArea, ULONG nNewRefresh );

    void    SetInCreate(BOOL bSet)                  { bInCreate = bSet; }
    void    SetDoInsert(BOOL bSet)                  { bDoInsert = bSet; }
    void    SetDestArea(const ScRange& rNew);


    const String&   GetFile() const         { return aFileName;     }
    const String&   GetFilter() const       { return aFilterName;   }
    const String&   GetOptions() const      { return aOptions;      }
    const String&   GetSource() const       { return aSourceArea;   }
    const ScRange&  GetDestArea() const     { return aDestArea;     }

    DECL_LINK( RefreshHdl, ScAreaLink* );

};


} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
