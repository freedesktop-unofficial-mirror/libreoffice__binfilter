/*************************************************************************
 *
 *  $RCSfile: svx_fmpgeimp.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: aw $ $Date: 2003-11-18 19:23:58 $
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

#define _EXTERN_FORMLAYER_


#ifndef _SVXERR_HXX
#include "svxerr.hxx"
#endif

#ifndef _SVX_FMUNOPGE_HXX
#include "fmpgeimp.hxx"
#endif

#ifndef _COM_SUN_STAR_SDB_COMMANDTYPE_HPP_
#include <com/sun/star/sdb/CommandType.hpp>
#endif

#ifndef _COM_SUN_STAR_IO_XOBJECTINPUTSTREAM_HPP_
#include <com/sun/star/io/XObjectInputStream.hpp>
#endif
#ifndef _COM_SUN_STAR_IO_XPERSISTOBJECT_HPP_
#include <com/sun/star/io/XPersistObject.hpp>
#endif
#ifndef _COM_SUN_STAR_IO_XOBJECTOUTPUTSTREAM_HPP_
#include <com/sun/star/io/XObjectOutputStream.hpp>
#endif
#ifndef _COM_SUN_STAR_IO_XACTIVEDATASINK_HPP_
#include <com/sun/star/io/XActiveDataSink.hpp>
#endif
#ifndef _COM_SUN_STAR_IO_XACTIVEDATASOURCE_HPP_
#include <com/sun/star/io/XActiveDataSource.hpp>
#endif
#ifndef _COM_SUN_STAR_IO_XMARKABLESTREAM_HPP_
#include <com/sun/star/io/XMarkableStream.hpp>
#endif

#ifndef _SFX_OBJSH_HXX
#include <bf_sfx2/objsh.hxx>
#endif

#ifndef _SVX_FMUNDO_HXX
#include "fmundo.hxx"
#endif
#ifndef _SVX_FMTOOLS_HXX
#include "fmtools.hxx"
#endif
#ifndef _SVX_FMPROP_HRC
#include "fmprop.hrc"
#endif
#ifndef _SVX_FMGLOB_HXX
#include "fmglob.hxx"
#endif
#ifndef _SVX_FMSERVS_HXX
#include "fmservs.hxx"
#endif

//  #include "fmstream.hxx"
#ifndef _SVX_FMOBJ_HXX
#include "fmobj.hxx"
#endif
#ifndef _SVX_FMPAGE_HXX
#include "fmpage.hxx"
#endif
#ifndef _SVX_FMMODEL_HXX
#include "fmmodel.hxx"
#endif

#ifndef _TOOLS_RESID_HXX //autogen
#include <tools/resid.hxx>
#endif

#ifndef _SVDITER_HXX //autogen
#include "svditer.hxx"
#endif

#ifndef _SVX_FMRESIDS_HRC
#include "fmresids.hrc"
#endif

#ifndef _SHL_HXX
#include <tools/shl.hxx>
#endif
#ifndef _VCL_STDTEXT_HXX
#include <vcl/stdtext.hxx>
#endif

#ifndef _SVX_DIALMGR_HXX
#include "dialmgr.hxx"
#endif

#ifndef _COMPHELPER_PROCESSFACTORY_HXX_
#include <comphelper/processfactory.hxx>
#endif
#ifndef _COMPHELPER_UNO3_HXX_
#include <comphelper/uno3.hxx>
#endif
#ifndef _COMPHELPER_TYPES_HXX_
#include <comphelper/types.hxx>
#endif
#ifndef _UTL_STREAM_WRAPPER_HXX_
#include <unotools/streamwrap.hxx>
#endif
#ifndef SVX_DBTOOLSCLIENT_HXX
#include "dbtoolsclient.hxx"
#endif
#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif
namespace binfilter {

using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::sdbc;
using namespace ::com::sun::star::sdb;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::form;
using namespace ::binfilter::svxform;//STRIP008 using namespace ::svxform;

/*N*/ DBG_NAME(FmFormPageImpl)
//------------------------------------------------------------------------------
/*N*/ FmFormPageImpl::FmFormPageImpl(FmFormPage* _pPage)
/*N*/                :pPage(_pPage)
/*N*/              ,m_bFirstActivation( sal_True )
/*N*/ {
/*N*/     DBG_CTOR(FmFormPageImpl,NULL);
/*N*/     Init();
/*N*/ }

