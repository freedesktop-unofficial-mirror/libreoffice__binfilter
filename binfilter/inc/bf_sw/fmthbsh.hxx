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
#ifndef _FMTHBSH_HXX
#define _FMTHBSH_HXX

#include <bf_svtools/bf_solar.h>


#include <bf_svtools/poolitem.hxx>
namespace binfilter {

// ATT_SOFTHYPH ******************************
// Attribut fuer benutzerdefinierte Trennstellen.

class SwFmtSoftHyph : public SfxPoolItem
{
public:
    SwFmtSoftHyph();

    // "pure virtual Methoden" vom SfxPoolItem
    virtual int operator==( const SfxPoolItem& ) const{DBG_BF_ASSERT(0, "STRIP"); return 0;};
    virtual SfxPoolItem*    Clone( SfxItemPool* /*pPool = 0*/ ) const{DBG_BF_ASSERT(0, "STRIP");return NULL; };
    virtual SfxPoolItem*    Create(SvStream &, USHORT nVer) const;
    virtual SvStream&       Store(SvStream &rStream, USHORT) const { return rStream; }

    inline SwFmtSoftHyph& operator=(const SwFmtSoftHyph& /*rSH*/) {
            return *this;
        }
};

// ATT_HARDBLANK ******************************
// Attribut fuer geschuetzte Leerzeichen.

class SwFmtHardBlank : public SfxPoolItem
{
    sal_Unicode cChar;
public:
    SwFmtHardBlank( sal_Unicode cCh, BOOL bCheck = TRUE );

    // "pure virtual Methoden" vom SfxPoolItem
    virtual int             operator==( const SfxPoolItem& ) const{DBG_BF_ASSERT(0, "STRIP"); return 0;};
    virtual SfxPoolItem*    Clone( SfxItemPool* /*pPool = 0*/ ) const{DBG_BF_ASSERT(0, "STRIP"); return NULL;};
    virtual SfxPoolItem*    Create(SvStream &, USHORT nVer) const;
    virtual SvStream&       Store(SvStream &rStream, USHORT) const { return rStream; }

    virtual USHORT           GetVersion( USHORT nFFVer ) const;

    inline sal_Unicode GetChar() const { return cChar; }
    inline SwFmtHardBlank& operator=(const SwFmtHardBlank& rHB)
    { cChar = rHB.GetChar(); return *this; }
};


} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
