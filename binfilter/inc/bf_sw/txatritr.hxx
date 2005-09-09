/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: txatritr.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 16:39:34 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/
#ifndef _TXATRITR_HXX
#define _TXATRITR_HXX

#ifndef _SOLAR_H
#include <tools/solar.h>
#endif
#ifndef _SAL_TYPES_H_
#include <sal/types.h>
#endif
// auto strip #ifndef _SVARRAY_HXX
// auto strip #include <svtools/svarray.hxx>
// auto strip #endif
#include <tools/debug.hxx>
class String;
class SfxPoolItem;
namespace binfilter {

class SwTxtNode;
class SwTxtAttr;



class SwScriptIterator
{
//STRIP001  const String& rText;
//STRIP001  xub_StrLen nChgPos;
//STRIP001  sal_uInt16 nCurScript;
//STRIP001     sal_Bool bForward;

public:
    SwScriptIterator( const String& rStr, xub_StrLen nStart = 0,
                      sal_Bool bFrwrd = sal_True ){DBG_BF_ASSERT(0, "STRIP");};

//STRIP001  sal_Bool Next();

//STRIP001  sal_uInt16 GetCurrScript() const        { return nCurScript; }
//STRIP001  xub_StrLen GetScriptChgPos() const      { return nChgPos; }
//STRIP001  const String& GetText() const           { return rText; }
};


class SwTxtAttrIterator
{
//STRIP001  SwScriptIterator aSIter;
//STRIP001  SvPtrarr aStack;
//STRIP001  const SwTxtNode& rTxtNd;
    const SfxPoolItem *pParaItem, *pCurItem;
//STRIP001  xub_StrLen nChgPos;
//STRIP001  sal_uInt16 nAttrPos, nWhichId;
//STRIP001
//STRIP001  void AddToStack( const SwTxtAttr& rAttr );
//STRIP001  void SearchNextChg();

public:
SwTxtAttrIterator( const SwTxtNode& rTxtNd, USHORT nWhichId,//STRIP001  SwTxtAttrIterator( const SwTxtNode& rTxtNd, USHORT nWhichId,
xub_StrLen nStart = 0 ){DBG_BF_ASSERT(0, "STRIP");} ;//STRIP001                         xub_StrLen nStart = 0 );
//STRIP001
//STRIP001  sal_Bool Next();
//STRIP001
    const SfxPoolItem& GetAttr() const  { return *pCurItem; }
//STRIP001  xub_StrLen GetChgPos() const        { return nChgPos; }
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
