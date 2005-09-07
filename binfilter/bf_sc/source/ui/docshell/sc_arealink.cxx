/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sc_arealink.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 19:05:43 $
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

#ifdef PCH
// auto strip #include "ui_pch.hxx"
#endif

#pragma hdrstop

// INCLUDE ---------------------------------------------------------

#include <bf_sfx2/app.hxx>
#include <bf_sfx2/docfile.hxx>
// auto strip #include <bf_svx/linkmgr.hxx>
#include <svtools/stritem.hxx>
#include <vcl/msgbox.hxx>

#include "arealink.hxx"

#include "tablink.hxx"
// auto strip #include "document.hxx"
#include "docsh.hxx"
#include "rangenam.hxx"
#include "dbcolect.hxx"
// auto strip #include "undoblk.hxx"
#include "globstr.hrc"
#include "markdata.hxx"
#include "hints.hxx"
// auto strip #include "htmlimp.hxx"
// auto strip #include "linkarea.hxx"           // dialog

#include "attrib.hxx"           // raus, wenn ResetAttrib am Dokument
#include "patattr.hxx"          // raus, wenn ResetAttrib am Dokument
#include "docpool.hxx"          // raus, wenn ResetAttrib am Dokument
namespace binfilter {

/*N*/ TYPEINIT1(ScAreaLink,::so3::SvBaseLink);

//------------------------------------------------------------------------

/*N*/ ScAreaLink::ScAreaLink( SfxObjectShell* pShell, const String& rFile,
/*N*/                       const String& rFilter, const String& rOpt,
/*N*/                       const String& rArea, const ScRange& rDest,
/*N*/                       ULONG nRefresh ) :
/*N*/   ::so3::SvBaseLink(so3::LINKUPDATE_ONCALL,FORMAT_FILE),
/*N*/   ScRefreshTimer  ( nRefresh ),
/*N*/   pDocShell       ((ScDocShell*)pShell),
/*N*/   aFileName       (rFile),
/*N*/   aFilterName     (rFilter),
/*N*/   aOptions        (rOpt),
/*N*/   aSourceArea     (rArea),
/*N*/   aDestArea       (rDest),
/*N*/   bAddUndo        (TRUE),
/*N*/   bInCreate       (FALSE),
/*N*/   bDoInsert       (TRUE)
/*N*/ {
/*N*/   DBG_ASSERT(pShell->ISA(ScDocShell), "ScAreaLink mit falscher ObjectShell");
/*N*/   SetRefreshHandler( LINK( this, ScAreaLink, RefreshHdl ) );
/*N*/   SetRefreshControl( pDocShell->GetDocument()->GetRefreshTimerControlAddress() );
/*N*/ }

/*N*/ __EXPORT ScAreaLink::~ScAreaLink()
/*N*/ {
/*N*/   StopRefreshTimer();
/*N*/ }

//STRIP001 BOOL __EXPORT ScAreaLink::Edit(Window* pParent)
//STRIP001 {
//STRIP001  //  use own dialog instead of SvBaseLink::Edit...
//STRIP001  //  DefModalDialogParent setzen, weil evtl. aus der DocShell beim ConvertFrom
//STRIP001  //  ein Optionen-Dialog kommt...
//STRIP001
//STRIP001  BOOL bRet = FALSE;
//STRIP001  ScLinkedAreaDlg* pDlg = new ScLinkedAreaDlg( pParent );
//STRIP001  pDlg->InitFromOldLink( aFileName, aFilterName, aOptions, aSourceArea, GetRefreshDelay() );
//STRIP001  if (pDlg->Execute() == RET_OK)
//STRIP001  {
//STRIP001      aOptions = pDlg->GetOptions();
//STRIP001      bRet = Refresh( pDlg->GetURL(), pDlg->GetFilter(), pDlg->GetSource(), pDlg->GetRefresh() );
//STRIP001
//STRIP001      //  copy source data from members (set in Refresh) into link name for dialog
//STRIP001      String aLinkName;
//STRIP001      ::so3::MakeLnkName( aLinkName, NULL, aFileName, aSourceArea, &aFilterName );
//STRIP001      SetName( aLinkName );
//STRIP001  }
//STRIP001  delete pDlg;
//STRIP001
//STRIP001  return bRet;
//STRIP001 }

/*N*/  void __EXPORT ScAreaLink::DataChanged( const String&,
/*N*/                                      const ::com::sun::star::uno::Any& )
/*N*/ {
        DBG_BF_ASSERT(0, "STRIP"); //STRIP001 /*?*/     //  bei bInCreate nichts tun, damit Update gerufen werden kann, um den Status im
//STRIP001  //  LinkManager zu setzen, ohne die Daten im Dokument zu aendern
//STRIP001
//STRIP001  if (bInCreate)
//STRIP001      return;
//STRIP001
//STRIP001  SvxLinkManager* pLinkManager=pDocShell->GetDocument()->GetLinkManager();
//STRIP001  if (pLinkManager!=NULL)
//STRIP001  {
//STRIP001      String aFile;
//STRIP001      String aFilter;
//STRIP001      String aArea;
//STRIP001      pLinkManager->GetDisplayNames( this,0,&aFile,&aArea,&aFilter);
//STRIP001
//STRIP001      //  the file dialog returns the filter name with the application prefix
//STRIP001      //  -> remove prefix
//STRIP001      ScDocumentLoader::RemoveAppPrefix( aFilter );
//STRIP001
//STRIP001      // #81155# dialog doesn't set area, so keep old one
//STRIP001      if ( !aArea.Len() )
//STRIP001      {
//STRIP001          aArea = aSourceArea;
//STRIP001
//STRIP001          // adjust in dialog:
//STRIP001          String aLinkName;
//STRIP001          ::so3::MakeLnkName( aLinkName, NULL, aFile, aArea, &aFilter );
//STRIP001          SetName( aLinkName );
//STRIP001      }
//STRIP001
//STRIP001      Refresh( aFile, aFilter, aArea, GetRefreshDelay() );
//STRIP001  }
/*N*/ }

//STRIP001 void __EXPORT ScAreaLink::Closed()
//STRIP001 {
//STRIP001  // Verknuepfung loeschen: Undo
//STRIP001
//STRIP001  ScDocument* pDoc = pDocShell->GetDocument();
//STRIP001  BOOL bUndo (pDoc->IsUndoEnabled());
//STRIP001  if (bAddUndo && bUndo)
//STRIP001  {
//STRIP001      pDocShell->GetUndoManager()->AddUndoAction( new ScUndoRemoveAreaLink( pDocShell,
//STRIP001                                                      aFileName, aFilterName, aOptions,
//STRIP001                                                      aSourceArea, aDestArea, GetRefreshDelay() ) );
//STRIP001
//STRIP001      bAddUndo = FALSE;   // nur einmal
//STRIP001  }
//STRIP001
//STRIP001  SvBaseLink::Closed();
//STRIP001 }

/*N*/ void ScAreaLink::SetDestArea(const ScRange& rNew)
/*N*/ {
/*N*/   aDestArea = rNew;           // fuer Undo
/*N*/ }

//STRIP001 void ScAreaLink::SetSource(const String& rDoc, const String& rFlt, const String& rOpt,
//STRIP001                              const String& rArea)
//STRIP001 {
//STRIP001  aFileName   = rDoc;
//STRIP001  aFilterName = rFlt;
//STRIP001  aOptions    = rOpt;
//STRIP001  aSourceArea = rArea;
//STRIP001
//STRIP001  //  also update link name for dialog
//STRIP001  String aLinkName;
//STRIP001  ::so3::MakeLnkName( aLinkName, NULL, aFileName, aSourceArea, &aFilterName );
//STRIP001  SetName( aLinkName );
//STRIP001 }

//STRIP001 BOOL ScAreaLink::IsEqual( const String& rFile, const String& rFilter, const String& rOpt,
//STRIP001                          const String& rSource, const ScRange& rDest ) const
//STRIP001 {
//STRIP001  return aFileName == rFile && aFilterName == rFilter && aOptions == rOpt &&
//STRIP001          aSourceArea == rSource && aDestArea.aStart == rDest.aStart;
//STRIP001 }

// find a range with name >rAreaName< in >pSrcDoc<, return it in >rRange<
/*N*/ BOOL ScAreaLink::FindExtRange( ScRange& rRange, ScDocument* pSrcDoc, const String& rAreaName )
/*N*/ {
/*N*/   BOOL bFound = FALSE;
/*N*/   ScRangeName* pNames = pSrcDoc->GetRangeName();
/*N*/   USHORT nPos;
/*N*/   if (pNames)         // benannte Bereiche
/*N*/   {
/*N*/       if (pNames->SearchName( rAreaName, nPos ))
/*N*/           if ( (*pNames)[nPos]->IsReference( rRange ) )
/*N*/               bFound = TRUE;
/*N*/   }
/*N*/   if (!bFound)        // Datenbankbereiche
/*N*/   {
/*N*/       ScDBCollection* pDBColl = pSrcDoc->GetDBCollection();
/*N*/       if (pDBColl)
/*N*/           if (pDBColl->SearchName( rAreaName, nPos ))
/*N*/           {
/*N*/               USHORT nTab,nCol1,nRow1,nCol2,nRow2;
/*N*/               (*pDBColl)[nPos]->GetArea(nTab,nCol1,nRow1,nCol2,nRow2);
/*N*/               rRange = ScRange( nCol1,nRow1,nTab, nCol2,nRow2,nTab );
/*N*/               bFound = TRUE;
/*N*/           }
/*N*/   }
/*N*/   if (!bFound)        // direct reference (range or cell)
/*N*/   {
/*N*/       if ( rRange.ParseAny( rAreaName, pSrcDoc ) & SCA_VALID )
/*N*/           bFound = TRUE;
/*N*/   }
/*N*/   return bFound;
/*N*/ }

//  ausfuehren:

/*N*/ BOOL ScAreaLink::Refresh( const String& rNewFile, const String& rNewFilter,
/*N*/                           const String& rNewArea, ULONG nNewRefresh )
/*N*/ {
/*N*/   //  Dokument laden - wie TabLink
/*N*/
/*N*/   if (!rNewFile.Len() || !rNewFilter.Len())
/*N*/       return FALSE;
/*N*/
/*N*/   String aNewUrl( ScGlobal::GetAbsDocName( rNewFile, pDocShell ) );
/*N*/   BOOL bNewUrlName = (aNewUrl != aFileName);
/*N*/
/*N*/   const SfxFilter* pFilter = SFX_APP()->GetFilter( pDocShell->GetFactory(), rNewFilter );
/*N*/   if (!pFilter)
/*N*/       return FALSE;
/*N*/
/*N*/   ScDocument* pDoc = pDocShell->GetDocument();
/*N*/
/*N*/   BOOL bUndo (pDoc->IsUndoEnabled());
/*N*/   pDoc->SetInLinkUpdate( TRUE );
/*N*/
/*N*/   //  wenn neuer Filter ausgewaehlt wurde, Optionen vergessen
/*N*/   if ( rNewFilter != aFilterName )
/*N*/       aOptions.Erase();
/*N*/
/*N*/   //  ItemSet immer anlegen, damit die DocShell die Optionen setzen kann
/*N*/   SfxItemSet* pSet = new SfxAllItemSet( SFX_APP()->GetPool() );
/*N*/   if ( aOptions.Len() )
/*N*/       pSet->Put( SfxStringItem( SID_FILE_FILTEROPTIONS, aOptions ) );
/*N*/
/*N*/   SfxMedium* pMed = new SfxMedium(aNewUrl, STREAM_STD_READ, FALSE, pFilter);
/*N*/
/*N*/   ScDocShell* pSrcShell = new ScDocShell(SFX_CREATE_MODE_INTERNAL);
/*N*/   SvEmbeddedObjectRef aRef = pSrcShell;
/*N*/   pSrcShell->DoLoad(pMed);
/*N*/
/*N*/   ScDocument* pSrcDoc = pSrcShell->GetDocument();
/*N*/
/*N*/   // Optionen koennten gesetzt worden sein
/*N*/   String aNewOpt = ScDocumentLoader::GetOptions(*pMed);
/*N*/   if (!aNewOpt.Len())
/*N*/       aNewOpt = aOptions;
/*N*/
/*N*/   // correct source range name list for web query import
/*N*/   String aTempArea;
/*N*/
/*N*/   if( rNewFilter == ScDocShell::GetWebQueryFilterName() )
/*?*/           {DBG_BF_ASSERT(0, "STRIP");} //STRIP001 /*?*/       aTempArea = ScHTMLImport::GetHTMLRangeNameList( pSrcDoc, rNewArea );
/*N*/   else
/*N*/       aTempArea = rNewArea;
/*N*/
/*N*/   // find total size of source area
/*N*/   USHORT nWidth = 0;
/*N*/   USHORT nHeight = 0;
/*N*/   xub_StrLen nTokenCnt = aTempArea.GetTokenCount( ';' );
/*N*/   xub_StrLen nStringIx = 0;
/*N*/   xub_StrLen nToken;
/*N*/
/*N*/   for( nToken = 0; nToken < nTokenCnt; nToken++ )
/*N*/   {
/*N*/       String aToken( aTempArea.GetToken( 0, ';', nStringIx ) );
/*N*/       ScRange aTokenRange;
/*N*/       if( FindExtRange( aTokenRange, pSrcDoc, aToken ) )
/*N*/       {
/*N*/           // columns: find maximum
/*N*/           nWidth = Max( nWidth, (USHORT)(aTokenRange.aEnd.Col() - aTokenRange.aStart.Col() + 1) );
/*N*/           // rows: add row range + 1 empty row
/*N*/           nHeight += aTokenRange.aEnd.Row() - aTokenRange.aStart.Row() + 2;
/*N*/       }
/*N*/   }
/*N*/   // remove the last empty row
/*N*/   if( nHeight )
/*N*/       nHeight--;
/*N*/
/*N*/   //  alte Daten loeschen / neue kopieren
/*N*/
/*N*/   ScAddress aDestPos = aDestArea.aStart;
/*N*/   USHORT nDestTab = aDestPos.Tab();
/*N*/   ScRange aOldRange = aDestArea;
/*N*/   ScRange aNewRange = aDestArea;          // alter Bereich, wenn Datei nicht gefunden o.ae.
/*N*/   if (nWidth && nHeight)
/*N*/   {
/*N*/       aNewRange.aEnd.SetCol( aNewRange.aStart.Col() + nWidth - 1 );
/*N*/       aNewRange.aEnd.SetRow( aNewRange.aStart.Row() + nHeight - 1 );
/*N*/   }
/*N*/
/*N*/   BOOL bCanDo = pDoc->CanFitBlock( aOldRange, aNewRange );    //! nach bDoInsert unterscheiden
/*N*/   if (bCanDo)
/*N*/   {
/*N*/       ScDocShellModificator aModificator( *pDocShell );
/*N*/
/*N*/       USHORT nStartX = aDestPos.Col();
/*N*/       USHORT nStartY = aDestPos.Row();
/*N*/       USHORT nOldEndX = aOldRange.aEnd.Col();
/*N*/       USHORT nOldEndY = aOldRange.aEnd.Row();
/*N*/       USHORT nNewEndX = aNewRange.aEnd.Col();
/*N*/       USHORT nNewEndY = aNewRange.aEnd.Row();
/*N*/       ScRange aMaxRange( aDestPos,
/*N*/                   ScAddress(Max(nOldEndX,nNewEndX), Max(nOldEndY,nNewEndY), nDestTab) );
/*N*/
/*N*/       //  Undo initialisieren
/*N*/
/*N*/       ScDocument* pUndoDoc = NULL;
/*N*/       ScDocument* pRedoDoc = NULL;
/*N*/       if ( bAddUndo && bUndo )
/*N*/       {
/*N*/           pUndoDoc = new ScDocument( SCDOCMODE_UNDO );
/*N*/           if ( bDoInsert )
/*N*/           {
/*N*/               if ( nNewEndX != nOldEndX || nNewEndY != nOldEndY )             // Bereich veraendert?
/*N*/               {
/*N*/                   pUndoDoc->InitUndo( pDoc, 0, pDoc->GetTableCount()-1 );
/*N*/                   pDoc->CopyToDocument( 0,0,0,MAXCOL,MAXROW,MAXTAB,
/*N*/                                           IDF_FORMULA, FALSE, pUndoDoc );     // alle Formeln
/*N*/               }
/*N*/               else
/*N*/                   pUndoDoc->InitUndo( pDoc, nDestTab, nDestTab );             // nur Zieltabelle
/*N*/               pDoc->CopyToDocument( aOldRange, IDF_ALL, FALSE, pUndoDoc );
/*N*/           }
/*N*/           else        // ohne Einfuegen
/*N*/           {
/*N*/               pUndoDoc->InitUndo( pDoc, nDestTab, nDestTab );             // nur Zieltabelle
/*N*/               pDoc->CopyToDocument( aMaxRange, IDF_ALL, FALSE, pUndoDoc );
/*N*/           }
/*N*/       }
/*N*/
/*N*/       //  Zellen einfuegen / loeschen
/*N*/       //  DeleteAreaTab loescht auch MERGE_FLAG Attribute
/*N*/
/*N*/       if (bDoInsert)
/*N*/           pDoc->FitBlock( aOldRange, aNewRange );         // incl. loeschen
/*N*/       else
/*N*/           pDoc->DeleteAreaTab( aMaxRange, IDF_ALL );
/*N*/
/*N*/       //  Daten kopieren
/*N*/
/*N*/       if (nWidth && nHeight)
/*N*/       {
/*N*/           ScDocument aClipDoc( SCDOCMODE_CLIP );
/*N*/           ScRange aNewTokenRange( aNewRange.aStart );
/*N*/           nStringIx = 0;
/*N*/           for( nToken = 0; nToken < nTokenCnt; nToken++ )
/*N*/           {
/*N*/               String aToken( aTempArea.GetToken( 0, ';', nStringIx ) );
/*N*/               ScRange aTokenRange;
/*N*/               if( FindExtRange( aTokenRange, pSrcDoc, aToken ) )
/*N*/               {
/*N*/                   USHORT nSrcTab = aTokenRange.aStart.Tab();
/*N*/                   ScMarkData aSourceMark;
/*N*/                   aSourceMark.SelectOneTable( nSrcTab );      // selektieren fuer CopyToClip
/*N*/                   aSourceMark.SetMarkArea( aTokenRange );
/*N*/
/*N*/                   pSrcDoc->CopyToClip( aTokenRange.aStart.Col(), aTokenRange.aStart.Row(),
/*N*/                                        aTokenRange.aEnd.Col(), aTokenRange.aEnd.Row(),
/*N*/                                        FALSE, &aClipDoc, FALSE, &aSourceMark );
/*N*/
/*N*/                   if ( aClipDoc.HasAttrib( 0,0,nSrcTab, MAXCOL,MAXROW,nSrcTab,
/*N*/                                           HASATTR_MERGED | HASATTR_OVERLAPPED ) )
/*N*/                   {
/*N*/                       //! ResetAttrib am Dokument !!!
/*N*/
/*N*/                       ScPatternAttr aPattern( pSrcDoc->GetPool() );
/*N*/                       aPattern.GetItemSet().Put( ScMergeAttr() );             // Defaults
/*N*/                       aPattern.GetItemSet().Put( ScMergeFlagAttr() );
/*N*/                       aClipDoc.ApplyPatternAreaTab( 0,0, MAXCOL,MAXROW, nSrcTab, aPattern );
/*N*/                   }
/*N*/
/*N*/                   aNewTokenRange.aEnd.SetCol( aNewTokenRange.aStart.Col() + (aTokenRange.aEnd.Col() - aTokenRange.aStart.Col()) );
/*N*/                   aNewTokenRange.aEnd.SetRow( aNewTokenRange.aStart.Row() + (aTokenRange.aEnd.Row() - aTokenRange.aStart.Row()) );
/*N*/                   ScMarkData aDestMark;
/*N*/                   aDestMark.SelectOneTable( nDestTab );
/*N*/                   aDestMark.SetMarkArea( aNewTokenRange );
/*N*/                   pDoc->CopyFromClip( aNewTokenRange, aDestMark, IDF_ALL, NULL, &aClipDoc, FALSE );
/*N*/                   aNewTokenRange.aStart.SetRow( aNewTokenRange.aEnd.Row() + 2 );
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           String aErr = ScGlobal::GetRscString(STR_LINKERROR);
/*N*/           pDoc->SetString( aDestPos.Col(), aDestPos.Row(), aDestPos.Tab(), aErr );
/*N*/       }
/*N*/
/*N*/       //  Undo eintragen
/*N*/
/*N*/       if ( bAddUndo && bUndo)
/*N*/       {
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 pRedoDoc = new ScDocument( SCDOCMODE_UNDO );
//STRIP001 /*?*/            pRedoDoc->InitUndo( pDoc, nDestTab, nDestTab );
//STRIP001 /*?*/            pDoc->CopyToDocument( aNewRange, IDF_ALL, FALSE, pRedoDoc );
//STRIP001 /*?*/
//STRIP001 /*?*/            pDocShell->GetUndoManager()->AddUndoAction(
//STRIP001 /*?*/                new ScUndoUpdateAreaLink( pDocShell,
//STRIP001 /*?*/                                            aFileName, aFilterName, aOptions,
//STRIP001 /*?*/                                            aSourceArea, aOldRange, GetRefreshDelay(),
//STRIP001 /*?*/                                            aNewUrl, rNewFilter, aNewOpt,
//STRIP001 /*?*/                                            rNewArea, aNewRange, nNewRefresh,
//STRIP001 /*?*/                                            pUndoDoc, pRedoDoc, bDoInsert ) );
/*N*/       }
/*N*/
/*N*/       //  neue Einstellungen merken
/*N*/
/*N*/       if ( bNewUrlName )
/*N*/           aFileName = aNewUrl;
/*N*/       if ( rNewFilter != aFilterName )
/*N*/           aFilterName = rNewFilter;
/*N*/       if ( rNewArea != aSourceArea )
/*N*/           aSourceArea = rNewArea;
/*N*/       if ( aNewOpt != aOptions )
/*N*/           aOptions = aNewOpt;
/*N*/
/*N*/       if ( aNewRange != aDestArea )
/*N*/           aDestArea = aNewRange;
/*N*/
/*N*/       if ( nNewRefresh != GetRefreshDelay() )
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 SetRefreshDelay( nNewRefresh );
/*N*/
/*N*/       USHORT nPaintEndX = Max( aOldRange.aEnd.Col(), aNewRange.aEnd.Col() );
/*N*/       USHORT nPaintEndY = Max( aOldRange.aEnd.Row(), aNewRange.aEnd.Row() );
/*N*/
/*N*/       if ( aOldRange.aEnd.Col() != aNewRange.aEnd.Col() )
/*N*/           nPaintEndX = MAXCOL;
/*N*/       if ( aOldRange.aEnd.Row() != aNewRange.aEnd.Row() )
/*N*/           nPaintEndY = MAXROW;
/*N*/
/*N*/       if ( !pDocShell->AdjustRowHeight( aDestPos.Row(), nPaintEndY, nDestTab ) )
/*N*/           pDocShell->PostPaint( aDestPos.Col(),aDestPos.Row(),nDestTab,
/*N*/                                   nPaintEndX,nPaintEndY,nDestTab, PAINT_GRID );
/*N*/       aModificator.SetDocumentModified();
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       //  CanFitBlock FALSE -> Probleme mit zusammengefassten Zellen
/*N*/       //                       oder Tabellengrenze erreicht!
/*N*/       //! Zellschutz ???
/*N*/
/*N*/       //! Link-Dialog muss Default-Parent setzen
/*N*/       //  "kann keine Zeilen einfuegen"
/*N*/       InfoBox aBox( Application::GetDefDialogParent(),
/*N*/                       ScGlobal::GetRscString( STR_MSSG_DOSUBTOTALS_2 ) );
/*N*/       aBox.Execute();
/*N*/   }
/*N*/
/*N*/   //  aufraeumen
/*N*/
/*N*/   aRef->DoClose();
/*N*/
/*N*/   pDoc->SetInLinkUpdate( FALSE );
/*N*/
/*N*/   if (bCanDo)
/*N*/   {
/*N*/       //  notify Uno objects (for XRefreshListener)
/*N*/       //! also notify Uno objects if file name was changed!
/*N*/       ScLinkRefreshedHint aHint;
/*N*/       aHint.SetAreaLink( aDestPos );
/*N*/       pDoc->BroadcastUno( aHint );
/*N*/   }
/*N*/
/*N*/   return bCanDo;
/*N*/ }


/*N*/ IMPL_LINK( ScAreaLink, RefreshHdl, ScAreaLink*, pCaller )
/*N*/ {
    DBG_BF_ASSERT(0, "STRIP"); return 0; //STRIP001 long nRes = Refresh( aFileName, aFilterName, aSourceArea,
//STRIP001      GetRefreshDelay() ) != 0;
//STRIP001  return nRes;
/*N*/ }

}