//------------------------------------------------------------------------------
//STRIP001 FmFormPageImpl::FmFormPageImpl(FmFormPage* _pPage, const FmFormPageImpl& rImpl)
//STRIP001                :pPage(_pPage)
//STRIP001             ,m_bFirstActivation( sal_True )
//STRIP001 {
//STRIP001     DBG_CTOR(FmFormPageImpl,NULL);
//STRIP001     Init();
//STRIP001
//STRIP001     // copy it by streaming
//STRIP001     // creating a pipe
//STRIP001     Reference< ::com::sun::star::io::XOutputStream >  xOutPipe(::legacy_binfilters::getLegacyProcessServiceFactory()->createInstance(::rtl::OUString::createFromAscii("com.sun.star.io.Pipe")), UNO_QUERY);
//STRIP001     Reference< ::com::sun::star::io::XInputStream >  xInPipe(xOutPipe, UNO_QUERY);
//STRIP001
//STRIP001     // creating the mark streams
//STRIP001     Reference< ::com::sun::star::io::XInputStream >  xMarkIn(::legacy_binfilters::getLegacyProcessServiceFactory()->createInstance(::rtl::OUString::createFromAscii("com.sun.star.io.MarkableInputStream")), UNO_QUERY);
//STRIP001     Reference< ::com::sun::star::io::XActiveDataSink >  xMarkSink(xMarkIn, UNO_QUERY);
//STRIP001
//STRIP001     Reference< ::com::sun::star::io::XOutputStream >  xMarkOut(::legacy_binfilters::getLegacyProcessServiceFactory()->createInstance(::rtl::OUString::createFromAscii("com.sun.star.io.MarkableOutputStream")), UNO_QUERY);
//STRIP001     Reference< ::com::sun::star::io::XActiveDataSource >  xMarkSource(xMarkOut, UNO_QUERY);
//STRIP001
//STRIP001     // connect pipe and sink
//STRIP001     Reference< ::com::sun::star::io::XActiveDataSink >  xSink(::legacy_binfilters::getLegacyProcessServiceFactory()->createInstance(::rtl::OUString::createFromAscii("com.sun.star.io.ObjectInputStream")), UNO_QUERY);
//STRIP001
//STRIP001     // connect pipe and source
//STRIP001     Reference< ::com::sun::star::io::XActiveDataSource >  xSource(::legacy_binfilters::getLegacyProcessServiceFactory()->createInstance(::rtl::OUString::createFromAscii("com.sun.star.io.ObjectOutputStream")), UNO_QUERY);
//STRIP001
//STRIP001     Reference< ::com::sun::star::io::XObjectOutputStream >  xOutStrm(xSource, UNO_QUERY);
//STRIP001     Reference< ::com::sun::star::io::XObjectInputStream >  xInStrm(xSink, UNO_QUERY);
//STRIP001
//STRIP001     if (xMarkSink.is() && xMarkSource.is() && xSink.is() && xSource.is() && xOutStrm.is() && xInStrm.is())
//STRIP001     {
//STRIP001         xMarkSink->setInputStream(xInPipe);
//STRIP001         xMarkSource->setOutputStream(xOutPipe);
//STRIP001         xSink->setInputStream(xMarkIn);
//STRIP001         xSource->setOutputStream(xMarkOut);
//STRIP001
//STRIP001         // write the objects to source
//STRIP001         rImpl.write(xOutStrm);
//STRIP001         xOutStrm->closeOutput();
//STRIP001
//STRIP001         // read them
//STRIP001         read(xInStrm);
//STRIP001         xInStrm->closeInput();
//STRIP001     }
//STRIP001     //  what to do else ?
//STRIP001 }

//------------------------------------------------------------------------------
/*N*/ void FmFormPageImpl::Init()
/*N*/ {
/*N*/     if (pPage)
/*N*/     {
/*N*/         FmFormModel* pDrawModel = (FmFormModel*)pPage->GetModel();
/*N*/         SfxObjectShell* pObjShell = pDrawModel->GetObjectShell();
/*N*/         if( pObjShell )
/*N*/             xModel = pObjShell->GetModel();
/*N*/
/*N*/         // get a unique page id from the model
/*N*/         m_sPageId = pDrawModel->GetUniquePageId();
/*N*/     }
/*N*/
/*N*/     static const ::rtl::OUString sFormsCollectionServiceName = ::rtl::OUString::createFromAscii("com.sun.star.form.Forms");
/*N*/     xForms = Reference< ::com::sun::star::container::XNameContainer > (
/*N*/         ::legacy_binfilters::getLegacyProcessServiceFactory()->createInstance(
/*N*/         sFormsCollectionServiceName), ::com::sun::star::uno::UNO_QUERY);
/*N*/     DBG_ASSERT(xForms.is(), "FmFormPageImpl::Init : could not create a forms collection !");
/*N*/     if (!xForms.is())
/*?*/         ShowServiceNotAvailableError(NULL, sFormsCollectionServiceName, sal_True);
/*N*/
/*N*/     Reference< ::com::sun::star::container::XChild >  xAsChild(xForms, UNO_QUERY);
/*N*/     if (xAsChild.is())
/*N*/         xAsChild->setParent( xModel );
/*N*/ }

//------------------------------------------------------------------------------
/*N*/ FmFormPageImpl::~FmFormPageImpl()
/*N*/ {
/*N*/     xCurrentForm = NULL;
/*N*/
/*N*/     ::comphelper::disposeComponent(xForms);
/*N*/     DBG_DTOR(FmFormPageImpl,NULL);
/*N*/ }

//------------------------------------------------------------------------------
//STRIP001 void FmFormPageImpl::setCurForm(Reference< ::com::sun::star::form::XForm >  xForm)
//STRIP001 {
//STRIP001     xCurrentForm = xForm;
//STRIP001 }

