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

#ifndef _NOTEURL_HXX
#define _NOTEURL_HXX


#include <bf_svtools/svarray.hxx>
#include <bf_tools/string.hxx>
#include "swrect.hxx"
class MapMode;

namespace binfilter {

class ImageMap;

class SwURLNote
{
    String aURL;
    String aTarget;
    SwRect aRect;
public:
    SwURLNote( const String& rURL, const String& rTarget, const SwRect& rRect )
    : aURL( rURL ), aTarget( rTarget ), aRect( rRect )
    {}
    const String& GetURL()      const { return aURL; }
    const String& GetTarget()   const { return aTarget; }
    const SwRect& GetRect()     const { return aRect; }
    BOOL operator==( const SwURLNote& rSwURLNote ) const
    { return aRect == rSwURLNote.aRect; }
};

typedef SwURLNote* SwURLNotePtr;
SV_DECL_PTRARR_DEL(SwURLNoteList, SwURLNotePtr, 0, 5)

class SwNoteURL
{
    SwURLNoteList aList;
public:
    SwNoteURL() {}
    USHORT Count() const { return aList.Count(); }
    const SwURLNote& GetURLNote( USHORT nPos ) const
        { return *aList.GetObject( nPos ); }
};

// globale Variable, in NoteURL.Cxx angelegt
extern SwNoteURL *pNoteURL;


} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
