/*************************************************************************
 *
 *  $RCSfile: sqlparserclient.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:22:01 $
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
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc..
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/

#ifndef SVX_SQLPARSERCLIENT_HXX
#define SVX_SQLPARSERCLIENT_HXX

#ifndef SVX_DBTOOLSCLIENT_HXX
#include "dbtoolsclient.hxx"
#endif
#ifndef SVX_QUERYDESIGNCONTEXT_HXX
#include "ParseContext.hxx"
#endif
#ifndef _COM_SUN_STAR_LANG_XMULTISERVICEFACTORY_HPP_
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#endif

//........................................................................
namespace svxform
{
//........................................................................

    //====================================================================
    //= OSQLParserClient
    //====================================================================
    class OSQLParserClient : public ODbtoolsClient
                            ,public ::svxform::OParseContextClient
    {
    private:
        //add by BerryJia for fixing Bug97420 Time:2002-9-12-11:00(PRC time)
        ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory > m_xORB;

    protected:
        mutable ::rtl::Reference< ::connectivity::simple::ISQLParser >  m_xParser;

    protected:
        OSQLParserClient(
            const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& _rxORB);
        //add by BerryJia for fixing Bug97420 Time:2002-9-12-11:00(PRC time)
//STRIP001      void create() const;

    protected:
//STRIP001          inline ::rtl::Reference< ::connectivity::simple::ISQLParseNode > predicateTree(
//STRIP001                  ::rtl::OUString& _rErrorMessage,
//STRIP001                  const ::rtl::OUString& _rStatement,
//STRIP001                  const ::com::sun::star::uno::Reference< ::com::sun::star::util::XNumberFormatter >& _rxFormatter,
//STRIP001                  const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >& _rxField
//STRIP001              ) const
//STRIP001          {
//STRIP001              ::rtl::Reference< ::connectivity::simple::ISQLParseNode > xReturn;
//STRIP001              if (!m_xParser.is())
//STRIP001                  create();
//STRIP001              if (m_xParser.is())
//STRIP001                  xReturn = m_xParser->predicateTree(_rErrorMessage, _rStatement, _rxFormatter, _rxField);
//STRIP001              return xReturn;
//STRIP001          }
    };

//........................................................................
}   // namespace svxform
//........................................................................

#endif // SVX_SQLPARSERCLIENT_HXX


