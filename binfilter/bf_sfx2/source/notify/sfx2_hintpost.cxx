/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sfx2_hintpost.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 11:31:43 $
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

#ifdef _MSC_VER
#pragma hdrstop
#endif

#include "hintpost.hxx"
#include "app.hxx"
namespace binfilter {

//====================================================================


//--------------------------------------------------------------------


//--------------------------------------------------------------------

/*N*/ SfxHintPoster::SfxHintPoster( const GenLink& rLink ):
/*N*/   aLink(rLink)
/*N*/ {
/*N*/ }


//--------------------------------------------------------------------

/*N*/ SfxHintPoster::~SfxHintPoster()
/*N*/ {
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void SfxHintPoster::Post( SfxHint* pHintToPost )
/*N*/ {
/*N*/     GetpApp()->PostUserEvent( ( LINK(this, SfxHintPoster, DoEvent_Impl) ), pHintToPost );
/*N*/   AddRef();
/*N*/ }

//--------------------------------------------------------------------

/*N*/ IMPL_LINK_INLINE_START( SfxHintPoster, DoEvent_Impl, SfxHint *, pPostedHint )
/*N*/ {
/*N*/   DBG_MEMTEST();
/*N*/   Event( pPostedHint );
/*N*/   ReleaseRef();
/*N*/   return 0;
/*N*/ }
/*N*/ IMPL_LINK_INLINE_END( SfxHintPoster, DoEvent_Impl, SfxHint *, pPostedHint )

//--------------------------------------------------------------------

/*N*/ void SfxHintPoster::Event( SfxHint* pPostedHint )
/*N*/ {
/*N*/   aLink.Call( pPostedHint );
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void SfxHintPoster::SetEventHdl( const GenLink& rLink )
/*N*/ {
/*N*/   DBG_MEMTEST();
/*N*/   aLink = rLink;
/*N*/ }


#define LOG( x )
#if 0
#define LOG( x )                                                \
{                                                               \
    SvFileStream aStrm( "f:\\temp\\log", STREAM_READWRITE );    \
    aStrm.Seek( STREAM_SEEK_TO_END );                           \
    aStrm << x.GetStr() << '\n';                                \
}
#endif
}
