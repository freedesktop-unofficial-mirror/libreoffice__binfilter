/*************************************************************************
 *
 *  $RCSfile: svx_poly3d.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: aw $ $Date: 2003-11-18 19:23:54 $
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

#include <stdio.h>

#ifndef _STRING_H
#include <string.h>
#ifndef _STRING_H
#define _STRING_H
#endif
#endif

#ifndef _XPOLY_HXX
#include "xpoly.hxx"
#endif

#ifndef _POLY3D_HXX
#include "poly3d.hxx"
#endif

#ifndef _SVX_MATRIX3D_HXX
#include "matrix3d.hxx"
#endif

#ifndef _SV_POLY_HXX
#include <vcl/poly.hxx>
#endif

#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif

#ifndef _B3D_BASE3D_HXX
#include <goodies/base3d.hxx>
#endif
namespace binfilter {

/*N*/ DBG_NAME(Polygon3D)
/*N*/ DBG_NAME(PolyPolygon3D)

/*************************************************************************
|*
|* 3D-PolyPolygon-Implementierung
|*
\************************************************************************/

/*N*/ DECLARE_LIST(Polygon3DList, Polygon3D*)//STRIP008 ;

/*N*/ class ImpPolyPolygon3D
/*N*/ {
/*N*/ public:
/*N*/   Polygon3DList               aPoly3DList;
/*N*/   UINT16                      nRefCount;
/*N*/
/*N*/   ImpPolyPolygon3D(UINT16 nInitSize = 4, UINT16 nResize = 4)
/*N*/   :   aPoly3DList(1024, nInitSize, nResize) { nRefCount = 1; }
/*N*/   ImpPolyPolygon3D(const ImpPolyPolygon3D& rImpPolyPoly3D);
/*N*/   ~ImpPolyPolygon3D();
/*N*/
/*N*/   BOOL operator==(const ImpPolyPolygon3D& rImpPolyPoly3D) const;
/*N*/   BOOL operator!=(const ImpPolyPolygon3D& rImpPolyPoly3D) const
/*N*/       { return !operator==(rImpPolyPoly3D); }
/*N*/ };

/*************************************************************************
|*
|* Standard-Konstruktor
|*
\************************************************************************/

/*N*/ ImpPolygon3D::ImpPolygon3D(UINT16 nInitSize, UINT16 nPolyResize)
/*N*/ {
/*N*/   pPointAry = NULL;
/*N*/   bDeleteOldAry = FALSE;
/*N*/   bClosed = FALSE;
/*N*/   nSize = 0;
/*N*/   nResize = nPolyResize;
/*N*/   nPoints = 0;
/*N*/   nRefCount = 1;
/*N*/   Resize(nInitSize);
/*N*/ }

/*************************************************************************
|*
|* Copy-Konstruktor
|*
\************************************************************************/

/*N*/ ImpPolygon3D::ImpPolygon3D(const ImpPolygon3D& rImpPoly3D)
/*N*/ {
/*N*/   ((ImpPolygon3D&)rImpPoly3D).CheckPointDelete();
/*N*/
/*N*/   pPointAry = NULL;
/*N*/   bDeleteOldAry = FALSE;
/*N*/   bClosed = rImpPoly3D.bClosed;
/*N*/   nSize = 0;
/*N*/   nResize = rImpPoly3D.nResize;
/*N*/   nPoints = 0;
/*N*/   nRefCount = 1;
/*N*/   Resize(rImpPoly3D.nSize);
/*N*/
/*N*/   // Kopieren
/*N*/   nPoints = rImpPoly3D.nPoints;
/*N*/   memcpy(pPointAry, rImpPoly3D.pPointAry, nSize*sizeof(Vector3D));
/*N*/ }

/*************************************************************************
|*
|* Destruktor
|*
\************************************************************************/

/*N*/ ImpPolygon3D::~ImpPolygon3D()
/*N*/ {
/*N*/   delete[] (char*)pPointAry;
/*N*/
/*N*/   if(bDeleteOldAry)
/*N*/       delete[] (char*)pOldPointAry;
/*N*/ }

/*************************************************************************
|*
|* Gibt unter Beachtung eines Flags den Speicher fuer das Polygon frei.
|*
\************************************************************************/

