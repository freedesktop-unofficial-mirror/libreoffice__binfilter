/*************************************************************************
 *
 *  $RCSfile: sw_pageiter.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 15:27:08 $
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


#pragma hdrstop

#include "doc.hxx"
#include "pagefrm.hxx"
#include "cntfrm.hxx"
#include "pam.hxx"

#ifndef _NODE_HXX //autogen
#include <node.hxx>
#endif
#include "pageiter.hxx"
#include "txtfrm.hxx"




//STRIP001 SwPageIter::SwPageIter( const SwDoc &rDoc, const SwPosition &rStartPos )
//STRIP001  : rPDoc( rDoc ), pPage(0)
//STRIP001 {
//STRIP001  Seek( rStartPos );
//STRIP001 }



//STRIP001 BOOL SwPageIter::NextPage()
//STRIP001 {
//STRIP001  if( IsEnd() )
//STRIP001      return FALSE;
//STRIP001  pPage = (SwPageFrm*)pPage->GetNext();
//STRIP001  return TRUE;
//STRIP001 }



//STRIP001 const SwPageDesc* SwPageIter::GetPageDesc() const
//STRIP001 {
//STRIP001  return  ( IsEnd() )? 0 : pPage->GetPageDesc();
//STRIP001 }



//STRIP001 BOOL SwPageIter::Seek( const SwPosition &rPos )
//STRIP001 {
//STRIP001  const SwTxtFrm *pTxt = (SwTxtFrm*)rPDoc.GetNodes()[rPos.nNode.GetIndex()]->
//STRIP001                                              GetCntntNode()->GetFrm();
//STRIP001  if ( !pTxt )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  pTxt = pTxt->GetFrmAtPos( rPos );
//STRIP001  pPage = pTxt->FindPageFrm();
//STRIP001  return TRUE;
//STRIP001 }



//STRIP001 BOOL SwPageIter::GetPosition( SwPosition &rPos ) const
//STRIP001 {
//STRIP001  if( IsEnd() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  const SwCntntFrm *pCnt = pPage->FindFirstBodyCntnt();
//STRIP001  if ( !pCnt )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  pCnt = ((SwTxtFrm*)pCnt)->GetFrmAtPos( rPos );
//STRIP001  if ( !pCnt )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  rPos.nNode = *pCnt->GetNode();
//STRIP001  rPos.nContent.Assign( rPos.nNode.GetNode().GetCntntNode(),
//STRIP001                          ((SwTxtFrm*)pCnt)->GetOfst() );
//STRIP001
//STRIP001  return TRUE;
//STRIP001 }

/*
#ifdef NIE
{
    SwPageIter aIter( MyDoc );

    while( !aIter.IsEnd() )
    {
        SwPosition MyPos( aIter.GetPos() );
        (...)
        aIter.NextPage();
    }
}

#endif // NIE
*/




