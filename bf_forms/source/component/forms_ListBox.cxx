/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */

#include <comphelper/proparrhlp.hxx>

#include "ListBox.hxx"
#include "property.hrc"
#include "services.hxx"
#include "frm_resource.hxx"
#include "frm_resource.hrc"
#include "BaseListBox.hxx"
#include <comphelper/container.hxx>
#include <comphelper/numbers.hxx>
#include <connectivity/dbconversion.hxx>

#include <com/sun/star/util/XNumberFormatTypes.hpp>
#include <com/sun/star/container/XIndexAccess.hpp>
#include <com/sun/star/sdb/XSQLQueryComposerFactory.hpp>
#include <com/sun/star/sdb/XQueriesSupplier.hpp>
#include <com/sun/star/util/NumberFormat.hpp>
#include <com/sun/star/awt/XListBox.hpp>
#include <com/sun/star/awt/XWindow.hpp>
#include <com/sun/star/sdbc/XConnection.hpp>
#include <com/sun/star/sdb/CommandType.hpp>
#include <connectivity/dbtools.hxx>
#include <vcl/svapp.hxx>

#include <com/sun/star/form/FormComponentType.hpp>

#include <com/sun/star/beans/PropertyAttribute.hpp>

#include <comphelper/property.hxx>

#include <com/sun/star/sdbcx/XColumnsSupplier.hpp>

