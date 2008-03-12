/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xlnasit.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 13:29:09 $
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

#ifndef _SVX_XLNASIT_HXX
#define _SVX_XLNASIT_HXX

#ifndef _SFXPOOLITEM_HXX //autogen
#include <bf_svtools/poolitem.hxx>
#endif
namespace binfilter {

/*************************************************************************
|*
|* SetItem mit dem ItemSet aller Linienattribute
|*
\************************************************************************/

class XLineAttrSetItem : public SfxSetItem
{
public:
                            TYPEINFO();
                            XLineAttrSetItem(SfxItemSet* pItemSet );
                            XLineAttrSetItem(SfxItemPool* pItemPool);
                            XLineAttrSetItem(const XLineAttrSetItem& rAttr);
                            XLineAttrSetItem(const XLineAttrSetItem& rAttr,
                                             SfxItemPool* pItemPool);
    virtual SfxPoolItem*    Clone( SfxItemPool* pToPool ) const;
    virtual SfxPoolItem*    Create( SvStream& rStream, USHORT nVersion ) const;
    virtual SvStream&       Store( SvStream& rStream, USHORT nItemVersion ) const;
};

}//end of namespace binfilter
#endif
