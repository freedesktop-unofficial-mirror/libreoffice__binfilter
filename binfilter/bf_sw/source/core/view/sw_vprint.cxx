/*************************************************************************
 *
 *  $RCSfile: sw_vprint.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 15:44:37 $
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

#ifndef _SFX_PRINTER_HXX //autogen
#include <bf_sfx2/printer.hxx>
#endif
#ifndef _INTN_HXX //autogen
#include <tools/intn.hxx>
#endif
#ifndef _SFX_PROGRESS_HXX //autogen
#include <bf_sfx2/progress.hxx>
#endif
#ifndef _SFXAPP_HXX //autogen
#include <bf_sfx2/app.hxx>
#endif
#ifndef _SFX_PRNMON_HXX
#include <bf_sfx2/prnmon.hxx>
#endif
#ifndef _SVX_PAPERINF_HXX //autogen
#include <bf_svx/paperinf.hxx>
#endif
#ifndef _SVX_PBINITEM_HXX //autogen
#include <bf_svx/pbinitem.hxx>
#endif
#ifndef _SVDVIEW_HXX //autogen
#include <bf_svx/svdview.hxx>
#endif
#ifndef _EMBOBJ_HXX //autogen
#include <so3/embobj.hxx>
#endif
#ifndef _UNOTOOLS_LOCALEDATAWRAPPER_HXX
#include <unotools/localedatawrapper.hxx>
#endif

#ifndef _TXTFLD_HXX //autogen
#include <txtfld.hxx>
#endif
#ifndef _FMTFLD_HXX //autogen
#include <fmtfld.hxx>
#endif
#ifndef _FMTFSIZE_HXX //autogen
#include <fmtfsize.hxx>
#endif
#ifndef _FRMATR_HXX
#include <frmatr.hxx>
#endif
#ifndef _ROOTFRM_HXX
#include <rootfrm.hxx>
#endif
#ifndef _PAGEFRM_HXX
#include <pagefrm.hxx>
#endif
#ifndef _CNTFRM_HXX
#include <cntfrm.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _FESH_HXX
#include <fesh.hxx>
#endif
#ifndef _PAM_HXX
#include <pam.hxx>
#endif
#ifndef _VIEWIMP_HXX
#include <viewimp.hxx>      // Imp->SetFirstVisPageInvalid()
#endif
#ifndef _LAYACT_HXX
#include <layact.hxx>
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>
#endif
#ifndef _FLDBAS_HXX
#include <fldbas.hxx>
#endif
#ifndef _DOCUFLD_HXX
#include <docufld.hxx>      // PostItFld /-Type
#endif
#ifndef _DOCFLD_HXX
#include <docfld.hxx>       // _SetGetExpFld
#endif
#ifndef _CALBCK_HXX
#include <calbck.hxx>       // SwModify/SwClientIter
#endif
#ifndef _SHELLRES_HXX
#include <shellres.hxx>
#endif
#ifndef _VIEWOPT_HXX
#include <viewopt.hxx>
#endif
#ifndef _SWPRTOPT_HXX
#include <swprtopt.hxx>     // SwPrtOptions
#endif
#ifndef _PAGEDESC_HXX
#include <pagedesc.hxx>
#endif
#ifndef _POOLFMT_HXX
#include <poolfmt.hxx>      // fuer RES_POOLPAGE_JAKET
#endif
#ifndef _MDIEXP_HXX
#include <mdiexp.hxx>       // Ansteuern der Statusleiste
#endif
#ifndef _STATSTR_HRC
#include <statstr.hrc>      //      -- " --
#endif
#ifndef _PTQUEUE_HXX
#include <ptqueue.hxx>
#endif
#ifndef _HINTS_HXX
#include <hints.hxx>
#endif
#ifndef _TABFRM_HXX
#include <tabfrm.hxx>
#endif
#ifndef _TXTFRM_HXX
#include <txtfrm.hxx>       // MinPrtLine
#endif
#ifndef _VISCRS_HXX
#include <viscrs.hxx>       // SwShellCrsr
#endif
#ifndef _FMTPDSC_HXX
#include <fmtpdsc.hxx>      // SwFmtPageDesc
#endif

#define JOBSET_ERR_DEFAULT          0
#define JOBSET_ERR_ERROR            1
#define JOBSET_ERR_ISSTARTET        2

//--------------------------------------------------------------------
//Klasse zum Puffern von Paints
class SwQueuedPaint
{
public:
    SwQueuedPaint *pNext;
    ViewShell      *pSh;
    SwRect          aRect;

    SwQueuedPaint( ViewShell *pNew, const SwRect &rRect ) :
        pNext( 0 ),
        pSh( pNew ),
        aRect( rRect )
    {}
};

SwQueuedPaint *SwPaintQueue::pQueue = 0;

//Klasse zum Speichern einiger Druckereinstellungen
//STRIP001 class SwPrtOptSave
//STRIP001 {
//STRIP001  Printer *pPrt;
//STRIP001  Size aSize;
//STRIP001  Paper ePaper;
//STRIP001  Orientation eOrientation;
//STRIP001  USHORT nPaperBin;
//STRIP001 public:
//STRIP001  SwPrtOptSave( Printer *pPrinter );
//STRIP001  ~SwPrtOptSave();
//STRIP001 };

// saves some settings from the draw view
//STRIP001 class SwDrawViewSave
//STRIP001 {
//STRIP001     String sLayerNm;
//STRIP001     SdrView* pDV;
//STRIP001     sal_Bool bPrintDraft;
//STRIP001     sal_Bool bPrintControls;
//STRIP001 public:
//STRIP001     SwDrawViewSave( SdrView* pSdrView );
//STRIP001     ~SwDrawViewSave();
//STRIP001 };


//STRIP001 void SwPaintQueue::Add( ViewShell *pNew, const SwRect &rNew )
//STRIP001 {
//STRIP001  SwQueuedPaint *pPt;
//STRIP001  if ( 0 != (pPt = pQueue) )
//STRIP001  {
//STRIP001      while ( pPt->pSh != pNew && pPt->pNext )
//STRIP001          pPt = pPt->pNext;
//STRIP001      if ( pPt->pSh == pNew )
//STRIP001      {
//STRIP001          pPt->aRect.Union( rNew );
//STRIP001          return;
//STRIP001      }
//STRIP001  }
//STRIP001  SwQueuedPaint *pNQ = new SwQueuedPaint( pNew, rNew );
//STRIP001  if ( pPt )
//STRIP001      pPt->pNext = pNQ;
//STRIP001  else
//STRIP001      pQueue = pNQ;
//STRIP001 }



//STRIP001 void SwPaintQueue::Repaint()
//STRIP001 {
//STRIP001  if ( !SwRootFrm::IsInPaint() && pQueue )
//STRIP001  {
//STRIP001      SwQueuedPaint *pPt = pQueue;
//STRIP001      do
//STRIP001      {   ViewShell *pSh = pPt->pSh;
//STRIP001          SET_CURR_SHELL( pSh );
//STRIP001          if ( pSh->IsPreView() )
//STRIP001          {
//STRIP001              if ( pSh->GetWin() )
//STRIP001              {
//STRIP001                  //Fuer PreView aussenherum, weil im PaintHdl (UI) die
//STRIP001                  //Zeilen/Spalten bekannt sind.
//STRIP001                  pSh->GetWin()->Invalidate();
//STRIP001                  pSh->GetWin()->Update();
//STRIP001              }
//STRIP001          }
//STRIP001          else
//STRIP001              pSh->Paint( pPt->aRect.SVRect() );
//STRIP001          pPt = pPt->pNext;
//STRIP001      } while ( pPt );
//STRIP001
//STRIP001      do
//STRIP001      {   pPt = pQueue;
//STRIP001          pQueue = pQueue->pNext;
//STRIP001          delete pPt;
//STRIP001      } while ( pQueue );
//STRIP001  }
//STRIP001 }



/*N*/ void SwPaintQueue::Remove( ViewShell *pSh )
/*N*/ {
/*N*/   SwQueuedPaint *pPt;
/*N*/   if ( 0 != (pPt = pQueue) )
/*N*/   {
/*?*/       SwQueuedPaint *pPrev = 0;
/*?*/       while ( pPt && pPt->pSh != pSh )
/*?*/       {
/*?*/           pPrev = pPt;
/*?*/           pPt = pPt->pNext;
/*?*/       }
/*?*/       if ( pPt )
/*?*/       {
/*?*/           if ( pPrev )
/*?*/               pPrev->pNext = pPt->pNext;
/*?*/           else if ( pPt == pQueue )
/*?*/               pQueue = 0;
/*?*/           delete pPt;
/*?*/       }
/*N*/   }
/*N*/ }


//STRIP001 const XubString& SwPrtOptions::MakeNextJobName()
//STRIP001 {
//STRIP001  static char __READONLY_DATA sDelim[] = " - ";
//STRIP001  USHORT nDelim = sJobName.SearchAscii( sDelim );
//STRIP001  if( STRING_NOTFOUND == nDelim )
//STRIP001      sJobName.AppendAscii(sDelim);
//STRIP001  else
//STRIP001      sJobName.Erase( nDelim + 3/*Zeichen!*/ );
//STRIP001
//STRIP001  return sJobName += XubString::CreateFromInt32( ++nJobNo );
//STRIP001 }

/******************************************************************************
 *  Methode     :   void SetSwVisArea( ViewShell *pSh, Point aPrtOffset, ...
 *  Beschreibung:
 *  Erstellt    :   OK 04.11.94 16:27
 *  Aenderung   :
 ******************************************************************************/

//STRIP001 void SetSwVisArea( ViewShell *pSh, const SwRect &rRect, BOOL bPDFExport )
//STRIP001 {
//STRIP001  ASSERT( !pSh->GetWin(), "Drucken mit Window?" );
//STRIP001  pSh->aVisArea = rRect;
//STRIP001  pSh->Imp()->SetFirstVisPageInvalid();
//STRIP001  Point aPt( rRect.Pos() );
//STRIP001
//STRIP001     if (!bPDFExport)
//STRIP001         aPt += pSh->aPrtOffst;
//STRIP001  aPt.X() = -aPt.X(); aPt.Y() = -aPt.Y();
//STRIP001
//STRIP001     OutputDevice *pOut = bPDFExport ? pSh->GetOut() : pSh->GetPrt();
//STRIP001     MapMode aMapMode( pOut->GetMapMode() );
//STRIP001  aMapMode.SetOrigin( aPt );
//STRIP001     pOut->SetMapMode( aMapMode );
//STRIP001 }

/******************************************************************************
 *  Methode     :   struct _PostItFld : public _SetGetExpFld
 *  Beschreibung:   Update an das PostItFeld
 *  Erstellt    :   OK 07.11.94 10:18
 *  Aenderung   :
 ******************************************************************************/
//STRIP001 struct _PostItFld : public _SetGetExpFld
//STRIP001 {
//STRIP001  _PostItFld( const SwNodeIndex& rNdIdx, const SwTxtFld* pFld,
//STRIP001                  const SwIndex* pIdx = 0 )
//STRIP001      : _SetGetExpFld( rNdIdx, pFld, pIdx ) {}
//STRIP001
//STRIP001  USHORT GetPageNo( MultiSelection &rMulti, BOOL bRgt, BOOL bLft,
//STRIP001                      USHORT& rVirtPgNo, USHORT& rLineNo );
//STRIP001  SwPostItField* GetPostIt() const
//STRIP001      { return (SwPostItField*) GetFld()->GetFld().GetFld(); }
//STRIP001 };



//STRIP001 USHORT _PostItFld::GetPageNo( MultiSelection &rMulti, BOOL bRgt, BOOL bLft,
//STRIP001                              USHORT& rVirtPgNo, USHORT& rLineNo )
//STRIP001 {
//STRIP001  //Problem: Wenn ein PostItFld in einem Node steht, der von mehr als
//STRIP001  //einer Layout-Instanz repraesentiert wird, steht die Frage im Raum,
//STRIP001  //ob das PostIt nur ein- oder n-mal gedruck werden soll.
//STRIP001  //Wahrscheinlich nur einmal, als Seitennummer soll hier keine Zufaellige
//STRIP001  //sondern die des ersten Auftretens des PostIts innerhalb des selektierten
//STRIP001  //Bereichs ermittelt werden.
//STRIP001  rVirtPgNo = 0;
//STRIP001  USHORT nPos = GetCntnt();
//STRIP001  SwClientIter aIter( (SwModify &)GetFld()->GetTxtNode() );
//STRIP001  for( SwTxtFrm* pFrm = (SwTxtFrm*)aIter.First( TYPE( SwFrm ));
//STRIP001          pFrm;  pFrm = (SwTxtFrm*)aIter.Next() )
//STRIP001  {
//STRIP001      if( pFrm->GetOfst() > nPos ||
//STRIP001          pFrm->HasFollow() && pFrm->GetFollow()->GetOfst() <= nPos )
//STRIP001          continue;
//STRIP001      USHORT nPgNo = pFrm->GetPhyPageNum();
//STRIP001      BOOL bRight = pFrm->OnRightPage();
//STRIP001      if( rMulti.IsSelected( nPgNo ) &&
//STRIP001          ( (bRight && bRgt) || (!bRight && bLft) ) )
//STRIP001      {
//STRIP001          rLineNo = (USHORT)(pFrm->GetLineCount( nPos ) +
//STRIP001                    pFrm->GetAllLines() - pFrm->GetThisLines());
//STRIP001          rVirtPgNo = pFrm->GetVirtPageNum();
//STRIP001          return nPgNo;
//STRIP001      }
//STRIP001  }
//STRIP001  return 0;
//STRIP001 }

