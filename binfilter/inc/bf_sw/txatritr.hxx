/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: txatritr.hxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 04:59:18 $
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
#include <tools/debug.hxx>
class String;
class SfxPoolItem;
namespace binfilter {

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
SwTxtAttrIterator( const SwTxtNode& rTxtNd, USHORT nWhichId,//STRIP001  SwTxtAttrIterator( const SwTxtNode& rTxtNd, USHORT nWhichId,
xub_StrLen nStart = 0 ){DBG_BF_ASSERT(0, "STRIP");} ;//STRIP001                         xub_StrLen nStart = 0 );
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
