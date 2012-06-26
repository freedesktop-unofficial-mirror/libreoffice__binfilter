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

#include <limits.h>             // USHRT_MAX

#include <bf_sfx2/docfile.hxx>

using namespace ::ucbhelper;
using namespace ::com::sun::star::uno;

#include "dialogs.hrc"
#include "impgrf.hrc"

#define _SVX_IMPGRF_CXX
#include "impgrf.hxx"

#include "dialmgr.hxx"
#include "helpid.hrc"
namespace binfilter {

// defines ---------------------------------------------------------------

#define IMPGRF_INIKEY_ASLINK        "ImportGraphicAsLink"
#define IMPGRF_INIKEY_PREVIEW       "ImportGraphicPreview"
#define IMPGRF_CONFIGNAME           String(DEFINE_CONST_UNICODE("ImportGraphicDialog"))

// -----------------------------------------------------------------------

/*N*/ GraphicFilter* DialogsResMgr::GetGrfFilter_Impl()
/*N*/ {
/*N*/   if( !pGrapicFilter )
/*N*/   {
/*N*/ #ifndef SVX_LIGHT
/*N*/       pGrapicFilter = new GraphicFilter;
/*N*/ #else
/*N*/       pGrapicFilter = new GraphicFilter(sal_False);
/*N*/ #endif
/*N*/       ::binfilter::FillFilter( *pGrapicFilter );
/*N*/   }
/*N*/   return pGrapicFilter;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ GraphicFilter* GetGrfFilter()
/*N*/ {
/*N*/   return (*(DialogsResMgr**)GetAppData(BF_SHL_SVX))->GetGrfFilter_Impl();
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ USHORT FillFilter( GraphicFilter& rFilter )
/*N*/ {
/*N*/     return rFilter.GetImportFormatCount();
/*N*/ }

// -----------------------------------------------------------------------

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
