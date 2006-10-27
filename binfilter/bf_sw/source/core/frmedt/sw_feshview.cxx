/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_feshview.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 22:40:09 $
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

#define ITEMID_BOXINFO      SID_ATTR_BORDER_INNER
#include "hintids.hxx"

#ifdef WIN
#define NEEDED_BY_FESHVIEW
#define _FESHVIEW_ONLY_INLINE_NEEDED
#endif

#ifndef _SVDOPATH_HXX
#include <bf_svx/svdopath.hxx>
#endif
#ifndef _SVDVMARK_HXX //autogen
#include <bf_svx/svdvmark.hxx>
#endif
#ifndef _SVX_PROTITEM_HXX //autogen
#include <bf_svx/protitem.hxx>
#endif
#ifndef _IPOBJ_HXX //autogen
#include <so3/ipobj.hxx>
#endif

#ifndef _POOLFMT_HRC
#include <poolfmt.hrc>      // fuer InitFldTypes
#endif
#ifndef _FRMFMT_HXX //autogen
#include <frmfmt.hxx>
#endif
#ifndef _FRMATR_HXX
#include <frmatr.hxx>
#endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#include "fesh.hxx"
#include "doc.hxx"
#include "dview.hxx"
#include "dflyobj.hxx"
#include "dcontact.hxx"
#include "viewimp.hxx"
#include "flyfrm.hxx"
#include "ndole.hxx"
#include "txtfrm.hxx"
namespace binfilter {

#define SCROLLVAL 75

//Tattergrenze fuer Drawing-SS
#define MINMOVE ((USHORT)GetOut()->PixelToLogic(Size(Imp()->GetDrawView()->GetMarkHdlSizePixel()/2,0)).Width())

/*N*/ SwFlyFrm *GetFlyFromMarked( const SdrMarkList *pLst, ViewShell *pSh )
/*N*/ {
/*N*/   if ( !pLst )
/*?*/       pLst = pSh->HasDrawView() ? &pSh->Imp()->GetDrawView()->GetMarkList():0;
/*N*/
/*N*/   if ( pLst && pLst->GetMarkCount() == 1 )
/*N*/   {
/*?*/       SdrObject *pO = pLst->GetMark( 0 )->GetObj();
/*?*/       if ( pO->IsWriterFlyFrame() )
/*?*/           return ((SwVirtFlyDrawObj*)pO)->GetFlyFrm();
/*N*/   }
/*N*/   return 0;
/*N*/ }


/*************************************************************************
|*
|*  SwFEShell::SelectObj()
|*
|*  Ersterstellung      MA 16. Nov. 92
|*  Letzte Aenderung    MA 22. Oct. 96
|*
*************************************************************************/

/*N*/ BOOL SwFEShell::SelectObj( const Point& rPt, BYTE nFlag, SdrObject *pObj )
/*N*/ {
DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001 //STRIP001   SET_CURR_SHELL( this );
/*N*/ }

/*************************************************************************
|*
|*  sal_Bool SwFEShell::MoveAnchor( USHORT nDir )
|*
|*  Created        AMA 05/28/2002
|*  Last modify    AMA 05/30/2002
|*
|*  Description: MoveAnchor( nDir ) looked for an another Anchor for
|*  the selected drawing object (or fly frame) in the given direction.
|*  An object "as character" doesn't moves anyway.
|*  A page bounded object could move to the previous/next page with up/down,
|*  an object bounded "at paragraph" moves to the previous/next paragraph, too.
|*  An object bounded "at character" moves to the previous/next paragraph
|*  with up/down and to the previous/next character with left/right.
|*  If the anchor for at paragraph/character bounded objects has vertical or
|*  right_to_left text direction, the directions for up/down/left/right will
|*  interpreted accordingly.
|*  An object bounded "at fly" takes the center of the actual anchor and looks
|*  for the nearest fly frame in the given direction.
|*
*************************************************************************/



/*************************************************************************
|*
|*  SwFEShell::GetSelFrmType()
|*
|*  Ersterstellung      MA 12. Jan. 93
|*  Letzte Aenderung    JP 19.03.96
|*
*************************************************************************/

const SdrMarkList* SwFEShell::_GetMarkList() const
{
    const SdrMarkList* pMarkList = NULL;
    if( Imp()->GetDrawView() != NULL )
        pMarkList = &Imp()->GetDrawView()->GetMarkList();
    return pMarkList;
}

USHORT SwFEShell::GetSelFrmType() const
{
    enum FrmType eType;

    // get marked frame list, and check if anything is selected
    const SdrMarkList* pMarkList = _GetMarkList();
    if( pMarkList == NULL  ||  pMarkList->GetMarkCount() == 0 )
        eType = FRMTYPE_NONE;
    else
    {
        // obtain marked item as fly frame; if no fly frame, it must
        // be a draw object
        const SwFlyFrm* pFly = ::binfilter::GetFlyFromMarked(pMarkList, (ViewShell*)this);
        if ( pFly != NULL )
        {
            if( pFly->IsFlyLayFrm() )
                eType = FRMTYPE_FLY_FREE;
            else if( pFly->IsFlyAtCntFrm() )
                eType = FRMTYPE_FLY_ATCNT;
            else
            {
                ASSERT( pFly->IsFlyInCntFrm(), "Neuer Rahmentyp?" );
                eType = FRMTYPE_FLY_INCNT;
            }
        }
        else
            eType = FRMTYPE_DRAWOBJ;
    }

    return eType;
}

// #108784# does the draw selection contain a control?
bool SwFEShell::IsSelContainsControl() const
{
    bool bRet = false;

    // basically, copy the mechanism from GetSelFrmType(), but call
    // CheckControl... if you get a drawing object
    const SdrMarkList* pMarkList = _GetMarkList();
    if( pMarkList != NULL  &&  pMarkList->GetMarkCount() == 1 )
    {
        // if we have one marked object, get the SdrObject and check
        // whether it contains a control
        const SdrObject* pSdrObject = pMarkList->GetMark( 0 )->GetObj();
        bRet = CheckControlLayer( pSdrObject );
    }
    return bRet;
}

/*************************************************************************
|*
|*  SwFEShell::Scroll()
|*
|*  Ersterstellung      MA 20. Dec. 94
|*  Letzte Aenderung    MA 27. Jul. 95
|*
*************************************************************************/


/*************************************************************************
|*
|*  SwFEShell::SetDragMode()
|*
|*  Ersterstellung      MA 30. Jan. 95
|*  Letzte Aenderung    MA 30. Jan. 95
|*
*************************************************************************/


/*************************************************************************
|*
|*  SwFEShell::BeginDrag()
|*
|*  Ersterstellung      MS 10.06.92
|*  Letzte Aenderung    MA 13. Mar. 96
|*
*************************************************************************/

/*************************************************************************
|*
|*  SwFEShell::Drag()
|*
|*  Ersterstellung      MS 10.06.92
|*  Letzte Aenderung    MA 13. Mar. 96
|*
*************************************************************************/


/*************************************************************************
|*
|*  SwFEShell::EndDrag()
|*
|*  Ersterstellung      MS 10.06.92
|*  Letzte Aenderung    MA 13. Mar. 96
|*
*************************************************************************/


/*************************************************************************
|*
|*  SwFEShell::BreakDrag()
|*
|*  Ersterstellung      OM 02. Okt. 95
|*  Letzte Aenderung    OM 02. Okt. 95
|*
*************************************************************************/


/*************************************************************************
|*
|*  SwFEShell::SelFlyGrabCrsr()
|*
|*  Beschreibung        Wenn ein Fly selektiert ist, zieht er den Crsr in
|*                      den ersten CntntFrm
|*  Ersterstellung      MA 11. Dec. 92
|*  Letzte Aenderung    MA 07. Oct. 96
|*
*************************************************************************/



/*************************************************************************
|*
|*  SwFEShell::SelectionToTop(), SelectionToBottom()
|*
|*  Beschreibung        Selektion nach oben/unten (Z-Order)
|*
|*  Ersterstellung      MA 05. Nov. 92
|*  Letzte Aenderung    MA 03. Jun. 96
|*
*************************************************************************/




/*************************************************************************
|*
|*  SwFEShell::GetLayerId()
|*
|*  Beschreibung        Objekt ueber/unter dem Dokument?
|*                      2 Controls, 1 Heaven, 0 Hell, -1 Uneindeutig
|*  Ersterstellung      MA 20. Dec. 94
|*  Letzte Aenderung    MA 20. Dec. 94
|*
*************************************************************************/


/*************************************************************************
|*
|*  SwFEShell::SelectionToHeaven(), SelectionToHell()
|*
|*  Beschreibung        Objekt ueber/unter dem Dokument
|*  Ersterstellung      MA 20. Dec. 94
|*  Letzte Aenderung    AMA 04. Jun. 98
|*
*************************************************************************/
// OD 25.06.2003 #108784#
// Note: only visible objects can be marked. Thus, objects with invisible
//       layer IDs have not to be considered.
//       If <SwFEShell> exists, layout exists!!



/*************************************************************************
|*
|*  SwFEShell::IsObjSelected(), IsFrmSelected()
|*
|*  Ersterstellung      MA 16. Nov. 92
|*  Letzte Aenderung    MA 17. Jan. 95
|*
*************************************************************************/

/*N*/ USHORT SwFEShell::IsObjSelected() const
/*N*/ {
/*N*/   if ( IsFrmSelected() || !Imp()->HasDrawView() )
/*N*/       return 0;
/*N*/   else
/*N*/       return USHORT( Imp()->GetDrawView()->GetMarkList().GetMarkCount() );
/*N*/ }

/*N*/ BOOL SwFEShell::IsFrmSelected() const
/*N*/ {
/*N*/   if ( !Imp()->HasDrawView() )
/*N*/       return FALSE;
/*N*/   else
/*N*/       return 0 != ::binfilter::GetFlyFromMarked( &Imp()->GetDrawView()->GetMarkList(),
/*N*/                                       (ViewShell*)this );
/*N*/ }



/*************************************************************************
|*
|*  SwFEShell::EndTextEdit()
|*
|*  Ersterstellung      MA 19. Feb. 96
|*  Letzte Aenderung    MA 19. Feb. 96
|*
*************************************************************************/


/*************************************************************************
|*
|*  SwFEShell::IsInsideSelectedObj()
|*
|*  Ersterstellung      MA 16. Nov. 92
|*  Letzte Aenderung    MA 08. Nov. 96
|*
*************************************************************************/


/*************************************************************************
|*
|*  SwFEShell::IsObjSelectable()
|*
|*  Ersterstellung      MA 16. Nov. 92
|*  Letzte Aenderung    MA 02. Feb. 95
|*
*************************************************************************/


// #107513#
// Test if there is a draw object at that position and if it should be selected.
// The 'should' is aimed at Writer text fly frames which may be in front of
// the draw object.

/*************************************************************************
|*
|*  SwFEShell::GotoObj()
|*
|*  Beschreibung        Wenn ein Obj selektiert ist, gehen wir von dessen
|*      TopLeft aus, andernfalls von der Mitte des aktuellen CharRects.
|*  Ersterstellung      MA 01. Jun. 95
|*  Letzte Aenderung    MA 30. Apr. 96
|*
*************************************************************************/
/* -----------------23.09.98 10:29-------------------
 * Beinhaltet das Objekt ein Control oder Gruppen,
 * die nur aus Controls bestehen
 * --------------------------------------------------*/


/*************************************************************************
|*
|*  SwFEShell::ControlCount(), GotoControl()
|*
|*  Ersterstellung      MA 22. Jul. 96
|*  Letzte Aenderung    MA 22. Jul. 96
|*
*************************************************************************/



/*************************************************************************
|*
|*  SwFEShell::BeginCreate()
|*
|*  Ersterstellung      MA 20. Dec. 94
|*  Letzte Aenderung    MA 21. Mar. 95
|*
*************************************************************************/



/*************************************************************************
|*
|*  SwFEShell::MoveCreate()
|*
|*  Ersterstellung      MA 20. Dec. 94
|*  Letzte Aenderung    MA 24. Jan. 95
|*
*************************************************************************/


/*************************************************************************
|*
|*  SwFEShell::EndCreate(), ImpEndCreate()
|*
|*  Ersterstellung      MA 20. Dec. 94
|*  Letzte Aenderung    MA 14. Oct. 96
|*
*************************************************************************/





/*************************************************************************
|*
|*  SwFEShell::BreakCreate()
|*
|*  Ersterstellung      MA 20. Dec. 94
|*  Letzte Aenderung    MA 09. Jan. 95
|*
*************************************************************************/


/*************************************************************************
|*
|*  SwFEShell::IsDrawCreate()
|*
|*  Ersterstellung      OM 16. Mar. 95
|*  Letzte Aenderung    OM 16. Mar. 95
|*
*************************************************************************/


/*************************************************************************
|*
|*  SwFEShell::BeginMark()
|*
|*  Ersterstellung      OM 07. Feb. 95
|*  Letzte Aenderung    OM 07. Feb. 95
|*
*************************************************************************/


/*************************************************************************
|*
|*  SwFEShell::MoveMark()
|*
|*  Ersterstellung      OM 07. Feb. 95
|*  Letzte Aenderung    OM 07. Feb. 95
|*
*************************************************************************/


/*************************************************************************
|*
|*  SwFEShell::EndMark()
|*
|*  Ersterstellung      OM 07. Feb. 95
|*  Letzte Aenderung    MA 08. Feb. 95
|*
*************************************************************************/


/*************************************************************************
|*
|*  SwFEShell::BreakSelect()
|*
|*  Ersterstellung      OM 07. Feb. 95
|*  Letzte Aenderung    OM 07. Feb. 95
|*
*************************************************************************/


/*************************************************************************
|*
|*  SwFEShell::GetAnchorId()
|*
|*  Ersterstellung      MA 30. Jan. 95
|*  Letzte Aenderung    MA 30. Jan. 95
|*
*************************************************************************/


/*************************************************************************
|*
|*  SwFEShell::ChgAnchor()
|*
|*  Ersterstellung      MA 10. Jan. 95
|*  Letzte Aenderung    MA 30. May. 96
|*
*************************************************************************/


/*************************************************************************
|*
|*  SwFEShell::DelSelectedObj()
|*
|*  Ersterstellung      MA 03. Nov. 92
|*  Letzte Aenderung    MA 14. Nov. 95
|*
*************************************************************************/


/*************************************************************************
|*
|*  SwFEShell::GetObjSize(), GetAnchorObjDiff()
|*
|*  Beschreibung        Fuer die Statuszeile zum Erfragen der aktuellen
|*                      Verhaeltnisse
|*  Ersterstellung      MA 25. Apr. 95
|*  Letzte Aenderung    MA 25. Apr. 95
|*
*************************************************************************/






/*************************************************************************
|*
|*  SwFEShell::IsGroupSelected()
|*
|*  Ersterstellung      MA 30. Jan. 95
|*  Letzte Aenderung    MA 30. May. 96
|*
*************************************************************************/


// OD 27.06.2003 #108784# - change return type.
// OD 27.06.2003 #108784# - adjustments for drawing objects in header/footer:
//      allow group, only if all selected objects are in the same header/footer
//      or not in header/footer.

/*************************************************************************
|*
|*  SwFEShell::GroupSelection()
|*
|*  Beschreibung        Die Gruppe bekommt den Anker und das Contactobjekt
|*                      des ersten in der Selektion
|*  Ersterstellung      MA 30. Jan. 95
|*  Letzte Aenderung    MA 23. Apr. 95
|*
*************************************************************************/


/*************************************************************************
|*
|*  SwFEShell::UnGroupSelection()
|*
|*  Beschreibung        Die Einzelobjekte bekommen eine Kopie vom Anker und
|*                      Contactobjekt der Gruppe.
|*  Ersterstellung      MA 30. Jan. 95
|*  Letzte Aenderung    MA 01. Feb. 95
|*
*************************************************************************/


/*************************************************************************
|*
|*  SwFEShell::MirrorSelection()
|*
|*  Ersterstellung      MA 06. Aug. 95
|*  Letzte Aenderung    MA 06. Aug. 95
|*
*************************************************************************/


// springe zum benannten Rahmen (Grafik/OLE)

/*N*/ BOOL SwFEShell::GotoFly( const String& rName, FlyCntType eType, BOOL bSelFrm )
/*N*/ {
/*N*/   BOOL bRet = FALSE;
/*N*/ static BYTE __READONLY_DATA aChkArr[ 4 ] = {
/*N*/            /* FLYCNTTYPE_ALL */   0,
/*N*/            /* FLYCNTTYPE_FRM */   ND_TEXTNODE,
/*N*/            /* FLYCNTTYPE_GRF */   ND_GRFNODE,
/*N*/            /* FLYCNTTYPE_OLE */   ND_OLENODE
/*N*/           };
/*N*/
/*N*/   const SwFlyFrmFmt* pFlyFmt = pDoc->FindFlyByName( rName, aChkArr[ eType]);
/*N*/   if( pFlyFmt )
/*N*/   {
/*N*/       SET_CURR_SHELL( this );
/*N*/
/*N*/       SwClientIter aIter( *(SwModify*)pFlyFmt );
/*N*/       SwFlyFrm* pFrm = (SwFlyFrm*)aIter.First( TYPE( SwFlyFrm ));
/*N*/       if( pFrm )
/*N*/       {
/*N*/           ASSERT( pFrm->IsFlyFrm(), "Wrong FrmType" );
/*N*/           if( bSelFrm )
/*N*/           {
/*?*/               DBG_BF_ASSERT(0, "STRIP"); //STRIP001   SelectObj( pFrm->Frm().Pos(), 0, ((SwFlyFrm*)pFrm)->GetVirtDrawObj() );
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               pFrm->GetAnchor()->Calc();
/*N*/               SwCntntFrm *pCFrm = pFrm->ContainsCntnt();
/*N*/               if ( pCFrm )
/*N*/               {
/*?*/                   DBG_BF_ASSERT(0, "STRIP"); //STRIP001 SwCntntNode   *pCNode = pCFrm->GetNode();
/*N*/               }
/*N*/           }
/*N*/           bRet = TRUE;
/*N*/       }
/*N*/   }
/*N*/   return bRet;
/*N*/ }




// zeige das akt. selektierte "Object" an
/*N*/ void SwFEShell::MakeSelVisible()
/*N*/ {
/*N*/   if( Imp()->HasDrawView() &&
/*N*/       Imp()->GetDrawView()->GetMarkList().GetMarkCount() )
/*N*/   {
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 MakeVisible( Imp()->GetDrawView()->GetAllMarkedRect() );
/*N*/   }
/*N*/   else
/*N*/       SwCrsrShell::MakeSelVisible();
/*N*/ }


//Welcher Schutz ist am selektierten Objekt gesetzt?
/*N*/ BYTE SwFEShell::IsSelObjProtected( FlyProtectType eType ) const
/*N*/ {
/*N*/   int nChk = 0;
/*N*/   BOOL bParent = eType & FLYPROTECT_PARENT;
/*N*/   if( Imp()->HasDrawView() )
/*N*/   {
/*N*/       const SdrMarkList &rMrkList = Imp()->GetDrawView()->GetMarkList();
/*N*/       for( ULONG i = rMrkList.GetMarkCount(); i; )
/*N*/       {
/*?*/           SdrObject *pObj = rMrkList.GetMark( --i )->GetObj();
/*?*/           if( !bParent )
/*?*/           {
/*?*/               nChk |= ( pObj->IsMoveProtect() ? FLYPROTECT_POS : 0 ) |
/*?*/                       ( pObj->IsResizeProtect()? FLYPROTECT_SIZE : 0 );
/*?*/
/*?*/               if( FLYPROTECT_CONTENT & eType && pObj->IsWriterFlyFrame() )
/*?*/               {
/*?*/                   SwFlyFrm *pFly = ((SwVirtFlyDrawObj*)pObj)->GetFlyFrm();
/*?*/                   if ( pFly->GetFmt()->GetProtect().IsCntntProtected() )
/*?*/                       nChk |= FLYPROTECT_CONTENT;
/*?*/
/*?*/                   if ( pFly->Lower() && pFly->Lower()->IsNoTxtFrm() )
/*?*/                   {
/*?*/                       SwOLENode *pNd = ((SwCntntFrm*)pFly->Lower())->GetNode()->GetOLENode();
/*?*/                       if ( pNd )
/*?*/                       {
/*?*/                           SvInPlaceObjectRef aRef = pNd->GetOLEObj().GetOleRef();
/*?*/                           if ( aRef.Is() &&
/*?*/                                SVOBJ_MISCSTATUS_NOTRESIZEABLE & aRef->GetMiscStatus() )
/*?*/                           {
/*?*/                               nChk |= FLYPROTECT_SIZE;
/*?*/                               nChk |= FLYPROTECT_FIXED;
/*?*/                           }
/*?*/                       }
/*?*/                   }
/*?*/               }
/*?*/               nChk &= eType;
/*?*/               if( nChk == eType )
/*?*/                   return eType;
/*?*/           }
/*?*/           SwFrm* pAnch;
/*?*/           if( pObj->IsWriterFlyFrame() )
/*?*/               pAnch = ( (SwVirtFlyDrawObj*)pObj )->GetFlyFrm()->GetAnchor();
/*?*/           else
/*?*/           {
/*?*/               SwDrawContact* pTmp = (SwDrawContact*)GetUserCall(pObj);
/*?*/               pAnch = pTmp ? pTmp->GetAnchor() : NULL;
/*?*/           }
/*?*/           if( pAnch && pAnch->IsProtected() )
/*?*/               return eType;
/*N*/       }
/*N*/   }
/*N*/   return nChk;
/*N*/ }





//Temporaerer Fix bis SS von JOE da ist




/* -----------------------------09.08.2002 07:40------------------------------

 ---------------------------------------------------------------------------*/
/*M*/ int SwFEShell::Chain( SwFrmFmt &rSource, const SwFrmFmt &rDest )
/*M*/ {
/*M*/     return GetDoc()->Chain(rSource, rDest);
/*M*/ }




/*N*/ void SwFEShell::HideChainMarker()
/*N*/ {
/*N*/   if ( pChainFrom )
/*?*/       {DBG_BF_ASSERT(0, "STRIP"); }//STRIP001 pChainFrom->Hide();
/*N*/   if ( pChainTo )
/*?*/       {DBG_BF_ASSERT(0, "STRIP");} //STRIP001 pChainTo->Hide();
/*N*/ }

/*N*/ void SwFEShell::SetChainMarker()
/*N*/ {
/*N*/   FASTBOOL bDelFrom = TRUE,
/*N*/            bDelTo   = TRUE;
/*N*/   if ( IsFrmSelected() )
/*N*/   {
/*?*/       SwFlyFrm *pFly = FindFlyFrm();
/*?*/
/*?*/       XPolygon aPoly(3);
/*?*/       if ( pFly->GetPrevLink() )
/*?*/       {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*?*/       }
/*?*/       if ( pFly->GetNextLink() )
/*?*/       {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*?*/       }
/*N*/   }
/*N*/   if ( bDelFrom )
/*N*/       delete pChainFrom, pChainFrom = 0;
/*N*/   if ( bDelTo )
/*N*/       delete pChainTo,   pChainTo = 0;
/*N*/ }

/* -----------------------------2002/06/24 15:07------------------------------

 ---------------------------------------------------------------------------*/

/** SwFEShell::GetShapeBackgrd

    OD 02.09.2002 for #102450#:
    method determines background color of the page the selected drawing
    object is on and returns this color.
    If no color is found, because no drawing object is selected or ...,
    color COL_BLACK (default color on constructing object of class Color)
    is returned.

    @author OD

    @returns an object of class Color
*/
/*?*/ const Color SwFEShell::GetShapeBackgrd() const
/*?*/ {
/*?*/     Color aRetColor;
/*?*/
/*?*/     // check, if a draw view exists
/*?*/     ASSERT( Imp()->GetDrawView(), "wrong usage of SwFEShell::GetShapeBackgrd - no draw view!");
/*?*/     if( Imp()->GetDrawView() )
/*?*/     {
/*?*/         // determine list of selected objects
/*?*/         const SdrMarkList* pMrkList = &Imp()->GetDrawView()->GetMarkList();
/*?*/         // check, if exactly one object is selected.
/*?*/         ASSERT( pMrkList->GetMarkCount() == 1, "wrong usage of SwFEShell::GetShapeBackgrd - no selected object!");
/*?*/         if ( pMrkList->GetMarkCount() == 1)
/*?*/         {
/*?*/             // get selected object
/*?*/             const SdrObject *pSdrObj = pMrkList->GetMark( 0 )->GetObj();
/*?*/             // check, if selected object is a shape (drawing object)
/*?*/             ASSERT( !pSdrObj->IsWriterFlyFrame(), "wrong usage of SwFEShell::GetShapeBackgrd - selected object is not a drawing object!");
/*?*/             if ( !pSdrObj->IsWriterFlyFrame() )
/*?*/             {
/*?*/                 // determine page frame of the frame the shape is anchored.
/*?*/                 const SwFrm* pAnchorFrm =
/*?*/                         static_cast<SwDrawContact*>(GetUserCall(pSdrObj))->GetAnchor();
/*?*/                 ASSERT( pAnchorFrm, "inconsistent modell - no anchor at shape!");
/*?*/                 if ( pAnchorFrm )
/*?*/                 {
/*?*/                     const SwPageFrm* pPageFrm = pAnchorFrm->FindPageFrm();
/*?*/                     ASSERT( pPageFrm, "inconsistent modell - no page!");
/*?*/                     if ( pPageFrm )
/*?*/                     {
/*?*/                        DBG_BF_ASSERT(0, "STRIP"); //STRIP001  aRetColor = pPageFrm->GetDrawBackgrdColor();
/*?*/                     }
/*?*/                 }
/*?*/             }
/*?*/         }
/*?*/     }
/*?*/
/*?*/     return aRetColor;
/*?*/ }

/** Is default horizontal text direction for selected drawing object right-to-left

    OD 09.12.2002 #103045#
    Because drawing objects only painted for each page only, the default
    horizontal text direction of a drawing object is given by the corresponding
    page property.

    @author OD

    @returns boolean, indicating, if the horizontal text direction of the
    page, the selected drawing object is on, is right-to-left.
*/
/* -----------------20.03.2003 14:35-----------------

 --------------------------------------------------*/

}
