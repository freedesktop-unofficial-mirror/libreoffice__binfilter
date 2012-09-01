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

#include "misccfg.hxx"

#include <bf_svtools/zforlist.hxx>

#include <tools/debug.hxx>

#include <rtl/logfile.hxx>


#define DEFAULT_TAB 2000

#define DEF_INCH    2540L
#define DEF_RELTWIP 1440L

using namespace com::sun::star::uno;

using ::rtl::OUString;

namespace binfilter
{

#define C2U(cChar) OUString::createFromAscii(cChar)
/*--------------------------------------------------------------------
     Beschreibung:
 --------------------------------------------------------------------*/
SfxMiscCfg::SfxMiscCfg() :
    ConfigItem(C2U("Office.Common") ),
    bPaperSize(FALSE),
    bPaperOrientation (FALSE),
    bNotFound (FALSE),
    nYear2000( SvNumberFormatter::GetYear2000Default() )
{
    RTL_LOGFILE_CONTEXT(aLog, "svtools SfxMiscCfg::SfxMiscCfg()");

    Load();
}


SfxMiscCfg::~SfxMiscCfg()
{
}



const Sequence<OUString>& SfxMiscCfg::GetPropertyNames()
{
    static Sequence<OUString> aNames;
    if(!aNames.getLength())
    {
        static const char* aPropNames[] =
        {
               "Print/Warning/PaperSize",               //  0
               "Print/Warning/PaperOrientation",        //  1
               "Print/Warning/NotFound",                //  2
            "DateFormat/TwoDigitYear",              //  3
        };
        const int nCount = 4;
        aNames.realloc(nCount);
        OUString* pNames = aNames.getArray();
        for(int i = 0; i < nCount; i++)
            pNames[i] = OUString::createFromAscii(aPropNames[i]);
    }
    return aNames;
}


void SfxMiscCfg::Load()
{
    const Sequence<OUString>& aNames = GetPropertyNames();
    Sequence<Any> aValues = GetProperties(aNames);
    EnableNotification(aNames);
    const Any* pValues = aValues.getConstArray();
    DBG_ASSERT(aValues.getLength() == aNames.getLength(), "GetProperties failed");
    if(aValues.getLength() == aNames.getLength())
    {
        for(int nProp = 0; nProp < aNames.getLength(); nProp++)
        {
            if(pValues[nProp].hasValue())
            {
                switch(nProp)
                {
                    case  0: bPaperSize        = *(sal_Bool*)pValues[nProp].getValue(); break;      //"Print/Warning/PaperSize",
                    case  1: bPaperOrientation = *(sal_Bool*)pValues[nProp].getValue();  break;     //"Print/Warning/PaperOrientation",
                    case  2: bNotFound         = *(sal_Bool*)pValues[nProp].getValue()  ;  break;   //"Print/Warning/NotFound",
                    case  3: pValues[nProp] >>= nYear2000;break;                                    //"DateFormat/TwoDigitYear",
                }
            }
        }
    }
}


void SfxMiscCfg::Notify( const com::sun::star::uno::Sequence<rtl::OUString>& )
{
    Load();
}


void SfxMiscCfg::Commit()
{
    const Sequence<OUString>& aNames = GetPropertyNames();
    Sequence<Any> aValues(aNames.getLength());
    Any* pValues = aValues.getArray();

    const Type& rType = ::getBooleanCppuType();
    for(int nProp = 0; nProp < aNames.getLength(); nProp++)
    {
        switch(nProp)
        {
            case  0: pValues[nProp].setValue(&bPaperSize, rType);break;  //"Print/Warning/PaperSize",
            case  1: pValues[nProp].setValue(&bPaperOrientation, rType);break;     //"Print/Warning/PaperOrientation",
            case  2: pValues[nProp].setValue(&bNotFound, rType);break;   //"Print/Warning/NotFound",
            case  3: pValues[nProp] <<= nYear2000;break;                 //"DateFormat/TwoDigitYear",
        }
    }
    PutProperties(aNames, aValues);
}

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
