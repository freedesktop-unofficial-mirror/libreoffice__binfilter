/*************************************************************************
 *
 *  $RCSfile: svx_fmtools.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:40:32 $
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
#pragma hdrstop

#ifndef _COM_SUN_STAR_LANG_XSERVICEINFO_HPP_
#include <com/sun/star/lang/XServiceInfo.hpp>
#endif
#ifndef _COM_SUN_STAR_IO_XPERSISTOBJECT_HPP_
#include <com/sun/star/io/XPersistObject.hpp>
#endif
#ifndef _COM_SUN_STAR_UI_DIALOGS_XEXECUTABLEDIALOG_HPP_
#include <com/sun/star/ui/dialogs/XExecutableDialog.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_XCOMPLETEDCONNECTION_HPP_
#include <com/sun/star/sdb/XCompletedConnection.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_PRIVILEGE_HPP_
#include <com/sun/star/sdbcx/Privilege.hpp>
#endif
#ifndef _ISOLANG_HXX
#include <tools/isolang.hxx>
#endif
#ifndef _COM_SUN_STAR_LANG_LOCALE_HPP_
#include <com/sun/star/lang/Locale.hpp>
#endif
#ifndef _SVX_FMTOOLS_HXX
#include "fmtools.hxx"
#endif
#ifndef SVX_DBTOOLSCLIENT_HXX
#include "dbtoolsclient.hxx"
#endif
#ifndef _SVX_FMSERVS_HXX
#include "fmservs.hxx"
#endif
#ifndef _SVX_FMGLOB_HXX
#include "fmglob.hxx"
#endif
#ifndef _VCL_STDTEXT_HXX
#include <vcl/stdtext.hxx>
#endif
#ifndef _TOOLKIT_HELPER_VCLUNOHELPER_HXX_
#include <toolkit/unohlp.hxx>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>

#ifndef _COM_SUN_STAR_UNO_XNAMINGSERVICE_HPP_
#include <com/sun/star/uno/XNamingService.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_XDATASOURCE_HPP_
#include <com/sun/star/sdbc/XDataSource.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_COMMANDTYPE_HPP_
#include <com/sun/star/sdb/CommandType.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_XQUERIESSUPPLIER_HPP_
#include <com/sun/star/sdb/XQueriesSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_SQLCONTEXT_HPP_
#include <com/sun/star/sdb/SQLContext.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_XTABLESSUPPLIER_HPP_
#include <com/sun/star/sdbcx/XTablesSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_XRESULTSETACCESS_HPP_
#include <com/sun/star/sdb/XResultSetAccess.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_DATATYPE_HPP_
#include <com/sun/star/sdbc/DataType.hpp>
#endif

#ifndef _COM_SUN_STAR_UTIL_NUMBERFORMAT_HPP_
#include <com/sun/star/util/NumberFormat.hpp>
#endif
#ifndef _COM_SUN_STAR_IO_XACTIVEDATASINK_HPP_
#include <com/sun/star/io/XActiveDataSink.hpp>
#endif
#ifndef _COM_SUN_STAR_IO_XACTIVEDATASOURCE_HPP_
#include <com/sun/star/io/XActiveDataSource.hpp>
#endif
#ifndef _COM_SUN_STAR_SCRIPT_XEVENTATTACHERMANAGER_HPP_
#include <com/sun/star/script/XEventAttacherManager.hpp>
#endif
#ifndef _COM_SUN_STAR_FORM_XFORM_HPP_
#include <com/sun/star/form/XForm.hpp>
#endif
#ifndef _COM_SUN_STAR_FORM_XFORMCOMPONENT_HPP_
#include <com/sun/star/form/XFormComponent.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_XNUMBERFORMATTER_HPP_
#include <com/sun/star/util/XNumberFormatter.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_XNUMBERFORMATSSUPPLIER_HPP_
#include <com/sun/star/util/XNumberFormatsSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_LANGUAGE_HPP_
#include <com/sun/star/util/Language.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_XNUMBERFORMATS_HPP_
#include <com/sun/star/util/XNumberFormats.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_XNUMBERFORMATTYPES_HPP_
#include <com/sun/star/util/XNumberFormatTypes.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_XCLONEABLE_HPP_
#include <com/sun/star/util/XCloneable.hpp>
#endif
#ifndef _COM_SUN_STAR_IO_XOBJECTINPUTSTREAM_HPP_
#include <com/sun/star/io/XObjectInputStream.hpp>
#endif
#ifndef _COM_SUN_STAR_IO_XOBJECTOUTPUTSTREAM_HPP_
#include <com/sun/star/io/XObjectOutputStream.hpp>
#endif
#ifndef _COM_SUN_STAR_REFLECTION_XIDLCLASS_HPP_
#include <com/sun/star/reflection/XIdlClass.hpp>
#endif
#ifndef _COM_SUN_STAR_REFLECTION_XIDLMETHOD_HPP_
#include <com/sun/star/reflection/XIdlMethod.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_XINTROSPECTION_HPP_
#include <com/sun/star/beans/XIntrospection.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_PROPERTYATTRIBUTE_HPP_
#include <com/sun/star/beans/PropertyAttribute.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XCHILD_HPP_
#include <com/sun/star/container/XChild.hpp>
#endif
#ifndef _COM_SUN_STAR_TASK_XINTERACTIONHANDLER_HPP_
#include <com/sun/star/task/XInteractionHandler.hpp>
#endif

#ifndef _TOOLS_DEBUG_HXX //autogen
#include <tools/debug.hxx>
#endif

#ifndef _STRING_HXX
#include <tools/string.hxx>
#endif

#ifndef _SBXVAR_HXX //autogen
#include <svtools/sbxvar.hxx>
#endif

#ifndef INCLUDED_RTL_MATH_HXX
#include <rtl/math.hxx>
#endif

#ifndef _SV_SVAPP_HXX //autogen
#include <vcl/svapp.hxx>
#endif

#ifndef _INTN_HXX //autogen
#include <tools/intn.hxx>
#endif

#ifndef _SVX_FMPROP_HRC
#include "fmprop.hrc"
#endif

#ifndef _SFX_BINDINGS_HXX //autogen wg. SfxBindings
#include <bf_sfx2/bindings.hxx>
#endif

#ifndef _SFXENUMITEM_HXX //autogen wg. SfxBoolItem
#include <svtools/eitem.hxx>
#endif

#ifndef _SFXSTRITEM_HXX //autogen wg. SfxStringItem
#include <svtools/stritem.hxx>
#endif

#ifndef _CPPUHELPER_SERVICEFACTORY_HXX_
#include <cppuhelper/servicefactory.hxx>
#endif
#ifndef _COMPHELPER_TYPES_HXX_
#include <comphelper/types.hxx>
#endif
#ifndef _COMPHELPER_PROPERTY_HXX_
#include <comphelper/property.hxx>
#endif
#ifndef _COMPHELPER_CONTAINER_HXX_
#include <comphelper/container.hxx>
#endif
#ifndef _CONNECTIVITY_DBTOOLS_HXX_
#include <connectivity/dbtools.hxx>
#endif
#ifndef _COMPHELPER_PROCESSFACTORY_HXX_
#include <comphelper/processfactory.hxx>
#endif
#ifndef _COMPHELPER_SEQUENCE_HXX_
#include <comphelper/sequence.hxx>
#endif
#ifndef _FM_STATIC_HXX_
#include "fmstatic.hxx"
#endif
#ifndef _COMPHELPER_EXTRACT_HXX_
#include <comphelper/extract.hxx>
#endif
#ifndef _COMPHELPER_UNO3_HXX_
#include <comphelper/uno3.hxx>
#endif
#ifndef _DBHELPER_DBEXCEPTION_HXX_
#include <connectivity/dbexception.hxx>
#endif
#ifndef _COMPHELPER_EXTRACT_HXX_
#include <comphelper/extract.hxx>
#endif
#include <algorithm>
#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif
namespace binfilter {

namespace svxform
{

    IMPLEMENT_CONSTASCII_USTRING(DATA_MODE,"DataMode");
    IMPLEMENT_CONSTASCII_USTRING(FILTER_MODE,"FilterMode");

}   // namespace svxform

using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::util;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::frame;
using namespace ::com::sun::star::awt;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::ui::dialogs;
using namespace ::com::sun::star::sdbc;
using namespace ::com::sun::star::sdbcx;
using namespace ::com::sun::star::sdb;
using namespace ::com::sun::star::task;
using namespace ::binfilter::svxform;//STRIP008 using namespace ::svxform;
using namespace ::connectivity::simple;

//  ------------------------------------------------------------------------------
//STRIP001 void displayException(const Any& _rExcept, Window* _pParent = NULL)
//STRIP001 {
//STRIP001  try
//STRIP001  {
//STRIP001      // the parent window
//STRIP001      Window* pParentWindow = _pParent ? _pParent : GetpApp()->GetDefDialogParent();
//STRIP001      Reference< XWindow > xParentWindow = VCLUnoHelper::GetInterface(pParentWindow);
//STRIP001
//STRIP001      Sequence< Any > aArgs(2);
//STRIP001      aArgs[0] <<= PropertyValue(::rtl::OUString::createFromAscii("SQLException"), 0, makeAny(_rExcept), PropertyState_DIRECT_VALUE);
//STRIP001      aArgs[1] <<= PropertyValue(::rtl::OUString::createFromAscii("ParentWindow"), 0, makeAny(xParentWindow), PropertyState_DIRECT_VALUE);
//STRIP001
//STRIP001      static ::rtl::OUString s_sDialogServiceName = ::rtl::OUString::createFromAscii("com.sun.star.sdb.ErrorMessageDialog");
//STRIP001      Reference< XExecutableDialog > xErrorDialog(
//STRIP001          ::legacy_binfilters::getLegacyProcessServiceFactory()->createInstanceWithArguments(s_sDialogServiceName, aArgs), UNO_QUERY);
//STRIP001      if (xErrorDialog.is())
//STRIP001          xErrorDialog->execute();
//STRIP001      else
//STRIP001          ShowServiceNotAvailableError(pParentWindow, s_sDialogServiceName, sal_True);
//STRIP001  }
//STRIP001  catch(Exception&)
//STRIP001  {
//STRIP001      OSL_ENSURE(sal_False, "displayException: could not display the error message!");
//STRIP001  }
//STRIP001 }

//  ------------------------------------------------------------------------------
//STRIP001 void displayException(const ::com::sun::star::sdbc::SQLException& _rExcept, Window* _pParent)
//STRIP001 {
//STRIP001  displayException(makeAny(_rExcept), _pParent);
//STRIP001 }

//  ------------------------------------------------------------------------------
//STRIP001 void displayException(const ::com::sun::star::sdbc::SQLWarning& _rExcept, Window* _pParent)
//STRIP001 {
//STRIP001  displayException(makeAny(_rExcept), _pParent);
//STRIP001 }

//  ------------------------------------------------------------------------------
//STRIP001 void displayException(const ::com::sun::star::sdb::SQLContext& _rExcept, Window* _pParent)
//STRIP001 {
//STRIP001  displayException(makeAny(_rExcept), _pParent);
//STRIP001 }

//  ------------------------------------------------------------------------------
//STRIP001 void displayException(const ::com::sun::star::sdb::SQLErrorEvent& _rEvent, Window* _pParent)
//STRIP001 {
//STRIP001  displayException(_rEvent.Reason, _pParent);
//STRIP001 }

//------------------------------------------------------------------------------
//STRIP001 Reference< XInterface > cloneUsingProperties(const Reference< ::com::sun::star::io::XPersistObject>& _xObj)
//STRIP001 {
//STRIP001  if (!_xObj.is())
//STRIP001      return Reference< XInterface >();
//STRIP001
//STRIP001  // create a new object
//STRIP001  ::rtl::OUString aObjectService = _xObj->getServiceName();
//STRIP001  Reference< ::com::sun::star::beans::XPropertySet> xDestSet(::legacy_binfilters::getLegacyProcessServiceFactory()->createInstance(aObjectService), UNO_QUERY);
//STRIP001  if (!xDestSet.is())
//STRIP001  {
//STRIP001      DBG_ERROR("cloneUsingProperties : could not instantiate an object of the given type !");
//STRIP001      return Reference< XInterface >();
//STRIP001  }
//STRIP001  // transfer properties
//STRIP001  Reference< XPropertySet > xSourceSet(_xObj, UNO_QUERY);
//STRIP001  Reference< XPropertySetInfo > xSourceInfo( xSourceSet->getPropertySetInfo());
//STRIP001  Sequence< Property> aSourceProperties = xSourceInfo->getProperties();
//STRIP001  Reference< XPropertySetInfo > xDestInfo( xDestSet->getPropertySetInfo());
//STRIP001  Sequence< Property> aDestProperties = xDestInfo->getProperties();
//STRIP001  int nDestLen = aDestProperties.getLength();
//STRIP001
//STRIP001  Property* pSourceProps = aSourceProperties.getArray();
//STRIP001  Property* pSourceEnd = pSourceProps + aSourceProperties.getLength();
//STRIP001  Property* pDestProps = aDestProperties.getArray();
//STRIP001
//STRIP001  for (; pSourceProps != pSourceEnd; ++pSourceProps)
//STRIP001  {
//STRIP001      ::com::sun::star::beans::Property* pResult = ::std::lower_bound(
//STRIP001              pDestProps,
//STRIP001              pDestProps + nDestLen,
//STRIP001              pSourceProps->Name,
//STRIP001              ::comphelper::PropertyStringLessFunctor()
//STRIP001          );
//STRIP001
//STRIP001      if  (   ( pResult != pDestProps + nDestLen )
//STRIP001          &&  ( pResult->Name == pSourceProps->Name )
//STRIP001          &&  ( pResult->Attributes == pSourceProps->Attributes )
//STRIP001          &&  ( (pResult->Attributes &  PropertyAttribute::READONLY ) == 0 )
//STRIP001          &&  ( pResult->Type.equals( pSourceProps->Type ) )
//STRIP001          )
//STRIP001      {   // Attribute/type are the same and the prop isn't readonly
//STRIP001          try
//STRIP001          {
//STRIP001              xDestSet->setPropertyValue(pResult->Name, xSourceSet->getPropertyValue(pResult->Name));
//STRIP001          }
//STRIP001          catch(IllegalArgumentException e)
//STRIP001          {
//STRIP001              e;
//STRIP001 #ifdef DBG_UTIL
//STRIP001              ::rtl::OString sMessage("cloneUsingProperties : could not transfer the value for property \"");
//STRIP001              sMessage = sMessage + ::rtl::OString(pResult->Name.getStr(), pResult->Name.getLength(), RTL_TEXTENCODING_ASCII_US);
//STRIP001              sMessage = sMessage + '\"';
//STRIP001              DBG_ERROR(sMessage);
//STRIP001 #endif
//STRIP001          }
//STRIP001
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return xDestSet;
//STRIP001 }

//------------------------------------------------------------------------------
//STRIP001 sal_Bool searchElement(const Reference< ::com::sun::star::container::XIndexAccess>& xCont, const Reference< XInterface >& xElement)
//STRIP001 {
//STRIP001  if (!xCont.is() || !xElement.is())
//STRIP001      return sal_False;
//STRIP001
//STRIP001  sal_Int32 nCount = xCont->getCount();
//STRIP001  Reference< XInterface > xComp;
//STRIP001  for (sal_Int32 i = 0; i < nCount; i++)
//STRIP001  {
//STRIP001      try
//STRIP001      {
//STRIP001          xCont->getByIndex(i) >>= xComp;
//STRIP001          if (xComp.is())
//STRIP001          {
//STRIP001              if (((XInterface *)xElement.get()) == (XInterface*)xComp.get())
//STRIP001                  return sal_True;
//STRIP001              else
//STRIP001              {
//STRIP001                  Reference< ::com::sun::star::container::XIndexAccess> xCont2(xComp, UNO_QUERY);
//STRIP001                  if (xCont2.is() && searchElement(xCont2, xElement))
//STRIP001                      return sal_True;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      catch(Exception&)
//STRIP001      {
//STRIP001      }
//STRIP001  }
//STRIP001  return sal_False;
//STRIP001 }

//------------------------------------------------------------------------------
/*N*/ sal_Int32 getElementPos(const Reference< ::com::sun::star::container::XIndexAccess>& xCont, const Reference< XInterface >& xElement)
/*N*/ {
/*N*/   sal_Int32 nIndex = -1;
/*N*/   if (!xCont.is())
/*N*/       return nIndex;
/*N*/

/*N*/   Reference< XInterface > xNormalized( xElement, UNO_QUERY );
/*N*/   DBG_ASSERT( xNormalized.is(), "getElementPos: invalid element!" );
/*N*/   if ( xNormalized.is() )
/*N*/   {
/*N*/       // Feststellen an welcher Position sich das Kind befindet
/*N*/       nIndex = xCont->getCount();
/*N*/       while (nIndex--)
/*N*/       {
/*N*/           try
/*N*/           {
/*N*/               Reference< XInterface > xCurrent;
/*N*/               xCont->getByIndex( nIndex ) >>= xCurrent;
/*N*/               DBG_ASSERT( xCurrent.get() == Reference< XInterface >( xCurrent, UNO_QUERY ).get(),
/*N*/                   "getElementPos: container element not normalized!" );
/*N*/               if ( xNormalized.get() == xCurrent.get() )
/*N*/                   break;
/*N*/           }
/*N*/           catch(Exception&)
/*N*/           {
/*N*/               DBG_ERROR( "getElementPos: caught an exception!" );
/*N*/           }
/*N*/
/*N*/       }
/*N*/   }
/*N*/   return nIndex;
/*N*/ }

