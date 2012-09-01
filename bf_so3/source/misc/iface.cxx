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

#include <string.h>
#include <stdio.h>


#include <bf_so3/iface.hxx>
#include <bf_svtools/ownlist.hxx>

#include "bf_so3/soerr.hxx"

#include <tools/debug.hxx>

namespace binfilter {

/************** class SvObject ******************************************/
SV_IMPL_FACTORY(SvObjectFactory)
    {
    }
};
TYPEINIT1(SvObjectFactory,SvFactory);


SO2_IMPL_CLASS1_DLL(SvObject,SvObjectFactory,SotObject,
                   SvGlobalName( 0x7F7E0E60L, 0xC32D, 0x101B,
                            0x80, 0x4C, 0x04, 0x02, 0x1C, 0x00, 0x70, 0x02 ) )

/*************************************************************************
|*  SvObject::GetMemberInterface()
|*
|*  Beschreibung:
*************************************************************************/
::IUnknown * SvObject::GetMemberInterface( const SvGlobalName & )
{
    return NULL;
}

/*************************************************************************
|*    SvObject::SvObject()
|*
|*    Beschreibung
*************************************************************************/
SvObject::SvObject()
    : pObj        ( NULL ) // union mit pClient, pService
    , nExtCount   ( 0 )
{
}

/*************************************************************************
|*
|*    SvObject::~SvObject()
|*
*************************************************************************/
SvObject::~SvObject()
{
}

/*************************************************************************
|*
|*    SvObject::ReleaseRef()
|*
*************************************************************************/
UINT32 SvObject::ReleaseRef()
{
    return SotObject::ReleaseRef();
}

//========================================================================
void SvObject::MakeUnknown()
/* [Beschreibung]

    Klassen, die immer extern sind, aber nicht sofort <SvObject::Init>
    rufen, m"ussen diese Methode "uberladen.
    Darin muss das externe Objekt erzeugt und mit Init eingesetzt werden.
    Im Konstruktor muss das Objekt als extern gekennzeichnet werden.

    [Beispiel]

    void MyClass::MyClass()
    {
        SetExtern();
    }

    void MyClass::MakeUnknown()
    {
        CreateBindCtx( 0, &pObjI );
        Init( pObjI );
    }
*/
{
}



#if defined (_INC_WINDOWS) || defined (_WINDOWS_)
RECT GetSysRect( const Rectangle & rRect )
{
    RECT aRect;
    aRect.top    = (int)rRect.Top();
    aRect.left   = (int)rRect.Left();
    if( rRect.Right() == RECT_EMPTY )
        aRect.right  = aRect.left;
    else
        aRect.right  = (int)(rRect.Right() +1);
    if( rRect.Bottom() == RECT_EMPTY )
        aRect.bottom = aRect.top;
    else
        aRect.bottom = (int)(rRect.Bottom() +1);
    return aRect;
}
Rectangle GetSvRect( const RECT & rRect )
{
    Rectangle aRect;
    aRect.Top()     = rRect.top;
    aRect.Left()    = rRect.left;
    if( rRect.right != rRect.left )
        aRect.Right()   = rRect.right -1;
    if( rRect.bottom != rRect.top )
        aRect.Bottom()  = rRect.bottom -1;
    return aRect;
}
#endif

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
