/*************************************************************************
 *
 *  $RCSfile: svx_svdpagv.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:22:28 $
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

#ifndef _COM_SUN_STAR_AWT_XWINDOW_HPP_
#include <com/sun/star/awt/XWindow.hpp>
#endif
#ifndef _COM_SUN_STAR_AWT_XWINDOWLISTENER_HPP_
#include <com/sun/star/awt/XWindowListener.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
#include <com/sun/star/beans/XPropertySet.hpp>
#endif
#ifndef _COM_SUN_STAR_AWT_XCONTROLCONTAINER_HPP_
#include <com/sun/star/awt/XControlContainer.hpp>
#endif
#ifndef _COM_SUN_STAR_AWT_POSSIZE_HPP_
#include <com/sun/star/awt/PosSize.hpp>
#endif
#ifndef _COM_SUN_STAR_FORM_XIMAGEPRODUCERSUPPLIER_HPP_
#include <com/sun/star/form/XImageProducerSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_XMODECHANGEBROADCASTER_HPP_
#include <com/sun/star/util/XModeChangeBroadcaster.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_XCOMPONENT_HPP_
#include <com/sun/star/lang/XComponent.hpp>
#endif

#include <comphelper/processfactory.hxx>

#ifndef _VOS_MUTEX_HXX_
#include <vos/mutex.hxx>
#endif

#ifndef _SV_SVAPP_HXX
#include <vcl/svapp.hxx>
#endif
#ifndef _SV_WRKWIN_HXX
#include <vcl/wrkwin.hxx>
#endif

#ifdef OS2
#include <tools/svpm.h>
#include <vcl/sysdep.hxx>
#endif

#ifndef _TOOLKIT_HELPER_VCLUNOHELPER_HXX_
#include <toolkit/helper/vclunohelper.hxx>
#endif

#ifndef INCLUDED_SVTOOLS_COLORCFG_HXX
#include <svtools/colorcfg.hxx>
#endif

#include "svdedxv.hxx"
#include "svdpagv.hxx"
#include "svdoutl.hxx"
#include "svdpagv.hxx"
#include "outliner.hxx"
#include "xpoly.hxx"
#include "svdxout.hxx"
#include "svdetc.hxx"
#include "svdobj.hxx"
#include "svdouno.hxx"
#include "svdpage.hxx"
#include "svdio.hxx"
#include "svdview.hxx"
#include "svditer.hxx"
#include "svdogrp.hxx"
#include "svdtypes.hxx"

#include "svdotext.hxx" // fuer PaintOutlinerView
#include "svdoole2.hxx"
#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif

#pragma hdrstop

using namespace ::rtl;
using namespace ::com::sun::star;

/*N*/ TYPEINIT1(SdrPageView, SfxListener);


// Klasse muﬂ als listener fungieren, um den Zustand, ob ein Object sichtbar ist oder nicht
// festzuhalten
//------------------------------------------------------------------------------
/*N*/ SdrUnoControlRec::SdrUnoControlRec(SdrUnoControlList* _pParent, SdrUnoObj* _pObj, ::com::sun::star::uno::Reference< ::com::sun::star::awt::XControl > _xControl) throw()
/*N*/                :pObj(_pObj)
/*N*/                ,xControl(_xControl)
/*N*/                ,bVisible(TRUE)
/*N*/                ,bIsListening(FALSE)
/*N*/                ,bDisposed(FALSE)
/*N*/                ,pParent(_pParent)
/*N*/                  ,mnPaintLevel( 0 )
/*N*/ {
/*N*/     DBG_ASSERT( xControl.is(), "SdrUnoControlRec::SdrUnoControlRec: invalid control, this will crash!" );
/*N*/
/*N*/     bVisible = xControl.is() ? !xControl->isDesignMode() : TRUE;
/*N*/     bool bOldVisible = bVisible;
/*N*/
/*N*/     // if bVisible is TRUE here, then switchControlListening will also start
/*N*/     // DesignModeListening
/*N*/     switchControlListening( true );
/*N*/
/*N*/     // adjust the initial visibility according to the visibility of the layer
/*N*/     // 2003-06-03 - #110592# - fs@openoffice.org
/*N*/     adjustControlVisibility( true );
/*N*/
/*N*/     // no start this design mode listening
/*N*/     if ( bOldVisible && !bOldVisible )
/*N*/         // visibility changed from true to false -> explicitly
/*N*/         // start DesignModeListening
/*N*/         // 2003-07-18 - #110916# - fs@openoffice.org
/*N*/         switchDesignModeListening( true );
/*N*/ }

//------------------------------------------------------------------------------
/*N*/ SdrUnoControlRec::~SdrUnoControlRec() throw()
/*N*/ {
/*N*/ }

//------------------------------------------------------------------------------
/*?*/ void SdrUnoControlRec::adjustControlVisibility( bool _bForce )
/*?*/ {{DBG_ASSERT(0, "STRIP");}//STRIP001
//STRIP001     uno::Reference< awt::XWindow > xControlWindow( xControl, uno::UNO_QUERY );
//STRIP001     if ( xControlWindow.is() && !xControl->isDesignMode() )
//STRIP001     {
//STRIP001         // the layer of our object
//STRIP001         SdrLayerID nObjectLayer = pObj->GetLayer();
//STRIP001         // the SdrPageView we're living in
//STRIP001         SdrPageView& rView = pParent->rPageView;
//STRIP001         // is the layer we're residing in visible in this view?
//STRIP001         bool bIsObjectLayerVisible = rView.GetVisibleLayers().IsSet( nObjectLayer );
//STRIP001
//STRIP001         if ( _bForce || ( bIsObjectLayerVisible != bVisible ) )
//STRIP001             xControlWindow->setVisible( bIsObjectLayerVisible );
//STRIP001  }
//STRIP001
/*?*/ }

//------------------------------------------------------------------------------
/*?*/ void SdrUnoControlRec::switchControlListening( bool _bStart )
/*?*/ {{DBG_ASSERT(0, "STRIP");}//STRIP001
//STRIP001  uno::Reference< awt::XWindow> xWindow( xControl, uno::UNO_QUERY );
//STRIP001  if ( xWindow.is() )
//STRIP001  {
//STRIP001         // listen for visibility changes
//STRIP001         if ( _bStart )
//STRIP001          xWindow->addWindowListener( this );
//STRIP001         else
//STRIP001             xWindow->removeWindowListener( this );
//STRIP001
//STRIP001         if ( !bVisible )
//STRIP001             switchDesignModeListening( _bStart );
//STRIP001
//STRIP001      // Am Property fuer das DefaultControl lauschen um das Control eventuell auszutauschen
//STRIP001         switchPropertyListening( _bStart, false );
//STRIP001
//STRIP001         // listen for design mode changes
//STRIP001         uno::Reference< util::XModeChangeBroadcaster > xDesignModeChanges( xControl, uno::UNO_QUERY );
//STRIP001         if ( xDesignModeChanges.is() )
//STRIP001             if ( _bStart )
//STRIP001                 xDesignModeChanges->addModeChangeListener( this );
//STRIP001             else
//STRIP001                 xDesignModeChanges->removeModeChangeListener( this );
//STRIP001  }
/*?*/ }

//------------------------------------------------------------------------------
/*?*/ void SdrUnoControlRec::switchPropertyListening( bool _bStart, bool _bListenForAll )
/*?*/ {{DBG_ASSERT(0, "STRIP");}//STRIP001
//STRIP001     DBG_ASSERT( xControl.is(), "SdrUnoControlRec::switchPropertyListening: no control!" );
//STRIP001     if ( xControl.is() )
//STRIP001  {
//STRIP001         uno::Reference< beans::XPropertySet > xSet( xControl->getModel(), uno::UNO_QUERY );
//STRIP001         if ( xSet.is() )
//STRIP001         {
//STRIP001             ::rtl::OUString sPropertyToListenFor;
//STRIP001
//STRIP001             if ( !_bListenForAll )
//STRIP001      {
//STRIP001                 // listen for the DefaultControl property only, if available
//STRIP001                 ::rtl::OUString sDefaultControlPropertyName( RTL_CONSTASCII_USTRINGPARAM( "DefaultControl" ) );
//STRIP001          uno::Reference< beans::XPropertySetInfo > xPropInfo( xSet->getPropertySetInfo() );
//STRIP001              if ( xPropInfo.is() && xPropInfo->hasPropertyByName( sDefaultControlPropertyName ) )
//STRIP001                     sPropertyToListenFor = sDefaultControlPropertyName;
//STRIP001             }
//STRIP001
//STRIP001             if ( _bStart )
//STRIP001              xSet->addPropertyChangeListener( sPropertyToListenFor, this );
//STRIP001             else
//STRIP001                 xSet->removePropertyChangeListener( sPropertyToListenFor, this );
//STRIP001         }
//STRIP001      }
/*?*/ }

//------------------------------------------------------------------------------
/*N*/ void SAL_CALL SdrUnoControlRec::disposing( const ::com::sun::star::lang::EventObject& Source )
/*N*/   throw(::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/   uno::Reference< awt::XControl > xSource( Source.Source, uno::UNO_QUERY);
/*N*/   if (xSource.is())
/*?*/   {  {DBG_ASSERT(0, "STRIP");}//STRIP001  // it's the control we're responsible for
//STRIP001 /*?*/         switchControlListening( false );
//STRIP001 /*?*/
//STRIP001 /*?*/        if (pParent)
//STRIP001 /*?*/        {
//STRIP001 /*?*/            uno::Reference< uno::XInterface > xThis(*this);
//STRIP001 /*?*/            xControl = NULL;
//STRIP001 /*?*/            pObj = NULL;
//STRIP001 /*?*/
//STRIP001 /*?*/            // jetzt darf mich der Vater freigeben
//STRIP001 /*?*/            pParent->Disposing(this);
//STRIP001 /*?*/            pParent = NULL;
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/        bDisposed = TRUE;
/*N*/   }
/*N*/ }

//------------------------------------------------------------------------------

// XWindowListener
/*N*/ void SAL_CALL SdrUnoControlRec::windowResized( const ::com::sun::star::awt::WindowEvent& e )
/*N*/   throw(::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/ }

/*N*/ void SAL_CALL SdrUnoControlRec::windowMoved( const ::com::sun::star::awt::WindowEvent& e )
/*N*/   throw(::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/ }

/*N*/ void SAL_CALL SdrUnoControlRec::windowShown( const ::com::sun::star::lang::EventObject& e )
/*N*/   throw(::com::sun::star::uno::RuntimeException)
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001     if ( !mnPaintLevel )
//STRIP001     {
//STRIP001      if (!IsVisible())
//STRIP001             switchDesignModeListening( false );
//STRIP001     }
//STRIP001
//STRIP001  bVisible = TRUE;
/*N*/ }

//------------------------------------------------------------------------------
/*N*/ void SAL_CALL SdrUnoControlRec::windowHidden( const ::com::sun::star::lang::EventObject& e )
/*N*/   throw(::com::sun::star::uno::RuntimeException)
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  bVisible = FALSE;
//STRIP001
//STRIP001  // Im Designmodus ist das Control nicht sichtbar und der drawing layer ist
//STRIP001  // verantwortlich fuer die Darstellung des Controls
//STRIP001  // In diesem Fall auf Aenderungen an den Eigenschaften der Controls gelauscht,
//STRIP001  // um ein Repaint auszufuehren.
//STRIP001     if ( !mnPaintLevel )
//STRIP001     {
//STRIP001      if (!bDisposed)
//STRIP001          switchDesignModeListening( true );
//STRIP001     }
/*N*/ }

// XPropertyChangeListener
//------------------------------------------------------------------------------
/*N*/ void SAL_CALL SdrUnoControlRec::propertyChange( const ::com::sun::star::beans::PropertyChangeEvent& evt )
/*N*/   throw(::com::sun::star::uno::RuntimeException)
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  if (!xControl.is())
//STRIP001      return;
//STRIP001
//STRIP001  if (evt.PropertyName == rtl::OUString::createFromAscii("DefaultControl"))
//STRIP001  {
//STRIP001      // anlegen eines neuen Controls
//STRIP001      uno::Reference< lang::XMultiServiceFactory > xFactory( ::legacy_binfilters::getLegacyProcessServiceFactory() );
//STRIP001      if( xFactory.is() )
//STRIP001      {
//STRIP001          OUString aControlName;
//STRIP001          if(evt.NewValue >>= aControlName)
//STRIP001          {
//STRIP001              uno::Reference< awt::XControl > xUnoControl( xFactory->createInstance(aControlName), uno::UNO_QUERY);
//STRIP001              ReplaceControl(xUnoControl);
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      ::vos::OGuard aGuard(Application::GetSolarMutex());
//STRIP001      // Attributaenderung:
//STRIP001      // Bereich neu Zeichnen
//STRIP001      OutputDevice* pOut = pObj->GetOutputDevice(xControl);
//STRIP001      if (pOut && pOut->GetOutDevType() == OUTDEV_WINDOW)
//STRIP001          ((Window*)pOut)->Invalidate(pObj->GetBoundRect());
//STRIP001  }
/*N*/ }

// XImageConsumer
//------------------------------------------------------------------------------
/*N*/ void SAL_CALL SdrUnoControlRec::complete( sal_Int32 Status, const ::com::sun::star::uno::Reference< ::com::sun::star::awt::XImageProducer >& xProducer )
/*N*/   throw(::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/ }

//------------------------------------------------------------------------------
/*N*/ void SAL_CALL SdrUnoControlRec::init( sal_Int32 Width, sal_Int32 Height ) throw(::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/ }

/*N*/ void SAL_CALL SdrUnoControlRec::setColorModel( sal_Int16 BitCount, const ::com::sun::star::uno::Sequence< sal_Int32 >& RGBAPal, sal_Int32 RedMask, sal_Int32 GreenMask, sal_Int32 BlueMask, sal_Int32 AlphaMask ) throw(::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/ }

/*N*/ void SAL_CALL SdrUnoControlRec::setPixelsByBytes( sal_Int32 nX, sal_Int32 nY, sal_Int32 nWidth, sal_Int32 nHeight, const ::com::sun::star::uno::Sequence< sal_Int8 >& aProducerData, sal_Int32 nOffset, sal_Int32 nScanSize ) throw(::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/ }

/*N*/ void SAL_CALL SdrUnoControlRec::setPixelsByLongs( sal_Int32 nX, sal_Int32 nY, sal_Int32 nWidth, sal_Int32 nHeight, const ::com::sun::star::uno::Sequence< sal_Int32 >& aProducerData, sal_Int32 nOffset, sal_Int32 nScanSize ) throw(::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/ }

//------------------------------------------------------------------------------
/*?*/ void SAL_CALL SdrUnoControlRec::modeChanged( const util::ModeChangeEvent& _rSource ) throw (uno::RuntimeException)
/*?*/ {{DBG_ASSERT(0, "STRIP");}//STRIP001
//STRIP001     // if the control is part of a invisible layer, we need to explicitly hide it in alive mode
//STRIP001     // 2003-06-03 - #110592# - fs@openoffice.org
//STRIP001     adjustControlVisibility( false );
/*?*/ }

