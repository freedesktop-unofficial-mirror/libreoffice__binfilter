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
#ifndef _DOCFUNC_HXX
#define _DOCFUNC_HXX

#include <bf_svtools/bf_solar.h>


// Diese Klasse wird von der Editshell benutz um fuer belibige
// Doc-Aktionen ueber eine definierte Schnittstelle alle Cursor/
// Bookmarks/usw. aus dem Loeschbereich zu verschieben, mit einem
// anschliessenden Join-Node.
// Das wird zur Zeit vom
//      - Delete
//      - Replace
// benotigt.


#include <bf_tools/string.hxx>
namespace binfilter {
class SwPaM;

enum DocFNType { DOC_DELETE, DOC_REPLACE };

class SwCallDocFunction
{
    // Parameter fuers Replace  (leider kein union moeglich; Str-Klasse !!)
    const String aRplStr;
    DocFNType eDocFnType;
    BOOL bRplRegExp;

public:
    // fuer parameterlose Methoden
    SwCallDocFunction( DocFNType eDocFn ) : eDocFnType( eDocFn ), aRplStr() {}
    // fuer das Replace
    SwCallDocFunction( const String& rStr, BOOL bFlag );

    BOOL Call( SwPaM& );

    // ALLE Methoden stehen im eddel.cxx !!
};


} //namespace binfilter
#endif
    //_DOCFUNC_HXX


/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
