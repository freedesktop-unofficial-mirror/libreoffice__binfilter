/*************************************************************************
 *
 *  $RCSfile: sw_dpage.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:49:24 $
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

#ifndef _BASMGR_HXX
#include <basic/basmgr.hxx>
#endif
#ifndef _GOODIES_IMAPOBJ_HXX
#include <svtools/imapobj.hxx>
#endif
#ifndef SVTOOLS_URIHELPER_HXX
#include <svtools/urihelper.hxx>
#endif
#ifndef _URLOBJ_HXX //autogen
#include <tools/urlobj.hxx>
#endif
#ifndef _SV_HELP_HXX //autogen
#include <vcl/help.hxx>
#endif
#ifndef _SVDVIEW_HXX //autogen
#include <bf_svx/svdview.hxx>
#endif

#ifndef _FMTURL_HXX //autogen
#include <fmturl.hxx>
#endif
#ifndef _FRMFMT_HXX //autogen
#include <frmfmt.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _DOCSH_HXX
#include <docsh.hxx>
#endif
#ifndef _VIEWIMP_HXX
#include <viewimp.hxx>
#endif
#ifndef _PAGEFRM_HXX
#include <pagefrm.hxx>
#endif
#ifndef _CNTFRM_HXX
#include <cntfrm.hxx>
#endif
#ifndef _ROOTFRM_HXX
#include <rootfrm.hxx>
#endif
#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif
#ifndef _SWTYPES_HXX
#include <swtypes.hxx>
#endif
#ifndef _FRMATR_HXX
#include <frmatr.hxx>
#endif
#ifndef _VIEWSH_HXX
#include <viewsh.hxx>
#endif
#ifndef _DRAWDOC_HXX
#include <drawdoc.hxx>
#endif
#ifndef _DPAGE_HXX
#include <dpage.hxx>
#endif
#ifndef _DCONTACT_HXX
#include <dcontact.hxx>
#endif
#ifndef _DFLYOBJ_HXX
#include <dflyobj.hxx>
#endif
#ifndef _DOCSH_HXX
#include <docsh.hxx>
#endif
#ifndef _USRFLD_HXX
#include <usrfld.hxx>
#endif
#ifndef _FLYFRM_HXX
#include <flyfrm.hxx>
#endif
#ifndef _NDNOTXT_HXX
#include <ndnotxt.hxx>
#endif
#ifndef _GRFATR_HXX
#include <grfatr.hxx>
#endif
#ifndef _COM_SUN_STAR_DRAWING_XDRAWPAGESUPPLIER_HPP_
#include <com/sun/star/drawing/XDrawPageSupplier.hpp>
#endif
namespace binfilter {

using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::drawing;
using namespace ::com::sun::star::frame;

/*?*/ SwDPage::SwDPage(SwDrawDocument& rNewModel, BOOL bMasterPage) :
/*?*/   FmFormPage(rNewModel, 0, bMasterPage),
/*?*/   pGridLst( 0 ),
/*?*/   rDoc(rNewModel.GetDoc())
/*?*/ {
/*?*/ }


/*N*/ SwDPage::~SwDPage()
/*N*/ {
/*N*/   delete pGridLst;
/*N*/ }


// #i3694#
// This GetOffset() method is not needed anymore, it even leads to errors.
//Point  SwDPage::GetOffset() const
//{
//  return Point( DOCUMENTBORDER, DOCUMENTBORDER );
//}

/*************************************************************************
|*
|*  SwDPage::ReplaceObject()
|*
|*  Ersterstellung      MA 07. Aug. 95
|*  Letzte Aenderung    MA 07. Aug. 95
|*
*************************************************************************/

/*N*/ SdrObject*  SwDPage::ReplaceObject( SdrObject* pNewObj, ULONG nObjNum )
/*N*/ {
/*N*/   SdrObject *pOld = GetObj( nObjNum );
/*N*/   ASSERT( pOld, "Oups, Object not replaced" );
/*N*/   SdrObjUserCall* pContact;
/*N*/   if ( 0 != ( pContact = GetUserCall(pOld) ) &&
/*N*/        RES_DRAWFRMFMT == ((SwContact*)pContact)->GetFmt()->Which())
            {DBG_ASSERT(0, "STRIP");} //STRIP001 /*?*/      ((SwDrawContact*)pContact)->ChangeMasterObject( pNewObj );
/*N*/   return FmFormPage::ReplaceObject( pNewObj, nObjNum );
/*N*/ }

/*************************************************************************
|*
|*  SwDPage::GetGridFrameList()
|*
|*  Ersterstellung      MA 04. Sep. 95
|*  Letzte Aenderung    MA 15. Feb. 96
|*
*************************************************************************/

