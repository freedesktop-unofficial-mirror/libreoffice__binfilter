/*************************************************************************
 *
 *  $RCSfile: sw_findcoll.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 15:08:44 $
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

#ifndef _SWCRSR_HXX
#include <swcrsr.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _PAMTYP_HXX
#include <pamtyp.hxx>
#endif
#ifndef _SWUNDO_HXX
#include <swundo.hxx>
#endif
#ifndef _UNDOBJ_HXX
#include <undobj.hxx>
#endif


//------------------ Methoden der CrsrShell ---------------------------

// Parameter fuer das Suchen vom FormatCollections
//STRIP001 struct SwFindParaFmtColl : public SwFindParas
//STRIP001 {
//STRIP001  const SwTxtFmtColl *pFmtColl, *pReplColl;
//STRIP001  SwCursor& rCursor;
//STRIP001  SwFindParaFmtColl( const SwTxtFmtColl& rFmtColl,
//STRIP001                      const SwTxtFmtColl* pRpColl, SwCursor& rCrsr )
//STRIP001      : rCursor( rCrsr ), pFmtColl( &rFmtColl ), pReplColl( pRpColl )
//STRIP001  {}
//STRIP001  virtual int Find( SwPaM* , SwMoveFn , const SwPaM*, FASTBOOL bInReadOnly );
//STRIP001  virtual int IsReplaceMode() const;
//STRIP001 };


//STRIP001 int SwFindParaFmtColl::Find( SwPaM* pCrsr, SwMoveFn fnMove, const SwPaM* pRegion,
//STRIP001                          FASTBOOL bInReadOnly )
//STRIP001 {
//STRIP001  int nRet = FIND_FOUND;
//STRIP001  if( bInReadOnly && pReplColl )
//STRIP001      bInReadOnly = FALSE;
//STRIP001
//STRIP001  if( !pCrsr->Find( *pFmtColl, fnMove, pRegion, bInReadOnly ) )
//STRIP001      nRet = FIND_NOT_FOUND;
//STRIP001  else if( pReplColl )
//STRIP001  {
//STRIP001      pCrsr->GetDoc()->SetTxtFmtColl( *pCrsr, (SwTxtFmtColl*)pReplColl );
//STRIP001      nRet = FIND_NO_RING;
//STRIP001  }
//STRIP001  return nRet;
//STRIP001 }


//STRIP001 int SwFindParaFmtColl::IsReplaceMode() const
//STRIP001 {
//STRIP001  return 0 != pReplColl;
//STRIP001 }


// Suchen nach Format-Collections


/*M*/ ULONG SwCursor::Find( const SwTxtFmtColl& rFmtColl,
/*M*/                     SwDocPositions nStart, SwDocPositions nEnde, BOOL& bCancel,
/*M*/                   FindRanges eFndRngs, const SwTxtFmtColl* pReplFmtColl )
/*M*/ {DBG_ASSERT(0, "STRIP");return 0;//STRIP001
/*M*/   // OLE-Benachrichtigung abschalten !!
//STRIP001 /*?*/    SwDoc* pDoc = GetDoc();
//STRIP001 /*?*/    Link aLnk( pDoc->GetOle2Link() );
//STRIP001 /*?*/    pDoc->SetOle2Link( Link() );
//STRIP001 /*?*/
//STRIP001 /*?*/    BOOL bSttUndo = pDoc->DoesUndo() && pReplFmtColl;
//STRIP001 /*?*/    if( bSttUndo )
//STRIP001 /*?*/        pDoc->StartUndo( UNDO_REPLACE );
//STRIP001 /*?*/
//STRIP001 /*?*/    SwFindParaFmtColl aSwFindParaFmtColl( rFmtColl, pReplFmtColl, *this );
//STRIP001 /*?*/
//STRIP001 /*?*/     ULONG nRet = FindAll( aSwFindParaFmtColl, nStart, nEnde, eFndRngs, bCancel );
//STRIP001 /*?*/    pDoc->SetOle2Link( aLnk );
//STRIP001 /*?*/
//STRIP001 /*?*/    if( nRet && pReplFmtColl )
//STRIP001 /*?*/        pDoc->SetModified();
//STRIP001 /*?*/
//STRIP001 /*?*/    if( bSttUndo )
//STRIP001 /*?*/        pDoc->EndUndo( UNDO_REPLACE );
//STRIP001 /*?*/     return nRet;
/*M*/ }



