/*************************************************************************
 *
 *  $RCSfile: sw_lineinfo.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 17:11:50 $
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

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif
// auto strip #ifndef _ERRHDL_HXX
// auto strip #include <errhdl.hxx>
// auto strip #endif

#include "doc.hxx"
#include "lineinfo.hxx"
#include "charfmt.hxx"
#include "poolfmt.hxx"
#include "rootfrm.hxx"
#include "viewsh.hxx"
namespace binfilter {

/*N*/ void SwDoc::SetLineNumberInfo( const SwLineNumberInfo &rNew )
/*N*/ {
/*N*/   if ( GetRootFrm() &&
/*N*/        (rNew.IsCountBlankLines() != pLineNumberInfo->IsCountBlankLines() ||
/*N*/         rNew.IsRestartEachPage() != pLineNumberInfo->IsRestartEachPage()) )
/*N*/   {
/*?*/       GetRootFrm()->StartAllAction();
/*?*/       GetRootFrm()->InvalidateAllCntnt( INV_LINENUM );
/*?*/       GetRootFrm()->EndAllAction();
/*N*/   }
/*N*/   *pLineNumberInfo = rNew;
/*N*/   SetModified();
/*N*/ }

/*N*/ SwLineNumberInfo::SwLineNumberInfo() :
/*N*/   nPosFromLeft( MM50 ),
/*N*/   nCountBy( 5 ),
/*N*/   nDividerCountBy( 3 ),
/*N*/   ePos( LINENUMBER_POS_LEFT ),
/*N*/   bPaintLineNumbers( FALSE ),
/*N*/   bCountBlankLines( TRUE ),
/*N*/   bCountInFlys( FALSE ),
/*N*/   bRestartEachPage( FALSE )
/*N*/ {
/*N*/ }

/*N*/ SwLineNumberInfo::SwLineNumberInfo(const SwLineNumberInfo &rCpy ) :
/*N*/   aType( rCpy.GetNumType() ),
/*N*/   aDivider( rCpy.GetDivider() ),
/*N*/   nPosFromLeft( rCpy.GetPosFromLeft() ),
/*N*/   nCountBy( rCpy.GetCountBy() ),
/*N*/   nDividerCountBy( rCpy.GetDividerCountBy() ),
/*N*/   ePos( rCpy.GetPos() ),
/*N*/   bPaintLineNumbers( rCpy.IsPaintLineNumbers() ),
/*N*/   bCountBlankLines( rCpy.IsCountBlankLines() ),
/*N*/   bCountInFlys( rCpy.IsCountInFlys() ),
/*N*/   bRestartEachPage( rCpy.IsRestartEachPage() )
/*N*/ {
/*N*/   if ( rCpy.GetRegisteredIn() )
/*?*/       ((SwModify*)rCpy.GetRegisteredIn())->Add( this );
/*N*/ }

/*N*/ SwLineNumberInfo& SwLineNumberInfo::operator=(const SwLineNumberInfo &rCpy)
/*N*/ {
/*N*/   if ( rCpy.GetRegisteredIn() )
/*N*/       ((SwModify*)rCpy.GetRegisteredIn())->Add( this );
/*N*/   else if ( GetRegisteredIn() )
/*?*/       pRegisteredIn->Remove( this );
/*N*/
/*N*/   aType = rCpy.GetNumType();
/*N*/   aDivider = rCpy.GetDivider();
/*N*/   nPosFromLeft = rCpy.GetPosFromLeft();
/*N*/   nCountBy = rCpy.GetCountBy();
/*N*/   nDividerCountBy = rCpy.GetDividerCountBy();
/*N*/   ePos = rCpy.GetPos();
/*N*/   bPaintLineNumbers = rCpy.IsPaintLineNumbers();
/*N*/   bCountBlankLines = rCpy.IsCountBlankLines();
/*N*/   bCountInFlys = rCpy.IsCountInFlys();
/*N*/   bRestartEachPage = rCpy.IsRestartEachPage();
/*N*/
/*N*/   return *this;
/*N*/ }

//STRIP001 BOOL SwLineNumberInfo::operator==( const SwLineNumberInfo& rInf ) const
//STRIP001 {
//STRIP001  return  GetRegisteredIn() == rInf.GetRegisteredIn() &&
//STRIP001          aType.GetNumberingType() == rInf.GetNumType().GetNumberingType() &&
//STRIP001          aDivider == rInf.GetDivider() &&
//STRIP001          nPosFromLeft == rInf.GetPosFromLeft() &&
//STRIP001          nCountBy == rInf.GetCountBy() &&
//STRIP001          nDividerCountBy == rInf.GetDividerCountBy() &&
//STRIP001          ePos == rInf.GetPos() &&
//STRIP001          bPaintLineNumbers == rInf.IsPaintLineNumbers() &&
//STRIP001          bCountBlankLines == rInf.IsCountBlankLines() &&
//STRIP001          bCountInFlys == rInf.IsCountInFlys() &&
//STRIP001          bRestartEachPage == rInf.IsRestartEachPage();
//STRIP001 }


/*N*/ SwCharFmt* SwLineNumberInfo::GetCharFmt(SwDoc &rDoc) const
/*N*/ {
/*N*/   if ( !GetRegisteredIn() )
/*?*/   {
/*?*/       SwCharFmt* pFmt = rDoc.GetCharFmtFromPool( RES_POOLCHR_LINENUM );
/*?*/       pFmt->Add( (SwClient*)this );
/*?*/   }
/*N*/   return (SwCharFmt*)GetRegisteredIn();
/*N*/ }

/*N*/ void SwLineNumberInfo::SetCharFmt( SwCharFmt *pChFmt )
/*N*/ {
/*N*/   ASSERT( pChFmt, "SetCharFmt, 0 is not a valid pointer" );
/*N*/   pChFmt->Add( this );
/*N*/ }

/*N*/ void SwLineNumberInfo::Modify( SfxPoolItem* pOld, SfxPoolItem* pNew )
/*N*/ {
/*N*/   SwClient::Modify( pOld, pNew );
/*N*/   SwDoc *pDoc = ((SwCharFmt*)GetRegisteredIn())->GetDoc();
/*N*/   SwRootFrm* pRoot = pDoc->GetRootFrm();
/*N*/   if( pRoot && pRoot->GetCurrShell() )
/*N*/   {
/*?*/       pRoot->StartAllAction();
/*?*/       pRoot->GetCurrShell()->AddPaintRect( pRoot->Frm() );
/*?*/       pRoot->EndAllAction();
/*N*/   }
/*N*/ }

}
