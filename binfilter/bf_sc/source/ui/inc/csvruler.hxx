/*************************************************************************
 *
 *  $RCSfile: csvruler.hxx,v $
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

// ============================================================================

#ifndef _SC_CSVRULER_HXX
#define _SC_CSVRULER_HXX

#ifndef _SV_VIRDEV_HXX
#include <vcl/virdev.hxx>
#endif

#ifndef _SC_CSVCONTROL_HXX
#include "csvcontrol.hxx"
#endif
#ifndef _SC_CSVSPLITS_HXX
#include "csvsplits.hxx"
#endif


class ScAccessibleCsvControl;


// ============================================================================

/** A ruler control for the CSV import dialog. Supports setting and moving
    splits (which divide lines of data into several columns). */
class ScCsvRuler : public ScCsvControl
{
private:
    VirtualDevice               maBackgrDev;        /// Ruler background, scaling.
    VirtualDevice               maRulerDev;         /// Ruler with splits and cursor.

    Color                       maBackColor;        /// Background color.
    Color                       maActiveColor;      /// Color for active part of ruler.
    Color                       maTextColor;        /// Text and scale color.
    Color                       maSplitColor;       /// Split area color.

    ScCsvSplits                 maSplits;           /// Vector with split positions.
    ScCsvSplits                 maOldSplits;        /// Old state for cancellation.

    sal_Int32                   mnPosCursorLast;    /// Last valid position of cursor.
    sal_Int32                   mnPosMTStart;       /// Start position of mouse tracking.
    sal_Int32                   mnPosMTCurr;        /// Current position of mouse tracking.
    bool                        mbPosMTMoved;       /// Tracking: Anytime moved to another position?

    Size                        maWinSize;          /// Size of the control.
    Rectangle                   maActiveRect;       /// The active area of the ruler.
    sal_Int32                   mnSplitSize;        /// Size of a split circle.

    // ------------------------------------------------------------------------
public:
    explicit                    ScCsvRuler( ScCsvControl& rParent );

    // common ruler handling --------------------------------------------------
//STRIP001 public:
//STRIP001     /** Sets position and size of the ruler. The height is calculated internally. */
//STRIP001     virtual void                SetPosSizePixel(
//STRIP001                                     sal_Int32 nX, sal_Int32 nY,
//STRIP001                                     sal_Int32 nWidth, sal_Int32 nHeight,
//STRIP001                                     sal_uInt16 nFlags = WINDOW_POSSIZE_ALL );
//STRIP001
//STRIP001     /** Apply current layout data to the ruler. */
//STRIP001     void                        ApplyLayout( const ScCsvLayoutData& rOldData );
//STRIP001
//STRIP001 private:
//STRIP001     /** Reads colors from system settings. */
//STRIP001     void                        InitColors();
//STRIP001     /** Initializes all data dependent from the control's size. */
//STRIP001     void                        InitSizeData();
//STRIP001
//STRIP001     /** Moves cursor to a new position.
//STRIP001         @param bScroll  TRUE = The method may scroll the ruler. */
//STRIP001     void                        MoveCursor( sal_Int32 nPos, bool bScroll = true );
//STRIP001     /** Moves cursor to the given direction. */
//STRIP001     void                        MoveCursorRel( ScMoveMode eDir );
//STRIP001     /** Sets cursor to an existing split, according to eDir. */
//STRIP001     void                        MoveCursorToSplit( ScMoveMode eDir );
//STRIP001     /** Scrolls data grid vertically. */
//STRIP001     void                        ScrollVertRel( ScMoveMode eDir );

