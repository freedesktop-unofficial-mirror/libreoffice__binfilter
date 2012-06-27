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
#ifndef _SFX_MISCCFG_HXX
#define _SFX_MISCCFG_HXX


#include <bf_svtools/bf_solar.h>

#include "unotools/configitem.hxx"

namespace binfilter
{

/*--------------------------------------------------------------------
     Beschreibung:
 --------------------------------------------------------------------*/

class  SfxMiscCfg : public utl::ConfigItem
{
    BOOL            bPaperSize;     // printer warnings
    BOOL            bPaperOrientation;
    BOOL            bNotFound;
    sal_Int32       nYear2000;      // two digit year representation

    const com::sun::star::uno::Sequence<rtl::OUString>& GetPropertyNames();
    void                    Load();

public:
    SfxMiscCfg( );
    ~SfxMiscCfg( );

    virtual void            Notify( const com::sun::star::uno::Sequence<rtl::OUString>& aPropertyNames);
    virtual void            Commit();

    BOOL        IsNotFoundWarning()     const {return bNotFound;}

    BOOL        IsPaperSizeWarning()    const {return bPaperSize;}

    BOOL        IsPaperOrientationWarning()     const {return bPaperOrientation;}

                // 0 ... 99
    sal_Int32   GetYear2000()           const { return nYear2000; }
};

}

#endif // _MISCCFG_HXX


/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
