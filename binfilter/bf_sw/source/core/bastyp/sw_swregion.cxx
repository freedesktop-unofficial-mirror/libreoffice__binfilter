/*************************************************************************
 *
 *  $RCSfile: sw_swregion.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 16:58:22 $
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


#ifndef _DEBUG_HXX //autogen
#include <tools/debug.hxx>
#endif
// auto strip #include "swtypes.hxx"
// auto strip #include "swrect.hxx"
#include "swregion.hxx"
namespace binfilter {


/*N*/ SV_IMPL_VARARR( SwRects, SwRect );

/*************************************************************************
|*
|*  SwRegionRects::SwRegionRects()
|*
|*  Ersterstellung      MA 28. Oct. 92
|*  Letzte Aenderung    MA 01. Feb. 93
|*
|*************************************************************************/

/*N*/ SwRegionRects::SwRegionRects( const SwRect &rStartRect, USHORT nInit,
/*N*/                                                       USHORT nGrow ) :
/*N*/   SwRects( (BYTE)nInit, (BYTE)nGrow ),
/*N*/   aOrigin( rStartRect )
/*N*/ {
/*N*/   Insert( aOrigin, 0 );
/*N*/ }

/*************************************************************************
 *                      inline InsertRect()
 *
 * InsertRect() wird nur von operator-=() gerufen.
 * Wenn bDel == TRUE ist, dann wird das Rect an der Position nPos mit
 * rRect ueberschrieben, ansonsten wird rRect hinten angehaengt.
 *************************************************************************/

/*N*/  inline void SwRegionRects::InsertRect( const SwRect &rRect, const USHORT nPos,
/*N*/                                      FASTBOOL &rDel )
/*N*/  {
/*N*/   if( rDel )
/*N*/   {
/*N*/       *(pData+nPos) = rRect;
/*N*/       rDel = FALSE;
/*N*/   }
/*N*/   else
/*N*/       Insert( rRect, Count() );
/*N*/  }

/*************************************************************************
|*
|*  SwRegionRects::operator-=()
|*
|*  Beschreibung        Alle Ueberschneidungen der Rechtecke, die sich
|*      gerade im Array befinden, mit dem uebergebenen Rechteck werden
|*      entfernt.
|*      Dazu muessen die vorhandenen Rechtecke entweder aufgeteilt oder
|*      geloescht werden.
|*  Ersterstellung      MA 28. Oct. 92
|*  Letzte Aenderung    MA 09. Sep. 93
|*
|*************************************************************************/

