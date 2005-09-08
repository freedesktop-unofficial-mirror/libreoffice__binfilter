/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_pntobj3d.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-08 05:33:08 $
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

#ifndef _SVDIO_HXX
#include "svdio.hxx"
#endif

// auto strip #ifndef _E3D_GLOBL3D_HXX
// auto strip #include "globl3d.hxx"
// auto strip #endif

#ifndef _E3D_PNTOBJ3D_HXX
#include "pntobj3d.hxx"
#endif
namespace binfilter {

/*N*/ TYPEINIT1(E3dPointObj, E3dObject);

/*************************************************************************
|*
|* Konstruktor
|*
\************************************************************************/

/*N*/ E3dPointObj::E3dPointObj(const Vector3D& rPos) :
/*N*/   aPosition(rPos),
/*N*/   bTransPosValid(FALSE)
/*N*/ {
/*N*/   aLocalBoundVol = Volume3D(aPosition, Vector3D(), FALSE);
/*N*/   bBoundVolValid = FALSE;
/*N*/ }

/*************************************************************************
|*
|* Leer-Konstruktor
|*
\************************************************************************/

/*N*/ E3dPointObj::E3dPointObj() :
/*N*/   aPosition(Vector3D()),
/*N*/   bTransPosValid(FALSE)
/*N*/ {
/*N*/   aLocalBoundVol = Volume3D(aPosition, Vector3D(), FALSE);
/*N*/   bBoundVolValid = FALSE;
/*N*/ }

/*************************************************************************
|*
|* bei Aenderung der Transformation
|*
\************************************************************************/

/*N*/ void E3dPointObj::SetTransformChanged()
/*N*/ {
/*N*/   E3dObject::SetTransformChanged();
/*N*/   bTransPosValid = FALSE;
/*N*/ }

/*************************************************************************
|*
|* Identifier zurueckgeben
|*
\************************************************************************/

//STRIP001 UINT16 E3dPointObj::GetObjIdentifier() const
//STRIP001 {
//STRIP001  return E3D_POINTOBJ_ID;
//STRIP001 }

/*************************************************************************
|*
|* neue Position setzen und Aenderung an Parents (Szene) melden
|*
\************************************************************************/

/*N*/ void E3dPointObj::SetPosition(const Vector3D& rNewPos)
/*N*/ {
/*N*/   if ( aPosition != rNewPos )
/*N*/   {
/*N*/       aPosition = rNewPos;
/*N*/       bBoundVolValid = FALSE;
/*N*/       bTransPosValid = FALSE;
/*N*/       StructureChanged(this);
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* Transformierte Position zurueckgeben
|*
\************************************************************************/

/*N*/ const Vector3D& E3dPointObj::GetTransPosition()
/*N*/ {
/*N*/   if ( !bTransPosValid )
/*N*/   {
/*N*/       aTransPos = GetFullTransform() * aPosition;
/*N*/       bTransPosValid = TRUE;
/*N*/   }
/*N*/   return aTransPos;
/*N*/ }

/*************************************************************************
|*
|* sichern
|*
\************************************************************************/

/*N*/ void E3dPointObj::WriteData(SvStream& rOut) const
/*N*/ {
/*N*/ #ifndef SVX_LIGHT
/*N*/   E3dObject::WriteData(rOut);
/*N*/
/*N*/ #ifdef E3D_STREAMING
/*N*/
/*N*/   SdrDownCompat aCompat(rOut, STREAM_WRITE);
/*N*/ #ifdef DBG_UTIL
/*N*/   aCompat.SetID("E3dPointObj");
/*N*/ #endif
/*N*/
/*N*/   rOut << aPosition;
/*N*/ #endif
/*N*/ #endif    // #ifndef SVX_LIGHT
/*N*/ }

/*************************************************************************
|*
|* laden
|*
\************************************************************************/

/*N*/ void E3dPointObj::ReadData(const SdrObjIOHeader& rHead, SvStream& rIn)
/*N*/ {
/*N*/   if (ImpCheckSubRecords (rHead, rIn))
/*N*/   {
/*N*/       E3dObject::ReadData(rHead, rIn);
/*N*/
/*N*/       SdrDownCompat aCompat(rIn, STREAM_READ);
/*N*/ #ifdef DBG_UTIL
/*N*/       aCompat.SetID("E3dPointObj");
/*N*/ #endif
/*N*/
/*N*/       rIn >> aPosition;
/*N*/
/*N*/       bTransPosValid = FALSE;
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* Zuweisungsoperator
|*
\************************************************************************/

//STRIP001 void E3dPointObj::operator=(const SdrObject& rObj)
//STRIP001 {
//STRIP001  E3dObject::operator=(rObj);
//STRIP001
//STRIP001  const E3dPointObj& r3DObj = (const E3dPointObj&) rObj;
//STRIP001  aPosition = r3DObj.aPosition;
//STRIP001  // sicher ist sicher...
//STRIP001  bTransPosValid = FALSE;
//STRIP001 }



}
