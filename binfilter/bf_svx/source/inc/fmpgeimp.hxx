/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */
#ifndef _SVX_FMUNOPGE_HXX
#define _SVX_FMUNOPGE_HXX

#include <com/sun/star/sdbc/XDataSource.hpp>
#include <com/sun/star/container/XNameAccess.hpp>
#include <com/sun/star/form/XFormComponent.hpp>
#include <com/sun/star/form/XForm.hpp>
#include <com/sun/star/container/XNameContainer.hpp>
#include <com/sun/star/frame/XModel.hpp>
#include <com/sun/star/lang/XServiceInfo.hpp>

#include <bf_tools/string.hxx>

#include <vector>

namespace com { namespace sun { namespace star {
    namespace io {
        class XObjectOutputStream;
        class XObjectInputStream;
    }
    namespace container {
        class XIndexContainer;
    }
}}}

class SvStream;
namespace binfilter {

class SdrIOHeader;
class FmFormObj;
class FmFormPage;
class SdrObject;
class SdrObjList;

typedef ::std::vector< FmFormObj* > FmObjectList;

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
    const ::com::sun::star::uno::Reference< ::com::sun::star::form::XForm>& getCurForm() {return xCurrentForm;}

    // Defaults fuer ein Object setzen
    // Eindeutigen Namen, Zuordnen zu einer Form falls noch nicht erfolgt

    UniString GetPageId() const { return m_sPageId; }

    // activation handling
    inline  sal_Bool    hasEverBeenActivated( ) const { return !m_bFirstActivation; }
    inline  void        setHasBeenActivated( ) { m_bFirstActivation = sal_False; }

protected:
    // lesen und schreiben der Objecte
    void ReadData(const SdrIOHeader& rHead, SvStream& rIn); //

    void read(const ::com::sun::star::uno::Reference< ::com::sun::star::io::XObjectInputStream>& InStream);

    const ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameContainer>& getForms() {return xForms;}

    void fillList(FmObjectList& rList, const SdrObjList& rObjList, sal_Bool bConnected) const;



public:


};


}//end of namespace binfilter
#endif // _SVX_FMUNOPGE_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
