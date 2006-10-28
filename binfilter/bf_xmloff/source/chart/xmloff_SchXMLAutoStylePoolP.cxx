/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xmloff_SchXMLAutoStylePoolP.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 01:37:05 $
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

#include <xmlprmap.hxx>

#include "SchXMLAutoStylePoolP.hxx"
#include "PropertyMap.hxx"

#ifndef SCH_XMLEXPORT_HXX_
#include "SchXMLExport.hxx"
#endif
namespace binfilter {

using ::binfilter::xmloff::token::GetXMLToken;
using ::binfilter::xmloff::token::XML_CDATA;

SchXMLAutoStylePoolP::SchXMLAutoStylePoolP( SchXMLExport& rSchXMLExport ) :
        SvXMLAutoStylePoolP( rSchXMLExport ),
        mrSchXMLExport( rSchXMLExport )
{}

SchXMLAutoStylePoolP::~SchXMLAutoStylePoolP()
{}

void SchXMLAutoStylePoolP::exportStyleAttributes(
    SvXMLAttributeList& rAttrList,
    sal_Int32 nFamily,
    const ::std::vector< XMLPropertyState >& rProperties,
    const SvXMLExportPropertyMapper& rPropExp
    , const SvXMLUnitConverter& rUnitConverter,
    const SvXMLNamespaceMap& rNamespaceMap
    ) const
{
    const ::rtl::OUString sCDATA( GetXMLToken( XML_CDATA ));
    SvXMLAutoStylePoolP::exportStyleAttributes( rAttrList, nFamily, rProperties,
                                                rPropExp, rUnitConverter, rNamespaceMap );

    if( nFamily == XML_STYLE_FAMILY_SCH_CHART_ID )
    {
        ::std::vector< XMLPropertyState >::const_iterator iter = rProperties.begin();
        for( iter; (iter != rProperties.end()); iter++ )
        {
            UniReference< XMLPropertySetMapper > aPropMapper =
                mrSchXMLExport.GetPropertySetMapper();
            sal_Int16 nContextID = aPropMapper->GetEntryContextId( iter->mnIndex );
            if( nContextID == XML_SCH_CONTEXT_SPECIAL_NUMBER_FORMAT )
            {
                sal_Int32 nNumberFormat = -1;
                if( ( iter->maValue >>= nNumberFormat ) &&
                    ( nNumberFormat != -1 ))
                {
                    ::rtl::OUString sAttrValue = mrSchXMLExport.getDataStyleName( nNumberFormat );
                    if( sAttrValue.getLength() )
                    {
                        mrSchXMLExport.AddAttribute(
                            aPropMapper->GetEntryNameSpace( iter->mnIndex ),
                            aPropMapper->GetEntryXMLName( iter->mnIndex ),
                            sAttrValue );
                    }
                }
            }
        }
    }
}
}//end of namespace binfilter