//------------------------------------------------------------------------------
//STRIP001 Reference< ::com::sun::star::form::XForm >  FmFormPageImpl::getDefaultForm()
//STRIP001 {
//STRIP001     Reference< ::com::sun::star::form::XForm >  xForm;
//STRIP001
//STRIP001  try
//STRIP001  {
//STRIP001      // wenn noch kein TargetForm gefunden, dann aktuelle oder Default
//STRIP001      if (!xCurrentForm.is())
//STRIP001      {
//STRIP001          if (xForms->hasElements())
//STRIP001          {
//STRIP001              // suche die Standardform
//STRIP001              ::rtl::OUString ustrStdFormName = ::rtl::OUString(SVX_RES(RID_STR_STDFORMNAME));
//STRIP001
//STRIP001              if (xForms->hasByName(ustrStdFormName))
//STRIP001              {
//STRIP001                  try
//STRIP001                  {
//STRIP001                      xForms->getByName(ustrStdFormName) >>= xForm;
//STRIP001                  }
//STRIP001                  catch(::com::sun::star::container::NoSuchElementException &)
//STRIP001                  {
//STRIP001                      DBG_ERROR("NoSuchElementException occured!");
//STRIP001                  }
//STRIP001                  catch(::com::sun::star::lang::WrappedTargetException &)
//STRIP001                  {
//STRIP001                      DBG_ERROR("WrappedTargetException occured!");
//STRIP001                  }
//STRIP001
//STRIP001              }
//STRIP001
//STRIP001              // gibt es denn ueberhaupt eine
//STRIP001              if (!xForm.is())
//STRIP001              {
//STRIP001                  Reference< ::com::sun::star::container::XIndexAccess >  xGetFirst(xForms, UNO_QUERY);
//STRIP001                  DBG_ASSERT(xGetFirst.is(), "FmFormPageImpl::getDefaultForm : no IndexAccess on my form container !");
//STRIP001                      // wenn das anspringt, muesste man sich die Namen des NameContainers geben lassen und dann das Objekt fuer den
//STRIP001                      // ersten Namen erfragen ... aber normalerweise sollte die FOrms-Sammlung auch einen IndexAccess haben
//STRIP001                  xGetFirst->getByIndex(0) >>= xForm;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001          xForm = xCurrentForm;
//STRIP001
//STRIP001      // keine gefunden dann standard erzeugen
//STRIP001      if (!xForm.is())
//STRIP001      {
//STRIP001
//STRIP001          SdrModel* pModel = pPage->GetModel();
//STRIP001          XubString aStr(SVX_RES(RID_STR_FORM));
//STRIP001          XubString aUndoStr(SVX_RES(RID_STR_UNDO_CONTAINER_INSERT));
//STRIP001          aUndoStr.SearchAndReplace('#', aStr);
//STRIP001          pModel->BegUndo(aUndoStr);
//STRIP001
//STRIP001          xForm = Reference< ::com::sun::star::form::XForm >(::legacy_binfilters::getLegacyProcessServiceFactory()->createInstance(FM_SUN_COMPONENT_FORM), UNO_QUERY);
//STRIP001          // a form should always have the command type table as default
//STRIP001          Reference< ::com::sun::star::beans::XPropertySet >  xSet(xForm, UNO_QUERY);
//STRIP001          try
//STRIP001          {
//STRIP001              xSet->setPropertyValue(FM_PROP_COMMANDTYPE, makeAny(sal_Int32(CommandType::TABLE)));
//STRIP001          }
//STRIP001          catch(Exception&)
//STRIP001          {
//STRIP001          }
//STRIP001
//STRIP001          ::rtl::OUString aName = ::rtl::OUString(SVX_RES(RID_STR_STDFORMNAME));
//STRIP001          xSet->setPropertyValue(FM_PROP_NAME, makeAny(aName));
//STRIP001
//STRIP001
//STRIP001          Reference< ::com::sun::star::container::XIndexContainer >  xContainer(xForms, UNO_QUERY);
//STRIP001          pModel->AddUndo(new FmUndoContainerAction(*(FmFormModel*)pModel,
//STRIP001                                                     FmUndoContainerAction::Inserted,
//STRIP001                                                     xContainer,
//STRIP001                                                     xForm,
//STRIP001                                                     xContainer->getCount()));
//STRIP001          xForms->insertByName(aName, makeAny(xForm));
//STRIP001          xCurrentForm = xForm;
//STRIP001          pModel->EndUndo();
//STRIP001      }
//STRIP001  }
//STRIP001  catch( const Exception& )
//STRIP001  {
//STRIP001      DBG_ERROR( "FmFormPageImpl::getDefaultForm: caught an exception!" );
//STRIP001      xForm.clear();
//STRIP001  }
//STRIP001
//STRIP001     return xForm;
//STRIP001 }

