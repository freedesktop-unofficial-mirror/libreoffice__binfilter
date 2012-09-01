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

#ifndef _SCH_SCHVIEW_HXX
#define _SCH_SCHVIEW_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_svx/svdedxv.hxx>
#include <bf_svx/view3d.hxx>
#include <bf_svx/svdpage.hxx>

#include "chtmodel.hxx"
#include "docshell.hxx"

class Graphic;

namespace binfilter {

class SchViewShell;
class SchPage;
class SchWindow;
class ChartModel;
class SchDragServerRef;
class E3dScene;

}

namespace binfilter {

/*************************************************************************
|*
|* View
|*
\************************************************************************/

class SchView : public E3dView
{
 protected:
    ChartModel*   pDoc;
    SchChartDocShell*   pDocSh;
    SchViewShell*       pViewSh;
    BOOL                bDragActive;
    USHORT              nLogicalMarked;
    USHORT              nLogicalEntered;

    Timer aTimer;
    void             Construct();
    void                SetMarkHandles();

 public:

    DECL_LINK(NotifySelection,void*);

    SchView(SchChartDocShell* pDocSh, OutputDevice* pOutDev, SchViewShell* pShell);
    virtual ~SchView();

    ChartModel& GetDoc() const { return *pDoc; }


    // clipboard / drag and drop methods using XTransferable

    void UpdateSelectionClipboard( BOOL bForceDeselect );


    BOOL IsActive() const { return bDragActive; }



    virtual void MarkListHasChanged();


    bool    IsLogicalGroupMarked() { return (nLogicalMarked != 0); }
    bool    IsLogicalGroupEntered() { return (nLogicalEntered != 0); }

    SchChartDocShell* GetDocShell() const { return pDocSh; }

    // drag and drop

    virtual void Notify( SfxBroadcaster& rBC, const SfxHint& rHint );
};

}
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
