/*************************************************************************
 *
 *  $RCSfile: sfx2_fltfnc.cxx,v $
 *
 *  $Revision: 1.10 $
 *
 *  last change: $Author: obo $ $Date: 2005-07-18 11:48:54 $
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

// auto strip #include "fltfnc.hxx"

// auto strip #ifndef _COM_SUN_STAR_UNO_EXCEPTION_HPP_
// auto strip #include <com/sun/star/uno/Exception.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_BEANS_PROPERTYVALUE_HPP_
// auto strip #include <com/sun/star/beans/PropertyValue.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_CONTAINER_XNAMEACCESS_HPP_
// auto strip #include <com/sun/star/container/XNameAccess.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_DATATRANSFER_DATAFLAVOR_HPP_
// auto strip #include <com/sun/star/datatransfer/DataFlavor.hpp>
// auto strip #endif

#ifndef _EXCHANGE_HXX //autogen
#include <sot/exchange.hxx>
#endif
// auto strip #ifndef _CONFIG_HXX
// auto strip #include <tools/config.hxx>
// auto strip #endif
// auto strip #ifndef _SB_SBMETH_HXX //autogen
// auto strip #include <basic/sbmeth.hxx>
// auto strip #endif
// auto strip #ifndef _BASMGR_HXX //autogen
// auto strip #include <basic/basmgr.hxx>
// auto strip #endif
// auto strip #ifndef _SB_SBSTAR_HXX //autogen
// auto strip #include <basic/sbstar.hxx>
// auto strip #endif
// auto strip #ifndef _SBX_SBXOBJECT_HXX //autogen
// auto strip #include <basic/sbxobj.hxx>
// auto strip #endif
#ifndef __SBX_SBXMETHOD_HXX //autogen
#include <basic/sbxmeth.hxx>
#endif
// auto strip #ifndef _SBXCORE_HXX //autogen
// auto strip #include <basic/sbxcore.hxx>
// auto strip #endif
// auto strip #ifndef _MSGBOX_HXX //autogen
// auto strip #include <vcl/msgbox.hxx>
// auto strip #endif
// auto strip #ifndef _RTL_USTRING_HXX //autogen
// auto strip #include <rtl/ustring.hxx>
// auto strip #endif
#ifndef _RTL_USTRBUF_HXX_
#include <rtl/ustrbuf.hxx>
#endif
// auto strip #ifndef _SFXENUMITEM_HXX //autogen
// auto strip #include <svtools/eitem.hxx>
// auto strip #endif
// auto strip #ifndef _SFXINTITEM_HXX //autogen
// auto strip #include <svtools/intitem.hxx>
// auto strip #endif
#ifndef _SFXSTRITEM_HXX //autogen
#include <svtools/stritem.hxx>
#endif
// auto strip #ifndef _SVSTOR_HXX //autogen
// auto strip #include <so3/svstor.hxx>
// auto strip #endif
// STRIP001 #ifndef _EXTATTR_HXX
// STRIP001 #include <svtools/extattr.hxx>
// STRIP001 #endif
// auto strip #ifndef _LCKBITEM_HXX //autogen
// auto strip #include <svtools/lckbitem.hxx>
// auto strip #endif
// auto strip #ifndef _INETTYPE_HXX //autogen
// auto strip #include <svtools/inettype.hxx>
// auto strip #endif
// auto strip #ifndef _SFXRECTITEM_HXX
// auto strip #include <svtools/rectitem.hxx>
// auto strip #endif

// auto strip #ifndef _COM_SUN_STAR_DOCUMENT_XDOCUMENTINFO_HPP_
// auto strip #include <com/sun/star/document/XDocumentInfo.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_DOCUMENT_XDOCUMENTINFOSUPPLIER_HPP_
// auto strip #include <com/sun/star/document/XDocumentInfoSupplier.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_DOCUMENT_XSTANDALONEDOCUMENTINFO_HPP_
// auto strip #include <com/sun/star/document/XStandaloneDocumentInfo.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_FRAME_XDISPATCHPROVIDERINTERCEPTOR_HPP_
// auto strip #include <com/sun/star/frame/XDispatchProviderInterceptor.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_FRAME_XDISPATCH_HPP_
// auto strip #include <com/sun/star/frame/XDispatch.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_FRAME_XDISPATCHPROVIDER_HPP_
// auto strip #include <com/sun/star/frame/XDispatchProvider.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_FRAME_XSTATUSLISTENER_HPP_
// auto strip #include <com/sun/star/frame/XStatusListener.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_FRAME_FRAMESEARCHFLAG_HPP_
// auto strip #include <com/sun/star/frame/FrameSearchFlag.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_FRAME_XDISPATCHPROVIDERINTERCEPTION_HPP_
// auto strip #include <com/sun/star/frame/XDispatchProviderInterception.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_FRAME_FEATURESTATEEVENT_HPP_
// auto strip #include <com/sun/star/frame/FeatureStateEvent.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_FRAME_DISPATCHDESCRIPTOR_HPP_
// auto strip #include <com/sun/star/frame/DispatchDescriptor.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_FRAME_XCONTROLLER_HPP_
// auto strip #include <com/sun/star/frame/XController.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_FRAME_XFRAMEACTIONLISTENER_HPP_
// auto strip #include <com/sun/star/frame/XFrameActionListener.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_FRAME_XCOMPONENTLOADER_HPP_
// auto strip #include <com/sun/star/frame/XComponentLoader.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_FRAME_XFRAME_HPP_
// auto strip #include <com/sun/star/frame/XFrame.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_FRAME_FRAMEACTIONEVENT_HPP_
// auto strip #include <com/sun/star/frame/FrameActionEvent.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_FRAME_FRAMEACTION_HPP_
// auto strip #include <com/sun/star/frame/FrameAction.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_FRAME_XFRAMELOADER_HPP_
// auto strip #include <com/sun/star/frame/XFrameLoader.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_FRAME_XLOADEVENTLISTENER_HPP_
// auto strip #include <com/sun/star/frame/XLoadEventListener.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_FRAME_XFILTERDETECT_HPP_
// auto strip #include <com/sun/star/frame/XFilterDetect.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_PLUGIN_PLUGINMODE_HPP_
// auto strip #include <com/sun/star/plugin/PluginMode.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_PLUGIN_PLUGINDESCRIPTION_HPP_
// auto strip #include <com/sun/star/plugin/PluginDescription.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_PLUGIN_PLUGINEXCEPTION_HPP_
// auto strip #include <com/sun/star/plugin/PluginException.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_PLUGIN_PLUGINVARIABLE_HPP_
// auto strip #include <com/sun/star/plugin/PluginVariable.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_PLUGIN_XPLUGIN_HPP_
// auto strip #include <com/sun/star/plugin/XPlugin.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_PLUGIN_XPLUGINMANAGER_HPP_
// auto strip #include <com/sun/star/plugin/XPluginManager.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_PLUGIN_XPLUGINCONTEXT_HPP_
// auto strip #include <com/sun/star/plugin/XPluginContext.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_LOADER_XIMPLEMENTATIONLOADER_HPP_
// auto strip #include <com/sun/star/loader/XImplementationLoader.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_LOADER_CANNOTACTIVATEFACTORYEXCEPTION_HPP_
// auto strip #include <com/sun/star/loader/CannotActivateFactoryException.hpp>
// auto strip #endif
// auto strip #ifndef _UNOTOOLS_PROCESSFACTORY_HXX
// auto strip #include <comphelper/processfactory.hxx>
// auto strip #endif

#include <sal/types.h>
#include <com/sun/star/uno/Reference.h>
#include <com/sun/star/ucb/XContent.hpp>
// auto strip #include <rtl/ustring.hxx>
#include <vos/process.hxx>
// auto strip #include <svtools/pathoptions.hxx>

// auto strip #ifndef _L2TXTENC_HXX
// auto strip #include <tools/l2txtenc.hxx>
// auto strip #endif

#include <rtl/logfile.hxx>

using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::ucb;
using namespace ::rtl;
using namespace ::vos;

#ifndef _SVTOOLS_CTYPEITM_HXX
#include <svtools/ctypeitm.hxx>
#endif
#ifndef _SFXECODE_HXX
#include <svtools/sfxecode.hxx>
#endif

#ifndef INCLUDED_SVTOOLS_SYSLOCALE_HXX
#include <svtools/syslocale.hxx>
#endif

// auto strip #include "app.hxx"
// auto strip #include "sfxhelp.hxx"
// auto strip #include "sfxbasic.hxx"
// auto strip #include "docfilt.hxx"
// auto strip #include "docfac.hxx"
// auto strip #include "sfxtypes.hxx"
// auto strip #include "sfxuno.hxx"
#include "docfile.hxx"
// auto strip #include "progress.hxx"
#include "loadenv.hxx"
// auto strip #include "openflag.hxx"
#include "bastyp.hrc"
// auto strip #include "sfxresid.hxx"
// auto strip #include "doctempl.hxx"
// auto strip #include "frame.hxx"
#include "dispatch.hxx"
#include "urlframe.hxx"
// auto strip #include "topfrm.hxx"
// auto strip #include "plugwin.hxx"
// auto strip #include "helper.hxx"
#include "fltlst.hxx"

// wg. EXPLORER_BROWSER
#include "request.hxx"
// auto strip #include "nfltdlg.hxx"
#include "arrdecl.hxx"
// auto strip #include "appdata.hxx"
// auto strip #include "appuno.hxx"
// auto strip #include "viewfrm.hxx"

#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif
namespace binfilter {

#define SFX_STR_OVERRIDE "Override"

#ifndef ERRCODE_SFX_RESTART
#define ERRCODE_SFX_RESTART 0
#endif

struct FlagMapping_Impl
{
    const char* pName;
    SfxFilterFlags nValue;
};

//----------------------------------------------------------------
/*N*/ inline String ToUpper_Impl( const String &rStr )
/*N*/ {
/*N*/     return SvtSysLocale().GetCharClass().upper( rStr );
/*N*/ }

//----------------------------------------------------------------
class SfxFilterContainer_Impl
{
public:
    SfxFilterContainer_Impl() : bLoadPending( sal_False ) {}
    SfxFilterList_Impl aList;
    String aName;
    sal_Bool bLoadPending;
    SfxFilterContainerFlags eFlags;
    ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > xCacheSync; // listener on framework::FilterCache to synchronize our two caches!

//STRIP001     void     syncDefaults( const ::com::sun::star::uno::Sequence< ::rtl::OUString >& lNew );
//STRIP001     sal_Bool equalFilterNames( const String& s1, const ::rtl::OUString& s2 ) const;
};


//----------------------------------------------------------------

/*N*/ SfxFilterContainer::SfxFilterContainer( const String& rName )
/*N*/ {
/*N*/     pImpl = new SfxFilterContainer_Impl;
/*N*/   pImpl->eFlags = 0;
/*N*/     pImpl->aName = rName;
/*N*/
/*N*/     // Start synchronize listener for framework::FilterCache changes ...
/*N*/     // But don't do it for basic factory - they has no filters!
/*N*/     if( rName.EqualsAscii("sbasic") == sal_False )
/*N*/     {
/*N*/         SfxFilterListener* pListener = new SfxFilterListener( rName, this );
/*N*/         pImpl->xCacheSync = ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface >( static_cast< ::com::sun::star::util::XFlushListener* >(pListener), ::com::sun::star::uno::UNO_QUERY );
/*N*/     }
/*N*/ }

//----------------------------------------------------------------

/*N*/ SfxFilterContainer::~SfxFilterContainer()
/*N*/ {
/*N*/     // Let synchronize listener die - we don't need it any longer!
/*N*/     pImpl->xCacheSync = ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface >();
/*N*/
/*N*/     SfxFilterList_Impl& rList = pImpl->aList;
/*N*/     sal_uInt16 nCount = (sal_uInt16 )rList.Count();
/*N*/     for( sal_uInt16 n = 0; n<nCount; n++ )
/*N*/         delete rList.GetObject( n );
/*N*/     delete pImpl;
/*N*/ }

