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

#include <dbconfig.hxx>

#include <tools/debug.hxx>
#include <com/sun/star/uno/Sequence.hxx>
#include <swdbdata.hxx>
namespace binfilter {
using namespace utl;
using namespace ::com::sun::star::uno;
using ::rtl::OUString;

/*N*/ #define C2U(cChar) OUString::createFromAscii(cChar)
/*--------------------------------------------------------------------
     Beschreibung: Ctor
 --------------------------------------------------------------------*/

/*N*/ const Sequence<OUString>& SwDBConfig::GetPropertyNames()
/*N*/ {
/*N*/   static Sequence<OUString> aNames;
/*N*/   if(!aNames.getLength())
/*N*/   {
/*N*/       static const char* aPropNames[] =
/*N*/       {
/*N*/             "AddressBook/DataSourceName",        //  0
/*N*/             "AddressBook/Command",              //  1
/*N*/             "AddressBook/CommandType",          //  2
/*N*/             "Bibliography/CurrentDataSource/DataSourceName",        //  4
/*N*/             "Bibliography/CurrentDataSource/Command",              //  5
/*N*/             "Bibliography/CurrentDataSource/CommandType"          //  6
/*N*/         };
/*N*/         const int nCount = sizeof(aPropNames)/sizeof(const char*);
/*N*/       aNames.realloc(nCount);
/*N*/       OUString* pNames = aNames.getArray();
/*N*/       for(int i = 0; i < nCount; i++)
/*N*/           pNames[i] = OUString::createFromAscii(aPropNames[i]);
/*N*/   }
/*N*/   return aNames;
/*N*/ }


/*N*/ SwDBConfig::SwDBConfig() :
/*N*/     ConfigItem(C2U("Office.DataAccess"),
/*N*/         CONFIG_MODE_DELAYED_UPDATE|CONFIG_MODE_RELEASE_TREE),
/*N*/     pAdrImpl(0),
/*N*/     pBibImpl(0)
/*N*/ {
/*N*/ };


/*N*/ SwDBConfig::~SwDBConfig()
/*N*/ {
/*N*/     delete pAdrImpl;
/*N*/     delete pBibImpl;
/*N*/ }


/*N*/ void SwDBConfig::Load()
/*N*/ {
/*N*/   const Sequence<OUString>& rNames = GetPropertyNames();
/*N*/     if(!pAdrImpl)
/*N*/   {
/*N*/
/*N*/         pAdrImpl = new SwDBData;
/*N*/         pAdrImpl->nCommandType = 0;
/*N*/         pBibImpl = new SwDBData;
/*N*/         pBibImpl->nCommandType = 0;
/*N*/     }
/*N*/   Sequence<Any> aValues = GetProperties(rNames);
/*N*/   const Any* pValues = aValues.getConstArray();
/*N*/   DBG_ASSERT(aValues.getLength() == rNames.getLength(), "GetProperties failed");
/*N*/   if(aValues.getLength() == rNames.getLength())
/*N*/   {
/*N*/       for(int nProp = 0; nProp < rNames.getLength(); nProp++)
/*N*/       {
/*N*/           switch(nProp)
/*N*/           {
/*N*/                 case  0: pValues[nProp] >>= pAdrImpl->sDataSource;  break;
/*N*/                 case  1: pValues[nProp] >>= pAdrImpl->sCommand;     break;
/*N*/                 case  2: pValues[nProp] >>= pAdrImpl->nCommandType; break;
/*N*/                 case  3: pValues[nProp] >>= pBibImpl->sDataSource;  break;
/*N*/                 case  4: pValues[nProp] >>= pBibImpl->sCommand;     break;
/*N*/                 case  5: pValues[nProp] >>= pBibImpl->nCommandType; break;
/*N*/             }
/*N*/       }
/*N*/   }
/*N*/ }


/*N*/ const SwDBData& SwDBConfig::GetAddressSource()
/*N*/ {
/*N*/     if(!pAdrImpl)
/*N*/       Load();
/*N*/     return *pAdrImpl;
/*N*/ }

    void SwDBConfig::Commit() {}
    void SwDBConfig::Notify( const ::com::sun::star::uno::Sequence< rtl::OUString >& ) {}

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
