/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_dview.cxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: obo $ $Date: 2008-01-07 08:21:51 $
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

#include "hintids.hxx"




#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#include "frmfmt.hxx"
#include "dcontact.hxx"
#include "viewsh.hxx"
#include "viewimp.hxx"
#include "dview.hxx"

#ifndef _FMTANCHR_HXX //autogen
#include <fmtanchr.hxx>
#endif

// #i7672#

// OD 18.06.2003 #108784#
#include <vector>
namespace binfilter {

class SwSdrHdl : public SdrHdl
{
public:
    SwSdrHdl(const Point& rPnt, bool bTopRight ) :
        SdrHdl( rPnt, bTopRight ? HDL_ANCHOR_TR : HDL_ANCHOR ) {}
};



/*************************************************************************
|*
|*  SwDrawView::Ctor
|*
|*  Ersterstellung      OK 18.11.94
|*  Letzte Aenderung    MA 22. Jul. 96
|*
*************************************************************************/



/*N*/ SwDrawView::SwDrawView( SwViewImp &rI, SdrModel *pMd, OutputDevice *pOutDev) :
/*N*/   FmFormView( (FmFormModel*)pMd, pOutDev ),
/*N*/   rImp( rI )
/*N*/ {
/*N*/   SetPageVisible( FALSE );
/*N*/   SetBordVisible( FALSE );
/*N*/   SetGridVisible( FALSE );
/*N*/   SetHlplVisible( FALSE );
/*N*/   SetGlueVisible( FALSE );
/*N*/   SetFrameDragSingles( TRUE );
/*N*/   SetVirtualObjectBundling( TRUE );
/*N*/   SetSwapAsynchron( TRUE );
/*N*/
/*N*/   EnableExtendedKeyInputDispatcher( FALSE );
/*N*/   EnableExtendedMouseEventDispatcher( FALSE );
/*N*/   EnableExtendedCommandEventDispatcher( FALSE );
/*N*/
/*N*/   SetHitTolerancePixel( GetMarkHdlSizePixel()/2 );
/*N*/
/*N*/   SetPrintPreview( rI.GetShell()->IsPreView() );
/*N*/ }

/*************************************************************************
|*
|*  SwDrawView::AddCustomHdl()
|*
|*  Gets called every time the handles need to be build
|*
|*  Ersterstellung      AW 06. Sep. 99
|*  Letzte Aenderung    AW 06. Sep. 99
|*
*************************************************************************/

/*M*/ void SwDrawView::AddCustomHdl()
/*M*/ {
/*M*/   const SdrMarkList &rMrkList = GetMarkList();
/*M*/
/*M*/   if(rMrkList.GetMarkCount() != 1 || !GetUserCall(rMrkList.GetMark( 0 )->GetObj()))
/*M*/       return;
/*M*/
/*?*/   SdrObject *pObj = rMrkList.GetMark(0)->GetObj();
/*?*/   const SwFmtAnchor &rAnchor = ::binfilter::FindFrmFmt(pObj)->GetAnchor();
/*?*/
/*?*/   if(FLY_IN_CNTNT == rAnchor.GetAnchorId())
/*?*/       return;
/*?*/ DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*M*/ }

/*************************************************************************
|*
|*  SwDrawView::GetMaxToTopObj(), _GetMaxToTopObj()
|*
|*  Ersterstellung      MA 13. Jan. 95
|*  Letzte Aenderung    MA 18. Mar. 97
|*
*************************************************************************/



/*************************************************************************
|*
|*  SwDrawView::GetMaxToBtmObj()
|*
|*  Ersterstellung      MA 13. Jan. 95
|*  Letzte Aenderung    MA 05. Sep. 96
|*
*************************************************************************/



/*************************************************************************
|*
|*  SwDrawView::ObjOrderChanged()
|*
|*  Ersterstellung      MA 31. Jul. 95
|*  Letzte Aenderung    MA 18. Mar. 97
|*
*************************************************************************/






/*************************************************************************
|*
|*  SwDrawView::TakeDragLimit()
|*
|*  Ersterstellung      AMA 26. Apr. 96
|*  Letzte Aenderung    MA 03. May. 96
|*
*************************************************************************/



/*************************************************************************
|*
|*  SwDrawView::CalcAnchor()
|*
|*  Ersterstellung      MA 13. Jan. 95
|*  Letzte Aenderung    MA 08. Nov. 96
|*
*************************************************************************/





/*************************************************************************
|*
|*  SwDrawView::ShowDragXor(), HideDragXor()
|*
|*  Ersterstellung      MA 17. Jan. 95
|*  Letzte Aenderung    MA 27. Jan. 95
|*
*************************************************************************/





/*************************************************************************
|*
|*  SwDrawView::MarkListHasChanged()
|*
|*  Ersterstellung      OM 02. Feb. 95
|*  Letzte Aenderung    OM 07. Jul. 95
|*
*************************************************************************/


/*N*/ void SwDrawView::MarkListHasChanged()
/*N*/ {
/*N*/   Imp().GetShell()->DrawSelChanged(this);
/*N*/   FmFormView::MarkListHasChanged();
/*N*/ }

// #i7672#
/*N*/ void SwDrawView::ModelHasChanged()
/*N*/ {
    // The ModelHasChanged() call in DrawingLayer also updates
    // a eventually active text edit view (OutlinerView). This also leads
    // to newly setting the background color for that edit view. Thus,
    // this method rescues the current background color if a OutlinerView
    // exists and re-establishes it then. To be more safe, the OutlinerView
    // will be fetched again (maybe textedit has ended).
/*N*/   OutlinerView* pView = GetTextEditOutlinerView();
/*N*/   Color aBackColor;
/*N*/   sal_Bool bColorWasSaved(sal_False);
/*N*/
/*N*/   if(pView)
/*N*/   {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/   }
/*N*/
/*N*/   // call parent
/*N*/   FmFormView::ModelHasChanged();
/*N*/
/*N*/   if(bColorWasSaved)
/*N*/   {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/   }
/*N*/ }


/** replace marked <SwDrawVirtObj>-objects by its reference object for delete
    marked objects.

    OD 18.06.2003 #108784#

    @author OD
*/


/********
JP 02.10.98: sollte als Fix fuer 57153 gelten, hatte aber Nebenwirkungen,
            wie Bug 57475
const SdrMarkList& SwDrawView::GetMarkList() const
{
    FlushComeBackTimer();
    return FmFormView::GetMarkList();
}
*************/









}
