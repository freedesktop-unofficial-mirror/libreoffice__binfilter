/*************************************************************************
 *
 *  $RCSfile: fusel.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:29:49 $
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

