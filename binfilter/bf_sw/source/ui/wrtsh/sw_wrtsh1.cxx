/*************************************************************************
 *
 *  $RCSfile: sw_wrtsh1.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:41:28 $
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

#include <so3/outplace.hxx>

#if STLPORT_VERSION>=321
#include <math.h>   // prevent conflict between exception and std::exception
#endif

#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif

#ifndef _SVDVIEW_HXX //autogen
#include <bf_svx/svdview.hxx>
#endif
#ifndef _SOT_FACTORY_HXX
#include <sot/factory.hxx>
#endif
#ifndef _SFXITEMITER_HXX //autogen
#include <svtools/itemiter.hxx>
#endif
#ifndef _SOUND_HXX //autogen
#include <vcl/sound.hxx>
#endif
#ifndef _BIGINT_HXX //autogen
#include <tools/bigint.hxx>
#endif
#ifndef _SVSTOR_HXX //autogen
#include <so3/svstor.hxx>
#endif
#ifndef _INSDLG_HXX //autogen
#include <so3/insdlg.hxx>
#endif
#ifndef _FRAMEOBJ_HXX //autogen
#include <bf_sfx2/frameobj.hxx>
#endif
#ifndef _EHDL_HXX //autogen
#include <svtools/ehdl.hxx>
#endif
#ifndef _IPENV_HXX //autogen
#include <so3/ipenv.hxx>
#endif
#ifndef _SOERR_HXX //autogen
#include <so3/soerr.hxx>
#endif
#ifndef _CACHESTR_HXX //autogen
#include <tools/cachestr.hxx>
#endif
#ifndef INCLUDED_SVTOOLS_MODULEOPTIONS_HXX
#include <svtools/moduleoptions.hxx>
#endif
#ifndef _SVX_BRKITEM_HXX //autogen
#include <bf_svx/brkitem.hxx>
#endif
#ifndef SMDLL0_HXX //autogen
#include <bf_starmath/smdll0.hxx>
#endif
#ifndef _SCHDLL0_HXX
#include <bf_sch/schdll0.hxx>
#endif
#ifndef _SCH_DLL_HXX
#include <bf_sch/schdll.hxx>
#endif
#ifndef _SCH_MEMCHRT_HXX
#include <bf_sch/memchrt.hxx>
#endif
#ifndef _OFF_APP_HXX //autogen
#include <bf_offmgr/app.hxx>
#endif
#ifndef _OFAACCFG_HXX //autogen
#include <bf_offmgr/ofaaccfg.hxx>
#endif
#ifndef _MySVXACORR_HXX
#include <bf_svx/svxacorr.hxx>
#endif
#ifndef _SV_GRAPH_HXX //autogen
#include <vcl/graph.hxx>
#endif
#ifndef _SVX_IMPGRF_HXX
#include <bf_svx/impgrf.hxx>
#endif
#ifndef _SFX_PRINTER_HXX //autogen
#include <bf_sfx2/printer.hxx>
#endif
#ifndef _UNOTOOLS_CHARCLASS_HXX
#include <unotools/charclass.hxx>
#endif

#ifndef _FMTFTN_HXX //autogen
#include <fmtftn.hxx>
#endif
#ifndef _FMTHBSH_HXX //autogen
#include <fmthbsh.hxx>
#endif
#ifndef _FMTPDSC_HXX //autogen
#include <fmtpdsc.hxx>
#endif
#ifndef _WDOCSH_HXX
#include <wdocsh.hxx>
#endif
#ifndef _BASESH_HXX
#include <basesh.hxx>
#endif
#ifndef _SWMODULE_HXX
#include <swmodule.hxx>
#endif
#ifndef _WRTSH_HXX
#include <wrtsh.hxx>
#endif
#ifndef _VIEW_HXX
#include <view.hxx>
#endif
#ifndef _UITOOL_HXX
#include <uitool.hxx>
#endif
#ifndef _CMDID_H
#include <cmdid.h>
#endif
#ifndef _PAGEDESC_HXX
#include <pagedesc.hxx>
#endif
#ifndef _FRMMGR_HXX
#include <frmmgr.hxx>
#endif
#ifndef _SHELLIO_HXX
#include <shellio.hxx>
#endif
#ifndef _UINUMS_HXX
#include <uinums.hxx>  // fuer Anwenden einer
#endif
#ifndef _SWUNDO_HXX
#include <swundo.hxx>  // fuer Undo-Ids
#endif
#ifndef _SWCLI_HXX
#include <swcli.hxx>
#endif
#ifndef _POOLFMT_HXX
#include <poolfmt.hxx>
#endif
#ifndef _WVIEW_HXX
#include <wview.hxx>
#endif
#ifndef _EDTWIN_HXX
#include <edtwin.hxx>
#endif
#ifndef _FMTCOL_HXX
#include <fmtcol.hxx>
#endif
#ifndef _SWTABLE_HXX
#include <swtable.hxx>
#endif
#ifndef _CAPTION_HXX
#include <caption.hxx>
#endif
#ifndef _VISCRS_HXX //autogen wg. SwSelPaintRects
#include <viscrs.hxx>
#endif
#ifndef _SWDTFLVR_HXX
#include <swdtflvr.hxx>
#endif
#ifndef _CRSSKIP_HXX
#include <crsskip.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _SWERROR_H
#include <swerror.h>
#endif
#ifndef _WRTSH_HRC
#include <wrtsh.hrc>
#endif
#ifndef _SWSTYLENAMEMAPPER_HXX
#include <SwStyleNameMapper.hxx>
#endif
namespace binfilter {

#define COMMON_INI_LIST \
        rView(rShell),\
        ePageMove(MV_NO),\
        pCrsrStack(0),  \
        fnLeaveSelect(&SwWrtShell::SttLeaveSelect),\
        fnDrag(&SwWrtShell::BeginDrag),\
        fnEndDrag(&SwWrtShell::EndDrag),\
        fnSetCrsr(&SwWrtShell::SetCrsr),\
        fnKillSel(&SwWrtShell::Ignore),\
        bDestOnStack(FALSE),\
        pModeStack(0)

#define BITFLD_INI_LIST \
        bClearMark = \
        bIns = TRUE;\
        bAddMode = \
        bExtMode = \
        bInSelect = \
        bCopy = \
        bLayoutMode = \
        bNoEdit = \
        bSelWrd = \
        bSelLn = \
        bIsInClickToEdit = FALSE;


//STRIP001 SvxAutoCorrect* lcl_IsAutoCorr()
//STRIP001 {
//STRIP001      SvxAutoCorrect* pACorr = OFF_APP()->GetAutoCorrConfig()->GetAutoCorrect();
//STRIP001     if( pACorr && !pACorr->IsAutoCorrFlag( CptlSttSntnc | CptlSttWrd |
//STRIP001                          ChgFractionSymbol | ChgOrdinalNumber |
//STRIP001                             ChgToEnEmDash | SetINetAttr | Autocorrect ))
//STRIP001      pACorr = 0;
//STRIP001  return pACorr;
//STRIP001 }
//STRIP001
//STRIP001 void SwWrtShell::NoEdit(BOOL bHideCrsr)
//STRIP001 {
//STRIP001  if(bHideCrsr)
//STRIP001      HideCrsr();
//STRIP001  bNoEdit = TRUE;
//STRIP001 }
//STRIP001
//STRIP001
//STRIP001
//STRIP001 void SwWrtShell::Edit()
//STRIP001 {
//STRIP001  if (CanInsert())
//STRIP001  {
//STRIP001      ShowCrsr();
//STRIP001      bNoEdit = FALSE;
//STRIP001  }
//STRIP001 }
//STRIP001
//STRIP001
//STRIP001
//STRIP001 BOOL SwWrtShell::IsEndWrd()
//STRIP001 {
//STRIP001  MV_KONTEXT(this);
//STRIP001  if(IsEndPara() && !IsSttPara())
//STRIP001      return TRUE;
//STRIP001
//STRIP001  return IsEndWord();
//STRIP001 }
//STRIP001
//STRIP001
//STRIP001 /*------------------------------------------------------------------------
//STRIP001  Beschreibung:   Abfrage, ob Einfuegen moeglich ist; gfs. Beep
//STRIP001 ------------------------------------------------------------------------*/
//STRIP001
//STRIP001
//STRIP001
//STRIP001 BOOL SwWrtShell::_CanInsert()
//STRIP001 {
//STRIP001  if(!CanInsert())
//STRIP001  {
//STRIP001      Sound::Beep();
//STRIP001      return FALSE;
//STRIP001  }
//STRIP001  return TRUE;
//STRIP001 }
//STRIP001 /*------------------------------------------------------------------------
//STRIP001  Beschreibung:   String einfuegen
//STRIP001 ------------------------------------------------------------------------*/
//STRIP001
//STRIP001 void SwWrtShell::InsertByWord( const String & rStr)
//STRIP001 {
//STRIP001  if( rStr.Len() )
//STRIP001  {
//STRIP001      BOOL bDelim = GetAppCharClass().isLetterNumeric( rStr, 0 );
//STRIP001      xub_StrLen nPos = 0, nStt = 0;
//STRIP001      for( ; nPos < rStr.Len(); nPos++ )
//STRIP001          {
//STRIP001          BOOL bTmpDelim = GetAppCharClass().isLetterNumeric( rStr, nPos );
//STRIP001          if( bTmpDelim != bDelim )
//STRIP001          {
//STRIP001              Insert( rStr.Copy( nStt, nPos - nStt ));
//STRIP001              nStt = nPos;
//STRIP001          }
//STRIP001      }
//STRIP001      if( nStt != nPos )
//STRIP001          Insert( rStr.Copy( nStt, nPos - nStt ));
//STRIP001  }
//STRIP001 }
//STRIP001
//STRIP001
//STRIP001 void SwWrtShell::Insert( const String &rStr )
//STRIP001 {
//STRIP001  ResetCursorStack();
//STRIP001  if( !_CanInsert() )
//STRIP001      return;
//STRIP001
//STRIP001  BOOL bStarted = FALSE, bHasSel = HasSelection(),
//STRIP001      bCallIns = bIns /*|| bHasSel*/;
//STRIP001
//STRIP001  // Notify abschalten
//STRIP001     // FME: This seems to be an optimisation: CallChgLink should not be called
//STRIP001     // for an insert event. This cannot hold any longer, since inserting
//STRIP001     // characters from a different script type has to call CallChgLink.
//STRIP001 //    SwChgLinkFlag *pChgFlg = bCallIns ? new SwChgLinkFlag( *this ) : 0;
//STRIP001
//STRIP001  if( bHasSel )
//STRIP001  {
//STRIP001          // nur hier klammern, da das normale Insert schon an der
//STRIP001          // Editshell geklammert ist
//STRIP001      StartAllAction();
//STRIP001      StartUndo(UNDO_INSERT);
//STRIP001      bStarted = TRUE;
//STRIP001      DelRight();
//STRIP001  }
//STRIP001 /*
//STRIP001 JP 21.01.98: Ueberschreiben ueberschreibt nur die Selektion, nicht das
//STRIP001          naechste Zeichen.
//STRIP001  if( bHasSel && !bIns && 1 < rStr.Len() )
//STRIP001  {
//STRIP001      // falls mehrere Zeichen anstehen, nur das erste einfuegen,
//STRIP001      // der Rest muss dann aber Ueberschrieben werden.
//STRIP001      SwEditShell::Insert( rStr.GetChar( 0 ) );
//STRIP001      SwEditShell::Overwrite( rStr.Copy( 1 ) );
//STRIP001  }
//STRIP001  else
//STRIP001 */
//STRIP001      bCallIns ? SwEditShell::Insert( rStr ) : SwEditShell::Overwrite( rStr );
//STRIP001
//STRIP001
//STRIP001  if( bStarted )
//STRIP001  {
//STRIP001      EndAllAction();
//STRIP001      EndUndo(UNDO_INSERT);
//STRIP001  }
//STRIP001 //    delete pChgFlg;
//STRIP001 }
//STRIP001
//STRIP001 /* Begrenzung auf maximale Hoehe geht nicht, da die maximale Hoehe
//STRIP001  * des aktuellen Frames nicht erfragt werden kann. */
//STRIP001
//STRIP001
//STRIP001
//STRIP001 void SwWrtShell::Insert( const String &rPath, const String &rFilter,
//STRIP001                       const Graphic &rGrf, SwFlyFrmAttrMgr *pFrmMgr,
//STRIP001                       BOOL bRule )
//STRIP001 {
//STRIP001  ResetCursorStack();
//STRIP001  if ( !_CanInsert() )
//STRIP001      return;
//STRIP001
//STRIP001  StartAllAction();
//STRIP001  StartUndo(UNDO_INSERT);
//STRIP001
//STRIP001  if ( HasSelection() )
//STRIP001      DelRight();
//STRIP001      // eingefuegte Grafik in eigenen Absatz, falls am Ende
//STRIP001      // eines nichtleeren Absatzes
//STRIP001  if ( IsEndPara() && !IsSttPara() )
//STRIP001      SwFEShell::SplitNode();
//STRIP001
//STRIP001  EnterSelFrmMode();
//STRIP001
//STRIP001  BOOL bSetGrfSize = TRUE;
//STRIP001  BOOL bOwnMgr     = FALSE;
//STRIP001
//STRIP001  if ( !pFrmMgr )
//STRIP001  {
//STRIP001      bOwnMgr = TRUE;
//STRIP001      pFrmMgr = new SwFlyFrmAttrMgr( TRUE, this, FRMMGR_TYPE_GRF );
//STRIP001
//STRIP001      // VORSICHT
//STRIP001      // GetAttrSet nimmt einen Abgleich vor
//STRIP001      // Beim Einfuegen ist eine SwFrmSize vorhanden wegen der
//STRIP001      // DEF-Rahmengroesse
//STRIP001      // Diese muss fuer die optimale Groesse explizit entfernt werden
//STRIP001      pFrmMgr->DelAttr(RES_FRM_SIZE);
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      Size aSz( pFrmMgr->GetSize() );
//STRIP001      if ( !aSz.Width() || !aSz.Height() )
//STRIP001      {
//STRIP001          aSz.Width() = aSz.Height() = 567;
//STRIP001          pFrmMgr->SetSize( aSz );
//STRIP001      }
//STRIP001      else if ( aSz.Width() != DFLT_WIDTH && aSz.Height() != DFLT_HEIGHT )
//STRIP001          bSetGrfSize = FALSE;
//STRIP001
//STRIP001      pFrmMgr->SetSizeType(ATT_FIX_SIZE);
//STRIP001
//STRIP001  }
//STRIP001
//STRIP001  // Einfuegen der Grafik
//STRIP001  SwFEShell::Insert(rPath, rFilter, &rGrf, &pFrmMgr->GetAttrSet());
//STRIP001  if ( bOwnMgr )
//STRIP001      pFrmMgr->UpdateAttrMgr();
//STRIP001
//STRIP001  if( bSetGrfSize && !bRule )
//STRIP001  {
//STRIP001      Size aGrfSize, aBound = GetGraphicDefaultSize();
//STRIP001      GetGrfSize( aGrfSize );
//STRIP001
//STRIP001      //Die GrafikSize noch um die Randattribute vergroessern, denn die
//STRIP001      //Zaehlen beim Rahmen mit.
//STRIP001      aGrfSize.Width() += pFrmMgr->CalcWidthBorder();
//STRIP001      aGrfSize.Height()+= pFrmMgr->CalcHeightBorder();
//STRIP001
//STRIP001      const BigInt aTempWidth( aGrfSize.Width() );
//STRIP001      const BigInt aTempHeight( aGrfSize.Height());
//STRIP001
//STRIP001      // ggf. Breite anpassen, Hoehe dann proportional verkleinern
//STRIP001      if( aGrfSize.Width() > aBound.Width() )
//STRIP001      {
//STRIP001          aGrfSize.Width()  = aBound.Width();
//STRIP001          aGrfSize.Height() = ((BigInt)aBound.Width()) * aTempHeight / aTempWidth;
//STRIP001      }
//STRIP001      // ggf. Hoehe anpassen, Breite dann proportional verkleinern
//STRIP001      if( aGrfSize.Height() > aBound.Height() )
//STRIP001      {
//STRIP001          aGrfSize.Height() = aBound.Height();
//STRIP001          aGrfSize.Width() =  ((BigInt)aBound.Height()) * aTempWidth / aTempHeight;
//STRIP001      }
//STRIP001      pFrmMgr->SetSize( aGrfSize );
//STRIP001      pFrmMgr->UpdateFlyFrm();
//STRIP001  }
//STRIP001  if ( bOwnMgr )
//STRIP001      delete pFrmMgr;
//STRIP001
//STRIP001  EndUndo(UNDO_INSERT);
//STRIP001  EndAllAction();
//STRIP001 }
//STRIP001
//STRIP001
//STRIP001 /*------------------------------------------------------------------------
//STRIP001    Beschreibung: Fuegt ein OLE-Objekt in die CORE ein.
//STRIP001               Wenn kein Object uebergeben wird, so wird eins erzeugt.
//STRIP001 ------------------------------------------------------------------------*/
//STRIP001
//STRIP001
//STRIP001 void SwWrtShell::Insert( SvInPlaceObjectRef *pRef, SvGlobalName *pName, BOOL bActivate, USHORT nSlotId)
//STRIP001 {
//STRIP001  ResetCursorStack();
//STRIP001  if( !_CanInsert() )
//STRIP001  {
//STRIP001      delete pRef;
//STRIP001      return;
//STRIP001  }
//STRIP001
//STRIP001  if( !pRef )
//STRIP001  {
//STRIP001      //Wir bauen uns ein neues OLE-Objekt, entweder per Dialog oder direkt
//STRIP001      //ueber den Namen.
//STRIP001      SvInPlaceObjectRef xIPObj;
//STRIP001      BOOL bDoVerb = TRUE;
//STRIP001      if ( pName )
//STRIP001      {
//STRIP001          const SotFactory* pFact = SvFactory::Find( *pName );
//STRIP001          if ( pFact )
//STRIP001          {
//STRIP001              SvStorageRef aStor = new SvStorage( aEmptyStr );
//STRIP001              xIPObj = &((SvFactory*)SvInPlaceObject::ClassFactory())->CreateAndInit( *pName,aStor );
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              SvStorageRef aStor = new SvStorage( FALSE, aEmptyStr );
//STRIP001              String aFileName;
//STRIP001              BOOL bOk;
//STRIP001              xIPObj = SvOutPlaceObject::InsertObject( NULL, &aStor, bOk, *pName, aFileName );
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          SvStorageRef aStor = new SvStorage( aEmptyStr, STREAM_STD_READWRITE);
//STRIP001
//STRIP001          switch (nSlotId)
//STRIP001          {
//STRIP001              case SID_INSERT_OBJECT:
//STRIP001              {
//STRIP001                  SvInsertOleObjectDialog aDlg;
//STRIP001                  aDlg.SetHelpId(nSlotId);
//STRIP001
//STRIP001                  //Wir wollen uns nicht selbst servieren.
//STRIP001                  SvObjectServerList aServerList;
//STRIP001                  aDlg.FillObjectServerList( &aServerList );
//STRIP001                  aServerList.Remove( *SwDocShell::ClassFactory() );
//STRIP001
//STRIP001                  xIPObj = aDlg.Execute( GetWin(), aStor, &aServerList);
//STRIP001
//STRIP001                  bDoVerb = aDlg.IsCreateNew();
//STRIP001              }
//STRIP001              break;
//STRIP001
//STRIP001              case SID_INSERT_PLUGIN:
//STRIP001              {
//STRIP001                  SvInsertPlugInDialog aDlg;
//STRIP001                  aDlg.SetHelpId(nSlotId);
//STRIP001
//STRIP001                  xIPObj = aDlg.Execute( GetWin(), aStor);
//STRIP001                  bDoVerb = FALSE;
//STRIP001              }
//STRIP001              break;
//STRIP001
//STRIP001              case SID_INSERT_APPLET:
//STRIP001              {
//STRIP001                  SvInsertAppletDialog aDlg;
//STRIP001                  aDlg.SetHelpId(nSlotId);
//STRIP001
//STRIP001                  xIPObj = aDlg.Execute( GetWin(), aStor);
//STRIP001                  bDoVerb = FALSE;
//STRIP001              }
//STRIP001              break;
//STRIP001
//STRIP001              case SID_INSERT_FLOATINGFRAME:
//STRIP001              {
//STRIP001                  SfxInsertFloatingFrameDialog aDlg( GetWin() );
//STRIP001                  xIPObj = aDlg.Execute( aStor );
//STRIP001                  bDoVerb = FALSE;
//STRIP001              }
//STRIP001
//STRIP001              default:
//STRIP001                  break;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      if ( xIPObj.Is() )
//STRIP001      {
//STRIP001          if( SVOBJ_MISCSTATUS_RESIZEONPRINTERCHANGE &
//STRIP001              xIPObj->GetMiscStatus() && GetPrt() )
//STRIP001              xIPObj->OnDocumentPrinterChanged( GetPrt() );
//STRIP001
//STRIP001          if( InsertOle( xIPObj ) && bActivate && bDoVerb )
//STRIP001          {
//STRIP001              SfxInPlaceClientRef xCli = GetView().FindIPClient( xIPObj,
//STRIP001                                                  &GetView().GetEditWin());
//STRIP001              if ( !xCli.Is() )
//STRIP001              {
//STRIP001                  xCli = new SwOleClient( &GetView(), &GetView().GetEditWin() );
//STRIP001                  SetCheckForOLEInCaption( TRUE );
//STRIP001              }
//STRIP001
//STRIP001              ErrCode nErr = xIPObj->DoConnect( xCli );
//STRIP001              ErrorHandler::HandleError( nErr );
//STRIP001              if ( !ERRCODE_TOERROR(nErr) )
//STRIP001              {
//STRIP001
//STRIP001                  SvEmbeddedObjectRef xObj = &xIPObj;
//STRIP001                  CalcAndSetScale( xObj );
//STRIP001                  //#50270# Error brauchen wir nicht handeln, das erledigt das
//STRIP001                  //DoVerb in der SfxViewShell
//STRIP001                  nErr = GetView().SfxViewShell::DoVerb( xCli, SVVERB_SHOW );
//STRIP001                  if ( !ERRCODE_TOERROR( nErr ) )
//STRIP001                      xIPObj->SetDocumentName( GetView().GetDocShell()->GetTitle() );
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if( HasSelection() )
//STRIP001          DelRight();
//STRIP001      InsertOle( *pRef );
//STRIP001  }
//STRIP001 }

