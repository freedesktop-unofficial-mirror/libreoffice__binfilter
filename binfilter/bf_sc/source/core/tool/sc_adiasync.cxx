/*************************************************************************
 *
 *  $RCSfile: sc_adiasync.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:26:25 $
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

//------------------------------------------------------------------------

#include <bf_sfx2/objsh.hxx>

#include "adiasync.hxx"
#include "brdcst.hxx"
#include "global.hxx"
#include "document.hxx"
#include "bf_sc.hrc"        // FID_DATACHANGED

#ifndef _OSL_THREAD_H_
#include <osl/thread.h>
#endif
namespace binfilter {


//------------------------------------------------------------------------

#pragma code_seg("SCSTATICS")

ScAddInAsyncs theAddInAsyncTbl;
static ScAddInAsync aSeekObj;

#pragma code_seg()


/*N*/ SV_IMPL_OP_PTRARR_SORT( ScAddInAsyncs, ScAddInAsyncPtr );

/*N*/ SV_IMPL_PTRARR_SORT( ScAddInDocs, ScAddInDocPtr );

//STRIP001 extern "C" {
//STRIP001 void CALLTYPE ScAddInAsyncCallBack( double& nHandle, void* pData )
//STRIP001 {
//STRIP001  ScAddInAsync::CallBack( ULONG( nHandle ), pData );
//STRIP001 }
//STRIP001 }



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
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001 pFuncData->Unadvice( (double)nHandle );
//STRIP001 /*?*/        if ( eType == PTR_STRING && pStr )      // mit Typvergleich wg. Union!
//STRIP001 /*?*/            delete pStr;
//STRIP001 /*?*/        delete pDocs;
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



//STRIP001 void ScAddInAsync::CallBack( ULONG nHandleP, void* pData )
//STRIP001 {
//STRIP001  ScAddInAsync* p;
//STRIP001  if ( !(p = Get( nHandleP )) )
//STRIP001      return;
//STRIP001  // keiner mehr dran? Unadvice und weg damit
//STRIP001  if ( !p->HasListeners() )
//STRIP001  {
//STRIP001      // nicht im dTor wg. theAddInAsyncTbl.DeleteAndDestroy in ScGlobal::Clear
//STRIP001      theAddInAsyncTbl.Remove( p );
//STRIP001      delete p;
//STRIP001      return ;
//STRIP001  }
//STRIP001  switch ( p->eType )
//STRIP001  {
//STRIP001      case PTR_DOUBLE :
//STRIP001          p->nVal = *(double*)pData;
//STRIP001          break;
//STRIP001      case PTR_STRING :
//STRIP001          if ( p->pStr )
//STRIP001              *p->pStr = String( (sal_Char*)pData, osl_getThreadTextEncoding() );
//STRIP001          else
//STRIP001              p->pStr = new String( (sal_Char*)pData, osl_getThreadTextEncoding() );
//STRIP001          break;
//STRIP001      default :
//STRIP001          DBG_ERROR( "unbekannter AsyncType" );
//STRIP001          return;
//STRIP001  }
//STRIP001  p->bValid = TRUE;
//STRIP001  p->Broadcast( ScHint( SC_HINT_DATACHANGED, ScAddress( 0 ), NULL ) );
//STRIP001
//STRIP001  const ScDocument** ppDoc = (const ScDocument**) p->pDocs->GetData();
//STRIP001  USHORT nCount = p->pDocs->Count();
//STRIP001  for ( USHORT j=0; j<nCount; j++, ppDoc++ )
//STRIP001  {
//STRIP001      ScDocument* pDoc = (ScDocument*)*ppDoc;
//STRIP001      pDoc->TrackFormulas();
//STRIP001      pDoc->GetDocumentShell()->Broadcast( SfxSimpleHint( FID_DATACHANGED ) );
//STRIP001      pDoc->ResetChanged( ScRange(0,0,0,MAXCOL,MAXROW,MAXTAB) );
//STRIP001  }
//STRIP001 }



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