/******************************************************************************
 *  Methode     :   void lcl_GetPostIts( SwDoc* pDoc, _SetGetExpFlds& ...
 *  Beschreibung:
 *  Erstellt    :   OK 07.11.94 10:20
 *  Aenderung   :
 ******************************************************************************/


//STRIP001 void lcl_GetPostIts( SwDoc* pDoc, _SetGetExpFlds& rSrtLst )
//STRIP001 {
//STRIP001  SwFieldType* pFldType = pDoc->GetSysFldType( RES_POSTITFLD );
//STRIP001  ASSERT( pFldType, "kein PostItType ? ");
//STRIP001
//STRIP001  if( pFldType->GetDepends() )
//STRIP001  {
//STRIP001      // Modify-Object gefunden, trage alle Felder ins Array ein
//STRIP001      SwClientIter aIter( *pFldType );
//STRIP001      SwClient* pLast;
//STRIP001      const SwTxtFld* pTxtFld;
//STRIP001
//STRIP001      for( pLast = aIter.First( TYPE(SwFmtFld)); pLast; pLast = aIter.Next() )
//STRIP001          if( 0 != ( pTxtFld = ((SwFmtFld*)pLast)->GetTxtFld() ) &&
//STRIP001              pTxtFld->GetTxtNode().GetNodes().IsDocNodes() )
//STRIP001          {
//STRIP001              SwNodeIndex aIdx( pTxtFld->GetTxtNode() );
//STRIP001              _PostItFld* pNew = new _PostItFld( aIdx, pTxtFld );
//STRIP001              rSrtLst.Insert( pNew );
//STRIP001          }
//STRIP001  }
//STRIP001 }

/******************************************************************************
 *  Methode     :   void lcl_FormatPostIt( SwDoc* pDoc, SwPaM& aPam, ...
 *  Beschreibung:
 *  Erstellt    :   OK 07.11.94 10:20
 *  Aenderung   :
 ******************************************************************************/


//STRIP001 void lcl_FormatPostIt( SwDoc* pDoc, SwPaM& aPam, SwPostItField* pField,
//STRIP001                         USHORT nPageNo, USHORT nLineNo )
//STRIP001 {
//STRIP001  static char __READONLY_DATA sTmp[] = " : ";
//STRIP001
//STRIP001  ASSERT( ViewShell::GetShellRes(), "missing ShellRes" );
//STRIP001
//STRIP001  String aStr(    ViewShell::GetShellRes()->aPostItPage   );
//STRIP001  aStr.AppendAscii(sTmp);
//STRIP001
//STRIP001  aStr += XubString::CreateFromInt32( nPageNo );
//STRIP001  aStr += ' ';
//STRIP001  if( nLineNo )
//STRIP001  {
//STRIP001      aStr += ViewShell::GetShellRes()->aPostItLine;
//STRIP001      aStr.AppendAscii(sTmp);
//STRIP001      aStr += XubString::CreateFromInt32( nLineNo );
//STRIP001      aStr += ' ';
//STRIP001  }
//STRIP001  aStr += ViewShell::GetShellRes()->aPostItAuthor;
//STRIP001  aStr.AppendAscii(sTmp);
//STRIP001  aStr += pField->GetPar1();
//STRIP001  aStr += ' ';
//STRIP001  aStr += GetAppLocaleData().getDate( pField->GetDate() );
//STRIP001  pDoc->Insert( aPam, aStr );
//STRIP001
//STRIP001  pDoc->SplitNode( *aPam.GetPoint() );
//STRIP001  aStr = pField->GetPar2();
//STRIP001 #ifdef MAC
//STRIP001  // Fuer den MAC alle CR durch LF ersetzen
//STRIP001  for( USHORT n = 0; n < aStr.Len(); ++n )
//STRIP001      if( aStr[n] == '\r' )
//STRIP001          aStr[n] = '\n';
//STRIP001 #endif
//STRIP001 #if defined( WIN ) || defined( WNT ) || defined( PM2 )
//STRIP001  // Bei Windows und Co alle CR rausschmeissen
//STRIP001  aStr.EraseAllChars( '\r' );
//STRIP001 #endif
//STRIP001  pDoc->Insert( aPam, aStr );
//STRIP001  pDoc->SplitNode( *aPam.GetPoint() );
//STRIP001  pDoc->SplitNode( *aPam.GetPoint() );
//STRIP001 }

/******************************************************************************
 *  Methode     :   void lcl_PrintPostIts( ViewShell* pPrtShell )
 *  Beschreibung:
 *  Erstellt    :   OK 07.11.94 10:21
 *  Aenderung   :   MA 10. May. 95
 ******************************************************************************/


//STRIP001 void lcl_PrintPostIts( ViewShell* pPrtShell, const XubString& rJobName,
//STRIP001                      BOOL& rStartJob, int& rJobStartError, BOOL bReverse)
//STRIP001 {
//STRIP001  // Formatieren und Ausdrucken
//STRIP001  pPrtShell->CalcLayout();
//STRIP001
//STRIP001  SfxPrinter* pPrn = pPrtShell->GetPrt();
//STRIP001
//STRIP001  //Das Druckdokument ist ein default Dokument, mithin arbeitet es auf der
//STRIP001  //StandardSeite.
//STRIP001  SwFrm *pPage = pPrtShell->GetLayout()->Lower();
//STRIP001
//STRIP001  SwPrtOptSave aPrtSave( pPrn );
//STRIP001
//STRIP001  pPrn->SetOrientation( ORIENTATION_PORTRAIT );
//STRIP001  pPrn->SetPaperBin( pPage->GetAttrSet()->GetPaperBin().GetValue() );
//STRIP001
//STRIP001  if( !rStartJob &&  JOBSET_ERR_DEFAULT == rJobStartError &&
//STRIP001      rJobName.Len() )
//STRIP001  {
//STRIP001      if( !pPrn->IsJobActive() )
//STRIP001      {
//STRIP001          rStartJob = pPrn->StartJob( rJobName );
//STRIP001          if( !rStartJob )
//STRIP001          {
//STRIP001              rJobStartError = JOBSET_ERR_ERROR;
//STRIP001              return;
//STRIP001          }
//STRIP001      }
//STRIP001      pPrtShell->InitPrt( pPrn );
//STRIP001      rJobStartError = JOBSET_ERR_ISSTARTET;
//STRIP001  }
//STRIP001
//STRIP001  // Wir koennen auch rueckwaerts:
//STRIP001  if ( bReverse )
//STRIP001      pPage = pPrtShell->GetLayout()->GetLastPage();
//STRIP001
//STRIP001  while( pPage )
//STRIP001  {
//STRIP001      //Mag der Anwender noch?, Abbruch erst in Prt()
//STRIP001      GetpApp()->Reschedule();
//STRIP001      ::SetSwVisArea( pPrtShell, pPage->Frm() );
//STRIP001      pPrn->StartPage();
//STRIP001      pPage->GetUpper()->Paint( pPage->Frm() );
//STRIP001 //       SFX_APP()->SpoilDemoOutput( *pPrtShell->GetOut(), pPage->Frm().SVRect());
//STRIP001      SwPaintQueue::Repaint();
//STRIP001      pPrn->EndPage();
//STRIP001      pPage = bReverse ? pPage->GetPrev() : pPage->GetNext();
//STRIP001  }
//STRIP001 }

/******************************************************************************
 *  Methode     :   void lcl_PrintPostItsEndDoc( ViewShell* pPrtShell, ...
 *  Beschreibung:
 *  Erstellt    :   OK 07.11.94 10:21
 *  Aenderung   :   MA 10. May. 95
 ******************************************************************************/


//STRIP001 void lcl_PrintPostItsEndDoc( ViewShell* pPrtShell,
//STRIP001          _SetGetExpFlds& rPostItFields, MultiSelection &rMulti,
//STRIP001          const XubString& rJobName, BOOL& rStartJob, int& rJobStartError,
//STRIP001          BOOL bRgt, BOOL bLft, BOOL bRev )
//STRIP001 {
//STRIP001  USHORT nPostIts = rPostItFields.Count();
//STRIP001  if( !nPostIts )
//STRIP001      // Keine Arbeit
//STRIP001      return;
//STRIP001
//STRIP001  SET_CURR_SHELL( pPrtShell );
//STRIP001
//STRIP001  SwDoc* pPrtDoc = pPrtShell->GetDoc();
//STRIP001
//STRIP001  // Dokument leeren und ans Dokumentende gehen
//STRIP001  SwPaM aPam( pPrtDoc->GetNodes().GetEndOfContent() );
//STRIP001  aPam.Move( fnMoveBackward, fnGoDoc );
//STRIP001  aPam.SetMark();
//STRIP001  aPam.Move( fnMoveForward, fnGoDoc );
//STRIP001  pPrtDoc->Delete( aPam );
//STRIP001
//STRIP001  for( USHORT i = 0, nVirtPg, nLineNo; i < nPostIts; ++i )
//STRIP001  {
//STRIP001      _PostItFld& rPostIt = (_PostItFld&)*rPostItFields[ i ];
//STRIP001      if( rPostIt.GetPageNo( rMulti, bRgt, bLft, nVirtPg, nLineNo ) )
//STRIP001          lcl_FormatPostIt( pPrtShell->GetDoc(), aPam,
//STRIP001                         rPostIt.GetPostIt(), nVirtPg, nLineNo );
//STRIP001  }
//STRIP001
//STRIP001  lcl_PrintPostIts( pPrtShell, rJobName, rStartJob, rJobStartError, bRev );
//STRIP001 }

/******************************************************************************
 *  Methode     :   void lcl_PrintPostItsEndPage( ViewShell* pPrtShell, ...
 *  Beschreibung:
 *  Erstellt    :   OK 07.11.94 10:22
 *  Aenderung   :
 ******************************************************************************/


//STRIP001 void lcl_PrintPostItsEndPage( ViewShell* pPrtShell,
//STRIP001          _SetGetExpFlds& rPostItFields, USHORT nPageNo, MultiSelection &rMulti,
//STRIP001          const XubString& rJobName, BOOL& rStartJob, int& rJobStartError,
//STRIP001          BOOL bRgt, BOOL bLft, BOOL bRev )
//STRIP001 {
//STRIP001  USHORT nPostIts = rPostItFields.Count();
//STRIP001  if( !nPostIts )
//STRIP001      // Keine Arbeit
//STRIP001      return;
//STRIP001
//STRIP001  SET_CURR_SHELL( pPrtShell );
//STRIP001
//STRIP001  USHORT i = 0, nVirtPg, nLineNo;
//STRIP001  while( ( i < nPostIts ) &&
//STRIP001         ( nPageNo != ((_PostItFld&)*rPostItFields[ i ]).
//STRIP001                              GetPageNo( rMulti,bRgt, bLft, nVirtPg, nLineNo )))
//STRIP001      ++i;
//STRIP001  if(i == nPostIts)
//STRIP001      // Nix zu drucken
//STRIP001      return;
//STRIP001
//STRIP001  SwDoc* pPrtDoc = pPrtShell->GetDoc();
//STRIP001
//STRIP001  // Dokument leeren und ans Dokumentende gehen
//STRIP001  SwPaM aPam( pPrtDoc->GetNodes().GetEndOfContent() );
//STRIP001  aPam.Move( fnMoveBackward, fnGoDoc );
//STRIP001  aPam.SetMark();
//STRIP001  aPam.Move( fnMoveForward, fnGoDoc );
//STRIP001  pPrtDoc->Delete( aPam );
//STRIP001
//STRIP001  while( i < nPostIts )
//STRIP001  {
//STRIP001      _PostItFld& rPostIt = (_PostItFld&)*rPostItFields[ i ];
//STRIP001      if( nPageNo == rPostIt.GetPageNo( rMulti, bRgt, bLft, nVirtPg, nLineNo ) )
//STRIP001          lcl_FormatPostIt( pPrtShell->GetDoc(), aPam,
//STRIP001                              rPostIt.GetPostIt(), nVirtPg, nLineNo );
//STRIP001      ++i;
//STRIP001  }
//STRIP001  lcl_PrintPostIts( pPrtShell, rJobName, rStartJob, rJobStartError, bRev );
//STRIP001 }

