/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_atrtox.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 12:42:01 $
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

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _TXTTXMRK_HXX //autogen
#include <txttxmrk.hxx>
#endif
#ifndef _TOX_HXX
#include <tox.hxx>
#endif
namespace binfilter {

/*N*/ SwTxtTOXMark::SwTxtTOXMark( const SwTOXMark& rAttr,
/*N*/                   xub_StrLen nStart, xub_StrLen* pEnde )
/*N*/   : SwTxtAttrEnd( rAttr, nStart, nStart ),
/*N*/   pEnd( 0 ),
/*N*/   pMyTxtNd( 0 )
/*N*/ {
/*N*/   ((SwTOXMark&)rAttr).pTxtAttr = this;
/*N*/   if( !rAttr.GetAlternativeText().Len() )
/*N*/   {
/*N*/       nEnd = *pEnde;
/*N*/       pEnd = &nEnd;
/*N*/   }
/*N*/   SetDontMergeAttr( TRUE );
/*N*/   SetDontMoveAttr( TRUE );
/*N*/   SetOverlapAllowedAttr( TRUE );
/*N*/ }

/*N*/ SwTxtTOXMark::~SwTxtTOXMark()
/*N*/ {
/*N*/ }

/*N*/ xub_StrLen* SwTxtTOXMark::GetEnd()
/*N*/ {
/*N*/   return pEnd;
/*N*/ }

/*N*/ void SwTxtTOXMark::CopyTOXMark( SwDoc* pDoc )
/*N*/ {
/*N*/   SwTOXMark& rTOX = (SwTOXMark&)GetTOXMark();
/*N*/   TOXTypes    eType   = rTOX.GetTOXType()->GetType();
/*N*/   USHORT      nCount  = pDoc->GetTOXTypeCount( eType );
/*N*/   const SwTOXType* pType = 0;
/*N*/   const XubString& rNm = rTOX.GetTOXType()->GetTypeName();
/*N*/
/*N*/   // kein entsprechender Verzeichnistyp vorhanden -> anlegen
/*N*/   // sonst verwenden
/*N*/   for(USHORT i=0; i < nCount; ++i)
/*N*/   {
/*N*/       const SwTOXType* pSrcType = pDoc->GetTOXType(eType, i);
/*N*/       if(pSrcType->GetTypeName() == rNm )
/*N*/       {
/*N*/           pType = pSrcType;
/*N*/           break;
/*N*/       }
/*N*/   }
/*N*/   // kein entsprechender Typ vorhanden -> neu erzeugen
/*N*/   //
/*N*/   if(!pType)
/*N*/   {
/*N*/       pDoc->InsertTOXType( SwTOXType( eType, rNm ) );
/*N*/       pType = pDoc->GetTOXType(eType, 0);
/*N*/   }
/*N*/   // Verzeichnistyp umhaengen
/*N*/   //
/*N*/   ((SwTOXType*)pType)->Add( &rTOX );
/*N*/ }
}
