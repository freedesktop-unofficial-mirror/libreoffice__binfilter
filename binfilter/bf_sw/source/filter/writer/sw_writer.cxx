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

#include <hintids.hxx>

#define _SVSTDARR_STRINGSSORTDTOR

 #ifndef _STREAM_HXX //autogen
 #include <tools/stream.hxx>
 #endif
#include <bf_svx/fontitem.hxx>
#include <bf_svx/eeitem.hxx>

#include <shellio.hxx>

#include <horiornt.hxx>
#include <errhdl.hxx>

#include <pam.hxx>
#include <doc.hxx>
#include <docary.hxx>
#include <bookmrk.hxx>          // fuer SwBookmark ...
#include <numrule.hxx>

#include <swerror.h>
namespace binfilter {

// Stringbuffer fuer die umgewandelten Zahlen
static sal_Char aNToABuf[] = "0000000000000000000000000";
#define NTOABUFLEN (sizeof(aNToABuf))

/*N*/ DECLARE_TABLE( SwBookmarkNodeTable, SvPtrarr* )

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
