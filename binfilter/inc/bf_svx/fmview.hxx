/*************************************************************************
 *
 *  $RCSfile: fmview.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:35 $
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

#ifndef _SVX_FMVIEW_HXX
#define _SVX_FMVIEW_HXX

// HACK to avoid too deep includes and to have some
// levels free in svdmark itself (MS compiler include depth limit)
#ifndef _SVDHDL_HXX
#include <bf_svx/svdhdl.hxx>
#endif

#ifndef _E3D_VIEW3D_HXX
#include <bf_svx/view3d.hxx>
#endif
#ifndef _COMPHELPER_UNO3_HXX_
#include <comphelper/uno3.hxx>
#endif
FORWARD_DECLARE_INTERFACE(util,XNumberFormats)
FORWARD_DECLARE_INTERFACE(beans,XPropertySet)

class OutputDevice;
class ExtOutputDevice;
class FmFormModel;
class FmPageViewWinRec;
class FmFormPage;

namespace svx {
    class ODataAccessDescriptor;
}

class FmFormView : public E3dView
{
    friend class FmXFormController;
    friend class FmFormShell;
    friend class FmXFormShell;
    friend class FmXFormView;
    friend class FmExplorer;
    friend class FmFormObj;

    FmXFormView*    pImpl;
    FmFormShell*    pFormShell;

    void Init();
    void SetFormShell( FmFormShell* pShell ) { pFormShell = pShell; }
    FmFormShell* GetFormShell() const { return pFormShell; }

public:
    TYPEINFO();

    FmFormView(FmFormModel* pModel, OutputDevice* pOut);
//STRIP001  FmFormView(FmFormModel* pModel, ExtOutputDevice* pOut);
//STRIP001  FmFormView(FmFormModel* pModel);
    virtual ~FmFormView();

    /** create a control pair (label/bound control) for the database field description given.
        @param rFieldDesc
            description of the field. see clipboard format SBA-FIELDFORMAT
        @deprecated
            This method is deprecated. Use the version with a ODataAccessDescriptor instead.
    */
//STRIP001  SdrObject*   CreateFieldControl(const UniString& rFieldDesc) const;

    /** create a control pair (label/bound control) for the database field description given.
    */
//STRIP001  SdrObject*   CreateFieldControl( const ::svx::ODataAccessDescriptor& _rColumnDescriptor );

    virtual void MarkListHasChanged();
//STRIP001  virtual void AddWin(OutputDevice* pWin1);
    virtual void DelWin(OutputDevice* pWin1);

    virtual SdrPageView* ShowPage(SdrPage* pPage, const Point& rOffs);
    virtual void HidePage(SdrPageView* pPV);

    // for copying complete form structures, not only control models
//STRIP001  virtual SdrModel* GetMarkedObjModel() const;
//STRIP001  virtual sal_Bool Paste(const SdrModel& rMod, const Point& rPos, SdrObjList* pLst=NULL, sal_uInt32 nOptions=0);

    /** grab the focus to the first form control on the view
        @param _bForceSync
            <TRUE/> if the handling should be done synchronously.
    */
//STRIP001  void    GrabFirstControlFocus( sal_Bool _bForceSync = sal_False );

    // SdrView
    BOOL KeyInput(const KeyEvent& rKEvt, Window* pWin);

protected:
    void ActivateControls(SdrPageView*);
    void DeactivateControls(SdrPageView*);

    // Hinweis an die UI, daﬂ ein Control erzeugt worden ist
//STRIP001  void ObjectCreated(FmFormObj* pObj);
    void ChangeDesignMode(sal_Bool bDesign);

public:
    FmXFormView* GetImpl() const {return pImpl;}

//STRIP001  virtual void InsertControlContainer(const ::com::sun::star::uno::Reference< ::com::sun::star::awt::XControlContainer >& xCC);
//STRIP001  virtual void RemoveControlContainer(const ::com::sun::star::uno::Reference< ::com::sun::star::awt::XControlContainer >& xCC);
private:
    const OutputDevice* GetActualOutDev() const {return pActualOutDev;}
    void AdjustMarks(const SdrMarkList& rMarkList);
    sal_Bool checkUnMarkAll(const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface >& _xSource);
    FmFormObj* getMarkedGrid() const;
};

#endif          // _FML_FMVIEW_HXX

