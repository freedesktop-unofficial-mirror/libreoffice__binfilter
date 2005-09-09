/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_noteurl.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 02:28:40 $
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



/*N*/  #pragma hdrstop
/*N*/
/*N*/  #include "swtypes.hxx"
/*N*/
/*N*/  #ifndef _SV_OUTDEV_HXX //autogen
/*N*/  #include <vcl/outdev.hxx>
/*N*/  #endif
/*N*/  #ifndef _GOODIES_IMAPRECT_HXX
/*N*/  #include <svtools/imaprect.hxx>
/*N*/  #endif
/*N*/  #ifndef _IMAP_HXX //autogen
/*N*/  #include <svtools/imap.hxx>
/*N*/  #endif
/*N*/
/*N*/  #include "txttypes.hxx"
/*N*/  #include "noteurl.hxx"
/*N*/  namespace binfilter {
/*N*/  // globale Variable, wird in noteurl.Hxx bekanntgegeben
/*N*/  SwNoteURL *pNoteURL = NULL;
//STRIP001
//STRIP001 SV_IMPL_PTRARR( SwURLNoteList, SwURLNotePtr )
//STRIP001
//STRIP001
//STRIP001 void SwNoteURL::InsertURLNote( const XubString& rURL, const XubString& rTarget,
//STRIP001  const SwRect& rRect )
//STRIP001 {
//STRIP001  MSHORT i;
//STRIP001  MSHORT nCount = aList.Count();
//STRIP001  for( i = 0; i < nCount; i++ )
//STRIP001      if( rRect == aList.GetObject(i)->GetRect() )
//STRIP001          break;
//STRIP001  if( i == nCount )
//STRIP001  {
//STRIP001      SwURLNote *pNew = new SwURLNote( rURL, rTarget, rRect );
//STRIP001      aList.Insert( pNew, nCount );
//STRIP001  }
//STRIP001 }
//STRIP001
//STRIP001
//STRIP001 void SwNoteURL::FillImageMap( ImageMap *pMap, const Point &rPos,
//STRIP001  const MapMode& rMap )
//STRIP001 {
//STRIP001  ASSERT( pMap, "FillImageMap: No ImageMap, no cookies!" );
//STRIP001  MSHORT nCount = Count();
//STRIP001  if( nCount )
//STRIP001  {
//STRIP001      MapMode aMap( MAP_100TH_MM );
//STRIP001      for( MSHORT i = 0; i < nCount; ++i )
//STRIP001      {
//STRIP001          const SwURLNote &rNote = GetURLNote( i );
//STRIP001          SwRect aSwRect( rNote.GetRect() );
//STRIP001          aSwRect -= rPos;
//STRIP001          Rectangle aRect( OutputDevice::LogicToLogic( aSwRect.SVRect(),
//STRIP001                                                       rMap, aMap ) );
//STRIP001          IMapRectangleObject aObj( aRect, rNote.GetURL(), aEmptyStr,
//STRIP001                                    rNote.GetTarget(), sal_True, sal_False );
//STRIP001          pMap->InsertIMapObject( aObj );
//STRIP001      }
//STRIP001  }
//STRIP001 }




}
