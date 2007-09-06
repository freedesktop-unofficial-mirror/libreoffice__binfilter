/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_ndarr.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 12:04:46 $
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

#ifndef _INDEX_HXX
#include <index.hxx>
#endif
#ifndef _NDARR_HXX
#include <ndarr.hxx>
#endif
namespace binfilter {


void SwNds::Insert(const SwNodePtr &aElement, const SwIndex & aPos)
{
    theArr.Insert((const ElementPtr&) aElement, aPos.GetIndex());
    SwIndexReg::Update(aPos, 1);
}

void SwNds::Insert(const SwNodePtr* pElement, USHORT nLen, const SwIndex & aPos)
{
    theArr.Insert((const ElementPtr*) pElement, nLen, aPos.GetIndex());
    SwIndexReg::Update(aPos, nLen);
}

void SwNds::Remove(const SwIndex & aPos, USHORT nLen)
{
    if(nLen)
    {
        theArr.Remove(aPos.GetIndex(), nLen);
        SwIndexReg::Update(aPos, nLen, TRUE);
    }
}

BOOL SwNds::Move( const SwIndex & rOldPos, const SwIndex & rNewPos )
{
    register USHORT nDelPos = rOldPos.GetIndex(),
                    nInsPos = rNewPos.GetIndex();
    if( nDelPos == nInsPos || nDelPos +1 == nInsPos )
        return FALSE;
    theArr.Move( nDelPos, nInsPos );
    SwIndexReg::MoveIdx( rOldPos, rNewPos );
    return TRUE;
}

}
