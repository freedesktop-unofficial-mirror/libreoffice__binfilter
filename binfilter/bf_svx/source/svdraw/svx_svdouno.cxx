/*************************************************************************
 *
 *  $RCSfile: svx_svdouno.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:40:41 $
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

#ifndef _COM_SUN_STAR_CONTAINER_XCHILD_HPP_
#include <com/sun/star/container/XChild.hpp>
#endif
#ifndef _COM_SUN_STAR_AWT_XWINDOW_HPP_
#include <com/sun/star/awt/XWindow.hpp>
#endif
#ifndef _COM_SUN_STAR_AWT_POSSIZE_HPP_
#include <com/sun/star/awt/PosSize.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
#include <com/sun/star/beans/XPropertySet.hpp>
#endif
#ifndef _COM_SUN_STAR_IO_XPERSISTOBJECT_HPP_
#include <com/sun/star/io/XPersistObject.hpp>
#endif
#ifndef _COM_SUN_STAR_IO_XOUTPUTSTREAM_HPP_
#include <com/sun/star/io/XOutputStream.hpp>
#endif
#ifndef _COM_SUN_STAR_IO_XINPUTSTREAM_HPP_
#include <com/sun/star/io/XInputStream.hpp>
#endif
#ifndef _COM_SUN_STAR_IO_XACTIVEDATASINK_HPP_
#include <com/sun/star/io/XActiveDataSink.hpp>
#endif
#ifndef _COM_SUN_STAR_IO_XACTIVEDATASOURCE_HPP_
#include <com/sun/star/io/XActiveDataSource.hpp>
#endif
#ifndef _COM_SUN_STAR_IO_XOBJECTOUTPUTSTREAM_HPP_
#include <com/sun/star/io/XObjectOutputStream.hpp>
#endif
#ifndef _COM_SUN_STAR_IO_XOBJECTINPUTSTREAM_HPP_
#include <com/sun/star/io/XObjectInputStream.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_XCLONEABLE_HPP_
#include <com/sun/star/util/XCloneable.hpp>
#endif

#include <comphelper/processfactory.hxx>

#ifndef _SVDOUNO_HXX
#include "svdouno.hxx"
#endif
#ifndef _SVDXOUT_HXX
#include "svdxout.hxx"
#endif
#ifndef _SVDPAGV_HXX
#include "svdpagv.hxx"
#endif
#ifndef _SVDMODEL_HXX
#include "svdmodel.hxx"
#endif
#ifndef _SVDIO_HXX
#include "svdio.hxx"
#endif
#ifndef _SVDGLOB_HXX
#include "svdglob.hxx"  // Stringcache
#endif
#include "svdstr.hrc"   // Objektname
#ifndef _SVDETC_HXX
#include "svdetc.hxx"
#endif
#ifndef _SVDVIEW_HXX
#include "svdview.hxx"
#endif
#ifndef _SVDORECT_HXX
#include "svdorect.hxx"
#endif
#ifndef _SVDVITER_HXX
#include "svdviter.hxx"
#endif

#include <set>

using namespace ::rtl;
using namespace ::com::sun::star;

//************************************************************
//   Defines
//************************************************************

//************************************************************
//   Hilfsklasse SdrControlEventListenerImpl
//************************************************************

#ifndef _COM_SUN_STAR_LANG_XEVENTLISTENER_HPP_
#include <com/sun/star/lang/XEventListener.hpp>
#endif

#include <cppuhelper/implbase1.hxx>
namespace binfilter {

/*N*/ class SdrControlEventListenerImpl : public ::cppu::WeakImplHelper1< ::com::sun::star::lang::XEventListener >
/*N*/ {
/*N*/ protected:
/*N*/   SdrUnoObj*                  pObj;
/*N*/
/*N*/ public:
/*N*/   SdrControlEventListenerImpl(SdrUnoObj* _pObj)
/*N*/   :   pObj(_pObj)
/*N*/   {}
/*N*/
/*N*/   // XEventListener
/*N*/     virtual void SAL_CALL disposing( const ::com::sun::star::lang::EventObject& Source ) throw(::com::sun::star::uno::RuntimeException);
/*N*/
/*N*/   void StopListening(const uno::Reference< lang::XComponent >& xComp);
/*N*/   void StartListening(const uno::Reference< lang::XComponent >& xComp);
/*N*/ };

// XEventListener
/*N*/ void SAL_CALL SdrControlEventListenerImpl::disposing( const ::com::sun::star::lang::EventObject& Source )
/*N*/   throw(::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/   if (pObj)
/*N*/   {
/*N*/       pObj->xUnoControlModel = NULL;
/*N*/   }
/*N*/ }

/*N*/ void SdrControlEventListenerImpl::StopListening(const uno::Reference< lang::XComponent >& xComp)
/*N*/ {
/*N*/   if (xComp.is())
/*N*/       xComp->removeEventListener(this);
/*N*/ }

/*N*/ void SdrControlEventListenerImpl::StartListening(const uno::Reference< lang::XComponent >& xComp)
/*N*/ {
/*N*/   if (xComp.is())
/*N*/       xComp->addEventListener(this);
/*N*/ }

