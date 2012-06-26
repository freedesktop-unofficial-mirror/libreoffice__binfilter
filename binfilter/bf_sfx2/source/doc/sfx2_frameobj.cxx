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

#include <sot/clsids.hxx>
#include <bf_so3/ipwin.hxx>


#ifdef _MSC_VER
#pragma hdrstop
#endif

#include "frameobj.hxx"

#include "frmdescr.hxx"

#include <appdata.hxx>

#include "app.hxx"

#include "objsh.hxx"

#include "bf_so3/staticbaseurl.hxx"
namespace binfilter {







/*N*/ struct SfxFrameObject_Impl
/*  [Beschreibung]

    Impl-Struktur des SfxFrameObjects.
*/
/*N*/ {
/*N*/   SfxFrameDescriptor*     pFrmDescr;
/*N*/   Timer*                  pNewObjectTimer;
/*N*/   SfxObjectShellLock      xDoc;
/*N*/
/*N*/               SfxFrameObject_Impl()
/*N*/                   : pFrmDescr( new SfxFrameDescriptor( NULL ) )
/*N*/                   , pNewObjectTimer( NULL )
/*N*/               {
/*N*/               }
/*N*/
/*N*/               ~SfxFrameObject_Impl()
/*N*/               {
/*N*/                   // Der Descriptor geh"ort dem Object, andere erhalten
/*N*/                   // davon immer nur Clones
/*N*/                   delete pFrmDescr;
/*N*/               }
/*N*/ };


//=========================================================================
//============== SfxFrameObject ===========================================
//=========================================================================
SO2_IMPL_BASIC_CLASS1_DLL(
    SfxFrameObject,
    SvFactory,
    SvInPlaceObject,
    SvGlobalName( BF_SO3_IFRAME_CLASSID )
)

//=========================================================================
SfxFrameObject::SfxFrameObject()
    : pImpl( new SfxFrameObject_Impl )
{
}

//=========================================================================
SfxFrameObject::~SfxFrameObject()
{
    delete pImpl;
}

BOOL SfxFrameObject::Load
(
    SvStorage* /*pStor*/
)
{
    DBG_BF_ASSERT(0, "STRIP");  // VIRTUAL
    return FALSE;
}

//=========================================================================

SfxFrameObjectFactoryPtr* SfxFrameObject::GetFactoryPtr()
{
    return SFX_APP()->Get_Impl()->pSfxFrameObjectFactoryPtr;
}

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
