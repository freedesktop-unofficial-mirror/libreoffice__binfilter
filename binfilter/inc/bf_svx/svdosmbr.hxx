/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svdosmbr.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: ihi $ $Date: 2007-07-11 13:01:39 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/

#ifndef _SVDOSMBR_HXX
#define _SVDOSMBR_HXX

#ifndef _SVX_BRWBOX_HXX //autogen
#include <svtools/brwbox.hxx>
#endif
#ifndef _SV_TIMER_HXX //autogen
#include <vcl/timer.hxx>
#endif
#ifndef _SV_FLOATWIN_HXX //autogen
#include <vcl/floatwin.hxx>
#endif
#ifndef _SV_MENU_HXX //autogen
#include <vcl/menu.hxx>
#endif
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
    FASTBOOL            bGroupExpanded[SMARTOBJBROWSER_GROUPCOUNT];
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
    FASTBOOL            bCursorVisible;
    FASTBOOL            bShowValues;
    ULONG               nTipId;
    long                mnCurRow;
    USHORT              mnCurColId;
private:
#if _SOLAR__PRIVATE
    void     ImpCtor();
    void     ImpForceSmartData() const;
    ULONG    ImpGetGroupCount() const;
    ULONG    ImpGetGroupLineCount(SmartGroupKind eGroup, FASTBOOL bOneIfCollapsed) const;
    FASTBOOL ImpIsGroupExpanded(SmartGroupKind eGroup) const;
    ULONG    ImpGetGroupStartLine(SmartGroupKind eGroup) const;
    void     ImpExpandGroup(SmartGroupKind eGroup, FASTBOOL bExpand);
    FASTBOOL ImpIsGroupValid(SmartGroupKind eGroup) const;
    void     ImpForceExpandedGeo() const;
    FASTBOOL ImpLineNumToDescription(ULONG nRow, ImpLineDescription& rLine) const;
    SdrSmartValueField* ImpGetValueField(const ImpLineDescription rLine, USHORT nColumnId) const;
    XubString ImpGetFixedFieldText(const ImpLineDescription rLine, USHORT nColumnId) const;
    void     ImpShowCursor(const ImpLineDescription rLine, USHORT nColumnId);
    void     ImpHideCursor(const ImpLineDescription rLine, USHORT nColumnId);
    void     ImpShowCursor();
    void     ImpHideCursor();
    void     ImpRepaintRows(ULONG nStart, ULONG nEnd);

    DECL_LINK( ImpAfterPaintHdl,Timer* );
    DECL_LINK( MenuSelectHdl, Menu* );

    FASTBOOL ImpInsertLine(SmartGroupKind eGroup, ULONG nLn);
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
            FASTBOOL IsChangeEntry() const          { return pEditControl!=NULL; }
    virtual FASTBOOL BegChangeEntry(SdrSmartValueField* pField);
    virtual FASTBOOL EndChangeEntry();
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
    FASTBOOL DeleteGeometric(ULONG nPos);
    FASTBOOL DeleteGeoLine(ULONG nGeoNum, ULONG nPos);
    FASTBOOL DeleteDraftLine(ULONG nPos);
    FASTBOOL DeleteVarsLine(ULONG nPos);
    FASTBOOL DeleteGluePoint(ULONG nPos);
    FASTBOOL DeleteDragPoint(ULONG nPos);
    FASTBOOL InsertGeometricPossible() const;
    FASTBOOL AppendGeometricPossible() const;
    FASTBOOL DeleteGeometricPossible() const;
    FASTBOOL InsertGeometric();
    FASTBOOL AppendGeometric();
    FASTBOOL DeleteGeometric();
    FASTBOOL InsertLinePossible() const;
    FASTBOOL AppendLinePossible() const;
    FASTBOOL DeleteLinePossible() const;
    FASTBOOL InsertLine();
    FASTBOOL AppendLine();
    FASTBOOL DeleteLine();
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
    void SetFloatingMode(FASTBOOL bOn) {}
    const _SdrSmartObjBrowserControl& GetBrowserControl() const { return aBrowse; }
    _SdrSmartObjBrowserControl& GetBrowserControl()             { return aBrowse; }
};

class SdrView;

class SdrSmartObjBrowser: public _SdrSmartObjBrowserWindow {
    Timer aIdleTimer;
    SdrView* pView;
    FASTBOOL bFixedObj;
    FASTBOOL bDirty;
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


