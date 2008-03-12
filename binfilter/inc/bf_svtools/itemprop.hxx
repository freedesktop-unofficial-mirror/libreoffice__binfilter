/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: itemprop.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 12:14:09 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/
#ifndef _SFX_ITEMPROP_HXX
#define _SFX_ITEMPROP_HXX

#include <tools/solar.h>
#include <tools/string.hxx>
#include <bf_svtools/itemset.hxx>
#include <cppuhelper/implbase1.hxx>
#include <com/sun/star/beans/XPropertySetInfo.hpp>
#include <com/sun/star/beans/PropertyState.hpp>
#include <com/sun/star/lang/IllegalArgumentException.hpp>

namespace binfilter
{

/* -----------------------------21.02.00 11:03--------------------------------
    UNO III - Implementation
 ---------------------------------------------------------------------------*/
#define MAP_CHAR_LEN(cchar) cchar, sizeof(cchar) - 1
struct SfxItemPropertyMap
{
    const char*                         pName;
    USHORT                              nNameLen;
    USHORT                              nWID;
    const ::com::sun::star::uno::Type*  pType;
    long                                nFlags;
    BYTE                                nMemberId;

     static const SfxItemPropertyMap*   GetByName(
        const SfxItemPropertyMap *pMap,
        const ::rtl::OUString &rName );
     static const SfxItemPropertyMap*   GetTolerantByName(
        const SfxItemPropertyMap *pMap,
        const ::rtl::OUString &rName );
};
/* -----------------------------21.02.00 11:19--------------------------------

 ---------------------------------------------------------------------------*/
class  SfxItemPropertySet
{
    const SfxItemPropertyMap*   _pMap;
protected:
    virtual BOOL            FillItem(SfxItemSet& rSet, USHORT nWhich, BOOL bGetProperty) const;

public:
                            SfxItemPropertySet( const SfxItemPropertyMap *pMap ) :
                                _pMap(pMap) {}

    void getPropertyValue( const SfxItemPropertyMap& rMap,
                                            const SfxItemSet& rSet,
                                            ::com::sun::star::uno::Any& rAny) const
                                            throw(::com::sun::star::uno::RuntimeException);
    ::com::sun::star::uno::Any
        getPropertyValue( const SfxItemPropertyMap& rMap,
                                            const SfxItemSet& rSet ) const
                                            throw(::com::sun::star::uno::RuntimeException);
    void getPropertyValue( const ::rtl::OUString &rName,
                                            const SfxItemSet& rSet,
                                            ::com::sun::star::uno::Any& rAny) const
                                            throw(::com::sun::star::uno::RuntimeException,
                                                    ::com::sun::star::beans::UnknownPropertyException);
    ::com::sun::star::uno::Any
        getPropertyValue( const ::rtl::OUString &rName,
                                            const SfxItemSet& rSet ) const
                                            throw(::com::sun::star::uno::RuntimeException,
                                                    ::com::sun::star::beans::UnknownPropertyException);
    void                    setPropertyValue( const SfxItemPropertyMap& rMap,
        const ::com::sun::star::uno::Any& aVal,
                                            SfxItemSet& rSet ) const
                                            throw(::com::sun::star::uno::RuntimeException,
                                            ::com::sun::star::lang::IllegalArgumentException);
    void                    setPropertyValue( const ::rtl::OUString& rPropertyName,
        const ::com::sun::star::uno::Any& aVal,
                                            SfxItemSet& rSet ) const
                                            throw(::com::sun::star::uno::RuntimeException,
                                            ::com::sun::star::lang::IllegalArgumentException,
                                                    ::com::sun::star::beans::UnknownPropertyException);

    ::com::sun::star::beans::PropertyState
        getPropertyState(const ::rtl::OUString& rName, const SfxItemSet& rSet)
        throw(::com::sun::star::beans::UnknownPropertyException);
    ::com::sun::star::beans::PropertyState
        getPropertyState(const SfxItemPropertyMap& rMap, const SfxItemSet& rSet)
                                    throw();

    ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySetInfo >
        getPropertySetInfo() const;
    const SfxItemPropertyMap*
        getPropertyMap() const {return _pMap;}

};

class  SfxItemPropertySetInfo : public cppu::WeakImplHelper1< ::com::sun::star::beans::XPropertySetInfo>
{
    const SfxItemPropertyMap*   _pMap;

public:
    SfxItemPropertySetInfo(const SfxItemPropertyMap *pMap ) :
                                _pMap(pMap) {}

    virtual ::com::sun::star::uno::Sequence< ::com::sun::star::beans::Property > SAL_CALL
        getProperties(  )
            throw(::com::sun::star::uno::RuntimeException);

    virtual ::com::sun::star::beans::Property SAL_CALL
        getPropertyByName( const ::rtl::OUString& aName )
            throw(::com::sun::star::beans::UnknownPropertyException,
                    ::com::sun::star::uno::RuntimeException);

    virtual sal_Bool SAL_CALL
        hasPropertyByName( const ::rtl::OUString& Name )
            throw(::com::sun::star::uno::RuntimeException);

    const SfxItemPropertyMap* getMap() const { return _pMap; }

    // XInterface
    virtual ::com::sun::star::uno::Any SAL_CALL queryInterface( const ::com::sun::star::uno::Type& aType ) throw (::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL acquire(  ) throw ();
    virtual void SAL_CALL release(  ) throw ();
};
/* -----------------------------21.02.00 12:01--------------------------------

 ---------------------------------------------------------------------------*/
class  SfxExtItemPropertySetInfo: public cppu::WeakImplHelper1< ::com::sun::star::beans::XPropertySetInfo >
{
    const SfxItemPropertyMap*                                           _pExtMap;
    ::com::sun::star::uno::Sequence< ::com::sun::star::beans::Property>     aPropertySeq;
public:
                            SfxExtItemPropertySetInfo(
                                const SfxItemPropertyMap *pMap,
                                const ::com::sun::star::uno::Sequence< ::com::sun::star::beans::Property>& rPropSeq );

    virtual ::com::sun::star::uno::Sequence< ::com::sun::star::beans::Property > SAL_CALL
        getProperties(  )
            throw(::com::sun::star::uno::RuntimeException);

    virtual ::com::sun::star::beans::Property SAL_CALL
        getPropertyByName( const ::rtl::OUString& aName )
            throw(::com::sun::star::beans::UnknownPropertyException, ::com::sun::star::uno::RuntimeException);

    virtual sal_Bool SAL_CALL
        hasPropertyByName( const ::rtl::OUString& Name )
            throw(::com::sun::star::uno::RuntimeException);

    // XInterface
    virtual ::com::sun::star::uno::Any SAL_CALL queryInterface( const ::com::sun::star::uno::Type& aType ) throw (::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL acquire(  ) throw ();
    virtual void SAL_CALL release(  ) throw ();
};

}

#endif
