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

#include <bf_svtools/zforlist.hxx>

#include <tools/debug.hxx>
#include "misccfg.hxx"
namespace binfilter {

#define DEFAULT_TAB 2000

#define DEF_INCH    2540L
#define DEF_RELTWIP 1440L

using namespace ::com::sun::star::uno;

using ::rtl::OUString;

/*--------------------------------------------------------------------
     Beschreibung:
 --------------------------------------------------------------------*/
/*N*/ SfxMiscCfg::SfxMiscCfg() :
/*N*/   ConfigItem(OUString::createFromAscii("Office.Common") ),
/*N*/   bPaperSize(FALSE),
/*N*/   bPaperOrientation (FALSE),
/*N*/   bNotFound (FALSE),
/*N*/   nYear2000( SvNumberFormatter::GetYear2000Default() )
/*N*/ {
/*N*/   Load();
/*N*/ }


/*N*/ const Sequence<OUString>& SfxMiscCfg::GetPropertyNames()
/*N*/ {
/*N*/   static Sequence<OUString> aNames;
/*N*/   if(!aNames.getLength())
/*N*/   {
/*N*/       static const char* aPropNames[] =
/*N*/       {
/*N*/           "Print/Warning/PaperSize",              //  0
/*N*/           "Print/Warning/PaperOrientation",       //  1
/*N*/           "Print/Warning/NotFound",               //  2
/*N*/           "DateFormat/TwoDigitYear",              //  3
/*N*/       };
/*N*/       const int nCount = 4;
/*N*/       aNames.realloc(nCount);
/*N*/       OUString* pNames = aNames.getArray();
/*N*/       for(int i = 0; i < nCount; i++)
/*N*/           pNames[i] = OUString::createFromAscii(aPropNames[i]);
/*N*/   }
/*N*/   return aNames;
/*N*/ }


/*N*/ void SfxMiscCfg::Load()
/*N*/ {
/*N*/   const Sequence<OUString>& aNames = GetPropertyNames();
/*N*/   Sequence<Any> aValues = GetProperties(aNames);
/*N*/   EnableNotification(aNames);
/*N*/   const Any* pValues = aValues.getConstArray();
/*N*/   DBG_ASSERT(aValues.getLength() == aNames.getLength(), "GetProperties failed");
/*N*/   if(aValues.getLength() == aNames.getLength())
/*N*/   {
/*N*/       for(int nProp = 0; nProp < aNames.getLength(); nProp++)
/*N*/       {
/*N*/           if(pValues[nProp].hasValue())
/*N*/           {
/*N*/               switch(nProp)
/*N*/               {
/*N*/                   case  0: bPaperSize        = *(sal_Bool*)pValues[nProp].getValue(); break;   //"Print/Warning/PaperSize",
/*N*/                   case  1: bPaperOrientation = *(sal_Bool*)pValues[nProp].getValue(); break;   //"Print/Warning/PaperOrientation",
/*N*/                   case  2: bNotFound         = *(sal_Bool*)pValues[nProp].getValue(); break;   //"Print/Warning/NotFound",
/*N*/                   case  3: pValues[nProp] >>= nYear2000; break;                                //"DateFormat/TwoDigitYear",
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }


/*?*/ void SfxMiscCfg::Notify( const ::com::sun::star::uno::Sequence<rtl::OUString>& /*aPropertyNames*/)
/*?*/ {
/*?*/   Load();
/*?*/ }


void SfxMiscCfg::Commit()
{
    DBG_BF_ASSERT(0, "STRIP");  // VIRTUAL
}

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