/*N*/ SfxFilterContainerFlags SfxFilterContainer::GetFlags() const
/*N*/ {
/*N*/   return pImpl->eFlags;
/*N*/ }

/*N*/ void SfxFilterContainer::SetFlags( SfxFilterContainerFlags eFlags )
/*N*/ {
/*N*/   pImpl->eFlags = eFlags;
/*N*/ }

//----------------------------------------------------------------

/*N*/ const SfxFilter* SfxFilterContainer::GetFilter4Protocol(
/*N*/     SfxMedium& rMed, SfxFilterFlags nMust, SfxFilterFlags nDont ) const
/*   [Beschreibung]

     Gibt den Filter zu einem bestimmten Protokoll zurueck. Diese Methode
     darf sich nicht auf Inhalte beziehen, sondern soll allein anhand von
     Protokoll / ::com::sun::star::util::URL einen Filter auswaehlen.
     In der Basisimplementierung werden einige Protokolle direkt auf
     GetFilter4FilterName abgebildet, man zur Integration des Filters
     in die Filterdetection einfach einen Filter des Protokollnames anlegen
     kann.
 */
/*N*/ {
/*N*/   const INetURLObject& rObj = rMed.GetURLObject();
/*N*/   String aName = rMed.GetURLObject().GetMainURL( INetURLObject::NO_DECODE );
/*N*/   // Hier noch pruefen, ob das Doc im Browser dargestellt werden soll
/*N*/   SFX_ITEMSET_ARG( rMed.GetItemSet(), pTargetItem, SfxStringItem,
/*N*/                    SID_TARGETNAME, sal_False);
/*N*/     if( pTargetItem && pTargetItem->GetValue().EqualsAscii("_beamer") )
/*N*/       return 0;
/*N*/     return GetFilter4Protocol( aName, nMust, nDont );
/*N*/ }

/*N*/ const SfxFilter* SfxFilterContainer::GetFilter4Protocol( const String& rName, SfxFilterFlags nMust, SfxFilterFlags nDont ) const
/*N*/ {
/*N*/     String aName( rName );
/*N*/   aName.ToLowerAscii();
/*N*/   sal_uInt16 nCount = ( sal_uInt16 ) pImpl->aList.Count();
/*N*/   for( sal_uInt16 n = 0; n < nCount; n++ )
/*N*/   {
/*N*/       const SfxFilter* pFilter = pImpl->aList.GetObject( n );
/*N*/       SfxFilterFlags nFlags = pFilter->GetFilterFlags();
/*N*/       String aString( pFilter->GetURLPattern());
/*N*/       if ( (nFlags & nMust) == nMust && !(nFlags & nDont ) &&
/*N*/            WildCard(aString ).Matches( aName ) )
/*N*/           return pFilter;
/*N*/   }
/*N*/   return 0;
/*N*/ }

//----------------------------------------------------------------

/*?*/ sal_uInt32 SfxFilterContainer::Execute( SfxMedium& rMedium, SfxFrame*& pFrame) const
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001
//STRIP001  return ERRCODE_ABORT;
/*?*/ }

//----------------------------------------------------------------

/*N*/ sal_uInt16 SfxFilterContainer::GetFilterCount() const
/*N*/ {
/*N*/   // Dazu muessen die Filter geladen werden
/*N*/     return (sal_uInt16) pImpl->aList.Count();
/*N*/ }

//----------------------------------------------------------------

/*N*/ const SfxFilter* SfxFilterContainer::GetFilter( sal_uInt16 nPos ) const
/*N*/ {
/*N*/     return pImpl->aList.GetObject( nPos );
/*N*/ }

/*N*/ const SfxFilter* SfxFilterContainer::GetAnyFilter( SfxFilterFlags nMust, SfxFilterFlags nDont ) const
/*N*/ {
/*N*/     sal_uInt16 nCount = ( sal_uInt16 ) pImpl->aList.Count();
/*N*/     for( sal_uInt16 n = 0; n < nCount; n++ )
/*N*/     {
/*N*/         const SfxFilter* pFilter = pImpl->aList.GetObject( n );
/*N*/         SfxFilterFlags nFlags = pFilter->GetFilterFlags();
/*N*/         if ( (nFlags & nMust) == nMust && !(nFlags & nDont ) )
/*N*/             return pFilter;
/*N*/     }
/*N*/
/*N*/     return NULL;
/*N*/ }

//----------------------------------------------------------------
/*   [Beschreibung]

     Da die meisten GetFilter4xxx Routinen in einem Container einfach eine
     Abfrage ueber alle enthaltenen Filter durchlaufen, sind diese in
     einem Makro kodiert.

     nMust sind die Flags, die gesetzt sein muessen, damit der Filter
     in Betracht gezogen wird, nDont duerfen nicht gesetzt sein.
 */

#define IMPL_CONTAINER_LOOP( aMethod, aArgType, aTest )         \
/*?*/ const SfxFilter* SfxFilterContainer::aMethod(                   \
/*?*/     aArgType aArg, SfxFilterFlags nMust, SfxFilterFlags nDont ) const \
/*?*/ {                                                               \
/*?*/     const SfxFilter* pFirstFilter=0;                            \
/*?*/     sal_uInt16 nCount = ( sal_uInt16 ) pImpl->aList.Count();    \
/*?*/     for( sal_uInt16 n = 0; n < nCount; n++ )                    \
/*?*/     {                                                           \
/*?*/         const SfxFilter* pFilter = pImpl->aList.GetObject( n ); \
/*?*/         SfxFilterFlags nFlags = pFilter->GetFilterFlags();      \
/*?*/         if ( (nFlags & nMust) == nMust &&                       \
/*?*/              !(nFlags & nDont ) && aTest )                      \
/*?*/         {                                                       \
/*?*/             if ( pFilter->GetFilterFlags() & SFX_FILTER_PREFERED ) \
/*?*/                 return pFilter;                                 \
/*?*/             else if ( !pFirstFilter )                           \
/*?*/                 pFirstFilter = pFilter;                         \
/*?*/         }                                                       \
/*?*/     }                                                           \
/*?*/     return pFirstFilter;                                        \
/*?*/ }

/*   [Beschreibung]

     Ermitelt einen Filter nach seinem Namen. Dieser enthaelt vorangestellt
     den Namen des Containers, falls er nicht im DefaultContainer steckt.
 */

/*N*/ IMPL_CONTAINER_LOOP( GetFilter, const String&,
/*N*/     ( pFilter->GetFilterNameWithPrefix().CompareIgnoreCaseToAscii( aArg ) == COMPARE_EQUAL ||
/*N*/         pFilter->GetFilterName().CompareIgnoreCaseToAscii( aArg ) == COMPARE_EQUAL ) )

/*   [Beschreibung]
     Ermitelt einen Filter nach seinem Mimetypen.
 */
/*?*/ IMPL_CONTAINER_LOOP(
/*?*/     GetFilter4Mime, const String&,
/*?*/     pFilter->GetMimeType().CompareIgnoreCaseToAscii( aArg ) == COMPARE_EQUAL )

/*   [Beschreibung]
     Ermitelt einen Filter nach seinem FilterNamen. Dies ist der Name ohne
     vorangestellten Containernamen.
 */
/*N*/ IMPL_CONTAINER_LOOP(
/*N*/     GetFilter4FilterName, const String&,
/*N*/     pFilter->GetFilterName().CompareIgnoreCaseToAscii(aArg ) == COMPARE_EQUAL )

/*   [Beschreibung]
     Ermitelt einen Filter nach seiner ClipboardID. Diese steckt im Storage.
 */
/*N*/ IMPL_CONTAINER_LOOP(
/*N*/     GetFilter4ClipBoardId, sal_uInt32, aArg && pFilter->GetFormat() == aArg )

#ifdef MAC
#define CONDITION \
     String( aArg ).Erase( 5 ) == String( pFilter->GetTypeName() ).Erase( 5 )
#else
#define CONDITION \
     aArg == pFilter->GetTypeName()
#endif
/*   [Beschreibung]
     Ermitelt einen Filter nach seinen Extended Attributes.
     Nur auf MAC und OS/2 von Interesse.
 */
/*N*/ IMPL_CONTAINER_LOOP(
/*N*/     GetFilter4EA, const String&, CONDITION )
#undef CONDITION

/*   [Beschreibung]
     Ermitelt einen Filter nach seiner Extension.
     (2Ah = '*')
 */
/*N*/ IMPL_CONTAINER_LOOP(
/*N*/     GetFilter4Extension, const String&,
/*N*/     pFilter->GetWildcard() != String() && pFilter->GetWildcard() != DEFINE_CONST_UNICODE("*.*") && pFilter->GetWildcard() != '*' &&
/*N*/   WildCard( ToUpper_Impl( pFilter->GetWildcard()() ), ';' ) == ToUpper_Impl( aArg ))

//STRIP001 IMPL_CONTAINER_LOOP(
//STRIP001     GetFilter4UIName, const String&,
//STRIP001     pFilter->GetUIName() == aArg )

//----------------------------------------------------------------

/*N*/ const String SfxFilterContainer::GetName() const
/*N*/ {
/*N*/     return pImpl->aName;
/*N*/ }

//----------------------------------------------------------------

//STRIP001 void SfxFilterContainer::DeleteFilter( const SfxFilter* pFilter )
//STRIP001 /*   [Beschreibung]
//STRIP001
//STRIP001   Loescht einen Filter aus seinem Container und den Filter selbst.
//STRIP001  */
//STRIP001 {
//STRIP001     pImpl->aList.Remove( (SfxFilter*)pFilter );
//STRIP001     delete (SfxFilter*)pFilter;
//STRIP001 }

//----------------------------------------------------------------

/*N*/ void SfxFilterContainer::AddFilter( SfxFilter* pFilter, sal_uInt16 nPos )
/*N*/ {
/*   [Beschreibung]

     Fuegt einen Filter in einen Container ein.
 */
/*N*/     if ( !pFilter->GetFilterName().Len() ||
/*N*/        !GetFilter4FilterName( pFilter->GetFilterName() ))
/*N*/       pImpl->aList.Insert( pFilter, nPos );
/*N*/ #if !defined(PRODUCT)
/*N*/   else
/*N*/       delete pFilter;
/*N*/ #endif
/*N*/ }

//----------------------------------------------------------------

/*N*/ void SfxFilterContainer::LoadFilters(
/*N*/     const String& rGroup,  // ConfigGruppe, aus der gelesen werden soll
/*N*/   sal_Bool bInstallIni,      // Falls sal_True aus install.ini lesen,
/*N*/                          // sonst soffice3.ini
/*N*/   SfxFilterFlags nOrFlags,       // Flags zusaetzlich zu denen in der Ini
/*N*/   SfxFilterFlags nNotFlags )     // Flags, die nicht aus der ini genommen werden
/*   [Beschreibung]

     Stoesst das Laden eines FilterContainers an. Das eigentliche
     Laden erfolgt im LateInitHandler bzw. in ForceFilterLoad_Impl,
     falls vor LateInit auf den FilterContainer zugegriffen wird.  */
/*N*/ {
/*N*/ }

//----------------------------------------------------------------

//STRIP001 void SfxFilterContainer::SaveFilters( const String& rGroup, SfxFilterFlags nMask ) const
//STRIP001 /*   [Beschreibung]
//STRIP001
//STRIP001   Speichert die Filter des Containers in der soffice3.ini.
//STRIP001  */
//STRIP001 {
//STRIP001 }

//-------------------------------------------------------------------------

/*?*/ sal_uInt32 SfxFilterContainer::GetFilter4Content(
/*?*/     SfxMedium& rMedium, const SfxFilter** ppFilter,
/*?*/   SfxFilterFlags, SfxFilterFlags ) const
/*?*/ {
/*?*/     return 0;
/*?*/ }

