/*************************************************************************
 *
 *  $RCSfile: sw_docdraw.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:48:56 $
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

#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif

#ifndef _RTL_LOGFILE_HXX_
#include <rtl/logfile.hxx>
#endif
#ifndef _OUTDEV_HXX //autogen
#include <vcl/outdev.hxx>
#endif
#ifndef _SFX_PRINTER_HXX //autogen
#include <bf_sfx2/printer.hxx>
#endif
#ifndef _EEITEM_HXX
#include <bf_svx/eeitem.hxx>
#endif
#ifndef _SVX_FLDITEM_HXX //autogen
#define ITEMID_FIELD EE_FEATURE_FIELD
#include <bf_svx/flditem.hxx>
#endif
#ifndef _MyEDITENG_HXX //autogen
#include <bf_svx/editeng.hxx>
#endif
#ifndef _SVDOUTL_HXX
#include <bf_svx/svdoutl.hxx>
#endif
#ifndef _SVX_COLRITEM_HXX //autogen
#include <bf_svx/colritem.hxx>
#endif
#ifndef _SVDPAGE_HXX //autogen
#include <bf_svx/svdpage.hxx>
#endif
#ifndef _SVDOGRP_HXX //autogen
#include <bf_svx/svdogrp.hxx>
#endif
#ifndef _SVX_LANGITEM_HXX
#include <bf_svx/langitem.hxx>
#endif

#ifndef _UNO_LINGU_HXX
#include <bf_svx/unolingu.hxx>
#endif
#ifndef _OFF_APP_HXX //autogen
#include <bf_offmgr/app.hxx>
#endif

#ifndef _SVDOMEAS_HXX
#include <bf_svx/svdfield.hxx>
#endif
#ifndef _SVDPOOL_HXX //autogen
#include <bf_svx/svdpool.hxx>
#endif

#ifndef _FMTANCHR_HXX //autogen
#include <fmtanchr.hxx>
#endif
#ifndef _CHARATR_HXX
#include <charatr.hxx>
#endif
#ifndef _FRMFMT_HXX //autogen
#include <frmfmt.hxx>
#endif
#ifndef _CHARFMT_HXX //autogen
#include <charfmt.hxx>
#endif
#ifndef _VIEWIMP_HXX //autogen
#include <viewimp.hxx>
#endif
#ifndef _SWHINTS_HXX
#include <swhints.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _DOCSH_HXX
#include <docsh.hxx>
#endif
#ifndef _ROOTFRM_HXX
#include <rootfrm.hxx>  //Damit der RootDtor gerufen wird.
#endif
#ifndef _FRAME_HXX
#include <frame.hxx>
#endif
#ifndef _POOLFMT_HXX
#include <poolfmt.hxx>
#endif
#ifndef _VIEWSH_HXX
#include <viewsh.hxx>           // fuer MakeDrawView
#endif
#ifndef _DRAWDOC_HXX
#include <drawdoc.hxx>
#endif
#ifndef _UNDOBJ_HXX
#include <undobj.hxx>
#endif
#ifndef _SWUNDO_HXX
#include <swundo.hxx>           // fuer die UndoIds
#endif
#ifndef _DCONTACT_HXX
#include <dcontact.hxx>
#endif
#ifndef _DVIEW_HXX
#include <dview.hxx>
#endif
#ifndef _MVSAVE_HXX
#include <mvsave.hxx>
#endif
#ifndef _FLYFRM_HXX
#include <flyfrm.hxx>
#endif
#ifndef _DFLYOBJ_HXX
#include <dflyobj.hxx>
#endif

#ifndef _SVDETC_HXX
#include <bf_svx/svdetc.hxx>
#endif
#ifndef _SVX_FHGTITEM_HXX
#include <bf_svx/fhgtitem.hxx>
#endif

// OD 26.06.2003 #108784#
#ifndef _SVDPAGV_HXX
#include <bf_svx/svdpagv.hxx>
#endif
namespace binfilter {

using namespace ::com::sun::star;
using namespace ::com::sun::star::linguistic2;


/*N*/ SV_IMPL_VARARR_SORT( _ZSortFlys, _ZSortFly )

/*************************************************************************
|*
|*  SwDoc::GroupSelection / SwDoc::UnGroupSelection
|*
|*  Ersterstellung      JP 21.08.95
|*  Letzte Aenderung    JP 21.08.95
|*
|*************************************************************************/

