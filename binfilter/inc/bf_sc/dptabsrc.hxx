/*************************************************************************
 *
 *  $RCSfile: dptabsrc.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 20:46:22 $
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

#ifndef SC_DPTABSRC_HXX
#define SC_DPTABSRC_HXX

// auto strip #ifndef _STRING_HXX //autogen
// auto strip #include <tools/string.hxx>
// auto strip #endif

// auto strip #ifndef _LIST_HXX //autogen wg. List
// auto strip #include <tools/list.hxx>
// auto strip #endif

#ifndef SC_SCGLOB_HXX
#include "global.hxx"       // enum ScSubTotalFunc
#endif

#ifndef _COM_SUN_STAR_SHEET_XDIMENSIONSSUPPLIER_HPP_
#include <com/sun/star/sheet/XDimensionsSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_SHEET_XHIERARCHIESSUPPLIER_HPP_
#include <com/sun/star/sheet/XHierarchiesSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_SHEET_XLEVELSSUPPLIER_HPP_
#include <com/sun/star/sheet/XLevelsSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_SHEET_XMEMBERSSUPPLIER_HPP_
#include <com/sun/star/sheet/XMembersSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_SHEET_XDATAPILOTRESULTS_HPP_
#include <com/sun/star/sheet/XDataPilotResults.hpp>
#endif
#ifndef _COM_SUN_STAR_SHEET_XDATAPILOTMEMBERRESULTS_HPP_
#include <com/sun/star/sheet/XDataPilotMemberResults.hpp>
#endif
// auto strip #ifndef _COM_SUN_STAR_SHEET_MEMBERRESULT_HPP_
// auto strip #include <com/sun/star/sheet/MemberResult.hpp>
// auto strip #endif
#ifndef _COM_SUN_STAR_SHEET_GENERALFUNCTION_HPP_
#include <com/sun/star/sheet/GeneralFunction.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_XREFRESHABLE_HPP_
#include <com/sun/star/util/XRefreshable.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_XCLONEABLE_HPP_
#include <com/sun/star/util/XCloneable.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
#include <com/sun/star/beans/XPropertySet.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_XSERVICEINFO_HPP_
#include <com/sun/star/lang/XServiceInfo.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XNAMED_HPP_
#include <com/sun/star/container/XNamed.hpp>
#endif

#ifndef _CPPUHELPER_IMPLBASE2_HXX_
#include <cppuhelper/implbase2.hxx>
#endif
#ifndef _CPPUHELPER_IMPLBASE3_HXX_
#include <cppuhelper/implbase3.hxx>
#endif
#ifndef _CPPUHELPER_IMPLBASE5_HXX_
#include <cppuhelper/implbase5.hxx>
#endif
namespace binfilter {


class ScDPResultMember;
class ScDPResultData;
struct ScDPItemData;
class ScDPTableData;

// --------------------------------------------------------------------

//  should be dynamic!
#define SC_DAPI_MAXFIELDS   256


// --------------------------------------------------------------------
//
//  implementation of DataPilotSource using ScDPTableData
//


class ScDPDimensions;
class ScDPDimension;
class ScDPHierarchies;
class ScDPHierarchy;
class ScDPLevels;
class ScDPLevel;
class ScDPMembers;
class ScDPMember;


class ScDPSource : public cppu::WeakImplHelper5<
                            ::com::sun::star::sheet::XDimensionsSupplier,
                            ::com::sun::star::sheet::XDataPilotResults,
                            ::com::sun::star::util::XRefreshable,
                            ::com::sun::star::beans::XPropertySet,
                            ::com::sun::star::lang::XServiceInfo >
{
private:
    ScDPTableData*          pData;              // data source
    ScDPDimensions*         pDimensions;        // api objects
                                                // settings:
    long                    nColDims[SC_DAPI_MAXFIELDS];
    long                    nRowDims[SC_DAPI_MAXFIELDS];
    long                    nDataDims[SC_DAPI_MAXFIELDS];
    long                    nPageDims[SC_DAPI_MAXFIELDS];
    long                    nColDimCount;
    long                    nRowDimCount;
    long                    nDataDimCount;
    long                    nPageDimCount;
    BOOL                    bColumnGrand;
    BOOL                    bRowGrand;
    BOOL                    bIgnoreEmptyRows;
    BOOL                    bRepeatIfEmpty;

    long                    nDupCount;

                                                // results:
    ScDPResultData*         pResData;           // keep the rest in this!
    ScDPResultMember*       pColResRoot;
    ScDPResultMember*       pRowResRoot;
    ::com::sun::star::uno::Sequence< ::com::sun::star::sheet::MemberResult>* pColResults;
    ::com::sun::star::uno::Sequence< ::com::sun::star::sheet::MemberResult>* pRowResults;
    List                    aColLevelList;
    List                    aRowLevelList;
    ScSubTotalFunc          eDataFunctions[SC_DAPI_MAXFIELDS];
    BOOL                    bResultOverflow;

//STRIP001  void                    CreateRes_Impl();
//STRIP001  void                    FillMemberResults();
//STRIP001  void                    FillLevelList( USHORT nOrientation, List& rList );

//STRIP001  void                    SetDupCount( long nNew );

public:
                                ScDPSource( ScDPTableData* pD );    // TableData is deleted by Source
    virtual                     ~ScDPSource();

    ScDPTableData*          GetData()       { return pData; }
    const ScDPTableData*    GetData() const { return pData; }

    USHORT                  GetOrientation(long nColumn);
    void                    SetOrientation(long nColumn, USHORT nNew);
    long                    GetPosition(long nColumn);

//STRIP001  long                    GetDataDimensionCount();
//STRIP001  String                  GetDataDimName(long nIndex);
    BOOL                    IsDataLayoutDimension(long nDim);
//STRIP001  USHORT                  GetDataLayoutOrientation();

    BOOL                    IsDateDimension(long nDim);

    BOOL                    SubTotalAllowed(long nColumn);      //! move to ScDPResultData

//STRIP001  ScDPDimension*          AddDuplicated(long nSource, const String& rNewName);
    long                    GetDupCount() const { return nDupCount; }

    long                    GetSourceDim(long nDim);

//STRIP001  const ::com::sun::star::uno::Sequence< ::com::sun::star::sheet::MemberResult>*
//STRIP001                          GetMemberResults( ScDPLevel* pLevel );

    ScDPDimensions*         GetDimensionsObject();

                            // XDimensionsSupplier
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameAccess >
                            SAL_CALL getDimensions(  )
                                throw(::com::sun::star::uno::RuntimeException);

                            // XDataPilotResults
    virtual ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Sequence<
                            ::com::sun::star::sheet::DataResult > > SAL_CALL getResults(  )
                                throw(::com::sun::star::uno::RuntimeException);

                            // XRefreshable
    virtual void SAL_CALL   refresh() throw(::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL   addRefreshListener( const ::com::sun::star::uno::Reference<
                                    ::com::sun::star::util::XRefreshListener >& l )
                                throw(::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL   removeRefreshListener( const ::com::sun::star::uno::Reference<
                                    ::com::sun::star::util::XRefreshListener >& l )
                                throw(::com::sun::star::uno::RuntimeException);

                            // XPropertySet
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySetInfo >
                            SAL_CALL getPropertySetInfo(  )
                                throw(::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL   setPropertyValue( const ::rtl::OUString& aPropertyName,
                                    const ::com::sun::star::uno::Any& aValue )
                                throw(::com::sun::star::beans::UnknownPropertyException,
                                    ::com::sun::star::beans::PropertyVetoException,
                                    ::com::sun::star::lang::IllegalArgumentException,
                                    ::com::sun::star::lang::WrappedTargetException,
                                    ::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Any SAL_CALL getPropertyValue(
                                    const ::rtl::OUString& PropertyName )
                                throw(::com::sun::star::beans::UnknownPropertyException,
                                    ::com::sun::star::lang::WrappedTargetException,
                                    ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL   addPropertyChangeListener( const ::rtl::OUString& aPropertyName,
                                    const ::com::sun::star::uno::Reference<
                                        ::com::sun::star::beans::XPropertyChangeListener >& xListener )
                                throw(::com::sun::star::beans::UnknownPropertyException,
                                    ::com::sun::star::lang::WrappedTargetException,
                                    ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL   removePropertyChangeListener( const ::rtl::OUString& aPropertyName,
                                    const ::com::sun::star::uno::Reference<
                                        ::com::sun::star::beans::XPropertyChangeListener >& aListener )
                                throw(::com::sun::star::beans::UnknownPropertyException,
                                    ::com::sun::star::lang::WrappedTargetException,
                                    ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL   addVetoableChangeListener( const ::rtl::OUString& PropertyName,
                                    const ::com::sun::star::uno::Reference<
                                        ::com::sun::star::beans::XVetoableChangeListener >& aListener )
                                throw(::com::sun::star::beans::UnknownPropertyException,
                                    ::com::sun::star::lang::WrappedTargetException,
                                    ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL   removeVetoableChangeListener( const ::rtl::OUString& PropertyName,
                                    const ::com::sun::star::uno::Reference<
                                        ::com::sun::star::beans::XVetoableChangeListener >& aListener )
                                throw(::com::sun::star::beans::UnknownPropertyException,
                                    ::com::sun::star::lang::WrappedTargetException,
                                    ::com::sun::star::uno::RuntimeException);

                            // XServiceInfo
    virtual ::rtl::OUString SAL_CALL getImplementationName(  )
                                throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ServiceName )
                                throw(::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames()
                                throw(::com::sun::star::uno::RuntimeException);

//STRIP001  virtual String              getDataDescription();       //! ???

    virtual BOOL                getColumnGrand() const;
    virtual void                setColumnGrand(BOOL bSet);
    virtual BOOL                getRowGrand() const;
    virtual void                setRowGrand(BOOL bSet);

    virtual BOOL                getIgnoreEmptyRows() const;
    virtual void                setIgnoreEmptyRows(BOOL bSet);
    virtual BOOL                getRepeatIfEmpty() const;
    virtual void                setRepeatIfEmpty(BOOL bSet);

//STRIP001  virtual void                validate();     //! ???
//STRIP001  virtual void                disposeData();
};

class ScDPDimensions : public cppu::WeakImplHelper2<
                            ::com::sun::star::container::XNameAccess,
                            ::com::sun::star::lang::XServiceInfo >
{
private:
    ScDPSource*         pSource;
    long                nDimCount;
    ScDPDimension**     ppDims;

public:
                            ScDPDimensions( ScDPSource* pSrc );
    virtual                 ~ScDPDimensions();

//STRIP001  void                    CountChanged();

                            // XNameAccess
    virtual ::com::sun::star::uno::Any SAL_CALL getByName( const ::rtl::OUString& aName )
                                throw(::com::sun::star::container::NoSuchElementException,
                                    ::com::sun::star::lang::WrappedTargetException,
                                    ::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getElementNames()
                                throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL hasByName( const ::rtl::OUString& aName )
                                throw(::com::sun::star::uno::RuntimeException);

                            // XElementAccess
    virtual ::com::sun::star::uno::Type SAL_CALL getElementType()
                                throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL hasElements() throw(::com::sun::star::uno::RuntimeException);

                            // XServiceInfo
    virtual ::rtl::OUString SAL_CALL getImplementationName(  )
                                throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ServiceName )
                                throw(::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames()
                                throw(::com::sun::star::uno::RuntimeException);

    virtual long            getCount() const;
    virtual ScDPDimension*  getByIndex(long nIndex) const;
};

class ScDPDimension : public cppu::WeakImplHelper5<
                            ::com::sun::star::sheet::XHierarchiesSupplier,
                            ::com::sun::star::container::XNamed,
                            ::com::sun::star::util::XCloneable,
                            ::com::sun::star::beans::XPropertySet,
                            ::com::sun::star::lang::XServiceInfo >
{
private:
    ScDPSource*         pSource;
    long                nDim;
    ScDPHierarchies*    pHierarchies;
    long                nUsedHier;
    USHORT              nFunction;          // enum GeneralFunction
    String              aName;              // if empty, take from source
    long                nSourceDim;         // >=0 if dup'ed

public:
                            ScDPDimension( ScDPSource* pSrc, long nD );
    virtual                 ~ScDPDimension();

    long                    GetSourceDim() const    { return nSourceDim; }

//STRIP001  ScDPDimension*          CreateCloneObject();
    ScDPHierarchies*        GetHierarchiesObject();

                            // XNamed
    virtual ::rtl::OUString SAL_CALL getName() throw(::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL   setName( const ::rtl::OUString& aName )
                                throw(::com::sun::star::uno::RuntimeException);

                            // XHierarchiesSupplier
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameAccess > SAL_CALL
                            getHierarchies() throw(::com::sun::star::uno::RuntimeException);

                            // XCloneable
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::util::XCloneable > SAL_CALL
                            createClone() throw(::com::sun::star::uno::RuntimeException);

                            // XPropertySet
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySetInfo >
                            SAL_CALL getPropertySetInfo(  )
                                throw(::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL   setPropertyValue( const ::rtl::OUString& aPropertyName,
                                    const ::com::sun::star::uno::Any& aValue )
                                throw(::com::sun::star::beans::UnknownPropertyException,
                                    ::com::sun::star::beans::PropertyVetoException,
                                    ::com::sun::star::lang::IllegalArgumentException,
                                    ::com::sun::star::lang::WrappedTargetException,
                                    ::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Any SAL_CALL getPropertyValue(
                                    const ::rtl::OUString& PropertyName )
                                throw(::com::sun::star::beans::UnknownPropertyException,
                                    ::com::sun::star::lang::WrappedTargetException,
                                    ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL   addPropertyChangeListener( const ::rtl::OUString& aPropertyName,
                                    const ::com::sun::star::uno::Reference<
                                        ::com::sun::star::beans::XPropertyChangeListener >& xListener )
                                throw(::com::sun::star::beans::UnknownPropertyException,
                                    ::com::sun::star::lang::WrappedTargetException,
                                    ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL   removePropertyChangeListener( const ::rtl::OUString& aPropertyName,
                                    const ::com::sun::star::uno::Reference<
                                        ::com::sun::star::beans::XPropertyChangeListener >& aListener )
                                throw(::com::sun::star::beans::UnknownPropertyException,
                                    ::com::sun::star::lang::WrappedTargetException,
                                    ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL   addVetoableChangeListener( const ::rtl::OUString& PropertyName,
                                    const ::com::sun::star::uno::Reference<
                                        ::com::sun::star::beans::XVetoableChangeListener >& aListener )
                                throw(::com::sun::star::beans::UnknownPropertyException,
                                    ::com::sun::star::lang::WrappedTargetException,
                                    ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL   removeVetoableChangeListener( const ::rtl::OUString& PropertyName,
                                    const ::com::sun::star::uno::Reference<
                                        ::com::sun::star::beans::XVetoableChangeListener >& aListener )
                                throw(::com::sun::star::beans::UnknownPropertyException,
                                    ::com::sun::star::lang::WrappedTargetException,
                                    ::com::sun::star::uno::RuntimeException);

                            // XServiceInfo
    virtual ::rtl::OUString SAL_CALL getImplementationName(  )
                                throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ServiceName )
                                throw(::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames()
                                throw(::com::sun::star::uno::RuntimeException);

    virtual USHORT              getOrientation() const;
    virtual void                setOrientation(USHORT nNew);
    virtual long                getPosition() const;
//STRIP001  virtual void                setPosition(long nNew);
    virtual BOOL                getIsDataLayoutDimension() const;
    virtual USHORT              getFunction() const;
    virtual void                setFunction(USHORT nNew);       // for data dimension
    virtual long                getUsedHierarchy() const;
//STRIP001  virtual void                setUsedHierarchy(long nNew);
//STRIP001  virtual BOOL                isDuplicated() const;
};

class ScDPHierarchies : public cppu::WeakImplHelper2<
                            ::com::sun::star::container::XNameAccess,
                            ::com::sun::star::lang::XServiceInfo >
{
private:
    ScDPSource*         pSource;
    long                nDim;
    long                nHierCount;
    ScDPHierarchy**     ppHiers;

public:
                            ScDPHierarchies( ScDPSource* pSrc, long nD );
    virtual                 ~ScDPHierarchies();

                            // XNameAccess
    virtual ::com::sun::star::uno::Any SAL_CALL getByName( const ::rtl::OUString& aName )
                                throw(::com::sun::star::container::NoSuchElementException,
                                    ::com::sun::star::lang::WrappedTargetException,
                                    ::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getElementNames()
                                throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL hasByName( const ::rtl::OUString& aName )
                                throw(::com::sun::star::uno::RuntimeException);

                            // XElementAccess
    virtual ::com::sun::star::uno::Type SAL_CALL getElementType()
                                throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL hasElements() throw(::com::sun::star::uno::RuntimeException);

                            // XServiceInfo
    virtual ::rtl::OUString SAL_CALL getImplementationName(  )
                                throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ServiceName )
                                throw(::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames()
                                throw(::com::sun::star::uno::RuntimeException);

    virtual long            getCount() const;
    virtual ScDPHierarchy*  getByIndex(long nIndex) const;
};

class ScDPHierarchy : public cppu::WeakImplHelper3<
                            ::com::sun::star::sheet::XLevelsSupplier,
                            ::com::sun::star::container::XNamed,
                            ::com::sun::star::lang::XServiceInfo >
{
private:
    ScDPSource*     pSource;
    long            nDim;
    long            nHier;
    ScDPLevels*     pLevels;

public:
                            ScDPHierarchy( ScDPSource* pSrc, long nD, long nH );
    virtual                 ~ScDPHierarchy();

    ScDPLevels*             GetLevelsObject();

                            // XNamed
    virtual ::rtl::OUString SAL_CALL getName() throw(::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL   setName( const ::rtl::OUString& aName )
                                throw(::com::sun::star::uno::RuntimeException);

                            // XLevelsSupplier
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameAccess > SAL_CALL
                            getLevels() throw(::com::sun::star::uno::RuntimeException);

                            // XServiceInfo
    virtual ::rtl::OUString SAL_CALL getImplementationName(  )
                                throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ServiceName )
                                throw(::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames()
                                throw(::com::sun::star::uno::RuntimeException);
};

class ScDPLevels : public cppu::WeakImplHelper2<
                            ::com::sun::star::container::XNameAccess,
                            ::com::sun::star::lang::XServiceInfo >
{
private:
    ScDPSource*     pSource;
    long            nDim;
    long            nHier;
    long            nLevCount;
    ScDPLevel**     ppLevs;

public:
                            ScDPLevels( ScDPSource* pSrc, long nD, long nH );
    virtual                 ~ScDPLevels();

                            // XNameAccess
    virtual ::com::sun::star::uno::Any SAL_CALL getByName( const ::rtl::OUString& aName )
                                throw(::com::sun::star::container::NoSuchElementException,
                                    ::com::sun::star::lang::WrappedTargetException,
                                    ::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getElementNames()
                                throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL hasByName( const ::rtl::OUString& aName )
                                throw(::com::sun::star::uno::RuntimeException);

                            // XElementAccess
    virtual ::com::sun::star::uno::Type SAL_CALL getElementType()
                                throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL hasElements() throw(::com::sun::star::uno::RuntimeException);

                            // XServiceInfo
    virtual ::rtl::OUString SAL_CALL getImplementationName(  )
                                throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ServiceName )
                                throw(::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames()
                                throw(::com::sun::star::uno::RuntimeException);

    virtual long            getCount() const;
    virtual ScDPLevel*      getByIndex(long nIndex) const;
};

class ScDPLevel : public cppu::WeakImplHelper5<
                            ::com::sun::star::sheet::XMembersSupplier,
                            ::com::sun::star::container::XNamed,
                            ::com::sun::star::sheet::XDataPilotMemberResults,
                            ::com::sun::star::beans::XPropertySet,
                            ::com::sun::star::lang::XServiceInfo >
{
private:
    ScDPSource*                 pSource;
    long                        nDim;
    long                        nHier;
    long                        nLev;
    ScDPMembers*                pMembers;
    ::com::sun::star::uno::Sequence< ::com::sun::star::sheet::GeneralFunction> aSubTotals;
    BOOL                        bShowEmpty;

public:
                            ScDPLevel( ScDPSource* pSrc, long nD, long nH, long nL );
    virtual                 ~ScDPLevel();

//STRIP001  ScDPMembers*            GetMembersObject();

                            // XNamed
    virtual ::rtl::OUString SAL_CALL getName() throw(::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL   setName( const ::rtl::OUString& aName )
                                throw(::com::sun::star::uno::RuntimeException);

                            // XMembersSupplier
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameAccess > SAL_CALL
                            getMembers() throw(::com::sun::star::uno::RuntimeException);

                            // XDataPilotMemberResults
    virtual ::com::sun::star::uno::Sequence< ::com::sun::star::sheet::MemberResult > SAL_CALL
                            getResults() throw(::com::sun::star::uno::RuntimeException);

                            // XPropertySet
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySetInfo >
                            SAL_CALL getPropertySetInfo(  )
                                throw(::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL   setPropertyValue( const ::rtl::OUString& aPropertyName,
                                    const ::com::sun::star::uno::Any& aValue )
                                throw(::com::sun::star::beans::UnknownPropertyException,
                                    ::com::sun::star::beans::PropertyVetoException,
                                    ::com::sun::star::lang::IllegalArgumentException,
                                    ::com::sun::star::lang::WrappedTargetException,
                                    ::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Any SAL_CALL getPropertyValue(
                                    const ::rtl::OUString& PropertyName )
                                throw(::com::sun::star::beans::UnknownPropertyException,
                                    ::com::sun::star::lang::WrappedTargetException,
                                    ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL   addPropertyChangeListener( const ::rtl::OUString& aPropertyName,
                                    const ::com::sun::star::uno::Reference<
                                        ::com::sun::star::beans::XPropertyChangeListener >& xListener )
                                throw(::com::sun::star::beans::UnknownPropertyException,
                                    ::com::sun::star::lang::WrappedTargetException,
                                    ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL   removePropertyChangeListener( const ::rtl::OUString& aPropertyName,
                                    const ::com::sun::star::uno::Reference<
                                        ::com::sun::star::beans::XPropertyChangeListener >& aListener )
                                throw(::com::sun::star::beans::UnknownPropertyException,
                                    ::com::sun::star::lang::WrappedTargetException,
                                    ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL   addVetoableChangeListener( const ::rtl::OUString& PropertyName,
                                    const ::com::sun::star::uno::Reference<
                                        ::com::sun::star::beans::XVetoableChangeListener >& aListener )
                                throw(::com::sun::star::beans::UnknownPropertyException,
                                    ::com::sun::star::lang::WrappedTargetException,
                                    ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL   removeVetoableChangeListener( const ::rtl::OUString& PropertyName,
                                    const ::com::sun::star::uno::Reference<
                                        ::com::sun::star::beans::XVetoableChangeListener >& aListener )
                                throw(::com::sun::star::beans::UnknownPropertyException,
                                    ::com::sun::star::lang::WrappedTargetException,
                                    ::com::sun::star::uno::RuntimeException);

                            // XServiceInfo
    virtual ::rtl::OUString SAL_CALL getImplementationName(  )
                                throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ServiceName )
                                throw(::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames()
                                throw(::com::sun::star::uno::RuntimeException);

    virtual ::com::sun::star::uno::Sequence< ::com::sun::star::sheet::GeneralFunction> getSubTotals() const;
//STRIP001  virtual void            setSubTotals(const ::com::sun::star::uno::Sequence<
//STRIP001                                          ::com::sun::star::sheet::GeneralFunction>& rNew);
//STRIP001  virtual BOOL            getShowEmpty() const;
    virtual void            setShowEmpty(BOOL bSet);

    //! number format (for data fields and date fields)
};

//STRIP001 class ScDPMembers : public cppu::WeakImplHelper2<
//STRIP001                          ::com::sun::star::container::XNameAccess,
//STRIP001                          ::com::sun::star::lang::XServiceInfo >
//STRIP001 {
//STRIP001 private:
//STRIP001  ScDPSource*     pSource;
//STRIP001  long            nDim;
//STRIP001  long            nHier;
//STRIP001  long            nLev;
//STRIP001  long            nMbrCount;
//STRIP001  ScDPMember**    ppMbrs;
//STRIP001
//STRIP001 public:
//STRIP001                          ScDPMembers( ScDPSource* pSrc, long nD, long nH, long nL );
//STRIP001  virtual                 ~ScDPMembers();
//STRIP001
//STRIP001                          // XNameAccess
//STRIP001  virtual ::com::sun::star::uno::Any SAL_CALL getByName( const ::rtl::OUString& aName )
//STRIP001                              throw(::com::sun::star::container::NoSuchElementException,
//STRIP001                                  ::com::sun::star::lang::WrappedTargetException,
//STRIP001                                  ::com::sun::star::uno::RuntimeException);
//STRIP001  virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getElementNames()
//STRIP001                              throw(::com::sun::star::uno::RuntimeException);
//STRIP001  virtual sal_Bool SAL_CALL hasByName( const ::rtl::OUString& aName )
//STRIP001                              throw(::com::sun::star::uno::RuntimeException);
//STRIP001
//STRIP001                          // XElementAccess
//STRIP001  virtual ::com::sun::star::uno::Type SAL_CALL getElementType()
//STRIP001                              throw(::com::sun::star::uno::RuntimeException);
//STRIP001  virtual sal_Bool SAL_CALL hasElements() throw(::com::sun::star::uno::RuntimeException);
//STRIP001
//STRIP001                          // XServiceInfo
//STRIP001  virtual ::rtl::OUString SAL_CALL getImplementationName(  )
//STRIP001                              throw(::com::sun::star::uno::RuntimeException);
//STRIP001  virtual sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ServiceName )
//STRIP001                              throw(::com::sun::star::uno::RuntimeException);
//STRIP001  virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames()
//STRIP001                              throw(::com::sun::star::uno::RuntimeException);
//STRIP001
//STRIP001  virtual long            getCount() const;
//STRIP001  virtual ScDPMember*     getByIndex(long nIndex) const;
//STRIP001
//STRIP001  long                    getMinMembers() const;
//STRIP001 };

//STRIP001 class ScDPMember : public cppu::WeakImplHelper3<
//STRIP001                          ::com::sun::star::container::XNamed,
//STRIP001                          ::com::sun::star::beans::XPropertySet,
//STRIP001                          ::com::sun::star::lang::XServiceInfo >
//STRIP001 {
//STRIP001 private:
//STRIP001  ScDPSource*     pSource;
//STRIP001  long            nDim;
//STRIP001  long            nHier;
//STRIP001  long            nLev;
//STRIP001
//STRIP001  String          aName;              // name for api etc.
//STRIP001 //   String          aCaption;           // visible name (changeable by user)
//STRIP001  double          fValue;             // used internally for matching
//STRIP001  BOOL            bHasValue;          // TRUE if this is a value
//STRIP001
//STRIP001  BOOL            bVisible;
//STRIP001  BOOL            bShowDet;
//STRIP001
//STRIP001 public:
//STRIP001                          ScDPMember( ScDPSource* pSrc, long nD, long nH, long nL,
//STRIP001                                          const String& rN, double fV, BOOL bHV );
//STRIP001  virtual                 ~ScDPMember();
//STRIP001
//STRIP001  BOOL                    IsNamedItem( const ScDPItemData& r ) const;
//STRIP001  String                  GetNameStr() const;
//STRIP001
//STRIP001                          // XNamed
//STRIP001  virtual ::rtl::OUString SAL_CALL getName() throw(::com::sun::star::uno::RuntimeException);
//STRIP001  virtual void SAL_CALL   setName( const ::rtl::OUString& aName )
//STRIP001                              throw(::com::sun::star::uno::RuntimeException);
//STRIP001
//STRIP001                          // XPropertySet
//STRIP001  virtual ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySetInfo >
//STRIP001                          SAL_CALL getPropertySetInfo(  )
//STRIP001                              throw(::com::sun::star::uno::RuntimeException);
//STRIP001  virtual void SAL_CALL   setPropertyValue( const ::rtl::OUString& aPropertyName,
//STRIP001                                  const ::com::sun::star::uno::Any& aValue )
//STRIP001                              throw(::com::sun::star::beans::UnknownPropertyException,
//STRIP001                                  ::com::sun::star::beans::PropertyVetoException,
//STRIP001                                  ::com::sun::star::lang::IllegalArgumentException,
//STRIP001                                  ::com::sun::star::lang::WrappedTargetException,
//STRIP001                                  ::com::sun::star::uno::RuntimeException);
//STRIP001  virtual ::com::sun::star::uno::Any SAL_CALL getPropertyValue(
//STRIP001                                  const ::rtl::OUString& PropertyName )
//STRIP001                              throw(::com::sun::star::beans::UnknownPropertyException,
//STRIP001                                  ::com::sun::star::lang::WrappedTargetException,
//STRIP001                                  ::com::sun::star::uno::RuntimeException);
//STRIP001  virtual void SAL_CALL   addPropertyChangeListener( const ::rtl::OUString& aPropertyName,
//STRIP001                                  const ::com::sun::star::uno::Reference<
//STRIP001                                      ::com::sun::star::beans::XPropertyChangeListener >& xListener )
//STRIP001                              throw(::com::sun::star::beans::UnknownPropertyException,
//STRIP001                                  ::com::sun::star::lang::WrappedTargetException,
//STRIP001                                  ::com::sun::star::uno::RuntimeException);
//STRIP001  virtual void SAL_CALL   removePropertyChangeListener( const ::rtl::OUString& aPropertyName,
//STRIP001                                  const ::com::sun::star::uno::Reference<
//STRIP001                                      ::com::sun::star::beans::XPropertyChangeListener >& aListener )
//STRIP001                              throw(::com::sun::star::beans::UnknownPropertyException,
//STRIP001                                  ::com::sun::star::lang::WrappedTargetException,
//STRIP001                                  ::com::sun::star::uno::RuntimeException);
//STRIP001  virtual void SAL_CALL   addVetoableChangeListener( const ::rtl::OUString& PropertyName,
//STRIP001                                  const ::com::sun::star::uno::Reference<
//STRIP001                                      ::com::sun::star::beans::XVetoableChangeListener >& aListener )
//STRIP001                              throw(::com::sun::star::beans::UnknownPropertyException,
//STRIP001                                  ::com::sun::star::lang::WrappedTargetException,
//STRIP001                                  ::com::sun::star::uno::RuntimeException);
//STRIP001  virtual void SAL_CALL   removeVetoableChangeListener( const ::rtl::OUString& PropertyName,
//STRIP001                                  const ::com::sun::star::uno::Reference<
//STRIP001                                      ::com::sun::star::beans::XVetoableChangeListener >& aListener )
//STRIP001                              throw(::com::sun::star::beans::UnknownPropertyException,
//STRIP001                                  ::com::sun::star::lang::WrappedTargetException,
//STRIP001                                  ::com::sun::star::uno::RuntimeException);
//STRIP001
//STRIP001                          // XServiceInfo
//STRIP001  virtual ::rtl::OUString SAL_CALL getImplementationName(  )
//STRIP001                              throw(::com::sun::star::uno::RuntimeException);
//STRIP001  virtual sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ServiceName )
//STRIP001                              throw(::com::sun::star::uno::RuntimeException);
//STRIP001  virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames()
//STRIP001                              throw(::com::sun::star::uno::RuntimeException);
//STRIP001
//STRIP001  virtual BOOL            getIsVisible() const;
//STRIP001  virtual void            setIsVisible(BOOL bSet);
//STRIP001  virtual BOOL            getShowDetails() const;
//STRIP001  virtual void            setShowDetails(BOOL bSet);
//STRIP001 };


} //namespace binfilter
#endif