//STRIP001 void InsertGridFrame( SdrPageGridFrameList *pLst, const SwFrm *pPg )
//STRIP001 {
//STRIP001  SwRect aPrt( pPg->Prt() );
//STRIP001  aPrt += pPg->Frm().Pos();
//STRIP001  const Rectangle aUser( aPrt.SVRect() );
//STRIP001  const Rectangle aPaper( pPg->Frm().SVRect() );
//STRIP001  pLst->Insert( SdrPageGridFrame( aPaper, aUser ) );
//STRIP001 }


//STRIP001 const SdrPageGridFrameList*  SwDPage::GetGridFrameList(
//STRIP001                      const SdrPageView* pPV, const Rectangle *pRect ) const
//STRIP001 {
//STRIP001  ViewShell *pSh = ((SwDrawDocument*)GetModel())->GetDoc().GetRootFrm()->GetCurrShell();
//STRIP001  if ( pSh )
//STRIP001  {
//STRIP001      while ( pSh->Imp()->GetPageView() != pPV )
//STRIP001          pSh = (ViewShell*)pSh->GetNext();
//STRIP001      if ( pSh )
//STRIP001      {
//STRIP001          if ( pGridLst )
//STRIP001              ((SwDPage*)this)->pGridLst->Clear();
//STRIP001          else
//STRIP001              ((SwDPage*)this)->pGridLst = new SdrPageGridFrameList;
//STRIP001
//STRIP001          if ( pRect )
//STRIP001          {
//STRIP001              //Das Drawing verlang alle Seiten, die mit dem Rect ueberlappen.
//STRIP001              const SwRect aRect( *pRect );
//STRIP001              const SwFrm *pPg = pSh->GetLayout()->Lower();
//STRIP001              do
//STRIP001              {   if ( pPg->Frm().IsOver( aRect ) )
//STRIP001                      ::InsertGridFrame( ((SwDPage*)this)->pGridLst, pPg );
//STRIP001                  pPg = pPg->GetNext();
//STRIP001              } while ( pPg );
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              //Das Drawing verlangt alle sichbaren Seiten
//STRIP001              const SwFrm *pPg = pSh->Imp()->GetFirstVisPage();
//STRIP001              if ( pPg )
//STRIP001                  do
//STRIP001                  {   ::InsertGridFrame( ((SwDPage*)this)->pGridLst, pPg );
//STRIP001                      pPg = pPg->GetNext();
//STRIP001                  } while ( pPg && pPg->Frm().IsOver( pSh->VisArea() ) );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return pGridLst;
//STRIP001 }

/*************************************************************************
|*
|*  String SwDPage::GetLinkData( const String& )
|*  void SwDPage::SetLinkData( const String&, const String& )
|*  void SwDPage::UpdateLinkData( const String&, const String& )
|*
|*  Ersterstellung      JP 04.09.95
|*  Letzte Aenderung    JP 04.09.95
|*
*************************************************************************/

//STRIP001 String SwDPage::GetLinkData( const String& rLinkName )
//STRIP001 {
//STRIP001  SwDoc& rDoc = ((SwDrawDocument*)GetModel())->GetDoc();
//STRIP001  SwFieldType* pFTyp = rDoc.GetFldType( RES_USERFLD, rLinkName );
//STRIP001  if( pFTyp )
//STRIP001      return ((SwUserFieldType*)pFTyp)->GetContent();
//STRIP001  return aEmptyStr;
//STRIP001 }


//STRIP001 void  SwDPage::SetLinkData( const String& rLinkName,
//STRIP001                                  const String& rLinkData )
//STRIP001 {
//STRIP001  SwDoc& rDoc = ((SwDrawDocument*)GetModel())->GetDoc();
//STRIP001  SwFieldType* pFTyp = rDoc.GetFldType( RES_USERFLD, rLinkName );
//STRIP001  if( pFTyp )
//STRIP001      ((SwUserFieldType*)pFTyp)->CtrlSetContent( rLinkData );
//STRIP001 }


//STRIP001 void  SwDPage::RequestBasic()
//STRIP001 {
//STRIP001  SwDoc& rDoc = ((SwDrawDocument*)GetModel())->GetDoc();
//STRIP001  if( rDoc.GetDocShell() )
//STRIP001  {
//STRIP001      BasicManager *pBasicMgr = rDoc.GetDocShell()->GetBasicManager();
//STRIP001      ASSERT( pBasicMgr, "wo ist mein BasicManager" )
//STRIP001      SetBasic( pBasicMgr->GetLib( 0 ) );
//STRIP001  }
//STRIP001  else
//STRIP001      ASSERT( !this, "wo ist meine DocShell" )
//STRIP001 }


