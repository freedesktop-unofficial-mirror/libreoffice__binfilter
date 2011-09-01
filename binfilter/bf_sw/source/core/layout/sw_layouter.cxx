/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2000, 2010 Oracle and/or its affiliates.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/


#ifdef _MSC_VER
#pragma hdrstop
#endif

#include "layouter.hxx"

#include <horiornt.hxx>

#include "doc.hxx"
#include "pagefrm.hxx"
namespace binfilter {

/*N*/ #define LOOP_DETECT 250

/*N*/ class SwLooping
/*N*/ {
/*N*/   USHORT nMinPage;
/*N*/   USHORT nMaxPage;
/*N*/   USHORT nCount;
/*N*/ public:
/*N*/   SwLooping( SwPageFrm* pPage );
/*N*/   static void Drastic( SwFrm* pFrm );
/*N*/ };






/*N*/ SwLooping::SwLooping( SwPageFrm* pPage )
/*N*/ {
/*N*/   OSL_ENSURE( pPage, "Where's my page?" );
/*N*/   nMinPage = pPage->GetPhyPageNum();
/*N*/   nMaxPage = nMinPage;
/*N*/   nCount = 0;
/*N*/ }

/*N*/ void SwLooping::Drastic( SwFrm* pFrm )
/*N*/ {
/*N*/   while( pFrm )
/*N*/   {
/*N*/       if( pFrm->IsLayoutFrm() )
/*N*/           Drastic( ((SwLayoutFrm*)pFrm)->Lower() );
/*N*/       pFrm->bValidPos = TRUE;
/*N*/       pFrm->bValidSize = TRUE;
/*N*/       pFrm->bValidPrtArea = TRUE;
/*N*/       pFrm = pFrm->GetNext();
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|*  SwLayouter::SwLayouter()
|*
|*************************************************************************/

/*N*/ SwLayouter::SwLayouter()
/*N*/ {
/*N*/ }

/*N*/ SwLayouter::~SwLayouter()
/*N*/ {
/*N*/ }

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
