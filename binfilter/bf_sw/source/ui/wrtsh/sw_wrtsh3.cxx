/*************************************************************************
 *
 *  $RCSfile: sw_wrtsh3.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:58:56 $
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

#ifndef _SVX_SVXIDS_HRC //autogen
#include <bf_svx/svxids.hrc>
#endif
#ifndef _SFXAPP_HXX //autogen
#include <bf_sfx2/app.hxx>
#endif
#ifndef _SFX_CHILDWIN_HXX //autogen
#include <bf_sfx2/childwin.hxx>
#endif
#ifndef _SFX_BINDINGS_HXX //autogen
#include <bf_sfx2/bindings.hxx>
#endif
#ifndef _SVDMARK_HXX //autogen
#include <bf_svx/svdmark.hxx>
#endif
#ifndef _SVDVIEW_HXX //autogen
#include <bf_svx/svdview.hxx>
#endif
#ifndef _SVX_FMGLOB_HXX
#include <bf_svx/fmglob.hxx>
#endif
#ifndef _SVDOUNO_HXX //autogen
#include <bf_svx/svdouno.hxx>
#endif
#ifndef _COM_SUN_STAR_FORM_FORMBUTTONTYPE_HPP_
#include <com/sun/star/form/FormButtonType.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
#include <com/sun/star/beans/XPropertySet.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSETINFO_HPP_
#include <com/sun/star/beans/XPropertySetInfo.hpp>
#endif
#ifndef _SVX_HTMLMODE_HXX
#include <bf_svx/htmlmode.hxx>
#endif
#ifndef _URLOBJ_HXX //autogen
#include <tools/urlobj.hxx>
#endif
#ifndef _SFXVIEWFRM_HXX
#include <bf_sfx2/viewfrm.hxx>
#endif


#include "wrtsh.hxx"
#include "view.hxx"
#include "bookmrk.hxx"
#include "doc.hxx"
#include "wrtsh.hrc"
namespace binfilter {

#define C2U(cChar) ::rtl::OUString::createFromAscii(cChar)

using namespace ::com::sun::star;
using namespace ::rtl;

extern sal_Bool bNoInterrupt;       // in mainwn.cxx

//STRIP001 FASTBOOL SwWrtShell::MoveBookMark(  BookMarkMove eFuncId,
//STRIP001                                     sal_uInt16 nPos,
//STRIP001                                     sal_Bool bStart )
//STRIP001 {
//STRIP001 //JP 08.03.96: die Wizards brauchen die Selektion !!
//STRIP001 //  EndSelect();
//STRIP001     (this->*fnKillSel)( 0, sal_False );
//STRIP001
//STRIP001     FASTBOOL bRet = sal_True;
//STRIP001     switch(eFuncId)
//STRIP001     {
//STRIP001         case BOOKMARK_INDEX:bRet = SwCrsrShell::GotoBookmark( nPos );break;
//STRIP001         case BOOKMARK_NEXT: bRet = SwCrsrShell::GoNextBookmark();break;
//STRIP001         case BOOKMARK_PREV: bRet = SwCrsrShell::GoPrevBookmark();break;
//STRIP001     }
//STRIP001
//STRIP001     if( bRet && IsSelFrmMode() )
//STRIP001     {
//STRIP001         UnSelectFrm();
//STRIP001         LeaveSelFrmMode();
//STRIP001     }
//STRIP001     if( IsSelection() )
//STRIP001     {
//STRIP001         fnKillSel = &SwWrtShell::ResetSelect;
//STRIP001         fnSetCrsr = &SwWrtShell::SetCrsrKillSel;
//STRIP001     }
//STRIP001     return bRet;
//STRIP001 }


/*--------------------------------------------------------------------
    Beschreibung: FontWork-Slots invalidieren
 --------------------------------------------------------------------*/


