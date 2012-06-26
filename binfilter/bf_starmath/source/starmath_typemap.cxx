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

#define ITEMID_PTR              0
#define ITEMID_SHADOW           0
#define ITEMID_PAGE             0
#define ITEMID_SETITEM          0
#define ITEMID_HORJUSTIFY       0
#define ITEMID_VERJUSTIFY       0
#define ITEMID_ORIENTATION      0
#define ITEMID_MARGIN           0
#define ITEMID_AUTHOR           0
#define ITEMID_DATE             0
#define ITEMID_TEXT             0
#define ITEMID_SPELLCHECK       0
#define ITEMID_HYPHENREGION     0
#define ITEMID_FONT             0
#define ITEMID_FONTHEIGHT       0
#define ITEMID_COLOR            0
#define ITEMID_BRUSH            0
#define ITEMID_BRUSH            0
#define ITEMID_BOX              0
#define ITEMID_LINE             0
#define ITEMID_BRUSH            0
#define ITEMID_SPELLCHECK       0
#define ITEMID_HYPHENREGION     0
#define ITEMID_LINESPACING      0
#define ITEMID_ADJUST           0
#define ITEMID_WIDOWS           0
#define ITEMID_ORPHANS          0
#define ITEMID_HYPHENZONE       0
#define ITEMID_TABSTOP          0
#define ITEMID_FMTSPLIT         0
#define ITEMID_PAGEMODEL        0
#define ITEMID_FONTLIST         0
#define ITEMID_FONT             0
#define ITEMID_POSTURE          0
#define ITEMID_WEIGHT           0
#define ITEMID_FONTHEIGHT       0
#define ITEMID_FONTWIDTH        0
#define ITEMID_UNDERLINE        0
#define ITEMID_CROSSEDOUT       0
#define ITEMID_SHADOWED         0
#define ITEMID_AUTOKERN         0
#define ITEMID_WORDLINEMODE     0
#define ITEMID_CONTOUR          0
#define ITEMID_PROPSIZE         0
#define ITEMID_COLOR            0
#define ITEMID_CHARSETCOLOR     0
#define ITEMID_KERNING          0
#define ITEMID_CASEMAP          0
#define ITEMID_ESCAPEMENT       0
#define ITEMID_LANGUAGE         0
#define ITEMID_NOLINEBREAK      0
#define ITEMID_NOHYPHENHERE     0
#define ITEMID_COLOR            0
#define ITEMID_FONT             0
#define ITEMID_FONTHEIGHT       0
#define ITEMID_SEARCH           0
#define ITEMID_COLOR_TABLE      0
#define ITEMID_GRADIENT_LIST    0
#define ITEMID_HATCH_LIST       0
#define ITEMID_BITMAP_LIST      0
#define ITEMID_DASH_LIST        0
#define ITEMID_LINEEND_LIST     0
#define ITEMID_NUMBERINFO       0
#define ITEMID_CHARTSTYLE       0
#define ITEMID_CHARTDATADESCR   0
#define ITEMID_CHARTLEGENDPOS   0
#define ITEMID_CHARTTEXTORDER   0
#define ITEMID_CHARTTEXTORIENT  0
#define ITEMID_DOUBLE           0
#define ITEMID_TABSTOP          0
#define ITEMID_PAPERBIN         0
#define ITEMID_SIZE             0
#define ITEMID_LRSPACE          0
#define ITEMID_ULSPACE          0
#define ITEMID_PRINT            0
#define ITEMID_OPAQUE           0
#define ITEMID_PROTECT          0
#define ITEMID_MACRO            0
#define ITEMID_BOX              0
#define ITEMID_BOXINFO          0
#define ITEMID_FMTBREAK         0
#define ITEMID_FMTKEEP          0
#define ITEMID_LINE             0
#define ITEMID_BRUSH            0

#define CharSetItem SfxVoidItem
#define FontFamilyItem SfxVoidItem
#define FontPitchItem SfxVoidItem
#define FontAlignItem SfxVoidItem
#define FontWeightItem SfxVoidItem
#define FontUnderlineItem SfxVoidItem
#define FontStrikeoutItem SfxVoidItem
#define FontItalicItem SfxVoidItem
#define SvxDbTypeItem SfxVoidItem
#define SvxLineSpaceItem SfxVoidItem
#define SvxInterLineSpaceItem SfxVoidItem
#define SvxBreakItem SfxVoidItem
#define BrushStyleItem SfxVoidItem
#define SvxNumTypeItem SfxVoidItem
#define SvxShadowLocationItem SfxVoidItem
#define SvxLanguage SfxVoidItem
#define SvxChooseControlEnumItem SfxVoidItem
#define SvxDrawToolEnumItem SfxVoidItem
#define SvxChooseControlItem SfxVoidItem
#define SvxDrawToolItem SfxVoidItem
#define SvxCellHorJustifyEnumItem SfxVoidItem
#define SvxCellVerJustifyEnumItem SfxVoidItem
#define SvxCellOrientationEnumItem SfxVoidItem

#include <bf_sfx2/msg.hxx>
#include <bf_svtools/stritem.hxx>
#include <bf_svtools/eitem.hxx>
#include <bf_svx/zoomitem.hxx>
#include <bf_svtools/slstitm.hxx>

#define SFX_TYPEMAP
namespace binfilter {
#include "smslots.hxx"
} //namespace binfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
