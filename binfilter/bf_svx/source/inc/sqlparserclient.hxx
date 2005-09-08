/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sqlparserclient.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-08 06:09:44 $
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

#ifndef SVX_SQLPARSERCLIENT_HXX
#define SVX_SQLPARSERCLIENT_HXX

#ifndef SVX_DBTOOLSCLIENT_HXX
#include "dbtoolsclient.hxx"
#endif
#ifndef SVX_QUERYDESIGNCONTEXT_HXX
#include "ParseContext.hxx"
#endif
// auto strip #ifndef _COM_SUN_STAR_LANG_XMULTISERVICEFACTORY_HPP_
// auto strip #include <com/sun/star/lang/XMultiServiceFactory.hpp>
// auto strip #endif
namespace binfilter {

//........................................................................
namespace svxform
{
//........................................................................

    //====================================================================
    //= OSQLParserClient
    //====================================================================
    class OSQLParserClient : public ODbtoolsClient
        ,public ::binfilter::svxform::OParseContextClient//STRIP008                             ,public ::svxform::OParseContextClient
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

}//end of namespace binfilter
#endif // SVX_SQLPARSERCLIENT_HXX


