/*************************************************************************
 *
 *  $RCSfile: sw_wrong.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 17:58:05 $
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

// auto strip #ifndef _STRING_HXX //autogen
// auto strip #include <tools/string.hxx>
// auto strip #endif
// auto strip #include "errhdl.hxx"
// auto strip #include "swtypes.hxx"
// auto strip #include "txttypes.hxx"

#include "wrong.hxx"
namespace binfilter {

/*************************************************************************
 * sal_Bool SwWrongList::InWrongWord() gibt den Anfang und die Laenge des Wortes
 * zurueck, wenn es als falsch markiert ist.
 *************************************************************************/
//STRIP001 sal_Bool SwWrongList::InWrongWord( xub_StrLen &rChk, xub_StrLen &rLn ) const
//STRIP001 {
//STRIP001  MSHORT nPos = GetPos( rChk );
//STRIP001  xub_StrLen nWrPos;
//STRIP001  if( nPos < Count() && ( nWrPos = WRPOS( nPos ) ) <= rChk )
//STRIP001  {
//STRIP001      rLn = WRLEN( nPos );
//STRIP001      if( nWrPos + rLn <= rChk )
//STRIP001          return sal_False;
//STRIP001      rChk = nWrPos;
//STRIP001      return sal_True;
//STRIP001  }
//STRIP001  return sal_False;
//STRIP001 }

/*************************************************************************
 * sal_Bool SwWrongList::Check() liefert den ersten falschen Bereich
 *************************************************************************/
//STRIP001 sal_Bool SwWrongList::Check( xub_StrLen &rChk, xub_StrLen &rLn ) const
//STRIP001 {
//STRIP001  MSHORT nPos = GetPos( rChk );
//STRIP001  rLn += rChk;
//STRIP001  xub_StrLen nWrPos;
//STRIP001
//STRIP001  if( nPos == Count() )
//STRIP001      return sal_False;
//STRIP001
//STRIP001  xub_StrLen nEnd = WRLEN( nPos );
//STRIP001  nEnd += ( nWrPos = WRPOS( nPos ) );
//STRIP001  if( nEnd == rChk )
//STRIP001  {
//STRIP001      ++nPos;
//STRIP001      if( nPos == Count() )
//STRIP001          return sal_False;
//STRIP001      else
//STRIP001      {
//STRIP001          nEnd = WRLEN( nPos );
//STRIP001          nEnd += ( nWrPos = WRPOS( nPos ) );
//STRIP001      }
//STRIP001  }
//STRIP001  if( nEnd > rChk && nWrPos < rLn )
//STRIP001  {
//STRIP001      if( nWrPos > rChk )
//STRIP001          rChk = nWrPos;
//STRIP001      if( nEnd < rLn )
//STRIP001          rLn = nEnd;
//STRIP001      rLn -= rChk;
//STRIP001      return 0 != rLn;
//STRIP001  }
//STRIP001  return sal_False;
//STRIP001 }

/*************************************************************************
 * xub_StrLen SwWrongList::NextWrong() liefert die naechste Fehlerposition
 *************************************************************************/

//STRIP001 xub_StrLen SwWrongList::NextWrong( xub_StrLen nChk ) const
//STRIP001 {
//STRIP001  xub_StrLen nRet;
//STRIP001  xub_StrLen nPos = GetPos( nChk );
//STRIP001  if( nPos < Count() )
//STRIP001  {
//STRIP001      nRet = WRPOS( nPos );
//STRIP001      if( nRet < nChk && nRet + WRLEN( nPos ) <= nChk )
//STRIP001      {
//STRIP001          if( ++nPos < Count() )
//STRIP001              nRet = WRPOS( nPos );
//STRIP001          else
//STRIP001              nRet = STRING_LEN;
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001      nRet = STRING_LEN;
//STRIP001  if( nRet > GetBeginInv() && nChk < GetEndInv() )
//STRIP001      nRet = nChk > GetBeginInv() ? nChk : GetBeginInv();
//STRIP001  return nRet;
//STRIP001 }

/*************************************************************************
 * xub_StrLen SwWrongList::LastWrong() liefert die letzte Fehlerposition
 *************************************************************************/

