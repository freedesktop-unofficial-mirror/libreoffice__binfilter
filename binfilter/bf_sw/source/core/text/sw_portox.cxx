/*************************************************************************
 *
 *  $RCSfile: sw_portox.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:51:23 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/


#pragma hdrstop

#ifndef _SW_PORTIONHANDLER_HXX
#include <SwPortionHandler.hxx>
#endif
#include "viewopt.hxx"  // SwViewOptions

#include "txtcfg.hxx"
#include "portox.hxx"
#include "inftxt.hxx"       // GetTxtSize()
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
