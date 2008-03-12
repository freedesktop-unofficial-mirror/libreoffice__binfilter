/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: redlnitr.hxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 10:18:37 $
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

#ifndef _REDLNITR_HXX
#define _REDLNITR_HXX

#include "ndhints.hxx"
#include "redlenum.hxx" // SwRedlineType
#include "swfont.hxx"
#ifndef _SVSTDARR_USHORTS
#define _SVSTDARR_USHORTS
#include <bf_svtools/svstdarr.hxx>
#endif
namespace binfilter {
class SfxItemSet;

class SwTxtNode;
class SwDoc;

class SwAttrHandler;

class SwExtend
{
    SwFont *pFnt;
    const SvUShorts &rArr;  // XAMA: Array of xub_StrLen
    xub_StrLen nStart;
    xub_StrLen nPos;
    xub_StrLen nEnd;
    sal_Bool _Leave( SwFont& rFnt, xub_StrLen nNew );
    sal_Bool Inside() const { return ( nPos >= nStart && nPos < nEnd ); }
    void ActualizeFont( SwFont &rFnt, xub_StrLen nAttr );
public:
    SwExtend( const SvUShorts &rA, xub_StrLen nSt ) : rArr( rA ), pFnt(0),
        nStart( nSt ), nPos( STRING_LEN ), nEnd( nStart + rA.Count() ) {}
    ~SwExtend() { delete pFnt; }
    sal_Bool IsOn() const { return pFnt != 0; }
    void Reset() { if( pFnt ) { delete pFnt; pFnt = NULL; } nPos = STRING_LEN; }
    sal_Bool Leave( SwFont& rFnt, xub_StrLen nNew )
        { if( pFnt ) return _Leave( rFnt, nNew ); return sal_False; }
    short Enter( SwFont& rFnt, xub_StrLen nNew );
    xub_StrLen Next( xub_StrLen nNext );
    SwFont* GetFont()  { return pFnt; }
    void UpdateFont( SwFont &rFnt ) { ActualizeFont( rFnt, rArr[ nPos - nStart ] ); }
};

class SwRedlineItr
{
    SwExtend *pExt;
    sal_Bool bOn;
public:
SwRedlineItr( const SwTxtNode& rTxtNd, SwFont& rFnt, SwAttrHandler& rAH,//STRIP001 SwRedlineItr( const SwTxtNode& rTxtNd, SwFont& rFnt, SwAttrHandler& rAH,
xub_StrLen nRedlPos, sal_Bool bShw, const SvUShorts *pArr = 0,//STRIP001         xub_StrLen nRedlPos, sal_Bool bShw, const SvUShorts *pArr = 0,
xub_StrLen nStart = STRING_LEN ){DBG_BF_ASSERT(0, "STRIP");} ;//STRIP001        xub_StrLen nStart = STRING_LEN );
    inline sal_Bool IsOn() const { return bOn || ( pExt && pExt->IsOn() ); }
            sal_Bool CheckLine( xub_StrLen nChkStart, xub_StrLen nChkEnd ){DBG_BF_ASSERT(0, "STRIP"); return FALSE;} //STRIP001     sal_Bool CheckLine( xub_StrLen nChkStart, xub_StrLen nChkEnd );
    inline sal_Bool ExtOn() { if( pExt ) return pExt->IsOn(); return sal_False; }
};


} //namespace binfilter
#endif