//------------------------------------------------------------------
//STRIP001 String getFormComponentAccessPath(const Reference< XInterface >& _xElement, Reference< XInterface >& _rTopLevelElement)
//STRIP001 {
//STRIP001  Reference< ::com::sun::star::form::XFormComponent> xChild(_xElement, UNO_QUERY);
//STRIP001  Reference< ::com::sun::star::container::XIndexAccess> xParent;
//STRIP001  if (xChild.is())
//STRIP001      xParent = Reference< ::com::sun::star::container::XIndexAccess>(xChild->getParent(), UNO_QUERY);
//STRIP001
//STRIP001  // while the current content is a form
//STRIP001  String sReturn;
//STRIP001  String sCurrentIndex;
//STRIP001  while (xChild.is())
//STRIP001  {
//STRIP001      // get the content's relative pos within it's parent container
//STRIP001      sal_Int32 nPos = getElementPos(xParent, xChild);
//STRIP001
//STRIP001      // prepend this current relaive pos
//STRIP001      sCurrentIndex = String::CreateFromInt32(nPos);
//STRIP001      if (sReturn.Len() != 0)
//STRIP001      {
//STRIP001          sCurrentIndex += '\\';
//STRIP001          sCurrentIndex += sReturn;
//STRIP001      }
//STRIP001
//STRIP001      sReturn = sCurrentIndex;
//STRIP001
//STRIP001      // travel up
//STRIP001      if (::comphelper::query_interface((Reference< XInterface >)xParent,xChild))
//STRIP001          xParent = Reference< ::com::sun::star::container::XIndexAccess>(xChild->getParent(), UNO_QUERY);
//STRIP001  }
//STRIP001
//STRIP001  _rTopLevelElement = xParent;
//STRIP001  return sReturn;
//STRIP001 }

