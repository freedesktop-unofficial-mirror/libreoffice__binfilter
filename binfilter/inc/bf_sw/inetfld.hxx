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
#ifndef _INETFLD_HXX
#define _INETFLD_HXX

#include <bf_svtools/bf_solar.h>


#include "fldbas.hxx"

namespace binfilter {
class SvxMacro;
class SvxMacroTableDtor;

class SwINetField;
class SwCharFmt;
class SwDoc;

/*--------------------------------------------------------------------
    Beschreibung: InterNet-FieldType -> Lade Document mit der URL
 --------------------------------------------------------------------*/

class SwINetFieldType : public SwFieldType
{
    SwDepend aNormalFmt;
    SwDepend aVisitFmt;
    SwDoc* pDoc;

public:
    SwINetFieldType( SwDoc* pDoc );

    virtual SwFieldType*    Copy() const;

    SwCharFmt*              GetCharFmt( const SwINetField& rFld );

    SwDoc* GetDoc() const   { return pDoc; }
};

/*--------------------------------------------------------------------
    Beschreibung: InterNet-Field -> Lade Document mit der URL
 --------------------------------------------------------------------*/

class SwINetField : public SwField
{
    friend class SwINetFieldType;

    String  sTargetFrameName;   // in diesen Frame soll die URL
    String  sURL;
    String  sText;
    SvxMacroTableDtor* pMacroTbl;

public:
    // Direkte Eingabe alten Wert loeschen
    SwINetField( SwINetFieldType* pTyp, USHORT nFmt,
                  const String& rURL, const String& rText );
    virtual ~SwINetField();

    virtual String   GetCntnt(BOOL bName = FALSE) const;
    virtual String   Expand() const;
    virtual SwField* Copy() const;

    // URL
    virtual const String& GetPar1() const;
    virtual void    SetPar1(const String& rStr);

    // HinweisText
    virtual String  GetPar2() const;
    virtual void    SetPar2(const String& rStr);

    // das ist das akt. Zeichenformat
          SwCharFmt* GetCharFmt();
    const SwCharFmt* GetCharFmt() const
            { return ((SwINetField*)this)->GetCharFmt(); }

    const String& GetTargetFrameName() const        { return sTargetFrameName; }
    void SetTargetFrameName( const String& rNm )    { sTargetFrameName = rNm; }

    // setze eine neue oder loesche die akt. MakroTabelle
    void SetMacroTbl( const SvxMacroTableDtor* pTbl = 0 );
    const SvxMacroTableDtor* GetMacroTbl() const    { return pMacroTbl; }

    // setze / erfrage ein Makro
    void SetMacro( USHORT nEvent, const SvxMacro& rMacro );
    const SvxMacro* GetMacro( USHORT nEvent ) const;
};


} //namespace binfilter
#endif // _INETFLD_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
