/*************************************************************************
 *
 *  $RCSfile: fmPropBrw.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:22:00 $
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
 *  Source License Version 1.1 (the License); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an AS IS basis,
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
#ifndef SVX_FMPROPBRW_HXX
#define SVX_FMPROPBRW_HXX

#ifndef _COM_SUN_STAR_LANG_XMULTISERVICEFACTORY_HPP_
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
#include <com/sun/star/beans/XPropertySet.hpp>
#endif
#ifndef _COM_SUN_STAR_AWT_XCONTROLCONTAINER_HPP_
#include <com/sun/star/awt/XControlContainer.hpp>
#endif
#ifndef _COM_SUN_STAR_FRAME_XFRAME_HPP_
#include <com/sun/star/frame/XFrame.hpp>
#endif
#ifndef _BASEDLGS_HXX
#include <bf_sfx2/basedlgs.hxx>
#endif
#ifndef _SFXCTRLITEM_HXX
#include <bf_sfx2/ctrlitem.hxx>
#endif
#ifndef _SFX_CHILDWIN_HXX
#include <bf_sfx2/childwin.hxx>
#endif

//========================================================================
class FmPropBrwMgr : public SfxChildWindow
{
protected:
    ::com::sun::star::uno::Reference< ::com::sun::star::awt::XControlContainer >
                    m_xUnoRepresentation;
public:
    FmPropBrwMgr(Window *pParent, sal_uInt16 nId, SfxBindings *pBindings, SfxChildWinInfo *pInfo);
    SFX_DECL_CHILDWINDOW(FmPropBrwMgr);
};

class FmPropControl;
class SfxBindings;
//========================================================================
//STRIP001 class FmPropBrw : public SfxFloatingWindow, public SfxControllerItem
//STRIP001 {
//STRIP001  sal_Bool        m_bInitialStateChange;
//STRIP001
//STRIP001  ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >
//STRIP001                  m_xORB;
//STRIP001  ::com::sun::star::uno::Reference< ::com::sun::star::frame::XFrame >
//STRIP001                  m_xMeAsFrame;
//STRIP001  ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >
//STRIP001                  m_xBrowserController;
//STRIP001  ::com::sun::star::uno::Reference< ::com::sun::star::awt::XWindow >
//STRIP001                  m_xBrowserComponentWindow;
//STRIP001
//STRIP001 protected:
//STRIP001  virtual void StateChanged(sal_uInt16 nSID, SfxItemState eState, const SfxPoolItem* pState);
//STRIP001  virtual void FillInfo( SfxChildWinInfo& rInfo ) const;
//STRIP001  virtual sal_Bool Close();
//STRIP001
//STRIP001  DECL_LINK( OnAsyncGetFocus, void* );
//STRIP001
//STRIP001  void implSetNewObject(
//STRIP001      const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >& _rxObject);
//STRIP001  void implDetachController();
//STRIP001
//STRIP001 public:
//STRIP001  FmPropBrw(const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >&   _xORB,
//STRIP001            SfxBindings *pBindings, SfxChildWindow *pMgr, Window* pParent);
//STRIP001  virtual ~FmPropBrw();
//STRIP001 };
#endif //SVX_FMPROPBRW_HXX
