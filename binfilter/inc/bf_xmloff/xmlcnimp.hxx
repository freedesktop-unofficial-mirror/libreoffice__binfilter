/*************************************************************************
 *
 *  $RCSfile: xmlcnimp.hxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: jmeng $ $Date: 2003-12-04 01:45:46 $
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

#ifndef _XMLOFF_XMLCNIMP_HXX
#define _XMLOFF_XMLCNIMP_HXX

#ifndef _COM_SUN_STAR_CONTAINER_XNAMEACCESS_HPP_
#include <com/sun/star/container/XNameAccess.hpp>
#endif

#ifndef _SVARRAY_HXX
#include <svtools/svarray.hxx>
#endif

#ifndef _XMLOFF_NMSPMAP_HXX
#include <bf_xmloff/nmspmap.hxx>
#endif

#define _SVSTDARR_USHORTS
#include <svtools/svstdarr.hxx>

namespace rtl { class OUString; }
namespace binfilter {

class SvXMLAttrContainerData_Impl;

class SvXMLAttrContainerData
{
    SvXMLNamespaceMap   aNamespaceMap;
    SvUShorts           aPrefixPoss;
    SvXMLAttrContainerData_Impl *pLNames;
    SvXMLAttrContainerData_Impl *pValues;

    inline sal_uInt16 GetPrefixPos( sal_uInt16 i ) const;
public:

    SvXMLAttrContainerData( const SvXMLAttrContainerData& rImpl );
    SvXMLAttrContainerData();
    ~SvXMLAttrContainerData();

    int  operator ==( const SvXMLAttrContainerData& rCmp ) const;

    BOOL AddAttr( const ::rtl::OUString& rLName, const ::rtl::OUString& rValue );
    BOOL AddAttr( const ::rtl::OUString& rPrefix, const ::rtl::OUString& rNamespace,
                    const ::rtl::OUString& rLName, const ::rtl::OUString& rValue );
    BOOL AddAttr( const ::rtl::OUString& rPrefix,
                  const ::rtl::OUString& rLName,
                  const ::rtl::OUString& rValue );

    sal_uInt16 GetAttrCount() const;
    inline ::rtl::OUString GetAttrNamespace( sal_uInt16 i ) const;
    inline ::rtl::OUString GetAttrPrefix( sal_uInt16 i ) const;
    const ::rtl::OUString& GetAttrLName( sal_uInt16 i ) const;
    const ::rtl::OUString& GetAttrValue( sal_uInt16 i ) const;

    sal_uInt16 GetFirstNamespaceIndex() const { return aNamespaceMap.GetFirstIndex(); }
    sal_uInt16 GetNextNamespaceIndex( sal_uInt16 nIdx ) const { return aNamespaceMap.GetNextIndex( nIdx ); }
    inline const ::rtl::OUString& GetNamespace( sal_uInt16 i ) const;
    inline const ::rtl::OUString& GetPrefix( sal_uInt16 i ) const;

    BOOL SetAt( sal_uInt16 i,
                const ::rtl::OUString& rLName, const ::rtl::OUString& rValue );
    BOOL SetAt( sal_uInt16 i,
                const ::rtl::OUString& rPrefix, const ::rtl::OUString& rNamespace,
                const ::rtl::OUString& rLName, const ::rtl::OUString& rValue );
    BOOL SetAt( sal_uInt16 i,
                const ::rtl::OUString& rPrefix,
                const ::rtl::OUString& rLName,
                const ::rtl::OUString& rValue );

    void Remove( sal_uInt16 i );
};

inline sal_uInt16 SvXMLAttrContainerData::GetPrefixPos( sal_uInt16 i ) const
{
//  DBG_ASSERT( i >= 0 && i < aPrefixPoss.Count(),
//              "SvXMLAttrContainerData::GetPrefixPos: illegal index" );
    return aPrefixPoss[i];
}

inline ::rtl::OUString SvXMLAttrContainerData::GetAttrNamespace( sal_uInt16 i ) const
{
    ::rtl::OUString sRet;
    sal_uInt16 nPos = GetPrefixPos( i );
    if( USHRT_MAX != nPos )
        sRet = aNamespaceMap.GetNameByIndex( nPos );
    return sRet;
}

inline ::rtl::OUString SvXMLAttrContainerData::GetAttrPrefix( sal_uInt16 i ) const
{
    ::rtl::OUString sRet;
    sal_uInt16 nPos = GetPrefixPos( i );
    if( USHRT_MAX != nPos )
        sRet = aNamespaceMap.GetPrefixByIndex( nPos );
    return sRet;
}

inline const ::rtl::OUString& SvXMLAttrContainerData::GetNamespace(
                                                            sal_uInt16 i ) const
{
    return aNamespaceMap.GetNameByIndex( i );
}

inline const ::rtl::OUString& SvXMLAttrContainerData::GetPrefix( sal_uInt16 i ) const
{
    return aNamespaceMap.GetPrefixByIndex( i );
}

}//end of namespace binfilter
#endif

