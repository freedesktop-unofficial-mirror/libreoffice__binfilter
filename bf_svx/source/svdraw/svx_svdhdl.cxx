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

#include "svdetc.hxx"
#include "svdmrkv.hxx"
#include "svdstr.hrc"

// #105678#
namespace binfilter {

SdrHdl::~SdrHdl() {}

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ class ImplHdlListData
/*N*/ {
/*N*/ public:
/*N*/   ULONG                   mnFocusIndex;
/*N*/   SdrMarkView*                pView;
/*N*/
/*N*/   ImplHdlListData(SdrMarkView* pV): mnFocusIndex(CONTAINER_ENTRY_NOTFOUND), pView(pV) {}
/*N*/ };


/*N*/ SdrHdlList::SdrHdlList(SdrMarkView* pV)
/*N*/ : pImpl(new ImplHdlListData(pV))
/*N*/ , aList(1024,32,32)
/*N*/ {
/*N*/   nHdlSize = 3;
/*N*/   bRotateShear = FALSE;
/*N*/   bMoveOutside = FALSE;
/*N*/   bDistortShear = FALSE;
/*N*/ }
/*N*/
/*N*/ SdrHdlList::~SdrHdlList()
/*N*/ {
/*N*/   Clear();
/*N*/   delete pImpl;
/*N*/ }


/*N*/ void SdrHdlList::Clear()
/*N*/ {
/*N*/   aList.Clear();
/*N*/
/*N*/   bRotateShear=FALSE;
/*N*/   bDistortShear=FALSE;
/*N*/ }

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