/*N*/ void SwWrtShell::DrawSelChanged(SdrView* pView)
/*N*/ {
/*N*/     static sal_uInt16 __READONLY_DATA aInval[] =
/*N*/     {
/*N*/         SID_ATTR_FILL_STYLE, SID_ATTR_FILL_COLOR, SID_ATTR_LINE_STYLE,
/*N*/         SID_ATTR_LINE_WIDTH, SID_ATTR_LINE_COLOR, 0
/*N*/     };
/*N*/
/*N*/     GetView().GetViewFrame()->GetBindings().Invalidate(aInval);
/*N*/
/*N*/     sal_Bool bOldVal = bNoInterrupt;
/*N*/     bNoInterrupt = sal_True;    // Trick, um AttrChangedNotify ueber Timer auszufuehren
/*N*/     GetView().AttrChangedNotify(this);
/*N*/     bNoInterrupt = bOldVal;
/*N*/ }

//STRIP001 FASTBOOL SwWrtShell::GotoBookmark( const String& rName )
//STRIP001 {
//STRIP001     sal_uInt16 nPos = FindBookmark( rName );
//STRIP001     if( USHRT_MAX == nPos )
//STRIP001         return sal_False;
//STRIP001
//STRIP001     return MoveBookMark( BOOKMARK_INDEX, nPos );
//STRIP001 }


/*N*/ FASTBOOL SwWrtShell::GotoBookmark( sal_uInt16 nPos )
/*N*/ {
/*?*/    DBG_ASSERT(0, "STRIP"); return FALSE;//STRIP001  return MoveBookMark( BOOKMARK_INDEX, nPos );
/*N*/ }


//STRIP001 FASTBOOL SwWrtShell::GoNextBookmark()
//STRIP001 {
//STRIP001     return MoveBookMark( BOOKMARK_NEXT );
//STRIP001 }


//STRIP001 FASTBOOL SwWrtShell::GoPrevBookmark()
//STRIP001 {
//STRIP001     return MoveBookMark( BOOKMARK_PREV );
//STRIP001 }


//STRIP001 void SwWrtShell::ExecMacro( const SvxMacro& rMacro, String* pRet, SbxArray* pArgs )
//STRIP001 {
//STRIP001     // OD 11.02.2003 #100556# - execute macro, if it is allowed.
//STRIP001     if ( IsMacroExecAllowed() )
//STRIP001     {
//STRIP001         GetDoc()->ExecMacro( rMacro, pRet, pArgs );
//STRIP001     }
//STRIP001 }


//STRIP001 sal_uInt16 SwWrtShell::CallEvent( sal_uInt16 nEvent, const SwCallMouseEvent& rCallEvent,
//STRIP001                                 sal_Bool bChkPtr, SbxArray* pArgs,
//STRIP001                                 const Link* pCallBack )
//STRIP001 {
//STRIP001     return GetDoc()->CallEvent( nEvent, rCallEvent, bChkPtr, pArgs, pCallBack );
//STRIP001 }


    // fall ein util::URL-Button selektiert ist, dessen util::URL returnen, ansonsten
    // einen LeerString