//-------------------------------------------------------------------------
#if 0
/*?*/ sal_uInt32 SfxExecutableFilterContainer::Choose_Impl( SfxMedium& rMedium ) const
/*?*/ {
/*?*/     SfxFilterMatcher& rMatcher = SFX_APP()->GetFilterMatcher();
/*?*/     SfxFilterDialog *pDlg =
/*?*/         new SfxFilterDialog(
/*?*/             0, &rMedium, rMatcher, 0, 0 );
/*?*/     const sal_Bool bOk = RET_OK == pDlg->Execute();
/*?*/     if (bOk)
/*?*/     {
/*?*/         const SfxFilter* pFilter  = rMatcher.GetFilter4UIName(
/*?*/             pDlg->GetSelectEntry() );
/*?*/         delete pDlg;
/*?*/         rMedium.SetFilter( pFilter );
/*?*/         return ERRCODE_NONE;
/*?*/     }
/*?*/     delete pDlg;
/*?*/     return ERRCODE_ABORT;
/*?*/ }
/*?*/
/*?*/ String SfxExecutableFilterContainer::GetBugdocName_Impl(
/*?*/     const String& rName ) const
/*   [Beschreibung]

     Sucht ein Bugdoc in den ueblichen Verzeichnissen
 */
/*?*/ {
/*?*/     static const char* pNames[] =
/*?*/     {
/*?*/         "q:\\sw\\bugdoc",
/*?*/         "q:\\sd\\bugdoc",
/*?*/         "q:\\sc\\bugdoc",
/*?*/         "q:\\sch\\bugdoc",
/*?*/         "q:\\solar\\bugdoc",
/*?*/         "q:\\bugdoc",
/*?*/         0
/*?*/     };
/*?*/     sal_uInt32 nNumber = rName.ToInt32();
/*?*/   String aMatch = rName;
/*?*/   aMatch += '*';
/*?*/     sal_uInt16 n = 1;
/*?*/     const char* pName = pNames[ 0 ];
/*?*/     while( pName )
/*?*/     {
/*?*/         DirEntry aEntry( String::CreateFromAscii(pName) );
/*?*/         for( sal_uInt32 nBase = ( nNumber / 500 + 1 ) * 500;
/*?*/              nBase - nNumber < 5000; nBase+=500 )
/*?*/         {
/*?*/             DirEntry aAkt( aEntry );
/*?*/             String aBis( DEFINE_CONST_UNICODE("bis") );
/*?*/             aBis += String::CreateFromInt32( nBase );
/*?*/             aAkt += DirEntry( aBis );
/*?*/             if( aAkt.Exists() )
/*?*/             {
/*?*/                 aAkt += DirEntry( aMatch );
/*?*/                 Dir aDir( aAkt );
/*?*/                 if( aDir.Count() )
/*?*/                     return aDir[ 0 ].GetFull();
/*?*/             }
/*?*/         }
/*?*/         pName = pNames[ n++ ];
/*?*/     }
/*?*/
/*?*/     return String();
/*?*/ }
/*?*/
/*?*/       case SFX_EXE_FILTER_BUGID:
/*?*/       {
/*?*/             String aPathName = DEFINE_CONST_UNICODE("http://webserver1.stardiv.de/Bugtracker/Source/Body_ReportDetail.asp?ID=");
/*?*/           aPathName += rMedium.GetURLObject().GetURLPath();
/*?*/           rMedium.SetName( aPathName );
/*?*/           rMedium.SetPhysicalName( String() );
/*?*/           rMedium.Init_Impl();
/*?*/           rMedium.SetFilter( 0 );
/*?*/           return ERRCODE_SFX_RESTART;
/*?*/       }
/*?*/
/*?*/       case SFX_EXE_FILTER_BUGDOC:
/*?*/       {
/*?*/           String aPathName = GetBugdocName_Impl(
/*?*/               rMedium.GetURLObject().GetURLPath() );
/*?*/           if( aPathName.Len() )
/*?*/           {
/*?*/               rMedium.SetName( aPathName );
/*?*/               rMedium.SetPhysicalName( String() );
/*?*/               rMedium.Init_Impl();
/*?*/               rMedium.SetFilter( 0 );
/*?*/               return ERRCODE_SFX_RESTART;
/*?*/           }
/*?*/           else return ERRCODE_SFX_INVALIDLINK;
/*?*/       }
/*?*/
#endif

//----------------------------------------------------------------

/*N*/ SfxFactoryFilterContainer::SfxFactoryFilterContainer(
/*N*/     const String& rName, const SfxObjectFactory& rFactP )
/*N*/     : SfxFilterContainer( rName ), rFact( rFactP ), pFunc(0)
/*   [Beschreibung]

     Im SfxFactoryFilterContainer befinden sich die Filter einer
     SfxObjectFactory. Wird kein DetectFilter registriert, so wird
     fuer die DefaultFactory <SfxApplication::DetectFilter> genommen
 */
/*N*/ {
/*N*/     //Defaults in den Container der DefaultFactory laden
/*N*/   SetFlags( GetFlags() | SFX_FILTER_CONTAINER_FACTORY );
/*N*/ }

//----------------------------------------------------------------

/*N*/ sal_uInt32 SfxFactoryFilterContainer::GetFilter4Content(
/*N*/     SfxMedium& rMedium, const SfxFilter** ppFilter, SfxFilterFlags nMust, SfxFilterFlags nDont ) const
/*N*/ {
/*N*/   SFX_ITEMSET_ARG( rMedium.GetItemSet(), pTargetItem, SfxStringItem,
/*N*/                    SID_TARGETNAME, sal_False);
/*N*/
/*N*/     if ( *ppFilter && ( (*ppFilter)->GetFilterFlags() & SFX_FILTER_STARONEFILTER ) )
/*N*/       return 0;
/*N*/
/*N*/     if( pFunc )
/*N*/     {
/*N*/         sal_uInt32 nErr = (*pFunc)(rMedium, ppFilter, nMust, nDont);
/*N*/         DBG_ASSERT( !*ppFilter ||
/*N*/                     (((*ppFilter)->GetFilterFlags() & nMust ) == nMust &&
/*N*/                      ((*ppFilter)->GetFilterFlags() & nDont ) == 0 ),
/*N*/                     "DetectFilter Spec nicht eingehalten" );
/*N*/         return nErr;
/*N*/     }
/*
    else
    {
        DBG_ASSERT( !GetFilterCount(), "No DetectFilter function set!" );
        return 0;
    }
*/
/*N*/     return 0;
/*N*/ }

//----------------------------------------------------------------

DECLARE_LIST( SfxFContainerList_Impl, SfxFilterContainer * )//STRIP008 ;

class SfxFilterMatcher_Impl
{
public:
    sal_uInt16 nAkt;
    SfxFContainerList_Impl aList;
    sal_Bool bDeleteContainers;
};

//----------------------------------------------------------------

/*N*/ SfxFilterMatcher::SfxFilterMatcher( SfxFilterContainer* pCont)
/*N*/ {
/*N*/     pImpl = new SfxFilterMatcher_Impl;
/*N*/   pImpl->bDeleteContainers = sal_False;
/*N*/     AddContainer( pCont );
/*N*/ }

//----------------------------------------------------------------

//STRIP001 SfxFilterMatcher::SfxFilterMatcher()
//STRIP001 {
//STRIP001     pImpl = new SfxFilterMatcher_Impl;
//STRIP001  pImpl->bDeleteContainers = sal_False;
//STRIP001 }

/*N*/ SfxFilterMatcher::SfxFilterMatcher(sal_Bool bDeleteContainers)
/*N*/ {
/*N*/     pImpl = new SfxFilterMatcher_Impl;
/*N*/   pImpl->bDeleteContainers = bDeleteContainers;
/*N*/ }

//----------------------------------------------------------------

/*N*/ SfxFilterMatcher::~SfxFilterMatcher()
/*N*/ {
/*N*/   if ( pImpl->bDeleteContainers )
/*N*/   {
/*N*/       for ( sal_uInt32 n = pImpl->aList.Count(); n--; )
/*N*/       {
/*N*/           SfxFilterContainer *pFCont = pImpl->aList.Remove(n);
/*N*/           delete pFCont;
/*N*/       }
/*N*/   }
/*N*/     delete pImpl;
/*N*/ }

//----------------------------------------------------------------

/*N*/ void SfxFilterMatcher::AddContainer( SfxFilterContainer* pC )
/*N*/ {
/*N*/     pImpl->aList.Insert( pC, pImpl->aList.Count() );
/*N*/ }

//----------------------------------------------------------------

//STRIP001 sal_uInt16 SfxFilterMatcher::GetContainerCount() const
//STRIP001 {
//STRIP001     return (sal_uInt16)pImpl->aList.Count();
//STRIP001 }

//----------------------------------------------------------------

//STRIP001 SfxFilterContainer* SfxFilterMatcher::GetContainer( sal_uInt16 nPos ) const
//STRIP001 {
//STRIP001     return pImpl->aList.GetObject( nPos );
//STRIP001 }

//----------------------------------------------------------------

/*?*/ SfxFilterContainer* SfxFilterMatcher::GetContainer( const String &rName ) const
/*STRIP003*/{ // DBG_BF_ASSERT(0, "STRIP"); return NULL;//STRIP001
/*STRIP003*/     SfxFContainerList_Impl& rList = pImpl->aList;
/*STRIP003*/     sal_uInt16 nCount = (sal_uInt16) rList.Count();
/*STRIP003*/     for( sal_uInt16 n = 0; n < nCount; n++ )
/*STRIP003*/         if( rList.GetObject( n )->GetName() == rName )
/*STRIP003*/             return rList.GetObject( n );
/*STRIP003*/     return 0;
/*?*/ }

//----------------------------------------------------------------

