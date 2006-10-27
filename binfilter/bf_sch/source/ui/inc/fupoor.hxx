/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: fupoor.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 17:53:32 $
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
namespace binfilter {

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


public:

    SchFuPoor(SchViewShell* pViewSh, SchWindow* pWin, SchView* pView,
              ChartModel* pDoc, SfxRequest& rReq);
    virtual ~SchFuPoor();


    // Mouse- & Key-Events; Returnwert=TRUE: Event wurde bearbeitet

    virtual void Activate();        // Function aktivieren
    virtual void Deactivate();      // Function deaktivieren



    USHORT GetSlotID() const { return( nSlotId ); }

};

} //namespace binfilter
#endif  // _SCH_FUPOOR_HXX


