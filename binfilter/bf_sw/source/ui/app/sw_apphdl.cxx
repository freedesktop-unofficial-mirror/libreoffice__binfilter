/*************************************************************************
 *
 *  $RCSfile: sw_apphdl.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:20:20 $
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

#ifndef _URLOBJ_HXX
#include <tools/urlobj.hxx>
#endif

#define _SVSTDARR_STRINGSDTOR
#include <svtools/svstdarr.hxx>

#ifndef SVTOOLS_URIHELPER_HXX
#include <svtools/urihelper.hxx>
#endif
#ifndef INCLUDED_SVTOOLS_UNDOOPT_HXX
#include <svtools/undoopt.hxx>
#endif
#ifndef INCLUDED_SVTOOLS_PATHOPTIONS_HXX
#include <svtools/pathoptions.hxx>
#endif
#ifndef INCLUDED_SVTOOLS_ACCESSIBILITYOPTIONS_HXX
#include <svtools/accessibilityoptions.hxx>
#endif
#ifndef _SFXDISPATCH_HXX //autogen
#include <bf_sfx2/dispatch.hxx>
#endif
#ifndef _SFXEVENT_HXX //autogen
#include <bf_sfx2/event.hxx>
#endif
#ifndef _SVX_SRCHITEM_HXX
#include <bf_svx/srchitem.hxx>
#endif
#ifndef INCLUDED_SVTOOLS_COLORCFG_HXX
#include <svtools/colorcfg.hxx>
#endif
#ifndef _SFXENUMITEM_HXX //autogen
#include <svtools/eitem.hxx>
#endif
#ifndef _OFF_APP_HXX //autogen
#include <bf_offmgr/app.hxx>
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
#ifndef _SFXREQUEST_HXX //autogen
#include <bf_sfx2/request.hxx>
#endif
#ifndef _OFA_OSPLCFG_HXX //autogen
#include <bf_offmgr/osplcfg.hxx>
#endif
#ifndef _SFXSTRITEM_HXX //autogen
#include <svtools/stritem.hxx>
#endif
#ifndef _SVTOOLS_LINGUCFG_HXX_
#include <svtools/lingucfg.hxx>
#endif
#ifndef _SVTOOLS_CTLOPTIONS_HXX
#include <svtools/ctloptions.hxx>
#endif
#ifndef _SVX_ADRITEM_HXX //autogen
#include <bf_svx/adritem.hxx>
#endif
#ifndef _VCL_MSGBOX_HXX //autogen
#include <vcl/msgbox.hxx>
#endif
#ifndef _VCL_WRKWIN_HXX //autogen
#include <vcl/wrkwin.hxx>
#endif
#ifndef _SVX_INSCTRL_HXX //autogen
#include <bf_svx/insctrl.hxx>
#endif
#ifndef _SVX_SELCTRL_HXX //autogen
#include <bf_svx/selctrl.hxx>
#endif
#ifndef _NAVICFG_HXX
#include <navicfg.hxx>
#endif

#ifndef _VIEW_HXX
#include <view.hxx>
#endif
#ifndef _SWPVIEW_HXX
#include <pview.hxx>
#endif
#ifndef _SRCVIEW_HXX
#include <srcview.hxx>
#endif
#ifndef _WRTSH_HXX
#include <wrtsh.hxx>
#endif
#ifndef _DOCSH_HXX
#include <docsh.hxx>
#endif
#ifndef _CMDID_H
#include <cmdid.h>          // Funktion-Ids
#endif
#ifndef _INITUI_HXX
#include <initui.hxx>
#endif
#ifndef _UITOOL_HXX
#include <uitool.hxx>
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
#ifndef _WIZZARD_HXX
#include <wizzard.hxx>      // Wizzards
#endif
#ifndef _USRPREF_HXX
#include <usrpref.hxx>
#endif
#ifndef _GLOSLST_HXX
#include <gloslst.hxx>      // SwGlossaryList
#endif
#ifndef _GLOSDOC_HXX
#include <glosdoc.hxx>      // SwGlossaryList
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _CFGITEMS_HXX
#include <cfgitems.hxx>
#endif
#ifndef _PRTOPT_HXX
#include <prtopt.hxx>
#endif
#ifndef _MODCFG_HXX
#include <modcfg.hxx>
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
#ifndef _LINGUISTIC_LNGPROPS_HHX_
#include <bf_linguistic/lngprops.hxx>
#endif
#ifndef _UNO_LINGU_HXX
#include <bf_svx/unolingu.hxx>
#endif
#ifndef _SFX_SFXUNO_HXX
#include <bf_sfx2/sfxuno.hxx>
#endif
#ifndef _COM_SUN_STAR_BEANS_PROPERTYVALUES_HPP_
#include <com/sun/star/beans/PropertyValues.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
#include <com/sun/star/beans/XPropertySet.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_PROPERTYVALUE_HPP_
#include <com/sun/star/beans/PropertyValue.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_PROPERTYSTATE_HPP_
#include <com/sun/star/beans/PropertyState.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSETINFO_HPP_
#include <com/sun/star/beans/XPropertySetInfo.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_XMULTIPROPERTYSET_HPP_
#include <com/sun/star/beans/XMultiPropertySet.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_XFASTPROPERTYSET_HPP_
#include <com/sun/star/beans/XFastPropertySet.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_XVETOABLECHANGELISTENER_HPP_
#include <com/sun/star/beans/XVetoableChangeListener.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSTATE_HPP_
#include <com/sun/star/beans/XPropertyState.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSTATECHANGELISTENER_HPP_
#include <com/sun/star/beans/XPropertyStateChangeListener.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_PROPERTYATTRIBUTE_HPP_
#include <com/sun/star/beans/PropertyAttribute.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTIESCHANGELISTENER_HPP_
#include <com/sun/star/beans/XPropertiesChangeListener.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYCHANGELISTENER_HPP_
#include <com/sun/star/beans/XPropertyChangeListener.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYACCESS_HPP_
#include <com/sun/star/beans/XPropertyAccess.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYCONTAINER_HPP_
#include <com/sun/star/beans/XPropertyContainer.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_PROPERTYSTATECHANGEEVENT_HPP_
#include <com/sun/star/beans/PropertyStateChangeEvent.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_PROPERTYCHANGEEVENT_HPP_
#include <com/sun/star/beans/PropertyChangeEvent.hpp>
#endif

// #107253#
#ifndef _SWLINGUCONFIG_HXX
#include <swlinguconfig.hxx>
#endif

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
#include <bf_svx/svxslots.hxx>
#include "swslots.hxx"
#ifndef _CFGID_H
#include <cfgid.h>
#endif

#include <shells.hrc>

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

//STRIP001 void lcl_SetViewMetaChars( SwViewOption& rVOpt, sal_Bool bOn)
//STRIP001 {
//STRIP001  rVOpt.SetViewMetaChars( bOn );
//STRIP001  if(bOn && !(rVOpt.IsParagraph()     ||
//STRIP001          rVOpt.IsTab()       ||
//STRIP001          rVOpt.IsLineBreak() ||
//STRIP001          rVOpt.IsBlank()))
//STRIP001  {
//STRIP001      rVOpt.SetParagraph(bOn);
//STRIP001      rVOpt.SetTab(bOn);
//STRIP001      rVOpt.SetLineBreak(bOn);
//STRIP001      rVOpt.SetBlank(bOn);
//STRIP001  }
//STRIP001 }


/*N*/sal_Bool lcl_IsViewMarks( const SwViewOption& rVOpt )
/*N*/{
/*N*/   return  rVOpt.IsHardBlank() &&
/*N*/           rVOpt.IsSoftHyph() &&
/*N*/            SwViewOption::IsFieldShadings();
/*N*/}
//STRIP001 void lcl_SetViewMarks(SwViewOption& rVOpt, sal_Bool bOn )
//STRIP001 {
//STRIP001  rVOpt.SetHardBlank(bOn);
//STRIP001  rVOpt.SetSoftHyph(bOn);
//STRIP001     SwViewOption::SetAppearanceFlag(
//STRIP001             VIEWOPT_FIELD_SHADINGS, bOn, TRUE);
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung:   State mit CheckMark fuer ViewOptions
 --------------------------------------------------------------------*/


