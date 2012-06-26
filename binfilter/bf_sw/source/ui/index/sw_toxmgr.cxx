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

#include <horiornt.hxx>

#include <viewsh.hxx>
#include <shellres.hxx>

#include <globals.hrc>

#include <tox.hxx>

namespace binfilter {

/*--------------------------------------------------
    Standard - Verzeichnisnamen herausreichen
--------------------------------------------------*/
/*N*/ const String& SwTOXBase::GetTOXName(TOXTypes eType)
/*N*/ {
/*N*/   const String* pRet;
/*N*/   ShellResource* pShellRes = ViewShell::GetShellRes();
/*N*/   switch(eType)
/*N*/   {
/*N*/       default:
/*N*/       case  TOX_CONTENT      :    pRet = &pShellRes->aTOXContentName;       break;
/*N*/       case  TOX_INDEX        :    pRet = &pShellRes->aTOXIndexName;         break;
/*?*/       case  TOX_USER         :    pRet = &pShellRes->aTOXUserName;          break;
/*?*/       case  TOX_ILLUSTRATIONS:    pRet = &pShellRes->aTOXIllustrationsName; break;
/*?*/       case  TOX_OBJECTS      :    pRet = &pShellRes->aTOXObjectsName;       break;
/*?*/       case  TOX_TABLES       :    pRet = &pShellRes->aTOXTablesName;        break;
/*?*/       case  TOX_AUTHORITIES :     pRet = &pShellRes->aTOXAuthoritiesName;   break;
/*N*/   }
/*N*/   return *pRet;
/*N*/ }

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
