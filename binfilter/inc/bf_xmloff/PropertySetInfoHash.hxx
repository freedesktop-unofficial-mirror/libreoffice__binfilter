/*************************************************************************
 *
 *  $RCSfile: PropertySetInfoHash.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: aw $ $Date: 2003-12-05 09:17:48 $
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
#ifndef _XMLOFF_PROPERTYSETINFOHASH_HXX
#define _XMLOFF_PROPERTYSETINFOHASH_HXX

#ifndef _XMLOFF_PROPERTYSETINFOKEY_HXX
#include <bf_xmloff/PropertySetInfoKey.hxx>
#endif
namespace binfilter {

struct PropertySetInfoHash
{
    inline size_t operator()( const PropertySetInfoKey& r ) const;
    inline bool operator()( const PropertySetInfoKey& r1,
                               const PropertySetInfoKey& r2 ) const;
};

inline size_t PropertySetInfoHash::operator()(
        const PropertySetInfoKey& r ) const
{
    const sal_Int32* pBytesAsInt32Array =
        (const sal_Int32*)r.aImplementationId.getConstArray();
    sal_Int32 nId32 =   pBytesAsInt32Array[0] ^
                        pBytesAsInt32Array[1] ^
                        pBytesAsInt32Array[2] ^
                        pBytesAsInt32Array[3];
    return (size_t)nId32 ^ (size_t)r.xPropInfo.get();
}

inline bool PropertySetInfoHash::operator()(
        const PropertySetInfoKey& r1,
        const PropertySetInfoKey& r2 ) const
{
    if( r1.xPropInfo != r2.xPropInfo )
        return sal_False;

    const sal_Int8* pId1 = r1.aImplementationId.getConstArray();
    const sal_Int8* pId2 = r2.aImplementationId.getConstArray();
    return memcmp( pId1, pId2, 16 * sizeof( sal_Int8 ) ) == 0;
}
}//end of namespace binfilter
#endif
