/*************************************************************************
 *
 *  $RCSfile: olinewin.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:18:28 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/

#ifndef SC_OLINEWIN_HXX
#define SC_OLINEWIN_HXX

#ifndef SC_VIEWDATA_HXX
#include "viewdata.hxx"
#endif

//STRIP001 class ScOutlineEntry;
class ScOutlineArray;
//STRIP001 class ScOutlineTable;


// ============================================================================

enum ScOutlineMode { SC_OUTLINE_HOR, SC_OUTLINE_VER };


// ----------------------------------------------------------------------------

/** The window left of or above the spreadsheet containing the outline groups
    and controls to expand/collapse them. */
class ScOutlineWindow : public Window
{
private:
    ScViewData&                 mrViewData;         /// View data containing the document.
    ScSplitPos                  meWhich;            /// Which area in split window.
    bool                        mbHoriz;            /// true = Horizontal orientation.
    bool                        mbMirrorHdr;        /// true = Header at end of the window (bottom or right).

    ImageList*                  mpSymbols;          /// Symbols for buttons.
    Color                       maLineColor;        /// Line color for expanded groups.
    sal_Int32                   mnHeaderSize;       /// Size of the header area in entry direction.
    sal_Int32                   mnHeaderPos;        /// Position of the header area in entry direction.
    sal_Int32                   mnMainFirstPos;     /// First position of main area in entry direction.
    sal_Int32                   mnMainLastPos;      /// Last position of main area in entry direction.

    sal_uInt16                  mnMTLevel;          /// Mouse tracking: Level of active button.
    sal_uInt16                  mnMTEntry;          /// Mouse tracking: Entry index of active button.
    bool                        mbMTActive;         /// Mouse tracking active?
    bool                        mbMTPressed;        /// Mouse tracking: Button currently drawed pressed?

    Rectangle                   maFocusRect;        /// Focus rectangle on screen.
    sal_uInt16                  mnFocusLevel;       /// Level of focused button.
    sal_uInt16                  mnFocusEntry;       /// Entry index of focused button.
    bool                        mbDontDrawFocus;    /// Do not redraw focus in next Paint().

public:
                                ScOutlineWindow(
                                    Window* pParent,
                                    ScOutlineMode eMode,
                                    ScViewData* pViewData,
                                    ScSplitPos eWhich );
    virtual                     ~ScOutlineWindow();

