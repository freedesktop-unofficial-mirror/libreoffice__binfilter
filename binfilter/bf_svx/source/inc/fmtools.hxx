/*************************************************************************
 *
 *  $RCSfile: fmtools.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 15:57:53 $
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
#ifndef _SVX_FMTOOLS_HXX
#define _SVX_FMTOOLS_HXX

// auto strip #ifndef _COM_SUN_STAR_SDB_SQLCONTEXT_HPP_
// auto strip #include <com/sun/star/sdb/SQLContext.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_SDB_XSQLQUERYCOMPOSERFACTORY_HPP_
// auto strip #include <com/sun/star/sdb/XSQLQueryComposerFactory.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_SDBCX_PRIVILEGE_HPP_
// auto strip #include <com/sun/star/sdbcx/Privilege.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_SDBCX_XCOLUMNSSUPPLIER_HPP_
// auto strip #include <com/sun/star/sdbcx/XColumnsSupplier.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_SDBCX_XDATADESCRIPTORFACTORY_HPP_
// auto strip #include <com/sun/star/sdbcx/XDataDescriptorFactory.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_SDBC_XROWSET_HPP_
// auto strip #include <com/sun/star/sdbc/XRowSet.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_SDBC_XDATABASEMETADATA_HPP_
// auto strip #include <com/sun/star/sdbc/XDatabaseMetaData.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_SDB_XCOLUMN_HPP_
// auto strip #include <com/sun/star/sdb/XColumn.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_SDB_XCOLUMNUPDATE_HPP_
// auto strip #include <com/sun/star/sdb/XColumnUpdate.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_SDBC_SQLERROREVENT_HPP_
// auto strip #include <com/sun/star/sdb/SQLErrorEvent.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_SDBC_XCONNECTION_HPP_
// auto strip #include <com/sun/star/sdbc/XConnection.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_SDBC_XRESULTSET_HPP_
// auto strip #include <com/sun/star/sdbc/XResultSet.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_SDBC_XRESULTSETUPDATE_HPP_
// auto strip #include <com/sun/star/sdbc/XResultSetUpdate.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_SDBCX_XROWLOCATE_HPP_
// auto strip #include <com/sun/star/sdbcx/XRowLocate.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_SDBC_XDATASOURCE_HPP_
// auto strip #include <com/sun/star/sdbc/XDataSource.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
// auto strip #include <com/sun/star/beans/XPropertySet.hpp>
// auto strip #endif
#ifndef _COM_SUN_STAR_FRAME_XDISPATCHPROVIDERINTERCEPTION_HPP_
#include <com/sun/star/frame/XDispatchProviderInterception.hpp>
#endif
// auto strip #ifndef _COM_SUN_STAR_FRAME_XDISPATCHPROVIDERINTERCEPTOR_HPP_
// auto strip #include <com/sun/star/frame/XDispatchProviderInterceptor.hpp>
// auto strip #endif
#ifndef _COM_SUN_STAR_FRAME_XINTERCEPTORINFO_HPP_
#include <com/sun/star/frame/XInterceptorInfo.hpp>
#endif
// auto strip #ifndef _COM_SUN_STAR_CONTAINER_XINDEXCONTAINER_HPP_
// auto strip #include <com/sun/star/container/XIndexContainer.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_FRAME_XDISPATCH_HPP_
// auto strip #include <com/sun/star/frame/XDispatch.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_FRAME_XSTATUSLISTENER_HPP_
// auto strip #include <com/sun/star/frame/XStatusListener.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_FRAME_FEATURESTATEEVENT_HPP_
// auto strip #include <com/sun/star/frame/FeatureStateEvent.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_FRAME_XMODEL_HPP_
// auto strip #include <com/sun/star/frame/XModel.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_SCRIPT_SCRIPTEVENTDESCRIPTOR_HPP_
// auto strip #include <com/sun/star/script/ScriptEventDescriptor.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_CONTAINER_XNAMEACCESS_HPP_
// auto strip #include <com/sun/star/container/XNameAccess.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_CONTAINER_XENUMERATION_HPP_
// auto strip #include <com/sun/star/container/XEnumeration.hpp>
// auto strip #endif
#ifndef _COM_SUN_STAR_CONTAINER_XINDEXACCESS_HPP_
#include <com/sun/star/container/XIndexAccess.hpp>
#endif
// auto strip #ifndef _COM_SUN_STAR_AWT_XCONTROLMODEL_HPP_
// auto strip #include <com/sun/star/awt/XControlModel.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_AWT_XCONTROL_HPP_
// auto strip #include <com/sun/star/awt/XControl.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_AWT_FONTSLANT_HPP_
// auto strip #include <com/sun/star/awt/FontSlant.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_AWT_FONTDESCRIPTOR_HPP_
// auto strip #include <com/sun/star/awt/FontDescriptor.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_AWT_FONTUNDERLINE_HPP_
// auto strip #include <com/sun/star/awt/FontUnderline.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_AWT_FONTSTRIKEOUT_HPP_
// auto strip #include <com/sun/star/awt/FontStrikeout.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_UTIL_XNUMBERFORMATSSUPPLIER_HPP_
// auto strip #include <com/sun/star/util/XNumberFormatsSupplier.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_LANG_XSERVICEINFO_HPP_
// auto strip #include <com/sun/star/lang/XServiceInfo.hpp>
// auto strip #endif
// auto strip #ifndef _SV_WINTYPES_HXX //autogen
// auto strip #include <vcl/wintypes.hxx>
// auto strip #endif

// auto strip #ifndef _VOS_MUTEX_HXX_ //autogen
// auto strip #include <vos/mutex.hxx>
// auto strip #endif

#ifndef _SVSTDARR_ULONGS
#define _SVSTDARR_ULONGS
// auto strip #include <svtools/svstdarr.hxx>
#endif

#ifndef _SFXCTRLITEM_HXX //autogen wg. SfxControllerItem
#include <bf_sfx2/ctrlitem.hxx>
#endif

// auto strip #ifndef _LINK_HXX
// auto strip #include <tools/link.hxx>
// auto strip #endif

// auto strip #ifndef _DATE_HXX
// auto strip #include <tools/date.hxx>
// auto strip #endif
// auto strip #ifndef _TOOLS_TIME_HXX
// auto strip #include <tools/time.hxx>
// auto strip #endif
// auto strip #ifndef _DATETIME_HXX
// auto strip #include <tools/datetime.hxx>
// auto strip #endif

#ifndef _SVX_FMPROP_HRC
#include "fmprop.hrc"
#endif
// auto strip #ifndef _COM_SUN_STAR_SDBC_XCONNECTION_HPP_
// auto strip #include <com/sun/star/sdbc/XConnection.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_IO_XOBJECTINPUTSTREAM_HPP_
// auto strip #include <com/sun/star/io/XObjectInputStream.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_IO_XOBJECTOUTPUTSTREAM_HPP_
// auto strip #include <com/sun/star/io/XObjectOutputStream.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_IO_XPERSISTOBJECT_HPP_
// auto strip #include <com/sun/star/io/XPersistObject.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_UTIL_XNUMBERFORMATTER_HPP_
// auto strip #include <com/sun/star/util/XNumberFormatter.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_UTIL_XNUMBERFORMATS_HPP_
// auto strip #include <com/sun/star/util/XNumberFormats.hpp>
// auto strip #endif
#ifndef _CPPUHELPER_INTERFACECONTAINER_H_
#include <cppuhelper/interfacecontainer.h>
#endif
// auto strip #ifndef _CPPUHELPER_COMPBASE2_HXX_
// auto strip #include <cppuhelper/compbase2.hxx>
// auto strip #endif
#ifndef _CPPUHELPER_COMPBASE3_HXX_
#include <cppuhelper/compbase3.hxx>
#endif
// auto strip #ifndef _CPPUHELPER_WEAKREF_HXX_
// auto strip #include <cppuhelper/weakref.hxx>
// auto strip #endif
#ifndef _COMPHELPER_UNO3_HXX_
#include <comphelper/uno3.hxx>
#endif
// auto strip #ifndef _CPPUHELPER_IMPLBASE1_HXX_
// auto strip #include <cppuhelper/implbase1.hxx>
// auto strip #endif
#ifndef _CPPUHELPER_IMPLBASE2_HXX_
#include <cppuhelper/implbase2.hxx>
#endif
// auto strip #ifndef _CPPUHELPER_IMPLBASE3_HXX_
// auto strip #include <cppuhelper/implbase3.hxx>
// auto strip #endif
#ifndef _CPPUHELPER_COMPONENT_HXX_
#include <cppuhelper/component.hxx>
#endif

#ifndef _FM_IMPLEMENTATION_IDS_HXX_
#include "fmimplids.hxx"
#endif

// auto strip #ifndef _FM_STATIC_HXX_
// auto strip #include "fmstatic.hxx"
// auto strip #endif
class Window;
namespace binfilter {



//==================================================================
// allgemeine Typen
//==================================================================
// displaying a database exception for the user
// display info about a simple ::com::sun::star::sdbc::SQLException
//STRIP001 void displayException(const ::com::sun::star::sdbc::SQLException&, Window* _pParent = NULL);
//STRIP001 void displayException(const ::com::sun::star::sdbc::SQLWarning&, Window* _pParent = NULL);
//STRIP001 void displayException(const ::com::sun::star::sdb::SQLContext&, Window* _pParent = NULL);
// display info about chained SQLExceptions
//STRIP001 void displayException(const ::com::sun::star::sdb::SQLErrorEvent&, Window* _pParent = NULL);

// StringConversion
namespace svxform
{
    // modes for the XModeSelector
    DECLARE_CONSTASCII_USTRING(DATA_MODE);
    DECLARE_CONSTASCII_USTRING(FILTER_MODE);

}   // namespace svxform


// Kopieren von Persistenten Objecten
//STRIP001 ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface> cloneUsingProperties(const ::com::sun::star::uno::Reference< ::com::sun::star::io::XPersistObject>& _xObj);

//STRIP001 sal_Int32 findPos(const ::rtl::OUString& aStr, const ::com::sun::star::uno::Sequence< ::rtl::OUString>& rList);

// Suchen in einer Indexliste nach einem Element
//STRIP001 sal_Bool  searchElement(const ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexAccess>& xCont, const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface>& xElement);

sal_Int32 getElementPos(const ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexAccess>& xCont, const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface>& xElement);
//STRIP001 String getFormComponentAccessPath(const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface>& _xElement);
//STRIP001 String getFormComponentAccessPath(const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface>& _xElement, ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface>& _rTopLevelElement);
//STRIP001 ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface> getElementFromAccessPath(const ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexAccess>& _xParent, const String& _rRelativePath);


//STRIP001 ::com::sun::star::uno::Reference< ::com::sun::star::frame::XModel> getXModel(const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface>& xIface);

//STRIP001 ::rtl::OUString getLabelName(const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet>& xControlModel);

// ===================================================================================================
// = class CursorWrapper - eine Hilfsklasse, die parallel mit je einem ::com::sun::star::uno::Reference<XDatabaseUpdateCursor>,
//                          XDatabaseBookmarkCursor und XDatabaseDirectCursor arbeitet
// ===================================================================================================

//STRIP001 class CursorWrapper
//STRIP001 {
//STRIP001 private:
//STRIP001  ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface>                m_xGeneric;
//STRIP001  ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XResultSet>               m_xMoveOperations;
//STRIP001  ::com::sun::star::uno::Reference< ::com::sun::star::sdbcx::XRowLocate>              m_xBookmarkOperations;
//STRIP001  ::com::sun::star::uno::Reference< ::com::sun::star::sdbcx::XColumnsSupplier>        m_xColumnsSupplier;
//STRIP001  ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet>            m_xPropertyAccess;
//STRIP001
//STRIP001 public:
//STRIP001  // Construction/Destruction
//STRIP001  CursorWrapper() { }
//STRIP001  CursorWrapper(const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XRowSet>& _rxCursor, sal_Bool bUseCloned = sal_False);
//STRIP001  CursorWrapper(const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XResultSet>& _rxCursor, sal_Bool bUseCloned = sal_False);
//STRIP001      // bei bUseCloned == sal_True wird der Cursor ueber das XCloneable-Interface (dass er besitzen muss) gedoubled und
//STRIP001      // erst dann benutzt
//STRIP001
//STRIP001  friend bool operator==(const CursorWrapper& lhs, const CursorWrapper& rhs)
//STRIP001  {
//STRIP001      return lhs.m_xGeneric.get() == rhs.m_xGeneric.get();
//STRIP001  }
//STRIP001
//STRIP001  sal_Bool is() const { return m_xMoveOperations.is(); }
//STRIP001  sal_Bool Is() const { return m_xMoveOperations.is(); }
//STRIP001
//STRIP001  CursorWrapper* operator ->() { return this; }
//STRIP001  operator const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface>& () const{ return m_xGeneric; }
//STRIP001
//STRIP001  // 'Konvertierungen'
//STRIP001  const CursorWrapper& operator=(const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XRowSet>& xCursor);
//STRIP001  operator const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XResultSet>& () const          { return m_xMoveOperations; }
//STRIP001  operator const ::com::sun::star::uno::Reference< ::com::sun::star::sdbcx::XRowLocate>& () const         { return m_xBookmarkOperations; }
//STRIP001  operator const ::com::sun::star::uno::Reference< ::com::sun::star::sdbcx::XColumnsSupplier>& () const   { return m_xColumnsSupplier; }
//STRIP001
//STRIP001  const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >&        getPropertySet() const      { return m_xPropertyAccess; }
//STRIP001  const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XResultSet >&           getResultSet() const        { return m_xMoveOperations; }
//STRIP001  const ::com::sun::star::uno::Reference< ::com::sun::star::sdbcx::XRowLocate >&          getRowLocate() const        { return m_xBookmarkOperations; }
//STRIP001  const ::com::sun::star::uno::Reference< ::com::sun::star::sdbcx::XColumnsSupplier >&    getColumnsSupplier() const  { return m_xColumnsSupplier; }
//STRIP001
//STRIP001  // das normale queryInterface
//STRIP001  virtual ::com::sun::star::uno::Any SAL_CALL queryInterface( const ::com::sun::star::uno::Type& type) throw ( ::com::sun::star::uno::RuntimeException )
//STRIP001  { return m_xMoveOperations->queryInterface(type); }
//STRIP001
//STRIP001  // ::com::sun::star::uno::Reference< ::com::sun::star::sdbcx::XRowLocate>
//STRIP001  ::com::sun::star::uno::Any getBookmark(void)
//STRIP001      throw( ::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException )
//STRIP001  { return m_xBookmarkOperations->getBookmark(); }
//STRIP001  sal_Bool moveToBookmark(const ::com::sun::star::uno::Any& bookmark) throw( ::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException ) { return m_xBookmarkOperations->moveToBookmark(bookmark); }
//STRIP001  sal_Bool moveRelativeToBookmark(const ::com::sun::star::uno::Any& bookmark, sal_Int32 rows) throw( ::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException ) { return m_xBookmarkOperations->moveRelativeToBookmark(bookmark, rows); }
//STRIP001  sal_Int32 compareBookmarks(const ::com::sun::star::uno::Any& first, const ::com::sun::star::uno::Any& second) const throw( ::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException ) { return m_xBookmarkOperations->compareBookmarks(first, second); }
//STRIP001  sal_Int32 hasOrderedBookmarks(void) const throw( ::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException ) { return m_xBookmarkOperations->hasOrderedBookmarks(); }
//STRIP001  sal_Int32 hashBookmark(const ::com::sun::star::uno::Any& bookmark) const throw( ::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException ) { return m_xBookmarkOperations->hashBookmark(bookmark); }
//STRIP001
//STRIP001  // ::com::sun::star::sdbc::XResultSet
//STRIP001  sal_Bool isBeforeFirst() const              { return m_xMoveOperations->isBeforeFirst(); }
//STRIP001  sal_Bool isAfterLast() const                { return m_xMoveOperations->isAfterLast(); }
//STRIP001  sal_Bool isFirst() const                    { return m_xMoveOperations->isFirst(); }
//STRIP001  sal_Bool isLast() const                     { return m_xMoveOperations->isLast(); }
//STRIP001  void beforeFirst()                          { m_xMoveOperations->beforeFirst(); }
//STRIP001  sal_Bool first()                            { return m_xMoveOperations->first(); }
//STRIP001  sal_Bool last()                             { return m_xMoveOperations->last(); }
//STRIP001  sal_Int32 getRow() const                    { return m_xMoveOperations->getRow(); }
//STRIP001  sal_Bool absolute(sal_Int32 nPosition)          { return m_xMoveOperations->absolute(nPosition); }
//STRIP001  sal_Bool relative(sal_Int32 nCount)             { return m_xMoveOperations->relative(nCount); }
//STRIP001  sal_Bool previous()                         { return m_xMoveOperations->previous(); }
//STRIP001  sal_Bool next()                             { return m_xMoveOperations->next(); }
//STRIP001  void refreshRow()                       { m_xMoveOperations->refreshRow(); }
//STRIP001  sal_Bool rowUpdated()                       { return m_xMoveOperations->rowUpdated(); }
//STRIP001  sal_Bool rowInserted()                      { return m_xMoveOperations->rowInserted(); }
//STRIP001  sal_Bool rowDeleted()                       { return m_xMoveOperations->rowDeleted(); }
//STRIP001  ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface> getStatement()         { return m_xMoveOperations->getStatement(); }
//STRIP001  // ::com::sun::star::sdbcx::XColumnsSupplier
//STRIP001  ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameAccess> getColumns() const throw( ::com::sun::star::uno::RuntimeException ) { return m_xColumnsSupplier->getColumns(); }
//STRIP001 private:
//STRIP001  void ImplConstruct(const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XResultSet>& _rxCursor, sal_Bool bUseCloned);
//STRIP001 };


class FmXDisposeMultiplexer;
//STRIP001 class FmXDisposeListener
//STRIP001 {
//STRIP001  friend class FmXDisposeMultiplexer;
//STRIP001
//STRIP001  FmXDisposeMultiplexer*  m_pAdapter;
//STRIP001  ::osl::Mutex&   m_rMutex;
//STRIP001
//STRIP001 public:
//STRIP001  FmXDisposeListener(::osl::Mutex& _rMutex) : m_pAdapter(NULL), m_rMutex(_rMutex) { }
//STRIP001  virtual ~FmXDisposeListener();
//STRIP001
//STRIP001  virtual void disposing(const ::com::sun::star::lang::EventObject& _rEvent, sal_Int16 _nId) throw( ::com::sun::star::uno::RuntimeException ) = 0;
//STRIP001
//STRIP001 protected:
//STRIP001  void setAdapter(FmXDisposeMultiplexer* pAdapter);
//STRIP001 };

typedef ::cppu::WeakImplHelper1< ::com::sun::star::lang::XEventListener> FmXDisposeMultiplexer_x;
//==============================================================================


//STRIP001 class FmXDisposeMultiplexer :public ::cppu::WeakImplHelper1< ::com::sun::star::lang::XEventListener>
//STRIP001 {
//STRIP001  ::com::sun::star::uno::Reference< ::com::sun::star::lang::XComponent>       m_xObject;
//STRIP001  FmXDisposeListener* m_pListener;
//STRIP001  sal_Int16               m_nId;
//STRIP001
//STRIP001  virtual ~FmXDisposeMultiplexer();
//STRIP001 public:
//STRIP001  FmXDisposeMultiplexer(FmXDisposeListener* _pListener, const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XComponent>& _rxObject, sal_Int16 _nId = -1);
//STRIP001
//STRIP001 // ::com::sun::star::lang::XEventListener
//STRIP001  virtual void SAL_CALL disposing( const ::com::sun::star::lang::EventObject& Source ) throw(::com::sun::star::uno::RuntimeException);
//STRIP001
//STRIP001  void dispose();
//STRIP001 };

//  ==================================================================

//==============================================================================
// FmSlotDispatch - some kind of translator between the Sfx-Slots and the UNO-dispatchers
//==============================================================================

typedef ::cppu::WeakImplHelper1< ::com::sun::star::frame::XDispatch >   FmSlotDispatch_x;
class FmSlotDispatch
            :public SfxControllerItem
            ,public ::cppu::WeakImplHelper2< ::com::sun::star::frame::XDispatch, ::com::sun::star::lang::XComponent>
            //  ,public XComponent
{
//STRIP001 protected:
//STRIP001  ::cppu::OInterfaceContainerHelper   m_aDisposeListeners;
//STRIP001  ::cppu::OInterfaceContainerHelper   m_aStatusListeners;
//STRIP001
//STRIP001  Link    m_aExecutor;
//STRIP001  ::com::sun::star::util::URL     m_aUrl;             // the URL we're responsible for
//STRIP001  ::osl::Mutex                    m_aAccessSafety;
//STRIP001  sal_Int16   m_nSlot;            // the slot 'translation' of the URL
//STRIP001
//STRIP001 public:
//STRIP001  const ::com::sun::star::util::URL&  getUrl() const { return m_aUrl; }
//STRIP001  sal_Int16       getSlot() const { return m_nSlot; }
//STRIP001
//STRIP001  void setExecutor(const Link& aExecutor) { m_aExecutor = aExecutor; }
//STRIP001  Link getExecutor() const { return m_aExecutor; }
//STRIP001
//STRIP001 public:
//STRIP001  FmSlotDispatch(const ::com::sun::star::util::URL& rUrl, sal_Int16 nSlotId, SfxBindings& rBindings);
//STRIP001  virtual ~FmSlotDispatch();
//STRIP001
    // force broadcasting the current status
    void    BroadcastCurrentState( );

//STRIP001  // ::com::sun::star::frame::XDispatch
//STRIP001  virtual void SAL_CALL dispatch( const ::com::sun::star::util::URL& aURL, const ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue >& aArgs ) throw(::com::sun::star::uno::RuntimeException);
//STRIP001  virtual void SAL_CALL addStatusListener( const ::com::sun::star::uno::Reference< ::com::sun::star::frame::XStatusListener >& xControl, const ::com::sun::star::util::URL& aURL ) throw(::com::sun::star::uno::RuntimeException);
//STRIP001  virtual void SAL_CALL removeStatusListener( const ::com::sun::star::uno::Reference< ::com::sun::star::frame::XStatusListener >& xControl, const ::com::sun::star::util::URL& aURL ) throw(::com::sun::star::uno::RuntimeException);
//STRIP001
//STRIP001  // XComponent
//STRIP001  virtual void SAL_CALL dispose(  ) throw(::com::sun::star::uno::RuntimeException);
//STRIP001  virtual void SAL_CALL addEventListener( const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XEventListener >& xListener ) throw(::com::sun::star::uno::RuntimeException);
//STRIP001  virtual void SAL_CALL removeEventListener( const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XEventListener >& aListener ) throw(::com::sun::star::uno::RuntimeException);
//STRIP001
//STRIP001 protected:
//STRIP001  // SfxControllerItem
//STRIP001  virtual void StateChanged(USHORT _nSID, SfxItemState _eState, const SfxPoolItem* _pState);
//STRIP001
//STRIP001  ::com::sun::star::frame::FeatureStateEvent BuildEvent(SfxItemState eState, const SfxPoolItem* pState);
//STRIP001
//STRIP001  virtual void NotifyState(SfxItemState eState, const SfxPoolItem* pState, const ::com::sun::star::uno::Reference< ::com::sun::star::frame::XStatusListener>& rListener = ::com::sun::star::uno::Reference< ::com::sun::star::frame::XStatusListener>());
//STRIP001      // the default implementations notifies the given listeners (or all available listeners) with a statusChanged
};

//========================================================================
//= dispatch interception helper classes
//========================================================================

//------------------------------------------------------------------------
//- FmDispatchInterceptor
//------------------------------------------------------------------------
class FmDispatchInterceptor
{
public:
    FmDispatchInterceptor() { }

    virtual ::com::sun::star::uno::Reference< ::com::sun::star::frame::XDispatch> interceptedQueryDispatch(sal_uInt16 _nId,
        const ::com::sun::star::util::URL& aURL, const ::rtl::OUString& aTargetFrameName, sal_Int32 nSearchFlags) throw( ::com::sun::star::uno::RuntimeException ) = 0;

    virtual ::osl::Mutex* getInterceptorMutex() = 0;
};

//------------------------------------------------------------------------
//- FmXDispatchInterceptorImpl
//------------------------------------------------------------------------
typedef ::cppu::WeakComponentImplHelper3<   ::com::sun::star::frame::XDispatchProviderInterceptor
                                        ,   ::com::sun::star::lang::XEventListener
                                        ,   ::com::sun::star::frame::XInterceptorInfo
                                        >   FmXDispatchInterceptorImpl_BASE;

class FmXDispatchInterceptorImpl : public FmXDispatchInterceptorImpl_BASE
{
    ::osl::Mutex                    m_aFallback;
    ::binfilter::form::OImplementationIdsRef    m_aHoldImplIdHelper;//STRIP008  ::form::OImplementationIdsRef   m_aHoldImplIdHelper;

    // the component which's dispatches we're intercepting
    ::com::sun::star::uno::WeakReference< ::com::sun::star::frame::XDispatchProviderInterception>
                    m_xIntercepted;
    sal_Bool        m_bListening;

    // the real interceptor
    FmDispatchInterceptor*          m_pMaster;

    // chaining
    ::com::sun::star::uno::Reference< ::com::sun::star::frame::XDispatchProvider>           m_xSlaveDispatcher;
    ::com::sun::star::uno::Reference< ::com::sun::star::frame::XDispatchProvider>           m_xMasterDispatcher;

    // our id
    sal_Int16                       m_nId;

    ::com::sun::star::uno::Sequence< ::rtl::OUString >
                                    m_aInterceptedURLSchemes;

    virtual ~FmXDispatchInterceptorImpl();

public:
    ::com::sun::star::uno::Reference< ::com::sun::star::frame::XDispatchProviderInterception> getIntercepted() const { return m_xIntercepted; }

public:
    FmXDispatchInterceptorImpl(
        const ::com::sun::star::uno::Reference< ::com::sun::star::frame::XDispatchProviderInterception>& _rToIntercept,
        FmDispatchInterceptor* _pMaster,
        sal_Int16 _nId,
        ::com::sun::star::uno::Sequence< ::rtl::OUString > _rInterceptedSchemes /// if not empty, this will be used for getInterceptedURLs
    );

    // StarOne
    DECLARE_UNO3_DEFAULTS(FmXDispatchInterceptorImpl, FmXDispatchInterceptorImpl_BASE);
    //  virtual ::com::sun::star::uno::Any SAL_CALL queryInterface( const ::com::sun::star::uno::Type& type) throw ( ::com::sun::star::uno::RuntimeException );
    virtual ::com::sun::star::uno::Sequence< sal_Int8 > SAL_CALL getImplementationId() throw(::com::sun::star::uno::RuntimeException);
    //  ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Type > SAL_CALL getTypes(  ) throw(::com::sun::star::uno::RuntimeException);


    // ::com::sun::star::frame::XDispatchProvider
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::frame::XDispatch > SAL_CALL queryDispatch( const ::com::sun::star::util::URL& aURL, const ::rtl::OUString& aTargetFrameName, sal_Int32 nSearchFlags ) throw(::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Reference< ::com::sun::star::frame::XDispatch > > SAL_CALL queryDispatches( const ::com::sun::star::uno::Sequence< ::com::sun::star::frame::DispatchDescriptor >& aDescripts ) throw(::com::sun::star::uno::RuntimeException);

    // ::com::sun::star::frame::XDispatchProviderInterceptor
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::frame::XDispatchProvider > SAL_CALL getSlaveDispatchProvider(  ) throw(::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL setSlaveDispatchProvider( const ::com::sun::star::uno::Reference< ::com::sun::star::frame::XDispatchProvider >& xNewDispatchProvider ) throw(::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::frame::XDispatchProvider > SAL_CALL getMasterDispatchProvider(  ) throw(::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL setMasterDispatchProvider( const ::com::sun::star::uno::Reference< ::com::sun::star::frame::XDispatchProvider >& xNewSupplier ) throw(::com::sun::star::uno::RuntimeException);

    // ::com::sun::star::frame::XInterceptorInfo
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getInterceptedURLs(  ) throw(::com::sun::star::uno::RuntimeException);

    // ::com::sun::star::lang::XEventListener
    virtual void SAL_CALL disposing( const ::com::sun::star::lang::EventObject& Source ) throw(::com::sun::star::uno::RuntimeException);

    // OComponentHelper
    virtual void SAL_CALL disposing();

protected:
    void ImplDetach();

    ::osl::Mutex&       getAccessSafety()
    {
        if (m_pMaster && m_pMaster->getInterceptorMutex())
            return *m_pMaster->getInterceptorMutex();
        return m_aFallback;
    }
};

//==================================================================
// ...
//==================================================================
//STRIP001 ::rtl::OUString  getServiceNameByControlType(sal_Int16 nType);
    // get a service name to create a model of the given type (OBJ_FM_...)
//STRIP001 sal_Int16        getControlTypeByObject(const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XServiceInfo>& _rxObject);
    // get the object type (OBJ_FM_...) from the services the object supports

//STRIP001 void TransferEventScripts(const ::com::sun::star::uno::Reference< ::com::sun::star::awt::XControlModel>& xModel, const ::com::sun::star::uno::Reference< ::com::sun::star::awt::XControl>& xControl,
//STRIP001  const ::com::sun::star::uno::Sequence< ::com::sun::star::script::ScriptEventDescriptor>& rTransferIfAvailable);

//STRIP001 sal_Int16    GridView2ModelPos(const ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexAccess>& rColumns, sal_Int16 nViewPos);

//==================================================================
//STRIP001 sal_Bool isLoadable(const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface>& xLoad);
//STRIP001 sal_Bool isRowSetAlive(const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface>& _rxRowSet);
    // checks if the ::com::sun::star::sdbcx::XColumnsSupplier provided by _rxRowSet supllies any columns

}//end of namespace binfilter
#endif // _SVX_FMTOOLS_HXX

