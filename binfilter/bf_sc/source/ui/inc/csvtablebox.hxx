/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: csvtablebox.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 19:40:23 $
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

#ifndef _SC_CSVTABLEBOX_HXX
#define _SC_CSVTABLEBOX_HXX

#ifndef _SV_CTRL_HXX
#include <vcl/ctrl.hxx>
#endif
#ifndef _SV_SCRBAR_HXX
#include <vcl/scrbar.hxx>
#endif

#ifndef _SC_CSVCONTROL_HXX
#include "csvcontrol.hxx"
#endif
#ifndef _SC_CSVRULER_HXX
#include "csvruler.hxx"
#endif
#ifndef _SC_CSVGRID_HXX
#include "csvgrid.hxx"
#endif
class ListBox;
namespace binfilter {

class ScAsciiOptions;


/* ============================================================================
Position: Positions between the characters (the dots in the ruler).
Character: The characters (the range from one position to the next).
Split: Positions which contain a split to divide characters into groups (columns).
Column: The range between two splits.
============================================================================ */

/** The control in the CSV import dialog that contains a ruler and a data grid
    to visualize and modify the current import settings. */
class ScCsvTableBox : public ScCsvControl
{
private:
    ScCsvLayoutData             maData;             /// Current layout data of the controls.

    ScCsvRuler                  maRuler;            /// The ruler for fixed width mode.
    ScCsvGrid                   maGrid;             /// Calc-like data table for fixed width mode.
    ScrollBar                   maHScroll;          /// Horizontal scroll bar.
    ScrollBar                   maVScroll;          /// Vertical scroll bar.
    ScrollBarBox                maScrollBox;        /// For the bottom right edge.

    Link                        maUpdateTextHdl;    /// Updates all cell texts.
    Link                        maColTypeHdl;       /// Handler for exporting the column type.

    ScCsvColStateVec            maFixColStates;     /// Column states in fixed width mode.
    ScCsvColStateVec            maSepColStates;     /// Column states in separators mode.

    sal_Int32                   mnFixedWidth;       /// Cached total width for fixed width mode.

    bool                        mbFixedMode;        /// false = Separators, true = Fixed width.

    // ------------------------------------------------------------------------
public:
    explicit                    ScCsvTableBox( Window* pParent );
    explicit                    ScCsvTableBox( Window* pParent, const ResId& rResId );

    // common table box handling ----------------------------------------------
//STRIP001 public:
//STRIP001     /** Sets the control to separators mode. */
//STRIP001     void                        SetSeparatorsMode();
//STRIP001     /** Sets the control to fixed width mode. */
//STRIP001     void                        SetFixedWidthMode();

//STRIP001 private:
//STRIP001     /** Initialisation on construction. */
//STRIP001     void                        Init();
//STRIP001     /** Initializes the children controls (pos/size, scroll bars, ...). */
//STRIP001     void                        InitControls();
//STRIP001     /** Initializes size and position data of horizontal scrollbar. */
//STRIP001     void                        InitHScrollBar();
//STRIP001     /** Initializes size and position data of vertical scrollbar. */
//STRIP001     void                        InitVScrollBar();

//STRIP001     /** Calculates and sets valid position offset nearest to nPos. */
//STRIP001     inline void                 ImplSetPosOffset( sal_Int32 nPos )
//STRIP001                                     { maData.mnPosOffset = Max( Min( nPos, GetMaxPosOffset() ), 0L ); }
//STRIP001     /** Calculates and sets valid line offset nearest to nLine. */
//STRIP001     inline void                 ImplSetLineOffset( sal_Int32 nLine )
//STRIP001                                     { maData.mnLineOffset = Max( Min( nLine, GetMaxLineOffset() ), 0L ); }
//STRIP001     /** Moves controls (not cursors!) so that nPos becomes visible. */
//STRIP001     void                        MakePosVisible( sal_Int32 nPos );

    // cell contents ----------------------------------------------------------
//STRIP001 public:
//STRIP001     /** Fills all cells of all lines with the passed texts (Unicode strings). */
//STRIP001     void                        SetUniStrings(
//STRIP001                                     const String* pTextLines, const String& rSepChars,
//STRIP001                                     sal_Unicode cTextSep, bool bMergeSep );
//STRIP001     /** Fills all cells of all lines with the passed texts (ByteStrings). */
//STRIP001     void                        SetByteStrings(
//STRIP001                                     const ByteString* pLineTexts, CharSet eCharSet,
//STRIP001                                     const String& rSepChars, sal_Unicode cTextSep, bool bMergeSep );

    // column settings --------------------------------------------------------
public:
    /** Reads UI strings for data types from the list box. */
    void                        InitTypes( const ListBox& rListBox );
//STRIP001     /** Returns the data type of the selected columns. */
//STRIP001     inline sal_Int32            GetSelColumnType() const { return maGrid.GetSelColumnType(); }

    /** Fills the options object with current column data. */
    void                        FillColumnData( ScAsciiOptions& rOptions ) const;

    // event handling ---------------------------------------------------------
public:
    /** Sets a new handler for "update cell texts" requests. */
    inline void                 SetUpdateTextHdl( const Link& rHdl ) { maUpdateTextHdl = rHdl; }
    /** Returns the handler for "update cell texts" requests. */
//STRIP001     inline const Link&          GetUpdateTextHdl() const { return maUpdateTextHdl; }
    /** Sets a new handler for "column selection changed" events. */
    inline void                 SetColTypeHdl( const Link& rHdl ) { maColTypeHdl = rHdl; }
    /** Returns the handler for "column selection changed" events. */
    inline const Link&          GetColTypeHdl() const { return maColTypeHdl; }

//STRIP001 protected:
//STRIP001     virtual void                Resize();
//STRIP001     virtual void                DataChanged( const DataChangedEvent& rDCEvt );

//STRIP001 private:
//STRIP001                                 DECL_LINK( CsvCmdHdl, ScCsvControl* );
//STRIP001                                 DECL_LINK( ScrollHdl, ScrollBar* );
//STRIP001                                 DECL_LINK( ScrollEndHdl, ScrollBar* );

    // accessibility ----------------------------------------------------------
//STRIP001 public:
//STRIP001     /** Creates and returns the accessible object of this control. */
//STRIP001     virtual XAccessibleRef      CreateAccessible();
//STRIP001
//STRIP001 protected:
//STRIP001     /** Creates a new accessible object. */
//STRIP001     virtual ScAccessibleCsvControl* ImplCreateAccessible();
};


// ============================================================================

} //namespace binfilter
#endif