/*------------------------------------------------------------------------
 Beschreibung:   Object in die Core einfuegen.
                 Vom ClipBoard oder Insert
------------------------------------------------------------------------*/

//STRIP001 BOOL SwWrtShell::InsertOle( SvInPlaceObjectRef aRef )
//STRIP001 {
//STRIP001  if ( aRef.Is() )
//STRIP001  {
//STRIP001      ResetCursorStack();
//STRIP001      StartAllAction();
//STRIP001      StartUndo(UNDO_INSERT);
//STRIP001
//STRIP001      //Some differences between StarMath and any other objects:
//STRIP001      //1. Selections should be deleted. For StarMath the Text should be
//STRIP001      //   passed to the Object
//STRIP001      //2. If the cursor is at the end of an non empty paragraph a paragraph
//STRIP001      //   break should be insertet. StarMath objects are character bound and
//STRIP001      //   no break should be inserted.
//STRIP001      //3. If an selektion is passed to a StarMath object, this object should
//STRIP001      //   not be activated. FALSE should be returned then.
//STRIP001      BOOL bStarMath,
//STRIP001           bActivate = TRUE;
//STRIP001
//STRIP001      SvGlobalName aCLSID;
//STRIP001      ULONG lDummy;
//STRIP001      String aDummy;
//STRIP001      // determine source CLSID
//STRIP001      aRef->SvPseudoObject::FillClass( &aCLSID, &lDummy, &aDummy, &aDummy, &aDummy);
//STRIP001      bStarMath = SmModuleDummy::HasID( *aRef->GetSvFactory() );
//STRIP001
//STRIP001      if( IsSelection() )
//STRIP001      {
//STRIP001          if( bStarMath )
//STRIP001          {
//STRIP001              String aMathData;
//STRIP001              GetSelectedText( aMathData, GETSELTXT_PARABRK_TO_ONLYCR );
//STRIP001              if( aMathData.Len() && aRef->SetData( aMathData ) )
//STRIP001              {
//STRIP001                  bActivate = FALSE;
//STRIP001                  //StarMath size depends on the Printer, which is
//STRIP001                  //passed here direct for avoiding time consuming
//STRIP001                  //connections between StarWriter and StarMath
//STRIP001                  aRef->OnDocumentPrinterChanged( GetPrt() );
//STRIP001              }
//STRIP001          }
//STRIP001          DelRight();
//STRIP001      }
//STRIP001
//STRIP001      if ( !bStarMath )
//STRIP001          SwFEShell::SplitNode( FALSE, FALSE );
//STRIP001
//STRIP001      EnterSelFrmMode();
//STRIP001
//STRIP001      SwFlyFrmAttrMgr aFrmMgr( TRUE, this, FRMMGR_TYPE_OLE );
//STRIP001      aFrmMgr.SetSizeType(ATT_FIX_SIZE);
//STRIP001
//STRIP001      SwRect aBound;
//STRIP001      CalcBoundRect( aBound, aFrmMgr.GetAnchor() );
//STRIP001
//STRIP001      //The Size should be suggested by the OLE server
//STRIP001      MapMode aRefMap( aRef->GetMapUnit() );
//STRIP001      Size aSz( aRef->GetVisArea().GetSize() );
//STRIP001      if ( !aSz.Width() || !aSz.Height() )
//STRIP001      {
//STRIP001          aSz.Width() = aSz.Height() = 5000;
//STRIP001          aSz = OutputDevice::LogicToLogic
//STRIP001                                  ( aSz, MapMode( MAP_100TH_MM ), aRefMap );
//STRIP001      }
//STRIP001      MapMode aMyMap( MAP_TWIP );
//STRIP001      aSz = OutputDevice::LogicToLogic( aSz, aRefMap, aMyMap );
//STRIP001      //Object size can be limited
//STRIP001      if ( aSz.Width() > aBound.Width() )
//STRIP001      {
//STRIP001          //Immer proportional begrenzen.
//STRIP001          aSz.Height() = aSz.Height() * aBound.Width() / aSz.Width();
//STRIP001          aSz.Width() = aBound.Width();
//STRIP001      }
//STRIP001      aFrmMgr.SetSize( aSz );
//STRIP001      SwFEShell::Insert( &aRef, &aFrmMgr.GetAttrSet() );
//STRIP001
//STRIP001      EndAllAction();
//STRIP001      GetView().AutoCaption(OLE_CAP, &aCLSID);
//STRIP001      EndUndo(UNDO_INSERT);
//STRIP001
//STRIP001      return bActivate;
//STRIP001  }
//STRIP001  return FALSE;
//STRIP001 }

