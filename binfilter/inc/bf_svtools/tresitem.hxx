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

#ifndef SVTOOLS_TRESITEM_HXX
#define SVTOOLS_TRESITEM_HXX

#include <bf_svtools/bf_solar.h>

#include <com/sun/star/ucb/TransferResult.hpp>

#include <bf_svtools/poolitem.hxx>

namespace binfilter
{

//============================================================================
class CntTransferResultItem: public SfxPoolItem
{
    com::sun::star::ucb::TransferResult m_aResult;

public:
    TYPEINFO();

    CntTransferResultItem(USHORT which = 0): SfxPoolItem(which) {}

    CntTransferResultItem(USHORT which,
                          com::sun::star::ucb::TransferResult const &
                              rTheResult):
        SfxPoolItem(which), m_aResult(rTheResult) {}

    virtual int operator ==(SfxPoolItem const & rItem) const;

    virtual bool QueryValue(com::sun::star::uno::Any & rVal, BYTE = 0) const;

    virtual bool PutValue(const com::sun::star::uno::Any & rVal, BYTE = 0);

    virtual SfxPoolItem * Clone(SfxItemPool * = 0) const;

    com::sun::star::ucb::TransferResult const & GetValue() const
    { return m_aResult; }
};

}

#endif // SVTOOLS_TRESITEM_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
