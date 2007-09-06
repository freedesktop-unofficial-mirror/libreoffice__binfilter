/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_wrong.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 12:40:07 $
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


#include "wrong.hxx"
namespace binfilter {

/*************************************************************************
 * sal_Bool SwWrongList::InWrongWord() gibt den Anfang und die Laenge des Wortes
 * zurueck, wenn es als falsch markiert ist.
 *************************************************************************/

/*************************************************************************
 * sal_Bool SwWrongList::Check() liefert den ersten falschen Bereich
 *************************************************************************/

/*************************************************************************
 * xub_StrLen SwWrongList::NextWrong() liefert die naechste Fehlerposition
 *************************************************************************/


/*************************************************************************
 * xub_StrLen SwWrongList::LastWrong() liefert die letzte Fehlerposition
 *************************************************************************/


/*************************************************************************
 *                 MSHORT SwWrongList::GetPos( xub_StrLen nValue )
 *  sucht die erste Position im Array, die groessergleich nValue ist,
 * dies kann natuerlich auch hinter dem letzten Element sein!
 *************************************************************************/


/*************************************************************************
 *                 void SwWrongList::Invalidate()
 *************************************************************************/

/*N*/ void SwWrongList::_Invalidate( xub_StrLen nBegin, xub_StrLen nEnd )
/*N*/ {
/*N*/   if ( nBegin < GetBeginInv() )
/*N*/       nBeginInvalid = nBegin;
/*N*/   if ( nEnd > GetEndInv() )
/*N*/       nEndInvalid = nEnd;
/*N*/ }

/*************************************************************************
 *                      SwWrongList::Move( xub_StrLen nPos, long nDiff )
 *  veraendert alle Positionen ab nPos um den angegebenen Wert,
 *  wird nach Einfuegen oder Loeschen von Buchstaben benoetigt.
 *************************************************************************/


/*************************************************************************
 *                      SwWrongList::Clear()/( xub_StrLen nBegin, xub_StrLen nEnd )
 *  loescht das Array im angegebenen Bereich
 *************************************************************************/



/*************************************************************************
 *                      SwWrongList::Fresh
 *
 * In this method the wrong list is updated, new wrong words are inserted,
 * and by evaluating the postiztion of wrong words, we also know, which
 * words are not wrong any longer and have to be removed.
 * Note: Fresh has to be called at the end of the check of the invalid region,
 * in order to find words, which are behind the last wrong word but not wrong
 * any longer
 *************************************************************************/

/*N*/ sal_Bool SwWrongList::InvalidateWrong( )
/*N*/ {
/*N*/   if( Count() )
/*N*/   {
/*N*/       xub_StrLen nFirst = WRPOS( 0 );
/*N*/       xub_StrLen nLast = WRPOS( Count() - 1 ) + WRLEN( Count() - 1 );
/*N*/       Invalidate( nFirst, nLast );
/*N*/       return sal_True;
/*N*/   }
/*N*/   else
/*N*/       return sal_False;
/*N*/ }



}
