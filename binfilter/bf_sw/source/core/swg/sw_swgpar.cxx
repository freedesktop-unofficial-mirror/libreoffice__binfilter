/*************************************************************************
 *
 *  $RCSfile: sw_swgpar.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 17:48:41 $
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
