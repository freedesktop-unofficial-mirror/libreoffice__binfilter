/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_portox.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 02:31:08 $
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


#pragma hdrstop

// auto strip #ifndef _SW_PORTIONHANDLER_HXX
// auto strip #include <SwPortionHandler.hxx>
// auto strip #endif
// auto strip #include "viewopt.hxx"    // SwViewOptions

// auto strip #include "txtcfg.hxx"
#include "portox.hxx"
// auto strip #include "inftxt.hxx"       // GetTxtSize()
namespace binfilter {

/*************************************************************************
 *               virtual SwToxPortion::Paint()
 *************************************************************************/

//STRIP001 void SwToxPortion::Paint( const SwTxtPaintInfo &rInf ) const
//STRIP001 {
//STRIP001  if( Width() )
//STRIP001  {
//STRIP001      rInf.DrawViewOpt( *this, POR_TOX );
//STRIP001      SwTxtPortion::Paint( rInf );
//STRIP001  }
//STRIP001 }

/*************************************************************************
 *                      class SwIsoToxPortion
 *************************************************************************/

/*N*/ SwLinePortion *SwIsoToxPortion::Compress() { return this; }
/*N*/
/*N*/ SwIsoToxPortion::SwIsoToxPortion() : nViewWidth(0)
/*N*/ {
/*N*/   SetLen(1);
/*N*/   SetWhichPor( POR_ISOTOX );
/*N*/ }

/*************************************************************************
 *               virtual SwIsoToxPortion::GetViewWidth()
 *************************************************************************/

//STRIP001 KSHORT SwIsoToxPortion::GetViewWidth( const SwTxtSizeInfo &rInf ) const
//STRIP001 {
//STRIP001  // Wir stehen zwar im const, aber nViewWidth sollte erst im letzten
//STRIP001  // Moment errechnet werden:
//STRIP001  SwIsoToxPortion* pThis = (SwIsoToxPortion*)this;
//STRIP001  // nViewWidth muss errechnet werden.
//STRIP001     if( !Width() && rInf.OnWin() &&
//STRIP001         !rInf.GetOpt().IsPagePreview() &&
//STRIP001             !rInf.GetOpt().IsReadonly() && SwViewOption::IsFieldShadings()   )
//STRIP001  {
//STRIP001      if( !nViewWidth )
//STRIP001          pThis->nViewWidth = rInf.GetTxtSize( ' ' ).Width();
//STRIP001  }
//STRIP001  else
//STRIP001      pThis->nViewWidth = 0;
//STRIP001  return nViewWidth;
//STRIP001 }

/*************************************************************************
 *                 virtual SwIsoToxPortion::Format()
 *************************************************************************/

/*N*/ sal_Bool SwIsoToxPortion::Format( SwTxtFormatInfo &rInf )
/*N*/ {
/*N*/   const sal_Bool bFull = SwLinePortion::Format( rInf );
/*N*/   return bFull;
/*N*/ }

/*************************************************************************
 *               virtual SwIsoToxPortion::Paint()
 *************************************************************************/

//STRIP001 void SwIsoToxPortion::Paint( const SwTxtPaintInfo &rInf ) const
//STRIP001 {
//STRIP001  if( Width() )
//STRIP001      rInf.DrawViewOpt( *this, POR_TOX );
//STRIP001 }

/*************************************************************************
 *              virtual SwIsoToxPortion::HandlePortion()
 *************************************************************************/

//STRIP001 void SwIsoToxPortion::HandlePortion( SwPortionHandler& rPH ) const
//STRIP001 {
//STRIP001     String aString;
//STRIP001     rPH.Special( GetLen(), aString, GetWhichPor() );
//STRIP001 }

}
