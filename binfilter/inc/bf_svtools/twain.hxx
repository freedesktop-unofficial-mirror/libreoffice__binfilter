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

#ifndef _TWAIN_HXX
#define _TWAIN_HXX

#include <bf_svtools/bf_solar.h>

// please add new platforms if TWAIN is available
#if defined WIN || defined WNT || defined UNX
#define TWAIN_AVAILABLE 1
#else
#undef  TWAIN_AVAILABLE
#endif

// include following only, if define is not set
#ifndef _TWAIN_HXX_CHECK

#include <vcl/bitmap.hxx>

// -----------
// - Defines -
// -----------

#define TWAIN_ERR_NO_ERROR                  0
#define TWAIN_ERR_MODULE_NOT_LOADED         2
#define TWAIN_ERR_DSMENTRY_NOT_FOUND        4
#define TWAIN_ERR_SOURCE_MANAGER_NOT_OPENED 6
#define TWAIN_ERR_SOURCE_SELECTION_DIALOG   8

// ---------
// - Twain -
// ---------

namespace com { namespace sun { namespace star { namespace lang { struct EventObject; } } } }

namespace binfilter
{

struct TwainImp;
class Twain
{
friend class TwainEventListener;

private:

    TwainImp*           mpImp;

    Bitmap              maBitmap;
    Link                maUpdateLink;
    USHORT              mnErrorCode;
    BOOL                mbScanning;

                        Twain();
                        Twain( const Twain& rTwain );
    const Twain&        operator=( const Twain& rTwain ) { return *this; }

protected:

    void                Disposing( const com::sun::star::lang::EventObject& rEventObject );

public:

                        Twain( const Link& rUpdateLink );
                        ~Twain();

    BOOL                SelectSource();
    BOOL                PerformTransfer();

    Bitmap              GetBitmap();

    BOOL                IsScanning() const { return mbScanning; }
    USHORT              GetErrorCode() const { return mnErrorCode; }
};

}
#endif // _TWAIN_HXX_CHECK
#endif // _TWAIN_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
