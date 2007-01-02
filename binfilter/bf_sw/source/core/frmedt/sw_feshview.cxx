/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_feshview.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: hr $ $Date: 2007-01-02 17:51:09 $
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

/*N*/ BOOL SwFEShell::IsFrmSelected() const
/*N*/ {
/*N*/   if ( !Imp()->HasDrawView() )
/*N*/       return FALSE;
/*N*/   else
/*N*/       return 0 != ::binfilter::GetFlyFromMarked( &Imp()->GetDrawView()->GetMarkList(),
/*N*/                                       (ViewShell*)this );
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

}
