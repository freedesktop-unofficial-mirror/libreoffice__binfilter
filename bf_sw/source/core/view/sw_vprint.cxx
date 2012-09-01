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


#include <hintids.hxx>

#include <horiornt.hxx>

#include <fesh.hxx>
#include <statstr.hrc>      //      -- " --
#include <ptqueue.hxx>

#include <bf_sfx2/printer.hxx>

namespace binfilter {

#define JOBSET_ERR_DEFAULT          0
#define JOBSET_ERR_ERROR            1
#define JOBSET_ERR_ISSTARTET        2

//--------------------------------------------------------------------
//Klasse zum Puffern von Paints
class SwQueuedPaint
{
public:
    SwQueuedPaint *pNext;
    ViewShell      *pSh;
    SwRect          aRect;

    SwQueuedPaint( ViewShell *pNew, const SwRect &rRect ) :
        pNext( 0 ),
        pSh( pNew ),
        aRect( rRect )
    {}
};

SwQueuedPaint *SwPaintQueue::pQueue = 0;

/*N*/ void SwPaintQueue::Remove( ViewShell *pSh )
/*N*/ {
/*N*/   SwQueuedPaint *pPt;
/*N*/   if ( 0 != (pPt = pQueue) )
/*N*/   {
/*?*/       SwQueuedPaint *pPrev = 0;
/*?*/       while ( pPt && pPt->pSh != pSh )
/*?*/       {
/*?*/           pPrev = pPt;
/*?*/           pPt = pPt->pNext;
/*?*/       }
/*?*/       if ( pPt )
/*?*/       {
/*?*/           if ( pPrev )
/*?*/               pPrev->pNext = pPt->pNext;
/*?*/           else if ( pPt == pQueue )
/*?*/               pQueue = 0;
/*?*/           delete pPt;
/*?*/       }
/*N*/   }
/*N*/ }
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
