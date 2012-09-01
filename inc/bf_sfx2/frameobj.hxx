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

#ifndef _FRAMEOBJ_HXX
#define _FRAMEOBJ_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_so3/ipobj.hxx>
namespace binfilter {

//=========================================================================
struct SfxFrameObject_Impl;
class SfxFrameDescriptor;

struct SfxFrameObjectFactoryPtr
{
    // Ist n"otig, da im SO2_DECL_BASIC_CLASS_DLL-Macro ein Pointer auf
    // eine exportierbare struct/class "ubergeben werden mu\s
    SotFactory *pSfxFrameObjectFactory;
    SfxFrameObjectFactoryPtr();
};

class SfxFrameObject : public SvInPlaceObject
/*  [Beschreibung]

*/
{
    SfxFrameObject_Impl*    pImpl;

#if _SOLAR__PRIVATE
    DECL_LINK(              NewObjectHdl_Impl, Timer* );
#endif

protected:
    BOOL                    ConstructFrame();
                            // Protokoll

                            // Datenaustausch

                            // Laden speichern
    virtual BOOL            Load( SvStorage * );
    virtual BOOL            Save() {return false;}

                            ~SfxFrameObject();
public:

    static SfxFrameObjectFactoryPtr*
                            GetFactoryPtr();

                            // Macro mu\s exportiert werden, sonst geht das
                            // SO2-RTTI schief, da GetFactoryAdress() die
                            // Factory-Adresse der Basisklasse liefert.
                            // Da das zweite Argument in einer Inline-Funktion
                            // verwendet wird, mu\s dieses exportierbare
                            // Funktionsaufrufe verwenden, also nicht z.B.
                            // SFX_APP()->Get_Impl()
                            SO2_DECL_BASIC_CLASS_DLL(SfxFrameObject, GetFactoryPtr())

                            SfxFrameObject();
};

inline SfxFrameObjectFactoryPtr::SfxFrameObjectFactoryPtr()
    : pSfxFrameObjectFactory(0)     // sonst funzt ClassFactory() nicht!
{
    // hier Factory nicht erzeugen, da GetFactoryPtr() erst nach Beenden dieses
    // ctors einen vern"unftigen Wert liefern kann!
}

SO2_DECL_IMPL_REF(SfxFrameObject)


}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