// -----------------------------------------------------------------------------
/*?*/ namespace
/*?*/ {
/*?*/     void lcl_ensureControlVisibility( SdrView* _pView, const SdrUnoObj* _pObject, bool _bVisible )
/*?*/     {
/*?*/         SdrPageView* pPageView = _pView ? _pView->GetPageView( _pObject->GetPage() ) : NULL;
/*?*/         DBG_ASSERT( pPageView, "lcl_ensureControlVisibility: no view found!" );
/*?*/
/*?*/         if ( pPageView )
/*?*/         {
/*?*/             // loop through all the views windows
/*?*/             const SdrPageViewWinList& rViewWins = pPageView->GetWinList();
/*?*/             USHORT nWins = rViewWins.GetCount();
/*?*/             for ( USHORT i=0; i<nWins; ++i )
/*?*/             {
/*?*/                 const SdrPageViewWinRec& rWinData = rViewWins[i];
/*?*/
/*?*/                 // loop through all controls in this window
/*?*/                 const SdrUnoControlList& rControlsInThisWin = rWinData.GetControlList();
/*?*/                 USHORT nControlsInThisWin = rControlsInThisWin.GetCount();
/*?*/                 for ( USHORT j=0; j<nControlsInThisWin; ++j )
/*?*/                 {
/*?*/                     const SdrUnoControlRec& rControlData = rControlsInThisWin[j];
/*?*/                     if ( rControlData.GetUnoObj() == _pObject )
/*?*/                     {
/*?*/                         // yep - this control is the representation of the given FmFormObj in the
/*?*/                         // given view
/*?*/                         // is the control in alive mode?
/*?*/                         uno::Reference< awt::XControl > xControl( rControlData.GetControl(), uno::UNO_QUERY );
/*?*/                         DBG_ASSERT( xControl.is(), "lcl_ensureControlVisibility: no control!" );
/*?*/                         if ( xControl.is() && !xControl->isDesignMode() )
/*?*/                         {
/*?*/                             // yes, alive mode. Is the visibility correct?
/*?*/                             if ( (bool)rControlData.IsVisible() != _bVisible )
/*?*/                             {
/*?*/                                 // no -> adjust it
/*?*/                                 uno::Reference< awt::XWindow > xControlWindow( xControl, uno::UNO_QUERY );
/*?*/                                 DBG_ASSERT( xControlWindow.is(), "lcl_ensureControlVisibility: the control is no window!" );
/*?*/                                 if ( xControlWindow.is() )
/*?*/                                 {
/*?*/                                     xControlWindow->setVisible( _bVisible );
/*?*/                                     DBG_ASSERT( (bool)rControlData.IsVisible() == _bVisible, "lcl_ensureControlVisibility: this didn't work!" );
/*?*/                                         // now this would mean that either IsVisible is not reliable (which would
/*?*/                                         // be bad 'cause we used it above) or that showing/hiding the window
/*?*/                                         // did not work as intended.
/*?*/                                 }
/*?*/                             }
/*?*/                         }
/*?*/                     }
/*?*/                 }
/*?*/             }
/*?*/         }
/*?*/     }
/*?*/ }

//************************************************************
//   SdrUnoObj
//************************************************************

/*N*/ TYPEINIT1(SdrUnoObj, SdrRectObj);

/*N*/ SdrUnoObj::SdrUnoObj(const String& rModelName, BOOL _bOwnUnoControlModel)
/*N*/ : bOwnUnoControlModel(_bOwnUnoControlModel)
/*N*/ {
/*N*/   bIsUnoObj = TRUE;
/*N*/
/*N*/   pEventListener = new SdrControlEventListenerImpl(this);
/*N*/   pEventListener->acquire();
/*N*/
/*N*/   // nur ein owner darf eigenstaendig erzeugen
/*N*/   if (rModelName.Len())
/*?*/   {DBG_BF_ASSERT(0, "STRIP");} //STRIP001     CreateUnoControlModel(rModelName);
/*N*/ }

/*?*/ SdrUnoObj::SdrUnoObj(const String& rModelName,
/*?*/                    const uno::Reference< lang::XMultiServiceFactory >& rxSFac,
/*?*/                    BOOL _bOwnUnoControlModel)
/*?*/ : bOwnUnoControlModel(_bOwnUnoControlModel)
/*?*/ {
/*?*/   bIsUnoObj = TRUE;
/*?*/
/*?*/   pEventListener = new SdrControlEventListenerImpl(this);
/*?*/   pEventListener->acquire();
/*?*/
/*?*/   // nur ein owner darf eigenstaendig erzeugen
/*?*/   if (rModelName.Len())
/*?*/       {DBG_BF_ASSERT(0, "STRIP"); }//STRIP001 CreateUnoControlModel(rModelName,rxSFac);
/*?*/ }

/*N*/ SdrUnoObj::~SdrUnoObj()
/*N*/ {
/*N*/   uno::Reference< lang::XComponent > xComp(xUnoControlModel, uno::UNO_QUERY);
/*N*/   if (xComp.is())
/*N*/   {
/*N*/       // gehoert das Control seiner Umgebung?
/*N*/       uno::Reference< container::XChild > xContent(xUnoControlModel, uno::UNO_QUERY);
/*N*/       if (xContent.is() && !xContent->getParent().is())
/*N*/           xComp->dispose();
/*N*/       else
/*N*/           pEventListener->StopListening(xComp);
/*N*/   }
/*N*/   pEventListener->release();
/*N*/ }

/*N*/ void SdrUnoObj::SetModel(SdrModel* pNewModel)
/*N*/ {
/*N*/   SdrRectObj::SetModel(pNewModel);
/*N*/ }

/*N*/ void SdrUnoObj::SetPage(SdrPage* pNewPage)
/*N*/ {
/*N*/   SdrRectObj::SetPage(pNewPage);
/*N*/ }

//STRIP001 void SdrUnoObj::TakeObjInfo(SdrObjTransformInfoRec& rInfo) const
//STRIP001 {
//STRIP001  rInfo.bRotateFreeAllowed        =   FALSE;
//STRIP001  rInfo.bRotate90Allowed          =   FALSE;
//STRIP001  rInfo.bMirrorFreeAllowed        =   FALSE;
//STRIP001  rInfo.bMirror45Allowed          =   FALSE;
//STRIP001  rInfo.bMirror90Allowed          =   FALSE;
//STRIP001  rInfo.bTransparenceAllowed = FALSE;
//STRIP001  rInfo.bGradientAllowed = FALSE;
//STRIP001  rInfo.bShearAllowed             =   FALSE;
//STRIP001  rInfo.bEdgeRadiusAllowed        =   FALSE;
//STRIP001  rInfo.bNoOrthoDesired           =   FALSE;
//STRIP001  rInfo.bCanConvToPath            =   FALSE;
//STRIP001  rInfo.bCanConvToPoly            =   FALSE;
//STRIP001  rInfo.bCanConvToPathLineToArea  =   FALSE;
//STRIP001  rInfo.bCanConvToPolyLineToArea  =   FALSE;
//STRIP001  rInfo.bCanConvToContour = FALSE;
//STRIP001 }

