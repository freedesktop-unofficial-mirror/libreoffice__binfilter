/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: pmdlitem.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 03:52:57 $
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
#ifndef _SVX_PMDLITEM_HXX
#define _SVX_PMDLITEM_HXX

// include ---------------------------------------------------------------

#ifndef _SFXSTRITEM_HXX //autogen
#include <svtools/stritem.hxx>
#endif
#ifndef _SVX_SVXIDS_HRC
#include <bf_svx/svxids.hrc>
#endif
namespace binfilter {

// class SvxPageModelItem ------------------------------------------------

/*
[Beschreibung]
Dieses Item enthaelt einen Namen einer Seitenvorlage.
*/

class SvxPageModelItem : public SfxStringItem
{
private:
    BOOL bAuto;

public:
    TYPEINFO();

    inline SvxPageModelItem( USHORT nWhich = ITEMID_PAGEMODEL );
    inline SvxPageModelItem( const String& rModel, BOOL bA = FALSE,
                             USHORT nWhich = ITEMID_PAGEMODEL );
    inline SvxPageModelItem& operator=( const SvxPageModelItem& rModel );

};

inline SvxPageModelItem::SvxPageModelItem( USHORT nWhich )
    : bAuto( FALSE )
{
    SetWhich( nWhich );
}

inline SvxPageModelItem::SvxPageModelItem( const String& rModel, BOOL bA,
                                           USHORT nWhich ) :
    SfxStringItem( nWhich, rModel ),
    bAuto( bA )
{}

inline SvxPageModelItem& SvxPageModelItem::operator=( const SvxPageModelItem& rModel )
{
    SetValue( rModel.GetValue() );
    return *this;
}

}//end of namespace binfilter
#endif

