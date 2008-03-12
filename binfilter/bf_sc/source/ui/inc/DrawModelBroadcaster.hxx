/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: DrawModelBroadcaster.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 07:06:33 $
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

#ifndef _SC_DRAWMODELBROADCASTER_HXX
#define _SC_DRAWMODELBROADCASTER_HXX


#ifndef _SFXLSTNER_HXX
#include <bf_svtools/lstner.hxx>
#endif
#ifndef _CPPUHELPER_INTERFACECONTAINER_H_
#include <cppuhelper/interfacecontainer.h>
#endif
#ifndef _CPPUHELPER_IMPLBASE1_HXX_
#include <cppuhelper/implbase1.hxx>
#endif

#ifndef _COM_SUN_STAR_DOCUMENT_XEVENTBROADCASTER_HPP_
#include <com/sun/star/document/XEventBroadcaster.hpp>
#endif
namespace binfilter {

class SdrModel;

class ScDrawModelBroadcaster : public SfxListener,
    public ::cppu::WeakImplHelper1< ::com::sun::star::document::XEventBroadcaster >
{
    mutable ::osl::Mutex maListenerMutex;
    ::cppu::OInterfaceContainerHelper maEventListeners;
    SdrModel *mpDrawModel;

public:

    ScDrawModelBroadcaster( SdrModel *pDrawModel );
    virtual ~ScDrawModelBroadcaster();

    virtual void SAL_CALL addEventListener( const ::com::sun::star::uno::Reference< ::com::sun::star::document::XEventListener >& xListener )
        throw (::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL removeEventListener( const ::com::sun::star::uno::Reference< ::com::sun::star::document::XEventListener >& xListener )
        throw (::com::sun::star::uno::RuntimeException);

    virtual void        Notify( SfxBroadcaster& rBC, const SfxHint& rHint );
};

} //namespace binfilter
#endif
