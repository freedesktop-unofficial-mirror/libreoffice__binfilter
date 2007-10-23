/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: ipmenu.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: vg $ $Date: 2007-10-23 13:45:08 $
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

#include <ipmenu.hxx>
#include <tools/link.hxx>
#include <tools/debug.hxx>

/************************************************************************/
/*************************************************************************
|*    SvInPlaceMenuBar::SvInPlaceMenuBar()
|*
|*    Beschreibung
*************************************************************************/
SvInPlaceMenuBar::SvInPlaceMenuBar( const ResId & rId )
    : MenuBar( rId )
{
    USHORT * pRes = (USHORT *)GetClassRes();
    nCount0       = pRes[ 0 ];
    nCount1       = pRes[ 1 ];
    nCount2       = pRes[ 2 ];
    IncrementRes( sizeof( short ) * 3 );
}

SvInPlaceMenuBar::SvInPlaceMenuBar( MenuBar * pBar,
                                    USHORT nPos0, USHORT nCount0P,
                                    USHORT nPos1, USHORT nCount1P,
                                    USHORT nPos2, USHORT nCount2P )
    : MenuBar()
{
    nCount0       = nCount0P;
    nCount1       = nCount1P;
    nCount2       = nCount2P;

    USHORT i;
    for( i = nPos0; i < nPos0 + nCount0; i++ )
        InsertItem( *pBar, i );
    for( i = nPos1; i < nPos1 + nCount1; i++ )
        InsertItem( *pBar, i );
    for( i = nPos2; i < nPos2 + nCount2; i++ )
        InsertItem( *pBar, i );
}

/*************************************************************************
|*    SvInPlaceMenuBar::~SvInPlaceMenuBar()
|*
|*    Beschreibung
*************************************************************************/
SvInPlaceMenuBar::~SvInPlaceMenuBar()
{
}

/*************************************************************************
|*    SvInPlaceMenuBar::InsertItem()
|*
|*    Beschreibung
*************************************************************************/
void SvInPlaceMenuBar::InsertItem( Menu & rMenu, USHORT nPos )
{
    CopyItem( rMenu, nPos );
}

/*************************************************************************
|*    SvInPlaceMenuBar::PushSelectHdl()
|*    SvInPlaceMenuBar::PopSelectHdl()
|*
|*    Beschreibung
*************************************************************************/
void SvInPlaceMenuBar::PushSelectHdl( const Link & rLink )
{
    MenuBar::SetSelectHdl( rLink );
    for( USHORT i = 0; i < GetItemCount(); i++ )
    {
        USHORT nId = GetItemId( i );
        GetPopupMenu( nId )->SetSelectHdl( rLink );
    }
}

void SvInPlaceMenuBar::PopSelectHdl()
{
    MenuBar::SetSelectHdl( Link());
    for( USHORT i = 0; i < GetItemCount(); i++ )
    {
        USHORT nId = GetItemId( i );
        GetPopupMenu( nId )->SetSelectHdl( Link() );
    }
}

/*************************************************************************
|*    SvInPlaceMenuBar::PushActivateHdl()
|*    SvInPlaceMenuBar::PopActivateHdl()
|*
|*    Beschreibung
*************************************************************************/
void SvInPlaceMenuBar::PushActivateHdl( const Link & rLink )
{
    (void)rLink;
    DBG_ERROR( "not implemented" );
}

void SvInPlaceMenuBar::PopActivateHdl()
{
    DBG_ERROR( "not implemented" );
}

/*************************************************************************
|*    SvInPlaceMenuBar::PushDeactivateHdl()
|*    SvInPlaceMenuBar::PopDeactivateHdl()
|*
|*    Beschreibung
*************************************************************************/
void SvInPlaceMenuBar::PushDeactivateHdl( const Link & rLink )
{
    (void)rLink;
    DBG_ERROR( "not implemented" );
}

void SvInPlaceMenuBar::PopDeactivateHdl()
{
    DBG_ERROR( "not implemented" );
}

/*************************************************************************
|*    SvInPlaceMenuBar::PushHighliteHdl()
|*    SvInPlaceMenuBar::PopHighliteHdl()
|*
|*    Beschreibung
*************************************************************************/
void SvInPlaceMenuBar::PushHighlightHdl( const Link & rLink )
{
    (void)rLink;
    DBG_ERROR( "not implemented" );
}

void SvInPlaceMenuBar::PopHighlightHdl()
{
    DBG_ERROR( "not implemented" );
}