//STRIP001 sal_Bool SwWrtShell::GetURLFromButton( String& rURL, String& rDescr ) const
//STRIP001 {
//STRIP001     sal_Bool bRet = sal_False;
//STRIP001     const SdrView *pDView = GetDrawView();
//STRIP001     if( pDView )
//STRIP001     {
//STRIP001         // Ein Fly ist genau dann erreichbar, wenn er selektiert ist.
//STRIP001         const SdrMarkList &rMarkList = pDView->GetMarkList();
//STRIP001
//STRIP001         if (rMarkList.GetMark(0))
//STRIP001         {
//STRIP001             SdrUnoObj* pUnoCtrl = PTR_CAST(SdrUnoObj, rMarkList.GetMark(0)->GetObj());
//STRIP001             if (pUnoCtrl && FmFormInventor == pUnoCtrl->GetObjInventor())
//STRIP001             {
//STRIP001                 uno::Reference< awt::XControlModel >  xControlModel = pUnoCtrl->GetUnoControlModel();
//STRIP001
//STRIP001                 ASSERT( xControlModel.is(), "UNO-Control ohne Model" );
//STRIP001                 if( !xControlModel.is() )
//STRIP001                     return bRet;
//STRIP001
//STRIP001                 uno::Reference< beans::XPropertySet >  xPropSet(xControlModel, uno::UNO_QUERY);
//STRIP001
//STRIP001                 uno::Any aTmp;
//STRIP001
//STRIP001                 form::FormButtonType eButtonType = form::FormButtonType_URL;
//STRIP001                 uno::Reference< beans::XPropertySetInfo >   xInfo = xPropSet->getPropertySetInfo();
//STRIP001                 if(xInfo->hasPropertyByName( C2U("ButtonType") ))
//STRIP001                 {
//STRIP001                     aTmp = xPropSet->getPropertyValue( C2U("ButtonType") );
//STRIP001                     form::FormButtonType eTmpButtonType;
//STRIP001                     aTmp >>= eTmpButtonType;
//STRIP001                     if( eButtonType == eTmpButtonType)
//STRIP001                     {
//STRIP001                         // Label
//STRIP001                         aTmp = xPropSet->getPropertyValue( C2U("Label") );
//STRIP001                         OUString uTmp;
//STRIP001                         if( (aTmp >>= uTmp) && uTmp.getLength())
//STRIP001                         {
//STRIP001                             rDescr = String(uTmp);
//STRIP001                         }
//STRIP001
//STRIP001                         // util::URL
//STRIP001                         aTmp = xPropSet->getPropertyValue( C2U("TargetURL") );
//STRIP001                         if( (aTmp >>= uTmp) && uTmp.getLength())
//STRIP001                         {
//STRIP001                             rURL = String(uTmp);
//STRIP001                         }
//STRIP001                         bRet = sal_True;
//STRIP001                     }
//STRIP001                 }
//STRIP001             }
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001     return bRet;
//STRIP001 }


    // falls ein util::URL-Button selektiert ist, dessen util::URL returnen, ansonsten
    // einen LeerString
//STRIP001 sal_Bool SwWrtShell::SetURLToButton( const String& rURL, const String& rDescr )
//STRIP001 {
//STRIP001     sal_Bool bRet = sal_False;
//STRIP001     const SdrView *pDView = GetDrawView();
//STRIP001     if( pDView )
//STRIP001     {
//STRIP001         // Ein Fly ist genau dann erreichbar, wenn er selektiert ist.
//STRIP001         const SdrMarkList &rMarkList = pDView->GetMarkList();
//STRIP001         if (rMarkList.GetMark(0))
//STRIP001         {
//STRIP001             SdrUnoObj* pUnoCtrl = PTR_CAST(SdrUnoObj, rMarkList.GetMark(0)->GetObj());
//STRIP001             if (pUnoCtrl && FmFormInventor == pUnoCtrl->GetObjInventor())
//STRIP001             {
//STRIP001                 uno::Reference< awt::XControlModel >  xControlModel = pUnoCtrl->GetUnoControlModel();
//STRIP001
//STRIP001                 ASSERT( xControlModel.is(), "UNO-Control ohne Model" );
//STRIP001                 if( !xControlModel.is() )
//STRIP001                     return bRet;
//STRIP001
//STRIP001                 uno::Reference< beans::XPropertySet >  xPropSet(xControlModel, uno::UNO_QUERY);
//STRIP001
//STRIP001                 uno::Any aTmp;
//STRIP001
//STRIP001                 // Darf man eine util::URL an dem Objekt setzen?
//STRIP001                 uno::Reference< beans::XPropertySetInfo >  xPropInfoSet = xPropSet->getPropertySetInfo();
//STRIP001                 beans::Property aProp = xPropInfoSet->getPropertyByName( C2U("TargetURL") );
//STRIP001                 if (aProp.Name.getLength())
//STRIP001                 {
//STRIP001                     // Ja!
//STRIP001                     aTmp <<= OUString(rDescr);
//STRIP001                     xPropSet->setPropertyValue( C2U("Label"), aTmp );
//STRIP001
//STRIP001                     aTmp <<= OUString(rURL);
//STRIP001                     xPropSet->setPropertyValue( C2U("TargetURL"), aTmp );
//STRIP001
//STRIP001
//STRIP001                     form::FormButtonType eButtonType = form::FormButtonType_URL;
//STRIP001                     aTmp.setValue( &eButtonType, ::getCppuType((form::FormButtonType*)0));
//STRIP001                     xPropSet->setPropertyValue( C2U("ButtonType"), aTmp );
//STRIP001                 }
//STRIP001             }
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001     return bRet;
//STRIP001 }



}
