/*************************************************************************
 *
 *  $RCSfile: sw_ssfrm.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 15:27:04 $
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

#ifndef _PAGEFRM_HXX
#include <pagefrm.hxx>
#endif
#ifndef _ROOTFRM_HXX
#include <rootfrm.hxx>
#endif
#ifndef _CNTFRM_HXX
#include <cntfrm.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _NODE_HXX
#include <node.hxx>
#endif
#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif

#ifndef _DVIEW_HXX
#include <dview.hxx>
#endif
#ifndef _DCONTACT_HXX
#include <dcontact.hxx>
#endif
#ifndef _DFLYOBJ_HXX
#include <dflyobj.hxx>
#endif
#ifndef _FLYFRM_HXX
#include <flyfrm.hxx>
#endif
#ifndef _TXTFRM_HXX
#include <txtfrm.hxx>       // ClearPara()
#endif
#ifndef _FTNIDX_HXX
#include <ftnidx.hxx>
#endif
#ifndef _TXTFTN_HXX
#include <txtftn.hxx>
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>
#endif
#ifndef _NDINDEX_HXX
#include <ndindex.hxx>
#endif

#ifndef _FRMTOOL_HXX
#include <frmtool.hxx>
#endif
#ifndef _PAGEDESC_HXX
#include <pagedesc.hxx>
#endif
#define ITEMID_BOXINFO      SID_ATTR_BORDER_INNER
#ifndef _HINTS_HXX
#include <hints.hxx>        //fuer SwFmtChg
#endif
#ifndef _SVX_BOXITEM_HXX //autogen
#include <bf_svx/boxitem.hxx>
#endif
#ifndef _SVX_SHADITEM_HXX //autogen
#include <bf_svx/shaditem.hxx>
#endif
#ifndef _FMTCLDS_HXX //autogen
#include <fmtclds.hxx>
#endif
#ifndef _VIEWSH_HXX
#include <viewsh.hxx>
#endif
#ifndef _VIEWIMP_HXX
#include <viewimp.hxx>
#endif
#ifndef _FRMSH_HXX
#include <frmsh.hxx>
#endif

    // No inline cause we need the function pointers
/*N*/ long SwFrm::GetTopMargin() const
/*N*/     { return Prt().Top(); }
/*N*/ long SwFrm::GetBottomMargin() const
/*N*/     { return Frm().Height() -Prt().Height() -Prt().Top(); }
/*N*/ long SwFrm::GetLeftMargin() const
/*N*/     { return Prt().Left(); }
/*N*/ long SwFrm::GetRightMargin() const
/*N*/     { return Frm().Width() - Prt().Width() - Prt().Left(); }
/*N*/ long SwFrm::GetPrtLeft() const
/*N*/     { return Frm().Left() + Prt().Left(); }
/*N*/ long SwFrm::GetPrtBottom() const
/*N*/     { return Frm().Top() + Prt().Height() + Prt().Top(); }
/*N*/ long SwFrm::GetPrtRight() const
/*N*/     { return Frm().Left() + Prt().Width() + Prt().Left(); }
/*N*/ long SwFrm::GetPrtTop() const
/*N*/     { return Frm().Top() + Prt().Top(); }

/*N*/ BOOL SwFrm::SetMinLeft( long nDeadline )
/*N*/ {
/*N*/     SwTwips nDiff = nDeadline - Frm().Left();
/*N*/     if( nDiff > 0 )
/*N*/     {
/*?*/         Frm().Left( nDeadline );
/*?*/         Prt().Width( Prt().Width() - nDiff );
/*?*/         return TRUE;
/*N*/     }
/*N*/     return FALSE;
/*N*/ }

/*N*/ BOOL SwFrm::SetMaxBottom( long nDeadline )
/*N*/ {
/*N*/     SwTwips nDiff = Frm().Top() + Frm().Height() - nDeadline;
/*N*/     if( nDiff > 0 )
/*N*/     {
/*?*/         Frm().Height( Frm().Height() - nDiff );
/*?*/         Prt().Height( Prt().Height() - nDiff );
/*?*/         return TRUE;
/*N*/     }
/*N*/     return FALSE;
/*N*/ }

