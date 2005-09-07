/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: csvgrid.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 19:39:26 $
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

// ============================================================================

#ifndef _SC_CSVGRID_HXX
#define _SC_CSVGRID_HXX

#ifndef _SV_VIRDEV_HXX
#include <vcl/virdev.hxx>
#endif
#ifndef _MENU_HXX
#include <vcl/menu.hxx>
#endif
#ifndef _SFXLSTNER_HXX
#include <svtools/lstner.hxx>
#endif

#include <vector>
#include <memory>

#ifndef _SC_CSVCONTROL_HXX
#include "csvcontrol.hxx"
#endif
#ifndef _SC_CSVSPLITS_HXX
#include "csvsplits.hxx"
#endif
namespace svtools { class ColorConfig; }
namespace binfilter {


// ----------------------------------------------------------------------------

//STRIP008 namespace svtools { class ColorConfig; }
class EditEngine;
class ScEditEngineDefaulter;
class ScAsciiOptions;
class ScAccessibleCsvControl;


// ============================================================================

const sal_uInt8 CSV_COLFLAG_NONE    = 0x00;         /// Nothing set.
const sal_uInt8 CSV_COLFLAG_SELECT  = 0x01;         /// Column is selected.

const sal_uInt32 CSV_COLUMN_INVALID = CSV_VEC_NOTFOUND;


// ----------------------------------------------------------------------------

/** This struct contains the state of one table column. */
struct ScCsvColState
{
    sal_Int32                   mnType;             /// Data type.
    sal_uInt8                   mnFlags;            /// Flags (i.e. selection state).

    inline explicit             ScCsvColState(
                                        sal_Int32 nType = CSV_TYPE_DEFAULT,
                                        sal_uInt8 nFlags = CSV_COLFLAG_NONE ) :
                                    mnType( nType ), mnFlags( nFlags ) {}

    inline bool                 IsSelected() const;
    inline void                 Select( bool bSel );
};

inline bool ScCsvColState::IsSelected() const
{
    return (mnFlags & CSV_COLFLAG_SELECT) != 0;
}

inline void ScCsvColState::Select( bool bSel )
{
    if( bSel ) mnFlags |= CSV_COLFLAG_SELECT; else mnFlags &= ~CSV_COLFLAG_SELECT;
}


// ----------------------------------------------------------------------------

typedef ::std::vector< ScCsvColState > ScCsvColStateVec;


// ============================================================================

/** A data grid control for the CSV import dialog. The design of this control
    simulates a Calc spreadsheet with row and column headers. */
class ScCsvGrid : public ScCsvControl, public SfxListener
{
private:
    typedef ::std::auto_ptr< ScEditEngineDefaulter > ScEditEnginePtr;

    VirtualDevice               maBackgrDev;        /// Grid background, headers, cell texts.
    VirtualDevice               maGridDev;          /// Data grid with selection and cursor.
    PopupMenu                   maPopup;            /// Popup menu for column types.

    ::svtools::ColorConfig&     mrColorConfig;      /// Application color configuration.
    Color                       maBackColor;        /// Cell background color.
    Color                       maGridColor;        /// Table grid color.
    Color                       maGridPBColor;      /// Grid color for "first imported line" delimiter.
    Color                       maAppBackColor;     /// Background color for unused area.
    Color                       maTextColor;        /// Text color for data area.
    Color                       maHeaderBackColor;  /// Background color for headers.
    Color                       maHeaderGridColor;  /// Grid color for headers.
    Color                       maHeaderTextColor;  /// Text color for headers.
    Color                       maSelectColor;      /// Header color of selected columns.

    ScEditEnginePtr             mpEditEngine;       /// For drawing cell texts.
    Font                        maHeaderFont;       /// Font for column and row headers.
    Font                        maMonoFont;         /// Monospace font for data cells.
    Size                        maWinSize;          /// Size of the control.
    Size                        maEdEngSize;        /// Paper size for edit engine.

    ScCsvSplits                 maSplits;           /// Vector with split positions.
    ScCsvColStateVec            maColStates;        /// State of each column.
    StringVec                   maTypeNames;        /// UI names of data types.
    StringVecVec                maTexts;            /// 2D-vector for cell texts.

    sal_Int32                   mnFirstImpLine;     /// First imported line (0-based).
    sal_uInt32                  mnRecentSelCol;     /// Index of most recently selected column.
    sal_uInt32                  mnMTCurrCol;        /// Current column of mouse tracking.
    bool                        mbMTSelecting;      /// Mouse tracking: true = select, false = deselect.

