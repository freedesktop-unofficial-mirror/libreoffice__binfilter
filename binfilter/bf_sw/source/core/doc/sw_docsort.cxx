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

#include <horiornt.hxx>
#include <osl/diagnose.h>
#include <doc.hxx>

namespace binfilter {

using namespace ::com::sun::star::lang;

/*--------------------------------------------------------------------
    Beschreibung: Text sortieren im Document
 --------------------------------------------------------------------*/

/*N*/ BOOL SwDoc::SortText(const SwPaM& /*rPaM*/, const SwSortOptions& /*rOpt*/)
/*N*/ {
/*N*/   DBG_BF_ASSERT(0, "STRIP");
/*N*/  return TRUE;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: Tabelle sortieren im Document
 --------------------------------------------------------------------*/

/*N*/ BOOL SwDoc::SortTbl(const SwSelBoxes& /*rBoxes*/, const SwSortOptions& /*rOpt*/)
/*N*/ {
/*N*/   DBG_BF_ASSERT(0, "STRIP");
/*N*/   return TRUE;
/*N*/ }

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
