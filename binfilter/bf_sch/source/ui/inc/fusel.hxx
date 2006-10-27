/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: fusel.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 17:53:43 $
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

#ifndef _SCH_FUSEL_HXX
#define _SCH_FUSEL_HXX


#ifndef _SCH_FUDRAW_HXX
#include "fudraw.hxx"
#endif
namespace binfilter {

class SdrDragMethod;
class SdrCircObj;

/*************************************************************************
|*
|* Basisklasse fuer alle Funktionen
|*
\************************************************************************/

class SchFuSelection : public SchFuDraw
{
protected:
    BOOL    bWasSelected;
    BOOL    bVCAction;
    SdrDragMethod* pDragMethod;


public:

    SchFuSelection(SchViewShell* pViewSh, SchWindow* pWin, SchView* pView,
                   ChartModel* pDoc, SfxRequest& rReq);

    virtual ~SchFuSelection();


    virtual void Activate();
    virtual void Deactivate();
};

} //namespace binfilter
#endif  // _SCH_FUSEL_HXX