namespace binfilter {


//.........................................................................
namespace frm
{
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::sdb;
using namespace ::com::sun::star::sdbc;
using namespace ::com::sun::star::sdbcx;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::form;
using namespace ::com::sun::star::awt;
using namespace ::com::sun::star::io;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::util;
using namespace ::dbtools;

//==================================================================
//= OListBoxModel
//==================================================================
sal_Int32 OListBoxModel::nSelectHandle = -1;
//------------------------------------------------------------------
InterfaceRef SAL_CALL OListBoxModel_CreateInstance(const Reference<XMultiServiceFactory>& _rxFactory) throw (RuntimeException)
{
    return *(new OListBoxModel(_rxFactory));
}

//------------------------------------------------------------------------------
Sequence< Type> OListBoxModel::_getTypes()
{
    return ::comphelper::concatSequences(
        OBoundControlModel::_getTypes(),
        OListBoxModel_BASE::getTypes(),
        OErrorBroadcaster::getTypes()
    );
}


DBG_NAME(OListBoxModel)
//------------------------------------------------------------------
OListBoxModel::OListBoxModel(const Reference<XMultiServiceFactory>& _rxFactory)
    :OBoundControlModel(_rxFactory, VCL_CONTROLMODEL_LISTBOX, FRM_CONTROL_LISTBOX)
                                    // use the old control name for compytibility reasons
    ,OErrorBroadcaster( OComponentHelper::rBHelper )
    ,m_aRefreshListeners(m_aMutex)
    ,m_nNULLPos(-1)
    ,m_bBoundComponent(sal_False)
{
    DBG_CTOR(OListBoxModel,NULL);

    m_nClassId = FormComponentType::LISTBOX;
    m_eListSourceType = ListSourceType_VALUELIST;
    m_aBoundColumn <<= (sal_Int16)1;
    m_sDataFieldConnectivityProperty = PROPERTY_SELECT_SEQ;
    if (OListBoxModel::nSelectHandle == -1)
        OListBoxModel::nSelectHandle = getOriginalHandle(PROPERTY_ID_SELECT_SEQ);
}

//------------------------------------------------------------------
OListBoxModel::OListBoxModel( const OListBoxModel* _pOriginal, const Reference<XMultiServiceFactory>& _rxFactory )
    :OBoundControlModel( _pOriginal, _rxFactory )
    ,OErrorBroadcaster( OComponentHelper::rBHelper )
    ,m_aRefreshListeners( m_aMutex )
    ,m_nNULLPos(-1)
    ,m_bBoundComponent(sal_False)
{
    DBG_CTOR(OListBoxModel,NULL);
    m_eListSourceType = _pOriginal->m_eListSourceType;
    m_aBoundColumn = _pOriginal->m_aBoundColumn;
}

//------------------------------------------------------------------
OListBoxModel::~OListBoxModel()
{
    if (!OComponentHelper::rBHelper.bDisposed)
    {
        acquire();
        dispose();
    }

    DBG_DTOR(OListBoxModel,NULL);
}

// XCloneable
//------------------------------------------------------------------------------
IMPLEMENT_DEFAULT_CLONING( OListBoxModel )

// XServiceInfo
//------------------------------------------------------------------------------
StringSequence SAL_CALL OListBoxModel::getSupportedServiceNames() throw(RuntimeException)
{
    StringSequence aSupported = OBoundControlModel::getSupportedServiceNames();
    aSupported.realloc(aSupported.getLength() + 2);

    ::rtl::OUString* pArray = aSupported.getArray();
    pArray[aSupported.getLength()-2] = FRM_SUN_COMPONENT_DATABASE_LISTBOX;
    pArray[aSupported.getLength()-1] = FRM_SUN_COMPONENT_LISTBOX;
    return aSupported;
}

//------------------------------------------------------------------------------
Any SAL_CALL OListBoxModel::queryAggregation(const Type& _rType) throw (RuntimeException)
{
    Any aReturn = OBoundControlModel::queryAggregation( _rType );
    if ( !aReturn.hasValue() )
        aReturn = OListBoxModel_BASE::queryInterface( _rType );
    if ( !aReturn.hasValue() )
        aReturn = OErrorBroadcaster::queryInterface( _rType );
    return aReturn;
}

// OComponentHelper
//------------------------------------------------------------------------------
void OListBoxModel::disposing()
{
    EventObject aEvt( static_cast< XWeak* >( this ) );
    m_aRefreshListeners.disposeAndClear(aEvt);

    OBoundControlModel::disposing();
    OErrorBroadcaster::disposing();
}

// XRefreshable
//------------------------------------------------------------------------------
void SAL_CALL OListBoxModel::addRefreshListener(const Reference<XRefreshListener>& _rxListener) throw(RuntimeException)
{
    m_aRefreshListeners.addInterface(_rxListener);
}

//------------------------------------------------------------------------------
void SAL_CALL OListBoxModel::removeRefreshListener(const Reference<XRefreshListener>& _rxListener) throw(RuntimeException)
{
    m_aRefreshListeners.removeInterface(_rxListener);
}

//------------------------------------------------------------------------------
void SAL_CALL OListBoxModel::refresh() throw(RuntimeException)
{
    {
        ::osl::MutexGuard aGuard(m_aMutex);
        if (m_eListSourceType != ListSourceType_VALUELIST)
        {
            if (getField().is())
                m_aValueSeq = StringSequence();

            if (m_xCursor.is())
                loadData();
        }
    }

    EventObject aEvt(static_cast< XWeak*>(this));
    m_aRefreshListeners.notifyEach(&XRefreshListener::refreshed, aEvt);
}

//------------------------------------------------------------------------------
void OListBoxModel::getFastPropertyValue(Any& _rValue, sal_Int32 _nHandle) const
{
    switch (_nHandle)
    {
        case PROPERTY_ID_BOUNDCOLUMN:
            _rValue <<= m_aBoundColumn;
            break;

        case PROPERTY_ID_LISTSOURCETYPE:
            _rValue <<= m_eListSourceType;
            break;

        case PROPERTY_ID_LISTSOURCE:
            _rValue <<= m_aListSourceSeq;
            break;

        case PROPERTY_ID_VALUE_SEQ:
            _rValue <<= m_aValueSeq;
            break;

        case PROPERTY_ID_DEFAULT_SELECT_SEQ:
            _rValue <<= m_aDefaultSelectSeq;
            break;

        default:
            OBoundControlModel::getFastPropertyValue(_rValue, _nHandle);
    }
}

//------------------------------------------------------------------------------
void OListBoxModel::setFastPropertyValue_NoBroadcast(sal_Int32 _nHandle, const Any& _rValue) throw (com::sun::star::uno::Exception)
{
    switch (_nHandle)
    {
        case PROPERTY_ID_BOUNDCOLUMN :
            DBG_ASSERT((_rValue.getValueType().getTypeClass() == TypeClass_SHORT) || (_rValue.getValueType().getTypeClass() == TypeClass_VOID),
                "OListBoxModel::setFastPropertyValue_NoBroadcast : invalid type !" );
            m_aBoundColumn = _rValue;
            break;

        case PROPERTY_ID_LISTSOURCETYPE :
            DBG_ASSERT(_rValue.getValueType().equals(::getCppuType(reinterpret_cast<ListSourceType*>(NULL))),
                "OComboBoxModel::setFastPropertyValue_NoBroadcast : invalid type !" );
            _rValue >>= m_eListSourceType;
            break;

        case PROPERTY_ID_LISTSOURCE :
            DBG_ASSERT(_rValue.getValueType().equals(::getCppuType(reinterpret_cast<StringSequence*>(NULL))),
                "OListBoxModel::setFastPropertyValue_NoBroadcast : invalid type !" );
            _rValue >>= m_aListSourceSeq;

            if (m_eListSourceType == ListSourceType_VALUELIST)
                m_aValueSeq = m_aListSourceSeq;
            else if (m_xCursor.is() && !getField().is()) // Listbox bereits mit Datenbank verbunden
                // Aenderung der Datenquelle -> neu laden
                loadData();

            break;

        case PROPERTY_ID_VALUE_SEQ :
            DBG_ASSERT(_rValue.getValueType().equals(::getCppuType(reinterpret_cast<StringSequence*>(NULL))),
                "OListBoxModel::setFastPropertyValue_NoBroadcast : invalid type !" );
            _rValue >>= m_aValueSeq;
            break;

        case PROPERTY_ID_DEFAULT_SELECT_SEQ :
            DBG_ASSERT(_rValue.getValueType().equals(::getCppuType(reinterpret_cast< Sequence<sal_Int16>*>(NULL))),
                "OListBoxModel::setFastPropertyValue_NoBroadcast : invalid type !" );
            _rValue >>= m_aDefaultSelectSeq;

            DBG_ASSERT(m_xAggregateFastSet.is(), "OListBoxModel::setFastPropertyValue_NoBroadcast(DEFAULT_SELECT_SEQ) : invalid aggregate !");
            if (m_xAggregateFastSet.is())
            {   // release our mutex once (it's acquired in the calling method !), as setting aggregate properties
                // may cause any uno controls belonging to us to lock the solar mutex, which is potentially dangerous with
                // our own mutex locked
                MutexRelease aRelease(m_aMutex);
                m_xAggregateFastSet->setFastPropertyValue(OListBoxModel::nSelectHandle, _rValue);
            }
            break;

        default:
            OBoundControlModel::setFastPropertyValue_NoBroadcast(_nHandle, _rValue);
    }

//  if (PROPERTY_ID_STRINGITEMLIST == _nHandle)
//      _reset();
}

//------------------------------------------------------------------------------
sal_Bool OListBoxModel::convertFastPropertyValue(
            Any& _rConvertedValue, Any& _rOldValue, sal_Int32 _nHandle, const Any& _rValue)
                        throw (IllegalArgumentException)
{
    sal_Bool bModified(sal_False);
    switch (_nHandle)
    {
        case PROPERTY_ID_BOUNDCOLUMN :
            bModified = tryPropertyValue(_rConvertedValue, _rOldValue, _rValue, m_aBoundColumn, ::getCppuType(reinterpret_cast<sal_Int16*>(NULL)));
            break;

        case PROPERTY_ID_LISTSOURCETYPE:
            bModified = tryPropertyValueEnum(_rConvertedValue, _rOldValue, _rValue, m_eListSourceType);
            break;

        case PROPERTY_ID_LISTSOURCE:
            bModified = tryPropertyValue(_rConvertedValue, _rOldValue, _rValue, m_aListSourceSeq);
            break;

        case PROPERTY_ID_VALUE_SEQ :
            bModified = tryPropertyValue(_rConvertedValue, _rOldValue, _rValue, m_aValueSeq);
            break;

        case PROPERTY_ID_DEFAULT_SELECT_SEQ :
            bModified = tryPropertyValue(_rConvertedValue, _rOldValue, _rValue, m_aDefaultSelectSeq);
            break;

        default:
            return OBoundControlModel::convertFastPropertyValue(_rConvertedValue, _rOldValue, _nHandle, _rValue);
    }
    return bModified;
}

//------------------------------------------------------------------------------
Reference<XPropertySetInfo> SAL_CALL OListBoxModel::getPropertySetInfo() throw(RuntimeException)
{
        Reference<XPropertySetInfo> xInfo( createPropertySetInfo( getInfoHelper() ) );
    return xInfo;
}

//------------------------------------------------------------------------------
cppu::IPropertyArrayHelper& OListBoxModel::getInfoHelper()
{
    return *const_cast<OListBoxModel*>(this)->getArrayHelper();
}

//------------------------------------------------------------------------------
void OListBoxModel::fillProperties(
                Sequence< Property >& _rProps,
                Sequence< Property >& _rAggregateProps ) const
{
    FRM_BEGIN_PROP_HELPER(13)
        DECL_PROP2(CLASSID,             sal_Int16,                      READONLY, TRANSIENT);
        DECL_PROP1(NAME,                ::rtl::OUString,                BOUND);
        DECL_PROP1(TAG,                 ::rtl::OUString,                BOUND);
        DECL_PROP1(TABINDEX,            sal_Int16,                      BOUND);
        DECL_PROP2(BOUNDCOLUMN,         sal_Int16,                      BOUND, MAYBEVOID);
        DECL_PROP1(LISTSOURCETYPE,      ListSourceType,                 BOUND);
        DECL_PROP1(LISTSOURCE,          StringSequence,                 BOUND);
        DECL_PROP3(VALUE_SEQ,           StringSequence,                 BOUND, READONLY, TRANSIENT);
        DECL_PROP1(DEFAULT_SELECT_SEQ,  Sequence<sal_Int16>,            BOUND);
        DECL_PROP1(CONTROLSOURCE,       ::rtl::OUString,                BOUND);
        DECL_IFACE_PROP3(BOUNDFIELD,    XPropertySet,                   BOUND,READONLY, TRANSIENT);
        DECL_IFACE_PROP2(CONTROLLABEL,  XPropertySet,                   BOUND, MAYBEVOID);
        DECL_PROP2(CONTROLSOURCEPROPERTY,   rtl::OUString,              READONLY, TRANSIENT);
    FRM_END_PROP_HELPER();
}

//------------------------------------------------------------------------------
::rtl::OUString SAL_CALL OListBoxModel::getServiceName() throw(RuntimeException)
{
    return FRM_COMPONENT_LISTBOX;   // old (non-sun) name for compatibility !
}

//------------------------------------------------------------------------------
void SAL_CALL OListBoxModel::write(const Reference<stario::XObjectOutputStream>& _rxOutStream)
    throw(stario::IOException, RuntimeException)
{
    OBoundControlModel::write(_rxOutStream);

    // Dummy-Seq, um Kompatible zu bleiben, wenn SelectSeq nicht mehr gespeichert wird
    Sequence<sal_Int16> aDummySeq;

    // Version
    // Version 0x0002: ListSource wird StringSeq
    _rxOutStream->writeShort(0x0004);

    // Maskierung fuer any
    sal_uInt16 nAnyMask = 0;
    if (m_aBoundColumn.getValueType().getTypeClass() != TypeClass_VOID)
        nAnyMask |= BOUNDCOLUMN;

    _rxOutStream << nAnyMask;

    _rxOutStream << m_aListSourceSeq;
    _rxOutStream << (sal_Int16)m_eListSourceType;
    _rxOutStream << aDummySeq;
    _rxOutStream << m_aDefaultSelectSeq;

    if ((nAnyMask & BOUNDCOLUMN) == BOUNDCOLUMN)
    {
        sal_Int16 nBoundColumn(0);
        m_aBoundColumn >>= nBoundColumn;
        _rxOutStream << nBoundColumn;
    }
    writeHelpTextCompatibly(_rxOutStream);

    // from version 0x0004 : common properties
    writeCommonProperties(_rxOutStream);
}

//------------------------------------------------------------------------------
void SAL_CALL OListBoxModel::read(const Reference<stario::XObjectInputStream>& _rxInStream) throw(stario::IOException, RuntimeException)
{
    // Bei manchen Variblen muessen Abhaengigkeiten beruecksichtigt werden.
    // Deshalb muessen sie explizit ueber setPropertyValue() gesetzt werden.

    OBoundControlModel::read(_rxInStream);
    ::osl::MutexGuard aGuard(m_aMutex);

    // Version
    sal_uInt16 nVersion = _rxInStream->readShort();
    DBG_ASSERT(nVersion > 0, "OListBoxModel::read : version 0 ? this should never have been written !");

    if (nVersion > 0x0004)
    {
        OSL_FAIL("OListBoxModel::read : invalid (means unknown) version !");
        m_aListSourceSeq.realloc(0);
        m_aBoundColumn <<= (sal_Int16)0;
        m_aValueSeq.realloc(0);
        m_eListSourceType = ListSourceType_VALUELIST;
        m_aDefaultSelectSeq.realloc(0);
        defaultCommonProperties();
        return;
    }

    // Maskierung fuer any
    sal_uInt16 nAnyMask;
    _rxInStream >> nAnyMask;

    // ListSourceSeq
    StringSequence aListSourceSeq;
    if (nVersion == 0x0001)
    {
        // ListSourceSeq aus String zusammenstellen;
        ::rtl::OUString sListSource;
        _rxInStream >> sListSource;

        sal_Int32 nTokens = 1;
        const sal_Unicode* pStr = sListSource.getStr();
        while ( *pStr )
        {
            if ( *pStr == ';' )
                nTokens++;
            pStr++;
        }
        aListSourceSeq.realloc( nTokens );
        for (sal_uInt16 i=0; i<nTokens; ++i)
        {
            sal_Int32 nTmp = 0;
            aListSourceSeq.getArray()[i] = sListSource.getToken(i,';',nTmp);
        }
    }
    else
        _rxInStream >> aListSourceSeq;

    sal_Int16 nListSourceType;
    _rxInStream >> nListSourceType;
    m_eListSourceType = (ListSourceType)nListSourceType;
    Any aListSourceSeqAny;
    aListSourceSeqAny <<= aListSourceSeq;

    setFastPropertyValue(PROPERTY_ID_LISTSOURCE, aListSourceSeqAny );

    // Dummy-Seq, um Kompatible zu bleiben, wenn SelectSeq nicht mehr gespeichert wird
    Sequence<sal_Int16> aDummySeq;
    _rxInStream >> aDummySeq;

    // DefaultSelectSeq
    Sequence<sal_Int16> aDefaultSelectSeq;
    _rxInStream >> aDefaultSelectSeq;
    Any aDefaultSelectSeqAny;
    aDefaultSelectSeqAny <<= aDefaultSelectSeq;
    setFastPropertyValue(PROPERTY_ID_DEFAULT_SELECT_SEQ, aDefaultSelectSeqAny);

    // BoundColumn
    if ((nAnyMask & BOUNDCOLUMN) == BOUNDCOLUMN)
    {
        sal_Int16 nValue;
        _rxInStream >> nValue;
        m_aBoundColumn <<= nValue;
    }

    if (nVersion > 2)
        readHelpTextCompatibly(_rxInStream);

    // Stringliste muss gelehrt werden, wenn nicht ueber WerteListe gefuellt wird
    // dieses kann der Fall sein wenn im alive modus gespeichert wird
    if (m_eListSourceType != ListSourceType_VALUELIST && m_xAggregateSet.is())
    {
        StringSequence aSequence;
        setFastPropertyValue(PROPERTY_ID_STRINGITEMLIST, makeAny(aSequence));
    }

    if (nVersion > 3)
        readCommonProperties(_rxInStream);

//  // Nach dem Lesen die Defaultwerte anzeigen
//  if (m_aControlSource.getLength())
//      // (not if we don't have a control source - the "State" property acts like it is persistent, then
//      _reset();
}

//------------------------------------------------------------------------------
void OListBoxModel::loadData()
{
    OSL_ENSURE( false, "OListBoxModel::loadData: dead code!?" );
}

//==================================================================
// OListBoxControl
//==================================================================

//------------------------------------------------------------------
InterfaceRef SAL_CALL OListBoxControl_CreateInstance(const Reference<XMultiServiceFactory>& _rxFactory) throw (RuntimeException)
{
    return *(new OListBoxControl(_rxFactory));
}

//------------------------------------------------------------------------------
Sequence< Type> OListBoxControl::_getTypes()
{
    static Sequence< Type> aTypes;
    if (!aTypes.getLength())
        aTypes = concatSequences(OBoundControl::_getTypes(), OListBoxControl_BASE::getTypes());
    return aTypes;
}

//------------------------------------------------------------------
Any SAL_CALL OListBoxControl::queryAggregation(const Type& _rType) throw (RuntimeException)
{
    Any aReturn = OBoundControl::queryAggregation(_rType);
    if (!aReturn.hasValue())
        aReturn = OListBoxControl_BASE::queryInterface(_rType);

    return aReturn;
}

DBG_NAME(OListBoxControl)
//------------------------------------------------------------------------------
OListBoxControl::OListBoxControl(const Reference<XMultiServiceFactory>& _rxFactory)
                  :OBoundControl(_rxFactory, VCL_CONTROL_LISTBOX)
                  ,m_aChangeListeners(m_aMutex)
{
    DBG_CTOR(OListBoxControl,NULL);

    increment(m_refCount);
    {
        // als FocusListener anmelden
        Reference<XWindow> xComp;
        if (query_aggregation(m_xAggregate, xComp))
            xComp->addFocusListener(this);

        // als ItemListener anmelden
        Reference<XListBox> xListbox;
        if (query_aggregation(m_xAggregate, xListbox))
            xListbox->addItemListener(this);
    }
    // Refcount bei 2 fuer angemeldete Listener
    decrement(m_refCount);

    m_aChangeTimer.SetTimeout(500);
    m_aChangeTimer.SetTimeoutHdl(LINK(this,OListBoxControl,OnTimeout));
}

//------------------------------------------------------------------------------
OListBoxControl::~OListBoxControl()
{
    if (!OComponentHelper::rBHelper.bDisposed)
    {
        acquire();
        dispose();
    }

    DBG_DTOR(OListBoxControl,NULL);
}

//------------------------------------------------------------------------------
StringSequence SAL_CALL OListBoxControl::getSupportedServiceNames() throw(RuntimeException)
{
    StringSequence aSupported = OBoundControl::getSupportedServiceNames();
    aSupported.realloc(aSupported.getLength() + 1);

    ::rtl::OUString* pArray = aSupported.getArray();
    pArray[aSupported.getLength()-1] = FRM_SUN_CONTROL_LISTBOX;
    return aSupported;
}


// XFocusListener
//------------------------------------------------------------------------------
void SAL_CALL OListBoxControl::focusGained(const FocusEvent& /*_rEvent*/) throw(RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    if (m_aChangeListeners.getLength()) // only if there are listeners
    {
        Reference<XPropertySet> xSet(getModel(), UNO_QUERY);
        if (xSet.is())
        {
            // memorize the current selection for posting the change event
            m_aCurrentSelection = xSet->getPropertyValue(PROPERTY_SELECT_SEQ);
        }
    }
}

//------------------------------------------------------------------------------
void SAL_CALL OListBoxControl::focusLost(const FocusEvent& /*_rEvent*/) throw(RuntimeException)
{
    m_aCurrentSelection.clear();
}

// XItemListener
//------------------------------------------------------------------------------
void SAL_CALL OListBoxControl::itemStateChanged(const ItemEvent& /*_rEvent*/) throw(RuntimeException)
{
   // call the changelistener delayed
   ::osl::ClearableMutexGuard aGuard(m_aMutex);
   if (m_aChangeTimer.IsActive())
   {
        Reference<XPropertySet> xSet(getModel(), UNO_QUERY);
        m_aCurrentSelection = xSet->getPropertyValue(PROPERTY_SELECT_SEQ);

        m_aChangeTimer.Stop();
        m_aChangeTimer.Start();
   }
   else
   {
       if (m_aChangeListeners.getLength() && m_aCurrentSelection.hasValue())
       {
            Reference<XPropertySet> xSet(getModel(), UNO_QUERY);
            if (xSet.is())
            {
                // Has the selection been changed?
                sal_Bool bModified(sal_False);
                Any aValue = xSet->getPropertyValue(PROPERTY_SELECT_SEQ);

                Sequence<sal_Int16>& rSelection = *(Sequence<sal_Int16> *)aValue.getValue();
                Sequence<sal_Int16>& rOldSelection = *(Sequence<sal_Int16> *)m_aCurrentSelection.getValue();
                sal_Int32 nLen = rSelection.getLength();
                if (nLen != rOldSelection.getLength())
                    bModified = sal_True;
                else
                {
                    const sal_Int16* pVal = rSelection.getConstArray();
                    const sal_Int16* pCompVal = rOldSelection.getConstArray();

                    while (nLen-- && !bModified)
                        bModified = pVal[nLen] != pCompVal[nLen];
                }

                if (bModified)
                {
                    m_aCurrentSelection = aValue;
                    m_aChangeTimer.Start();
                }
            }
        }
        else if (m_aCurrentSelection.hasValue())
            m_aCurrentSelection.clear();
   }
}

// XEventListener
//------------------------------------------------------------------------------
void SAL_CALL OListBoxControl::disposing(const EventObject& _rSource) throw (RuntimeException)
{
    OBoundControl::disposing(_rSource);
}

// XChangeBroadcaster
//------------------------------------------------------------------------------
void SAL_CALL OListBoxControl::addChangeListener(const Reference<XChangeListener>& _rxListener) throw(RuntimeException)
{
    m_aChangeListeners.addInterface(_rxListener);
}

//------------------------------------------------------------------------------
void SAL_CALL OListBoxControl::removeChangeListener(const Reference<XChangeListener>& _rxListener) throw(RuntimeException)
{
    m_aChangeListeners.removeInterface(_rxListener);
}

// OComponentHelper
//------------------------------------------------------------------------------
void OListBoxControl::disposing()
{
    if (m_aChangeTimer.IsActive())
        m_aChangeTimer.Stop();

    EventObject aEvt(static_cast< XWeak*>(this));
    m_aChangeListeners.disposeAndClear(aEvt);

    OBoundControl::disposing();
}

//------------------------------------------------------------------------------
IMPL_LINK(OListBoxControl, OnTimeout, void*, EMPTYARG)
{
    EventObject aEvt(static_cast< XWeak*>(this));
    m_aChangeListeners.notifyEach(&XChangeListener::changed, aEvt);
    return 1;
}

//.........................................................................
}
//.........................................................................

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
