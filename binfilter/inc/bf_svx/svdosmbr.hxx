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

#ifndef _SVDOSMBR_HXX
#define _SVDOSMBR_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_svtools/brwbox.hxx>
#include <vcl/timer.hxx>
#include <vcl/floatwin.hxx>
#include <vcl/menu.hxx>
namespace binfilter {

class BrowserMouseEvent;
class UShortCont;
class SdrObject;
class SdrObjSmartData;
class SdrSmartValueField;
class ImpLineDescription;
class ImpBrowseCursor;
class SdrSmartGeometric;
class SdrSmartGeometricLine;
class SdrSmartDraftLine;
class SdrSmartGluePoint;
class SdrSmartDragPoint;

#if _SOLAR__PRIVATE
enum SmartGroupKind {GROUP_POSSIZE,
                     GROUP_DRAFT,
                     GROUP_VARS,
                     GROUP_GLUE,
                     GROUP_DRAG,
                     GROUP_MISC,
                     GROUP_GEOMETRIC0,
                     GROUP_GEOMETRIC1,
                     GROUP_GEOMETRIC2/*,...*/};
#endif

#define SMARTOBJBROWSER_GROUPCOUNT 6 /* zzgl. der Geometrien */

class _SdrSmartObjBrowserControl: public BrowseBox {
friend class ImpSmartEdit;
friend class SdrSmartObjBrowser;
    bool            bGroupExpanded[SMARTOBJBROWSER_GROUPCOUNT];
    UShortCont*         pExpandedGeo;
    SdrObject*          pObj;
    SdrObjSmartData*    pSmartData;
    ImpLineDescription* pAktPaintRow;
    SdrSmartValueField* pAktChangeEntry;
    ImpSmartEdit*       pEditControl;
    Link                aEntryChangedHdl;
    Link                aSelectHdl;
    Timer               aBrAfterPaintTimer;
    ImpBrowseCursor*    pCursor;
    ULONG               nLastLineAnz;
    bool            bCursorVisible;
    bool            bShowValues;
    ULONG               nTipId;
    long                mnCurRow;
    USHORT              mnCurColId;
private:
#if _SOLAR__PRIVATE
    void     ImpCtor();
    void     ImpForceSmartData() const;
    ULONG    ImpGetGroupCount() const;
    ULONG    ImpGetGroupLineCount(SmartGroupKind eGroup, bool bOneIfCollapsed) const;
    bool ImpIsGroupExpanded(SmartGroupKind eGroup) const;
    ULONG    ImpGetGroupStartLine(SmartGroupKind eGroup) const;
    void     ImpExpandGroup(SmartGroupKind eGroup, bool bExpand);
    bool ImpIsGroupValid(SmartGroupKind eGroup) const;
    void     ImpForceExpandedGeo() const;
    bool ImpLineNumToDescription(ULONG nRow, ImpLineDescription& rLine) const;
    SdrSmartValueField* ImpGetValueField(const ImpLineDescription rLine, USHORT nColumnId) const;
    XubString ImpGetFixedFieldText(const ImpLineDescription rLine, USHORT nColumnId) const;
    void     ImpShowCursor(const ImpLineDescription rLine, USHORT nColumnId);
    void     ImpHideCursor(const ImpLineDescription rLine, USHORT nColumnId);
    void     ImpShowCursor();
    void     ImpHideCursor();
    void     ImpRepaintRows(ULONG nStart, ULONG nEnd);

    DECL_LINK( ImpAfterPaintHdl,Timer* );
    DECL_LINK( MenuSelectHdl, Menu* );

    bool ImpInsertLine(SmartGroupKind eGroup, ULONG nLn);
#endif // __PRIVATE
protected:
    virtual long GetRowCount() const;
    virtual BOOL SeekRow(long nRow);
    virtual void PaintField(OutputDevice& rDev, const Rectangle& rRect, USHORT nColumnId) const;
    virtual void DoubleClick(const BrowserMouseEvent& rEvt);
    virtual void KeyInput(const KeyEvent& rEvt);
    virtual void MouseButtonDown(const BrowserMouseEvent& rEvt);
    virtual void MouseMove(const BrowserMouseEvent& rEvt);
    virtual void MouseButtonUp(const BrowserMouseEvent& rEvt);
    virtual BOOL IsCursorMoveAllowed(long nNewRow, USHORT nNewColId) const;
    virtual void Select();

    long         GetCurRow() const;
    USHORT       GetCurColumnId() const;
    void         SeekPossibleField( BOOL bNext = TRUE );
public:
    _SdrSmartObjBrowserControl(Window* pParent, WinBits nBits=WB_SVLOOK|WB_BORDER|WB_TABSTOP|WB_CLIPCHILDREN);
    virtual ~_SdrSmartObjBrowserControl();
            bool IsChangeEntry() const          { return pEditControl!=NULL; }
    virtual bool BegChangeEntry(SdrSmartValueField* pField);
    virtual bool EndChangeEntry();
    virtual void     BrkChangeEntry();