/******************************************************************************
 *  Methode     :   void ViewShell::SetPrt( SfxPrinter *pNew, OutputDevice *pPDFOut )
 *  Beschreibung:
 *  Erstellt    :   OK 07.11.94 10:22
 *  Aenderung   :
 ******************************************************************************/

/*M*/ void ViewShell::InitPrt( SfxPrinter *pPrt, OutputDevice *pPDFOut )
/*M*/ {
/*M*/   //Fuer den Printer merken wir uns einen negativen Offset, der
/*M*/   //genau dem Offset de OutputSize entspricht. Das ist notwendig,
/*M*/   //weil unser Ursprung der linken ober Ecke der physikalischen
/*M*/   //Seite ist, die Ausgaben (SV) aber den Outputoffset als Urstprung
/*M*/   //betrachten.
/*M*/     OutputDevice *pTmpDev = pPDFOut ? pPDFOut : (OutputDevice *) pPrt;
/*M*/     if ( pTmpDev )
/*M*/   {
/*M*/         aPrtOffst = pPrt ? pPrt->GetPageOffset() : Point();
/*M*/
/*M*/         aPrtOffst += pTmpDev->GetMapMode().GetOrigin();
/*M*/         MapMode aMapMode( pTmpDev->GetMapMode() );
/*M*/       aMapMode.SetMapUnit( MAP_TWIP );
/*M*/         pTmpDev->SetMapMode( aMapMode );
/*M*/         pTmpDev->SetLineColor();
/*M*/         pTmpDev->SetFillColor();
/*M*/   }
/*M*/   else
/*M*/       aPrtOffst.X() = aPrtOffst.Y() = 0;
/*M*/
/*M*/   if ( !pWin )
/*M*/         pOut = pTmpDev;    //Oder was sonst?
/*M*/ }

//STRIP001 void ViewShell::SetPrt( SfxPrinter *pNew )
//STRIP001 {
//STRIP001     // If the reference device was the printer,
//STRIP001     // we have to set the new reference device
//STRIP001     GetDoc()->SetPrt( pNew, sal_True );
//STRIP001 }

/******************************************************************************
 *  Methode     :   void ViewShell::ChgAllPageOrientation
 *  Erstellt    :   MA 08. Aug. 95
 *  Aenderung   :
 ******************************************************************************/


//STRIP001 void ViewShell::ChgAllPageOrientation( USHORT eOri )
//STRIP001 {
//STRIP001  ASSERT( nStartAction, "missing an Action" );
//STRIP001  SET_CURR_SHELL( this );
//STRIP001
//STRIP001  USHORT nAll = GetDoc()->GetPageDescCnt();
//STRIP001  BOOL bNewOri = Orientation(eOri) == ORIENTATION_PORTRAIT ? FALSE : TRUE;
//STRIP001
//STRIP001  for( USHORT i = 0; i < nAll; ++ i )
//STRIP001  {
//STRIP001      const SwPageDesc& rOld = GetDoc()->GetPageDesc( i );
//STRIP001      if( rOld.GetLandscape() != bNewOri )
//STRIP001      {
//STRIP001          SwPageDesc aNew( rOld );
//STRIP001          aNew.SetLandscape( bNewOri );
//STRIP001          SwFrmFmt& rFmt = aNew.GetMaster();
//STRIP001          SwFmtFrmSize aSz( rFmt.GetFrmSize() );
//STRIP001          // Groesse anpassen.
//STRIP001          // PORTRAIT  -> Hoeher als Breit
//STRIP001          // LANDSCAPE -> Breiter als Hoch
//STRIP001          // Hoehe ist die VarSize, Breite ist die FixSize (per Def.)
//STRIP001          if( bNewOri ? aSz.GetHeight() > aSz.GetWidth()
//STRIP001                      : aSz.GetHeight() < aSz.GetWidth() )
//STRIP001          {
//STRIP001              SwTwips aTmp = aSz.GetHeight();
//STRIP001              aSz.SetHeight( aSz.GetWidth() );
//STRIP001              aSz.SetWidth( aTmp );
//STRIP001              rFmt.SetAttr( aSz );
//STRIP001          }
//STRIP001          GetDoc()->ChgPageDesc( i, aNew );
//STRIP001      }
//STRIP001  }
//STRIP001 }

/******************************************************************************
 *  Methode     :   void ViewShell::ChgAllPageOrientation
 *  Erstellt    :   MA 08. Aug. 95
 *  Aenderung   :
 ******************************************************************************/


//STRIP001 void ViewShell::ChgAllPageSize( Size &rSz )
//STRIP001 {
//STRIP001  ASSERT( nStartAction, "missing an Action" );
//STRIP001  SET_CURR_SHELL( this );
//STRIP001
//STRIP001  SwDoc* pDoc = GetDoc();
//STRIP001  USHORT nAll = pDoc->GetPageDescCnt();
//STRIP001
//STRIP001  for( USHORT i = 0; i < nAll; ++i )
//STRIP001  {
//STRIP001      // Fuer WIN95 als Pointer anlegen! (falsche Optimierung!!)
//STRIP001      SwPageDesc* pNew = new SwPageDesc( pDoc->GetPageDesc( i ) );
//STRIP001      SwFrmFmt& rPgFmt = pNew->GetMaster();
//STRIP001      Size aSz( rSz );
//STRIP001      const BOOL bOri = pNew->GetLandscape();
//STRIP001      if( bOri  ? aSz.Height() > aSz.Width()
//STRIP001                : aSz.Height() < aSz.Width() )
//STRIP001      {
//STRIP001          SwTwips aTmp = aSz.Height();
//STRIP001          aSz.Height() = aSz.Width();
//STRIP001          aSz.Width()  = aTmp;
//STRIP001      }
//STRIP001
//STRIP001      SwFmtFrmSize aFrmSz( rPgFmt.GetFrmSize() );
//STRIP001      aFrmSz.SetSize( aSz );
//STRIP001      rPgFmt.SetAttr( aFrmSz );
//STRIP001      pDoc->ChgPageDesc( i, *pNew );
//STRIP001      delete pNew;
//STRIP001  }
//STRIP001 }

/******************************************************************************
 *  Methode     :   void ViewShell::CalcPagesForPrint( short nMax, BOOL ...
 *  Beschreibung:
 *  Erstellt    :   OK 04.11.94 15:33
 *  Aenderung   :   MA 07. Jun. 95
 ******************************************************************************/



//STRIP001 void lcl_SetState( SfxProgress& rProgress, ULONG nPage, ULONG nMax,
//STRIP001  const XubString *pStr, ULONG nAct, ULONG nCnt, ULONG nOffs, ULONG nPageNo )
//STRIP001 {
//STRIP001  XubString aTmp = XubString::CreateFromInt64( nPageNo );
//STRIP001  if( pStr )
//STRIP001  {
//STRIP001      aTmp += ' ';
//STRIP001      aTmp += *pStr;
//STRIP001      if( nCnt )
//STRIP001      {
//STRIP001          nMax *= 2;
//STRIP001          rProgress.SetStateText( (nAct-1)*nMax+nPage+nOffs,
//STRIP001                                      aTmp, nCnt*nMax );
//STRIP001      }
//STRIP001      else
//STRIP001          rProgress.SetStateText( nPage, aTmp, nMax );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      aTmp += ' '; aTmp += '('; aTmp += XubString::CreateFromInt64( nPage );
//STRIP001      aTmp += '/'; aTmp += XubString::CreateFromInt64( nMax ); aTmp += ')';
//STRIP001      rProgress.SetStateText( nPage, aTmp, nMax );
//STRIP001  }
//STRIP001 }



//STRIP001 void ViewShell::CalcPagesForPrint( USHORT nMax, SfxProgress* pProgress,
//STRIP001  const XubString* pStr, ULONG nMergeAct, ULONG nMergeCnt )
//STRIP001 {
//STRIP001  SET_CURR_SHELL( this );
//STRIP001
//STRIP001  //Seitenweise durchformatieren, by the way kann die Statusleiste
//STRIP001  //angetriggert werden, damit der Anwender sieht worauf er wartet.
//STRIP001  //Damit der Vorgang moeglichst transparent gestaltet werden kann
//STRIP001  //Versuchen wir mal eine Schaetzung.
//STRIP001  SfxPrinter* pPrt = GetPrt();
//STRIP001  BOOL bPrtJob = pPrt ? pPrt->IsJobActive() : FALSE;
//STRIP001  SwRootFrm* pLayout = GetLayout();
//STRIP001  ULONG nStatMax = pLayout->GetPageNum();
//STRIP001
//STRIP001  const SwFrm *pPage = pLayout->Lower();
//STRIP001  SwLayAction aAction( pLayout, Imp() );
//STRIP001
//STRIP001  if( pProgress )
//STRIP001  {
//STRIP001      // HACK, damit die Anzeige sich nicht verschluckt.
//STRIP001      const XubString aTmp( SW_RES( STR_STATSTR_PRINT ) );
//STRIP001      pProgress->SetText( aTmp );
//STRIP001      lcl_SetState( *pProgress, 1, nStatMax, pStr, nMergeAct, nMergeCnt, 0,
//STRIP001                    1 );
//STRIP001      pProgress->Reschedule(); //Mag der Anwender noch oder hat er genug?
//STRIP001
//STRIP001      aAction.SetProgress(pProgress);
//STRIP001  }
//STRIP001
//STRIP001  pLayout->StartAllAction();
//STRIP001  for ( USHORT i = 1; pPage && i <= nMax; pPage = pPage->GetNext(), ++i )
//STRIP001  {
//STRIP001      if ( (bPrtJob && !pPrt->IsJobActive()) || Imp()->IsStopPrt())
//STRIP001          break;
//STRIP001
//STRIP001
//STRIP001      if( pProgress )
//STRIP001      {
//STRIP001          //HACK, damit die Anzeige sich nicht verschluckt.
//STRIP001          if ( i > nStatMax )
//STRIP001              nStatMax = i;
//STRIP001          lcl_SetState( *pProgress, i, nStatMax, pStr, nMergeAct, nMergeCnt, 0, i );
//STRIP001          pProgress->Reschedule(); //Mag der Anwender noch oder hat er genug?
//STRIP001      }
//STRIP001
//STRIP001      if ( bPrtJob && !pPrt->IsJobActive() ||
//STRIP001           Imp()->IsStopPrt())
//STRIP001          break;
//STRIP001      pPage->Calc();
//STRIP001      SwRect aOldVis( VisArea() );
//STRIP001      aVisArea = pPage->Frm();
//STRIP001      Imp()->SetFirstVisPageInvalid();
//STRIP001      aAction.Reset();
//STRIP001      aAction.SetPaint( FALSE );
//STRIP001      aAction.SetWaitAllowed( FALSE );
//STRIP001      aAction.SetReschedule( TRUE );
//STRIP001
//STRIP001      aAction.Action();
//STRIP001
//STRIP001      aVisArea = aOldVis;             //Zuruecksetzen wg. der Paints!
//STRIP001      Imp()->SetFirstVisPageInvalid();
//STRIP001      SwPaintQueue::Repaint();
//STRIP001  }
//STRIP001  if (pProgress)
//STRIP001  {
//STRIP001      aAction.SetProgress(NULL);
//STRIP001  }
//STRIP001
//STRIP001  pLayout->EndAllAction();
//STRIP001 }

/******************************************************************************/

