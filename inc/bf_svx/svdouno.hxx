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

#ifndef _SVDOUNO_HXX
#define _SVDOUNO_HXX

#include <bf_svtools/bf_solar.h>

#include <com/sun/star/awt/XControlModel.hpp>
#include <com/sun/star/awt/XControl.hpp>
#include <com/sun/star/lang/XMultiServiceFactory.hpp>

#include <bf_svx/svdorect.hxx>
namespace binfilter {

//************************************************************
//   Vorausdeklarationen
//************************************************************

class SdrView;
class SdrControlEventListenerImpl;

//************************************************************
//   SdrUnoObj
//************************************************************

class SdrUnoObj : public SdrRectObj
{
    friend class                SdrPageView;
    friend class                SdrControlEventListenerImpl;

    SdrControlEventListenerImpl*    pEventListener;

    String                      aUnoControlModelTypeName;
    String                      aUnoControlTypeName;
    BOOL                        bOwnUnoControlModel;

protected:
    ::com::sun::star::uno::Reference< ::com::sun::star::awt::XControlModel > xUnoControlModel; // kann auch von aussen gesetzt werden

private:

public:
    TYPEINFO();

    SdrUnoObj(BOOL bOwnsModel = TRUE);
    virtual ~SdrUnoObj();
    using SdrRectObj::operator=;

    virtual void SetPage(SdrPage* pNewPage);
    virtual void SetModel(SdrModel* pModel);



    virtual void NbcMove(const Size& rSize);
    virtual void NbcResize(const Point& rRef, const Fraction& xFact, const Fraction& yFact);
    virtual void NbcSetSnapRect(const Rectangle& rRect);
    virtual void NbcSetLogicRect(const Rectangle& rRect);
    virtual void NbcSetLayer(SdrLayerID nLayer);

    virtual void ReadData(const SdrObjIOHeader& rHead, SvStream& rIn);


    ::com::sun::star::uno::Reference< ::com::sun::star::awt::XControlModel > GetUnoControlModel() const {return xUnoControlModel;}

    const String& GetUnoControlModelTypeName() const { return aUnoControlTypeName; }
    const String& GetUnoControlTypeName() const { return aUnoControlTypeName; }

    void SetUnoControlModel(::com::sun::star::uno::Reference< ::com::sun::star::awt::XControlModel > xModel);
    void VisAreaChanged(const OutputDevice* pOut=NULL);
};

}//end of namespace binfilter
#endif          // _SVDOUNO_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
