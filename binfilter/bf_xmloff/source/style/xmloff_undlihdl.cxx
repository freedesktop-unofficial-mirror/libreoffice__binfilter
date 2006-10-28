/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xmloff_undlihdl.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 02:05:13 $
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

#ifndef _XMLOFF_PROPERTYHANDLER_UNDERLINETYPES_HXX
#include <undlihdl.hxx>
#endif


#ifndef _XMLOFF_XMLUCONV_HXX
#include "xmluconv.hxx"
#endif

#ifndef _RTL_USTRBUF_HXX_
#include <rtl/ustrbuf.hxx>
#endif


#ifndef _COM_SUN_STAR_AWT_FONTUNDERLINE_HPP
#include <com/sun/star/awt/FontUnderline.hpp>
#endif

namespace binfilter {

using namespace ::rtl;
using namespace ::com::sun::star;
using namespace ::com::sun::star::awt;
using namespace ::binfilter::xmloff::token;

SvXMLEnumMapEntry __READONLY_DATA pXML_Underline_Enum[] =
{
    { XML_UNDERLINE_NONE,               FontUnderline::NONE },
    { XML_UNDERLINE_SINGLE,             FontUnderline::SINGLE },
    { XML_UNDERLINE_DOUBLE,             FontUnderline::DOUBLE },
    { XML_UNDERLINE_DOTTED,             FontUnderline::DOTTED },
    { XML_UNDERLINE_DASH,               FontUnderline::DASH },
    { XML_UNDERLINE_LONG_DASH,          FontUnderline::LONGDASH },
    { XML_UNDERLINE_DOT_DASH,           FontUnderline::DASHDOT },
    { XML_UNDERLINE_DOT_DOT_DASH,       FontUnderline::DASHDOTDOT },
    { XML_UNDERLINE_WAVE,               FontUnderline::WAVE },
    { XML_UNDERLINE_BOLD,               FontUnderline::BOLD },
    { XML_UNDERLINE_BOLD_DOTTED,        FontUnderline::BOLDDOTTED },
    { XML_UNDERLINE_BOLD_DASH,          FontUnderline::BOLDDASH },
    { XML_UNDERLINE_BOLD_LONG_DASH,     FontUnderline::BOLDLONGDASH },
    { XML_UNDERLINE_BOLD_DOT_DASH,      FontUnderline::BOLDDASHDOT },
    { XML_UNDERLINE_BOLD_DOT_DOT_DASH,  FontUnderline::BOLDDASHDOTDOT },
    { XML_UNDERLINE_BOLD_WAVE,          FontUnderline::BOLDWAVE },
    { XML_UNDERLINE_DOUBLE_WAVE,        FontUnderline::DOUBLEWAVE },
    { XML_UNDERLINE_SMALL_WAVE,         FontUnderline::SMALLWAVE },
    { XML_TOKEN_INVALID,                0 }
};

///////////////////////////////////////////////////////////////////////////////
//
// class XMLPosturePropHdl
//

XMLUnderlinePropHdl::~XMLUnderlinePropHdl()
{
    // nothing to do
}

sal_Bool XMLUnderlinePropHdl::importXML( const OUString& rStrImpValue, uno::Any& rValue, const SvXMLUnitConverter& rUnitConverter ) const
{
    sal_Bool bRet = sal_False;
    sal_uInt16 eUnderline;

    if( ( bRet = rUnitConverter.convertEnum( eUnderline, rStrImpValue, pXML_Underline_Enum ) ) )
        rValue <<= (sal_Int16)eUnderline;

    return bRet;
}

sal_Bool XMLUnderlinePropHdl::exportXML( OUString& rStrExpValue, const uno::Any& rValue, const SvXMLUnitConverter& rUnitConverter ) const
{
    sal_Bool bRet = sal_False;
    sal_Int16 nValue;
    OUStringBuffer aOut;

    if( rValue >>= nValue )
    {
        if( ( bRet = rUnitConverter.convertEnum( aOut, (sal_uInt16)nValue,
                                                 pXML_Underline_Enum ) ) )
            rStrExpValue = aOut.makeStringAndClear();
    }

    return bRet;
}

}//end of namespace binfilter
