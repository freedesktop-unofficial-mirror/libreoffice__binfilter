/*************************************************************************
 *
 *  $RCSfile: sc_bclist.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: aw $ $Date: 2004-02-27 18:54:39 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/

#ifdef PCH
#include "core_pch.hxx"
#endif

#pragma hdrstop

//------------------------------------------------------------------

#include <svtools/brdcst.hxx>
#include <svtools/lstner.hxx>
#include <tools/list.hxx>

#include "bclist.hxx"
namespace binfilter {

//------------------------------------------------------------------------

#define SC_LISTENERS_MAX 1024

/*N*/ DECLARE_LIST(ScBroadcasters, SfxBroadcaster*)//STRIP008 ;

//------------------------------------------------------------------------

/*N*/ ScBroadcasterList::ScBroadcasterList() :
/*N*/   pMoreBCs( NULL )
/*N*/ {
/*N*/ }

/*N*/ ScBroadcasterList::~ScBroadcasterList()
/*N*/ {
/*N*/   if (pMoreBCs)
/*N*/   {
/*?*/       ULONG nCount = pMoreBCs->Count();
/*?*/       for (ULONG i=0; i<nCount; i++)
/*?*/       {
/*?*/           SfxBroadcaster* pBC = pMoreBCs->GetObject(i);
/*?*/           delete pBC;
/*?*/       }
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
/*?*/           ULONG nCount = pMoreBCs->Count();
/*?*/           for (ULONG i=0; i<nCount; i++)
/*?*/           {
/*?*/               SfxBroadcaster* pBC = pMoreBCs->GetObject(i);
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
/*?*/       ULONG nCount = pMoreBCs->Count();
/*?*/       for (ULONG i=0; i<nCount; i++)
/*?*/       {
/*?*/           SfxBroadcaster* pBC = pMoreBCs->GetObject(i);
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
/*N*/   pMoreBCs->Insert(pNew, (ULONG)0);   // vorne
/*N*/ }

/*N*/ void ScBroadcasterList::EndBroadcasting( SfxListener& rLst )
/*N*/ {
/*N*/   rLst.EndListening(aFirstBC);
/*N*/   if (pMoreBCs)
/*N*/   {
/*?*/       ULONG nCount = pMoreBCs->Count();
/*?*/       for (ULONG i=0; i<nCount; i++)
/*?*/       {
/*?*/           SfxBroadcaster* pBC = pMoreBCs->GetObject(i);
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
/*?*/       ULONG nCount = pMoreBCs->Count();
/*?*/       for (ULONG i=0; i<nCount; i++)
/*?*/       {
/*?*/           SfxBroadcaster* pBC = pMoreBCs->GetObject(i);
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
/*?*/       ULONG nCount = pMoreBCs->Count();
/*?*/       for (ULONG i=0; i<nCount; i++)
/*?*/       {
/*?*/           SfxBroadcaster* pBC = pMoreBCs->GetObject(i);
/*?*/           pBC->Broadcast( rHint );
/*?*/       }
/*N*/   }
/*N*/ }

/*N*/ void ScBroadcasterList::MoveListenersTo( ScBroadcasterList& rNew )
/*N*/ {
/*N*/   SfxBroadcaster* pNewBC = &rNew.aFirstBC;
/*N*/
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
/*N*/       ULONG nBCCount = pMoreBCs->Count();
/*N*/       for (ULONG i=0; i<nBCCount; i++)
/*N*/       {
/*N*/           SfxBroadcaster* pBC = pMoreBCs->GetObject(i);
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
