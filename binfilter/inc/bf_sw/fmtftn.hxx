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
#ifndef _FMTFTN_HXX
#define _FMTFTN_HXX

#include <bf_svtools/bf_solar.h>


#include <bf_svtools/poolitem.hxx>
namespace binfilter {

class SwDoc;
class SwTxtFtn;

// ATT_FTN **********************************************************

class SwFmtFtn: public SfxPoolItem
{
    friend class SwTxtFtn;
    SwTxtFtn* pTxtAttr;     //mein TextAttribut
    String  aNumber;        //Benutzerdefinierte 'Nummer'
    USHORT  nNumber;        //Automatische Nummerierung
    BOOL    bEndNote;       //Ist es eine Endnote?

    // geschuetzter CopyCtor
    SwFmtFtn& operator=(const SwFmtFtn& rFtn);
    SwFmtFtn( const SwFmtFtn& );

public:
    SwFmtFtn( BOOL bEndNote = FALSE );
    ~SwFmtFtn() {}

    // "pure virtual Methoden" vom SfxPoolItem
    virtual int             operator==( const SfxPoolItem& ) const {DBG_BF_ASSERT(0, "STRIP"); return 0; }
    virtual SfxPoolItem*    Clone( SfxItemPool* pPool = 0 ) const;
    virtual SfxPoolItem*    Create(SvStream &, USHORT nVer) const;
    virtual SvStream&       Store(SvStream &rStream, USHORT) const { return rStream; }
    virtual USHORT          GetVersion( USHORT nFFVer ) const;

    const String &GetNumStr() const { return aNumber; }
    const USHORT &GetNumber() const { return nNumber; }
          BOOL    IsEndNote() const { return bEndNote;}

    void SetNumStr( const String& rStr )    { aNumber = rStr; }
    void SetNumber( USHORT nNo )            { nNumber = nNo; }

    void SetNumber( const SwFmtFtn& rFtn )
        { nNumber = rFtn.nNumber; aNumber = rFtn.aNumber; }

    const SwTxtFtn *GetTxtFtn() const   { return pTxtAttr; }
          SwTxtFtn *GetTxtFtn()         { return pTxtAttr; }


    // returnt den anzuzeigenden String der Fuss-/Endnote
    String GetViewNumStr( const SwDoc& rDoc, BOOL bInclStrs = FALSE ) const;
};


} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
