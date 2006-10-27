/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_apphdl.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 23:58:14 $
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


#pragma hdrstop



#define _SVSTDARR_STRINGSDTOR

#ifndef INCLUDED_SVTOOLS_ACCESSIBILITYOPTIONS_HXX
#include <svtools/accessibilityoptions.hxx>
#endif
#ifndef _SFXEVENT_HXX //autogen
#include <bf_sfx2/event.hxx>
#endif
#ifndef INCLUDED_SVTOOLS_COLORCFG_HXX
#include <svtools/colorcfg.hxx>
#endif
#ifndef _SFXENUMITEM_HXX //autogen
#include <svtools/eitem.hxx>
#endif
#ifndef _SFX_WHITER_HXX //autogen
#include <svtools/whiter.hxx>
#endif
#ifndef _SFXSTBMGR_HXX //autogen
#include <bf_sfx2/stbmgr.hxx>
#endif
#ifndef _SFXISETHINT_HXX //autogen
#include <svtools/isethint.hxx>
#endif
#ifndef _SVX_DLG_HYPERLINK_HXX //autogen
#include <bf_offmgr/hyprlink.hxx>
#endif
#ifndef _SVTOOLS_CTLOPTIONS_HXX
#include <svtools/ctloptions.hxx>
#endif
#ifndef _SVX_INSCTRL_HXX //autogen
#include <bf_svx/insctrl.hxx>
#endif
#ifndef _SVX_SELCTRL_HXX //autogen
#include <bf_svx/selctrl.hxx>
#endif


#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _WRTSH_HXX
#include <wrtsh.hxx>
#endif
#ifndef _CMDID_H
#include <cmdid.h>          // Funktion-Ids
#endif
#ifndef _SWMODULE_HXX
#include <swmodule.hxx>
#endif
#ifndef _WDOCSH_HXX
#include <wdocsh.hxx>
#endif
#ifndef _WVIEW_HXX
#include <wview.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _GLOBALS_H
#include <globals.h>        // globale Konstanten z.B.
#endif
#ifndef _APP_HRC
#include <app.hrc>
#endif
#ifndef _USRPREF_HXX //autogen
#include <usrpref.hxx>
#endif
#ifndef _PRTOPT_HXX //autogen
#include <prtopt.hxx>
#endif
#ifndef _MODOPT_HXX //autogen
#include <modcfg.hxx>
#endif
#ifndef _FONTCFG_HXX //autogen
#include <fontcfg.hxx>
#endif
#ifndef _BARCFG_HXX
#include <barcfg.hxx>
#endif
#ifndef _UINUMS_HXX //autogen
#include <uinums.hxx>
#endif
#ifndef _DBCONFIG_HXX
#include <dbconfig.hxx>
#endif

// #107253#

using namespace ::com::sun::star;

#define C2S(cChar) String::CreateFromAscii(cChar)
/*--------------------------------------------------------------------
    Beschreibung: Slotmaps fuer Methoden der Applikation
 --------------------------------------------------------------------*/


// hier werden die SlotID's included
// siehe Idl-File
//
#define SwModule
#define ViewSettings
#define WebViewSettings
#define PrintSettings
#define _ExecAddress ExecOther
#define _StateAddress StateOther
#include "itemdef.hxx"

#ifndef _CFGID_H
#include <cfgid.h>
#endif

