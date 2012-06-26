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

#ifdef _MSC_VER
#pragma hdrstop
#endif

//------------------------------------------------------------------

#include <bf_svtools/lstner.hxx>
#include <vector>

#include "bclist.hxx"
namespace binfilter {

//------------------------------------------------------------------------

#define SC_LISTENERS_MAX 1024

typedef ::std::vector< SfxBroadcaster* > ScBroadcasters;

//------------------------------------------------------------------------

/*N*/ ScBroadcasterList::ScBroadcasterList() :
/*N*/   pMoreBCs( NULL )
/*N*/ {
/*N*/ }

/*N*/ ScBroadcasterList::~ScBroadcasterList()
/*N*/ {
/*N*/   if (pMoreBCs)
/*N*/   {
/*?*/       size_t nCount = pMoreBCs->size();
/*?*/       for (size_t i = 0; i < nCount; i++)
/*?*/           delete (*pMoreBCs)[ i ];
/*?*/       delete pMoreBCs;
/*N*/   }
/*N*/ }

/*N*/ void ScBroadcasterList::StartBroadcasting( SfxListener& rLst, BOOL bCheckDup )
/*N*/ {
/*N*/   if (bCheckDup)
/*N*/   {
/*N*/       if (rLst.IsListening(aFirstBC))
/*N*/           return;
/*N*/       if (pMoreBCs)
/*N*/       {
/*?*/           size_t nCount = pMoreBCs->size();
/*?*/           for (size_t i = 0; i < nCount; i++)
/*?*/           {
/*?*/               SfxBroadcaster* pBC = (*pMoreBCs)[ i ];
/*?*/               if (rLst.IsListening(*pBC))
/*?*/                   return;
/*?*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if ( aFirstBC.GetListenerCount() < SC_LISTENERS_MAX )
/*N*/   {
/*N*/       rLst.StartListening(aFirstBC, FALSE);
/*N*/       return;
/*N*/   }
/*N*/   if (pMoreBCs)
/*N*/   {
/*?*/       size_t nCount = pMoreBCs->size();
/*?*/       for (size_t i = 0; i < nCount; i++)
/*?*/       {
/*?*/           SfxBroadcaster* pBC = (*pMoreBCs)[ i ];
/*?*/           if ( pBC->GetListenerCount() < SC_LISTENERS_MAX )
/*?*/           {
/*?*/               rLst.StartListening(*pBC, FALSE);
/*?*/               return;
/*?*/           }
/*?*/       }
/*N*/   }
/*N*/   if (!pMoreBCs)
/*?*/       pMoreBCs = new ScBroadcasters;
/*N*/   SfxBroadcaster* pNew = new SfxBroadcaster;
/*N*/   rLst.StartListening(*pNew, FALSE);
/*N*/   pMoreBCs->insert( pMoreBCs->begin(), pNew );    // vorne
/*N*/ }

/*N*/ void ScBroadcasterList::EndBroadcasting( SfxListener& rLst )
/*N*/ {
/*N*/   rLst.EndListening(aFirstBC);
/*N*/   if (pMoreBCs)
/*N*/   {
/*?*/       size_t nCount = pMoreBCs->size();
/*?*/       for (size_t i = 0; i < nCount; i++)
/*?*/       {
/*?*/           SfxBroadcaster* pBC = (*pMoreBCs)[ i ];
/*?*/           rLst.EndListening(*pBC);
/*?*/       }
/*N*/   }
/*N*/ }

/*N*/ BOOL ScBroadcasterList::HasListeners() const
/*N*/ {
/*N*/   if (aFirstBC.HasListeners())
/*N*/       return TRUE;
/*N*/   if (pMoreBCs)
/*N*/   {
/*?*/       size_t nCount = pMoreBCs->size();
/*?*/       for (size_t i = 0; i < nCount; i++)
/*?*/       {
/*?*/           SfxBroadcaster* pBC = (*pMoreBCs)[ i ];
/*?*/           if (pBC->HasListeners())
/*?*/               return TRUE;
/*?*/       }
/*N*/   }
/*N*/   return FALSE;
/*N*/ }

/*N*/ void ScBroadcasterList::Broadcast( const SfxHint &rHint )
/*N*/ {
/*N*/   aFirstBC.Broadcast( rHint );
/*N*/   if (pMoreBCs)
/*N*/   {
/*?*/       size_t nCount = pMoreBCs->size();
/*?*/       for (size_t i = 0; i < nCount; i++)
/*?*/       {
/*?*/           SfxBroadcaster* pBC = (*pMoreBCs)[ i  ];
/*?*/           pBC->Broadcast( rHint );
/*?*/       }
/*N*/   }
/*N*/ }

/*N*/ void ScBroadcasterList::MoveListenersTo( ScBroadcasterList& rNew )
/*N*/ {
/*N*/   USHORT nLstCount, nLstPos;
/*N*/   nLstCount = aFirstBC.GetListenerCount();
/*N*/   for (nLstPos=nLstCount; nLstPos>0;)
/*N*/   {
/*N*/       --nLstPos;
/*N*/       SfxListener* pLst = aFirstBC.GetListener(nLstPos);
/*N*/       rNew.StartBroadcasting(*pLst, TRUE);
/*N*/       pLst->EndListening(aFirstBC);
/*N*/   }
/*N*/   if (pMoreBCs)
/*N*/   {
/*N*/       size_t nBCCount = pMoreBCs->size();
/*N*/       for (size_t i = 0; i < nBCCount; i++)
/*N*/       {
/*N*/           SfxBroadcaster* pBC = (*pMoreBCs)[ i ];
/*N*/           nLstCount = pBC->GetListenerCount();
/*N*/           for (nLstPos=nLstCount; nLstPos>0;)
/*N*/           {
/*N*/               --nLstPos;
/*N*/               SfxListener* pLst = pBC->GetListener(nLstPos);
/*N*/               rNew.StartBroadcasting(*pLst, TRUE);
/*N*/               pLst->EndListening(*pBC);
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }




}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
