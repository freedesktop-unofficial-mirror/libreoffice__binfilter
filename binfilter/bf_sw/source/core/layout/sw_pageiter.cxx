/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_pageiter.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 12:21:42 $
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

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#include "doc.hxx"
#include "pagefrm.hxx"
#include "cntfrm.hxx"
#include "pam.hxx"

#ifndef _NODE_HXX //autogen
#include <node.hxx>
#endif
#include "pageiter.hxx"
#include "txtfrm.hxx"
namespace binfilter {




SwPageIter::SwPageIter( const SwDoc &rDoc, const SwPosition &rStartPos )
    : rPDoc( rDoc ), pPage(0)
{
    Seek( rStartPos );
}



BOOL SwPageIter::NextPage()
{
    if( IsEnd() )
        return FALSE;
    pPage = (SwPageFrm*)pPage->GetNext();
    return TRUE;
}



const SwPageDesc* SwPageIter::GetPageDesc() const
{
    return  ( IsEnd() )? 0 : pPage->GetPageDesc();
}



BOOL SwPageIter::Seek( const SwPosition &rPos )
{
    const SwTxtFrm *pTxt = (SwTxtFrm*)rPDoc.GetNodes()[rPos.nNode.GetIndex()]->
                                                GetCntntNode()->GetFrm();
    if ( !pTxt )
        return FALSE;

    pTxt = pTxt->GetFrmAtPos( rPos );
    pPage = pTxt->FindPageFrm();
    return TRUE;
}



BOOL SwPageIter::GetPosition( SwPosition &rPos ) const
{
    if( IsEnd() )
        return FALSE;

    const SwCntntFrm *pCnt = pPage->FindFirstBodyCntnt();
    if ( !pCnt )
        return FALSE;

    pCnt = ((SwTxtFrm*)pCnt)->GetFrmAtPos( rPos );
    if ( !pCnt )
        return FALSE;

    rPos.nNode = *pCnt->GetNode();
    rPos.nContent.Assign( rPos.nNode.GetNode().GetCntntNode(),
                            ((SwTxtFrm*)pCnt)->GetOfst() );

    return TRUE;
}


}
