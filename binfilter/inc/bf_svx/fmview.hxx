/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: fmview.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 03:33:52 $
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
namespace binfilter {
class ExtOutputDevice;
class FmFormModel;
class FmPageViewWinRec;
class FmFormObj;
class FmFormPage;
class FmFormShell;
class FmXFormView;

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
    virtual ~FmFormView();

    /** create a control pair (label/bound control) for the database field description given.
        @param rFieldDesc
            description of the field. see clipboard format SBA-FIELDFORMAT
        @deprecated
            This method is deprecated. Use the version with a ODataAccessDescriptor instead.
    */

    /** create a control pair (label/bound control) for the database field description given.
    */

    virtual void MarkListHasChanged();
    virtual void DelWin(OutputDevice* pWin1);

    virtual SdrPageView* ShowPage(SdrPage* pPage, const Point& rOffs);
    virtual void HidePage(SdrPageView* pPV);

    // for copying complete form structures, not only control models

    /** grab the focus to the first form control on the view
        @param _bForceSync
            <TRUE/> if the handling should be done synchronously.
    */

    // SdrView
    BOOL KeyInput(const KeyEvent& rKEvt, Window* pWin);

protected:
    void ActivateControls(SdrPageView*);
    void DeactivateControls(SdrPageView*);

    // Hinweis an die UI, da?ein Control erzeugt worden ist
    void ChangeDesignMode(sal_Bool bDesign);

public:
    FmXFormView* GetImpl() const {return pImpl;}

private:
    const OutputDevice* GetActualOutDev() const {return pActualOutDev;}
    void AdjustMarks(const SdrMarkList& rMarkList);
    sal_Bool checkUnMarkAll(const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface >& _xSource);
    FmFormObj* getMarkedGrid() const;
};

}//end of namespace binfilter
#endif          // _FML_FMVIEW_HXX

