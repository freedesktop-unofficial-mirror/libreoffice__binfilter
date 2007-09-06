/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sc_docsh4.cxx,v $
 *
 *  $Revision: 1.10 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 11:05:44 $
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
#endif

#ifdef _MSC_VER
#pragma hdrstop
#endif


// INCLUDE ---------------------------------------------------------------
#if STLPORT_VERSION>=321
#include <math.h>       // prevent conflict between exception and std::exception
#endif

#define ITEMID_FIELD EE_FEATURE_FIELD

#include <bf_sfx2/app.hxx>
#include <bf_sfx2/docfile.hxx>
#include <svtools/ehdl.hxx>
#include "bf_basic/sbxcore.hxx"
#include <bf_sfx2/request.hxx>
#include <svtools/sfxecode.hxx>
#include <svtools/whiter.hxx>
#include <vcl/msgbox.hxx>
#include <vcl/waitobj.hxx>

#include "docsh.hxx"
#include "docfunc.hxx"
#include "bf_sc.hrc"
#include "stlpool.hxx"
#include "appoptio.hxx"
#include "globstr.hrc"
#include "dbdocfun.hxx"
#include "printfun.hxx"              // DrawToDev
#include "viewdata.hxx"
#include "dbcolect.hxx"
#include "scmod.hxx"
#include "tablink.hxx"      // ScDocumentLoader statics
#include "docoptio.hxx"

