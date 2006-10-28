/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: fwdtitem.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 03:35:54 $
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
#ifndef _SVX_FWDTITEM_HXX
#define _SVX_FWDTITEM_HXX

// include ---------------------------------------------------------------

#ifndef _SFXPOOLITEM_HXX //autogen
#include <svtools/poolitem.hxx>
#endif
#ifndef   ITEMID_FONTWIDTH
#define   ITEMID_FONTWIDTH 0
#endif
namespace binfilter {

// class SvxFontWidthItem -----------------------------------------------

/*  [Beschreibung]

    Dieses Item beschreibt die Font-Breite.
*/

class SvxFontWidthItem : public SfxPoolItem
{
    UINT16  nWidth;         // 0 = default
    USHORT  nProp;          // default 100%
public:

    SvxFontWidthItem(   const USHORT nSz = 0,
                        const USHORT nPropWidth = 100,
                        const USHORT nId = ITEMID_FONTWIDTH );


    UINT16 GetWidth() const { return nWidth; }

};

}//end of namespace binfilter
#endif