//------------------------------------------------------------------------------
/*N*/ void SdrUnoControlRec::Clear(BOOL bDispose)
/*N*/ {
/*N*/   if (xControl.is())
/*N*/   {
/*N*/         switchControlListening( false );
/*N*/
/*N*/       if (bDispose)
/*?*/           xControl->dispose();
/*N*/       xControl = NULL;
/*N*/   }
/*N*/ }

//------------------------------------------------------------------------------
//STRIP001 void SdrUnoControlRec::ReplaceControl(uno::Reference< awt::XControl > _xControl)
//STRIP001 {
//STRIP001  uno::Reference< awt::XWindow > xWindow(_xControl, uno::UNO_QUERY);
//STRIP001  if (xWindow.is())
//STRIP001  {
//STRIP001      uno::Reference< awt::XControlContainer > xControlContainer(xControl->getContext(), uno::UNO_QUERY);
//STRIP001      _xControl->setModel(xControl->getModel());
//STRIP001
//STRIP001      // Feststellen, welcher Modus eingeschaltet ist
//STRIP001      BOOL bDesignMode = xControl->isDesignMode();
//STRIP001
//STRIP001      // set the correct zoom
//STRIP001      OutputDevice* pOutDev = pObj->GetOutputDevice(xControl);
//STRIP001      if (pOutDev && !bDesignMode)
//STRIP001      {
//STRIP001          uno::Reference< awt::XView > xView(_xControl, uno::UNO_QUERY);
//STRIP001          if (xView.is())
//STRIP001          {
//STRIP001              const MapMode& rMap = pOutDev->GetMapMode();
//STRIP001              xView->setZoom((float) double(rMap.GetScaleX()),
//STRIP001                             (float) double(rMap.GetScaleY()));
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      // Groeﬂe setzen
//STRIP001      if (pOutDev && pOutDev->GetOutDevType() == OUTDEV_WINDOW)
//STRIP001      {
//STRIP001          Rectangle aRect(pObj->GetLogicRect());
//STRIP001          Point aPixPos(pOutDev->LogicToPixel(aRect.TopLeft()));
//STRIP001          Size aPixSize(pOutDev->LogicToPixel(aRect.GetSize()));
//STRIP001          xWindow->setPosSize(aPixPos.X(), aPixPos.Y(), aPixSize.Width(), aPixSize.Height(), awt::PosSize::POSSIZE);
//STRIP001      }
//STRIP001
//STRIP001      // Control wird nicht mehr benoetigt
//STRIP001      // zunaechst als Listener austragen
//STRIP001      Clear(TRUE);
//STRIP001
//STRIP001      xControlContainer->addControl(String(), _xControl);
//STRIP001
//STRIP001      // Designmodus erst setzen, wenn Peer bereits existiert!
//STRIP001      _xControl->setDesignMode(bDesignMode);
//STRIP001
//STRIP001      xControl = _xControl;
//STRIP001
//STRIP001      // und wieder alle Listener anmelden
//STRIP001         switchControlListening( true );
//STRIP001  }
//STRIP001 }

//------------------------------------------------------------------------------