#ifndef _COM_SUN_STAR_DOCUMENT_UPDATEDOCMODE_HPP_
#include <com/sun/star/document/UpdateDocMode.hpp>
#endif
namespace binfilter {

//------------------------------------------------------------------

#define IS_SHARE_HEADER(set) \
    ((SfxBoolItem&) \
        ((SvxSetItem&)(set).Get(ATTR_PAGE_HEADERSET)).GetItemSet(). \
            Get(ATTR_PAGE_SHARED)).GetValue()

#define IS_SHARE_FOOTER(set) \
    ((SfxBoolItem&) \
        ((SvxSetItem&)(set).Get(ATTR_PAGE_FOOTERSET)).GetItemSet(). \
            Get(ATTR_PAGE_SHARED)).GetValue()

#define IS_AVAILABLE(WhichId,ppItem) \
    (pReqArgs->GetItemState((WhichId), TRUE, ppItem ) == SFX_ITEM_SET)

#define SC_PREVIEW_SIZE_X   10000
#define SC_PREVIEW_SIZE_Y   12400


//------------------------------------------------------------------


//------------------------------------------------------------------


//------------------------------------------------------------------

/*N*/ void ScDocShell::DoRecalc( BOOL bApi )
/*N*/ {
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 ScInputHandler* pHdl = SC_MOD()->GetInputHdl(pSh);
/*N*/ }

/*N*/ void ScDocShell::DoHardRecalc( BOOL bApi )
/*N*/ {
/*N*/   aDocument.CalcAll();
/*N*/   GetDocFunc().DetectiveRefresh();    // erzeugt eigenes Undo
/*N*/   PostPaintGridAll();
/*N*/ }

//------------------------------------------------------------------


//------------------------------------------------------------------

/*N*/ void ScDocShell::NotifyStyle( const SfxStyleSheetHint& rHint )
/*N*/ {
/*N*/   USHORT nId = rHint.GetHint();
/*N*/   const SfxStyleSheetBase* pStyle = rHint.GetStyleSheet();
/*N*/   if (!pStyle)
/*N*/       return;
/*N*/
/*N*/   if ( pStyle->GetFamily() == SFX_STYLE_FAMILY_PAGE )
/*N*/   {
/*N*/       if ( nId == SFX_STYLESHEET_MODIFIED )
/*N*/       {
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 ScDocShellModificator aModificator( *this );
/*N*/       }
/*N*/   }
/*N*/
/*N*/   //  alles andere geht ueber Slots...
/*N*/ }

//  wie in printfun.cxx
#define ZOOM_MIN    10



/*N*/ void ScDocShell::PageStyleModified( const String& rStyleName, BOOL bApi )
/*N*/ {
/*N*/   ScDocShellModificator aModificator( *this );
/*N*/
/*N*/   BOOL bWarn = FALSE;
/*N*/
/*N*/   USHORT nTabCount = aDocument.GetTableCount();
/*N*/   USHORT nUseTab = MAXTAB+1;
/*N*/   for (USHORT nTab=0; nTab<nTabCount && nUseTab>MAXTAB; nTab++)
/*N*/       if ( aDocument.GetPageStyle(nTab) == rStyleName &&
/*N*/               ( !bApi || aDocument.GetPageSize(nTab).Width() ) )
/*N*/           nUseTab = nTab;
/*N*/                               // bei bApi nur, wenn Umbrueche schon angezeigt
/*N*/
/*N*/   if (nUseTab<=MAXTAB)        // nicht verwendet -> nichts zu tun
/*N*/   {
/*?*/       ScPrintFunc aPrintFunc( this, GetPrinter(), nUseTab );  //! ohne CountPages auskommen
/*?*/       if (!aPrintFunc.UpdatePages())                          //  setzt Umbrueche auf allen Tabs
/*?*/           bWarn = TRUE;
/*?*/
/*?*/       if (bWarn && !bApi)
/*?*/       {
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 ScWaitCursorOff aWaitOff( GetDialogParent() );
/*?*/       }
/*N*/   }
/*N*/
/*N*/   aModificator.SetDocumentModified();
/*N*/ }



/*N*/ Rectangle __EXPORT ScDocShell::GetVisArea( USHORT nAspect ) const
/*N*/ {
/*N*/   SfxObjectCreateMode eShellMode = GetCreateMode();
/*N*/   if ( eShellMode == SFX_CREATE_MODE_ORGANIZER )
/*N*/   {
/*?*/       //  ohne Inhalte wissen wir auch nicht, wie gross die Inhalte sind
/*?*/       //  leeres Rechteck zurueckgeben, das wird dann nach dem Laden berechnet
/*?*/       return Rectangle();
/*N*/   }
/*N*/
/*N*/   if( nAspect == ASPECT_THUMBNAIL )
/*N*/   {
/*?*/ //        Rectangle aArea( 0,0, 3175,3175 );                          //  120x120 Pixel in 1:1
/*?*/       Rectangle aArea( 0,0, SC_PREVIEW_SIZE_X,SC_PREVIEW_SIZE_Y );
/*?*/       aDocument.SnapVisArea( aArea );
/*?*/       return aArea;
/*N*/   }
/*N*/   else if( nAspect == ASPECT_CONTENT && eShellMode != SFX_CREATE_MODE_EMBEDDED )
/*N*/   {
/*N*/       //  Visarea holen wie nach Load
/*N*/
/*N*/       USHORT nVisTab = aDocument.GetVisibleTab();
/*N*/       if (!aDocument.HasTable(nVisTab))
/*N*/       {
/*?*/           nVisTab = 0;
/*?*/           ((ScDocShell*)this)->aDocument.SetVisibleTab(nVisTab);
/*N*/       }
/*N*/       USHORT nStartCol,nStartRow;
/*N*/       aDocument.GetDataStart( nVisTab, nStartCol, nStartRow );
/*N*/       USHORT nEndCol,nEndRow;
/*N*/       aDocument.GetPrintArea( nVisTab, nEndCol, nEndRow );
/*N*/       if (nStartCol>nEndCol)
/*?*/           nStartCol = nEndCol;
/*N*/       if (nStartRow>nEndRow)
/*?*/           nStartRow = nEndRow;
/*N*/       Rectangle aNewArea = ((ScDocument&)aDocument)
/*N*/                               .GetMMRect( nStartCol,nStartRow, nEndCol,nEndRow, nVisTab );
/*N*/       ((ScDocShell*)this)->SvEmbeddedObject::SetVisArea( aNewArea );
/*N*/       return aNewArea;
/*N*/   }
/*N*/   else
/*N*/       return SfxInPlaceObject::GetVisArea( nAspect );
/*N*/ }





//------------------------------------------------------------------

/*N*/ ScViewData* ScDocShell::GetViewData()
/*N*/ {
/*N*/   return NULL;
/*N*/ }

//------------------------------------------------------------------

/*N*/ USHORT ScDocShell::GetCurTab()
/*N*/ {
/*N*/   //! this must be made non-static and use a ViewShell from this document!
/*N*/
/*N*/   ScViewData* pViewData = GetViewData();
/*N*/
/*N*/   return pViewData ? pViewData->GetTabNo() : 0;
/*N*/ }


}
