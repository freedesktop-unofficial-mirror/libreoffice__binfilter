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

#include <limits.h>

#include "dialogs.hrc"

#include "dlgutil.hxx"
namespace binfilter {

// -----------------------------------------------------------------------

/*N*/ long CalcToUnit( float nIn, SfxMapUnit eUnit )
/*N*/ {
/*N*/   // nIn ist in Points
/*N*/
/*N*/   DBG_ASSERT( eUnit == SFX_MAPUNIT_TWIP       ||
/*N*/               eUnit == SFX_MAPUNIT_100TH_MM   ||
/*N*/               eUnit == SFX_MAPUNIT_10TH_MM    ||
/*N*/               eUnit == SFX_MAPUNIT_MM         ||
/*N*/               eUnit == SFX_MAPUNIT_CM, "this unit is not implemented" );
/*N*/
/*N*/   float nTmp = nIn;
/*N*/
/*N*/   if ( SFX_MAPUNIT_TWIP != eUnit )
/*N*/       nTmp = nIn * 10 / 567;
/*N*/
/*N*/   switch ( eUnit )
/*N*/   {
/*N*/       case SFX_MAPUNIT_100TH_MM:  nTmp *= 100; break;
/*?*/       case SFX_MAPUNIT_10TH_MM:   nTmp *= 10;  break;
/*?*/       case SFX_MAPUNIT_MM:                     break;
/*?*/       case SFX_MAPUNIT_CM:        nTmp /= 10;  break;
        default: break;
/*N*/   }
/*N*/
/*N*/   nTmp *= 20;
/*N*/   long nRet = (long)nTmp;
/*N*/   return nRet;
/*N*/ //!   return (long)(nTmp * 20);
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ long CalcToPoint( long nIn, SfxMapUnit eUnit, USHORT nFaktor )
/*N*/ {
/*N*/   DBG_ASSERT( eUnit == SFX_MAPUNIT_TWIP       ||
/*N*/               eUnit == SFX_MAPUNIT_100TH_MM   ||
/*N*/               eUnit == SFX_MAPUNIT_10TH_MM    ||
/*N*/               eUnit == SFX_MAPUNIT_MM         ||
/*N*/               eUnit == SFX_MAPUNIT_CM, "this unit is not implemented" );
/*N*/
/*N*/   long nRet = 0;
/*N*/
/*N*/   if ( SFX_MAPUNIT_TWIP == eUnit )
/*N*/       nRet = nIn;
/*N*/   else
/*N*/       nRet = nIn * 567;
/*N*/
/*N*/   switch ( eUnit )
/*N*/   {
/*N*/       case SFX_MAPUNIT_100TH_MM:  nRet /= 100; break;
/*?*/       case SFX_MAPUNIT_10TH_MM:   nRet /= 10;  break;
/*?*/       case SFX_MAPUNIT_MM:                     break;
/*?*/       case SFX_MAPUNIT_CM:        nRet *= 10;  break;
        default: break;
/*N*/   }
/*N*/
/*N*/   // ggf. aufrunden
/*N*/   if ( SFX_MAPUNIT_TWIP != eUnit )
/*N*/   {
/*N*/       long nMod = 10;
/*N*/       long nTmp = nRet % nMod;
/*N*/
/*N*/       if ( nTmp >= 4 )
/*N*/           nRet += 10 - nTmp;
/*N*/       nRet /= 10;
/*N*/   }
/*N*/   return nRet * nFaktor / 20;
/*N*/ }

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