//------------------------------------------------------------------------------
//STRIP001 Reference< ::com::sun::star::form::XForm >  FmFormPageImpl::SetDefaults(const Reference< ::com::sun::star::form::XFormComponent > & rContent,
//STRIP001                                      const Reference< XDataSource > & rDatabase,
//STRIP001                                      const ::rtl::OUString& rDBTitle,
//STRIP001                                      const ::rtl::OUString& rCursorSource,
//STRIP001                                      sal_Int32 nCommandType)
//STRIP001 {
//STRIP001     // Ist das Control bereits einer ::com::sun::star::form zugeordnet
//STRIP001     if (!rContent.is() || rContent->getParent().is())
//STRIP001         return NULL;
//STRIP001
//STRIP001     Reference< XForm >  xForm;
//STRIP001     Reference< XPropertySet >  xSet;
//STRIP001
//STRIP001     // Wenn Datenbank und CursorSource gesetzt sind, dann wird
//STRIP001     // die ::com::sun::star::form anhand dieser Kriterien gesucht, ansonsten nur aktuelle
//STRIP001     // und die StandardForm
//STRIP001     if (rDatabase.is() && rCursorSource.getLength())
//STRIP001     {
//STRIP001         // erst in der aktuellen form suchen
//STRIP001         xForm = FindForm(xCurrentForm, rDatabase, rCursorSource, nCommandType);
//STRIP001
//STRIP001         Reference< ::com::sun::star::container::XIndexAccess >  xFormsByIndex(xForms, UNO_QUERY);
//STRIP001         DBG_ASSERT(xFormsByIndex.is(), "FmFormPageImpl::SetDefaults : no index access for my forms collection !");
//STRIP001         sal_Int32 nCount = xFormsByIndex->getCount();
//STRIP001         for (sal_Int32 i = 0; !xForm.is() && i < nCount; i++)
//STRIP001         {
//STRIP001             Reference< ::com::sun::star::form::XForm >  xToSearch;
//STRIP001             xFormsByIndex->getByIndex(i) >>= xToSearch;
//STRIP001             xForm = FindForm(xToSearch, rDatabase, rCursorSource, nCommandType);
//STRIP001         }
//STRIP001
//STRIP001         // wenn keine ::com::sun::star::form gefunden, dann eine neue erzeugen
//STRIP001         if (!xForm.is())
//STRIP001         {
//STRIP001             SdrModel* pModel = pPage->GetModel();
//STRIP001             XubString aStr(SVX_RES(RID_STR_FORM));
//STRIP001             XubString aUndoStr(SVX_RES(RID_STR_UNDO_CONTAINER_INSERT));
//STRIP001             aUndoStr.SearchAndReplace('#', aStr);
//STRIP001             pModel->BegUndo(aUndoStr);
//STRIP001             xForm = Reference< ::com::sun::star::form::XForm >(::legacy_binfilters::getLegacyProcessServiceFactory()->createInstance(FM_SUN_COMPONENT_FORM), UNO_QUERY);
//STRIP001             // a form should always have the command type table as default
//STRIP001             Reference< ::com::sun::star::beans::XPropertySet >  xSet(xForm, UNO_QUERY);
//STRIP001             try { xSet->setPropertyValue(FM_PROP_COMMANDTYPE, makeAny(sal_Int32(CommandType::TABLE))); }
//STRIP001             catch(Exception&) { }
//STRIP001
//STRIP001             if (rDBTitle.getLength())
//STRIP001                 xSet->setPropertyValue(FM_PROP_DATASOURCE,makeAny(rDBTitle));
//STRIP001             else
//STRIP001             {
//STRIP001                 Reference< ::com::sun::star::beans::XPropertySet >  xDatabaseProps(rDatabase, UNO_QUERY);
//STRIP001                 Any aDatabaseUrl = xDatabaseProps->getPropertyValue(FM_PROP_URL);
//STRIP001                 xSet->setPropertyValue(FM_PROP_DATASOURCE, aDatabaseUrl);
//STRIP001             }
//STRIP001
//STRIP001             xSet->setPropertyValue(FM_PROP_COMMAND,makeAny(rCursorSource));
//STRIP001             xSet->setPropertyValue(FM_PROP_COMMANDTYPE, makeAny(nCommandType));
//STRIP001
//STRIP001             Reference< ::com::sun::star::container::XNameAccess >  xNamedSet(xForms, UNO_QUERY);
//STRIP001             ::rtl::OUString aName;
//STRIP001
//STRIP001             if ((CommandType::TABLE == nCommandType) || (CommandType::QUERY == nCommandType))
//STRIP001             {
//STRIP001                 // Namen der ::com::sun::star::form ueber den Titel der CursorSource setzen
//STRIP001                 aName = getUniqueName(rCursorSource, xNamedSet);
//STRIP001             }
//STRIP001             else
//STRIP001                 // ansonsten StandardformName verwenden
//STRIP001                 aName = getUniqueName(::rtl::OUString(SVX_RES(RID_STR_STDFORMNAME)), xNamedSet);
//STRIP001
//STRIP001             xSet->setPropertyValue(FM_PROP_NAME, makeAny(aName));
//STRIP001
//STRIP001             Reference< ::com::sun::star::container::XIndexContainer >  xContainer(xForms, UNO_QUERY);
//STRIP001             pModel->AddUndo(new FmUndoContainerAction(*(FmFormModel*)pModel,
//STRIP001                                                      FmUndoContainerAction::Inserted,
//STRIP001                                                      xContainer,
//STRIP001                                                      xForm,
//STRIP001                                                      xContainer->getCount()));
//STRIP001
//STRIP001
//STRIP001             xForms->insertByName(aName, makeAny(xForm));
//STRIP001             pModel->EndUndo();
//STRIP001         }
//STRIP001         xCurrentForm = xForm;
//STRIP001     }
//STRIP001
//STRIP001     xForm = getDefaultForm();
//STRIP001     // eindeutigen Namen fuer die Componente setzen
//STRIP001     setUniqueName(rContent, xForm);
//STRIP001     return xForm;
//STRIP001 }