//STRIP001 UINT16 SdrUnoObj::GetObjIdentifier() const
//STRIP001 {
//STRIP001  return UINT16(OBJ_UNO);
//STRIP001 }

/** helper class to restore graphics at <awt::XView> object after <SdrUnoObj::Paint>

    OD 08.05.2003 #109432#
    Restoration of graphics necessary to assure that paint on a window

    @author OD
*/
/*?*/ class RestoreXViewGraphics
/*?*/ {
/*?*/     private:
/*?*/         uno::Reference< awt::XView >        m_rXView;
/*?*/         uno::Reference< awt::XGraphics >    m_rXGraphics;
/*?*/
/*?*/     public:
/*?*/         RestoreXViewGraphics( const uno::Reference< awt::XView >& _rXView )
/*?*/         {
/*?*/              m_rXView = _rXView;
/*?*/              m_rXGraphics = m_rXView->getGraphics();
/*?*/         }
/*?*/         ~RestoreXViewGraphics()
/*?*/         {
/*?*/             m_rXView->setGraphics( m_rXGraphics );
/*?*/         }
/*?*/ };

//STRIP001 FASTBOOL SdrUnoObj::Paint(ExtOutputDevice& rXOut, const SdrPaintInfoRec& rInfoRec) const
//STRIP001 {
//STRIP001  const SdrPageView* pPV = rInfoRec.pPV;
//STRIP001  OutputDevice* pOut = rXOut.GetOutDev();
//STRIP001  OutDevType eOutDevType = pOut->GetOutDevType();
//STRIP001  const SdrUnoControlRec* pControlRec = NULL;
//STRIP001
//STRIP001  if (pPV && xUnoControlModel.is())
//STRIP001  {
//STRIP001      const SdrPageViewWinList& rWL = pPV->GetWinList();
//STRIP001      USHORT nWinNum = rWL.Find(pOut);
//STRIP001
//STRIP001      if (nWinNum == SDRPAGEVIEWWIN_NOTFOUND && eOutDevType == OUTDEV_VIRDEV)
//STRIP001      {
//STRIP001          // Controls koennen sich z.Z. noch nicht ins VDev zeichnen,
//STRIP001          // daher wird das korrespondierende, im ersten Window liegende
//STRIP001          // Control invalidiert (s.u.)
//STRIP001          if (rWL.GetCount() > 0)
//STRIP001          {
//STRIP001              // Liste enhaelt Windows, daher nehmen wir das erste
//STRIP001              nWinNum = 0;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      if (nWinNum != SDRPAGEVIEWWIN_NOTFOUND)
//STRIP001      {
//STRIP001          const SdrPageViewWinRec& rWR = rWL[nWinNum];
//STRIP001          const SdrUnoControlList& rControlList = rWR.GetControlList();
//STRIP001          USHORT nCtrlNum = rControlList.Find(xUnoControlModel);
//STRIP001
//STRIP001          if (nCtrlNum != SDRUNOCONTROL_NOTFOUND)
//STRIP001          {
//STRIP001              pControlRec = &rControlList[nCtrlNum];
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if (pControlRec && pControlRec->GetControl().is())
//STRIP001  {
//STRIP001         SdrUnoControlPaintGuard aLockForPaint( *const_cast< SdrUnoControlRec* >( pControlRec ) );
//STRIP001
//STRIP001      uno::Reference< awt::XControl > xUnoControl = pControlRec->GetControl();
//STRIP001
//STRIP001      uno::Reference< awt::XView > xView(xUnoControl, uno::UNO_QUERY);
//STRIP001      if (xView.is())
//STRIP001      {
//STRIP001             // OD 08.05.2003 #109432# - create helper object to restore graphics
//STRIP001             // at <awt::XView> object.
//STRIP001             RestoreXViewGraphics aRestXViewGraph( xView );
//STRIP001
//STRIP001             OutputDevice* pOut = rXOut.GetOutDev();
//STRIP001          const MapMode& rMap = pOut->GetMapMode();
//STRIP001          xView->setZoom((float) double(rMap.GetScaleX()),
//STRIP001                         (float) double(rMap.GetScaleY()));
//STRIP001
//STRIP001          BOOL bDesignMode = pPV->GetView().IsDesignMode();
//STRIP001
//STRIP001             uno::Reference< awt::XWindow > xWindow(xUnoControl, uno::UNO_QUERY);
//STRIP001             if (xWindow.is())
//STRIP001             {
//STRIP001                 Point aPixPos(pOut->LogicToPixel(aRect.TopLeft()));
//STRIP001                 Size aPixSize(pOut->LogicToPixel(aRect.GetSize()));
//STRIP001                 xWindow->setPosSize(aPixPos.X(), aPixPos.Y(),
//STRIP001                                     aPixSize.Width(), aPixSize.Height(),
//STRIP001                                     awt::PosSize::POSSIZE);
//STRIP001          }
//STRIP001
//STRIP001          BOOL bInvalidatePeer = FALSE;
//STRIP001          if (eOutDevType == OUTDEV_WINDOW)
//STRIP001          {
//STRIP001              // Nicht wenn an der Stelle ein 'lebendes' Control liegt
//STRIP001              // das sich selber zeichnet.
//STRIP001              if (bDesignMode || pPV->GetView().IsPrintPreview())
//STRIP001              {
//STRIP001                  if (pPV->GetView().IsPrintPreview())
//STRIP001                  {
//STRIP001                      uno::Reference< awt::XGraphics > x( pOut->CreateUnoGraphics()); // UNO3
//STRIP001                      xView->setGraphics( x );
//STRIP001                  }
//STRIP001
//STRIP001                  // don't draw if we're in print preview and the control isn't printable
//STRIP001                  // FS - 10/06/99
//STRIP001                  BOOL bDrawIt = TRUE;
//STRIP001                  if (pPV->GetView().IsPrintPreview())
//STRIP001                  {
//STRIP001                      uno::Reference< beans::XPropertySet > xP(xUnoControl->getModel(), uno::UNO_QUERY);
//STRIP001                      if (xP.is())
//STRIP001                      {
//STRIP001                          uno::Reference< beans::XPropertySetInfo > xPropInfo = xP->getPropertySetInfo();
//STRIP001                          if( xPropInfo.is() && xPropInfo->hasPropertyByName( ::rtl::OUString::createFromAscii("Printable")) )
//STRIP001                          {
//STRIP001                              uno::Any aVal( xP->getPropertyValue( ::rtl::OUString::createFromAscii("Printable")) );
//STRIP001                              if( aVal.hasValue() && aVal.getValueType() == ::getCppuBooleanType() )
//STRIP001                                  bDrawIt = *(sal_Bool*)aVal.getValue();
//STRIP001                          }
//STRIP001                          else
//STRIP001                              bDrawIt = FALSE;
//STRIP001                      }
//STRIP001                      else
//STRIP001                          bDrawIt = FALSE;
//STRIP001                  }
//STRIP001
//STRIP001                  if (bDrawIt)
//STRIP001                  {
//STRIP001                      if( pPV->GetView().IsFillDraft() )
//STRIP001                      {
//STRIP001                          const SfxItemSet& rSet = GetItemSet();
//STRIP001
//STRIP001                          // perepare ItemSet to avoid old XOut filling
//STRIP001                          SfxItemSet aEmptySet(*rSet.GetPool());
//STRIP001                          aEmptySet.Put(XFillStyleItem(XFILL_NONE));
//STRIP001                          rXOut.SetFillAttr(aEmptySet);
//STRIP001
//STRIP001                          rXOut.SetLineAttr(rSet);
//STRIP001
//STRIP001                          rXOut.DrawRect( aRect );
//STRIP001                      }
//STRIP001                      else
//STRIP001                      {
//STRIP001                          Point aP = pOut->LogicToPixel(aRect.TopLeft());
//STRIP001                          xView->draw(aP.X(), aP.Y());
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001              else if ( xUnoControl->isTransparent() )
//STRIP001              {
//STRIP001                  bInvalidatePeer = TRUE;
//STRIP001              }
//STRIP001          }
//STRIP001          else if (eOutDevType == OUTDEV_PRINTER || eOutDevType == OUTDEV_VIRDEV)
//STRIP001          {
//STRIP001              uno::Reference< beans::XPropertySet > xP(xUnoControl->getModel(), uno::UNO_QUERY);
//STRIP001              if (xP.is())
//STRIP001              {
//STRIP001                  uno::Reference< beans::XPropertySetInfo > xPropInfo = xP->getPropertySetInfo();
//STRIP001                  if( xPropInfo.is() && xPropInfo->hasPropertyByName( ::rtl::OUString::createFromAscii("Printable")) )
//STRIP001                  {
//STRIP001                      uno::Any aVal( xP->getPropertyValue( ::rtl::OUString::createFromAscii("Printable")) );
//STRIP001                      if( aVal.hasValue() && aVal.getValueType() == ::getCppuBooleanType() && *(sal_Bool*)aVal.getValue() )
//STRIP001                      {
//STRIP001                          uno::Reference< awt::XGraphics > x = pOut->CreateUnoGraphics(); // UNO3
//STRIP001                          xView->setGraphics( x );
//STRIP001                          Point aP = pOut->LogicToPixel(aRect.TopLeft());
//STRIP001                          xView->draw(aP.X(), aP.Y());
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001             else
//STRIP001              DBG_ERROR( "SdrUnoObj::Paint: Ehm - what kind of device is this?" );
//STRIP001
//STRIP001          if ( bInvalidatePeer )
//STRIP001          {
//STRIP001              uno::Reference< awt::XWindowPeer > xPeer(xUnoControl->getPeer());
//STRIP001              if (xPeer.is())
//STRIP001              {
//STRIP001                  xPeer->invalidate(INVALIDATE_NOTRANSPARENT |
//STRIP001                                    INVALIDATE_CHILDREN);
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 SdrObject* SdrUnoObj::CheckHit(const Point& rPnt, USHORT nTol, const SetOfByte* pVisiLayer) const
//STRIP001 {
//STRIP001  return ImpCheckHit(rPnt, nTol, pVisiLayer, TRUE, TRUE);
//STRIP001 }

