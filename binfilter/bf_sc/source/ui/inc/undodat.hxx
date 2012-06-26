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

#ifndef SC_UNDODAT_HXX
#define SC_UNDODAT_HXX

#include "undobase.hxx"

#include "rangeutl.hxx"     // ScArea

#include "rangelst.hxx"     // ScRangeListRef

#include "markdata.hxx"

#include "sortparam.hxx"
namespace binfilter {


class ScDocShell;
class ScDocument;
class ScOutlineTable;
class ScRangeName;
class ScDBData;
class ScDBCollection;
class ScPivot;
class ScDPObject;

//----------------------------------------------------------------------------



















class ScUndoDBData: public ScSimpleUndo
{
public:
                    ScUndoDBData( ScDocShell* pNewDocShell,
                            ScDBCollection* pNewUndoColl, ScDBCollection* pNewRedoColl );
    virtual         ~ScUndoDBData();

    virtual BOOL    CanRepeat(SfxRepeatTarget& rTarget) const;

    virtual String  GetComment() const;

private:
    ScDBCollection* pUndoColl;
    ScDBCollection* pRedoColl;
};












class ScUndoChartData: public ScSimpleUndo
{
public:
                        ScUndoChartData( ScDocShell* pNewDocShell,
                                const String& rName, const ScRange& rNew,
                                BOOL bColHdr, BOOL bRowHdr, BOOL bAdd );
                        ScUndoChartData( ScDocShell* pNewDocShell,
                                const String& rName, const ScRangeListRef& rNew,
                                BOOL bColHdr, BOOL bRowHdr, BOOL bAdd );
    virtual             ~ScUndoChartData();



private:
    String              aChartName;
    ScRangeListRef      aOldRangeListRef;
    BOOL                bOldColHeaders;
    BOOL                bOldRowHeaders;
//  ScRange             aNewRange;
    ScRangeListRef      aNewRangeListRef;
    BOOL                bNewColHeaders;
    BOOL                bNewRowHeaders;
    BOOL                bAddRange;

};




} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