//STRIP001 SwDoc * ViewShell::CreatePrtDoc( SfxPrinter* pPrt, SvEmbeddedObjectRef &rDocShellRef)
//STRIP001 {
//STRIP001     ASSERT( this->IsA( TYPE(SwFEShell) ),"ViewShell::Prt for FEShell only");
//STRIP001     SwFEShell* pFESh = (SwFEShell*)this;
//STRIP001     // Wir bauen uns ein neues Dokument
//STRIP001     SwDoc *pPrtDoc = new SwDoc;
//STRIP001     pPrtDoc->AddLink();
//STRIP001     pPrtDoc->SetRefForDocShell( (SvEmbeddedObjectRef*)&(long&)rDocShellRef );
//STRIP001     pPrtDoc->LockExpFlds();
//STRIP001
//STRIP001     // Der Drucker wird uebernommen
//STRIP001     if (pPrt)
//STRIP001         pPrtDoc->SetPrt( pPrt );
//STRIP001
//STRIP001     const SfxPoolItem* pCpyItem;
//STRIP001     const SfxItemPool& rPool = GetAttrPool();
//STRIP001     for( USHORT nWh = POOLATTR_BEGIN; nWh < POOLATTR_END; ++nWh )
//STRIP001         if( 0 != ( pCpyItem = rPool.GetPoolDefaultItem( nWh ) ) )
//STRIP001             pPrtDoc->GetAttrPool().SetPoolDefaultItem( *pCpyItem );
//STRIP001
//STRIP001     // JP 29.07.99 - Bug 67951 - set all Styles from the SourceDoc into
//STRIP001     //                              the PrintDoc - will be replaced!
//STRIP001     pPrtDoc->ReplaceStyles( *GetDoc() );
//STRIP001
//STRIP001     SwShellCrsr *pActCrsr = pFESh->_GetCrsr();
//STRIP001     SwShellCrsr *pFirstCrsr = (SwShellCrsr*)*((SwCursor*)pActCrsr->GetNext());
//STRIP001     if( !pActCrsr->HasMark() ) // bei Multiselektion kann der aktuelle Cursor leer sein
//STRIP001         pActCrsr = (SwShellCrsr*)*((SwCursor*)pActCrsr->GetPrev());
//STRIP001     // Die Y-Position der ersten Selektion
//STRIP001     long nMinY = pFESh->IsTableMode() ? pFESh->GetTableCrsr()->GetSttPos().Y()
//STRIP001                                : pFirstCrsr->GetSttPos().Y();
//STRIP001     SwPageFrm* pPage = (SwPageFrm*)GetLayout()->Lower();
//STRIP001     // Suche die zugehoerige Seite
//STRIP001     while ( pPage->GetNext() && nMinY >= pPage->GetNext()->Frm().Top() )
//STRIP001         pPage = (SwPageFrm*)pPage->GetNext();
//STRIP001     // und ihren Seitendescribtor
//STRIP001     SwPageDesc *pSrc = pPage->GetPageDesc();
//STRIP001     SwPageDesc* pPageDesc = pPrtDoc->FindPageDescByName(
//STRIP001                                 pPage->GetPageDesc()->GetName() );
//STRIP001
//STRIP001     if( !pFESh->IsTableMode() && pActCrsr->HasMark() )
//STRIP001     {   // Am letzten Absatz die Absatzattribute richten:
//STRIP001         SwNodeIndex aNodeIdx( *pPrtDoc->GetNodes().GetEndOfContent().StartOfSectionNode() );
//STRIP001         SwTxtNode* pTxtNd = pPrtDoc->GetNodes().GoNext( &aNodeIdx )->GetTxtNode();
//STRIP001         SwCntntNode *pLastNd =
//STRIP001             pActCrsr->GetCntntNode( (*pActCrsr->GetMark()) <= (*pActCrsr->GetPoint()) );
//STRIP001         // Hier werden die Absatzattribute des ersten Absatzes uebertragen
//STRIP001         if( pLastNd && pLastNd->IsTxtNode() )
//STRIP001             ((SwTxtNode*)pLastNd)->CopyCollFmt( *pTxtNd );
//STRIP001     }
//STRIP001
//STRIP001     // es wurde in der CORE eine neu angelegt (OLE-Objekte kopiert!)
//STRIP001 //      if( aDocShellRef.Is() )
//STRIP001 //          SwDataExchange::InitOle( aDocShellRef, pPrtDoc );
//STRIP001     // und fuellen es mit dem selektierten Bereich
//STRIP001     pFESh->Copy( pPrtDoc );
//STRIP001
//STRIP001     //Jetzt noch am ersten Absatz die Seitenvorlage setzen
//STRIP001     {
//STRIP001         SwNodeIndex aNodeIdx( *pPrtDoc->GetNodes().GetEndOfContent().StartOfSectionNode() );
//STRIP001         SwCntntNode* pCNd = pPrtDoc->GetNodes().GoNext( &aNodeIdx ); // gehe zum 1. ContentNode
//STRIP001         if( pFESh->IsTableMode() )
//STRIP001         {
//STRIP001             SwTableNode* pTNd = pCNd->FindTableNode();
//STRIP001             if( pTNd )
//STRIP001                 pTNd->GetTable().GetFrmFmt()->SetAttr( SwFmtPageDesc( pPageDesc ) );
//STRIP001         }
//STRIP001         else
//STRIP001         {
//STRIP001             pCNd->SetAttr( SwFmtPageDesc( pPageDesc ) );
//STRIP001             if( pFirstCrsr->HasMark() )
//STRIP001             {
//STRIP001                 SwTxtNode *pTxtNd = pCNd->GetTxtNode();
//STRIP001                 if( pTxtNd )
//STRIP001                 {
//STRIP001                     SwCntntNode *pFirstNd =
//STRIP001                         pFirstCrsr->GetCntntNode( (*pFirstCrsr->GetMark()) > (*pFirstCrsr->GetPoint()) );
//STRIP001                     // Hier werden die Absatzattribute des ersten Absatzes uebertragen
//STRIP001                     if( pFirstNd && pFirstNd->IsTxtNode() )
//STRIP001                         ((SwTxtNode*)pFirstNd)->CopyCollFmt( *pTxtNd );
//STRIP001                 }
//STRIP001             }
//STRIP001         }
//STRIP001     }
//STRIP001     return pPrtDoc;
//STRIP001 }
/*N*/ SwDoc * ViewShell::FillPrtDoc( SwDoc *pPrtDoc, const SfxPrinter* pPrt)
/*N*/ {DBG_ASSERT(0, "STRIP"); return NULL;//STRIP001
//STRIP001 /*?*/     ASSERT( this->IsA( TYPE(SwFEShell) ),"ViewShell::Prt for FEShell only");
//STRIP001 /*?*/     SwFEShell* pFESh = (SwFEShell*)this;
//STRIP001 /*?*/     // Wir bauen uns ein neues Dokument
//STRIP001 /*?*/ //    SwDoc *pPrtDoc = new SwDoc;
//STRIP001 /*?*/ //    pPrtDoc->AddLink();
//STRIP001 /*?*/ //    pPrtDoc->SetRefForDocShell( (SvEmbeddedObjectRef*)&(long&)rDocShellRef );
//STRIP001 /*?*/     pPrtDoc->LockExpFlds();
//STRIP001 /*?*/
//STRIP001 /*?*/     // Der Drucker wird uebernommen
//STRIP001 /*?*/     //! Make a copy of it since it gets destroyed with the temporary document
//STRIP001 /*?*/     //! used for PDF export
//STRIP001 /*?*/     if (pPrt)
//STRIP001 /*?*/         pPrtDoc->SetPrt( new SfxPrinter(*pPrt) );
//STRIP001 /*?*/
//STRIP001 /*?*/     const SfxPoolItem* pCpyItem;
//STRIP001 /*?*/     const SfxItemPool& rPool = GetAttrPool();
//STRIP001 /*?*/     for( USHORT nWh = POOLATTR_BEGIN; nWh < POOLATTR_END; ++nWh )
//STRIP001 /*?*/         if( 0 != ( pCpyItem = rPool.GetPoolDefaultItem( nWh ) ) )
//STRIP001 /*?*/             pPrtDoc->GetAttrPool().SetPoolDefaultItem( *pCpyItem );
//STRIP001 /*?*/
//STRIP001 /*?*/     // JP 29.07.99 - Bug 67951 - set all Styles from the SourceDoc into
//STRIP001 /*?*/     //                              the PrintDoc - will be replaced!
//STRIP001 /*?*/     pPrtDoc->ReplaceStyles( *GetDoc() );
//STRIP001 /*?*/
//STRIP001 /*?*/     SwShellCrsr *pActCrsr = pFESh->_GetCrsr();
//STRIP001 /*?*/     SwShellCrsr *pFirstCrsr = (SwShellCrsr*)*((SwCursor*)pActCrsr->GetNext());
//STRIP001 /*?*/     if( !pActCrsr->HasMark() ) // bei Multiselektion kann der aktuelle Cursor leer sein
//STRIP001 /*?*/         pActCrsr = (SwShellCrsr*)*((SwCursor*)pActCrsr->GetPrev());
//STRIP001 /*?*/     // Die Y-Position der ersten Selektion
//STRIP001 /*?*/     long nMinY = pFESh->IsTableMode() ? pFESh->GetTableCrsr()->GetSttPos().Y()
//STRIP001 /*?*/                                : pFirstCrsr->GetSttPos().Y();
//STRIP001 /*?*/     SwPageFrm* pPage = (SwPageFrm*)GetLayout()->Lower();
//STRIP001 /*?*/     // Suche die zugehoerige Seite
//STRIP001 /*?*/     while ( pPage->GetNext() && nMinY >= pPage->GetNext()->Frm().Top() )
//STRIP001 /*?*/         pPage = (SwPageFrm*)pPage->GetNext();
//STRIP001 /*?*/     // und ihren Seitendescribtor
//STRIP001 /*?*/     SwPageDesc *pSrc = pPage->GetPageDesc();
//STRIP001 /*?*/     SwPageDesc* pPageDesc = pPrtDoc->FindPageDescByName(
//STRIP001 /*?*/                                 pPage->GetPageDesc()->GetName() );
//STRIP001 /*?*/
//STRIP001 /*?*/     if( !pFESh->IsTableMode() && pActCrsr->HasMark() )
//STRIP001 /*?*/     {   // Am letzten Absatz die Absatzattribute richten:
//STRIP001 /*?*/         SwNodeIndex aNodeIdx( *pPrtDoc->GetNodes().GetEndOfContent().StartOfSectionNode() );
//STRIP001 /*?*/         SwTxtNode* pTxtNd = pPrtDoc->GetNodes().GoNext( &aNodeIdx )->GetTxtNode();
//STRIP001 /*?*/         SwCntntNode *pLastNd =
//STRIP001 /*?*/             pActCrsr->GetCntntNode( (*pActCrsr->GetMark()) <= (*pActCrsr->GetPoint()) );
//STRIP001 /*?*/         // Hier werden die Absatzattribute des ersten Absatzes uebertragen
//STRIP001 /*?*/         if( pLastNd && pLastNd->IsTxtNode() )
//STRIP001 /*?*/             ((SwTxtNode*)pLastNd)->CopyCollFmt( *pTxtNd );
//STRIP001 /*?*/     }
//STRIP001 /*?*/
//STRIP001 /*?*/     // es wurde in der CORE eine neu angelegt (OLE-Objekte kopiert!)
//STRIP001 /*?*/ //      if( aDocShellRef.Is() )
//STRIP001 /*?*/ //          SwDataExchange::InitOle( aDocShellRef, pPrtDoc );
//STRIP001 /*?*/     // und fuellen es mit dem selektierten Bereich
//STRIP001 /*?*/     pFESh->Copy( pPrtDoc );
//STRIP001 /*?*/
//STRIP001 /*?*/     //Jetzt noch am ersten Absatz die Seitenvorlage setzen
//STRIP001 /*?*/     {
//STRIP001 /*?*/         SwNodeIndex aNodeIdx( *pPrtDoc->GetNodes().GetEndOfContent().StartOfSectionNode() );
//STRIP001 /*?*/         SwCntntNode* pCNd = pPrtDoc->GetNodes().GoNext( &aNodeIdx ); // gehe zum 1. ContentNode
//STRIP001 /*?*/         if( pFESh->IsTableMode() )
//STRIP001 /*?*/         {
//STRIP001 /*?*/             SwTableNode* pTNd = pCNd->FindTableNode();
//STRIP001 /*?*/             if( pTNd )
//STRIP001 /*?*/                 pTNd->GetTable().GetFrmFmt()->SetAttr( SwFmtPageDesc( pPageDesc ) );
//STRIP001 /*?*/         }
//STRIP001 /*?*/         else
//STRIP001 /*?*/         {
//STRIP001 /*?*/             pCNd->SetAttr( SwFmtPageDesc( pPageDesc ) );
//STRIP001 /*?*/             if( pFirstCrsr->HasMark() )
//STRIP001 /*?*/             {
//STRIP001 /*?*/                 SwTxtNode *pTxtNd = pCNd->GetTxtNode();
//STRIP001 /*?*/                 if( pTxtNd )
//STRIP001 /*?*/                 {
//STRIP001 /*?*/                     SwCntntNode *pFirstNd =
//STRIP001 /*?*/                         pFirstCrsr->GetCntntNode( (*pFirstCrsr->GetMark()) > (*pFirstCrsr->GetPoint()) );
//STRIP001 /*?*/                     // Hier werden die Absatzattribute des ersten Absatzes uebertragen
//STRIP001 /*?*/                     if( pFirstNd && pFirstNd->IsTxtNode() )
//STRIP001 /*?*/                         ((SwTxtNode*)pFirstNd)->CopyCollFmt( *pTxtNd );
//STRIP001 /*?*/                 }
//STRIP001 /*?*/             }
//STRIP001 /*?*/         }
//STRIP001 /*?*/     }
//STRIP001 /*?*/     return pPrtDoc;
/*N*/ }

