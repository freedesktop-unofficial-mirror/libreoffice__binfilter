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

#ifndef _FACTORY_HXX
#define _FACTORY_HXX

#include <bf_svtools/bf_solar.h>
#include <bf_tools/string.hxx>
#include <bf_so3/so2ref.hxx>
#include <bf_svtools/brdcst.hxx>
#include <tools/globname.hxx>
#include <sot/factory.hxx>
#include <com/sun/star/datatransfer/XTransferable.hpp>

#include "bf_so3/so3dllapi.h"

namespace binfilter {
class SvObject;
class SvStorage;
class SvFactory_Impl;

typedef SvGlobalName SvUniqueName;

//==================class SvFactory========================================
class SO3_DLLPUBLIC SvFactory : public SotFactory
/*  [Beschreibung]

    Die Methoden der Klasse kann man in zwei Gruppen aufteilen.
    Erstens allgemeine Verwaltung des So-Projektes. Dies bedeutet den
    Zugriff auf Resourcen, Variablen und Methoden, die das Projekt
    zur Verfuegung stellt. Alle diese Methoden sind static.
    Zweitens bereitstellen von speziellen Informationen "uber die
    einzelnen Klassen. Diese Methoden sind nicht static. Factories f"ur
    verschiedene Klassen bekommt man "uber die Methode
    Klasse::ClassFactory (<SvObject::ClassFactory>). Die Factory zu einem
    Objekt bekommt man durch <SvObject::GetSvFactory>.
*/
{
    SvFactory_Impl *    pImp;
    ULONG               nRegisterId;
protected:
    virtual             ~SvFactory();
public:
                        TYPEINFO();

    static  BOOL                    Init();

    static  void                    SetDefaultPlugInFactory( SvFactory * );
    static  SvFactory *             GetDefaultPlugInFactory();

    static  void                    SetDefaultAppletFactory( SvFactory * );
    static  SvFactory *             GetDefaultAppletFactory();

    SvObjectRef         Create( const SvGlobalName & rSvClassName ) const;
    SvObjectRef         CreateAndLoad( SvStorage *, BOOL bLink = FALSE ) const;
    SvObjectRef         CreateAndLoad( SvStream &, ULONG * nLen = NULL ) const;
    SvObjectRef         CreateAndInit( const SvGlobalName & rSvClassName,
                                       SvStorage * ) const;

            SvFactory( const SvGlobalName &,
                       const String & rClassName, CreateInstanceType );

    void                Register();
    BOOL                IsRegistered() const { return nRegisterId != 0; }

    static SvGlobalName GetAutoConvertTo( const SvGlobalName & rClass );
    static BOOL         IsIntern( const SvGlobalName & rClass,
                                     long *pFileFormat  );
    static SvGlobalName GetServerName( long nStorageFormat );
    static String       GetServiceName( const SvGlobalName& );

private:
                        SvFactory( const SvFactory & );
    SvFactory &         operator = ( const SvFactory & );
};

#define SV_IMPL_FACTORY(ClassName)                                  \
class ClassName : public SvFactory                                  \
{                                                                   \
public:                                                             \
         TYPEINFO();                                                 \
        ClassName( const SvGlobalName & rName,                      \
                              const String & rClassName,              \
                              CreateInstanceType pCreateFuncP )       \
            : SvFactory( rName, rClassName, pCreateFuncP )

}

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