//------------------------------------------------------------------------------
//STRIP001 Reference< XForm >  FmFormPageImpl::FindForm(
//STRIP001      const Reference< XForm > & rForm, const Reference< XDataSource > & _rxDatabase,
//STRIP001      const ::rtl::OUString& _rCursorSource, sal_Int32 nCommandType)
//STRIP001 {
//STRIP001     Reference< XForm >           xResultForm;
//STRIP001     Reference< XRowSet >     xDBForm(rForm, UNO_QUERY);
//STRIP001     Reference< XPropertySet >    xFormProps(rForm, UNO_QUERY);
//STRIP001     if (!xDBForm.is() || !xFormProps.is())
//STRIP001         return xResultForm;
//STRIP001
//STRIP001  OSL_ENSURE(_rxDatabase.is(), "FmFormPageImpl::FindForm: invalid data source!");
//STRIP001  ::rtl::OUString sLookupName;            // the name of the data source we're looking for
//STRIP001  ::rtl::OUString sFormDataSourceName;    // the name of the data source the current connection in the form is based on
//STRIP001  try
//STRIP001  {
//STRIP001      Reference< XPropertySet > xDSProps(_rxDatabase, UNO_QUERY);
//STRIP001      if (xDSProps.is())
//STRIP001          xDSProps->getPropertyValue(FM_PROP_NAME) >>= sLookupName;
//STRIP001
//STRIP001      xFormProps->getPropertyValue(FM_PROP_DATASOURCE) >>= sFormDataSourceName;
//STRIP001      if (0 == sFormDataSourceName.getLength())
//STRIP001      {
//STRIP001          // check if it has an active connection
//STRIP001          Reference< XConnection > xFormConnection = OStaticDataAccessTools().getRowSetConnection(xDBForm);
//STRIP001          if (xFormConnection.is())
//STRIP001          {
//STRIP001              OSL_ENSURE(sal_False, "FmFormPageImpl::FindForm: a connection without data source name?");
//STRIP001                  // don't know if this is allowed to happen (don't think so, that's why asserting this).
//STRIP001                  // 05.06.2001 - 87688 - frank.schoenheit@sun.com
//STRIP001              Reference< XChild > xConnAsChild(xFormConnection, UNO_QUERY);
//STRIP001              if (xConnAsChild.is())
//STRIP001              {
//STRIP001                  Reference< XDataSource > xFormDS(xConnAsChild->getParent(), UNO_QUERY);
//STRIP001                      // the data source which created the connection
//STRIP001                  if (xFormDS.is())
//STRIP001                  {
//STRIP001                      xDSProps = xDSProps.query(xFormDS);
//STRIP001                      if (xDSProps.is())
//STRIP001                          xDSProps->getPropertyValue(FM_PROP_NAME) >>= sFormDataSourceName;
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  catch(const Exception& e)
//STRIP001  {
//STRIP001      e;
//STRIP001      OSL_ENSURE(sal_False, "FmFormPageImpl::FindForm: caught an exception!");
//STRIP001  }
//STRIP001
//STRIP001  if (sLookupName == sFormDataSourceName)
//STRIP001     {
//STRIP001         // jetzt noch ueberpruefen ob CursorSource und Type uebereinstimmen
//STRIP001         ::rtl::OUString aCursorSource = ::comphelper::getString(xFormProps->getPropertyValue(FM_PROP_COMMAND));
//STRIP001         sal_Int32 nType = ::comphelper::getINT32(xFormProps->getPropertyValue(FM_PROP_COMMANDTYPE));
//STRIP001         if (!aCursorSource.getLength() || ((nType == nCommandType) && (aCursorSource == _rCursorSource))) // found the form
//STRIP001         {
//STRIP001             xResultForm = rForm;
//STRIP001             // Ist noch keine Datenquelle gesetzt, wird dieses hier nachgeholt
//STRIP001             if (!aCursorSource.getLength())
//STRIP001             {
//STRIP001                 xFormProps->setPropertyValue(FM_PROP_COMMAND, makeAny(_rCursorSource));
//STRIP001                 xFormProps->setPropertyValue(FM_PROP_COMMANDTYPE, makeAny((sal_Int32)nCommandType));
//STRIP001             }
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001  // as long as xResultForm is NULL, search the child forms of rForm
//STRIP001     Reference< XIndexAccess >  xComponents(rForm, UNO_QUERY);
//STRIP001     sal_Int32 nCount = xComponents->getCount();
//STRIP001     for (sal_Int32 i = 0; !xResultForm.is() && i < nCount; ++i)
//STRIP001     {
//STRIP001         Reference< ::com::sun::star::form::XForm >  xSearchForm;
//STRIP001         xComponents->getByIndex(i) >>= xSearchForm;
//STRIP001         // jetzt innerhalb der ::com::sun::star::form weitersuchen
//STRIP001         if (xSearchForm.is())
//STRIP001             xResultForm = FindForm(xSearchForm, _rxDatabase, _rCursorSource, nCommandType);
//STRIP001     }
//STRIP001     return xResultForm;
//STRIP001 }

