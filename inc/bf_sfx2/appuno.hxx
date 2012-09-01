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
#ifndef _SFX_APPUNO_HXX
#define _SFX_APPUNO_HXX

//____________________________________________________________________________________________________________________________________
//  generated header
//____________________________________________________________________________________________________________________________________
#include <com/sun/star/frame/XFrame.hpp>
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#include <com/sun/star/lang/XServiceInfo.hpp>
#include <com/sun/star/lang/XInitialization.hpp>
#include <com/sun/star/lang/XTypeProvider.hpp>
#include <com/sun/star/registry/XSimpleRegistry.hpp>
#include <com/sun/star/beans/PropertyValue.hpp>
#include <com/sun/star/util/URL.hpp>
#include <com/sun/star/uno/Exception.hpp>
#include <com/sun/star/frame/XDispatchProvider.hpp>
#include <com/sun/star/frame/XDispatch.hpp>
#include <com/sun/star/frame/XSynchronousDispatch.hpp>
#include <com/sun/star/frame/XNotifyingDispatch.hpp>
#include <com/sun/star/frame/XDispatchResultListener.hpp>
#include <com/sun/star/frame/DispatchDescriptor.hpp>
#include <com/sun/star/lang/XMultiServiceFactory.hpp>

//____________________________________________________________________________________________________________________________________
//  fix uno header
//____________________________________________________________________________________________________________________________________
#include <com/sun/star/uno/Any.h>
#include <com/sun/star/uno/Reference.h>
#include <com/sun/star/uno/Sequence.hxx>
#include <cppuhelper/weak.hxx>
#include <cppuhelper/implbase3.hxx>

//____________________________________________________________________________________________________________________________________
//  something else header
//____________________________________________________________________________________________________________________________________

#include <tools/errcode.hxx>
#include <bf_svtools/svarray.hxx>
#define _SVSTDARR_STRINGSDTOR
#include <bf_svtools/svstdarr.hxx>
#include <bf_sfx2/sfxuno.hxx>
#include <bf_svtools/poolitem.hxx>

namespace binfilter {
class SfxAllItemSet;
class SfxItemSet;

class SfxUsrAnyItem : public SfxPoolItem
{
    ::com::sun::star::uno::Any  aValue;
public:
                                TYPEINFO();
                                SfxUsrAnyItem( sal_uInt16 nWhich, const ::com::sun::star::uno::Any& rAny );
    ::com::sun::star::uno::Any  GetValue() const
                                { return aValue; }
    virtual int                 operator==( const SfxPoolItem& ) const;
    virtual String              GetValueText() const{DBG_BF_ASSERT(0, "STRIP"); return String();}
    virtual SfxPoolItem*        Clone( SfxItemPool *pPool = 0 ) const;
};

typedef SfxUsrAnyItem SfxUnoAnyItem;

void TransformParameters(           sal_uInt16                          nSlotId     ,
                            const   UNOSEQUENCE< UNOPROPERTYVALUE >&    seqArgs     ,
                                    SfxAllItemSet&                      aSet    );

void TransformItems(        sal_uInt16                          nSlotId     ,
                            const   SfxItemSet&                         aSet        ,
                                    UNOSEQUENCE< UNOPROPERTYVALUE >&    seqArgs  );


}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
