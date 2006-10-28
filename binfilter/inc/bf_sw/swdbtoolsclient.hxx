/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: swdbtoolsclient.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 04:54:22 $
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
#ifndef _SWDBTOOLSCLIENT_HXX
#define _SWDBTOOLSCLIENT_HXX

#ifndef CONNECTIVITY_VIRTUAL_DBTOOLS_HXX
#include <connectivity/virtualdbtools.hxx>
#endif
#ifndef _OSL_MUTEX_HXX_
#include <osl/mutex.hxx>
#endif
#ifndef _OSL_MODULE_H_
#include <osl/module.h>
#endif
namespace binfilter {

/* -----------------------------30.08.2001 11:01------------------------------
    Client to use the dbtools library as load-on-call
 ---------------------------------------------------------------------------*/
class SwDbtoolsClient
{
private:
    ::rtl::Reference< ::connectivity::simple::IDataAccessTools >            m_xDataAccessTools;
    ::rtl::Reference< ::connectivity::simple::IDataAccessTypeConversion >   m_xAccessTypeConversion;
    ::rtl::Reference< ::connectivity::simple::IDataAccessToolsFactory >     m_xDataAccessFactory;



public:
    SwDbtoolsClient(){DBG_BF_ASSERT(0, "STRIP");} //STRIP001 SwDbtoolsClient();
    ~SwDbtoolsClient(){DBG_BF_ASSERT(0, "STRIP");} //STRIP001 ~SwDbtoolsClient();

    ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XDataSource > getDataSource(
        const ::rtl::OUString& _rsRegisteredName,
        const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory>& _rxFactory
            ){DBG_BF_ASSERT(0, "STRIP"); return NULL;} //STRIP001 );


};

} //namespace binfilter
#endif

