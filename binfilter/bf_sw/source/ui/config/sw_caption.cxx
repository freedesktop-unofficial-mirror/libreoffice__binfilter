/*************************************************************************
 *
 *  $RCSfile: sw_caption.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 18:34:48 $
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

// auto strip #ifndef _TOOLS_DEBUG_HXX //autogen
// auto strip #include <tools/debug.hxx>
// auto strip #endif

#include "numrule.hxx"
#include "caption.hxx"
namespace binfilter {

#define VERSION_01      1
#define CAPTION_VERSION VERSION_01

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

/*N*/ InsCaptionOpt::InsCaptionOpt(const SwCapObjType eType, const SvGlobalName* pOleId) :
/*N*/   bUseCaption(FALSE),
/*N*/   eObjType(eType),
/*N*/   nNumType(SVX_NUM_ARABIC),
/*N*/   nPos(1),
/*N*/   nLevel(0),
/*N*/   cSeparator('.'),
/*N*/   bIgnoreSeqOpts(FALSE),
/*N*/   bCopyAttributes(FALSE)
/*N*/ {
/*N*/   if (pOleId)
/*N*/       aOleId = *pOleId;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

//STRIP001 InsCaptionOpt::InsCaptionOpt(const InsCaptionOpt& rOpt)
//STRIP001 {
//STRIP001  *this = rOpt;
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

/*N*/ InsCaptionOpt::~InsCaptionOpt()
/*N*/ {
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

//STRIP001 InsCaptionOpt& InsCaptionOpt::operator=( const InsCaptionOpt& rOpt )
//STRIP001 {
//STRIP001  bUseCaption = rOpt.bUseCaption;
//STRIP001  eObjType = rOpt.eObjType;
//STRIP001  aOleId = rOpt.aOleId;
//STRIP001  sCategory = rOpt.sCategory;
//STRIP001  nNumType = rOpt.nNumType;
//STRIP001  sCaption = rOpt.sCaption;
//STRIP001  nPos = rOpt.nPos;
//STRIP001  nLevel = rOpt.nLevel;
//STRIP001  cSeparator = rOpt.cSeparator;
//STRIP001  bIgnoreSeqOpts = rOpt.bIgnoreSeqOpts;
//STRIP001  bCopyAttributes = rOpt.bCopyAttributes;
//STRIP001
//STRIP001  return *this;
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

//STRIP001 BOOL InsCaptionOpt::operator==( const InsCaptionOpt& rOpt ) const
//STRIP001 {
//STRIP001  return (eObjType == rOpt.eObjType &&
//STRIP001          aOleId == rOpt.aOleId); // Damit gleiche Ole-IDs nicht mehrfach eingefuegt
//STRIP001                                  // werden koennen, auf nichts weiteres vergleichen
//STRIP001
//STRIP001
//STRIP001 /*            &&
//STRIP001          sCategory == rOpt.sCategory &&
//STRIP001          nNumType == rOpt.nNumType &&
//STRIP001          sCaption == rOpt.sCaption &&
//STRIP001          nPos == rOpt.nPos &&
//STRIP001          nLevel == rOpt.nLevel &&
//STRIP001          cSeparator == rOpt.cSeparator);*/
//STRIP001 }

/*************************************************************************
|*
|*    InsCaptionOpt::operator>>()
|*
|*    Beschreibung      Stream-Leseoperator
|*
*************************************************************************/

//STRIP001 SvStream& operator>>( SvStream& rIStream, InsCaptionOpt& rCapOpt )
//STRIP001 {
//STRIP001  rtl_TextEncoding eEncoding = gsl_getSystemTextEncoding();
//STRIP001  UINT16 nVal;
//STRIP001  BYTE   cVal;
//STRIP001  BYTE   nVersion;
//STRIP001
//STRIP001  rIStream >> nVersion;
//STRIP001  rIStream >> cVal;               rCapOpt.UseCaption() = cVal != 0;
//STRIP001  rIStream >> nVal;               rCapOpt.eObjType = (SwCapObjType)nVal;
//STRIP001  rIStream >> rCapOpt.aOleId;
//STRIP001
//STRIP001  rIStream.ReadByteString( rCapOpt.sCategory, eEncoding );
//STRIP001  rIStream >> nVal;               rCapOpt.nNumType = nVal;
//STRIP001  rIStream.ReadByteString( rCapOpt.sCaption, eEncoding );
//STRIP001  rIStream >> nVal;               rCapOpt.nPos = nVal;
//STRIP001  rIStream >> nVal;               rCapOpt.nLevel = nVal;
//STRIP001
//STRIP001  rIStream >> cVal;
//STRIP001  rCapOpt.cSeparator = UniString( ByteString(cVal) , eEncoding).GetChar(0);
//STRIP001
//STRIP001  return rIStream;
//STRIP001 }

/*************************************************************************
|*
|*    InsCaptionOpt::operator<<()
|*
|*    Beschreibung      Stream-Schreiboperator
|*
*************************************************************************/

//STRIP001 SvStream& operator<<( SvStream& rOStream, const InsCaptionOpt& rCapOpt )
//STRIP001 {
//STRIP001  rtl_TextEncoding eEncoding = gsl_getSystemTextEncoding();
//STRIP001  rOStream    << (BYTE)CAPTION_VERSION
//STRIP001              << (BYTE)rCapOpt.UseCaption()
//STRIP001              << (UINT16)rCapOpt.eObjType
//STRIP001              << rCapOpt.aOleId;
//STRIP001
//STRIP001  rOStream.WriteByteString( rCapOpt.sCategory, eEncoding );
//STRIP001
//STRIP001  rOStream    << (UINT16)rCapOpt.nNumType;
//STRIP001
//STRIP001  rOStream.WriteByteString( rCapOpt.sCaption, eEncoding );
//STRIP001
//STRIP001  BYTE cSep = ByteString(UniString(rCapOpt.cSeparator), eEncoding).GetChar(0);
//STRIP001  rOStream    << (UINT16)rCapOpt.nPos
//STRIP001              << (UINT16)rCapOpt.nLevel
//STRIP001              << cSep;
//STRIP001
//STRIP001  return rOStream;
//STRIP001 }

}
