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

#include <bf_svtools/tresitem.hxx>

using namespace com::sun::star;

namespace binfilter
{

//============================================================================
//
//  CntTransferResultItem
//
//============================================================================

TYPEINIT1_AUTOFACTORY(CntTransferResultItem, SfxPoolItem)

//============================================================================
// virtual
int CntTransferResultItem::operator ==(SfxPoolItem const & rItem) const
{
    if (CntTransferResultItem * pResultItem = PTR_CAST(CntTransferResultItem,
                                                       &rItem))
        return m_aResult.Source == pResultItem->m_aResult.Source
               && m_aResult.Target == pResultItem->m_aResult.Target
               && m_aResult.Result == pResultItem->m_aResult.Result;
    return false;
}

//============================================================================
// virtual
bool CntTransferResultItem::QueryValue(uno::Any & rVal, BYTE) const
{
    rVal <<= m_aResult;
    return true;
}

//============================================================================
// virtual
bool CntTransferResultItem::PutValue(uno::Any const & rVal, BYTE)
{
    return rVal >>= m_aResult;
}

//============================================================================
// virtual
SfxPoolItem * CntTransferResultItem::Clone(SfxItemPool *) const
{
    return new CntTransferResultItem(*this);
}

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
