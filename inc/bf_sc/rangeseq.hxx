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

#ifndef SC_RANGESEQ_HXX
#define SC_RANGESEQ_HXX

#include <bf_svtools/bf_solar.h>

#include <com/sun/star/uno/Any.h>
namespace binfilter {

class SvNumberFormatter;
class ScDocument;
class ScRange;
class ScMatrix;

class ScRangeToSequence
{
public:
    static BOOL FillLongArray( ::com::sun::star::uno::Any& rAny,
                                ScDocument* pDoc, const ScRange& rRange );
    static BOOL FillLongArray( ::com::sun::star::uno::Any& rAny,
                                const ScMatrix* pMatrix );
    static BOOL FillDoubleArray( ::com::sun::star::uno::Any& rAny,
                                ScDocument* pDoc, const ScRange& rRange );
    static BOOL FillDoubleArray( ::com::sun::star::uno::Any& rAny,
                                const ScMatrix* pMatrix );
    static BOOL FillStringArray( ::com::sun::star::uno::Any& rAny,
                                ScDocument* pDoc, const ScRange& rRange );
    static BOOL FillStringArray( ::com::sun::star::uno::Any& rAny,
                                const ScMatrix* pMatrix, SvNumberFormatter* pFormatter );
    static BOOL FillMixedArray( ::com::sun::star::uno::Any& rAny,
                                ScDocument* pDoc, const ScRange& rRange,
                                BOOL bAllowNV = FALSE );
    static BOOL FillMixedArray( ::com::sun::star::uno::Any& rAny,
                                const ScMatrix* pMatrix );
};



} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