//STRIP001 void SdrUnoObj::TakeObjNameSingul(XubString& rName) const
//STRIP001 {
//STRIP001  rName = ImpGetResStr(STR_ObjNameSingulUno);
//STRIP001
//STRIP001  String aName( GetName() );
//STRIP001  if(aName.Len())
//STRIP001  {
//STRIP001      rName += sal_Unicode(' ');
//STRIP001      rName += sal_Unicode('\'');
//STRIP001      rName += aName;
//STRIP001      rName += sal_Unicode('\'');
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrUnoObj::TakeObjNamePlural(XubString& rName) const
//STRIP001 {
//STRIP001  rName = ImpGetResStr(STR_ObjNamePluralUno);
//STRIP001 }

//STRIP001 void SdrUnoObj::operator = (const SdrObject& rObj)
//STRIP001 {
//STRIP001  SdrRectObj::operator = (rObj);
//STRIP001
//STRIP001  // release the reference to the current control model
//STRIP001  SetUnoControlModel(uno::Reference< awt::XControlModel >());
//STRIP001
//STRIP001  aUnoControlModelTypeName = ((SdrUnoObj&) rObj).aUnoControlModelTypeName;
//STRIP001  aUnoControlTypeName = ((SdrUnoObj&) rObj).aUnoControlTypeName;
//STRIP001
//STRIP001  // copy the uno control model
//STRIP001  uno::Reference< awt::XControlModel > xCtrl( ((SdrUnoObj&) rObj).GetUnoControlModel(), uno::UNO_QUERY );
//STRIP001  uno::Reference< util::XCloneable > xClone( xCtrl, uno::UNO_QUERY );
//STRIP001
//STRIP001  if ( xClone.is() )
//STRIP001  {
//STRIP001      // copy the model by cloning
//STRIP001      uno::Reference< awt::XControlModel > xNewModel( xClone->createClone(), uno::UNO_QUERY );
//STRIP001      DBG_ASSERT( xNewModel.is(), "SdrUnoObj::operator =, no control model!");
//STRIP001      xUnoControlModel = xNewModel;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      // copy the model by streaming
//STRIP001      uno::Reference< io::XPersistObject > xObj( xCtrl, uno::UNO_QUERY );
//STRIP001      uno::Reference< lang::XMultiServiceFactory > xFactory( ::legacy_binfilters::getLegacyProcessServiceFactory() );
//STRIP001
//STRIP001      if ( xObj.is() && xFactory.is() )
//STRIP001      {
//STRIP001          // creating a pipe
//STRIP001          uno::Reference< io::XOutputStream > xOutPipe(xFactory->createInstance( ::rtl::OUString::createFromAscii("com.sun.star.io.Pipe")), uno::UNO_QUERY);
//STRIP001          uno::Reference< io::XInputStream > xInPipe(xOutPipe, uno::UNO_QUERY);
//STRIP001
//STRIP001          // creating the mark streams
//STRIP001          uno::Reference< io::XInputStream > xMarkIn(xFactory->createInstance( ::rtl::OUString::createFromAscii("com.sun.star.io.MarkableInputStream")), uno::UNO_QUERY);
//STRIP001          uno::Reference< io::XActiveDataSink > xMarkSink(xMarkIn, uno::UNO_QUERY);
//STRIP001
//STRIP001          uno::Reference< io::XOutputStream > xMarkOut(xFactory->createInstance( ::rtl::OUString::createFromAscii("com.sun.star.io.MarkableOutputStream")), uno::UNO_QUERY);
//STRIP001          uno::Reference< io::XActiveDataSource > xMarkSource(xMarkOut, uno::UNO_QUERY);
//STRIP001
//STRIP001          // connect mark and sink
//STRIP001          uno::Reference< io::XActiveDataSink > xSink(xFactory->createInstance( ::rtl::OUString::createFromAscii("com.sun.star.io.ObjectInputStream")), uno::UNO_QUERY);
//STRIP001
//STRIP001          // connect mark and source
//STRIP001          uno::Reference< io::XActiveDataSource > xSource(xFactory->createInstance( ::rtl::OUString::createFromAscii("com.sun.star.io.ObjectOutputStream")), uno::UNO_QUERY);
//STRIP001
//STRIP001          uno::Reference< io::XObjectOutputStream > xOutStrm(xSource, uno::UNO_QUERY);
//STRIP001          uno::Reference< io::XObjectInputStream > xInStrm(xSink, uno::UNO_QUERY);
//STRIP001
//STRIP001          if (xMarkSink.is() && xMarkSource.is() && xSink.is() && xSource.is())
//STRIP001          {
//STRIP001              xMarkSink->setInputStream(xInPipe);
//STRIP001              xMarkSource->setOutputStream(xOutPipe);
//STRIP001              xSink->setInputStream(xMarkIn);
//STRIP001              xSource->setOutputStream(xMarkOut);
//STRIP001
//STRIP001              // write the object to source
//STRIP001              xOutStrm->writeObject(xObj);
//STRIP001              xOutStrm->closeOutput();
//STRIP001              // read the object
//STRIP001              uno::Reference< awt::XControlModel > xModel(xInStrm->readObject(), uno::UNO_QUERY);
//STRIP001              xInStrm->closeInput();
//STRIP001
//STRIP001              DBG_ASSERT(xModel.is(), "SdrUnoObj::operator =, keine Model erzeugt");
//STRIP001
//STRIP001              xUnoControlModel = xModel;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // get service name of the control from the control model
//STRIP001  uno::Reference< beans::XPropertySet > xSet(xUnoControlModel, uno::UNO_QUERY);
//STRIP001  if (xSet.is())
//STRIP001  {
//STRIP001      uno::Any aValue( xSet->getPropertyValue( ::rtl::OUString::createFromAscii("DefaultControl")) );
//STRIP001      OUString aStr;
//STRIP001
//STRIP001      if( aValue >>= aStr )
//STRIP001          aUnoControlTypeName = String(aStr);
//STRIP001  }
//STRIP001
//STRIP001  uno::Reference< lang::XComponent > xComp(xUnoControlModel, uno::UNO_QUERY);
//STRIP001  if (xComp.is())
//STRIP001      pEventListener->StartListening(xComp);
//STRIP001 }

