/*************************************************************************
 *
 *  $RCSfile: sw_noteurl.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:51:20 $
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