/******************************************************************************
 *  Methode     :   void ViewShell::Prt( const SwPrtOptions& rOptions, SfxProgress& rProgress,
 *                                       OutputDevice *pPDFOut )
 *  Beschreibung:
 *  Erstellt    :   OK 04.11.94 15:33
 *  Aenderung   :   MA 10. May. 95
 ******************************************************************************/


/*N*/ BOOL ViewShell::Prt( SwPrtOptions& rOptions, SfxProgress& rProgress,
/*N*/                      OutputDevice *pPDFOut )
/*N*/ {DBG_ASSERT(0, "STRIP"); return FALSE;//STRIP001
//STRIP001 /*?*/ //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//STRIP001 /*?*/ //Immer die Druckroutine in viewpg.cxx (fuer Seitenvorschau) mitpflegen!!
//STRIP001 /*?*/ //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//STRIP001 /*?*/
//STRIP001 /*?*/    BOOL bStartJob = FALSE;
//STRIP001 /*?*/
//STRIP001 /*?*/     //! Note: Since for PDF export of (multi-)selection a temporary
//STRIP001 /*?*/     //! document is created that contains only the selects parts,
//STRIP001 /*?*/     //! and thus that document is to printed in whole the,
//STRIP001 /*?*/     //! rOptions.bPrintSelection parameter will be false.
//STRIP001 /*?*/    BOOL bSelection = rOptions.bPrintSelection;
//STRIP001 /*?*/
//STRIP001 /*?*/     // Damit beim Selektionsdruck nicht mit einer leeren Seite gestartet wird
//STRIP001 /*?*/    BOOL bIgnoreEmptyPage = bSelection;
//STRIP001 /*?*/
//STRIP001 /*?*/    MultiSelection aMulti( rOptions.aMulti );
//STRIP001 /*?*/
//STRIP001 /*?*/    if ( !aMulti.GetSelectCount() )
//STRIP001 /*?*/        return bStartJob;
//STRIP001 /*?*/
//STRIP001 /*?*/    Range aPages( aMulti.FirstSelected(), aMulti.LastSelected() );
//STRIP001 /*?*/    if ( aPages.Max() > USHRT_MAX )
//STRIP001 /*?*/        aPages.Max() = USHRT_MAX;
//STRIP001 /*?*/
//STRIP001 /*?*/    ASSERT( aPages.Min() > 0,
//STRIP001 /*?*/            "Seite 0 Drucken?" );
//STRIP001 /*?*/    ASSERT( aPages.Min() <= aPages.Max(),
//STRIP001 /*?*/            "MinSeite groesser MaxSeite." );
//STRIP001 /*?*/
//STRIP001 /*?*/     SfxPrinter* pPrt = 0;   //!! will be 0 for PDF export !!
//STRIP001 /*?*/     if (pPDFOut)
//STRIP001 /*?*/         pPDFOut->Push();
//STRIP001 /*?*/     else
//STRIP001 /*?*/     {
//STRIP001 /*?*/         // wenn kein Drucker vorhanden ist, wird nicht gedruckt
//STRIP001 /*?*/         pPrt = GetPrt();
//STRIP001 /*?*/         if( !pPrt || !pPrt->GetName().Len() )
//STRIP001 /*?*/         {
//STRIP001 /*?*/             ASSERT( FALSE, "Drucken ohne Drucker?" );
//STRIP001 /*?*/             return bStartJob;
//STRIP001 /*?*/         }
//STRIP001 /*?*/
//STRIP001 /*?*/         if( !rOptions.GetJobName().Len() && !pPrt->IsJobActive() )
//STRIP001 /*?*/             return bStartJob;
//STRIP001 /*?*/
//STRIP001 /*?*/         // Einstellungen am Drucker merken
//STRIP001 /*?*/         SwPrtOptSave aPrtSave( pPrt );
//STRIP001 /*?*/     }
//STRIP001 /*?*/     OutputDevice *pPrtOrPDFOut = pPDFOut ? pPDFOut : (OutputDevice *) pPrt;
//STRIP001 /*?*/
//STRIP001 /*?*/    // eine neue Shell fuer den Printer erzeugen
//STRIP001 /*?*/    ViewShell *pShell;
//STRIP001 /*?*/    SwDoc *pPrtDoc;
//STRIP001 /*?*/
//STRIP001 /*?*/     //!! muss warum auch immer hier in diesem scope existieren !!
//STRIP001 /*?*/     //!! (hängt mit OLE Objekten im Dokument zusammen.)
//STRIP001 /*?*/     SvEmbeddedObjectRef aDocShellRef;
//STRIP001 /*?*/
//STRIP001 /*?*/     // PDF export for (multi-)selection has already generated a temporary document
//STRIP001 /*?*/     // with the selected text. (see XRenderable implementation in unotxdoc.cxx)
//STRIP001 /*?*/     // Thus we like to go in the 'else' part here in that case.
//STRIP001 /*?*/     // Is is implemented this way because PDF export calls this Prt function
//STRIP001 /*?*/     // once per page and we do not like to always have the temporary document
//STRIP001 /*?*/     // to be created that often here in the 'then' part.
//STRIP001 /*?*/     if (bSelection )
//STRIP001 /*?*/    {
//STRIP001 /*?*/         pPrtDoc = CreatePrtDoc( pPrt, aDocShellRef );
//STRIP001 /*?*/
//STRIP001 /*?*/        // eine ViewShell darauf
//STRIP001 /*?*/         OutputDevice *pTmpDev = pPDFOut ? pPDFOut : 0;
//STRIP001 /*?*/         pShell = new ViewShell( *pPrtDoc, 0, pOpt, pTmpDev );
//STRIP001 /*?*/        pPrtDoc->SetRefForDocShell( 0 );
//STRIP001 /*?*/    }
//STRIP001 /*?*/    else
//STRIP001 /*?*/    {
//STRIP001 /*?*/         pPrtDoc = GetDoc();
//STRIP001 /*?*/         OutputDevice *pTmpDev = pPDFOut ? pPDFOut : 0;
//STRIP001 /*?*/         pShell = new ViewShell( *this, 0, pTmpDev );
//STRIP001 /*?*/    }
//STRIP001 /*?*/
//STRIP001 /*?*/    {   //Zusaetzlicher Scope, damit die CurrShell vor dem zerstoeren der
//STRIP001 /*?*/        //Shell zurueckgesetzt wird.
//STRIP001 /*?*/
//STRIP001 /*?*/    SET_CURR_SHELL( pShell );
//STRIP001 /*?*/
//STRIP001 /*?*/     if (!pPDFOut)
//STRIP001 /*?*/     {
//STRIP001 /*?*/         Link aLnk = LINK(pShell->Imp(), SwViewImp, SetStopPrt);
//STRIP001 /*?*/         ((SfxPrintProgress &) rProgress).SetCancelHdl(aLnk);
//STRIP001 /*?*/     }
//STRIP001 /*?*/
//STRIP001 /*?*/
//STRIP001 /*?*/    //JP 01.02.99: das ReadOnly Flag wird NIE mitkopiert; Bug 61335
//STRIP001 /*?*/    if( pOpt->IsReadonly() )
//STRIP001 /*?*/        pShell->pOpt->SetReadonly( TRUE );
//STRIP001 /*?*/
//STRIP001 /*?*/     // save options at draw view:
//STRIP001 /*?*/     SwDrawViewSave aDrawViewSave( pShell->GetDrawView() );
//STRIP001 /*?*/
//STRIP001 /*?*/    pShell->PrepareForPrint( rOptions );
//STRIP001 /*?*/
//STRIP001 /*?*/    // gibt es versteckte Absatzfelder, braucht nicht beruecksichtigt werden,
//STRIP001 /*?*/    // wenn diese bereits ausgeblendet sind
//STRIP001 /*?*/    BOOL bHiddenFlds = FALSE;
//STRIP001 /*?*/    SwHiddenParaFieldType* pFldType = 0;
//STRIP001 /*?*/    if ( GetViewOptions()->IsShowHiddenPara() )
//STRIP001 /*?*/    {
//STRIP001 /*?*/        pFldType    = (SwHiddenParaFieldType*)pPrtDoc->
//STRIP001 /*?*/                                          GetSysFldType(RES_HIDDENPARAFLD);
//STRIP001 /*?*/        bHiddenFlds = pFldType && pFldType->GetDepends();
//STRIP001 /*?*/        if( bHiddenFlds )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            SwMsgPoolItem aHnt( RES_HIDDENPARA_PRINT );
//STRIP001 /*?*/            pFldType->Modify( &aHnt, 0);
//STRIP001 /*?*/        }
//STRIP001 /*?*/    }
//STRIP001 /*?*/
//STRIP001 /*?*/
//STRIP001 /*?*/    XubString *pStr;
//STRIP001 /*?*/    ULONG nMergeAct = rOptions.nMergeAct, nMergeCnt = rOptions.nMergeCnt;
//STRIP001 /*?*/    if( nMergeAct )
//STRIP001 /*?*/    {
//STRIP001 /*?*/        pStr = new SW_RESSTR(STR_STATSTR_LETTER);
//STRIP001 /*?*/        *pStr += ' ';
//STRIP001 /*?*/        *pStr += XubString::CreateFromInt64( nMergeAct );
//STRIP001 /*?*/        if( nMergeCnt )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            *pStr += '/';
//STRIP001 /*?*/            *pStr += XubString::CreateFromInt64( nMergeCnt );
//STRIP001 /*?*/        }
//STRIP001 /*?*/    }
//STRIP001 /*?*/    else
//STRIP001 /*?*/    {
//STRIP001 /*?*/        pStr = 0;
//STRIP001 /*?*/        ++nMergeAct;
//STRIP001 /*?*/    }
//STRIP001 /*?*/
//STRIP001 /*?*/    // Seiten fuers Drucken formatieren
//STRIP001 /*?*/    pShell->CalcPagesForPrint( (USHORT)aPages.Max(), &rProgress, pStr,
//STRIP001 /*?*/                                nMergeAct, nMergeCnt );
//STRIP001 /*?*/
//STRIP001 /*?*/     // Some field types, can require a valid layout
//STRIP001 /*?*/     // (expression fields in tables). For these we do an UpdateFlds
//STRIP001 /*?*/     // here after calculation of the pages.
//STRIP001 /*?*/    pShell->UpdateFlds(TRUE);
//STRIP001 /*?*/
//STRIP001 /*?*/     if( !  pShell->Imp()->IsStopPrt() &&
//STRIP001 /*?*/        (pPDFOut || rOptions.GetJobName().Len() || pPrt->IsJobActive()) )
//STRIP001 /*?*/    {
//STRIP001 /*?*/        BOOL bStop = FALSE;
//STRIP001 /*?*/        int nJobStartError = JOBSET_ERR_DEFAULT;
//STRIP001 /*?*/
//STRIP001 /*?*/        USHORT nCopyCnt = rOptions.bCollate ? rOptions.nCopyCount : 1;
//STRIP001 /*?*/
//STRIP001 /*?*/        USHORT nPrintCount = 1;
//STRIP001 /*?*/        XubString sJobName( rOptions.GetJobName() );
//STRIP001 /*?*/
//STRIP001 /*?*/        for ( USHORT nCnt = 0; !bStop && nCnt < nCopyCnt; nCnt++ )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            const SwPageFrm *pStPage  = (SwPageFrm*)pShell->GetLayout()->Lower();
//STRIP001 /*?*/            const SwFrm     *pEndPage = pStPage;
//STRIP001 /*?*/
//STRIP001 /*?*/            USHORT nFirstPageNo = 0;
//STRIP001 /*?*/            USHORT nLastPageNo  = 0;
//STRIP001 /*?*/            USHORT nPageNo      = 1;
//STRIP001 /*?*/
//STRIP001 /*?*/             if (pPrt)
//STRIP001 /*?*/             {
//STRIP001 /*?*/                 if( rOptions.IsPrintSingleJobs() && sJobName.Len() &&
//STRIP001 /*?*/                     ( bStartJob || rOptions.bJobStartet ) )
//STRIP001 /*?*/                 {
//STRIP001 /*?*/                     pPrt->EndJob();
//STRIP001 /*?*/                     bStartJob = FALSE;
//STRIP001 /*?*/                     rOptions.bJobStartet = TRUE;
//STRIP001 /*?*/
//STRIP001 /*?*/                     // Reschedule statt Yield, da Yield keine Events abarbeitet
//STRIP001 /*?*/                     // und es sonst eine Endlosschleife gibt.
//STRIP001 /*?*/                     while( pPrt->IsPrinting() )
//STRIP001 /*?*/                             rProgress.Reschedule();
//STRIP001 /*?*/
//STRIP001 /*?*/                     sJobName = rOptions.MakeNextJobName();
//STRIP001 /*?*/                     nJobStartError = JOBSET_ERR_DEFAULT;
//STRIP001 /*?*/                 }
//STRIP001 /*?*/             }
//STRIP001 /*?*/
//STRIP001 /*?*/            for( USHORT i = 1; i <= (USHORT)aPages.Max(); ++i )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                if( i < (USHORT)aPages.Min() )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    if( !pStPage->GetNext() )
//STRIP001 /*?*/                        break;
//STRIP001 /*?*/                    pStPage = (SwPageFrm*)pStPage->GetNext();
//STRIP001 /*?*/                    pEndPage= pStPage;
//STRIP001 /*?*/                }
//STRIP001 /*?*/                else if( i == (USHORT)aPages.Min() )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    nFirstPageNo = i;
//STRIP001 /*?*/                    nLastPageNo = nFirstPageNo;
//STRIP001 /*?*/                    if( !pStPage->GetNext() || (i == (USHORT)aPages.Max()) )
//STRIP001 /*?*/                        break;
//STRIP001 /*?*/                    pEndPage = pStPage->GetNext();
//STRIP001 /*?*/                }
//STRIP001 /*?*/                else if( i > (USHORT)aPages.Min() )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    nLastPageNo = i;
//STRIP001 /*?*/                    if( !pEndPage->GetNext() || (i == (USHORT)aPages.Max()) )
//STRIP001 /*?*/                        break;
//STRIP001 /*?*/                    pEndPage = pEndPage->GetNext();
//STRIP001 /*?*/                }
//STRIP001 /*?*/            }
//STRIP001 /*?*/
//STRIP001 /*?*/            if( !nFirstPageNo )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                if( bHiddenFlds )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    SwMsgPoolItem aHnt( RES_HIDDENPARA_PRINT );
//STRIP001 /*?*/                    pFldType->Modify( &aHnt, 0);
//STRIP001 /*?*/                    CalcPagesForPrint( (USHORT)aPages.Max(), &rProgress, pStr,
//STRIP001 /*?*/                                        nMergeAct, nMergeCnt );
//STRIP001 /*?*/                }
//STRIP001 /*?*/                bStop = TRUE;
//STRIP001 /*?*/                break;
//STRIP001 /*?*/            }
//STRIP001 /*?*/
//STRIP001 /*?*/ // HACK: Hier muss von der MultiSelection noch eine akzeptable Moeglichkeit
//STRIP001 /*?*/ // geschaffen werden, alle Seiten von Seite x an zu deselektieren.
//STRIP001 /*?*/ // Z.B. durch SetTotalRange ....
//STRIP001 /*?*/
//STRIP001 /*?*/ //         aMulti.Select( Range( nLastPageNo+1, SELECTION_MAX ), FALSE );
//STRIP001 /*?*/            MultiSelection aTmpMulti( Range( 1, nLastPageNo ) );
//STRIP001 /*?*/            long nTmpIdx = aMulti.FirstSelected();
//STRIP001 /*?*/            while ( SFX_ENDOFSELECTION != nTmpIdx && nTmpIdx <= long(nLastPageNo) )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                aTmpMulti.Select( nTmpIdx );
//STRIP001 /*?*/                nTmpIdx = aMulti.NextSelected();
//STRIP001 /*?*/            }
//STRIP001 /*?*/            aMulti = aTmpMulti;
//STRIP001 /*?*/ // Ende des HACKs
//STRIP001 /*?*/
//STRIP001 /*?*/            const USHORT nSelCount = USHORT(aMulti.GetSelectCount()
//STRIP001 /*?*/                            /* * nCopyCnt*/);
//STRIP001 /*?*/
//STRIP001 /*?*/            rProgress.SetText( SW_RESSTR(STR_STATSTR_PRINT) );
//STRIP001 /*?*/            lcl_SetState( rProgress, 1, nSelCount, pStr,
//STRIP001 /*?*/                                nMergeAct, nMergeCnt, nSelCount, 1 );
//STRIP001 /*?*/
//STRIP001 /*?*/            if ( rOptions.bPrintReverse )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                const SwFrm *pTmp = pStPage;
//STRIP001 /*?*/                pStPage  = (SwPageFrm*)pEndPage;
//STRIP001 /*?*/                pEndPage = pTmp;
//STRIP001 /*?*/                nPageNo  = nLastPageNo;
//STRIP001 /*?*/            }
//STRIP001 /*?*/            else
//STRIP001 /*?*/                nPageNo = nFirstPageNo;
//STRIP001 /*?*/
//STRIP001 /*?*/            // PostitListe holen
//STRIP001 /*?*/            _SetGetExpFlds aPostItFields;
//STRIP001 /*?*/            SwDoc*     pPostItDoc   = 0;
//STRIP001 /*?*/            ViewShell* pPostItShell = 0;
//STRIP001 /*?*/            if( rOptions.nPrintPostIts != POSTITS_NONE )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                lcl_GetPostIts( pDoc, aPostItFields );
//STRIP001 /*?*/                pPostItDoc   = new SwDoc;
//STRIP001 /*?*/                 if (pPrt)
//STRIP001 /*?*/                     pPostItDoc->SetPrt( pPrt );
//STRIP001 /*?*/                pPostItShell = new ViewShell( *pPostItDoc, 0,
//STRIP001 /*?*/                                               pShell->GetViewOptions() );
//STRIP001 /*?*/                // Wenn PostIts am Dokumentenende gedruckt werden sollen,
//STRIP001 /*?*/                // die Druckreihenfolge allerdings umgekehrt ist, dann hier
//STRIP001 /*?*/                if ( ( rOptions.nPrintPostIts == POSTITS_ENDDOC ) &&
//STRIP001 /*?*/                        rOptions.bPrintReverse )
//STRIP001 /*?*/                        lcl_PrintPostItsEndDoc( pPostItShell, aPostItFields,
//STRIP001 /*?*/                        aMulti, sJobName, bStartJob, nJobStartError,
//STRIP001 /*?*/                        rOptions.bPrintRightPage, rOptions.bPrintLeftPage, TRUE );
//STRIP001 /*?*/
//STRIP001 /*?*/            }
//STRIP001 /*?*/
//STRIP001 /*?*/            // aOldMapMode wird fuer das Drucken von Umschlaegen gebraucht.
//STRIP001 /*?*/            MapMode aOldMapMode;
//STRIP001 /*?*/
//STRIP001 /*?*/            const SwPageDesc *pLastPageDesc = NULL;
//STRIP001 /*?*/             BOOL bSetOrient   = FALSE;
//STRIP001 /*?*/             BOOL bSetPaperSz  = FALSE;
//STRIP001 /*?*/             BOOL bSetPaperBin = FALSE;
//STRIP001 /*?*/             BOOL bSetPrt      = FALSE;
//STRIP001 /*?*/             if (pPrt)
//STRIP001 /*?*/             {
//STRIP001 /*?*/                 bSetOrient      = pPrt->HasSupport( SUPPORT_SET_ORIENTATION );
//STRIP001 /*?*/                 bSetPaperSz     = pPrt->HasSupport( SUPPORT_SET_PAPERSIZE );
//STRIP001 /*?*/                 bSetPaperBin    =  !rOptions.bPaperFromSetup &&
//STRIP001 /*?*/                                     pPrt->HasSupport( SUPPORT_SET_PAPERBIN );
//STRIP001 /*?*/                 bSetPrt = bSetOrient || bSetPaperSz || bSetPaperBin;
//STRIP001 /*?*/             }
//STRIP001 /*?*/
//STRIP001 /*?*/            if ( rOptions.nPrintPostIts != POSTITS_ONLY )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                while( pStPage && !bStop )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    // Mag der Anwender noch ?
//STRIP001 /*?*/                    rProgress.Reschedule();
//STRIP001 /*?*/
//STRIP001 /*?*/                     if (pPrt)
//STRIP001 /*?*/                     {
//STRIP001 /*?*/                         if( ( JOBSET_ERR_ERROR == nJobStartError )
//STRIP001 /*?*/                             || ( !pPrt->IsJobActive() &&
//STRIP001 /*?*/                                 ( !sJobName.Len() || bStartJob ) ) )
//STRIP001 /*?*/                         {
//STRIP001 /*?*/                             if( bHiddenFlds )
//STRIP001 /*?*/                             {
//STRIP001 /*?*/                                 SwMsgPoolItem aHnt( RES_HIDDENPARA_PRINT );
//STRIP001 /*?*/                                 pFldType->Modify( &aHnt, 0);
//STRIP001 /*?*/                                 CalcPagesForPrint( (USHORT)aPages.Max() );
//STRIP001 /*?*/                             }
//STRIP001 /*?*/                             bStop = TRUE;
//STRIP001 /*?*/                             break;
//STRIP001 /*?*/                         }
//STRIP001 /*?*/                     }
//STRIP001 /*?*/                    else if (pShell->Imp()->IsStopPrt())
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        bStop = TRUE;
//STRIP001 /*?*/                        break;
//STRIP001 /*?*/                    }
//STRIP001 /*?*/
//STRIP001 /*?*/                     ::SetSwVisArea( pShell, pStPage->Frm(), 0 != pPDFOut );
//STRIP001 /*?*/
//STRIP001 /*?*/                    //  wenn wir einen Umschlag drucken wird ein Offset beachtet
//STRIP001 /*?*/                    if( pStPage->GetFmt()->GetPoolFmtId() == RES_POOLPAGE_JAKET )
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                         aOldMapMode = pPrtOrPDFOut->GetMapMode();
//STRIP001 /*?*/                         Point aNewOrigin = pPrtOrPDFOut->GetMapMode().GetOrigin();
//STRIP001 /*?*/                        aNewOrigin += rOptions.aOffset;
//STRIP001 /*?*/                         MapMode aTmp( pPrtOrPDFOut->GetMapMode() );
//STRIP001 /*?*/                        aTmp.SetOrigin( aNewOrigin );
//STRIP001 /*?*/                         pPrtOrPDFOut->SetMapMode( aTmp );
//STRIP001 /*?*/                    }
//STRIP001 /*?*/
//STRIP001 /*?*/                    BOOL bRightPg = pStPage->OnRightPage();
//STRIP001 /*?*/                    if( aMulti.IsSelected( nPageNo ) &&
//STRIP001 /*?*/                        ( (bRightPg && rOptions.bPrintRightPage) ||
//STRIP001 /*?*/                            (!bRightPg && rOptions.bPrintLeftPage) ) )
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                         if ( bSetPrt )
//STRIP001 /*?*/                        {
//STRIP001 /*?*/                             // check for empty page
//STRIP001 /*?*/                             const SwPageFrm* pFormatPage = NULL;
//STRIP001 /*?*/
//STRIP001 /*?*/                             // for empty pages, take the format of the partner
//STRIP001 /*?*/                             // page
//STRIP001 /*?*/                             if ( pStPage->IsEmptyPage() )
//STRIP001 /*?*/                             {
//STRIP001 /*?*/                                 if ( bRightPg )
//STRIP001 /*?*/                                     pFormatPage = (SwPageFrm*)pStPage->GetNext();
//STRIP001 /*?*/                                 else
//STRIP001 /*?*/                                     pFormatPage = (SwPageFrm*)pStPage->GetPrev();
//STRIP001 /*?*/                             }
//STRIP001 /*?*/
//STRIP001 /*?*/                             if ( ! pFormatPage )
//STRIP001 /*?*/                                 pFormatPage = pStPage;
//STRIP001 /*?*/
//STRIP001 /*?*/                             if ( pLastPageDesc != pFormatPage->GetPageDesc() )
//STRIP001 /*?*/                             {
//STRIP001 /*?*/                                 pLastPageDesc = pFormatPage->GetPageDesc();
//STRIP001 /*?*/
//STRIP001 /*?*/                                 const BOOL bLandScp =
//STRIP001 /*?*/                                         pFormatPage->GetPageDesc()->GetLandscape();
//STRIP001 /*?*/
//STRIP001 /*?*/                                 if( bSetPaperBin )      // Schacht einstellen.
//STRIP001 /*?*/                                     pPrt->SetPaperBin( pFormatPage->GetFmt()->
//STRIP001 /*?*/                                                        GetPaperBin().GetValue() );
//STRIP001 /*?*/
//STRIP001 /*?*/                                 if (bSetOrient )
//STRIP001 /*?*/                                {
//STRIP001 /*?*/                                    // Orientation einstellen: Breiter als Hoch
//STRIP001 /*?*/                                    //  -> Landscape, sonst -> Portrait.
//STRIP001 /*?*/                                    if( bLandScp )
//STRIP001 /*?*/                                        pPrt->SetOrientation(ORIENTATION_LANDSCAPE);
//STRIP001 /*?*/                                    else
//STRIP001 /*?*/                                        pPrt->SetOrientation(ORIENTATION_PORTRAIT);
//STRIP001 /*?*/                                }
//STRIP001 /*?*/                                if (bSetPaperSz )
//STRIP001 /*?*/                                {
//STRIP001 /*?*/                                    Size aSize = pStPage->Frm().SSize();
//STRIP001 /*?*/
//STRIP001 /*?*/                                    // Let VCL decide which printer paper should be used for printing
//STRIP001 /*?*/                                    pPrt->SetPaperSizeUser( aSize );
//STRIP001 /*?*/                                }
//STRIP001 /*?*/                             }
//STRIP001 /*?*/                        }
//STRIP001 /*?*/
//STRIP001 /*?*/                        // Wenn PostIts nach Seite gedruckt werden sollen,
//STRIP001 /*?*/                        // jedoch Reverse eingestellt ist ...
//STRIP001 /*?*/                        if( rOptions.bPrintReverse &&
//STRIP001 /*?*/                            rOptions.nPrintPostIts == POSTITS_ENDPAGE )
//STRIP001 /*?*/                                lcl_PrintPostItsEndPage( pPostItShell, aPostItFields,
//STRIP001 /*?*/                                    nPageNo, aMulti, sJobName, bStartJob, nJobStartError,
//STRIP001 /*?*/                                    rOptions.bPrintRightPage, rOptions.bPrintLeftPage,
//STRIP001 /*?*/                                    rOptions.bPrintReverse );
//STRIP001 /*?*/
//STRIP001 /*?*/                        lcl_SetState( rProgress, nPrintCount++, nSelCount,
//STRIP001 /*?*/                                            pStr, nMergeAct, nMergeCnt,
//STRIP001 /*?*/                                            nSelCount, nPageNo );
//STRIP001 /*?*/
//STRIP001 /*?*/                        if( !bStartJob && JOBSET_ERR_DEFAULT == nJobStartError
//STRIP001 /*?*/                            && sJobName.Len() )
//STRIP001 /*?*/                        {
//STRIP001 /*?*/                             if( pPrt && !pPrt->IsJobActive() )
//STRIP001 /*?*/                            {
//STRIP001 /*?*/                                bStartJob = pPrt->StartJob( sJobName );
//STRIP001 /*?*/                                if( !bStartJob )
//STRIP001 /*?*/                                {
//STRIP001 /*?*/                                    nJobStartError = JOBSET_ERR_ERROR;
//STRIP001 /*?*/                                    continue;
//STRIP001 /*?*/                                }
//STRIP001 /*?*/                            }
//STRIP001 /*?*/
//STRIP001 /*?*/                             pShell->InitPrt( pPrt, pPDFOut );
//STRIP001 /*?*/
//STRIP001 /*?*/                             ::SetSwVisArea( pShell, pStPage->Frm(), 0 != pPDFOut );
//STRIP001 /*?*/                            nJobStartError = JOBSET_ERR_ISSTARTET;
//STRIP001 /*?*/                        }
//STRIP001 /*?*/                        // Bei Selektionsdruck wird ggf. die erste leere Seite ausgelassen
//STRIP001 /*?*/                        if( !bIgnoreEmptyPage || (0==(bIgnoreEmptyPage=TRUE)) ||
//STRIP001 /*?*/                            pStPage->Frm().Height() )
//STRIP001 /*?*/                        {
//STRIP001 /*?*/                             if (pPrt)
//STRIP001 /*?*/                                 pPrt->StartPage();
//STRIP001 /*?*/                            pStPage->GetUpper()->Paint( pStPage->Frm() );
//STRIP001 /*?*/ //                         SFX_APP()->SpoilDemoOutput( *pShell->GetOut(),
//STRIP001 /*?*/ //                                                          pStPage->Frm().SVRect() );
//STRIP001 /*?*/                             if (pPrt)
//STRIP001 /*?*/                                 pPrt->EndPage();
//STRIP001 /*?*/                        }
//STRIP001 /*?*/                        SwPaintQueue::Repaint();
//STRIP001 /*?*/
//STRIP001 /*?*/                         // OD 03.03.2003 #103602# - printing contents of table,
//STRIP001 /*?*/                         // which doesn't fit on the page on an extra page, doesn't
//STRIP001 /*?*/                         // work as excepted for PDF export. Thus, do *not*
//STRIP001 /*?*/                         // perform this code for PDF export.
//STRIP001 /*?*/                         if ( !pPDFOut )
//STRIP001 /*?*/                         {
//STRIP001 /*?*/                        //Wenn eine Tabelle heraushaengt, so wird der Rest der
//STRIP001 /*?*/                        //Tabelle auf zusaetzliche Seiten verteilt.
//STRIP001 /*?*/                        const SwFrm *pFrm = pStPage->FindLastBodyCntnt();
//STRIP001 /*?*/                        if ( pFrm && pFrm->IsInTab() )
//STRIP001 /*?*/                        {
//STRIP001 /*?*/                            pFrm = pFrm->FindTabFrm();
//STRIP001 /*?*/                            const SwFrm *pBody = pStPage->FindBodyCont();
//STRIP001 /*?*/                            long nBottom = pBody->Prt().Bottom();
//STRIP001 /*?*/                            nBottom += pBody->Frm().Top();
//STRIP001 /*?*/                            if ( nBottom < pFrm->Frm().Bottom() )
//STRIP001 /*?*/                            {
//STRIP001 /*?*/                                SwRootFrm *pRoot = (SwRootFrm*)pStPage->GetUpper();
//STRIP001 /*?*/                                long nDiff = pFrm->Frm().Bottom() - nBottom;
//STRIP001 /*?*/                                SwRect aNewVis( pBody->Prt() );
//STRIP001 /*?*/                                aNewVis += pBody->Frm().Pos();
//STRIP001 /*?*/                                SwRect aTmp( pShell->VisArea() );
//STRIP001 /*?*/                                aTmp.SSize().Height() = LONG_MAX - aTmp.Top();
//STRIP001 /*?*/                                aTmp.SSize().Width()  = LONG_MAX - aTmp.Left();
//STRIP001 /*?*/                                 ::SetSwVisArea( pShell, aTmp, 0 != pPDFOut );
//STRIP001 /*?*/                                while ( nDiff > 0 )
//STRIP001 /*?*/                                {
//STRIP001 /*?*/                                     if (pPrt)
//STRIP001 /*?*/                                         pPrt->StartPage();
//STRIP001 /*?*/
//STRIP001 /*?*/                                    //VisArea auf die Tabelle schummeln
//STRIP001 /*?*/                                    aNewVis.Pos().Y() += aNewVis.Height()+1;
//STRIP001 /*?*/
//STRIP001 /*?*/                                    //Offset in den MapMode schummeln.
//STRIP001 /*?*/                                     MapMode aMap( pPrtOrPDFOut->GetMapMode() );
//STRIP001 /*?*/                                    Point aTmp( aMap.GetOrigin() );
//STRIP001 /*?*/                                    aTmp.Y() -= aNewVis.Height()+1;
//STRIP001 /*?*/                                    aMap.SetOrigin( aTmp );
//STRIP001 /*?*/                                     pPrtOrPDFOut->SetMapMode( aMap );
//STRIP001 /*?*/
//STRIP001 /*?*/                                     /// OD 30.08.2002 #102450#
//STRIP001 /*?*/                                     /// determine color of page the table is on
//STRIP001 /*?*/                                     /// for <PaintLayer> method calls
//STRIP001 /*?*/                                     const Color aPageBackgrdColor =
//STRIP001 /*?*/                                             pStPage->GetDrawBackgrdColor();
//STRIP001 /*?*/                                    pRoot->HackPrepareLongTblPaint( HACK_TABLEMODE_INIT );
//STRIP001 /*?*/                                    SwTxtFrm::SetMinPrtLine( aNewVis.Pos().Y() );
//STRIP001 /*?*/                                    pFrm->PaintBaBo( aNewVis, pStPage, TRUE );
//STRIP001 /*?*/                                    if ( pShell->Imp()->HasDrawView() )
//STRIP001 /*?*/                                    {
//STRIP001 /*?*/                                        pRoot->HackPrepareLongTblPaint( HACK_TABLEMODE_LOCKLINES );
//STRIP001 /*?*/                                         /// OD 30.08.2002 #102450# - add 3rd parameter
//STRIP001 /*?*/                                         pShell->Imp()->PaintLayer( pShell->GetDoc()->GetHellId(),
//STRIP001 /*?*/                                                         aNewVis, &aPageBackgrdColor );
//STRIP001 /*?*/                                        pRoot->HackPrepareLongTblPaint( HACK_TABLEMODE_PAINTLINES );
//STRIP001 /*?*/                                        pRoot->HackPrepareLongTblPaint( HACK_TABLEMODE_UNLOCKLINES );
//STRIP001 /*?*/                                    }
//STRIP001 /*?*/                                    pFrm->Paint( aNewVis );
//STRIP001 /*?*/                                    if ( pShell->Imp()->HasDrawView() )
//STRIP001 /*?*/                                    {
//STRIP001 /*?*/                                         /// OD 30.08.2002 #102450# - add 3rd parameter
//STRIP001 /*?*/                                        pShell->Imp()->PaintLayer( pShell->GetDoc()->GetHeavenId(),
//STRIP001 /*?*/                                                     aNewVis, &aPageBackgrdColor );
//STRIP001 /*?*/                                         pShell->Imp()->PaintLayer( pShell->GetDoc()->GetControlsId(),
//STRIP001 /*?*/                                                                    aNewVis );
//STRIP001 /*?*/                                        pRoot->HackPrepareLongTblPaint( HACK_TABLEMODE_PAINTLINES );
//STRIP001 /*?*/                                    }
//STRIP001 /*?*/                                    pRoot->HackPrepareLongTblPaint( HACK_TABLEMODE_EXIT );
//STRIP001 /*?*/                                    SwTxtFrm::SetMinPrtLine( 0 );
//STRIP001 /*?*/
//STRIP001 /*?*/ //                                 SFX_APP()->SpoilDemoOutput( *pShell->GetOut(),
//STRIP001 /*?*/ //                                                              aNewVis.SVRect() );
//STRIP001 /*?*/                                     if (pPrt)
//STRIP001 /*?*/                                         pPrt->EndPage();
//STRIP001 /*?*/                                    SwPaintQueue::Repaint();
//STRIP001 /*?*/                                    nDiff -= pBody->Prt().Height();
//STRIP001 /*?*/                                }
//STRIP001 /*?*/                            }
//STRIP001 /*?*/                        }
//STRIP001 /*?*/                         } // END OF If ( !pPDFOut ); OD 03.03.2003 #103602#
//STRIP001 /*?*/
//STRIP001 /*?*/                        // Wenn PostIts nach Seite gedruckt werden sollen ...
//STRIP001 /*?*/                        if( (!rOptions.bPrintReverse) &&
//STRIP001 /*?*/                            rOptions.nPrintPostIts == POSTITS_ENDPAGE )
//STRIP001 /*?*/                                lcl_PrintPostItsEndPage( pPostItShell, aPostItFields,
//STRIP001 /*?*/                                    nPageNo, aMulti, sJobName, bStartJob, nJobStartError,
//STRIP001 /*?*/                                    rOptions.bPrintRightPage, rOptions.bPrintLeftPage,
//STRIP001 /*?*/                                    rOptions.bPrintReverse );
//STRIP001 /*?*/                    }
//STRIP001 /*?*/
//STRIP001 /*?*/                    // den eventl. fuer Umschlaege modifizierte OutDevOffset wieder
//STRIP001 /*?*/                    // zuruecksetzen.
//STRIP001 /*?*/                    if( pStPage->GetFmt()->GetPoolFmtId() == RES_POOLPAGE_JAKET )
//STRIP001 /*?*/                         pPrtOrPDFOut->SetMapMode( aOldMapMode );
//STRIP001 /*?*/
//STRIP001 /*?*/                    if ( pStPage == pEndPage )
//STRIP001 /*?*/                        pStPage = 0;
//STRIP001 /*?*/                    else if ( rOptions.bPrintReverse )
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        --nPageNo;
//STRIP001 /*?*/                        pStPage = (SwPageFrm*)pStPage->GetPrev();
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                    else
//STRIP001 /*?*/                    {   ++nPageNo;
//STRIP001 /*?*/                        pStPage = (SwPageFrm*)pStPage->GetNext();
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                }
//STRIP001 /*?*/                if ( bStop )
//STRIP001 /*?*/                    break;
//STRIP001 /*?*/            }
//STRIP001 /*?*/
//STRIP001 /*?*/            // Wenn PostIts am Dokumentenende gedruckt werden sollen, dann hier machen
//STRIP001 /*?*/            if( ((rOptions.nPrintPostIts == POSTITS_ENDDOC) && !rOptions.bPrintReverse)
//STRIP001 /*?*/                || (rOptions.nPrintPostIts == POSTITS_ONLY) )
//STRIP001 /*?*/                    lcl_PrintPostItsEndDoc( pPostItShell, aPostItFields, aMulti,
//STRIP001 /*?*/                        sJobName, bStartJob, nJobStartError,
//STRIP001 /*?*/                        rOptions.bPrintRightPage, rOptions.bPrintLeftPage,
//STRIP001 /*?*/                        rOptions.bPrintReverse );
//STRIP001 /*?*/
//STRIP001 /*?*/            if( pPostItShell )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                pPostItDoc->_SetPrt( 0 );   //damit am echten DOC der Drucker bleibt
//STRIP001 /*?*/                delete pPostItShell;        //Nimmt das PostItDoc mit ins Grab.
//STRIP001 /*?*/            }
//STRIP001 /*?*/
//STRIP001 /*?*/            if( bStartJob )
//STRIP001 /*?*/                rOptions.bJobStartet = TRUE;
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/        if( bHiddenFlds && !bStop )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            SwMsgPoolItem aHnt( RES_HIDDENPARA_PRINT );
//STRIP001 /*?*/            pFldType->Modify( &aHnt, 0);
//STRIP001 /*?*/            CalcPagesForPrint( (USHORT)aPages.Max() );
//STRIP001 /*?*/        }
//STRIP001 /*?*/    }
//STRIP001 /*?*/    delete pStr;
//STRIP001 /*?*/
//STRIP001 /*?*/    }  //Zus. Scope wg. CurShell!
//STRIP001 /*?*/
//STRIP001 /*?*/    delete pShell;
//STRIP001 /*?*/
//STRIP001 /*?*/     if (bSelection )
//STRIP001 /*?*/    {
//STRIP001 /*?*/         // damit das Dokument nicht den Drucker mit ins Grab nimmt
//STRIP001 /*?*/        pPrtDoc->_SetPrt( NULL );
//STRIP001 /*?*/
//STRIP001 /*?*/        if ( !pPrtDoc->RemoveLink() )
//STRIP001 /*?*/            delete pPrtDoc;
//STRIP001 /*?*/    }
//STRIP001 /*?*/
//STRIP001 /*?*/     // restore settings of OutputDevicef
//STRIP001 /*?*/     if (pPDFOut)
//STRIP001 /*?*/         pPDFOut->Pop();
//STRIP001 /*?*/
//STRIP001 /*?*/    return bStartJob;
/*N*/ }

