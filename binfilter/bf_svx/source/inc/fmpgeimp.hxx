/*************************************************************************
 *
 *  $RCSfile: fmpgeimp.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: kz $ $Date: 2005-07-14 14:36:48 $
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
#ifndef _SVX_FMUNOPGE_HXX
#define _SVX_FMUNOPGE_HXX

#ifndef _COM_SUN_STAR_SDBC_XDATASOURCE_HPP_
#include <com/sun/star/sdbc/XDataSource.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XNAMEACCESS_HPP_
#include <com/sun/star/container/XNameAccess.hpp>
#endif
#ifndef _COM_SUN_STAR_FORM_XFORMCOMPONENT_HPP_
#include <com/sun/star/form/XFormComponent.hpp>
#endif
#ifndef _COM_SUN_STAR_FORM_XFORM_HPP_
#include <com/sun/star/form/XForm.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XNAMECONTAINER_HPP_
#include <com/sun/star/container/XNameContainer.hpp>
#endif
#ifndef _COM_SUN_STAR_FRAME_XMODEL_HPP_
#include <com/sun/star/frame/XModel.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_XSERVICEINFO_HPP_
#include <com/sun/star/lang/XServiceInfo.hpp>
#endif


#ifndef _LIST_HXX //autogen
#include <tools/list.hxx>
#endif

#ifndef _COMPHELPER_UNO3_HXX_
#include <comphelper/uno3.hxx>
#endif
FORWARD_DECLARE_INTERFACE(io,XObjectOutputStream)
FORWARD_DECLARE_INTERFACE(io,XObjectInputStream)
FORWARD_DECLARE_INTERFACE(container,XIndexContainer)
class SvStream;
namespace binfilter {

class SdrIOHeader;
class FmFormObj;
class FmFormPage;
class SdrObject;

//FORWARD_DECLARE_INTERFACE(uno,Reference)
//STRIP008 FORWARD_DECLARE_INTERFACE(io,XObjectOutputStream)
//STRIP008 FORWARD_DECLARE_INTERFACE(io,XObjectInputStream)
//STRIP008 FORWARD_DECLARE_INTERFACE(container,XIndexContainer)

class SdrObjList;

DECLARE_LIST(FmObjectList, FmFormObj*)//STRIP008 DECLARE_LIST(FmObjectList, FmFormObj*);

//==================================================================
// FmFormPageImpl
// lauscht an allen Containern, um festzustellen, wann Objecte
// eingefuegt worden sind und wann diese entfernt wurden
//==================================================================

class FmFormPageImpl
{
    friend class FmFormPage;
    friend class FmFormObj;
    friend class FmXFormShell;

    ::com::sun::star::uno::Reference< ::com::sun::star::form::XForm>                xCurrentForm;   // aktuelles Formular
    ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameContainer>  xForms;         // Liste aller Forms
    ::com::sun::star::uno::Reference< ::com::sun::star::frame::XModel>              xModel;
    FmFormPage*             pPage;
    UniString               m_sPageId;

    sal_Bool        m_bFirstActivation  : 1;

protected:
    FmFormPageImpl(FmFormPage* _pPage);
    FmFormPageImpl(FmFormPage* _pPage, const FmFormPageImpl& rImpl);
    ~FmFormPageImpl();

    void Init();

public:
    //  nur wichtig fuer den DesignMode
//STRIP001  void setCurForm(::com::sun::star::uno::Reference< ::com::sun::star::form::XForm> xForm);
    const ::com::sun::star::uno::Reference< ::com::sun::star::form::XForm>& getCurForm() {return xCurrentForm;}
//STRIP001  ::com::sun::star::uno::Reference< ::com::sun::star::form::XForm> getDefaultForm();

    // Defaults fuer ein Object setzen
    // Eindeutigen Namen, Zuordnen zu einer Form falls noch nicht erfolgt
//STRIP001  ::com::sun::star::uno::Reference< ::com::sun::star::form::XForm> SetDefaults(const ::com::sun::star::uno::Reference< ::com::sun::star::form::XFormComponent>& rContent,
//STRIP001                       const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XDataSource>& rDatabase = ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XDataSource>(),
//STRIP001                       const ::rtl::OUString& rDBTitle = ::rtl::OUString(),
//STRIP001                       const ::rtl::OUString& rCursorSource = ::rtl::OUString(),
//STRIP001                       sal_Int32 nCommandType = 0);

    UniString GetPageId() const { return m_sPageId; }

    // activation handling
    inline  sal_Bool    hasEverBeenActivated( ) const { return !m_bFirstActivation; }
    inline  void        setHasBeenActivated( ) { m_bFirstActivation = sal_False; }

protected:
    // lesen und schreiben der Objecte
    void WriteData(SvStream& rOut) const; //
    void ReadData(const SdrIOHeader& rHead, SvStream& rIn); //

    void write(const ::com::sun::star::uno::Reference< ::com::sun::star::io::XObjectOutputStream>& OutStream) const;
    void read(const ::com::sun::star::uno::Reference< ::com::sun::star::io::XObjectInputStream>& InStream);

    const ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameContainer>& getForms() {return xForms;}

    void fillList(FmObjectList& rList, const SdrObjList& rObjList, sal_Bool bConnected) const;

//STRIP001  ::com::sun::star::uno::Reference< ::com::sun::star::form::XForm> FindForm(const ::com::sun::star::uno::Reference< ::com::sun::star::form::XForm>& rForm,
//STRIP001                    const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XDataSource>& rDatabase,
//STRIP001                    const ::rtl::OUString& rCursorSource,
//STRIP001                    sal_Int32 nCommandType);

//STRIP001  ::rtl::OUString getDefaultName(
//STRIP001                      sal_Int16 _nClassId,
//STRIP001                      const ::com::sun::star::uno::Reference< ::com::sun::star::form::XForm>& _rxControls,
//STRIP001                      const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XServiceInfo >& _rxObject
//STRIP001                  ) const;

public:

//STRIP001  static UniString getDefaultName(
//STRIP001                      sal_Int16 nClassId,
//STRIP001                      const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XServiceInfo >& _rxObject
//STRIP001                  );

//STRIP001  ::rtl::OUString setUniqueName(const ::com::sun::star::uno::Reference< ::com::sun::star::form::XFormComponent>& xFormComponent, const ::com::sun::star::uno::Reference< ::com::sun::star::form::XForm>& xControls);
//STRIP001  ::rtl::OUString getUniqueName(const ::rtl::OUString& rName, const ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameAccess>& xNamedSet) const;
};


}//end of namespace binfilter
#endif // _SVX_FMUNOPGE_HXX

