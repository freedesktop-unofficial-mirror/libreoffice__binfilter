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

#include "itemholder2.hxx"

//-----------------------------------------------
// includes

#include <comphelper/processfactory.hxx>

#include <com/sun/star/lang/XComponent.hpp>

#include <bf_svtools/cjkoptions.hxx>
#include <bf_svtools/colorcfg.hxx>
#include <bf_svtools/ctloptions.hxx>
#include <unotools/configitem.hxx>
#include <bf_svtools/helpopt.hxx>
#include <bf_svtools/languageoptions.hxx>
#include <misccfg.hxx>
#include <bf_svtools/printoptions.hxx>
#include <bf_svtools/syslocaleoptions.hxx>
#include <bf_svtools/undoopt.hxx>
#include <bf_svtools/useroptions.hxx>
#include <bf_svtools/options.hxx>
#include <bf_svtools/miscopt.hxx>


#include <tools/debug.hxx>

//-----------------------------------------------
// namespaces

namespace css = ::com::sun::star;

namespace binfilter
{

//-----------------------------------------------
// declarations

//-----------------------------------------------
ItemHolder2::ItemHolder2()
    : ItemHolderMutexBase()
{
    try
    {
        css::uno::Reference< css::lang::XMultiServiceFactory > xSMGR = ::comphelper::getProcessServiceFactory();
        css::uno::Reference< css::lang::XComponent > xCfg(
            xSMGR->createInstance(::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.configuration.ConfigurationProvider" ))),
            css::uno::UNO_QUERY);
        if (xCfg.is())
            xCfg->addEventListener(static_cast< css::lang::XEventListener* >(this));
    }
    catch(css::uno::RuntimeException& rREx)
    {
        throw rREx;
    }
#ifdef DBG_UTIL
    catch(css::uno::Exception& rEx)
    {
        static sal_Bool bMessage = sal_True;
        if(bMessage)
        {
            bMessage = sal_False;
            ::rtl::OString sMsg("CreateInstance with arguments exception: ");
            sMsg += ::rtl::OString(rEx.Message.getStr(),
                        rEx.Message.getLength(),
                        RTL_TEXTENCODING_ASCII_US);
            OSL_FAIL(sMsg.getStr());
        }
    }
#else
    catch(css::uno::Exception&){}
#endif
}

//-----------------------------------------------
ItemHolder2::~ItemHolder2()
{
    impl_releaseAllItems();
}

//-----------------------------------------------
void ItemHolder2::holdConfigItem(EItem eItem)
{
    static ItemHolder2* pHolder = new ItemHolder2();
    pHolder->impl_addItem(eItem);
}

//-----------------------------------------------
void SAL_CALL ItemHolder2::disposing(const css::lang::EventObject&)
    throw(css::uno::RuntimeException)
{
    impl_releaseAllItems();
}

//-----------------------------------------------
void ItemHolder2::impl_addItem(EItem eItem)
{
    ::osl::ResettableMutexGuard aLock(m_aLock);

    TItems::const_iterator pIt;
    for (  pIt  = m_lItems.begin();
           pIt != m_lItems.end()  ;
         ++pIt                    )
    {
        const TItemInfo& rInfo = *pIt;
        if (rInfo.eItem == eItem)
            return;
    }

    TItemInfo aNewItem;
    aNewItem.eItem = eItem;
    impl_newItem(aNewItem);
    if (aNewItem.pItem)
        m_lItems.push_back(aNewItem);
}

//-----------------------------------------------
void ItemHolder2::impl_releaseAllItems()
{
    ::osl::ResettableMutexGuard aLock(m_aLock);

    TItems::iterator pIt;
    for (  pIt  = m_lItems.begin();
           pIt != m_lItems.end()  ;
         ++pIt                    )
    {
        TItemInfo& rInfo = *pIt;
        impl_deleteItem(rInfo);
    }
    m_lItems.clear();
}

//-----------------------------------------------
void ItemHolder2::impl_newItem(TItemInfo& rItem)
{
    switch(rItem.eItem)
    {
        case E_APEARCFG :
            break;

        case E_CJKOPTIONS :
            rItem.pItem = new SvtCJKOptions();
            break;

        case E_COLORCFG :
            rItem.pItem = new ColorConfig();
            break;

        case E_CTLOPTIONS :
            rItem.pItem = new SvtCTLOptions();
            break;

        case E_FONTSUBSTCONFIG :
            break;

        case E_HELPOPTIONS :
            rItem.pItem = new SvtHelpOptions();
            break;

        case E_LANGUAGEOPTIONS :
// capsulate CTL and CJL options !            rItem.pItem = new SvtLanguageOptions();
            break;

        case E_MISCCFG :
// no ref count            rItem.pItem = new SfxMiscCfg();
            break;

        case E_PRINTOPTIONS :
            rItem.pItem = new SvtPrinterOptions();
            break;

        case E_PRINTFILEOPTIONS :
            rItem.pItem = new SvtPrintFileOptions();
            break;

        case E_SYSLOCALEOPTIONS :
            rItem.pItem = new SvtSysLocaleOptions();
            break;

        case E_UNDOOPTIONS :
            rItem.pItem = new SvtUndoOptions();
            break;

        case E_USEROPTIONS :
            rItem.pItem = new SvtUserOptions();
            break;
        case E_MISCOPTIONS :
            rItem.pItem = new SvtMiscOptions();
            break;

        default:
            OSL_ASSERT(false);
            break;
    }
}

//-----------------------------------------------
void ItemHolder2::impl_deleteItem(TItemInfo& rItem)
{
    if (rItem.pItem)
    {
        delete rItem.pItem;
        rItem.pItem = 0;
    }
}
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