/******************************************************************************
 *  Methode     :   PrtOle2()
 *  Beschreibung:
 *  Erstellt    :   PK 07.12.94
 *  Aenderung   :   MA 16. Feb. 95
 ******************************************************************************/



//STRIP001 void ViewShell::PrtOle2( SwDoc *pDoc, const SwViewOption *pOpt, SwPrtOptions& rOptions,
//STRIP001                       OutputDevice* pOleOut, const Rectangle& rRect )
//STRIP001 {
//STRIP001   //Wir brauchen eine Shell fuer das Drucken. Entweder hat das Doc schon
//STRIP001  //eine, dann legen wir uns eine neue Sicht an, oder das Doc hat noch
//STRIP001  //keine, dann erzeugen wir die erste Sicht.
//STRIP001  ViewShell *pSh;
//STRIP001  if( pDoc->GetRootFrm() && pDoc->GetRootFrm()->GetCurrShell() )
//STRIP001      pSh = new ViewShell( *pDoc->GetRootFrm()->GetCurrShell(), 0, pOleOut );
//STRIP001  else
//STRIP001      pSh = new ViewShell( *pDoc, 0, pOpt, pOleOut );
//STRIP001
//STRIP001  {
//STRIP001      SET_CURR_SHELL( pSh );
//STRIP001         pSh->PrepareForPrint( rOptions );
//STRIP001         pSh->SetPrtFormatOption( TRUE );
//STRIP001
//STRIP001      SwRect aSwRect( rRect );
//STRIP001      pSh->aVisArea = aSwRect;
//STRIP001
//STRIP001      if ( pDoc->IsBrowseMode() && pSh->GetNext() == pSh )
//STRIP001      {
//STRIP001          pSh->CheckBrowseView( FALSE );
//STRIP001          pDoc->GetRootFrm()->Lower()->InvalidateSize();
//STRIP001      }
//STRIP001
//STRIP001      // Seiten fuers Drucken formatieren
//STRIP001      pSh->CalcPagesForPrint( SHRT_MAX );
//STRIP001
//STRIP001      //#39275# jetzt will der Meyer doch ein Clipping
//STRIP001      pOleOut->Push( PUSH_CLIPREGION );
//STRIP001      pOleOut->IntersectClipRegion( aSwRect.SVRect() );
//STRIP001      pSh->GetLayout()->Paint( aSwRect );
//STRIP001 //       SFX_APP()->SpoilDemoOutput( *pOleOut, rRect );
//STRIP001      pOleOut->Pop();
//STRIP001
//STRIP001      // erst muss das CurrShell Object zerstoert werden!!
//STRIP001  }
//STRIP001  delete pSh;
//STRIP001 }

