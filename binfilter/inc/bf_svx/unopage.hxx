/*************************************************************************
 *
 *  $RCSfile: unopage.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:47 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/
#ifndef _SVX_UNOWPAGE_HXX
#define _SVX_UNOWPAGE_HXX

#ifndef _COM_SUN_STAR_LANG_XTYPEPROVIDER_HPP_
#include <com/sun/star/lang/XTypeProvider.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_XSERVICEINFO_HPP_
#include <com/sun/star/lang/XServiceInfo.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
#include <com/sun/star/beans/XPropertySet.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_XDRAWPAGE_HPP_
#include <com/sun/star/drawing/XDrawPage.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_XSHAPEGROUPER_HPP_
#include <com/sun/star/drawing/XShapeGrouper.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_XSHAPECOMBINER_HPP_
#include <com/sun/star/drawing/XShapeCombiner.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_XSHAPEBINDER_HPP_
#include <com/sun/star/drawing/XShapeBinder.hpp>
#endif
#ifndef _COM_SUN_STAR_UNO_XUNOTUNNEL_HPP_
#include <com/sun/star/lang/XUnoTunnel.hpp>
#endif

#ifndef _CPPUHELPER_WEAK_HXX_
#include <cppuhelper/weak.hxx>
#endif
#ifndef _CPPUHELPER_WEAKAGG_HXX_
#include <cppuhelper/weakagg.hxx>
#endif

#ifndef _SFXLSTNER_HXX
#include <svtools/lstner.hxx>
#endif

#include <cppuhelper/implbase4.hxx>
#include <unotools/servicehelper.hxx>

#include <bf_svx/unoprov.hxx>

class SdrPage;
class SdrModel;
class SdrView;
class SdrPageView;
class SdrObject;
class List;
class SvxShapeDescriptor;
class SvxShape;
class SvxShapeGroup;
class SvxShapeConnector;
class SvxShapeList;
class SvxDrawPageList;

/***********************************************************************
* Macros fuer Umrechnung Twips<->100tel mm                             *
***********************************************************************/
#define TWIPS_TO_MM(val) ((val * 127 + 36) / 72)
#define MM_TO_TWIPS(val) ((val * 72 + 63) / 127)

/***********************************************************************
*                                                                      *
***********************************************************************/
class SvxDrawPage : public ::cppu::WeakAggImplHelper4< ::com::sun::star::drawing::XDrawPage,
                                               ::com::sun::star::drawing::XShapeGrouper,
                                               ::com::sun::star::lang::XServiceInfo,
                                               ::com::sun::star::lang::XUnoTunnel>,
                    public SfxListener
{
 protected:

    SdrPage*        pPage;
    SdrModel*       pModel;
    SdrView*        pView;

    void    _SelectObjectsInView( const ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XShapes >& aShapes, SdrPageView*   pPageView ) throw ();
    void    _SelectObjectInView( const ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XShape >& xShape, SdrPageView*  pPageView ) throw();

 public:
    SvxDrawPage( SdrPage* pPage ) throw();
    SvxDrawPage() throw();
    virtual ~SvxDrawPage() throw();

    // Internals
    SdrPage* GetSdrPage() const { return pPage; }

    // Erzeugen eines SdrObjects und Einfugen in die SdrPage
    SdrObject *CreateSdrObject( const ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XShape >& xShape ) throw();

    // Typ und Inventor bestimmen
    void GetTypeAndInventor( sal_uInt16& rType, sal_uInt32& rInventor, const ::rtl::OUString& aName ) const throw();

    // Erzeugen eines SdrObjects anhand einer Description. Kann von
    // abgeleiteten Klassen dazu benutzt werden, eigene Shapes zu
    // unterstuetzen (z.B. Controls)
    virtual SdrObject *_CreateSdrObject( const ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XShape >& xShape ) throw();

    static SvxShape* CreateShapeByTypeAndInventor( sal_uInt16 nType, sal_uInt32 nInventor, SdrObject *pObj = NULL, SvxDrawPage *pPage = NULL ) throw();

    // Die folgende Methode wird gerufen, wenn ein SvxShape-Objekt angelegt
    // werden soll. abgeleitete Klassen koennen hier eine Ableitung oder
    // ein ein SvxShape aggregierenden Objekt anlegen.
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XShape > _CreateShape( SdrObject *pObj ) const throw();

    static SvxDrawPage* GetPageForSdrPage( SdrPage* pPage ) throw();

    UNO3_GETIMPLEMENTATION_DECL( SvxDrawPage )

    // SfxListener
    virtual void Notify( SfxBroadcaster& rBC, const SfxHint& rHint );

    // XShapes
    virtual void SAL_CALL add( const ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XShape >& xShape ) throw(::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL remove( const ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XShape >& xShape ) throw(::com::sun::star::uno::RuntimeException);

    // XElementAccess
    virtual ::com::sun::star::uno::Type SAL_CALL getElementType() throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL hasElements() throw(::com::sun::star::uno::RuntimeException);

    // XIndexAccess
    virtual sal_Int32 SAL_CALL getCount() throw(::com::sun::star::uno::RuntimeException) ;
    virtual ::com::sun::star::uno::Any SAL_CALL getByIndex( sal_Int32 Index ) throw(::com::sun::star::lang::IndexOutOfBoundsException, ::com::sun::star::lang::WrappedTargetException, ::com::sun::star::uno::RuntimeException);

    // XShapeGrouper
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XShapeGroup > SAL_CALL group( const ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XShapes >& xShapes ) throw(::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL ungroup( const ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XShapeGroup >& aGroup ) throw(::com::sun::star::uno::RuntimeException);

    // XServiceInfo
    virtual ::rtl::OUString SAL_CALL getImplementationName() throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ServiceName ) throw(::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames() throw(::com::sun::star::uno::RuntimeException);
};

#endif

