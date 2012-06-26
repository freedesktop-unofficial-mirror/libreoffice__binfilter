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
#ifndef _PORFTN_HXX
#define _PORFTN_HXX

#include "porfld.hxx"
namespace binfilter {

class SwTxtFrm;
class SwTxtFtn;

/*************************************************************************
 *                      class SwFtnPortion
 *************************************************************************/

class SwFtnPortion : public SwFldPortion
{
    SwTxtFrm *pFrm;         // um im Dtor RemoveFtn rufen zu koennen.
    SwTxtFtn *pFtn;
    KSHORT  nOrigHeight;
public:
    SwFtnPortion( const XubString &rExpand, SwTxtFrm *pFrm, SwTxtFtn *pFtn,
                  KSHORT nOrig = KSHRT_MAX );
    inline KSHORT& Orig() { return nOrigHeight; }

    virtual void Paint( const SwTxtPaintInfo & ) const { DBG_BF_ASSERT(0, "STRIP"); }
    virtual sal_Bool GetExpTxt( const SwTxtSizeInfo &rInf, XubString &rTxt ) const;
    virtual SwPosSize GetTxtSize( const SwTxtSizeInfo& /*rInfo*/ ) const { DBG_BF_ASSERT(0, "STRIP"); return 0; }
    virtual sal_Bool Format( SwTxtFormatInfo &rInf );

    const SwTxtFtn* GetTxtFtn() const { return pFtn; };
    OUTPUT_OPERATOR
};

/*************************************************************************
 *                      class SwFtnNumPortion
 *************************************************************************/

class SwFtnNumPortion : public SwNumberPortion
{
public:
    inline SwFtnNumPortion( const XubString &rExpand, SwFont *pFnt1 )
         : SwNumberPortion( rExpand, pFnt1, sal_True, sal_False, 0 )
         { SetWhichPor( POR_FTNNUM ); }
    sal_Bool DiffFont( SwFont* pFont );
    OUTPUT_OPERATOR
};

/*************************************************************************
 *                      class SwQuoVadisPortion
 *************************************************************************/

class SwQuoVadisPortion : public SwFldPortion
{
public:
    SwQuoVadisPortion( const XubString &rExp, const XubString& ): SwFldPortion( rExp ){DBG_BF_ASSERT(0, "STRIP");} ;

    // Felder-Cloner fuer SplitGlue

    // Accessibility: pass information about this portion to the PortionHandler
    OUTPUT_OPERATOR
};

/*************************************************************************
 *                      class SwErgoSumPortion
 *************************************************************************/

class SwErgoSumPortion : public SwFldPortion
{
public:
    SwErgoSumPortion( const XubString &rExp, const XubString& ):SwFldPortion( rExp ){DBG_BF_ASSERT(0, "STRIP");} ;
    OUTPUT_OPERATOR
};

CLASSIO( SwFtnPortion )
CLASSIO( SwFtnNumPortion )
CLASSIO( SwQuoVadisPortion )
CLASSIO( SwErgoSumPortion )


} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
