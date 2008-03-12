/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: taborder.hxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 09:29:55 $
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
#ifndef _SVX_TABORDER_HXX
#define _SVX_TABORDER_HXX

#ifndef _SVTREEBOX_HXX
#include <bf_svtools/svtreebx.hxx>
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


#ifndef _FIXED_HXX //autogen
#include <vcl/fixed.hxx>
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


public:
    FmTabOrderDlg(  const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& _xORB,
                    Window* pParent, FmFormShell* pShell );
    virtual ~FmTabOrderDlg();

};

}//end of namespace binfilter
#endif

