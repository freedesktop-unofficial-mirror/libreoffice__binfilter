/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sd_drawdoc.cxx,v $
 *
 *  $Revision: 1.10 $
 *
 *  last change: $Author: obo $ $Date: 2007-03-09 14:32:11 $
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

#define ITEMID_SEARCH           SID_SEARCH_ITEM

#ifndef _COM_SUN_STAR_TEXT_WRITINGMODE_HPP_
#include <com/sun/star/text/WritingMode.hpp>
#endif
#ifndef _COM_SUN_STAR_DOCUMENT_PRINTERINDEPENDENTLAYOUT_HPP_
#include <com/sun/star/document/PrinterIndependentLayout.hpp>
#endif

#ifndef _FORBIDDENCHARACTERSTABLE_HXX
#include <bf_svx/forbiddencharacterstable.hxx>
#endif

#include <bf_svx/svxids.hrc>

#ifndef _OSPLCFG_HXX
#include <bf_offmgr/osplcfg.hxx>
#endif
#ifndef _OFA_MISCCFG_HXX
#include <bf_sfx2/misccfg.hxx>
#endif
#ifndef _SFX_PRINTER_HXX //autogen
#include <bf_sfx2/printer.hxx>
#endif
#ifndef _SFX_TOPFRM_HXX //autogen wg. SfxTopViewFrame
#include <bf_sfx2/topfrm.hxx>
#endif
#include <bf_sfx2/app.hxx>
#include <bf_offmgr/app.hxx>
#include <bf_svx/linkmgr.hxx>
#include <bf_svx/dialogs.hrc>
#include "sdoutl.hxx"

#ifndef _EEITEM_HXX //autogen
#include <bf_svx/eeitem.hxx>
#endif
#ifndef _EEITEMID_HXX //autogen
#include <bf_svx/eeitemid.hxx>
#endif
#ifndef _EDITSTAT_HXX //autogen
#include <bf_svx/editstat.hxx>
#endif
#ifndef _SVX_FONTITEM_HXX //autogen
#include <bf_svx/fontitem.hxx>
#endif
#ifndef _SFXFLAGITEM_HXX //autogen
#include <svtools/flagitem.hxx>
#endif
#ifndef _SVDOATTR_HXX //autogen
#include <bf_svx/svdoattr.hxx>
#endif
#ifndef _SVDOTEXT_HXX //autogen
#include <bf_svx/svdotext.hxx>
#endif
#ifndef _SVX_BULITEM_HXX //autogen
#include <bf_svx/bulitem.hxx>
#endif
#ifndef _SVX_NUMITEM_HXX //autogen
#include <bf_svx/numitem.hxx>
#endif
#ifndef _SVDITER_HXX //autogen
#include <bf_svx/svditer.hxx>
#endif
#ifndef _UNO_LINGU_HXX
#include <bf_svx/unolingu.hxx>
#endif
#ifndef _SFXITEMPOOL_HXX //autogen wg. SfxItemPool
#include <svtools/itempool.hxx>
#endif
#ifndef _COM_SUN_STAR_LANG_XMULTISERVICEFACTORY_HPP_
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#endif
#include <bf_svx/xtable.hxx>
#ifndef _COM_SUN_STAR_LINGUISTIC2_XHYPHENATOR_HPP_
#include <com/sun/star/linguistic2/XHyphenator.hpp>
#endif
#ifndef _COM_SUN_STAR_LINGUISTIC2_XSPELLCHECKER1_HPP_
#include <com/sun/star/linguistic2/XSpellChecker1.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
#include <com/sun/star/beans/XPropertySet.hpp>
#endif
#ifndef _OUTLOBJ_HXX
#include <bf_svx/outlobj.hxx>
#endif
#ifndef INCLUDED_SVTOOLS_SAVEOPT_HXX
#include <svtools/saveopt.hxx>
#endif
#include <comphelper/extract.hxx>
#ifndef _XCEPTION_HXX_
#include <vos/xception.hxx>
#endif
#ifndef INCLUDED_I18NPOOL_MSLANGID_HXX
#include <i18npool/mslangid.hxx>
#endif
#include <unotools/charclass.hxx>
#ifndef _COMPHELPER_PROCESSFACTORY_HXX_
#include <comphelper/processfactory.hxx>
#endif
#ifndef _SVTOOLS_PATHOPTIONS_HXX_
#include <svtools/pathoptions.hxx>
#endif
#ifndef _SVTOOLS_LINGUCFG_HXX_
#include <svtools/lingucfg.hxx>
#endif
#ifndef _SVTOOLS_LINGUPROPS_HXX_
#include <svtools/linguprops.hxx>
#endif

#include "eetext.hxx"
#include "drawdoc.hxx"
#include "sdpage.hxx"
#include "pglink.hxx"
#include "sdattr.hxx"
#include "glob.hrc"
#include "glob.hxx"
#include "stlpool.hxx"
#include "sdiocmpt.hxx"
#include "sdresid.hxx"
#include "cusshow.hxx"

#ifndef MAC
#include "../ui/inc/docshell.hxx"
#include "../ui/inc/grdocsh.hxx"
#include "../ui/inc/sdxfer.hxx"
#include "../ui/inc/viewshel.hxx"
#include "../ui/inc/grdocsh.hxx"
#include "../ui/inc/optsitem.hxx"
#include "../ui/inc/frmview.hxx"
#else
#include "docshell.hxx"
#include "grdocsh.hxx"
#include "sdresid.hxx"
#include "sdxfer.hxx"
#include "viewshel.hxx"
#include "grdocsh.hxx"
#include "optsitem.hxx"
#include "frmview.hxx"
#endif

#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif

// #90477#
#ifndef _TOOLS_TENCCVT_HXX
#include <tools/tenccvt.hxx>
#endif

#ifndef _SFX_SRCHITEM_HXX
#include <bf_sfx2/srchitem.hxx>
#endif

