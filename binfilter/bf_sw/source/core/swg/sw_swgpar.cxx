/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_swgpar.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-08 10:14:10 $
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


#pragma hdrstop

// auto strip #include "swtypes.hxx"

// auto strip #include "rdswg.hxx"
// auto strip #include "swgpar.hxx"
namespace binfilter {

/////////////////////////////////////////////////////////////////////////

//STRIP001 SwSwgParser::SwSwgParser( SwDoc *pSwDoc, const SwPaM* pSwPaM,
//STRIP001               SvStream *pIstream, const String& rFileName, BOOL bNewDoc )
//STRIP001 {
//STRIP001  pRdr = new SwSwgReader( pSwDoc, pSwPaM, *pIstream, rFileName, bNewDoc );
//STRIP001  pRdr->LoadFileHeader();
//STRIP001 }

//STRIP001 SwSwgParser::SwSwgParser( SvStream *pIstream )
//STRIP001 {
//STRIP001  pRdr = new SwSwgReader( NULL, NULL, *pIstream, aEmptyStr, TRUE );
//STRIP001  pRdr->LoadFileHeader();
//STRIP001 }

//STRIP001 SwSwgParser::~SwSwgParser()
//STRIP001 {
//STRIP001  delete pRdr;
//STRIP001 }


//STRIP001 ULONG SwSwgParser::CallParser( USHORT nOptions )
//STRIP001 {
//STRIP001  return pRdr->Read( nOptions );
//STRIP001 }

//STRIP001 BOOL SwSwgParser::NeedsPasswd()
//STRIP001 {
//STRIP001  return pRdr->GetError()
//STRIP001      ? FALSE
//STRIP001      : BOOL( ( pRdr->aFile.nFlags & SWGF_HAS_PASSWD ) != 0 );
//STRIP001 }

//STRIP001 BOOL SwSwgParser::CheckPasswd( const String& rStr )
//STRIP001 {
//STRIP001  return pRdr->GetError() ? FALSE : pRdr->CheckPasswd( rStr );
//STRIP001 }

//STRIP001 const SfxDocumentInfo& SwSwgParser::GetDocInfo()
//STRIP001 {
//STRIP001  return pRdr->GetDocInfo();
//STRIP001 }

}
