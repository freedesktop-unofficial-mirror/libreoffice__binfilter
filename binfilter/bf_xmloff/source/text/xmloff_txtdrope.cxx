/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xmloff_txtdrope.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 02:19:54 $
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



#ifndef _COM_SUN_STAR_STYLE_DROPCAPFORMAT_HPP_
#include <com/sun/star/style/DropCapFormat.hpp>
#endif


#ifndef _XMLOFF_XMLEXP_HXX
#include "xmlexp.hxx"
#endif

#ifndef _XMLOFF_XMLUCONV_HXX
#include "xmluconv.hxx"
#endif

#ifndef _XMLOFF_XMLNMSPE_HXX
#include "xmlnmspe.hxx"
#endif

#ifndef _XMLOFF_TXTDROPE_HXX
#include "txtdrope.hxx"
#endif
namespace binfilter {

using namespace ::com::sun::star;
using namespace ::com::sun::star::style;
using namespace ::com::sun::star::uno;
using namespace ::rtl;
using namespace ::binfilter::xmloff::token;


XMLTextDropCapExport::XMLTextDropCapExport( SvXMLExport& rExp ) :
    rExport(rExp)
{
}

XMLTextDropCapExport::~XMLTextDropCapExport()
{
}

void XMLTextDropCapExport::exportXML( const Any& rAny,
                                      sal_Bool bWholeWord,
                                      const OUString& rStyleName )
{
    DropCapFormat aFormat;
    rAny >>= aFormat;
    OUString sValue;
    OUStringBuffer sBuffer;
    if( aFormat.Lines > 1 )
    {
        SvXMLUnitConverter& rUnitConv = rExport.GetMM100UnitConverter();

        // style:lines
        rUnitConv.convertNumber( sBuffer, (sal_Int32)aFormat.Lines );
        rExport.AddAttribute( XML_NAMESPACE_STYLE, XML_LINES,
                              sBuffer.makeStringAndClear() );

        // style:length
        if( bWholeWord )
        {
            sValue = GetXMLToken(XML_WORD);
        }
        else if( aFormat.Count > 1 )
        {
            rUnitConv.convertNumber( sBuffer, (sal_Int32)aFormat.Count );
            sValue = sBuffer.makeStringAndClear();
        }
        if( sValue.getLength() )
            rExport.AddAttribute( XML_NAMESPACE_STYLE, XML_LENGTH, sValue );

        // style:distance
        if( aFormat.Distance > 0 )
        {
            rUnitConv.convertMeasure( sBuffer, aFormat.Distance );
            rExport.AddAttribute( XML_NAMESPACE_STYLE, XML_DISTANCE,
                                  sBuffer.makeStringAndClear() );
        }

        // style:style-name
        if( rStyleName.getLength() )
            rExport.AddAttribute( XML_NAMESPACE_STYLE, XML_STYLE_NAME,
                                  rStyleName );
    }

    SvXMLElementExport aElem( rExport, XML_NAMESPACE_STYLE, XML_DROP_CAP,
                              sal_False, sal_False );
}



}//end of namespace binfilter
