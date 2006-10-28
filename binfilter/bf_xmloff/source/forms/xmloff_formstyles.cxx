/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xmloff_formstyles.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 01:49:42 $
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

#ifndef XMLOFF_FORMSTYLES_HXX
#include "formstyles.hxx"
#endif
namespace binfilter {

//.........................................................................
namespace xmloff
{
//.........................................................................

    using namespace token;
    using namespace ::com::sun::star::uno;
    using namespace ::com::sun::star::xml;

    //=====================================================================
    //= OControlStyleContext
    //=====================================================================
    //---------------------------------------------------------------------
    OControlStyleContext::OControlStyleContext( SvXMLImport& _rImport, const sal_uInt16 _Prefix, const ::rtl::OUString& _rLocalName,
        const Reference< sax::XAttributeList >& _rxAttrList, SvXMLStylesContext& _rParentStyles,
        const sal_uInt16 _nFamily, const sal_Bool _bDefaultStyle )
        :XMLPropStyleContext( _rImport, _Prefix, _rLocalName, _rxAttrList, _rParentStyles, _nFamily, _bDefaultStyle )
    {
    }

    //---------------------------------------------------------------------
    void OControlStyleContext::SetAttribute( sal_uInt16 _nPrefixKey, const ::rtl::OUString& _rLocalName, const ::rtl::OUString& _rValue )
    {
        if ( _rLocalName == GetXMLToken( XML_DATA_STYLE_NAME ) )
            m_sNumberStyleName = _rValue;
        else
            XMLPropStyleContext::SetAttribute( _nPrefixKey, _rLocalName, _rValue );
    }

//.........................................................................
}   // namespace xmloff
//.........................................................................


}//end of namespace binfilter
