/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: csvruler.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 16:04:55 $
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
namespace binfilter {


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

    // split handling ---------------------------------------------------------

    // event handling ---------------------------------------------------------

    // painting ---------------------------------------------------------------



};


// ============================================================================

} //namespace binfilter
#endif

