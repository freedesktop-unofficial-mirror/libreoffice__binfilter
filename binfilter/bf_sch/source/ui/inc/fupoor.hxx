/*************************************************************************
 *
 *  $RCSfile: fupoor.hxx,v $
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

#ifndef _SCH_FUPOOR_HXX
#define _SCH_FUPOOR_HXX
//------------------------------------------------------------------
//
// dieses Define dient nur zum Testen und darf auf keinen Fall aktiv bleiben
// Bei Umstellungen alle Files nach SIG_CHARTMODELDEFSCHDOC durchsuchen
// #define ChartModel SchChartDocument
//------------------------------------------------------------------

#ifndef _SV_DIALOG_HXX //autogen
#include <vcl/dialog.hxx>
#endif

#include "objid.hxx"

class SchView;
class SchViewShell;
class SchWindow;
class ChartModel;
class SfxRequest;

#define HITPIX    2     // Hit-Toleranz in Pixel
#define DRGPIX    2     // Drag MinMove in Pixel


/*************************************************************************
|*
|* Basisklasse fuer alle Funktionen
|*
\************************************************************************/

class SchFuPoor
{
protected:
    SchView*        pView;
    SchViewShell*   pViewShell;
    SchWindow*      pWindow;
    ChartModel* pChDoc;

    USHORT          nSlotId;
    USHORT          nSlotValue;

    Dialog*         pDialog;

    Timer           aDragTimer;             // fuer Drag&Drop
    DECL_LINK(DragHdl, Timer*);
    BOOL            bIsInDragMode;
    Point           aMDPos;                 // Position von MouseButtonDown

    SdrObject   *pMarkedObj;
    SchObjectId *pMarkedObjId;
    UINT16      nMarkedID;

    BOOL            bFirstMouseMove;

//STRIP001  virtual void RemarkObject ();
//STRIP001  virtual void Select3DGroupMembers(SdrObject *pObj,  SdrPageView* pPV);

public:
//STRIP001  TYPEINFO();

    SchFuPoor(SchViewShell* pViewSh, SchWindow* pWin, SchView* pView,
              ChartModel* pDoc, SfxRequest& rReq);
    virtual ~SchFuPoor();

//STRIP001  virtual BOOL DoCut();
//STRIP001  virtual void DoCopy();
//STRIP001  virtual void DoPaste();

    // Mouse- & Key-Events; Returnwert=TRUE: Event wurde bearbeitet
//STRIP001  virtual BOOL KeyInput(const KeyEvent& rKEvt);
//STRIP001  virtual BOOL MouseMove(const MouseEvent& rMEvt);
//STRIP001  virtual BOOL MouseButtonUp(const MouseEvent& rMEvt);
//STRIP001  virtual BOOL MouseButtonDown(const MouseEvent& rMEvt);
//STRIP001  virtual BOOL Command(const CommandEvent& rCEvt);
//STRIP001  virtual void Paint(const Rectangle& rRect, SchWindow* pWin);

    virtual void Activate();        // Function aktivieren
    virtual void Deactivate();      // Function deaktivieren

//STRIP001  void SetWindow(SchWindow* pWin) { pWindow = pWin; }

//STRIP001  virtual void SelectionHasChanged();

    USHORT GetSlotID() const { return( nSlotId ); }
//STRIP001  USHORT GetSlotValue() const { return( nSlotValue ); }

};

#endif  // _SCH_FUPOOR_HXX


