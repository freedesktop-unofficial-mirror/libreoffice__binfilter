/*************************************************************************
 *
 *  $RCSfile: fudraw.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:17:39 $
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

#ifndef _SCH_FUDRAW_HXX
#define _SCH_FUDRAW_HXX

#include "fupoor.hxx"

/*************************************************************************
|*
|* Basisklasse fuer alle Drawmodul-spezifischen Funktionen
|*
\************************************************************************/

class SdrObject;

class SchFuDraw : public SchFuPoor
{
protected:
    Pointer aNewPointer;
    Pointer aOldPointer;
    BOOL    bMBDown;

    /** possible directions in which to select objects
     */
    enum lcl_Selection_Direction
    {
        lcl_SELECT_PREVIOUS,
        lcl_SELECT_NEXT,
        lcl_SELECT_FIRST,
        lcl_SELECT_LAST
    };

    /** possible directions in which to move an object
     */
    enum lcl_Movement_Direction
    {
        lcl_MOVE_LEFT,
        lcl_MOVE_RIGHT,
        lcl_MOVE_UP,
        lcl_MOVE_DOWN
    };

    /** marks the next/previous/first or last object in the current
        group of chart objects.

        @param eDirection determines in which direction to travel

        @param nDepth is to prevent a loop in recursion.  When
               selecting a new object, this may be invalid.  In this
               case the method tries the next object.  If the last
               object is reached without success, the first is
               selected using a recursive call.  If no valid objects
               are available at all this parameter avoids a loop
               (which should normally never occur).

        @param bEnterDiagram determines if during navigation the
               diagram should be ignored as group and its content
               rather be treated as top-level objects.  This parameter
               is especially needed so that the diagram can still be
               selected (without entering).

        @returns TRUE, if an object could be marked
     */
//STRIP001     BOOL MarkChartObject( lcl_Selection_Direction eDirection, int nDepth = 0, bool bEnterDiagram = true );

    /** moves an object in one of the four directions given in
        lcl_Movement_Direction.  This is only possible for top-level
        chart objects, i.e., titles, legend and diagram

        @param eDirection the direction in which to move.  If an
               object is too close to the edge, the object is not
               moved.

        @param nAmount the amount of units to be moved about.  The
               unit can be 100th of a mm or pixels depending on what
               bPixel is set to.

        @param bPixel If true, the amount nAmount is treated as pixels
               in the current window, otherwise the current logical
               unit is used, which in a chart is always 100th of a mm.

        @returns TRUE, if the object could be moved
     */
//STRIP001     BOOL MoveMarkedObject( lcl_Movement_Direction eDirection, long nAmount, bool bPixel = false );

    /** resizes an object by the amount given into the larger of width
        and height.  In the smaller extent the amount is calculated
        such that the resize is proportional.

        @param nAmount the amount by which the object will be resized.
               The amount will be added to the larger extent (width or
               height).  The resize is proportional in the other
               direction.

        @param bPixel If true, the amount nAmount is treated as pixels
               in the current window for the larger of width and
               height.  Otherwise the current logical unit is used,
               which in a chart is always 100th of a mm.

        @returns TRUE, if the object could be resized
     */
//STRIP001     BOOL ResizeMarkedObject( long nAmount, bool bPixel = false );

    /** moves a pie segment by the given amount in percent

        @param bOut if true increases the offset, otherwise decreases
               the offset.  The offset stays always between 0 and 100.

        @param nAmount the amount of percent by which the pie segment
               is dragged.

        @returns TRUE, if the object was a pie and could be moved
     */
//STRIP001     BOOL MovePieSegment( bool bOut, long nAmount );

    /** determines if the object currently selected is valid, i.e. it
        may be selected in the UI for making changes.

        @returns true, if a valid object is selected.
     */
//STRIP001     bool ValidObjectSelected();

    /** For some objects only the 8 green handles of the group are
        shown, for others a special handling is required, e.g. bars in
        a bar chart.  This is done here for the currently selected
        object.
     */
//STRIP001     void AdjustHandles( SdrObject* pObj );

    /** Some groups in a chart may not be entered, e.g. an axis
        object.  Otherwise you would be able to select all tick-mark
        objects or labels.

        @returns true, if the currently selected object is a group
                 that may be entered, e.g. a data series object.
     */
//STRIP001     bool MayEnterGroup();

    /** get the object which is currently selected in the UI.  In the
        chart this can only be one object at a time.
     */
//STRIP001     SdrObject* GetCurrentlyMarkedObject();

    /** after move or resize there have to be some things set at chart
        objects and the model.  It is called by MoveMarkedObject.
     */
//STRIP001     void ApplyMoveResizeChanges();

public:
//STRIP001  TYPEINFO();

    SchFuDraw(SchViewShell* pViewSh, SchWindow* pWin, SchView* pView,
              ChartModel* pDoc, SfxRequest& rReq);
    virtual ~SchFuDraw();

//STRIP001  virtual BOOL KeyInput(const KeyEvent& rKEvt);
//STRIP001  virtual BOOL MouseMove(const MouseEvent& rMEvt);
//STRIP001  virtual BOOL MouseButtonUp(const MouseEvent& rMEvt);
//STRIP001  virtual BOOL MouseButtonDown(const MouseEvent& rMEvt);

    virtual void Activate();

    virtual void ForcePointer(const MouseEvent* pMEvt = NULL);

//STRIP001  virtual void DoubleClick();
};

#endif  // _SCH_FUDRAW_HXX


