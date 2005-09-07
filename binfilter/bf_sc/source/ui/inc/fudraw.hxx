/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: fudraw.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 19:49:24 $
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

#ifndef SC_FUDRAW_HXX
#define SC_FUDRAW_HXX

#ifndef _SC_FUPOOR_HXX
#include "fupoor.hxx"
#endif

#ifndef _SV_POINTR_HXX //autogen
#include <vcl/pointr.hxx>
#endif
namespace binfilter {

/*************************************************************************
|*
|* Basisklasse fuer alle Drawmodul-spezifischen Funktionen
|*
\************************************************************************/

class FuDraw : public FuPoor
{
 protected:
    Pointer aNewPointer;
    Pointer aOldPointer;

 public:
    FuDraw(ScTabViewShell* pViewSh, Window* pWin, SdrView* pView,
           SdrModel* pDoc, SfxRequest& rReq);
    virtual ~FuDraw();

//STRIP001  virtual BOOL KeyInput(const KeyEvent& rKEvt);

//STRIP001  virtual void ScrollStart();
//STRIP001  virtual void ScrollEnd();

//STRIP001  virtual void Activate();
//STRIP001  virtual void Deactivate();

//STRIP001  virtual void ForcePointer(const MouseEvent* pMEvt);

//STRIP001  virtual BOOL MouseMove(const MouseEvent& rMEvt);
//STRIP001  virtual BOOL MouseButtonUp(const MouseEvent& rMEvt);
//STRIP001  virtual BOOL MouseButtonDown(const MouseEvent& rMEvt);

    // #97016# II
//STRIP001  virtual void SelectionHasChanged();

//STRIP001  private:
//STRIP001  void    DoModifiers(const MouseEvent& rMEvt);
//STRIP001  void    ResetModifiers();
};



} //namespace binfilter
#endif      // _SD_FUDRAW_HXX
