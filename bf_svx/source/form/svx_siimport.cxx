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

#include "siimport.hxx"

#include "svdorect.hxx"

#include "svdio.hxx"

#include "svdmodel.hxx"

#include "xflclit.hxx"

#include "xlnclit.hxx"

#include "xtable.hxx"
namespace binfilter {

const UINT32 SiInventor = UINT32('S')*0x00000001+
                          UINT32('D')*0x00000100+
                          UINT32('V')*0x00010000+
                          UINT32('C')*0x01000000;

#define OBJ_CHECKBOX            ((UINT16)0)
#define OBJ_RADIOBUTTON         ((UINT16)1)
#define OBJ_PUSHBUTTON          ((UINT16)2)
#define OBJ_SPINBUTTON          ((UINT16)3)
#define OBJ_FIXEDTEXT           ((UINT16)4)
#define OBJ_GROUPBOX            ((UINT16)5)
#define OBJ_LISTBOX             ((UINT16)6)
#define OBJ_COMBOBOX            ((UINT16)7)
#define OBJ_EDIT                ((UINT16)8)
#define OBJ_HSCROLLBAR          ((UINT16)9)
#define OBJ_VSCROLLBAR          ((UINT16)10)

#define OBJ_URLBUTTON           ((UINT16)25)


//============================================================================
// SiImportRect
//============================================================================

class SiImportRect : public SdrRectObj
{
public:
    SiImportRect();

    using SdrRectObj::operator=;

    virtual void ReadData(const SdrObjIOHeader& rHead, SvStream& rIn);
};

//----------------------------------------------------------------------------

/*N*/ SiImportRect::SiImportRect() : SdrRectObj()
/*N*/ {
/*N*/ }

//----------------------------------------------------------------------------

/*N*/ void SiImportRect::ReadData(const SdrObjIOHeader& rHead, SvStream& rIn)
/*N*/ {
/*N*/   // SdrRectObj ueberspringen!!!!
/*N*/   SdrObject::ReadData( rHead, rIn );
/*N*/   SdrDownCompat aCompat( rIn, STREAM_READ );
/*N*/   aRect = aOutRect;
/*N*/   SfxItemSet aSet(pModel->GetItemPool());
/*N*/   aSet.Put(XFillStyleItem(XFILL_SOLID));
/*N*/   aSet.Put(XFillColorItem(String(), RGB_Color(COL_LIGHTRED)));
/*N*/   aSet.Put(XLineStyleItem(XLINE_SOLID));
/*N*/   aSet.Put(XLineColorItem(String(), RGB_Color(COL_BLACK)));
/*N*/
/*N*/     SetItemSet(aSet);
/*N*/
/*N*/   SetXPolyDirty();
/*N*/ }


//============================================================================
// SiImportFactory
//============================================================================

/*N*/ SiImportFactory::SiImportFactory()
/*N*/ {
/*N*/   SdrObjFactory::InsertMakeObjectHdl( LINK(this, SiImportFactory, MakeObject) );
/*N*/ }

//----------------------------------------------------------------------------

/*N*/ SiImportFactory::~SiImportFactory()
/*N*/ {
/*N*/ }

//----------------------------------------------------------------------------

/*N*/ IMPL_LINK( SiImportFactory, MakeObject, SdrObjFactory *, pObjFactory )
/*N*/ {
/*N*/   if( pObjFactory->nInventor == SiInventor )
/*N*/   {
/*N*/       if( pObjFactory->nIdentifier <= OBJ_VSCROLLBAR ||
/*N*/           pObjFactory->nIdentifier == OBJ_URLBUTTON )
/*N*/       {
/*N*/             switch( pObjFactory->nIdentifier )
/*N*/           {
/*N*/               case OBJ_CHECKBOX:
/*N*/               case OBJ_RADIOBUTTON:
/*N*/               case OBJ_PUSHBUTTON:
/*N*/               case OBJ_SPINBUTTON:
/*N*/               case OBJ_FIXEDTEXT:
/*N*/               case OBJ_GROUPBOX:
/*N*/               case OBJ_LISTBOX:
/*N*/               case OBJ_COMBOBOX:
/*N*/               case OBJ_EDIT:
/*N*/               case OBJ_HSCROLLBAR:
/*N*/               case OBJ_VSCROLLBAR:
/*N*/               case OBJ_URLBUTTON:
/*N*/                   pObjFactory->pNewObj = new SiImportRect();
/*N*/           }
/*N*/         }
/*N*/   }
/*N*/
/*N*/   return 0;
/*N*/ }

//----------------------------------------------------------------------------



}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
