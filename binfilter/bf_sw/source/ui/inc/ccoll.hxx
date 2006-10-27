/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: ccoll.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 00:33:26 $
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
#ifndef _CCOLL_HXX
#define _CCOLL_HXX

#ifndef _SFXPOOLITEM_HXX //autogen
#include <svtools/poolitem.hxx>
#endif

#ifndef _STRING_HXX //autogen
#include <tools/string.hxx>
#endif

#ifndef _FIXED_HXX //autogen
#include <vcl/fixed.hxx>
#endif

#ifndef _BUTTON_HXX //autogen
#include <vcl/button.hxx>
#endif

#ifndef _SVTABBX_HXX //autogen
#include <svtools/svtabbx.hxx>
#endif

#ifndef _LSTBOX_HXX //autogen
#include <vcl/lstbox.hxx>
#endif

#ifndef _TOOLS_RESARY_HXX
#include <tools/resary.hxx>
#endif

#include "cmdid.h"
namespace binfilter {

class SwWrtShell;
class SwFmt;
class SwCollCondition;


//***********************************************************

struct CollName {
//      const char* pStr;
        ULONG nCnd;
        ULONG nSubCond;
    };

//***********************************************************

#define COND_COMMAND_COUNT 28

struct CommandStruct
{
    ULONG nCnd;
    ULONG nSubCond;
};


//***********************************************************

class SwCondCollItem : public SfxPoolItem
{
    static CommandStruct        aCmds[COND_COMMAND_COUNT];

    String                      sStyles[COND_COMMAND_COUNT];

public:
    SwCondCollItem(USHORT nWhich = FN_COND_COLL);
    ~SwCondCollItem();

                                TYPEINFO();

    virtual SfxPoolItem*        Clone( SfxItemPool *pPool = 0 ) const;
    virtual int                 operator==( const SfxPoolItem& ) const;

    static const CommandStruct* GetCmds();

    const String&               GetStyle(USHORT nPos) const;
    void                        SetStyle( const String* pStyle, USHORT nPos);

};

//***********************************************************

} //namespace binfilter
#endif

