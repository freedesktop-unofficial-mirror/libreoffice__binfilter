/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: porexp.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 23:05:46 $
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

#ifndef _POREXP_HXX
#define _POREXP_HXX

#include "portxt.hxx"
namespace binfilter {

/*************************************************************************
 *                      class SwExpandPortion
 *************************************************************************/

class SwExpandPortion : public SwTxtPortion
{
public:
    inline  SwExpandPortion() { SetWhichPor( POR_EXP ); }
    virtual sal_Bool Format( SwTxtFormatInfo &rInf );
    virtual SwPosSize GetTxtSize( const SwTxtSizeInfo &rInfo ) const;

    // Accessibility: pass information about this portion to the PortionHandler

    OUTPUT_OPERATOR
};


/*************************************************************************
 *                      class SwBlankPortion
 *************************************************************************/

class SwBlankPortion : public SwExpandPortion
{
    xub_Unicode cChar;
    BOOL bMulti;        // For multiportion brackets
public:
    inline  SwBlankPortion( xub_Unicode cCh, BOOL bMult = sal_False )
        : cChar( cCh ), bMulti( bMult )
        { cChar = cCh; SetLen(1); SetWhichPor( POR_BLANK ); }

    BOOL IsMulti() const { return bMulti; }
    void SetMulti( BOOL bNew ) { bMulti = bNew; }

    virtual SwLinePortion *Compress();
    virtual sal_Bool GetExpTxt( const SwTxtSizeInfo &rInf, XubString &rTxt ) const;
    virtual sal_Bool Format( SwTxtFormatInfo &rInf );
    MSHORT MayUnderFlow( const SwTxtFormatInfo &rInf, xub_StrLen nIdx,
        sal_Bool bUnderFlow ) const;

    // Accessibility: pass information about this portion to the PortionHandler

    OUTPUT_OPERATOR
};

/*************************************************************************
 *                      class SwPostItsPortion
 *************************************************************************/

class SwPostItsPortion : public SwExpandPortion
{
public:
    SwPostItsPortion( sal_Bool bScrpt ){DBG_BF_ASSERT(0, "STRIP");}; //STRIP001 //STRIP001          SwPostItsPortion( sal_Bool bScrpt );
    OUTPUT_OPERATOR
};


CLASSIO( SwExpandPortion )
CLASSIO( SwBlankPortion )


} //namespace binfilter
#endif