//STRIP001 xub_StrLen SwWrongList::LastWrong( xub_StrLen nChk ) const
//STRIP001 {
//STRIP001  xub_StrLen nPos = GetPos( nChk );
//STRIP001  xub_StrLen nRet;
//STRIP001  if( nPos >= Count() || ( nRet = WRPOS( nPos ) ) >= nChk )
//STRIP001      nRet = nPos ? WRPOS( --nPos ) : STRING_LEN;
//STRIP001  if( nChk > GetBeginInv() && ( nRet == STRING_LEN || nRet < GetEndInv() ) )
//STRIP001      nRet = nChk > GetEndInv() ? GetEndInv() : nChk;
//STRIP001  else if( nRet < STRING_LEN )
//STRIP001      nRet += WRLEN( nPos );
//STRIP001  return nRet;
//STRIP001 }

/*************************************************************************
 *                 MSHORT SwWrongList::GetPos( xub_StrLen nValue )
 *  sucht die erste Position im Array, die groessergleich nValue ist,
 * dies kann natuerlich auch hinter dem letzten Element sein!
 *************************************************************************/

//STRIP001 MSHORT SwWrongList::GetPos( xub_StrLen nValue ) const
//STRIP001 {
//STRIP001  register MSHORT nOben = Count(), nMitte, nUnten = 0;
//STRIP001  if( nOben > 0 )
//STRIP001  {
//STRIP001      --nOben;
//STRIP001      while( nUnten <= nOben )
//STRIP001      {
//STRIP001          nMitte = nUnten + ( nOben - nUnten ) / 2;
//STRIP001          xub_StrLen nTmp = WRPOS( nMitte );
//STRIP001          if( nTmp == nValue )
//STRIP001              return nMitte;
//STRIP001          else if( nTmp < nValue )
//STRIP001          {
//STRIP001              if( nTmp + WRLEN( nMitte ) >= nValue )
//STRIP001                  return nMitte;
//STRIP001              nUnten = nMitte + 1;
//STRIP001          }
//STRIP001          else if( nMitte == 0 )
//STRIP001              return nUnten;
//STRIP001          else
//STRIP001              nOben = nMitte - 1;
//STRIP001      }
//STRIP001  }
//STRIP001  return nUnten;
//STRIP001 }

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

//STRIP001 void SwWrongList::Move( xub_StrLen nPos, long nDiff )
//STRIP001 {
//STRIP001  MSHORT i = GetPos( nPos );
//STRIP001  if( nDiff < 0 )
//STRIP001  {
//STRIP001      xub_StrLen nEnd = nPos + xub_StrLen( -nDiff );
//STRIP001      MSHORT nLst = i;
//STRIP001      xub_StrLen nWrPos;
//STRIP001      xub_StrLen nWrLen;
//STRIP001      sal_Bool bJump = sal_False;
//STRIP001      while( nLst < Count() && WRPOS( nLst ) < nEnd )
//STRIP001          ++nLst;
//STRIP001         if( nLst > i && ( nWrPos = WRPOS( nLst - 1 ) ) <= nPos )
//STRIP001      {
//STRIP001             nWrLen = WRLEN( nLst - 1 );
//STRIP001             // calculate new length of word
//STRIP001             nWrLen = ( nEnd > nWrPos + nWrLen ) ?
//STRIP001                        nPos - nWrPos :
//STRIP001                        nWrLen + nDiff;
//STRIP001          if( nWrLen )
//STRIP001          {
//STRIP001                 aLen.GetObject( --nLst ) = nWrLen;
//STRIP001              bJump = sal_True;
//STRIP001          }
//STRIP001      }
//STRIP001      Remove( i, nLst - i );
//STRIP001      aLen.Remove( i, nLst - i );
//STRIP001      if ( bJump )
//STRIP001          ++i;
//STRIP001      if( STRING_LEN == GetBeginInv() )
//STRIP001             SetInvalid( nPos ? nPos - 1 : nPos, nPos + 1 );
//STRIP001      else
//STRIP001      {
//STRIP001          ShiftLeft( nBeginInvalid, nPos, nEnd );
//STRIP001          ShiftLeft( nEndInvalid, nPos, nEnd );
//STRIP001             _Invalidate( nPos ? nPos - 1 : nPos, nPos + 1 );
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      xub_StrLen nWrPos;
//STRIP001      xub_StrLen nEnd = nPos + xub_StrLen( nDiff );
//STRIP001      if( STRING_LEN != GetBeginInv() )
//STRIP001      {
//STRIP001          if( nBeginInvalid > nPos )
//STRIP001              nBeginInvalid += xub_StrLen( nDiff );
//STRIP001          if( nEndInvalid >= nPos )
//STRIP001              nEndInvalid += xub_StrLen( nDiff );
//STRIP001      }
//STRIP001      // Wenn wir mitten in einem falschen Wort stehen, muss vom Wortanfang
//STRIP001      // invalidiert werden.
//STRIP001      if( i < Count() && nPos >= ( nWrPos = WRPOS( i ) ) )
//STRIP001      {
//STRIP001          Invalidate( nWrPos, nEnd );
//STRIP001          xub_StrLen nWrLen = WRLEN( i ) + xub_StrLen( nDiff );
//STRIP001          aLen.GetObject( i++ ) = nWrLen;
//STRIP001             nWrLen += nWrPos;
//STRIP001             Invalidate( nWrPos, nWrLen );
//STRIP001      }
//STRIP001      else
//STRIP001          Invalidate( nPos, nEnd );
//STRIP001  }
//STRIP001  while( i < Count() )
//STRIP001  {
//STRIP001      xub_StrLen nTmp = nDiff + GetObject( i );
//STRIP001      GetObject( i++ ) = nTmp;
//STRIP001  }
//STRIP001 }

