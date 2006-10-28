/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: SchAddInCollection.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 02:45:10 $
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
#ifndef _SCH_ADDINCOLLECTION_HXX_
#define _SCH_ADDINCOLLECTION_HXX_

#include <com/sun/star/uno/Sequence.hxx>
#include <com/sun/star/util/XRefreshable.hpp>
namespace rtl {
    class OUString;
}

namespace binfilter {

//STRIP008 namespace rtl {
//STRIP008  class OUString;
//STRIP008 }

class SchAddInCollection // : public
{
private:
    ::com::sun::star::uno::Sequence< ::rtl::OUString > maServiceNames;
    sal_Bool mbInitialized;

protected:
    void Initialize();

public:
    SchAddInCollection();
    virtual ~SchAddInCollection();

    ::com::sun::star::uno::Reference< ::com::sun::star::util::XRefreshable > GetAddInByName( const ::rtl::OUString& rName );
    ::com::sun::star::uno::Sequence< ::rtl::OUString > GetAddInNames();
};

} //namespace binfilter
#endif  // _SCH_ADDINCOLLECTION_HXX_
