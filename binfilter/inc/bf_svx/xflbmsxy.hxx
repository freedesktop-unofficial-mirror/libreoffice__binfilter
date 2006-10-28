/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xflbmsxy.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 04:26:46 $
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

#ifndef _SVX_XFLBMSXY_HXX
#define _SVX_XFLBMSXY_HXX

#ifndef _SFXMETRICITEM_HXX //autogen
#include <svtools/metitem.hxx>
#endif
namespace binfilter {

/*************************************************************************
|*
|*
|*
\************************************************************************/

class XFillBmpSizeXItem : public SfxMetricItem
{
public:
                            TYPEINFO();
                            XFillBmpSizeXItem( long nSizeX = 0 );
                            XFillBmpSizeXItem( SvStream& rIn );

    virtual SfxPoolItem*    Clone( SfxItemPool* pPool = 0 ) const;
    virtual SfxPoolItem*    Create( SvStream& rIn, USHORT nVer ) const;


    // Dieses Item nimmt sowohl metrische als auch
    // Prozentwerte ( sind negativ ) auf; das muessen
    // wir hier beruecksichtigen
};

/*************************************************************************
|*
|*
|*
\************************************************************************/

class XFillBmpSizeYItem : public SfxMetricItem
{
public:
                            TYPEINFO();
                            XFillBmpSizeYItem( long nSizeY = 0 );
                            XFillBmpSizeYItem( SvStream& rIn );

    virtual SfxPoolItem*    Clone( SfxItemPool* pPool = 0 ) const;
    virtual SfxPoolItem*    Create( SvStream& rIn, USHORT nVer ) const;


    // Dieses Item nimmt sowohl metrische als auch
    // Prozentwerte ( sind negativ ) auf; das muessen
    // wir hier beruecksichtigen
};

}//end of namespace binfilter
#endif