/*N*/ void ImpPolygon3D::CheckPointDelete()
/*N*/ {
/*N*/   if(bDeleteOldAry)
/*N*/   {
/*N*/       delete[] (char*)pOldPointAry;
/*N*/       bDeleteOldAry = FALSE;
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|*    ImpPolygon3D::Resize()
|*
|*    !!! Polygongroesse aendern - wenn bDeletePoints FALSE, dann den
|*    Punkt-Array nicht loeschen, sondern in pOldPointAry sichern und
|*    das Flag bDeleteOldAry setzen. Beim naechsten Zugriff wird
|*    das Array dann geloescht.
|*    Damit wird verhindert, dass bei Poly3D[n] = Poly3D[0] durch ein
|*    Resize der fuer den rechten Ausdruck verwendete Vector3D-Array
|*    vorzeitig geloescht wird.
|*
\************************************************************************/

/*N*/ void ImpPolygon3D::Resize(UINT16 nNewSize, BOOL bDeletePoints)
/*N*/ {
/*N*/   if(nNewSize == nSize)
/*N*/       return;
/*N*/
/*N*/   UINT16 nOldSize = nSize;
/*N*/
/*N*/   CheckPointDelete();
/*N*/   pOldPointAry = pPointAry;
/*N*/
/*N*/   // Neue Groesse auf vielfaches von nResize runden, sofern Objekt
/*N*/   // nicht neu angelegt wurde (nSize != 0)
/*N*/   if(nSize && nNewSize > nSize)
/*N*/   {
/*N*/       DBG_ASSERT(nResize, "Resize-Versuch trotz nResize = 0 !");
/*N*/       nNewSize = nSize + ((nNewSize-nSize-1) / nResize + 1) * nResize;
/*N*/   }
/*N*/
/*N*/   // Punkt-Array erzeugen
/*N*/   nSize = nNewSize;
/*N*/   pPointAry = (Vector3D*)new char[nSize * sizeof(Vector3D)];
/*N*/   memset(pPointAry, 0, nSize * sizeof(Vector3D));
/*N*/
/*N*/   // Eventuell umkopieren
/*N*/   if(nOldSize)
/*N*/   {
/*N*/       if(nOldSize < nSize)
/*N*/       {
/*N*/           memcpy(pPointAry, pOldPointAry, nOldSize * sizeof(Vector3D));
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           memcpy(pPointAry, pOldPointAry, nSize*sizeof(Vector3D));
/*N*/
/*N*/           // Anzahl der gueltigen Punkte anpassen
/*N*/           if(nPoints > nSize)
/*N*/               nPoints = nSize;
/*N*/       }
/*N*/       if(bDeletePoints)
/*N*/           delete[] (char*)pOldPointAry;
/*N*/       else
/*N*/           bDeleteOldAry = TRUE;
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* Vektoren einfuegen
|*
\************************************************************************/

//STRIP001 void ImpPolygon3D::InsertSpace(UINT16 nPos, UINT16 nCount)
//STRIP001 {
//STRIP001  UINT16 nOldSize = nSize;
//STRIP001
//STRIP001  CheckPointDelete();
//STRIP001
//STRIP001  if(nPos > nPoints)
//STRIP001      nPos = nPoints;
//STRIP001
//STRIP001  // Wenn Polygon zu klein dann groesser machen
//STRIP001  if(nPoints + nCount > nSize)
//STRIP001      Resize(nPoints + nCount);
//STRIP001
//STRIP001  // Wenn nicht hinter dem letzten Punkt eingefuegt wurde,
//STRIP001  // den Rest nach hinten schieben
//STRIP001  if(nPos < nPoints)
//STRIP001  {
//STRIP001      memmove(&pPointAry[nPos+nCount], &pPointAry[nPos],
//STRIP001          (nPoints - nPos) * sizeof(Vector3D));
//STRIP001  }
//STRIP001  memset(&pPointAry[nPos], 0, nCount * sizeof(Vector3D));
//STRIP001
//STRIP001  nPoints += nCount;
//STRIP001 }

/*************************************************************************
|*
|* Vektoren entfernen
|*
\************************************************************************/

/*N*/ void ImpPolygon3D::Remove(UINT16 nPos, UINT16 nCount)
/*N*/ {
/*N*/   CheckPointDelete();
/*N*/
/*N*/   if(nPos + nCount <= nPoints)
/*N*/   {
/*N*/       UINT16 nMove = nPoints - nPos - nCount;
/*N*/       if(nMove)
/*N*/           memmove(&pPointAry[nPos], &pPointAry[nPos+nCount],
/*N*/                   nMove * sizeof(Vector3D));
/*N*/
/*N*/       nPoints -= nCount;
/*N*/       memset(&pPointAry[nPoints], 0, nCount * sizeof(Vector3D));
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* Standard-Konstruktor
|*
\************************************************************************/

/*N*/ Polygon3D::Polygon3D(UINT16 nSize, UINT16 nResize)
/*N*/ {
/*N*/   pImpPolygon3D = new ImpPolygon3D(nSize, nResize);
/*N*/ }

/*************************************************************************
|*
|* Copy-Konstruktor
|*
\************************************************************************/

/*N*/ Polygon3D::Polygon3D(const Polygon3D& rPoly3D)
/*N*/ {
/*N*/   pImpPolygon3D = rPoly3D.pImpPolygon3D;
/*N*/   pImpPolygon3D->nRefCount++;
/*N*/ }

/*************************************************************************
|*
|* Konstruktor aus Standard-Polygon
|*
\************************************************************************/

/*N*/ Polygon3D::Polygon3D(const Polygon& rPoly, double fScale)
/*N*/ {
/*N*/   UINT16 nSize(rPoly.GetSize());
/*N*/   pImpPolygon3D = new ImpPolygon3D(nSize);
/*N*/
/*N*/   if(fScale != 1.0)
/*N*/   {
/*?*/       for(UINT16 a=0; a<nSize; a++)
/*?*/       {
/*?*/           pImpPolygon3D->pPointAry[a].X() = rPoly[a].X() * fScale;
/*?*/           pImpPolygon3D->pPointAry[a].Y() = -rPoly[a].Y() * fScale;
/*?*/           pImpPolygon3D->pPointAry[a].Z() = 0.0;
/*?*/       }
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       for(UINT16 a=0; a<nSize; a++)
/*N*/       {
/*N*/           pImpPolygon3D->pPointAry[a].X() = rPoly[a].X();
/*N*/           pImpPolygon3D->pPointAry[a].Y() = -rPoly[a].Y();
/*N*/           pImpPolygon3D->pPointAry[a].Z() = 0.0;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   pImpPolygon3D->nPoints = nSize;
/*N*/
/*N*/   CheckClosed();
/*N*/ }

/*************************************************************************
|*
|* Konstruktor aus XPolygon - Achtung! Es werden nur die Punkte
|* uebernommen, ohne Konvertierung
|*
\************************************************************************/

/*N*/ Polygon3D::Polygon3D(const XPolygon& rXPoly, double fScale)
/*N*/ {
/*N*/   UINT16 nSize(rXPoly.GetPointCount());
/*N*/   pImpPolygon3D = new ImpPolygon3D(nSize);
/*N*/
/*N*/   if(fScale != 1.0)
/*N*/   {
/*?*/       for(UINT16 a=0; a<nSize; a++)
/*?*/       {
/*?*/           pImpPolygon3D->pPointAry[a].X() = rXPoly[a].X() * fScale;
/*?*/           pImpPolygon3D->pPointAry[a].Y() = -rXPoly[a].Y() * fScale;
/*?*/           pImpPolygon3D->pPointAry[a].Z() = 0.0;
/*?*/       }
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       for(UINT16 a=0; a<nSize; a++)
/*N*/       {
/*N*/           pImpPolygon3D->pPointAry[a].X() = rXPoly[a].X();
/*N*/           pImpPolygon3D->pPointAry[a].Y() = -rXPoly[a].Y();
/*N*/           pImpPolygon3D->pPointAry[a].Z() = 0.0;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   pImpPolygon3D->nPoints = nSize;
/*N*/
/*N*/   CheckClosed();
/*N*/ }

/*************************************************************************
|*
|* Closed-Status der Einzelpolygone korrigieren
|*
\************************************************************************/

/*N*/ void Polygon3D::CheckClosed()
/*N*/ {
/*N*/   // #97067# Test needs to look for > 1, not for != 0
/*N*/   if(pImpPolygon3D->nPoints > 1
/*N*/       && pImpPolygon3D->pPointAry[0] == pImpPolygon3D->pPointAry[pImpPolygon3D->nPoints - 1])
/*N*/   {
/*N*/       pImpPolygon3D->bClosed = TRUE;
/*N*/       pImpPolygon3D->nPoints--;
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* Destruktor
|*
\************************************************************************/

/*N*/ Polygon3D::~Polygon3D()
/*N*/ {
/*N*/   if( pImpPolygon3D->nRefCount > 1 )
/*N*/       pImpPolygon3D->nRefCount--;
/*N*/   else
/*N*/       delete pImpPolygon3D;
/*N*/ }

/*************************************************************************
|*
|* Closed-Zustand des Polygons testen
|*
\************************************************************************/

/*N*/ BOOL Polygon3D::IsClosed() const
/*N*/ {
/*N*/   return pImpPolygon3D->bClosed;
/*N*/ }

/*************************************************************************
|*
|* Closed-Zustand des Polygons aendern
|*
\************************************************************************/

/*N*/ void Polygon3D::SetClosed(BOOL bNew)
/*N*/ {
/*N*/   if(bNew != IsClosed())
/*N*/   {
/*N*/       CheckReference();
/*N*/       pImpPolygon3D->bClosed = bNew;
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* Referenzzaehler desImpPoly3D pruefen und ggf. von diesem abkoppeln
|*
\************************************************************************/

/*N*/ void Polygon3D::CheckReference()
/*N*/ {
/*N*/   if(pImpPolygon3D->nRefCount > 1)
/*N*/   {
/*N*/       pImpPolygon3D->nRefCount--;
/*N*/       pImpPolygon3D = new ImpPolygon3D(*pImpPolygon3D);
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* neue Groesse setzen
|*
\************************************************************************/

//STRIP001 void Polygon3D::SetSize(UINT16 nNewSize)
//STRIP001 {
//STRIP001  CheckReference();
//STRIP001  pImpPolygon3D->Resize(nNewSize);
//STRIP001 }

/*************************************************************************
|*
|* Groesse zurueckgeben
|*
\************************************************************************/

//STRIP001 UINT16 Polygon3D::GetSize() const
//STRIP001 {
//STRIP001  pImpPolygon3D->CheckPointDelete();
//STRIP001  return pImpPolygon3D->nSize;
//STRIP001 }

/*************************************************************************
|*
|* Laenge der Polygonkante zurueckgeben
|*
\************************************************************************/

/*N*/ double Polygon3D::GetLength() const
/*N*/ {
/*N*/   double fRetval = 0.0;
/*N*/   Vector3D *pLast = &pImpPolygon3D->pPointAry[
/*N*/       IsClosed() ? pImpPolygon3D->nPoints - 1 : 0];
/*N*/
/*N*/   for(UINT16 a=IsClosed() ? 0 : 1;a<pImpPolygon3D->nPoints;a++)
/*N*/   {
/*N*/       Vector3D *pCandidate = &pImpPolygon3D->pPointAry[a];
/*N*/       Vector3D aVec = *pCandidate - *pLast;
/*N*/       fRetval += aVec.GetLength();
/*N*/       pLast = pCandidate;
/*N*/   }
/*N*/
/*N*/   return fRetval;
/*N*/ }

/*************************************************************************
|*
|* Anzahl der belegten Punkte setzen
|*
\************************************************************************/

/*N*/ void Polygon3D::SetPointCount(UINT16 nPoints)
/*N*/ {
/*N*/   pImpPolygon3D->CheckPointDelete();
/*N*/   CheckReference();
/*N*/
/*N*/   if(pImpPolygon3D->nSize < nPoints)
/*?*/       pImpPolygon3D->Resize(nPoints);
/*N*/
/*N*/   if(nPoints < pImpPolygon3D->nPoints)
/*N*/   {
/*N*/       UINT16 nSize = pImpPolygon3D->nPoints - nPoints;
/*N*/       memset(&pImpPolygon3D->pPointAry[nPoints], 0, nSize * sizeof(Vector3D));
/*N*/   }
/*N*/   pImpPolygon3D->nPoints = nPoints;
/*N*/ }

/*************************************************************************
|*
|* Anzahl der belegten Punkte zurueckgeben
|*
\************************************************************************/

/*N*/ UINT16 Polygon3D::GetPointCount() const
/*N*/ {
/*N*/   pImpPolygon3D->CheckPointDelete();
/*N*/   return pImpPolygon3D->nPoints;
/*N*/ }

/*************************************************************************
|*
|* Polygonpunkte entfernen
|*
\************************************************************************/

//STRIP001 void Polygon3D::Remove(UINT16 nPos, UINT16 nCount)
//STRIP001 {
//STRIP001  CheckReference();
//STRIP001  pImpPolygon3D->Remove(nPos, nCount);
//STRIP001 }

/*************************************************************************
|*
|* const-Arrayoperator
|*
\************************************************************************/

/*N*/ const Vector3D& Polygon3D::operator[]( UINT16 nPos ) const
/*N*/ {
/*N*/   DBG_ASSERT(nPos < pImpPolygon3D->nPoints, "Ungueltiger Index bei const-Arrayzugriff auf Polygon3D");
/*N*/   pImpPolygon3D->CheckPointDelete();
/*N*/   return pImpPolygon3D->pPointAry[nPos];
/*N*/ }

/*************************************************************************
|*
|* Arrayoperator
|*
\************************************************************************/

/*N*/ Vector3D& Polygon3D::operator[]( UINT16 nPos )
/*N*/ {
/*N*/   pImpPolygon3D->CheckPointDelete();
/*N*/   CheckReference();
/*N*/
/*N*/   if(nPos >= pImpPolygon3D->nSize)
/*N*/   {
/*N*/       DBG_ASSERT(pImpPolygon3D->nResize, "Ungueltiger Index bei Arrayzugriff auf Polygon3D");
/*N*/       pImpPolygon3D->Resize(nPos + 1, FALSE);
/*N*/   }
/*N*/
/*N*/   if(nPos >= pImpPolygon3D->nPoints)
/*N*/       pImpPolygon3D->nPoints = nPos + 1;
/*N*/
/*N*/   return pImpPolygon3D->pPointAry[nPos];
/*N*/ }

/*************************************************************************
|*
|* Zuweisungsoperator
|*
\************************************************************************/

/*N*/ Polygon3D& Polygon3D::operator=(const Polygon3D& rPoly3D)
/*N*/ {
/*N*/   pImpPolygon3D->CheckPointDelete();
/*N*/
/*N*/   rPoly3D.pImpPolygon3D->nRefCount++;
/*N*/
/*N*/   if(pImpPolygon3D->nRefCount > 1)
/*N*/       pImpPolygon3D->nRefCount--;
/*N*/   else
/*N*/       delete pImpPolygon3D;
/*N*/
/*N*/   pImpPolygon3D = rPoly3D.pImpPolygon3D;
/*N*/
/*N*/   return *this;
/*N*/ }

/*************************************************************************
|*
|* Vergleichsoperator
|*
\************************************************************************/

/*N*/ BOOL Polygon3D::operator==(const Polygon3D& rPoly3D) const
/*N*/ {
/*N*/   pImpPolygon3D->CheckPointDelete();
/*N*/
/*N*/   if(rPoly3D.pImpPolygon3D == pImpPolygon3D)
/*N*/       return TRUE;
/*N*/
/*N*/   if(pImpPolygon3D->nPoints != rPoly3D.pImpPolygon3D->nPoints)
/*N*/       return FALSE;
/*N*/
/*N*/   // point-to point compare necessary
/*N*/   for(UINT16 a=0;a<pImpPolygon3D->nPoints;a++)
/*N*/       if(pImpPolygon3D->pPointAry[a] != rPoly3D.pImpPolygon3D->pPointAry[a])
/*N*/           return FALSE;
/*N*/
/*N*/   return TRUE;
/*N*/ }

/*************************************************************************
|*
|* Ungleichoperator
|*
\************************************************************************/

//STRIP001 BOOL Polygon3D::operator!=( const Polygon3D& rPoly3D ) const
//STRIP001 {
//STRIP001  pImpPolygon3D->CheckPointDelete();
//STRIP001
//STRIP001  if(rPoly3D.pImpPolygon3D != pImpPolygon3D)
//STRIP001      return TRUE;
//STRIP001
//STRIP001  if(pImpPolygon3D->nPoints != rPoly3D.pImpPolygon3D->nPoints)
//STRIP001      return TRUE;
//STRIP001
//STRIP001  // point-to point compare necessary
//STRIP001  for(UINT16 a=0;a<pImpPolygon3D->nPoints;a++)
//STRIP001      if(pImpPolygon3D->pPointAry[a] != rPoly3D.pImpPolygon3D->pPointAry[a])
//STRIP001          return TRUE;
//STRIP001
//STRIP001  return FALSE;
//STRIP001 }

/*************************************************************************
|*
|* aus einem Stream lesen
|*
*************************************************************************/

/*N*/ SvStream& operator>>(SvStream& rIStream, Polygon3D& rPoly3D)
/*N*/ {
/*N*/   DBG_CHKOBJ(&rPoly3D, Polygon3D, NULL);
/*N*/   UINT16 nPntCnt;
/*N*/
/*N*/   rPoly3D.pImpPolygon3D->CheckPointDelete();
/*N*/
/*N*/   // Anzahl der Punkte einlesen und Array erzeugen
/*N*/   rIStream >> nPntCnt;
/*N*/   rPoly3D.pImpPolygon3D->nPoints = nPntCnt;
/*N*/
/*N*/   if(rPoly3D.pImpPolygon3D->nRefCount != 1)
/*N*/   {
/*?*/       if(rPoly3D.pImpPolygon3D->nRefCount)
/*?*/           rPoly3D.pImpPolygon3D->nRefCount--;
/*?*/       rPoly3D.pImpPolygon3D = new ImpPolygon3D(nPntCnt);
/*N*/   }
/*N*/   else
/*N*/       rPoly3D.pImpPolygon3D->Resize(nPntCnt);
/*N*/
/*N*/   Vector3D* pPoint = rPoly3D.pImpPolygon3D->pPointAry;
/*N*/
/*N*/   for(UINT16 i = 0; i < nPntCnt; i++)
/*N*/       rIStream >> *pPoint++;
/*N*/
/*N*/   // auf geschlossenheit pruefen
/*N*/   if(*rPoly3D.pImpPolygon3D->pPointAry == *(pPoint-1))
/*N*/   {
/*N*/       rPoly3D.pImpPolygon3D->bClosed = TRUE;
/*N*/       rPoly3D.pImpPolygon3D->nPoints = nPntCnt-1;
/*N*/   }
/*N*/
/*N*/   INT16 nTmp;
/*N*/   rIStream >> nTmp; // war mal nConvexPoint
/*N*/   rIStream >> nTmp; // alt: rPoly3D.nOuterPoly;
/*N*/
/*N*/   return rIStream;
/*N*/ }

/*************************************************************************
|*
|* in einem Stream speichern
|*
*************************************************************************/

/*N*/ SvStream& operator<<(SvStream& rOStream, const Polygon3D& rPoly3D)
/*N*/ {
/*N*/   DBG_CHKOBJ(&rPoly3D, Polygon3D, NULL);
/*N*/
/*N*/   rPoly3D.pImpPolygon3D->CheckPointDelete();
/*N*/
/*N*/   Vector3D* pPoint = rPoly3D.pImpPolygon3D->pPointAry;
/*N*/   UINT16 nPntCnt = rPoly3D.GetPointCount();
/*N*/
/*N*/   if(rPoly3D.pImpPolygon3D->bClosed)
/*N*/   {
/*N*/       nPntCnt++;
/*N*/       rOStream << nPntCnt;
/*N*/       nPntCnt--;
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       rOStream << nPntCnt;
/*N*/   }
/*N*/
/*N*/   for (UINT16 i = 0; i < nPntCnt; i++)
/*N*/       rOStream << *pPoint++;
/*N*/
/*N*/   if(rPoly3D.pImpPolygon3D->bClosed)
/*N*/   {
/*N*/       // ersten Punkt nochmal, um polygon auf geschlossen zu zwingen
/*N*/       pPoint = rPoly3D.pImpPolygon3D->pPointAry;
/*N*/       rOStream << *pPoint;
/*N*/   }
/*N*/
/*N*/   rOStream << (INT16)0; // war mal nConvexPoint
/*N*/   rOStream << (INT16)-1; // alt: rPoly3D.nOuterPoly;
/*N*/
/*N*/   return rOStream;
/*N*/ }

/*************************************************************************
|*
|* Laufrichtung des Polygons feststellen
|*
\************************************************************************/

/*N*/ BOOL Polygon3D::IsClockwise(const Vector3D &rNormal) const
/*N*/ {
/*N*/   double fZValue = rNormal.Scalar(GetNormal());
/*N*/   return (fZValue >= 0.0);
/*N*/ }

/*************************************************************************
|*
|* Eine garantier die Orientierung wiederspiegelnde Ecke des Polygons
|* liefern
|*
\************************************************************************/

/*N*/ UINT16 Polygon3D::GetHighestEdge() const
/*N*/ {
/*N*/   UINT16 nRetval = 0;
/*N*/   Vector3D *pHighest = &pImpPolygon3D->pPointAry[nRetval];
/*N*/   for(UINT16 a=1;a<pImpPolygon3D->nPoints;a++)
/*N*/   {
/*N*/       Vector3D *pCandidate = &pImpPolygon3D->pPointAry[a];
/*N*/       if(pCandidate->X() <= pHighest->X())
/*N*/       {
/*N*/           if(pCandidate->X() < pHighest->X())
/*N*/           {
/*N*/               pHighest = pCandidate;
/*N*/               nRetval = a;
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               if(pCandidate->Y() <= pHighest->Y())
/*N*/               {
/*N*/                   if(pCandidate->Y() < pHighest->Y())
/*N*/                   {
/*N*/                       pHighest = pCandidate;
/*N*/                       nRetval = a;
/*N*/                   }
/*N*/                   else
/*N*/                   {
/*N*/                       if(pCandidate->Z() < pHighest->Z())
/*N*/                       {
/*N*/                           pHighest = pCandidate;
/*N*/                           nRetval = a;
/*N*/                       }
/*N*/                   }
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   return nRetval;
/*N*/ }

/*************************************************************************
|*
|* Normale des Polygons liefern
|*
|* Dabei eine Ecke waehlen, die die spezifische Orientierung des Polygons
|* besitzt und mit gleichen Punkten rechnen!
|*
\************************************************************************/

/*N*/ Vector3D Polygon3D::GetNormal() const
/*N*/ {
/*N*/   Vector3D aNormal(0.0, 0.0, -1.0);
/*N*/
/*N*/   if(pImpPolygon3D->nPoints > 2)
/*N*/   {
/*N*/       // HighestEdge bestimmen
/*N*/       UINT16 nPntCnt = pImpPolygon3D->nPoints;
/*N*/       UINT16 nHighest = GetHighestEdge();
/*N*/       const Vector3D &rHighest = (*this)[nHighest];
/*N*/
/*N*/       // Vorgaenger bestimmen
/*N*/       UINT16 nPrev(nHighest);
/*N*/       do {
/*N*/           nPrev = (nPrev == 0) ? nPntCnt-1 : nPrev-1;
/*N*/       } while((*this)[nPrev] == rHighest && nPrev != nHighest);
/*N*/       const Vector3D &rPrev = (*this)[nPrev];
/*N*/
/*N*/       // Nachfolger bestimmen
/*N*/       UINT16 nNext(nHighest);
/*N*/       do {
/*N*/           nNext = (nNext == nPntCnt-1) ? 0 : nNext+1;
/*N*/       } while((*this)[nNext] == rHighest && nNext != nHighest);
/*N*/       const Vector3D &rNext = (*this)[nNext];
/*N*/
/*N*/       // Fehlerfaelle abfangen
/*N*/       if(rHighest == rPrev || rHighest == rNext || rPrev == rNext)
/*N*/           return aNormal;
/*N*/
/*N*/       // Normale bilden
/*N*/       aNormal = (rPrev - rHighest)|(rNext - rHighest);
/*N*/
/*N*/       // get length
/*N*/       double fLen = aNormal.GetLength();
/*N*/
/*N*/       // correct length
/*N*/       if(fabs(fLen) < SMALL_DVALUE)
/*N*/           fLen = 0.0;
/*N*/
/*N*/       if(0.0 != fLen)
/*N*/       {
/*N*/           // use own normalize here since we already know the vector length
/*N*/           // with square root applied
/*N*/           // aNormal.Normalize();
/*N*/           if(1.0 != fLen)
/*N*/           {
/*N*/               // normalize
/*N*/               double fFac = 1.0 / fLen;
/*N*/               aNormal = Vector3D(aNormal.X() * fFac, aNormal.Y() * fFac, aNormal.Z() * fFac);
/*N*/           }
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           // points are on one line, use default normal
/*N*/           aNormal = Vector3D(0.0, 0.0, -1.0);
/*N*/       }
/*N*/   }
/*N*/   return aNormal;
/*N*/ }

/*************************************************************************
|*
|* Mittelpunkt des Polygons (in Bezug auf die Einzelpunkte) berechnen
|*
\************************************************************************/

/*N*/ Vector3D Polygon3D::GetMiddle() const
/*N*/ {
/*N*/   Vector3D aMiddle;
/*N*/   UINT16 nPntCnt = pImpPolygon3D->nPoints;
/*N*/
/*N*/   for(UINT16 i = 0; i < nPntCnt; i++)
/*N*/       aMiddle += pImpPolygon3D->pPointAry[i];
/*N*/
/*N*/   aMiddle /= (double)nPntCnt;
/*N*/
/*N*/   return aMiddle;
/*N*/ }

/*************************************************************************
|*
|* Laufrichtung des Polygons umkehren
|*
\************************************************************************/

/*N*/ void Polygon3D::FlipDirection()
/*N*/ {
/*N*/   pImpPolygon3D->CheckPointDelete();
/*N*/   CheckReference();
/*N*/
/*N*/   UINT16 nPntCnt = pImpPolygon3D->nPoints;
/*N*/   UINT16 nCnt = nPntCnt / 2;
/*N*/   Vector3D* pBeg = pImpPolygon3D->pPointAry;
/*N*/   Vector3D* pEnd = pBeg + nPntCnt - 1;
/*N*/
/*N*/   for(UINT16 i = 0; i < nCnt; i++)
/*N*/   {
/*N*/       Vector3D aTmp = *pBeg;
/*N*/       *pBeg++ = *pEnd;
/*N*/       *pEnd-- = aTmp;
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* Polygonpunkte mit uebergebener Matrix transformieren
|*
\************************************************************************/

/*N*/ void Polygon3D::Transform(const Matrix4D& rTfMatrix)
/*N*/ {
/*N*/   pImpPolygon3D->CheckPointDelete();
/*N*/   CheckReference();
/*N*/
/*N*/   Vector3D* pPoint = pImpPolygon3D->pPointAry;
/*N*/   UINT16 nPntCnt = pImpPolygon3D->nPoints;
/*N*/
/*N*/   for(UINT16 i = 0; i < nPntCnt; i++)
/*N*/       *pPoint++ *= rTfMatrix;
/*N*/ }

/*************************************************************************
|*
|* doppelte aufeinanderfolgende Polygonpunkte entfernen; ein
|* geschlossenes Polygon wird dabei ggf. "geoeffnet"
|*
\************************************************************************/

/*N*/ void Polygon3D::RemoveDoublePoints()
/*N*/ {
/*N*/   pImpPolygon3D->CheckPointDelete();
/*N*/   CheckReference();
/*N*/
/*N*/   UINT16 nPntCnt = pImpPolygon3D->nPoints;
/*N*/
/*N*/   if(nPntCnt)
/*N*/   {
/*N*/       Vector3D* pPoint = pImpPolygon3D->pPointAry;
/*N*/       Vector3D aP0 = *pPoint;
/*N*/
/*N*/       pPoint += nPntCnt;
/*N*/
/*N*/       while(*--pPoint == aP0 && nPntCnt > 3)
/*N*/       {
/*N*/           nPntCnt--;
/*N*/           pImpPolygon3D->bClosed = TRUE;
/*N*/       }
/*N*/
/*N*/       for(UINT16 i = nPntCnt-1; i > 0 && nPntCnt > 3; i--)
/*N*/       {
/*N*/           if(*pPoint == *(pPoint-1))
/*N*/           {
/*N*/               pImpPolygon3D->Remove(i, 1);
/*N*/               nPntCnt--;
/*N*/           }
/*N*/           pPoint--;
/*N*/       }
/*N*/
/*N*/       SetPointCount(nPntCnt);
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       DBG_ASSERT(FALSE, "Empty polygon used!");
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* Ueberlappen sich das aktuelle und das angegebene Polygon ?
|*
\************************************************************************/

//STRIP001 BOOL Polygon3D::DoesBoundVolumeOverlap(const Polygon3D& rOrig, UINT16 nDegreeFlag) const
//STRIP001 {
//STRIP001  Volume3D aVolumeOrig = rOrig.GetPolySize();
//STRIP001  Volume3D aVolumeThis = GetPolySize();
//STRIP001
//STRIP001  BOOL bOverlapX(TRUE);
//STRIP001  if(nDegreeFlag & DEGREE_FLAG_X)
//STRIP001      bOverlapX = BOOL(aVolumeOrig.MinVec().X() < aVolumeThis.MaxVec().X() && aVolumeOrig.MaxVec().X() > aVolumeThis.MinVec().X());
//STRIP001
//STRIP001  BOOL bOverlapY(TRUE);
//STRIP001  if(nDegreeFlag & DEGREE_FLAG_Y)
//STRIP001      bOverlapY = BOOL(aVolumeOrig.MinVec().Y() < aVolumeThis.MaxVec().Y() && aVolumeOrig.MaxVec().Y() > aVolumeThis.MinVec().Y());
//STRIP001
//STRIP001  BOOL bOverlapZ(TRUE);
//STRIP001  if(nDegreeFlag & DEGREE_FLAG_Z)
//STRIP001      bOverlapZ = BOOL(aVolumeOrig.MinVec().Z() < aVolumeThis.MaxVec().Z() && aVolumeOrig.MaxVec().Z() > aVolumeThis.MinVec().Z());
//STRIP001
//STRIP001  return (bOverlapX && bOverlapY && bOverlapZ);
//STRIP001 }

//STRIP001 BOOL Polygon3D::DoesOverlap(const Polygon3D& rOrig, UINT16 nDegreeFlag) const
//STRIP001 {
//STRIP001  BOOL bRetval = DoesBoundVolumeOverlap(rOrig, nDegreeFlag);
//STRIP001
//STRIP001  if(bRetval)
//STRIP001  {
//STRIP001      // Schneiden sich die Polygone auch?
//STRIP001      BOOL bPolyCut = DoesCut(rOrig, nDegreeFlag);
//STRIP001
//STRIP001      // Falls Ueberlappung von Einzelpolygonen
//STRIP001      if(bPolyCut)
//STRIP001      {
//STRIP001          bRetval = TRUE;
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          // Polygone koennen sich noch umschliessen
//STRIP001          if((IsClosed() && IsInside(rOrig[0]))
//STRIP001              || (rOrig.IsClosed() && rOrig.IsInside((*this)[0])))
//STRIP001              bRetval = TRUE;
//STRIP001          else
//STRIP001              bRetval = FALSE;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return bRetval;
//STRIP001 }

/*************************************************************************
|*
|* Existiert ein Schnitt zwischen den Polys?
|*
\************************************************************************/

//STRIP001 BOOL Polygon3D::DoesCut(const Polygon3D& rOrig, UINT16 nDegreeFlag) const
//STRIP001 {
//STRIP001  BOOL bRetval(FALSE);
//STRIP001
//STRIP001  UINT16 nEndLoopA = IsClosed() ? pImpPolygon3D->nPoints : pImpPolygon3D->nPoints - 1;
//STRIP001  for(UINT16 a=0;!bRetval && a < nEndLoopA; a++)
//STRIP001  {
//STRIP001      UINT16 nEndLoopB = rOrig.IsClosed() ? rOrig.GetPointCount() : rOrig.GetPointCount() - 1;
//STRIP001      for(UINT16 b=0;!bRetval && b < nEndLoopB; b++)
//STRIP001      {
//STRIP001          UINT16 nCut = FindCut(a, rOrig, b);
//STRIP001          if(nCut)
//STRIP001              bRetval = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return bRetval;
//STRIP001 }

/*************************************************************************
|*
|* Crossings Test for point and whole polygon
|*
\************************************************************************/

/*N*/ BOOL Polygon3D::IsInside(const Vector3D& rPnt, BOOL bWithBorder) const
/*N*/ {
/*N*/   BOOL bInside(FALSE);
/*N*/   UINT16 nNumPoint(GetPointCount());
/*N*/   Vector3D* pPoints = pImpPolygon3D->pPointAry;
/*N*/
/*N*/   for(UINT16 a=0;a<nNumPoint;a++)
/*N*/   {
/*N*/       if(bWithBorder
/*N*/           && (fabs(pPoints[a].X() - rPnt.X()) < SMALL_DVALUE)
/*N*/           && (fabs(pPoints[a].Y() - rPnt.Y()) < SMALL_DVALUE))
/*N*/           return TRUE;
/*N*/
/*N*/       UINT16 nPrev((!a) ? nNumPoint-1 : a-1);
/*N*/
/*N*/       if((pPoints[nPrev].Y() - rPnt.Y() > -SMALL_DVALUE) != (pPoints[a].Y() - rPnt.Y() > -SMALL_DVALUE))
/*N*/       {
/*N*/           BOOL bXFlagOld(pPoints[nPrev].X() - rPnt.X() > -SMALL_DVALUE);
/*N*/
/*N*/           if(bXFlagOld == (pPoints[a].X() - rPnt.X() > -SMALL_DVALUE))
/*N*/           {
/*N*/               if(bXFlagOld)
/*N*/                   bInside = !bInside;
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               double fCmp =
/*N*/                   pPoints[a].X() - (pPoints[a].Y() - rPnt.Y()) *
/*N*/                   (pPoints[nPrev].X() - pPoints[a].X()) /
/*N*/                   (pPoints[nPrev].Y() - pPoints[a].Y());
/*N*/
/*N*/               if((bWithBorder && fCmp > rPnt.X()) || (!bWithBorder && fCmp - rPnt.X() > -SMALL_DVALUE))
/*N*/                   bInside = !bInside;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return bInside;
/*N*/ }

/*?*/ BOOL Polygon3D::IsInside(const Polygon3D& rPoly, BOOL bWithBorder) const
/*?*/ {
/*?*/   UINT16 nPnt(rPoly.GetPointCount());
/*?*/
/*?*/   for(UINT16 a=0;a<nPnt;a++)
/*?*/       if(!IsInside(rPoly[a], bWithBorder))
/*?*/           return FALSE;
/*?*/
/*?*/   return TRUE;
/*?*/ }

/*************************************************************************
|*
|* XPolygon herausgeben
|*
\************************************************************************/

/*N*/ XPolygon Polygon3D::GetXPolygon() const
/*N*/ {
/*N*/   XPolygon aXPolygon(GetPolygon());
/*N*/   return(aXPolygon);
/*N*/ }

/*************************************************************************
|*
|* FG: Identisch wie oben, das Polygon herausgeben
|*
\************************************************************************/

/*N*/ Polygon Polygon3D::GetPolygon() const
/*N*/ {
/*N*/   BOOL bClosed = IsClosed();
/*N*/   UINT16 nSize = pImpPolygon3D->nPoints;
/*N*/   if(bClosed)
/*N*/       nSize++;
/*N*/   Polygon aPolygon(nSize);
/*N*/   Vector3D* pVec3D = pImpPolygon3D->pPointAry;
/*N*/
/*N*/   if (pVec3D)
/*N*/   {
/*N*/       UINT16 i;
/*N*/       for (i = 0; i < pImpPolygon3D->nPoints; i++)
/*N*/       {
/*N*/           // X und Y uebernehmen, Z vernachlaessigen
/*N*/           aPolygon.SetPoint(Point((long)  pVec3D[i].X(),
/*N*/                                   (long) -pVec3D[i].Y()), i);
/*N*/       }
/*N*/       if(bClosed)
/*N*/           aPolygon.SetPoint(Point((long)  pVec3D[0].X(),
/*N*/                                   (long) -pVec3D[0].Y()), i);
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       for (UINT16 i = 0; i < nSize; i++)
/*N*/       {
/*?*/           aPolygon.SetPoint(Point(), i);
/*N*/       }
/*N*/   }
/*N*/   aPolygon.SetSize(nSize);
/*N*/   return(aPolygon);
/*N*/ }

/*************************************************************************
|*
|* Ausdehnung des Polygons ermitteln
|*
\************************************************************************/

/*N*/ Volume3D Polygon3D::GetPolySize() const
/*N*/ {
/*N*/   Volume3D aRetval;
/*N*/   UINT16 nPntCnt = pImpPolygon3D->nPoints;
/*N*/
/*N*/   aRetval.Reset();
/*N*/   for(UINT16 i = 0; i < nPntCnt; i++)
/*N*/       aRetval.Union((*this)[i]);
/*N*/
/*N*/   return aRetval;
/*N*/ }

/*************************************************************************
|*
|* Flaeche des Polygons ermitteln
|*
\************************************************************************/

//STRIP001 double Polygon3D::GetPolyArea() const
//STRIP001 {
//STRIP001  Vector3D aNormal = GetNormal();
//STRIP001  return GetPolyArea(aNormal);
//STRIP001 }

/*N*/ double Polygon3D::GetPolyArea(const Vector3D& rNormal) const
/*N*/ {
/*N*/   double fRetval = 0.0;
/*N*/   UINT16 nPntCnt = pImpPolygon3D->nPoints;
/*N*/
/*N*/   if(nPntCnt > 2)
/*N*/   {
/*N*/       const Vector3D& rFirst = (*this)[0];
/*N*/       Vector3D aLastVector = (*this)[1] - rFirst;
/*N*/
/*N*/       for (UINT16 i = 2; i < nPntCnt; i++)
/*N*/       {
/*N*/           const Vector3D& rPoint = (*this)[i];
/*N*/           Vector3D aNewVec = rPoint - rFirst;
/*N*/           Vector3D aArea = aLastVector;
/*N*/           aArea |= aNewVec;
/*N*/           fRetval += (rNormal.Scalar(aArea)) / 2.0;
/*N*/       }
/*N*/   }
/*N*/   return fabs(fRetval);
/*N*/ }

/*************************************************************************
|*
|* Schnitt zwischen den von den Punkten angegebenen Kanten ermitteln.
|* Dabei ist der Rueckgabewert != 0.0, wenn der Schnitt innerhalb
|* der Parameterbereiche der Kanten liegt und gibt den Wert ]0.0, 1.0]
|* innerhalb der ersten Kante an.
|*
\************************************************************************/

//STRIP001 UINT16 Polygon3D::FindCut(UINT16 nEdge1, UINT16 nEdge2,
//STRIP001  UINT16 nCutFlags, double* pCut1, double* pCut2) const
//STRIP001 {
//STRIP001  UINT16 nRetval(0);
//STRIP001  UINT16 nPntCnt = pImpPolygon3D->nPoints;
//STRIP001
//STRIP001  if(nEdge1 < nPntCnt && nEdge2 < nPntCnt && nEdge1 != nEdge2)
//STRIP001  {
//STRIP001      UINT16 nEnd1 = (nEdge1 == nPntCnt-1) ? 0 : nEdge1+1;
//STRIP001      UINT16 nEnd2 = (nEdge2 == nPntCnt-1) ? 0 : nEdge2+1;
//STRIP001
//STRIP001      nRetval = FindCut(
//STRIP001          (*this)[nEdge1], (*this)[nEnd1] - (*this)[nEdge1],
//STRIP001          (*this)[nEdge2], (*this)[nEnd2] - (*this)[nEdge2],
//STRIP001          nCutFlags, pCut1, pCut2);
//STRIP001  }
//STRIP001
//STRIP001  return nRetval;
//STRIP001 }

/*************************************************************************
|*
|* Diese Version arbeitet mit der Kante nEdge1 aus dem lokalen
|* Polygon und nEdge2 aus dem uebergebenen
|*
\************************************************************************/

//STRIP001 UINT16 Polygon3D::FindCut(UINT16 nEdge1, const Polygon3D& rPoly3D, UINT16 nEdge2,
//STRIP001  UINT16 nCutFlags, double* pCut1, double* pCut2) const
//STRIP001 {
//STRIP001  UINT16 nRetval(0);
//STRIP001  UINT16 nPntCnt1 = pImpPolygon3D->nPoints;
//STRIP001
//STRIP001  if(nEdge1 < nPntCnt1)
//STRIP001  {
//STRIP001      UINT16 nPntCnt2 = rPoly3D.GetPointCount();
//STRIP001      if(nEdge2 < nPntCnt2)
//STRIP001      {
//STRIP001          UINT16 nEnd1 = (nEdge1 == nPntCnt1-1) ? 0 : nEdge1+1;
//STRIP001          UINT16 nEnd2 = (nEdge2 == nPntCnt2-1) ? 0 : nEdge2+1;
//STRIP001
//STRIP001          nRetval = FindCut(
//STRIP001              (*this)[nEdge1], (*this)[nEnd1] - (*this)[nEdge1],
//STRIP001              rPoly3D[nEdge2], rPoly3D[nEnd2] - rPoly3D[nEdge2],
//STRIP001              nCutFlags, pCut1, pCut2);
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return nRetval;
//STRIP001 }

/*************************************************************************
|*
|* test if point is on line in range ]0.0..1.0[ without
|* the points. If so, return TRUE and put the parameter
|* value in pCut (if provided)
|*
\************************************************************************/

//STRIP001 BOOL Polygon3D::FindPointInLine(
//STRIP001  const Vector3D& rPoint,
//STRIP001  const Vector3D& rEdgeStart,
//STRIP001  const Vector3D& rEdgeDelta,
//STRIP001  double* pCut)
//STRIP001 {
//STRIP001  BOOL bDeltaXIsZero(fabs(rEdgeDelta.X()) < SMALL_DVALUE);
//STRIP001  BOOL bDeltaYIsZero(fabs(rEdgeDelta.Y()) < SMALL_DVALUE);
//STRIP001
//STRIP001  if(bDeltaXIsZero && bDeltaYIsZero)
//STRIP001  {
//STRIP001      return FALSE;
//STRIP001  }
//STRIP001  else if(bDeltaXIsZero)
//STRIP001  {
//STRIP001      if(fabs(rPoint.X() - rEdgeStart.X()) < SMALL_DVALUE)
//STRIP001      {
//STRIP001          double fValue = (rPoint.Y() - rEdgeStart.Y()) / rEdgeDelta.Y();
//STRIP001          if(fValue >= SMALL_DVALUE && fValue <= (1.0 - SMALL_DVALUE))
//STRIP001          {
//STRIP001              if(pCut)
//STRIP001                  *pCut = fValue;
//STRIP001              return TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  else if(bDeltaYIsZero)
//STRIP001  {
//STRIP001      if(fabs(rPoint.Y() - rEdgeStart.Y()) < SMALL_DVALUE)
//STRIP001      {
//STRIP001          double fValue = (rPoint.X() - rEdgeStart.X()) / rEdgeDelta.X();
//STRIP001          if(fValue >= SMALL_DVALUE && fValue <= (1.0 - SMALL_DVALUE))
//STRIP001          {
//STRIP001              if(pCut)
//STRIP001                  *pCut = fValue;
//STRIP001              return TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      double fTOne = (rPoint.X() - rEdgeStart.X()) / rEdgeDelta.X();
//STRIP001      double fTTwo = (rPoint.Y() - rEdgeStart.Y()) / rEdgeDelta.Y();
//STRIP001      if(fabs(fTOne - fTTwo) < SMALL_DVALUE)
//STRIP001      {
//STRIP001          // same representation, point is on line
//STRIP001          double fValue = (fTOne + fTTwo) / 2.0;
//STRIP001          if(fValue >= SMALL_DVALUE && fValue <= (1.0 - SMALL_DVALUE))
//STRIP001          {
//STRIP001              // point is inside line bounds, too
//STRIP001              if(pCut)
//STRIP001                  *pCut = fValue;
//STRIP001              return TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return FALSE;
//STRIP001 }

/*************************************************************************
|*
|* Diese Version nimmt die Startpunkte und Vektoren (relative Angabe
|* des Endpunktes) zweier Kanten
|*
\************************************************************************/

//STRIP001 UINT16 Polygon3D::FindCut(
//STRIP001  const Vector3D& rEdge1Start, const Vector3D& rEdge1Delta,
//STRIP001  const Vector3D& rEdge2Start, const Vector3D& rEdge2Delta,
//STRIP001  UINT16 nCutFlags,
//STRIP001  double* pCut1, double* pCut2)
//STRIP001 {
//STRIP001  UINT16 nRetval(0);
//STRIP001  double fCut1(0.0);
//STRIP001  double fCut2(0.0);
//STRIP001  BOOL bFinished(!((BOOL)(nCutFlags & CUTFLAG_ALL)));
//STRIP001
//STRIP001  // test for same points?
//STRIP001  if(!bFinished
//STRIP001      && (nCutFlags & (CUTFLAG_START1|CUTFLAG_END1))
//STRIP001      && (nCutFlags & (CUTFLAG_START2|CUTFLAG_END2)))
//STRIP001  {
//STRIP001      // same startpoint?
//STRIP001      if(!bFinished
//STRIP001          && ((nCutFlags & (CUTFLAG_START1|CUTFLAG_START2)) == (CUTFLAG_START1|CUTFLAG_START2))
//STRIP001          && (fabs(rEdge1Start.X() - rEdge2Start.X()) < SMALL_DVALUE)
//STRIP001          && (fabs(rEdge1Start.Y() - rEdge2Start.Y()) < SMALL_DVALUE))
//STRIP001      {
//STRIP001          bFinished = TRUE;
//STRIP001          nRetval = (CUTFLAG_START1|CUTFLAG_START2);
//STRIP001      }
//STRIP001
//STRIP001      // same endpoint?
//STRIP001      if(!bFinished
//STRIP001          && ((nCutFlags & (CUTFLAG_END1|CUTFLAG_END2)) == (CUTFLAG_END1|CUTFLAG_END2))
//STRIP001          && (fabs(rEdge1Start.X() + rEdge1Delta.X() - rEdge2Start.X() + rEdge2Delta.X()) < SMALL_DVALUE)
//STRIP001          && (fabs(rEdge1Start.Y() + rEdge1Delta.Y() - rEdge2Start.Y() + rEdge2Delta.Y()) < SMALL_DVALUE))
//STRIP001      {
//STRIP001          bFinished = TRUE;
//STRIP001          nRetval = (CUTFLAG_END1|CUTFLAG_END2);
//STRIP001          fCut1 = fCut2 = 1.0;
//STRIP001      }
//STRIP001
//STRIP001      // startpoint1 == endpoint2?
//STRIP001      if(!bFinished
//STRIP001          && ((nCutFlags & (CUTFLAG_START1|CUTFLAG_END2)) == (CUTFLAG_START1|CUTFLAG_END2))
//STRIP001          && (fabs(rEdge1Start.X() - rEdge2Start.X() + rEdge2Delta.X()) < SMALL_DVALUE)
//STRIP001          && (fabs(rEdge1Start.Y() - rEdge2Start.Y() + rEdge2Delta.Y()) < SMALL_DVALUE))
//STRIP001      {
//STRIP001          bFinished = TRUE;
//STRIP001          nRetval = (CUTFLAG_START1|CUTFLAG_END2);
//STRIP001          fCut1 = 0.0;
//STRIP001          fCut2 = 1.0;
//STRIP001      }
//STRIP001
//STRIP001      // startpoint2 == endpoint1?
//STRIP001      if(!bFinished
//STRIP001          && ((nCutFlags & (CUTFLAG_START2|CUTFLAG_END1)) == (CUTFLAG_START2|CUTFLAG_END1))
//STRIP001          && (fabs(rEdge1Start.X() + rEdge1Delta.X() - rEdge2Start.X()) < SMALL_DVALUE)
//STRIP001          && (fabs(rEdge1Start.Y() + rEdge1Delta.Y() - rEdge2Start.Y()) < SMALL_DVALUE))
//STRIP001      {
//STRIP001          bFinished = TRUE;
//STRIP001          nRetval = (CUTFLAG_START2|CUTFLAG_END1);
//STRIP001          fCut1 = 1.0;
//STRIP001          fCut2 = 0.0;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if(!bFinished
//STRIP001      && (nCutFlags & CUTFLAG_LINE))
//STRIP001  {
//STRIP001      if(!bFinished
//STRIP001          && (nCutFlags & CUTFLAG_START1))
//STRIP001      {
//STRIP001          // start1 on line 2 ?
//STRIP001          if(FindPointInLine(rEdge1Start, rEdge2Start, rEdge2Delta, &fCut2))
//STRIP001          {
//STRIP001              bFinished = TRUE;
//STRIP001              nRetval = (CUTFLAG_LINE|CUTFLAG_START1);
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      if(!bFinished
//STRIP001          && (nCutFlags & CUTFLAG_START2))
//STRIP001      {
//STRIP001          // start2 on line 1 ?
//STRIP001          if(FindPointInLine(rEdge2Start, rEdge1Start, rEdge1Delta, &fCut1))
//STRIP001          {
//STRIP001              bFinished = TRUE;
//STRIP001              nRetval = (CUTFLAG_LINE|CUTFLAG_START2);
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      if(!bFinished
//STRIP001          && (nCutFlags & CUTFLAG_END1))
//STRIP001      {
//STRIP001          // end1 on line 2 ?
//STRIP001          if(FindPointInLine(rEdge1Start + rEdge1Delta, rEdge2Start, rEdge2Delta, &fCut2))
//STRIP001          {
//STRIP001              bFinished = TRUE;
//STRIP001              nRetval = (CUTFLAG_LINE|CUTFLAG_END1);
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      if(!bFinished
//STRIP001          && (nCutFlags & CUTFLAG_END2))
//STRIP001      {
//STRIP001          // end2 on line 1 ?
//STRIP001          if(FindPointInLine(rEdge2Start + rEdge2Delta, rEdge1Start, rEdge1Delta, &fCut1))
//STRIP001          {
//STRIP001              bFinished = TRUE;
//STRIP001              nRetval = (CUTFLAG_LINE|CUTFLAG_END2);
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      if(!bFinished)
//STRIP001      {
//STRIP001          // cut in line1, line2 ?
//STRIP001          fCut1 = (rEdge1Delta.X() * rEdge2Delta.Y()) - (rEdge1Delta.Y() * rEdge2Delta.X());
//STRIP001          if(fabs(fCut1) > SMALL_DVALUE)
//STRIP001          {
//STRIP001              fCut1 = (rEdge2Delta.Y() * (rEdge2Start.X() - rEdge1Start.X())
//STRIP001                  + rEdge2Delta.X() * (rEdge1Start.Y() - rEdge2Start.Y())) / fCut1;
//STRIP001
//STRIP001              // inside parameter range edge1 AND fCut2 ist calcable
//STRIP001              if(fCut1 >= SMALL_DVALUE
//STRIP001                  && fCut1 <= (1.0 - SMALL_DVALUE)
//STRIP001                  && (fabs(rEdge2Delta.X()) > SMALL_DVALUE || fabs(rEdge2Delta.Y()) > SMALL_DVALUE))
//STRIP001              {
//STRIP001                  if(fabs(rEdge2Delta.X()) > fabs(rEdge2Delta.Y()))
//STRIP001                  {
//STRIP001                      fCut2 = (rEdge1Start.X() + fCut1
//STRIP001                          * rEdge1Delta.X() - rEdge2Start.X()) / rEdge2Delta.X();
//STRIP001                  }
//STRIP001                  else
//STRIP001                  {
//STRIP001                      fCut2 = (rEdge1Start.Y() + fCut1
//STRIP001                          * rEdge1Delta.Y() - rEdge2Start.Y()) / rEdge2Delta.Y();
//STRIP001                  }
//STRIP001
//STRIP001                  // inside parameter range edge2, too
//STRIP001                  if(fCut2 >= SMALL_DVALUE && fCut2 <= (1.0 - SMALL_DVALUE))
//STRIP001                  {
//STRIP001                      bFinished = TRUE;
//STRIP001                      nRetval = CUTFLAG_LINE;
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // copy values if wanted
//STRIP001  if(pCut1)
//STRIP001      *pCut1 = fCut1;
//STRIP001  if(pCut2)
//STRIP001      *pCut2 = fCut2;
//STRIP001
//STRIP001  return nRetval;
//STRIP001 }

/*************************************************************************
|*
|* Orientierung im Punkt nIndex liefern
|*
\************************************************************************/

/*N*/ BOOL Polygon3D::GetPointOrientation(UINT16 nIndex) const
/*N*/ {
/*N*/   UINT16 nPntCnt = pImpPolygon3D->nPoints;
/*N*/   BOOL bRetval(TRUE);
/*N*/
/*N*/   if(nIndex < nPntCnt)
/*N*/   {
/*N*/       const Vector3D& rMid = (*this)[nIndex];
/*N*/       const Vector3D& rPre = (*this)[(nIndex == 0) ? nPntCnt-1 : nIndex-1];
/*N*/       const Vector3D& rPos = (*this)[(nIndex == nPntCnt-1) ? 0 : nIndex+1];
/*N*/
/*N*/       Vector3D aNormal = (rPre - rMid)|(rPos - rMid);
/*N*/       bRetval = (aNormal.Z() > 0.0) ? TRUE : FALSE;
/*N*/   }
/*N*/
/*N*/   return bRetval;
/*N*/ }

/*************************************************************************
|*
|* get position on polypos, with clipping to start/end
|*
\************************************************************************/

/*N*/ Vector3D Polygon3D::GetPosition(double fPos) const
/*N*/ {
/*N*/   Vector3D aRetval((*this)[0]);
/*N*/
/*N*/   if(fPos <= 0.0 || pImpPolygon3D->nPoints < 2)
/*N*/       return aRetval;
/*N*/
/*N*/   double fLen = GetLength();
/*N*/
/*N*/   if(fPos >= fLen)
/*N*/   {
/*N*/       aRetval = (*this)[pImpPolygon3D->nPoints - 1];
/*N*/       return aRetval;
/*N*/   }
/*N*/
/*N*/   UINT16 nPos(0);
/*N*/   Vector3D aPart((*this)[0] - (*this)[1]);
/*N*/   double fPartLen = aPart.GetLength();
/*N*/
/*N*/   while(fPos > fPartLen)
/*N*/   {
/*N*/       fPos -= fPartLen;
/*N*/       nPos++;
/*N*/       aPart = Vector3D((*this)[nPos] - (*this)[nPos+1]);
/*N*/       fPartLen = aPart.GetLength();
/*N*/   }
/*N*/
/*N*/   aRetval.CalcInBetween((*this)[nPos], (*this)[nPos+1], fPos / fPartLen);
/*N*/
/*N*/   return aRetval;
/*N*/ }

//////////////////////////////////////////////////////////////////////////////
// create a expanded or compresssed poly with exactly nNum Points
//
/*N*/ Polygon3D Polygon3D::GetExpandedPolygon(sal_uInt32 nNum)
/*N*/ {
/*N*/   if(GetPointCount() && nNum && (sal_uInt32)GetPointCount() != nNum)
/*N*/   {
/*N*/       Polygon3D aDestPoly((sal_uInt16)nNum);
/*N*/
/*N*/       // length of step in dest poly
/*N*/       double fStep = GetLength() / (double)(IsClosed() ? nNum : nNum - 1);
/*N*/
/*N*/       // actual positions for run
/*N*/       double fDestPos = 0.0;
/*N*/       double fSrcPos = 0.0;
/*N*/
/*N*/       // actual indices for run
/*N*/       sal_uInt32 nSrcPos = 0;
/*N*/       sal_uInt32 nSrcPosNext = (nSrcPos+1 == (sal_uInt32)GetPointCount()) ? 0 : nSrcPos + 1;
/*N*/
/*N*/       // length of next source step
/*N*/       double fNextSrcLen = ((*this)[(sal_uInt16)nSrcPos] - (*this)[(sal_uInt16)nSrcPosNext]).GetLength();
/*N*/
/*N*/       for(sal_uInt32 b = 0; b < nNum; b++)
/*N*/       {
/*N*/           // calc fDestPos in source
/*N*/           while(fSrcPos + fNextSrcLen < fDestPos)
/*N*/           {
/*N*/               fSrcPos += fNextSrcLen;
/*N*/               nSrcPos++;
/*N*/               nSrcPosNext = (nSrcPos+1 == (sal_uInt32)GetPointCount()) ? 0 : nSrcPos + 1;
/*N*/               fNextSrcLen = ((*this)[(sal_uInt16)nSrcPos] - (*this)[(sal_uInt16)nSrcPosNext]).GetLength();
/*N*/           }
/*N*/
/*N*/           // fDestPos is between fSrcPos and (fSrcPos + fNextSrcLen)
/*N*/           double fLenA = (fDestPos - fSrcPos) / fNextSrcLen;
/*N*/           Vector3D aOld1 = (*this)[(sal_uInt16)nSrcPos];
/*N*/           Vector3D aOld2 = (*this)[(sal_uInt16)nSrcPosNext];
/*N*/           Vector3D aNewPoint;
/*N*/           aNewPoint.CalcInBetween(aOld1, aOld2, fLenA);
/*N*/
/*N*/           aDestPoly[(sal_uInt16)b] = aNewPoint;
/*N*/
/*N*/           // next step
/*N*/           fDestPos += fStep;
/*N*/       }
/*N*/
/*N*/       if(aDestPoly.GetPointCount() >= 3)
/*N*/           aDestPoly.SetClosed(IsClosed());
/*N*/
/*N*/       return aDestPoly;
/*N*/   }
/*N*/   else
/*N*/       return *this;
/*N*/ }

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+--------------- ImpPolyPolygon3D -------------------------------------+
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/*************************************************************************
|*
|* Copy-Konstruktor
|*
\************************************************************************/

/*N*/ ImpPolyPolygon3D::ImpPolyPolygon3D(const ImpPolyPolygon3D& rImpPolyPoly3D) :
/*N*/   aPoly3DList(rImpPolyPoly3D.aPoly3DList)
/*N*/ {
/*N*/   nRefCount = 1;
/*N*/   // Einzelne Elemente duplizieren
/*N*/   Polygon3D* pPoly3D = aPoly3DList.First();
/*N*/
/*N*/   while ( pPoly3D )
/*N*/   {
/*N*/       aPoly3DList.Replace(new Polygon3D(*(aPoly3DList.GetCurObject())));
/*N*/       pPoly3D = aPoly3DList.Next();
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* Destruktor
|*
\************************************************************************/

/*N*/ ImpPolyPolygon3D::~ImpPolyPolygon3D()
/*N*/ {
/*N*/   Polygon3D* pPoly3D = aPoly3DList.First();
/*N*/
/*N*/   while( pPoly3D )
/*N*/   {
/*N*/       delete pPoly3D;
/*N*/       pPoly3D = aPoly3DList.Next();
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* Gleichheitsoperator
|*
\************************************************************************/

/*N*/ BOOL ImpPolyPolygon3D::operator==(const ImpPolyPolygon3D& rImpPolyPoly3D) const
/*N*/ {
/*N*/   UINT16 nCnt = (UINT16) aPoly3DList.Count();
/*N*/   const Polygon3DList& rCmpList = rImpPolyPoly3D.aPoly3DList;
/*N*/
/*N*/   if ( nCnt != (UINT16) rCmpList.Count() )
/*N*/       return FALSE;
/*N*/
/*N*/   BOOL bEqual = TRUE;
/*N*/
/*N*/   for ( UINT16 i = 0; i < nCnt && bEqual; i++ )
/*N*/       bEqual = ( *aPoly3DList.GetObject(i) == *rCmpList.GetObject(i) );
/*N*/
/*N*/   return bEqual;
/*N*/ }

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+--------------- PolyPolygon3D ----------------------------------------+
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/*************************************************************************
|*
|* Konstruktor
|*
\************************************************************************/

/*N*/ PolyPolygon3D::PolyPolygon3D(UINT16 nInitSize, UINT16 nResize)
/*N*/ {
/*N*/   DBG_CTOR(PolyPolygon3D, NULL);
/*N*/   pImpPolyPolygon3D = new ImpPolyPolygon3D(nInitSize, nResize);
/*N*/ }


/*************************************************************************
|*
|* Konstruktor mit Polygon3D
|*
\************************************************************************/

/*N*/ PolyPolygon3D::PolyPolygon3D(const Polygon3D& rPoly3D)
/*N*/ {
/*N*/   DBG_CTOR(PolyPolygon3D, NULL);
/*N*/   pImpPolyPolygon3D = new ImpPolyPolygon3D;
/*N*/   pImpPolyPolygon3D->aPoly3DList.Insert(new Polygon3D(rPoly3D));
/*N*/ }

/*************************************************************************
|*
|* Konstruktor mit PolyPolygon3D
|*
\************************************************************************/

/*N*/ PolyPolygon3D::PolyPolygon3D(const PolyPolygon3D& rPolyPoly3D)
/*N*/ {
/*N*/   DBG_CTOR(PolyPolygon3D,NULL);
/*N*/   pImpPolyPolygon3D = rPolyPoly3D.pImpPolyPolygon3D;
/*N*/   pImpPolyPolygon3D->nRefCount++;
/*N*/ }

/*************************************************************************
|*
|* Konstruktor mit SV-Polygon
|*
\************************************************************************/

/*?*/ PolyPolygon3D::PolyPolygon3D(const Polygon& rPoly, double fScale)
/*?*/ {
/*?*/   DBG_CTOR(PolyPolygon3D, NULL);
/*?*/   pImpPolyPolygon3D = new ImpPolyPolygon3D;
/*?*/   pImpPolyPolygon3D->aPoly3DList. Insert(new Polygon3D(rPoly, fScale));
/*?*/ }

/*************************************************************************
|*
|* Konstruktor mit SV-PolyPolygon
|*
\************************************************************************/

/*N*/ PolyPolygon3D::PolyPolygon3D(const PolyPolygon& rPolyPoly, double fScale)
/*N*/ {
/*N*/   DBG_CTOR(PolyPolygon3D, NULL);
/*N*/   pImpPolyPolygon3D = new ImpPolyPolygon3D;
/*N*/   UINT16 nCnt = rPolyPoly.Count();
/*N*/
/*N*/   for ( UINT16 i = 0; i < nCnt; i++ )
/*N*/       pImpPolyPolygon3D->aPoly3DList.Insert(
/*N*/           new Polygon3D(rPolyPoly.GetObject(i), fScale), LIST_APPEND);
/*N*/ }

/*************************************************************************
|*
|* Konstruktor mit XPolygon
|*
\************************************************************************/

/*?*/ PolyPolygon3D::PolyPolygon3D(const XPolygon& rXPoly, double fScale)
/*?*/ {
/*?*/   DBG_CTOR(PolyPolygon3D, NULL);
/*?*/   pImpPolyPolygon3D = new ImpPolyPolygon3D;
/*?*/   pImpPolyPolygon3D->aPoly3DList.Insert(new Polygon3D(rXPoly, fScale));
/*?*/ }

/*************************************************************************
|*
|* Konstruktor mit XPolyPolygon
|*
\************************************************************************/

/*N*/ PolyPolygon3D::PolyPolygon3D(const XPolyPolygon& rXPolyPoly, double fScale)
/*N*/ {
/*N*/   DBG_CTOR(PolyPolygon3D, NULL);
/*N*/   pImpPolyPolygon3D = new ImpPolyPolygon3D;
/*N*/   UINT16 nCnt = rXPolyPoly.Count();
/*N*/
/*N*/   for ( UINT16 i = 0; i < nCnt; i++ )
/*N*/       pImpPolyPolygon3D->aPoly3DList.Insert(
/*N*/           new Polygon3D(rXPolyPoly.GetObject(i), fScale), LIST_APPEND);
/*N*/ }

/*************************************************************************
|*
|* Closed-Status der Einzelpolygone korrigieren
|*
\************************************************************************/

//STRIP001 void PolyPolygon3D::CheckClosed()
//STRIP001 {
//STRIP001  for(UINT16 a=0;a<Count();a++)
//STRIP001      (*this)[a].CheckClosed();
//STRIP001 }

/*************************************************************************
|*
|* Destruktor
|*
\************************************************************************/

/*N*/ PolyPolygon3D::~PolyPolygon3D()
/*N*/ {
/*N*/   DBG_DTOR(PolyPolygon3D, NULL);
/*N*/
/*N*/   if( pImpPolyPolygon3D->nRefCount > 1 )  pImpPolyPolygon3D->nRefCount--;
/*N*/   else                                    delete pImpPolyPolygon3D;
/*N*/ }

/*************************************************************************
|*
|* Feststellen, ob ein Punkt innerhalb liegt
|*
\************************************************************************/

//STRIP001 BOOL PolyPolygon3D::IsInside(const Vector3D& rPnt, BOOL bWithBorder) const
//STRIP001 {
//STRIP001  BOOL bInside(FALSE);
//STRIP001
//STRIP001  for(UINT16 a=0;a<Count();a++)
//STRIP001      if((*this)[a].IsInside(rPnt, bWithBorder))
//STRIP001          bInside = !bInside;
//STRIP001  return bInside;
//STRIP001 }

//STRIP001 BOOL PolyPolygon3D::IsInside(const Polygon3D& rPoly, BOOL bWithBorder) const
//STRIP001 {
//STRIP001  BOOL bInside(FALSE);
//STRIP001
//STRIP001  for(UINT16 a=0;a<Count();a++)
//STRIP001      if((*this)[a].IsInside(rPoly, bWithBorder))
//STRIP001          bInside = !bInside;
//STRIP001  return bInside;
//STRIP001 }

/*************************************************************************
|*
|* Scnittpunkt angegebene Linie mit Polygon
|*
\************************************************************************/

//STRIP001 BOOL PolyPolygon3D::GetCutPoint(Vector3D &rCut, const Vector3D &rLeft,
//STRIP001  const Vector3D &rRight) const
//STRIP001 {
//STRIP001  BOOL bCutValid = FALSE;
//STRIP001  const Polygon3D& rPoly3D = (*this)[0];
//STRIP001  UINT16 nPntCnt = rPoly3D.GetPointCount();
//STRIP001  if(nPntCnt > 2)
//STRIP001  {
//STRIP001      // Normale und Skalar der Ebenengleichung ermitteln
//STRIP001      Vector3D aVector = rPoly3D[0] - rPoly3D[1];
//STRIP001      Vector3D aNormal;
//STRIP001      UINT16 a=2;
//STRIP001      do
//STRIP001      {
//STRIP001          const Vector3D &rThree = rPoly3D[a++];
//STRIP001          aNormal = aVector;
//STRIP001          aNormal |= rThree - rPoly3D[1];
//STRIP001          aNormal.Normalize();
//STRIP001      } while(a < nPntCnt && aNormal.GetLength() < 0.000000001);
//STRIP001      double fScalar = -(rPoly3D[1].Scalar(aNormal));
//STRIP001
//STRIP001      Vector3D aLineVec = rLeft - rRight;
//STRIP001      double fZwi = aNormal.Scalar(aLineVec);
//STRIP001
//STRIP001      if(fabs(fZwi) > 0.000000001)
//STRIP001      {
//STRIP001          fZwi = (-fScalar - (rRight.Scalar(aNormal))) / fZwi;
//STRIP001          if(fZwi > 0.000000001 && fZwi < 1.0 - 0.000000001)
//STRIP001          {
//STRIP001              rCut.X() = rRight.X() + (aLineVec.X() * fZwi);
//STRIP001              rCut.Y() = rRight.Y() + (aLineVec.Y() * fZwi);
//STRIP001              rCut.Z() = rRight.Z() + (aLineVec.Z() * fZwi);
//STRIP001
//STRIP001              bCutValid = TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return bCutValid;
//STRIP001 }

/*************************************************************************
|*
|* Referenzzaehler pruefen und ggf. neuen Container erzeugen
|*
\************************************************************************/

/*N*/ void PolyPolygon3D::CheckReference()
/*N*/ {
/*N*/   if( pImpPolyPolygon3D->nRefCount > 1 )
/*N*/   {
/*N*/       pImpPolyPolygon3D->nRefCount--;
/*N*/       pImpPolyPolygon3D = new ImpPolyPolygon3D(*pImpPolyPolygon3D);
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* Polygon in die Liste einfuegen
|*
\************************************************************************/

/*N*/ void PolyPolygon3D::Insert(const Polygon3D& rPoly3D, UINT16 nPos)
/*N*/ {
/*N*/   CheckReference();
/*N*/   pImpPolyPolygon3D->aPoly3DList.Insert(new Polygon3D(rPoly3D), nPos);
/*N*/ }

/*************************************************************************
|*
|* PolyPolygon in die Liste einfuegen
|*
\************************************************************************/

/*N*/ void PolyPolygon3D::Insert(const PolyPolygon3D& rPolyPoly3D, UINT16 nPos)
/*N*/ {
/*N*/   CheckReference();
/*N*/   UINT16 nCnt = rPolyPoly3D.Count();
/*N*/
/*N*/   for ( UINT16 i = 0; i < nCnt; i++)
/*N*/   {
/*N*/       Polygon3D* pPoly3D = new Polygon3D(rPolyPoly3D[i]);
/*N*/       pImpPolyPolygon3D->aPoly3DList. Insert(pPoly3D, nPos);
/*N*/
/*N*/       if ( nPos != POLYPOLY3D_APPEND )
/*N*/           nPos++;
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* Polygon aus der Liste entfernen
|*
\************************************************************************/

//STRIP001 Polygon3D PolyPolygon3D::Remove(UINT16 nPos)
//STRIP001 {
//STRIP001  CheckReference();
//STRIP001  Polygon3D* pTmpPoly3D = pImpPolyPolygon3D->aPoly3DList.Remove(nPos);
//STRIP001  Polygon3D aPoly3D(*pTmpPoly3D);
//STRIP001  delete pTmpPoly3D;
//STRIP001  return aPoly3D;
//STRIP001 }


/*************************************************************************
|*
|* Polygon in der Liste ersetzen
|*
\************************************************************************/

//STRIP001 Polygon3D PolyPolygon3D::Replace(const Polygon3D& rPoly3D, UINT16 nPos)
//STRIP001 {
//STRIP001  CheckReference();
//STRIP001  Polygon3D* pPoly3D = new Polygon3D(rPoly3D);
//STRIP001  Polygon3D* pTmpPoly3D = pImpPolyPolygon3D->aPoly3DList.Replace(pPoly3D, nPos);
//STRIP001  Polygon3D  aPoly3D(*pTmpPoly3D);
//STRIP001  delete pTmpPoly3D;
//STRIP001  return aPoly3D;
//STRIP001 }

/*************************************************************************
|*
|* Referenz auf Polygon zurueckgeben, ggf. neues Polygon einfuegen
|*
\************************************************************************/

/*N*/ const Polygon3D& PolyPolygon3D::GetObject(UINT16 nPos) const
/*N*/ {
/*N*/   Polygon3D* pPoly3D = pImpPolyPolygon3D->aPoly3DList.GetObject(nPos);
/*N*/
/*N*/   if ( pPoly3D == NULL )
/*N*/   {   // Wenn noch kein Polygon an der Position vorhanden, neu erzeugen
/*N*/       pPoly3D = new Polygon3D;
/*N*/       pImpPolyPolygon3D->aPoly3DList.Insert(pPoly3D, nPos);
/*N*/   }
/*N*/   return *pPoly3D;
/*N*/ }

/*************************************************************************
|*
|* Liste loeschen
|*
\************************************************************************/

/*N*/ void PolyPolygon3D::Clear()
/*N*/ {
/*N*/   if ( pImpPolyPolygon3D->nRefCount > 1 )
/*N*/   {
/*?*/       pImpPolyPolygon3D->nRefCount--;
/*?*/       pImpPolyPolygon3D = new ImpPolyPolygon3D();
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       Polygon3D* pPoly3D = pImpPolyPolygon3D->aPoly3DList.First();
/*N*/
/*N*/       while( pPoly3D )
/*N*/       {
/*N*/           delete pPoly3D;
/*N*/           pPoly3D = pImpPolyPolygon3D->aPoly3DList.Next();
/*N*/       }
/*N*/       pImpPolyPolygon3D->aPoly3DList.Clear();
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* Anzahl der Polygone zurueckgeben
|*
\************************************************************************/

/*N*/ UINT16 PolyPolygon3D::Count() const
/*N*/ {
/*N*/   return (UINT16)(pImpPolyPolygon3D->aPoly3DList.Count());
/*N*/ }

/*************************************************************************
|*
|* Arrayoperator
|*
\************************************************************************/

/*N*/ Polygon3D& PolyPolygon3D::operator[](UINT16 nPos)
/*N*/ {
/*N*/   CheckReference();
/*N*/   Polygon3D* pPoly3D = pImpPolyPolygon3D->aPoly3DList.GetObject(nPos);
/*N*/
/*N*/   if ( pPoly3D == NULL )
/*N*/   {   // Wenn noch kein Polygon an der Position vorhanden, neu erzeugen
/*N*/       pPoly3D = new Polygon3D;
/*N*/       pImpPolyPolygon3D->aPoly3DList.Insert(pPoly3D, nPos);
/*N*/   }
/*N*/   return *pPoly3D;
/*N*/ }

/*************************************************************************
|*
|* Zuweisungsoperator
|*
\************************************************************************/

/*N*/ PolyPolygon3D& PolyPolygon3D::operator=(const PolyPolygon3D& rPolyPoly3D)
/*N*/ {
/*N*/   rPolyPoly3D.pImpPolyPolygon3D->nRefCount++;
/*N*/
/*N*/   if( pImpPolyPolygon3D->nRefCount > 1 )  pImpPolyPolygon3D->nRefCount--;
/*N*/   else                                    delete pImpPolyPolygon3D;
/*N*/
/*N*/   pImpPolyPolygon3D = rPolyPoly3D.pImpPolyPolygon3D;
/*N*/   return *this;
/*N*/ }

/*************************************************************************
|*
|* Gleichheitsoperator
|*
\************************************************************************/

//STRIP001 BOOL PolyPolygon3D::operator==(const PolyPolygon3D& rPolyPoly3D) const
//STRIP001 {
//STRIP001  if ( pImpPolyPolygon3D == rPolyPoly3D.pImpPolyPolygon3D )
//STRIP001      return TRUE;
//STRIP001  else
//STRIP001      return *pImpPolyPolygon3D == *rPolyPoly3D.pImpPolyPolygon3D;
//STRIP001 }

/*************************************************************************
|*
|* Ungleichheitsoperator
|*
\************************************************************************/

/*N*/ BOOL PolyPolygon3D::operator!=(const PolyPolygon3D& rPolyPoly3D) const
/*N*/ {
/*N*/   if ( pImpPolyPolygon3D == rPolyPoly3D.pImpPolyPolygon3D )
/*N*/       return FALSE;
/*N*/   else
/*N*/       return *pImpPolyPolygon3D != *rPolyPoly3D.pImpPolyPolygon3D;
/*N*/ }

/*************************************************************************
|*
|* alle Polygone mit uebergebener Matrix transformieren
|*
\************************************************************************/

/*N*/ void PolyPolygon3D::Transform(const Matrix4D& rTfMatrix)
/*N*/ {
/*N*/   CheckReference();
/*N*/   UINT16 nCnt = Count();
/*N*/
/*N*/   for ( UINT16 i = 0; i < nCnt; i++ )
/*N*/       pImpPolyPolygon3D->aPoly3DList.GetObject(i)->Transform(rTfMatrix);
/*N*/ }

/*************************************************************************
|*
|* Die Umlaufrichtungen ineinanderliegender Polygone so anpassen, dass
|* sie wechseln; Ausserdem wird ggf. das Polygon mit der geometrisch
|* betrachtet aeussersten Kontur an den Anfang der Liste verschoben
|* werden, damit Normalenberechnungen immer anhand des ersten Polygons
|* ausgefuehrt werden koennen.
|*
\************************************************************************/

/*N*/ void PolyPolygon3D::SetDirections(const Vector3D& rNormal)
/*N*/ {
/*N*/   CheckReference();
/*N*/
/*N*/   UINT16  nCnt = Count();
/*N*/   UINT16  nPoly;
/*N*/   short   nFirstPoly = -1;
/*N*/
/*N*/   if(nCnt)
/*N*/   {
/*N*/       for ( nPoly = 0; nPoly < nCnt; nPoly++ )
/*N*/       {
/*N*/           Polygon3D& rPoly3D = *pImpPolyPolygon3D->aPoly3DList.GetObject(nPoly);
/*N*/           BOOL bFlip = !rPoly3D.IsClockwise(rNormal);
/*N*/           short nDepth = 0;
/*N*/           const Vector3D& rPos = rPoly3D[0];
/*N*/
/*N*/           // bestimmen, wie tief das aktuelle Polygon in den anderen
/*N*/           // verschachtelt ist
/*N*/           for ( UINT16 i = 0; i < nCnt; i++ )
/*N*/           {
/*N*/               if ( i != nPoly &&
/*N*/                    pImpPolyPolygon3D->aPoly3DList.GetObject(i)->IsInside(rPos) )
/*N*/                       nDepth++;
/*N*/           }
/*N*/           // ungerade nDepth-Werte bedeuten: das  Polygon ist ein "Loch"
/*N*/           // in der aeusseren Kontur
/*N*/           BOOL bHole = ((nDepth & 0x0001) == 1);
/*N*/
/*N*/           if ( (bFlip && !bHole) || (!bFlip && bHole) )
/*N*/               rPoly3D.FlipDirection();
/*N*/
/*N*/           // Den Index des (geometrisch) aeussersten Polygons merken
/*N*/           if ( nDepth == 0 && nFirstPoly == -1 )
/*N*/               nFirstPoly = (short) nPoly;
/*N*/       }
/*N*/       // liegt das aeussere Polygon nicht am Anfang, wird es dahin verschoben
/*N*/       if ( nFirstPoly > 0 )
/*N*/       {
/*N*/           Polygon3D* pOuter = pImpPolyPolygon3D->aPoly3DList.Remove(nFirstPoly);
/*N*/           pImpPolyPolygon3D->aPoly3DList.Insert(pOuter, (ULONG) 0);
/*N*/       }
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* in allen Polygonen doppelte aufeinanderfolgende Polygonpunkte
|* entfernen; ein geschlossenes Polygon wird dabei ggf. "geoeffnet"
|*
\************************************************************************/

/*N*/ void PolyPolygon3D::RemoveDoublePoints()
/*N*/ {
/*N*/   CheckReference();
/*N*/   UINT16 nCnt = Count();
/*N*/
/*N*/   for ( UINT16 i = 0; i < nCnt; i++ )
/*N*/       pImpPolyPolygon3D->aPoly3DList.GetObject(i)->RemoveDoublePoints();
/*N*/ }

/*************************************************************************
|*
|* Ein mittels GrowPoly() geschrumpftes PolyPolygon in eventuell
|* entstandenen Selbstueberschneidungen in Eckpunkten ohne
|* Punktreduzierung korrigieren
|*
\************************************************************************/

/*N*/ void PolyPolygon3D::CorrectGrownPoly(const PolyPolygon3D& rPolyOrig)
/*N*/ {
/*N*/   if(Count() == rPolyOrig.Count())
/*N*/   {
/*N*/       for(UINT16 a=0;a<Count();a++)
/*N*/       {
/*N*/           const Polygon3D& rOrig = rPolyOrig[a];
/*N*/           Polygon3D& rPoly = (*this)[a];
/*N*/           UINT16 nPntCnt = rOrig.GetPointCount();
/*N*/
/*N*/           if(nPntCnt == rPoly.GetPointCount() && nPntCnt > 2)
/*N*/           {
/*N*/               UINT16 nNumDiff(0);
/*N*/               UINT16 nDoneStart(0xffff);
/*N*/
/*N*/               // Testen auf Anzahl Aenderungen
/*N*/               UINT16 b;
/*N*/               for(b=0;b<nPntCnt;b++)
/*N*/               {
/*N*/                   if(rOrig.GetPointOrientation(b) != rPoly.GetPointOrientation(b))
/*N*/                   {
/*N*/                       nNumDiff++;
/*N*/                   }
/*N*/                   else
/*N*/                   {
/*N*/                       if(nDoneStart == 0xffff)
/*N*/                       {
/*N*/                           // eventuellen Startpunkt auf gleiche Orientierung legen
/*N*/                           nDoneStart = b;
/*N*/                       }
/*N*/                   }
/*N*/               }
/*N*/
/*N*/               if(nNumDiff == nPntCnt)
/*N*/               {
/*N*/                   // Komplett umgedreht, alles auf einen Punkt
/*N*/                   Vector3D aMiddle = rPoly.GetMiddle();
/*N*/
/*N*/                   for(b=0;b<nPntCnt;b++)
/*N*/                   {
/*N*/                       rPoly[b] = aMiddle;
/*N*/                   }
/*N*/               }
/*N*/               else if(nNumDiff)
/*N*/               {
/*N*/                   // es gibt welche, nDoneStart ist gesetzt. Erzeuge (und
/*N*/                   // setze) nDoneEnd
/*N*/                   UINT16 nDoneEnd(nDoneStart);
/*N*/                   UINT16 nStartLoop;
/*N*/                   BOOL bInLoop(FALSE);
/*N*/
/*N*/                   // einen step mehr in der Schleife, um Loops abzuschliessen
/*N*/                   BOOL bFirstStep(TRUE);
/*N*/
/*N*/                   while(nDoneEnd != nDoneStart || bFirstStep)
/*N*/                   {
/*N*/                       bFirstStep = FALSE;
/*N*/
/*N*/                       // nCandidate ist Kandidat fuer Test
/*N*/                       UINT16 nCandidate = (nDoneEnd == nPntCnt-1) ? 0 : nDoneEnd+1;
/*N*/
/*N*/                       if(rOrig.GetPointOrientation(nCandidate) == rPoly.GetPointOrientation(nCandidate))
/*N*/                       {
/*N*/                           // Orientierung ist gleich
/*N*/                           if(bInLoop)
/*N*/                           {
/*N*/                               // Punkte innerhalb bInLoop auf ihr Zentrum setzen
/*N*/                               Vector3D aMiddle;
/*N*/                               UINT16 nCounter(0);
/*N*/                               UINT16 nStart(nStartLoop);
/*N*/
/*N*/                               while(nStart != nCandidate)
/*N*/                               {
/*N*/                                   aMiddle += rPoly[nStart];
/*N*/                                   nCounter++;
/*N*/                                   nStart = (nStart == nPntCnt-1) ? 0 : nStart+1;
/*N*/                               }
/*N*/
/*N*/                               // Mittelwert bilden
/*N*/                               aMiddle /= (double)nCounter;
/*N*/
/*N*/                               // Punkte umsetzen
/*N*/                               nStart = nStartLoop;
/*N*/                               while(nStart != nCandidate)
/*N*/                               {
/*N*/                                   rPoly[nStart] = aMiddle;
/*N*/                                   nStart = (nStart == nPntCnt-1) ? 0 : nStart+1;
/*N*/                               }
/*N*/
/*N*/                               // Loop beenden
/*N*/                               bInLoop = FALSE;
/*N*/                           }
/*N*/                       }
/*N*/                       else
/*N*/                       {
/*N*/                           // Orientierung unterschiedlich
/*N*/                           if(!bInLoop)
/*N*/                           {
/*N*/                               // Start eines Loop mit geaenderter Orientierung
/*N*/                               nStartLoop = nCandidate;
/*N*/                               bInLoop = TRUE;
/*N*/                           }
/*N*/                       }
/*N*/
/*N*/                       // Weitergehen
/*N*/                       nDoneEnd = nCandidate;
/*N*/                   }
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* Ueberlappen sich das aktuelle und das angegebene PolyPolygon (in X/Y) ?
|*
\************************************************************************/

//STRIP001 BOOL PolyPolygon3D::DoesBoundVolumeOverlap(const PolyPolygon3D& rOrig, UINT16 nDegreeFlag) const
//STRIP001 {
//STRIP001  Volume3D aVolumeOrig = rOrig.GetPolySize();
//STRIP001  Volume3D aVolumeThis = GetPolySize();
//STRIP001
//STRIP001  BOOL bOverlapX(TRUE);
//STRIP001  if(nDegreeFlag & DEGREE_FLAG_X)
//STRIP001      bOverlapX = BOOL(aVolumeOrig.MinVec().X() < aVolumeThis.MaxVec().X() && aVolumeOrig.MaxVec().X() > aVolumeThis.MinVec().X());
//STRIP001
//STRIP001  BOOL bOverlapY(TRUE);
//STRIP001  if(nDegreeFlag & DEGREE_FLAG_Y)
//STRIP001      bOverlapY = BOOL(aVolumeOrig.MinVec().Y() < aVolumeThis.MaxVec().Y() && aVolumeOrig.MaxVec().Y() > aVolumeThis.MinVec().Y());
//STRIP001
//STRIP001  BOOL bOverlapZ(TRUE);
//STRIP001  if(nDegreeFlag & DEGREE_FLAG_Z)
//STRIP001      bOverlapZ = BOOL(aVolumeOrig.MinVec().Z() < aVolumeThis.MaxVec().Z() && aVolumeOrig.MaxVec().Z() > aVolumeThis.MinVec().Z());
//STRIP001
//STRIP001  return (bOverlapX && bOverlapY && bOverlapZ);
//STRIP001 }

//STRIP001 BOOL PolyPolygon3D::DoesOverlap(const PolyPolygon3D& rOrig, UINT16 nDegreeFlag) const
//STRIP001 {
//STRIP001  BOOL bRetval = DoesBoundVolumeOverlap(rOrig, nDegreeFlag);
//STRIP001
//STRIP001  if(bRetval)
//STRIP001  {
//STRIP001      // ueberlappen auch einzelen Polygone?
//STRIP001      BOOL bSinglePolyOverlap(FALSE);
//STRIP001
//STRIP001      for(UINT16 a=0;!bSinglePolyOverlap && a<Count();a++)
//STRIP001      {
//STRIP001          const Polygon3D& rPoly = (*this)[a];
//STRIP001
//STRIP001          for(UINT16 b=0;!bSinglePolyOverlap && b<rOrig.Count();b++)
//STRIP001          {
//STRIP001              const Polygon3D& rOrigPoly = rOrig[b];
//STRIP001
//STRIP001              bSinglePolyOverlap = rPoly.DoesOverlap(rOrigPoly, nDegreeFlag);
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      // Falls keine Ueberlappung von Einzelpolygonen
//STRIP001      if(!bSinglePolyOverlap)
//STRIP001          bRetval = FALSE;
//STRIP001  }
//STRIP001
//STRIP001  return bRetval;
//STRIP001 }

/*************************************************************************
|*
|* Remove all completely overlapping polygons
|*
\************************************************************************/

//STRIP001 UINT16 PolyPolygon3D::RemoveContainedPolygons(BOOL bRemoveHoles, BOOL bWithBorder)
//STRIP001 {
//STRIP001  UINT16 nRetval(0);
//STRIP001  UINT16 nCount(Count());
//STRIP001
//STRIP001  if(nCount > 1)
//STRIP001  {
//STRIP001      for(UINT16 a=0;a+1<nCount;)
//STRIP001      {
//STRIP001          BOOL bIncA(TRUE);
//STRIP001
//STRIP001          for(UINT16 b=a+1;b<nCount;)
//STRIP001          {
//STRIP001              BOOL bIncB(TRUE);
//STRIP001
//STRIP001              if(GetObject(b).IsInside(GetObject(a), bWithBorder)
//STRIP001                  && (bRemoveHoles || GetObject(a).IsClockwise()))
//STRIP001              {
//STRIP001                  // remove a
//STRIP001                  Remove(a);
//STRIP001                  nRetval++;
//STRIP001                  nCount--;
//STRIP001                  bIncA = FALSE;
//STRIP001                  bIncB = FALSE;
//STRIP001                  b = nCount;
//STRIP001              }
//STRIP001              else if(GetObject(a).IsInside(GetObject(b), bWithBorder)
//STRIP001                  && (bRemoveHoles || GetObject(b).IsClockwise()))
//STRIP001              {
//STRIP001                  // remove b
//STRIP001                  Remove(b);
//STRIP001                  nRetval++;
//STRIP001                  nCount--;
//STRIP001                  bIncB = FALSE;
//STRIP001              }
//STRIP001
//STRIP001              if(bIncB)
//STRIP001                  b++;
//STRIP001          }
//STRIP001
//STRIP001          if(bIncA)
//STRIP001              a++;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return nRetval;
//STRIP001 }

/*************************************************************************
|*
|* aus Stream laden
|*
\************************************************************************/

/*N*/ SvStream& operator>>(SvStream& rIStream, PolyPolygon3D& rPolyPoly3D)
/*N*/ {
/*N*/   DBG_CHKOBJ(&rPolyPoly3D, PolyPolygon3D, NULL);
/*N*/
/*N*/   Polygon3D* pPoly3D;
/*N*/
/*N*/   // Anzahl der Polygone einlesen
/*N*/   UINT16 nPolyCount;
/*N*/   rIStream >> nPolyCount;
/*N*/
/*N*/   BOOL bTruncated = FALSE;
/*N*/   // Gesamtanzahl der Punkte mitzaehlen
/*N*/   ULONG nAllPointCount = 0;
/*N*/
/*N*/   if ( rPolyPoly3D.pImpPolyPolygon3D->nRefCount > 1 )
/*?*/       rPolyPoly3D.pImpPolyPolygon3D->nRefCount--;
/*N*/   else
/*N*/       delete rPolyPoly3D.pImpPolyPolygon3D;
/*N*/
/*N*/   rPolyPoly3D.pImpPolyPolygon3D = new ImpPolyPolygon3D(nPolyCount);
/*N*/
/*N*/   while ( nPolyCount > 0 )
/*N*/   {
/*N*/       pPoly3D = new Polygon3D;
/*N*/       rIStream >> *pPoly3D;
/*N*/       nAllPointCount += pPoly3D->GetPointCount();
/*N*/
/*N*/       if ( !bTruncated )
/*N*/       {
/*N*/           if ( nAllPointCount > POLY3D_MAXPOINTS )
/*N*/           {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/                UINT16 nDel = (UINT16)(nAllPointCount - POLY3D_MAXPOINTS);
//STRIP001 /*?*/                UINT16 nPos = pPoly3D->GetPointCount() - nDel;
//STRIP001 /*?*/                pPoly3D->Remove(nPos, nDel);
//STRIP001 /*?*/                // alle nachfolgenden Polygone ignorieren
//STRIP001 /*?*/                bTruncated = TRUE;
/*N*/           }
/*N*/           rPolyPoly3D.pImpPolyPolygon3D->aPoly3DList.Insert(pPoly3D, LIST_APPEND);
/*N*/       }
/*N*/       else
/*?*/           delete pPoly3D;
/*N*/
/*N*/       nPolyCount--;
/*N*/   }
/*N*/
/*N*/   return rIStream;
/*N*/ }

/*************************************************************************
|*
|* in Stream speichern
|*
\************************************************************************/

/*N*/ SvStream& operator<<(SvStream& rOStream, const PolyPolygon3D& rPolyPoly3D)
/*N*/ {
/*N*/   DBG_CHKOBJ(&rPolyPoly3D, PolyPolygon3D, NULL);
/*N*/
/*N*/   // Anzahl der Polygone rausschreiben
/*N*/   rOStream << rPolyPoly3D.Count();
/*N*/
/*N*/   // Die einzelnen Polygone ausgeben
/*N*/   Polygon3D* pPoly3D = rPolyPoly3D.pImpPolyPolygon3D->aPoly3DList.First();
/*N*/
/*N*/   while( pPoly3D )
/*N*/   {
/*N*/       rOStream << *pPoly3D;
/*N*/       pPoly3D = rPolyPoly3D.pImpPolyPolygon3D->aPoly3DList.Next();
/*N*/   }
/*N*/
/*N*/   return rOStream;
/*N*/ }

/*?*/ BOOL PolyPolygon3D::IsClockwise(UINT16 nInd) const
/*?*/ {
/*?*/   if(pImpPolyPolygon3D->aPoly3DList.Count() > nInd)
/*?*/   {
/*?*/       Vector3D aNormal = (*this)[0].GetNormal();
/*?*/       return (*this)[nInd].IsClockwise(aNormal);
/*?*/   }
/*?*/   return FALSE;
/*?*/ }

/*N*/ Vector3D PolyPolygon3D::GetNormal() const
/*N*/ {
/*N*/   if(pImpPolyPolygon3D->aPoly3DList.Count())
/*N*/       return (*this)[0].GetNormal();
/*N*/   return Vector3D(0.0, 0.0, -1.0);
/*N*/ }

/*************************************************************************
|*
|* die Umlaufrichtung des ersten Polygons umkehren
|*
\************************************************************************/

/*?*/ void PolyPolygon3D::FlipDirection(UINT16 nInd)
/*?*/ {
/*?*/   CheckReference();
/*?*/   if(pImpPolyPolygon3D->aPoly3DList.Count() > nInd)
/*?*/       pImpPolyPolygon3D->aPoly3DList.GetObject(nInd)->FlipDirection();
/*?*/ }

/*N*/ void PolyPolygon3D::FlipDirections()
/*N*/ {
/*N*/   CheckReference();
/*N*/   UINT16 nCnt = Count();
/*N*/
/*N*/   for ( UINT16 i = 0; i < nCnt; i++ )
/*N*/       pImpPolyPolygon3D->aPoly3DList.GetObject(i)->FlipDirection();
/*N*/ }

/*N*/ Vector3D PolyPolygon3D::GetMiddle() const
/*N*/ {
/*N*/   if(pImpPolyPolygon3D->aPoly3DList.Count())
/*N*/       return (*this)[0].GetMiddle();
/*N*/   return Vector3D();
/*N*/ }

/*N*/ BOOL PolyPolygon3D::IsClosed() const
/*N*/ {
/*N*/   BOOL bClosed = TRUE;
/*N*/   UINT16 nCnt = Count();
/*N*/
/*N*/   for ( UINT16 i = 0; i < nCnt; i++ )
/*N*/       if(!pImpPolyPolygon3D->aPoly3DList.GetObject(i)->IsClosed())
/*N*/           bClosed = FALSE;
/*N*/   return bClosed;
/*N*/ }

/*************************************************************************
|*
|* XPolyPolygon herausgeben
|*
\************************************************************************/

/*?*/ XPolyPolygon PolyPolygon3D::GetXPolyPolygon() const
/*?*/ {
/*?*/   XPolyPolygon aXPolyPolygon;
/*?*/   UINT16 nCnt = Count();
/*?*/
/*?*/   for ( UINT16 i = 0; i < nCnt; i++ )
/*?*/       aXPolyPolygon.Insert((*this)[i].GetXPolygon());
/*?*/
/*?*/   return(aXPolyPolygon);
/*?*/ }

/*************************************************************************
|*
|* export PolyPolygon
|*
\************************************************************************/

/*N*/ PolyPolygon PolyPolygon3D::GetPolyPolygon() const
/*N*/ {
/*N*/   PolyPolygon aPolyPolygon;
/*N*/   UINT16 nCnt = Count();
/*N*/
/*N*/   for(UINT16 i=0; i<nCnt;i++)
/*N*/       aPolyPolygon.Insert((*this)[i].GetPolygon());
/*N*/
/*N*/   return(aPolyPolygon);
/*N*/ }

/*************************************************************************
|*
|* Ausdehnung ermitteln
|*
\************************************************************************/

/*N*/ Volume3D PolyPolygon3D::GetPolySize() const
/*N*/ {
/*N*/   UINT16 nCnt = Count();
/*N*/   Volume3D aRetval;
/*N*/   Volume3D aSubVolume;
/*N*/
/*N*/   aRetval.Reset();
/*N*/   for ( UINT16 i = 0; i < nCnt; i++ )
/*N*/   {
/*N*/       aSubVolume = (*this)[i].GetPolySize();
/*N*/       aRetval.Union(aSubVolume);
/*N*/   }
/*N*/
/*N*/   return aRetval;
/*N*/ }

/*************************************************************************
|*
|* Flaeche des Polygons ermitteln
|*
\************************************************************************/

/*N*/ double PolyPolygon3D::GetPolyArea() const
/*N*/ {
/*N*/   UINT16 nCnt = Count();
/*N*/   double fRetval = 0.0;
/*N*/
/*N*/   // Einzelflaechen aufsummieren
/*N*/   Vector3D aNormal = GetNormal();
/*N*/   for ( UINT16 i = 0; i < nCnt; i++ )
/*N*/   {
/*N*/       if((*this)[i].IsClockwise(aNormal))
/*N*/       {
/*N*/           fRetval += (*this)[i].GetPolyArea(aNormal);
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           fRetval -= (*this)[i].GetPolyArea(aNormal);
/*N*/       }
/*N*/   }
/*N*/   return fabs(fRetval);
/*N*/ }

/*************************************************************************
|*
|* Laenge des Polygons ermitteln
|*
\************************************************************************/

/*N*/ double PolyPolygon3D::GetLength() const
/*N*/ {
/*N*/   UINT16 nCnt = Count();
/*N*/   double fRetval = 0.0;
/*N*/
/*N*/   for ( UINT16 i = 0; i < nCnt; i++ )
/*N*/       fRetval += (*this)[i].GetLength();
/*N*/
/*N*/   return fRetval;
/*N*/ }

/*************************************************************************
|*
|* Umschliessenden Kugelradius feststellen
|*
\************************************************************************/

/*?*/ double PolyPolygon3D::GetEnclosingRadius() const
/*?*/ {
/*?*/   Volume3D aSize = GetPolySize();
/*?*/   double fBiggestDistance = 0.0;
/*?*/   if(aSize.MinVec().X() != DBL_MAX && aSize.MaxVec().X() != DBL_MIN)
/*?*/       if(aSize.MaxVec().X() - aSize.MinVec().X() > fBiggestDistance)
/*?*/           fBiggestDistance = aSize.MaxVec().X() - aSize.MinVec().X();
/*?*/   if(aSize.MinVec().Y() != DBL_MAX && aSize.MaxVec().Y() != DBL_MIN)
/*?*/       if(aSize.MaxVec().Y() - aSize.MinVec().Y() > fBiggestDistance)
/*?*/           fBiggestDistance = aSize.MaxVec().Y() - aSize.MinVec().Y();
/*?*/   if(aSize.MinVec().Z() != DBL_MAX && aSize.MaxVec().Z() != DBL_MIN)
/*?*/       if(aSize.MaxVec().Z() - aSize.MinVec().Z() > fBiggestDistance)
/*?*/           fBiggestDistance = aSize.MaxVec().Z() - aSize.MinVec().Z();
/*?*/   return (fBiggestDistance / 2.0);
/*?*/ }

///////////////////////////////////////////////////////////////////////////////

//STRIP001 class ImpPolyNode
//STRIP001 {
//STRIP001  Vector3D                    maPosition;
//STRIP001  ImpPolyNode*                mpPrev;
//STRIP001  ImpPolyNode*                mpNext;
//STRIP001
//STRIP001  ImpPolyNode*                mpListPrev;
//STRIP001  ImpPolyNode*                mpListNext;
//STRIP001
//STRIP001 public:
//STRIP001  ImpPolyNode(const Vector3D& rPos, ImpPolyNode* pPrev);
//STRIP001  ~ImpPolyNode();
//STRIP001
//STRIP001  ImpPolyNode* GetPrev() const { return mpPrev; }
//STRIP001  ImpPolyNode* GetNext() const { return mpNext; }
//STRIP001  const Vector3D& GetPos() const { return maPosition; }
//STRIP001
//STRIP001  void CalcMinMaxX(double& fMaxAX, double& fMinAX);
//STRIP001  void CalcMinMaxY(double& fMaxAY, double& fMinAY);
//STRIP001
//STRIP001  void SwapPrevNext() { ImpPolyNode* pZwi = mpPrev; mpPrev = mpNext; mpNext = pZwi; }
//STRIP001  void SwapNextPointers(ImpPolyNode* pCand);
//STRIP001
//STRIP001  void AddToList(ImpPolyNode*& rpList);
//STRIP001  void RemFromList(ImpPolyNode*& rpList);
//STRIP001
//STRIP001  BOOL GetOrientation();
//STRIP001  void SwapOrientation();
//STRIP001
//STRIP001  void GetVolume(Volume3D& rVolume);
//STRIP001
//STRIP001  BOOL IsInside(const Vector3D& rPnt, BOOL bWithBorder = TRUE);
//STRIP001  BOOL IsPolyInside(ImpPolyNode* pPoly);
//STRIP001 };

//STRIP001 ImpPolyNode::ImpPolyNode(const Vector3D& rPos, ImpPolyNode* pPrev)
//STRIP001 :    maPosition(rPos),
//STRIP001  mpListPrev(this),
//STRIP001  mpListNext(this)
//STRIP001 {
//STRIP001  if(pPrev)
//STRIP001  {
//STRIP001      mpNext = pPrev->GetNext();
//STRIP001      mpPrev = pPrev;
//STRIP001      mpNext->mpPrev = this;
//STRIP001      mpPrev->mpNext = this;
//STRIP001  }
//STRIP001  else
//STRIP001      mpPrev = mpNext = this;
//STRIP001 }
//STRIP001
//STRIP001 ImpPolyNode::~ImpPolyNode()
//STRIP001 {
//STRIP001  if(mpNext != this)
//STRIP001  {
//STRIP001      mpPrev->mpNext = mpNext;
//STRIP001      mpNext->mpPrev = mpPrev;
//STRIP001  }
//STRIP001 }

//STRIP001 BOOL ImpPolyNode::IsPolyInside(ImpPolyNode* pPoly)
//STRIP001 {
//STRIP001  ImpPolyNode* pTest = pPoly;
//STRIP001  BOOL bAllAInside(TRUE);
//STRIP001
//STRIP001  do {
//STRIP001      bAllAInside = IsInside(pTest->GetPos());
//STRIP001      pTest = pTest->GetNext();
//STRIP001  } while(bAllAInside && pTest != pPoly);
//STRIP001
//STRIP001  return bAllAInside;
//STRIP001 }

//STRIP001 BOOL ImpPolyNode::IsInside(const Vector3D& rPnt, BOOL bWithBorder)
//STRIP001 {
//STRIP001  BOOL bInside(FALSE);
//STRIP001  ImpPolyNode* pAct = this;
//STRIP001
//STRIP001  do
//STRIP001  {
//STRIP001      if(bWithBorder
//STRIP001          && (fabs(pAct->GetPos().X() - rPnt.X()) < SMALL_DVALUE)
//STRIP001          && (fabs(pAct->GetPos().Y() - rPnt.Y()) < SMALL_DVALUE))
//STRIP001          return TRUE;
//STRIP001
//STRIP001      ImpPolyNode* pNext = pAct->GetNext();
//STRIP001      if((pAct->GetPos().Y() - rPnt.Y() > -SMALL_DVALUE) != (pNext->GetPos().Y() - rPnt.Y() > -SMALL_DVALUE))
//STRIP001      {
//STRIP001          BOOL bXFlagOld(pAct->GetPos().X() - rPnt.X() > -SMALL_DVALUE);
//STRIP001
//STRIP001          if(bXFlagOld == (pNext->GetPos().X() - rPnt.X() > -SMALL_DVALUE))
//STRIP001          {
//STRIP001              if(bXFlagOld)
//STRIP001                  bInside = !bInside;
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              double fCmp =
//STRIP001                  pNext->GetPos().X() - (pNext->GetPos().Y() - rPnt.Y()) *
//STRIP001                  (pAct->GetPos().X() - pNext->GetPos().X()) /
//STRIP001                  (pAct->GetPos().Y() - pNext->GetPos().Y());
//STRIP001
//STRIP001              if((bWithBorder && fCmp > rPnt.X()) || (!bWithBorder && fCmp - rPnt.X() > -SMALL_DVALUE))
//STRIP001                  bInside = !bInside;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      // next edge
//STRIP001      pAct = pNext;
//STRIP001
//STRIP001  } while(pAct != this);
//STRIP001
//STRIP001  return bInside;
//STRIP001 }

//STRIP001 void ImpPolyNode::GetVolume(Volume3D& rVolume)
//STRIP001 {
//STRIP001  ImpPolyNode* pAct = this;
//STRIP001  do {
//STRIP001      rVolume.Union(pAct->GetPos());
//STRIP001      pAct = pAct->GetPrev();
//STRIP001  } while(pAct != this);
//STRIP001 }

//STRIP001 void ImpPolyNode::SwapOrientation()
//STRIP001 {
//STRIP001  ImpPolyNode* pAct = this;
//STRIP001  do {
//STRIP001      pAct->SwapPrevNext();
//STRIP001      pAct = pAct->GetPrev();
//STRIP001  } while(pAct != this);
//STRIP001 }

//STRIP001 BOOL ImpPolyNode::GetOrientation()
//STRIP001 {
//STRIP001  ImpPolyNode* pOutmost = this;
//STRIP001  ImpPolyNode* pAct = this->GetNext();
//STRIP001
//STRIP001  while(pAct != this)
//STRIP001  {
//STRIP001      if(pOutmost->GetPos().X() - pAct->GetPos().X() > -SMALL_DVALUE)
//STRIP001      {
//STRIP001          if(pAct->GetPos().X() < pOutmost->GetPos().X())
//STRIP001          {
//STRIP001              pOutmost = pAct;
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              if(pAct->GetPos().Y() < pOutmost->GetPos().Y())
//STRIP001              {
//STRIP001                  pOutmost = pAct;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      // next node
//STRIP001      pAct = pAct->GetNext();
//STRIP001  }
//STRIP001
//STRIP001  Vector3D aVec1 = pOutmost->GetPrev()->GetPos() - pOutmost->GetPos();
//STRIP001  Vector3D aVec2 = pOutmost->GetNext()->GetPos() - pOutmost->GetPos();
//STRIP001  return (BOOL)((aVec1.X() * aVec2.Y() - aVec1.Y() * aVec2.X()) > -SMALL_DVALUE);
//STRIP001 }

//STRIP001 void ImpPolyNode::SwapNextPointers(ImpPolyNode* pCand)
//STRIP001 {
//STRIP001  ImpPolyNode* pZwi = mpNext;
//STRIP001  mpNext = pCand->mpNext;
//STRIP001  pCand->mpNext = pZwi;
//STRIP001  mpNext->mpPrev = this;
//STRIP001  pCand->mpNext->mpPrev = pCand;
//STRIP001 }

//STRIP001 void ImpPolyNode::AddToList(ImpPolyNode*& rpList)
//STRIP001 {
//STRIP001  if(rpList)
//STRIP001  {
//STRIP001      mpListNext = rpList->mpListNext;
//STRIP001      rpList->mpListNext = this;
//STRIP001      mpListPrev = rpList;
//STRIP001      mpListNext->mpListPrev = this;
//STRIP001  }
//STRIP001  else
//STRIP001      rpList = this;
//STRIP001 }

//STRIP001 void ImpPolyNode::RemFromList(ImpPolyNode*& rpList)
//STRIP001 {
//STRIP001  if(mpListNext != this)
//STRIP001  {
//STRIP001      if(rpList == this)
//STRIP001          rpList = mpListPrev;
//STRIP001      mpListPrev->mpListNext = mpListNext;
//STRIP001      mpListNext->mpListPrev = mpListPrev;
//STRIP001      mpListNext = mpListPrev = this;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if(rpList == this)
//STRIP001          rpList = NULL;
//STRIP001  }
//STRIP001 }

//STRIP001 void ImpPolyNode::CalcMinMaxX(double& fMaxAX, double& fMinAX)
//STRIP001 {
//STRIP001  if(maPosition.X() > mpNext->maPosition.X())
//STRIP001  {
//STRIP001      fMaxAX = maPosition.X();
//STRIP001      fMinAX = mpNext->maPosition.X();
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      fMaxAX = mpNext->maPosition.X();
//STRIP001      fMinAX = maPosition.X();
//STRIP001  }
//STRIP001 }

//STRIP001 void ImpPolyNode::CalcMinMaxY(double& fMaxAY, double& fMinAY)
//STRIP001 {
//STRIP001  if(maPosition.Y() > mpNext->maPosition.Y())
//STRIP001  {
//STRIP001      fMaxAY = maPosition.Y();
//STRIP001      fMinAY = mpNext->maPosition.Y();
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      fMaxAY = mpNext->maPosition.Y();
//STRIP001      fMinAY = maPosition.Y();
//STRIP001  }
//STRIP001 }

///////////////////////////////////////////////////////////////////////////////

//STRIP001 DECLARE_LIST(ImpPolyNodeList, ImpPolyNode*)//STRIP008 ;

///////////////////////////////////////////////////////////////////////////////

//STRIP001 class ImpSimpleCut
//STRIP001 {
//STRIP001  ImpPolyNode*                mpLeft;
//STRIP001  ImpPolyNode*                mpRight;
//STRIP001
//STRIP001  BOOL                        mbCorrectOrientation;
//STRIP001  BOOL                        mbOrientation;
//STRIP001
//STRIP001 public:
//STRIP001  ImpSimpleCut(ImpPolyNode* pL, ImpPolyNode* pR, BOOL bCoOr = FALSE, BOOL bOr = TRUE)
//STRIP001  :   mpLeft(pL),
//STRIP001      mpRight(pR),
//STRIP001      mbCorrectOrientation(bCoOr),
//STRIP001      mbOrientation(bOr)
//STRIP001  {
//STRIP001  }
//STRIP001
//STRIP001  void Solve();
//STRIP001  ImpPolyNode* GetLeft() const { return mpLeft; }
//STRIP001  ImpPolyNode* GetRight() const { return mpRight; }
//STRIP001
//STRIP001  BOOL IsSameCut(ImpPolyNode* pA, ImpPolyNode* pB) const
//STRIP001      { return ((pA == mpLeft && pB == mpRight) || (pB == mpLeft && pA == mpRight)); }
//STRIP001 };

//STRIP001 void ImpSimpleCut::Solve()
//STRIP001 {
//STRIP001  mpLeft->SwapNextPointers(mpRight);
//STRIP001
//STRIP001  if(mbCorrectOrientation)
//STRIP001  {
//STRIP001      if(mpLeft->GetOrientation() != mbOrientation)
//STRIP001          mpLeft->SwapOrientation();
//STRIP001
//STRIP001      if(mpRight->GetOrientation() != mbOrientation)
//STRIP001          mpRight->SwapOrientation();
//STRIP001  }
//STRIP001 }

///////////////////////////////////////////////////////////////////////////////

//STRIP001 DECLARE_LIST(ImpSimpleCutList, ImpSimpleCut*)//STRIP008 ;

///////////////////////////////////////////////////////////////////////////////

//STRIP001 class ImpExtraPolyInfo
//STRIP001 {
//STRIP001  Volume3D                    maVolume;
//STRIP001  INT16                       mnDepth;
//STRIP001  BOOL                        mbOrientation;
//STRIP001
//STRIP001 public:
//STRIP001  ImpExtraPolyInfo() {}
//STRIP001
//STRIP001  void Init(ImpPolyNode* pNew);
//STRIP001  const Volume3D& GetVolume() const { return maVolume; }
//STRIP001  BOOL GetOrientation() const { return mbOrientation; }
//STRIP001
//STRIP001  INT16 GetDepth() const { return mnDepth; }
//STRIP001  void ChangeDepth(BOOL bOrient) { if(bOrient) mnDepth++; else mnDepth--; }
//STRIP001 };

//STRIP001 void ImpExtraPolyInfo::Init(ImpPolyNode* pNew)
//STRIP001 {
//STRIP001  pNew->GetVolume(maVolume);
//STRIP001  mbOrientation = pNew->GetOrientation();
//STRIP001  mnDepth = (mbOrientation) ? 0 : -1;
//STRIP001 }

///////////////////////////////////////////////////////////////////////////////

//STRIP001 class ImpPolygonCutter
//STRIP001 {
//STRIP001  // list of polys
//STRIP001  ImpPolyNodeList         aPolyList;
//STRIP001  PolyPolygon3D           aNotClosedPolys;
//STRIP001
//STRIP001  // help routines
//STRIP001  BOOL IsSamePos(const Vector3D& rPntA, const Vector3D& rPntB)
//STRIP001      { return (fabs(rPntA.X() - rPntB.X()) < SMALL_DVALUE && fabs(rPntA.Y() - rPntB.Y()) < SMALL_DVALUE); }
//STRIP001  ImpSimpleCut* GetExistingCut(ImpSimpleCutList& rTmpCuts, ImpPolyNode* pA, ImpPolyNode* pB);
//STRIP001  ImpPolyNode* ExtractNextPoly(ImpPolyNode*& rpList);
//STRIP001  BOOL IsCrossover(ImpPolyNode* pA, ImpPolyNode* pB);
//STRIP001  BOOL IsCrossover(ImpSimpleCut* pEnter, ImpSimpleCut* pLeave);
//STRIP001  BOOL IsNextSamePos(ImpPolyNode* pA, ImpPolyNode* pB)
//STRIP001      { return IsSamePos(pA->GetNext()->GetPos(), pB->GetNext()->GetPos()); }
//STRIP001  BOOL IsPrevSamePos(ImpPolyNode* pA, ImpPolyNode* pB)
//STRIP001      { return IsSamePos(pA->GetPrev()->GetPos(), pB->GetPrev()->GetPos()); }
//STRIP001  void AddAllNodes(ImpPolyNode* pPoly, ImpPolyNode*& rpList);
//STRIP001  ImpPolyNode* CreateNewPoly(const Polygon3D& rPoly);
//STRIP001  void DeletePoly(ImpPolyNode* pCand);
//STRIP001  void PolysToList(ImpPolyNode*& rpList);
//STRIP001  void ListToPolys(ImpPolyNode*& rpList);
//STRIP001  BOOL DoVolumesIntersect(const Volume3D& rVol1, const Volume3D& rVol2) const;
//STRIP001  BOOL DoVolumesInclude(const Volume3D& rVol1, const Volume3D& rVol2) const;
//STRIP001  void SolveAllCuts(ImpSimpleCutList& rCuts);
//STRIP001
//STRIP001 public:
//STRIP001  ImpPolygonCutter() {}
//STRIP001  ~ImpPolygonCutter();
//STRIP001
//STRIP001  // put/get poly
//STRIP001  void AddPolyPolygon3D(PolyPolygon3D& rPoly, BOOL bForceClockwise = FALSE);
//STRIP001  void GetPolyPolygon3D(PolyPolygon3D& rPoly);
//STRIP001
//STRIP001  // transformations
//STRIP001  void RemoveSelfIntersections();
//STRIP001  void RemoveDoubleIntersections();
//STRIP001
//STRIP001  // remove included
//STRIP001  void RemoveIncludedPolygons(BOOL bUseOr = TRUE);
//STRIP001 };

//STRIP001 ImpPolygonCutter::~ImpPolygonCutter()
//STRIP001 {
//STRIP001  while(aPolyList.Count())
//STRIP001      delete aPolyList.Remove((UINT32)0L);
//STRIP001 }

//STRIP001 void ImpPolygonCutter::RemoveIncludedPolygons(BOOL bUseOr)
//STRIP001 {
//STRIP001  ImpExtraPolyInfo* pInfos = new ImpExtraPolyInfo[aPolyList.Count()];
//STRIP001  UINT32 aCount(aPolyList.Count());
//STRIP001  UINT32 a, b;
//STRIP001
//STRIP001  // fill infos
//STRIP001  for(a=0;a<aCount;a++)
//STRIP001      pInfos[a].Init(aPolyList.GetObject(a));
//STRIP001
//STRIP001  // get all includes
//STRIP001  for(a=0;a<aCount;a++)
//STRIP001  {
//STRIP001      ImpExtraPolyInfo& rInfoA = pInfos[a];
//STRIP001      for(b=0;b<aCount;b++)
//STRIP001      {
//STRIP001          ImpExtraPolyInfo& rInfoB = pInfos[b];
//STRIP001          if(a!=b && DoVolumesInclude(rInfoA.GetVolume(), rInfoB.GetVolume()))
//STRIP001          {
//STRIP001              // volume B in A, test pA, pB for inclusion
//STRIP001              if(aPolyList.GetObject(a)->IsPolyInside(aPolyList.GetObject(b)))
//STRIP001              {
//STRIP001                  // pB is inside pA
//STRIP001                  rInfoB.ChangeDepth(rInfoA.GetOrientation());
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // delete removable
//STRIP001  for(a=0,b=0;a<aCount;a++)
//STRIP001  {
//STRIP001      ImpExtraPolyInfo& rInfo = pInfos[a];
//STRIP001
//STRIP001      if((bUseOr && rInfo.GetDepth() != 0) || (!bUseOr && rInfo.GetDepth() < 1))
//STRIP001          DeletePoly(aPolyList.Remove((UINT32)b));
//STRIP001      else
//STRIP001          b++;
//STRIP001  }
//STRIP001
//STRIP001  // delete infos
//STRIP001  /*#90353#*/ delete [] pInfos;
//STRIP001 }

//STRIP001 void ImpPolygonCutter::SolveAllCuts(ImpSimpleCutList& rCuts)
//STRIP001 {
//STRIP001  ImpPolyNode* pNewList = NULL;
//STRIP001
//STRIP001  // add all nodes of polys to list
//STRIP001  PolysToList(pNewList);
//STRIP001
//STRIP001  // solve cuts
//STRIP001  while(rCuts.Count())
//STRIP001  {
//STRIP001      ImpSimpleCut* pCut = rCuts.Remove((UINT32)0L);
//STRIP001      pCut->Solve();
//STRIP001      delete pCut;
//STRIP001  }
//STRIP001
//STRIP001  // extract polys
//STRIP001  ListToPolys(pNewList);
//STRIP001 }

//STRIP001 BOOL ImpPolygonCutter::DoVolumesIntersect(const Volume3D& rVol1, const Volume3D& rVol2) const
//STRIP001 {
//STRIP001  if(rVol2.MaxVec().X() - rVol1.MinVec().X() > -SMALL_DVALUE && rVol1.MaxVec().X() - rVol2.MinVec().X() > -SMALL_DVALUE)
//STRIP001      if(rVol2.MaxVec().Y() - rVol1.MinVec().Y() > -SMALL_DVALUE && rVol1.MaxVec().Y() - rVol2.MinVec().Y() > -SMALL_DVALUE)
//STRIP001          return TRUE;
//STRIP001  return FALSE;
//STRIP001 }

//STRIP001 BOOL ImpPolygonCutter::DoVolumesInclude(const Volume3D& rVolA, const Volume3D& rVolB) const
//STRIP001 {
//STRIP001  return ((rVolB.MinVec().X() - rVolA.MinVec().X() > -SMALL_DVALUE)
//STRIP001      && (rVolA.MaxVec().X() - rVolB.MaxVec().X() > -SMALL_DVALUE)
//STRIP001      && (rVolB.MinVec().Y() - rVolA.MinVec().Y() > -SMALL_DVALUE)
//STRIP001      && (rVolA.MaxVec().Y() - rVolB.MaxVec().Y() > -SMALL_DVALUE));
//STRIP001 }

//STRIP001 void ImpPolygonCutter::PolysToList(ImpPolyNode*& rpList)
//STRIP001 {
//STRIP001  while(aPolyList.Count())
//STRIP001      AddAllNodes(aPolyList.Remove((UINT32)0L), rpList);
//STRIP001 }

//STRIP001 void ImpPolygonCutter::ListToPolys(ImpPolyNode*& rpList)
//STRIP001 {
//STRIP001  while(rpList)
//STRIP001  {
//STRIP001      // get one
//STRIP001      ImpPolyNode* pNew = ExtractNextPoly(rpList);
//STRIP001      if(pNew)
//STRIP001          aPolyList.Insert(pNew, LIST_APPEND);
//STRIP001  }
//STRIP001 }

//STRIP001 ImpPolyNode* ImpPolygonCutter::CreateNewPoly(const Polygon3D& rPoly)
//STRIP001 {
//STRIP001  ImpPolyNode* pRetval = NULL;
//STRIP001
//STRIP001  for(UINT16 a=0;a<rPoly.GetPointCount();a++)
//STRIP001      pRetval = new ImpPolyNode(rPoly[a], pRetval);
//STRIP001
//STRIP001  return pRetval;
//STRIP001 }

//STRIP001 void ImpPolygonCutter::DeletePoly(ImpPolyNode* pCand)
//STRIP001 {
//STRIP001  ImpPolyNode* pPoly = pCand;
//STRIP001
//STRIP001  while(pPoly)
//STRIP001  {
//STRIP001      ImpPolyNode* pNext = pPoly->GetNext();
//STRIP001      if(pNext == pPoly)
//STRIP001          pNext = NULL;
//STRIP001      delete pPoly;
//STRIP001      pPoly = pNext;
//STRIP001  }
//STRIP001 }

//STRIP001 void ImpPolygonCutter::AddAllNodes(ImpPolyNode* pPoly, ImpPolyNode*& rpList)
//STRIP001 {
//STRIP001  ImpPolyNode* pAct = pPoly;
//STRIP001  do {
//STRIP001      pAct->AddToList(rpList);
//STRIP001      pAct = pAct->GetNext();
//STRIP001  } while(pAct != pPoly);
//STRIP001 }

//STRIP001 void ImpPolygonCutter::AddPolyPolygon3D(PolyPolygon3D& rPoly, BOOL bForceClockwise)
//STRIP001 {
//STRIP001  for(UINT16 a=0;a<rPoly.Count();a++)
//STRIP001  {
//STRIP001      Polygon3D& rCand = rPoly[a];
//STRIP001      rCand.RemoveDoublePoints();
//STRIP001
//STRIP001      if(!rCand.IsClosed() || rCand.GetPointCount() < 3)
//STRIP001      {
//STRIP001          aNotClosedPolys.Insert(rCand);
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          if(bForceClockwise && !rCand.IsClockwise())
//STRIP001              rCand.FlipDirection();
//STRIP001
//STRIP001          ImpPolyNode* pNew = CreateNewPoly(rCand); // new ImpSimplePoly(rCand);
//STRIP001          aPolyList.Insert(pNew, LIST_APPEND);
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void ImpPolygonCutter::GetPolyPolygon3D(PolyPolygon3D& rPoly)
//STRIP001 {
//STRIP001  while(aPolyList.Count())
//STRIP001  {
//STRIP001      ImpPolyNode* pCand = aPolyList.Remove((UINT32)0L);
//STRIP001      ImpPolyNode* pAct = pCand;
//STRIP001      UINT16 nCount(0);
//STRIP001
//STRIP001      do {
//STRIP001          nCount++;
//STRIP001          pAct = pAct->GetNext();
//STRIP001      } while(pAct != pCand);
//STRIP001
//STRIP001      if(nCount > 2)
//STRIP001      {
//STRIP001          Polygon3D aNewPoly(nCount);
//STRIP001          nCount = 0;
//STRIP001
//STRIP001          do {
//STRIP001              aNewPoly[nCount++] = pAct->GetPos();
//STRIP001              pAct = pAct->GetNext();
//STRIP001          } while(pAct != pCand);
//STRIP001
//STRIP001          aNewPoly.SetClosed(TRUE);
//STRIP001          rPoly.Insert(aNewPoly);
//STRIP001      }
//STRIP001
//STRIP001      DeletePoly(pCand);
//STRIP001  }
//STRIP001
//STRIP001  while(aNotClosedPolys.Count())
//STRIP001      rPoly.Insert(aNotClosedPolys.Remove(0L));
//STRIP001 }

//STRIP001 ImpSimpleCut* ImpPolygonCutter::GetExistingCut(ImpSimpleCutList& rTmpCuts, ImpPolyNode* pA, ImpPolyNode* pB)
//STRIP001 {
//STRIP001  for(UINT32 a=0;a<rTmpCuts.Count();a++)
//STRIP001  {
//STRIP001      ImpSimpleCut* pCand = rTmpCuts.GetObject(a);
//STRIP001      if(pCand->IsSameCut(pA, pB))
//STRIP001          return pCand;
//STRIP001  }
//STRIP001
//STRIP001  return NULL;
//STRIP001 }

//STRIP001 ImpPolyNode* ImpPolygonCutter::ExtractNextPoly(ImpPolyNode*& rpList)
//STRIP001 {
//STRIP001  ImpPolyNode* pStart = rpList;
//STRIP001
//STRIP001  // remove all nodes of this poly from list
//STRIP001  ImpPolyNode* pAct = pStart;
//STRIP001  UINT32 nNumNodes(0L);
//STRIP001  do {
//STRIP001      pAct->RemFromList(rpList);
//STRIP001      pAct = pAct->GetNext();
//STRIP001      nNumNodes++;
//STRIP001  } while(pAct != pStart);
//STRIP001
//STRIP001  if(nNumNodes < 3)
//STRIP001  {
//STRIP001      DeletePoly(pStart);
//STRIP001      return NULL;
//STRIP001  }
//STRIP001  else
//STRIP001      return pStart;
//STRIP001 }

//STRIP001 void ImpPolygonCutter::RemoveSelfIntersections()
//STRIP001 {
//STRIP001  ImpSimpleCutList aCuts(256, 256);
//STRIP001  ImpSimpleCutList aNewCuts(64, 64);
//STRIP001  ImpPolyNode* pCand;
//STRIP001  ImpPolyNode* pA;
//STRIP001  ImpPolyNode* pB;
//STRIP001  double fMaxAX, fMinAX, fMaxAY, fMinAY;
//STRIP001  double fMaxBX, fMinBX, fMaxBY, fMinBY;
//STRIP001  double fCut;
//STRIP001
//STRIP001  // first job: Find all cuts and add points there
//STRIP001  for(UINT32 a=0;a<aPolyList.Count();a++)
//STRIP001  {
//STRIP001      pCand = aPolyList.GetObject(a);
//STRIP001      pA = pCand;
//STRIP001
//STRIP001      // one run to find same start positions (so there is no need to
//STRIP001      // search for existing cuts in main loop)
//STRIP001      do {
//STRIP001          pB = pA->GetNext();
//STRIP001          do {
//STRIP001              if(IsSamePos(pA->GetPos(), pB->GetPos()))
//STRIP001                  aNewCuts.Insert(new ImpSimpleCut(pA, pB, TRUE, pCand->GetOrientation()), LIST_APPEND);
//STRIP001
//STRIP001              // next B
//STRIP001              pB = pB->GetNext();
//STRIP001          } while(pB != pCand);
//STRIP001
//STRIP001          // next A
//STRIP001          pA = pA->GetNext();
//STRIP001      } while(pA->GetNext() != pCand);
//STRIP001
//STRIP001      // second run to find real cuts
//STRIP001      pA = pCand;
//STRIP001      do {
//STRIP001          // get bounds for this edge in poly
//STRIP001          pA->CalcMinMaxX(fMaxAX, fMinAX);
//STRIP001          pA->CalcMinMaxY(fMaxAY, fMinAY);
//STRIP001
//STRIP001          pB = pA->GetNext();
//STRIP001          do {
//STRIP001              pB->CalcMinMaxX(fMaxBX, fMinBX);
//STRIP001              if(fMaxBX - fMinAX > -SMALL_DVALUE && fMaxAX - fMinBX > -SMALL_DVALUE)
//STRIP001              {
//STRIP001                  pB->CalcMinMaxY(fMaxBY, fMinBY);
//STRIP001                  if(fMaxBY - fMinAY > -SMALL_DVALUE && fMaxAY - fMinBY > -SMALL_DVALUE)
//STRIP001                  {
//STRIP001                      if(!IsSamePos(pA->GetPos(), pB->GetPos()))
//STRIP001                      {
//STRIP001                          if(Polygon3D::FindCut(pA->GetPos(), pA->GetNext()->GetPos() - pA->GetPos(), pB->GetPos(), pB->GetNext()->GetPos() - pB->GetPos(), CUTFLAG_LINE, &fCut))
//STRIP001                          {
//STRIP001                              // crossover, two new points
//STRIP001                              Vector3D aNewPos;
//STRIP001                              aNewPos.CalcInBetween(pA->GetPos(), pA->GetNext()->GetPos(), fCut);
//STRIP001                              ImpPolyNode* pCutLo = new ImpPolyNode(aNewPos, pA);
//STRIP001                              ImpPolyNode* pCutHi = new ImpPolyNode(aNewPos, pB);
//STRIP001                              aNewCuts.Insert(new ImpSimpleCut(pCutLo, pCutHi, TRUE, pCand->GetOrientation()), LIST_APPEND);
//STRIP001                              pA->CalcMinMaxX(fMaxAX, fMinAX);
//STRIP001                              pA->CalcMinMaxY(fMaxAY, fMinAY);
//STRIP001                          }
//STRIP001                          else
//STRIP001                          {
//STRIP001                              if(Polygon3D::FindPointInLine(pA->GetPos(), pB->GetPos(), pB->GetNext()->GetPos() - pB->GetPos(), &fCut))
//STRIP001                              {
//STRIP001                                  // startpoint A at edge B, one new point
//STRIP001                                  ImpPolyNode* pCutHi = new ImpPolyNode(pA->GetPos(), pB);
//STRIP001                                  aNewCuts.Insert(new ImpSimpleCut(pA, pCutHi, TRUE, pCand->GetOrientation()), LIST_APPEND);
//STRIP001                              }
//STRIP001                              else if(Polygon3D::FindPointInLine(pB->GetPos(), pA->GetPos(), pA->GetNext()->GetPos() - pA->GetPos(), &fCut))
//STRIP001                              {
//STRIP001                                  // startpoint B at edge A, one new point
//STRIP001                                  ImpPolyNode* pCutLo = new ImpPolyNode(pB->GetPos(), pA);
//STRIP001                                  aNewCuts.Insert(new ImpSimpleCut(pCutLo, pB, TRUE, pCand->GetOrientation()), LIST_APPEND);
//STRIP001                                  pA->CalcMinMaxX(fMaxAX, fMinAX);
//STRIP001                                  pA->CalcMinMaxY(fMaxAY, fMinAY);
//STRIP001                              }
//STRIP001                          }
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001
//STRIP001              // next B
//STRIP001              pB = pB->GetNext();
//STRIP001          } while(pB != pCand);
//STRIP001
//STRIP001          // next A
//STRIP001          pA = pA->GetNext();
//STRIP001      } while(pA->GetNext() != pCand);
//STRIP001
//STRIP001      // copy new cuts to cuts
//STRIP001      while(aNewCuts.Count())
//STRIP001          aCuts.Insert(aNewCuts.Remove((UINT32)0L));
//STRIP001  }
//STRIP001
//STRIP001  // second job: if there were cuts, split polys
//STRIP001  if(aCuts.Count())
//STRIP001      SolveAllCuts(aCuts);
//STRIP001 }

//STRIP001 BOOL ImpPolygonCutter::IsCrossover(ImpPolyNode* pA, ImpPolyNode* pB)
//STRIP001 {
//STRIP001  // build entering vectors
//STRIP001  Vector3D aVecA = pA->GetPrev()->GetPos() - pA->GetPos();
//STRIP001  Vector3D aVecB = pB->GetPrev()->GetPos() - pA->GetPos();
//STRIP001  aVecA.Normalize();
//STRIP001  aVecB.Normalize();
//STRIP001  double fDegreeA2 = atan2(aVecA.Y(), aVecA.X());
//STRIP001  double fDegreeB2 = atan2(aVecB.Y(), aVecB.X());
//STRIP001
//STRIP001  // build leaving vectors
//STRIP001  aVecA = pA->GetNext()->GetPos() - pA->GetPos();
//STRIP001  aVecB = pB->GetNext()->GetPos() - pA->GetPos();
//STRIP001  aVecA.Normalize();
//STRIP001  aVecB.Normalize();
//STRIP001  double fDegreeA1 = atan2(aVecA.Y(), aVecA.X());
//STRIP001  double fDegreeB1 = atan2(aVecB.Y(), aVecB.X());
//STRIP001
//STRIP001  // compare
//STRIP001  if(fDegreeA1 > fDegreeA2)
//STRIP001  {
//STRIP001      double fZwi = fDegreeA2;
//STRIP001      fDegreeA2 = fDegreeA1;
//STRIP001      fDegreeA1 = fZwi;
//STRIP001  }
//STRIP001
//STRIP001  BOOL bB1Inside = (fDegreeB1 - fDegreeA1 > SMALL_DVALUE && fDegreeA2 - fDegreeB1 > SMALL_DVALUE);
//STRIP001  BOOL bB2Inside = (fDegreeB2 - fDegreeA1 > SMALL_DVALUE && fDegreeA2 - fDegreeB2 > SMALL_DVALUE);
//STRIP001
//STRIP001  if(bB1Inside && bB2Inside)
//STRIP001      return FALSE;
//STRIP001
//STRIP001  BOOL bB1Outside = (fDegreeA1 - fDegreeB1 > SMALL_DVALUE || fDegreeB1 - fDegreeA2 > SMALL_DVALUE);
//STRIP001  BOOL bB2Outside = (fDegreeA1 - fDegreeB2 > SMALL_DVALUE || fDegreeB2 - fDegreeA2 > SMALL_DVALUE);
//STRIP001
//STRIP001  return !(bB1Outside && bB2Outside);
//STRIP001 }

//STRIP001 BOOL ImpPolygonCutter::IsCrossover(ImpSimpleCut* pEnter, ImpSimpleCut* pLeave)
//STRIP001 {
//STRIP001  // build entering vectors
//STRIP001  Vector3D aVecJ = pEnter->GetLeft()->GetNext()->GetPos() - pEnter->GetLeft()->GetPos();
//STRIP001  Vector3D aVecA = pEnter->GetLeft()->GetPrev()->GetPos() - pEnter->GetLeft()->GetPos();
//STRIP001  Vector3D aVecB = pEnter->GetRight()->GetPrev()->GetPos() - pEnter->GetLeft()->GetPos();
//STRIP001  aVecJ.Normalize();
//STRIP001  aVecA.Normalize();
//STRIP001  aVecB.Normalize();
//STRIP001  double fDegreeJo = atan2(aVecJ.Y(), aVecJ.X());
//STRIP001  double fDegreeA2 = atan2(aVecA.Y(), aVecA.X()) - fDegreeJo;
//STRIP001  double fDegreeB2 = atan2(aVecB.Y(), aVecB.X()) - fDegreeJo;
//STRIP001
//STRIP001  // move to range [0..2PI[
//STRIP001  while(fDegreeA2 < 0)
//STRIP001      fDegreeA2 += (2.0 * F_PI);
//STRIP001  while(fDegreeA2 >= (2.0 * F_PI))
//STRIP001      fDegreeA2 -= (2.0 * F_PI);
//STRIP001
//STRIP001  // move to range [0..2PI[
//STRIP001  while(fDegreeB2 < 0)
//STRIP001      fDegreeB2 += (2.0 * F_PI);
//STRIP001  while(fDegreeB2 >= (2.0 * F_PI))
//STRIP001      fDegreeB2 -= (2.0 * F_PI);
//STRIP001
//STRIP001  BOOL bA2BiggerB2 = (fDegreeA2 - fDegreeB2 > -SMALL_DVALUE);
//STRIP001
//STRIP001  // build leaving vectors
//STRIP001  aVecJ = pLeave->GetLeft()->GetPrev()->GetPos() - pLeave->GetLeft()->GetPos();
//STRIP001  aVecA = pLeave->GetLeft()->GetNext()->GetPos() - pLeave->GetLeft()->GetPos();
//STRIP001  aVecB = pLeave->GetRight()->GetNext()->GetPos() - pLeave->GetLeft()->GetPos();
//STRIP001  aVecJ.Normalize();
//STRIP001  aVecA.Normalize();
//STRIP001  aVecB.Normalize();
//STRIP001  fDegreeJo = atan2(aVecJ.Y(), aVecJ.X());
//STRIP001  double fDegreeA1 = atan2(aVecA.Y(), aVecA.X()) - fDegreeJo;
//STRIP001  double fDegreeB1 = atan2(aVecB.Y(), aVecB.X()) - fDegreeJo;
//STRIP001
//STRIP001  // move to range [0..2PI[
//STRIP001  while(fDegreeA1 < 0)
//STRIP001      fDegreeA1 += (2.0 * F_PI);
//STRIP001  while(fDegreeA1 >= (2.0 * F_PI))
//STRIP001      fDegreeA1 -= (2.0 * F_PI);
//STRIP001
//STRIP001  // move to range [0..2PI[
//STRIP001  while(fDegreeB1 < 0)
//STRIP001      fDegreeB1 += (2.0 * F_PI);
//STRIP001  while(fDegreeB1 >= (2.0 * F_PI))
//STRIP001      fDegreeB1 -= (2.0 * F_PI);
//STRIP001
//STRIP001  BOOL bA1BiggerB1 = (fDegreeA1 - fDegreeB1 > -SMALL_DVALUE);
//STRIP001
//STRIP001  // compare
//STRIP001  return (bA1BiggerB1 == bA2BiggerB2);
//STRIP001 }

//STRIP001 void ImpPolygonCutter::RemoveDoubleIntersections()
//STRIP001 {
//STRIP001  double fMaxAX, fMinAX, fMaxAY, fMinAY;
//STRIP001  double fMaxBX, fMinBX, fMaxBY, fMinBY;
//STRIP001  double fCut;
//STRIP001  ImpSimpleCutList aCuts(256, 256);
//STRIP001  ImpSimpleCutList aTmpCuts(64, 64);
//STRIP001  ImpSimpleCutList aNewCuts(64, 64);
//STRIP001  ImpPolyNode* pCandA;
//STRIP001  ImpPolyNode* pCandB;
//STRIP001  ImpPolyNode* pA;
//STRIP001  ImpPolyNode* pB;
//STRIP001  UINT32 a;
//STRIP001
//STRIP001  // create volume list for all polys for faster compares
//STRIP001  Volume3D* pVolumes = new Volume3D[aPolyList.Count()];
//STRIP001
//STRIP001  for(a=0L;a<aPolyList.Count();a++)
//STRIP001      aPolyList.GetObject(a)->GetVolume(pVolumes[a]);
//STRIP001
//STRIP001  // register cuts (and add points for them) between pCandA and pCandB
//STRIP001  for(a=0L;a+1<aPolyList.Count();a++)
//STRIP001  {
//STRIP001      pCandA = aPolyList.GetObject(a);
//STRIP001      for(UINT32 b=a+1;b<aPolyList.Count();b++)
//STRIP001      {
//STRIP001          if(DoVolumesIntersect(pVolumes[a], pVolumes[b]))
//STRIP001          {
//STRIP001              pCandB = aPolyList.GetObject(b);
//STRIP001              pA = pCandA;
//STRIP001
//STRIP001              // one run to find same start positions (so there is no need to
//STRIP001              // search for existing cuts in main loop)
//STRIP001              do {
//STRIP001                  pB = pCandB;
//STRIP001                  do {
//STRIP001                      if(IsSamePos(pA->GetPos(), pB->GetPos()))
//STRIP001                          aTmpCuts.Insert(new ImpSimpleCut(pA, pB), LIST_APPEND);
//STRIP001
//STRIP001                      // next B
//STRIP001                      pB = pB->GetNext();
//STRIP001                  } while(pB != pCandB);
//STRIP001
//STRIP001                  // next A
//STRIP001                  pA = pA->GetNext();
//STRIP001              } while(pA != pCandA);
//STRIP001
//STRIP001              // second run to find real cuts
//STRIP001              pA = pCandA;
//STRIP001              do {
//STRIP001                  // get bounds for this edge in poly
//STRIP001                  pA->CalcMinMaxX(fMaxAX, fMinAX);
//STRIP001                  pA->CalcMinMaxY(fMaxAY, fMinAY);
//STRIP001
//STRIP001                  pB = pCandB;
//STRIP001                  do {
//STRIP001                      pB->CalcMinMaxX(fMaxBX, fMinBX);
//STRIP001                      if(fMaxBX - fMinAX > -SMALL_DVALUE && fMaxAX - fMinBX > -SMALL_DVALUE)
//STRIP001                      {
//STRIP001                          pB->CalcMinMaxY(fMaxBY, fMinBY);
//STRIP001                          if(fMaxBY - fMinAY > -SMALL_DVALUE && fMaxAY - fMinBY > -SMALL_DVALUE)
//STRIP001                          {
//STRIP001                              if(!IsSamePos(pA->GetPos(), pB->GetPos()))
//STRIP001                              {
//STRIP001                                  if(Polygon3D::FindCut(pA->GetPos(), pA->GetNext()->GetPos() - pA->GetPos(), pB->GetPos(), pB->GetNext()->GetPos() - pB->GetPos(), CUTFLAG_LINE, &fCut))
//STRIP001                                  {
//STRIP001                                      // crossover, two new points, use as cutpoint
//STRIP001                                      Vector3D aNewPos;
//STRIP001
//STRIP001                                      aNewPos.CalcInBetween(pA->GetPos(), pA->GetNext()->GetPos(), fCut);
//STRIP001                                      ImpPolyNode* pCutLo = new ImpPolyNode(aNewPos, pA);
//STRIP001                                      ImpPolyNode* pCutHi = new ImpPolyNode(aNewPos, pB);
//STRIP001                                      aNewCuts.Insert(new ImpSimpleCut(pCutLo, pCutHi), LIST_APPEND);
//STRIP001                                      pA->CalcMinMaxX(fMaxAX, fMinAX);
//STRIP001                                      pA->CalcMinMaxY(fMaxAY, fMinAY);
//STRIP001                                  }
//STRIP001                                  else
//STRIP001                                  {
//STRIP001                                      if(Polygon3D::FindPointInLine(pA->GetPos(), pB->GetPos(), pB->GetNext()->GetPos() - pB->GetPos(), &fCut))
//STRIP001                                      {
//STRIP001                                          // startpoint A at edge B, one new point
//STRIP001                                          // leaves or enters common section
//STRIP001                                          ImpPolyNode* pCutHi = new ImpPolyNode(pA->GetPos(), pB);
//STRIP001                                          aTmpCuts.Insert(new ImpSimpleCut(pA, pCutHi), LIST_APPEND);
//STRIP001                                      }
//STRIP001                                      else if(Polygon3D::FindPointInLine(pB->GetPos(), pA->GetPos(), pA->GetNext()->GetPos() - pA->GetPos(), &fCut))
//STRIP001                                      {
//STRIP001                                          // startpoint B at edge A, one new point
//STRIP001                                          // leaves or enters common section
//STRIP001                                          ImpPolyNode* pCutLo = new ImpPolyNode(pB->GetPos(), pA);
//STRIP001                                          aTmpCuts.Insert(new ImpSimpleCut(pCutLo, pB), LIST_APPEND);
//STRIP001                                          pA->CalcMinMaxX(fMaxAX, fMinAX);
//STRIP001                                          pA->CalcMinMaxY(fMaxAY, fMinAY);
//STRIP001                                      }
//STRIP001                                  }
//STRIP001                              }
//STRIP001                          }
//STRIP001                      }
//STRIP001
//STRIP001                      // next B
//STRIP001                      pB = pB->GetNext();
//STRIP001                  } while(pB != pCandB);
//STRIP001
//STRIP001                  // next A
//STRIP001                  pA = pA->GetNext();
//STRIP001              } while(pA != pCandA);
//STRIP001
//STRIP001              // test all temporary cuts for simple criteria
//STRIP001              for(UINT32 c=0;c<aTmpCuts.Count();)
//STRIP001              {
//STRIP001                  ImpSimpleCut* pCand = aTmpCuts.GetObject(c);
//STRIP001                  BOOL bPrevSamePos(IsPrevSamePos(pCand->GetLeft(), pCand->GetRight()));
//STRIP001                  BOOL bNextSamePos(IsNextSamePos(pCand->GetLeft(), pCand->GetRight()));
//STRIP001                  BOOL bDelete(FALSE);
//STRIP001                  BOOL bIncC(TRUE);
//STRIP001
//STRIP001                  if(bPrevSamePos && bNextSamePos)
//STRIP001                  {
//STRIP001                      // single point inside continued same direction section
//STRIP001                      bDelete = TRUE;
//STRIP001                  }
//STRIP001                  else if(!bPrevSamePos && !bNextSamePos)
//STRIP001                  {
//STRIP001                      // this is no same direction section, test for real cut
//STRIP001                      if(IsCrossover(pCand->GetLeft(), pCand->GetRight()))
//STRIP001                      {
//STRIP001                          // real cut, move to real cutlist
//STRIP001                          aNewCuts.Insert(aTmpCuts.Remove(c), LIST_APPEND);
//STRIP001                          bIncC = FALSE;
//STRIP001                      }
//STRIP001                      else
//STRIP001                      {
//STRIP001                          // no cut, just a touch in one point
//STRIP001                          bDelete = TRUE;
//STRIP001                      }
//STRIP001                  }
//STRIP001
//STRIP001                  // delete if wanted
//STRIP001                  if(bDelete)
//STRIP001                  {
//STRIP001                      delete aTmpCuts.Remove(c);
//STRIP001                      bIncC = FALSE;
//STRIP001                  }
//STRIP001
//STRIP001                  // next candidate
//STRIP001                  if(bIncC)
//STRIP001                      c++;
//STRIP001              }
//STRIP001
//STRIP001              // are there entering/leaving same direction sections?
//STRIP001              while(aTmpCuts.Count())
//STRIP001              {
//STRIP001                  // this cuts enter/leave a common same-direction section between
//STRIP001                  // polygons pCandA, pCandB. If it is a real crossover, a cutpoint
//STRIP001                  // for it is needed, else it can be ignored.
//STRIP001                  ImpSimpleCut* pCutA = aTmpCuts.Remove((UINT32)0L);
//STRIP001                  ImpPolyNode* pActA = pCutA->GetLeft();
//STRIP001                  ImpPolyNode* pActB = pCutA->GetRight();
//STRIP001                  BOOL bPrevSamePos(IsPrevSamePos(pActA, pActB));
//STRIP001                  BOOL bNextSamePos(IsNextSamePos(pActA, pActB));
//STRIP001
//STRIP001                  if(aTmpCuts.Count())
//STRIP001                  {
//STRIP001                      ImpSimpleCut* pCutB = NULL;
//STRIP001
//STRIP001                      if(IsNextSamePos(pCutA->GetLeft(), pCutA->GetRight()))
//STRIP001                      {
//STRIP001                          // this is a start node
//STRIP001                          ImpPolyNode* pActA = pCutA->GetLeft()->GetNext();
//STRIP001                          ImpPolyNode* pActB = pCutA->GetRight()->GetNext();
//STRIP001
//STRIP001                          while(!pCutB && pActA != pCutA->GetLeft())
//STRIP001                          {
//STRIP001                              if(!IsNextSamePos(pActA, pActB))
//STRIP001                                  pCutB = GetExistingCut(aTmpCuts, pActA, pActB);
//STRIP001
//STRIP001                              pActA = pActA->GetNext();
//STRIP001                              pActB = pActB->GetNext();
//STRIP001                          }
//STRIP001
//STRIP001                          if(pCutB)
//STRIP001                          {
//STRIP001                              aTmpCuts.Remove(pCutB);
//STRIP001
//STRIP001                              if(IsCrossover(pCutA, pCutB))
//STRIP001                                  aNewCuts.Insert(pCutB, LIST_APPEND);
//STRIP001                              else
//STRIP001                                  delete pCutB;
//STRIP001                          }
//STRIP001                      }
//STRIP001                      else
//STRIP001                      {
//STRIP001                          // this is a end node
//STRIP001                          ImpPolyNode* pActA = pCutA->GetLeft()->GetPrev();
//STRIP001                          ImpPolyNode* pActB = pCutA->GetRight()->GetPrev();
//STRIP001
//STRIP001                          while(!pCutB && pActA != pCutA->GetLeft())
//STRIP001                          {
//STRIP001                              if(!IsPrevSamePos(pActA, pActB))
//STRIP001                                  pCutB = GetExistingCut(aTmpCuts, pActA, pActB);
//STRIP001
//STRIP001                              pActA = pActA->GetPrev();
//STRIP001                              pActB = pActB->GetPrev();
//STRIP001                          }
//STRIP001
//STRIP001                          if(pCutB)
//STRIP001                          {
//STRIP001                              aTmpCuts.Remove(pCutB);
//STRIP001
//STRIP001                              if(IsCrossover(pCutB, pCutA))
//STRIP001                                  aNewCuts.Insert(pCutB, LIST_APPEND);
//STRIP001                              else
//STRIP001                                  delete pCutB;
//STRIP001                          }
//STRIP001                      }
//STRIP001                  }
//STRIP001
//STRIP001                  // delete cut in EVERY case
//STRIP001                  delete pCutA;
//STRIP001              }
//STRIP001
//STRIP001              // copy new cuts to all cuts
//STRIP001              while(aNewCuts.Count())
//STRIP001                  aCuts.Insert(aNewCuts.Remove((UINT32)0L), LIST_APPEND);
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // delete volume list again
//STRIP001  /*#90353#*/ delete [] pVolumes;
//STRIP001
//STRIP001  // are there cuts to solve? Solve them all in one run
//STRIP001  if(aCuts.Count())
//STRIP001      SolveAllCuts(aCuts);
//STRIP001 }

///////////////////////////////////////////////////////////////////////////////

//STRIP001 void PolyPolygon3D::Merge(BOOL bForceClockwise, BOOL bInvertRemove)
//STRIP001 {
//STRIP001  ImpPolygonCutter aCutter;
//STRIP001
//STRIP001  aCutter.AddPolyPolygon3D(*this, bForceClockwise);
//STRIP001  aCutter.RemoveSelfIntersections();
//STRIP001  aCutter.RemoveDoubleIntersections();
//STRIP001  aCutter.RemoveIncludedPolygons(!bInvertRemove);
//STRIP001  Clear();
//STRIP001  aCutter.GetPolyPolygon3D(*this);
//STRIP001 }



}
