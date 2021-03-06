/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2000, 2010 Oracle and/or its affiliates.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/


#include <rtl/ustrbuf.hxx>

#include "xmluconv.hxx"


#include "DrawAspectHdl.hxx"
namespace binfilter {

using namespace ::rtl;
using namespace ::com::sun::star;
using namespace ::binfilter::xmloff::token;

///////////////////////////////////////////////////////////////////////////////
//
// class XMLMeasurePropHdl
//

SvXMLEnumMapEntry const pXML_DrawAspect_Enum[] =
{
    { XML_CONTENT,          1   },
    { XML_THUMBNAIL,        2   },
    { XML_ICON,             4   },
    { XML_PRINT,            8   },
    { XML_TOKEN_INVALID, 0 }
};

DrawAspectHdl::~DrawAspectHdl()
{
    // nothing to do
}

sal_Bool DrawAspectHdl::importXML( const OUString& rStrImpValue, uno::Any& rValue, const SvXMLUnitConverter& rUnitConverter ) const
{
    sal_Int32 nAspect = 0;

    SvXMLTokenEnumerator aTokenEnum( rStrImpValue );
    OUString aToken;
    while( aTokenEnum.getNextToken( aToken ) )
    {
        sal_uInt16 nVal;
        if( rUnitConverter.convertEnum( nVal, aToken, pXML_DrawAspect_Enum ) )
        {
            nAspect = nAspect | (sal_Int32)nVal;
        }
    }

    rValue <<= nAspect;

    return nAspect != 0;
}

sal_Bool DrawAspectHdl::exportXML( OUString& rStrExpValue, const uno::Any& rValue, const SvXMLUnitConverter& /*rUnitConverter*/ ) const
{
    sal_Bool bRet = sal_False;
      OUStringBuffer aOut;

    sal_Int32 nAspect(0);
    if( rValue >>= nAspect )
    {
        if( (nAspect & 1) != 0 )
            aOut.append( GetXMLToken(XML_CONTENT) );

        if( (nAspect & 2) != 0 )
        {
            if( aOut.getLength() )
                aOut.append( sal_Unicode(' ') );
            aOut.append( GetXMLToken(XML_THUMBNAIL) );
        }

        if( (nAspect & 4) != 0 )
        {
            if( aOut.getLength() )
                aOut.append( sal_Unicode(' ') );
            aOut.append( GetXMLToken(XML_ICON) );
        }

        if( (nAspect & 8) != 0 )
        {
            if( aOut.getLength() )
                aOut.append( sal_Unicode(' ') );
            aOut.append( GetXMLToken(XML_PRINT) );
        }

        rStrExpValue = aOut.makeStringAndClear();

        bRet = sal_True;
    }

    return bRet;
}
}//end of namespace binfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
