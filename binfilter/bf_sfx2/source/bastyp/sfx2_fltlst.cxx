/*************************************************************************
 *
 *  $RCSfile: sfx2_fltlst.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:40:08 $
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

#include "fltlst.hxx"

//*****************************************************************************************************************
//  includes
//*****************************************************************************************************************
#ifndef _COM_SUN_STAR_UNO_SEQUENCE_HXX_
#include <com/sun/star/uno/Sequence.hxx>
#endif

#ifndef _COM_SUN_STAR_UNO_ANY_HXX_
#include <com/sun/star/uno/Any.hxx>
#endif

#ifndef _COMPHELPER_PROCESSFACTORY_HXX_
#include <comphelper/processfactory.hxx>
#endif

#include "sfxuno.hxx"

#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif
namespace binfilter {

//*****************************************************************************************************************
//  namespaces
//*****************************************************************************************************************
using namespace ::com::sun::star;

//*****************************************************************************************************************
//  definitions
//*****************************************************************************************************************

/*-************************************************************************************************************//**
    @short          ctor
    @descr          These initialize an instance of a SfxFilterListener class. Created object listen automaticly
                    on right FilterFactory-Service for all changes and synchronize right SfxFilterContainer with
                    corresponding framework-cache.
                    We use given "sFactory" value to decide which query must be used to fill "pContainer" with new values.
                    Given "pContainer" hold us alive as uno reference and we use it to syschronize it with framework caches.
                    We will die, if he die! see dtor for further informations.

    @seealso        dtor
    @seealso        class framework::FilterCache
    @seealso        service ::document::FilterFactory

    @param          "sFactory"  , short name of module which contains filter container
    @param          "pContainer", pointer to filter container which will be informed
    @return         -

    @onerror        We show some assertions in non product version.
                    Otherwise we do nothing!
    @threadsafe     yes

    @last_change    17.10.2001 10:27
*//*-*************************************************************************************************************/
/*N*/ SfxFilterListener::SfxFilterListener( const ::rtl::OUString&    sFactory   ,
/*N*/                                             SfxFilterContainer* pContainer )
/*N*/     :   m_aMutex    (            )
/*N*/     ,   m_pContainer( pContainer )
/*N*/ {
/*N*/     // search for right factory long name by using given shortname.
/*N*/     // These value is neccessary for "ReadExternalFilter()" call during our "flushed()" function.
/*N*/     m_sFactory = ::rtl::OUString();
/*N*/     if( sFactory == DEFINE_CONST_OUSTRING("swriter") )
/*N*/         m_sFactory = DEFINE_CONST_OUSTRING("com.sun.star.text.TextDocument");
/*N*/     else
/*N*/     if( sFactory == DEFINE_CONST_OUSTRING("swriter/web") )
/*N*/         m_sFactory = DEFINE_CONST_OUSTRING("com.sun.star.text.WebDocument");
/*N*/     else
/*N*/     if( sFactory == DEFINE_CONST_OUSTRING("swriter/GlobalDocument") )
/*N*/         m_sFactory = DEFINE_CONST_OUSTRING("com.sun.star.text.GlobalDocument");
/*N*/     else
/*N*/     if( sFactory == DEFINE_CONST_OUSTRING("schart") )
/*N*/         m_sFactory = DEFINE_CONST_OUSTRING("com.sun.star.chart.ChartDocument");
/*N*/     else
/*N*/     if( sFactory == DEFINE_CONST_OUSTRING("scalc") )
/*N*/         m_sFactory = DEFINE_CONST_OUSTRING("com.sun.star.sheet.SpreadsheetDocument");
/*N*/     else
/*N*/     if( sFactory == DEFINE_CONST_OUSTRING("sdraw") )
/*N*/         m_sFactory = DEFINE_CONST_OUSTRING("com.sun.star.drawing.DrawingDocument");
/*N*/     else
/*N*/     if( sFactory == DEFINE_CONST_OUSTRING("simpress") )
/*N*/         m_sFactory = DEFINE_CONST_OUSTRING("com.sun.star.presentation.PresentationDocument");
/*N*/     else
/*N*/     if( sFactory == DEFINE_CONST_OUSTRING("smath") )
/*N*/         m_sFactory = DEFINE_CONST_OUSTRING("com.sun.star.formula.FormulaProperties");
/*N*/
/*N*/     OSL_ENSURE( !(m_sFactory.getLength()<1), "SfxFilterListener::SfxFilterListener()\nUnknown factory found! Can't listen for nothing ...\n" );
/*N*/
/*N*/     // Start listening on framework filter cache only, if factory is valid!
/*N*/     if( m_sFactory.getLength() > 0 )
/*N*/     {
/*N*/         uno::Reference< lang::XMultiServiceFactory > xSmgr = ::legacy_binfilters::getLegacyProcessServiceFactory();
/*N*/         if( xSmgr.is() == sal_True )
/*N*/         {
/*N*/             uno::Reference< util::XFlushable > xNotifier( xSmgr->createInstance( DEFINE_CONST_OUSTRING("com.sun.star.document.FilterFactory") ), uno::UNO_QUERY );
/*N*/             if( xNotifier.is() == sal_True )
/*N*/             {
/*N*/                 m_xFilterCache = xNotifier;
/*N*/                 m_xFilterCache->addFlushListener( this );
/*N*/             }
/*N*/
/*N*/             xNotifier = uno::Reference< util::XFlushable >( xSmgr->createInstance( DEFINE_CONST_OUSTRING("com.sun.star.document.TypeDetection") ), uno::UNO_QUERY );
/*N*/             if( xNotifier.is() == sal_True )
/*N*/             {
/*N*/                 m_xTypeCache = xNotifier;
/*N*/                 m_xTypeCache->addFlushListener( this );
/*N*/             }
/*N*/         }
/*N*/     }
/*N*/ }

