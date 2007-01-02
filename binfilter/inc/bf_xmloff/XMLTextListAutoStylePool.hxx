/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: XMLTextListAutoStylePool.hxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: hr $ $Date: 2007-01-02 18:51:48 $
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

#ifndef _XMLOFF_XMLTEXTLISTAUTOSTYLEPOOL_HXX
#define _XMLOFF_XMLTEXTLISTAUTOSTYLEPOOL_HXX


#ifndef _COM_SUN_STAR_UCB_XANYCOMPARE_HPP_
#include <com/sun/star/ucb/XAnyCompare.hpp>
#endif

namespace com { namespace sun { namespace star { namespace container {
    class XIndexReplace; } } } }
namespace rtl { class OUString; }
namespace binfilter {

class XMLTextListAutoStylePool_Impl;
class XMLTextListAutoStylePoolNames_Impl;
class XMLTextListAutoStylePoolEntry_Impl;
class SvXMLExport;

class XMLTextListAutoStylePool
{
    SvXMLExport& rExport;

    const ::rtl::OUString sPrefix;

    XMLTextListAutoStylePool_Impl *pPool;
    XMLTextListAutoStylePoolNames_Impl *pNames;
    sal_uInt32 nName;

    /** this is an optional NumRule compare component for applications where
        the NumRules don't have names */
    ::com::sun::star::uno::Reference< ::com::sun::star::ucb::XAnyCompare > mxNumRuleCompare;

    sal_uInt32 Find( XMLTextListAutoStylePoolEntry_Impl* pEntry ) const;
public:

    XMLTextListAutoStylePool( SvXMLExport& rExport );
    ~XMLTextListAutoStylePool();

    void RegisterName( const ::rtl::OUString& rName );

    ::rtl::OUString Add(
            const ::com::sun::star::uno::Reference <
                ::com::sun::star::container::XIndexReplace > & rNumRules );

    ::rtl::OUString Find(
            const ::com::sun::star::uno::Reference <
                ::com::sun::star::container::XIndexReplace > & rNumRules ) const;
    ::rtl::OUString Find( const ::rtl::OUString& rInternalName ) const;

    void exportXML() const;
};

}//end of namespace binfilter
#endif  //  _XMLOFF_XMLTEXTLISTAUTOSTYLEPOOL_HXX
