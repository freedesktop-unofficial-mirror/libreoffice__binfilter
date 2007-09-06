/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_dpage.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 12:08:22 $
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

#ifdef _MSC_VER
#pragma hdrstop
#endif


#ifndef _FRMFMT_HXX //autogen
#include <frmfmt.hxx>
#endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _DOC_HXX
#include <doc.hxx>
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
#ifndef _DOCSH_HXX
#include <docsh.hxx>
#endif
#ifndef _FLYFRM_HXX
#include <flyfrm.hxx>
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
            {DBG_BF_ASSERT(0, "STRIP");} //STRIP001 /*?*/       ((SwDrawContact*)pContact)->ChangeMasterObject( pNewObj );
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
/* -----------------------------27.11.00 07:35--------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ Reference< XInterface > SwDPage::createUnoPage()
/*N*/ {
/*N*/   Reference<XModel> xModel = rDoc.GetDocShell()->GetBaseModel();
/*N*/   Reference<XDrawPageSupplier> xPageSupp(xModel, UNO_QUERY);
/*N*/   return xPageSupp->getDrawPage();
/*N*/ }



}
