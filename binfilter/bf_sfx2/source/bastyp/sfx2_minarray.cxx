/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sfx2_minarray.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 11:26:05 $
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
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001
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


// -----------------------------------------------------------------------


// -----------------------------------------------------------------------


// -----------------------------------------------------------------------


// -----------------------------------------------------------------------


// -----------------------------------------------------------------------


// -----------------------------------------------------------------------


// -----------------------------------------------------------------------


// -----------------------------------------------------------------------


// -----------------------------------------------------------------------


// -----------------------------------------------------------------------


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


// -----------------------------------------------------------------------

/*N*/ WordArr::~WordArr()
/*N*/ {
/*N*/   DBG_MEMTEST();
/*N*/   delete [] pData;
/*N*/ }

// -----------------------------------------------------------------------


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
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ BOOL WordArr::Remove( short aElem )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
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
