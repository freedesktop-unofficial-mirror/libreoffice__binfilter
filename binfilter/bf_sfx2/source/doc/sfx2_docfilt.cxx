/*************************************************************************
 *
 *  $RCSfile: sfx2_docfilt.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: aw $ $Date: 2003-11-18 19:23:21 $
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

// INCLUDE ---------------------------------------------------------------

#ifdef SOLARIS
// HACK: prevent conflict between STLPORT and Workshop headers on Solaris 8
#include <ctime>
#endif

#include <string> // HACK: prevent conflict between STLPORT and Workshop headers

#ifndef _SOT_EXCHANGE_HXX
#include <sot/exchange.hxx>
#endif
#ifndef _COM_SUN_STAR_PLUGIN_PLUGINMODE_HPP_
#include <com/sun/star/plugin/PluginMode.hpp>
#endif
#ifndef _COM_SUN_STAR_PLUGIN_PLUGINDESCRIPTION_HPP_
#include <com/sun/star/plugin/PluginDescription.hpp>
#endif
#ifndef _COM_SUN_STAR_PLUGIN_PLUGINEXCEPTION_HPP_
#include <com/sun/star/plugin/PluginException.hpp>
#endif
#ifndef _COM_SUN_STAR_PLUGIN_PLUGINVARIABLE_HPP_
#include <com/sun/star/plugin/PluginVariable.hpp>
#endif
#ifndef _COM_SUN_STAR_PLUGIN_XPLUGIN_HPP_
#include <com/sun/star/plugin/XPlugin.hpp>
#endif
#ifndef _COM_SUN_STAR_PLUGIN_XPLUGINMANAGER_HPP_
#include <com/sun/star/plugin/XPluginManager.hpp>
#endif
#ifndef _COM_SUN_STAR_PLUGIN_XPLUGINCONTEXT_HPP_
#include <com/sun/star/plugin/XPluginContext.hpp>
#endif
#ifndef _UNOTOOLS_PROCESSFACTORY_HXX_
#include <comphelper/processfactory.hxx>
#endif

#pragma hdrstop

#include "docfac.hxx"
#include "docfilt.hxx"
#include "fltfnc.hxx"
#include "app.hxx"
#include "sfxresid.hxx"
#include "doc.hrc"
#include "sfxuno.hxx"

#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif
namespace binfilter {

// STATIC DATA -----------------------------------------------------------

/*N*/ DBG_NAME(SfxFilter)
/*N*/
/*N*/ SfxFilter::SfxFilter(  const String &rName,
/*N*/                      const String &rWildCard,
/*N*/                      SfxFilterFlags nType,
/*N*/                      sal_uInt32 lFmt,
/*N*/                      const String &rMacTyp,
/*N*/                      const String &rTypNm,
/*N*/                      sal_uInt16 nIcon,
/*N*/                      const String &rMimeType,
/*N*/                      const SfxFilterContainer* pContainerP,
/*N*/                      const String &rUsrDat ):
/*N*/   lFormat(lFmt),
/*N*/   nFormatType(nType),
/*N*/   aWildCard(rWildCard, ';'),
/*N*/   aMacType(rMacTyp),
/*N*/   aTypeName(rTypNm),
/*N*/   nDocIcon(nIcon),
/*N*/   aUserData(rUsrDat),
/*N*/   aName( rName ),
/*N*/   aMimeType( rMimeType ),
/*N*/   aFilterName( rName ),
/*N*/   pContainer( pContainerP )
/*N*/ {
/*N*/   InitMembers_Impl();
/*N*/   pContainer = pContainerP;
/*N*/   aFilterName = rName;
/*N*/   aMimeType = rMimeType;
/*N*/ }


