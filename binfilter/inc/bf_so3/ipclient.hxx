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

#ifndef _IPCLIENT_HXX
#define _IPCLIENT_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_so3/client.hxx>

#include "bf_so3/so3dllapi.h"

/*************************************************************************
*************************************************************************/
class  MenuBar;
class  Accelerator;
struct IOleInPlaceSite;
struct IOleInPlaceFrame;
struct IOleInPlaceUIWindow;

namespace binfilter {
class  SvInPlaceEnvironment;
class SvContainerEnvironment;
class  SvInPlaceClientList;
class  SvInPlaceClient;
class  SvInPlaceClient;
class  SvInPlaceObject;
class  ImpInPlaceSite;
class  ImpInPlaceFrame;
class  ImpInPlaceUIWin;

    //=========================================================================
class SO3_DLLPUBLIC SvInPlaceClient : public SvEmbeddedClient
{
friend class ImpInPlaceSite;
friend class ImpInPlaceFrame;
friend class ImpInPlaceUIWin;
friend class SvInPlaceObject;
friend class SvEditObjectProtocol;
friend class ImplSvEditObjectProtocol;
friend class SvContainerEnvironment;

    IOleInPlaceSite *       pObjI;

    SO3_DLLPRIVATE  BOOL                CanInPlaceActivate() const;
protected:
                             ~SvInPlaceClient();

    virtual void        Opened( BOOL bOpen );
    virtual void        InPlaceActivate( BOOL bActivate );
    virtual void        UIActivate( BOOL bActivate );

    virtual void        MakeViewData();
public:
                        SvInPlaceClient();
                        SO2_DECL_STANDARD_CLASS_DLL(SvInPlaceClient,SOAPP)

    IOleInPlaceSite *           GetInPlaceSite() const;

    static SvInPlaceClientList & GetIPActiveClientList();

    SvContainerEnvironment *    GetEnv();
    virtual void                MakeVisible();

    BOOL                        IsInPlaceActive() const
                                { return aProt.IsInPlaceActive(); }
    SvInPlaceObject *           GetIPObj() const
                                { return aProt.GetIPObj(); }

    virtual void                DeactivateAndUndo();
    virtual void                DiscardUndoState();
};
#ifndef SO2_DECL_SVINPLACECLIENT_DEFINED
#define SO2_DECL_SVINPLACECLIENT_DEFINED
SO2_DECL_REF(SvInPlaceClient)
#endif
SO2_IMPL_REF(SvInPlaceClient)

SV_DECL_REF_LIST(SvInPlaceClient,SvInPlaceClient*)
SV_IMPL_REF_LIST(SvInPlaceClient,SvInPlaceClient*)

}

#endif // _IPCLIENT_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