//STRIP001 /*-************************************************************************************************************//**
//STRIP001     @short          dtor
//STRIP001     @descr          These deinitialize instance. If our corresponding SfxFilterContainer will die - he release our
//STRIP001                     reference. Normaly it should be the only one - so we can die too.
//STRIP001
//STRIP001     @seealso        ctor
//STRIP001     @seealso        method diposing()
//STRIP001
//STRIP001     @param          -
//STRIP001     @return         -
//STRIP001
//STRIP001     @onerror        -
//STRIP001     @threadsafe     yes
//STRIP001
//STRIP001     @last_change    16.10.2001 14:26
//STRIP001 *//*-*************************************************************************************************************/
/*?*/ SfxFilterListener::~SfxFilterListener()
/*?*/ {DBG_BF_ASSERT(0, "STRIP");//STRIP001
//STRIP001     if( m_xTypeCache.is() )
//STRIP001     {
//STRIP001         m_xTypeCache->removeFlushListener( this );
//STRIP001         m_xTypeCache = uno::Reference< util::XFlushable >();
//STRIP001     }
//STRIP001     if( m_xFilterCache.is() )
//STRIP001     {
//STRIP001         m_xFilterCache->removeFlushListener( this );
//STRIP001         m_xFilterCache = uno::Reference< util::XFlushable >();
//STRIP001     }
//STRIP001
//STRIP001     m_sFactory   = ::rtl::OUString();
//STRIP001     m_pContainer = NULL;
/*?*/ }

//STRIP001 /*-************************************************************************************************************//**
//STRIP001     @short          callback from framework FilterCache
//STRIP001     @descr          If some filter was changed in framework cache - we are notified by FilterFactory service
//STRIP001                     by calling this method. We have to get all neccessary informations about changes and
//STRIP001                     sysnchronize our internal set SfxFilterContainer with it.
//STRIP001                     In the moment we don't support selective changes - we reload ALL filters for current factory!
//STRIP001
//STRIP001     @seealso        interface XFlushable
//STRIP001     @seealso        interface XFlushListener
//STRIP001     @seealso        service ::document::FilterFactory
//STRIP001
//STRIP001     @param          "aEvent", describe source of event
//STRIP001     @return         -
//STRIP001
//STRIP001     @onerror        We ignore call!
//STRIP001     @threadsafe     yes
//STRIP001
//STRIP001     @last_change    17.10.2001 10:28
//STRIP001 *//*-*************************************************************************************************************/
/*?*/ void SAL_CALL SfxFilterListener::flushed( const lang::EventObject& aSource ) throw( uno::RuntimeException )
/*?*/ {{DBG_BF_ASSERT(0, "STRIP"); }//STRIP001
//STRIP001     /* SAFE AREA ----------------------------------------------------------------------------------------------- */
//STRIP001     ::osl::ResettableMutexGuard aGuard( m_aMutex );
//STRIP001
//STRIP001     if( m_pContainer != NULL )
//STRIP001     {
//STRIP001         uno::Reference< util::XFlushable > xContainer( aSource.Source, uno::UNO_QUERY );
//STRIP001         if(
//STRIP001             (xContainer.is()                                       ) &&
//STRIP001             (xContainer==m_xTypeCache || xContainer==m_xFilterCache) &&
//STRIP001             (m_sFactory.getLength() > 0                            )
//STRIP001           )
//STRIP001         {
//STRIP001             m_pContainer->ReadExternalFilters( m_sFactory );
//STRIP001         }
//STRIP001     }
/*?*/ }

//STRIP001 /*-************************************************************************************************************//**
//STRIP001     @short          deinitialize object
//STRIP001     @descr          If our framework filter cache will die BEFORE SfxFilterContainer will do that ...
//STRIP001                     we get this disposing message. So we should cancel all further work ...
//STRIP001
//STRIP001     @seealso        dtor
//STRIP001
//STRIP001     @param          "aSource", source of event
//STRIP001     @return         -
//STRIP001
//STRIP001     @onerror        -
//STRIP001     @threadsafe     yes
//STRIP001
//STRIP001     @last_change    16.10.2001 14:30
//STRIP001 *//*-*************************************************************************************************************/
/*?*/ void SAL_CALL SfxFilterListener::disposing( const lang::EventObject& aSource ) throw( uno::RuntimeException )
/*?*/ {{DBG_BF_ASSERT(0, "STRIP"); }//STRIP001
//STRIP001     /* SAFE AREA ----------------------------------------------------------------------------------------------- */
//STRIP001     ::osl::ResettableMutexGuard aGuard( m_aMutex );
//STRIP001
//STRIP001     uno::Reference< util::XFlushable > xNotifier( aSource.Source, uno::UNO_QUERY );
//STRIP001     if (!xNotifier.is())
//STRIP001         return;
//STRIP001
//STRIP001     if (xNotifier == m_xTypeCache)
//STRIP001     {
//STRIP001         m_xTypeCache->removeFlushListener( this );
//STRIP001         m_xTypeCache = uno::Reference< util::XFlushable >();
//STRIP001     }
//STRIP001     else
//STRIP001     if (xNotifier == m_xFilterCache)
//STRIP001     {
//STRIP001         m_xFilterCache->removeFlushListener( this );
//STRIP001         m_xFilterCache = uno::Reference< util::XFlushable >();
//STRIP001     }
/*?*/ }
}
