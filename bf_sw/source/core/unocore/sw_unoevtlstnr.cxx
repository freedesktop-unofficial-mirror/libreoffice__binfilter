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


#ifdef _MSC_VER
#pragma hdrstop
#endif

#include <unoevtlstnr.hxx>
#include <tools/debug.hxx>

#include <com/sun/star/lang/EventObject.hpp>
#include <com/sun/star/lang/XEventListener.hpp>
namespace binfilter {

using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::uno;


SV_IMPL_PTRARR(SwEvtLstnrArray, XEventListenerPtr);


SwEventListenerContainer::SwEventListenerContainer( uno::XInterface* pxInParent) :
    pListenerArr(0),
    pxParent(pxInParent)
{
}

SwEventListenerContainer::~SwEventListenerContainer()
{
    if(pListenerArr && pListenerArr->Count())
    {
        pListenerArr->DeleteAndDestroy(0, pListenerArr->Count());
    }
    delete pListenerArr;
}

void    SwEventListenerContainer::AddListener(const uno::Reference< lang::XEventListener > & rxListener)
{
    if(!pListenerArr)
        pListenerArr = new SwEvtLstnrArray;
    uno::Reference< lang::XEventListener > * pInsert = new uno::Reference< lang::XEventListener > ;
    *pInsert = rxListener;
    pListenerArr->Insert(pInsert, pListenerArr->Count());
}

sal_Bool    SwEventListenerContainer::RemoveListener(const uno::Reference< lang::XEventListener > & rxListener)
{
    if(!pListenerArr)
        return sal_False;
    else
    {
         lang::XEventListener* pLeft = rxListener.get();
        for(sal_uInt16 i = 0; i < pListenerArr->Count(); i++)
        {
            XEventListenerPtr pElem = pListenerArr->GetObject(i);
             lang::XEventListener* pRight = pElem->get();
            if(pLeft == pRight)
            {
                pListenerArr->Remove(i);
                delete pElem;
                return sal_True;
            }
        }
    }
    return sal_False;
}

void    SwEventListenerContainer::Disposing()
{
    if(!pListenerArr)
        return;

    lang::EventObject aObj(pxParent);
    for(sal_uInt16 i = 0; i < pListenerArr->Count(); i++)
    {
        XEventListenerPtr pElem = pListenerArr->GetObject(i);
        (*pElem)->disposing(aObj);
    }
    pListenerArr->DeleteAndDestroy(0, pListenerArr->Count());
}


}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
