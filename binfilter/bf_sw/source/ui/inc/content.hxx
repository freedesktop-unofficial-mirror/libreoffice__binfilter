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
#ifndef _CONTENT_HXX
#define _CONTENT_HXX

#include <bf_svtools/bf_solar.h>

#include <limits.h>     // USHRT_MAX
#include "swcont.hxx"

#include <vcl/menu.hxx>
namespace binfilter {

class SwWrtShell;
class SwContentArr;
class SwContentType;
class SwNavigationPI;
class SwFmtFld;
class SwTxtINetFmt;
class SwDocShell;
class SvDataObject;
class SwTOXBase;

//----------------------------------------------------------------------------
//  Hilfsklassen
//----------------------------------------------------------------------------

class SwPopup : public PopupMenu
{
    USHORT          nCurId;
    virtual void    Select(){nCurId = GetCurItemId();}

public:
    SwPopup() :
        PopupMenu(),
        nCurId(USHRT_MAX){}

    USHORT          GetCurId() const { return nCurId; }

};

//----------------------------------------------------------------------------

class SwOutlineContent : public SwContent
{
    USHORT  nOutlinePos;
    BYTE    nOutlineLevel;
    BOOL    bIsMoveable;
    public:
        SwOutlineContent(   const SwContentType* pCnt,
                            const String& rName,
                            USHORT nArrPos,
                            BYTE nLevel,
                            BOOL bMove,
                            long nYPos) :
            SwContent(pCnt, rName, nYPos), nOutlineLevel(nLevel),
                        nOutlinePos(nArrPos), bIsMoveable(bMove){}

    USHORT  GetPos(){return nOutlinePos;}
    BYTE    GetOutlineLevel(){return nOutlineLevel;}
    BOOL    IsMoveable(){return bIsMoveable;};
};

//----------------------------------------------------------------------------
class SwRegionContent : public SwContent
{

    BYTE    nRegionLevel;

    public:
        SwRegionContent(    const SwContentType* pCnt,
                            const String& rName,
                            BYTE nLevel,
                            long nYPos) :
            SwContent(pCnt, rName, nYPos),
                        nRegionLevel(nLevel){}
    BYTE    GetRegionLevel() const {return nRegionLevel;}
};
//----------------------------------------------------------------------------




//----------------------------------------------------------------------------



//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
/*
    class ContentType enthaelt Informationen zu einer Inhaltsform
    Das MemberArray wird nur gefuellt, wenn der Inhalt mit GetMember
    angefordert wird. Es wird nach Invalidate() nur dann neu geladen,
    wenn der Inhalt erneut ausgelesen werden soll.
*/
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------






} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
