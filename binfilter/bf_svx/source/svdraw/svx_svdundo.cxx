/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_svdundo.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 21:47:29 $
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

#include "svdundo.hxx"
#include "svdstr.hrc"   // Namen aus der Resource
#include "scene3d.hxx"


// #i11426#

// #109587#

// #109587#
namespace binfilter {

////////////////////////////////////////////////////////////////////////////////////////////////////








////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ SdrUndoGroup::SdrUndoGroup(SdrModel& rNewMod)
/*N*/ : SdrUndoAction(rNewMod),
/*N*/   aBuf(1024,32,32),
/*N*/   eFunction(SDRREPFUNC_OBJ_NONE)      /*#72642#*/
/*N*/ {}

/*?*/ SdrUndoGroup::SdrUndoGroup(SdrModel& rNewMod,const String& rStr)
/*?*/ : SdrUndoAction(rNewMod),
/*?*/   aBuf(1024,32,32),
/*?*/   aComment(rStr),
/*?*/   eFunction(SDRREPFUNC_OBJ_NONE)
/*?*/ {}

/*N*/ SdrUndoGroup::~SdrUndoGroup()
/*N*/ {
/*N*/   Clear();
/*N*/ }

/*N*/ void SdrUndoGroup::Clear()
/*N*/ {
/*N*/   for (ULONG nu=0; nu<GetActionCount(); nu++) {
/*N*/       SdrUndoAction* pAct=GetAction(nu);
/*N*/       delete pAct;
/*N*/   }
/*N*/   aBuf.Clear();
/*N*/ }

/*N*/ void SdrUndoGroup::AddAction(SdrUndoAction* pAct)
/*N*/ {
/*N*/   aBuf.Insert(pAct,CONTAINER_APPEND);
/*N*/ }







////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
//
//   @@@@   @@@@@   @@@@@@  @@@@@   @@@@   @@@@@@   @@@@
//  @@  @@  @@  @@      @@  @@     @@  @@    @@    @@  @@
//  @@  @@  @@  @@      @@  @@     @@        @@    @@
//  @@  @@  @@@@@       @@  @@@@   @@        @@     @@@@
//  @@  @@  @@  @@      @@  @@     @@        @@        @@
//  @@  @@  @@  @@  @@  @@  @@     @@  @@    @@    @@  @@
//   @@@@   @@@@@    @@@@   @@@@@   @@@@     @@     @@@@
//
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ SdrUndoObj::SdrUndoObj(SdrObject& rNewObj):
/*N*/   SdrUndoAction(*rNewObj.GetModel()),
/*N*/   pObj(&rNewObj)
/*N*/ {
/*N*/ }


// #94278# common call method for evtl. page change when UNDO/REDO
// is triggered

////////////////////////////////////////////////////////////////////////////////////////////////////










////////////////////////////////////////////////////////////////////////////////////////////////////







////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ SdrUndoGeoObj::SdrUndoGeoObj(SdrObject& rNewObj):
/*N*/   SdrUndoObj(rNewObj),
/*N*/   pUndoGeo(NULL),
/*N*/   pRedoGeo(NULL),
/*N*/   pUndoGroup(NULL)
/*N*/ {
/*N*/   SdrObjList* pOL=rNewObj.GetSubList();
/*N*/   if (pOL!=NULL && pOL->GetObjCount() && !rNewObj.ISA(E3dScene))
/*N*/   {
/*?*/       // Aha, Gruppenobjekt
/*?*/       // AW: Aber keine 3D-Szene, dann nur fuer die Szene selbst den Undo anlegen
/*?*/       pUndoGroup=new SdrUndoGroup(*pObj->GetModel());
/*?*/       ULONG nObjAnz=pOL->GetObjCount();
/*?*/       for (ULONG nObjNum=0; nObjNum<nObjAnz; nObjNum++) {
/*?*/           pUndoGroup->AddAction(new SdrUndoGeoObj(*pOL->GetObj(nObjNum)));
/*?*/       }
/*N*/   } else {
/*N*/       pUndoGeo=pObj->GetGeoData();
/*N*/   }
/*N*/ }

/*N*/ SdrUndoGeoObj::~SdrUndoGeoObj()
/*N*/ {
/*N*/   if (pUndoGeo!=NULL) delete pUndoGeo;
/*N*/   if (pRedoGeo!=NULL) delete pRedoGeo;
/*N*/   if (pUndoGroup!=NULL) delete pUndoGroup;
/*N*/ }




////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ SdrUndoObjList::SdrUndoObjList(SdrObject& rNewObj, FASTBOOL bOrdNumDirect):
/*N*/   pView(NULL),
/*N*/   pPageView(NULL),
/*N*/   SdrUndoObj(rNewObj),
/*N*/   bOwner(FALSE)
/*N*/ {
/*N*/   pObjList=pObj->GetObjList();
/*N*/   if (bOrdNumDirect) {
/*?*/       nOrdNum=pObj->GetOrdNumDirect();
/*N*/   } else {
/*N*/       nOrdNum=pObj->GetOrdNum();
/*N*/   }
/*N*/ }
/*N*/
/*N*/ SdrUndoObjList::~SdrUndoObjList()
/*N*/ {
/*N*/   if (pObj!=NULL && IsOwner())
/*N*/   {
/*N*/       // Attribute muessen wieder in den regulaeren Pool
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 SetOwner(FALSE);
/*?*/
/*?*/       // nun loeschen
/*N*/   }
/*N*/ }


////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////







////////////////////////////////////////////////////////////////////////////////////////////////////










////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////
// #i11702#


////////////////////////////////////////////////////////////////////////////////////////////////////





////////////////////////////////////////////////////////////////////////////////////////////////////










////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  @@      @@@@   @@  @@  @@@@@  @@@@@
//  @@     @@  @@  @@  @@  @@     @@  @@
//  @@     @@  @@  @@  @@  @@     @@  @@
//  @@     @@@@@@   @@@@   @@@@   @@@@@
//  @@     @@  @@    @@    @@     @@  @@
//  @@     @@  @@    @@    @@     @@  @@
//  @@@@@  @@  @@    @@    @@@@@  @@  @@
//
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  @@@@@    @@@@    @@@@   @@@@@   @@@@
//  @@  @@  @@  @@  @@  @@  @@     @@  @@
//  @@  @@  @@  @@  @@      @@     @@
//  @@@@@   @@@@@@  @@ @@@  @@@@    @@@@
//  @@      @@  @@  @@  @@  @@         @@
//  @@      @@  @@  @@  @@  @@     @@  @@
//  @@      @@  @@   @@@@@  @@@@@   @@@@
//
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ SdrUndoPage::SdrUndoPage(SdrPage& rNewPg):
/*N*/   SdrUndoAction(*rNewPg.GetModel()), pPage(&rNewPg)
/*N*/ { }





////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ SdrUndoPageList::SdrUndoPageList(SdrPage& rNewPg):
/*N*/   SdrUndoPage(rNewPg),
/*N*/   bItsMine(FALSE)
/*N*/ {
/*N*/   nPageNum=rNewPg.GetPageNum();
/*N*/ }

/*N*/ SdrUndoPageList::~SdrUndoPageList()
/*N*/ {
/*N*/   if(bItsMine && pPage)
/*N*/   {
/*?*/       delete pPage;
/*?*/       pPage = 0L;
/*N*/   }
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////









////////////////////////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////////////////////////////





////////////////////////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  @@   @@  @@@@   @@@@  @@@@@@ @@@@@ @@@@@   @@@@@   @@@@   @@@@  @@@@@  @@@@
//  @@@ @@@ @@  @@ @@  @@   @@   @@    @@  @@  @@  @@ @@  @@ @@  @@ @@    @@  @@
//  @@@@@@@ @@  @@ @@       @@   @@    @@  @@  @@  @@ @@  @@ @@     @@    @@
//  @@@@@@@ @@@@@@  @@@@    @@   @@@@  @@@@@   @@@@@  @@@@@@ @@ @@@ @@@@   @@@@
//  @@ @ @@ @@  @@     @@   @@   @@    @@  @@  @@     @@  @@ @@  @@ @@        @@
//  @@   @@ @@  @@ @@  @@   @@   @@    @@  @@  @@     @@  @@ @@  @@ @@    @@  @@
//  @@   @@ @@  @@  @@@@    @@   @@@@@ @@  @@  @@     @@  @@  @@@@@ @@@@@  @@@@
//
////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////////////////////////////




}
