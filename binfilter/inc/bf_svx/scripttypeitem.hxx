/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: scripttypeitem.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 03:57:00 $
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
#ifndef _SVX_SCRIPTTYPEITEM_HXX
#define _SVX_SCRIPTTYPEITEM_HXX

// include ---------------------------------------------------------------

#ifndef _SFXINTITEM_HXX
#include <svtools/intitem.hxx>
#endif
#ifndef _SVX_SVXIDS_HRC
#include <bf_svx/svxids.hrc>
#endif
#ifndef _SVTOOLS_LANGUAGEOPTIONS_HXX
#include <svtools/languageoptions.hxx>
#endif
namespace binfilter {

// class SvxScriptTypeItem ----------------------------------------------

/* [Description]

        This item describe  the scriptype of the selected text and is only
    used for the user interface.
*/

USHORT GetI18NScriptTypeOfLanguage( USHORT nLang );
USHORT GetItemScriptType( short nI18NType );
short  GetI18NScriptType( USHORT nItemType );


class SvxScriptSetItem : public SfxSetItem
{
public:
    TYPEINFO();

    SvxScriptSetItem( USHORT nSlotId, SfxItemPool& rPool );

    virtual SfxPoolItem* Clone( SfxItemPool *pPool = 0 ) const;
    virtual SfxPoolItem* Create( SvStream &, USHORT nVersion ) const;

    static const SfxPoolItem* GetItemOfScriptSet( const SfxItemSet& rSet,
                                                    USHORT nWhich );
    inline const SfxPoolItem* GetItemOfScriptSet( USHORT nWhich ) const
    { return SvxScriptSetItem::GetItemOfScriptSet( GetItemSet(), nWhich ); }

    const SfxPoolItem* GetItemOfScript( USHORT nScript ) const;


    void GetWhichIds( USHORT& rLatin, USHORT& rAsian, USHORT& rComplex) const;

    static void GetSlotIds( USHORT nSlotId, USHORT& rLatin, USHORT& rAsian,
                                            USHORT& rComplex );
    inline void GetSlotIds( USHORT& rLatin, USHORT& rAsian,
                                USHORT& rComplex ) const
    { GetSlotIds( Which(), rLatin, rAsian, rComplex ); }
};

}//end of namespace binfilter
#endif