#include <shells.hrc>
#include "so3/staticbaseurl.hxx"
namespace binfilter {
#include "swslots.hxx"
/*N*/ SFX_IMPL_INTERFACE( SwModule, SfxModule, SW_RES(RID_SW_NAME) )
/*N*/ {
/*N*/   SFX_CHILDWINDOW_REGISTRATION(SvxHyperlinkDlgWrapper::GetChildWindowId());
/*N*/   SFX_STATUSBAR_REGISTRATION(SW_RES(CFG_STATUSBAR));
/*N*/     SFX_OBJECTBAR_REGISTRATION( SFX_OBJECTBAR_APPLICATION |
/*N*/             SFX_VISIBILITY_DESKTOP | SFX_VISIBILITY_STANDARD | SFX_VISIBILITY_CLIENT | SFX_VISIBILITY_VIEWER,
/*N*/             SW_RES(RID_MODULE_TOOLBOX) );
/*N*/ }

/*------------------------------------------------------------------------
 Beschreibung:  Funktionen Ansicht
------------------------------------------------------------------------*/



/*N*/sal_Bool lcl_IsViewMarks( const SwViewOption& rVOpt )
/*N*/{
/*N*/   return  rVOpt.IsHardBlank() &&
/*N*/           rVOpt.IsSoftHyph() &&
/*N*/            SwViewOption::IsFieldShadings();
/*N*/}

/*--------------------------------------------------------------------
    Beschreibung:   State mit CheckMark fuer ViewOptions
 --------------------------------------------------------------------*/


/*M*/ void SwModule::StateViewOptions(SfxItemSet &rSet)
/*M*/ {
/*M*/   SfxWhichIter aIter(rSet);
/*M*/   sal_uInt16 nWhich = aIter.FirstWhich();
/*M*/   SfxBoolItem aBool;
/*M*/   const SwViewOption* pOpt = 0;
    /*M*/   SwView* pActView = ::binfilter::GetActiveView();
/*M*/   SwDoc *pDoc = 0;
/*M*/   if(pActView)
/*M*/   {
/*M*/       pOpt = pActView->GetWrtShell().GetViewOptions();
/*M*/       pDoc = pActView->GetDocShell()->GetDoc();
/*M*/   }
/*M*/
/*M*/   while(nWhich)
/*M*/   {
/*M*/       if(pActView)
/*M*/       {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*M*/       }
/*M*/       else
/*M*/       {
/*M*/           rSet.DisableItem( nWhich );
/*M*/           nWhich = 0;
/*M*/       }
/*M*/
/*M*/       if( nWhich )
/*M*/       {
/*M*/           aBool.SetWhich( nWhich );
/*M*/           rSet.Put( aBool );
/*M*/       }
/*M*/       nWhich = aIter.NextWhich();
/*M*/   }
/*M*/ }

/*--------------------------------------------------------------------
    Beschreibung: Andere States
 --------------------------------------------------------------------*/


/*N*/void SwModule::StateOther(SfxItemSet &rSet)
/*N*/{
DBG_BF_ASSERT(0, "STRIP"); //STRIP001   SfxWhichIter aIter(rSet);
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung:   Wizzards
 --------------------------------------------------------------------*/


/*N*/void SwModule::ExecWizzard(SfxRequest & rReq)
/*N*/{
/*?*/   DBG_BF_ASSERT(0, "STRIP"); //STRIP001 Wizzard( rReq.GetSlot() );
/*N*/}

/*--------------------------------------------------------------------
    Beschreibung:   Einstellungen fuer den Bildschirm
 --------------------------------------------------------------------*/


/*N*/ void SwModule::ExecViewOptions(SfxRequest &rReq)
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung:   Felddialog starten
 --------------------------------------------------------------------*/


/*N*/void SwModule::ExecOther(SfxRequest& rReq)
/*N*/{
DBG_BF_ASSERT(0, "STRIP"); //STRIP001   const SfxItemSet *pArgs = rReq.GetArgs();
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

/*
SfxMacro *SwWriterApp::CreateMacro() const
{
    return BasicIDE::CreateMacro();
} */

/*--------------------------------------------------------------------
    Beschreibung: Notifies abfangen
 --------------------------------------------------------------------*/


    // Hint abfangen fuer DocInfo
/*M*/ void SwModule::Notify( SfxBroadcaster& rBC, const SfxHint& rHint )
/*M*/ {
/*M*/   if( rHint.ISA( SfxEventHint ) )
/*M*/   {
/*M*/       SfxEventHint& rEvHint = (SfxEventHint&) rHint;
/*M*/       SwDocShell* pDocSh = PTR_CAST( SwDocShell, rEvHint.GetObjShell() );
/*M*/       if( pDocSh )
/*M*/       {
/*M*/           SwWrtShell* pWrtSh = pDocSh ? pDocSh->GetWrtShell() : 0;
/*M*/           switch( rEvHint.GetEventId() )
/*M*/           {
/*          MA 07. Mar. 96: UpdateInputFlds() nur noch bei Dokument neu.
                                (Und bei Einfuegen Textbaust.)
                case SFX_EVENT_OPENDOC:
                // dann am aktuellen Dokument die Input-Fedler updaten
                if( pWrtSh )
                    pWrtSh->UpdateInputFlds();
                break;
*/
/*M*/           case SFX_EVENT_CREATEDOC:
/*M*/               // alle FIX-Date/Time Felder auf akt. setzen
/*M*/               if( pWrtSh )
/*M*/               {
/*?*/               DBG_BF_ASSERT(0, "STRIP"); //STRIP001   pWrtSh->SetFixFields();
/*M*/               }
/*M*/               break;
/*M*/           }
/*M*/       }
/*M*/   }
/*M*/   else if(rHint.ISA(SfxItemSetHint))
/*M*/   {
/*M*/       if( SFX_ITEM_SET == ((SfxItemSetHint&)rHint).GetItemSet().GetItemState(SID_ATTR_PATHNAME))
/*M*/       {
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 ::GetGlossaries()->UpdateGlosPath( sal_False );
/*M*/       }
/*M*/
/*M*/       if( SFX_ITEM_SET == ((SfxItemSetHint&)rHint).GetItemSet().
/*M*/                   GetItemState( SID_ATTR_ADDRESS, sal_False ))
/*M*/           bAuthorInitialised = FALSE;
/*M*/   }
/*M*/     else if(rHint.ISA(SfxSimpleHint))
/*M*/     {
/*M*/         ULONG nHintId = ((SfxSimpleHint&)rHint).GetId();
/*M*/         if(SFX_HINT_COLORS_CHANGED == nHintId ||
/*N*/            SFX_HINT_ACCESSIBILITY_CHANGED == nHintId )
/*M*/         {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/         }
/*N*/         else if( SFX_HINT_CTL_SETTINGS_CHANGED == nHintId )
/*N*/         {
/*N*/             const SfxObjectShell* pObjSh = SfxObjectShell::GetFirst();
/*N*/             while( pObjSh )
/*N*/             {
/*N*/                 if( pObjSh->IsA(TYPE(SwDocShell)) )
/*N*/                 {
/*N*/                     const SwDoc* pDoc = ((SwDocShell*)pObjSh)->GetDoc();
/*N*/                     ViewShell* pVSh = 0;
/*N*/                     pDoc->GetEditShell( &pVSh );
/*N*/                     if ( pVSh )
/*N*/                         pVSh->ChgNumberDigits();
/*N*/                 }
/*N*/                 pObjSh = SfxObjectShell::GetNext(*pObjSh);
/*N*/             }
/*N*/         }
/*M*/         else if(SFX_HINT_DEINITIALIZING == nHintId)
/*M*/         {
/*M*/             DELETEZ(pWebUsrPref);
/*M*/             DELETEZ(pUsrPref)   ;
/*M*/             DELETEZ(pModuleConfig);
/*M*/             DELETEZ(pPrtOpt)      ;
/*M*/             DELETEZ(pWebPrtOpt)   ;
/*M*/             DELETEZ(pChapterNumRules);
/*M*/             DELETEZ(pStdFontConfig)     ;
/*M*/             DELETEZ(pToolbarConfig)     ;
/*M*/             DELETEZ(pWebToolbarConfig)  ;
/*M*/             DELETEZ(pAuthorNames)       ;
/*M*/             DELETEZ(pDBConfig);
/*M*/             EndListening(*pColorConfig);
/*M*/             DELETEZ(pColorConfig);
/*M*/             EndListening(*pAccessibilityOptions);
/*N*/             DELETEZ(pAccessibilityOptions);
/*N*/             EndListening(*pCTLOptions);
/*N*/             DELETEZ(pCTLOptions);
/*M*/         }
/*M*/   }
/*M*/ }
/*N*/ void SwModule::FillStatusBar( StatusBar& rStatusBar )
/*N*/ {
/*N*/   // Hier den StatusBar initialisieren
/*N*/   // und Elemente reinschieben
/*N*/
/*N*/   // Anzeige Seite
/*N*/   String aTmp; aTmp.Fill( 10, 'X' );
/*N*/   rStatusBar.InsertItem( FN_STAT_PAGE, rStatusBar.GetTextWidth(
/*N*/                                   aTmp ), SIB_AUTOSIZE | SIB_LEFT);
/*N*/   rStatusBar.SetHelpId(FN_STAT_PAGE, FN_STAT_PAGE);
/*N*/
/*N*/   // Seitenvorlage
/*N*/   aTmp.Fill( 15, 'X' );
/*N*/   rStatusBar.InsertItem( FN_STAT_TEMPLATE, rStatusBar.GetTextWidth(
/*N*/                                   aTmp ), SIB_AUTOSIZE | SIB_LEFT );
/*N*/   rStatusBar.SetHelpId(FN_STAT_TEMPLATE, FN_STAT_TEMPLATE);
/*N*/
/*N*/   // Zoomeinstellungen
/*N*/   rStatusBar.InsertItem( SID_ATTR_ZOOM, rStatusBar.GetTextWidth(
/*N*/                                                           C2S("1000%")) );
/*N*/   rStatusBar.SetHelpId(SID_ATTR_ZOOM, SID_ATTR_ZOOM);
/*N*/
/*N*/   // Insert/Overwrite
/*N*/   rStatusBar.InsertItem( SID_ATTR_INSERT,
/*N*/       SvxInsertStatusBarControl::GetDefItemWidth(rStatusBar));
/*N*/   rStatusBar.SetHelpId(SID_ATTR_INSERT, SID_ATTR_INSERT);
/*N*/
/*N*/   // awt::Selection-Modus
/*N*/   rStatusBar.InsertItem( FN_STAT_SELMODE,
/*N*/           SvxSelectionModeControl::GetDefItemWidth(rStatusBar));
/*N*/
/*N*/   rStatusBar.SetHelpId(FN_STAT_SELMODE, FN_STAT_SELMODE);
/*N*/
/*N*/   // Hyperlink ausfuehren/bearbeiten
/*N*/   rStatusBar.InsertItem( FN_STAT_HYPERLINKS, rStatusBar.GetTextWidth(
/*N*/                                                           C2S("HYP")) );
/*N*/   rStatusBar.SetHelpId(FN_STAT_HYPERLINKS, FN_STAT_HYPERLINKS);
/*N*/
/*N*/   // Dokument geaendert
/*N*/   rStatusBar.InsertItem( SID_DOC_MODIFIED, rStatusBar.GetTextWidth(
/*N*/                                                               C2S("*")));
/*N*/   rStatusBar.SetHelpId(SID_DOC_MODIFIED, SID_DOC_MODIFIED);
/*N*/
/*N*/   // den aktuellen Context anzeigen Uhrzeit / FrmPos / TabellenInfo
/*N*/   aTmp.Fill( 25, sal_Unicode('X') );
/*N*/   rStatusBar.InsertItem( SID_ATTR_SIZE, rStatusBar.GetTextWidth(
/*N*/                   aTmp ), SIB_AUTOSIZE | SIB_LEFT | SIB_USERDRAW);
/*N*/   rStatusBar.SetHelpId(SID_ATTR_SIZE, SID_ATTR_SIZE);
/*N*/ }

/* -----------------------------20.02.01 12:43--------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ SwDBConfig*   SwModule::GetDBConfig()
/*N*/ {
/*N*/   if(!pDBConfig)
/*N*/       pDBConfig = new SwDBConfig;
/*N*/   return pDBConfig;
/*N*/ }
/* -----------------------------11.04.2002 15:27------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ svtools::ColorConfig& SwModule::GetColorConfig()
/*N*/ {
/*N*/     if(!pColorConfig)
/*N*/   {
/*N*/         pColorConfig = new svtools::ColorConfig;
/*N*/       SwViewOption::ApplyColorConfigValues(*pColorConfig);
/*N*/         StartListening(*pColorConfig);
/*N*/     }
/*N*/     return *pColorConfig;
/*N*/ }
/* -----------------------------06.05.2002 09:42------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ SvtAccessibilityOptions& SwModule::GetAccessibilityOptions()
/*N*/ {
/*N*/     if(!pAccessibilityOptions)
/*N*/     {
/*N*/         pAccessibilityOptions = new SvtAccessibilityOptions;
/*N*/         StartListening(*pAccessibilityOptions);
/*N*/     }
/*N*/     return *pAccessibilityOptions;
/*N*/ }
/*-----------------30.01.97 08.30-------------------

--------------------------------------------------*/
SvtCTLOptions& SwModule::GetCTLOptions()
{
    if(!pCTLOptions)
    {
        pCTLOptions = new SvtCTLOptions;
        StartListening(*pCTLOptions);
    }
    return *pCTLOptions;
}
/*-----------------30.01.97 08.30-------------------

--------------------------------------------------*/
/*N*/ const SwMasterUsrPref *SwModule::GetUsrPref(sal_Bool bWeb) const
/*N*/ {
/*N*/   SwModule* pNonConstModule = (SwModule*)this;
/*N*/   if(bWeb && !pWebUsrPref)
/*N*/   {
/*N*/       // im Load der SwMasterUsrPref wird der SpellChecker gebraucht, dort darf
/*N*/       // er aber nicht angelegt werden #58256#
/*N*/       pNonConstModule->pWebUsrPref = new SwMasterUsrPref(TRUE);
/*N*/   }
/*N*/   else if(!bWeb && !pUsrPref)
/*N*/   {
/*N*/       pNonConstModule->pUsrPref = new SwMasterUsrPref(FALSE);
/*N*/   }
/*N*/   return  bWeb ? pWebUsrPref : pUsrPref;
/*N*/ }


}