/******************************************************************************
 *  Methode     :   IsAnyFieldInDoc()
 *  Beschreibung:   Stellt fest, ob im DocNodesArray Felder verankert sind
 *  Erstellt    :   JP 27.07.95
 *  Aenderung   :   JP 10.12.97
 ******************************************************************************/



//STRIP001 BOOL ViewShell::IsAnyFieldInDoc() const
//STRIP001 {
//STRIP001  const SfxPoolItem* pItem;
//STRIP001  USHORT nMaxItems = pDoc->GetAttrPool().GetItemCount( RES_TXTATR_FIELD );
//STRIP001  for( USHORT n = 0; n < nMaxItems; ++n )
//STRIP001      if( 0 != (pItem = pDoc->GetAttrPool().GetItem( RES_TXTATR_FIELD, n )))
//STRIP001      {
//STRIP001          const SwFmtFld* pFmtFld = (SwFmtFld*)pItem;
//STRIP001          const SwTxtFld* pTxtFld = pFmtFld->GetTxtFld();
//STRIP001          if( pTxtFld && pTxtFld->GetTxtNode().GetNodes().IsDocNodes() )
//STRIP001              return TRUE;
//STRIP001      }
//STRIP001  return FALSE;
//STRIP001 }



/******************************************************************************
 *  Klasse      :   SwPrtOptSave
 *  Erstellt    :   AMA 12.07.95
 *  Aenderung   :   AMA 12.07.95
 *  Holt sich im Ctor folgende Einstellungen des Druckers, die im Dtor dann
 *  wieder im Drucker gesetzt werden (falls sie sich ueberhaupt geaendert haben)
 *  - PaperBin - Orientation - PaperSize -
 ******************************************************************************/



