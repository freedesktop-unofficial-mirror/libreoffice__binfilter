/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_swgpar.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: kz $ $Date: 2006-11-08 12:35:32 $
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

#include "swtypes.hxx"

#include "rdswg.hxx"
#include "swgpar.hxx"
namespace binfilter {

/////////////////////////////////////////////////////////////////////////

SwSwgParser::SwSwgParser( SwDoc *pSwDoc, const SwPaM* pSwPaM,
                 SvStream *pIstream, const String& rFileName, BOOL bNewDoc )
{
    pRdr = new SwSwgReader( pSwDoc, pSwPaM, *pIstream, rFileName, bNewDoc );
    pRdr->LoadFileHeader();
}

SwSwgParser::SwSwgParser( SvStream *pIstream )
{
    pRdr = new SwSwgReader( NULL, NULL, *pIstream, aEmptyStr, TRUE );
    pRdr->LoadFileHeader();
}

SwSwgParser::~SwSwgParser()
{
    delete pRdr;
}


ULONG SwSwgParser::CallParser( USHORT nOptions )
{
    return pRdr->Read( nOptions );
}

BOOL SwSwgParser::NeedsPasswd()
{
    return pRdr->GetError()
        ? FALSE
        : BOOL( ( pRdr->aFile.nFlags & SWGF_HAS_PASSWD ) != 0 );
}

BOOL SwSwgParser::CheckPasswd( const String& rStr )
{
    return pRdr->GetError() ? FALSE : pRdr->CheckPasswd( rStr );
}

const SfxDocumentInfo& SwSwgParser::GetDocInfo()
{
    return pRdr->GetDocInfo();
}

}
