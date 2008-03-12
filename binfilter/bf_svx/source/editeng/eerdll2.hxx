/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: eerdll2.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 09:25:33 $
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

#ifndef _EERDLL2_HXX
#define _EERDLL2_HXX

#include <forbiddencharacterstable.hxx>
#include <vos/ref.hxx>
namespace binfilter {

class SfxPoolItem;
class SvxAutoCorrect;

class GlobalEditData
{
private:
    SfxPoolItem**   ppDefItems;
    OutputDevice*   pStdRefDevice;

    Link            aGetAutoCorrectHdl;

    vos::ORef<SvxForbiddenCharactersTable>  xForbiddenCharsTable;

public:
                    GlobalEditData();
                    ~GlobalEditData();

    SfxPoolItem**   GetDefItems();
    OutputDevice*   GetStdRefDevice();

    void            SetGetAutoCorrectHdl( const Link& rHdl ) { aGetAutoCorrectHdl = rHdl; }
    SvxAutoCorrect* GetAutoCorrect() const { return (SvxAutoCorrect*) aGetAutoCorrectHdl.Call( NULL ); }

    vos::ORef<SvxForbiddenCharactersTable>  GetForbiddenCharsTable();
    void            SetForbiddenCharsTable( vos::ORef<SvxForbiddenCharactersTable> xForbiddenChars ) { xForbiddenCharsTable = xForbiddenChars; }
};


}//end of namespace binfilter
#endif //_EERDLL2_HXX