//STRIP001 SwPrtOptSave::SwPrtOptSave( Printer *pPrinter )
//STRIP001  : pPrt( pPrinter )
//STRIP001 {
//STRIP001  if ( pPrt )
//STRIP001  {
//STRIP001      ePaper = pPrt->GetPaper();
//STRIP001      if ( PAPER_USER == ePaper )
//STRIP001          aSize = pPrt->GetPaperSize();
//STRIP001      eOrientation = pPrt->GetOrientation();
//STRIP001      nPaperBin = pPrt->GetPaperBin();
//STRIP001
//STRIP001  }
//STRIP001 }



//STRIP001 SwPrtOptSave::~SwPrtOptSave()
//STRIP001 {
//STRIP001  if ( pPrt )
//STRIP001  {
//STRIP001      if ( PAPER_USER == ePaper )
//STRIP001      {
//STRIP001          if( pPrt->GetPaperSize() != aSize )
//STRIP001              pPrt->SetPaperSizeUser( aSize );
//STRIP001      }
//STRIP001      else if ( pPrt->GetPaper() != ePaper )
//STRIP001          pPrt->SetPaper( ePaper );
//STRIP001      if ( pPrt->GetOrientation() != eOrientation)
//STRIP001          pPrt->SetOrientation( eOrientation );
//STRIP001      if ( pPrt->GetPaperBin() != nPaperBin )
//STRIP001          pPrt->SetPaperBin( nPaperBin );
//STRIP001  }
//STRIP001 }


/******************************************************************************
 *  SwDrawViewSave
 *
 *  Saves some settings at the draw view
 ******************************************************************************/

//STRIP001 SwDrawViewSave::SwDrawViewSave( SdrView* pSdrView )
//STRIP001     : pDV( pSdrView )
//STRIP001 {
//STRIP001     if ( pDV )
//STRIP001  {
//STRIP001         bPrintDraft = pDV->IsLineDraftPrn();
//STRIP001         sLayerNm.AssignAscii( RTL_CONSTASCII_STRINGPARAM("Controls" ) );
//STRIP001         bPrintControls = pDV->IsLayerPrintable( sLayerNm );
//STRIP001     }
//STRIP001 }

//STRIP001 SwDrawViewSave::~SwDrawViewSave()
//STRIP001 {
//STRIP001     if ( pDV )
//STRIP001  {
//STRIP001         pDV->SetLineDraftPrn( bPrintDraft );
//STRIP001         pDV->SetFillDraftPrn( bPrintDraft );
//STRIP001         pDV->SetGrafDraftPrn( bPrintDraft );
//STRIP001         pDV->SetTextDraftPrn( bPrintDraft );
//STRIP001         pDV->SetLayerPrintable( sLayerNm, bPrintControls );
//STRIP001     }
//STRIP001 }


// OD 09.01.2003 #i6467# - method also called for page preview
//STRIP001 void ViewShell::PrepareForPrint(  const SwPrtOptions &rOptions )
//STRIP001 {
//STRIP001  // Viewoptions fuer den Drucker setzen
//STRIP001     pOpt->SetGraphic ( TRUE == rOptions.bPrintGraphic );
//STRIP001  pOpt->SetTable   ( TRUE == rOptions.bPrintTable );
//STRIP001  pOpt->SetDraw    ( TRUE == rOptions.bPrintDraw  );
//STRIP001  pOpt->SetControl ( TRUE == rOptions.bPrintControl );
//STRIP001  pOpt->SetPageBack( TRUE == rOptions.bPrintPageBackground );
//STRIP001  pOpt->SetBlackFont( TRUE == rOptions.bPrintBlackFont );
//STRIP001
//STRIP001  if ( HasDrawView() )
//STRIP001  {
//STRIP001      SdrView *pDrawView = GetDrawView();
//STRIP001      FASTBOOL bDraw = rOptions.bPrintDraw;
//STRIP001         // OD 09.01.2003 #i6467# - consider, if view shell belongs to page preview
//STRIP001         if ( !IsPreView() )
//STRIP001         {
//STRIP001             pDrawView->SetLineDraftPrn( !bDraw );
//STRIP001             pDrawView->SetFillDraftPrn( !bDraw );
//STRIP001             pDrawView->SetGrafDraftPrn( !bDraw );
//STRIP001             pDrawView->SetTextDraftPrn( !bDraw );
//STRIP001         }
//STRIP001         else
//STRIP001         {
//STRIP001             pDrawView->SetLineDraft( !bDraw );
//STRIP001             pDrawView->SetFillDraft( !bDraw );
//STRIP001             pDrawView->SetGrafDraft( !bDraw );
//STRIP001             pDrawView->SetTextDraft( !bDraw );
//STRIP001         }
//STRIP001
//STRIP001         String sLayerNm;
//STRIP001         sLayerNm.AssignAscii(RTL_CONSTASCII_STRINGPARAM("Controls" ));
//STRIP001         // OD 09.01.2003 #i6467# - consider, if view shell belongs to page preview
//STRIP001         if ( !IsPreView() )
//STRIP001         {
//STRIP001             pDrawView->SetLayerPrintable( sLayerNm, rOptions.bPrintControl );
//STRIP001         }
//STRIP001         else
//STRIP001         {
//STRIP001             pDrawView->SetLayerVisible( sLayerNm, rOptions.bPrintControl );
//STRIP001         }
//STRIP001  }
//STRIP001 }