/*N*/ SwDrawContact* SwDoc::GroupSelection( SdrView& rDrawView )
/*N*/ {
    // OD 30.06.2003 #108784# - replace marked 'virtual' drawing objects by
    // the corresponding 'master' drawing objects.
DBG_ASSERT(0, "STRIP"); return NULL;    //STRIP001 SwDrawView::ReplaceMarkedDrawVirtObjs( rDrawView );
//STRIP001
//STRIP001  const SdrMarkList &rMrkList = rDrawView.GetMarkList();
//STRIP001  SwDrawFrmFmt *pFmt;
//STRIP001  SdrObject *pObj = rMrkList.GetMark( 0 )->GetObj();
//STRIP001  BOOL bNoGroup = ( 0 == pObj->GetUpGroup() );
//STRIP001  if( bNoGroup )
//STRIP001  {
//STRIP001      //Ankerattribut aufheben.
//STRIP001      SwDrawContact *pContact = (SwDrawContact*)GetUserCall(pObj);
//STRIP001      const SwFmtAnchor aAnch( pContact->GetFmt()->GetAnchor() );
//STRIP001      //Ankerpos des ersten, um die Objekte zu synchronisieren.
//STRIP001      Point aAnchPos( pObj->GetAnchorPos() );
//STRIP001
//STRIP001      SwUndoDrawGroup* pUndo = !DoesUndo() ? 0 : new SwUndoDrawGroup(
//STRIP001                                              (USHORT)rMrkList.GetMarkCount() );
//STRIP001
//STRIP001      //ContactObjekte und Formate vernichten.
//STRIP001      for( USHORT i = 0; i < rMrkList.GetMarkCount(); ++i )
//STRIP001      {
//STRIP001          pObj = rMrkList.GetMark( i )->GetObj();
//STRIP001          SwDrawContact *pContact = (SwDrawContact*)GetUserCall(pObj);
//STRIP001
//STRIP001          //Ankerpos und Relpos synchronisieren, damit die Position der
//STRIP001          //Objekte erhalten bleibt.
//STRIP001             const Point aAbs( pContact->GetAnchor()->GetFrmAnchorPos( ::HasWrap( pObj ) ) +
//STRIP001                              pObj->GetRelativePos() );
//STRIP001
//STRIP001          pFmt = (SwDrawFrmFmt*)pContact->GetFmt();
//STRIP001          //loescht sich selbst!
//STRIP001          pContact->Changed(*pObj, SDRUSERCALL_DELETE, pObj->GetBoundRect() );
//STRIP001          pObj->SetUserCall( 0 );
//STRIP001
//STRIP001          if( pUndo )
//STRIP001              pUndo->AddObj( i, pFmt, pObj );
//STRIP001          else
//STRIP001              DelFrmFmt( pFmt );
//STRIP001
//STRIP001          pObj->NbcSetRelativePos( aAbs - aAnchPos );
//STRIP001          pObj->NbcSetAnchorPos( aAnchPos );
//STRIP001      }
//STRIP001
//STRIP001      pFmt = MakeDrawFrmFmt( String::CreateFromAscii(
//STRIP001                              RTL_CONSTASCII_STRINGPARAM( "DrawObject" )),
//STRIP001                              GetDfltFrmFmt() );
//STRIP001      pFmt->SetAttr( aAnch );
//STRIP001
//STRIP001      if( pUndo )
//STRIP001      {
//STRIP001          pUndo->SetGroupFmt( pFmt );
//STRIP001          ClearRedo();
//STRIP001          AppendUndo( pUndo );
//STRIP001      }
//STRIP001  }
//STRIP001  else if( DoesUndo() )
//STRIP001      ClearRedo();
//STRIP001
//STRIP001  rDrawView.GroupMarked();
//STRIP001  ASSERT( rMrkList.GetMarkCount() == 1, "GroupMarked more or none groups." );
//STRIP001  SwDrawContact *pNewContact = 0;
//STRIP001  if( bNoGroup )
//STRIP001  {
//STRIP001      pNewContact = new SwDrawContact( pFmt, rMrkList.GetMark( 0 )->GetObj() );
//STRIP001      pNewContact->ConnectToLayout();
//STRIP001  }
//STRIP001  return pNewContact;
/*N*/ }