//------------------------------------------------------------------
//STRIP001 String getFormComponentAccessPath(const Reference< XInterface >& _xElement)
//STRIP001 {
//STRIP001  Reference< XInterface > xDummy;
//STRIP001  return getFormComponentAccessPath(_xElement, xDummy);
//STRIP001 }

//------------------------------------------------------------------------------
//STRIP001 Reference< XInterface > getElementFromAccessPath(const Reference< ::com::sun::star::container::XIndexAccess>& _xParent, const String& _rRelativePath)
//STRIP001 {
//STRIP001  if (!_xParent.is())
//STRIP001      return Reference< XInterface >();
//STRIP001  Reference< ::com::sun::star::container::XIndexAccess> xContainer(_xParent);
//STRIP001  Reference< XInterface > xElement( _xParent);
//STRIP001
//STRIP001  String sPath(_rRelativePath);
//STRIP001  while (sPath.Len() && xContainer.is())
//STRIP001  {
//STRIP001      xub_StrLen nSepPos = sPath.Search((sal_Unicode)'\\');
//STRIP001
//STRIP001      String sIndex(sPath.Copy(0, (nSepPos == STRING_NOTFOUND) ? sPath.Len() : nSepPos));
//STRIP001      //  DBG_ASSERT(sIndex.IsNumeric(), "getElementFromAccessPath : invalid path !");
//STRIP001
//STRIP001      sPath = sPath.Copy((nSepPos == STRING_NOTFOUND) ? sPath.Len() : nSepPos+1);
//STRIP001
//STRIP001      ::cppu::extractInterface(xElement, xContainer->getByIndex(sIndex.ToInt32()));
//STRIP001      xContainer = Reference< ::com::sun::star::container::XIndexAccess>::query(xElement);
//STRIP001  }
//STRIP001
//STRIP001  if (sPath.Len() != 0)
//STRIP001      // the loop terminated because an element wasn't a container, but we stil have a path -> the path is invalid
//STRIP001      xElement = NULL;
//STRIP001
//STRIP001  return xElement;
//STRIP001 }

//------------------------------------------------------------------
// Vergleichen von PropertyInfo
//STRIP001 extern "C" int
//STRIP001 #if defined( WNT )
//STRIP001  __cdecl
//STRIP001 #endif
//STRIP001 #if defined( ICC ) && defined( OS2 )
//STRIP001 _Optlink
//STRIP001 #endif
//STRIP001  NameCompare(const void* pFirst, const void* pSecond)
//STRIP001 {
//STRIP001  return ((::rtl::OUString*)pFirst)->compareTo(*(::rtl::OUString*)pSecond);
//STRIP001 }

//------------------------------------------------------------------------------
//STRIP001 sal_Int32 findPos(const ::rtl::OUString& aStr, const Sequence< ::rtl::OUString>& rList)
//STRIP001 {
//STRIP001  const ::rtl::OUString* pStrList = rList.getConstArray();
//STRIP001  ::rtl::OUString* pResult = (::rtl::OUString*) bsearch(&aStr, (void*)pStrList, rList.getLength(), sizeof(::rtl::OUString),
//STRIP001      &NameCompare);
//STRIP001
//STRIP001  if (pResult)
//STRIP001      return (pResult - pStrList);
//STRIP001  else
//STRIP001      return -1;
//STRIP001 }

//------------------------------------------------------------------
//STRIP001 Reference< ::com::sun::star::frame::XModel> getXModel(const Reference< XInterface >& xIface)
//STRIP001 {
//STRIP001  Reference< ::com::sun::star::frame::XModel> xModel(xIface, UNO_QUERY);
//STRIP001  if (xModel.is())
//STRIP001      return xModel;
//STRIP001  else
//STRIP001  {
//STRIP001      Reference< ::com::sun::star::container::XChild> xChild(xIface, UNO_QUERY);
//STRIP001      if (xChild.is())
//STRIP001      {
//STRIP001          Reference< XInterface > xParent( xChild->getParent());
//STRIP001          return getXModel(xParent);
//STRIP001      }
//STRIP001      else
//STRIP001          return NULL;
//STRIP001  }
//STRIP001 }

//------------------------------------------------------------------
//STRIP001 ::rtl::OUString getLabelName(const Reference< ::com::sun::star::beans::XPropertySet>& xControlModel)
//STRIP001 {
//STRIP001  if (!xControlModel.is())
//STRIP001      return ::rtl::OUString();
//STRIP001
//STRIP001  if (::comphelper::hasProperty(FM_PROP_CONTROLLABEL, xControlModel))
//STRIP001  {
//STRIP001      Reference< ::com::sun::star::beans::XPropertySet> xLabelSet;
//STRIP001      xControlModel->getPropertyValue(FM_PROP_CONTROLLABEL) >>= xLabelSet;
//STRIP001      if (xLabelSet.is() && ::comphelper::hasProperty(FM_PROP_LABEL, xLabelSet))
//STRIP001      {
//STRIP001          Any aLabel( xLabelSet->getPropertyValue(FM_PROP_LABEL) );
//STRIP001          if ((aLabel.getValueTypeClass() == TypeClass_STRING) && ::comphelper::getString(aLabel).getLength())
//STRIP001              return ::comphelper::getString(aLabel);
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return ::comphelper::getString(xControlModel->getPropertyValue(FM_PROP_CONTROLSOURCE));
//STRIP001 }

//========================================================================
// = CursorWrapper
//------------------------------------------------------------------------
//STRIP001 CursorWrapper::CursorWrapper(const Reference< ::com::sun::star::sdbc::XRowSet>& _rxCursor, sal_Bool bUseCloned)
//STRIP001 {
//STRIP001  ImplConstruct(Reference< ::com::sun::star::sdbc::XResultSet>(_rxCursor, UNO_QUERY), bUseCloned);
//STRIP001 }

//------------------------------------------------------------------------
//STRIP001 CursorWrapper::CursorWrapper(const Reference< ::com::sun::star::sdbc::XResultSet>& _rxCursor, sal_Bool bUseCloned)
//STRIP001 {
//STRIP001  ImplConstruct(_rxCursor, bUseCloned);
//STRIP001 }

