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

#ifndef _EERDLL2_HXX
#define _EERDLL2_HXX

#include <forbiddencharacterstable.hxx>
#include <rtl/ref.hxx>
namespace binfilter {

class SfxPoolItem;
class SvxAutoCorrect;

class GlobalEditData
{
private:
    SfxPoolItem**   ppDefItems;
    OutputDevice*   pStdRefDevice;

    Link            aGetAutoCorrectHdl;

    rtl::Reference<SvxForbiddenCharactersTable> xForbiddenCharsTable;

public:
                    GlobalEditData();
                    ~GlobalEditData();

    SfxPoolItem**   GetDefItems();
    OutputDevice*   GetStdRefDevice();

    void            SetGetAutoCorrectHdl( const Link& rHdl ) { aGetAutoCorrectHdl = rHdl; }
    SvxAutoCorrect* GetAutoCorrect() const { return (SvxAutoCorrect*) aGetAutoCorrectHdl.Call( NULL ); }

    rtl::Reference<SvxForbiddenCharactersTable> GetForbiddenCharsTable();
    void            SetForbiddenCharsTable( rtl::Reference<SvxForbiddenCharactersTable> xForbiddenChars ) { xForbiddenCharsTable = xForbiddenChars; }
};


}//end of namespace binfilter
#endif //_EERDLL2_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
