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

#ifndef SC_STLSHEET_HXX
#define SC_STLSHEET_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_svtools/style.hxx>
namespace binfilter {

//------------------------------------------------------------------------

#define SCSTYLEBIT_STANDARD     0x0001

//------------------------------------------------------------------------

class ScStyleSheetPool;

class ScStyleSheet : public SfxStyleSheet
{
friend class ScStyleSheetPool;

public:

    enum    Usage
    {
        UNKNOWN,
        USED,
        NOTUSED
    };

private:
    mutable ScStyleSheet::Usage eUsage;

public:
                        TYPEINFO();
    virtual             ~ScStyleSheet();

                        ScStyleSheet( const ScStyleSheet& rStyle );

    virtual BOOL        SetParent        ( const String& rParentName );
    virtual SfxItemSet& GetItemSet       ();
    virtual BOOL        IsUsed           () const;

    virtual const String& GetName() const;
    virtual const String& GetParent() const;
    virtual const String& GetFollow() const;

    virtual BOOL SetName( const String& );

            void                SetUsage( ScStyleSheet::Usage eUse ) const
                                    { eUsage = eUse; }
            ScStyleSheet::Usage GetUsage() const
                                    { return eUsage; }

protected:
                ScStyleSheet( const String&     rName,
                              ScStyleSheetPool& rPool,
                              SfxStyleFamily    eFamily,
                              USHORT            nMask );

    virtual void SFX_NOTIFY( SfxBroadcaster& rBC, const TypeId& rBCType,
                         const SfxHint& rHint, const TypeId& rHintType );
};

} //namespace binfilter
#endif     // SC_STLSHEET_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
