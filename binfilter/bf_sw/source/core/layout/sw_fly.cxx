/*************************************************************************
 *
 *  $RCSfile: sw_fly.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 15:27:05 $
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

#include "hintids.hxx"
#ifndef _SFXITEMITER_HXX //autogen
#include <svtools/itemiter.hxx>
#endif
#ifndef _IMAP_HXX //autogen
#include <svtools/imap.hxx>
#endif
#ifndef _GRAPH_HXX //autogen
#include <vcl/graph.hxx>
#endif
#ifndef _POLY_HXX //autogen
#include <vcl/poly.hxx>
#endif
#ifndef _CONTDLG_HXX_ //autogen
#include <bf_svx/contdlg.hxx>
#endif
#ifndef _SVX_PROTITEM_HXX //autogen
#include <bf_svx/protitem.hxx>
#endif
#ifndef _SVX_OPAQITEM_HXX //autogen
#include <bf_svx/opaqitem.hxx>
#endif
#ifndef _SVX_ULSPITEM_HXX //autogen
#include <bf_svx/ulspitem.hxx>
#endif
#ifndef _SVX_LRSPITEM_HXX //autogen
#include <bf_svx/lrspitem.hxx>
#endif
#ifndef _SVX_FRMDIRITEM_HXX
#include <bf_svx/frmdiritem.hxx>
#endif

#ifndef _FMTANCHR_HXX //autogen
#include <fmtanchr.hxx>
#endif
#ifndef _FMTFSIZE_HXX //autogen
#include <fmtfsize.hxx>
#endif
#ifndef _FMTCLDS_HXX //autogen
#include <fmtclds.hxx>
#endif
#ifndef _FMTCNTNT_HXX //autogen
#include <fmtcntnt.hxx>
#endif
#ifndef _FMTURL_HXX //autogen
#include <fmturl.hxx>
#endif
#ifndef _FMTSRND_HXX //autogen
#include <fmtsrnd.hxx>
#endif
#ifndef _FMTORNT_HXX //autogen
#include <fmtornt.hxx>
#endif
#ifndef _FMTPDSC_HXX //autogen
#include <fmtpdsc.hxx>
#endif
#ifndef _FMTCNCT_HXX //autogen
#include <fmtcnct.hxx>
#endif
#ifndef _LAYHELP_HXX
#include <layhelp.hxx>
#endif
// OD 16.04.2003 #i13147# - for <SwFlyFrm::GetContour(..)>
#ifndef _NDGRF_HXX
#include <ndgrf.hxx>
#endif

#include "doc.hxx"
#include "viewsh.hxx"
#include "layouter.hxx"
#include "pagefrm.hxx"
#include "rootfrm.hxx"
#include "cntfrm.hxx"
#include "pam.hxx"
#include "frmatr.hxx"
#include "viewimp.hxx"
#include "errhdl.hxx"
#include "dcontact.hxx"
#include "dflyobj.hxx"
#include "dview.hxx"
#include "flyfrm.hxx"
#include "frmtool.hxx"
#include "frmfmt.hxx"
#include "hints.hxx"
#include "swregion.hxx"
#include "frmsh.hxx"
#include "tabfrm.hxx"
#include "txtfrm.hxx"
#include "ndnotxt.hxx"
#include "notxtfrm.hxx"   // GetGrfArea
#include "flyfrms.hxx"
#include "ndindex.hxx"   // GetGrfArea
#include "sectfrm.hxx"

//Aus dem PageFrm:

/*N*/ SV_IMPL_PTRARR_SORT(SwSortDrawObjs,SdrObjectPtr)


/*************************************************************************
|*
|*  SwFlyFrm::SwFlyFrm()
|*
|*  Ersterstellung      MA 28. Sep. 92
|*  Letzte Aenderung    MA 09. Apr. 99
|*
|*************************************************************************/