/*------------------------------------------------------------------------
    Beschreibung: Das aktuelle selektierte OLE-Objekt wird mit dem
                  Verb in den Server geladen.
------------------------------------------------------------------------*/



//STRIP001 void SwWrtShell::LaunchOLEObj( long nVerb )
//STRIP001 {
//STRIP001  if ( GetCntType() == CNT_OLE &&
//STRIP001       !GetView().GetDocShell()->GetProtocol().IsInPlaceActive() )
//STRIP001  {
//STRIP001      SvInPlaceObjectRef xRef = GetOLEObj();
//STRIP001      ASSERT( xRef.Is(), "OLE not found" );
//STRIP001      SfxInPlaceClientRef xCli;
//STRIP001
//STRIP001         //  Link fuer Daten-Highlighting im Chart zuruecksetzen
//STRIP001         SvtModuleOptions aMOpt;
//STRIP001         if( aMOpt.IsChart() )
//STRIP001         {
//STRIP001             SvGlobalName aObjClsId( *xRef->GetSvFactory() );
//STRIP001             SchMemChart* pMemChart;
//STRIP001             if( SchModuleDummy::HasID( aObjClsId ) &&
//STRIP001                 0 != (pMemChart = SchDLL::GetChartData( xRef ) ))
//STRIP001             {
//STRIP001                 pMemChart->SetSelectionHdl( LINK( this, SwWrtShell,
//STRIP001                                             ChartSelectionHdl ) );
//STRIP001                 //#60043# Damit die DataBrowseBox nicht erscheint wird das
//STRIP001                 //Chart auf Readonly gesetzt wenn es eine Verbindung
//STRIP001                 //zu einer Tabelle hat.
//STRIP001                 if ( GetChartName( xRef ).Len() )
//STRIP001                 {
//STRIP001                     pMemChart->SetReadOnly( TRUE );
//STRIP001                     pMemChart->SetNumberFormatter(GetDoc()->GetNumberFormatter( sal_True ));
//STRIP001                     SchDLL::Update(xRef, pMemChart);
//STRIP001                 }
//STRIP001             }
//STRIP001         }
//STRIP001
//STRIP001         xCli = GetView().FindIPClient( xRef, &GetView().GetEditWin() );
//STRIP001         if ( !xCli.Is() )
//STRIP001             xCli = new SwOleClient( &GetView(), &GetView().GetEditWin() );
//STRIP001
//STRIP001         ((SwOleClient*)&xCli)->SetInDoVerb( TRUE );
//STRIP001
//STRIP001         xRef->DoConnect( xCli );
//STRIP001         SvEmbeddedObjectRef xObj = &xRef;
//STRIP001         CalcAndSetScale( xObj );
//STRIP001         //#50270# Error brauchen wir nicht handeln, das erledigt das
//STRIP001         //DoVerb in der SfxViewShell
//STRIP001         GetView().SfxViewShell::DoVerb( xCli, nVerb );
//STRIP001
//STRIP001         ((SwOleClient*)&xCli)->SetInDoVerb( FALSE );
//STRIP001         CalcAndSetScale( xObj );
//STRIP001  }
//STRIP001 }