/*M*/ void SwModule::StateViewOptions(SfxItemSet &rSet)
/*M*/ {
/*M*/   SfxWhichIter aIter(rSet);
/*M*/   sal_uInt16 nWhich = aIter.FirstWhich();
/*M*/   SfxBoolItem aBool;
/*M*/   const SwViewOption* pOpt = 0;
/*M*/   SwView* pActView = ::GetActiveView();
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
/*M*/       {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/            sal_Bool bReadonly = pActView->GetDocShell()->IsReadOnly();
//STRIP001 /*?*/            sal_Bool bBrowse = pDoc ? pDoc->IsBrowseMode() : sal_False;
//STRIP001 /*?*/            if ( bReadonly && nWhich != FN_VIEW_GRAPHIC )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                rSet.DisableItem(nWhich);
//STRIP001 /*?*/                nWhich = 0;
//STRIP001 /*?*/            }
//STRIP001 /*?*/            switch(nWhich)
//STRIP001 /*?*/            {
//STRIP001 /*?*/                case FN_RULER:
//STRIP001 /*?*/                 {
//STRIP001 /*?*/                     if(!pOpt->IsViewHRuler(TRUE) && !pOpt->IsViewVRuler(TRUE))
//STRIP001 /*?*/                     {
//STRIP001 /*?*/                         rSet.DisableItem(nWhich);
//STRIP001 /*?*/                         nWhich = 0;
//STRIP001 /*?*/                     }
//STRIP001 /*?*/                     else
//STRIP001 /*?*/                         aBool.SetValue( pOpt->IsViewAnyRuler());
//STRIP001 /*?*/                 }
//STRIP001 /*?*/                 break;
//STRIP001 /*?*/                case FN_VIEW_BOUNDS:
//STRIP001 /*?*/                     aBool.SetValue( SwViewOption::IsDocBoundaries()); break;
//STRIP001 /*?*/                case FN_VIEW_GRAPHIC:
//STRIP001 /*?*/                    aBool.SetValue( !pOpt->IsGraphic() ); break;
//STRIP001 /*?*/                case FN_VIEW_FIELDS:
//STRIP001 /*?*/                     aBool.SetValue( SwViewOption::IsFieldShadings() ); break;
//STRIP001 /*?*/                case FN_VIEW_FIELDNAME:
//STRIP001 /*?*/                    aBool.SetValue( pOpt->IsFldName() ); break;
//STRIP001 /*?*/                case FN_VIEW_MARKS:
//STRIP001 /*?*/                    aBool.SetValue( lcl_IsViewMarks(*pOpt) ); break;
//STRIP001 /*?*/                case FN_VIEW_META_CHARS:
//STRIP001 /*?*/                    aBool.SetValue( pOpt->IsViewMetaChars() ); break;
//STRIP001 /*?*/                case FN_VIEW_TABLEGRID:
//STRIP001 /*?*/                     aBool.SetValue( SwViewOption::IsTableBoundaries() ); break;
//STRIP001 /*?*/                case FN_VIEW_HIDDEN_PARA:
//STRIP001 /*?*/                    aBool.SetValue( pOpt->IsShowHiddenPara()); break;
//STRIP001 /*?*/                case SID_GRID_VISIBLE:
//STRIP001 /*?*/                    aBool.SetValue( pOpt->IsGridVisible() ); break;
//STRIP001 /*?*/                case SID_GRID_USE:
//STRIP001 /*?*/                    aBool.SetValue( pOpt->IsSnap() ); break;
//STRIP001 /*?*/                case SID_HELPLINES_MOVE:
//STRIP001 /*?*/                    aBool.SetValue( pOpt->IsCrossHair() ); break;
//STRIP001 /*?*/                case FN_VIEW_SMOOTH_SCROLL:
//STRIP001 /*?*/                    aBool.SetValue( pOpt->IsSmoothScroll()); break;
//STRIP001 /*?*/                case FN_VLINEAL:
//STRIP001 /*?*/                    aBool.SetValue( pActView->StatVLineal() ); break;
//STRIP001 /*?*/                case FN_HSCROLLBAR:
//STRIP001 /*?*/                    if(bBrowse)
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        rSet.DisableItem(nWhich);
//STRIP001 /*?*/                        nWhich = 0;
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                    else
//STRIP001 /*?*/                         aBool.SetValue( pActView->IsHScrollbarVisible() ); break;
//STRIP001 /*?*/                case FN_VSCROLLBAR:
//STRIP001 /*?*/                     aBool.SetValue( pActView->IsVScrollbarVisible() ); break;
//STRIP001 /*?*/                case SID_AUTOSPELL_CHECK:
//STRIP001 /*?*/                    aBool.SetValue( pOpt->IsOnlineSpell() );
//STRIP001 /*?*/                break;
//STRIP001 /*?*/                case SID_AUTOSPELL_MARKOFF:
//STRIP001 /*?*/                    aBool.SetValue( pOpt->IsHideSpell() );
//STRIP001 /*?*/                break;
//STRIP001 /*?*/                case FN_SHADOWCURSOR:
//STRIP001 /*?*/                    if (pDoc == 0 || pDoc->IsBrowseMode())
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        rSet.DisableItem( nWhich );
//STRIP001 /*?*/                        nWhich = 0;
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                    else
//STRIP001 /*?*/                        aBool.SetValue( pOpt->IsShadowCursor() );
//STRIP001 /*?*/                break;
//STRIP001 /*?*/
//STRIP001 /*?*/            }
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
DBG_ASSERT(0, "STRIP"); //STRIP001  SfxWhichIter aIter(rSet);
//STRIP001  sal_uInt16 nWhich = aIter.FirstWhich();
//STRIP001
//STRIP001  SwView* pActView = ::GetActiveView();
//STRIP001  sal_Bool bWebView = 0 != PTR_CAST(SwWebView, pActView);
//STRIP001
//STRIP001  while(nWhich)
//STRIP001  {
//STRIP001      switch(nWhich)
//STRIP001      {
//STRIP001          case FN_BUSINESS_CARD:
//STRIP001          case FN_LABEL:
//STRIP001          case FN_ENVELOP:
//STRIP001          {
//STRIP001              sal_Bool bDisable = sal_False;
//STRIP001              SfxViewShell* pView = SfxViewShell::Current();
//STRIP001              if( !pView || (pView && !pView->ISA(SwView)) )
//STRIP001                  bDisable = sal_True;
//STRIP001              SwDocShell *pDocSh = (SwDocShell*) SfxObjectShell::Current();
//STRIP001              if ( bDisable ||
//STRIP001                  (pDocSh &&    (pDocSh->IsReadOnly() ||
//STRIP001                                pDocSh->GetCreateMode() == SFX_CREATE_MODE_EMBEDDED)) )
//STRIP001                  rSet.DisableItem( nWhich );
//STRIP001
//STRIP001          }
//STRIP001          break;
//STRIP001          case FN_EDIT_FORMULA:
//STRIP001              {
//STRIP001                  SwWrtShell* pSh = 0;
//STRIP001                  int nSelection = 0;
//STRIP001                  if( pActView )
//STRIP001                      pSh = &pActView->GetWrtShell();
//STRIP001                  if( pSh )
//STRIP001                      nSelection = pSh->GetSelectionType();
//STRIP001
//STRIP001                  if( (pSh && pSh->HasSelection()) ||
//STRIP001                      !(nSelection & (SwWrtShell::SEL_TXT | SwWrtShell::SEL_TBL)))
//STRIP001                      rSet.DisableItem(nWhich);
//STRIP001              }
//STRIP001          break;
//STRIP001          case SID_ATTR_ADDRESS:
//STRIP001          {
//STRIP001              SvxAddressItem aAddress;
//STRIP001              aAddress.SetWhich( nWhich );
//STRIP001              rSet.Put( aAddress );
//STRIP001          }
//STRIP001          break;
//STRIP001          case SID_ATTR_UNDO_COUNT:
//STRIP001              rSet.Put(SfxUInt16Item( SID_ATTR_UNDO_COUNT, SwEditShell::GetUndoActionCount()));
//STRIP001          break;
//STRIP001          case SID_ATTR_METRIC:
//STRIP001              rSet.Put( SfxUInt16Item( SID_ATTR_METRIC, ::GetDfltMetric(bWebView)));
//STRIP001          break;
//STRIP001          case FN_SET_MODOPT_TBLNUMFMT:
//STRIP001              rSet.Put( SfxBoolItem( nWhich, pModuleConfig->
//STRIP001                                          IsInsTblFormatNum( bWebView )));
//STRIP001          break;
//STRIP001             default:
//STRIP001              DBG_ERROR("::StateOther: default");
//STRIP001      }
//STRIP001      nWhich = aIter.NextWhich();
//STRIP001  }
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung:   Wizzards
 --------------------------------------------------------------------*/


/*N*/void SwModule::ExecWizzard(SfxRequest & rReq)
/*N*/{
/*?*/   DBG_ASSERT(0, "STRIP"); //STRIP001 Wizzard( rReq.GetSlot() );
/*N*/}

/*--------------------------------------------------------------------
    Beschreibung:   Einstellungen fuer den Bildschirm
 --------------------------------------------------------------------*/


/*N*/ void SwModule::ExecViewOptions(SfxRequest &rReq)
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  SwViewOption* pOpt = 0;
//STRIP001  OfficeApplication* pOffApp = OFF_APP();
//STRIP001  sal_Bool bModified = sal_True;
//STRIP001  if ( GetView() )
//STRIP001  {
//STRIP001      pOpt = new SwViewOption( *GetView()->GetWrtShell().GetViewOptions() );
//STRIP001      bModified = GetView()->GetWrtShell().IsModified();
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      pOpt = new SwViewOption();
//STRIP001      DBG_ERROR("ExecViewOptions: ohne View - falsche UsrPref?")
//STRIP001      MakeUsrPref(*pOpt, sal_False);
//STRIP001  }
//STRIP001
//STRIP001
//STRIP001  int eState = STATE_TOGGLE;
//STRIP001  sal_Bool bSet = sal_False;
//STRIP001
//STRIP001  const SfxItemSet *pArgs = rReq.GetArgs();
//STRIP001  sal_uInt16 nSlot = rReq.GetSlot();
//STRIP001     const SfxPoolItem* pAttr=NULL;
//STRIP001
//STRIP001  if( pArgs && SFX_ITEM_SET == pArgs->GetItemState( nSlot , sal_False, &pAttr ))
//STRIP001  {
//STRIP001      bSet = ((SfxBoolItem*)pAttr)->GetValue();
//STRIP001         eState = bSet ? STATE_ON : STATE_OFF;
//STRIP001  }
//STRIP001
//STRIP001  int bFlag = STATE_ON == eState;
//STRIP001  // fuer die (WebViewSettings
//STRIP001  enum WebDepend
//STRIP001  {
//STRIP001      DEPEND_NONE,
//STRIP001      DEPEND_NOWEB,
//STRIP001      DEPEND_WEB
//STRIP001  }eWebDepend = DEPEND_NONE;
//STRIP001
//STRIP001  uno::Reference< beans::XPropertySet >  xLngProp( ::GetLinguPropertySet() );
//STRIP001
//STRIP001  switch ( nSlot )
//STRIP001  {
//STRIP001      case FN_VIEW_GRAPHIC:
//STRIP001
//STRIP001              if( STATE_TOGGLE == eState )
//STRIP001                  bFlag = !pOpt->IsGraphic();
//STRIP001              pOpt->SetGraphic( bFlag );
//STRIP001              break;
//STRIP001
//STRIP001      case FN_VIEW_FIELDS:
//STRIP001              if( STATE_TOGGLE == eState )
//STRIP001                     bFlag = !SwViewOption::IsFieldShadings() ;
//STRIP001                 SwViewOption::SetAppearanceFlag(VIEWOPT_FIELD_SHADINGS, bFlag, TRUE );
//STRIP001              break;
//STRIP001
//STRIP001      case FN_VIEW_BOUNDS:
//STRIP001              if( STATE_TOGGLE == eState )
//STRIP001                     bFlag = !SwViewOption::IsDocBoundaries();
//STRIP001                 SwViewOption::SetAppearanceFlag(VIEWOPT_DOC_BOUNDARIES, bFlag, TRUE );
//STRIP001              break;
//STRIP001
//STRIP001      case SID_GRID_VISIBLE:
//STRIP001              if( STATE_TOGGLE == eState )
//STRIP001                  bFlag = !pOpt->IsGridVisible();
//STRIP001
//STRIP001              pOpt->SetGridVisible( bFlag );
//STRIP001              break;
//STRIP001
//STRIP001      case SID_GRID_USE:
//STRIP001              if( STATE_TOGGLE == eState )
//STRIP001                  bFlag = !pOpt->IsSnap();
//STRIP001
//STRIP001              pOpt->SetSnap( bFlag );
//STRIP001              break;
//STRIP001
//STRIP001      case SID_HELPLINES_MOVE:
//STRIP001              if( STATE_TOGGLE == eState )
//STRIP001                  bFlag = !pOpt->IsCrossHair();
//STRIP001
//STRIP001              pOpt->SetCrossHair( bFlag );
//STRIP001              break;
//STRIP001
//STRIP001      case FN_VIEW_HIDDEN_PARA:
//STRIP001              if ( STATE_TOGGLE == eState )
//STRIP001                  bFlag = !pOpt->IsShowHiddenPara();
//STRIP001
//STRIP001              pOpt->SetShowHiddenPara( bFlag );
//STRIP001              break;
//STRIP001
//STRIP001      case FN_VIEW_SMOOTH_SCROLL:
//STRIP001
//STRIP001              if ( STATE_TOGGLE == eState )
//STRIP001                  bFlag = !pOpt->IsSmoothScroll();
//STRIP001
//STRIP001              pOpt->SetSmoothScroll( bFlag );
//STRIP001              break;
//STRIP001
//STRIP001
//STRIP001      case FN_VLINEAL:
//STRIP001              if( STATE_TOGGLE == eState )
//STRIP001                     bFlag = !pOpt->IsViewVRuler();
//STRIP001
//STRIP001                 pOpt->SetViewVRuler( bFlag );
//STRIP001              break;
//STRIP001
//STRIP001      case FN_VSCROLLBAR:
//STRIP001              if( STATE_TOGGLE == eState )
//STRIP001                  bFlag = !pOpt->IsViewVScrollBar();
//STRIP001
//STRIP001              pOpt->SetViewVScrollBar( bFlag );
//STRIP001              break;
//STRIP001
//STRIP001      case FN_HSCROLLBAR:
//STRIP001              if( STATE_TOGGLE == eState )
//STRIP001                  bFlag = !pOpt->IsViewHScrollBar();
//STRIP001
//STRIP001              pOpt->SetViewHScrollBar( bFlag );
//STRIP001              break;
//STRIP001      case FN_RULER:
//STRIP001              if( STATE_TOGGLE == eState )
//STRIP001                     bFlag = !pOpt->IsViewAnyRuler();
//STRIP001
//STRIP001                 pOpt->SetViewAnyRuler( bFlag );
//STRIP001              break;
//STRIP001
//STRIP001      case FN_VIEW_TABLEGRID:
//STRIP001              if( STATE_TOGGLE == eState )
//STRIP001                     bFlag = !SwViewOption::IsTableBoundaries();
//STRIP001                 SwViewOption::SetAppearanceFlag(VIEWOPT_TABLE_BOUNDARIES, bFlag, TRUE );
//STRIP001              break;
//STRIP001
//STRIP001      case FN_VIEW_FIELDNAME:
//STRIP001              if( STATE_TOGGLE == eState )
//STRIP001                  bFlag = !pOpt->IsFldName() ;
//STRIP001
//STRIP001              pOpt->SetFldName( bFlag );
//STRIP001              break;
//STRIP001      case FN_VIEW_MARKS:
//STRIP001              if( STATE_TOGGLE == eState )
//STRIP001                  bFlag = !lcl_IsViewMarks(*pOpt) ;
//STRIP001
//STRIP001              lcl_SetViewMarks( *pOpt, bFlag );
//STRIP001              break;
//STRIP001      case FN_VIEW_META_CHARS:
//STRIP001              if( STATE_TOGGLE == eState )
//STRIP001                  bFlag = !pOpt->IsViewMetaChars();
//STRIP001
//STRIP001              lcl_SetViewMetaChars( *pOpt, bFlag );
//STRIP001      break;
//STRIP001      case SID_AUTOSPELL_CHECK:
//STRIP001          if( STATE_TOGGLE == eState )
//STRIP001              bFlag = bSet = !pOpt->IsOnlineSpell();
//STRIP001
//STRIP001          pOpt->SetOnlineSpell(bSet);
//STRIP001             {
//STRIP001                 uno::Any aVal( &bSet, ::getCppuBooleanType() );
//STRIP001                 String aPropName( C2S(UPN_IS_SPELL_AUTO) );
//STRIP001
//STRIP001              // #107253# Replaced SvtLinguConfig with SwLinguConfig wrapper with UsageCount
//STRIP001                 SwLinguConfig().SetProperty( aPropName, aVal );
//STRIP001
//STRIP001                 if (xLngProp.is())
//STRIP001                     xLngProp->setPropertyValue( aPropName, aVal );
//STRIP001             }
//STRIP001
//STRIP001          if (!(STATE_TOGGLE == eState && bSet && ( pOpt->IsHideSpell() )))
//STRIP001              break;
//STRIP001      case SID_AUTOSPELL_MARKOFF:
//STRIP001          if( STATE_TOGGLE == eState )
//STRIP001              bFlag = bSet = !pOpt->IsHideSpell();
//STRIP001
//STRIP001          pOpt->SetHideSpell(bSet);
//STRIP001             {
//STRIP001                 uno::Any aVal( &bSet, ::getCppuBooleanType() );
//STRIP001                 String aPropName( C2S(UPN_IS_SPELL_HIDE) );
//STRIP001
//STRIP001              // #107253# Replaced SvtLinguConfig with SwLinguConfig wrapper with UsageCount
//STRIP001                 SwLinguConfig().SetProperty( aPropName, aVal );
//STRIP001
//STRIP001                 if (xLngProp.is())
//STRIP001                     xLngProp->setPropertyValue( aPropName, aVal );
//STRIP001             }
//STRIP001      break;
//STRIP001
//STRIP001      case FN_SHADOWCURSOR:
//STRIP001          if( STATE_TOGGLE == eState )
//STRIP001              bFlag = bSet = !pOpt->IsShadowCursor();
//STRIP001
//STRIP001          pOpt->SetShadowCursor(bSet);
//STRIP001      break;
//STRIP001
//STRIP001      default:
//STRIP001          ASSERT(sal_False, Falsche Request-Methode);
//STRIP001          return;
//STRIP001  }
//STRIP001
//STRIP001  // UserPrefs setzen Request als bearbeitet kennzeichnen
//STRIP001  SwView* pApplyView = GetView();
//STRIP001  sal_Bool bWebView =  0 != PTR_CAST(SwWebView, pApplyView);
//STRIP001  // die ViewSettings duerfen nur der View zugewiesen werden,
//STRIP001  // wenn es auch die richtigen sind
//STRIP001  if(pApplyView && DEPEND_NONE != eWebDepend)
//STRIP001  {
//STRIP001      if(bWebView && DEPEND_NOWEB == eWebDepend ||
//STRIP001          !bWebView && DEPEND_WEB == eWebDepend )
//STRIP001              pApplyView = 0;
//STRIP001  }
//STRIP001  if( pApplyView )
//STRIP001  {
//STRIP001      SwWrtShell &rSh = GetView()->GetWrtShell();
//STRIP001      rSh.StartAction();
//STRIP001      if( !(*rSh.GetViewOptions() == *pOpt ))
//STRIP001      {
//STRIP001          rSh.ApplyViewOptions( *pOpt );
//STRIP001
//STRIP001          //Die UsrPref muessen als Modified gekennzeichnet werden.
//STRIP001          if(bWebView)
//STRIP001          {
//STRIP001              // fuer die Initialisierung
//STRIP001              if(!pWebUsrPref)
//STRIP001                  GetUsrPref(sal_True);
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              if(!pUsrPref)
//STRIP001                  GetUsrPref(sal_False);
//STRIP001          }
//STRIP001          SW_MOD()->CheckSpellChanges( pOpt->IsOnlineSpell(), sal_False, sal_False );
//STRIP001
//STRIP001      }
//STRIP001      //OS:   Modified wieder zuruecksetzen, weil Ansicht/Felder
//STRIP001      //      das Doc modified setzt.
//STRIP001      if( !bModified )
//STRIP001          rSh.ResetModified();
//STRIP001  }
//STRIP001  sal_uInt16 nDest = VIEWOPT_DEST_VIEW;
//STRIP001  if(DEPEND_WEB == eWebDepend )
//STRIP001      nDest = VIEWOPT_DEST_WEB;
//STRIP001  else if(DEPEND_NOWEB == eWebDepend)
//STRIP001      nDest = VIEWOPT_DEST_TEXT;
//STRIP001  ApplyUsrPref( *pOpt, pApplyView, nDest );
//STRIP001  if ( pApplyView )
//STRIP001     {
//STRIP001         SwWrtShell &rSh = pApplyView->GetWrtShell();
//STRIP001         const BOOL bLockedView = rSh.IsViewLocked();
//STRIP001         rSh.LockView( TRUE );    //lock visible section
//STRIP001      pApplyView->GetWrtShell().EndAction();
//STRIP001         rSh.LockView( bLockedView );
//STRIP001     }
//STRIP001
//STRIP001  delete pOpt;
//STRIP001  Invalidate(rReq.GetSlot());
//STRIP001  if(!pArgs)
//STRIP001         rReq.AppendItem(SfxBoolItem(nSlot, (BOOL)bFlag));
//STRIP001     rReq.Done();
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung:   Felddialog starten
 --------------------------------------------------------------------*/


/*N*/void SwModule::ExecOther(SfxRequest& rReq)
/*N*/{
DBG_ASSERT(0, "STRIP"); //STRIP001  const SfxItemSet *pArgs = rReq.GetArgs();
//STRIP001  const SfxPoolItem* pItem = 0;
//STRIP001
//STRIP001  sal_uInt16 nWhich = rReq.GetSlot();
//STRIP001  switch (nWhich)
//STRIP001  {
//STRIP001      case FN_ENVELOP:
//STRIP001             InsertEnv( rReq );
//STRIP001          break;
//STRIP001
//STRIP001      case FN_BUSINESS_CARD:
//STRIP001      case FN_LABEL:
//STRIP001          InsertLab(rReq, nWhich == FN_LABEL);
//STRIP001          break;
//STRIP001
//STRIP001      case SID_SW_DOCMAN_PATH:
//STRIP001          {
//STRIP001              ASSERT(pArgs && pArgs->Count(), "fehlende Parameter GetDocManPath");
//STRIP001              if(!pArgs)
//STRIP001                  return;
//STRIP001
//STRIP001              String aParam(((const SfxStringItem &)pArgs->Get(rReq.GetSlot())).GetValue());
//STRIP001              String aPath;
//STRIP001
//STRIP001              if(aParam == C2S("~~~GetMacroPath"))
//STRIP001              {
//STRIP001                  SvtPathOptions aPathOpt;
//STRIP001                  aPath = URIHelper::SmartRelToAbs( aPathOpt.GetConfigPath() );
//STRIP001                  if(aPath.Len())
//STRIP001                      aPath += INET_PATH_TOKEN;
//STRIP001              }
//STRIP001              else if(aParam == C2S("~~~GetDefDocExt"))
//STRIP001                  aPath =
//STRIP001 #if defined(PM2) || defined(MAC_WITHOUT_EXT)
//STRIP001                  aEmptyStr;
//STRIP001 #else
//STRIP001                  C2S(".sdw");
//STRIP001 #endif
//STRIP001              else if(aParam == C2S("~~~SetNoFrameBeep"))
//STRIP001              {
//STRIP001                  SwView* pActView = ::GetActiveView();
//STRIP001                  if( pActView && pActView->GetDocShell() )
//STRIP001                      pActView->GetDocShell()->GetDoc()->SetFrmBeepEnabled( sal_False );
//STRIP001              }
//STRIP001              else if(aParam == C2S("~~~SetFrameBeep"))
//STRIP001              {
//STRIP001                  SwView* pActView = ::GetActiveView();
//STRIP001                  if( pActView && pActView->GetDocShell() )
//STRIP001                      pActView->GetDocShell()->GetDoc()->SetFrmBeepEnabled( sal_True );
//STRIP001              }
//STRIP001              rReq.SetReturnValue(SfxStringItem( SID_SW_DOCMAN_PATH, aPath ));
//STRIP001          }
//STRIP001          break;
//STRIP001
//STRIP001      case SID_ATTR_ADDRESS:
//STRIP001      {
//STRIP001          if(pArgs && SFX_ITEM_SET == pArgs->GetItemState(nWhich, sal_False, &pItem))
//STRIP001          {
//STRIP001              ((SvxAddressItem*)pItem)->Store();
//STRIP001          }
//STRIP001      }
//STRIP001      break;
//STRIP001      case SID_ATTR_UNDO_COUNT:
//STRIP001      if(pArgs && SFX_ITEM_SET == pArgs->GetItemState(nWhich, sal_False, &pItem))
//STRIP001      {
//STRIP001          const int nNew = ((SfxUInt16Item*)pItem)->GetValue();
//STRIP001          const int nOld = SwEditShell::GetUndoActionCount();
//STRIP001          if(!nNew || !nOld)
//STRIP001          {
//STRIP001              sal_Bool bUndo = nNew != 0;
//STRIP001              //ueber DocShells iterieren und Undo umschalten
//STRIP001
//STRIP001              TypeId aType(TYPE(SwDocShell));
//STRIP001              SwDocShell* pDocShell = (SwDocShell*)SfxObjectShell::GetFirst(&aType);
//STRIP001              while( pDocShell )
//STRIP001              {
//STRIP001                  pDocShell->GetDoc()->DoUndo( bUndo );
//STRIP001                  pDocShell = (SwDocShell*)SfxObjectShell::GetNext(*pDocShell, &aType);
//STRIP001              }
//STRIP001          }
//STRIP001          SwEditShell::SetUndoActionCount( nNew );
//STRIP001          // intern kommt der Request aus dem Dialog, dort werden die Options gesetzt
//STRIP001          if( rReq.IsAPI() )
//STRIP001          {
//STRIP001              SvtUndoOptions aOpt;
//STRIP001              aOpt.SetUndoCount(  nNew );
//STRIP001          }
//STRIP001          break;
//STRIP001      }
//STRIP001      break;
//STRIP001      case SID_ATTR_METRIC:
//STRIP001      if(pArgs && SFX_ITEM_SET == pArgs->GetItemState(nWhich, sal_False, &pItem))
//STRIP001      {
//STRIP001          FieldUnit eUnit = (FieldUnit)((const SfxUInt16Item*)pItem)->GetValue();
//STRIP001          switch( eUnit )
//STRIP001          {
//STRIP001              case FUNIT_MM:
//STRIP001              case FUNIT_CM:
//STRIP001              case FUNIT_INCH:
//STRIP001              case FUNIT_PICA:
//STRIP001              case FUNIT_POINT:
//STRIP001              {
//STRIP001                  SwView* pActView = ::GetActiveView();
//STRIP001                  sal_Bool bWebView = 0 != PTR_CAST(SwWebView, pActView);
//STRIP001                  ::SetDfltMetric(eUnit, bWebView);
//STRIP001              }
//STRIP001              break;
//STRIP001          }
//STRIP001      }
//STRIP001      break;
//STRIP001
//STRIP001      case FN_SET_MODOPT_TBLNUMFMT:
//STRIP001          {
//STRIP001              sal_Bool bWebView = 0 != PTR_CAST(SwWebView, ::GetActiveView() ),
//STRIP001                   bSet;
//STRIP001
//STRIP001              if( pArgs && SFX_ITEM_SET == pArgs->GetItemState(
//STRIP001                      nWhich, sal_False, &pItem ))
//STRIP001                  bSet = ((SfxBoolItem*)pItem)->GetValue();
//STRIP001              else
//STRIP001                  bSet = !pModuleConfig->IsInsTblFormatNum( bWebView );
//STRIP001
//STRIP001              pModuleConfig->SetInsTblFormatNum( bWebView, bSet );
//STRIP001          }
//STRIP001          break;
//STRIP001  }
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
/*?*/               DBG_ASSERT(0, "STRIP"); //STRIP001  pWrtSh->SetFixFields();
//STRIP001 /*?*/                    pWrtSh->UpdateInputFlds();
//STRIP001 /*?*/
//STRIP001 /*?*/                    // Sind Datenbankfelder enthalten?
//STRIP001 /*?*/                    // Erstmal alle verwendeten Datenbanken holen
//STRIP001 /*?*/                    SwDoc *pDoc = pDocSh->GetDoc();
//STRIP001 /*?*/                    SvStringsDtor aDBNameList;
//STRIP001 /*?*/                    pDoc->GetAllUsedDB( aDBNameList );
//STRIP001 /*?*/                    sal_uInt16 nCount = aDBNameList.Count();
//STRIP001 /*?*/                    if (nCount)
//STRIP001 /*?*/                    {   // Datenbankbeamer oeffnen
//STRIP001 /*?*/                         ShowDBObj(pWrtSh->GetView(), pDoc->GetDBData());
//STRIP001 /*?*/                    }
/*M*/               }
/*M*/               break;
/*M*/           }
/*M*/       }
/*M*/   }
/*M*/   else if(rHint.ISA(SfxItemSetHint))
/*M*/   {
/*M*/       if( SFX_ITEM_SET == ((SfxItemSetHint&)rHint).GetItemSet().GetItemState(SID_ATTR_PATHNAME))
/*M*/       {
/*?*/           DBG_ASSERT(0, "STRIP"); //STRIP001 ::GetGlossaries()->UpdateGlosPath( sal_False );
//STRIP001 /*?*/            SwGlossaryList* pList = ::GetGlossaryList();
//STRIP001 /*?*/            if(pList->IsActive())
//STRIP001 /*?*/                pList->Update();
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
/*M*/         {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/             sal_Bool bAccessibility = sal_False;
//STRIP001 /*?*/             if(SFX_HINT_COLORS_CHANGED == nHintId)
//STRIP001 /*?*/                 SwViewOption::ApplyColorConfigValues(*pColorConfig);
//STRIP001 /*?*/             else
//STRIP001 /*?*/                 bAccessibility = sal_True;
//STRIP001 /*?*/
//STRIP001 /*?*/             //invalidate all edit windows
//STRIP001 /*?*/             const TypeId aSwViewTypeId = TYPE(SwView);
//STRIP001 /*?*/             const TypeId aSwPreViewTypeId = TYPE(SwPagePreView);
//STRIP001 /*?*/             const TypeId aSwSrcViewTypeId = TYPE(SwSrcView);
//STRIP001 /*?*/             SfxViewShell* pViewShell = SfxViewShell::GetFirst();
//STRIP001 /*?*/             while(pViewShell)
//STRIP001 /*?*/             {
//STRIP001 /*?*/                 if(pViewShell->GetWindow())
//STRIP001 /*?*/                 {
//STRIP001 /*?*/                     if((pViewShell->IsA(aSwViewTypeId) ||
//STRIP001 /*?*/                         pViewShell->IsA(aSwPreViewTypeId) ||
//STRIP001 /*?*/                         pViewShell->IsA(aSwSrcViewTypeId)))
//STRIP001 /*?*/                     {
//STRIP001 /*?*/                         if(bAccessibility)
//STRIP001 /*?*/                         {
//STRIP001 /*?*/                             if(pViewShell->IsA(aSwViewTypeId))
//STRIP001 /*?*/                                 ((SwView*)pViewShell)->ApplyAccessiblityOptions(*pAccessibilityOptions);
//STRIP001 /*?*/                             else if(pViewShell->IsA(aSwPreViewTypeId))
//STRIP001 /*?*/                                 ((SwPagePreView*)pViewShell)->ApplyAccessiblityOptions(*pAccessibilityOptions);
//STRIP001 /*?*/                         }
//STRIP001 /*?*/                         pViewShell->GetWindow()->Invalidate();
//STRIP001 /*?*/                     }
//STRIP001 /*?*/                 }
//STRIP001 /*?*/                 pViewShell = SfxViewShell::GetNext( *pViewShell );
//STRIP001 /*?*/             }
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
//STRIP001 /*?*/             DELETEZ(pNavigationConfig)  ;
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


