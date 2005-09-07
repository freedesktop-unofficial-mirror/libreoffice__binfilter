/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: fupoor.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 19:51:06 $
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

#ifndef _SC_FUPOOR_HXX
#define _SC_FUPOOR_HXX

#ifndef _EVENT_HXX //autogen
#include <vcl/event.hxx>
#endif
#ifndef _TIMER_HXX //autogen
#include <vcl/timer.hxx>
#endif
#ifndef _SFXREQUEST_HXX //autogen
#include <bf_sfx2/request.hxx>
#endif
class Window;
class Dialog;
namespace binfilter {

class SdrView;
class ScTabViewShell;
class SdrModel;

// #98185# Create default drawing objects via keyboard
class SdrObject;

//  Return-Werte fuer Command
#define SC_CMD_NONE     0
#define SC_CMD_USED     1
#define SC_CMD_IGNORE   2

/*************************************************************************
|*
|* Basisklasse fuer alle Funktionen
|*
\************************************************************************/

class FuPoor
{
 protected:
    SdrView*        pView;
    ScTabViewShell* pViewShell;
    Window*         pWindow;
    SdrModel*       pDrDoc;

    SfxRequest      aSfxRequest;
    Dialog*         pDialog;

    Timer           aScrollTimer;           // fuer Autoscrolling
    DECL_LINK( ScrollHdl, Timer * );
//STRIP001  void ForceScroll(const Point& aPixPos);

    Timer           aDragTimer;             // fuer Drag&Drop
    DECL_LINK( DragTimerHdl, Timer * );
//STRIP001  DECL_LINK( DragHdl, void * );
    BOOL            bIsInDragMode;
    Point           aMDPos;                 // Position von MouseButtonDown

    // #95491# member to hold state of the mouse buttons for creation
    // of own MouseEvents (like in ScrollHdl)
private:
    sal_uInt16      mnCode;

 public:
    FuPoor(ScTabViewShell* pViewSh, Window* pWin, SdrView* pView,
           SdrModel* pDoc, SfxRequest& rReq);
    virtual ~FuPoor();

//STRIP001  // #95491# see member
//STRIP001  void SetMouseButtonCode(sal_uInt16 nNew) { if(nNew != mnCode) mnCode = nNew; }
//STRIP001  const sal_uInt16 GetMouseButtonCode() const { return mnCode; }
//STRIP001
//STRIP001  virtual void Paint(const Rectangle& rRect, Window* pWin) {}
//STRIP001
//STRIP001  virtual void DoCut();
//STRIP001  virtual void DoCopy();
//STRIP001  virtual void DoPaste();
//STRIP001
//STRIP001  // Mouse- & Key-Events; Returnwert=TRUE: Event wurde bearbeitet
//STRIP001  virtual BOOL KeyInput(const KeyEvent& rKEvt);
//STRIP001  virtual BOOL MouseMove(const MouseEvent& rMEvt) { return FALSE; }
//STRIP001
//STRIP001  // #95491# moved from inline to *.cxx
//STRIP001  virtual BOOL MouseButtonUp(const MouseEvent& rMEvt); // { return FALSE; }
//STRIP001
//STRIP001  // #95491# moved from inline to *.cxx
//STRIP001  virtual BOOL MouseButtonDown(const MouseEvent& rMEvt); // { return FALSE; }
//STRIP001
//STRIP001  virtual BYTE Command(const CommandEvent& rCEvt);
//STRIP001
//STRIP001  virtual void Activate();        // Function aktivieren
//STRIP001  virtual void Deactivate();      // Function deaktivieren
//STRIP001
//STRIP001  virtual void ScrollStart() {}   // diese Funktionen werden von
//STRIP001  virtual void ScrollEnd() {}     // ForceScroll aufgerufen
//STRIP001
//STRIP001  void SetWindow(Window* pWin) { pWindow = pWin; }
//STRIP001
    USHORT GetSlotID() const { DBG_BF_ASSERT(0, "STRIP"); return 0;} //STRIP001 USHORT GetSlotID() const { return( aSfxRequest.GetSlot() );}
//STRIP001
//STRIP001  BOOL    IsDetectiveHit( const Point& rLogicPos );
//STRIP001
    void    StopDragTimer();
//STRIP001
//STRIP001  // #98185# Create default drawing objects via keyboard
//STRIP001  virtual SdrObject* CreateDefaultObject(const sal_uInt16 nID, const Rectangle& rRectangle);
//STRIP001 protected:
//STRIP001  void ImpForceQuadratic(Rectangle& rRect);
};



} //namespace binfilter
#endif      // _SD_FUPOOR_HXX

