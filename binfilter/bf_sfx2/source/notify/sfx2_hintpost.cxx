/*************************************************************************
 *
 *  $RCSfile: sfx2_hintpost.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:40:57 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/

#pragma hdrstop

#include "arrdecl.hxx"
#include "hintpost.hxx"
#include "app.hxx"
#include "sfxtypes.hxx"
namespace binfilter {

//====================================================================

//STRIP001 void SfxHintPoster::RegisterEvent()
//STRIP001 {
//STRIP001  DBG_MEMTEST();
//STRIP001 }

//--------------------------------------------------------------------

//STRIP001 SfxHintPoster::SfxHintPoster()
//STRIP001 {
//STRIP001  RegisterEvent();
//STRIP001 }

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