/*?*/ SfxFilter::SfxFilter(  const char* pName, const String &rWildCard,
/*?*/                      SfxFilterFlags nType,
/*?*/                      const SfxFilterContainer* pContainerP )
/*?*/   : lFormat(0),
/*?*/     nFormatType(nType),
/*?*/     aWildCard(rWildCard, ';'),
/*?*/     nDocIcon(0),
/*?*/     pContainer( pContainerP )
/*?*/ {
/*?*/   aName = String::CreateFromAscii( pName );
/*?*/   aFilterName = String::CreateFromAscii( pName );
/*?*/   InitMembers_Impl();
/*?*/   pContainer = pContainerP;
/*?*/ }

/*?*/ SfxFilter::SfxFilter(  const char* pName, const String &rWildCard,
/*?*/                      SfxFilterFlags nType, const String &rTypeName,
/*?*/                      const SfxFilterContainer* pContainerP )
/*?*/   : lFormat(0),
/*?*/     nFormatType(nType),
/*?*/     aWildCard(rWildCard, ';'),
/*?*/     aTypeName( rTypeName ),
/*?*/     nDocIcon(0),
/*?*/     pContainer( pContainerP )
/*?*/ {
/*?*/   aName = String::CreateFromAscii( pName );
/*?*/   aFilterName = String::CreateFromAscii( pName );
/*?*/   InitMembers_Impl();
/*?*/   pContainer = pContainerP;
/*?*/ }

/*N*/ void SfxFilter::InitMembers_Impl()
/*N*/ {
/*N*/   String aExts = GetWildcard()();
/*N*/   String aShort, aLong;
/*N*/   String aRet;
/*N*/   sal_uInt16 nMaxLength =
/*N*/ #if defined( WIN ) || defined( OS2 )
/*N*/       3
/*N*/ #else
/*N*/       USHRT_MAX
/*N*/ #endif
/*N*/       ;
/*N*/   String aTest;
/*N*/   sal_uInt16 nPos = 0;
/*N*/   while( ( aRet = aExts.GetToken( nPos++, ';' ) ).Len() )
/*N*/   {
/*N*/       aTest = aRet;
/*N*/       aTest.SearchAndReplace( DEFINE_CONST_UNICODE( "*." ), String() );
/*N*/       if( aTest.Len() <= nMaxLength )
/*N*/       {
/*N*/           if( aShort.Len() ) aShort += ';';
/*N*/           aShort += aRet;
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           if( aLong.Len() ) aLong += ';';
/*N*/           aLong += aRet;
/*N*/       }
/*N*/   }
/*N*/   if( aShort.Len() && aLong.Len() )
/*N*/   {
/*N*/       aShort += ';';
/*N*/       aShort += aLong;
/*N*/   }
/*N*/   aWildCard = aShort;
/*N*/
/*N*/     nVersion = SOFFICE_FILEFORMAT_50;
/*N*/   bPlugDataSearched = 0;
/*N*/   pPlugData = 0;
/*N*/   aUIName = aFilterName;
/*N*/ }

/*N*/ SfxFilter::~SfxFilter()
/*N*/ {
/*N*/   delete pPlugData;
/*N*/ }

/*N*/ const String& SfxFilter::GetTypeName() const
/*N*/ {
/*N*/   return
/*N*/ #ifdef MAC
/*N*/   aMacType;
/*N*/ #else
/*N*/   aTypeName;
/*N*/ #endif
/*N*/ }