/*N*/ sal_uInt32  SfxFilterMatcher::GuessFilterIgnoringContent(
/*N*/     SfxMedium& rMedium, const SfxFilter**ppFilter,
/*N*/     SfxFilterFlags nMust, SfxFilterFlags nDont ) const
/*N*/ {
/*N*/     String aFileName = rMedium.GetName();
/*N*/     sal_uInt32 nErr = ERRCODE_NONE;
/*N*/   const SfxFilter* pFilter = *ppFilter;
/*N*/   const INetURLObject& rObj = rMedium.GetURLObject();
/*N*/
/*N*/   if( !pFilter )
/*N*/       pFilter = SFX_APP()->GetFilterMatcher().GetFilter4Protocol( rMedium );
/*N*/
/*N*/     sal_Bool bCheckExternBrowser = sal_False;
/*N*/     if( !pFilter )
/*N*/   {
/*N*/       // Falls Medium Remote, Zunaechst ueber Mimetypen pruefen ( nicht bei ExternBrowser, sofern dabei angeladen wird )
/*N*/       if( !pFilter && rMedium.SupportsMIME_Impl() && ( !bCheckExternBrowser || rObj.GetProtocol() != INET_PROT_HTTP && rObj.GetProtocol() != INET_PROT_HTTPS ) )
/*N*/       {
/*N*/           // Mime Typen holen
/*N*/           String aMime;
/*N*/           nErr = rMedium.GetMIMEAndRedirect( aMime );
/*N*/           nErr = ERRCODE_TOERROR( nErr );
/*N*/           if ( nErr == ERRCODE_IO_PENDING )
/*N*/               return nErr;
/*N*/           else if( !nErr && aMime.Len() )
/*N*/           {
/*?*/               if ( aMime.EqualsAscii(CONTENT_TYPE_STR_X_CNT_HTTPFILE) )
/*?*/                   // FilterDetection nur "uber den Content
/*?*/                   return ERRCODE_NONE;
/*?*/               else
/*?*/                   {DBG_BF_ASSERT(0, "STRIP");} //STRIP001 pFilter = GetFilter4Mime( aMime, nMust, nDont );
/*?*/
/*?*/               if ( pFilter && aMime.EqualsAscii(CONTENT_TYPE_STR_APP_OCTSTREAM) )
/*?*/               {
/*?*/                   // Damit eigene Formate wie sdw auch bei falsch konfiguriertem Server erkannt werden, bevor
/*?*/                   // wir GetInStream rufen
/*?*/                   const SfxFilter* pMimeFilter = pFilter;
/*?*/                   pFilter = GetFilter4Extension( rMedium.GetURLObject().GetName(), nMust, nDont );
/*?*/                   if( pFilter )
/*?*/                       nErr = ERRCODE_NONE;
/*?*/                     else
/*?*/                       pFilter = pMimeFilter;
/*?*/               }
/*?*/
/*?*/               // Bei MIME Typen keinen Storage anfordern
/*?*/                 if( !nErr && rMedium.SupportsMIME_Impl() && pFilter && !pFilter->UsesStorage() )
/*?*/               {
/*?*/                   rMedium.GetInStream();
/*?*/                   nErr = rMedium.GetError();
/*?*/               }
/*N*/           }
/*N*/
/*N*/           if( nErr )
/*N*/           {
/*?*/               if ( nErr == ERRCODE_SFX_CONSULTUSER )
/*?*/                   *ppFilter = pFilter;
/*?*/               return nErr;
/*N*/           }
/*N*/           else if ( pFilter && aMime.EqualsAscii(CONTENT_TYPE_STR_TEXT_HTML) )
/*N*/           {
/*N*/               // MIME ist vertrauenswuerdig ( !? )
/*N*/               nErr = ERRCODE_SFX_NEVERCHECKCONTENT;
/*N*/           }
/*N*/       }
/*N*/
/*N*/         if( !pFilter && rMedium.IsDownloadDone_Impl() )
/*N*/       {
/*N*/           // dann ueber Storage CLSID
/*N*/           // Remote macht das keinen Sinn, wenn der Download noch la"uft
/*N*/             SvStorageRef aStor = rMedium.GetStorage();
/*N*/             if ( aStor.Is() )
/*N*/                 pFilter = GetFilter4ClipBoardId( aStor->GetFormat(), nMust, nDont );
/*N*/
// STRIP001 /*N*/           // Als naechstes ueber Extended Attributes pruefen
// STRIP001 /*N*/           String aNewFileName;
// STRIP001 /*N*/           if( !pFilter )
// STRIP001 /*N*/           {
// STRIP001 /*N*/               aNewFileName = rMedium.GetPhysicalName();
// STRIP001 /*N*/               SvEaMgr aMgr( aNewFileName );
// STRIP001 /*N*/               String aType;
// STRIP001 /*N*/               if( aMgr.GetFileType( aType ))
// STRIP001 /*N*/               {
// STRIP001 /*N*/                   // Plain text verwerfen wir, damit unter OS/2
// STRIP001 /*N*/                   // html Dateien mit attribut Text als html geladen werden
// STRIP001 /*?*/                   if( aType.CompareIgnoreCaseToAscii( "Plain Text" ) != COMPARE_EQUAL )
// STRIP001 /*?*/                       pFilter = GetFilter4EA( aType, nMust, nDont );
// STRIP001 /*N*/               }
// STRIP001 /*N*/           }
/*N*/       }
/*N*/
/*N*/       // Zu allerletzt ueber Extension mappen
/*N*/       if( !pFilter )
/*N*/       {
/*N*/           pFilter = GetFilter4Extension( rMedium.GetURLObject().GetName(), nMust, nDont );
/*N*/           if( !pFilter || pFilter->GetWildcard()==DEFINE_CONST_UNICODE("*.*") || pFilter->GetWildcard() == '*' )
/*N*/               pFilter = 0;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   *ppFilter = pFilter;
/*N*/   return nErr;
/*N*/ }

//----------------------------------------------------------------

#define CHECKERROR()                                            \
if( nErr == 1 || nErr == USHRT_MAX || nErr == ULONG_MAX )       \
{                                                               \
    ByteString aText = "Fehler in FilterDetection: Returnwert ";\
    aText += ByteString::CreateFromInt32(nErr);                 \
    if( pFilter )                                               \
    {                                                           \
        aText += ' ';                                           \
        aText += ByteString(U2S(pFilter->GetFilterName()));     \
    }                                                           \
    DBG_ERROR( aText.GetBuffer() );                             \
    nErr = ERRCODE_ABORT;                                       \
}

//----------------------------------------------------------------

/*N*/ sal_uInt32  SfxFilterMatcher::GuessFilter(
/*N*/     SfxMedium& rMedium, const SfxFilter**ppFilter,
/*N*/     SfxFilterFlags nMust, SfxFilterFlags nDont ) const
/*N*/ {
/*N*/     const SfxFilter* pOldFilter = *ppFilter;
/*N*/     const SfxFilter* pFilter = pOldFilter;
/*N*/
/*N*/   sal_Bool bConsultUser = sal_False;
/*N*/   sal_Bool bSupportsMime = rMedium.SupportsMIME_Impl();
/*N*/
/*N*/   // Zunaechst, falls Filter mitkommt einmal testen, ob dieser in Ordnung ist.
/*N*/   ErrCode nErr = ERRCODE_NONE;
/*N*/     if( pFilter && ( pFilter->GetFilterContainer()->GetFlags() & SFX_FILTER_CONTAINER_FACTORY ) )
/*N*/   {
/*?*/         rMedium.StartDownload();
/*?*/       if ( !rMedium.IsDownloadDone_Impl() )
/*?*/       {
/*?*/           if ( pFilter->GetFilterFlags() & SFX_FILTER_ASYNC )
/*?*/           {
/*?*/               // kurzzeitig auf synchron schalten solange die Apps sich weigern asynchron
/*?*/               // zu detecten
/*?*/               rMedium.ForceSynchronStream_Impl( sal_True );
/*?*/               if ( !rMedium.GetInStream() )
/*?*/               {
/*?*/                   ErrCode e = rMedium.GetErrorCode();
/*?*/                   if ( e == ERRCODE_NONE )
/*?*/                   {
/*?*/                       *ppFilter = pFilter;
/*?*/                       return ERRCODE_IO_PENDING;
/*?*/                   }
/*?*/                   else
/*?*/                       return e;
/*?*/               }
/*?*/           }
/*?*/           else
/*?*/           {
/*?*/               *ppFilter = pFilter;
/*?*/               return ERRCODE_IO_PENDING;
/*?*/           }
/*?*/       }
/*?*/
/*?*/       if( bSupportsMime && !pFilter->UsesStorage() )
/*?*/           rMedium.GetInStream();
/*?*/
/*?*/       nErr = pFilter->GetFilterContainer()->GetFilter4Content( rMedium, &pFilter, nMust, nDont );
/*?*/       CHECKERROR();
/*?*/
/*?*/       rMedium.ForceSynchronStream_Impl( sal_False );
/*?*/
/*?*/       // ABORT bedeutet Filter ungueltig
/*?*/       if( nErr && (nErr != ERRCODE_ABORT && nErr != ERRCODE_SFX_FORCEQUIET ) )
/*?*/           return nErr;
/*?*/
/*?*/       // War der Filter ungueltig oder wurde ein anderer zurueckgegeben,
/*?*/       // so detecten wir selbst (wg. redirection)
/*?*/       if( nErr == ERRCODE_ABORT && pFilter )
/*?*/           bConsultUser = sal_True;
/*?*/
/*?*/       if( nErr != ERRCODE_SFX_FORCEQUIET && pOldFilter && pFilter != pOldFilter )
/*N*/           pFilter = 0;
/*N*/   }
/*N*/
/*N*/   if( !pFilter )
/*N*/   {
/*N*/       bConsultUser = sal_False;
/*N*/ //DV !!!! don't close InStream when using the new medium
/*N*/ //        rMedium.CloseInStream();
/*N*/
/*N*/       // Als erstes Protocol, MIME-Type, Extension etc. probieren
/*N*/       nErr = GuessFilterIgnoringContent( rMedium, &pFilter, nMust, nDont );
/*N*/       if ( nErr == ERRCODE_IO_PENDING )
/*N*/       {
/*?*/           *ppFilter = pFilter;
/*?*/           return nErr;
/*N*/       }
/*N*/
/*N*/       if ( pFilter && nErr == ERRCODE_SFX_CONSULTUSER )
/*?*/           *ppFilter = pFilter;
/*N*/
/*N*/       if( nErr && nErr != ERRCODE_ABORT && nErr != ERRCODE_SFX_FORCEQUIET && nErr != ERRCODE_SFX_NEVERCHECKCONTENT )
/*N*/           return nErr;
/*N*/
/*N*/       if( nErr == ERRCODE_ABORT )
/*N*/           pFilter = 0;
/*N*/
/*N*/       // Jetzt wird geprueft, ob das Modul auch einverstanden ist; ist das nicht der Fall, wird auf
/*N*/       // jeden Fall auf ConsultUser umgeschaltet
/*N*/         if( pFilter )
/*N*/       {
/*N*/           if( nErr == ERRCODE_SFX_NEVERCHECKCONTENT )
/*N*/               nErr = ERRCODE_NONE;
/*N*/           else if( pFilter->GetFilterContainer()->GetFlags() & SFX_FILTER_CONTAINER_FACTORY )
/*N*/           {
/*N*/               rMedium.StartDownload();
/*N*/               if ( !rMedium.IsDownloadDone_Impl() )
/*N*/               {
/*?*/                   if ( !pFilter->UsesStorage() && rMedium.GetInStream() && ( pFilter->GetFilterFlags() & SFX_FILTER_ASYNC ) )
/*?*/                       // kurzzeitig auf synchron schalten solange die Apps sich weigern asynchron
/*?*/                       // zu detecten
/*?*/                       rMedium.ForceSynchronStream_Impl( sal_True );
/*?*/                   else
/*?*/                   {
/*?*/                       *ppFilter = pFilter;
/*?*/                       return ERRCODE_IO_PENDING;
/*?*/                   }
/*N*/               }
/*N*/
/*N*/               const SfxFilter* pTmpFilter = pFilter;
/*N*/               nErr = pFilter->GetFilterContainer()->GetFilter4Content( rMedium, &pFilter, nMust, nDont );
/*N*/               CHECKERROR();
/*N*/
/*N*/               rMedium.ForceSynchronStream_Impl( sal_False );
/*N*/
/*N*/               // ABORT bedeutet Filter ungueltig
/*N*/               if( nErr && (nErr != ERRCODE_ABORT && nErr != ERRCODE_SFX_FORCEQUIET ) )
/*N*/                   return nErr;
/*N*/
/*N*/               if( nErr == ERRCODE_ABORT && pFilter )
/*N*/                   pFilter = 0;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   // Jetzt einmal drueberiterieren und nur die perfekten Filter nehmen
/*N*/   if( !pFilter )
/*N*/   {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/        // Achtung: hier k"onnte auch asynchron detected werden!
//STRIP001 /*?*/         rMedium.StartDownload();
//STRIP001 /*?*/        if ( !rMedium.IsDownloadDone_Impl() )
//STRIP001 /*?*/            return ERRCODE_IO_PENDING;
//STRIP001 /*?*/
//STRIP001 /*?*/         rMedium.GetStorage();
//STRIP001 /*?*/        nErr = rMedium.GetErrorCode();
//STRIP001 /*?*/        if( nErr )
//STRIP001 /*?*/            return nErr;
//STRIP001 /*?*/        nErr = GetFilter4Content( rMedium, &pFilter, nMust, nDont, sal_True );
//STRIP001 /*?*/        CHECKERROR();
//STRIP001 /*?*/        if( nErr && (nErr != ERRCODE_ABORT && nErr != ERRCODE_SFX_FORCEQUIET ) )
//STRIP001 /*?*/            return nErr;
//STRIP001 /*?*/
//STRIP001 /*?*/        if( nErr == ERRCODE_ABORT && pFilter )
//STRIP001 /*?*/            pFilter = 0;
/*N*/   }
/*N*/
/*N*/   // Letzte Moeglichkeit ist die Befragung aller ObjectFactories.
/*N*/   if( !pFilter )
/*N*/   {
/*N*/       // Achtung: hier k"onnte auch asynchron detected werden!
/*?*/       if ( !rMedium.IsDownloadDone_Impl() )
/*?*/           return ERRCODE_IO_PENDING;
/*?*/
/*?*/ //DV !!!! don't close InStream when using the new Medium
/*?*/ //rMedium.CloseInStream();
/*?*/ DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/         rMedium.GetStorage();
//STRIP001 /*?*/        nErr = GetFilter4Content( rMedium, &pFilter, nMust, nDont );
//STRIP001 /*?*/        CHECKERROR();
//STRIP001 /*?*/        if( nErr && (nErr != ERRCODE_ABORT && nErr != ERRCODE_SFX_FORCEQUIET ) )
//STRIP001 /*?*/            return nErr;
//STRIP001 /*?*/
//STRIP001 /*?*/        if( nErr == ERRCODE_ABORT && pFilter )
//STRIP001 /*?*/            bConsultUser = sal_True;
/*N*/   }
/*N*/
/*N*/   *ppFilter = pFilter;
/*N*/
/*N*/   if ( ( ( pOldFilter && pOldFilter!=pFilter &&
/*N*/           ( !pOldFilter->IsOwnTemplateFormat() || !pFilter->IsOwnFormat() ) ) ) &&
/*N*/           nErr != ERRCODE_SFX_FORCEQUIET || bConsultUser )
/*N*/         return ERRCODE_SFX_CONSULTUSER;
/*N*/
/*N*/     if( !pOldFilter )
/*N*/       pOldFilter = pFilter;
/*N*/
/*N*/   // Checken, ob Daten vorliegen. Dies verhindert Fehler, die in
/*N*/   // GetFilter4Content auftreten und die Auswahlbox hochbringen.
/*N*/   ErrCode nMediumError = rMedium.GetErrorCode();
/*N*/   if( nMediumError )
/*N*/       return nMediumError;
/*N*/
/*N*/   *ppFilter = pFilter;
/*N*/     if ( ( nErr ||
/*N*/           ( pOldFilter && pOldFilter!=pFilter
/*N*/           && ( !pOldFilter->IsOwnTemplateFormat() ||
/*N*/                !pFilter->IsOwnFormat() ) ))
/*N*/           && nErr != ERRCODE_SFX_FORCEQUIET )
/*N*/         nErr = ERRCODE_SFX_CONSULTUSER;
/*N*/
/*N*/     if( nErr == ERRCODE_SFX_FORCEQUIET )
/*N*/         nErr = 0;
/*N*/     return nErr;
/*N*/ };

//----------------------------------------------------------------
//STRIP001 sal_Bool SfxFilterMatcher::IsFilterInstalled( const SfxFilter* pFilter )
//STRIP001 {
//STRIP001  Window *pWindow = SFX_APP()->GetTopWindow();
//STRIP001  if ( pFilter->GetFilterFlags() & SFX_FILTER_MUSTINSTALL )
//STRIP001  {
//STRIP001      // Hier k"onnte noch eine Nachinstallation angeboten werden
//STRIP001      String aText( SfxResId( STR_FILTER_NOT_INSTALLED ) );
//STRIP001      aText.SearchAndReplaceAscii( "$(FILTER)", pFilter->GetUIName() );
//STRIP001      QueryBox aQuery( pWindow, WB_YES_NO | WB_DEF_YES, aText );
//STRIP001      short nRet = aQuery.Execute();
//STRIP001      if ( nRet == RET_YES )
//STRIP001      {
//STRIP001 #ifdef DBG_UTIL
//STRIP001          // Setup starten
//STRIP001          InfoBox( pWindow, DEFINE_CONST_UNICODE("Hier soll jetzt das Setup starten!") ).Execute();
//STRIP001 #endif
//STRIP001          // Installation mu\s hier noch mitteilen, ob es geklappt hat, dann kann das
//STRIP001          // Filterflag gel"oscht werden
//STRIP001      }
//STRIP001
//STRIP001      return ( !(pFilter->GetFilterFlags() & SFX_FILTER_MUSTINSTALL) );
//STRIP001  }
//STRIP001  else if ( pFilter->GetFilterFlags() & SFX_FILTER_CONSULTSERVICE )
//STRIP001  {
//STRIP001      String aText( SfxResId( STR_FILTER_CONSULT_SERVICE ) );
//STRIP001      aText.SearchAndReplaceAscii( "$(FILTER)", pFilter->GetUIName() );
//STRIP001      InfoBox ( pWindow, aText ).Execute();
//STRIP001      return sal_False;
//STRIP001  }
//STRIP001  else
//STRIP001      return sal_True;
//STRIP001 }


//STRIP001 sal_uInt32 SfxFilterMatcher::DetectFilter( SfxMedium& rMedium, const SfxFilter**ppFilter, sal_Bool bPlugIn, sal_Bool bAPI ) const
//STRIP001 /*  [Beschreibung]
//STRIP001
//STRIP001     Hier wird noch die Filterauswahlbox hochgezogen. Sonst GuessFilter
//STRIP001  */
//STRIP001
//STRIP001 {
//STRIP001     const SfxFilter* pOldFilter = rMedium.GetFilter();
//STRIP001     if ( pOldFilter )
//STRIP001     {
//STRIP001         if( !IsFilterInstalled( pOldFilter ) )
//STRIP001             pOldFilter = 0;
//STRIP001         else
//STRIP001         {
//STRIP001             SFX_ITEMSET_ARG( rMedium.GetItemSet(), pSalvageItem, SfxStringItem, SID_DOC_SALVAGE, sal_False);
//STRIP001             if ( ( pOldFilter->GetFilterFlags() & SFX_FILTER_PACKED ) && pSalvageItem )
//STRIP001                 // Salvage is always done without packing
//STRIP001                 pOldFilter = 0;
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001     const SfxFilter* pFilter = pOldFilter;
//STRIP001
//STRIP001     sal_Bool bPreview = rMedium.IsPreview_Impl(), bInsert = sal_False;
//STRIP001  SFX_ITEMSET_ARG(rMedium.GetItemSet(), pReferer, SfxStringItem, SID_REFERER, FALSE);
//STRIP001     if ( bPreview && rMedium.IsRemote() && ( !pReferer || pReferer->GetValue().CompareToAscii("private:searchfolder:",21 ) != COMPARE_EQUAL ) )
//STRIP001         return ERRCODE_ABORT;
//STRIP001
//STRIP001  ErrCode nErr = GuessFilter( rMedium, &pFilter );
//STRIP001  if ( nErr == ERRCODE_ABORT )
//STRIP001      return nErr;
//STRIP001
//STRIP001  if ( nErr == ERRCODE_IO_PENDING )
//STRIP001  {
//STRIP001      *ppFilter = pFilter;
//STRIP001      return nErr;
//STRIP001  }
//STRIP001
//STRIP001  if ( !pFilter )
//STRIP001  {
//STRIP001      const SfxFilter* pInstallFilter = NULL;
//STRIP001
//STRIP001      // Jetzt auch Filter testen, die nicht installiert sind ( ErrCode ist irrelevant )
//STRIP001      GuessFilter( rMedium, &pInstallFilter, SFX_FILTER_IMPORT, SFX_FILTER_CONSULTSERVICE );
//STRIP001      if ( pInstallFilter )
//STRIP001      {
//STRIP001          if ( IsFilterInstalled( pInstallFilter ) )
//STRIP001              // Eventuell wurde der Filter nachinstalliert
//STRIP001              pFilter = pInstallFilter;
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          // Jetzt auch Filter testen, die erst von Star bezogen werden m"ussen ( ErrCode ist irrelevant )
//STRIP001          GuessFilter( rMedium, &pInstallFilter, SFX_FILTER_IMPORT, 0 );
//STRIP001          if ( pInstallFilter )
//STRIP001              IsFilterInstalled( pInstallFilter );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001     sal_Bool bHidden = bPreview;
//STRIP001  SFX_ITEMSET_ARG( rMedium.GetItemSet(), pFlags, SfxStringItem, SID_OPTIONS, sal_False);
//STRIP001     if ( !bHidden && pFlags )
//STRIP001     {
//STRIP001         String aFlags( pFlags->GetValue() );
//STRIP001         aFlags.ToUpperAscii();
//STRIP001         if( STRING_NOTFOUND != aFlags.Search( 'H' ) )
//STRIP001             bHidden = sal_True;
//STRIP001     }
//STRIP001
//STRIP001     if ( ( !pFilter || nErr == ERRCODE_SFX_CONSULTUSER ) && !bAPI && !bHidden )
//STRIP001     {
//STRIP001         if ( !pFilter )
//STRIP001          pFilter = pOldFilter;
//STRIP001
//STRIP001         String aTmpName;
//STRIP001      if ( pFilter )
//STRIP001          aTmpName = pFilter->GetUIName();
//STRIP001
//STRIP001         SfxFilterMatcher *pMatcher;
//STRIP001         if( bPlugIn && pFilter )
//STRIP001             pMatcher = new SfxFilterMatcher( (SfxFilterContainer *) pFilter->GetFilterContainer() );
//STRIP001         else
//STRIP001             pMatcher = (SfxFilterMatcher*) this;
//STRIP001
//STRIP001         SfxFilterDialog *pDlg = new SfxFilterDialog( 0, &rMedium, *pMatcher, pFilter ? &aTmpName: 0, 0 );
//STRIP001         const sal_Bool bOk = RET_OK == pDlg->Execute();
//STRIP001         if (bOk)
//STRIP001             pFilter  = pMatcher->GetFilter4UIName( pDlg->GetSelectEntry());
//STRIP001
//STRIP001         if( bPlugIn && pFilter )
//STRIP001          delete pMatcher;
//STRIP001         delete pDlg;
//STRIP001
//STRIP001         if ( !bOk)
//STRIP001          nErr = ERRCODE_ABORT;
//STRIP001         else
//STRIP001          nErr = ERRCODE_NONE;
//STRIP001     }
//STRIP001
//STRIP001     *ppFilter = pFilter;
//STRIP001
//STRIP001     if ( bHidden || bAPI && nErr == ERRCODE_SFX_CONSULTUSER )
//STRIP001      nErr = pFilter ? ERRCODE_NONE : ERRCODE_ABORT;
//STRIP001     return nErr;
//STRIP001 }

//----------------------------------------------------------------

//STRIP001 const SfxFilter* SfxFilterMatcher::GetDefaultFilter() const
//STRIP001 /*  [Beschreibung]
//STRIP001
//STRIP001  Returned den ersten Filter, der nicht internal ist und im Filedialog
//STRIP001  auftaucht
//STRIP001  */
//STRIP001 {
//STRIP001     SfxFilterMatcherIter aIter(
//STRIP001         this, 0, SFX_FILTER_INTERNAL | SFX_FILTER_NOTINFILEDLG );
//STRIP001  return aIter.First();
//STRIP001 }

//----------------------------------------------------------------

/*STRIP003*/ sal_uInt32 SfxFilterMatcher::GetFilter4Content(
/*STRIP003*/     SfxMedium& rMedium, const SfxFilter** ppFilter,  SfxFilterFlags nMust, SfxFilterFlags nDont, sal_Bool bOnlyGoodOnes ) const
/*STRIP003*/ {
/*STRIP003*/     sal_uInt32 nErr = ERRCODE_NONE;
/*STRIP003*/     SfxFContainerList_Impl& rList = pImpl->aList;
/*STRIP003*/     sal_uInt16 nCount = (sal_uInt16)rList.Count();
/*STRIP003*/     for( sal_uInt16 n = 0; n<nCount; n++ )
/*STRIP003*/     {
/*STRIP003*/         const SfxFilter* pFilter = 0;
/*STRIP003*/         nErr = rList.GetObject( n )->GetFilter4Content(
/*STRIP003*/             rMedium, &pFilter, nMust, nDont );
/*STRIP003*/        CHECKERROR();
/*STRIP003*/         if( rMedium.GetError() != ERRCODE_NONE )
/*STRIP003*/         {
/*STRIP003*/             pFilter = 0;
/*STRIP003*/             return rMedium.GetError();
/*STRIP003*/         }
/*STRIP003*/        if( nErr == ERRCODE_ABORT && bOnlyGoodOnes ) pFilter = 0;
/*STRIP003*/         if( pFilter )
/*STRIP003*/         {
/*STRIP003*/             *ppFilter = pFilter;
/*STRIP003*/             return nErr;
/*STRIP003*/         }
/*STRIP003*/     }
/*STRIP003*/     return 0;
/*STRIP003*/ }

#define IMPL_LOOP( Type, ArgType )                              \
const SfxFilter* SfxFilterMatcher::Type(                        \
    ArgType rStr, SfxFilterFlags nMust, SfxFilterFlags nDont ) const \
{                                                               \
    const SfxFilter* pFirstFilter = 0;                          \
    SfxApplication* pApp = SFX_APP();                           \
    if( this == &pApp->GetFilterMatcher() )                     \
        pApp->ForcePendingInitFactories();                      \
    SfxFContainerList_Impl& rList = pImpl->aList;               \
    sal_uInt16 nCount = (sal_uInt16)rList.Count();              \
    for( sal_uInt16 n = 0; n<nCount; n++ )                      \
    {                                                           \
        const SfxFilter* pFilter =                              \
            rList.GetObject( n )->Type(rStr, nMust, nDont );    \
        if( pFilter && ( pFilter->GetFilterFlags() & SFX_FILTER_PREFERED ) ) \
            return pFilter;                                     \
        else if ( !pFirstFilter )                               \
            pFirstFilter = pFilter;                             \
    }                                                           \
    return pFirstFilter;                                        \
}

//STRIP001 IMPL_LOOP( GetFilter4Mime, const String& )
/*N*/ IMPL_LOOP( GetFilter4EA, const String& )
/*N*/ IMPL_LOOP( GetFilter4Extension, const String& )
/*N*/ IMPL_LOOP( GetFilter4Protocol, SfxMedium& )
/*N*/ IMPL_LOOP( GetFilter4ClipBoardId, sal_uInt32 )
/*N*/ IMPL_LOOP( GetFilter, const String& )
/*N*/ IMPL_LOOP( GetFilter4FilterName, const String& )
//STRIP001 IMPL_LOOP( GetFilter4UIName, const String& )

//----------------------------------------------------------------

//STRIP001 sal_uInt32 SfxFilterMatcher::AppDetectFilter(
//STRIP001     SfxMedium& rMedium, const SfxFilter** ppFilter,  SfxFilterFlags nMust, SfxFilterFlags nDont )
//STRIP001 {
//STRIP001     SfxFilterFlags nClass = nMust & SFX_FILTER_TEMPLATE ?
//STRIP001         SFX_FILTER_TEMPLATE : USHRT_MAX;
//STRIP001     return SFX_APP()->DetectFilter( rMedium, ppFilter, (sal_uInt16)nMust );
//STRIP001 }

//----------------------------------------------------------------

/*?*/ IMPL_STATIC_LINK( SfxFilterMatcher, MaybeFileHdl_Impl, String*, pString )
/*?*/ {
/*N*/   const SfxFilter* pFilter =
/*N*/       pThis->GetFilter4Extension( *pString, SFX_FILTER_IMPORT );
/*N*/   if( pFilter && !pFilter->GetWildcard().Matches( String() ) &&
/*N*/       pFilter->GetWildcard() != DEFINE_CONST_UNICODE("*.*") && pFilter->GetWildcard() != '*' )
/*N*/       return sal_True;
/*N*/   return sal_False;
/*?*/ }

//----------------------------------------------------------------

/*N*/ SfxFilterMatcherIter::SfxFilterMatcherIter(
/*N*/     const SfxFilterMatcher* pMatchP,
/*N*/   SfxFilterFlags nOrMaskP, SfxFilterFlags nAndMaskP )
/*N*/     : pMatch( pMatchP->pImpl),
/*N*/       nOrMask( nOrMaskP ), nAndMask( nAndMaskP )
/*N*/ {
/*N*/     // Iterator auf AppFilterMatcher -> DoInitFactory
/*N*/     SfxApplication* pApp = SFX_APP();
/*N*/     if( pMatchP == &pApp->GetFilterMatcher() )
/*N*/         pApp->ForcePendingInitFactories();
/*N*/     if( nOrMask == 0xffff ) //Wg. Fehlbuild auf s
/*N*/         nOrMask = 0;
/*N*/ }

//----------------------------------------------------------------

/*N*/ const SfxFilter *SfxFilterMatcherIter::Forward_Impl()
/*N*/ {
/*N*/     sal_uInt16 nCount = (sal_uInt16 )pMatch->aList.Count();
/*N*/     for( ++nAktContainer; nAktContainer < nCount ; nAktContainer++ )
/*N*/     {
/*N*/         pCont = pMatch->aList.GetObject( nAktContainer );
/*N*/         sal_uInt16 nCnt = pCont->GetFilterCount();
/*N*/         if( nCnt )
/*N*/         {
/*N*/             nBorder=nCnt;
/*N*/             nAktFilter = 0;
/*N*/             return pCont->GetFilter( 0 );
/*N*/         }
/*N*/     }
/*N*/     return 0;
/*N*/ }

//----------------------------------------------------------------

/*N*/ const SfxFilter* SfxFilterMatcherIter::First_Impl()
/*N*/ {
/*N*/     nAktFilter = -1;
/*N*/     nAktContainer = -1;
/*N*/     nBorder = 0;
/*N*/
/*N*/     return Forward_Impl();
/*N*/ }

//----------------------------------------------------------------

/*N*/ const SfxFilter* SfxFilterMatcherIter::Next_Impl()
/*N*/ {
/*N*/     if( ++nAktFilter < nBorder )
/*N*/         return pCont->GetFilter( nAktFilter );
/*N*/     return Forward_Impl();
/*N*/ }

//----------------------------------------------------------------

/*N*/ const SfxFilter* SfxFilterMatcherIter::First()
/*N*/ {
/*N*/     const SfxFilter* pFilter;
/*N*/     for( pFilter = First_Impl(); pFilter; pFilter = Next_Impl())
/*N*/     {
/*N*/         SfxFilterFlags nFlags = pFilter->GetFilterFlags();
/*N*/         if( ((nFlags & nOrMask) == nOrMask ) && !(nFlags & nAndMask ) )
/*N*/             break;
/*N*/     }
/*N*/     return pFilter;
/*N*/ }

//----------------------------------------------------------------

/*N*/ const SfxFilter* SfxFilterMatcherIter::Next()
/*N*/ {
/*N*/     const SfxFilter* pFilter;
/*N*/     for( pFilter = Next_Impl(); pFilter; pFilter = Next_Impl())
/*N*/     {
/*N*/         SfxFilterFlags nFlags = pFilter->GetFilterFlags();
/*N*/         if( ((nFlags & nOrMask) == nOrMask ) && !(nFlags & nAndMask ) )
/*N*/             break;
/*N*/     }
/*N*/     return pFilter;
/*N*/ }

//STRIP001 sal_Bool SfxFilterContainer::IsUsableForRedirects() const
//STRIP001 {
//STRIP001     return FALSE;
//STRIP001 }

//STRIP001 const SfxFilter* SfxExecutableFilterContainer::GetDownloadFilter()
//STRIP001 {
//STRIP001     return NULL;
//STRIP001 }

//STRIP001 const SfxFilter* SfxExecutableFilterContainer::GetChooserFilter()
//STRIP001 {
//STRIP001     return NULL;
//STRIP001 }

/*---------------------------------------------------------------
    helper to build own formated string from given stringlist by
    using given seperator
  ---------------------------------------------------------------*/
/*N*/ ::rtl::OUString implc_convertStringlistToString( const ::com::sun::star::uno::Sequence< ::rtl::OUString >& lList     ,
/*N*/                                                  const sal_Unicode&                                        cSeperator,
/*N*/                                                  const ::rtl::OUString&                                    sPrefix   )
/*N*/ {
/*N*/     ::rtl::OUStringBuffer   sString ( 1000 )           ;
/*N*/     sal_Int32               nCount  = lList.getLength();
/*N*/     sal_Int32               nItem   = 0                ;
/*N*/     for( nItem=0; nItem<nCount; ++nItem )
/*N*/     {
/*N*/         if( sPrefix.getLength() > 0 )
/*N*/         {
/*N*/             sString.append( sPrefix );
/*N*/         }
/*N*/         sString.append( lList[nItem] );
/*N*/         if( nItem+1<nCount )
/*N*/         {
/*N*/             sString.append( cSeperator );
/*N*/         }
/*N*/     }
/*N*/     return sString.makeStringAndClear();
/*N*/ }

// com.sun.star.sheet.SpreadsheetDocument
#define NNUMFILTERNAMESFORSPREADSHEETDOCUMENT (7)
static const sal_Char* sFilterNamesForSpreadsheetDocument[NNUMFILTERNAMESFORSPREADSHEETDOCUMENT] =
{
    "StarCalc 1.0",
    "StarCalc 3.0",
    "StarCalc 3.0 Vorlage/Template",
    "StarCalc 4.0",
    "StarCalc 4.0 Vorlage/Template",
    "StarCalc 5.0",
    "StarCalc 5.0 Vorlage/Template"
};

// com.sun.star.chart.ChartDocument
#define SFILTERNAMESFORCHARTDOCUMENT (3)
static const sal_Char* sFilterNamesForChartDocument[SFILTERNAMESFORCHARTDOCUMENT] =
{
    "StarChart 3.0",
    "StarChart 4.0",
    "StarChart 5.0"
};

// com.sun.star.drawing.DrawingDocument
#define SFILTERNAMESFORDRAWINGDOCUMENT (4)
static const sal_Char* sFilterNamesForDrawingDocument[SFILTERNAMESFORDRAWINGDOCUMENT] =
{
    "StarDraw 3.0",
    "StarDraw 3.0 Vorlage",
    "StarDraw 5.0",
    "StarDraw 5.0 Vorlage"
};

// com.sun.star.presentation.PresentationDocument
#define SFILTERNAMESFORPRESENTATIONDOCUMENT (9)
static const sal_Char* sFilterNamesForPresentationDocument[SFILTERNAMESFORPRESENTATIONDOCUMENT] =
{
    "StarDraw 3.0 (StarImpress)",
    "StarDraw 3.0 Vorlage (StarImpress)",
    "StarDraw 5.0 (StarImpress)",
    "StarDraw 5.0 Vorlage (StarImpress)",
    "StarImpress 4.0",
    "StarImpress 4.0 Vorlage",
    "StarImpress 5.0",
    "StarImpress 5.0 (packed)",
    "StarImpress 5.0 Vorlage"
};

// com.sun.star.formula.FormulaProperties
#define SFILTERNAMESFORFORMULAPROPERTIES (4)
static const sal_Char* sFilterNamesForFormulaProperties[SFILTERNAMESFORFORMULAPROPERTIES] =
{
    "StarMath 2.0",
    "StarMath 3.0",
    "StarMath 4.0",
    "StarMath 5.0"
};

// com.sun.star.text.GlobalDocument
#define SFILTERNAMESFORGLOBALDOCUMENT (5)
static const sal_Char* sFilterNamesForGlobalDocument[SFILTERNAMESFORGLOBALDOCUMENT] =
{
    "StarWriter 3.0 (StarWriter/GlobalDocument)",
    "StarWriter 4.0 (StarWriter/GlobalDocument)",
    "StarWriter 4.0/GlobalDocument",
    "StarWriter 5.0 (StarWriter/GlobalDocument)",
    "StarWriter 5.0/GlobalDocument"
};

// com.sun.star.text.TextDocument
#define SFILTERNAMESFORTEXTDOCUMENT (6)
static const sal_Char* sFilterNamesForTextDocument[SFILTERNAMESFORTEXTDOCUMENT] =
{
    "StarWriter 3.0",
    "StarWriter 3.0 Vorlage/Template",
    "StarWriter 4.0",
    "StarWriter 4.0 Vorlage/Template",
    "StarWriter 5.0",
    "StarWriter 5.0 Vorlage/Template"
};

/*N*/ void SfxFilterContainer::ReadExternalFilters( const String& rDocServiceName )
/*N*/ {
/*N*/     RTL_LOGFILE_CONTEXT( aMeasure, "sfx2 (as96863) ::SfxFilterContainer::ReadExternalFilters" );
/*N*/
/*N*/     try
/*N*/     {
/*N*/         // get the FilterFactory service to access the registered filters ... and types!
/*N*/         ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory > xServiceManager  =::legacy_binfilters::getLegacyProcessServiceFactory();//STRIP002 ::comphelper::getProcessServiceFactory();
/*N*/         ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameAccess >     xFilterCFG                                                ;
/*N*/         ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameAccess >     xTypeCFG                                                  ;
/*N*/         if( xServiceManager.is() == sal_True )
/*N*/         {
/*N*/             xFilterCFG = ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameAccess >( xServiceManager->createInstance( DEFINE_CONST_UNICODE( "com.sun.star.document.FilterFactory" ) ), ::com::sun::star::uno::UNO_QUERY );
/*N*/             xTypeCFG   = ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameAccess >( xServiceManager->createInstance( DEFINE_CONST_UNICODE( "com.sun.star.document.TypeDetection" ) ), ::com::sun::star::uno::UNO_QUERY );
/*N*/         }
/*N*/
/*N*/         if(
/*N*/             ( xFilterCFG.is() == sal_True ) &&
/*N*/             ( xTypeCFG.is()   == sal_True )
/*N*/           )
/*N*/         {
/*N*/             // select right query to get right set of filters for search modul
///*N*/             ::rtl::OUString sQuery;
///*N*/             if( rDocServiceName.EqualsAscii("com.sun.star.text.TextDocument"                ) == TRUE ) sQuery = DEFINE_CONST_UNICODE("_query_writer:sort_prop=uiname:use_order:default_first"    ); else
///*N*/             if( rDocServiceName.EqualsAscii("com.sun.star.text.WebDocument"                 ) == TRUE ) sQuery = DEFINE_CONST_UNICODE("_query_web:sort_prop=uiname:use_order:default_first"       ); else
///*N*/             if( rDocServiceName.EqualsAscii("com.sun.star.text.GlobalDocument"              ) == TRUE ) sQuery = DEFINE_CONST_UNICODE("_query_global:sort_prop=uiname:use_order:default_first"    ); else
///*N*/             if( rDocServiceName.EqualsAscii("com.sun.star.chart.ChartDocument"              ) == TRUE ) sQuery = DEFINE_CONST_UNICODE("_query_chart:sort_prop=uiname:use_order:default_first"     ); else
///*N*/             if( rDocServiceName.EqualsAscii("com.sun.star.sheet.SpreadsheetDocument"        ) == TRUE ) sQuery = DEFINE_CONST_UNICODE("_query_calc:sort_prop=uiname:use_order:default_first"      ); else
///*N*/             if( rDocServiceName.EqualsAscii("com.sun.star.presentation.PresentationDocument") == TRUE ) sQuery = DEFINE_CONST_UNICODE("_query_impress:sort_prop=uiname:use_order:default_first"   ); else
///*N*/             if( rDocServiceName.EqualsAscii("com.sun.star.drawing.DrawingDocument"          ) == TRUE ) sQuery = DEFINE_CONST_UNICODE("_query_draw:sort_prop=uiname:use_order:default_first"      ); else
///*N*/             if( rDocServiceName.EqualsAscii("com.sun.star.formula.FormulaProperties"        ) == TRUE ) sQuery = DEFINE_CONST_UNICODE("_query_math:sort_prop=uiname:use_order:default_first"      );
///*N*/
///*N*/             DBG_ASSERT( !(sQuery.getLength()<1), "SfxFilterContainer::ReadExternalFilters()\nCouldn't find right filter query for given modul! Filters will be ignored ...\n" );

                // select right query to get right set of filters for search modul
                ::std::vector< ::rtl::OUString > aFilterNameList;

                if(rDocServiceName.EqualsAscii("com.sun.star.text.TextDocument") == TRUE)
                {
                    for(sal_uInt32 a(0L); a < SFILTERNAMESFORTEXTDOCUMENT; a++)
                        aFilterNameList.push_back( OUString::createFromAscii( sFilterNamesForTextDocument[a] ));
                }
                else if(rDocServiceName.EqualsAscii("com.sun.star.text.WebDocument") == TRUE)
                {
                }
                else if(rDocServiceName.EqualsAscii("com.sun.star.text.GlobalDocument") == TRUE)
                {
                    for(sal_uInt32 a(0L); a < SFILTERNAMESFORGLOBALDOCUMENT; a++)
                        aFilterNameList.push_back( OUString::createFromAscii( sFilterNamesForGlobalDocument[a] ));
                }
                else if(rDocServiceName.EqualsAscii("com.sun.star.chart.ChartDocument") == TRUE)
                {
                    for(sal_uInt32 a(0L); a < SFILTERNAMESFORCHARTDOCUMENT; a++)
                        aFilterNameList.push_back( OUString::createFromAscii( sFilterNamesForChartDocument[a] ));
                }
                else if(rDocServiceName.EqualsAscii("com.sun.star.sheet.SpreadsheetDocument") == TRUE)
                {
                    for(sal_uInt32 a(0L); a < NNUMFILTERNAMESFORSPREADSHEETDOCUMENT; a++)
                        aFilterNameList.push_back( OUString::createFromAscii( sFilterNamesForSpreadsheetDocument[a] ));
                }
                else if(rDocServiceName.EqualsAscii("com.sun.star.presentation.PresentationDocument") == TRUE)
                {
                    for(sal_uInt32 a(0L); a < SFILTERNAMESFORPRESENTATIONDOCUMENT; a++)
                        aFilterNameList.push_back( OUString::createFromAscii( sFilterNamesForPresentationDocument[a] ));
                }
                else if(rDocServiceName.EqualsAscii("com.sun.star.drawing.DrawingDocument") == TRUE)
                {
                    for(sal_uInt32 a(0L); a < SFILTERNAMESFORDRAWINGDOCUMENT; a++)
                        aFilterNameList.push_back( OUString::createFromAscii( sFilterNamesForDrawingDocument[a] ));
                }
                else if(rDocServiceName.EqualsAscii("com.sun.star.formula.FormulaProperties") == TRUE)
                {
                    for(sal_uInt32 a(0L); a < SFILTERNAMESFORFORMULAPROPERTIES; a++)
                        aFilterNameList.push_back( OUString::createFromAscii( sFilterNamesForFormulaProperties[a] ));
                }

/*N*/             if( aFilterNameList.size() ) //sQuery.getLength() > 0 )
/*N*/             {
/*N*/                 // get all internal filter names, which are match given doc service name (modul)
/*N*/                 //::com::sun::star::uno::Sequence< ::rtl::OUString > lFilterNames;
/*N*/                 ::com::sun::star::uno::Any aResult;
/*N*/
/*N*/                 //aResult = xFilterCFG->getByName( sQuery );
///*N*/                 if(sFilterNameArray) //  aResult >>= lFilterNames )
///*N*/                 {
/*N*/                     // If list of filters already exist ...
/*N*/                     // ReadExternalFilters must work in update mode.
/*N*/                     // Best way seams to mark all filters NOT_INSTALLED
/*N*/                     // and change it back for all valid filters afterwards.
///*N*/                     BOOL bUpdated = FALSE;
///*N*/                     if( pImpl->aList.Count() > 0 )
///*N*/                     {
///*?*/                         bUpdated = TRUE;
///*?*/                         SfxFilterList_Impl& rList = pImpl->aList;
///*?*/                         USHORT nCount = (USHORT)rList.Count();
///*?*/                         SfxFilter* pFilter;
///*?*/                         for (USHORT f=0; f<nCount; ++f)
///*?*/                         {
///*?*/                             pFilter = NULL;
///*?*/                             pFilter = rList.GetObject(f);
///*?*/                             pFilter->nFormatType |= SFX_FILTER_NOTINSTALLED;
///*?*/                         }
///*N*/                     }
/*N*/
/*N*/                     // get all properties of filters ... put it into the filter container
/*N*/                     ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue > lFilterProperties                           ;
///*N*/                     sal_Int32                                                                 nFilterCount      = lFilterNames.getLength();
///*N*/                     sal_Int32                                                                 nFilter           = 0                       ;
/*N*/
/*N*/                     for(sal_uInt32 nFilter(0L); nFilter < aFilterNameList.size(); nFilter++) // nFilter=0; nFilter<nFilterCount; ++nFilter )
/*N*/                     {
/*N*/                         // Try to get filter .. but look for any exceptions!
/*N*/                         // May be filter was deleted by another thread ...
/*N*/                         ::rtl::OUString sFilterName(aFilterNameList[nFilter]); //::rtl::OUString sFilterName = lFilterNames[nFilter];
/*N*/                         try
/*N*/                         {
/*N*/                             aResult = xFilterCFG->getByName( sFilterName );
/*N*/                         }
/*N*/                         catch( ::com::sun::star::container::NoSuchElementException& )
/*N*/                         {
/*?*/                             aResult = ::com::sun::star::uno::Any();
/*N*/                         }
/*N*/
/*N*/                         if( aResult >>= lFilterProperties )
/*N*/                         {
/*N*/                             // collect informations to add filter to container
/*N*/                             // (attention: some informations aren't available on filter directly ... you must search for corresponding type too!)
/*N*/                             sal_Int32       nFlags          = 0 ;
/*N*/                             sal_Int32       nClipboardId    = 0 ;
/*N*/                             sal_Int32       nDocumentIconId = 0 ;
/*N*/                             sal_Int32       nFormatVersion  = 0 ;
/*N*/                             ::rtl::OUString sMimeType           ;
/*N*/                             ::rtl::OUString sType               ;
/*N*/                             ::rtl::OUString sUIName             ;
/*N*/                             ::rtl::OUString sHumanName          ;
/*N*/                             ::rtl::OUString sDefaultTemplate    ;
/*N*/                             ::rtl::OUString sUserData           ;
/*N*/                             ::rtl::OUString sExtension          ;
/*N*/
/*N*/                             // first get directly available properties
/*N*/                             sal_Int32 nFilterPropertyCount = lFilterProperties.getLength();
/*N*/                             sal_Int32 nFilterProperty      = 0                            ;
/*N*/                             for( nFilterProperty=0; nFilterProperty<nFilterPropertyCount; ++nFilterProperty )
/*N*/                             {
/*N*/                                 if( lFilterProperties[nFilterProperty].Name.compareToAscii( "FileFormatVersion" ) == 0 )
/*N*/                                 {
/*N*/                                     lFilterProperties[nFilterProperty].Value >>= nFormatVersion;
/*N*/                                 }
/*N*/                                 else if( lFilterProperties[nFilterProperty].Name.compareToAscii( "TemplateName" ) == 0 )
/*N*/                                 {
/*N*/                                     lFilterProperties[nFilterProperty].Value >>= sDefaultTemplate;
/*N*/                                 }
/*N*/                                 else if( lFilterProperties[nFilterProperty].Name.compareToAscii( "Flags" ) == 0 )
/*N*/                                 {
/*N*/                                     lFilterProperties[nFilterProperty].Value >>= nFlags;
/*N*/                                 }
/*N*/                                 else if( lFilterProperties[nFilterProperty].Name.compareToAscii( "UIName" ) == 0 )
/*N*/                                 {
/*N*/                                     lFilterProperties[nFilterProperty].Value >>= sUIName;
/*N*/                                 }
/*N*/                                 else if( lFilterProperties[nFilterProperty].Name.compareToAscii( "UserData" ) == 0 )
/*N*/                                 {
/*N*/                                     ::com::sun::star::uno::Sequence< ::rtl::OUString > lUserData;
/*N*/                                     lFilterProperties[nFilterProperty].Value >>= lUserData;
/*N*/                                     sUserData = implc_convertStringlistToString( lUserData, ',', ::rtl::OUString() );
/*N*/                                 }
/*N*/                                 else if( lFilterProperties[nFilterProperty].Name.compareToAscii( "Type" ) == 0 )
/*N*/                                 {
/*N*/                                     lFilterProperties[nFilterProperty].Value >>= sType;
/*N*/                                     // Try to get filter .. but look for any exceptions!
/*N*/                                     // May be filter was deleted by another thread ...
/*N*/                                     try
/*N*/                                     {
/*N*/                                         aResult = xTypeCFG->getByName( sType );
/*N*/                                     }
/*N*/                                     catch( ::com::sun::star::container::NoSuchElementException& )
/*N*/                                     {
/*?*/                                         aResult = ::com::sun::star::uno::Any();
/*N*/                                     }
/*N*/
/*N*/                                     ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue > lTypeProperties;
/*N*/                                     if( aResult >>= lTypeProperties )
/*N*/                                     {
/*N*/                                         // get indirect available properties then (types)
/*N*/                                         sal_Int32 nTypePropertyCount = lTypeProperties.getLength();
/*N*/                                         sal_Int32 nTypeProperty      = 0                          ;
/*N*/                                         for( nTypeProperty=0; nTypeProperty<nTypePropertyCount; ++nTypeProperty )
/*N*/                                         {
/*N*/                                             if( lTypeProperties[nTypeProperty].Name.compareToAscii( "ClipboardFormat" ) == 0 )
/*N*/                                             {
/*N*/                                                 lTypeProperties[nTypeProperty].Value >>= sHumanName;
/*N*/                                             }
/*N*/                                             else if( lTypeProperties[nTypeProperty].Name.compareToAscii( "DocumentIconID" ) == 0 )
/*N*/                                             {
/*N*/                                                 lTypeProperties[nTypeProperty].Value >>= nDocumentIconId;
/*N*/                                             }
/*N*/                                             else if( lTypeProperties[nTypeProperty].Name.compareToAscii( "MediaType" ) == 0 )
/*N*/                                             {
/*N*/                                                 lTypeProperties[nTypeProperty].Value >>= sMimeType;
/*N*/                                             }
/*N*/                                             else if( lTypeProperties[nTypeProperty].Name.compareToAscii( "Extensions" ) == 0 )
/*N*/                                             {
/*N*/                                                 ::com::sun::star::uno::Sequence< ::rtl::OUString > lExtensions;
/*N*/                                                 lTypeProperties[nTypeProperty].Value >>= lExtensions;
/*N*/                                                 sExtension = implc_convertStringlistToString( lExtensions, ';', DEFINE_CONST_UNICODE("*.") );
/*N*/                                             }
/*N*/                                             else if( lTypeProperties[nTypeProperty].Name.compareToAscii( "URLPattern" ) == 0 )
/*N*/                                             {
/*N*/                                                 lTypeProperties[nTypeProperty].Value >>= nFormatVersion;
/*N*/                                             }
/*N*/                                         }
/*N*/                                     }
/*N*/                                 }
/*N*/                             }
/*N*/                             // old formats are found ... using HumanPresentableName!
/*N*/                             if( sHumanName.getLength() )
/*N*/                             {
/*N*/                                 nClipboardId = SotExchange::RegisterFormatName( sHumanName );
/*N*/
//STRIP007 /*N*/            /*remove the bugid 100570*/                 // #100570# For external filters ignore clipboard IDs
//STRIP007 /*N*/                                if((nFlags & SFX_FILTER_STARONEFILTER) == SFX_FILTER_STARONEFILTER)
//STRIP007 /*N*/                                {
//STRIP007 /*?*/                                    nClipboardId = 0;
//STRIP007 /*N*/                                }
/*N*/                             }
/*N*/                             // register SfxFilter
/*N*/                             // first erase module name from old filter names!
/*N*/                             // e.g: "scalc: DIF" => "DIF"
/*N*/                             sal_Int32 nStartRealName = sFilterName.indexOf( DEFINE_CONST_UNICODE(": "), 0 );
/*N*/                             if( nStartRealName != -1 )
/*N*/                             {
/*?*/                                 DBG_ERROR("Old format, not supported!");
/*?*/                                 sFilterName = sFilterName.copy( nStartRealName+2 );
/*N*/                             }
/*N*/
/*N*/                             USHORT nCachePos = 0;
/*N*/                             if (!((nFlags & SFX_FILTER_DEFAULT) == SFX_FILTER_DEFAULT))
/*N*/                                 nCachePos = GetFilterCount();
/*N*/
/*N*/                             SfxFilter* pFilter = this->GetFilter4FilterName(sFilterName,0,0);
/*N*/                             const SfxFilter* pCheck = this->GetFilter4FilterName(sFilterName,0,0);
/*N*/                             BOOL bNew = FALSE;
/*N*/                             if (!pFilter)
/*N*/                             {
/*N*/                                 bNew = TRUE;
/*N*/                                 pFilter = new SfxFilter( sFilterName             ,
/*N*/                                                          sExtension              ,
/*N*/                                                          nFlags                  ,
/*N*/                                                          nClipboardId            ,
/*N*/                                                          sType                   ,
/*N*/                                                          sType                   ,
/*N*/                                                          (USHORT)nDocumentIconId ,
/*N*/                                                          sMimeType               ,
/*N*/                                                          this                    ,
/*N*/                                                          sUserData               );
/*N*/                             }
/*N*/                             else
/*N*/                             {
/*?*/                                 pFilter->aName        = sFilterName;
/*?*/                                 pFilter->aWildCard    = WildCard(sExtension, ';');
/*?*/                                 pFilter->nFormatType  = nFlags;
/*?*/                                 pFilter->lFormat      = nClipboardId;
/*?*/                                 pFilter->aMacType     = sType;
/*?*/                                 pFilter->aTypeName    = sType;
/*?*/                                 pFilter->nDocIcon     = (USHORT)nDocumentIconId;
/*?*/                                 pFilter->aMimeType    = sMimeType;
/*?*/                                 pFilter->pContainer   = this;
/*?*/                                 pFilter->aUserData    = sUserData;
/*?*/                             }
/*N*/
/*N*/                             // Don't forget to set right UIName!
/*N*/                             // Otherwise internal name is used as fallback ...
/*N*/                             pFilter->SetUIName( sUIName );
/*N*/                             pFilter->SetDefaultTemplate( sDefaultTemplate );
/*N*/                             if( nFormatVersion )
/*N*/                             {
/*N*/                                 pFilter->SetVersion( nFormatVersion );
/*N*/                             }

/*N*/                             if (bNew)
/*N*/                                 AddFilter(pFilter, nCachePos);
/*N*/                         }
/*N*/                     }
/*N*/
///*N*/                     // In case we updated an already filled cache, it was to complicated to
///*N*/                     // look for right place of the default filter!
///*N*/                     // It seams to be easiear to step over the whole container twice and
///*N*/                     // correct it now ...
///*N*/                     if (bUpdated)
///*N*/                     {
///*?*/                         SfxFilterList_Impl& rList       = pImpl->aList;
///*?*/                         SfxFilter*          pOldDefault = rList.First();
///*?*/                         SfxFilter*          pNewDefault = NULL         ;
///*?*/                         sal_Int32           nNewPos     = 0            ;
///*?*/
///*?*/                         if ((pOldDefault->nFormatType & SFX_FILTER_DEFAULT) != SFX_FILTER_DEFAULT)
///*?*/                         {
///*?*/                             USHORT nCount = (USHORT)rList.Count();
///*?*/                             SfxFilter* pFilter;
///*?*/                             for (USHORT f=0; f<nCount; ++f)
///*?*/                             {
///*?*/                                 pFilter = NULL;
///*?*/                                 pFilter = rList.GetObject(f);
///*?*/                                 if ((pFilter->nFormatType & SFX_FILTER_DEFAULT) == SFX_FILTER_DEFAULT)
///*?*/                                 {
///*?*/                                     pNewDefault = pFilter;
///*?*/                                     nNewPos     = f;
///*?*/                                     break;
///*?*/                                 }
///*?*/                             }
///*?*/
///*?*/                             if (nNewPos>0 && pNewDefault)
///*?*/                             {
///*?*/                                 rList.Remove( pNewDefault                 );
///*?*/                                 rList.Remove( pOldDefault                 );
///*?*/                                 rList.Insert( pNewDefault, (ULONG)0       );
///*?*/                                 rList.Insert( pOldDefault, (ULONG)nNewPos );
///*?*/                             }
///*N*/                         }
///*N*/                     }
///*N*/                 }
/*N*/             }
/*N*/         }
/*N*/     }
/*N*/     catch( ::com::sun::star::uno::Exception& )
/*N*/     {
/*N*/         DBG_ASSERT( sal_False, "SfxFilterContainer::ReadExternalFilter()\nException detected. Possible not all filters could be cached.\n" );
/*N*/     }
/*N*/ }

//STRIP001 sal_Bool SfxFilterContainer_Impl::equalFilterNames( const String& s1, const ::rtl::OUString& s2 ) const
//STRIP001 {
//STRIP001     ::rtl::OUString sC1( s1 );
//STRIP001     ::rtl::OUString sC2( s2 );
//STRIP001     sal_Int32       nPos = -1;
//STRIP001
//STRIP001     nPos = sC1.indexOf( DEFINE_CONST_UNICODE(": "), 0 );
//STRIP001     if( nPos > 0 )
//STRIP001     {
//STRIP001         sC1 = sC1.copy( nPos+2 );
//STRIP001     }
//STRIP001
//STRIP001     nPos = sC2.indexOf( DEFINE_CONST_UNICODE(": "), 0 );
//STRIP001     if( nPos > 0 )
//STRIP001     {
//STRIP001         sC2 = sC2.copy( nPos+2 );
//STRIP001     }
//STRIP001
//STRIP001     return( sC1 == sC2 );
//STRIP001 }

//STRIP001 void SfxFilterContainer_Impl::syncDefaults( const ::com::sun::star::uno::Sequence< ::rtl::OUString >& lNew )
//STRIP001 {
//STRIP001     // sync lists only, wich diff by old/new default filters only.
//STRIP001     // They must have same size and should be allready filled.
//STRIP001     if(
//STRIP001         ( lNew.getLength()        >  0             )    &&
//STRIP001         ( aList.Count()           >  0             )    &&
//STRIP001         ( (ULONG)lNew.getLength() == aList.Count() )
//STRIP001       )
//STRIP001     {
//STRIP001         SfxFilter* pOldDefault = aList.First();
//STRIP001         SfxFilter* pNewDefault = NULL         ;
//STRIP001         sal_Int32  nOldPos     = 0            ;
//STRIP001
//STRIP001         // search for old/new positions of items in both lists
//STRIP001         sal_Int32 nCount = aList.Count();
//STRIP001         for( sal_Int32 nStep=0; nStep<nCount; ++nStep )
//STRIP001         {
//STRIP001             // get new default filter
//STRIP001             if( equalFilterNames( aList.GetObject(nStep)->GetFilterName(), lNew[0] ) == sal_True )
//STRIP001             {
//STRIP001                 pNewDefault = aList.GetObject(nStep);
//STRIP001             }
//STRIP001
//STRIP001             // get position for old default filter
//STRIP001             if( equalFilterNames( pOldDefault->GetFilterName(), lNew[nStep] ) == sal_True )
//STRIP001             {
//STRIP001                 nOldPos = nStep;
//STRIP001             }
//STRIP001
//STRIP001             // break search, if all neccessary informations are available
//STRIP001             if( nOldPos>0 && pNewDefault!= NULL )
//STRIP001             {
//STRIP001                 break;
//STRIP001             }
//STRIP001         }
//STRIP001
//STRIP001         // realy changed ?!
//STRIP001         if(
//STRIP001             ( pOldDefault != pNewDefault )  &&
//STRIP001             ( nOldPos     >  0           )
//STRIP001           )
//STRIP001         {
//STRIP001             // move default filter to top of list
//STRIP001             aList.Remove( pNewDefault                 );
//STRIP001             aList.Insert( pNewDefault, (ULONG)0       );
//STRIP001             // move old default one to right place in list
//STRIP001             aList.Remove( pOldDefault                 );
//STRIP001             aList.Insert( pOldDefault, (ULONG)nOldPos );
//STRIP001         }
//STRIP001     }
//STRIP001 }
}
