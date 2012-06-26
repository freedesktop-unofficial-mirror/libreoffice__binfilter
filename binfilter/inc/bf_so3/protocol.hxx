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

#ifndef _PROTOCOL_HXX
#define _PROTOCOL_HXX

#include <bf_svtools/bf_solar.h>

#include <tools/errcode.hxx>
#include <bf_tools/string.hxx>

#include "bf_so3/so3dllapi.h"

/*************************************************************************
*************************************************************************/
class  String;

namespace binfilter {

class  SvEmbeddedObject;
class  SvInPlaceObject;
class  SvEmbeddedClient;
class  SvInPlaceClient;
class  SoDll;
class  ImplSvEditObjectProtocol;

class SO3_DLLPUBLIC SvEditObjectProtocol
{
friend class SoDll;
private:
    ImplSvEditObjectProtocol * pImp;
    SO3_DLLPRIVATE static void         Imp_DeleteDefault();
    SO3_DLLPRIVATE BOOL                Release();
public:
    SvEditObjectProtocol();
    SvEditObjectProtocol( const SvEditObjectProtocol & );
    SO3_DLLPRIVATE SvEditObjectProtocol & operator = ( const SvEditObjectProtocol & );
    ~SvEditObjectProtocol();

    // Objekte
    SvEmbeddedObject * GetObj() const;
    SvInPlaceObject *  GetIPObj() const;
    SvEmbeddedClient * GetClient() const;
    SvInPlaceClient *  GetIPClient() const;

    // Zustandsabfragen
    BOOL IsConnect() const;
    BOOL IsOpen() const;
    BOOL IsEmbed() const;
    BOOL IsPlugIn() const;
    BOOL IsInPlaceActive() const;
    BOOL IsUIActive() const;

    // Protokolle
    ErrCode EmbedProtocol();
    ErrCode PlugInProtocol();
    ErrCode IPProtocol();
    ErrCode UIProtocol();

    // Protokoll zurueckfahren
    BOOL Reset();
    BOOL Reset2Connect();
    BOOL Reset2Open();
    BOOL Reset2Embed();
    BOOL Reset2PlugIn();
    BOOL Reset2InPlaceActive();
    BOOL Reset2UIActive();

    // Einzelschritte der Protokolle
    void Opened( BOOL bOpen );
    void Embedded( BOOL bEmbed );
    void PlugIn( BOOL bPlugIn );
    void InPlaceActivate( BOOL bActivate );
    void UIActivate( BOOL bActivate );
    void SetInClosed( BOOL bInClosed );
};

}

#endif // _PROTOCOL_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