/*N*/ void SwWrtShell::CalcAndSetScale( SvEmbeddedObjectRef xObj,
/*N*/                            const SwRect *pFlyPrtRect,
/*N*/                            const SwRect *pFlyFrmRect )
/*N*/ {
/*N*/   //Einstellen der Skalierung am Client. Diese ergibt sich aus der Differenz
/*N*/   //zwischen der VisArea des Objektes und der ObjArea.
/*N*/   ASSERT( xObj.Is(), "ObjectRef not  valid" );
/*N*/
/*N*/   SfxInPlaceClientRef xCli = GetView().FindIPClient( xObj, &GetView().GetEditWin() );
/*N*/   if ( !xCli.Is() || !xCli->GetEnv() )
/*N*/   {
/*N*/       //Das kann ja wohl nur ein nicht aktives Objekt sein. Diese bekommen
/*N*/       //auf Wunsch die neue Groesse als VisArea gesetzt (StarChart)
/*N*/       if( SVOBJ_MISCSTATUS_SERVERRESIZE & xObj->GetMiscStatus() )
/*N*/       {
/*N*/           SwRect aRect( pFlyPrtRect ? *pFlyPrtRect
/*N*/                       : GetAnyCurRect( RECT_FLY_PRT_EMBEDDED, 0, &xObj ));
/*N*/           if( !aRect.IsEmpty() )
/*N*/               xObj->SetVisArea( OutputDevice::LogicToLogic(
/*N*/                           aRect.SVRect(), MAP_TWIP, xObj->GetMapUnit() ));
/*N*/           return;
/*N*/       }
/*N*/       if ( SVOBJ_MISCSTATUS_ALWAYSACTIVATE & xObj->GetMiscStatus() ||
/*N*/            SVOBJ_MISCSTATUS_RESIZEONPRINTERCHANGE & xObj->GetMiscStatus() )
/*N*/       {
/*N*/           xCli = new SwOleClient( &GetView(), &GetView().GetEditWin() );
/*N*/       }
/*N*/       else
/*N*/           return;
/*N*/   }
/*N*/
/*N*/   Size aVisArea( xObj->GetVisArea().GetSize() );
/*N*/   BOOL bSetScale100 = TRUE;
/*N*/   SvContainerEnvironment *pEnv = xCli->GetEnv();
/*N*/
/*N*/   // solange keine vernuenftige Size vom Object kommt, kann nichts
/*N*/   // skaliert werden
/*N*/   if( aVisArea.Width() && aVisArea.Height() )
/*N*/   {
/*N*/       const MapMode aTmp( MAP_TWIP );
/*N*/       aVisArea = OutputDevice::LogicToLogic( aVisArea, xObj->GetMapUnit(), aTmp);
/*N*/       Size aObjArea;
/*N*/       if ( pFlyPrtRect )
/*?*/           aObjArea = pFlyPrtRect->SSize();
/*N*/       else
/*N*/           aObjArea = GetAnyCurRect( RECT_FLY_PRT_EMBEDDED, 0, &xObj ).SSize();
/*N*/
/*N*/       // differ the aObjArea and aVisArea by 1 Pixel then set new VisArea
/*N*/       long nX, nY;
/*N*/       SwSelPaintRects::Get1PixelInLogic( *this, &nX, &nY );
/*N*/       if( !( aVisArea.Width() - nX <= aObjArea.Width() &&
/*N*/              aVisArea.Width() + nX >= aObjArea.Width() &&
/*N*/              aVisArea.Height()- nY <= aObjArea.Height()&&
/*N*/              aVisArea.Height()+ nY >= aObjArea.Height() ))
/*N*/       {
/*N*/           if( SVOBJ_MISCSTATUS_RESIZEONPRINTERCHANGE & xObj->GetMiscStatus() )
/*N*/           {
/*N*/               //This type of objects should never be resized.
/*N*/               //If this request comes from the Writer core (inaktive Object
/*N*/               //ist resized), the Object should be resized too.
/*N*/               //If this request comes from the Object itself, the Frame
/*N*/               //in the Writer core should be resized.
/*N*/               if ( pFlyPrtRect )      //Request from core?
/*N*/               {
/*?*/                   xObj->SetVisArea( OutputDevice::LogicToLogic(
/*?*/                       pFlyPrtRect->SVRect(), MAP_TWIP, xObj->GetMapUnit() ));
/*N*/               }
/*N*/               else
/*N*/               {
/*N*/                   SwRect aTmp( Point( LONG_MIN, LONG_MIN ), aVisArea );
/*N*/                   RequestObjectResize( aTmp, xObj );
/*N*/               }
/*N*/               //Der Rest erledigt sich, weil wir eh wiederkommen sollten, evtl.
/*N*/               //sogar rekursiv.
/*N*/               return;
/*N*/           }
/*N*/           else
/*?*/           {
/*?*/               const Fraction aScaleWidth ( aObjArea.Width(),  aVisArea.Width() );
/*?*/               const Fraction aScaleHeight( aObjArea.Height(), aVisArea.Height());
/*?*/               pEnv->SetSizeScale( aScaleWidth, aScaleHeight );
/*?*/               bSetScale100 = FALSE;
/*N*/           }
/*N*/       }
/*N*/   }
/*?*/
/*?*/   if( bSetScale100 )
/*?*/   {
/*?*/       const Fraction aScale( 1, 1 );
/*?*/       pEnv->SetSizeScale( aScale, aScale );
/*?*/   }
/*?*/
/*?*/   //Jetzt ist auch der guenstige Zeitpunkt die ObjArea einzustellen.
/*?*/   //Die Scalierung muss beruecksichtigt werden.
/*?*/   SwRect aArea;
/*?*/   if ( pFlyPrtRect )
/*?*/   {
/*?*/       aArea = *pFlyPrtRect;
/*?*/       aArea += pFlyFrmRect->Pos();
/*?*/   }
/*?*/   else
/*?*/   {
/*?*/       aArea = GetAnyCurRect( RECT_FLY_PRT_EMBEDDED, 0, &xObj );
/*?*/       aArea.Pos() += GetAnyCurRect( RECT_FLY_EMBEDDED, 0, &xObj ).Pos();
/*?*/   }
/*?*/   aArea.Width ( Fraction( aArea.Width()  ) / pEnv->GetScaleWidth() );
/*?*/   aArea.Height( Fraction( aArea.Height() ) / pEnv->GetScaleHeight());
/*?*/   pEnv->SetObjArea( aArea.SVRect() );
/*?*/
/*?*/   if ( SVOBJ_MISCSTATUS_ALWAYSACTIVATE & xObj->GetMiscStatus() )
/*?*/   {
/*?*/       xObj->DoConnect( xCli );
/*?*/       xObj->DoVerb();
/*?*/   }
/*N*/ }