    // ------------------------------------------------------------------------
public:
    explicit                    ScCsvGrid( ScCsvControl& rParent );
    virtual                     ~ScCsvGrid();

    // common grid handling ---------------------------------------------------
//STRIP001 public:
//STRIP001     /** Updates layout data dependent from the control's state. */
//STRIP001     void                        UpdateLayoutData();
//STRIP001     /** Updates X coordinate of first visible position dependent from line numbers. */
//STRIP001     void                        UpdateOffsetX();
//STRIP001     /** Apply current layout data to the grid control. */
//STRIP001     void                        ApplyLayout( const ScCsvLayoutData& rOldData );
//STRIP001     /** Sets the number of the first imported line (for visual feedback). nLine is 0-based! */
//STRIP001     void                        SetFirstImportedLine( sal_Int32 nLine );
//STRIP001
//STRIP001     /** Finds a column position nearest to nPos which does not cause scrolling the visible area. */
//STRIP001     sal_Int32                   GetNoScrollCol( sal_Int32 nPos ) const;
//STRIP001
//STRIP001 private:
//STRIP001     /** Reads colors from system settings. */
//STRIP001     void                        InitColors();
//STRIP001     /** Initializes all font settings. */
//STRIP001     void                        InitFonts();
//STRIP001     /** Initializes all data dependent from the control's size. */
//STRIP001     void                        InitSizeData();
//STRIP001
//STRIP001     // split handling ---------------------------------------------------------
//STRIP001 public:
//STRIP001     /** Inserts a split. */
//STRIP001     void                        InsertSplit( sal_Int32 nPos );
//STRIP001     /** Removes a split. */
//STRIP001     void                        RemoveSplit( sal_Int32 nPos );
//STRIP001     /** Inserts a new or removes an existing split. */
//STRIP001     void                        MoveSplit( sal_Int32 nPos, sal_Int32 nNewPos );
//STRIP001     /** Removes all splits. */
//STRIP001     void                        RemoveAllSplits();
//STRIP001     /** Removes all splits and inserts the splits from rSplits. */
//STRIP001     void                        SetSplits( const ScCsvSplits& rSplits );
//STRIP001
//STRIP001 private:
//STRIP001     /** Inserts a split and adjusts column data. */
//STRIP001     bool                        ImplInsertSplit( sal_Int32 nPos );
//STRIP001     /** Removes a split and adjusts column data. */
//STRIP001     bool                        ImplRemoveSplit( sal_Int32 nPos );
//STRIP001     /** Clears the split array and re-inserts boundary splits. */
//STRIP001     void                        ImplClearSplits();
//STRIP001
//STRIP001     // columns/column types ---------------------------------------------------
//STRIP001 public:
//STRIP001     /** Returns the number of columns. */
//STRIP001     inline sal_uInt32           GetColumnCount() const { return maColStates.size(); }
//STRIP001     /** Returns the index of the first visible column. */
//STRIP001     sal_uInt32                  GetFirstVisColumn() const;
//STRIP001     /** Returns the index of the last visible column. */
//STRIP001     sal_uInt32                  GetLastVisColumn() const;
//STRIP001
//STRIP001     /** Returns true, if nColIndex points to an existing column. */
//STRIP001     bool                        IsValidColumn( sal_uInt32 nColIndex ) const;
//STRIP001     /** Returns true, if column with index nColIndex is (at least partly) visible. */
//STRIP001     bool                        IsVisibleColumn( sal_uInt32 nColIndex ) const;
//STRIP001
//STRIP001     /** Returns X coordinate of the specified column. */
//STRIP001     sal_Int32                   GetColumnX( sal_uInt32 nColIndex ) const;
//STRIP001     /** Returns column index from output coordinate. */
//STRIP001     sal_uInt32                  GetColumnFromX( sal_Int32 nX ) const;
//STRIP001
//STRIP001     /** Returns start position of the column with the specified index. */
//STRIP001     inline sal_Int32            GetColumnPos( sal_uInt32 nColIndex ) const { return maSplits[ nColIndex ]; }
//STRIP001     /** Returns column index from position. A split counts to its following column. */
//STRIP001     sal_uInt32                  GetColumnFromPos( sal_Int32 nPos ) const;
//STRIP001     /** Returns the character width of the column with the specified index. */
//STRIP001     sal_Int32                   GetColumnWidth( sal_uInt32 nColIndex ) const;
//STRIP001
//STRIP001     /** Returns the vector with the states of all columns. */
//STRIP001     inline const ScCsvColStateVec& GetColumnStates() const { return maColStates; }
//STRIP001     /** Sets all column states to the values in the passed vector. */
//STRIP001     void                        SetColumnStates( const ScCsvColStateVec& rColStates );
//STRIP001     /** Returns the data type of the selected columns. */
//STRIP001     sal_Int32                   GetSelColumnType() const;
//STRIP001     /** Changes the data type of all selected columns. */
//STRIP001     void                        SetSelColumnType( sal_Int32 nType );
//STRIP001     /** Sets new UI data type names. */
//STRIP001     void                        SetTypeNames( const StringVec& rTypeNames );
//STRIP001     /** Returns the UI type name of the specified column. */
//STRIP001     const String&               GetColumnTypeName( sal_uInt32 nColIndex ) const;
//STRIP001
//STRIP001     /** Fills the options object with column data for separators mode. */
//STRIP001     void                        FillColumnDataSep( ScAsciiOptions& rOptions ) const;
//STRIP001     /** Fills the options object with column data for fixed width mode. */
//STRIP001     void                        FillColumnDataFix( ScAsciiOptions& rOptions ) const;
//STRIP001
//STRIP001 private:
//STRIP001     /** Returns the data type of the specified column. */
//STRIP001     sal_Int32                   GetColumnType( sal_uInt32 nColIndex ) const;
//STRIP001     /** Returns the data type of the specified column. */
//STRIP001     void                        SetColumnType( sal_uInt32 nColIndex, sal_Int32 nColType );
//STRIP001
//STRIP001     /** Scrolls data grid vertically. */
//STRIP001     void                        ScrollVertRel( ScMoveMode eDir );
//STRIP001     /** Executes the data type popup menu. */
//STRIP001     void                        ExecutePopup( const Point& rPos );
//STRIP001
//STRIP001     // selection handling -----------------------------------------------------
//STRIP001 public:
//STRIP001     /** Returns true, if the specified column is selected. */
//STRIP001     bool                        IsSelected( sal_uInt32 nColIndex ) const;
//STRIP001     /** Returns index of the first selected column. */
//STRIP001     sal_uInt32                  GetFirstSelected() const;
//STRIP001     /** Returns index of the first selected column really after nFromIndex. */
//STRIP001     sal_uInt32                  GetNextSelected( sal_uInt32 nFromIndex ) const;
//STRIP001     /** Returns true, if at least one column is selected. */
//STRIP001     inline bool                 HasSelection() const { return GetFirstSelected() != CSV_COLUMN_INVALID; }
//STRIP001
//STRIP001     /** Selects or deselects the specified column. */
//STRIP001     void                        Select( sal_uInt32 nColIndex, bool bSelect = true );
//STRIP001     /** Toggles selection of the specified column. */
//STRIP001     void                        ToggleSelect( sal_uInt32 nColIndex );
//STRIP001     /** Selects or deselects the specified column range. */
//STRIP001     void                        SelectRange( sal_uInt32 nColIndex1, sal_uInt32 nColIndex2, bool bSelect = true );
//STRIP001     /** Selects or deselects all columns. */
//STRIP001     void                        SelectAll( bool bSelect = true );
//STRIP001
//STRIP001     /** Returns index of the focused column. */
//STRIP001     inline sal_uInt32           GetFocusColumn() const { return GetColumnFromPos( GetGridCursorPos() ); }
//STRIP001
//STRIP001 private:
//STRIP001     /** Moves column cursor to a new position. */
//STRIP001     void                        MoveCursor( sal_uInt32 nColIndex );
//STRIP001     /** Moves column cursor to the given direction. */
//STRIP001     void                        MoveCursorRel( ScMoveMode eDir );
//STRIP001
//STRIP001     /** Clears the entire selection without notify. */
//STRIP001     void                        ImplClearSelection();
//STRIP001
//STRIP001     /** Executes selection action for a specific column. */
//STRIP001     void                        DoSelectAction( sal_uInt32 nColIndex, sal_uInt16 nModifier );
//STRIP001
//STRIP001     // cell contents ----------------------------------------------------------
//STRIP001 public:
//STRIP001     /** Fills all cells of a line with the passed text (separators mode). */
//STRIP001     void                        ImplSetTextLineSep(
//STRIP001                                     sal_Int32 nLine, const String& rTextLine,
//STRIP001                                     const String& rSepChars, sal_Unicode cTextSep, bool bMergeSep );
//STRIP001     /** Fills all cells of a line with the passed text (fixed width mode). */
//STRIP001     void                        ImplSetTextLineFix( sal_Int32 nLine, const String& rTextLine );
//STRIP001
//STRIP001     /** Returns the text of the specified cell. */
//STRIP001     const String&               GetCellText( sal_uInt32 nColIndex, sal_Int32 nLine ) const;
//STRIP001
//STRIP001     // event handling ---------------------------------------------------------
//STRIP001 protected:
//STRIP001     virtual void                Resize();
//STRIP001     virtual void                GetFocus();
//STRIP001     virtual void                LoseFocus();
//STRIP001
//STRIP001     virtual void                MouseButtonDown( const MouseEvent& rMEvt );
//STRIP001     virtual void                Tracking( const TrackingEvent& rTEvt );
//STRIP001     virtual void                KeyInput( const KeyEvent& rKEvt );
//STRIP001     virtual void                Command( const CommandEvent& rCEvt );
//STRIP001
//STRIP001     virtual void                DataChanged( const DataChangedEvent& rDCEvt );
//STRIP001     virtual void                Notify( SfxBroadcaster& rBC, const SfxHint& rHint );
//STRIP001
//STRIP001     // painting ---------------------------------------------------------------
//STRIP001 protected:
//STRIP001     virtual void                Paint( const Rectangle& );
//STRIP001
//STRIP001 public:
//STRIP001     /** Redraws the entire data grid. */
//STRIP001     void                        ImplRedraw();
//STRIP001     /** Returns a pointer to the used edit engine. */
//STRIP001     EditEngine*                 GetEditEngine();
//STRIP001
//STRIP001 private:
//STRIP001     /** Returns the width of the control. */
//STRIP001     inline sal_Int32            GetWidth() const { return maWinSize.Width(); }
//STRIP001     /** Returns the height of the control. */
//STRIP001     inline sal_Int32            GetHeight() const { return maWinSize.Height(); }
//STRIP001
//STRIP001     /** Sets a clip region in the specified output device for the specified column. */
//STRIP001     void                        ImplSetColumnClipRegion( OutputDevice& rOutDev, sal_uInt32 nColIndex );
//STRIP001     /** Draws the header of the specified column to the specified output device. */
//STRIP001     void                        ImplDrawColumnHeader( OutputDevice& rOutDev, sal_uInt32 nColIndex, Color aFillColor );
//STRIP001
//STRIP001     /** Draws the text at the specified position to maBackgrDev. */
//STRIP001     void                        ImplDrawCellText( const Point& rPos, const String& rText );
//STRIP001     /** Draws the "first imported line" separator to maBackgrDev (or erases, if bSet is false). */
//STRIP001     void                        ImplDrawFirstLineSep( bool bSet );
//STRIP001     /** Draws the column with index nColIndex to maBackgrDev. */
//STRIP001     void                        ImplDrawColumnBackgr( sal_uInt32 nColIndex );
//STRIP001     /** Draws the row headers column to maBackgrDev. */
//STRIP001     void                        ImplDrawRowHeaders();
//STRIP001     /** Draws all columns and the row headers column to maBackgrDev. */
//STRIP001     void                        ImplDrawBackgrDev();
//STRIP001
//STRIP001     /** Draws the column with index nColIndex with its selection state to maGridDev. */
//STRIP001     void                        ImplDrawColumnSelection( sal_uInt32 nColIndex );
//STRIP001     /** Draws all columns with selection and cursor to maGridDev. */
//STRIP001     void                        ImplDrawGridDev();
//STRIP001
//STRIP001     /** Redraws the entire column (background and selection). */
//STRIP001     void                        ImplDrawColumn( sal_uInt32 nColIndex );
//STRIP001
//STRIP001     /** Optimized drawing: Scrolls horizontally and redraws only missing parts. */
//STRIP001     void                        ImplDrawHorzScrolled( sal_Int32 nOldPos );
//STRIP001
//STRIP001     /** Inverts the cursor bar at the specified position in maGridDev. */
//STRIP001     void                        ImplInvertCursor( sal_Int32 nPos );
//STRIP001
//STRIP001     /** Draws directly tracking rectangle to the column with the specified index. */
//STRIP001     void                        ImplDrawTrackingRect( sal_uInt32 nColIndex );
//STRIP001
//STRIP001     // accessibility ----------------------------------------------------------
//STRIP001 protected:
//STRIP001     /** Creates a new accessible object. */
//STRIP001     virtual ScAccessibleCsvControl* ImplCreateAccessible();
};


// ============================================================================

} //namespace binfilter
#endif

