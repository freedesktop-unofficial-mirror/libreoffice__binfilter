/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: sfx2_hintpost.cxx,v $
 * $Revision: 1.7 $
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
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