//------------------------------------------------------------------------
//STRIP001 void CursorWrapper::ImplConstruct(const Reference< ::com::sun::star::sdbc::XResultSet>& _rxCursor, sal_Bool bUseCloned)
//STRIP001 {
//STRIP001  if (bUseCloned)
//STRIP001  {
//STRIP001      Reference< ::com::sun::star::sdb::XResultSetAccess> xAccess(_rxCursor, UNO_QUERY);
//STRIP001      try
//STRIP001      {
//STRIP001          m_xMoveOperations = xAccess.is() ? xAccess->createResultSet() : Reference< ::com::sun::star::sdbc::XResultSet>();
//STRIP001      }
//STRIP001      catch(Exception&)
//STRIP001      {
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001      m_xMoveOperations   = _rxCursor;
//STRIP001
//STRIP001  m_xBookmarkOperations   = m_xBookmarkOperations.query( m_xMoveOperations );
//STRIP001  m_xColumnsSupplier      = m_xColumnsSupplier.query( m_xMoveOperations );
//STRIP001  m_xPropertyAccess       = m_xPropertyAccess.query( m_xMoveOperations );
//STRIP001
//STRIP001  if ( !m_xMoveOperations.is() || !m_xBookmarkOperations.is() || !m_xColumnsSupplier.is() || !m_xPropertyAccess.is() )
//STRIP001  {   // all or nothing !!
//STRIP001      m_xMoveOperations = NULL;
//STRIP001      m_xBookmarkOperations = NULL;
//STRIP001      m_xColumnsSupplier = NULL;
//STRIP001  }
//STRIP001  else
//STRIP001      m_xGeneric = m_xMoveOperations.get();
//STRIP001 }

//------------------------------------------------------------------------
//STRIP001 const CursorWrapper& CursorWrapper::operator=(const Reference< ::com::sun::star::sdbc::XRowSet>& _rxCursor)
//STRIP001 {
//STRIP001  m_xMoveOperations = Reference< ::com::sun::star::sdbc::XResultSet>(_rxCursor, UNO_QUERY);
//STRIP001  m_xBookmarkOperations = Reference< ::com::sun::star::sdbcx::XRowLocate>(_rxCursor, UNO_QUERY);
//STRIP001  m_xColumnsSupplier = Reference< ::com::sun::star::sdbcx::XColumnsSupplier>(_rxCursor, UNO_QUERY);
//STRIP001  if (!m_xMoveOperations.is() || !m_xBookmarkOperations.is() || !m_xColumnsSupplier.is())
//STRIP001  {   // all or nothing !!
//STRIP001      m_xMoveOperations = NULL;
//STRIP001      m_xBookmarkOperations = NULL;
//STRIP001      m_xColumnsSupplier = NULL;
//STRIP001  }
//STRIP001  return *this;
//STRIP001 }

//------------------------------------------------------------------------------
//STRIP001 FmXDisposeListener::~FmXDisposeListener()
//STRIP001 {
//STRIP001  setAdapter(NULL);
//STRIP001 }

//------------------------------------------------------------------------------
//STRIP001 void FmXDisposeListener::setAdapter(FmXDisposeMultiplexer* pAdapter)
//STRIP001 {
//STRIP001  if (m_pAdapter)
//STRIP001  {
//STRIP001      ::osl::MutexGuard aGuard(m_rMutex);
//STRIP001      m_pAdapter->release();
//STRIP001      m_pAdapter = NULL;
//STRIP001  }
//STRIP001
//STRIP001  if (pAdapter)
//STRIP001  {
//STRIP001      ::osl::MutexGuard aGuard(m_rMutex);
//STRIP001      m_pAdapter = pAdapter;
//STRIP001      m_pAdapter->acquire();
//STRIP001  }
//STRIP001 }

//==============================================================================
//STRIP001 DBG_NAME(FmXDisposeMultiplexer)
//------------------------------------------------------------------------------
//STRIP001 FmXDisposeMultiplexer::FmXDisposeMultiplexer(FmXDisposeListener* _pListener, const Reference< ::com::sun::star::lang::XComponent>& _rxObject, sal_Int16 _nId)
//STRIP001  :m_pListener(_pListener)
//STRIP001  ,m_xObject(_rxObject)
//STRIP001  ,m_nId(_nId)
//STRIP001 {
//STRIP001  DBG_CTOR(FmXDisposeMultiplexer, NULL);
//STRIP001  m_pListener->setAdapter(this);
//STRIP001
//STRIP001  if (m_xObject.is())
//STRIP001      m_xObject->addEventListener(this);
//STRIP001 }

//------------------------------------------------------------------------------
//STRIP001 FmXDisposeMultiplexer::~FmXDisposeMultiplexer()
//STRIP001 {
//STRIP001  DBG_DTOR(FmXDisposeMultiplexer, NULL);
//STRIP001 }

// ::com::sun::star::lang::XEventListener
//------------------------------------------------------------------
//STRIP001 void FmXDisposeMultiplexer::disposing(const ::com::sun::star::lang::EventObject& _Source) throw( RuntimeException )
//STRIP001 {
//STRIP001  Reference< ::com::sun::star::lang::XEventListener> xPreventDelete(this);
//STRIP001
//STRIP001  if (m_pListener)
//STRIP001  {
//STRIP001      m_pListener->disposing(_Source, m_nId);
//STRIP001      m_pListener->setAdapter(NULL);
//STRIP001      m_pListener = NULL;
//STRIP001  }
//STRIP001  m_xObject = NULL;
//STRIP001 }

//------------------------------------------------------------------
//STRIP001 void FmXDisposeMultiplexer::dispose()
//STRIP001 {
//STRIP001  if (m_xObject.is())
//STRIP001  {
//STRIP001      Reference< ::com::sun::star::lang::XEventListener> xPreventDelete(this);
//STRIP001
//STRIP001      m_xObject->removeEventListener(this);
//STRIP001      m_xObject = NULL;
//STRIP001
//STRIP001      m_pListener->setAdapter(NULL);
//STRIP001      m_pListener = NULL;
//STRIP001  }
//STRIP001 }

//==============================================================================
//------------------------------------------------------------------------------
//STRIP001 sal_Int16 getControlTypeByObject(const Reference< ::com::sun::star::lang::XServiceInfo>& _rxObject)
//STRIP001 {
//STRIP001  // ask for the persistent service name
//STRIP001  Reference< ::com::sun::star::io::XPersistObject> xPersistence(_rxObject, UNO_QUERY);
//STRIP001  DBG_ASSERT(xPersistence.is(), "::getControlTypeByObject : argument shold be an ::com::sun::star::io::XPersistObject !");
//STRIP001  if (!xPersistence.is())
//STRIP001      return OBJ_FM_CONTROL;
//STRIP001
//STRIP001  ::rtl::OUString sPersistentServiceName = xPersistence->getServiceName();
//STRIP001  if (sPersistentServiceName.equals(FM_COMPONENT_EDIT))   // 5.0-Name
//STRIP001  {
//STRIP001      // may be a simple edit field or a formatted field, dependent of the supported services
//STRIP001      if (_rxObject->supportsService(FM_SUN_COMPONENT_FORMATTEDFIELD))
//STRIP001          return OBJ_FM_FORMATTEDFIELD;
//STRIP001      return OBJ_FM_EDIT;
//STRIP001  }
//STRIP001  if (sPersistentServiceName.equals(FM_COMPONENT_TEXTFIELD))
//STRIP001      return OBJ_FM_EDIT;
//STRIP001  if (sPersistentServiceName.equals(FM_COMPONENT_COMMANDBUTTON))
//STRIP001      return OBJ_FM_BUTTON;
//STRIP001  if (sPersistentServiceName.equals(FM_COMPONENT_FIXEDTEXT))
//STRIP001      return OBJ_FM_FIXEDTEXT;
//STRIP001  if (sPersistentServiceName.equals(FM_COMPONENT_LISTBOX))
//STRIP001      return OBJ_FM_LISTBOX;
//STRIP001  if (sPersistentServiceName.equals(FM_COMPONENT_CHECKBOX))
//STRIP001      return OBJ_FM_CHECKBOX;
//STRIP001  if (sPersistentServiceName.equals(FM_COMPONENT_RADIOBUTTON))
//STRIP001      return OBJ_FM_RADIOBUTTON;
//STRIP001  if (sPersistentServiceName.equals(FM_COMPONENT_GROUPBOX))
//STRIP001      return OBJ_FM_GROUPBOX;
//STRIP001  if (sPersistentServiceName.equals(FM_COMPONENT_COMBOBOX))
//STRIP001      return OBJ_FM_COMBOBOX;
//STRIP001  if (sPersistentServiceName.equals(FM_COMPONENT_GRID))   // 5.0-Name
//STRIP001      return OBJ_FM_GRID;
//STRIP001  if (sPersistentServiceName.equals(FM_COMPONENT_GRIDCONTROL))
//STRIP001      return OBJ_FM_GRID;
//STRIP001  if (sPersistentServiceName.equals(FM_COMPONENT_IMAGEBUTTON))
//STRIP001      return OBJ_FM_IMAGEBUTTON;
//STRIP001  if (sPersistentServiceName.equals(FM_COMPONENT_FILECONTROL))
//STRIP001      return OBJ_FM_FILECONTROL;
//STRIP001  if (sPersistentServiceName.equals(FM_COMPONENT_DATEFIELD))
//STRIP001      return OBJ_FM_DATEFIELD;
//STRIP001  if (sPersistentServiceName.equals(FM_COMPONENT_TIMEFIELD))
//STRIP001      return OBJ_FM_TIMEFIELD;
//STRIP001  if (sPersistentServiceName.equals(FM_COMPONENT_NUMERICFIELD))
//STRIP001      return OBJ_FM_NUMERICFIELD;
//STRIP001  if (sPersistentServiceName.equals(FM_COMPONENT_CURRENCYFIELD))
//STRIP001      return OBJ_FM_CURRENCYFIELD;
//STRIP001  if (sPersistentServiceName.equals(FM_COMPONENT_PATTERNFIELD))
//STRIP001      return OBJ_FM_PATTERNFIELD;
//STRIP001  if (sPersistentServiceName.equals(FM_COMPONENT_HIDDEN)) // 5.0-Name
//STRIP001      return OBJ_FM_HIDDEN;
//STRIP001  if (sPersistentServiceName.equals(FM_COMPONENT_HIDDENCONTROL))
//STRIP001      return OBJ_FM_HIDDEN;
//STRIP001  if (sPersistentServiceName.equals(FM_COMPONENT_IMAGECONTROL))
//STRIP001      return OBJ_FM_IMAGECONTROL;
//STRIP001  if (sPersistentServiceName.equals(FM_COMPONENT_FORMATTEDFIELD))
//STRIP001  {
//STRIP001      DBG_ERROR("::getControlTypeByObject : suspicious persistent service name (formatted field) !");
//STRIP001          // objects with that service name should exist as they aren't compatible with older versions
//STRIP001      return OBJ_FM_FORMATTEDFIELD;
//STRIP001  }
//STRIP001
//STRIP001  DBG_ERROR("::getControlTypeByObject : unknown object type !");
//STRIP001  return OBJ_FM_CONTROL;
//STRIP001 }