//------------------------------------------------------------------------------
//STRIP001 ::rtl::OUString FmFormPageImpl::setUniqueName(const Reference< ::com::sun::star::form::XFormComponent > & xFormComponent, const Reference< ::com::sun::star::form::XForm > & xControls)
//STRIP001 {
//STRIP001     ::rtl::OUString sName;
//STRIP001     Reference< ::com::sun::star::beans::XPropertySet >  xSet(xFormComponent, UNO_QUERY);
//STRIP001     if (xSet.is())
//STRIP001     {
//STRIP001         Any aValue = xSet->getPropertyValue(FM_PROP_NAME);
//STRIP001         sName = ::comphelper::getString(aValue);
//STRIP001         Reference< ::com::sun::star::container::XNameAccess >  xNameAcc(xControls, UNO_QUERY);
//STRIP001
//STRIP001         if (!sName.getLength() || xNameAcc->hasByName(sName))
//STRIP001         {
//STRIP001             // setzen eines default Namens ueber die ClassId
//STRIP001             Any aValue = xSet->getPropertyValue(FM_PROP_CLASSID);
//STRIP001             sal_Int16 nClassId(::com::sun::star::form::FormComponentType::CONTROL);
//STRIP001             aValue >>= nClassId;
//STRIP001          Reference< XServiceInfo > xSI( xSet, UNO_QUERY );
//STRIP001
//STRIP001             ::rtl::OUString sDefaultName = getDefaultName( nClassId, xControls, xSI );
//STRIP001             // bei Radiobuttons, die einen Namen haben, diesen nicht ueberschreiben!
//STRIP001             if (!sName.getLength() || nClassId != ::com::sun::star::form::FormComponentType::RADIOBUTTON)
//STRIP001             {
//STRIP001                 xSet->setPropertyValue(FM_PROP_NAME, makeAny(sDefaultName));
//STRIP001             }
//STRIP001
//STRIP001             //////////////////////////////////////////////////////////////
//STRIP001             // Labels anpassen
//STRIP001             UniString aLabel = sDefaultName;
//STRIP001             sal_uInt16 nResId = 0;
//STRIP001
//STRIP001             switch (nClassId)
//STRIP001             {
//STRIP001                 case ::com::sun::star::form::FormComponentType::COMMANDBUTTON:  nResId = RID_STR_PROPTITLE_PUSHBUTTON;      break;
//STRIP001                 case ::com::sun::star::form::FormComponentType::RADIOBUTTON:    nResId = RID_STR_PROPTITLE_RADIOBUTTON;     break;
//STRIP001                 case ::com::sun::star::form::FormComponentType::CHECKBOX:       nResId = RID_STR_PROPTITLE_CHECKBOX;        break;
//STRIP001                 case ::com::sun::star::form::FormComponentType::GROUPBOX:       nResId = RID_STR_PROPTITLE_GROUPBOX;        break;
//STRIP001                 case ::com::sun::star::form::FormComponentType::FIXEDTEXT:      nResId = RID_STR_PROPTITLE_FIXEDTEXT;       break;
//STRIP001             }
//STRIP001
//STRIP001             if (nResId)
//STRIP001             {
//STRIP001                 aValue = xSet->getPropertyValue(FM_PROP_LABEL);
//STRIP001                 ::rtl::OUString aText;
//STRIP001                 aValue >>= aText;
//STRIP001                 if (!aText.getLength())
//STRIP001                 {
//STRIP001                     aLabel.SearchAndReplace( getDefaultName( nClassId, xSI ), ::rtl::OUString(SVX_RES(nResId)) );
//STRIP001                     xSet->setPropertyValue( FM_PROP_LABEL, makeAny(::rtl::OUString(aLabel)) );
//STRIP001                 }
//STRIP001             }
//STRIP001
//STRIP001             sName = sDefaultName;
//STRIP001         }
//STRIP001     }
//STRIP001     return sName;
//STRIP001 }


//STRIP001 UniString FmFormPageImpl::getDefaultName( sal_Int16 _nClassId, const Reference< XServiceInfo >& _rxObject )
//STRIP001 {
//STRIP001     sal_uInt16 nResId;
//STRIP001
//STRIP001     switch (_nClassId)
//STRIP001     {
//STRIP001         case FormComponentType::COMMANDBUTTON:  nResId = RID_STR_BUTTON_CLASSNAME;      break;
//STRIP001         case FormComponentType::RADIOBUTTON:    nResId = RID_STR_RADIOBUTTON_CLASSNAME; break;
//STRIP001         case FormComponentType::CHECKBOX:       nResId = RID_STR_CHECKBOX_CLASSNAME;    break;
//STRIP001         case FormComponentType::LISTBOX:        nResId = RID_STR_LISTBOX_CLASSNAME;     break;
//STRIP001         case FormComponentType::COMBOBOX:       nResId = RID_STR_COMBOBOX_CLASSNAME;    break;
//STRIP001         case FormComponentType::GROUPBOX:       nResId = RID_STR_GROUPBOX_CLASSNAME;    break;
//STRIP001         case FormComponentType::IMAGEBUTTON:    nResId = RID_STR_IMAGE_CLASSNAME;       break;
//STRIP001         case FormComponentType::FIXEDTEXT:      nResId = RID_STR_FIXEDTEXT_CLASSNAME;   break;
//STRIP001         case FormComponentType::GRIDCONTROL:    nResId = RID_STR_GRID_CLASSNAME;        break;
//STRIP001         case FormComponentType::FILECONTROL:    nResId = RID_STR_FILECONTROL_CLASSNAME; break;
//STRIP001         case FormComponentType::DATEFIELD:      nResId = RID_STR_DATEFIELD_CLASSNAME;   break;
//STRIP001         case FormComponentType::TIMEFIELD:      nResId = RID_STR_TIMEFIELD_CLASSNAME;   break;
//STRIP001         case FormComponentType::NUMERICFIELD:   nResId = RID_STR_NUMERICFIELD_CLASSNAME;    break;
//STRIP001         case FormComponentType::CURRENCYFIELD:  nResId = RID_STR_CURRENCYFIELD_CLASSNAME;   break;
//STRIP001         case FormComponentType::PATTERNFIELD:   nResId = RID_STR_PATTERNFIELD_CLASSNAME;    break;
//STRIP001         case FormComponentType::IMAGECONTROL:   nResId = RID_STR_IMAGECONTROL_CLASSNAME;    break;
//STRIP001         case FormComponentType::HIDDENCONTROL:  nResId = RID_STR_HIDDEN_CLASSNAME;      break;
//STRIP001
//STRIP001         case FormComponentType::TEXTFIELD:
//STRIP001          nResId = RID_STR_EDIT_CLASSNAME;
//STRIP001          if ( _rxObject.is() && _rxObject->supportsService( FM_SUN_COMPONENT_FORMATTEDFIELD ) )
//STRIP001              nResId = RID_STR_FORMATTED_CLASSNAME;
//STRIP001          break;
//STRIP001
//STRIP001         case FormComponentType::CONTROL:
//STRIP001         default:
//STRIP001             nResId = RID_STR_CONTROL_CLASSNAME;     break;
//STRIP001     }
//STRIP001
//STRIP001     return SVX_RES(nResId);
//STRIP001 }