/*************************************************************************
 *                      SwWrongList::Clear()/( xub_StrLen nBegin, xub_StrLen nEnd )
 *  loescht das Array im angegebenen Bereich
 *************************************************************************/

//STRIP001 void SwWrongList::Clear()
//STRIP001 {
//STRIP001  Remove( 0, Count() );
//STRIP001  aLen.Remove( 0, aLen.Count() );
//STRIP001 }

//STRIP001 void SwWrongList::Clear( xub_StrLen nBegin, xub_StrLen nEnd )
//STRIP001 {
//STRIP001  MSHORT nFirst = 0;
//STRIP001  while( nFirst < Count() && WRPOS( nFirst ) < nBegin )
//STRIP001      ++nFirst;
//STRIP001  MSHORT i = nFirst;
//STRIP001  while( i < Count() && WRPOS( i++ ) <= nEnd )
//STRIP001      ;
//STRIP001  Remove( nFirst, i - nFirst );
//STRIP001  aLen.Remove( nFirst, i - nFirst );
//STRIP001 }

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
//STRIP001 sal_Bool SwWrongList::Fresh( xub_StrLen &rStart, xub_StrLen &rEnd, xub_StrLen nPos,
//STRIP001                       xub_StrLen nLen, MSHORT nIndex, xub_StrLen nCursorPos )
//STRIP001 {
//STRIP001     sal_Bool bRet = nLen && ( nCursorPos > nPos + nLen || nCursorPos < nPos );
//STRIP001  xub_StrLen nWrPos;
//STRIP001  xub_StrLen nWrEnd = rEnd;
//STRIP001  MSHORT nCnt = nIndex;
//STRIP001  if( nIndex < Count() && ( nWrPos = WRPOS( nIndex ) ) < nPos )
//STRIP001  {
//STRIP001      nWrEnd = nWrPos + WRLEN( nCnt++ );
//STRIP001      if( rStart > nWrPos )
//STRIP001          rStart = nWrPos;
//STRIP001  }
//STRIP001  while( nCnt < Count() && ( nWrPos = WRPOS( nCnt ) ) < nPos )
//STRIP001      nWrEnd = nWrPos + WRLEN( nCnt++ );
//STRIP001  if( nCnt < Count() && nWrPos == nPos && WRLEN( nCnt ) == nLen )
//STRIP001  {
//STRIP001      ++nCnt;
//STRIP001      bRet = sal_True;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if( bRet )
//STRIP001      {
//STRIP001          if( rStart > nPos )
//STRIP001              rStart = nPos;
//STRIP001          nWrEnd = nPos + nLen;
//STRIP001      }
//STRIP001  }
//STRIP001  nPos += nLen;
//STRIP001  if( nCnt < Count() && ( nWrPos = WRPOS( nCnt ) ) < nPos )
//STRIP001  {
//STRIP001      nWrEnd = nWrPos + WRLEN( nCnt++ );
//STRIP001      if( rStart > nWrPos )
//STRIP001          rStart = nWrPos;
//STRIP001  }
//STRIP001  while( nCnt < Count() && ( nWrPos = WRPOS( nCnt ) ) < nPos )
//STRIP001      nWrEnd = nWrPos + WRLEN( nCnt++ );
//STRIP001  if( rEnd < nWrEnd )
//STRIP001      rEnd = nWrEnd;
//STRIP001  Remove( nIndex, nCnt - nIndex );
//STRIP001  aLen.Remove( nIndex, nCnt - nIndex );
//STRIP001  return bRet;
//STRIP001 }

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