//------------------------------------------------------------------------------
//STRIP001 ::rtl::OUString getServiceNameByControlType(sal_Int16 nType)
//STRIP001 {
//STRIP001  switch (nType)
//STRIP001  {
//STRIP001      case OBJ_FM_EDIT            : return FM_COMPONENT_TEXTFIELD;
//STRIP001      case OBJ_FM_BUTTON          : return FM_COMPONENT_COMMANDBUTTON;
//STRIP001      case OBJ_FM_FIXEDTEXT       : return FM_COMPONENT_FIXEDTEXT;
//STRIP001      case OBJ_FM_LISTBOX         : return FM_COMPONENT_LISTBOX;
//STRIP001      case OBJ_FM_CHECKBOX        : return FM_COMPONENT_CHECKBOX;
//STRIP001      case OBJ_FM_RADIOBUTTON     : return FM_COMPONENT_RADIOBUTTON;
//STRIP001      case OBJ_FM_GROUPBOX        : return FM_COMPONENT_GROUPBOX;
//STRIP001      case OBJ_FM_COMBOBOX        : return FM_COMPONENT_COMBOBOX;
//STRIP001      case OBJ_FM_GRID            : return FM_COMPONENT_GRIDCONTROL;
//STRIP001      case OBJ_FM_IMAGEBUTTON     : return FM_COMPONENT_IMAGEBUTTON;
//STRIP001      case OBJ_FM_FILECONTROL     : return FM_COMPONENT_FILECONTROL;
//STRIP001      case OBJ_FM_DATEFIELD       : return FM_COMPONENT_DATEFIELD;
//STRIP001      case OBJ_FM_TIMEFIELD       : return FM_COMPONENT_TIMEFIELD;
//STRIP001      case OBJ_FM_NUMERICFIELD    : return FM_COMPONENT_NUMERICFIELD;
//STRIP001      case OBJ_FM_CURRENCYFIELD   : return FM_COMPONENT_CURRENCYFIELD;
//STRIP001      case OBJ_FM_PATTERNFIELD    : return FM_COMPONENT_PATTERNFIELD;
//STRIP001      case OBJ_FM_HIDDEN          : return FM_COMPONENT_HIDDENCONTROL;
//STRIP001      case OBJ_FM_IMAGECONTROL    : return FM_COMPONENT_IMAGECONTROL;
//STRIP001      case OBJ_FM_FORMATTEDFIELD  : return FM_COMPONENT_FORMATTEDFIELD;
//STRIP001  }
//STRIP001  return ::rtl::OUString();
//STRIP001 }
//------------------------------------------------------------------------------
//STRIP001 Sequence< ::rtl::OUString> getEventMethods(const Type& type)
//STRIP001 {
//STRIP001  typelib_InterfaceTypeDescription *pType=0;
//STRIP001  type.getDescription( (typelib_TypeDescription**)&pType);
//STRIP001
//STRIP001  if(!pType)
//STRIP001      return Sequence< ::rtl::OUString>();
//STRIP001
//STRIP001  Sequence< ::rtl::OUString> aNames(pType->nMembers);
//STRIP001  ::rtl::OUString* pNames = aNames.getArray();
//STRIP001  for(sal_Int32 i=0;i<pType->nMembers;i++,++pNames)
//STRIP001  {
//STRIP001      // the decription reference
//STRIP001      typelib_TypeDescriptionReference* pMemberDescriptionReference = pType->ppMembers[i];
//STRIP001      // the description for the reference
//STRIP001      typelib_TypeDescription* pMemberDescription = NULL;
//STRIP001      typelib_typedescriptionreference_getDescription(&pMemberDescription, pMemberDescriptionReference);
//STRIP001      if (pMemberDescription)
//STRIP001      {
//STRIP001          typelib_InterfaceMemberTypeDescription* pRealMemberDescription =
//STRIP001              reinterpret_cast<typelib_InterfaceMemberTypeDescription*>(pMemberDescription);
//STRIP001          *pNames = pRealMemberDescription->pMemberName;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  typelib_typedescription_release( (typelib_TypeDescription *)pType );
//STRIP001  return aNames;
//STRIP001 }


