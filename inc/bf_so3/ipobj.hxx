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

#ifndef _IPOBJ_HXX
#define _IPOBJ_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_so3/embobj.hxx>
#include <bf_so3/ipobj.hxx>

#include "bf_so3/so3dllapi.h"

/*************************************************************************/
/*************************************************************************/
class  MenuBar;
class  Window;
class  KeyEvent;
class  Palette;

namespace binfilter {

class  SvContainerEnvironment;
class  ImpInPlaceObject;
class  ImpInPlaceSite;
class  ImpOleInPlaceActiveObject;
struct IOleInPlaceObject;
struct IOleInPlaceActiveObject;
class SvInPlaceEnvironment;
class  SvInPlaceClipWindow;
class  SvInPlaceWindow;

/*************************************************************************
*************************************************************************/

class SvInPlaceObject;
#ifndef SO2_DECL_SVINPLACEOBJECT_DEFINED
#define SO2_DECL_SVINPLACEOBJECT_DEFINED
SO2_DECL_REF(SvInPlaceObject)
#endif

class SO3_DLLPUBLIC SvInPlaceObject : public SvEmbeddedObject
{
friend class ImpInPlaceObject;
friend class ImpInPlaceSite;
friend class SvInPlaceClient;
friend class ImpOleInPlaceActiveObject;
friend class SvEditObjectProtocol;
friend class ImplSvEditObjectProtocol;
friend class SvInPlaceEnvironment;

private:
    IOleInPlaceObject *         pObjI;
    IOleInPlaceActiveObject *   pActiveObj;
    SvInPlaceEnvironment *      pIPEnv;
    BOOL                        bIsUndoable:1,
                                bDeleteIPEnv:1;

    SO3_DLLPRIVATE BOOL                         DoMergePalette();
protected:
                     ~SvInPlaceObject();

    virtual void    TopWinActivate( BOOL bActivate );
    virtual void    DocWinActivate( BOOL bActivate );

    SO3_DLLPRIVATE void         SetIPEnv( SvInPlaceEnvironment * pFrm );

    virtual ErrCode Verb( long nVerbPos, SvEmbeddedClient * pCallerClient,
                        Window * pWin, const Rectangle * pWorkAreaPixel );
    virtual void    Open( BOOL bOpen );
    virtual void    InPlaceActivate( BOOL bActivate );
    virtual void    UIActivate( BOOL bActivate );

    SO3_DLLPRIVATE void         SetUndoable( BOOL bUndoable )
                    { bIsUndoable = bUndoable; }
    // View
    virtual BOOL    MergePalette( const Palette & rContainerPal );
public:
                    SvInPlaceObject();
                    SO2_DECL_STANDARD_CLASS_DLL(SvInPlaceObject,SOAPP)
    IOleInPlaceObject *         GetInPlaceObject() const;
    IOleInPlaceActiveObject *   GetInPlaceActiveObject() const;
    BOOL                        SetInPlaceActiveObject( IOleInPlaceActiveObject * );

    SvInPlaceEnvironment* GetIPEnv() const { return pIPEnv; }
    SvInPlaceClient * GetIPClient() const
                    { return aProt.GetIPClient(); }

    // Robuste Protokollsteuerung
    ErrCode         DoInPlaceActivate( BOOL bActivate );
    ErrCode         DoUIActivate( BOOL bActivate );

    virtual void    SetVisArea( const Rectangle & rVisArea );
    BOOL            IsUndoable() const { return bIsUndoable; }
    virtual BOOL    ReactivateAndUndo();
};

SO2_IMPL_REF(SvInPlaceObject)

//=========================================================================
class SO3_DLLPUBLIC SvDeathObject : public SvInPlaceObject
/*  [Beschreibung]

    Wenn das Laden eine Ole-Objektes fehlschl"agt, kann dieses Objekt
    teilweise als ersatzt dienen.

    [Probleme]

    Nicht an allen Methoden des Objektes erkennt der Aufrufer,
    dass es sich um eine Ersatzobjekt handelt.
*/
{
protected:
    SO3_DLLPRIVATE virtual ErrCode Verb( long, SvEmbeddedClient * pCallerClient,
                        Window * pWin, const Rectangle * pWorkRectPixel );
    SO3_DLLPRIVATE virtual void    Draw( OutputDevice *,
                          const JobSetup & rSetup,
                          USHORT nAspect = ASPECT_CONTENT );
public:
                    SvDeathObject( const Rectangle & rVisArea );
};

}

#endif // _IPOBJ_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
