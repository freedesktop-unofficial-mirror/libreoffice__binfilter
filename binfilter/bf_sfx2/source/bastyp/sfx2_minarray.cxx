/*************************************************************************
 *
 *  $RCSfile: sfx2_minarray.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-04 10:01:59 $
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

#include "minarray.hxx"
namespace binfilter {

// -----------------------------------------------------------------------

/*N*/ SfxPtrArr::SfxPtrArr( BYTE nInitSize, BYTE nGrowSize ):
/*N*/   nUsed( 0 ),
/*N*/   nGrow( nGrowSize ? nGrowSize : 1 ),
/*N*/   nUnused( nInitSize )
/*N*/ {
/*N*/   DBG_MEMTEST();
/*N*/   USHORT nMSCBug = nInitSize;
/*N*/
/*N*/   if ( nMSCBug > 0 )
/*N*/       pData = new void*[nMSCBug];
/*N*/   else
/*N*/       pData = 0;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPtrArr::SfxPtrArr( const SfxPtrArr& rOrig )
/*N*/ {
/*N*/   DBG_MEMTEST();
/*N*/   nUsed = rOrig.nUsed;
/*N*/   nGrow = rOrig.nGrow;
/*N*/   nUnused = rOrig.nUnused;
/*N*/
/*N*/   if ( rOrig.pData != 0 )
/*N*/   {
/*N*/       pData = new void*[nUsed+nUnused];
/*N*/       memcpy( pData, rOrig.pData, nUsed*sizeof(void*) );
/*N*/   }
/*N*/   else
/*?*/       pData = 0;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPtrArr::~SfxPtrArr()
/*N*/ {
/*N*/   DBG_MEMTEST();
/*N*/   delete [] pData;
/*N*/ }

// -----------------------------------------------------------------------

//STRIP001 SfxPtrArr& SfxPtrArr::operator=( const SfxPtrArr& rOrig )
//STRIP001 {
//STRIP001  DBG_MEMTEST();
//STRIP001
//STRIP001  __DELETE (DEL_ARRAY (nUsed+nUnused)) pData;
//STRIP001
//STRIP001  nUsed = rOrig.nUsed;
//STRIP001  nGrow = rOrig.nGrow;
//STRIP001  nUnused = rOrig.nUnused;
//STRIP001
//STRIP001  if ( rOrig.pData != 0 )
//STRIP001  {
//STRIP001      pData = new void*[nUsed+nUnused];
//STRIP001      memcpy( pData, rOrig.pData, nUsed*sizeof(void*) );
//STRIP001  }
//STRIP001  else
//STRIP001      pData = 0;
//STRIP001  return *this;
//STRIP001 }

// -----------------------------------------------------------------------

/*N*/ void SfxPtrArr::Append( void* aElem )
/*N*/ {
/*N*/   DBG_MEMTEST();
/*N*/   DBG_ASSERT( (nUsed+1) < ( USHRT_MAX / sizeof(void*) ), "array too large" );
/*N*/   // musz das Array umkopiert werden?
/*N*/   if ( nUnused == 0 )
/*N*/   {
/*N*/       USHORT nNewSize = (nUsed == 1) ? (nGrow==1 ? 2 : nGrow) : nUsed+nGrow;
/*N*/       void** pNewData = new void*[nNewSize];
/*N*/       if ( pData )
/*N*/       {
/*N*/           DBG_ASSERT( nUsed <= nNewSize, "" );
/*N*/           memmove( pNewData, pData, sizeof(void*)*nUsed );
/*N*/           delete [] pData;
/*N*/       }
/*N*/       nUnused = nNewSize-nUsed;
/*N*/       pData = pNewData;
/*N*/   }
/*N*/
/*N*/   // jetzt hinten in den freien Raum schreiben
/*N*/   pData[nUsed] = aElem;
/*N*/   ++nUsed;
/*N*/   --nUnused;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ USHORT SfxPtrArr::Remove( USHORT nPos, USHORT nLen )
/*N*/ {
/*N*/   DBG_MEMTEST();
/*N*/   // nLen adjustieren, damit nicht ueber das Ende hinaus geloescht wird
/*N*/   nLen = Min( (USHORT)(nUsed-nPos), nLen );
/*N*/
/*N*/   // einfache Aufgaben erfordern einfache Loesungen!
/*N*/   if ( nLen == 0 )
/*N*/       return 0;
/*N*/
/*N*/   // bleibt vielleicht keiner uebrig
/*N*/   if ( (nUsed-nLen) == 0 )
/*N*/   {
/*N*/       delete [] pData;
/*N*/       pData = 0;
/*N*/       nUsed = 0;
/*N*/       nUnused = 0;
/*N*/       return nLen;
/*N*/   }
/*N*/
/*N*/   // feststellen, ob das Array dadurch physikalisch schrumpft...
/*N*/   if ( (nUnused+nLen) >= nGrow )
/*N*/   {
/*N*/       // auf die naechste Grow-Grenze aufgerundet verkleinern
/*N*/       USHORT nNewUsed = nUsed-nLen;
/*N*/       USHORT nNewSize = (nNewUsed+nGrow-1)/nGrow; nNewSize *= nGrow;
/*N*/       DBG_ASSERT( nNewUsed <= nNewSize && nNewUsed+nGrow > nNewSize,
/*N*/                   "shrink size computation failed" );
/*N*/       void** pNewData = new void*[nNewSize];
/*N*/       if ( nPos > 0 )
/*N*/       {
/*N*/           DBG_ASSERT( nPos <= nNewSize, "" );
/*N*/           memmove( pNewData, pData, sizeof(void*)*nPos );
/*N*/       }
/*N*/       if ( nNewUsed != nPos )
/*N*/           memmove( pNewData+nPos, pData+nPos+nLen,
/*N*/                    sizeof(void*)*(nNewUsed-nPos) );
/*N*/       delete [] pData;
/*N*/       pData = pNewData;
/*N*/       nUsed = nNewUsed;
/*N*/       nUnused = nNewSize - nNewUsed;
/*N*/       return nLen;
/*N*/   }
/*N*/
/*N*/   // in allen anderen Faellen nur zusammenschieben
/*N*/   if ( nUsed-nPos-nLen > 0 )
/*N*/       memmove( pData+nPos, pData+nPos+nLen, (nUsed-nPos-nLen)*sizeof(void*) );
/*N*/   nUsed -= nLen;
/*N*/   nUnused += nLen;
/*N*/   return nLen;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ BOOL SfxPtrArr::Remove( void* aElem )
/*N*/ {
/*N*/   DBG_MEMTEST();
/*N*/   // einfache Aufgaben ...
/*N*/   if ( nUsed == 0 )
/*N*/       return FALSE;
/*N*/
/*N*/   // rueckwaerts, da meist der letzte zuerst wieder entfernt wird
/*N*/   void* *pIter = pData + nUsed - 1;
/*N*/   for ( USHORT n = 0; n < nUsed; ++n, --pIter )
/*N*/       if ( *pIter == aElem )
/*N*/       {
/*N*/           Remove(nUsed-n-1, 1);
/*N*/           return TRUE;
/*N*/       }
/*N*/   return FALSE;
/*N*/ }

// -----------------------------------------------------------------------

/*?*/ BOOL SfxPtrArr::Replace( void* aOldElem, void* aNewElem )
/*?*/ {DBG_ASSERT(0, "STRIP"); return FALSE;//STRIP001
//STRIP001  DBG_MEMTEST();
//STRIP001  // einfache Aufgaben ...
//STRIP001  if ( nUsed == 0 )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  // rueckwaerts, da meist der letzte zuerst wieder entfernt wird
//STRIP001  void* *pIter = pData + nUsed - 1;
//STRIP001  for ( USHORT n = 0; n < nUsed; ++n, --pIter )
//STRIP001      if ( *pIter == aOldElem )
//STRIP001      {
//STRIP001          pData[nUsed-n-1] = aNewElem;
//STRIP001          return TRUE;
//STRIP001      }
//STRIP001  return FALSE;
/*?*/ }

// -----------------------------------------------------------------------

/*N*/ BOOL SfxPtrArr::Contains( const void* rItem ) const
/*N*/ {
/*N*/   DBG_MEMTEST();
/*N*/   if ( !nUsed )
/*N*/       return FALSE;
/*N*/
/*N*/   for ( USHORT n = 0; n < nUsed; ++n )
/*N*/   {
/*N*/       void* p = GetObject(n);
/*N*/       if ( p == rItem )
/*N*/           return TRUE;
/*N*/   }
/*N*/
/*N*/   return FALSE;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ void SfxPtrArr::Insert( USHORT nPos, void* rElem )
/*N*/ {
/*N*/   DBG_MEMTEST();
/*N*/   DBG_ASSERT( (nUsed+1) < ( USHRT_MAX / sizeof(void*) ), "array too large" );
/*N*/   // musz das Array umkopiert werden?
/*N*/   if ( nUnused == 0 )
/*N*/   {
/*N*/       // auf die naechste Grow-Grenze aufgerundet vergroeszern
/*N*/       USHORT nNewSize = nUsed+nGrow;
/*N*/       void** pNewData = new void*[nNewSize];
/*N*/
/*N*/       if ( pData )
/*N*/       {
/*N*/           DBG_ASSERT( nUsed < nNewSize, "" );
/*N*/           memmove( pNewData, pData, sizeof(void*)*nUsed );
/*N*/           delete [] pData;
/*N*/       }
/*N*/       nUnused = nNewSize-nUsed;
/*N*/       pData = pNewData;
/*N*/   }
/*N*/
/*N*/   // jetzt den hinteren Teil verschieben
/*N*/   if ( nPos < nUsed )
/*N*/       memmove( pData+nPos+1, pData+nPos, (nUsed-nPos)*sizeof(void*) );
/*N*/
/*N*/   // jetzt in den freien Raum schreiben
/*N*/   memmove( pData+nPos, &rElem, sizeof(void*) );
/*N*/   nUsed += 1;
/*N*/   nUnused -= 1;
/*N*/ }

// class ByteArr ---------------------------------------------------------

//STRIP001 ByteArr::ByteArr( BYTE nInitSize, BYTE nGrowSize ):
//STRIP001  nUsed( 0 ),
//STRIP001  nGrow( nGrowSize ? nGrowSize : 1 ),
//STRIP001  nUnused( nInitSize )
//STRIP001 {
//STRIP001  DBG_MEMTEST();
//STRIP001  USHORT nMSCBug = nInitSize;
//STRIP001
//STRIP001  if ( nInitSize > 0 )
//STRIP001      pData = new char[nMSCBug];
//STRIP001  else
//STRIP001      pData = 0;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 ByteArr::ByteArr( const ByteArr& rOrig )
//STRIP001 {
//STRIP001  DBG_MEMTEST();
//STRIP001  nUsed = rOrig.nUsed;
//STRIP001  nGrow = rOrig.nGrow;
//STRIP001  nUnused = rOrig.nUnused;
//STRIP001
//STRIP001  if ( rOrig.pData != 0 )
//STRIP001  {
//STRIP001      pData = new char[nUsed+nUnused];
//STRIP001      memcpy( pData, rOrig.pData, nUsed*sizeof(char) );
//STRIP001  }
//STRIP001  else
//STRIP001      pData = 0;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 ByteArr::~ByteArr()
//STRIP001 {
//STRIP001  DBG_MEMTEST();
//STRIP001  __DELETE (DEL_ARRAY (nUsed+nUnused)) pData;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 ByteArr& ByteArr::operator=( const ByteArr& rOrig )
//STRIP001 {
//STRIP001  DBG_MEMTEST();
//STRIP001
//STRIP001  __DELETE (DEL_ARRAY (nUsed+nUnused)) pData;
//STRIP001
//STRIP001  nUsed = rOrig.nUsed;
//STRIP001  nGrow = rOrig.nGrow;
//STRIP001  nUnused = rOrig.nUnused;
//STRIP001
//STRIP001  if ( rOrig.pData != 0 )
//STRIP001  {
//STRIP001      pData = new char[nUsed+nUnused];
//STRIP001      memcpy( pData, rOrig.pData, nUsed*sizeof(char) );
//STRIP001  }
//STRIP001  else
//STRIP001      pData = 0;
//STRIP001  return *this;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 void ByteArr::Append( char aElem )
//STRIP001 {
//STRIP001  DBG_MEMTEST();
//STRIP001  // musz das Array umkopiert werden?
//STRIP001  if ( nUnused == 0 )
//STRIP001  {
//STRIP001      USHORT nNewSize = (nUsed == 1) ? (nGrow==1 ? 2 : nGrow) : nUsed+nGrow;
//STRIP001      char* pNewData = new char[nNewSize];
//STRIP001      if ( pData )
//STRIP001      {
//STRIP001          DBG_ASSERT( nUsed <= nNewSize, "" );
//STRIP001          memmove( pNewData, pData, sizeof(char)*nUsed );
//STRIP001          __DELETE (DEL_ARRAY (nUsed+nUnused)) pData;
//STRIP001      }
//STRIP001      nUnused = nNewSize-nUsed;
//STRIP001      pData = pNewData;
//STRIP001  }
//STRIP001
//STRIP001  // jetzt hinten in den freien Raum schreiben
//STRIP001  pData[nUsed] = aElem;
//STRIP001  ++nUsed;
//STRIP001  --nUnused;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 USHORT ByteArr::Remove( USHORT nPos, USHORT nLen )
//STRIP001 {
//STRIP001  DBG_MEMTEST();
//STRIP001  // nLen adjustieren, damit nicht ueber das Ende hinaus geloescht wird
//STRIP001  nLen = Min( (USHORT)(nUsed-nPos), nLen );
//STRIP001
//STRIP001  // einfache Aufgaben erfordern einfache Loesungen!
//STRIP001  if ( nLen == 0 )
//STRIP001      return 0;
//STRIP001
//STRIP001  // bleibt vielleicht keiner uebrig
//STRIP001  if ( (nUsed-nLen) == 0 )
//STRIP001  {
//STRIP001      __DELETE (DEL_ARRAY (nUsed+nUnused)) pData;
//STRIP001      pData = 0;
//STRIP001      nUsed = 0;
//STRIP001      nUnused = 0;
//STRIP001      return nLen;
//STRIP001  }
//STRIP001
//STRIP001  // feststellen, ob das Array dadurch physikalisch schrumpft...
//STRIP001  if ( (nUnused+nLen) >= nGrow )
//STRIP001  {
//STRIP001      // auf die naechste Grow-Grenze aufgerundet verkleinern
//STRIP001      USHORT nNewUsed = nUsed-nLen;
//STRIP001      USHORT nNewSize = (nNewUsed+nGrow-1)/nGrow; nNewSize *= nGrow;
//STRIP001      DBG_ASSERT( nNewUsed <= nNewSize && nNewUsed+nGrow > nNewSize,
//STRIP001                  "shrink size computation failed" );
//STRIP001      char* pNewData = new char[nNewSize];
//STRIP001      if ( nPos > 0 )
//STRIP001      {
//STRIP001          DBG_ASSERT( nPos <= nNewSize, "" );
//STRIP001          memmove( pNewData, pData, sizeof(char)*nPos );
//STRIP001      }
//STRIP001      if ( nNewUsed != nPos )
//STRIP001          memmove( pNewData+nPos, pData+nPos+nLen,
//STRIP001                   sizeof(char)*(nNewUsed-nPos) );
//STRIP001      __DELETE (DEL_ARRAY (nUsed+nUnused)) pData;
//STRIP001      pData = pNewData;
//STRIP001      nUsed = nNewUsed;
//STRIP001      nUnused = nNewSize - nNewUsed;
//STRIP001      return nLen;
//STRIP001  }
//STRIP001
//STRIP001  // in allen anderen Faellen nur zusammenschieben
//STRIP001  if ( nUsed-nPos-nLen > 0 )
//STRIP001      memmove( pData+nPos, pData+nPos+nLen, (nUsed-nPos-nLen)*sizeof(char) );
//STRIP001  nUsed -= nLen;
//STRIP001  nUnused += nLen;
//STRIP001  return nLen;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 BOOL ByteArr::Remove( char aElem )
//STRIP001 {
//STRIP001  DBG_MEMTEST();
//STRIP001  // einfache Aufgaben ...
//STRIP001  if ( nUsed == 0 )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  // rueckwaerts, da meist der letzte zuerst wieder entfernt wird
//STRIP001  char *pIter = pData + nUsed - 1;
//STRIP001  for ( USHORT n = 0; n < nUsed; ++n, --pIter )
//STRIP001      if ( *pIter == aElem )
//STRIP001      {
//STRIP001          Remove(nUsed-n-1, 1);
//STRIP001          return TRUE;
//STRIP001      }
//STRIP001  return FALSE;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 BOOL ByteArr::Contains( const char rItem ) const
//STRIP001 {
//STRIP001  DBG_MEMTEST();
//STRIP001  if ( !nUsed )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  for ( USHORT n = 0; n < nUsed; ++n )
//STRIP001  {
//STRIP001      char p = GetObject(n);
//STRIP001      if ( p == rItem )
//STRIP001          return TRUE;
//STRIP001  }
//STRIP001
//STRIP001  return FALSE;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 void ByteArr::Insert( USHORT nPos, char rElem )
//STRIP001 {
//STRIP001  DBG_MEMTEST();
//STRIP001  // musz das Array umkopiert werden?
//STRIP001  if ( nUnused == 0 )
//STRIP001  {
//STRIP001      // auf die naechste Grow-Grenze aufgerundet vergroeszern
//STRIP001      USHORT nNewSize = nUsed+nGrow;
//STRIP001      char* pNewData = new char[nNewSize];
//STRIP001
//STRIP001      if ( pData )
//STRIP001      {
//STRIP001          DBG_ASSERT( nUsed < nNewSize, "" );
//STRIP001          memmove( pNewData, pData, sizeof(char)*nUsed );
//STRIP001          __DELETE (DEL_ARRAY (nUsed)) pData;
//STRIP001      }
//STRIP001      nUnused = nNewSize-nUsed;
//STRIP001      pData = pNewData;
//STRIP001  }
//STRIP001
//STRIP001  // jetzt den hinteren Teil verschieben
//STRIP001  if ( nPos < nUsed )
//STRIP001      memmove( pData+nPos+1, pData+nPos, (nUsed-nPos)*sizeof(char) );
//STRIP001
//STRIP001  // jetzt in den freien Raum schreiben
//STRIP001  memmove( pData+nPos, &rElem, sizeof(char) );
//STRIP001  nUsed += 1;
//STRIP001  nUnused -= 1;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 char ByteArr::operator[]( USHORT nPos ) const
//STRIP001 {
//STRIP001  DBG_MEMTEST();
//STRIP001  DBG_ASSERT( nPos < nUsed, "" );
//STRIP001  return *(pData+nPos);
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 char& ByteArr::operator [] (USHORT nPos)
//STRIP001 {
//STRIP001  DBG_MEMTEST();
//STRIP001  DBG_ASSERT( nPos < nUsed, "" );
//STRIP001  return *(pData+nPos);
//STRIP001 }

// class WordArr ---------------------------------------------------------

/*N*/ WordArr::WordArr( BYTE nInitSize, BYTE nGrowSize ):
/*N*/   nUsed( 0 ),
/*N*/   nGrow( nGrowSize ? nGrowSize : 1 ),
/*N*/   nUnused( nInitSize )
/*N*/ {
/*N*/   DBG_MEMTEST();
/*N*/   USHORT nMSCBug = nInitSize;
/*N*/
/*N*/   if ( nInitSize > 0 )
/*N*/       pData = new short[nMSCBug];
/*N*/   else
/*N*/       pData = 0;
/*N*/ }

// -----------------------------------------------------------------------

//STRIP001 WordArr::WordArr( const WordArr& rOrig )
//STRIP001 {
//STRIP001  DBG_MEMTEST();
//STRIP001  nUsed = rOrig.nUsed;
//STRIP001  nGrow = rOrig.nGrow;
//STRIP001  nUnused = rOrig.nUnused;
//STRIP001
//STRIP001  if ( rOrig.pData != 0 )
//STRIP001  {
//STRIP001      pData = new short[nUsed+nUnused];
//STRIP001      memcpy( pData, rOrig.pData, nUsed*sizeof(short) );
//STRIP001  }
//STRIP001  else
//STRIP001      pData = 0;
//STRIP001 }

// -----------------------------------------------------------------------

/*N*/ WordArr::~WordArr()
/*N*/ {
/*N*/   DBG_MEMTEST();
/*N*/   delete [] pData;
/*N*/ }

// -----------------------------------------------------------------------

//STRIP001 WordArr& WordArr::operator=( const WordArr& rOrig )
//STRIP001 {
//STRIP001  DBG_MEMTEST();
//STRIP001
//STRIP001  __DELETE (DEL_ARRAY (nUsed+nUnused)) pData;
//STRIP001
//STRIP001  nUsed = rOrig.nUsed;
//STRIP001  nGrow = rOrig.nGrow;
//STRIP001  nUnused = rOrig.nUnused;
//STRIP001
//STRIP001  if ( rOrig.pData != 0 )
//STRIP001  {
//STRIP001      pData = new short[nUsed+nUnused];
//STRIP001      memcpy( pData, rOrig.pData, nUsed*sizeof(short) );
//STRIP001  }
//STRIP001  else
//STRIP001      pData = 0;
//STRIP001  return *this;
//STRIP001 }

// -----------------------------------------------------------------------

/*N*/ void WordArr::Append( short aElem )
/*N*/ {
/*N*/   DBG_MEMTEST();
/*N*/   // musz das Array umkopiert werden?
/*N*/   if ( nUnused == 0 )
/*N*/   {
/*N*/       USHORT nNewSize = (nUsed == 1) ? (nGrow==1 ? 2 : nGrow) : nUsed+nGrow;
/*N*/       short* pNewData = new short[nNewSize];
/*N*/       if ( pData )
/*N*/       {
/*N*/           DBG_ASSERT( nUsed <= nNewSize, " " );
/*N*/           memmove( pNewData, pData, sizeof(short)*nUsed );
/*N*/           delete [] pData;
/*N*/       }
/*N*/       nUnused = nNewSize-nUsed;
/*N*/       pData = pNewData;
/*N*/   }
/*N*/
/*N*/   // jetzt hinten in den freien Raum schreiben
/*N*/   pData[nUsed] = aElem;
/*N*/   ++nUsed;
/*N*/   --nUnused;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ USHORT WordArr::Remove( USHORT nPos, USHORT nLen )
/*N*/ {DBG_ASSERT(0, "STRIP"); return 0;//STRIP001
//STRIP001  DBG_MEMTEST();
//STRIP001  // nLen adjustieren, damit nicht ueber das Ende hinaus geloescht wird
//STRIP001  nLen = Min( (USHORT)(nUsed-nPos), nLen );
//STRIP001
//STRIP001  // einfache Aufgaben erfordern einfache Loesungen!
//STRIP001  if ( nLen == 0 )
//STRIP001      return 0;
//STRIP001
//STRIP001  // bleibt vielleicht keiner uebrig
//STRIP001  if ( (nUsed-nLen) == 0 )
//STRIP001  {
//STRIP001      __DELETE (DEL_ARRAY (nUsed+nUnused)) pData;
//STRIP001      pData = 0;
//STRIP001      nUsed = 0;
//STRIP001      nUnused = 0;
//STRIP001      return nLen;
//STRIP001  }
//STRIP001
//STRIP001  // feststellen, ob das Array dadurch physikalisch schrumpft...
//STRIP001  if ( (nUnused+nLen) >= nGrow )
//STRIP001  {
//STRIP001      // auf die naechste Grow-Grenze aufgerundet verkleinern
//STRIP001      USHORT nNewUsed = nUsed-nLen;
//STRIP001      USHORT nNewSize = (nNewUsed+nGrow-1)/nGrow; nNewSize *= nGrow;
//STRIP001      DBG_ASSERT( nNewUsed <= nNewSize && nNewUsed+nGrow > nNewSize,
//STRIP001                  "shrink size computation failed" );
//STRIP001      short* pNewData = new short[nNewSize];
//STRIP001      if ( nPos > 0 )
//STRIP001      {
//STRIP001          DBG_ASSERT( nPos <= nNewSize, "" );
//STRIP001          memmove( pNewData, pData, sizeof(short)*nPos );
//STRIP001      }
//STRIP001      if ( nNewUsed != nPos )
//STRIP001          memmove( pNewData+nPos, pData+nPos+nLen,
//STRIP001                   sizeof(short)*(nNewUsed-nPos) );
//STRIP001          __DELETE (DEL_ARRAY (nUsed+nUnused)) pData;
//STRIP001      pData = pNewData;
//STRIP001      nUsed = nNewUsed;
//STRIP001      nUnused = nNewSize - nNewUsed;
//STRIP001      return nLen;
//STRIP001  }
//STRIP001
//STRIP001  // in allen anderen Faellen nur zusammenschieben
//STRIP001  if ( nUsed-nPos-nLen > 0 )
//STRIP001      memmove( pData+nPos, pData+nPos+nLen, (nUsed-nPos-nLen)*sizeof(short) );
//STRIP001  nUsed -= nLen;
//STRIP001  nUnused += nLen;
//STRIP001  return nLen;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ BOOL WordArr::Remove( short aElem )
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  DBG_MEMTEST();
//STRIP001  // einfache Aufgaben ...
//STRIP001  if ( nUsed == 0 )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  // rueckwaerts, da meist der letzte zuerst wieder entfernt wird
//STRIP001  short *pIter = pData + nUsed - 1;
//STRIP001  for ( USHORT n = 0; n < nUsed; ++n, --pIter )
//STRIP001      if ( *pIter == aElem )
//STRIP001      {
//STRIP001          Remove(nUsed-n-1, 1);
//STRIP001          return TRUE;
//STRIP001      }
/*N*/   return FALSE;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ BOOL WordArr::Contains( const short rItem ) const
/*N*/ {
/*N*/   DBG_MEMTEST();
/*N*/   if ( !nUsed )
/*N*/       return FALSE;
/*N*/
/*N*/   for ( USHORT n = 0; n < nUsed; ++n )
/*N*/   {
/*N*/       short p = GetObject(n);
/*N*/       if ( p == rItem )
/*N*/           return TRUE;
/*N*/   }
/*N*/
/*N*/   return FALSE;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ void WordArr::Insert( USHORT nPos, short rElem )
/*N*/ {
/*N*/   DBG_MEMTEST();
/*N*/   // musz das Array umkopiert werden?
/*N*/   if ( nUnused == 0 )
/*N*/   {
/*N*/       // auf die naechste Grow-Grenze aufgerundet vergroeszern
/*?*/       USHORT nNewSize = nUsed+nGrow;
/*?*/       short* pNewData = new short[nNewSize];
/*?*/
/*?*/       if ( pData )
/*?*/       {
/*?*/           DBG_ASSERT( nUsed < nNewSize, "" );
/*?*/           memmove( pNewData, pData, sizeof(short)*nUsed );
/*?*/           delete [] pData;
/*?*/       }
/*?*/       nUnused = nNewSize-nUsed;
/*?*/       pData = pNewData;
/*N*/   }
/*N*/
/*N*/   // jetzt den hinteren Teil verschieben
/*N*/   if ( nPos < nUsed )
/*N*/       memmove( pData+nPos+1, pData+nPos, (nUsed-nPos)*sizeof(short) );
/*N*/
/*N*/   // jetzt in den freien Raum schreiben
/*N*/   memmove( pData+nPos, &rElem, sizeof(short) );
/*N*/   nUsed += 1;
/*N*/   nUnused -= 1;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ short WordArr::operator[]( USHORT nPos ) const
/*N*/ {
/*N*/   DBG_MEMTEST();
/*N*/   DBG_ASSERT( nPos < nUsed, "" );
/*N*/   return *(pData+nPos);
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ short& WordArr::operator [] (USHORT nPos)
/*N*/ {
/*N*/   DBG_MEMTEST();
/*N*/   DBG_ASSERT( nPos < nUsed, "" );
/*N*/   return *(pData+nPos);
/*N*/ }


}
