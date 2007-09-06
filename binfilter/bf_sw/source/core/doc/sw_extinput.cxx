/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_extinput.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 12:01:07 $
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



#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif
#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _EXTINPUT_HXX
#include <extinput.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
namespace binfilter {








// die Doc Schnittstellen:



/*N*/ SwExtTextInput* SwDoc::GetExtTextInput( const SwNode& rNd,
/*N*/                                       xub_StrLen nCntntPos ) const
/*N*/ {
/*N*/   SwExtTextInput* pRet = 0;
/*N*/   if( pExtInputRing )
/*N*/   {
/*?*/       ULONG nNdIdx = rNd.GetIndex();
/*?*/       SwExtTextInput* pTmp = (SwExtTextInput*)pExtInputRing;
/*?*/       do {
/*?*/           ULONG nPt = pTmp->GetPoint()->nNode.GetIndex(),
/*?*/                 nMk = pTmp->GetMark()->nNode.GetIndex();
/*?*/           xub_StrLen nPtCnt = pTmp->GetPoint()->nContent.GetIndex(),
/*?*/                      nMkCnt = pTmp->GetMark()->nContent.GetIndex();
/*?*/
/*?*/           if( nPt < nMk || ( nPt == nMk && nPtCnt < nMkCnt ))
/*?*/           {
/*?*/               ULONG nTmp = nMk; nMk = nPt; nPt = nTmp;
/*?*/               nTmp = nMkCnt; nMkCnt = nPtCnt; nPtCnt = (xub_StrLen)nTmp;
/*?*/           }
/*?*/
/*?*/           if( nMk <= nNdIdx && nNdIdx <= nPt &&
/*?*/               ( STRING_NOTFOUND == nCntntPos ||
/*?*/                   ( nMkCnt <= nCntntPos && nCntntPos <= nPtCnt )))
/*?*/           {
/*?*/               pRet = pTmp;
/*?*/               break;
/*?*/           }
/*?*/       } while( pExtInputRing != (pTmp = (SwExtTextInput*)pExtInputRing ) );
/*N*/   }
/*N*/   return pRet;
/*N*/ }



}
