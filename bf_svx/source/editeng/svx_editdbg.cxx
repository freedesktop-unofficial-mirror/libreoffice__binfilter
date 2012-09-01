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


#ifdef _MSC_VER
#pragma hdrstop
#endif

#include "eeitem.hxx"
#include "eeitemid.hxx"





#include <vcl/window.hxx>

#include <editdoc.hxx>
namespace binfilter {

#if defined( DBG_UTIL ) || ( OSL_DEBUG_LEVEL > 1 )









/*N*/ BOOL CheckOrderedList( CharAttribArray& rAttribs, BOOL bStart )
/*N*/ {
/*N*/   USHORT nPrev = 0;
/*N*/   for ( USHORT nAttr = 0; nAttr < rAttribs.Count(); nAttr++ )
/*N*/   {
/*N*/       EditCharAttrib* pAttr = rAttribs[nAttr];
/*N*/       USHORT nCur = bStart ? pAttr->GetStart() : pAttr->GetEnd();
/*N*/       if ( nCur < nPrev )
/*N*/           return FALSE;
/*N*/
/*N*/       nPrev = nCur;
/*N*/   }
/*N*/   return TRUE;
/*N*/ }

#endif

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
