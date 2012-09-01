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
#ifndef _SHELLRES_HXX
#define _SHELLRES_HXX

#include <bf_svtools/bf_solar.h>


#include <tools/rc.hxx>
#include <vcl/bitmap.hxx>

#ifndef _SVSTDARR_HXX
#define _SVSTDARR_STRINGSDTOR
#include <bf_svtools/svstdarr.hxx>
#endif
namespace binfilter {

struct ShellResource : public Resource
{
    String          aPostItAuthor;
    String          aPostItPage;
    String          aPostItLine;

    // Calc Fehlerstrings
    String          aCalc_Syntax;
    String          aCalc_ZeroDiv;
    String          aCalc_Brack;
    String          aCalc_Pow;
    String          aCalc_VarNFnd;
    String          aCalc_Overflow;
    String          aCalc_WrongTime;
    String          aCalc_Default;
    String          aCalc_Error;

    // fuers GetRefFeld - oben/unten
    String          aGetRefFld_Up, aGetRefFld_Down;
    // fuer dynamisches Menu - String "alle"
    String          aStrAllPageHeadFoot;
    // fuer einige Listboxen - String "keine"
    String          aStrNone;
    // fuer Felder, die Fixiert sind
    String          aFixedStr;

    //names of TOXs
    String          aTOXIndexName;
    String          aTOXUserName;
    String          aTOXContentName;
    String          aTOXIllustrationsName;
    String          aTOXObjectsName;
    String          aTOXTablesName;
    String          aTOXAuthoritiesName;

    SvStringsDtor   aDocInfoLst;

    // Fly-Anker Bmps
//  Bitmap          aAnchorBmp;
//  Bitmap          aDragAnchorBmp;

    // die AutoFormat-Redline-Kommentare
    inline const SvStringsDtor& GetAutoFmtNameLst() const;

    ShellResource();
    ~ShellResource();

private:
    void _GetAutoFmtNameLst() const;
    SvStringsDtor   *pAutoFmtNameLst;
    String          sPageDescFirstName, sPageDescFollowName, sPageDescName;
};

inline const SvStringsDtor& ShellResource::GetAutoFmtNameLst() const
{
    if( !pAutoFmtNameLst )
        _GetAutoFmtNameLst();
    return *pAutoFmtNameLst;
}


} //namespace binfilter
#endif //_SHELLRES_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
