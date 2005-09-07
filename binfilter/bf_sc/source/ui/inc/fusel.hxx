/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: fusel.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 19:51:21 $
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

#ifndef SC_FUSEL_HXX
#define SC_FUSEL_HXX

#ifndef _SV_HXX
#endif

#ifndef SC_FUDRAW_HXX
#include "fudraw.hxx"
#endif
namespace binfilter {

//class Outliner;
//class OutlinerView;
class SdrPageView;


/*************************************************************************
|*
|* Basisklasse fuer alle Funktionen
|*
\************************************************************************/

class FuSelection : public FuDraw
{
 protected:
//  Outliner*       pOutliner;
//  OutlinerView*   pOutlinerView;
    BOOL            bVCAction;

 private:
//STRIP001  BOOL TestDetective( SdrPageView* pPV, const Point& rPos );  // -> fusel2
//STRIP001  BOOL TestComment( SdrPageView* pPV, const Point& rPos );    // -> fusel2

 public:
    FuSelection(ScTabViewShell* pViewSh, Window* pWin, SdrView* pView,
           SdrModel* pDoc, SfxRequest& rReq );

    virtual ~FuSelection();
                                       // Mouse- & Key-Events
//STRIP001  virtual BOOL KeyInput(const KeyEvent& rKEvt);
//STRIP001  virtual BOOL MouseMove(const MouseEvent& rMEvt);
//STRIP001  virtual BOOL MouseButtonUp(const MouseEvent& rMEvt);
//STRIP001  virtual BOOL MouseButtonDown(const MouseEvent& rMEvt);
//STRIP001  virtual BYTE Command(const CommandEvent& rCEvt);
//STRIP001
//STRIP001  virtual void Activate();           // Function aktivieren
//STRIP001  virtual void Deactivate();         // Function deaktivieren
};



} //namespace binfilter
#endif      // _SD_FUSEL_HXX

