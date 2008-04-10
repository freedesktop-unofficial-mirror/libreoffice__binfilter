/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: SchXMLAutoStylePoolP.hxx,v $
 * $Revision: 1.3 $
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
#ifndef _SCH_XMLAUTOSTYLEPOOLP_HXX_
#define _SCH_XMLAUTOSTYLEPOOLP_HXX_

#ifndef _XMLOFF_XMLASTPLP_HXX
#include "xmlaustp.hxx"
#endif
namespace binfilter {

class SchXMLExport;

class SchXMLAutoStylePoolP : public SvXMLAutoStylePoolP
{
protected:
    SchXMLExport& mrSchXMLExport;

    virtual void exportStyleAttributes(
        SvXMLAttributeList& rAttrList,
        sal_Int32 nFamily,
        const ::std::vector< XMLPropertyState >& rProperties,
        const SvXMLExportPropertyMapper& rPropExp
        , const SvXMLUnitConverter& rUnitConverter,
        const SvXMLNamespaceMap& rNamespaceMap
        ) const;

public:
    SchXMLAutoStylePoolP( SchXMLExport& rSchXMLExport );
    virtual ~SchXMLAutoStylePoolP();
};

}//end of namespace binfilter
#endif  // _SCH_XMLAUTOSTYLEPOOLP_HXX_