/*N*/ BOOL SwFrm::SetMinTop( long nDeadline )
/*N*/ {
/*N*/     SwTwips nDiff = nDeadline - Frm().Top();
/*N*/     if( nDiff > 0 )
/*N*/     {
/*?*/         Frm().Top( nDeadline );
/*?*/         Prt().Height( Prt().Height() - nDiff );
/*?*/         return TRUE;
/*N*/     }
/*N*/     return FALSE;
/*N*/ }

/*N*/ BOOL SwFrm::SetMaxRight( long nDeadline )
/*N*/ {
/*N*/     SwTwips nDiff = Frm().Left() + Frm().Width() - nDeadline;
/*N*/     if( nDiff > 0 )
/*N*/     {
/*?*/         Frm().Width( Frm().Width() - nDiff );
/*?*/         Prt().Width( Prt().Width() - nDiff );
/*?*/         return TRUE;
/*N*/     }
/*N*/     return FALSE;
/*N*/ }

/*N*/ void SwFrm::MakeBelowPos( const SwFrm* pUp, const SwFrm* pPrv, BOOL bNotify )
/*N*/ {
/*N*/     if( pPrv )
/*N*/     {
/*N*/         aFrm.Pos( pPrv->Frm().Pos() );
/*N*/         aFrm.Pos().Y() += pPrv->Frm().Height();
/*N*/     }
/*N*/     else
/*N*/     {
/*N*/         aFrm.Pos( pUp->Frm().Pos() );
/*N*/         aFrm.Pos() += pUp->Prt().Pos();
/*N*/     }
/*N*/     if( bNotify )
/*N*/         aFrm.Pos().Y() += 1;
/*N*/ }

/*N*/ void SwFrm::MakeUpperPos( const SwFrm* pUp, const SwFrm* pPrv, BOOL bNotify )
/*N*/ {
/*N*/     if( pPrv )
/*N*/     {
/*N*/         aFrm.Pos( pPrv->Frm().Pos() );
/*N*/         aFrm.Pos().Y() -= Frm().Height();
/*N*/     }
/*N*/     else
/*N*/     {
/*N*/         aFrm.Pos( pUp->Frm().Pos() );
/*N*/         aFrm.Pos() += pUp->Prt().Pos();
/*N*/         aFrm.Pos().Y() += pUp->Prt().Height() - aFrm.Height();
/*N*/     }
/*N*/     if( bNotify )
/*N*/         aFrm.Pos().Y() -= 1;
/*N*/ }

/*N*/ void SwFrm::MakeLeftPos( const SwFrm* pUp, const SwFrm* pPrv, BOOL bNotify )
/*N*/ {
/*N*/     if( pPrv )
/*N*/     {
/*N*/         aFrm.Pos( pPrv->Frm().Pos() );
/*N*/         aFrm.Pos().X() -= Frm().Width();
/*N*/     }
/*N*/     else
/*N*/     {
/*N*/         aFrm.Pos( pUp->Frm().Pos() );
/*N*/         aFrm.Pos() += pUp->Prt().Pos();
/*N*/         aFrm.Pos().X() += pUp->Prt().Width() - aFrm.Width();
/*N*/     }
/*N*/     if( bNotify )
/*N*/         aFrm.Pos().X() -= 1;
/*N*/ }

/*N*/ void SwFrm::MakeRightPos( const SwFrm* pUp, const SwFrm* pPrv, BOOL bNotify )
/*N*/ {
/*N*/     if( pPrv )
/*N*/     {
/*N*/         aFrm.Pos( pPrv->Frm().Pos() );
/*N*/         aFrm.Pos().X() += pPrv->Frm().Width();
/*N*/     }
/*N*/     else
/*N*/     {
/*N*/         aFrm.Pos( pUp->Frm().Pos() );
/*N*/         aFrm.Pos() += pUp->Prt().Pos();
/*N*/     }
/*N*/     if( bNotify )
/*N*/         aFrm.Pos().X() += 1;
/*N*/ }

/*N*/ void SwFrm::SetTopBottomMargins( long nTop, long nBot )
/*N*/ {
/*N*/     Prt().Top( nTop );
/*N*/     Prt().Height( Frm().Height() - nTop - nBot );
/*N*/ }

/*N*/ void SwFrm::SetBottomTopMargins( long nBot, long nTop )
/*N*/ {
/*N*/     Prt().Top( nTop );
/*N*/     Prt().Height( Frm().Height() - nTop - nBot );
/*N*/ }