/*?*/ void SdrUnoControlRec::switchDesignModeListening( bool _bStart )
/*?*/ {{DBG_ASSERT(0, "STRIP");}//STRIP001
//STRIP001  if ( (bool)IsListening() != _bStart )
//STRIP001  {
//STRIP001      bIsListening = _bStart;
//STRIP001
//STRIP001      if (xControl.is())
//STRIP001      {
//STRIP001             switchPropertyListening( _bStart, true );
//STRIP001
//STRIP001          uno::Reference< form::XImageProducerSupplier > xImg( xControl->getModel(), uno::UNO_QUERY );
//STRIP001          if (xImg.is())
//STRIP001          {
//STRIP001              uno::Reference< awt::XImageProducer > xProducer = xImg->getImageProducer();
//STRIP001              if (xProducer.is())
//STRIP001                     if ( _bStart )
//STRIP001                         xProducer->addConsumer(this);
//STRIP001                     else
//STRIP001                  xProducer->removeConsumer(this);
//STRIP001          }
//STRIP001      }
//STRIP001  }
/*?*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*N*/ SV_IMPL_OP_PTRARR_SORT( SdrUnoControlAccessArr, SdrUnoControlAccessPtr )

//------------------------------------------------------------------------
/*N*/ SdrUnoControlRec* SdrUnoControlList::GetObject(USHORT i) const
/*N*/ {
/*N*/   SdrUnoControlAccess* pAccess = aAccessArr[i];
/*N*/   return pAccess->pControlRec;
/*N*/ }

//------------------------------------------------------------------------
/*N*/ void SdrUnoControlList::Clear(BOOL bDispose)
/*N*/ {
/*N*/   for( USHORT i=aAccessArr.Count(); i > 0; )
/*N*/       Delete(--i, bDispose);
/*N*/
/*N*/   DBG_ASSERT(!aList.Count(), "SdrUnoControlList::Clear(BOOL bDispose): List not empty");
/*N*/ }

//------------------------------------------------------------------------
/*N*/ void SdrUnoControlList::Insert(SdrUnoControlRec* pRec)
/*N*/ {
/*N*/   aList.Insert( pRec, LIST_APPEND );
/*N*/   pRec->acquire();
/*N*/
/*N*/   SdrUnoControlAccess* pAccess = new SdrUnoControlAccess(pRec->GetControl()->getModel(), pRec);
/*N*/   aAccessArr.Insert( pAccess );
/*N*/ }

//------------------------------------------------------------------------
/*N*/ void SdrUnoControlList::Delete(USHORT nPos, BOOL bDispose)
/*N*/ {
/*N*/   SdrUnoControlAccess* pAccess = aAccessArr[nPos];
/*N*/   SdrUnoControlRec* pRec = pAccess->pControlRec;
/*N*/
/*N*/   aList.Remove( pRec );
/*N*/   aAccessArr.Remove( nPos );
/*N*/
/*N*/   // Rec laeﬂt alles los und wird anschlieﬂend zerstoert
/*N*/   pRec->Clear(bDispose);
/*N*/
/*N*/   pRec->release();
/*N*/   delete pAccess;
/*N*/ }

//------------------------------------------------------------------------
//STRIP001 void SdrUnoControlList::Disposing(SdrUnoControlRec* pRec)
//STRIP001 {
//STRIP001  SdrUnoControlAccess* pAccess = NULL;
//STRIP001  for (USHORT i = 0; i < aAccessArr.Count(); i++)
//STRIP001  {
//STRIP001      pAccess = aAccessArr[i];
//STRIP001      if (pAccess->pControlRec == pRec)
//STRIP001      {
//STRIP001          aList.Remove( pRec );
//STRIP001          aAccessArr.Remove( i );
//STRIP001
//STRIP001          pRec->release();
//STRIP001          delete pAccess;
//STRIP001          break;
//STRIP001      }
//STRIP001  }
//STRIP001 }

//------------------------------------------------------------------------
//STRIP001 USHORT SdrUnoControlList::Find(SdrUnoControlRec* pUCR) const
//STRIP001 {
//STRIP001  return Find( pUCR->GetControl()->getModel() );
//STRIP001 }

//------------------------------------------------------------------------
//STRIP001 USHORT SdrUnoControlList::Find(uno::Reference< awt::XControl > rUnoControl) const
//STRIP001 {
//STRIP001  return Find( rUnoControl->getModel() );
//STRIP001 }

//------------------------------------------------------------------------
/*N*/ USHORT SdrUnoControlList::Find(uno::Reference< awt::XControlModel > rUnoControlModel) const
/*N*/ {
/*N*/   SdrUnoControlAccess aAccess(rUnoControlModel);
/*N*/   USHORT nPos;
/*N*/   if( !aAccessArr.Seek_Entry(&aAccess, &nPos) )
/*N*/       return SDRUNOCONTROL_NOTFOUND;
/*N*/
/*N*/   return nPos;
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*N*/ void SdrPageViewWinList::Clear()
/*N*/ {
/*N*/   USHORT nAnz=GetCount();
/*N*/   for (USHORT i=0; i<nAnz; i++) {
/*N*/       delete GetObject(i);
/*N*/   }
/*N*/   aList.Clear();
/*N*/ }

/*N*/ USHORT SdrPageViewWinList::Find(OutputDevice* pOut) const
/*N*/ {
/*N*/   USHORT nAnz=GetCount();
/*N*/   USHORT nRet=SDRPAGEVIEWWIN_NOTFOUND;
/*N*/   for (USHORT nNum=0; nNum<nAnz && nRet==SDRPAGEVIEWWIN_NOTFOUND; nNum++) {
/*N*/       if (GetObject(nNum)->MatchOutputDevice(pOut))
/*N*/           nRet=nNum;
/*N*/   }
/*N*/   return nRet;
/*N*/ }


////////////////////////////////////////////////////////////////////////////////////////////////////
/*N*/ SdrPageViewWinRec::SdrPageViewWinRec(SdrPageView& rNewPageView, OutputDevice* pOut)
/*N*/     :rView( rNewPageView.GetView() )
/*N*/   ,pOutDev( pOut )
/*N*/     ,aControlList( rNewPageView )
/*N*/ {
/*N*/ }

/*N*/ SdrPageViewWinRec::~SdrPageViewWinRec()
/*N*/ {
/*N*/   if (xControlContainer.is())
/*N*/   {
/*N*/       // notify derived views
/*N*/       rView.RemoveControlContainer(xControlContainer);
/*N*/
/*N*/       // clear the control place holders
/*N*/       aControlList.Clear(FALSE);
/*N*/
/*N*/       // dispose the control container
/*N*/       uno::Reference< lang::XComponent > xComponent(xControlContainer, uno::UNO_QUERY);
/*N*/       xComponent->dispose();
/*N*/   }
/*N*/ }

/*N*/ void SdrPageViewWinRec::CreateControlContainer()
/*N*/ {
/*N*/   if (!xControlContainer.is())
/*N*/   {
/*N*/       if (pOutDev && pOutDev->GetOutDevType() == OUTDEV_WINDOW &&
/*N*/           !rView.IsPrintPreview())
/*N*/       {
/*N*/           Window* pWindow = (Window*) pOutDev;
/*N*/           xControlContainer = VCLUnoHelper::CreateControlContainer( pWindow );

            // #100394# xC->setVisible triggers window->Show() and this has
            // problems when the view is not completely constructed which may
            // happen when loading. This leads to accessibility broadcasts which
            // throw asserts due to the not finished view. All this chan be avoided
            // since xC->setVisible is here called only for the side effect in
            // UnoControlContainer::setVisible(...) which calls createPeer(...).
            // This will now be called directly from here.

            // UnoContainerModel erzeugen
            // uno::Reference< awt::XWindow > xC(xControlContainer, uno::UNO_QUERY);
            // CreateControlContainer() is only used from
            // , thus it seems not necessary to make
            // it visible her at all.
            // #58917# Das Show darf nicht am VCL-Fenster landen, weil dann Assertion vom SFX
            // BOOL bVis = pWindow->IsVisible();
            // xC->setVisible(TRUE);
            // if ( !bVis )
            //  pWindow->Hide();
            //  if( !mxContext.is() && bVisible )
            //      // Es ist ein TopWindow, also automatisch anzeigen
            //      createPeer( ::com::sun::star::uno::Reference< ::com::sun::star::awt::XToolkit > (), ::com::sun::star::uno::Reference< ::com::sun::star::awt::XWindowPeer > () );

/*N*/           uno::Reference< awt::XControl > xControl(xControlContainer, uno::UNO_QUERY);
/*N*/           if(xControl.is())
/*N*/           {
/*N*/               uno::Reference< uno::XInterface > xContext = xControl->getContext();
/*N*/               if(!xContext.is())
/*N*/               {
/*N*/                   xControl->createPeer( ::com::sun::star::uno::Reference< ::com::sun::star::awt::XToolkit > (),
/*N*/                       ::com::sun::star::uno::Reference< ::com::sun::star::awt::XWindowPeer > () );
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/       else
/*N*/       {
/*?*/           // Printer und VirtualDevice, bzw. kein OutDev
/*?*/           uno::Reference< lang::XMultiServiceFactory > xFactory( ::legacy_binfilters::getLegacyProcessServiceFactory() );
/*?*/           if( xFactory.is() )
/*?*/           {
/*?*/               xControlContainer = uno::Reference< awt::XControlContainer >(xFactory->createInstance(rtl::OUString::createFromAscii("com.sun.star.awt.UnoControlContainer")), uno::UNO_QUERY);
/*?*/               uno::Reference< awt::XControlModel > xModel(xFactory->createInstance(rtl::OUString::createFromAscii("com.sun.star.awt.UnoControlContainerModel")), uno::UNO_QUERY);
/*?*/               uno::Reference< awt::XControl > xControl(xControlContainer, uno::UNO_QUERY);
/*?*/               if (xControl.is())
/*?*/                   xControl->setModel(xModel);
/*?*/
/*?*/               Point aPosPix;
/*?*/               Size aSizePix;
/*?*/
/*?*/               if ( pOutDev )
/*?*/               {
/*?*/                   aPosPix = pOutDev->GetMapMode().GetOrigin();
/*?*/                   aSizePix = pOutDev->GetOutputSizePixel();
/*?*/               }
/*?*/
/*?*/               uno::Reference< awt::XWindow > xContComp(xControlContainer, uno::UNO_QUERY);
/*?*/               if( xContComp.is() )
/*?*/                   xContComp->setPosSize(aPosPix.X(), aPosPix.Y(), aSizePix.Width(), aSizePix.Height(), awt::PosSize::POSSIZE);
/*?*/           }
/*N*/       }
/*N*/
/*N*/       rView.InsertControlContainer(xControlContainer);
/*N*/   }
/*N*/ }

/*N*/ BOOL SdrPageViewWinRec::MatchOutputDevice(OutputDevice* pOut) const
/*N*/ {
/*N*/   BOOL bMatch = FALSE;
/*N*/
/*N*/   if (pOutDev == pOut)
/*N*/   {
/*N*/       bMatch = TRUE;
/*N*/   }
/*N*/
/*N*/   return (bMatch);
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ DBG_NAME(SdrPageView);


/*N*/ SdrPageView::SdrPageView(SdrPage* pPage1, const Point& rOffs, SdrView& rNewView):
/*N*/   rView(rNewView),
/*N*/   //aRedraw(1024,16,16),
/*N*/   aOfs(rOffs),
/*N*/   pPaintingPageObj( NULL ),
/*N*/   maDocumentColor( COL_AUTO )     // #103911# col_auto color lets the view takes the default SvxColorConfig entry
/*N*/ {
/*N*/   DBG_CTOR(SdrPageView,NULL);
/*N*/   pDragPoly0=new XPolyPolygon;
/*N*/   pDragPoly=new XPolyPolygon;
/*N*/   pWinList=new SdrPageViewWinList;
/*N*/   pPage=pPage1;
/*N*/   if (pPage!=NULL) {
/*N*/       aPgOrg.X()=pPage->GetLftBorder();
/*N*/       aPgOrg.Y()=pPage->GetUppBorder();
/*N*/   }
/*N*/ //      aOut.SetOutDev(rView.pWin);
/*N*/ //      aOut.SetOffset(rOffs);
/*N*/ //      eDrwStat=RS_READY;
/*N*/   bHasMarked=FALSE;
/*N*/   //aDragPoly.Clear();
/*N*/   aLayerVisi.SetAll();
/*N*/   aLayerPrn.SetAll();
/*N*/   bVisible=FALSE;
/*N*/
/*N*/   pAktList = NULL;
/*N*/   pAktGroup = NULL;
/*N*/   SetAktGroupAndList(NULL, pPage);
/*N*/
/*N*/   StartListening(*rNewView.GetModel());
/*N*/   USHORT nWinAnz=rNewView.GetWinCount();
/*N*/   for (USHORT nWinNum=0; nWinNum<nWinAnz; nWinNum++) {
/*N*/       AddWin(rNewView.GetWin(nWinNum));
/*N*/   }
/*N*/ }


/*N*/ SdrPageView::~SdrPageView()
/*N*/ {
/*N*/   if (rView.GetModel()->GetPaintingPageView() == this)
/*N*/   {
        // Abmelden
/*?*/       rView.GetModel()->SetPaintingPageView(NULL);
/*N*/   }
/*N*/
/*N*/   DBG_DTOR(SdrPageView,NULL);
/*N*/   delete pWinList;
/*N*/   delete pDragPoly0;
/*N*/   delete pDragPoly;
/*N*/ }

/*N*/ SdrPageViewWinRec* SdrPageView::ImpMakePageViewWinRec(OutputDevice* pOut)
/*N*/ {
/*N*/   // MIB 3.7.08: Das WinRec muss sofort in die Liste eingetragen werden,
/*N*/   // weil sich das InsertControlContainer darauf verlaesst
/*N*/   SdrPageViewWinRec* pRec = new SdrPageViewWinRec( *this, pOut );
/*N*/   pWinList->Insert(pRec);
/*N*/
/*N*/   ULONG nObjAnz=pPage!=NULL?pPage->GetObjCount():0;
/*N*/
/*N*/   for (ULONG nObjNum=0; nObjNum<nObjAnz; nObjNum++)
/*N*/   {
/*N*/       SdrObject* pObj = pPage->GetObj(nObjNum);
/*N*/
/*N*/       if (pObj->IsUnoObj())
/*N*/       {
/*N*/           SdrUnoObj* pSdrUnoObj = PTR_CAST(SdrUnoObj, pObj);
/*N*/           ImpInsertControl(pSdrUnoObj, pRec);
/*N*/       }
/*N*/       else if (pObj->GetObjIdentifier() == OBJ_GRUP &&
/*N*/                pObj->GetObjInventor() == SdrInventor)
/*N*/       {
/*N*/           // Gruppenobjekt: sind Uno-Objekte enthalten?
/*N*/           SdrObjListIter aIter(*((SdrObjGroup*) pObj)->GetSubList(), IM_DEEPNOGROUPS);
/*N*/
/*N*/           SdrObject* pObj = NULL;
/*N*/
/*N*/           while (aIter.IsMore())
/*N*/           {
/*N*/               pObj = aIter.Next();
/*N*/
/*N*/               if (pObj && pObj->IsUnoObj())
/*N*/               {
/*?*/                   SdrUnoObj* pSdrUnoObj = PTR_CAST(SdrUnoObj, pObj);
/*?*/                   ImpInsertControl(pSdrUnoObj, pRec);
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   return pRec;
/*N*/ }

/*N*/ void SdrPageView::AddWin(OutputDevice* pOutDev)
/*N*/ {
/*N*/   USHORT nPos = pWinList->Find(pOutDev);
/*N*/
/*N*/   if (nPos == SDRPAGEVIEWWIN_NOTFOUND)
/*N*/       SdrPageViewWinRec* pWinRec = ImpMakePageViewWinRec(pOutDev);
/*N*/ }

/*N*/ void SdrPageView::DelWin(OutputDevice* pOutDev)
/*N*/ {
/*N*/   USHORT nPos=pWinList->Find(pOutDev);
/*N*/
/*N*/   if (nPos != SDRPAGEVIEWWIN_NOTFOUND)
/*N*/   {
/*N*/       pWinList->Delete(nPos);
/*N*/   }
/*N*/ }

/*?*/ ::com::sun::star::uno::Reference< ::com::sun::star::awt::XControlContainer > SdrPageView::GetControlContainer( const OutputDevice* _pDevice )
/*?*/ {{DBG_ASSERT(0, "STRIP");}//STRIP001
/*?*/     ::com::sun::star::uno::Reference< ::com::sun::star::awt::XControlContainer > xReturn;
//STRIP001 /*?*/     USHORT nWinPos = pWinList->Find( const_cast< OutputDevice* >( _pDevice ) );
//STRIP001 /*?*/     if ( SDRPAGEVIEWWIN_NOTFOUND != nWinPos )
//STRIP001 /*?*/     {
//STRIP001 /*?*/         xReturn = xReturn.query( ((*pWinList)[ nWinPos ]).GetControlContainerRef( ) );
//STRIP001 /*?*/         if ( !xReturn.is() )
//STRIP001 /*?*/             ((*pWinList)[ nWinPos ]).CreateControlContainer( );
//STRIP001 /*?*/         xReturn = xReturn.query( ((*pWinList)[ nWinPos ]).GetControlContainerRef( ) );
//STRIP001 /*?*/     }
/*?*/     return xReturn;
/*?*/ }

/*N*/ void SdrPageView::ImpInsertControl(const SdrUnoObj* pSdrUnoObj,
/*N*/                                  SdrPageViewWinRec* pRec)
/*N*/ {
/*N*/   if (pSdrUnoObj)
/*N*/   {
/*N*/       uno::Reference< awt::XControlModel > xUnoControlModel(pSdrUnoObj->GetUnoControlModel());
/*N*/       if (!xUnoControlModel.is())
/*N*/           return;
/*N*/
/*N*/       USHORT nCtrlNum = pRec->aControlList.Find(xUnoControlModel);
/*N*/       if (nCtrlNum == SDRUNOCONTROL_NOTFOUND)
/*N*/       {
/*N*/           // Control fuer die View erzeugen
/*N*/           uno::Reference< lang::XMultiServiceFactory > xFactory( ::legacy_binfilters::getLegacyProcessServiceFactory() );
/*N*/           uno::Reference< awt::XControl > xUnoControl;
/*N*/           if( xFactory.is() )
/*N*/               xUnoControl = uno::Reference< awt::XControl >(xFactory->createInstance(pSdrUnoObj->GetUnoControlTypeName()), uno::UNO_QUERY);
/*N*/
/*N*/           if (xUnoControl.is())
/*N*/           {
/*N*/               xUnoControl->setModel(xUnoControlModel);
/*N*/               if (pRec->pOutDev->GetOutDevType() != OUTDEV_WINDOW)
/*N*/               {
/*?*/                   uno::Reference< awt::XView > xView = xUnoControl->getView();
/*?*/                   if (xView.is())
/*?*/                   {
/*?*/ //                          xView->setGraphics(pRec->pOutDev->GetGraphicsInterface(TRUE));
/*?*/                   }
/*N*/               }
/*N*/
/*N*/               // ControlContainer ggf. erzeugen
/*N*/               pRec->CreateControlContainer();
/*N*/
/*N*/               // xControl in ControlContainer einfuegen (Eigentuemer-Uebergang)
/*N*/               if (pRec->GetControlContainerRef().is())
/*N*/               {
/*N*/                   uno::Reference< awt::XWindow > xWindow(xUnoControl, uno::UNO_QUERY);
/*N*/                   if (xWindow.is())
/*N*/                   {
/*N*/                       Rectangle aRect(pSdrUnoObj->GetLogicRect());
/*N*/                       Point aPixPos(pRec->pOutDev->LogicToPixel(aRect.TopLeft()));
/*N*/                       Size aPixSize(pRec->pOutDev->LogicToPixel(aRect.GetSize()));
/*N*/                       xWindow->setPosSize(aPixPos.X(), aPixPos.Y(), aPixSize.Width(), aPixSize.Height(), awt::PosSize::POSSIZE);
/*N*/                   }
/*N*/
/*N*/                   // set the correct zoom
/*N*/                   if (!GetView().IsDesignMode())
/*N*/                   {
/*N*/                       uno::Reference< awt::XView > xView(xUnoControl, uno::UNO_QUERY);
/*N*/                       if (xView.is())
/*N*/                       {
/*N*/                           const MapMode& rMap = pRec->pOutDev->GetMapMode();
/*N*/                           xView->setZoom((float) double(rMap.GetScaleX()),
/*N*/                                          (float) double(rMap.GetScaleY()));
/*N*/                       }
/*N*/                   }
/*N*/
/*N*/                   // #107049# set design mode before peer is created,
/*N*/                   // this is also needed for accessibility
/*N*/                   xUnoControl->setDesignMode(GetView().IsDesignMode());
/*N*/
/*N*/                   SdrUnoControlRec* pUCR = new SdrUnoControlRec(&pRec->aControlList, (SdrUnoObj*)pSdrUnoObj, xUnoControl);
/*N*/                   pRec->aControlList.Insert(pUCR);
/*N*/
/*N*/                     // #108327# do this last - the addition of the control triggeres processes which rely
/*N*/                     // on the control already being inserted into the aControlList
/*N*/                   pRec->GetControlContainerRef()->addControl(pSdrUnoObj->GetUnoControlTypeName(), xUnoControl);
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }


/*N*/ void SdrPageView::ImpUnoInserted(const SdrObject* pObj)
/*N*/ {
/*N*/   SdrUnoObj* pSdrUnoObj = (SdrUnoObj*)pObj;
/*N*/   USHORT nPos = pWinList->GetCount();
/*N*/
/*N*/   for (; nPos; )
/*N*/       ImpInsertControl(pSdrUnoObj, &(*pWinList)[--nPos]);
/*N*/
/*N*/ }

//STRIP001 void SdrPageView::ImpUnoRemoved(const SdrObject* pObj)
//STRIP001 {
//STRIP001  SdrUnoObj* pSdrUno=(SdrUnoObj*)pObj;
//STRIP001  USHORT nPos = pWinList->GetCount();
//STRIP001  for (; nPos; )
//STRIP001  {
//STRIP001      SdrPageViewWinRec& rPVWR=(*pWinList)[--nPos];
//STRIP001      USHORT nControlPos=rPVWR.aControlList.Find(pSdrUno->GetUnoControlModel());
//STRIP001
//STRIP001      if (nControlPos != SDRUNOCONTROL_NOTFOUND)
//STRIP001          rPVWR.aControlList.Delete(nControlPos, TRUE);
//STRIP001  }
//STRIP001 }


/*N*/ void __EXPORT SdrPageView::SFX_NOTIFY(SfxBroadcaster& rBC, const TypeId& rBCType, const SfxHint& rHint, const TypeId& rHintType)
/*N*/ {
/*N*/   if (bVisible) {
/*N*/       SdrHint* pSdrHint=PTR_CAST(SdrHint,&rHint);
/*N*/       if (pSdrHint!=NULL) {
/*N*/           SdrHintKind eKind=pSdrHint->GetKind();
/*N*/           const SdrObject* pObj=pSdrHint->GetObject();
/*N*/           if ( pObj!=NULL && pObj->GetPage() == pPage )
/*N*/           {
/*N*/               if (pObj->IsUnoObj())
/*N*/               {
/*N*/                   if (eKind == HINT_OBJINSERTED ||
/*N*/                       eKind == HINT_CONTROLINSERTED)
/*N*/                   {
/*N*/                       ImpUnoInserted(pObj);
/*N*/                   }
/*N*/                   else if (eKind == HINT_OBJREMOVED ||
/*N*/                            eKind == HINT_CONTROLREMOVED)
/*N*/
/*N*/                   {
/*?*/                   DBG_ASSERT(0, "STRIP"); //STRIP001  ImpUnoRemoved(pObj);
/*N*/                   }
/*N*/               }
/*N*/               else if (pObj->GetObjIdentifier() == OBJ_GRUP &&
/*N*/                        pObj->GetObjInventor() == SdrInventor)
/*N*/               {
/*N*/                   // Gruppenobjekt: sind Uno-Objekte enthalten?
/*N*/                   SdrObjListIter aIter(*((SdrObjGroup*) pObj)->GetSubList(), IM_DEEPNOGROUPS);
/*N*/
/*N*/                   SdrObject* pObj = NULL;
/*N*/
/*N*/                   while (aIter.IsMore())
/*N*/                   {
/*N*/                       pObj = aIter.Next();
/*N*/
/*N*/                       if (pObj && pObj->IsUnoObj())
/*N*/                       {
/*?*/                           if (eKind == HINT_OBJINSERTED ||
/*?*/                               eKind == HINT_CONTROLINSERTED)
/*?*/
/*?*/                           {
/*?*/                               ImpUnoInserted(pObj);
/*?*/                           }
/*?*/                           else if (eKind == HINT_OBJREMOVED ||
/*?*/                                    eKind == HINT_CONTROLREMOVED)
/*?*/
/*?*/                           {
/*?*/                               DBG_ASSERT(0, "STRIP"); //STRIP001 ImpUnoRemoved(pObj);
/*?*/                           }
/*N*/                       }
/*N*/                   }
/*N*/               }
/*N*/           }
/*N*/           if (pSdrHint->IsNeedRepaint()) {
/*N*/               if (((eKind==HINT_OBJCHG
/*N*/                   || eKind==HINT_OBJINSERTED || eKind==HINT_OBJREMOVED
/*N*/                   || eKind == HINT_CONTROLINSERTED || eKind == HINT_CONTROLREMOVED) &&
/*N*/                    pSdrHint->GetPage()!=NULL) ||
/*N*/                   eKind==HINT_PAGECHG)
/*N*/               {
/*N*/                   FASTBOOL bInv=FALSE;
/*N*/                   if (pSdrHint->GetPage()==pPage) bInv=TRUE;
/*N*/                   else if (pSdrHint->GetPage()->IsMasterPage()) { // ebenfalls Invalidate, wenn pPage die geaenderte Page als MasterPage referenziert
/*N*/                       USHORT nMaPgAnz=pPage!=NULL?pPage->GetMasterPageCount():0;
/*N*/                       for (USHORT i=0; i<nMaPgAnz && !bInv; i++) {
/*N*/                           const SdrPage* pMPg=pPage->GetMasterPage(i);
/*N*/                           bInv=pMPg==pSdrHint->GetPage();
/*N*/                       }
/*N*/                   }
/*N*/                   if (bInv) {
/*N*/                       InvalidateAllWin(pSdrHint->GetRect(),TRUE);
/*N*/                   }
/*N*/               }
/*N*/           }
/*N*/           if (eKind==HINT_OBJLISTCLEARED && pSdrHint->GetPage()==pPage) {
/*?*/               if (GetAktGroup()!=NULL) {
/*?*/                   rView.UnmarkAllObj();
/*?*/                   LeaveAllGroup();
/*?*/                   //pWinList ...
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }


/*N*/ void SdrPageView::ModelHasChanged()
/*N*/ {
/*N*/   if (GetAktGroup()!=NULL) CheckAktGroup();
/*N*/ }


//STRIP001 FASTBOOL SdrPageView::IsReadOnly() const
//STRIP001 {
//STRIP001  return pPage==NULL || rView.GetModel()->IsReadOnly() || pPage->IsReadOnly() || GetObjList()->IsReadOnly();
//STRIP001 }


/*N*/ void SdrPageView::Show()
/*N*/ {
/*N*/   if (!bVisible) {
/*N*/       bVisible=TRUE;
/*N*/       InvalidateAllWin();
/*N*/       USHORT nWinAnz=rView.GetWinCount();
/*N*/       for (USHORT nWinNum=0; nWinNum<nWinAnz; nWinNum++) {
/*N*/           AddWin(rView.GetWin(nWinNum));
/*N*/       }
/*N*/   }
/*N*/ }


/*N*/ void SdrPageView::Hide()
/*N*/ {
/*N*/   if (bVisible) {
/*N*/       InvalidateAllWin();
/*N*/       bVisible=FALSE;
/*N*/       pWinList->Clear();
/*N*/   }
/*N*/ }


//STRIP001 void SdrPageView::SetOffset(const Point& rPnt)
//STRIP001 {
//STRIP001  if (aOfs!=rPnt) {
//STRIP001      if (bVisible) InvalidateAllWin();
//STRIP001      aOfs=rPnt;
//STRIP001      if (bVisible) InvalidateAllWin();
//STRIP001  }
//STRIP001 }


/*N*/ Rectangle SdrPageView::GetPageRect() const
/*N*/ {
/*N*/   if (pPage==NULL) return Rectangle();
/*N*/   return Rectangle(GetOffset(),Size(pPage->GetWdt()+1,pPage->GetHgt()+1));
/*N*/ }


/*N*/ void SdrPageView::InvalidateAllWin()
/*N*/ {
/*N*/   if (bVisible && pPage!=NULL) {
/*N*/       Rectangle aRect(Point(0,0),Size(pPage->GetWdt()+1,pPage->GetHgt()+1));
/*N*/       aRect.Union(pPage->GetAllObjBoundRect());
/*N*/       aRect.Move(aOfs.X(),aOfs.Y());
/*N*/       rView.InvalidateAllWin(aRect);
/*N*/   }
/*N*/ }


/*N*/ void SdrPageView::InvalidateAllWin(const Rectangle& rRect, FASTBOOL bPlus1Pix)
/*N*/ {
/*N*/   if (bVisible) {
/*N*/       rView.InvalidateAllWin(rRect+GetOffset(),bPlus1Pix);
/*N*/   }
/*N*/ }


//STRIP001 void SdrPageView::ImpPaintOutlinerView(OutputDevice* pOut, const Rectangle& rRect) const
//STRIP001 {
//STRIP001  if (rView.pTextEditOutliner==NULL) return;
//STRIP001  const SdrObject* pTextObjTmp=rView.GetTextEditObject();
//STRIP001  const SdrTextObj* pText=PTR_CAST(SdrTextObj,pTextObjTmp);
//STRIP001  FASTBOOL bTextFrame=pText!=NULL && pText->IsTextFrame();
//STRIP001  ULONG nViewAnz=rView.pTextEditOutliner->GetViewCount();
//STRIP001  for (ULONG i=0; i<nViewAnz; i++) {
//STRIP001      OutlinerView* pOLV=rView.pTextEditOutliner->GetView(i);
//STRIP001      if (pOLV->GetWindow()==pOut) {
//STRIP001          rView.ImpPaintOutlinerView(*pOLV,&rRect);
//STRIP001          return;
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 FASTBOOL SdrPageView::DoCachedMasterPaint(const SdrPage* pMasterPage, ExtOutputDevice& rXOut,
//STRIP001                                        const SdrPaintInfoRec& InfoRec) const
//STRIP001 {
//STRIP001  return DoCachedMasterPaint( pMasterPage, rXOut, InfoRec, SDR_MASTERPAGECACHE_FULL );
//STRIP001 }

//STRIP001 FASTBOOL SdrPageView::DoCachedMasterPaint(const SdrPage* pPg, ExtOutputDevice& rXOut,
//STRIP001                                        const SdrPaintInfoRec& rInfoRec, ULONG nCacheMode) const
//STRIP001 {
//STRIP001  if( pPage->GetBackgroundObj() )
//STRIP001      return FALSE;                   // own background available
//STRIP001
//STRIP001  ULONG nImplPrepareMode, nImplPaintMode;
//STRIP001
//STRIP001  if( SDR_MASTERPAGECACHE_FULL != nCacheMode && SDR_MASTERPAGECACHE_BACKGROUND != nCacheMode )
//STRIP001  {
//STRIP001      DBG_ERROR( "Wrong cache mode! Assuming SDR_MASTERPAGECACHE_FULL." );
//STRIP001      nCacheMode = SDR_MASTERPAGECACHE_FULL;
//STRIP001  }
//STRIP001
//STRIP001  if( SDR_MASTERPAGECACHE_FULL == nCacheMode )
//STRIP001      nImplPrepareMode = IMP_PAGEPAINT_PREPARE_CACHE, nImplPaintMode = IMP_PAGEPAINT_PAINT_CACHE;
//STRIP001  else
//STRIP001      nImplPrepareMode = IMP_PAGEPAINT_PREPARE_BG_CACHE, nImplPaintMode = IMP_PAGEPAINT_PAINT_BG_CACHE;
//STRIP001
//STRIP001  FASTBOOL bRet=TRUE;
//STRIP001
//STRIP001  OutputDevice* pWin=rXOut.GetOutDev();
//STRIP001  ImpMasterBmp* pBmp=rView.pMasterBmp;;
//STRIP001  const MapMode& rMap=pWin->GetMapMode();
//STRIP001
//STRIP001  // 1. Gucken, ob vielleicht eine passende Bmp da ist
//STRIP001  FASTBOOL bCreate=pBmp==NULL;
//STRIP001
//STRIP001  // Seitennummer der MasterPage muss gleich sein
//STRIP001  if (!bCreate)
//STRIP001      bCreate=pBmp->nMasterPageNum!=pPg->GetPageNum();
//STRIP001  if (!bCreate) // Scaling checken
//STRIP001      bCreate=rMap.GetScaleX()!=pBmp->aMapX || rMap.GetScaleY()!=pBmp->aMapY;
//STRIP001
//STRIP001  // Sichtbare Layer muessen gleich sein
//STRIP001  if (!bCreate)
//STRIP001      bCreate=pBmp->aVisLayers!=rInfoRec.aPaintLayer;
//STRIP001
//STRIP001  // Der sichtbare Bereich von pPg muss innerhalb des Bereiches des VD liegen
//STRIP001  Point aTopLeftTmp(rMap.GetOrigin()); aTopLeftTmp.X()=-aTopLeftTmp.X(); aTopLeftTmp.Y()=-aTopLeftTmp.Y();
//STRIP001  Size aWinSize(pWin->GetOutputSize());
//STRIP001  Rectangle aNeedLogRect(aTopLeftTmp,aWinSize);
//STRIP001  aNeedLogRect.Right()++; aNeedLogRect.Bottom()++; // Weil Rect(Pnt,Siz) unten rechts immer eins weniger ist
//STRIP001  Rectangle aPageBound(pPg->GetAllObjBoundRect()); // Nur den wirklich verwendeten Bereich der MasterPage
//STRIP001  Size aPageSize(aPageBound.GetSize()); aPageSize.Width()--; aPageSize.Height()--;
//STRIP001  aNeedLogRect.Intersection(aPageBound); // Nur den wirklich verwendeten Bereich der MasterPage
//STRIP001
//STRIP001  // Wenn die Seite vollstaendig ins Fenster passen wuerde...
//STRIP001  if (aWinSize.Width()>=aPageSize.Width())
//STRIP001  {
//STRIP001      aNeedLogRect.Left()=aPageBound.Left();
//STRIP001      aNeedLogRect.Right()=aPageBound.Right();
//STRIP001  }
//STRIP001
//STRIP001  // Wenn die Seite vollstaendig ins Fenster passen wuerde...
//STRIP001  if (aWinSize.Height()>=aPageSize.Height())
//STRIP001  {
//STRIP001      aNeedLogRect.Top()=aPageBound.Top();
//STRIP001      aNeedLogRect.Bottom()=aPageBound.Bottom();
//STRIP001  }
//STRIP001  if (!bCreate)
//STRIP001      bCreate=!pBmp->aLogBound.IsInside(aNeedLogRect);
//STRIP001
//STRIP001     // #108444# Check whether the draw modes match, this is relevant
//STRIP001     // for cache object validity
//STRIP001  if (!bCreate)
//STRIP001         bCreate = pBmp->nDrawMode != rInfoRec.nPaintMode;
//STRIP001
//STRIP001  // 2. Wenn keine passende Bmp da ist, dann versuchen eine zu erzeugen
//STRIP001  if (bCreate)
//STRIP001  {
//STRIP001      pPg->SwapInAll();          // Gelinkte Graphiken auf MasterPages machen sonst Probleme
//STRIP001
//STRIP001      if (pBmp==NULL)
//STRIP001      {
//STRIP001          pBmp=new ImpMasterBmp(*pWin);
//STRIP001          rView.pMasterBmp=pBmp;
//STRIP001      }
//STRIP001
//STRIP001         // Propagate digit language to device of bitmap.
//STRIP001         pBmp->aVD.SetDigitLanguage (pWin->GetDigitLanguage());
//STRIP001
//STRIP001      pBmp->aVD.SetClipRegion(); // ggf. gesetztes Clipping entfernen
//STRIP001      pBmp->aVD.SetMapMode(rMap);
//STRIP001      Size aNeedLogSize(aNeedLogRect.GetSize()); aNeedLogSize.Width()--; aNeedLogSize.Height()--;
//STRIP001      Size a1Pix(pWin->PixelToLogic(Size(1,1)));
//STRIP001      aNeedLogSize.Width() +=a1Pix.Width();  // 1 Pixel fuer Toleranz drauf
//STRIP001      aNeedLogSize.Height()+=a1Pix.Height();
//STRIP001
//STRIP001      // #103834# Use flag that impress application is using this view
//STRIP001      pBmp->aVD.SetBackground( Wallpaper(maBackgroundColor));
//STRIP001
//STRIP001      if (pBmp->aVD.SetOutputSize(aNeedLogSize,TRUE))
//STRIP001      {
//STRIP001          // MapMode ausrechnen und am VirtDev setzen
//STRIP001          MapMode aNewMap(rMap);
//STRIP001          Point aMapOrgTmp(aNeedLogRect.TopLeft());
//STRIP001          aMapOrgTmp.X()=-aMapOrgTmp.X(); aMapOrgTmp.Y()=-aMapOrgTmp.Y();
//STRIP001          Point aMapOrgGridTmp(aMapOrgTmp);
//STRIP001          aMapOrgGridTmp-=aOfs; // Position der PageView abziehen fuer Border, Grid, ...
//STRIP001          aNewMap.SetOrigin(aMapOrgGridTmp);
//STRIP001          pBmp->aVD.SetMapMode(aNewMap);
//STRIP001          rXOut.SetOutDev(&pBmp->aVD);
//STRIP001
//STRIP001             // Paper, Border etc. painten
//STRIP001             if (rView.bPageVisible)
//STRIP001             {
//STRIP001                 ((SdrPageView*)this)->DrawPaper(pBmp->aVD);
//STRIP001
//STRIP001                 if (rView.bPageBorderVisible)
//STRIP001                     ((SdrPageView*)this)->DrawPaperBorder(pBmp->aVD);
//STRIP001             }
//STRIP001
//STRIP001             if (rView.bBordVisible)
//STRIP001                 ((SdrPageView*)this)->DrawBorder(pBmp->aVD);
//STRIP001
//STRIP001             if (rView.bGridVisible && !rView.bGridFront)
//STRIP001                 ((SdrPageView*)this)->DrawGrid(pBmp->aVD, rView.GetGridColor());
//STRIP001
//STRIP001             if (rView.bHlplVisible && !rView.bHlplFront)
//STRIP001                 ((SdrPageView*)this)->DrawHelplines(pBmp->aVD);
//STRIP001
//STRIP001          // DrawMode vom Window uebernehmen
//STRIP001          const ULONG nOldDrawMode = pBmp->aVD.GetDrawMode();
//STRIP001          pBmp->aVD.SetDrawMode( pWin->GetDrawMode() );
//STRIP001
//STRIP001             // #108444# Store draw mode, this is relevant for object validity
//STRIP001             pBmp->nDrawMode = rInfoRec.nPaintMode;
//STRIP001
//STRIP001          // und nun endlich die MasterPage
//STRIP001          aNewMap.SetOrigin(aMapOrgTmp);
//STRIP001          pBmp->aVD.SetMapMode(aNewMap);
//STRIP001
//STRIP001          Point aTopLeftVDPixelLog(-aMapOrgTmp.X(),-aMapOrgTmp.Y());
//STRIP001          pBmp->aVD.IntersectClipRegion(Rectangle(aTopLeftVDPixelLog,aNeedLogSize));
//STRIP001          SdrPaintInfoRec aInfoRec(rInfoRec);
//STRIP001          aInfoRec.aCheckRect=aNeedLogRect;
//STRIP001          aInfoRec.aDirtyRect=aNeedLogRect;
//STRIP001          pPg->Paint(rXOut,aInfoRec,FALSE,(sal_uInt16)nImplPrepareMode);
//STRIP001          pBmp->aLogBound=aNeedLogRect;
//STRIP001          pBmp->nMasterPageNum=pPg->GetPageNum();
//STRIP001          pBmp->aMapX=rMap.GetScaleX();
//STRIP001          pBmp->aMapY=rMap.GetScaleY();
//STRIP001          pBmp->aVisLayers=rInfoRec.aPaintLayer;
//STRIP001          rXOut.SetOutDev(pWin);
//STRIP001          // MapOrigin des VDev wieder auf 0 setzen
//STRIP001          aNewMap.SetOrigin(Point());
//STRIP001          pBmp->aVD.SetMapMode(aNewMap);
//STRIP001          pBmp->aVD.SetClipRegion(); // ggf. gesetztes Clipping entfernen
//STRIP001
//STRIP001          // urspr. DrawMode wieder setzen
//STRIP001          pBmp->aVD.SetDrawMode( nOldDrawMode );
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          // Speicher reicht nicht
//STRIP001          delete pBmp;
//STRIP001          pBmp=NULL;
//STRIP001          rView.pMasterBmp=NULL;
//STRIP001      }
//STRIP001  }
//STRIP001  // 3. Bmp painten
//STRIP001  if (pBmp!=NULL)
//STRIP001  {
//STRIP001      Size aSiz(pBmp->aVD.GetOutputSize());
//STRIP001      pWin->DrawOutDev(pBmp->aLogBound.TopLeft(),aSiz,Point(),aSiz,pBmp->aVD);
//STRIP001      pPg->Paint(rXOut,rInfoRec,FALSE,(sal_uInt16)nImplPaintMode);
//STRIP001
//STRIP001      // #74982# activate plugins on master page
//STRIP001      if(rInfoRec.pPV)
//STRIP001      {
//STRIP001          SdrView* pSdrView = (SdrView*) &rInfoRec.pPV->GetView();
//STRIP001          SdrObjListIter aIter(*pPg, IM_DEEPNOGROUPS);
//STRIP001
//STRIP001          while(aIter.IsMore())
//STRIP001          {
//STRIP001              SdrObject* pObj = aIter.Next();
//STRIP001
//STRIP001              if(pObj && pObj->ISA(SdrOle2Obj))
//STRIP001              {
//STRIP001                  pSdrView->DoConnect((SdrOle2Obj*)pObj);
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001      bRet=FALSE; // ansonsten hat der Speicher nicht ausgereicht
//STRIP001
//STRIP001 //#endif
//STRIP001
//STRIP001  return bRet;
//STRIP001 }


//STRIP001 FASTBOOL SdrPageView::MasterShouldBeCached(const SdrPage* pPg) const
//STRIP001 {
//STRIP001  ULONG nObjAnz=pPg->GetObjCount();
//STRIP001  FASTBOOL bYes=nObjAnz>10; // bei mehr als 10 Objekten wird der Cache angeschaltet
//STRIP001  for (ULONG nObjNum=0; nObjNum<nObjAnz && !bYes; nObjNum++) {
//STRIP001      const SdrObject* pObj=pPg->GetObj(nObjNum);
//STRIP001      if (!pObj->IsNotVisibleAsMaster()) { // z.B. TitleText und OutlineText
//STRIP001          UINT32 nInv=pObj->GetObjInventor();
//STRIP001          UINT16 nId=pObj->GetObjIdentifier();
//STRIP001          // Bestimmte Objekttypen werden grundsaetzlich als langsam im Paint eingestuft:
//STRIP001          bYes=nInv==SdrInventor &&
//STRIP001               (nId==OBJ_GRUP ||
//STRIP001                nId==OBJ_PATHLINE || nId==OBJ_PATHFILL || nId==OBJ_FREELINE || nId==OBJ_FREEFILL ||
//STRIP001                nId==OBJ_GRAF     || nId==OBJ_OLE2     || nId==OBJ_PATHPOLY || nId==OBJ_PATHPLIN);
//STRIP001          // Alles was Text hat wird gecached.
//STRIP001          if (!bYes) bYes=pObj->GetOutlinerParaObject()!=NULL;
//STRIP001          // Nochmal auf GruppenObjekt checken
//STRIP001          if (!bYes) bYes=pObj->GetSubList()!=NULL;
//STRIP001          // Und nun Attribute Checken
//STRIP001          if (!bYes) {
//STRIP001              const SfxItemSet& rSet = pObj->GetItemSet();
//STRIP001              XLineStyle eLineStyle=((XLineStyleItem&)(rSet.Get(XATTR_LINESTYLE))).GetValue();
//STRIP001              XFillStyle eFillStyle=((XFillStyleItem&)(rSet.Get(XATTR_FILLSTYLE))).GetValue();
//STRIP001              bYes=(eLineStyle!=XLINE_NONE && eLineStyle!=XLINE_SOLID) ||
//STRIP001                   (eFillStyle!=XFILL_NONE && eFillStyle!=XFILL_SOLID);
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return bYes;
//STRIP001 }


//STRIP001 void SdrPageView::InitRedraw(USHORT nWinNum, const Region& rReg, USHORT nPaintMode, const Link* pPaintProc)
//STRIP001 {
//STRIP001  OutputDevice* pOut=rView.GetWin(nWinNum);
//STRIP001  if (pOut!=NULL) InitRedraw(pOut,rReg,nPaintMode,pPaintProc);
//STRIP001 }


//STRIP001 void SdrPageView::InitRedraw(OutputDevice* pOut_, const Region& rReg, USHORT nPaintMode, const Link* pPaintProc)
//STRIP001 {
//STRIP001  if(!pPage)
//STRIP001      return;
//STRIP001
//STRIP001  sal_uInt16 nWinAnz(pOut_!=NULL ? 1 : rView.GetWinCount());
//STRIP001  rView.GetModel()->SetPaintingPageView(this);
//STRIP001
//STRIP001  for(sal_uInt16 nWinNum(0); nWinNum < nWinAnz; nWinNum++)
//STRIP001  {
//STRIP001      OutputDevice* pOut = pOut_!=NULL ? pOut_ : rView.GetWin(nWinNum);
//STRIP001      DBG_ASSERT(pOut!=NULL,"SdrPageView::InitRedraw(): pOut==NULL");
//STRIP001
//STRIP001      if(!pOut)
//STRIP001          break;
//STRIP001
//STRIP001      sal_Bool bPrinter(OUTDEV_PRINTER == pOut->GetOutDevType());
//STRIP001      const sal_uInt32 nOldDrawMode(pOut->GetDrawMode());
//STRIP001
//STRIP001      // DrawMode temp. zuruecksetzen
//STRIP001      pOut->SetDrawMode(DRAWMODE_DEFAULT);
//STRIP001
//STRIP001      ExtOutputDevice* pXOut = rView.pXOut;
//STRIP001      pXOut->SetOutDev(pOut);
//STRIP001
//STRIP001      sal_Bool bDrawAll(rReg.IsEmpty());
//STRIP001      Rectangle aDirtyRect(rReg.GetBoundRect());
//STRIP001      Size a1PixSiz(pOut->PixelToLogic(Size(1, 1)));
//STRIP001      Rectangle aCheckRect(aDirtyRect);
//STRIP001
//STRIP001      aCheckRect.Left() -= a1PixSiz.Width();
//STRIP001      aCheckRect.Top() -= a1PixSiz.Height();
//STRIP001      aCheckRect.Right() += a1PixSiz.Width();
//STRIP001      aCheckRect.Bottom() += a1PixSiz.Height();
//STRIP001
//STRIP001      // Rect relativ zur PageView zum checken der Objekte
//STRIP001      aCheckRect -= aOfs;
//STRIP001
//STRIP001      sal_Bool bTextEdit(rView.IsTextEdit() && rView.pTextEditPV == this);
//STRIP001      ImpSdrHdcMerk aHDCMerk(*pOut, SDRHDC_SAVEPENANDBRUSHANDFONT, rView.bRestoreColors);
//STRIP001      // Dirty, wg. DrawPager, ...
//STRIP001      sal_Bool bColorsDirty(sal_True);
//STRIP001
//STRIP001      if(!bPrinter)
//STRIP001      {
//STRIP001          if(rView.bPageVisible)
//STRIP001             {
//STRIP001              DrawPaper(*pOut);
//STRIP001
//STRIP001              if(rView.bPageBorderVisible)
//STRIP001                     DrawPaperBorder(*pOut);
//STRIP001             }
//STRIP001
//STRIP001          if(rView.bBordVisible)
//STRIP001              DrawBorder(*pOut);
//STRIP001
//STRIP001          if(rView.bGridVisible && !rView.bGridFront)
//STRIP001              DrawGrid(*pOut,aCheckRect, rView.GetGridColor());
//STRIP001
//STRIP001          if(rView.bHlplVisible && !rView.bHlplFront)
//STRIP001              DrawHelplines(*pOut);
//STRIP001      }
//STRIP001
//STRIP001      pXOut->SetOffset(aOfs);
//STRIP001
//STRIP001      // eingestellten DrawMode wiederherstellen
//STRIP001      pOut->SetDrawMode(nOldDrawMode);
//STRIP001
//STRIP001      SdrPaintInfoRec aInfoRec;
//STRIP001      aInfoRec.pPV = this;
//STRIP001      aInfoRec.bPrinter = bPrinter;
//STRIP001      aInfoRec.aDirtyRect = aDirtyRect;
//STRIP001      aInfoRec.aCheckRect = aCheckRect;
//STRIP001      aInfoRec.pPaintProc = pPaintProc;
//STRIP001
//STRIP001      if(bPrinter)
//STRIP001      {
//STRIP001          if(rView.IsLineDraftPrn())
//STRIP001              nPaintMode |= SDRPAINTMODE_DRAFTLINE;
//STRIP001
//STRIP001          if(rView.IsFillDraftPrn())
//STRIP001              nPaintMode |= SDRPAINTMODE_DRAFTFILL;
//STRIP001
//STRIP001          if(rView.IsTextDraftPrn())
//STRIP001              nPaintMode |= SDRPAINTMODE_DRAFTTEXT;
//STRIP001
//STRIP001          if(rView.IsGrafDraftPrn())
//STRIP001              nPaintMode |= SDRPAINTMODE_DRAFTGRAF;
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          if(rView.IsLineDraft())
//STRIP001              nPaintMode |= SDRPAINTMODE_DRAFTLINE;
//STRIP001
//STRIP001          if(rView.IsFillDraft())
//STRIP001              nPaintMode |= SDRPAINTMODE_DRAFTFILL;
//STRIP001
//STRIP001          if(rView.IsTextDraft())
//STRIP001              nPaintMode |= SDRPAINTMODE_DRAFTTEXT;
//STRIP001
//STRIP001          if(rView.IsGrafDraft())
//STRIP001              nPaintMode |= SDRPAINTMODE_DRAFTGRAF;
//STRIP001
//STRIP001          if(rView.IsHideGrafDraft())
//STRIP001              nPaintMode |= SDRPAINTMODE_HIDEDRAFTGRAF;
//STRIP001      }
//STRIP001
//STRIP001      const SetOfByte& rPaintLayer = bPrinter ? aLayerPrn : aLayerVisi;
//STRIP001
//STRIP001      // erstmal alle MasterPages Painten
//STRIP001      sal_uInt16 nMaPgAnz(pPage->GetMasterPageCount());
//STRIP001      sal_Bool bNeedMPagPaint(sal_True);
//STRIP001
//STRIP001      if(!bPrinter && 1 == nMaPgAnz && rView.IsMasterPagePaintCaching())
//STRIP001      {
//STRIP001          // Die MasterPage ggf. mit 'ner Bitmap malen
//STRIP001          SdrPage* pMasterPage = pPage->GetMasterPage(0);
//STRIP001
//STRIP001          if(pMasterPage && pMasterPage->GetObjCount() && MasterShouldBeCached(pMasterPage))
//STRIP001          {
//STRIP001              // Gucken, ob passende Bmp da ist. Wenn nicht, dann versuchen eine zu erzeugen. Bmp painten.
//STRIP001              aInfoRec.aPaintLayer = rPaintLayer;
//STRIP001              aInfoRec.aPaintLayer &= pPage->GetMasterPageVisibleLayers(0);
//STRIP001              aInfoRec.nPaintMode = nPaintMode | SDRPAINTMODE_MASTERPAGE;
//STRIP001              bNeedMPagPaint = !DoCachedMasterPaint(pMasterPage, *pXOut, aInfoRec, rView.GetMasterPagePaintCacheMode());
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      if(bNeedMPagPaint)
//STRIP001      {
//STRIP001          sal_uInt16 nMaPgNum(0);
//STRIP001
//STRIP001          while(nMaPgNum < nMaPgAnz)
//STRIP001          {
//STRIP001              SdrPage* pMasterPage = pPage->GetMasterPage(nMaPgNum);
//STRIP001
//STRIP001              if(pMasterPage && pMasterPage->GetObjCount())
//STRIP001              {
//STRIP001                  aInfoRec.aPaintLayer = rPaintLayer;
//STRIP001                  aInfoRec.aPaintLayer &= pPage->GetMasterPageVisibleLayers(nMaPgNum);
//STRIP001                  aInfoRec.nPaintMode = nPaintMode | SDRPAINTMODE_MASTERPAGE;
//STRIP001                  pMasterPage->Paint(*pXOut, aInfoRec, rView.bRestoreColors);
//STRIP001              }
//STRIP001              nMaPgNum++;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      // Und nun die eigentliche Zeichenseite Painten
//STRIP001      aInfoRec.aPaintLayer = rPaintLayer;
//STRIP001      aInfoRec.nPaintMode = nPaintMode;
//STRIP001
//STRIP001      if(GetObjList() != pPage)
//STRIP001          aInfoRec.pAktList = GetObjList();
//STRIP001
//STRIP001      if(!bPrinter && rView.ImpIsGlueVisible())
//STRIP001      {
//STRIP001          aInfoRec.nPaintMode |= SDRPAINTMODE_GLUEPOINTS;
//STRIP001      }
//STRIP001
//STRIP001      // Zeichnen
//STRIP001      pPage->Paint(*pXOut, aInfoRec, rView.bRestoreColors);
//STRIP001      pXOut->SetOffset(Point(0, 0));
//STRIP001
//STRIP001      if(!bPrinter)
//STRIP001      {
//STRIP001          // Raster und Hilfslinien malen
//STRIP001          if(rView.bGridVisible && rView.bGridFront)
//STRIP001              DrawGrid(*pOut, aCheckRect, rView.GetGridColor());
//STRIP001
//STRIP001          if(rView.bHlplVisible && rView.bHlplFront)
//STRIP001              DrawHelplines(*pOut);
//STRIP001      }
//STRIP001
//STRIP001      if(bTextEdit)
//STRIP001      {
//STRIP001          ImpPaintOutlinerView(pOut, aCheckRect);
//STRIP001          bColorsDirty = sal_True;
//STRIP001      }
//STRIP001
//STRIP001      if(rView.bRestoreColors)
//STRIP001      {
//STRIP001          aHDCMerk.Restore(*pOut);
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  rView.PostPaint();
//STRIP001  // #37074#: fuer SolidHandles im LiveModus der praesentation
//STRIP001  rView.RestartAfterPaintTimer();
//STRIP001 }


//STRIP001 FASTBOOL SdrPageView::IsReady() const
//STRIP001 {
//STRIP001  FASTBOOL bRet=TRUE;
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 void SdrPageView::DrawPaper(OutputDevice& rOut)
//STRIP001 {
//STRIP001  if( pPage )
//STRIP001     {
//STRIP001      // #103911# use color that was set on this view as background if present
//STRIP001      if( maDocumentColor != COL_AUTO )
//STRIP001      {
//STRIP001          rOut.SetFillColor( maDocumentColor );
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001             const svtools::ColorConfig aColorConfig;
//STRIP001             rOut.SetFillColor( aColorConfig.GetColorValue( svtools::DOCCOLOR ).nColor );
//STRIP001      }
//STRIP001
//STRIP001
//STRIP001         rOut.SetLineColor();
//STRIP001      rOut.DrawRect( GetPageRect() );
//STRIP001     }
//STRIP001 }

//STRIP001 void SdrPageView::DrawPaperBorder(OutputDevice& rOut)
//STRIP001 {
//STRIP001  if( pPage )
//STRIP001     {
//STRIP001      svtools::ColorConfig aColorConfig;
//STRIP001      rOut.SetLineColor( Color(aColorConfig.GetColorValue( svtools::FONTCOLOR ).nColor) );
//STRIP001      rOut.SetFillColor();
//STRIP001      rOut.DrawRect( GetPageRect() );
//STRIP001     }
//STRIP001 }

//STRIP001 void SdrPageView::DrawBorder(OutputDevice& rOut)
//STRIP001 {
//STRIP001  if( pPage && ( pPage->GetLftBorder() || pPage->GetUppBorder() || pPage->GetRgtBorder() || pPage->GetLwrBorder() ) )
//STRIP001     {
//STRIP001         svtools::ColorConfig    aColorConfig;
//STRIP001      Color               aBorderColor;
//STRIP001
//STRIP001         if( Application::GetSettings().GetStyleSettings().GetHighContrastMode() )
//STRIP001             aBorderColor = aColorConfig.GetColorValue( svtools::FONTCOLOR ).nColor;
//STRIP001         else
//STRIP001             aBorderColor = aColorConfig.GetColorValue( svtools::DOCBOUNDARIES ).nColor;
//STRIP001
//STRIP001      rOut.SetLineColor( aBorderColor );
//STRIP001      rOut.SetFillColor();
//STRIP001
//STRIP001      Rectangle aRect(GetPageRect());
//STRIP001      aRect.Left  ()+=pPage->GetLftBorder();
//STRIP001      aRect.Top   ()+=pPage->GetUppBorder();
//STRIP001      aRect.Right ()-=pPage->GetRgtBorder();
//STRIP001      aRect.Bottom()-=pPage->GetLwrBorder();
//STRIP001      rOut.DrawRect(aRect);
//STRIP001     }
//STRIP001 }

#ifdef OS2
#define RGBCOLOR(r,g,b) ((ULONG)(((BYTE)(b) | ((USHORT)(g)<<8)) | (((ULONG)(BYTE)(r))<<16)))
#endif


//STRIP001 void SdrPageView::DrawGrid(OutputDevice& rOut, const Rectangle& rRect, Color aColor)
//STRIP001 {
//STRIP001  if (pPage==NULL)
//STRIP001      return;
//STRIP001
//STRIP001  long nx1=rView.aGridBig.Width();
//STRIP001  long nx2=rView.aGridFin.Width();
//STRIP001  long ny1=rView.aGridBig.Height();
//STRIP001  long ny2=rView.aGridFin.Height();
//STRIP001
//STRIP001  if (nx1==0) nx1=nx2;
//STRIP001  if (nx2==0) nx2=nx1;
//STRIP001  if (ny1==0) ny1=ny2;
//STRIP001  if (ny2==0) ny2=ny1;
//STRIP001  if (nx1==0) { nx1=ny1; nx2=ny2; }
//STRIP001  if (ny1==0) { ny1=nx1; ny2=nx2; }
//STRIP001  if (nx1<0) nx1=-nx1;
//STRIP001  if (nx2<0) nx2=-nx2;
//STRIP001  if (ny1<0) ny1=-ny1;
//STRIP001  if (ny2<0) ny2=-ny2;
//STRIP001
//STRIP001  if (nx1!=0)
//STRIP001  {
//STRIP001      // no more global output size, use window size instead to decide grid sizes
//STRIP001      long nScreenWdt = rOut.GetOutputSizePixel().Width();
//STRIP001      // old: long nScreenWdt=System::GetDesktopRectPixel().GetWidth();
//STRIP001
//STRIP001      // Grid bei kleinen Zoomstufen etwas erweitern
//STRIP001      //Size a1PixSiz(rOut.PixelToLogic(Size(1,1)));
//STRIP001      long nMinDotPix=2;
//STRIP001      long nMinLinPix=4;
//STRIP001
//STRIP001      if (nScreenWdt>=1600)
//STRIP001      {
//STRIP001          nMinDotPix=4;
//STRIP001          nMinLinPix=8;
//STRIP001      }
//STRIP001      else if (nScreenWdt>=1024)
//STRIP001      {
//STRIP001          nMinDotPix=3;
//STRIP001          nMinLinPix=6;
//STRIP001      }
//STRIP001      else
//STRIP001      { // z.B. 640x480
//STRIP001          nMinDotPix=2;
//STRIP001          nMinLinPix=4;
//STRIP001      }
//STRIP001      Size aMinDotDist(rOut.PixelToLogic(Size(nMinDotPix,nMinDotPix)));
//STRIP001      //Size a3PixSiz(rOut.PixelToLogic(Size(2,2)));
//STRIP001      Size aMinLinDist(rOut.PixelToLogic(Size(nMinLinPix,nMinLinPix)));
//STRIP001      FASTBOOL bHoriSolid=nx2<aMinDotDist.Width();
//STRIP001      FASTBOOL bVertSolid=ny2<aMinDotDist.Height();
//STRIP001      // Linienabstand vergroessern (mind. 4 Pixel)
//STRIP001      // Vergroesserung: *2 *5 *10 *20 *50 *100 ...
//STRIP001      int nTgl=0;
//STRIP001      long nVal0=nx1;
//STRIP001      while (nx1<aMinLinDist.Width())
//STRIP001      {
//STRIP001          long a=nx1;
//STRIP001
//STRIP001          if (nTgl==0) nx1*=2;
//STRIP001          if (nTgl==1) nx1=nVal0*5; // => nx1*=2.5
//STRIP001          if (nTgl==2) nx1*=2;
//STRIP001
//STRIP001          nVal0=a;
//STRIP001          nTgl++; if (nTgl>=3) nTgl=0;
//STRIP001      }
//STRIP001      nTgl=0;
//STRIP001      nVal0=ny1;
//STRIP001      while (ny1<aMinLinDist.Height())
//STRIP001      {
//STRIP001          long a=ny1;
//STRIP001
//STRIP001          if (nTgl==0) ny1*=2;
//STRIP001          if (nTgl==1) ny1=nVal0*5; // => ny1*=2.5
//STRIP001          if (nTgl==2) ny1*=2;
//STRIP001
//STRIP001          nVal0=a;
//STRIP001          nTgl++;
//STRIP001
//STRIP001          if (nTgl>=3) nTgl=0;
//STRIP001      }
//STRIP001      // Keine Zwischenpunkte, wenn...
//STRIP001      //if (nx2<a2PixSiz.Width()) nx2=nx1;
//STRIP001      //if (ny2<a2PixSiz.Height()) ny2=ny1;
//STRIP001
//STRIP001      FASTBOOL bHoriFine=nx2<nx1;
//STRIP001      FASTBOOL bVertFine=ny2<ny1;
//STRIP001      FASTBOOL bHoriLines=bHoriSolid || bHoriFine || !bVertFine;
//STRIP001      FASTBOOL bVertLines=bVertSolid || bVertFine;
//STRIP001
//STRIP001      Color aColorMerk( rOut.GetLineColor() );
//STRIP001      rOut.SetLineColor( aColor );
//STRIP001
//STRIP001      FASTBOOL bMap0=rOut.IsMapModeEnabled();
//STRIP001 #ifdef WIN // SetPixel-Profiling fuer Windows
//STRIP001     COLORREF aWinColRef=PALETTERGB(aColor.GetRed()>>8,aColor.GetGreen()>>8,aColor.GetBlue()>>8);
//STRIP001     HDC aWinhDC=Sysdepen::GethDC(rOut);
//STRIP001 #endif
//STRIP001 #ifdef OS2 // SetPixel-Profiling fuer OS/2
//STRIP001      HPS aOS2hPS=Sysdepen::GethPS(rOut);
//STRIP001      LINEBUNDLE aOS2BundleMerker;
//STRIP001      memset(&aOS2BundleMerker,0,sizeof(aOS2BundleMerker));
//STRIP001      GpiQueryAttrs(aOS2hPS,PRIM_LINE,LBB_COLOR,&aOS2BundleMerker);
//STRIP001      LINEBUNDLE aOS2Bundle;
//STRIP001      memset(&aOS2Bundle,0,sizeof(aOS2Bundle));
//STRIP001      aOS2Bundle.lColor=RGBCOLOR(aColor.GetRed()>>8,aColor.GetGreen()>>8,aColor.GetBlue()>>8);
//STRIP001      GpiSetAttrs(aOS2hPS,PRIM_LINE,LBB_COLOR,0,&aOS2Bundle);
//STRIP001      long nOS2MaxYPix=rOut.GetOutputSizePixel().Height()-1;
//STRIP001 #endif
//STRIP001
//STRIP001      //Point aWriterPageOffset(pPage->GetOffset());
//STRIP001      long nWrX=0;//aWriterPageOffset.X();
//STRIP001      long nWrY=0;//aWriterPageOffset.Y();
//STRIP001      Point aOrg(aPgOrg);
//STRIP001      long xo=aOfs.X();
//STRIP001      long yo=aOfs.Y();
//STRIP001      long x1=pPage->GetLftBorder()+1+nWrX;
//STRIP001      long x2=pPage->GetWdt()-pPage->GetRgtBorder()-1+nWrY;
//STRIP001      long y1=pPage->GetUppBorder()+1+nWrX;
//STRIP001      long y2=pPage->GetHgt()-pPage->GetLwrBorder()-1+nWrY;
//STRIP001      const SdrPageGridFrameList* pFrames=pPage->GetGridFrameList(this,NULL);
//STRIP001      USHORT nBufSiz=1024; // 4k Buffer = max. 512 Punkte
//STRIP001      // #90353# long* pBuf = NULL;
//STRIP001      unsigned nGridPaintAnz=1;
//STRIP001      if (pFrames!=NULL) nGridPaintAnz=pFrames->GetCount();
//STRIP001      for (unsigned nGridPaintNum=0; nGridPaintNum<nGridPaintAnz; nGridPaintNum++) {
//STRIP001          if (pFrames!=NULL) {
//STRIP001              const SdrPageGridFrame& rGF=(*pFrames)[nGridPaintNum];
//STRIP001              nWrX=rGF.GetPaperRect().Left();
//STRIP001              nWrY=rGF.GetPaperRect().Top();
//STRIP001              x1=rGF.GetUserArea().Left();
//STRIP001              x2=rGF.GetUserArea().Right();
//STRIP001              y1=rGF.GetUserArea().Top();
//STRIP001              y2=rGF.GetUserArea().Bottom();
//STRIP001              aOrg=rGF.GetUserArea().TopLeft();
//STRIP001              aOrg-=rGF.GetPaperRect().TopLeft();
//STRIP001          }
//STRIP001          if (!rRect.IsEmpty()) {
//STRIP001              Size a1PixSiz(rOut.PixelToLogic(Size(1,1)));
//STRIP001              long nX1Pix=a1PixSiz.Width();  // 1 Pixel Toleranz drauf
//STRIP001              long nY1Pix=a1PixSiz.Height();
//STRIP001              if (x1<rRect.Left()  -nX1Pix/*-nWrX/**/) x1=rRect.Left()  -nX1Pix/*-nWrX/**/;
//STRIP001              if (x2>rRect.Right() +nX1Pix/*-nWrX/**/) x2=rRect.Right() +nX1Pix/*-nWrX/**/;
//STRIP001              if (y1<rRect.Top()   -nY1Pix/*-nWrY/**/) y1=rRect.Top()   -nY1Pix/*-nWrY/**/;
//STRIP001              if (y2>rRect.Bottom()+nY1Pix/*-nWrY/**/) y2=rRect.Bottom()+nY1Pix/*-nWrY/**/;
//STRIP001          }
//STRIP001          Point aPnt;
//STRIP001
//STRIP001          long xBigOrg=aOrg.X()+nWrX;
//STRIP001          while (xBigOrg>=x1) xBigOrg-=nx1;
//STRIP001          while (xBigOrg<x1) xBigOrg+=nx1;
//STRIP001          long xFinOrg=xBigOrg;
//STRIP001          while (xFinOrg>=x1) xFinOrg-=nx2;
//STRIP001          while (xFinOrg<x1) xFinOrg+=nx2;
//STRIP001
//STRIP001          long yBigOrg=aOrg.Y()+nWrY;
//STRIP001          while (yBigOrg>=y1) yBigOrg-=ny1;
//STRIP001          while (yBigOrg<y1) yBigOrg+=ny1;
//STRIP001          long yFinOrg=yBigOrg;
//STRIP001          while (yFinOrg>=y1) yFinOrg-=ny2;
//STRIP001          while (yFinOrg<y1) yFinOrg+=ny2;
//STRIP001
//STRIP001          if( x1 <= x2 && y1 <= y2 )
//STRIP001          {
//STRIP001              if( bHoriLines )
//STRIP001              {
//STRIP001                  ULONG nGridFlags = ( bHoriSolid ? GRID_HORZLINES : GRID_DOTS );
//STRIP001                  UINT16 nSteps = sal_uInt16(nx1 / nx2);
//STRIP001                  UINT32 nRestPerStepMul1000 = nSteps ? ( ((nx1 * 1000L)/ nSteps) - (nx2 * 1000L) ) : 0;
//STRIP001                  UINT32 nStepOffset = 0;
//STRIP001                  UINT16 nPointOffset = 0;
//STRIP001
//STRIP001                  for(UINT16 a=0;a<nSteps;a++)
//STRIP001                  {
//STRIP001                      // Zeichnen
//STRIP001                      rOut.DrawGrid(
//STRIP001                          Rectangle( xo + xFinOrg + (a * nx2) + nPointOffset, yo + yBigOrg, x2, y2 ),
//STRIP001                          Size( nx1, ny1 ), nGridFlags );
//STRIP001
//STRIP001                      // Schritt machen
//STRIP001                      nStepOffset += nRestPerStepMul1000;
//STRIP001                      while(nStepOffset >= 1000)
//STRIP001                      {
//STRIP001                          nStepOffset -= 1000;
//STRIP001                          nPointOffset++;
//STRIP001                      }
//STRIP001                  }
//STRIP001
//STRIP001                  // rOut.DrawGrid( Rectangle( xo + xFinOrg, yo + yBigOrg, x2, y2 ), Size( nx2, ny1 ), nGridFlags );
//STRIP001              }
//STRIP001
//STRIP001              if( bVertLines )
//STRIP001              {
//STRIP001                  ULONG nGridFlags = ( bVertSolid ? GRID_VERTLINES : GRID_DOTS );
//STRIP001                  UINT16 nSteps = sal_uInt16(ny1 / ny2);
//STRIP001                  UINT32 nRestPerStepMul1000 = nSteps ? ( ((ny1 * 1000L)/ nSteps) - (ny2 * 1000L) ) : 0;
//STRIP001                  UINT32 nStepOffset = 0;
//STRIP001                  UINT16 nPointOffset = 0;
//STRIP001
//STRIP001                  for(UINT16 a=0;a<nSteps;a++)
//STRIP001                  {
//STRIP001                      // Zeichnen
//STRIP001                      rOut.DrawGrid(
//STRIP001                          Rectangle( xo + xBigOrg, yo + yFinOrg + (a * ny2) + nPointOffset, x2, y2 ),
//STRIP001                          Size( nx1, ny1 ), nGridFlags );
//STRIP001
//STRIP001                      // Schritt machen
//STRIP001                      nStepOffset += nRestPerStepMul1000;
//STRIP001                      while(nStepOffset >= 1000)
//STRIP001                      {
//STRIP001                          nStepOffset -= 1000;
//STRIP001                          nPointOffset++;
//STRIP001                      }
//STRIP001                  }
//STRIP001
//STRIP001                  // rOut.DrawGrid( Rectangle( xo + xBigOrg, yo + yFinOrg, x2, y2 ), Size( nx1, ny2 ), nGridFlags );
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      // #90353# delete [] pBuf;
//STRIP001      rOut.EnableMapMode(bMap0);
//STRIP001      rOut.SetLineColor(aColorMerk);
//STRIP001 #ifdef OS2 // SetPixel-Profiling fuer OS/2
//STRIP001      // OS2-LineAttribute restaurieren
//STRIP001      GpiSetAttrs(aOS2hPS,PRIM_LINE,LBB_COLOR,0,&aOS2BundleMerker);
//STRIP001 #endif
//STRIP001  }
//STRIP001 }


//STRIP001 void SdrPageView::DrawHelplines(OutputDevice& rOut)
//STRIP001 {
//STRIP001  aHelpLines.DrawAll(rOut,aOfs);
//STRIP001 }


//STRIP001 FASTBOOL SdrPageView::RedrawOne(USHORT nBrkEvent)
//STRIP001 {
//STRIP001  return TRUE;
//STRIP001 }


//STRIP001 FASTBOOL SdrPageView::RedrawUntilInput(USHORT nBrkEvent)
//STRIP001 {
//STRIP001  return TRUE;
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////


//STRIP001 void SdrPageView::RedrawOneLayer(SdrLayerID nId, const Rectangle& rRect, OutputDevice* pOut_, USHORT nPaintMode, const Link* pPaintProc) const
//STRIP001 {
//STRIP001  if (pPage==NULL) return;
//STRIP001  USHORT nWinAnz=pOut_!=NULL ? 1 : rView.GetWinCount();
//STRIP001  if (pPage->GetObjCount()==0) return; // Liste ist leer!
//STRIP001  for (USHORT nWinNum=0; nWinNum<nWinAnz; nWinNum++) {
//STRIP001      OutputDevice* pOut=pOut_!=NULL ? pOut_ : rView.GetWin(nWinNum);
//STRIP001      DBG_ASSERT(pOut!=NULL,"SdrPageView::InitRedraw(): pOut==NULL");
//STRIP001      if (pOut==NULL) break;
//STRIP001
//STRIP001      FASTBOOL bPrinter=(pOut->GetOutDevType()==OUTDEV_PRINTER);
//STRIP001      if (!(bPrinter?&aLayerPrn:&aLayerVisi)->IsSet(nId)) break; // der ist aber nicht druck/sichtbar!
//STRIP001      ExtOutputDevice* pXOut=rView.pXOut;
//STRIP001      pXOut->SetOutDev(pOut);
//STRIP001
//STRIP001      FASTBOOL bDrawAll=rRect.IsEmpty();
//STRIP001
//STRIP001      Size a1PixSiz(pOut->PixelToLogic(Size(1,1)));
//STRIP001      Rectangle aCheckRect(rRect);
//STRIP001      aCheckRect.Left()  -=a1PixSiz.Width();
//STRIP001      aCheckRect.Top()   -=a1PixSiz.Height();
//STRIP001      aCheckRect.Right() +=a1PixSiz.Width();
//STRIP001      aCheckRect.Bottom()+=a1PixSiz.Height();
//STRIP001      aCheckRect-=aOfs; // Rect relativ zur PageView zum checken der Objekte
//STRIP001
//STRIP001      FASTBOOL bTextEdit=rView.IsTextEdit() && rView.pTextEditPV==this;
//STRIP001
//STRIP001      ImpSdrHdcMerk aHDCMerk(*pOut,SDRHDC_SAVEPENANDBRUSHANDFONT,rView.bRestoreColors);
//STRIP001      FASTBOOL bColorsDirty=FALSE;
//STRIP001
//STRIP001      pXOut->SetOffset(aOfs);
//STRIP001      SdrPaintInfoRec aInfoRec;
//STRIP001      aInfoRec.pPV=this;
//STRIP001      aInfoRec.bPrinter=bPrinter;
//STRIP001      aInfoRec.aDirtyRect=rRect;
//STRIP001      aInfoRec.aCheckRect=aCheckRect;
//STRIP001      aInfoRec.pPaintProc=pPaintProc;
//STRIP001
//STRIP001      if (bPrinter) {
//STRIP001          if (rView.IsLineDraftPrn()) nPaintMode|=SDRPAINTMODE_DRAFTLINE;
//STRIP001          if (rView.IsFillDraftPrn()) nPaintMode|=SDRPAINTMODE_DRAFTFILL;
//STRIP001          if (rView.IsTextDraftPrn()) nPaintMode|=SDRPAINTMODE_DRAFTTEXT;
//STRIP001          if (rView.IsGrafDraftPrn()) nPaintMode|=SDRPAINTMODE_DRAFTGRAF;
//STRIP001      } else {
//STRIP001          if (rView.IsLineDraft()) nPaintMode|=SDRPAINTMODE_DRAFTLINE;
//STRIP001          if (rView.IsFillDraft()) nPaintMode|=SDRPAINTMODE_DRAFTFILL;
//STRIP001          if (rView.IsTextDraft()) nPaintMode|=SDRPAINTMODE_DRAFTTEXT;
//STRIP001          if (rView.IsGrafDraft()) nPaintMode|=SDRPAINTMODE_DRAFTGRAF;
//STRIP001          if (rView.IsHideGrafDraft()) nPaintMode|=SDRPAINTMODE_HIDEDRAFTGRAF;
//STRIP001      }
//STRIP001
//STRIP001      aInfoRec.aPaintLayer.ClearAll();
//STRIP001      aInfoRec.aPaintLayer.Set((BYTE)nId);
//STRIP001      aInfoRec.nPaintMode=nPaintMode;
//STRIP001      if (GetObjList()!=pPage) aInfoRec.pAktList=GetObjList();
//STRIP001      if (!bPrinter && rView.ImpIsGlueVisible()) {
//STRIP001          aInfoRec.nPaintMode|=SDRPAINTMODE_GLUEPOINTS;
//STRIP001      }
//STRIP001
//STRIP001      pPage->Paint(*pXOut,aInfoRec,rView.bRestoreColors);
//STRIP001      pXOut->SetOffset(Point(0,0));
//STRIP001
//STRIP001      if (bTextEdit)
//STRIP001      {
//STRIP001          SdrObject* pObj = rView.GetTextEditObject();
//STRIP001          if( pObj && pObj->GetLayer() == nId )
//STRIP001          {
//STRIP001              ImpPaintOutlinerView(pOut,aCheckRect);
//STRIP001              bColorsDirty=TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      if (rView.bRestoreColors /*&& bColorsDirty*/) {
//STRIP001          aHDCMerk.Restore(*pOut);
//STRIP001      }
//STRIP001
//STRIP001      const USHORT nWinNum1 = rView.FindWin( pOut );
//STRIP001      if( nWinNum1 != SDRVIEWWIN_NOTFOUND )
//STRIP001          rView.AfterInitRedraw( nWinNum1 ); // fuer SolidHandles im Writer und Calc (Joe, 13.3.1998)
//STRIP001  }
//STRIP001
//STRIP001  // #72567# removed: rView.PostPaint();
//STRIP001  rView.RestartAfterPaintTimer(); // #36496#: fuer SolidHandles im Writer und Calc
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////


/*N*/ void SdrPageView::AdjHdl()
/*N*/ {
/*N*/   rView.AdjustMarkHdl();
/*N*/ }


/*N*/ void SdrPageView::SetLayer(const XubString& rName, SetOfByte& rBS, FASTBOOL bJa)
/*N*/ {
/*N*/   if (pPage==NULL) return;
/*N*/   SdrLayerID nID=pPage->GetLayerAdmin().GetLayerID(rName,TRUE);
/*N*/   if (nID!=SDRLAYER_NOTFOUND) {
/*N*/       rBS.Set(nID,bJa);
/*N*/         if (&rBS == &aLayerVisi)
/*N*/             LayerVisibilityChanged(nID, bJa);
/*N*/   }
/*N*/ }


/*N*/ FASTBOOL SdrPageView::IsLayer(const XubString& rName, const SetOfByte& rBS) const
/*N*/ {
/*N*/   if(!pPage)
/*N*/       return FALSE;
/*N*/
/*N*/   BOOL bRet(FALSE);
/*N*/
/*N*/   if(rName.Len())
/*N*/   {
/*N*/       SdrLayerID nId = pPage->GetLayerAdmin().GetLayerID(rName, TRUE);
/*N*/
/*N*/       if(nId != SDRLAYER_NOTFOUND)
/*N*/       {
/*N*/           bRet = rBS.IsSet(nId);
/*N*/       }
/*N*/   }
/*N*/   return bRet;
/*N*/ }


//STRIP001 void SdrPageView::SetAllLayers(SetOfByte& rB, FASTBOOL bJa)
//STRIP001 {
//STRIP001  if (bJa) {
//STRIP001      rB.SetAll();
//STRIP001      rB.Clear(SDRLAYER_NOTFOUND);
//STRIP001  } else {
//STRIP001      rB.ClearAll();
//STRIP001  }
//STRIP001     // TODO: LayerVisibilityChanged to be called when necessary
//STRIP001 }


/*?*/ void SdrPageView::LayerVisibilityChanged( const SdrLayerID _nLayerId, bool _bNewVisibility )
/*?*/ {{DBG_ASSERT(0, "STRIP");}//STRIP001
//STRIP001     // adjust the visibility of UNO controls, if necessary
//STRIP001     const SdrPageViewWinList& rWinList = GetWinList();
//STRIP001     const USHORT nWinCount = rWinList.GetCount();
//STRIP001     for ( USHORT i=0; i<nWinCount; ++i )
//STRIP001     {
//STRIP001         const SdrPageViewWinRec& rWinData = rWinList[i];
//STRIP001         const SdrUnoControlList& rWinControls = rWinData.GetControlList();
//STRIP001         const USHORT nControlCount = rWinControls.GetCount();
//STRIP001         for ( USHORT j=0; j<nControlCount; ++j )
//STRIP001         {
//STRIP001             SdrUnoControlRec& rControlData = const_cast< SdrUnoControlRec& >( rWinControls[j] );
//STRIP001                 // I prefer the const_cast over using the various friend relationships
//STRIP001             rControlData.adjustControlVisibility( false );
//STRIP001         }
//STRIP001     }
/*?*/ }

//STRIP001 void SdrPageView::ShowLayerSet(const XubString& rName, FASTBOOL bShow)
//STRIP001 {
//STRIP001  if (pPage==NULL) return;
//STRIP001  SdrLayerSet* pSet=pPage->GetLayerAdmin().GetLayerSet(rName,TRUE);
//STRIP001  if (pSet!=NULL) {
//STRIP001      for (USHORT i=0; i<255; i++) {
//STRIP001          if (pSet->IsMember(BYTE(i))) {
//STRIP001              aLayerVisi.Set(BYTE(i),bShow);
//STRIP001                 LayerVisibilityChanged(static_cast<SdrLayerID>(i), bShow);
//STRIP001          } else {
//STRIP001              if (bShow && pSet->IsExcluded(BYTE(i))) {
//STRIP001                  aLayerVisi.Clear(BYTE(i));
//STRIP001                     LayerVisibilityChanged(static_cast<SdrLayerID>(i), FALSE);
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  if (!bShow) rView.AdjustMarkHdl();
//STRIP001  InvalidateAllWin();
//STRIP001 }


//STRIP001 FASTBOOL SdrPageView::IsLayerSetVisible(const XubString& rName) const
//STRIP001 {
//STRIP001  if (pPage==NULL) return FALSE;
//STRIP001  FASTBOOL bRet=FALSE;
//STRIP001  SdrLayerSet* pSet=pPage->GetLayerAdmin().GetLayerSet(rName,TRUE);
//STRIP001  if (pSet!=NULL) {
//STRIP001      bRet=TRUE;
//STRIP001      USHORT i=0;
//STRIP001      while (bRet && i<255) {
//STRIP001          if (pSet->IsMember(BYTE(i))) {
//STRIP001              bRet=aLayerVisi.IsSet(BYTE(i));
//STRIP001          } else {
//STRIP001              if (pSet->IsExcluded(BYTE(i))) {
//STRIP001                  bRet=!aLayerVisi.IsSet(BYTE(i));
//STRIP001              }
//STRIP001          }
//STRIP001          i++;
//STRIP001      }
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }


/*N*/ FASTBOOL SdrPageView::IsObjMarkable(SdrObject* pObj) const
/*N*/ {
/*N*/   if(pObj)
/*N*/   {
/*N*/       // Vom Markieren ausgeschlossen?
/*N*/       if(pObj->IsMarkProtect())
/*N*/           return FALSE;
/*N*/
/*N*/       // Der Layer muss sichtbar und darf nicht gesperrt sein
/*N*/       SdrLayerID nL = pObj->GetLayer();
/*N*/       return aLayerVisi.IsSet(BYTE(nL)) && !aLayerLock.IsSet(BYTE(nL));
/*N*/   }
/*N*/   return FALSE;
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////


//STRIP001 void SdrPageView::SetPageOrigin(const Point& rOrg)
//STRIP001 {
//STRIP001  if (rOrg!=aPgOrg) {
//STRIP001      aPgOrg=rOrg;
//STRIP001      if (rView.IsGridVisible()) {
//STRIP001          InvalidateAllWin();
//STRIP001      }
//STRIP001  }
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////


//STRIP001 void SdrPageView::ImpInvalidateHelpLineArea(USHORT nNum) const
//STRIP001 {
//STRIP001  if (rView.IsHlplVisible() && nNum<aHelpLines.GetCount()) {
//STRIP001      const SdrHelpLine& rHL=aHelpLines[nNum];
//STRIP001      for (USHORT i=0; i<rView.GetWinCount(); i++) {
//STRIP001          OutputDevice* pOut=rView.GetWin(i);
//STRIP001          if (pOut->GetOutDevType()==OUTDEV_WINDOW) {
//STRIP001              Rectangle aR(rHL.GetBoundRect(*pOut));
//STRIP001              Size aSiz(pOut->PixelToLogic(Size(1,1)));
//STRIP001              aR.Left  ()-=aSiz.Width();
//STRIP001              aR.Right ()+=aSiz.Width();
//STRIP001              aR.Top   ()-=aSiz.Height();
//STRIP001              aR.Bottom()+=aSiz.Height();
//STRIP001              aR.Move(aOfs.X(),aOfs.Y());
//STRIP001              rView.InvalidateOneWin(*(Window*)pOut,aR);
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }


/*N*/ void SdrPageView::SetHelpLines(const SdrHelpLineList& rHLL)
/*N*/ {
/*N*/   aHelpLines=rHLL;
/*N*/   InvalidateAllWin();
/*N*/ }


//STRIP001 void SdrPageView::SetHelpLine(USHORT nNum, const SdrHelpLine& rNewHelpLine)
//STRIP001 {
//STRIP001  if (nNum<aHelpLines.GetCount() && aHelpLines[nNum]!=rNewHelpLine) {
//STRIP001      FASTBOOL bNeedRedraw=TRUE;
//STRIP001      if (aHelpLines[nNum].GetKind()==rNewHelpLine.GetKind()) {
//STRIP001          switch (rNewHelpLine.GetKind()) {
//STRIP001              case SDRHELPLINE_VERTICAL  : if (aHelpLines[nNum].GetPos().X()==rNewHelpLine.GetPos().X()) bNeedRedraw=FALSE; break;
//STRIP001              case SDRHELPLINE_HORIZONTAL: if (aHelpLines[nNum].GetPos().Y()==rNewHelpLine.GetPos().Y()) bNeedRedraw=FALSE; break;
//STRIP001          } // switch
//STRIP001      }
//STRIP001      if (bNeedRedraw) ImpInvalidateHelpLineArea(nNum);
//STRIP001      aHelpLines[nNum]=rNewHelpLine;
//STRIP001      if (bNeedRedraw) ImpInvalidateHelpLineArea(nNum);
//STRIP001  }
//STRIP001 }


//STRIP001 void SdrPageView::DeleteHelpLine(USHORT nNum)
//STRIP001 {
//STRIP001  if (nNum<aHelpLines.GetCount()) {
//STRIP001      ImpInvalidateHelpLineArea(nNum);
//STRIP001      aHelpLines.Delete(nNum);
//STRIP001  }
//STRIP001 }


//STRIP001 void SdrPageView::InsertHelpLine(const SdrHelpLine& rHL, USHORT nNum)
//STRIP001 {
//STRIP001  if (nNum>aHelpLines.GetCount()) nNum=aHelpLines.GetCount();
//STRIP001  aHelpLines.Insert(rHL,nNum);
//STRIP001  if (rView.IsHlplVisible()) {
//STRIP001      if (rView.IsHlplFront()) {
//STRIP001          // Hier optimieren ...
//STRIP001          ImpInvalidateHelpLineArea(nNum);
//STRIP001       } else {
//STRIP001          ImpInvalidateHelpLineArea(nNum);
//STRIP001      }
//STRIP001  }
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////


// Betretene Gruppe und Liste setzen
/*N*/ void SdrPageView::SetAktGroupAndList(SdrObject* pNewGroup, SdrObjList* pNewList)
/*N*/ {
/*N*/   if(pAktGroup != pNewGroup)
/*N*/   {
/*?*/       pAktGroup = pNewGroup;
/*N*/   }
/*N*/   if(pAktList != pNewList)
/*N*/   {
/*N*/       pAktList = pNewList;
/*N*/   }
/*N*/ }

//STRIP001 FASTBOOL SdrPageView::EnterGroup(SdrObject* pObj)
//STRIP001 {
//STRIP001  FASTBOOL bRet=FALSE;
//STRIP001  if (pObj!=NULL && pObj->IsGroupObject()) {
//STRIP001      FASTBOOL bDisInvalidate=rView.pDisabledAttr!=NULL;
//STRIP001      FASTBOOL bGlueInvalidate=!bDisInvalidate && rView.ImpIsGlueVisible();
//STRIP001      if (bGlueInvalidate) rView.GlueInvalidate();
//STRIP001
//STRIP001      // deselect all
//STRIP001      rView.UnmarkAll();
//STRIP001
//STRIP001      // set current group and list
//STRIP001      SdrObjList* pNewObjList = pObj->GetSubList();
//STRIP001      SetAktGroupAndList(pObj, pNewObjList);
//STRIP001
//STRIP001      // select contained object if only one object is contained,
//STRIP001      // else select nothing and let the user decide what to do next
//STRIP001      if(pNewObjList && pNewObjList->GetObjCount() == 1)
//STRIP001      {
//STRIP001          SdrObject* pFirstObject = pNewObjList->GetObj(0L);
//STRIP001
//STRIP001          for(UINT16 nv = 0; nv < rView.GetPageViewCount(); nv++)
//STRIP001              rView.MarkObj(pFirstObject, rView.GetPageViewPvNum(nv));
//STRIP001      }
//STRIP001
//STRIP001      // build new handles
//STRIP001      rView.AdjustMarkHdl();
//STRIP001
//STRIP001      // invalidate only when view wants to visualize group entering
//STRIP001      if(rView.DoVisualizeEnteredGroup())
//STRIP001          InvalidateAllWin();
//STRIP001
//STRIP001      if (bGlueInvalidate)
//STRIP001          rView.GlueInvalidate();
//STRIP001      bRet=TRUE;
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 void SdrPageView::LeaveOneGroup()
//STRIP001 {
//STRIP001  if(GetAktGroup())
//STRIP001  {
//STRIP001      BOOL bDisInvalidate = (rView.pDisabledAttr != NULL);
//STRIP001      BOOL bGlueInvalidate = (!bDisInvalidate && rView.ImpIsGlueVisible());
//STRIP001
//STRIP001      if(bGlueInvalidate)
//STRIP001          rView.GlueInvalidate();
//STRIP001
//STRIP001      SdrObject* pLastGroup = GetAktGroup();
//STRIP001      SdrObject* pParentGroup = GetAktGroup()->GetUpGroup();
//STRIP001      SdrObjList* pParentList = pPage;
//STRIP001
//STRIP001      if(pParentGroup)
//STRIP001          pParentList = pParentGroup->GetSubList();
//STRIP001
//STRIP001      // Alles deselektieren
//STRIP001      rView.UnmarkAll();
//STRIP001
//STRIP001      // Zuweisungen, pAktGroup und pAktList muessen gesetzt sein
//STRIP001      SetAktGroupAndList(pParentGroup, pParentList);
//STRIP001
//STRIP001      // gerade verlassene Gruppe selektieren
//STRIP001      if(pLastGroup)
//STRIP001          for(UINT16 nv = 0; nv < rView.GetPageViewCount(); nv++)
//STRIP001              rView.MarkObj(pLastGroup, rView.GetPageViewPvNum(nv));
//STRIP001
//STRIP001      rView.AdjustMarkHdl();
//STRIP001
//STRIP001      // invalidate only when view wants to visualize group entering
//STRIP001      if(rView.DoVisualizeEnteredGroup())
//STRIP001          InvalidateAllWin();
//STRIP001
//STRIP001      if(bGlueInvalidate)
//STRIP001          rView.GlueInvalidate();
//STRIP001  }
//STRIP001 }


/*N*/ void SdrPageView::LeaveAllGroup()
/*N*/ {
/*N*/   if(GetAktGroup())
/*N*/   {
/*?*/       BOOL bDisInvalidate = (rView.pDisabledAttr != NULL);
/*?*/       BOOL bGlueInvalidate = (!bDisInvalidate && rView.ImpIsGlueVisible());
/*?*/
/*?*/       if(bGlueInvalidate)
/*?*/           {DBG_ASSERT(0, "STRIP"); }//STRIP001 rView.GlueInvalidate();
/*?*/
/*?*/       SdrObject* pLastGroup = GetAktGroup();
/*?*/
/*?*/       // Alles deselektieren
/*?*/       rView.UnmarkAll();
/*?*/
/*?*/       // Zuweisungen, pAktGroup und pAktList muessen gesetzt sein
/*?*/       SetAktGroupAndList(NULL, pPage);
/*?*/
/*?*/       // Oberste letzte Gruppe finden und selektieren
/*?*/       if(pLastGroup)
/*?*/       {
/*?*/           while(pLastGroup->GetUpGroup())
/*?*/               pLastGroup = pLastGroup->GetUpGroup();
/*?*/
/*?*/           for(UINT16 nv = 0; nv < rView.GetPageViewCount(); nv++)
/*?*/               rView.MarkObj(pLastGroup, rView.GetPageViewPvNum(nv));
/*?*/       }
/*?*/
/*?*/       rView.AdjustMarkHdl();
/*?*/
/*?*/       // invalidate only when view wants to visualize group entering
/*?*/       if(rView.DoVisualizeEnteredGroup())
/*?*/           InvalidateAllWin();
/*?*/
/*?*/       if(bGlueInvalidate)
/*?*/           {DBG_ASSERT(0, "STRIP"); }//STRIP001 rView.GlueInvalidate();
/*N*/   }
/*N*/ }


/*N*/ USHORT SdrPageView::GetEnteredLevel() const
/*N*/ {
/*N*/   USHORT nAnz=0;
/*N*/   SdrObject* pGrp=GetAktGroup();
/*N*/   while (pGrp!=NULL) {
/*?*/       nAnz++;
/*?*/       pGrp=pGrp->GetUpGroup();
/*N*/   }
/*N*/   return nAnz;
/*N*/ }


//STRIP001 XubString SdrPageView::GetActualGroupName() const
//STRIP001 {
//STRIP001  if(GetAktGroup())
//STRIP001  {
//STRIP001      XubString aStr(GetAktGroup()->GetName());
//STRIP001
//STRIP001      if(!aStr.Len())
//STRIP001          aStr += sal_Unicode('?');
//STRIP001
//STRIP001      return aStr;
//STRIP001  }
//STRIP001  else
//STRIP001      return String();
//STRIP001 }


//STRIP001 XubString SdrPageView::GetActualPathName(sal_Unicode cSep) const
//STRIP001 {
//STRIP001  XubString aStr;
//STRIP001  BOOL bNamFnd(FALSE);
//STRIP001  SdrObject* pGrp = GetAktGroup();
//STRIP001
//STRIP001  while(pGrp)
//STRIP001  {
//STRIP001      XubString aStr1(pGrp->GetName());
//STRIP001
//STRIP001      if(!aStr1.Len())
//STRIP001          aStr1 += sal_Unicode('?');
//STRIP001      else
//STRIP001          bNamFnd = TRUE;
//STRIP001
//STRIP001      aStr += aStr1;
//STRIP001      pGrp = pGrp->GetUpGroup();
//STRIP001
//STRIP001      if(pGrp)
//STRIP001          aStr += cSep;
//STRIP001  }
//STRIP001
//STRIP001  if(!bNamFnd && GetAktGroup())
//STRIP001  {
//STRIP001      aStr = String();
//STRIP001      aStr += sal_Unicode('(');
//STRIP001      aStr += String::CreateFromInt32( GetEnteredLevel() );
//STRIP001      aStr += sal_Unicode(')');
//STRIP001  }
//STRIP001
//STRIP001  return aStr;
//STRIP001 }


/*N*/ void SdrPageView::CheckAktGroup()
/*N*/ {
/*N*/   SdrObject* pGrp=GetAktGroup();
/*N*/   while (pGrp!=NULL &&
/*N*/          (!pGrp->IsInserted() || pGrp->GetObjList()==NULL ||
/*N*/           pGrp->GetPage()==NULL || pGrp->GetModel()==NULL)) { // irgendwas daneben?
/*N*/       pGrp=pGrp->GetUpGroup();
/*N*/   }
/*N*/   if (pGrp!=GetAktGroup()) {
/*?*/       if (pGrp!=NULL) {DBG_ASSERT(0, "STRIP"); }//STRIP001 EnterGroup(pGrp);
/*N*/       else LeaveAllGroup();
/*N*/   }
/*N*/ }


/*N*/ SvStream& operator<<(SvStream& rOut, const SdrPageView& rPageView)
/*N*/ {
/*N*/   SdrIOHeader aHead(rOut,STREAM_WRITE,SdrIOPgVwID);
/*N*/   {
/*N*/       if (rPageView.pPage!=NULL) {
/*N*/           SdrNamedSubRecord aSubRecord(rOut,STREAM_WRITE,SdrInventor,SDRIORECNAME_PAGVIEW);
/*N*/           rOut<<BOOL(rPageView.bVisible);
/*N*/           rOut<<BOOL(rPageView.pPage->IsMasterPage());
/*N*/           rOut<<rPageView.pPage->GetPageNum();
/*N*/           rOut<<rPageView.aOfs;
/*N*/           rOut<<rPageView.aPgOrg;
/*N*/       }
/*N*/   } {
/*N*/       SdrNamedSubRecord aSubRecord(rOut,STREAM_WRITE,SdrInventor,SDRIORECNAME_PAGVLAYER);
/*N*/       rOut<<rPageView.aLayerVisi;
/*N*/       rOut<<rPageView.aLayerLock;
/*N*/       rOut<<rPageView.aLayerPrn;
/*N*/   } {
/*N*/       SdrNamedSubRecord aSubRecord(rOut,STREAM_WRITE,SdrInventor,SDRIORECNAME_PAGVHELPLINES);
/*N*/       rOut<<rPageView.aHelpLines;
/*N*/   }
/*N*/   //if (GetAktGroup()!=NULL) {
/*N*/   //    // ...
/*N*/   //    //rOut<<aAktGroup;
/*N*/   //}
/*N*/   return rOut;
/*N*/ }


/*N*/ SvStream& operator>>(SvStream& rIn, SdrPageView& rPageView)
/*N*/ {
/*N*/   if (rIn.GetError()!=0) return rIn;
/*N*/   SdrIOHeader aHead(rIn,STREAM_READ);
/*N*/   while (aHead.GetBytesLeft()>0 && rIn.GetError()==0 && !rIn.IsEof()) {
/*N*/       SdrNamedSubRecord aSubRecord(rIn,STREAM_READ);
/*N*/       if (aSubRecord.GetInventor()==SdrInventor) {
/*N*/           switch (aSubRecord.GetIdentifier()) {
/*N*/               case SDRIORECNAME_PAGVIEW: {
/*N*/                   BOOL bVisible;
/*N*/                   BOOL bMaster;
/*N*/                   USHORT nPgNum;
/*N*/                   rIn>>bVisible;
/*N*/                   rPageView.bVisible=bVisible;
/*N*/                   rIn>>bMaster;
/*N*/                   rIn>>nPgNum;
/*N*/                   rIn>>rPageView.aOfs;
/*N*/                   rIn>>rPageView.aPgOrg;
/*N*/                   SdrModel* pMod=rPageView.GetView().GetModel();
/*N*/                   if (!bMaster) rPageView.pPage=pMod->GetPage(nPgNum);
/*N*/                   else rPageView.pPage=pMod->GetMasterPage(nPgNum);
/*N*/                   rPageView.pAktList=rPageView.pPage;
/*N*/               } break;
/*N*/               case SDRIORECNAME_PAGVLAYER: {
/*N*/                   rIn>>rPageView.aLayerVisi;
/*N*/                   rIn>>rPageView.aLayerLock;
/*N*/                   rIn>>rPageView.aLayerPrn;
/*N*/               } break;
/*N*/               case SDRIORECNAME_PAGVHELPLINES: {
/*N*/                   rIn>>rPageView.aHelpLines;
/*N*/               } break;
/*N*/               case SDRIORECNAME_PAGVAKTGROUP: {
/*N*/                   //rIn>>aAktGroup; fehlende Implementation!
/*N*/               } break;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   return rIn;
/*N*/ }

// #103834# Set background color for svx at SdrPageViews
//STRIP001 void SdrPageView::SetApplicationBackgroundColor(Color aBackgroundColor)
//STRIP001 {
//STRIP001  maBackgroundColor = aBackgroundColor;
//STRIP001 }
//STRIP001
//STRIP001 // #103911# Set document color for svx at SdrPageViews
//STRIP001 void SdrPageView::SetApplicationDocumentColor(Color aDocumentColor)
//STRIP001 {
//STRIP001  maDocumentColor = aDocumentColor;
//STRIP001 }
//STRIP001
//STRIP001 Color SdrPageView::GetApplicationDocumentColor() const
//STRIP001 {
//STRIP001  return maDocumentColor;
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////


