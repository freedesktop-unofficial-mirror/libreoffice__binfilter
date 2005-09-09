/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: animexp.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 17:29:20 $
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

#ifndef _XMLOFF_ANIMEXP_HXX
#define _XMLOFF_ANIMEXP_HXX

#ifndef _COM_SUN_STAR_DRAWING_XSHAPE_HPP_
#include <com/sun/star/drawing/XShape.hpp>
#endif

#ifndef _UNIVERSALL_REFERENCE_HXX
#include <bf_xmloff/uniref.hxx>
#endif
namespace binfilter {

class AnimExpImpl;
class SvXMLExport;
class XMLShapeExport;

class XMLAnimationsExporter : public UniRefBase
{
    AnimExpImpl*    mpImpl;

public:
    XMLAnimationsExporter( XMLShapeExport* pShapeExp );
    virtual ~XMLAnimationsExporter();

    void prepare( ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XShape > xShape );
    void collect( ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XShape > xShape );
    void exportAnimations( SvXMLExport& rExport );
};

}//end of namespace binfilter
#endif  //  _XMLOFF_ANIMEXP_HXX

