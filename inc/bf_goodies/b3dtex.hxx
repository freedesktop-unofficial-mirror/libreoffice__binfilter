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

#ifndef _B3D_B3DTEX_HXX
#define _B3D_B3DTEX_HXX

#include <bf_svtools/bf_solar.h>


#include <tools/color.hxx>
#include <vcl/salbtype.hxx>

namespace binfilter {

/*************************************************************************
|*
|* define for lifetime of a texture in texture cache.
|* Parameter of Time(...) call, so hrs, min, sec, 100thsec.
|* Timer for cache uses ten secs delays
|*
\************************************************************************/

#define B3D_TEXTURE_LIFETIME                0, 1, 0

/*************************************************************************
|*
|* Long-Zeiger fuer OpenGL Texturdatenuebergabe
|*
\************************************************************************/

#ifdef WIN
typedef UINT8 huge* GL_UINT8;
#else
typedef UINT8*      GL_UINT8;
#endif

/*************************************************************************
|*
|* Art der Pixeldaten der Textur
|*
\************************************************************************/

enum Base3DTextureKind
{
    Base3DTextureLuminance = 1,
    Base3DTextureIntensity,
    Base3DTextureColor
};

/*************************************************************************
|*
|* Modus der Textur
|*
\************************************************************************/

enum Base3DTextureMode
{
    Base3DTextureReplace = 1,
    Base3DTextureModulate,
    Base3DTextureBlend
};

/*************************************************************************
|*
|* Filtermodus der Textur
|*
\************************************************************************/

enum Base3DTextureFilter
{
    Base3DTextureNearest = 1,
    Base3DTextureLinear
};

/*************************************************************************
|*
|* Wrapping-Modus
|*
\************************************************************************/

enum Base3DTextureWrap
{
    Base3DTextureClamp = 1,
    Base3DTextureRepeat,
    Base3DTextureSingle
};

/*************************************************************************
|*
|* Defines fuer Maskenbildung um Entscheidung innerhalb von ModifyColor
|* zu beschleunigen
|*
\************************************************************************/

#define B3D_TXT_KIND_LUM        0x00
#define B3D_TXT_KIND_INT        0x01
#define B3D_TXT_KIND_COL        0x02

#define B3D_TXT_MODE_REP        0x04
#define B3D_TXT_MODE_MOD        0x08
#define B3D_TXT_MODE_BND        0x0C

#define B3D_TXT_FLTR_NEA        0x10

/*************************************************************************
|*
|* Klassen fuer TexturAttribute beim Anfordern von Texturen
|*
\************************************************************************/

#define TEXTURE_ATTRIBUTE_TYPE_COLOR            0x0000
#define TEXTURE_ATTRIBUTE_TYPE_BITMAP           0x0001
#define TEXTURE_ATTRIBUTE_TYPE_GRADIENT         0x0002
#define TEXTURE_ATTRIBUTE_TYPE_HATCH            0x0003

}//end of namespace binfilter

#endif          // _B3D_B3DTEX_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
