/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: SchXMLWrapper.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: vg $ $Date: 2007-10-23 14:18:32 $
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
#ifndef _SCH_XMLWRP_HXX_
#define _SCH_XMLWRP_HXX_

#ifndef _SVSTOR_HXX
#include <bf_so3/svstor.hxx>
#endif
namespace com { namespace sun { namespace star {
    namespace xml {
        namespace sax {
            class XParser;
        }
    }
    namespace document {
        class XGraphicObjectResolver;
    }
    namespace frame {
        class XModel;
    }
    namespace task {
        class XStatusIndicator;
    }
    namespace lang {
        class XMultiServiceFactory;
    }
    namespace io {
        class XActiveDataSource;
    }
}}}
namespace binfilter {

//STRIP008 namespace com { namespace sun { namespace star {
//STRIP008  namespace xml {
//STRIP008      namespace sax {
//STRIP008          class XParser;
//STRIP008      }
//STRIP008  }
//STRIP008  namespace document {
//STRIP008      class XGraphicObjectResolver;
//STRIP008  }
//STRIP008  namespace frame {
//STRIP008      class XModel;
//STRIP008  }
//STRIP008  namespace task {
//STRIP008      class XStatusIndicator;
//STRIP008  }
//STRIP008  namespace lang {
//STRIP008      class XMultiServiceFactory;
//STRIP008  }
//STRIP008     namespace io {
//STRIP008         class XActiveDataSource;
//STRIP008     }
//STRIP008 }}}

class SchXMLWrapper
{
    ::com::sun::star::uno::Reference< ::com::sun::star::frame::XModel > mxModel;
    ::com::sun::star::uno::Reference< ::com::sun::star::task::XStatusIndicator > mxStatusIndicator;
    SvStorage& mrStorage;

    sal_Bool mbIsDraw : 1;
    sal_Bool mbShowProgress : 1;

    sal_Int32 ImportStream(
        const ::rtl::OUString& rsStreamName,
        const ::rtl::OUString& rsServiceName,
        ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XParser >& xParser,
        ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory>& xServiceFactory,
        ::com::sun::star::uno::Reference< ::com::sun::star::document::XGraphicObjectResolver >& xGraphObjResolver );

    sal_Bool ExportStream(
        const ::rtl::OUString& rsStreamName,
        const ::rtl::OUString& rsServiceName,
        ::com::sun::star::uno::Reference< ::com::sun::star::io::XActiveDataSource >& xDataSource,
        ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory>& xServiceFactory,
        ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Any >& aArgs );

public:
    SchXMLWrapper( ::com::sun::star::uno::Reference< ::com::sun::star::frame::XModel >& xModel,
                   SvStorage& rStorage,
                   sal_Bool bShowProgress = TRUE );

    sal_Int32 Import();
    sal_Bool Export();
};

} //namespace binfilter
#endif  // _SCH_XMLWRP_HXX_