/*N*/ void SwFrm::SetLeftRightMargins( long nLeft, long nRight)
/*N*/ {
/*N*/     Prt().Left( nLeft );
/*N*/     Prt().Width( Frm().Width() - nLeft - nRight );
/*N*/ }

/*N*/ void SwFrm::SetRightLeftMargins( long nRight, long nLeft)
/*N*/ {
/*N*/     Prt().Left( nLeft );
/*N*/     Prt().Width( Frm().Width() - nLeft - nRight );
/*N*/ }

/*-----------------11.9.2001 11:11------------------
 * SwFrm::CheckDirChange(..)
 * checks the layout direction and
 * invalidates the lower frames rekursivly, if necessary.
 * --------------------------------------------------*/

/*N*/ void SwFrm::CheckDirChange()
/*N*/ {
/*N*/     BOOL bOldVert = GetVerticalFlag();
/*N*/     BOOL bOldRev = IsReverse();
/*N*/     BOOL bOldR2L = GetRightToLeftFlag();
/*N*/     SetInvalidVert( TRUE );
/*N*/     SetInvalidR2L( TRUE );
/*N*/     BOOL bChg = bOldR2L != IsRightToLeft();
/*N*/     if( ( IsVertical() != bOldVert ) || bChg || IsReverse() != bOldRev )
/*N*/     {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001         InvalidateAll();
//STRIP001         if( IsLayoutFrm() )
//STRIP001         {
//STRIP001             SwFrm* pFrm = ((SwLayoutFrm*)this)->Lower();
//STRIP001             const SwFmtCol* pCol = NULL;
//STRIP001             SwLayoutFrm* pBody;
//STRIP001             if( pFrm )
//STRIP001             {
//STRIP001                 if( IsPageFrm() )
//STRIP001                 {
//STRIP001                     // If we're a page frame and we change our layout direction,
//STRIP001                     // we have to look for columns and rearrange them.
//STRIP001                     pBody = ((SwPageFrm*)this)->FindBodyCont();
//STRIP001                     if(pBody && pBody->Lower() && pBody->Lower()->IsColumnFrm())
//STRIP001                         pCol = &((SwPageFrm*)this)->GetFmt()->GetCol();
//STRIP001                     SwSortDrawObjs *pObjs = ((SwPageFrm*)this)->GetSortedObjs();
//STRIP001                     if( pObjs )
//STRIP001                     {
//STRIP001                         USHORT nCnt = pObjs->Count();
//STRIP001                         for ( USHORT i = 0; i < nCnt; ++i )
//STRIP001                         {
//STRIP001                             SdrObject *pObj = (*pObjs)[i];
//STRIP001                             if ( pObj->IsWriterFlyFrame() )
//STRIP001                             {
//STRIP001                                 SwFlyFrm *pFly =
//STRIP001                                          ((SwVirtFlyDrawObj*)pObj)->GetFlyFrm();
//STRIP001                                 if( pFly->GetAnchor() == this )
//STRIP001                                     pFly->CheckDirChange();
//STRIP001                             }
//STRIP001                             else
//STRIP001                             {
//STRIP001                              const SwDrawContact* pContact =
//STRIP001                                  (SwDrawContact*)GetUserCall(pObj);
//STRIP001                              if ( pContact && pContact->GetAnchor() == this )
//STRIP001                              {
//STRIP001                                     // OD 30.06.2003 #108784# - Note: only 'at page'
//STRIP001                                     // anchored drawing objects are considered here.
//STRIP001                                     // change anchor position
//STRIP001                                     pObj->SetAnchorPos( GetFrmAnchorPos( ::HasWrap( pObj ) ) );
//STRIP001                                  // check if the new position
//STRIP001                                  // would not exceed the margins of the page
//STRIP001                                     CaptureDrawObj( *pObj, Frm() );
//STRIP001                              }
//STRIP001                             }
//STRIP001                         }
//STRIP001                     }
//STRIP001                 }
//STRIP001                 else if( pFrm->IsColumnFrm() )
//STRIP001                 {
//STRIP001                     pBody = ((SwLayoutFrm*)this);
//STRIP001                     const SwFrmFmt *pFmt = pBody->GetFmt();
//STRIP001                     if( pFmt )
//STRIP001                         pCol = &pFmt->GetCol();
//STRIP001                 }
//STRIP001             }
//STRIP001             while( pFrm )
//STRIP001             {
//STRIP001                 pFrm->CheckDirChange();
//STRIP001                 pFrm = pFrm->GetNext();
//STRIP001             }
//STRIP001             if( pCol )
//STRIP001                 pBody->AdjustColumns( pCol, TRUE );
//STRIP001         }
//STRIP001         else if( IsTxtFrm() )
//STRIP001             ((SwTxtFrm*)this)->Prepare( PREP_CLEAR );
//STRIP001
//STRIP001         if( !IsPageFrm() && GetDrawObjs() )
//STRIP001         {
//STRIP001             const SwDrawObjs *pObjs = GetDrawObjs();
//STRIP001             USHORT nCnt = pObjs->Count();
//STRIP001             for ( USHORT i = 0; i < nCnt; ++i )
//STRIP001             {
//STRIP001                 SdrObject *pObj = (*pObjs)[i];
//STRIP001                 if( pObj->IsWriterFlyFrame() )
//STRIP001                     ((SwVirtFlyDrawObj*)pObj)->GetFlyFrm()->CheckDirChange();
//STRIP001                 else
//STRIP001              {
//STRIP001                     // change anchor position
//STRIP001                     pObj->SetAnchorPos( GetFrmAnchorPos( ::HasWrap( pObj ) ) );
//STRIP001                     // OD 30.06.2003 #108784# - consider 'virtual' drawing objects:
//STRIP001                     if ( pObj->ISA(SwDrawVirtObj) )
//STRIP001                     {
//STRIP001                         static_cast<SwDrawVirtObj*>(pObj)->AdjustRelativePosToReference();
//STRIP001                     }
//STRIP001                     else
//STRIP001                     {
//STRIP001                         SwPageFrm* pPage = FindPageFrm();
//STRIP001                         if ( pPage )
//STRIP001                         {
//STRIP001                             // check if the new position
//STRIP001                             // would not exceed the margins of the page
//STRIP001                             CaptureDrawObj( *pObj, pPage->Frm() );
//STRIP001                         }
//STRIP001                         // OD 30.06.2003 #108784# - correct relative position
//STRIP001                         // of 'virtual' drawing objects.
//STRIP001                         SwDrawContact* pDrawContact =
//STRIP001                             static_cast<SwDrawContact*>(pObj->GetUserCall());
//STRIP001                         if ( pDrawContact )
//STRIP001                         {
//STRIP001                             pDrawContact->CorrectRelativePosOfVirtObjs();
//STRIP001                         }
//STRIP001                     }
//STRIP001              }
//STRIP001             }
//STRIP001         }
/*N*/     }
/*N*/ }

