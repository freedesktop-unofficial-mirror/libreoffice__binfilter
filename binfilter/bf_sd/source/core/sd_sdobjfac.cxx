/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sd_sdobjfac.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 11:20:56 $
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


#include "sdpage.hxx"
#include "sdobjfac.hxx"
#include "anminfo.hxx"
#include "imapinfo.hxx"
namespace binfilter {


SdObjectFactory aSdObjectFactory;

/*************************************************************************
|*
|* void SdObjectFactory::MakeUserData()
|*
\************************************************************************/

/*N*/ IMPL_LINK( SdObjectFactory, MakeUserData, SdrObjFactory *, pObjFactory )
/*N*/ {
/*N*/   if ( pObjFactory->nInventor == SdUDInventor )
/*N*/   {
/*N*/       SdrObject* pObj = pObjFactory->pObj;
/*N*/
/*N*/       switch( pObjFactory->nIdentifier )
/*N*/       {
/*N*/           case( SD_ANIMATIONINFO_ID ):
/*N*/           {
/*N*/               SdDrawDocument* pDoc = NULL;
/*N*/
/*N*/               if ( pObj )
/*N*/                   pDoc = (SdDrawDocument*) pObj->GetModel();
/*N*/
/*N*/               DBG_ASSERT(pDoc, "kein Model gefunden");
/*N*/
/*N*/               pObjFactory->pNewData = new SdAnimationInfo(pDoc);
/*N*/           }
/*N*/           break;
/*?*/
/*?*/           case( SD_IMAPINFO_ID ):
/*?*/               pObjFactory->pNewData = new SdIMapInfo;
/*?*/           break;
/*N*/
/*N*/           default:
/*N*/           break;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if ( pObjFactory->pNewData )
/*N*/       return 0;
/*N*/
/*N*/   if( aOldMakeUserDataLink.IsSet() )
/*?*/       aOldMakeUserDataLink.Call( this );
/*N*/
/*N*/   return 0;
/*N*/ }


}
