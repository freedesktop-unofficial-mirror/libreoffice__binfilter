/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sxmfsitm.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 13:16:07 $
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
#ifndef _SXMFSITM_HXX
#define _SXMFSITM_HXX

#ifndef _SVDDEF_HXX //autogen
#include <bf_svx/svddef.hxx>
#endif

#ifndef _SFXSTRITEM_HXX //autogen
#include <bf_svtools/stritem.hxx>
#endif
namespace binfilter {

// Formatstring (aehnl. Calc), z.B. "#.###,00km"
// ueberschreibt SdrMeasureUnitItem und SdrMeasureShowUnitItem (n.i.)
class SdrMeasureFormatStringItem: public SfxStringItem {
public:
    SdrMeasureFormatStringItem()                   : SfxStringItem() { SetWhich(SDRATTR_MEASUREFORMATSTRING); }
    SdrMeasureFormatStringItem(const String& rStr) : SfxStringItem(SDRATTR_MEASUREFORMATSTRING,rStr) {}
    SdrMeasureFormatStringItem(SvStream& rIn)      : SfxStringItem(SDRATTR_MEASUREFORMATSTRING,rIn)  {}
};

}//end of namespace binfilter
#endif
