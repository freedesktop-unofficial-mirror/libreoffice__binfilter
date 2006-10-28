/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: scriptspaceitem.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 03:56:48 $
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
#ifndef _SVX_SRIPTSPACEITEM_HXX
#define _SVX_SRIPTSPACEITEM_HXX

// include ---------------------------------------------------------------

#ifndef _SFXENUMITEM_HXX
#include <svtools/eitem.hxx>
#endif
#ifndef _SVX_SVXIDS_HRC
#include <bf_svx/svxids.hrc>
#endif
namespace binfilter {

// class SvxScriptSpaceItem ----------------------------------------------

/* [Description]

    This item describe the scriptype of the selected text and is only
    used for the user interface.
*/

class SvxScriptSpaceItem : public SfxBoolItem
{
public:
    TYPEINFO();

    SvxScriptSpaceItem( sal_Bool bOn = sal_False,
                        const sal_uInt16 nId = ITEMID_SCRIPTSPACE );

    virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;
    virtual SfxPoolItem*    Create(SvStream &, USHORT) const;
    virtual USHORT          GetVersion( USHORT nFileVersion ) const;


    inline SvxScriptSpaceItem& operator=(const SvxScriptSpaceItem& rItem )
    {
        SetValue( rItem.GetValue() );
        return *this;
    }

};

}//end of namespace binfilter
#endif