/*?*/ const ::com::sun::star::plugin::PluginDescription* SfxFilter::GetPlugData()
/*?*/ {DBG_ASSERT(0, "STRIP"); return 0;//STRIP001
//STRIP001  if( !bPlugDataSearched )
//STRIP001  {
//STRIP001      bPlugDataSearched = sal_True;
//STRIP001
//STRIP001         ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >  xMan = ::legacy_binfilters::getLegacyProcessServiceFactory();
//STRIP001      ::com::sun::star::uno::Reference< ::com::sun::star::plugin::XPluginManager >
//STRIP001              xPlugMgr( xMan->createInstance( DEFINE_CONST_UNICODE( "com.sun.star.plugin.PluginManager" ) ), ::com::sun::star::uno::UNO_QUERY );
//STRIP001      DBG_ASSERT( xPlugMgr.is(), "### cannot create instance com.sun.star.plugin.PluginManager!" );
//STRIP001      if( xPlugMgr.is() )
//STRIP001      {
//STRIP001          ::com::sun::star::uno::Sequence < ::com::sun::star::plugin::PluginDescription > aDescr = xPlugMgr->getPluginDescriptions();
//STRIP001          const ::com::sun::star::plugin::PluginDescription *pArr = aDescr.getConstArray();
//STRIP001          sal_uInt16 n;
//STRIP001          for (n=0; n<aDescr.getLength(); n++ )
//STRIP001          {
//STRIP001              const ::com::sun::star::plugin::PluginDescription& rData = pArr[n];
//STRIP001              String aTest = rData.Description;
//STRIP001              aTest += DEFINE_CONST_UNICODE( " (PlugIn)" );
//STRIP001              if( aTest == GetFilterName() )
//STRIP001                  break;
//STRIP001          }
//STRIP001
//STRIP001          const ::com::sun::star::plugin::PluginDescription& rData = pArr[n];
//STRIP001          ::com::sun::star::plugin::PluginDescription *pPlug = new ::com::sun::star::plugin::PluginDescription;
//STRIP001          pPlug->PluginName = rData.PluginName;
//STRIP001          pPlug->Mimetype = rData.Mimetype;
//STRIP001          pPlug->Extension = rData.Extension;
//STRIP001          pPlug->Description = rData.Description;
//STRIP001
//STRIP001          pPlugData = pPlug;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return pPlugData;
/*?*/ }

/*?*/ sal_Bool SfxFilter::IsFirstPlugin() const
/*?*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  const ::com::sun::star::plugin::PluginDescription* pData = GetPlugData();
//STRIP001  if( pData )
//STRIP001  {
//STRIP001         ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >  xMan = ::legacy_binfilters::getLegacyProcessServiceFactory();
//STRIP001      ::com::sun::star::uno::Reference< ::com::sun::star::plugin::XPluginManager >
//STRIP001          xPlugMgr( xMan->createInstance( DEFINE_CONST_UNICODE( "com.sun.star.plugin.PluginManager" ) ), ::com::sun::star::uno::UNO_QUERY );
//STRIP001      DBG_ASSERT( xPlugMgr.is(), "### cannot create instance com.sun.star.plugin.PluginManager!" );
//STRIP001      if( xPlugMgr.is() )
//STRIP001      {
//STRIP001          ::com::sun::star::uno::Sequence < ::com::sun::star::plugin::PluginDescription > aDescr = xPlugMgr->getPluginDescriptions();
//STRIP001          String aPlug;
//STRIP001          const ::com::sun::star::plugin::PluginDescription *pArr = aDescr.getConstArray();
//STRIP001          String aTest;
//STRIP001          for ( sal_uInt16 n=0; n<aDescr.getLength(); n++ )
//STRIP001          {
//STRIP001              if( pArr[n].Description == pData->Description )
//STRIP001                  return sal_True;
//STRIP001              else if( pArr[n].PluginName == pData->PluginName )
//STRIP001                      return sal_False;
//STRIP001          }
//STRIP001      }
//STRIP001  }
/*?*/   return sal_False;
/*?*/ }


/*?*/ String SfxFilter::GetDefaultExtension() const
/*?*/ {
/*?*/   return GetWildcard()().GetToken( 0, ';' );
/*?*/ }


/*?*/ String SfxFilter::GetSuffixes() const
/*?*/ {
/*?*/   String aRet = GetWildcard()();
/*?*/   while( aRet.SearchAndReplaceAscii( "*.", String() ) != STRING_NOTFOUND );
/*?*/   while( aRet.SearchAndReplace( ';', ',' ) != STRING_NOTFOUND );
/*?*/   return aRet;
/*?*/ }

/*N*/ String SfxFilter::GetFilterNameWithPrefix() const
/*N*/ {
/*N*/     String aName = pContainer->GetName();
/*N*/   aName += DEFINE_CONST_UNICODE( ": " );
/*N*/   aName += aFilterName;
/*N*/     return aName;
/*N*/ }
}
