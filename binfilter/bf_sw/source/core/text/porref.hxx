/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: porref.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 02:23:29 $
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
#ifndef _PORREF_HXX
#define _PORREF_HXX

#include "portxt.hxx"
namespace binfilter {

/*************************************************************************
 *                      class SwRefPortion
 *************************************************************************/

class SwRefPortion : public SwTxtPortion
{
public:
    inline  SwRefPortion(){ SetWhichPor( POR_REF ); }
//STRIP001  virtual void Paint( const SwTxtPaintInfo &rInf ) const;
    OUTPUT_OPERATOR
};

/*************************************************************************
 *                      class SwIsoRefPortion
 *************************************************************************/

class SwIsoRefPortion : public SwRefPortion
{
//STRIP001  KSHORT nViewWidth;
//STRIP001
public:
    SwIsoRefPortion(){DBG_BF_ASSERT(0, "STRIP");}; //STRIP001 //STRIP001            SwIsoRefPortion();
//STRIP001  virtual sal_Bool Format( SwTxtFormatInfo &rInf );
//STRIP001  virtual void Paint( const SwTxtPaintInfo &rInf ) const;
//STRIP001  virtual SwLinePortion *Compress();
//STRIP001  virtual KSHORT GetViewWidth( const SwTxtSizeInfo &rInf ) const;

    // Accessibility: pass information about this portion to the PortionHandler
//STRIP001     virtual void HandlePortion( SwPortionHandler& rPH ) const;

    OUTPUT_OPERATOR
};

/*************************************************************************
 *                  inline - Implementations
 *************************************************************************/

CLASSIO( SwRefPortion )
//STRIP001 CLASSIO( SwIsoRefPortion )


} //namespace binfilter
#endif
