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
#ifndef INCLUDED_SVTOOLS_USEROPTIONS_HXX
#define INCLUDED_SVTOOLS_USEROPTIONS_HXX


#include <unotools/configitem.hxx>
#include <bf_tools/string.hxx>
#include <osl/mutex.hxx>
#include <bf_svtools/brdcst.hxx>
#include <bf_svtools/lstner.hxx>
#include <bf_svtools/options.hxx>

namespace binfilter
{

// define ----------------------------------------------------------------

#define USER_OPT_CITY               ((USHORT)0)
#define USER_OPT_COMPANY            ((USHORT)1)
#define USER_OPT_COUNTRY            ((USHORT)2)
#define USER_OPT_EMAIL              ((USHORT)3)
#define USER_OPT_FAX                ((USHORT)4)
#define USER_OPT_FIRSTNAME          ((USHORT)5)
#define USER_OPT_LASTNAME           ((USHORT)6)
#define USER_OPT_POSITION           ((USHORT)7)
#define USER_OPT_STATE              ((USHORT)8)
#define USER_OPT_STREET             ((USHORT)9)
#define USER_OPT_TELEPHONEHOME      ((USHORT)10)
#define USER_OPT_TELEPHONEWORK      ((USHORT)11)
#define USER_OPT_TITLE              ((USHORT)12)
#define USER_OPT_ID                 ((USHORT)13)
#define USER_OPT_ZIP                ((USHORT)14)
#define USER_OPT_FATHERSNAME        ((USHORT)15)
#define USER_OPT_APARTMENT          ((USHORT)16)

// class SvtUserOptions --------------------------------------------------

class SvtUserOptions_Impl;

class  SvtUserOptions : public Options, public SfxBroadcaster, public SfxListener
{
private:
    SvtUserOptions_Impl*    pImp;

public:
    SvtUserOptions();
    virtual ~SvtUserOptions();

    static ::osl::Mutex&    GetInitMutex();

    virtual void        Notify( SfxBroadcaster& rBC, const SfxHint& rHint );

    // get the address token
    const String&   GetCompany() const;
    const String&   GetFirstName() const;
    const String&   GetLastName() const;
    const String&   GetID() const;
    const String&   GetStreet() const;
    const String&   GetCity() const;
    const String&   GetState() const;
    const String&   GetZip() const;
    const String&   GetCountry() const;
    const String&   GetPosition() const;
    const String&   GetTitle() const;
    const String&   GetTelephoneHome() const;
    const String&   GetTelephoneWork() const;
    const String&   GetFax() const;
    const String&   GetEmail() const;

    const String&   GetFullName() const;
};

}

#endif // #ifndef INCLUDED_SVTOOLS_USEROPTIONS_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