/*N*/ void SwWrtShell::ConnectObj( SvInPlaceObjectRef xIPObj, const SwRect &rPrt,
/*N*/                           const SwRect &rFrm )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001     SfxInPlaceClientRef xCli = GetView().FindIPClient( xIPObj,
//STRIP001                                                         &GetView().GetEditWin());
//STRIP001     if ( !xCli.Is() )
//STRIP001         xCli = new SwOleClient( &GetView(), &GetView().GetEditWin() );
//STRIP001     xIPObj->DoConnect( xCli );
//STRIP001     SvEmbeddedObjectRef xObj = &xIPObj;
//STRIP001     CalcAndSetScale( xObj, &rPrt, &rFrm );
/*N*/ }

//STRIP001 IMPL_LINK( SwWrtShell, ChartSelectionHdl, ChartSelectionInfo *, pInfo )
//STRIP001 {
//STRIP001  long nRet = 0;
//STRIP001
//STRIP001 #ifdef USED
//STRIP001 // JP 03.11.98: mit der Selektion kann es nicht gehen, da dann der Cursor
//STRIP001 //               immer sichtbar gemacht wird. Das fuehrt dann aber zu
//STRIP001 //               unbeabsichtigten scrollen. Ausserdem sind 2 Selektionen
//STRIP001 //               vorhanden - TabellenSelektion und die OLE-Rahmenselektion.
//STRIP001
//STRIP001  if( pInfo )
//STRIP001  {
//STRIP001      if( CHART_SEL_QUERYSUPPORT & pInfo->nSelection )
//STRIP001          nRet = CHART_SEL_NONE | CHART_SEL_ALL | CHART_SEL_ROW |
//STRIP001                  CHART_SEL_COL | CHART_SEL_POINT;
//STRIP001      else
//STRIP001      {
//STRIP001          // dann suche mal die Tabelle zu diesem StarChart-Object
//STRIP001          SfxInPlaceClient* pIPClient = GetView().GetIPClient();
//STRIP001          SvInPlaceObject* pObj = pIPClient &&
//STRIP001                                  pIPClient->IsInPlaceActive()
//STRIP001                                  ? pIPClient->GetIPObj() : 0;
//STRIP001          String sTable;
//STRIP001          if( pObj )
//STRIP001              sTable = GetChartName( pObj );
//STRIP001
//STRIP001          if( sTable.Len() )
//STRIP001          {
//STRIP001              LockView( TRUE );   //Scrollen im EndAction verhindern
//STRIP001              StartAction();
//STRIP001
//STRIP001              ClearMark();
//STRIP001              if( GotoTable( sTable ) )
//STRIP001              {
//STRIP001                  // !!!!!!!!!!!!!!!
//STRIP001                  //      im nSelection sind Flags gesetzt, koennen also
//STRIP001                  //      auch gemischt auftauchen, darum das nICol, nIRow
//STRIP001                  // !!!!!!!!!!!!!!!!
//STRIP001                  USHORT nIRow = pInfo->nRow, nICol = pInfo->nCol,
//STRIP001                          nRow = 0, nCol = 0;
//STRIP001
//STRIP001                  SchMemChart* pMemChart = SchDLL::GetChartData( pObj );
//STRIP001                  if( pMemChart && 2 == pMemChart->SomeData2().Len() )
//STRIP001                  {
//STRIP001                      if( '1' == pMemChart->SomeData2().GetChar( 0 ) )
//STRIP001                          ++nIRow;
//STRIP001                      if( '1' == pMemChart->SomeData2().GetChar( 1 ))
//STRIP001                          ++nICol;
//STRIP001                  }
//STRIP001
//STRIP001 // ist das default   if( (CHART_SEL_NONE | CHART_SEL_ALL) & pInfo->nSelection )
//STRIP001                  if( CHART_SEL_ROW & pInfo->nSelection )
//STRIP001                      nRow = nIRow, nCol = 0;
//STRIP001                  if( CHART_SEL_COL & pInfo->nSelection )
//STRIP001                      nCol = nICol, nRow = 0;
//STRIP001                  if( CHART_SEL_POINT & pInfo->nSelection )
//STRIP001                      nCol = nICol, nRow = nIRow;
//STRIP001
//STRIP001                  if( GotoTblBox( SwTable::GetBoxName( nRow, nCol ) ) )
//STRIP001                  {
//STRIP001                      nRet = pInfo->nSelection;
//STRIP001                      if( ( CHART_SEL_ROW & pInfo->nSelection && !SelTblRow() ) ||
//STRIP001                          ( CHART_SEL_COL & pInfo->nSelection && !SelTblCol() ) ||
//STRIP001                          ( CHART_SEL_ALL & pInfo->nSelection &&
//STRIP001                              ( SetMark(),
//STRIP001                                  !MoveTable( fnTableCurr, fnTableEnd ))) )
//STRIP001                              nRet = 0;
//STRIP001                      else if( CHART_SEL_POINT & pInfo->nSelection )
//STRIP001                      {
//STRIP001                          // Selektion der einen Box
//STRIP001                          SetMark();
//STRIP001                          if( GoPrevCell() )
//STRIP001                              GoNextCell( FALSE );
//STRIP001                          else if( GoNextCell( FALSE ) )
//STRIP001                              GoPrevCell();
//STRIP001                          else
//STRIP001                              ClearMark();
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001
//STRIP001              EndAction();
//STRIP001              LockView( FALSE );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 #endif
//STRIP001  return nRet;
//STRIP001 }