namespace binfilter {

using namespace ::rtl;
using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::linguistic2;

/*N*/ TYPEINIT1( SdDrawDocument, FmFormModel );

/*N*/ SdDrawDocument* SdDrawDocument::pDocLockedInsertingLinks = NULL;

/*************************************************************************
|*
|* Konstruktor
|*
\************************************************************************/

/*N*/ SdDrawDocument::SdDrawDocument(DocumentType eType, SfxObjectShell* pDrDocSh) :
/*N*/   FmFormModel(
/*N*/   SvtPathOptions().GetPalettePath(),
/*N*/   NULL, (SvPersist*)pDrDocSh ),
/*N*/   eDocType(eType),
/*N*/   pDocSh( (SdDrawDocShell*) pDrDocSh ),
/*N*/     pCreatingTransferable( NULL ),
/*N*/   bPresAll(TRUE),
/*N*/   bPresEndless(FALSE),
/*N*/   bPresManual(FALSE),
/*N*/   bPresMouseVisible(TRUE),
/*N*/   bPresMouseAsPen(FALSE),
/*N*/   bPresLockedPages(FALSE),
/*N*/   bStartPresWithNavigator(FALSE),
/*N*/   bAnimationAllowed(TRUE),
/*N*/   bPresAlwaysOnTop(FALSE),
/*N*/   bPresFullScreen(TRUE),
/*N*/   nPresPause(10),
/*N*/   bPresShowLogo(FALSE),
/*N*/   bCustomShow(false),
/*N*/   nPresFirstPage(1),
/*N*/   pOutliner(NULL),
/*N*/   pInternalOutliner(NULL),
/*N*/   ePageNumType(SVX_ARABIC),
/*N*/   bNewOrLoadCompleted(FALSE),
/*N*/   pWorkStartupTimer(NULL),
/*N*/   pOnlineSpellingTimer(NULL),
/*N*/   pOnlineSpellingList(NULL),
/*N*/   bInitialOnlineSpellingEnabled(TRUE),
/*N*/   bHasOnlineSpellErrors(FALSE),
/*N*/   pOnlineSearchItem(NULL),
/*N*/   mpLocale(NULL),
/*N*/   mpCharClass(NULL),
/*N*/   bAllocDocSh(FALSE),
/*N*/   pDeletedPresObjList(NULL),
/*N*/   nFileFormatVersion(SDIOCOMPAT_VERSIONDONTKNOW),
/*N*/   pDocStor(NULL),
/*N*/   pCustomShowList(NULL),
/*N*/   eLanguage( LANGUAGE_SYSTEM ),
/*N*/   eLanguageCJK( LANGUAGE_SYSTEM ),
/*N*/   eLanguageCTL( LANGUAGE_SYSTEM ),
/*N*/   mbStartWithPresentation( false )
/*N*/ {
/*N*/   SetObjectShell(pDrDocSh);       // fuer das VCDrawModel
/*N*/
/*N*/   if (pDocSh)
/*N*/   {
/*N*/       SetSwapGraphics(TRUE);
/*N*/   }
/*N*/
/*N*/   // Masseinheit (von App) und Massstab (von SdMod) setzen
/*N*/   INT32 nX, nY;
/*N*/   SdOptions* pOptions = SD_MOD()->GetSdOptions(eDocType);
/*N*/   pOptions->GetScale( nX, nY );
/*N*/
/*N*/     // #92067# Allow UI scale only for draw documents.
/*N*/     if( eType == DOCUMENT_TYPE_DRAW )
/*N*/         SetUIUnit( (FieldUnit)pOptions->GetMetric(), Fraction( nX, nY ) );    // user-defined
/*N*/     else
/*N*/         SetUIUnit( (FieldUnit)pOptions->GetMetric(), Fraction( 1, 1 ) );  // default
/*N*/
/*N*/   SetScaleUnit(MAP_100TH_MM);
/*N*/   SetScaleFraction(Fraction(1, 1));
/*N*/   SetDefaultFontHeight(847);     // 24p
/*N*/
/*N*/   pItemPool->SetDefaultMetric(SFX_MAPUNIT_100TH_MM);
/*N*/   pItemPool->FreezeIdRanges();
/*N*/   SetTextDefaults();
/*N*/
/*N*/   // die DrawingEngine muss auch wissen, wo er ist
/*N*/   FmFormModel::SetStyleSheetPool( new SdStyleSheetPool( GetPool(), this ) );
/*N*/
/*N*/   // Dem DrawOutliner den StyleSheetPool setzen, damit Textobjekte richtig
/*N*/   // eingelesen werden koennen. Der Link zum StyleRequest-Handler des
/*N*/   // Dokuments wird erst in NewOrLoadCompleted gesetzt, da erst dann alle
/*N*/   // Vorlagen existieren.
/*N*/   SdrOutliner& rOutliner = GetDrawOutliner();
/*N*/   rOutliner.SetStyleSheetPool((SfxStyleSheetPool*)GetStyleSheetPool());
/*N*/   rOutliner.SetCalcFieldValueHdl(LINK(SD_MOD(), SdModule, CalcFieldValueHdl));
/*N*/
/*N*/   // set linguistic options
/*N*/   {
/*N*/         const SvtLinguConfig    aLinguConfig;
/*N*/       SvtLinguOptions         aOptions;
/*N*/       aLinguConfig.GetOptions( aOptions );
/*N*/
/*N*/       SetLanguage( aOptions.nDefaultLanguage, EE_CHAR_LANGUAGE );
/*N*/       SetLanguage( aOptions.nDefaultLanguage_CJK, EE_CHAR_LANGUAGE_CJK );
/*N*/       SetLanguage( aOptions.nDefaultLanguage_CTL, EE_CHAR_LANGUAGE_CTL );
/*N*/
/*N*/       bOnlineSpell = aOptions.bIsSpellAuto;
/*N*/       bHideSpell = aOptions.bIsSpellHideMarkings;
/*N*/   }
/*N*/
/*N*/   LanguageType eRealLanguage = MsLangId::getRealLanguage( eLanguage );
/*N*/
/*N*/   mpLocale = new ::com::sun::star::lang::Locale( MsLangId::convertLanguageToLocale( eRealLanguage ));
/*N*/   mpCharClass = new CharClass( *mpLocale );
/*N*/
/*N*/   // If the current application language is a language that uses right-to-left text...
/*N*/   LanguageType eRealCTLLanguage = Application::GetSettings().GetLanguage();
/*N*/   if( (LANGUAGE_ARABIC == (eRealCTLLanguage & 0x00ff)) ||
/*N*/       (LANGUAGE_URDU == (eRealCTLLanguage & 0x00ff)) ||
/*N*/       (LANGUAGE_HEBREW == eRealCTLLanguage) )
/*N*/   {
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 // ... then we have to set this as a default
/*N*/   }
/*N*/
/*N*/   // DefTab und SpellOptions setzen
/*N*/   //OfaMiscCfg* pOfaMiscCfg = SFX_APP()->GetMiscConfig();
/*N*/   // Jetzt am Modul (SD)
/*N*/   USHORT nDefTab = pOptions->GetDefTab();
/*N*/   SetDefaultTabulator( nDefTab );
/*N*/
/*N*/   try
/*N*/   {
/*N*/       Reference< XSpellChecker1 > xSpellChecker( LinguMgr::GetSpellChecker() );
/*N*/       if ( xSpellChecker.is() )
/*N*/           rOutliner.SetSpeller( xSpellChecker );
/*N*/
/*N*/       Reference< XHyphenator > xHyphenator( LinguMgr::GetHyphenator() );
/*N*/       if( xHyphenator.is() )
/*N*/           rOutliner.SetHyphenator( xHyphenator );
/*N*/
/*N*/       SetForbiddenCharsTable( new SvxForbiddenCharactersTable( ::legacy_binfilters::getLegacyProcessServiceFactory() ) );
/*N*/   }
/*N*/   catch(...)
/*N*/   {
/*N*/       DBG_ERROR("Can't get SpellChecker");
/*N*/   }
/*N*/   // END_CATCH
/*N*/
/*N*/   rOutliner.SetDefaultLanguage( Application::GetSettings().GetLanguage() );
/*N*/
/*N*/   aOldNotifyUndoActionHdl = GetNotifyUndoActionHdl();
/*N*/   SetNotifyUndoActionHdl(LINK(this, SdDrawDocument, NotifyUndoActionHdl));
/*N*/
/*N*/   if (pDocSh)
/*N*/   {
/*N*/       SetLinkManager( new SvxLinkManager(pDocSh) );
/*N*/   }
/*N*/
/*N*/   ULONG nCntrl = rOutliner.GetControlWord();
/*N*/   nCntrl |= EE_CNTRL_ALLOWBIGOBJS;
/*N*/   nCntrl |= EE_CNTRL_URLSFXEXECUTE;
/*N*/
/*N*/   if (bHideSpell)
/*N*/       nCntrl |= EE_CNTRL_NOREDLINES;
/*N*/   else
/*N*/       nCntrl &= ~EE_CNTRL_NOREDLINES;
/*N*/
/*N*/   if (bOnlineSpell)
/*N*/       nCntrl |= EE_CNTRL_ONLINESPELLING;
/*N*/   else
/*N*/       nCntrl &= ~EE_CNTRL_ONLINESPELLING;
/*N*/
/*N*/   nCntrl &= ~ EE_CNTRL_ULSPACESUMMATION;
/*N*/     if ( eDocType != DOCUMENT_TYPE_IMPRESS )
/*N*/         SetSummationOfParagraphs( sal_False );
/*N*/     else
/*N*/     {
/*N*/         SetSummationOfParagraphs( pOptions->IsSummationOfParagraphs() );
/*N*/       if ( pOptions->IsSummationOfParagraphs() )
/*N*/           nCntrl |= EE_CNTRL_ULSPACESUMMATION;
/*N*/     }
/*N*/   rOutliner.SetControlWord(nCntrl);
/*N*/
/*N*/     // Initialize the printer independent layout mode.
/*N*/     SetPrinterIndependentLayout (pOptions->GetPrinterIndependentLayout());
/*N*/
/*N*/   // Dem HitTestOutliner den StyleSheetPool setzen.
/*N*/   // Der Link zum StyleRequest-Handler des
/*N*/   // Dokuments wird erst in NewOrLoadCompleted gesetzt, da erst dann alle
/*N*/   // Vorlagen existieren.
/*N*/   SfxItemSet aSet2( pHitTestOutliner->GetEmptyItemSet() );
/*N*/   pHitTestOutliner->SetStyleSheetPool( (SfxStyleSheetPool*)GetStyleSheetPool() );
/*N*/
/*N*/   pHitTestOutliner->SetCalcFieldValueHdl( LINK(SD_MOD(), SdModule, CalcFieldValueHdl) );
/*N*/
/*N*/   try
/*N*/   {
/*N*/       Reference< XSpellChecker1 > xSpellChecker( LinguMgr::GetSpellChecker() );
/*N*/       if ( xSpellChecker.is() )
/*N*/           pHitTestOutliner->SetSpeller( xSpellChecker );
/*N*/
/*N*/       Reference< XHyphenator > xHyphenator( LinguMgr::GetHyphenator() );
/*N*/       if( xHyphenator.is() )
/*N*/           pHitTestOutliner->SetHyphenator( xHyphenator );
/*N*/   }
/*N*/   catch(...)
/*N*/   {
/*N*/       DBG_ERROR("Can't get SpellChecker");
/*N*/   }
/*N*/   //END_CATCH
/*N*/
/*N*/   pHitTestOutliner->SetDefaultLanguage( Application::GetSettings().GetLanguage() );
/*N*/
/*N*/   ULONG nCntrl2 = pHitTestOutliner->GetControlWord();
/*N*/   nCntrl2 |= EE_CNTRL_ALLOWBIGOBJS;
/*N*/   nCntrl2 |= EE_CNTRL_URLSFXEXECUTE;
/*N*/   nCntrl2 |= EE_CNTRL_NOREDLINES;
/*N*/   nCntrl2 &= ~EE_CNTRL_ONLINESPELLING;
/*N*/
/*N*/   nCntrl2 &= ~ EE_CNTRL_ULSPACESUMMATION;
/*N*/   if ( pOptions->IsSummationOfParagraphs() )
/*N*/       nCntrl2 |= EE_CNTRL_ULSPACESUMMATION;
/*N*/
/*N*/   pHitTestOutliner->SetControlWord( nCntrl2 );
/*N*/
    /**************************************************************************
    * Layer anlegen
    *
    * Es werden auf Pages und MasterPages folgende Default-Layer angelegt:
    *
    * Layer STR_LAYOUT    : Standardlayer fr alle Zeichenobjekte
    *
    * Layer STR_BCKGRND   : Hintergrund der MasterPage
    *                       (auf normalen Pages z.Z. keine Verwendung)
    *
    * Layer STR_BCKGRNDOBJ: Objekte auf dem Hintergrund der MasterPage
    *                       (auf normalen Pages z.Z. keine Verwendung)
    *
    * Layer STR_CONTROLS  : Standardlayer fr Controls
    *
    **************************************************************************/
/*N*/   {
/*N*/       String aControlLayerName( SdResId(STR_LAYER_CONTROLS) );
/*N*/
/*N*/       SdrLayerAdmin& rLayerAdmin = GetLayerAdmin();
/*N*/       rLayerAdmin.NewLayer( String(SdResId(STR_LAYER_LAYOUT)) );
/*N*/       rLayerAdmin.NewLayer( String(SdResId(STR_LAYER_BCKGRND)) );
/*N*/       rLayerAdmin.NewLayer( String(SdResId(STR_LAYER_BCKGRNDOBJ)) );
/*N*/       rLayerAdmin.NewLayer( aControlLayerName );
/*N*/       rLayerAdmin.NewLayer( String(SdResId(STR_LAYER_MEASURELINES)) );
/*N*/
/*N*/       rLayerAdmin.SetControlLayerName(aControlLayerName);
/*N*/   }
/*N*/
/*N*/   pFrameViewList = new List();
/*N*/ }

/*************************************************************************
|*
|* Destruktor
|*
\************************************************************************/

/*N*/ SdDrawDocument::~SdDrawDocument()
/*N*/ {
/*N*/   Broadcast(SdrHint(HINT_MODELCLEARED));
/*N*/
/*N*/   if (pWorkStartupTimer)
/*N*/   {
/*N*/       if ( pWorkStartupTimer->IsActive() )
/*?*/           pWorkStartupTimer->Stop();
/*N*/
/*N*/       delete pWorkStartupTimer;
/*N*/       pWorkStartupTimer = NULL;
/*N*/   }
/*N*/
/*N*/   StopOnlineSpelling();
/*N*/   delete pOnlineSearchItem;
/*N*/   pOnlineSearchItem = NULL;
/*N*/
/*N*/   CloseBookmarkDoc();
/*N*/   SetAllocDocSh(FALSE);
/*N*/
/*N*/   SetNotifyUndoActionHdl(aOldNotifyUndoActionHdl);
/*N*/   Clear();
/*N*/
/*N*/   if (pLinkManager)
/*N*/   {
/*N*/       // BaseLinks freigeben
/*N*/       if ( pLinkManager->GetLinks().Count() )
/*?*/       {
/*?*/           pLinkManager->Remove( 0, pLinkManager->GetLinks().Count() );
/*?*/       }
/*N*/
/*N*/       delete pLinkManager;
/*N*/       pLinkManager = NULL;
/*N*/   }
/*N*/
/*N*/   FrameView* pFrameView = NULL;
/*N*/
/*N*/   for (ULONG i = 0; i < pFrameViewList->Count(); i++)
/*N*/   {
/*N*/       // Ggf. FrameViews loeschen
/*N*/       pFrameView = (FrameView*) pFrameViewList->GetObject(i);
/*N*/
/*N*/       if (pFrameView)
/*N*/           delete pFrameView;
/*N*/   }
/*N*/
/*N*/   delete pFrameViewList;
/*N*/   pFrameViewList = NULL;
/*N*/
/*N*/   if (pCustomShowList)
/*?*/   {
/*?*/       for (ULONG j = 0; j < pCustomShowList->Count(); j++)
/*?*/       {
            // Ggf. CustomShows loeschen
/*?*/           SdCustomShow* pCustomShow = (SdCustomShow*) pCustomShowList->GetObject(j);
/*?*/           delete pCustomShow;
/*?*/       }

/*?*/       delete pCustomShowList;
/*?*/       pCustomShowList = NULL;
/*?*/   }
/*N*/
/*N*/   delete pOutliner;
/*N*/   pOutliner = NULL;
/*N*/
/*N*/   delete pInternalOutliner;
/*N*/   pInternalOutliner = NULL;
/*N*/
/*N*/   delete pDeletedPresObjList;
/*N*/   pDeletedPresObjList = NULL;
/*N*/
/*N*/   delete mpLocale;
/*N*/   mpLocale = NULL;
/*N*/
/*N*/   delete mpCharClass;
/*N*/   mpCharClass = NULL;
/*N*/ }

/*************************************************************************
|*
|* Diese Methode erzeugt eine neue Seite (SdPage) und gibt einen Zeiger
|* darauf zurueck. Die Drawing Engine benutzt diese Methode beim Laden
|* zur Erzeugung von Seiten (deren Typ sie ja nicht kennt, da es ABLEITUNGEN
|* der SdrPage sind).
|*
\************************************************************************/

/*N*/ SdrPage* SdDrawDocument::AllocPage(FASTBOOL bMasterPage)
/*N*/ {
/*N*/   return new SdPage(*this, NULL, bMasterPage);
/*N*/ }

/*************************************************************************
|*
|* Inserter fuer SvStream zum Speichern
|*
\************************************************************************/

/*N*/ SvStream& operator << (SvStream& rOut, SdDrawDocument& rDoc)
/*N*/ {
/*N*/   // #90477# CharSet eSysSet = ::GetStoreCharSet( gsl_getSystemTextEncoding());
/*N*/   CharSet eSysSet = GetSOStoreTextEncoding(gsl_getSystemTextEncoding(), (sal_uInt16)rOut.GetVersion());
/*N*/
    /**************************************************************************
    * Aktuelle FileFormat-Versionsnummer
    * Bei Aenderugen stets inkrementieren und beim Laden beruecksichtigen!
    **************************************************************************/
/*N*/   rDoc.nFileFormatVersion = 18;
/*N*/
/*N*/   // AutoLayouts muessen ggf. erzeugt werden
/*N*/   rDoc.StopWorkStartupDelay();
/*N*/
/*N*/   // Eindeutige Namen der StandardLayer erzeugen
/*N*/   rDoc.MakeUniqueLayerNames();
/*N*/
/*N*/   rOut << (FmFormModel&) rDoc;
/*N*/
/*N*/   // Sprachabhaengige Namen der StandardLayer wieder herstellen
/*N*/   rDoc.RestoreLayerNames();
/*N*/
/*N*/   if ( rDoc.IsStreamingSdrModel() )
/*N*/   {
/*N*/       // Es wird nur das SdrModel gestreamt, nicht das SdDrawDocument!
/*N*/       // Anwendungsfall: svdraw Clipboard-Format
/*N*/       return(rOut);
/*N*/   }
/*N*/
/*N*/   SdIOCompat aIO(rOut, STREAM_WRITE, rDoc.nFileFormatVersion);
/*N*/
/*N*/   BOOL bDummy = TRUE;
/*N*/   rOut << bDummy;                    // ehem. bPresentation
/*N*/   rOut << rDoc.bPresAll;
/*N*/   rOut << rDoc.bPresEndless;
/*N*/   rOut << rDoc.bPresManual;
/*N*/   rOut << rDoc.bPresMouseVisible;
/*N*/   rOut << rDoc.bPresMouseAsPen;
/*N*/   rOut << rDoc.nPresFirstPage;
/*N*/
/*N*/   // Es wird nun eine Liste von FrameViews geschrieben (siehe weiter unten),
/*N*/   // daher wird an dieser Stelle ein FALSE vermerkt.
/*N*/   BOOL bSingleFrameView = FALSE;
/*N*/   rOut << bSingleFrameView;
/*N*/
    /**************************************************************************
    * Frueher (StarDraw Version 3.0, File-Format Version 3) wurde hier das
    * JobSetup geschrieben, nun der Printer (binaer-kompatibel, daher wurde
    * die Version des File-Formats nicht geaendert)
    **************************************************************************/
/*N*/   if (rDoc.pDocSh)
/*N*/   {
/*N*/       SfxPrinter* pPrinter = rDoc.pDocSh->GetPrinter(TRUE);
/*N*/       pPrinter->Store(rOut);
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       // Keine DocShell, daher wird ein JobSetup geschrieben
/*N*/       JobSetup aJobSetup;
/*N*/       rOut << aJobSetup;
/*N*/   }
/*N*/
/*N*/   rOut << (sal_uInt32) rDoc.eLanguage;
/*N*/
    /**************************************************************************
    * FrameViews schreiben
    **************************************************************************/
/*N*/   sal_uInt32 nFrameViewCount = 0;
/*N*/   SdViewShell* pViewSh = NULL;
/*N*/   SfxViewShell* pSfxViewSh = NULL;
/*N*/   SfxViewFrame* pSfxViewFrame = SfxViewFrame::GetFirst(rDoc.pDocSh,
/*N*/                                                        TYPE(SfxTopViewFrame));
/*N*/
/*N*/   while (pSfxViewFrame)
/*N*/   {
/*N*/       // Anzahl FrameViews ermitteln
/*N*/       pSfxViewSh = pSfxViewFrame->GetViewShell();
/*N*/       pViewSh = PTR_CAST( SdViewShell, pSfxViewSh );
/*N*/
/*N*/       if ( pViewSh && pViewSh->GetFrameView() )
/*N*/       {
/*N*/           nFrameViewCount++;
/*N*/       }
/*N*/
/*N*/       pSfxViewFrame = SfxViewFrame::GetNext(*pSfxViewFrame, rDoc.pDocSh,
/*N*/                                             TYPE(SfxTopViewFrame));
/*N*/   }
/*N*/
/*N*/   // Anzahl FrameViews schreiben
/*N*/   rOut << nFrameViewCount;
/*N*/
/*N*/   FrameView* pFrame = NULL;
/*N*/   pViewSh = NULL;
/*N*/   pSfxViewSh = NULL;
/*N*/   pSfxViewFrame = SfxViewFrame::GetFirst(rDoc.pDocSh, TYPE(SfxTopViewFrame));
/*N*/
/*N*/   while (pSfxViewFrame)
/*N*/   {
/*N*/       // FrameViews schreiben
/*N*/       pSfxViewSh = pSfxViewFrame->GetViewShell();
/*N*/       pViewSh = PTR_CAST( SdViewShell, pSfxViewSh );
/*N*/
/*N*/       if ( pViewSh && pViewSh->GetFrameView() )
/*N*/       {
/*N*/           pViewSh->WriteFrameViewData();
/*N*/           rOut << *pViewSh->GetFrameView();
/*N*/       }
/*N*/
/*N*/       pSfxViewFrame = SfxViewFrame::GetNext(*pSfxViewFrame, rDoc.pDocSh,
/*N*/                                             TYPE(SfxTopViewFrame));
/*N*/   }
/*N*/
/*N*/   rOut << rDoc.bStartPresWithNavigator;
/*N*/   rOut << rDoc.bPresLockedPages;
/*N*/   rOut << rDoc.bPresAlwaysOnTop;
/*N*/   rOut << rDoc.bOnlineSpell;
/*N*/   rOut << rDoc.bHideSpell;
/*N*/   rOut << rDoc.bPresFullScreen;
/*N*/   rOut.WriteByteString( rDoc.aPresPage, eSysSet );
/*N*/   rOut << rDoc.bAnimationAllowed;
/*N*/
/*N*/   UINT16 nDocType = (UINT16) rDoc.eDocType;
/*N*/   rOut << nDocType;
/*N*/
/*N*/   // CustomShow aktiv
/*N*/   rOut << rDoc.bCustomShow;
/*N*/
/*N*/   // Anzahl CustomShows schreiben
/*N*/   sal_uInt32 nCustomShowCount = 0;
/*N*/
/*N*/   if (rDoc.pCustomShowList)
/*N*/   {
/*?*/       nCustomShowCount = rDoc.pCustomShowList->Count();
/*N*/   }
/*N*/
/*N*/   rOut << nCustomShowCount;
/*N*/
/*N*/   if (rDoc.pCustomShowList)
/*N*/   {
/*?*/       for (ULONG i = 0; i < nCustomShowCount; i++)
        {
            // CustomShows schreiben
/*?*/           SdCustomShow* pCustomShow = (SdCustomShow*) rDoc.pCustomShowList->GetObject(i);
            rOut << *pCustomShow;
        }

        // Position der aktuellen CustomShow
        sal_uInt32 nCurPos = rDoc.pCustomShowList->GetCurPos();
        rOut << nCurPos;
    }

/*N*/   // ab Version 15
/*N*/   rOut << (sal_uInt32) rDoc.GetPageNumType();
/*N*/
/*N*/   // ab Version 17
/*N*/   rOut << rDoc.GetPresPause() << rDoc.IsPresShowLogo();
/*N*/
/*N*/   // ab Version 18 (keine Aenderung)
/*N*/
/*N*/   return rOut;
/*N*/ }

/*************************************************************************
|*
|* Extractor fuer SvStream zum Laden
|*
\************************************************************************/

/*N*/ SvStream& operator >> (SvStream& rIn, SdDrawDocument& rDoc)
/*N*/ {
/*N*/   // #90477# CharSet eSysSet = ::GetStoreCharSet( gsl_getSystemTextEncoding());
/*N*/   CharSet eSysSet = GetSOLoadTextEncoding(gsl_getSystemTextEncoding(), (sal_uInt16)rIn.GetVersion());
/*N*/
/*N*/   rIn >> (FmFormModel&) rDoc;
/*N*/   rDoc.GetItemPool().LoadCompleted();
/*N*/   rDoc.SetTextDefaults();     // overwrites loaded pool defaults
/*N*/
/*N*/     // Turn off printer independent layout (make it printer *dependent*) for
/*N*/     // pre-6.0 documents.
/*N*/     rDoc.SetPrinterIndependentLayout (
/*N*/         ::com::sun::star::document::PrinterIndependentLayout::DISABLED);
/*N*/
/*N*/   // Fehler ?
/*N*/   if (rIn.GetError() != 0)
/*N*/       return (rIn);
/*N*/
/*N*/   if ( rDoc.IsStreamingSdrModel() )
/*N*/   {
/*N*/       // Es wird nur das SdrModel gestreamt, nicht das SdDrawDocument!
/*N*/       // Anwendungsfall: svdraw Clipboard-Format
/*N*/       return(rIn);
/*N*/   }
/*N*/
/*N*/   SdIOCompat aIO(rIn, STREAM_READ);
/*N*/
/*N*/   BOOL bDummy;
/*N*/   rIn >> bDummy;                     // ehem. bPresentation
/*N*/   rIn >> rDoc.bPresAll;
/*N*/   rIn >> rDoc.bPresEndless;
/*N*/   rIn >> rDoc.bPresManual;
/*N*/   rIn >> rDoc.bPresMouseVisible;
/*N*/   rIn >> rDoc.bPresMouseAsPen;
/*N*/   rIn >> rDoc.nPresFirstPage;
/*N*/
/*N*/   rDoc.nFileFormatVersion = aIO.GetVersion();
/*N*/
/*N*/   if (rDoc.nFileFormatVersion >= 1)
/*N*/   {
/*N*/       // Daten der Versionen >= 1 einlesen
/*N*/
/*N*/       BOOL bSingleFrameView;
/*N*/       rIn >> bSingleFrameView;
/*N*/
/*N*/       if (bSingleFrameView)
/*N*/       {
/*N*/           FrameView * pFrameView = new FrameView( &rDoc );
/*N*/           rIn >> *pFrameView;
/*N*/           rDoc.pFrameViewList->Insert(pFrameView, LIST_APPEND);
/*N*/
/*N*/           // Fehler ?
/*N*/           if (rIn.GetError() != 0)
/*N*/               return (rIn);
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if (rDoc.nFileFormatVersion >= 2)
/*N*/   {
/*N*/       // Daten der Versionen >= 2 einlesen
/*N*/
         /******************************************************************
         * Frueher (StarDraw Version 3.0, File-Format Version 3) wurde hier
         * das JobSetup eingelesen, nun wird der Printer erzeugt
         * (binaer-kompatibel)
         *******************************************************************/
/*N*/       // ItemSet mit speziellem Poolbereich anlegen
/*N*/       SfxItemSet* pSet = new SfxItemSet( rDoc.GetPool(),
/*N*/                       SID_PRINTER_NOTFOUND_WARN,  SID_PRINTER_NOTFOUND_WARN,
/*N*/                       SID_PRINTER_CHANGESTODOC,   SID_PRINTER_CHANGESTODOC,
/*N*/                       ATTR_OPTIONS_PRINT,         ATTR_OPTIONS_PRINT,
/*N*/                       0 );
/*N*/       // PrintOptionsSet setzen
/*N*/       SdOptionsPrintItem aPrintItem(ATTR_OPTIONS_PRINT
/*N*/                                     ,SD_MOD()->GetSdOptions(rDoc.eDocType)
/*N*/                                     );
/*N*/
/*N*/       SfxFlagItem aFlagItem( SID_PRINTER_CHANGESTODOC );
/*N*/       USHORT      nFlags = 0;
/*N*/
/*N*/       nFlags =  (aPrintItem.IsWarningSize() ? SFX_PRINTER_CHG_SIZE : 0) |
/*N*/               (aPrintItem.IsWarningOrientation() ? SFX_PRINTER_CHG_ORIENTATION : 0);
/*N*/       aFlagItem.SetValue( nFlags );
/*N*/
/*N*/       pSet->Put( aPrintItem );
/*N*/       pSet->Put( SfxBoolItem( SID_PRINTER_NOTFOUND_WARN, aPrintItem.IsWarningPrinter() ) );
/*N*/       pSet->Put( aFlagItem );
/*N*/
/*N*/       SfxPrinter* pPrinter = SfxPrinter::Create(rIn, pSet);
/*N*/
/*N*/       MapMode aMM (pPrinter->GetMapMode());
/*N*/       aMM.SetMapUnit(MAP_100TH_MM);
/*N*/       pPrinter->SetMapMode(aMM);
/*N*/       if (rDoc.pDocSh)            // z. B. nicht bei "Einfuegen-Datei"
/*N*/           rDoc.pDocSh->SetPrinter(pPrinter);
/*N*/       else
/*N*/           delete pPrinter;
/*N*/   }
/*N*/
/*N*/   if (rDoc.nFileFormatVersion >= 3)
/*N*/   {
/*N*/       sal_uInt32 nTmp;
/*N*/       rIn >> nTmp;
/*N*/       rDoc.SetLanguage( (LanguageType) nTmp, EE_CHAR_LANGUAGE );
/*N*/   }
/*N*/
/*N*/   if (rDoc.nFileFormatVersion >= 4)
/*N*/   {
         /**********************************************************************
         * FrameViews lesen
         **********************************************************************/
/*N*/       ULONG nCount = 0;
/*N*/       FrameView* pFrameView = NULL;
/*N*/
/*N*/       for (nCount=0; nCount<rDoc.pFrameViewList->Count(); nCount++)
/*N*/       {
/*N*/           // Ggf. FrameViews loeschen
/*?*/           pFrameView = (FrameView*) rDoc.pFrameViewList->GetObject(nCount);

            if (pFrameView)
                delete pFrameView;
        }
/*N*/
/*N*/       rDoc.pFrameViewList->Clear();
/*N*/
/*N*/       // Anzahl FrameViews lesen
/*N*/       const SvtSaveOptions aOptions;
/*N*/       BOOL bIsSaveDocView = aOptions.IsSaveDocView();
/*N*/
/*N*/       sal_uInt32 nFrameViewCount = 0;
/*N*/       rIn >> nFrameViewCount;
/*N*/
/*N*/       for (nCount=0; nCount<nFrameViewCount; nCount++)
/*N*/       {
/*N*/           // Einzelne FrameViews lesen
/*N*/           pFrameView = new FrameView( &rDoc );
/*N*/           rIn >> *pFrameView;
/*N*/
/*N*/           if (bIsSaveDocView)
/*N*/           {
/*N*/               // FrameViews werden fuer die ViewShell gebraucht
/*N*/               // Die FrameView gehoert nun der Liste
/*N*/               rDoc.pFrameViewList->Insert(pFrameView, nCount);
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               // FrameView kann wieder geloescht werden
/*N*/               delete pFrameView;
/*N*/           }
/*N*/
/*N*/           // Fehler ?
/*N*/           if (rIn.GetError() != 0)
/*N*/               return (rIn);
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if (rDoc.nFileFormatVersion >= 5)
/*N*/   {
/*N*/       rIn >> rDoc.bStartPresWithNavigator;
/*N*/   }
/*N*/
/*N*/   if (rDoc.nFileFormatVersion >= 6)
/*N*/   {
/*N*/       rIn >> rDoc.bPresLockedPages;
/*N*/   }
/*N*/
/*N*/   if (rDoc.nFileFormatVersion >= 7)
/*N*/   {
/*N*/       rIn >> rDoc.bPresAlwaysOnTop;
/*N*/   }
/*N*/
/*N*/   if (rDoc.nFileFormatVersion >= 8)
/*N*/   {
/*N*/       rIn >> rDoc.bOnlineSpell;
/*N*/       rIn >> rDoc.bHideSpell;
/*N*/   }
/*N*/
/*N*/   if (rDoc.nFileFormatVersion >= 9)
/*N*/   {
/*N*/       rIn >> rDoc.bPresFullScreen;
/*N*/   }
/*N*/
/*N*/   if (rDoc.nFileFormatVersion >= 10)
/*N*/   {
/*N*/       rIn.ReadByteString( rDoc.aPresPage, eSysSet );
/*N*/   }
/*N*/
/*N*/   if (rDoc.nFileFormatVersion >= 11)
/*N*/   {
/*N*/       rIn >> rDoc.bAnimationAllowed;
/*N*/   }
/*N*/
/*N*/   if (rDoc.nFileFormatVersion >= 12)
/*N*/   {
/*N*/       UINT16 nDocType;
/*N*/       rIn >> nDocType;
/*N*/       rDoc.eDocType = (DocumentType) nDocType;
/*N*/       // existiert eine DocShell bestimmt diese den DocType
/*N*/       if(rDoc.pDocSh)
/*N*/       {
/*N*/           if(NULL != PTR_CAST(SdGraphicDocShell,rDoc.pDocSh))
/*N*/               rDoc.eDocType = DOCUMENT_TYPE_DRAW;
/*N*/           else
/*N*/               rDoc.eDocType = DOCUMENT_TYPE_IMPRESS;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if (rDoc.nFileFormatVersion >= 13)
/*N*/   {
/*N*/       // Keine Aenderung
/*N*/   }
/*N*/
/*N*/   if (rDoc.nFileFormatVersion >= 14)
/*N*/   {
/*N*/       // CustomShow aktiv
/*N*/       rIn >> rDoc.bCustomShow;
/*N*/
/*N*/       sal_uInt32 nCustomShowCount = 0;
/*N*/       rIn >> nCustomShowCount;
/*N*/
/*N*/       if (nCustomShowCount > 0)
/*N*/       {
            // Liste erzeugen
/*?*/           rDoc.GetCustomShowList(TRUE);
            rDoc.pCustomShowList->Clear();

            for (ULONG i = 0; i < nCustomShowCount; i++)
            {
                // Einzelne CustomShows lesen
                SdCustomShow* pCustomShow = new SdCustomShow(&rDoc);
                rIn >> *pCustomShow;

                // Die CustomShows gehoert nun der Liste
                rDoc.pCustomShowList->Insert(pCustomShow, i);

                // Fehler ?
                if (rIn.GetError() != 0)
                    return (rIn);
            }

            // Aktuelle CustomShow selektieren
            sal_uInt32 nCurPos;
            rIn >> nCurPos;
            rDoc.pCustomShowList->Seek(nCurPos);
        }
/*N*/   }
/*N*/
/*N*/   if (rDoc.nFileFormatVersion >= 15)
/*N*/   {
/*N*/       sal_uInt32 nTmp;
/*N*/       rIn >> nTmp;
/*N*/       rDoc.SetPageNumType( (SvxNumType) nTmp );
/*N*/   }
/*N*/
/*N*/   if (rDoc.nFileFormatVersion >= 17)
/*N*/   {
/*N*/       sal_uInt32 nPauseSec;
/*N*/       BOOL    bShowLogo;
/*N*/
/*N*/       rIn >> nPauseSec >> bShowLogo;
/*N*/       rDoc.SetPresPause( nPauseSec );
/*N*/       rDoc.SetPresShowLogo( bShowLogo );
/*N*/   }
/*N*/   else
/*N*/       rDoc.SetPresPause( 0 );
/*N*/
/*N*/   if (rDoc.nFileFormatVersion >= 18)
/*N*/   {
/*N*/       // Keine Aenderung
/*N*/   }
/*N*/
    /**************************************************************************
    * So machts der Writer, und so muessen es alle machen:
    * Bug 9714: Der CharSet an den Fonts muss geaendert werden, wenn
    * es der globale CharSet ist (MT)
    **************************************************************************/
/*N*/   SfxItemPool& rPool = rDoc.GetItemPool();
/*N*/   USHORT nMaxItems = rPool.GetItemCount(EE_CHAR_FONTINFO);
/*N*/   SvxFontItem* pItem;
/*N*/   CharSet eSrcSet = ((SdPage*) rDoc.GetPage(0))->GetCharSet();
/*N*/
/*N*/   for (USHORT n = 0; n < nMaxItems; ++n)
/*N*/   {
/*N*/       pItem = (SvxFontItem*) rPool.GetItem(EE_CHAR_FONTINFO, n);
/*N*/       if (pItem && pItem->GetCharSet() == eSrcSet)
/*N*/       {
/*N*/           pItem->GetCharSet() = eSysSet;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return rIn;
/*N*/ }

/*************************************************************************
|*
|* "Alle Dias"-Parameter der Praesentation aendern
|*
\************************************************************************/

/*N*/ void SdDrawDocument::SetPresAll(BOOL bNewPresAll)
/*N*/ {
/*N*/   bPresAll     = bNewPresAll;
/*N*/ }

/*************************************************************************
|*
|* "Endlos"-Parameter der Praesentation aendern
|*
\************************************************************************/

/*N*/ void SdDrawDocument::SetPresEndless(BOOL bNewPresEndless)
/*N*/ {
/*N*/   bPresEndless = bNewPresEndless;
/*N*/ }

/*************************************************************************
|*
|* "Manuell"-Parameter der Praesentation aendern
|*
\************************************************************************/

/*N*/ void SdDrawDocument::SetPresManual(BOOL bNewPresManual)
/*N*/ {
/*N*/   bPresManual  = bNewPresManual;
/*N*/ }

/*************************************************************************
|*
|* "Maus sichtbar"-Parameter der Praesentation aendern
|*
\************************************************************************/

/*N*/ void SdDrawDocument::SetPresMouseVisible(BOOL bNewPresMouseVisible)
/*N*/ {
/*N*/   bPresMouseVisible = bNewPresMouseVisible;
/*N*/ }

/*************************************************************************
|*
|* "Maus als Stift"-Parameter der Praesentation aendern
|*
\************************************************************************/

/*N*/ void SdDrawDocument::SetPresMouseAsPen(BOOL bNewPresMouseAsPen)
/*N*/ {
/*N*/   bPresMouseAsPen = bNewPresMouseAsPen;
/*N*/ }

/*************************************************************************
|*
|* "Ab Dia"-Parameter der Praesentation aendern
|*
\************************************************************************/


/*************************************************************************
|*
|* SetChanged(), das Model wurde geaendert
|*
\************************************************************************/

/*N*/ void SdDrawDocument::SetChanged(FASTBOOL bFlag)
/*N*/ {
/*N*/   if (pDocSh)
/*N*/   {
/*N*/       if (bNewOrLoadCompleted && pDocSh->IsEnableSetModified())
/*N*/       {
/*N*/           // weitergeben an Basisklasse
/*N*/           FmFormModel::SetChanged(bFlag);
/*N*/
/*N*/           // an ObjectShell weiterleiten
/*N*/           pDocSh->SetModified(bFlag);
/*N*/       }
/*N*/   }
/*N*/   else
/*?*/   {
        // weitergeben an Basisklasse
/*?*/       FmFormModel::SetChanged(bFlag);
/*?*/   }
/*N*/ }

/*************************************************************************
|*
|* NbcSetChanged(), the model changed, don't call anybody else
|*
\************************************************************************/

/*N*/ void SdDrawDocument::NbcSetChanged(FASTBOOL bFlag)
/*N*/ {
/*N*/     // #100237# forward to baseclass
/*N*/     FmFormModel::SetChanged(bFlag);
/*N*/ }

/*************************************************************************
|*
|* NewOrLoadCompleted
|*
|* Wird gerufen, wenn das Dokument geladen wurde bzw. feststeht, dass es
|* nicht mehr geladen wird.
|*
\************************************************************************/

/*N*/ void SdDrawDocument::NewOrLoadCompleted(DocCreationMode eMode)
/*N*/ {
/*N*/   if (eMode == NEW_DOC)
/*N*/   {
/*N*/       // Neues Dokument:
/*N*/       // Praesentations- und Standardvorlagen erzeugen,
/*N*/       // Pool fuer virtuelle Controls erzeugen
/*N*/       CreateLayoutTemplates();
/*N*/
/*N*/       ((SdStyleSheetPool*)pStyleSheetPool)->CreatePseudosIfNecessary();
/*N*/   }
/*N*/   else if (eMode == DOC_LOADED)
/*N*/   {
/*N*/           // Dokument wurde geladen:
/*N*/
/*N*/       CheckMasterPages();
/*N*/
/*N*/       if ( GetMasterSdPageCount(PK_STANDARD) > 1 )
/*N*/           RemoveUnnessesaryMasterPages( NULL, TRUE, FALSE );
/*N*/
/*N*/       for ( USHORT i = 0; i < GetPageCount(); i++ )
/*N*/       {
/*N*/           // Check for correct layout names
/*N*/           SdPage* pPage = (SdPage*) GetPage( i );
/*N*/           if( pPage->GetMasterPageCount() > 0 )
/*N*/           {
/*N*/               SdPage* pMaster = (SdPage*) pPage->GetMasterPage( 0 );
/*N*/               if( pMaster && pMaster->GetLayoutName() != pPage->GetLayoutName() )
/*N*/                   pPage->SetLayoutName( pMaster->GetLayoutName() );
/*N*/           }
/*N*/       }
/*N*/
/*N*/       for ( USHORT nPage = 0; nPage < GetMasterPageCount(); nPage++)
/*N*/       {
/*N*/           // LayoutName and PageName must be the same
/*N*/           SdPage* pPage = (SdPage*) GetMasterPage( nPage );
/*N*/
/*N*/           String aName( pPage->GetLayoutName() );
/*N*/           aName.Erase( aName.SearchAscii( SD_LT_SEPARATOR ) );
/*N*/
/*N*/           if( aName != pPage->GetName() )
/*N*/               pPage->SetName( aName );
/*N*/
/*N*/           SdrObject* pPresObj = pPage->GetPresObj( PRESOBJ_BACKGROUND ) ;
/*N*/
/*N*/           if( pPage->GetPageKind() == PK_STANDARD )
/*N*/           {
/*N*/               DBG_ASSERT( pPresObj, "Masterpage without a background object!" );
/*N*/               if (pPresObj && pPresObj->GetOrdNum() != 0 )
/*N*/                   pPage->NbcSetObjectOrdNum(pPresObj->GetOrdNum(),0);
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               DBG_ASSERT( pPresObj == NULL, "Non Standard Masterpage with a background object!\n(This assertion is ok for old binary files)" );
/*N*/               if( pPresObj )
/*N*/               {
/*N*/                   pPage->RemoveObject( pPresObj->GetOrdNum() );
/*N*/                   pPage->GetPresObjList()->Remove(pPresObj);
/*N*/                   delete pPresObj;
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/
/*N*/       // Sprachabhaengige Namen der StandardLayer erzeugen
/*N*/       RestoreLayerNames();
/*N*/
/*N*/       // Sprachabhaengige Namen der Vorlagen setzen
/*N*/       ((SdStyleSheetPool*)pStyleSheetPool)->UpdateStdNames();
/*N*/
/*N*/       // Ggf. fehlende Vorlagen erzeugen (es gab z.B. frueher keinen Subtitle)
/*N*/       ((SdStyleSheetPool*)pStyleSheetPool)->CreatePseudosIfNecessary();
/*N*/   }
/*N*/
/*N*/   // Standardvorlage an der Drawing Engine setzen
/*N*/   String aName( SdResId(STR_STANDARD_STYLESHEET_NAME));
/*N*/   SfxStyleSheet* pSheet = (SfxStyleSheet*)pStyleSheetPool->
/*N*/                                   Find(aName, SFX_STYLE_FAMILY_PARA);
/*N*/   SetDefaultStyleSheet(pSheet);
/*N*/
/*N*/   // Draw-Outliner und  Dokument Outliner initialisieren,
/*N*/   // aber nicht den globalen Outliner, den der ist ja nicht
/*N*/   // dokumentspezifisch wie StyleSheetPool und StyleRequestHandler
/*N*/   Outliner& rDrawOutliner = GetDrawOutliner();
/*N*/   rDrawOutliner.SetStyleSheetPool((SfxStyleSheetPool*)GetStyleSheetPool());
/*N*/       rDrawOutliner.SetMinDepth(0);
/*N*/   ULONG nCntrl = rDrawOutliner.GetControlWord();
/*N*/   if (bOnlineSpell)
/*N*/       nCntrl |= EE_CNTRL_ONLINESPELLING;
/*N*/   else
/*N*/       nCntrl &= ~EE_CNTRL_ONLINESPELLING;
/*N*/   rDrawOutliner.SetControlWord(nCntrl);
/*N*/
/*N*/   // HitTest-Outliner und  Dokument Outliner initialisieren,
/*N*/   // aber nicht den globalen Outliner, den der ist ja nicht
/*N*/   // dokumentspezifisch wie StyleSheetPool und StyleRequestHandler
/*N*/   pHitTestOutliner->SetStyleSheetPool((SfxStyleSheetPool*)GetStyleSheetPool());
/*N*/       pHitTestOutliner->SetMinDepth(0);
/*N*/
/*N*/   if (pOutliner)
/*?*/   {
/*?*/       pOutliner->SetStyleSheetPool((SfxStyleSheetPool*)GetStyleSheetPool());
/*?*/       pOutliner->SetMinDepth(0);
/*?*/   }
/*N*/   if (pInternalOutliner)
/*?*/   {
/*?*/       pInternalOutliner->SetStyleSheetPool((SfxStyleSheetPool*)GetStyleSheetPool());
/*?*/       pInternalOutliner->SetMinDepth(0);
/*?*/   }

/*N*/   if ( eMode == DOC_LOADED )
/*N*/   {
/*N*/       if (nFileFormatVersion <= 17 && nFileFormatVersion != SDIOCOMPAT_VERSIONDONTKNOW)
/*N*/       {
/*N*/           // Da sich die Bedeutung der SvxLRSpaceItems ab nFileFormatVersion = 16
/*N*/           // geaendert hat (Bullet-Handling des Outliners), muss fuer aeltere Versionen
/*N*/           // eine Korrektur vorgenommen werden.
/*N*/           // Bis Version 17 gab es noch diverse Probleme
/*N*/           ((SdStyleSheetPool*) pStyleSheetPool)->AdjustLRSpaceItems();
/*N*/       }
/*N*/
/*N*/       // Praesentationsobjekte muessen wieder Listener der entsprechenden
/*N*/       // Vorlagen werden
/*N*/       SdStyleSheetPool* pSPool = (SdStyleSheetPool*) GetStyleSheetPool();
/*N*/       SfxStyleSheet*    pSheet = NULL;
/*N*/       USHORT nPage, nPageCount;
/*N*/
/*N*/       // #96323# create missing layout style sheets for broken documents
/*N*/       //         that where created with the 5.2
/*N*/       nPageCount = GetMasterSdPageCount( PK_STANDARD );
/*N*/       for (nPage = 0; nPage < nPageCount; nPage++)
/*N*/       {
/*N*/           SdPage* pPage = GetMasterSdPage(nPage, PK_STANDARD);
/*N*/           pSPool->CreateLayoutStyleSheets( pPage->GetName(), sal_True );
/*N*/       }
/*N*/
/*N*/       // Standard- und Notizseiten:
/*N*/       for (nPage = 0; nPage < GetPageCount(); nPage++)
/*N*/       {
/*N*/           SdPage* pPage = (SdPage*)GetPage(nPage);
/*N*/
/*N*/           if( nFileFormatVersion <= 4 )
/*N*/               pPage->CreateTitleAndLayout();
/*N*/
/*N*/           SdrObjListIter aIter( *pPage );
/*N*/           while( aIter.IsMore() )
/*N*/           {
/*N*/               OutlinerParaObject* pOPO = aIter.Next()->GetOutlinerParaObject();
/*N*/               if( pOPO )
/*N*/               {
/*N*/                   if( pOPO->GetOutlinerMode() == OUTLINERMODE_DONTKNOW )
/*N*/                       pOPO->SetOutlinerMode( OUTLINERMODE_TEXTOBJECT );
/*N*/
/*N*/                   pOPO->FinishLoad( pSPool );
/*N*/               }
/*N*/           }
/*N*/
/*N*/           List* pPresObjList = pPage->GetPresObjList();
/*N*/           ULONG nObjCount = pPresObjList->Count();
/*N*/           if (nObjCount)
/*N*/           {
/*N*/               // Listen mit Titel- und Gliederungsvorlagen erstellen
/*N*/               String aName = pPage->GetLayoutName();
/*N*/               aName.Erase( aName.SearchAscii( SD_LT_SEPARATOR ));
/*N*/
/*N*/               List* pOutlineList = pSPool->CreateOutlineSheetList(aName);
/*N*/               SfxStyleSheet* pTitleSheet = (SfxStyleSheet*)
/*N*/                                               pSPool->GetTitleSheet(aName);
/*N*/
/*N*/               // jetzt nach Titel- und Gliederungstextobjekten suchen und
/*N*/               // Objekte zu Listenern machen
/*N*/               SdrAttrObj* pObj = (SdrAttrObj*)pPresObjList->First();
/*N*/               while (pObj)
/*N*/               {
/*N*/                   if (pObj->GetObjInventor() == SdrInventor)
/*N*/                   {
/*N*/                       OutlinerParaObject* pOPO = pObj->GetOutlinerParaObject();
/*N*/                       SdPage* pPage = (SdPage*) pObj->GetPage();
/*N*/                       UINT16 nId = pObj->GetObjIdentifier();
/*N*/
/*N*/                       if (nId == OBJ_TITLETEXT)
/*N*/                       {
/*N*/                           if( pOPO && pOPO->GetOutlinerMode() == OUTLINERMODE_DONTKNOW )
/*N*/                               pOPO->SetOutlinerMode( OUTLINERMODE_TITLEOBJECT );
/*N*/
/*N*/                           // TRUE: harte Attribute dabei nicht loeschen
/*N*/                           if (pTitleSheet)
/*N*/                               pObj->SetStyleSheet(pTitleSheet, TRUE);
/*N*/                       }
/*N*/                       else if (nId == OBJ_OUTLINETEXT)
/*N*/                       {
/*N*/                           if( pOPO && pOPO->GetOutlinerMode() == OUTLINERMODE_DONTKNOW )
/*N*/                               pOPO->SetOutlinerMode( OUTLINERMODE_OUTLINEOBJECT );
/*N*/
/*N*/                           for (USHORT nSheet = 0; nSheet < 10; nSheet++)
/*N*/                           {
/*N*/                               pSheet = (SfxStyleSheet*)pOutlineList->GetObject(nSheet);
/*N*/                               if (pSheet)
/*N*/                               {
/*N*/                                   pObj->StartListening(*pSheet);
/*N*/
/*N*/                                   if( nSheet == 0)
/*N*/                                       // Textrahmen hoert auf StyleSheet der Ebene1
/*N*/                                       pObj->NbcSetStyleSheet(pSheet, TRUE);
/*N*/                               }
/*N*/                           }
/*N*/                       }
/*N*/
/*N*/                       if (pObj->ISA(SdrTextObj) && pObj->IsEmptyPresObj() && pPage)
/*N*/                       {
/*N*/                           PresObjKind ePresObjKind = pPage->GetPresObjKind(pObj);
/*N*/                           String aString = pPage->GetPresObjText(ePresObjKind);
/*N*/
/*N*/                           if (aString.Len())
/*N*/                           {
/*N*/                               SdOutliner* pInternalOutl = GetInternalOutliner(TRUE);
/*N*/                               pInternalOutl->SetMinDepth(0);
/*N*/                               pPage->SetObjText( (SdrTextObj*) pObj, pInternalOutl, ePresObjKind, aString );
/*N*/                               pObj->NbcSetStyleSheet( pPage->GetStyleSheetForPresObj( ePresObjKind ), TRUE );
/*N*/                               pInternalOutl->Clear();
/*N*/                           }
/*N*/                       }
/*N*/                   }
/*N*/                   pObj = (SdrAttrObj*)pPresObjList->Next();
/*N*/               }
/*N*/
/*N*/               delete pOutlineList;
/*N*/           }
/*N*/       }
/*N*/
/*N*/       // Masterpages:
/*N*/       for (nPage = 0; nPage < GetMasterPageCount(); nPage++)
/*N*/       {
/*N*/           SdPage* pPage = (SdPage*)GetMasterPage(nPage);
/*N*/           SdrObjListIter aIter( *pPage );
/*N*/           while( aIter.IsMore() )
/*N*/           {
/*N*/               OutlinerParaObject* pOPO = aIter.Next()->GetOutlinerParaObject();
/*N*/               if( pOPO )
/*N*/               {
/*N*/                   if( pOPO->GetOutlinerMode() == OUTLINERMODE_DONTKNOW )
/*N*/                       pOPO->SetOutlinerMode( OUTLINERMODE_TEXTOBJECT );
/*N*/
/*N*/                   pOPO->FinishLoad( pSPool );
/*N*/               }
/*N*/           }
/*N*/
/*N*/           // BackgroundObjekt vor Selektion schuetzen #62144#
/*N*/           SdrObject* pBackObj = pPage->GetPresObj(PRESOBJ_BACKGROUND);
/*N*/           if(pBackObj)
/*N*/               pBackObj->SetMarkProtect(TRUE);
/*N*/
/*N*/           List* pPresObjList = pPage->GetPresObjList();
/*N*/           ULONG nObjCount = pPresObjList->Count();
/*N*/           if (nObjCount)
/*N*/           {
/*N*/               // Listen mit Titel- und Gliederungsvorlagen erstellen
/*N*/               String aName = pPage->GetLayoutName();
/*N*/               aName.Erase(aName.SearchAscii( SD_LT_SEPARATOR ));
/*N*/
/*N*/               List* pOutlineList = pSPool->CreateOutlineSheetList(aName);
/*N*/               SfxStyleSheet* pTitleSheet = (SfxStyleSheet*)
/*N*/                                               pSPool->GetTitleSheet(aName);
/*N*/
/*N*/               // jetzt nach Titel- und Gliederungstextobjekten suchen und
/*N*/               // Objekte zu Listenern machen
/*N*/               SdrAttrObj* pObj = (SdrAttrObj*)pPresObjList->First();
/*N*/               while (pObj)
/*N*/               {
/*N*/                   if (pObj->GetObjInventor() == SdrInventor)
/*N*/                   {
/*N*/                       OutlinerParaObject* pOPO = pObj->GetOutlinerParaObject();
/*N*/                       UINT16 nId = pObj->GetObjIdentifier();
/*N*/
/*N*/                       if (nId == OBJ_TITLETEXT)
/*N*/                       {
/*N*/                           if( pOPO && pOPO->GetOutlinerMode() == OUTLINERMODE_DONTKNOW )
/*N*/                               pOPO->SetOutlinerMode( OUTLINERMODE_TITLEOBJECT );
/*N*/
/*N*/                           // TRUE: harte Attribute dabei nicht loeschen
/*N*/                           if (pTitleSheet)
/*N*/                               pObj->SetStyleSheet(pTitleSheet, TRUE);
/*N*/                       }
/*N*/                       else if (nId == OBJ_OUTLINETEXT)
/*N*/                       {
/*N*/                           if( pOPO && pOPO->GetOutlinerMode() == OUTLINERMODE_DONTKNOW )
/*N*/                               pOPO->SetOutlinerMode( OUTLINERMODE_OUTLINEOBJECT );
/*N*/
/*N*/                           for (USHORT nSheet = 0; nSheet < 10; nSheet++)
/*N*/                           {
/*N*/                               pSheet = (SfxStyleSheet*)pOutlineList->GetObject(nSheet);
/*N*/                               if (pSheet)
/*N*/                               {
/*N*/                                   pObj->StartListening(*pSheet);
/*N*/
/*N*/                                   if( nSheet == 0)
/*N*/                                       // Textrahmen hoert auf StyleSheet der Ebene1
/*N*/                                       pObj->NbcSetStyleSheet(pSheet, TRUE);
/*N*/                               }
/*N*/                           }
/*N*/                       }
/*N*/
/*N*/                       SdPage* pPage = (SdPage*) pObj->GetPage();
/*N*/
/*N*/                       if (pObj->ISA(SdrTextObj) && pObj->IsEmptyPresObj() && pPage)
/*N*/                       {
/*N*/                           PresObjKind ePresObjKind = pPage->GetPresObjKind(pObj);
/*N*/                           String aString = pPage->GetPresObjText(ePresObjKind);
/*N*/
/*N*/                           if (aString.Len())
/*N*/                           {
/*N*/                               SdOutliner* pInternalOutl = GetInternalOutliner(TRUE);
/*N*/                               pInternalOutl->SetMinDepth(0);
/*N*/                               pPage->SetObjText( (SdrTextObj*) pObj, pInternalOutl, ePresObjKind, aString );
/*N*/                               pObj->NbcSetStyleSheet( pPage->GetStyleSheetForPresObj( ePresObjKind ), TRUE );
/*N*/                               pInternalOutl->Clear();
/*N*/                           }
/*N*/                       }
/*N*/                   }
/*N*/                   pObj = (SdrAttrObj*)pPresObjList->Next();
/*N*/               }
/*N*/
/*N*/               delete pOutlineList;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   bNewOrLoadCompleted = TRUE;
/*N*/
    /**************************************************************************
    * Alle gelinkten Pages aktualisieren
    **************************************************************************/
/*N*/   SdPage* pPage = NULL;
/*N*/   USHORT nMaxSdPages = GetSdPageCount(PK_STANDARD);
/*N*/
/*N*/   for (USHORT nSdPage=0; nSdPage < nMaxSdPages; nSdPage++)
/*N*/   {
/*N*/       pPage = (SdPage*) GetSdPage(nSdPage, PK_STANDARD);
/*N*/
/*N*/       if (pPage && pPage->GetFileName().Len() && pPage->GetBookmarkName().Len())
/*N*/       {
/*N*/           pPage->SetModel(this);
/*N*/       }
/*N*/   }
/*N*/
/*N*/   UpdateAllLinks();
/*N*/
/*N*/   SetChanged( FALSE );
/*N*/ }

/** updates all links, only links in this document should by resolved */
/*N*/ void SdDrawDocument::UpdateAllLinks()
/*N*/ {
/*N*/   if ( !pDocLockedInsertingLinks && pLinkManager && pLinkManager->GetLinks().Count() )
/*?*/   {
/*?*/       pDocLockedInsertingLinks = this; // lock inserting links. only links in this document should by resolved

/*?*/       pLinkManager->UpdateAllLinks();  // query box: update all links?

/*?*/       if( pDocLockedInsertingLinks == this )
/*?*/           pDocLockedInsertingLinks = NULL;  // unlock inserting links
/*?*/   }
/*N*/ }


/*************************************************************************
|*
|* Lokaler Outliner, welcher fuer den Gliederungsmodus verwendet wird
|* In diesen Outliner werden ggf. OutlinerViews inserted!
|*
\************************************************************************/

/*N*/ SdOutliner* SdDrawDocument::GetOutliner(BOOL bCreateOutliner)
/*N*/ {
/*N*/   if (!pOutliner && bCreateOutliner)
/*?*/   {
/*?*/       pOutliner = new SdOutliner( this, OUTLINERMODE_TEXTOBJECT );

/*?*/       if (pDocSh)
/*?*/           pOutliner->SetRefDevice( SD_MOD()->GetRefDevice( *pDocSh ) );

/*?*/       pOutliner->SetDefTab( nDefaultTabulator );
/*?*/       pOutliner->SetStyleSheetPool((SfxStyleSheetPool*)GetStyleSheetPool());
/*?*/       pOutliner->SetMinDepth(0);
/*?*/   }

/*N*/   return(pOutliner);
/*N*/ }


/*************************************************************************
|*
|* Interner Outliner, welcher fuer die Erzeugung von Textobjekten
|* verwendet wird.
|* In diesen Outliner werden keine OutlinerViews inserted!
|*
\************************************************************************/

/*N*/ SdOutliner* SdDrawDocument::GetInternalOutliner(BOOL bCreateOutliner)
/*N*/ {
/*N*/   if ( !pInternalOutliner && bCreateOutliner )
/*N*/   {
/*N*/       pInternalOutliner = new SdOutliner( this, OUTLINERMODE_TEXTOBJECT );
/*N*/       // MT:
/*N*/       // Dieser Outliner wird nur fuer das Erzeugen spezieller Textobjekte
/*N*/       // verwendet. Da in diesen Textobjekten keine Portion-Informationen
/*N*/       // gespeichert werden muessen, kann/soll der Update-Mode immer FALSE bleiben.
/*N*/       pInternalOutliner->SetUpdateMode( FALSE );
/*N*/       pInternalOutliner->EnableUndo( FALSE );
/*N*/
/*N*/       if (pDocSh)
/*N*/           pInternalOutliner->SetRefDevice( SD_MOD()->GetRefDevice( *pDocSh ) );
/*N*/
/*N*/       pInternalOutliner->SetDefTab( nDefaultTabulator );
/*N*/       pInternalOutliner->SetStyleSheetPool((SfxStyleSheetPool*)GetStyleSheetPool());
/*N*/       pInternalOutliner->SetMinDepth(0);
/*N*/   }
/*N*/
/*N*/   DBG_ASSERT( !pInternalOutliner || ( pInternalOutliner->GetUpdateMode() == FALSE ) , "InternalOutliner: UpdateMode = TRUE !" );
/*N*/   DBG_ASSERT( !pInternalOutliner || ( pInternalOutliner->IsUndoEnabled() == FALSE ), "InternalOutliner: Undo = TRUE !" );
/*N*/
/*N*/   // MT: Wer ihn vollmuellt, macht ihn auch gleich wieder leer:
/*N*/   // Vorteile:
/*N*/   // a) Keine unnoetigen Clear-Aufrufe
/*N*/   // b) Kein Muell im Speicher.
/*N*/   DBG_ASSERT( !pInternalOutliner || ( ( pInternalOutliner->GetParagraphCount() == 1 ) && ( pInternalOutliner->GetText( pInternalOutliner->GetParagraph( 0 ) ).Len() == 0 ) ), "InternalOutliner: Nicht leer!" );
/*N*/
/*N*/   return pInternalOutliner;
/*N*/ }

/*************************************************************************
|*
|* beim Starten der Praesentation den Navigator hochfahren oder nicht
|*
\************************************************************************/

/*N*/ void SdDrawDocument::SetStartPresWithNavigator(BOOL bStart)
/*N*/ {
/*N*/   bStartPresWithNavigator = bStart;
/*N*/ }

/*************************************************************************
|*
|* in der Praesentation bei einem Klick in die Flaeche nicht die Seite wechslen
|*
\************************************************************************/

/*N*/ void SdDrawDocument::SetPresLockedPages(BOOL bLock)
/*N*/ {
/*N*/   bPresLockedPages = bLock;
/*N*/ }

/*************************************************************************
|*
|* Praesentation immer oberstes Fenster oder nicht
|*
\************************************************************************/

/*N*/ void SdDrawDocument::SetPresAlwaysOnTop(BOOL bOnTop)
/*N*/ {
/*N*/   bPresAlwaysOnTop = bOnTop;
/*N*/ }

/*************************************************************************
|*
|* Praesentation im Vollbild-Modus oder im Fenster
|*
\************************************************************************/

/*N*/ void SdDrawDocument::SetPresFullScreen(BOOL bNewFullScreen)
/*N*/ {
/*N*/   bPresFullScreen = bNewFullScreen;
/*N*/ }


/*N*/ uno::Reference< uno::XInterface > SdDrawDocument::createUnoModel()
/*N*/ {
/*N*/   uno::Reference< uno::XInterface > xModel;
/*N*/
/*N*/   try
/*N*/   {
/*N*/       xModel = pDocSh->GetModel();
/*N*/   }
/*N*/   catch( uno::RuntimeException& e )
/*N*/   {
/*N*/       e;                              // to avoid a compiler warning...
/*N*/   }
/*N*/
/*N*/   return xModel;
/*N*/ }

/*N*/ SvxNumType SdDrawDocument::GetPageNumType() const
/*N*/ {
/*N*/   return ePageNumType;
/*N*/ }

/*N*/ void SdDrawDocument::SetPrinterIndependentLayout (sal_Int32 nMode)
/*N*/ {
/*N*/   // #108104#
/*N*/     // DBG_ASSERT (pDocSh!=NULL, "No available document shell to set ref device at.");
/*N*/
/*N*/   switch (nMode)
/*N*/     {
/*N*/         case ::com::sun::star::document::PrinterIndependentLayout::DISABLED:
/*N*/         case ::com::sun::star::document::PrinterIndependentLayout::ENABLED:
/*N*/             // Just store supported modes and inform the doc shell.
/*N*/             mnPrinterIndependentLayout = nMode;
/*N*/
/*N*/           // #108104#
/*N*/           // Since it is possible that a SdDrawDocument is constructed without a
/*N*/           // SdDrawDocShell the pointer member pDocSh needs to be tested
/*N*/           // before the call is executed. This is e.-g. used for copy/paste.
/*N*/           if(pDocSh)
/*N*/           {
/*N*/               pDocSh->UpdateRefDevice ();
/*N*/           }
/*N*/
/*N*/             break;
/*N*/
/*N*/         default:
/*N*/             // Ignore unknown values.
/*N*/             break;
/*N*/     }
/*N*/ }

/*N*/ sal_Int32 SdDrawDocument::GetPrinterIndependentLayout (void)
/*N*/ {
/*N*/     return mnPrinterIndependentLayout;
/*N*/ }
}
