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

#ifndef SC_POOLHELP_HXX
#define SC_POOLHELP_HXX

#include <salhelper/simplereferenceobject.hxx>

namespace binfilter {

class SvNumberFormatter;
class SfxItemPool;
class ScDocument;
class ScDocumentPool;
class ScStyleSheetPool;


class ScPoolHelper : public salhelper::SimpleReferenceObject
{
private:
    ScDocumentPool*     pDocPool;
    ScStyleSheetPool*   pStylePool;
    SvNumberFormatter*  pFormTable;
    SfxItemPool*        pEditPool;                      // EditTextObjectPool
    SfxItemPool*        pEnginePool;                    // EditEnginePool

public:
                ScPoolHelper( ScDocument* pSourceDoc );
    virtual     ~ScPoolHelper();

                // called in dtor of main document
    void        SourceDocumentGone();

                // access to pointers (are never 0):
    ScDocumentPool*     GetDocPool() const      { return pDocPool; }
    ScStyleSheetPool*   GetStylePool() const    { return pStylePool; }
    SvNumberFormatter*  GetFormTable() const    { return pFormTable; }
    SfxItemPool*        GetEditPool() const     { return pEditPool; }
    SfxItemPool*        GetEnginePool() const   { return pEnginePool; }
};

} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