/*------------------------------------------------------------------------
 Beschreibung:  Einfuegen harter Seitenumbruch;
                Selektionen werden ueberschrieben
------------------------------------------------------------------------*/



//STRIP001 void SwWrtShell::InsertPageBreak(const String *pPageDesc, USHORT nPgNum )
//STRIP001 {
//STRIP001  ResetCursorStack();
//STRIP001  if( _CanInsert() )
//STRIP001  {
//STRIP001      ACT_KONTEXT(this);
//STRIP001      StartUndo(UIUNDO_INSERT_PAGE_BREAK);
//STRIP001
//STRIP001      if ( !IsCrsrInTbl() )
//STRIP001      {
//STRIP001          if(HasSelection())
//STRIP001              DelRight();
//STRIP001          SwFEShell::SplitNode();
//STRIP001      }
//STRIP001
//STRIP001      const SwPageDesc *pDesc = pPageDesc
//STRIP001                              ? FindPageDescByName( *pPageDesc, TRUE ) : 0;
//STRIP001      if( pDesc )
//STRIP001      {
//STRIP001          SwFmtPageDesc aDesc( pDesc );
//STRIP001          aDesc.SetNumOffset( nPgNum );
//STRIP001          SetAttr( aDesc );
//STRIP001      }
//STRIP001      else
//STRIP001          SetAttr( SvxFmtBreakItem(SVX_BREAK_PAGE_BEFORE) );
//STRIP001      EndUndo(UIUNDO_INSERT_PAGE_BREAK);
//STRIP001  }
//STRIP001 }
/*------------------------------------------------------------------------
 Beschreibung:  Einfuegen harter Zeilenumbruch;
                Selektionen werden ueberschrieben
------------------------------------------------------------------------*/


//STRIP001 void SwWrtShell::InsertLineBreak()
//STRIP001 {
//STRIP001  ResetCursorStack();
//STRIP001  if( _CanInsert() )
//STRIP001  {
//STRIP001      if(HasSelection())
//STRIP001          DelRight();
//STRIP001
//STRIP001      const sal_Unicode cIns = 0x0A;
//STRIP001      SvxAutoCorrect* pACorr = lcl_IsAutoCorr();
//STRIP001      if( pACorr )
//STRIP001          AutoCorrect( *pACorr, cIns );
//STRIP001      else
//STRIP001          SwWrtShell::Insert( String( cIns ) );
//STRIP001  }
//STRIP001 }
/*------------------------------------------------------------------------
 Beschreibung:  Einfuegen harter Spaltenumbruch;
                Selektionen werden ueberschrieben
------------------------------------------------------------------------*/


//STRIP001 void SwWrtShell::InsertColumnBreak()
//STRIP001 {
//STRIP001  ACT_KONTEXT(this);
//STRIP001  ResetCursorStack();
//STRIP001  if( _CanInsert() )
//STRIP001  {
//STRIP001      StartUndo(UIUNDO_INSERT_COLUMN_BREAK);
//STRIP001
//STRIP001      if ( !IsCrsrInTbl() )
//STRIP001      {
//STRIP001          if(HasSelection())
//STRIP001              DelRight();
//STRIP001          SwFEShell::SplitNode( FALSE, FALSE );
//STRIP001      }
//STRIP001      SetAttr(SvxFmtBreakItem(SVX_BREAK_COLUMN_BEFORE));
//STRIP001
//STRIP001      EndUndo(UIUNDO_INSERT_COLUMN_BREAK);
//STRIP001  }
//STRIP001 }

/*------------------------------------------------------------------------
 Beschreibung:  Einfuegen Fussnote
 Parameter:     rStr -- optionales Fussnotenzeichen
------------------------------------------------------------------------*/


//STRIP001 void SwWrtShell::InsertFootnote(const String &rStr, BOOL bEndNote, BOOL bEdit )
//STRIP001 {
//STRIP001  ResetCursorStack();
//STRIP001  if( _CanInsert() )
//STRIP001  {
//STRIP001      if(HasSelection())
//STRIP001          DelRight();
//STRIP001
//STRIP001      SwFmtFtn aFootNote( bEndNote );
//STRIP001      if(rStr.Len())
//STRIP001          aFootNote.SetNumStr( rStr );
//STRIP001
//STRIP001      SetAttr(aFootNote);
//STRIP001
//STRIP001      if( bEdit )
//STRIP001      {
//STRIP001          // zur Bearbeiung des Fussnotentextes
//STRIP001          Left(CRSR_SKIP_CHARS, FALSE, 1, FALSE );
//STRIP001          GotoFtnTxt();
//STRIP001      }
//STRIP001  }
//STRIP001 }
/*------------------------------------------------------------------------
 Beschreibung:  SplitNode; hier auch, da
                    - selektierter Inhalt geloescht wird;
                    - der Cursorstack gfs. zurueckgesetzt wird.
------------------------------------------------------------------------*/


//STRIP001 void SwWrtShell::SplitNode( BOOL bAutoFmt, BOOL bCheckTableStart )
//STRIP001 {
//STRIP001  ResetCursorStack();
//STRIP001  if( _CanInsert() )
//STRIP001  {
//STRIP001      ACT_KONTEXT(this);
//STRIP001
//STRIP001      rView.GetEditWin().FlushInBuffer( this );
//STRIP001      BOOL bHasSel = HasSelection();
//STRIP001      if( bHasSel )
//STRIP001      {
//STRIP001          StartUndo( UNDO_INSERT );
//STRIP001          DelRight();
//STRIP001      }
//STRIP001
//STRIP001      SwFEShell::SplitNode( bAutoFmt, bCheckTableStart );
//STRIP001      if( bHasSel )
//STRIP001          EndUndo( UNDO_INSERT );
//STRIP001  }
//STRIP001 }

/*------------------------------------------------------------------------
 Beschreibung:  Numerierung anschalten
 Parameter:     Optionale Angabe eines Namens fuer die benannte Liste;
                dieser bezeichnet eine Position, wenn er in eine
                Zahl konvertierbar ist und kleiner ist als nMaxRules.
-------------------------------------------------------------------------*/


// zum Testen der CharFormate an der Numerierung
// extern void SetNumChrFmt( SwWrtShell*, SwNumRules& );

//STRIP001 void SwWrtShell::NumOn()
//STRIP001 {
//STRIP001  SwNumRule aNumRule( GetUniqueNumRuleName() );
//STRIP001
//STRIP001  const SwNumRule* pCurRule = GetCurNumRule();
//STRIP001  if( !pCurRule )
//STRIP001  {
//STRIP001      // Zeichenvorlage an die Numerierung haengen
//STRIP001      SwCharFmt* pChrFmt = GetCharFmtFromPool( RES_POOLCHR_NUM_LEVEL );
//STRIP001      SwDocShell* pDocSh = GetView().GetDocShell();
//STRIP001      BOOL bHtml = 0 != PTR_CAST(SwWebDocShell, pDocSh);
//STRIP001      for( BYTE nLvl = 0; nLvl < MAXLEVEL; ++nLvl )
//STRIP001      {
//STRIP001          SwNumFmt aFmt( aNumRule.Get( nLvl ) );
//STRIP001          aFmt.SetCharFmt( pChrFmt );
//STRIP001          if(bHtml && nLvl)
//STRIP001          {
//STRIP001              // 1/2" fuer HTML
//STRIP001              aFmt.SetLSpace(720);
//STRIP001              aFmt.SetAbsLSpace(nLvl * 720);
//STRIP001          }
//STRIP001          aNumRule.Set( nLvl, aFmt );
//STRIP001      }
//STRIP001      SetCurNumRule( aNumRule );
//STRIP001  }
//STRIP001 }

/*------------------------------------------------------------------------
 Beschreibung:  Default-Bulletliste erfragen
------------------------------------------------------------------------*/

