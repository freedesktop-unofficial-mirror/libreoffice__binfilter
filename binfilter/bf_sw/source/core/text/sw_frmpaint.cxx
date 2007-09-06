/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_frmpaint.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 12:32:37 $
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


#ifdef _MSC_VER
#pragma hdrstop
#endif

#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif



#ifndef _PAGEDESC_HXX
#include <pagedesc.hxx> // SwPageDesc
#endif

#ifndef _ITRPAINT_HXX
#include <itrpaint.hxx>     // SwTxtPainter
#endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

namespace binfilter {


// steht im number.cxx
extern const sal_Char __FAR_DATA sBulletFntName[];

extern FASTBOOL bOneBeepOnly;

sal_Bool bInitFont = sal_True;

#define REDLINE_DISTANCE 567/4
#define REDLINE_MINDIST  567/10


/*************************************************************************
 * SwExtraPainter::PaintExtra()
 **************************************************************************/




/*************************************************************************
 *                      SwTxtFrm::Paint()
 *************************************************************************/

/*N*/ SwRect SwTxtFrm::Paint()
/*N*/ {
/*N*/ #if OSL_DEBUG_LEVEL > 1
/*N*/   const SwTwips nDbgY = Frm().Top();
/*N*/ #endif
/*N*/
/*N*/   // finger layout
/*N*/   ASSERT( GetValidPosFlag(), "+SwTxtFrm::Paint: no Calc()" );
/*N*/
/*N*/   SwRect aRet( Prt() );
/*N*/   if ( IsEmpty() || !HasPara() )
/*N*/       aRet += Frm().Pos();
/*N*/   else
/*N*/   {
/*N*/       // AMA: Wir liefern jetzt mal das richtige Repaintrechteck zurueck,
/*N*/       //      d.h. als linken Rand den berechneten PaintOfst!
/*N*/       SwRepaint *pRepaint = GetPara()->GetRepaint();
/*N*/       long l;
/*N*/       if( pRepaint->GetOfst() )
/*N*/           pRepaint->Left( pRepaint->GetOfst() );
/*N*/
/*N*/       l = pRepaint->GetRightOfst();
/*N*/       if( l && ( pRepaint->GetOfst() || l > pRepaint->Right() ) )
/*N*/            pRepaint->Right( l );
/*N*/       pRepaint->SetOfst( 0 );
/*N*/       aRet = *pRepaint;
/*N*/
/*N*/ #ifdef BIDI
/*N*/         if ( IsRightToLeft() )
                {DBG_BF_ASSERT(0, "STRIP");} //STRIP001 /*?*/             SwitchLTRtoRTL( aRet );
/*N*/ #endif
/*N*/         if ( IsVertical() )
/*N*/             SwitchHorizontalToVertical( aRet );
/*N*/   }
/*N*/   ResetRepaint();
/*N*/
/*N*/     return aRet;
/*N*/ }

/*************************************************************************
 *                      SwTxtFrm::Paint()
 *************************************************************************/


/*************************************************************************
 *                      SwTxtFrm::Paint()
 *************************************************************************/


}
