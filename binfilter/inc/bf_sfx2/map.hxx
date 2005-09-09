/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: map.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 12:24:31 $
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
#ifndef _SFX_MAP_HXX
#define _SFX_MAP_HXX

#include <tools.hxx>
#include <sfxitems.hxx>
namespace binfilter {

class SfxInterface;
class SfxDispatcher;
class SfxShell;

class SfxMap: public SfxWhichMap
{
    const SfxInterface  *pInterface;
    const SfxDispatcher *pDispatcher;
    BOOL                bRecursive;
public:
    inline              SfxMap();
    inline              SfxMap(const SfxDispatcher &rDispatcher );
                        SfxMap(const SfxShell &, BOOL bRecursiveSearch = FALSE );
    inline              SfxMap( const SfxMap & rMap);

    virtual USHORT      GetWhich(USHORT nSlot) const;
    virtual USHORT      GetSlot(USHORT nWhich) const;
    virtual SfxWhichMap*Clone() const;
};

//--------------------------------------------------------------------

inline SfxMap::SfxMap():
        SfxWhichMap( FALSE ),
        pInterface( 0 ),
        pDispatcher( 0 ),
        bRecursive( FALSE )
{
}

inline SfxMap::SfxMap( const SfxMap & rMap):
        SfxWhichMap( TRUE ),
        pInterface( rMap.pInterface ),
        pDispatcher( rMap.pDispatcher ),
        bRecursive( rMap.bRecursive )
{
}

inline SfxMap::SfxMap(const SfxDispatcher &rDispatcher ):
        SfxWhichMap( TRUE ),
        pInterface( 0 ),
        pDispatcher( &rDispatcher ),
        bRecursive( 0 )
{
}

}//end of namespace binfilter
#endif

