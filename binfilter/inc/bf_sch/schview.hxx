/*************************************************************************
 *
 *  $RCSfile: schview.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:25:34 $
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

#ifndef _SCH_SCHVIEW_HXX
#define _SCH_SCHVIEW_HXX

#ifndef _SVDEDXV_HXX //autogen
#include <bf_svx/svdedxv.hxx>
#endif
#ifndef _E3D_VIEW3D_HXX //autogen
#include <bf_svx/view3d.hxx>
#endif

#ifndef _SVDPAGE_HXX //autogen
#include <bf_svx/svdpage.hxx>
#endif
#ifndef _TRANSFER_HXX //autogen
#include <svtools/transfer.hxx>
#endif


#ifndef _CHTMODEL_HXX
#include "chtmodel.hxx"
#endif

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
namespace com { namespace sun { namespace star { namespace datatransfer {
    class XTransferable;
}}}}
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
//STRIP001  static void      DeleteChartUserData(ChartModel& rDoc);
    void             Construct();
//      SchDragServerRef CreateDataObject(SchView* pView, const Point& rDragPos);
//      SchDragServerRef CreateDataObject(ChartModel* pDocument);
    void                SetMarkHandles();

 public:

    //void NotifySelection();
    DECL_LINK(NotifySelection,void*);

    SchView(SchChartDocShell* pDocSh, OutputDevice* pOutDev, SchViewShell* pShell);
//STRIP001  SchView(ChartModel* pDoc, OutputDevice* pOutDev);
    virtual ~SchView();

//STRIP001  virtual BOOL DoCut(Window* pWindow=NULL);
//STRIP001  virtual void DoCopy(Window* pWindow=NULL);
//STRIP001  virtual void DoPaste(Window* pWindow=NULL);

//STRIP001  FASTBOOL BegTextEdit(SdrObject* pObj, SdrPageView* pPV = NULL,
//STRIP001                       Window* pWin = NULL, FASTBOOL bIsNewObj = FALSE,
//STRIP001                       SdrOutliner* pGivenOutliner = NULL,
//STRIP001                       OutlinerView* pGivenOutlinerView = NULL,
//STRIP001                       FASTBOOL bDontDeleteOutliner = FALSE,
//STRIP001                       FASTBOOL bOnlyOneView = FALSE);
//STRIP001  SdrEndTextEditKind EndTextEdit();

//STRIP001  BOOL IsChartObjSelected();
    long GetSelectedRow() const;
//STRIP001  BOOL CanDeleteMarkedObjects();
//STRIP001  BOOL DeleteMarkedObjects(const String& rUndoStr);
//STRIP001  BOOL CanSetDataAttr();
//STRIP001  void PutMarkedToPos(ULONG nObjPos);
//STRIP001  void MovMarkedToPos(ULONG nObjPos);

    String GetContext();
    String GetContextType();

    ChartModel& GetDoc() const { return *pDoc; }

//STRIP001  BOOL BeginDrag( Window* pWindow, Point aStartPos );

    // clipboard / drag and drop methods using XTransferable
//STRIP001  sal_Bool InsertData( TransferableDataHelper& rDataHelper, const Point& rPos, BOOL bCopy, ULONG nFormat = 0 );
//STRIP001  ::com::sun::star::uno::Reference< ::com::sun::star::datatransfer::XTransferable > CreateDragDropDataObject( SchView* pView, Window& rWindow, const Point& rDragPos );
//STRIP001  ::com::sun::star::uno::Reference< ::com::sun::star::datatransfer::XTransferable > CreateClipboardDataObject();
//STRIP001  ::com::sun::star::uno::Reference< ::com::sun::star::datatransfer::XTransferable > CreateSelectionDataObject( SchView* pWorkView, Window& rWindow );

    void UpdateSelectionClipboard( BOOL bForceDeselect );

//STRIP001  BOOL InsertGraphic( const Graphic& rGraphic, const Point& rPos );

    BOOL IsActive() const { return bDragActive; }

//STRIP001  virtual void InvalidateOneWin(Window& rWin, const Rectangle& rRect);

//STRIP001  void       SetDefault();

//STRIP001  virtual BOOL NotifyNewUndoAction();
    virtual void MarkListHasChanged();

//STRIP001  FASTBOOL    EnterMarkedGroup();
//STRIP001  void        LeaveOneGroup();
//STRIP001  void        LeaveAllGroup();

    FASTBOOL    IsLogicalGroupMarked() { return (nLogicalMarked != 0); }
    FASTBOOL    IsLogicalGroupEntered() { return (nLogicalEntered != 0); }
//STRIP001  void        MarkLogicalGroup();

//STRIP001  FASTBOOL    PickObj(const Point& rPnt, short nTol, SdrObject*& prObj,
//STRIP001                      SdrPageView*& prPV,ULONG nOptions=0) const;

//STRIP001  FASTBOOL    IsMarkedHit(const Point& rPnt, short nTol=-2) const;

//STRIP001  E3dLogicalObjList GetLogicalObjList();
    SchChartDocShell* GetDocShell() const { return pDocSh; }

    // drag and drop
//STRIP001  virtual sal_Int8 AcceptDrop( const AcceptDropEvent& rEvt, SchWindow* pWin );
//STRIP001  virtual sal_Int8 ExecuteDrop( const ExecuteDropEvent& rEvt, SchWindow* pWin );

//STRIP001     Window* GetWindow() const;

    virtual void Notify( SfxBroadcaster& rBC, const SfxHint& rHint );
};

} //namespace binfilter
#endif      // _SCH_SCHVIEW_HXX
