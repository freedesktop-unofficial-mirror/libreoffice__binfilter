/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_txtcache.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 12:37:28 $
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


#ifdef _MSC_VER
#pragma hdrstop
#endif

#include "txtcache.hxx"
#include "txtfrm.hxx"
#include "porlay.hxx"
namespace binfilter {

/*************************************************************************
|*
|*  SwTxtLine::SwTxtLine(), ~SwTxtLine()
|*
|*  Ersterstellung      MA 16. Mar. 94
|*  Letzte Aenderung    MA 16. Mar. 94
|*
|*************************************************************************/

/*N*/ SwTxtLine::SwTxtLine( SwTxtFrm *pFrm, SwParaPortion *pNew ) :
/*N*/   SwCacheObj( (void*)pFrm ),
/*N*/   pLine( pNew )
/*N*/ {
/*N*/ }
/*N*/
/*N*/ SwTxtLine::~SwTxtLine()
/*N*/ {
/*N*/   delete pLine;
/*N*/ }

/*************************************************************************
|*
|*  SwTxtLineAccess::NewObj()
|*
|*  Ersterstellung      MA 16. Mar. 94
|*  Letzte Aenderung    MA 16. Mar. 94
|*
|*************************************************************************/

/*N*/ SwCacheObj *SwTxtLineAccess::NewObj()
/*N*/ {
/*N*/   return new SwTxtLine( (SwTxtFrm*)pOwner );
/*N*/ }

/*************************************************************************
|*
|*  SwTxtLineAccess::GetPara()
|*
|*  Ersterstellung      MA 16. Mar. 94
|*  Letzte Aenderung    MA 16. Mar. 94
|*
|*************************************************************************/

/*N*/ SwParaPortion *SwTxtLineAccess::GetPara()
/*N*/ {
/*N*/   SwTxtLine *pRet;
/*N*/   if ( pObj )
/*N*/       pRet = (SwTxtLine*)pObj;
/*N*/   else
/*N*/   {
/*N*/       pRet = (SwTxtLine*)Get();
/*N*/       ((SwTxtFrm*)pOwner)->SetCacheIdx( pRet->GetCachePos() );
/*N*/   }
/*N*/   if ( !pRet->GetPara() )
/*N*/       pRet->SetPara( new SwParaPortion );
/*N*/   return pRet->GetPara();
/*N*/ }


/*************************************************************************
|*
|*  SwTxtLineAccess::SwTxtLineAccess()
|*
|*  Ersterstellung      MA 16. Mar. 94
|*  Letzte Aenderung    MA 16. Mar. 94
|*
|*************************************************************************/

/*N*/ SwTxtLineAccess::SwTxtLineAccess( const SwTxtFrm *pOwner ) :
/*N*/   SwCacheAccess( *SwTxtFrm::GetTxtCache(), pOwner, pOwner->GetCacheIdx() )
/*N*/ {
/*N*/ }

/*************************************************************************
|*
|*  SwTxtLineAccess::IsAvailable
|*
|*  Ersterstellung      MA 23. Mar. 94
|*  Letzte Aenderung    MA 23. Mar. 94
|*
|*************************************************************************/

/*N*/ sal_Bool SwTxtLineAccess::IsAvailable() const
/*N*/ {
/*N*/   if ( pObj )
/*N*/       return ((SwTxtLine*)pObj)->GetPara() != 0;
/*N*/   return sal_False;
/*N*/ }

/*************************************************************************
|*
|*  SwTxtFrm::HasPara()
|*
|*  Ersterstellung      MA 16. Mar. 94
|*  Letzte Aenderung    MA 22. Aug. 94
|*
|*************************************************************************/

/*N*/ sal_Bool SwTxtFrm::_HasPara() const
/*N*/ {
/*N*/   SwTxtLine *pTxtLine = (SwTxtLine*)SwTxtFrm::GetTxtCache()->
/*N*/                                           Get( this, GetCacheIdx(), sal_False );
/*N*/   if ( pTxtLine )
/*N*/   {
/*N*/       if ( pTxtLine->GetPara() )
/*N*/           return sal_True;
/*N*/   }
/*N*/   else
/*N*/       ((SwTxtFrm*)this)->nCacheIdx = MSHRT_MAX;
/*N*/
/*N*/   return sal_False;
/*N*/ }

/*************************************************************************
|*
|*  SwTxtFrm::GetPara()
|*
|*  Ersterstellung      MA 16. Mar. 94
|*  Letzte Aenderung    MA 22. Aug. 94
|*
|*************************************************************************/

/*N*/ SwParaPortion *SwTxtFrm::GetPara()
/*N*/ {
/*N*/   if ( GetCacheIdx() != MSHRT_MAX )
/*N*/   {   SwTxtLine *pLine = (SwTxtLine*)SwTxtFrm::GetTxtCache()->
/*N*/                                       Get( this, GetCacheIdx(), sal_False );
/*N*/       if ( pLine )
/*N*/           return pLine->GetPara();
/*N*/       else
/*N*/           nCacheIdx = MSHRT_MAX;
/*N*/   }
/*N*/   return 0;
/*N*/ }


/*************************************************************************
|*
|*  SwTxtFrm::ClearPara()
|*
|*  Ersterstellung      MA 16. Mar. 94
|*  Letzte Aenderung    MA 22. Aug. 94
|*
|*************************************************************************/

/*N*/ void SwTxtFrm::ClearPara()
/*N*/ {
/*N*/   ASSERT( !IsLocked(), "+SwTxtFrm::ClearPara: this is locked." );
/*N*/   if ( !IsLocked() && GetCacheIdx() != MSHRT_MAX )
/*N*/   {
/*N*/       SwTxtLine *pTxtLine = (SwTxtLine*)SwTxtFrm::GetTxtCache()->
/*N*/                                       Get( this, GetCacheIdx(), sal_False );
/*N*/       if ( pTxtLine )
/*N*/       {
/*N*/           delete pTxtLine->GetPara();
/*N*/           pTxtLine->SetPara( 0 );
/*N*/       }
/*N*/       else
/*N*/           nCacheIdx = MSHRT_MAX;
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|*  SwTxtFrm::SetPara()
|*
|*  Ersterstellung      MA 16. Mar. 94
|*  Letzte Aenderung    MA 22. Aug. 94
|*
|*************************************************************************/

/*N*/ void SwTxtFrm::SetPara( SwParaPortion *pNew, sal_Bool bDelete )
/*N*/ {
/*N*/   if ( GetCacheIdx() != MSHRT_MAX )
/*N*/   {
/*N*/       //Nur die Information Auswechseln, das CacheObj bleibt stehen.
/*N*/       SwTxtLine *pTxtLine = (SwTxtLine*)SwTxtFrm::GetTxtCache()->
/*N*/                                       Get( this, GetCacheIdx(), sal_False );
/*N*/       if ( pTxtLine )
/*N*/       {
/*N*/           if( bDelete )
/*N*/               delete pTxtLine->GetPara();
/*N*/           pTxtLine->SetPara( pNew );
/*N*/       }
/*N*/       else
/*N*/       {
/*?*/           ASSERT( !pNew, "+SetPara: Losing SwParaPortion" );
/*?*/           nCacheIdx = MSHRT_MAX;
/*N*/       }
/*N*/   }
/*N*/   else if ( pNew )
/*N*/   {   //Einen neuen einfuegen.
/*N*/       SwTxtLine *pTxtLine = new SwTxtLine( this, pNew );
/*N*/       if ( SwTxtFrm::GetTxtCache()->Insert( pTxtLine ) )
/*N*/           nCacheIdx = pTxtLine->GetCachePos();
/*N*/       else
/*N*/       {
/*?*/           ASSERT( sal_False, "+SetPara: InsertCache failed." );
/*N*/       }
/*N*/   }
/*N*/ }
/*N*/
/*N*/
}