/*-----------------13.9.2002 11:11------------------
 * SwFrm::GetAnchorPos(..)
 * returns the position for anchors based on frame direction
 * --------------------------------------------------*/

/*N*/ Point SwFrm::GetFrmAnchorPos( sal_Bool bIgnoreFlysAnchoredAtThisFrame ) const
/*N*/ {
/*N*/     Point aAnchor = Frm().Pos();
/*N*/     if ( IsVertical() || IsRightToLeft() )
/*N*/         aAnchor.X() += Frm().Width();
/*N*/
/*N*/     if ( IsTxtFrm() )
/*N*/     {
/*N*/         SwTwips nBaseOfstForFly =
/*N*/             ((SwTxtFrm*)this)->GetBaseOfstForFly( bIgnoreFlysAnchoredAtThisFrame );
/*N*/         if ( IsVertical() )
/*N*/             aAnchor.Y() += nBaseOfstForFly;
/*N*/         else
/*N*/             aAnchor.X() += nBaseOfstForFly;
/*N*/     }
/*N*/
/*N*/     return aAnchor;
/*N*/ }


/*************************************************************************
|*
|*  SwFrm::~SwFrm()
|*
|*  Ersterstellung      MA 02. Mar. 94
|*  Letzte Aenderung    MA 25. Jun. 95
|*
|*************************************************************************/


