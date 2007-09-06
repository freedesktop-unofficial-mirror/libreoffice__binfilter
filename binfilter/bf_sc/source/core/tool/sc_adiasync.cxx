/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sc_adiasync.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 10:42:12 $
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

#ifdef PCH
#endif

#ifdef _MSC_VER
#pragma hdrstop
#endif

//------------------------------------------------------------------------

#include <bf_sfx2/objsh.hxx>

#include "adiasync.hxx"
#include "document.hxx"
#include "bf_sc.hrc"        // FID_DATACHANGED

#ifndef _OSL_THREAD_H_
#include <osl/thread.h>
#endif
namespace binfilter {


//------------------------------------------------------------------------

#ifdef _MSC_VER
#pragma code_seg("SCSTATICS")
#endif

ScAddInAsyncs theAddInAsyncTbl;
static ScAddInAsync aSeekObj;

#ifdef _MSC_VER
#pragma code_seg()
#endif


/*N*/ SV_IMPL_OP_PTRARR_SORT( ScAddInAsyncs, ScAddInAsyncPtr );

/*N*/ SV_IMPL_PTRARR_SORT( ScAddInDocs, ScAddInDocPtr );




/*N*/ ScAddInAsync::ScAddInAsync() :
/*N*/   SfxBroadcaster(),
/*N*/   nHandle( 0 )
/*N*/ { // nur fuer aSeekObj !
/*N*/ }



/*N*/ ScAddInAsync::ScAddInAsync( ULONG nHandleP, USHORT nIndex, ScDocument* pDoc ) :
/*N*/   SfxBroadcaster(),
/*N*/   pStr( NULL ),
/*N*/   nHandle( nHandleP ),
/*N*/   bValid( FALSE )
/*N*/ {
/*N*/   pDocs = new ScAddInDocs( 1, 1 );
/*N*/   pDocs->Insert( pDoc );
/*N*/   pFuncData = (FuncData*)ScGlobal::GetFuncCollection()->At(nIndex);
/*N*/   eType = pFuncData->GetAsyncType();
/*N*/   theAddInAsyncTbl.Insert( this );
/*N*/ }



/*N*/ ScAddInAsync::~ScAddInAsync()
/*N*/ {
/*N*/   // aSeekObj hat das alles nicht, Handle 0 gibt es sonst nicht
/*N*/   if ( nHandle )
/*N*/   {
/*?*/       // im dTor wg. theAddInAsyncTbl.DeleteAndDestroy in ScGlobal::Clear
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 pFuncData->Unadvice( (double)nHandle );
/*N*/   }
/*N*/ }



/*N*/ ScAddInAsync* ScAddInAsync::Get( ULONG nHandleP )
/*N*/ {
/*N*/   USHORT nPos;
/*N*/   ScAddInAsync* pRet = 0;
/*N*/   aSeekObj.nHandle = nHandleP;
/*N*/   if ( theAddInAsyncTbl.Seek_Entry( &aSeekObj, &nPos ) )
/*N*/       pRet = theAddInAsyncTbl[ nPos ];
/*N*/   aSeekObj.nHandle = 0;
/*N*/   return pRet;
/*N*/ }






/*N*/ void ScAddInAsync::RemoveDocument( ScDocument* pDocumentP )
/*N*/ {
/*N*/   USHORT nPos = theAddInAsyncTbl.Count();
/*N*/   if ( nPos )
/*N*/   {
/*?*/       const ScAddInAsync** ppAsync =
/*?*/           (const ScAddInAsync**) theAddInAsyncTbl.GetData() + nPos - 1;
/*?*/       for ( ; nPos-- >0; ppAsync-- )
/*?*/       {   // rueckwaerts wg. Pointer-Aufrueckerei im Array
/*?*/           ScAddInDocs* p = ((ScAddInAsync*)*ppAsync)->pDocs;
/*?*/           USHORT nFoundPos;
/*?*/           if ( p->Seek_Entry( pDocumentP, &nFoundPos ) )
/*?*/           {
/*?*/               p->Remove( nFoundPos );
/*?*/               if ( p->Count() == 0 )
/*?*/               {   // dieses AddIn wird nicht mehr benutzt
/*?*/                   ScAddInAsync* pAsync = (ScAddInAsync*)*ppAsync;
/*?*/                   theAddInAsyncTbl.Remove( nPos );
/*?*/                   delete pAsync;
/*?*/                   ppAsync = (const ScAddInAsync**) theAddInAsyncTbl.GetData()
/*?*/                       + nPos;
/*?*/               }
/*?*/           }
/*?*/       }
/*N*/   }
/*N*/ }



}
