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
#ifndef _CAPTION_HXX
#define _CAPTION_HXX

#include <bf_svtools/bf_solar.h>

#include <tools/globname.hxx>
namespace binfilter {

enum SwCapObjType
{
    FRAME_CAP, GRAPHIC_CAP, TABLE_CAP, OLE_CAP
};

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

class InsCaptionOpt
{
private:
    BOOL         bUseCaption;
    SwCapObjType eObjType;
    SvGlobalName aOleId;
    String       sCategory;
    USHORT       nNumType;
    String       sCaption;
    USHORT       nPos;
    USHORT       nLevel;
    sal_Unicode  cSeparator;
    BOOL         bIgnoreSeqOpts;    // wird nicht gespeichert
    BOOL         bCopyAttributes;   //          -""-

public:
    InsCaptionOpt(const SwCapObjType eType = FRAME_CAP, const SvGlobalName* pOleId = 0);
    ~InsCaptionOpt();

    inline BOOL&            UseCaption()                    { return bUseCaption; }
    inline BOOL             UseCaption() const              { return bUseCaption; }

    inline SwCapObjType     GetObjType() const              { return eObjType; }
    inline void             SetObjType(const SwCapObjType eType) { eObjType = eType; }

    inline const SvGlobalName&  GetOleId() const                { return aOleId; }
    inline void             SetOleId(const SvGlobalName &rId)   { aOleId = rId; }

    inline const String&    GetCategory() const             { return sCategory; }
    inline void             SetCategory(const String& rCat) { sCategory = rCat; }

    inline USHORT           GetNumType() const              { return nNumType; }
    inline void             SetNumType(const USHORT nNT)    { nNumType = nNT; }

    inline const String&    GetCaption() const              { return sCaption; }
    inline void             SetCaption(const String& rCap)  { sCaption = rCap; }

    inline USHORT           GetPos() const                  { return nPos; }
    inline void             SetPos(const USHORT nP)         { nPos = nP; }

    inline USHORT           GetLevel() const                { return nLevel; }
    inline void             SetLevel(const USHORT nLvl)     { nLevel = nLvl; }

    inline sal_Unicode      GetSeparator() const                { return cSeparator; }
    inline void             SetSeparator(const sal_Unicode cSep){ cSeparator = cSep; }

    inline BOOL&            IgnoreSeqOpts()                 { return bIgnoreSeqOpts; }
    inline BOOL             IgnoreSeqOpts() const           { return bIgnoreSeqOpts; }

    inline BOOL&            CopyAttributes()                { return bCopyAttributes; }
    inline BOOL             CopyAttributes() const          { return bCopyAttributes; }

    inline BOOL             operator< ( const InsCaptionOpt & rObj ) const
                                                { return aOleId < rObj.aOleId; }
};

} //namespace binfilter
#endif


/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