    // split handling ---------------------------------------------------------
//STRIP001 public:
//STRIP001     /** Returns the split array. */
//STRIP001     inline const ScCsvSplits&   GetSplits() const { return maSplits; }
//STRIP001     /** Returns the number of splits. */
//STRIP001     inline sal_uInt32           GetSplitCount() const
//STRIP001                                     { return maSplits.Count(); }
//STRIP001     /** Returns the position of the specified split. */
//STRIP001     inline sal_Int32            GetSplitPos( sal_uInt32 nIndex ) const
//STRIP001                                     { return maSplits[ nIndex ]; }
//STRIP001     /** Finds a position nearest to nPos which does not cause scrolling the visible area. */
//STRIP001     sal_Int32                   GetNoScrollPos( sal_Int32 nPos ) const;
//STRIP001
//STRIP001     /** Returns true if at position nPos is a split. */
//STRIP001     inline bool                 HasSplit( sal_Int32 nPos ) const { return maSplits.HasSplit( nPos ); }
//STRIP001     /** Inserts a split. */
//STRIP001     void                        InsertSplit( sal_Int32 nPos );
//STRIP001     /** Removes a split. */
//STRIP001     void                        RemoveSplit( sal_Int32 nPos );
//STRIP001     /** Moves a split from nPos to nNewPos. */
//STRIP001     void                        MoveSplit( sal_Int32 nPos, sal_Int32 nNewPos );
//STRIP001     /** Removes all splits of the ruler. */
//STRIP001     void                        RemoveAllSplits();
//STRIP001
//STRIP001 private:
//STRIP001     /** Finds next position without a split. */
//STRIP001     sal_Int32                   FindEmptyPos( sal_Int32 nPos, ScMoveMode eDir ) const;
//STRIP001
//STRIP001     /** Moves split and cursor to nNewPos and commits event. */
//STRIP001     void                        MoveCurrSplit( sal_Int32 nNewPos );
//STRIP001     /** Moves split and cursor to the given direction and commits event. */
//STRIP001     void                        MoveCurrSplitRel( ScMoveMode eDir );

    // event handling ---------------------------------------------------------
//STRIP001 protected:
//STRIP001     virtual void                Resize();
//STRIP001     virtual void                GetFocus();
//STRIP001     virtual void                LoseFocus();
//STRIP001     virtual void                DataChanged( const DataChangedEvent& rDCEvt );
//STRIP001
//STRIP001     virtual void                MouseButtonDown( const MouseEvent& rMEvt );
//STRIP001     virtual void                MouseMove( const MouseEvent& rMEvt );
//STRIP001     virtual void                Tracking( const TrackingEvent& rTEvt );
//STRIP001
//STRIP001     virtual void                KeyInput( const KeyEvent& rKEvt );
//STRIP001
//STRIP001 private:
//STRIP001     /** Starts tracking at the specified position. */
//STRIP001     void                        StartMouseTracking( sal_Int32 nPos );
//STRIP001     /** Moves tracking to a new position. */
//STRIP001     void                        MoveMouseTracking( sal_Int32 nPos );
//STRIP001     /** Applies tracking action for the current tracking position.
//STRIP001         @param bApply  TRUE = apply action, FALSE = cancel action. */
//STRIP001     void                        EndMouseTracking( bool bApply );

    // painting ---------------------------------------------------------------
//STRIP001 protected:
//STRIP001     virtual void                Paint( const Rectangle& );

//STRIP001 public:
//STRIP001     /** Redraws the entire ruler. */
//STRIP001     void                        ImplRedraw();

//STRIP001 private:
//STRIP001     /** Returns the width of the control. */
//STRIP001     inline sal_Int32            GetWidth() const { return maWinSize.Width(); }
//STRIP001     /** Returns the height of the control. */
//STRIP001     inline sal_Int32            GetHeight() const { return maWinSize.Height(); }
//STRIP001
//STRIP001     /** Draws the background and active area to maBackgrDev (only the given X range). */
//STRIP001     void                        ImplDrawArea( sal_Int32 nPosX, sal_Int32 nWidth );
//STRIP001     /** Draws the entire ruler background with scaling to maBackgrDev. */
//STRIP001     void                        ImplDrawBackgrDev();
//STRIP001
//STRIP001     /** Draws a split to maRulerDev. */
//STRIP001     void                        ImplDrawSplit( sal_Int32 nPos );
//STRIP001     /** Erases a split from maRulerDev. */
//STRIP001     void                        ImplEraseSplit( sal_Int32 nPos );
//STRIP001     /** Draws the ruler background, all splits and the cursor to maRulerDev. */
//STRIP001     void                        ImplDrawRulerDev();
//STRIP001
//STRIP001     /** Inverts the cursor bar at the specified position in maRulerDev. */
//STRIP001     void                        ImplInvertCursor( sal_Int32 nPos );
//STRIP001     /** Draws directly tracking rectangle to the column with the specified index. */
//STRIP001     void                        ImplDrawTrackingRect();
//STRIP001
//STRIP001     /** Sets arrow or horizontal split pointer. */
//STRIP001     void                        ImplSetMousePointer( sal_Int32 nPos );

//STRIP001     // accessibility ----------------------------------------------------------
//STRIP001 protected:
//STRIP001     /** Creates a new accessible object. */
//STRIP001     virtual ScAccessibleCsvControl* ImplCreateAccessible();
};


// ============================================================================

#endif