//------------------------------------------------------------------------------
//STRIP001 void TransferEventScripts(const Reference< ::com::sun::star::awt::XControlModel>& xModel, const Reference< ::com::sun::star::awt::XControl>& xControl,
//STRIP001  const Sequence< ::com::sun::star::script::ScriptEventDescriptor>& rTransferIfAvailable)
//STRIP001 {
//STRIP001  // first check if we have a XEventAttacherManager for the model
//STRIP001  Reference< ::com::sun::star::container::XChild> xModelChild(xModel, UNO_QUERY);
//STRIP001  if (!xModelChild.is())
//STRIP001      return; // nothing to do
//STRIP001
//STRIP001  Reference< ::com::sun::star::script::XEventAttacherManager> xEventManager(xModelChild->getParent(), UNO_QUERY);
//STRIP001  if (!xEventManager.is())
//STRIP001      return; // nothing to do
//STRIP001
//STRIP001  if (!rTransferIfAvailable.getLength())
//STRIP001      return; // nothing to do
//STRIP001
//STRIP001  // check for the index of the model within it's parent
//STRIP001  Reference< ::com::sun::star::container::XIndexAccess> xParentIndex(xModelChild->getParent(), UNO_QUERY);
//STRIP001  if (!xParentIndex.is())
//STRIP001      return; // nothing to do
//STRIP001  sal_Int32 nIndex = getElementPos(xParentIndex, xModel);
//STRIP001  if (nIndex<0 || nIndex>=xParentIndex->getCount())
//STRIP001      return; // nothing to do
//STRIP001
//STRIP001  // then we need informations about the listeners supported by the control and the model
//STRIP001  Sequence< Type> aModelListeners;
//STRIP001  Sequence< Type> aControlListeners;
//STRIP001
//STRIP001  Reference< ::com::sun::star::beans::XIntrospection> xModelIntrospection(::legacy_binfilters::getLegacyProcessServiceFactory()->createInstance(::rtl::OUString::createFromAscii("com.sun.star.beans.Introspection")), UNO_QUERY);
//STRIP001  Reference< ::com::sun::star::beans::XIntrospection> xControlIntrospection(::legacy_binfilters::getLegacyProcessServiceFactory()->createInstance(::rtl::OUString::createFromAscii("com.sun.star.beans.Introspection")), UNO_QUERY);
//STRIP001
//STRIP001  if (xModelIntrospection.is() && xModel.is())
//STRIP001  {
//STRIP001      Any aModel(makeAny(xModel));
//STRIP001      aModelListeners = xModelIntrospection->inspect(aModel)->getSupportedListeners();
//STRIP001  }
//STRIP001
//STRIP001  if (xControlIntrospection.is() && xControl.is())
//STRIP001  {
//STRIP001      Any aControl(makeAny(xControl));
//STRIP001      aControlListeners = xControlIntrospection->inspect(aControl)->getSupportedListeners();
//STRIP001  }
//STRIP001
//STRIP001  sal_Int32 nMaxNewLen = aModelListeners.getLength() + aControlListeners.getLength();
//STRIP001  if (!nMaxNewLen)
//STRIP001      return; // the model and the listener don't support any listeners (or we were unable to retrieve these infos)
//STRIP001
//STRIP001  Sequence< ::com::sun::star::script::ScriptEventDescriptor>  aTransferable(nMaxNewLen);
//STRIP001  ::com::sun::star::script::ScriptEventDescriptor* pTransferable = aTransferable.getArray();
//STRIP001
//STRIP001  const ::com::sun::star::script::ScriptEventDescriptor* pCurrent = rTransferIfAvailable.getConstArray();
//STRIP001  sal_Int32 i,j,k;
//STRIP001  for (i=0; i<rTransferIfAvailable.getLength(); ++i, ++pCurrent)
//STRIP001  {
//STRIP001      // search the model/control idl classes for the event described by pCurrent
//STRIP001      for (   Sequence< Type>* pCurrentArray = &aModelListeners;
//STRIP001              pCurrentArray;
//STRIP001              pCurrentArray = (pCurrentArray == &aModelListeners) ? &aControlListeners : NULL
//STRIP001          )
//STRIP001      {
//STRIP001          const Type* pCurrentListeners = pCurrentArray->getConstArray();
//STRIP001          for (j=0; j<pCurrentArray->getLength(); ++j, ++pCurrentListeners)
//STRIP001          {
//STRIP001              UniString aListener = (*pCurrentListeners).getTypeName();
//STRIP001              sal_Int32 nTokens = aListener.GetTokenCount('.');
//STRIP001              if (nTokens)
//STRIP001                  aListener = aListener.GetToken(nTokens - 1, '.');
//STRIP001
//STRIP001              if (aListener == pCurrent->ListenerType.getStr())
//STRIP001                  // the current ::com::sun::star::script::ScriptEventDescriptor doesn't match the current listeners class
//STRIP001                  continue;
//STRIP001
//STRIP001              // now check the methods
//STRIP001              Sequence< ::rtl::OUString> aMethodsNames = getEventMethods(*pCurrentListeners);
//STRIP001              const ::rtl::OUString* pMethodsNames = aMethodsNames.getConstArray();
//STRIP001              for (k=0; k<aMethodsNames.getLength(); ++k, ++pMethodsNames)
//STRIP001              {
//STRIP001                  if ((*pMethodsNames).compareTo(pCurrent->EventMethod) != COMPARE_EQUAL)
//STRIP001                      // the current ::com::sun::star::script::ScriptEventDescriptor doesn't match the current listeners current method
//STRIP001                      continue;
//STRIP001
//STRIP001                  // we can transfer the script event : the model (control) supports it
//STRIP001                  *pTransferable = *pCurrent;
//STRIP001                  ++pTransferable;
//STRIP001                  break;
//STRIP001              }
//STRIP001              if (k<aMethodsNames.getLength())
//STRIP001                  break;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  sal_Int32 nRealNewLen = pTransferable - aTransferable.getArray();
//STRIP001  aTransferable.realloc(nRealNewLen);
//STRIP001
//STRIP001  xEventManager->registerScriptEvents(nIndex, aTransferable);
//STRIP001 }

//------------------------------------------------------------------------------
//STRIP001 sal_Int16    GridView2ModelPos(const Reference< ::com::sun::star::container::XIndexAccess>& rColumns, sal_Int16 nViewPos)
//STRIP001 {
//STRIP001  try
//STRIP001  {
//STRIP001      if (rColumns.is())
//STRIP001      {
//STRIP001          // loop through all columns
//STRIP001          sal_Int16 i;
//STRIP001          Reference< ::com::sun::star::beans::XPropertySet> xCur;
//STRIP001          for (i=0; i<rColumns->getCount(); ++i)
//STRIP001          {
//STRIP001              rColumns->getByIndex(i) >>= xCur;
//STRIP001              if (!::comphelper::getBOOL(xCur->getPropertyValue(FM_PROP_HIDDEN)))
//STRIP001                  // for every visible col : if nViewPos is greater zero, decrement it, else we
//STRIP001                  // have found the model position
//STRIP001                  if (!nViewPos)
//STRIP001                      break;
//STRIP001                  else
//STRIP001                      --nViewPos;
//STRIP001          }
//STRIP001          if (i<rColumns->getCount())
//STRIP001              return i;
//STRIP001      }
//STRIP001  }
//STRIP001  catch(const Exception&)
//STRIP001  {
//STRIP001      DBG_ERROR("GridView2ModelPos Exception occured!");
//STRIP001  }
//STRIP001  return (sal_Int16)-1;
//STRIP001 }

//==============================================================================
// FmSlotDispatch - some kind of translator between the Sfx-Slots and the UNO-dispatchers
//==============================================================================

//  SMART_UNO_IMPLEMENTATION(FmSlotDispatch, UsrObject);


//STRIP001 DBG_NAME(FmSlotDispatch)
//------------------------------------------------------------------------------
//STRIP001 FmSlotDispatch::FmSlotDispatch(const  URL& rUrl, sal_Int16 nSlotId, SfxBindings& rBindings)
//STRIP001  :SfxControllerItem(nSlotId, rBindings)
//STRIP001  ,m_aDisposeListeners(m_aAccessSafety)
//STRIP001  ,m_aStatusListeners(m_aAccessSafety)
//STRIP001  ,m_aUrl(rUrl)
//STRIP001  ,m_nSlot(nSlotId)
//STRIP001 {
//STRIP001  DBG_CTOR(FmSlotDispatch,NULL);
//STRIP001
//STRIP001 }

//------------------------------------------------------------------------------
//STRIP001 FmSlotDispatch::~FmSlotDispatch()
//STRIP001 {
//STRIP001
//STRIP001  DBG_DTOR(FmSlotDispatch,NULL);
//STRIP001 }

//------------------------------------------------------------------------------
//STRIP001 void FmSlotDispatch::BroadcastCurrentState( )
//STRIP001 {
//STRIP001  SfxPoolItem* pCurrentState = NULL;
//STRIP001  SfxItemState eCurrentState = GetBindings().QueryState( m_nSlot, pCurrentState );
//STRIP001  NotifyState( eCurrentState, pCurrentState );
//STRIP001  delete pCurrentState;
//STRIP001 }

//------------------------------------------------------------------------------
//STRIP001 void FmSlotDispatch::dispatch(const  URL& aURL, const Sequence< ::com::sun::star::beans::PropertyValue>& aArgs) throw( RuntimeException )
//STRIP001 {
//STRIP001  DBG_ASSERT(aURL.Main.compareTo(m_aUrl.Main) == COMPARE_EQUAL, "FmSlotDispatch::dispatch : invalid argument !");
//STRIP001  DBG_ASSERT(m_aExecutor.IsSet(), "FmSlotDispatch::dispatch : no executor !");
//STRIP001  // if we have no executor we would have disabled this feature in statusChanged-calls
//STRIP001
//STRIP001  m_aExecutor.Call(this);
//STRIP001 }

//------------------------------------------------------------------------------
//STRIP001 void FmSlotDispatch::NotifyState(SfxItemState eState, const SfxPoolItem* pState, const Reference< ::com::sun::star::frame::XStatusListener>& rListener)
//STRIP001 {
//STRIP001  ::com::sun::star::frame::FeatureStateEvent aEvent = BuildEvent(eState, pState);
//STRIP001
//STRIP001  if (rListener.is())
//STRIP001      rListener->statusChanged(aEvent);
//STRIP001  else
//STRIP001      NOTIFY_LISTENERS(m_aStatusListeners, ::com::sun::star::frame::XStatusListener, statusChanged, aEvent);
//STRIP001 }

