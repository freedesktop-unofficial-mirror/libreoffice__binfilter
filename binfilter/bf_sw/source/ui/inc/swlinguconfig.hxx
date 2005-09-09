/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: swlinguconfig.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 05:53:27 $
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
#ifndef _SWLINGUCONFIG_HXX
#define _SWLINGUCONFIG_HXX

#ifndef _COM_SUN_STAR_UNO_ANY_H_
#include <com/sun/star/uno/Any.h>
#endif

// auto strip #ifndef _RTL_USTRING_HXX_
// auto strip #include <rtl/ustring.hxx>
// auto strip #endif
class SvtLinguConfig;
struct SvtLinguOptions;
namespace binfilter {

// predeclarations


// #107253#
class SwLinguConfig
{
public:
    SwLinguConfig();
    ~SwLinguConfig();

    sal_Bool SetProperty(const ::rtl::OUString &rPropertyName, const ::com::sun::star::uno::Any &rValue);
    sal_Bool GetOptions(SvtLinguOptions &rOptions) const;
    ::com::sun::star::uno::Any GetProperty(const ::rtl::OUString &rPropertyName) const;
};

} //namespace binfilter
#endif // _SWLINGUCONFIG_HXX
