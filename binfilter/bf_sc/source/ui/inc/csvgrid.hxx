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

// ============================================================================

#ifndef _SC_CSVGRID_HXX
#define _SC_CSVGRID_HXX

#include <vcl/virdev.hxx>
#include <vcl/menu.hxx>
#include <bf_svtools/lstner.hxx>

#include <vector>
#include <memory>

#include "csvcontrol.hxx"
#include "csvsplits.hxx"

namespace binfilter {
class ColorConfig;

// ----------------------------------------------------------------------------

class EditEngine;
class ScEditEngineDefaulter;
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

    ColorConfig&                mrColorConfig;      /// Application color configuration.
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
};


// ============================================================================

} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
