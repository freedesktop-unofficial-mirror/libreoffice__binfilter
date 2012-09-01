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
#ifndef _SVX_SVXFONT_HXX
#define _SVX_SVXFONT_HXX

#include <bf_svtools/bf_solar.h>

#include <limits.h>     // USHRT_MAX

#include <bf_svx/svxenum.hxx>

#include <i18npool/lang.h>
#include <vcl/font.hxx>
class OutputDevice;
class Printer;
namespace binfilter {

class SvxFont : public Font
{
    LanguageType eLang;         // Language
    SvxCaseMap   eCaseMap;      // Textauszeichnung
    short nEsc;                 // Grad der Hoch-/Tiefstellung
    BYTE  nPropr;               // Grad der Verkleinerung der Fonthoehe
    short nKern;                // Kerning in Pt

public:
    SvxFont();
    SvxFont( const Font &rFont );
    SvxFont( const SvxFont &rFont );

    // Methoden fuer die Hoch-/Tiefstellung
    inline short GetEscapement() const { return nEsc; }
    inline void SetEscapement( const short nNewEsc ) { nEsc = nNewEsc; }

    inline BYTE GetPropr() const { return nPropr; }
    inline void SetPropr( const BYTE nNewPropr ) { nPropr = nNewPropr; }
    inline void SetProprRel( const BYTE nNewPropr )
        { SetPropr( (BYTE)( (long)nNewPropr * (long)nPropr / 100L ) ); }

    // Kerning
    inline short GetFixKerning() const { return nKern; }
    inline void  SetFixKerning( const short nNewKern ) { nKern = nNewKern; }

    inline SvxCaseMap GetCaseMap() const { return eCaseMap; }
    inline void    SetCaseMap( const SvxCaseMap eNew ) { eCaseMap = eNew; }

    inline LanguageType GetLanguage() const { return eLang; }
    inline void SetLanguage( const LanguageType eNewLan ) { eLang = eNewLan; }

    // Is-Methoden:
    inline BOOL IsCaseMap() const { return SVX_CASEMAP_NOT_MAPPED != eCaseMap; }
    inline BOOL IsCapital() const { return SVX_CASEMAP_KAPITAELCHEN == eCaseMap; }
    inline BOOL IsKern() const { return 0 != nKern; }
    inline BOOL IsEsc() const { return 0 != nEsc; }

    // Versalien, Gemeine etc. beruecksichtigen
    String CalcCaseMap( const String &rTxt ) const;

    // Kapitaelchenbearbeitung

    void SetPhysFont( OutputDevice *pOut ) const;



    Size GetPhysTxtSize( const OutputDevice *pOut, const String &rTxt );



    void QuickDrawText( OutputDevice *pOut, const Point &rPos, const String &rTxt,
               const USHORT nIdx = 0, const USHORT nLen = STRING_LEN, const sal_Int32* pDXArray = NULL ) const;

    Size QuickGetTextSize( const OutputDevice *pOut, const String &rTxt,
                         const USHORT nIdx, const USHORT nLen, sal_Int32* pDXArray = NULL ) const;


    SvxFont&    operator=( const SvxFont& rFont );
    SvxFont&    operator=( const Font& rFont );
};

}//end of namespace binfilter
#endif // #ifndef   _SVX_SVXFONT_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
