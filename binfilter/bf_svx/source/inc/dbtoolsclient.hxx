/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: dbtoolsclient.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 21:07:17 $
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

#ifndef SVX_DBTOOLSCLIENT_HXX
#define SVX_DBTOOLSCLIENT_HXX

#ifndef CONNECTIVITY_VIRTUAL_DBTOOLS_HXX
#include <connectivity/virtualdbtools.hxx>
#endif
#ifndef _OSL_MODULE_H_
#include <osl/module.h>
#endif
#ifndef _SOLAR_H
#include <tools/solar.h>
#endif
namespace binfilter {
//........................................................................
namespace svxform
{
//........................................................................

    //====================================================================
    //= ODbtoolsClient
    //====================================================================
    /** base class for classes which want to use dbtools features with load-on-call
        of the dbtools lib.
    */
    class ODbtoolsClient
    {
    private:
        static  ::osl::Mutex    s_aMutex;
        static  sal_Int32       s_nClients;
        static oslModule        s_hDbtoolsModule;
        static ::connectivity::simple::createDataAccessToolsFactoryFunction
                                s_pFactoryCreationFunc;
        //add by BerryJia for fixing Bug97420 Time:2002-9-12-11:00(PRC time)
        mutable BOOL            m_bCreateAlready;

    private:
        mutable ::rtl::Reference< ::connectivity::simple::IDataAccessToolsFactory > m_xDataAccessFactory;

    protected:
        const ::rtl::Reference< ::connectivity::simple::IDataAccessToolsFactory >&
            getFactory() const { return m_xDataAccessFactory; }

    protected:
        ODbtoolsClient();
        ~ODbtoolsClient();
        //add by BerryJia for fixing Bug97420 Time:2002-9-12-11:00(PRC time)

    private:
    };

    //====================================================================
    //= OStaticDataAccessTools
    //====================================================================
    class OStaticDataAccessTools : public ODbtoolsClient
    {
    protected:
        mutable ::rtl::Reference< ::connectivity::simple::IDataAccessTools >    m_xDataAccessTools;
        //add by BerryJia for fixing Bug97420 Time:2002-9-12-11:00(PRC time)
        void create() const;

        void checkIfLoaded() const;

    public:
        OStaticDataAccessTools();

        ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XConnection> getRowSetConnection(
                const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XRowSet>& _rxRowSet)
                const SAL_THROW ( (::com::sun::star::uno::RuntimeException) );

        // ------------------------------------------------

        // ------------------------------------------------
        ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XDataSource > getDataSource(
                const ::rtl::OUString& _rsRegisteredName,
                const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory>& _rxFactory
            ) const;

        // ------------------------------------------------
        /** check if the property "Privileges" supports ::com::sun::star::sdbcx::Privilege::INSERT
            @param      _rxCursorSet    the property set
        */
        sal_Bool canInsert(const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet>& _rxCursorSet) const;

        // ------------------------------------------------
        /** check if the property "Privileges" supports ::com::sun::star::sdbcx::Privilege::UPDATE
            @param      _rxCursorSet    the property set
        */
        sal_Bool canUpdate(const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet>& _rxCursorSet) const;

        // ------------------------------------------------
        /** check if the property "Privileges" supports ::com::sun::star::sdbcx::Privilege::DELETE
            @param      _rxCursorSet    the property set
        */
        sal_Bool canDelete(const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet>& _rxCursorSet) const;

        // ------------------------------------------------
        virtual ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameAccess >
            getFieldsByCommandDescriptor(
                const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XConnection >& _rxConnection,
                const sal_Int32 _nCommandType,
                const ::rtl::OUString& _rCommand,
                ::com::sun::star::uno::Reference< ::com::sun::star::lang::XComponent >& _rxKeepFieldsAlive,
                ::dbtools::SQLExceptionInfo* _pErrorInfo = NULL
            )   SAL_THROW( ( ) );

        // ------------------------------------------------
        virtual ::com::sun::star::uno::Sequence< ::rtl::OUString >
            getFieldNamesByCommandDescriptor(
                const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XConnection >& _rxConnection,
                const sal_Int32 _nCommandType,
                const ::rtl::OUString& _rCommand,
                ::dbtools::SQLExceptionInfo* _pErrorInfo = NULL
            )   SAL_THROW( ( ) );
    };
//........................................................................
}   // namespace svxform
//........................................................................

}//end of namespace binfilter
#endif // SVX_DBTOOLSCLIENT_HXX


