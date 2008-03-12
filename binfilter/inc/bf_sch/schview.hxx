/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: schview.hxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 11:27:34 $
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

#ifndef _SCH_SCHVIEW_HXX
#define _SCH_SCHVIEW_HXX

#include <bf_svx/svdedxv.hxx>
#include <bf_svx/view3d.hxx>
#include <bf_svx/svdpage.hxx>

#include "chtmodel.hxx"
#include "docshell.hxx"

class Graphic;
namespace binfilter {

class SchViewShell;
class SchPage;
class SchWindow;
class ChartModel;
class SchDragServerRef;
class E3dScene;
} //namespace binfilter

namespace binfilter {//STRIP009
DECLARE_LIST(E3dLogicalObjList, E3dObject*)//STRIP008 DECLARE_LIST(E3dLogicalObjList, E3dObject*);

/*************************************************************************
|*
|* View
|*
\************************************************************************/

class SchView : public E3dView
{
 protected:
    ChartModel*   pDoc;
    SchChartDocShell*   pDocSh;
    SchViewShell*       pViewSh;
    BOOL                bDragActive;
    USHORT              nLogicalMarked;
    USHORT              nLogicalEntered;

    Timer aTimer;
    void             Construct();
//      SchDragServerRef CreateDataObject(SchView* pView, const Point& rDragPos);
//      SchDragServerRef CreateDataObject(ChartModel* pDocument);
    void                SetMarkHandles();

 public:

    //void NotifySelection();
    DECL_LINK(NotifySelection,void*);

    SchView(SchChartDocShell* pDocSh, OutputDevice* pOutDev, SchViewShell* pShell);
    virtual ~SchView();

    ChartModel& GetDoc() const { return *pDoc; }


    // clipboard / drag and drop methods using XTransferable

    void UpdateSelectionClipboard( BOOL bForceDeselect );


    BOOL IsActive() const { return bDragActive; }



    virtual void MarkListHasChanged();


    FASTBOOL    IsLogicalGroupMarked() { return (nLogicalMarked != 0); }
    FASTBOOL    IsLogicalGroupEntered() { return (nLogicalEntered != 0); }



    SchChartDocShell* GetDocShell() const { return pDocSh; }

    // drag and drop


    virtual void Notify( SfxBroadcaster& rBC, const SfxHint& rHint );
};

} //namespace binfilter
#endif      // _SCH_SCHVIEW_HXX
