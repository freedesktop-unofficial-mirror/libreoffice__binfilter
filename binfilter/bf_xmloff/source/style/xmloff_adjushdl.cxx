/*************************************************************************
 *
 *  $RCSfile: xmloff_adjushdl.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 20:12:21 $
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

#ifndef _XMLOFF_PROPERTYHANDLER_ADJUSTTYPES_HXX
#include <adjushdl.hxx>
#endif

#ifndef _SOLAR_H
#include <tools/solar.h>
#endif

// auto strip #ifndef _XMLOFF_XMLTOKEN_HXX
// auto strip #include "xmltoken.hxx"
// auto strip #endif

#ifndef _XMLOFF_XMLUCONV_HXX
#include "xmluconv.hxx"
#endif

#ifndef _RTL_USTRBUF_HXX_
#include <rtl/ustrbuf.hxx>
#endif

#ifndef _COM_SUN_STAR_STYLE_PARAGRAPHADJUST_HPP_
#include <com/sun/star/style/ParagraphAdjust.hpp>
#endif

// auto strip #ifndef _COM_SUN_STAR_UNO_ANY_HXX_
// auto strip #include <com/sun/star/uno/Any.hxx>
// auto strip #endif

// auto strip #ifndef _XMLOFF_XMLEMENT_HXX
// auto strip #include "xmlelement.hxx"
// auto strip #endif
namespace binfilter {

using namespace ::com::sun::star;
using namespace ::rtl;
using namespace ::binfilter::xmloff::token;

SvXMLEnumMapEntry __READONLY_DATA pXML_Para_Adjust_Enum[] =
{
    { XML_START,        style::ParagraphAdjust_LEFT },
    { XML_END,          style::ParagraphAdjust_RIGHT },
    { XML_CENTER,       style::ParagraphAdjust_CENTER },
    { XML_JUSTIFY,      style::ParagraphAdjust_BLOCK },
    { XML_JUSTIFIED,    style::ParagraphAdjust_BLOCK }, // obsolete
    { XML_TOKEN_INVALID, 0 }
};

SvXMLEnumMapEntry __READONLY_DATA pXML_Para_Align_Last_Enum[] =
{
    { XML_START,        style::ParagraphAdjust_LEFT },
    { XML_CENTER,       style::ParagraphAdjust_CENTER },
    { XML_JUSTIFY,      style::ParagraphAdjust_BLOCK },
    { XML_JUSTIFIED,    style::ParagraphAdjust_BLOCK }, // obsolete
    { XML_TOKEN_INVALID, 0 }
};

///////////////////////////////////////////////////////////////////////////////
//
// class XMLParaAdjustPropHdl
//

XMLParaAdjustPropHdl::~XMLParaAdjustPropHdl()
{
    // nothing to do
}

sal_Bool XMLParaAdjustPropHdl::importXML( const OUString& rStrImpValue, uno::Any& rValue, const SvXMLUnitConverter& rUnitConverter ) const
{
    sal_Bool bRet = sal_False;
    sal_uInt16 eAdjust;

    if( ( bRet = rUnitConverter.convertEnum( eAdjust, rStrImpValue, pXML_Para_Adjust_Enum ) ) )
        rValue <<= (sal_Int16)eAdjust;

    return bRet;
}

sal_Bool XMLParaAdjustPropHdl::exportXML( OUString& rStrExpValue, const uno::Any& rValue, const SvXMLUnitConverter& rUnitConverter ) const
{
    if(!rValue.hasValue())
        return sal_False;     //added by BerryJia for fixing Bug102407 2002-11-5
    OUStringBuffer aOut;
    sal_Int16 nVal;

    rValue >>= nVal;

    sal_Bool bRet = rUnitConverter.convertEnum( aOut, nVal, pXML_Para_Adjust_Enum, XML_START );

    rStrExpValue = aOut.makeStringAndClear();

    return bRet;
}

///////////////////////////////////////////////////////////////////////////////
//
// class XMLLastLineAdjustPropHdl
//

XMLLastLineAdjustPropHdl::~XMLLastLineAdjustPropHdl()
{
    // nothing to do
}

sal_Bool XMLLastLineAdjustPropHdl::importXML( const OUString& rStrImpValue, uno::Any& rValue, const SvXMLUnitConverter& rUnitConverter ) const
{
    sal_Bool bRet = sal_False;
    sal_uInt16 eAdjust;

    if( ( bRet = rUnitConverter.convertEnum( eAdjust, rStrImpValue, pXML_Para_Align_Last_Enum ) ) )
        rValue <<= (sal_Int16)eAdjust;

    return bRet;
}

sal_Bool XMLLastLineAdjustPropHdl::exportXML( OUString& rStrExpValue, const uno::Any& rValue, const SvXMLUnitConverter& rUnitConverter ) const
{
    OUStringBuffer aOut;
    sal_Int16 nVal;
    sal_Bool bRet = sal_False;

    rValue >>= nVal;

    if( nVal != style::ParagraphAdjust_LEFT )
        bRet = rUnitConverter.convertEnum( aOut, nVal, pXML_Para_Align_Last_Enum, XML_START );

    rStrExpValue = aOut.makeStringAndClear();

    return bRet;
}

}//end of namespace binfilter