/*N*/ void SwDoc::UnGroupSelection( SdrView& rDrawView )
/*N*/ {
/*N*/ DBG_ASSERT(0, "STRIP"); //STRIP001    int bUndo = DoesUndo();
//STRIP001  if( bUndo )
//STRIP001      ClearRedo();
//STRIP001
//STRIP001     // OD 30.06.2003 #108784# - replace marked 'virtual' drawing objects by
//STRIP001     // the corresponding 'master' drawing objects.
//STRIP001     SwDrawView::ReplaceMarkedDrawVirtObjs( rDrawView );
//STRIP001
//STRIP001  const SdrMarkList &rMrkList = rDrawView.GetMarkList();
//STRIP001  if( rMrkList.GetMarkCount() )
//STRIP001  {
//STRIP001      SdrObject *pObj = rMrkList.GetMark( 0 )->GetObj();
//STRIP001      if( !pObj->GetUpGroup() )
//STRIP001      {
//STRIP001          String sDrwFmtNm( String::CreateFromAscii(
//STRIP001                              RTL_CONSTASCII_STRINGPARAM("DrawObject" )));
//STRIP001          for ( USHORT i = 0; i < rMrkList.GetMarkCount(); ++i )
//STRIP001          {
//STRIP001              SdrObject *pObj = rMrkList.GetMark( i )->GetObj();
//STRIP001              if ( pObj->IsA( TYPE(SdrObjGroup) ) )
//STRIP001              {
//STRIP001                  SwDrawContact *pContact = (SwDrawContact*)GetUserCall(pObj);
//STRIP001                  SwFmtAnchor aAnch( pContact->GetFmt()->GetAnchor() );
//STRIP001                  SdrObjList *pLst = ((SdrObjGroup*)pObj)->GetSubList();
//STRIP001
//STRIP001                  SwUndoDrawUnGroup* pUndo = 0;
//STRIP001                  if( bUndo )
//STRIP001                  {
//STRIP001                      pUndo = new SwUndoDrawUnGroup( (SdrObjGroup*)pObj );
//STRIP001                      AppendUndo( pUndo );
//STRIP001                  }
//STRIP001
//STRIP001                  for ( USHORT i2 = 0; i2 < pLst->GetObjCount(); ++i2 )
//STRIP001                  {
//STRIP001                      SdrObject *pSubObj = pLst->GetObj( i2 );
//STRIP001                      SwDrawFrmFmt *pFmt = MakeDrawFrmFmt( sDrwFmtNm,
//STRIP001                                                          GetDfltFrmFmt() );
//STRIP001                      pFmt->SetAttr( aAnch );
//STRIP001                      SwDrawContact *pContact = new SwDrawContact( pFmt, pSubObj );
//STRIP001                      pContact->ConnectToLayout();
//STRIP001
//STRIP001                      if( bUndo )
//STRIP001                          pUndo->AddObj( i2, pFmt );
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  rDrawView.UnGroupMarked();
/*N*/ }

/*************************************************************************
|*
|*  SwDoc::DeleteSelection()
|*
|*  Ersterstellung      MA 14. Nov. 95
|*  Letzte Aenderung    MA 14. Nov. 95
|*
|*************************************************************************/

