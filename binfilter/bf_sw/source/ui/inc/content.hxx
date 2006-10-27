/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: content.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 00:36:16 $
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
#ifndef _CONTENT_HXX
#define _CONTENT_HXX

#include <limits.h>     // USHRT_MAX
#ifndef _SWCONT_HXX
#include "swcont.hxx"
#endif

#ifndef _MENU_HXX //autogen
#include <vcl/menu.hxx>
#endif
namespace binfilter {

class SwWrtShell;
class SwContentArr;
class SwContentType;
class SwNavigationPI;
class SwFmtFld;
class SwTxtINetFmt;
class SwDocShell;
class SvDataObject;
class SwTOXBase;

//----------------------------------------------------------------------------
//  Hilfsklassen
//----------------------------------------------------------------------------

class SwPopup : public PopupMenu
{
    USHORT          nCurId;
    virtual void    Select(){nCurId = GetCurItemId();}

public:
    SwPopup() :
        PopupMenu(),
        nCurId(USHRT_MAX){}

    USHORT          GetCurId() const { return nCurId; }

};

//----------------------------------------------------------------------------

class SwOutlineContent : public SwContent
{
    USHORT  nOutlinePos;
    BYTE    nOutlineLevel;
    BOOL    bIsMoveable;
    public:
        SwOutlineContent(   const SwContentType* pCnt,
                            const String& rName,
                            USHORT nArrPos,
                            BYTE nLevel,
                            BOOL bMove,
                            long nYPos) :
            SwContent(pCnt, rName, nYPos), nOutlineLevel(nLevel),
                        nOutlinePos(nArrPos), bIsMoveable(bMove){}

    USHORT  GetPos(){return nOutlinePos;}
    BYTE    GetOutlineLevel(){return nOutlineLevel;}
    BOOL    IsMoveable(){return bIsMoveable;};
};

//----------------------------------------------------------------------------
class SwRegionContent : public SwContent
{

    BYTE    nRegionLevel;

    public:
        SwRegionContent(    const SwContentType* pCnt,
                            const String& rName,
                            BYTE nLevel,
                            long nYPos) :
            SwContent(pCnt, rName, nYPos),
                        nRegionLevel(nLevel){}
    BYTE    GetRegionLevel() const {return nRegionLevel;}
};
//----------------------------------------------------------------------------




//----------------------------------------------------------------------------



//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
/*
    class ContentType enthaelt Informationen zu einer Inhaltsform
    Das MemberArray wird nur gefuellt, wenn der Inhalt mit GetMember
    angefordert wird. Es wird nach Invalidate() nur dann neu geladen,
    wenn der Inhalt erneut ausgelesen werden soll.
*/
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------






} //namespace binfilter
#endif