//STRIP001 BOOL SwDPage::RequestHelp( Window* pWindow, SdrView* pView,
//STRIP001                         const HelpEvent& rEvt )
//STRIP001 {
//STRIP001  BOOL bWeiter = TRUE;
//STRIP001
//STRIP001  if( rEvt.GetMode() & ( HELPMODE_QUICK | HELPMODE_BALLOON ))
//STRIP001  {
//STRIP001      Point aPos( rEvt.GetMousePosPixel() );
//STRIP001      aPos = pWindow->ScreenToOutputPixel( aPos );
//STRIP001      aPos = pWindow->PixelToLogic( aPos );
//STRIP001
//STRIP001      SdrPageView* pPV;
//STRIP001      SdrObject* pObj;
//STRIP001      if( pView->PickObj( aPos, 0, pObj, pPV, SDRSEARCH_PICKMACRO ) &&
//STRIP001           pObj->IsWriterFlyFrame() )
//STRIP001      {
//STRIP001          SwFlyFrm *pFly = ((SwVirtFlyDrawObj*)pObj)->GetFlyFrm();
//STRIP001          const SwFmtURL &rURL = pFly->GetFmt()->GetURL();
//STRIP001          String sTxt;
//STRIP001          if( rURL.GetMap() )
//STRIP001          {
//STRIP001              IMapObject *pObj = pFly->GetFmt()->GetIMapObject( aPos, pFly );
//STRIP001              if( pObj )
//STRIP001              {
//STRIP001                  sTxt = pObj->GetDescription();
//STRIP001                  if ( !sTxt.Len() )
//STRIP001                      sTxt = URIHelper::removePassword( pObj->GetURL(),
//STRIP001                                      INetURLObject::WAS_ENCODED,
//STRIP001                                      INetURLObject::DECODE_UNAMBIGUOUS);
//STRIP001              }
//STRIP001          }
//STRIP001          else if ( rURL.GetURL().Len() )
//STRIP001          {
//STRIP001              sTxt = URIHelper::removePassword( rURL.GetURL(),
//STRIP001                                      INetURLObject::WAS_ENCODED,
//STRIP001                                      INetURLObject::DECODE_UNAMBIGUOUS);
//STRIP001
//STRIP001              if( rURL.IsServerMap() )
//STRIP001              {
//STRIP001                  // dann die rel. Pixel Position anhaengen !!
//STRIP001                  Point aPt( aPos );
//STRIP001                  aPt -= pFly->Frm().Pos();
//STRIP001                  // ohne MapMode-Offset !!!!!
//STRIP001                  // ohne MapMode-Offset, ohne Offset, o ... !!!!!
//STRIP001                  aPt = (Point&)(Size&)pWindow->LogicToPixel(
//STRIP001                          (Size&)aPt, MapMode( MAP_TWIP ) );
//STRIP001                  ((( sTxt += '?' ) += String::CreateFromInt32( aPt.X() ))
//STRIP001                           += ',' ) += String::CreateFromInt32( aPt.Y() );
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          if ( sTxt.Len() )
//STRIP001          {
//STRIP001              if( rEvt.GetMode() & HELPMODE_QUICK )
//STRIP001              {
//STRIP001                  // dann zeige die Hilfe mal an:
//STRIP001                  Rectangle aRect( rEvt.GetMousePosPixel(), Size(1,1) );
/*
Bug 29593: QuickHelp immer an der MausPosition anzeigen (besonders unter OS/2)

                    Rectangle aRect( pObj->GetSnapRect() );
                    Point aPt( pWindow->OutputToScreenPixel( pWindow->LogicToPixel( aRect.TopLeft() )));
                    aRect.Left()   = aPt.X();
                    aRect.Top()    = aPt.Y();
                    aPt = pWindow->OutputToScreenPixel( pWindow->LogicToPixel( aRect.BottomRight() ));
                    aRect.Right()  = aPt.X();
                    aRect.Bottom() = aPt.Y();
*/
//STRIP001                  Help::ShowQuickHelp( pWindow, aRect, sTxt );
//STRIP001              }
//STRIP001              else
//STRIP001                  Help::ShowBalloon( pWindow, rEvt.GetMousePosPixel(), sTxt );
//STRIP001              bWeiter = FALSE;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if( bWeiter )
//STRIP001      bWeiter = !FmFormPage::RequestHelp( pWindow, pView, rEvt );
//STRIP001
//STRIP001  return bWeiter;
//STRIP001 }
/* -----------------------------27.11.00 07:35--------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ Reference< XInterface > SwDPage::createUnoPage()
/*N*/ {
/*N*/   Reference<XModel> xModel = rDoc.GetDocShell()->GetBaseModel();
/*N*/   Reference<XDrawPageSupplier> xPageSupp(xModel, UNO_QUERY);
/*N*/   return xPageSupp->getDrawPage();
/*N*/ }



}