//STRIP001 BOOL SwDoc::DeleteSelection( SwDrawView& rDrawView )
//STRIP001 {
//STRIP001  BOOL bCallBase = FALSE;
//STRIP001  const SdrMarkList &rMrkList = rDrawView.GetMarkList();
//STRIP001  if( rMrkList.GetMarkCount() )
//STRIP001  {
//STRIP001      StartUndo();
//STRIP001      USHORT i;
//STRIP001      FASTBOOL bDelMarked = TRUE;
//STRIP001
//STRIP001      if( 1 == rMrkList.GetMarkCount() )
//STRIP001      {
//STRIP001          SdrObject *pObj = rMrkList.GetMark( 0 )->GetObj();
//STRIP001          if( pObj->IsWriterFlyFrame() )
//STRIP001          {
//STRIP001              SwFlyFrmFmt* pFrmFmt = (SwFlyFrmFmt*)
//STRIP001                  ((SwVirtFlyDrawObj*)pObj)->GetFlyFrm()->GetFmt();
//STRIP001              if( pFrmFmt )
//STRIP001              {
//STRIP001 #if 0
//STRIP001 // JP 28.09.98: erstmal wuerde ich NEIN sagen.
//STRIP001 // muss das sein ????
//STRIP001                  // ggfs. die CrsrPosition umsetzen
//STRIP001                  SwCrsrShell* pCShell = PTR_CAST( SwCrsrShell,
//STRIP001                                          rDrawView.Imp().GetShell() );
//STRIP001                  if( pCShell )
//STRIP001                  {
//STRIP001                      SwRect& rChrRect = (SwRect&)pCShell->GetCharRect();
//STRIP001                      SwFlyFrm* pFly = pFrmFmt->GetFrm( &rChrRect.Pos(), FALSE );
//STRIP001
//STRIP001                      if( pFly && pFly->IsFlyInCntFrm() )
//STRIP001                      {
//STRIP001                          rChrRect = pFly->Frm();
//STRIP001                          pCShell->GetCrsrDocPos() = rChrRect.Pos();
//STRIP001                      }
//STRIP001                  }
//STRIP001 // muss das sein ????
//STRIP001 #endif
//STRIP001                  DelLayoutFmt( pFrmFmt );
//STRIP001                  bDelMarked = FALSE;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      for( i = 0; i < rMrkList.GetMarkCount(); ++i )
//STRIP001      {
//STRIP001          SdrObject *pObj = rMrkList.GetMark( i )->GetObj();
//STRIP001          if( !pObj->IsWriterFlyFrame() )
//STRIP001          {
//STRIP001              SwDrawContact *pC = (SwDrawContact*)GetUserCall(pObj);
//STRIP001              SwDrawFrmFmt *pFrmFmt = (SwDrawFrmFmt*)pC->GetFmt();
//STRIP001              if( pFrmFmt &&
//STRIP001                  FLY_IN_CNTNT == pFrmFmt->GetAnchor().GetAnchorId() )
//STRIP001              {
//STRIP001                  rDrawView.MarkObj( pObj, rDrawView.Imp().GetPageView(), TRUE );
//STRIP001                  --i;
//STRIP001                  DelLayoutFmt( pFrmFmt );
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      if( rMrkList.GetMarkCount() && bDelMarked )
//STRIP001      {
//STRIP001          SdrObject *pObj = rMrkList.GetMark( 0 )->GetObj();
//STRIP001          if( !pObj->GetUpGroup() )
//STRIP001          {
//STRIP001              SwUndoDrawDelete* pUndo = !DoesUndo() ? 0
//STRIP001                          : new SwUndoDrawDelete( (USHORT)rMrkList.GetMarkCount() );
//STRIP001
//STRIP001              //ContactObjekte vernichten, Formate sicherstellen.
//STRIP001              for( i = 0; i < rMrkList.GetMarkCount(); ++i )
//STRIP001              {
//STRIP001                  const SdrMark& rMark = *rMrkList.GetMark( i );
//STRIP001                  pObj = rMark.GetObj();
//STRIP001                  SwDrawContact *pContact = (SwDrawContact*)pObj->GetUserCall();
//STRIP001                  if( pContact ) // natuerlich nicht bei gruppierten Objekten
//STRIP001                  {
//STRIP001                      SwDrawFrmFmt *pFmt = (SwDrawFrmFmt*)pContact->GetFmt();
//STRIP001                         // OD 18.06.2003 #108784# - before delete of selection
//STRIP001                         // is performed, marked <SwDrawVirtObj>-objects have to
//STRIP001                         // be replaced by its reference objects.
//STRIP001                         // Thus, assert, if a <SwDrawVirt>-object is found in the mark list.
//STRIP001                         if ( pObj->ISA(SwDrawVirtObj) )
//STRIP001                         {
//STRIP001                             ASSERT( false,
//STRIP001                                     "<SwDrawVirtObj> is still marked for delete. application will crash!" );
//STRIP001                         }
//STRIP001                      //loescht sich selbst!
//STRIP001                      pContact->Changed(*pObj, SDRUSERCALL_DELETE, pObj->GetBoundRect() );
//STRIP001                      pObj->SetUserCall( 0 );
//STRIP001
//STRIP001                      if( pUndo )
//STRIP001                          pUndo->AddObj( i, pFmt, rMark );
//STRIP001                      else
//STRIP001                          DelFrmFmt( pFmt );
//STRIP001                  }
//STRIP001              }
//STRIP001
//STRIP001              if( pUndo )
//STRIP001                  AppendUndo( pUndo );
//STRIP001          }
//STRIP001          bCallBase = TRUE;
//STRIP001      }
//STRIP001      SetModified();
//STRIP001
//STRIP001      EndUndo();
//STRIP001  }
//STRIP001
//STRIP001  return bCallBase;
//STRIP001 }

/*************************************************************************
|*
|*  SwDoc::DeleteSelection()
|*
|*  Ersterstellung      JP 11.01.96
|*  Letzte Aenderung    JP 11.01.96
|*
|*************************************************************************/

/*N*/ _ZSortFly::_ZSortFly( const SwFrmFmt* pFrmFmt, const SwFmtAnchor* pFlyAn,
/*N*/                     UINT32 nArrOrdNum )
/*N*/   : pFmt( pFrmFmt ), pAnchor( pFlyAn ), nOrdNum( nArrOrdNum )
/*N*/ {
/*N*/       // #i11176#
/*N*/   // This also needs to work when no layout exists. Thus, for
/*N*/   // FlyFrames an alternative method is used now in that case.
/*N*/   SwClientIter aIter( (SwFmt&)*pFmt );
/*N*/
/*N*/   if( RES_FLYFRMFMT == pFmt->Which() )
/*N*/   {
/*N*/       if( pFmt->GetDoc()->GetRootFrm() )
/*N*/       {
/*N*/           // Schauen, ob es ein SdrObject dafuer gibt
/*N*/           if( aIter.First( TYPE( SwFlyFrm) ) )
/*N*/               nOrdNum = ((SwFlyFrm*)aIter())->GetVirtDrawObj()->GetOrdNum();
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           // Schauen, ob es ein SdrObject dafuer gibt
/*N*/           if( aIter.First( TYPE(SwFlyDrawContact) ) )
/*N*/               nOrdNum = ((SwFlyDrawContact*)aIter())->GetMaster()->GetOrdNum();
/*N*/       }
/*N*/   }
/*N*/   else if( RES_DRAWFRMFMT == pFmt->Which() )
/*N*/   {
/*N*/           // Schauen, ob es ein SdrObject dafuer gibt
/*N*/           if( aIter.First( TYPE(SwDrawContact) ) )
/*N*/               nOrdNum = ((SwDrawContact*)aIter())->GetMaster()->GetOrdNum();
/*N*/   }
/*N*/   else
/*N*/           ASSERT( !this, "was ist das fuer ein Format?" );
/*N*/ }
} //namespace binfilter
/*************************************************************************/
// Wird auch vom Sw3-Reader gerufen, wenn ein Fehler beim Einlesen
// des Drawing Layers auftrat. In diesem Fall wird der Layer komplett
// neu aufgebaut.