/*N*/ SwFrm::~SwFrm()
/*N*/ {
/*N*/ #ifdef ACCESSIBLE_LAYOUT
/*N*/   // accessible objects for fly and cell frames have been already disposed
/*N*/   // by the destructors of the derived classes.
/*N*/   if( IsAccessibleFrm() && !(IsFlyFrm() || IsCellFrm()) && GetDep() )
/*N*/   {
/*N*/       SwRootFrm *pRootFrm = FindRootFrm();
/*N*/       if( pRootFrm && pRootFrm->IsAnyShellAccessible() )
/*N*/       {
/*?*/           ViewShell *pVSh = pRootFrm->GetCurrShell();
/*?*/           if( pVSh && pVSh->Imp() )
/*?*/           {
/*?*/               DBG_ASSERT(0, "STRIP"); //STRIP001 ASSERT( !GetLower(), "Lowers should be dispose already!" );
//STRIP001 /*?*/                pVSh->Imp()->DisposeAccessibleFrm( this );
/*?*/           }
/*N*/       }
/*N*/   }
/*N*/ #endif
/*N*/
/*N*/   if( pDrawObjs )
/*N*/   {
/*N*/       for ( USHORT i = pDrawObjs->Count(); i; )
/*N*/       {
/*N*/           SdrObject *pObj = (*pDrawObjs)[--i];
/*N*/           if ( pObj->IsWriterFlyFrame() )
/*N*/               delete ((SwVirtFlyDrawObj*)pObj)->GetFlyFrm();
/*N*/             else
/*N*/             // OD 23.06.2003 #108784# - consider 'virtual' drawing objects
/*N*/             {
/*N*/                 if ( pObj->GetUserCall() )
/*N*/                 {
/*N*/                     ((SwDrawContact*)pObj->GetUserCall())->DisconnectObjFromLayout( pObj );
/*N*/                 }
/*N*/             }
/*N*/       }
/*N*/       if ( pDrawObjs )
/*N*/           delete pDrawObjs;
/*N*/   }
/*N*/
/*N*/ #ifndef PRODUCT
/*N*/   // JP 15.10.2001: for detection of access to deleted frames
/*N*/   pDrawObjs = (SwDrawObjs*)0x33333333;
/*N*/ #endif
/*N*/ }

/*************************************************************************
|*
|*    SwLayoutFrm::SetFrmFmt()
|*    Ersterstellung    MA 22. Apr. 93
|*    Letzte Aenderung  MA 02. Nov. 94
|*
|*************************************************************************/


