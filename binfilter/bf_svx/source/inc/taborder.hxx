/*************************************************************************
 *
 *  $RCSfile: taborder.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:44:36 $
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
#ifndef _SVX_TABORDER_HXX
#define _SVX_TABORDER_HXX

#ifndef _SVTREEBOX_HXX
#include <svtools/svtreebx.hxx>
#endif

#ifndef _COM_SUN_STAR_AWT_XTABCONTROLLERMODEL_HPP_
#include <com/sun/star/awt/XTabControllerModel.hpp>
#endif
#ifndef _COM_SUN_STAR_AWT_XCONTROLCONTAINER_HPP_
#include <com/sun/star/awt/XControlContainer.hpp>
#endif

#ifndef _DIALOG_HXX //autogen
#include <vcl/dialog.hxx>
#endif

#ifndef _BUTTON_HXX //autogen
#include <vcl/button.hxx>
#endif

#ifndef _SV_LSTBOX_HXX //autogen
#include <vcl/lstbox.hxx>
#endif

#ifndef _FIXED_HXX //autogen
#include <vcl/fixed.hxx>
#endif

#ifndef _TOOLS_LIST_HXX
#include <tools/list.hxx>
#endif

#ifndef _SVX_FMEXCH_HXX
#include "fmexch.hxx"
#endif

class SdrModel;
class ImageList;

#ifndef _COMPHELPER_UNO3_HXX_
#include <comphelper/uno3.hxx>
#endif
FORWARD_DECLARE_INTERFACE(beans,XPropertySet)
namespace binfilter {
//STRIP008 FORWARD_DECLARE_INTERFACE(beans,XPropertySet)

//========================================================================
class FmOrderTreeListBox : public SvTreeListBox
{
protected:
    ::binfilter::svxform::OControlExchangeHelper    m_aFieldExchange;//STRIP008     ::svxform::OControlExchangeHelper   m_aFieldExchange;

public:
    FmOrderTreeListBox( Window* pParent );
    FmOrderTreeListBox( Window* pParent, const ResId& rResId  );
    virtual ~FmOrderTreeListBox();

//STRIP001  void            MoveSelection( long nRelPos );

protected:
    virtual sal_Int8    AcceptDrop( const AcceptDropEvent& rEvt );
    virtual sal_Int8    ExecuteDrop( const ExecuteDropEvent& rEvt );
    virtual void        StartDrag( sal_Int8 nAction, const Point& rPosPixel );
};


//========================================================================
class FmFormShell;
class FmTabOrderDlg : public ModalDialog
{
    ::com::sun::star::uno::Reference< ::com::sun::star::awt::XTabControllerModel >      xTempModel, // Model zum Bearbeiten der TabReihenfolge
                                xModel;     // Model mit der zu veraendernden TabReihenfolge

    ::com::sun::star::uno::Reference< ::com::sun::star::awt::XControlContainer >        xControlContainer;
    ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >    m_xORB;
    SdrModel*                   pDrawModel;

    FixedText                   aFT_Controls;
    FmOrderTreeListBox          aLB_Controls;

    OKButton                    aPB_OK;
    CancelButton                aPB_CANCEL;
    HelpButton                  aPB_HELP;

    PushButton                  aPB_MoveUp;
    PushButton                  aPB_MoveDown;
    PushButton                  aPB_AutoOrder;

    ImageList*                  pImageList;

    DECL_LINK( MoveUpClickHdl, Button* );
    DECL_LINK( MoveDownClickHdl, Button* );
    DECL_LINK( AutoOrderClickHdl, Button* );
    DECL_LINK( OKClickHdl, Button* );

//STRIP001  void FillList();
//STRIP001  Image GetImage(const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet > & xSet) const;

public:
    FmTabOrderDlg(  const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& _xORB,
                    Window* pParent, FmFormShell* pShell );
    virtual ~FmTabOrderDlg();

//STRIP001  void SetModified();
};

}//end of namespace binfilter
#endif

