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

#ifndef SC_DOCFUNC_HXX
#define SC_DOCFUNC_HXX

#include <tools/link.hxx>

#include "global.hxx"
namespace binfilter {

class SfxUndoAction;
class EditEngine;
class ScAddress;
class ScDocShell;
class ScMarkData;
class ScPatternAttr;
class ScRange;
class ScRangeName;
class ScBaseCell;
struct ScTabOpParam;


// ---------------------------------------------------------------------------

class ScDocFunc
{
private:
    ScDocShell&     rDocShell;

    BOOL            AdjustRowHeight( const ScRange& rRange, BOOL bPaint = TRUE );
    void            CreateOneName( ScRangeName& rList,
                                    USHORT nPosX, USHORT nPosY, USHORT nTab,
                                    USHORT nX1, USHORT nY1, USHORT nX2, USHORT nY2,
                                    BOOL& rCancel, BOOL bApi );
    void            NotifyInputHandler( const ScAddress& rPos );

public:
                    ScDocFunc( ScDocShell& rDocSh ): rDocShell(rDocSh) {}
                    ~ScDocFunc() {}

    DECL_LINK( NotifyDrawUndo, SfxUndoAction* );

    BOOL            DetectiveAddPred(const ScAddress& rPos);
    BOOL            DetectiveDelPred(const ScAddress& rPos);
    BOOL            DetectiveDelSucc(const ScAddress& rPos);
    BOOL            DetectiveAddError(const ScAddress& rPos);
    BOOL            DetectiveMarkInvalid(USHORT nTab);
    BOOL            DetectiveDelAll(USHORT nTab);
    BOOL            DetectiveRefresh();

    BOOL            DeleteContents( const ScMarkData& rMark, USHORT nFlags,
                                    BOOL bRecord, BOOL bApi );


     BOOL           SetNormalString( const ScAddress& rPos, const String& rText, BOOL bApi );
    BOOL            PutCell( const ScAddress& rPos, ScBaseCell* pNewCell, BOOL bApi );
    BOOL            PutData( const ScAddress& rPos, EditEngine& rEngine,
                                BOOL bInterpret, BOOL bApi );
    BOOL            SetCellText( const ScAddress& rPos, const String& rText,
                                    BOOL bInterpret, BOOL bEnglish, BOOL bApi );

                    // creates a new cell for use with PutCell
    ScBaseCell*     InterpretEnglishString( const ScAddress& rPos, const String& rText );

    BOOL            SetNoteText( const ScAddress& rPos, const String& rText, BOOL bApi );

    BOOL            ApplyAttributes( const ScMarkData& rMark, const ScPatternAttr& rPattern,
                                    BOOL bRecord, BOOL bApi );
    BOOL            ApplyStyle( const ScMarkData& rMark, const String& rStyleName,
                                    BOOL bRecord, BOOL bApi );

    BOOL            InsertTable( USHORT nTab, const String& rName, BOOL bRecord, BOOL bApi );
    BOOL            RenameTable( USHORT nTab, const String& rName, BOOL bRecord, BOOL bApi );

    BOOL            SetTableVisible( USHORT nTab, BOOL bVisible, BOOL bApi );

    BOOL            SetWidthOrHeight( BOOL bWidth, USHORT nRangeCnt, USHORT* pRanges,
                                    USHORT nTab, ScSizeMode eMode, USHORT nSizeTwips,
                                    BOOL bRecord, BOOL bApi );

    BOOL            RemovePageBreak( BOOL bColumn, const ScAddress& rPos,
                                    BOOL bRecord, BOOL bSetModified );

    BOOL            Protect( USHORT nTab, const String& rPassword, BOOL bApi );
    BOOL            Unprotect( USHORT nTab, const String& rPassword, BOOL bApi );

    BOOL            ClearItems( const ScMarkData& rMark, const USHORT* pWhich, BOOL bApi );
    BOOL            ChangeIndent( const ScMarkData& rMark, BOOL bIncrement, BOOL bApi );
    BOOL            AutoFormat( const ScRange& rRange, const ScMarkData* pTabMark,
                                    USHORT nFormatNo, BOOL bRecord, BOOL bApi );

    BOOL            EnterMatrix( const ScRange& rRange, const ScMarkData* pTabMark,
                                    const String& rString, BOOL bApi, BOOL bEnglish );

    BOOL            MergeCells( const ScRange& rRange, BOOL bContents,
                                BOOL bRecord, BOOL bApi );

    BOOL            ModifyRangeNames( const ScRangeName& rNewRanges );

    BOOL            CreateNames( const ScRange& rRange, USHORT nFlags, BOOL bApi );
    BOOL            InsertNameList( const ScAddress& rStartPos, BOOL bApi );

    BOOL            InsertAreaLink( const String& rFile, const String& rFilter,
                                    const String& rOptions, const String& rSource,
                                    const ScRange& rDestRange, ULONG nRefresh,
                                    BOOL bFitBlock );
};



} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