//------------------------------------------------------------------------------
//STRIP001 void SAL_CALL FmSlotDispatch::addStatusListener( const Reference< ::com::sun::star::frame::XStatusListener >& xControl, const URL& aURL ) throw(RuntimeException)
//STRIP001 {
//STRIP001  DBG_ASSERT((aURL.Main.getLength() == 0) || (aURL.Main.compareTo(m_aUrl.Main) == COMPARE_EQUAL),
//STRIP001      "FmSlotDispatch::addStatusListener: invalid argument !");
//STRIP001  m_aStatusListeners.addInterface( xControl );
//STRIP001
//STRIP001  // acknowledge the initial status
//STRIP001  SfxPoolItem* pState = NULL;
//STRIP001  SfxItemState eInitialState = GetBindings().QueryState(m_nSlot, pState);
//STRIP001
//STRIP001  NotifyState(eInitialState, pState, xControl);
//STRIP001 }

//------------------------------------------------------------------------------
//STRIP001 void SAL_CALL FmSlotDispatch::removeStatusListener( const Reference< ::com::sun::star::frame::XStatusListener >& xControl, const URL& aURL ) throw(RuntimeException)
//STRIP001 {
//STRIP001  DBG_ASSERT((aURL.Main.getLength() == 0) || (aURL.Main.compareTo(m_aUrl.Main) == COMPARE_EQUAL),
//STRIP001      "FmSlotDispatch::removeStatusListener: invalid argument !");
//STRIP001  m_aStatusListeners.removeInterface( xControl );
//STRIP001 }

//------------------------------------------------------------------------------
//STRIP001 void SAL_CALL FmSlotDispatch::dispose(   ) throw(RuntimeException)
//STRIP001 {
//STRIP001     Reference< XInterface > xXInterface((*this));
//STRIP001  ::com::sun::star::lang::EventObject aEvt(xXInterface);
//STRIP001  m_aDisposeListeners.disposeAndClear(aEvt);
//STRIP001  m_aStatusListeners.disposeAndClear(aEvt);
//STRIP001 }

//------------------------------------------------------------------------------
//STRIP001 void SAL_CALL FmSlotDispatch::addEventListener( const Reference< ::com::sun::star::lang::XEventListener >& xListener ) throw(RuntimeException)
//STRIP001 {
//STRIP001  m_aDisposeListeners.addInterface( xListener );
//STRIP001 }

//------------------------------------------------------------------------------
//STRIP001 void SAL_CALL FmSlotDispatch::removeEventListener( const Reference< ::com::sun::star::lang::XEventListener >& aListener ) throw(RuntimeException)
//STRIP001 {
//STRIP001  m_aDisposeListeners.removeInterface( aListener );
//STRIP001 }

//------------------------------------------------------------------------------
//STRIP001 void FmSlotDispatch::StateChanged(USHORT _nSID, SfxItemState _eState, const SfxPoolItem* _pState)
//STRIP001 {
//STRIP001  DBG_ASSERT(_nSID == m_nSlot, "FmSlotDispatch::StateChanged : where did this come from ?");
//STRIP001
//STRIP001  ::com::sun::star::frame::FeatureStateEvent eEvent = BuildEvent(_eState, _pState);
//STRIP001  NOTIFY_LISTENERS(m_aStatusListeners, ::com::sun::star::frame::XStatusListener, statusChanged, eEvent);
//STRIP001 }

//------------------------------------------------------------------------------
//STRIP001 ::com::sun::star::frame::FeatureStateEvent FmSlotDispatch::BuildEvent(SfxItemState eState, const SfxPoolItem* pState)
//STRIP001 {
//STRIP001  ::com::sun::star::frame::FeatureStateEvent aReturn;
//STRIP001  aReturn.Source = static_cast< ::cppu::OWeakObject* >( this );
//STRIP001  aReturn.FeatureURL = m_aUrl;
//STRIP001  aReturn.IsEnabled = (SFX_ITEM_DISABLED != eState) && m_aExecutor.IsSet();
//STRIP001  aReturn.Requery = sal_False;
//STRIP001
//STRIP001  if (pState)
//STRIP001  {
//STRIP001      if (pState->ISA(SfxBoolItem))
//STRIP001          aReturn.State <<= ((SfxBoolItem*)pState)->GetValue();
//STRIP001      else if (pState->ISA(SfxStringItem))
//STRIP001          aReturn.State <<= ::rtl::OUString(((SfxStringItem*)pState)->GetValue());
//STRIP001 #if DBG_UTIL
//STRIP001      else if (!pState->ISA(SfxVoidItem))
//STRIP001          DBG_ERROR("FmSlotDispatch::BuildEvent : don't know what to do with the ItemState !");
//STRIP001 #endif
//STRIP001  }
//STRIP001
//STRIP001  return aReturn;
//STRIP001 }

//========================================================================
//= FmXDispatchInterceptorImpl
//========================================================================

/*N*/ DBG_NAME(FmXDispatchInterceptorImpl)
//------------------------------------------------------------------------
/*N*/ FmXDispatchInterceptorImpl::FmXDispatchInterceptorImpl(
/*N*/           const Reference< XDispatchProviderInterception >& _rxToIntercept, FmDispatchInterceptor* _pMaster,
/*N*/           sal_Int16 _nId, Sequence< ::rtl::OUString > _rInterceptedSchemes)
/*N*/   :FmXDispatchInterceptorImpl_BASE(_pMaster && _pMaster->getInterceptorMutex() ? *_pMaster->getInterceptorMutex() : m_aFallback)
/*N*/   ,m_xIntercepted(_rxToIntercept)
/*N*/   ,m_pMaster(_pMaster)
/*N*/   ,m_nId(_nId)
/*N*/   ,m_aInterceptedURLSchemes(_rInterceptedSchemes)
/*N*/   ,m_bListening(sal_False)
/*N*/ {
/*N*/   DBG_CTOR(FmXDispatchInterceptorImpl,NULL);
/*N*/
/*N*/   ::osl::MutexGuard aGuard(getAccessSafety());
/*N*/   ::comphelper::increment(m_refCount);
/*N*/   if (_rxToIntercept.is())
/*N*/   {
/*N*/       _rxToIntercept->registerDispatchProviderInterceptor((::com::sun::star::frame::XDispatchProviderInterceptor*)this);
/*N*/       // this should make us the top-level dispatch-provider for the component, via a call to our
/*N*/       // setDispatchProvider we should have got an fallback for requests we (i.e. our master) cannot fullfill
/*N*/       Reference< ::com::sun::star::lang::XComponent> xInterceptedComponent(_rxToIntercept, UNO_QUERY);
/*N*/       if (xInterceptedComponent.is())
/*N*/       {
/*N*/           xInterceptedComponent->addEventListener(this);
/*N*/           m_bListening = sal_True;
/*N*/       }
/*N*/   }
/*N*/   ::comphelper::decrement(m_refCount);
/*N*/ }

//------------------------------------------------------------------------
/*N*/ FmXDispatchInterceptorImpl::~FmXDispatchInterceptorImpl()
/*N*/ {
/*N*/   if (!rBHelper.bDisposed)
/*?*/       dispose();
/*N*/
/*N*/   DBG_DTOR(FmXDispatchInterceptorImpl,NULL);
/*N*/ }

//------------------------------------------------------------------------------
/*N*/ Sequence< sal_Int8 > SAL_CALL FmXDispatchInterceptorImpl::getImplementationId() throw(RuntimeException)
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); Sequence< sal_Int8 > a; return a;//STRIP001
//STRIP001  return ::binfilter::form::OImplementationIds::getImplementationId(getTypes());//STRIP008 return ::form::OImplementationIds::getImplementationId(getTypes());
/*N*/ }
//------------------------------------------------------------------------------
/*N*/ Reference< ::com::sun::star::frame::XDispatch > SAL_CALL FmXDispatchInterceptorImpl::queryDispatch( const URL& aURL, const ::rtl::OUString& aTargetFrameName, sal_Int32 nSearchFlags ) throw(RuntimeException)
/*N*/ {
/*N*/   ::osl::MutexGuard aGuard(getAccessSafety());
/*N*/   Reference< ::com::sun::star::frame::XDispatch> xResult;
/*N*/   // ask our 'real' interceptor
/*N*/   if (m_pMaster)
/*N*/       xResult = m_pMaster->interceptedQueryDispatch(m_nId, aURL, aTargetFrameName, nSearchFlags);
/*N*/
/*N*/   // ask our slave provider
/*N*/   if (!xResult.is() && m_xSlaveDispatcher.is())
/*N*/       xResult = m_xSlaveDispatcher->queryDispatch(aURL, aTargetFrameName, nSearchFlags);
/*N*/
/*N*/   return xResult;
/*N*/ }

