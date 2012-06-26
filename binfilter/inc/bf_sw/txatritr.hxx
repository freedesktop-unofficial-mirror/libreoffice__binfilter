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
#ifndef _TXATRITR_HXX
#define _TXATRITR_HXX

#include <bf_svtools/bf_solar.h>
#include <sal/types.h>
#include <tools/debug.hxx>
class String;
namespace binfilter {

class SfxPoolItem;
class SwTxtNode;
class SwTxtAttr;



class SwScriptIterator
{

public:
    SwScriptIterator( const String& rStr, xub_StrLen nStart = 0,
                      sal_Bool bFrwrd = sal_True ){DBG_BF_ASSERT(0, "STRIP");};


};


class SwTxtAttrIterator
{
    const SfxPoolItem *pParaItem, *pCurItem;

public:
SwTxtAttrIterator( const SwTxtNode& rTxtNd, USHORT nWhichId,
xub_StrLen nStart = 0 ){DBG_BF_ASSERT(0, "STRIP");} ;
    const SfxPoolItem& GetAttr() const  { return *pCurItem; }
};


#ifdef ITEMID_LANGUAGE

class SwLanguageIterator : public SwTxtAttrIterator
{
public:
    SwLanguageIterator( const SwTxtNode& rTxtNd, xub_StrLen nStart = 0 )
        : SwTxtAttrIterator( rTxtNd, RES_CHRATR_LANGUAGE, nStart )
    {}

    sal_uInt16 GetLanguage() const
        { return ((SvxLanguageItem&)GetAttr()).GetValue(); }
};

#endif


} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
