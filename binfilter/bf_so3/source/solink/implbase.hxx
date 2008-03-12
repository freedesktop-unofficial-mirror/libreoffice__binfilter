/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: implbase.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 08:21:41 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
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

