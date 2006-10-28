/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xmlcnitm.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 04:31:49 $
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

#ifndef _SVX_XMLCNITM_HXX
#define _SVX_XMLCNITM_HXX

#ifndef _SFXPOOLITEM_HXX
#include <svtools/poolitem.hxx>
#endif
namespace rtl { class OUString; }
namespace binfilter {
class SvXMLNamespaceMap;
class SvXMLAttrContainerData;
//STRIP008 namespace rtl { class OUString; }

//============================================================================


class SvXMLAttrContainerItem: public SfxPoolItem
{
    SvXMLAttrContainerData  *pImpl;

public:
    TYPEINFO();

    SvXMLAttrContainerItem( sal_uInt16 nWhich = 0 );
    SvXMLAttrContainerItem( const SvXMLAttrContainerItem& );
    virtual ~SvXMLAttrContainerItem();

    virtual int operator==( const SfxPoolItem& ) const;


    virtual sal_uInt16 GetVersion( sal_uInt16 nFileFormatVersion ) const;

    virtual BOOL             QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;
    virtual BOOL             PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 );

    virtual SfxPoolItem *Clone( SfxItemPool * = 0) const
    { return new SvXMLAttrContainerItem( *this ); }

    sal_Bool AddAttr( const ::rtl::OUString& rLName,
                          const ::rtl::OUString& rValue );
    sal_Bool AddAttr( const ::rtl::OUString& rPrefix,
                          const ::rtl::OUString& rNamespace,
                          const ::rtl::OUString& rLName,
                          const ::rtl::OUString& rValue );

    sal_uInt16 GetAttrCount() const;
    ::rtl::OUString GetAttrNamespace( sal_uInt16 i ) const;
    ::rtl::OUString GetAttrPrefix( sal_uInt16 i ) const;
    const ::rtl::OUString& GetAttrLName( sal_uInt16 i ) const;
    const ::rtl::OUString& GetAttrValue( sal_uInt16 i ) const;

    sal_uInt16 GetFirstNamespaceIndex() const;
    sal_uInt16 GetNextNamespaceIndex( sal_uInt16 nIdx ) const;
    const ::rtl::OUString& GetNamespace( sal_uInt16 i ) const;
    const ::rtl::OUString& GetPrefix( sal_uInt16 i ) const;
};

}//end of namespace binfilter
#endif //  _SVX_XMLCNITM_HXX

