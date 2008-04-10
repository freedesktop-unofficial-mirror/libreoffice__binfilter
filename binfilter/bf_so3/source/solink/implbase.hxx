/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: implbase.hxx,v $
 * $Revision: 1.4 $
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/

#ifndef _IMPLBASE_HXX
#define _IMPLBASE_HXX

#include <tools/solar.h>

namespace binfilter {

class  ImplDdeItem;
struct Impl_LinkInfo;

// nur fuer die interne Verwaltung
struct ImplBaseLinkData
{
    union {
        struct
        {
            // gilt fuer alle Links
            ULONG               nCntntType; // Update Format
            Impl_LinkInfo *     pLinkInfo;  // Information fuer Ole-Link

            // nicht Ole-Links
            BOOL            bIntrnlLnk; // ist es ein interner Link
            USHORT          nUpdateMode;// UpdateMode
        } ClientType;

        struct
        {
            ImplDdeItem* pItem;
        } DDEType;

        // und hier fuer So
        //struct
        //{
        //} SoType;
    };

    ImplBaseLinkData()
    {
        ClientType.nCntntType = NULL;
        ClientType.pLinkInfo = NULL;
        ClientType.bIntrnlLnk = FALSE;
        ClientType.nUpdateMode = 0;
        DDEType.pItem = NULL;
    }
};


}

#endif