//STRIP001 SwWrongList* SwWrongList::SplitList( xub_StrLen nSplitPos )
//STRIP001 {
//STRIP001     SwWrongList *pRet = NULL;
//STRIP001     MSHORT nLst = 0;
//STRIP001     xub_StrLen nWrPos;
//STRIP001     xub_StrLen nWrLen;
//STRIP001     while( nLst < Count() && WRPOS( nLst ) < nSplitPos )
//STRIP001         ++nLst;
//STRIP001     if( nLst && ( nWrPos = WRPOS( nLst - 1 ) )
//STRIP001         + ( nWrLen = WRLEN( nLst - 1 ) ) > nSplitPos )
//STRIP001     {
//STRIP001         nWrLen += nWrPos - nSplitPos;
//STRIP001         GetObject( --nLst ) = nSplitPos;
//STRIP001         aLen.GetObject( nLst ) = nWrLen;
//STRIP001     }
//STRIP001     if( nLst )
//STRIP001     {
//STRIP001         pRet = new SwWrongList;
//STRIP001         pRet->SvXub_StrLens::Insert( this, 0, 0, nLst );
//STRIP001         pRet->aLen.Insert( &aLen, 0, 0, nLst );
//STRIP001         pRet->SetInvalid( GetBeginInv(), GetEndInv() );
//STRIP001         pRet->_Invalidate( nSplitPos ? nSplitPos - 1 : nSplitPos, nSplitPos );
//STRIP001         Remove( 0, nLst );
//STRIP001         aLen.Remove( 0, nLst );
//STRIP001     }
//STRIP001     if( STRING_LEN == GetBeginInv() )
//STRIP001         SetInvalid( 0, 1 );
//STRIP001     else
//STRIP001     {
//STRIP001         ShiftLeft( nBeginInvalid, 0, nSplitPos );
//STRIP001         ShiftLeft( nEndInvalid, 0, nSplitPos );
//STRIP001         _Invalidate( 0, 1 );
//STRIP001  }
//STRIP001     nLst = 0;
//STRIP001     while( nLst < Count() )
//STRIP001  {
//STRIP001         nWrPos = GetObject( nLst ) - nSplitPos;
//STRIP001         GetObject( nLst++ ) = nWrPos;
//STRIP001     }
//STRIP001     return pRet;
//STRIP001 }

//STRIP001 void SwWrongList::JoinList( SwWrongList* pNext, xub_StrLen nInsertPos )
//STRIP001 {
//STRIP001     if( pNext )
//STRIP001     {
//STRIP001         USHORT nCnt = Count();
//STRIP001         pNext->Move( 0, nInsertPos );
//STRIP001         SvXub_StrLens::Insert( pNext, nCnt, 0, pNext->Count() );
//STRIP001         aLen.Insert( &pNext->aLen, nCnt, 0, pNext->Count() );
//STRIP001         Invalidate( pNext->GetBeginInv(), pNext->GetEndInv() );
//STRIP001         if( nCnt && Count() > nCnt )
//STRIP001         {
//STRIP001             xub_StrLen nWrPos = WRPOS( nCnt );
//STRIP001             xub_StrLen nWrLen = WRLEN( nCnt );
//STRIP001             if( !nWrPos )
//STRIP001             {
//STRIP001                 nWrPos += nInsertPos;
//STRIP001                 nWrLen -= nInsertPos;
//STRIP001                 GetObject( nCnt ) = nWrPos;
//STRIP001                 aLen.GetObject( nCnt ) = nWrLen;
//STRIP001             }
//STRIP001             if( nWrPos == WRPOS( nCnt - 1 ) + WRLEN( nCnt - 1 ) )
//STRIP001             {
//STRIP001                 nWrLen += WRLEN( nCnt - 1 );
//STRIP001                 aLen.GetObject( nCnt - 1 ) = nWrLen;
//STRIP001                 Remove( nCnt, 1 );
//STRIP001                 aLen.Remove( nCnt, 1 );
//STRIP001             }
//STRIP001         }
//STRIP001     }
//STRIP001     Invalidate( nInsertPos ? nInsertPos - 1 : nInsertPos, nInsertPos + 1 );
//STRIP001 }

}
