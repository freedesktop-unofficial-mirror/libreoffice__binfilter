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
#ifndef _SFXHINT_HXX
#define _SFXHINT_HXX

#include <bf_svtools/bf_solar.h>

#include <tools/rtti.hxx>

namespace binfilter
{

class  SfxHint
{
public:
    TYPEINFO();

    virtual ~SfxHint();
};

//--------------------------------------------------------------------

#define DECL_PTRHINT(Visibility, Name, Type) \
        class Visibility Name: public ::binfilter::SfxHint \
        { \
            Type* pObj; \
            BOOL  bIsOwner; \
        \
        public: \
            TYPEINFO(); \
            Name( Type* Object, BOOL bOwnedByHint = FALSE ); \
            ~Name(); \
        \
            Type* GetObject() const { return pObj; } \
            BOOL  IsOwner() const { return bIsOwner; } \
        }

#define IMPL_PTRHINT(Name, Type) \
        TYPEINIT1(Name, SfxHint);   \
        Name::Name( Type* pObject, BOOL bOwnedByHint ) \
            { pObj = pObject; bIsOwner = bOwnedByHint; } \
        Name::~Name() {}


}

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