/*N*/ void SwRegionRects::operator-=( const SwRect &rRect )
/*N*/ {
/*N*/   USHORT nMax = Count();
/*N*/   for ( USHORT i = 0; i < nMax; ++i )
/*N*/   {
/*N*/       if ( rRect.IsOver( *(pData+i) ) )
/*N*/       {
/*N*/           SwRect aTmp( *(pData+i) );
/*N*/           SwRect aInter( aTmp );
/*N*/           aInter._Intersection( rRect );
/*N*/
/*N*/           // Das erste Rect, das wir inserten wollen, nimmt die
/*N*/           // Stelle von i ein. So ersparen wir uns das Delete().
/*N*/           FASTBOOL bDel = TRUE;
/*N*/
/*N*/           //Jetzt aufteilen das Teil: Es sollen diejenigen Rechtecke
/*N*/           //zurueckbleiben, die im alten aber nicht im neuen liegen.
/*N*/           //Sprich alle Rechtecke die im alten aber nicht in der Intersection
/*N*/           //liegen.
/*N*/           long nTmp;
/*N*/           if ( 0 < (nTmp = aInter.Top() - aTmp.Top()) )
/*N*/           {
/*N*/               const long nOldVal = aTmp.Height();
/*N*/               aTmp.SSize().Height() = nTmp;
/*N*/               InsertRect( aTmp, i, bDel );
/*N*/               aTmp.Height( nOldVal );
/*N*/           }
/*N*/
/*N*/           aTmp.Top( aInter.Top() + aInter.Height() );
/*N*/           if ( aTmp.Height() > 0 )
/*N*/               InsertRect( aTmp, i, bDel );
/*N*/
/*N*/           aTmp.Top( aInter.Top() );
/*N*/           aTmp.Bottom( aInter.Bottom() );
/*N*/           if ( 0 < (nTmp = aInter.Left() - aTmp.Left()) )
/*N*/           {
/*N*/               const long nOldVal = aTmp.Width();
/*N*/               aTmp.Width( nTmp );
/*N*/               InsertRect( aTmp, i, bDel );
/*N*/               aTmp.Width( nOldVal );
/*N*/           }
/*N*/
/*N*/           aTmp.Left( aInter.Left() + aInter.Width() ); //+1?
/*N*/           if ( aTmp.Width() > 0 )
/*N*/               InsertRect( aTmp, i, bDel );
/*N*/
/*N*/           if( bDel )
/*N*/           {
/*N*/               Remove( i );
/*N*/               --i;              //Damit wir keinen uebergehen.
/*N*/               --nMax;           //Damit wir keinen zuviel verarbeiten.
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/ }

/*************************************************************************
 *                      SwRegionRects::Invert()
 *
 * Bezugspunkt ist aOrigin, das Original-SRectangle.
 * Aus Loechern werden Flaechen, aus Flaechen werden Loecher.
 * Ein Hinweis: Wenn keine Rects abgezogen wurden, so ist das enthaltene
 * Rechteck identisch mit aOrigin. Nach Invert() besteht die Region aus
 * einem Null-SRectangle.
 *************************************************************************/

//STRIP001 void SwRegionRects::Invert()
//STRIP001 {
//STRIP001  // Nicht besonders elegant und schnell, aber wirkungsvoll:
//STRIP001  // Wir legen eine weitere Region an und ziehen alle Flaechen ab,
//STRIP001  // die in uns noch uebrig geblieben sind. Danach werden alle
//STRIP001  // Werte uebertragen.
//STRIP001
//STRIP001  // Um unuetze Speicheranforderungen zu vermeiden versuchen wir die
//STRIP001  // iniale Groesse moeglichst brauchbar anzulegen:
//STRIP001  // Anzahl der Rechtecke in der Region * 2 + 2
//STRIP001  // plus zwei um den Sonderfall eines einzelnen Loches (macht vier
//STRIP001  // Rechtecke im inversen Fall) abzudecken.
//STRIP001
//STRIP001  SwRegionRects aInvRegion( aOrigin, Count()*2+2 );
//STRIP001  const SwRect *pDat = GetData();
//STRIP001  for( USHORT i = 0; i < Count(); ++pDat, ++i )
//STRIP001      aInvRegion -= *pDat;
//STRIP001
//STRIP001  USHORT nCpy = Count(), nDel = 0;
//STRIP001  if( aInvRegion.Count() < Count() )
//STRIP001  {
//STRIP001      nDel = Count() - aInvRegion.Count();
//STRIP001      nCpy = aInvRegion.Count();
//STRIP001  }
//STRIP001  // alle vorhandenen ueberschreiben
//STRIP001  memcpy( pData, aInvRegion.GetData(), nCpy * sizeof( SwRect ));
//STRIP001
//STRIP001  if( nCpy < aInvRegion.Count() )
//STRIP001      Insert( &aInvRegion, nCpy, nCpy );
//STRIP001  else if( nDel )
//STRIP001      Remove( nCpy, nDel );
//STRIP001 }
/*************************************************************************
|*
|*  SwRegionRects::Compress()
|*
|*  Beschreibung        Zusammenfassen von benachbarten Rechtecken.
|*  Ersterstellung      MA 16. Apr. 93
|*  Letzte Aenderung    MA 21. Apr. 93
|*
|*************************************************************************/
//STRIP001 inline SwTwips CalcArea( const SwRect &rRect )
//STRIP001 {
//STRIP001  return rRect.Width() * rRect.Height();
//STRIP001 }


#pragma optimize("e",off)
//STRIP001 void SwRegionRects::Compress( BOOL bFuzzy )
//STRIP001 {
//STRIP001  for ( int i = 0; i < Count(); ++i )
//STRIP001  {
//STRIP001      for ( int j = i+1; j < Count(); ++j )
//STRIP001      {
//STRIP001          //Wenn zwei Rechtecke ineinanderliegen, so ist eins davon
//STRIP001          //uberfluessig.
//STRIP001          if ( (*(pData + i)).IsInside( *(pData + j) ) )
//STRIP001          {
//STRIP001              Remove( j, 1 );
//STRIP001              --j;
//STRIP001          }
//STRIP001          else if ( (*(pData + j)).IsInside( *(pData + i) ) )
//STRIP001          {
//STRIP001              *(pData + i) = *(pData + j);
//STRIP001              Remove( j, 1 );
//STRIP001              i = -1;
//STRIP001              break;
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              //Wenn zwei Rechtecke dieselbe Flaeche haben wie deren
//STRIP001              //Union abzueglich deren Intersection, so ist eines
//STRIP001              //davon ueberfluessig.
//STRIP001              //Um moeglichst viel zusammenzufassen und in der Folge
//STRIP001              //moeglichst wenig einzelne Paints zu haben darf die Flaeche
//STRIP001              //der Union ruhig ein bischen groesser sein
//STRIP001              //( 9622 * 141.5 = 1361513 ~= ein virtel Zentimeter ueber die
//STRIP001              //                            Breite einer DINA4 Seite)
//STRIP001              const long nFuzzy = bFuzzy ? 1361513 : 0;
//STRIP001              SwRect aUnion( *(pData + i) );aUnion.Union( *(pData + j) );
//STRIP001              SwRect aInter( *(pData + i) );aInter.Intersection( *(pData + j));
//STRIP001              if ( (::CalcArea( *(pData + i) ) +
//STRIP001                    ::CalcArea( *(pData + j) ) + nFuzzy) >=
//STRIP001                   (::CalcArea( aUnion ) - CalcArea( aInter )) )
//STRIP001              {
//STRIP001                  *(pData + i) = aUnion;
//STRIP001                  Remove( j, 1 );
//STRIP001                  i = -1;
//STRIP001                  break;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }
#pragma optimize("",on)


}