//------------------------------------------------------------------------------
//STRIP001 ::rtl::OUString FmFormPageImpl::getDefaultName(
//STRIP001  sal_Int16 _nClassId, const Reference< XForm >& _rxControls, const Reference< XServiceInfo >& _rxObject ) const
//STRIP001 {
//STRIP001     ::rtl::OUString aClassName=getDefaultName( _nClassId, _rxObject );
//STRIP001
//STRIP001     Reference< ::com::sun::star::container::XNameAccess >  xNamedSet( _rxControls, UNO_QUERY );
//STRIP001     return getUniqueName(aClassName, xNamedSet);
//STRIP001 }

//------------------------------------------------------------------
//STRIP001 ::rtl::OUString FmFormPageImpl::getUniqueName(const ::rtl::OUString& rName, const Reference< ::com::sun::star::container::XNameAccess > & xNamedSet) const
//STRIP001 {
//STRIP001     Reference< ::com::sun::star::container::XIndexAccess >  xIndexSet(xNamedSet, UNO_QUERY);
//STRIP001     ::rtl::OUString sName( rName );
//STRIP001
//STRIP001     if ( !xIndexSet.is() )
//STRIP001         return sName;
//STRIP001
//STRIP001     sal_Int32 n = 0;
//STRIP001     ::rtl::OUString sClassName = rName;
//STRIP001
//STRIP001     while ( xNamedSet->hasByName( sName ) )
//STRIP001         sName = sClassName + ::rtl::OUString::valueOf(++n);
//STRIP001
//STRIP001     return sName;
//STRIP001 }

//------------------------------------------------------------------------------
/*N*/ void FmFormPageImpl::WriteData(SvStream& rOut) const
/*N*/ {
/*N*/     // anlegen eines output streams fuer UNO
/*N*/     Reference< ::com::sun::star::io::XActiveDataSource >  xSource(::legacy_binfilters::getLegacyProcessServiceFactory()->createInstance(::rtl::OUString::createFromAscii("com.sun.star.io.ObjectOutputStream")), UNO_QUERY);
/*N*/     Reference< ::com::sun::star::io::XOutputStream >  xMarkOut(::legacy_binfilters::getLegacyProcessServiceFactory()->createInstance(::rtl::OUString::createFromAscii("com.sun.star.io.MarkableOutputStream")), UNO_QUERY);
/*N*/     Reference< ::com::sun::star::io::XActiveDataSource >  xMarkSource(xMarkOut, UNO_QUERY);
/*N*/
/*N*/     if (xSource.is())
/*N*/     {
/*N*/         xMarkSource->setOutputStream(new ::utl::OOutputStreamWrapper(rOut));
/*N*/         xSource->setOutputStream(xMarkOut);
/*N*/
/*N*/         Reference< ::com::sun::star::io::XObjectOutputStream >  xOutStrm(xSource, UNO_QUERY);
/*N*/         try
/*N*/         {
/*N*/             write(xOutStrm);
/*N*/         }
/*N*/         catch(Exception&)
/*N*/         {
/*?*/             rOut.SetError( ERRCODE_CLASS_WRITE | ERRCODE_SVX_FORMS_READWRITEFAILED | ERRCODE_WARNING_MASK );
/*N*/         }
/*N*/
/*N*/         xOutStrm->closeOutput();
/*N*/     }
/*N*/     else
/*N*/     {
/*N*/         // let's do a hack : in former versions we didn't use UNO-stream but SvStreams, so there was
/*N*/         // no possibility that we couldn't write because of the lack of stream objects. Now, with UNO, this may happen
/*N*/         // (as it happended here). But the read-methods of the older versions don't expect that (there is no flag in
/*N*/         // the fileformat as it never was neccessary). To allow the old versions the read of the documents, we fake the
/*N*/         // write : the first token usually written by our impl is an sal_Int32 giving the number of forms within the forms
/*N*/         // collection. If this number is 0, no further reading will occur.
/*?*/         sal_Int32 nDummLength = 0; rOut << nDummLength;     // this means 'no forms'
/*?*/         nDummLength = 0; rOut << nDummLength;           // this means 'no form controls"
/*?*/         // To tell the user that something went wrong we set a warning on the stream.
/*?*/         rOut.SetError( ERRCODE_CLASS_WRITE | ERRCODE_SVX_FORMS_NOIOSERVICES | ERRCODE_WARNING_MASK );
/*N*/     }
/*N*/ }

//------------------------------------------------------------------------------
/*N*/ void FmFormPageImpl::ReadData(const SdrIOHeader& rHead, SvStream& rIn)
/*N*/ {
/*N*/     // Abholen des InputStreams ueber uno
/*N*/     Reference< ::com::sun::star::io::XActiveDataSink >  xSink(::legacy_binfilters::getLegacyProcessServiceFactory()->createInstance(::rtl::OUString::createFromAscii("com.sun.star.io.ObjectInputStream")), UNO_QUERY);
/*N*/
/*N*/     // creating the mark streams
/*N*/     Reference< ::com::sun::star::io::XInputStream >  xMarkIn(::legacy_binfilters::getLegacyProcessServiceFactory()->createInstance(::rtl::OUString::createFromAscii("com.sun.star.io.MarkableInputStream")), UNO_QUERY);
/*N*/     Reference< ::com::sun::star::io::XActiveDataSink >  xMarkSink(xMarkIn, UNO_QUERY);
/*N*/
/*N*/     if (xSink.is())
/*N*/     {
/*N*/         ::utl::OInputStreamWrapper* pUnoStream = new ::utl::OInputStreamWrapper(rIn);
/*N*/         xMarkSink->setInputStream(Reference< ::com::sun::star::io::XInputStream > (pUnoStream));
/*N*/         xSink->setInputStream(xMarkIn);
/*N*/
/*N*/         // freigeben aller forms
/*N*/         xCurrentForm = NULL;
/*N*/
/*N*/         if (xForms->hasElements())
/*N*/         {
/*?*/             ::comphelper::disposeComponent(xForms);
/*?*/             Init();
/*N*/         }
/*N*/
/*N*/         Reference< ::com::sun::star::io::XObjectInputStream >  xInStrm(xSink,UNO_QUERY);
/*N*/         try
/*N*/         {
/*N*/             read(xInStrm);
/*N*/         }
/*N*/         catch(Exception&)
/*N*/         {
/*?*/             rIn.SetError( ERRCODE_CLASS_READ | ERRCODE_SVX_FORMS_READWRITEFAILED | ERRCODE_WARNING_MASK );
/*N*/         }
/*N*/
/*N*/
/*N*/         xInStrm->closeInput();
/*N*/     }
/*N*/     else
/*?*/         rIn.SetError( ERRCODE_CLASS_READ | ERRCODE_SVX_FORMS_NOIOSERVICES | ERRCODE_WARNING_MASK );
/*N*/ }

