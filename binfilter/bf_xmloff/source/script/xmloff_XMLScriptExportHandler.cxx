/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xmloff_XMLScriptExportHandler.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 01:52:26 $
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

#ifndef _XMLOFF_XMLSCRIPTEXPORTHANDLER_HXX
#include "XMLScriptExportHandler.hxx"
#endif



#ifndef _XMLOFF_XMLEXP_HXX
#include "xmlexp.hxx"
#endif


#ifndef _XMLOFF_XMLNMSPE_HXX
#include "xmlnmspe.hxx"
#endif
namespace binfilter {


using namespace ::com::sun::star::uno;
using namespace ::binfilter::xmloff::token;

using ::rtl::OUString;
using ::com::sun::star::beans::PropertyValue;


XMLScriptExportHandler::XMLScriptExportHandler() :
    sURL(RTL_CONSTASCII_USTRINGPARAM("Script"))
{
}

XMLScriptExportHandler::~XMLScriptExportHandler()
{
}

void XMLScriptExportHandler::Export(
    SvXMLExport& rExport,
    const OUString& rEventName,
    Sequence<PropertyValue> & rValues,
    sal_Bool bUseWhitespace)
{
    rExport.AddAttribute(XML_NAMESPACE_SCRIPT, XML_LANGUAGE, XML_SCRIPT);
    rExport.AddAttribute(XML_NAMESPACE_SCRIPT, XML_EVENT_NAME, rEventName);

    sal_Int32 nCount = rValues.getLength();
    for(sal_Int32 i = 0; i < nCount; i++)
    {
        if (sURL.equals(rValues[i].Name))
        {
            OUString sTmp;
            rValues[i].Value >>= sTmp;
            rExport.AddAttribute(XML_NAMESPACE_XLINK, XML_HREF, sTmp);
        }
        // else: disregard
    }

    SvXMLElementExport aEventElemt(rExport, XML_NAMESPACE_SCRIPT, XML_EVENT,
                                   bUseWhitespace, sal_False);
}
}//end of namespace binfilter