//------------------------------------------------------------------------------
/*?*/ Sequence< Reference< ::com::sun::star::frame::XDispatch > > SAL_CALL
/*?*/ FmXDispatchInterceptorImpl::queryDispatches( const Sequence< ::com::sun::star::frame::DispatchDescriptor >& aDescripts ) throw(RuntimeException)
/*?*/ {
/*?*/ DBG_BF_ASSERT(0, "STRIP"); Sequence< Reference< ::com::sun::star::frame::XDispatch> > aReturn(aDescripts.getLength()); return aReturn;//STRIP001  ::osl::MutexGuard aGuard(getAccessSafety());
//STRIP001  Sequence< Reference< ::com::sun::star::frame::XDispatch> > aReturn(aDescripts.getLength());
//STRIP001  Reference< ::com::sun::star::frame::XDispatch>* pReturn = aReturn.getArray();
//STRIP001  const ::com::sun::star::frame::DispatchDescriptor* pDescripts = aDescripts.getConstArray();
//STRIP001  for (sal_Int16 i=0; i<aDescripts.getLength(); ++i, ++pReturn, ++pDescripts)
//STRIP001  {
//STRIP001      *pReturn = queryDispatch(pDescripts->FeatureURL, pDescripts->FrameName, pDescripts->SearchFlags);
//STRIP001  }
//STRIP001  return aReturn;
/*?*/ }

//------------------------------------------------------------------------------
/*N*/ Reference< ::com::sun::star::frame::XDispatchProvider > SAL_CALL FmXDispatchInterceptorImpl::getSlaveDispatchProvider(    ) throw(RuntimeException)
/*N*/ {
/*N*/   ::osl::MutexGuard aGuard(getAccessSafety());
/*N*/   return m_xSlaveDispatcher;
/*N*/ }

//------------------------------------------------------------------------------
/*N*/ void SAL_CALL FmXDispatchInterceptorImpl::setSlaveDispatchProvider(const Reference< ::com::sun::star::frame::XDispatchProvider>& xNewDispatchProvider) throw( RuntimeException )
/*N*/ {
/*N*/   ::osl::MutexGuard aGuard(getAccessSafety());
/*N*/   m_xSlaveDispatcher = xNewDispatchProvider;
/*N*/ }

//------------------------------------------------------------------------------
/*N*/ Reference< ::com::sun::star::frame::XDispatchProvider> SAL_CALL FmXDispatchInterceptorImpl::getMasterDispatchProvider(void) throw( RuntimeException )
/*N*/ {
/*N*/   ::osl::MutexGuard aGuard(getAccessSafety());
/*N*/   return m_xMasterDispatcher;
/*N*/ }

//------------------------------------------------------------------------------
/*N*/ void SAL_CALL FmXDispatchInterceptorImpl::setMasterDispatchProvider(const Reference< ::com::sun::star::frame::XDispatchProvider>& xNewSupplier) throw( RuntimeException )
/*N*/ {
/*N*/   ::osl::MutexGuard aGuard(getAccessSafety());
/*N*/   m_xMasterDispatcher = xNewSupplier;
/*N*/ }

//------------------------------------------------------------------------------
/*N*/ Sequence< ::rtl::OUString > SAL_CALL FmXDispatchInterceptorImpl::getInterceptedURLs(  ) throw(RuntimeException)
/*N*/ {
/*N*/   return m_aInterceptedURLSchemes;
/*N*/ }

//------------------------------------------------------------------------------
/*?*/ void SAL_CALL FmXDispatchInterceptorImpl::disposing(const ::com::sun::star::lang::EventObject& Source) throw( ::com::sun::star::uno::RuntimeException )
/*?*/ {
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001   if (m_bListening)
//STRIP001  {
//STRIP001      Reference< XDispatchProviderInterception > xIntercepted(m_xIntercepted.get(), UNO_QUERY);
//STRIP001      if (Source.Source == xIntercepted)
//STRIP001          ImplDetach();
//STRIP001  }
/*?*/ }

//------------------------------------------------------------------------------
/*N*/ void FmXDispatchInterceptorImpl::ImplDetach()
/*N*/ {
/*N*/   ::osl::MutexGuard aGuard(getAccessSafety());
/*N*/   OSL_ENSURE(m_bListening, "FmXDispatchInterceptorImpl::ImplDetach: invalid call!");
/*N*/
/*N*/   // deregister ourself from the interception component
/*N*/   Reference< XDispatchProviderInterception > xIntercepted(m_xIntercepted.get(), UNO_QUERY);
/*N*/   if (xIntercepted.is())
/*N*/       xIntercepted->releaseDispatchProviderInterceptor(static_cast<XDispatchProviderInterceptor*>(this));
/*N*/
/*N*/ //    m_xIntercepted = Reference< XDispatchProviderInterception >();
/*N*/       // Don't reset m_xIntercepted: It may be needed by our owner to check for which object we were
/*N*/       // responsible. As we hold the object with a weak reference only, this should be no problem.
/*N*/       // 88936 - 23.07.2001 - frank.schoenheit@sun.com
/*N*/   m_pMaster = NULL;
/*N*/   m_bListening = sal_False;
/*N*/ }

//------------------------------------------------------------------------------
/*N*/ void FmXDispatchInterceptorImpl::disposing()
/*N*/ {
/*N*/   // remove ourself as event listener from the interception component
/*N*/   if (m_bListening)
/*N*/   {
/*N*/       Reference< ::com::sun::star::lang::XComponent> xInterceptedComponent(m_xIntercepted.get(), UNO_QUERY);
/*N*/       if (xInterceptedComponent.is())
/*N*/           xInterceptedComponent->removeEventListener(static_cast<XEventListener*>(this));
/*N*/
/*N*/       // detach from the interception component
/*N*/       ImplDetach();
/*N*/   }
/*N*/ }

//==============================================================================
//==============================================================================

//------------------------------------------------------------------------------
//STRIP001 sal_Bool isLoadable(const Reference< XInterface >& xLoad)
//STRIP001 {
//STRIP001  // determines whether a form should be loaded or not
//STRIP001  // if there is no datasource or connection there is no reason to load a form
//STRIP001  Reference< ::com::sun::star::beans::XPropertySet> xSet(xLoad, UNO_QUERY);
//STRIP001  if (xSet.is())
//STRIP001  {
//STRIP001      try
//STRIP001      {
//STRIP001          // is there already a active connection
//STRIP001          Reference< XInterface > xConn;
//STRIP001          xSet->getPropertyValue(FM_PROP_ACTIVE_CONNECTION) >>= xConn;
//STRIP001          return (xConn.is() ||
//STRIP001                  ::comphelper::getString(xSet->getPropertyValue(FM_PROP_DATASOURCE)).getLength() ||
//STRIP001                  ::comphelper::getString(xSet->getPropertyValue(FM_PROP_URL)).getLength());
//STRIP001      }
//STRIP001      catch(Exception&)
//STRIP001      {
//STRIP001          DBG_ERROR("isLoadable Exception occured!");
//STRIP001      }
//STRIP001
//STRIP001  }
//STRIP001  return sal_False;
//STRIP001 }

//------------------------------------------------------------------------------
//STRIP001 void setConnection(const Reference< ::com::sun::star::sdbc::XRowSet>& _rxRowSet, const Reference< ::com::sun::star::sdbc::XConnection>& _rxConn)
//STRIP001 {
//STRIP001  Reference< ::com::sun::star::beans::XPropertySet> xRowSetProps(_rxRowSet, UNO_QUERY);
//STRIP001  if (xRowSetProps.is())
//STRIP001  {
//STRIP001      try
//STRIP001      {
//STRIP001          Any aConn(makeAny(_rxConn));
//STRIP001          xRowSetProps->setPropertyValue(FM_PROP_ACTIVE_CONNECTION, aConn);
//STRIP001      }
//STRIP001      catch(Exception&)
//STRIP001      {
//STRIP001          DBG_ERROR("::setConnection : could not set the connection !");
//STRIP001      }
//STRIP001
//STRIP001  }
//STRIP001 }
//------------------------------------------------------------------------------
//STRIP001 sal_Bool isRowSetAlive(const Reference< XInterface >& _rxRowSet)
//STRIP001 {
//STRIP001  sal_Bool bIsAlive = sal_False;
//STRIP001  Reference< ::com::sun::star::sdbcx::XColumnsSupplier> xSupplyCols(_rxRowSet, UNO_QUERY);
//STRIP001  Reference< ::com::sun::star::container::XIndexAccess> xCols;
//STRIP001  if (xSupplyCols.is())
//STRIP001      xCols = Reference< ::com::sun::star::container::XIndexAccess>(xSupplyCols->getColumns(), UNO_QUERY);
//STRIP001  if (xCols.is() && (xCols->getCount() > 0))
//STRIP001      bIsAlive = sal_True;
//STRIP001
//STRIP001  return bIsAlive;
//STRIP001 }
}
