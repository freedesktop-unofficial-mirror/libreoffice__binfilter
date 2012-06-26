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
#ifndef INCLUDED_SVTOOLS_COLORCFG_HXX
#define INCLUDED_SVTOOLS_COLORCFG_HXX

#include "bf_svtools/svtdllapi.h"

#include <rtl/ustring.hxx>
#include <tools/color.hxx>
#include <com/sun/star/uno/Sequence.h>
#include <bf_svtools/brdcst.hxx>
#include <bf_svtools/lstner.hxx>
#include <bf_svtools/options.hxx>


//-----------------------------------------------------------------------------
namespace binfilter {
enum ColorConfigEntry
{
    DOCCOLOR            ,
    DOCBOUNDARIES       ,
    APPBACKGROUND       ,
    OBJECTBOUNDARIES    ,
    TABLEBOUNDARIES     ,
    FONTCOLOR           ,
    LINKS               ,
    LINKSVISITED        ,
    SPELL         ,
    SMARTTAGS     ,
    WRITERTEXTGRID      ,
    WRITERFIELDSHADINGS ,
    WRITERIDXSHADINGS         ,
    WRITERDIRECTCURSOR        ,
    WRITERSCRIPTINDICATOR,
    WRITERSECTIONBOUNDARIES,
    WRITERPAGEBREAKS,
    HTMLSGML            ,
    HTMLCOMMENT         ,
    HTMLKEYWORD         ,
    HTMLUNKNOWN         ,
    CALCGRID            ,
    CALCPAGEBREAK       ,
    CALCPAGEBREAKMANUAL,
    CALCPAGEBREAKAUTOMATIC,
    CALCDETECTIVE       ,
    CALCDETECTIVEERROR       ,
    CALCREFERENCE       ,
    CALCNOTESBACKGROUND     ,
    DRAWGRID            ,
    BASICIDENTIFIER,
    BASICCOMMENT   ,
    BASICNUMBER    ,
    BASICSTRING    ,
    BASICOPERATOR  ,
    BASICKEYWORD   ,
    BASICERROR   ,
    ColorConfigEntryCount
};


class ColorConfig_Impl;
struct ColorConfigValue
{

    sal_Bool    bIsVisible; //validity depends on the element type
    sal_Int32   nColor;
    ColorConfigValue() : bIsVisible(sal_False), nColor(0) {}
    sal_Bool operator !=(const ColorConfigValue& rCmp) const
        { return nColor != rCmp.nColor || bIsVisible != rCmp.bIsVisible;}
};


class  ColorConfig:
    public Options, public SfxBroadcaster, public SfxListener
{
    friend class ColorConfig_Impl;
private:
    static ColorConfig_Impl* m_pImpl;
public:
    ColorConfig();
    virtual ~ColorConfig();

    virtual void        Notify( SfxBroadcaster& rBC, const SfxHint& rHint );

    // get the configured value - if bSmart is set the default color setting is provided
    // instead of the automatic color
    ColorConfigValue        GetColorValue(ColorConfigEntry eEntry, sal_Bool bSmart = sal_True)const;

    static Color            GetDefaultColor(ColorConfigEntry eEntry);
};
}
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
