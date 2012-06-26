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

#ifndef SC_UNDOCELL_HXX
#define SC_UNDOCELL_HXX

#include "undobase.hxx"
namespace binfilter {

class ScDocShell;
class ScBaseCell;
class ScPatternAttr;
class EditTextObject;
class SdrUndoAction;
class ScDetOpList;
class ScDetOpData;
class ScRangeName;

//----------------------------------------------------------------------------







class ScUndoPutCell: public ScSimpleUndo
{
public:
                    ScUndoPutCell( ScDocShell* pNewDocShell,
                            const ScAddress& rNewPos,
                            ScBaseCell* pUndoCell, ScBaseCell* pRedoCell, BOOL bHeight );
    virtual         ~ScUndoPutCell();

    virtual BOOL    CanRepeat(SfxRepeatTarget& rTarget) const;

    virtual String  GetComment() const;

private:
    ScAddress       aPos;
    ScBaseCell*     pOldCell;
    ScBaseCell*     pEnteredCell;
    ULONG           nEndChangeAction;
    BOOL            bNeedHeight;

    void            SetChangeTrack();
};






class ScUndoNote: public ScSimpleUndo
{
public:
                    ScUndoNote( ScDocShell* pNewDocShell,
                                BOOL bShow, const ScAddress& rNewPos,
                                SdrUndoAction* pDraw );
    virtual         ~ScUndoNote();



private:
    BOOL            bIsShow;
    ScAddress       aPos;
    SdrUndoAction*  pDrawUndo;
};






class ScUndoRangeNames: public ScSimpleUndo
{
public:
                    ScUndoRangeNames( ScDocShell* pNewDocShell,
                                        ScRangeName* pOld, ScRangeName* pNew );
    virtual         ~ScUndoRangeNames();

    virtual BOOL    CanRepeat(SfxRepeatTarget& rTarget) const;

    virtual String  GetComment() const;

private:
    ScRangeName*    pOldRanges;
    ScRangeName*    pNewRanges;

};



} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
