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

#include <osl/mutex.hxx>
#include <vcl/svapp.hxx>

#include "calbck.hxx"

#include <unoredlines.hxx>

#include <osl/diagnose.h>

#include <unoredline.hxx>
#include <tools/debug.hxx>
#include <pagedesc.hxx>
#include "poolfmt.hxx"

#include <horiornt.hxx>

#include <doc.hxx>
#include <docary.hxx>
#include <redline.hxx>
#include <com/sun/star/beans/XPropertySet.hpp>
namespace binfilter {

using namespace ::com::sun::star;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::text;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::beans;

using rtl::OUString;


SwXRedlines::SwXRedlines(SwDoc* pInDoc) :
    SwUnoCollection(pInDoc)
{
}

SwXRedlines::~SwXRedlines()
{
}

sal_Int32 SwXRedlines::getCount(  ) throw(RuntimeException)
{
    SolarMutexGuard aGuard;
    if(!IsValid())
        throw uno::RuntimeException();
    const SwRedlineTbl& rRedTbl = GetDoc()->GetRedlineTbl();
    return rRedTbl.Count();
}

Any SwXRedlines::getByIndex(sal_Int32 nIndex)
    throw( IndexOutOfBoundsException, WrappedTargetException, RuntimeException )
{
    SolarMutexGuard aGuard;
    if(!IsValid())
        throw uno::RuntimeException();
    const SwRedlineTbl& rRedTbl = GetDoc()->GetRedlineTbl();
    Any aRet;
    if(rRedTbl.Count() > nIndex && nIndex >= 0)
    {
        Reference <XPropertySet> xRet = SwXRedlines::GetObject( *rRedTbl.GetObject((USHORT)nIndex), *GetDoc() );
        aRet <<= xRet;
    }
    else
        throw IndexOutOfBoundsException();
    return aRet;
}

Reference< XEnumeration >  SwXRedlines::createEnumeration(void)
    throw( RuntimeException )
{
    SolarMutexGuard aGuard;
    if(!IsValid())
        throw uno::RuntimeException();
    return Reference< XEnumeration >(new SwXRedlineEnumeration(*GetDoc()));
}

Type SwXRedlines::getElementType(  ) throw(RuntimeException)
{
    return ::getCppuType((Reference<XPropertySet>*)0);
}

sal_Bool SwXRedlines::hasElements(  ) throw(RuntimeException)
{
    SolarMutexGuard aGuard;
    if(!IsValid())
        throw uno::RuntimeException();
    const SwRedlineTbl& rRedTbl = GetDoc()->GetRedlineTbl();
    return rRedTbl.Count() > 0;
}

OUString SwXRedlines::getImplementationName(void) throw( RuntimeException )
{
    return C2U("SwXRedlines");
}

BOOL SwXRedlines::supportsService(const ::rtl::OUString& /*ServiceName*/)
    throw( RuntimeException )
{
    OSL_FAIL("not implemented");
    return FALSE;
}

Sequence< OUString > SwXRedlines::getSupportedServiceNames(void)
    throw( RuntimeException )
{
    OSL_FAIL("not implemented");
    return Sequence< OUString >();
}

XPropertySet*   SwXRedlines::GetObject( SwRedline& rRedline, SwDoc& rDoc )
{
    SwPageDesc* pStdDesc = rDoc.GetPageDescFromPool(RES_POOLPAGE_STANDARD);
    SwClientIter aIter(*pStdDesc);
    SwXRedline* pxRedline = (SwXRedline*)aIter.First( TYPE( SwXRedline ));
    while(pxRedline)
    {
        if(pxRedline->GetRedline() == &rRedline)
            break;
        pxRedline = (SwXRedline*)aIter.Next();
    }
    if( !pxRedline )
        pxRedline = new SwXRedline(rRedline, rDoc);
    return pxRedline;
}

SwXRedlineEnumeration::SwXRedlineEnumeration(SwDoc& rDoc) :
    pDoc(&rDoc),
    nCurrentIndex(0)
{
    pDoc->GetPageDescFromPool(RES_POOLPAGE_STANDARD)->Add(this);
}

SwXRedlineEnumeration::~SwXRedlineEnumeration()
{
}

BOOL SwXRedlineEnumeration::hasMoreElements(void) throw( RuntimeException )
{
    if(!pDoc)
        throw RuntimeException();
    return pDoc->GetRedlineTbl().Count() > nCurrentIndex;
}

Any SwXRedlineEnumeration::nextElement(void)
    throw( NoSuchElementException, WrappedTargetException, RuntimeException )
{
    if(!pDoc)
        throw RuntimeException();
    const SwRedlineTbl& rRedTbl = pDoc->GetRedlineTbl();
    if(!(rRedTbl.Count() > nCurrentIndex))
        throw NoSuchElementException();
    Reference <XPropertySet> xRet = SwXRedlines::GetObject( *rRedTbl.GetObject(nCurrentIndex++), *pDoc );
    Any aRet;
    aRet <<= xRet;
    return aRet;
}

rtl::OUString SwXRedlineEnumeration::getImplementationName(void) throw( RuntimeException )
{
    return C2U("SwXRedlineEnumeration");
}

BOOL SwXRedlineEnumeration::supportsService(const ::rtl::OUString& /*ServiceName*/) throw( RuntimeException )
{
    return FALSE;
}

Sequence< OUString > SwXRedlineEnumeration::getSupportedServiceNames(void) throw( RuntimeException )
{
    return Sequence< OUString >();
}

void SwXRedlineEnumeration::Modify( SfxPoolItem *pOld, SfxPoolItem *pNew)
{
    ClientModify(this, pOld, pNew);
    if(!GetRegisteredIn())
        pDoc = 0;
}
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