/*N*/ SwFlyFrm::SwFlyFrm( SwFlyFrmFmt *pFmt, SwFrm *pAnch ) :
/*N*/   SwLayoutFrm( pFmt ),
/*N*/   aRelPos(),
/*N*/   pAnchor( 0 ),
/*N*/   pPrevLink( 0 ),
/*N*/   pNextLink( 0 ),
/*N*/   bInCnt( FALSE ),
/*N*/   bAtCnt( FALSE ),
/*N*/   bLayout( FALSE ),
/*N*/     bAutoPosition( FALSE ),
/*N*/     bNoShrink( FALSE )
/*N*/ {
/*N*/     nType = FRMC_FLY;
/*N*/
/*N*/   bInvalid = bNotifyBack = TRUE;
/*N*/   bLocked  = bMinHeight =
/*N*/   bHeightClipped = bWidthClipped = bFormatHeightOnly = FALSE;
/*N*/
/*N*/   //Grosseneinstellung, Fixe groesse ist immer die Breite
/*N*/   const SwFmtFrmSize &rFrmSize = pFmt->GetFrmSize();
/*N*/     BOOL bVert = FALSE;
/*N*/     UINT16 nDir =
/*N*/         ((SvxFrameDirectionItem&)pFmt->GetAttr( RES_FRAMEDIR )).GetValue();
/*N*/     if( FRMDIR_ENVIRONMENT == nDir )
/*N*/     {
/*N*/         bDerivedVert = 1;
/*N*/         bDerivedR2L = 1;
/*N*/         if( pAnch && pAnch->IsVertical() )
/*?*/             bVert = TRUE;
/*N*/     }
/*N*/     else
/*N*/     {
/*?*/         bInvalidVert = 0;
/*?*/         bDerivedVert = 0;
/*?*/         bDerivedR2L = 0;
/*?*/         if( FRMDIR_HORI_LEFT_TOP == nDir || FRMDIR_HORI_RIGHT_TOP == nDir
/*?*/                                          || pFmt->GetDoc()->IsBrowseMode() )
/*?*/             bVertical = 0;
/*?*/         else
/*?*/             bVertical = 1;
/*?*/         bVert = bVertical;
/*?*/         bInvalidR2L = 0;
/*?*/         if( FRMDIR_HORI_RIGHT_TOP == nDir )
/*?*/             bRightToLeft = 1;
/*?*/         else
/*?*/             bRightToLeft = 0;
/*?*/     }
/*N*/
/*N*/         Frm().Width( rFrmSize.GetWidth() );
/*N*/         Frm().Height( rFrmSize.GetHeight() );
/*N*/
/*N*/   //Hoehe Fix oder Variabel oder was?
/*N*/   if ( rFrmSize.GetSizeType() == ATT_MIN_SIZE )
/*N*/       bMinHeight = TRUE;
/*N*/   else if ( rFrmSize.GetSizeType() == ATT_FIX_SIZE )
/*N*/         bFixSize = TRUE;
/*N*/
/*N*/   //Spalten?
/*N*/   const SwFmtCol &rCol = pFmt->GetCol();
/*N*/   if ( rCol.GetNumCols() > 1 )
/*N*/   {
/*N*/       //PrtArea ersteinmal so gross wie der Frm, damit die Spalten
/*N*/       //vernuenftig eingesetzt werden koennen; das schaukelt sich dann
/*N*/       //schon zurecht.
/*N*/       Prt().Width( Frm().Width() );
/*N*/       Prt().Height( Frm().Height() );
/*N*/       const SwFmtCol aOld; //ChgColumns() verlaesst sich darauf, dass auch ein
/*N*/                            //Old-Wert hereingereicht wird.
/*N*/       ChgColumns( aOld, rCol );
/*N*/   }
/*N*/
/*N*/   //Erst das Init, dann den Inhalt, denn zum Inhalt koennen  widerum
/*N*/   //Objekte/Rahmen gehoeren die dann angemeldet werden.
/*N*/   InitDrawObj( FALSE );
/*N*/
/*N*/   //Fuer Verkettungen kann jetzt die Verbindung aufgenommen werden. Wenn
/*N*/   //ein Nachbar nicht existiert, so macht das nichts, denn dieser wird ja
/*N*/   //irgendwann Konsturiert und nimmt dann die Verbindung auf.
/*N*/   const SwFmtChain &rChain = pFmt->GetChain();
/*N*/   if ( rChain.GetPrev() || rChain.GetNext() )
/*N*/   {
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001 if ( rChain.GetNext() )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            SwFlyFrm *pFollow = FindChainNeighbour( *rChain.GetNext(), pAnch );
//STRIP001 /*?*/            if ( pFollow )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                ASSERT( !pFollow->GetPrevLink(), "wrong chain detected" );
//STRIP001 /*?*/                if ( !pFollow->GetPrevLink() )
//STRIP001 /*?*/                    SwFlyFrm::ChainFrames( this, pFollow );
//STRIP001 /*?*/            }
//STRIP001 /*?*/        }
//STRIP001 /*?*/        if ( rChain.GetPrev() )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            SwFlyFrm *pMaster = FindChainNeighbour( *rChain.GetPrev(), pAnch );
//STRIP001 /*?*/            if ( pMaster )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                ASSERT( !pMaster->GetNextLink(), "wrong chain detected" );
//STRIP001 /*?*/                if ( !pMaster->GetNextLink() )
//STRIP001 /*?*/                    SwFlyFrm::ChainFrames( pMaster, this );
//STRIP001 /*?*/            }
//STRIP001 /*?*/        }
/*N*/   }
/*N*/
/*N*/   if ( !GetPrevLink() ) //Inhalt gehoert sonst immer dem Master und meiner Zaehlt nicht
/*N*/   {
/*N*/       const SwFmtCntnt &rCntnt = pFmt->GetCntnt();
/*N*/       ASSERT( rCntnt.GetCntntIdx(), ":-( Kein Inhalt vorbereitet." );
/*N*/       ULONG nIndex = rCntnt.GetCntntIdx()->GetIndex();
/*N*/       // Lower() bedeutet SwColumnFrm, eingefuegt werden muss der Inhalt dann in den (Column)BodyFrm
/*N*/       ::_InsertCnt( Lower() ? (SwLayoutFrm*)((SwLayoutFrm*)Lower())->Lower() : (SwLayoutFrm*)this,
/*N*/                     pFmt->GetDoc(), nIndex );
/*N*/
/*N*/       //NoTxt haben immer eine FixHeight.
/*N*/       if ( Lower() && Lower()->IsNoTxtFrm() )
/*N*/       {
/*N*/             bFixSize = TRUE;
/*N*/           bMinHeight = FALSE;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   //Und erstmal in den Wald stellen die Kiste, damit bei neuen Dokument nicht
/*N*/   //unnoetig viel formatiert wird.
/*N*/   Frm().Pos().X() = Frm().Pos().Y() = WEIT_WECH;
/*N*/ }

/*************************************************************************
|*
|*  SwFlyFrm::~SwFlyFrm()
|*
|*  Ersterstellung      MA 28. Sep. 92
|*  Letzte Aenderung    MA 07. Jul. 95
|*
|*************************************************************************/

/*N*/ SwFlyFrm::~SwFlyFrm()
/*N*/ {
/*N*/ #ifdef ACCESSIBLE_LAYOUT
/*N*/   // Accessible objects for fly frames will be destroyed in this destructor.
/*N*/   // For frames bound as char or frames that don't have an anchor we have
/*N*/   // to do that ourselves. For any other frame the call RemoveFly at the
/*N*/   // anchor will do that.
/*N*/   if( IsAccessibleFrm() && GetFmt() && (IsFlyInCntFrm() || !pAnchor) )
/*N*/   {
/*N*/       SwRootFrm *pRootFrm = FindRootFrm();
/*N*/       if( pRootFrm && pRootFrm->IsAnyShellAccessible() )
/*N*/       {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/            ViewShell *pVSh = pRootFrm->GetCurrShell();
//STRIP001 /*?*/            if( pVSh && pVSh->Imp() )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                // Lowers aren't disposed already, so we have to do a recursive
//STRIP001 /*?*/                // dispose
//STRIP001 /*?*/                pVSh->Imp()->DisposeAccessibleFrm( this, sal_True );
//STRIP001 /*?*/            }
/*N*/       }
/*N*/   }
/*N*/ #endif
/*N*/
/*N*/   if( GetFmt() && !GetFmt()->GetDoc()->IsInDtor() )
/*N*/   {
/*N*/       //Aus der Verkettung loessen.
/*N*/       if ( GetPrevLink() )
/*?*/       {DBG_ASSERT(0, "STRIP");} //STRIP001    UnchainFrames( GetPrevLink(), this );
/*N*/       if ( GetNextLink() )
/*?*/       {DBG_ASSERT(0, "STRIP");} //STRIP001    UnchainFrames( this, GetNextLink() );
/*N*/
/*N*/       //Unterstruktur zerstoeren, wenn dies erst im LayFrm DTor passiert ist's
/*N*/       //zu spaet, denn dort ist die Seite nicht mehr erreichbar (muss sie aber
/*N*/       //sein, damit sich ggf. weitere Flys abmelden koennen).
/*N*/       SwFrm *pFrm = pLower;
/*N*/       while ( pFrm )
/*N*/       {
/*N*/           //Erst die Flys des Frm vernichten, denn diese koennen sich sonst nach
/*N*/           //dem Remove nicht mehr bei der Seite abmelden.
/*N*/           while ( pFrm->GetDrawObjs() && pFrm->GetDrawObjs()->Count() )
/*N*/             {
/*N*/                 SdrObject *pObj = (*pFrm->GetDrawObjs())[0];
/*N*/               if ( pObj->IsWriterFlyFrame() )
/*N*/                   delete ((SwVirtFlyDrawObj*)pObj)->GetFlyFrm();
/*N*/                 else
/*N*/                 // OD 23.06.2003 #108784# - consider 'virtual' drawing objects
/*N*/                 {
/*N*/                     if ( pObj->ISA(SwDrawVirtObj) )
/*N*/                     {
/*N*/                         SwDrawVirtObj* pDrawVirtObj = static_cast<SwDrawVirtObj*>(pObj);
/*N*/                         pDrawVirtObj->RemoveFromWriterLayout();
/*N*/                         pDrawVirtObj->RemoveFromDrawingPage();
/*N*/                     }
/*N*/                     else
/*N*/                     {
/*N*/                         SdrObjUserCall* pUserCall = GetUserCall(pObj);
/*N*/                         if ( pUserCall )
/*N*/                         {
/*N*/                             static_cast<SwDrawContact*>(pUserCall)->DisconnectFromLayout();
/*N*/                         }
/*N*/                     }
/*N*/                 }
/*N*/           }
/*N*/           pFrm->Remove();
/*N*/           delete pFrm;
/*N*/           pFrm = pLower;
/*N*/       }
/*N*/
/*N*/       //Damit kein zerstoerter Cntnt als Turbo bei der Root angemeldet bleiben
/*N*/       //kann verhindere ich hier, dass dort ueberhaupt noch einer angemeldet
/*N*/       //ist.
/*N*/       InvalidatePage();
/*N*/
/*N*/       //Tschuess sagen.
/*N*/       if ( pAnchor )
/*N*/           pAnchor->RemoveFly( this );
/*N*/   }
/*N*/   FinitDrawObj();
/*N*/ }

/*************************************************************************
|*
|*  SwFlyFrm::InitDrawObj()
|*
|*  Ersterstellung      MA 02. Dec. 94
|*  Letzte Aenderung    MA 30. Nov. 95
|*
|*************************************************************************/
#pragma optimize("",off)

/*N*/ void SwFlyFrm::InitDrawObj( BOOL bNotify )
/*N*/ {
/*N*/   //ContactObject aus dem Format suchen. Wenn bereits eines existiert, so
/*N*/   //braucht nur eine neue Ref erzeugt werden, anderfalls ist es jetzt an
/*N*/   //der Zeit das Contact zu erzeugen.
/*N*/   SwClientIter aIter( *GetFmt() );
/*N*/   SwFlyDrawContact *pContact = (SwFlyDrawContact*)
/*N*/                                       aIter.First( TYPE(SwFlyDrawContact) );
/*N*/   if ( !pContact )
/*N*/       pContact = new SwFlyDrawContact( (SwFlyFrmFmt*)GetFmt(),
/*N*/                           GetFmt()->GetDoc()->MakeDrawModel() );
/*N*/   ASSERT( pContact, "InitDrawObj failed" );
/*N*/   pDrawObj = pContact->CreateNewRef( this );
/*N*/
/*N*/   //Den richtigen Layer setzen.
/*N*/   pDrawObj->SetLayer( GetFmt()->GetOpaque().GetValue() ?
/*N*/                           GetFmt()->GetDoc()->GetHeavenId() :
/*N*/                           GetFmt()->GetDoc()->GetHellId() );
/*N*/   if ( bNotify )
/*?*/       NotifyDrawObj();
/*N*/ }

/*N*/ #pragma optimize("",on)

/*************************************************************************
|*
|*  SwFlyFrm::FinitDrawObj()
|*
|*  Ersterstellung      MA 12. Dec. 94
|*  Letzte Aenderung    MA 15. May. 95
|*
|*************************************************************************/

/*N*/ void SwFlyFrm::FinitDrawObj()
/*N*/ {
/*N*/   if ( !pDrawObj )
/*?*/       return;
/*N*/
/*N*/   //Bei den SdrPageViews abmelden falls das Objekt dort noch selektiert ist.
/*N*/   if ( !GetFmt()->GetDoc()->IsInDtor() )
/*N*/   {
/*N*/       ViewShell *p1St = GetShell();
/*N*/       if ( p1St )
/*N*/       {
/*N*/           ViewShell *pSh = p1St;
/*N*/           do
/*N*/           {   //z.Zt. kann das Drawing nur ein Unmark auf alles, weil das
/*N*/               //Objekt bereits Removed wurde.
/*N*/               if( pSh->HasDrawView() )
/*N*/                   pSh->Imp()->GetDrawView()->UnmarkAll();
/*N*/               pSh = (ViewShell*)pSh->GetNext();
/*N*/
/*N*/           } while ( pSh != p1St );
/*N*/       }
/*N*/   }
/*N*/
/*N*/   //VirtObject mit in das Grab nehmen. Wenn das letzte VirObject
/*N*/   //zerstoert wird, mussen das DrawObject und DrawContact ebenfalls
/*N*/   //zerstoert werden.
/*N*/   SwFlyDrawContact *pMyContact = 0;
/*N*/   if ( GetFmt() )
/*N*/   {
/*N*/       SwClientIter aIter( *GetFmt() );
/*N*/       aIter.GoStart();
/*N*/       do {
/*N*/           if ( aIter()->ISA(SwFrm) && (SwFrm*)aIter() != this )
/*N*/           {
/*N*/               pMyContact = 0;
/*N*/               break;
/*N*/           }
/*N*/           if( !pMyContact && aIter()->ISA(SwFlyDrawContact) )
/*N*/               pMyContact = (SwFlyDrawContact*)aIter();
/*N*/           aIter++;
/*N*/       } while( aIter() );
/*N*/   }
/*N*/
/*N*/   pDrawObj->SetUserCall( 0 ); //Ruft sonst Delete des ContactObj
/*N*/   delete pDrawObj;            //Meldet sich selbst beim Master ab.
/*N*/   if ( pMyContact )
/*N*/       delete pMyContact;      //zerstoert den Master selbst.
/*N*/ }

/*************************************************************************
|*
|*  SwFlyFrm::ChainFrames()
|*
|*  Ersterstellung      MA 29. Oct. 97
|*  Letzte Aenderung    MA 20. Jan. 98
|*
|*************************************************************************/

//STRIP001 void SwFlyFrm::ChainFrames( SwFlyFrm *pMaster, SwFlyFrm *pFollow )
//STRIP001 {
//STRIP001  ASSERT( pMaster && pFollow, "uncomplete chain" );
//STRIP001  ASSERT( !pMaster->GetNextLink(), "link can not be changed" );
//STRIP001  ASSERT( !pFollow->GetPrevLink(), "link can not be changed" );
//STRIP001
//STRIP001  pMaster->pNextLink = pFollow;
//STRIP001  pFollow->pPrevLink = pMaster;
//STRIP001
//STRIP001  if ( pMaster->ContainsCntnt() )
//STRIP001  {
//STRIP001      //Damit ggf. ein Textfluss zustande kommt muss invalidiert werden.
//STRIP001      SwFrm *pInva = pMaster->FindLastLower();
//STRIP001         SWRECTFN( pMaster )
//STRIP001         const long nBottom = (pMaster->*fnRect->fnGetPrtBottom)();
//STRIP001      while ( pInva )
//STRIP001      {
//STRIP001             if( (pInva->Frm().*fnRect->fnBottomDist)( nBottom ) <= 0 )
//STRIP001          {
//STRIP001              pInva->InvalidateSize();
//STRIP001              pInva->Prepare( PREP_CLEAR );
//STRIP001              pInva = pInva->FindPrev();
//STRIP001          }
//STRIP001          else
//STRIP001              pInva = 0;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if ( pFollow->ContainsCntnt() )
//STRIP001  {
//STRIP001      //Es gibt nur noch den Inhalt des Masters, der Inhalt vom Follow
//STRIP001      //hat keine Frames mehr (sollte immer nur genau ein leerer TxtNode sein).
//STRIP001      SwFrm *pFrm = pFollow->ContainsCntnt();
//STRIP001      ASSERT( !pFrm->IsTabFrm() && !pFrm->FindNext(), "follow in chain contains content" );
//STRIP001      pFrm->Cut();
//STRIP001      delete pFrm;
//STRIP001  }
//STRIP001
//STRIP001 #ifdef ACCESSIBLE_LAYOUT
//STRIP001     // invalidate accessible relation set (accessibility wrapper)
//STRIP001     ViewShell* pSh = pMaster->GetShell();
//STRIP001     if( pSh && pSh->GetLayout()->IsAnyShellAccessible() )
//STRIP001         pSh->Imp()->InvalidateAccessibleRelationSet( pMaster, pFollow );
//STRIP001 #endif
//STRIP001
//STRIP001 }

//STRIP001 void SwFlyFrm::UnchainFrames( SwFlyFrm *pMaster, SwFlyFrm *pFollow )
//STRIP001 {
//STRIP001  pMaster->pNextLink = 0;
//STRIP001  pFollow->pPrevLink = 0;
//STRIP001
//STRIP001  if ( pFollow->ContainsCntnt() )
//STRIP001  {
//STRIP001      //Der Master saugt den Inhalt vom Follow auf
//STRIP001      SwLayoutFrm *pUpper = pMaster;
//STRIP001      if ( pUpper->Lower()->IsColumnFrm() )
//STRIP001      {
//STRIP001          pUpper = (SwLayoutFrm*)pUpper->Lower();
//STRIP001          while ( pUpper->GetNext() ) // sucht die letzte Spalte
//STRIP001              pUpper = (SwLayoutFrm*)pUpper->GetNext();
//STRIP001          pUpper = (SwLayoutFrm*)((SwLayoutFrm*)pUpper)->Lower(); // der (Column)BodyFrm
//STRIP001          ASSERT( pUpper && pUpper->IsColBodyFrm(), "Missing ColumnBody" );
//STRIP001      }
//STRIP001      SwFlyFrm *pFoll = pFollow;
//STRIP001      while ( pFoll )
//STRIP001      {
//STRIP001          SwFrm *pTmp = ::SaveCntnt( pFoll );
//STRIP001          if ( pTmp )
//STRIP001              ::RestoreCntnt( pTmp, pUpper, pMaster->FindLastLower() );
//STRIP001          pFoll->SetCompletePaint();
//STRIP001          pFoll->InvalidateSize();
//STRIP001          pFoll = pFoll->GetNextLink();
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  //Der Follow muss mit seinem eigenen Inhalt versorgt werden.
//STRIP001  const SwFmtCntnt &rCntnt = pFollow->GetFmt()->GetCntnt();
//STRIP001  ASSERT( rCntnt.GetCntntIdx(), ":-( Kein Inhalt vorbereitet." );
//STRIP001  ULONG nIndex = rCntnt.GetCntntIdx()->GetIndex();
//STRIP001  // Lower() bedeutet SwColumnFrm, dieser beinhaltet wieder einen SwBodyFrm
//STRIP001  ::_InsertCnt( pFollow->Lower() ? (SwLayoutFrm*)((SwLayoutFrm*)pFollow->Lower())->Lower()
//STRIP001                                 : (SwLayoutFrm*)pFollow,
//STRIP001                pFollow->GetFmt()->GetDoc(), ++nIndex );
//STRIP001
//STRIP001 #ifdef ACCESSIBLE_LAYOUT
//STRIP001     // invalidate accessible relation set (accessibility wrapper)
//STRIP001     ViewShell* pSh = pMaster->GetShell();
//STRIP001     if( pSh && pSh->GetLayout()->IsAnyShellAccessible() )
//STRIP001         pSh->Imp()->InvalidateAccessibleRelationSet( pMaster, pFollow );
//STRIP001 #endif
//STRIP001 }

/*************************************************************************
|*
|*  SwFlyFrm::FindChainNeighbour()
|*
|*  Ersterstellung      MA 11. Nov. 97
|*  Letzte Aenderung    MA 09. Apr. 99
|*
|*************************************************************************/

//STRIP001 SwFlyFrm *SwFlyFrm::FindChainNeighbour( SwFrmFmt &rChain, SwFrm *pAnch )
//STRIP001 {
//STRIP001  //Wir suchen denjenigen Fly, der in dem selben Bereich steht.
//STRIP001  //Bereiche koennen zunaechst nur Kopf-/Fusszeilen oder Flys sein.
//STRIP001
//STRIP001  if ( !pAnch )           //Wenn ein Anchor uebergeben Wurde zaehlt dieser: Ctor!
//STRIP001      pAnch = GetAnchor();
//STRIP001
//STRIP001  SwLayoutFrm *pLay;
//STRIP001  if ( pAnch->IsInFly() )
//STRIP001      pLay = pAnch->FindFlyFrm();
//STRIP001  else
//STRIP001  {
//STRIP001      //FindFooterOrHeader taugt hier nicht, weil evtl. noch keine Verbindung
//STRIP001      //zum Anker besteht.
//STRIP001      pLay = pAnch->GetUpper();
//STRIP001      while ( pLay && !(pLay->GetType() & (FRM_HEADER|FRM_FOOTER)) )
//STRIP001          pLay = pLay->GetUpper();
//STRIP001  }
//STRIP001
//STRIP001  SwClientIter aIter( rChain );
//STRIP001  SwFlyFrm *pFly = (SwFlyFrm*)aIter.First( TYPE(SwFlyFrm ) );
//STRIP001  if ( pLay )
//STRIP001  {
//STRIP001      while ( pFly )
//STRIP001      {
//STRIP001          if ( pFly->GetAnchor() )
//STRIP001          {
//STRIP001              if ( pFly->GetAnchor()->IsInFly() )
//STRIP001              {
//STRIP001                  if ( pFly->GetAnchor()->FindFlyFrm() == pLay )
//STRIP001                      break;
//STRIP001              }
//STRIP001              else if ( pLay == pFly->FindFooterOrHeader() )
//STRIP001                  break;
//STRIP001          }
//STRIP001          pFly = (SwFlyFrm*)aIter.Next();
//STRIP001      }
//STRIP001  }
//STRIP001  else if ( pFly )
//STRIP001  {
//STRIP001      ASSERT( !aIter.Next(), "chain with more than one inkarnation" );
//STRIP001  }
//STRIP001  return pFly;
//STRIP001 }


/*************************************************************************
|*
|*  SwFlyFrm::FindLastLower()
|*
|*  Ersterstellung      MA 29. Oct. 97
|*  Letzte Aenderung    MA 29. Oct. 97
|*
|*************************************************************************/

//STRIP001 SwFrm *SwFlyFrm::FindLastLower()
//STRIP001 {
//STRIP001  SwFrm *pRet = ContainsAny();
//STRIP001  if ( pRet && pRet->IsInTab() )
//STRIP001      pRet = pRet->FindTabFrm();
//STRIP001  SwFrm *pNxt = pRet;
//STRIP001  while ( pNxt && IsAnLower( pNxt ) )
//STRIP001  {   pRet = pNxt;
//STRIP001      pNxt = pNxt->FindNext();
//STRIP001  }
//STRIP001  return pRet;
//STRIP001 }


/*************************************************************************
|*
|*  SwFlyFrm::FrmSizeChg()
|*
|*  Ersterstellung      MA 17. Dec. 92
|*  Letzte Aenderung    MA 24. Jul. 96
|*
|*************************************************************************/

/*N*/ BOOL SwFlyFrm::FrmSizeChg( const SwFmtFrmSize &rFrmSize )
/*N*/ {
/*N*/   BOOL bRet = FALSE;
/*N*/   SwTwips nDiffHeight = Frm().Height();
/*N*/   if ( rFrmSize.GetSizeType() == ATT_VAR_SIZE )
/*?*/         BFIXHEIGHT = bMinHeight = FALSE;
/*N*/   else
/*N*/   {
/*N*/       if ( rFrmSize.GetSizeType() == ATT_FIX_SIZE )
/*N*/         {   BFIXHEIGHT = TRUE;
/*N*/           bMinHeight = FALSE;
/*N*/       }
/*N*/       else if ( rFrmSize.GetSizeType() == ATT_MIN_SIZE )
/*?*/         {   BFIXHEIGHT = FALSE;
/*?*/           bMinHeight = TRUE;
/*N*/       }
/*N*/       nDiffHeight -= rFrmSize.GetHeight();
/*N*/   }
/*N*/   //Wenn der Fly Spalten enthaehlt muessen der Fly und
/*N*/   //die Spalten schon einmal auf die Wunschwerte gebracht
/*N*/   //werden, sonst haben wir ein kleines Problem.
/*N*/   if ( Lower() )
/*N*/   {
/*N*/       if ( Lower()->IsColumnFrm() )
/*N*/       {
/*?*/           const SwRect aOld( AddSpacesToFrm() );
/*?*/           const Size   aOldSz( Prt().SSize() );
/*?*/           const SwTwips nDiffWidth = Frm().Width() - rFrmSize.GetWidth();
/*?*/           aFrm.Height( aFrm.Height() - nDiffHeight );
/*?*/           aFrm.Width ( aFrm.Width()  - nDiffWidth  );
/*?*/           aPrt.Height( aPrt.Height() - nDiffHeight );
/*?*/           aPrt.Width ( aPrt.Width()  - nDiffWidth  );
/*?*/           ChgLowersProp( aOldSz );
/*?*/           ::Notify( this, FindPageFrm(), aOld );
/*?*/           bValidPos = FALSE;
/*?*/           bRet = TRUE;
/*N*/       }
/*N*/       else if ( Lower()->IsNoTxtFrm() )
/*N*/       {
/*N*/             BFIXHEIGHT = TRUE;
/*N*/           bMinHeight = FALSE;
/*N*/       }
/*N*/   }
/*N*/   return bRet;
/*N*/ }

/*************************************************************************
|*
|*  SwFlyFrm::Modify()
|*
|*  Ersterstellung      MA 17. Dec. 92
|*  Letzte Aenderung    MA 17. Jan. 97
|*
|*************************************************************************/

/*N*/ void SwFlyFrm::Modify( SfxPoolItem * pOld, SfxPoolItem * pNew )
/*N*/ {
/*N*/   BYTE nInvFlags = 0;
/*N*/
/*N*/   if( pNew && RES_ATTRSET_CHG == pNew->Which() )
/*N*/   {
/*N*/       SfxItemIter aNIter( *((SwAttrSetChg*)pNew)->GetChgSet() );
/*N*/       SfxItemIter aOIter( *((SwAttrSetChg*)pOld)->GetChgSet() );
/*N*/       SwAttrSetChg aOldSet( *(SwAttrSetChg*)pOld );
/*N*/       SwAttrSetChg aNewSet( *(SwAttrSetChg*)pNew );
/*N*/       while( TRUE )
/*N*/       {
/*N*/           _UpdateAttr( (SfxPoolItem*)aOIter.GetCurItem(),
/*N*/                        (SfxPoolItem*)aNIter.GetCurItem(), nInvFlags,
/*N*/                        &aOldSet, &aNewSet );
/*N*/           if( aNIter.IsAtEnd() )
/*N*/               break;
/*?*/           aNIter.NextItem();
/*?*/           aOIter.NextItem();
/*N*/       }
/*N*/       if ( aOldSet.Count() || aNewSet.Count() )
/*N*/           SwLayoutFrm::Modify( &aOldSet, &aNewSet );
/*N*/   }
/*N*/   else
/*N*/       _UpdateAttr( pOld, pNew, nInvFlags );
/*N*/
/*N*/   if ( nInvFlags != 0 )
/*N*/   {
/*N*/       _Invalidate();
/*N*/       if ( nInvFlags & 0x01 )
/*N*/           _InvalidatePos();
/*N*/       if ( nInvFlags & 0x02 )
/*N*/           _InvalidateSize();
/*N*/       if ( nInvFlags & 0x04 )
/*N*/           _InvalidatePrt();
/*N*/       if ( nInvFlags & 0x08 )
/*N*/           SetNotifyBack();
/*N*/       if ( nInvFlags & 0x10 )
/*N*/           SetCompletePaint();
/*N*/       if ( ( nInvFlags & 0x40 ) && Lower() && Lower()->IsNoTxtFrm() )
/*N*/           ClrContourCache( GetVirtDrawObj() );
/*N*/       SwRootFrm *pRoot;
/*N*/       if ( nInvFlags & 0x20 && 0 != (pRoot = FindRootFrm()) )
/*N*/           pRoot->InvalidateBrowseWidth();
/*N*/   }
/*N*/ }

/*M*/ void SwFlyFrm::_UpdateAttr( SfxPoolItem *pOld, SfxPoolItem *pNew,
/*M*/                           BYTE &rInvFlags,
/*M*/                           SwAttrSetChg *pOldSet, SwAttrSetChg *pNewSet )
/*M*/ {
/*M*/   BOOL bClear = TRUE;
/*M*/   const USHORT nWhich = pOld ? pOld->Which() : pNew ? pNew->Which() : 0;
/*M*/   ViewShell *pSh = GetShell();
/*M*/   switch( nWhich )
/*M*/   {
/*M*/       case RES_VERT_ORIENT:
/*M*/       case RES_HORI_ORIENT:
/*M*/           //Achtung! _immer_ Aktion in ChgRePos() mitpflegen.
/*M*/           rInvFlags |= 0x09;
/*M*/           break;
/*M*/
/*M*/       case RES_SURROUND:
/*M*/           {
/*M*/           rInvFlags |= 0x40;
/*M*/           //Der Hintergrund muss benachrichtigt und Invalidiert werden.
/*M*/           const SwRect aTmp( AddSpacesToFrm() );
/*M*/           NotifyBackground( FindPageFrm(), aTmp, PREP_FLY_ATTR_CHG );
/*M*/
/*M*/           // Durch eine Umlaufaenderung von rahmengebundenen Rahmen kann eine
/*M*/           // vertikale Ausrichtung aktiviert/deaktiviert werden => MakeFlyPos
/*M*/           if( FLY_AT_FLY == GetFmt()->GetAnchor().GetAnchorId() )
/*M*/               rInvFlags |= 0x09;
/*M*/
/*M*/           //Ggf. die Kontur am Node loeschen.
/*M*/           if ( Lower() && Lower()->IsNoTxtFrm() &&
/*M*/                !GetFmt()->GetSurround().IsContour() )
/*M*/           {
/*M*/               SwNoTxtNode *pNd = (SwNoTxtNode*)((SwCntntFrm*)Lower())->GetNode();
/*M*/               if ( pNd->HasContour() )
/*M*/                   pNd->SetContour( 0 );
/*M*/           }
/*M*/           }
/*M*/           break;
/*M*/
/*M*/       case RES_PROTECT:
/*M*/           {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/            const SvxProtectItem *pP = (SvxProtectItem*)pNew;
//STRIP001 /*?*/            GetVirtDrawObj()->SetMoveProtect( pP->IsPosProtected()  );
//STRIP001 /*?*/            GetVirtDrawObj()->SetResizeProtect( pP->IsSizeProtected() );
//STRIP001 /*M*/ #ifdef ACCESSIBLE_LAYOUT
//STRIP001 /*?*/            if( pSh && pSh->GetLayout()->IsAnyShellAccessible() )
//STRIP001 /*?*/                pSh->Imp()->InvalidateAccessibleEditableState( sal_True, this );
//STRIP001 /*M*/ #endif
/*M*/           break;
/*M*/           }
/*M*/
/*M*/       case RES_COL:
/*M*/           {
/*?*/               ChgColumns( *(const SwFmtCol*)pOld, *(const SwFmtCol*)pNew );
/*?*/               const SwFmtFrmSize &rNew = GetFmt()->GetFrmSize();
/*?*/               if ( FrmSizeChg( rNew ) )
/*?*/                   NotifyDrawObj();
/*?*/               rInvFlags |= 0x1A;
/*M*/               break;
/*M*/           }
/*M*/
/*M*/       case RES_FRM_SIZE:
/*M*/       case RES_FMT_CHG:
/*M*/       {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/            const SwFmtFrmSize &rNew = GetFmt()->GetFrmSize();
//STRIP001 /*?*/            if ( FrmSizeChg( rNew ) )
//STRIP001 /*?*/                NotifyDrawObj();
//STRIP001 /*?*/            rInvFlags |= 0x7F;
//STRIP001 /*?*/            if ( RES_FMT_CHG == nWhich )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                SwRect aNew( AddSpacesToFrm() );
//STRIP001 /*?*/                SwRect aOld( aFrm );
//STRIP001 /*?*/                const SvxULSpaceItem &rUL = ((SwFmtChg*)pOld)->pChangedFmt->GetULSpace();
//STRIP001 /*?*/                aOld.Top( Max( aOld.Top() - long(rUL.GetUpper()), 0L ) );
//STRIP001 /*?*/                aOld.SSize().Height()+= rUL.GetLower();
//STRIP001 /*?*/                const SvxLRSpaceItem &rLR = ((SwFmtChg*)pOld)->pChangedFmt->GetLRSpace();
//STRIP001 /*?*/                aOld.Left  ( Max( aOld.Left() - long(rLR.GetLeft()), 0L ) );
//STRIP001 /*?*/                aOld.SSize().Width() += rLR.GetRight();
//STRIP001 /*?*/                aNew.Union( aOld );
//STRIP001 /*?*/                NotifyBackground( FindPageFrm(), aNew, PREP_CLEAR );
//STRIP001 /*?*/
//STRIP001 /*?*/                //Dummer Fall. Bei der Zusweisung einer Vorlage k”nnen wir uns
//STRIP001 /*?*/                //nicht auf das alte Spaltenattribut verlassen. Da diese
//STRIP001 /*?*/                //wenigstens anzahlgemass fuer ChgColumns vorliegen muessen,
//STRIP001 /*?*/                //bleibt uns nur einen temporaeres Attribut zu basteln.
//STRIP001 /*?*/                SwFmtCol aCol;
//STRIP001 /*?*/                if ( Lower() && Lower()->IsColumnFrm() )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    USHORT nCol = 0;
//STRIP001 /*?*/                    SwFrm *pTmp = Lower();
//STRIP001 /*?*/                    do
//STRIP001 /*?*/                    {   ++nCol;
//STRIP001 /*?*/                        pTmp = pTmp->GetNext();
//STRIP001 /*?*/                    } while ( pTmp );
//STRIP001 /*?*/                    aCol.Init( nCol, 0, 1000 );
//STRIP001 /*?*/                }
//STRIP001 /*?*/                ChgColumns( aCol, GetFmt()->GetCol() );
//STRIP001 /*?*/            }
//STRIP001 /*?*/
//STRIP001 /*?*/            SwFmtURL aURL( GetFmt()->GetURL() );
//STRIP001 /*?*/            if ( aURL.GetMap() )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                const SwFmtFrmSize &rOld = nWhich == RES_FRM_SIZE ?
//STRIP001 /*?*/                                *(SwFmtFrmSize*)pNew :
//STRIP001 /*?*/                                ((SwFmtChg*)pOld)->pChangedFmt->GetFrmSize();
//STRIP001 /*?*/                //#35091# Kann beim Laden von Vorlagen mal 0 sein
//STRIP001 /*?*/                if ( rOld.GetWidth() && rOld.GetHeight() )
//STRIP001 /*?*/                {
//STRIP001 /*?*/
//STRIP001 /*?*/                    Fraction aScaleX( rOld.GetWidth(), rNew.GetWidth() );
//STRIP001 /*?*/                    Fraction aScaleY( rOld.GetHeight(), rOld.GetHeight() );
//STRIP001 /*?*/                    aURL.GetMap()->Scale( aScaleX, aScaleY );
//STRIP001 /*?*/                    SwFrmFmt *pFmt = GetFmt();
//STRIP001 /*?*/                    pFmt->LockModify();
//STRIP001 /*?*/                    pFmt->SetAttr( aURL );
//STRIP001 /*?*/                    pFmt->UnlockModify();
//STRIP001 /*?*/                }
//STRIP001 /*?*/            }
//STRIP001 /*?*/            const SvxProtectItem &rP = GetFmt()->GetProtect();
//STRIP001 /*?*/            GetVirtDrawObj()->SetMoveProtect( rP.IsPosProtected()   );
//STRIP001 /*?*/            GetVirtDrawObj()->SetResizeProtect( rP.IsSizeProtected() );
//STRIP001 /*?*/
//STRIP001 /*?*/            if ( pSh )
//STRIP001 /*?*/                pSh->InvalidateWindows( Frm() );
//STRIP001 /*?*/            const BYTE nId = GetFmt()->GetOpaque().GetValue() ?
//STRIP001 /*?*/                                GetFmt()->GetDoc()->GetHeavenId() :
//STRIP001 /*?*/                                GetFmt()->GetDoc()->GetHellId();
//STRIP001 /*?*/            GetVirtDrawObj()->SetLayer( nId );
//STRIP001 /*?*/
//STRIP001 /*?*/            if ( Lower() )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                //Ggf. die Kontur am Node loeschen.
//STRIP001 /*?*/                if( Lower()->IsNoTxtFrm() &&
//STRIP001 /*?*/                     !GetFmt()->GetSurround().IsContour() )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    SwNoTxtNode *pNd = (SwNoTxtNode*)((SwCntntFrm*)Lower())->GetNode();
//STRIP001 /*?*/                    if ( pNd->HasContour() )
//STRIP001 /*?*/                        pNd->SetContour( 0 );
//STRIP001 /*?*/                }
//STRIP001 /*?*/                else if( !Lower()->IsColumnFrm() )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    SwFrm* pFrm = Lower();
//STRIP001 /*?*/                    while( pFrm->GetNext() )
//STRIP001 /*?*/                        pFrm = pFrm->GetNext();
//STRIP001 /*?*/                    if( pFrm->IsTxtFrm() && ((SwTxtFrm*)pFrm)->IsUndersized() )
//STRIP001 /*?*/                        pFrm->Prepare( PREP_ADJUST_FRM );
//STRIP001 /*?*/                }
//STRIP001 /*?*/            }
//STRIP001 /*?*/
/*M*/           break;
/*M*/       }
/*M*/       case RES_UL_SPACE:
/*M*/       case RES_LR_SPACE:
/*M*/           {
/*?*/           rInvFlags |= 0x41;
/*?*/           if ( GetFmt()->GetDoc()->IsBrowseMode() )
/*?*/               GetFmt()->GetDoc()->GetRootFrm()->InvalidateBrowseWidth();
/*?*/           SwRect aNew( AddSpacesToFrm() );
/*?*/           SwRect aOld( aFrm );
/*?*/           if ( RES_UL_SPACE == nWhich )
/*?*/           {
/*?*/               const SvxULSpaceItem &rUL = *(SvxULSpaceItem*)pNew;
/*?*/               aOld.Top( Max( aOld.Top() - long(rUL.GetUpper()), 0L ) );
/*?*/               aOld.SSize().Height()+= rUL.GetLower();
/*?*/           }
/*?*/           else
/*?*/           {
/*?*/               const SvxLRSpaceItem &rLR = *(SvxLRSpaceItem*)pNew;
/*?*/               aOld.Left  ( Max( aOld.Left() - long(rLR.GetLeft()), 0L ) );
/*?*/               aOld.SSize().Width() += rLR.GetRight();
/*?*/           }
/*?*/           aNew.Union( aOld );
/*?*/           NotifyBackground( FindPageFrm(), aNew, PREP_CLEAR );
/*?*/           }
/*M*/           break;
/*M*/
/*M*/       case RES_BOX:
/*M*/       case RES_SHADOW:
/*M*/           rInvFlags |= 0x17;
/*M*/           break;
/*M*/
/*M*/         case RES_FRAMEDIR :
/*?*/             SetDerivedVert( FALSE );
/*?*/             SetDerivedR2L( FALSE );
/*?*/             CheckDirChange();
/*M*/             break;
/*M*/
/*M*/         case RES_OPAQUE:
/*M*/           {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/            if ( pSh )
//STRIP001 /*?*/                pSh->InvalidateWindows( Frm() );
//STRIP001 /*?*/            const BYTE nId = ((SvxOpaqueItem*)pNew)->GetValue() ?
//STRIP001 /*?*/                                GetFmt()->GetDoc()->GetHeavenId() :
//STRIP001 /*?*/                                GetFmt()->GetDoc()->GetHellId();
//STRIP001 /*?*/            GetVirtDrawObj()->SetLayer( nId );
//STRIP001 /*?*/ #ifdef ACCESSIBLE_LAYOUT
//STRIP001 /*?*/            if( pSh && pSh->GetLayout()->IsAnyShellAccessible() )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                pSh->Imp()->DisposeAccessibleFrm( this );
//STRIP001 /*?*/                pSh->Imp()->AddAccessibleFrm( this );
//STRIP001 /*?*/            }
//STRIP001 /*?*/ #endif
/*M*/           }
/*M*/           break;
/*M*/
/*M*/       case RES_URL:
/*M*/           //Das Interface arbeitet bei Textrahmen auf der Rahmengroesse,
/*M*/           //die Map muss sich aber auf die FrmSize beziehen
/*?*/           if ( (!Lower() || !Lower()->IsNoTxtFrm()) &&
/*?*/                ((SwFmtURL*)pNew)->GetMap() && ((SwFmtURL*)pOld)->GetMap() )
/*?*/           {
/*?*/               const SwFmtFrmSize &rSz = GetFmt()->GetFrmSize();
/*?*/               if ( rSz.GetHeight() != Frm().Height() ||
/*?*/                    rSz.GetWidth()  != Frm().Width() )
/*?*/               {
/*?*/                   SwFmtURL aURL( GetFmt()->GetURL() );
/*?*/                   Fraction aScaleX( Frm().Width(),  rSz.GetWidth() );
/*?*/                   Fraction aScaleY( Frm().Height(), rSz.GetHeight() );
/*?*/                   aURL.GetMap()->Scale( aScaleX, aScaleY );
/*?*/                   SwFrmFmt *pFmt = GetFmt();
/*?*/                   pFmt->LockModify();
/*?*/                   pFmt->SetAttr( aURL );
/*?*/                   pFmt->UnlockModify();
/*?*/               }
/*?*/           }
/*M*/           /* Keine Invalidierung notwendig */
/*M*/           break;
/*M*/
/*M*/       case RES_CHAIN:
/*M*/           {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/                SwFmtChain *pChain = (SwFmtChain*)pNew;
//STRIP001 /*?*/                if ( pChain->GetNext() )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    SwFlyFrm *pFollow = FindChainNeighbour( *pChain->GetNext() );
//STRIP001 /*?*/                    if ( GetNextLink() && pFollow != GetNextLink() )
//STRIP001 /*?*/                        SwFlyFrm::UnchainFrames( this, GetNextLink());
//STRIP001 /*?*/                    if ( pFollow )
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        if ( pFollow->GetPrevLink() &&
//STRIP001 /*?*/                             pFollow->GetPrevLink() != this )
//STRIP001 /*?*/                            SwFlyFrm::UnchainFrames( pFollow->GetPrevLink(),
//STRIP001 /*?*/                                                     pFollow );
//STRIP001 /*?*/                        if ( !GetNextLink() )
//STRIP001 /*?*/                            SwFlyFrm::ChainFrames( this, pFollow );
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                }
//STRIP001 /*?*/                else if ( GetNextLink() )
//STRIP001 /*?*/                    SwFlyFrm::UnchainFrames( this, GetNextLink() );
//STRIP001 /*?*/                if ( pChain->GetPrev() )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    SwFlyFrm *pMaster = FindChainNeighbour( *pChain->GetPrev() );
//STRIP001 /*?*/                    if ( GetPrevLink() && pMaster != GetPrevLink() )
//STRIP001 /*?*/                        SwFlyFrm::UnchainFrames( GetPrevLink(), this );
//STRIP001 /*?*/                    if ( pMaster )
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        if ( pMaster->GetNextLink() &&
//STRIP001 /*?*/                             pMaster->GetNextLink() != this )
//STRIP001 /*?*/                            SwFlyFrm::UnchainFrames( pMaster,
//STRIP001 /*?*/                                                     pMaster->GetNextLink() );
//STRIP001 /*?*/                        if ( !GetPrevLink() )
//STRIP001 /*?*/                            SwFlyFrm::ChainFrames( pMaster, this );
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                }
//STRIP001 /*?*/                else if ( GetPrevLink() )
//STRIP001 /*?*/                    SwFlyFrm::UnchainFrames( GetPrevLink(), this );
/*M*/           }
/*M*/
/*M*/       default:
/*M*/           bClear = FALSE;
/*M*/   }
/*M*/   if ( bClear )
/*M*/   {
/*M*/       if ( pOldSet || pNewSet )
/*M*/       {
/*M*/           if ( pOldSet )
/*M*/               pOldSet->ClearItem( nWhich );
/*M*/           if ( pNewSet )
/*M*/               pNewSet->ClearItem( nWhich );
/*M*/       }
/*M*/       else
/*M*/           SwLayoutFrm::Modify( pOld, pNew );
/*M*/   }
/*M*/ }

/*************************************************************************
|*
|*                SwFlyFrm::GetInfo()
|*
|*    Beschreibung      erfragt Informationen
|*    Ersterstellung    JP 31.03.94
|*    Letzte Aenderung  JP 31.03.94
|*
*************************************************************************/

    // erfrage vom Modify Informationen
/*N*/ BOOL SwFlyFrm::GetInfo( SfxPoolItem & rInfo ) const
/*N*/ {
/*N*/   if( RES_AUTOFMT_DOCNODE == rInfo.Which() )
/*N*/       return FALSE;   // es gibt einen FlyFrm also wird er benutzt
/*?*/   return TRUE;        // weiter suchen
/*N*/ }

/*************************************************************************
|*
|*  SwFlyFrm::_Invalidate()
|*
|*  Ersterstellung      MA 15. Oct. 92
|*  Letzte Aenderung    MA 26. Jun. 96
|*
|*************************************************************************/

/*N*/ void SwFlyFrm::_Invalidate( SwPageFrm *pPage )
/*N*/ {
/*N*/   InvalidatePage( pPage );
/*N*/   bNotifyBack = bInvalid = TRUE;
/*N*/
/*N*/   SwFlyFrm *pFrm;
/*N*/   if ( GetAnchor() && 0 != (pFrm = GetAnchor()->FindFlyFrm()) )
/*N*/   {
/*N*/       //Gaanz dumm: Wenn der Fly innerhalb eines Fly gebunden ist, der
/*N*/       //Spalten enthaehlt, sollte das Format von diesem ausgehen.
/*N*/       if ( !pFrm->IsLocked() && !pFrm->IsColLocked() &&
/*N*/            pFrm->Lower() && pFrm->Lower()->IsColumnFrm() )
/*N*/           pFrm->InvalidateSize();
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|*  SwFlyFrm::ChgRelPos()
|*
|*  Beschreibung        Aenderung der relativen Position, die Position wird
|*      damit automatisch Fix, das Attribut wird entprechend angepasst.
|*  Ersterstellung      MA 25. Aug. 92
|*  Letzte Aenderung    MA 09. Aug. 95
|*
|*************************************************************************/

//STRIP001 void SwFlyFrm::ChgRelPos( const Point &rNewPos )
//STRIP001 {
//STRIP001  if ( GetCurRelPos() != rNewPos )
//STRIP001  {
//STRIP001      SwFrmFmt *pFmt = GetFmt();
//STRIP001         SWRECTFN( GetAnchor() )
//STRIP001         SwTwips nNewY = bVert ? rNewPos.X() : rNewPos.Y();
//STRIP001         SwTwips nTmpY = nNewY == LONG_MAX ? 0 : nNewY;
//STRIP001         if( bVert )
//STRIP001             nTmpY = -nTmpY;
//STRIP001      SfxItemSet aSet( pFmt->GetDoc()->GetAttrPool(),
//STRIP001                       RES_VERT_ORIENT, RES_HORI_ORIENT);
//STRIP001
//STRIP001      SwFmtVertOrient aVert( pFmt->GetVertOrient() );
//STRIP001      SwTxtFrm *pAutoFrm = NULL;
//STRIP001      if( IsFlyAtCntFrm() || VERT_NONE != aVert.GetVertOrient() )
//STRIP001      {
//STRIP001          if( REL_CHAR == aVert.GetRelationOrient() && IsAutoPos() )
//STRIP001          {
//STRIP001                 if( LONG_MAX != nNewY )
//STRIP001              {
//STRIP001                  aVert.SetVertOrient( VERT_NONE );
//STRIP001                  xub_StrLen nOfs =
//STRIP001                      pFmt->GetAnchor().GetCntntAnchor()->nContent.GetIndex();
//STRIP001                  ASSERT( GetAnchor()->IsTxtFrm(), "TxtFrm expected" );
//STRIP001                  pAutoFrm = (SwTxtFrm*)GetAnchor();
//STRIP001                  while( pAutoFrm->GetFollow() &&
//STRIP001                         pAutoFrm->GetFollow()->GetOfst() <= nOfs )
//STRIP001                  {
//STRIP001                      if( pAutoFrm == GetAnchor() )
//STRIP001                          nTmpY += pAutoFrm->GetRelPos().Y();
//STRIP001                      nTmpY -= pAutoFrm->GetUpper()->Prt().Height();
//STRIP001                      pAutoFrm = pAutoFrm->GetFollow();
//STRIP001                  }
//STRIP001                  nTmpY = ((SwFlyAtCntFrm*)this)->GetRelCharY(pAutoFrm)-nTmpY;
//STRIP001              }
//STRIP001              else
//STRIP001                  aVert.SetVertOrient( VERT_CHAR_BOTTOM );
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              aVert.SetVertOrient( VERT_NONE );
//STRIP001              aVert.SetRelationOrient( FRAME );
//STRIP001          }
//STRIP001      }
//STRIP001      aVert.SetPos( nTmpY );
//STRIP001      aSet.Put( aVert );
//STRIP001
//STRIP001         //Fuer Flys im Cnt ist die horizontale Ausrichtung uninteressant,
//STRIP001      //den sie ist stets 0.
//STRIP001      if ( !IsFlyInCntFrm() )
//STRIP001      {
//STRIP001             SwTwips nNewX = bVert ? rNewPos.Y() : rNewPos.X();
//STRIP001             SwTwips nTmpX = nNewX == LONG_MAX ? 0 : nNewX;
//STRIP001          SwFmtHoriOrient aHori( pFmt->GetHoriOrient() );
//STRIP001          if( IsFlyAtCntFrm() || HORI_NONE != aHori.GetHoriOrient() )
//STRIP001          {
//STRIP001              aHori.SetHoriOrient( HORI_NONE );
//STRIP001              if( REL_CHAR == aHori.GetRelationOrient() && IsAutoPos() )
//STRIP001              {
//STRIP001                     if( LONG_MAX != nNewX )
//STRIP001                  {
//STRIP001                      if( !pAutoFrm )
//STRIP001                      {
//STRIP001                          xub_StrLen nOfs = pFmt->GetAnchor().GetCntntAnchor()
//STRIP001                                        ->nContent.GetIndex();
//STRIP001                          ASSERT( GetAnchor()->IsTxtFrm(), "TxtFrm expected");
//STRIP001                          pAutoFrm = (SwTxtFrm*)GetAnchor();
//STRIP001                          while( pAutoFrm->GetFollow() &&
//STRIP001                                 pAutoFrm->GetFollow()->GetOfst() <= nOfs )
//STRIP001                              pAutoFrm = pAutoFrm->GetFollow();
//STRIP001                      }
//STRIP001                      nTmpX -= ((SwFlyAtCntFrm*)this)->GetRelCharX(pAutoFrm);
//STRIP001                  }
//STRIP001              }
//STRIP001              else
//STRIP001                  aHori.SetRelationOrient( FRAME );
//STRIP001              aHori.SetPosToggle( FALSE );
//STRIP001          }
//STRIP001          aHori.SetPos( nTmpX );
//STRIP001          aSet.Put( aHori );
//STRIP001      }
//STRIP001      pFmt->GetDoc()->SetAttr( aSet, *pFmt );
//STRIP001  }
//STRIP001 }
/*************************************************************************
|*
|*  SwFlyFrm::Format()
|*
|*  Beschreibung:       "Formatiert" den Frame; Frm und PrtArea.
|*                      Die Fixsize wird hier nicht eingestellt.
|*  Ersterstellung      MA 14. Jun. 93
|*  Letzte Aenderung    MA 13. Jun. 96
|*
|*************************************************************************/

/*N*/ void SwFlyFrm::Format( const SwBorderAttrs *pAttrs )
/*N*/ {
/*N*/   ASSERT( pAttrs, "FlyFrm::Format, pAttrs ist 0." );
/*N*/
/*N*/   ColLock();
/*N*/
/*N*/   if ( !bValidSize )
/*N*/   {
/*N*/       if ( Frm().Top() == WEIT_WECH && Frm().Left() == WEIT_WECH )
/*N*/           //Sicherheitsschaltung wegnehmen (siehe SwFrm::CTor)
/*N*/           Frm().Pos().X() = Frm().Pos().Y() = 0;
/*N*/
/*N*/       //Breite der Spalten pruefen und ggf. einstellen.
/*N*/       if ( Lower() && Lower()->IsColumnFrm() )
/*N*/           AdjustColumns( 0, FALSE );
/*N*/
/*N*/       bValidSize = TRUE;
/*N*/
/*N*/       const SwTwips nUL  = pAttrs->CalcTopLine() + pAttrs->CalcBottomLine();
/*N*/       const SwTwips nLR  = pAttrs->CalcLeftLine()+ pAttrs->CalcRightLine();
/*N*/       const Size    &rSz = pAttrs->GetSize();
/*N*/       const SwFmtFrmSize &rFrmSz = GetFmt()->GetFrmSize();
/*N*/
/*N*/       ASSERT( rSz.Height() != 0 || rFrmSz.GetHeightPercent(), "Hoehe des RahmenAttr ist 0." );
/*N*/       ASSERT( rSz.Width()  != 0 || rFrmSz.GetWidthPercent(), "Breite des RahmenAttr ist 0." );
/*N*/
/*N*/         SWRECTFN( this )
/*N*/         if( !HasFixSize() )
/*N*/       {
/*N*/             SwTwips nRemaining = 0;
/*N*/             SwTwips nOldHeight = (Frm().*fnRect->fnGetHeight)();
/*N*/             long nMinHeight = 0;
/*N*/             if( IsMinHeight() )
/*N*/             {
/*N*/                 Size aSz( CalcRel( rFrmSz ) );
/*N*/                 nMinHeight = bVert ? aSz.Width() : aSz.Height();
/*N*/             }
/*N*/           if ( Lower() )
/*N*/           {
/*N*/               if ( Lower()->IsColumnFrm() )
/*N*/               {
/*N*/                   FormatWidthCols( *pAttrs, nUL, nMinHeight );
/*N*/                     nRemaining = (Lower()->Frm().*fnRect->fnGetHeight)();
/*N*/               }
/*N*/               else
/*N*/               {
/*N*/                   SwFrm *pFrm = Lower();
/*N*/                   while ( pFrm )
/*N*/                     {   nRemaining += (pFrm->Frm().*fnRect->fnGetHeight)();
/*N*/                       if( pFrm->IsTxtFrm() && ((SwTxtFrm*)pFrm)->IsUndersized() )
/*N*/                           // Dieser TxtFrm waere gern ein bisschen groesser
/*N*/                           nRemaining += ((SwTxtFrm*)pFrm)->GetParHeight()
/*N*/                                     - (pFrm->Prt().*fnRect->fnGetHeight)();
/*N*/                       else if( pFrm->IsSctFrm() && ((SwSectionFrm*)pFrm)->IsUndersized() )
/*N*/                           nRemaining += ((SwSectionFrm*)pFrm)->Undersize();
/*N*/                       pFrm = pFrm->GetNext();
/*N*/                   }
/*N*/                     if( !nRemaining )
/*N*/                         nRemaining = nOldHeight - nUL;
/*N*/               }
/*N*/               if ( GetDrawObjs() )
/*N*/               {
/*?*/                   USHORT nCnt = GetDrawObjs()->Count();
/*?*/                     SwTwips nTop = (Frm().*fnRect->fnGetTop)();
/*?*/                     SwTwips nBorder = (Frm().*fnRect->fnGetHeight)() -
/*?*/                                       (Prt().*fnRect->fnGetHeight)();
/*?*/                   for ( USHORT i = 0; i < nCnt; ++i )
/*?*/                   {
/*?*/                       SdrObject *pO = (*GetDrawObjs())[i];
/*?*/                       if ( pO->IsWriterFlyFrame() )
/*?*/                       {
/*?*/                           SwFlyFrm *pFly = ((SwVirtFlyDrawObj*)pO)->GetFlyFrm();
/*?*/                             if( pFly->IsFlyLayFrm() &&
/*?*/                                 pFly->Frm().Top() != WEIT_WECH )
/*?*/                           {
/*?*/                                 SwTwips nDist = -(pFly->Frm().*fnRect->
/*?*/                                     fnBottomDist)( nTop );
/*?*/                                 if( nDist > nBorder + nRemaining )
/*?*/                                     nRemaining = nDist - nBorder;
/*?*/                           }
/*?*/                       }
/*?*/                   }
/*N*/               }
/*N*/           }
/*N*/ #ifndef PRODUCT
/*N*/           if ( IsMinHeight() )
/*N*/           {
/*N*/                 const Size aSizeII = CalcRel( rFrmSz );
/*N*/                 ASSERT( nMinHeight==(bVert? aSizeII.Width() : aSizeII.Height()),
/*N*/                         "FlyFrm::Format: Changed MinHeight" );
/*N*/           }
/*N*/ #endif
/*N*/           if( IsMinHeight() && (nRemaining + nUL) < nMinHeight )
/*N*/               nRemaining = nMinHeight - nUL;
/*N*/           //Weil das Grow/Shrink der Flys die Groessen nicht direkt
/*N*/           //einstellt, sondern indirekt per Invalidate ein Format
/*N*/           //ausloesst, muessen die Groessen hier direkt eingestellt
/*N*/           //werden. Benachrichtung laeuft bereits mit.
/*N*/           //Weil bereits haeufiger 0en per Attribut hereinkamen wehre
/*N*/           //ich mich ab sofort dagegen.
/*N*/           if ( nRemaining < MINFLY )
/*?*/               nRemaining = MINFLY;
/*N*/             (Prt().*fnRect->fnSetHeight)( nRemaining );
/*N*/             nRemaining -= (Frm().*fnRect->fnGetHeight)();
/*N*/             (Frm().*fnRect->fnAddBottom)( nRemaining + nUL );
/*N*/           bValidSize = TRUE;
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           bValidSize = TRUE;  //Fixe Frms formatieren sich nicht.
/*N*/                               //Flys stellen ihre Groesse anhand des Attr ein.
/*N*/             Size aSz( CalcRel( rFrmSz ) );
/*N*/             SwTwips nNewSize = bVert ? aSz.Width() : aSz.Height();
/*N*/             nNewSize -= nUL;
/*N*/             if( nNewSize < MINFLY )
/*?*/                 nNewSize = MINFLY;
/*N*/             (Prt().*fnRect->fnSetHeight)( nNewSize );
/*N*/             nNewSize += nUL - (Frm().*fnRect->fnGetHeight)();
/*N*/             (Frm().*fnRect->fnAddBottom)( nNewSize );
/*N*/       }
/*N*/       if ( !bFormatHeightOnly )
/*N*/       {
/*N*/             Size aSz( CalcRel( rFrmSz ) );
/*N*/             SwTwips nNewSize = bVert ? aSz.Height() : aSz.Width();
/*N*/             nNewSize -= nLR;
/*N*/             if( nNewSize < MINFLY )
/*?*/                 nNewSize = MINFLY;
/*N*/             (Prt().*fnRect->fnSetWidth)( nNewSize );
/*N*/             nNewSize += nLR - (Frm().*fnRect->fnGetWidth)();
/*N*/             (Frm().*fnRect->fnAddRight)( nNewSize );
/*N*/       }
/*N*/   }
/*N*/   ColUnlock();
/*N*/ }

// OD 14.03.2003 #i11760# - change parameter <bNoColl>: type <bool>;
//                          default value = false.
// OD 14.03.2003 #i11760# - add new parameter <bNoCalcFollow> with
//                          default value = false.
// OD 11.04.2003 #108824# - new parameter <bNoCalcFollow> was used by method
//                          <FormatWidthCols(..)> to avoid follow formatting
//                          for text frames. But, unformatted follows causes
//                          problems in method <SwCntntFrm::_WouldFit(..)>,
//                          which assumes that the follows are formatted.
//                          Thus, <bNoCalcFollow> no longer used by <FormatWidthCols(..)>.
//void CalcCntnt( SwLayoutFrm *pLay, BOOL bNoColl )
/*N*/ void CalcCntnt( SwLayoutFrm *pLay,
/*N*/                 bool bNoColl,
/*N*/                 bool bNoCalcFollow )
/*N*/ {
/*N*/   SwSectionFrm* pSect;
/*N*/   BOOL bCollect = FALSE;
/*N*/   if( pLay->IsSctFrm() )
/*N*/   {
/*N*/       pSect = (SwSectionFrm*)pLay;
/*N*/       if( pSect->IsEndnAtEnd() && !bNoColl )
/*N*/       {
/*?*/           DBG_ASSERT(0, "STRIP"); //STRIP001 bCollect = TRUE;
//STRIP001 /*?*/            SwLayouter::CollectEndnotes( pLay->GetFmt()->GetDoc(), pSect );
/*N*/       }
/*N*/       pSect->CalcFtnCntnt();
/*N*/   }
/*N*/   else
/*N*/       pSect = NULL;
/*N*/   SwFrm *pFrm = pLay->ContainsAny();
/*N*/   if ( !pFrm )
/*N*/   {
/*?*/       if( pSect )
/*?*/       {
/*?*/           if( pSect->HasFollow() )
/*?*/               pFrm = pSect->GetFollow()->ContainsAny();
/*?*/           if( !pFrm )
/*?*/           {
/*?*/               if( pSect->IsEndnAtEnd() )
/*?*/               {
/*?*/                   if( bCollect )
/*?*/                   {DBG_ASSERT(0, "STRIP");} //STRIP001    pLay->GetFmt()->GetDoc()->GetLayouter()->
//STRIP001 /*?*/                            InsertEndnotes( pSect );
/*?*/                   BOOL bLock = pSect->IsFtnLock();
/*?*/                   pSect->SetFtnLock( TRUE );
/*?*/                   pSect->CalcFtnCntnt();
/*?*/                   pSect->CalcFtnCntnt();
/*?*/                   pSect->SetFtnLock( bLock );
/*?*/               }
/*?*/               return;
/*?*/           }
/*?*/           pFrm->_InvalidatePos();
/*?*/       }
/*?*/       else
/*?*/           return;
/*N*/   }
/*N*/   pFrm->InvalidatePage();
/*N*/
/*N*/   do
/*N*/   {
/*N*/       SwFlyFrm *pAgainFly1 = 0,       //Oszillation abknipsen.
/*N*/                *pAgainFly2 = 0;
/*N*/       SwFrm* pLast;
/*N*/       do
/*N*/       {
/*N*/           pLast = pFrm;
/*N*/             if( pFrm->IsVertical() ?
/*N*/                 ( pFrm->GetUpper()->Prt().Height() != pFrm->Frm().Height() )
/*N*/                 : ( pFrm->GetUpper()->Prt().Width() != pFrm->Frm().Width() ) )
/*N*/           {
/*N*/               pFrm->Prepare( PREP_FIXSIZE_CHG );
/*N*/               pFrm->_InvalidateSize();
/*N*/           }
/*N*/
/*N*/           if ( pFrm->IsTabFrm() )
/*N*/           {
/*N*/               ((SwTabFrm*)pFrm)->bCalcLowers = TRUE;
/*N*/               if ( ((SwTabFrm*)pFrm)->IsFollow() )
/*?*/                   ((SwTabFrm*)pFrm)->bLockBackMove = TRUE;
/*N*/           }
/*N*/
/*N*/             // OD 14.03.2003 #i11760# - forbid format of follow, if requested.
/*N*/             if ( bNoCalcFollow && pFrm->IsTxtFrm() )
/*N*/                 static_cast<SwTxtFrm*>(pFrm)->ForbidFollowFormat();
/*N*/             pFrm->Calc();
/*N*/             // OD 14.03.2003 #i11760# - reset control flag for follow format.
/*N*/             if ( pFrm->IsTxtFrm() )
/*N*/             {
/*N*/                 static_cast<SwTxtFrm*>(pFrm)->AllowFollowFormat();
/*N*/             }
/*N*/
/*N*/           //Dumm aber wahr, die Flys muessen mitkalkuliert werden.
/*N*/           BOOL bAgain = FALSE;
/*N*/             if ( pFrm->GetDrawObjs() && pLay->IsAnLower( pFrm ) )
/*N*/           {
/*N*/               USHORT nCnt = pFrm->GetDrawObjs()->Count();
/*N*/               for ( USHORT i = 0; i < nCnt; ++i )
/*N*/               {
/*N*/                   SdrObject *pO = (*pFrm->GetDrawObjs())[i];
/*N*/                   if ( pO->IsWriterFlyFrame() )
/*N*/                   {
/*N*/                       SwFlyFrm *pFly = ((SwVirtFlyDrawObj*)pO)->GetFlyFrm();
/*N*/                       pFly->InvalidatePos();
/*N*/                       SwRect aRect( pFly->Frm() );
/*N*/                       pFly->Calc();
/*N*/                       if ( aRect != pFly->Frm() )
/*N*/                       {
/*N*/                           bAgain = TRUE;
/*N*/                           if ( pAgainFly2 == pFly )
/*N*/                           {
/*?*/                               //Oszillation unterbinden.
/*?*/                               SwFrmFmt *pFmt = pFly->GetFmt();
/*?*/                               SwFmtSurround aAttr( pFmt->GetSurround() );
/*?*/                               if( SURROUND_THROUGHT != aAttr.GetSurround() )
/*?*/                               {
/*?*/                                   // Bei autopositionierten hilft manchmal nur
/*?*/                                   // noch, auf Durchlauf zu schalten
/*?*/                                   if( pFly->IsAutoPos() &&
/*?*/                                       SURROUND_PARALLEL == aAttr.GetSurround() )
/*?*/                                       aAttr.SetSurround( SURROUND_THROUGHT );
/*?*/                                   else
/*?*/                                       aAttr.SetSurround( SURROUND_PARALLEL );
/*?*/                                   pFmt->LockModify();
/*?*/                                   pFmt->SetAttr( aAttr );
/*?*/                                   pFmt->UnlockModify();
/*?*/                               }
/*N*/                           }
/*N*/                           else
/*N*/                           {
/*N*/                               if ( pAgainFly1 == pFly )
/*?*/                                   pAgainFly2 = pFly;
/*N*/                               pAgainFly1 = pFly;
/*N*/                           }
/*N*/                       }
/*N*/                       if ( !pFrm->GetDrawObjs() )
/*?*/                           break;
/*N*/                       if ( pFrm->GetDrawObjs()->Count() < nCnt )
/*N*/                       {
/*?*/                           --i;
/*?*/                           --nCnt;
/*N*/                       }
/*N*/                   }
/*N*/               }
/*N*/               if ( bAgain )
/*N*/               {
/*N*/                   pFrm = pLay->ContainsCntnt();
/*N*/                   if ( pFrm && pFrm->IsInTab() )
/*?*/                       pFrm = pFrm->FindTabFrm();
/*N*/                   if( pFrm && pFrm->IsInSct() )
/*N*/                   {
/*?*/                       SwSectionFrm* pTmp = pFrm->FindSctFrm();
/*?*/                       if( pTmp != pLay && pLay->IsAnLower( pTmp ) )
/*?*/                           pFrm = pTmp;
/*N*/                   }
/*N*/                   continue;
/*N*/               }
/*N*/           }
/*N*/           if ( pFrm->IsTabFrm() )
/*N*/           {
/*N*/               if ( ((SwTabFrm*)pFrm)->IsFollow() )
/*?*/                   ((SwTabFrm*)pFrm)->bLockBackMove = FALSE;
/*N*/           }
/*N*/
/*N*/           pFrm = pFrm->FindNext();
/*N*/           if( pFrm && pFrm->IsSctFrm() && pSect )
/*N*/           {
/*N*/               // Es koennen hier leere SectionFrms herumspuken
/*N*/               while( pFrm && pFrm->IsSctFrm() && !((SwSectionFrm*)pFrm)->GetSection() )
/*?*/                   pFrm = pFrm->FindNext();
/*N*/               // Wenn FindNext den Follow des urspruenglichen Bereichs liefert,
/*N*/               // wollen wir mit dessen Inhalt weitermachen, solange dieser
/*N*/               // zurueckfliesst.
/*N*/               if( pFrm && pFrm->IsSctFrm() && ( pFrm == pSect->GetFollow() ||
/*N*/                   ((SwSectionFrm*)pFrm)->IsAnFollow( pSect ) ) )
/*N*/               {
/*N*/                   pFrm = ((SwSectionFrm*)pFrm)->ContainsAny();
/*N*/                   if( pFrm )
/*N*/                       pFrm->_InvalidatePos();
/*N*/               }
/*N*/           }
/*N*/           // Im pLay bleiben, Ausnahme, bei SectionFrms mit Follow wird der erste
/*N*/           // CntntFrm des Follows anformatiert, damit er die Chance erhaelt, in
/*N*/           // pLay zu landen. Solange diese Frames in pLay landen, geht's weiter.
/*N*/       } while ( pFrm && ( pLay->IsAnLower( pFrm ) ||
/*N*/               ( pSect && ( ( pSect->HasFollow() && ( pLay->IsAnLower( pLast )
/*N*/               ||(pLast->IsInSct() && pLast->FindSctFrm()->IsAnFollow(pSect)) )
/*N*/               && pSect->GetFollow()->IsAnLower( pFrm ) ) || ( pFrm->IsInSct()
/*N*/               && pFrm->FindSctFrm()->IsAnFollow( pSect ) ) ) ) ) );
/*N*/       if( pSect )
/*N*/       {
/*N*/           if( bCollect )
/*N*/           {
/*?*/               DBG_ASSERT(0, "STRIP"); //STRIP001 pLay->GetFmt()->GetDoc()->GetLayouter()->InsertEndnotes(pSect);
//STRIP001 /*?*/                pSect->CalcFtnCntnt();
/*N*/           }
/*N*/           if( pSect->HasFollow() )
/*N*/           {
/*N*/               SwSectionFrm* pNxt = pSect->GetFollow();
/*N*/               while( pNxt && !pNxt->ContainsCntnt() )
/*?*/                   pNxt = pNxt->GetFollow();
/*N*/               if( pNxt )
/*N*/                   pNxt->CalcFtnCntnt();
/*N*/           }
/*N*/           if( bCollect )
/*N*/           {
/*?*/               pFrm = pLay->ContainsAny();
/*?*/               bCollect = FALSE;
/*?*/               if( pFrm )
/*?*/                   continue;
/*N*/           }
/*N*/       }
/*N*/       break;
/*N*/   }
/*?*/   while( TRUE );
/*N*/ }

/*************************************************************************
|*
|*  SwFlyFrm::MakeFlyPos()
|*
|*  Ersterstellung      MA ??
|*  Letzte Aenderung    MA 14. Nov. 96
|*
|*************************************************************************/

/*M*/ void SwFlyFrm::MakeFlyPos()
/*M*/ {
/*M*/   if ( !bValidPos )
/*M*/   {   bValidPos = TRUE;
/*M*/       GetAnchor()->Calc();
/*M*/         SWRECTFN( GetAnchor() );
/*M*/           //Die Werte in den Attributen muessen ggf. upgedated werden,
/*M*/           //deshalb werden hier Attributinstanzen und Flags benoetigt.
/*M*/       SwFlyFrmFmt *pFmt = (SwFlyFrmFmt*)GetFmt();
/*M*/       BOOL bFlyAtFly = FLY_AT_FLY == pFmt->GetAnchor().GetAnchorId();
/*M*/       SwFmtVertOrient aVert( pFmt->GetVertOrient() );
/*M*/       SwFmtHoriOrient aHori( pFmt->GetHoriOrient() );
/*M*/       const SvxLRSpaceItem &rLR = pFmt->GetLRSpace();
/*M*/       const SvxULSpaceItem &rUL = pFmt->GetULSpace();
/*M*/       FASTBOOL bVertChgd = FALSE,
/*M*/                bHoriChgd = FALSE;
/*M*/
/*M*/       //Horizontale und vertikale Positionen werden getrennt berechnet.
/*M*/       //Sie koennen jeweils Fix oder Variabel (automatisch) sein.
/*M*/
/*M*/       //Erst die vertikale Position
/*M*/       BOOL bVertPrt = aVert.GetRelationOrient() == PRTAREA ||
/*M*/                       aVert.GetRelationOrient() == REL_PG_PRTAREA;
/*M*/       if ( aVert.GetVertOrient() == VERT_NONE )
/*M*/       {
/*M*/           SwTwips nYPos = aVert.GetPos();
/*M*/           if ( bVertPrt )
/*M*/           {
/*M*/                 nYPos += (GetAnchor()->*fnRect->fnGetTopMargin)();
/*M*/                 if( GetAnchor()->IsPageFrm() && !bVert )
/*M*/               {
/*M*/                   SwFrm* pPrtFrm = ((SwPageFrm*)GetAnchor())->Lower();
/*M*/                   if( pPrtFrm && pPrtFrm->IsHeaderFrm() )
/*M*/                         nYPos += (pPrtFrm->Frm().*fnRect->fnGetHeight)();
/*M*/               }
/*M*/           }
/*M*/           if( nYPos < 0 )
/*M*/ #ifdef AMA_OUT_OF_FLY
/*M*/             if( !bFlyAtFly  )
/*M*/ #endif
/*M*/               nYPos = 0;
/*M*/             if( bVert )
/*M*/             {
/*M*/                 aRelPos.X() = bRev ? nYPos : -nYPos;
/*M*/                 aRelPos.X() -= Frm().Width();
/*M*/             }
/*M*/             else
/*M*/                 aRelPos.Y() = nYPos;
/*M*/       }
/*M*/       else
/*M*/       {   //Zuerst den Bezugsrahmen festlegen (PrtArea oder Frame)
/*M*/           SwTwips nRel, nAdd;
/*M*/           if ( bVertPrt )
/*M*/             {   nRel = (GetAnchor()->Prt().*fnRect->fnGetHeight)();
/*M*/                 nAdd = (GetAnchor()->*fnRect->fnGetTopMargin)();
/*M*/                 if( GetAnchor()->IsPageFrm() && !bVert )
/*M*/               {
/*M*/                   // Wenn wir am SeitenTextBereich ausgerichtet sind,
/*M*/                   // sollen Kopf- und Fusszeilen _nicht_ mit zaehlen.
/*M*/                   SwFrm* pPrtFrm = ((SwPageFrm*)GetAnchor())->Lower();
/*M*/                   while( pPrtFrm )
/*M*/                   {
/*M*/                       if( pPrtFrm->IsHeaderFrm() )
/*M*/                       {
/*M*/                           nRel -= pPrtFrm->Frm().Height();
/*M*/                           nAdd += pPrtFrm->Frm().Height();
/*M*/                       }
/*M*/                       else if( pPrtFrm->IsFooterFrm() )
/*M*/                           nRel -= pPrtFrm->Frm().Height();
/*M*/                       pPrtFrm = pPrtFrm->GetNext();
/*M*/                   }
/*M*/               }
/*M*/           }
/*M*/           else
/*M*/             {   nRel = (GetAnchor()->Frm().*fnRect->fnGetHeight)();
/*M*/               nAdd = 0;
/*M*/           }
/*M*/           // Bei rahmengebunden Rahmen wird nur vertikal unten oder zentriert
/*M*/           // ausgerichtet, wenn der Text durchlaeuft oder der Anker eine feste
/*M*/           // Hoehe besitzt.
/*M*/             SwTwips nRelPosY;
/*M*/             SwTwips nFrmHeight = (aFrm.*fnRect->fnGetHeight)();
/*M*/           if( bFlyAtFly && VERT_TOP != aVert.GetVertOrient() &&
/*M*/               SURROUND_THROUGHT != pFmt->GetSurround().GetSurround() &&
/*M*/                 !GetAnchor()->HasFixSize() )
/*M*/                 nRelPosY = bVert ? rLR.GetRight() : rUL.GetUpper();
/*M*/           else if ( aVert.GetVertOrient() == VERT_CENTER )
/*M*/                 nRelPosY = (nRel / 2) - (nFrmHeight / 2);
/*M*/           else if ( aVert.GetVertOrient() == VERT_BOTTOM )
/*M*/                 nRelPosY = nRel - ( nFrmHeight +
/*M*/                                    ( bVert ? rLR.GetLeft() : rUL.GetLower() ) );
/*M*/           else
/*M*/                 nRelPosY = bVert ? rLR.GetRight() : rUL.GetUpper();
/*M*/             nRelPosY += nAdd;
/*M*/             if( bVert )
/*M*/                 nRelPosY += nFrmHeight;
/*M*/
/*M*/             if ( aVert.GetPos() != nRelPosY )
/*M*/             {   aVert.SetPos( nRelPosY );
/*M*/               bVertChgd = TRUE;
/*M*/           }
/*M*/             if( bVert )
/*M*/             {
/*M*/                 if( !bRev )
/*M*/                     nRelPosY = - nRelPosY;
/*M*/                 aRelPos.X() = nRelPosY;
/*M*/             }
/*M*/             else
/*M*/                 aRelPos.Y() = nRelPosY;
/*M*/       }
/*M*/
/*M*/       //Fuer die Hoehe der Seiten im Browser muessen wir etwas tricksen. Das
/*M*/       //Grow muessen wir auf den Body rufen; wegen ggf. eingeschalteter
/*M*/       //Kopfzeilen und weil die Seite sowieso eine fix-Hoehe hat.
/*M*/       if ( !bFlyAtFly && GetFmt()->GetDoc()->IsBrowseMode() &&
/*M*/            GetAnchor()->IsPageFrm() ) //Was sonst?
/*M*/       {
/*M*/           const long nAnchorBottom = GetAnchor()->Frm().Bottom();
/*M*/           const long nBottom = GetAnchor()->Frm().Top() + aRelPos.Y() + Frm().Height();
/*M*/           if ( nAnchorBottom < nBottom )
/*M*/           {
/*M*/               ((SwPageFrm*)GetAnchor())->FindBodyCont()->
/*M*/                                     Grow( nBottom - nAnchorBottom PHEIGHT );
/*M*/           }
/*M*/       }
/*M*/
/*M*/
/*M*/       //Jetzt die Horizontale Position
/*M*/       const BOOL bToggle = aHori.IsPosToggle()&&!FindPageFrm()->OnRightPage();
/*M*/       BOOL bTmpToggle = bToggle;
/*M*/       //und wieder erst der Bezugsrahmen
/*M*/       SwTwips nRel, nAdd;
/*M*/       SwHoriOrient eHOri = aHori.GetHoriOrient();
/*M*/       if( bToggle )
/*M*/       {
/*M*/           if( HORI_RIGHT == eHOri )
/*M*/               eHOri = HORI_LEFT;
/*M*/           else if( HORI_LEFT == eHOri )
/*M*/               eHOri = HORI_RIGHT;
/*M*/       }
/*M*/       switch ( aHori.GetRelationOrient() )
/*M*/       {
/*M*/           case PRTAREA:
/*M*/           case REL_PG_PRTAREA:
/*M*/           {
/*M*/                 nRel = (GetAnchor()->Prt().*fnRect->fnGetWidth)();
/*M*/                 nAdd = (GetAnchor()->*fnRect->fnGetLeftMargin)();
/*M*/               break;
/*M*/           }
/*M*/           case REL_PG_LEFT:
/*M*/           case REL_FRM_LEFT:
/*M*/               bTmpToggle = !bToggle;
/*M*/               // kein break;
/*M*/           case REL_PG_RIGHT:
/*M*/           case REL_FRM_RIGHT:
/*M*/           {
/*M*/               if ( bTmpToggle )    // linker Seitenrand
/*M*/               {
/*M*/                     nRel = (GetAnchor()->*fnRect->fnGetLeftMargin)();
/*M*/                   nAdd = 0;
/*M*/               }
/*M*/               else            // rechter Seitenrand
/*M*/               {
/*M*/                     nRel = (GetAnchor()->Frm().*fnRect->fnGetWidth)();
/*M*/                     nAdd = (GetAnchor()->Prt().*fnRect->fnGetRight)();
/*M*/                   nRel -= nAdd;
/*M*/               }
/*M*/               break;
/*M*/           }
/*M*/           default:
/*M*/           {
/*M*/                 nRel = (GetAnchor()->Frm().*fnRect->fnGetWidth)();
/*M*/               nAdd = 0;
/*M*/               break;
/*M*/           }
/*M*/       }
/*M*/         SwTwips nFrmWidth = (Frm().*fnRect->fnGetWidth)();
/*M*/         if( bRev )
/*M*/         {
/*M*/             nFrmWidth = -nFrmWidth;
/*M*/             nRel = -nRel;
/*M*/             nAdd = -nAdd;
/*M*/         }
/*M*/         SwTwips nRelX;
/*M*/       if ( aHori.GetHoriOrient() == HORI_NONE )
/*M*/       {
/*M*/             if( bToggle ||
/*M*/                 ( !aHori.IsPosToggle() && GetAnchor()->IsRightToLeft() ) )
/*M*/                 nRelX = nRel - nFrmWidth - aHori.GetPos();
/*M*/           else
/*M*/                 nRelX = aHori.GetPos();
/*M*/       }
/*M*/       else if ( HORI_CENTER == eHOri )
/*M*/             nRelX = (nRel / 2) - (nFrmWidth / 2);
/*M*/       else if ( HORI_RIGHT == eHOri )
/*M*/             nRelX = nRel - ( nFrmWidth +
/*M*/                                 ( bVert ? rUL.GetLower() : rLR.GetRight() ) );
/*M*/       else
/*M*/             nRelX = bVert ? rUL.GetUpper() : rLR.GetLeft();
/*M*/         nRelX += nAdd;
/*M*/
/*M*/         if( ( nRelX < 0 ) != bRev )
/*M*/             nRelX = 0;
/*M*/         if( bVert )
/*M*/             aRelPos.Y() = nRelX;
/*M*/         else
/*M*/             aRelPos.X() = nRelX;
/*M*/       if ( HORI_NONE != aHori.GetHoriOrient() &&
/*M*/             aHori.GetPos() != nRelX )
/*M*/         {   aHori.SetPos( nRelX );
/*M*/           bHoriChgd = TRUE;
/*M*/       }
/*M*/       //Die Absolute Position ergibt sich aus der absoluten Position des
/*M*/       //Ankers plus der relativen Position.
/*M*/       aFrm.Pos( aRelPos );
/*M*/         aFrm.Pos() += (GetAnchor()->Frm().*fnRect->fnGetPos)();
/*M*/
/*M*/       //Und ggf. noch die aktuellen Werte im Format updaten, dabei darf
/*M*/       //zu diesem Zeitpunkt natuerlich kein Modify verschickt werden.
/*M*/       pFmt->LockModify();
/*M*/       if ( bVertChgd )
/*M*/           pFmt->SetAttr( aVert );
/*M*/       if ( bHoriChgd )
/*M*/           pFmt->SetAttr( aHori );
/*M*/       pFmt->UnlockModify();
/*M*/   }
/*M*/ }

/*************************************************************************
|*
|*  SwFlyFrm::MakePrtArea()
|*
|*  Ersterstellung      MA 23. Jun. 93
|*  Letzte Aenderung    MA 23. Jun. 93
|*
|*************************************************************************/

/*N*/ void SwFlyFrm::MakePrtArea( const SwBorderAttrs &rAttrs )
/*N*/ {
/*N*/
/*N*/   if ( !bValidPrtArea )
/*N*/   {
/*N*/       bValidPrtArea = TRUE;
/*N*/
/*N*/       //Position einstellen.
/*N*/       aPrt.Left( rAttrs.CalcLeftLine() );
/*N*/       aPrt.Top ( rAttrs.CalcTopLine()  );
/*N*/
/*N*/       //Sizes einstellen; die Groesse gibt der umgebende Frm vor, die
/*N*/       //die Raender werden einfach abgezogen.
/*N*/       aPrt.Width ( aFrm.Width() - (rAttrs.CalcRightLine() + aPrt.Left()) );
/*N*/       aPrt.Height( aFrm.Height()- (aPrt.Top() + rAttrs.CalcBottomLine()));
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|*  SwFlyFrm::_Grow(), _Shrink()
|*
|*  Ersterstellung      MA 05. Oct. 92
|*  Letzte Aenderung    MA 05. Sep. 96
|*
|*************************************************************************/

/*N*/ SwTwips SwFlyFrm::_Grow( SwTwips nDist, BOOL bTst )
/*N*/ {
/*N*/     SWRECTFN( this )
/*N*/     if ( Lower() && !IsColLocked() && !HasFixSize() )
/*N*/   {
/*N*/         SwTwips nSize = (Frm().*fnRect->fnGetHeight)();
/*N*/         if( nSize > 0 && nDist > ( LONG_MAX - nSize ) )
/*?*/             nDist = LONG_MAX - nSize;
/*N*/
/*N*/       if ( nDist <= 0L )
/*?*/           return 0L;
/*N*/
/*N*/       if ( Lower()->IsColumnFrm() )
/*N*/       {   //Bei Spaltigkeit ubernimmt das Format die Kontrolle ueber
/*N*/           //das Wachstum (wg. des Ausgleichs).
/*N*/           if ( !bTst )
/*N*/           {   _InvalidatePos();
/*N*/               InvalidateSize();
/*N*/           }
/*N*/           return 0L;
/*N*/       }
/*N*/
/*N*/       if ( !bTst )
/*N*/       {
/*N*/           const SwRect aOld( AddSpacesToFrm() );
/*N*/           _InvalidateSize();
/*N*/           const BOOL bOldLock = bLocked;
/*N*/           Unlock();
/*N*/           if ( IsFlyFreeFrm() )
/*N*/               ((SwFlyFreeFrm*)this)->SwFlyFreeFrm::MakeAll();
/*N*/           else
/*N*/               MakeAll();
/*N*/           _InvalidateSize();
/*N*/           InvalidatePos();
/*N*/           if ( bOldLock )
/*?*/               Lock();
/*N*/           const SwRect aNew( AddSpacesToFrm() );
/*N*/           if ( aOld != aNew )
/*N*/               ::Notify( this, FindPageFrm(), aOld );
/*N*/             return (aNew.*fnRect->fnGetHeight)()-(aOld.*fnRect->fnGetHeight)();
/*N*/       }
/*N*/       return nDist;
/*N*/   }
/*N*/   return 0L;
/*N*/ }

/*M*/ SwTwips SwFlyFrm::_Shrink( SwTwips nDist, BOOL bTst )
/*M*/ {
/*M*/     if( Lower() && !IsColLocked() && !HasFixSize() && !IsNoShrink() )
/*M*/   {
/*M*/         SWRECTFN( this )
/*M*/         SwTwips nHeight = (Frm().*fnRect->fnGetHeight)();
/*M*/         if ( nDist > nHeight )
/*M*/             nDist = nHeight;
/*M*/
/*M*/         SwTwips nVal = nDist;
/*M*/       if ( IsMinHeight() )
/*M*/       {
/*M*/             const SwFmtFrmSize& rFmtSize = GetFmt()->GetFrmSize();
/*M*/             SwTwips nFmtHeight = bVert ? rFmtSize.GetWidth() : rFmtSize.GetHeight();
/*M*/
/*M*/             nVal = Min( nDist, nHeight - nFmtHeight );
/*M*/       }
/*M*/
/*M*/       if ( nVal <= 0L )
/*M*/           return 0L;
/*M*/
/*M*/       if ( Lower()->IsColumnFrm() )
/*M*/       {   //Bei Spaltigkeit ubernimmt das Format die Kontrolle ueber
/*M*/           //das Wachstum (wg. des Ausgleichs).
/*M*/           if ( !bTst )
/*M*/           {
/*M*/               SwRect aOld( AddSpacesToFrm() );
/*M*/                 (Frm().*fnRect->fnSetHeight)( nHeight - nVal );
/*M*/                 nHeight = (Prt().*fnRect->fnGetHeight)();
/*M*/                 (Prt().*fnRect->fnSetHeight)( nHeight - nVal );
/*M*/               _InvalidatePos();
/*M*/               InvalidateSize();
/*M*/               ::Notify( this, FindPageFrm(), aOld );
/*M*/               NotifyDrawObj();
/*M*/               if ( GetAnchor()->IsInFly() )
/*M*/                     GetAnchor()->FindFlyFrm()->Shrink( nDist, bTst );
/*M*/           }
/*M*/           return 0L;
/*M*/       }
/*M*/
/*M*/       if ( !bTst )
/*M*/       {
/*M*/           const SwRect aOld( AddSpacesToFrm() );
/*M*/           _InvalidateSize();
/*M*/           const BOOL bOldLocked = bLocked;
/*M*/           Unlock();
/*M*/           if ( IsFlyFreeFrm() )
/*M*/               ((SwFlyFreeFrm*)this)->SwFlyFreeFrm::MakeAll();
/*M*/           else
/*M*/               MakeAll();
/*M*/           _InvalidateSize();
/*M*/           InvalidatePos();
/*M*/           if ( bOldLocked )
/*M*/               Lock();
/*M*/           const SwRect aNew( AddSpacesToFrm() );
/*M*/           if ( aOld != aNew )
/*M*/           {
/*M*/               ::Notify( this, FindPageFrm(), aOld );
/*M*/               if ( GetAnchor()->IsInFly() )
/*M*/                     GetAnchor()->FindFlyFrm()->Shrink( nDist, bTst );
/*M*/           }
/*M*/             return (aOld.*fnRect->fnGetHeight)() -
/*M*/                    (aNew.*fnRect->fnGetHeight)();
/*M*/       }
/*M*/       return nVal;
/*M*/   }
/*M*/   return 0L;
/*M*/ }

/*************************************************************************
|*
|*  SwFlyFrm::ChgSize()
|*
|*  Ersterstellung      MA 05. Oct. 92
|*  Letzte Aenderung    MA 04. Sep. 96
|*
|*************************************************************************/

/*N*/ void SwFlyFrm::ChgSize( const Size& aNewSize )
/*N*/ {
/*N*/   if ( aNewSize != Frm().SSize() )
/*N*/   {
/*N*/       SwFrmFmt *pFmt = GetFmt();
/*N*/       SwFmtFrmSize aSz( pFmt->GetFrmSize() );
/*N*/       aSz.SetWidth( aNewSize.Width() );
/*N*/         if ( Abs(aNewSize.Height() - aSz.GetHeight()) > 1 )
/*N*/           aSz.SetHeight( aNewSize.Height() );
/*N*/       // uebers Doc fuers Undo!
/*N*/       pFmt->GetDoc()->SetAttr( aSz, *pFmt );
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|*  SwFlyFrm::IsLowerOf()
|*
|*  Ersterstellung      MA 27. Dec. 93
|*  Letzte Aenderung    MA 27. Dec. 93
|*
|*************************************************************************/

/*N*/ BOOL SwFlyFrm::IsLowerOf( const SwLayoutFrm *pUpper ) const
/*N*/ {
/*N*/   ASSERT( GetAnchor(), "8-( Fly is lost in Space." );
/*N*/   const SwFrm *pFrm = GetAnchor();
/*N*/   do
/*N*/   {   if ( pFrm == pUpper )
/*N*/           return TRUE;
/*N*/       pFrm = pFrm->IsFlyFrm() ? ((const SwFlyFrm*)pFrm)->GetAnchor() :
/*N*/                                 pFrm->GetUpper();
/*N*/   } while ( pFrm );
/*N*/   return FALSE;
/*N*/ }

/*************************************************************************
|*
|*  SwFlyFrm::Cut()
|*
|*  Ersterstellung      MA 23. Feb. 94
|*  Letzte Aenderung    MA 23. Feb. 94
|*
|*************************************************************************/

/*N*/ void SwFlyFrm::Cut()
/*N*/ {
/*N*/ }

/*************************************************************************
|*
|*  SwFrm::AppendFly(), RemoveFly()
|*
|*  Ersterstellung      MA 25. Aug. 92
|*  Letzte Aenderung    MA 09. Jun. 95
|*
|*************************************************************************/

/*N*/ void SwFrm::AppendFly( SwFlyFrm *pNew )
/*N*/ {
/*N*/   if ( !pDrawObjs )
/*N*/       pDrawObjs = new SwDrawObjs();
/*N*/   SdrObject *pObj = pNew->GetVirtDrawObj();
/*N*/   pDrawObjs->Insert( pObj, pDrawObjs->Count() );
/*N*/   pNew->ChgAnchor( this );
/*N*/
/*N*/   //Bei der Seite anmelden; kann sein, dass noch keine da ist - die
/*N*/   //Anmeldung wird dann in SwPageFrm::PreparePage durch gefuehrt.
/*N*/   SwPageFrm *pPage = FindPageFrm();
/*N*/   if ( pPage )
/*N*/   {
/*N*/       if ( pNew->IsFlyAtCntFrm() && pNew->Frm().Top() == WEIT_WECH )
/*N*/       {
/*N*/           //Versuch die Seitenformatierung von neuen Dokumenten etwas
/*N*/           //guenstiger zu gestalten.
/*N*/           //Wir haengen die Flys erstenmal nach hinten damit sie bei heftigem
/*N*/           //Fluss der Anker nicht unoetig oft formatiert werden.
/*N*/           //Damit man noch brauchbar an das Ende des Dokumentes springen
/*N*/           //kann werden die Flys nicht ganz an das Ende gehaengt.
/*N*/           SwRootFrm *pRoot = (SwRootFrm*)pPage->GetUpper();
/*N*/             if( !SwLayHelper::CheckPageFlyCache( pPage, pNew ) )
/*N*/             {
/*N*/                 SwPageFrm *pTmp = pRoot->GetLastPage();
/*N*/                 if ( pTmp->GetPhyPageNum() > 30 )
/*N*/                 {
/*N*/                     for ( USHORT i = 0; i < 10; ++i )
/*N*/                     {
/*N*/                         pTmp = (SwPageFrm*)pTmp->GetPrev();
/*N*/                         if( pTmp->GetPhyPageNum() <= pPage->GetPhyPageNum() )
/*N*/                             break; // damit wir nicht vor unserem Anker landen
/*N*/                     }
/*N*/                     if ( pTmp->IsEmptyPage() )
/*?*/                         pTmp = (SwPageFrm*)pTmp->GetPrev();
/*N*/                     pPage = pTmp;
/*N*/                 }
/*N*/           }
/*N*/           pPage->SwPageFrm::AppendFly( pNew );
/*N*/       }
/*N*/       else
/*N*/           pPage->SwPageFrm::AppendFly( pNew );
/*N*/   }
/*N*/ }

/*N*/ void SwFrm::RemoveFly( SwFlyFrm *pToRemove )
/*N*/ {
/*N*/   //Bei der Seite Abmelden - kann schon passiert sein weil die Seite
/*N*/   //bereits destruiert wurde.
/*N*/   SwPageFrm *pPage = pToRemove->FindPageFrm();
/*N*/   if ( pPage && pPage->GetSortedObjs() )
/*N*/       pPage->SwPageFrm::RemoveFly( pToRemove );
/*N*/
/*N*/   const SdrObjectPtr pObj = pToRemove->GetVirtDrawObj();
/*N*/   pDrawObjs->Remove( pDrawObjs->GetPos( pObj ) );
/*N*/   if ( !pDrawObjs->Count() )
/*N*/       DELETEZ( pDrawObjs );
/*N*/
/*N*/   pToRemove->ChgAnchor( 0 );
/*N*/
/*N*/   if ( !pToRemove->IsFlyInCntFrm() && GetUpper() && IsInTab() )//MA_FLY_HEIGHT
/*?*/       GetUpper()->InvalidateSize();
/*N*/ }

/*************************************************************************
|*
|*  SwFrm::AppendDrawObj(), RemoveDrawObj()
|*
|*  Ersterstellung      MA 09. Jan. 95
|*  Letzte Aenderung    MA 26. Jun. 95
|*
|*************************************************************************/

void SwFrm::AppendDrawObj( SwDrawContact *pNew )
{
    if ( pNew->GetAnchor() && pNew->GetAnchor() != this )
        pNew->DisconnectFromLayout( false );

    SdrObject* pObj = pNew->GetMaster();
    if ( pNew->GetAnchor() != this )
    {
        if ( !pDrawObjs )
            pDrawObjs = new SwDrawObjs();
        pDrawObjs->Insert( pObj, pDrawObjs->Count() );
        pNew->ChgAnchor( this );
    }

    const SwFmtAnchor &rAnch = pNew->GetFmt()->GetAnchor();
    if( FLY_AUTO_CNTNT == rAnch.GetAnchorId() )
    {
        SwRect aTmpRect;
        SwPosition *pPos = (SwPosition*)rAnch.GetCntntAnchor();
        if ( IsValid() )
            GetCharRect( aTmpRect, *pPos );
        else
            aTmpRect = Frm();
        pNew->GetMaster()->SetAnchorPos( aTmpRect.Pos() );
    }
    else if( FLY_IN_CNTNT != rAnch.GetAnchorId() )
    {
        pNew->GetMaster()->SetAnchorPos( GetFrmAnchorPos( ::HasWrap( pNew->GetMaster() ) ) );
    }

    // OD 27.06.2003 #108784# - move 'master' drawing object to visible layer
    {
        SwDoc* pDoc = pNew->GetFmt()->GetDoc();
        if ( pDoc )
        {
            if ( !pDoc->IsVisibleLayerId( pObj->GetLayer() ) )
            {
                pObj->SetLayer( pDoc->GetVisibleLayerIdByInvisibleOne( pObj->GetLayer() ) );
            }
        }
    }

    //Bei der Seite anmelden; kann sein, dass noch keine da ist - die
    //Anmeldung wird dann in SwPageFrm::PreparePage durch gefuehrt.
    SwPageFrm *pPage = FindPageFrm();
    if ( pPage )
        pPage->SwPageFrm::AppendDrawObj( pNew );

#ifdef ACCESSIBLE_LAYOUT
    // Notify accessible layout.
    ViewShell* pSh = GetShell();
    if( pSh && pSh->GetLayout()->IsAnyShellAccessible() )
        pSh->Imp()->AddAccessibleObj( pNew->GetMaster() );
#endif
}

// OD 20.05.2003 #108784# - add 'virtual' drawing object to frame.
void SwFrm::AppendVirtDrawObj( SwDrawContact* _pDrawContact,
                               SwDrawVirtObj* _pDrawVirtObj )
{
    if ( _pDrawVirtObj->GetAnchorFrm() != this )
    {
        if ( !pDrawObjs )
            pDrawObjs = new SwDrawObjs();
        pDrawObjs->Insert( _pDrawVirtObj, pDrawObjs->Count() );
        _pDrawVirtObj->SetAnchorFrm( this );
    }

    // positioning of 'virtual' drawing object.
    const SwFmtAnchor &rAnch = _pDrawContact->GetFmt()->GetAnchor();
    switch ( rAnch.GetAnchorId() )
    {
        case FLY_AUTO_CNTNT:
            {
                ASSERT( false,
                        "<SwFrm::AppendVirtDrawObj(..)> - at character anchored drawing objects aren't supported." );
            }
            break;
        case FLY_PAGE:
        case FLY_AT_CNTNT:
        case FLY_AT_FLY:
            {
                // set anchor position
                _pDrawVirtObj->NbcSetAnchorPos( GetFrmAnchorPos( ::HasWrap( _pDrawVirtObj ) ) );
                // set offset in relation to reference object
                Point aOffset = GetFrmAnchorPos( ::HasWrap( _pDrawVirtObj ) ) -
                                _pDrawContact->GetAnchor()->GetFrmAnchorPos( ::HasWrap( _pDrawVirtObj ) );
                _pDrawVirtObj->SetOffset( aOffset );
                // correct relative position at 'virtual' drawing object
                _pDrawVirtObj->AdjustRelativePosToReference();
            }
            break;
        case FLY_IN_CNTNT:
        {
            /*nothing to do*/;
        }
        break;
        default:    ASSERT( false, "<SwFrm::AppendVirtDrawObj(..) - unknown anchor type." );
    }

    //Bei der Seite anmelden; kann sein, dass noch keine da ist - die
    //Anmeldung wird dann in SwPageFrm::PreparePage durch gefuehrt.
    SwPageFrm *pPage = FindPageFrm();
    if ( pPage )
    {
        pPage->SwPageFrm::AppendVirtDrawObj( _pDrawContact, _pDrawVirtObj );
    }

    // Notify accessible layout.
    ViewShell* pSh = GetShell();
    if( pSh && pSh->GetLayout()->IsAnyShellAccessible() )
    {
        pSh->Imp()->AddAccessibleObj( _pDrawVirtObj );
    }
}

/*N*/ void SwFrm::RemoveDrawObj( SwDrawContact *pToRemove )
/*N*/ {
/*N*/   //Bei der Seite Abmelden - kann schon passiert sein weil die Seite
/*N*/   //bereits destruiert wurde.
/*N*/ #ifdef ACCESSIBLE_LAYOUT
/*N*/   // Notify accessible layout.
/*N*/     ViewShell* pSh = GetShell();
/*N*/   if( pSh && pSh->GetLayout()->IsAnyShellAccessible() )
/*?*/   {DBG_ASSERT(0, "STRIP"); }//STRIP001    pSh->Imp()->DisposeAccessibleObj( pToRemove->GetMaster() );
/*N*/ #endif
/*N*/   SwPageFrm *pPage = pToRemove->GetPage();
/*N*/   if ( pPage && pPage->GetSortedObjs() )
/*N*/       pPage->SwPageFrm::RemoveDrawObj( pToRemove );
/*N*/
/*N*/   SdrObject *pObj = pToRemove->GetMaster();
/*N*/   pDrawObjs->Remove( pDrawObjs->GetPos( pObj ) );
/*N*/   if ( !pDrawObjs->Count() )
/*N*/       DELETEZ( pDrawObjs );
/*N*/
/*N*/   pToRemove->ChgAnchor( 0 );
/*N*/ }

// OD 20.05.2003 #108784# - remove 'virtual' drawing object from frame.
void SwFrm::RemoveVirtDrawObj( SwDrawContact* _pDrawContact,
                               SwDrawVirtObj* _pDrawVirtObj )
{
    // Notify accessible layout.
    ViewShell* pSh = GetShell();
    if( pSh && pSh->GetLayout()->IsAnyShellAccessible() )
    {
        pSh->Imp()->DisposeAccessibleObj( _pDrawVirtObj );
    }

    SwPageFrm *pPage = _pDrawVirtObj->GetPageFrm();
    if ( pPage && pPage->GetSortedObjs() )
    {
        pPage->SwPageFrm::RemoveVirtDrawObj( _pDrawContact, _pDrawVirtObj );
    }

    pDrawObjs->Remove( pDrawObjs->GetPos( _pDrawVirtObj ) );
    if ( !pDrawObjs->Count() )
        DELETEZ( pDrawObjs );

    _pDrawVirtObj->SetAnchorFrm( 0 );
}

/*************************************************************************
|*
|*  SwFrm::CalcFlys()
|*
|*  Ersterstellung      MA 29. Nov. 96
|*  Letzte Aenderung    MA 29. Nov. 96
|*
|*************************************************************************/

/*N*/ void lcl_MakeFlyPosition( SwFlyFrm *pFly )
/*N*/ {
/*N*/   if( pFly->IsFlyFreeFrm() )
/*N*/   {
/*N*/       ((SwFlyFreeFrm*)pFly)->SwFlyFreeFrm::MakeAll();
/*N*/       return;
/*N*/   }
/*N*/
/*?*/   BOOL bOldLock = pFly->IsLocked();
/*?*/   pFly->Lock();
/*?*/   SwFlyNotify aNotify( pFly );
/*?*/   pFly->MakeFlyPos();
/*?*/   if( !bOldLock )
/*?*/       pFly->Unlock();
/*N*/ }

void SwFrm::CalcFlys( BOOL bPosOnly )
{
    if ( GetDrawObjs() )
    {
        USHORT nCnt = GetDrawObjs()->Count();
        for ( USHORT i = 0; i < nCnt; ++i )
        {
            SdrObject *pO = (*GetDrawObjs())[i];
            if ( pO->IsWriterFlyFrame() )
            {
                SwFlyFrm *pFly = ((SwVirtFlyDrawObj*)pO)->GetFlyFrm();
                // Bei autopositionierten (am Zeichen geb.) Rahmen vertrauen wir
                // darauf, dass die Positionierung vom SwTxtFrm::Format vorgenommen
                // wird. Wenn wir sie dagegen hier kalkulieren wuerden, fuehrt es
                // zur Endlosschleife in Bug 50796.
                if ( pFly->IsFlyInCntFrm() )
                    continue;
                if( pFly->IsAutoPos() )
                {
                    if( bPosOnly )
                    {
                        pFly->_Invalidate();
                        pFly->_InvalidatePos();
                    }
                    continue;
                }
                pFly->_Invalidate();
                pFly->_InvalidatePos();

                if ( bPosOnly && pFly->GetValidSizeFlag() && pFly->GetValidPrtAreaFlag() )
                    ::lcl_MakeFlyPosition( pFly );
                else
                {
                    if ( !bPosOnly )
                        pFly->_InvalidateSize();
                    pFly->Calc();
                }
                if ( !GetDrawObjs() )
                    break;
                if ( GetDrawObjs()->Count() < nCnt )
                {
                    --i;
                    --nCnt;
                }
            }
            else
            {
                // assumption: <pO> is a drawing object.
                SwFrmFmt *pFrmFmt = ::FindFrmFmt( pO );
                if( !pFrmFmt ||
                    FLY_IN_CNTNT != pFrmFmt->GetAnchor().GetAnchorId() )
                {
                    // change anchor position
                    pO->SetAnchorPos( GetFrmAnchorPos( ::HasWrap( pO ) ) );
                    // OD 19.06.2003 #108784# - correct relative position of
                    // <SwDrawVirtObj>-objects to reference object.
                    if ( pO->ISA(SwDrawVirtObj) )
                    {
                        static_cast<SwDrawVirtObj*>(pO)->AdjustRelativePosToReference();
                    }
                    else
                    {
                        if ( GetValidPosFlag() )
                        {
                            SwPageFrm* pPage = FindPageFrm();
                            if ( pPage && ! pPage->IsInvalidLayout() )
                            {
                                // check if the new position
                                // would not exceed the margins of the page
                                CaptureDrawObj( *pO, pPage->Frm() );
                            }
                        }

                        ((SwDrawContact*)GetUserCall(pO))->ChkPage();

                        // OD 27.06.2003 #108784# - correct movement of 'virtual'
                        // drawing objects caused by the <SetAnchorPos(..)>
                        // of the 'master' drawing object.
                        SwDrawContact* pDrawContact =
                            static_cast<SwDrawContact*>(pO->GetUserCall());
                        if ( pDrawContact )
                        {
                            pDrawContact->CorrectRelativePosOfVirtObjs();
                        }
                    }
                }
            }
        }
    }
}


/*************************************************************************
|*
|*  SwLayoutFrm::NotifyFlys()
|*
|*  Ersterstellung      MA 18. Feb. 94
|*  Letzte Aenderung    MA 26. Jun. 96
|*
|*************************************************************************/

/*N*/ void SwLayoutFrm::NotifyFlys()
/*N*/ {
/*N*/   //Sorgt dafuer, dass untergeordnete Flys pruefen, ob sich sich an
/*N*/   //die Verhaeltnisse anpassen muessen.
/*N*/
/*N*/   //Wenn mehr Platz da ist muessen die Positionen und Sizes der
/*N*/   //Flys berechnet werden, denn es koennte sein, das sie kuenstlich
/*N*/   //geschrumpft/vershoben wurden und jetzt wieder naeher an ihre
/*N*/   //Sollwerte gehen duerfen.
/*N*/   //Ist weniger Platz da, so reicht es wenn sie in das MakeAll laufen
/*N*/   //der preiswerteste Weg dazu ist die Invalidierung der PrtArea.
/*N*/
/*N*/   SwPageFrm *pPage = FindPageFrm();
/*N*/   if ( pPage && pPage->GetSortedObjs() )
/*N*/   {
/*N*/       //Die Seite nur einmal antriggern.
/*N*/       FASTBOOL bPageInva = TRUE;
/*N*/
/*N*/       SwSortDrawObjs &rObjs = *pPage->GetSortedObjs();
/*N*/       const BOOL bHeadFoot = IsHeaderFrm() || IsFooterFrm();
/*N*/       for ( USHORT i = 0; i < rObjs.Count(); ++i )
/*N*/       {
/*N*/           SdrObject *pO = rObjs[i];
/*N*/           if ( pO->IsWriterFlyFrame() )
/*N*/           {
/*N*/               SwFlyFrm *pFly = ((SwVirtFlyDrawObj*)pO)->GetFlyFrm();
/*N*/
/*N*/               if ( pFly->Frm().Left() == WEIT_WECH )
/*N*/                   continue;
/*N*/
/*N*/               //Wenn der Fly nicht irgendwo ausserhalb liegt braucht er nur
/*N*/               //nur benachrichtigt werden, wenn er geclipped ist.
/*N*/               // Bei Header/Footer keine Abkuerzung, denn hier muesste die
/*N*/               // die PrtArea geprueft werden, die zu diesem Zeitpunkt
/*N*/               // (ShrinkFrm) noch nicht angepasst ist.
/*N*/                 if( ( !bHeadFoot && Frm().IsInside( pFly->Frm() )
/*N*/                       && !pFly->IsClipped() ) || pFly->IsAnLower( this ) )
/*N*/                   continue;
/*N*/
/*N*/               const BOOL bLow = pFly->IsLowerOf( this );
/*N*/               if ( bLow || pFly->GetAnchor()->FindPageFrm() != pPage )
/*N*/               {
/*N*/                   pFly->_Invalidate( pPage );
/*N*/                   if ( !bLow || pFly->IsFlyAtCntFrm() )
/*N*/                       pFly->_InvalidatePos();
/*N*/                   else
/*?*/                       pFly->_InvalidatePrt();
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|*  SwFlyFrm::NotifyDrawObj()
|*
|*  Ersterstellung      OK 22. Nov. 94
|*  Letzte Aenderung    MA 10. Jan. 97
|*
|*************************************************************************/

/*N*/ void SwFlyFrm::NotifyDrawObj()
/*N*/ {
/*N*/   pDrawObj->SetRect();
/*N*/   pDrawObj->_SetRectsDirty();
/*N*/   pDrawObj->SetChanged();
/*N*/   pDrawObj->SendRepaintBroadcast( TRUE ); //Broadcast ohne Repaint!
/*N*/   if ( GetFmt()->GetSurround().IsContour() )
/*?*/       ClrContourCache( pDrawObj );
/*N*/ }

/*************************************************************************
|*
|*  SwLayoutFrm::CalcRel()
|*
|*  Ersterstellung      MA 13. Jun. 96
|*  Letzte Aenderung    MA 10. Oct. 96
|*
|*************************************************************************/

/*N*/ Size SwFlyFrm::CalcRel( const SwFmtFrmSize &rSz ) const
/*N*/ {
/*N*/   Size aRet( rSz.GetSize() );
/*N*/
/*N*/   const SwFrm *pRel = IsFlyLayFrm() ? GetAnchor() : GetAnchor()->GetUpper();
/*N*/   if( pRel ) // LAYER_IMPL
/*N*/   {
/*N*/       long nRelWidth = LONG_MAX, nRelHeight = LONG_MAX;
/*N*/       const ViewShell *pSh = GetShell();
/*N*/       if ( ( pRel->IsBodyFrm() || pRel->IsPageFrm() ) &&
/*N*/            GetFmt()->GetDoc()->IsBrowseMode() &&
/*N*/            pSh && pSh->VisArea().HasArea() )
/*N*/       {
/*?*/           nRelWidth  = pSh->VisArea().Width();
/*?*/           nRelHeight = pSh->VisArea().Height();
/*?*/           const Size aBorder = pSh->GetOut()->PixelToLogic( pSh->GetBrowseBorder() );
/*?*/           nRelWidth -= 2*aBorder.Width();
/*?*/           long nDiff = nRelWidth - pRel->Prt().Width();
/*?*/           if ( nDiff > 0 )
/*?*/               nRelWidth -= nDiff;
/*?*/           nRelHeight -= 2*aBorder.Height();
/*?*/           nDiff = nRelHeight - pRel->Prt().Height();
/*?*/           if ( nDiff > 0 )
/*?*/               nRelHeight -= nDiff;
/*N*/       }
/*N*/       nRelWidth  = Min( nRelWidth,  pRel->Prt().Width() );
/*N*/       nRelHeight = Min( nRelHeight, pRel->Prt().Height() );
/*N*/         if( !pRel->IsPageFrm() )
/*N*/         {
/*N*/             const SwPageFrm* pPage = FindPageFrm();
/*N*/             if( pPage )
/*N*/             {
/*N*/                 nRelWidth  = Min( nRelWidth,  pPage->Prt().Width() );
/*N*/                 nRelHeight = Min( nRelHeight, pPage->Prt().Height() );
/*N*/             }
/*N*/         }
/*N*/
/*N*/       if ( rSz.GetWidthPercent() && rSz.GetWidthPercent() != 0xFF )
/*N*/           aRet.Width() = nRelWidth * rSz.GetWidthPercent() / 100;
/*N*/       if ( rSz.GetHeightPercent() && rSz.GetHeightPercent() != 0xFF )
/*N*/           aRet.Height() = nRelHeight * rSz.GetHeightPercent() / 100;
/*N*/
/*N*/       if ( rSz.GetWidthPercent() == 0xFF )
/*N*/       {
/*?*/           aRet.Width() *= aRet.Height();
/*?*/           aRet.Width() /= rSz.GetHeight();
/*N*/       }
/*N*/       else if ( rSz.GetHeightPercent() == 0xFF )
/*N*/       {
/*N*/           aRet.Height() *= aRet.Width();
/*N*/           aRet.Height() /= rSz.GetWidth();
/*N*/       }
/*N*/   }
/*N*/   return aRet;
/*N*/ }

/*************************************************************************
|*
|*  SwFlyFrm::AddSpacesToFrm
|*
|*  Ersterstellung      MA 11. Nov. 96
|*  Letzte Aenderung    MA 10. Mar. 97
|*
|*************************************************************************/

/*N*/ SwRect SwFlyFrm::AddSpacesToFrm() const
/*N*/ {
/*N*/   SwRect aRect( Frm() );
/*N*/   const SvxULSpaceItem &rUL = GetFmt()->GetULSpace();
/*N*/   const SvxLRSpaceItem &rLR = GetFmt()->GetLRSpace();
/*N*/   aRect.Left( Max( aRect.Left() - long(rLR.GetLeft()), 0L ) );
/*N*/   aRect.SSize().Width() += rLR.GetRight();
/*N*/   aRect.Top( Max( aRect.Top() - long(rUL.GetUpper()), 0L ) );
/*N*/   aRect.SSize().Height()+= rUL.GetLower();
/*N*/   return aRect;
/*N*/ }

/*************************************************************************
|*
|*  SwFlyFrm::GetContour()
|*
|*  Ersterstellung      MA 09. Jan. 97
|*  Letzte Aenderung    MA 10. Jan. 97
|*
|*************************************************************************/
/// OD 16.04.2003 #i13147# - If called for paint and the <SwNoTxtFrm> contains
/// a graphic, load of intrinsic graphic has to be avoided.
//STRIP001 BOOL SwFlyFrm::GetContour( PolyPolygon&   rContour,
//STRIP001                            const sal_Bool _bForPaint ) const
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001  if( GetFmt()->GetSurround().IsContour() && Lower() &&
//STRIP001      Lower()->IsNoTxtFrm() )
//STRIP001  {
//STRIP001      SwNoTxtNode *pNd = (SwNoTxtNode*)((SwCntntFrm*)Lower())->GetNode();
//STRIP001         // OD 16.04.2003 #i13147# - determine <GraphicObject> instead of <Graphic>
//STRIP001         // in order to avoid load of graphic, if <SwNoTxtNode> contains a graphic
//STRIP001         // node and method is called for paint.
//STRIP001         const GraphicObject* pGrfObj = NULL;
//STRIP001         sal_Bool bGrfObjCreated = sal_False;
//STRIP001         const SwGrfNode* pGrfNd = pNd->GetGrfNode();
//STRIP001         if ( pGrfNd && _bForPaint )
//STRIP001         {
//STRIP001             pGrfObj = &(pGrfNd->GetGrfObj());
//STRIP001         }
//STRIP001         else
//STRIP001         {
//STRIP001             pGrfObj = new GraphicObject( pNd->GetGraphic() );
//STRIP001             bGrfObjCreated = sal_True;
//STRIP001         }
//STRIP001         ASSERT( pGrfObj, "SwFlyFrm::GetContour() - No Graphic/GraphicObject found at <SwNoTxtNode>." );
//STRIP001         if ( pGrfObj && pGrfObj->GetType() != GRAPHIC_NONE )
//STRIP001         {
//STRIP001             if( !pNd->HasContour() )
//STRIP001             {
//STRIP001                 // OD 16.04.2003 #i13147# - no <CreateContour> for a graphic
//STRIP001                 // during paint. Thus, return (value of <bRet> should be <FALSE>).
//STRIP001                 if ( pGrfNd && _bForPaint )
//STRIP001                 {
//STRIP001                     ASSERT( false, "SwFlyFrm::GetContour() - No Contour found at <SwNoTxtNode> during paint." );
//STRIP001                     return bRet;
//STRIP001                 }
//STRIP001                 pNd->CreateContour();
//STRIP001             }
//STRIP001             pNd->GetContour( rContour );
//STRIP001          //Der Node haelt das Polygon passend zur Originalgroesse der Grafik
//STRIP001          //hier muss die Skalierung einkalkuliert werden.
//STRIP001          SwRect aClip;
//STRIP001          SwRect aOrig;
//STRIP001          Lower()->Calc();
//STRIP001          ((SwNoTxtFrm*)Lower())->GetGrfArea( aClip, &aOrig, FALSE );
//STRIP001             // OD 16.04.2003 #i13147# - copy method code <SvxContourDlg::ScaleContour(..)>
//STRIP001             // in order to avoid that graphic has to be loaded for contour scale.
//STRIP001             //SvxContourDlg::ScaleContour( rContour, aGrf, MAP_TWIP, aOrig.SSize() );
//STRIP001             {
//STRIP001                 OutputDevice*   pOutDev = Application::GetDefaultDevice();
//STRIP001                 const MapMode   aDispMap( MAP_TWIP );
//STRIP001                 const MapMode   aGrfMap( pGrfObj->GetPrefMapMode() );
//STRIP001                 const Size      aGrfSize( pGrfObj->GetPrefSize() );
//STRIP001                 double          fScaleX;
//STRIP001                 double          fScaleY;
//STRIP001                 Size            aOrgSize;
//STRIP001                 Point           aNewPoint;
//STRIP001                 BOOL            bPixelMap = aGrfMap.GetMapUnit() == MAP_PIXEL;
//STRIP001
//STRIP001                 if ( bPixelMap )
//STRIP001                     aOrgSize = pOutDev->PixelToLogic( aGrfSize, aDispMap );
//STRIP001                 else
//STRIP001                     aOrgSize = pOutDev->LogicToLogic( aGrfSize, aGrfMap, aDispMap );
//STRIP001
//STRIP001                 if ( aOrgSize.Width() && aOrgSize.Height() )
//STRIP001                 {
//STRIP001                     fScaleX = (double) aOrig.Width() / aOrgSize.Width();
//STRIP001                     fScaleY = (double) aOrig.Height() / aOrgSize.Height();
//STRIP001
//STRIP001                     for ( USHORT j = 0, nPolyCount = rContour.Count(); j < nPolyCount; j++ )
//STRIP001                     {
//STRIP001                         Polygon& rPoly = rContour[ j ];
//STRIP001
//STRIP001                         for ( USHORT i = 0, nCount = rPoly.GetSize(); i < nCount; i++ )
//STRIP001                         {
//STRIP001                             if ( bPixelMap )
//STRIP001                                 aNewPoint = pOutDev->PixelToLogic( rPoly[ i ], aDispMap  );
//STRIP001                             else
//STRIP001                                 aNewPoint = pOutDev->LogicToLogic( rPoly[ i ], aGrfMap, aDispMap  );
//STRIP001
//STRIP001                             rPoly[ i ] = Point( FRound( aNewPoint.X() * fScaleX ), FRound( aNewPoint.Y() * fScaleY ) );
//STRIP001                         }
//STRIP001                     }
//STRIP001                 }
//STRIP001             }
//STRIP001             // OD 17.04.2003 #i13147# - destroy created <GraphicObject>.
//STRIP001             if ( bGrfObjCreated )
//STRIP001             {
//STRIP001                 delete pGrfObj;
//STRIP001             }
//STRIP001             rContour.Move( aOrig.Left(), aOrig.Top() );
//STRIP001             if( !aClip.Width() )
//STRIP001                 aClip.Width( 1 );
//STRIP001             if( !aClip.Height() )
//STRIP001                 aClip.Height( 1 );
//STRIP001             rContour.Clip( aClip.SVRect() );
//STRIP001          bRet = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 BOOL SwFlyFrm::ConvertHoriTo40( SwHoriOrient &rHori, SwRelationOrient &rRel,
//STRIP001                              SwTwips &rPos ) const
//STRIP001 {
//STRIP001  ASSERT( rHori > PRTAREA, "ConvertHoriTo40: Why?" );
//STRIP001  if( !GetAnchor() )
//STRIP001      return FALSE;
//STRIP001  rHori = HORI_NONE;
//STRIP001  rRel = FRAME;
//STRIP001  rPos = Frm().Left() - GetAnchor()->Frm().Left();
//STRIP001  return TRUE;
//STRIP001 }


