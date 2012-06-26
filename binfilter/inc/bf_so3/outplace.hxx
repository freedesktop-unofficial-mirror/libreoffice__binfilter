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

#ifndef _OUTPLACE_HXX
#define _OUTPLACE_HXX

#include <bf_svtools/bf_solar.h>

#include <com/sun/star/lang/XComponent.hpp>

#include <com/sun/star/datatransfer/XTransferable.hpp>

#include <bf_so3/ipobj.hxx>

#include "bf_so3/so3dllapi.h"

//=========================================================================
namespace binfilter
{
    struct SvOutPlace_Impl;
    class SvObjectServer;

class SO3_DLLPUBLIC SvOutPlaceObject : public SvInPlaceObject
/*  [Beschreibung]

    Die Klasse SvOutPlaceObject ist ein Wrapper fuer alle Windows Ole-Objekte

    [Probleme]
*/
{
private:
    SvOutPlace_Impl *   pImpl;

    SO3_DLLPRIVATE void         DataChanged_Impl( BOOL bOnlyEmbedSource );
    SO3_DLLPRIVATE void         LoadSO_Cont();

protected:
    SO3_DLLPRIVATE virtual void    FillClass( SvGlobalName * pClassName,
                               ULONG * pFormat,
                               String * pAppName,
                               String * pFullTypeName,
                               String * pShortTypeName,
                               long nFileFormat = SOFFICE_FILEFORMAT_CURRENT ) const;
                    // Protokoll
    SO3_DLLPRIVATE virtual void    Open( BOOL bOpen );
    SO3_DLLPRIVATE virtual void    Embed( BOOL bEmbedded );
    SO3_DLLPRIVATE virtual ErrCode Verb( long, SvEmbeddedClient * pCallerClient,
                        Window * pWin, const Rectangle * pWorkRectPixel );

                    // Datenaustausch
    SO3_DLLPRIVATE virtual void    Draw( OutputDevice *,
                          const JobSetup & rSetup,
                          USHORT nAspect = ASPECT_CONTENT );

                    // Laden speichern
    SO3_DLLPRIVATE virtual BOOL    InitNew( SvStorage * );
    SO3_DLLPRIVATE virtual BOOL    Load( SvStorage * );
    SO3_DLLPRIVATE virtual BOOL    Save() {return false;}
    SO3_DLLPRIVATE virtual void    HandsOff();

    SO3_DLLPRIVATE              ~SvOutPlaceObject();
public:
                    SO2_DECL_BASIC_CLASS(SvOutPlaceObject)
                    SvOutPlaceObject();
    static SvInPlaceObjectRef   InsertObject( Window *, SvStorage * pIStorage,
                                            BOOL & bOut, const SvGlobalName & rName, String & rFileName );
#ifdef WNT
    static SvInPlaceObjectRef   CreateFromData( const ::com::sun::star::uno::Reference<
                                                ::com::sun::star::datatransfer::XTransferable>&,
                                                SvStorage*);
    static SvGlobalName         GetCLSID( const String & rFileName );
#endif
    static const ::binfilter::SvObjectServer* GetInternalServer_Impl( const SvGlobalName& aGlobName );

    void            ClearCache();
    SotStorage *    GetWorkingStorage();
    virtual void    SetVisArea( const Rectangle & rVisArea );
    using SvEmbeddedObject::GetVisArea;
    Rectangle       GetVisArea( USHORT dwAspect ) const;
    void            ViewChanged( USHORT nAspects );
    virtual const SvVerbList & GetVerbList() const;

    virtual UINT32      GetViewAspect() const;
    ::com::sun::star::uno::Reference < ::com::sun::star::lang::XComponent > GetUnoComponent() const;
    SvGlobalName        GetObjectCLSID();
    void    DrawObject( OutputDevice *,
                          const JobSetup & rSetup,
                          const Size& rSize,
                          USHORT nAspect = ASPECT_CONTENT );

};

SO2_DECL_IMPL_REF(SvOutPlaceObject)

}

#endif // _OUTPLACE_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