    /** GetCellText returns the text at the given position
        @param  _nRow
            the number of the row
        @param  _nColId
            the ID of the column
        @return
            the text out of the cell
    */
    virtual String  GetCellText(long _nRow, USHORT _nColId) const;

    SdrObject* GetObject() const                    { return pObj; }
    void       SetObject(SdrObject* pObj);
//  String GetNewEntryValue() const                 { return ((Edit*)pEditControl)->GetText(); }
    void SetEntryChangedHdl(const Link& rLink)      { aEntryChangedHdl=rLink; }
    const Link& GetEntryChangedHdl() const          { return aEntryChangedHdl; }
    void SetSelectHdl(const Link& rLink)            { aSelectHdl=rLink; }
    const Link& GetSelectHdl() const                { return aSelectHdl; }
    void SeekGeometricLine(const SdrSmartGeometricLine* pLine);
    void SeekDraftLine(const SdrSmartDraftLine* pDraft);
    void SeekVarsLine(const SdrSmartDraftLine* pVars);
    void SeekGluePoint(const SdrSmartGluePoint* pGlue);
    void SeekDragPoint(const SdrSmartDragPoint* pDrag);
    SdrSmartGeometric*     InsertGeometric(ULONG nPos);
    SdrSmartGeometricLine* InsertGeoLine(ULONG nGeoNum, ULONG nPos=CONTAINER_APPEND);
    SdrSmartDraftLine*     InsertDraftLine(ULONG nPos=CONTAINER_APPEND);
    SdrSmartDraftLine*     InsertVarsLine(ULONG nPos=CONTAINER_APPEND);
    SdrSmartGluePoint*     InsertGluePoint(ULONG nPos=CONTAINER_APPEND);
    SdrSmartDragPoint*     InsertDragPoint(ULONG nPos=CONTAINER_APPEND);
    bool DeleteGeometric(ULONG nPos);
    bool DeleteGeoLine(ULONG nGeoNum, ULONG nPos);
    bool DeleteDraftLine(ULONG nPos);
    bool DeleteVarsLine(ULONG nPos);
    bool DeleteGluePoint(ULONG nPos);
    bool DeleteDragPoint(ULONG nPos);
    bool InsertGeometricPossible() const;
    bool AppendGeometricPossible() const;
    bool DeleteGeometricPossible() const;
    bool InsertGeometric();
    bool AppendGeometric();
    bool DeleteGeometric();
    bool InsertLinePossible() const;
    bool AppendLinePossible() const;
    bool DeleteLinePossible() const;
    bool InsertLine();
    bool AppendLine();
    bool DeleteLine();
};

#define WB_STDSIZEABLEDOCKWIN  (WB_STDDOCKWIN|WB_SVLOOK|WB_CLOSEABLE|WB_SIZEMOVE|WB_MINMAX|WB_CLIPCHILDREN)
#define WB_STDSIZEABLEFLOATWIN (WB_STDFLOATWIN|WB_SVLOOK|WB_CLOSEABLE|WB_SIZEMOVE|WB_MINMAX|WB_CLIPCHILDREN)

class _SdrSmartObjBrowserWindow: public FloatingWindow {
    _SdrSmartObjBrowserControl aBrowse;
public:
    _SdrSmartObjBrowserWindow(Window* pParent, WinBits nBits=WB_STDSIZEABLEDOCKWIN);
    virtual ~_SdrSmartObjBrowserWindow();
    virtual void Resize();
    virtual void GetFocus();
    void Clear()                                            { aBrowse.Clear(); }
    void SetFloatingMode(bool bOn) {}
    const _SdrSmartObjBrowserControl& GetBrowserControl() const { return aBrowse; }
    _SdrSmartObjBrowserControl& GetBrowserControl()             { return aBrowse; }
};

class SdrView;

class SdrSmartObjBrowser: public _SdrSmartObjBrowserWindow {
    Timer aIdleTimer;
    SdrView* pView;
    bool bFixedObj;
    bool bDirty;
private:
    static Window* ImpGetViewWin(SdrView& rView);
    DECL_LINK(IdleHdl,Timer*);
    DECL_LINK(ChangedHdl,_SdrSmartObjBrowserControl*);
    DECL_LINK(SelectHdl,_SdrSmartObjBrowserControl*);
public:
    SdrSmartObjBrowser(SdrView& rView);
    void ForceParent();
    void SetView(SdrView& rView) { pView=&rView; ForceParent(); SetDirty(); }
    void SetDirty();
    void Undirty();
    void ForceUndirty() { if (bDirty) Undirty(); }
};

}//end of namespace binfilter
#endif //_SVDOSMBR_HXX


/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
