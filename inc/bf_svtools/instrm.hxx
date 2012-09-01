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

#ifndef SVTOOLS_INSTRM_HXX
#define SVTOOLS_INSTRM_HXX

#include <bf_svtools/bf_solar.h>

#include <com/sun/star/uno/Reference.h>
#include <tools/stream.hxx>

namespace com { namespace sun { namespace star { namespace io {
    class XInputStream;
    class XSeekable;
} } } }

namespace binfilter
{

class SvDataPipe_Impl;

//============================================================================
class  SvInputStream: public SvStream
{
    com::sun::star::uno::Reference< com::sun::star::io::XInputStream >
        m_xStream;
    com::sun::star::uno::Reference< com::sun::star::io::XSeekable >
        m_xSeekable;
    SvDataPipe_Impl * m_pPipe;
    ULONG m_nSeekedFrom;

     bool open();

     virtual ULONG GetData(void * pData, ULONG nSize);

     virtual ULONG PutData(void const *, ULONG);

     virtual ULONG SeekPos(ULONG nPos);

     virtual void FlushData();

     virtual void SetSize(ULONG);

public:
    SvInputStream(
        com::sun::star::uno::Reference< com::sun::star::io::XInputStream >
                const &
            rTheStream);

    virtual ~SvInputStream();

    virtual USHORT IsA() const;
};

}

#endif // SVTOOLS_INSTRM_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