//STRIP001 FASTBOOL SdrUnoObj::HasSpecialDrag() const
//STRIP001 {
//STRIP001  return FALSE;
//STRIP001 }

/*N*/ void SdrUnoObj::VisAreaChanged(const OutputDevice* pOut)
/*N*/ {
/*N*/   if (!xUnoControlModel.is())
/*N*/       return;
/*N*/
/*N*/   if (pOut)
/*N*/   {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
        // Nur dieses eine OutDev beruecksichtigen
//STRIP001 /*?*/        uno::Reference< awt::XWindow > xWindow(GetUnoControl(pOut), uno::UNO_QUERY);
//STRIP001 /*?*/        if (xWindow.is())
//STRIP001 /*?*/        {
//STRIP001 /*?*/            Rectangle aPixRect(pOut->LogicToPixel(aRect));
//STRIP001 /*?*/            xWindow->setPosSize(aPixRect.Left(), aPixRect.Top(),
//STRIP001 /*?*/                         aPixRect.GetWidth(), aPixRect.GetHeight(), awt::PosSize::POSSIZE);
//STRIP001 /*?*/        }
/*N*/   }
/*N*/   else if (pModel)
/*N*/   {
/*N*/       // Controls aller PageViews beruecksichtigen
/*N*/       USHORT nLstPos = pModel->GetListenerCount();
/*N*/       uno::Reference< awt::XWindow > xWindow;
/*N*/       Point aPixPos;
/*N*/       Size aPixSize;
/*N*/       SfxListener* pListener;
/*N*/       SdrPageView* pPV;
/*N*/       const SdrUnoControlRec* pControlRec = NULL;
/*N*/
/*N*/       for (; nLstPos ;)
/*N*/       {
/*N*/           pListener = pModel->GetListener(--nLstPos);
/*N*/
/*N*/           if (pListener && pListener->ISA(SdrPageView))
/*N*/           {
/*N*/               pPV = (SdrPageView*) pListener;
/*N*/               const SdrPageViewWinList& rWL = pPV->GetWinList();
/*N*/               USHORT nPos = rWL.GetCount();
/*N*/
/*N*/               for (; nPos ; )
/*N*/               {
/*N*/                   // Controls aller OutDevs beruecksichtigen
/*N*/                   const SdrPageViewWinRec& rWR = rWL[--nPos];
/*N*/                   const SdrUnoControlList& rControlList = rWR.GetControlList();
/*N*/                   USHORT nCtrlNum = rControlList.Find(xUnoControlModel);
/*N*/                   pControlRec = (nCtrlNum != SDRUNOCONTROL_NOTFOUND) ? &rControlList[nCtrlNum] : NULL;
/*N*/                   if (pControlRec)
/*N*/                   {
/*N*/                       xWindow = uno::Reference< awt::XWindow >(pControlRec->GetControl(), uno::UNO_QUERY);
/*N*/                       if (xWindow.is())
/*N*/                       {
/*N*/                           // #62560 Pixelverschiebung weil mit einem Rechteck
/*N*/                           // und nicht mit Point, Size gearbeitet wurde
/*N*/                           aPixPos = rWR.GetOutputDevice()->LogicToPixel(aRect.TopLeft());
/*N*/                           aPixSize = rWR.GetOutputDevice()->LogicToPixel(aRect.GetSize());
/*N*/                           xWindow->setPosSize(aPixPos.X(), aPixPos.Y(),
/*N*/                                               aPixSize.Width(), aPixSize.Height(),
/*N*/                                               awt::PosSize::POSSIZE);
/*N*/                       }
/*N*/                   }
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ void SdrUnoObj::NbcResize(const Point& rRef, const Fraction& xFact, const Fraction& yFact)
/*N*/ {
/*N*/   SdrRectObj::NbcResize(rRef,xFact,yFact);
/*N*/
/*N*/   if (aGeo.nShearWink!=0 || aGeo.nDrehWink!=0)
/*N*/   {
/*N*/       // kleine Korrekturen
/*?*/       if (aGeo.nDrehWink>=9000 && aGeo.nDrehWink<27000)
/*?*/       {
/*?*/           aRect.Move(aRect.Left()-aRect.Right(),aRect.Top()-aRect.Bottom());
/*?*/       }
/*?*/
/*?*/       aGeo.nDrehWink  = 0;
/*?*/       aGeo.nShearWink = 0;
/*?*/       aGeo.nSin       = 0.0;
/*?*/       aGeo.nCos       = 1.0;
/*?*/       aGeo.nTan       = 0.0;
/*?*/       SetRectsDirty();
/*N*/   }
/*N*/
/*N*/   VisAreaChanged();
/*N*/ }

/*N*/ void SdrUnoObj::NbcMove(const Size& rSize)
/*N*/ {
/*N*/   SdrRectObj::NbcMove(rSize);
/*N*/   VisAreaChanged();
/*N*/ }

/*N*/ void SdrUnoObj::NbcSetSnapRect(const Rectangle& rRect)
/*N*/ {
/*N*/   SdrRectObj::NbcSetSnapRect(rRect);
/*N*/   VisAreaChanged();
/*N*/ }

/*N*/ void SdrUnoObj::NbcSetLogicRect(const Rectangle& rRect)
/*N*/ {
/*N*/   SdrRectObj::NbcSetLogicRect(rRect);
/*N*/   VisAreaChanged();
/*N*/ }

// -----------------------------------------------------------------------------
/*N*/ void SdrUnoObj::NbcSetLayer( SdrLayerID _nLayer )
/*N*/ {
/*N*/     if ( GetLayer() == _nLayer )
/*N*/     {   // redundant call -> not interested in doing anything here
/*N*/         SdrRectObj::NbcSetLayer( _nLayer );
/*N*/         return;
/*N*/     }
/*N*/
/*N*/     // we need some special handling here in case we're moved from an invisible layer
/*N*/     // to a visible one, or vice versa
/*N*/     // (relative to a layer. Remember that the visibility of a layer is a view attribute
/*N*/     // - the same layer can be visible in one view, and invisible in another view, at the
/*N*/     // same time)
/*N*/     // 2003-06-03 - #110592# - fs@openoffice.org
/*N*/
/*N*/     // collect all views in which our old layer is visible
/*N*/     ::std::set< SdrView* > aPreviouslyVisible;
/*N*/
/*N*/     {
/*N*/         SdrViewIter aIter( this );
/*N*/         for ( SdrView* pView = aIter.FirstView(); pView; pView = aIter.NextView() )
/*N*/             aPreviouslyVisible.insert( pView );
/*N*/     }
/*N*/
/*N*/     SdrRectObj::NbcSetLayer( _nLayer );
/*N*/
/*N*/     // collect all views in which our new layer is visible
/*N*/     ::std::set< SdrView* > aNewlyVisible;
/*N*/
/*N*/     {
/*N*/         SdrViewIter aIter( this );
/*N*/       for ( SdrView* pView = aIter.FirstView(); pView; pView = aIter.NextView() )
/*N*/         {
/*N*/             ::std::set< SdrView* >::const_iterator aPrevPos = aPreviouslyVisible.find( pView );
/*N*/             if ( aPreviouslyVisible.end() != aPrevPos )
/*N*/             {   // in pView, we were visible _before_ the layer change, and are
/*N*/                 // visible _after_ the layer change, too
/*N*/                 // -> we're not interested in this view at all
/*N*/                 aPreviouslyVisible.erase( aPrevPos );
/*N*/             }
/*N*/             else
/*N*/             {
/*N*/                 // in pView, we were visible _before_ the layer change, and are
/*N*/                 // _not_ visible after the layer change
/*N*/                 // => remember this view, as our visibility there changed
/*N*/                 aNewlyVisible.insert( pView );
/*N*/             }
/*N*/         }
/*N*/     }
/*N*/
/*N*/     // now aPreviouslyVisible contains all views where we became invisible
/*N*/     ::std::set< SdrView* >::const_iterator aLoopViews;
/*N*/     for (   aLoopViews = aPreviouslyVisible.begin();
/*N*/             aLoopViews != aPreviouslyVisible.end();
/*N*/             ++aLoopViews
/*N*/         )
/*N*/     {
/*N*/         lcl_ensureControlVisibility( *aLoopViews, this, false );
/*N*/     }
/*N*/
/*N*/     // and aNewlyVisible all views where we became visible
/*N*/     for (   aLoopViews = aNewlyVisible.begin();
/*N*/             aLoopViews != aNewlyVisible.end();
/*N*/             ++aLoopViews
/*N*/         )
/*N*/     {
/*N*/         lcl_ensureControlVisibility( *aLoopViews, this, true );
/*N*/     }
/*N*/ }

//STRIP001 void SdrUnoObj::CreateUnoControlModel(const String& rModelName)
//STRIP001 {
//STRIP001  DBG_ASSERT(!xUnoControlModel.is(), "model already exists");
//STRIP001
//STRIP001  aUnoControlModelTypeName = rModelName;
//STRIP001
//STRIP001  uno::Reference< awt::XControlModel >   xModel;
//STRIP001  uno::Reference< lang::XMultiServiceFactory > xFactory( ::legacy_binfilters::getLegacyProcessServiceFactory() );
//STRIP001  if (aUnoControlModelTypeName.Len() && xFactory.is() )
//STRIP001  {
//STRIP001      xModel = uno::Reference< awt::XControlModel >(xFactory->createInstance(
//STRIP001          aUnoControlModelTypeName), uno::UNO_QUERY);
//STRIP001
//STRIP001      if (xModel.is())
//STRIP001          SetChanged();
//STRIP001  }
//STRIP001
//STRIP001  SetUnoControlModel(xModel);
//STRIP001 }

//STRIP001 void SdrUnoObj::CreateUnoControlModel(const String& rModelName,
//STRIP001                                    const uno::Reference< lang::XMultiServiceFactory >& rxSFac)
//STRIP001 {
//STRIP001  DBG_ASSERT(!xUnoControlModel.is(), "model already exists");
//STRIP001
//STRIP001  aUnoControlModelTypeName = rModelName;
//STRIP001
//STRIP001  uno::Reference< awt::XControlModel >   xModel;
//STRIP001  if (aUnoControlModelTypeName.Len() && rxSFac.is() )
//STRIP001  {
//STRIP001      xModel = uno::Reference< awt::XControlModel >(rxSFac->createInstance(
//STRIP001          aUnoControlModelTypeName), uno::UNO_QUERY);
//STRIP001
//STRIP001      if (xModel.is())
//STRIP001          SetChanged();
//STRIP001  }
//STRIP001
//STRIP001  SetUnoControlModel(xModel);
//STRIP001 }

/*N*/ void SdrUnoObj::WriteData(SvStream& rOut) const
/*N*/ {
/*N*/   SdrRectObj::WriteData(rOut);
/*N*/   SdrDownCompat aCompat(rOut, STREAM_WRITE); // Fuer Abwaertskompatibilitaet (Lesen neuer Daten mit altem Code)
/*N*/
/*N*/ #ifdef DBG_UTIL
/*N*/   aCompat.SetID("SdrUnoObj");
/*N*/ #endif
/*N*/
/*N*/   if (bOwnUnoControlModel)                    // nur als besitzt des Models dieses auch schreiben
/*N*/   {
/*?*/       // UNICODE: rOut << aUnoControlModelTypeName;
/*?*/       rOut.WriteByteString(aUnoControlModelTypeName);
/*N*/   }
/*N*/ }

/*N*/ void SdrUnoObj::ReadData(const SdrObjIOHeader& rHead, SvStream& rIn)
/*N*/ {
/*N*/   if (rIn.GetError() != 0)
/*N*/       return;
/*N*/
/*N*/   SdrRectObj::ReadData(rHead,rIn);
/*N*/
/*N*/   SdrDownCompat aCompat(rIn, STREAM_READ);    // Fuer Abwaertskompatibilitaet (Lesen neuer Daten mit altem Code)
/*N*/
/*N*/ #ifdef DBG_UTIL
/*N*/   aCompat.SetID("SdrUnoObj");
/*N*/ #endif
/*N*/
/*N*/   if (bOwnUnoControlModel)                    // nur als besitzt des Models dieses auch lesen
/*N*/   {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/        // UNICODE: rIn >> aUnoControlModelTypeName;
//STRIP001 /*?*/        rIn.ReadByteString(aUnoControlModelTypeName);
//STRIP001 /*?*/
//STRIP001 /*?*/        CreateUnoControlModel(aUnoControlModelTypeName);
/*N*/   }
/*N*/ }

/*N*/ void SdrUnoObj::SetUnoControlModel( uno::Reference< awt::XControlModel > xModel)
/*N*/ {
/*N*/   if (xUnoControlModel.is())
/*N*/   {
/*?*/       uno::Reference< lang::XComponent > xComp(xUnoControlModel, uno::UNO_QUERY);
/*?*/       if (xComp.is())
/*?*/           pEventListener->StopListening(xComp);
/*?*/
/*?*/       if (pModel)
/*?*/       {
/*?*/           SdrHint aHint(*this);
/*?*/           aHint.SetKind(HINT_CONTROLREMOVED);
/*?*/           pModel->Broadcast(aHint);
/*?*/       }
/*N*/   }
/*N*/
/*N*/   xUnoControlModel = xModel;
/*N*/
/*N*/   // control model muss servicename des controls enthalten
/*N*/   if (xUnoControlModel.is())
/*N*/   {
/*N*/       uno::Reference< beans::XPropertySet > xSet(xUnoControlModel, uno::UNO_QUERY);
/*N*/       if (xSet.is())
/*N*/       {
/*N*/           uno::Any aValue( xSet->getPropertyValue(String("DefaultControl", gsl_getSystemTextEncoding())) );
/*N*/           OUString aStr;
/*N*/           if( aValue >>= aStr )
/*N*/               aUnoControlTypeName = String(aStr);
/*N*/       }
/*N*/
/*N*/       uno::Reference< lang::XComponent > xComp(xUnoControlModel, uno::UNO_QUERY);
/*N*/       if (xComp.is())
/*N*/           pEventListener->StartListening(xComp);
/*N*/
/*N*/       if (pModel)
/*N*/       {
/*N*/           SdrHint aHint(*this);
/*N*/           aHint.SetKind(HINT_CONTROLINSERTED);
/*N*/           pModel->Broadcast(aHint);
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ uno::Reference< awt::XControl > SdrUnoObj::GetUnoControl(const OutputDevice* pOut) const
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); return uno::Reference< awt::XControl >();//STRIP001
//STRIP001  uno::Reference< awt::XControl > xUnoControl;
//STRIP001
//STRIP001  if (pModel && xUnoControlModel.is())
//STRIP001  {
//STRIP001      USHORT nLstCnt = pModel->GetListenerCount();
//STRIP001
//STRIP001      for (USHORT nLst = 0; nLst < nLstCnt && !xUnoControl.is(); nLst++ )
//STRIP001      {
//STRIP001          // Unter allen Listenern die PageViews suchen
//STRIP001          SfxListener* pListener = pModel->GetListener(nLst);
//STRIP001
//STRIP001          if (pListener && pListener->ISA(SdrPageView))
//STRIP001          {
//STRIP001              // PageView gefunden
//STRIP001              SdrPageView* pPV = (SdrPageView*) pListener;
//STRIP001              const SdrPageViewWinList& rWL = pPV->GetWinList();
//STRIP001              USHORT nWRCnt = rWL.GetCount();
//STRIP001              for (USHORT nWR = 0; nWR < nWRCnt && !xUnoControl.is(); nWR++)
//STRIP001              {
//STRIP001                  // Alle WinRecords der PageView untersuchen
//STRIP001                  const SdrPageViewWinRec& rWR = rWL[nWR];
//STRIP001                  if (pOut == rWR.GetOutputDevice())
//STRIP001                  {
//STRIP001                      // Richtiges OutputDevice gefunden
//STRIP001                      // Darin nun das Control suchen
//STRIP001                      const SdrUnoControlList& rControlList = rWR.GetControlList();
//STRIP001                      USHORT nCtrlNum = rControlList.Find(xUnoControlModel);
//STRIP001                      if (nCtrlNum != SDRUNOCONTROL_NOTFOUND)
//STRIP001                      {
//STRIP001                          const SdrUnoControlRec* pControlRec = &rControlList[nCtrlNum];
//STRIP001                          if (pControlRec && pControlRec->GetControl().is())
//STRIP001                          {
//STRIP001                              xUnoControl = pControlRec->GetControl();
//STRIP001                          }
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return xUnoControl;
/*N*/ }

//STRIP001 OutputDevice* SdrUnoObj::GetOutputDevice(uno::Reference< awt::XControl > _xControl) const
//STRIP001 {
//STRIP001  OutputDevice* pOut = NULL;
//STRIP001  if (pModel && xUnoControlModel.is() && _xControl.is() && _xControl->getModel() == xUnoControlModel)
//STRIP001  {
//STRIP001      USHORT nLstCnt = pModel->GetListenerCount();
//STRIP001      for (USHORT nLst = 0; nLst < nLstCnt && !pOut; nLst++ )
//STRIP001      {
//STRIP001          // Unter allen Listenern die PageViews suchen
//STRIP001          SfxListener* pListener = pModel->GetListener(nLst);
//STRIP001          if (pListener && pListener->ISA(SdrPageView))
//STRIP001          {
//STRIP001              // PageView gefunden
//STRIP001              SdrPageView* pPV = (SdrPageView*) pListener;
//STRIP001              if (pPV)
//STRIP001              {
//STRIP001                  const SdrPageViewWinList& rWL = pPV->GetWinList();
//STRIP001                  USHORT nWRCnt = rWL.GetCount();
//STRIP001                  for (USHORT nWR = 0; nWR < nWRCnt && !pOut; nWR++)
//STRIP001                  {
//STRIP001                      // Alle WinRecords der PageView untersuchen
//STRIP001                      const SdrPageViewWinRec& rWR = rWL[nWR];
//STRIP001                      const SdrUnoControlList& rControlList = rWR.GetControlList();
//STRIP001                      if (SDRUNOCONTROL_NOTFOUND != rWR.GetControlList().Find(_xControl))
//STRIP001                          pOut = rWR.GetOutputDevice();
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return pOut;
//STRIP001 }


}