// #75371#
#ifndef _SXENDITM_HXX
#include <bf_svx/sxenditm.hxx>
#endif

namespace binfilter {//STRIP009
/*N*/ void SwDoc::InitDrawModel()
/*N*/ {
/*N*/   RTL_LOGFILE_CONTEXT_AUTHOR( aLog, "SW", "JP93722",  "SwDoc::InitDrawModel" );
/*N*/
/*N*/   //!!Achtung im sw3-Reader (sw3imp.cxx) gibt es aehnlichen Code, der
/*N*/   //mitgepfelgt werden muss.
/*N*/   if ( pDrawModel )
/*?*/       ReleaseDrawModel();
/*N*/
/*N*/   //DrawPool und EditEnginePool anlegen, diese gehoeren uns und werden
/*N*/   //dem Drawing nur mitgegeben. Im ReleaseDrawModel werden die Pools wieder
/*N*/   //zerstoert.
/*N*/   // 17.2.99: for Bug 73110 - for loading the drawing items. This must
/*N*/   //                          be loaded without RefCounts!
/*N*/   SfxItemPool *pSdrPool = new SdrItemPool( &aAttrPool, SDRATTR_START,
/*N*/                                           SDRATTR_END, FALSE );
/*N*/   // #75371# change DefaultItems for the SdrEdgeObj distance items
/*N*/   // to TWIPS.
/*N*/   if(pSdrPool)
/*N*/   {
/*N*/       const long nDefEdgeDist = ((500 * 72) / 127); // 1/100th mm in twips
/*N*/       pSdrPool->SetPoolDefaultItem(SdrEdgeNode1HorzDistItem(nDefEdgeDist));
/*N*/       pSdrPool->SetPoolDefaultItem(SdrEdgeNode1VertDistItem(nDefEdgeDist));
/*N*/       pSdrPool->SetPoolDefaultItem(SdrEdgeNode2HorzDistItem(nDefEdgeDist));
/*N*/       pSdrPool->SetPoolDefaultItem(SdrEdgeNode2VertDistItem(nDefEdgeDist));
/*N*/   }
/*N*/   SfxItemPool *pEEgPool = EditEngine::CreatePool( FALSE );
/*N*/   pSdrPool->SetSecondaryPool( pEEgPool );
/*N*/   if ( !aAttrPool.GetFrozenIdRanges () )
/*N*/       aAttrPool.FreezeIdRanges();
/*N*/   else
/*?*/       pSdrPool->FreezeIdRanges();
/*N*/
/*N*/     // SJ: #95129# set FontHeight pool defaults without changing static SdrEngineDefaults
/*N*/   aAttrPool.SetPoolDefaultItem(SvxFontHeightItem( 240, 100, EE_CHAR_FONTHEIGHT ));
/*N*/
/*N*/   RTL_LOGFILE_CONTEXT_TRACE( aLog, "before create DrawDocument" );
/*N*/   //Das SdrModel gehoert dem Dokument, wir haben immer zwei Layer und eine
/*N*/   //Seite.
/*N*/   pDrawModel = new SwDrawDocument( this );
/*N*/
/*N*/   String sLayerNm;
/*N*/   sLayerNm.AssignAscii(RTL_CONSTASCII_STRINGPARAM("Hell" ));
/*N*/   nHell   = pDrawModel->GetLayerAdmin().NewLayer( sLayerNm )->GetID();
/*N*/
/*N*/   sLayerNm.AssignAscii(RTL_CONSTASCII_STRINGPARAM("Heaven" ));
/*N*/   nHeaven = pDrawModel->GetLayerAdmin().NewLayer( sLayerNm )->GetID();
/*N*/
/*N*/   sLayerNm.AssignAscii(RTL_CONSTASCII_STRINGPARAM("Controls" ));
/*N*/   nControls = pDrawModel->GetLayerAdmin().NewLayer( sLayerNm )->GetID();
/*N*/
/*N*/     // OD 25.06.2003 #108784# - add invisible layers corresponding to the
/*N*/     // visible ones.
/*N*/     {
/*N*/         sLayerNm.AssignAscii(RTL_CONSTASCII_STRINGPARAM("InvisibleHell" ));
/*N*/         nInvisibleHell   = pDrawModel->GetLayerAdmin().NewLayer( sLayerNm )->GetID();
/*N*/
/*N*/         sLayerNm.AssignAscii(RTL_CONSTASCII_STRINGPARAM("InvisibleHeaven" ));
/*N*/         nInvisibleHeaven = pDrawModel->GetLayerAdmin().NewLayer( sLayerNm )->GetID();
/*N*/
/*N*/         sLayerNm.AssignAscii(RTL_CONSTASCII_STRINGPARAM("InvisibleControls" ));
/*N*/         nInvisibleControls = pDrawModel->GetLayerAdmin().NewLayer( sLayerNm )->GetID();
/*N*/     }
/*N*/
/*N*/   pDrawModel->InsertPage( pDrawModel->AllocPage( FALSE ) );
/*N*/   RTL_LOGFILE_CONTEXT_TRACE( aLog, "after create DrawDocument" );
/*N*/
/*N*/   RTL_LOGFILE_CONTEXT_TRACE( aLog, "before create Spellchecker/Hyphenator" );
/*N*/   SdrOutliner& rOutliner = pDrawModel->GetDrawOutliner();
/*N*/   uno::Reference< XSpellChecker1 > xSpell = ::binfilter::GetSpellChecker();
/*N*/   rOutliner.SetSpeller( xSpell );
/*N*/     uno::Reference<XHyphenator> xHyphenator( ::binfilter::GetHyphenator() );
/*N*/   rOutliner.SetHyphenator( xHyphenator );
/*N*/   RTL_LOGFILE_CONTEXT_TRACE( aLog, "after create Spellchecker/Hyphenator" );
/*N*/
/*N*/   SetCalcFieldValueHdl(&rOutliner);
/*N*/   SetCalcFieldValueHdl(&pDrawModel->GetHitTestOutliner());
/*N*/
/*N*/   //JP 16.07.98: Bug 50193 - Linkmanager am Model setzen, damit
/*N*/   //          dort ggfs. verlinkte Grafiken eingefuegt werden koennen
/*N*/   //JP 28.01.99: der WinWord Import benoetigt ihn auch
/*N*/   pDrawModel->SetLinkManager( &GetLinkManager() );
/*N*/
/*N*/       OutputDevice* pRefDev = _GetRefDev();
/*N*/     if ( pRefDev )
/*N*/         pDrawModel->SetRefDevice( pRefDev );
/*N*/   pDrawModel->SetNotifyUndoActionHdl( LINK( this, SwDoc, AddDrawUndo ));
/*N*/   if ( pLayout )
/*N*/   {
/*N*/       pLayout->SetDrawPage( pDrawModel->GetPage( 0 ) );
/*N*/       pLayout->GetDrawPage()->SetSize( pLayout->Frm().SSize() );
/*N*/   }
/*N*/ }

/** method to notify drawing page view about the invisible layers

    OD 26.06.2003 #108784#

    @author OD
*/
void SwDoc::NotifyInvisibleLayers( SdrPageView& _rSdrPageView )
{
    String sLayerNm;
    sLayerNm.AssignAscii(RTL_CONSTASCII_STRINGPARAM("InvisibleHell" ));
    _rSdrPageView.SetLayerVisible( sLayerNm, FALSE );

    sLayerNm.AssignAscii(RTL_CONSTASCII_STRINGPARAM("InvisibleHeaven" ));
    _rSdrPageView.SetLayerVisible( sLayerNm, FALSE );

    sLayerNm.AssignAscii(RTL_CONSTASCII_STRINGPARAM("InvisibleControls" ));
    _rSdrPageView.SetLayerVisible( sLayerNm, FALSE );
}

/** method to determine, if a layer ID belongs to the visible ones.

    OD 25.06.2003 #108784#
    Note: If given layer ID is unknown, method asserts and returns <false>.

    @author OD
*/
bool SwDoc::IsVisibleLayerId( const SdrLayerID& _nLayerId )
{
    bool bRetVal;

    if ( _nLayerId == GetHeavenId() ||
         _nLayerId == GetHellId() ||
         _nLayerId == GetControlsId() )
    {
        bRetVal = true;
    }
    else if ( _nLayerId == GetInvisibleHeavenId() ||
              _nLayerId == GetInvisibleHellId() ||
              _nLayerId == GetInvisibleControlsId() )
    {
        bRetVal = false;
    }
    else
    {
        ASSERT( false, "<SwDoc::IsVisibleLayerId(..)> - unknown layer ID." );
        bRetVal = false;
    }

    return bRetVal;
}

/** method to determine, if the corresponding visible layer ID for a invisible one.

    OD 25.06.2003 #108784#
    Note: If given layer ID is a visible one, method returns given layer ID.
    Note: If given layer ID is unknown, method returns given layer ID.

    @author OD
*/
SdrLayerID SwDoc::GetVisibleLayerIdByInvisibleOne( const SdrLayerID& _nInvisibleLayerId )
{
    SdrLayerID nVisibleLayerId;

    if ( _nInvisibleLayerId == GetInvisibleHeavenId() )
    {
        nVisibleLayerId = GetHeavenId();
    }
    else if ( _nInvisibleLayerId == GetInvisibleHellId() )
    {
        nVisibleLayerId = GetHellId();
    }
    else if ( _nInvisibleLayerId == GetInvisibleControlsId() )
    {
        nVisibleLayerId = GetControlsId();
    }
    else if ( _nInvisibleLayerId == GetHeavenId() ||
              _nInvisibleLayerId == GetHellId() ||
              _nInvisibleLayerId == GetControlsId() )
    {
        ASSERT( false, "<SwDoc::GetVisibleLayerIdByInvisibleOne(..)> - given layer ID already an invisible one." );
        nVisibleLayerId = _nInvisibleLayerId;
    }
    else
    {
        ASSERT( false, "<SwDoc::GetVisibleLayerIdByInvisibleOne(..)> - given layer ID is unknown." );
        nVisibleLayerId = _nInvisibleLayerId;
    }

    return nVisibleLayerId;
}

/** method to determine, if the corresponding invisible layer ID for a visible one.

    OD 25.06.2003 #108784#
    Note: If given layer ID is a invisible one, method returns given layer ID.
    Note: If given layer ID is unknown, method returns given layer ID.

    @author OD
*/
SdrLayerID SwDoc::GetInvisibleLayerIdByVisibleOne( const SdrLayerID& _nVisibleLayerId )
{
    SdrLayerID nInvisibleLayerId;

    if ( _nVisibleLayerId == GetHeavenId() )
    {
        nInvisibleLayerId = GetInvisibleHeavenId();
    }
    else if ( _nVisibleLayerId == GetHellId() )
    {
        nInvisibleLayerId = GetInvisibleHellId();
    }
    else if ( _nVisibleLayerId == GetControlsId() )
    {
        nInvisibleLayerId = GetInvisibleControlsId();
    }
    else if ( _nVisibleLayerId == GetInvisibleHeavenId() ||
              _nVisibleLayerId == GetInvisibleHellId() ||
              _nVisibleLayerId == GetInvisibleControlsId() )
    {
        ASSERT( false, "<SwDoc::GetInvisibleLayerIdByVisibleOne(..)> - given layer ID already an invisible one." );
        nInvisibleLayerId = _nVisibleLayerId;
    }
    else
    {
        ASSERT( false, "<SwDoc::GetInvisibleLayerIdByVisibleOne(..)> - given layer ID is unknown." );
        nInvisibleLayerId = _nVisibleLayerId;
    }

    return nInvisibleLayerId;
}

/*************************************************************************/


/*N*/ void SwDoc::ReleaseDrawModel()
/*N*/ {
/*N*/   if ( pDrawModel )
/*N*/   {
/*N*/       //!!Den code im sw3io fuer Einfuegen Dokument mitpflegen!!
/*N*/
/*N*/       delete pDrawModel; pDrawModel = 0;
/*N*/       SfxItemPool *pSdrPool = aAttrPool.GetSecondaryPool();
/*N*/
/*N*/       ASSERT( pSdrPool, "missing Pool" );
/*N*/       SfxItemPool *pEEgPool = pSdrPool->GetSecondaryPool();
/*N*/       ASSERT( !pEEgPool->GetSecondaryPool(), "i don't accept additional pools");
/*N*/       pSdrPool->Delete();                 //Erst die Items vernichten lassen,
/*N*/                                           //dann erst die Verkettung loesen
/*N*/       aAttrPool.SetSecondaryPool( 0 );    //Der ist ein muss!
/*N*/       pSdrPool->SetSecondaryPool( 0 );    //Der ist sicherer
/*N*/       delete pSdrPool;
/*N*/       delete pEEgPool;
/*N*/   }
/*N*/ }

/*************************************************************************/


/*N*/ SdrModel* SwDoc::_MakeDrawModel()
/*N*/ {
/*N*/   ASSERT( !pDrawModel, "_MakeDrawModel: Why?" );
/*N*/   InitDrawModel();
/*N*/   if ( pLayout && pLayout->GetCurrShell() )
/*N*/   {
/*N*/       ViewShell* pTmp = pLayout->GetCurrShell();
/*N*/       do
/*N*/       {
/*N*/           pTmp->MakeDrawView();
/*N*/           pTmp = (ViewShell*) pTmp->GetNext();
/*N*/       } while ( pTmp != pLayout->GetCurrShell() );
/*N*/
/*N*/       //Broadcast, damit die FormShell mit der DrawView verbunden werden kann
/*N*/       if( GetDocShell() )
/*N*/       {
/*N*/           SfxSimpleHint aHnt( SW_BROADCAST_DRAWVIEWS_CREATED );
/*N*/           GetDocShell()->Broadcast( aHnt );
/*N*/       }
/*N*/   }
/*N*/   return pDrawModel;
/*N*/ }

/*************************************************************************/

/*N*/ void SwDoc::DrawNotifyUndoHdl()
/*N*/ {
/*N*/   pDrawModel->SetNotifyUndoActionHdl( Link() );
/*N*/ }

/*************************************************************************/
/*
/* Am Outliner Link auf Methode fuer Felddarstellung in Editobjekten setzen
/*
/*************************************************************************/

/*N*/ void SwDoc::SetCalcFieldValueHdl(Outliner* pOutliner)
/*N*/ {
/*N*/   pOutliner->SetCalcFieldValueHdl(LINK(this, SwDoc, CalcFieldValueHdl));
/*N*/ }

/*************************************************************************
|*
|* Felder bzw URLs im Outliner erkennen und Darstellung festlegen
|*
\************************************************************************/

/*N*/ IMPL_LINK(SwDoc, CalcFieldValueHdl, EditFieldInfo*, pInfo)
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  if (pInfo)
//STRIP001  {
//STRIP001      const SvxFieldItem& rField = pInfo->GetField();
//STRIP001      const SvxFieldData* pField = rField.GetField();
//STRIP001
//STRIP001      if (pField && pField->ISA(SvxDateField))
//STRIP001      {
//STRIP001          /******************************************************************
//STRIP001          * Date-Field
//STRIP001          ******************************************************************/
//STRIP001          pInfo->SetRepresentation(
//STRIP001              ((const SvxDateField*) pField)->GetFormatted(
//STRIP001                      *GetNumberFormatter( TRUE ), LANGUAGE_SYSTEM) );
//STRIP001      }
//STRIP001      else if (pField && pField->ISA(SvxURLField))
//STRIP001      {
//STRIP001          /******************************************************************
//STRIP001          * URL-Field
//STRIP001          ******************************************************************/
//STRIP001
//STRIP001          switch ( ((const SvxURLField*) pField)->GetFormat() )
//STRIP001          {
//STRIP001              case SVXURLFORMAT_APPDEFAULT: //!!! einstellbar an App???
//STRIP001              case SVXURLFORMAT_REPR:
//STRIP001              {
//STRIP001                  pInfo->SetRepresentation(
//STRIP001                      ((const SvxURLField*)pField)->GetRepresentation());
//STRIP001              }
//STRIP001              break;
//STRIP001
//STRIP001              case SVXURLFORMAT_URL:
//STRIP001              {
//STRIP001                  pInfo->SetRepresentation(
//STRIP001                      ((const SvxURLField*)pField)->GetURL());
//STRIP001              }
//STRIP001              break;
//STRIP001          }
//STRIP001
//STRIP001          USHORT nChrFmt;
//STRIP001
//STRIP001          if (IsVisitedURL(((const SvxURLField*)pField)->GetURL()))
//STRIP001              nChrFmt = RES_POOLCHR_INET_VISIT;
//STRIP001          else
//STRIP001              nChrFmt = RES_POOLCHR_INET_NORMAL;
//STRIP001
//STRIP001          SwFmt *pFmt = GetCharFmtFromPool(nChrFmt);
//STRIP001
//STRIP001          Color aColor(COL_LIGHTBLUE);
//STRIP001          if (pFmt)
//STRIP001              aColor = pFmt->GetColor().GetValue();
//STRIP001
//STRIP001          pInfo->SetTxtColor(aColor);
//STRIP001      }
//STRIP001      else if (pField && pField->ISA(SdrMeasureField))
//STRIP001      {
//STRIP001          /******************************************************************
//STRIP001          * Measure-Field
//STRIP001          ******************************************************************/
//STRIP001          pInfo->ClearFldColor();
//STRIP001      }
//STRIP001         else if ( pField && pField->ISA(SvxExtTimeField))
//STRIP001         {
//STRIP001             /******************************************************************
//STRIP001             * Time-Field
//STRIP001             ******************************************************************/
//STRIP001             pInfo->SetRepresentation(
//STRIP001                 ((const SvxExtTimeField*) pField)->GetFormatted(
//STRIP001                         *GetNumberFormatter( TRUE ), LANGUAGE_SYSTEM) );
//STRIP001         }
//STRIP001      else
//STRIP001      {
//STRIP001          DBG_ERROR("unbekannter Feldbefehl");
//STRIP001          pInfo->SetRepresentation( String( '?' ) );
//STRIP001      }
//STRIP001  }
//STRIP001
/*N*/  return(0);
/*N*/ }
}