//------------------------------------------------------------------------------
/*N*/ void FmFormPageImpl::write(const Reference< ::com::sun::star::io::XObjectOutputStream > & xOutStrm) const
/*N*/ {
/*N*/     Reference< ::com::sun::star::io::XMarkableStream >  xMarkStrm(xOutStrm, UNO_QUERY);
/*N*/     if (!xMarkStrm.is())
/*N*/         return; // exception
/*N*/
/*N*/     //  sortieren der objectlist nach der Reihenfolge
/*N*/     FmObjectList aList;
/*N*/     fillList(aList, *pPage, sal_True);
/*N*/
/*N*/     // schreiben aller forms
/*N*/     Reference< ::com::sun::star::io::XPersistObject >  xAsPersist(xForms, UNO_QUERY);
/*N*/     if (xAsPersist.is())
/*N*/         xAsPersist->write(xOutStrm);
/*N*/         // don't use the writeObject of the stream, as this wouldn't be compatible with older documents
/*N*/
/*N*/     // objectliste einfuegen
/*N*/     sal_Int32 nLength = aList.Count();
/*N*/
/*N*/     // schreiben der laenge
/*N*/     xOutStrm->writeLong(nLength);
/*N*/
/*N*/     for (sal_Int32 i = 0; i < nLength; i++)
/*N*/     {
/*N*/         // schreiben des Objects mit Marke
/*N*/         // Marke um an den Anfang zu springen
/*N*/         Reference< ::com::sun::star::io::XPersistObject >  xObj(aList.GetObject(i)->GetUnoControlModel(), UNO_QUERY);
/*N*/         if (xObj.is())
/*N*/         {
/*N*/             xOutStrm->writeObject(xObj);
/*N*/         }
/*N*/         else
/*N*/             ;// exception
/*N*/     }
/*N*/ }

//------------------------------------------------------------------------------
/*N*/ void FmFormPageImpl::read(const Reference< ::com::sun::star::io::XObjectInputStream > & xInStrm)
/*N*/ {
/*N*/     Reference< ::com::sun::star::io::XMarkableStream >  xMarkStrm(xInStrm, UNO_QUERY);
/*N*/     if (!xMarkStrm.is())
/*N*/         return; // exception
/*N*/
/*N*/     //  sortieren der objectlist nach der Reihenfolge
/*N*/     FmObjectList aList;
/*N*/     fillList(aList, *pPage, sal_False);
/*N*/
/*N*/     // lesen aller forms
/*N*/     Reference< ::com::sun::star::io::XPersistObject >  xAsPersist(xForms, UNO_QUERY);
/*N*/     if (xAsPersist.is())
/*N*/         xAsPersist->read(xInStrm);
/*N*/         // don't use the readObject of the stream, as this wouldn't be compatible with older documents
/*N*/
/*N*/     // Zuordnung der Formobjekte zu den FormComponents
/*N*/     sal_Int32 nLength = xInStrm->readLong();
/*N*/     DBG_ASSERT(nLength == (sal_Int32) aList.Count(), "Fehler beim Lesen der UnoModels");
/*N*/     for (sal_Int32 i = 0; i < nLength; i++)
/*N*/     {
/*N*/         Reference< ::com::sun::star::awt::XControlModel >  xRef(xInStrm->readObject(), UNO_QUERY);
/*N*/         if (i < (sal_Int32)aList.Count())
/*N*/             aList.GetObject(i)->SetUnoControlModel(xRef);
/*N*/     }
/*N*/ }

//------------------------------------------------------------------------------
/*N*/ void FmFormPageImpl::fillList(FmObjectList& rList, const SdrObjList& rObjList, sal_Bool bConnected) const
/*N*/ {
/*N*/     SdrObjListIter aIter(rObjList);
/*N*/     while (aIter.IsMore())
/*N*/     {
/*N*/         SdrObject* pObj = aIter.Next();
/*N*/         if (pObj && pObj->GetObjInventor() == FmFormInventor)
/*N*/         {
/*N*/             FmFormObj* pFormObj = PTR_CAST(FmFormObj, pObj);
/*N*/             DBG_ASSERT(!bConnected || pFormObj->GetUnoControlModel().is(), "Controlshape ohne Control");
/*N*/             if (!bConnected || pFormObj->GetUnoControlModel().is())
/*N*/                 rList.Insert(pFormObj, LIST_APPEND);
/*N*/
/*N*/         }
/*N*/     }
/*N*/ }


}