    /** Sets the size of the header area (width/height dep. on window type). */
    void                        SetHeaderSize( sal_Int32 nNewSize );
    /** Returns the width/height the window needs to show all levels. */
    sal_Int32                   GetDepthSize() const;

//STRIP001     /** Scrolls the window content by the specified amount of pixels. */
//STRIP001     void                        ScrollPixel( sal_Int32 nDiff );

private:
    /** Initializes color and image settings. */
    void                        InitSettings();

//STRIP001     /** Returns the calc document. */
//STRIP001     inline ScDocument&          GetDoc() const { return *mrViewData.GetDocument(); }
//STRIP001     /** Returns the current sheet index. */
//STRIP001     inline sal_uInt16           GetTab() const { return mrViewData.GetTabNo(); }
//STRIP001     /** Returns the outline array of the corresponding document. */
//STRIP001     const ScOutlineArray*       GetOutlineArray() const;
//STRIP001     /** Returns the specified outline entry. */
//STRIP001     const ScOutlineEntry*       GetOutlineEntry( sal_uInt16 nLevel, sal_uInt16 nEntry ) const;
//STRIP001
//STRIP001     /** Returns true, if the column/row is hidden. */
//STRIP001     bool                        IsHidden( sal_uInt16 nColRowIndex ) const;
//STRIP001     /** Returns true, if the column/row is filtered. */
//STRIP001     bool                        IsFiltered( sal_uInt16 nColRowIndex ) const;
//STRIP001     /** Returns true, if all columns/rows before nColRowIndex are hidden. */
//STRIP001     bool                        IsFirstVisible( sal_uInt16 nColRowIndex ) const;
//STRIP001     /** Returns the currently visible column/row range. */
//STRIP001     void                        GetVisibleRange( sal_uInt16& rnColRowStart, sal_uInt16& rnColRowEnd ) const;
//STRIP001
//STRIP001     /** Returns the point in the window of the specified position. */
//STRIP001     Point                       GetPoint( sal_Int32 nLevelPos, sal_Int32 nEntryPos ) const;
//STRIP001     /** Returns the rectangle in the window of the specified position. */
//STRIP001     Rectangle                   GetRectangle(
//STRIP001                                     sal_Int32 nLevelStart, sal_Int32 nEntryStart,
//STRIP001                                     sal_Int32 nLevelEnd, sal_Int32 nEntryEnd ) const;
//STRIP001
//STRIP001     /** Returns the window size for the level coordinate. */
//STRIP001     sal_Int32                   GetOutputSizeLevel() const;
//STRIP001     /** Returns the window size for the entry coordinate. */
//STRIP001     sal_Int32                   GetOutputSizeEntry() const;
//STRIP001
//STRIP001     /** Returns the count of levels of the outline array. 0 means no outlines. */
//STRIP001     sal_uInt16                  GetLevelCount() const;
//STRIP001     /** Returns the pixel position of the specified level. */
//STRIP001     sal_Int32                   GetLevelPos( sal_uInt16 nLevel ) const;
//STRIP001     /** Returns the level of the passed pixel position. */
//STRIP001     sal_uInt16                  GetLevelFromPos( sal_Int32 nLevelPos ) const;
//STRIP001
//STRIP001     /** Returns the start coordinate of the specified column/row in the window. */
//STRIP001     sal_Int32                   GetColRowPos( sal_uInt16 nColRowIndex ) const;
//STRIP001     /** Returns the entry position of header images. */
//STRIP001     sal_Int32                   GetHeaderEntryPos() const;
//STRIP001     /** Calculates the coordinates the outline entry takes in the window.
//STRIP001         @return  false = no part of the group is visible (outside window or collapsed by parent group). */
//STRIP001     bool                        GetEntryPos(
//STRIP001                                     sal_uInt16 nLevel, sal_uInt16 nEntry,
//STRIP001                                     sal_Int32& rnStartPos, sal_Int32& rnEndPos, sal_Int32& rnImagePos ) const;
//STRIP001     /** Calculates the absolute position of the image of the specified outline entry.
//STRIP001         @param nLevel  The level of the entry.
//STRIP001         @param nEntry  The entry index or SC_OL_HEADERENTRY for the header image.
//STRIP001         @return  false = image is not visible. */
//STRIP001     bool                        GetImagePos( sal_uInt16 nLevel, sal_uInt16 nEntry, Point& rPos ) const;
//STRIP001     /** Returns true, if the button of the specified entry is visible in the window. */
//STRIP001     bool                        IsButtonVisible( sal_uInt16 nLevel, sal_uInt16 nEntry ) const;
//STRIP001
//STRIP001     /** Returns true, if rPos is inside of a button or over the line of an expanded
//STRIP001         group. The outline entry data is stored in the passed variables. */
//STRIP001     bool                        ItemHit( const Point& rPos, sal_uInt16& rnLevel, sal_uInt16& rnEntry, bool& rbButton ) const;
//STRIP001     /** Returns true, if rPos is inside of a button.
//STRIP001         The button data is stored in the passed variables. */
//STRIP001     bool                        ButtonHit( const Point& rPos, sal_uInt16& rnLevel, sal_uInt16& rnEntry ) const;
//STRIP001     /** Returns true, if rPos is over the line of an expanded group.
//STRIP001         The outline entry data is stored in the passed variables. */
//STRIP001     bool                        LineHit( const Point& rPos, sal_uInt16& rnLevel, sal_uInt16& rnEntry ) const;
//STRIP001
//STRIP001     /** Performs an action with the specified item.
//STRIP001         @param nLevel  The level of the entry.
//STRIP001         @param nEntry  The entry index or SC_OL_HEADERENTRY for the header entry. */
//STRIP001     void                        DoFunction( sal_uInt16 nLevel, sal_uInt16 nEntry ) const;
//STRIP001     /** Expands the specified entry (does nothing with header entries). */
//STRIP001     void                        DoExpand( sal_uInt16 nLevel, sal_uInt16 nEntry ) const;
//STRIP001     /** Collapses the specified entry (does nothing with header entries). */
//STRIP001     void                        DoCollapse( sal_uInt16 nLevel, sal_uInt16 nEntry ) const;
//STRIP001
//STRIP001     /** Returns true, if the focused button is visible in the window. */
//STRIP001     bool                        IsFocusButtonVisible() const;
//STRIP001
//STRIP001     /** Calculates index of next/previous focus button in the current level (no paint).
//STRIP001         @param bFindVisible  true = repeats until a visible button has been found.
//STRIP001         @return  true = focus wrapped from end to start or vice versa. */
//STRIP001     bool                        ImplMoveFocusByEntry( bool bForward, bool bFindVisible );
//STRIP001     /** Calculates position of focus button in next/previous level (no paint).
//STRIP001         @return  true = focus wrapped from end to start or vice versa. */
//STRIP001     bool                        ImplMoveFocusByLevel( bool bForward );
//STRIP001     /** Calculates position of focus button in tab order.
//STRIP001         @param bFindVisible  true = repeats until a visible button has been found.
//STRIP001         @return  true = focus wrapped from end to start or vice versa. */
//STRIP001     bool                        ImplMoveFocusByTabOrder( bool bForward, bool bFindVisible );
//STRIP001
//STRIP001     /** If the focused entry is invisible, tries to move to visible position. */
//STRIP001     void                        ImplMoveFocusToVisible( bool bForward );
//STRIP001
//STRIP001     /** Focuses next/previous button in the current level. */
//STRIP001     void                        MoveFocusByEntry( bool bForward );
//STRIP001     /** Focuses button in next/previous level. */
//STRIP001     void                        MoveFocusByLevel( bool bForward );
//STRIP001     /** Focuses next/previous button in tab order. */
//STRIP001     void                        MoveFocusByTabOrder( bool bForward );
//STRIP001
//STRIP001     /** Starts mouse tracking after click on a button. */
//STRIP001     void                        StartMouseTracking( sal_uInt16 nLevel, sal_uInt16 nEntry );
//STRIP001     /** Returns whether mouse tracking mode is active. */
//STRIP001     inline bool                 IsMouseTracking() const { return mbMTActive; }
//STRIP001     /** Ends mouse tracking. */
//STRIP001     void                        EndMouseTracking();
//STRIP001
//STRIP001     /** Sets a clip region for the window area without header. */
//STRIP001     void                        SetEntryAreaClipRegion();
//STRIP001     /** Converts coordinates to real window points and draws the line. */
//STRIP001     void                        DrawLineRel(
//STRIP001                                     sal_Int32 nLevelStart, sal_Int32 nEntryStart,
//STRIP001                                     sal_Int32 nLevelEnd, sal_Int32 nEntryEnd );
//STRIP001     /** Converts coordinates to real window points and draws the rectangle. */
//STRIP001     void                        DrawRectRel(
//STRIP001                                     sal_Int32 nLevelStart, sal_Int32 nEntryStart,
//STRIP001                                     sal_Int32 nLevelEnd, sal_Int32 nEntryEnd );
//STRIP001     /** Draws the specified image unpressed. */
//STRIP001     void                        DrawImageRel( sal_Int32 nLevelPos, sal_Int32 nEntryPos, sal_uInt16 nId );
//STRIP001     /** Draws a pressed or unpressed border. */
//STRIP001     void                        DrawBorder( const Point& rPos, bool bPressed );
//STRIP001     /** Draws a pressed or unpressed border. */
//STRIP001     void                        DrawBorderRel( sal_uInt16 nLevel, sal_uInt16 nEntry, bool bPressed );
//STRIP001
//STRIP001     /** Draws the focus rectangle into the focused button. */
//STRIP001     void                        ShowFocus();
//STRIP001     /** Erases the focus rectangle from the focused button. */
//STRIP001     void                        HideFocus();
//STRIP001
//STRIP001     /** Scrolls the window in entry-relative direction. */
//STRIP001     void                        ScrollRel( sal_Int32 nEntryDiff );
//STRIP001     /** Scrolls the specified range of the window in entry-relative direction. */
//STRIP001     void                        ScrollRel( sal_Int32 nEntryDiff, sal_Int32 nEntryStart, sal_Int32 nEntryEnd );
//STRIP001
//STRIP001 protected:
//STRIP001     virtual void                Paint( const Rectangle& rRect );
//STRIP001
//STRIP001     virtual void                Resize();
//STRIP001     virtual void                GetFocus();
//STRIP001     virtual void                LoseFocus();
//STRIP001
//STRIP001     virtual void                MouseMove( const MouseEvent& rMEvt );
//STRIP001     virtual void                MouseButtonUp( const MouseEvent& rMEvt );
//STRIP001     virtual void                MouseButtonDown( const MouseEvent& rMEvt );
//STRIP001
//STRIP001     virtual void                KeyInput( const KeyEvent& rKEvt );
//STRIP001
//STRIP001 public:
//STRIP001     virtual void                DataChanged( const DataChangedEvent& rDCEvt );
};


// ============================================================================

#endif