//STRIP001 void SwWrtShell::BulletOn()
//STRIP001 {
//STRIP001  SwNumRule aRule( GetUniqueNumRuleName() );
//STRIP001
//STRIP001  SwCharFmt* pChrFmt = GetCharFmtFromPool( RES_POOLCHR_BUL_LEVEL );
//STRIP001  const Font* pFnt = &SwNumRule::GetDefBulletFont();
//STRIP001
//STRIP001  SwDocShell* pDocSh = GetView().GetDocShell();
//STRIP001  BOOL bHtml = 0 != PTR_CAST(SwWebDocShell, pDocSh);
//STRIP001  for( BYTE n = 0; n < MAXLEVEL; ++n )
//STRIP001  {
//STRIP001      SwNumFmt aFmt( aRule.Get( n ) );
//STRIP001      aFmt.SetBulletFont( pFnt );
//STRIP001      aFmt.SetBulletChar( cBulletChar );
//STRIP001      aFmt.SetNumberingType(SVX_NUM_CHAR_SPECIAL);
//STRIP001      aFmt.SetCharFmt( pChrFmt );
//STRIP001      if(bHtml && n)
//STRIP001      {
//STRIP001          // 1/2" fuer HTML
//STRIP001          aFmt.SetLSpace(720);
//STRIP001          aFmt.SetAbsLSpace(n * 720);
//STRIP001      }
//STRIP001      aRule.Set( n, aFmt );
//STRIP001  }
//STRIP001  SetCurNumRule( aRule );
//STRIP001 }

/*--------------------------------------------------

--------------------------------------------------*/
/*N*/ int SwWrtShell::GetSelectionType() const
/*N*/ {
/*N*/   // ContentType kann nicht ermittelt werden innerhalb einer
/*N*/   // Start-/Endactionklammerung.
/*N*/   // Da es keinen ungueltigen Wert gibt, wird TEXT geliefert.
/*N*/   // Der Wert ist egal, da in EndAction ohnehin aktualisiert wird.
/*N*/
/*N*/   if ( BasicActionPend() )
/*N*/       return IsSelFrmMode() ? SEL_FRM : SEL_TXT;
/*N*/
/*N*/ //    if ( IsTableMode() )
/*N*/ //        return SEL_TBL | SEL_TBL_CELLS;
/*N*/
/*N*/   SwView &rView = ((SwView&)GetView());
/*N*/   USHORT nCnt;
/*N*/
/*N*/   // Rahmen einfuegen ist kein DrawMode
/*N*/   if ( !rView.GetEditWin().IsFrmAction() &&
/*N*/           (IsObjSelected() || (rView.IsDrawMode() && !IsFrmSelected()) ))
/*N*/   {
/*?*/       if (GetDrawView()->IsTextEdit())
/*?*/           nCnt = SEL_DRW_TXT;
/*?*/       else
/*?*/       {
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 if (GetView().IsFormMode())   // Nur Forms selektiert
//STRIP001 /*?*/                nCnt = SEL_DRW_FORM;
//STRIP001 /*?*/            else
//STRIP001 /*?*/                nCnt = SEL_DRW;         // Irgendein Draw-Objekt
//STRIP001 /*?*/
//STRIP001 /*?*/            if (rView.IsBezierEditMode())
//STRIP001 /*?*/                nCnt |= SEL_BEZ;
/*?*/       }
/*?*/
/*?*/       return nCnt;
/*N*/   }
/*N*/
/*N*/   nCnt = GetCntType();
/*N*/
/*N*/   if ( IsFrmSelected() )
/*N*/   {
/*?*/       if (rView.IsDrawMode())
/*?*/           rView.LeaveDrawCreate();    // Aufraeumen (Bug #45639)
/*?*/       if ( !(nCnt & (CNT_GRF | CNT_OLE)) )
/*?*/           return SEL_FRM;
/*N*/   }
/*N*/
/*N*/   if ( IsCrsrInTbl() )
/*N*/       nCnt |= SEL_TBL;
/*N*/
/*N*/   if ( IsTableMode() )
/*N*/       nCnt |= (SEL_TBL | SEL_TBL_CELLS);
/*N*/
/*N*/   if ( GetCurNumRule() )
/*N*/       nCnt |= SEL_NUM;
/*N*/
/*N*/   return nCnt;
/*N*/ }

/*------------------------------------------------------------------------
 Beschreibung:  Finden der TextCollection mit dem Name rCollname
 Return:                Pointer auf die Collection oder 0, wenn keine
                                TextCollection mit diesem Namen existiert oder
                                diese eine Defaultvorlage ist.
------------------------------------------------------------------------*/


//STRIP001 SwTxtFmtColl *SwWrtShell::GetParaStyle(const String &rCollName, GetStyle eCreate )
//STRIP001 {
//STRIP001  SwTxtFmtColl* pColl = FindTxtFmtCollByName( rCollName );
//STRIP001  if( !pColl && GETSTYLE_NOCREATE != eCreate )
//STRIP001  {
//STRIP001      USHORT nId = SwStyleNameMapper::GetPoolIdFromUIName( rCollName, GET_POOLID_TXTCOLL );
//STRIP001      if( USHRT_MAX != nId || GETSTYLE_CREATEANY == eCreate )
//STRIP001          pColl = GetTxtCollFromPool( nId );
//STRIP001  }
//STRIP001  return pColl;
//STRIP001 }
/*------------------------------------------------------------------------
 Beschreibung:  Finden der Zeichenvorlage mit dem Name rCollname
 Return:                Pointer auf die Collection oder 0, wenn keine
                                Zeichenvorlage mit diesem Namen existiert oder
                                diese eine Defaultvorlage oder automatische Vorlage ist.
------------------------------------------------------------------------*/



//STRIP001 SwCharFmt *SwWrtShell::GetCharStyle(const String &rFmtName, GetStyle eCreate )
//STRIP001 {
//STRIP001  SwCharFmt* pFmt = FindCharFmtByName( rFmtName );
//STRIP001  if( !pFmt && GETSTYLE_NOCREATE != eCreate )
//STRIP001  {
//STRIP001      USHORT nId = SwStyleNameMapper::GetPoolIdFromUIName( rFmtName, GET_POOLID_CHRFMT );
//STRIP001      if( USHRT_MAX != nId || GETSTYLE_CREATEANY == eCreate )
//STRIP001          pFmt = (SwCharFmt*)GetFmtFromPool( nId );
//STRIP001  }
//STRIP001  return pFmt;
//STRIP001 }

/*------------------------------------------------------------------------
 Beschreibung:  Finden des Tabellenformates mit dem Name rFmtname
 Return:                Pointer auf das Format oder 0, wenn kein
                                Rahmenformat mit diesem Namen existiert oder
                                dieses eine Defaultformat oder automatisches Format ist.
------------------------------------------------------------------------*/



//STRIP001 SwFrmFmt *SwWrtShell::GetTblStyle(const String &rFmtName)
//STRIP001 {
//STRIP001  SwFrmFmt *pFmt = 0;
//STRIP001  for( USHORT i = GetTblFrmFmtCount(); i; )
//STRIP001      if( !( pFmt = &GetTblFrmFmt( --i ) )->IsDefault() &&
//STRIP001          pFmt->GetName() == rFmtName && IsUsed( *pFmt ) )
//STRIP001          return pFmt;
//STRIP001  return 0;
//STRIP001 }


/*------------------------------------------------------------------------
 Beschreibung:  Anwenden der Vorlagen
------------------------------------------------------------------------*/



//STRIP001 void SwWrtShell::SetPageStyle(const String &rCollName)
//STRIP001 {
//STRIP001  if( !SwCrsrShell::HasSelection() && !IsSelFrmMode() && !IsObjSelected() )
//STRIP001  {
//STRIP001      SwPageDesc* pDesc = FindPageDescByName( rCollName, TRUE );
//STRIP001      if( pDesc )
//STRIP001          ChgCurPageDesc( *pDesc );
//STRIP001  }
//STRIP001 }

/*------------------------------------------------------------------------
 Beschreibung:  Zugriff Vorlagen
------------------------------------------------------------------------*/



/*N*/ String SwWrtShell::GetCurPageStyle( const BOOL bCalcFrm ) const
/*N*/ {
/*N*/   return GetPageDesc(GetCurPageDesc( bCalcFrm )).GetName();
/*N*/ }

/*------------------------------------------------------------------------
 Beschreibung:  Aktuelle Vorlage anhand der geltenden Attribute aendern
------------------------------------------------------------------------*/


//STRIP001 void SwWrtShell::QuickUpdateStyle()
//STRIP001 {
//STRIP001  SwTxtFmtColl *pColl = GetCurTxtFmtColl();
//STRIP001
//STRIP001  // Standard kann nicht geaendert werden
//STRIP001  if(pColl && !pColl->IsDefault())
//STRIP001  {
//STRIP001      FillByEx(pColl);
//STRIP001          // Vorlage auch anwenden, um harte Attributierung
//STRIP001          // zu entfernen
//STRIP001      SetTxtFmtColl(pColl);
//STRIP001  }
//STRIP001 }