/*N*/ void SwLayoutFrm::SetFrmFmt( SwFrmFmt *pNew )
/*N*/ {
/*N*/   if ( pNew != GetFmt() )
/*N*/   {
/*N*/       SwFmtChg aOldFmt( GetFmt() );
/*N*/       pNew->Add( this );
/*N*/       SwFmtChg aNewFmt( pNew );
/*N*/       Modify( &aOldFmt, &aNewFmt );
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|*    SwCntntFrm::SwCntntFrm(), ~SwCntntFrm()
|*
|*    Ersterstellung    AK 15-Feb-1991
|*    Letzte Aenderung  MA 25. Apr. 95
|*
|*************************************************************************/


/*N*/ SwCntntFrm::SwCntntFrm( SwCntntNode * const pCntnt ) :
/*N*/   SwFrm( pCntnt ),
/*N*/   SwFlowFrm( (SwFrm&)*this )
/*N*/ {
/*N*/ }



/*N*/ SwCntntFrm::~SwCntntFrm()
/*N*/ {
/*N*/   SwCntntNode* pCNd;
/*N*/   if( 0 != ( pCNd = PTR_CAST( SwCntntNode, pRegisteredIn )) &&
/*N*/       !pCNd->GetDoc()->IsInDtor() )
/*N*/   {
/*N*/       //Bei der Root abmelden wenn ich dort noch im Turbo stehe.
/*N*/       SwRootFrm *pRoot = FindRootFrm();
/*N*/       if( pRoot && pRoot->GetTurbo() == this )
/*N*/       {
/*?*/           pRoot->DisallowTurbo();
/*?*/           pRoot->ResetTurbo();
/*N*/       }
/*N*/         if( IsTxtFrm() && ((SwTxtFrm*)this)->HasFtn() )
/*N*/         {
/*?*/             SwTxtNode *pTxtNd = ((SwTxtFrm*)this)->GetTxtNode();
/*?*/             const SwFtnIdxs &rFtnIdxs = pCNd->GetDoc()->GetFtnIdxs();
/*?*/             USHORT nPos;
/*?*/             ULONG nIndex = pCNd->GetIndex();
/*?*/             rFtnIdxs.SeekEntry( *pTxtNd, &nPos );
/*?*/             SwTxtFtn* pTxtFtn;
/*?*/             if( nPos < rFtnIdxs.Count() )
/*?*/             {
/*?*/                 while( nPos && pTxtNd == &(rFtnIdxs[ nPos ]->GetTxtNode()) )
/*?*/                     --nPos;
/*?*/                 if( nPos || pTxtNd != &(rFtnIdxs[ nPos ]->GetTxtNode()) )
/*?*/                     ++nPos;
/*?*/             }
/*?*/             while( nPos < rFtnIdxs.Count() )
/*?*/             {
/*?*/                 DBG_ASSERT(0, "STRIP"); //STRIP001 pTxtFtn = rFtnIdxs[ nPos ];
//STRIP001 /*?*/                 if( pTxtFtn->GetTxtNode().GetIndex() > nIndex )
//STRIP001 /*?*/                     break;
//STRIP001 /*?*/                 pTxtFtn->DelFrms();
//STRIP001 /*?*/                 ++nPos;
/*?*/             }
/*N*/         }
/*N*/   }
/*N*/   if( IsTxtFrm() && ((SwTxtFrm*)this)->HasBlinkPor() )
/*?*/       ((SwTxtFrm*)this)->ClearPara();
/*N*/ }

/*************************************************************************
|*
|*  SwLayoutFrm::~SwLayoutFrm
|*
|*  Ersterstellung      AK 28-Feb-1991
|*  Letzte Aenderung    MA 11. Jan. 95
|*
|*************************************************************************/


/*N*/ SwLayoutFrm::~SwLayoutFrm()
/*N*/ {
/*N*/   SwFrm *pFrm = pLower;
/*N*/
/*N*/   if( GetFmt() && !GetFmt()->GetDoc()->IsInDtor() )
/*N*/   {
/*N*/         while ( pFrm )
/*N*/       {
/*N*/           //Erst die Objs des Frm vernichten, denn diese koennen sich sonst nach
/*N*/           //dem Remove nicht mehr bei der Seite abmelden.
/*N*/           //Falls sich einer nicht abmeldet wollen wir nicht gleich
/*N*/           //endlos schleifen.
/*N*/
/*N*/             USHORT nCnt;
/*N*/           while ( pFrm->GetDrawObjs() && pFrm->GetDrawObjs()->Count() )
/*N*/           {
/*N*/               nCnt = pFrm->GetDrawObjs()->Count();
/*N*/               SdrObject *pObj = (*pFrm->GetDrawObjs())[0];
/*N*/               if ( pObj->IsWriterFlyFrame() )
/*N*/                   delete ((SwVirtFlyDrawObj*)pObj)->GetFlyFrm();
/*N*/               else if ( pObj->GetUserCall() )
/*N*/                 {
/*N*/                     // OD 19.06.2003 #108784# - adjustments for drawing objects
/*N*/                     // in header/footer.
/*N*/                     ((SwDrawContact*)pObj->GetUserCall())->DisconnectObjFromLayout( pObj );
/*N*/                 }
/*N*/
/*N*/               if ( pFrm->GetDrawObjs() &&
/*N*/                    nCnt == pFrm->GetDrawObjs()->Count() )
/*N*/                 {
/*N*/                   pFrm->GetDrawObjs()->Remove( 0 );
/*N*/                 }
/*N*/           }
/*N*/           pFrm->Remove();
/*N*/           delete pFrm;
/*N*/           pFrm = pLower;
/*N*/       }
/*N*/       //Fly's vernichten. Der letzte loescht gleich das Array.
/*N*/       USHORT nCnt;
/*N*/       while ( GetDrawObjs() && GetDrawObjs()->Count() )
/*N*/       {
/*N*/           nCnt = GetDrawObjs()->Count();
/*N*/           SdrObject *pObj = (*GetDrawObjs())[0];
/*N*/           if ( pObj->IsWriterFlyFrame() )
/*N*/               delete ((SwVirtFlyDrawObj*)pObj)->GetFlyFrm();
/*N*/           else if ( pObj->GetUserCall() )
/*N*/             {
/*N*/                 // OD 19.06.2003 #108784# - adjustments for drawing objects
/*N*/                 // in header/footer.
/*N*/                 ((SwDrawContact*)pObj->GetUserCall())->DisconnectObjFromLayout( pObj );
/*N*/             }
/*N*/
/*N*/           if ( GetDrawObjs() && nCnt == GetDrawObjs()->Count() )
/*N*/               GetDrawObjs()->Remove( 0 );
/*N*/       }
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       while( pFrm )
/*N*/       {
/*N*/           SwFrm *pNxt = pFrm->GetNext();
/*N*/           delete pFrm;
/*N*/           pFrm = pNxt;
/*N*/       }
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|*  SwFrm::PaintArea()
|*
|*  Created     AMA 08/22/2000
|*  Last change AMA 08/23/2000
|*
|*  The paintarea is the area, in which the content of a frame is allowed
|*  to be displayed. This region could be larger than the printarea (Prt())
|*  of the upper, it includes e.g. often the margin of the page.
|*
|*************************************************************************/

/*N*/ const SwRect SwFrm::PaintArea() const
/*N*/ {
/*N*/   SwRect aRect( Frm() );
/*N*/     const FASTBOOL bVert = IsVertical();
/*N*/     SwRectFn fnRect = bVert ? fnRectVert : fnRectHori;
/*N*/     long nRight = (aRect.*fnRect->fnGetRight)();
/*N*/     long nLeft  = (aRect.*fnRect->fnGetLeft)();
/*N*/   const SwFrm* pTmp = this;
/*N*/   BOOL bLeft = TRUE;
/*N*/   BOOL bRight = TRUE;
/*N*/   while( pTmp )
/*N*/   {
/*N*/         long nTmpRight = (pTmp->Frm().*fnRect->fnGetRight)();
/*N*/         long nTmpLeft = (pTmp->Frm().*fnRect->fnGetLeft)();
/*N*/       ASSERT( pTmp, "PaintArea lost in time and space" );
/*N*/       if( pTmp->IsPageFrm() || pTmp->IsFlyFrm() ||
/*N*/           pTmp->IsCellFrm() || pTmp->IsRowFrm() || //nobody leaves a table!
/*N*/           pTmp->IsRootFrm() )
/*N*/       {
/*N*/             if( bLeft || nLeft < nTmpLeft )
/*N*/                 nLeft = nTmpLeft;
/*N*/             if( bRight || nTmpRight < nRight )
/*N*/               nRight = nTmpRight;
/*N*/           if( pTmp->IsPageFrm() || pTmp->IsFlyFrm() || pTmp->IsRootFrm() )
/*N*/               break;
/*N*/           bLeft = FALSE;
/*N*/           bRight = FALSE;
/*N*/       }
/*N*/       else if( pTmp->IsColumnFrm() )  // nobody enters neightbour columns
/*N*/       {
/*N*/             BOOL bR2L = pTmp->IsRightToLeft();
/*N*/             // the first column has _no_ influence to the left range
/*N*/             if( bR2L ? pTmp->GetNext() : pTmp->GetPrev() )
/*N*/             {
/*N*/                 if( bLeft || nLeft < nTmpLeft )
/*N*/                     nLeft = nTmpLeft;
/*N*/               bLeft = FALSE;
/*N*/           }
/*N*/              // the last column has _no_ influence to the right range
/*N*/             if( bR2L ? pTmp->GetPrev() : pTmp->GetNext() )
/*N*/             {
/*N*/               if( bRight || nTmpRight < nRight )
/*N*/                     nRight = nTmpRight;
/*N*/               bRight = FALSE;
/*N*/           }
/*N*/       }
/*N*/         else if( bVert && pTmp->IsBodyFrm() )
/*N*/         {
/*?*/             // Header and footer frames have always horizontal direction and
/*?*/             // limit the body frame.
/*?*/             // A previous frame of a body frame must be a header,
/*?*/             // the next frame of a body frame may be a footnotecontainer or
/*?*/             // a footer. The footnotecontainer has the same direction like
/*?*/             // the body frame.
/*?*/             if( pTmp->GetPrev() && ( bLeft || nLeft < nTmpLeft ) )
/*?*/             {
/*?*/                 nLeft = nTmpLeft;
/*?*/                 bLeft = FALSE;
/*?*/             }
/*?*/             if( pTmp->GetNext() &&
/*?*/                 ( pTmp->GetNext()->IsFooterFrm() || pTmp->GetNext()->GetNext() )
/*?*/                 && ( bRight || nTmpRight < nRight ) )
/*?*/             {
/*?*/                 nRight = nTmpRight;
/*?*/                 bRight = FALSE;
/*?*/           }
/*N*/         }
/*N*/       pTmp = pTmp->GetUpper();
/*N*/   }
/*N*/     (aRect.*fnRect->fnSetLeft)( nLeft );
/*N*/     (aRect.*fnRect->fnSetRight)( nRight );
/*N*/   return aRect;
/*N*/ }

/*************************************************************************
|*
|*  SwFrm::UnionFrm()
|*
|*  Created     AMA 08/22/2000
|*  Last change AMA 08/23/2000
|*
|*  The unionframe is the framearea (Frm()) of a frame expanded by the
|*  printarea, if there's a negative margin at the left or right side.
|*
|*************************************************************************/

/*N*/ const SwRect SwFrm::UnionFrm( BOOL bBorder ) const
/*N*/ {
/*N*/     BOOL bVert = IsVertical();
/*N*/     SwRectFn fnRect = bVert ? fnRectVert : fnRectHori;
/*N*/     long nLeft = (Frm().*fnRect->fnGetLeft)();
/*N*/     long nWidth = (Frm().*fnRect->fnGetWidth)();
/*N*/     long nPrtLeft = (Prt().*fnRect->fnGetLeft)();
/*N*/     long nPrtWidth = (Prt().*fnRect->fnGetWidth)();
/*N*/     if( nPrtLeft + nPrtWidth > nWidth )
/*?*/         nWidth = nPrtLeft + nPrtWidth;
/*N*/     if( nPrtLeft < 0 )
/*N*/     {
/*N*/         nLeft += nPrtLeft;
/*N*/         nWidth -= nPrtLeft;
/*N*/     }
/*N*/     SwTwips nRight = nLeft + nWidth;
/*N*/     long nAdd = 0;
/*N*/   if( bBorder )
/*N*/   {
/*N*/       SwBorderAttrAccess aAccess( SwFrm::GetCache(), this );
/*N*/       const SwBorderAttrs &rAttrs = *aAccess.Get();
/*N*/       const SvxBoxItem &rBox = rAttrs.GetBox();
/*N*/       if ( rBox.GetLeft() )
/*N*/             nLeft -= rBox.CalcLineSpace( BOX_LINE_LEFT );
/*N*/       else if ( rAttrs.IsBorderDist() )
/*?*/             nLeft -= rBox.GetDistance( BOX_LINE_LEFT ) + 1;
/*N*/       if ( rBox.GetRight() )
/*N*/             nAdd += rBox.CalcLineSpace( BOX_LINE_RIGHT );
/*N*/       else if ( rAttrs.IsBorderDist() )
/*?*/             nAdd += rBox.GetDistance( BOX_LINE_RIGHT ) + 1;
/*N*/       if( rAttrs.GetShadow().GetLocation() != SVX_SHADOW_NONE )
/*N*/       {
/*N*/           const SvxShadowItem &rShadow = rAttrs.GetShadow();
/*N*/             nLeft -= rShadow.CalcShadowSpace( SHADOW_LEFT );
/*N*/             nAdd += rShadow.CalcShadowSpace( SHADOW_RIGHT );
/*N*/       }
/*N*/   }
/*N*/     if( IsTxtFrm() && ((SwTxtFrm*)this)->HasPara() )
/*N*/     {
/*N*/         long nTmp = ((SwTxtFrm*)this)->HangingMargin();
/*N*/         if( nTmp > nAdd )
/*?*/             nAdd = nTmp;
/*N*/     }
/*N*/     nWidth = nRight + nAdd - nLeft;
/*N*/   SwRect aRet( Frm() );
/*N*/     (aRet.*fnRect->fnSetPosX)( nLeft );
/*N*/     (aRet.*fnRect->fnSetWidth)( nWidth );
/*N*/   return aRet;
/*N*/ }




