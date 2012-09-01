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
#ifndef _SFX_INTERNO_HXX
#define _SFX_INTERNO_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_so3/ipobj.hxx>
#include "bf_sfx2/objsh.hxx"
#include "bf_sfx2/sfx.hrc"

namespace binfilter {

struct SfxInPlaceObject_Impl;
class SfxObjectShell;
class INote;


//=========================================================================

class SfxInPlaceObject : public SvInPlaceObject
{
    SfxObjectShell*     pObjShell;
    INote*              pNote;
    BOOL                bTriggerLinkTimer : 1;
    BOOL                bDisableViewScaling : 1;

#if _SOLAR__PRIVATE
private:

public:
#endif
                        SO2_DECL_STANDARD_CLASS(SfxInPlaceObject)
public:
    SfxObjectShell*     GetObjectShell() const { return pObjShell; }

protected:
    void                SetShell( SfxObjectShell *pObjSh );

    virtual void        FillClass( SvGlobalName * pClassName,
                                   ULONG * pClipFormat,
                                   String * pAppName,
                                   String * pLongUserName,
                                   String * pUserName,
                                   long nVersion = SOFFICE_FILEFORMAT_CURRENT
    ) const;

    virtual BOOL        InitNew( SvStorage * );         // Rekursiv
    virtual BOOL        Load( SvStorage * );            // Rekursiv
    virtual BOOL        Save() {return false;}                         // Rekursiv
    virtual void        HandsOff();                     // Rekursiv

    virtual ErrCode     Verb( long nVerbPos,
                            SvEmbeddedClient *pCaller,
                            Window *pWin,
                            const Rectangle *pWorkAreaPixel );
    virtual BOOL        Verb( long nVerbPos, const Rectangle *pWorkAreaPixel );
    virtual void        Embed( BOOL bEmbedded );
    virtual void        Open( BOOL bOpen );
    virtual void        InPlaceActivate( BOOL );
    virtual void        DocumentNameChanged( const String & rDocName );

    virtual             ~SfxInPlaceObject();

public:
                        SfxInPlaceObject();

    void                SetTriggerLinkTimer( BOOL bSet )
                        { bTriggerLinkTimer = bSet; }
    void                UpdateLinks();

    virtual void        SetVisArea( const Rectangle & rVisArea );

    void                SetModified( BOOL bSet );
    void                DisableViewScaling( BOOL bSet )
                        { bDisableViewScaling = bSet; }
    BOOL                IsViewScalingDisabled()
                        { return bDisableViewScaling; }
};

#ifndef SFX_DECL_INTERNALOBJECT_DEFINED
#define SFX_DECL_INTERNALOBJECT_DEFINED
SO2_DECL_REF(SfxInPlaceObject)
#endif
SO2_IMPL_REF(SfxInPlaceObject)

#if _SOLAR__PRIVATE
class SfxForceLinkTimer_Impl
{
    SfxInPlaceObject *pInObj;

public:
    SfxForceLinkTimer_Impl( SfxObjectShell *pObj );
    ~SfxForceLinkTimer_Impl()
    { if( pInObj ) pInObj->SetTriggerLinkTimer( TRUE ); }
};
#endif


}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
