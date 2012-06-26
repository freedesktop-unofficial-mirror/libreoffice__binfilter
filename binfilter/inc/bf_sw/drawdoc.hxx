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
#ifndef _DRAWDOC_HXX
#define _DRAWDOC_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_svx/fmmodel.hxx>
class Window;
class SbxValue;
class SbxObject;
namespace binfilter {

class SwDoc;
class SwDocShell;
class SjJSbxObject;


//==================================================================

class SwDrawDocument : public FmFormModel
{
    SwDoc* pDoc;
public:
    SwDrawDocument( SwDoc* pDoc );
    SwDrawDocument( SfxItemPool *pPool, SwDocShell *pDocSh );
    ~SwDrawDocument();

    const SwDoc& GetDoc() const { return *pDoc; }
          SwDoc& GetDoc()       { return *pDoc; }

    virtual SdrPage* AllocPage(bool bMasterPage);

    // fuers "load on demand" von Grafiken im DrawingLayer
    virtual SvStream* GetDocumentStream( SdrDocumentStreamInfo& rInfo ) const;

    // fuers Speicher von Rechtecken als Control-Ersatz fuker Versionen < 5.0
};


} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
