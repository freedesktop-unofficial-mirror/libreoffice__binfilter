/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */

#include "svdcrtv.hxx"
#include "svdio.hxx"


namespace binfilter {

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
//
//   @@@@  @@@@@  @@@@@  @@@@  @@@@@@ @@@@@  @@ @@ @@ @@@@@ @@   @@
//  @@  @@ @@  @@ @@    @@  @@   @@   @@     @@ @@ @@ @@    @@   @@
//  @@     @@  @@ @@    @@  @@   @@   @@     @@ @@ @@ @@    @@ @ @@
//  @@     @@@@@  @@@@  @@@@@@   @@   @@@@   @@@@@ @@ @@@@  @@@@@@@
//  @@     @@  @@ @@    @@  @@   @@   @@      @@@  @@ @@    @@@@@@@
//  @@  @@ @@  @@ @@    @@  @@   @@   @@      @@@  @@ @@    @@@ @@@
//   @@@@  @@  @@ @@@@@ @@  @@   @@   @@@@@    @   @@ @@@@@ @@   @@
//
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void SdrCreateView::ImpClearVars()
/*N*/ {
/*N*/   nAktInvent=SdrInventor;
/*N*/   nAktIdent=OBJ_NONE;
/*N*/   pCurrentLibObj=NULL;
/*N*/   bCurrentLibObjMoveNoResize=FALSE;
/*N*/   bCurrentLibObjSetDefAttr=FALSE;
/*N*/   bCurrentLibObjSetDefLayer=FALSE;
/*N*/   pAktCreate=NULL;
/*N*/   pCreatePV=NULL;
/*N*/   bAutoTextEdit=FALSE;
/*N*/   b1stPointAsCenter=FALSE;
/*N*/   aAktCreatePointer=Pointer(POINTER_CROSS);
/*N*/   bUseIncompatiblePathCreateInterface=FALSE;
/*N*/   bAutoClosePolys=TRUE;
/*N*/   nAutoCloseDistPix=5;
/*N*/   nFreeHandMinDistPix=10;
/*N*/ }

/*N*/ SdrCreateView::SdrCreateView(SdrModel* pModel1, OutputDevice* pOut):
/*N*/   SdrDragView(pModel1,pOut)
/*N*/ {
/*N*/   ImpClearVars();
/*N*/ }

/*N*/ SdrCreateView::~SdrCreateView()
/*N*/ {
/*N*/   delete pCurrentLibObj;
/*N*/   delete pAktCreate;
/*N*/ }


/*N*/ BOOL SdrCreateView::IsAction() const
/*N*/ {
/*N*/   return SdrDragView::IsAction() || pAktCreate!=NULL;
/*N*/ }


/*N*/ void SdrCreateView::BrkAction()
/*N*/ {
/*N*/   SdrDragView::BrkAction();
/*N*/ }


/*N*/ void SdrCreateView::ToggleShownXor(OutputDevice* pOut, const Region* pRegion) const
/*N*/ {
/*N*/   SdrDragView::ToggleShownXor(pOut,pRegion);
/*N*/ }

/*N*/ BOOL SdrCreateView::CheckEdgeMode()
/*N*/ {
/*N*/   if (pAktCreate!=NULL) {
/*?*/       // wird vom EdgeObj gemanaged
/*?*/       if (nAktInvent==SdrInventor && nAktIdent==OBJ_EDGE) return FALSE;
/*N*/   }
/*N*/   if (!IsCreateMode() || nAktInvent!=SdrInventor || nAktIdent!=OBJ_EDGE || pCurrentLibObj!=NULL) {
/*N*/       return FALSE;
/*N*/   } else {
/*N*/       // TRUE heisst: MouseMove soll Connect checken
/*?*/       return !IsAction();
/*N*/   }
/*N*/ }


/*N*/ BOOL SdrCreateView::IsTextTool() const
/*N*/ {
/*N*/   return eEditMode==SDREDITMODE_CREATE
            && pCurrentLibObj==NULL
            && nAktInvent==SdrInventor
            && (  nAktIdent==OBJ_TEXT
               || nAktIdent==OBJ_TEXTEXT
               || nAktIdent==OBJ_TITLETEXT
               || nAktIdent==OBJ_OUTLINETEXT
               );
/*N*/ }


/*N*/ void SdrCreateView::SetCurrentObj(UINT16 nIdent, UINT32 nInvent)
/*N*/ {
/*N*/   if (pCurrentLibObj!=NULL) {
/*?*/       delete pCurrentLibObj;
/*?*/       pCurrentLibObj=NULL;
/*N*/   }
/*N*/   if (nAktInvent!=nInvent || nAktIdent!=nIdent) {
/*N*/       nAktInvent=nInvent;
/*N*/       nAktIdent=nIdent;
/*N*/       SdrObject* pObj = SdrObjFactory::MakeNewObject(nInvent,nIdent,NULL,NULL);
/*N*/
/*N*/       if(pObj)
/*N*/       {
/*N*/           // Auf pers. Wunsch von Marco:
/*N*/           // Mauszeiger bei Textwerkzeug immer I-Beam. Fadenkreuz
/*N*/           // mit kleinem I-Beam erst bai MouseButtonDown
/*N*/           if(IsTextTool())
/*N*/           {
/*N*/               // #81944# AW: Here the correct pointer needs to be used
/*N*/               // if the default is set to vertical writing
/*?*/               aAktCreatePointer = POINTER_TEXT;
/*N*/           }
/*N*/           else
/*N*/               aAktCreatePointer = pObj->GetCreatePointer();
/*N*/
/*N*/           delete pObj;
/*N*/       }
/*N*/       else
/*N*/       {
/*?*/           aAktCreatePointer = Pointer(POINTER_CROSS);
/*N*/       }
/*N*/   }
/*N*/
/*N*/   CheckEdgeMode();
/*N*/ }


////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void SdrCreateView::WriteRecords(SvStream& rOut) const
/*N*/ {
/*N*/   SdrDragView::WriteRecords(rOut);
/*N*/   {
/*N*/       SdrNamedSubRecord aSubRecord(rOut,STREAM_WRITE,SdrInventor,SDRIORECNAME_VIEWCROBJECT);
/*N*/       rOut<<nAktInvent;
/*N*/       rOut<<nAktIdent;
/*N*/   } {
/*N*/       SdrNamedSubRecord aSubRecord(rOut,STREAM_WRITE,SdrInventor,SDRIORECNAME_VIEWCRFLAGS);
/*N*/       rOut<<BOOL(b1stPointAsCenter);
/*N*/   } {
/*N*/       // in der CreateView (statt ObjEditView) weil sonst inkompatibel.
/*N*/       SdrNamedSubRecord aSubRecord(rOut,STREAM_WRITE,SdrInventor,SDRIORECNAME_VIEWTEXTEDIT);
/*N*/       rOut<<BOOL(bQuickTextEditMode);
/*N*/   } {
/*N*/       // in der CreateView (statt ObjEditView) weil sonst inkompatibel.
/*N*/       SdrNamedSubRecord aSubRecord(rOut,STREAM_WRITE,SdrInventor,SDRIORECNAME_VIEWMACRO);
/*N*/       rOut<<BOOL(bMacroMode);
/*N*/   }
/*N*/ }

/*N*/ BOOL SdrCreateView::ReadRecord(const SdrIOHeader& rViewHead,
/*N*/   const SdrNamedSubRecord& rSubHead,
/*N*/   SvStream& rIn)
/*N*/ {
/*N*/   BOOL bRet=FALSE;
/*N*/   if (rSubHead.GetInventor()==SdrInventor) {
/*N*/       bRet=TRUE;
/*N*/       switch (rSubHead.GetIdentifier()) {
/*N*/           case SDRIORECNAME_VIEWCROBJECT: {
/*N*/               UINT32 nInvent;
/*N*/               UINT16 nIdent;
/*N*/               rIn>>nInvent;
/*N*/               rIn>>nIdent;
/*N*/               SetCurrentObj(nIdent,nInvent);
/*N*/           } break;
/*N*/           case SDRIORECNAME_VIEWCRFLAGS: {
/*N*/               BOOL bTmp; rIn>>bTmp; b1stPointAsCenter=bTmp;
/*N*/           } break;
/*N*/           case SDRIORECNAME_VIEWTEXTEDIT: {
/*N*/               // in der CreateView (statt ObjEditView) weil sonst inkompatibel.
/*N*/               BOOL bTmp; rIn>>bTmp; bQuickTextEditMode=bTmp;
/*N*/           } break;
/*N*/           case SDRIORECNAME_VIEWMACRO: {
/*N*/               // in der CreateView (statt ObjEditView) weil sonst inkompatibel.
/*N*/               BOOL bTmp; rIn>>bTmp; bMacroMode=bTmp;
/*N*/           } break;
/*N*/           default: bRet=FALSE;
/*N*/       }
/*N*/   }
/*N*/   if (!bRet) bRet=SdrDragView::ReadRecord(rViewHead,rSubHead,rIn);
/*N*/   return bRet;
/*N*/ }

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