//STRIP001 void SwWrtShell::AutoUpdatePara(SwTxtFmtColl* pColl, const SfxItemSet& rStyleSet)
//STRIP001 {
//STRIP001  SfxItemSet aCoreSet( GetAttrPool(),
//STRIP001          RES_CHRATR_BEGIN,           RES_CHRATR_END - 1,
//STRIP001          RES_PARATR_BEGIN,           RES_PARATR_END - 1,
//STRIP001          RES_FRMATR_BEGIN,           RES_FRMATR_END - 1,
//STRIP001          SID_ATTR_TABSTOP_POS,       SID_ATTR_TABSTOP_POS,
//STRIP001          SID_ATTR_TABSTOP_DEFAULTS,  SID_ATTR_TABSTOP_DEFAULTS,
//STRIP001          SID_ATTR_TABSTOP_OFFSET,    SID_ATTR_TABSTOP_OFFSET,
//STRIP001          SID_ATTR_BORDER_INNER,      SID_ATTR_BORDER_INNER,
//STRIP001          SID_ATTR_PARA_MODEL,        SID_ATTR_PARA_KEEP,
//STRIP001          SID_ATTR_PARA_PAGENUM,      SID_ATTR_PARA_PAGENUM,
//STRIP001          0   );
//STRIP001  GetAttr( aCoreSet );
//STRIP001  BOOL bReset = FALSE;
//STRIP001  SfxItemIter aParaIter( aCoreSet );
//STRIP001  const SfxPoolItem* pParaItem = aParaIter.FirstItem();
//STRIP001  while( pParaItem )
//STRIP001  {
//STRIP001      if(!IsInvalidItem(pParaItem))
//STRIP001      {
//STRIP001          USHORT nWhich = pParaItem->Which();
//STRIP001          if(SFX_ITEM_SET == aCoreSet.GetItemState(nWhich) &&
//STRIP001             SFX_ITEM_SET == rStyleSet.GetItemState(nWhich))
//STRIP001          {
//STRIP001              aCoreSet.ClearItem(nWhich);
//STRIP001              bReset = TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001      pParaItem = aParaIter.NextItem();
//STRIP001  }
//STRIP001  StartAction();
//STRIP001  if(bReset)
//STRIP001  {
//STRIP001      ResetAttr();
//STRIP001      SetAttr(aCoreSet);
//STRIP001  }
//STRIP001  pColl->SetAttr( rStyleSet );
//STRIP001  EndAction();
//STRIP001 }

/*-----------------12.03.97 12.24-------------------

--------------------------------------------------*/

//STRIP001 void SwWrtShell::AutoUpdateFrame( SwFrmFmt* pFmt, const SfxItemSet& rStyleSet )
//STRIP001 {
//STRIP001  StartAction();
//STRIP001
//STRIP001  ResetFlyFrmAttr( 0, &rStyleSet );
//STRIP001  pFmt->SetAttr( rStyleSet );
//STRIP001
//STRIP001  EndAction();
//STRIP001 }


//STRIP001 void SwWrtShell::AutoCorrect( SvxAutoCorrect& rACorr, sal_Unicode cChar )
//STRIP001 {
//STRIP001  ResetCursorStack();
//STRIP001  if(_CanInsert())
//STRIP001  {
//STRIP001      BOOL bStarted = FALSE;
//STRIP001      if(HasSelection())
//STRIP001      {
//STRIP001              // nur hier klammern, da das normale Insert schon an der
//STRIP001              // Editshell geklammert ist
//STRIP001          StartAllAction();
//STRIP001          StartUndo(UNDO_INSERT);
//STRIP001          bStarted = TRUE;
//STRIP001          DelRight();
//STRIP001      }
//STRIP001      SwEditShell::AutoCorrect( rACorr, IsInsMode(), cChar );
//STRIP001
//STRIP001      if(bStarted)
//STRIP001      {
//STRIP001          EndAllAction();
//STRIP001          EndUndo(UNDO_INSERT);
//STRIP001      }
//STRIP001  }
//STRIP001 }


/*
 * eine Art kontrollierter copy ctor
 */

/*?*/ SwWrtShell::SwWrtShell( SwWrtShell& rSh, Window *pWin, SwView &rShell )
/*?*/   : SwFEShell( rSh, pWin ),
/*?*/    COMMON_INI_LIST
/*?*/ {
/*?*/   BITFLD_INI_LIST
/*?*/   SET_CURR_SHELL( this );
/*?*/   SetSfxViewShell( (SfxViewShell *)&rShell );
/*?*/   SetFlyMacroLnk( LINK(this, SwWrtShell, ExecFlyMac) );
/*?*/ }


/*N*/ SwWrtShell::SwWrtShell( SwDoc& rDoc, Window *pWin, SwView &rShell,
/*N*/                       SwRootFrm *pRoot, const SwViewOption *pViewOpt )
/*N*/   : SwFEShell( rDoc, pWin, pRoot, pViewOpt),
/*N*/     COMMON_INI_LIST
/*N*/ {
/*N*/   BITFLD_INI_LIST
/*N*/   SET_CURR_SHELL( this );
/*N*/   SetSfxViewShell( (SfxViewShell *)&rShell );
/*N*/   SetFlyMacroLnk( LINK(this, SwWrtShell, ExecFlyMac) );
/*N*/ }

/*
 * ctor
 */



/*N*/ SwWrtShell::~SwWrtShell()
/*N*/ {
/*N*/   SET_CURR_SHELL( this );
/*N*/   while(IsModePushed())
/*?*/   {DBG_BF_ASSERT(0, "STRIP");} //STRIP001     PopMode();
/*N*/   while(PopCrsr(FALSE))
/*N*/       ;
/*N*/   SwTransferable::ClearSelection( *this );
/*N*/ }




//STRIP001 void SwWrtShell::StartBasicAction()
//STRIP001 {
//STRIP001  IncBasicAction();
//STRIP001  StartAllAction();
//STRIP001 }



//STRIP001 void SwWrtShell::SetBasicActionCount(USHORT nSet)
//STRIP001 {
//STRIP001  DBG_ASSERT(!GetBasicActionCnt(), "Es sind schon Actions offen!")
//STRIP001  while( nSet )
//STRIP001  {
//STRIP001      IncBasicAction();
//STRIP001      StartAllAction();
//STRIP001      nSet--;
//STRIP001  }
//STRIP001 }



//STRIP001 void SwWrtShell::EndBasicAction()
//STRIP001 {
//STRIP001  if(GetBasicActionCnt())
//STRIP001  {
//STRIP001      DecBasicAction();
//STRIP001      EndAllAction();
//STRIP001  }
//STRIP001 }



//STRIP001 USHORT SwWrtShell::EndAllBasicActions()
//STRIP001 {
//STRIP001  USHORT nRet = GetBasicActionCnt();
//STRIP001  while( GetBasicActionCnt() )
//STRIP001  {
//STRIP001      DecBasicAction();
//STRIP001      EndAllAction();
//STRIP001  }
//STRIP001  return nRet;
//STRIP001 }



//STRIP001 FASTBOOL SwWrtShell::Pop( BOOL bOldCrsr )
//STRIP001 {
//STRIP001  FASTBOOL bRet = SwCrsrShell::Pop( bOldCrsr );
//STRIP001  if( bRet && IsSelection() )
//STRIP001  {
//STRIP001      fnSetCrsr = &SwWrtShell::SetCrsrKillSel;
//STRIP001      fnKillSel = &SwWrtShell::ResetSelect;
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/



//STRIP001 BOOL SwWrtShell::CanInsert()
//STRIP001 {
//STRIP001  return (!(IsSelFrmMode() | IsObjSelected() | (GetView().GetDrawFuncPtr() != NULL)));
//STRIP001 }



    // die Core erzeugt eine Selektion, das SttSelect muss gerufen werden
//STRIP001 void SwWrtShell::NewCoreSelection()
//STRIP001 {
//STRIP001  SttSelect();
//STRIP001 }

// --------------
/*N*/ void SwWrtShell::ChgDBData(const SwDBData& aDBData)
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001     SwEditShell::ChgDBData(aDBData);
//STRIP001     //notify the db-beamer if available
//STRIP001     GetView().NotifyDBChanged();
/*N*/ }




}
