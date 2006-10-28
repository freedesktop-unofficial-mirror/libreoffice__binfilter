/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: editdll.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 03:29:34 $
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

#ifndef _EERDLL_HXX
#define _EERDLL_HXX
namespace binfilter {
class GlobalEditData;
}//end of namespace binfilter
#ifndef _TOOLS_RESID_HXX //autogen
#include <tools/resid.hxx>
#endif

namespace binfilter {

class EditResId: public ResId
{
public:
    EditResId( USHORT nId );
};

class EditDLL
{
    ResMgr*         pResMgr;
    GlobalEditData* pGlobalData;

public:
                    EditDLL();
                    ~EditDLL();

    ResMgr*         GetResMgr() const       { return pResMgr; }
    GlobalEditData* GetGlobalData() const   { return pGlobalData; }
};

#define EE_DLL() (*(EditDLL**)GetAppData( BF_SHL_EDIT ) )

}//end of namespace binfilter
#endif //_EERDLL_HXX
