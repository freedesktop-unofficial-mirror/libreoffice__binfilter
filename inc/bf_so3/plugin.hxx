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

#ifndef _PLUGIN_HXX
#define _PLUGIN_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_so3/ipobj.hxx>
#include <bf_svtools/ownlist.hxx>
#include <bf_so3/ipenv.hxx>

#include "bf_so3/so3dllapi.h"

class Timer;

class INetURLObject;

namespace binfilter {

//=========================================================================
struct SvPlugInData_Impl;
class SjJScriptPluginObject;
class SjJScriptJavaObject;
class SO3_DLLPUBLIC SvPlugInObject : public SvInPlaceObject
/*  [Beschreibung]

    Die Klasse PlugInObject ist die Abbildung eines InPlace-Objektes
    auf einen PlugIn-Server. Dieses Objekt kann nur InPlace- und
    nicht UI-Aktiviert werden.

    [Probleme]
    Es handelt sich bei diesem Objekt immer um einen Link. Dieser Link
    kann allerdings InPlace aktiviert werden.
*/
{
friend class SvPlugInEnvironment;
friend class Executor_Impl;
private:
    SvPlugInEnvironment * pPlugInEnv;
    SvPlugInData_Impl * pImpl;
    SvCommandList   aCmdList;
    INetURLObject*  pURL;
    USHORT          nPlugInMode;// nicht ein Enum, wegen header file
                                // und streamen

    DECL_STATIC_LINK( SvPlugInObject, NewPlugInHdl_Impl, Timer * );
    DECL_STATIC_LINK( SvPlugInObject, DataAvailable, void* );

    SO3_DLLPRIVATE void         DataChanged_Impl( BOOL bOnlyEmbedSource );
protected:
    SO3_DLLPRIVATE BOOL         DoStartPlugIn( );
    SO3_DLLPRIVATE BOOL         StartPlugIn( );
    SO3_DLLPRIVATE virtual void    FillClass( SvGlobalName * pClassName,
                               ULONG * pFormat,
                               String * pAppName,
                               String * pFullTypeName,
                               String * pShortTypeName,
                               long nFileFormat = SOFFICE_FILEFORMAT_CURRENT ) const;
                    // Protokoll
    SO3_DLLPRIVATE virtual void    Open( BOOL bOpen );
    SO3_DLLPRIVATE virtual void    Embed( BOOL );
    SO3_DLLPRIVATE virtual void    InPlaceActivate( BOOL );
    SO3_DLLPRIVATE virtual ErrCode Verb( long, SvEmbeddedClient * pCallerClient,
                        Window * pWin, const Rectangle * pWorkRectPixel );

                    // Datenaustausch
    SO3_DLLPRIVATE virtual void    SetVisArea( const Rectangle & rVisArea );
    SO3_DLLPRIVATE virtual void    Draw( OutputDevice *,
                          const JobSetup & rSetup,
                          USHORT nAspect = ASPECT_CONTENT );

                    // Laden speichern
    SO3_DLLPRIVATE virtual BOOL    InitNew( SvStorage * );
    SO3_DLLPRIVATE virtual BOOL    Load( SvStorage * );
    SO3_DLLPRIVATE virtual BOOL    Save() {return false;}
    SO3_DLLPRIVATE virtual void    HandsOff();

    // Spaeter gerne mal virtuell...
    SO3_DLLPRIVATE void            SetMIMEDetectedLink( const Link& rLink );

    SO3_DLLPRIVATE              ~SvPlugInObject();
public:
                    SO2_DECL_BASIC_CLASS_DLL(SvPlugInObject,SOAPP)
                    SvPlugInObject();

    virtual ULONG   GetMiscStatus() const;
    virtual BOOL    IsLink() const;

                    // spezielle Internet Methoden
    void            SetCommandList( const SvCommandList & rList );
    const SvCommandList & GetCommandList() const { return aCmdList; }
    void            SetURL( const INetURLObject & rURL );
    INetURLObject * GetURL() const { return pURL; }
    void            SetMimeType( const String & rMimeType );
    const String &  GetMimeType() const;
    void            SetPlugInMode( USHORT );
    USHORT          GetPlugInMode() const { return nPlugInMode; }
};

SO2_DECL_IMPL_REF(SvPlugInObject)

}

#endif // _PLUGIN_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
